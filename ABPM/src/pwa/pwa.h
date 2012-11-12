/*
 * pwa.h
 *
 * Created: 10/10/2012 11:29:02 AM
 *  Author: yoonl
 */ 


#ifndef PWA_H_
#define PWA_H_

#include <asf.h>
#include "pwa_data.h"

Peripheral_Parameters *PeriphParams; // Peripheral output parameters to be used for Periph/Central calculation.
Central_Parameters *CentralParams; // Central output parameters for report.

bool RawSignal_init(uint16_t pSize);
void RawSignal_final(void);
bool FloatSignal_init(void);
void FloatSignal_final(void);
bool Central_FloatSignal_init(void);
void Central_FloatSignal_final(void);

bool IntegerOnsets_init(void);
void IntegerOnsets_final(void);
bool Central_IntegerOnsets_init(void);
void Central_IntegerOnsets_final(void);

bool PeriphParams_init(void);
void PeriphParams_final(void);
bool CentralParams_init(void);
void CentralParams_final(void);

void Initialise(void);
void Finalise(void);

bool InitialDownSample(const uint8_t pDownSampleRate, const uint16_t rawSignalLength);
bool ValidateBeforeCalculate(void);
bool CalculateBrachial(void);
bool CalculateRadial(void);
bool Convolution_Radial(const float *pPulses);
bool Convolution_Brachial(const float *averagePulses);
bool CalibrateAvPulse_Periph(void);
bool CalibrateAvPulse_Central(void);
void ExtractFeatures(void);
bool RejectIrregularTrigPts(void);

void TestCallPWA(void); // For porting to C only, will be removed after done porting to C.
void TestSetRawSignal(void); // For porting to C only, will be removed after done porting to C.

#endif /* PWA_H_ */