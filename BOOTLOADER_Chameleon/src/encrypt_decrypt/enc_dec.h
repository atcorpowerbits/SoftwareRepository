/**
 * \file
 *
 * \brief Encrypt/Decrypt CBP image.
 *
 * Copyright (c) Atcor Medical Pty. Ltd., 2013
 *
 * \date Created: 21/03/2014 11:26:32 AM
 * \author yoonl
 */ 

#ifndef ENC_DEC_H_
#define ENC_DEC_H_

#include <asf.h>
#include "Blowfish.h"

#define ENC_DEC_BLOCK_SIZE		8
#define ENC_DEC_DATA_SIZE		2

extern unsigned char key[MAXKEYBYTES];
extern unsigned int key_length;

extern void init_enc_dec_with_key(void);
extern bool decrypt(const unsigned char *encrypted_data, unsigned char *decrypted_data);

#endif /* ENC_DEC_H_ */