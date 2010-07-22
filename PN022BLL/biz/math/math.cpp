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

/* ###########################################################################
 ** TimeToIndex(double fvalue)
 **
 ** DESCRIPTION
 **  Convert time in msec into index
 ** INPUT
 **  pTime - time
 **  pExpandRate - rate of upsampling
 **  pSampleRate (usually 128) - rate of signal sampling
 ** OUTPUT (RETURN)
 **  none
 ** RETURN
 **  index
*/
//---------------------------------------------------------------------------
int BizMath::TimeToIndex(const float pTime, const int pExpandRate,
                     const int pSampleRate)
{
  if (pExpandRate < 1 || pTime <= 0. || pTime > 9998 || pSampleRate < 1)
    return -1;
  int ind = BizMath::Round(pTime*pSampleRate*pExpandRate/1000.);
	return ind;
}

/* ###########################################################################
 ** IndexToTime
 **
 ** DESCRIPTION
 **  Convert index into time in msec
 ** INPUT
 **  ind - index
 **  pExpandRate - rate of upsampling
 **  pSampleRate (usually 128) - rate of signal sampling
 ** OUTPUT (RETURN)
 **  none
 ** RETURN
 **  time
*/
//---------------------------------------------------------------------------
float BizMath::IndexToTime(const int pIndex, const int pExpandRate,
                       const int pSampleRate)
{
  if (pExpandRate < 1 || pIndex < 0 || pSampleRate < 1)
    return -1;
  float lTime = pIndex*(float)1000./(pSampleRate*pExpandRate);
	return lTime;
}

/* ###########################################################################
 ** Round (double fvalue)
 **
 ** DESCRIPTION
 **  Round real numbers to nearest integer
 **		Example :
 **		3.78 -> 4, -3.78 -> -4
 **		3.27 -> 3, -3.27 -> -3
 ** INPUT
 **  pValue - double value to round
 ** OUTPUT (RETURN)
 **  pCentral[NofPoints] - central pressure signal
 ** RETURN
 **  boolean success or not
*/
//---------------------------------------------------------------------------
int BizMath::Round (double pValue)
{
  int iValue;

	if (pValue >= DEFAULT_VALUE || pValue <= -DEFAULT_VALUE)
	{
		return DEFAULT_VALUE;
	}
	  
	// round positive number
		if( pValue >= 0.0 )
		{
			if ((pValue - ((long long int)pValue)) < 0.5)
		   {
			   iValue = Convert::ToInt32(Math::Floor(pValue));		// round down
		   }
		   else
		   {
			   iValue = Convert::ToInt32(Math::Ceiling(pValue));		// round up
		   }
		}
		// round negative number
		else
		{
		   if ((pValue - ((long long int)pValue)) < -0.5 )
		   {
			  iValue = Convert::ToInt32(Math::Floor(pValue));	// round down
		   }
		   else
		   {
			  iValue = Convert::ToInt32(Math::Ceiling(pValue)); 	// round up
		   }
		}

	return(iValue );
}

/* ###########################################################################
 ** Round_nearest_20 (int pValue)
 **
 ** DESCRIPTION
 **  Round integers to nearest multiple of 20
 **		Example :
 **		110 -> 120, -110 -> -120
 **      109 -> 100, -109 -> -100
 ** INPUT
 **  pValue - integer value to round
 ** OUTPUT (RETURN)
 **  none
 ** RETURN
 **  ivalue - rounded integer
*/
//---------------------------------------------------------------------------
int BizMath::RoundNearest20 (int pValue)
{
  int iValue;
  int multiple;
  int remainder;

  if (pValue >= DEFAULT_VALUE || pValue <= -DEFAULT_VALUE)
	{
		return DEFAULT_VALUE;
	}

	// round positive number
	if( pValue >= 0.0 )
	{
      multiple = pValue / 20;
      remainder = pValue % 20;
		if (remainder < 10)
      {
         iValue = 20 * multiple;		      // round down
      }
	   else
      {
         iValue = 20 * (multiple + 1);		// round up
      }
	}
   // round negative number
	else
	{
      multiple = pValue / 20;
      remainder = pValue % 20;
		if (remainder < -10)
      {
         iValue = 20 * (multiple - 1);		      // round down
      }
	   else
      {
         iValue = 20 * multiple;		// round up
      }
	}

	return(iValue);
}

