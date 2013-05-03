/**
 * main.c
 *
 * main method
 *
 * Copyright (c) Atcor Medical Pty. Ltd., 2013
 *
 * Created: 10/10/2012 11:29:02 AM
 *  Author: yoonl
 */

/*
 * Include header files for all drivers that have been imported from
 * Atmel Software Framework (ASF).
 */
#include <asf.h>
#include "usart/usart_rxtx.h"
#include "command-response/listener.h"
#include "command-response/sender.h"
#include "pwa/pwa.h"

int main (void)
{
	board_init();
	usart_rs232_mode_init();
	listener_init();
	sender_init();
	
	print_debug("Start main().\r\n");

	while (1)
	{
		// Listen to any command for CBP
		listener_task();

		// Send any CBP response to BP
		sender_task();
		
		// Do PWA calculation when requested
		pwa_calculation_task();	
	};
}
