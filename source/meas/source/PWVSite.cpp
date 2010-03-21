//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include <stdlib.h>
#include <math.h>

#include <msg\pubserv.h>
#include <meas\pubserv.h>
#include "PWVSite.h"
#include "Common.h"


//---------------------------------------------------------------------------
#pragma package(smart_init)
const int PWV_MIN_HEART_RATE = 20;
const int PWV_MAX_HEART_RATE = 200;

// Pulse is invalid if PulseLength percent of Average < 0.7 or > 1.3
const float PWV_MIN_VALID_PULSELENGTH_PERCENT = 0.70;
const float PWV_MAX_VALID_PULSELENGTH_PERCENT = 1.3;

const float PWV_ECG_PULSE_HEIGHT_PERCENT = 100./3;
const float PWV_VARIATION_COEFF = 1.65; // To reject extra short or long DeltaT

const float PWV_MIN_NOF_VALID_DT = 3; // Minimal number of Vaid DeltaT

// ###########################################################################
// Constructor and Destructor for TPWVSite Class
//---------------------------------------------------------------------------
TPWVSite::TPWVSite()
{
  // Allocate Signals
  Tonom.Allocate(PWVSITE_MAX_PPOINTS, PWVSITE_MAX_ONSETS);
  ECG.Allocate(PWVSITE_MAX_PPOINTS, PWVSITE_MAX_ONSETS);

  // Initialise
  Initialise(0);
}
//---------------------------------------------------------------------------
// Class initialisator
//---------------------------------------------------------------------------
void TPWVSite::Initialise(const int pSignalSampleRate)
{
  Tonom.Initialise(pSignalSampleRate);
  ECG.Initialise(pSignalSampleRate);

  MeasureType = PWV_NOF_MEASURES;
  Nof10s = 0;
  SetDefaults(pSignalSampleRate);
}

//---------------------------------------------------------------------------
// Set default values for calculated variables
//---------------------------------------------------------------------------
void TPWVSite::SetDefaults(const int pSignalSampleRate)
{
    // Variables initialisation
    NofDT = 0;
    NofValidDT = 0;
    Tonom.SetDefaults(pSignalSampleRate);
    ECG.SetDefaults(pSignalSampleRate);
    // Calculated values
    MeanDT = DEFAULT_VALUE;
    Deviation = DEFAULT_VALUE;
    deviation_ok = false;
    HeartRate = DEFAULT_VALUE;
    // onsets = -1
    for (int i = 0; i < PWVSITE_MAX_ONSETS; i++)
    {
      Tonom.FloatOnsets[i] = -1;
      ECG.FloatOnsets[i] = -1;
      DeltaT[i].Value = -1;
      DeltaT[i].Valid = false;
    }
}
//---------------------------------------------------------------------------
TPWVSite::~TPWVSite()
{
}

