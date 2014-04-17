/**
 * \file
 *
 * \brief Encrypt/Decrypt CBP image.
 *
 * Copyright (c) Atcor Medical Pty. Ltd., 2013
 *
 * \date Created: 21/03/2014 3:23:38 PM
 * \author yoonl
 */ 

#ifndef BLOWFISH_H_
#define BLOWFISH_H_

#define MAXKEYBYTES 56          /* 448 bits */
#define little_endian 1              /* Eg: Intel */
#define INITIALIZATION_VECTOR_SIZE	2

// The cipher-block chaining (CBC) mode requires typical random initialization vector (IV).
extern unsigned long iv[INITIALIZATION_VECTOR_SIZE];

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

void getl(unsigned char *v, unsigned long *lv);
void getb(unsigned long *lv, unsigned char *v);

#endif /* BLOWFISH_H_ */