/*
    Copyright (C) ATCOR MEDICAL PTY LTD, 2010

    Filename	 :	signal.h
	
	Author       :  Paul McBryde

    Description  :	DECLARATION of Signal Class
*/

#pragma once
#include <biz.h>
#include <math_library.h>
#include <biz_namespace.h>

using namespace System::Runtime::InteropServices;

START_BIZ_NAMESPACE

public ref class BizSignal
{

public:

	property unsigned short	signalLength;	// Number of accounted points in signal
	property unsigned short	onsetsLength;	// Actual number of onsets
	property unsigned short	sampleRate;		// Signal Sample rate
	property float	pulseHeight;			// Quality Control - pulse height
	property float	pulseHeightVariation;	// Quality Control - pulse height variation
	property float	pulseLengthVariation;	// Quality Control - pulse length variation
	property float	pulseBaselineVariation;	// Quality Control - baseline variation

	property array<unsigned short>^ signal			// Signal array
	{
		array<unsigned short>^ get() 
		{
			return _signal;
		}
	private: void set(array<unsigned short>^ input) 
		{
			_signal = input;
		}
	}

	property array<float>^ floatOnsets		// Index of onsets in the signal
	{
		array<float>^ get() 
		{
			return _floatOnsets;
		}
	private: void set(array<float>^ input) 
		{
			_floatOnsets = input;
		}
	}

	property array<float>^ firstDerivative	// Signal 1st Derivative
	{
		array<float>^ get() 
		{
			return _firstDerivative;
		}
	private: void set(array<float>^ input) 
		{
			_firstDerivative = input;
		}
	}

private:
	property bool			_readyToCapture;		
	array<unsigned short>^	_signal;
	array<float>^			_floatOnsets;	
	array<float>^			_firstDerivative;

protected:
	property unsigned short maximumSignalLength;		// Maximum accounted points in signal
	property unsigned short maximumOnsetsLength;		// Maximum number of onsets
	
public:
	// Member functions:

	// Constructor
	BizSignal();
	
	// Initialise properties
	bool Initialise(const unsigned short inputSampleRate);
	bool Allocate(const unsigned short inputMaximumSignalLength, const unsigned short inputMaximumOnsetsLength);

	// Set default values for onsets not touching Signal
	void SetDefaults();

	// Store whole signal in Signal array
	bool CaptureSignal(array<const unsigned short>^ input, const unsigned short size);

	// Allow signal capture
	void PrepareToCapture();
	
	// Validate Signal length
	bool ValidateSignalLength(const unsigned short minimumSignalLength);

	// Validate Signal amplitude
	bool ValidateSignalHeight(const unsigned short minimumSignalHeight);

	// Validate signal record before storing in Database
	bool ValidateBeforeStore(const unsigned short minimumSignalLength, const unsigned short minimumOnsetsLength,
							 const unsigned short minimumSignalHeight);

	// Calculate Quality Control parameters for a Signal
	bool CalculateQualityControls();

	// Validate Signal
	bool ValidateSignal(const unsigned short minimumSignalLength, const unsigned short minimumSignalHeight);

	// Find Trigger points for TSignal signal
	bool FindOnsets();
	
	// Find onsets using tangent algorithm (crossing of
	// pulse foot line by tangent at point of maximum dP/dt
	//bool TangentAlgorithm(const float maximumFirstDerivative);
	
};
END_BIZ_NAMESPACE

static bool BizCorCalculateQualityControls(unsigned short signalLength, 
											unsigned short onsetsLength, 
											unsigned short* signal, 
											float* floatOnsets,
											float* pulseHeight,
											float* pulseHeightVariation,
											float* pulseLengthVariation,
											float* pulseBaselineVariation);
static bool BizCorFindOnsets(unsigned short signalLength, unsigned short sampleRate, unsigned short maximumOnsetsLength,
						unsigned short* signal, float* firstDerivative, 
						float* floatOnsets,	unsigned short* onsetsLength);
bool BizCorTangentAlgorithm(const float maximumFirstDerivative, unsigned short signalLength, 
							unsigned short sampleRate, unsigned short maximumOnsetsLength,
							unsigned short* signal, float* firstDerivative, 
							float* floatOnsets,	unsigned short* onsetsLength);