/* ###########################################################################
 ** PopulateDBase()
 **
 ** DESCRIPTION
 **  populate class properties from current record in pDataSet
 ** INPUT
 **  pDataSet - TADOQuery or TADOTable
 **  String pPrefix - "A_" for SiteA, "B_" for SiteB
 ** OUTPUT
 ** RETURN
 **  boolean success or not
*/
//---------------------------------------------------------------------------
bool TPWVSite::PopulateDBase(TDataSet* pDataSet, const String pPrefix, const int pSampleRate)
{
  // SetDefaults();
  if (pDataSet->RecordCount <= 0)
    return false;
  try
  {
    // Populate variables
    Nof10s = pDataSet->FieldByName(pPrefix + MPWV_NOPSETS)->AsInteger;
    NofValidDT = pDataSet->FieldByName(pPrefix + MPWV_NOVALDT)->AsInteger;
    MeasureType = PwvFindMeasureType(pDataSet->FieldByName(pPrefix + MPWV_SUBTYPE)->AsString);

    HeartRate = pDataSet->FieldByName(pPrefix + MPWV_HR)->AsFloat;
    MeanDT = pDataSet->FieldByName(pPrefix + MPWV_MDT)->AsFloat;
    Deviation = pDataSet->FieldByName(pPrefix + MPWV_STD)->AsFloat;
    if (Deviation > (0.06 * MeanDT)) // represents 6% of Mean DT
    {
       deviation_ok = false;
    }
    else
    {
       deviation_ok = true;
    }

    // Quality controls not stored in Dbase DB
    Tonom.QC_PulseHeight = DEFAULT_VALUE;
    Tonom.QC_PulseHeightVariation = DEFAULT_VALUE;
    Tonom.QC_PulseLengthVariation = DEFAULT_VALUE;
    Tonom.QC_BaseLineVariation = DEFAULT_VALUE;
    ECG.QC_PulseHeight = DEFAULT_VALUE;
    ECG.QC_PulseHeightVariation = DEFAULT_VALUE;
    ECG.QC_PulseLengthVariation = DEFAULT_VALUE;
    ECG.QC_BaseLineVariation = DEFAULT_VALUE;

    // DeltaT
    int NofBytes = min((int)(pDataSet->FieldByName(pPrefix + MPWV_DT)->AsString.Length()), (int) sizeof(DeltaT));
    if (UnpackFromString(DeltaT, pDataSet->FieldByName(pPrefix + MPWV_DT)->AsString, NofBytes)==false)
      return false;
    NofDT = pDataSet->FieldByName(pPrefix + MPWV_NODT)->AsInteger;

    // Tonometer, ECG
    Tonom.Populate(pDataSet, pPrefix + MPWV_TONPULSES, "", pPrefix + MPWV_TONON);
    ECG.Populate(pDataSet, pPrefix + MPWV_ECGPULSES, "", pPrefix + MPWV_ECGON);

    Tonom.GetFloatOnsetsFromArray(Tonom.NofOnsets, pSampleRate);
    ECG.GetFloatOnsetsFromArray(ECG.NofOnsets, pSampleRate);
  }
  catch (Exception &exception)
  {
    MsgBox(TERROR, GetCurrentPwvMeasureDetails(), MSG_DBREADWRITE_ERROR, MSG_ERR_READDB,
           LoadStr(MSG_ERR_READDB) + exception.Message);
    return false;
  }
  return true;
}
//---------------------------------------------------------------------------
bool TPWVSite::PopulateAccess(TDataSet* pDataSet, const String pPrefix)
{

  if (pDataSet->RecordCount <= 0)
    return false;
  try
  {
    // Populate variables
    Nof10s = pDataSet->FieldByName(pPrefix + MPWV_NOF_10_SETS)->AsInteger;
    // NofValidDT = pDataSet->FieldByName(pPrefix + MPWV_NOF_VALID_DT)->AsInteger;
    MeasureType = PwvFindMeasureType(pDataSet->FieldByName(pPrefix + MPWV_SUBTYPE)->AsString);

    HeartRate = pDataSet->FieldByName(pPrefix + MPWV_HR)->AsFloat;
    MeanDT = pDataSet->FieldByName(pPrefix + MPWV_MDT)->AsFloat;
    Deviation = pDataSet->FieldByName(pPrefix + MPWV_DEVIATION_DT)->AsFloat;
    if (Deviation > (0.06 * MeanDT)) // represents 6% of Mean DT
    {
       deviation_ok = false;
    }
    else
    {
       deviation_ok = true;
    }

    // Quality controls
    Tonom.QC_PulseHeight = pDataSet->FieldByName(pPrefix + MPWV_TON_QC_PH)->AsFloat;
    Tonom.QC_PulseHeightVariation = pDataSet->FieldByName(pPrefix + MPWV_TON_QC_PHV)->AsFloat;
    Tonom.QC_PulseLengthVariation = pDataSet->FieldByName(pPrefix + MPWV_TON_QC_PLV)->AsFloat;
    Tonom.QC_BaseLineVariation = pDataSet->FieldByName(pPrefix + MPWV_TON_QC_BLV)->AsFloat;
    ECG.QC_PulseHeight = pDataSet->FieldByName(pPrefix + MPWV_ECG_QC_PH)->AsFloat;
    ECG.QC_PulseHeightVariation = pDataSet->FieldByName(pPrefix + MPWV_ECG_QC_PHV)->AsFloat;
    ECG.QC_PulseLengthVariation = pDataSet->FieldByName(pPrefix + MPWV_ECG_QC_PLV)->AsFloat;
    ECG.QC_BaseLineVariation = pDataSet->FieldByName(pPrefix + MPWV_ECG_QC_BLV)->AsFloat;

    // Tonometer, ECG
    Tonom.Populate(pDataSet, pPrefix + MPWV_TON_WAVEFORM, "", pPrefix + MPWV_TON_ONSETS);
    ECG.Populate(pDataSet, pPrefix + MPWV_ECG_WAVEFORM, "", pPrefix + MPWV_ECG_ONSETS);

    //Next should be commented to permit negative onsets
    //Tonom.GetFloatOnsetsFromArray(Tonom.NofOnsets);
    //ECG.GetFloatOnsetsFromArray(ECG.NofOnsets);

    // DeltaT
    int NofBytes = min((int)(pDataSet->FieldByName(pPrefix + MPWV_DT)->AsString.Length()), (int) sizeof(DeltaT));
    if (UnpackFromString(DeltaT, pDataSet->FieldByName(pPrefix + MPWV_DT)->AsString, NofBytes)==false)
      return false;
    NofDT = NofBytes/(sizeof(float) + sizeof(short int));
    if (NofDT > PWVSITE_MAX_ONSETS)
      NofDT = PWVSITE_MAX_ONSETS;
    // Work out NofValidDT
    NofValidDT = 0;
    for (int i=0; i < NofDT; i++)
    {
      if (DeltaT[i].Valid == true)
        NofValidDT++;
    }
  }
  catch (Exception &exception)
  {
    MsgBox(TERROR, GetCurrentPwvMeasureDetails(), MSG_DBREADWRITE_ERROR, MSG_ERR_READDB,
           LoadStr(MSG_ERR_READDB) + exception.Message);
    return false;
  }
  return true;
}

