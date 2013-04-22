/*
 * pulse.c
 *
 * Calculations about T1,T2,ED of expand pulse, finding min/max, index of pulse.
 *
 * Copyright (c) Atcor Medical Pty. Ltd., 2013
 *
 * Created: 17/10/2012 2:03:33 PM
 *  Author: yoonl
 */ 

#include "pulse.h"
#include "math_pwa.h"
#include "usart/usart_rxtx.h"
#include <math.h>

#define BEGIN_PERCENT	(float)0.03 // Calculate T1,T2,ED from this percent of length
#define NORMAL_ED_MAX	(int16_t)420
#define SLOW_HR_ED_MAX	(int16_t)450
#define ED_MIN_PERCENT	(float)0.20
#define ED_MAX_PERCENT	(float)0.65 // ED cannot be more then 65% of Length
#define ESP_MAX_PERCENT	(float)0.75 // ESP cannot be more then 75% of PulseHeight
#define LIMIT_T1T2_FACTOR	(float)1.2 // Central T2 cannot be more then 1.2* Periph T2

/* ###########################################################################
 ** Smooth()
 **
 ** DESCRIPTION
 **  Smooth pulse profile using running average algorithm
 ** INPUT
 **  pProfile - pressure points
 **  pSize - Number of Filter points
 ** OUTPUT
 **  smoothed profile
 ** RETURN
 **  true if success, false otherwise
*/
bool Smooth(float *pProfile, const int16_t pSize)
{
	return Math_SmoothArray(pProfile, pSize);
}

/* ###########################################################################
 ** Math_Max()
 **
 ** DESCRIPTION
 **  Find Max for pulse between indexes i1, i2
 ** INPUT
 **  i1,i2,pPulse
 ** OUTPUT
 ** RETURN
 **  pMax values for pulse
 */
float Math_Max(const int16_t i1, const int16_t i2, const Pulse *pPulse)
{
	float pMax = -DEFAULT_VALUE;
	// Pulse Validation
	if (Validate(pPulse)==false)
	{
		return pMax;
	}
	// Validate interval
	if (i1 >= i2)
	{
		return pMax;
	}

	// Find max for Pulse
	pMax = pPulse->Profile[i1];
	for (int16_t i = i1; i < i2; i++)
	{
		if (pPulse->Profile[i] > pMax)
		{
			pMax = pPulse->Profile[i];
		}
	}
	return pMax;
}

/* ###########################################################################
 ** Math_Min()
 **
 ** DESCRIPTION
 **  Find Min for pulse between indexes i1, i2
 ** INPUT
 **  i1,i2,pPulse
 ** OUTPUT
 ** RETURN
 **  pMin values for pulse
 */
float Math_Min(const int16_t i1, const int16_t i2, const Pulse *pPulse)
{
	float pMin = DEFAULT_VALUE;
	// Pulse Validation
	if (Validate(pPulse)==false)
	{
		return pMin;
	}
	// Validate interval
	if (i1 >= i2)
	{
		return pMin;
	}

	// Find min for Pulse
	pMin = pPulse->Profile[i1];
	for (int16_t i = i1; i < i2; i++)
	{
		if (pPulse->Profile[i] < pMin)
		{
			pMin = pPulse->Profile[i];
		}
	}
	return pMin;
}

/* ###########################################################################
 ** MinMax ()
 **
 ** DESCRIPTION
 **  Find Min, Max for pulse
 ** INPUT
 **  pPulse
 ** OUTPUT
 **  pMin, pMax values for pulse
 ** RETURN
 **  boolean - return false if validation of pPulse is failed.
*/
bool MinMax(float *pMin, float *pMax, const Pulse *pPulse)
{
	// Pulse Validation
	if (!Validate(pPulse))
	{
		return false;
	}

	// Find max, min for Pulse
	*pMin = pPulse->Profile[pPulse->Start];
	*pMax = pPulse->Profile[pPulse->Start];
	for (int16_t i = pPulse->Start; i <= pPulse->End; i++)
	{
		if (pPulse->Profile[i] > *pMax)
		{
			*pMax = pPulse->Profile[i];
		}
		if (pPulse->Profile[i] < *pMin)
		{
			*pMin = pPulse->Profile[i];
		}
	}
	return (*pMax > *pMin);
}

/* ###########################################################################
 ** IndexOfMax (), IndexOfMin ()
 **
 ** DESCRIPTION
 **  Find index of Maximal (or Minimal) value for pulse
 **  between indexes i1, i2
 ** INPUT
 **  i1, i2 - indexes
 **  pPulse
 ** OUTPUT
 ** RETURN
 **  Index or -1 if wrong pulse
*/
int16_t IndexOfMax(const int16_t i1, const int16_t i2, const Pulse *pPulse)
{
	int16_t ind = -1;
	// Pulse Validation
	if (Validate(pPulse)==false)
	{
		return ind;
	}
	// Validate interval
	if (i1 >= i2)
	{
		return ind;
	}

	// Find max for Pulse
	float pMax = pPulse->Profile[i1];
	ind = i1;
	for (int16_t i = i1; i < i2; i++)
	{
		if (pPulse->Profile[i] > pMax)
		{
			pMax = pPulse->Profile[i];
			ind = i;
		}
	}
	return ind;
}
int16_t IndexOfMin(const int16_t i1, const int16_t i2, const Pulse *pPulse)
{
	int16_t ind = -1;
	// Pulse Validation
	if (Validate(pPulse)==false)
	{
		return ind;
	}
	// Validate interval
	if (i1 >= i2)
	{
		return ind;
	}

	// Find max for Pulse
	float pMin = pPulse->Profile[i1];
	ind = i1;
	for (int16_t i = i1; i < i2; i++)
	{
		if (pPulse->Profile[i] < pMin)
		{
			pMin = pPulse->Profile[i];
			ind = i;
		}
	}
	return ind;
}

/* ###########################################################################
 ** Integral()
 **
 ** DESCRIPTION
 **  Use trapezoid formula to integrate pulse profile on interval [pBegin, pEnd]:
 **  End point pEnd included in formula. Abscissa step = 1.
 **  Int = (f[pBegin] + 2*f[pBegin+1] + 2*f[pBegin+2]... + 2*f[pEnd - 1] + f[pEnd])/2
 ** INPUT
 **  pPulse - average pulse
 **  pBegin, pEnd - interval
 ** OUTPUT
 ** RETURN
 **  Integral value
*/
float Integral(int16_t pBegin, int16_t pEnd, const Pulse *pPulse)
{
	float lAv = -DEFAULT_VALUE; // -9999

	// Validate pulse
	if (Validate(pPulse)==false)
	{
		return lAv;
	}
	// Validate interval
	if (pBegin >= pEnd)
	{
		return lAv;
	}

	// Integrating
	double d = pPulse->Profile[pBegin]/2;
	for (int16_t i = pBegin + 1; i < pEnd; i++)
	{
		d += pPulse->Profile[i];
	}
	d += pPulse->Profile[pEnd]/2;

	lAv = (float)d;
	return lAv;
}

