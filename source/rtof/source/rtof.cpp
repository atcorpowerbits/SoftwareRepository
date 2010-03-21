//---------------------------------------------------------------------------
// PM V9
#include <vcl.h>
#pragma hdrstop

#include <rtof/pubserv.h>
#include <log/pubserv.h>
#include <msg/pubserv.h>
#include <config/pubserv.h>
#include <meas/pubserv.h>
#include <scor/utils.h>
#include "math.h"
#include "measure.h"
#include "rtof.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)

RTOF_RECORD_TYPE  rtof_active;
RTOF_RECORD_TYPE  rtof_default;
bool              rtof_initialised;

short int         rtof_min;
short int         rtof_max;
int               rtof_min_time;
int               rtof_max_time;
int               rtof_capture_time;
int               rtof_last_pulse_time;

short int         rtof_Sp[RTOF_MAX_PULSES];
short int         rtof_Dp[RTOF_MAX_PULSES];
int               rtof_Sp_time[RTOF_MAX_PULSES];
int               rtof_nof_pulses;
int               rtof_index;
bool              rtof_buff_full;

UCOUNT            rtof_samples;
/* ###########################################################################
// initialise variables
*/
bool rtof_initialise(void)
{
   rtof_set_defaults();
   rtof_initialised = true;
   return rtof_initialised;
}

/* ###########################################################################
// Cleanup variables
*/
void rtof_destroy(void)
{
   if (rtof_initialised)
   {
      rtof_initialised = false;
   }
}

/* ###########################################################################
// Set default values
*/
void rtof_set_defaults(void)
{
   rtof_capture_time = 0;
   rtof_last_pulse_time = 0;
   rtof_max = 0;
   rtof_min = DEFAULT_VALUE;
   rtof_max_time = 0;
   rtof_min_time = 0;

   // PM CR
   TPWA *rtof_pwa = meas_get_current_pwa();
   rtof_samples = (UCOUNT)(rtof_pwa->SampleRate * CAPTURE_SECS_TOTAL);

   rtof_default.upper_guidance_band = DEFAULT_VALUE;
	rtof_default.lower_guidance_band = DEFAULT_VALUE;
   rtof_default.pulse_height_color = sphygmocor_red;
	rtof_default.pulse_height_variation_color = sphygmocor_red;
	rtof_default.baseline_variation_color = sphygmocor_red;
	rtof_default.pulse_height_label = "";
	rtof_default.pulse_height_variation_label = "";
	rtof_default.baseline_variation_label = "";
	rtof_default.waveform_color = sphygmocor_white;
	rtof_default.capture = false;

   rtof_reset();
}

/* ###########################################################################
// Reset RTOF values
*/
void rtof_reset(void)
{
   rtof_index = 0;
   rtof_nof_pulses = 0;
   rtof_buff_full = false;

   for (int i = 0; i < RTOF_MAX_PULSES; i++)
   {
      rtof_Sp[i] = DEFAULT_VALUE;
      rtof_Dp[i] = DEFAULT_VALUE;
      rtof_Sp_time[i] = 0;
   }

   rtof_active = rtof_default;
}

/* ###########################################################################
// Get the active RTOF record
*/
bool rtof_get(RTOF_RECORD_TYPE *rtof)
{
   rtof->upper_guidance_band = rtof_active.upper_guidance_band;
   rtof->lower_guidance_band = rtof_active.lower_guidance_band;
   rtof->pulse_height_color = rtof_active.pulse_height_color;
   rtof->pulse_height_variation_color = rtof_active.pulse_height_variation_color;
   rtof->baseline_variation_color = rtof_active.baseline_variation_color;
   rtof->pulse_height_label = rtof_active.pulse_height_label;
   rtof->pulse_height_variation_label = rtof_active.pulse_height_variation_label;
   rtof->baseline_variation_label = rtof_active.baseline_variation_label;
   rtof->waveform_color = rtof_active.waveform_color;
   rtof->capture = rtof_active.capture;
   return true;
}

