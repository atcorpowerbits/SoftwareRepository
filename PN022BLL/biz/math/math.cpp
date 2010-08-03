/*
    Copyright (C) ATCOR MEDICAL PTY LTD, 2010

    Filename	 :	math.cpp
	
	Author       :  Paul McBryde

    Description  :	DECLARATION of Math Class
*/
#include "stdafx.h"
#include "stdlib.h"
#include "math.h"

using namespace Biz;
using namespace System;

#pragma hdrstop

/**
 ** TimeToIndex
 **
 ** DESCRIPTION
 **  Convert time in msec into index

 ** INPUT
 **  time
 **  expandRate - rate of upsampling
 **  sampleRate (usually 256) - rate of signal sampling

 ** OUTPUT (RETURN)
 **  index

 ** RETURN
 **  bool success or not
*/

bool BizMath::TimeToIndex(const float time, const int expandRate,
                     const int sampleRate, int% index)
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
	BizMath::Round(time * sampleRate * expandRate / 1000., index);
	return true;
}

/** 
 ** IndexToTime
 **
 ** DESCRIPTION
 **  Convert index into time in msec

 ** INPUT
 **  index
 **  expandRate - rate of upsampling
 **  sampleRate (usually 256) - rate of signal sampling

 ** OUTPUT (RETURN)
 **  time

 ** RETURN
 **  bool success or not
*/

bool BizMath::IndexToTime(const int index, const int expandRate,
                       const int sampleRate, float% time)
{
	// Validation
	if (expandRate < 1 || expandRate >= DEFAULT_VALUE)
	{
		return false;  
	}
	if (index < 0 || index >= DEFAULT_VALUE)
	{
		return false;  
	}
	if (sampleRate < 1 || sampleRate >= DEFAULT_VALUE)
	{
		return false;
	}

	// Calculate time
	time = index * (float)1000. / (sampleRate * expandRate);
	return true;
}

/**
 ** Round (double input)
 **
 ** DESCRIPTION
 **  Round real numbers to nearest integer
 **		Example :
 **		3.78 -> 4, -3.78 -> -4
 **		3.27 -> 3, -3.27 -> -3
 **
 ** INPUT
 **  input - double value to round
 **
 ** OUTPUT (RETURN)
 **  output - rounded integer
 **
 ** RETURN
 **  bool success or not
*/

bool BizMath::Round(double input, int% output)
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
			output = Convert::ToInt32(Math::Floor(input));		
		}
		// Round up
		else
		{
			output = Convert::ToInt32(Math::Ceiling(input));	
		}
	}
	// Round negative number
	else
	{
		// Round down
		if ((input - ((long long int)input)) < -0.5 )
		{
			output = Convert::ToInt32(Math::Floor(input));		
		}
		// Round up
		else
		{
			output = Convert::ToInt32(Math::Ceiling(input));	
		}
	}

	return true;
}

/**
 ** RoundNearest20 (int input)
 **
 ** DESCRIPTION
 **  Round integers to nearest multiple of 20
 **		Example :
 **		110 -> 120, -110 -> -100
 **     109 -> 100, -111 -> -120

 ** INPUT
 **  input - integer value to round

 ** OUTPUT (RETURN)
 **  output - rounded integer

 ** RETURN
 **  bool success or not
*/

bool BizMath::RoundNearest20(int input, int% output)
{
	int multiple;
	int remainder;

	// Validation
	if (input >= DEFAULT_VALUE || input <= -DEFAULT_VALUE)
	{
		return false;
	}

	// Round positive number
	if( input >= 0.0 )
	{
		multiple = input / 20;
		remainder = input % 20;
		// Round down
		if (remainder < 10)
		{
			output = 20 * multiple;		   
		}
		// Round up
		else
		{
			output = 20 * (multiple + 1);	
		}
	}
	// Round negative number
	else
	{
		multiple = input / 20;
		remainder = input % 20;
		// Round down
		if (remainder < -10)
		{
			output = 20 * (multiple - 1);	
		}
		// Round up
		else
		{
			output = 20 * multiple;			
		}
	}

	return true;
}

