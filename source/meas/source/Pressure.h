/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
      Copyright (C) PWV MEDICAL PTY LTD, 1998

	    Filename 	  	:  PWA.H
      Author        :  Sergei Eremenko
      Revision      :  1.00
      Date          :  25 Aug 98

  	  Description 	:	DECLARATION of TPWA Measurement Class
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
//---------------------------------------------------------------------------
#ifndef PressureH
#define PressureH
#include <vcl\db.hpp>

#include <meas/pubtype.h>
#include "PWAPulse.h"
#include "PWASignals.h"

//---------------------------------------------------------------------------
const int MAX_CAPTURE_TIME = 60; //60 for PWM, 9 for PWA
const int PRESSURE_PULSE_MAXLENGTH = 308;
const int PRESSURE_MAX_PPOINTS = MEAS_DEFAULT_SAMPLE_RATE * MAX_CAPTURE_TIME + PRESSURE_PULSE_MAXLENGTH;
const int PRESSURE_MAX_PULSES	= MAX_CAPTURE_TIME * MAX_HR / 60.;
const int PRESSURE_MAX_TPOINTS = PRESSURE_MAX_PULSES + 1;
const int EXPPULSE_MAX_EXPAND_FACTOR = 8; // Max factor (from 128 Htz to 1024 Htz)
const int PRESSURE_EXPPULSE_MAXLENGTH = PRESSURE_PULSE_MAXLENGTH * EXPPULSE_MAX_EXPAND_FACTOR;
const int PWA_MIN_PRESSURE_PULSE_HEIGHT = 10;
//---------------------------------------------------------------------------

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Abstract Base TPressure class
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
class TPressure: public TPWASignal
{
  friend class TPWA;
  friend class TPWM;
  public:
    int NofPulses;                              // Actual number of pulses
    TPulse Pulses[PRESSURE_MAX_PULSES];         // Whole signal pulses
    TPulse AvPulse;                             // Averaged pulse
    TPulse CalAvPulse;                          // Calibrated Average pulse

    TPWAPulse ExpPulse;                         // Expanded calibrated pulse
    TPulse Der1ExpPulse;                        // First derivative of expanded calibrated pulse
    TPulse Der2ExpPulse;                        // Second derivative of expanded calibrated pulse
    TPulse Der3ExpPulse;                        // Third derivative of expanded calibrated pulse

    float Sp;    // mmHg       Systolic Pressure
    float Dp;    // mmHg       Diastolic Pressure
    float MeanP; // mmHg       Mean Peripheral Pressure

    float T1;           // ms         User entered T1
    float T2;           // ms         User entered T2
    float AI1;          // Augmentation Index (type #1, old - saved on dbase)
    float CalcT1;       // ms         Time to 1st peak
    float CalcT2;       // ms         Time to 2nd peak

    float ED;        // ms         User entered ED
    float ESP;       // mmHg       End Systolic Pressure
    float CalcED;    // ms         Ejection Duration calculated by math engine

    // Non-database parameters
    float P1;    // Pressure at time T1
    float P2;    // Pressure at time T2
    float T1ED;  // T1/ED * 100%
    float T2ED;  // T2/ED * 100%

    // T1, T2, ED Qualities
    int QualityT1;
    int QualityT2;

  protected:
    // Constructors, destructors
    TPressure();
    ~TPressure();

    // Member functions:

    // Initialise properties
    void Initialise(const int pSignalSampleRate, const int pExpPulseSampleRate);

    // populate TPressure class properties from current record in pDataSet
    bool PopulateDBase (TDataSet* pDataSet, String pPrefix,
                        const int pSignalSampleRate,  const int pExpPulseSampleRate,
                        const int pDataRev);
    bool PopulateAccess(TDataSet* pDataSet, String pPrefix,
                        const int pSignalSampleRate, const int pExpPulseSampleRate,
                        const int pDataRev);

    // Store TPressure class properties to pDataSet
    bool StoreDBase(TDataSet* pDataSet, String pPrefix);
    bool StoreAccess(TDataSet* pDataSet, String pPrefix);

    // Export (print) measurement to string
    bool ExportPrintTitle(TDataSet* pDataSet, String pPrefix, String &pOut);
    bool Export(String &pOut);

