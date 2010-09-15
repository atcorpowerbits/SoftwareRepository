//---------------------------------------------------------------------------
#include <vcl.h>

#pragma hdrstop

#include <math.h>
#include <stdlib.h>

#include <msg\pubserv.h>
#include "Pulse.h"
#include "Mathem.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)

/* ###########################################################################
 ** TPulse ()
 ** DESCRIPTION
 **  Class constructor
 ** INPUT
 ** OUTPUT
 ** RETURN
 **  None
*/
//---------------------------------------------------------------------------
TPulse::TPulse()
{
  Profile = NULL;
  Initialise(0);
}
/* ###########################################################################
 ** Allocate ()
 ** DESCRIPTION
 **  Allocate memory for a pulse
 ** INPUT
 **  Pulse class
 ** OUTPUT
 ** RETURN
 **  None
*/
//---------------------------------------------------------------------------
void TPulse::Allocate(const int pSize)
{
  Profile = new float [pSize];
  if (Profile!=NULL)
    FMaxSize = (short int) pSize;
}
/* ###########################################################################
 ** Free ()
 ** DESCRIPTION
 **  Free memory for a pulse
 ** INPUT
 **  Pulse class
 ** OUTPUT
 ** RETURN
 **  None
*/
//---------------------------------------------------------------------------
void TPulse::Free()
{
  Initialise();
  delete [] Profile;
  Profile = NULL;
  FSize = 0;
}
//---------------------------------------------------------------------------
void TPulse::Initialise(const int pSampleRate)
{
  FLength = 0;
  Index = -1;
  Start = 0;
  End = 0;
  FSize = 0;
  SampleRate = (short int) pSampleRate;
}
/* ###########################################################################
 ** SetSize()
 ** DESCRIPTION
 **  Set size of an array for a pulse
 ** INPUT
 **  Pulse class
 ** OUTPUT
 ** RETURN
 **  None
*/
//---------------------------------------------------------------------------
void TPulse::SetSize(const int pSize)
{
  FSize = (short int) pSize;
  Validate();
}
/* ###########################################################################
 ** SetMaxSize()
 ** DESCRIPTION
 **  Set max size of an array for a pulse
 ** INPUT
 **  Pulse class
 ** OUTPUT
 ** RETURN
 **  None
*/
//---------------------------------------------------------------------------
void TPulse::SetMaxSize(const int pMaxSize)
{
  FMaxSize = (short int) pMaxSize;
}
/* ###########################################################################
 ** SetLength()
 ** DESCRIPTION
 **  Set size of an array for a pulse
 ** INPUT
 **  Pulse class
 ** OUTPUT
 ** RETURN
 **  None
*/
//---------------------------------------------------------------------------
void TPulse::SetLength(const int pLength)
{
  End = (short int) (Start + pLength - 1);
  FLength = (short int) pLength;
  if (FLength > FSize)
    FSize = FLength;
  Validate();
}
/* ###########################################################################
 ** Copy()
 **
 ** DESCRIPTION
 **  Create a copy of input pulse
 ** INPUT
 **  pPulse - input pulse
 ** OUTPUT
 **  none
 ** RETURN
 **  boolean success or not
*/
//---------------------------------------------------------------------------
bool TPulse::Copy(TPulse *pPulse)
{
  // Validate input pulse
  if (pPulse->Validate()==false)
     return false;
  if (pPulse->FSize > FMaxSize)
     return false;
  // Copying
  FLength = pPulse->FLength;
  //FMaxSize = pPulse->FMaxSize;  // Maximal possible size of a pulse array
  FSize = pPulse->FSize;        // Size of array for pulse
  Index = pPulse->Index;
  Start = pPulse->Start;
  End = pPulse->End;
  SampleRate = pPulse->SampleRate;
  memcpy(Profile, pPulse->Profile, pPulse->Size()*sizeof(Profile[0]));
  return Validate();
}
//---------------------------------------------------------------------------
bool TPulse::ExtractFromBuffer(const char *cProfile, const short int pSize,
                               const int Divider, const int pBase)
{
  // Validation
  if (Profile==NULL || Divider == 0 || (pBase != 2 && pBase != 4))
  {
     MsgBox_show(TERROR,
                 MSG_MATH_ERROR,
                 LoadStr(MSG_WRONG_PULSE),
                 MSG_WRONG_PULSE,
                 LoadStr(MSG_WRONG_PULSE));
     return false;
  }

  // Cutting Pulse and divide by divider
  // Memcopy
  int l2 = pSize/pBase;
  int lLength = (short int) l2;    // !!
  short int num;
  float fnum;
  for (int i=0; i<l2; i++)
  {
    if (pBase == 2)
    {
      memcpy(&num, cProfile + i*pBase, pBase);
      if (num <=0)
      {
        lLength = (short int) i;
        break;
      }
      else
      {
        Profile[i] = float(num) / Divider;
      }
    }
    else if (pBase == 4)
    {
      memcpy(&fnum, cProfile + i*pBase, pBase);
      if (fnum <=0)
      {
        lLength = (short int) i;
        break;
      }
      else
      {
        Profile[i] = fnum;
      }
    }
  }
  if (lLength <= 0)
  {
     MsgBox(TERROR, MSG_DBREADWRITE_ERROR, MSG_WRONG_RECORD);
     return false;
  }
  Initialise();
  SetLength(lLength);
  SetSize(lLength);
  // return
  if (Validate()==false)
  {
     MsgBox(TERROR, MSG_DBREADWRITE_ERROR, MSG_WRONG_RECORD);
     return false;
  }
  return true;
}

