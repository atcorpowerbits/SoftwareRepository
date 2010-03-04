//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include <sdlbasepack_82C6.hpp>
#include <sdlmathpack_82C6.hpp>
#include <meas/pubserv.h>
#include <msg/pubserv.h>
#include <config/pubserv.h>
#include <patient/pubserv.h>
#include "Mathem.h"
#include "math.h"
#include "AVI.h"
//#include <iostream>
//---------------------------------------------------------------------------

#pragma package(smart_init)

const int AVI_MAX_FLOW = 100;
const int AVI_MAX_HARMONICS = 40;
const int AVI_MAX_CORRELATIONS = 40;
const float AVI_CAROTID_FEMORAL_SLOPE = 0.6182;
const float AVI_CAROTID_FEMORAL_INTERCEPT = -10.166;
using namespace std;
static TAVI avi;
TCurveFit     *AVICurveFit;

TAVI*  meas_get_current_avi (void)
{
  return &avi;
}

//---------------------------------------------------------------------------
TAVI::TAVI()
{
  // Allocate Signals
  Flow = new float[PRESSURE_PULSE_MAXLENGTH];
  Forward_Pressure = new float[PRESSURE_PULSE_MAXLENGTH];
  Backward_Pressure = new float[PRESSURE_PULSE_MAXLENGTH];
  Forward_Pressure_Refined = new float[PRESSURE_PULSE_MAXLENGTH];
  Backward_Pressure_Refined = new float[PRESSURE_PULSE_MAXLENGTH];
  Forward_Pressure_Final = new float[PRESSURE_PULSE_MAXLENGTH];
  Backward_Pressure_Final = new float[PRESSURE_PULSE_MAXLENGTH];

  Pressure_Spectrum = new float[MEAS_DEFAULT_SAMPLE_RATE];
  Flow_Spectrum = new float[MEAS_DEFAULT_SAMPLE_RATE];
  Frequency = new float[MEAS_DEFAULT_SAMPLE_RATE];

  Pressure_Harmonics = new float[AVI_MAX_HARMONICS+1];
  Flow_Harmonics = new float[AVI_MAX_HARMONICS+1];

  Cross_Correlation = new float[AVI_MAX_CORRELATIONS + 1];

  AVICurveFit = new TCurveFit(Application);

  Initialise();
}

