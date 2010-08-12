/*
    Copyright (C) ATCOR MEDICAL PTY LTD, 2010

    Filename	 :	measure_pwv.h
	
	Author       :  Victor Aung

    Description  :	DECLARATION of Business Logic Layer PWV Measurement
*/

#pragma once

//#include <string>
#include "measure.h"

using namespace System;
using namespace DataAccess;

namespace Biz {

	const unsigned short PWV_DISTANCE_MIN = 10;
	const unsigned short PWV_DISTANCE_MAX = 2200;
	const unsigned short PWV_FEM2CUFF_MIN = 10;
	const unsigned short PWV_FEM2CUFF_MAX = 700;
	const unsigned short PWV_MAX_ONSETS = 30 * 3;

	//---------------------------------------------------------------------------
	// Pulse Wave Velocity data structure
	//---------------------------------------------------------------------------
	typedef struct
	{
		float value;	// Pulse wave velocity (in m/s)
		bool isValid;	// Pulse wave velocity is valid/invalid
	} BizDelta;

	public ref class BizDistance abstract
	{
	public:
		property unsigned short Distance;
	};
	public ref class BizPWV : BizMeasure
	{
	public:
		property unsigned short CarotidDistance;
		property unsigned short CuffDistance;
		property unsigned short Femoral2CuffDistance;
		property unsigned short PWVDistance;

		bool ValidatePWVDistance();
		bool ValidateFemoral2CuffDistance();
		virtual bool Validate() override;

		BizPWV(void);
		virtual bool StartCapture() override;
	private:
		DalTonoData^ tonoDataRaw; // to observe Tonometer raw data
		void UpdateTonometerData(Object^ sender, DalTonoDataEventArgs^ e);

	public:
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

		//BizSignal^ signalA; // (PWVSITE_MAX_PPOINTS, PWVSITE_MAX_ONSETS);
		//BizSignal^ signalB;   // (PWVSITE_MAX_PPOINTS, PWVSITE_MAX_ONSETS);
/*
    // Member functions:

    // Initialise properties
    void Initialise();

    // Populate class properties from current record in pDataSet
    bool Populate(TDataSet* pDataSet);
    bool PopulateDBase(TDataSet* pDataSet);
    bool PopulateAccess(TDataSet* pDataSet);

    // Store class properties to current record in pDataSet
    bool Store(TDataSet* pDataSet, const bool pRewriteKeyFields = true, const bool pRewriteDate = true);
    bool StoreDBase(TDataSet* pDataSet, const bool pRewriteKeyFields = true, const bool pRewriteDate = true);
    bool StoreAccess(TDataSet* pDataSet, const bool pRewriteKeyFields = true, const bool pRewriteDate = true);

    // Export (print) measurement to string
    bool ExportPrintTitle(TDataSet* pDataSet, String &pOut);
    bool Export(String &pOut);
    bool ExportArrays(int pFileHandle);

    // Do all mathematics for this measurement
    bool Calculate();

    // Set ReadyToCapture property to true
    void PrepareToCaptureSignal();
    
    // Validate TPWV class properties before Calculation routine
    bool ValidateBeforeCalculate();
    
    // Save arrays if an error occurs while calculating
    bool SaveToFile();
    
private:
    // bool ReadyToCapture; // Is ready to store signal?
    // Set default values for calculated variables
    void SetDefaults();
    // Calculate distances
    bool CalculateDistance();
    // Validate TPWV class properties before Store in database
    bool ValidateBeforeStore();
    // Calculate PWV, MeanDt, Deviation for this measurement
    bool CalcMainFeatures();
	};

	

  protected:

    // Constructors, destructors
    TPWVSite();
    ~TPWVSite();

    // Member functions:

    // Initialise properties
    void Initialise(const int pSignalSampleRate);

    // populate TPWVSite class properties from current record in pDataSet
    bool PopulateDBase(TDataSet* pDataSet, const String pPrefix, const int pSampleRate);
    bool PopulateAccess(TDataSet* pDataSet, const String pPrefix);

    // Validate pressure record before storing in Database
    bool ValidateBeforeStore();

    // Store TPWVSite class properties to pDataSet
    bool StoreDBase(TDataSet* pDataSet, const String pPrefix);
    bool StoreAccess(TDataSet* pDataSet, const String pPrefix);

    // Export (print) measurement to string
    bool ExportPrintTitle(TDataSet* pDataSet, const String pPrefix, String &pOut);
    bool Export(String &pOut);

  public:
  // protected:
    // Set default values for calculated variables
    void SetDefaults(const int pSignalSampleRate);

    // Do all mathematics for this measurement
    bool Calculate(const int pAlgorithm,
                   const float pHeightPercent,
                   const int pSampleRate,
                   const int p_qc_scalefactor);

  private:

    // Work array to mark rejected Onsets
    short int RejectedOnsets[PWVSITE_MAX_ONSETS];
    // Validate pressure class properties record
    //bool ValidateBeforeRestorePulses();
    // Calculate time difference between Tonom and ECG Onsets
    bool CalcDeltaT(const int pSampleRate);
    // Calculate Heart rate on the base of ECG Onsets
    bool CalcHeartRate(const int pSampleRate);
    // Calculate DeltaT average (MeanDt) and its standard deviation
    bool MeanDeviation();
    // Validate pressure class properties record
    bool ValidateBeforeCalculate();*/
	};
}