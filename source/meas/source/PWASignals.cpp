//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "PWASignals.h"
#include "Mathem.h"
#include <msg\pubserv.h>
#include <meas\pubserv.h>
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
const float PWA_DER1_THRESHOLD1 = 0.60;
const float PWA_DER1_THRESHOLD2 = 0.55;
const float PWA_DER1_THRESHOLD3 = 0.40; // To find Average Peak of Der1
const int   PWA_MAX_SIGNAL_GRADIENT = 200; // To reject DBASE3 records
const int   PWA_MIN_PULSE_HEIGHT = 30;
const int   PWA_MIN_NOF_ONSETS = 2;
//---------------------------------------------------------------------------
// Constructor and Destructor for TPWASignal Class
//---------------------------------------------------------------------------
TPWASignal::TPWASignal(const int pMaxNofPoints, const int pMaxNofOnsets)
                : TSignal(pMaxNofPoints, pMaxNofOnsets)
{
  // Allocate Der1
  if (pMaxNofPoints > 0)
  {
    Der1 = new float[pMaxNofPoints];
    Der2 = new float[pMaxNofPoints];
    for (int i=0; i<pMaxNofPoints; i++)
    {
      Der1[i] = 0.;
      Der2[i] = 0.;
    }
  }
}
//---------------------------------------------------------------------------
TPWASignal::~TPWASignal()
{
  // free Der1
  if (Der1 != NULL) delete [] Der1;
  if (Der2 != NULL) delete [] Der2;
}
//---------------------------------------------------------------------------
void TPWASignal::Allocate(const int pMaxNofPoints, const int pMaxNofOnsets)
{
  // Allocate Signal
  TSignal::Allocate(pMaxNofPoints, pMaxNofOnsets);
  // Allocate Derivatives
  Der1 = new float[pMaxNofPoints];
  Der2 = new float[pMaxNofPoints];
  for (int i=0; i<pMaxNofPoints; i++)
  {
    Der1[i] = 0.;
    Der2[i] = 0.;
  }
}
/* ###########################################################################
 ** ValidateSignal()
 **
 ** DESCRIPTION
 **  Validate Signal
 ** INPUT
 ** OUTPUT
 **   Class properties
 ** RETURN
 **  boolean success or not
*/
//---------------------------------------------------------------------------
bool TPWASignal::ValidateSignal(const int pMinNofPoints)
{
  // Validate length
  if (ValidateSignalLength(pMinNofPoints)==false)
  {
    return false;
  }
  // Validate length
  if (ValidateSignalHeight(PWA_MIN_PULSE_HEIGHT)==false)
  {
    return false;
  }
  return true;
}

