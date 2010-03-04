//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include <math.h>

#include <meas/pubserv.h>
#include <msg/pubserv.h>
#include <log/pubserv.h>
#include "hrvclass.h"
#include "hrvtime.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)

THRVTime::THRVTime()
{
  Initialise();
}

THRVTime::~THRVTime()
{

}

void THRVTime::Initialise()
{
   hrv = meas_get_current_hrv();

   RtoR_mean = 0;
   RtoR_max = 0;
   RtoR_min = 0;
   RtoR_range = 0;
   RtoR_SD = 0;
   NN50 = 0;
   PNN50 = 0;
   RMS_SD = 0;
   RtoR_mode = 0;
   RtoR_mode_frequency = 0;
   HRV_index = 0;
   rounded_RtoR_max = 0;
   rounded_RtoR_min = 0;
   Triangular_index = 0;
   Segment_length = 5;
   No_of_segments = 0;
   SDANN = 0;
   SDNN = 0;
   Valsalva_high = 0;
   Valsalva_low = 0;
   Valsalva_ratio = 0;
   Stand_high = 0;
   Stand_low = 0;
   Stand_ratio = 0;

   SetDefaults();

}

void THRVTime::SetDefaults()
{
   for (int i = 0; i < MAX_HISTOGRAM_LENGTH; i++)
   {
      RtoR_histogram[i]= 0;
   }
   for (int i = 0; i < HRV_MAX_NUMBER_OF_PULSES; i++)
   {
      RtoR_differences[i]= DEFAULT_VALUE;
   }
}


bool THRVTime::Calculate()
{
   Initialise();
   int mode_index = 0;
   
   // Use math functions to calculate statistical parameters
   RtoR_mean = math_MeanInArray (hrv->RtoR_raw_refined, hrv->PulsesInSession_refined);
   if (math_MinMaxInArray (hrv->RtoR_raw_refined, hrv->PulsesInSession_refined, RtoR_min, RtoR_max))
   {
      RtoR_max_min = RtoR_max/RtoR_min;
      RtoR_range = RtoR_max - RtoR_min;
      rounded_RtoR_max = math_Round(RtoR_max);
      rounded_RtoR_min = math_Round(RtoR_min);
      Triangular_index = rounded_RtoR_max - rounded_RtoR_min;
   }
   else
   {
      return false;
   }
   RtoR_SD = math_STDinArray(hrv->RtoR_raw_refined, hrv->PulsesInSession_refined);

   // Calculate RtoR interval parameters: NN50, PNN50 and RMS_SD
   if (FindIntervals())
   {
      PNN50 = (float)NN50/(hrv->PulsesInSession_refined-1)*100;
      RMS_SD = math_RMSinArray(RtoR_differences, hrv->PulsesInSession_refined - 1);
   }

   // Calculate histogram parameters such as the HRV index
   if (CreateHistogram())
   {
      if (math_IndexMaxInArray (RtoR_histogram, MAX_HISTOGRAM_LENGTH, mode_index, RtoR_mode_frequency))
      {
         RtoR_mode = mode_index*10 + 5;
         HRV_index = (float)hrv->PulsesInSession_refined/RtoR_mode_frequency;
      }
      else
      {
         return false;
      }
   }

   // Calculate Segmented data
   CreateSegments();

   // Calculate manoeuvre parameters
   switch (hrv->MeasureType)
   {
      case HRV_NORMAL:
         break;

      case HRV_VALSALVA:
         if (math_MaxAfterMinInArray (hrv->RtoR_raw_refined, hrv->PulsesInSession_refined, Valsalva_high, Valsalva_low))
         {
            Valsalva_high = 60*1000/Valsalva_high;
            Valsalva_low = 60*1000/Valsalva_low;
            Valsalva_ratio = Valsalva_high/Valsalva_low;
         }
         else
         {
            return false;
         }
         break;

      case HRV_STAND:
         if (CalculateStandManoeuvre())
         {
            Stand_high = 60*1000/Stand_high;
            Stand_low = 60*1000/Stand_low;
            Stand_ratio = Stand_high/Stand_low;
         }
         else
         {
            return false;
         }
         break;
   }

   return true;
}

bool THRVTime::FindIntervals()
{
   // RtoR differences are the difference between successive RtoR values
   for (int i = 1; i < hrv->PulsesInSession_refined; i++)
   {
      RtoR_differences[i-1] = hrv->RtoR_raw_refined[i] - hrv->RtoR_raw_refined[i-1];

      // Count the number of intervals greater than 50ms
      if (fabs(RtoR_differences[i-1]) > 50)
      {
         NN50++;
      }
   }
   return true;
}

