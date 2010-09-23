// bizcor.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "bizcor.h"
#include <math.h>
#include <biz.h>

using namespace Biz;

// This is an example of an exported variable
BIZCORNATIVEDLL_API int nBizCorNativeDLL=0;

// This is an example of an exported function.
BIZCORNATIVEDLL_API int fnBizCorNativeDLL(void)
{
	return 42;
}

// ctor
CPerson::CPerson()
{
   *m_sName = 0;
   ::ZeroMemory(&m_birthDate, sizeof(m_birthDate));
}

CPerson::CPerson(LPCTSTR pszName, SYSTEMTIME birthDate): m_birthDate(birthDate)
{
   if (pszName != 0)
      ::lstrcpy(m_sName, pszName);
}

unsigned int CPerson::get_Age(void)
{
   SYSTEMTIME st;
   unsigned int age;

   ::GetSystemTime(&st);

   age = (unsigned int)(st.wYear - m_birthDate.wYear);

   if ((m_birthDate.wMonth > st.wMonth) ||
      ((m_birthDate.wMonth == st.wMonth) && (m_birthDate.wDay > st.wDay)))
   {
      --age;
      ::MessageBeep(0);
   }

   return age;
}

/**
 ** ValidateArray()
 **
 ** DESCRIPTION:
 **  Validate the array boundaries.

 ** INPUT:
 **  input[size] - array.
 
 ** OUTPUT:
 **  none.

 ** RETURN:
 **  bool success or not.
*/
/*
bool BizCorValidateArray(const float* input, int size)
{
	if (input == NULL)
	{
		return false; 
	}
	if (size < 1 || size >= DEFAULT_VALUE)// || size > sizeof(input) / sizeof(float))
	{
		return false;
	}
	for (int i = 0; i < size; i++)
	{
		if (input[i] >= DEFAULT_VALUE || input[i] <= -DEFAULT_VALUE)
		{
			return false;
		}
	}
	return true;
}
*/
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
BIZCORNATIVEDLL_API bool BizCorCalculateQualityControls(short signalLength, 
														short onsetsLength, 
														float* signal, 
														float* floatOnsets,
														float& pulseHeight,
														float& pulseHeightVariation,
														float& pulseLengthVariation,
														float& pulseBaselineVariation)
{
	float minimum = 0; 
	float maximum = 0;
	float baseline = 0;
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
	//array<const float>^ subset = gcnew array<const float>((short) signalLength);

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

		//BizMath::FunctionValue(signal, signalLength, currentOnset, baseline);
		averageBaseline += baseline;

		//Array::Copy(signal, (short) currentOnset, subset, 0, (short) pulseLength);
		//BizMath::MinimumMaximumInArray(subset, (short) pulseLength, minimum, maximum);
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
		currentOnset = fabs(floatOnsets[index]);
		nextOnset = fabs(floatOnsets[index + 1]);

		pulseLength = nextOnset - currentOnset;
		lengthVariation += fabs(pulseLength - averagePulseLength);

		//BizMath::FunctionValue(signal, signalLength, currentOnset, baseline);
		baselineVariation += (float) pow(baseline - averageBaseline, 2);

		//Array::Copy(signal, (short) currentOnset, subset, 0, (short) pulseLength);
		//BizMath::MinimumMaximumInArray(subset, (short) pulseLength, minimum, maximum);
		height = maximum - minimum;
		heightVariation += fabs(height - averagePulseHeight);
	}

	// Average the variations in Height, Length and Baseline of -
	// each pulse from the average
	heightVariation /= (onsetsLength - 1);
	pulseHeightVariation = heightVariation/averagePulseHeight * 100;

	lengthVariation /= (onsetsLength - 1);
	pulseLengthVariation = lengthVariation/averagePulseHeight * 100;

	baselineVariation = (float) sqrt(baselineVariation/(onsetsLength - 1));
	pulseBaselineVariation = baselineVariation/averagePulseHeight * 100;

	return true;
}