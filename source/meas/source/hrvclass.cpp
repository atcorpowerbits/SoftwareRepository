//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include <config/pubserv.h>
#include <patient/pubserv.h>
#include <msg/pubserv.h>
#include <meas/pubtype.h>
#include <log/pubserv.h>
#include "TSignal.h"
#include "Mathem.h"
#include "Measure.h"
#include "form_hrv.h"
#include "hrvclass.h"
#include "hrvtime.h"
#include "HRVfrequency.h"



const float HRV_ECG_FILTER_THRESHOLD = 0.47;
const int HRV_MIN_QRS_DURATION=40;

//---------------------------------------------------------------------------

#pragma package(smart_init)

THRV          *hrv;
THRVTime      *hrv_time;
THRVFrequency *hrv_frequency;

THRV*  meas_get_current_hrv(void)
{
   return hrv;
}

THRVTime*  meas_get_current_hrvtime(void)
{
   return hrv_time;
}

THRVFrequency*  meas_get_current_hrvfreq(void)
{
   return hrv_frequency;
}

String GetCurrentHRVMeasureDetails()
{
  String ret = "";
  THRV* hrv = meas_get_current_hrv();
  if (hrv==NULL) return ret;
  ret = " Patient :" + IntToStr(hrv->Patient_No);
  ret = ret + ", Measurement :" + hrv->DateTime.DateTimeString();
  ret = ret + ", DataRevision :" + IntToStr(hrv->DataRev) +" ";
  return ret;
}

bool meas_hrv_initialise(void)
{
   CONFIG_SYSTEM_OPTIONS sw_capabilities;
   bool                  hrv_init = false;


   sw_capabilities = config_get_system_options();

   if ((sw_capabilities == CONFIG_HRV_OPTION) ||  (sw_capabilities == CONFIG_EXTENDED_ALL_OPTION))
   {
      hrv = new THRV();
      if (hrv != NULL)
      {
         hrv_time = new THRVTime();
         if (hrv_time != NULL)
         {
            hrv_frequency = new THRVFrequency();
            if (hrv_frequency != NULL)
            {
               if (meas_hrv_form_initialise())
               {
                  hrv_init = true;
               }
            }
         }
      }
   }
   else
   {
      hrv_init = true;
   }
   return hrv_init;
}

void meas_hrv_destroy(void)
{
   if (hrv != NULL)
   {
      delete hrv;
   }
   if (hrv_time != NULL)
   {
      delete hrv_time;
   }

   if (hrv_frequency != NULL)
   {
      delete hrv_frequency;
   }
}

String meas_hrv_get_table_name()
{
  return MHRV;
}

bool meas_hrv_classes_initialise(int sample_rate)
{
   hrv->Initialise(sample_rate);
   hrv_time->Initialise();
   hrv_frequency->Initialise();
   return true;
}

THRVECGSignal::THRVECGSignal(const int pMaxNofPoints, const int pMaxNofOnsets)
                 : TSignal(pMaxNofPoints, pMaxNofOnsets)
{
   ;
}

THRVECGSignal::~THRVECGSignal()
{
   ;
}

//-----------------------------------------------------------------------------
//*****************************************************************************
bool THRVECGSignal::ValidateSignal(const int pMinNofPoints)
{
  bool ret = ValidateSignalLength(pMinNofPoints);
  if (ret == true)
  {
     ret = ValidateSignalHeight(HRV_ECG_MIN_PULSEHEIGHT);
  }
  return ret;
}


//-----------------------------------------------------------------------------
//*****************************************************************************
bool THRVECGSignal::FindOnsets(const int pAlgorithm)
{
   bool ret;

   switch (pAlgorithm)
   {
      case 1:
         ret = Algorithm_QRS_Filter();
         break;
      default:
         ret = false;
         break;
   }

   if ((NofOnsets < SIGNAL_ECG_MIN_ONSETS) || (NofOnsets >= SIGNAL_ECG_MAX_ONSETS))
   {
       onset_error = "Number of onsets out of range, " + IntToStr(NofOnsets);
       ret = false;
   }
   return ret;
}