/* ###########################################################################
 ** Validate ()
 **
 ** DESCRIPTION
 **  Validate pulse
 ** INPUT
 **  pPulse
 ** OUTPUT
 ** RETURN
 **  boolean valid pulse or not
*/
bool Validate(const Pulse *pPulse)
{
	// Pulse Validation
	if ((!pPulse) || (pPulse->FLength < 1) || (pPulse->Start < 0) || (pPulse->Start > pPulse->End) ||
		(pPulse->FSize < pPulse->FLength) || (pPulse->FSize > PRESSURE_EXPPULSE_MAXLENGTH) || (pPulse->End - pPulse->Start + 1 != pPulse->FLength))
	{
		PWA_Error_Code = PWA_MSG_WRONG_PULSE;
		print_debug("Error(%d): Invalid or unrecognizable pulse detected.\r\n", PWA_Error_Code);
		return false;
	}
	return true;
}

/* ###########################################################################
 ** IsExtremumStable()
 **
 ** DESCRIPTION
 **  Check extremum stability
 ** INPUT
 **   ExtPoint, pBegin, pEnd, pMaxOrMin, Der2, pPulse
 ** OUTPUT
 ** RETURN
 **  boolean Stable extremum
*/
bool IsExtremumStable(const int16_t ExtPoint, const int16_t pBegin, const int16_t pEnd,	const bool pMaxOrMin, const float* Der2, const Pulse *pPulse)
{
	// Analyse profile extremum
	for (int16_t i = pBegin; i<=pEnd; i++)
	{
		if (i == ExtPoint)
		{
			continue;
		}
		if (pMaxOrMin == MAX) // max
		{
			if (pPulse->Profile[i] > pPulse->Profile[ExtPoint]) // found point > max
			{
				return false;
			}
			if (Der2 && Der2[i] >= 0.) // for stable max Der2 always < 0
			{
				return false;
			}
		}
		else
		{
			if (pPulse->Profile[i] < pPulse->Profile[ExtPoint]) // found point < min
			{
				return false;
			}
			if (Der2 && Der2[i] <= 0.) // for stable min Der2 always > 0
			{
				return false;
			}
		}
	}
	// Stable extremum
	return true;
}

/* ###########################################################################
 ** CheckCondition()
 **
 ** DESCRIPTION
 **  Check whether the function is changing sign (so unstable) in window [i1,i2]
 ** INPUT
 **  i, i1, i2, pOtherFunction, pOtherLessOrMore
 **  pOtherLessOrMoreThan, pOtherStabilityZone, pPulseEnd
 ** OUTPUT
 ** RETURN
 **  boolean - return false if change the sign.
*/
bool CheckCondition(const int16_t i, const int16_t i1, const int16_t i2,
	float* pOtherFunction, const bool pOtherLessOrMore,
	const float pOtherLessOrMoreThan, const int16_t pOtherStabilityZone, const int16_t pPulseEnd)
{
	int16_t lBegin, lEnd;
	if (pOtherStabilityZone > 0)
	{
		lBegin = (i - pOtherStabilityZone > 0 ?	i - pOtherStabilityZone : i1);
		lEnd =   (i + pOtherStabilityZone <= pPulseEnd ? i + pOtherStabilityZone : i2);
	}
	else
	{
		lBegin = i;
		lEnd   = i + 1;
	}
	// Reject if function change the sign
	if (pOtherLessOrMoreThan != DEFAULT_VALUE)
	{
		bool lReject = false;
		for (int16_t i = lBegin; i < lEnd; i++)
		{
			if (pOtherLessOrMore == LESS)
			{
				if (pOtherFunction[i] >= pOtherLessOrMoreThan)
				{
					lReject = true;
					break;
				}
			}
			else // if (pLessOrMore == MORE)
			{
				if (pOtherFunction[i] <= pOtherLessOrMoreThan)
				{
					lReject = true;
					break;
				}
			}
		}
		if (lReject == true)
		{
			return false;
		}			
	}
	return true;
}

/* ###########################################################################
 ** IndexOfExtremum()
 **
 ** DESCRIPTION
 **  Find index of Extremal Maximal (or Minimal) value for pulse
 **  between indexes i1, i2
 ** INPUT
 **  pPulse, pMinOrMax, pOnlyFirst
 **  i1, i2 - indexes
 **  pStabilityZone, pLessOrMore, pLessOrMoreThan, Der2
 **  4 sets of pOtherFunction, pOtherLessOrMore, pOtherLessOrMoreThan, pOtherStabilityZone
 ** OUTPUT
 ** RETURN
 **  Index or -1 if wrong pulse
*/
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
	const float pOtherLessOrMoreThan4, const int16_t pOtherStabilityZone4)
{
	int16_t ind = -1;
	// Pulse Validation
	if (Validate(pPulse)==false)
	{
		return ind;
	}
	// Validate interval
	if (i1 >= i2)
	{
		return ind;
	}
	// Find Extremum for Pulse.
	// For maximum extremum is where Current > Last, Current >= Next
	// For minimum extremum is where Current < Last, Current <= Next
	float lCurrent, lLast, lNext;
	for (int16_t i = i1 + 1; i < i2 - 1; i++)
	{
		lCurrent = pPulse->Profile[i];
		// Check limit
		if (pLessOrMoreThan != DEFAULT_VALUE)
		{
			if (pLessOrMore == LESS)
			{
				if (lCurrent >= pLessOrMoreThan)
				{
					continue;
				}
			}
			else // if (pLessOrMore == MORE)
			{
				if (lCurrent <= pLessOrMoreThan)
				{
					continue;
				}
			}
		}
		lLast = pPulse->Profile[i-1];
		lNext = pPulse->Profile[i+1];
		// Check conditions for Max or Min
		if (pMinOrMax == MAX)
		{
			if (lCurrent <= lLast || lCurrent < lNext)
			{
				continue;
			}
		}
		else // if (pMinOrMax == MINIMUM)
		{
			if (lCurrent >= lLast || lCurrent > lNext)
			{
				continue;
			}
		}
		// Now lCurrent is extremum. Check stability of an extremum
		if (pStabilityZone > 0)
		{
			int16_t lBegin = (i - pStabilityZone > 0 ? i - pStabilityZone : i1);
			int16_t lEnd = (i + pStabilityZone <= pPulse->End ? i + pStabilityZone : i2);
			// Reject if function change the sign
			if (pLessOrMoreThan != DEFAULT_VALUE)
			{
				bool lReject = false;
				for (int16_t i = lBegin; i < lEnd; i++)
				{
					if (pLessOrMore == LESS)
					{
						if (pPulse->Profile[i] >= pLessOrMoreThan)
						{
							lReject = true;
							break;
						}
					}
					else // if (pLessOrMore == MORE)
					{
						if (pPulse->Profile[i] <= pLessOrMoreThan)
						{
							lReject = true;
							break;
						}
					}
				}
				if (lReject == true)
				{
					continue;
				}
			}
			// Reject unstable extremum
			if (IsExtremumStable(i, lBegin, lEnd, pMinOrMax, Der2, pPulse)==false)
			{
				continue;
			}
		}
		// .................................................................
		// Now lCurrent is extremum. Check stability of OtherFunctions
		if (pOtherFunction && pOtherLessOrMoreThan != DEFAULT_VALUE)
		{
			if (CheckCondition(i, i1, i2, pOtherFunction, pOtherLessOrMore,
				pOtherLessOrMoreThan, pOtherStabilityZone, pPulse->End)==false)
			{
				continue;
			}
		}
		if (pOtherFunction2 && pOtherLessOrMoreThan2 != DEFAULT_VALUE)
		{
			if (CheckCondition(i, i1, i2, pOtherFunction2, pOtherLessOrMore2,
				pOtherLessOrMoreThan2, pOtherStabilityZone2, pPulse->End)==false)
			{
				continue;
			}
		}
		if (pOtherFunction3 && pOtherLessOrMoreThan3 != DEFAULT_VALUE)
		{
			if (CheckCondition(i, i1, i2, pOtherFunction3, pOtherLessOrMore3,
				pOtherLessOrMoreThan3, pOtherStabilityZone3, pPulse->End)==false)
			{
				continue;
			}
		}
		if (pOtherFunction4 && pOtherLessOrMoreThan4 != DEFAULT_VALUE)
		{
			if (CheckCondition(i, i1, i2, pOtherFunction4, pOtherLessOrMore4,
				pOtherLessOrMoreThan4, pOtherStabilityZone4, pPulse->End)==false)
			{
				continue;
			}
		}
		// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		// Analise whether extremum is first or not, if necessary
		if (ind < 0)
		{
			ind = i;
			if (pOnlyFirst == FIRST)
			{
				break;
			}
		}
		else
		{
			if (pMinOrMax == MAX)
			{
				if (lCurrent > pPulse->Profile[ind])
				{
					ind = i;
				}
			}
			else // if (pMinOrMax == MINIMUM)
			{
				if (lCurrent < pPulse->Profile[ind])
				{
					ind = i;
				}
			}
		}
	}

	return ind;
}

