/*
 * pulse.h
 *
 * Calculations about T1,T2,ED of expand pulse, finding min/max, index of pulse.
 *
 * Copyright (c) Atcor Medical Pty. Ltd., 2013
 *
 * Created: 17/10/2012 2:03:03 PM
 *  Author: yoonl
 */ 


#ifndef PULSE_H_
#define PULSE_H_

#include "asf.h"
#include "pwa_data.h"

// Structure of a single pulse.
typedef struct
{
	int16_t Index;
	int16_t Start;
	int16_t End;
	int16_t FLength;
	int16_t FSize;
	float *Profile;
}Pulse;

// Smooth profile using running average algorithm
bool Smooth(float *pProfile, const int16_t pSize);
// Find Max/Min for pulse between indexes i1, i2
float Math_Max(const int16_t i1, const int16_t i2, const Pulse *pPulse);
float Math_Min(const int16_t i1, const int16_t i2, const Pulse *pPulse);
// Find Min, Max for pulse
bool MinMax(float *pMin, float *pMax, const Pulse *pPulse);
// Find index of maximal (or minimal) value for pulse between indexes i1, i2
int16_t IndexOfMax(const int16_t i1, const int16_t i2, const Pulse *pPulse);
int16_t IndexOfMin(const int16_t i1, const int16_t i2, const Pulse *pPulse);
// Integrate pulse profile using trapezoid formula on interval [pBegin, pEnd]:
float Integral(int16_t pBegin, int16_t pEnd, const Pulse *pPulse);
// Validate pulse
bool Validate(const Pulse *pPulse);
// Check extremum stability
bool IsExtremumStable(const int16_t ExtPoint, const int16_t pBegin, const int16_t pEnd,	const bool pMaxOrMin, const float* Der2, const Pulse *pPulse);
// Check whether the function is changing sign (so unstable) in window [i1,i2]
bool CheckCondition(const int16_t i, const int16_t i1, const int16_t i2,
	float* pOtherFunction, const bool pOtherLessOrMore,
	const float pOtherLessOrMoreThan, const int16_t pOtherStabilityZone, const int16_t pPulseEnd);

// Find index of Extremal (local) Maximal (or Minimal) value for pulse
// between indexes i1, i2 with checking stability and limits
int16_t IndexOfExtremum(const Pulse *pPulse, const bool pMinOrMax, const bool pOnlyFirst,
	const int16_t i1, const int16_t i2,
	const int16_t pStabilityZone, const bool pLessOrMore,
	const float pLessOrMoreThan, float *Der2,
	float *pOtherFunction, const bool pOtherLessOrMore,
	const float pOtherLessOrMoreThan, const int16_t pOtherStabilityZone,
	float *pOtherFunction2, const bool pOtherLessOrMore2,
	const float pOtherLessOrMoreThan2, const int16_t pOtherStabilityZone2,
	float *pOtherFunction3, const bool pOtherLessOrMore3,
	const float pOtherLessOrMoreThan3, const int16_t pOtherStabilityZone3,
	float *pOtherFunction4, const bool pOtherLessOrMore4,
	const float pOtherLessOrMoreThan4, const int16_t pOtherStabilityZone4);

// Re-sample pulse from high to low frequency
bool DownSample(const Pulse *pExpPulse, const const int8_t pDownSampleRate, Pulse *pAvPulse);

// Find points of T1, T2, ED (not real time)
void FindT1T2ED(const Pulse *pExpPulse, Pulse *Der1, Pulse *Der2, Pulse *Der3, const int8_t pExpandFactor, const int16_t pSampleRate,
	const int16_t pED, const int16_t pCentralMainPeak, const int16_t pPeriphMainPeak, const int16_t pLimitT1T2, float *pCentralDer1_Profile,
	Peripheral_Parameters *pPeriphParams, Central_Parameters *pCentralParams);

// Convert Index into time in msec
float IndexToTime(const int16_t pIndex, const Pulse *pExpPulse);
// Convert Time into index assuming 0 correspond to start point
int16_t TimeToIndex(const float pTime, const Pulse *pExpPulse);
// Find maximum the 1st derivative of pulse between indexes i1, i2
float MaxDerivative1(const int16_t i1, const int16_t i2, const int16_t pSmoothOrder, const Pulse *pExpPulse);
// Find Value of a pulse in x-point pPoint
float PressureValue(const float pPoint, const Pulse *pPulse);
// Find pulse height (Max - Min)
float Height(const Pulse *pPulse);
// Find pulse height (Max - Profile[0])
float QC_Height(const Pulse *pPulse);

#endif /* PULSE_H_ */