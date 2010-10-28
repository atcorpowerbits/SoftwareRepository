/*
    Copyright (C) ATCOR MEDICAL PTY LTD, 2010

    Filename	 :	signal.cpp
	
	Author       :  Paul McBryde

    Description  :	DECLARATION of Signal Class
*/
#include "stdafx.h"
#include "signal.h"
#include <math.h>

using namespace System;
using namespace System::Diagnostics;
using namespace System::Globalization;
using namespace BIZ_NAMESPACE;
using namespace CRX_MSG_NAMESPACE;

#pragma hdrstop

/**
 ** Constructor()
 **
 ** DESCRIPTION:
 **  Constructor for signal class.

 ** INPUT:
 **	 none.

 ** OUTPUT:
 **  none.

 ** RETURN:
 **  none.
*/
BizSignal::BizSignal()
{
	signalLength = 0;
	onsetsLength = 0;
	maximumSignalLength = 0;
	maximumOnsetsLength = 0;
	signal = nullptr;
	floatOnsets = nullptr;
	firstDerivative = nullptr;

	_readyToCapture = false;

	pulseHeight = (float) DEFAULT_VALUE; 
	pulseHeightVariation = (float) DEFAULT_VALUE;
	pulseLengthVariation = (float) DEFAULT_VALUE;
	pulseBaselineVariation = (float) DEFAULT_VALUE;
}

/**
 ** Allocate()
 **
 ** DESCRIPTION:
 **  Allocate memory for array memebers.

 ** INPUT:
 **	 inputMaximumSignalLength	- Maximum signal length,
 **	 inputMaximumOnsetsLength	- Maximum number of onsets.

 ** OUTPUT:
 **  maximumSignalLength		- Maximum signal length,
 **  maximumOnsetsLength		- Maximum number of onsets.

 ** RETURN:
 **  boolean success or not.
*/
bool BizSignal::Allocate(const unsigned short inputMaximumSignalLength, 
						 const unsigned short inputMaximumOnsetsLength)
{
	if (inputMaximumSignalLength < MIN_SIGNAL_LENGTH 
		|| inputMaximumSignalLength > MAX_SIGNAL_LENGTH)
	{
		return false;
	}
	if (inputMaximumOnsetsLength < MIN_ONSETS 
		|| inputMaximumOnsetsLength > MAX_ONSETS)
	{
		return false;
	}

	maximumSignalLength = inputMaximumSignalLength;
	maximumOnsetsLength = inputMaximumOnsetsLength;

	// Allocate
	signal = gcnew array<unsigned short>(maximumSignalLength);
	floatOnsets = gcnew array<float>(maximumOnsetsLength);

	// Allocate Derivatives
	firstDerivative = gcnew array<float>(maximumSignalLength);
	
	// Initialise cannot return false
	Initialise(0);

	return true;
}

/**
 ** Initialise()
 **
 ** DESCRIPTION:
 **  Initialse the signal array and sample rate.

 ** INPUT:
 **	 inputSampleRate				- Signal sample rate,
 **  BizSignal::maximumSignalLength - Maximum accounted points in signal.

 ** OUTPUT:
 **  sampleRate.

 ** RETURN:
 **  boolean success or not.
*/
bool BizSignal::Initialise(const unsigned short inputSampleRate)
{
	if (inputSampleRate >= DEFAULT_VALUE)
	{
		return false;
	}
	
	signalLength = 0;
	sampleRate = inputSampleRate;

	// Signal initialisation
	for (unsigned short i = 0; i < maximumSignalLength; i++)
	{
		signal[i] = 0;
	}

	// Onsets initialisation
	SetDefaults();

	return true;
}
/**
 ** SetDefaults()
 **
 ** DESCRIPTION:
 **  Initialse the onsets array and quality control members.

 ** INPUT:
 **  BizSignal::maximumOnsetsLength - Maximum number of onsets.

 ** OUTPUT:
 **  none.

 ** RETURN:
 **  none.
*/
void BizSignal::SetDefaults()
{
	// Initialisation
	_readyToCapture = false;

	pulseHeight = (float) DEFAULT_VALUE;
	pulseHeightVariation = (float) DEFAULT_VALUE;
	pulseLengthVariation = (float) DEFAULT_VALUE;
	pulseBaselineVariation = (float) DEFAULT_VALUE;

	// Onsets initialisation
	onsetsLength = 0;
	for (int i = 0; i < maximumOnsetsLength; i++)
	{
		floatOnsets[i] = DEFAULT_FLOAT_VALUE;
	}
}

