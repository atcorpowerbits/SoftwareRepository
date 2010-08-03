/*
    Copyright (C) ATCOR MEDICAL PTY LTD, 2010

    Filename	 :	measure.h
	
	Author       :  Victor Aung

    Description  :	DECLARATION of Business Logic Layer Mesurements
*/

#pragma once

using namespace System;

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

	public ref class BizHeight abstract
	{
	public:
		property unsigned int Height;
	public:
		virtual bool Validate() = 0;
		BizHeight(void) {};
	};
	public ref class BizHeightCm : BizHeight
	{
	public:
		BizHeightCm(void) {};
		virtual bool Validate() override;
	};
	public ref class BizHeightInch : BizHeight
	{
	public:
		BizHeightInch(void) {};
		virtual bool Validate() override;
	};
	public ref class BizWeight abstract
	{
	public:
		property unsigned int Weight;
	public:
		virtual bool Validate() = 0;
		BizWeight(void) {};
	};
	public ref class BizWeightKg : BizWeight
	{
	public:
		BizWeightKg(void) {};
		virtual bool Validate() override;
	};
	public ref class BizWeightLB : BizWeight
	{
	public:
		BizWeightLB(void) {};
		virtual bool Validate() override;
	};
	public ref class BizPressureReading abstract
	{
	public:
		property unsigned int Reading;
	public:
		virtual bool Validate();
		BizPressureReading(void) {};
	};
	public ref class BizSP : BizPressureReading
	{
	public:
		virtual bool Validate() override;
		BizSP(void){};
	};
	public ref class BizDP : BizPressureReading
	{
	public:
		virtual bool Validate() override;
		BizDP(void){};
	};
	public ref class BizMP : BizPressureReading
	{
	public:
		virtual bool Validate() override;
		BizMP(void){};
	};
	public ref class BizBloodPressure abstract
	{
	protected:
		BizSP^ SP;
		BizDP^ DP;
		BizMP^ MP;
	public:
		virtual bool Validate() = 0;
		BizBloodPressure(void) {};
	};
	public ref class BizSPAndDP : BizBloodPressure
	{
	public:
		BizSPAndDP(void) {};
		virtual bool Validate() override;
	};
	public ref class BizMPAndDP : BizBloodPressure
	{
	public:
		BizMPAndDP(void) {};
		virtual bool Validate() override;
	};
	public ref class BizSPAndMP : BizBloodPressure
	{
	public:
		BizSPAndMP(void) {};
		virtual bool Validate() override;
	};
	public ref class BizMeasure abstract
	{
	public:
		property String^        SystemId;
		property String^        GroupStudyId;

		property DateTime       MeasurementDateTime;    // date and time of measurement
		property unsigned short DataRev;     // data revision number

		BizBloodPressure^		myBP;        // patient blood pressure
		BizHeight^				myHeight;    // patient height 
		BizWeight^				myWeight;    // patient weight
		property float          Bmi;         // body mass index

		property String^        Medication;  // notes regarding medication for this patient
		property String^        Notes;       // miscellaneous notes for this measurement
		property String^    	OperatorId;  // Operator Id
		property String^        Interpretation;  // notes regarding clinical interpretation for this patient

		property unsigned short CaptureTime;
		property unsigned short SampleRate;    // Rate of measurement in Htz.
		property bool           Simulation; // Indicates a Simulated report
		property unsigned short DefSampleRate; // Default sample rate

		virtual bool Validate() = 0;

	public:
		BizMeasure(void);
	};
}