/* ###########################################################################
 ** StoreAccess()
 **
 ** DESCRIPTION
 **  Store TPWVSite class properties to MSAccess database
 ** INPUT
 **  pDataSet - TADOQuery or TADOTable
 **  pPrefix = "A_" for SiteA, "B_" for SiteB
 ** OUTPUT
 **  none
 ** RETURN
 **  boolean success or not
*/
//---------------------------------------------------------------------------
bool TPWVSite::StoreAccess (TDataSet* pDataSet, const String pPrefix)
{
  try
  {
    // Store variables
    pDataSet->FieldByName(pPrefix + MPWV_SUBTYPE)->AsString = PWVMTypeAsString[MeasureType];
    pDataSet->FieldByName(pPrefix + MPWV_NOF_10_SETS)->AsInteger = Nof10s;
    // pDataSet->FieldByName(pPrefix + MPWV_NOF_VALID_DT)->AsInteger = NofValidDT;

    pDataSet->FieldByName(pPrefix + MPWV_HR)->AsFloat = HeartRate;
    pDataSet->FieldByName(pPrefix + MPWV_MDT)->AsFloat = MeanDT;
    pDataSet->FieldByName(pPrefix + MPWV_DEVIATION_DT)->AsFloat = Deviation;

    // Quality controls
    pDataSet->FieldByName(pPrefix + MPWV_TON_QC_PH)->AsFloat = Tonom.QC_PulseHeight;
    pDataSet->FieldByName(pPrefix + MPWV_TON_QC_PHV)->AsFloat = Tonom.QC_PulseHeightVariation;
    pDataSet->FieldByName(pPrefix + MPWV_TON_QC_PLV)->AsFloat = Tonom.QC_PulseLengthVariation;
    pDataSet->FieldByName(pPrefix + MPWV_TON_QC_BLV)->AsFloat = Tonom.QC_BaseLineVariation;
    pDataSet->FieldByName(pPrefix + MPWV_ECG_QC_PH)->AsFloat = ECG.QC_PulseHeight;
    pDataSet->FieldByName(pPrefix + MPWV_ECG_QC_PHV)->AsFloat = ECG.QC_PulseHeightVariation;
    pDataSet->FieldByName(pPrefix + MPWV_ECG_QC_PLV)->AsFloat = ECG.QC_PulseLengthVariation;
    pDataSet->FieldByName(pPrefix + MPWV_ECG_QC_BLV)->AsFloat = ECG.QC_BaseLineVariation;

    // DeltaT
    pDataSet->FieldByName(pPrefix + MPWV_DT)->AsString = PackToString(DeltaT, NofDT);

    // Tonometer, ECG
    Tonom.Store(pDataSet, pPrefix + MPWV_TON_WAVEFORM, "", pPrefix + MPWV_TON_ONSETS);
    ECG.Store(pDataSet, pPrefix + MPWV_ECG_WAVEFORM, "", pPrefix + MPWV_ECG_ONSETS);
  }
  catch (Exception &exception)
  {
    MsgBox(TERROR, GetCurrentPwvMeasureDetails(), MSG_DBREADWRITE_ERROR, MSG_ERR_READDB,
           LoadStr(MSG_ERR_READDB) + exception.Message);
    return false;
  }

  return true;
}

