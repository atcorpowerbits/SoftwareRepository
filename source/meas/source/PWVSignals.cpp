//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include <stdlib.h>

#include <msg\pubserv.h>
#include <log\pubserv.h>

#include "Common.h"
#include "Mathem.h"
#include "PWVSignals.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
const float PWV_DER1_THRESHOLD1 = 0.70;
const float PWV_DER1_THRESHOLD2 = 0.65;
const float PWV_DER1_THRESHOLD3 = 0.40; // To find Average Peak of Der1
const int PWV_MAX_SIGNAL_GRADIENT = 200;
const float PULSE_HEIGHT_THRESHOLD = 0.65; // Percent to get signal peak
const int PWV_ARRAY_SIZE_FOR_PEAKS = 50;
const float PWV_ECG_FILTER_THRESHOLD = 0.47;
//---------------------------------------------------------------------------
// Constructor and Destructor for TPWVTonomSignal Class
//---------------------------------------------------------------------------
TPWVTonomSignal::TPWVTonomSignal(const int pMaxNofPoints, const int pMaxNofOnsets)
                :TSignal(pMaxNofPoints, pMaxNofOnsets)
{
  // Allocate Derivatives
  if (pMaxNofPoints > 0)
  {
    Der1 = new float[pMaxNofPoints];
    Der2 = new float[pMaxNofPoints];
  }
  QC_PulseHeight = DEFAULT_VALUE;
  QC_PulseHeightVariation = DEFAULT_VALUE;
  QC_PulseLengthVariation = DEFAULT_VALUE;
  QC_BaseLineVariation = DEFAULT_VALUE;
}
//---------------------------------------------------------------------------
TPWVTonomSignal::~TPWVTonomSignal()
{
  // free Derivatives
  if (Der1 != NULL) delete [] Der1;
  if (Der2 != NULL) delete [] Der2;
}
//---------------------------------------------------------------------------
void TPWVTonomSignal::Allocate(const int pMaxNofPoints, const int pMaxNofOnsets)
{
  // Allocate Signal
  TSignal::Allocate(pMaxNofPoints, pMaxNofOnsets);
  // Allocate Derivatives
  Der1 = new float[pMaxNofPoints];
  Der2 = new float[pMaxNofPoints];
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
bool TPWVTonomSignal::ValidateSignal(const int pMinNofPoints)
{
  // Validate length
  if (ValidateSignalLength(pMinNofPoints)==false)
  {
    return false;
  }
  // Validate Height
  if (ValidateSignalHeight(PWV_TON_MIN_PULSEHEIGHT)==false)
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
bool TPWVTonomSignal::FindOnsets(const int pAlgorithm, const float pHeightPercent)
{
  bool ret = false;
  // Initialise Onsets
	for(int i = 0; i < MaxNofOnsets; i++)
  {
    FloatOnsets[i] = -1;
  }
  NofOnsets = 0;
  try
  {
    // Find Derivative 1 and its max
    float lAbsMaxDer1, lAvMaxDer1;
    math_SmoothDerivative1(Signal, NofPoints, 3, 1., Der1, lAbsMaxDer1);
    float lAbsMaxDer2;
    math_SmoothDerivative1(Der1, NofPoints, 3, 1., Der2, lAbsMaxDer2);

    // Try to find Average of the peaks of Der1 which is higher
    // then 55% of absolute max of Der1
    lAvMaxDer1 = 0;
    int lNofPeaks = 0;
    int lNofLoops = 0;
    do
    {
      int lPeakOfDer1 = 0;
      while (lPeakOfDer1 >= 0)
      {
        lPeakOfDer1 = math_IndexOfExtremum(Der1, MAX, FIRST, lPeakOfDer1, NofPoints,
                                           MORE, PWV_DER1_THRESHOLD3*lAbsMaxDer1);
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
      case 1:
        // Standard percentage of pulse height algorithm
        // ret = TSignal::FindOnsets(pHeightPercent, PWV_TON_MIN_PULSEHEIGHT);
        // break;
        ret = Algorithm1(lAvMaxDer1, lMinPulseLength, pHeightPercent);
        break;
      case 2:
        // Find Onsets using Algorithm2
        ret = Algorithm2(lAvMaxDer1, lMinPulseLength);
        break;
      case 3:
        // Find Onsets using Algorithm3
        ret = Algorithm3(lAvMaxDer1, lMinPulseLength);
        break;
      case 4:
        // Find Derivative 1 and its max
        float lAbsMaxDer2;
        math_SmoothDerivative1(Der1, NofPoints, 3, 1., Der2, lAbsMaxDer2);
        // Find Onsets using Algorithm4
        ret = Algorithm4(lAvMaxDer1, lMinPulseLength, Der2);
        break;
    }
  }
  catch (Exception &e)
  {
    Application->ShowException(&e);
    ret = false;
  }
  if (ret == false || NofOnsets < PWV_MIN_NOF_ONSETS)
  {
    MsgBox(TERROR, GetCurrentPwvMeasureDetails(), MSG_MATH_ERROR, MSG_PWV_TRIGGER_ERR);
    return false;
  }
  return true;
}

/* ###########################################################################
 ** Algorithm1()
 **
 ** DESCRIPTION
 **  Find onsets using Percent of PulseHeight algorithm
 ** INPUT
 ** OUTPUT
 **  Class properties(source)
 ** RETURN
 **  boolean success or not
*/
//---------------------------------------------------------------------------
bool TPWVTonomSignal::Algorithm1(const float pMaxDer1, const int pMinPulseLength,
                                 const float pHeightPercent)
{
  // ThresHold values
  float lThresHold1 = PWV_DER1_THRESHOLD1 * pMaxDer1;
  float lThresHold2 = PWV_DER1_THRESHOLD2 * pMaxDer1;

  // Find Trigger Points
  bool  WeAreInPeak = false;
  bool Beginning = true;
  int   lDer1PeakIndex = -1, lPeakIndex, lFootIndex;

  // Main loop
  for (int i = 0; i < NofPoints; i++)
  {
    // Avoid signal beginning where values already above threashold
    if (Beginning == true)
    {
      if (Der1[i] >= lThresHold1)
        continue;
      Beginning = false;
    }
    // Avoid MinPulseLength zone after last onset being found
    if (NofOnsets > 0 && (i - FloatOnsets[NofOnsets - 1] < pMinPulseLength))
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
      if (lDer1PeakIndex < 0)
      {
        lDer1PeakIndex = i;
        continue;
      }
      // Find max in peak
      if (Der1[i] > Der1[lDer1PeakIndex])
      {
        lDer1PeakIndex = i;
      }
    }
    else
    {
      WeAreInPeak = false;
      if (lDer1PeakIndex < 0)
        continue;
      // End of Peak. Go back to find point where Signal has minimum;
      int lInitPeakIndex = ((NofOnsets > 0) ? FloatOnsets[NofOnsets-1] + 1: 0);
      lFootIndex = -1;
      // Find foot points found where Previous > Current
      for (int j = lDer1PeakIndex; j > lInitPeakIndex; j--)
      {
        if (Signal[j] <= Signal[j-1])
        {
          lFootIndex = j;
          break;
        }
      }
      // Find Signal peak
      lPeakIndex = math_IndexOfExtremum(Signal, MAX, FIRST, lDer1PeakIndex, NofPoints-1, MORE, Signal[lDer1PeakIndex]);
      if (lFootIndex < 0 || lPeakIndex < 0)
      {
        lDer1PeakIndex = -1;
        continue;
      }
      // After foot has been found
      float lPulseHeight = Signal[lPeakIndex] - Signal[lFootIndex];
      /*
      float lPulsePeak;
      float lind = math_IndexOfQuadrInterpMax(lPeakIndex-1, lPeakIndex, lPeakIndex+1,
                   Signal[lPeakIndex-1], Signal[lPeakIndex], Signal[lPeakIndex+1], lPulsePeak);
      float lPulseHeight = (lind >= lPeakIndex-1 ? lPulsePeak - Signal[lFootIndex] : -1);
      */
      // Reject short signal
      if (lPulseHeight < PWV_TON_MIN_PULSEHEIGHT)
      {
        lDer1PeakIndex = -1;
        continue;
      }
      float lOnset = -1;
      if (pHeightPercent == 0) // If pHeightPercent == 0 then Onset = FootIndex
      {
        lOnset = lFootIndex;
      }
      else // Catch point where Signal cross treashold
      {
        // ThresHold value for pHeightPercent of PulseHeight
        float lThresHold2 = Signal[lFootIndex] + pHeightPercent/100. * lPulseHeight;
        for (int j = lFootIndex; j < lPeakIndex; j++)
        {
          if (Signal[j] < lThresHold2)
            continue;
          if (Signal[j] <= Signal[j-1]) // To prevent zero devide
            continue;
          // Select nearest point between j and j-1
          // lOnset = (Signal[j] - lThresHold2 >= lThresHold2 - Signal[j-1] ? j-1 : j);
          // Interpolate Signal to catch Treashold value
          double N2 = (lThresHold2 - Signal[j-1])/(Signal[j] - Signal[j-1]);
          double N1 = 1. - N2;
          lOnset = N1*(j-1) + N2*j;
          break;
        }
      }
      // Validate
      if (lOnset > lInitPeakIndex)
      {
        FloatOnsets[NofOnsets] = lOnset;
        NofOnsets++;
      }
      lDer1PeakIndex = -1;
      // Check NofOnsets limit. If more, stop process
      if (NofOnsets == MaxNofOnsets) break;
    }
  } // End of Main loop

  // return
  return (NofOnsets >= PWV_MIN_NOF_ONSETS);
}

/* ###########################################################################
 ** Algorithm2()
 **
 ** DESCRIPTION
 **  Find onsets using maxdP/dt algorithm
 ** INPUT
 ** OUTPUT
 **  Class properties(source)
 ** RETURN
 **  boolean success or not
*/
//---------------------------------------------------------------------------
bool TPWVTonomSignal::Algorithm2(const float pMaxDer1, const int pMinPulseLength)
{
  // ThresHold values
  float lThresHold1 = PWV_DER1_THRESHOLD1 * pMaxDer1;
  float lThresHold2 = PWV_DER1_THRESHOLD2 * pMaxDer1;

  // Find Trigger Points
  bool  WeAreInPeak = false;
  bool  Beginning = true;
  int   lPeakIndex = -1;

  // Main loop
  for (int i = 0; i < NofPoints; i++)
  {
    // Avoid signal beginning where values already above threashold
    if (Beginning == true)
    {
      if (Der1[i] >= lThresHold1)
        continue;
      Beginning = false;
    }
    // Avoid MinPulseLength zone after last onset being found
    if (NofOnsets > 0 && (i - FloatOnsets[NofOnsets - 1] < pMinPulseLength))
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
      // End of Peak. Save peak index
      WeAreInPeak = false;
      if (lPeakIndex < 1)
        continue;
      // FloatOnsets[NofOnsets] = (short int)lPeakIndex;
      // Use quadratic interpolation to find peak value of Der1
      float lMaxDer1;
      float lOnset = math_IndexOfQuadrInterpMax(lPeakIndex-1, lPeakIndex, lPeakIndex+1,
                     Der1[lPeakIndex-1], Der1[lPeakIndex], Der1[lPeakIndex+1], lMaxDer1);
      float lPrevios = (NofOnsets > 0 ? FloatOnsets[NofOnsets-1] : 0);
      if (lOnset < lPeakIndex-1 || lOnset <= lPrevios)
      {
        lPeakIndex = -1;
        continue;
      }
      FloatOnsets[NofOnsets] = lOnset;
      NofOnsets++;
      lPeakIndex = -1;
      // Check NofOnsets limit. If more, stop process
      if (NofOnsets == MaxNofOnsets) break;
    }
  } // End of Main loop
/*
  // Catch last Trigger Point
  if (lPeakIndex > 0 && NofOnsets < MaxNofOnsets)
  {
      NofOnsets++;
      FloatOnsets[NofOnsets-1] = (short int)lPeakIndex;
  }
*/
  // return
  return (NofOnsets >= PWV_MIN_NOF_ONSETS);
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
bool TPWVTonomSignal::Algorithm3(const float pMaxDer1,
                                 const int pMinPulseLength)
{
  // ThresHold values
  float lThresHold1 = PWV_DER1_THRESHOLD1 * pMaxDer1;
  float lThresHold2 = PWV_DER1_THRESHOLD2 * pMaxDer1;

  // Find Trigger Points
  bool  WeAreInPeak = false;
  bool Beginning = true;
  int   lPeakIndex = -1, lFootIndex;
  // Main loop
  for (int i = 0; i < NofPoints; i++)
  {
    // Avoid signal beginning where values already above threashold
    if (Beginning == true)
    {
      if (Der1[i] >= lThresHold1)
        continue;
      Beginning = false;
    }
    // Avoid MinPulseLength zone after last onset being found
    if (NofOnsets > 0 && (i - FloatOnsets[NofOnsets - 1] < pMinPulseLength))
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
      int lInitPeakIndex = ((NofOnsets > 0) ? FloatOnsets[NofOnsets-1] + 1: 0);
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
        FloatOnsets[NofOnsets] = (float(lPeakIndex) - lHorizShoulder);
        NofOnsets++;
      }
      lPeakIndex = -1;
      // Check NofOnsets limit. If more, stop process
      if (NofOnsets == MaxNofOnsets) break;
    }
  } // End of Main loop

  // return
  return (NofOnsets >= PWV_MIN_NOF_ONSETS);
}