bool THRVTime::CreateHistogram()
{
   // Add the number of RtoR values within each 10ms period and store them in an
   // array, where the index represents the RtoR value
   int index;
   for (int i = 0; i < hrv->PulsesInSession_refined; i++)
   {
      index = floor(hrv->RtoR_raw_refined[i]/10);
      RtoR_histogram[index]++;
   }
   return true;
}

bool THRVTime::CreateSegments()
{
   int j = 0;
   bool success = false;
   Word hour, min, sec, msec;
   //TDateTime CaptureTime = hrv->DateTime - hrv->StartTime;

   DecodeTime(hrv->time_elapsed, hour, min, sec, msec);
   length = 60*hour + min;
   //length = hrv->Time_raw_refined[hrv->PulsesInSession_refined - 1];

   // Segmented data is only calculated if more than two segments are captured
   if (length >= 2*Segment_length)
   {
      segment_time = 60*Segment_length;
      for (int i = 0; i < hrv->PulsesInSession_refined; i++)
      {
         // Populate the segment array
         if (hrv->Time_raw_refined[i] < segment_time)
         {
            segment[j] = hrv->RtoR_raw_refined[i];
            j++;
         }
         else
         {
            // At the end of each segment: Calculate intermediate values, restart
            // the segment array and increment the segment time and number
            SDNN = SDNN + math_STDinArray(segment, j);
            sdann[No_of_segments] = math_MeanInArray(segment, j);
            segment[0] = hrv->RtoR_raw_refined[i];
            j = 1;
            No_of_segments++;
            segment_time = segment_time + 60*Segment_length;
         }
      }
      // When elapsed time is a multiple of the segment length, the end of the
      // last segment will not be reached above. Thus the final segment is
      // calculated here.
      if (length/Segment_length == No_of_segments +1)
      {
         SDNN = SDNN + math_STDinArray(segment, j);
         sdann[No_of_segments] = math_MeanInArray(segment, j);
         No_of_segments++;
      }

      // Calculate the segment parameters if at least 2 segments have been calculated
      if (No_of_segments >=2)
      {
         SDNN = SDNN/No_of_segments;
         SDANN = math_STDinArray(sdann, No_of_segments);
         success = true;
      }
      else
      {
         // This ensures segmented data is not displayed
         No_of_segments = 0;
         log_write("Calculation of segments failed");
      }
   }
   return success;
}

bool THRVTime::CalculateStandManoeuvre()
{
   int   high_index = 4;
   int   low_index = 20;

   // Validation
   if (hrv->PulsesInSession_refined < 45)
   {
      return false;
   }

   // Find the shortest R to R interval around the 15th pulse (zero index)
   Stand_high = hrv->RtoR_raw_refined[4];
   for (int i = 5; i < 25; i++)
   {
      if (hrv->RtoR_raw_refined[i] < Stand_high)
      {
         Stand_high = hrv->RtoR_raw_refined[i];
         high_index = i;
      }
   }

   // Find the longest R to R interval around the 30th pulse after the high (zero index)
   if (high_index >= low_index)
   {
      low_index = high_index + 1;
   }
   Stand_low = hrv->RtoR_raw_refined[low_index];
   for (int i = low_index + 1; i < 45; i++)
   {
      if (hrv->RtoR_raw_refined[i] > Stand_low)
      {
         Stand_low = hrv->RtoR_raw_refined[i];
      }
   }

   // Return
   return true;
}

