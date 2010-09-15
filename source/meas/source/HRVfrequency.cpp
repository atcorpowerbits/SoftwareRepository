//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
//#include <sdlbase.hpp>
#include <sdlbasepack_82C6.hpp>
#include <sdlmathpack_82C6.hpp>

#include <math.h>
#include <stdio.h>

#include <msg/pubserv.h>
#include <meas/pubserv.h>
#include "hrvclass.h"
#include "HRVfrequency.h"

TCurveFit *CurveFit1;
TFastFourier *FFT1;
//---------------------------------------------------------------------------
#pragma package(smart_init)
THRVFrequency::THRVFrequency()
{

   CurveFit1= new TCurveFit(Application);
   FFT1= new TFastFourier(Application);
   RtoR_sampled = NULL;
   Time_sampled = NULL;
   Initialise();
}
//---------------------------------------------------------------------------

void THRVFrequency::Initialise()
{
   hrv = meas_get_current_hrv();
   CurveFit1->Init();

   if (RtoR_sampled!= NULL)
   {
      delete[] RtoR_sampled;
      RtoR_sampled = NULL;
   }

   if (Time_sampled != NULL)
   {
      delete[] Time_sampled;
      Time_sampled = NULL;
   }


   number_of_points_sampled= 0;
   Active_Window = SpecHamming;
   number_of_points_spectrum=0;
   Spectrum_Max = 0;
   TotalPower = 0;
   RtoR_sampled = new float[HRV_MAX_TIME_LENGTH];
   Time_sampled = new float[HRV_MAX_TIME_LENGTH];
   SetDefault();

}
//---------------------------------------------------------------------------

void THRVFrequency::SetDefault()
{
   for (int i=0 ; i< HRV_MAX_TIME_LENGTH; i++)
   {
      RtoR_sampled[i] = DEFAULT_VALUE;
      Time_sampled[i] = DEFAULT_VALUE;
   }
   for (int i=0 ; i < HRV_FREQ_DEFAULT_SPECTRUM_SIZE; i++)
   {
      Power_Spectrum[i] = DEFAULT_VALUE;
      Frequency[i] = DEFAULT_VALUE;
   }
}
//---------------------------------------------------------------------------

THRVFrequency::~THRVFrequency()
{

   if (RtoR_sampled!= NULL)
   {
      delete[] RtoR_sampled;
   }

   if (Time_sampled != NULL)
   {
      delete[] Time_sampled;
   }

   delete CurveFit1;
   delete FFT1;
}

//--------------------------------------------------------------------------

