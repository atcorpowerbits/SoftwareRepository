//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include <msg\pubserv.h>
#include <log\pubserv.h>
#include <meas/pubserv.h>
#include <Mathem.h>
#include "TSignal.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
const double PI = 3.14159265358979;
// Get string with measurement details
extern String GetCurrentMeasureDetails();
//---------------------------------------------------------------------------
// Constructor and Destructor for TSignal Class
//---------------------------------------------------------------------------
TSignal::TSignal(const int pMaxNofPoints, const int pMaxNofOnsets)
{
  NofPoints = 0;
  NofOnsets = 0;
  MaxNofPoints = 0;
  MaxNofOnsets = 0;
  Signal = NULL;
  Onsets = NULL;
  TrigPts = NULL;
  FloatOnsets = NULL;

  ReadyToCapture = false;
  CurrentIndex = -1;

  QC_PulseHeight = DEFAULT_VALUE;
  QC_PulseHeightVariation = DEFAULT_VALUE;
  QC_PulseLengthVariation = DEFAULT_VALUE;
  QC_BaseLineVariation = DEFAULT_VALUE;
  // Allocate memory
  if (pMaxNofPoints > 0 && pMaxNofOnsets > 0)
    Allocate(pMaxNofPoints, pMaxNofOnsets);
}
//---------------------------------------------------------------------------
void TSignal::Allocate(const int pMaxNofPoints, const int pMaxNofOnsets)
{
  MaxNofPoints = pMaxNofPoints;
  MaxNofOnsets = pMaxNofOnsets;

  // Allocate
  Signal = new float[MaxNofPoints];
  FloatOnsets = new float[pMaxNofOnsets];
  Onsets = (short int*) FloatOnsets;


  // Link other names
  TrigPts = Onsets;
  // Initialise
  Initialise(0);
}
//---------------------------------------------------------------------------
// Class initialisator
//---------------------------------------------------------------------------
void TSignal::Initialise(const int pSampleRate)
{
  // Sizes = 0
  NofPoints = 0;
  SampleRate = (short int) pSampleRate;
  // Signal initialisation
  for (int i = 0; i < MaxNofPoints; i++)
  {
    Signal[i] = 0;
  }
  // Onsets initialisation
  SetDefaults(pSampleRate);
}
//---------------------------------------------------------------------------
// Set default values for onsets not touching Signal
//---------------------------------------------------------------------------
void TSignal::SetDefaults(const int pSampleRate)
{
  // Initialisation
  ReadyToCapture = false;
  QC_PulseHeightVariation = DEFAULT_VALUE;
  QC_PulseLengthVariation = DEFAULT_VALUE;
  QC_PulseHeight = DEFAULT_VALUE;
  QC_BaseLineVariation = DEFAULT_VALUE;
  // Onsets initialisation
  NofOnsets = 0;
  for (int i = 0; i < MaxNofOnsets; i++)
  {
    Onsets[i] = -1; FloatOnsets[i] = -1;
  }
}

//---------------------------------------------------------------------------
TSignal::~TSignal()
{
  delete [] Signal;
  delete [] FloatOnsets;
}