bool THRVTime::ValidateBeforeStore()
{
  bool ret = true;

  // Ensure histogram values are positive
  for (int i=0; i < MAX_HISTOGRAM_LENGTH; i++)
  {
    if (RtoR_histogram[i]<0)
    {
      MsgBox(TERROR, GetCurrentHRVMeasureDetails(), MSG_VALIDATION_ERROR, MSG_HRV_NEG_HISTOGRAM);
      ret = false;
      break;
    }
  }

  // Check mean within maximum range
  if (RtoR_mean < MIN_RTOR_INTERVAL || RtoR_mean > MAX_RTOR_INTERVAL)
  {
    MsgBox(TERROR,
           GetCurrentHRVMeasureDetails(),
           MSG_VALIDATION_ERROR, MSG_HRV_MEAN_OUT,
           LoadStr(MSG_HRV_MEAN_OUT) + RoundIntToStr(RtoR_mean));
    ret = false;
  }

  // Validate maximum
  if (RtoR_max > MAX_RTOR_INTERVAL)
  {
    MsgBox(TERROR,
           GetCurrentHRVMeasureDetails(),
           MSG_VALIDATION_ERROR, MSG_HRV_MAX_OUT,
           LoadStr(MSG_HRV_MAX_OUT) + RoundIntToStr(RtoR_max));
    ret = false;
  }

  // Validate maximum
  if (RtoR_min < MIN_RTOR_INTERVAL)
  {
    MsgBox(TERROR,
           GetCurrentHRVMeasureDetails(),
           MSG_VALIDATION_ERROR, MSG_HRV_MIN_OUT,
           LoadStr(MSG_HRV_MIN_OUT) + RoundIntToStr(RtoR_min));
    ret = false;
  }

  // Check max/min ratio within maximum range
  if (RtoR_max_min < 1 || RtoR_max_min > MAX_RTOR_INTERVAL/MIN_RTOR_INTERVAL)
  {
    MsgBox(TERROR,
           GetCurrentHRVMeasureDetails(),
           MSG_VALIDATION_ERROR, MSG_HRV_MAX_MIN_OUT,
           LoadStr(MSG_HRV_MAX_MIN_OUT) + RoundIntToStr(RtoR_max_min));
    ret = false;
  }

  // Validate range
  if (RtoR_range < 0 || RtoR_range > MAX_RTOR_INTERVAL - MIN_RTOR_INTERVAL)
  {
    MsgBox(TERROR,
           GetCurrentHRVMeasureDetails(),
           MSG_VALIDATION_ERROR, MSG_HRV_RANGE_OUT,
           LoadStr(MSG_HRV_RANGE_OUT) + RoundIntToStr(RtoR_range));
    ret = false;
  }

  // Check Standard Deviation is positive
  if (RtoR_SD < 0)
  {
     MsgBox(TERROR, GetCurrentHRVMeasureDetails(), MSG_VALIDATION_ERROR, MSG_HRV_NEG_SD);
     ret = false;
  }

  // Check NN50 is positive
  if (NN50 < 0)
  {
     MsgBox(TERROR, GetCurrentHRVMeasureDetails(), MSG_VALIDATION_ERROR, MSG_HRV_NEG_NN50);
     ret = false;
  }

  // Check PNN50 is a valid percent
  if (PNN50 < 0 || PNN50 > 100)
  {
     MsgBox(TERROR, GetCurrentHRVMeasureDetails(), MSG_VALIDATION_ERROR, MSG_HRV_PNN50_OUT);
     ret = false;
  }

  // Check RMS SDD is positive
  if (RMS_SD < 0)
  {
     MsgBox(TERROR, GetCurrentHRVMeasureDetails(), MSG_VALIDATION_ERROR, MSG_HRV_NEG_RMS_SD);
     ret = false;
  }

  // Validate HRV index
  if (HRV_index < 1 || HRV_index > hrv->PulsesInSession_refined)
  {
     MsgBox(TERROR,
           GetCurrentHRVMeasureDetails(),
           MSG_VALIDATION_ERROR, MSG_HRV_INDEX_OUT,
           LoadStr(MSG_HRV_INDEX_OUT) + RoundIntToStr(HRV_index));
     ret = false;
  }

  // Validate Triangular index
  if (Triangular_index < 0 || Triangular_index > MAX_RTOR_INTERVAL - MIN_RTOR_INTERVAL)
  {
    MsgBox(TERROR,
           GetCurrentHRVMeasureDetails(),
           MSG_VALIDATION_ERROR, MSG_HRV_TRIANGULAR_INDEX_OUT,
           LoadStr(MSG_HRV_TRIANGULAR_INDEX_OUT) + IntToStr(Triangular_index));
     ret = false;
  }

  // Check SDANN is positive
  if (SDANN < 0)
  {
     MsgBox(TERROR, GetCurrentHRVMeasureDetails(), MSG_VALIDATION_ERROR, MSG_HRV_NEG_SDANN);
     ret = false;
  }

  // Check SDNN is positive
  if (SDNN < 0)
  {
     MsgBox(TERROR, GetCurrentHRVMeasureDetails(), MSG_VALIDATION_ERROR, MSG_HRV_NEG_SDNN);
     ret = false;
  }

  switch (hrv->MeasureType)
  {
      case HRV_NORMAL:
         break;

      case HRV_VALSALVA:
         // Validate valsalva high
         if (Valsalva_high > 60*1000/MIN_RTOR_INTERVAL)
         {
            MsgBox(TERROR,
                  GetCurrentHRVMeasureDetails(),
                  MSG_VALIDATION_ERROR, MSG_HRV_VALSALVA_HIGH,
                  LoadStr(MSG_HRV_VALSALVA_HIGH) + FormatFloat("0.0", Valsalva_high));
            ret = false;
         }

         // Validate valsalva low
         if (Valsalva_low < 60*1000/MAX_RTOR_INTERVAL)
         {
            MsgBox(TERROR,
                  GetCurrentHRVMeasureDetails(),
                  MSG_VALIDATION_ERROR, MSG_HRV_VALSALVA_LOW,
                  LoadStr(MSG_HRV_VALSALVA_LOW) + FormatFloat("0.0", Valsalva_low));
            ret = false;
         }

         // Check valsalva ratio within maximum range
         if (Valsalva_ratio < 1 || Valsalva_ratio > MAX_RTOR_INTERVAL/MIN_RTOR_INTERVAL)
         {
            MsgBox(TERROR,
                  GetCurrentHRVMeasureDetails(),
                  MSG_VALIDATION_ERROR, MSG_HRV_VALSALVA_RATIO,
                  LoadStr(MSG_HRV_VALSALVA_RATIO) + FormatFloat("0.00", Valsalva_ratio));
            ret = false;
         }
         break;

      case HRV_STAND:
         // Validate stand high
         if (Stand_high > 60*1000/MIN_RTOR_INTERVAL)
         {
            MsgBox(TERROR,
                  GetCurrentHRVMeasureDetails(),
                  MSG_VALIDATION_ERROR, MSG_HRV_STAND_HIGH,
                  LoadStr(MSG_HRV_STAND_HIGH) + FormatFloat("0.0", Stand_high));
            ret = false;
         }

         // Validate stand low
         if (Stand_low < 60*1000/MAX_RTOR_INTERVAL)
         {
            MsgBox(TERROR,
                  GetCurrentHRVMeasureDetails(),
                  MSG_VALIDATION_ERROR, MSG_HRV_STAND_LOW,
                  LoadStr(MSG_HRV_STAND_LOW) + FormatFloat("0.0", Stand_low));
            ret = false;
         }

         // Check stand ratio within maximum range
         if (Stand_ratio < 1 || Stand_ratio > MAX_RTOR_INTERVAL/MIN_RTOR_INTERVAL)
         {
            MsgBox(TERROR,
                  GetCurrentHRVMeasureDetails(),
                  MSG_VALIDATION_ERROR, MSG_HRV_STAND_RATIO,
                  LoadStr(MSG_HRV_STAND_RATIO) + FormatFloat("0.00", Stand_ratio));
            ret = false;
         }
         break;
  }
  return ret;
}