//-----------------------------------------------------------------------------
//*****************************************************************************
bool THRVECGSignal::Algorithm_QRS_Filter(void)
{
   int    weighting_parm;
   int    i, j, k;
   float  signal_peak;
   float  signal_threshold;
   float  *opened_signal;
   float  *closed_signal;
   float  *resulting_signal;
   float  *signal_segment;
   float  *filtered_resulting_signal;
   int    *index_threshold;
   int    nof_thresholds = 0;
   int    starting_point;
   float  qrs_time1;
   float  qrs_time2;
   int   qrs_duration;
   int   qr1;
   int   qr2;
   bool  qrs_detected;
   bool  result = true;

   // Initialise Onsets
   NofOnsets = 0;
   for (i = 0; i < MaxNofOnsets; i++)
   {
      FloatOnsets[i] = -1;
   }


   opened_signal = new float[MaxNofPoints + 1];
   closed_signal = new float[MaxNofPoints + 1];
   resulting_signal = new float[MaxNofPoints + 1];
   signal_segment = new float[SampleRate*3];    // sample rate * 60 / MIN HEART RATE
   index_threshold = new int[MaxNofOnsets];
   filtered_resulting_signal = new float[MaxNofPoints + 1];

   if (opened_signal == NULL ||
       closed_signal == NULL ||
       resulting_signal == NULL ||
       filtered_resulting_signal == NULL ||
       signal_segment == NULL ||
       index_threshold == NULL)
   {
      onset_error = "Out of Memory...ECG Morphological Filter";
      return false;
   }

   weighting_parm = math_Round(5.5 * SampleRate / 100);
   starting_point= math_Round(0.02*SampleRate);
   Openingn(weighting_parm, &Signal[0], &opened_signal[0]);
   Closingn(weighting_parm, &opened_signal[0], &closed_signal[0]);

   for (i = 0; i < NofPoints; i++)
   {
      resulting_signal[i] = Signal[i] - closed_signal[i];
   }

   signal_peak = math_MaxInArray(&resulting_signal[starting_point-1], NofPoints - weighting_parm-starting_point);
   signal_threshold = HRV_ECG_FILTER_THRESHOLD * signal_peak;

   if (signal_threshold <= 45)
   {
      onset_error = "Signal threshold too low, " + RoundIntToStr(signal_threshold);
      result = false;
   }

   if (result)
   {
      for (i = 0; i < NofPoints - weighting_parm; i++)
      {
         if ((resulting_signal[i] < signal_threshold) &&
            (resulting_signal[i+1] >= signal_threshold))
         {
            if (nof_thresholds < MaxNofOnsets)
            {
               index_threshold[nof_thresholds] = i;
               nof_thresholds++;
            }
         }
      }
      i = 0;
      while ((NofOnsets < MaxNofOnsets) && (i < nof_thresholds-1))
      {
         int ss = 0;
         for (j = index_threshold[i]; j <= index_threshold[i+1];j++)
         {
            if (ss < (SampleRate*3))
            {
               signal_segment[ss] = resulting_signal[j];
               ss++;
            }
         }
         FloatOnsets[NofOnsets] = math_MaxInArrayIndex(&signal_segment[0], ss) + index_threshold[i];
         NofOnsets++;
         for (k = 0; k < ss; k++)
         {
            signal_segment[k] = 0;
         }
         i++;
      }
      if (NofOnsets > 1)
      {
         for(i = 0; i < NofOnsets - 1; i++)
         {
            if ((FloatOnsets[i+1]-FloatOnsets[i]) > SIGNAL_MAX_APPEND_LEN)
            {
            onset_error = "Onsets too far apart";
            result = false;
            }
         }
      }
      else
      {
         onset_error = "Not enough onsets, " + IntToStr(NofOnsets);
         result = false;
      }
   }

   if (result)
   {
      if (NofOnsets > 1)
      {
         for (i = 0; i < NofPoints; i++)
         {
            filtered_resulting_signal[i] = resulting_signal[i];
         }

         if(math_SmoothArray(filtered_resulting_signal, NofPoints, 5))
         {
            qrs_duration = 0;
            j = 1;
            while (j < NofOnsets - 1)
            {
               qr1 = FloatOnsets[j] - 5;
               qrs_detected = false;
               while (!qrs_detected && (qr1 > (FloatOnsets[j-1] - weighting_parm)))
               {
	               if ((filtered_resulting_signal[qr1] <= filtered_resulting_signal[qr1-1]) || (filtered_resulting_signal[qr1] <= 0))
                  {
	                  qrs_detected = true;
                  }
                  --qr1;
               }
               ++qr1;
	            qrs_time1 = (qr1 * 1000) / SampleRate;

               qr2 = FloatOnsets[j] + 5;
               qrs_detected = false;
               while (!qrs_detected && (qr2 < (FloatOnsets[j+1] - weighting_parm)))
	            {
	               if ((filtered_resulting_signal[qr2] <= filtered_resulting_signal[qr2+1]) || (filtered_resulting_signal[qr2] <= 0 ))
	               {
                     qrs_detected = true;
                  }
                  ++qr2;
	            }
               --qr2;
	            qrs_time2 = (qr2*1000) / SampleRate;

               qrs_duration = qrs_duration + (qrs_time2 - qrs_time1);
               j++;
            }
            if (j > 1)
            {
               qrs_duration = qrs_duration / (j - 1);

               if (qrs_duration < HRV_MIN_QRS_DURATION)
               {
                  onset_error = "QRS duration too low, " + RoundIntToStr(qrs_duration);
                  result = false;
               }
            }
         }
         else
         {
            onset_error = "Not enough points, " + IntToStr(NofPoints);
            result = false;
         }
      }
   }


   if (opened_signal != NULL)
   {
      delete[] opened_signal;
   }

   if (closed_signal != NULL)
   {
      delete[] closed_signal;
   }

   if (resulting_signal != NULL)
   {
      delete[] resulting_signal;
   }
   if (signal_segment != NULL)
   {
      delete[] signal_segment;
   }
   if (filtered_resulting_signal != NULL)
   {
      delete[] filtered_resulting_signal;
   }
   if (index_threshold != NULL)
   {
      delete[] index_threshold;
   }

   return result;
}