/* ###########################################################################
 ** Populate()
 **
 ** DESCRIPTION
 **  populate class properties from current record in pDataSet
 ** INPUT
 **  pDataSet - TADOQuery or TADOTable
 ** OUTPUT
 ** RETURN
 **  boolean success or not
*/
//----------------------------------------------------------------------------------
bool TSignal::Populate(TDataSet* pDataSet, const String pSignalField,
                       const String pOnsetsField, const String pFloatOnsetsField)
{
  // SetDefaults();
  if (pDataSet->RecordCount <= 0)
    return false;
  try
  {
    // PickUp Arrays
    int NofBytes;

    // Extract Signal
    NofBytes = min((int)(pDataSet->FieldByName(pSignalField)->AsString.Length()),
                   (int)(MaxNofPoints*sizeof(short int)));
    if (UnpackFromString(Signal, pDataSet->FieldByName(pSignalField)->AsString, NofBytes, 1)==false)
      return false;
    NofPoints = NofBytes/sizeof(short int);

    // Extract Integer Onsets
    if (pFloatOnsetsField == "")
    {
      NofBytes = min((int)(pDataSet->FieldByName(pOnsetsField)->AsString.Length()),
                     (int)(MaxNofOnsets*sizeof(short int)));
      if (UnpackFromString(Onsets, pDataSet->FieldByName(pOnsetsField)->AsString, NofBytes)==false)
        return false;
      NofOnsets = NofBytes/sizeof(short int);
    }
    else // Extract Float Onsets
    {
      NofBytes = min((int)(pDataSet->FieldByName(pFloatOnsetsField)->AsString.Length()),
                     (int)(MaxNofOnsets*sizeof(float)));
      if (UnpackFloatFromString(FloatOnsets, pDataSet->FieldByName(pFloatOnsetsField)->AsString, NofBytes)==false)
        return false;
      NofOnsets = NofBytes/sizeof(float);
    }
  }
  catch (Exception &exception)
  {
    MsgBox(TERROR, GetCurrentMeasureDetails(), MSG_DBREADWRITE_ERROR, MSG_ERR_READDB,
           LoadStr(MSG_ERR_READDB) +exception.Message);
    return false;
  }
  return true;
}


/* ###########################################################################
 ** GetFloatOnsetsFromArray
 **
 ** DESCRIPTION
 **  Get trigger points from populated TrigPts array and calculate their number
 ** INPUT
 **  TPWVSignal class (source)
 ** OUTPUT
 **  TPWVSignal class properties
 ** RETURN
 **  boolean success or not
*/
//---------------------------------------------------------------------------
bool TSignal::GetFloatOnsetsFromArray(const int pLength, const int pFactor)
{
  NofOnsets = 0;
  // Find last positive value (because for Dbase DB negatives are valid)
  for (int i=pLength-1; i>=0; i--)
  {
    if (FloatOnsets[i] > 0.)
    {
      NofOnsets = i + 1;
      break;
    }
  }
  // Multiply by Sample Rate when extracted from PWV Dbase
  if (pFactor != 1 && pFactor != 0 && NofOnsets > 0)
  {
    for (int i=0; i < NofOnsets; i++)
    {
      if (FloatOnsets[i] > 0)
        FloatOnsets[i] *= pFactor;
    }
  }
  // Validated later
  return true;
}

/* ###########################################################################
 ** Store()
 **
 ** DESCRIPTION
 **  Store TSignal class properties to pDataSet
 ** INPUT
 **  pDataSet - TADOQuery or TADOTable
 ** OUTPUT
 **  boolean success or not
*/
//--------------------------------------------------------------------------------
bool TSignal::Store (TDataSet* pDataSet, const String pSignalField,
                     const String pOnsetsField, const String pFloatOnsetsField)
{
  try
  {
    // Store Signal
    pDataSet->FieldByName(pSignalField)->Value =
      PackToString(Signal, NofPoints, 1);
    if (pFloatOnsetsField=="") // Store Integer Onsets
    {
      pDataSet->FieldByName(pOnsetsField)->Value =
        PackToString(Onsets, NofOnsets);
    }
    else  // Store Float Onsets
    {
      pDataSet->FieldByName(pFloatOnsetsField)->Value =
        PackFloatToString(FloatOnsets, NofOnsets);
    }
  }
  catch (Exception &exception)
  {
    MsgBox(TERROR, GetCurrentMeasureDetails(), MSG_DBREADWRITE_ERROR, MSG_ERR_READDB,
           LoadStr(MSG_ERR_READDB) +exception.Message);
    return false;
  }

  return true;
}