/**
 ** ValidateBeforeStore()
 **
 ** DESCRIPTION:
 **  Validate class properties before storing in database.

 ** INPUT:
 **	 minimumSignalLength			- Minimum signal length,
 **	 minimumSignalHeight			- Minimum signal amplitude,
 **  minimumOnsetsLength			- Minimum number of onsets,
 **  BizSignal::signal				- Signal array,
 **  BizSignal::signalLength		- Number of accounted points in signal,
 **  BizSignal::sampleRate			- Signal Sample rate,
 **  BizSignal::onsetsLength		- Number of onsets,
 **  BizSignal::maximumSignalLength - Maximum accounted points in signal,
 **  BizSignal::maximumOnsetsLength - Maximum number of onsets.

 ** OUTPUT:
 **  onsetsLength (if greater than maximumOnsetsLength).

 ** RETURN:
 **  boolean success or not.
*/
bool BizSignal::ValidateBeforeStore(const unsigned short minimumSignalLength, 
									const unsigned short minimumOnsetsLength, 
									const unsigned short minimumSignalHeight)
{
	// Validate input
	if (minimumOnsetsLength < MIN_ONSETS 
		|| minimumOnsetsLength > MAX_ONSETS)
	{
		return false;
	}
	
	// Validate signal and inputs
	if (!ValidateSignalLength(minimumSignalLength))
	{
		return false;
	}
	if (!ValidateSignalHeight(minimumSignalHeight))
	{
		return false;
	}

	// Validate onsets
	bool success = true;
	if (onsetsLength < minimumOnsetsLength)
	{
#if 0 // TBD: Use a suitable CRX API
		CrxMessageFacade::Instance()->Message(TraceEventType::Error,
			CrxMessageFacade::Instance()->messageResources->GetString(L"VALIDATION_ERROR", CultureInfo::CurrentUICulture), 
			/*GetCurrentMeasureDetails()\n\n +*/
			CrxMessageFacade::Instance()->messageResources->GetString(L"SIGNAL_NOT_ENOUGH_ONSETS", CultureInfo::CurrentUICulture) 
			+ Convert::ToString(onsetsLength, CultureInfo::CurrentUICulture) 
			+ ", " + Convert::ToString(minimumOnsetsLength, CultureInfo::CurrentUICulture), 
			/*GetCurrentMeasureDetails()\n\n +*/
			CrxMessageFacade::Instance()->messageResources->GetString(L"SIGNAL_NOT_ENOUGH_ONSETS", CultureInfo::InvariantCulture) 
			+ Convert::ToString(onsetsLength, CultureInfo::InvariantCulture) 
			+ ", " + Convert::ToString(minimumOnsetsLength, CultureInfo::InvariantCulture));
#endif
		success = false;
	}
	if (onsetsLength > maximumOnsetsLength)
	{
#if 0 // TBD: Use a suitable CRX API
		CrxMessageFacade::Instance()->Message(TraceEventType::Error,
			CrxMessageFacade::Instance()->messageResources->GetString(L"VALIDATION_ERROR", CultureInfo::CurrentUICulture), 
			/*GetCurrentMeasureDetails()\n\n +*/
			CrxMessageFacade::Instance()->messageResources->GetString(L"SIGNAL_TOO_MANY_ONSETS", CultureInfo::CurrentUICulture) 
			+ Convert::ToString(onsetsLength, CultureInfo::CurrentUICulture) 
			+ ", " + Convert::ToString(maximumOnsetsLength, CultureInfo::CurrentUICulture), 
			/*GetCurrentMeasureDetails()\n\n +*/
			CrxMessageFacade::Instance()->messageResources->GetString(L"SIGNAL_TOO_MANY_ONSETS", CultureInfo::InvariantCulture) 
			+ Convert::ToString(onsetsLength, CultureInfo::InvariantCulture) 
			+ ", " + Convert::ToString(maximumOnsetsLength, CultureInfo::InvariantCulture));
#endif
		onsetsLength = maximumOnsetsLength;
	}
	return success;
}

/**
 ** PrepareToCapture()
 **
 ** DESCRIPTION:
 **  Allow signal capture.

 ** INPUT:
 **  none.

 ** OUTPUT:
 **	 _readyToCapture - true.

 ** RETURN:
 **  none.
*/
void BizSignal::PrepareToCapture()
{
	_readyToCapture = true;
}
/**
 ** CaptureSignal()
 **
 ** DESCRIPTION:
 **  Store whole signal in Signal array.

 ** INPUT:
 **  input							- integer signal,
 **  size							- length of input,
 **  BizSignal::maximumSignalLength - Maximum accounted points in signal,
 **  BizSignal::_readyToCapture.

 ** OUTPUT:
 **	 signalLength					- Number of accounted points in signal,
 **  signal							- Signal array.

 ** RETURN:
 **  boolean success or not.
*/
bool BizSignal::CaptureSignal(array<const unsigned short>^ input, 
							  const unsigned short size)
{
	// Validation
	if (!BizMath::ValidateArray(input, size))
	{
		return false;
	}
	if (!_readyToCapture)
	{
		return false;
	}

	// Store the input signal
	signalLength = Math::Min(size, maximumSignalLength);
	for (int i = 0; i < signalLength; i++)
	{
		signal[i] = input[i];
	}
	return signalLength > 1;
}

