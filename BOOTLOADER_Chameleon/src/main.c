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
#include "compiler.h"
#include "preprocessor.h"
#include "board.h"
#include "conf_usb.h"
#include "udd.h"
#include "udc.h"
#include "udi_dfu_atmel.h"
#include "isp.h"
#include "sysclk_auto.h"
#if UC3L3_L4 || UC3D
#include "gpio.h"
#endif

#include "power_clocks_lib.h"
#include "flashc.h"
#include "print_funcs.h"
//va:DF #include "conf_at45dbx.h"
//va:DF #include "at45dbx.h"
#include "boot.h"
#include "string.h"
#include "wdt.h"

#include "HexFile.h"

// !!! *******************************
#include "cycle_counter.h"
#include "gpio.h"
#include "sysclk.h"
//#include "flashexample.h"

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
		print_dbg("LED ON\r\n");
		cpu_delay_ms(1000, sysclk_get_cpu_hz());
	}
	else
	{
		gpio_clr_gpio_pin(LED0_GPIO); // switch off LED0
		is_on_LED0 = false;
		print_dbg("LED OFF\r\n");
		cpu_delay_ms(1000, sysclk_get_cpu_hz());
	}
}
// **********************************

#  define EXAMPLE_TARGET_PBACLK_FREQ_HZ FOSC0  // PBA clock target frequency

/*! \brief Initializes AT45DBX resources: GPIO, SPI and AT45DBX.
 */
static void at45dbx_resources_init(void)
{
  //static const gpio_map_t AT45DBX_SPI_GPIO_MAP =
  //{
    //{AT45DBX_SPI_SCK_PIN,          AT45DBX_SPI_SCK_FUNCTION         },  // SPI Clock.
    //{AT45DBX_SPI_MISO_PIN,         AT45DBX_SPI_MISO_FUNCTION        },  // MISO.
    //{AT45DBX_SPI_MOSI_PIN,         AT45DBX_SPI_MOSI_FUNCTION        },  // MOSI.
//#define AT45DBX_ENABLE_NPCS_PIN(NPCS, unused) \
    //{AT45DBX_SPI_NPCS##NPCS##_PIN, AT45DBX_SPI_NPCS##NPCS##_FUNCTION},  // Chip Select NPCS.
    //MREPEAT(AT45DBX_MEM_CNT, AT45DBX_ENABLE_NPCS_PIN, ~)
//#undef AT45DBX_ENABLE_NPCS_PIN
  //};
//
  //// SPI options.
  //spi_options_t spiOptions =
  //{
    //.reg          = AT45DBX_SPI_FIRST_NPCS,   // Defined in conf_at45dbx.h.
    //.baudrate     = AT45DBX_SPI_MASTER_SPEED, // Defined in conf_at45dbx.h.
    //.bits         = AT45DBX_SPI_BITS,         // Defined in conf_at45dbx.h.
    //.spck_delay   = 0,
    //.trans_delay  = 0,
    //.stay_act     = 1,
    //.spi_mode     = 0,
    //.modfdis      = 1
  //};
//
  //// Assign I/Os to SPI.
  //gpio_enable_module(AT45DBX_SPI_GPIO_MAP,
                     //sizeof(AT45DBX_SPI_GPIO_MAP) / sizeof(AT45DBX_SPI_GPIO_MAP[0]));
//
  //// Initialize as master.
  //spi_initMaster(AT45DBX_SPI, &spiOptions);
//
  //// Set selection mode: variable_ps, pcs_decode, delay.
  //spi_selectionMode(AT45DBX_SPI, 0, 0, 0);
//
  //// Enable SPI.
  //spi_enable(AT45DBX_SPI);
//
  //// Initialize data flash with SPI clock Osc0.
  //at45dbx_init(spiOptions, EXAMPLE_TARGET_PBACLK_FREQ_HZ);
}

#define CONFIG_WORD1_ADDR					0x01fc
#define CONFIG_WORD1_VAL_JUMPTO_BOOTLOADER	0xe11effd7
#define CONFIG_WORD1_VAL_JUMPTO_OP_FW		0xe11efdd9

void JumpToOpFirmwareAfterReset(void)
{
	U32 cWord1 = CONFIG_WORD1_VAL_JUMPTO_OP_FW;
	U32 r_cWord1 = 0;	

	/* read configuration Word1 to view the original value */
	//flashc_memcpy(&r_cWord1, AVR32_FLASHC_USER_PAGE + 0x01fc, 4, false);

	/* set configuration Word 1 to desired value */
	flashc_memset32(AVR32_FLASHC_USER_PAGE + CONFIG_WORD1_ADDR, CONFIG_WORD1_VAL_JUMPTO_OP_FW, 4, true);

	/* verify by reading configuration Word1 */
	r_cWord1 = 0;
	flashc_memcpy(&r_cWord1, AVR32_FLASHC_USER_PAGE + 0x01fc, 4, false);	
	
	if (r_cWord1 != cWord1)
	{
		print_dbg("\twrite Configuration Word failed\r\n");
	}
	else
		print_dbg("\twrite Configuration Word passed\r\n");	
}

