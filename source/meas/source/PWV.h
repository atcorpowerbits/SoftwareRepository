/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
      Copyright (C) PWV MEDICAL PTY LTD, 1998

	    Filename 	  	:  TPWV.H
      Author        :  Sergei Eremenko
      Revision      :  1.00
      Date          :  25 May 99

  	  Description 	:	DECLARATION of TPWV Measurement Class
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
//---------------------------------------------------------------------------
#ifndef PWVH
#define PWVH
#include "Measure.h"
#include "PWVSite.h"
#include <cfr11\pubtype.h>
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// TPWV measurement Class
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
class TPWV : public /*private*/ TMeasure
{
  public:
    float    DistancePx;
    float    DistanceDt;
    float    Distance;           // anatomical distance (in mm) for calculation of pulse wave velocity
    float    DistanceError;      // pwv distance error in cm
    int      Algorithm;          // flags algorithm used to determine systolic onsets
    float    PHeightPercent;     // percentage of pulse height used to define pulse onsets for method "AlgorType1"

    // ECGGainType       ecg_gain;
    float    MeanDT;             // mean pulse onset time difference (in ms) between site A and site B pulse traces
    float    DeviationDT;        // standard deviation (in ms) of pulse onset time differences
    float    PWV;                // pulse wave velocity (in m/s)
    float    PWVError;           // pulse wave velocity error
    bool     hr_diff_ok;         // Indicate to operator whether heart rate difference between sites is acceptable.
    int      qc_scale;           //  Quality Control Pulse Height Divisor

    TPWVSite SiteA;
    TPWVSite SiteB;

    String           Reason;
    AUDIT_FLAG_TYPE  AuditFlag;
    TDateTime        AuditChange;

    int  Tonometer;

    // Constructors, destructors
    TPWV();

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
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
String GetCurrentPwvMeasureDetails();
#endif
