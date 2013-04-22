/*
 * buffer.c
 *
 * Add sample to adc_buffer
 *
 * Copyright (c) Atcor Medical Pty. Ltd., 2013
 *
 * Created: 9/10/2012 2:27:16 PM
 *  Author: yoonl
 */ 

#include "buffer.h"
#include "usart/usart_rxtx.h"
#include "pwa_data.h"

static uint16_t buf_index = 0; // adc_buffer buffer index

/* ###########################################################################
 ** ADCBuffer_init()
 **
 ** DESCRIPTION
 **  Allocate memory, initailise adc_buffer properties
 ** INPUT
 ** OUTPUT
 ** RETURN
 **  boolean - return false if out of memory.
*/
bool ADCBuffer_init(void)
{
	buf_index = 0;
	if (adc_buffer == NULL)
	{
		adc_buffer = (uint16_t*)malloc(sizeof(uint16_t)*ADC_BUF_SIZE);
		if (adc_buffer == NULL)
		{
			return false;
		}
	}		
	memset((void*)adc_buffer, 0, sizeof(adc_buffer[0])*ADC_BUF_SIZE);
	return true;
}

/* ###########################################################################
 ** AddSignal()
 **
 ** DESCRIPTION
 **  Add each digital unit into adc_buffer
 ** INPUT
 **  signal - each sample
 ** OUTPUT
 ** RETURN
*/
void AddSignal(uint16_t signal)
{
	if (adc_buffer == NULL)
	{
		PWA_Error_Code = PWA_MSG_OUT_OF_MEMORY;
		print_debug("Error(%d): AddSignal() - adc_buffer is null.\r\n", PWA_Error_Code);
		return;
	}
	
	if (buf_index < ADC_BUF_SIZE)
	{
		adc_buffer[buf_index] = signal;
		++buf_index;
	}
}

/* ###########################################################################
 ** IsADCBufferFull()
 **
 ** DESCRIPTION
 **  Check adc_buffer is full or not
 ** INPUT
 ** OUTPUT
 ** RETURN
 **  boolean - return true if adc_buffer is full.
*/
bool IsADCBufferFull(void)
{
	return (buf_index > ADC_BUF_SIZE-1);
}

/* ###########################################################################
 ** ADCBuffer_final()
 **
 ** DESCRIPTION
 **  Free adc_buffer properties
 ** INPUT
 ** OUTPUT
 ** RETURN
*/
void ADCBuffer_final(void)
{
	if (adc_buffer != NULL)
	{
		free((void*)adc_buffer);
		adc_buffer = NULL;
	}
}
