#include <vcl.h>
#include <vcl\dstring.h>
#pragma hdrstop

#include <config\pubserv.h>
#include <comms\pubserv.h>
#include <capture\pubserv.h>
#include <meas\pubserv.h>
#include <msg\pubserv.h>
#include <patient\pubserv.h>
#include <emr\pubserv.h>
#include <rtof\pubserv.h>
#include "capture.h"
#include "form_cappwa.h"

#pragma package(smart_init)
#pragma resource "*.dfm"
Tfrm_capture_pwa *frm_capture_pwa;

const String CAPTURE_TITLE = "SphygmoCor Study Data Capture  ";
//---------------------------------------------------------------------------
__fastcall Tfrm_capture_pwa::Tfrm_capture_pwa(TComponent* Owner)
    : TForm(Owner)
{
   capture_time = 0;
   pwa = NULL;
   display_resolution = 0;
   display_reset = 0;
   total_samples = 0;
   calc_samples = 0;
   tmr_capture->Enabled = false;
   pwa = meas_get_current_pwa();
   if (pwa != NULL)
   {
      display_resolution = (UCOUNT)(CAPTURE_SECS_DISPLAY_RESOLUTION * pwa->SampleRate);
      display_reset = (UCOUNT)(CAPTURE_SECS_DISPLAY_RESET * pwa->SampleRate);
      total_samples = (UCOUNT)(pwa->SampleRate * CAPTURE_SECS_TOTAL);
      calc_samples =  (UCOUNT)(pwa->SampleRate * MEAS_PWA_MIN_CAPTURE_TIME);
      capture_ch1_buff = new short int[total_samples];
      pwa->CaptureTime = "";
   }
}

//---------------------------------------------------------------------------
void __fastcall Tfrm_capture_pwa::FormShow(TObject *Sender)
{
   String         title;
   COMMS_ID_TYPE  the_port;

   // PM V9
   // Clinical mode is always Radial, so no need for the label
   if (config_get_clinical_option())
   {
      title = "";
   }
   else
   {
      switch (pwa->MeasureType)
      {
         case PWA_RADIAL:
            title = "[ Radial ]  ";
            break;
         case PWA_CAROTID:
            title = "[ Carotid ]  ";
            break;
         case PWA_AORTIC:
            title = "[ Aortic ]  ";
            break;
      }
   }
   title = title + CAPTURE_TITLE + "( " +patient_get_name() + " )";
   chrt_main->Title->Text->Clear();
   chrt_main->Title->Text->Add(title);

   // PM V9
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

   lbl_pulse_height->Caption = "";
   lbl_pulse_height_variation->Caption = "";
   lbl_baseline_variation->Caption = "";

   capture_reset(MEAS_PWA_ID);

   // PM V9
   // Set the qc_scale before data capture for RTOF
   if (comms_is_module_12bit() == true)
   {
      pwa->Periph.qc_scale = 4;
   }
   else
   {
      pwa->Periph.qc_scale = 1;
   }

   the_port = config_get_comms_port();
   if (comms_open(the_port))
   {
      if (comms_start(MEAS_PWA_ID))
      {
         tmr_capture->Enabled = true;
      }
      else
      {
        PostMessage(this->Handle, WM_CLOSE, 0, 0);
      }
   }
}

