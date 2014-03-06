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
#include <asf.h>
#include "debug.h"

#define CONFIG_WORD1_OFFSET					0x01fc
#define CONFIG_WORD1_VAL_JUMPTO_OP_FW		0xe11efdd9

#define WATCHDOG_TIMEOUT   1000000 // in usec

wdt_opt_t watchdog_opt = {
	.dar   = false,     // After a watchdog reset, the WDT will still be enabled.
	.mode  = WDT_BASIC_MODE,    // The WDT is in basic mode, only PSEL time is used.
	.sfv   = false,     // WDT Control Register is not locked.
	.fcd   = false,     // The flash calibration will be redone after a watchdog reset.
	.cssel = WDT_CLOCK_SOURCE_SELECT_RCSYS,       // Select the system RC oscillator (RCSYS) as clock source.
	.us_timeout_period = WATCHDOG_TIMEOUT  // Timeout Value
};

// Bootloading error
void BootloadingError (void)
{
	while (true) {
		gpio_tgl_gpio_pin(AVR32_PIN_PA02);
		delay_ms(50);
	}
}

// Check the new downloaded CBP Image in DataFlash
int8_t CheckDownloadedImage (void)
{
	debug_msg("Checking downloaded image\r\n");

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
	debug_msg("Decrypting image\r\n");

	return 0;
}

// Prepare for noraml reboot
void PrepareNormalReboot (void)
{
	U32 cWord1 = CONFIG_WORD1_VAL_JUMPTO_OP_FW;
	U32 r_cWord1 = 0;

	debug_msg("Preparing to reboot\r\n");

	/* write Configuration Word 1 to reboot operational firmware */
	flashc_memset32(AVR32_FLASHC_USER_PAGE + CONFIG_WORD1_OFFSET, CONFIG_WORD1_VAL_JUMPTO_OP_FW, 4, true);

	/* verify by reading Configuration Word 1 again after writing */
	r_cWord1 = 0;
	flashc_memcpy(&r_cWord1, AVR32_FLASHC_USER_PAGE + CONFIG_WORD1_OFFSET, 4, false);
	
	if (r_cWord1 != cWord1)
	{
		debug_msg("??? Failed to prepare for normal reboot\r\n");
		BootloadingError();
	}
	else
	{
		debug_msg("Ready for normal reboot\r\n");
	}
}

// Reboot now
void RebootNow (void)
{
	debug_msg("Rebooting now...\r\n");

	// Save watchdog timeout value in GPLP register
	pcl_write_gplp(0, WATCHDOG_TIMEOUT);

	// Enable the watchdog to reset MCU
	wdt_enable(&watchdog_opt);
}