/**
 ** SmoothDerivative1(...)
 **
 ** DESCRIPTION
 **  Calculate first derivative of a function
 **  using formula after smoothing
 **  input[k]' = 3/[n*(n+1)*(2n+1)] * Sum (j*input[k+j]) , j = -n...n

 ** INPUT
 **  input[size] - function values
 **  step - step of abscissa
 **  n - smoothOrder - Smoothing order

 ** OUTPUT
 **  firstDerivative[size] - first derivative
 **  maximum - maximum value of a derivative (cannot be the first or last 2 points)

 ** RETURN
 **  bool success or not
*/

bool BizMath::SmoothDerivative1(array<const float>^ input, const int size, const int smoothOrder,
                            const float step, array<float>^ firstDerivative, float% maximum)
{

	// Validation
	if (smoothOrder < 1 || smoothOrder >= DEFAULT_VALUE)
	{
		return false;
	}
	if (size < 2*smoothOrder || size > input->Length)
	{
		return false;
	}
	if (step == 0. || step <= -DEFAULT_VALUE || step >= DEFAULT_VALUE) 
	{
		return false;
	}

	float doubleStep = step*2;

	// First point
	firstDerivative[0] = (-input[0] + input[1]) /step;
	
	// Start points (ForwardStep formula)
	for (int i = 1; i < smoothOrder; i++)
	{
		if (i == 1)
		{
			firstDerivative[i] = (input[i+1] - input[i-1]) /doubleStep;
		}
		else
		{
			firstDerivative[i] = (-2*input[i-2] - input[i-1] + input[i+1] + 2*input[i+2]) / ((float)10. * step);
		}
	}

	// Middle points
	float smoothingCoefficient = float(3)/(smoothOrder * (smoothOrder + 1) * (2*smoothOrder + 1)* step);
	for (int i = smoothOrder; i < size - smoothOrder; i++)
	{
		float sum = 0.;
		for (int j = -smoothOrder; j <= smoothOrder; j++)
		{
			if (j != 0) 
			{
				sum += j * input[i + j];
			}
		}
		firstDerivative[i] = sum * smoothingCoefficient;
	}

	// End points (BackStep formula)
	for (int i = size - smoothOrder; i < size - 1; i++)
	{
		if (i == size - 2)
		{
			firstDerivative[i] = (input[i+1] - input[i-1]) /doubleStep;
		}
		else
		{
			firstDerivative[i] = (-2*input[i-2] - input[i-1] + input[i+1] + 2*input[i+2]) / ((float)10. * step);
		}
	}
  
	// Last point
	firstDerivative[size - 1] = (input[size - 1] - input[size - 2]) /step;

	// Find the maximum, not including the first or last 2 points
	array<const float>^ subset = gcnew array<const float>(size - 3);
	Array::Copy(firstDerivative, 1, subset, 0, size - 3);
	if (MaxInArray(subset, size - 3, maximum) == false)
	{
		return false;
	}
	return true;
}
/**
 ** MaxInArray(...),  MinInArray(...),  MinMaxInArray(...)
 **
 ** DESCRIPTION
 **  find maximum/minimum value in array

 ** INPUT
 **  input[pSize] - array

 ** OUTPUT (RETURN)
 **  maximum/minimum value

 ** RETURN
 ** bool success or not
*/

bool BizMath::MaxInArray (array<const float>^ input, int size, float% maximum)
{
	// Validation
	if (size < 1 || size >= DEFAULT_VALUE || size > input->Length)
		return false;

	maximum = input[0];
	// Find the maximum in the array
	for (int i = 0; i < size; i++)
	{
		// Validation
		if (input[i] >= DEFAULT_VALUE || input[i] <= -DEFAULT_VALUE)
		{
			return false;
		}
		else if (input[i] > maximum)
		{
			maximum = input[i];
		}
	}
	return true;
}

