/**
 * \file
 *
 * \brief Main functions
 *
 * Copyright (c) 2011 Atmel Corporation. All rights reserved.
 *
 * \asf_license_start
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
#include "board.h"
#include "print_funcs.h"

// !!! *******************************
#include "gpio.h"
#include "sysclk.h"
#include "states.h"
#include "dataflash_if.h"

static bool is_on_LED0 = false;

void led_task_init(void)
{
	// do nothing
}

void led0_flash_with_delay(void)
{
	if (!is_on_LED0)
	{
		gpio_set_gpio_pin(LED0_GPIO); // Let's switch on LED0
		is_on_LED0 = true;
		print_dbg_char('!');
		cpu_delay_ms(20, sysclk_get_cpu_hz());
	}
	else
	{
		gpio_clr_gpio_pin(LED0_GPIO); // switch off LED0
		is_on_LED0 = false;
		print_dbg_char('.');
		cpu_delay_ms(480, sysclk_get_cpu_hz());
	}
}
// **********************************

/*! \brief Main function. Execution starts here.
 */
int main(void)
{
	board_init();

	// Switch main clock to external oscillator 0 (crystal).
	pcl_switch_to_osc(PCL_OSC0, FOSC0, OSC0_STARTUP);
	
	// Initialize the debug USART module.
	init_dbg_rs232(FOSC0);

	// Initialize AT45DBX resources: GPIO, SPI and AT45DBX.
	df_interface_init();
	  	
	print_dbg("\r\n---------- Chameleon bootloader started ------------------\r\n");
	
	// We are here because ISP was in force
	DoISP(TRANSITION_ISP_FORCED);
	
	while (true) {
		led0_flash_with_delay();
	}
}
