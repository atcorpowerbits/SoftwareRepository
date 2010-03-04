//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include <stdio.h>
#include <stdlib.h>

#include <msg\pubserv.h>
#include <log\pubserv.h>
#include <meas\pubserv.h>
#include <patient\pubserv.h>
#include <dbmgr\pubserv.h>
#include <config/pubserv.h>
#include "pwm.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
const int NOF_CONSTANT_SAMPLES = 15; // Nof samples to get constant area for MedWave device
//---------------------------------------------------------------------------
extern float coeff_radial[NOF_TF_COEFF];
extern float coeff_carotid[NOF_TF_COEFF];

static TPWM pwm;

TPWM*  meas_get_current_pwm (void)
{
  return &pwm;
}

String meas_pwm_get_pwm_table_name()
{
  return MPWM;
}
String meas_pwm_get_session_table_name()
{
  return MPWMSESSION;
}
String meas_pwm_get_trend_table_name()
{
  return MPWMTREND;
}
String meas_pwm_get_device_table_name()
{
  return "PWM_DEVICE";
}

/* ###########################################################################
 ** GetCurrentPwmMeasureDetails()
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
String GetCurrentPwmMeasureDetails()
{
  String ret = "";
  TPWM* pwm = meas_get_current_pwm();
  if (pwm==NULL) return ret;
  ret = "PWM -> Patient :" + IntToStr(pwm->Patient_No);
  ret = ret + ", Session :" + IntToStr(pwm->Session_ID);
  ret = ret + ", Measurement :" + pwm->DateTime.DateTimeString();
  ret = ret + ", DataRevision :" + IntToStr(pwm->DataRev);
  return ret;
}


// ###########################################################################
// Public constructor for TPWM Measurement Class
//---------------------------------------------------------------------------
TPWM::TPWM() : TPWA()
{
  RadialBuffer = new TAtCorStack<float>(NOF_TF_COEFF);
  FParamList = new TStringList();
  CreateParamsMap();

  // Initialise other properties
  event_comment = new TStringList();
  periph_buffer = new float [PRESSURE_PULSE_MAXLENGTH];
  Initialise();
}
//---------------------------------------------------------------------------
TPWM::~TPWM()
{
  delete RadialBuffer;
  delete FParamList;
  if (event_comment != NULL)
   {
      event_comment->Clear();
      delete event_comment;
   }
   if (periph_buffer != NULL)
   {
      delete periph_buffer;
   }
}

//---------------------------------------------------------------------------
// Class initialisator
//---------------------------------------------------------------------------
void TPWM::Initialise()
{
  Session_ID = 0;
  SessionStart = NULL;
  SessionFinished = NULL;
  SessionNotes = "";
  SessionMedication = "";

  DeviceID = -1;
  DeviceName = "";
  Calibrated = false;
  Continuous = true;
  CalibrationRatio = 1;
  CalibrationOffset = 0;

  TrendSamplePeriod = 5;
  TrendRefreshPeriod = -1;
  ReportGenerationPeriod = -1;
  AorticSendOut = false;
  PeriphSendOut = false;
  EventMarker = DEFAULT_VALUE;
  event_comment->Clear();
  periph_buff_len = 0;

  //ReadyToStore = false;

  // Initialise Pressures
  TPWA::Initialise();
}

void TPWM::SetDefaults()
{
  Session_ID = 0;
  SessionStart = NULL;
  SessionFinished = NULL;
  SessionNotes = "";
  SessionMedication = "";

  DeviceID = -1;
  DeviceName = "";
  Calibrated = false;
  Continuous = true;
  CalibrationRatio = 1;
  CalibrationOffset = 0;

  TrendSamplePeriod = 5;
  TrendRefreshPeriod = -1;
  ReportGenerationPeriod = -1;
  AorticSendOut = false;
  PeriphSendOut = false;
  EventMarker = DEFAULT_VALUE;
  event_comment->Clear();
  periph_buff_len = 0;

  //ReadyToStore = false;

  // Initialise Pressures
  TMeasure::Initialise();
  TPWA::Initialise();
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
bool TPWM::Populate(TDataSet* pDataSet)
{

  Session_ID = pDataSet->FieldByName(MPWM_SESSION_ID)->AsInteger;
  return TPWA::Populate(pDataSet);
}

//---------------------------------------------------------------------------
bool TPWM::PopulateSession(TDataSet* pSessionTable)
{
  try
  {
    if (pSessionTable->RecordCount <= 0)
    {
      SetDefaults();
      System_ID = patient_get_system_id();
      Patient_No = patient_get_number();
      Study_ID = patient_get_study_id();
      return true;
    }
    event_comment->Clear();

    TLocateOptions SearchOptions;
    SearchOptions.Clear();
    TADOTable* pDeviceTable = dynamic_cast<TADOTable *> (dbmgr_get_dataset(DBMGR_DEVICE_TABLE, false));

    System_ID   = pSessionTable->FieldByName(MPW_SYSTEM_ID)->AsString;
    Study_ID    = pSessionTable->FieldByName(MPW_STUDY_ID)->AsString;
    Patient_No  = pSessionTable->FieldByName(MPW_PATIENT_NO)->AsInteger;

    Session_ID   = pSessionTable->FieldByName(MPWM_SESSION_ID)->AsInteger;
    SessionStart = pSessionTable->FieldByName(MPWM_SESSION_START)->AsDateTime;
    SessionFinished = pSessionTable->FieldByName(MPWM_SESSION_FINISHED)->AsDateTime;
    SessionNotes = pSessionTable->FieldByName(MPWM_SESSION_NOTES)->AsString;
    SessionMedication  = pSessionTable->FieldByName(MPW_MED)->AsString;
    Operator = pSessionTable->FieldByName(MPW_OPERATOR)->AsString;

    Calibrated = pSessionTable->FieldByName(MPWM_SESSION_CALIBRATED)->AsBoolean;
    DeviceID = pSessionTable->FieldByName(MPWM_SESSION_DEVICE_ID)->AsInteger;
    event_comment->CommaText = pSessionTable->FieldByName(MPWM_SESSION_EVENT_COMMENT)->AsString;

    // Populate from the device table as well.
    pDeviceTable->Open();
    if( pDeviceTable->Locate(MPWM_SESSION_DEVICE_ID, DeviceID, SearchOptions))
    {
       CalibrationRatio = pDeviceTable->FieldByName(MPWM_DEVICE_CALIBRATION_RATIO)->AsFloat;
       CalibrationOffset = pDeviceTable->FieldByName(MPWM_DEVICE_CALIBRATION_OFFSET)->AsFloat;
       DeviceName = pDeviceTable->FieldByName(MPWM_DEVICE_NAME)->AsString;
    }

    MeasureType = PwaFindMeasureType(pSessionTable->FieldByName(MPWA_SUB_TYPE)->AsString);
    Sp = pSessionTable->FieldByName(MPW_SP)->AsFloat;
    Dp = pSessionTable->FieldByName(MPW_DP)->AsFloat;
    MeanP = pSessionTable->FieldByName(MPW_MP)->AsFloat;

    Height = pSessionTable->FieldByName(MPW_HEIGHT)->AsFloat;
    Weight = pSessionTable->FieldByName(MPW_WEIGHT)->AsFloat;
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

    if (pSessionTable->FindField(MPWM_TREND_SAMPLE_PERIOD) != NULL)
      TrendSamplePeriod = pSessionTable->FieldByName(MPWM_TREND_SAMPLE_PERIOD)->AsInteger;
    else
      TrendSamplePeriod = 5;

    if (pSessionTable->FindField(MPW_SIMULATION)!=NULL)
    {
      Simulation = pSessionTable->FieldByName(MPW_SIMULATION)->AsInteger;
    }
  }
  catch (Exception &exception)
  {
     MsgBox_show(TERROR,
                 MSG_EXCEPTION,
                 LoadStr(MSG_POP_EXC),
                 MSG_POP_EXC,
                 LoadStr(MSG_POP_EXC) +GetCurrentPwmMeasureDetails() +exception.Message);
    return false;
  }
  return true;
}

//---------------------------------------------------------------------------
// Create map of parameters to be stored to file
//---------------------------------------------------------------------------
void TPWM::CreateParamsMap()
{
   FParamList->AddObject("Radial Sp", (TObject *)&Periph.Sp);
   FParamList->AddObject("Radial Dp", (TObject *)&Periph.Dp);
   FParamList->AddObject("Aortic Sp", (TObject *)&Central.Sp);
   FParamList->AddObject("Aortic Dp", (TObject *)&Central.Dp);
   FParamList->AddObject("Mean P", (TObject *)&Central.MeanP);
   FParamList->AddObject("Heart rate", (TObject *)&Central.HR);
   FParamList->AddObject("Ejection duration", (TObject *)&Central.ED);
   FParamList->AddObject("Aortic T1", (TObject *)&Central.T1);
   FParamList->AddObject("Aortic T2", (TObject *)&Central.T2);
   FParamList->AddObject("AI1", (TObject *)&Central.AI1);
   FParamList->AddObject("Aortic AP", (TObject *)&Central.AP);
   FParamList->AddObject("Mean pressure systolic", (TObject *)&Central.MPS);
   FParamList->AddObject("Mean pressure diastolic", (TObject *)&Central.MPD);
   FParamList->AddObject("End systolic pressure", (TObject *)&Central.ESP);

   FParamList->AddObject("SEVR", (TObject *)&Central.SVI);

   FParamList->AddObject("Period", (TObject *)&Central.Period);
   //FParamList->AddObject("ED/Period", (TObject *)&Central.EDPeriod);
   FParamList->AddObject("Aortic PP", (TObject *)&Central.PH);
   FParamList->AddObject("Augmentation index", (TObject *)&Central.AGPH);
   FParamList->AddObject("Event Marker", (TObject *)&EventMarker);
   FParamList->AddObject("Aortic Tr", (TObject *)&Central.Tr);

}

/* ###########################################################################
 ** GetParamIndex()
 **
 ** DESCRIPTION
 **  Get index of parameter in params map
 ** INPUT
 **  String pParamName - name
 ** OUTPUT
 **  None
 ** RETURN
 **  Index of parameter or -1 if wrong
*/
//---------------------------------------------------------------------------
int TPWM::GetParamIndex(const String pParamName)
{
  return FParamList->IndexOf(pParamName);
}

