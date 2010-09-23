/*
    Copyright (C) ATCOR MEDICAL PTY LTD, 2010

    Filename	 :	signal.h
	
	Author       :  Paul McBryde

    Description  :	DECLARATION of Signal Class
*/

#pragma once
#include <biz.h>
#include <math.h>
using namespace System::Runtime::InteropServices;

namespace Biz {

	public ref class BizSignal
	{
	
	public:

		property short	signalLength;			// Number of accounted points in signal
		property short	onsetsLength;			// Actual number of onsets
		property short	sampleRate;				// Signal Sample rate
		property float	pulseHeight;			// Quality Control - pulse height
		property float	pulseHeightVariation;	// Quality Control - pulse height variation
		property float	pulseLengthVariation;	// Quality Control - pulse length variation
		property float	pulseBaselineVariation;	// Quality Control - baseline variation

		property array<float>^ signal			// Signal array
		{
			array<float>^ get() 
			{
				return _signal;
			}
		private: void set(array<float>^ input) 
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

		// Direct native API call.
		/*[DllImport("bizcor.dll")]
		static bool BizCorCalculateQualityControls(short signalLength, 
														short onsetsLength, 
														array<float>^ signal, 
														array<float>^ floatOnsets,
														float% pulseHeight,
														float% pulseHeightVariation,
														float% pulseLengthVariation,
														float% pulseBaselineVariation);*/

	private:
		property bool	_readyToCapture;		
    	array<float>^	_signal;
		array<float>^	_floatOnsets;	
		array<float>^	_firstDerivative;

	protected:
		property short   maximumSignalLength;		// Maximum accounted points in signal
		property short   maximumOnsetsLength;		// Maximum number of onsets
		
	public:
		// Member functions:

		// Constructor
		BizSignal();
		
		// Initialise properties
		bool Initialise(const short inputSampleRate);
		bool Allocate(const short inputMaximumSignalLength, const short inputMaximumOnsetsLength);

		// Set default values for onsets not touching Signal
		void SetDefaults();

		// Store whole signal in Signal array
		bool CaptureSignal(array<const short>^ input, const short size);

		// Allow signal capture
		void PrepareToCapture();
		
		// Validate Signal length
		bool ValidateSignalLength(const short minimumSignalLength);

		// Validate Signal amplitude
		bool ValidateSignalHeight(const short minimumSignalHeight);

		// Validate signal record before storing in Database
		bool ValidateBeforeStore(const short minimumSignalLength, const short minimumOnsetsLength,
								 const short minimumSignalHeight);

		// Calculate Quality Control parameters for a Signal
		bool CalculateQualityControls();

		// Validate Signal
		bool ValidateSignal(const short minimumSignalLength, const short minimumSignalHeight);
    
		// Find Trigger points for TSignal signal
		bool FindOnsets();
		
		// Find onsets using tangent algorithm (crossing of
		// pulse foot line by tangent at point of maximum dP/dt
		bool TangentAlgorithm(const float maximumFirstDerivative);
		
	};
}
static bool BizCorCalculateQualityControls(short signalLength, 
											short onsetsLength, 
											float* signal, 
											float* floatOnsets,
											float pulseHeight,
											float pulseHeightVariation,
											float pulseLengthVariation,
											float pulseBaselineVariation);