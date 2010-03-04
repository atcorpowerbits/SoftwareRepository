//---------------------------------------------------------------------------
#include <vcl.h>
#include <dos.h>
#pragma hdrstop

#include <inc/std.h>
#include <comms/pubserv.h>
#include <meas/pubserv.h>
#include <config/pubserv.h>
#include <capture/pubserv.h>
#include <msg/pubserv.h>
#include <log/pubserv.h>
#include <rtof/pubserv.h>
#include "form_cappwa.h"
#include "form_cappwv.h"
#include "form_cappwm.h"
#include "form_caphrv.h"
#include "capture.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

VAR_EXPORT  UCOUNT     capture_p_upper_limit;
VAR_EXPORT  UCOUNT     capture_raw_max;
VAR_EXPORT  UCOUNT     capture_raw_min;
VAR_EXPORT  UCOUNT     capture_raw_min_pulse_height;
VAR_EXPORT  UCOUNT     capture_raw_max_pulse_height;
VAR_EXPORT  UCOUNT     capture_raw_data_threshold;
VAR_EXPORT  UCOUNT     capture_raw_data_height_threshold;
VAR_EXPORT  COUNT      capture_pwm_calibration[CAPTURE_PWM_MAX_CALIBRATE_CHANNEL];
VAR_EXPORT  int        capture_time;
VAR_EXPORT  int        capture_raw_value;
VAR_EXPORT  int        capture_circbuff_index;
VAR_EXPORT  bool       capture_circbuff_full;
VAR_EXPORT  bool       capture_calibrated;
VAR_EXPORT  bool       capture_tonometer;
VAR_EXPORT  bool       capture_pwm_is_autoscale;
VAR_EXPORT  bool       capture_loopback;
VAR_EXPORT  short int  *capture_ch1_buff;
VAR_EXPORT  short int  *capture_ch2_buff;
VAR_EXPORT  int        capture_increment;

bool          capture_initialised;
MEAS_ID_TYPE  capture_meas_type;
const String LEVEL_CAPTION = "???";

bool capture_initialise(void)
{
   int i;

   capture_initialised = false;

   capture_p_upper_limit = (UCOUNT)(CAPTURE_MAX_RAW_VALUE);
   capture_raw_max = (UCOUNT)CAPTURE_MAX_RAW_VALUE;
   capture_raw_min = (UCOUNT)CAPTURE_MIN_RAW_VALUE;
   capture_raw_min_pulse_height = (UCOUNT)CAPTURE_MIN_PULSE_HEIGHT;
   capture_raw_max_pulse_height = (UCOUNT)CAPTURE_MAX_PULSE_HEIGHT;
   capture_raw_data_threshold = (UCOUNT)CAPTURE_DATA_THRESHOLD;
   capture_raw_data_height_threshold = (UCOUNT)CAPTURE_MIN_PULSE_HEIGHT_THRESHOLD;
   capture_meas_type = MEAS_NONE;
   capture_time = 0;
   capture_raw_value = 0;
   capture_circbuff_index = 0;
   capture_circbuff_full = false;                             
   capture_calibrated = false;
   capture_tonometer = true;
   capture_pwm_is_autoscale = false;
   capture_loopback = false;
   capture_increment = CAPTURE_INTERVAL;
   
   capture_ch1_buff = NULL;
   capture_ch2_buff = NULL;

   for (i = 0; i < CAPTURE_PWM_MAX_CALIBRATE_CHANNEL; i++)
   {
      capture_pwm_calibration[i] = 0;
   }

   capture_initialised = true;

   return (capture_initialised);
}

void capture_destroy(void)
{
   if (capture_initialised)
   {
      if (capture_ch1_buff != NULL)
      {
         delete [] capture_ch1_buff;
      }
      if (capture_ch2_buff != NULL)
      {
         delete [] capture_ch2_buff;
      }
      capture_initialised = false;
   }
}

void capture_reset(MEAS_ID_TYPE meas_id)
{
   capture_time = 0;
   capture_raw_value = 0;
   capture_circbuff_index = 0;
   capture_circbuff_full = false;
   capture_calibrated = false;


   capture_p_upper_limit = config_get_pressure_upper_limit();

   capture_raw_max = (UCOUNT)CAPTURE_MAX_RAW_VALUE;
   capture_raw_min = (UCOUNT)CAPTURE_MIN_RAW_VALUE;
   capture_raw_min_pulse_height = (UCOUNT)CAPTURE_MIN_PULSE_HEIGHT;
   capture_raw_max_pulse_height = (UCOUNT)CAPTURE_MAX_PULSE_HEIGHT;
   capture_raw_data_threshold = (UCOUNT)CAPTURE_DATA_THRESHOLD;
   capture_raw_data_height_threshold = (UCOUNT)CAPTURE_MIN_PULSE_HEIGHT_THRESHOLD;
   capture_increment = CAPTURE_INTERVAL;
   
   if (comms_is_module_12bit())
   {
      if (capture_p_upper_limit <= CAPTURE_OLD_MAX_RAW_VALUE)
      {
         capture_p_upper_limit = CAPTURE_MAX_RAW_VALUE;
      }
   }
   else
   {
      capture_raw_max = (UCOUNT)CAPTURE_OLD_MAX_RAW_VALUE;
      capture_raw_min = (UCOUNT)CAPTURE_OLD_MIN_RAW_VALUE;
      capture_raw_min_pulse_height = (UCOUNT)CAPTURE_OLD_MIN_PULSE_HEIGHT;
      capture_raw_max_pulse_height = (UCOUNT)CAPTURE_OLD_MAX_PULSE_HEIGHT;
      capture_raw_data_threshold = (UCOUNT)CAPTURE_OLD_DATA_THRESHOLD;
      capture_raw_data_height_threshold = (UCOUNT)CAPTURE_OLD_MIN_PULSE_HEIGHT_THRESHOLD;
      capture_increment = CAPTURE_OLD_INTERVAL;
      
      if (capture_p_upper_limit > capture_raw_max)
      {
         capture_p_upper_limit = capture_raw_max;
      }
   }

   switch (meas_id)
   {
      case MEAS_PWA_ID:
         frm_capture_pwa->lbl_level->Caption = LEVEL_CAPTION;
         frm_capture_pwa->tmr_capture->Enabled = false;

         frm_capture_pwa->srs_capture_main->Clear();
         frm_capture_pwa->srs_capture_secondary->Clear();
         frm_capture_pwa->srs_rtof_upper->Clear();
         frm_capture_pwa->srs_rtof_lower->Clear();
         frm_capture_pwa->srs_rtof_height->Clear();

         frm_capture_pwa->chrt_main->LeftAxis->SetMinMax(capture_raw_min,
                                                         capture_p_upper_limit);
         frm_capture_pwa->chrt_main->LeftAxis->Automatic = false;

         frm_capture_pwa->chrt_secondary->BottomAxis->SetMinMax(0, frm_capture_pwa->total_samples / 2);
         frm_capture_pwa->chrt_secondary->LeftAxis->SetMinMax(capture_raw_min,
                                                              capture_p_upper_limit);

         // PM V9
         // Setup RTOF
         rtof_set_defaults();
         break;

      case MEAS_PWV_ID:
         frm_capture_pwv->lbl_level->Caption = LEVEL_CAPTION;
         frm_capture_pwv->lbl_level_ecg->Caption = LEVEL_CAPTION;
         frm_capture_pwv->tmr_capture->Enabled = false;

         frm_capture_pwv->srs_pressure_main->Clear();
         frm_capture_pwv->srs_ecg_main->Clear();
         frm_capture_pwv->srs_pressure_secondary->Clear();
         frm_capture_pwv->srs_ecg_secondary->Clear();

         frm_capture_pwv->chrt_pressure->LeftAxis->Automatic = false;
         frm_capture_pwv->chrt_pressure->LeftAxis->SetMinMax(capture_raw_min,
                                                             capture_p_upper_limit);
         frm_capture_pwv->chrt_pressure->LeftAxis->Increment = capture_increment;
         frm_capture_pwv->chrt_ecg->LeftAxis->Automatic = false;
         frm_capture_pwv->chrt_ecg->LeftAxis->SetMinMax(capture_raw_min,
                                                              capture_p_upper_limit);
         frm_capture_pwv->chrt_ecg->LeftAxis->Increment = capture_increment;

         frm_capture_pwv->chrt_secondary->BottomAxis->SetMinMax(0, frm_capture_pwv->total_samples / 2);
         frm_capture_pwv->chrt_secondary->LeftAxis->SetMinMax(capture_raw_min,
                                                              capture_p_upper_limit);
         frm_capture_pwv->chrt_secondary->RightAxis->SetMinMax(capture_raw_min,
                                                               capture_p_upper_limit);
         break;

      case MEAS_PWM_ID:
         frm_capture_pwm->tmr_capture->Enabled = false;
         capture_calibrated = frm_capture_pwm->pwm->Calibrated;
         frm_capture_pwm->trend_counter = 1;
         frm_capture_pwm->calculated_trend_counter = 0;

         frm_capture_pwm->srs_periph_pressure->Clear();
         frm_capture_pwm->srs_central_pressure->Clear();

         /*
         ** Used display_resolution previously to set the axis as points rather
         ** than time indication
         */
         if (frm_capture_pwm->pwm->TrendSamplePeriod == 0)
         {
            frm_capture_pwm->chrt_pressure->BottomAxis->SetMinMax(0, CAPTURE_SECS_DISPLAY_RESOLUTION);
         }
         else
         {
            frm_capture_pwm->chrt_pressure->BottomAxis->SetMinMax(0, frm_capture_pwm->pwm->TrendSamplePeriod);
         }


         if (capture_calibrated)
         {
            capture_p_upper_limit = CAPTURE_CAL_UPPER_PRESSURE_LIMIT;
            capture_raw_max = CAPTURE_CAL_MAX_RAW_VALUE;
            capture_raw_min = CAPTURE_CAL_MIN_RAW_VALUE;
            capture_raw_min_pulse_height = CAPTURE_CAL_MIN_PULSE_HEIGHT;
            capture_raw_max_pulse_height = CAPTURE_CAL_MAX_PULSE_HEIGHT;
            capture_raw_data_threshold = CAPTURE_CAL_DATA_THRESHOLD;
            frm_capture_pwm->chrt_pressure->LeftAxis->Automatic = true;
            frm_capture_pwm->chrt_pressure->LeftAxis->SetMinMax(capture_raw_min,
                                                                capture_p_upper_limit);
         }
         else
         {
            frm_capture_pwm->chrt_pressure->LeftAxis->Automatic = false;
            frm_capture_pwm->chrt_pressure->LeftAxis->SetMinMax(capture_raw_min,
                                                                capture_p_upper_limit);
         }


         if (capture_calibrated)
         {
            frm_capture_pwm->chrt_pressure->RightAxis->Automatic = true;
            frm_capture_pwm->chrt_pressure->RightAxis->SetMinMax(capture_raw_min,
                                                                 capture_p_upper_limit);
         }
         else
         {
            frm_capture_pwm->chrt_pressure->RightAxis->Automatic = false;
            frm_capture_pwm->chrt_pressure->RightAxis->SetMinMax(capture_raw_min,
                                                                 capture_p_upper_limit);
         }

         frm_capture_pwm->srs_central_ap->Clear();
         frm_capture_pwm->srs_central_dp->Clear();
         frm_capture_pwm->srs_central_sp->Clear();
         frm_capture_pwm->srs_central_pp->Clear();
         frm_capture_pwm->srs_periph_dp->Clear();
         frm_capture_pwm->srs_periph_sp->Clear();
         frm_capture_pwm->srs_periph_pp->Clear();
         frm_capture_pwm->srs_mp->Clear();

         frm_capture_pwm->srs_augx->Clear();
         frm_capture_pwm->srs_cardiac_period->Clear();
         frm_capture_pwm->srs_ed->Clear();
         frm_capture_pwm->srs_sevr->Clear();

         if (frm_capture_pwm->display_trend_refresh_rate)
         {
            frm_capture_pwm->chrt_trend_pressure->BottomAxis->SetMinMax(0, frm_capture_pwm->display_trend_refresh_rate);
            frm_capture_pwm->ChartHR->BottomAxis->SetMinMax(0, frm_capture_pwm->display_trend_refresh_rate);
            frm_capture_pwm->ChartSEVR->BottomAxis->SetMinMax(0, frm_capture_pwm->display_trend_refresh_rate);
            frm_capture_pwm->ChartED->BottomAxis->SetMinMax(0, frm_capture_pwm->display_trend_refresh_rate);
            frm_capture_pwm->ChartAI->BottomAxis->SetMinMax(0, frm_capture_pwm->display_trend_refresh_rate);
         }
         else
         {
            frm_capture_pwm->chrt_trend_pressure->BottomAxis->Automatic = true;
            frm_capture_pwm->ChartHR->BottomAxis->Automatic = true;
            frm_capture_pwm->ChartSEVR->BottomAxis->Automatic = true;
            frm_capture_pwm->ChartED->BottomAxis->Automatic = true;
            frm_capture_pwm->ChartAI->BottomAxis->Automatic = true;
         }
         if (capture_pwm_get_autoscale_trends() == true)
         {
            frm_capture_pwm->ChartAI->AllowZoom = true;
            frm_capture_pwm->ChartSEVR->AllowZoom = true;
            frm_capture_pwm->ChartED->AllowZoom = true;
            frm_capture_pwm->ChartHR->AllowZoom = true;

            frm_capture_pwm->chrt_trend_pressure->LeftAxis->AutomaticMaximum = true;
            frm_capture_pwm->ChartHR->LeftAxis->AutomaticMaximum = true;
            frm_capture_pwm->ChartSEVR->LeftAxis->AutomaticMaximum = true;
            frm_capture_pwm->ChartED->LeftAxis->AutomaticMaximum = true;
            frm_capture_pwm->ChartAI->LeftAxis->AutomaticMaximum = true;
         }
         else
         {
            frm_capture_pwm->ChartAI->AllowZoom = false;
            frm_capture_pwm->ChartSEVR->AllowZoom = false;
            frm_capture_pwm->ChartED->AllowZoom = false;
            frm_capture_pwm->ChartHR->AllowZoom = false;
         }
         break;

      case MEAS_HRV_ID:

         frm_capture_hrv->srs_ecg->Clear();
         frm_capture_hrv->srs_rtor_interval->Clear();
         frm_capture_hrv->srs_highlow_rtor->Clear();

         frm_capture_hrv->chrt_ecg_monitor->BottomAxis->SetMinMax(0, 5);
         /*
         frm_capture_hrv->chrt_ecg_monitor->LeftAxis->SetMinMax(capture_raw_min,
                                                      capture_p_upper_limit);
         */
         frm_capture_hrv->chrt_ecg_monitor->LeftAxis->Automatic = false;

         break;

      default:
         break;
   }
}