//---------------------------------------------------------------------------
void TPWM::PrepareToCapture()
{
  // Clear up everything except Sp, Dp, Meanp ...
  TPWA::Initialise();
  // Set up ready flag
  ReadyToCapture = true;
  (*RadialBuffer).Clear();
}
/* ###########################################################################
 ** StoreSignal()
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
bool TPWM::StoreSignal(const short int *pInput, const int pLength)
{
  if (ReadyToStore==false) return false;
  return Periph.StoreSignal(pInput, pLength);
}
*/
/* ###########################################################################
 ** StoreSignalPacket()
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
bool TPWM::StoreSignalPacket(const short int *pInput, const int pLength)
{
   bool ret;
   if (ReadyToCapture==false)
   {
      PrepareToCapture();
   }
   // Continous uncalibrated PWM
   for (int i=0; i<pLength; i++)
   {
     RadialBuffer->Push(pInput[i]);
   }
   ret = true;
   return ret;
}

/*
//---------------------------------------------------------------------------
// Pulse broker
// Storing packet with identifying end of the pulse for MedWave device
//---------------------------------------------------------------------------
bool TPWM::StoreSignalPacket(const short int *pInput, const int pLength,
                             bool &pReadyToCalculate)
{
   const short int DUMMY_VALUE = -9999;
   short int first;
   pReadyToCalculate = false;
   if (ReadyToCapture==false)
   {
     PrepareToCapture();
     OldValues->Fill(DUMMY_VALUE);
     WeAreInPeak = false;
     Beginning = false;
   }
   for (int i=0; i<pLength; i++)
   {
     RadialBuffer->Push(pInput[i]);
     if (WeAreInPeak == false)
     {
       first = OldValues->First();
       if (first==DUMMY_VALUE)
       {
           OldValues->Push(pInput[i]);
           continue;
       }
       if (OldValues->IsEqual(pInput[i]))
       {
         Beginning = true;
         continue;
       }

       //if (Beginning && pInput[i]!=OldValues->Last())
       if (Beginning && pInput[i]!=OldValues->First())
       {
         WeAreInPeak = true;
       }

       OldValues->Push(pInput[i]);
       continue;
     }
     else // We are in peak
     {
       if (OldValues->IsEqual(pInput[i]))
       {
         pReadyToCalculate = true;
         WeAreInPeak = false;
         Beginning = false;
         OldValues->Fill(DUMMY_VALUE);
         continue;
       }
       else
       {
         OldValues->Push(pInput[i]);
         continue;
       }
     }
   }
   return pReadyToCalculate;
}
*/