/**
 ** ValidateSignalLength()
 **
 ** DESCRIPTION:
 **  Validate Signal length.

 ** INPUT:
 **  minimumSignalLength			- Minimum signal length,
 **  BizSignal::signalLength		- Number of accounted points in signal,
 **  BizSignal::sampleRate			- Signal Sample rate,
 **  BizSignal::maximumSignalLength - Maximum accounted points in signal.

 ** OUTPUT:
 **   signalLength (if greater than maximumSignalLength).

 ** RETURN:
 **  boolean appropriate signal or not.
*/
bool BizSignal::ValidateSignalLength(const unsigned short minimumSignalLength)
{
	// Validate input
	if (minimumSignalLength < MIN_SIGNAL_LENGTH 
		|| minimumSignalLength > MAX_SIGNAL_LENGTH)
	{
		return false;
	}
	bool success = true;

	// Validate signal
	if (signalLength < minimumSignalLength)
	{
#if 0 // TBD: Use a suitable CRX API
		CrxMessageFacade::Instance()->Message(TraceEventType::Error,
			CrxMessageFacade::Instance()->messageResources->GetString(L"VALIDATION_ERROR", CultureInfo::CurrentUICulture), 
			/*GetCurrentMeasureDetails() +*/
			CrxMessageFacade::Instance()->messageResources->GetString(L"SIGNAL_TOO_SHORT", CultureInfo::CurrentUICulture) 
			+ Convert::ToString(signalLength, CultureInfo::CurrentUICulture) 
			+ ", " + Convert::ToString(minimumSignalLength, CultureInfo::CurrentUICulture), 
			/*GetCurrentMeasureDetails() +*/
			CrxMessageFacade::Instance()->messageResources->GetString(L"SIGNAL_TOO_SHORT", CultureInfo::InvariantCulture) 
			+ Convert::ToString(signalLength, CultureInfo::InvariantCulture) 
			+ ", " + Convert::ToString(minimumSignalLength, CultureInfo::InvariantCulture));
#endif
		success = false;
	}
	if (signalLength > maximumSignalLength)
	{
#if 0 // TBD: Use a suitable CRX API
		CrxMessageFacade::Instance()->Message(TraceEventType::Error,
			CrxMessageFacade::Instance()->messageResources->GetString(L"VALIDATION_ERROR", CultureInfo::CurrentUICulture), 
			/*GetCurrentMeasureDetails() +*/
			CrxMessageFacade::Instance()->messageResources->GetString(L"SIGNAL_TOO_LONG", CultureInfo::CurrentUICulture) 
			+ Convert::ToString(signalLength, CultureInfo::CurrentUICulture) 
			+ ", " + Convert::ToString(maximumSignalLength, CultureInfo::CurrentUICulture), 
			/*GetCurrentMeasureDetails() +*/
			CrxMessageFacade::Instance()->messageResources->GetString(L"SIGNAL_TOO_LONG", CultureInfo::InvariantCulture) 
			+ Convert::ToString(signalLength, CultureInfo::InvariantCulture) 
			+ ", " + Convert::ToString(maximumSignalLength, CultureInfo::InvariantCulture));
#endif
		signalLength = maximumSignalLength;
	}
	
	// Validate sample rate
	if (sampleRate <= 0 || sampleRate >= DEFAULT_VALUE)
	{
#if 0 // TBD: Use a suitable CRX API
		CrxMessageFacade::Instance()->Message(TraceEventType::Error,
			CrxMessageFacade::Instance()->messageResources->GetString(L"VALIDATION_ERROR", CultureInfo::CurrentUICulture), 
			/*GetCurrentMeasureDetails() +*/
			CrxMessageFacade::Instance()->messageResources->GetString(L"SIGNAL_INVALID_SAMPLE_RATE", CultureInfo::CurrentUICulture)
			+ Convert::ToString(sampleRate, CultureInfo::CurrentUICulture), 
			/*GetCurrentMeasureDetails() +*/
			CrxMessageFacade::Instance()->messageResources->GetString(L"SIGNAL_INVALID_SAMPLE_RATE", CultureInfo::InvariantCulture)
			+ Convert::ToString(sampleRate, CultureInfo::InvariantCulture));
#endif
		success = false;
	}
	
	return success;
}

/**
 ** ValidateSignalHeight()
 **
 ** DESCRIPTION:
 **  Validate Signal amplitude.

 ** INPUT:
 **  minimumSignalHeight		- Minimum signal amplitude,
 **  BizSignal::signalLength	- Number of accounted points in signal,
 **  BizSignal::signal			- Signal array.

 ** OUTPUT:
 **   None.

 ** RETURN:
 **  boolean appropriate signal or not.
*/
bool BizSignal::ValidateSignalHeight(const unsigned short minimumSignalHeight)
{
	// Validate input
	if (minimumSignalHeight < TONOMETER_MIN_SIGNAL_HEIGHT 
		&& minimumSignalHeight < CUFF_MIN_SIGNAL_HEIGHT)
	{
		return false;
	}
	if (minimumSignalHeight >= DEFAULT_VALUE)
	{
		return false;
	}
	bool success = true;
	
	// Validate signal height
	unsigned short signalMinimum, signalMaximum;

	// MinimumMaximumInArray cannot return false because only valid signals can be
	// available in this class - see CaptureSignal
	BizMath::MinimumMaximumInArray(signal, signalLength, signalMinimum, signalMaximum);
	unsigned short signalHeight = signalMaximum - signalMinimum;
	if (signalHeight < minimumSignalHeight)
	{
#if 0 // TBD: Use a suitable CRX API
		CrxMessageFacade::Instance()->Message(TraceEventType::Error,
			CrxMessageFacade::Instance()->messageResources->GetString(L"VALIDATION_ERROR", CultureInfo::CurrentUICulture), 
			/*GetCurrentMeasureDetails() +*/
			CrxMessageFacade::Instance()->messageResources->GetString(L"SIGNAL_TOO_SMALL", CultureInfo::CurrentUICulture)
			+ Convert::ToString(signalHeight, CultureInfo::CurrentUICulture) 
			+ ", " + Convert::ToString(minimumSignalHeight, CultureInfo::CurrentUICulture), 
			/*GetCurrentMeasureDetails() +*/
			CrxMessageFacade::Instance()->messageResources->GetString(L"SIGNAL_TOO_SMALL", CultureInfo::InvariantCulture)
			+ Convert::ToString(signalHeight, CultureInfo::InvariantCulture) 
			+ ", " + Convert::ToString(minimumSignalHeight, CultureInfo::InvariantCulture));
#endif
		success = false;
	}

	return success;
}

