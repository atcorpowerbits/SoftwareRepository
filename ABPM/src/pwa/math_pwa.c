/*
 * math_pwa.c
 *
 * Created: 11/10/2012 9:54:03 AM
 *  Author: yoonl
 */ 

#include "math_pwa.h"
#include "pwa_data.h"
#include <math.h>

/* ###########################################################################
 ** Math_SmoothArray()
 **
 ** DESCRIPTION
 **  Smooth array using Running average algorithm
 ** INPUT
 **  pArray[pSize] - float array
 **  pNofFilterPoints - Number of Filter points (usually 5, must be odd)
 ** OUTPUT
 **  pArray rewritten
 ** RETURN
 **  true if success, false otherwise
*/
bool Math_SmoothArray(float *pArray, const uint16_t pSize)
{
	// Validation
	if (pArray == NULL)
	{
		return false;
	}
	if (pSize < 1 || pSize >= DEFAULT_VALUE)
	{
		return false;
	}

	// Allocate memory for new array and copy old into
	float *lSt = (float*)malloc(sizeof(float)*pSize);
	for (uint16_t i=0; i<pSize; i++)
		lSt[i] = pArray[i];

	// Perform running average
	double lSum;
	// smooth (0 to (order-1)) samples
	pArray[0] = (float)((lSt[0] + lSt[1]) / 2.0);
	for(int16_t i = 1; i < DEFAULT_SMOOTH_ORDER; i++)
	{
		lSum = 0;
		int16_t lim = i*2 + 1;
		for(int16_t j = 0; j < lim; j++)
			lSum += lSt[j];
		pArray[i] = (float)(lSum / lim);
	}
	// Smooth middle of a signal
	int16_t lNofFilterPoints = DEFAULT_SMOOTH_ORDER*2 + 1;
	for (uint16_t i = DEFAULT_SMOOTH_ORDER; i < pSize-DEFAULT_SMOOTH_ORDER; i++)
	{
		lSum = 0.;
		for (int16_t j = -DEFAULT_SMOOTH_ORDER; j <= DEFAULT_SMOOTH_ORDER; j++)
			lSum += lSt[i+j];
		pArray[i] = (float)(lSum / lNofFilterPoints);
	}
	// smooth tail
	pArray[pSize - 1] = (float)((lSt[pSize - 1] + lSt[pSize - 2]) / 2.0);
	for(uint16_t i = pSize - DEFAULT_SMOOTH_ORDER; i < pSize - 1; i++)
	{
		lSum = 0;
		uint16_t lim = (pSize - 1 - i)*2 + 1;
		for(uint16_t j = 0; j < lim; j++)
			lSum += lSt[pSize - 1 - j];
		pArray[i] = (float)(lSum / lim);
	}

	// free memory
	free(lSt);
	lSt = NULL;
	
	// Success
	return true;
}

/* ###########################################################################
 ** Math_TimeToIndex(double fvalue)
 **
 ** DESCRIPTION
 **  Convert time in msec into index
 ** INPUT
 **  time
 **  expandRate - rate of upsampling
 **  sampleRate (usually 128) - rate of signal sampling
 ** OUTPUT (RETURN)
 **  none
 ** RETURN
 **  index
*/
bool Math_TimeToIndex(const float time, const uint8_t expandRate, const uint8_t sampleRate, int16_t *index)
{
	// Validation
	if (expandRate < 1 || expandRate >= DEFAULT_VALUE)
	{
		return false;
	}
	if (time <= 0. || time >= DEFAULT_VALUE)
	{
		return false;

	}
	if (sampleRate < 1 || sampleRate >= DEFAULT_VALUE)
	{
		return false;
	}

	// Calculate index
	return Math_Round(time * sampleRate * expandRate / 1000, index);
}