/* ###########################################################################
 ** GetAorticValue()
 **
 ** DESCRIPTION
 **  Calculate aortic value for Radial buffer and return
 ** INPUT
 ** OUTPUT
 **  none
 ** RETURN
 **  Calculated Aortic value or -1
*/
//---------------------------------------------------------------------------
float TPWM::GetAorticValue()
{
  if (ReadyToCapture == false || RadialBuffer->Full() == false)
  {
    return -1.;
  }
  switch (MeasureType)
  {
    case PWA_RADIAL:
      return Convolution1(coeff_radial);
    case PWA_CAROTID:
      return Convolution1(coeff_carotid);
    case PWA_AORTIC: // No transformation
      return (*RadialBuffer)[0];
    default:
      throw Exception(LoadStr(MSG_INVALID_MTYPE));
  }
}

/* ###########################################################################
 ** Convolution1()
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
float TPWM::Convolution1(const float *pTfc)
{
  // Calculate Central for Radial buffer
  double ld = 0.0;
  for(int j = 0; j < RadialBuffer->Size(); j++ )
  {
    float rb = (*RadialBuffer)[j];
    ld += pTfc[j] * rb;
  }
  return (float)ld;
}

/* ###########################################################################
 ** PrepareToStoreParamsToFile()
 **
 ** DESCRIPTION
 **  Store monitored parameters to file with automatic closing
 ** INPUT
 **  pFileHandle - File
 ** OUTPUT
 ** RETURN
 **  success or not
*/
//------------------------------------------------------------
bool TPWM::PrepareToStoreParamsToFile(const String pFileName,
                                      const int pLimitNofStrings,
                                      TStrings *pParamList)
{
   String  param_file_path;
  // Validation
  if (Session_ID <= 0 )
  {
    MsgBox("Session has not been created", SERROR, MB_ICONSTOP);
    return false;
  }
  if (System_ID == "" || Patient_No <= 0 || Study_ID == "")
  {
    MsgBox("Invalid SystemID, PatientNo or StudyID", SERROR, MB_ICONSTOP);
    return false;
  }

  // Validation
  if (FFileHandle > 0)
  {
     FileClose(FFileHandle);
  }
  param_file_path = ExtractFilePath(ParamStr(0)) +pFileName;
  FFileHandle = FileCreate(param_file_path);
  if (FFileHandle <= 0)
  {
     MsgBox("Error creating parameters file", SERROR, MB_ICONSTOP);
     return false;
  }

  if (pParamList!=NULL && pParamList->Count<=0)
  {
     MsgBox("Empty list of parameters to be stored to file", SERROR, MB_ICONSTOP);
     return false;
  }

  // Store SystemID, PatientNo... if file header
  String lTitle = System_ID + "," + IntToStr(Patient_No)
                  +  "," + Study_ID + "," + IntToStr(Session_ID) + "\r\n";
  FileWrite(FFileHandle, lTitle.c_str(), lTitle.Length());

  // Keep file names
  if (pParamList!=NULL)
  {
    FParamList->Clear();
    FParamList->AddStrings(pParamList);
  }

  lTitle = FParamList->CommaText + "\r\n";

  // Write column names
  FileWrite(FFileHandle, lTitle.c_str(), lTitle.Length());
  FileClose(FFileHandle);
  FFileHandle = -1;

  // Initialise class variables
  FParamsFileName = param_file_path;
  FLimitNofStrings = (pLimitNofStrings > 0 ? pLimitNofStrings : 10);
  FNofStrings = 0;
  FAllStoredStrings = 0;

  // Success
  return true;
}

