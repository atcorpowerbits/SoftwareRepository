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
#include "pwa/buffer.h"
#include "pwa/pwa.h"
#include "usart/usart_rxtx.h"

int main (void)
{
	board_init();
	usart_rs232_mode_init();
	
	print_debug("Start main().\r\n");
	Finalise();
	if (!ADCBuffer_init())
	{
		PWA_Error_Code = PWA_MSG_OUT_OF_MEMORY;
		print_debug("Error(%d): failed to allocate memory adc_buffer.\r\n", PWA_Error_Code);
		return false;
	}
	TestSetRawSignal();
	
	while (1)
	{
		// Intentionally left empty.
	};
}