//---------------------------------------------------------------------------
void TAVI::Initialise()
{
   //SmoothOrder = 3;

   SetDefaults();
}
//---------------------------------------------------------------------------
void TAVI::SetDefaults()
{
   // Variables initialisation
   MaxDpDt = DEFAULT_VALUE;
   Forward_Max = DEFAULT_VALUE;
   T1_index = DEFAULT_VALUE;
   ED_index = DEFAULT_VALUE;
   MaxDpDt_index = DEFAULT_VALUE;
   Forward_index = DEFAULT_VALUE;
   Forward_Max_index = DEFAULT_VALUE;
   SpectrumLength = DEFAULT_VALUE;
   Impedance = DEFAULT_VALUE;
   Forward_Vector_Max = DEFAULT_VALUE;
   Forward_Vector_Min = DEFAULT_VALUE;
   Backward_Vector_Max = DEFAULT_VALUE;
   Backward_Vector_Min = DEFAULT_VALUE;
   Forward_Pressure_Max = DEFAULT_VALUE;
   Forward_Pressure_Max_Time = DEFAULT_VALUE;
   Forward_Pressure_Max_Time_Index = DEFAULT_VALUE;
   Forward_Pressure_Height = DEFAULT_VALUE;
   Backward_Pressure_Max = DEFAULT_VALUE;
   Backward_Pressure_Max_Time = DEFAULT_VALUE;
   Backward_Pressure_Max_Time_Index = DEFAULT_VALUE;
   Backward_Pressure_Height = DEFAULT_VALUE;
   Reflection_Index = DEFAULT_VALUE;
   Aortic_Reflection_Lag = DEFAULT_VALUE;
   Aortic_Reflection_Time = DEFAULT_VALUE;
   Carotid_Femoral_Transmission_Time = DEFAULT_VALUE;
   Aortic_Distance = DEFAULT_VALUE;
   SphygmoCor_Velocity_Index = DEFAULT_VALUE;
   
   // Arrays initialisation
   for (int i = 0; i < PRESSURE_PULSE_MAXLENGTH; i++)
   {
      Forward_Pressure[i] = 0;
      Backward_Pressure[i] = 0;
      Forward_Pressure_Refined[i] = 0;
      Backward_Pressure_Refined[i] = 0;
      Forward_Pressure_Final[i] = 0;
      Backward_Pressure_Final[i] = 0;
      Flow[i] = DEFAULT_VALUE;
   }

   for (int i=0 ; i < MEAS_DEFAULT_SAMPLE_RATE; i++)
   {
      Pressure_Spectrum[i] = DEFAULT_VALUE;
      Flow_Spectrum[i] = DEFAULT_VALUE;
      Frequency[i] = DEFAULT_VALUE;
   }

   for (int i=0 ; i <= AVI_MAX_HARMONICS; i++)
   {
      Pressure_Harmonics[i] = DEFAULT_VALUE;
      Flow_Harmonics[i] = DEFAULT_VALUE;
   }

   for (int i=0 ; i <= AVI_MAX_CORRELATIONS; i++)
   {
      Cross_Correlation[i] = DEFAULT_VALUE;
   }
}
//---------------------------------------------------------------------------
TAVI::~TAVI()
{
  // Arrays cleanup
  if (Forward_Pressure != NULL)
  {
      delete Forward_Pressure;
  }
  if (Backward_Pressure != NULL)
  {
      delete Backward_Pressure;
  }
  if (Forward_Pressure_Refined != NULL)
  {
      delete Forward_Pressure_Refined;
  }
  if (Backward_Pressure_Refined != NULL)
  {
      delete Backward_Pressure_Refined;
  }
  if (Forward_Pressure_Final != NULL)
  {
      delete Forward_Pressure_Final;
  }
  if (Backward_Pressure_Final != NULL)
  {
      delete Backward_Pressure_Final;
  }
  if (Flow != NULL)
  {
      delete Flow;
  }
  if (Pressure_Spectrum != NULL)
  {
      delete Pressure_Spectrum;
  }
  if (Flow_Spectrum != NULL)
  {
      delete Flow_Spectrum;
  }
  if (Frequency != NULL)
  {
      delete Frequency;
  }
  if (Pressure_Harmonics != NULL)
  {
      delete Pressure_Harmonics;
  }
  if (Flow_Harmonics != NULL)
  {
      delete Flow_Harmonics;
  }
  if (Pressure_Plan != NULL)
  {
      fftwf_destroy_plan(Pressure_Plan);
  }
  if (Flow_Plan != NULL)
  {
      fftwf_destroy_plan(Flow_Plan);
  }
  if (Pressure_Output != NULL)
  {
      fftwf_free(Pressure_Output);
  }
  if (Flow_Output != NULL)
  {
      fftwf_free(Flow_Output);
  }
  if (Cross_Correlation != NULL)
  {
      delete Cross_Correlation;
  }
}                         

bool TAVI::Calculate(TPressureCentral *Central)
{
   MEAS_ID_TYPE  meas_mode;

   meas_mode = patient_get_study_mode();

    // Only calculate if AVI is enabled and in PWA mode
   if (!config_get_avi_option() || meas_mode != MEAS_PWA_ID)
   {
      return true;             
   }

   AVICentral = Central;
   if (!ValidateBeforeCalculate())
   {
      return false;
   }

   CalculateFlow(AVICentral->T1);
   if (!FourierTransform())
   {
      return false;
   }
   if (!Harmonics())
   {
      return false;
   }
   CalculateImpedance();
   CalculatePressureWaves();
   if (!Recalculate())
   {
      return false;
   }
   RecalculateFlow();
   CrossCorrelation();
   return true;
}

