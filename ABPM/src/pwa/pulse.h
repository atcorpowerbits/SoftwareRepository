/*
 * pulse.h
 *
 * Created: 17/10/2012 2:03:03 PM
 *  Author: yoonl
 */ 


#ifndef PULSE_H_
#define PULSE_H_

#include "asf.h"
#include "pwa_data.h"

typedef struct
{
	int16_t Index;
	int16_t Start;
	int16_t End;
	int16_t FLength;
	int16_t FSize;
	float *Profile;
}Pulse;

bool Smooth(float *pProfile, const int16_t pSize);
float Math_Max(const int16_t i1, const int16_t i2, const Pulse *pPulse);
float Math_Min(const int16_t i1, const int16_t i2, const Pulse *pPulse);
int16_t IndexOfMax(const int16_t i1, const int16_t i2, const Pulse *pPulse);
int16_t IndexOfMin(const int16_t i1, const int16_t i2, const Pulse *pPulse);
float Integral(int16_t pBegin, int16_t pEnd, const Pulse *pPulse);
bool Validate(const Pulse *pPulse);
bool IsExtremumStable(const int16_t ExtPoint, const int16_t pBegin, const int16_t pEnd,	const bool pMaxOrMin, const float* Der2, const Pulse *pPulse);
bool CheckCondition(const int16_t i, const int16_t i1, const int16_t i2,
	float* pOtherFunction, const bool pOtherLessOrMore,
	const float pOtherLessOrMoreThan, const int16_t pOtherStabilityZone, const int16_t pPulseEnd);
	
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
	
bool DownSample(const Pulse *pExpPulse, const const int8_t pDownSampleRate, Pulse *pAvPulse);

void FindT1T2ED(const Pulse *pExpPulse, Pulse *Der1, Pulse *Der2, Pulse *Der3, const int8_t pExpandFactor, const int16_t pSampleRate,
	const int16_t pED, const int16_t pCentralMainPeak, const int16_t pPeriphMainPeak, const int16_t pLimitT1T2, float *pCentralDer1_Profile,
	Peripheral_Parameters *pPeriphParams, Central_Parameters *pCentralParams);
	
float IndexToTime(const int16_t pIndex, const Pulse *pExpPulse);
int16_t TimeToIndex(const float pTime, const Pulse *pExpPulse);
float MaxDerivative1(const int16_t i1, const int16_t i2, const int16_t pSmoothOrder, const Pulse *pExpPulse);
float PressureValue(const float pPoint, const Pulse *pPulse);

#endif /* PULSE_H_ */