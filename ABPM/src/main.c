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
#include "pwa/pwa.h"
#include "usart/usart_rxtx.h"

int main (void)
{
	board_init();
	usart_rs232_mode_init();
	
	Finalise();
	if (!ADCBuffer_init())
	{
		print_debug("Error: failed to allocate memory adc_buffer.\r\n");
		return false;
	}
	
	TestSetRawSignal();
	
	while (1)
	{
		// Intentionally left empty.
	};
}