    // virtual function to make pressure class abstract
    virtual bool PopulateDBase(TDataSet* pDataSet, const int pSampleRate,
                               const int pExpPulseSampleRate, const int pDataRev) = 0;

    // Validate pressure record before storing in Database
    bool ValidateBeforeStore();

    // Recalculate parameters depandant on pED
    bool RecalculateEDDependants(const int pEDIndex/*, const int pSampleRate*/);

  public:
    // Extract feature parameters (T1, T2, ED, ) from CalAvPulse
    bool ExtractFeatures(/*const int pSampleRate, */const int pED);
    // Set default values for calculated variables
    void SetDefaults(const int pSignalSampleRate, const int pExpPulseSampleRate);

    int SplineOrder; // Spline order to approximate Expanded pulse
    int SmoothOrder; // Smoothing order for calculate derivatives
    // int ExpandFactor;// Coefficient of expanding (in ExpandFactor times)
    int Divider;     // Factor to multiply on to store float CalAvPulse in database
  private:
    float Der1Step;  // Abscissa step to calculate Der1
    // Validate pressure class properties record
    bool ValidateBeforeRestorePulses();
    // Calculate trigger points
    bool CalculateTrigPts(const int pAlgorithm, const int pMinTrigPt);

    // Calibrate AveragePulse and find Min, Max
    bool CalibratePulse(const float pGain, const float pOffset, float &pMin, float &pMax);

    // Get Calibrate pulse from DB to calculate features
    // on the base of old stored CalPulse.
    // Need only to compare old and new math
    bool GetCalPulseFromDB (TDataSet* pDataSet, String pPrefix,
                            const int pSignalSampleRate,
                            const int pDataRev);

    // Find Average Pulse from Pulses
    bool AveragePulse(const int pLength, const int pTail, const int pSignalSampleRate);

    // Expand pPulse from 308 (pPulse.Length) to 1024 (ExpPulse.Length) points
    // with analitical calculation of expanded profile and its derivatives
    // using polinomial spline interpolation
    bool ExpandPulse(TPulse *pPulse, const int pExpandFactor);
    // Expand pPulse from 308 (pPulse.Length) to 1024 (ExpPulse.Length) points
    // with analitical calculation of expanded profile
    // using polinomial spline interpolation
    bool ExpandOnlyPulse(TPulse *pPulse, const int pExpandFactor);

    // Find systolic onset (trigger point) for a pulse,
    // line up (shift) pulse profile and derivatives to it and cut pulse tale
    bool SystolicOnset(const int pAlgorithm, const int pLengthOfRadial);

    // Get trigger points from populated TrigPts array and calculate their number
    bool GetTriggerPointsFromArray(const int pLength);

    // Validate pressure class properties record
    bool ValidateBeforeCalculate();

    // Calculate Pulses using trigger points
    bool CalcPulses(bool pRejectExtraPulses, const int pTail);

    // Find Trigger points for TPressure signal
    bool TriggerPoints();

    // Calculate specific non-database features
    bool NonDBaseFeatures(TPulse *pPulse/*, const int pSampleRate*/);
};
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Peripheral pressure class
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
class TPressurePeriph: public /*private*/ TPressure
{
  friend class TPWA;
  public:
    float MaxdPdt;     // mmHg/s  Maximum dP/dt
    float NoiseFactor; // Noise in Periph Signal
    float AGPH;      // AG/PH in %
    float PH;

    int QualityED;

    // Quality control parameters
    float QC_PulseHeightVariation;
    float QC_PulseLengthVariation;
    float QC_PulseHeight;
    float QC_DiastolicVariation;
    float QC_ShapeDeviation;
    float QC_Michael;
    int   qc_scale;
    int   OperatorIndex;

    // Constructors, destructors
    TPressurePeriph();

    // Member functions:

    // Initialise properties
    //void Initialise();
    void Initialise(const int pSignalSampleRate, const int pExpPulseSampleRate);
    // Set default values for calculated variables
    void SetDefaults(const int pNofPoints,
                     const int pSignalSampleRate, const int pExpPulseSampleRate);

    // Extract specific feature parameters for Periph TPressure
    bool ExtractFeatures(/*const int pSampleRate, */const int pED);