//--------------------------------------------------------------------------------
bool TPWVSite::ExportPrintTitle(TDataSet* pDataSet, String pPrefix, String &pOut)
{
  // Actual printing title string
  try
  {
    // Export specific properties
    pOut = pOut + pDataSet->FieldByName(pPrefix + MPWV_SUBTYPE)->DisplayName + "\t";
    pOut = pOut + pDataSet->FieldByName(pPrefix + MPWV_NOF_10_SETS)->DisplayName + "\t";
    pOut = pOut + pDataSet->FieldByName(pPrefix + MPWV_HR)->DisplayName + "\t";
    pOut = pOut + pDataSet->FieldByName(pPrefix + MPWV_MDT)->DisplayName + "\t";
    pOut = pOut + pDataSet->FieldByName(pPrefix + MPWV_DEVIATION_DT)->DisplayName + "\t";

    // Quality controls
    pOut = pOut + pDataSet->FieldByName(pPrefix + MPWV_TON_QC_PH)->DisplayName + "\t";
    pOut = pOut + pDataSet->FieldByName(pPrefix + MPWV_TON_QC_PHV)->DisplayName + "\t";
    pOut = pOut + pDataSet->FieldByName(pPrefix + MPWV_TON_QC_PLV)->DisplayName + "\t";
    pOut = pOut + pDataSet->FieldByName(pPrefix + MPWV_TON_QC_BLV)->DisplayName + "\t";
    pOut = pOut + pDataSet->FieldByName(pPrefix + MPWV_ECG_QC_PH)->DisplayName + "\t";
    pOut = pOut + pDataSet->FieldByName(pPrefix + MPWV_ECG_QC_PHV)->DisplayName + "\t";
    pOut = pOut + pDataSet->FieldByName(pPrefix + MPWV_ECG_QC_PLV)->DisplayName + "\t";
    pOut = pOut + pDataSet->FieldByName(pPrefix + MPWV_ECG_QC_BLV)->DisplayName + "\t";
/*
    // DeltaT
    pDataSet->FieldByName(pPrefix + MPWV_DT)->AsString = PackToString(DeltaT, NofDT);
    // Tonometer, ECG
    Tonom.Store(pDataSet, pPrefix + MPWV_TON_WAVEFORM, "", pPrefix + MPWV_TON_ONSETS);
    ECG.Store(pDataSet, pPrefix + MPWV_ECG_WAVEFORM, "", pPrefix + MPWV_ECG_ONSETS);
*/
  }
  catch (Exception &exception)
  {
    MsgBox(TERROR, GetCurrentPwvMeasureDetails(), MSG_EXCEPTION, MSG_EXPORT_ERROR, LoadStr(MSG_EXPORT_ERROR) + exception.Message);
    return false;
  }
  // return at success
  return true;
}

//------------------------------------------------------------
bool TPWVSite::Export(String &pOut)
{
  // Export specific properties
  pOut = pOut + PWVMTypeAsString[MeasureType] + "\t";
  pOut = pOut + IntToStr(Nof10s) + "\t";
  pOut = pOut + RoundIntToStr(HeartRate) + "\t";
  pOut = pOut + FormatFloat("###0.#", MeanDT) + "\t";
  pOut = pOut + FormatFloat("###0.#", Deviation) + "\t";
  // Quality controls
  pOut = pOut + FormatFloat("###0", Tonom.QC_PulseHeight) + "\t";
  pOut = pOut + FormatFloat("###0", Tonom.QC_PulseHeightVariation) + "\t";
  pOut = pOut + FormatFloat("###0", Tonom.QC_PulseLengthVariation) + "\t";
  pOut = pOut + FormatFloat("###0.#", Tonom.QC_BaseLineVariation) + "\t";
  pOut = pOut + FormatFloat("###0", ECG.QC_PulseHeight) + "\t";
  pOut = pOut + FormatFloat("###0", ECG.QC_PulseHeightVariation) + "\t";
  pOut = pOut + FormatFloat("###0", ECG.QC_PulseLengthVariation) + "\t";
  pOut = pOut + FormatFloat("###0.#", ECG.QC_BaseLineVariation) + "\t";

  // return at success
  return true;
}