/* ###########################################################################
 ** DownSample()
 **
 ** DESCRIPTION
 **  Resample pulse from high to low frequency
 ** (for example, from 1024 to 128 Htz)
 ** INPUT
 **  pExpPulse - input high frequency pulse
 **  pDownSampleRate - rate of upsampling (8)
 ** OUTPUT
 **  pAvPulse
 ** RETURN
 **  boolean - validation of pExpPulse,pAvPulse.
*/
bool DownSample(const Pulse *pExpPulse, const const int8_t pDownSampleRate, Pulse *pAvPulse)
{
	// Validation
	if (Validate(pExpPulse)==false)
	{
		return false;
	}

	// Initialise AvPulse
	pAvPulse->Index = -1;
	pAvPulse->Start = 0;
	pAvPulse->End = 0;
	pAvPulse->FLength = 0;
	pAvPulse->FSize = 0;
	memset(pAvPulse->Profile, 0, sizeof(float)*PRESSURE_PULSE_MAXLENGTH);
	
	int16_t lSize = (pExpPulse->FLength - 1)/pDownSampleRate + 1;
	pAvPulse->End = pAvPulse->Start + lSize - 1;
	pAvPulse->FLength = lSize;
	pAvPulse->FSize = lSize;
	for (int16_t i=0; i < lSize; i++)
	{
		pAvPulse->Profile[i] = pExpPulse->Profile[pExpPulse->Start + i*pDownSampleRate];
	}
	return Validate(pAvPulse);
}