//-----------------------------------------------------------------------------
//*****************************************************************************
bool THRVECGSignal::Erosion(int pb , float *pSignal, float *pErosion)
{
   float *Z ;
   Z= new float[(pb+3)*(MaxNofPoints + 1)];
   float *ZZ;
   ZZ= new float[pb+3];


   for (int i = 0; i <= pb; i++)
   {
      ZZ[i] = 0;
   }
   if (NofPoints <= (2*pb))
   {
      return false;
   }

   for (int i = 0; i < NofPoints; i++)
   {
      Z[i] = pSignal[i];
   }
   for (int i = 1; i <= pb;i++)
   {
      int ss=0;
      for (int j = (i * NofPoints); j<((i+1) * NofPoints); j++)
      {
         if (j< ((i+1) * NofPoints) -i)
         {
            Z[j] = pSignal[ss + i];
         }
         else
         {
            Z[j] = 0;
         }
         ss++;
      }
   }
   for (int j = 0; j < NofPoints; j++)
   {
      for (int i = 0; i <= pb; i++)
      {
         ZZ[i] = Z[(i*NofPoints) + j];
      }
      pErosion[j] = math_MinInArray(&ZZ[0], pb + 1);
      for (int i=0; i <= pb; i++)
      {
         ZZ[i] = 0;
      }
   }
   delete[] ZZ;
   delete[] Z;
   return true;
}


//-----------------------------------------------------------------------------
//*****************************************************************************
bool THRVECGSignal::Dilation(int pb, float *pSignal, float *pDilated)
{
   int k;
   float *Z;
   Z = new float[(pb+3)*(MaxNofPoints + 1)];
   float *ZZ;
   ZZ= new float[pb+3];

   if (NofPoints <= (2*pb))
   {
      return false;
   }

   for (int i = 0; i < NofPoints; i++)
   {
      Z[i] = pSignal[i];
   }
   for (int i = 1; i <= pb;i++)
   {
      k = 0;
      for (int j = (i * NofPoints); j < ((i+1)*NofPoints); j++)
      {
         if (j <= (i*(NofPoints + 1)))
         {
            Z[j] = 0;
         }
         else
         {
            Z[j]= pSignal[k];
            k++;
         }
      }
   }
   for (int j = 0; j < NofPoints; j++)
   {
      for (int i = 0; i <= pb;i++)
      {
         ZZ[i]= Z[(i*NofPoints) + j];
      }
      pDilated[j]= math_MaxInArray(&ZZ[0], pb+1);
      for (int i = 0; i <= pb; i++)
      {
         ZZ[i]=0;
      }
   }
   delete[] ZZ;
   delete[] Z;
   return true;
}


//-----------------------------------------------------------------------------
//*****************************************************************************
void THRVECGSignal::Openingn(int pb, float *pSignal, float *pOpened)
{
   float *erosion_signal;

   erosion_signal = new float[MaxNofPoints + 1];

   Erosion(pb, &pSignal[0], &erosion_signal[0]);
   Dilation(pb, &erosion_signal[0], &pOpened[0]);
   delete[] erosion_signal;
}


//-----------------------------------------------------------------------------
//*****************************************************************************
void THRVECGSignal::Closingn(int pb, float *pOpened, float *pClosed)
{
   float *dilated_signal;

   dilated_signal = new float[MaxNofPoints + 1];
   Dilation(pb, &pOpened[0], &dilated_signal[0]);
   Erosion(pb, &dilated_signal[0], &pClosed[0]);
   delete[] dilated_signal;
}

THRV::THRV()
{
  // Allocate Signals
  ecg.Allocate(HRV_MAX_CAPTURE_TIME * HRV_MAX_ECG_SAMPLE_RATE, SIGNAL_ECG_MAX_ONSETS);
  ecg_signal_buffer = new float[HRV_MAX_ECG_SAMPLE_RATE * HRV_MAX_CAPTURE_TIME];
  ecg_signal = new short int[HRV_SAVED_ECG_LENGTH];

  Initialise(HRV_MAX_ECG_SAMPLE_RATE);
}

THRV::~THRV()
{
   if (ecg_signal_buffer != NULL)
   {
      delete ecg_signal_buffer;
   }
   if (ecg_signal != NULL)
   {
      delete ecg_signal;
   }
}

void THRV::Initialise(const int pECGSampleRate)
{
   ecg_signal_buffer_len = 0;
   ecg_signal_length = 0;
   PulseCounter=0;
   PulsesInSession = 0;
   StartPulse = 0;
   EndPulse = 0;
   number_rejected_rtor_tot = 0;
   NofOnsets = 0;
   SumRtoR = 0;
   TDateTime dt = EncodeTime(0, 0, 0, 0);
   time_elapsed = dt;
   ecg_sample_rate = pECGSampleRate;
   ecg.Initialise(pECGSampleRate);

   SetDefaults(pECGSampleRate);
   TMeasure::SetSampleRate(pECGSampleRate);
}

void THRV::SetDefaults(const int pECGSampleRate)
{
   for (int np = 0; np < HRV_MAX_NUM_PULSES_IN_SWEEP; np++)
   {
      rtor_intervals[np]= DEFAULT_VALUE;
   }

   for (int np1 = 0; np1 < HRV_MAX_REJECTED_PULSES; np1++)
   {
      index_rejected_rtor[np1] = DEFAULT_VALUE;
   }
   number_rejected_rtor = 0;
   nof_ecg_pulses = 0;
}

