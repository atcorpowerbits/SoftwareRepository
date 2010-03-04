///---------------------------------------------------------------------------
//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include <math.h>
#include <stdlib.h>
#include <comms\pubserv.h>
#include <capture\pubserv.h>
#include <config\pubserv.h>
#include <patient\pubserv.h>
#include <msg\pubserv.h>
#include <export\pubserv.h>
#include <emr\pubserv.h>
#include <scor\utils.h>
#include "capture.h"
#include "form_caphrv.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

Tfrm_capture_hrv *frm_capture_hrv;

//---------------------------------------------------------------------------
__fastcall Tfrm_capture_hrv::Tfrm_capture_hrv(TComponent* Owner)
    : TForm(Owner)
{

}
//---------------------------------------------------------------------------

void __fastcall Tfrm_capture_hrv::FormCreate(TObject *Sender)
{
   capture_hrv = meas_get_current_hrv();
   display_resolution = 5 * 1024;
   total_samples = display_resolution;
   capture_ch1_buff = new short int[total_samples];
}


void __fastcall Tfrm_capture_hrv::FormDestroy(TObject *Sender)
{
   if (capture_ch1_buff != NULL)
   {
      delete [] capture_ch1_buff;
      capture_ch1_buff = NULL;
   }
   FileClose(capture_hrv->lFileHandle);

}
//---------------------------------------------------------------------------






bool __fastcall Tfrm_capture_hrv::simulate_start(void)
{
   AnsiString sim_pressure_fname;
   AnsiString sim_ecg_fname;

   sim_ecg_fname = config_get_simulation_directory() + "\\" + CONFIG_HRV_SIMULATE;
   return (sim_ecg_buffer.OpenFile(sim_ecg_fname));
}

void __fastcall Tfrm_capture_hrv::simulate_stop(void)
{
   sim_ecg_buffer.CloseFile();

}

void __fastcall Tfrm_capture_hrv::simulate_data(void)
{
   int i;
   int j;
   short int esample[8];
   bool status = true;

   i = 0;
   while (status && i < 12)
   {
      for (j = 0; j < 8; j++)
      {
         sim_ecg_buffer.GetNextValueFromFile(&esample[j]);
      }
      status = capture_hrv_add_sample(&esample[0], 8, true, false);
      ++i;
   }
}


//---------------------------------------------------------------------------

void __fastcall Tfrm_capture_hrv::FormShow(TObject *Sender)
{
   COMMS_ID_TYPE  the_port;

   switch (capture_hrv->MeasureType)
   {
      case HRV_NORMAL:
         bbtn_start_session->Caption = "Start &Session";
         lbl_capture_message->Caption = "";
         break;
      case HRV_VALSALVA:
         bbtn_start_session->Caption = "Start &Valsalva";
         lbl_capture_message->Caption = "  Prepare To Hold Breath";
         break;
      case HRV_STAND:
         bbtn_start_session->Caption = "Start &Stand";
         lbl_capture_message->Caption = "  Prepare To Stand";
         break;
   }

   bbtn_event_marker->Enabled = false;
   bbtn_calculate->Enabled = false;
   bbtn_start_session->Enabled = true;
   first_time = true;
   lbl_pname->Caption = patient_get_name();

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
   
   capture_reset(MEAS_HRV_ID);
   the_port = config_get_comms_port();
   if (comms_open(the_port))
   {
      if (comms_start(MEAS_HRV_ID) == false)
      {
         PostMessage(this->Handle, WM_CLOSE, 0, 0);
      }
   }
   // Prepare to store signal to file
   String lFileName = ExtractFilePath(Application->ExeName) + EXPORT_SUBDIR + "hrv_session.txt";

   DeleteFile(lFileName);
   capture_hrv->lFileHandle = FileCreate(lFileName);
   
   // Validation
   if (capture_hrv->lFileHandle <= 0)
   {
     MsgBox(LoadStr(MSG_COMMS_NO_FILE) + lFileName + "\n\n" +
          LoadStr(MSG_COMMS_CHECK_FILENAME), SWARNING, MB_ICONSTOP);
   }

   chrt_ecg_monitor->Color = sphygmocor_background;
   chrt_btob_trends->BackWall->Color = sphygmocor_white;
}
//---------------------------------------------------------------------------