/* ###########################################################################
 ** FindT1T2ED
 **
 ** DESCRIPTION
 **  Find points of T1, T2, ED (not real time) from ExpPulse
 ** INPUT
 **  Expanded pulses
 **  pED - predefined ED. For periph = -1, for central = Periph.ED
 **  Der1, Der2, Der3 - pulse waveform derivatives
 **  pExpandFactor (8) - Coefficient of expanding sample
 **                      frequency(in ExpandFactor times)
 **  pSampleRate (128) - Signal sample rate
 **  pCentralMainPeak - Main peak for Central Pulse waveform
 **  pPeriphMainPeak - Main peak for peripheral Pulse waveform
 **  pLimitT1T2 - Limit time for T2 (Central)
 **  pCentralDer1_Profile - Der1 for Central pulse
 ** OUTPUT
 **  pPeriphParams or pCentralParams
 ** RETURN
*/
void FindT1T2ED(const Pulse *pExpPulse, Pulse *Der1, Pulse *Der2, Pulse *Der3, const int8_t pExpandFactor, const int16_t pSampleRate,
	const int16_t pED, const int16_t pCentralMainPeak, const int16_t pPeriphMainPeak, const int16_t pLimitT1T2, float *pCentralDer1_Profile,
	Peripheral_Parameters *pPeriphParams, Central_Parameters *pCentralParams)
{
	// Initialisation
	float *CD1P = pCentralDer1_Profile, *CD2P = NULL;
	
	int16_t T1 = DEFAULT_VALUE; // Index of the 1st peak
	int16_t T2 = DEFAULT_VALUE; // Index of the 2nd peak
	int16_t ED = (pED > 0 && pED != DEFAULT_VALUE ? pED : DEFAULT_VALUE); // Index of ejection duration

	int16_t QualityT1 = DEFAULT_VALUE;
	int16_t QualityT2 = DEFAULT_VALUE;
	int16_t QualityED = DEFAULT_VALUE;
	int16_t OurCase = -1; // Distinquish cases

	int16_t PeakBeforeMain = -1; // Peak before main
	int16_t PeakAfterMain = -1;  // Peak after main

	int16_t ShoulderBeforePeak = -1; // Shoulder before main peak
	int16_t ShoulderAfterPeak = -1;  // Shoulder after main peak
	int16_t T2m = -1; // Min der3 for T2
	int16_t EndT2 = -1; // End of effective length of pulse after cut tail
	int16_t Tr = -1; // Time of reflected wave (Max Der2)
	
	int8_t LocalZoneNofPoints = 4; // NofPoints in local zone
	int8_t StabilityZoneNofPoints = 2; // NofPoints in stability zone for extremums
	int8_t OtherStabilityZoneNofPoints = 1; // NofPoints in stability zone for central wave
	
	// Local Zone - shift to prevent finding neighbourhood points
	int16_t LocalZone = LocalZoneNofPoints * pExpandFactor;
	// Zone of stability to find stable extremums
	int16_t StabilityZone = min(StabilityZoneNofPoints * pExpandFactor, LocalZone);
	// Zone of stability to find stable extremums with analysis stability of another function as well
	int16_t OtherStabilityZone = min(OtherStabilityZoneNofPoints * pExpandFactor, StabilityZone);

	// Define Effective length of Pulse - the value for which T2 cannot be more
	float lHR = ((float)60 * pSampleRate * pExpandFactor) / (pExpPulse->FLength - 1); // Heart rate
	// Calculate TopED - line ED(HR) from table for adult normals ED
	float lTopEDAtHRLow = 350; float lTopEDAtHRHigh = 220;
	float lHRLow = 50; float lHRHigh = 120;
	float la = (lTopEDAtHRLow - lTopEDAtHRHigh)/(lHRLow - lHRHigh);
	float lb = lTopEDAtHRLow - la*lHRLow;
	int16_t lTopED = (int16_t)(la*lHR + lb);
	int16_t lNormalED = lTopED - 32;
	
	int16_t lLength = pExpPulse->FLength;
	int16_t L = (int16_t)(lLength/pExpandFactor > 100 ?	lLength * 0.5 : lLength * 0.55);
	if (lLength/pExpandFactor < 85)
	{
		L = (int16_t)(lLength * 0.60);
	}
	if (lLength/pExpandFactor < 70)
	{
		L = (int16_t)(lLength * 0.70);
	}
	// ED cannot be more than ED_MAX msec
	int16_t lEdMax = (lHR < 60 ? SLOW_HR_ED_MAX : NORMAL_ED_MAX);
	int16_t index = 0;
	Math_TimeToIndex((float)lEdMax, pExpandFactor, pSampleRate, &index);
	L = min(L, index);

	int16_t lDefaultED = 0;
	Math_TimeToIndex((float)lNormalED, pExpandFactor, pSampleRate, &lDefaultED);

	// Index of 60 msec
	float t60msec = (float)TimeToIndex((float)60, pExpPulse);
	
	// For fast HR decrease stability zones
	if (lHR > 90)
	{
		LocalZone = (int16_t)(LocalZone/1.5);
		StabilityZone = (int16_t)(StabilityZone/1.5);
		OtherStabilityZone = (int16_t)(OtherStabilityZone/1.5);
		t60msec /= 1.5;
	}
	else if (lHR < 55)
	{
		LocalZone = (int16_t)(LocalZone*1.5);
		StabilityZone = (int16_t)(StabilityZone*1.5);
		OtherStabilityZone = (int16_t)(OtherStabilityZone*1.5);
		t60msec *= 1.5;
	}
	
	int16_t lLowED = (int16_t)(ED_MIN_PERCENT*lLength); // ED Cannot be less 17% of Length
	// Begin point of signal beginning after avoiding a few points
	int16_t rounded = 0;
	Math_Round(BEGIN_PERCENT*L, &rounded);
	int16_t Begin = max(rounded, LocalZone); // 3% of Length
	
	// MainPeak - Absolute maximum of a signal, main (highest) peak
	int16_t MainPeak = IndexOfExtremum(pExpPulse, MAX, GLOBAL, Begin, L,
									0, LESS, DEFAULT_VALUE, NULL,
									NULL, LESS, DEFAULT_VALUE, 0,
									NULL, LESS, DEFAULT_VALUE, 0,
									NULL, LESS, DEFAULT_VALUE, 0,
									NULL, LESS, DEFAULT_VALUE, 0);
	if (MainPeak < 0)
	{
		print_debug("Info: Main peak for pulse not found.\r\n");
		return;
	}
	// Reject if wrong
	if (pED > 0 && pED != DEFAULT_VALUE && MainPeak >= pED)
	{
		print_debug("Info: Invalid Ejection Duration (less than pulse peak time) for Average Pulse.\r\n");
		return;
	}
	
	// Manage case where Periph ED not found
	if (pED == DEFAULT_VALUE)
	{
		T1 = MainPeak;
		T2 = DEFAULT_VALUE;
		QualityT1 = STRONG;
		QualityT2 = VERYWEAK;
		OurCase = 9;
		goto UpdateParameters;
	}
	
	// Find PeakOfDer1
	int16_t lPeakBeforeMain = IndexOfExtremum(pExpPulse, MAX, GLOBAL, StabilityZone, MainPeak - StabilityZone,
											0, LESS, DEFAULT_VALUE, NULL,
											NULL, LESS, DEFAULT_VALUE, 0,
											NULL, LESS, DEFAULT_VALUE, 0,
											NULL, LESS, DEFAULT_VALUE, 0,
											NULL, LESS, DEFAULT_VALUE, 0);
	int16_t lLimitOfPeakOfDer1 = (lPeakBeforeMain > 0 ? lPeakBeforeMain - StabilityZone	: MainPeak - StabilityZone);
	int16_t PeakOfDer1 = IndexOfExtremum(Der1, MAX, GLOBAL, StabilityZone, lLimitOfPeakOfDer1,
										StabilityZone, MORE, 0., NULL,
										NULL, LESS, DEFAULT_VALUE, 0,
										NULL, LESS, DEFAULT_VALUE, 0,
										NULL, LESS, DEFAULT_VALUE, 0,
										NULL, LESS, DEFAULT_VALUE, 0);
	if (PeakOfDer1 < 0)
	{
		PeakOfDer1 = IndexOfExtremum(Der1, MAX, GLOBAL, StabilityZone, lLimitOfPeakOfDer1,
									OtherStabilityZone, MORE, 0., NULL,
									NULL, LESS, DEFAULT_VALUE, 0,
									NULL, LESS, DEFAULT_VALUE, 0,
									NULL, LESS, DEFAULT_VALUE, 0,
									NULL, LESS, DEFAULT_VALUE, 0);
	}
	if (PeakOfDer1 < 0)
	{
		PeakOfDer1 = IndexOfExtremum(Der1, MAX, GLOBAL, StabilityZone, lLimitOfPeakOfDer1 + StabilityZone/2,
									OtherStabilityZone, MORE, 0., NULL,
									NULL, LESS, DEFAULT_VALUE, 0,
									NULL, LESS, DEFAULT_VALUE, 0,
									NULL, LESS, DEFAULT_VALUE, 0,
									NULL, LESS, DEFAULT_VALUE, 0);
	}
	if (PeakOfDer1 < 0)
	{
		// Check Begin point
		if (Begin >= MainPeak - LocalZone)
		{
			Begin = MainPeak - LocalZone -1;
		}
		if (Begin <= pExpPulse->Start)
		{
			Begin = pExpPulse->Start + 1;
		}
	}
	else
	{
		Begin = PeakOfDer1;
	}
	
	// Largest peak index for periph and central
	int16_t lCentralLatestPeak = (pCentralMainPeak > 0 ? pCentralMainPeak : -1);
	int16_t lLatestPeak = (lCentralLatestPeak > 0 ? max(lCentralLatestPeak, MainPeak) : MainPeak);
	// lEDBegin - left window where ED can be located
	int16_t lEDBegin = max(lLatestPeak + LocalZone, lLowED);
	
	// Find EndT2 - limit distance between peak and ED. In most cases it is almost ED
	float lTreas = 0;
	int16_t EDMin = -1;
	int16_t PeakOfDer2 = -1; // Peak of Der2 for Periph signal
	
	// For Central case EndT2 = ED
	if (ED != DEFAULT_VALUE)
	{
		// End of Window for Central T1, T2 should be less 110% of T2 for periph
		EndT2 = (pLimitT1T2 > 0 ? (int16_t)(pLimitT1T2 * LIMIT_T1T2_FACTOR) : ED - StabilityZone);
	}
	else // For Periph case we need estimate End
	{
		// Periph Pressure[ED] should be less than 75% of PulseHeight
		float PHProc = (float)1. - ESP_MAX_PERCENT;
		float fP0 = pExpPulse->Profile[MainPeak];
		float PHt = fP0 - pExpPulse->Profile[pExpPulse->Start];
		lTreas = fP0 - PHProc*PHt;

		// Try to find sharp minimum as ED and PeakOfDer2 nearby
		int16_t lLimitPeakOfDer2 = L;
		EDMin = IndexOfExtremum(pExpPulse, MIN, GLOBAL, lEDBegin, L, StabilityZone,
								LESS, lTreas, Der2->Profile,
								CD1P, LESS, 0., StabilityZone,
								CD2P, MORE, 0., StabilityZone,
								NULL, LESS, DEFAULT_VALUE, 0,
								NULL, LESS, DEFAULT_VALUE, 0);
		if (EDMin < 0)
		{
			EDMin = IndexOfExtremum(pExpPulse, MIN, FIRST, lEDBegin, L, OtherStabilityZone,
									LESS, lTreas, Der2->Profile,
									CD1P, LESS, 0., OtherStabilityZone,
									CD2P, MORE, 0., OtherStabilityZone,
									NULL, LESS, DEFAULT_VALUE, 0,
									NULL, LESS, DEFAULT_VALUE, 0);
		}
		if (EDMin < 0)
		{
			EDMin = IndexOfExtremum(pExpPulse, MIN, FIRST, lEDBegin, L, OtherStabilityZone,
									LESS, lTreas, Der2->Profile,
									CD1P, LESS, 0., 0,
									CD2P, MORE, 0., 0,
									NULL, LESS, DEFAULT_VALUE, 0,
									NULL, LESS, DEFAULT_VALUE, 0);
		}
		if (EDMin > 0)
		{
			PeakOfDer2 = IndexOfExtremum(Der2, MAX, GLOBAL, EDMin - 2*LocalZone, EDMin/* + 2*LocalZone*/,
										StabilityZone, MORE, 0., NULL,
										pExpPulse->Profile, LESS, lTreas, 0,
										Der1->Profile, LESS, 0., 0,
										CD1P, LESS, 0., 0,
										CD2P, MORE, 0., OtherStabilityZone);
			lLimitPeakOfDer2 = EDMin /* + 2*LocalZone*/;
		}

		// If sharp minimum not found, extract ED from Der2 where Central.Der2 is stably positive in OtherStabilityZone
		if (PeakOfDer2 < 0)
		{
			PeakOfDer2 = IndexOfExtremum(Der2, MAX, GLOBAL, lEDBegin, lLimitPeakOfDer2,
										StabilityZone, MORE, 0., NULL,
										pExpPulse->Profile, LESS, lTreas, 0,
										Der1->Profile, LESS, 0., 0,
										CD1P, LESS, 0., 0,
										CD2P, MORE, 0., OtherStabilityZone);
			// Check if there another good peak after
			if (PeakOfDer2 > 0)
			{
				int16_t lPeakOfDer2 = IndexOfExtremum(Der2, MAX, GLOBAL, PeakOfDer2, lLimitPeakOfDer2,
													StabilityZone, MORE, (float)(Der2->Profile[PeakOfDer2]*0.5), NULL,
													pExpPulse->Profile, LESS, lTreas, 0,
													Der1->Profile, LESS, 0., 0,
													CD1P, LESS, 0., 0,
													CD2P, MORE, 0., OtherStabilityZone);
				if (lPeakOfDer2 > PeakOfDer2)
				{
					PeakOfDer2 = lPeakOfDer2;
				}
			}
		}
		// If not found, extract ED from Der2 where Central.Der2 is positive without accounting stability
		if (PeakOfDer2 < 0)
		{
			PeakOfDer2 = IndexOfExtremum(Der2, MAX, GLOBAL, lEDBegin, lLimitPeakOfDer2,
										StabilityZone, MORE, 0., NULL,
										pExpPulse->Profile, LESS, lTreas, 0,
										Der1->Profile, LESS, 0., 0,
										CD1P, LESS, 0., 0,
										CD2P, MORE, 0., 0);
		}
		// If not found, extract ED from Der2 without accounting Central.Der
		if (EDMin < 0 && PeakOfDer2 < 0)
		{
			PeakOfDer2 = IndexOfExtremum(Der2, MAX, GLOBAL, lEDBegin, lLimitPeakOfDer2,
										StabilityZone, MORE, 0., NULL,
										pExpPulse->Profile, LESS, lTreas, 0,
										Der1->Profile, LESS, 0., 0,
										CD1P, LESS, 0., 0,
										NULL, LESS, DEFAULT_VALUE, 0);
		}
		// If not found, extract ED from Der2 decreasing Stability Zone
		if (EDMin < 0 && PeakOfDer2 < 0)
		{
			PeakOfDer2 = IndexOfExtremum(Der2, MAX, FIRST, lEDBegin, lLimitPeakOfDer2,
										OtherStabilityZone, MORE, 0., NULL,
										pExpPulse->Profile, LESS, lTreas, 0,
										Der1->Profile, LESS, 0., 0,
										CD1P, LESS, 0., 0,
										NULL, LESS, DEFAULT_VALUE, 0);
		}
		// If not found, extract ED from Der2 decreasing Stability Zone one more
		if (EDMin < 0 && PeakOfDer2 < 0)
		{
			PeakOfDer2 = IndexOfExtremum(Der2, MAX, FIRST, lEDBegin, lLimitPeakOfDer2,
										OtherStabilityZone/2, MORE, 0., NULL,
										pExpPulse->Profile, LESS, lTreas, 0,
										Der1->Profile, LESS, 0., 0,
										CD1P, LESS, 0., 0,
										NULL, LESS, DEFAULT_VALUE, 0);
		}

		// Work out EndT2 - limit zone for T2
		EndT2 = max(EDMin, PeakOfDer2);

		// If EndT2 (ED Candidate) not found, set it as DefaultED
		// If ED found, Decrease EndT2 to prevent finding T2 very close to ED
		if (EndT2 > 0)
		{
			EndT2 -= StabilityZone;
		}
		else
		{
			EndT2 = (lDefaultED > lEDBegin ? lDefaultED : L);
		}
	}
	
	// Now try to find T1, T2 in window [Begin, EndT2]

	// Distinquish between different types of pulses
	OurCase = 0;
	while (true)
	{
		PeakBeforeMain = IndexOfExtremum(pExpPulse, MAX, FIRST, Begin, MainPeak - LocalZone,
										OtherStabilityZone, MORE, 0., Der2->Profile,
										NULL, LESS, DEFAULT_VALUE, 0,
										NULL, LESS, DEFAULT_VALUE, 0,
										NULL, LESS, DEFAULT_VALUE, 0,
										NULL, LESS, DEFAULT_VALUE, 0);
		if (PeakBeforeMain > 0) // If found
		{
			T1 = PeakBeforeMain;
			T2 = MainPeak;
			OurCase = 1;
			QualityT1 = VERYSTRONG;
			QualityT2 = VERYSTRONG;
			break;
		}
		
		// Find first peak between main peak and EndT2
		PeakAfterMain = IndexOfExtremum(pExpPulse, MAX, FIRST, (int16_t)(MainPeak + t60msec), EndT2,
										OtherStabilityZone, MORE, 0., Der2->Profile,
										NULL, LESS, DEFAULT_VALUE, 0,
										NULL, LESS, DEFAULT_VALUE, 0,
										NULL, LESS, DEFAULT_VALUE, 0,
										NULL, LESS, DEFAULT_VALUE, 0);
		if (PeakAfterMain > 0) // If found
		{
			T1 = MainPeak;
			T2 = PeakAfterMain;
			QualityT1 = VERYSTRONG;
			QualityT2 = VERYSTRONG;
			OurCase = 2;
			break;
		}
		
		ShoulderBeforePeak = IndexOfExtremum(Der3, MAX, GLOBAL, Begin, MainPeak - LocalZone,
											OtherStabilityZone, MORE, 0., NULL,
											NULL, LESS, DEFAULT_VALUE, 0,
											NULL, LESS, DEFAULT_VALUE, 0,
											NULL, LESS, DEFAULT_VALUE, 0,
											NULL, LESS, DEFAULT_VALUE, 0);
		ShoulderAfterPeak  = IndexOfExtremum(Der2, MIN, GLOBAL, MainPeak + LocalZone, EndT2,
											StabilityZone, LESS, DEFAULT_VALUE, NULL,
											NULL, LESS, DEFAULT_VALUE, 0,
											NULL, LESS, DEFAULT_VALUE, 0,
											NULL, LESS, DEFAULT_VALUE, 0,
											NULL, LESS, DEFAULT_VALUE, 0);
		// Shoulder before peak found
		if ((ShoulderAfterPeak < 0) && (ShoulderBeforePeak > 0))
		{
			T1 = ShoulderBeforePeak;
			T2 = MainPeak;
			QualityT1 = STRONG;
			QualityT2 = STRONG;
			OurCase = 33;
			break;
		}
		// Check ShoulderAfterPeak found
		if ((ShoulderAfterPeak > 0) && (ShoulderBeforePeak < 0))
		{
			T1 = MainPeak;
			QualityT1 = STRONG;
			T2m = IndexOfExtremum(Der3, MIN, GLOBAL, MainPeak + LocalZone, ShoulderAfterPeak,
								StabilityZone, LESS, DEFAULT_VALUE, NULL,
								Der1->Profile, LESS, 0, StabilityZone,
								NULL, LESS, DEFAULT_VALUE, 0,
								NULL, LESS, DEFAULT_VALUE, 0,
								NULL, LESS, DEFAULT_VALUE, 0);
			if (T2m > 0)
			{
				T2 = T2m;
				QualityT2 = STRONG;
				OurCase = 34;
			}
			else
			{
				T2 = ShoulderAfterPeak;
				QualityT2 = WEAK;
				OurCase = 24;
			}
			break;
		}
		
		// Both shoulders found
		if ((ShoulderBeforePeak > 0) && (ShoulderAfterPeak > 0))
		{
			// Both shoulders exist. Seems flat area here
			T2m = IndexOfExtremum(Der3, MIN, GLOBAL, MainPeak + OtherStabilityZone, ShoulderAfterPeak,
								OtherStabilityZone, LESS, DEFAULT_VALUE, NULL,
								Der1->Profile, LESS, 0, OtherStabilityZone,
								NULL, LESS, DEFAULT_VALUE, 0,
								NULL, LESS, DEFAULT_VALUE, 0,
								NULL, LESS, DEFAULT_VALUE, 0);
			if (T2m < 0)
			{
				T1 = ShoulderBeforePeak;
				T2 = MainPeak;
				QualityT1 = STRONG;
				QualityT2 = WEAK;
				OurCase = 35;
				break;
			}
			
			// Shoulders as Der3 before and after peak exist
			// try to find shoulder length
			float P0 = fabs(pExpPulse->Profile[pExpPulse->Start]);
			float P1 = fabs(PressureValue((float)ShoulderBeforePeak, pExpPulse)) - P0;
			float P2 = fabs(PressureValue((float)T2m, pExpPulse)) - P0;
			float Pt = fabs(PressureValue((float)MainPeak, pExpPulse)) - P0;
			float L1 = sqrt(pow(P1-Pt,2) + pow((float)(ShoulderBeforePeak-MainPeak),2));
			float L2 = sqrt(pow(P2-Pt,2) + pow((float)(T2m - MainPeak),2));
			if (P1 >= Pt || P2 >= Pt || L1 <= 0 || L2 <= 0)
			{
				T1 = ShoulderBeforePeak;
				T2 = MainPeak;
				QualityT1 = VERYWEAK;
				QualityT2 = WEAK;
				OurCase = 35;
				break;
			}
			
			// Check T1 limits
			float BeforePeakTime = IndexToTime(ShoulderBeforePeak, pExpPulse);
			float PeakTime = IndexToTime(MainPeak, pExpPulse);
			if ((PeakTime > PWA_MAX_T1) && (BeforePeakTime >= PWA_MIN_T1))
			{
				T1 = ShoulderBeforePeak;
				T2 = MainPeak;
				QualityT1 = STRONG;
				QualityT2 = WEAK;
				OurCase = 35;
				break;
			}

			if ((BeforePeakTime < PWA_MIN_T1) && (PeakTime <= PWA_MAX_T1))
			{
				T1 = MainPeak;
				T2 = T2m;
				QualityT1 = WEAK;
				QualityT2 = STRONG;
				OurCase = 36;
				break;
			}
			
			// Compare shoulders
			if (L1 >= L2)
			{
				T1 = ShoulderBeforePeak;
				T2 = MainPeak;
				QualityT1 = STRONG;
				QualityT2 = WEAK;
				OurCase = 35;
				break;
			}
			else
			{
				T1 = MainPeak;
				T2 = T2m;
				QualityT1 = WEAK;
				QualityT2 = STRONG;
				OurCase = 36;
				break;
			}
		}			
		
		// No shoulders found.
		// Last chance to get very weak T1 as a negative max of der3
		// Usually for very slow HR
		ShoulderBeforePeak = IndexOfExtremum(Der3, MAX, GLOBAL, Begin, MainPeak - LocalZone,
											OtherStabilityZone, LESS, DEFAULT_VALUE, NULL,
											NULL, LESS, DEFAULT_VALUE, 0,
											NULL, LESS, DEFAULT_VALUE, 0,
											NULL, LESS, DEFAULT_VALUE, 0,
											NULL, LESS, DEFAULT_VALUE, 0);
		if (ShoulderBeforePeak > 0)
		{
			T1 = ShoulderBeforePeak;
			T2 = MainPeak;
			QualityT1 = VERYWEAK;
			QualityT2 = STRONG;
			OurCase = 39;
			break;
		}
		
		// The last break.
		T1 = MainPeak;
		T2 = DEFAULT_VALUE;
		QualityT1 = STRONG;
		QualityT2 = WEAK;
		OurCase = 50;
		break;
	}
	
	
	// Now T1, T2 found (if T2 exist)

	// Calculate ED for Peripheral
	if (pED < 0 || pED == DEFAULT_VALUE)
	{
		// lBegin - left ED window after T2
		int16_t lBegin = (T2 > 0 && T2 != DEFAULT_VALUE ? max(T2 + StabilityZone, lEDBegin) : max(T1 + LocalZone, lEDBegin));
		// Increase EndT2 to catch sharp min
		if (EndT2 > 0)
		{
			EndT2 += 2*StabilityZone; // Shift right EndT2 to catch srtong EndT2
		}
		int16_t lEndOfDer2 = (EDMin > 0 ? EDMin : EndT2);
		// Trying to find ED
		while (true)
		{
			// Find ED as a feature of Der2 with accounting Central.Der2 > 0 in OtherStabilityZone
			ED = IndexOfExtremum(Der2, MAX, GLOBAL, lBegin, lEndOfDer2,
								StabilityZone, MORE, 0., NULL,
								Der1->Profile, LESS, 0., 0,
								CD1P, LESS, 0., 0,
								CD2P, MORE, 0., OtherStabilityZone,
								NULL, LESS, DEFAULT_VALUE, 0);
			if (ED > 0)
			{
				QualityED = VERYSTRONG;
				break;
			}
			
			ED = IndexOfExtremum(Der2, MAX, GLOBAL, lBegin, lEndOfDer2,
								StabilityZone, MORE, 0., NULL,
								Der1->Profile, LESS, 0., 0,
								CD1P, LESS, 0., 0,
								CD2P, MORE, 0., 0,
								NULL, LESS, DEFAULT_VALUE, 0);
			if (ED > 0)
			{
				QualityED = STRONG;
				break;
			}
			// If not found, do not account Central Der2
			if (EDMin < 0 && T2 != DEFAULT_VALUE)
			{
				ED = IndexOfExtremum(Der2, MAX, GLOBAL, lBegin, lEndOfDer2,
									StabilityZone, MORE, 0., NULL,
									Der1->Profile, LESS, 0., 0,
									CD1P, LESS, 0., 0,
									NULL, LESS, DEFAULT_VALUE, 0,
									NULL, LESS, DEFAULT_VALUE, 0);
			}
			if (ED > 0)
			{
				QualityED = STRONG;
				break;
			}

			// If not found, decrease stability zone
			if (EDMin < 0 && T2 != DEFAULT_VALUE)
			{
				ED = IndexOfExtremum(Der2, MAX, FIRST, lBegin, lEndOfDer2,
									OtherStabilityZone, MORE, 0., NULL,
									Der1->Profile, LESS, 0., 0,
									CD1P, LESS, 0., 0,
									NULL, LESS, DEFAULT_VALUE, 0,
									NULL, LESS, DEFAULT_VALUE, 0);
			}
			if (ED > 0)
			{
				QualityED = STRONG;
				break;
			}
			if (EDMin > 0 && T2 != DEFAULT_VALUE)
			{
				ED = IndexOfExtremum(Der2, MAX, FIRST, lBegin, lEndOfDer2,
									OtherStabilityZone, MORE, 0., NULL,
									Der1->Profile, LESS, 0., 0,
									CD1P, LESS, 0., 0,
									NULL, LESS, DEFAULT_VALUE, 0,
									NULL, LESS, DEFAULT_VALUE, 0);
			}
			if (ED > 0)
			{
				QualityED = WEAK;
				break;
			}
			// If not found, but sharp min exist, take it as ED
			if (EDMin > 0 && (float)EDMin/lLength > 0.20 && (float)EDMin/lLength < 0.50)
			{
				ED = EDMin;
				QualityED = WEAK;
				break;
			}
			// If not found, avoid stability zone
			ED = IndexOfExtremum(Der2, MAX, FIRST, lBegin, lEndOfDer2,
								0, MORE, 0., NULL,
								Der1->Profile, LESS, 0., 0,
								CD1P, LESS, 0., 0,
								NULL, LESS, DEFAULT_VALUE, 0,
								NULL, LESS, DEFAULT_VALUE, 0);
			if (ED > 0)
			{
				QualityED = WEAK;
				break;
			}

			// Increase window where ED can be up to L

			// Try to find Weak ED after increasing EndT2
			ED = IndexOfExtremum(Der2, MAX, GLOBAL, lBegin, L,
								StabilityZone, MORE, 0., NULL,
								Der1->Profile, LESS, 0., 0,
								CD1P, LESS, 0., 0,
								CD2P, MORE, 0., OtherStabilityZone,
								NULL, LESS, DEFAULT_VALUE, 0);
			if (ED > 0)
			{
				QualityED = WEAK;
				break;
			}
			// If not found, do not account Central Der2
			ED = IndexOfExtremum(Der2, MAX, GLOBAL, lBegin, L,
								StabilityZone, MORE, 0., NULL,
								Der1->Profile, LESS, 0., 0,
								CD1P, LESS, 0., 0,
								NULL, LESS, DEFAULT_VALUE, 0,
								NULL, LESS, DEFAULT_VALUE, 0);
			if (ED > 0)
			{
				QualityED = WEAK;
				break;
			}
			// If not found, try to find sharp minimum with accounting Central Der2
			ED = IndexOfExtremum(pExpPulse, MIN, GLOBAL, lBegin, L,
								StabilityZone, LESS, lTreas, Der2->Profile,
								Der1->Profile, LESS, 0., 0,
								CD1P, LESS, 0., 0,
								CD2P, MORE, 0., 0,
								NULL, LESS, DEFAULT_VALUE, 0);
			if (ED > 0)
			{
				QualityED = WEAK;
				break;
			}

			// If not found, try to find sharp minimum without accounting Central Der
			ED = IndexOfExtremum(pExpPulse, MIN, FIRST, lBegin, L,
								StabilityZone, LESS, DEFAULT_VALUE, NULL,
								NULL, LESS, DEFAULT_VALUE, 0,
								NULL, LESS, DEFAULT_VALUE, 0,
								NULL, LESS, DEFAULT_VALUE, 0,
								NULL, LESS, DEFAULT_VALUE, 0);
			if (ED > 0)
			{
				QualityED = VERYWEAK;
				break;
			}
			// If not found, avoid stability zone
			ED = IndexOfExtremum(Der2, MAX, FIRST, lBegin, L,
								0, MORE, 0., NULL,
								NULL, LESS, DEFAULT_VALUE, 0,
								NULL, LESS, DEFAULT_VALUE, 0,
								NULL, LESS, DEFAULT_VALUE, 0,
								NULL, LESS, DEFAULT_VALUE, 0);
			if (ED > 0)
			{
				QualityED = VERYWEAK;
				break;
			}

			// If still not found, try to find Weak ED after increasing window up to 65% of pulse length
			int16_t index = 0;
			Math_TimeToIndex((float)lEdMax, pExpandFactor, pSampleRate, &index);
			int16_t lEnd = min((int16_t)(lLength*ED_MAX_PERCENT), index);
			ED = IndexOfExtremum(Der2, MAX, GLOBAL, lBegin, lEnd,
								StabilityZone, MORE, 0., NULL,
								Der1->Profile, LESS, 0., 0,
								CD1P, LESS, 0., 0,
								CD2P, MORE, 0., OtherStabilityZone,
								NULL, LESS, DEFAULT_VALUE, 0);
			if (ED > 0)
			{
				QualityED = WEAK;
				break;
			}
			ED = IndexOfExtremum(Der2, MAX, GLOBAL, lBegin, lEnd,
								StabilityZone, MORE, 0., NULL,
								Der1->Profile, LESS, 0., 0,
								CD1P, LESS, 0., 0,
								NULL, LESS, DEFAULT_VALUE, 0,
								NULL, LESS, DEFAULT_VALUE, 0);
			if (ED > 0)
			{
				QualityED = WEAK;
				break;
			}
			ED = IndexOfExtremum(pExpPulse, MIN, GLOBAL, lBegin, lEnd,
								StabilityZone, LESS, lTreas, Der2->Profile,
								CD1P, LESS, 0., 0,
								CD2P, MORE, 0., 0,
								NULL, LESS, DEFAULT_VALUE, 0,
								NULL, LESS, DEFAULT_VALUE, 0);
			if (ED > 0)
			{
				QualityED = WEAK;
				break;
			}
			ED = IndexOfExtremum(pExpPulse, MIN, FIRST, lBegin, lEnd,
								StabilityZone, MORE, 0., NULL,
								NULL, LESS, DEFAULT_VALUE, 0,
								NULL, LESS, DEFAULT_VALUE, 0,
								NULL, LESS, DEFAULT_VALUE, 0,
								NULL, LESS, DEFAULT_VALUE, 0);
			if (ED > 0)
			{
				QualityED = VERYWEAK;
				break;
			}
			ED = IndexOfExtremum(Der2, MAX, FIRST, lBegin, lEnd,
								0, MORE, 0., NULL,
								NULL, LESS, DEFAULT_VALUE, 0,
								NULL, LESS, DEFAULT_VALUE, 0,
								NULL, LESS, DEFAULT_VALUE, 0,
								NULL, LESS, DEFAULT_VALUE, 0);
			if (ED > 0)
			{
				QualityED = VERYWEAK;
				break;
			}
			
			break;
		}
	}
	// Calculate Time of reflected wave Tr between T1 and ED
	// (only for Central wave)
	else
	{
		if (ED > 0 && ED != DEFAULT_VALUE && T1 > 0)
		{
			Tr = IndexOfExtremum(Der2, MAX, GLOBAL, T1, ED - StabilityZone,
								StabilityZone, LESS, DEFAULT_VALUE, NULL,
								NULL, LESS, DEFAULT_VALUE, 0,
								NULL, LESS, DEFAULT_VALUE, 0,
								NULL, LESS, DEFAULT_VALUE, 0,
								NULL, LESS, DEFAULT_VALUE, 0);
			if (Tr >= T2)
			{
				Tr = DEFAULT_VALUE;
			}
		}
	}
	
	
	// Now T1, T2, ED should be found
	// Extra validation
	if (ED < 0)
	{
		ED = DEFAULT_VALUE;
		QualityED = DEFAULT_VALUE;
	}
	// T1, T2
	if (T1 < 0)
	{
		T1 = MainPeak;
		T2 = DEFAULT_VALUE;
		QualityT1 = WEAK;
		QualityT2 = DEFAULT_VALUE;
		OurCase = -1;
	}
	else if (T2 < T1)
	{
		T2 = DEFAULT_VALUE;
		QualityT2 = DEFAULT_VALUE;
		OurCase = -1;
	}
	else if (ED > 0 && (T2 > 0 && T2 != DEFAULT_VALUE) && ED < T2)
	{
		ED = DEFAULT_VALUE;
		QualityED = DEFAULT_VALUE;
		OurCase = -1;
	}
	
	
UpdateParameters:
	if (pPeriphParams != NULL)
	{
		pPeriphParams->ExpPulse_T1 = T1;
		pPeriphParams->ExpPulse_T2 = T2;
		pPeriphParams->ExpPulse_ED = ED;
		pPeriphParams->ExpPulse_T2m = T2m;
		pPeriphParams->ExpPulse_ShoulderAfterPeak = ShoulderAfterPeak;
		pPeriphParams->QualityT1 = QualityT1;
	}
	else if (pCentralParams != NULL)
	{
		pCentralParams->ExpPulse_T1 = T1;
		pCentralParams->ExpPulse_T2 = T2;
	}
}

