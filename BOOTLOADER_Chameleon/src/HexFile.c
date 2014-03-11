/*
 * HexFile.c
 *
 * Created: 19/02/2014 4:53:24 PM
 *  Author: lawrencec
 */ 

#include "compiler.h"
#include "preprocessor.h"
#include "string.h"
#include "HexFile.h"
#include "BLOWFISH.H"
#include "print_funcs.h"

typedef unsigned long word32;

/* store one block of data */
//#define CHUNK_LEN	8
//typedef struct {
//	unsigned char b[CHUNK_LEN];
//} chunk;

typedef struct {
	//char	startCode;
	unsigned char	byteCount;
	unsigned short	addr;
	unsigned char	recType;
	unsigned char	data[16];
	unsigned char	chksum;
} HexLine;

/* function prototypes */
void getv(char *s, unsigned char *v, int len);
void getl(unsigned char *v, unsigned long *lv);
void getb(unsigned long *lv, unsigned char *v);

void InitialiseHexLine(unsigned char* str, HexLine* aLine);
unsigned char HexStrToInt(char *s);
int ConvertHexStrToIntArray(unsigned char *dest, char* src, int count);


/* convert ascii to unsigned char [8] */
void getv(char *s, unsigned char *v, int len)
{
	register int i, t;

	if (s[0] == '0' && s[1] == 'x')
	s += 2; /* Ignore C-style 0x prefix */
	// skip special bytes in hex file.
	for (i = 0; i < len; i++) {
		t = 0;
		if (*s >= '0' && *s <= '9') t = *s++ - '0';
		else if (*s >= 'a' && *s <= 'f') t = *s++ - 'a' + 10;
		else if (*s >= 'A' && *s <= 'F') t = *s++ - 'A' + 10;
		t <<= 4;
		if (*s >= '0' && *s <= '9') t |= *s++ - '0';
		else if (*s >= 'a' && *s <= 'f') t |= *s++ - 'a' + 10;
		else if (*s >= 'A' && *s <= 'F') t |= *s++ - 'A' + 10;
		v[i] = t;
		//if (*s == '.' && i == 3) {
		//	s++;
		//}
	}
}

/* convert unsigned char [8] to unsigned long [2] */
void getl(unsigned char *v, unsigned long *lv)
{
	register int i, j;

	for (i=0, j=0; i < 2; ++i, j+=4)
	{
		lv[i] = v[j] << 24 | v[j+1] << 16 | v[j+2] << 8 | v[j+3];
	}
}

/* convert unsigned long [2] to unsigned char [8] */
void getb(unsigned long *lv, unsigned char *v)
{
	register int i, j;

	for (i = 0, j = 0; i < 2; ++i, j += 4)
	{
		v[j] = lv[i] >> 24;
		v[j + 1] = lv[i] >> 16;
		v[j + 2] = lv[i] >> 8;
		v[j + 3] = lv[i] & 0x000000ff;
	}
}

#define BUF_SIZE		(BLOCK_LEN<<1)	/* Each byte occupies two ASCII characters, eg. 0x12 */
#define KEY_LEN			16
static char aKeyStr[KEY_LEN] = { 0x01, 0x23, 0x45, 0x67, 0x89, 0xAB, 0xCD, 0xEF, 0xF0, 0xE1, 0xD2, 0xC3, 0xB4, 0xA5, 0x96, 0x87 };
//static unsigned char aKeyStr[] = "Real Barca pateontology 21Jan2014";
static unsigned char key[KEY_LEN>>1];
//static unsigned long iv[2] = { 0xFEDCBA98, 0x76543210 };
static unsigned long iv[2] = { 0x10632014, 0x04552201 };

#define BIN_BUF_SIZE		(BLOCK_LEN)		/* Each byte occupies ONE (binary) byte */


// data must be at least BLOCK_LEN in size.
void EncryptBin(unsigned char *data, bool doDecrypt, bool firstOp)
{
	//!!!unsigned char	data[BIN_BUF_SIZE];
	//char*			got = NULL;
	register int	i;
	unsigned long	ldata[2];

	//print_dbg("before getv\r\n");

	// got what we need, ie. a 64-bit block
	// set up key for encryption.
	getv(aKeyStr, key, sizeof(key));
	blf_key(key, sizeof(key));

	//print_dbg("after blf_key\r\n");

	// call encrypt or decrypt function.
	//!!!memcpy(data, src, BIN_BUF_SIZE/*sizeof(data)*/);		// !!! optimise more. No need for this extra copy.
	//getv(aBufPtr, data, sizeof(data));

	//print_dbg("before getl\r\n");

	getl(data, ldata);
	if (doDecrypt == false)
	{
		//print_dbg("doDecrypt == false\r\n");

#if 1		
		blf_enc(ldata, 1);
#else
		if (firstOp)
			blf_cbc_initial_enc(ldata, iv);
		else
			blf_cbc_continue_enc(ldata);
#endif		
		//print_dbg("#\r\n");
	}
	else
	{
		//print_dbg("doDecrypt == true\r\n");

#if 1
		blf_dec(ldata, 1);
#else
		if (firstOp)
			blf_cbc_initial_dec(ldata, iv);
		else
			blf_cbc_continue_dec(ldata);
#endif
		//print_dbg("@\r\n");
	}

	getb(ldata, data);
	//!!!memcpy(src, data, BIN_BUF_SIZE);
}

void testcase1(void)
{
	unsigned char key[] = "AAAAA";
	unsigned long data[10];
	int i;

	print_dbg("\ttestcase1\r\n");

	for (i = 0; i < 10; ++i) data[i] = i;

	blf_key(key, 5);
	blf_enc(data, 5);
	for (i = 0; i < 10; i += 2)
	{
		print_dbg("Block ");
		print_dbg_hex(i/2);
		print_dbg(" encrypts to: 0x");
		print_dbg_hex(data[i]);
		print_dbg(" 0x");
		print_dbg_hex(data[i+1]);
		print_dbg("\r\n");
	}
	blf_dec(data, 1);
	blf_dec(data + 2, 4);
	for (i = 0; i < 10; i += 2)
	{
		print_dbg("Block ");
		print_dbg_hex(i/2);
		print_dbg(" decrypts to: 0x");
		print_dbg_hex(data[i]);
		print_dbg(" 0x");
		print_dbg_hex(data[i+1]);
		print_dbg("\r\n");
	}
}
