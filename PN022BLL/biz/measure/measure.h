/*
    Copyright (C) ATCOR MEDICAL PTY LTD, 2010

    Filename	 :	measure.h
	
	Author       :  Victor Aung

    Description  :	DECLARATION of Business Logic Layer Mesurements
*/

#pragma once

#include <biz.h>
#include <biz_constants.h>

using namespace System;
using namespace DAL_NAMESPACE;
using namespace CRX_DATABASE_MANAGER_NAMESPACE;

START_BIZ_NAMESPACE

// Abstract height with validation
public ref class BizHeightAndWeight
{
public:
	property unsigned short heightInCentimetres;
	property unsigned short heightInInches;
	property unsigned short weightInKilograms;
	property unsigned short weightInPounds;
	property float bodyMassIndex;			// body mass index
	
	BizHeightAndWeight();
	void Initialise();
	bool ValidateAndCalculate();
	
	// Store the BizHeightAndWeight class into a database structure
	bool Store( CrxStructPWVMeasurementData^ record );
    
	// Populate the BizHeightAndWeight class from a database structure
	bool Populate( CrxStructPWVMeasurementData^ record );
};

// Abstract height with validation
public ref class BizHeight abstract
{
public:
	property unsigned short Height;
	virtual bool Validate() = 0;
protected:
	BizHeight() {};
};
// Height in cm with validation
public ref class BizHeightCM : BizHeight
{
public:
	BizHeightCM(void) {};
	virtual bool Validate() override;
};
// Height in inches with validation
public ref class BizHeightInch : BizHeight
{
public:
	BizHeightInch(void) {};
	virtual bool Validate() override;
};
// Abstract weight with validation
public ref class BizWeight abstract
{
public:
	property unsigned int Weight;
	virtual bool Validate() = 0;
protected:
	BizWeight() {};
};
// Weight in kilograms with validation
public ref class BizWeightKG : BizWeight
{
public:
	BizWeightKG(void) {};
	virtual bool Validate() override;
};
// Weight in pounds with validation
public ref class BizWeightLB : BizWeight
{
public:
	BizWeightLB(void) {};
	virtual bool Validate() override;
};
// Abstract blood pressure reading with validation
public ref class BizPressureReading abstract
{
public:
	property unsigned short Reading;
	virtual bool Validate();
protected:
	BizPressureReading();
	void Initialise();
};
// Systolic blood pressure reading with validation
public ref class BizSP : BizPressureReading
{
public:
	virtual bool Validate() override;
	BizSP(void){};
};
// Diastolic blood pressure reading with validation
public ref class BizDP : BizPressureReading
{
public:
	virtual bool Validate() override;
	BizDP(void){};
};
// Mean blood pressure reading with validation
public ref class BizMP : BizPressureReading
{
public:
	virtual bool Validate() override;
	BizMP(void){};
};
// Abstract blood pressure measurement with validation
public ref class BizBloodPressure abstract
{
public:
	property BizSP^ SP;
	property BizDP^ DP;
	property BizMP^ MP;
	virtual bool Validate() = 0;

	// Store the BizBloodPressure class into a database structure
	bool Store( CrxStructPWVMeasurementData^ record );
    
	// Populate the BizBloodPressure class from a database structure
	bool Populate( CrxStructPWVMeasurementData^ record );
protected:
	// Always initialise the blood pressures to simplify storing and populating
	BizBloodPressure() { SP = gcnew BizSP; DP = gcnew BizDP; MP = gcnew BizMP; };
};
// Blood pressure measurement in SP & DP with validation
public ref class BizSPAndDP : BizBloodPressure
{
public:
	BizSPAndDP(void) {};
	virtual bool Validate() override;
};
// Blood pressure measurement in MP & DP with validation
public ref class BizMPAndDP : BizBloodPressure
{
public:
	BizMPAndDP(void) {};
	virtual bool Validate() override;
};
// Blood pressure measurement in SP & MP with validation
public ref class BizSPAndMP : BizBloodPressure
{
public:
	BizSPAndMP(void) {};
	virtual bool Validate() override;
};
// Abstract measurement
public ref class BizMeasure abstract
{
public:
	virtual bool StartCapture() { return false; };
	virtual bool StopCapture() { return false; };
	virtual void DispatchCaptureData() = 0;
	virtual bool SaveCaptureData() = 0;					// save captured data as simulation file

	property BizBloodPressure^	bloodPressure;			// patient blood pressure
	property unsigned short bloodPressureEntryOption;	// Blood pressure option selected when the object was calculated
	property String^ bloodPressureRangeTitle;			// Blood pressure category to be displayed

	property BizHeightAndWeight^ heightAndWeight;		// patient height, weight and BMI

	property unsigned int		systemId;				// Customer System ID
	property String^			groupStudyId;			// User defined group/study
	property unsigned int		patientNumber;			// Internal patient number

	property DateTime			measurementDateTime;    // date and time of measurement
	property unsigned short		dataRevision;			// data revision number
	property unsigned short		patientAge;

	property String^			medication;				// notes regarding medication for this patient
	property String^			notes;					// miscellaneous notes for this measurement
	property String^    		operatorId;				// Operator Id
	property String^			interpretation;			// notes regarding clinical interpretation for this patient

	property unsigned short		captureTime;			// Time used for report calculation
	property unsigned short		sampleRate;				// Rate of measurement in Hz.
	property bool				simulation;				// Indicates a Simulated report
	
	/* CFR11 data members
	property String^			reasonForChange;		// notes for changing this measurement
	property auditChangeType	auditChange;			// The type of change to this measurement
	property DateTime			auditDateTime;			// The date and time of the change to this measurement
	*/
	virtual bool Validate();

	// Store the Measure class into a database structure
	bool Store( CrxStructPWVMeasurementData^ record );
    
	// Populate the Measure class from a database structure
	bool Populate( CrxStructPWVMeasurementData^ record );
protected:
	property BloodPressureEnumeration bloodPressureRange;	// Blood pressure category
	
	// Constructor
	BizMeasure(void);

	// Initialse the members of the measure class
	void Initialise();

	// Log current patient and measurement data
	virtual void LogSetupData() {};

	// Calculate the patient's age on the date of the measurement
	bool CalculateAge();

	// Calculate the blood pressure range
	bool CalculateBloodPressureRange();
private:
	static array<String^>^ _bloodPressureRangeTitles =
	{
		"Optimal",
		"Normal",
		"High Normal",
		"Grade I",
		"Grade II & III"
	};
};

END_BIZ_NAMESPACE
