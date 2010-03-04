//---------------------------------------------------------------------------
#include <vcl.h>
#include <windef.h>
#pragma hdrstop
#include "pwv.h"
#include <meas\pubserv.h>
#include <msg\pubserv.h>
#include <patient\pubserv.h>
#include <export/pubserv.h>
#include <config/pubserv.h>
#include <cfr11/pubserv.h>
#include <math.h>
//---------------------------------------------------------------------------
const float PWV_MAX_DIST = 2000; // Maximal and minimal valid distances
const float PWV_MIN_DIST = 10;
const int PWV_MAX_PH_PERCENT = 50;
const float PWV_MAX_HR_DIFFERENCE = 5;
const float PWV_BIG_DEVIATION_PERCENT = 0.30; // Warning if deviation 30% of Mean
//---------------------------------------------------------------------------
#pragma package(smart_init)

static TPWV pwv;

TPWV*  meas_get_current_pwv (){ return &pwv; }

String meas_pwv_get_table_name()
{
  return MPWV;
}

/* ###########################################################################
 ** GetCurrentPwvMeasureDetails()
 **
 ** DESCRIPTION
 **  Get string with details about current measurement
 ** INPUT
 **  None
 ** OUTPUT
 **  None
 ** RETURN
 **  String with meas details
*/
//---------------------------------------------------------------------------
String GetCurrentPwvMeasureDetails()
{
  String ret = "";
  TPWV* pwv = meas_get_current_pwv();
  if (pwv==NULL) return ret;
  ret = " Patient :" + IntToStr(pwv->Patient_No);
  ret = ret + ", PWV Measurement :" + pwv->DateTime.DateTimeString();
  ret = ret + ", DataRevision :" + IntToStr(pwv->DataRev) +" ";
  return ret;
}
// ###########################################################################
// Public constructor for TPWV Measurement Class
//---------------------------------------------------------------------------
TPWV::TPWV() : TMeasure()
{
  Tonometer = CONFIG_DEFAULT_TONOMETER;
  Reason = "";
  AuditFlag = AUDIT_ORIGINAL;
  AuditChange = Now();

  // Initialise other properties
  Initialise();
}