/**
 ** CalculateQualityControls()
 **
 ** DESCRIPTION:
 **  Calculate Quality Control parameters for a Signal.

 ** INPUT:
 **  BizSignal::signalLength	- Number of accounted points in signal,
 **  BizSignal::onsetsLength	- Actual number of onsets,
 **  BizSignal::signal			- Signal array,
 **  BizSignal::floatOnsets		- Index of onsets in the signal.

 ** OUTPUT:
 **  pulseHeight				- Quality Control - pulse height,
 **  pulseHeightVariation		- Quality Control - pulse height variation,
 **  pulseLengthVariation		- Quality Control - pulse length variation,
 **  pulseBaselineVariation		- Quality Control - baseline variation.

 ** RETURN:
 **  boolean success or not.
*/
bool BizSignal::CalculateQualityControls()
{
	// Prevent the Garbage Collector from deleting array's and -
	// output parameters
	pin_ptr<unsigned short> corSignal = &signal[0];
	pin_ptr<float> corFloatOnsets = &floatOnsets[0];
	pin_ptr<float> corPulseHeight = &(float%)pulseHeight;
	pin_ptr<float> corPulseHeightVariation = &(float%)pulseHeightVariation;
	pin_ptr<float> corPulseLengthVariation = &(float%)pulseLengthVariation;
	pin_ptr<float> corPulseBaselineVariation = &(float%)pulseBaselineVariation;
	
	bool success = BizCorCalculateQualityControls(signalLength,
											onsetsLength, 
											corSignal, 
											corFloatOnsets,
											corPulseHeight,
											corPulseHeightVariation,
											corPulseLengthVariation,
											corPulseBaselineVariation);

	// References to the class members themselves cannot be passed -
	// to a native function, so we assign them now
	pulseHeight = *corPulseHeight;
	pulseHeightVariation = *corPulseHeightVariation;
	pulseLengthVariation = *corPulseLengthVariation;
	pulseBaselineVariation = *corPulseBaselineVariation;

	return success;
	
	/*float minimum; 
	float maximum;
	float baseline;
	float height;
	float pulseLength;
	float currentOnset;
	float nextOnset;	
	short index;
	
	// Initialisation
	pulseHeight = DEFAULT_VALUE;
	pulseHeightVariation = DEFAULT_VALUE;
	pulseLengthVariation = DEFAULT_VALUE;
	pulseBaselineVariation = DEFAULT_VALUE;

	array<const float>^ subset = gcnew array<const float>((short) signalLength);

	// Additional Validation, onsetsLength should never be less than 2
	if (onsetsLength <= 1)
	{
		return false;
	}

	// Sum the Heights, Lengths and Baselines of each pulse
	float averagePulseHeight = 0;
	float averagePulseLength = 0;
	float averageBaseline = 0;
	for (index = 0; index < onsetsLength - 1; index++)
	{
		currentOnset = Math::Abs(floatOnsets[index]);
		nextOnset = Math::Abs(floatOnsets[index + 1]);

		pulseLength = nextOnset - currentOnset;
		averagePulseLength += pulseLength;

		BizMath::FunctionValue(signal, signalLength, currentOnset, baseline);
		averageBaseline += baseline;

		Array::Copy(signal, (short) currentOnset, subset, 0, (short) pulseLength);
		BizMath::MinimumMaximumInArray(subset, (short) pulseLength, minimum, maximum);
		height = maximum - minimum;
		averagePulseHeight += height;
	}
	
	// Average the Heights, Lengths and Baselines of each pulse
	averagePulseHeight /= (onsetsLength - 1);
	averagePulseLength /= (onsetsLength - 1);
	averageBaseline /= (onsetsLength - 1);

	// Average Pulse Height
	if (averagePulseHeight > 0)
	{
		pulseHeight = averagePulseHeight;
	}
	else
	{
		return false;
	}
	
	// Sum the variations in Height, Length and Baseline of -
	// each pulse from the average
	float heightVariation = 0;
	float lengthVariation = 0;
	float baselineVariation = 0;
	for (index = 0; index < onsetsLength - 1; index++)
	{
		currentOnset = Math::Abs(floatOnsets[index]);
		nextOnset = Math::Abs(floatOnsets[index + 1]);

		pulseLength = nextOnset - currentOnset;
		lengthVariation += Math::Abs(pulseLength - averagePulseLength);

		BizMath::FunctionValue(signal, signalLength, currentOnset, baseline);
		baselineVariation += (float) Math::Pow(baseline - averageBaseline, 2);

		Array::Copy(signal, (short) currentOnset, subset, 0, (short) pulseLength);
		BizMath::MinimumMaximumInArray(subset, (short) pulseLength, minimum, maximum);
		height = maximum - minimum;
		heightVariation += Math::Abs(height - averagePulseHeight);
	}

	// Average the variations in Height, Length and Baseline of -
	// each pulse from the average
	heightVariation /= (onsetsLength - 1);
	pulseHeightVariation = heightVariation/averagePulseHeight * 100;

	lengthVariation /= (onsetsLength - 1);
	pulseLengthVariation = lengthVariation/averagePulseHeight * 100;

	baselineVariation = (float) Math::Sqrt(baselineVariation/(onsetsLength - 1));
	pulseBaselineVariation = baselineVariation/averagePulseHeight * 100;
	
	return true;*/
}
#pragma unmanaged
bool BizCorCalculateQualityControls(unsigned short signalLength, 
									unsigned short onsetsLength, 
									unsigned short* signal, 
									float* floatOnsets,
									float* pulseHeight,
									float* pulseHeightVariation,
									float* pulseLengthVariation,
									float* pulseBaselineVariation)
{
	unsigned short minimum; 
	unsigned short maximum;
	float baseline;
	unsigned short height;
	float pulseLength;
	float currentOnset;
	float nextOnset;	
	unsigned short index;
	
	// Initialisation
	*pulseHeight = DEFAULT_VALUE;
	*pulseHeightVariation = DEFAULT_VALUE;
	*pulseLengthVariation = DEFAULT_VALUE;
	*pulseBaselineVariation = DEFAULT_VALUE;

	// Additional Validation, onsetsLength should never be less than 2
	if (onsetsLength <= 1)
	{
		return false;
	}

	// Sum the Heights, Lengths and Baselines of each pulse
	float averagePulseHeight = 0;
	float averagePulseLength = 0;
	float averageBaseline = 0;
	for (index = 0; index < onsetsLength - 1; index++)
	{
		currentOnset = fabs(floatOnsets[index]);
		nextOnset = fabs(floatOnsets[index + 1]);

		pulseLength = nextOnset - currentOnset;
		averagePulseLength += pulseLength;

		BizCorFunctionValue(signal, signalLength, currentOnset, &baseline);
		averageBaseline += baseline;

		BizCorMinimumMaximumInArray(&signal[(int) currentOnset], (unsigned short) pulseLength, &minimum, &maximum);
		height = maximum - minimum;
		averagePulseHeight += (float) height;
	}
	
	// Average the Heights, Lengths and Baselines of each pulse
	averagePulseHeight /= (onsetsLength - 1);
	averagePulseLength /= (onsetsLength - 1);
	averageBaseline /= (onsetsLength - 1);

	// Average Pulse Height
	if (averagePulseHeight > 0)
	{
		*pulseHeight = averagePulseHeight;
	}
	else
	{
		return false;
	}
	
	// Sum the variations in Height, Length and Baseline of -
	// each pulse from the average
	float heightVariation = 0;
	float lengthVariation = 0;
	float baselineVariation = 0;
	for (index = 0; index < onsetsLength - 1; index++)
	{
		currentOnset = fabs(floatOnsets[index]);
		nextOnset = fabs(floatOnsets[index + 1]);

		pulseLength = nextOnset - currentOnset;
		lengthVariation += fabs(pulseLength - averagePulseLength);

		BizCorFunctionValue(signal, signalLength, currentOnset, &baseline);
		baselineVariation += (float) pow(baseline - averageBaseline, 2);

		BizCorMinimumMaximumInArray(&signal[(int) currentOnset], (unsigned short) pulseLength, &minimum, &maximum);
		height = maximum - minimum;
		heightVariation += fabs((float)height - averagePulseHeight);
	}

	// Average the variations in Height, Length and Baseline of -
	// each pulse from the average
	heightVariation /= (onsetsLength - 1);
	*pulseHeightVariation = heightVariation/averagePulseHeight * 100;

	lengthVariation /= (onsetsLength - 1);
	*pulseLengthVariation = lengthVariation/averagePulseHeight * 100;

	baselineVariation = (float) sqrt(baselineVariation/(onsetsLength - 1));
	*pulseBaselineVariation = baselineVariation/averagePulseHeight * 100;
	
	return true;
}
#pragma managed
/**
 ** ValidateSignal()
 **
 ** DESCRIPTION:
 **  Validate Signal.

 ** INPUT:
 **  minimumSignalLength			- Minimum signal length,
 **  minimumSignalHeight			- Minimum signal amplitude,
 **  BizSignal::signalLength		- Number of accounted points in signal,
 **  BizSignal::sampleRate			- Signal Sample rate,
 **  BizSignal::signal				- Signal array,
 **  BizSignal::maximumSignalLength - Maximum accounted points in signal.

 ** OUTPUT:
 **   none.

 ** RETURN:
 **  boolean success or not.
*/
bool BizSignal::ValidateSignal(const unsigned short minimumSignalLength, const unsigned short minimumSignalHeight)
{
	// Validate length and input
	if (!ValidateSignalLength(minimumSignalLength))
	{
		return false;
	}
	
	// Validate Height and input
	if (!ValidateSignalHeight(minimumSignalHeight))
	{
		return false;
	}
	return true;
}

