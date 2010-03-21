//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "Mathem.h"
#include <math.h>
#include <stdlib.h>
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
/* ###########################################################################
 ** math_TimeToIndex(double fvalue)
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
int math_TimeToIndex(const float pTime, const int pExpandRate,
                     const int pSampleRate)
{
  if (pExpandRate < 1 || pTime <= 0. || pTime > 9998 || pSampleRate < 1)
    return -1;
  int ind = math_Round(pTime*pSampleRate*pExpandRate/1000.);
	return ind;
}

/* ###########################################################################
 ** math_IndexToTime
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
float math_IndexToTime(const int pIndex, const int pExpandRate,
                       const int pSampleRate)
{
  if (pExpandRate < 1 || pIndex < 0 || pSampleRate < 1)
    return -1;
  float lTime = pIndex*1000./(pSampleRate*pExpandRate);
	return lTime;
}

/* ###########################################################################
 ** math_Round (double fvalue)
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
int math_Round (double pValue)
{
  int iValue;

	// round positive number
	if( pValue >= 0.0 )
	{
		if ((pValue - ((long int)pValue)) < 0.5)
       {
	      iValue = floor(pValue);		// round down
       }
	   else
       {
          iValue = ceil(pValue);		// round up
       }
	}
	// round negative number
	else
	{
	   if ((pValue - ((long int)pValue)) < -0.5 )
       {
	      iValue = floor(pValue);	// round up
       }
       else
       {
          iValue = ceil(pValue); 	// round down
       }
	}

	return(iValue );
}

/* ###########################################################################
 ** math_Round_nearest_20 (int fvalue)
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
int math_Round_nearest_20 (int pValue)
{
  int iValue;
  int multiple;
  int remainder;

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
         iValue = 20 * multiple;		      // round up
      }
	   else
      {
         iValue = 20 * (multiple - 1);		// round down
      }
	}

	return(iValue);
}

/* ###########################################################################
 ** math_Derivative1(...)
 **
 ** DESCRIPTION
 **  Calculate first derivative of a function using simple linear interpolation
 ** INPUT
 **  F[NofPoints] - function values
 **  pDt - step of abscissa
 ** OUTPUT
 **  NofDer1Points = NofPoints - 1 - number of Derivative points
 **  pDer1[NofDer1Points] - first derivative
 **  pMax - maximum value of a derivative
 ** RETURN
 **  none
*/
//---------------------------------------------------------------------------
void math_Derivative1(const float* F, const int NofPoints, const float pDt,
                      float* pDer1, float &pMax)
{
  for (int i = 0; i < NofPoints - 1; i++)
  {
    pDer1[i] = (F[i+1] - F[i])/pDt;
    if (i == 0) pMax = pDer1[i];
    if (pDer1[i] > pMax) pMax = pDer1[i];
  }
}
/* ###########################################################################
 ** math_Deriv1(...)
 **
 ** DESCRIPTION
 **  Calculate first derivative of a function using 3-points formula
 ** INPUT
 **  F[NofPoints] - function values
 **  pDt - step of abscissa
 ** OUTPUT
 **  NofDer1Points = NofPoints - 1 - number of Derivative points
 **  pDer1[NofDer1Points] - first derivative
 **  pMax - maximum value of a derivative
 ** RETURN
 **  none
*/
//---------------------------------------------------------------------------
void math_Deriv1(const float* F, const int NofPoints,
                 const float pDt, float* pDer1, float &pMax)
{
  if (NofPoints < 3)
    return;
  double lDt2 = 2. * pDt;
  for (int i = 0; i < NofPoints; i++)
  {

    if (i==0)
    {
      pDer1[i] = (-3*F[0] + 4*F[1] - F[2]) /lDt2;
      pMax = pDer1[i];
    }
    else if (i == NofPoints - 1) pDer1[i] = (F[NofPoints - 3] - 4*F[NofPoints - 2] + 3*F[NofPoints - 1]) /lDt2;
         else pDer1[i] = (- F[i-1] + F[i+1]) /lDt2;

  /*
    if (i < NofPoints - 2)
    {
      pDer1[i] = (-3*F[i] + 4*F[i+1] - F[i+2]) /lDt2;
      if (i==0) pMax = pDer1[i];
    }
    else if (i == NofPoints - 1) pDer1[i] = (F[NofPoints - 3] - 4*F[NofPoints - 2] + 3*F[NofPoints - 1]) /lDt2;
         else pDer1[i] = (- F[i-1] + F[i+1]) /lDt2;

   */
    if (pDer1[i] > pMax) pMax = pDer1[i];
  }
}
/* ###########################################################################
 ** math_SmoothDerivative1(...)
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
void math_SmoothDerivative1(const float* F, const int NofPoints, const int SmoothOrder,
                            const float pDt, float* pDer1, float &pMax)
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
      pDer1[i] = (-2*F[i-2] - F[i-1] + F[i+1] + 2*F[i+2]) /10. /pDt;
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
 ** math_Derivatives123(...)
 **
 ** DESCRIPTION
 **  Calculate 1,2,3rd derivatives of a function using 3-points formula
 ** INPUT
 **  F[NofPoints] - function values
 **  pDt - step of abscissa
 ** OUTPUT
 **  NofDer1Points = NofPoints - 1 - number of Derivative points
 **  pDer1[NofDer1Points] - first derivative
 **  pMax - maximum value of a derivative
 ** RETURN
 **  none
*/
//---------------------------------------------------------------------------
void math_Derivatives123(const float* F, const int NofPoints, const float pDt,
                         float* pDer1, float* pDer2, float* pDer3,
                         float &pMaxDer1, float &pMaxDer2, float &pMaxDer3,
                         const int pOrder, const int pFormulaType)
{
  if (NofPoints < 5)
    return;
  double lDt = pDt;
  double lDt2 = pow(pDt, 2);
  double lDt3 = pow(pDt, 3);
  switch (pFormulaType)
  {
    case DER_CENTRAL_SCHEME:
    {
      for (int i = 0; i < NofPoints; i++)
      {
        if (i==0)
        {
          pDer1[i] = (-3*F[0] + 4*F[1] - F[2]) /lDt/2.;
          pMaxDer1 = pDer1[i];
          if (pDer2 != NULL)
          {
            pDer2[i] = (2*F[0] - 5*F[1] + 4*F[2] - F[3])/lDt2;
            pMaxDer2 = pDer2[i];
          }
          if (pDer3 != NULL)
          {
            pDer3[i] = (-2*F[0] + 7*F[1] -9*F[2] + 5*F[3] - F[4])/lDt3;
            pMaxDer3 = pDer3[i];
          }
        }
        else if (i==1)
        {
          pDer1[i] = (-F[0] + F[2])/lDt/2.;
          if (pDer2 != NULL)
//            pDer2[i] = (11*F[0] - 20*F[1] + 6*F[2] + 4*F[3] - F[4])/lDt2/6.;
//            pDer2[i] = (2*F[1] - 5*F[2] + 4*F[3] - F[4])/lDt2;
            pDer2[i] = (F[0] - 2*F[1] + F[2])/lDt2;
          if (pDer3 != NULL)
            pDer3[i] = (-3*F[0] + 10*F[1] -12*F[2] + 6*F[3] - F[4])/lDt3/2.;
        }
        else if (i == NofPoints - 1)
        {
          pDer1[i] = (F[NofPoints - 3] - 4*F[NofPoints - 2] + 3*F[NofPoints - 1])/lDt/2.;
          if (pDer2 != NULL)
            pDer2[i] = (F[NofPoints - 4] - 4*F[NofPoints - 3] + 5*F[NofPoints - 2] - 2*F[NofPoints - 1])/lDt2;
          if (pDer3 != NULL)
            pDer3[i] = (F[NofPoints - 5] - 5*F[NofPoints - 4] + 9*F[NofPoints - 3] - 7*F[NofPoints - 2] + 2*F[NofPoints - 1])/lDt3;
        }
        else if (i == NofPoints - 2)
        {
          pDer1[i] = (-F[NofPoints - 3] + F[NofPoints - 1])/lDt/2.;
          if (pDer2 != NULL)
            // pDer2[i] = (F[NofPoints - 5] - 4*F[NofPoints - 4] - 6*F[NofPoints - 3] + 20*F[NofPoints - 2] - 11*F[NofPoints - 1])/lDt2/12.;
            // pDer2[i] = (F[NofPoints - 5] - 4*F[NofPoints - 4] + 5*F[NofPoints - 3] - 2*F[NofPoints - 2])/lDt2;
            pDer2[i] = (F[NofPoints - 3] - 2*F[NofPoints - 2] + F[NofPoints - 1])/lDt2;
          if (pDer3 != NULL)
            pDer3[i] = (F[NofPoints - 5] - 6*F[NofPoints - 4] + 12*F[NofPoints - 3] - 10*F[NofPoints - 2] + 3*F[NofPoints - 1])/lDt3/2.;
        }
        else
        {
          pDer1[i] = (F[i-2] - 8*F[i-1] + 8*F[i+1] - F[i+2]) /lDt/12.;
          if (pDer2 != NULL)
            pDer2[i] = double(- F[i-2] + 16.*F[i-1] - 30.*F[i] + 16.*F[i+1] - F[i+2]) /lDt2/12.;
            //pDer2[i] = (F[i-1] - 2*F[i] + F[i+1]) /lDt2;
          if (pDer3 != NULL)
            pDer3[i] = (- F[i-2] + 2*F[i-1] - 2*F[i+1] + F[i+2]) /lDt3/2.;
        }
        if (pDer1[i] > pMaxDer1) pMaxDer1 = pDer1[i];
        if (pDer2 != NULL)
          if (pDer1[2] > pMaxDer2) pMaxDer2 = pDer2[i];
        if (pDer3 != NULL)
          if (pDer1[3] > pMaxDer3) pMaxDer3 = pDer3[i];
      }
    }
    break;
    case DER_RIGHT_SCHEME:
    {
    }
  }
}
/* ###########################################################################
 ** math_MaxInArray(...),  math_MinInArray(...),  math_MinMaxInArray(...)
 **
 ** DESCRIPTION
 **  find maximum/minimum value in array
 ** INPUT
 **  pA[pSize] - array
 ** OUTPUT (RETURN)
 **  maximum/minimum value
*/
//---------------------------------------------------------------------------
float math_MaxInArray (const float *pA, int pSize)
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
int math_MaxInArrayIndex(const float *pA, int pSize)
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
float math_MinInArray (const float *pA, int pSize)
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
bool math_MinMaxInArray (const float *pA, int pSize, float &pMin, float &pMax)
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
bool math_MinMaxInArray (const short int *pA, int pSize, short int &pMin, short int &pMax)
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
/*
** Find the minumum and the following maximum in the array.
*/
bool math_MaxAfterMinInArray (const float *pA, int pSize, float &pMin, float &pMax)
{
  int index = 0;

  // Validation
  if (pSize <= 0)
    return false;
  // Main routine
  pMin = pA[0];
  for (int i = 0; i < pSize; i++)
  {
    if (pA[i] < pMin)
    {
      pMin = pA[i];
      index = i;
    }
  }
  pMax = pA[index];
  for (int i = index; i < pSize; i++)
  {
    if (pA[i] > pMax)
    {
      pMax = pA[i];
    }
  }
  // Return
  return true;
}