/* ###########################################################################
 ** Math_Round (double fvalue)
 **
 ** DESCRIPTION
 **  Round real numbers to nearest integer
 **		Example :
 **		3.78 -> 4, -3.78 -> -4
 **		3.27 -> 3, -3.27 -> -3
 ** INPUT
 **  input - float value to round
 ** OUTPUT (RETURN)
 **  output
 ** RETURN
 **  boolean success or not
*/
bool Math_Round(float input, int16_t *output)
{
	// Validation
	if (input >= DEFAULT_VALUE || input <= -DEFAULT_VALUE)
	{
		return false;
	}
	
	// Round positive number
	if( input >= 0.0 )
	{
		// Round down
		if ((input - ((long long int) input)) < 0.5)
		{
			*output = (int16_t)floor(input);
		}
		// Round up
		else
		{
			*output = (int16_t)ceil(input);
		}
	}
	// Round negative number
	else
	{
		// Round down
		if ((input - ((long long int)input)) < -0.5 )
		{
			*output = (int16_t)floor(input);
		}
		// Round up
		else
		{
			*output = (int16_t)ceil(input);
		}
	}

	return true;
}

// Round real numbers to nearest integer, but return short for convinent way
int16_t Math_Round_Return(float input)
{
	int16_t ret = 0;
	Math_Round(input, &ret);
	return ret;
}

/* ###########################################################################
 ** Math_SmoothFirstDerivative(...)
 **
 ** DESCRIPTION
 **  Calculate first derivative of a function
 **  using formula after smoothing
 **  f[k]' = 3/[n*(n+1)*(2n+1)] * Sum (j*f[k+j]) , j = -n...n
 ** INPUT
 **  input[size] - function values
 **  step - step of abscissa
 **  smoothOrder = SmoothOrder - Smoothing order
 ** OUTPUT
 **  firstDerivative[NofDer1Points] - first derivative
 **  maximum - maximum value of a derivative
 ** RETURN
 **  none
*/
bool Math_SmoothFirstDerivative(const float* input, const uint16_t size, const int8_t smoothOrder,
	const float step, float* firstDerivative, float* maximum)
{
	// Validation
	if ((smoothOrder < 1) || (size < 2*smoothOrder))
	{
		return false;
	}
	if (step == 0.)
	{
		return false;
	}

	float dt2 = step*2;

	// Start points (ForwardStep formula)
	// firstDerivative[0] = (-3*input[0] + 4*input[1] - input[2]) /dt2;
	firstDerivative[0] = (-input[0] + input[1]) /step;
	// *maximum = firstDerivative[0];
	for (int16_t i = 1; i < smoothOrder; i++)
	{
		// firstDerivative[i] = (input[i+3] - 6*input[i+2] + 18*input[i+1] -10*input[i] - 3*input[i-1]) /12. /step;
		if (i==1)
		{
			firstDerivative[i] = (input[i+1] - input[i-1]) /dt2;
			*maximum = firstDerivative[1];
		}
		else
			firstDerivative[i] = (-2*input[i-2] - input[i-1] + input[i+1] + 2*input[i+2]) /(float)10. /step;
		// firstDerivative[i] = (-3*input[i] +4*input[i+1] - input[i+2]) /dt2;
		if (firstDerivative[i] > *maximum)
			*maximum = firstDerivative[i];
	}

	// Middle points
	double c = ((double)3)/smoothOrder/(smoothOrder + 1)/(2*smoothOrder + 1)/step;
	for (uint16_t i = smoothOrder; i < size - smoothOrder; i++)
	{
		double sum = 0.;
		for (int16_t j = -smoothOrder; j <= smoothOrder; j++)
		{
			if (j!=0) sum += j*input[i+j];
		}
		firstDerivative[i] = (float)(sum * c);
		if (firstDerivative[i] > *maximum)
			*maximum = firstDerivative[i];
	}

	// End points (BackStep formula)
	for (uint16_t i = size - smoothOrder; i < size - 1; i++)
	{
		// firstDerivative[i] = (3*input[i+1] + 10*input[i] - 18*input[i-1] + 6*input[i-2] - input[i-3]) /12. /step;
		if (i==size - 2)
			firstDerivative[i] = (input[i+1] - input[i-1]) /dt2;
		else
			firstDerivative[i] = (-2*input[i-2] - input[i-1] + input[i+1] + 2*input[i+2]) /(float)10. /step;
		if (firstDerivative[i] > *maximum)
			*maximum = firstDerivative[i];
	}
	// firstDerivative[size - 1] = (input[size - 3] - 4*input[size - 2] + 3*input[size - 1]) /dt2;
	firstDerivative[size - 1] = (input[size - 1] - input[size - 2]) /step;
	// if (firstDerivative[size - 1] > *maximum)
	//  *maximum = firstDerivative[size - 1];

	return true;
}