/* ###########################################################################
 ** StoreParamsToFile()
 **
 ** DESCRIPTION
 **  Store monitored parameters to file with automatic closing
 ** INPUT
 **  None
 ** OUTPUT
 **  ErrorString - String with error description, if any
 ** RETURN
 **  Nof stored parameters
*/
//----------------------------------------------------------------
int TPWM::StoreParamsToFile(String &ErrorString)
{
  ErrorString = "";
  int lNofStored = 0;

  // Validation
  if (FFileHandle <= 0 && FParamsFileName == "")
  {
    ErrorString = "No file to store PWM parameters to";
    return lNofStored;
  }
  else if (FFileHandle <= 0 && FParamsFileName != "")
  {
    FFileHandle = FileOpen(FParamsFileName, fmOpenReadWrite);
    int lFileLength = FileSeek(FFileHandle, 0, 2);
    if (FFileHandle <= 0 || lFileLength < 0)
    {
      ErrorString = "Error opening file " + FParamsFileName;
      return lNofStored;
    }
  }
  if (FFileHandle <= 0)
  {
    ErrorString = "Error opening file " + FParamsFileName;
    return lNofStored;
  }

  // Prepare comma-delimited parameter string from FParamList map
  String lOut;
  for (int i=0; i<FParamList->Count; i++)
  {
    float *a = (float *) (FParamList->Objects[i]);
    lOut = lOut + RoundIntToStr(*a);
    if (i < FParamList->Count - 1)
      lOut = lOut + ",";
  }
  lOut = lOut + "\r\n";
  if (FileWrite(FFileHandle, lOut.c_str(), lOut.Length()) <= 0)
  {
    CloseParamsFile();
    ErrorString = "Error writing parameters ";
    return lNofStored;
  }
  FNofStrings++;
  FAllStoredStrings++;
  lNofStored = FAllStoredStrings;
  if (FNofStrings >= FLimitNofStrings)
  {
    CloseParamsFile();
    FNofStrings = 0;
  }
  return lNofStored;
}

//----------------------------------------------------------------
void TPWM::CloseParamsFile()
{
  FileClose(FFileHandle);
  FFileHandle = -1;
}

/* ###########################################################################
 ** TrendFileToDB()
 **
 ** DESCRIPTION
 **  Create PWMTrend Table from PWMTrend file
 ** INPUT
 **  pTrendFile - File
 **  pTrendTable - Table
 ** OUTPUT
 **  None
 ** RETURN
 **  Nof parameters successfully stored in PWMTrend table
*/
//------------------------------------------------------------
int TPWM::TrendFileToDB(const String pTrendFile, TADOTable *pTrendTable)
{
  int     lNofStored = 0;
  String  params_file_path;
  // Validation
  params_file_path = ExtractFilePath(ParamStr(0)) +pTrendFile;
  if (FileExists(params_file_path) == false)
  {
     MsgBox("PWM Trend file does not exist. FileName : " + pTrendFile, SERROR, MB_ICONSTOP);
     return lNofStored;
  }
  // Validation DataSet
  if (pTrendTable == NULL)
  {
    MsgBox("PWM Trend Table not defined", SERROR, MB_ICONSTOP);
    return lNofStored;
  }
  try
  {
      pTrendTable->Open();
  }
  catch (Exception &e)
  {
     Application->ShowException(&e);
  }
  if (pTrendTable->Active == false)
  {
    MsgBox("Error opening PWM Trend DataSet", SERROR, MB_ICONSTOP);
    return lNofStored;
  }
  pTrendTable->Close();

  // Open file for read
  FILE *lFileStream;
  lFileStream = fopen(params_file_path.c_str(), "r");
  if (lFileStream==NULL)
  {
    MsgBox("Error opening file " + pTrendFile, SERROR, MB_ICONSTOP);
    return lNofStored;
  }

  // Read File title and header from lFileStream
  String lTitle;
  lTitle.SetLength(400);
  if (fgets(lTitle.c_str(), lTitle.Length(), lFileStream)==NULL)
  {
    MsgBox("Error reading title of trend file " + pTrendFile, SERROR, MB_ICONSTOP);
    fclose(lFileStream);
    return lNofStored;
  }

  // Read comma-delimited SystemID, PatientID , Session ID...
  TStringList* lList = new TStringList();
  lList->CommaText = lTitle;
  if (lList->Count < 4)
  {
    MsgBox("Error reading title of file " + pTrendFile, SERROR, MB_ICONSTOP);
    fclose(lFileStream);
    lList->Clear();
    delete lList;
    return lNofStored;
  }

  String lSystem_ID = lList->Strings[0];
  int lPatient_No = lList->Strings[1].ToIntDef(0);
  String lStudy_ID = lList->Strings[2];
  int lSession_ID = lList->Strings[3].ToIntDef(0);
  lList->Clear();

  if (lSystem_ID == "" || lPatient_No <= 0 || lStudy_ID == "" || lSession_ID <= 0 )
  {
    MsgBox("Error reading title of file " + pTrendFile, SERROR, MB_ICONSTOP);
    fclose(lFileStream);
    lList->Clear();
    delete lList;
    return lNofStored;
  }

  // Read comma-delimited column names from lFileStream
  lTitle.SetLength(400);
  if (fgets(lTitle.c_str(), lTitle.Length(), lFileStream)==NULL)
  {
    MsgBox("Error reading title of file " + pTrendFile, SERROR, MB_ICONSTOP);
    fclose(lFileStream);
    lList->Clear();
    delete lList;
    return lNofStored;
  }
  TStringList* lColumnNames = new TStringList();
  lColumnNames->CommaText = lTitle;

  if (lColumnNames->Count <= 0)
  {
    MsgBox("Error reading title of file " + pTrendFile, SERROR, MB_ICONSTOP);
    fclose(lFileStream);
    lList->Clear();
    lColumnNames->Clear();
    delete lList;
    delete lColumnNames;
    return lNofStored;
  }

  String blob;
  short int *Buffer;
  TStringList *blob_list;

  // Read file for each parameter
  for (int np=0; np < lColumnNames->Count; np++)
  {
    try
    {
      fclose(lFileStream);
      lFileStream = fopen(params_file_path.c_str(), "r");
      // Skip 2 lines of titles
      fgets(lTitle.c_str(), lTitle.Length(), lFileStream);
      fgets(lTitle.c_str(), lTitle.Length(), lFileStream);
      // Insert new record in Trend Table
      pTrendTable->Close();
      pTrendTable->Open();
      pTrendTable->Append();
      int lNo = 0;
      blob_list = new TStringList();
      while (fgets(lTitle.c_str(), lTitle.Length(), lFileStream)!=NULL)
      {
        lList->Clear();
        lList->CommaText = lTitle;
        if (lList->Count < lColumnNames->Count)
        {
          break;
        }
        // Store param value as string in blob list
        String num = lList->Strings[np];
        blob_list->Add(num);
        lNo++;
      }
      if (lNo <= 0 && TrendSamplePeriod != 0)
      {
        MsgBox("Invalid PWMTrend file structure", SERROR, MB_ICONSTOP);
        fclose(lFileStream);
        pTrendTable->Cancel();
        pTrendTable->Close();
        lList->Clear();
        lColumnNames->Clear();
        delete lColumnNames;
        delete lList;
        return lNofStored;
      }

      // Convert param values to a short integer array, then pack to a string.
      Buffer = new short int[lNo];
      if (Buffer)
      {
         for (int i=0; i<lNo; i++)
         {
            Buffer[i] = (short int) blob_list->Strings[i].ToInt();
         }
         blob = PackToString(Buffer, lNo);
         delete Buffer;
      }
      // PM CR
      if (blob_list != NULL)
      {
         blob_list->Clear();
         delete blob_list;
      }
      pTrendTable->FieldByName(MPW_SYSTEM_ID)->AsString = lSystem_ID;
      pTrendTable->FieldByName(MPW_STUDY_ID)->AsString = lStudy_ID;
      pTrendTable->FieldByName(MPW_PATIENT_NO)->AsInteger = lPatient_No;
      pTrendTable->FieldByName(MPWM_SESSION_ID)->AsInteger = lSession_ID;
      pTrendTable->FieldByName(MPWM_PARAM_ID)->AsInteger = np + 1;
      pTrendTable->FieldByName(MPWM_PARAM_NAME)->AsString = lColumnNames->Strings[np];
      pTrendTable->FieldByName(MPWM_PARAM_TREND)->AsString = blob;
      pTrendTable->Post();
    }
    catch (Exception &e)
    {
      MsgBox("Error creating PWMTrend database with exception : \r\n" + e.Message,
              SERROR, MB_ICONSTOP);
      pTrendTable->Cancel();
      break;
    }

    lNofStored++;
  }
  // Success
  fclose(lFileStream);
  pTrendTable->Close();
  lList->Clear();
  lColumnNames->Clear();
  //blob_list->Clear();
  delete lColumnNames;
  delete lList;
  //delete blob_list;
  if (lNofStored > 0)
  {
    DeleteFile(params_file_path);
    FParamsFileName = "";
    FFileHandle = -1;
  }
  return lNofStored;
}