/* ###########################################################################
 ** math_GetSplineIndex(x, SplineIndex, SplineOrder, pPulse.Length);
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
int math_GetSplineIndex(const float x, const int SplineIndex,
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
 ** math_GetSplineOverlay(x, SplineIndex, NofSplines, SplineOrder, pPulse.Length);
 **
 ** DESCRIPTION
 **  Find SplineIndex (beginning of nearest spline) and
 **  Nof closest splines for point x on pulse
 ** INPUT
 **  x - abscissa of a point on a Pulse
 **  SplineIndex - old SplineIndex
 **  SplineOrder - order of spline
 **  pPulseLength - length of a pulse
 ** OUTPUT
 **  NofSplines - Nof closest splines
 **  SplineIndex - new spline index
 ** RETURN
 **  boolean success
*/
//---------------------------------------------------------------------------
bool math_GetSplineOverlay(const float x, int& SplineIndex, int& NofSplines,
                           const int SplineOrder, const int pPulseLength)
{
  // int NewSplineIndex = SplineIndex;

  // NofSplines = 1;

  int SO1 = SplineOrder + 1;

  int Limit = 1; // Limit point in spline to switch on next spline
  int Step = 1;  // Step to increment spline initial point

  // Special case of pulse end
  if (x >= pPulseLength - SplineOrder)
  {
    SplineIndex = pPulseLength - SO1;
    NofSplines = 1; // pPulseLength - 1 SplineIndex - 1;
  }
  // Check point overcome limit
  else if (x > SplineIndex + Limit)
  {
    SplineIndex += Step;
    // NofSplines
    if (SplineIndex >= SplineOrder - 1) NofSplines = SplineOrder;
    else NofSplines = SplineIndex + 1;
  }

  return (NofSplines >= 1);
}