/* ###########################################################################
 ** Validate ()
 **
 ** DESCRIPTION
 **  Validate pulse
 ** INPUT
 **  Pulse class
 ** OUTPUT
 **  boolean valid pulse or not
*/
//---------------------------------------------------------------------------
bool TPulse::Validate()
{
   // Pulse Validation
   if ((Profile==NULL) || (FLength < 1) || (Start < 0) || (Start > End) ||
       (FSize < FLength) || (FSize > FMaxSize) || (End - Start + 1 != FLength))
   {
      throw Exception(LoadStr(MSG_MATH_ERROR) + " : " + LoadStr(MSG_WRONG_PULSE));
      /*
      MsgBox_show(TERROR,
                  MSG_MATH_ERROR,
                  LoadStr(MSG_WRONG_PULSE),
                  MSG_WRONG_PULSE,
                  LoadStr(MSG_WRONG_PULSE));
      return false;
      */
   }
   return true;
}

/* ###########################################################################
 ** MinMax ()
 **
 ** DESCRIPTION
 **  Find Min, Max for pulse
 ** INPUT
 **  Pulse class
 ** OUTPUT
 **  pMin, pMax values for pulse
 **  boolean success or not
*/
//---------------------------------------------------------------------------
bool TPulse::MinMax(float &pMin, float &pMax)
{
  // Pulse Validation
  if (Validate()==false) return false;

  // Find max, min for Pulse
  pMin = Profile[Start];
  pMax = Profile[Start];
  for (int i = Start; i <= End; i++)
  {
    if (Profile[i] > pMax) pMax = Profile[i];
    if (Profile[i] < pMin) pMin = Profile[i];
  }
  return (pMax > pMin);
}