/* ###########################################################################
 ** Algorithm4()
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
bool TPWVTonomSignal::Algorithm4(const float pMaxDer1, const int pMinPulseLength,
                                 const float *Der2)
{
  // ThresHold values
  float lThresHold1 = PWV_DER1_THRESHOLD1 * pMaxDer1;
  float lThresHold2 = PWV_DER1_THRESHOLD2 * pMaxDer1;

  // Find Trigger Points
  bool  WeAreInPeak = false;
  bool  Beginning = true;
  int   lPeakIndex = -1, lFootIndex;

  // Main loop
  for (int i = 0; i < NofPoints; i++)
  {
    // Avoid signal beginning where values already above threashold
    if (Beginning == true)
    {
      if (Der1[i] >= lThresHold1)
        continue;
      Beginning = false;
    }
    // Avoid MinPulseLength zone after last onset being found
    if (NofOnsets > 0 && (i - FloatOnsets[NofOnsets - 1] < pMinPulseLength))
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
      int lInitPeakIndex = ((NofOnsets > 0) ? FloatOnsets[NofOnsets-1] : 0);
      lFootIndex = -1;

      // Find foot points found where Der1 has a positive zero crossing
      for (int j = lPeakIndex; j > lInitPeakIndex; j--)
      {
        if (Signal[j] <= Signal[j-1])
        // if (Der1[j] <= 0.)
        {
          lFootIndex = j;
          break;
        }
      }
      // Validate
      if (lFootIndex < 0)
      {
        lPeakIndex = -1;
        continue;
      }
      // After foot has been found
      // Find point where Der2 has a positive maximum
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
      if (lIndOfMaxDer2 < 1 || lMaxDer2 <= 0.)
      {
        lPeakIndex = -1;
        continue;
      }
      // After onset has been found
      lPeakIndex = -1;
      // Use quadratic interpolation to catch float onset
      float lMaxOfDer2;
      float lOnset = math_IndexOfQuadrInterpMax(lIndOfMaxDer2-1, lIndOfMaxDer2, lIndOfMaxDer2+1,
                     Der2[lIndOfMaxDer2-1], Der2[lIndOfMaxDer2], Der2[lIndOfMaxDer2+1], lMaxOfDer2);
      if (lOnset < lIndOfMaxDer2-1)
      {
        continue;
      }
      // FloatOnsets[NofOnsets] = (short int)lIndOfMaxDer2;
      FloatOnsets[NofOnsets] = lOnset;
      NofOnsets++;
      // Check NofOnsets limit. If more, stop process
      if (NofOnsets == MaxNofOnsets) break;
    }
  } // End of Main loop

  // return
  return (NofOnsets >= PWV_MIN_NOF_ONSETS);
}

//---------------------------------------------------------------------------
// Constructor and Destructor for TPWVECGSignal Class
//---------------------------------------------------------------------------
TPWVECGSignal::TPWVECGSignal(const int pMaxNofPoints, const int pMaxNofOnsets)
                : TSignal(pMaxNofPoints, pMaxNofOnsets)
{
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
bool TPWVECGSignal::ValidateSignal(const int pMinNofPoints)
{
  bool ret = ValidateSignalLength(pMinNofPoints);
  if (ret == true)
    ret = ValidateSignalHeight(PWV_ECG_MIN_PULSEHEIGHT);
  return ret;
}

/* ###########################################################################
 ** FindOnsets()
 **
 ** DESCRIPTION
 **  Find ECG onsets
 ** INPUT
 **  pAlgorithm - 1 - 30% of pulse height
 **               2 - index of peak
 ** OUTPUT
 **  none
 ** RETURN
 **  boolean success or not
*/
//---------------------------------------------------------------------------
bool TPWVECGSignal::FindOnsets(PWV_ECG_ONSET_ALGORITHM_TYPE pAlgorithm,
                               const float                  pHeightPercent,
                               const float                  pMinPulseHeight)
{

  // Minimum pulse length
  int lMinPulseLength = 60. * SampleRate / MAX_HR;

  bool ret;
  switch (pAlgorithm)
  {
     case ECG_ALGORITHM_ONSET_PEAKS:
      // Percentage of pulse height algorithm
      ret = Algorithm1(pHeightPercent, lMinPulseLength, pMinPulseHeight);
      break;
    case ECG_ALGORITHM_ONSET_LENGTH:
      // Find Onsets using index of peak
      ret = Algorithm2(lMinPulseLength);
      break;
    case ECG_ALGORITHM_ONSET_FILTER:
      // Find Onsets using index of peak
      ret = Algorithm_QRS_Filter();
      break;
  }
  if (ret == false || NofOnsets < PWV_MIN_NOF_ONSETS)
  {
    MsgBox(TERROR, GetCurrentPwvMeasureDetails(), MSG_MATH_ERROR, MSG_PWV_TRIGGER_ERR);
    return false;
  }
  return true;
}