void  THRV::PrepareToCaptureSignal(void)
{
   ecg.PrepareToCapture();
}

bool THRV::Calculate(void)
{
   if (ValidateBeforeCalculate()==false)
      return false;

   DateTime = StartTime + time_elapsed;
   DetermineUnusualBeats();
   RefineRtoR();
   EndPulse = PulsesInSession;
   if (hrv_time->Calculate() == false)
   {
      return false;
   }
   if (hrv_frequency->Calculate() == false)
   {
      return false;
   }
   return true;
}

bool THRV::CalculatePulses(void)
{
   bool calc = false;

   SaveToFile();
   SaveECG();

   ecg.Append(&ecg_signal_buffer[0], ecg_signal_buffer_len);

   SetDefaults(ecg_sample_rate);
   if (!(ecg.ValidateSignal(5 * ecg_sample_rate)))
   {
      error_string = "Validate ECG signal failed";
      log_write(error_string);
      return calc;
   }

   if (ecg.NofPoints > 0)
   {
      if (ecg.FindOnsets(1))
      {
         if (PulseCalc())
         {
            calc = true;
         }
         else
         {
            calc = false;

            // If there is an error, ignore the last screen
            ecg_signal_length = ecg_signal_length - HRV_SAVED_ECG_RESOLUTION;
         }
      }
      else
      {
         error_string = ecg.onset_error;
         log_write(error_string);
         calc = false;
      }
   }
   else
   {
      error_string = "No ECG points";
      log_write(error_string);
      calc = false;
   }

   if (calc)
   {
      if ( (ecg.NofPoints-ecg.FloatOnsets[ecg.NofOnsets - 2])<(1024 * 4))
      {
         int indE=0;
         for (int i= (int)ecg.FloatOnsets[ecg.NofOnsets -2];
            i < ecg.NofPoints; i++)
         {
             ecg_signal_buffer[indE]=ecg.Signal[i];
             indE++;
         }
         ecg_signal_buffer_len = indE;
         NofOnsets = ecg.NofOnsets - 1;
      }
      else
      {
        error_string = "Not enough pulses";
        log_write(error_string);
        calc = false;
      }
   }
   else
   {
      calc = false;
   }

   return calc;
}


