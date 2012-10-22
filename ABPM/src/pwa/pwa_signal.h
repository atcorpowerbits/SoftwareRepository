/*
 * pwa_signal.h
 *
 * Created: 11/10/2012 9:45:34 AM
 *  Author: yoonl
 */ 


#ifndef PWA_SIGNAL_H_
#define PWA_SIGNAL_H_

#include "asf.h"

float *Derivatives1;
float *Derivatives2;

bool Derivatives_init(void);
void Derivatives_final(void);
bool FindOnsets(const uint8_t pAlgorithm, const uint8_t pMinTrigPt, const float *floatSignal, const uint16_t signalLength,
	uint16_t *onsetsLength, int16_t *integerOnsets, float *derivatives1, float *derivatives2);

#endif /* PWA_SIGNAL_H_ */