bool capture_show_form(MEAS_ID_TYPE meas_id)
{
   bool           calc = false;
   COMMS_ID_TYPE  the_port;

   the_port = config_get_comms_port();
   if (comms_open(the_port))
   {
      /*
      ** Occassionally the module locks in a certain mode and you need three module
      ** detects to unlock it. Since the module does not have a reset command then this
      ** is a suitable workaround for the moment. 15/05/2002
      */
      comms_detect_module();
      if (!comms_is_module_available())
      {
         comms_detect_module();
         if (!comms_is_module_available())
         {
            comms_detect_module();
         }
      }
      if (comms_is_module_available())
      {
         capture_meas_type = meas_id;
         if (meas_id == MEAS_PWA_ID)
         {
            frm_capture_pwa = new Tfrm_capture_pwa(Application->MainForm);
            if (frm_capture_pwa != NULL)
            {
               if (frm_capture_pwa->ShowModal() == mrOk)
               {
                  calc = true;
               }
               try
               {
                  delete frm_capture_pwa;
                  frm_capture_pwa = NULL;
               }
               catch (...)
               {
                  ;
               }
            }
         }
         else if (meas_id == MEAS_PWV_ID)
         {
            frm_capture_pwv = new Tfrm_capture_pwv(Application->MainForm, true);
            if (frm_capture_pwv != NULL)
            {
               if (frm_capture_pwv->ShowModal() == mrOk)
               {
                  calc = true;
               }
               try
               {
                  delete frm_capture_pwv;
                  frm_capture_pwv = NULL;
               }
               catch (...)
               {
                  ;
               }
               if (calc)
               {
                  calc = false;
                  if (MsgBox("Site A Data Captured.\n\nWould you like to continue and capture Site B data.",
                             SCONFIRMATION,
                             MB_YESNO | MB_ICONQUESTION) == ID_YES)
                  {
                     frm_capture_pwv = new Tfrm_capture_pwv(Application->MainForm, false);
                     if (frm_capture_pwv != NULL)
                     {
                        if (frm_capture_pwv->ShowModal() == mrOk)
                        {
                           calc = true;
                        }
                        else
                        {
                           bool pwv_siteb_stop = false;
                           while (!pwv_siteb_stop)
                           {
                              if (MsgBox("Site B Data Capture Failed.\n\nWould you like to retry and capture Site B Data.",
                                          SCONFIRMATION,
                                          MB_YESNO | MB_ICONQUESTION) == ID_NO)
                              {
                                 pwv_siteb_stop = true;
                              }
                              else
                              {
                                 if (frm_capture_pwv->ShowModal() == mrOk)
                                 {
                                    calc = true;
                                    pwv_siteb_stop = true;
                                 }
                              }
                           }
                        }

                        try
                        {
                           delete frm_capture_pwv;
                           frm_capture_pwv = NULL;
                        }
                        catch (...)
                        {
                           ;
                        }
                     }
                  }
               }
            }
         }
         else if (meas_id == MEAS_PWM_ID)
         {
            frm_capture_pwm = new Tfrm_capture_pwm(Application->MainForm);
            if (frm_capture_pwm != NULL)
            {
               if (frm_capture_pwm->ShowModal() == mrOk)
               {
                  calc = true;
               }
               try
               {
                  delete frm_capture_pwm;
                  frm_capture_pwm = NULL;
               }
               catch (...)
               {
                  ;
               }
            }
         }
         else if (meas_id == MEAS_HRV_ID)
         {
            frm_capture_hrv = new Tfrm_capture_hrv(Application->MainForm);
            if (frm_capture_hrv != NULL)
            {
               if (frm_capture_hrv->ShowModal() == mrOk)
               {
                  calc = true;
               }
               try
               {
                  delete frm_capture_hrv;
                  frm_capture_hrv = NULL;
               }
               catch (...)
               {
                  ;
               }
            }
         }
         capture_meas_type = MEAS_NONE;
      }
      else
      {
         MsgBox(LoadStr(MSG_COMMS_EL_MODULE_NOT_FOUND) + "\n\n" +LoadStr(MSG_COMMS_CHECK_POWER_CONNECTION),
                SNOTIFICATION,
                MB_ICONINFORMATION | MB_OK);
      }
   }
   else
   {
      if (the_port == COMMS_PORT_USB)
      {
         MsgBox(LoadStr(MSG_COMMS_EL_MODULE_NOT_FOUND) + "\n\n" +LoadStr(MSG_COMMS_CHECK_POWER_CONNECTION),
                SNOTIFICATION,
                MB_ICONINFORMATION | MB_OK);
      }
   }

   return (calc);
}

bool capture_is_calibrated(void)
{
   return capture_calibrated;
}

bool capture_from_tonometer(void)
{
   return capture_tonometer;
}

bool capture_pwm_get_autoscale_trends(void)
{
   return capture_pwm_is_autoscale;
}

void capture_pwm_set_autoscale_trends(bool is_autoscale_trends)
{
   capture_pwm_is_autoscale = is_autoscale_trends;
}

void capture_set_from_tonometer(bool is_tonometer)
{
   capture_tonometer = is_tonometer;
}

bool capture_do_loopback(void)
{
   return capture_loopback;
}

void capture_set_loopback(bool loopback)
{
   capture_loopback = loopback;
}

bool capture_send_output(CAPTURE_PWM_CALIBRATE_CHANNEL_TYPE  op_channel)
{
   bool op_send = false;

   if (capture_meas_type == MEAS_PWM_ID)
   {
      if (op_channel == CAPTURE_PWM_OUTPUT_CHANNEL_ONE)
      {
         if (frm_capture_pwm != NULL)
         {
            if (frm_capture_pwm->pwm->PeriphSendOut)
            {
               op_send = true;
            }
         }
      }
      if (op_channel == CAPTURE_PWM_OUTPUT_CHANNEL_TWO)
      {
         if (frm_capture_pwm != NULL)
         {
            if (frm_capture_pwm->pwm->AorticSendOut)
            {
               op_send = true;
            }
         }
      }
   }
   return (op_send);
}

COUNT capture_get_calibration_factor(CAPTURE_PWM_CALIBRATE_CHANNEL_TYPE  channel)
{
   UCOUNT cal_factor;

   switch (channel)
   {
      case CAPTURE_PWM_INPUT_CHANNEL:
         cal_factor = capture_pwm_calibration[CAPTURE_PWM_INPUT_CHANNEL];
         break;
      case CAPTURE_PWM_OUTPUT_CHANNEL_ONE:
         cal_factor = capture_pwm_calibration[CAPTURE_PWM_OUTPUT_CHANNEL_ONE];
         break;
      case CAPTURE_PWM_OUTPUT_CHANNEL_TWO:
         cal_factor = capture_pwm_calibration[CAPTURE_PWM_OUTPUT_CHANNEL_TWO];
         break;
      default:
         cal_factor = 0;
         break;
   }
   return (cal_factor);
}