bool  THRV::PulseCalc(void)
{
   number_rejected_rtor = 0;
   AnsiString S;
   int start;
   bool ret= true;
   nof_ecg_pulses = 0;
   int i;
   bool too_many_rejected_pulses = false;

   for (int i=0; i < ecg.NofOnsets - 1; i++)
   {
      rtor_intervals[nof_ecg_pulses]= (ecg.FloatOnsets[i+1] - ecg.FloatOnsets[i])*1000 / ecg.SampleRate;
      SumRtoR = SumRtoR + rtor_intervals[nof_ecg_pulses];
      ++nof_ecg_pulses;
   }
   AveRtoR = math_MeanInArray(&rtor_intervals[0], nof_ecg_pulses);
   if (AveRtoR)
   {
      AveHeartRate = (60.0 *1000/ (AveRtoR));
   }


   if (PulsesInSession == 0)
   {
      start = 1;
      rtor_intervals_prev = rtor_intervals[0];
      number_rejected_rtor_tot = 0;
   }
   else
   {
      start = 0;
   }
   i = start;
   while (!too_many_rejected_pulses && i < nof_ecg_pulses)
   {
      if ((rtor_intervals[i] > (1.5 * rtor_intervals_prev)) || (rtor_intervals[i] < (0.5 * rtor_intervals_prev)))
      {
         index_rejected_rtor[number_rejected_rtor_tot]= (short int)(i + PulsesInSession);
         number_rejected_rtor_tot++;
         number_rejected_rtor++;
         if (number_rejected_rtor_tot > HRV_MAX_REJECTED_PULSES)
         {
            too_many_rejected_pulses = true;
         }
      }
      rtor_intervals_prev = rtor_intervals[i];
      i++;
   }
   PulsesInSession += nof_ecg_pulses;

   if (!too_many_rejected_pulses)
   {
      if (nof_ecg_pulses >= 1)
      {
         if ((AveHeartRate < SIGNAL_ECG_MIN_HEART_RATE)||(AveHeartRate > SIGNAL_ECG_MAX_HEART_RATE))
         {
            error_string = "Heart rate out of range, " + RoundIntToStr(AveHeartRate);
            log_write(error_string);
            ret = false;
         }
         for (int i = start; i < nof_ecg_pulses; i++)
         {
            // To convert the length from msec to sec
            if (rtor_intervals[i]> (SIGNAL_MAX_APPEND_LEN * 1000 / ecg.SampleRate))
            {
               error_string = "R to R interval too large, " + RoundIntToStr(rtor_intervals[i]);
               log_write(error_string);
               ret = false;
               break;
            }
         }
         if (PulsesInSession < SIGNAL_ECG_MIN_ONSETS || PulsesInSession > HRV_MAX_NUMBER_OF_PULSES)
         {
            error_string = LoadStr(MSG_HRV_PULSES_OUT) + IntToStr(PulsesInSession);
            log_write(error_string);
            ret = false;
         }
      }
      if (ret == false)
      {
         PulsesInSession = PulsesInSession - nof_ecg_pulses;
      }
   }
   else
   {
      PulsesInSession = PulsesInSession - nof_ecg_pulses;
      ret = false;
      error_string = "Too many rejected R-R intervals, " +IntToStr(PulsesInSession);
      log_write(error_string);
   }
   if (ret == true)
   {
      int count=0;
      for (int k = PulseCounter; k < PulsesInSession; k++)
      {
         RtoR_raw[k] = rtor_intervals[count];
         count++;
      }
      PulseCounter = PulsesInSession;
   }

   return (ret);
}
//--------------------------------------------------------------------------
//--------------------------------------------------------------------------
void  THRV::DetermineUnusualBeats(void)
{
   int sum, LenAve, Start;
   float AveRtoR;
   int n = 0;
   bool hi_low;
   bool valid_rtor = false;
   bool too_many_rejected_pulses = false;


   number_rejected_rtor_tot = 0;

   while (n < PulsesInSession && !valid_rtor && !too_many_rejected_pulses)
   {
      if ((RtoR_raw[n] < MIN_RTOR_INTERVAL) || (RtoR_raw[n] > MAX_RTOR_INTERVAL))
      {
         index_rejected_rtor[number_rejected_rtor_tot] = n;
         number_rejected_rtor_tot++;
         if (number_rejected_rtor_tot > HRV_MAX_REJECTED_PULSES)
         {
            too_many_rejected_pulses = true;
         }
      }
      else
      {
         Start = n;
         valid_rtor = true;
      }
      ++n;
   }

   if (valid_rtor)
   {
      int k = Start+1;
      while ( k < PulsesInSession && !too_many_rejected_pulses)
      {
         if ((k-Start)>=3)
         {
            sum=0;
            LenAve=0;
            for (int km = k-3; km < k; km++)
            {

               if (number_rejected_rtor_tot>0)
               {
                     for (int kl=0; kl<number_rejected_rtor_tot;kl++)
                     {
                        if (km==index_rejected_rtor[kl])
                        {
                           hi_low=true;
                           break;
                        }
                        else
                        {
                           hi_low=false;
                        }
                     }
                     if (!hi_low)
                     {
                        sum=sum+RtoR_raw[km];
                        LenAve++;
                     }
               }
               else
               {
                  sum=sum+RtoR_raw[km];
                  LenAve++;
               }
            }
            if (LenAve!=0)
            {
                  AveRtoR = sum / LenAve;
            }
            else
            {
               AveRtoR = RtoR_raw[k-1];
            }
         }
         else
         {

            if (( RtoR_raw[k-1]<MIN_RTOR_INTERVAL)||(RtoR_raw[k-1]>MAX_RTOR_INTERVAL))
            {
               AveRtoR = RtoR_raw[k-2];
            }
            else
            {
               AveRtoR = RtoR_raw[k-1];
            }
         }

         if ((RtoR_raw[k] > (1.6 * AveRtoR)) ||
            (RtoR_raw[k] < (0.5*AveRtoR)))
         {
            index_rejected_rtor[number_rejected_rtor_tot] = (short int)k;
            number_rejected_rtor_tot++;
            if (number_rejected_rtor_tot > HRV_MAX_REJECTED_PULSES)
            {
               too_many_rejected_pulses = true;
            }
         }
         k++;
      }
   }
   return;
}
//--------------------------------------------------------------------------
//--------------------------------------------------------------------------
void THRV::RefineRtoR(void)
{
 int Count;
 float sum;
 bool hi_lo;
 if(number_rejected_rtor_tot>0)
 {
    Count=0;
    sum=0;
    for (int i = 0; i < PulsesInSession; i++)
    {
       hi_lo=true;
       for(int k=0; k < number_rejected_rtor_tot;k++)
       {
          if (i == index_rejected_rtor[k])
          {
             hi_lo = false;
             break;
          }
       }
       if (!hi_lo)
       {
          sum=sum+RtoR_raw[i];
          Time_raw[i]=sum/1000;
       }
       else
       {
          sum=sum+RtoR_raw[i];
          RtoR_raw_refined[Count]=RtoR_raw[i];
          Time_raw_refined[Count]=sum/1000;
          Time_raw[i]=sum/1000;
          Count++;
       }

    }
 }
 else
 {
    Count=0;
    sum=0;
    for (int i=0; i<PulsesInSession; i++)
    {
       sum=sum+RtoR_raw[i];
       RtoR_raw_refined[Count]=RtoR_raw[i];
       Time_raw_refined[Count]=sum/1000;
       Time_raw[i]=sum/1000;
       Count++;
    }
 }
   PulsesInSession_refined = Count;
}
//--------------------------------------------------------------------------