/* ###########################################################################
 ** Math_GetSplineIndex(x, SplineIndex, SplineOrder, pPulse.Length);
 **
 ** DESCRIPTION
 **  Find SplineIndex (beginning of a spline) for pulse
 ** INPUT
 **  abscissa - abscissa of a point on a Pulse
 **  SplineIndex - old SplineIndex
 **  size - length of a pulse
 ** OUTPUT
 **  newSplineIndex - new spline index
 ** RETURN
 **  bool success or not
*/
bool Math_GetSplineIndex(const float abscissa, const uint16_t splineIndex, const uint16_t size, uint16_t *newSplineIndex)
{
	// Validation
	if (abscissa < 0 || abscissa >= DEFAULT_VALUE)
	{
		return false;
	}
	if (splineIndex >= DEFAULT_VALUE)
	{
		return false;
	}
	if (size < 1 || size >= DEFAULT_VALUE)
	{
		return false;
	}
	
	*newSplineIndex = splineIndex;
	
	// Limit point in spline to switch on next spline
	int16_t limit = 2;

	// Step to increment spline initial point
	int16_t step = 1;

	// Special case for the pulse end
	if (abscissa >= size - (DEFAULT_SPLINE_ORDER + 1))
	{
		*newSplineIndex = size - (DEFAULT_SPLINE_ORDER + 1);
	}
	// Check if the limit has been overcome
	else if (abscissa > splineIndex + limit)
	{
		*newSplineIndex += step;
	}
	return true;
}

/* ###########################################################################
 ** Math_Spline(...)
 **
 ** DESCRIPTION
 **  Find a value of polinomial spline approximation of order SplineOrder in point x of
 **  Pulse profile together with derivatives, if their initial values != C999
 ** INPUT
 **  abscissa - abscissa of a point on a Pulse
 **  Profile[SplineOrder + 1] - Pulse section
 **  SplineOrder - order of spline
 ** OUTPUT
 **  derivatives[numOfDerivatives] - derivatives
 ** RETURN
 **  bool success or not
*/
bool Math_Spline(const float abscissa, const float* profile, const int8_t splineOrder, float* value, float *derivatives, const int8_t numOfDerivatives)
{
	// Spline length
	double l = splineOrder; // * Dx;
	double l2 = l*l;
	double l3 = l2*l;

	// Number of Derivatives
	int8_t lNofDer = ((derivatives == NULL || numOfDerivatives <= 0) ? 0 : numOfDerivatives);

	// L-coordinates of spline
	double L2 = abscissa/l;
	double L1 = 1 - L2;

	// Calculate spline basic functions and derivatives
	static double N[5], N1[5], N2[5], N3[5];
	switch (splineOrder)
	{
	  case 1:
		   N[0] = L1;
		   N[1] = L2;
		   if (lNofDer >= 1)
		   {
			 N1[0] = -1./l;
			 N1[1] =  1./l;
		   }
		   break;
	  case 2:
		   N[0] = L1*(2*L1-1);
		   N[1] = 4*L1*L2;
		   N[2] = L2*(2*L2-1);
		   if (lNofDer >= 1)
		   {
			 N1[0] = (1 - 4*L1)/l;
			 N1[1] = 4* (L1 - L2)/l;
			 N1[2] = (4*L2 - 1)/l;
		   }
		   if (lNofDer >= 2)
		   {
			 N2[0] = 4./l2;
			 N2[1] = -8./l2;
			 N2[2] = 4./l2;
		   }
		   break;
	  case 3:
		   N[0] = L1*(3*L1-1)*(3*L1-2)/2;
		   N[1] = 9*L1*L2*(3*L1-1)/2;
		   N[2] = 9*L1*L2*(3*L2-1)/2;
		   N[3] = L2*(3*L2-1)*(3*L2-2)/2;
		   if (lNofDer >= 1)
		   {
			 N1[0] = (-27*L1*L1 + 18*L1 - 2)/(2*l);
			 N1[1] = (-54*L1*L2 + 9*L2 + 27*L1*L1 - 9*L1)/(2*l);
			 N1[2] = (-27*L2*L2 + 9*L2 + 54*L1*L2 - 9*L1)/(2*l);
			 N1[3] = (27*L2*L2 - 18*L2 + 2)/(2*l);
		   }
		   if (lNofDer >= 2)
		   {
			 N2[0] = (54*L1 - 18)/(2*l2);
			 N2[1] = (54*L2 - 108*L1 + 18)/(2*l2);
			 N2[2] = (54*L1 - 108*L2 + 18)/(2*l2);
			 N2[3] = (54*L2 - 18)/(2*l2);
		   }
		   if (lNofDer >= 3)
		   {
			 N3[0] = (-54)/(2*l3);
			 N3[1] = (3*54)/(2*l3);
			 N3[2] = (-3*54)/(2*l3);
			 N3[3] = 54/(2*l3);
		   }
		   break;
	  default:
		   return false;
	}
	/*
	// Check formula correctness (only for testing)
	float Sum = 0., Sum1 = 0., Sum2 = 0., Sum3 = 0.;
	for (int i = 0; i <= splineOrder; i++)
	{
	  Sum  +=  N[i];
	  Sum1 += N1[i];
	  Sum2 += N2[i];
	  Sum3 += N3[i];
	}
	if (fabs(Sum -1) > 1e-4 || fabs(Sum1) > 1e-3 || fabs(Sum2) > 1e-3 || fabs(Sum3) > 1e-3)
	{
	   return false;
	}
	*/
	// Calculate value and derivatives
	double dValue = 0.;  double dDer1  = 0.;  double dDer2  = 0.;  double dDer3  = 0.;
	for (int16_t i = 0; i <= splineOrder; i++)
	{
		dValue += N[i]*profile[i];
		if (lNofDer >= 1) dDer1  += N1[i]*profile[i];
		if (lNofDer >= 2) dDer2  += N2[i]*profile[i];
		if (lNofDer >= 3) dDer3  += N3[i]*profile[i];
	}
	// Return
	*value = (float)dValue;
	if (lNofDer >= 1) derivatives[0] = (float)dDer1;
	if (lNofDer >= 2) derivatives[1] = (float)dDer2;
	if (lNofDer >= 3) derivatives[2] = (float)dDer3;

	return true;
}

