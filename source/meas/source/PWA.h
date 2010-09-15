/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
      Copyright (C) PWV MEDICAL PTY LTD, 1998

	    Filename 	  	:  TPWA.H
      Author        :  Sergei Eremenko
      Revision      :  1.00
      Date          :  25 Aug 98

  	  Description 	:	DECLARATION of TPWA Measurement Class
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
//---------------------------------------------------------------------------
#ifndef PWAH
#define PWAH
#include "Measure.h"
#include "Pressure.h"
#include "AVI.h"
#include <meas\pubtype.h>
#include <cfr11\pubtype.h>
//---------------------------------------------------------------------------
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// TPWA (tonometry) measurement Class
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
class TPWA : public /*private*/ TMeasure
{
  friend class TPWM;
  public:
    PWA_MEASURE_TYPE  MeasureType;   // anatomical location (RADIAL,CAROTID,FEMORAL)
    int  SystolicOnsetAlgorithm;
    int  Tonometer;

    int  SignalUpSampleRate;          // Signal UpSampleRate from hardware level (1)
    int  ExpPulseUpSampleRate;        // ExpPulse UpSampleRate from hardware level (8)

    // float    CardiacOutput;
    // float    Flow;
    float            ReferenceAge;
    int              ReferenceScore;
    float            AmplificationRatio;
    bool             CalcIsInconclusive;
    AnsiString       InconclusiveNote;
    float            T1Ratio;
    String           CaptureTime;

    TPressurePeriph  Periph;   // Peripheral pressure results
    TPressureCentral Central;  // Central pressure results

    TAVI    *avi; // AVI class

    String           Reason;
    AUDIT_FLAG_TYPE  AuditFlag;
    TDateTime        AuditChange;

    // Constructors, destructors
    TPWA();

    // Member functions:

    // Initialise properties
    void Initialise();

    // Populate class properties from current record in pDataSet
    bool Populate(TDataSet* pDataSet);
    bool PopulateDBase(TDataSet* pDataSet);
    bool PopulateAccess(TDataSet* pDataSet);

    // Store class properties to current record in pDataSet
    bool Store(TDataSet* pDataSet, bool pRewriteKeyFields = true, bool pRewriteDate = true);
    bool StoreDBase(TDataSet* pDataSet, bool pRewriteKeyFields = true, bool pRewriteDate = true);
    bool StoreAccess(TDataSet* pDataSet, bool pRewriteKeyFields = true, bool pRewriteDate = true);

    // Export (print) measurement to string
    bool ExportPrintTitle(TDataSet* pDataSet, String &pOut);
    bool Export(String &pOut, const int pSessionID = 0);
    bool ExportArrays(int pFileHandle);

    // Validate TPWA class properties before Calculation routine
    bool ValidateBeforeCalculate();
    // Do all mathematics for this measurement
    bool Calculate(const float pCalibrationFactor = 0.);
    // Do all mathematics for a single pulse
    bool CalculateSinglePulse(const float pCalibrationFactor = 0.);
    // Do all mathematics for this measurement with replacement CalAvPulse from DB
    bool CalculateFeaturesFromDB(TDataSet* pDataSet);
    // Recalculate parameters depandant on pED
    bool RecalculateEDDependants(const int pEDIndex);
    // Recalculate parameters depandant on pT1
    bool RecalculateT1Dependants(const int pT1Index);
    // Recalculate parameters depandant on pT2
    bool RecalculateT2Dependants(const int pT2Index);
    // Check whether ED is in valid window
    bool CheckEDLimitations(const int pEDIndex, bool &pLeft, bool &pRight);
    // Check whether T1 is in valid window
    bool CheckT1Limitations(const int pT1Index, bool &pLeft, bool &pRight);
    // Check whether T2 is in valid window
    bool CheckT2Limitations(const int pT2Index, bool &pLeft, bool &pRight);

    // Set ReadyToCapture property to true
    void PrepareToCaptureSignal();

    // Save arrays if an error occurs while calculating
    bool SaveToFile();
/*
    // Store signal packet from tonometer in PressurePeriph class
    bool CaptureSignalPacket(const short int *pInput, const int pLength);
    // Store whole signal from tonometer in PressurePeriph class
    bool CaptureSignal(const short int *pInput, const int pLength);
*/
  private:
    // bool ReadyToCapture; // Is ready to store signal ?

    // Validate TPWA class properties before Store in database
    bool ValidateBeforeStore();

    // Convert Peripheral Signal To Central
    bool PeriphToCentral();
    // Convert Peripheral Signal To Central using convolution
    bool Convolution(const float *pTfc, const int pNofTFC);

    // Compare Periph and Central trigger points and Reject irregulars
    bool RejectIrregularTrigPts();

    // Assign trigger points for central with accounting
    // 16 points shift between Central and Radial
    bool AssignCentralTrigPts();

    // Calibration AvPulses for Periph and Central together
    bool CalibrateAvPulses(const float pGain = 0., const float pOffset = 0.);

    // Find T1, T2, ED for Periph and Central, Set Central.ED = Periph.ED
    //  and Extract features
    bool ExtractFeatures(/*int pSampleRate*/);

    // Recalculate weak or very weak values of T1 or T2
    bool FineTuneT1T2();
};
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#endif
