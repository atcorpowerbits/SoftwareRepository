/*
 * pulse.c
 *
 * Created: 17/10/2012 2:03:33 PM
 *  Author: yoonl
 */ 

#include "pulse.h"
#include "math_pwa.h"
#include "usart/usart_rxtx.h"

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
 ** IndexOfMax (), IndexOfMin ()
 **
 ** DESCRIPTION
 **  Find index of Maximal (or Minimal) value for pulse
 **  between indexes i1, i2
 ** INPUT
 **   i1, i2 - indexes, pPulse
 ** OUTPUT
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
 **  Use trapesoid formula to integrate pulse profile on interval [pBegin, pEnd]:
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
		print_debug("Error: wrong pulse.\r\n");
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
 **  boolean change the sign
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
 **  boolean success or not
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
 **  pPeriphParams, pCentralParams
 ** RETURN
 **  boolean success or not
*/
bool FindT1T2ED(const Pulse *pExpPulse, Pulse *Der1, Pulse *Der2, Pulse *Der3, const int8_t pExpandFactor, const int16_t pSampleRate,
	const int16_t pED, const int16_t pCentralMainPeak, const int16_t pPeriphMainPeak, const int16_t pLimitT1T2, float *pCentralDer1_Profile,
	Peripheral_Parameters *pPeriphParams, Central_Parameters *pCentralParams)
{
	// Long codes here ...
	
	return true;
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
		print_debug("Error: The point %f is out of pulse.\r\n", pPoint);
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