/* ###########################################################################
 ** Algorithm1()
 **
 ** DESCRIPTION
 **  Find onsets as percentage of Pulse Height for ECG signal
 ** INPUT
 **  Class properties(source)
 ** OUTPUT
 **  None
 ** RETURN
 **  boolean success or not
*/
//---------------------------------------------------------------------------
bool TPWVECGSignal::Algorithm1(const float pHeightPercent, const int pMinPulseLength,
                               const float pMinPulseHeight)
{
  // Initialise Onsets
	for(int i = 0; i < MaxNofOnsets; i++)
  {
    FloatOnsets[i] = -1;
  }
  NofOnsets = 0;
  // Validate
  if (pHeightPercent > 100. || pHeightPercent < 0)
  {
    MsgBox(TERROR, GetCurrentPwvMeasureDetails(), MSG_MATH_ERROR, MSG_PWV_TRIGGER_ERR);
    return false;
  }
  // Find Signal Min, Max
  float lGlobalMin, lGlobalMax, lMin, lMax;
//  if (math_MinMaxInArray (Signal, NofPoints, lMin, lMax)==false)
  int lIndMin = math_IndexOfExtremum(Signal, MIN, GLOBAL, 0, NofPoints-1);
  int lIndMax = math_IndexOfExtremum(Signal, MAX, GLOBAL, 0, NofPoints-1);
  if (lIndMin < 0 || lIndMax < 0)
  {
    return false;
  }
  // Get rid of largest and smallest
  lGlobalMin = Signal[lIndMin];
  lGlobalMax = Signal[lIndMax];
  if (lGlobalMax - pMinPulseHeight <= lGlobalMin)
  {
    return false;
  }
  lIndMin = math_IndexOfExtremum(Signal, MIN, GLOBAL, 0, NofPoints-1, MORE, lGlobalMin);
  lIndMax = math_IndexOfExtremum(Signal, MAX, GLOBAL, 0, NofPoints-1, LESS, lGlobalMax);
  if (lIndMax < 0 || lIndMin < 0)
  {
    lMin = lGlobalMin;
    lMax = lGlobalMax;
  }
  else
  {
    lMin = Signal[lIndMin];
    lMax = Signal[lIndMax];
    if (lMax - pMinPulseHeight <= lMin)
    {
      lMin = lGlobalMin;
      lMax = lGlobalMax;
    }
  }
  // ThresHold values
  float lThresHold = PULSE_HEIGHT_THRESHOLD * (lMax - lMin) + lMin;
  // Find the average pulse height
  float lAvPulseHeight = FindAvPulseHeight(lThresHold, pMinPulseHeight);
  if (lAvPulseHeight <= 0)
  {
    MsgBox(TERROR, GetCurrentPwvMeasureDetails(), MSG_MATH_ERROR, MSG_PWV_TRIGGER_ERR);
    return false;
  }
  // Setup percent of average pulse height
  float lPercentAvPulseHeight = pHeightPercent/100. * lAvPulseHeight;
  // Main loop
  bool  WeAreInPeak = false;
  bool Beginning = true;
  int   lPeakIndex = -1;
  int   lFootIndex;
  for (int i = 0; i < NofPoints; i++)
  {
    // Avoid signal beginning where values already above threashold
    if (Beginning == true)
    {
      if (Signal[i] >= lThresHold)
        continue;
      Beginning = false;
    }
    // Avoid MinPulseLength zone after last onset being found
    if (NofOnsets > 0 && (i - FloatOnsets[NofOnsets - 1] < pMinPulseLength))
      continue;

    // avoid beginning of a wave
    if ((WeAreInPeak == false) && (Signal[i] < lThresHold))
      continue;

    // Begin of peak
    if (WeAreInPeak==false) WeAreInPeak = true;

    if (Signal[i] > lThresHold)
    {
      // We are in Peak first point
      if (lPeakIndex < 0)
      {
        lPeakIndex = i;
        continue;
      }
      // Find max in peak
      if (Signal[i] > Signal[lPeakIndex])
      {
        lPeakIndex = i;
      }
    }
    else
    {
      WeAreInPeak = false;
      // End of Peak. Go back to find point where Signal has minimum;
      int lInitPeakIndex = ((NofOnsets > 0) ? FloatOnsets[NofOnsets-1] + 1: 0);
      lFootIndex = -1;
      // Find foot points found where Previous > Current
      for (int j = lPeakIndex; j > lInitPeakIndex; j--)
      {
        if (Signal[j] <= Signal[j-1])
        {
          lFootIndex = j;
          break;
        }
      }
      if (lFootIndex < 0 || lPeakIndex < 0)
      {
        lPeakIndex = -1;
        continue;
      }

      // After foot has been found
      float lPulseHeight = Signal[lPeakIndex] - Signal[lFootIndex];
      // float lPulseHeight = Signal[lPeakIndex] - lMin;
      // Reject short signal
      if (lPulseHeight < pMinPulseHeight || lPulseHeight < lPercentAvPulseHeight)
      {
        lPeakIndex = -1;
        continue;
      }
      float lOnset = -1;
      if (pHeightPercent == 0.) // If pHeightPercent == 0 then Onset = FootIndex
      {
        lOnset = lFootIndex;
      }
      else // Catch point where Signal cross threshold
      {
/*
        // Find more presisely float foot;
        float lFloatFootIndex, lFootValue;
        int lBeforeFootIndex = (lFootIndex > 0 ? lFootIndex - 1 : 0);
        FindFoot(lBeforeFootIndex, lPeakIndex, Signal[lFootIndex] + lPercentAvPulseHeight, lFloatFootIndex, lFootValue);
*/
        float lFootValue = Signal[lFootIndex];

        // ThresHold value for pHeightPercent of PulseHeight
        // float lThresHold2 = Signal[lFootIndex] + pHeightPercent/100. * lPulseHeight;
        float lThresHold2 = lFootValue + lPercentAvPulseHeight;
        // float lThresHold2 = lMin + lPercentAvPulseHeight;
        for (int j = lFootIndex; j <= lPeakIndex; j++)
        {
          if (Signal[j] < lThresHold2)
            continue;
          if (Signal[j] <= Signal[j-1]) // To prevent zero devide
            continue;
          // Interpolate Signal to catch Treashold value
          double N2 = (lThresHold2 - Signal[j-1])/(Signal[j] - Signal[j-1]);
          double N1 = 1. - N2;
          lOnset = N1*(j-1) + N2*j;
          break;
        }
      }
      // Validate
      if (lOnset > lInitPeakIndex)
      {
        FloatOnsets[NofOnsets] = lOnset;
        NofOnsets++;
      }
      WeAreInPeak = false;
      lPeakIndex = -1;
      // Check NofOnsets limit. If more, stop process
      if (NofOnsets == MaxNofOnsets) break;
    }
  } // End of Main loop

  // return
  if (NofOnsets < PWV_MIN_NOF_ONSETS)
  {
    MsgBox(TERROR, GetCurrentPwvMeasureDetails(), MSG_MATH_ERROR, MSG_PWV_TRIGGER_ERR);
    return false;
  }
  return true;
}

