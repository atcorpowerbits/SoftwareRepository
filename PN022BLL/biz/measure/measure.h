/*
    Copyright (C) ATCOR MEDICAL PTY LTD, 2010

    Filename	 :	measure.h
	
	Author       :  Victor Aung

    Description  :	DECLARATION of Business Logic Layer Mesurements
*/

#pragma once

using namespace System;
using namespace DataAccess;

namespace Biz {

	const unsigned int MEA_HEIGHT_CM_MIN = 20;
	const unsigned int MEA_HEIGHT_CM_MAX= 220;
	const unsigned int MEA_HEIGHT_INCH_MIN = 12;
	const unsigned int MEA_HEIGHT_INCH_MAX = 100;
	const unsigned int MEA_WEIGHT_KG_MIN = 3;
	const unsigned int MEA_WEIGHT_KG_MAX = 227;
	const unsigned int MEA_WEIGHT_LB_MIN = 7;
	const unsigned int MEA_WEIGHT_LB_MAX = 500;
	const unsigned int MEA_BP_MIN = 30;
	const unsigned int MEA_BP_MAX = 250;
	const unsigned int MEA_SP2DP_DIFF_MIN = 10;
	const unsigned int MEA_MP2DP_DIFF_MIN = 5;
	const unsigned int MEA_SP2MP_DIFF_MIN = 5;

	// Audit flag types
	typedef enum
	{
	  AUDIT_ORIGINAL,
	  AUDIT_MODIFIED,
	  AUDIT_DELETED,
	  AUDIT_NOF_FLAGS
	} auditChangeType;

	// Abstract height with validation
	public ref class BizHeight abstract
	{
	public:
		property unsigned short Height;
	public:
		virtual bool Validate() = 0;
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
	public:
		virtual bool Validate() = 0;
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
		property unsigned int Reading;
	public:
		virtual bool Validate();
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
	protected:
		property BizSP^ SP;
		property BizDP^ DP;
		property BizMP^ MP;
	public:
		virtual bool Validate() = 0;
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
		virtual void DispatchCaptureData() {};

	protected:
		property String^        SystemId;
		property String^        GroupStudyId;
		property unsigned short PatientNo;				// patient number
    
		property DateTime       MeasurementDateTime;    // date and time of measurement
		property unsigned short DataRev;				// data revision number

		property BizBloodPressure^	myBP;				// patient blood pressure
		property BizHeight^		myHeight;				// patient height 
		property BizWeight^		myWeight;				// patient weight
		property float          Bmi;					// body mass index

		property String^        Medication;				// notes regarding medication for this patient
		property String^        Notes;					// miscellaneous notes for this measurement
		property String^    	OperatorId;				// Operator Id
		property String^        Interpretation;			// notes regarding clinical interpretation for this patient

		property unsigned short CaptureTime;
		property unsigned short SampleRate;				// Rate of measurement in Htz.
		property bool           Simulation;				// Indicates a Simulated report
		property unsigned short DefSampleRate;			// Default sample rate

		// CFR11 data members
		property String^        reasonForChange;		// Notes for changing this measurement
		property auditChangeType  auditChange;			// The type of change to this measurement
		property DateTime       auditDateTime;			// The date and time of the change to this measurement

		virtual bool Validate() = 0;

		// Constructors
		BizMeasure(void) {};
		void Initialise();
		
		// Validate measure class properties before storing in database
		bool ValidateBeforeStore();
	};
}