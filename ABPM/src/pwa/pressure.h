/*
 * pressure.h
 *
 * Created: 12/10/2012 1:44:56 PM
 *  Author: yoonl
 */ 


#ifndef PRESSURE_H_
#define PRESSURE_H_

#include "asf.h"
#include "pulse.h"

Pulse *Pulses; // For Brachial, Peripheral, Central signals calculation.
Pulse *AvPulse; // For Brachial, Peripheral, Central signals calculation.
uint8_t NofPulses; // For CalcPulses(), AveragePulse()
Pulse *Periph_CalAvPulse;
Pulse *Central_CalAvPulse;

// Expand pulses which are used for Peripheral, Central calculation.
Pulse *ExpPulse;
Pulse *Der1ExpPulse;
Pulse *Der2ExpPulse;
Pulse *Der3ExpPulse;

bool Pulses_init(void);
void Pulses_final(void);
bool AvPulse_init(void);
void AvPulse_final(void);
bool Periph_CalAvPulse_init(void);
void Periph_CalAvPulse_final(void);
bool Central_CalAvPulse_init(void);
void Central_CalAvPulse_final(void);
bool ExpPulses_init(void);
void ExpPulses_final(void);

bool CalcPulses(const int8_t pTail, const uint16_t pOnsetsLength, const float *pFloatSignal, const int16_t *TrigPts);
bool AveragePulse(const int16_t pLength, const int8_t pTail, const int16_t pSignalSampleRate);
void CalibratePulse(const float pGain, const float pOffset, const Pulse *pAvPulse, float *pMin, float *pMax, Pulse *pCalAvPulse);
bool ExpandPulse(Pulse *pPulse, const int8_t pExpandFactor);
bool SystolicOnset(const int8_t pAlgorithm, const int16_t pLengthOfRadial, const int16_t pExpPulseSampleRate, Pulse *pExpPulse, Pulse *pDer1ExpPulse, Pulse *pDer2ExpPulse, Pulse *pDer3ExpPulse);
bool PeriphExtractFeatures(const int16_t pEDIndex, const Pulse *pExpPulse);
bool CentralExtractFeatures(const int16_t pEDIndex, const Pulse *pExpPulse);

#endif /* PRESSURE_H_ */