/* ###########################################################################
 ** FindOnsets()
 **
 ** DESCRIPTION
 **  Find trigger points (onsets) for a signal
 ** INPUT
 **  Class properties(source)
 ** OUTPUT
 **  boolean success or not
*/
//---------------------------------------------------------------------------
bool TPWASignal::FindOnsets(const int pAlgorithm, const int pMinTrigPt)
{
  // Initialise Onsets
  NofOnsets = 0;
	for(int i = 0; i < MaxNofOnsets; i++)
  {
    Onsets[i] = -1;
  }
  // Validate
  if (SampleRate <= 0)
    return false;
  // Find Derivative 1 and its max
  float lAbsMaxDer1, lMaxDer2, lAvMaxDer1;
  math_SmoothDerivative1(Signal, NofPoints, 2, 1., Der1, lAbsMaxDer1);
  if (lAbsMaxDer1 <= 0)
    return false;
  // Try to find Average of the peaks of Der1 which is higher
  // then 55% of absolute max of Der1
  lAvMaxDer1 = 0;
  int lNofPeaks = 0;
  int lNofLoops = 0;
  do
  {
    int lPeakOfDer1 = pMinTrigPt;
    while (lPeakOfDer1 >= 0)
    {
      lPeakOfDer1 = math_IndexOfExtremum(Der1, MAX, FIRST, lPeakOfDer1, NofPoints,
                                         MORE, PWA_DER1_THRESHOLD3*lAbsMaxDer1);
      if (lPeakOfDer1 >= 0)
      {
        if (Der1[lPeakOfDer1] < lAbsMaxDer1) // Avoid largest maximum
        {
           lAvMaxDer1 += Der1[lPeakOfDer1];
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
        lAbsMaxDer1 *= 0.9;
      }
      else // To prevent infinite loop
      {
        lAvMaxDer1 = lAbsMaxDer1;
        break;
      }
    }
  } while (lNofPeaks <= 3);

  // Minimal pulse length
  int lMinPulseLength = 60. * SampleRate / MAX_HR;

  // Algorithm switch. Algorithm2 must have been executed before other algorithms
  switch (pAlgorithm)
  {
    case PWA_DER1_ALGORITHM:
      // Find Onsets using Algorithm2
      return AlgorithmDer1(lAvMaxDer1, pMinTrigPt, lMinPulseLength);
    case PWA_DER2_ALGORITHM:
      math_SmoothDerivative1(Der1, NofPoints, 2, 1., Der2, lMaxDer2);
      // Find Onsets using Algorithm3
      return AlgorithmDer2(lAvMaxDer1, pMinTrigPt, lMinPulseLength);
    case PWA_TANGENT_DER1_ALGORITHM:
      // Find Onsets using Algorithm2
      return AlgorithmTangentDer1(lAvMaxDer1, pMinTrigPt, lMinPulseLength);
    case PWA_TANGENT_DER2_ALGORITHM:
      math_SmoothDerivative1(Der1, NofPoints, 2, 1., Der2, lMaxDer2);
      // Find Onsets using Algorithm4
      return AlgorithmTangentDer2(lAvMaxDer1, pMinTrigPt, lMinPulseLength);
  }
  return (NofOnsets > PWA_MIN_NOF_ONSETS);
}
/* ###########################################################################
 ** AlgorithmDer2()
 **
 ** DESCRIPTION
 **  Find onsets using maxDer2 algorithm
 ** INPUT
 ** OUTPUT
 **  Class properties(source)
 ** RETURN
 **  boolean success or not
*/
//---------------------------------------------------------------------------
bool TPWASignal::AlgorithmDer2(const float pAvMaxDer1, const int pMinTrigPt,
                               const int pMinPulseLength)
{
  // ThresHold values
  float lThresHold1 = PWA_DER1_THRESHOLD1 * pAvMaxDer1;
  float lThresHold2 = PWA_DER1_THRESHOLD2 * pAvMaxDer1;

  // Find Trigger Points
  bool  WeAreInPeak = false;
  bool  Beginning = true;
  int   lPeakIndex = -1, lFootIndex;

  // Main loop
  for (int i = pMinTrigPt; i < NofPoints; i++)
  {
    // Avoid signal beginning where values already above threashold
    if (Beginning == true)
    {
      if (Der1[i] >= lThresHold1)
        continue;
      Beginning = false;
    }
    // Avoid MinPulseLength zone after last onset being found
    if (NofOnsets > 0 && (i - Onsets[NofOnsets - 1] < pMinPulseLength))
      continue;
    // Find Peak
    // avoid beginning of a wave
    if ((WeAreInPeak == false) && (Der1[i] < lThresHold1))
      continue;

    // Begin of peak
    if (WeAreInPeak==false)
      WeAreInPeak = true;

    if (Der1[i] > lThresHold2)
    {
      // We are in Peak first point
      if (lPeakIndex < 0)
      {
        lPeakIndex = i;
        continue;
      }
      // Find max in peak
      if (Der1[i] > Der1[lPeakIndex])
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
      int lInitPeakIndex = ((NofOnsets > 0) ? Onsets[NofOnsets-1] : pMinTrigPt);
      lFootIndex = -1;

      // Find foot points found where Previous > Current
      for (int j = lPeakIndex; j > lInitPeakIndex; j--)
      {
        if (Signal[j] <= Signal[j-1])
        //if (Der1[j] <= 0.)
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

      // Find point where Der2 has a positive maximum between lFootIndex and PeakIndex
      float lMaxDer2 = 0.;
      int lIndOfMaxDer2 = -1;
      for (int j = lFootIndex; j < lPeakIndex; j++)
      {
        if (Der2[j] > lMaxDer2)
        {
          lIndOfMaxDer2 = j;
          lMaxDer2 = Der2[j];
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
      Onsets[NofOnsets] = (short int)lIndOfMaxDer2;
      NofOnsets++;
      WeAreInPeak = false;
      lPeakIndex = -1;
      // Check NofOnsets limit. If more, stop process
      if (NofOnsets == MaxNofOnsets) break;
    }
  } // End of Main loop

  // return
  return (NofOnsets > PWA_MIN_NOF_ONSETS);
}
/* ###########################################################################
 ** AlgorithmDer1()
 **
 ** DESCRIPTION
 **  Find onsets using Der1 = 0 algorithm
 ** INPUT
 ** OUTPUT
 **  Class properties(source)
 ** RETURN
 **  boolean success or not
*/
//---------------------------------------------------------------------------
bool TPWASignal::AlgorithmDer1(const float pAvMaxDer1, const int pMinTrigPt,
                               const int pMinPulseLength)
{
  // ThresHold values
  float lThresHold1 = PWA_DER1_THRESHOLD1 * pAvMaxDer1;
  float lThresHold2 = PWA_DER1_THRESHOLD2 * pAvMaxDer1;

  // Find Trigger Points
  bool  WeAreInPeak = false;
  bool  Beginning = true;
  int   lPeakIndex = -1, lFootIndex;

  // Main loop
  for (int i = pMinTrigPt; i < NofPoints; i++)
  {
    // Avoid signal beginning where values already above threashold
    if (Beginning == true)
    {
      if (Der1[i] >= lThresHold1)
        continue;
      Beginning = false;
    }
    // Avoid MinPulseLength zone after last onset being found
    if (NofOnsets > 0 && (i - Onsets[NofOnsets - 1] < pMinPulseLength))
      continue;
    // Find Peak
    // avoid beginning of a wave
    if ((WeAreInPeak == false) && (Der1[i] < lThresHold1))
      continue;

    // Begin of peak
    if (WeAreInPeak==false)
      WeAreInPeak = true;

    if (Der1[i] > lThresHold2)
    {
      // We are in Peak first point
      if (lPeakIndex < 0)
      {
        lPeakIndex = i;
        continue;
      }
      // Find max in peak
      if (Der1[i] > Der1[lPeakIndex])
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
      int lInitPeakIndex = ((NofOnsets > 0) ? Onsets[NofOnsets-1] : pMinTrigPt);
      lFootIndex = -1;

      // Find foot points found where Previous > Current
      for (int j = lPeakIndex; j > lInitPeakIndex; j--)
      {
        if (Signal[j] <= Signal[j-1])
        //if (Der1[j] <= 0.)
        {
          lFootIndex = j;
          break;
        }
      }
      if (lFootIndex < 0 || lFootIndex <= lInitPeakIndex)
      {
        lPeakIndex = -1;
        continue;
      }

      // After onset has been found
      NofOnsets++;
      Onsets[NofOnsets-1] = (short int)lFootIndex;
      WeAreInPeak = false;
      lPeakIndex = -1;
      // Check NofOnsets limit. If more, stop process
      if (NofOnsets == MaxNofOnsets) break;
    }
  } // End of Main loop

  // return
  return (NofOnsets > PWA_MIN_NOF_ONSETS);
}
/* ###########################################################################
 ** Algorithm3()
 **
 ** DESCRIPTION
 **  Find onsets using tangent algorithm (crossing of
 **  pulse foot line by tangent at point of max dP/dt
 ** INPUT
 ** OUTPUT
 **  Class properties(source)
 ** RETURN
 **  boolean success or not
*/
//---------------------------------------------------------------------------
bool TPWASignal::AlgorithmTangentDer1(const float pMaxDer1, const int pMinTrigPt,
                                      const int pMinPulseLength)
{
  // ThresHold values
  // float lThresHold1 = PWV_DER1_THRESHOLD1 * pMaxDer1;
  // float lThresHold2 = PWV_DER1_THRESHOLD2 * pMaxDer1;
  float lThresHold1 = PWA_DER1_THRESHOLD1 * pMaxDer1;
  float lThresHold2 = PWA_DER1_THRESHOLD2 * pMaxDer1;

  // Find Trigger Points
  bool  WeAreInPeak = false;
  bool Beginning = true;
  int   lPeakIndex = -1, lFootIndex;
  // Main loop
  for (int i = pMinTrigPt; i < NofPoints; i++)
  {
    // Avoid signal beginning where values already above threashold
    if (Beginning == true)
    {
      if (Der1[i] >= lThresHold1)
        continue;
      Beginning = false;
    }
    // Avoid MinPulseLength zone after last onset being found
    if (NofOnsets > 0 && (i - Onsets[NofOnsets - 1] < pMinPulseLength))
      continue;
    // Find Peak
    // avoid beginning of a wave
    if ((WeAreInPeak == false) && (Der1[i] < lThresHold1))
      continue;

    // Begin of peak
    if (WeAreInPeak==false)
      WeAreInPeak = true;

    if (Der1[i] > lThresHold2)
    {
      // We are in Peak first point
      if (lPeakIndex < 0)
      {
        lPeakIndex = i;
        continue;
      }
      // Find max in peak
      if (Der1[i] > Der1[lPeakIndex])
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
      int lInitPeakIndex = ((NofOnsets > 0) ? Onsets[NofOnsets-1] + 1: pMinTrigPt);
      lFootIndex = -1;

      // Find foot points where Der1 has a positive zero crossing
      for (int j = lPeakIndex; j > lInitPeakIndex; j--)
      {
        // if (Der1[j] <= 0.)
        if (Signal[j] <= Signal[j-1])
        {
          lFootIndex = j;
          break;
        }
      }
      float lTangent = Der1[lPeakIndex]; // tangent is a Der1 value in point maxDpDt
      // Validate
      if (lFootIndex < 0 || lTangent <= 0.)
      {
        lPeakIndex = -1;
        continue;
      }
      // After foot has been found
      // Solve triangle to get time-shift
      float lVertShoulder = Signal[lPeakIndex] - Signal[lFootIndex];
      float lHorizShoulder = lVertShoulder/lTangent;
      // Find onset
      if (float(lPeakIndex) - lHorizShoulder > lInitPeakIndex)
      {
        Onsets[NofOnsets] = (short int) math_Round(float(lPeakIndex) - lHorizShoulder);
        // FloatOnsets[NofOnsets] = (float(lPeakIndex) - lHorizShoulder);
        NofOnsets++;
      }
      lPeakIndex = -1;
      // Check NofOnsets limit. If more, stop process
      if (NofOnsets == MaxNofOnsets) break;
    }
  } // End of Main loop

  // return
  return (NofOnsets >= PWA_MIN_NOF_ONSETS);
}

/* ###########################################################################
 ** AlgorithmTangentDer2()
 **
 ** DESCRIPTION
 **  Find onsets using maxDer2 algorithm
 ** INPUT
 ** OUTPUT
 **  Class properties(source)
 ** RETURN
 **  boolean success or not
*/
//---------------------------------------------------------------------------
bool TPWASignal::AlgorithmTangentDer2(const float pAvMaxDer1, const int pMinTrigPt,
                                      const int pMinPulseLength)
{
  // ThresHold values
  float lThresHold1 = PWA_DER1_THRESHOLD1 * pAvMaxDer1;
  float lThresHold2 = PWA_DER1_THRESHOLD2 * pAvMaxDer1;

  // Find Trigger Points
  bool  WeAreInPeak = false;
  bool  Beginning = true;
  int   lPeakIndex = -1, lFootIndex;

  // Main loop
  for (int i = pMinTrigPt; i < NofPoints; i++)
  {
    // Avoid signal beginning where values already above threashold
    if (Beginning == true)
    {
      if (Der1[i] >= lThresHold1)
        continue;
      Beginning = false;
    }
    // Avoid MinPulseLength zone after last onset being found
    if (NofOnsets > 0 && (i - Onsets[NofOnsets - 1] < pMinPulseLength))
      continue;

    // Find Peak
    // avoid beginning of a wave
    if ((WeAreInPeak == false) && (Der1[i] < lThresHold1))
      continue;

    // Begin of peak
    if (WeAreInPeak==false)
      WeAreInPeak = true;

    if (Der1[i] > lThresHold2)
    {
      // We are in Peak first point
      if (lPeakIndex < 0)
      {
        lPeakIndex = i;
        continue;
      }
      // Find max in peak
      //if (Signal[j] <= Signal[j-1])
      //if (Der1[i] > Der1[lPeakIndex])
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
      int lInitPeakIndex = ((NofOnsets > 0) ? Onsets[NofOnsets-1] : pMinTrigPt);
      lFootIndex = -1;

      // Find foot points found where Previous > Current
      for (int j = lPeakIndex; j > lInitPeakIndex; j--)
      {
        if (Signal[j] <= Signal[j-1])
        //if (Der1[j] <= 0.)
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

      // Find point where Der2 has a positive maximum between lFootIndex and PeakIndex
      float lMaxDer2 = 0.;
      int lIndOfMaxDer2 = -1;
      for (int j = lFootIndex; j < lPeakIndex; j++)
      {
        if (Der2[j] > lMaxDer2)
        {
          lIndOfMaxDer2 = j;
          lMaxDer2 = Der2[j];
        }
      }
      // Validate
      if (lIndOfMaxDer2 < 0 || lMaxDer2 <= 0.)
      {
        lPeakIndex = -1;
        continue;
      }
      // After onset has been found
      float lTangent = Der1[lIndOfMaxDer2]; // tangent is a Der1 value in point maxDpDt
      // Validate
      if (lFootIndex < 0 || lTangent <= 0.)
      {
        lPeakIndex = -1;
        continue;
      }
      // After foot has been found
      // Solve triangle to get time-shift
      float lVertShoulder = Signal[lIndOfMaxDer2] - Signal[lFootIndex];
      float lHorizShoulder = lVertShoulder/lTangent;
      // Find onset
      float lFloatOnset = float(lIndOfMaxDer2) - lHorizShoulder;
      if (lFloatOnset <= lFootIndex)
        lFloatOnset = lFootIndex;
      if (lFloatOnset > lInitPeakIndex)
      {
        Onsets[NofOnsets] = (short int) math_Round(lFloatOnset);
        NofOnsets++;
      }
      WeAreInPeak = false;
      lPeakIndex = -1;
      // Check NofOnsets limit. If more, stop process
      if (NofOnsets == MaxNofOnsets) break;
    }
  } // End of Main loop

  // return
  return (NofOnsets > PWA_MIN_NOF_ONSETS);
}

