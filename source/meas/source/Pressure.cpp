//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include <stdlib.h>
#include <meas\pubserv.h>
#include <msg\pubserv.h>
#include "Pressure.h"
#include "Mathem.h"
#include "math.h"


//---------------------------------------------------------------------------
#pragma package(smart_init)
const float PWA_MIN_VALID_PULSELENGTH_PERCENT = 0.60;
const float PWA_MAX_VALID_PULSELENGTH_PERCENT = 1.50;
const int   PWA_MIN_SIGNAL_LENGTH = 300;
const float PRESSURE_PULSE_MINLENGTH = 60.* (float)(MEAS_DEFAULT_SAMPLE_RATE) / MAX_HR;

// ###########################################################################
// Constructor and Destructor for TPressure Class
//---------------------------------------------------------------------------
TPressure::TPressure()
  : TPWASignal(PRESSURE_MAX_PPOINTS, PRESSURE_MAX_TPOINTS)
{
  // Allocate workspace to store AvPulse, CalAvPulse and ExpPulses
  AvPulse.Allocate(PRESSURE_PULSE_MAXLENGTH);
  CalAvPulse.Allocate(PRESSURE_PULSE_MAXLENGTH);
  ExpPulse.Allocate(PRESSURE_EXPPULSE_MAXLENGTH);
  Der1ExpPulse.Allocate(PRESSURE_EXPPULSE_MAXLENGTH);
  Der2ExpPulse.Allocate(PRESSURE_EXPPULSE_MAXLENGTH);
  Der3ExpPulse.Allocate(PRESSURE_EXPPULSE_MAXLENGTH);
  for (int np=0; np<PRESSURE_MAX_PULSES; np++)
  {
    Pulses[np].SetMaxSize(PRESSURE_PULSE_MAXLENGTH);
  }
  // Initialise
  Initialise(0,0);
}
//---------------------------------------------------------------------------
TPressure::~TPressure()
{
  AvPulse.Free();
  CalAvPulse.Free();
  ExpPulse.Free();
  Der1ExpPulse.Free();
  Der2ExpPulse.Free();
  Der3ExpPulse.Free();
}
//---------------------------------------------------------------------------
// Class initialisator
//---------------------------------------------------------------------------
void TPressure::Initialise(const int pSignalSampleRate, const int pExpPulseSampleRate)
{
  SetDefaults(pSignalSampleRate, pExpPulseSampleRate);
  // NofPoints = 0;
  NofPoints = PRESSURE_MAX_PPOINTS;
  SplineOrder = 3;  // Cubic splines - optimal
  SmoothOrder = 3;  // Optimal smooth order formula
  // ExpandFactor = EXPPULSE_MAX_EXPAND_FACTOR; // Maximum possible

  // Factor to multiply on to store float CalAvPulse in database
  Divider = 100;
  Der1Step = 1./10;

  // Arrays initialisation
  for (int i = 0; i < PRESSURE_MAX_PPOINTS; i++)
  {
    Signal[i] = 0;
    Der1[i] = 0.0;
    Der2[i] = 0.0;
  }
}
//---------------------------------------------------------------------------
// Set default values for calculated variables
//---------------------------------------------------------------------------
void TPressure::SetDefaults(const int pSignalSampleRate, const int pExpPulseSampleRate)
{
    // Variables initialisation
    Sp = DEFAULT_VALUE;
    Dp = DEFAULT_VALUE;
    MeanP = DEFAULT_VALUE;

    T1 = DEFAULT_VALUE;
    T2 = DEFAULT_VALUE;
    AI1 = DEFAULT_VALUE;
    CalcT1 = DEFAULT_VALUE;
    CalcT2 = DEFAULT_VALUE;

    T1ED = DEFAULT_VALUE;
    T2ED = DEFAULT_VALUE;
    P1 = DEFAULT_VALUE;
    P2 = DEFAULT_VALUE;
    QualityT1 = DEFAULT_VALUE;
    QualityT2 = DEFAULT_VALUE;

    ED = DEFAULT_VALUE;
    ESP = DEFAULT_VALUE;
    CalcED = DEFAULT_VALUE;

    NofPulses = 0;
    NofOnsets = 0;

    SampleRate = (short int) pSignalSampleRate;

    // Trigger points = -1
    for (int i = 0; i < PRESSURE_MAX_TPOINTS; TrigPts[i++] = -1);

    // Pulses initialisation
    AvPulse.Initialise(pSignalSampleRate);
    CalAvPulse.Initialise(pSignalSampleRate);
    ExpPulse.Initialise(pExpPulseSampleRate);
    Der1ExpPulse.Initialise(pExpPulseSampleRate);
    Der2ExpPulse.Initialise(pExpPulseSampleRate);
    Der3ExpPulse.Initialise(pExpPulseSampleRate);
}

/* ###########################################################################
 ** PopulateDBase()
 **
 ** DESCRIPTION
 **  populate class properties from current record in pDataSet
 ** INPUT
 **  pDataSet - TADOQuery or TADOTable
 **  const int pSampleRate - Sample Rate
 **  const int pDataRev - DataRevisionNumber from Database
 ** OUTPUT
 **  boolean success or not
*/
//---------------------------------------------------------------------------
bool TPressure::PopulateDBase(TDataSet* pDataSet, String pPrefix,
                const int pSignalSampleRate,  const int pExpPulseSampleRate,
                const int pDataRev)
{
  // SetDefaults();
  if (pDataSet->RecordCount <= 0 || pExpPulseSampleRate < pSignalSampleRate)
    return false;
  int lExpandFactor = pExpPulseSampleRate/pSignalSampleRate;

  try
  {
    // Populate variables
    Sp    = pDataSet->FieldByName(pPrefix + MPWA_NO_SP)->AsInteger;
    Dp    = pDataSet->FieldByName(pPrefix + MPWA_NO_DP)->AsInteger;
    MeanP = pDataSet->FieldByName(pPrefix + MPWA_NO_MEANP)->AsInteger;
    T1    = pDataSet->FieldByName(pPrefix + MPWA_NO_T1)->AsInteger;
    T2    = pDataSet->FieldByName(pPrefix + MPWA_NO_T2)->AsInteger;
    AI1   = pDataSet->FieldByName(pPrefix + MPWA_NO_AI)->AsInteger;

    ED    = pDataSet->FieldByName(MPWA_ED)->AsInteger;
    CalcED = ED;

    int NofBytes;

    // PickUp Arrays
    if (TPWASignal::Populate(pDataSet, pPrefix + MPWA_NO_PULSES, pPrefix + MPWA_NO_TRIGS)==false)
      return false;
    // Prevent -1 at the end for Dbase  
    SampleRate = (short int) pSignalSampleRate;
    // Validate signal
    if (TPWASignal::ValidateSignal(PWA_MIN_SIGNAL_LENGTH)==false)
      return false;

    // Calibrated average pulse
    NofBytes = min((int)(pDataSet->FieldByName(pPrefix + MPWA_NO_AV)->AsString.Length()),
              (int)(PRESSURE_PULSE_MAXLENGTH * sizeof (short int)));
    if (CalAvPulse.ExtractFromBuffer(pDataSet->FieldByName(pPrefix + MPWA_NO_AV)->AsString.c_str(),
              (short int) NofBytes, Divider)==false)
      return false;
    CalAvPulse.SampleRate = (short int) pSignalSampleRate;

    // Expand Calibrated average pulse
    if (ExpandOnlyPulse(&CalAvPulse, lExpandFactor)==false)
      return false;

    // if (ExpPulse.Smooth(16)==false)
    //  return false;
    Der1ExpPulse.Initialise();
    Der2ExpPulse.Initialise();
    Der3ExpPulse.Initialise();
  }
  catch (Exception &exception)
  {
    MsgBox(TERROR, GetCurrentPwaMeasureDetails(), MSG_DBREADWRITE_ERROR, MSG_ERR_READDB,
           LoadStr(MSG_ERR_READDB) +exception.Message);
    return false;
  }

  // Restore Pulses and calculate AvPulse for populated pressure
  NofPulses = 0;
  int TrgPtsArraySize = NofOnsets;

  // Extract database trigger points
  if (GetTriggerPointsFromArray(TrgPtsArraySize)==false)
    return false;

  // Validate before Restore signal
  if (ValidateBeforeRestorePulses()==false)
    return false;

  // Calculate pulses using Trigger Points
  // without rejection extra short and long pulses
  if (CalcPulses(false, 0)==false)
  {
    MsgBox_show(TWARNING,
                MSG_MATH_ERROR,
                LoadStr(MSG_CALCPULSES_ERR) +GetCurrentPwaMeasureDetails(),
                MSG_CALCPULSES_ERR, "");
    // return false;
  }

  // Calculate Raw Average Pulse
  if (AveragePulse(0,0,pSignalSampleRate)==false)
  {
    MsgBox_show(TWARNING,
                MSG_MATH_ERROR,
                LoadStr(MSG_AVPULSE_ERR) +"\n\n" +GetCurrentPwaMeasureDetails(),
                MSG_AVPULSE_ERR, "");
    //return false;
  }

  // Calculate specific non-database features
  if (NonDBaseFeatures(&CalAvPulse/*, pSampleRate*/)==false)
    return false;

  return true;
}
//---------------------------------------------------------------------------
bool TPressure::PopulateAccess(TDataSet* pDataSet, String pPrefix,
                const int pSignalSampleRate, const int pExpPulseSampleRate,
                const int pDataRev)
{
  // SetDefaults();
  if (pDataSet->RecordCount <= 0 || pExpPulseSampleRate < pSignalSampleRate)
    return false;
  int lExpandFactor = pExpPulseSampleRate/pSignalSampleRate;

  try
  {
    // Populate variables
    Sp    = pDataSet->FieldByName(pPrefix + MPWA_NO_SP)->AsFloat;
    Dp    = pDataSet->FieldByName(pPrefix + MPWA_NO_DP)->AsFloat;
    MeanP = pDataSet->FieldByName(pPrefix + MPWA_NO_MEANP)->AsFloat;
    T1    = pDataSet->FieldByName(pPrefix + MPWA_NO_T1)->AsFloat;
    T2    = pDataSet->FieldByName(pPrefix + MPWA_NO_T2)->AsFloat;
    AI1   = pDataSet->FieldByName(pPrefix + MPWA_NO_AI)->AsFloat;
    CalcT1 = pDataSet->FieldByName(pPrefix + MPWA_NO_CALCT1)->AsFloat;
    CalcT2 = pDataSet->FieldByName(pPrefix + MPWA_NO_CALCT2)->AsFloat;
    // If CalcT1 or CalcT2 have not been stored before, set them to T1 and T2
    // CalcT1 and CalcT2 are new to Version 8.1
    if (CalcT1 == 0)
    {
      CalcT1 = T1;
    }
    if (CalcT2 == 0)
    {
      CalcT2 = T2;
    }

    ED    = pDataSet->FieldByName(MPWA_ED)->AsFloat;
    ESP   = pDataSet->FieldByName(pPrefix + MPWA_NO_ESP)->AsFloat;
    // If there is no field CalcED in DB, set it = ED
    CalcED = (pDataSet->FindField(MPWA_CALC_ED) != NULL ?
              pDataSet->FieldByName(MPWA_CALC_ED)->AsFloat : ED);

    // Additional for MSAccess
    P1    = pDataSet->FieldByName(pPrefix + MPWA_NO_P1)->AsFloat;
    P2    = pDataSet->FieldByName(pPrefix + MPWA_NO_P2)->AsFloat;
    T1ED  = pDataSet->FieldByName(pPrefix + MPWA_NO_T1ED)->AsFloat;
    T2ED  = pDataSet->FieldByName(pPrefix + MPWA_NO_T2ED)->AsFloat;

    QualityT1 = pDataSet->FieldByName(pPrefix + MPWA_NO_QT1)->AsInteger;
    QualityT2 = pDataSet->FieldByName(pPrefix + MPWA_NO_QT2)->AsInteger;

    // PickUp Arrays
    int NofBytes;

    // PickUp Arrays
    if (TPWASignal::Populate(pDataSet, pPrefix + MPWA_NO_PULSES, pPrefix + MPWA_NO_TRIGS)==false)
      return false;
    SampleRate = (short int) pSignalSampleRate;

    // UnCalibrated average pulse
    NofBytes = min((int)(pDataSet->FieldByName(pPrefix + MPWA_NO_UNCAL_AV)->AsString.Length()), (int)(PRESSURE_PULSE_MAXLENGTH * sizeof (short int)));
    if (AvPulse.ExtractFromBuffer(pDataSet->FieldByName(pPrefix + MPWA_NO_UNCAL_AV)->AsString.c_str(), (short int) NofBytes, 1)==false)
      return false;
    AvPulse.SampleRate = (short int) pSignalSampleRate;

    // Calibrated average pulse
    if (pDataSet->FindField(pPrefix + MPWA_NO_AV) != NULL)
    {
      NofBytes = min((int)(pDataSet->FieldByName(pPrefix + MPWA_NO_AV)->AsString.Length()),
                (int)(PRESSURE_PULSE_MAXLENGTH * sizeof (short int)));
      if (NofBytes > 0)
      {
        if (CalAvPulse.ExtractFromBuffer(pDataSet->FieldByName(pPrefix + MPWA_NO_AV)->AsString.c_str(),
                  (short int) NofBytes, Divider)==false)
          return false;
        CalAvPulse.SampleRate = (short int) pSignalSampleRate;

        // Expand Calibrated average pulse
        if (ExpandOnlyPulse(&CalAvPulse, lExpandFactor)==false)
          return false;
      }
    }
    else if (pDataSet->FindField(pPrefix + MPWA_NO_EXPPULSE) != NULL)
    { // Expanded pulse in database
      NofBytes = min((int)(pDataSet->FieldByName(pPrefix + MPWA_NO_EXPPULSE)->AsString.Length()),
                     (int)(PRESSURE_EXPPULSE_MAXLENGTH * sizeof (float)));
      if (NofBytes > 0)
      {
        ExpPulse.Initialise();
        if (ExpPulse.ExtractFromBuffer(pDataSet->FieldByName(pPrefix + MPWA_NO_EXPPULSE)->AsString.c_str(),
                     (short int) NofBytes, 1, sizeof(float))==false)
        return false;
        ExpPulse.SampleRate = (short int) pExpPulseSampleRate;

        // calculate Calibrated average pulse
        if (CalAvPulse.DownSample(&ExpPulse, lExpandFactor)==false)
          return false;
      }
    }

    // if (ExpPulse.Smooth()==false)
    //  return false;
    Der1ExpPulse.Initialise();
    Der2ExpPulse.Initialise();
    Der3ExpPulse.Initialise();
  }
  catch (Exception &exception)
  {
    MsgBox(TERROR, GetCurrentPwaMeasureDetails(), MSG_DBREADWRITE_ERROR, MSG_ERR_READDB,
           LoadStr(MSG_ERR_READDB) +exception.Message);
    return false;
  }

  // Restore Pulses and calculate AvPulse for populated pressure
  NofPulses = 0;
  int TrgPtsArraySize = NofOnsets;

  // Extract database trigger points
  if (GetTriggerPointsFromArray(TrgPtsArraySize)==false)
    return false;

  // Validate before Restore signal
  if (ValidateBeforeRestorePulses()==false)
    return false;

  // Calculate pulses using Trigger Points
  // with rejection extra short and long pulses (in DBASE no rejection!)
  if (CalcPulses(true, 0)==false)
  {
    MsgBox_show(TERROR,
                MSG_MATH_ERROR,
                LoadStr(MSG_CALCPULSES_ERR),
                MSG_CALCPULSES_ERR,
                LoadStr(MSG_CALCPULSES_ERR) +GetCurrentPwaMeasureDetails());
    return false;
  }

  return true;
}