/* ###########################################################################
 ** CreateSession()
 **
 ** DESCRIPTION
 **  Create new record in PWMSession table
 ** INPUT
 **  pSessionID - File
 **  pSessionTable - Table
 ** OUTPUT
 **  None
 ** RETURN
 **  Nof parameters successfully stored in PWMTrend table
*/
//------------------------------------------------------------
bool TPWM::CreateNewSession(TADOTable *pSessionTable)
{
  // Validation DataSet
  if (pSessionTable==NULL)
  {
    MsgBox("Session table not defined", SERROR, MB_ICONSTOP);
    return false;
  }
  try
  {
    int lSessionID = 0;
    // Find unique SessionID
    pSessionTable->Open();
    pSessionTable->Filter = MPW_SYSTEM_ID + "='" + System_ID +
                            "' AND " + MPW_STUDY_ID + "='" + Study_ID +
                            "' AND " + MPW_PATIENT_NO + "=" + IntToStr(Patient_No);
    pSessionTable->Filtered = true;
    for (pSessionTable->First();!pSessionTable->Eof; pSessionTable->Next())
    {
      lSessionID = max(pSessionTable->FieldByName(MPWM_SESSION_ID)->AsInteger, lSessionID);
    }
    pSessionTable->Filter = "";
    pSessionTable->Filtered = false;
    Session_ID = lSessionID + 1;
    event_comment->Clear();
    SessionStart = Now();

    // Insert new record
    pSessionTable->Append();
    pSessionTable->FieldByName(MPW_SYSTEM_ID)->AsString = System_ID;
    pSessionTable->FieldByName(MPW_STUDY_ID)->AsString = Study_ID;
    pSessionTable->FieldByName(MPW_PATIENT_NO)->AsInteger = Patient_No;
    pSessionTable->FieldByName(MPWM_SESSION_ID)->AsInteger = Session_ID;

    // This is a fix to limit the precision of the DateTime field and allow equality tests, eg. Locate
    pSessionTable->FieldByName(MPWM_SESSION_START)->AsDateTime = StrToDateTime(DateTimeToStr(SessionStart));

    pSessionTable->FieldByName(MPWM_SESSION_NOTES)->AsString = SessionNotes;
    pSessionTable->FieldByName(MPW_MED)->AsString = SessionMedication;
    pSessionTable->FieldByName(MPW_OPERATOR)->AsString = Operator;

    pSessionTable->FieldByName(MPWM_SESSION_CALIBRATED)->AsBoolean = Calibrated;
    pSessionTable->FieldByName(MPWM_SESSION_DEVICE_ID)->AsInteger = DeviceID;

    pSessionTable->FieldByName(MPWA_SUB_TYPE)->AsString = PWAMTypeAsString[MeasureType];

    pSessionTable->FieldByName(MPW_SP)->AsFloat = Sp;
    pSessionTable->FieldByName(MPW_DP)->AsFloat = Dp;
    pSessionTable->FieldByName(MPW_MP)->AsFloat = MeanP;

    pSessionTable->FieldByName(MPW_HEIGHT)->AsFloat = Height;
    pSessionTable->FieldByName(MPW_WEIGHT)->AsFloat = Weight;
    Bmi = (Height > 0 && Height != DEFAULT_VALUE && Weight > 0 && Weight != DEFAULT_VALUE
          ? Weight / ((Height / 100.) * (Height / 100.)) : DEFAULT_VALUE);
    pSessionTable->FieldByName(MPW_BMI)->AsFloat = Bmi;

    if (pSessionTable->FindField(MPWM_TREND_SAMPLE_PERIOD) != NULL)
      pSessionTable->FieldByName(MPWM_TREND_SAMPLE_PERIOD)->AsFloat = TrendSamplePeriod;

    if (pSessionTable->FindField(MPW_SIMULATION)!=NULL)
    {
       pSessionTable->FieldByName(MPW_SIMULATION)->AsInteger = Simulation;
    }

    pSessionTable->Post();
  }
  catch (Exception &e)
  {
    Application->ShowException(&e);
    MsgBox("Error creating session", SERROR, MB_ICONSTOP);
    pSessionTable->Cancel();
    //Abort();
    pSessionTable->Close();
    return false;
  }
  // Success
  pSessionTable->Close();
  return (Session_ID > 0);
}