/**
 ** FindOnsets()
 **
 ** DESCRIPTION:
 **  Find trigger points (onsets) for a signal.

 ** INPUT:
 **  BizSignal::signalLength		- Number of accounted points in signal,
 **  BizSignal::sampleRate			- Signal Sample rate,
 **  BizSignal::signal				- Signal array,
 **  BizSignal::maximumOnsetsLength - Maximum number of onsets.

 ** OUTPUT:
 **  firstDerivative - Signal 1st Derivative,
 **  floatOnsets - Index of onsets in the signal,
 **  onsetsLength - Actual number of onsets.

 ** RETURN:
 **  boolean success or not.
*/
bool BizSignal::FindOnsets()
{
	// Prevent the Garbage Collector from deleting array's and -
	// output parameters
	pin_ptr<unsigned short> corSignal = &signal[0];
	pin_ptr<float> corFirstDerivative = &firstDerivative[0];
	pin_ptr<float> corFloatOnsets = &floatOnsets[0];
	pin_ptr<unsigned short> corOnsetsLength = &(unsigned short%)onsetsLength;
	
	bool success = BizCorFindOnsets(signalLength,
										sampleRate,
										maximumOnsetsLength,
										corSignal, 
										corFirstDerivative,
										corFloatOnsets,
										corOnsetsLength);

	// References to the class members themselves cannot be passed -
	// to a native function, so we assign them now
	onsetsLength = *corOnsetsLength;

	if (!success)
	{
#if 0 // TBD: Use a suitable CRX API
		CrxMessageFacade::Instance()->Message(TraceEventType::Error,
			CrxMessageFacade::Instance()->messageResources->GetString(L"MATH_ERROR", CultureInfo::CurrentUICulture), 
			/*GetCurrentMeasureDetails() +*/
			CrxMessageFacade::Instance()->messageResources->GetString(L"SIGNAL_ONSETS_ERROR", CultureInfo::CurrentUICulture), 
			/*GetCurrentMeasureDetails() +*/
			CrxMessageFacade::Instance()->messageResources->GetString(L"SIGNAL_ONSETS_ERROR", CultureInfo::InvariantCulture));
#endif
	}

	return success;
	
	/*bool success = false;
	
	// Initialise Onsets
	for (short i = 0; i < maximumOnsetsLength; i++)
	{
		floatOnsets[i] = DEFAULT_FLOAT_VALUE;
	}
	onsetsLength = 0;
	
	// Find the 1st derivative and its maximum
	// SmoothFirstDerivative cannot return false because only -
	// valid signals can be available in this class (see CaptureSignal) -
	// and smoothOrder and step are static
	float maximumFirstDerivative;
	BizMath::SmoothFirstDerivative(signal, signalLength, 
		SIGNAL_SMOOTH_ORDER, SIGNAL_STEP, firstDerivative, maximumFirstDerivative);
	
	// Find the average of the extremums of the 1st derivative which are higher
	// than 40% (FIRST_DERIVATIVE_THRESHOLD3) of the maximum of 1st derivative
	float averageMaximumFirstDerivative = 0;
	short extremums = 0;
	short loops = 0;
	do
	{
		int extremumFirstDerivative = 0;

		// Find the first extremum above the threshold starting at -
		// extremumFirstDerivative until there are no more extremums
		while (BizMath::IndexOfExtremum(firstDerivative, extremumFirstDerivative, signalLength, 
			FIRST_DERIVATIVE_THRESHOLD3 * maximumFirstDerivative, extremumFirstDerivative))
		{
			// Ignore the maximum of 1st derivative
			if (firstDerivative[extremumFirstDerivative] < maximumFirstDerivative)
			{
				averageMaximumFirstDerivative += firstDerivative[extremumFirstDerivative];
				extremums++;
			}
			// Find the next extremum
			extremumFirstDerivative++;
		}
	  
		// Calculate the average if enough extremums were found
		if (extremums > 3)
		{
			averageMaximumFirstDerivative /= extremums;
			break;
		}
		else
		{
			// Otherwise, lower the threshold and try again
			if (loops++ < 5)
			{
				maximumFirstDerivative *= (float) 0.9;
			}
			// After 5 attempts, set the average to the maximum and give up
			else
			{
				averageMaximumFirstDerivative = maximumFirstDerivative;
				break;
			}
		}
	} while (extremums <= 3);

	// Find Onsets using the Tangent Algorithm
	success = TangentAlgorithm(averageMaximumFirstDerivative);
	
	if (!success)
	{
		CrxMessageFacade::Instance()->Message(TraceEventType::Error,
			CrxMessageFacade::Instance()->messageResources->GetString(L"MATH_ERROR", CultureInfo::CurrentUICulture), 
			/*GetCurrentMeasureDetails() +
			CrxMessageFacade::Instance()->messageResources->GetString(L"SIGNAL_ONSETS_ERROR", CultureInfo::CurrentUICulture), 
			/*GetCurrentMeasureDetails() +
			CrxMessageFacade::Instance()->messageResources->GetString(L"SIGNAL_ONSETS_ERROR", CultureInfo::InvariantCulture));
	}
	return success;*/
}