//--------------------------------------------------------------------------------
bool TPressure::ExportPrintTitle(TDataSet* pDataSet, String pPrefix, String &pOut)
{
  // Actual printing title string
  try
  {
    // Export specific properties
    pOut = pOut + pDataSet->FieldByName(pPrefix + MPWA_NO_SP)->DisplayName + "\t";
    pOut = pOut + pDataSet->FieldByName(pPrefix + MPWA_NO_DP)->DisplayName + "\t";
    pOut = pOut + pDataSet->FieldByName(pPrefix + MPWA_NO_MEANP)->DisplayName + "\t";
    pOut = pOut + pDataSet->FieldByName(pPrefix + MPWA_NO_T1)->DisplayName + "\t";
    pOut = pOut + pDataSet->FieldByName(pPrefix + MPWA_NO_T2)->DisplayName + "\t";
    pOut = pOut + pDataSet->FieldByName(pPrefix + MPWA_NO_AI)->DisplayName + "\t";
    pOut = pOut + pPrefix + "CalcT1" + "\t";
    pOut = pOut + pPrefix + "CalcT2" + "\t";

    pOut = pOut + pDataSet->FieldByName(pPrefix + MPWA_NO_ESP)->DisplayName + "\t";

    // Additional for MSAccess
    pOut = pOut + pDataSet->FieldByName(pPrefix + MPWA_NO_P1)->DisplayName + "\t";
    pOut = pOut + pDataSet->FieldByName(pPrefix + MPWA_NO_P2)->DisplayName + "\t";
    pOut = pOut + pDataSet->FieldByName(pPrefix + MPWA_NO_T1ED)->DisplayName + "\t";
    pOut = pOut + pDataSet->FieldByName(pPrefix + MPWA_NO_T2ED)->DisplayName + "\t";

    pOut = pOut + pDataSet->FieldByName(pPrefix + MPWA_NO_QT1)->DisplayName + "\t";
    pOut = pOut + pDataSet->FieldByName(pPrefix + MPWA_NO_QT2)->DisplayName + "\t";
  }
  catch (Exception &exception)
  {
    MsgBox(TERROR, GetCurrentPwaMeasureDetails(), MSG_EXCEPTION, MSG_EXPORT_ERROR, LoadStr(MSG_EXPORT_ERROR) + exception.Message);
    return false;
  }
  // return at success
  return true;
}

//------------------------------------------------------------
bool TPressure::Export(String &pOut)
{
  // Export specific properties
  pOut = pOut + RoundIntToStr(Sp) + "\t";
  pOut = pOut + RoundIntToStr(Dp) + "\t";
  pOut = pOut + RoundIntToStr(MeanP) + "\t";
  pOut = pOut + RoundIntToStr(T1) + "\t";
  pOut = pOut + RoundIntToStr(T2) + "\t";
  pOut = pOut + RoundIntToStr(AI1) + "\t";
  pOut = pOut + RoundIntToStr(CalcT1) + "\t";
  pOut = pOut + RoundIntToStr(CalcT2) + "\t";

  pOut = pOut + RoundIntToStr(ESP) + "\t";

  // Additional for MSAccess
  pOut = pOut + RoundIntToStr(P1) + "\t";
  pOut = pOut + RoundIntToStr(P2) + "\t";
  pOut = pOut + RoundIntToStr(T1ED) + "\t";
  pOut = pOut + RoundIntToStr(T2ED) + "\t";

  pOut = pOut + IntToStr(QualityT1) + "\t";
  pOut = pOut + IntToStr(QualityT2) + "\t";

  // return at success
  return true;
}
/* ###########################################################################
 ** ValidateBeforeRestorePulses()
 **
 ** DESCRIPTION
 **  Validate TPressure class properties before restore Pulses and AvPulse
 **  from Signal array
 ** INPUT
 **  // const int pSampleRate - Sample Rate
 ** OUTPUT
 ** RETURN
 **  boolean success or not
*/
//---------------------------------------------------------------------------
bool TPressure::ValidateBeforeRestorePulses()
{
  // Check signal too short
  if (NofPoints < PRESSURE_PULSE_MAXLENGTH)
  {
    MsgBox(TERROR, GetCurrentMeasureDetails(), MSG_VALIDATION_ERROR, MSG_SIGNAL_TOO_SHORT);
    return false;
  }
  // Trigger points validation
  if (NofOnsets <= 2)
  {
    MsgBox(TERROR, GetCurrentMeasureDetails(), MSG_DBREADWRITE_ERROR, MSG_TRIGGER_ERRDB);
    return false;
  }
  // Success
  return true;
}

/* ###########################################################################
 ** StoreDBase()
 **
 ** DESCRIPTION
 **  Store TPressure class properties to pDataSet
 ** INPUT
 **  pDataSet - TADOQuery or TADOTable
 **  const int pSampleRate - Sample Rate
 ** OUTPUT
 **  boolean success or not
*/
//---------------------------------------------------------------------------
bool TPressure::StoreDBase (TDataSet* pDataSet, String pPrefix)
{
  try
  {
    // Store variables
    pDataSet->FieldByName(pPrefix + MPWA_NO_SP)->AsInteger = Sp;
    pDataSet->FieldByName(pPrefix + MPWA_NO_DP)->AsInteger = Dp;
    pDataSet->FieldByName(pPrefix + MPWA_NO_MEANP)->AsInteger = MeanP;
    pDataSet->FieldByName(pPrefix + MPWA_NO_T1)->AsInteger = T1;
    pDataSet->FieldByName(pPrefix + MPWA_NO_T2)->AsInteger = T2;
    pDataSet->FieldByName(pPrefix + MPWA_NO_AI)->AsInteger = AI1;

    // Store Arrays
    pDataSet->FieldByName(pPrefix + MPWA_NO_AV)->Value =
      PackToString(&CalAvPulse.Profile[CalAvPulse.Start], CalAvPulse.Length(), Divider);

    if (TPWASignal::Store(pDataSet, pPrefix + MPWA_NO_PULSES, pPrefix + MPWA_NO_TRIGS)==false)
      return false;
/*
    pDataSet->FieldByName(pPrefix + MPWA_NO_PULSES)->Value =
      PackToString(Signal, NofPoints, 1);

    pDataSet->FieldByName(pPrefix + MPWA_NO_TRIGS)->Value =
      PackToString(TrigPts, NofOnsets);
*/
  }
  catch (Exception &exception)
  {
    MsgBox(TERROR, GetCurrentPwaMeasureDetails(), MSG_DBREADWRITE_ERROR, MSG_ERR_READDB,
           LoadStr(MSG_ERR_READDB) + exception.Message);
    return false;
  }

  return true;
}

/* ###########################################################################
 ** StoreAccess()
 **
 ** DESCRIPTION
 **  Store TPressure class properties to MSAccess database
 ** INPUT
 **  pDataSet - TADOQuery or TADOTable
 **  const int pSampleRate - Sample Rate
 ** OUTPUT
 **  boolean success or not
*/
//---------------------------------------------------------------------------
bool TPressure::StoreAccess (TDataSet* pDataSet, String pPrefix)
{
  try
  {
    // Store variables
    pDataSet->FieldByName(pPrefix + MPWA_NO_SP)->AsFloat = Sp;
    pDataSet->FieldByName(pPrefix + MPWA_NO_DP)->AsFloat = Dp;
    pDataSet->FieldByName(pPrefix + MPWA_NO_MEANP)->AsFloat = MeanP;
    pDataSet->FieldByName(pPrefix + MPWA_NO_T1)->AsFloat = T1;
    pDataSet->FieldByName(pPrefix + MPWA_NO_T2)->AsFloat = T2;
    pDataSet->FieldByName(pPrefix + MPWA_NO_AI)->AsFloat = AI1;
    pDataSet->FieldByName(pPrefix + MPWA_NO_CALCT1)->AsFloat = CalcT1;
    pDataSet->FieldByName(pPrefix + MPWA_NO_CALCT2)->AsFloat = CalcT2;

    // Additional for MSAccess
    pDataSet->FieldByName(pPrefix + MPWA_NO_ESP)->AsFloat = ESP;
    pDataSet->FieldByName(pPrefix + MPWA_NO_P1)->AsFloat = P1;
    pDataSet->FieldByName(pPrefix + MPWA_NO_P2)->AsFloat = P2;
    pDataSet->FieldByName(pPrefix + MPWA_NO_T1ED)->AsFloat = T1ED;
    pDataSet->FieldByName(pPrefix + MPWA_NO_T2ED)->AsFloat = T2ED;
    pDataSet->FieldByName(pPrefix + MPWA_NO_QT1)->AsInteger = QualityT1;
    pDataSet->FieldByName(pPrefix + MPWA_NO_QT2)->AsInteger = QualityT2;

    // Store Arrays
    if (TPWASignal::Store(pDataSet, pPrefix + MPWA_NO_PULSES, pPrefix + MPWA_NO_TRIGS)==false)
      return false;

    pDataSet->FieldByName(pPrefix + MPWA_NO_UNCAL_AV)->AsString =
      PackToString(&AvPulse.Profile[AvPulse.Start], AvPulse.Length(), 1);

    // Calibrated average pulse
    if (pDataSet->FindField(pPrefix + MPWA_NO_AV) != NULL)
    {
      // Recalculate Calibrated average pulse
      int lExpandFactor = ExpPulse.SampleRate/CalAvPulse.SampleRate;
      if (CalAvPulse.DownSample(&ExpPulse, lExpandFactor)==false)
          return false;
      pDataSet->FieldByName(pPrefix + MPWA_NO_AV)->AsString =
        PackToString(&CalAvPulse.Profile[CalAvPulse.Start], CalAvPulse.Length(), Divider);
    }
    else if (pDataSet->FindField(pPrefix + MPWA_NO_EXPPULSE) != NULL)
    { // Expanded pulse in database
      pDataSet->FieldByName(pPrefix + MPWA_NO_EXPPULSE)->AsString =
        PackFloatToString(&ExpPulse.Profile[ExpPulse.Start], ExpPulse.Length());
    }
/*
    pDataSet->FieldByName(pPrefix + MPWA_NO_PULSES)->AsString =
      PackToString(Signal, NofPoints, 1);

    pDataSet->FieldByName(pPrefix + MPWA_NO_TRIGS)->AsString =
      PackToString(TrigPts, NofOnsets);
*/
  }
  catch (Exception &exception)
  {
    MsgBox(TERROR, GetCurrentPwaMeasureDetails(), MSG_DBREADWRITE_ERROR, MSG_ERR_READDB,
           LoadStr(MSG_ERR_READDB) +exception.Message);
    return false;
  }

  return true;
}

/* ###########################################################################
 ** ValidateBeforeStore()
 **
 ** DESCRIPTION
 **  Validate TPressure class properties picked up from database
 ** INPUT
 **  // const int pSampleRate - Sample Rate
 ** OUTPUT
 ** RETURN
 **  boolean success or not
*/
//---------------------------------------------------------------------------
bool TPressure::ValidateBeforeStore()
{
  bool ret = true;

  // Pressure validation
  if ((Sp!=DEFAULT_VALUE) && ((Sp < MIN_PRESS) || (Sp > MAX_PRESS)))
  {
    MsgBox(TERROR,
           GetCurrentPwaMeasureDetails(),
           MSG_VALIDATION_ERROR, MSG_SP_OUT,
           LoadStr(MSG_SP_OUT) + RoundIntToStr(Sp));
    Sp = DEFAULT_VALUE;
    ret = false;
  }
  if ((Dp!=DEFAULT_VALUE) && ((Dp < MIN_PRESS) || (Dp >= Sp)))
  {
    MsgBox(TERROR,
           GetCurrentPwaMeasureDetails(),
           MSG_VALIDATION_ERROR,
           MSG_DP_OUT,
           LoadStr(MSG_DP_OUT) + RoundIntToStr(Dp));
    Dp = DEFAULT_VALUE;
    ret = false;
  }
  if ((MeanP!=DEFAULT_VALUE) && ((MeanP < Dp) || (MeanP > Sp)))
  {
    MsgBox(TERROR,
           GetCurrentPwaMeasureDetails(),
           MSG_VALIDATION_ERROR,
           MSG_MP_OUT,
           LoadStr(MSG_MP_OUT) + RoundIntToStr(MeanP));
    MeanP = DEFAULT_VALUE;
    ret = false;
  }

  // Check Calibrated Average pulse is negative
  for (int i=CalAvPulse.Start; i <= CalAvPulse.End; i++)
  {
    if (CalAvPulse.Profile[i]<=0)
    {
      MsgBox(TERROR, GetCurrentPwaMeasureDetails(), MSG_VALIDATION_ERROR, MSG_NEG_AVPULSE,
             LoadStr(MSG_NEG_AVPULSE) + IntToStr(i));
      ret = false;
      break;
    }
  }

  // Validate signal
  // Cut signal if it is negative
  for (int i=0; i<NofPoints; i++)
  {
    if (Signal[i] <= 0.)
    {
      NofPoints = i;
      MsgBox(TERROR, GetCurrentPwaMeasureDetails(), MSG_VALIDATION_ERROR, MSG_NEG_SIGNAL,
             LoadStr(MSG_NEG_SIGNAL) + IntToStr(NofPoints));
      // ret = false;
      break;
    }
  }

  // Check signal too short
  if (NofPoints < PRESSURE_PULSE_MAXLENGTH)
  {
      MsgBox(TERROR, GetCurrentPwaMeasureDetails(), MSG_VALIDATION_ERROR, MSG_SIGNAL_TOO_SHORT);
      ret = false;
  }

  // Check AveragePulse is negative
  for (int i=AvPulse.Start; i<=AvPulse.End; i++)
  {
    if (AvPulse.Profile[i]<=0)
    {
      MsgBox(TERROR, GetCurrentPwaMeasureDetails(), MSG_VALIDATION_ERROR, MSG_NEG_AVPULSE,
             LoadStr(MSG_NEG_AVPULSE) + IntToStr(i));
      ret = false;
      break;
    }
  }

  // Do not allow to store in database (return false)
  if (ret == false) return ret;

  // Check not critical parameters
  int lMaxTime = ((ED!=DEFAULT_VALUE) && (ED > 0) ? ED + 1 : MAX_TIME);

  if ((T1!=DEFAULT_VALUE) && ((T1 <= 0) || (T1 >= lMaxTime)))
  {
    MsgBox_show(TWARNING,
                MSG_VALIDATION_ERROR,
                LoadStr(MSG_INVALID_T1),
                MSG_INVALID_T1,
                LoadStr(MSG_INVALID_T1) +RoundIntToStr(T1) +GetCurrentPwaMeasureDetails());
    T1 = DEFAULT_VALUE;
  }

  if ((T2!=DEFAULT_VALUE) && ((T2 <= 0) || (T2 >= lMaxTime)))
  {
     MsgBox_show(TWARNING,
                MSG_VALIDATION_ERROR,
                LoadStr(MSG_INVALID_T2),
                MSG_INVALID_T2,
                LoadStr(MSG_INVALID_T2) +RoundIntToStr(T2) +GetCurrentPwaMeasureDetails());
     T2 = DEFAULT_VALUE;
  }

  if ((ED!=DEFAULT_VALUE) && ((ED <= 0) || (ED >= lMaxTime)))
  {
     MsgBox_show(TWARNING,
                 MSG_VALIDATION_ERROR,
                 LoadStr(MSG_INVALID_ED),
                 MSG_INVALID_ED,
                 LoadStr(MSG_INVALID_ED) +RoundIntToStr(ED) +GetCurrentPwaMeasureDetails());
     ED = DEFAULT_VALUE;
  }
  return true;
}