/* ###########################################################################
 ** Math_IndexOfExtremum()
 **
 ** DESCRIPTION
 **  Find index of Extremal Maximal (or Minimal) value for pulse
 **  between indexes index1, index2
 ** INPUT
 **  input - derivatives profile
 **  minOrMax, onlyFirst, lessOrMore, lessOrMoreThan
 **  index1, index2 - indexes
 ** OUTPUT
 **  Index or -1 if wrong pulse
 ** RETURN
 **  boolean success or not
*/
bool Math_IndexOfExtremum(const float *input, const bool minOrMax, const bool onlyFirst, const int16_t index1, const int16_t index2,
	const bool lessOrMore, const float lessOrMoreThan, int16_t* index)
{
	*index = -1;
	// Validate interval
	if (index1 >= index2 - 2)
		return false;
	// Find Extremum for Pulse.
	// For maximum extremum is where Current > Last, Current >= Next
	// For minimum extremum is where Current < Last, Current <= Next
	float lCurrent, lLast, lNext;
	for (int16_t i = index1 + 1; i < index2 - 1; i++)
	{
		lCurrent = input[i];
		// Check limit
		if (lessOrMoreThan != DEFAULT_VALUE)
		{
			if (lessOrMore == LESS)
			{
				if (lCurrent >= lessOrMoreThan)
					continue;
			}
			else // if (lessOrMore == MORE)
			{
				if (lCurrent <= lessOrMoreThan)
					continue;
			}
		}
		lLast = input[i-1];
		lNext = input[i+1];
		// Check conditions for Max or Min
		if (minOrMax == MAX)
		{
			if (lCurrent <= lLast || lCurrent < lNext)
				continue;
		}
		else // if (minOrMax == MINIMUM)
		{
			if (lCurrent >= lLast || lCurrent > lNext)
				continue;
		}
		// Now lCurrent is extremum.
		// Analise first extremum or not, if necessary
		if (*index < 0)
		{
			*index = i;
			if (onlyFirst == FIRST)
				break;
		}
		else
		{
			if (minOrMax == MAX)
			{
				if (lCurrent > input[*index])
					*index = i;
			}
			else // if (minOrMax == MINIMUM)
			{
				if (lCurrent < input[*index])
					*index = i;
			}
		}
	}

	return true;
}