/* ###########################################################################
 ** IndexToTime()
 **
 ** DESCRIPTION
 **  Convert Index into time in msec for ExpPulse
 ** INPUT
 **  pIndex - index
 **  pExpPulse
 ** OUTPUT
 ** RETURN
 **  time
*/
float IndexToTime(const int16_t pIndex, const Pulse *pExpPulse)
{
	float lTime = 0;
	lTime = (pIndex - pExpPulse->Start) * ((float)1000/(MEAS_DEFAULT_SAMPLE_RATE*EXPPULSE_MAX_EXPAND_FACTOR));
	return lTime;
}

/* ###########################################################################
 ** TimeToIndex()
 **
 ** DESCRIPTION
 **  Convert Time into index assuming 0 correspond to start point
 ** INPUT
 **  float pTime, pExpPulse
 ** OUTPUT
 ** RETURN
 **  ind - Index
*/
int16_t TimeToIndex(const float pTime, const Pulse *pExpPulse)
{
	int16_t ind = 0;
	
	if (Math_Round(pTime * ((MEAS_DEFAULT_SAMPLE_RATE*EXPPULSE_MAX_EXPAND_FACTOR)/(float)1000), &ind))
	{
		ind += pExpPulse->Start;
	}
	if (ind > pExpPulse->End || ind < pExpPulse->Start)
	{
		print_debug("Warning: Time value is out of Pulse range.\r\n");
	}
	
	return ind;
}