/* ###########################################################################
 ** ValidateBeforeCalculate()
 **
 ** DESCRIPTION
 **  Validate TPressure class properties before storing in the database
 **  setting up DEFAULT_VALUE (9999) if wrong value
 ** INPUT
 **  // const int pSampleRate - Sample Rate
 ** OUTPUT
 ** RETURN
 **  boolean success or not
*/
//---------------------------------------------------------------------------
bool TPressure::ValidateBeforeCalculate()
{
  bool ret = true;
  if (NofPoints < PRESSURE_PULSE_MAXLENGTH)
  {
    MsgBox(TERROR, GetCurrentPwaMeasureDetails(), MSG_VALIDATION_ERROR, MSG_SIGNAL_TOO_SHORT);
    ret = false;
  }
  if (NofPoints > PRESSURE_MAX_PPOINTS)
  {
    MsgBox(TERROR, GetCurrentPwaMeasureDetails(), MSG_VALIDATION_ERROR, MSG_SIGNAL_TOO_LONG);
    NofPoints = PRESSURE_MAX_PPOINTS;
  }
  return ret;
}

/* ###########################################################################
 ** NonDBaseFeatures()
 **
 ** DESCRIPTION
 **  Calculate specific non-database features for Pressure
 **  on the base of Pulse
 ** INPUT
 ** TPressureCentral class properties
 **  pPulse - pulse to extract data from (AvPulse when only populate
 **  data from DB, ExpPulse - when Calculate data)
 **  pSampleRate - Sample Rate (128 when populate, 1024 when calculate)
 ** OUTPUT
 ** TPressure class properties
 ** RETURN
 **  boolean success or not
*/
//---------------------------------------------------------------------------
bool TPressure::NonDBaseFeatures(TPulse *pPulse) //, const int pSampleRate)
{
  // Initialisation
  P1 = DEFAULT_VALUE;
  P2 = DEFAULT_VALUE;
  T1ED = DEFAULT_VALUE;
  T2ED = DEFAULT_VALUE;
  // Calculation
  if ((ED != DEFAULT_VALUE) && (ED > 0) && (T1 != DEFAULT_VALUE) && (T1 < ED))
  {
     T1ED = T1/ED * 100;
  }
  if (T1 != DEFAULT_VALUE)
  {
     P1  = pPulse->ValueAsTime (T1); //, pSampleRate);
  }

  if ((ED != DEFAULT_VALUE) && (ED > 0) && (T2 != DEFAULT_VALUE) && (T2 < ED))
  {
     T2ED = float(T2)/ED * 100;
  }
  if (T2 != DEFAULT_VALUE)
  {
     P2  = pPulse->ValueAsTime (T2); //, pSampleRate);
  }
  return true;
}

/* ###########################################################################
 ** Calculate()
 **
 ** DESCRIPTION
 **  Do all mathematics for a Pressure signal
 ** INPUT
 **  TPressure class (source)
 ** OUTPUT
 **  boolean success or not
*/
//---------------------------------------------------------------------------
bool TPressure::CalculateTrigPts(const int pAlgorithm, const int pMinTrigPt)
{
  // Validation
  if (ValidateBeforeCalculate()==false)
    return false;

  if (FindOnsets(pAlgorithm, pMinTrigPt)==false)
  {
    MsgBox(TERROR, GetCurrentMeasureDetails(), MSG_MATH_ERROR,  MSG_TRIGGER_ERR);
    return false;
  }
  return true;
}

/* ###########################################################################
 ** GetTriggerPointsFromArray
 **
 ** DESCRIPTION
 **  Get trigger points from populated TrigPts array and calculate their number
 ** INPUT
 **  TPressure class (source)
 ** OUTPUT
 **  TPressure class properties
 ** RETURN
 **  boolean success or not
*/
//---------------------------------------------------------------------------
bool TPressure::GetTriggerPointsFromArray(const int pLength)
{
  // NofOnsets = 0;
  NofOnsets = pLength;
  // Loop up to the first negative trigger point
  for (int i=0; i < pLength; i++)
  {
    if (TrigPts[i] < 0 || TrigPts[i] > NofPoints) // PRESSURE_MAX_PPOINTS)
    {
      if (i!=0) NofOnsets = i;
      break;
    }
    else
    {
      if (i>0 && TrigPts[i] <= TrigPts[i-1])
      {
        NofOnsets = i;
        break;
      }
    }
  }
  // Validation is checked later
  return true;
}

/* ###########################################################################
 ** CalcPulses ()
 **
 ** DESCRIPTION
 **  Calculate Pulses using trigger points
 ** INPUT
 **  TPressure class (source)
 ** OUTPUT
 **  boolean success or not
*/
//---------------------------------------------------------------------------
bool TPressure::CalcPulses(const bool pRejectExtraPulses, const int pTail)
{
  if (pRejectExtraPulses == false)
  {
    // Calculate pulses without rejecting extra short and long pulses
    NofPulses = 0;
    for (int i=0; i < NofOnsets - 1; i++)
    {
      short int lLength = (short int)(TrigPts[i+1] - TrigPts[i] + 1);
      // Reject extralarge pulses
      if (lLength > PRESSURE_PULSE_MAXLENGTH  || lLength < PRESSURE_PULSE_MINLENGTH)
        continue;
      int index = TrigPts[i] - pTail;
      if (index < 0) // Miss first trigger point if it is too close to the start
         continue;
      Pulses[NofPulses].Profile = &Signal[index];
      Pulses[NofPulses].Initialise();
      Pulses[NofPulses].Start = (short int) (pTail);
      Pulses[NofPulses].Index = TrigPts[i];
      Pulses[NofPulses].SetLength(lLength);
      Pulses[NofPulses].SetSize(lLength + 1*pTail);
      NofPulses++;
    }
    return (NofPulses > 1);
  }
  else
  {
    if (NofOnsets <= 1)
    {
      return false;
    }
    // Calculate average length
    float lAvLength = 0.;
    int NofAv = 0;
    for (int i=0; i < NofOnsets - 1; i++)
    {
      int lLength = (TrigPts[i+1] - TrigPts[i] + 1);
      if (lLength < PRESSURE_PULSE_MAXLENGTH && lLength > PRESSURE_PULSE_MINLENGTH)
      {
        lAvLength += lLength;
        NofAv++;
      }
    }
    if (NofAv <= 0)
      return false;

    lAvLength /= NofAv;
    // Calculate pulses rejecting extra short and long pulses
    NofPulses = 0;
    for (int i=0; i < NofOnsets - 1; i++)
    {
      short int lLength = (short int)(TrigPts[i+1] - TrigPts[i] + 1);
      if (lLength > PRESSURE_PULSE_MAXLENGTH || lLength < PRESSURE_PULSE_MINLENGTH)
        continue;
      if ((lLength >= lAvLength*PWA_MIN_VALID_PULSELENGTH_PERCENT) &&
          (lLength <= lAvLength*PWA_MAX_VALID_PULSELENGTH_PERCENT))
      {
        int index = TrigPts[i] - pTail/* * ExpandFactor*/;
        if (index < 0) // Miss first trigger point if it is too close to the start
          continue;
        Pulses[NofPulses].Profile = &Signal[index];
        Pulses[NofPulses].Initialise();
        Pulses[NofPulses].Start = (short int) (pTail/* * ExpandFactor*/);
        Pulses[NofPulses].Index = TrigPts[i];
        Pulses[NofPulses].SetLength(lLength);
        Pulses[NofPulses].SetSize(lLength + 1*pTail/* * ExpandFactor*/);
        NofPulses++;
      }
    }
    return (NofPulses > 1);
  }
}

/* ###########################################################################
 ** AveragePulse (...)
 **
 ** DESCRIPTION
 **  Find Average Pulse from Pulses
 ** INPUT
 **  pLength - predefined pulse Length (0 for periph, >0 for central)
 **  Pulses[NofPulses] - all pulses
 ** OUTPUT
 **  AvPulse - average pulse structure
 ** RETURN
 **  boolean success or not
*/
//---------------------------------------------------------------------------
bool TPressure::AveragePulse(const int pLengthAvPulse, const int pTail, const int pSignalSampleRate)
{
  if (NofPulses <= 0)
  {
    // MsgBox(TERROR, GetCurrentPwaMeasureDetails(), MSG_MATH_ERROR, MSG_AVPULSE_ERR);
    return false;
  }
  // Calculate Size of Average Pulse averaging all pulses
  // if the length is unknown
  int LengthAvPulse = 0;
  if (pLengthAvPulse > 0)
  {
    LengthAvPulse = pLengthAvPulse;
  }
  else
  {
    for (int i = 0; i < NofPulses; i++)
    {
      // Break if wrong pulse
      if (Pulses[i].Validate()==false)
      {
        //MsgBox(TERROR, GetCurrentPwaMeasureDetails(), MSG_MATH_ERROR, MSG_AVPULSE_ERR);
        return false;
      }
      LengthAvPulse += Pulses[i].Length();
    }
    LengthAvPulse = math_Round(float(LengthAvPulse)/ NofPulses);
  }

  // Validation
  if (LengthAvPulse < PRESSURE_PULSE_MINLENGTH || LengthAvPulse > PRESSURE_PULSE_MAXLENGTH)
  {
     //MsgBox(TERROR, GetCurrentPwaMeasureDetails(), MSG_MATH_ERROR, MSG_AVPULSE_ERR);
     return false;
  }

  // Create AvPulse
  AvPulse.Initialise(pSignalSampleRate);
  AvPulse.Start = (short int) (pTail);
  AvPulse.SetLength(LengthAvPulse);
  AvPulse.SetSize(LengthAvPulse + 1*pTail);
  // Initialisation of AvPulse for summarisation
  for (int i = 0; i < AvPulse.Size(); i++)
  {
    double lsum = 0;
    int lCountPulses = 0;
    for (int np = 0; np < NofPulses; np++)
    {
      if (i < Pulses[np].Size())
      {
        // Shift Up Pulse[np] from Pulse[0]
        float lUpStep = Pulses[np].Profile[Pulses[np].Start] - Pulses[0].Profile[Pulses[0].Start];
        lsum += Pulses[np].Profile[i] - lUpStep;
        lCountPulses++;
      }
    }
    if (lCountPulses < 1)
    {
       //MsgBox(TERROR, GetCurrentPwaMeasureDetails(), MSG_MATH_ERROR, MSG_AVPULSE_ERR);
       return false;
    }
    AvPulse.Profile[i] = lsum/lCountPulses;
  }
/*
  float lScale, lv, lUpStep;
  for (int i = 0; i < NofPulses; i++)
  {
    // Length scale
    lScale = float(Pulses[i].Length - 1)/(LengthAvPulse - 1);
    for (int j = 0; j < LengthAvPulse; j++)
    {
      int ind = math_Round(j*lScale);
      if (ind > Pulses[i].Length - 1)
        ind = Pulses[i].Length - 1;
      lv = Pulses[i].Profile[ind] - lUpStep;
      AvPulse.Profile[j] += lv/NofPulses;
    }
  }
  AvPulse.Length = (short int) LengthAvPulse;
*/
  AvPulse.Index = 0;

  if (AvPulse.Length() < PRESSURE_PULSE_MINLENGTH || AvPulse.Length() > PRESSURE_PULSE_MAXLENGTH/**ExpandFactor*/)
  {
    //MsgBox(TERROR, GetCurrentPwaMeasureDetails(), MSG_MATH_ERROR, MSG_AVPULSE_ERR);
    return false;
  }
  return true;
}

/* ###########################################################################
 ** GetCalPulseFromDB()
 **
 ** DESCRIPTION
 **  Get Calibrate pulse from DB to calculate features
 **  on the base of old stored CalPulse.
 **  Need only to compare old and new math
 ** INPUT
 ** TPressure class
 ** OUTPUT
 ** CalAvPulse
 ** RETURN
 **  boolean success or not
*/
//---------------------------------------------------------------------------
bool TPressure::GetCalPulseFromDB(TDataSet* pDataSet, String pPrefix,
                                  const int pSignalSampleRate,
                                  const int pDataRev)
{
  // Calibrated average pulse
  int NofBytes = min((int)(pDataSet->FieldByName(pPrefix + MPWA_NO_AV)->AsString.Length()),
                (int)(PRESSURE_PULSE_MAXLENGTH * sizeof (short int)));
  if (CalAvPulse.ExtractFromBuffer(pDataSet->FieldByName(pPrefix + MPWA_NO_AV)->AsString.c_str(),
                (short int) NofBytes, Divider)==false)
    return false;
  CalAvPulse.SampleRate = (short int) pSignalSampleRate,


  // Sp, Dp - from database
  Sp = pDataSet->FieldByName(pPrefix + MPWA_NO_SP)->AsInteger;
  Dp = pDataSet->FieldByName(pPrefix + MPWA_NO_DP)->AsInteger;

  return true;
}

/* ###########################################################################
 ** CalibratePulse()
 **
 ** DESCRIPTION
 **  Calibrate Pulse using formula:
 **  Cal = Gain*UnCal + Offset
 **  and finding min, max
 ** INPUT
 ** TPressure class
 ** pGain, pOffset - gain and offset
 ** OUTPUT
 **  boolean success or not
*/
//---------------------------------------------------------------------------
bool TPressure::CalibratePulse(const float pGain, const float pOffset, float &pMin, float &pMax)
{
  // Transforming
  for (int i = 0; i < AvPulse.Size(); i++)
  {
    CalAvPulse.Profile[i] = pGain * AvPulse.Profile[i] + pOffset;
    // Find Min, Max
    if (i==AvPulse.Start)
    {
      pMin = CalAvPulse.Profile[CalAvPulse.Start];
      pMax = CalAvPulse.Profile[CalAvPulse.Start];
    }
    else if (i > AvPulse.Start && i <= AvPulse.End)
    {
      if (CalAvPulse.Profile[i] > pMax)
        pMax = CalAvPulse.Profile[i];
      if (CalAvPulse.Profile[i] < pMin)
        pMin = CalAvPulse.Profile[i];
    }
  }
  // Setup length
  CalAvPulse.Initialise();
  CalAvPulse.Start = AvPulse.Start;
  CalAvPulse.Index  = AvPulse.Index;
  CalAvPulse.SetLength(AvPulse.Length());
  CalAvPulse.SetSize(AvPulse.Size());

  return true;
}

/* ###########################################################################
 ** ExtractFeatures()
 **
 ** DESCRIPTION
 **  Extract feature parameters depended on T1, T2, ED from ExpPulse
 ** INPUT
 ** int pSampleRate - Sample Rate after expanding (1024Hz)
 ** TPressure class properties
 ** OUTPUT
 ** TPressure class properties
 ** RETURN
 **  boolean success or not
*/
//---------------------------------------------------------------------------
bool TPressure::ExtractFeatures(/*const int pSampleRate, */const int pEDIndex)
{
   // Validate whether expanded pulse is shifted properly to systolic onset
   if (ExpPulse.Length()!=ExpPulse.Size() || ExpPulse.Start!=0)
    return false;

   // Sp, Dp should be already calculated in Calibrate AvPulse
   // T1, T2, ED calculated in TPWA class

   // Mean Pressure  mmHg
   if (ExpPulse.Length() > 1)
     MeanP = ExpPulse.Integral()/(ExpPulse.Length() - 1);

   // if (ExpPulse.ED != DEFAULT_VALUE)
   //  ESP = ExpPulse.Value(ExpPulse.ED);   // mmHg End Systilic pressure

   // P1, P2 - calculated pressures
   float P0 = ExpPulse.Profile[ExpPulse.Start];

   if (ExpPulse.T1 != DEFAULT_VALUE)
   {
     P1 = ExpPulse.Value (ExpPulse.T1);
   }
   if (ExpPulse.T2 != DEFAULT_VALUE)
   {
     P2 = ExpPulse.Value (ExpPulse.T2);
   }

   // Augmentation Index
   if ((P1 != DEFAULT_VALUE) && (P2 != DEFAULT_VALUE) && (P1 - P0 > 0))
   {
  	 AI1 = (P2 - P0)/(P1 - P0) * 100;
   }
   QualityT1 = ExpPulse.QualityT1;
   QualityT2 = ExpPulse.QualityT2;

   if (RecalculateEDDependants(pEDIndex/*, pSampleRate*/)==false)
    return false;

/*
   // Pressures extracted for Calibrated Average pulse
   // because of after Expanded Pulse smoothing pressures
   // can be less then Dp

   // Mean Pressure  mmHg
   if (CalAvPulse.Length > 1)
     MeanP = CalAvPulse.Integral(0, CalAvPulse.Length - 1)/(CalAvPulse.Length - 1);

   // mmHg End Systilic pressure
   if (ED != DEFAULT_VALUE)
     ESP = CalAvPulse.Value(ED, pSampleRate);

   // P1, P2 - calculated pressures
   float P0 = CalAvPulse.Profile[Start];

   if (T1 != DEFAULT_VALUE)
   {
     P1 = CalAvPulse.Value (T1, pSampleRate);
   }
   if (T2 != DEFAULT_VALUE)
   {
     P2 = CalAvPulse.Value (T2, pSampleRate);
   }
*/
/*
   if ((pED != DEFAULT_VALUE) && (ExpPulse.T1 != DEFAULT_VALUE))
     T1ED = float(ExpPulse.T1)/pED * 100;
   if ((pED != DEFAULT_VALUE) && (ExpPulse.T2 != DEFAULT_VALUE))
     T2ED = float(ExpPulse.T2)/pED * 100;
*/

   return true;
}

