/*
 * pwa.h
 *
 * Created: 10/10/2012 11:29:02 AM
 *  Author: yoonl
 */ 


#ifndef PWA_H_
#define PWA_H_

#include <asf.h>

bool FloatSignal_init(void);
void FloatSignal_final(void);
bool IntegerOnsets_init(void);
void IntegerOnsets_final(void);
void Finalise(void);
bool InitialDownSample(const uint8_t pDownSampleRate, const uint16_t rawSignalLength);
bool ValidateBeforeCalculate(void);
bool CalculateBrachial(void);
bool CalculateRadial(float pCalibrationFactor);
void Convolution_Radial(const float *pPulses);
void Convolution_Brachial(const float *averagePulses);

#endif /* PWA_H_ */