/* ###########################################################################
 ** Algorithm2()
 **
 ** DESCRIPTION
 **  Find onsets as index of peaks for ECG signal
 ** INPUT
 **  Class properties(source)
 ** OUTPUT
 **  None
 ** RETURN
 **  boolean success or not
*/
//---------------------------------------------------------------------------
bool TPWVECGSignal::Algorithm2(const int pMinPulseLength)
{
  // Initialise Onsets
  NofOnsets = 0;
	for(int i = 0; i < MaxNofOnsets; i++)
  {
    FloatOnsets[i] = -1;
  }
  // Find Signal Min, Max
  float lGlobalMin, lGlobalMax, lMin, lMax;
//  if (math_MinMaxInArray (Signal, NofPoints, lMin, lMax)==false)
  int lIndMin = math_IndexOfExtremum(Signal, MIN, GLOBAL, 0, NofPoints);
  int lIndMax = math_IndexOfExtremum(Signal, MAX, GLOBAL, 0, NofPoints);
  if (lIndMax < 0 || lIndMin < 0)
  {
    return false;
  }
  // Get rid of largest and smallest
  lGlobalMin = Signal[lIndMin];
  lGlobalMax = Signal[lIndMax];
  lIndMin = math_IndexOfExtremum(Signal, MIN, GLOBAL, 0, NofPoints, MORE, lGlobalMin);
  lIndMax = math_IndexOfExtremum(Signal, MAX, GLOBAL, 0, NofPoints, LESS, lGlobalMax);
  if (lIndMax < 0 || lIndMin < 0)
  {
    lMin = lGlobalMin;
    lMax = lGlobalMax;
    // return false;
  }
  else
  {
    lMin = Signal[lIndMin];
    lMax = Signal[lIndMax];
  }
  if (lMax <= lMin)
  {
    lMin = lGlobalMin;
    lMax = lGlobalMax;
    //return false;
  }
  // ThresHold values
  float lThresHold = PULSE_HEIGHT_THRESHOLD * (lMax - lMin) + lMin;
  // Main loop
  bool  WeAreInPeak = false;
  bool  Beginning = true;
  int   lPeakIndex = -1;
  for (int i = 0; i < NofPoints; i++)
  {
    // Avoid signal beginning where values already above threashold
    if (Beginning == true)
    {
      if (Signal[i] >= lThresHold)
        continue;
      Beginning = false;
    }
    // Avoid MinPulseLength zone after last onset being found
    if (NofOnsets > 0 && (i - FloatOnsets[NofOnsets - 1] < pMinPulseLength))
      continue;

    // avoid beginning of a wave
    if ((WeAreInPeak == false) && (Signal[i] < lThresHold))
      continue;

    // Begin of peak
    if (WeAreInPeak==false)
      WeAreInPeak = true;

    if (Signal[i] > lThresHold)
    {
      // We are in Peak first point
      if (lPeakIndex < 0)
      {
        lPeakIndex = i;
        continue;
      }
      // Find max in peak
      if (Signal[i] > Signal[lPeakIndex])
      {
        lPeakIndex = i;
      }
    }
    else
    {
      WeAreInPeak = false;
      if (lPeakIndex < 1)
        continue;
      float lPulsePeak;
      float lOnset = math_IndexOfQuadrInterpMax(lPeakIndex-1, lPeakIndex, lPeakIndex+1,
                   Signal[lPeakIndex-1], Signal[lPeakIndex], Signal[lPeakIndex+1], lPulsePeak);
      // Validate
      float lPrevios = (NofOnsets > 0 ? FloatOnsets[NofOnsets-1] : 0);
      if (lOnset >= lPeakIndex - 1 && lOnset > lPrevios)
      {
        FloatOnsets[NofOnsets] = lOnset;
        NofOnsets++;
      }
      lPeakIndex = -1;
      // Check NofOnsets limit. If more, stop process
      if (NofOnsets == MaxNofOnsets) break;
    }
  } // End of Main loop
  return true;
}