/* ###########################################################################
 ** ValidateBeforeStore()
 **
 ** DESCRIPTION
 **  Validate TPWVSite class properties picked up from database
 ** INPUT
 **  // const int pSampleRate - Sample Rate
 ** OUTPUT
 ** RETURN
 **  boolean success or not
*/
//---------------------------------------------------------------------------
bool TPWVSite::ValidateBeforeStore()
{
  if (ValidateBeforeCalculate()==false)
    return false;

  if (Tonom.ValidateBeforeStore(PWV_MIN_SIGNAL_LENGTH, PWV_MIN_NOF_ONSETS, PWV_TON_MIN_PULSEHEIGHT)==false)
    return false;
  if (ECG.ValidateBeforeStore(PWV_MIN_SIGNAL_LENGTH, PWV_MIN_NOF_ONSETS, PWV_ECG_MIN_PULSEHEIGHT)==false)
    return false;
  return true;
}

/* ###########################################################################
 ** ValidateBeforeCalculate()
 **
 ** DESCRIPTION
 **  Validate TPWVSite class properties before Calculate PWV
 ** INPUT
 ** OUTPUT
 **   Class properties
 ** RETURN
 **  boolean success or not
*/
//---------------------------------------------------------------------------
bool TPWVSite::ValidateBeforeCalculate()
{
  bool ret1 = Tonom.ValidateSignal(PWV_MIN_SIGNAL_LENGTH);
  bool ret2 =   ECG.ValidateSignal(PWV_MIN_SIGNAL_LENGTH);
  bool ret = ret1 & ret2;
  return ret;
}

/* ###########################################################################
 ** Calculate()
 **
 ** DESCRIPTION
 **  Do all mathematics for a PWVSite class
 ** INPUT
 **  TPWVSite class (source)
 **   pAlgorithm - algorithm number (1,2,3,4) to find onsets for Tonometer signal
 **   pHeightPercent - percent of pulse height (20) to find onsets for Algorithm 1
 ** OUTPUT
 **  boolean success or not
*/
//---------------------------------------------------------------------------
bool TPWVSite::Calculate(const int   pAlgorithm,
                         const float pHeightPercent,
                         const int   pSampleRate,
                         const int   p_qc_scalefactor)
{
  // Validation
  if (ValidateBeforeCalculate()==false)
    return false;

  // Onsets
  if (Tonom.FindOnsets(pAlgorithm, pHeightPercent) == false)
  {
     return false;
  }

  if (ECG.FindOnsets(ECG_ALGORITHM_ONSET_FILTER,//ECG_ALGORITHM_ONSET_LENGTH,
                     PWV_ECG_PULSE_HEIGHT_PERCENT,
                     PWV_ECG_MIN_PULSEHEIGHT) == false)
  {
    return false;
  }

  // Delete last ECG onset if it is more than last Tonom onset
  if (ECG.FloatOnsets[ECG.NofOnsets - 1] >= Tonom.FloatOnsets[Tonom.NofOnsets - 1])
  {
     ECG.FloatOnsets[ECG.NofOnsets - 1] = -1;
     ECG.NofOnsets--;
  }

  // Quality controls
  if (Tonom.QualityControls()==false)
    return false;



  if (ECG.QualityControls()==false)
    return false;

  if (p_qc_scalefactor != DEFAULT_VALUE && p_qc_scalefactor != 0)
  {
     Tonom.QC_PulseHeight = Tonom.QC_PulseHeight / p_qc_scalefactor;
     ECG.QC_PulseHeight = ECG.QC_PulseHeight / p_qc_scalefactor;
  }

  // Heart rate
  if (CalcHeartRate(pSampleRate)==false)
    return false;

  // Delta T
  if (CalcDeltaT(pSampleRate)==false)
    return false;

  // Mean and Deviation
  if (MeanDeviation()==false)
    return false;

  return true;
}