/* ###########################################################################
 ** CloseSession()
 **
 ** DESCRIPTION
 **  Set SessionFinish time in PWMSession table
 ** INPUT
 **  pSessionTable - Table
 ** OUTPUT
 **  None
 ** RETURN
 **  Nof parameters successfully stored in PWMTrend table
*/
//------------------------------------------------------------
bool TPWM::CloseSession(TADOTable *pSessionTable)
{
  // Validation DataSet
  if (pSessionTable==NULL)
  {
    MsgBox("Session table not defined", SERROR, MB_ICONSTOP);
    return false;
  }
  try
  {
    pSessionTable->Open();

    // Try to locate record with SystemID, SessionID...
    TLocateOptions SearchOptions;
    SearchOptions.Clear();
    SearchOptions << loPartialKey;

    //Try to find the record with current SessionID
    Variant lLocateValues[4];
    lLocateValues[0] = System_ID;
    lLocateValues[1] = Study_ID;
    lLocateValues[2] = Patient_No;
    lLocateValues[3] = Session_ID;

    String lKeyFields = MPW_SYSTEM_ID + ";" + MPW_STUDY_ID + ";" + MPW_PATIENT_NO
                        + ";" + MPWM_SESSION_ID;

    bool found = pSessionTable->Locate(lKeyFields, VarArrayOf(lLocateValues, 3),SearchOptions);
    if (!found)
    {
      MsgBox("Unable to locate database record for closing session "
              + IntToStr(Session_ID), SERROR, MB_ICONSTOP);
      pSessionTable->Close();
      return false;
    }
    pSessionTable->Edit();
    // This is a fix to limit the precision of the DateTime field and allow equality tests, eg. Locate
    pSessionTable->FieldByName(MPWM_SESSION_FINISHED)->AsDateTime = StrToDateTime(DateTimeToStr(Now()));
    pSessionTable->FieldByName(MPWM_SESSION_EVENT_COMMENT)->AsString = event_comment->CommaText;
    pSessionTable->Post();
  }
  catch (Exception &e)
  {
    MsgBox("Error creating session " + IntToStr(Session_ID) + " with exception:\r\n" + e.Message,
           SERROR, MB_ICONSTOP);
    pSessionTable->Cancel();
    //Abort();
    pSessionTable->Close();
    return false;
  }
  // Success
  pSessionTable->Close();
  return true;
}
/* ###########################################################################
 ** DeleteSession()
 **
 ** DESCRIPTION
 **  Delete session
 ** INPUT
 **  pSessionTable - Table
 ** OUTPUT
 **  None
 ** RETURN
 **  Nof parameters successfully stored in PWMTrend table
*/
//------------------------------------------------------------
bool TPWM::DeleteSession(TADOTable *pSessionTable, bool pOnlyIncomplete)
{
  // Validation DataSet
  if (pSessionTable==NULL)
  {
    MsgBox("Session table not defined", SERROR, MB_ICONSTOP);
    return false;
  }
  try
  {
    pSessionTable->Open();

    // Try to locate record with SystemID, SessionID...
    TLocateOptions SearchOptions;
    SearchOptions.Clear();
    SearchOptions << loPartialKey;

    //Try to find the record with current SessionID
    Variant lLocateValues[4];
    lLocateValues[0] = System_ID;
    lLocateValues[1] = Study_ID;
    lLocateValues[2] = Patient_No;
    lLocateValues[3] = Session_ID;

    String lKeyFields = MPW_SYSTEM_ID + ";" + MPW_STUDY_ID + ";" + MPW_PATIENT_NO
                        + ";" + MPWM_SESSION_ID;

    bool found = pSessionTable->Locate(lKeyFields, VarArrayOf(lLocateValues, 3),SearchOptions);
    if (!found)
    {
       if (Session_ID != 0)
       {
          MsgBox("Unable to locate database record for deleting session "
                 + IntToStr(Session_ID), SERROR, MB_ICONSTOP);
       }
       pSessionTable->Close();
      return true;
    }
    if (pOnlyIncomplete)
    {
      if (pSessionTable->FieldByName(MPWM_SESSION_FINISHED)->AsDateTime <=
          pSessionTable->FieldByName(MPWM_SESSION_START)->AsDateTime)
      {
        pSessionTable->Delete();
      }
    }
    else
    {
      pSessionTable->Delete();
    }
  }
  catch (Exception &e)
  {
    MsgBox("Error deleting session " + IntToStr(Session_ID) + " with exception:\r\n" + e.Message,
           SERROR, MB_ICONSTOP);
    pSessionTable->Cancel();
    //Abort();
    pSessionTable->Close();
    return false;
  }
  // Success
  pSessionTable->Close();
  Initialise();
  return true;
}

