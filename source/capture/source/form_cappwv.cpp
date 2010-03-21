//---------------------------------------------------------------------------
#include <vcl.h>
#include <vcl\dstring.h>
#pragma hdrstop

#include <stdlib.h>
#include <config\pubserv.h>
#include <comms\pubserv.h>
#include <capture\pubserv.h>
#include <meas\pubserv.h>
#include <msg\pubserv.h>
#include <patient\pubserv.h>
#include <emr\pubserv.h>
#include "capture.h"
#include "form_cappwv.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
Tfrm_capture_pwv *frm_capture_pwv;

//---------------------------------------------------------------------------
__fastcall Tfrm_capture_pwv::Tfrm_capture_pwv(TComponent* Owner, bool is_sitea)
    : TForm(Owner)
{
   sitea = is_sitea;
   capture_time = 0;
   display_resolution = 0;
   display_reset = 0;
   display_rescale = 0;
   pwv_comms_started = true;
   pwv = NULL;
   tmr_capture->Enabled = false;
    pwv = meas_get_current_pwv();
    if (pwv != NULL)
    {
       display_resolution = (UCOUNT)(CAPTURE_SECS_DISPLAY_RESOLUTION * pwv->SampleRate);
       display_reset = (UCOUNT)(CAPTURE_SECS_DISPLAY_RESET * pwv->SampleRate);
       display_rescale =  (UCOUNT)(CAPTURE_SECS_DISPLAY_RESCALE * pwv->SampleRate);
       if (sitea)
       {
          #ifdef PWV_SHORT_STUDY_ENABLED
            if (pwv->SiteA.Nof10s == PWV_SHORT_STUDY_ID)
            {
               total_samples = (UCOUNT)(pwv->SampleRate * PWV_SHORT_STUDY + (2 * pwv->SampleRate));
            }
            else
            {
               total_samples = (UCOUNT)(pwv->SampleRate * pwv->SiteA.Nof10s * 10 + (2 * pwv->SampleRate));
            }
          #else
             total_samples = (UCOUNT)(pwv->SampleRate * pwv->SiteA.Nof10s * 10 + (2 * pwv->SampleRate));
          #endif
          calc_samples =  (UCOUNT)(total_samples - (2 * pwv->SampleRate));
       }
       else
       {
          #ifdef PWV_SHORT_STUDY_ENABLED
            if (pwv->SiteB.Nof10s == PWV_SHORT_STUDY_ID)
            {
               total_samples = (UCOUNT)(pwv->SampleRate * PWV_SHORT_STUDY + (2 * pwv->SampleRate));
            }
            else
            {
               total_samples = (UCOUNT)(pwv->SampleRate * pwv->SiteB.Nof10s * 10 + (2 * pwv->SampleRate));
            }
          #else
            total_samples = (UCOUNT)(pwv->SampleRate * pwv->SiteB.Nof10s * 10 + (2 * pwv->SampleRate));
          #endif
          calc_samples =  (UCOUNT)(total_samples - (2 * pwv->SampleRate));
       }
       capture_ch1_buff = new short int[total_samples];
       capture_ch2_buff = new short int[total_samples];
    }
}