bool THRV::ValidateBeforeCalculate()
{
   Word hour, min, sec, msec;
   int length;
   bool ret = true;

   if (PulsesInSession < SIGNAL_ECG_MIN_ONSETS || PulsesInSession > HRV_MAX_NUMBER_OF_PULSES)
   {
      MsgBox(TERROR,
           GetCurrentHRVMeasureDetails(),
           MSG_VALIDATION_ERROR, MSG_HRV_PULSES_OUT,
           LoadStr(MSG_HRV_PULSES_OUT) + IntToStr(PulsesInSession));
      ret = false;
   }

   for (int i=0; i < PulsesInSession; i++)
   {
      if (RtoR_raw[i] <= 0)
      {
         MsgBox(TERROR, GetCurrentHRVMeasureDetails(), MSG_VALIDATION_ERROR, MSG_HRV_NEG_RTOR,
             LoadStr(MSG_HRV_NEG_RTOR) + IntToStr(i));
         ret = false;
         break;
      }
   }

   if (number_rejected_rtor_tot < 0 || number_rejected_rtor_tot > HRV_MAX_REJECTED_PULSES)
   {
      MsgBox(TERROR,
           GetCurrentHRVMeasureDetails(),
           MSG_VALIDATION_ERROR, MSG_HRV_REJECTED_OUT,
           LoadStr(MSG_HRV_REJECTED_OUT) + IntToStr(number_rejected_rtor_tot));
      ret = false;
   }

   for (int i=0; i < number_rejected_rtor_tot; i++)
   {
      if (index_rejected_rtor[i] < 0)
      {
         MsgBox(TERROR,
              GetCurrentHRVMeasureDetails(),
              MSG_VALIDATION_ERROR, MSG_HRV_REJECTED_INDEX_OUT,
              LoadStr(MSG_HRV_REJECTED_INDEX_OUT) + IntToStr(i));
         ret = false;
         break;
      }
   }

   DecodeTime(time_elapsed, hour, min, sec, msec);
   length = 60*hour + min;
   if (length < 0 || length > HRV_MAX_SESSION_TIME)
   {
      MsgBox(TERROR,
           GetCurrentHRVMeasureDetails(),
           MSG_VALIDATION_ERROR, MSG_HRV_TIME_OUT,
           LoadStr(MSG_HRV_TIME_OUT) + IntToStr(length) + " minutes.");
      ret = false;
   }

   for (int i=0; i < ecg_signal_length; i++)
   {
      if (ecg_signal[i] <= 0)
      {
         MsgBox(TWARNING, GetCurrentHRVMeasureDetails(), MSG_VALIDATION_ERROR, MSG_HRV_NEG_ECG,
             LoadStr(MSG_HRV_NEG_ECG) + IntToStr(i));
         break;
      }
   }

   // Only validate the pressures if a value has been entered (Version 9.0)
  if (Sp == 0 && Dp == 0 && MeanP == 0)
  {
      ValidateSpDp = false;
  }
  else
  {
      ValidateSpDp = true;
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

   return ret;
}

bool THRV::ValidateBeforeStore()
{
   bool ret = true;                  

   if (TMeasure::ValidateBeforeStore() == false)
   {
      ret = false;
   }

   if (StartPulse < 0)
   {
      MsgBox(TERROR, GetCurrentHRVMeasureDetails(), MSG_VALIDATION_ERROR, MSG_HRV_NEG_START_PULSE);
      ret = false;
   }
   
   if ((EndPulse > PulsesInSession) || ((EndPulse - StartPulse) < SIGNAL_ECG_MIN_ONSETS))
   {
      MsgBox(TERROR,
           GetCurrentHRVMeasureDetails(),
           MSG_VALIDATION_ERROR, MSG_HRV_END_PULSE_OUT,
           LoadStr(MSG_HRV_END_PULSE_OUT) + IntToStr(EndPulse));
      ret = false;
   }

   if (hrv_time->ValidateBeforeStore() == false)
   {
      ret = false;
   }

   if (hrv_frequency->ValidateBeforeStore() == false)
   {
      ret = false;
   }
   return ret;
}

bool THRV::Store(TDataSet* pDataSet, bool pRewriteKeyFields, bool pRewriteDate)
{
   bool success = false;

   if (pDataSet->CanModify == false)
   {
      MsgBox_show(TERROR,
                  MSG_DBREADWRITE_ERROR,
                  LoadStr(MSG_NO_STORE),
                  MSG_NO_STORE,
                  LoadStr(MSG_NO_STORE) +GetCurrentHRVMeasureDetails());
      return success;
   }
   // Validation
   if (ValidateBeforeStore() == false)
   {
      return success;
   }
   if (TMeasure::StoreAccess(pDataSet, pRewriteKeyFields, pRewriteDate) == true)
   {
      try
      {
         // This is a fix to limit the precision of the DateTime field and allow equality tests, eg. Locate
         pDataSet->FieldByName(MHRV_START_TIME)->AsDateTime = StrToDateTime(DateTimeToStr(StartTime));

         pDataSet->FieldByName(MHRV_MEASURE_TYPE)->AsInteger = (int) MeasureType;

         pDataSet->FieldByName(MHRV_RTOR_INTERVALS)->Value =
          PackFloatToString(RtoR_raw, PulsesInSession);

         pDataSet->FieldByName(MHRV_UNUSUAL_BEATS)->Value =
          PackToString(index_rejected_rtor, number_rejected_rtor_tot);

         pDataSet->FieldByName(MHRV_ECG)->Value =
          PackToString(ecg_signal, ecg_signal_length);

         pDataSet->FieldByName(MHRV_NUMBER_PULSES)->AsInteger = PulsesInSession;

         pDataSet->FieldByName(MHRV_START_PULSE)->AsInteger = StartPulse;

         pDataSet->FieldByName(MHRV_END_PULSE)->AsInteger = EndPulse;

         pDataSet->FieldByName(MHRV_SIMULATION)->AsInteger = Simulation;
         success = true;
      }
      catch (Exception &exception)
      {
         MsgBox_show(TERROR,
                     MSG_EXCEPTION,
                     LoadStr(MSG_STORE_ERROR),
                     MSG_STORE_ERROR,
                     LoadStr(MSG_STORE_ERROR) +GetCurrentMeasureDetails() +exception.Message);
      }
   }


   if (success)
   {
      if (hrv_time->Store(pDataSet) && hrv_frequency->Store(pDataSet))
      {
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
                        LoadStr(MSG_POST_ERROR) +exception.Message);
            success = false;
         }
      }
      else
      {
         success = false;
      }
   }

   if (success == false)
   {
      pDataSet->Cancel();
   }
   return success;
}