/* ###########################################################################
 ** ExpandPulse (TPulse *pPulse)
 **
 ** DESCRIPTION
 **  Expand pPulse from 308 (pPulse.Length) to 1024 (ExpPulse.Length) points
 **  with analitical calculation of expanded profile and its derivatives
 **  using polinomial spline interpolation
 ** INPUT
 **  pPulse - pulse (for example, Calibrated Average pulse)
 ** OUTPUT
 **  ExpPulse, Der1ExpPulse, Der2ExpPulse, Der3ExpPulse- expanded pulse and its derivatives
 ** RETURN
 **  boolean success or not
*/
//---------------------------------------------------------------------------
bool TPressure::ExpandPulse(TPulse *pPulse, const int pExpandFactor)
{
  // Pulse Validation
  if (pPulse->Validate()==false)
  {
    return false;
  }
  if (pPulse->SampleRate <= 0 || pExpandFactor < 1)
  {
    return false;
  }

  ExpPulse.Start = (short int) (pPulse->Start * pExpandFactor);
  ExpPulse.SetLength((pPulse->Length() - 1) * pExpandFactor + 1);
  ExpPulse.SampleRate = (short int) (pPulse->SampleRate * pExpandFactor);

  Der1ExpPulse.SetLength(ExpPulse.Length());
  Der2ExpPulse.SetLength(ExpPulse.Length());
  Der3ExpPulse.SetLength(ExpPulse.Length());
  Der1ExpPulse.SampleRate = ExpPulse.SampleRate;
  Der2ExpPulse.SampleRate = ExpPulse.SampleRate;
  Der3ExpPulse.SampleRate = ExpPulse.SampleRate;

  ExpPulse.SetSize((pPulse->Size() - 1) * pExpandFactor + 1);
  Der1ExpPulse.SetSize(ExpPulse.Size());
  Der2ExpPulse.SetSize(ExpPulse.Size());
  Der3ExpPulse.SetSize(ExpPulse.Size());

  float lMaxDer1, lMaxDer2, lMaxDer3;
  Der1Step = 1./10;

  // If ExpandFactor = 1 - copy Pulse into ExpPulse and find derivatives
  if (pExpandFactor == 1)
  {
    memcpy (ExpPulse.Profile, pPulse->Profile, pPulse->Size() * sizeof(float));
    math_SmoothDerivative1(pPulse->Profile, pPulse->Size(), SmoothOrder, Der1Step, Der1ExpPulse.Profile, lMaxDer1);
    math_SmoothDerivative1(Der1ExpPulse.Profile, pPulse->Size(), SmoothOrder, 1./5, Der2ExpPulse.Profile, lMaxDer2);
    math_SmoothDerivative1(Der2ExpPulse.Profile, pPulse->Size(), SmoothOrder, 1./5, Der3ExpPulse.Profile, lMaxDer3);
    //math_Deriv1(pPulse.Profile, pPulse->Length, 1./10, Der1ExpPulse.Profile, lMaxDer1);
    //math_Deriv1(Der1ExpPulse.Profile, pPulse->Length, 1./5, Der2ExpPulse.Profile, lMaxDer2);
    //math_Deriv1(Der2ExpPulse.Profile, pPulse->Length, 1./5, Der3ExpPulse.Profile, lMaxDer3);
    return true;
  }

  // Scale coefficient
  float Scale = double(1) / pExpandFactor;

  // step-by-step polinomial interpolation for function and derivatives
  // ------------------------------------------------------------------

  // First and second derivatives of Raw Pulse
  int lpSize = pPulse->Size();
  math_SmoothDerivative1(pPulse->Profile, lpSize, SmoothOrder, Der1Step, Der1, lMaxDer1);
  math_SmoothDerivative1(Der1, lpSize, SmoothOrder, 1./5, &Der1[lpSize], lMaxDer2);
  math_SmoothDerivative1(&Der1[lpSize], lpSize, SmoothOrder, 1./2, &Der1[2*lpSize], lMaxDer3);
/*
  pPulse->Smooth(2);
  math_Derivatives123(pPulse->Profile, lpSize, 1., Der1, &Der1[lpSize], &Der1[2*lpSize],
                      lMaxDer1, lMaxDer2, lMaxDer3);
  float Der1Amplifier = 10;
  float Der2Amplifier = 50;
  float Der3Amplifier = 100;
  for (int i=0; i<lpSize; i++)
  {
     Der1[i] *= Der1Amplifier;
     Der1[lpSize + i] *= Der2Amplifier;
     Der1[2*lpSize + i] *= Der3Amplifier;
  }
  math_SmoothArray(&Der1[0], lpSize, 2);
  math_SmoothArray(&Der1[lpSize], lpSize, 2);
  math_SmoothArray(&Der1[2*lpSize], lpSize, 2);
  //Der1ExpPulse.Smooth(PulseDerSmoothOrder/2);
  //Der2ExpPulse.Smooth(PulseDerSmoothOrder);
  //Der3ExpPulse.Smooth(PulseDerSmoothOrder*2);
*/
  // Interpolation of Raw profile and derivatives
  int SplineIndex = 0; // Initial spline index
  for (int i = 0; i < ExpPulse.Size(); i++)
  {
    float fj = Scale * i; // fj is an image of ExPulse x-point on pPulse->x-point
    // Find SplineIndex - beginning of a spline
    SplineIndex = math_GetSplineIndex(fj, SplineIndex, SplineOrder, pPulse->Size());
    // Profile
    math_Spline (fj - SplineIndex, &pPulse->Profile[SplineIndex], SplineOrder, ExpPulse.Profile[i]);
    // First derivative
    math_Spline (fj - SplineIndex, &Der1[SplineIndex], SplineOrder, Der1ExpPulse.Profile[i]);
    // Second derivative
    math_Spline (fj - SplineIndex, &Der1[lpSize + SplineIndex], SplineOrder, Der2ExpPulse.Profile[i]);
    // Third derivative
    math_Spline (fj - SplineIndex, &Der1[2*lpSize + SplineIndex], SplineOrder, Der3ExpPulse.Profile[i]);
  }
/*
  ExpPulse->Smooth();
  math_SmoothDerivative1(ExpPulse.Profile, ExpPulse.Length, SmoothOrder, 1./(5.*ExpandFactor), Der1ExpPulse.Profile, lMaxDer1);
  math_SmoothDerivative1(Der1ExpPulse->Profile, ExpPulse.Length, SmoothOrder, 1./(5.*ExpandFactor), Der2ExpPulse.Profile, lMaxDer2);
*/
  return true;
}

/* ###########################################################################
 ** SystolicOnset (pAlgorithm)
 **
 ** DESCRIPTION
 **  Find systolic onset (trigger point) for a pulse,
 **  line up (shift) pulse profile and derivatives to it and cut pulse tale
 ** INPUT
 **  pAlgorithm (PWA_TANGENT_DER2_ALGORITHM) - algorithm type to calculate onset
 ** OUTPUT
 **  None
 ** RETURN
 **  boolean success or not
*/
//---------------------------------------------------------------------------
bool TPressure::SystolicOnset(const int pAlgorithm, const int pLengthOfRadial)
{
  // Validation
  if (SampleRate > ExpPulse.SampleRate || SampleRate <= 0)
    return false;
  int lExpandFactor = ExpPulse.SampleRate / SampleRate;
  if (lExpandFactor <= 0)
    return false;
  // Find systolic onset as a peak of der2
  // Find pulse top
  int lTop = ExpPulse.IndexOfMax(0, ExpPulse.End/2);
  if (lTop <= 0)
    return false;
  // Find peak of der1
  int lPeakOfDer1 = Der1ExpPulse.IndexOfExtremum(MAX, GLOBAL, 0, lTop - 1, lExpandFactor);
  if (lPeakOfDer1 <= 0)
    return false;
  // Find peak of der2
  int lPeakOfDer2 = Der2ExpPulse.IndexOfExtremum(MAX, GLOBAL, 0, lPeakOfDer1 - 1, lExpandFactor);
  if (lPeakOfDer2 <= 0)
    return false;
  // Find the foot
  int lFoot = -1;
  for (int j=lPeakOfDer2; j>=0; j--)
  {
    if (ExpPulse.Profile[j] <= ExpPulse.Profile[j-1])
    {
      lFoot = j;
      break;
    }
  }
  if (lFoot < 0)
    lFoot = 0;

  // switch between algorithm
  int lSystolicOnset = -1;
  switch (pAlgorithm)
  {
    case PWA_DER1_ALGORITHM:
      lSystolicOnset = lFoot;
      break;
    case PWA_DER2_ALGORITHM:
      lSystolicOnset = lPeakOfDer2;
      break;
    case PWA_TANGENT_DER1_ALGORITHM:
      break;
    case PWA_TANGENT_DER2_ALGORITHM:
    {
      // Calculate tangent
      // tangent is a Der1 value in point maxD2
      double lTangent;
      try
      {
        float D1F = Der1Step/float(lExpandFactor);
        lTangent = Der1ExpPulse.Profile[lPeakOfDer2]*D1F;
      }
      catch (...)
      {
        return false;
      }
      if (lTangent <= 0.)
        return false;
      // After foot has been found
      // Solve triangle to get time-shift
      float lVertShoulder = ExpPulse.Profile[lPeakOfDer2] - ExpPulse.Profile[lFoot];
      float lHorizShoulder = lVertShoulder/lTangent;
      // Find onset
      float lFloatOnset = float(lPeakOfDer2) - lHorizShoulder;
      if (lFloatOnset <= lFoot)
        lFloatOnset = lFoot;
      lSystolicOnset = math_Round(lFloatOnset);
      break;
    }
  }

  if (lSystolicOnset < 0)
    return false;

  if (lSystolicOnset > ExpPulse.Start)
    lSystolicOnset = ExpPulse.Start;

/*
  // Check whether new systolic onset close to old
  if (abs(lSystolicOnset - ExpPulse.Start) > ExpPulse.Start/2)
    return false;
*/

  // Shift ExpPulse and derivatives
  int lLength = (pLengthOfRadial <= 0 ? ExpPulse.Length() : pLengthOfRadial);
  for (int i=0; i<lLength; i++)
  {
    ExpPulse.Profile[i] = ExpPulse.Profile[lSystolicOnset + i];
    Der1ExpPulse.Profile[i] = Der1ExpPulse.Profile[lSystolicOnset + i];
    Der2ExpPulse.Profile[i] = Der2ExpPulse.Profile[lSystolicOnset + i];
    Der3ExpPulse.Profile[i] = Der3ExpPulse.Profile[lSystolicOnset + i];
  }
  ExpPulse.Start = 0;
  ExpPulse.SetLength(lLength);
  Der1ExpPulse.SetLength(lLength);
  Der2ExpPulse.SetLength(lLength);
  Der3ExpPulse.SetLength(lLength);

  ExpPulse.SetSize(lLength);
  Der1ExpPulse.SetSize(lLength);
  Der2ExpPulse.SetSize(lLength);
  Der3ExpPulse.SetSize(lLength);

  return true;
}

/* ###########################################################################
 ** ExpandOnlyPulse (TPulse pPulse)
 **
 ** DESCRIPTION
 **  Expand pPulse from 308 (pPulse.Length) to 1024 (ExpPulse.Length) points
 **  with analitical calculation of expanded profile
 **  using polinomial spline interpolation
 ** INPUT
 **  pPulse - pulse (for example, Calibrated Average pulse)
 ** OUTPUT
 **  ExpPulse - expanded pulse
 ** RETURN
 **  boolean success or not
*/
//---------------------------------------------------------------------------
bool TPressure::ExpandOnlyPulse(TPulse *pPulse, const int pExpandFactor)
{
  // Pulse Validation
  if (pPulse->Validate()==false || pPulse->SampleRate <= 0
      || pExpandFactor < 1)
  {
    return false;
  }

  ExpPulse.Initialise();
  ExpPulse.Start = (short int) (pPulse->Start * pExpandFactor);
  ExpPulse.SetLength((pPulse->Length() - 1) * pExpandFactor + 1);
  ExpPulse.SetSize((pPulse->Size() - 1) * pExpandFactor + 1);
  ExpPulse.SampleRate = (short int) (pPulse->SampleRate * pExpandFactor);

  // If ExpandFactor = 1 - copy Pulse into ExpPulse and find derivatives
  if (pExpandFactor == 1)
  {
    memcpy (ExpPulse.Profile, pPulse->Profile, pPulse->Size() * sizeof(float));
    return true;
  }

  // Scale coefficient
  float Scale = double(1) / pExpandFactor;

  // step-by-step polinomial interpolation for function and derivatives
  // ------------------------------------------------------------------
  // Interpolation of Raw profile and derivatives
  int SplineIndex = 0; // Initial spline index
  for (int i = 0; i < ExpPulse.Size(); i++)
  {
    float fj = Scale * i; // fj is an image of ExPulse x-point on pPulse x-point
    // Find SplineIndex - beginning of a spline
    SplineIndex = math_GetSplineIndex(fj, SplineIndex, SplineOrder, pPulse->Size());
    // Profile
    math_Spline (fj - SplineIndex, &pPulse->Profile[SplineIndex], SplineOrder, ExpPulse.Profile[i]);
  }
  return true;
}