bool TAVI::Recalculate()
{
   float Backward_Pressure_Min;

   // Check if the waves need to recalculated
   Backward_Pressure_Min = math_MinInArray(Backward_Pressure_Final, AVICentral->CalAvPulse.Length());
   if (Backward_Pressure_Min < Backward_Pressure_Final[0] - 1)
   {
      T1_index = T1_index - 1;
      float T1 = AVICentral->CalAvPulse.IndexToTime(T1_index);
      if (T1 < 80.0)
      {
         return true;
      }

      CalculateFlow(T1);
      if (!FourierTransform())
      {
         return false;
      }
      if (!Harmonics())
      {
         return false;
      }
      CalculateImpedance();
      CalculatePressureWaves();
      if (!Recalculate())
      {
         return false;
      }
   }
   return true;
}

void TAVI::CalculateFlow(float T1)
{
   float gradient1;
   float gradient2;
   float y_intercept;
   int index = 0;

   T1_index = AVICentral->CalAvPulse.TimeToIndex(T1);
   ED_index = AVICentral->CalAvPulse.TimeToIndex(AVICentral->ED);
   gradient1 = (float)AVI_MAX_FLOW /(float) T1_index;
   gradient2 = (float)AVI_MAX_FLOW / (float)(T1_index - ED_index);
   y_intercept = -gradient2 * (float)ED_index;

   while (index < T1_index)
   {
      Flow[index] = gradient1 * index;
      index++;
   }

   while (index < ED_index)
   {
      Flow[index] = gradient2 * index + y_intercept;
      index++;
   }

   while (index < AVICentral->CalAvPulse.Length())
   {
      Flow[index] = 0;
      index++;
   }
}

bool TAVI::FourierTransform()
{
   bool result=false;
   float FrequencyIncrement;
   if (AVICentral->CalAvPulse.Length() != 0)
   {
      SpectrumLength = AVICentral->CalAvPulse.Length() / 2 + 1;
      FrequencyIncrement = MEAS_DEFAULT_SAMPLE_RATE / (2 * (SpectrumLength - 1));
      Pressure_Output = (fftwf_complex *) fftwf_malloc(sizeof(fftwf_complex) * SpectrumLength);
      Flow_Output = (fftwf_complex *) fftwf_malloc(sizeof(fftwf_complex) * SpectrumLength);
      Pressure_Plan = fftwf_plan_dft_r2c_1d(AVICentral->CalAvPulse.Length(), AVICentral->CalAvPulse.Profile, Pressure_Output, FFTW_ESTIMATE);
      Flow_Plan = fftwf_plan_dft_r2c_1d(AVICentral->CalAvPulse.Length(), Flow, Flow_Output, FFTW_ESTIMATE);
      fftwf_execute(Pressure_Plan);
      fftwf_execute(Flow_Plan);
      for (int i = 0; i < SpectrumLength; i++)
      {
         Pressure_Spectrum[i]= Magnitude(Pressure_Output[i][0], Pressure_Output[i][1]);
         Flow_Spectrum[i]= Magnitude(Flow_Output[i][0], Flow_Output[i][1]);
         Frequency[i]= i * FrequencyIncrement;
      }
      result=true;
   }
   return (result);
}

float TAVI::Magnitude(float real, float imaginary)
{
   float a;
   float b;
   float magnitude;

   a = (2 * real) / AVICentral->CalAvPulse.Length();
   b = (2 * imaginary) / AVICentral->CalAvPulse.Length();
   magnitude = (a * a) + (b * b);
   return magnitude;
}

bool TAVI::Harmonics()
{
   bool result=false;
   float a1;
   float b1;
   float a2;
   float b2;

   if (SpectrumLength!=DEFAULT_VALUE)
   {
      for (int i = 0; i <= AVI_MAX_HARMONICS; i++)
      {
         Pressure_Harmonics[i]= sqrt(Pressure_Spectrum[i]);
         Flow_Harmonics[i]= sqrt(Flow_Spectrum[i]);
      }
      result=true;
   }
   return (result);
}

void TAVI::CalculateImpedance()
{
   Impedance = 0;

   for (int i = 4; i <= 7; i++)
   {
      Impedance += Pressure_Harmonics[i] / Flow_Harmonics[i];
   }
   Impedance = Impedance / 4;
}