//---------------------------------------------------------------------------
// Class initialisator
//---------------------------------------------------------------------------
void TPWV::Initialise()
{
  // Specific properties initialisation
  DistancePx = 0; //DEFAULT_VALUE;
  DistanceDt = 0; //DEFAULT_VALUE;
  Distance = 0; //DEFAULT_VALUE;
  DistanceError = DEFAULT_VALUE;
  Algorithm = 0;
  PHeightPercent = 0; // DEFAULT_VALUE;
  qc_scale = 1;
  hr_diff_ok = true;

  SetDefaults();

  // ECGGainType       ecg_gain;
  // ReadyToCapture = false;

  // Initialise Pressures
  SiteA.Initialise(SampleRate);
  SiteB.Initialise(SampleRate);
}
//---------------------------------------------------------------------------
// Set default values for calculated variables
//---------------------------------------------------------------------------
void TPWV::SetDefaults()
{
  MeanDT = DEFAULT_VALUE;
  DeviationDT = DEFAULT_VALUE;
  PWV = DEFAULT_VALUE;
  PWVError = DEFAULT_VALUE;
  hr_diff_ok = true;
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
bool TPWV::Populate(TDataSet* pDataSet)
{
  if (MSAccess==true)
    return PopulateAccess(pDataSet);
  else
    return PopulateDBase(pDataSet);
}
//---------------------------------------------------------------------------
bool TPWV::PopulateDBase(TDataSet* pDataSet)
{
  try
  {
    // Populate base Measure properties
    if (TMeasure::PopulateDBase(pDataSet)==false)
      return false;

    if (pDataSet->RecordCount <= 0)
    {
      Initialise();
      return false; //true;
    }

    String Med1 = pDataSet->FieldByName(MPWV_MED_1)->AsString;
    String Med2 = pDataSet->FieldByName(MPWV_MED_2)->AsString;
    String Med3 = pDataSet->FieldByName(MPWV_MED_3)->AsString;
    String Med4 = pDataSet->FieldByName(MPWV_MED_4)->AsString;
    Medication = Med1;
    if (Med2!="")
      Medication = Medication + "\r\n" + Med2;
    if (Med3!="")
      Medication = Medication + "\r\n" + Med3;
    if (Med4!="")
      Medication = Medication + "\r\n" + Med4;

    String Notes1 = pDataSet->FieldByName(MPWV_NOTES_1)->AsString;
    String Notes2 = pDataSet->FieldByName(MPWV_NOTES_2)->AsString;
    String Notes3 = pDataSet->FieldByName(MPWV_NOTES_3)->AsString;
    String Notes4 = pDataSet->FieldByName(MPWV_NOTES_4)->AsString;
    Notes = Notes1;
    if (Notes2!="")
      Notes = Notes + "\r\n" + Notes2;
    if (Notes3!="")
      Notes = Notes + "\r\n" + Notes3;
    if (Notes4!="")
      Notes = Notes + "\r\n" + Notes4;

    Height = pDataSet->FieldByName(MPWV_HEIGHT)->AsFloat;
    Weight = pDataSet->FieldByName(MPWV_WEIGHT)->AsFloat;
    Bmi = (Height > 0 && Height != DEFAULT_VALUE && Weight > 0 && Weight != DEFAULT_VALUE
          ? Weight / ((Height / 100.) * (Height / 100.)) : DEFAULT_VALUE);
    // Bmi = pDataSet->FieldByName(MPWV_BMI)->AsFloat;

    // Convert stored Metric values to Imperial values
    if (Height > 0 && Height != DEFAULT_VALUE)
    {
      int temp = math_Round(Height / CONVERT_INCH_TO_CM);
      Inch = temp % 12;
      Feet = temp / 12;
    }
    else
    {
      Inch = DEFAULT_VALUE;
      Feet = DEFAULT_VALUE;
    }
    Pound = (Weight > 0 && Weight != DEFAULT_VALUE
            ? math_Round(Weight / CONVERT_POUND_TO_KILO) : DEFAULT_VALUE);

    // Populate specific properties
    DistancePx = pDataSet->FieldByName(MPWV_PX_DIST)->AsFloat;
    DistanceDt = pDataSet->FieldByName(MPWV_DT_DIST)->AsFloat;
    Distance   = pDataSet->FieldByName(MPWV_PWV_DIST)->AsFloat;
    DistanceError = pDataSet->FieldByName(MPWV_DISTERR)->AsFloat;
    Algorithm = pDataSet->FieldByName(MPWV_ALGORITHM)->AsInteger;
    PHeightPercent = pDataSet->FieldByName(MPWV_PHEIGHT_PC)->AsFloat;

    MeanDT = pDataSet->FieldByName(MPWV_PP_MDT)->AsFloat;
    DeviationDT = pDataSet->FieldByName(MPWV_PP_SDEV)->AsFloat;
    PWV = pDataSet->FieldByName(MPWV_PWV)->AsFloat;
    PWVError = pDataSet->FieldByName(MPWV_PWVERR)->AsFloat;

    // Populate SiteA and SiteB Pressure
    bool ret1 = SiteA.PopulateDBase(pDataSet, PREFIX_A, SampleRate);
    bool ret2 = SiteB.PopulateDBase(pDataSet, PREFIX_B, SampleRate);
    if (fabs(SiteA.HeartRate - SiteB.HeartRate) > PWV_MAX_HR_DIFFERENCE)
    {
       hr_diff_ok = false;
    }
    return ret1 && ret2;
  }
  catch (Exception &exception)
  {
     MsgBox_show(TERROR,
                 MSG_EXCEPTION,
                 LoadStr(MSG_POP_EXC),
                 MSG_POP_EXC,
                 LoadStr(MSG_POP_EXC) +GetCurrentPwvMeasureDetails() +exception.Message);
    return false;
  }
}
//---------------------------------------------------------------------------
bool TPWV::PopulateAccess(TDataSet* pDataSet)
{
  try
  {
    // Populate base Measure properties
    if (TMeasure::PopulateAccess(pDataSet)==false)
    {
      return false;
    }
    if (pDataSet->RecordCount <= 0)
    {
      Initialise();
      return false; // true;
    }
    // Populate specific properties
    DistancePx = pDataSet->FieldByName(MPWV_PX_DIST)->AsFloat;
    DistanceDt = pDataSet->FieldByName(MPWV_DT_DIST)->AsFloat;
    Distance   = pDataSet->FieldByName(MPWV_PWV_DIST)->AsFloat;
    DistanceError = pDataSet->FieldByName(MPWV_PWV_DISTERR)->AsFloat;
    Algorithm = pDataSet->FieldByName(MPWV_ALGORITHM)->AsInteger;
    PHeightPercent = pDataSet->FieldByName(MPWV_PHEIGHT_PC)->AsFloat;

    MeanDT = pDataSet->FieldByName(MPWV_PP_MDT)->AsFloat;
    DeviationDT = pDataSet->FieldByName(MPWV_PP_DEVIATION)->AsFloat;
    PWV = pDataSet->FieldByName(MPWV_PWV)->AsFloat;
    PWVError = pDataSet->FieldByName(MPWV_PWVERR)->AsFloat;
    qc_scale = pDataSet->FieldByName(MPWV_QC_SCALE_FACTOR)->AsInteger;
    if (qc_scale == 0)
    {
       qc_scale = 1;
    }
    Tonometer = pDataSet->FieldByName(MPWV_TONOMETER)->AsInteger;

    // Populate Audit
    Reason = pDataSet->FieldByName(MPWV_AUDIT_REASON)->AsString;
    AuditFlag = (AUDIT_FLAG_TYPE)pDataSet->FieldByName(MPWV_AUDIT_FLAG)->AsInteger;
    Simulation = pDataSet->FieldByName(MPWV_SIMULATION)->AsInteger;
    // The Audit Datetime field is only available in audit mode
    if (pDataSet->FindField(MPWV_AUDIT_DATETIME)!= NULL)
    {
      AuditChange = pDataSet->FieldByName(MPWV_AUDIT_DATETIME)->AsDateTime;
    }

    // Populate SiteA and SiteB Pressure
    bool ret1 = SiteA.PopulateAccess(pDataSet, PREFIX_A);
    bool ret2 = SiteB.PopulateAccess(pDataSet, PREFIX_B);
    if (fabs(SiteA.HeartRate - SiteB.HeartRate) > PWV_MAX_HR_DIFFERENCE)
    {
       hr_diff_ok = false;
    }
    else
    {
       hr_diff_ok = true;
    }
    return ret1 && ret2;
  }
  catch (Exception &exception)
  {
     MsgBox_show(TERROR,
                 MSG_EXCEPTION,
                 LoadStr(MSG_POP_EXC),
                 MSG_POP_EXC,
                 LoadStr(MSG_POP_EXC) +GetCurrentPwvMeasureDetails() +exception.Message);
    return false;
  }
}

/* ###########################################################################
 ** Store()
 **
 ** DESCRIPTION
 **  Validate and Store class properties to current record in pDataSet
 ** INPUT
 **  pDataSet - TADOQuery or TADOTable
 **  pRewriteKeyFields - flag to rewrite primary key fields in database
 **  (when new measurement created) or simply update current record without
 **   rewriting key fields
 **  pRewriteDate - if true - date of measurement will be current datetime,
 **                 if false - keep existing
 ** OUTPUT
 **  none
*/
//---------------------------------------------------------------------------
bool TPWV::Store(TDataSet* pDataSet, const bool pRewriteKeyFields, const bool pRewriteDate)
{
  bool ret;
  if (MSAccess == true)
  {
    ret = StoreAccess(pDataSet, pRewriteKeyFields, pRewriteDate);
  }
  else
  {
    ret = StoreDBase(pDataSet, pRewriteKeyFields, pRewriteDate);
  }
  if (ret == false)
  {
    pDataSet->Cancel();
  }
  return ret;
}

//---------------------------------------------------------------------------
bool TPWV::StoreDBase(TDataSet* pDataSet, const bool pRewriteKeyFields, const bool pRewriteDate)
{
  // Store to Dbase currently not supported
  return StoreAccess(pDataSet, pRewriteKeyFields, pRewriteDate);
}
//---------------------------------------------------------------------------
bool TPWV::StoreAccess(TDataSet* pDataSet, const bool pRewriteKeyFields, const bool pRewriteDate)
{
  // DataSet should have already been prepared
  if (pDataSet->CanModify==false)
  {
     MsgBox_show(TERROR,
                 MSG_DBREADWRITE_ERROR,
                 LoadStr(MSG_NO_STORE),
                 MSG_NO_STORE,
                 LoadStr(MSG_NO_STORE) +GetCurrentPwvMeasureDetails());
     return false;
  }
  // Validation
  if (ValidateBeforeStore()==false)
    return false;

  // Actual storing

  // Append/Update base Measure class properties
  if (TMeasure::StoreAccess(pDataSet, pRewriteKeyFields, pRewriteDate)==false)
  {
    return false;
  }

  try
  {
    // Store specific properties
    pDataSet->FieldByName(MPWV_PX_DIST)->AsFloat = DistancePx;
    pDataSet->FieldByName(MPWV_DT_DIST)->AsFloat = DistanceDt;
    pDataSet->FieldByName(MPWV_PWV_DIST)->AsFloat = Distance;
    pDataSet->FieldByName(MPWV_PWV_DISTERR)->AsFloat = DistanceError;
    pDataSet->FieldByName(MPWV_ALGORITHM)->AsInteger = Algorithm;
    pDataSet->FieldByName(MPWV_PHEIGHT_PC)->AsFloat = PHeightPercent;

    pDataSet->FieldByName(MPWV_PP_MDT)->AsFloat = MeanDT;
    pDataSet->FieldByName(MPWV_PP_DEVIATION)->AsFloat = DeviationDT;
    pDataSet->FieldByName(MPWV_PWV)->AsFloat = PWV;
    pDataSet->FieldByName(MPWV_PWVERR)->AsFloat = PWVError;
    pDataSet->FieldByName(MPWV_QC_SCALE_FACTOR)->AsInteger = qc_scale;

    pDataSet->FieldByName(MPWV_TONOMETER)->AsInteger = Tonometer;
    pDataSet->FieldByName(MPWV_AUDIT_REASON)->AsString = Reason;
    pDataSet->FieldByName(MPWV_AUDIT_FLAG)->AsInteger = AuditFlag;
    pDataSet->FieldByName(MPWV_SIMULATION)->AsInteger = Simulation;

    // Store Sites
    bool ret1 = SiteA.StoreAccess(pDataSet, PREFIX_A);
    bool ret2 = SiteB.StoreAccess(pDataSet, PREFIX_B);
    bool ret = ret1 & ret2;
    if (ret==false)
      return false;
  }
  catch (Exception &exception)
  {
     MsgBox_show(TERROR,
                 MSG_EXCEPTION,
                 LoadStr(MSG_STORE_ERROR),
                 MSG_STORE_ERROR,
                 LoadStr(MSG_STORE_ERROR) +GetCurrentPwvMeasureDetails() +exception.Message);
    return false;
  }
  // Validation success. Try to post data
  try
  {
    pDataSet->Post();
  }
  catch (Exception &exception)
  {
     MsgBox_show(TERROR,
                 MSG_DBREADWRITE_ERROR,
                 LoadStr(MSG_POST_ERROR),
                 MSG_POST_ERROR,
                 LoadStr(MSG_POST_ERROR) +GetCurrentPwvMeasureDetails() +exception.Message);
    return false;
  }
  // return at success
  return true;
}

//------------------------------------------------------------
bool TPWV::ExportPrintTitle(TDataSet* pDataSet, String &pOut)
{
  // DataSet should have already been prepared
  if (pDataSet->RecordCount <= 0)
  {
    MsgBox_warning(LoadStr(MSG_NO_EXPORT), SWARNING);
    return false;
  }

  // Actual printing title string

  // ExportPrintTitle Measure class
  if (TMeasure::ExportPrintTitle(pDataSet, pOut)==false)
  {
    return false;
  }

  try
  {
    // Print specific properties
    pOut = pOut + pDataSet->FieldByName(MPWV_PX_DIST)->DisplayName + "\t";
    pOut = pOut + pDataSet->FieldByName(MPWV_DT_DIST)->DisplayName + "\t";
    pOut = pOut + pDataSet->FieldByName(MPWV_PWV_DIST)->DisplayName + "\t";
    pOut = pOut + pDataSet->FieldByName(MPWV_PWV_DISTERR)->DisplayName + "\t";
    pOut = pOut + pDataSet->FieldByName(MPWV_ALGORITHM)->DisplayName + "\t";
    pOut = pOut + pDataSet->FieldByName(MPWV_PHEIGHT_PC)->DisplayName + "\t";
    pOut = pOut + pDataSet->FieldByName(MPWV_PP_MDT)->DisplayName + "\t";
    pOut = pOut + pDataSet->FieldByName(MPWV_PP_DEVIATION)->DisplayName + "\t";
    pOut = pOut + pDataSet->FieldByName(MPWV_PWV)->DisplayName + "\t";
    pOut = pOut + pDataSet->FieldByName(MPWV_PWVERR)->DisplayName + "\t";
    pOut = pOut + "PTT SD\t";
    pOut = pOut + "Tonometer Serial Number\t";
  }
  catch (Exception &exception)
  {
    MsgBox(TERROR, GetCurrentPwvMeasureDetails(), MSG_EXPORT_ERROR, MSG_EXPORT_EXCEPTION,  LoadStr(MSG_EXPORT_EXCEPTION) + exception.Message);
    return false;
  }
  // Print Periph and Central Pressure
  bool ret1 = SiteA.ExportPrintTitle(pDataSet, PREFIX_A, pOut);
  bool ret2 = SiteB.ExportPrintTitle(pDataSet, PREFIX_B, pOut);
  bool ret = ret1 & ret2;
  // Final delimiter
  pOut.Delete(pOut.LastDelimiter("\t"),1);
  // return at success
  return ret;
}

//------------------------------------------------------------
bool TPWV::Export(String &pOut)
{
  // Actual printing properties

  // Export Measure class
  if (TMeasure::Export(pOut)==false)
  {
    return false;
  }
  // PM V9
  // Export the PTT SD
  float PWVSD = DeviationDT / MeanDT * 100.0;

  // Export specific properties
  pOut = pOut + RoundIntToStr(DistancePx) + "\t";
  pOut = pOut + RoundIntToStr(DistanceDt) + "\t";
  pOut = pOut + RoundIntToStr(Distance) + "\t";
  pOut = pOut + RoundIntToStr(DistanceError) + "\t";
  pOut = pOut + IntToStr(Algorithm) + "\t";
  pOut = pOut + IntToStr((int)PHeightPercent) + "\t";
  pOut = pOut + FormatFloat("###0.#", MeanDT) + "\t";
  pOut = pOut + FormatFloat("###0.#", DeviationDT) + "\t";
  pOut = pOut + FormatFloat("###0.#", PWV) + "\t";
  pOut = pOut + FormatFloat("###0.#", PWVError) + "\t";
  pOut = pOut + FormatFloat("###0.#", PWVSD) + "\t";
  pOut = pOut + IntToStr(Tonometer) + "\t";

  // Export Periph and Central Pressure
  bool ret1 = SiteA.Export(pOut);
  bool ret2 = SiteB.Export(pOut);
  bool ret = ret1 & ret2;
  // Final delimiter
  pOut.Delete(pOut.LastDelimiter("\t"),1);
  // return at success
  return ret;
}

//------------------------------------------------------------
bool TPWV::ExportArrays(int pFileHandle)
{
  if (pFileHandle <= 0)
    return false;
  // Printing title for Arrays
  String lOut = "\r\nSiteA Pressure \t Site A ECG \t SiteB Pressure \t Site B ECG\r\n";
  FileWrite(pFileHandle, lOut.c_str(), lOut.Length());

  // Printing arrays
  int lMaxSize = max(SiteA.Tonom.NofPoints, SiteB.Tonom.NofPoints);

  for (int i = 0; i < lMaxSize; i++)
  {
    lOut = "";
    if (i < SiteA.Tonom.NofPoints)
    {
      lOut = lOut + FormatFloat("####0.0#", SiteA.Tonom.Signal[i]);
    }
    if (i < SiteA.ECG.NofPoints)
    {
      lOut = lOut + "\t" + FormatFloat("####0.0#", SiteA.ECG.Signal[i]);
    }
    if (i < SiteB.Tonom.NofPoints)
    {
      lOut = lOut + "\t" + FormatFloat("####0.0#", SiteB.Tonom.Signal[i]);
    }
    if (i < SiteB.ECG.NofPoints)
    {
      lOut = lOut + "\t" + FormatFloat("####0.0#", SiteB.ECG.Signal[i]);
    }
    lOut = lOut + "\r\n";
    FileWrite(pFileHandle, lOut.c_str(), lOut.Length());
  }
  return true;
}

/* ###########################################################################
 ** ValidateBeforeCalculate()
 **
 ** DESCRIPTION
 **  Validate TPWV class properties before Calculation routine
 ** INPUT
 **  TPWV Class properties
 ** OUTPUT
 ** RETURN
 **  boolean success or not
*/
//---------------------------------------------------------------------------
bool TPWV::ValidateBeforeCalculate()
{
  bool ret = true;
  // Measure type
  if (SiteA.MeasureType == PWV_NOF_MEASURES || SiteB.MeasureType == PWV_NOF_MEASURES)
  {
    MsgBox_show(TWARNING,
                MSG_VALIDATION_ERROR,
                LoadStr(MSG_INVALID_MTYPE),
                MSG_INVALID_MTYPE,
                LoadStr(MSG_INVALID_MTYPE) +GetCurrentPwvMeasureDetails());
    ret = false;
  }
  if (SiteA.MeasureType == SiteB.MeasureType)
  {
    MsgBox_show(TWARNING,
                MSG_VALIDATION_ERROR,
                LoadStr(MSG_PWV_THE_SAME_TYPE),
                MSG_PWV_THE_SAME_TYPE, "");
    ret = false;
  }
  if (SiteA.MeasureType == PWV_DISTAL)
  {
    MsgBox(TERROR, GetCurrentPwvMeasureDetails(), MSG_VALIDATION_ERROR, MSG_PWV_SITEA_DISTAL);
    ret = false;
  }
  if (SiteB.MeasureType == PWV_PROXIMAL)
  {
    MsgBox(TERROR, GetCurrentPwvMeasureDetails(), MSG_VALIDATION_ERROR, MSG_PWV_SITEB_PROXIMAL);
    ret = false;
  }
  // Algorithm
  if (Algorithm < 1 || Algorithm > 4)
  {
    MsgBox(TERROR, GetCurrentPwvMeasureDetails(), MSG_VALIDATION_ERROR, MSG_PWV_INVALID_ALGORITHM,
           LoadStr(MSG_PWV_INVALID_ALGORITHM) + IntToStr(Algorithm));
    ret = false;
  }
  // Sample rate
  if (SampleRate < DefSampleRate)
  {
    MsgBox(TERROR, GetCurrentPwvMeasureDetails(), MSG_VALIDATION_ERROR, MSG_INVALID_SAMPLERATE,
           LoadStr(MSG_INVALID_SAMPLERATE) + IntToStr(SampleRate));
    ret = false;
  }
  // Pulse height percent
  if (Algorithm == 1 && (PHeightPercent <= 0 || PHeightPercent > PWV_MAX_PH_PERCENT))
  {
    MsgBox(TERROR, GetCurrentPwvMeasureDetails(), MSG_VALIDATION_ERROR, MSG_PWV_INVALID_PULSE_HEIGHT_PERCENT,
           LoadStr(MSG_PWV_INVALID_PULSE_HEIGHT_PERCENT) + IntToStr((int)PHeightPercent));
    ret = false;
  }
  // Distance
  if (CalculateDistance())
  {
    if (Distance < PWV_MIN_DIST || Distance > PWV_MAX_DIST)
    {
      MsgBox_show(TNOTIFICATION,
                  MSG_VALIDATION_ERROR,
                  LoadStr(MSG_PWV_INVALID_DISTANCE) +IntToStr((int)Distance) +"  [" +IntToStr((int)PWV_MIN_DIST) +"," +IntToStr((int)PWV_MAX_DIST) +"].",
                  MSG_PWV_INVALID_DISTANCE, "");
      ret = false;
    }
  }
  else
  {
    ret = false;
  }
  // Pressures Sp, Dp, Mp
  if (ValidateSpDpMp() == false)
  {
     ret = false;
  }

  // Height and Weight
  if (ValidateHtWt()==false)
  {
      ret = false;
  }

  // Site A, B Nof10s
  if (SiteA.Nof10s < 1 || (SiteA.Nof10s > 3 && SiteA.Nof10s != PWV_SHORT_STUDY_ID))
  {
    MsgBox(TERROR, GetCurrentPwvMeasureDetails(), MSG_VALIDATION_ERROR, MSG_PWV_INVALID_CAPTURE_TIME,
           LoadStr(MSG_PWV_INVALID_CAPTURE_TIME) + IntToStr(SiteA.Nof10s));
    ret = false;
  }
  if (SiteB.Nof10s < 1 || (SiteB.Nof10s > 3 && SiteB.Nof10s != PWV_SHORT_STUDY_ID))
  {
    MsgBox(TERROR, GetCurrentPwvMeasureDetails(), MSG_VALIDATION_ERROR, MSG_PWV_INVALID_CAPTURE_TIME,
           LoadStr(MSG_PWV_INVALID_CAPTURE_TIME) + IntToStr(SiteB.Nof10s));
    ret = false;
  }

  // Return
  return ret;
}

/* ###########################################################################
 ** ValidateBeforeStore()
 **
 ** DESCRIPTION
 **  Validate TPWV class properties before Store in database
 ** INPUT
 **  TPWV Class properties
 ** OUTPUT
 ** RETURN
 **  boolean success or not
*/
//---------------------------------------------------------------------------
bool TPWV::ValidateBeforeStore()
{
   float hr_diff = 0.0;
   UCOUNT report_age;

   report_age = patient_get_age_at_date(DateTime);

   // Heavy validation of properties before storing
   if (TMeasure::ValidateBeforeStore() == false)
   {
      return false;
   }
   if (ValidateBeforeCalculate() == false)
   {
      return false;
   }
   // Validate parameters
   // PWV Validation
   if (report_age >= PATIENT_YOUNG_AGE &&
         ((SiteA.MeasureType == PWV_CAROTID && SiteB.MeasureType == PWV_FEMORAL) ||
         (SiteA.MeasureType == PWV_FEMORAL && SiteB.MeasureType == PWV_CAROTID)))
   {
      if ((PWV > PWV_TOO_LARGE) || (PWV < PWV_TOO_SMALL))
      {
         // PM V9
         // Invalid PWV's are allowed but a warning is displayed
         if (MsgBox(LoadStr(MSG_PWV_INVALID_RANGE),
                   SCONFIRMATION,
                   MB_YESNO | MB_ICONQUESTION) == ID_NO)
         {
            return false;
         }
      }
   }
   // MeanDt and Deviation
   if (DeviationDT > PWV_BIG_DEVIATION_PERCENT*MeanDT)
   {
      MsgBox_show(TWARNING,
                  MSG_VALIDATION_ERROR,
                  LoadStr(MSG_PWV_DEVIATION_TOO_BIG) +FormatFloat("###.#", MeanDT) +", " +FormatFloat("##0.#", DeviationDT),
                  MSG_PWV_DEVIATION_TOO_BIG,
                  LoadStr(MSG_PWV_DEVIATION_TOO_BIG) +FormatFloat("###.#", MeanDT) +", " +FormatFloat("##0.#", DeviationDT));
   }
   hr_diff = fabs(SiteA.HeartRate - SiteB.HeartRate);
   if (hr_diff > PWV_MAX_HR_DIFFERENCE)
   {
      hr_diff_ok = false;
      MsgBox_show(TWARNING,
                  MSG_VALIDATION_ERROR,
                  LoadStr(MSG_PWV_HR_DIFFERENCE) +FormatFloat("###.#", hr_diff) +",  [HR diff > " +FormatFloat("###.#", PWV_MAX_HR_DIFFERENCE) +"].",
                  MSG_PWV_HR_DIFFERENCE,
                  LoadStr(MSG_PWV_HR_DIFFERENCE) +FormatFloat("###.#", hr_diff));
   }
   else
   {
      hr_diff_ok = true;
   }

  // Pressure class validation
  bool ret1 = SiteA.ValidateBeforeStore();
  bool ret2 = SiteB.ValidateBeforeStore();
  // Return
  return ret1 & ret2;
}
/* ###########################################################################
 ** Calculate ()
 **
 ** DESCRIPTION
 **  Do all mathematics for this measurement
 ** INPUT
 **  TPWV class (source)
 ** OUTPUT
 **  boolean success or not
*/
//---------------------------------------------------------------------------
bool TPWV::Calculate()
{
  try
  {
    // Default values for calculated variables
    SetDefaults();
    SiteA.SetDefaults(SampleRate);
    SiteB.SetDefaults(SampleRate);

    // Calculate Distance
    if (CalculateDistance() == false)
    {
       return false;
    }

    // Check necessary properties before calculation
    if (ValidateBeforeCalculate() == false)
    {
       return false;
    }

    // Check whether enough captured points
    if (SiteA.Tonom.ValidateSignal(PWV_MIN_SIGNAL_LENGTH)==false ||
        SiteA.ECG.ValidateSignal(PWV_MIN_SIGNAL_LENGTH)==false ||
        SiteB.Tonom.ValidateSignal(PWV_MIN_SIGNAL_LENGTH)==false ||
        SiteB.ECG.ValidateSignal(PWV_MIN_SIGNAL_LENGTH)==false)
    {
      return false;
    }

    // Onsets Points and Pulses
    if (SiteA.Calculate(Algorithm, PHeightPercent, SampleRate, qc_scale) == false)
    {
       return false;
    }
    if (SiteB.Calculate(Algorithm, PHeightPercent, SampleRate, qc_scale) == false)
    {
      return false;
    }

    // Calculate Main
    if (CalcMainFeatures() == false)
    {
       return false;
    }

    // Success
    return true;
  }
  catch (Exception &exception)
  {
     MsgBox(TERROR, GetCurrentPwvMeasureDetails(), MSG_MATH_ERROR, MSG_CALC_EXC,
            LoadStr(MSG_CALC_EXC) + exception.Message);
     return false;
  }
}
//---------------------------------------------------------------------------
bool TPWV::CalculateDistance()
{
  // Check whether Distance has been entered direcly
  if (Distance > 0)
    return true;

  // If not, calculate
  if (DistancePx < PWV_MIN_DIST || DistancePx > PWV_MAX_DIST ||
      DistanceDt < PWV_MIN_DIST || DistanceDt > PWV_MAX_DIST)
  {
    MsgBox_show(TWARNING,
                MSG_VALIDATION_ERROR,
                LoadStr(MSG_PWV_INVALID_DISTANCES) +IntToStr((int)DistancePx) + ", " +IntToStr((int)DistanceDt) +"  [" +IntToStr((int)PWV_MIN_DIST) +"," +IntToStr((int)PWV_MAX_DIST) +"].",
                MSG_PWV_INVALID_DISTANCES, "");
    return false;
  }
  Distance = DistanceDt - DistancePx;
  if (Distance < PWV_MIN_DIST || Distance > PWV_MAX_DIST)
  {
    MsgBox_show(TWARNING,
                MSG_VALIDATION_ERROR,
                LoadStr(MSG_PWV_INVALID_DISTANCES) + IntToStr((int)DistancePx) + "," + IntToStr((int)DistanceDt) +"  [" +IntToStr((int)PWV_MIN_DIST) +"," +IntToStr((int)PWV_MAX_DIST) +"].",
                MSG_PWV_INVALID_DISTANCES, "");
    return false;
  }
  return true;
}
/* ###########################################################################
 ** CalcMainFeatures()
 **
 ** DESCRIPTION
 **  Calculate PWV, MeanDt, Deviation for this measurement
 ** INPUT
 ** OUTPUT
 ** RETURN
 **  boolean success or not
*/
//---------------------------------------------------------------------------
bool TPWV::CalcMainFeatures()
{
  if ((SiteA.MeasureType == PWV_PROXIMAL) ||
      (SiteA.MeasureType == PWV_CAROTID) ||
      ((SiteA.MeasureType == PWV_FEMORAL) &&
      (SiteB.MeasureType == PWV_RADIAL)))
  {
    MeanDT = SiteB.MeanDT - SiteA.MeanDT;
  }
  else
  {
    MeanDT = SiteA.MeanDT - SiteB.MeanDT;
  }
  // Swapping sites if MeanDT is negative
  if (MeanDT < 0 && SiteA.MeasureType != PWV_PROXIMAL && SiteB.MeasureType != PWV_DISTAL)
  {
     MsgBox_show(TNOTIFICATION,
                 MSG_VALIDATION_ERROR,
                 LoadStr(MSG_PWV_NEGATIVE_DT) +FormatFloat("##0.#", MeanDT) +"\n\n" +LoadStr(MSG_PWV_SWAP_SITES),
                 MSG_PWV_NEGATIVE_DT,
                 LoadStr(MSG_PWV_NEGATIVE_DT) +FormatFloat("##0.#", MeanDT) +", " +GetCurrentPwvMeasureDetails());
    PWV_MEASURE_TYPE l = SiteA.MeasureType;
    SiteA.MeasureType = SiteB.MeasureType;
    SiteB.MeasureType = l;
  }

  // Validation
  MeanDT = fabs(MeanDT);
  DeviationDT = sqrt(pow(SiteA.Deviation,2) + pow(SiteB.Deviation,2));
  if (MeanDT <= 0. || DeviationDT >= MeanDT)
  {
     MsgBox_show(TERROR,
                MSG_VALIDATION_ERROR,
                LoadStr(MSG_PWV_DEVIATION_TOO_BIG) +FormatFloat("###.#", MeanDT) +", " +FormatFloat("##0.#", DeviationDT),
                MSG_PWV_DEVIATION_TOO_BIG,
                GetCurrentPwvMeasureDetails() +LoadStr(MSG_PWV_DEVIATION_TOO_BIG) +FormatFloat("###.#", MeanDT) +", " +FormatFloat("##0.#", DeviationDT));
    return false;
  }
  // PWV
  PWV = Distance / MeanDT;
  // PWV Error
  PWVError = (Distance/(MeanDT - DeviationDT) - Distance/(MeanDT + DeviationDT))/2;
  // Success
  return true;
}

/* ###########################################################################
 ** PrepareToCaptureSignal()
 **
 ** DESCRIPTION
 **  Preparing TPWV object to store signal
 ** INPUT
 **  none
 ** OUTPUT
 **  Appropriate properties have set up
 ** RETURN
 **  none
*/
//---------------------------------------------------------------------------
void TPWV::PrepareToCaptureSignal()
{
  // Clear up everything except Sp, Dp, Meanp ...
  SetDefaults();
  SiteA.SetDefaults(SampleRate);
  SiteB.SetDefaults(SampleRate);
  // Set up ready flags for Signals
  SiteA.Tonom.PrepareToCapture();
  SiteA.ECG.PrepareToCapture();
  SiteB.Tonom.PrepareToCapture();
  SiteB.ECG.PrepareToCapture();
}

bool TPWV::SaveToFile()
{
  PATIENT_RECORD_TYPE  pat;
  if (patient_get(&pat))
  {
    String lFileName = ExtractFilePath(Application->ExeName) + EXPORT_SUBDIR + "pwv_session_" +
                        pat.surname + "_" + DateTime.FormatString("ddmmmyyyy") + ".txt";

    DeleteFile(lFileName);
    int lFileHandle = FileCreate(lFileName);

    // Validation
    if (lFileHandle <= 0)
    {
        MsgBox(LoadStr(MSG_COMMS_NO_FILE) + lFileName + "\n\n" +
                LoadStr(MSG_COMMS_CHECK_FILENAME), SWARNING, MB_ICONSTOP);
        return false;
    }
    // Printing arrays
    if (ExportArrays(lFileHandle) == false)
    {
        return false;
    }

    FileClose(lFileHandle);
    return true;
  }
  return false;
}

