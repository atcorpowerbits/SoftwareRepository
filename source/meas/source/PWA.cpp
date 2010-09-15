//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include <msg\pubserv.h>
#include <meas\pubserv.h>
#include <patient\pubserv.h>
#include <export/pubserv.h>
#include <config\pubserv.h>
#include <report\pubserv.h>
#include "stdlib.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
const float PWA_ED_TOP_PERCENT = 0.75;  // ED cannot be more then 65% of Length
const float PWA_EFFECTIVE_PULSE_LENGTH_PERCENT = 0.75; // percent to calculate min value for calibration
const int   PWA_NOF_DELAY_SAMPLES = 8;

// Transformation coefficients for Radial type of measurement
/*const */float coeff_radial[NOF_TF_COEFF] =
{
      0.009862,			-0.000095,	  -0.005618,		-0.003233,
			0.006131,			0.017503,			0.024616,			0.023522,
			0.014987,			0.004218,			-0.002010,		0.000762,
			0.012045,			0.026615,			0.037516,			0.040147,
			0.034989,			0.027256,			0.023525,			0.027286,
			0.036144,			0.042628,			0.038530,			0.020530,
			-0.006188,		-0.028806,		-0.032427,		-0.007839,
			0.042468,			0.103461,			0.152893,			0.170668,
			0.147910
};

// Transformation coefficients for Carotid type of measurement
/*const */float coeff_carotid [NOF_TF_COEFF] =
{
			0.010791,			0.024537,			0.031748,			0.027346,
			0.012983,			-0.003134,		-0.010473,		-0.002415,
			0.019032,			0.043001,			0.054750,			0.043660,
			0.010112,			-0.032672,	 	-0.063426,		-0.062414,
			-0.021320,		0.051507,			0.133337,			0.196125,
			0.218259,			0.193526,			0.133184,			0.060371,
			-0.000289,		-0.032830,		-0.035241,		-0.017949,
			0.003084,			0.014735,			0.012343,			0.000219,
			-0.012487
};

static TPWA pwa;
TPWA*  meas_get_current_pwa (void){ return &pwa; }

String meas_pwa_get_table_name()
{
  return MPWA;
}
/* ###########################################################################
 ** GetCurrentPwaMeasureDetails()
 **
 ** DESCRIPTION
 **  Get string with details about current measurement
 ** INPUT
      None
 ** OUTPUT
 ** RETURN
 **  String with meas details
*/
//---------------------------------------------------------------------------
String GetCurrentPwaMeasureDetails()
{
  String ret = "";
  TPWA* pwa = meas_get_current_pwa();
  if (pwa==NULL) return ret;
  ret = " Patient :" + IntToStr(pwa->Patient_No);
  ret = ret + ", Measurement :" + pwa->DateTime.DateTimeString();
  ret = ret + ", DataRevision :" + IntToStr(pwa->DataRev) +" ";
  return ret;
}

// ###########################################################################
// Public constructor for TPWA Measurement Class
//---------------------------------------------------------------------------
TPWA::TPWA() : TMeasure()
{
  MeasureType = PWA_RADIAL;
  SystolicOnsetAlgorithm = PWA_TANGENT_DER2_ALGORITHM;
  Tonometer = CONFIG_DEFAULT_TONOMETER;
  Reason = "";
  AuditFlag = AUDIT_ORIGINAL;
  AuditChange = Now();
  CaptureTime = "";

  // ValidateSpDp = true;
  // Initialise other properties
  Initialise();
}