bool THRVTime::Store(TDataSet* pDataSet)
{
   try
   {
      pDataSet->FieldByName(MHRV_HISTOGRAM)->Value =
       PackToString(RtoR_histogram, MAX_HISTOGRAM_LENGTH);

      pDataSet->FieldByName(MHRV_MEAN)->AsFloat = RtoR_mean;
      pDataSet->FieldByName(MHRV_MAXIMUM)->AsFloat = RtoR_max;
      pDataSet->FieldByName(MHRV_MINIMUM)->AsFloat = RtoR_min;
      pDataSet->FieldByName(MHRV_MAX_MIN)->AsFloat = RtoR_max_min;
      pDataSet->FieldByName(MHRV_RANGE)->AsFloat = RtoR_range;
      pDataSet->FieldByName(MHRV_STANDARD_DEVIATION)->AsFloat = RtoR_SD;
      pDataSet->FieldByName(MHRV_MODE)->AsFloat = RtoR_mode;
      pDataSet->FieldByName(MHRV_NN50)->AsInteger = NN50;
      pDataSet->FieldByName(MHRV_PNN50)->AsFloat = PNN50;
      pDataSet->FieldByName(MHRV_RMS_SD)->AsFloat = RMS_SD;
      pDataSet->FieldByName(MHRV_HRV_INDEX)->AsFloat = HRV_index;
      pDataSet->FieldByName(MHRV_TRIANGULAR_INDEX)->AsInteger = Triangular_index;
      pDataSet->FieldByName(MHRV_SEGMENT_LENGTH)->AsInteger = Segment_length;
      pDataSet->FieldByName(MHRV_NUMBER_SEGMENTS)->AsInteger = No_of_segments;
      pDataSet->FieldByName(MHRV_SDANN)->AsFloat = SDANN;
      pDataSet->FieldByName(MHRV_SDNN)->AsFloat = SDNN;

      switch (hrv->MeasureType)
      {
         case HRV_NORMAL:
            break;

         case HRV_VALSALVA:
            pDataSet->FieldByName(MHRV_VALSALVA_HIGH)->AsFloat = Valsalva_high;
            pDataSet->FieldByName(MHRV_VALSALVA_LOW)->AsFloat = Valsalva_low;
            pDataSet->FieldByName(MHRV_VALSALVA_RATIO)->AsFloat = Valsalva_ratio;
            break;

         case HRV_STAND:
            pDataSet->FieldByName(MHRV_STAND_HIGH)->AsFloat = Stand_high;
            pDataSet->FieldByName(MHRV_STAND_LOW)->AsFloat = Stand_low;
            pDataSet->FieldByName(MHRV_STAND_RATIO)->AsFloat = Stand_ratio;
            break;
      }

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

bool THRVTime::Populate(TDataSet* pDataSet)
{
   try
   {
      // PickUp Arrays
      int NofBytes;

      NofBytes = min((int)(pDataSet->FieldByName(MHRV_HISTOGRAM)->AsString.Length()),
                     (int)(MAX_HISTOGRAM_LENGTH*sizeof(int)));
      if (UnpackFromString(RtoR_histogram, pDataSet->FieldByName(MHRV_HISTOGRAM)->AsString, NofBytes) == false)
      {
         return false;
      }

      RtoR_mean = pDataSet->FieldByName(MHRV_MEAN)->AsFloat;
      RtoR_max = pDataSet->FieldByName(MHRV_MAXIMUM)->AsFloat;
      RtoR_min = pDataSet->FieldByName(MHRV_MINIMUM)->AsFloat;
      RtoR_max_min = pDataSet->FieldByName(MHRV_MAX_MIN)->AsFloat;
      RtoR_range = pDataSet->FieldByName(MHRV_RANGE)->AsFloat;
      RtoR_SD = pDataSet->FieldByName(MHRV_STANDARD_DEVIATION)->AsFloat;
      RtoR_mode = pDataSet->FieldByName(MHRV_MODE)->AsFloat;
      NN50 = pDataSet->FieldByName(MHRV_NN50)->AsInteger;
      PNN50 = pDataSet->FieldByName(MHRV_PNN50)->AsFloat;
      RMS_SD = pDataSet->FieldByName(MHRV_RMS_SD)->AsFloat;
      HRV_index = pDataSet->FieldByName(MHRV_HRV_INDEX)->AsFloat;
      Triangular_index = pDataSet->FieldByName(MHRV_TRIANGULAR_INDEX)->AsInteger;
      Segment_length = pDataSet->FieldByName(MHRV_SEGMENT_LENGTH)->AsInteger;
      No_of_segments = pDataSet->FieldByName(MHRV_NUMBER_SEGMENTS)->AsInteger;
      SDANN = pDataSet->FieldByName(MHRV_SDANN)->AsFloat;
      SDNN = pDataSet->FieldByName(MHRV_SDNN)->AsFloat;
      Valsalva_high = pDataSet->FieldByName(MHRV_VALSALVA_HIGH)->AsFloat;
      Valsalva_low = pDataSet->FieldByName(MHRV_VALSALVA_LOW)->AsFloat;
      Valsalva_ratio = pDataSet->FieldByName(MHRV_VALSALVA_RATIO)->AsFloat;
      Stand_high = pDataSet->FieldByName(MHRV_STAND_HIGH)->AsFloat;
      Stand_low = pDataSet->FieldByName(MHRV_STAND_LOW)->AsFloat;
      Stand_ratio = pDataSet->FieldByName(MHRV_STAND_RATIO)->AsFloat;
   }
   catch (Exception &exception)
   {
      MsgBox(TERROR, GetCurrentMeasureDetails(), MSG_DBREADWRITE_ERROR, MSG_ERR_READDB,
             LoadStr(MSG_ERR_READDB) +exception.Message);
      return false;
   }
   return true;
}

//--------------------------------------------------------------------------------
bool THRVTime::ExportPrintTitle(TDataSet* pDataSet, String &pOut)
{
  // Actual printing title string
  try
  {
    // Export specific properties
    pOut = pOut + pDataSet->FieldByName(MHRV_MEAN)->DisplayName + "\t";
    pOut = pOut + pDataSet->FieldByName(MHRV_MAXIMUM)->DisplayName + "\t";
    pOut = pOut + pDataSet->FieldByName(MHRV_MINIMUM)->DisplayName + "\t";
    pOut = pOut + pDataSet->FieldByName(MHRV_MAX_MIN)->DisplayName + "\t";
    pOut = pOut + pDataSet->FieldByName(MHRV_RANGE)->DisplayName + "\t";
    pOut = pOut + "SDNN\t";
    pOut = pOut + pDataSet->FieldByName(MHRV_MODE)->DisplayName + "\t";
    pOut = pOut + pDataSet->FieldByName(MHRV_NN50)->DisplayName + "\t";
    pOut = pOut + pDataSet->FieldByName(MHRV_PNN50)->DisplayName + "\t";
    // PM CR
    pOut = pOut + "RMSSD\t";
    pOut = pOut + "HRV_TRIANGULAR_INDEX\t";
    pOut = pOut + "TINN\t";
    pOut = pOut + pDataSet->FieldByName(MHRV_SEGMENT_LENGTH)->DisplayName + "\t";
    pOut = pOut + pDataSet->FieldByName(MHRV_NUMBER_SEGMENTS)->DisplayName + "\t";
    pOut = pOut + pDataSet->FieldByName(MHRV_SDANN)->DisplayName + "\t";
    pOut = pOut + "SDNN Index\t";
    pOut = pOut + pDataSet->FieldByName(MHRV_STAND_HIGH)->DisplayName + "\t";
    pOut = pOut + pDataSet->FieldByName(MHRV_STAND_LOW)->DisplayName + "\t";
    pOut = pOut + pDataSet->FieldByName(MHRV_STAND_RATIO)->DisplayName + "\t";
    pOut = pOut + pDataSet->FieldByName(MHRV_VALSALVA_HIGH)->DisplayName + "\t";
    pOut = pOut + pDataSet->FieldByName(MHRV_VALSALVA_LOW)->DisplayName + "\t";
    pOut = pOut + pDataSet->FieldByName(MHRV_VALSALVA_RATIO)->DisplayName + "\t";
  }
  catch (Exception &exception)
  {
    MsgBox(TERROR, GetCurrentHRVMeasureDetails(), MSG_EXCEPTION, MSG_EXPORT_ERROR, LoadStr(MSG_EXPORT_ERROR) + exception.Message);
    return false;
  }
  // return at success
  return true;
}

bool THRVTime::Export(String &pOut)
{
  // Export specific properties
  pOut = pOut + FormatFloat("0", RtoR_mean) + "\t";
  pOut = pOut + FormatFloat("0", RtoR_max) + "\t";
  pOut = pOut + FormatFloat("0", RtoR_min) + "\t";
  pOut = pOut + FormatFloat("0.00", RtoR_max_min) + "\t";
  pOut = pOut + FormatFloat("0", RtoR_range) + "\t";
  pOut = pOut + FormatFloat("0.00", RtoR_SD) + "\t";
  pOut = pOut + IntToStr(RtoR_mode) + "\t";
  pOut = pOut + IntToStr(NN50) + "\t";
  pOut = pOut + FormatFloat("0.0", PNN50) + "\t";
  pOut = pOut + FormatFloat("0.0", RMS_SD) + "\t";
  pOut = pOut + FormatFloat("0.0", HRV_index) + "\t";
  pOut = pOut + IntToStr(Triangular_index) + "\t";
  pOut = pOut + IntToStr(Segment_length) + "\t";
  pOut = pOut + IntToStr(No_of_segments) + "\t";
  pOut = pOut + FormatFloat("0", SDANN) + "\t";
  pOut = pOut + FormatFloat("0", SDNN) + "\t";
  pOut = pOut + FormatFloat("0.0", Stand_high) + "\t";
  pOut = pOut + FormatFloat("0.0", Stand_low) + "\t";
  pOut = pOut + FormatFloat("0.00", Stand_ratio) + "\t";
  pOut = pOut + FormatFloat("0.0", Valsalva_high) + "\t";
  pOut = pOut + FormatFloat("0.0", Valsalva_low) + "\t";
  pOut = pOut + FormatFloat("0.00", Valsalva_ratio) + "\t";

  // return at success
  return true;
}
