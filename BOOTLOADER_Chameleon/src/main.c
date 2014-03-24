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

//PORT: #define BIN_DATA_SIZE	190840		// !!! size of binary image to be read, need to read from image header instead.
//PORT: #define PROGRAM_START_PAGE  (PROGRAM_START_OFFSET / AVR32_FLASHC_PAGE_SIZE)

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
	
#if 0 //Port: Not ported yet
	// ** read a page from data Flash into memory.
	U32 position = 1;
	unsigned char rdata[DF_PAGE_SIZE];		// data read from external data Flash
	//unsigned char *c = rdata;
	register int nRead = BIN_DATA_SIZE;				// actual size of binary image to be read
	volatile U64 *flash_ptr;
	S32 mcuPos = 0;
	
	// ************ Erase and verify ********************		
	// erase relevant MCU Flash sectors.
	for (i = flashc_get_page_region(PROGRAM_START_PAGE); i < AVR32_FLASHC_REGIONS; i++)
	{
		flashc_lock_region(i, false);
		if (flashc_is_region_locked(i))
		{	// erase and verify failed.
			print_dbg("\tflashc_is_region_locked failed i=0x");
			print_dbg_hex(i);
			print_dbg("\r\n");
			return;
		}
	}
	for (i = flashc_get_page_count() - 1; i >= PROGRAM_START_PAGE; i--)
	{
		if (!flashc_erase_page(i, true))
		{	// erase and verify failed.
			print_dbg("\tflashc_erase_page failed i=0x");
			print_dbg_hex(i);
			print_dbg("\r\n");
			return;
		}
	}
	
	print_dbg("\terase and verify passed\r\n");
	
	// ************ Program and verify ********************
	// go to the relevant position in external Flash.
	unsigned short sectorOffset = 0;
	U32 aSector;
	register int totReadSector;
	unsigned short copySize;
	
	position = PROGRAM_START_OFFSET; // 0x2000, 0x4000?
	aSector = position / AT45DBX_SECTOR_SIZE;
//Port:DF	at45dbx_read_open(aSector+1);

	print_dbg("\tprogram start offset 0x");
	print_dbg_hex(position);
	print_dbg("\r\n");

	if ( position < AT45DBX_SECTOR_SIZE )
		sectorOffset = position;
	else
		sectorOffset = position - aSector * AT45DBX_SECTOR_SIZE;
	totReadSector = 0;
	i = nRead - position;				// we are not reading the whole binary image, only read from program start offset.

	print_dbg("\tbefore do-while loop i=0x");
	print_dbg_hex(i);
	print_dbg(" nRead=0x");
	print_dbg_hex(nRead);
	print_dbg("\r\n");

	// !!! can be removed - test decryption algorithm.
	//testcase1();
	
	bool firstOp = true;
	do
	{
//Port:DF		at45dbx_read_sector_2_ram(rdata);
		//c = rdata + sectorOffset;			
		copySize = ( i < AT45DBX_SECTOR_SIZE ) ? i : AT45DBX_SECTOR_SIZE;
		copySize -= sectorOffset;
		
#if 1 // decrypt binary image
		for (j=0; j<copySize; j+=BLOCK_LEN)
		{
			if ( firstOp ) // first time calling EncryptBin()
			{
				firstOp = false;
				EncryptBin(&rdata[j], true, true);
			}
			else
				EncryptBin(&rdata[j], true, false);
		}				
#endif // 1
		// write rdata to MCU Flash
		flash_ptr = (U64 *)(PROGRAM_START_ADDRESS + mcuPos);
		
		flashc_clear_page_buffer();
		for (j = 0; j < copySize / sizeof(*flash_ptr); j++)		// AVR32_FLASHC_PAGE_SIZE
			flash_ptr[j] = ((U64 *)rdata)[j];
		flashc_write_page(-1);
		if (memcmp((void *)flash_ptr, rdata, copySize))			// AVR32_FLASHC_PAGE_SIZE
		{	// verify failed
			print_dbg("\tmemcmp failed\r\n");
			break;
		}
		
		mcuPos += copySize;
		nRead -= copySize;

		i -= copySize;		
		++totReadSector;
		sectorOffset = 0;
		
		print_dbg(".");
	} while ( i > 0 );
//Port:DF	at45dbx_read_close();

	if ( i > 0 )
	{	// !!! print debug info
		print_dbg("\ti=");
		print_dbg_hex(i);
		print_dbg("\r\n");
		print_dbg("\tprogram and verify failed\r\n");
	}
	else
	{
		print_dbg("\ti=0 totReadSector=0x");
		print_dbg_hex(totReadSector);
		print_dbg("\r\n");
		print_dbg("\tprogram and verify passed\r\n");
	}
		
	// *** Check the MCU Flash image matches the data Flash, can use a CRC
	// !!!
	print_dbg("\tchk MCU Flash image ");
	unsigned char *chkPtr = 0x80004000;
	print_dbg_hex(*chkPtr);
	print_dbg(" ");
	print_dbg_hex(*(chkPtr+1));
	print_dbg(" ");
	print_dbg_hex(*(chkPtr+2));
	print_dbg(" ");
	print_dbg_hex(*(chkPtr+BIN_DATA_SIZE-2));
	print_dbg(" ");
	print_dbg_hex(*(chkPtr+BIN_DATA_SIZE-1));
	print_dbg("\r\n");
#endif //Port: Not ported yet	
	
	while (true) {
		led0_flash_with_delay();
	}
}