/* ###########################################################################
 ** MaxDerivative1()
 **
 ** DESCRIPTION
 **  Find maximum the 1st derivative of ExpPulse
 ** INPUT
 **  pSmoothOrder, pExpPulse
 **  i1, i2 > i1 - indexes
 ** OUTPUT
 ** RETURN
 **  Maximum value
*/
float MaxDerivative1(const int16_t i1, const int16_t i2, const int16_t pSmoothOrder, const Pulse *pExpPulse)
{
	float lMaxDer1 = DEFAULT_VALUE;
	float* lDer1 = NULL;

	// Validate pulse
	if (Validate(pExpPulse)==false)
	{
		return lMaxDer1;
	}		
	// Validate interval
	if (i1 >= i2)
	{
		return lMaxDer1;
	}		

	// Allocate memory for derivative array
	lDer1 = malloc(sizeof(float) * pExpPulse->FSize);
	if (lDer1 == NULL)
	{
		return lMaxDer1;
	}
	memset(lDer1, 0, sizeof(float) * pExpPulse->FSize);

	// Calculate derivative
	Math_SmoothFirstDerivative(pExpPulse->Profile, pExpPulse->FSize, pSmoothOrder, (float)1, lDer1, &lMaxDer1);

	// Find Max
	lMaxDer1 = lDer1[i1];
	for (int16_t i = i1; i < i2; i++)
	{
		if (lDer1[i] > lMaxDer1)
		{
			lMaxDer1 = lDer1[i];
		}			
	}			

	// Free memory
	free(lDer1);
	lDer1 = NULL;

	return lMaxDer1;
}