//---------------------------------------------------------------------------
void __fastcall Tfrm_capture_pwv::FormShow(TObject *Sender)
{
   AnsiString        title;
   COMMS_ID_TYPE     the_port;
   PWV_MEASURE_TYPE  meas_type;
   AnsiString        location_str;
   AnsiString        tlength_str;

   if (sitea)
   {
      meas_type = pwv->SiteA.MeasureType;
      #ifdef PWV_SHORT_STUDY_ENABLED
        if (pwv->SiteA.Nof10s == PWV_SHORT_STUDY_ID)
        {
           tlength_str = IntToStr(PWV_SHORT_STUDY);
        }
        else
        {
           tlength_str = IntToStr(pwv->SiteA.Nof10s * 10);
        }
      #else
        tlength_str = IntToStr(pwv->SiteA.Nof10s * 10);
      #endif
   }
   else
   {
      meas_type = pwv->SiteB.MeasureType;
      #ifdef PWV_SHORT_STUDY_ENABLED
        if (pwv->SiteB.Nof10s == PWV_SHORT_STUDY_ID)
        {
           tlength_str = IntToStr(PWV_SHORT_STUDY);
        }
        else
        {
           tlength_str = IntToStr(pwv->SiteB.Nof10s * 10);
        }
      #else
         tlength_str = IntToStr(pwv->SiteB.Nof10s * 10);
      #endif
   }

   location_str = PWVMTypeAsString[meas_type] +" " +tlength_str;
   title = "SphygmoCor Pulse Wave Velocity Data Capture  " +patient_get_name() +"   " +location_str;
   //chrt_pressure->Title->Text->Clear();
   //chrt_pressure->Title->Text->Add(title);
   chrt_ecg->Title->Text->Clear();
   chrt_ecg->Title->Text->Add(title);

   // Determine the current mode and display it on the data mode label
   if (config_get_audit_option())
   {
      lbl_data_mode->Caption = AUDIT_ENABLED + "  ";
   }
   else if (emr_patient_is_active())
   {
      lbl_data_mode->Caption = EMR_ENABLED + "  ";
   }
   else if (emr_get_default_mode())
   {
      lbl_data_mode->Caption = EMR_DEFAULT_MODE + "  ";
   }
   else
   {
      lbl_data_mode->Caption = "";
   }

   capture_reset(MEAS_PWV_ID);
   the_port = config_get_comms_port();
   if (comms_open(the_port))
   {
      if (comms_start(MEAS_PWV_ID) == false)
      {
         pwv_comms_started = false;
      }
      tmr_capture->Enabled = true;
   }
   else
   {
      tmr_capture->Enabled = true;
      pwv_comms_started = false;
   }
}
//---------------------------------------------------------------------------
void __fastcall Tfrm_capture_pwv::FormKeyPress(TObject *Sender, char &Key)
{
   int        i;
   int        j;
   bool       create_report;
   short int  *sample_pressure_data;
   short int  *sample_ecg_data;
   int        upper_pressure_limit;
   short int   signal_max;
   short int   signal_min;

   create_report = true;

   if (Key == VK_SPACE)
   {
      upper_pressure_limit = config_get_pressure_upper_limit();
      sample_pressure_data = new short int[total_samples];
      sample_ecg_data = new short int[total_samples];
      comms_stop();
      tmr_capture->Enabled = false;
      if (capture_circbuff_full)
      {
         i = capture_circbuff_index;
         j = 0;
		     while (((j < calc_samples) && (i < total_samples)))
         {
			sample_pressure_data[j] = capture_ch1_buff[i];
            sample_ecg_data[j] = capture_ch2_buff[i];
            ++i;
            ++j;
         }
         i = 0;
         while (((j < calc_samples) && (i < (capture_circbuff_index - (total_samples - calc_samples)))))
         {
            sample_pressure_data[j] = capture_ch1_buff[i];
            sample_ecg_data[j] = capture_ch2_buff[i];
            ++i;
            ++j;
         }
         i = 0;
         while (create_report && i < calc_samples)
         {
            if (sample_pressure_data[i] < capture_raw_data_threshold)
            {
               create_report = false;
               MsgBox(TNOTIFICATION, MSG_CAPTURE, MSG_CAPTURE_SIGNAL_TOO_LOW);
            }
            ++i;
         }
         if (create_report && math_MinMaxInArray(sample_pressure_data, calc_samples, signal_min, signal_max))
         {
            if (signal_max - signal_min < capture_raw_data_height_threshold)
            {
               create_report = false;
               MsgBox(TNOTIFICATION, MSG_CAPTURE, MSG_CAPTURE_SIGNAL_HEIGHT_TOO_LOW);
            }
         }

         if (create_report)
         {
            i = 0;
            while (create_report && i < calc_samples)
            {
               if (sample_ecg_data[i] > capture_raw_max &&
                   sample_ecg_data[i] > upper_pressure_limit)
               {
                  create_report = false;
               }
               ++i;
            }
            if (create_report == false)
            {
               MsgBox(TNOTIFICATION, MSG_CAPTURE, MSG_CAPTURE_SIGNAL_ECG_CLIPPED);
            }
         }

         if (create_report)
         {
            comms_close();
            if (sitea)
            {
               if (comms_is_module_12bit() == true)
               {
                  pwv->qc_scale = 4;
               }
               else
               {
                  pwv->qc_scale = 1;
               }
               pwv->PrepareToCaptureSignal();
               pwv->SiteA.Tonom.CaptureSignal(sample_pressure_data, calc_samples);
               pwv->SiteA.ECG.CaptureSignal(sample_ecg_data, calc_samples);
            }
            else
            {
               pwv->SiteB.Tonom.CaptureSignal(sample_pressure_data, calc_samples);
               pwv->SiteB.ECG.CaptureSignal(sample_ecg_data, calc_samples);
            }
            capture_reset(MEAS_PWV_ID);
            ModalResult = mrOk;
         }
         else
         {
            capture_reset(MEAS_PWV_ID);
            comms_start(MEAS_PWV_ID);
            tmr_capture->Enabled = true;
         }
      }
      else
      {
         capture_reset(MEAS_PWV_ID);
         if (MsgBox(LoadStr(MSG_NOT_ENOUGH_POINTS) +LoadStr(MSG_PWV_NEED_SECONDS),
                    SCONFIRMATION,
                    MB_YESNO | MB_ICONQUESTION) == ID_YES)
         {
            comms_start(MEAS_PWV_ID);
            tmr_capture->Enabled = true;
         }
         else
         {
            comms_close();
            ModalResult = mrNone;
            Close();
         }
      }
      if (sample_pressure_data != NULL)
      {
         delete [] sample_pressure_data;
      }
      if (sample_ecg_data != NULL)
      {
         delete [] sample_ecg_data;
      }
   }
   else if (Key == VK_ESCAPE)
   {
      comms_stop();
      capture_reset(MEAS_PWV_ID);
      comms_close();
      ModalResult = mrNone;
      Close();
   }
}
//---------------------------------------------------------------------------
void __fastcall Tfrm_capture_pwv::tmr_captureTimer(TObject *Sender)
{
   ++capture_time;
   static bool display_abort = true;

   if (pwv_comms_started == false)
   {
      tbtn_CancelClick(this);
   }

   if (comms_get_footswitch_status() == COMMS_FOOTSWITCH_ONE)
   {
      frm_capture_pwv->tbtn_OKClick(this);
   }

   if (capture_time % 2 == 0)
   {
      short int lSec = (short int) ((capture_time / 2) % 60);
      short int lHour = (short int) ((capture_time / 2) / 3600);
      short int lMin =  (short int) (((capture_time / 2) / 60) % 60);

      String lStrSec = (lSec < 10 ? "0" + IntToStr(lSec) : IntToStr(lSec));
      String lStrMin = (lMin < 10 ? "0" + IntToStr(lMin) : IntToStr(lMin));
      String lStrHour= (lHour< 10 ? "0" + IntToStr(lHour): IntToStr(lHour));

      lbl_capture_time->Caption = lStrHour + TimeSeparator + lStrMin + TimeSeparator + lStrSec;
   }

   if (capture_time % 10 == 0)
   {
      if (display_abort)
      {
         lbl_capture_prompt->Caption =  " Press [ESC] or Click <Cancel> To Abort Data Capture  ";
         display_abort = false;
      }
      else
      {
         lbl_capture_prompt->Caption =  " Press [Space] or Click <OK> To Capture Data  ";
         display_abort = true;
      }
   }

}