bool THRVFrequency::Resample()
{
   int Time_max;
   int Count=0;
   float sum=0;

   for(int i=0;i<hrv->PulsesInSession_refined;i++)
   {
      CurveFit1->EnterStatValue(hrv->Time_raw_refined[i],hrv->RtoR_raw_refined[i]);
   }
   Time_max=floor(hrv->Time_raw_refined[hrv->PulsesInSession_refined-1]);

   while (sum<=Time_max)
   {
      sum = sum + HRV_RTOR_SAMPLING_PERIOD;
      Time_sampled[Count]=sum;
      Count++;
   }
   number_of_points_sampled=Count;
   for (int km=0;km<Count;km++)
   {
      RtoR_sampled[km]=CurveFit1->CubicSpline(Time_sampled[km]);
   }

   return true;

}
//----------------------------------------------------------------
bool THRVFrequency::PowerSpectrum()
{
   bool result=false;
   FFT1->Clear();
   if (number_of_points_sampled!=0)
   {
      FFT1->SpectrumSize = 2 * HRV_FREQ_DEFAULT_SPECTRUM_SIZE;
      for (int i=1;i<=number_of_points_sampled;i++)
      {
         FFT1->RealSpec[i]= RtoR_sampled[i-1];
      }
      switch (Active_Window)
      {
         case 0 : FFT1->WeightingWindow=fwRectangle; break;
         case 1 : FFT1->WeightingWindow=fwTriangle; break;
         case 2 : FFT1->WeightingWindow=fwCos2; break;
         case 3 : FFT1->WeightingWindow=fwGauss; break;
         case 4 : FFT1->WeightingWindow=fwHamming; break;
         case 5 : FFT1->WeightingWindow=fwBlackman; break;
      }
      FFT1->Transform();
      for (int i=1; i<=FFT1->SpectrumSize/2; i++)
      {
         Power_Spectrum[i-1]= FFT1->PowerSpec[i];
         Frequency[i-1]=FFT1->FreqOfLine(i,HRV_RTOR_SAMPLING_PERIOD);
      }
      number_of_points_spectrum=FFT1->SpectrumSize/2;

      result=true;
   }
   return (result);
}
//----------------------------------------------------------------
bool THRVFrequency::CalculateFreqParam()
{
   float *freq_low;
   freq_low= new float [number_of_points_spectrum];
   float *spect_low;
   spect_low= new float [number_of_points_spectrum];
   float *freq_hi;
   freq_hi= new float [number_of_points_spectrum];
   float *spect_hi;
   spect_hi= new float [number_of_points_spectrum];

   int indexlo;
   int indexhi;
   float sumL=0;
   float sumH=0;
   float sumT = 0;
   int numlow=0;
   int numhi=0;
   float lf_max_spectrum = 0;
   float hf_max_spectrum = 0;

   for (int i = 1; i < number_of_points_spectrum; i++)
   {
       sumT = sumT + Power_Spectrum[i];
   }

   TotalPower = sumT / number_of_points_spectrum;

   for (int i = 1; i < number_of_points_spectrum; i++)
   {
      if ((Frequency[i]<=0.15)&&(Frequency[i]>0.04))                        
      {
         freq_low[numlow]=Frequency[i];
         spect_low[numlow]=Power_Spectrum[i];
         sumL=sumL+Power_Spectrum[i];
         numlow++;
      }
      else if ((Frequency[i]>0.15)&&(Frequency[i]<=0.4))
      {
         freq_hi[numhi]=Frequency[i];
         spect_hi[numhi]=Power_Spectrum[i];
         sumH=sumH+Power_Spectrum[i];
         numhi++;
      }
   }
   LF_Power=sumL/(number_of_points_spectrum);
   LF_Power_normlised=sumL*100/(sumL+sumH);
   HF_Power=sumH/(number_of_points_spectrum);
   HF_Power_normlised=sumH*100/(sumL+sumH);
   LF_HF_Ratio= LF_Power/HF_Power;
   indexlo=math_MaxInArrayIndex(&spect_low[0],numlow);
   LF_Freq_max=freq_low[indexlo];
   indexhi=math_MaxInArrayIndex(&spect_hi[0],numhi);
   HF_Freq_max=freq_hi[indexhi];
   lf_max_spectrum = math_MaxInArray(&spect_low[0],numlow);
   hf_max_spectrum=math_MaxInArray(&spect_hi[0],numhi);

   if (lf_max_spectrum > hf_max_spectrum)
   {
      Spectrum_Max = lf_max_spectrum;
   }
   else
   {
      Spectrum_Max = hf_max_spectrum;
   }

   delete [] freq_low;
   delete [] spect_low;
   delete [] freq_hi;
   delete [] spect_hi;

   return true;
}
//----------------------------------------------------------------
bool THRVFrequency::Calculate()
{
  Initialise();
  bool ret=false;

  if(Resample())
  {
     if(PowerSpectrum())
     {
        if(CalculateFreqParam())
        {
           ret=true;
        }
     }
  }

  return ret;
}