void capture_set_calibration_factor(CAPTURE_PWM_CALIBRATE_CHANNEL_TYPE  channel,
                                    UCOUNT                              cal_factor)
{
   int  input_at_two_point_five = 3072;
   int  output_at_two = 2866;
   switch (channel)
   {
      case CAPTURE_PWM_INPUT_CHANNEL:
         capture_pwm_calibration[CAPTURE_PWM_INPUT_CHANNEL] = input_at_two_point_five - cal_factor;
         break;

      case CAPTURE_PWM_OUTPUT_CHANNEL_ONE:
         capture_pwm_calibration[CAPTURE_PWM_OUTPUT_CHANNEL_ONE] = (output_at_two - cal_factor);
         break;

      case CAPTURE_PWM_OUTPUT_CHANNEL_TWO:
         capture_pwm_calibration[CAPTURE_PWM_OUTPUT_CHANNEL_TWO] = (output_at_two - cal_factor);
         break;

      default:
         break;
   }
}

void capture_simulation_get_data(void)
{
   switch (capture_meas_type)
   {
      case MEAS_PWA_ID:
         frm_capture_pwa->simulate_data();
         break;

      case MEAS_PWV_ID:
         frm_capture_pwv->simulate_data();
         break;

      case MEAS_PWM_ID:
         frm_capture_pwm->simulate_data();
         break;

      case MEAS_HRV_ID:
         frm_capture_hrv->simulate_data();
         break;

      default:
         break;
   }
}

bool capture_simulation_start(void)
{
   bool started = false;

   switch (capture_meas_type)
   {
      case MEAS_PWA_ID:
         if (frm_capture_pwa->simulate_start())
         {
            started = true;
         }
         break;

      case MEAS_PWV_ID:
         if (frm_capture_pwv->simulate_start())
         {
            started = true;
         }
         break;

      case MEAS_PWM_ID:
         if (frm_capture_pwm->simulate_start())
         {
            started = true;
         }
         break;

      case MEAS_HRV_ID:
         if (frm_capture_hrv->simulate_start())
         {
            started = true;
         }
         break;
      default:
         break;
   }
   return started;
}

void capture_simulation_stop(void)
{
   switch (capture_meas_type)
   {
      case MEAS_PWA_ID:
         frm_capture_pwa->simulate_stop();
         break;

      case MEAS_PWV_ID:
         frm_capture_pwv->simulate_stop();
         break;

      case MEAS_PWM_ID:
         frm_capture_pwm->simulate_stop();
         break;

       case MEAS_HRV_ID:
         frm_capture_hrv->simulate_stop();
         break;

      default:
         break;
   }
}

bool capture_add_sample(short int  psample,
                        bool       data_valid,
                        bool       check_fswitch)
{
   bool captured = false;

   if (capture_meas_type == MEAS_PWA_ID)
   {
      if (capture_pwa_add_sample(psample, data_valid, check_fswitch))
      {
         captured = true;
      }
   }
   else if (capture_meas_type == MEAS_PWM_ID)
   {
      if (capture_pwm_add_sample(psample, data_valid, check_fswitch))
      {
         captured = true;
      }
   }
   return (captured);
}

bool capture_pwv_add_sample(short int   pressure_sample,
                            short int   ecg_sample,
                            bool        is_data_valid,
                            bool        check_fswitch)
{
   const double   SRS_YMIN_VALUE = 1000.;
   double         max_y;
   double         min_y;
   double         max_ecg_y;
   double         min_ecg_y;
   double         ecg_height;
   int            xpos_srs_main;
   int            xpos_srs_secondary;
   bool           displayed_ok = true;
   COMMS_ID_TYPE  the_port;
   static double  srs_max_y = 0.0;
   static double  srs_min_y = SRS_YMIN_VALUE;
   static int     i = 0;
   static unsigned int data_buff[2][10];

   if (frm_capture_pwv == NULL)
   {
      log_write("Comms PWV Capture: Capture closed but received data");
      return false;
   }

   if (is_data_valid && (ecg_sample >= 0) && (pressure_sample >= 0))
   {
      data_buff[0][i] = pressure_sample;
      data_buff[1][i] = ecg_sample;
      ++i;
      if (i == 4)
      {
         frm_capture_pwv->srs_ecg_main->AutoRepaint = false;
         frm_capture_pwv->srs_pressure_main->AutoRepaint = false;
         frm_capture_pwv->srs_pressure_secondary->AutoRepaint = false;
         frm_capture_pwv->srs_ecg_secondary->AutoRepaint = false;
         i = 0;
         for (i = 0; i < 4; i++)
         {
            xpos_srs_main = frm_capture_pwv->srs_pressure_main->Count();
            xpos_srs_secondary = frm_capture_pwv->srs_pressure_secondary->Count();
            if (data_buff[0][i] > frm_capture_pwv->chrt_pressure->LeftAxis->Maximum)
            {
               srs_max_y = data_buff[0][i];
               frm_capture_pwv->srs_pressure_main->AddXY(xpos_srs_main,
                                                         frm_capture_pwv->chrt_pressure->LeftAxis->Maximum,
                                                         "", clWhite);
            }
            else if (data_buff[0][i] < frm_capture_pwv->chrt_pressure->LeftAxis->Minimum)
            {
               srs_min_y = data_buff[0][i];
               frm_capture_pwv->srs_pressure_main->AddXY(xpos_srs_main,
                                                        frm_capture_pwv->chrt_pressure->LeftAxis->Minimum,
                                                        "", clWhite);
            }
            else
            {
               frm_capture_pwv->srs_pressure_main->AddXY(xpos_srs_main, data_buff[0][i], "", clWhite);
            }
            frm_capture_pwv->srs_ecg_main->AddXY(xpos_srs_main, data_buff[1][i], "", clYellow);

             if ((i % 2) == 0)
            {
               frm_capture_pwv->srs_pressure_secondary->AddXY(xpos_srs_secondary, data_buff[0][i], "", clLime);
               frm_capture_pwv->srs_ecg_secondary->AddXY(xpos_srs_secondary, data_buff[1][i], "", clYellow);
            }

            capture_ch1_buff[capture_circbuff_index] = data_buff[0][i];
            capture_ch2_buff[capture_circbuff_index] = data_buff[1][i];
            ++capture_circbuff_index;
            if (capture_circbuff_full == false)
            {
               capture_circbuff_full = (capture_circbuff_index >= frm_capture_pwv->total_samples) ? true : false;
            }
            capture_circbuff_index %= frm_capture_pwv->total_samples;
         }

         i = 0;
         xpos_srs_main = frm_capture_pwv->srs_pressure_main->Count();
         xpos_srs_secondary = frm_capture_pwv->srs_pressure_secondary->Count();
         xpos_srs_secondary = xpos_srs_secondary * 2;

         if (xpos_srs_secondary >= frm_capture_pwv->display_rescale)
         {
            if (xpos_srs_secondary >= frm_capture_pwv->display_reset)
            {
               frm_capture_pwv->srs_pressure_secondary->AutoRepaint = true;
               frm_capture_pwv->srs_pressure_secondary->Clear();
               frm_capture_pwv->srs_ecg_secondary->AutoRepaint = true;
               frm_capture_pwv->srs_ecg_secondary->Clear();
               frm_capture_pwv->chrt_secondary->BottomAxis->SetMinMax(0, frm_capture_pwv->total_samples / 2);
               xpos_srs_secondary = 0;
            }
            else
            {
               if (((xpos_srs_secondary - frm_capture_pwv->display_rescale) % frm_capture_pwv->pwv->SampleRate) == 0)
               {
                  min_y = frm_capture_pwv->srs_pressure_main->MinYValue();
                  max_y = frm_capture_pwv->srs_pressure_main->MaxYValue();

                  min_ecg_y = frm_capture_pwv->srs_ecg_main->MinYValue();
                  max_ecg_y = frm_capture_pwv->srs_ecg_main->MaxYValue();

                  if (max_y == min_y)
                  {
                     max_y = capture_p_upper_limit;
                     min_y = capture_raw_min;
                  }
                  else
                  {
                     max_y = max_y * 1.04;
                     min_y = min_y * 0.96;
                  }

                  if (max_ecg_y == min_ecg_y)
                  {
                     max_ecg_y = capture_p_upper_limit;
                     min_ecg_y = capture_raw_min;
                  }
                  else
                  {
                     max_ecg_y = max_ecg_y * 1.04;
                     min_ecg_y = min_ecg_y * 0.96;
                  }
                  frm_capture_pwv->srs_pressure_secondary->AutoRepaint = true;
                  frm_capture_pwv->srs_ecg_secondary->AutoRepaint = true;
                  if (xpos_srs_secondary >= frm_capture_pwv->total_samples)
                  {
                     frm_capture_pwv->chrt_secondary->BottomAxis->Scroll(frm_capture_pwv->pwv->SampleRate / 2, false);
                  }

                  frm_capture_pwv->chrt_secondary->LeftAxis->SetMinMax(min_y, max_y);
                  frm_capture_pwv->chrt_secondary->LeftAxis->Automatic = false;

                  frm_capture_pwv->chrt_secondary->RightAxis->SetMinMax(min_ecg_y, max_ecg_y);
                  frm_capture_pwv->chrt_secondary->RightAxis->Automatic = false;

               }
            }
         }
         if (xpos_srs_main >= frm_capture_pwv->display_resolution)
         {
            frm_capture_pwv->srs_pressure_main->AutoRepaint = true;
            frm_capture_pwv->srs_ecg_main->AutoRepaint = true;
            max_y = frm_capture_pwv->srs_pressure_main->MaxYValue();
            min_y = frm_capture_pwv->srs_pressure_main->MinYValue();

            if (max_y != min_y && min_y > capture_raw_min)
            {
               if (srs_max_y != 0.0)
               {
                  max_y = srs_max_y;
               }


               if (srs_min_y != SRS_YMIN_VALUE)
               {
                  min_y = srs_min_y;
               }
            }
            srs_max_y = 0.0;
            srs_min_y = SRS_YMIN_VALUE;

            min_ecg_y = frm_capture_pwv->srs_ecg_main->MinYValue();
            max_ecg_y = frm_capture_pwv->srs_ecg_main->MaxYValue();
            frm_capture_pwv->lbl_level_ecg->Caption = RoundIntToStr(max_ecg_y - min_ecg_y);
            if (max_ecg_y == min_ecg_y)
            {
               max_ecg_y = capture_p_upper_limit;
               min_ecg_y = capture_raw_min;
            }
            else
            {
               /*if ((int)(min_ecg_y - capture_raw_min) >= 0)
               {
                  min_ecg_y = min_ecg_y - capture_raw_min;
               }*/
               max_ecg_y = max_ecg_y * 1.04;
               min_ecg_y = min_ecg_y * 0.96;
            }
            frm_capture_pwv->chrt_ecg->LeftAxis->SetMinMax(min_ecg_y, max_ecg_y);
            frm_capture_pwv->chrt_ecg->LeftAxis->Automatic = false;

            frm_capture_pwv->srs_pressure_main->Clear();
            frm_capture_pwv->srs_ecg_main->Clear();
            xpos_srs_main = 0;
            frm_capture_pwv->lbl_level->Caption = RoundIntToStr(max_y - min_y);


            if ((max_y > frm_capture_pwv->chrt_pressure->LeftAxis->Maximum) ||
                (min_y < frm_capture_pwv->chrt_pressure->LeftAxis->Minimum) ||
                ((max_y -  min_y) > capture_raw_max_pulse_height) || ((max_y - min_y) < capture_raw_min_pulse_height) ||
                (frm_capture_pwv->chrt_pressure->LeftAxis->Maximum >= capture_p_upper_limit))
            {
               frm_capture_pwv->chrt_pressure->LeftAxis->Automatic = false;

               if (((max_y - min_y) > capture_raw_max_pulse_height) ||
                   ((max_y - min_y) < capture_raw_min_pulse_height) ||
                   (min_y <= capture_raw_min) || (max_y >= capture_p_upper_limit))
               {
                  max_y = capture_p_upper_limit;
                  min_y = capture_raw_min;
                  frm_capture_pwv->chrt_pressure->LeftAxis->Minimum = 0;
                  frm_capture_pwv->chrt_pressure->LeftAxis->Maximum = max_y;
                  frm_capture_pwv->chrt_pressure->LeftAxis->Minimum = min_y;
                  frm_capture_pwv->lbl_level->Caption = LEVEL_CAPTION;
                  frm_capture_pwv->lbl_level_ecg->Caption = LEVEL_CAPTION;
               }
               else
               {
                  frm_capture_pwv->chrt_pressure->LeftAxis->Minimum = 0;
                  frm_capture_pwv->chrt_pressure->LeftAxis->Maximum = min_y + capture_raw_max_pulse_height;
                  frm_capture_pwv->chrt_pressure->LeftAxis->Minimum = min_y * 0.96;

               }
            }
         }
      }
   }
   else
   {
      displayed_ok = false;
      log_write("Comms, PWV Capture, Samples: = " +IntToStr(pressure_sample) +", " +IntToStr(ecg_sample));
      comms_stop();
      comms_close();
      frm_capture_pwv->ModalResult = mrNone;
      frm_capture_pwv->Close();
   }
   return (displayed_ok);
}



