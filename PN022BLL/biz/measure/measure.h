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
protected:
	BizBloodPressure() {};
};
// Blood pressure measurement in SP & DP with validation
public ref class BizSPAndDP : BizBloodPressure
{
public:
	BizSPAndDP(void) { SP = gcnew BizSP; DP = gcnew BizDP; };
	virtual bool Validate() override;
};
// Blood pressure measurement in MP & DP with validation
public ref class BizMPAndDP : BizBloodPressure
{
public:
	BizMPAndDP(void) { DP = gcnew BizDP; MP = gcnew BizMP; };
	virtual bool Validate() override;
};
// Blood pressure measurement in SP & MP with validation
public ref class BizSPAndMP : BizBloodPressure
{
public:
	BizSPAndMP(void) { SP = gcnew BizSP; MP = gcnew BizMP; };
	virtual bool Validate() override;
};
// Abstract measurement
public ref class BizMeasure abstract
{
public:
	virtual bool StartCapture() { return false; };
	virtual bool StopCapture() { return false; };
	virtual void DispatchCaptureData() = 0;

	property BizBloodPressure^	bloodPressure;				// patient blood pressure
	//property BizHeight^		myHeight;				// patient height 
	//property BizWeight^		myWeight;				// patient weight
	property BizHeightAndWeight^	heightAndWeight;

	property String^			systemId;				// Customer System ID
	property String^			groupStudyId;			// User defined group/study
	property unsigned int		patientNumber;			// Internal patient number

	property DateTime			measurementDateTime;    // date and time of measurement
	property unsigned short		dataRevision;			// data revision number

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

protected:
	// Constructor
	BizMeasure(void);

	// Initialse the members of the measure class
	void Initialise();

};

END_BIZ_NAMESPACE