bool BizMath::MinInArray (array<const float>^ input, int size, float% minimum)
{
	// Validation
	if (size < 1 || size >= DEFAULT_VALUE || size > input->Length)
		return false;

	minimum = input[0];
	// Find the minimum in the array
	for (int i = 0; i < size; i++)
	{
		// Validation
		if (input[i] >= DEFAULT_VALUE || input[i] <= -DEFAULT_VALUE)
		{
			return false;
		}
		else if (input[i] < minimum)
		{
			minimum = input[i];
		}
	}
	return true;
}
//---------------------------------------------------------------------------
bool BizMath::MinMaxInArray (array<const float>^ input, int size, float% minimum, float% maximum)
{
	// Validation
	if (size < 1 || size >= DEFAULT_VALUE || size > input->Length)
		return false;

	maximum = input[0];
	minimum = input[0];
	// Find the minimum and maximum in the array
	for (int i = 0; i < size; i++)
	{
		// Validation
		if (input[i] >= DEFAULT_VALUE || input[i] <= -DEFAULT_VALUE)
		{
			return false;
		}
		if (input[i] > maximum)
		{
			maximum = input[i];
		}
		if (input[i] < minimum)
		{
			minimum = input[i];
		}
	}
	return true;
}

//---------------------------------------------------------------------------
bool BizMath::MinMaxInArray (array<const short int>^ input, int size, short int% minimum, short int% maximum)
{
	// Validation
	if (size < 1 || size >= DEFAULT_VALUE || size > input->Length)
		return false;

	maximum = input[0];
	minimum = input[0];
	// Find the minimum and maximum in the array
	for (int i = 0; i < size; i++)
	{
		// Validation
		if (input[i] >= DEFAULT_VALUE || input[i] <= -DEFAULT_VALUE)
		{
			return false;
		}
		if (input[i] > maximum)
		{
			maximum = input[i];
		}
		if (input[i] < minimum)
		{
			minimum = input[i];
		}
	}
	return true;
}

/*
** Find the index of where the maximum resides within an array.
*/
bool BizMath::MaxInArrayIndex(array<const float>^ input, int size, int% maximumIndex)
{
	// Validation
	if (size < 1 || size >= DEFAULT_VALUE || size > input->Length)
		return false;
	
	float maximum = input[0];
	maximumIndex = 0;
	// Find the index of the maximum in the array
	for (int i = 0; i < size; i++)
	{
		// Validation
		if (input[i] >= DEFAULT_VALUE || input[i] <= -DEFAULT_VALUE)
		{
			return false;
		}
		else if (input[i] > maximum)
		{
			maximum = input[i];
			maximumIndex = i;
		}
	}
	return true;
}

//---------------------------------------------------------------------------
/* ###########################################################################
 ** GetSplineIndex(x, SplineIndex, SplineOrder, pPulse.Length);
 **
 ** DESCRIPTION
 **  Find SplineIndex (beginning of a spline) for pulse
 ** INPUT
 **  x - abscissa of a point on a Pulse
 **  SplineIndex - old SplineIndex
 **  SplineOrder - order of spline
 **  pPulseLength - length of a pulse
 ** OUTPUT
 ** RETURN
 **  NewSplineIndex - new spline index
*/
//---------------------------------------------------------------------------
int BizMath::GetSplineIndex(const float x, const int SplineIndex,
                        const int SplineOrder, const int pPulseLength)
{
  int NewSplineIndex = SplineIndex;
  int SO1 = SplineOrder + 1;

  int Limit; // Limit point in spline to switch on next spline
  int Step;  // Step to increment spline initial point
  switch (SplineOrder)
  {
    case 1:
         Limit = 1;
         Step = 1;
         break;
    case 2:
         Limit = 1;
         Step = 1;
         break;
    case 3:
         Limit = 2;
         Step = 1;
         break;
    case 4:
         Limit = 3;
         Step = 2;
         break;
    case 5:
         Limit = 3;
         Step = 1;
         break;
    default:
         // MsgBox(TERROR, MSG_MATH_ERROR, MSG_WRONG_SPLINE,
         //       LoadStr(MSG_WRONG_SPLINE) + IntToStr(SplineOrder));
         return NewSplineIndex;
  }

  // Special case of pulse end
  if (x >= pPulseLength - SO1)
  {
    NewSplineIndex = pPulseLength - SO1;
  }
  // Check point overcome limit
  else if (x > SplineIndex + Limit)
  {
    NewSplineIndex += Step;
  }
  return NewSplineIndex;
}

