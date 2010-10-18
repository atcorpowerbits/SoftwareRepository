/*
    Copyright (C) ATCOR MEDICAL PTY LTD, 2010

    Filename	 :	measure_pwv.h
	
	Author       :  Victor Aung

    Description  :	DECLARATION of Business Logic Layer PWV Measurement
*/

#pragma once

#include <measure.h>
#include <capture.h>
#include <cuff.h>

using namespace System;
using namespace DataAccess;

namespace Biz {

	const unsigned short PWV_DISTANCE_MIN = 10;
	const unsigned short PWV_DISTANCE_MAX = 2200;
	const unsigned short PWV_FEM2CUFF_MIN = 10;
	const unsigned short PWV_FEM2CUFF_MAX = 700;
	const unsigned short PWV_MAX_ONSETS = 30 * 3;

	/*---------------------------------------------------------------------------
	// Pulse Wave Velocity data structure
	//---------------------------------------------------------------------------
	typedef struct
	{
		float value;	// Pulse wave velocity (in m/s)
		bool isValid;	// Pulse wave velocity is valid/invalid
	} BizDelta;*/

	// Abstract distance with validation
	public ref class BizDistance abstract
	{
	public:
		virtual bool Validate() = 0;
		property unsigned short distance;
	};
	// Carotid distance with validation
	public ref class BizCarotidDistance : BizDistance
	{
	public:
		virtual bool Validate() override;
	};
	// Cuff distance with validation
	public ref class BizCuffDistance : BizDistance
	{
	public:
		virtual bool Validate() override;
	};
	// Femoral to cuff distance with validation
	public ref class BizFemoral2CuffDistance : BizDistance
	{
	public:
		virtual bool Validate() override;
	};
	// PWV direct distance with validation
	public ref class BizPWVDirectDistance : BizDistance
	{
	public:
		virtual bool Validate() override;
	};
	// PWV Measurement
	public ref class BizPWV : BizMeasure
	{
	public:

		property BizCarotidDistance^ myCarotidDistance;
		property BizCuffDistance^ myCuffDistance;
		property BizFemoral2CuffDistance^ myFemoral2CuffDistance;
		property BizPWVDirectDistance^ myPWVDirectDistance;

		// Validate PWV distance with respect to calculation method used
		bool ValidatePWVDistance();

		virtual bool StartCapture() override;
		virtual bool StopCapture() override;
		virtual void DispatchCaptureData() override;

		property BizTonometerDataCapture^ tonometerDataObserver;
		property BizCuffPulseCapture^ cuffPulseObserver;
		property BizCountdownTimerCapture^ countdownTimerObserver;
		property BizCuff^ cuffObserver;

		property float meanDeltaTime;				// Mean pulse onset time difference (in ms) between pulse traces
		property array<float>^ deltaTime;			// Pulse onset time difference (in ms) between pulse traces of each pulse
		property float correctionTime;				// Correction factor to convert Carotid-Cuff time to Carotid-Femoral time
		property float meanPulseWaveVelocity;		// Mean pulse wave velocity (in m/s)
		property float standardDeviation;			// standard deviation (in m/s) of pulse wave velocity

		property unsigned short numberOfPulses;          // Actual number of DeltaT values
		property unsigned short numberOfValidPulses;	// Actual number of valid DeltaT values
    
		property bool isStandardDeviationValid;			// Indicate to operator whether quality satisfactory
		property float HeartRate;						// Heart rate of the ECG (in bpm)

		//BizDelta pulseWaveVelocity[PWV_MAX_ONSETS];  // Time difference

		//BizSignal^ signalA; // Site A signal
		//BizSignal^ signalB;   // Site B signal

	public:
		// Member functions:

		virtual bool Validate() override;
		BizPWV(void);	
    
		// Initialise properties
		void Initialise(const int signalSampleRate);

		// Do all mathematics for this measurement
		bool Calculate();

		// Prepare PWV class to store signals
		void PrepareToCaptureSignal();
	    
		// Validate PWV class properties before Store in database
		bool ValidateBeforeStore();

		// Validate PWV class properties before Calculation routine
		bool ValidateBeforeCalculate();
	    
		// Save arrays if an error occurs while calculating
		bool SaveToFile();
	    
	private:
		// Work array to mark rejected Onsets
		array<short int>^ rejectedOnsets; // = gcnew array<short int>(PWV_MAX_ONSETS);
		
		// Set default values for calculated variables
		void SetDefaults();

		// Calculate distances
		bool CalculateDistance();

		// Calculate PWV, MeanDt, Deviation for this measurement
		bool CalcMainFeatures();

		// Calculate time difference between Tonometer and Cuff Onsets
		bool CalcDeltaT(const int sampleRate);

		// Calculate Heart rate on the base of ECG Onsets
		bool CalcHeartRate(const int sampleRate);

		// Calculate DeltaT average (MeanDt) and its standard deviation
		bool MeanDeviation();

		};
}