/* ###########################################################################
// Get the auto capture status
*/
bool rtof_get_auto_capture(void)
{
   return rtof_active.capture;
}

/* ###########################################################################
// Add a sample to the RTOF record
// Return true if the display needs to be updated
*/
bool rtof_add_sample(short int pressure_sample)
{
   int   max_delay;
   int   upstroke;
   float heart_rate;
   int   sum_PH;
   int   sum_Dp;
   int   sum_baseline;
   float ave_Dp;
   float ave_baseline;
   int   pulse_counter;
   int   previous_pulse;
   int   start_pulse;
   int   lUpStep;
   bool  eleven_seconds;
   bool  end_pulses;

   float QC_PulseHeightVariation;
   float QC_PulseHeight;
   float QC_DiastolicVariation;
   float QC_BaselineVariation;
   float QC_LowerVariation;
   float lPHV;
   float lDV;
   float lBV;

   TPWA *rtof_pwa = meas_get_current_pwa();

   bool update_display = false;

   // Find the signal minimum
   if (rtof_min > pressure_sample)
   {
      rtof_min = pressure_sample;
      rtof_min_time = rtof_capture_time;
      rtof_max = 0;
   }
   // Find the maximum after the minimum
   if (rtof_max < pressure_sample)
   {
      rtof_max = pressure_sample;
      rtof_max_time = rtof_capture_time;
   }

   max_delay = rtof_capture_time - rtof_max_time;

   upstroke = rtof_max_time - rtof_min_time;

   ++rtof_capture_time;
   ++rtof_last_pulse_time;

   // After 2 seconds of no signal, reset the RTOF values
   if (rtof_last_pulse_time > 2 * MEAS_DEFAULT_SAMPLE_RATE)
   {
      rtof_reset();
      update_display = true;
   }
   // Ignore inflection points
   if((max_delay > 3)&&(upstroke < RTOF_MINIMUM_UPSTROKE_POINTS))
   {
        rtof_max = 0;
        rtof_min = DEFAULT_VALUE;
   }

   // Pulse Found
   if ((max_delay > RTOF_MINIMUM_DELAY_POINTS)&&(upstroke > RTOF_MINIMUM_UPSTROKE_POINTS))
   {
      // This is the first pulse
      if (rtof_nof_pulses == 0)
      {
         rtof_Sp[rtof_index] = rtof_max;
         rtof_Dp[rtof_index] = rtof_min;
         rtof_Sp_time[rtof_index] = rtof_max_time;

         rtof_last_pulse_time = 0;
         rtof_nof_pulses = 1;
         rtof_index++;
      }
      else
      {
         if (rtof_index == 0)
         {
            heart_rate = 60. * (float) MEAS_DEFAULT_SAMPLE_RATE / (rtof_max_time - rtof_Sp_time[RTOF_MAX_PULSES - 1]);
         }
         else
         {
            heart_rate = 60. * (float) MEAS_DEFAULT_SAMPLE_RATE / (rtof_max_time - rtof_Sp_time[rtof_index - 1]);
         }

         // If the Pulse Interval is valid
         if (heart_rate < MAX_HR && heart_rate > MIN_HR) 
         {
            // Calculate SP and DP
            rtof_Sp[rtof_index] = rtof_max;
            rtof_Dp[rtof_index] = rtof_min;
            rtof_Sp_time[rtof_index] = rtof_max_time;

            rtof_last_pulse_time = 0;
            rtof_active.upper_guidance_band = rtof_max;
	         rtof_active.lower_guidance_band = rtof_min;

            sum_PH = 0;
            sum_Dp = 0;
            sum_baseline = 0;
            ave_Dp = 0.;
            ave_baseline = 0.;
            rtof_nof_pulses = 0;

            pulse_counter = rtof_index;
            eleven_seconds = false; // Use the last 11 seconds
            end_pulses = false; // Or all the pulses (whichever comes first)
            previous_pulse = DEFAULT_VALUE;
            start_pulse = rtof_min;

            // Count backwards through the pulses until you reach 11 seconds
            // or the end of the pulses
            while (!eleven_seconds && !end_pulses)
            {
               // Find the maximum SP value
               if (rtof_Sp[pulse_counter] > rtof_active.upper_guidance_band)
               {
                   rtof_active.upper_guidance_band = rtof_Sp[pulse_counter];
               }
               // Find the minimum DP value
               if (rtof_Dp[pulse_counter] < rtof_active.lower_guidance_band)
               {
                  rtof_active.lower_guidance_band = rtof_Dp[pulse_counter];
               }
               // Ignore the first pulse
               if (previous_pulse == DEFAULT_VALUE)
               {
                  previous_pulse = rtof_Dp[pulse_counter];
               }
               else
               {
                  // Sum the Pulse Height of the current pulse
                  sum_PH += rtof_Sp[pulse_counter] - rtof_Dp[pulse_counter];
                  // Baseline of this pulse is the minimum of the previous upstroke
                  sum_baseline += previous_pulse;
                  // DP is the baseline value when the pulses are corrected to the same starting point
                  lUpStep = rtof_Dp[pulse_counter] - start_pulse;
                  sum_Dp += previous_pulse - lUpStep;
                  previous_pulse = rtof_Dp[pulse_counter];
                  rtof_nof_pulses++;
               }

               // When you reach the beginning of the buffer, circle to the end
               pulse_counter--;
               if (pulse_counter < 0)
               {
                  pulse_counter = RTOF_MAX_PULSES - 1;
                  // If the buffer is not full, there are no more pulses
                  if (!rtof_buff_full)
                  {
                     end_pulses = true;
                  }
               }

               if (!end_pulses)
               {
                  // Stop if 11 seconds has been reached
                  if (rtof_Sp_time[pulse_counter] < rtof_max_time - rtof_samples)
                  {
                     eleven_seconds = true;
                  }
                  // Stop if the maximum number of pulses have been reached
                  if (rtof_nof_pulses >= RTOF_MAX_PULSES)
                  {
                     end_pulses = true;
                  }
               }
            }
            // Calculate the average Pulse Height, DP and Baseline
            QC_PulseHeight = (float) sum_PH / rtof_nof_pulses;
            ave_Dp = (float) sum_Dp / rtof_nof_pulses;
            ave_baseline = (float) sum_baseline / rtof_nof_pulses;

            lPHV = 0.;
            lDV = 0.;
            lBV = 0.;
            pulse_counter = rtof_index;
            rtof_nof_pulses = 0;
            eleven_seconds = false;
            end_pulses = false;
            previous_pulse = DEFAULT_VALUE;

            // Count backwards through the pulses until you reach 11 seconds
            // or the end of the pulses
            while (!eleven_seconds && !end_pulses)
            {
               // Ignore the first pulse
               if (previous_pulse == DEFAULT_VALUE)
               {
                  previous_pulse = rtof_Dp[pulse_counter];
               }
               else
               {
                  // Sum Pulse Height, DP and Baseline Variations of the current pulse
                  lPHV += fabs((float) (rtof_Sp[pulse_counter] - rtof_Dp[pulse_counter]) - QC_PulseHeight);
                  lBV += fabs((float) previous_pulse - ave_baseline);
                  lUpStep = rtof_Dp[pulse_counter] - start_pulse;
                  lDV += fabs((float)(previous_pulse - lUpStep) - ave_Dp);
                  previous_pulse = rtof_Dp[pulse_counter];
                  rtof_nof_pulses++;
               }

               // When you reach the beginning of the buffer, circle to the end
               pulse_counter--;
               if (pulse_counter < 0)
               {
                  pulse_counter = RTOF_MAX_PULSES - 1;
                  // If the buffer is not full, there are no more pulses
                  if (!rtof_buff_full)
                  {
                     end_pulses = true; // No more pulses
                  }
               }

               if (!end_pulses)
               {
                  // Stop if 11 seconds has been reached
                  if (rtof_Sp_time[pulse_counter] < rtof_max_time - rtof_samples)
                  {
                     eleven_seconds = true;
                  }
                  // Stop if the maximum number of pulses have been reached
                  if (rtof_nof_pulses >= RTOF_MAX_PULSES)
                  {
                     end_pulses = true;
                  }
               }
            }
            // Calculate Pulse Height, Diastolic and Baseline Variations as a
            // percentage of the Average Pulse Height
            lPHV /= rtof_nof_pulses;
            QC_PulseHeightVariation = (lPHV >= 0 ? lPHV/QC_PulseHeight * 100 : DEFAULT_VALUE);
            lBV /= rtof_nof_pulses;
            QC_BaselineVariation = (lBV >= 0 ? lBV/QC_PulseHeight * 100 : DEFAULT_VALUE);
            lDV /= rtof_nof_pulses;
            QC_DiastolicVariation = (lDV >= 0 ? lDV/QC_PulseHeight * 100 : DEFAULT_VALUE);
            // The Lower variation is a combination of Baseline and Diastolic Variations
            QC_LowerVariation = 0.5 * QC_BaselineVariation + 0.5 * QC_DiastolicVariation;

            // The actual Pulse Height value is dependant on the Electronics Module type
            QC_PulseHeight = QC_PulseHeight / rtof_pwa->Periph.qc_scale;

            // Determine the Pulse Height Variation feedback colour and label
            if (QC_PulseHeightVariation < 5.0)
            {
               rtof_active.pulse_height_variation_color = sphygmocor_lime;
               rtof_active.pulse_height_variation_label = "";
            }
            else if (QC_PulseHeightVariation < 10.0)
            {
               rtof_active.pulse_height_variation_color = sphygmocor_yellow;
               rtof_active.pulse_height_variation_label = "Reduce Pulse Height Variation";
            }
            else
            {
               rtof_active.pulse_height_variation_color = sphygmocor_red;
               rtof_active.pulse_height_variation_label = "Reduce Pulse Height Variation";
            }

            // Determine the Baseline Variation feedback colour and label
            if (QC_LowerVariation < 5.0)
            {
               rtof_active.baseline_variation_color = sphygmocor_lime;
               rtof_active.baseline_variation_label = "";
            }
            else if (QC_LowerVariation < 10.0)
            {
               rtof_active.baseline_variation_color = sphygmocor_yellow;
               rtof_active.baseline_variation_label = "Reduce Baseline Variation";
            }
            else
            {
               rtof_active.baseline_variation_color = sphygmocor_red;
               rtof_active.baseline_variation_label = "Reduce Baseline Variation";
            }

            // Determine the Pulse Height feedback colour and label
            if (QC_PulseHeight > 85.0)
            {
               rtof_active.pulse_height_color = sphygmocor_lime;
               rtof_active.pulse_height_label = "";
            }
            else if (QC_PulseHeight > 75.0)
            {
               rtof_active.pulse_height_color = sphygmocor_yellow;
               rtof_active.pulse_height_label = "Increase Pulse Height";
            }
            else
            {
               rtof_active.pulse_height_color = sphygmocor_red;
               rtof_active.pulse_height_label = "Increase Pulse Height";
            }

            // If there's 11 seconds of pulses and all quality control parameters
            // are acceptable, then the waveform is acceptable
            if (eleven_seconds)
            {
               if (QC_PulseHeightVariation < 5.0 && QC_LowerVariation < 5.0 && QC_PulseHeight > 85.0)
               {
                  rtof_active.waveform_color = sphygmocor_lime;
                  // If Auto Capture is enabled, then allow report generation
                  if (config_get_auto_capture())
                  {
                     rtof_active.capture = true;
                  }
               }
               else
               {
                  rtof_active.waveform_color = sphygmocor_white;
               }
            }

            // Update the circular buffer
            rtof_index++;
            if (!rtof_buff_full)
            {
               rtof_buff_full = (rtof_index >= RTOF_MAX_PULSES) ? true : false;
            }
            rtof_index %= RTOF_MAX_PULSES;
            update_display = true;
         }
      }
      rtof_max = 0;
      rtof_min = DEFAULT_VALUE;
   }

   return update_display;
}
