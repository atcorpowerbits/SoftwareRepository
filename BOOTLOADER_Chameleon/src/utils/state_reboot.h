/*
 * \file
 *
 * \brief Bootloading reboot state header
 *
 * Copyright (c) Atcor Medical Pty. Ltd., 2014
 *
 * \date Created: 24/03/2014 3:55:50 PM
 * \author victora
 */ 


#ifndef STATE_REBOOT_H_
#define STATE_REBOOT_H_

#include "states.h"

#define CONFIG_WORD1_ADDR					0x01fc
#define CONFIG_WORD1_VAL_JUMPTO_BOOTLOADER	0xe11effd7 // Enable ISP_FORCE without testing ISP_IO_COND_EN
#define CONFIG_WORD1_VAL_JUMPTO_OP_FW		0xe11efcde // Disable ISP_FORCE without ISP_IO_COND_EN flag to eliminate any remote chance of starting ISP due to spurious GPIO pin

// Prepare for normal reboot
transition_t PrepareNormalReboot (void);

// Go ahead to reboot now
transition_t RebootNow (void);

void SetupWDT (void);

#endif /* STATE_REBOOT_H_ */