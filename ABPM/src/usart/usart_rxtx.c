/*
 * usart_rxtx.c
 *
 * Created: 10/10/2012 9:32:35 AM
 *  Author: yoonl
 */ 

#include "usart_rxtx.h"
#include <stdio.h>
#include <stdarg.h>

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
}

void print_debug(char *msg, ...)
{
// _DEBUG is set on Debug mode only from Project Properties->Toolchain->AVR32/GNU C Compiler->Symbols
#ifdef _DEBUG
	va_list args;
	char szBuf[1024] = {0};

    va_start(args, msg);
	vsprintf(szBuf, msg, args);
    va_end(args);

    usart_write_line(PBA_USART, szBuf);
#endif
}