bool THRVFrequency::ValidateBeforeStore()
{

   bool success = true;
   int  i = 0;

   if (number_of_points_spectrum <= 0 || number_of_points_spectrum > 128)
   {
      MsgBox(TERROR,
           GetCurrentHRVMeasureDetails(),
           MSG_VALIDATION_ERROR, MSG_HRV_POINTS_OUT,
           LoadStr(MSG_HRV_POINTS_OUT) + IntToStr(number_of_points_spectrum));
      success = false;
   }

   while (i < number_of_points_spectrum && success)
   {
      if (Power_Spectrum[i] < 0)
      {
         MsgBox(TERROR, GetCurrentHRVMeasureDetails(), MSG_VALIDATION_ERROR, MSG_HRV_NEG_POWER,
                LoadStr(MSG_HRV_NEG_POWER) + IntToStr(i));
         success = false;
      }
      ++i;
   }

   i = 0;
   while (i < number_of_points_spectrum && success)
   {
      if (Frequency[i] < 0)
      {
         MsgBox(TERROR, GetCurrentHRVMeasureDetails(), MSG_VALIDATION_ERROR, MSG_HRV_NEG_FREQUENCY,
                LoadStr(MSG_HRV_NEG_FREQUENCY) + IntToStr(i));
         success = false;
      }
      ++i;
   }

   if (LF_Power < 0)
   {
      MsgBox(TERROR, GetCurrentHRVMeasureDetails(), MSG_VALIDATION_ERROR, MSG_HRV_NEG_LF_POWER);
      success = false;
   }

   if (HF_Power < 0)
   {
      MsgBox(TERROR, GetCurrentHRVMeasureDetails(), MSG_VALIDATION_ERROR, MSG_HRV_NEG_HF_POWER);
      success = false;
   }

   if (LF_Power_normlised > 100)
   {
      MsgBox(TERROR,
           GetCurrentHRVMeasureDetails(),
           MSG_VALIDATION_ERROR, MSG_HRV_LF_POWER_NORM_OUT,
           LoadStr(MSG_HRV_LF_POWER_NORM_OUT) + RoundIntToStr(LF_Power_normlised));
      success = false;
   }

   if (HF_Power_normlised > 100)
   {
      MsgBox(TERROR,
           GetCurrentHRVMeasureDetails(),
           MSG_VALIDATION_ERROR, MSG_HRV_HF_POWER_NORM_OUT,
           LoadStr(MSG_HRV_HF_POWER_NORM_OUT) + RoundIntToStr(HF_Power_normlised));
      success = false;
   }

   if (LF_Freq_max < 0.04 || LF_Freq_max > 0.15)
   {
      MsgBox(TERROR,
           GetCurrentHRVMeasureDetails(),
           MSG_VALIDATION_ERROR, MSG_HRV_LF_MAX_OUT,
           LoadStr(MSG_HRV_LF_MAX_OUT) + RoundIntToStr(LF_Freq_max));
      success = false;
   }

   if (HF_Freq_max < 0.15 || HF_Freq_max > 0.4)
   {
      MsgBox(TERROR,
           GetCurrentHRVMeasureDetails(),
           MSG_VALIDATION_ERROR, MSG_HRV_HF_MAX_OUT,
           LoadStr(MSG_HRV_HF_MAX_OUT) + RoundIntToStr(HF_Freq_max));
      success = false;
   }

   return success;
}

