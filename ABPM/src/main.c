/**
 * \file
 *
 * \brief Empty user application template
 *
 */

/*
 * Include header files for all drivers that have been imported from
 * Atmel Software Framework (ASF).
 */
#include <asf.h>
#include "pwa/buffer.h"
#include "usart/usart_rxtx.h"

int main (void)
{
	board_init();
	usart_rs232_mode_init();
	if (!ADCBuffer_init())
	{
		return false;
	}
	
	TestSetRawSignal();
}