bool capture_pwa_add_sample(short int pressure_sample,
                            bool      is_data_valid,
                            bool      check_fswitch)
{
   const double      SRS_YMIN_VALUE = 1000.;
   double            max_y;
   double            min_y;
   int               xpos_srs_main;
   int               xpos_srs_secondary;
   bool              displayed_ok = true;
   bool              comms_failed = false;
   COMMS_ID_TYPE     port_id;
   static double     srs_max_y = 0.0;
   static double     srs_min_y = SRS_YMIN_VALUE;
   static int        i = 0;
   static short int  data_buff[20];
   RTOF_RECORD_TYPE  rtof;

   if (frm_capture_pwa == NULL)
   {
      log_write("Comms PWA Capture: Capture closed but received data");
      return false;
   }

   if (is_data_valid && (pressure_sample >= 0))
   {
      data_buff[i] = pressure_sample;
      ++i;
      if (i == 4)
      {
         frm_capture_pwa->srs_capture_main->AutoRepaint = false;
         frm_capture_pwa->srs_capture_secondary->AutoRepaint = false;
         i = 0;
         for (i = 0; i < 4; i++)
         {
            xpos_srs_main = frm_capture_pwa->srs_capture_main->Count();
            xpos_srs_secondary = frm_capture_pwa->srs_capture_secondary->Count();
            if (data_buff[i] > frm_capture_pwa->chrt_main->LeftAxis->Maximum)
            {
               srs_max_y = data_buff[i];
               frm_capture_pwa->srs_capture_main->AddXY(xpos_srs_main,
                                                        frm_capture_pwa->chrt_main->LeftAxis->Maximum,
                                                        "", clWhite);
            }
            else if (data_buff[i] < frm_capture_pwa->chrt_main->LeftAxis->Minimum)
            {
               srs_min_y = data_buff[i];
               frm_capture_pwa->srs_capture_main->AddXY(xpos_srs_main,
                                                        frm_capture_pwa->chrt_main->LeftAxis->Minimum,
                                                        "", clWhite);
            }
            else
            {
               frm_capture_pwa->srs_capture_main->AddXY(xpos_srs_main, data_buff[i], "", clWhite);
            }

            if ((i % 2) == 0)
            {
               //frm_capture_pwa->srs_capture_secondary->AutoRepaint = true;
               frm_capture_pwa->srs_capture_secondary->AddXY(xpos_srs_secondary, data_buff[i], "", clLime);
            }

            capture_ch1_buff[capture_circbuff_index] = data_buff[i];
            ++capture_circbuff_index;
            if (capture_circbuff_full == false)
            {
			   capture_circbuff_full = (capture_circbuff_index >= frm_capture_pwa->total_samples) ? true : false;
            }
            capture_circbuff_index %= frm_capture_pwa->total_samples;

            // PM V9
            // Calculate RTOF values for Radial measurements when at least 1 of
            // the RTOF options has been selected by the user
            if ((config_get_rtof() || config_get_auto_capture()) && frm_capture_pwa->pwa->MeasureType == PWA_RADIAL)
            {
               // If the display needs updating
               if (rtof_add_sample(data_buff[i]))
               {
                  if (rtof_get(&rtof) && config_get_rtof())
                  {
                     // Display guidance bars
                     frm_capture_pwa->srs_rtof_upper->Clear();
                     frm_capture_pwa->srs_rtof_lower->Clear();
                     frm_capture_pwa->srs_rtof_height->Clear();

                     if (rtof.upper_guidance_band != DEFAULT_VALUE)
                     {
                        frm_capture_pwa->srs_rtof_upper->AddXY(frm_capture_pwa->chrt_main->BottomAxis->Minimum, rtof.upper_guidance_band, "", clTeeColor);
                        frm_capture_pwa->srs_rtof_upper->AddXY(frm_capture_pwa->chrt_main->BottomAxis->Maximum, rtof.upper_guidance_band, "", clTeeColor);
                        frm_capture_pwa->srs_rtof_upper->SeriesColor =  rtof.pulse_height_variation_color;
                        frm_capture_pwa->srs_rtof_lower->AddXY(frm_capture_pwa->chrt_main->BottomAxis->Minimum, rtof.lower_guidance_band, "", clTeeColor);
                        frm_capture_pwa->srs_rtof_lower->AddXY(frm_capture_pwa->chrt_main->BottomAxis->Maximum, rtof.lower_guidance_band, "", clTeeColor);
                        frm_capture_pwa->srs_rtof_lower->SeriesColor =  rtof.baseline_variation_color;
                        frm_capture_pwa->srs_rtof_height->AddXY(frm_capture_pwa->chrt_main->BottomAxis->Maximum, rtof.upper_guidance_band, "", clTeeColor);
                        frm_capture_pwa->srs_rtof_height->AddXY(frm_capture_pwa->chrt_main->BottomAxis->Maximum, rtof.lower_guidance_band, "", clTeeColor);
                        frm_capture_pwa->srs_rtof_height->SeriesColor =  rtof.pulse_height_color;
                     }
                     // Display hints
                     frm_capture_pwa->lbl_pulse_height_variation->Caption = rtof.pulse_height_variation_label;
                     frm_capture_pwa->lbl_baseline_variation->Caption = rtof.baseline_variation_label;
                     frm_capture_pwa->lbl_pulse_height->Caption = rtof.pulse_height_label;
                     frm_capture_pwa->srs_capture_main->SeriesColor = rtof.waveform_color;
                     if (rtof.waveform_color == clWhite)
                     {
                        frm_capture_pwa->srs_capture_main->LinePen->Width = 1;
                     }
                     else
                     {
                        frm_capture_pwa->srs_capture_main->LinePen->Width = 2;
                     }
                     //Beep();
                  }
		         }
            }
         }

         i = 0;
         xpos_srs_main = frm_capture_pwa->srs_capture_main->Count();
         xpos_srs_secondary = frm_capture_pwa->srs_capture_secondary->Count();
         // We are displaying every second point
         xpos_srs_secondary = xpos_srs_secondary * 2;
         if (xpos_srs_secondary >= frm_capture_pwa->total_samples)
         {
            if (xpos_srs_secondary >= frm_capture_pwa->display_reset)
            {
               frm_capture_pwa->srs_capture_secondary->AutoRepaint = true;
               frm_capture_pwa->srs_capture_secondary->Clear();
               frm_capture_pwa->chrt_secondary->BottomAxis->SetMinMax(0, frm_capture_pwa->total_samples / 2);
               xpos_srs_secondary = 0;
            }
            else
            {
               if (((xpos_srs_secondary - frm_capture_pwa->total_samples) % frm_capture_pwa->pwa->SampleRate) == 0)
               {
                  min_y = frm_capture_pwa->srs_capture_main->MinYValue();
                  max_y = frm_capture_pwa->srs_capture_main->MaxYValue();

                  if (max_y == min_y)
                  {
                     max_y = capture_p_upper_limit;
                     min_y = capture_raw_min;
                  }
                  else
                  {
                     max_y = max_y * 1.04;
                     min_y = min_y * 0.96;
                  }

                  frm_capture_pwa->srs_capture_secondary->AutoRepaint = true;
                  frm_capture_pwa->chrt_secondary->BottomAxis->Scroll(frm_capture_pwa->pwa->SampleRate / 2, false);

                  frm_capture_pwa->chrt_secondary->LeftAxis->SetMinMax(min_y, max_y);
                  frm_capture_pwa->chrt_secondary->LeftAxis->Automatic = false;

               }
            }
         }
         if (xpos_srs_main >= frm_capture_pwa->display_resolution)
         {
            frm_capture_pwa->srs_capture_main->AutoRepaint = true;
            max_y = frm_capture_pwa->srs_capture_main->MaxYValue();
            min_y = frm_capture_pwa->srs_capture_main->MinYValue();

            if (max_y != min_y && min_y > capture_raw_min)
            {
               if (srs_max_y != 0.0)
               {
                  max_y = srs_max_y;
               }


               if (srs_min_y != SRS_YMIN_VALUE)
               {
                  min_y = srs_min_y;
               }
            }
            srs_max_y = 0.0;
            srs_min_y = SRS_YMIN_VALUE;

            frm_capture_pwa->srs_capture_main->Clear();
            xpos_srs_main = 0;
            frm_capture_pwa->lbl_level->Caption = RoundIntToStr(max_y - min_y);

            if ((max_y > frm_capture_pwa->chrt_main->LeftAxis->Maximum) ||
                (min_y < frm_capture_pwa->chrt_main->LeftAxis->Minimum) ||
                ((max_y -  min_y) > capture_raw_max_pulse_height) || ((max_y - min_y) < capture_raw_min_pulse_height) ||
                (frm_capture_pwa->chrt_main->LeftAxis->Maximum >= capture_p_upper_limit))
            {
               frm_capture_pwa->chrt_main->LeftAxis->Automatic = false;

               if (((max_y - min_y) > capture_raw_max_pulse_height) ||
                   ((max_y - min_y) < capture_raw_min_pulse_height) ||
                   (min_y <= capture_raw_min) || (max_y >= capture_p_upper_limit))
               {
                  max_y = capture_p_upper_limit;
                  min_y = capture_raw_min;
                  frm_capture_pwa->chrt_main->LeftAxis->Minimum = 0;
                  frm_capture_pwa->chrt_main->LeftAxis->Maximum = max_y;
                  frm_capture_pwa->chrt_main->LeftAxis->Minimum = min_y;
                  frm_capture_pwa->lbl_level->Caption = LEVEL_CAPTION;
               }
               else
               {
                  frm_capture_pwa->chrt_main->LeftAxis->Minimum = 0;
                  frm_capture_pwa->chrt_main->LeftAxis->Maximum = min_y + capture_raw_max_pulse_height;
                  frm_capture_pwa->chrt_main->LeftAxis->Minimum = min_y * 0.96;
               }
            }
         }
      }
   }
   else
   {
      displayed_ok = false;
      comms_stop();
      log_write("Comms PWA Capture: Sample = " +IntToStr(pressure_sample));
      capture_reset(MEAS_PWA_ID);
      if (MsgBox(LoadStr(MSG_COMMS_COMMUNICATIONS_PROBLEM) + LoadStr(MSG_COMMS_TRY_AGAIN),
                 SCONFIRMATION,
                 MB_YESNO | MB_ICONQUESTION) == ID_YES)
      {
         port_id = config_get_comms_port();

         if (port_id == COMMS_PORT_USB)
         {
            comms_close();
            if (!comms_open(port_id))
            {
               comms_failed = true;
            }
         }
         if (!comms_failed)
         {
            if (comms_start(MEAS_PWA_ID))
            {
               frm_capture_pwa->tmr_capture->Enabled = true;
            }
            else
            {
               comms_failed = true;
            }
         }
      }
      else
      {
         comms_failed = true;
      }
      if (comms_failed)
      {
         comms_close();
         frm_capture_pwa->ModalResult = mrNone;
         frm_capture_pwa->Close();
      }
   }
   return (displayed_ok);
}