bool THRVFrequency::Store(TDataSet* pDataSet)
{
   try
   {
      pDataSet->FieldByName(MHRV_POWER_SPECTRUM)->Value =
       PackFloatToString(Power_Spectrum, number_of_points_spectrum);

      pDataSet->FieldByName(MHRV_FREQUENCY)->Value =
       PackFloatToString(Frequency, number_of_points_spectrum);

      pDataSet->FieldByName(MHRV_SPECTRUM_POINTS)->AsInteger = number_of_points_spectrum;
      pDataSet->FieldByName(MHRV_LF_POWER)->AsFloat = LF_Power;
      pDataSet->FieldByName(MHRV_LF_POWER_NORMALISED)->AsFloat = LF_Power_normlised;
      pDataSet->FieldByName(MHRV_HF_POWER)->AsFloat = HF_Power;
      pDataSet->FieldByName(MHRV_HF_POWER_NORMALISED)->AsFloat = HF_Power_normlised;
      pDataSet->FieldByName(MHRV_LF_HF_RATIO)->AsFloat = LF_HF_Ratio;
      pDataSet->FieldByName(MHRV_LF_MAXIMUM)->AsFloat = LF_Freq_max;
      pDataSet->FieldByName(MHRV_HF_MAXIMUM)->AsFloat = HF_Freq_max;
      pDataSet->FieldByName(MHRV_SPECTRUM_MAXIMUM)->AsFloat = Spectrum_Max;
      pDataSet->FieldByName(MHRV_TOTAL_POWER)->AsFloat = TotalPower;

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

bool THRVFrequency::Populate(TDataSet* pDataSet)
{
   try
   {


      number_of_points_spectrum = pDataSet->FieldByName(MHRV_SPECTRUM_POINTS)->AsInteger;

      if (number_of_points_spectrum)
      {
         if (UnpackFloatFromString(Power_Spectrum,
                                   pDataSet->FieldByName(MHRV_POWER_SPECTRUM)->AsString,
                                   (number_of_points_spectrum * sizeof(float)), 1) == false)
         {
            return false;
         }

         if (UnpackFloatFromString(Frequency,
                                   pDataSet->FieldByName(MHRV_FREQUENCY)->AsString,
                                   (number_of_points_spectrum * sizeof(float)), 1) == false)
         {
            return false;
         }
         LF_Power = pDataSet->FieldByName(MHRV_LF_POWER)->AsFloat;
         LF_Power_normlised = pDataSet->FieldByName(MHRV_LF_POWER_NORMALISED)->AsFloat;
         HF_Power = pDataSet->FieldByName(MHRV_HF_POWER)->AsFloat;
         HF_Power_normlised = pDataSet->FieldByName(MHRV_HF_POWER_NORMALISED)->AsFloat;
         LF_HF_Ratio = pDataSet->FieldByName(MHRV_LF_HF_RATIO)->AsFloat;
         LF_Freq_max = pDataSet->FieldByName(MHRV_LF_MAXIMUM)->AsFloat;
         HF_Freq_max = pDataSet->FieldByName(MHRV_HF_MAXIMUM)->AsFloat;
         Spectrum_Max = pDataSet->FieldByName(MHRV_SPECTRUM_MAXIMUM)->AsFloat;
         TotalPower = pDataSet->FieldByName(MHRV_TOTAL_POWER)->AsFloat;

         return true;
      }
      else
      {
         return false;
      }
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

//--------------------------------------------------------------------------------
bool THRVFrequency::ExportPrintTitle(TDataSet* pDataSet, String &pOut)
{
  // Actual printing title string
  try
  {
    // Export specific properties
    pOut = pOut + pDataSet->FieldByName(MHRV_SPECTRUM_POINTS)->DisplayName + "\t";
    pOut = pOut + pDataSet->FieldByName(MHRV_LF_POWER)->DisplayName + "\t";
    pOut = pOut + pDataSet->FieldByName(MHRV_LF_POWER_NORMALISED)->DisplayName + "\t";
    pOut = pOut + pDataSet->FieldByName(MHRV_HF_POWER)->DisplayName + "\t";
    pOut = pOut + pDataSet->FieldByName(MHRV_HF_POWER_NORMALISED)->DisplayName + "\t";
    pOut = pOut + pDataSet->FieldByName(MHRV_LF_HF_RATIO)->DisplayName + "\t";
    pOut = pOut + pDataSet->FieldByName(MHRV_LF_MAXIMUM)->DisplayName + "\t";
    pOut = pOut + pDataSet->FieldByName(MHRV_HF_MAXIMUM)->DisplayName + "\t";
    pOut = pOut + pDataSet->FieldByName(MHRV_SPECTRUM_MAXIMUM)->DisplayName + "\t";
    pOut = pOut + pDataSet->FieldByName(MHRV_TOTAL_POWER)->DisplayName + "\t";
  }
  catch (Exception &exception)
  {
    MsgBox(TERROR, GetCurrentHRVMeasureDetails(), MSG_EXCEPTION, MSG_EXPORT_ERROR, LoadStr(MSG_EXPORT_ERROR) + exception.Message);
    return false;
  }
  // return at success
  return true;
}

bool THRVFrequency::Export(String &pOut)
{
  // Export specific properties
  pOut = pOut + IntToStr(number_of_points_spectrum) + "\t";
  pOut = pOut + FormatFloat("0", LF_Power) + "\t";
  pOut = pOut + FormatFloat("0.00", LF_Power_normlised) + "\t";
  pOut = pOut + FormatFloat("0", HF_Power) + "\t";
  pOut = pOut + FormatFloat("0.00", HF_Power_normlised) + "\t";
  pOut = pOut + FormatFloat("0.00", LF_HF_Ratio) + "\t";
  pOut = pOut + FormatFloat("0.00", LF_Freq_max) + "\t";
  pOut = pOut + FormatFloat("0.00", HF_Freq_max) + "\t";
  pOut = pOut + FormatFloat("0", Spectrum_Max) + "\t";
  pOut = pOut + FormatFloat("0", TotalPower) + "\t";

  // return at success
  return true;
}