/* ###########################################################################
 ** math_Spline(...)
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
bool math_Spline(const float x, const float* Profile, const int SplineOrder,
                 float &Value, float *Der, const int NofDer)
{
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
 ** math_Hermit(...)
 **
 ** DESCRIPTION
 ** INPUT
 **  Find a value of cubic (hermitian) spline approximation of order SplineOrder in point x of
 **  Pulse profile together with derivatives
 **  x - abscissa of a point on a Pulse
 **  Profile[2] - Pulse section
 **  D1[2] - Pulse derivative
 ** OUTPUT
 **  Value - pulse value
 **  Der1, Der2, Der3 - derivatives values
 ** RETURN
 **  bool success or not
*/
//--------------------------------------------------------------------------------
bool math_Hermit(const float x, const float* Profile, const float* D1,
                 float &Value, float &Der1, float &Der2, float &Der3)
{
  Value = 0.;
  Der1  = 0.;
  Der2  = 0.;
  Der3  = 0.;

  // Spline length
  double l = 1.;
  double l2 = l*l;
  double l3 = l2*l;
  // L-coordinates
  double L = x/l;
  double L2 = L*L;
  double L3 = L2*L;

  // Calculate cubic spline basic functions and derivatives
  double N[2], N1[2], N2[2], N3[2];
  double M[2], M1[2], M2[2], M3[2];

  N[0] = 1 - 3*L2 + 2*L3;
  N[1] = 3*L2 - 2*L3;
  M[0] = l*(L - 2*L2 + L3);
  M[1] = l*(-L2 + L3);

  N1[0] = (-6*L + 6*L2)/l;
  N1[1] = ( 6*L - 6*L2)/l;
  M1[0] = (1 - 4*L + 3*L2);
  M1[1] = (- 2*L + 3*L2);

  N2[0] = (-6 + 12*L)/l2;
  N2[1] = ( 6 - 12*L)/l2;
  M2[0] = (- 4 + 6*L)/l;
  M2[1] = (- 2 + 6*L)/l;

  N3[0] = 12./l3;
  N3[1] = -12./l3;
  M3[0] = 6/l2;
  M3[1] = 6/l2;
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
  for (int i = 0; i < 2; i++)
  {
    Value += N[i]*Profile[i]  + M[i]*D1[i];
    Der1  += N1[i]*Profile[i] + M1[i]*D1[i];
    Der2  += N2[i]*Profile[i] + M2[i]*D1[i];
    Der3  += N3[i]*Profile[i] + M3[i]*D1[i];
  }
  return true;
}