/* ###########################################################################
 ** FindFoot()
 **
 ** DESCRIPTION
 **  Find foot of ECG Signal as a peak of Der2
 ** INPUT
 **  i1 - index of signal local minimum
 **  i2 - index of signal peak
 ** OUTPUT
 **  none
 ** RETURN
 **  float peak of der2 between
*/
//-----------------------------------------------------------------------------------------
void TPWVECGSignal::FindFoot(const int i1, const int i2, const float lThreshold, float &pFoot, float &pValue)
{
  // Default values
  pFoot = i1+1; // +1 because i1 is a point before footindex
  pValue = Signal[i1+1];
  // Allocate memory for derivatives
  // Validation - NofPoints should be more than 3
  int l = i2-i1+1;
  if (l < 3 || l > PWV_ARRAY_SIZE_FOR_PEAKS)
  {
    return;
  }
  static float D1[PWV_ARRAY_SIZE_FOR_PEAKS];
  static float D2[PWV_ARRAY_SIZE_FOR_PEAKS];
  // Find derivatives
  float lMDer1, lMDer2;
  if (l > 6)
  {
    math_SmoothDerivative1(&Signal[i1], l,  3, 1., D1, lMDer1);
    math_SmoothDerivative1(D1, l,  3, 1., D2, lMDer2);
  }
  else
  {
    math_Deriv1(&Signal[i1], l,  1., D1, lMDer1);
    math_Deriv1(D1, l,  1., D2, lMDer2);
  }
  // Work out float index of max der 1
  float lIndMaxDer1 = 0.; //, lMaxDer1 = 0.;
  int lIntIndMaxDer1 = math_IndexOfExtremum(D1, MAX, FIRST, 1, l, MORE, 0.);
  if (lIntIndMaxDer1 > 0/* && Signal[i1 + lIntIndMaxDer1] < lThreshold*/)
  {
    lIndMaxDer1 = lIntIndMaxDer1;
  }
  // Validate peak of der1
  if (/*lMaxDer1 <= 0. || */lIndMaxDer1 <= 0.)
    return;
/*
  if (lIndMaxDer1 - i1 <= 1)
    return;
*/
  // Work out float index of max der 2
  float lIndMaxDer2 = 0.; // , lMaxDer2 = 0.;
  int lIntIndMaxDer2 = math_IndexOfExtremum(D2, MAX, FIRST, 0, min((int)lIndMaxDer1+1,l), MORE, 0.);
  if (lIntIndMaxDer2 > 0/* && Signal[i1 + lIntIndMaxDer2] < lThreshold*/)
  {
    float f1 = math_FunctionValue(D2, l, lIntIndMaxDer2-1);
    float f2 = math_FunctionValue(D2, l, lIntIndMaxDer2);
    float f3 = math_FunctionValue(D2, l, lIntIndMaxDer2+1);
    float fm;
    float lIndMax = math_IndexOfQuadrInterpMax(lIntIndMaxDer2-1, lIntIndMaxDer2, lIntIndMaxDer2+1,
                    f1, f2, f3, fm);
    if (lIndMax >= lIntIndMaxDer2-1)
    {
      if (math_FunctionValue(Signal, NofPoints, i1 + lIndMax) < lThreshold)
      {
        lIndMaxDer2 = i1 + lIndMax;
      }
    }
  }
/*
  int i3 = (int) (lIndMaxDer1 + 0.5); // Round to nearest higher
  if (i3 > i2)
    return;
  l = i3-i1+1;
  for (int i=i1+1; i<=i3-2; i++)
  {
    float f1 = math_FunctionValue(D2, l, i-i1);
    float f2 = math_FunctionValue(D2, l, i-i1+1);
    float f3 = math_FunctionValue(D2, l, i-i1+2);
    float fm;
    float lIndMax = i1 + math_IndexOfQuadrInterpMax(i-i1, i-i1+1, i-i1+2,
                    f1, f2, f3, fm);
    if (lIndMax >= i && fm > lMaxDer2)
    {
      if (math_FunctionValue(Signal, NofPoints, lIndMax) < lThreshold)
      {
        lMaxDer2 = fm;
        lIndMaxDer2 = lIndMax;
      }
      else
      {
        break;
      }
    }
  }
*/
  // Validate peak of der2
  if (/*lMaxDer2 <= 0. || */lIndMaxDer2 <= 0.)
    return;
  // Success
  pFoot = lIndMaxDer2;
  pValue = math_FunctionValue(Signal, NofPoints, pFoot);
  return;
}