bool THRV::Populate(TDataSet* pDataSet)
{
   if (TMeasure::PopulateAccess(pDataSet) == false)
   {
      return false;
   }

   if (pDataSet->RecordCount <= 0)
   {
      Initialise(1024);
      System_ID = patient_get_system_id();
      Patient_No = patient_get_number();
      Study_ID = patient_get_study_id();
      return false; //true
   }

   System_ID   = pDataSet->FieldByName(MPW_SYSTEM_ID)->AsString;
   Study_ID    = pDataSet->FieldByName(MPW_STUDY_ID)->AsString;
   Patient_No  = pDataSet->FieldByName(MPW_PATIENT_NO)->AsInteger;

   DateTime    = pDataSet->FieldByName(MPW_DATETIME)->AsDateTime;

   try
   {
      // PickUp Arrays
       int NofBytes;

       NofBytes = min((int)(pDataSet->FieldByName(MHRV_RTOR_INTERVALS)->AsString.Length()),
                           (int)(HRV_MAX_NUMBER_OF_PULSES*sizeof(float)));
       if (UnpackFloatFromString(RtoR_raw, pDataSet->FieldByName(MHRV_RTOR_INTERVALS)->AsString, NofBytes)==false)
       {
          return false;
       }

       // Extract Signal
       NofBytes = min((int)(pDataSet->FieldByName(MHRV_UNUSUAL_BEATS)->AsString.Length()),
                      (int)(HRV_MAX_REJECTED_PULSES*sizeof(short int)));
       if (NofBytes > 0)
       {
          if (UnpackFromString(index_rejected_rtor, pDataSet->FieldByName(MHRV_UNUSUAL_BEATS)->AsString, NofBytes)==false)
          {
             return false;
          }
          number_rejected_rtor_tot = NofBytes/sizeof(short int);
       }
       else
       {
          number_rejected_rtor_tot = 0;
       }

       // This is not an error condition
       NofBytes = min((int)(pDataSet->FieldByName(MHRV_ECG)->AsString.Length()),
                      (int)(HRV_SAVED_ECG_LENGTH*sizeof(short int)));
       if (UnpackFromString(ecg_signal, pDataSet->FieldByName(MHRV_ECG)->AsString, NofBytes) == false)
       {
          ;
       }
       else
       {
          ;
       }
       ecg_signal_length = NofBytes/sizeof(short int);

       MeasureType = (HRV_MEASURE_TYPE) pDataSet->FieldByName(MHRV_MEASURE_TYPE)->AsInteger;
       StartTime = pDataSet->FieldByName(MHRV_START_TIME)->AsDateTime;    
       PulsesInSession = pDataSet->FieldByName(MHRV_NUMBER_PULSES)->AsInteger;
       StartPulse = pDataSet->FieldByName(MHRV_START_PULSE)->AsInteger;
       EndPulse = pDataSet->FieldByName(MHRV_END_PULSE)->AsInteger;
       Simulation = pDataSet->FieldByName(MHRV_SIMULATION)->AsInteger;
         
       RefineRtoR();
       hrv_time->Populate(pDataSet);
       hrv_frequency->Populate(pDataSet);
     }
     catch (Exception &exception)
     {
        MsgBox(TERROR, GetCurrentMeasureDetails(), MSG_DBREADWRITE_ERROR, MSG_ERR_READDB,
               LoadStr(MSG_ERR_READDB) +exception.Message);
        return false;
     }
     return true;
}

bool THRV::SaveToFile()
{
   // Validation
   if (lFileHandle <= 0)
   {
     return false;
   }

  // Printing arrays
  for (int i=0; i<ecg.NofPoints; i++)
  {
    String lOut = RoundIntToStr(ecg.Signal[i]) + "\r\n";
    FileWrite(lFileHandle, lOut.c_str(), lOut.Length());
  }

  return true;
}

