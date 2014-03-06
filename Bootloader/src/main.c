/**
 * \file
 *
 * \brief Main functions
 *
 * Copyright (c) 2011-2012 Atmel Corporation. All rights reserved.
 *
 * \asf_license_start
 *
 * \page License
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * 3. The name of Atmel may not be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * 4. This software may only be redistributed and used in connection with an
 *    Atmel microcontroller product.
 *
 * THIS SOFTWARE IS PROVIDED BY ATMEL "AS IS" AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT ARE
 * EXPRESSLY AND SPECIFICALLY DISCLAIMED. IN NO EVENT SHALL ATMEL BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 * ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 * \asf_license_stop
 *
 */

#include <asf.h>
#include "print_funcs.h"
#include "states.h"

/*! \brief Main function. Execution starts here.
 */
int main(void)
{
	cpu_irq_enable();

	// Switch main clock to external oscillator 0 (crystal).
	pcl_switch_to_osc(PCL_OSC0, FOSC0, OSC0_STARTUP);
	
	// Initialize the debug USART module.
	init_dbg_rs232(FOSC0);

	// Check the new downloaded CBP Image in DataFlash
	CheckDownloadedImage();

	// Decrypt and Program the new CBP Image in MCU Flash
	DecryptAndProgramImage();
	
	// Prepare for normal, i.e. non-ISP reboot
	PrepareNormalReboot();
	
	// Reboot to start the new CBP Image
	RebootNow();

	while (true) {
		gpio_tgl_gpio_pin(AVR32_PIN_PA02);
		delay_s(1);
	}
}

/**
 * \mainpage ASF USB Device DFU
 *
 * \section intro Introduction
 * This application is the official Atmel USB DFU bootloader for the UC3 devices.
 *
 * The guide of this bootloader is proposed in the following application note
 * "AVR32806-AVR UC3 USB DFU Bootloader version 1.1.0 and higher".
 *
 * \section files Application Files
 * The specific files of application are:
 * - main.c: the main file to start clock and USB DFU Device.
 * - sysclk_auto.c: specific system clock management to support automatically
 * detection of external oscillator
 * - intc.c: specific INTC driver optimized to save code
 * - specific linker script to store the bootloader in RAM at address 0x0 instead of 0x2000.
 */