/* ###########################################################################
 ** CreateTrendSeries()
 **
 ** DESCRIPTION
 **  Create Trend Series for specific parameter
 ** INPUT
 **  pTrendTable - Table
 **  pSeries - Series to be created
 **  pParamIndex - index of a parameter
 ** OUTPUT
 **  None
 ** RETURN
 **  success or not
*/
//------------------------------------------------------------
bool TPWM::CreateTrendSeries(TDataSet *pTrendTable, TChartSeries *pSeries)
{
  String        error_string;
  String        lStream;
  short int     *Buffer;
  bool          found;
  bool          blob_failed;
  String pParamName = pSeries->Title.Trim();
  int pParamIndex = FParamList->IndexOf(pParamName);

  blob_failed = false;
  if (pParamIndex < 0)
  {
    MsgBox("No matches for series <" + pParamName + ">", SERROR, MB_ICONSTOP);
    return false;
  }
  // Validation DataSet
  if (pTrendTable == NULL)
  {
    MsgBox("PWM Trend table not defined", SERROR, MB_ICONSTOP);
    return false;
  }

  if (pTrendTable->Active == false)
  {
    MsgBox("Error opening PWM Trend DataSet", SERROR, MB_ICONSTOP);
    return false;
  }
  // Validation
  if (Session_ID <= 0 )
  {
    MsgBox("Session has not been created", SERROR, MB_ICONSTOP);
    return false;
  }
  if (System_ID == "" || Patient_No <= 0 || Study_ID == "")
  {
    MsgBox("Invalid SystemID, PatientNo or StudyID", SERROR, MB_ICONSTOP);
    return false;
  }

  // Try to locate record with SystemID, SessionID...
  TLocateOptions SearchOptions;
  SearchOptions.Clear();
  SearchOptions << loPartialKey;

 	//Try to find the record
  Variant lLocateValues[5];
  lLocateValues[0] = System_ID;
  lLocateValues[1] = Study_ID;
  lLocateValues[2] = Patient_No;
  lLocateValues[3] = Session_ID;
  lLocateValues[4] = pParamName;

  String lKeyFields = MPW_SYSTEM_ID + ";" + MPW_STUDY_ID + ";" + MPW_PATIENT_NO
                      + ";" + MPWM_SESSION_ID + ";" + MPWM_PARAM_NAME;


  try
  {
    found = pTrendTable->Locate(lKeyFields, VarArrayOf(lLocateValues, 4),SearchOptions);
  }
  catch (Exception &e)
  {
    found = false;
  }
  if (!found)
  {
    return false;
  }

  try
  {
    lStream = pTrendTable->FieldByName(MPWM_PARAM_TREND)->AsString;
    if (lStream.Length() <= 0)
    {
      MsgBox("No parameters to create Trend series <"
             + pParamName + ">", SERROR, MB_ICONSTOP);
      return false;
    }
    // Read blob stream and fill Series
    int points = lStream.Length()/sizeof(short int);
    Buffer = new short int[points];
    UnpackFromString(Buffer, lStream, lStream.Length());
    pSeries->Clear();
    for ( int l = 0; l < points; l++)
    {
      if (Buffer[l]!=(short int)DEFAULT_VALUE)
      {
        pSeries->AddXY((l+1)*TrendSamplePeriod/60., Buffer[l],"",pSeries->SeriesColor);
      }
      else
      {
        if (pParamName != "Event Marker")
        {
           pSeries->AddNullXY((l+1)*TrendSamplePeriod/60., 0. ,"");
        }

      }
    }
  }
  catch (Exception &e)
  {
    error_string = "Trend failed for " +pParamName +" " +GetCurrentPwmMeasureDetails() +e.Message;
    log_write(error_string);
    blob_failed = true;
    lStream = NULL;
  }
  // Success
  delete Buffer;
  if (blob_failed)
  {
     ;
  }
  else
  {
     lStream = NULL;
  }
  return (pSeries->Count()>0);
}

