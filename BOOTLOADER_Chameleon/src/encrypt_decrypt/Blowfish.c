/**
 * \file
 *
 * \brief Encrypt/Decrypt CBP image.
 *
 * Copyright (c) Atcor Medical Pty. Ltd., 2013
 *
 * \date Created: 21/03/2014 3:24:53 PM
 * \author yoonl
 */ 

#include "Blowfish.h"
#include "BlowfishData.h"

#define N               16
#define noErr            0
#define DATAERROR         -1
#define KEYBYTES         8

unsigned long P[N + 2];
unsigned long S[4][256];
//FILE*         SubkeyFile;

//short opensubkeyfile(void) /* read only */
//{
//   short error;
//
//   error = noErr;
//
//   if ((fopen_s(&SubkeyFile, subkeyfilename, "rb")) != 0) {
//      error = DATAERROR;
//   }
//
//   return error;
//}

unsigned long F(unsigned long x)
{
	unsigned short a;
	unsigned short b;
	unsigned short c;
	unsigned short d;
	unsigned long  y;

	d = x & 0x00FF;
	x >>= 8;
	c = x & 0x00FF;
	x >>= 8;
	b = x & 0x00FF;
	x >>= 8;
	a = x & 0x00FF;
	//y = ((S[0][a] + S[1][b]) ^ S[2][c]) + S[3][d];
	y = S[0][a] + S[1][b];
	y = y ^ S[2][c];
	y = y + S[3][d];

	return y;
}

void Blowfish_encipher(unsigned long *xl, unsigned long *xr)
{
	unsigned long  Xl;
	unsigned long  Xr;
	unsigned long  temp;
	short          i;

	Xl = *xl;
	Xr = *xr;

	for (i = 0; i < N; ++i) {
		Xl = Xl ^ P[i];
		Xr = F(Xl) ^ Xr;

		temp = Xl;
		Xl = Xr;
		Xr = temp;
	}

	temp = Xl;
	Xl = Xr;
	Xr = temp;

	Xr = Xr ^ P[N];
	Xl = Xl ^ P[N + 1];
	
	*xl = Xl;
	*xr = Xr;
}

void Blowfish_decipher(unsigned long *xl, unsigned long *xr)
{
	unsigned long  Xl;
	unsigned long  Xr;
	unsigned long  temp;
	short          i;

	Xl = *xl;
	Xr = *xr;

	for (i = N + 1; i > 1; --i) {
		Xl = Xl ^ P[i];
		Xr = F(Xl) ^ Xr;

		/* Exchange Xl and Xr */
		temp = Xl;
		Xl = Xr;
		Xr = temp;
	}

	/* Exchange Xl and Xr */
	temp = Xl;
	Xl = Xr;
	Xr = temp;

	Xr = Xr ^ P[1];
	Xl = Xl ^ P[0];

	*xl = Xl;
	*xr = Xr;
}

short InitializeBlowfish(unsigned char key[], short keybytes)
{
	short          i;
	short          j;
	short          k;
	short          error=noErr;
	short          numread;
	unsigned long  data;
	unsigned long  datal;
	unsigned long  datar;

	/* First, open the file containing the array initialization data */
	//  error = opensubkeyfile();
	//  if (error == noErr) {
	//for (i = 0; i < N + 2; ++i) {
	//	numread = fread(&data, 4, 1, SubkeyFile);
	//	#ifdef little_endian      /* Eg: Intel   We want to process things in byte   */
	//			   /*   order, not as rearranged in a longword          */
	//	 data = ((data & 0xFF000000) >> 24) |
	//		((data & 0x00FF0000) >>  8) |
	//		((data & 0x0000FF00) <<  8) |
	//		((data & 0x000000FF) << 24);
	//   #endif

	//	 if (numread != 1) {
	//		return DATAERROR;
	//	 } else {
	//		P[i] = data;
	//	 }
	//   }

	//  for (i = 0; i < 4; ++i) {
	//for (j = 0; j < 256; ++j) {
	//	numread = fread(&data, 4, 1, SubkeyFile);

	//	#ifdef little_endian    /* Eg: Intel   We want to process things in byte   */
	//							/*   order, not as rearranged in a longword          */
	//		data = ((data & 0xFF000000) >> 24) |
	//			((data & 0x00FF0000) >>  8) |
	//			((data & 0x0000FF00) <<  8) |
	//			((data & 0x000000FF) << 24);
	//	#endif

	//	if (numread != 1) {
	//		return DATAERROR;
	//	} else {
	//		S[i][j] = data;
	//	}
	//}
	//  }

	//    fclose(SubkeyFile);

	for (i = 0; i < N + 2; ++i)
	P[i] = parray[i];

	for (j = 0; j < 256; ++j)
	{
		S[0][j] = sbox0[j];
		S[1][j] = sbox1[j];
		S[2][j] = sbox2[j];
		S[3][j] = sbox3[j];
	}

	j = 0;
	for (i = 0; i < N + 2; ++i) {
		data = 0x00000000;
		for (k = 0; k < 4; ++k) {
			data = (data << 8) | key[j];
			j = j + 1;
			if (j >= keybytes) {
				j = 0;
			}
		}
		P[i] = P[i] ^ data;
	}

	datal = 0x00000000;
	datar = 0x00000000;

	for (i = 0; i < N + 2; i += 2) {
		Blowfish_encipher(&datal, &datar);

		P[i] = datal;
		P[i + 1] = datar;
	}

	for (i = 0; i < 4; ++i) {
		for (j = 0; j < 256; j += 2) {

			Blowfish_encipher(&datal, &datar);
			
			S[i][j] = datal;
			S[i][j + 1] = datar;
		}
	}
	//} else {
	//   printf("Unable to open subkey initialization file : %d\n", error);
	//}

	return error;
}

