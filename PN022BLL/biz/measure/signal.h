/*
    Copyright (C) ATCOR MEDICAL PTY LTD, 2010

    Filename	 :	signal.h
	
	Author       :  Paul McBryde

    Description  :	DECLARATION of Signal Class
*/

#pragma once
#include <biz.h>
#include <math.h>

namespace Biz {

	public ref class BizSignal
	{
	
	public:

		property short			signalLength;	// Number of accounted points in signal=SIGNAL_MAX_PPOINTS
		property short			onsetsLength;   // Actual number of onsets
    	property array<float>^	signal;			// Signal array
    	property array<float>^	floatOnsets;	// Float onsets for PWV
    	property short			sampleRate;     // Signal Sample rate
    
		property float pulseHeight;				// Quality Control - pulse height
		property float pulseHeightVariation;	// Quality Control - pulse height variation
		property float pulseLengthVariation;	// Quality Control - pulse length variation
		property float baseLineVariation;		// Quality Control - baseline variation

		property array<float>^ derivative1;		// Signal derivative1
		property array<float>^ derivative2;		// Signal derivative2
    
	private:
		property bool  readyToCapture;
	
	protected:
		property short   maxSignalLength;		// Maximal NofPoints
		property short   maxOnsetsLength;		// Maximal NofOnsets
		
	public:
		// Member functions:

		// Constructor
		BizSignal();
		
		// Initialise properties
		bool Initialise(const short inputSampleRate);
		bool Allocate(const short inputMaxSignalLength, const short inputMaxOnsetsLength);

		// Set default values for onsets not touching Signal
		void SetDefaults();

		// Store whole signal in Signal array
		bool CaptureSignal(array<const short>^ input, const short size);

		// Allow signal capture
		void PrepareToCapture();
		
		// Validate Signal length
		bool ValidateSignalLength(const short minSignalLength);

		// Validate Signal amplitude
		bool ValidateSignalHeight(const short minSignalHeight);

		// Validate signal record before storing in Database
		bool ValidateBeforeStore(const short minSignalLength, const short minOnsetsLength,
								 const short minSignalHeight);

		// Calculate Quality Control parameters for a Signal
		bool CalculateQualityControls();

		// Validate Signal
		bool ValidateSignal(const int minSignalLength);
    
		// Find Trigger points for TSignal signal
		bool FindOnsets(const int algorithm);
		
		// Find onsets using tangent algorithm (crossing of
		// pulse foot line by tangent at point of max dP/dt
		bool TangentAlgorithm(const float maxDerivative1, const int minPulseLength);
		
	};
}