//---------------------------------------------------------------------------
void __fastcall Tfrm_capture_pwa::FormKeyPress(TObject *Sender, char &Key)
{
   int        i;
   int        j;
   bool       create_report;
   short int  *sample_data;
   short int   signal_max;
   short int   signal_min;

   create_report = true;

   if (Key == VK_SPACE)
   {
      sample_data = new short int[total_samples];
      comms_stop();
      tmr_capture->Enabled = false;
      if (capture_circbuff_full)
      {
         i = capture_circbuff_index;
         j = 0;
		     while (((j < calc_samples) && (i < total_samples)))
         {
			      sample_data[j++] = capture_ch1_buff[i++];
         }
         i = 0;
         while (((j < calc_samples) && (i < (capture_circbuff_index - (total_samples - calc_samples)))))
         {
            sample_data[j++] = capture_ch1_buff[i++];
         }

         i = 0;
         while (create_report && i < calc_samples)
         {
            if (sample_data[i] < capture_raw_data_threshold)
            {
               create_report = false;
               MsgBox(TNOTIFICATION, MSG_CAPTURE, MSG_CAPTURE_SIGNAL_TOO_LOW);
               capture_reset(MEAS_PWA_ID);
               comms_start(MEAS_PWA_ID);
               tmr_capture->Enabled = true;
            }
            ++i;
         }
         if (create_report && math_MinMaxInArray(sample_data, calc_samples, signal_min, signal_max))
         {
            if (signal_max - signal_min < capture_raw_data_height_threshold)
            {
               create_report = false;
               MsgBox(TNOTIFICATION, MSG_CAPTURE, MSG_CAPTURE_SIGNAL_HEIGHT_TOO_LOW);
               capture_reset(MEAS_PWA_ID);
               comms_start(MEAS_PWA_ID);
               tmr_capture->Enabled = true;
            }
         }

         if (create_report)
         {
            comms_close();
            if (comms_is_module_12bit() == true)
            {
               pwa->Periph.qc_scale = 4;
            }
            else
            {
               pwa->Periph.qc_scale = 1;
            }
            pwa->PrepareToCaptureSignal();
            pwa->Periph.CaptureSignal(sample_data, calc_samples);
            pwa->CaptureTime = lbl_capture_time->Caption;
            capture_reset(MEAS_PWA_ID);
            ModalResult = mrOk;
         }

      }
      else
      {
         capture_reset(MEAS_PWA_ID);
         if (MsgBox(LoadStr(MSG_NOT_ENOUGH_POINTS) +LoadStr(MSG_NEED_11_SECONDS),
                    SCONFIRMATION, MB_YESNO | MB_ICONQUESTION) == ID_YES)
         {
            if (comms_start(MEAS_PWA_ID))
            {
               tmr_capture->Enabled = true;
            }
            else
            {
               comms_close();
               ModalResult = mrNone;
               Close();
            }
         }
         else
         {
            comms_close();
            ModalResult = mrNone;
            Close();
         }
      }
      if (sample_data != NULL)
      {
         delete [] sample_data;
      }
   }
   else if (Key == VK_ESCAPE)
   {
      comms_stop();
      capture_reset(MEAS_PWA_ID);
      comms_close();
      ModalResult = mrNone;
      Close();
   }

}
//---------------------------------------------------------------------------
void __fastcall Tfrm_capture_pwa::tmr_captureTimer(TObject *Sender)
{
   ++capture_time;
   static bool display_abort = true;

   if (comms_get_footswitch_status() == COMMS_FOOTSWITCH_ONE)
   {
      bbtn_okClick(this);
   }

   // PM V9
   // If auto capture is set, then calculate a report
   if (rtof_get_auto_capture())
   {
      bbtn_okClick(this);
   }

   if (capture_time % 2 == 0)
   {
      // Display time
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

void __fastcall Tfrm_capture_pwa::FormDestroy(TObject *Sender)
{
   if (capture_ch1_buff != NULL)
   {
      delete [] capture_ch1_buff;
      capture_ch1_buff = NULL;
   }
}

bool __fastcall Tfrm_capture_pwa::simulate_start(void)
{
   AnsiString sim_fname;

   sim_fname = config_get_simulation_directory() + "\\" + CONFIG_PWA_SIMULATE;
   return gBuffer.OpenFile(sim_fname);
}

void __fastcall Tfrm_capture_pwa::simulate_stop(void)
{
   gBuffer.CloseFile();
}

void __fastcall Tfrm_capture_pwa::simulate_data(void)
{
   int i;
   short int sample1;

   for (i = 0; i < 12; i++)
   {
      //if (pwa->Periph.GetNextValue(sample1))
      if (gBuffer.GetNextValueFromFile(&sample1))
      {
         capture_pwa_add_sample(sample1, true, false);
      }
      else
      {
         MsgBox("Simulation Failed.\n\nPress OK to continue.",
                SERROR, MB_OK);
         bbtn_cancelClick(this);
      }
   }
}
void __fastcall Tfrm_capture_pwa::FormResize(TObject *Sender)
{
   pnl_bottom->Height = frm_capture_pwa->Height/8;
   lbl_pulse_height_variation->Width = pnl_rtof->Width/3;
   lbl_pulse_height->Width = pnl_rtof->Width/3;
}
//---------------------------------------------------------------------------
void __fastcall Tfrm_capture_pwa::bbtn_okClick(TObject *Sender)
{
   char simulate_space;

   simulate_space = VK_SPACE;
   FormKeyPress(Sender, simulate_space);
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_capture_pwa::bbtn_cancelClick(TObject *Sender)
{
   char simulate_esc;

   simulate_esc = VK_ESCAPE;
   FormKeyPress(Sender, simulate_esc);
}
//---------------------------------------------------------------------------