void TAVI::CalculatePressureWaves()
{
   float derivative;
   float threshold;
   float remainder;
   float index;

   AVICurveFit->Init();

   // Calculate a rough estimate of the forward and backward pressure waves
   for (int i = 0;i < AVICentral->CalAvPulse.Length();i++)
   {
      Forward_Pressure[i] = (AVICentral->CalAvPulse.Profile[i] + (Flow[i] * Impedance)) / 2;
      Backward_Pressure[i] = (AVICentral->CalAvPulse.Profile[i] - (Flow[i] * Impedance)) / 2;
      Forward_Pressure_Refined[i] = Forward_Pressure[i];
      Backward_Pressure_Refined[i] = Backward_Pressure[i];
   }

   // Find the maximum derivative of the backward wave between T1 and ED
   for (int i = T1_index; i < ED_index + 1; i++)
   {
      derivative = Backward_Pressure[i + 1] - Backward_Pressure[i];
      if (i == T1_index)
      {
         MaxDpDt = derivative;
         MaxDpDt_index = i;
      }
      else if (derivative > MaxDpDt)
      {
         MaxDpDt = derivative;
         MaxDpDt_index = i;
      }
   }

   // Refine the forward and backward pressure waves
   threshold = Backward_Pressure[MaxDpDt_index];
   for (int i = MaxDpDt_index; i > 0; i--)
   {
      // Calculate the new backward pressure wave
      if (threshold > Backward_Pressure[0])
      {
         Backward_Pressure_Refined[i] = Backward_Pressure_Refined[i + 1] - MaxDpDt;
         threshold = Backward_Pressure_Refined[i];
      }
      // Once the threshold is found, the rest of the signal is given its value
      else
      {
         Backward_Pressure_Refined[i] = Backward_Pressure[0];
      }
      // Calculate the new forward pressure wave
      remainder = Backward_Pressure[i] - Backward_Pressure_Refined[i];
      Forward_Pressure_Refined[i] = Forward_Pressure_Refined[i] + remainder;
   }

   // Find the index of the Forward Pressure maximum
   Forward_index = MaxDpDt_index - ((Backward_Pressure[MaxDpDt_index] - Backward_Pressure[0]) / MaxDpDt);
   Forward_Max_index = 0;
   Forward_Max = Forward_Pressure[Forward_Max_index];
   for (int i = 1; i <= Forward_index; i++)
   {
      if (Forward_Pressure[i] > Forward_Max)
      {
         Forward_Max = Forward_Pressure[i];
         Forward_Max_index = i;
      }
   }

   // Interpolate the Forward Pressure wave
   for (int i = 0; i <= Forward_Max_index + 1; i++)
   {
      AVICurveFit->EnterStatValue(i, Forward_Pressure_Refined[i]);
   }
   for (int i = ED_index; i < AVICentral->CalAvPulse.Length(); i++)
   {
      AVICurveFit->EnterStatValue(i, Forward_Pressure_Refined[i]);
   }

   for (int i = 0; i < AVICentral->CalAvPulse.Length(); i++)
   {
      Forward_Pressure_Final[i] = AVICurveFit->CubicSpline(i);
      remainder = Forward_Pressure_Refined[i] - Forward_Pressure_Final[i];
      Backward_Pressure_Final[i] = Backward_Pressure_Refined[i] + remainder;
   }
}

void TAVI::RecalculateFlow()
{
   for (int i = 0; i < AVICentral->CalAvPulse.Length(); i++)
   {
      Flow[i] = (2 * Forward_Pressure_Final[i]) - AVICentral->CalAvPulse.Profile[i];
   }
}