/* ###########################################################################
 ** math_IndexOfFirstPositiveCrossing(...)
 **
 ** DESCRIPTION
 **  Find an index of first positive/negative crossing
 **  of function Profile[...] between indexes i1, i2
 ** INPUT
 **  Profile[...] - function values
 **  i1, i2 - indexes
 ** OUTPUT
 ** RETURN
 **  index of crossing or -1 if not found
*/
//-------------------------------------------------------------------------------------
int math_IndexOfFirstPositiveCrossing(const float *Profile, const int i1, const int i2)
{
  int ret = -1;
  // Validation
  if ((i2 < i1) || (i1 < 0) || (i2 <= 0)) return ret;
  // Loop
  float Current, Last, Next;
  for (int i = i1; i < i2; i++)
  {
    // Get last, current and next values and avoid undesired
    Current = Profile[i];
    // if (Current < 0.) continue;
    Last = ( (i > i1) ? Profile[i-1] : Profile[i1]);
    if (Last > 0.) continue;
    Next = ( (i < i2 - 1) ? Profile[i+1] : Profile[i2]);
    if (Next < 0.) continue;
    // check tripple
    if ((Current > Last) && (Current < Next))
    {
      ret = (fabs(Current) >= fabs(Next) ? i+1 : i);
      // ret = i+1;
      // ret = i;
      break;
    }
  }
  return ret;
}
//-------------------------------------------------------------------------------------
int math_IndexOfFirstNegativeCrossing(const float *Profile, const int i1, const int i2)
{
  int ret = -1;
  // Validation
  if ((i2 < i1) || (i1 < 0) || (i2 <= 0)) return ret;
  // Loop
  float Current, Last, Next;
  for (int i = i1; i < i2; i++)
  {
    // Get last, current and next values and avoid undesired
    Current = Profile[i];
    // if (Current < 0.) continue;
    Next = ( (i < i2 - 1) ? Profile[i+1] : Profile[i2]);
    if (Next > 0.) continue;
    Last = ( (i > i1) ? Profile[i-1] : Profile[i1]);
    if (Last < 0.) continue;
    // check tripple
    if ((Current < Last) && (Current > Next))
    {
      ret = (fabs(Current) >= fabs(Next) ? i+1 : i);
      // ret = i+1;
      // ret = i;
      break;
    }
  }
  return ret;
}
/* ###########################################################################
 ** math_IndexOfSecondPositiveCrossing(...)
 **
 ** DESCRIPTION
 **  Find an index of second positive/negative crossing
 **  of function Profile[Length]
 ** INPUT
 **  Profile[Length] - function values
 **  Begin - start point to analyse signal from
 ** OUTPUT
 ** RETURN
 **  index of crossing or -1 if not found
*/
//-------------------------------------------------------------------------------------
int math_IndexOfSecondPositiveCrossing(const float *Profile, const int Begin, const int Length)
{
  int ret = -1;
  // Validation
  if (Length <= 0) return ret;
  // Find first crossing
  int i1 = math_IndexOfFirstPositiveCrossing(Profile, Begin, Length);
  if (i1 <= 0) return ret;
  // Find second for the rest of signal
  ret = math_IndexOfFirstPositiveCrossing(Profile, i1 + 1, Length);
  return ret;
}
//-------------------------------------------------------------------------------------
int math_IndexOfSecondNegativeCrossing(const float *Profile, const int Begin, const int Length)
{
  int ret = -1;
  // Validation
  if (Length <= 0) return ret;
  // Find first crossing
  int i1 = math_IndexOfFirstNegativeCrossing(Profile, Begin, Length);
  if (i1 <= 0) return ret;
  // Find second for the rest of signal
  ret = math_IndexOfFirstNegativeCrossing(Profile, i1 + 1, Length);
  return ret;
}
/* ###########################################################################
 ** math_IndexOfFirstPositiveCrossing(...)
 **
 ** DESCRIPTION
 **  Check if the function Profile[...]
 **  positive between indexes i1, i2
 ** INPUT
 **  Profile[...] - function values
 **  i1, i2 - indexes
 ** OUTPUT
 ** RETURN
 **  true if positive, false otherwise
*/
//-------------------------------------------------------------------------------------
bool math_IsPositive(const float *Profile, const int i1, const int i2)
{
  // Validation
  if (i1 < 0) throw (Exception ("Invalid index in function math_IsPositive"));
  // Loop with check
  for (int i = i1; i < i2; i++)
  {
    if (Profile[i] < 0.) return false;
  }
  // All positive
  return true;
}

