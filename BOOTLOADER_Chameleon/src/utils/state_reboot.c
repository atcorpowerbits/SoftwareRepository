/*
 * \file
 *
 * \brief Bootloading reboot state header
 *
 * Copyright (c) Atcor Medical Pty. Ltd., 2014
 *
 * \date Created: 24/03/2014 3:54:54 PM
 * \author victora
 */ 

#include "state_reboot.h"
#include "print_funcs.h"
#include "flashc.h"
#include "wdt.h"
#include "power_clocks_lib.h"
#include "cycle_counter.h"

// Min value of 1s
#define WDT_MIN_VALUE_US   1000000
// Min value of 4s
#define WDT_MAX_VALUE_US   4000000
// Step of 1s
#define WDT_CTRL_STEP_US   1000000
// Fine tuned WDT timeout within 1s for Chameleon
#define WDT_TIMEOUT_VALUE  10000

// To specify current Watchdog timeout
volatile U32 current_wdt_value = WDT_TIMEOUT_VALUE;
//
wdt_opt_t opt = {
	.dar   = false,     // After a watchdog reset, the WDT will still be enabled.
	.mode  = WDT_BASIC_MODE,    // The WDT is in basic mode, only PSEL time is used.
	.sfv   = false,     // WDT Control Register is not locked.
	.fcd   = false,     // The flash calibration will be redone after a watchdog reset.
	.cssel = WDT_CLOCK_SOURCE_SELECT_RCSYS,       // Select the system RC oscillator (RCSYS) as clock source.
	.us_timeout_period = WDT_MIN_VALUE_US  // Timeout Value
};

/**
 * \brief Setup Watchdog to reboot MCU eventually
 */
void SetupWDT(void)
{
	// If Reset Cause is due to a Watchdog reset.
	if(AVR32_PM.RCAUSE.wdt)
	{
		print_dbg("watchdog reset\r\n");
		
	} // If Reset Cause is due to a Power On reset, enable Watchdog with default value
	else if (AVR32_PM.RCAUSE.por)
	{
		print_dbg("Power On reset\r\n");
		
	}
	else if (AVR32_PM.RCAUSE.ext)
	{
		print_dbg("External reset\r\n");
	}
	else if (AVR32_PM.RCAUSE.jtag)
	{
		print_dbg("Jtag reset\r\n");
	}
	else if (AVR32_PM.RCAUSE.awire)
	{
		print_dbg("awire reset\r\n");
	}
	else if (AVR32_PM.RCAUSE.jtaghard)
	{
		print_dbg("jtaghard reset\r\n");
	}
	else if (AVR32_PM.RCAUSE.awirehard)
	{
		print_dbg("awirehard reset\r\n");
	}
	else if (AVR32_PM.RCAUSE.ocdrst)
	{
		print_dbg("ocd reset\r\n");
	}
	else
	{
		print_dbg("other cause reset\r\n");
	}

	// Save current value in GPLP register
	pcl_write_gplp(0,current_wdt_value);
	opt.us_timeout_period = current_wdt_value;
	wdt_enable(&opt);
}

/**
 * \brief Prepare non-IPS reboot by clearing ISP_FORCE bit in User Page configuration word.
 * \return Transition event.
 */
transition_t PrepareNormalReboot (void)
{
	U32 cWord1 = CONFIG_WORD1_VAL_JUMPTO_OP_FW;
	U32 r_cWord1 = 0;
	register int i, j;

	/* read configuration Word1 to view the original value */
	//flashc_memcpy(&r_cWord1, AVR32_FLASHC_USER_PAGE + 0x01fc, 4, false);

	/* set configuration Word 1 to desired value */
	flashc_memset32(AVR32_FLASHC_USER_PAGE + CONFIG_WORD1_ADDR, CONFIG_WORD1_VAL_JUMPTO_OP_FW, 4, true);

	/* verify by reading configuration Word1 */
	r_cWord1 = 0;
	flashc_memcpy(&r_cWord1, AVR32_FLASHC_USER_PAGE + 0x01fc, 4, false);
	
	if (r_cWord1 != cWord1)
	{
		print_dbg("Failed to finish\r\n"); // write Configuration Word failed
		return TRANSITION_REBOOT_PREP_FAILED;
	}
	else
	{
		print_dbg("\r\nFinish "); // write Configuration Word passed
	}
	return TRANSITION_REBOOT;
}

/**
 * \brief Go ahead to reboot now
 * \return Transition event.
 */
transition_t RebootNow (void)
{
	// *** set WDT to reset MCU.
	SetupWDT();
	
	print_dbg("Rebooting soon");
	return TRANSITION_EXIT;
}
