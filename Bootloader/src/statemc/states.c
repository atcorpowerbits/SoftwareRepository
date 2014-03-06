/*
 * \file
 *
 * \brief Bootloading state machine 
 *
 * Copyright (c) Atcor Medical Pty. Ltd., 2014
 *
 * \date Created: 28/02/2014 12:11:51 PM
 * \author victora
 */ 

#include <compiler.h>
#include "print_funcs.h"

// Check the new downloaded CBP Image in DataFlash
int8_t CheckDownloadedImage (void)
{
	//df_error_code_t df_status;
	//int32_t len;
	//int32_t crc32;
	//
	//df_status = DFReadInt32(LEN_OFFSET, &len);
	//if (DF_RW_SUCCESS == df_status)
	//{
		//df_status = DFReadInt32(CRC_OFFSET, &crc32);
	//}
	//if (DF_RW_SUCCESS == df_status)
	//{
		//df_status = CheckCRC(ENCRYPTED_IMAGE_OFFSET, len);
	//}
	return 0;
}

// Decrypt and Program the new CBP Image in MCU
int8_t DecryptAndProgramImage (void)
{
	return 0;
}

// Prepare for noraml reboot
void PrepareNormalReboot (void)
{
	return 0;
}

// Reboot now
void RebootNow (void)
{
	print_dbg("Reboot now...\r\n");
}

// Bootloading error
void BootloadingError (void)
{
	// TBD
}