/* ###########################################################################
 ** Spline(...)
 **
 ** DESCRIPTION
 **  Find a value of polinomial spline approximation of order SplineOrder in point x of
 **  Pulse profile together with derivatives, if their initial values != C999
 ** INPUT
 **  x - abscissa of a point on a Pulse
 **  Profile[SplineOrder + 1] - Pulse section
 **  SplineOrder - order of spline
 **  // Dx - sample rate
 ** OUTPUT
 **  Der[NofDer] - derivatives
 **  Value - pulse value
 ** RETURN
 **  bool success or not
*/
//-------------------------------------------------------------------------------------------
bool BizMath::Spline(const float x, array<const float>^ Profile, const int SplineOrder,
                 float% Value)
{
	// Initialise
	float *Der = NULL; 
	const int NofDer = 0;
  
	// Spline length
  double l = SplineOrder; // * Dx;
  double l2 = l*l;
  double l3 = l2*l;

  // Number of Derivatives
  int lNofDer = ((Der == NULL || NofDer <= 0) ? 0 : NofDer);

  // L-coordinates of spline
  double L2 = x/l;
  double L1 = 1 - L2;

  // Calculate spline basic functions and derivatives
  static double N[5], N1[5], N2[5], N3[5];
  switch (SplineOrder)
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
         // MsgBox(TERROR, MSG_VALIDATION_ERROR, "Wrong spline order " + IntToStr(SplineOrder));
         return false;
  }
  /*
  // Check formula correctness (only for testing)
  float Sum = 0., Sum1 = 0., Sum2 = 0., Sum3 = 0.;
  for (int i = 0; i <= SplineOrder; i++)
  {
    Sum  +=  N[i];
    Sum1 += N1[i];
    Sum2 += N2[i];
    Sum3 += N3[i];
  }
  if (fabs(Sum -1) > 1e-4 || fabs(Sum1) > 1e-3 || fabs(Sum2) > 1e-3 || fabs(Sum3) > 1e-3)
  {
     MsgBox(TERROR, MSG_VALIDATION_ERROR, "Wrong spline basic functions. Order = " + IntToStr(SplineOrder));
     return false;
  }
  */
  // Calculate value and derivatives
  double dValue = 0.;  double dDer1  = 0.;  double dDer2  = 0.;  double dDer3  = 0.;
  for (int i = 0; i <= SplineOrder; i++)
  {
    dValue += N[i]*Profile[i];
    if (lNofDer >= 1) dDer1  += N1[i]*Profile[i];
    if (lNofDer >= 2) dDer2  += N2[i]*Profile[i];
    if (lNofDer >= 3) dDer3  += N3[i]*Profile[i];
  }
  // Return
  Value = dValue;
  if (lNofDer >= 1) Der[0] = dDer1;
  if (lNofDer >= 2) Der[1] = dDer2;
  if (lNofDer >= 3) Der[2] = dDer3;
  return true;
}