void blf_key(unsigned char* k, int len)
{
	InitializeBlowfish(k, len);
}

void blf_enc(unsigned long *data, int blocks)
{
	unsigned long *d;
	register int i;

	d = data;
	for (i = 0; i < blocks; i++)
	{
		Blowfish_encipher(d, d + 1);
		d += 2;
	}
}

void blf_dec(unsigned long *data, int blocks)
{
	unsigned long *d;
	register int i;

	d = data;
	for (i = 0; i < blocks; i++)
	{
		Blowfish_decipher(d, d + 1);
		d += 2;
	}
}

/* cipher block chaining (CBC) mode encryption */
void blf_chain_enc(unsigned long *data, int blocks, unsigned long *iv)
{
	unsigned long *d;
	int i;
	unsigned long *s0, *s1;

	d = data;
	*d ^= *iv;
	*(d+1) ^= *(iv+1);
	for (i = 0; i < blocks; ++i)
	{
		Blowfish_encipher(d, d + 1);
		s0 = d;
		s1 = d + 1;
		d += 2;
		if (i < blocks - 1)
		{
			*d ^= *s0;
			*(d + 1) ^= *s1;
		}
	}
}

static unsigned long s0, s1;

void blf_cbc_initial_enc(unsigned long *data, unsigned long *iv)
{
	unsigned long *d;

	d = data;
	*d ^= *iv;
	*(d + 1) ^= *(iv + 1);
	Blowfish_encipher(d, d + 1);
	s0 = *d;
	s1 = *(d + 1);
}

void blf_cbc_continue_enc(unsigned long *data)
{
	unsigned long *d;
	register int i;

	d = data;
	*d ^= s0;
	*(d + 1) ^= s1;
	Blowfish_encipher(d, d + 1);
	s0 = *d;
	s1 = *(d + 1);
}

/* cipher block chaining (CBC) mode decryption */
void blf_chain_dec(unsigned long *data, int blocks, unsigned long *iv)
{
	unsigned long *d;
	int i;
	unsigned long prev_c0, prev_c1;
	unsigned long c0, c1;

	d = data;
	prev_c0 = *iv;
	prev_c1 = *(iv + 1);
	c0 = *d;
	c1 = *(d + 1);
	
	for (i = 0; i < blocks; ++i)
	{
		Blowfish_decipher(d, d + 1);
		*d ^= prev_c0;
		*(d + 1) ^= prev_c1;
		
		prev_c0 = c0;
		prev_c1 = c1;
		
		d += 2;

		c0 = *d;
		c1 = *(d + 1);
	}
}

static unsigned long prev_c0, prev_c1;
static unsigned long c0, c1;

void blf_cbc_initial_dec(unsigned long *data, unsigned long *iv)
{
	unsigned long *d;
	register int i;

	d = data;
	prev_c0 = *iv;
	prev_c1 = *(iv + 1);
	c0 = *d;
	c1 = *(d + 1);

	Blowfish_decipher(d, d + 1);
	*d ^= prev_c0;
	*(d + 1) ^= prev_c1;

	prev_c0 = c0;
	prev_c1 = c1;
}

void blf_cbc_continue_dec(unsigned long *data)
{
	unsigned long *d;
	register int i;

	d = data;
	c0 = *d;
	c1 = *(d + 1);

	Blowfish_decipher(d, d + 1);
	*d ^= prev_c0;
	*(d + 1) ^= prev_c1;

	prev_c0 = c0;
	prev_c1 = c1;
}

/* Blowfish: convert unsigned char [8] to unsigned long [2] */
void getl(unsigned char *v, unsigned long *lv)
{
	register int i, j;

	for (i=0, j=0; i < 2; ++i, j+=4)
	{
		lv[i] = v[j] << 24 | v[j+1] << 16 | v[j+2] << 8 | v[j+3];
	}
}

/* Blowfish: convert unsigned long [2] to unsigned char [8] */
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