/* ###########################################################################
 ** Max (), Min ()
 **
 ** DESCRIPTION
 **  Find Max or Min for pulse between indexes i1, i2
 ** INPUT
 **  Pulse class
 ** OUTPUT
 **  pMin, pMax values for pulse
 **  boolean success or not
*/
//---------------------------------------------------------------------------
float TPulse::Max(const int i1, const int i2)
{
  float pMax = -DEFAULT_VALUE;
  // Pulse Validation
  if (Validate()==false)
    return pMax;
  // Validate interval
  if (IsIntervalValid(i1, i2)==false)
    return pMax;

  // Find max, min for Pulse
  pMax = Profile[i1];
  for (int i = i1; i < i2; i++)
  {
    if (Profile[i] > pMax)
      pMax = Profile[i];
  }
  return pMax;
}
//---------------------------------------------------------------------------
float TPulse::Min(const int i1, const int i2)
{
  float pMin = DEFAULT_VALUE;
  // Pulse Validation
  if (Validate()==false)
    return pMin;
  // Validate interval
  if (IsIntervalValid(i1, i2)==false)
    return pMin;

  // Find max, min for Pulse
  pMin = Profile[i1];
  for (int i = i1; i < i2; i++)
  {
    if (Profile[i] < pMin)
      pMin = Profile[i];
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
 **   i1, i2 - indexes
 **  Pulse class
 ** OUTPUT
 **  Index or -1 if wrong pulse
*/
//---------------------------------------------------------------------------
int TPulse::IndexOfMax(const int i1, const int i2)
{
  int ind = -1;
  // Pulse Validation
  if (Validate()==false) return ind;
  // Validate interval
  if (IsIntervalValid(i1, i2)==false) return ind;

  // Find max for Pulse
  float pMax = Profile[i1];
  ind = i1;
  for (int i = i1; i < i2; i++)
  {
    if (Profile[i] > pMax)
    {
      pMax = Profile[i];
      ind = i;
    }
  }
  return ind;
}
//---------------------------------------------------------------------------
int TPulse::IndexOfMin(const int i1, const int i2)
{
  int ind = -1;
  // Pulse Validation
  if (Validate()==false)
    return ind;
  // Validate interval
  if (IsIntervalValid(i1, i2)==false)
    return ind;

  // Find max for Pulse
  float pMin = Profile[i1];
  ind = i1;
  for (int i = i1; i < i2; i++)
  {
    if (Profile[i] < pMin)
    {
      pMin = Profile[i];
      ind = i;
    }
  }
  return ind;
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
int TPulse::IndexOfExtremum(const bool pMinOrMax, const bool pOnlyFirst,
                            const int i1, const int i2,

            const int pStabilityZone, const bool pLessOrMore,
            const float pLessOrMoreThan, const float *Der2,

            const float *pOtherFunction, const bool pOtherLessOrMore,
            const float pOtherLessOrMoreThan, const int pOtherStabilityZone,

            const float *pOtherFunction2, const bool pOtherLessOrMore2,
            const float pOtherLessOrMoreThan2, const int pOtherStabilityZone2,

            const float *pOtherFunction3, const bool pOtherLessOrMore3,
            const float pOtherLessOrMoreThan3, const int pOtherStabilityZone3,

            const float *pOtherFunction4, const bool pOtherLessOrMore4,
            const float pOtherLessOrMoreThan4, const int pOtherStabilityZone4)
{
  int ind = -1;
  // Pulse Validation
  if (Validate()==false)
    return ind;
  // Validate interval
  if (IsIntervalValid(i1, i2, false)==false)
    return ind;
  // Find Extremum for Pulse.
  // For maximum extremum is where Current > Last, Current >= Next
  // For minimum extremum is where Current < Last, Current <= Next
  float lCurrent, lLast, lNext;
  for (int i = i1 + 1; i < i2 - 1; i++)
  {
    lCurrent = Profile[i];
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
    lLast = Profile[i-1];
    lNext = Profile[i+1];
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
    // Now lCurrent is extremum. Check stability of an extremum
    if (pStabilityZone > 0)
    {
      int lBegin = (i - pStabilityZone > 0 ?
                    i - pStabilityZone : i1);
      int lEnd = (i + pStabilityZone <= End ?
                    i + pStabilityZone : i2);
      // lBegin = max(i1, i - pStabilityZone);
      // lEnd = min(i2, i + pStabilityZone);
      // Reject if function change the sign
      if (pLessOrMoreThan != DEFAULT_VALUE)
      {
        bool lReject = false;
        for (int i = lBegin; i < lEnd; i++)
        {
          if (pLessOrMore == LESS)
          {
            if (Profile[i] >= pLessOrMoreThan)
            {
              lReject = true;
              break;
            }
          }
          else // if (pLessOrMore == MORE)
          {
            if (Profile[i] <= pLessOrMoreThan)
            {
              lReject = true;
              break;
            }
          }
        }
        if (lReject == true)
          continue;
      }
      // Reject unstable extremum
      if (IsExtremumStable(i, lBegin, lEnd, pMinOrMax, Der2)==false)
        continue;
    }
    // .................................................................
    // Now lCurrent is extremum. Check stability of OtherFunctions
    if (pOtherFunction != NULL && pOtherLessOrMoreThan != DEFAULT_VALUE)
    {
        if (CheckCondition(i, i1, i2, pOtherFunction, pOtherLessOrMore,
            pOtherLessOrMoreThan, pOtherStabilityZone)==false)
        {
          continue;
        }
    }
    if (pOtherFunction2 != NULL && pOtherLessOrMoreThan2 != DEFAULT_VALUE)
    {
        if (CheckCondition(i, i1, i2, pOtherFunction2, pOtherLessOrMore2,
            pOtherLessOrMoreThan2, pOtherStabilityZone2)==false)
        {
          continue;
        }
    }
    if (pOtherFunction3 != NULL && pOtherLessOrMoreThan3 != DEFAULT_VALUE)
    {
        if (CheckCondition(i, i1, i2, pOtherFunction3, pOtherLessOrMore3,
            pOtherLessOrMoreThan3, pOtherStabilityZone3)==false)
        {
          continue;
        }
    }
    if (pOtherFunction4 != NULL && pOtherLessOrMoreThan4 != DEFAULT_VALUE)
    {
        if (CheckCondition(i, i1, i2, pOtherFunction4, pOtherLessOrMore4,
            pOtherLessOrMoreThan4, pOtherStabilityZone4)==false)
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
        break;
    }
    else
    {
      if (pMinOrMax == MAX)
      {
         if (lCurrent > Profile[ind])
            ind = i;
      }
      else // if (pMinOrMax == MINIMUM)
      {
         if (lCurrent < Profile[ind])
            ind = i;
      }
    }
  }
  // return
  return ind;
}
//---------------------------------------------------------------------------
bool TPulse::IsExtremumStable(const int ExtPoint, const int pBegin, const int pEnd,
                              const bool pMaxOrMin, const float *Der2)
{
  // Analyse profile extremum
  for (int i = pBegin; i<=pEnd; i++)
  {
    if (i == ExtPoint) continue;
    if (pMaxOrMin == MAX) // max
    {
      if (Profile[i] > Profile[ExtPoint]) // found point > max
        return false;
      if (Der2 != NULL && Der2[i] >= 0.) // for stable max Der2 always < 0
        return false;
    }
    else
    {
      if (Profile[i] < Profile[ExtPoint]) // found point < min
        return false;
      if (Der2 != NULL && Der2[i] <= 0.) // for stable min Der2 always > 0
        return false;
    }
  }
  // Stable extremum
  return true;
}
//---------------------------------------------------------------------------
// Check whether the function is changing sign (so unstable) in window [i1,i2]
//---------------------------------------------------------------------------
bool TPulse::CheckCondition(const int i, const int i1, const int i2,
                            const float *pOtherFunction, const bool pOtherLessOrMore,
                            const float pOtherLessOrMoreThan, const int pOtherStabilityZone)
{
  int lBegin, lEnd;
  if (pOtherStabilityZone > 0)
  {
    lBegin = (i - pOtherStabilityZone > 0 ?
              i - pOtherStabilityZone : i1);
    lEnd =   (i + pOtherStabilityZone <= End ?
              i + pOtherStabilityZone : i2);
    // lBegin = max(i1, i - pOtherStabilityZone);
    // lEnd   = min(i2, i + pOtherStabilityZone);
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
    for (int i = lBegin; i < lEnd; i++)
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
      return false;
  }
  return true;
}
/* ###########################################################################
 ** math_SmoothArray()
 **
 ** DESCRIPTION
 **  Smooth pulse profile using running average algorithm
 ** INPUT
 **  pNofFilterPoints - Number of Filter points (usually 5, must be odd)
 ** OUTPUT
 **  smoothed profile
 ** RETURN
 **  true if success, false otherwise
*/
//---------------------------------------------------------------------------
bool TPulse::Smooth(const int pSmoothOrder)
{
  // Pulse Validation
  if (Validate()==false)
    return false;
  // Call math function
  return math_SmoothArray(Profile, FSize, pSmoothOrder);
}
/* ###########################################################################
 ** GainOffset ()
 **
 ** DESCRIPTION
 **  Find Gain, Offset coefficients to calibrate pulse in Range [Dp, Sp]
 ** INPUT
 **  Pulse class
 **  [pDp, pSp] - range of calibration
 ** OUTPUT
 **  pGain, pOffset - calculated coefficients
 ** RETURN
 **  boolean success or not
*/
//---------------------------------------------------------------------------
bool TPulse::GainOffset(float &pGain, float &pOffset, const float pDp, const float pSp)
{
  // Range Validation
  if (pDp >= pSp)
  {
    MsgBox(TERROR, MSG_MATH_ERROR, MSG_WRONG_RANGE,
           LoadStr(MSG_WRONG_RANGE) + FloatToStr(pDp) + ", " + FloatToStr(pSp));
    return false;
  }
  // Find Min, Max
  float lMin, lMax;
  if (MinMax(lMin, lMax) == false)
  {
    return false;
  }

  // Find Gain, Offset
  pGain = float(pSp - pDp) / (lMax - lMin);
  pOffset = float(pSp) - pGain * lMax;

  return true;
}

/* ###########################################################################
 ** Average ()
 **
 ** DESCRIPTION
 **  Find Average value of a pulse
 ** INPUT
 **  Pulse class
 ** OUTPUT
 ** RETURN
 **  Average value
*/
//---------------------------------------------------------------------------
float TPulse::Average()
{
  return Average(Start, End + 1);
}

/* ###########################################################################
 ** Average (int pBegin, int pEnd)
 **
 ** DESCRIPTION
 **  Find pulse average value on  interval [pBegin, pEnd]
 ** INPUT
 **  Pulse class
 **  pBegin, pEnd - interval
 ** OUTPUT
 ** RETURN
 **  Average value
*/
//---------------------------------------------------------------------------
float TPulse::Average(int pBegin, int pEnd)
{
  float lAv = -1.;
  // Validate pulse
  if (Validate()==false)
    return lAv;
  // Validate interval
  if (IsIntervalValid(pBegin, pEnd)==false)
    return lAv;

  // Averaging
  double d = 0.;
  float l = pEnd - pBegin;
  for (int i = pBegin; i < pEnd; i++)
  {
    d += Profile[i]/l;
  }
  lAv = (float)d;
  return lAv;
}

/* ###########################################################################
 ** Integral (int pBegin, int pEnd)
 **
 ** DESCRIPTION
 **  Use trapesoid formula to integrate pulse profile on interval [pBegin, pEnd]:
 **  End point pEnd included in formula. Abscissa step = 1.
 **  Int = (f[pBegin] + 2*f[pBegin+1] + 2*f[pBegin+2]... + 2*f[pEnd - 1] + f[pEnd])/2
 ** INPUT
 **  Pulse class
 **  pBegin, pEnd - interval
 ** OUTPUT
 ** RETURN
 **  Integral value
*/
//---------------------------------------------------------------------------
float TPulse::Integral()
{
  return Integral(Start, End);
}
//---------------------------------------------------------------------------
float TPulse::Integral(int pBegin, int pEnd)
{
  float lAv = -DEFAULT_VALUE; // -9999

  // Validate pulse
  if (Validate()==false)
    return lAv;
  // Validate interval
  if (IsIntervalValid(pBegin, pEnd+1)==false)
    return lAv;

  // Integrating
  double d = Profile[pBegin]/2;
  // float l = pEnd - pBegin;
  for (int i = pBegin + 1; i < pEnd; i++)
  {
    d += Profile[i];
  }
  d += Profile[pEnd]/2;

  lAv = (float)d;
  return lAv;
}

float TPulse::Integral(int pBegin, int pEnd, int pBaseLine)
{
  float lAv = -DEFAULT_VALUE; // -9999

  // Validate pulse
  if (Validate()==false)
    return lAv;
  // Validate interval
  if (IsIntervalValid(pBegin, pEnd+1)==false)
    return lAv;

  // Integrating
  double d = Profile[pBegin]/2 - pBaseLine;
  // float l = pEnd - pBegin;
  for (int i = pBegin + 1; i < pEnd; i++)
  {
       d = d + (Profile[i] - pBaseLine);
  }
  d = d + (Profile[pEnd] / 2 - pBaseLine);

  lAv = (float)d;
  return lAv;
}

/* ###########################################################################
 ** MaxDerivative1()
 **
 ** DESCRIPTION
 **  Find maximum the 1st derivative of pulse
 ** INPUT
 **  Pulse class
 **  i1, i2 > i1 - indexes
 ** OUTPUT
 ** RETURN
 **  Maximum value
*/
//---------------------------------------------------------------------------
float TPulse::MaxDerivative1(const int i1, const int i2, const int pSmoothOrder)
{
  float lMaxDer1 = DEFAULT_VALUE;

  // Validate pulse
  if (Validate()==false)
    return lMaxDer1;
  // Validate interval
  if (IsIntervalValid(i1, i2)==false)
    return lMaxDer1;

  // Allocate memory for derivative array
  float* lDer1 = new float [FSize];

  // Calculate derivative
  // int NofDer1Points;
  // math_Derivative1(Profile, FLength, 1., lDer1, NofDer1Points, lMaxDer1);
  math_SmoothDerivative1(Profile, FSize, pSmoothOrder, 1., lDer1, lMaxDer1);

  // Find Max
  lMaxDer1 = lDer1[i1];
  for (int i = i1; i < i2; i++)
    if (lDer1[i] > lMaxDer1)
      lMaxDer1 = lDer1[i];

  // Free memory
  delete [] lDer1;

  // return
  return lMaxDer1;
}
/* ###########################################################################
 ** Sum ()
 **
 ** DESCRIPTION
 **  Find Sum of a pulse sample values
 ** INPUT
 **  Pulse class
 ** OUTPUT
 ** RETURN
 **  Sum
*/
//---------------------------------------------------------------------------
float TPulse::Sum()
{
  return Sum(Start, End + 1);
}

/* ###########################################################################
 ** Sum (int pBegin, int pEnd)
 **
 ** DESCRIPTION
 **  Find pulse sum on  interval [pBegin, pEnd]
 ** INPUT
 **  Pulse class
 **  pBegin, pEnd - interval
 ** OUTPUT
 ** RETURN
 **  Sum
*/
//---------------------------------------------------------------------------
float TPulse::Sum (int pBegin, int pEnd)
{
  float lAv = -DEFAULT_VALUE;
  // Validate pulse
  if (Validate()==false) return lAv;
  // Validate interval
  if (IsIntervalValid(pBegin, pEnd)==false) return lAv;

  // Summarising
  double d = 0.;
  for (int i = pBegin; i < pEnd; i++)
  {
    d += Profile[i];
  }
  lAv = (float)d;
  return lAv;
}

/* ###########################################################################
 ** IsIntervalValid (int pBegin, int pEnd)
 **
 ** DESCRIPTION
 **  Check interval pBegin, pEnd is inside the pulse
 **  and show message if not
 ** INPUT
 **  Pulse class
 **  pBegin, pEnd - interval points
 ** OUTPUT
 ** RETURN
 **  true - if Yes, false - otherwise
*/
//---------------------------------------------------------------------------
bool TPulse::IsIntervalValid (const int pBegin, const int pEnd, const bool pShowMessage)
{
  // Validate interval
  if ((pBegin >= pEnd) /*||(pBegin > Start)||(pEnd > End + 1)*/)
  {
    if (pShowMessage)
    {
      MsgBox(TERROR, GetCurrentPwaMeasureDetails(), MSG_MATH_ERROR, MSG_OUT_OF_PULSE,
             LoadStr(MSG_OUT_OF_PULSE) + IntToStr(FSize) + ", "
             + IntToStr(pBegin) + ", "+ IntToStr(pEnd));
    }
    return false;
  }
  // Success
  return true;
}

/* ###########################################################################
 ** Value (float pTime)
 **
 ** DESCRIPTION
 **  Find Value of a pulse in x-point pTime
 **  assuming each point "contains" SampleRate
 ** INPUT
 **  Pulse class
 **  pTime - point
 **  pSampleRate
 ** OUTPUT
 ** RETURN
 **  Value in this point
*/
//---------------------------------------------------------------------------
float TPulse::ValueAsTime(const float pTime) //, const int pSampleRate)
{
  float lValue = -1.;
  // Validate
  if (Validate()==false)
    return lValue;
  if (SampleRate <= 0)
  {
    // throw Exception((LoadStr(MSG_MATH_ERROR) + " : " + LoadStr(MSG_WRONG_PULSE));
    MsgBox(TERROR, MSG_MATH_ERROR, MSG_WRONG_PULSE_SAMPLERATE);
    return lValue;
  }

  double rate = 1000./SampleRate; // (Time in msec)

  // Validate pPoint
  float lEnd = (FLength-1)*rate;

  if ((pTime < 0.)||(pTime > lEnd))
  {
    MsgBox(TERROR, GetCurrentPwaMeasureDetails(), MSG_MATH_ERROR, MSG_POINT_OUT_OF_PULSE,
            LoadStr(MSG_POINT_OUT_OF_PULSE) + IntToStr((int)pTime) + ", 0 , " + FloatToStr(lEnd));
    return lValue;
  }
  // Catch start point
  if (pTime == 0)
  {
     return Profile[Start];
  }
  // Finding Value
  for (int i = Start + 1; i <= End; i++)
  {
    float moment = i*rate;
    if (moment >= pTime)
    {
      // Linear interpolation
      double N1 = (moment - pTime)/rate;
      double N2 = 1. - N1;
      lValue = N1*Profile[i-1] + N2*Profile[i];
      return lValue;
    }
  }

  return lValue;
}

/* ###########################################################################
 ** Value (float pPoint)
 **
 ** DESCRIPTION
 **  Find Value of a pulse in x-point pPoint
 ** INPUT
 **  Pulse class
 **  pPoint - point
 **  pSampleRate
 ** OUTPUT
 ** RETURN
 **  Value in this point
*/
//---------------------------------------------------------------------------
float TPulse::Value(const float pPoint)
{
  float lValue = -1.;
  // Validate pulse
  if (Validate()==false)
    return lValue;

  // Validate pPoint
  if ((pPoint < Start)||(pPoint > End))
  {
    MsgBox(TERROR, GetCurrentPwaMeasureDetails(), MSG_MATH_ERROR, MSG_POINT_OUT_OF_PULSE,
            LoadStr(MSG_POINT_OUT_OF_PULSE) + IntToStr((int)pPoint) +
            ", " + IntToStr(Start) + " , " + IntToStr(End));
    return lValue;
  }
  // Catch start point
  if (pPoint == Start)
    return Profile[Start];

  // Finding Value
  for (int i = Start + 1; i <= End; i++)
  {
    float moment = i;
    if (moment >= pPoint)
    {
      // Linear interpolation
      double N1 = moment - pPoint;
      double N2 = 1. - N1;
      lValue = N1*Profile[i-1] + N2*Profile[i];
      return lValue;
    }
  }

  return lValue;
}

/* ###########################################################################
 ** IndexToTime
 **
 ** DESCRIPTION
 **  Convert Index into time in msec
 ** INPUT
 **  ind - index
 ** OUTPUT
 ** RETURN
 **  time
*/
//---------------------------------------------------------------------------
float TPulse::IndexToTime(const int pIndex)
{
  if (SampleRate <= 0)
  {
    throw Exception(LoadStr(MSG_MATH_ERROR) + " : " + LoadStr(MSG_WRONG_PULSE_SAMPLERATE));
  }
  float lTime = (pIndex - Start)*1000./SampleRate;
	return lTime;
}

/* ###########################################################################
 ** TimeToIndex
 **
 ** DESCRIPTION
 **  Convert Time into index assuming 0 correspond to start point
 ** INPUT
 **  float pTime
 ** OUTPUT
 ** RETURN
 **  Index
*/
//---------------------------------------------------------------------------
int TPulse::TimeToIndex(const float pTime)
{
  if (SampleRate <= 0)
  {
    throw Exception(LoadStr(MSG_MATH_ERROR) + " : " + LoadStr(MSG_WRONG_PULSE_SAMPLERATE));
  }
  int ind = math_Round(pTime*SampleRate/1000.) + Start;
  if (ind > End || ind < Start)
  {
    throw Exception(LoadStr(MSG_MATH_ERROR) + " : " + LoadStr(MSG_TIME_OUT_OF_RANGE)
         + FloatToStr(pTime) + ", " + IntToStr(Start) + ", " + IntToStr(End));
  }
	return ind;
}

/* ###########################################################################
 ** Height()
 **
 ** DESCRIPTION
 **  Find pulse height (Max - Min)
 ** INPUT
 **  Pulse class
 ** OUTPUT
 ** RETURN
 **  Height
*/
//---------------------------------------------------------------------------
float TPulse::Height()
{
  float lHeight = 0.;
  // Validate pulse
  if (Validate()==false)
    return lHeight;
  // MinMax
  float lMin, lMax;
  if (MinMax(lMin, lMax)==false)
    return lHeight;
  // Height
  //lHeight = lMax - Profile[Start];
  lHeight = lMax - lMin;
  return lHeight;
}
/* ###########################################################################
 ** QC_Height()
 **
 ** DESCRIPTION
 **  Find pulse height (Max - Profile[Start])
 ** INPUT
 **  Pulse class
 ** OUTPUT
 ** RETURN
 **  Height
*/
//---------------------------------------------------------------------------
float TPulse::QC_Height()
{
  float lHeight = 0.;
  // Validate pulse
  if (Validate()==false)
    return lHeight;
  // MinMax
  float lMin, lMax;
  if (MinMax(lMin, lMax)==false)
    return lHeight;
  // Height
  lHeight = lMax - Profile[Start];
  return lHeight;
}
/* ###########################################################################
 ** Length()
 **
 ** DESCRIPTION
 **  Calculate pulse length between [Start, End]
 ** INPUT
 **  Pulse class
 ** OUTPUT
 ** RETURN
 **  Pulse length
*/
//---------------------------------------------------------------------------
int TPulse::Length()
{
  return (Validate() ? FLength : DEFAULT_VALUE);
}
/* ###########################################################################
 ** Size()
 ** DESCRIPTION
 **  Calculate pulse array size between [0, FSize]
 ** INPUT
 **  Pulse class
 ** OUTPUT
 ** RETURN
 **  Pulse array size
*/
//---------------------------------------------------------------------------
int TPulse::Size()
{
  return (Validate() ? FSize : -1);
}

/* ###########################################################################
 ** Shift()
 ** DESCRIPTION
 **  Shift pulse Start point to 0 position and cut tail
 ** INPUT
 **  Pulse class
 ** OUTPUT
 ** RETURN
 **  boolean success or not
*/
//---------------------------------------------------------------------------
bool TPulse::Shift()
{
  if (Validate()==false)
     return false;
  if (Start==0)
     return true;
  // Cut Radial AvPulse convolution tail
  for (int i=0; i<FLength; i++)
  {
     Profile[i]= Profile[Start + i];
  }
  Start = 0;
  End = (short int) (FLength-1);
  FSize = FLength;
  return Validate();
}

/* ###########################################################################
 ** PulseEnd()
 **
 ** DESCRIPTION
 **  Find pulse end value (Profile[FLength-1])
 ** INPUT
 **  Pulse class
 ** OUTPUT
 ** RETURN
 **  End value
*/
//---------------------------------------------------------------------------
float TPulse::PulseEndValue()
{
  return (Validate() ? Profile[End] : DEFAULT_VALUE);
}
/* ###########################################################################
 ** DownSample()
 **
 ** DESCRIPTION
 **  Resample pulse from high to low frequency
 ** (for example, from 1024 to 128 Htz)
 ** INPUT
 **  pPulse - input high frequency pulse
 **  pDownSampleRate - rate of upsampling (8)
 ** OUTPUT
 ** RETURN
 **  boolean success or not
*/
//---------------------------------------------------------------------------
bool TPulse::DownSample(TPulse *pPulse, const int pDownSampleRate)
{
  // Validation
  if (pPulse->Validate()==false)
    return false;
  if (pDownSampleRate <= 0 || pPulse->SampleRate <= 0)
  {
    MsgBox(TERROR, MSG_MATH_ERROR, MSG_WRONG_PULSE_SAMPLERATE);
    return false;
  }

  Initialise();
  SampleRate = (short int) (pPulse->SampleRate/pDownSampleRate);
  int lSize = (pPulse->Length() - 1)/pDownSampleRate + 1;
  SetLength(lSize);
  SetSize(lSize);
  for (int i=0; i < lSize; i++)
  {
    Profile[i] = pPulse->Profile[pPulse->Start + i*pDownSampleRate];
  }
  return Validate();
}

/* ###########################################################################
 ** Convolution()
 **
 ** DESCRIPTION
 **  Calculate pulse profile by convolution of input pulse
 ** INPUT
 **  pTfc[NofTFC] - transformation coefficients for convolution
 **  pPulse - radial pulse
 ** OUTPUT
 **  none
 ** RETURN
 **  boolean success or not
*/
//---------------------------------------------------------------------------
bool TPulse::Convolution(TPulse *pPulse, const float *pTfc, const int pNofTFC)
{
  // Validate input pulse
  if (pPulse->Validate()==false)
     return false;
  // Initialise this pulse
  Initialise(pPulse->SampleRate);
  SetLength(pPulse->Length());
	// Calculate aortic pulse
	for(int i = 0; i < Length(); i++)
  {
    // Calculate Central for actual signal
    double ld = 0.0;
	  for(int j = 0; j < pNofTFC; j++)
    {
        ld += pTfc[j] * pPulse->Profile[i+j];
    }
	  Profile[i] = ld;
	}
  Index = pPulse->Index;
  return true;
}