bool THRV::SaveECG()
{
   // If there is not enough space in the ecg_signal array, then shift the
   // signal back to allow the current sweep to be stored at the end
   if (ecg_signal_length + HRV_SAVED_ECG_RESOLUTION > HRV_SAVED_ECG_LENGTH)
   {
      for (int j=0; j<HRV_SAVED_ECG_LENGTH - HRV_SAVED_ECG_RESOLUTION; j++)
      {
         ecg_signal[j] = ecg_signal[j + HRV_SAVED_ECG_RESOLUTION];
      }
      ecg_signal_length = ecg_signal_length - HRV_SAVED_ECG_RESOLUTION;
   }

   // Store every 8th ecg point at the end of the ecg_signal array
   for (int i=0; i<ecg.NofPoints; i=i+8)
   {
      ecg_signal[ecg_signal_length] = (short int)ecg.Signal[i];
      ecg_signal_length++;
   }

   return true;
}

bool THRV::ValidateSpDpMp()
{
   // Must overide the function because ValidateSpDpMp is protected
   return TMeasure::ValidateSpDpMp();
}

bool THRV::ValidateHtWt()
{
   // Must overide the function because ValidateHtWt is protected
   return TMeasure::ValidateHtWt();
}

bool THRV::ValidateMeasureType()
{
   switch (MeasureType)
   {
      case HRV_NORMAL:
         return true;

      case HRV_VALSALVA:
         return true;

      case HRV_STAND:
         return true;

      default:
         return false;
   }
}

//------------------------------------------------------------
bool THRV::ExportPrintTitle(TDataSet* pDataSet, String &pOut)
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
    pOut = pOut + pDataSet->FieldByName(MHRV_START_TIME)->DisplayName + "\t";
    pOut = pOut + pDataSet->FieldByName(MHRV_MEASURE_TYPE)->DisplayName + "\t";
    pOut = pOut + pDataSet->FieldByName(MHRV_NUMBER_PULSES)->DisplayName + "\t";
    pOut = pOut + pDataSet->FieldByName(MHRV_START_PULSE)->DisplayName + "\t";
    pOut = pOut + pDataSet->FieldByName(MHRV_END_PULSE)->DisplayName + "\t";
  }
  catch (Exception &exception)
  {
    MsgBox(TERROR, GetCurrentHRVMeasureDetails(), MSG_EXPORT_ERROR, MSG_EXPORT_EXCEPTION,  LoadStr(MSG_EXPORT_EXCEPTION) + exception.Message);
    return false;
  }
  // Print Time and Frequency
  bool ret1 = hrv_time->ExportPrintTitle(pDataSet, pOut);
  bool ret2 = hrv_frequency->ExportPrintTitle(pDataSet, pOut);
  bool ret = ret1 & ret2;
  // Final delimiter
  pOut.Delete(pOut.LastDelimiter("\t"),1);
  // return at success
  return ret;
}

//------------------------------------------------------------
bool THRV::Export(String &pOut)
{
  // Actual printing properties

  // Export Measure class
  if (TMeasure::Export(pOut)==false)
  {
    return false;
  }

  // Export specific properties
  pOut = pOut + StartTime.FormatString("dd/mm/yyyy hh:nn:ss") + "\t";
  pOut = pOut + IntToStr((int)MeasureType) + "\t";
  pOut = pOut + IntToStr(PulsesInSession) + "\t";
  pOut = pOut + IntToStr(StartPulse) + "\t";
  pOut = pOut + IntToStr(EndPulse) + "\t";

  // Export Time and Frequency
  bool ret1 = hrv_time->Export(pOut);
  bool ret2 = hrv_frequency->Export(pOut);
  bool ret = ret1 & ret2;
  // Final delimiter
  pOut.Delete(pOut.LastDelimiter("\t"),1);
  // return at success
  return ret;
}

bool THRV::ExportArrays(int pFileHandle)
{
  if (pFileHandle <= 0)
    return false;
  // Printing title for Arrays
  String lOut = "\r\nR to R Intervals\r\n";
  FileWrite(pFileHandle, lOut.c_str(), lOut.Length());

  // Printing arrays
  int lMaxSize = PulsesInSession;


  for (int i = 0; i < lMaxSize; i++)
  {
    lOut = "";
    if (i < PulsesInSession)
    {
      lOut = lOut + FormatFloat("0", RtoR_raw[i]);
    }
    /*
    if (i < number_rejected_rtor_tot)
    {
      lOut = lOut + "\t" + IntToStr(index_rejected_rtor[i]);
    }
    else
    {
      lOut = lOut + "\t";
    }
    if (i < MAX_HISTOGRAM_LENGTH)
    {
      lOut = lOut + "\t" + IntToStr(hrv_time->RtoR_histogram[i]);
    }
    else
    {
      lOut = lOut + "\t";
    }
    if (i < hrv_frequency->number_of_points_spectrum)
    {
      lOut = lOut + "\t" + FormatFloat("0.00", hrv_frequency->Power_Spectrum[i]);
      lOut = lOut + "\t" + FormatFloat("0.000", hrv_frequency->Frequency[i]);
    }
    */
    lOut = lOut + "\r\n";
    FileWrite(pFileHandle, lOut.c_str(), lOut.Length());
  }
  return true;
}
