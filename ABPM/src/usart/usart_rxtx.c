/*
 * usart_rxtx.c
 *
 * Created: 10/10/2012 9:32:35 AM
 *  Author: yoonl
 */ 

#include "usart_rxtx.h"
#include "sysclk.h"
#include "cycle_counter.h"
#include <stdio.h>
#include <stdarg.h>
#include <string.h>

void usart_rs232_mode_init(void)
{
	// Configure Osc0 in crystal mode (i.e. use of an external crystal source, with
	// frequency FOSC0) with an appropriate startup time then switch the main clock
	// source to Osc0.
	pcl_switch_to_osc(PCL_OSC0, FOSC0, OSC0_STARTUP);
	
	// Assign GPIO to USART.
	gpio_enable_module(USART_GPIO_MAP, sizeof(USART_GPIO_MAP) / sizeof(USART_GPIO_MAP[0]));

	// Initialize USART in RS232 mode.
	usart_init_rs232(PBA_USART, &USART_OPTIONS, PBA_TARGET_PBACLK_FREQ_HZ);
	usart_init_rs232(CMD_USART, &CMD_USART_OPTIONS, CMD_USART_PBx_FREQ_HZ); // for BP-CBP command/response serial comms
}

void print_debug(char *msg, ...)
{
// _DEBUG is set on Debug mode only from Project Properties->Toolchain->AVR32/GNU C Compiler->Symbols
#ifdef _DEBUG
	va_list args;
	char szBuf[1024] = {0};
	unsigned long current_cycle_count = Get_system_register(AVR32_COUNT);
	uint32_t elapsed = cpu_cy_2_ms(current_cycle_count, sysclk_get_cpu_hz()); // in msec
	uint16_t elapsed_min = elapsed / (1000*60);
	float elapsed_sec = (float)(elapsed - (elapsed_min * 60 * 1000)) / 1000;
	
	// Print elapsed time in mm:ss.sss
	sprintf(szBuf, "%02u:%02.3f ", elapsed_min, elapsed_sec);
    usart_write_line(PBA_USART, szBuf);
	
    va_start(args, msg);
	vsprintf(szBuf, msg, args);
    va_end(args);

    usart_write_line(PBA_USART, szBuf);
#endif
}

/**
 * \brief Transmit the response packet to BP
 * \param[in] response Response packet to be transmitted
 * \param[in] len Length of the response packet
 */
void transmit_response (uint8_t* response, int len)
{
#ifdef _DEBUG
	char debug_buffer[1024] = {0};
	char hex_byte[5] = {0};
		
	// Dump the packet to be transmitted for debugging
	for (int i = 0; i < len; i++)
	{
		sprintf(hex_byte, " %02X", response[i]);
		strcat(debug_buffer, hex_byte);
	}
	print_debug("Transmitting:%s\n", debug_buffer);
#endif
	// Transmit the packet to BP out of the designated port
	// <TBD> Trying to send directly via USART driver; could be better via PDCA (DMA)
	while (len--)
	{
		usart_putchar(CMD_USART, *response++);
	}
}