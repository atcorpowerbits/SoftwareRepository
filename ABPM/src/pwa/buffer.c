/*
 * buffer.c
 *
 * Created: 9/10/2012 2:27:16 PM
 *  Author: yoonl
 */ 

#include "buffer.h"
#include "usart/usart_rxtx.h"


uint16_t buf_index; // Circular buffer index

/* ###########################################################################
 ** ADCBuffer_init()
 **
 ** DESCRIPTION
 **  Allocate memory, initailise adc_buffer properties
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
	memset(adc_buffer, 0, sizeof(adc_buffer[0])*ADC_BUF_SIZE);
	return true;
}

/* ###########################################################################
 ** AddSignal()
 **
 ** DESCRIPTION
 **  Add each digital unit into adc_buffer
*/
void AddSignal(uint16_t signal)
{
	if (adc_buffer == NULL)
	{
		print_debug("Info: AddSignal() - adc_buffer is NULL.\r\n");
		return;
	}
	
	if (signal < 0)
	{
		signal = 0;
	}

	if (buf_index > ADC_BUF_SIZE-1) // buffer is full
	{
		// shift to left and put a new signal into the last array element to make circular adc_buffer.
		memmove(&adc_buffer[0], &adc_buffer[1], (sizeof(adc_buffer[0])*ADC_BUF_SIZE) - sizeof(adc_buffer[0]));
		adc_buffer[ADC_BUF_SIZE-1] = signal;
	}
	else
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
*/
void ADCBuffer_final(void)
{
	if (adc_buffer != NULL)
	{
		free(adc_buffer);
		adc_buffer = NULL;
	}
}