/* ###########################################################################
 ** PressureValue()
 **
 ** DESCRIPTION
 **  Find Value of a pulse in x-point pPoint
 ** INPUT
 **  pPulse
 **  pPoint - x-point
 ** OUTPUT
 ** RETURN
 **  Value in this point
*/
float PressureValue(const float pPoint, const Pulse *pPulse)
{
	float lValue = -1;
	// Validate pulse
	if (Validate(pPulse)==false)
	{
		return lValue;
	}		

	// Validate pPoint
	if (pPoint < pPulse->Start || pPoint > pPulse->End)
	{
		PWA_Error_Code = PWA_MSG_POINT_OUT_OF_PULSE;
		print_debug("Error(%d): Point is out of Pulse range. Point, Pulse Begin = %d, End = %d.\r\n", PWA_Error_Code, pPulse->Start, pPulse->End);
		return lValue;
	}
	// Catch start point
	if (pPoint == pPulse->Start)
	{
		return pPulse->Profile[pPulse->Start];
	}		

	// Finding Value
	for (int16_t i = pPulse->Start + 1; i <= pPulse->End; i++)
	{
		float moment = (float)i;
		if (moment >= pPoint)
		{
			// Linear interpolation
			double N1 = moment - pPoint;
			double N2 = 1. - N1;
			lValue = (float)(N1*pPulse->Profile[i-1] + N2*pPulse->Profile[i]);
			return lValue;
		}
	}

	return lValue;
}

/* ###########################################################################
 ** Height()
 **
 ** DESCRIPTION
 **  Find pulse height (Max - Min)
 ** INPUT
 **  pPulse 
 ** OUTPUT
 ** RETURN
 **  Height of pulse
*/
float Height(const Pulse *pPulse)
{
	float lHeight = 0;

	// MinMax
	float lMin=0, lMax=0;
	if (!MinMax(&lMin, &lMax, pPulse))
	{
		return lHeight;
	}
	
	// Height
	lHeight = lMax - lMin;
	return lHeight;
}

/* ###########################################################################
 ** QC_Height()
 **
 ** DESCRIPTION
 **  Find pulse height (Max - Profile[Start])
 ** INPUT
 **  pPulse
 ** OUTPUT
 ** RETURN
 **  Height of Max - Profile[Start]
*/
float QC_Height(const Pulse *pPulse)
{
	float lHeight = 0;

	// MinMax
	float lMin=0, lMax=0;
	if (!MinMax(&lMin, &lMax, pPulse))
	{
		return lHeight;
	}
	
	// Height
	lHeight = lMax - pPulse->Profile[pPulse->Start];
	return lHeight;
}