//---------------------------------------------------------------------------
void __fastcall Tfrm_capture_pwv::tbtn_OKClick(TObject *Sender)
{
   char simulate_space = VK_SPACE;
   FormKeyPress(Sender, simulate_space);
}
//---------------------------------------------------------------------------
void __fastcall Tfrm_capture_pwv::tbtn_CancelClick(TObject *Sender)
{
  char simulate_space = VK_ESCAPE;
  FormKeyPress(Sender, simulate_space);
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_capture_pwv::FormDestroy(TObject *Sender)
{
   if (capture_ch1_buff != NULL)
   {
      delete [] capture_ch1_buff;
      capture_ch1_buff = NULL;
   }
   if (capture_ch2_buff != NULL)
   {
      delete [] capture_ch2_buff;
      capture_ch2_buff = NULL;
   }
}

bool __fastcall Tfrm_capture_pwv::simulate_start(void)
{
   AnsiString sim_fname;
   bool started;

   if (sitea)
   {
      sim_fname = config_get_simulation_directory() + "\\" + CONFIG_PWV_SITEA_SIMULATE;
   }
   else
   {
      sim_fname = config_get_simulation_directory() + "\\" + CONFIG_PWV_SITEB_SIMULATE;
   }
   started = gBuffer.OpenFile(sim_fname);
   return started;
}

void __fastcall Tfrm_capture_pwv::simulate_stop(void)
{
   gBuffer.CloseFile();
}

void __fastcall Tfrm_capture_pwv::simulate_data(void)
{
   short int sample1;
   short int sample2;
   int       i;

   for (i = 0; i < 12; i++)
   {
      if (gBuffer.GetNextValueFromFile(&sample1, &sample2))
      {
         capture_pwv_add_sample(sample1, sample2, true, false);
      }
      else
      {
         MsgBox("Simulation Failed.\n\nPress OK to continue.",
                SERROR, MB_OK);
         tbtn_CancelClick(this);

      }
   }
}
void __fastcall Tfrm_capture_pwv::FormResize(TObject *Sender)
{
   pnl_bottom->Height = frm_capture_pwv->Height/5.5;
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_capture_pwv::pnl_main_chartResize(TObject *Sender)
{
   chrt_ecg->Height = pnl_main_chart->Height/3;
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_capture_pwv::bbtn_okClick(TObject *Sender)
{
   char simulate_space = VK_SPACE;
   FormKeyPress(Sender, simulate_space);
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_capture_pwv::bbtn_cancelClick(TObject *Sender)
{
   char simulate_space = VK_ESCAPE;
   FormKeyPress(Sender, simulate_space);
}
//---------------------------------------------------------------------------