// Min value of 1s
#define WDT_MIN_VALUE_US   1000000
// Min value of 4s
#define WDT_MAX_VALUE_US   4000000
// Step of 1s
#define WDT_CTRL_STEP_US   1000000

// To specify which current Watchdog value
volatile U32 current_wdt_value = WDT_MIN_VALUE_US;
// 
wdt_opt_t opt = {
	.dar   = false,     // After a watchdog reset, the WDT will still be enabled.
	.mode  = WDT_BASIC_MODE,    // The WDT is in basic mode, only PSEL time is used.
	.sfv   = false,     // WDT Control Register is not locked.
	.fcd   = false,     // The flash calibration will be redone after a watchdog reset.
	.cssel = WDT_CLOCK_SOURCE_SELECT_RCSYS,       // Select the system RC oscillator (RCSYS) as clock source.
	.us_timeout_period = WDT_MIN_VALUE_US  // Timeout Value
};

void SetupWDT(void)
{
	// If Reset Cause is due to a Watchdog reset.
	if(AVR32_PM.RCAUSE.wdt)
	{
		  print_dbg("\watchdog reset\r\n");
		  
	} // If Reset Cause is due to a Power On reset, enable Watchdog with default value
	else if (AVR32_PM.RCAUSE.por) 
	{
		  print_dbg("\tPower On reset\r\n");
	  
	}
	else if (AVR32_PM.RCAUSE.ext)
	{
		print_dbg("\tExternal reset\r\n");		
		wdt_reenable();
		cpu_delay_ms(300,FOSC0);
	}
	else if (AVR32_PM.RCAUSE.jtag)
		print_dbg("\tJtag reset\r\n");
	else if (AVR32_PM.RCAUSE.awire)
		print_dbg("\tawire reset\r\n");
	else if (AVR32_PM.RCAUSE.jtaghard)
	{
		print_dbg("\tjtaghard reset\r\n");
	}
	else if (AVR32_PM.RCAUSE.awirehard)
		print_dbg("\tawirehard reset\r\n");
	else if (AVR32_PM.RCAUSE.ocdrst)
		print_dbg("\tocd reset\r\n");
	else
		print_dbg("\tOther cause reset\r\n");

#if 1		
		current_wdt_value = WDT_MIN_VALUE_US ;//WDT_MIN_VALUE;
		// Save current value in GPLP register
		pcl_write_gplp(0,current_wdt_value);
		opt.us_timeout_period = current_wdt_value;
		wdt_enable(&opt);	
#endif // 0	
}

#define BIN_DATA_SIZE	190840		// !!! size of binary image to be read, need to read from image header instead.
#define PROGRAM_START_PAGE  (PROGRAM_START_OFFSET / AVR32_FLASHC_PAGE_SIZE)

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
//va:DF	at45dbx_resources_init();
	  	
	// IMPORTANT!!!: note that AVR32_FLASHC_PAGE_SIZE happens to be the same as AT45DBX_SECTOR_SIZE. It may not be true with Adesto chip, need to check.
	// *** copy image from data Flash to MCU Flash.

	print_dbg("---------- Chameleon bootloader started ------------------\r\n");
	
	register int i, j;
#if 0 //va: Not ported yet
	// ** read a page from data Flash into memory.
	U32 position = 1;
	unsigned char rdata[AT45DBX_SECTOR_SIZE];		// data read from external data Flash
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
//va:DF	at45dbx_read_open(aSector+1);

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
//va:DF		at45dbx_read_sector_2_ram(rdata);
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
//va:DF	at45dbx_read_close();

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
#endif //va: Not ported yet	
	
	// ************ Program Configuration Word ********************	
	// *** set Configuration Word 1.
#if 1
	JumpToOpFirmwareAfterReset();
#endif

	// *** write fuse bits
	#define FGPFRLO_VALUE	0xf875ffff
	for (j=0; j<7; j++)
		flashc_write_gp_fuse_byte(j, FGPFRLO_VALUE >> (j<<3));
	
	U8 aFuseByte;
	print_dbg("\tflashc_read_gp_fuse_byte 0x");
	for (j=0; j<7; j++)
	{
		aFuseByte = flashc_read_gp_fuse_byte(j);
		print_dbg_hex(aFuseByte);
		print_dbg(" 0x");
	}	
	print_dbg("\r\n");

	// *** set security bit
#if 0
	print_dbg("\tsetup security bit\r\n");
	flashc_activate_security_bit();
	if (flashc_is_security_bit_active())
		print_dbg("\tsecurity bit is active\r\n");
#endif // 0
	
	// *** set WDT to reset MCU.
	print_dbg("\tsetup WDT\r\n");
	SetupWDT();

	while (true) {
		// !!!
		led0_flash_with_delay();
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
 * - sysclk_auto.c: specific system clock management to support automaticaly
 * detection of external oscillator
 * - intc.c: specific INTC driver optimized to save code
 * - specific linker script to store the bootloader in RAM at address 0x0 instead of 0x2000.
 */