/*
** Algorithm_QRS_Filter
**
** DESCRIPTION
**  Find onsets as index of peaks for ECG signal
** INPUT
**  Class properties(source)
** OUTPUT
**  None
** RETURN
**  boolean success or not
*/
bool TPWVECGSignal::Algorithm_QRS_Filter(void)
{
   int    weighting_parm;
   int    i, j, k;
   float  signal_peak;
   float  signal_threshold;
   float  *opened_signal;
   float  *closed_signal;
   float  *resulting_signal;
   float  *signal_segment;
   int    *index_threshold;
   int    nof_thresholds = 0;

   // Initialise Onsets
   NofOnsets = 0;
   for (i = 0; i < MaxNofOnsets; i++)
   {
      FloatOnsets[i] = -1;
   }

   // Minimal pulse length
   int max_sigseg = 60. * SampleRate / MIN_HR;

   opened_signal = new float[NofPoints + 1];
   closed_signal = new float[NofPoints + 1];
   resulting_signal = new float[NofPoints + 1];
   signal_segment = new float[max_sigseg];
   index_threshold = new int[MaxNofOnsets];

   if (opened_signal == NULL ||
       closed_signal == NULL ||
       resulting_signal == NULL ||
       signal_segment == NULL ||
       index_threshold == NULL)
   {
      log_write("Out of Memory...ECG Morphological Filter");
      return false;
   }

   weighting_parm = math_Round(5.5 * SampleRate / 100);
   weighting_parm = weighting_parm + 1;

   Openingn(weighting_parm, &Signal[0], &opened_signal[0]);
   Closingn(weighting_parm, &opened_signal[0], &closed_signal[0]);
   for (i = 0; i < NofPoints; i++)
   {
      resulting_signal[i] = Signal[i] - closed_signal[i];
   }
   signal_peak = math_MaxInArray(&resulting_signal[0], NofPoints - weighting_parm);

   signal_threshold = PWV_ECG_FILTER_THRESHOLD * signal_peak;


   for (i = 0; i < NofPoints - weighting_parm; i++)
   {
      if ((resulting_signal[i] < signal_threshold) &&
          (resulting_signal[i+1] >= signal_threshold))
      {
         if (nof_thresholds < MaxNofOnsets)
         {
            index_threshold[nof_thresholds] = i;
            nof_thresholds++;
         }
      }
   }
   i = 0;
   while (nof_thresholds && (NofOnsets < MaxNofOnsets) && (i < nof_thresholds - 1))
   {
      int ss = 0;
      for (j = index_threshold[i]; j <= index_threshold[i+1];j++)
      {
         if (ss < max_sigseg)
         {
           signal_segment[ss] = resulting_signal[j];
           ss++;
         }
         else
         {
            ;
         }
      }
      FloatOnsets[NofOnsets] = math_MaxInArrayIndex(&signal_segment[0], ss) + index_threshold[i];
      NofOnsets++;
      for (k = 0; k < ss; k++)
      {
         signal_segment[k] = 0;
      }
      ++i;
   }

   if (opened_signal != NULL)
   {
      delete[] opened_signal;
   }

   if (closed_signal != NULL)
   {
      delete[] closed_signal;
   }

   if (resulting_signal != NULL)
   {
      delete[] resulting_signal;
   }
   if (signal_segment != NULL)
   {
      delete[] signal_segment;
   }
   if (index_threshold != NULL)
   {
      delete[] index_threshold;
   }

   return true;
}

