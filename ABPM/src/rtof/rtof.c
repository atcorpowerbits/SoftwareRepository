/*
 * rtof.c
 *
 * Created: 10/10/2012 4:17:30 PM
 *  Author: yoonl
 */ 

#include "rtof.h"
#include "usart/usart_rxtx.h"
#include "pwa/pwa.h"
#include "pwa/buffer.h"

void rtof_add_calculate(uint16_t pressure_sample)
{
}

void TestCallPWA(void)
{
	if (!CalculateBrachial())
	{
		Finalise();
		print_debug("Error: failed CalculateBrachial().\r\n");
		return;
	}
	
	if (!CalculateRadial(0))
	{
		Finalise();
		print_debug("Error: failed CalculateRadial().\r\n");
		return;
	}
}