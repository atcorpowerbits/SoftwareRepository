/*
 * pwa_signal.c
 *
 * Finding onsets algorithm.
 *
 * Copyright (c) Atcor Medical Pty. Ltd., 2013
 *
 * Created: 11/10/2012 9:45:46 AM
 *  Author: yoonl
 */ 

#include "pwa_signal.h"
#include "math_pwa.h"
#include "pwa_data.h"

/* ###########################################################################
 ** FindOnsets()
 **
 ** DESCRIPTION
 **  Find trigger points (onsets) for a signal
 **  Pulse count = Onset count - 1.
 ** INPUT
 **  All parameters
 ** OUTPUT
 ** RETURN
 **  boolean - return true if found 3 onsets at least.
*/
bool FindOnsets(const uint8_t pAlgorithm, const uint8_t pMinTrigPt, const float *floatSignal, const uint16_t signalLength,
	uint16_t *onsetsLength, int16_t *integerOnsets, float *derivatives1, float *derivatives2)
{
	// Initialise Onsets
	*onsetsLength = 0;
	for(int16_t i = 0; i < PRESSURE_MAX_TPOINTS; i++)
	{
		integerOnsets[i] = -1;
	}

	// Find Derivative 1 and its max
	float lAbsMaxDer1, lMaxDer2, lAvMaxDer1;
	Math_SmoothFirstDerivative(floatSignal, signalLength, 2, 1., derivatives1, &lAbsMaxDer1);
	if (lAbsMaxDer1 <= 0)
	{
		return false;
	}		
	// Try to find Average of the peaks of derivatives1 which is higher
	// then 55% of absolute max of derivatives1
	lAvMaxDer1 = 0;
	int16_t lNofPeaks = 0;
	int16_t lNofLoops = 0;
	do
	{
		int16_t lPeakOfDer1 = pMinTrigPt;
		while (lPeakOfDer1 >= 0)
		{
			Math_IndexOfExtremum(derivatives1, MAX, FIRST, lPeakOfDer1, signalLength,
				MORE, PWA_DER1_THRESHOLD3*lAbsMaxDer1, &lPeakOfDer1);
			if (lPeakOfDer1 >= 0)
			{
				if (derivatives1[lPeakOfDer1] < lAbsMaxDer1) // Avoid largest maximum
				{
					lAvMaxDer1 += derivatives1[lPeakOfDer1];
					lNofPeaks++;
				}
				lPeakOfDer1++;
			}
		}
		// Validate
		if (lNofPeaks > 3)
		{
			lAvMaxDer1 /= lNofPeaks;
			break;
		}
		else
		{
			if (lNofLoops++ < 5)
			{
				lAbsMaxDer1 *= (float)0.9;
			}
			else // To prevent infinite loop
			{
				lAvMaxDer1 = lAbsMaxDer1;
				break;
			}
		}
	} while (lNofPeaks <= 3);

	// Minimal pulse length
	int16_t lMinPulseLength = (int16_t)(60. * MEAS_DEFAULT_SAMPLE_RATE / MAX_HR);

	// Algorithm switch. Algorithm2 must have been executed before other algorithms
	uint8_t outOnsetLength = 0;
	switch (pAlgorithm)
	{
		case PWA_DER2_ALGORITHM:
			Math_SmoothFirstDerivative(derivatives1, signalLength, 2, 1., derivatives2, &lMaxDer2);
			// Find Onsets using Algorithm2
			if (Math_AlgorithmDer2(derivatives1, derivatives2, floatSignal, signalLength, PRESSURE_MAX_TPOINTS,
				lAvMaxDer1, pMinTrigPt, lMinPulseLength, integerOnsets, &outOnsetLength))
			{
				*onsetsLength = outOnsetLength;
				return true;
			}
			*onsetsLength = outOnsetLength;
			break;
		default:
			// PWA uses PWA_DER2_ALGORITHM only
			break;
	}
	return (*onsetsLength > PWA_MIN_NOF_ONSETS);
}