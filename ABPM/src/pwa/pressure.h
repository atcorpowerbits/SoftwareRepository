/*
 * pressure.h
 *
 * Calculations about Pulses, average pulse, calibration, quality control(QC).
 *
 * Copyright (c) Atcor Medical Pty. Ltd., 2013
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
Pulse *Periph_CalAvPulse; // Final calibrated Peripheral average pulse after all calculation.
Pulse *Central_CalAvPulse; // Final calibrated Central average pulse after all calculation.

// Expand pulses which are used for Peripheral, Central calculation.
Pulse *ExpPulse;
Pulse *Der1ExpPulse;
Pulse *Der2ExpPulse;
Pulse *Der3ExpPulse;

// Allocate and free memories on heap.
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

// Calculate Pulses using trigger points
bool CalcPulses(const int8_t pTail, const uint16_t pOnsetsLength, const float *pFloatSignal, const int16_t *TrigPts);
// Find Average Pulse from Pulses
bool AveragePulse(const int16_t pLength, const int8_t pTail, const int16_t pSignalSampleRate);
// Calibrate AveragePulse and find Min, Max
void CalibratePulse(const float pGain, const float pOffset, const Pulse *pAvPulse, float *pMin, float *pMax, Pulse *pCalAvPulse);
// Expand pPulse with analitical calculation of expanded profile and its derivatives using polinomial spline interpolation.
bool ExpandPulse(Pulse *pPulse, const int8_t pExpandFactor);
// Find systolic onset (trigger point) for a pulse, line up (shift) pulse profile and derivatives to it and cut pulse tale.
bool SystolicOnset(const int8_t pAlgorithm, const int16_t pLengthOfRadial, const int16_t pExpPulseSampleRate, Pulse *pExpPulse, Pulse *pDer1ExpPulse, Pulse *pDer2ExpPulse, Pulse *pDer3ExpPulse);
// Extract specific feature parameters for Central.
bool CentralExtractFeatures(const int16_t pEDIndex, const Pulse *pExpPulse);
// Calculate Quality Control parameters.
bool QualityControl(void);
// Calculate Operator Index used by Quality Control parameters.
int16_t CalculateOperatorIndex(void);

#endif /* PRESSURE_H_ */