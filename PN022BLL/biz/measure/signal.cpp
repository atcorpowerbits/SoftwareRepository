/*
    Copyright (C) ATCOR MEDICAL PTY LTD, 2010

    Filename	 :	signal.cpp
	
	Author       :  Paul McBryde

    Description  :	DECLARATION of Signal Class
*/
#include "stdafx.h"
#include "signal.h"

using namespace Biz;
using namespace System;
using namespace CrossCutting;
using namespace System::Diagnostics;

#pragma hdrstop

/**
	Constructor for Signal Class
*/
BizSignal::BizSignal()
{
	signalLength = 0;
	onsetsLength = 0;
	maxSignalLength = 0;
	maxOnsetsLength = 0;
	signal = nullptr;
	floatOnsets = nullptr;

	readyToCapture = false;

	pulseHeight = (float) DEFAULT_VALUE; 
	pulseHeightVariation = (float) DEFAULT_VALUE;
	pulseLengthVariation = (float) DEFAULT_VALUE;
	baseLineVariation = (float) DEFAULT_VALUE;
}

bool BizSignal::Allocate(const short inputMaxSignalLength, 
						 const short inputMaxOnsetsLength)
{
	if (inputMaxSignalLength < MIN_SIGNAL_LENGTH 
		|| inputMaxSignalLength > MAX_SIGNAL_LENGTH)
	{
		return false;
	}
	if (inputMaxOnsetsLength < MIN_ONSETS 
		|| inputMaxOnsetsLength > MAX_ONSETS)
	{
		return false;
	}

	maxSignalLength = inputMaxSignalLength;
	maxOnsetsLength = inputMaxOnsetsLength;

	// Allocate
	signal = gcnew array<float>(maxSignalLength);
	floatOnsets = gcnew array<float>(maxOnsetsLength);

	// Allocate Derivatives
	derivative1 = gcnew array<float>(maxSignalLength);
	derivative2 = gcnew array<float>(maxSignalLength);
	
	// Initialise cannot return false
	Initialise(0);

	return true;
}

/**
	Class initialisator
*/
bool BizSignal::Initialise(const short inputSampleRate)
{
	if (inputSampleRate < 0 
		|| inputSampleRate >= DEFAULT_VALUE)
	{
		return false;
	}
	
	signalLength = 0;
	sampleRate = inputSampleRate;

	// Signal initialisation
	for (int i = 0; i < maxSignalLength; i++)
	{
		signal[i] = 0;
	}

	// Onsets initialisation
	SetDefaults();

	return true;
}
/**
	Set default values for onsets not touching Signal
*/
void BizSignal::SetDefaults()
{
	// Initialisation
	readyToCapture = false;

	pulseHeight = (float) DEFAULT_VALUE;
	pulseHeightVariation = (float) DEFAULT_VALUE;
	pulseLengthVariation = (float) DEFAULT_VALUE;
	baseLineVariation = (float) DEFAULT_VALUE;

	// Onsets initialisation
	onsetsLength = 0;
	for (int i = 0; i < maxOnsetsLength; i++)
	{
		floatOnsets[i] = -1;
	}
}

/**
 ** ValidateBeforeStore()
 **
 ** DESCRIPTION
 **  Validate class properties before storing in database

 ** INPUT
 **	 minSignalLength - minimum signal length
 **	 minSignalHeight - minimum signal amplitude
 **  minOnsetsLength - minimum number of onsets

 ** OUTPUT
 **  none

 ** RETURN
 **  boolean success or not
*/
bool BizSignal::ValidateBeforeStore(const short minSignalLength, 
									const short minOnsetsLength, 
									const short minSignalHeight)
{
	// Validate input
	if (minOnsetsLength < MIN_ONSETS 
		|| minOnsetsLength > MAX_ONSETS)
	{
		return false;
	}
	
	// Validate signal
	if (!ValidateSignalLength(minSignalLength))
	{
		return false;
	}
	if (!ValidateSignalHeight(minSignalHeight))
	{
		return false;
	}

	// Validate onsets
	bool success = true;
	if (onsetsLength < minOnsetsLength)
	{
		CrxMessageFacade::Instance()->Message(TraceEventType::Error,
			CrxMessageFacade::Instance()->messageResources->GetString(L"VALIDATION_ERROR"), 
			/*GetCurrentMeasureDetails()\n\n +*/
			CrxMessageFacade::Instance()->messageResources->GetString(L"SIGNAL_NOT_ENOUGH_ONSETS") 
			+ Convert::ToString(onsetsLength) + ", " + Convert::ToString(minOnsetsLength), 
			"");
		success = false;
	}
	if (onsetsLength > maxOnsetsLength)
	{
		CrxMessageFacade::Instance()->Message(TraceEventType::Error,
			CrxMessageFacade::Instance()->messageResources->GetString(L"VALIDATION_ERROR"), 
			/*GetCurrentMeasureDetails()\n\n +*/
			CrxMessageFacade::Instance()->messageResources->GetString(L"SIGNAL_TOO_MANY_ONSETS") 
			+ Convert::ToString(onsetsLength) + ", " + Convert::ToString(maxOnsetsLength), 
			"");
		onsetsLength = maxOnsetsLength;
	}
	return success;
}