/*
**
** Erosion part of morpholigical filter
** INPUTS
** pSignal  Input signal (array of float number)
** pb       a parameter, which depends on the sampling frequency
**          calculated by the detection procedure.
** pSize    size of the pSignal (number of points)
**
** OUTPUTS
** pErosion  The output signal from the Erosion procedure
**
*/
bool TPWVECGSignal::Erosion(int pb , float *pSignal, float *pErosion)
{
   float *shifted_signal;
   float *min_at_weighting;
   int   ss = 0;
   int i, j;

   if (NofPoints <= (2 * pb))
   {
      return false;
   }

   shifted_signal = new float[pb * (NofPoints + 1)];
   min_at_weighting = new float[pb];

   if (shifted_signal == NULL || min_at_weighting == NULL)
   {
      log_write("Out of Memory...ECG Morphological Filter-Erosion");
      return false;
   }

   for (int i = 0; i < pb; i++)
   {
      min_at_weighting[i] = 0;
   }


   for (i = 0; i < NofPoints; i++)
   {
      shifted_signal[i] = pSignal[i];
   }
   for (i = 1; i < pb;i++)
   {
      ss = 0;
      for (j = (i * NofPoints); j<((i+1) * NofPoints); j++)
      {
         if (j < ((i+1) * NofPoints) -i)
         {
            shifted_signal[j] = pSignal[ss + i];
         }
         else
         {
            shifted_signal[j] = 0;
         }
         ss++;
      }
   }
   for (j = 0; j < NofPoints; j++)
   {
      for (i = 0; i < pb; i++)
      {
         min_at_weighting[i] = shifted_signal[(i*NofPoints) + j];
      }
      pErosion[j] = math_MinInArray(&min_at_weighting[0], pb);
      for (i = 0; i < pb; i++)
      {
         min_at_weighting[i] = 0;
      }
   }

   if (min_at_weighting != NULL)
   {
      delete[] min_at_weighting;
   }

   if (shifted_signal != NULL)
   {
      delete[] shifted_signal;
   }
   return true;
}

/*
**
** Dilation part of morpholigical filter
** INPUTS
** pSignal  Input signal (array of float number)
** pb       a parameter, which depends on the sampling frequency
**          calculated by the detection procedure.
** pSize    size of the pSignal (number of points)
**
** OUTPUTS
** pDilated  The output signal from the Dilation procedure
**
*/
bool TPWVECGSignal:: Dilation(int pb, float *pSignal, float *pDilated)
{
   int   i, j, k;
   float *shifted_signal;
   float *max_at_weighting;

   if (NofPoints <= (2*pb))
   {
      return false;
   }

   shifted_signal = new float[pb * (NofPoints + 1)];
   max_at_weighting = new float[pb];

   if (shifted_signal == NULL || max_at_weighting == NULL)
   {
      log_write("Out of Memory...ECG Morphological Filter-Dilation");
      return false;
   }

   for (i = 0; i < NofPoints; i++)
   {
      shifted_signal[i] = pSignal[i];
   }
   for (i = 1; i < pb;i++)
   {
      k = 0;
      for (j = (i * NofPoints); j < ((i+1)*NofPoints); j++)
      {
         if (j <= (i*(NofPoints + 1)))
         {
            shifted_signal[j] = 0;
         }
         else
         {
            shifted_signal[j]= pSignal[k];
            k++;
         }
      }
   }
   for (j = 0; j < NofPoints; j++)
   {
      for (i = 0; i < pb;i++)
      {
         max_at_weighting[i]= shifted_signal[(i*NofPoints) + j];
      }
      pDilated[j]= math_MaxInArray(&max_at_weighting[0], pb);
      for (i = 0; i < pb; i++)
      {
         max_at_weighting[i] = 0;
      }
   }

   if (max_at_weighting != NULL)
   {
      delete[] max_at_weighting;
   }

   if (shifted_signal != NULL)
   {
      delete[] shifted_signal;
   }
   return true;
}