void TAVI::CrossCorrelation()
{
   TVector *Forward_Vector;
   TVector *Backward_Vector;

   Forward_Vector = new TVector(Application);
   Backward_Vector = new TVector(Application);

   Forward_Vector->NrOfElem = ED_index + 1;
   Backward_Vector->NrOfElem = ED_index + 1;
   Forward_Vector_Max = Forward_Pressure_Final[0];
   Forward_Vector_Min = Forward_Pressure_Final[0];
   Backward_Vector_Max = Backward_Pressure_Final[0];
   Backward_Vector_Min = Backward_Pressure_Final[0];

   // Find the minimums and maximums
   for (int i = 1; i <= ED_index; i++)
   {
      if(Forward_Pressure_Final[i] > Forward_Vector_Max)
      {
         Forward_Vector_Max = Forward_Pressure_Final[i];
      }
      if(Forward_Pressure_Final[i] < Forward_Vector_Min)
      {
         Forward_Vector_Min = Forward_Pressure_Final[i];
      }
      if(Backward_Pressure_Final[i] > Backward_Vector_Max)
      {
         Backward_Vector_Max = Backward_Pressure_Final[i];
      }
      if(Backward_Pressure_Final[i] < Backward_Vector_Min)
      {
         Backward_Vector_Min = Backward_Pressure_Final[i];
      }
   }

   // Normalise the pressure signals
   for (int i = 0; i <= ED_index; i++)
   {
      Forward_Vector->Elem[i + 1] = (Forward_Pressure_Final[i] - Forward_Vector_Min) / (Forward_Vector_Max - Forward_Vector_Min);
      Backward_Vector->Elem[i + 1] = (Backward_Pressure_Final[i] - Backward_Vector_Min) / (Backward_Vector_Max - Backward_Vector_Min);
   }

   // Calculate the Cross Correlation Array
   for (int i = 0; i <= AVI_MAX_CORRELATIONS; i++)
   {
      Cross_Correlation[i] = Forward_Vector->Correlate(Backward_Vector, i - (AVI_MAX_CORRELATIONS / 2));
   }

   // Calculate AVI Parameters
   Forward_Pressure_Max = math_MaxInArray(Forward_Pressure_Final, AVICentral->CalAvPulse.Length());
   Forward_Pressure_Max_Time_Index = math_MaxInArrayIndex(Forward_Pressure_Final, AVICentral->CalAvPulse.Length());
   Forward_Pressure_Max_Time = AVICentral->CalAvPulse.IndexToTime(Forward_Pressure_Max_Time_Index);
   Forward_Pressure_Height = Forward_Pressure_Max - Forward_Pressure_Final[0];
   Backward_Pressure_Max = math_MaxInArray(Backward_Pressure_Final, AVICentral->CalAvPulse.Length());
   Backward_Pressure_Max_Time_Index = math_MaxInArrayIndex(Backward_Pressure_Final, AVICentral->CalAvPulse.Length());
   Backward_Pressure_Max_Time = AVICentral->CalAvPulse.IndexToTime(Backward_Pressure_Max_Time_Index);
   Backward_Pressure_Height = Backward_Pressure_Max - Backward_Pressure_Final[0];
   Reflection_Index = (Backward_Pressure_Height / Forward_Pressure_Height) * 100;
   Aortic_Reflection_Lag = (float)math_MaxInArrayIndex(Cross_Correlation, AVI_MAX_CORRELATIONS + 1) / 2;// - (AVI_MAX_CORRELATIONS / 2);
   Aortic_Reflection_Time = Aortic_Reflection_Lag * 1000. / MEAS_DEFAULT_SAMPLE_RATE;//AVICentral->CalAvPulse.IndexToTime(Aortic_Reflection_Lag);
   Carotid_Femoral_Transmission_Time = (AVI_CAROTID_FEMORAL_SLOPE * Aortic_Reflection_Time) + AVI_CAROTID_FEMORAL_INTERCEPT;
   if (Aortic_Distance < DEFAULT_VALUE)
   {
      SphygmoCor_Velocity_Index = Aortic_Distance / Carotid_Femoral_Transmission_Time;
   }
   else
   {
      SphygmoCor_Velocity_Index = DEFAULT_VALUE;
   }
}
//------------------------------------------------------------
bool TAVI::Store(TDataSet* pDataSet, TPressureCentral *Central)
{
   bool ret = true;
   MEAS_ID_TYPE  meas_mode;

   meas_mode = patient_get_study_mode();

    // Only store if AVI is enabled and in PWA mode
   if (!config_get_avi_option() || meas_mode != MEAS_PWA_ID)
   {
      return true;
   }

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
  {
      // Reset AVI parameters and store them so we know validation failed
      // This is because AVI does not stop PWA from calculating
    MsgBox(TWARNING, GetCurrentPwaMeasureDetails(), MSG_VALIDATION_ERROR, MSG_AVI_ERROR_CALC);
    Initialise();
    ret = false;
  }


  // Actual storing

  try
  {
      // Store specific properties
      pDataSet->FieldByName(MPWA_C_FLOW)->Value = PackFloatToString(Flow, Central->CalAvPulse.Length());
      pDataSet->FieldByName(MPWA_C_FORWARD)->Value = PackFloatToString(Forward_Pressure_Final, Central->CalAvPulse.Length());
      pDataSet->FieldByName(MPWA_C_BACKWARD)->Value = PackFloatToString(Backward_Pressure_Final, Central->CalAvPulse.Length());

      pDataSet->FieldByName(MPWA_C_AVI)->AsFloat = Aortic_Reflection_Time;
      pDataSet->FieldByName(MPWA_C_PPTT)->AsFloat = Carotid_Femoral_Transmission_Time;
      pDataSet->FieldByName(MPWA_C_AVD)->AsFloat = Aortic_Distance;
      pDataSet->FieldByName(MPWA_C_PWV)->AsFloat = SphygmoCor_Velocity_Index;

      // Not Calculated yet
      /*pDataSet->FieldByName(MPWA_C_FORWARD_AREA)->AsFloat = ;
      pDataSet->FieldByName(MPWA_C_BACKWARD_AREA)->AsFloat = ;
      pDataSet->FieldByName(MPWA_C_AREA_RATIO)->AsFloat = ;*/

      pDataSet->FieldByName(MPWA_C_PULSE_RATIO)->AsInteger = Reflection_Index;
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

  // return at success
  return ret;
}
//------------------------------------------------------------
bool TAVI::Populate(TDataSet* pDataSet, TPressureCentral *Central)
{
   MEAS_ID_TYPE  meas_mode;

   meas_mode = patient_get_study_mode();

    // Only populate if AVI is enabled and in PWA mode
   if (!config_get_avi_option() || meas_mode != MEAS_PWA_ID)
   {
      return true;
   }

   try
   {
      if (pDataSet->RecordCount <= 0)
      {
         return false;
      }

      // Chack if AVI has been calculated yet
      Aortic_Reflection_Time = pDataSet->FieldByName(MPWA_C_AVI)->AsFloat;
      if (Aortic_Reflection_Time == DEFAULT_VALUE)
      {
         Initialise();
         return true;
      }

      // PickUp Arrays
      int NofBytes;

      NofBytes = min((int)(pDataSet->FieldByName(MPWA_C_FLOW)->AsString.Length()),
                     (int)(PRESSURE_PULSE_MAXLENGTH*sizeof(int)));
      if (UnpackFromString(Flow, pDataSet->FieldByName(MPWA_C_FLOW)->AsString, NofBytes) == false)
      {
         return false;
      }

      NofBytes = min((int)(pDataSet->FieldByName(MPWA_C_FORWARD)->AsString.Length()),
                     (int)(PRESSURE_PULSE_MAXLENGTH*sizeof(int)));
      if (UnpackFromString(Forward_Pressure_Final, pDataSet->FieldByName(MPWA_C_FORWARD)->AsString, NofBytes) == false)
      {
         return false;
      }

      NofBytes = min((int)(pDataSet->FieldByName(MPWA_C_BACKWARD)->AsString.Length()),
                     (int)(PRESSURE_PULSE_MAXLENGTH*sizeof(int)));
      if (UnpackFromString(Backward_Pressure_Final, pDataSet->FieldByName(MPWA_C_BACKWARD)->AsString, NofBytes) == false)
      {
         return false;
      }

      // Pick Up Variables
      Carotid_Femoral_Transmission_Time = pDataSet->FieldByName(MPWA_C_PPTT)->AsFloat;
      Aortic_Distance = pDataSet->FieldByName(MPWA_C_AVD)->AsFloat;
      SphygmoCor_Velocity_Index = pDataSet->FieldByName(MPWA_C_PWV)->AsFloat;

      // Not Calculated yet
      /*pDataSet->FieldByName(MPWA_C_FORWARD_AREA)->AsFloat;
      pDataSet->FieldByName(MPWA_C_BACKWARD_AREA)->AsFloat;
      pDataSet->FieldByName(MPWA_C_AREA_RATIO)->AsFloat;*/

      Reflection_Index = pDataSet->FieldByName(MPWA_C_PULSE_RATIO)->AsInteger;
      Forward_Pressure_Max = math_MaxInArray(Forward_Pressure_Final, Central->CalAvPulse.Length());
      Forward_Pressure_Max_Time_Index = math_MaxInArrayIndex(Forward_Pressure_Final, Central->CalAvPulse.Length());
      Forward_Pressure_Max_Time = Central->CalAvPulse.IndexToTime(Forward_Pressure_Max_Time_Index);
      Forward_Pressure_Height = Forward_Pressure_Max - Forward_Pressure_Final[0];
      Backward_Pressure_Max = math_MaxInArray(Backward_Pressure_Final, Central->CalAvPulse.Length());
      Backward_Pressure_Max_Time_Index = math_MaxInArrayIndex(Backward_Pressure_Final, Central->CalAvPulse.Length());
      Backward_Pressure_Max_Time = Central->CalAvPulse.IndexToTime(Backward_Pressure_Max_Time_Index);
      Backward_Pressure_Height = Backward_Pressure_Max - Backward_Pressure_Final[0];
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
bool TAVI::ExportPrintTitle(TDataSet* pDataSet, String &pOut)
{
   MEAS_ID_TYPE  meas_mode;

   meas_mode = patient_get_study_mode();

    // Only export if AVI is enabled and in PWA mode
   if (!config_get_avi_option() || meas_mode != MEAS_PWA_ID)
   {
      return true;
   }

   // Actual printing title string
  try
  {
    pOut = pOut + "C_APRT" + "\t";
    pOut = pOut + "C_CFTT" + "\t";
    pOut = pOut + "C_CFD" + "\t";
    pOut = pOut + "C_WRPWV" + "\t";
    pOut = pOut + "C_RI" + "\t";
    pOut = pOut + "C_FPPH" + "\t";
    pOut = pOut + "C_FPPT" + "\t";
    pOut = pOut + "C_RPPH" + "\t";
    pOut = pOut + "C_RPPT" + "\t";
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
bool TAVI::Export(String &pOut)
{
   MEAS_ID_TYPE  meas_mode;

   meas_mode = patient_get_study_mode();

   // Only export if AVI is enabled and calculated in PWA mode
   if (!config_get_avi_option() || Aortic_Reflection_Time == DEFAULT_VALUE || meas_mode != MEAS_PWA_ID)
   {
      return true;
   }

   // Export specific properties
  pOut = pOut + RoundIntToStr(Aortic_Reflection_Time) + "\t";
  pOut = pOut + RoundIntToStr(Carotid_Femoral_Transmission_Time) + "\t";
  pOut = pOut + RoundIntToStr(Aortic_Distance) + "\t";
  pOut = pOut + FormatFloat("#0.0", SphygmoCor_Velocity_Index) + "\t";
  pOut = pOut + RoundIntToStr(Reflection_Index) + "\t";
  pOut = pOut + RoundIntToStr(Forward_Pressure_Height) + "\t";
  pOut = pOut + RoundIntToStr(Forward_Pressure_Max_Time) + "\t";
  pOut = pOut + RoundIntToStr(Backward_Pressure_Height) + "\t";
  pOut = pOut + RoundIntToStr(Backward_Pressure_Max_Time) + "\t";

  // Success
  return true;
}

bool TAVI::ValidateBeforeCalculate()
{
   bool ret = true;
   MEAS_ID_TYPE  meas_mode;

   meas_mode = patient_get_study_mode();

    // Only validate if AVI is enabled and in PWA mode
   if (!config_get_avi_option() || meas_mode != MEAS_PWA_ID)
   {
      return ret;
   }


   // Check T1 has been calculated
   if (AVICentral->T1 == DEFAULT_VALUE)
   {
      MsgBox(TWARNING,
           GetCurrentPwaMeasureDetails(),
           MSG_VALIDATION_ERROR, MSG_AVI_NO_T1,
           LoadStr(MSG_AVI_NO_T1));
      ret = false;
   }

   // Check ED has been calculated
   if (AVICentral->ED == DEFAULT_VALUE)
   {
      MsgBox(TWARNING,
           GetCurrentPwaMeasureDetails(),
           MSG_VALIDATION_ERROR, MSG_AVI_NO_ED,
           LoadStr(MSG_AVI_NO_ED));
      ret = false;
   }

   // Check T1 is within the allowed range
   if (AVICentral->T1 < PWA_MIN_T1 || AVICentral->T1 > PWA_MAX_T1)
   {
      MsgBox(TWARNING,
           GetCurrentPwaMeasureDetails(),
           MSG_VALIDATION_ERROR, MSG_AVI_T1_OUT,
           LoadStr(MSG_AVI_T1_OUT) + RoundIntToStr(PWA_MIN_T1) + "->" + RoundIntToStr(PWA_MAX_T1)
           + ".\n\nT1 = " + RoundIntToStr(AVICentral->T1));
      ret = false;
   }
   return ret;
}

bool TAVI::ValidateBeforeStore()
{
   bool ret = true;
   MEAS_ID_TYPE  meas_mode;

   meas_mode = patient_get_study_mode();

   // Only validate if AVI is enabled and calculated in PWA mode
   if (!config_get_avi_option() || Aortic_Reflection_Time == DEFAULT_VALUE || meas_mode != MEAS_PWA_ID)
   {
      return ret;
   }

   // Check reflection index is less than 100%
   if (Reflection_Index > 100)
   {
      MsgBox(TWARNING,
           GetCurrentPwaMeasureDetails(),
           MSG_VALIDATION_ERROR, MSG_AVI_REFLECTION_INDEX_OUT,
           LoadStr(MSG_AVI_REFLECTION_INDEX_OUT) + RoundIntToStr(Reflection_Index));
      ret = false;
   }

   // Check aortic reflection time is greater than 50ms
   if (Aortic_Reflection_Time < 50)
   {
      MsgBox(TWARNING,
           GetCurrentPwaMeasureDetails(),
           MSG_VALIDATION_ERROR, MSG_AVI_AORTIC_REFLECTION_TIME_OUT,
           LoadStr(MSG_AVI_AORTIC_REFLECTION_TIME_OUT) + RoundIntToStr(Aortic_Reflection_Time));
      ret = false;
   }

   // Check carotid - femoral transmission time is greater than 20ms
   if (Carotid_Femoral_Transmission_Time < 20)
   {
      MsgBox(TWARNING,
           GetCurrentPwaMeasureDetails(),
           MSG_VALIDATION_ERROR, MSG_AVI_TRANSMISSION_TIME_OUT,
           LoadStr(MSG_AVI_TRANSMISSION_TIME_OUT) + RoundIntToStr(Carotid_Femoral_Transmission_Time));
      ret = false;
   }

   // Validate peak times
   if (Forward_Pressure_Max_Time > Backward_Pressure_Max_Time)
   {
      MsgBox(TWARNING,
           GetCurrentPwaMeasureDetails(),
           MSG_VALIDATION_ERROR, MSG_AVI_PEAK_TIMES,
           LoadStr(MSG_AVI_PEAK_TIMES));
      ret = false;
   }

   // Validate SphygmoCor Velocity Index if it has been calculated
   if (Aortic_Distance != DEFAULT_VALUE)
   {
      if ((SphygmoCor_Velocity_Index > PWV_TOO_LARGE) || (SphygmoCor_Velocity_Index < PWV_TOO_SMALL))
      {
         MsgBox(TWARNING,
               GetCurrentPwaMeasureDetails(),
               MSG_VALIDATION_ERROR, MSG_AVI_VELOCITY_OUT,
               LoadStr(MSG_AVI_VELOCITY_OUT) + RoundIntToStr(SphygmoCor_Velocity_Index));
         ret = false;
      }
   }
   return ret;
}