// ###########################################################################
// Constructor for TPressurePeriph Class
//---------------------------------------------------------------------------
TPressurePeriph::TPressurePeriph() : TPressure ()
{
  Initialise(0,0);
}
//---------------------------------------------------------------------------
// Class initialisator
//---------------------------------------------------------------------------
void TPressurePeriph::Initialise(const int pSignalSampleRate, const int pExpPulseSampleRate)
{
  // Base class initialisation
  TPressure::Initialise(pSignalSampleRate, pExpPulseSampleRate);
  // PSpare1 = 0;
  SetDefaults(PRESSURE_MAX_PPOINTS, pSignalSampleRate, pExpPulseSampleRate);
}
//---------------------------------------------------------------------------
// Set default values
//---------------------------------------------------------------------------
void TPressurePeriph::SetDefaults(const int pNofPoints, const int pSignalSampleRate,
                                  const int pExpPulseSampleRate)
{
  // Base class defaulting
  TPressure::SetDefaults(pSignalSampleRate, pExpPulseSampleRate);
  // Specific properties initialisation
  NofPoints = pNofPoints;
  MaxdPdt = DEFAULT_VALUE;      // mmHg/s     Maximum dP/dt
  AGPH = DEFAULT_VALUE;
  PH   = DEFAULT_VALUE;
  NoiseFactor = DEFAULT_VALUE;
  QualityED = DEFAULT_VALUE;

  // Quality controls
  QC_PulseHeightVariation = DEFAULT_VALUE;
  QC_PulseLengthVariation = DEFAULT_VALUE;
  QC_PulseHeight = DEFAULT_VALUE;
  QC_DiastolicVariation = DEFAULT_VALUE;
  QC_ShapeDeviation = DEFAULT_VALUE;
  QC_Michael = DEFAULT_VALUE;
  OperatorIndex = DEFAULT_VALUE;
}
/* ###########################################################################
 ** PopulateDBase()
 **
 ** DESCRIPTION
 **  populate class properties from current record in pDataSet
 ** INPUT
 **  pDataSet - TADOQuery or TADOTable
 ** OUTPUT
 **  none
*/
//---------------------------------------------------------------------------
bool TPressurePeriph::PopulateDBase(TDataSet* pDataSet,
     const int pSignalSampleRate,  const int pExpPulseSampleRate,
     const int pDataRev)
{
  if (pDataSet->RecordCount <= 0)
    return false;
  // Pick Up Variables
  MaxdPdt = pDataSet->FieldByName(MPWA_P_MAX_DPDT)->AsInteger;
  // PSpare1 = pDataSet->FieldByName(MPWA_P_SPARE1)->AsInteger;

  // Populate base TPressure class
  if (TPressure::PopulateDBase(pDataSet, PERIPH_PREFIX, pSignalSampleRate,
      pExpPulseSampleRate, pDataRev)==false)
    return false;

  if (ValidateAfterPopulate()==false)
    return false;

  // Only calculate (not check) quality control values
  if (QualityControl()==false)
    return false;

  // Non-database features (ESP for periph)
  if (NonDBaseFeatures(&CalAvPulse/*, pSampleRate*/)== false) return false;

  return true;
}
//---------------------------------------------------------------------------
bool TPressurePeriph::PopulateAccess(TDataSet* pDataSet, const int pSignalSampleRate,
                                     const int pExpPulseSampleRate, const int pDataRev)
{
  PH = DEFAULT_VALUE;
  try
  {
    if (pDataSet->RecordCount <= 0)
      return false;
    // Pick Up Variables
    MaxdPdt = pDataSet->FieldByName(MPWA_P_MAX_DPDT)->AsInteger;

    // Additional for MSAccess
    QualityED = pDataSet->FieldByName(MPWA_QUALITY_ED)->AsInteger;
    QC_PulseHeight = pDataSet->FieldByName(MPWA_P_QC_PH)->AsFloat;
    QC_PulseHeightVariation = pDataSet->FieldByName(MPWA_P_QC_PHV)->AsFloat;
    QC_PulseLengthVariation = pDataSet->FieldByName(MPWA_P_QC_PLV)->AsFloat;
    QC_DiastolicVariation = pDataSet->FieldByName(MPWA_P_QC_DV)->AsFloat;
    qc_scale = pDataSet->FieldByName(MPWA_P_QC_SCALE_FACTOR)->AsInteger;
    QC_ShapeDeviation = pDataSet->FieldByName(MPWA_P_QC_SD)->AsFloat;
    OperatorIndex = pDataSet->FieldByName(MPWA_P_QC_OI)->AsFloat;
    // PM V9
    // Change default to EM3 and MM3 value
    if (qc_scale == 0)
    {
       qc_scale = 4;
    }

    // Populate base TPressure class
    if (TPressure::PopulateAccess(pDataSet, PERIPH_PREFIX, pSignalSampleRate,
                                  pExpPulseSampleRate, pDataRev) == false)
    {
       return false;
    }
    else
    {
       if (ValidateAfterPopulate()== false)
       {
          return false;
       }
       if (Sp > Dp)
       {
          PH = Sp - Dp;
       }
       if (P1 != DEFAULT_VALUE && P2 != DEFAULT_VALUE && PH != DEFAULT_VALUE)
       {
          AGPH = ((P2 - P1) / PH) * 100.0;
       }
       else
       {
          AGPH = DEFAULT_VALUE;
       }
       if (OperatorIndex == 0)
       {
         CalculateOperatorIndex();
       }
    }
  }
  catch (Exception &exception)
  {
    MsgBox(TERROR, GetCurrentPwaMeasureDetails(), MSG_DBREADWRITE_ERROR, MSG_ERR_READDB,
           LoadStr(MSG_ERR_READDB) +exception.Message);
    return false;
  }

  return true;
}

/* ###########################################################################
 ** ValidateAfterPopulate()
 **
 ** DESCRIPTION
 **  Validate TPressurePeriph class properties after populating
 ** INPUT
 ** OUTPUT
 ** RETURN
 **  boolean success or not
*/
//---------------------------------------------------------------------------
bool TPressurePeriph::ValidateAfterPopulate()
{
  // Validate signal
  // Cut signal if it is negative
  for (int i=0; i<NofPoints; i++)
  {
    if (Signal[i] <= 0.)
    {
      NofPoints = i;
      MsgBox_show(TWARNING,
                  MSG_VALIDATION_ERROR,
                  LoadStr(MSG_NEG_SIGNAL),
                  MSG_NEG_SIGNAL,
                  GetCurrentPwaMeasureDetails() +LoadStr(MSG_NEG_SIGNAL) +IntToStr(NofPoints));
      break;
    }
  }

  // Check signal too short
  if (NofPoints < PRESSURE_PULSE_MAXLENGTH)
  {
      MsgBox_show(TERROR,
                  MSG_VALIDATION_ERROR,
                  LoadStr(MSG_SIGNAL_TOO_SHORT),
                  MSG_SIGNAL_TOO_SHORT,
                  GetCurrentPwaMeasureDetails() +LoadStr(MSG_SIGNAL_TOO_SHORT));
      return false;
  }

  return true;
}

/* ###########################################################################
 ** QualityControl()
 **
 ** DESCRIPTION
 **  Calculate Quality Control parameters for TPressure Class
 ** INPUT
 **  TPressure class properties
 ** OUTPUT
 **  Quality Control properties
 ** RETURN
 **  boolean success or not
*/
//---------------------------------------------------------------------------
bool TPressurePeriph::QualityControl()
{
  // Initialisation
  QC_PulseHeightVariation = DEFAULT_VALUE;
  QC_PulseLengthVariation = DEFAULT_VALUE;
  QC_PulseHeight = DEFAULT_VALUE;
  QC_DiastolicVariation = DEFAULT_VALUE;
  QC_ShapeDeviation = DEFAULT_VALUE;
  QC_Michael = DEFAULT_VALUE;

  if (NofPulses <= 0)
    return false;

  // Average of all pulse Height
  float lSumPH = 0.;
  for (int np = 0; np < NofPulses; np++)
  {
    lSumPH += Pulses[np].Height();
  }
  lSumPH /= NofPulses;
  QC_PulseHeight = (lSumPH >= 0 ? lSumPH : DEFAULT_VALUE);
  if (QC_PulseHeight == DEFAULT_VALUE)
    return false;

    if (qc_scale != DEFAULT_VALUE && qc_scale != 0)
    {
       QC_PulseHeight = QC_PulseHeight / qc_scale;
    }

  // PulseHeightVariation
  float lQC_SumPH = 0.;
  for (int np = 0; np < NofPulses; np++)
  {
    lQC_SumPH += Pulses[np].QC_Height();
  }
  lQC_SumPH /= NofPulses;

  float lPHV = 0.;
  for (int np = 0; np < NofPulses; np++)
  {
    lPHV += fabs(Pulses[np].QC_Height() - lQC_SumPH);
  }
  lPHV /= NofPulses;
  QC_PulseHeightVariation = (lPHV >= 0 ? lPHV/lQC_SumPH * 100 : DEFAULT_VALUE);

  // PulseLengthVariation
  float lPLV = 0.;
  for (int np = 0; np < NofPulses; np++)
  {
    lPLV += fabs(Pulses[np].Length() - AvPulse.Length());
  }
  lPLV /= NofPulses;
  QC_PulseLengthVariation = (lPLV >= 0 ? lPLV/AvPulse.Length() * 100 : DEFAULT_VALUE);

  // Diastolic Variation. Diast pressure is min at the end of pulse (25% tail)
  float lDV = 0.;
  //float lAvDiast = AvPulse.PulseEndValue();
  float lAvDiast = AvPulse.Min(AvPulse.Size() * 0.75, AvPulse.Size());
  for (int np = 0; np < NofPulses; np++)
  {
    // Shift from the level of first pulse
    int lUpStep = Pulses[np].Profile[Pulses[np].Start] - Pulses[0].Profile[Pulses[0].Start];
    //float lDiast = Pulses[np].PulseEndValue();
    float lDiast = Pulses[np].Min(Pulses[np].Size() * 0.75, Pulses[np].Size());
    lDV += fabs(lDiast - lUpStep - lAvDiast);
  }
  lDV /= NofPulses;
  QC_DiastolicVariation = (lDV >= 0 ? lDV/lSumPH * 100 : DEFAULT_VALUE);

  // Slope Variation. RMS error for the first 40% of the pulses
  float lSV = 0.;
  int lFinish = math_Round(AvPulse.Size() * 0.4);
  int lStart = AvPulse.Start; //IndexOfMin(0, lFinish);
  int lLength = lFinish - lStart;
  float AvPulse_rise = AvPulse.Max(lStart, lFinish) - AvPulse.Profile[lStart];
  for (int np = 0; np < NofPulses; np++)
  {
    // Shift from the level of first pulse
    float lSum = 0.;
    float lError = 0.;
    float lMean = 0.;
    //int lPulseStart = Pulses[np].IndexOfMin(0, lFinish);
    float Pulse_rise = Pulses[np].Max(lStart, lFinish) - Pulses[np].Profile[Pulses[np].Start];
    float scaling_factor = AvPulse_rise / Pulse_rise;
    //int lPulseIndex = lPulseStart;
    for (int lIndex = lStart; lIndex < lFinish; lIndex++)
    {
      // Sum the square error for each point in the target range
      // The pulses are scaled to the average pulse height
     // lError = (Pulses[np].Profile[lIndex] - lUpStep) * scaling_factor - AvPulse.Profile[lIndex];
     lError = (((Pulses[np].Profile[lIndex] - Pulses[np].Profile[Pulses[np].Start]) * scaling_factor)+AvPulse.Profile[lStart]) - AvPulse.Profile[lIndex];
      lSum += lError * lError;
      //lPulseIndex++;
    }
    // Calculate the root mean
    lMean = lSum / lLength;
    lSV += sqrt(lMean);
  }
  lSV /= NofPulses;
  QC_ShapeDeviation = (lSV >= 0 ? lSV/lSumPH * 100 : DEFAULT_VALUE);

  // PM CR
  // Shape Variation only equals '0' when the value has not been calculated
  // Check if it's less than 1 because it's a float
  if (QC_ShapeDeviation < 1)
  {
      QC_ShapeDeviation = 1;
  }

  return true;
}

void TPressurePeriph::CalculateOperatorIndex(void)
{
   float       qc_weight_ph;
   float       qc_weight_dv;
   float       qc_weight_phv;
   float       qc_weight_sd;
   float       qc_index = 0.0;

   qc_weight_ph = 35 - (95 - QC_PulseHeight);
   if (qc_weight_ph < -10)
   {
      qc_weight_ph = -10;
   }
   if (qc_weight_ph > 35)
   {
      qc_weight_ph = 35;
   }

   qc_weight_dv = 20 - ((QC_DiastolicVariation - 3) * 3);
   if (qc_weight_dv < -10)
   {
      qc_weight_dv = -10;
   }
   if (qc_weight_dv > 20)
   {
      qc_weight_dv = 20;
   }

   qc_weight_phv = 20 - ((QC_PulseHeightVariation - 4) * 4);
   if (qc_weight_phv < -10)
   {
      qc_weight_phv = -10;
   }
   if (qc_weight_phv > 20)
   {
      qc_weight_phv = 20;
   }

   qc_weight_sd = 25 - ((QC_ShapeDeviation - 3) * 6);
   if (qc_weight_sd < -10)
   {
      qc_weight_sd = -10;
   }
   if (qc_weight_sd > 25)
   {
      qc_weight_sd = 25;
   }
   qc_index = qc_weight_ph + qc_weight_dv + qc_weight_phv + qc_weight_sd;

   if (QualityT1 == WEAK)
   {
      qc_index = qc_index - 10;
   }

   if (QualityT1 == VERYWEAK)
   {
      qc_index = qc_index - 20;
   }

   if (qc_index < 0.)
   {
      qc_index = 0.;
   }
   if (qc_index > 100.)
   {
      qc_index = 100.;
   }
   OperatorIndex = qc_index;
}


