/*
    Copyright (C) ATCOR MEDICAL PTY LTD, 2010

    Filename	 :	measure_pwv.h
	
	Author       :  Victor Aung

    Description  :	DECLARATION of Business Logic Layer PWV Measurement
*/

#pragma once

#include <measure.h>
#include <capture.h>
#include <biz.h>
#include <signal.h>
#include <cuff.h>
#include <quality.h>

using namespace System;
using namespace DAL_NAMESPACE;

START_BIZ_NAMESPACE
	
// Abstract distance with validation
public ref class BizDistance abstract
{
public:
	virtual bool Validate() = 0;
	property unsigned short distance;
protected:
	BizDistance() {};
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

// Pulse Wave Velocity array class
public ref class BizDelta
{
public:
	property float deltaTime;			// Pulse onset time difference (in ms) between pulse traces of each pulse
	property float correctedTime;		// Pulse onset time difference (in ms) corrected for cuff to femoral distance
	property float pulseWaveVelocity;	// Pulse wave velocity (in m/s)
	property bool isValid;				// Pulse wave velocity is valid/invalid

	// Set default values for calculated variables
	void SetDefaults();
};


// PWV Measurement
public ref class BizPWV : BizMeasure
{
public:

	property BizCarotidDistance^ myCarotidDistance;
	property BizCuffDistance^ myCuffDistance;
	property BizFemoral2CuffDistance^ myFemoral2CuffDistance;
	property BizPWVDirectDistance^ myPWVDirectDistance;
	property unsigned short calculatedDistance;		// Distance used to calculate pulse wave velocity - must be in mm

	property float correctionTime;					// Correction factor to convert Carotid-Cuff time to Carotid-Femoral time
	
	property BizTonometerDataCapture^ tonometerDataObserver;
	property BizCuffPulseCapture^ cuffPulseObserver;
	property BizCountdownTimerCapture^ countdownTimerObserver;
	property BizCuff^ cuffObserver;
	property BizQuality^ carotidQualityObserver;

	property BizSignal^ carotidSignal;				// Carotid Tonometer signal
	property BizSignal^ femoralSignal;				// Femoral Cuff signal
	property bool isCarotidSignalValid;				// Indicate to operator whether carotid quality is satisfactory
	property bool isFemoralSignalValid;				// Indicate to operator whether femoral quality is satisfactory
	
	property unsigned short numberOfDeltas;         // Actual number of BizDelta values
	property unsigned short numberOfValidDeltas;	// Actual number of valid BizDelta values

	property float heartRate;						// Heart rate of the ECG (in bpm)
	
	property float meanDeltaTime;					// Mean pulse onset time difference (in ms) between pulse traces
	property float meanCorrectedTime;				// Mean Carotid-Femoral time difference (in ms) between pulse traces
	property float meanPulseWaveVelocity;			// Mean pulse wave velocity (in m/s)
	property float standardDeviation;				// standard deviation (in m/s) of pulse wave velocity
	property bool isStandardDeviationValid;			// Indicate to operator whether standard deviation quality is satisfactory

	property array<BizDelta^>^ pulseWaveVelocity	// Time differences and pulse wave velocities
	{
		array<BizDelta^>^ get() 
		{
			return _pulseWaveVelocity;
		}
	private: void set(array<BizDelta^>^ input) 
		{
			_pulseWaveVelocity = input;
		}
	}

private:
	array<BizDelta^>^			_pulseWaveVelocity;

public:
	// Member functions:
	BizPWV(void);	

	// Validate PWV distance with respect to calculation method used
	bool ValidatePWVDistance();

	virtual bool StartCapture() override;
	virtual bool StopCapture() override;
	virtual void DispatchCaptureData() override;

	// Validate PWV class properties
	virtual bool Validate() override;
	
	// Initialise properties
	void Initialise();

	// Do all mathematics for this measurement
	bool Calculate();

	// Prepare PWV class to store signals
	void PrepareToCaptureSignal();
    
	// Validate the PWV measurement before storing
	bool ValidateBeforeStore();

	// Validate Signal class properties
	bool ValidateSignals();
    
	// Save arrays if an error occurs while calculating
	bool SaveToFile();
    
private:
	// Set default values for calculated variables
	void SetDefaults();

	// Calculate and validate distance
	bool CalculateAndValidateDistance();

	// Calculate quality control members
	bool CalculateQualityControls();
	
	// Calculate Heart rate on the base of ECG Onsets
	bool CalculateHeartRate();
	
	// Calculate the BizDelta array between the femoral and carotid signals
	bool CalculateBizDeltaArray();

	// Calculate PWV, MeanDt, standardDeviation for this measurement
	bool CalculateFeatures();

};

END_BIZ_NAMESPACE
