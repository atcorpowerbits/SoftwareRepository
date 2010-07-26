#pragma once

#include <string>

using namespace System;

namespace BizLogicLayer {
	public ref class BizMeasurement
	{
	public:
		property String^        SystemId;
		property String^        GroupStudyId;

		property float          SP;          // systolic pressure entered by the operator
		property float          DP;          // diastolic pressure entered by the operator
		property float          MP;          // Mean pressure entered by operator

		property DateTime       MeasurementDateTime;    // date and time of measurement
		property int            DataRev;     // data revision number

		property String^        Medication;  // notes regarding medication for this patient
		property String^        Notes;       // miscellaneous notes for this measurement
		property String^    	OperatorId;    // Operator Id
		property String^        Interpretation;  // notes regarding clinical interpretation for this patient

		property float          Height;      // patient height in cm
		property float          Weight;      // patient weight in kg
		property float          Bmi;         // body mass index

		property float          Feet;        // patient height in ft
		property float          Inch;        // patient height in in
		property float          Pound;       // patient weight in lb

		property int            CaptureTime;

		property int            SampleRate;    // Rate of measurement in Htz.
	    
		property bool           Simulation; // Indicates a Simulated report

		property int            DefSampleRate; // Default sample rate

	public:
		BizMeasurement(void);

	};

	public ref class BizPWV : BizMeasurement
	{
	public:
		property int            CarotidDistance;
		property int            CuffDistance;
		property int            Femoral2CuffDistance;

	public:
		BizPWV(void);
	};
}