/* ###########################################################################
 ** NonDBaseFeatures()
 **
 ** DESCRIPTION
 **  Calculate specific non-database features for Pressure
 **  on the base of Pulse
 ** INPUT
 ** TPressureCentral class properties
 **  pPulse - pulse to extract data from (AvPulse when only populate
 **  data from DB, ExpPulse - when Calculate data)
 **  pSampleRate - Sample Rate (128 when populate, 1024 when calculate)
 ** OUTPUT
 ** TPressure class properties
 ** RETURN
 **  boolean success or not
*/
//---------------------------------------------------------------------------
bool TPressurePeriph::NonDBaseFeatures(TPulse *pPulse)//, const int pSampleRate)
{
  // Initialisation
  ESP = DEFAULT_VALUE;
  // Calculation
  if (ED != DEFAULT_VALUE)
  {
     ESP  = pPulse->ValueAsTime (ED); // , pSampleRate);
  }
  return true;
}
/* ###########################################################################
 ** ValidateBeforeStore()
 **
 ** DESCRIPTION
 **  Validate TPressureCentral class properties before storing in database
 ** INPUT
 **  // const int pSampleRate - Sample Rate
 ** OUTPUT
 ** RETURN
 **  boolean success or not
*/
//---------------------------------------------------------------------------
bool TPressurePeriph::ValidateBeforeStore()
{
  // General pressure validation
  if (TPressure::ValidateBeforeStore()==false)
    return false;


  if (MaxdPdt < MEAS_MIN_DPDT || MaxdPdt > MEAS_MAX_DPDT)
  {
    MsgBox_show(TWARNING,
                MSG_VALIDATION_ERROR,
                LoadStr(MSG_DPDT_OUT) +RoundIntToStr(MaxdPdt),
                MSG_DPDT_OUT, "");
  }

  // Quality control parameters
  if (QC_PulseHeightVariation > 15 && QC_DiastolicVariation > 15 &&
      QC_ShapeDeviation > 15)
  {
    MsgBox(TERROR, GetCurrentPwaMeasureDetails(), MSG_VALIDATION_ERROR,
           MSG_PWA_TOO_BAD_SIGNAL);
    return false;
  }

  // return
  return true;
}
/* ###########################################################################
 ** Store()
 **
 ** DESCRIPTION
 **  Store class properties to current record in pDataSet
 ** INPUT
 **  pDataSet - TADOQuery or TADOTable
 ** OUTPUT
 **  none
*/
//---------------------------------------------------------------------------
bool TPressurePeriph::StoreDBase(TDataSet* pDataSet)
{
  try
  {
    // Store Variables
    pDataSet->FieldByName(MPWA_P_MAX_DPDT)->AsInteger = MaxdPdt;
    // pDataSet->FieldByName(MPWA_P_SPARE1)->AsInteger = PSpare1;

    // Ejection duration stored only for peripheral
    pDataSet->FieldByName(MPWA_ED)->AsInteger = ED;

    // Store base TPressure class
    if (TPressure::StoreDBase(pDataSet, PERIPH_PREFIX)==false)
      return false;
  }
  catch (Exception &exception)
  {
    MsgBox(TERROR, GetCurrentPwaMeasureDetails(), MSG_DBREADWRITE_ERROR, MSG_ERR_READDB,
           LoadStr(MSG_ERR_READDB) + exception.Message);
    return false;
  }

  return true;
}
//---------------------------------------------------------------------------
bool TPressurePeriph::StoreAccess(TDataSet* pDataSet)
{
  try
  {
    // Store Variables
    pDataSet->FieldByName(MPWA_P_MAX_DPDT)->AsFloat = MaxdPdt;

    // Ejection duration stored only for peripheral
    pDataSet->FieldByName(MPWA_ED)->AsFloat = ED;

    // If there is no field CalcED in DB, do not store CalcED
    if (pDataSet->FindField(MPWA_CALC_ED) != NULL)
    {
      pDataSet->FieldByName(MPWA_CALC_ED)->AsFloat = CalcED;
    }

    // Additional for MSAccess
    pDataSet->FieldByName(MPWA_QUALITY_ED)->AsInteger = QualityED;
    pDataSet->FieldByName(MPWA_P_QC_PH)->AsFloat = QC_PulseHeight;
    pDataSet->FieldByName(MPWA_P_QC_PHV)->AsFloat = QC_PulseHeightVariation;
    pDataSet->FieldByName(MPWA_P_QC_PLV)->AsFloat = QC_PulseLengthVariation;
    pDataSet->FieldByName(MPWA_P_QC_DV)->AsFloat = QC_DiastolicVariation;
    pDataSet->FieldByName(MPWA_P_QC_SCALE_FACTOR)->AsInteger = qc_scale;
    pDataSet->FieldByName(MPWA_P_QC_SD)->AsFloat = QC_ShapeDeviation;
    pDataSet->FieldByName(MPWA_P_QC_OI)->AsFloat = OperatorIndex;

    // Store base TPressure class
    if (TPressure::StoreAccess(pDataSet, PERIPH_PREFIX)==false)
      return false;
  }
  catch (Exception &exception)
  {
    MsgBox(TERROR, GetCurrentPwaMeasureDetails(), MSG_DBREADWRITE_ERROR, MSG_ERR_READDB,
           LoadStr(MSG_ERR_READDB) +exception.Message);
    return false;
  }

  return true;
}
//----------------------------------------------------------------------
bool TPressurePeriph::ExportPrintTitle(TDataSet* pDataSet, String &pOut)
{
  // Actual printing title string
  try
  {
    pOut = pOut + pDataSet->FieldByName(MPWA_P_MAX_DPDT)->DisplayName + "\t";
    pOut = pOut + pDataSet->FieldByName(MPWA_ED)->DisplayName + "\t";
    pOut = pOut + pDataSet->FieldByName(MPWA_CALC_ED)->DisplayName + "\t";
    // Additional for MSAccess
    pOut = pOut + pDataSet->FieldByName(MPWA_QUALITY_ED)->DisplayName + "\t";
    pOut = pOut + pDataSet->FieldByName(MPWA_P_QC_PH)->DisplayName + "\t";
    pOut = pOut + pDataSet->FieldByName(MPWA_P_QC_PHV)->DisplayName + "\t";
    pOut = pOut + pDataSet->FieldByName(MPWA_P_QC_PLV)->DisplayName + "\t";
    pOut = pOut + pDataSet->FieldByName(MPWA_P_QC_DV)->DisplayName + "\t";
    pOut = pOut + "P_QC_SDEV" + "\t";
    pOut = pOut + "Operator Index\t";
    if (TPressure::ExportPrintTitle(pDataSet, PERIPH_PREFIX, pOut)==false)
      return false;
  }
  catch (Exception &exception)
  {
    MsgBox(TERROR, GetCurrentPwaMeasureDetails(), MSG_EXCEPTION, MSG_EXPORT_ERROR, LoadStr(MSG_EXPORT_ERROR) + exception.Message);
    return false;
  }
  // return at success
  return true;
}
//------------------------------------------------------------
bool TPressurePeriph::Export(String &pOut)
{
  // Export specific properties
  pOut = pOut + RoundIntToStr(MaxdPdt) + "\t";
  pOut = pOut + RoundIntToStr(ED) + "\t";
  pOut = pOut + RoundIntToStr(CalcED) + "\t";
  pOut = pOut + IntToStr(QualityED) + "\t";
  pOut = pOut + RoundIntToStr(QC_PulseHeight) + "\t";
  pOut = pOut + RoundIntToStr(QC_PulseHeightVariation) + "\t";
  pOut = pOut + RoundIntToStr(QC_PulseLengthVariation) + "\t";
  pOut = pOut + RoundIntToStr(QC_DiastolicVariation) + "\t";
  pOut = pOut + RoundIntToStr(QC_ShapeDeviation) + "\t";
  pOut = pOut + IntToStr(OperatorIndex) + "\t";
  // Populate base TPressure class
  if (TPressure::Export(pOut)==false)
    return false;
  // Success
  return true;
}

/* ###########################################################################
 ** ExtractFeatures()
 **
 ** DESCRIPTION
 **  Extract specific feature parameters for Periph Pressure
 ** INPUT
 ** int pSampleRate - Sample Rate
 ** TPressure class properties
 ** OUTPUT
 ** TPressure class properties
 ** RETURN
 **  boolean success or not
*/
//---------------------------------------------------------------------------
bool TPressurePeriph::ExtractFeatures(/*const int pSampleRate, */const int pED)
{
  PH = DEFAULT_VALUE;

  ED = (pED != DEFAULT_VALUE ? ExpPulse.IndexToTime(pED) : DEFAULT_VALUE);

  // Specific
  MaxdPdt = ExpPulse.MaxDerivative1(ExpPulse.Start, ExpPulse.Length()/2)
                     * ExpPulse.SampleRate;

  // Convert T1, T2, ED in time
  if (ExpPulse.T1 != DEFAULT_VALUE)
  {
     T1 = ExpPulse.IndexToTime(ExpPulse.T1);
  }
  if (ExpPulse.T2 != DEFAULT_VALUE)
  {
     T2 = ExpPulse.IndexToTime(ExpPulse.T2);
  }

  // Extract general features for pressure (without accounting SampleRate)
  if (TPressure::ExtractFeatures(/*pSampleRate, */pED)==false)
    return false;

   QualityED = ExpPulse.QualityED;
   if (Sp > Dp)
   {
      PH = Sp - Dp;
   }
   if (P1 != DEFAULT_VALUE && P2 != DEFAULT_VALUE && PH != DEFAULT_VALUE)
   {
      AGPH = ((P2 - P1) / PH) * 100.0;
   }
   CalculateOperatorIndex();
   return true;
}

// ###########################################################################
// Constructor for TPressureCentral Class
//---------------------------------------------------------------------------
TPressureCentral::TPressureCentral() : TPressure ()
{
  Initialise(0,0);
}
//---------------------------------------------------------------------------
// Class initialisator
//---------------------------------------------------------------------------
void TPressureCentral::Initialise(const int pSignalSampleRate, const int pExpPulseSampleRate)
{
  // Base class initialisation
  TPressure::Initialise(pSignalSampleRate, pExpPulseSampleRate);
  SetDefaults(PRESSURE_MAX_PPOINTS, NOF_TF_COEFF, pSignalSampleRate, pExpPulseSampleRate);
}
//---------------------------------------------------------------------------
// Set default values
//---------------------------------------------------------------------------
void TPressureCentral::SetDefaults(const int pNofPoints, const int pShift,
                                   const int pSignalSampleRate, const int pExpPulseSampleRate)
{
  // Base class defaulting
  TPressure::SetDefaults(pSignalSampleRate, pExpPulseSampleRate);

  // Specific properties initialisation

  // For central not all points accounted (pShift = NOF_TF_COEFF)
  // For NPROC pShift = 0;
  NofPoints = pNofPoints - pShift;

  AP = DEFAULT_VALUE;         // mmHg       Augmented Pressure
  AP_HR75 = DEFAULT_VALUE;    // mmHg       Augmented Pressure corrected for Heart Rate
  MPS = DEFAULT_VALUE;        // mmHg       Mean Pressure Systole
  MPD = DEFAULT_VALUE;        // mmHg       Mean Pressure Diastole
  TTI = DEFAULT_VALUE;        // mmHg.s/min Tension Time Index
  DTI = DEFAULT_VALUE;        // mmHg.s/min Diastolic Time Index
  SVI = DEFAULT_VALUE; 			// SubEndocardial Viability = DTI/TTI
  STI = DEFAULT_VALUE;        // Systolic Time Index
  ATI = DEFAULT_VALUE;        // Augmentation Time Index
  AL = DEFAULT_VALUE; 			// Augmentation Load

  Tr = DEFAULT_VALUE;

  // CSpare1 = 0;    // central spare data #1 (not used, set to 0)
  // CSpare2 = 0;    // central spare data #2 (not used, set to 0)

  HR = DEFAULT_VALUE;         // heart rate in bpm (beats per minute)
  Period = DEFAULT_VALUE;     // Pulse period

  DD = DEFAULT_VALUE;         // Diast duration
  DDPeriod = DEFAULT_VALUE;   // % DD of Period
  EDPeriod = DEFAULT_VALUE;   // % ED of Period
  PH = DEFAULT_VALUE;         // Pulse Height  = SP - DP;
  AGPH = DEFAULT_VALUE;       // AG/PH in %
  AGPH_HR75 = DEFAULT_VALUE;  // AG/PH in % normalised for Heart Rate 75

  P1Height = DEFAULT_VALUE;   // P1 Height = P1 - DP;

}
/* ###########################################################################
 ** Populate()
 **
 ** DESCRIPTION
 **  populate class properties from current record in pDataSet
 ** INPUT
 **  pDataSet - TADOQuery or TADOTable
 **  const int pSampleRate - Sample rate to calculate Add Features
 ** OUTPUT
 **  none
*/
//---------------------------------------------------------------------------
bool TPressureCentral::PopulateDBase(TDataSet* pDataSet, const int pSignalSampleRate,
                                     const int pExpPulseSampleRate, const int pDataRev)
{
  try
  {
    if (pDataSet->RecordCount <= 0)
      return false;

    // Pick Up Variables
    AP  = pDataSet->FieldByName(MPWA_C_AP)->AsInteger;
    ESP = pDataSet->FieldByName(MPWA_C_ESP)->AsInteger;
    MPS = pDataSet->FieldByName(MPWA_C_MPS)->AsInteger;
    MPD = pDataSet->FieldByName(MPWA_C_MPD)->AsInteger;
    TTI = pDataSet->FieldByName(MPWA_C_TTI)->AsInteger;
    DTI = pDataSet->FieldByName(MPWA_C_DTI)->AsInteger;
    SVI = pDataSet->FieldByName(MPWA_C_SVI)->AsInteger;
    Tr = DEFAULT_VALUE;

    // CSpare1 = pDataSet->FieldByName(MPWA_C_SPARE1)->AsInteger;
    // CSpare2 = pDataSet->FieldByName(MPWA_C_SPARE2)->AsInteger;

    HR = pDataSet->FieldByName(MPWA_HR)->AsInteger;   // heart rate in bpm (beats per minute)

    // Populate base TPressure class
    if (TPressure::PopulateDBase(pDataSet, CENTRAL_PREFIX, pSignalSampleRate,
                                 pExpPulseSampleRate, pDataRev)==false)
      return false;

    // Calculate specific non-database features
    if (NonDBaseFeatures(&CalAvPulse/*, pSampleRate*/)==false)
      return false;
  }
  catch (Exception &exception)
  {
    MsgBox(TERROR, GetCurrentPwaMeasureDetails(), MSG_DBREADWRITE_ERROR, MSG_ERR_READDB,
           LoadStr(MSG_ERR_READDB) +exception.Message);
    return false;
  }
  return true;
}
//---------------------------------------------------------------------------
bool TPressureCentral::PopulateAccess(TDataSet* pDataSet, const int pSignalSampleRate,
                                      const int pExpPulseSampleRate, const int pDataRev)
{
  try
  {
    if (pDataSet->RecordCount <= 0)
    {
       return false;
    }

    // Pick Up Variables
    AP  = pDataSet->FieldByName(MPWA_C_AP)->AsFloat;
    MPS = pDataSet->FieldByName(MPWA_C_MPS)->AsFloat;
    MPD = pDataSet->FieldByName(MPWA_C_MPD)->AsFloat;
    TTI = pDataSet->FieldByName(MPWA_C_TTI)->AsFloat;
    DTI = pDataSet->FieldByName(MPWA_C_DTI)->AsFloat;
    SVI = pDataSet->FieldByName(MPWA_C_SVI)->AsFloat;

    if (pDataSet->FindField(MPWA_C_T1R) != NULL)
    {
       Tr = pDataSet->FieldByName(MPWA_C_T1R)->AsFloat;
    }
    else
    {
       Tr = DEFAULT_VALUE;
    }
    if (pDataSet->FindField(MPWA_C_AL) != NULL)
    {
       AL = pDataSet->FieldByName(MPWA_C_AL)->AsFloat;
    }
    else
    {
       AL = DEFAULT_VALUE;
    }
    if (pDataSet->FindField(MPWA_C_ATI) != NULL)
    {
       ATI = pDataSet->FieldByName(MPWA_C_ATI)->AsFloat;
    }
    else
    {
       ATI = DEFAULT_VALUE;
    }

    HR = pDataSet->FieldByName(MPWA_HR)->AsFloat;

    // Additional for MSAccess
    Period = pDataSet->FieldByName(MPWA_C_PERIOD)->AsFloat;
    DD = pDataSet->FieldByName(MPWA_C_DD)->AsFloat;
    EDPeriod = pDataSet->FieldByName(MPWA_C_ED_PERIOD)->AsFloat;
    DDPeriod = pDataSet->FieldByName(MPWA_C_DD_PERIOD)->AsFloat;
    PH = pDataSet->FieldByName(MPWA_C_PH)->AsFloat;
    AGPH = pDataSet->FieldByName(MPWA_C_AGPH)->AsFloat;

    P1Height = pDataSet->FieldByName(MPWA_C_P1_HEIGHT)->AsFloat;

    // Populate base TPressure class
    if (TPressure::PopulateAccess(pDataSet, CENTRAL_PREFIX,
                                  pSignalSampleRate, pExpPulseSampleRate, pDataRev) == false)
    {
       return false;
    }
    if (AGPH != DEFAULT_VALUE && HR != DEFAULT_VALUE)
    {
       if (HR < 40 || HR > 110)
       {
          AGPH_HR75 = DEFAULT_VALUE;
          AP_HR75 = DEFAULT_VALUE;
       }
       else
       {
          float p2_calc = 0.0;
          AGPH_HR75 = -0.48 * (75 - HR) +AGPH;
          if (AGPH_HR75 < 0)
          {
             AP_HR75 = (AGPH_HR75 * PH / 100.0);
          }
          else
          {
             p2_calc = (((100.0 * P1) - (AGPH_HR75 * Dp)) / (100.0 - AGPH_HR75));
             AP_HR75 = p2_calc - P1;
          }
       }
    }
    else
    {
       AGPH_HR75 = DEFAULT_VALUE;
       AP_HR75 = DEFAULT_VALUE;
    }
  }
  catch (Exception &exception)
  {
    MsgBox(TERROR, GetCurrentPwaMeasureDetails(), MSG_DBREADWRITE_ERROR, MSG_ERR_READDB,
           LoadStr(MSG_ERR_READDB) +exception.Message);
    return false;
  }
  return true;
}