void __fastcall Tfrm_capture_hrv::FormKeyPress(TObject *Sender, char &Key)
{
   if (Key == VK_SPACE)
   {
      // PM V9
      // If caclulate is not enabled, then ignore the space bar
      if (bbtn_calculate->Enabled)
      {
         comms_stop();
         capture_reset(MEAS_HRV_ID);
         comms_close();
         ModalResult = mrOk;
      }
      /*else
      {
         capture_reset(MEAS_HRV_ID);
         comms_close();
         MsgBox(LoadStr(MSG_HRV_NO_PULSES),
                SNOTIFICATION,
                MB_OK | MB_ICONINFORMATION);
         ModalResult = mrNone;
         Close();
      }*/
   }
   else if (Key == VK_ESCAPE)
   {
      comms_stop();
      /*
      ** Please note comms close is not called at this point
      ** as the AsyncPro library hangs when we try and close the
      ** physical comms port.
      */
      if (bbtn_calculate->Enabled)
      {
         if (MsgBox_confirmation("Do you really want to Abort this Session !\n\nClick Yes if you want to Cancel and not save this Session, otherwise\n\nClick No to save this Session and generate a HRV Report.",
                                 "Cancel HRV Session") == IDYES)
         {
            capture_reset(MEAS_HRV_ID);
            comms_close();
            ModalResult = mrNone;
            Close();
         }
         else
         {
            comms_close();
            capture_reset(MEAS_HRV_ID);
            ModalResult = mrOk;
         }
      }
      else
      {

         comms_close();
         capture_reset(MEAS_HRV_ID);
         ModalResult = mrNone;
         Close();
      }
   }
   else if (Key == VK_RETURN)
   {
      bbtn_event_marker->Enabled = true;

      // This commences data capture
      bbtn_start_session->Enabled = false;

      chrt_ecg_monitor->Color = sphygmocor_black;
      chrt_btob_trends->BackWall->Color = sphygmocor_black;
      comms_reset_footswitch();
      switch (capture_hrv->MeasureType)
      {
         case HRV_NORMAL:
             break;

         case HRV_VALSALVA:
            lbl_capture_message->Caption = "  Blow Against 40mmHg Strain Now";
            break;

         case HRV_STAND:
            lbl_capture_message->Caption = "  Stand Up Now";
            break;
      }
   }
}
//---------------------------------------------------------------------------



void __fastcall Tfrm_capture_hrv::pnl_topClick(TObject *Sender)
{
   //edtbx_event_comment->Enabled = true;
   //edtbx_event_comment->SetFocus();
}
//---------------------------------------------------------------------------


void __fastcall Tfrm_capture_hrv::chrt_ecg_monitorClick(
      TObject *Sender)
{
   //edtbx_event_comment->Enabled = false;
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_capture_hrv::chrt_btob_trendsClick(TObject *Sender)
{
   //edtbx_event_comment->Enabled = false;
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_capture_hrv::pnl_controlClick(TObject *Sender)
{
   //edtbx_event_comment->Enabled = false;
}
//---------------------------------------------------------------------------



void __fastcall Tfrm_capture_hrv::FormResize(TObject *Sender)
{
   pnl_trend->Height = frm_capture_hrv->Height/3;
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_capture_hrv::bbtn_stopClick(TObject *Sender)
{
   char simulate_esc;

   simulate_esc = VK_ESCAPE;
   FormKeyPress(Sender, simulate_esc);
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_capture_hrv::bbtn_calculateClick(TObject *Sender)
{
   char simulate_space;

   simulate_space = VK_SPACE;
   FormKeyPress(Sender, simulate_space);
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_capture_hrv::bbtn_start_sessionClick(TObject *Sender)
{
   char simulate_space;

   simulate_space = VK_RETURN;
   FormKeyPress(Sender, simulate_space);
}
//---------------------------------------------------------------------------



