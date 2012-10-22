/*
 * buffer.h
 *
 * Created: 9/10/2012 1:47:21 PM
 *  Author: yoonl
 */ 


#ifndef BUFFER_H_
#define BUFFER_H_

#include "dsp.h"

#define ADC_BUF_SIZE	(uint16_t)1280 //DEFAULT_SAMPLE_RATE*PWA_MAX_CAPTURE_TIME

uint16_t *adc_buffer; // Circular buffer

bool ADCBuffer_init(void);
void AddSignal(uint16_t signal);
bool IsADCBufferFull(void);
void ADCBuffer_final(void);

void TestSetRawSignal(void);

#endif /* BUFFER_H_ */