/*
**
** Openingn procedure (part of morpholigical filter)
** It calls on the Erosion procedure then the Dialation procedure
**
** INPUTS
** pSignal  Input signal (array of float number)
** pb       a parameter, which depends on the sampling frequency
**          calculated by the detection procedure.
** pSize    size of the pSignal (number of points)
**
** OUTPUTS
** pOpened= The output signal from the Openingn procedure
*/
void TPWVECGSignal::Openingn(int pb, float *pSignal, float *pOpened)
{
   float *erosion_signal;

   erosion_signal = new float[NofPoints + 1];

   if (erosion_signal != NULL)
   {
      Erosion(pb, &pSignal[0], &erosion_signal[0]);
      Dilation(pb, &erosion_signal[0], &pOpened[0]);
      delete[] erosion_signal;
   }
}

/*
**
** Closingn procedure (part of morpholigical filter)
** It calls on the Dilation procedure then the Erosion procedure
**
** INPUTS
** pSignal Input signal (array of float number)
** pb     parameter, which depends on the sampling frequency
**        calculated by the detection procedure.
** pSize  size of the pSignal (number of points)
**
** OUTPUTS
** pClosed= The output signal from the Closingn procedure
**
*/
void TPWVECGSignal::Closingn(int pb, float *pOpened, float *pClosed)
{
   float *dilated_signal;

   dilated_signal = new float[NofPoints + 1];

   if (dilated_signal != NULL)
   {
      Dilation(pb, &pOpened[0], &dilated_signal[0]);
      Erosion(pb, &dilated_signal[0], &pClosed[0]);
      delete[] dilated_signal;
   }
}

/* ###########################################################################
 ** FindAvPulseHeight()
 **
 ** DESCRIPTION
 **  Find average pulse height for a signal
 ** INPUT
 **  pThreasHold - theashold to catch a maximum
 ** OUTPUT
 **  none
 ** RETURN
 **  average pulse height value
*/
//-----------------------------------------------------------------------------------------
float TPWVECGSignal::FindAvPulseHeight(const float pThresHold, const float pMinPulseHeight)
{
  float Heights[PWVSITE_MAX_ONSETS];
  // int LastHeightIndex = -1;
  int NofHeights = 0;
  float lAvPulseHeight;
  // Main loop
  bool  WeAreInPeak = false;
  bool  Beginning = true;
  int   lPeakIndex = -1;
  // int   lFootIndex = -1;
  float lSignalMin = math_MinInArray(Signal, NofPoints);
  for (int i = 0; i < NofPoints; i++)
  {
    // Avoid signal beginning where values already above threashold
    if (Beginning == true)
    {
      if (Signal[i] >= pThresHold)
        continue;
      Beginning = false;
    }
    // avoid beginning of a wave
    if ((WeAreInPeak == false) && (Signal[i] < pThresHold))
      continue;
    // Begin of peak
    if (WeAreInPeak==false)
      WeAreInPeak = true;
    if (Signal[i] > pThresHold)
    {
      // We are in Peak first point
      if (lPeakIndex < 0)
      {
        lPeakIndex = i;
        continue;
      }
      // Find max in peak
      if (Signal[i] > Signal[lPeakIndex])
      {
        lPeakIndex = i;
      }
    }
    else
    {
      WeAreInPeak = false;
      // End of Peak. Go back to find point where Signal has minimum;
      // int lInitPeakIndex = LastHeightIndex + 1;
/*
      lFootIndex = -1;
      // Find foot points found where Previous > Current
      for (int j = lPeakIndex; j > lInitPeakIndex; j--)
      {
        if (Signal[j] <= Signal[j-1])
        {
          lFootIndex = j;
          break;
        }
      }
*/
/*
      lFootIndex = math_IndexOfExtremum(Signal, MIN, FIRST, lPeakIndex, NofPoints-1, LESS, pThresHold);
      if (lFootIndex < 0)
      {
        lPeakIndex = -1;
        continue;
      }
*/
      if (lPeakIndex < 0)
      {
        lPeakIndex = i;
        continue;
      }
      // After foot has been found
      // float lPulseHeight = Signal[lPeakIndex] - Signal[lFootIndex];
      float lPulseHeight = Signal[lPeakIndex] - lSignalMin;
      // Reject short signal
      if (lPulseHeight < pMinPulseHeight)
      {
        lPeakIndex = -1;
        continue;
      }
      // Validate
      if (lPulseHeight > 0)
      {
        Heights[NofHeights] = lPulseHeight;
        NofHeights++;
        // LastHeightIndex = lPeakIndex;
      }
      WeAreInPeak = false;
      lPeakIndex = -1;
      // Check NofOnsets limit. If more, stop process
      if (NofHeights == MaxNofOnsets) break;
    }
  } // End of Main loop

  // Find the average of the Pulse Heights rejecting 20% of extra high and extra low
  lAvPulseHeight = 0.;
  float lHeightMin, lHeightMax;
  if (math_MinMaxInArray(Heights, NofHeights, lHeightMin, lHeightMax)==false)
  {
    return lAvPulseHeight;
  }
  if (lHeightMax < lHeightMin)
  {
    return lAvPulseHeight;
  }
  else if (lHeightMax == lHeightMin && lHeightMax > 0.)
  {
    lAvPulseHeight = lHeightMax;
    return lAvPulseHeight;
  }
  // 20% of variation
  float lVar20 = (lHeightMax - lHeightMin)*0.2;
  float lUpLimit = lHeightMax - lVar20;
  float lDownLimit = lHeightMin + lVar20;
  // Averaging
  int lNofAvHeights = 0;
  for (int i=0; i<NofHeights; i++)
  {
    if (Heights[i] >= lDownLimit && Heights[i] <= lUpLimit)
    {
      lAvPulseHeight += Heights[i];
      lNofAvHeights++;
    }
  }
  if (lNofAvHeights > 0)
    lAvPulseHeight /= lNofAvHeights;

  return lAvPulseHeight;
}