/* ###########################################################################
 ** SmoothDerivative1(...)
 **
 ** DESCRIPTION
 **  Calculate first derivative of a function
 **  using formula after smoothing
 **  f[k]' = 3/[n*(n+1)*(2n+1)] * Sum (j*f[k+j]) , j = -n...n
 ** INPUT
 **  F[NofPoints] - function values
 **  pDt - step of abscissa
 **  n = SmoothOrder - Smoothing order
 ** OUTPUT
 **  NofDer1Points = NofPoints - 1 - number of Derivative points
 **  pDer1[NofDer1Points] - first derivative
 **  pMax - maximum value of a derivative
 ** RETURN
 **  none
*/
//-------------------------------------------------------------------------------------
void BizMath::SmoothDerivative1(const array<float>^ F, const int NofPoints, const int SmoothOrder,
                            const float pDt, array<float>^ pDer1, float% pMax)
{
  // Validation
  if ((SmoothOrder < 1) || (NofPoints < 2*SmoothOrder)) return;
  if (pDt == 0.) return;

  float dt2 = pDt*2;

  // Start points (ForwardStep formula)
  // pDer1[0] = (-3*F[0] + 4*F[1] - F[2]) /dt2;
  pDer1[0] = (-F[0] + F[1]) /pDt;
  // pMax = pDer1[0];
  for (int i = 1; i < SmoothOrder; i++)
  {
    // pDer1[i] = (F[i+3] - 6*F[i+2] + 18*F[i+1] -10*F[i] - 3*F[i-1]) /12. /pDt;
    if (i==1)
    {
      pDer1[i] = (F[i+1] - F[i-1]) /dt2;
      pMax = pDer1[1];
    }
    else
      pDer1[i] = (-2*F[i-2] - F[i-1] + F[i+1] + 2*F[i+2]) /(float)10. /pDt;
    // pDer1[i] = (-3*F[i] +4*F[i+1] - F[i+2]) /dt2;
    if (pDer1[i] > pMax)
      pMax = pDer1[i];
  }

  // Middle points
  double c = double(3)/SmoothOrder/(SmoothOrder + 1)/(2*SmoothOrder + 1)/pDt;
  for (int i = SmoothOrder; i < NofPoints - SmoothOrder; i++)
  {
    double sum = 0.;
    for (int j = -SmoothOrder; j <= SmoothOrder; j++)
    {
      if (j!=0) sum += j*F[i+j];
    }
    pDer1[i] = sum * c;
    if (pDer1[i] > pMax)
      pMax = pDer1[i];
  }

  // End points (BackStep formula)
  for (int i = NofPoints - SmoothOrder; i < NofPoints - 1; i++)
  {
    // pDer1[i] = (3*F[i+1] + 10*F[i] - 18*F[i-1] + 6*F[i-2] - F[i-3]) /12. /pDt;
    if (i==NofPoints - 2)
      pDer1[i] = (F[i+1] - F[i-1]) /dt2;
    else
      pDer1[i] = (-2*F[i-2] - F[i-1] + F[i+1] + 2*F[i+2]) /10. /pDt;
    if (pDer1[i] > pMax)
      pMax = pDer1[i];
  }
  // pDer1[NofPoints - 1] = (F[NofPoints - 3] - 4*F[NofPoints - 2] + 3*F[NofPoints - 1]) /dt2;
  pDer1[NofPoints - 1] = (F[NofPoints - 1] - F[NofPoints - 2]) /pDt;
  // if (pDer1[NofPoints - 1] > pMax)
  //  pMax = pDer1[NofPoints - 1];
}
/* ###########################################################################
 ** MaxInArray(...),  MinInArray(...),  MinMaxInArray(...)
 **
 ** DESCRIPTION
 **  find maximum/minimum value in array
 ** INPUT
 **  pA[pSize] - array
 ** OUTPUT (RETURN)
 **  maximum/minimum value
*/
//---------------------------------------------------------------------------
float BizMath::MaxInArray (const array<float>^ pA, int pSize)
{
  float lMax = pA[0];
  for (int i = 0; i < pSize; i++)
  {
    if (pA[i] > lMax)
    {
      lMax = pA[i];
    }
  }
  return lMax;
}

/*
** Find the index of where the maximum resides within an array.
*/
int BizMath::MaxInArrayIndex(const array<float>^ pA, int pSize)
{
  float lMax = pA[0];
  int MaxIndex = 0;
  for (int i = 0; i < pSize; i++)
  {
    if (pA[i] > lMax)
    {
      lMax = pA[i];
      MaxIndex=i;
    }
  }
  return MaxIndex;
}

//---------------------------------------------------------------------------
float BizMath::MinInArray (const array<float>^ pA, int pSize)
{
  float lMax = pA[0];
  for (int i = 0; i < pSize; i++)
  {
    if (pA[i] < lMax)
    {
      lMax = pA[i];
    }
  }
  return lMax;
}
//---------------------------------------------------------------------------
bool BizMath::MinMaxInArray (const array<float>^ pA, int pSize, float% pMin, float% pMax)
{
  // Validation
  if (pSize <= 0)
    return false;
  // Main routine
  pMax = pA[0];
  pMin = pA[0];
  for (int i = 0; i < pSize; i++)
  {
    if (pA[i] > pMax)
    {
      pMax = pA[i];
    }
    if (pA[i] < pMin)
    {
      pMin = pA[i];
    }
  }
  // Return
  return true;
}

//---------------------------------------------------------------------------
bool BizMath::MinMaxInArray (const array<short int>^ pA, int pSize, short int% pMin, short int% pMax)
{
  // Validation
  if (pSize <= 0)
    return false;
  // Main routine
  pMax = pA[0];
  pMin = pA[0];
  for (int i = 0; i < pSize; i++)
  {
    if (pA[i] > pMax)
    {
      pMax = pA[i];
    }
    if (pA[i] < pMin)
    {
      pMin = pA[i];
    }
  }
  // Return
  return true;
}

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
bool BizMath::Spline(const float x, const array<float>^ Profile, const int SplineOrder,
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
int BizMath::IndexOfExtremum(const array<float>^ pProfile, const bool pMinOrMax, const bool pOnlyFirst, const int i1, const int i2,
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
float BizMath::FunctionValue(const array<float>^ pF, const int pNofPoints, const float pX)
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