#pragma unmanaged
bool BizCorFindOnsets(unsigned short signalLength, unsigned short sampleRate, unsigned short maximumOnsetsLength,
						unsigned short* signal, float* firstDerivative, 
						float* floatOnsets,	unsigned short* onsetsLength)
{
	bool success = false;
	
	// Initialise Onsets
	for (unsigned short i = 0; i < maximumOnsetsLength; i++)
	{
		floatOnsets[i] = DEFAULT_FLOAT_VALUE;
	}
	*onsetsLength = 0;
	
	// Find the 1st derivative and its maximum
	// SmoothFirstDerivative cannot return false because only -
	// valid signals can be available in this class (see CaptureSignal) -
	// and smoothOrder and step are static
	float maximumFirstDerivative;
	BizCorSmoothFirstDerivative(signal, signalLength, SIGNAL_SMOOTH_ORDER, 
					SIGNAL_STEP, firstDerivative, &maximumFirstDerivative);
	
	// Find the average of the extremums of the 1st derivative which are higher
	// than 40% (FIRST_DERIVATIVE_THRESHOLD3) of the maximum of 1st derivative
	float averageMaximumFirstDerivative = 0;
	unsigned short extremums = 0;
	unsigned short loops = 0;
	do
	{
		unsigned short extremumFirstDerivative = 0;

		// Find the first extremum above the threshold starting at -
		// extremumFirstDerivative until there are no more extremums
		while (BizCorIndexOfExtremum(firstDerivative, extremumFirstDerivative, signalLength, 
			FIRST_DERIVATIVE_THRESHOLD3 * maximumFirstDerivative, &extremumFirstDerivative))
		{
			// Ignore the maximum of 1st derivative
			if (firstDerivative[extremumFirstDerivative] < maximumFirstDerivative)
			{
				averageMaximumFirstDerivative += firstDerivative[extremumFirstDerivative];
				extremums++;
			}
			// Find the next extremum
			extremumFirstDerivative++;
		}
	  
		// Calculate the average if enough extremums were found
		if (extremums > 3)
		{
			averageMaximumFirstDerivative /= extremums;
			break;
		}
		else
		{
			// Otherwise, lower the threshold and try again
			if (loops++ < 5)
			{
				maximumFirstDerivative *= (float) 0.9;
			}
			// After 5 attempts, set the average to the maximum and give up
			else
			{
				averageMaximumFirstDerivative = maximumFirstDerivative;
				break;
			}
		}
	} while (extremums <= 3);

	// Find Onsets using the Tangent Algorithm
	success = BizCorTangentAlgorithm(averageMaximumFirstDerivative,
										signalLength, 
										sampleRate, 
										maximumOnsetsLength,
										signal, 
										firstDerivative, 
										floatOnsets,	
										onsetsLength);
	
	return success;
}
/*
 ** TangentAlgorithm()
 **
 ** DESCRIPTION:
 **  Find onsets using tangent algorithm - crossing of
 **  pulse foot line by tangent at point of maximum dP/dt

 ** INPUT:
 **  maximumFirstDerivative			- Average of the 1st derivative maximums,
 **  BizSignal::signalLength		- Number of accounted points in signal,
 **  BizSignal::sampleRate			- Signal Sample rate,
 **  BizSignal::signal				- Signal array,
 **  BizSignal::maximumOnsetsLength - Maximum number of onsets,
 **  BizSignal::firstDerivative		- Signal 1st Derivative.

 ** OUTPUT:
 **  floatOnsets - Index of onsets in the signal,
 **  onsetsLength - Actual number of onsets.

 ** RETURN:
 **  boolean success or not.
*/
bool BizCorTangentAlgorithm(const float maximumFirstDerivative, unsigned short signalLength, 
							unsigned short sampleRate, unsigned short maximumOnsetsLength,
							unsigned short* signal, float* firstDerivative, 
							float* floatOnsets,	unsigned short* onsetsLength)
{
	// Validate Input
	if (maximumFirstDerivative <= -DEFAULT_VALUE || maximumFirstDerivative >= DEFAULT_VALUE)
	{
		return false;
	}
	
	// Minimum pulse length
	unsigned short minimumPulseLength = 60 * sampleRate / MAX_HEART_RATE;
	
	// Threshold values are 70% (threshold1) and 65% (threshold2) -
	// of the maximum 1st derivative
	float threshold1 = FIRST_DERIVATIVE_THRESHOLD1 * maximumFirstDerivative;
	float threshold2 = FIRST_DERIVATIVE_THRESHOLD2 * maximumFirstDerivative;

	bool weAreInPeak = false;
	bool thisIsBeginning = true;
	short peakIndex = -1;
	short footIndex;
	short previousOnsetIndex = 0;

	// Find All Trigger Points in the signal
	for (short index = 0; index < signalLength; index++)
	{	
		// Avoid onsets within the minimum pulse length of the previous onset
		if (*onsetsLength > 0)
		{
			previousOnsetIndex = (short) floatOnsets[*onsetsLength - 1];
			if (index - previousOnsetIndex < minimumPulseLength)
			{
				continue;
			}

			// When searching for the minimum, we do not want to -
			// search all the way back to the previous onset
			previousOnsetIndex++;
		}
		
		// Wait for the derivative to drop below the threshold -
		// because we need to find a peak first
		if (firstDerivative[index] >= threshold1)
		{
			if (thisIsBeginning)
			{	
				continue;
			}
			weAreInPeak = true;
		}
		thisIsBeginning = false;

		if (!weAreInPeak)
		{
			continue;
		}

		if (firstDerivative[index] > threshold2)
		{
			// This is the first point in the peak
			if (peakIndex < 0)
			{
				peakIndex = index;
				continue;
			}
			
			// Find the maximum of the 1st derivative (maximum dp/dt)
			if (firstDerivative[index] > firstDerivative[peakIndex])
			{
				peakIndex = index;
			}
		}
		else
		{
			// The end of the peak. Now find the previous minimum
			weAreInPeak = false;			
			footIndex = -1;

			// Find the foot index at the first minimum before this peak
			for (short i = peakIndex; i > previousOnsetIndex; i--)
			{
				if (signal[i] <= signal[i-1])
				{
					footIndex = i;
					break;
				}
			}
			
			// tangent is the maximum slope (maximum dp/dt)
			float tangent = firstDerivative[peakIndex]; 

			// Validate
			if (footIndex < 0 || tangent <= 0)
			{
				peakIndex = -1;
				continue;
			}
			
			// Find where the tangent intersects the foot
			float signalChange = float(signal[peakIndex] - signal[footIndex]);
			float indexChange = signalChange/tangent;
			
			// Find onset checking that it is not before the previous onset
			if (float(peakIndex) - indexChange > previousOnsetIndex)
			{
				floatOnsets[*onsetsLength] = (float(peakIndex) - indexChange);
				*onsetsLength = *onsetsLength + 1;
			}

			// Find the next onset
			peakIndex = -1;

			// Check onsetsLength limit. If more, stop process
			if (*onsetsLength == maximumOnsetsLength) 
			{
				break;
			}
		}
	}

	// return success if the minimum onsets were found
	return (*onsetsLength >= MIN_ONSETS);
}
/*
bool BizSignal::TangentAlgorithm(const float maximumFirstDerivative)
{
	// Validate Input
	if (maximumFirstDerivative <= -DEFAULT_VALUE || maximumFirstDerivative >= DEFAULT_VALUE)
	{
		return false;
	}
	
	// Minimum pulse length
	short minimumPulseLength = 60 * sampleRate / MAX_HEART_RATE;
	
	// Threshold values are 70% (threshold1) and 65% (threshold2) -
	// of the maximum 1st derivative
	float threshold1 = FIRST_DERIVATIVE_THRESHOLD1 * maximumFirstDerivative;
	float threshold2 = FIRST_DERIVATIVE_THRESHOLD2 * maximumFirstDerivative;

	bool weAreInPeak = false;
	bool thisIsBeginning = true;
	short peakIndex = -1;
	short footIndex;
	short previousOnsetIndex = 0;

	// Find All Trigger Points in the signal
	for (short index = 0; index < signalLength; index++)
	{	
		// Avoid onsets within the minimum pulse length of the previous onset
		if (onsetsLength > 0)
		{
			previousOnsetIndex = (short) floatOnsets[onsetsLength - 1];
			if (index - previousOnsetIndex < minimumPulseLength)
			{
				continue;
			}

			// When searching for the minimum, we do not want to -
			// search all the way back to the previous onset
			previousOnsetIndex++;
		}
		
		// Wait for the derivative to drop below the threshold -
		// because we need to find a peak first
		if (firstDerivative[index] >= threshold1)
		{
			if (thisIsBeginning)
			{	
				continue;
			}
			weAreInPeak = true;
		}
		thisIsBeginning = false;

		if (!weAreInPeak)
		{
			continue;
		}

		if (firstDerivative[index] > threshold2)
		{
			// This is the first point in the peak
			if (peakIndex < 0)
			{
				peakIndex = index;
				continue;
			}
			
			// Find the maximum of the 1st derivative (maximum dp/dt)
			if (firstDerivative[index] > firstDerivative[peakIndex])
			{
				peakIndex = index;
			}
		}
		else
		{
			// The end of the peak. Now find the previous minimum
			weAreInPeak = false;			
			footIndex = -1;

			// Find the foot index at the first minimum before this peak
			for (short i = peakIndex; i > previousOnsetIndex; i--)
			{
				if (signal[i] <= signal[i-1])
				{
					footIndex = i;
					break;
				}
			}
			
			// tangent is the maximum slope (maximum dp/dt)
			float tangent = firstDerivative[peakIndex]; 

			// Validate
			if (footIndex < 0 || tangent <= 0)
			{
				peakIndex = -1;
				continue;
			}
			
			// Find where the tangent intersects the foot
			float signalChange = signal[peakIndex] - signal[footIndex];
			float indexChange = signalChange/tangent;
			
			// Find onset checking that it is not before the previous onset
			if (float(peakIndex) - indexChange > previousOnsetIndex)
			{
				floatOnsets[onsetsLength] = (float(peakIndex) - indexChange);
				onsetsLength++;
			}

			// Find the next onset
			peakIndex = -1;

			// Check onsetsLength limit. If more, stop process
			if (onsetsLength == maximumOnsetsLength) 
			{
				break;
			}
		}
	}

	// return success if the minimum onsets were found
	return (onsetsLength >= MIN_ONSETS);
}*/