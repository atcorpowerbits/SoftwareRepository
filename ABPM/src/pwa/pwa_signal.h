/*
 * pwa_signal.h
 *
 * Finding onsets algorithm.
 *
 * Copyright (c) Atcor Medical Pty. Ltd., 2013
 *
 * Created: 11/10/2012 9:45:34 AM
 *  Author: yoonl
 */ 


#ifndef PWA_SIGNAL_H_
#define PWA_SIGNAL_H_

#include "asf.h"

// Find Trigger points for signal.
bool FindOnsets(const uint8_t pAlgorithm, const uint8_t pMinTrigPt, const float *floatSignal, const uint16_t signalLength,
	uint16_t *onsetsLength, int16_t *integerOnsets, float *derivatives1, float *derivatives2);

#endif /* PWA_SIGNAL_H_ */