//------------------------------------------------------------
bool TPressureCentral::ExportPrintTitle(TDataSet* pDataSet, String &pOut)
{
  // Actual printing title string
  try
  {
    pOut = pOut + pDataSet->FieldByName(MPWA_C_AP)->DisplayName + "\t";
    pOut = pOut + "C_AP_HR75" + "\t";
    pOut = pOut + pDataSet->FieldByName(MPWA_C_MPS)->DisplayName + "\t";
    pOut = pOut + pDataSet->FieldByName(MPWA_C_MPD)->DisplayName + "\t";
    pOut = pOut + pDataSet->FieldByName(MPWA_C_TTI)->DisplayName + "\t";
    pOut = pOut + pDataSet->FieldByName(MPWA_C_DTI)->DisplayName + "\t";
    pOut = pOut + pDataSet->FieldByName(MPWA_C_SVI)->DisplayName + "\t";
    pOut = pOut + "C_AL" + "\t";
    pOut = pOut + "C_ATI" + "\t";

    pOut = pOut + pDataSet->FieldByName(MPWA_HR)->DisplayName + "\t";

    // Additional for MSAccess
    pOut = pOut + pDataSet->FieldByName(MPWA_C_PERIOD)->DisplayName + "\t";
    pOut = pOut + pDataSet->FieldByName(MPWA_C_DD)->DisplayName + "\t";
    pOut = pOut + pDataSet->FieldByName(MPWA_C_ED_PERIOD)->DisplayName + "\t";
    pOut = pOut + pDataSet->FieldByName(MPWA_C_DD_PERIOD)->DisplayName + "\t";
    pOut = pOut + pDataSet->FieldByName(MPWA_C_PH)->DisplayName + "\t";
    pOut = pOut + pDataSet->FieldByName(MPWA_C_AGPH)->DisplayName + "\t";
    pOut = pOut + "C_AGPH_HR75" + "\t";
    pOut = pOut + pDataSet->FieldByName(MPWA_C_P1_HEIGHT)->DisplayName + "\t";
    if (pDataSet->FindField(MPWA_C_T1R) != NULL)
    {
       pOut = pOut + pDataSet->FieldByName(MPWA_C_T1R)->DisplayName + "\t";
    }
    else
    {
       pOut = pOut + "C_T1R" + "\t";
    }
    // Populate base TPressure class
    if (TPressure::ExportPrintTitle(pDataSet, CENTRAL_PREFIX, pOut)==false)
      return false;
  }
  catch (Exception &exception)
  {
    MsgBox(TERROR, GetCurrentPwaMeasureDetails(), MSG_EXCEPTION, MSG_EXPORT_ERROR, LoadStr(MSG_EXPORT_ERROR) + exception.Message);
    return false;
  }
  // return at success
  return true;
}
//------------------------------------------------------------
bool TPressureCentral::Export(String &pOut)
{

  // Export specific properties
  pOut = pOut + RoundIntToStr(AP) + "\t";
  pOut = pOut + RoundIntToStr(AP_HR75) + "\t";
  pOut = pOut + RoundIntToStr(MPS) + "\t";
  pOut = pOut + RoundIntToStr(MPD) + "\t";
  pOut = pOut + RoundIntToStr(TTI) + "\t";
  pOut = pOut + RoundIntToStr(DTI) + "\t";
  pOut = pOut + RoundIntToStr(SVI) + "\t";
  pOut = pOut + RoundIntToStr(AL) + "\t";
  pOut = pOut + RoundIntToStr(ATI) + "\t";
  pOut = pOut + RoundIntToStr(HR) + "\t";
  pOut = pOut + RoundIntToStr(Period) + "\t";
  pOut = pOut + RoundIntToStr(DD) + "\t";
  pOut = pOut + RoundIntToStr(EDPeriod) + "\t";
  pOut = pOut + RoundIntToStr(DDPeriod) + "\t";
  pOut = pOut + RoundIntToStr(PH) + "\t";
  pOut = pOut + RoundIntToStr(AGPH) + "\t";
  pOut = pOut + RoundIntToStr(AGPH_HR75) + "\t";
  pOut = pOut + RoundIntToStr(P1Height) + "\t";
  pOut = pOut + RoundIntToStr(Tr) + "\t";
  // Populate base TPressure class
  if (TPressure::Export(pOut)==false)
    return false;
  // Success
  return true;
}

/* ###########################################################################
 ** StoreDBase()
 **
 ** DESCRIPTION
 **  Store class properties to current record in pDataSet
 ** INPUT
 **  pDataSet - TADOQuery or TADOTable
 ** OUTPUT
 **  none
 ** RETURN
 **  success or not
*/
//---------------------------------------------------------------------------
bool TPressureCentral::StoreDBase(TDataSet* pDataSet)
{
  try
  {
    // Store Variables
    pDataSet->FieldByName(MPWA_C_AP)->AsInteger = AP;
    pDataSet->FieldByName(MPWA_C_ESP)->AsInteger = ESP;
    pDataSet->FieldByName(MPWA_C_MPS)->AsInteger = MPS;
    pDataSet->FieldByName(MPWA_C_MPD)->AsInteger = MPD;
    pDataSet->FieldByName(MPWA_C_TTI)->AsInteger = TTI;
    pDataSet->FieldByName(MPWA_C_DTI)->AsInteger = DTI;
    pDataSet->FieldByName(MPWA_C_SVI)->AsInteger = SVI;


    pDataSet->FieldByName(MPWA_HR)->AsInteger = HR;

    // Populate base TPressure class
    if (TPressure::StoreDBase(pDataSet, CENTRAL_PREFIX)==false)
      return false;
  }
  catch (Exception &exception)
  {
    MsgBox(TERROR, GetCurrentPwaMeasureDetails(), MSG_DBREADWRITE_ERROR, MSG_ERR_READDB,
           LoadStr(MSG_ERR_READDB) + exception.Message);
    return false;
  }
  return true;
}
//---------------------------------------------------------------------------
bool TPressureCentral::StoreAccess(TDataSet* pDataSet)
{
  try
  {
    // Store Variables
    pDataSet->FieldByName(MPWA_C_AP)->AsFloat = AP;
    pDataSet->FieldByName(MPWA_C_MPS)->AsFloat = MPS;
    pDataSet->FieldByName(MPWA_C_MPD)->AsFloat = MPD;
    pDataSet->FieldByName(MPWA_C_TTI)->AsFloat = TTI;
    pDataSet->FieldByName(MPWA_C_DTI)->AsFloat = DTI;
    pDataSet->FieldByName(MPWA_C_SVI)->AsFloat = SVI;

    if (pDataSet->FindField(MPWA_C_T1R)!=NULL)
    {
       pDataSet->FieldByName(MPWA_C_T1R)->AsFloat = Tr;
    }
    if (pDataSet->FindField(MPWA_C_AL)!=NULL)
    {
       pDataSet->FieldByName(MPWA_C_AL)->AsFloat = AL;
    }
    if (pDataSet->FindField(MPWA_C_ATI)!=NULL)
    {
       pDataSet->FieldByName(MPWA_C_ATI)->AsFloat = ATI;
    }
    pDataSet->FieldByName(MPWA_HR)->AsFloat = HR;

    // Additional for MSAccess
    pDataSet->FieldByName(MPWA_C_PERIOD)->AsFloat = Period;
    pDataSet->FieldByName(MPWA_C_DD)->AsFloat = DD;
    pDataSet->FieldByName(MPWA_C_ED_PERIOD)->AsFloat = EDPeriod;
    pDataSet->FieldByName(MPWA_C_DD_PERIOD)->AsFloat = DDPeriod;
    pDataSet->FieldByName(MPWA_C_PH)->AsFloat = PH;
    pDataSet->FieldByName(MPWA_C_AGPH)->AsFloat = AGPH;
    pDataSet->FieldByName(MPWA_C_P1_HEIGHT)->AsFloat = P1Height;

    // Populate base TPressure class
    if (TPressure::StoreAccess(pDataSet, CENTRAL_PREFIX)==false)
      return false;
  }
  catch (Exception &exception)
  {
    MsgBox(TERROR, GetCurrentPwaMeasureDetails(), MSG_DBREADWRITE_ERROR, MSG_ERR_READDB,
           LoadStr(MSG_ERR_READDB) +exception.Message);
    return false;
  }
  return true;
}

/* ###########################################################################
 ** ValidateBeforeStore()
 **
 ** DESCRIPTION
 **  Validate TPressureCentral class properties before storing in database
 ** INPUT
 **  // const int pSampleRate - Sample Rate
 ** OUTPUT
 ** RETURN
 **  boolean success or not
*/
//---------------------------------------------------------------------------
bool TPressureCentral::ValidateBeforeStore()
{
  // General pressure validation
  if (TPressure::ValidateBeforeStore()==false)
    return false;

  bool ret = true;

  // Central Pressure validation
  if ((MPS != DEFAULT_VALUE) && ((MPS < Dp) || (MPS > Sp)))
  {
    MsgBox_show(TWARNING,
                MSG_VALIDATION_ERROR,
                LoadStr(MSG_MPS_OUT) + RoundIntToStr(MPS),
                MSG_MPS_OUT, "");
  }
  if ((MPD != DEFAULT_VALUE) && ((MPD < Dp) || (MPD > Sp)))
  {
    MsgBox_show(TWARNING,
                MSG_VALIDATION_ERROR,
                LoadStr(MSG_MPD_OUT) + RoundIntToStr(MPD),
                MSG_MPD_OUT, "");
  }

  if ((HR != DEFAULT_VALUE) && ((HR <= MIN_HR) || (HR > MAX_HR)))
  {
    MsgBox_show(TERROR,
                MSG_VALIDATION_ERROR,
                LoadStr(MSG_HR_OUT) +RoundIntToStr(HR),
                MSG_HR_OUT,
                LoadStr(MSG_HR_OUT) +RoundIntToStr(HR) +GetCurrentPwaMeasureDetails());
    HR = DEFAULT_VALUE;
    ret = false;
  }

  if ((ED!=DEFAULT_VALUE) && ((ED <= 0) || (ED >= Period)))
  {
    MsgBox_show(TERROR,
                MSG_VALIDATION_ERROR,
                LoadStr(MSG_INVALID_ED) + RoundIntToStr(ED),
                MSG_INVALID_ED,
                LoadStr(MSG_INVALID_ED) + RoundIntToStr(ED) +GetCurrentPwaMeasureDetails());
    ED = DEFAULT_VALUE;
    ret = false;
  }

  if (ESP!=DEFAULT_VALUE && ((math_Round(ESP) < math_Round(Dp)) || (math_Round(ESP) > math_Round(Sp))))
  {
    MsgBox_show(TWARNING,
                MSG_VALIDATION_ERROR,
                LoadStr(MSG_ESP_OUT) +RoundIntToStr(ESP),
                MSG_ESP_OUT, "");
  }

  if ((P1Height != DEFAULT_VALUE) && (P1Height < 5))
  {
    MsgBox_show(TWARNING,
                MSG_VALIDATION_ERROR,
                LoadStr(MSG_P1H_OUT) + RoundIntToStr(P1Height),
                MSG_P1H_OUT, "");
  }

  if ((AGPH != DEFAULT_VALUE) && ((AGPH <= -50) || (AGPH >= 50)))
  {
     MsgBox_show(TWARNING,
                 MSG_VALIDATION_ERROR,
                 LoadStr(MSG_AI_OUT) +RoundIntToStr(AGPH),
                 MSG_AI_OUT, "");
  }

  if (T2 == DEFAULT_VALUE)
  {
    AP = DEFAULT_VALUE;
    P2 = DEFAULT_VALUE;
    AI1 = DEFAULT_VALUE;
    AGPH = DEFAULT_VALUE;
  }

  return ret;
}

/* ###########################################################################
 ** ExtractFeatures()
 **
 ** DESCRIPTION
 **  Extract specific feature parameters (ED, HR, ...) for Cenral Pressure
 ** INPUT
 ** int pSampleRate - Sample Rate
 ** TPressure class properties
 ** OUTPUT
 ** TPressure class properties
 ** RETURN
 **  boolean success or not
*/
//---------------------------------------------------------------------------
bool TPressureCentral::ExtractFeatures(/*const int pSampleRate, */const int pED)
{
  AGPH = DEFAULT_VALUE;
  AGPH_HR75 = DEFAULT_VALUE;
  AP_HR75 = DEFAULT_VALUE;

  float Area1 = -DEFAULT_VALUE;
  float Area2 = -DEFAULT_VALUE;
  float Area3 = -DEFAULT_VALUE;
  float Area4 = -DEFAULT_VALUE;
  float Area5 = -DEFAULT_VALUE;

  if (ExpPulse.Validate()== false)
  {
     return false;
  }

  // SampleRate after pulse expanding (128 * 8)
  // int lSampleRate = pSampleRate * ExpandFactor;

  // Specific
  // float rate = 1000. / lSampleRate;
  Period = ExpPulse.IndexToTime(ExpPulse.End); //rate * (ExpPulse.Length() - 1);

  // Systolic-diastolic areas


  if (pED != DEFAULT_VALUE)
  {
    Area1 = ExpPulse.Integral(0,pED);
    Area2 = ExpPulse.Integral(pED, ExpPulse.End);
  }

  // Mean pressure systolic/diastolic
  if (pED != DEFAULT_VALUE && pED > 0 && Area1 > 0)
  {
     MPS = Area1/pED;
  }
  if (pED != DEFAULT_VALUE && pED < ExpPulse.End && Area2 > 0)
  {
     MPD = Area2/(ExpPulse.End - pED);
  }

  // Heart rate (bpm) = 60000./Period
  HR = float(60.*ExpPulse.SampleRate)/ExpPulse.End;

  if (Area1 > 0)
  {
     TTI = Area1 * 60. / ExpPulse.End;
  }

  if (Area2 > 0)
  {
     DTI = Area2 * 60. / ExpPulse.End;
  }
  if (Area1 > 0 && Area2 > 0)
  {
     SVI = Area2/Area1*100;
  }

  // Convert T1, T2, ED in time
  if (pED != DEFAULT_VALUE)
  {
     ED = ExpPulse.IndexToTime(pED);
  }
  else
  {
     ED = DEFAULT_VALUE;
  }

  if (ExpPulse.T1 != DEFAULT_VALUE)
  {
     T1 = ExpPulse.IndexToTime(ExpPulse.T1);
     /*
     float max_t1_for_period;
     max_t1_for_period =  0.19 * Period;
     if (max_t1_for_period > 225.)
     {
        max_t1_for_period = 225.;
     }
     if (max_t1_for_period < 125.)
     {
        max_t1_for_period = 125.;
     }
     if (T1 < 80 || T1 > max_t1_for_period)
     {
        T1 = DEFAULT_VALUE;
        ExpPulse.T1 = DEFAULT_VALUE;
     }
     */
  }

  if (ExpPulse.T2 != DEFAULT_VALUE)
  {
     T2 = ExpPulse.IndexToTime(ExpPulse.T2);
  }

  // Extract general features for pressure
  if (TPressure::ExtractFeatures(/*pSampleRate, */pED)==false)
    return false;

  if ((P1 != DEFAULT_VALUE) && (P2 != DEFAULT_VALUE))
  {
     AP  = P2 - P1;
  }

  if (ExpPulse.Tr != DEFAULT_VALUE && ExpPulse.Tr > 0)
  {
     Tr = ExpPulse.IndexToTime(ExpPulse.Tr);
  }

  // Non-database features
  if (NonDBaseFeatures(&ExpPulse) == false)
  {
     return false;
  }

  // AG/PH in %
  if ((PH != DEFAULT_VALUE) && (AP != DEFAULT_VALUE))
  {
     AGPH = AP/PH * 100;
  }

   if (AGPH != DEFAULT_VALUE && HR != DEFAULT_VALUE)
   {
      if (HR < 40 || HR > 110)
      {
         AGPH_HR75 = DEFAULT_VALUE;
         AP_HR75 = DEFAULT_VALUE;
      }
      else
      {
         float p2_calc = 0.0;
         AGPH_HR75 = -0.48 * (75 - HR) + AGPH;
         if (AGPH_HR75 < 0)
         {
            AP_HR75 = (AGPH_HR75 * PH / 100.0);
         }
         else
         {
            p2_calc = (((100.0 * P1) - (AGPH_HR75 * Dp)) / (100.0 - AGPH_HR75));
            AP_HR75 = p2_calc - P1;
         }
      }
   }
   else
   {
      AGPH_HR75 = DEFAULT_VALUE;
      AP_HR75 = DEFAULT_VALUE;
   }

   // Only calculate Augmentation Load if Augmentation Pressure is positive
   if (AP > 0)
   {
      if (pED != DEFAULT_VALUE && ExpPulse.T1 != DEFAULT_VALUE && ExpPulse.T2 != DEFAULT_VALUE && ESP != DEFAULT_VALUE && P1 != DEFAULT_VALUE)
      {
         if (P1 > ESP)
         {
            // Area drawing a flat line from T1 to T2 and then a diagonal to ED
            Area3 = (P1 - Dp) * (ExpPulse.T2 - ExpPulse.T1) + (((P1 + ESP) / 2) - Dp) * (pED - ExpPulse.T2);
         }
         else
         {
            // Area drawing a line from T1 to ED
            Area3 = (((P1 + ESP) / 2) - Dp) * (pED - ExpPulse.T1);
         }
         Area4 = ExpPulse.Integral(ExpPulse.T1, pED, Dp);
         Area5 = Area4 - Area3;
         Area4 = Area4 + ExpPulse.Integral(0, ExpPulse.T1, Dp);
      }
   }

   if (Area4 > 0)
   {
      STI = Area4 * 1000./ ExpPulse.SampleRate;
   }
   if (Area5 > 0)
   {
      ATI = Area5 * 60. / ExpPulse.End;
   }
   if (Area5 > 0 && Area4 > 0)
   {
      AL = Area5/Area4*100;
   }

   return true;
}
/* ###########################################################################
 ** NonDBaseFeatures()
 **
 ** DESCRIPTION
 **  Calculate specific non-database features for Cenral Pressure
 ** INPUT
 ** TPressureCentral class properties
 **  pPulse - pulse to extract data from (AvPulse when only populate
 **  data from DB, ExpPulse - when Calculate data)
 **  pSampleRate - Sample Rate (128 when populate, 1024 when calculate)
 ** OUTPUT
 ** TPressure class properties
 ** RETURN
 **  boolean success or not
*/
//---------------------------------------------------------------------------
bool TPressureCentral::NonDBaseFeatures(TPulse *pPulse/*, const int pSampleRate*/)
{
  // Initialisation
  Period = DEFAULT_VALUE;
  PH = DEFAULT_VALUE;
  P1Height = DEFAULT_VALUE;
  EDPeriod = DEFAULT_VALUE;
  DDPeriod = DEFAULT_VALUE;
  DD = DEFAULT_VALUE;

  if (pPulse->SampleRate <= 0)
  {
     return false;
  }

  float rate = 1000. / pPulse->SampleRate;

  // Period
  if (pPulse->Length() > 1)
  {
     Period = rate * (pPulse->Length() - 1);
  }

  // Other pressures
  if (Sp != DEFAULT_VALUE && Dp != DEFAULT_VALUE)
  {
     if (Sp > Dp)
     {
        PH  = Sp - Dp;
     }
  }

  if (P1 != DEFAULT_VALUE)
  {
     P1Height = P1 - Dp;
  }
  // ED dependants
  if (Period != DEFAULT_VALUE && Period > 0 && ED != DEFAULT_VALUE)
  {
    EDPeriod = float(ED)/Period * 100.;
    DDPeriod = 100 - EDPeriod;
    DD = Period - ED;
  }

  return true;
}

