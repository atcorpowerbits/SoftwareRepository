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

// ENC_DEC_BLOCK_SIZE should not be less than MCU_READ_WRITE_SIZE.
// According to Atmel, writing of 8-bit and 16-bit data to the page buffer of CBP MCU Flash is not allowed and may lead to unpredictable data corruption.
#define ENC_DEC_BLOCK_SIZE		8
#define ENC_DEC_DATA_SIZE		2
#define SIGNATURE_LEN_CBP_IMAGE 8
#define SIGNATURE_CBP_IMAGE		(char*)("Chamleon")
#define SIGNATURE_CBX_IMAGE		(char*)("abpmCBP")

extern unsigned char key[MAXKEYBYTES];
extern unsigned int key_length;

extern void init_enc_dec_with_key(void);
extern bool decrypt(unsigned char *encrypted_data, unsigned char *decrypted_data, const bool first_use_cbc);

#endif /* ENC_DEC_H_ */