/* ###########################################################################
 ** CalcHeartRate()
 **
 ** DESCRIPTION
 **  Calculate Heart rate on the base of ECG Onsets
 ** INPUT
 **  pSampleRate - Sample rate in Hz
 ** OUTPUT
 ** RETURN
 **  boolean success or not
*/
//---------------------------------------------------------------------------
bool TPWVSite::CalcHeartRate(const int pSampleRate)
{
  // Initialisation
  int lNofPulses = ECG.NofOnsets - 1;
  HeartRate = DEFAULT_VALUE;

  // Calculate AveragePulse Length
  double lAvLength = 0;
  int lNofValidPulses = 0;
  for (int i=0; i<lNofPulses; i++)
  {
    if (ECG.FloatOnsets[i+1] > 0 && ECG.FloatOnsets[i] > 0)
    {
      lAvLength += fabs(ECG.FloatOnsets[i+1]-ECG.FloatOnsets[i]);
      lNofValidPulses++;
    }
  }
  lAvLength /= lNofValidPulses;

  // Calc HR with rejecting extra short and long pulses
  double lSum = 0.;
  lNofValidPulses = 0;
  for (int i=0; i<lNofPulses; i++)
  {
    if (ECG.FloatOnsets[i+1] > 0 && ECG.FloatOnsets[i] > 0)
    {
      float PulseLength = ECG.FloatOnsets[i+1]-ECG.FloatOnsets[i];
      if ((PulseLength > lAvLength*PWV_MIN_VALID_PULSELENGTH_PERCENT) &&
          (PulseLength < lAvLength*PWV_MAX_VALID_PULSELENGTH_PERCENT))
      {
        lSum += PulseLength;
        lNofValidPulses++;
      }
    }
  }
  // Validate NofValidPulses
  if (lNofValidPulses <= 0 || lSum <= 0.)
  {
    MsgBox(TERROR, GetCurrentPwvMeasureDetails(), MSG_VALIDATION_ERROR, MSG_PWV_TOO_BAD_SIGNAL);
    return false;
  }
  // All OK
  HeartRate = (60. * pSampleRate) / (lSum / lNofValidPulses);
  // Validate HeartRate
  if (HeartRate < PWV_MIN_HEART_RATE || HeartRate > PWV_MAX_HEART_RATE)
  {
    MsgBox(TERROR, GetCurrentPwvMeasureDetails(), MSG_VALIDATION_ERROR, MSG_HR_OUT, LoadStr(MSG_HR_OUT) + RoundIntToStr(HeartRate));
    HeartRate = DEFAULT_VALUE;
    return false;
  }
  // Success
  return true;
}
/* ###########################################################################
 ** CalcDeltaT()
 **
 ** DESCRIPTION
 **  Calculate time difference between Tonom and ECG Onsets
 ** INPUT
 **  pSampleRate - Sample rate in Hz
 ** OUTPUT
 ** RETURN
 **  boolean success or not
*/
//---------------------------------------------------------------------------
bool TPWVSite::CalcDeltaT(const int pSampleRate)
{
  // Initialisation
  NofDT = 0;
  NofValidDT = 0;    // Actual number of valid DeltaT values
  for (int i=0; i<PWVSITE_MAX_ONSETS; i++)
  {
    RejectedOnsets[i] = -1;
  }
  // Mark all onsets as negatives
  for (int i=0; i<Tonom.NofOnsets; i++)
  {
    Tonom.FloatOnsets[i] = -Tonom.FloatOnsets[i];
  }
  for (int i=0; i<ECG.NofOnsets; i++)
  {
    ECG.FloatOnsets[i] = -ECG.FloatOnsets[i];
  }
  int lMaxNofOnsets = max (Tonom.NofOnsets, ECG.NofOnsets);
  int TonIndex = 0, ECGIndex = 0;
  // Loop
  for (int indDT = 0; indDT < lMaxNofOnsets; indDT++)
  {
    // Defaulting
    DeltaT[indDT].Value = -1.; //DEFAULT_VALUE;
    DeltaT[indDT].Valid = false;
    if (ECGIndex >= ECG.NofOnsets || TonIndex == Tonom.NofOnsets)
      break;
    // Get current onsets
    float TonOnset = fabs(Tonom.FloatOnsets[TonIndex]);
    float ECGOnset = fabs(ECG.FloatOnsets[ECGIndex]);
    // Comparison
    if (TonOnset > ECGOnset)
    {
      // Check additional ECG before TonOnset
      if (ECGIndex == ECG.NofOnsets - 1 || TonOnset < fabs(ECG.FloatOnsets[ECGIndex+1]))
      {
        DeltaT[NofDT].Value = (TonOnset - ECGOnset) * 1000. / pSampleRate;
        DeltaT[NofDT].Valid = true;
        ECG.FloatOnsets[ECGIndex] = fabs(ECG.FloatOnsets[ECGIndex]);
        Tonom.FloatOnsets[TonIndex] = fabs(Tonom.FloatOnsets[TonIndex]);
        RejectedOnsets[NofDT] = (short int) TonIndex; // Remember tonom Onset
        NofDT++;
        NofValidDT++;
        ECGIndex++;
        TonIndex++;
      }
      else
      {
        ECGIndex++;
        continue;
      }
    }
    else // TonOnset < ECGOnset
    {
      TonIndex++;
      continue;
    }
  }
  // Validation
  if (NofDT <= PWV_MIN_NOF_VALID_DT)
  {
    MsgBox(TERROR, GetCurrentPwvMeasureDetails(), MSG_MATH_ERROR,  MSG_PWV_CALCDELTAT_ERR);
    return false;
  }

  // Rejecting Dt values which aren't withing 1.65 Deviation of Mean
  // Setup limitations
  if (MeanDeviation()==false)
    return false;
  float lUpLimit = MeanDT + Deviation*PWV_VARIATION_COEFF;
  float lDownLimit = MeanDT - Deviation*PWV_VARIATION_COEFF;
  // Rejecting
  NofValidDT = 0;
  for (int i=0; i<NofDT; i++)
  {
    if (DeltaT[i].Valid == true)
    {
      if (DeltaT[i].Value >= lDownLimit && DeltaT[i].Value <= lUpLimit)
      {
        NofValidDT++;
      }
      else
      {
        // DeltaT[i].Value = -1.;
        DeltaT[i].Valid = false;
        // Mark Tonom Onset as invalid
        int lTonIndex = RejectedOnsets[i];
        if (lTonIndex >= 0 && lTonIndex < Tonom.NofOnsets)
        {
          Tonom.FloatOnsets[lTonIndex] = -fabs(Tonom.FloatOnsets[lTonIndex]);
        }
      }
    }
  }
  // Validation
  if (NofValidDT < PWV_MIN_NOF_VALID_DT || NofValidDT > NofDT)
  {
    MsgBox(TERROR, GetCurrentPwvMeasureDetails(), MSG_MATH_ERROR,  MSG_PWV_CALCDELTAT_ERR);
    return false;
  }
  // Success
  return true;
}
/* ###########################################################################
 ** MeanDeviation()
 **
 ** DESCRIPTION
 **  Calculate DeltaT average (MeanDt) and its standard deviation
 ** INPUT
 **  None
 ** OUTPUT
 **  None
 ** RETURN
 **  boolean success or not
*/
//---------------------------------------------------------------------------
bool TPWVSite::MeanDeviation()
{
  // Validation
  if (NofDT < PWV_MIN_NOF_VALID_DT || NofValidDT < PWV_MIN_NOF_VALID_DT)
    return false;
  // Initialisation
  MeanDT = DEFAULT_VALUE;
  Deviation = DEFAULT_VALUE;
  // Calculate MeanDt for valid Dt by averaging
  double lSum = 0;
  int lNofV = 0;
  for (int i=0; i<NofDT; i++)
  {
    if (DeltaT[i].Valid)
    {
      lSum += DeltaT[i].Value;
      lNofV++;
    }
  }
  // Correcting NofValiDT if it is not correspond
  if (NofValidDT != lNofV)
    NofValidDT = lNofV;
  // Averaging
  if (NofValidDT > 0)
    MeanDT = lSum / NofValidDT;
  else
    return false;

  // Validation
  if (MeanDT <= 0.)
    return false;

  // Calculate Deviation
  lSum = 0.;
  for (int i=0; i<NofDT; i++)
  {
    if (DeltaT[i].Valid)
    {
      lSum += pow(DeltaT[i].Value - MeanDT,2);
    }
  }
  Deviation = sqrt(lSum / NofValidDT);
  // Validation implemented later for 2 Sites
  if (Deviation > (0.06 * MeanDT)) // represents 6% of Mean DT
  {
     deviation_ok = false;
  }
  else
  {
     deviation_ok = true;
  }
  // Success
  return true;
}