/* ###########################################################################
 ** ValidateBeforeStore()
 **
 ** DESCRIPTION
 **  Validate class properties before storing in database
 ** INPUT
 ** OUTPUT
 ** RETURN
 **  boolean success or not
*/
//---------------------------------------------------------------------------
bool TSignal::ValidateBeforeStore(const int pMinNofPoints, const int pMinNofOnsets, const int pMinHeight)
{
  // Signal
  if (ValidateSignalLength(pMinNofPoints)==false)
    return false;
  if (ValidateSignalHeight(pMinHeight)==false)
    return false;
  // Onsets
  bool ret = true;
  if (NofOnsets < pMinNofOnsets)
  {
    MsgBox(TERROR, GetCurrentMeasureDetails(), MSG_VALIDATION_ERROR, MSG_NOT_ENOUGH_ONSETS,
           LoadStr(MSG_NOT_ENOUGH_ONSETS) + IntToStr(NofOnsets) + ", " + IntToStr(pMinNofOnsets));
    ret = false;
  }
  if (NofOnsets > MaxNofOnsets)
  {
    MsgBox_show(TWARNING,
                MSG_VALIDATION_ERROR,
                LoadStr(MSG_TOO_MUCH_ONSETS) + IntToStr(NofOnsets) + ", " + IntToStr(MaxNofOnsets),
                MSG_TOO_MUCH_ONSETS, "");
    NofOnsets = MaxNofOnsets;
  }
  return ret;
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
//---------------------------------------------------------------------------
bool TSignal::CaptureSignal(const short int *pInput, const int pLength)
{
  if (ReadyToCapture == false || pLength < 1)
    return false;
  NofPoints = min(pLength, (int)MaxNofPoints);
  for (int i = 0; i < NofPoints; i++)
  {
   Signal[i] = pInput[i];
  }
  return NofPoints > 1;
}

/* ###########################################################################
 ** CaptureSignalPacket()
 **
 ** DESCRIPTION
 **  Store signal packet from tonometer in Signal array
 ** INPUT
 **  short int * input  - integer signal
 **  int pLength - packet length
 ** OUTPUT
 ** RETURN
 **  none
*/
//---------------------------------------------------------------------------
bool TSignal::CaptureSignalPacket(const short int *pInput, const int pLength)
{
  if (ReadyToCapture == false || NofPoints + pLength > MaxNofPoints)
    return false;
  for (int i = 0; i < pLength; i++)
  {
    Signal[NofPoints + i] = pInput[i];
  }
  NofPoints += pLength;
  return NofPoints > 1;
}

/* ###########################################################################
 ** CaptureSignal()
 **
 ** DESCRIPTION
 **  Store whole signal from tonometer in Signal array
 ** INPUT
 **  float * input  - input signal
 **  int pLength
 ** OUTPUT
 ** RETURN
 **  none
*/
//---------------------------------------------------------------------------
bool TSignal::CaptureSignal(const float *pInput, const int pLength)
{
  if (ReadyToCapture == false || pLength < 1)
    return false;
  NofPoints = min(pLength, (int)MaxNofPoints);
  for (int i = 0; i < NofPoints; i++)
  {
   Signal[i] = pInput[i];
  }
  return NofPoints > 1;
}

/* ###########################################################################
 ** CaptureSignalPacket()
 **
 ** DESCRIPTION
 **  Store signal packet from tonometer in Signal array
 ** INPUT
 **  float * input  - input signal
 **  int pLength - packet length
 ** OUTPUT
 ** RETURN
 **  none
*/
//---------------------------------------------------------------------------
bool TSignal::CaptureSignalPacket(const float *pInput, const int pLength)
{
  if (ReadyToCapture == false || NofPoints + pLength > MaxNofPoints)
    return false;
  for (int i = 0; i < pLength; i++)
  {
    Signal[NofPoints + i] = pInput[i];
  }
  NofPoints += pLength;
  return NofPoints > 1;
}

/* ###########################################################################
 ** ReadFromFile()
 **
 ** DESCRIPTION
 **  Read Signal array from file
 ** INPUT
 **  pFileName - file name
 **  pColumn - column number in file with Signal
 ** OUTPUT
 **   None
 ** RETURN
 **   boolean success or not
*/
//---------------------------------------------------------------------------
bool TSignal::ReadFromFile(const String pFileName, const int pColumn,
                           const int pNofColumns)
{
  if (pColumn <= 0 || pColumn > pNofColumns)
    return false;

  if (FileExists(pFileName)==false)
  {
    MsgBox(LoadStr(MSG_COMMS_NO_FILE) + pFileName + "\n\n" +
           LoadStr(MSG_COMMS_CHECK_FILENAME), SWARNING, MB_ICONSTOP);
    //ReadyToCapture = false;
    return false;
  }

  // Open file for read
  FILE *stream;
  stream = fopen(pFileName.c_str(), "r");
  if (stream==NULL)
  {
    MsgBox(LoadStr(MSG_COMMS_NO_FILE) + pFileName + "\n\n" +
           LoadStr(MSG_COMMS_CHECK_FILENAME), SWARNING, MB_ICONSTOP);
    //ReadyToCapture = false;
    return false;
  }

  /* read numbers from the file */
  NofPoints = 0;
  float f[2];
  bool lEof = true;
  while ((lEof == true) && (NofPoints < MaxNofPoints))
  {
    if (pNofColumns == 1)
    {
      lEof = fscanf(stream, "%f",&f[0])!=EOF;
      if (lEof == true) Signal[NofPoints] = f[0];
    }
    else if (pNofColumns == 2)
    {
      lEof = fscanf(stream, "%f %f",&f[0], &f[1])!=EOF;
      if (lEof == true) Signal[NofPoints] = f[pColumn-1];
    }
    if (lEof == true)
      NofPoints++;
  }
  fclose(stream);

  CurrentIndex = 0;
  return (NofPoints > 1);
}

/* ###########################################################################
 ** SaveToFile()
 **
 ** DESCRIPTION
 **  Save Signal to file
 ** INPUT
 **  pFileName - file name
 ** OUTPUT
 **   None
 ** RETURN
 **   boolean success or not
*/
//---------------------------------------------------------------------------
bool TSignal::SaveToFile(const String pFileName)
{
  int lFileHandle = FileCreate(pFileName);
  // Validation
  if (lFileHandle <= 0)
  {
     MsgBox(LoadStr(MSG_COMMS_NO_FILE) + pFileName + "\n\n" +
          LoadStr(MSG_COMMS_CHECK_FILENAME), SWARNING, MB_ICONSTOP);
     return false;
  }
  // Printing arrays
  for (int i=0; i<NofPoints; i++)
  {
    String lOut = FormatFloat("####0.0##", Signal[i]) + "\r\n";;
    FileWrite(lFileHandle, lOut.c_str(), lOut.Length());
  }
  FileClose(lFileHandle);
  return true;
}

/* ###########################################################################
 ** GetSignalValue()
 **
 ** DESCRIPTION
 **  Getting current value of a signal
 ** INPUT
 **  None
 ** OUTPUT
 **  pValue - current value as integer
 ** RETURN
 **   boolean success or not. If end of Signal, return false
*/
//---------------------------------------------------------------------------
bool TSignal::GetNextValue(short int &pValue)
{
  if (CurrentIndex > NofPoints - 1 || CurrentIndex < 0)
  {
    ResetIndex();
    return false;
  }
  pValue = (short int) math_Round(Signal[CurrentIndex]);
  CurrentIndex++;
  return true;
}
/* ###########################################################################
 ** ResetIndex()
 **
 ** DESCRIPTION
 **  Setting CurrentIndex to -1
 ** INPUT
 **  None
 ** OUTPUT
 **  None
 ** RETURN
 **   None
*/
//---------------------------------------------------------------------------
void TSignal::ResetIndex()
{
  CurrentIndex = -1;
}

/* ###########################################################################
 ** ValidateSignalLength()
 **
 ** DESCRIPTION
 **  Validate Signal length
 ** INPUT
 **  pMinNofPoints - minimal signal length
 ** OUTPUT
 **   None
 ** RETURN
 **  boolean appropriate signal or not
*/
//---------------------------------------------------------------------------
bool TSignal::ValidateSignalLength(const int pMinNofPoints)
{
  bool ret = true;
  if (NofPoints < pMinNofPoints)
  {
    MsgBox(TERROR, GetCurrentMeasureDetails(), MSG_VALIDATION_ERROR, MSG_SIGNAL_TOO_SHORT,
           LoadStr(MSG_SIGNAL_TOO_SHORT) + IntToStr(NofPoints));
    ret = false;
  }
  // Sample rate
  if (SampleRate <=0)
  {
    MsgBox(TERROR, GetCurrentMeasureDetails(), MSG_VALIDATION_ERROR, MSG_INVALID_SAMPLERATE);
    ret = false;
  }
  if (NofPoints > MaxNofPoints)
  {
    MsgBox(TERROR, GetCurrentMeasureDetails(), MSG_VALIDATION_ERROR, MSG_SIGNAL_TOO_LONG);
    NofPoints = MaxNofPoints;
  }
  return ret;
}

/* ###########################################################################
 ** ValidateSignalHeight()
 **
 ** DESCRIPTION
 **  Validate Signal amplitude
 ** INPUT
 **  pMinHeight - minimal signal amplitude
 ** OUTPUT
 **   None
 ** RETURN
 **  boolean appropriate signal or not
*/
//---------------------------------------------------------------------------
bool TSignal::ValidateSignalHeight(const int pMinHeight)
{
  float lMin, lMax;
  float lHeight = 0.;
  bool ret = math_MinMaxInArray(Signal, NofPoints, lMin, lMax);
  if (ret == true)
  {
    lHeight = lMax - lMin;
    if (lHeight < pMinHeight)
      ret = false;
  }
  if (ret == false)
  {
    MsgBox(TERROR, GetCurrentMeasureDetails(), MSG_VALIDATION_ERROR, MSG_SIGNAL_TOO_SMALL,
           LoadStr(MSG_SIGNAL_TOO_SMALL) + RoundIntToStr(lHeight));
    ret = false;
  }
  return ret;
}

/* ###########################################################################
 ** QualityControl()
 **
 ** DESCRIPTION
 **  Calculate Quality Control parameters for a Signal
 ** INPUT
 **  TSignal class properties
 ** OUTPUT
 **  Quality Controls properties
 ** RETURN
 **  boolean success or not
*/
//---------------------------------------------------------------------------
bool TSignal::QualityControls()
{
  // Initialisation
  QC_PulseHeightVariation = DEFAULT_VALUE;
  QC_PulseLengthVariation = DEFAULT_VALUE;
  QC_PulseHeight = DEFAULT_VALUE;
  QC_BaseLineVariation = DEFAULT_VALUE;

  if (NofOnsets <= 1)
  {
     return false;
  }

  // Average of all pulse Heights, Lengths, BaseLines
  float lAvPH = 0.;
  float lAvPulseLength = 0.;
  float lAvBase = 0.;
  for (int np = 0; np < NofOnsets-1; np++)
  {
    float on1 = fabs(FloatOnsets[np]);
    float on2 = fabs(FloatOnsets[np+1]);
    // Calculate pulse height
    float lMin, lMax;
    math_MinMaxInArray(&Signal[(int)on1], (int)on2 - (int)on1, lMin, lMax);
    float lHeight = lMax - lMin;
    lAvPH += lHeight;
    float lPulseLength = on2 - on1;
    lAvPulseLength += lPulseLength;
    float lBase = math_FunctionValue(Signal, NofPoints, on1);
    lAvBase += lBase;
  }
  lAvPH /= (NofOnsets - 1);
  lAvPulseLength /= (NofOnsets - 1);
  lAvBase /= (NofOnsets - 1);

  QC_PulseHeight = (lAvPH > 0 ? lAvPH : DEFAULT_VALUE);
  if (QC_PulseHeight == DEFAULT_VALUE)
    return false;

  // Variations
  float lPHV = 0.;
  float lPLV = 0.;
  float lBLV = 0.;
  for (int np = 0; np < NofOnsets-1; np++)
  {
    float on1 = fabs(FloatOnsets[np]);
    float on2 = fabs(FloatOnsets[np+1]);
    // Calculate pulse height
    float lMin, lMax;
    math_MinMaxInArray(&Signal[(int)on1], (int)on2 - (int)on1, lMin, lMax);
    float lHeight = lMax - lMin;
    lPHV += fabs(lHeight - lAvPH);
    float lPulseLength = on2 - on1;
    lPLV += fabs(lPulseLength - lAvPulseLength);
    float lBase = math_FunctionValue(Signal, NofPoints, on1);
    lBLV += pow(lBase - lAvBase, 2);
  }
  lPHV /= (NofOnsets - 1);
  QC_PulseHeightVariation = (lPHV >= 0 ? lPHV/lAvPH * 100 : DEFAULT_VALUE);
  lPLV /= (NofOnsets - 1);
  QC_PulseLengthVariation = (lPLV >= 0 ? lPLV/lAvPulseLength * 100 : DEFAULT_VALUE);
  lBLV = sqrt(lBLV/(NofOnsets - 1));
  lBLV = (lBLV / QC_PulseHeight) * 100;
  QC_BaseLineVariation = lBLV;
  return true;
}

/* ###########################################################################
 ** Generate()
 **
 ** DESCRIPTION
 **  Generate Signal array as a SIN Wave
 ** INPUT
 **  pHeartRate
 **  pAmplitude
 **  pBaseLine
 **  pTimePhase
 **  pSignalDuration
 ** OUTPUT
 **   None
 ** RETURN
 **   boolean success or not
*/
//---------------------------------------------------------------------------
bool TSignal::Generate(const int pHeartRate, const int pAmplitude,
                       const int pBaseLine, const int pTimePhase,
                       const int pSignalDuration)
{
  // Validation
  if (SampleRate <= 0)
  {
    MsgBox("Signal Sample rate undefined", SWARNING, MB_ICONSTOP);
    return false;
  }
  if (pHeartRate <= 0 || pAmplitude <= 0)
  {
    MsgBox("Wrong parameters to generate Signal", SWARNING, MB_ICONSTOP);
    return false;
  }
  int lNofPoints = math_TimeToIndex(pSignalDuration * 1000, SampleRate, 1);
  if (lNofPoints > MaxNofPoints)
  {
    MsgBox("Signal duration too big", SWARNING, MB_ICONSTOP);
    return false;
  }

  NofPoints = lNofPoints;

  float lPeriod = 60000./pHeartRate;
  // Generate sin-wave
  for (int i=0; i<NofPoints; i++)
  {
    float lTime = math_IndexToTime(i, SampleRate, 1);
    float ksi = 2*(lTime + pTimePhase)/lPeriod - 1;
    double f = pBaseLine + pAmplitude*cos(PI*ksi);
    Signal[i] = f;
  }

  CurrentIndex = 0;
  return (NofPoints > 1);
}

 /* ###########################################################################
 ** Append()
 **
 ** DESCRIPTION
 **  Append the Last Pulse to the signall array
 ** INPUT
 **  The last Pulse (pBuffer)
 **  The length of the last pulse (pbuffer_length)
 ** OUTPUT
 **   None
 ** RETURN
 **  void
*/
//---------------------------------------------------------------------------
 void TSignal::Append(float *pBuffer, int pBuffer_length)
{
   float *temp;
   int   i;

   temp = NULL;
   if (pBuffer_length!=0)
   {
      temp = new float [MaxNofPoints];
      if (temp == NULL)
      {
         return;
      }
      for (i = 0; i < NofPoints; i++)
      {
         temp[i] = Signal[i];
      }
      for (i = 0; i < NofPoints + pBuffer_length; i++)
      {
         if (i < pBuffer_length)
         {
            Signal[i] = pBuffer[i];
         }
         else
         {
            if (i < MaxNofPoints)
            {
               Signal[i] = temp[i - pBuffer_length];
            }

         }
      }
      if ((NofPoints + pBuffer_length) <  MaxNofPoints)
      {
         NofPoints = NofPoints + pBuffer_length;
      }
      else
      {
         NofPoints =  MaxNofPoints;
      }
      delete[] temp;
   }
}