/**
 ** PrepareToCapture()
 **
 ** DESCRIPTION
 **  Allow signal capture

 ** INPUT
 **  none

 ** OUTPUT
 **	 readyToCapture - true

 ** RETURN
 **  none
*/
void BizSignal::PrepareToCapture()
{
	readyToCapture = true;
}
/**
 ** CaptureSignal()
 **
 ** DESCRIPTION
 **  Store whole signal in Signal array

 ** INPUT
 **  short int * input  - integer signal
 **  int size

 ** OUTPUT
 **	 none

 ** RETURN
 **  boolean success or not
*/
bool BizSignal::CaptureSignal(array<const short>^ input, 
							  const short size)
{
	// Validation
	if (!Biz::BizMath::ValidateArray(input, size))
	{
		return false;
	}
	if (!readyToCapture)
	{
		return false;
	}

	// Store the input signal
	signalLength = Math::Min(size, maxSignalLength);
	for (int i = 0; i < signalLength; i++)
	{
		signal[i] = input[i];
	}
	return signalLength > 1;
}

/**
 ** ValidateSignalLength()
 **
 ** DESCRIPTION
 **  Validate Signal length

 ** INPUT
 **  minSignalLength - minimum signal length

 ** OUTPUT
 **   None

 ** RETURN
 **  boolean appropriate signal or not
*/
bool BizSignal::ValidateSignalLength(const short minSignalLength)
{
	// Validate input
	if (minSignalLength < MIN_SIGNAL_LENGTH 
		|| minSignalLength > MAX_SIGNAL_LENGTH)
	{
		return false;
	}
	bool success = true;

	// Validate signal
	if (signalLength < minSignalLength)
	{
		CrxMessageFacade::Instance()->Message(TraceEventType::Error,
			CrxMessageFacade::Instance()->messageResources->GetString(L"VALIDATION_ERROR"), 
			/*GetCurrentMeasureDetails() +*/
			CrxMessageFacade::Instance()->messageResources->GetString(L"SIGNAL_TOO_SHORT") 
			+ Convert::ToString(signalLength) + ", " + Convert::ToString(minSignalLength), 
			"");
		success = false;
	}
	if (signalLength > maxSignalLength)
	{
		CrxMessageFacade::Instance()->Message(TraceEventType::Error,
			CrxMessageFacade::Instance()->messageResources->GetString(L"VALIDATION_ERROR"), 
			/*GetCurrentMeasureDetails() +*/
			CrxMessageFacade::Instance()->messageResources->GetString(L"SIGNAL_TOO_LONG") 
			+ Convert::ToString(signalLength) + ", " + Convert::ToString(maxSignalLength), 
			"");
		signalLength = maxSignalLength;
	}
	
	// Validate sample rate
	if (sampleRate <= 0 || sampleRate >= DEFAULT_VALUE)
	{
		CrxMessageFacade::Instance()->Message(TraceEventType::Error,
			CrxMessageFacade::Instance()->messageResources->GetString(L"VALIDATION_ERROR"), 
			/*GetCurrentMeasureDetails() +*/
			CrxMessageFacade::Instance()->messageResources->GetString(L"INVALID_SAMPLE_RATE")
			+ Convert::ToString(sampleRate), "");
		success = false;
	}
	
	return success;
}

/**
 ** ValidateSignalHeight()
 **
 ** DESCRIPTION
 **  Validate Signal amplitude

 ** INPUT
 **  minSignalHeight - minimal signal amplitude

 ** OUTPUT
 **   None

 ** RETURN
 **  boolean appropriate signal or not
*/
bool BizSignal::ValidateSignalHeight(const short minSignalHeight)
{
	// Validate input
	if (minSignalHeight < TONOMETER_MIN_SIGNAL_HEIGHT 
		&& minSignalHeight < CUFF_MIN_SIGNAL_HEIGHT)
	{
		return false;
	}
	if (minSignalHeight >= DEFAULT_VALUE)
	{
		return false;
	}
	bool success = true;
	
	// Validate signal height
	float signalMinimum, signalMaximum;

	// MinMaxInArray cannot return false because only valid signals can be
	// available in this class - see CaptureSignal
	BizMath::MinMaxInArray(signal, signalLength, signalMinimum, signalMaximum);
	float signalHeight = signalMaximum - signalMinimum;
	if (signalHeight < minSignalHeight)
	{
		CrxMessageFacade::Instance()->Message(TraceEventType::Error,
			CrxMessageFacade::Instance()->messageResources->GetString(L"VALIDATION_ERROR"), 
			/*GetCurrentMeasureDetails() +*/
			CrxMessageFacade::Instance()->messageResources->GetString(L"SIGNAL_TOO_SMALL")
			+ Convert::ToString(signalHeight) + ", " + Convert::ToString(minSignalHeight), 
			"");
		success = false;
	}

	return success;
}

