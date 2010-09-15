//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include <meas\pubserv.h>
#include <config\pubserv.h>
#include <patient\pubserv.h>
#include <msg\pubserv.h>
#include <scor\form_main.h>
#include <multdb\pubserv.h>
#include "form_pwa.h"
#include "form_pwv.h"
#include "form_pwm.h"
#include "form_hrv.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)

bool meas_initialise(void)
{
   bool meas_initialised = false;

  if (meas_pwa_initialise() && meas_pwv_initialise() && meas_pwm_initialise())
  {
     if (meas_hrv_initialise())
     {
        meas_initialised = true;
     }
  }
  return meas_initialised;
}

void meas_destroy(void)
{
   meas_hrv_destroy();
}

Child_Form  *meas_get_form_pointer()
{
   Child_Form    *meas_form;
   MEAS_ID_TYPE  meas_id;

   meas_id = patient_get_study_mode();

   switch (meas_id)
   {
      case MEAS_PWA_ID:
         meas_form = frm_measure_pwa;
         break;

      case MEAS_PWV_ID:
         if (frm_measure_pwv == NULL)
         {
            frm_measure_pwv = new Tfrm_measure_pwv(emma_get_main_form_pointer());
         }
         meas_form = frm_measure_pwv;
         break;

      case MEAS_PWM_ID:
         if (frm_measure_pwm == NULL)
         {
            frm_measure_pwm = new Tfrm_measure_pwm(emma_get_main_form_pointer());
         }
         meas_form = frm_measure_pwm;
         break;

      case MEAS_HRV_ID:
         if (frm_measure_hrv == NULL)
         {
            frm_measure_hrv = new Tfrm_measure_hrv(emma_get_main_form_pointer());
         }
         meas_form = frm_measure_hrv;
         break;

      default:
         meas_form = (Child_Form *)NULL;
         break;
   }
   return (meas_form);
}

/* ###########################################################################
 ** GetCurrentMeasureDetails()
 **
 ** DESCRIPTION
 **  Get string with details about current measurement
 ** INPUT
      None
 ** OUTPUT
      None
 ** RETURN
 **  String with meas details
*/
//---------------------------------------------------------------------------
String GetCurrentMeasureDetails()
{
  MEAS_ID_TYPE  meas_id;
  String        ret = "";

  meas_id = patient_get_study_mode();
  switch (meas_id)
  {
    case MEAS_PWA_ID:
       return GetCurrentPwaMeasureDetails();
    case MEAS_PWV_ID:
       return GetCurrentPwvMeasureDetails();
    case MEAS_PWM_ID:
       return GetCurrentPwmMeasureDetails();
    case MEAS_HRV_ID:
       return GetCurrentHRVMeasureDetails();
    default:
       break;
  }
  return ret;
}
/* ###########################################################################
 ** GetMeasureDateTime()
 **
 ** DESCRIPTION
 ** INPUT
 **  pDataSet - TADOQuery or TADOTable
 ** OUTPUT
 ** RETURN
 **  Date requested
*/
// return Date and time of measurement
//---------------------------------------------------------------------------
TDateTime GetMeasureDateTime(TDataSet* pDataSet)
{
   TDateTime lDateTime;
/*
  TDateTime lDateTime = StrToDateTime (pDataSet->FieldByName(MPW_DATE)->AsString + " " +
                                       pDataSet->FieldByName(MPW_TIME)->AsString);  // date and time of measurement
  return lDateTime;
*/
   MEAS_ID_TYPE meas_id = patient_get_study_mode();
   switch (meas_id)
   {
      case MEAS_PWA_ID:
      case MEAS_PWV_ID:
      case MEAS_HRV_ID:
         lDateTime = pDataSet->FieldByName(MPW_DATETIME)->AsDateTime;
         break;
      case MEAS_PWM_ID:
         lDateTime = pDataSet->FieldByName(MPWM_SESSION_START)->AsDateTime;
         break;
      default:
         break;
   }
   return lDateTime;
}
// PM CR
// ###########################################################################
// Public constructor for Measure Abstract Class
//---------------------------------------------------------------------------
TMeasure::TMeasure()
//---------------------------------------------------------------------------
{
  Initialise();
}
//---------------------------------------------------------------------------
void TMeasure::Initialise()
{
  System_ID = "";
  Patient_No = 0;                          // patient number
  Study_ID = "DATA";
  DateTime = Now();                        // date and time of measurement
  DateFormat = "dd/mm/yyyy";               // Date format
  DateTimeFormat = "dd/mm/yyyy hh:nn:ss";  // DateTime format
  Secs = 0;
  SecInc = 1;
  // DateFormat = get_date_format();
  DataRev = MEAS_MATH_DATA_REVISION;           // Data revision number

  MSAccess = true;
  ValidateSpDp = true;

  Medication = "";     // notes regarding medication for this patient
  Notes = "";          // miscellaneous notes for this measurement
  Operator = "";       // Operator ID
  Interpretation = ""; // notes regarding clinical interpretation for this patient

  Height = DEFAULT_VALUE; // patient height in cm
  Weight = DEFAULT_VALUE; // patient weight in kg
  Bmi = DEFAULT_VALUE;    // body mass index

  Feet = DEFAULT_VALUE;  // patient height in ft
  Inch = DEFAULT_VALUE;  // patient height in in
  Pound = DEFAULT_VALUE; // patient weight in lb

  Sp = 120;
  Dp = 80;
  MeanP = 0;

  // Age = 0;                                 // age at measurement date
  DefSampleRate = MEAS_DEFAULT_SAMPLE_RATE;   // default value in Htz
  SampleRate = DefSampleRate;  // default value in Htz
  Spare1 = "";

  Simulation = false;
}