    // Populate class properties
    bool PopulateDBase(TDataSet* pDataSet, const int pSignalSampleRate,
                       const int pExpPulseSampleRate, const int pDataRev);
    bool PopulateAccess(TDataSet* pDataSet,
                        const int pSignalSampleRate, const int pExpPulseSampleRate,
                        const int pDataRev);

    // Store class properties to current record in pDataSet
    bool StoreDBase(TDataSet* pDataSet);
    bool StoreAccess(TDataSet* pDataSet);

    // Export (print) measurement to string
    bool ExportPrintTitle(TDataSet* pDataSet, String &pOut);
    bool Export(String &pOut);

   private:
   // Validate signal after Populate
    bool ValidateAfterPopulate();
    // Check negative signal
    bool ValidateBeforeStore();
    // Calculate specific non-database features
    bool NonDBaseFeatures(TPulse *pPulse/*, const int pSampleRate*/);

    // Calculate Quality Control parameters for TPressurePeriph Class
    bool QualityControl();

    // Calculate Operator Index from Peripheral wave
    void CalculateOperatorIndex(void);
};

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Central TPressure class
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
class TPressureCentral: /*private*/ public TPressure
{
  friend class TPWA;
  public:
	  float AP;          // mmHg       Augmented Pressure
     float AP_HR75;     // Augmentation Pressure normalised for HR 75
	  float MPS;         // mmHg       Mean Pressure Systole
	  float MPD;         // mmHg       Mean Pressure Diastole
	  float TTI;         // mmHg.s/min Tension Time Index
	  float DTI;         // mmHg.s/min Diastolic Time Index
	  float SVI;    		// SubEndocardial Viability = DTI/TTI
     float STI;         // Systolic Time Index
     float ATI;         // Augmentation Time Index
     float AL;          // Augmentation Load = STI/ATI

	  float Tr;          // ms         Time of reflected wave

    float HR;          // heart rate in bpm (beats per minute)
    float Period;      // Pulse period in miliseconds

    float DD;          // Diast duration
    float DDPeriod;    // % DD of Period
    float EDPeriod;    // % ED of Period
    float PH;          // Pulse Height  = SP - DP;
    float AGPH;        // AG/PH in %
    float AGPH_HR75;   // Augmentation Index normalised for HR 75
    float P1Height;    // P1 Height = P1 - DP;

    // Constructors, destructors
    TPressureCentral();

    // Member functions:

    // Initialise properties
    // void Initialise();
    void Initialise(const int pSignalSampleRate, const int pExpPulseSampleRate);

    // Set default values for calculated variables
    void SetDefaults(const int pNofPoints, const int pShift,
                     const int pSignalSampleRate, const int pExpPulseSampleRate);

    // Extract specific feature parameters (ED, HR, ...) for Cenral Pressure
    bool ExtractFeatures(/*const int pSampleRate, */const int pED);
    // Recalculate parameters depandant on pED
    bool RecalculateEDDependants(const int pEDIndex/*, const int pSampleRate*/);
    // Recalculate parameters depandant on pT1
    bool RecalculateT1Dependants(const int pT1Index);
    // Recalculate parameters depandant on pT2
    bool RecalculateT2Dependants(const int pT2Index);

    // Populate class properties
    bool PopulateDBase(TDataSet* pDataSet, const int pSignalSampleRate,
                       const int pExpPulseSampleRate, const int pDataRev);
    bool PopulateAccess(TDataSet* pDataSet,
                        const int pSignalSampleRate, const int pExpPulseSampleRate,
                        const int pDataRev);

    // Validate TPressureCentral class properties before storing in database
    bool ValidateBeforeStore();

    // Store class properties to current record in pDataSet
    bool StoreDBase(TDataSet* pDataSet);
    bool StoreAccess(TDataSet* pDataSet);

    // Export (print) measurement to string
    bool ExportPrintTitle(TDataSet* pDataSet, String &pOut);
    bool Export(String &pOut);
  private:
    // Calculate specific non-database features for Cenral Pressure
    bool NonDBaseFeatures(TPulse *pPulse/*, const int pSampleRate*/);
};
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#endif