/* ###########################################################################
 ** QualityControl()
 **
 ** DESCRIPTION
 **  Calculate Quality Control parameters for a Signal
 ** INPUT
 **  TSignal class properties
 ** OUTPUT
 **  Quality Controls properties
 ** RETURN
 **  boolean success or not
*/
//---------------------------------------------------------------------------
bool BizSignal::CalculateQualityControls()
{
  /* Initialisation
  QC_PulseHeightVariation = DEFAULT_VALUE;
  QC_PulseLengthVariation = DEFAULT_VALUE;
  QC_PulseHeight = DEFAULT_VALUE;
  QC_BaseLineVariation = DEFAULT_VALUE;

  if (NofOnsets <= 1)
  {
     return false;
  }

  // Average of all pulse Heights, Lengths, BaseLines
  float lAvPH = 0.;
  float lAvPulseLength = 0.;
  float lAvBase = 0.;
  for (int np = 0; np < NofOnsets-1; np++)
  {
    float on1 = fabs(FloatOnsets[np]);
    float on2 = fabs(FloatOnsets[np+1]);
    // Calculate pulse height
    float lMin, lMax;
    math_MinMaxInArray(&Signal[(int)on1], (int)on2 - (int)on1, lMin, lMax);
    float lHeight = lMax - lMin;
    lAvPH += lHeight;
    float lPulseLength = on2 - on1;
    lAvPulseLength += lPulseLength;
    float lBase = math_FunctionValue(Signal, NofPoints, on1);
    lAvBase += lBase;
  }
  lAvPH /= (NofOnsets - 1);
  lAvPulseLength /= (NofOnsets - 1);
  lAvBase /= (NofOnsets - 1);

  QC_PulseHeight = (lAvPH > 0 ? lAvPH : DEFAULT_VALUE);
  if (QC_PulseHeight == DEFAULT_VALUE)
    return false;

  // Variations
  float lPHV = 0.;
  float lPLV = 0.;
  float lBLV = 0.;
  for (int np = 0; np < NofOnsets-1; np++)
  {
    float on1 = fabs(FloatOnsets[np]);
    float on2 = fabs(FloatOnsets[np+1]);
    // Calculate pulse height
    float lMin, lMax;
    math_MinMaxInArray(&Signal[(int)on1], (int)on2 - (int)on1, lMin, lMax);
    float lHeight = lMax - lMin;
    lPHV += fabs(lHeight - lAvPH);
    float lPulseLength = on2 - on1;
    lPLV += fabs(lPulseLength - lAvPulseLength);
    float lBase = math_FunctionValue(Signal, NofPoints, on1);
    lBLV += pow(lBase - lAvBase, 2);
  }
  lPHV /= (NofOnsets - 1);
  QC_PulseHeightVariation = (lPHV >= 0 ? lPHV/lAvPH * 100 : DEFAULT_VALUE);
  lPLV /= (NofOnsets - 1);
  QC_PulseLengthVariation = (lPLV >= 0 ? lPLV/lAvPulseLength * 100 : DEFAULT_VALUE);
  lBLV = sqrt(lBLV/(NofOnsets - 1));
  lBLV = (lBLV / QC_PulseHeight) * 100;
  QC_BaseLineVariation = lBLV;
  return true;*/
	return true;
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
bool BizSignal::ValidateSignal(const int pMinNofPoints)
{
  /* Validate length
  if (ValidateSignalLength(pMinNofPoints)==false)
  {
    return false;
  }
  // Validate Height
  if (ValidateSignalHeight(PWV_TON_MIN_PULSEHEIGHT)==false)
  {
    return false;
  }*/
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
bool BizSignal::FindOnsets(const int algorithm)
{
  /*bool ret = false;
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
  }*/
  return true;
}

/**
 ** TangentAlgorithm()
 **
 ** DESCRIPTION
 **  Find onsets using tangent algorithm - crossing of
 **  pulse foot line by tangent at point of max dP/dt

 ** INPUT
 ** 
 ** OUTPUT
 **  Class properties(source)
 ** RETURN
 **  boolean success or not
*/
//---------------------------------------------------------------------------
bool BizSignal::TangentAlgorithm(const float pMaxDer1,
                                 const int pMinPulseLength)
{
  /* ThresHold values
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
  return (NofOnsets >= PWV_MIN_NOF_ONSETS);*/
	return true;
}
