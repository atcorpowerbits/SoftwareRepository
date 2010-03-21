/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
      Copyright (C) PWV MEDICAL PTY LTD, 1998

	    Filename 	  	:  PWVSite.H
      Author        :  Sergei Eremenko
      Revision      :  1.00
      Date          :  21 Dec 98

  	  Description 	:	DECLARATION of TPWVSite Measurement Class
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
//---------------------------------------------------------------------------
#ifndef PWVSiteH
#define PWVSiteH

#include "PWVSignals.h"
#include <meas\pubtype.h>
#include <vcl\db.hpp>
//---------------------------------------------------------------------------
const int PWVSITE_MAX_PPOINTS = 30 * MEAS_DEFAULT_SAMPLE_RATE; // 30sec * SampleRate
const int PWV_MIN_SIGNAL_LENGTH = (PWV_SHORT_STUDY * MEAS_DEFAULT_SAMPLE_RATE); // 5 sec
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Base TPWVSite class
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
class TPWVSite
{
  friend class TPWV;
  public:
  // protected:
    PWV_MEASURE_TYPE  MeasureType;   // anatomical location (RADIAL,CAROTID,FEMORAL)
    int           NofDT;             // Actual number of DeltaT values
    int           NofValidDT;        // Actual number of valid DeltaT values
    int           Nof10s;            // (1,2,3) Actual number of 10s pulse sets

    float MeanDT;         // Mean pulse onset time difference
    float Deviation;      // Standard deviation of mean pulse onset time difference
    bool  deviation_ok;  // Indicate to operator whether quality satisfactory
    float HeartRate;     // Heart rate of the ECG (in bpm)

    TDelta        DeltaT[PWVSITE_MAX_ONSETS];  // Time difference

    TPWVTonomSignal Tonom; // (PWVSITE_MAX_PPOINTS, PWVSITE_MAX_ONSETS);
    TPWVECGSignal   ECG;   // (PWVSITE_MAX_PPOINTS, PWVSITE_MAX_ONSETS);

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
    bool ValidateBeforeCalculate();
};
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#endif