/* ###########################################################################
 ** SmoothArray()
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
//-------------------------------------------------------------------------------------
bool BizMath::SmoothArray(array<float>^ pArray, const int pSize, const int pSmoothOrder)
{
  // Validation
	if ((pSmoothOrder <= 0) || (pSmoothOrder >= pSize - pSmoothOrder))
  {
		return false;
  }
  // Allocate memory for new array and copy old into
	float *lSt = new float[pSize];
  for (int i=0; i<pSize; i++)
    lSt[i] = pArray[i];

  // Perform running average
  double lSum;
	// smooth (0 to (order-1)) samples
	pArray[0] = (lSt[0] + lSt[1]) / 2.0;
	for(int i = 1; i < pSmoothOrder; i++ )
	{
    lSum = 0;
    int lim = i*2 + 1;
		for(int j = 0; j < lim; j++)
			lSum += lSt[j];
		pArray[i] = lSum / lim;
	}
  // Smooth middle of a signal
  int lNofFilterPoints = pSmoothOrder*2 + 1;
	for (int i = pSmoothOrder; i < pSize-pSmoothOrder; i++)
	{
    lSum = 0.;
		for (int j = -pSmoothOrder; j <= pSmoothOrder; j++)
			lSum += lSt[i+j];
		pArray[i] = lSum / lNofFilterPoints;
	}
	// smooth tail
	pArray[pSize - 1] = (lSt[pSize - 1] + lSt[pSize - 2]) / 2.0;
	for(int i = pSize - pSmoothOrder; i < pSize - 1; i++)
	{
    lSum = 0;
    int lim = (pSize - 1 - i)*2 + 1;
		for(int j = 0; j < lim; j++)
			lSum += lSt[pSize - 1 - j];
		pArray[i] = lSum / lim;
	}

  // free memory
	delete [] lSt;

  // Success
	return true;
}

/* ###########################################################################
 ** IndexOfExtremum()
 **
 ** DESCRIPTION
 **  Find index of Extremal Maximal (or Minimal) value for pulse
 **  between indexes i1, i2
 ** INPUT
 **   i1, i2 - indexes
 **  Pulse class
 ** OUTPUT
 **  Index or -1 if wrong pulse
*/
//--------------------------------------------------------------------------------------
int BizMath::IndexOfExtremum(array<const float>^ pProfile, const bool pMinOrMax, const bool pOnlyFirst, const int i1, const int i2,
                         const bool pLessOrMore, const float pLessOrMoreThan)
{
  int ind = -1;
  // Validate interval
  if (i1 >= i2 - 2)
    return ind;
  // Find Extremum for Pulse.
  // For maximum extremum is where Current > Last, Current >= Next
  // For minimum extremum is where Current < Last, Current <= Next
  float lCurrent, lLast, lNext;
  for (int i = i1 + 1; i < i2 - 1; i++)
  {
    lCurrent = pProfile[i];
    // Check limit
	if (pLessOrMoreThan != DEFAULT_VALUE)
    {
      if (pLessOrMore == LESS)
      {
        if (lCurrent >= pLessOrMoreThan)
          continue;
      }
      else // if (pLessOrMore == MORE)
      {
        if (lCurrent <= pLessOrMoreThan)
          continue;
      }
    }
    lLast = pProfile[i-1];
    lNext = pProfile[i+1];
    // Check conditions for Max or Min
    if (pMinOrMax == MAX)
    {
       if (lCurrent <= lLast || lCurrent < lNext)
          continue;
    }
    else // if (pMinOrMax == MINIMUM)
    {
       if (lCurrent >= lLast || lCurrent > lNext)
          continue;
    }
    // Now lCurrent is extremum.
    // Analise first extremum or not, if necessary
    if (ind < 0)
    {
      ind = i;
      if (pOnlyFirst == FIRST)
        break;
    }
    else
    {
      if (pMinOrMax == MAX)
      {
         if (lCurrent > pProfile[ind])
            ind = i;
      }
      else // if (pMinOrMax == MINIMUM)
      {
         if (lCurrent < pProfile[ind])
            ind = i;
      }
    }
  }
  // return
  return ind;
}

/* ###########################################################################
 ** FunctionValue
 **
 ** DESCRIPTION
 **  Find Value of function f at x-point
 ** INPUT
 **  pF[pNofPoints] - function
 **  pX - point to find value at
 ** OUTPUT
 **  None
 ** RETURN
 **  Value at point pX
*/
//---------------------------------------------------------------------------
float BizMath::FunctionValue(array<const float>^ pF, const int pNofPoints, const float pX)
{
  float lValue = -9999;
  // Catch start point
  if (pX == 0) return pF[0];

  // Finding Value
  for (int i = 1; i < pNofPoints; i++)
  {
    float moment = i;
    if (moment >= pX)
    {
      // Linear interpolation
      double N1 = moment - pX;
      double N2 = 1. - N1;
      lValue = N1*pF[i-1] + N2*pF[i];
      return lValue;
    }
  }

  return lValue;
}