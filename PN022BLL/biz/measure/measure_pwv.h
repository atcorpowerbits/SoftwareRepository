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
using namespace CRX_DATABASE_MANAGER_NAMESPACE;

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

// Delta class for each Carotid - Femoral pressure pulse pair
public ref class BizDelta
{
public:
	property float heartRate;			// Heart rate (in bpm)
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
	property unsigned short distanceMethod;		// Distance method selected when the object was calculated
		
	property float correctionTime;					// Correction factor to convert Carotid-Cuff time to Carotid-Femoral time
	property unsigned short deflationTime;			// To be subtracted from time to deflation countdown timer to adjust 
													// countdown timer to reach zero when cuff starts to deflate
	
	property BizTonometerDataCapture^ tonometerDataObserver;
	property BizCuffPulseCapture^ cuffPulseObserver;
	property BizCountdownTimerCapture^ countdownTimerObserver;
	property BizCuff^ cuffObserver;
	property BizQuality^ carotidQualityObserver;
	property BizQuality^ femoralQualityObserver;

	property BizSignal^ carotidSignal;				// Carotid Tonometer signal
	property BizSignal^ femoralSignal;				// Femoral Cuff signal
	property bool isCarotidSignalValid;				// Indicate to operator whether carotid quality is satisfactory
	property bool isFemoralSignalValid;				// Indicate to operator whether femoral quality is satisfactory
	
	property unsigned short numberOfDeltas;         // Actual number of BizDelta values
	property unsigned short numberOfValidDeltas;	// Actual number of valid BizDelta values

	property float meanHeartRate;					// Heart rate of the Femoral signal (in bpm)
	
	property float meanDeltaTime;					// Mean pulse onset time difference (in ms) between pulse traces
	property float meanCorrectedTime;				// Mean Carotid-Femoral time difference (in ms) between pulse traces
	property float meanPulseWaveVelocity;			// Mean pulse wave velocity (in m/s)
	property float standardDeviation;				// standard deviation (in m/s) of pulse wave velocity
	property bool isStandardDeviationValid;			// Indicate to operator whether standard deviation quality is satisfactory

	property float referenceRangeDistance;			// Distance used to calculate the reference range pulse wave velocity - must be in mm
	property float referenceRangePulseWaveVelocity; // Pulse wave velocity to be displayed on the reference range graph (in m/s)

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

	property array<float>^ normalRange				// Upper limit of normal PWV range for display
	{
		array<float>^ get() 
		{
			return _normalRange;
		}
	private: void set(array<float>^ input) 
		{
			_normalRange = input;
		}
	}

	property array<float>^ referenceRange			// Upper limit of reference PWV range for display
	{
		array<float>^ get() 
		{
			return _referenceRange;
		}
	private: void set(array<float>^ input) 
		{
			_referenceRange = input;
		}
	}

private:
	array<BizDelta^>^ _pulseWaveVelocity;
	array<float>^ _normalRange;
	array<float>^ _referenceRange;
	BizBuffer^ tonometerBuffer;
	BizBuffer^ cuffBuffer;

	// TBD: Hide these arrays by making them unmanaged code
	static array<const float>^ _referenceRangeCoefficient1 =
	{
		(float) 0,
		(float) 0,
		(float) 0,
		(float) 0,
		(float) 0
	};
	static array<const float>^ _referenceRangeCoefficient2 =
	{
		(float) 0.2,
		(float) 0.2,
		(float) 0.2,
		(float) 0.2,
		(float) 0.2
	};
	static array<const float>^ _referenceRangeCoefficient3 =
	{
		(float) 0,
		(float) 0,
		(float) 0,
		(float) 0,
		(float) 0
	};
	
public:
	// Member functions:
	BizPWV(void);	

	// Validate PWV distance with respect to calculation method used
	bool ValidatePWVDistance();

	virtual bool StartCapture() override;
	virtual bool StopCapture() override;
	virtual void DispatchCaptureData() override;
	virtual bool SaveCaptureData() override; // save captured data as simulation file

	// Validate PWV class properties
	virtual bool Validate() override;
	
	// Initialise properties
	bool Initialise();

	// Keep raw (captured) PWV data from tonometer & cuff pulse in BLL internal circular buffers
	void Append(unsigned short tonometerData, unsigned short cuffPulseData);

	// Do all mathematics for this measurement
	bool Calculate();

	// Validate the PWV measurement before storing
	bool ValidateBeforeStore();

	// Validate Signal class properties
	bool ValidateSignals();

	// Store signals from the circular buffers into the PWV class
	bool CaptureSignals();

	// Store the PWV class into a database structure
	bool Store( CrxStructPWVMeasurementData^ record );
    
	// Populate the PWV class from a database structure
	bool Populate( CrxStructPWVMeasurementData^ record );
    
	// Increment the measurement counter by 1 in the firmware
	static bool IncrementMeasurementCounter();

	// Calculate and store a PWV report into a database record
	bool CalculatePWVReport( CrxStructPWVMeasurementData^ record );

	// Recalculate and store a PWV report into a database record
	bool RecalculatePWVReport( CrxStructPWVMeasurementData^ record );
private:
	// Set default values for calculated variables
	bool SetDefaults();

	// Calculate and validate distance
	bool CalculateAndValidateDistance();

	// Calculate quality control members
	bool CalculateQualityControls();
	
	// Calculate the BizDelta array between the femoral and carotid signals
	bool CalculateBizDeltaArray();

	// Calculate PWV, MeanDt, standardDeviation for this measurement
	bool CalculateFeatures();

	// Calculate the normalRange array
	void CalculateNormalRange();

	// Calculate the referenceRange array
	bool CalculateReferenceRange();

	// Handle quality indicator referesh timer event
	static void OnTimerQualityIndicatorEvents(Object^ sender, ElapsedEventArgs^ args);

protected:
	// Log current patient and measurement data
	virtual void LogSetupData() override;

};

END_BIZ_NAMESPACE