//---------------------------------------------------------------------------
// Class initialisator
//---------------------------------------------------------------------------
void TPWA::Initialise()
{
  // Specific properties initialisation
  // CardiacOutput = DEFAULT_VALUE;
  // Flow = DEFAULT_VALUE;

  // ReadyToCapture = false;
  ReferenceAge = DEFAULT_VALUE;
  ReferenceScore = DEFAULT_VALUE;
  AmplificationRatio = DEFAULT_VALUE;
  CalcIsInconclusive = false;
  InconclusiveNote = "";
  SignalUpSampleRate = 1;
  ExpPulseUpSampleRate = EXPPULSE_MAX_EXPAND_FACTOR;


  // Initialise Pressures
  Periph.Initialise(SampleRate * SignalUpSampleRate, SampleRate * ExpPulseUpSampleRate);
  Central.Initialise(SampleRate * SignalUpSampleRate, SampleRate * ExpPulseUpSampleRate);

  // Initialise AVI
  avi = meas_get_current_avi();
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
bool TPWA::Populate(TDataSet* pDataSet)
{
  if (MSAccess==true)
    return PopulateAccess(pDataSet);
  else
    return PopulateDBase(pDataSet);
}

//---------------------------------------------------------------------------
bool TPWA::PopulateDBase(TDataSet* pDataSet)
{
  try
  {
    // Populate base Measure properties
    if (TMeasure::PopulateDBase(pDataSet)==false)
    {
      return false;
    }
    if (pDataSet->RecordCount <= 0)
    {
      Initialise();
      return false; //true;
    }

    // Extract Secs from Spare field
    Spare1 = pDataSet->FieldByName(MPW_SPARE1)->AsString;
    // Manage Seconds
    if (Spare1.Length() > 0)
    {
      Secs =  (unsigned char)Spare1[1];
    }
    else // If no seconds, add them to prevent key violation
    {
      SecInc = (short int) (SecInc < 59 ? SecInc+1 : 1);
      Secs = SecInc;
    }
    if (Secs!=0)
      DateTime = DateTime + TDateTime(0,0,(unsigned short)Secs,0);

    String Med1 = pDataSet->FieldByName(MPWA_MED_1)->AsString;
    String Med2 = pDataSet->FieldByName(MPWA_MED_2)->AsString;
    Medication = Med1;
    if (Med2!="")
      Medication = Medication + "\r\n" + Med2;

    String Notes1 = pDataSet->FieldByName(MPWA_NOTES_1)->AsString;
    String Notes2 = pDataSet->FieldByName(MPWA_NOTES_2)->AsString;
    Notes = Notes1;
    if (Notes2!="")
      Notes = Notes + "\r\n" + Notes2;

    // Extract MeanP from Spare field
    MeanP = (Spare1.Length() > 4 ? (unsigned char)Spare1[5] : 0);

    // Height and Weight
    if (Spare1.Length() >= 3)
    {
      Height = (unsigned char)Spare1[2];
      Weight = (unsigned char)Spare1[3];
      Bmi = (Height > 0 && Height != DEFAULT_VALUE && Weight > 0 && Weight != DEFAULT_VALUE
            ? Weight * 1./Height : DEFAULT_VALUE);
    }

    MeasureType = PwaFindMeasureType(pDataSet->FieldByName(MPWA_SUB_TYPE)->AsString);

    SignalUpSampleRate = 1;
    ExpPulseUpSampleRate = 8;

    // Populate Periph and Central Pressure
    bool ret1 = Periph.PopulateDBase(pDataSet, SampleRate*SignalUpSampleRate,
                                     SampleRate*ExpPulseUpSampleRate, DataRev);
    bool ret2 = Central.PopulateDBase(pDataSet, SampleRate*SignalUpSampleRate,
                                     SampleRate*ExpPulseUpSampleRate, DataRev);
    return ret1 && ret2;
  }
  catch (Exception &exception)
  {
     MsgBox_show(TERROR,
                 MSG_EXCEPTION,
                 LoadStr(MSG_POP_EXC),
                 MSG_POP_EXC,
                 LoadStr(MSG_POP_EXC) +GetCurrentPwaMeasureDetails() +exception.Message);
    return false;
  }
}
//---------------------------------------------------------------------------
bool TPWA::PopulateAccess(TDataSet* pDataSet)
{
   float t1_ratio = 0.0;

   try
   {
      ReferenceAge = DEFAULT_VALUE;
      ReferenceScore = DEFAULT_VALUE;
      AmplificationRatio = DEFAULT_VALUE;
      CalcIsInconclusive = false;
      InconclusiveNote = "";
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

      MeasureType = PwaFindMeasureType(pDataSet->FieldByName(MPWA_SUB_TYPE)->AsString);

      SignalUpSampleRate =   (pDataSet->FindField(MPWA_SIGNAL_UPSAMPLE_RATE) != NULL ?
                              pDataSet->FieldByName(MPWA_SIGNAL_UPSAMPLE_RATE)->AsInteger : 1);
      ExpPulseUpSampleRate = (pDataSet->FindField(MPWA_EXPPULSE_UPSAMPLE_RATE) != NULL ?
                              pDataSet->FieldByName(MPWA_EXPPULSE_UPSAMPLE_RATE)->AsInteger : 8);
      Tonometer = pDataSet->FieldByName(MPWA_TONOMETER)->AsInteger;

      // Populate Audit
      Reason = pDataSet->FieldByName(MPWA_AUDIT_REASON)->AsString;
      AuditFlag = (AUDIT_FLAG_TYPE)pDataSet->FieldByName(MPWA_AUDIT_FLAG)->AsInteger;
      Simulation = pDataSet->FieldByName(MPW_SIMULATION)->AsInteger;
      // The Audit Datetime field is only available in audit mode
      if (pDataSet->FindField(MPWA_AUDIT_DATETIME)!= NULL)
      {
         AuditChange = pDataSet->FieldByName(MPWA_AUDIT_DATETIME)->AsDateTime;
      }
      
      // Populate Periph and Central Pressure
      bool ret1 = Periph.PopulateAccess (pDataSet, SampleRate*SignalUpSampleRate,
                                         SampleRate*ExpPulseUpSampleRate, DataRev);
      bool ret2 = Central.PopulateAccess(pDataSet, SampleRate*SignalUpSampleRate,
                                         SampleRate*ExpPulseUpSampleRate, DataRev);

      // Populate AVI
      bool ret3 = avi->Populate(pDataSet, &Central);
      
      if (Central.AP != DEFAULT_VALUE && Central.HR != DEFAULT_VALUE)
      {
         if (Central.HR < 40 || Central.HR > 110)
         {
            ReferenceAge = DEFAULT_VALUE;
         }
         else
         {
            if (patient_is_male())
            {
               if (Height != DEFAULT_VALUE && Height > 0)
               {
                  ReferenceAge = (float)((4.77 * Central.AP) + (0.234 * Height) + (0.80 * Central.HR) - 79.4);
               }
            }
            else
            {
               if (Height != DEFAULT_VALUE && Height > 0)
               {
                  ReferenceAge = (float)((4.2 * Central.AP) + (0.311 * Height) + (0.91 * Central.HR) - 110);
               }
            }
         }
      }
      else
      {
         ReferenceAge = DEFAULT_VALUE;
      }

      // PM CR

      if (Central.PH != DEFAULT_VALUE && Periph.PH != DEFAULT_VALUE)
      {
         if (Central.HR >= 40 && Central.HR <= 110)
         {
            if (Central.PH > 0 && Periph.PH > 0)
            {
               AmplificationRatio = ((float)Periph.PH / (float)Central.PH) * 100;
            }
         }
      }

      // The priority for the inconclusive note is set as:
      // 1. Central AIx
      // 2. Max dP/dt
      // 3. Central T1
      // 4. Peripheral T1
      // 5. T1 Ratio
      // 6. Operator Index
      if (Central.AGPH >= 50.0 && Central.AGPH != DEFAULT_VALUE)
      {
         CalcIsInconclusive = true;
         InconclusiveNote = AORTIC_AIX_NOTE;
      }
      else if (Periph.MaxdPdt < MEAS_MIN_DPDT)
      {
         CalcIsInconclusive = true;
         InconclusiveNote = MAXDPDT_NOTE;
      }
      else if (Central.T1 == DEFAULT_VALUE || Central.T1 < PWA_MIN_T1 || Central.T1 > PWA_MAX_T1)
      {
         CalcIsInconclusive = true;
         InconclusiveNote = AORTIC_TI_NOTE;
      }
      else if (Periph.T1 == DEFAULT_VALUE || Periph.T1 < PWA_MIN_T1 || Periph.T1 > PWA_MAX_T1)
      {
         CalcIsInconclusive = true;
         InconclusiveNote = PERIPHERAL_TI_NOTE;
      }
      else
      {
         if (Central.T1 > Periph.T1)
         {
            t1_ratio = (Periph.T1 / Central.T1) * 100.0;
         }
         else
         {
            t1_ratio = (Central.T1 / Periph.T1) * 100.0;
         }
         if (t1_ratio < PWA_MIN_T1_RATIO)
         {
            CalcIsInconclusive = true;
            InconclusiveNote = T1_RATIO_NOTE;
         }
         else if (Periph.OperatorIndex < PWA_MIN_OPERATOR_INDEX)
         {
            CalcIsInconclusive = true;
            InconclusiveNote = OPERATOR_INDEX_NOTE;
         }
      }


      return ret1 && ret2 && ret3;
   }
   catch (Exception &exception)
   {
      MsgBox_show(TERROR,
                  MSG_EXCEPTION,
                  LoadStr(MSG_POP_EXC),
                  MSG_POP_EXC,
                  LoadStr(MSG_POP_EXC) +GetCurrentPwaMeasureDetails() +exception.Message);
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
bool TPWA::Store(TDataSet* pDataSet, bool pRewriteKeyFields, bool pRewriteDate)
{
  bool ret;
  if (MSAccess==true)
    ret = StoreAccess(pDataSet, pRewriteKeyFields, pRewriteDate);
  else
    ret = StoreDBase(pDataSet, pRewriteKeyFields, pRewriteDate);
  if (ret == false)
  {
    pDataSet->Cancel();
  }
  return ret;
}
//---------------------------------------------------------------------------
bool TPWA::StoreDBase(TDataSet* pDataSet, bool pRewriteKeyFields, bool pRewriteDate)
{
  // DataSet should have already been prepared
  if (pDataSet->CanModify==false)
  {
     MsgBox_show(TERROR,
                 MSG_DBREADWRITE_ERROR,
                 LoadStr(MSG_NO_STORE),
                 MSG_NO_STORE,
                 LoadStr(MSG_NO_STORE) +GetCurrentPwaMeasureDetails());
    return false;
  }
  // Validation
  if (ValidateBeforeStore()==false)
    return false;

  // Actual storing

  // Append/Update base Measure class properties
  if (TMeasure::StoreDBase(pDataSet, pRewriteKeyFields, pRewriteDate)==false)
  {
    return false;
  }

  try
  {
    // Store specific properties
    pDataSet->FieldByName(MPWA_SUB_TYPE)->AsString = PWAMTypeAsString[MeasureType];
  }
  catch (Exception &exception)
  {
     MsgBox_show(TERROR,
                 MSG_EXCEPTION,
                 LoadStr(MSG_STORE_ERROR),
                 MSG_STORE_ERROR,
                 LoadStr(MSG_STORE_ERROR) +GetCurrentPwaMeasureDetails() +exception.Message);
    return false;
  }
  // Store Periph and Central Pressure
  bool ret1 = Periph.StoreDBase(pDataSet);
  bool ret2 = Central.StoreDBase(pDataSet);
  bool ret = ret1 & ret2;
  if (ret==false)
    return false;
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
                 LoadStr(MSG_POST_ERROR) +GetCurrentPwaMeasureDetails() +exception.Message);
    return false;
  }
  // return at success
  return true;
}
//---------------------------------------------------------------------------
bool TPWA::StoreAccess(TDataSet* pDataSet, bool pRewriteKeyFields, bool pRewriteDate)
{
  // DataSet should have already been prepared
  if (pDataSet->CanModify==false)
  {
     MsgBox_show(TERROR,
                 MSG_DBREADWRITE_ERROR,
                 LoadStr(MSG_NO_STORE),
                 MSG_NO_STORE,
                 LoadStr(MSG_NO_STORE) +GetCurrentPwaMeasureDetails());
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
    pDataSet->FieldByName(MPWA_SUB_TYPE)->AsString = PWAMTypeAsString[MeasureType];
    if (pDataSet->FindField(MPWA_SIGNAL_UPSAMPLE_RATE) != NULL)
        pDataSet->FieldByName(MPWA_SIGNAL_UPSAMPLE_RATE)->AsInteger = SignalUpSampleRate;
    if (pDataSet->FindField(MPWA_EXPPULSE_UPSAMPLE_RATE) != NULL)
        pDataSet->FieldByName(MPWA_EXPPULSE_UPSAMPLE_RATE)->AsInteger = ExpPulseUpSampleRate;
    pDataSet->FieldByName(MPWA_TONOMETER)->AsInteger = Tonometer;

    pDataSet->FieldByName(MPWA_AUDIT_REASON)->AsString = Reason;
    pDataSet->FieldByName(MPWA_AUDIT_FLAG)->AsInteger = AuditFlag;
    pDataSet->FieldByName(MPW_SIMULATION)->AsInteger = Simulation;

  }
  catch (Exception &exception)
  {
     MsgBox_show(TERROR,
                 MSG_EXCEPTION,
                 LoadStr(MSG_STORE_ERROR),
                 MSG_STORE_ERROR,
                 LoadStr(MSG_STORE_ERROR) +GetCurrentPwaMeasureDetails() +exception.Message);
    return false;
  }
  // Store Periph and Central Pressure
  bool ret1 = Periph.StoreAccess(pDataSet);
  bool ret2 = Central.StoreAccess(pDataSet);

  bool ret = ret1 & ret2;
  if (ret==false)
    return false;

  // Store AVI
  // Doesn't matter if it fails
  avi->Store(pDataSet, &Central);

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
                 LoadStr(MSG_POST_ERROR) +GetCurrentPwaMeasureDetails() +exception.Message);
    return false;
  }
  // return at success
  return true;
}
//------------------------------------------------------------
bool TPWA::ExportPrintTitle(TDataSet* pDataSet, String &pOut)
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
    pOut = pOut + "Tonometer Serial Number\t";
    pOut = pOut + pDataSet->FieldByName(MPWA_SUB_TYPE)->DisplayName + "\t";
    pOut = pOut + "Inconclusive\t";
    pOut = pOut + "Reference Age\t";
    pOut = pOut + "PPAmpRatio\t";
    // PM CR
  }
  catch (Exception &exception)
  {
    MsgBox(TERROR, GetCurrentPwaMeasureDetails(), MSG_EXPORT_ERROR, MSG_EXPORT_EXCEPTION,  LoadStr(MSG_EXPORT_EXCEPTION) + exception.Message);
    return false;
  }
  // Print Periph and Central Pressure
  bool ret1 = Periph.ExportPrintTitle(pDataSet, pOut);
  bool ret2 = Central.ExportPrintTitle(pDataSet, pOut);
  bool ret3 = avi->ExportPrintTitle(pDataSet, pOut);
  bool ret = ret1 & ret2 & ret3;
  // Final delimiter
  pOut.Delete(pOut.LastDelimiter("\t"),1);
  // return at success
  return ret;
}
//------------------------------------------------------------
bool TPWA::Export(String &pOut, const int pSessionID)
{
   AnsiString S;
  // Actual printing properties

  // Export Measure class
  if (TMeasure::Export(pOut, pSessionID)==false)
  {
    return false;
  }

  // Export specific properties
  pOut = pOut + IntToStr(Tonometer) + "\t";
  pOut = pOut + PWAMTypeAsString[MeasureType] + "\t";
  if (CalcIsInconclusive)
  {
     pOut = pOut +"Yes\t";
  }
  else
  {
     pOut = pOut +"No\t";
  }
  /*
  ** Limit the age between 20 and 80
  */
  if (ReferenceAge != DEFAULT_VALUE)
  {
     if (ReferenceAge > 80)
     {
        S = "80+";
     }
     else if (ReferenceAge < 20)
     {
        S = "20";
     }
     else
     {
        S = RoundIntToStr(ReferenceAge);
     }
  }
  else
  {
     S = RoundIntToStr(ReferenceAge);
  }
  // PM CR
  pOut = pOut + S + "\t";
  pOut = pOut + RoundIntToStr(AmplificationRatio) +"\t";

  // Export Periph and Central Pressure
  bool ret1 = Periph.Export(pOut);
  bool ret2 = Central.Export(pOut);
  bool ret3 = avi->Export(pOut);
  bool ret = ret1 & ret2 & ret3;
  // Final delimiter
  pOut.Delete(pOut.LastDelimiter("\t"),1);
  // return at success
  return ret;
}
//------------------------------------------------------------
bool TPWA::ExportArrays(int pFileHandle)
{
  // Validation
  if (pFileHandle <= 0)
    return false;
  // Printing title for Arrays
  String lOut;

  // Only print AVI arrays if AVI is enabled and has been calculated
  if (config_get_avi_option() && avi->Aortic_Reflection_Time < DEFAULT_VALUE)
  {
      lOut = "PeriphSignal \t CentralSignal \t PeriphPulse \t CentralPulse";
      lOut = lOut + "\t FlowWave \t ForwardPulse \t ReflectedPulse \r\n";
  }
  else
  {
      lOut = "PeriphSignal \t CentralSignal \t PeriphPulse \t CentralPulse \r\n";
  }
  FileWrite(pFileHandle, lOut.c_str(), lOut.Length());
  // Printing arrays
  int lMaxSize = max (Periph.NofPoints, Central.NofPoints);
  lMaxSize = max ((int)Periph.CalAvPulse.Length(), lMaxSize);
  for (int i=0; i<lMaxSize; i++)
  {
    lOut = "";
    if (i < Periph.NofPoints)
      lOut = lOut + FormatFloat("####0.0#", Periph.Signal[i]);
    if (i < Central.NofPoints)
      lOut = lOut + "\t" + FormatFloat("####0.0#", Central.Signal[i]);
    if (i < Periph.CalAvPulse.Length())
      lOut = lOut + "\t" +  FormatFloat("####0.0#", Periph.CalAvPulse.Profile[Periph.CalAvPulse.Start + i]);
    if (i < Central.CalAvPulse.Length())
      lOut = lOut + "\t" +  FormatFloat("####0.0#", Central.CalAvPulse.Profile[Central.CalAvPulse.Start + i]);
    if (config_get_avi_option() && avi->Aortic_Reflection_Time < DEFAULT_VALUE)
    {
      if (i < Central.CalAvPulse.Length())
         lOut = lOut + "\t" +  FormatFloat("####0.0#", avi->Flow[Central.CalAvPulse.Start + i]);
      if (i < Central.CalAvPulse.Length())
         lOut = lOut + "\t" +  FormatFloat("####0.0#", avi->Forward_Pressure_Final[Central.CalAvPulse.Start + i]);
      if (i < Central.CalAvPulse.Length())
         lOut = lOut + "\t" +  FormatFloat("####0.0#", avi->Backward_Pressure_Final[Central.CalAvPulse.Start + i]);
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
 **  Validate TPWA class properties before Calculation routine
 ** INPUT
 **  TPWA Class properties
 ** OUTPUT
 ** RETURN
 **  boolean success or not
*/
//---------------------------------------------------------------------------
bool TPWA::ValidateBeforeCalculate()
{
  bool ret = true;
  // Measure type
  if (MeasureType == PWA_NOF_MEASURES)
  {
    MsgBox(TERROR, GetCurrentPwaMeasureDetails(), MSG_VALIDATION_ERROR, MSG_INVALID_MTYPE);
    ret = false;
  }

  // UpSampleRates
  if (SignalUpSampleRate < 1 || SignalUpSampleRate > EXPPULSE_MAX_EXPAND_FACTOR
      || ExpPulseUpSampleRate < 1 || ExpPulseUpSampleRate >EXPPULSE_MAX_EXPAND_FACTOR)
  {
    MsgBox(TERROR, GetCurrentPwaMeasureDetails(), MSG_VALIDATION_ERROR, MSG_INVALID_UPSAMPLERATE);
    ret = false;
  }

  // Pressures Sp, Dp, Mp
  if (ValidateSpDp)
  {
    if (ValidateSpDpMp()==false)
      ret = false;
  }

  // Height and Weight
  if (ValidateHtWt()==false)
  {
      ret = false;
  }

  // Return
  return ret;
}

/* ###########################################################################
 ** ValidateBeforeStore()
 **
 ** DESCRIPTION
 **  Validate TPWA class properties before Store in database
 ** INPUT
 **  TPWA Class properties
 ** OUTPUT
 ** RETURN
 **  boolean success or not
*/
//---------------------------------------------------------------------------
bool TPWA::ValidateBeforeStore()
{
  // Heavy validation of properties before storing
  if (TMeasure::ValidateBeforeStore()==false)
    return false;
  if (ValidateBeforeCalculate()==false)
    return false;
  // Validate Periph against Central
  if (Periph.ExpPulse.Length()!=Central.ExpPulse.Length())
  {
    MsgBox(TERROR, GetCurrentPwaMeasureDetails(), MSG_VALIDATION_ERROR, MSG_PERIPH_CENTRAL_LENGTH);
    return false;
  }
  if (Periph.CalAvPulse.Length()!=Central.CalAvPulse.Length())
  {
    MsgBox(TERROR, GetCurrentPwaMeasureDetails(), MSG_VALIDATION_ERROR, MSG_PERIPH_CENTRAL_LENGTH);
    return false;
  }
  if (Periph.AvPulse.Length()!=Central.AvPulse.Length())
  {
    MsgBox(TERROR, GetCurrentPwaMeasureDetails(), MSG_VALIDATION_ERROR, MSG_PERIPH_CENTRAL_LENGTH);
    return false;
  }

  if (Periph.ED != Central.ED)
  {
    MsgBox(TERROR, GetCurrentPwaMeasureDetails(), MSG_VALIDATION_ERROR,
           MSG_PERIPH_CENTRAL_ED);
    Central.ED = Periph.ED;
  }
  // Pressure class validation
  bool ret1 = Periph.ValidateBeforeStore();
  bool ret2 = Central.ValidateBeforeStore();
  // Return
  return ret1 & ret2;
}
/* ###########################################################################
 ** PeriphToCentral()
 **
 ** DESCRIPTION
 **  Convert Peripheral Signal To Central using
 **  own transformation function for each MEASURE_TYPE
 ** INPUT
 **  PressurePeriph class (source)
 **  PressureCentral class (destination)
 ** OUTPUT
 **  boolean success or not
*/
//---------------------------------------------------------------------------
bool TPWA::PeriphToCentral()
{
  switch (MeasureType)
  {
    case PWA_RADIAL:
      return Convolution(coeff_radial, NOF_TF_COEFF);
    case PWA_CAROTID:
      return Convolution(coeff_carotid, NOF_TF_COEFF);
    case PWA_AORTIC: // No transformation
      memcpy(Central.Signal, Periph.Signal, Periph.NofPoints * sizeof(Central.Signal[0]));
      return true;
    default:
      MsgBox(TERROR, GetCurrentPwaMeasureDetails(), MSG_VALIDATION_ERROR, MSG_INVALID_MTYPE);
      return false;
  }
}

/* ###########################################################################
 ** Convolution()
 **
 ** DESCRIPTION
 **  Convert Peripheral Signal To Central using convolution
 ** INPUT
 **  pTfc[NofTFC] - transformation coefficients
 ** OUTPUT
 **  Central[0 : NofPoints-NofTFC] - shifted central pressure signal
 **  Central[NofPoints-NofTFC : NofPoints] = 0 - tail of central pressure signal
 ** RETURN
 **  boolean success or not
*/
//---------------------------------------------------------------------------
bool TPWA::Convolution(const float *pTfc, const int pNofTFC)
{
	// calculate central (aortic) data
	for(int i = 0; i < Periph.NofPoints; i++)
  {
    // Do not calculate Central for tail of a signal
    if (i > Periph.NofPoints - pNofTFC)
    {
      Central.Signal[i] = 0.;
      continue;
    }
    // Calculate Central for actual signal
    double ld = 0.0;
	  for(int j = 0; j < pNofTFC; j++ )
    {
			ld += pTfc[j] * Periph.Signal[i+j];
    }
		Central.Signal[i] = ld;
	}

  return true;
}
/* ###########################################################################
 ** Calculate ()
 **
 ** DESCRIPTION
 **  Do all mathematics for this measurement
 ** INPUT
 **  TPWA class (source)
 ** OUTPUT
 **  boolean success or not
*/
//---------------------------------------------------------------------------
bool TPWA::Calculate(const float pCalibrationFactor)
{


  try
  {
    ReferenceAge = DEFAULT_VALUE;
    AmplificationRatio = DEFAULT_VALUE;
    CalcIsInconclusive = false;
    // Default values for calculated variables
    int lNofPoints = (Periph.NofPoints > 0 ? min(Periph.NofPoints, PRESSURE_MAX_PPOINTS) : PRESSURE_MAX_PPOINTS);
    Periph.SetDefaults(lNofPoints, SampleRate * SignalUpSampleRate, SampleRate * ExpPulseUpSampleRate);
    int lShift = (MeasureType == PWA_RADIAL || MeasureType == PWA_CAROTID ?
                  NOF_TF_COEFF : 0);
    Central.SetDefaults(lNofPoints, lShift, SampleRate * SignalUpSampleRate, SampleRate * ExpPulseUpSampleRate);

    // Check necessary properties before calculation
    // bool lValidateSpDp = (pCalibrationFactor == 0.);
    if (ValidateBeforeCalculate()==false)
      return false;

    // Convert Periph to Central
    if (PeriphToCentral()==false)
      return false;
    // Find trigger Points
    int lMinTrigPt = PWA_NOF_DELAY_SAMPLES + 2;
    if (Periph.CalculateTrigPts(PWA_DER2_ALGORITHM, lMinTrigPt)==false)
      return false;
    if (Central.CalculateTrigPts(PWA_DER2_ALGORITHM, lMinTrigPt)==false)
      return false;
    if (RejectIrregularTrigPts()==false)
      return false;

    // Store pulses
    if (Periph.CalcPulses(true, PWA_NOF_DELAY_SAMPLES)==false
    || Central.CalcPulses(true, PWA_NOF_DELAY_SAMPLES)==false)
    {
      MsgBox(TERROR, GetCurrentMeasureDetails(), MSG_MATH_ERROR,  MSG_CALCPULSES_ERR);
      return false;
    }

    // Average pulse (for Central length = as for peripheral)
    if (Periph.AveragePulse(0, PWA_NOF_DELAY_SAMPLES, SampleRate * SignalUpSampleRate)==false)
    {
      MsgBox(TERROR, GetCurrentMeasureDetails(), MSG_MATH_ERROR,  MSG_CALCPULSES_ERR);
      return false;
    }
    if (Central.AveragePulse(Periph.AvPulse.Length(), PWA_NOF_DELAY_SAMPLES,
        SampleRate * SignalUpSampleRate)==false)
    {
      MsgBox(TERROR, GetCurrentMeasureDetails(), MSG_MATH_ERROR, MSG_AVPULSE_ERR);
      return false;
    }

    // Quality controls
    if (Periph.QualityControl()==false)
      return false;

    // Smooth average pulse
    if (Periph.AvPulse.Smooth()==false)
      return false;
    if (Central.AvPulse.Smooth()==false)
      return false;

    // Expand average pulse
    if (Periph.ExpandPulse(&Periph.AvPulse, ExpPulseUpSampleRate)==false)
      return false;
    if (Central.ExpandPulse(&Central.AvPulse, ExpPulseUpSampleRate)==false)
      return false;

    if (Periph.SystolicOnset(SystolicOnsetAlgorithm, 0)==false)
    {
      MsgBox(TERROR, GetCurrentMeasureDetails(), MSG_MATH_ERROR,  MSG_CALCSYSTONSET_ERR);
      return false;
    }
    if (Central.SystolicOnset(SystolicOnsetAlgorithm, Periph.ExpPulse.Length())==false)
    {
      MsgBox(TERROR, GetCurrentMeasureDetails(), MSG_MATH_ERROR,  MSG_CALCSYSTONSET_ERR);
      return false;
    }

    // Recalculate Average Pulse cutting tale
    // calculate Calibrated average pulse
    if (Periph.AvPulse.DownSample(&Periph.ExpPulse, ExpPulseUpSampleRate)==false)
        return false;
    if (Central.AvPulse.DownSample(&Central.ExpPulse, ExpPulseUpSampleRate)==false)
        return false;

    // Smooth Average pulse (not too good idea)
    // if (Periph.AvPulse.Smooth()==false) return false;
    // if (Central.AvPulse.Smooth()==false) return false;

    // Calibrate Average pulses together
    if (CalibrateAvPulses(pCalibrationFactor,0)==false)
      return false;

    if (Periph.ExpandPulse(&Periph.CalAvPulse, ExpPulseUpSampleRate)==false)
      return false;
    if (Central.ExpandPulse(&Central.CalAvPulse, ExpPulseUpSampleRate)==false)
      return false;

    // Set the length of calibrated average pulse
    if (Central.CalAvPulse.Size() - Central.CalAvPulse.Start < Periph.CalAvPulse.Length())
    {
      MsgBox(TERROR, GetCurrentMeasureDetails(), MSG_MATH_ERROR,  MSG_CALCPULSES_ERR);
      return false;
    }
    Central.CalAvPulse.SetLength(Periph.CalAvPulse.Length());

    //Find T1,T2,ED and extract other features
    if (ExtractFeatures() == false)
    {
       return false;
    }

    // Success
    return true;
  }
  catch (Exception &exception)
  {
    MsgBox(TERROR, GetCurrentMeasureDetails(), MSG_MATH_ERROR, MSG_CALC_EXC,
           LoadStr(MSG_CALC_EXC) + exception.Message);
    return false;
  }
}

/* ###########################################################################
 ** CalculateSinglePulse ()
 **
 ** DESCRIPTION
 **  Do all mathematics for a single pulse
 ** INPUT
 **  TPWA class (source)
 ** OUTPUT
 **  boolean success or not
*/
//---------------------------------------------------------------------------
bool TPWA::CalculateSinglePulse(const float pCalibrationFactor)
{
  try
  {
    ReferenceAge = DEFAULT_VALUE;
    AmplificationRatio = DEFAULT_VALUE;
    CalcIsInconclusive = false;

    // Default values for calculated variables
    int lNofPoints = (Periph.NofPoints > 0 ? min(Periph.NofPoints, PRESSURE_MAX_PPOINTS) : PRESSURE_MAX_PPOINTS);
    Periph.SetDefaults(lNofPoints, SampleRate * SignalUpSampleRate, SampleRate * ExpPulseUpSampleRate);
    int lShift = (MeasureType == PWA_RADIAL || MeasureType == PWA_CAROTID ?
                  NOF_TF_COEFF : 0);
    Central.SetDefaults(lNofPoints, lShift, SampleRate * SignalUpSampleRate, SampleRate * ExpPulseUpSampleRate);

    // Check necessary properties before calculation
    if (ValidateBeforeCalculate()==false)
      return false;

    // Convert Periph to Central
    if (PeriphToCentral()==false)
      return false;

    // Find trigger Points
    int lMinTrigPt = PWA_NOF_DELAY_SAMPLES + 2;
    if (Periph.CalculateTrigPts(PWA_DER2_ALGORITHM, lMinTrigPt, true)==false)
      return false;
    if (Central.CalculateTrigPts(PWA_DER2_ALGORITHM, lMinTrigPt, true)==false)
      return false;
    if (RejectIrregularTrigPts()==false)
      return false;

    // Calculate the last pulse
    if (Periph.CalcPulses(true, PWA_NOF_DELAY_SAMPLES, true)==false
    || Central.CalcPulses(true, PWA_NOF_DELAY_SAMPLES, true)==false)
    {
      MsgBox(TERROR, GetCurrentMeasureDetails(), MSG_MATH_ERROR,  MSG_CALCPULSES_ERR);
      return false;
    }

    // Set the pulses to the same length
    // As there's only 1 pulse, they cannot be different lengths
    if (Periph.Pulses[0].Length() < Central.Pulses[0].Length())
    {
      Central.Pulses[0].SetLength(Periph.Pulses[0].Length());
    }
    else if (Periph.Pulses[0].Length() > Central.Pulses[0].Length())
    {
      Periph.Pulses[0].SetLength(Central.Pulses[0].Length());
    }

    // Store the last pulse as the Average Pulse
    if (Periph.AveragePulse(0, PWA_NOF_DELAY_SAMPLES, SampleRate * SignalUpSampleRate)==false)
    {
      MsgBox(TERROR, GetCurrentMeasureDetails(), MSG_MATH_ERROR,  MSG_CALCPULSES_ERR);
      return false;
    }
    if (Central.AveragePulse(Periph.AvPulse.Length(), PWA_NOF_DELAY_SAMPLES,
        SampleRate * SignalUpSampleRate)==false)
    {
      MsgBox(TERROR, GetCurrentMeasureDetails(), MSG_MATH_ERROR, MSG_AVPULSE_ERR);
      return false;
    }

    // Smooth average pulse
    if (Periph.AvPulse.Smooth()==false)
      return false;
    if (Central.AvPulse.Smooth()==false)
      return false;
      
    // Expand average pulse
    if (Periph.ExpandPulse(&Periph.AvPulse, ExpPulseUpSampleRate)==false)
      return false;
    if (Central.ExpandPulse(&Central.AvPulse, ExpPulseUpSampleRate)==false)
      return false;

    // Find the Systolic onsets
    if (Periph.SystolicOnset(SystolicOnsetAlgorithm, 0)==false)
    {
      MsgBox(TERROR, GetCurrentMeasureDetails(), MSG_MATH_ERROR,  MSG_CALCSYSTONSET_ERR);
      return false;
    }
    if (Central.SystolicOnset(SystolicOnsetAlgorithm, Periph.ExpPulse.Length())==false)
    {
      MsgBox(TERROR, GetCurrentMeasureDetails(), MSG_MATH_ERROR,  MSG_CALCSYSTONSET_ERR);
      return false;
    }

    // Recalculate Average Pulse cutting tail
    if (Periph.AvPulse.DownSample(&Periph.ExpPulse, ExpPulseUpSampleRate)==false)
        return false;
    if (Central.AvPulse.DownSample(&Central.ExpPulse, ExpPulseUpSampleRate)==false)
        return false;

    // Calibrate Average pulses together
    if (CalibrateAvPulses(pCalibrationFactor,0)==false)
      return false;

    // Expand the average pulses
    if (Periph.ExpandPulse(&Periph.CalAvPulse, ExpPulseUpSampleRate)==false)
      return false;
    if (Central.ExpandPulse(&Central.CalAvPulse, ExpPulseUpSampleRate)==false)
      return false;

    // Set the length of calibrated average pulse
    if (Central.CalAvPulse.Size() - Central.CalAvPulse.Start < Periph.CalAvPulse.Length())
    {
      MsgBox(TERROR, GetCurrentMeasureDetails(), MSG_MATH_ERROR,  MSG_CALCPULSES_ERR);
      return false;
    }
    Central.CalAvPulse.SetLength(Periph.CalAvPulse.Length());

    //Find T1,T2,ED and extract other features
    if (ExtractFeatures() == false)
    {
       return false;
    }

    // Success
    return true;
  }
  catch (Exception &exception)
  {
    MsgBox(TERROR, GetCurrentMeasureDetails(), MSG_MATH_ERROR, MSG_CALC_EXC,
           LoadStr(MSG_CALC_EXC) + exception.Message);
    return false;
  }
}
/* ###########################################################################
 ** CalculateFeaturesFromDB()
 **
 ** DESCRIPTION
 **  Do all mathematics for this measurement
 **  with replacement CalAvPulse from DB
 ** INPUT
 **  TPWA class (source)
 ** OUTPUT
 **  boolean success or not
*/
//---------------------------------------------------------------------------
bool TPWA::CalculateFeaturesFromDB(TDataSet* pDataSet)
{
  // Default values for calculated variables
  int lNofPoints = (Periph.NofPoints > 0 ? min(Periph.NofPoints, PRESSURE_MAX_PPOINTS) : PRESSURE_MAX_PPOINTS);
  Periph.SetDefaults(lNofPoints, SampleRate * SignalUpSampleRate, SampleRate * ExpPulseUpSampleRate);
  int lShift = (MeasureType == PWA_RADIAL || MeasureType == PWA_CAROTID ?
                NOF_TF_COEFF : 0);
  Central.SetDefaults(lNofPoints, lShift, SampleRate * SignalUpSampleRate, SampleRate * ExpPulseUpSampleRate);

  // Check necessary properties before calculation
  if (ValidateBeforeCalculate()==false)
    return false;

  // Convert Periph to Central
  if (PeriphToCentral()==false)
    return false;

    // Trigger Points and Pulses
    int lMinTrigPt = lShift + PWA_NOF_DELAY_SAMPLES + 2;
    if (Periph.CalculateTrigPts(PWA_DER2_ALGORITHM, lMinTrigPt)==false)
      return false;
    if (AssignCentralTrigPts()==false)
      return false;
    // if (RejectIrregularTrigPts()==false)
    //  return false;
    if (Periph.CalcPulses(true, PWA_NOF_DELAY_SAMPLES)==false
    || Central.CalcPulses(true, PWA_NOF_DELAY_SAMPLES)==false)
    {
      MsgBox(TERROR, GetCurrentPwaMeasureDetails(), MSG_MATH_ERROR,  MSG_CALCPULSES_ERR);
      return false;
    }
    // Average pulse (for Central length = as for peripheral)
    if (Periph.AveragePulse(0, PWA_NOF_DELAY_SAMPLES, SampleRate*SignalUpSampleRate)==false)
    {
      MsgBox(TERROR, GetCurrentPwaMeasureDetails(), MSG_MATH_ERROR, MSG_AVPULSE_ERR);
      return false;
    }
    if (Central.AveragePulse(Periph.AvPulse.Length(), PWA_NOF_DELAY_SAMPLES,
        SampleRate*SignalUpSampleRate)==false)
    {
      MsgBox(TERROR, GetCurrentPwaMeasureDetails(), MSG_MATH_ERROR, MSG_AVPULSE_ERR);
      return false;
    }

    // Quality controls
    if (Periph.QualityControl()==false)
      return false;

    // Smooth average pulse
    if (Periph.AvPulse.Smooth()==false)
      return false;
    if (Central.AvPulse.Smooth()==false)
      return false;

    // Expand average pulse
    if (Periph.ExpandPulse(&Periph.AvPulse, ExpPulseUpSampleRate)==false)
      return false;
    if (Central.ExpandPulse(&Central.AvPulse, ExpPulseUpSampleRate)==false)
      return false;
/*
    // Smooth Expanded pulse
    if (Periph.ExpPulse.Smooth(16)==false)
      return false;
    if (Central.ExpPulse.Smooth(16)==false)
      return false;
*/
    if (Periph.SystolicOnset(SystolicOnsetAlgorithm, 0)==false)
    {
      MsgBox(TERROR, GetCurrentPwaMeasureDetails(), MSG_MATH_ERROR,  MSG_CALCSYSTONSET_ERR);
      return false;
    }
    if (Central.SystolicOnset(SystolicOnsetAlgorithm, Periph.ExpPulse.Length())==false)
    {
      MsgBox(TERROR, GetCurrentPwaMeasureDetails(), MSG_MATH_ERROR,  MSG_CALCSYSTONSET_ERR);
      return false;
    }

    // Recalculate Average Pulse cutting tale
    // calculate Calibrated average pulse
    if (Periph.AvPulse.DownSample(&Periph.ExpPulse, ExpPulseUpSampleRate)==false)
        return false;
    if (Central.AvPulse.DownSample(&Central.ExpPulse, ExpPulseUpSampleRate)==false)
        return false;

    // Smooth Average pulse (not too good idea)
    // if (Periph.AvPulse.Smooth()==false) return false;
    // if (Central.AvPulse.Smooth()==false) return false;
    // Calibrate Average pulses together
    if (CalibrateAvPulses()==false)
      return false;
/*
    if (Periph.CalAvPulse.Smooth()==false)
      return false;
    if (Central.CalAvPulse.Smooth()==false)
      return false;
*/
    if (Periph.GetCalPulseFromDB(pDataSet, PERIPH_PREFIX, SampleRate*SignalUpSampleRate, DataRev)==false)
      return false;
    if (Central.GetCalPulseFromDB(pDataSet, CENTRAL_PREFIX, SampleRate*SignalUpSampleRate, DataRev)==false)
      return false;

    // Expand Calibrated Pulse
    if (Periph.ExpandPulse(&Periph.CalAvPulse, ExpPulseUpSampleRate)==false)
      return false;
    if (Central.ExpandPulse(&Central.CalAvPulse, ExpPulseUpSampleRate)==false)
      return false;
/*
    // Smooth Expanded pulse
    if (Periph.ExpPulse.Smooth(16)==false)
      return false;
    if (Central.ExpPulse.Smooth(16)==false)
      return false;
*/
/*
    if (Periph.SystolicOnset(PWA_TANGENT_DER2_ALGORITHM)==false)
    {
      MsgBox(TERROR, GetCurrentPwaMeasureDetails(), MSG_MATH_ERROR,  MSG_CALCSYSTONSET_ERR);
      return false;
    }
    if (Central.SystolicOnset(PWA_TANGENT_DER2_ALGORITHM)==false)
    {
      MsgBox(TERROR, GetCurrentPwaMeasureDetails(), MSG_MATH_ERROR,  MSG_CALCSYSTONSET_ERR);
      return false;
    }
*/
    // Find T1,T2,ED and extract other features
    if (ExtractFeatures(/*SampleRate*/)==false)
      return false;
    // Success
    return true;
}
/* ###########################################################################
 ** ExtractFeatures()
 **
 ** DESCRIPTION
 **  Find T1, T2, ED for Periph and Central, Set Central.ED = Periph.ED
 **  and Extract features
 ** INPUT
 **  TPWA.Periph, TPWA.Central classes (source)
 ** OUTPUT
 **  boolean success or not
*/
//---------------------------------------------------------------------------
bool TPWA::ExtractFeatures(/*int pSampleRate*/)
{
   T1Ratio = 0.0;
   // Find peaks of Central and Peripheral
   int lCentralMainPeak = Central.ExpPulse.IndexOfExtremum(MAX, GLOBAL, 1, (int)(Central.ExpPulse.Length()/2));
   int lPeriphMainPeak = Periph.ExpPulse.IndexOfExtremum(MAX, GLOBAL, 1, (int)(Periph.ExpPulse.Length()/2));
   if (lCentralMainPeak < 0 && lPeriphMainPeak < 0)
   {
      MsgBox(TERROR, GetCurrentPwaMeasureDetails(), MSG_VALIDATION_ERROR, MSG_NOT_FOUND_PEAK);
      return true;
   }

   // Find T1, T2, ED for peripheral
   // For NPROC it is not necessary to use correspondence
   TPulse* lCD1 = (MeasureType == PWA_RADIAL || MeasureType == PWA_CAROTID ?
                   &Central.Der1ExpPulse : NULL);
   TPulse* lCD2 = (MeasureType == PWA_RADIAL || MeasureType == PWA_CAROTID ?
                   &Central.Der2ExpPulse : NULL);
   if (Periph.ExpPulse.FindT1T2ED(&Periph.Der1ExpPulse, &Periph.Der2ExpPulse,
       &Periph.Der3ExpPulse, ExpPulseUpSampleRate,
       SampleRate, -1, lCentralMainPeak, -1, -1,
       lCD1, lCD2)==false)
   {
        return false;
   }
   if (Periph.ExpPulse.ED == DEFAULT_VALUE)
   {
      MsgBox_show(TWARNING,
                  MSG_MATH_ERROR,
                  LoadStr(MSG_NO_PERIPHED),
                  MSG_NO_PERIPHED,
                  LoadStr(MSG_NO_PERIPHED) +GetCurrentPwaMeasureDetails());
      //return false;
   }
   // Find  T1, T2, ED for Central
   // Set the limitation for Central.T2 on the base of Periph.T2
   int lLimitT1T2 = (Periph.ExpPulse.T2 != DEFAULT_VALUE ?
                     Periph.ExpPulse.T2 : -1);
   if (lLimitT1T2 > 0 && Periph.ExpPulse.T2m > 0
       && Periph.ExpPulse.ShoulderAfterPeak > Periph.ExpPulse.T2m)
   {
     lLimitT1T2 = Periph.ExpPulse.ShoulderAfterPeak;
   }
   if (Central.ExpPulse.FindT1T2ED(&Central.Der1ExpPulse, &Central.Der2ExpPulse, &Central.Der3ExpPulse,
       ExpPulseUpSampleRate, SampleRate, Periph.ExpPulse.ED, -1, lPeriphMainPeak, lLimitT1T2)==false)
   {
       return false;
   }

   // Set all EDs the same
   // Set Central.ED = Periph.ED
   Central.ExpPulse.ED = Periph.ExpPulse.ED;

   // Extract other features dependant on T1, T2, ED
   if (Periph.ExtractFeatures(/*SampleRate, */Periph.ExpPulse.ED) == false)
   {
      return false;
   }

   if (Central.ExtractFeatures(/*SampleRate, */Central.ExpPulse.ED) == false)
   {
      return false;
   }

   // Calculate AVI features on Radial and Aortic measurements when AVI enabled
   // If it fails, reset AVI and do not prevent PWA from calculating a report
   if ((MeasureType == PWA_RADIAL || MeasureType == PWA_AORTIC) && config_get_avi_option())
   {
      if (avi->Calculate(&Central) == false)
      {
         MsgBox_show(TWARNING,
                       MSG_MATH_ERROR,
                       LoadStr(MSG_AVI_ERROR_CALC),
                       MSG_AVI_ERROR_CALC, "");
         avi->Initialise();
      }
   }
   else
   {
      avi->Initialise();
   }

   // Calculate the correspondence of T1
   if (Central.T1 > Periph.T1)
   {
      T1Ratio = (Periph.T1 / Central.T1) * 100.0;
   }
   else
   {
      T1Ratio = (Central.T1 / Periph.T1) * 100.0;
   }

   // Save the calculated parameters
   Periph.CalcED = Periph.ED;
   Central.CalcED = Central.ED;
   Periph.CalcT1 = Periph.T1;
   Central.CalcT1 = Central.T1;
   Periph.CalcT2 = Periph.T2;
   Central.CalcT2 = Central.T2;

   if (Central.AP != DEFAULT_VALUE && Central.HR != DEFAULT_VALUE)
    {
      if (Central.HR < 40 || Central.HR > 110)
      {
         ReferenceAge = DEFAULT_VALUE;
      }
      else
      {
         if (patient_is_male())
         {
            if (Height != DEFAULT_VALUE && Height > 0)
            {
               ReferenceAge = (float)((4.77 * Central.AP) + (0.234 * Height) + (0.80 * Central.HR) - 79.4);
            }
         }
         else
         {
            if (Height != DEFAULT_VALUE && Height > 0)
            {
               ReferenceAge = (float)((4.2 * Central.AP) + (0.311 * Height) + (0.91 * Central.HR) - 110);
            }
         }
      }
    }
    else
    {
       ReferenceAge = DEFAULT_VALUE;
    }

    // PM CR

    if (Central.PH != DEFAULT_VALUE && Periph.PH != DEFAULT_VALUE)
    {
      if (Central.HR >= 40 && Central.HR <= 110)
      {
         if (Central.PH > 0 && Periph.PH > 0)
         {
            AmplificationRatio = ((float)Periph.PH / (float)Central.PH) * 100;
         }
      }
   }

      // The priority for the inconclusive note is set as:
      // 1. Central AIx
      // 2. Max dP/dt
      // 3. Central T1
      // 4. Peripheral T1
      // 5. T1 Ratio
      // 6. Operator Index
      if (Central.AGPH >= 50.0)
      {
         CalcIsInconclusive = true;
         InconclusiveNote = AORTIC_AIX_NOTE;
      }
      else if (Periph.MaxdPdt < MEAS_MIN_DPDT)
      {
         CalcIsInconclusive = true;
         InconclusiveNote = MAXDPDT_NOTE;
      }
      else if (Central.T1 == DEFAULT_VALUE || Central.T1 < PWA_MIN_T1 || Central.T1 > PWA_MAX_T1)
      {
         CalcIsInconclusive = true;
         InconclusiveNote = AORTIC_TI_NOTE;
      }
      else if (Periph.T1 == DEFAULT_VALUE || Periph.T1 < PWA_MIN_T1 || Periph.T1 > PWA_MAX_T1)
      {
         CalcIsInconclusive = true;
         InconclusiveNote = PERIPHERAL_TI_NOTE;
      }
      else
      {
         if (T1Ratio < PWA_MIN_T1_RATIO)
         {
            CalcIsInconclusive = true;
            InconclusiveNote = T1_RATIO_NOTE;
         }
         else if (Periph.OperatorIndex < PWA_MIN_OPERATOR_INDEX)
         {
            CalcIsInconclusive = true;
            InconclusiveNote = OPERATOR_INDEX_NOTE;
         }
      }

   // Success
   return true;
}

/* ###########################################################################
 ** FineTuneT1T2()
 **
 ** DESCRIPTION
 **  Recalculate weak or very weak values of T1 or T2
 ** INPUT
 **  None
 ** OUTPUT
 ** RETURN
 **  boolean success or not
*/
//---------------------------------------------------------------------------
bool TPWA::FineTuneT1T2()
{
   float gradient    = 0.6614;
   float y_intercept = 39.216;
   float NewPeriphAIx;
   float NewPeriphP1;
   float NewPeriphT1Index;
   float NewPeriphT1;
   bool Periph_T1_found = false;
   bool success = false;
   int index1 = 0;
   int index2 = 0;

   // Only calculate for radial measurements where Augmentation Index has been calculated
   if ((MeasureType == PWA_RADIAL) && (Periph.AGPH != DEFAULT_VALUE) && (Central.AGPH != DEFAULT_VALUE))
   {
      // Check conditions for recalculating T1
      if ((Periph.QualityT1 > STRONG) && (Central.QualityT1 < WEAK) && (Central.T1 >= PWA_MIN_T1) && (Central.T1 <= PWA_MAX_T1)
         && ((T1Ratio < PWA_MIN_T1_RATIO) || (Periph.T1 < PWA_MIN_T1) || (Periph.T1 > PWA_MAX_T1)))
      {
         // Find Peripheral T1 from the Central T1 regression
         NewPeriphAIx = (Central.AGPH - y_intercept) / gradient;
         NewPeriphP1 = Periph.P2 - ((NewPeriphAIx / 100) * (Periph.Sp - Periph.Dp));
         if (NewPeriphP1 > Periph.Sp)
         {
            NewPeriphP1 = Periph.Sp;
         }
         while (!Periph_T1_found || (index1 < Periph.ExpPulse.Length() - 1))
         {
            if ((Periph.ExpPulse.Profile[index1] <= NewPeriphP1) &&
               (Periph.ExpPulse.Profile[index1 + 1] >= NewPeriphP1))
            {
               NewPeriphT1Index = index1;
               Periph_T1_found = true;
            }
            index1++;
         }
         if (Periph_T1_found)
         {
            // Ensure the new T1 is not inconclusive
            NewPeriphT1 = Periph.ExpPulse.IndexToTime(NewPeriphT1Index);
            if (NewPeriphT1 < PWA_MIN_T1 || NewPeriphT1 > PWA_MAX_T1)
            {
               // If inconclusive and AIx is low, try P1=P2
               if (Periph.AGPH < 0.5 && Periph.AGPH > -2.5)
               {
                  Periph_T1_found = false;
                  NewPeriphP1 = Periph.P2 - 0.2;

                  while (!Periph_T1_found || (index2 < Periph.ExpPulse.Length() - 1))
                  {
                     if ((Periph.ExpPulse.Profile[index2] <= NewPeriphP1) &&
                        (Periph.ExpPulse.Profile[index2 + 1] >= NewPeriphP1))
                     {
                        NewPeriphT1Index = index2;
                        Periph_T1_found = true;
                     }
                     index2++;
                  }
                  if (Periph_T1_found)
                  {
                     // Ensure the new T1 is not inconclusive
                     NewPeriphT1 = Periph.ExpPulse.IndexToTime(NewPeriphT1Index);
                     if (NewPeriphT1 < PWA_MIN_T1 || NewPeriphT1 > PWA_MAX_T1)
                     {
                        //give up
                     }
                     else
                     {
                        // The new T1 is not inconclusive - success!
                        Periph.ExpPulse.T1 = NewPeriphT1Index;
                        success = true;
                     }
                  }
               }
            }
            else
            {
               // The new T1 is not inconclusive - success!
               Periph.ExpPulse.T1 = NewPeriphT1Index;
               success = true;
            }
         }
      }
   }
   return success;
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
bool TPWA::RecalculateEDDependants(const int pEDIndex)
{
  if (Periph.RecalculateEDDependants(pEDIndex/*, SampleRate*/)==false)
    return false;
  if (Central.RecalculateEDDependants(pEDIndex/*, SampleRate*/)==false)
    return false;
   // Calculate AVI features on Radial and Aortic measurements when AVI enabled
   // If it fails, reset AVI and do not prevent PWA from calculating a report
   if ((MeasureType == PWA_RADIAL || MeasureType == PWA_AORTIC) && config_get_avi_option())
   {
      if (avi->Calculate(&Central) == false)
      {
         MsgBox_show(TWARNING,
                       MSG_MATH_ERROR,
                       LoadStr(MSG_AVI_ERROR_CALC),
                       MSG_AVI_ERROR_CALC, "");
         avi->Initialise();
      }
   }
   else
   {
      avi->Initialise();
   }
      
  // Success
  return true;
}

//---------------------------------------------------------------------------
// Check whether ED is within valid window
//---------------------------------------------------------------------------
bool TPWA::CheckEDLimitations(const int pEDIndex, bool &pLeft, bool &pRight)
{
  // Validation
  if (Periph.T1 == DEFAULT_VALUE || Periph.T1 <= 0)
    return false;
  if (Central.T1 == DEFAULT_VALUE || Central.T1 <= 0)
    return false;

  int EDMinIndex;
  int EDMaxIndex = Periph.ExpPulse.Length() * PWA_ED_TOP_PERCENT;
  int pmax;
  if (Periph.T2 != DEFAULT_VALUE && Periph.T2 > Periph.T1)
      pmax = Periph.ExpPulse.TimeToIndex(Periph.T2);
  else
      pmax = Periph.ExpPulse.TimeToIndex(Periph.T1);
  int cmax;
  if (Central.T2 != DEFAULT_VALUE && Central.T2 > Central.T1)
      cmax = Central.ExpPulse.TimeToIndex(Central.T2);
  else
      cmax = Central.ExpPulse.TimeToIndex(Central.T1);
  EDMinIndex = max(pmax, cmax) +
      Central.ExpPulse.TimeToIndex(16) - Central.ExpPulse.Start;

  // Actual check
  pLeft = (pEDIndex >= EDMinIndex);
  pRight = (pEDIndex <= EDMaxIndex);
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
bool TPWA::RecalculateT1Dependants(const int pT1Index)
{
   if (Central.RecalculateT1Dependants(pT1Index)==false)
      return false;
   // Calculate AVI features on Radial and Aortic measurements when AVI enabled
   // If it fails, reset AVI and do not prevent PWA from calculating a report
   if ((MeasureType == PWA_RADIAL || MeasureType == PWA_AORTIC) && config_get_avi_option())
   {
      if (avi->Calculate(&Central) == false)
      {
         MsgBox_show(TWARNING,
                       MSG_MATH_ERROR,
                       LoadStr(MSG_AVI_ERROR_CALC),
                       MSG_AVI_ERROR_CALC, "");
         avi->Initialise();
      }
   }
   else
   {
      avi->Initialise();
   }

   // Calculate the correspondence of T1
   if (Central.T1 > Periph.T1)
   {
      T1Ratio = (Periph.T1 / Central.T1) * 100.0;
   }
   else
   {
      T1Ratio = (Central.T1 / Periph.T1) * 100.0;
   }

   if (Central.AP != DEFAULT_VALUE && Central.HR != DEFAULT_VALUE)
   {
      if (Central.HR < 40 || Central.HR > 110)
      {
         ReferenceAge = DEFAULT_VALUE;
      }
      else
      {
         if (patient_is_male())
         {
            if (Height != DEFAULT_VALUE && Height > 0)
            {
               ReferenceAge = (float)((4.77 * Central.AP) + (0.234 * Height) + (0.80 * Central.HR) - 79.4);
            }
         }
         else
         {
            if (Height != DEFAULT_VALUE && Height > 0)
            {
               ReferenceAge = (float)((4.2 * Central.AP) + (0.311 * Height) + (0.91 * Central.HR) - 110);
            }
         }
      }
   }
   else
   {
      ReferenceAge = DEFAULT_VALUE;
   }

   // PM CR

   // The priority for the inconclusive note is set as:
   // 1. Central AIx
   // 2. Max dP/dt
   // 3. Central T1
   // 4. Peripheral T1
   // 5. T1 Ratio
   // 6. Operator Index
   if (Central.AGPH >= 50.0)
   {
      CalcIsInconclusive = true;
      InconclusiveNote = AORTIC_AIX_NOTE;
   }
   else if (Periph.MaxdPdt < MEAS_MIN_DPDT)
   {
      CalcIsInconclusive = true;
      InconclusiveNote = MAXDPDT_NOTE;
   }
   else if (Central.T1 == DEFAULT_VALUE || Central.T1 < PWA_MIN_T1 || Central.T1 > PWA_MAX_T1)
   {
      CalcIsInconclusive = true;
      InconclusiveNote = AORTIC_TI_NOTE;
   }
   else if (Periph.T1 == DEFAULT_VALUE || Periph.T1 < PWA_MIN_T1 || Periph.T1 > PWA_MAX_T1)
   {
      CalcIsInconclusive = true;
      InconclusiveNote = PERIPHERAL_TI_NOTE;
   }
   else
   {
      if (T1Ratio < PWA_MIN_T1_RATIO)
      {
         CalcIsInconclusive = true;
         InconclusiveNote = T1_RATIO_NOTE;
      }
      else if (Periph.OperatorIndex < PWA_MIN_OPERATOR_INDEX)
      {
         CalcIsInconclusive = true;
         InconclusiveNote = OPERATOR_INDEX_NOTE;
      }
   }

  // Success
  return true;
}

//---------------------------------------------------------------------------
// Check whether T1 is within valid window
//---------------------------------------------------------------------------
bool TPWA::CheckT1Limitations(const int pT1Index, bool &pLeft, bool &pRight)
{
  // Validation
  if (Central.T1 == DEFAULT_VALUE || Central.T1 <= 0)
    return false;

  int T1MinIndex = Central.ExpPulse.TimeToIndex(PWA_MIN_T1);
  int T1MaxIndex = Central.ExpPulse.TimeToIndex(PWA_MAX_T1);

  // Actual check
  pLeft = (pT1Index >= T1MinIndex);
  pRight = (pT1Index <= T1MaxIndex);
  // Success
  return true;
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
bool TPWA::RecalculateT2Dependants(const int pT2Index)
{
   if (Central.RecalculateT2Dependants(pT2Index)==false)
    return false;

   // Calculate the correspondence of T1
   if (Central.T1 > Periph.T1)
   {
      T1Ratio = (Periph.T1 / Central.T1) * 100.0;
   }
   else
   {
      T1Ratio = (Central.T1 / Periph.T1) * 100.0;
   }

   if (Central.AP != DEFAULT_VALUE && Central.HR != DEFAULT_VALUE)
   {
      if (Central.HR < 40 || Central.HR > 110)
      {
         ReferenceAge = DEFAULT_VALUE;
      }
      else
      {
         if (patient_is_male())
         {
            if (Height != DEFAULT_VALUE && Height > 0)
            {
               ReferenceAge = (float)((4.77 * Central.AP) + (0.234 * Height) + (0.80 * Central.HR) - 79.4);
            }
         }
         else
         {
            if (Height != DEFAULT_VALUE && Height > 0)
            {
               ReferenceAge = (float)((4.2 * Central.AP) + (0.311 * Height) + (0.91 * Central.HR) - 110);
            }
         }
      }
   }
   else
   {
      ReferenceAge = DEFAULT_VALUE;
   }

   // PM CR

   // The priority for the inconclusive note is set as:
   // 1. Central AIx
   // 2. Central T1
   // 3. Peripheral T1
   // 4. T1 Ratio
   // 5. Operator Index
   if (Central.AGPH >= 50.0)
   {
      CalcIsInconclusive = true;
      InconclusiveNote = AORTIC_AIX_NOTE;
   }
   else if (Periph.MaxdPdt < MEAS_MIN_DPDT)
   {
      CalcIsInconclusive = true;
      InconclusiveNote = MAXDPDT_NOTE;
   }
   else if (Central.T1 == DEFAULT_VALUE || Central.T1 < PWA_MIN_T1 || Central.T1 > PWA_MAX_T1)
   {
      CalcIsInconclusive = true;
      InconclusiveNote = AORTIC_TI_NOTE;
   }
   else if (Periph.T1 == DEFAULT_VALUE || Periph.T1 < PWA_MIN_T1 || Periph.T1 > PWA_MAX_T1)
   {
      CalcIsInconclusive = true;
      InconclusiveNote = PERIPHERAL_TI_NOTE;
   }
   else
   {
      if (T1Ratio < PWA_MIN_T1_RATIO)
      {
         CalcIsInconclusive = true;
         InconclusiveNote = T1_RATIO_NOTE;
      }
      else if (Periph.OperatorIndex < PWA_MIN_OPERATOR_INDEX)
      {
         CalcIsInconclusive = true;
         InconclusiveNote = OPERATOR_INDEX_NOTE;
      }
   }
  // Success
  return true;
}

//---------------------------------------------------------------------------
// Check whether T2 is within valid window
//---------------------------------------------------------------------------
bool TPWA::CheckT2Limitations(const int pT2Index, bool &pLeft, bool &pRight)
{
  // Validation
  if (Central.T2 == DEFAULT_VALUE || Central.T2 <= 0)
    return false;

  int T2MinIndex;
  int T2MaxIndex;

  if (Central.T1 != DEFAULT_VALUE)
      T2MinIndex = Central.ExpPulse.TimeToIndex(Central.T1);
  else
      T2MinIndex = Central.ExpPulse.TimeToIndex(PWA_MIN_T1);

  if (Central.ED != DEFAULT_VALUE)
      T2MaxIndex = Central.ExpPulse.TimeToIndex(Central.ED);
  else
      T2MaxIndex = Periph.ExpPulse.Length() * PWA_ED_TOP_PERCENT;

  // Actual check
  pLeft = (pT2Index >= T2MinIndex);
  pRight = (pT2Index <= T2MaxIndex);
  // Success
  return true;
}

/* ###########################################################################
 ** AssignCentralTrigPts()
 **
 ** DESCRIPTION
 **  Assign trigger points for central with accounting
 **  16 points shift between Central and Radial
 ** INPUT
 **  None
 ** OUTPUT
 ** RETURN
 **  boolean success or not
*/
//---------------------------------------------------------------------------
bool TPWA::AssignCentralTrigPts()
{

  short int lShift;
  switch (MeasureType)
  {
    case PWA_RADIAL:
      lShift = NOF_TF_COEFF;
      break;
    case PWA_CAROTID:
      lShift = 20; //(NOF_TF_COEFF - 1)/2;
      break;
    case PWA_AORTIC: // No transformation
      lShift = 0;
      break;
    default:
      MsgBox(TERROR, GetCurrentPwaMeasureDetails(), MSG_VALIDATION_ERROR, MSG_INVALID_MTYPE);
      return false;
  }

  Central.NofOnsets = Periph.NofOnsets;
  for (int i=0; i < Central.NofOnsets; i++)
  {
    Central.TrigPts[i] = (short int) (Periph.TrigPts[i] - lShift);
  }
  // Success
  return (Central.NofOnsets > 1);
}

/* ###########################################################################
 ** RejectIrregularTrigPts()
 **
 ** DESCRIPTION
 **  Compare Periph and Central trigger points and Reject irregulars
 ** INPUT
 **  PWA Class
 ** OUTPUT
 ** RETURN
 **  boolean success or not
*/
//---------------------------------------------------------------------------
bool TPWA::RejectIrregularTrigPts()
{
  // Perform only for Radial or Carotid
  if (MeasureType != PWA_RADIAL && MeasureType != PWA_CAROTID)
  {
    return true;
  }
  // Check Trigger points correspondence
  // Initialisation
  int NofValidTrigs = 0;    // Actual number of valid trigger points
  int PeriphIndex = 0, CentralIndex = 0;
  // Allocate memory for valid Trigger points
  int lMaxNofTr = max (Periph.NofOnsets, Central.NofOnsets);
  // int lMinNofTr = min (Periph.NofOnsets, Central.NofOnsets);
  short int *lNewPeriphTrigs = new short int [lMaxNofTr];
  short int *lNewCentralTrigs = new short int [lMaxNofTr];
  // Loop
  for (int ltr = 0; ltr < lMaxNofTr; ltr++)
  {
    // Get current onsets
    short int PeriphOnset = Periph.TrigPts[PeriphIndex];
    short int CentralOnset = Central.TrigPts[CentralIndex];
    // Check last trigger point
    if (PeriphIndex >= Periph.NofOnsets || CentralIndex >= Central.NofOnsets)
      break;
    // Comparison
    if (PeriphOnset > CentralOnset)
    {
      // Check additional Central before PeriphOnset
      if (CentralIndex == Central.NofOnsets - 1 || PeriphOnset < Central.TrigPts[CentralIndex+1])
      {
        lNewPeriphTrigs[NofValidTrigs] = PeriphOnset;
        lNewCentralTrigs[NofValidTrigs] = CentralOnset;
        NofValidTrigs++;
        CentralIndex++;
        PeriphIndex++;
      }
      else
      {
        CentralIndex++;
        continue;
      }
    }
    else // PeriphOnset < CentralOnset
    {
      PeriphIndex++;
      continue;
    }
  }
  // Validation
  if (NofValidTrigs <= 1)
  {
    MsgBox(TERROR, GetCurrentMeasureDetails(), MSG_MATH_ERROR, MSG_TRIGGER_ERR);
    delete [] lNewPeriphTrigs;
    delete [] lNewCentralTrigs;
    return false;
  }
  // Copy new trigger points to the places for old
  for (int i=0; i < lMaxNofTr; i++)
  {
    Periph.TrigPts[i] = (i < NofValidTrigs ? lNewPeriphTrigs[i] : (short int)-1);
    Central.TrigPts[i] = (i < NofValidTrigs ? lNewCentralTrigs[i] : (short int)-1);
  }
  Periph.NofOnsets = NofValidTrigs;
  Central.NofOnsets = NofValidTrigs;
  // Free memory
  delete [] lNewPeriphTrigs;
  delete [] lNewCentralTrigs;
  // Success
  return true;

}

/* ###########################################################################
 ** CalibrateAvPulses()
 **
 ** DESCRIPTION
 **  Calibrate together AvPulses for Central and Peripheral pressures
 ** INPUT
 **  PWA Class
 ** OUTPUT
 **  boolean success or not
*/
//---------------------------------------------------------------------------
bool TPWA::CalibrateAvPulses(const float pGain, const float pOffset)
{
  // Find Min, Max, Gain and Offset for different type of measurement
  // using Sp, Dp, MeanP entered by operator
  float lGain, lOffset, lMin, lMax, lAver;
  bool ret;
  switch (MeasureType)
  {
    case PWA_RADIAL:
      //ret = Periph.AvPulse.MinMax (lMin, lMax);
      lMax = Periph.AvPulse.Max(0, Periph.AvPulse.End);
      lMin = Periph.AvPulse.Min(0, Periph.AvPulse.End * PWA_EFFECTIVE_PULSE_LENGTH_PERCENT);
      lAver = Periph.AvPulse.Integral(0, Periph.AvPulse.End)
              /(Periph.AvPulse.Length() - 1);
      break;
    case PWA_CAROTID:
      // ret = Central.AvPulse.MinMax (lMin, lMax);
      lMax = Central.AvPulse.Max(0, Central.AvPulse.End);
      lMin = Central.AvPulse.Min(0, Central.AvPulse.End * PWA_EFFECTIVE_PULSE_LENGTH_PERCENT);
      lAver = Central.AvPulse.Integral(0, Central.AvPulse.End)
              /(Central.AvPulse.Length() - 1);
      break;
    case PWA_AORTIC:
      // ret = Periph.AvPulse.MinMax (lMin, lMax);
      lMax = Periph.AvPulse.Max(0, Periph.AvPulse.End);
      lMin = Periph.AvPulse.Min(0, Periph.AvPulse.End * PWA_EFFECTIVE_PULSE_LENGTH_PERCENT);
      lAver = Periph.AvPulse.Integral(0, Periph.AvPulse.End)
              /(Periph.AvPulse.Length() - 1);
      break;
    default:
      return false;
  }

  if (/*ret == false || */lAver <= lMin || lMin >= lMax)
    return false;

  // Find Gain and Offset
  if (pGain == 0.)
  {
    if (Sp > Dp)
    {
      lGain = (Sp - Dp) / (lMax - lMin);
      lOffset = Sp - lGain*lMax;
    }
    else if (MeanP > Dp)
    {
      lGain = (MeanP - Dp) / (lAver - lMin);
      lOffset = MeanP - lGain*lAver;
    }
  }
  else // Calibrated signal with pGain, pOffset for particular device
  {
    lGain = pGain;
    lOffset = pOffset;
  }

  // Transform using the same Gain and Offset for both Periph and Central AvPulses
  float pMin, pMax, cMin, cMax;
  bool ret1 = Periph.CalibratePulse (lGain, lOffset, pMin, pMax);
  bool ret2 = Central.CalibratePulse(lGain, lOffset, cMin, cMax);
  ret =  ret1 && ret2;
  if (ret == false)
    return false;

  // Work out Sp, Dp and adjust offset to make Mp(Central) = Mp(Periph)
  float lPeriphAver = Periph.CalAvPulse.Integral(0, Periph.CalAvPulse.End)
        /(Periph.CalAvPulse.Length() - 1);
  float lCentralAver = Central.CalAvPulse.Integral(0, Central.CalAvPulse.End)
        /(Central.CalAvPulse.Length() - 1);
  switch (MeasureType)
  {
    case PWA_RADIAL:
      if (lPeriphAver != lCentralAver)
      {
        for (int i=0; i < Central.CalAvPulse.Size(); i++)
        {
          Central.CalAvPulse.Profile[i] += lPeriphAver - lCentralAver;
        }
      }
      //Central.CalAvPulse.MinMax(cMin, cMax);
      //Periph.CalAvPulse.MinMax(pMin, pMax);
      pMax = Periph.CalAvPulse.Max(0, Periph.CalAvPulse.End);
      pMin = Periph.CalAvPulse.Min(0, Periph.CalAvPulse.End * PWA_EFFECTIVE_PULSE_LENGTH_PERCENT);
      cMax = Central.CalAvPulse.Max(0, Central.CalAvPulse.End);
      cMin = Central.CalAvPulse.Min(0, Central.CalAvPulse.End * PWA_EFFECTIVE_PULSE_LENGTH_PERCENT);
      // Find Gain and Offset
      if (pGain == 0.)
      {
        Periph.Sp = (Sp > 0 ? Sp : pMax);
        Periph.Dp = Dp;
        Central.Sp = cMax;
        Central.Dp = cMin;
      }
      else
      {
        Periph.Sp = pMax;
        Periph.Dp = pMin;
        Central.Sp = cMax;
        Central.Dp = cMin;
      }
      break;
    case PWA_CAROTID:
      if (lPeriphAver != lCentralAver)
      {
        for (int i=0; i < Periph.CalAvPulse.Size(); i++)
        {
          Periph.CalAvPulse.Profile[i] += lCentralAver - lPeriphAver;
        }
      }
      //Periph.CalAvPulse.MinMax(pMin, pMax);
      //Central.CalAvPulse.MinMax(cMin, cMax);
      pMax = Periph.CalAvPulse.Max(0, Periph.CalAvPulse.End);
      pMin = Periph.CalAvPulse.Min(0, Periph.CalAvPulse.End * PWA_EFFECTIVE_PULSE_LENGTH_PERCENT);
      cMax = Central.CalAvPulse.Max(0, Central.CalAvPulse.End);
      cMin = Central.CalAvPulse.Min(0, Central.CalAvPulse.End * PWA_EFFECTIVE_PULSE_LENGTH_PERCENT);
      if (pGain == 0.)
      {
        Central.Sp = (Sp > 0 ? Sp : cMax);
        Central.Dp = Dp;
        Periph.Sp = pMax;
        Periph.Dp = pMin;
      }
      else
      {
        Central.Sp = cMax;
        Central.Dp = cMin;
        Periph.Sp = pMax;
        Periph.Dp = pMin;
      }
      break;
    case PWA_AORTIC:
      //Central.CalAvPulse.MinMax(cMin, cMax);
      //Periph.CalAvPulse.MinMax(pMin, pMax);
      pMax = Periph.CalAvPulse.Max(0, Periph.CalAvPulse.End);
      pMin = Periph.CalAvPulse.Min(0, Periph.CalAvPulse.End * PWA_EFFECTIVE_PULSE_LENGTH_PERCENT);
      cMax = Central.CalAvPulse.Max(0, Central.CalAvPulse.End);
      cMin = Central.CalAvPulse.Min(0, Central.CalAvPulse.End * PWA_EFFECTIVE_PULSE_LENGTH_PERCENT);
      if (pGain == 0.)
      {
        Periph.Sp = (Sp > 0 ? Sp : pMax);
        Periph.Dp = Dp;
        Central.Sp = cMax;
        Central.Dp = cMin;
      }
      else
      {
        Central.Sp = cMax;
        Central.Dp = cMin;
        Periph.Sp = pMax;
        Periph.Dp = pMin;
      }
      break;
    default:
      return false;
  }
  Periph.CalAvPulse.SampleRate = Periph.AvPulse.SampleRate;
  Central.CalAvPulse.SampleRate = Central.AvPulse.SampleRate;
  return true;
}

/* ###########################################################################
 ** PrepareToCaptureSignal()
 **
 ** DESCRIPTION
 **  Preparing TPWA object to store signal
 ** INPUT
 **  none
 ** OUTPUT
 **  Appropriate properties have set up
 ** RETURN
 **  none
*/
//---------------------------------------------------------------------------
void TPWA::PrepareToCaptureSignal()
{
  // Clear up everything except Sp, Dp, Meanp ...
  Initialise();
  // Set up ready flag
  Periph.PrepareToCapture();
}

/* ###########################################################################
 ** CaptureSignal()
 **
 ** DESCRIPTION
 **  Store whole signal from tonometer in Signal array
 ** INPUT
 **  short int * input  - integer signal
 **  int pLength
 ** OUTPUT
 ** RETURN
 **  none
*/
/*
//---------------------------------------------------------------------------
bool TPWA::CaptureSignal(const short int *pInput, const int pLength)
{
  if (ReadyToCapture==false) return false;
  return Periph.CaptureSignal(pInput, pLength);
}
*/
/* ###########################################################################
 ** CaptureSignalPacket()
 **
 ** DESCRIPTION
 **  Store signal packet from tonometer in PressurePeriph class
 ** INPUT
 **  short int * input  - integer signal
 **  int pLength - packet length
 ** OUTPUT
 ** RETURN
 **  none
*/
//---------------------------------------------------------------------------
/*
bool TPWA::CaptureSignalPacket(const short int *pInput, const int pLength)
{
  if (ReadyToCapture==false) return false;
  return Periph.CaptureSignal(pInput, pLength);
}
*/

bool TPWA::SaveToFile()
{
  PATIENT_RECORD_TYPE  pat;
  if (patient_get(&pat))
  {
    String lFileName = ExtractFilePath(Application->ExeName) + EXPORT_SUBDIR + "pwa_session_" +
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
