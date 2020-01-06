/**
 * \file
 *
 * \brief Encrypt/Decrypt CBP image.
 *
 * Copyright (c) Atcor Medical Pty. Ltd., 2013
 *
 * \date Created: 21/03/2014 11:28:36 AM
 * \author yoonl
 */ 

#include <string.h>
#include "enc_dec.h"

#define KEY_STRING		(char*)("yLDRI7DgXH5pjTNp6iCltQ44564RFiD05b9UEng0wcyx2RvRn0dR5tPZ")

unsigned char key[MAXKEYBYTES] = {0};
unsigned int key_length = 0;

/**
 * \brief Initialize Encrypt/Decrypt required arrays with key.
 */
void init_enc_dec_with_key(void)
{
	// Prepare key and length.
	key_length = strlen(KEY_STRING);
	if (key_length > MAXKEYBYTES)
	{
		key_length = MAXKEYBYTES;
	}
	memset(key, 0, MAXKEYBYTES);
	memcpy(key, KEY_STRING, key_length);
	
	// Initialize four s_boxes and one p_array in Blowfish.
	blf_key(key, key_length);
}

/**
 * \brief Decrypt encrypted data by ENC_DEC_BLOCK_SIZE.
 * \return boolean successful or not.
 */
bool decrypt(unsigned char *encrypted_data, unsigned char *decrypted_data, const bool first_use_cbc)
{
	unsigned long ldata[ENC_DEC_DATA_SIZE];
	
	if (!encrypted_data || !decrypted_data)
	{
		return false;
	}
	
	memset(ldata, 0, ENC_DEC_DATA_SIZE);
	getl(encrypted_data, ldata);
	if (first_use_cbc)
	{
		blf_cbc_initial_dec(ldata, iv);
	}
	else
	{
		blf_cbc_continue_dec(ldata);
	}
	getb(ldata, decrypted_data);
	
	return true;
}