bool capture_pwm_add_sample(short int   pressure_sample,
                            bool        is_data_valid,
                            bool        check_fswitch)
{
   const double   SRS_YMIN_VALUE = 1000.;
   double         max_y;
   double         min_y;
   double         central_pressure_sample;
   double         calibrated_pressure_value;
   double         digital_value;
   float          pwm_cal_factor;
   float          pwm_cal_offset;
   float          actual_display_val;
   float          time_val;
   int            xpos_srs_main;
   int            j;
   bool           displayed_ok = true;
   short int      *pressure_data;
   short int      the_pressure_sample;
   UINT16         send_pressure_data[8];
   COUNT          input_correction_factor = 0;
   COUNT          output_correction_factor = 0;
   static double  srs_max_y = 0.0;
   static double  srs_min_y = SRS_YMIN_VALUE;
   static int     i = 0;
   static unsigned int data_buff[2][10];

   if (is_data_valid && (pressure_sample >= 0))
   {
      pwm_cal_factor = 1.0;
      pwm_cal_offset = 0.0;
      if (capture_calibrated)
      {
         input_correction_factor = capture_get_calibration_factor(CAPTURE_PWM_INPUT_CHANNEL);

         pwm_cal_factor = frm_capture_pwm->pwm->CalibrationRatio;
         if (pwm_cal_factor == 0.)
         {
            pwm_cal_factor = 1.0;
         }
         pwm_cal_offset = frm_capture_pwm->pwm->CalibrationOffset / pwm_cal_factor;
         the_pressure_sample = pressure_sample - input_correction_factor;
         digital_value = the_pressure_sample;
         calibrated_pressure_value = (((the_pressure_sample - 2048) / 409.6) / pwm_cal_factor) + pwm_cal_offset;
         if (calibrated_pressure_value < 0.)
         {
            calibrated_pressure_value = 0.;
         }
         if ((pwm_cal_factor == 1.0) && (pwm_cal_offset == 0.0))
         {
             calibrated_pressure_value = pressure_sample;
         }
         the_pressure_sample = calibrated_pressure_value;
      }
      else
      {
         if (capture_tonometer)
         {
            the_pressure_sample = pressure_sample;
         }
         else
         {
            input_correction_factor = capture_get_calibration_factor(CAPTURE_PWM_INPUT_CHANNEL);
            the_pressure_sample = pressure_sample - input_correction_factor;
         }

      }
      data_buff[0][i] = the_pressure_sample;
      frm_capture_pwm->pwm->StoreSignalPacket(&the_pressure_sample, 1);
      central_pressure_sample = frm_capture_pwm->pwm->GetAorticValue();
      if (central_pressure_sample < 0)
      {
         central_pressure_sample = 0;
      }
      data_buff[1][i] = central_pressure_sample;
      if ((frm_capture_pwm->pwm->AorticSendOut || frm_capture_pwm->pwm->PeriphSendOut) &&
          comms_is_module_12bit())
      {
         j = 0;
         if (frm_capture_pwm->pwm->PeriphSendOut)
         {
            output_correction_factor = capture_get_calibration_factor(CAPTURE_PWM_OUTPUT_CHANNEL_ONE);
            if (capture_calibrated)
            {
               send_pressure_data[j] = digital_value - output_correction_factor;
            }
            else
            {
               send_pressure_data[j] = data_buff[0][i] - output_correction_factor;
            }
         }
         else
         {
            send_pressure_data[j] = 0;
         }
         ++j;
         if (frm_capture_pwm->pwm->AorticSendOut)
         {
            output_correction_factor = capture_get_calibration_factor(CAPTURE_PWM_OUTPUT_CHANNEL_TWO);
            if (capture_calibrated)
            {
               digital_value = (409.6 * pwm_cal_factor * (data_buff[1][i] - pwm_cal_offset)) + 2048;
               send_pressure_data[j] = digital_value - output_correction_factor;
            }
            else
            {
               send_pressure_data[j] = data_buff[1][i] - output_correction_factor;
            }
         }
         else
         {
            send_pressure_data[j] = 0;
         }
         ++j;
         comms_send(send_pressure_data, j);
      }
      ++i;
      if (i == 4)
      {
         capture_raw_value = the_pressure_sample;

         frm_capture_pwm->srs_central_pressure->AutoRepaint = false;
         frm_capture_pwm->srs_periph_pressure->AutoRepaint = false;
         i = 0;
         for (i = 0; i < 4; i++)
         {
            xpos_srs_main = frm_capture_pwm->srs_periph_pressure->Count();
            time_val = xpos_srs_main / (float)frm_capture_pwm->pwm->SampleRate;
            if (data_buff[0][i] > frm_capture_pwm->chrt_pressure->LeftAxis->Maximum)
            {
               srs_max_y = data_buff[0][i];
               frm_capture_pwm->srs_periph_pressure->AddXY(time_val,
                                                           srs_max_y,
                                                           "", clWhite);
            }
            else if (data_buff[0][i] < frm_capture_pwm->chrt_pressure->LeftAxis->Minimum)
            {
               srs_min_y = data_buff[0][i];
               frm_capture_pwm->srs_periph_pressure->AddXY(time_val,
                                                           frm_capture_pwm->chrt_pressure->LeftAxis->Minimum,
                                                           "", clWhite);
            }
            else
            {
               frm_capture_pwm->srs_periph_pressure->AddXY(time_val,
                                                           data_buff[0][i],
                                                           "", clWhite);
            }
            frm_capture_pwm->srs_central_pressure->AddXY(time_val,
                                                         data_buff[1][i],
                                                         "", clYellow);
            capture_ch1_buff[capture_circbuff_index] = (short int) data_buff[0][i];
            ++capture_circbuff_index;
            if (capture_circbuff_full == false)
            {
      		   capture_circbuff_full = (capture_circbuff_index >= frm_capture_pwm->total_samples) ? true : false;
            }
            capture_circbuff_index %= frm_capture_pwm->total_samples;
         }

         i = 0;
         xpos_srs_main = frm_capture_pwm->srs_periph_pressure->Count();

         if (xpos_srs_main >= frm_capture_pwm->display_resolution ||
            ((xpos_srs_main > 0) && (xpos_srs_main % frm_capture_pwm->display_rescale == 0)))
         {
            frm_capture_pwm->srs_periph_pressure->AutoRepaint = true;
            frm_capture_pwm->srs_central_pressure->AutoRepaint = true;

            max_y = frm_capture_pwm->srs_periph_pressure->MaxYValue();
            min_y = frm_capture_pwm->srs_periph_pressure->MinYValue();

            if (frm_capture_pwm->pwm->TrendSamplePeriod &&
               (xpos_srs_main >= frm_capture_pwm->display_resolution))
            {
               pressure_data = new short int[frm_capture_pwm->display_resolution];
               for (int j = 0; j < frm_capture_pwm->srs_periph_pressure->Count(); j++)
               {
                  pressure_data[j] = (short int)(frm_capture_pwm->srs_periph_pressure->YValues->Value[j]);
               }
               frm_capture_pwm->pwm->PrepareToCaptureSignal();
               frm_capture_pwm->pwm->Periph.CaptureSignal(pressure_data,
                                                       frm_capture_pwm->srs_periph_pressure->Count());

               // Only calculate once the "Start Session" button has been clicked
               if (!frm_capture_pwm->bbtn_start->Enabled)
               {

                  if (frm_capture_pwm->pwm->Calculate(true))
                  {
                     delete [] pressure_data;

                     String lErrorString = "";
                     int lNofStored = frm_capture_pwm->pwm->StoreParamsToFile(lErrorString);
                     frm_capture_pwm->pwm->EventMarker = DEFAULT_VALUE;
                     if (lNofStored <= 0)
                     {
                        ShowMessage(lErrorString);
                     }

                     if (frm_capture_pwm->pwm->Periph.Sp < DEFAULT_VALUE)
                     {
                        frm_capture_pwm->srs_periph_sp->AddXY(frm_capture_pwm->trend_counter,
                                                        frm_capture_pwm->pwm->Periph.Sp,
                                                        "", frm_capture_pwm->srs_periph_sp->SeriesColor);
                     }
                     else
                     {
                        frm_capture_pwm->srs_periph_sp->AddNull("");
                     }

                     if (frm_capture_pwm->pwm->Periph.Dp < DEFAULT_VALUE)
                     {
                        frm_capture_pwm->srs_periph_dp->AddXY(frm_capture_pwm->trend_counter,
                                                        frm_capture_pwm->pwm->Periph.Dp,
                                                        "", frm_capture_pwm->srs_periph_dp->SeriesColor);
                     }
                     else
                     {
                        frm_capture_pwm->srs_periph_dp->AddNull("");
                     }

                     if (frm_capture_pwm->pwm->Periph.Dp < DEFAULT_VALUE &&
                         frm_capture_pwm->pwm->Periph.Sp < DEFAULT_VALUE)
                     {
                        frm_capture_pwm->srs_periph_pp->AddXY(frm_capture_pwm->trend_counter,
                                                        frm_capture_pwm->pwm->Periph.Sp - frm_capture_pwm->pwm->Periph.Dp,
                                                        "", frm_capture_pwm->srs_periph_pp->SeriesColor);
                     }
                     else
                     {
                        frm_capture_pwm->srs_periph_pp->AddNull("");
                     }

                     if (frm_capture_pwm->pwm->Central.Sp < DEFAULT_VALUE)
                     {
                        frm_capture_pwm->srs_central_sp->AddXY(frm_capture_pwm->trend_counter,
                                                         frm_capture_pwm->pwm->Central.Sp,
                                                         "", frm_capture_pwm->srs_central_sp->SeriesColor);
                     }
                     else
                     {
                        frm_capture_pwm->srs_central_sp->AddNull("");
                     }

                     if (frm_capture_pwm->pwm->Central.Dp < DEFAULT_VALUE)
                     {
                        frm_capture_pwm->srs_central_dp->AddXY(frm_capture_pwm->trend_counter,
                                                            frm_capture_pwm->pwm->Central.Dp,
                                                            "", frm_capture_pwm->srs_central_dp->SeriesColor);
                     }
                     else
                     {
                        frm_capture_pwm->srs_central_dp->AddNull("");
                     }

                     if (frm_capture_pwm->pwm->Central.PH < DEFAULT_VALUE)
                     {
                        frm_capture_pwm->srs_central_pp->AddXY(frm_capture_pwm->trend_counter,
                                                         frm_capture_pwm->pwm->Central.PH,
                                                         "", frm_capture_pwm->srs_central_pp->SeriesColor);
                     }
                     else
                     {
                        frm_capture_pwm->srs_central_pp->AddNull("");
                     }

                     if (frm_capture_pwm->pwm->Central.AP < DEFAULT_VALUE)
                     {
                        frm_capture_pwm->srs_central_ap->AddXY(frm_capture_pwm->trend_counter,
                                                         frm_capture_pwm->pwm->Central.AP,
                                                         "", frm_capture_pwm->srs_central_ap->SeriesColor);
                     }
                     else
                     {
                        frm_capture_pwm->srs_central_ap->AddNull("");
                     }

                     if (frm_capture_pwm->pwm->Periph.MeanP < DEFAULT_VALUE)
                     {
                        frm_capture_pwm->srs_mp->AddXY(frm_capture_pwm->trend_counter,
                                                 frm_capture_pwm->pwm->Periph.MeanP,
                                                 "", frm_capture_pwm->srs_mp->SeriesColor);
                     }
                     else
                     {
                        frm_capture_pwm->srs_mp->AddNull("");
                     }


                     if (frm_capture_pwm->pwm->Central.HR < DEFAULT_VALUE)
                     {
                        frm_capture_pwm->srs_cardiac_period->AddXY(frm_capture_pwm->trend_counter,
                                                             frm_capture_pwm->pwm->Central.HR,
                                                             "", clTeeColor);
                        frm_capture_pwm->ChartHR->Title->Text->Strings[0] =
                        frm_capture_pwm->ChartHRTitle + ": " + RoundIntToStr(frm_capture_pwm->pwm->Central.HR);
                     }
                     else
                     {
                        frm_capture_pwm->srs_cardiac_period->AddNull("");
                        frm_capture_pwm->ChartHR->Title->Text->Strings[0] =
                        frm_capture_pwm->ChartHRTitle + ": n/c";
                     }

                     if (frm_capture_pwm->pwm->Central.SVI >= DEFAULT_VALUE)
                     {
                        frm_capture_pwm->srs_sevr->AddNull("");
                        frm_capture_pwm->ChartSEVR->Title->Text->Strings[0] =
                        frm_capture_pwm->ChartSEVRTitle + ": n/c";
                     }
                     else
                     {
                        frm_capture_pwm->srs_sevr->AddXY(frm_capture_pwm->trend_counter,
                                                   frm_capture_pwm->pwm->Central.SVI,
                                                   "", clTeeColor);
                        frm_capture_pwm->ChartSEVR->Title->Text->Strings[0] =
                        frm_capture_pwm->ChartSEVRTitle + ": " + RoundIntToStr(frm_capture_pwm->pwm->Central.SVI);
                     }

                     if (frm_capture_pwm->pwm->Central.ED >= DEFAULT_VALUE)
                     {
                        frm_capture_pwm->srs_ed->AddNull("");
                        frm_capture_pwm->ChartED->Title->Text->Strings[0] =
                        frm_capture_pwm->ChartEDTitle + ": n/c";
                     }
                     else
                     {
                        frm_capture_pwm->srs_ed->AddXY(frm_capture_pwm->trend_counter,
                                                 frm_capture_pwm->pwm->Central.ED,
                                                 "", clTeeColor);
                        frm_capture_pwm->ChartED->Title->Text->Strings[0] =
                        frm_capture_pwm->ChartEDTitle + " : " + RoundIntToStr(frm_capture_pwm->pwm->Central.ED);
                     }

                     if (frm_capture_pwm->pwm->Central.AGPH >= DEFAULT_VALUE)
                     {
                        frm_capture_pwm->srs_augx->AddNull("");
                        frm_capture_pwm->ChartAI->Title->Text->Strings[0] =
                        frm_capture_pwm->ChartAITitle + ": n/c";
                     }
                     else
                     {
                        frm_capture_pwm->srs_augx->AddXY(frm_capture_pwm->trend_counter,
                                                   frm_capture_pwm->pwm->Central.AGPH,
                                                   "", clTeeColor);
                        frm_capture_pwm->ChartAI->Title->Text->Strings[0] =
                        frm_capture_pwm->ChartAITitle + ": " + RoundIntToStr(frm_capture_pwm->pwm->Central.AGPH);
                     }

                     if (frm_capture_pwm->pwm->Periph.Sp < DEFAULT_VALUE)
                     {
                        frm_capture_pwm->lbl_psp->Caption = RoundIntToStr(frm_capture_pwm->pwm->Periph.Sp);
                     }
                     else
                     {
                        frm_capture_pwm->lbl_psp->Caption = "???";
                     }

                     if (frm_capture_pwm->pwm->Periph.Dp < DEFAULT_VALUE)
                     {
                        frm_capture_pwm->lbl_pdp->Caption = RoundIntToStr(frm_capture_pwm->pwm->Periph.Dp);
                     }
                     else
                     {
                        frm_capture_pwm->lbl_pdp->Caption = "???";
                     }

                     if (frm_capture_pwm->pwm->Central.Sp < DEFAULT_VALUE)
                     {
                        frm_capture_pwm->lbl_csp->Caption = RoundIntToStr(frm_capture_pwm->pwm->Central.Sp);
                     }
                     else
                     {
                        frm_capture_pwm->lbl_csp->Caption = "???";
                     }

                     if (frm_capture_pwm->pwm->Central.Dp < DEFAULT_VALUE)
                     {
                        frm_capture_pwm->lbl_cdp->Caption = RoundIntToStr(frm_capture_pwm->pwm->Central.Dp);
                     }
                     else
                     {
                        frm_capture_pwm->lbl_cdp->Caption = "???";
                     }

                     if (frm_capture_pwm->pwm->Periph.Sp < DEFAULT_VALUE &&
                        frm_capture_pwm->pwm->Periph.Dp < DEFAULT_VALUE)
                     {
                        frm_capture_pwm->pnl_ppp->Caption = RoundIntToStr(frm_capture_pwm->pwm->Periph.Sp
                                                                    - frm_capture_pwm->pwm->Periph.Dp);
                     }
                     else
                     {
                        frm_capture_pwm->pnl_ppp->Caption = "???";
                     }

                     if (frm_capture_pwm->pwm->Central.PH < DEFAULT_VALUE)
                     {
                        frm_capture_pwm->pnl_cpp->Caption = RoundIntToStr(frm_capture_pwm->pwm->Central.PH);
                     }
                     else
                     {
                        frm_capture_pwm->pnl_cpp->Caption = "???";
                     }

                     if (frm_capture_pwm->pwm->Periph.MeanP < DEFAULT_VALUE)
                     {
                        frm_capture_pwm->pnl_mp->Caption = RoundIntToStr(frm_capture_pwm->pwm->Periph.MeanP);
                     }
                     else
                     {
                        frm_capture_pwm->pnl_mp->Caption = "???";
                     }

                     ++frm_capture_pwm->trend_counter;
                     ++frm_capture_pwm->calculated_trend_counter;
                     if (frm_capture_pwm->display_trend_refresh_rate)
                     {
                        if (frm_capture_pwm->trend_counter % frm_capture_pwm->display_trend_refresh_rate == 0)
                        {
                           frm_capture_pwm->chrt_trend_pressure->BottomAxis->SetMinMax(0, frm_capture_pwm->trend_counter + frm_capture_pwm->display_trend_refresh_rate);
                           frm_capture_pwm->ChartHR->BottomAxis->SetMinMax(0, frm_capture_pwm->trend_counter + frm_capture_pwm->display_trend_refresh_rate);
                           frm_capture_pwm->ChartSEVR->BottomAxis->SetMinMax(0, frm_capture_pwm->trend_counter + frm_capture_pwm->display_trend_refresh_rate);
                           frm_capture_pwm->ChartED->BottomAxis->SetMinMax(0, frm_capture_pwm->trend_counter + frm_capture_pwm->display_trend_refresh_rate);
                           frm_capture_pwm->ChartAI->BottomAxis->SetMinMax(0, frm_capture_pwm->trend_counter + frm_capture_pwm->display_trend_refresh_rate);
                        }
                     }
                  }
                  else
                  {
                     delete [] pressure_data;
                     String parameter_string = "";
                     frm_capture_pwm->pwm->StoreParamsToFile(parameter_string);

                     frm_capture_pwm->lbl_psp->Caption = "???";
                     frm_capture_pwm->lbl_pdp->Caption = "???";
                     frm_capture_pwm->lbl_csp->Caption = "???";
                     frm_capture_pwm->lbl_cdp->Caption = "???";
                     frm_capture_pwm->pnl_cpp->Caption = "???";
                     frm_capture_pwm->pnl_ppp->Caption = "???";
                     frm_capture_pwm->pnl_mp->Caption = "???";

                     frm_capture_pwm->ChartHR->Title->Text->Strings[0] =
                        frm_capture_pwm->ChartHRTitle + ": ???";

                     frm_capture_pwm->ChartED->Title->Text->Strings[0] =
                        frm_capture_pwm->ChartEDTitle + ": ???";

                     frm_capture_pwm->ChartSEVR->Title->Text->Strings[0] =
                        frm_capture_pwm->ChartSEVRTitle + ": ???";

                     frm_capture_pwm->ChartAI->Title->Text->Strings[0] =
                        frm_capture_pwm->ChartAITitle + ": ???";

                     frm_capture_pwm->srs_periph_sp->AddNull("");
                     frm_capture_pwm->srs_periph_dp->AddNull("");
                     frm_capture_pwm->srs_central_sp->AddNull("");
                     frm_capture_pwm->srs_central_dp->AddNull("");
                     frm_capture_pwm->srs_central_ap->AddNull("");

                     frm_capture_pwm->srs_cardiac_period->AddNull("");
                     frm_capture_pwm->srs_sevr->AddNull("");
                     frm_capture_pwm->srs_ed->AddNull("");
                     frm_capture_pwm->srs_augx->AddNull("");
                     frm_capture_pwm->pwm->EventMarker = DEFAULT_VALUE;
                     ++frm_capture_pwm->trend_counter;

                     if (frm_capture_pwm->display_trend_refresh_rate)
                     {
                        if (frm_capture_pwm->trend_counter % frm_capture_pwm->display_trend_refresh_rate == 0)
                        {
                           frm_capture_pwm->chrt_trend_pressure->BottomAxis->SetMinMax(0, frm_capture_pwm->trend_counter + frm_capture_pwm->display_trend_refresh_rate);
                           frm_capture_pwm->ChartHR->BottomAxis->SetMinMax(0, frm_capture_pwm->trend_counter + frm_capture_pwm->display_trend_refresh_rate);
                           frm_capture_pwm->ChartSEVR->BottomAxis->SetMinMax(0, frm_capture_pwm->trend_counter + frm_capture_pwm->display_trend_refresh_rate);
                           frm_capture_pwm->ChartED->BottomAxis->SetMinMax(0, frm_capture_pwm->trend_counter + frm_capture_pwm->display_trend_refresh_rate);
                           frm_capture_pwm->ChartAI->BottomAxis->SetMinMax(0, frm_capture_pwm->trend_counter + frm_capture_pwm->display_trend_refresh_rate);
                        }
                     }
                  }
               }
            }

            if ((max_y != min_y) && (min_y > capture_raw_min))
            {
               if (srs_max_y != 0.0)
               {
                  max_y = srs_max_y;
               }

               if (srs_min_y != SRS_YMIN_VALUE)
               {
                  min_y = srs_min_y;
               }
            }
            srs_max_y = 0.0;
            srs_min_y = SRS_YMIN_VALUE;

            if (xpos_srs_main >= frm_capture_pwm->display_resolution)
            {
               frm_capture_pwm->srs_periph_pressure->Clear();
               frm_capture_pwm->srs_central_pressure->Clear();
               xpos_srs_main = 0;
            }

            if ((max_y > frm_capture_pwm->chrt_pressure->LeftAxis->Maximum) ||
                (min_y < frm_capture_pwm->chrt_pressure->LeftAxis->Minimum) ||
                ((max_y -  min_y) > capture_raw_max_pulse_height) ||
                ((max_y - min_y) < capture_raw_min_pulse_height) ||
                (frm_capture_pwm->chrt_pressure->LeftAxis->Maximum >= capture_p_upper_limit))
            {
               frm_capture_pwm->chrt_pressure->LeftAxis->Automatic = false;

               if (((max_y - min_y) > (capture_raw_max_pulse_height)) ||
                   ((max_y - min_y) < capture_raw_min_pulse_height) ||
                   (min_y <= capture_raw_min) ||
                   (max_y >= capture_p_upper_limit))
               {
                  max_y = capture_p_upper_limit;
                  min_y = capture_raw_min;
                  frm_capture_pwm->chrt_pressure->LeftAxis->Minimum = 0;
                  frm_capture_pwm->chrt_pressure->LeftAxis->Maximum = max_y;
                  frm_capture_pwm->chrt_pressure->LeftAxis->Minimum = min_y;

                  frm_capture_pwm->chrt_pressure->RightAxis->Minimum = 0;
                  frm_capture_pwm->chrt_pressure->RightAxis->Maximum = max_y;
                  frm_capture_pwm->chrt_pressure->RightAxis->Minimum = min_y;
               }
               else
               {
                  frm_capture_pwm->chrt_pressure->LeftAxis->Minimum = 0;
                  frm_capture_pwm->chrt_pressure->LeftAxis->Maximum = min_y + (max_y - min_y) * 1.2; //(capture_raw_max_pulse_height);
                  frm_capture_pwm->chrt_pressure->LeftAxis->Minimum = min_y * 0.96;

                  frm_capture_pwm->chrt_pressure->RightAxis->Minimum = 0;
                  frm_capture_pwm->chrt_pressure->RightAxis->Maximum = min_y + (max_y - min_y) * 1.2; //(capture_raw_max_pulse_height);
                  frm_capture_pwm->chrt_pressure->RightAxis->Minimum = min_y * 0.96;
               }
            }
            else
            {
               if (((max_y * 1.25) < frm_capture_pwm->chrt_pressure->LeftAxis->Maximum) ||
                   ((min_y * 0.75) > frm_capture_pwm->chrt_pressure->LeftAxis->Minimum))
               {
                  frm_capture_pwm->chrt_pressure->LeftAxis->Minimum = 0;
                  frm_capture_pwm->chrt_pressure->LeftAxis->Maximum = max_y * 1.2;
                  frm_capture_pwm->chrt_pressure->LeftAxis->Minimum = min_y * 0.8;

                  frm_capture_pwm->chrt_pressure->RightAxis->Minimum = 0;
                  frm_capture_pwm->chrt_pressure->RightAxis->Maximum = max_y * 1.2;
                  frm_capture_pwm->chrt_pressure->RightAxis->Minimum = min_y * 0.8;
               }
            }
         }
      }
   }
   else
   {
      displayed_ok = false;
      msg_enable_messages();
      frm_capture_pwm->tmr_capture->Enabled = false;
      comms_stop();
      comms_display_error();
      if ((capture_circbuff_full && frm_capture_pwm->calculated_trend_counter > 1) || frm_capture_pwm->pwm->TrendSamplePeriod == 0)
      {
         if (MsgBox(LoadStr(MSG_COMMS_COMMUNICATIONS_PROBLEM) +"\n\nWould you like to save and process the data you have captured thus far ?",
                            SCONFIRMATION,
                            MB_YESNO | MB_ICONQUESTION) == ID_YES)
         {
            capture_reset(MEAS_PWM_ID);
            comms_close();
            frm_capture_pwm->ModalResult = mrOk;
         }
         else
         {
            capture_reset(MEAS_PWM_ID);
            comms_close();
            frm_capture_pwm->ModalResult = mrNone;
            frm_capture_pwm->Close();
         }
      }
      else
      {
         capture_reset(MEAS_PWM_ID);
         comms_close();
         frm_capture_pwm->ModalResult = mrNone;
         frm_capture_pwm->Close();
      }
   }
   return (displayed_ok);
}