/* ###########################################################################
 ** ExportParam()
 **
 ** DESCRIPTION
 **  Create string of a parameter Trend
 ** INPUT
 **  pTrendTable - Table
 ** OUTPUT
 **  pOut - Output String
 ** RETURN
 **  success or not
*/
//------------------------------------------------------------
bool TPWM::ExportParam(TDataSet *pTrendTable, String &pOut)
{
  // Validation

  String lStream = NULL;
  short int *Buffer;
  int lCount = 0;
  try
  {
    String lParamName = pTrendTable->FieldByName(MPWM_PARAM_NAME)->DisplayText;
    pOut = lParamName;

    lStream = pTrendTable->FieldByName(MPWM_PARAM_TREND)->AsString;
    if (lStream.Length() <= 0)
    {
      return false;
    }
    int points = lStream.Length()/sizeof(short int);
    Buffer = new short int[points];
    UnpackFromString(Buffer, lStream, lStream.Length());
    for ( int l = 0; l < points; l++)
    {
      pOut = pOut + "\t" + IntToStr(Buffer[l]);
      lCount++;
    }
  }
  catch (Exception &e)
  {
    lCount = 0;
  }
  // Success
  delete Buffer;
  lStream = NULL;
  return (lCount > 0);
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
bool TPWM::Store(TDataSet* pDataSet, bool pRewriteKeyFields, bool pRewriteDate)
{
  pDataSet->FieldByName(MPWM_SESSION_ID)->AsInteger = Session_ID;
  bool ret = TPWA::Store(pDataSet, pRewriteKeyFields, pRewriteDate);
  return ret;
}

/* ###########################################################################
 ** Calculate ()
 **
 ** DESCRIPTION
 **  Calculate report for this moment of monitoring
 ** INPUT
 **  TPWM class (source)
 ** OUTPUT
 **  boolean success or not
*/
//---------------------------------------------------------------------------
bool TPWM::Calculate(bool append)
{
  bool ret;

  // Append the end of the last capture screen to the beginning of the signal, then calculate
  if (append)
  {
    Periph.Append(&periph_buffer[0],periph_buff_len);
  }

  if (Calibrated && Continuous)
  {
    ValidateSpDp = false;
    ret = TPWA::Calculate(1.0);//CalibrationRatio);
  }
  else if (!Calibrated && Continuous)
  {
    ValidateSpDp = true;
    ret = TPWA::Calculate();
  }
  else
  {
    ret = false;
  }
  if (append)
  {
    if(ret)
    {
      // Store the end of the signal from the second last trigger point
      int indP = 0;
      int start = (int)(Periph.Onsets[Periph.NofOnsets-2]);
      int finish = Periph.NofPoints;
      if(finish - start < PRESSURE_PULSE_MAXLENGTH)
      {
         for (int i = start; i < finish; i++)
         {
            periph_buffer[indP] = Periph.Signal[i];
            indP++;
         }
         periph_buff_len = indP;
      }
      else
      {
         periph_buff_len = 0;
      }
    }
    else
    {
      periph_buff_len = 0;
    }
  }
  return ret;
}

/* ###########################################################################
 ** FindCalibrationFactor()
 **
 ** DESCRIPTION
 **  Get Calibration Factor from Device table
 ** INPUT
 **  pDeviceTable - Table
 ** OUTPUT
 **  None
 ** RETURN
 **  Success or not
*/
//------------------------------------------------------------
bool TPWM::FindCalibrationFactor(TADOTable *pDeviceTable)
{
  // Validation DataSet
  if (pDeviceTable==NULL)
  {
    MsgBox("Undefined Device table", SERROR, MB_ICONSTOP);
    return false;
  }
  if (DeviceID <= 0)
  {
    MsgBox("Undefined DeviceID", SERROR, MB_ICONSTOP);
    return false;
  }
  try
  {
    pDeviceTable->Open();

    // Try to locate record with DeviceID...
    TLocateOptions SearchOptions;
    SearchOptions.Clear();
    SearchOptions << loPartialKey;

    //Try to find the record with current SessionID
/*
    Variant lLocateValues[1];
    lLocateValues[0] = DeviceID;

    String lKeyFields = MPWM_SESSION_DEVICE_ID;
*/
    //  bool found = pDeviceTable->Locate(lKeyFields, VarArrayOf(lLocateValues, 1),SearchOptions);
    bool found = pDeviceTable->Locate(MPWM_SESSION_DEVICE_ID, DeviceID,SearchOptions);
    if (!found)
    {
      MsgBox("Unable to locate database record for device "
              + IntToStr(DeviceID), SERROR, MB_ICONSTOP);
      pDeviceTable->Close();
      return false;
    }
    CalibrationRatio = pDeviceTable->FieldByName(MPWM_DEVICE_CALIBRATION_RATIO)->AsFloat;
    CalibrationOffset = pDeviceTable->FieldByName(MPWM_DEVICE_CALIBRATION_OFFSET)->AsFloat;
  }
  catch (Exception &e)
  {
    MsgBox("Error finding calibration factor for device " + IntToStr(DeviceID) + " with exception:\r\n" + e.Message,
           SERROR, MB_ICONSTOP);
    pDeviceTable->Cancel();
    //Abort();
    pDeviceTable->Close();
    return false;
  }
  // Success
  pDeviceTable->Close();
  return (CalibrationRatio > 0.);
}

bool  TPWM::UpdateEventComments(TDataSet *dataset_session)
{
   bool updated = false;
   TStringList *tmp_comment_list = NULL;

   try
   {
      tmp_comment_list =  new TStringList();
      if (tmp_comment_list != NULL)
      {
         tmp_comment_list->Assign(event_comment);
         dataset_session->Edit();
         dataset_session->FieldByName(MPWM_SESSION_EVENT_COMMENT)->AsString = tmp_comment_list->CommaText;
         dataset_session->Post();
         updated = true;
      }
   }
   catch (Exception &e)
   {
      MsgBox("Error updating Session " + IntToStr(Session_ID) + " with exception:\r\n" + e.Message,
              SERROR, MB_ICONSTOP);

   }
   if (tmp_comment_list != NULL)
   {
      delete tmp_comment_list;
   }
   return (updated);
}

int TPWM::GetMarkerIndicator(AnsiString marker_string)
{
   int         marker_value = -1;
   AnsiString  num_str = "";

   if (marker_string.Length() >= 2)
   {
      marker_value = marker_string.AnsiPos("-");
      if (marker_value == 0)
      {
         marker_value = -1;
      }
      else
      {
         num_str = marker_string.SubString(1, marker_value - 1);
         if (num_str.Length())
         {
            marker_value = StrToInt(num_str);
         }
      }
   }
   return (marker_value);
}

AnsiString TPWM::GetMarkerString(AnsiString marker_string)
{
   int         marker_value = -1;
   AnsiString  event_str = "";

   if (marker_string.Length() >= 2)
   {
      marker_value = marker_string.AnsiPos("-");
      if (marker_value == 0)
      {
         marker_value = -1;
      }
      else
      {
         event_str = marker_string.SubString(marker_value + 1, marker_string.Length());
      }
   }
   return (event_str);
}

bool TPWM::ValidateHtWt()
{
   // Must overide the function because ValidateHtWt is protected
   return TMeasure::ValidateHtWt();
}