/* ###########################################################################
 ** AlgorithmDer2()
 **
 ** DESCRIPTION
 **  Find onsets using maxDer2 algorithm
 ** INPUT
 **  derivatives1, derivatives2, floatSignal
 **  signalLength, maximumOnsetsLength
 **  pAvMaxDer1, pMinTrigPt, pMinPulseLength
  ** OUTPUT
 **  integerOnsets - integer array of Onsets
 **  onsetsLength - size of Onsets
 ** RETURN
 **  boolean success or not
*/
bool Math_AlgorithmDer2(float* derivatives1, float* derivatives2, const float* floatSignal,
	uint16_t signalLength, uint16_t maximumOnsetsLength,
	const float pAvMaxDer1, const int16_t pMinTrigPt, const int16_t pMinPulseLength,
	int16_t* integerOnsets, uint8_t* onsetsLength)
{
	// ThresHold values
	float lThresHold1 = PWA_DER1_THRESHOLD1 * pAvMaxDer1;
	float lThresHold2 = PWA_DER1_THRESHOLD2 * pAvMaxDer1;

	// Find Trigger Points
	bool  WeAreInPeak = false;
	bool  Beginning = true;
	int16_t lPeakIndex = -1, lFootIndex;

	// Main loop
	for (uint16_t i = pMinTrigPt; i < signalLength; i++)
	{
		// Avoid signal beginning where values already above threashold
		if (Beginning == true)
		{
			if (derivatives1[i] >= lThresHold1)
				continue;
			Beginning = false;
		}
		// Avoid MinPulseLength zone after last onset being found
		if (*onsetsLength > 0 && (i - integerOnsets[*onsetsLength - 1] < pMinPulseLength))
			continue;
		// Find Peak
		// avoid beginning of a wave
		if ((WeAreInPeak == false) && (derivatives1[i] < lThresHold1))
			continue;

		// Begin of peak
		if (WeAreInPeak==false)
			WeAreInPeak = true;

		if (derivatives1[i] > lThresHold2)
		{
			// We are in Peak first point
			if (lPeakIndex < 0)
			{
				lPeakIndex = i;
				continue;
			}
			// Find max in peak
			if (derivatives1[i] > derivatives1[lPeakIndex])
			{
				lPeakIndex = i;
			}
		}
		else
		{
			WeAreInPeak = false;
			if (lPeakIndex < 0)
				continue;
			// End of Peak. Go back to find point where Signal has minimum;
			int16_t lInitPeakIndex = ((*onsetsLength > 0) ? integerOnsets[*onsetsLength-1] : pMinTrigPt);
			lFootIndex = -1;

			// Find foot points found where Previous > Current
			for (int16_t j = lPeakIndex; j > lInitPeakIndex; j--)
			{
				if (floatSignal[j] <= floatSignal[j-1])
				//if (derivatives1[j] <= 0.)
				{
					lFootIndex = j;
					break;
				}
			}
			if (lFootIndex < 0)
			{
				lPeakIndex = -1;
				continue;
			}

			// Find point where derivatives2 has a positive maximum between lFootIndex and PeakIndex
			float lMaxDer2 = 0.;
			int16_t lIndOfMaxDer2 = -1;
			for (int16_t j = lFootIndex; j < lPeakIndex; j++)
			{
				if (derivatives2[j] > lMaxDer2)
				{
					lIndOfMaxDer2 = j;
					lMaxDer2 = derivatives2[j];
				}
			}
			WeAreInPeak = false;
			// Validate
			if (lIndOfMaxDer2 < 0 || lMaxDer2 <= 0. || lIndOfMaxDer2 <= lInitPeakIndex)
			{
				lPeakIndex = -1;
				continue;
			}
			// After onset has been found
			integerOnsets[*onsetsLength] = (int16_t)lIndOfMaxDer2;
			*onsetsLength = *onsetsLength + 1;
			WeAreInPeak = false;
			lPeakIndex = -1;
			// Check onsetsLength limit. If more, stop process
			if (*onsetsLength == maximumOnsetsLength) break;
		}
	} // End of Main loop

	// return
	return (*onsetsLength > PWA_MIN_NOF_ONSETS);
}