/* ###########################################################################
 ** RecalculateEDDependants()
 **
 ** DESCRIPTION
 **  Recalculate parameters depandant on pED
 ** INPUT
 **  pED - Entered UserED
 ** OUTPUT
 ** RETURN
 **  boolean success or not
*/
//---------------------------------------------------------------------------
bool TPressure::RecalculateEDDependants(const int pEDIndex/*, const int pSampleRate*/)
{
  if (pEDIndex == DEFAULT_VALUE || pEDIndex < 0)
    return true;
  ED = ExpPulse.IndexToTime(pEDIndex);
  ESP = ExpPulse.Value(pEDIndex);
  if (T1 != DEFAULT_VALUE)
  {
     T1ED = T1*1./ED * 100;
  }
  if (T2 != DEFAULT_VALUE)
  {
     T2ED = T2*1./ED * 100;
  }
  return ED > 0;
}

/* ###########################################################################
 ** RecalculateEDDependants()
 **
 ** DESCRIPTION
 **  Recalculate parameters depandant on pED
 ** INPUT
 **  pED - Entered UserED
 ** OUTPUT
 ** RETURN
 **  boolean success or not
*/
//---------------------------------------------------------------------------
bool TPressureCentral::RecalculateEDDependants(const int pEDIndex/*, const int pSampleRate*/)
{
  if (TPressure::RecalculateEDDependants(pEDIndex/*, pSampleRate*/)==false)
    return false;

  // Systolic-diastolic areas
  float Area1 = 0.0;
  float Area2 = 0.0;
  float Area3 = 0.0;
  float Area4 = 0.0;
  float Area5 = 0.0;
  int T1Index = DEFAULT_VALUE;
  int T2Index = DEFAULT_VALUE;

  Area1 = ExpPulse.Integral(0,pEDIndex);
  Area2 = ExpPulse.Integral(pEDIndex, ExpPulse.End);
  T1Index = ExpPulse.TimeToIndex(T1);
  T2Index = ExpPulse.TimeToIndex(T2);

  // Mean pressure systolic/diastolic
  if (Area1 > 0)
  {
     MPS = Area1/pEDIndex;
  }
  if (Area2 > 0)
  {
     MPD = Area2/(ExpPulse.End - pEDIndex);
  }

  if (Area1 > 0)
  {
     TTI = Area1 * 60. / ExpPulse.End;
  }
  if (Area2 > 0)
  {
     DTI = Area2 * 60. / ExpPulse.End;
  }
  if (Area1 > 0 && Area2 > 0)
  {
     SVI = Area2*1./Area1*100;
  }

   // Only calculate Augmentation Load if Augmentation Pressure is positive
   if (AP > 0)
   {
      if (pEDIndex != DEFAULT_VALUE && T1Index != DEFAULT_VALUE && T2Index != DEFAULT_VALUE && ESP != DEFAULT_VALUE && P1 != DEFAULT_VALUE)
      {
         if (P1 > ESP)
         {
            // Area drawing a flat line from T1 to T2 and then a diagonal to ED
            Area3 = (P1 - Dp) * (T2Index - T1Index) + (((P1 + ESP) / 2) - Dp) * (pEDIndex - T2Index);
         }
         else
         {
            // Area drawing a line from T1 to ED
            Area3 = (((P1 + ESP) / 2) - Dp) * (pEDIndex - T1Index);
         }
         Area4 = ExpPulse.Integral(T1Index, pEDIndex, Dp);
         Area5 = Area4 - Area3;
      }
   }

   if (Area4 > 0)
   {
      STI = Area4 * 1000./ ExpPulse.SampleRate;
   }
   if (Area5 > 0)
   {
      ATI = Area5 * 60. / ExpPulse.End;
   }
   if (Area5 > 0 && Area4 > 0)
   {
      AL = Area5/Area4*100;
   }

  // ED dependants
  if (Period != DEFAULT_VALUE && Period > 0 &&  ED != DEFAULT_VALUE)
  {
     EDPeriod = float(ED)/Period * 100.;
     DDPeriod = 100 - EDPeriod;
     DD = Period - ED;
  }

  // Success
  return true;
}

/* ###########################################################################
 ** RecalculateT1Dependants()
 **
 ** DESCRIPTION
 **  Recalculate parameters depandant on pT1
 ** INPUT
 **  pT1 - Entered UserT1
 ** OUTPUT
 ** RETURN
 **  boolean success or not
*/
//---------------------------------------------------------------------------
bool TPressureCentral::RecalculateT1Dependants(const int pT1Index)
{
   // Systolic-diastolic areas
   float Area3 = 0.0;
   float Area4 = 0.0;
   float Area5 = 0.0;
   int T2Index = DEFAULT_VALUE;

   T2Index = ExpPulse.TimeToIndex(T2);

   if (pT1Index == DEFAULT_VALUE || pT1Index < 0)
      return true;
   T1 = ExpPulse.IndexToTime(pT1Index);
   P1 = ExpPulse.Value(pT1Index);
   if (ED != DEFAULT_VALUE)
   {
      T1ED = T1*1./ED * 100;
   }

   // Augmentation Index
   float P0 = ExpPulse.Profile[ExpPulse.Start];
   if ((P1 != DEFAULT_VALUE) && (P2 != DEFAULT_VALUE) && (P1 - P0 > 0))
   {
  	   AI1 = (P2 - P0)/(P1 - P0) * 100;
   }

   // Augmentation Pressure
   if ((P1 != DEFAULT_VALUE) && (P2 != DEFAULT_VALUE))
   {
      AP = P2 - P1;
   }

   // P1 Height
   if (P1 != DEFAULT_VALUE)
   {
      P1Height = P1 - Dp;
   }

   // AG/PH in %
   if ((PH != DEFAULT_VALUE) && (AP != DEFAULT_VALUE))
   {
      AGPH = AP/PH * 100;
   }

   if (AGPH != DEFAULT_VALUE && HR != DEFAULT_VALUE)
   {
      if (HR < 40 || HR > 110)
      {
         AGPH_HR75 = DEFAULT_VALUE;
         AP_HR75 = DEFAULT_VALUE;
      }
      else
      {
         float p2_calc = 0.0;
         AGPH_HR75 = -0.48 * (75 - HR) + AGPH;
         if (AGPH_HR75 < 0)
         {
            AP_HR75 = (AGPH_HR75 * PH / 100.0);
         }
         else
         {
            p2_calc = (((100.0 * P1) - (AGPH_HR75 * Dp)) / (100.0 - AGPH_HR75));
            AP_HR75 = p2_calc - P1;
         }
      }
   }
   else
   {
      AGPH_HR75 = DEFAULT_VALUE;
      AP_HR75 = DEFAULT_VALUE;
   }

   // Only calculate Augmentation Load if Augmentation Pressure is positive
   if (AP > 0)
   {
      if (ExpPulse.ED != DEFAULT_VALUE && pT1Index != DEFAULT_VALUE && T2Index != DEFAULT_VALUE && ESP != DEFAULT_VALUE && P1 != DEFAULT_VALUE)
      {
         if (P1 > ESP)
         {
            // Area drawing a flat line from T1 to T2 and then a diagonal to ED
            Area3 = (P1 - Dp) * (T2Index - pT1Index) + (((P1 + ESP) / 2) - Dp) * (ExpPulse.ED - T2Index);
         }
         else
         {
            // Area drawing a line from T1 to ED
            Area3 = (((P1 + ESP) / 2) - Dp) * (ExpPulse.ED - pT1Index);
         }
         Area4 = ExpPulse.Integral(pT1Index, ExpPulse.ED, Dp);
         Area5 = Area4 - Area3;
         Area4 = Area4 + ExpPulse.Integral(0, pT1Index, Dp);
      }
   }

   if (Area4 > 0)
   {
      STI = Area4 * 1000./ ExpPulse.SampleRate;
   }
   if (Area5 > 0)
   {
      ATI = Area5 * 60. / ExpPulse.End;
   }
   if (Area5 > 0 && Area4 > 0)
   {
      AL = Area5/Area4*100;
   }

   return T1 > 0;
}

/* ###########################################################################
 ** RecalculateT2Dependants()
 **
 ** DESCRIPTION
 **  Recalculate parameters depandant on pT2
 ** INPUT
 **  pT2 - Entered UserT2
 ** OUTPUT
 ** RETURN
 **  boolean success or not
*/
//---------------------------------------------------------------------------
bool TPressureCentral::RecalculateT2Dependants(const int pT2Index)
{
   // Systolic-diastolic areas
   float Area3 = 0.0;
   float Area4 = 0.0;
   float Area5 = 0.0;
   int T1Index = DEFAULT_VALUE;

   T1Index = ExpPulse.TimeToIndex(T1);

   if (pT2Index == DEFAULT_VALUE || pT2Index < 0)
      return true;
   T2 = ExpPulse.IndexToTime(pT2Index);
   P2 = ExpPulse.Value(pT2Index);
   if (ED != DEFAULT_VALUE)
   {
      T2ED = T2*1./ED * 100;
   }

   // Augmentation Index
   float P0 = ExpPulse.Profile[ExpPulse.Start];
   if ((P1 != DEFAULT_VALUE) && (P2 != DEFAULT_VALUE) && (P1 - P0 > 0))
   {
  	   AI1 = (P2 - P0)/(P1 - P0) * 100;
   }

   // Augmentation Pressure
   if ((P1 != DEFAULT_VALUE) && (P2 != DEFAULT_VALUE))
   {
      AP = P2 - P1;
   }

   // AG/PH in %
   if ((PH != DEFAULT_VALUE) && (AP != DEFAULT_VALUE))
   {
      AGPH = AP/PH * 100;
   }

   if (AGPH != DEFAULT_VALUE && HR != DEFAULT_VALUE)
   {
      if (HR < 40 || HR > 110)
      {
         AGPH_HR75 = DEFAULT_VALUE;
         AP_HR75 = DEFAULT_VALUE;
      }
      else
      {
         float p2_calc = 0.0;
         AGPH_HR75 = -0.48 * (75 - HR) + AGPH;
         if (AGPH_HR75 < 0)
         {
            AP_HR75 = (AGPH_HR75 * PH / 100.0);
         }
         else
         {
            p2_calc = (((100.0 * P1) - (AGPH_HR75 * Dp)) / (100.0 - AGPH_HR75));
            AP_HR75 = p2_calc - P1;
         }
      }
   }
   else
   {
      AGPH_HR75 = DEFAULT_VALUE;
      AP_HR75 = DEFAULT_VALUE;
   }

   // Only calculate Augmentation Load if Augmentation Pressure is positive
   if (AP > 0)
   {
      if (ExpPulse.ED != DEFAULT_VALUE && T1Index != DEFAULT_VALUE && ESP != DEFAULT_VALUE && P1 != DEFAULT_VALUE)
      {
         if (P1 > ESP)
         {
            // Area drawing a flat line from T1 to T2 and then a diagonal to ED
            Area3 = (P1 - Dp) * (pT2Index - T1Index) + (((P1 + ESP) / 2) - Dp) * (ExpPulse.ED - pT2Index);
         }
         else
         {
            // Area drawing a line from T1 to ED
            Area3 = (((P1 + ESP) / 2) - Dp) * (ExpPulse.ED - T1Index);
         }
         Area4 = ExpPulse.Integral(T1Index, ExpPulse.ED, Dp);
         Area5 = Area4 - Area3;
         Area4 = Area4 + ExpPulse.Integral(0, T1Index, Dp);
      }
   }

   if (Area4 > 0)
   {
      STI = Area4 * 1000./ ExpPulse.SampleRate;
   }
   if (Area5 > 0)
   {
      ATI = Area5 * 60. / ExpPulse.End;
   }
   if (Area5 > 0 && Area4 > 0)
   {
      AL = Area5/Area4*100;
   }

   return T2 > 0;
}