void TMeasure::SetSampleRate(int pSampleRate)
{
   SampleRate = pSampleRate;
}

/* ###########################################################################
 ** Populate()
 **
 ** DESCRIPTION
 **  populate class properties from current record in pDataSet
 ** INPUT
 **  pDataSet - TADOQuery or TADOTable
 ** OUTPUT
 **  none
*/
//---------------------------------------------------------------------------
bool TMeasure::PopulateDBase(TDataSet* pDataSet)
{
  // SampleRate = DefSampleRate;
  if (pDataSet->RecordCount <= 0)
  {
    Initialise();
    System_ID = config_get_system_id();
    Patient_No = patient_get_number();
    Study_ID = multdb_get_active_name();
    return true;
  }

  try
  {
    System_ID   = pDataSet->FieldByName(MPW_SYSTEM_ID)->AsString;
    Patient_No  = pDataSet->FieldByName(MPW_PATIENT_NO)->AsInteger;
    Study_ID = multdb_get_active_name();

    // date and time of measurement
    DateTime    = StrToDateTime (pDataSet->FieldByName(MPW_DATE)->AsString + " " +
                                 pDataSet->FieldByName(MPW_TIME)->AsString);

    // Sp, Dp, Mp
    Sp = pDataSet->FieldByName(MPW_SP)->AsFloat;
    Dp = pDataSet->FieldByName(MPW_DP)->AsFloat;

    String StrDataRev = pDataSet->FieldByName(MPW_DATA_REV)->AsString;
    if (StrDataRev.ToIntDef(-1) > 0)
    {
      DataRev = StrDataRev.ToInt();
    }
    else
    {
      StrDataRev = StrDataRev.SubString(2, StrDataRev.Length()-1);
      if (StrDataRev.ToIntDef(-1) > 0)
      {
        DataRev = StrDataRev.ToInt();
      }
      else // Exception will be thrown and cought
      {
        DataRev = pDataSet->FieldByName(MPW_DATA_REV)->AsInteger;
      }
    }
    Operator    = pDataSet->FieldByName(MPW_OPERATOR)->AsString;
/*
    Height = pDataSet->FieldByName(MPW_HEIGHT)->AsFloat;
    Weight = pDataSet->FieldByName(MPW_WEIGHT)->AsFloat;
    Bmi = pDataSet->FieldByName(MPW_BMI)->AsFloat;
*/
  }
  catch (Exception &exception)
  {
     MsgBox_show(TERROR,
                 MSG_EXCEPTION,
                 LoadStr(MSG_POP_EXC),
                 MSG_POP_EXC,
                 LoadStr(MSG_POP_EXC) +GetCurrentMeasureDetails() +exception.Message);
     return false;
  }

  return true;
}
//---------------------------------------------------------------------------
bool TMeasure::PopulateAccess(TDataSet* pDataSet)
{
  MEAS_ID_TYPE           study_mode;

  if (pDataSet->RecordCount <= 0)
  {
    Initialise();
    System_ID = patient_get_system_id();
    Patient_No = patient_get_number();
    Study_ID = patient_get_study_id();
    return true;
  }

  System_ID   = pDataSet->FieldByName(MPW_SYSTEM_ID)->AsString;
  Study_ID    = pDataSet->FieldByName(MPW_STUDY_ID)->AsString;
  Patient_No  = pDataSet->FieldByName(MPW_PATIENT_NO)->AsInteger;

  DateTime    = pDataSet->FieldByName(MPW_DATETIME)->AsDateTime;

  Sp = pDataSet->FieldByName(MPW_SP)->AsFloat;
  Dp = pDataSet->FieldByName(MPW_DP)->AsFloat;
  MeanP = pDataSet->FieldByName(MPW_MP)->AsFloat;

  DataRev     = pDataSet->FieldByName(MPW_DATA_REV)->AsInteger;

  Medication  = pDataSet->FieldByName(MPW_MED)->AsString;

  Notes       = pDataSet->FieldByName(MPW_NOTES)->AsString;

  Operator    = pDataSet->FieldByName(MPW_OPERATOR)->AsString;

  // This is because HRV stores Interpretation in a different location
  if (pDataSet->FindField(MPW_INTERPRETATION)!=NULL)
  {
      Interpretation  = pDataSet->FieldByName(MPW_INTERPRETATION)->AsString;
  }
  else
  {
      Interpretation  = pDataSet->FieldByName(MHRV_INTERPRETATION)->AsString;
  }

  Height = pDataSet->FieldByName(MPW_HEIGHT)->AsFloat;
  Weight = pDataSet->FieldByName(MPW_WEIGHT)->AsFloat;
  Bmi = (Height > 0 && Height != DEFAULT_VALUE && Weight > 0 && Weight != DEFAULT_VALUE
        ? Weight / ((Height / 100.) * (Height / 100.)) : DEFAULT_VALUE);

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

  SampleRate = pDataSet->FieldByName(MPW_SAMPLE_RATE)->AsInteger;

  return true;
}
/* ###########################################################################
 ** ValidateBeforeStore()
 **
 ** DESCRIPTION
 **  Validate measure class properties before storing in database
 ** INPUT
 **  TPWA Class properties
 ** OUTPUT
 ** RETURN
 **  boolean success or not
*/
//---------------------------------------------------------------------------
bool TMeasure::ValidateBeforeStore()
{
  bool ret = true;
  if (System_ID=="")
  {
    MsgBox(TERROR, GetCurrentMeasureDetails(), MSG_VALIDATION_ERROR, MSG_NO_SYSTEMID);
    ret = false;
  }
  if (Patient_No <= 0)
  {
    MsgBox(TERROR, GetCurrentMeasureDetails(), MSG_VALIDATION_ERROR, MSG_NO_PATIENTNO);
    ret = false;
  }
  if (Study_ID=="")
  {
    MsgBox(TERROR, GetCurrentMeasureDetails(), MSG_VALIDATION_ERROR, MSG_NO_SYSTEMID);
    ret = false;
  }
  // Sample rate
  if (SampleRate < DefSampleRate)
  {
      MsgBox(TERROR, GetCurrentMeasureDetails(), MSG_VALIDATION_ERROR, MSG_INVALID_SAMPLERATE,
             LoadStr(MSG_INVALID_SAMPLERATE) + " " + IntToStr(SampleRate));
      ret = false;
  }

  if (ValidateSpDp)
  {
    if (ValidateSpDpMp()==false)
    {
      MsgBox(TERROR, GetCurrentMeasureDetails(), MSG_VALIDATION_ERROR, MSG_SPDPMP_VALIDATION_ERROR);
      ret = false;
    }
  }

  return ret;
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
bool TMeasure::StoreDBase(TDataSet* pDataSet, bool pRewriteKeyFields, bool pRewriteDate)
{
  try
  {
    if (pRewriteKeyFields) // Rewrite key fields
    {
      pDataSet->FieldByName(MPW_SYSTEM_ID)->AsString = System_ID;
      pDataSet->FieldByName(MPW_PATIENT_NO)->AsInteger = Patient_No;
    }
    if (pRewriteDate)
    {
      DateTime = TDateTime::CurrentDateTime();
    }
    DataRev  = MEAS_MATH_DATA_REVISION;
    pDataSet->FieldByName(MPW_DATE)->AsString = DateTime.FormatString(DateFormat);
    pDataSet->FieldByName(MPW_TIME)->AsString = DateTime.FormatString("hh:nn:ss");
    pDataSet->FieldByName(MPW_DATA_REV)->AsInteger = DataRev;

    // Sp, Dp, Mp
    pDataSet->FieldByName(MPW_SP)->AsInteger = Sp;
    pDataSet->FieldByName(MPW_DP)->AsInteger = Dp;
    // Pack MeanP to Spare field
    if (Spare1.Length() < 4) Spare1.SetLength(4);
    Spare1[4] = (unsigned char) MeanP;
    // Extract Secs from Spare field
    Spare1[1] = (unsigned char) Secs;

    pDataSet->FieldByName(MPW_DATA_REV)->AsInteger = MEAS_MATH_DATA_REVISION;
    pDataSet->FieldByName(MPW_OPERATOR)->AsString = Operator;

    return true;
  }
  catch (Exception &exception)
  {
     MsgBox_show(TERROR,
                 MSG_EXCEPTION,
                 LoadStr(MSG_STORE_ERROR),
                 MSG_STORE_ERROR,
                 LoadStr(MSG_STORE_ERROR) +GetCurrentMeasureDetails() +exception.Message);
    return false;
  }
}
//---------------------------------------------------------------------------
bool TMeasure::StoreAccess(TDataSet* pDataSet, bool pRewriteKeyFields, bool pRewriteDate)
{
  MEAS_ID_TYPE           study_mode;

  try
  {
    if (pRewriteKeyFields)
    {
      pDataSet->FieldByName(MPW_SYSTEM_ID)->AsString = System_ID;
      pDataSet->FieldByName(MPW_STUDY_ID)->AsString = Study_ID;
      pDataSet->FieldByName(MPW_PATIENT_NO)->AsInteger = Patient_No;
    }

    pDataSet->FieldByName(MPW_SP)->AsFloat = Sp;
    pDataSet->FieldByName(MPW_DP)->AsFloat = Dp;
    pDataSet->FieldByName(MPW_MP)->AsFloat = MeanP;

    if (pRewriteDate)
    {
      DateTime = Now();
    }
    // This is a fix to limit the precision of the DateTime field and allow equality tests, eg. Locate
    pDataSet->FieldByName(MPW_DATETIME)->AsDateTime = StrToDateTime(DateTimeToStr(DateTime));
    
    DataRev  = MEAS_MATH_DATA_REVISION;
    pDataSet->FieldByName(MPW_DATA_REV)->AsInteger = DataRev;

    pDataSet->FieldByName(MPW_MED)->AsString = Medication;

    pDataSet->FieldByName(MPW_NOTES)->AsString = Notes;

    pDataSet->FieldByName(MPW_OPERATOR)->AsString = Operator;

    // This is because HRV stores Interpretation in a different location
    if (pDataSet->FindField(MPW_INTERPRETATION)!=NULL)
    {
       pDataSet->FieldByName(MPW_INTERPRETATION)->AsString = Interpretation;
    }
    else
    {
       pDataSet->FieldByName(MHRV_INTERPRETATION)->AsString = Interpretation;
    }

    pDataSet->FieldByName(MPW_HEIGHT)->AsFloat = Height;
    pDataSet->FieldByName(MPW_WEIGHT)->AsFloat = Weight;
    pDataSet->FieldByName(MPW_BMI)->AsFloat = Bmi;

    pDataSet->FieldByName(MPW_SAMPLE_RATE)->AsInteger = SampleRate;

    return true;
  }
  catch (Exception &exception)
  {
     MsgBox_show(TERROR,
                 MSG_EXCEPTION,
                 LoadStr(MSG_STORE_ERROR),
                 MSG_STORE_ERROR,
                 LoadStr(MSG_STORE_ERROR) +GetCurrentMeasureDetails() +exception.Message);
    return false;
  }
}
//------------------------------------------------------------
bool TMeasure::ExportPrintTitle(TDataSet* pDataSet, String &pOut)
{
  // Actual printing title string
  try
  {
    patient_get_export_titles(pOut);

    if (pDataSet->FindField(MPWM_SESSION_ID) != NULL)
    {
        pOut = pOut + pDataSet->FieldByName(MPWM_SESSION_ID)->DisplayName + "\t";
    }
    pOut = pOut + pDataSet->FieldByName(MPW_SP)->DisplayName + "\t"; // Sp;
    pOut = pOut + pDataSet->FieldByName(MPW_DP)->DisplayName + "\t"; // Dp;
    pOut = pOut + pDataSet->FieldByName(MPW_MP)->DisplayName + "\t"; // MeanP;

    pOut = pOut + pDataSet->FieldByName(MPW_DATA_REV)->DisplayName + "\t"; // DataRev;
    pOut = pOut + pDataSet->FieldByName(MPW_DATETIME)->DisplayName + "\t"; // DateTime;

    pOut = pOut + "AGE" + "\t"; // Age;

    pOut = pOut + pDataSet->FieldByName(MPW_MED)->DisplayName + "\t";   // Medication;
    pOut = pOut + pDataSet->FieldByName(MPW_NOTES)->DisplayName + "\t"; // Notes;

    pOut = pOut + pDataSet->FieldByName(MPW_OPERATOR)->DisplayName + "\t"; // Operator;

    pOut = pOut + "INTERPRETATION" + "\t";   // Interpretation;

    if (config_get_system_locale() == CONFIG_DEFAULT_LOCALE)
   {
      pOut = pOut + pDataSet->FieldByName(MPW_HEIGHT)->DisplayName + "\t"; // Height;
      pOut = pOut + pDataSet->FieldByName(MPW_WEIGHT)->DisplayName + "\t"; // Weight;
   }
   else if (config_get_system_locale() == CONFIG_IMPERIAL_LOCALE)
   {
      pOut = pOut + "FEET" + "\t"; // Feet;
      pOut = pOut + "INCH" + "\t"; // Inch;
      pOut = pOut + "POUND" + "\t"; // Pound
   }
   pOut = pOut + pDataSet->FieldByName(MPW_BMI)->DisplayName + "\t";    // Bmi;

    pOut = pOut + pDataSet->FieldByName(MPW_SAMPLE_RATE)->DisplayName + "\t"; // SampleRate;

    pOut = pOut + SIMULATION + "\t";

    return true;
    // Export specific properties
  }
  catch (Exception &exception)
  {
    MsgBox(TERROR, GetCurrentMeasureDetails(), MSG_EXPORT_EXCEPTION, MSG_EXPORT_EXCEPTION, LoadStr(MSG_EXPORT_EXCEPTION) + exception.Message);
  }
  return false;
}
//------------------------------------------------------------
bool TMeasure::Export(String &pOut, const int pSessionID)
{
  UCOUNT report_age;

  report_age = patient_get_age_at_date(DateTime);

  // Actual printing parameters string
  patient_get_export_data(pOut);
  if (pSessionID > 0)
  {
    pOut = pOut + IntToStr(pSessionID) + "\t";
  }

  pOut = pOut + RoundIntToStr(Sp) + "\t";
  pOut = pOut + RoundIntToStr(Dp) + "\t";
  pOut = pOut + RoundIntToStr(MeanP) + "\t";

  pOut = pOut + IntToStr(DataRev) + "\t";
  pOut = pOut + DateTime.FormatString(DateTimeFormat) + "\t";
  // PM V9
  pOut = pOut + IntToStr(report_age) + "\t";

  pOut = pOut + MsgBox_ReplaceCarriage(Medication) + "\t";
  pOut = pOut + MsgBox_ReplaceCarriage(Notes) + "\t";

  pOut = pOut + Operator + "\t";

  pOut = pOut + MsgBox_ReplaceCarriage(Interpretation) + "\t";

   if (config_get_system_locale() == CONFIG_DEFAULT_LOCALE)
   {
      pOut = pOut + RoundIntToStr(Height) + "\t";
      pOut = pOut + RoundIntToStr(Weight) + "\t";
   }
   else if (config_get_system_locale() == CONFIG_IMPERIAL_LOCALE)
   {
      pOut = pOut + RoundIntToStr(Feet) + "\t";
      pOut = pOut + RoundIntToStr(Inch) + "\t";
      pOut = pOut + RoundIntToStr(Pound) + "\t";
   }
   pOut = pOut + FormatFloat("#0.##", Bmi) + "\t";

  pOut = pOut + IntToStr(SampleRate) + "\t";

  if (Simulation)
  {
     pOut = pOut +"Yes\t";
  }
  else
  {
     pOut = pOut +"No\t";
  }
  return true;
}
/* ###########################################################################
 ** ValidateSpDpMp()
 **
 ** DESCRIPTION
 **  Validate Sp, Dp, Mp pressures
 ** INPUT
 **  TPWA Class properties
 ** OUTPUT
 **  None
 ** RETURN
 **  boolean success or not
*/
//---------------------------------------------------------------------------
bool TMeasure::ValidateSpDpMp()
{
  bool        ret = true;
  // PM CR
  AnsiString  spdp_range = "  Allowable Range [" +IntToStr(MIN_DP + 1) +", " +IntToStr(MAX_SP - 1) +"] ";

  // Sp, Dp, Mp pressures validation
  // PM V9
  // The minimum DP value is not allowed. It is assumed to be an operator error
  if (Dp <= MIN_DP)
  {
     if (Sp <= 0 && MeanP <= 0)
     {
        MsgBox_show(TWARNING,
                    MSG_VALIDATION_ERROR,
                    LoadStr(MSG_ENT_SP_OUT) +FloatToStr(Sp) +spdp_range,
                    MSG_ENT_SP_OUT, "");
     }
     else
     {
        MsgBox_show(TWARNING,
                    MSG_VALIDATION_ERROR,
                    LoadStr(MSG_ENT_DP_OUT) +FloatToStr(Dp) + spdp_range,
                    MSG_ENT_DP_OUT, "");
     }
     ret = false;
  }

  if (ret)
  {
     if (Sp > 0)
     {
       MeanP = 0;
       // PM CR
        if (Sp <= Dp)
       {
         MsgBox_show(TWARNING,
                     MSG_VALIDATION_ERROR,
                     LoadStr(MSG_ENT_SP_LESS_DP_OUT) +FloatToStr(Sp) +spdp_range,
                     MSG_ENT_SP_LESS_DP_OUT, "");
         ret = false;
       }
       // PM V9
        // The maximum SP value is not allowed. It is assumed to be an operator error
        else if (Sp >= MAX_SP)
       {
         MsgBox_show(TWARNING,
                     MSG_VALIDATION_ERROR,
                     LoadStr(MSG_ENT_SP_OUT) +FloatToStr(Sp) +spdp_range,
                     MSG_ENT_SP_OUT, "");
         ret = false;
       }
       else
       {
         if (Sp - Dp < PWA_MIN_PRESSURE_PULSE_HEIGHT)
         {
            MsgBox_show(TWARNING,
                        MSG_VALIDATION_ERROR,
                        LoadStr(MSG_PH_TOO_SMALL) +IntToStr(PWA_MIN_PRESSURE_PULSE_HEIGHT),
                        MSG_PH_TOO_SMALL, "");
           ret = false;
         }
       }
     }
     else
     {
       if (MeanP <= 0)
       {
          MsgBox_show(TWARNING,
                      MSG_VALIDATION_ERROR,
                      LoadStr(MSG_ENT_SP_OUT) +FloatToStr(Sp) +spdp_range,
                      MSG_ENT_SP_OUT, "");
          ret = false;
       }
       else if ((MeanP <= Dp) || (MeanP >= MAX_SP))
       {
          MsgBox_show(TWARNING,
                      MSG_VALIDATION_ERROR,
                      LoadStr(MSG_ENT_MP_OUT) +FloatToStr(MeanP) +spdp_range,
                      MSG_ENT_MP_OUT, "");
          ret = false;
       }
       else if (MeanP - Dp < PWA_MIN_PRESSURE_PULSE_HEIGHT / 2)
       {
          MsgBox_show(TWARNING,
                      MSG_VALIDATION_ERROR,
                      LoadStr(MSG_PH_TOO_SMALL) +IntToStr((PWA_MIN_PRESSURE_PULSE_HEIGHT / 2)),
                      MSG_PH_TOO_SMALL, "");
          ret = false;
       }
     }
  }
  return ret;
}

/* ###########################################################################
 ** ValidateHtWt()
 **
 ** DESCRIPTION
 **  Validate Height and Weight
 ** INPUT
 **  TPWA Class properties
 ** OUTPUT
 **  None
 ** RETURN
 **  boolean success or not
*/
//---------------------------------------------------------------------------
bool TMeasure::ValidateHtWt()
{
  bool        ret = true;
  AnsiString  height_range = "  Allowable Range [" +IntToStr(MIN_HEIGHT) +", " +IntToStr(MAX_HEIGHT) +"] ";
  AnsiString  weight_range = "  Allowable Range [" +IntToStr(MIN_WEIGHT) +", " +IntToStr(MAX_WEIGHT) +"] ";

  // Height and Weight validation
  if (Height != DEFAULT_VALUE)
  {
     if (Height < MIN_HEIGHT || Height > MAX_HEIGHT)
     {
        MsgBox_show(TWARNING,
                    MSG_VALIDATION_ERROR,
                    LoadStr(MSG_ENT_HT_OUT) +FloatToStr(Height) + "cm" + height_range,
                    MSG_ENT_HT_OUT, "");
        ret = false;
     }
  }

  if (ret)
  {
     if (Weight != DEFAULT_VALUE)
     {
         if (Weight < MIN_WEIGHT || Weight > MAX_WEIGHT)
         {
            MsgBox_show(TWARNING,
                        MSG_VALIDATION_ERROR,
                        LoadStr(MSG_ENT_WT_OUT) +FloatToStr(Weight) + "kg" + weight_range,
                        MSG_ENT_WT_OUT, "");
            ret = false;
         }
      }
  }
  return ret;
}