/* ###########################################################################
 ** math_SmoothArray()
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
bool math_SmoothArray(float *pArray, const int pSize, const int pSmoothOrder)
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
 ** math_SGSmoothArray()
 **
 ** DESCRIPTION
 **  Smooth array using Savitsky - Golay smoothing filter
 ** INPUT
 **  pArray[pSize] - float array
 **  pSmoothOrder [1,2,3,4] - "strength" of filtering
 ** OUTPUT
 **  pArray (rewritten)
 ** RETURN
 **  true if success, false otherwise
*/
//-------------------------------------------------------------------------------------
bool math_SGSmoothArray(float *pArray, const int pSize, const int pSmoothOrder)
{
  // Validation
	if (pSmoothOrder <= 0 || pSmoothOrder >= 5)
  {
		return false;
  }
  // Allocate memory for new array and copy old into
	double *lSt = new double[pSize];
  for (int i=0; i<pSize; i++)
    lSt[i] = pArray[i];
  // Different formulas
  switch (pSmoothOrder)
  {
    case 1:
    {
      // S-G formula at M = 2, n = 2
      pArray[0] = lSt[0]; // (lSt[0] + lSt[1]) / 2.0;
      pArray[1] = (lSt[0] + lSt[1] + lSt[2]) / 3.;
      // double d;
      for (int i=2; i < pSize - 2; i++)
      {
        pArray[i] = (-0.086*lSt[i-2] + 0.343*lSt[i-1] + 0.486*lSt[i]
                     + 0.343*lSt[i+1] - 0.086*lSt[i+2]);
      }
      pArray[pSize - 2] = (lSt[pSize - 3] + lSt[pSize - 2] + lSt[pSize - 1]) / 3.;
      pArray[pSize - 1] = lSt[pSize - 1]; // (lSt[pSize - 2] + lSt[pSize - 1]) / 2.;
    }
    break;
    case 2:
    {
      // S-G formula at M = 2, n = 5
      pArray[0] = lSt[0]; // (lSt[0] + lSt[1]) / 2.0;
      pArray[1] = (lSt[0] + lSt[1] + lSt[2]) / 3.;
      pArray[2] = (-0.086*lSt[0] + 0.343*lSt[1] + 0.486*lSt[2] +
                    0.343*lSt[3] - 0.086*lSt[4]);
      pArray[3] = (-0.086*lSt[1] + 0.343*lSt[2] + 0.486*lSt[3] +
                    0.343*lSt[4] - 0.086*lSt[5]);
      pArray[4] = (-0.086*lSt[2] + 0.343*lSt[3] + 0.486*lSt[4] +
                    0.343*lSt[5] - 0.086*lSt[6]);
      for (int i=5; i < pSize - 5; i++)
      {
        pArray[i] = (-0.084*lSt[i-5] + 0.021*lSt[i-4] + 0.103*lSt[i-3] + 0.161*lSt[i-2] + 0.196*lSt[i-1] +
                     + 0.207*lSt[i] +
                     + 0.196*lSt[i+1] + 0.161*lSt[i+2] + 0.103*lSt[i+3] + 0.021*lSt[i+4] -0.084*lSt[i+5]);
      }
      pArray[pSize-5] = (-0.086*lSt[pSize-7] + 0.343*lSt[pSize-6] + 0.486*lSt[pSize-5] +
                          0.343*lSt[pSize-4] - 0.086*lSt[pSize-3]);
      pArray[pSize-4] = (-0.086*lSt[pSize-6] + 0.343*lSt[pSize-5] + 0.486*lSt[pSize-4] +
                          0.343*lSt[pSize-3] - 0.086*lSt[pSize-2]);
      pArray[pSize-3] = (-0.086*lSt[pSize-5] + 0.343*lSt[pSize-4] + 0.486*lSt[pSize-3] +
                          0.343*lSt[pSize-2] - 0.086*lSt[pSize-1]);
      pArray[pSize - 2] = (lSt[pSize - 3] + lSt[pSize - 2] + lSt[pSize - 1]) / 3.;
      pArray[pSize - 1] = lSt[pSize - 1]; // (lSt[pSize - 2] + lSt[pSize - 1]) / 2.;
    }
    break;
    case 3:
    {
      // S-G formula at M = 4, n = 4
      pArray[0] = lSt[0]; // (lSt[0] + lSt[1]) / 2.0;
      pArray[1] = (lSt[0] + lSt[1] + lSt[2]) / 3.;
      pArray[2] = (-0.086*lSt[0] + 0.343*lSt[1] + 0.486*lSt[2] +
                    0.343*lSt[3] - 0.086*lSt[4]);
      pArray[3] = (-0.086*lSt[1] + 0.343*lSt[2] + 0.486*lSt[3] +
                    0.343*lSt[4] - 0.086*lSt[5]);
      for (int i=4; i < pSize - 4; i++)
      {
        pArray[i] = (0.035*lSt[i-4] - 0.128*lSt[i-3] + 0.070*lSt[i-2] + 0.315*lSt[i-1] +
                     + 0.417*lSt[i] +
                     + 0.315*lSt[i+1] + 0.070*lSt[i+2] - 0.128*lSt[i+3] + 0.035*lSt[i+4]);
      }
      pArray[pSize-4] = (-0.086*lSt[pSize-6] + 0.343*lSt[pSize-5] + 0.486*lSt[pSize-4] +
                          0.343*lSt[pSize-3] - 0.086*lSt[pSize-2]);
      pArray[pSize-3] = (-0.086*lSt[pSize-5] + 0.343*lSt[pSize-4] + 0.486*lSt[pSize-3] +
                          0.343*lSt[pSize-2] - 0.086*lSt[pSize-1]);
      pArray[pSize - 2] = (lSt[pSize - 3] + lSt[pSize - 2] + lSt[pSize - 1]) / 3.;
      pArray[pSize - 1] = lSt[pSize - 1]; // (lSt[pSize - 2] + lSt[pSize - 1]) / 2.;
    }
    break;
    case 4:
    {
      // S-G formula at M = 4, n = 5
      pArray[0] = lSt[0]; // (lSt[0] + lSt[1]) / 2.0;
      pArray[1] = (lSt[0] + lSt[1] + lSt[2]) / 3.;
      pArray[2] = (-0.086*lSt[0] + 0.343*lSt[1] + 0.486*lSt[2] +
                    0.343*lSt[3] - 0.086*lSt[4]);
      pArray[3] = (-0.086*lSt[1] + 0.343*lSt[2] + 0.486*lSt[3] +
                    0.343*lSt[4] - 0.086*lSt[5]);
      pArray[4] = (-0.086*lSt[2] + 0.343*lSt[3] + 0.486*lSt[4] +
                    0.343*lSt[5] - 0.086*lSt[6]);
      for (int i=5; i < pSize - 5; i++)
      {
        pArray[i] = (0.042*lSt[i-5] - 0.105*lSt[i-4] - 0.023*lSt[i-3] + 0.140*lSt[i-2] + 0.280*lSt[i-1] +
                   + 0.333*lSt[i] +
                   + 0.280*lSt[i+1] + 0.140*lSt[i+2] - 0.023*lSt[i+3] - 0.105*lSt[i+4] + 0.042*lSt[i+5]);
      }
      pArray[pSize-5] = (-0.086*lSt[pSize-7] + 0.343*lSt[pSize-6] + 0.486*lSt[pSize-5] +
                          0.343*lSt[pSize-4] - 0.086*lSt[pSize-3]);
      pArray[pSize-4] = (-0.086*lSt[pSize-6] + 0.343*lSt[pSize-5] + 0.486*lSt[pSize-4] +
                          0.343*lSt[pSize-3] - 0.086*lSt[pSize-2]);
      pArray[pSize-3] = (-0.086*lSt[pSize-5] + 0.343*lSt[pSize-4] + 0.486*lSt[pSize-3] +
                          0.343*lSt[pSize-2] - 0.086*lSt[pSize-1]);
      pArray[pSize - 2] = (lSt[pSize - 3] + lSt[pSize - 2] + lSt[pSize - 1]) / 3.;
      pArray[pSize - 1] = lSt[pSize - 1]; // (lSt[pSize - 2] + lSt[pSize - 1]) / 2.;
    }
    break;
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
int math_IndexOfExtremum(const float* pProfile, const bool pMinOrMax, const bool pOnlyFirst, const int i1, const int i2,
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
 ** math_IndexOfQuadrInterpMax()
 **
 ** DESCRIPTION
 **  Find float index of Maximal value of a quadratic interpolation
 **  of a function constructed for tripple f(x1), f(x2), f(x3)
 ** INPUT
 **   x1, x2, x3 - abcisses, f1, f2, f3 - ordinates
 ** OUTPUT
 **  None
 ** RETURN
 **  abscissa of a point where funaction f(x) has a maximum
*/
//--------------------------------------------------------------------------------------
float math_IndexOfQuadrInterpMax(const float x1, const float x2, const float x3,
                                 const float f1, const float f2, const float f3, float &fmax)
{
  float xmax = min (x1, min(x2, x3)) - 1.;
  const float LSTEP =  0.05;
  fmax = min (f1, min(f2, f3));
  for (float L1 = 0.; L1 < 1. + LSTEP/2.; L1+= LSTEP)
  {
    float L2 = 1. - L1;
    double N1 = L1*(2*L1-1);
    double N2 = 4*L1*L2;
    double N3 = L2*(2*L2-1);
    float x = N1*x1 + N2*x2 + N3*x3;
    float f = N1*f1 + N2*f2 + N3*f3;
    if (f > fmax)
    {
      xmax = x; fmax = f;
    }
  }
  return xmax;
}
/* ###########################################################################
 ** math_FunctionValue
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
float math_FunctionValue(const float* pF, const int pNofPoints, const float pX)
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


float math_MeanInArray (const float *pA, int pSize)
{
  float sum=0;
  float mean = -1;

  if (pSize > 0)
  {
     for (int i = 0; i < pSize; i++)
     {
       sum=pA[i]+sum;
     }
     mean=sum/pSize;
  }
  return mean;
}

float math_STDinArray(int *pA,int pSize)
{
    float sum1=0;
    float sum2=0;
    float std = -1;

    if (pSize > 1)
    {
       for (int i=0; i<pSize; i++)
       {
          sum1=sum1+(pA[i]*pA[i]);
          sum2=sum2+pA[i];
       }
       std=sqrt((sum1-((sum2*sum2)/pSize))/(pSize-1));
    }
    return std;
}

double math_STDinArray(float *pA,int pSize)
{
    double sum1 = 0;
    double sum2 = 0;
    double std = 0;

    for (int i = 0; i < pSize; i++)
    {
       sum1 = sum1 + (pA[i]*pA[i]);
       sum2 = sum2 + pA[i];
    }
    std = sqrt((sum1-((sum2*sum2)/(float)pSize))/((float)pSize-1));
    
    return std;
}

double math_RMSinArray(float *pA, int pSize)
{
    double sum=0;
    double rms = -1;

    if (pSize > 1)
    {
       for (int i=0; i<pSize; i++)
       {
          sum = sum+(pA[i]*pA[i]);
       }
       rms = sqrt(sum/(float)pSize);
    }
    return rms;
}

bool math_IndexMaxInArray (const int *pA, int pSize, int &pIndex, int &pMax)
{
  // Validation
  if (pSize <= 0)
    return false;
  // Main routine
  pMax = pA[0];
  for (int i = 0; i < pSize; i++)
  {
    if (pA[i] > pMax)
    {
      pMax = pA[i];
      pIndex = i;
    }
  }
  return true;
}

bool math_IndexMaxInArray (const short int *pA, int pSize, int &pIndex, int &pMax)
{
  // Validation
  if (pSize <= 0)
    return false;
  // Main routine
  pMax = (int)pA[0];
  for (int i = 0; i < pSize; i++)
  {
    if (pA[i] > pMax)
    {
      pMax = (int)pA[i];
      pIndex = i;
    }
  }
  return true;
}
