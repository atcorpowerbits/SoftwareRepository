/*
 * Blowfish.h
 *
 * Created: 19/02/2014 4:44:18 PM
 *  Author: lawrencec
 */ 


#ifndef BLOWFISH_H_
#define BLOWFISH_H_

#define MAXKEYBYTES 56          /* 448 bits */
#define little_endian 1              /* Eg: Intel */
//#define big_endian 1            /* Eg: Motorola */

short opensubkeyfile(void);
unsigned long F(unsigned long x);
void Blowfish_encipher(unsigned long *xl, unsigned long *xr);
void Blowfish_decipher(unsigned long *xl, unsigned long *xr);
short InitializeBlowfish(unsigned char key[], short keybytes);

void blf_key(unsigned char* k, int len);
void blf_enc(unsigned long *data, int blocks);
void blf_dec(unsigned long *data, int blocks);

void blf_chain_enc(unsigned long *data, int blocks, unsigned long *iv);
void blf_chain_dec(unsigned long *data, int blocks, unsigned long *iv);

void blf_cbc_initial_enc(unsigned long *data, unsigned long *iv);
void blf_cbc_continue_enc(unsigned long *data);

void blf_cbc_initial_dec(unsigned long *data, unsigned long *iv);
void blf_cbc_continue_dec(unsigned long *data);

#endif /* BLOWFISH_H_ */