bool capture_hrv_add_sample(short int  *ecg_sample,
                            UTINY      ecg_buff_len,
                            bool       is_data_valid,
                            bool       check_fswitch)
{
   const double   SRS_YMIN_VALUE = 1000.;
   int            xpos_srs_ecg = 0;
   bool           displayed_ok = true;
   bool           ecg_samples_valid;
   static int     i = 0;
   static float   data_buff[32];
   UINT16         output_data[8];
   float          *ecg_data;
   double         time_x;
   int            prev_segments;
   int            t_min;
   int            t_sec;
   double         max_y;
   double         min_y;
   double         max_ecg_y;
   double         min_ecg_y;
   static double  srs_min_y = SRS_YMIN_VALUE;
   Word           hour, min, sec, msec;

   if (frm_capture_hrv == NULL)
   {
      log_write("Comms HRV Capture: Capture closed but received data");
      return false;
   }

   if (is_data_valid)
   {
      if (frm_capture_hrv->bbtn_calculate->Enabled)
      {
         if (comms_get_footswitch_status() == COMMS_FOOTSWITCH_ONE)
         {
            comms_stop();
            displayed_ok = true;
            frm_capture_hrv->bbtn_calculateClick(Application);
            return (displayed_ok);
         }
      }
   }

   ecg_samples_valid = true;
   for (int j = 0; j < ecg_buff_len; j++)
   {
      if (ecg_sample[j] < 0)
      {
         ecg_samples_valid = false;
      }

   }
   if (is_data_valid && ecg_samples_valid)
   {
      for (int j = 0; j < ecg_buff_len; j++)
      {
         data_buff[i * 8 + j] = ecg_sample[j] * 1.0;
      }
      ++i;

      if (i == 4)
      {

         time_x = 0.0;
         frm_capture_hrv->srs_ecg->AutoRepaint = false;
         frm_capture_hrv->srs_rtor_interval->AutoRepaint = false;

         i = 0;
         xpos_srs_ecg = frm_capture_hrv->srs_ecg->Count();
         for (int k = 0; k < 4; k++)
         {
            for (int j = 0; j < 8; j++)
            {
               time_x = (float)(((float)xpos_srs_ecg + ((float)k * (float)8.0 + (float)j)) / 1024.0);

               frm_capture_hrv->srs_ecg->AddXY(time_x, data_buff[k * 8 + j], "", clTeeColor);
            }
         }
         xpos_srs_ecg = frm_capture_hrv->srs_ecg->Count();
         if (xpos_srs_ecg >= frm_capture_hrv->display_resolution)
         {
            frm_capture_hrv->srs_ecg->AutoRepaint = true;
            max_y = frm_capture_hrv->srs_ecg->MaxYValue();
            min_y = frm_capture_hrv->srs_ecg->MinYValue();

            // If the signal is flat or outside the capture range, then display the maximum range
            if (max_y == min_y || max_y > CAPTURE_MAX_RAW_VALUE || min_y < CAPTURE_MIN_RAW_VALUE)
            {
               max_y = CAPTURE_MAX_RAW_VALUE;
               min_y = CAPTURE_MIN_RAW_VALUE;
               frm_capture_hrv->chrt_ecg_monitor->LeftAxis->SetMinMax(min_y, max_y);
               frm_capture_hrv->chrt_ecg_monitor->LeftAxis->Automatic = false;
            }

            // If the signal moves outside the display range or the display is at the maximum range,
            // then set the display to the signal height plus the buffer
            else if (max_y > frm_capture_hrv->chrt_ecg_monitor->LeftAxis->Maximum ||
                     min_y < frm_capture_hrv->chrt_ecg_monitor->LeftAxis->Minimum ||
                     frm_capture_hrv->chrt_ecg_monitor->LeftAxis->Maximum == CAPTURE_MAX_RAW_VALUE)
            {
               max_y = max_y + CAPTURE_HRV_BUFFER;
               min_y = min_y - CAPTURE_HRV_BUFFER;
               if (max_y > CAPTURE_MAX_RAW_VALUE)
               {
                  max_y = CAPTURE_MAX_RAW_VALUE;
               }
               if (min_y < CAPTURE_MIN_RAW_VALUE)
               {
                  min_y = CAPTURE_MIN_RAW_VALUE;
               }
               frm_capture_hrv->chrt_ecg_monitor->LeftAxis->SetMinMax(min_y, max_y);
               frm_capture_hrv->chrt_ecg_monitor->LeftAxis->Automatic = false;
            }

            // Begin the data capture when the start session button is disabled
            if (!frm_capture_hrv->bbtn_start_session->Enabled)
            {
               ecg_data = new float[frm_capture_hrv->display_resolution * 8];
               for (int j = 0; j < frm_capture_hrv->srs_ecg->Count(); j++)
               {
                  ecg_data[j] = frm_capture_hrv->srs_ecg->YValues->Value[j];
               }

               frm_capture_hrv->capture_hrv->PrepareToCaptureSignal();
               frm_capture_hrv->capture_hrv->ecg.CaptureSignal(ecg_data,
                                                               frm_capture_hrv->srs_ecg->Count());

               delete [] ecg_data;
               if (frm_capture_hrv->capture_hrv->CalculatePulses())
               {
                  int count = 0;
                  int x_scale;
                  int nof_pulses = 0;
                  TDateTime dt = EncodeTime(0, 0, 5, 0);//frm_capture_hrv->capture_baro->device.trend_sample_period, 0);
                  int prev_segments = frm_capture_hrv->srs_rtor_interval->Count();

                  // At the end of the first sweep, store the start time and enable the calculate button
                  if (frm_capture_hrv->first_time)
                  {
                     frm_capture_hrv->capture_hrv->StartTime = Now() - dt;
                     if (frm_capture_hrv->capture_hrv->MeasureType == HRV_NORMAL)
                     {
                        frm_capture_hrv->bbtn_calculate->Enabled = true;
                     }
                     frm_capture_hrv->first_time = false;
                  }

                  x_scale = frm_capture_hrv->capture_hrv->PulsesInSession / 60;
                  x_scale = (x_scale + 1) * 60;
                  if (x_scale >  frm_capture_hrv->chrt_btob_trends->BottomAxis->Maximum)
                  {
                     frm_capture_hrv->chrt_btob_trends->BottomAxis->SetMinMax(0, x_scale);
                     frm_capture_hrv->srs_rtor_interval->AutoRepaint = true;
                     max_y = frm_capture_hrv->srs_rtor_interval->MaxYValue();
                     min_y = frm_capture_hrv->srs_rtor_interval->MinYValue();

                     max_y = max_y + CAPTURE_HRV_TREND_BUFFER;
                     min_y = min_y - CAPTURE_HRV_TREND_BUFFER;
                     if (max_y > CAPTURE_MAX_HRV_TREND)
                     {
                        max_y = CAPTURE_MAX_HRV_TREND;
                     }
                     if (min_y < CAPTURE_MIN_HRV_TREND)
                     {
                        min_y = CAPTURE_MIN_HRV_TREND;
                     }
                     frm_capture_hrv->chrt_btob_trends->LeftAxis->SetMinMax(min_y, max_y);
                     frm_capture_hrv->chrt_btob_trends->LeftAxis->Automatic = false;
                  }
                  for (int k = prev_segments; k < frm_capture_hrv->capture_hrv->PulsesInSession; k++)
                  {
                     frm_capture_hrv->srs_rtor_interval->AddXY(k+1, frm_capture_hrv->capture_hrv->rtor_intervals[count],
                                                            "", clTeeColor);
                     nof_pulses++;
                     if (frm_capture_hrv->capture_hrv->number_rejected_rtor > 0)
                     {
                        for (int km = frm_capture_hrv->capture_hrv->number_rejected_rtor_tot-frm_capture_hrv->capture_hrv->number_rejected_rtor;
                             km < frm_capture_hrv->capture_hrv->number_rejected_rtor_tot; km++)
                        {
                           if (k == frm_capture_hrv->capture_hrv->index_rejected_rtor[km])
                           {
                              frm_capture_hrv->srs_highlow_rtor->AddXY(k+1, 900, "", clTeeColor);
                           }
                        }
                     }
                     count++;
                  }
                  frm_capture_hrv->capture_hrv->time_elapsed = frm_capture_hrv->capture_hrv->time_elapsed + dt;

                  frm_capture_hrv->lbl_time_elapsed->Caption = FormatDateTime("hh:nn:ss",frm_capture_hrv->capture_hrv->time_elapsed);
                  frm_capture_hrv->lbl_rtor->Caption = FormatFloat("0", frm_capture_hrv->capture_hrv->AveRtoR);
                  frm_capture_hrv->lbl_heart_rate->Caption = FormatFloat("0", frm_capture_hrv->capture_hrv->AveHeartRate);
                  frm_capture_hrv->lbl_nof_pulses->Caption = IntToStr(nof_pulses);

                  // Display manoeuvre messages
                  switch (frm_capture_hrv->capture_hrv->MeasureType)
                  {
                     case HRV_NORMAL:
                        break;

                     case HRV_VALSALVA:
                        if (frm_capture_hrv->capture_hrv->time_elapsed == EncodeTime(0, 0, 15, 0))
                        {
                           frm_capture_hrv->lbl_capture_message->Caption = "  Relax And Breathe At Normal Rate";
                        }
                        // Equality testing for floats is unreliable.
                        // So check for greater than 55 seconds.
                        else if (frm_capture_hrv->capture_hrv->time_elapsed > EncodeTime(0, 0, 55, 0))
                        {
                           frm_capture_hrv->lbl_capture_message->Caption = "  Calculate Valsalva Manoeuvre Now";
                        }
                        break;

                     case HRV_STAND:
                        if (frm_capture_hrv->capture_hrv->time_elapsed > EncodeTime(0, 0, 55, 0))
                        {
                           frm_capture_hrv->lbl_capture_message->Caption = "  Calculate Stand Manoeuvre Now";
                        }
                        break;
                  }

                  // Enable the calculate button for manoeuvre modes
                  if (frm_capture_hrv->capture_hrv->PulsesInSession - frm_capture_hrv->capture_hrv->number_rejected_rtor_tot > 45)
                  {
                     frm_capture_hrv->bbtn_calculate->Enabled = true;
                  }
                  //frm_capture_hrv->capture_baro->StoreParamsToFile(error_string);
               }
               else
               {
                  displayed_ok = false;
                  comms_stop();

                  // Only give the option to calculate if calculate will succeed
                  // The error string specifies where the error occurred 
                  if (frm_capture_hrv->bbtn_calculate->Enabled && frm_capture_hrv->capture_hrv->ValidateBeforeCalculate())
                  {
                     if (MsgBox(frm_capture_hrv->capture_hrv->error_string + ".\n\nWould you like to perform a HRV calculation\nwith data gathered so far?",
                             SERROR, MB_YESNO) == ID_YES)
                     {
                           frm_capture_hrv->bbtn_calculateClick(Application);
                     }
                     else
                     {
                        frm_capture_hrv->bbtn_stopClick(Application);
                     }
                  }
                  else
                  {
                     MsgBox(frm_capture_hrv->capture_hrv->error_string, SERROR, MB_OK);
                     frm_capture_hrv->bbtn_stopClick(Application);
                  }
               }
            }
            xpos_srs_ecg = 0;
            frm_capture_hrv->srs_ecg->Clear();
            Word capture_max_time = HRV_MAX_SESSION_TIME/60;
            DecodeTime(frm_capture_hrv->capture_hrv->time_elapsed, hour, min, sec, msec);

            // When the maximum session time is reached, calculate a report
            if (hour >= capture_max_time || frm_capture_hrv->capture_hrv->PulsesInSession > HRV_MAX_CAPTURE_PULSES)
            {
               displayed_ok = true;
               comms_stop();
               frm_capture_hrv->bbtn_calculateClick(Application);
            }

         }
      }
   }
   else
   {
      displayed_ok = false;
      comms_stop();
      log_write("Comms HRV Capture: Sample = " +IntToStr(ecg_sample[0]));
      if (frm_capture_hrv->bbtn_calculate->Enabled && frm_capture_hrv->capture_hrv->ValidateBeforeCalculate())
      {
         if (MsgBox(LoadStr(MSG_COMMS_COMMUNICATIONS_PROBLEM) +"\n\nWould you like to save and process the data you have captured thus far ?",
                    SCONFIRMATION,
                    MB_YESNO | MB_ICONQUESTION) == ID_YES)
         {
            frm_capture_hrv->bbtn_calculateClick(Application);
         }
         else
         {
            frm_capture_hrv->bbtn_stopClick(Application);
         }
      }
      else
      {
         capture_reset(MEAS_HRV_ID);
         comms_close();
         frm_capture_hrv->ModalResult = mrNone;
         frm_capture_hrv->Close();
      }
   }

   return (displayed_ok);
}

MEAS_ID_TYPE capture_get_current(void)
{
   return (capture_meas_type);
}



