/*
 * pwa.h
 *
 * Major functions for PWA calculation, Peripheral/Central output parameters.
 *
 * Copyright (c) Atcor Medical Pty. Ltd., 2013
 *
 * Created: 10/10/2012 11:29:02 AM
 *  Author: yoonl
 */ 


#ifndef PWA_H_
#define PWA_H_

#include <asf.h>
#include "pwa_data.h"
#include "config/conf_abpm.h"

Peripheral_Parameters *PeriphParams; // Peripheral output parameters to be used for Periph/Central calculation.
Central_Parameters *CentralParams; // Central output parameters for report.
QC_Parameters *QCParams; // Quality Control parameters.

float *floatSignal; // For Brachial and Peripheral signals calculation.
float *Central_floatSignal; // For Central calculation transformed from Peripheral signals.
int16_t *integerOnsets; // For Brachial and Peripheral signals calculation.
uint16_t onsetsLength; // For Brachial and Peripheral signals calculation.
int16_t *Central_integerOnsets; // For Central calculation.
uint16_t Central_onsetsLength; // For Central calculation.
uint16_t signalLength; // For Brachial, Peripheral, Central signals calculation.

// Used for finding onset, slope, peak.
float *Derivatives1;
float *Derivatives2;

// Allocate and free memories on heap.
bool FloatSignal_init(void);
void FloatSignal_final(void);
bool Central_FloatSignal_init(void);
void Central_FloatSignal_final(void);
bool IntegerOnsets_init(void);
void IntegerOnsets_final(void);
bool Central_IntegerOnsets_init(void);
void Central_IntegerOnsets_final(void);
bool Derivatives_init(void);
void Derivatives_final(void);

bool PeriphParams_init(void);
void PeriphParams_final(void);
bool CentralParams_init(void);
void CentralParams_final(void);
bool QCParams_init(void);
void QCParams_final(void);

void Initialise(void); // Initialise all single tone parameters, eg. signalLength, onsetsLength, etc.
void Finalise(void); // Free all heap memories.

bool CheckSamples(void); // Check each sample in adc_buffer whether acceptable or not.
bool ValidateBeforeCalculate(void); // Validate signalLength before Calculation routine.
bool CalculateBrachial(void); // Calculate Brachial raw signal.
bool CalculateRadial(void); // Calculate Periph/Central signals transformed from Brachial signal.
bool CalculatePeriph_CalAvPulse(void); // Calculate Periph_CalAvPulse and Peripheral parameters.
bool CalculateCentral_CalAvPulse(void); // Calculate Central_CalAvPulse and Central parameters.
void Convolution_Radial(const float *pPulses); // Transform Peripheral signal to Central signal.
void Convolution_Brachial(const float *averagePulses); // Transform Brachial signal to Peripheral signal.
bool CalibrateAvPulse_Periph(void); // Calibrate Periph_CalAvPulse.
bool CalibrateAvPulse_Central(void); // Calibrate Central_CalAvPulse.
bool ExtractFeatures(void); // Find T1, T2, ED for Periph and Central, extract Periph and Central parameters.
bool RejectIrregularTrigPts(void); // Compare Periph and Central trigger points and Reject irregulars.
bool ValidateBeforeStore(void); // Validate Periph and Central parameters before store.
bool CalculatePWA(void); // Do all mathematics for this measurement.

void TestCallPWA(void); // For porting to C only, will be removed after done porting to C.
void TestSetRawSignal(void); // For porting to C only, will be removed after done porting to C.

void DisplayMemoryUsage(char *msg);

void pwa_calculation_task (void);

extern bool flag_start_pwa;
extern bool flag_finished_pwa;

#endif /* PWA_H_ */