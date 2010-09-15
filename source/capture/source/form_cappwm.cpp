//---------------------------------------------------------------------------
#include <vcl.h>
#include <vcl\dstring.h>
#pragma hdrstop

#include <stdlib.h>

#include <config\pubserv.h>
#include <comms\pubserv.h>
#include <dbmgr\pubserv.h>
#include <capture\pubserv.h>
#include <meas\pubserv.h>
#include <msg\pubserv.h>
#include <patient\pubserv.h>
#include <scor/utils.h>
#include "capture.h"
#include "form_cappwm.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
Tfrm_capture_pwm *frm_capture_pwm;

//---------------------------------------------------------------------------
__fastcall Tfrm_capture_pwm::Tfrm_capture_pwm(TComponent* Owner)
    : TForm(Owner)
{

   capture_time = 0;
   last_report_time = 0;
   display_resolution = 0;
   display_reset = 0;
   display_rescale = 0;
   display_trend_refresh_rate = 0;
   report_generation_period = 0;
   trend_counter = 1;
   calculated_trend_counter = 0;
   display_counter = 0;
   pwm_trend_autoscale = false;
   pwm = NULL;
   tmr_capture->Enabled = false;
   count = 0;
   pwm = meas_get_current_pwm();
    if (pwm != NULL)
    {
       if (pwm->TrendSamplePeriod == 0)
       {
          display_resolution = (UCOUNT)(CAPTURE_SECS_DISPLAY_RESOLUTION * pwm->SampleRate);
          display_trend_refresh_rate = ((60. / CAPTURE_SECS_DISPLAY_RESOLUTION) * pwm->TrendRefreshPeriod);
       }
       else
       {
          display_resolution = (UCOUNT)(pwm->TrendSamplePeriod * pwm->SampleRate);
          display_trend_refresh_rate = ((60. / pwm->TrendSamplePeriod) * pwm->TrendRefreshPeriod);
       }

       display_reset = (UCOUNT)(CAPTURE_SECS_DISPLAY_RESET * pwm->SampleRate);
       total_samples = (UCOUNT)(pwm->SampleRate * CAPTURE_SECS_TOTAL);
       calc_samples =  (UCOUNT)(pwm->SampleRate * MEAS_PWA_MIN_CAPTURE_TIME);
       display_rescale = (UCOUNT) (CAPTURE_SECS_DISPLAY_RESCALE * pwm->SampleRate);
       report_generation_period = (UCOUNT) (pwm->ReportGenerationPeriod * 60);
       capture_ch1_buff = new short int[total_samples];
       pwm->periph_buff_len = 0;
    }

    ChartHRTitle = ChartHR->Title->Text->Strings[0];
    ChartSEVRTitle = ChartSEVR->Title->Text->Strings[0];
    ChartEDTitle = ChartED->Title->Text->Strings[0];
    ChartAITitle = ChartAI->Title->Text->Strings[0];
    this->ActiveControl = NULL;
    Application->ProcessMessages();
}

//---------------------------------------------------------------------------
void __fastcall Tfrm_capture_pwm::FormShow(TObject *Sender)
{
   AnsiString        title;
   COMMS_ID_TYPE     the_port;
   AnsiString        location_str;
   AnsiString        tlength_str;

   title = patient_get_name();
   chrt_pressure->Title->Text->Clear();
   chrt_pressure->Title->Text->Add(title);
   pnl_header->Color = sphygmocor_white;
   bbtn_ok->Enabled = false;
   bbtn_snapshot->Enabled = false;
   bbtn_event_mark->Visible = false;
   chrt_pressure->Color = sphygmocor_background;
   chrt_trend_pressure->BackWall->Color = sphygmocor_white;
   ChartHR->BackWall->Color = sphygmocor_white;
   ChartSEVR->BackWall->Color = sphygmocor_white;
   ChartED->BackWall->Color = sphygmocor_white;
   ChartAI->BackWall->Color = sphygmocor_white;

   capture_reset(MEAS_PWM_ID);
   the_port = config_get_comms_port();
   if (comms_open(the_port))
   {
      if (capture_is_calibrated())
      {
         title = "(mmHg)";
         chrt_pressure->LeftAxis->Title->Caption = title;
         lbl_uncal_sp->Visible = false;
         lbl_uncal_mp->Visible = false;
         lbl_uncal_dp->Visible = false;
         edt_uncal_sp->Visible = false;
         edt_uncal_mp->Visible = false;
         edt_uncal_dp->Visible = false;
         spdbtn_update_pressures->Visible = false;
      }
      else
      {
         title = "(mV)";
         chrt_pressure->LeftAxis->Title->Caption = title;
         lbl_uncal_sp->Visible = true;
         lbl_uncal_mp->Visible = true;
         lbl_uncal_dp->Visible = true;
         edt_uncal_sp->Visible = true;
         edt_uncal_mp->Visible = true;
         edt_uncal_dp->Visible = true;
         spdbtn_update_pressures->Visible = true;
         if (pwm != NULL)
         {
            if (pwm->Dp > 0)
            {
               edt_uncal_dp->Text = RoundIntToStr(pwm->Dp);
            }
            else
            {
               edt_uncal_dp->Text = "";
            }
            if (pwm->Sp > 0)
            {
               edt_uncal_sp->Text = RoundIntToStr(pwm->Sp);
            }
            else
            {
               edt_uncal_sp->Text = "";
            }
            if (pwm->MeanP > 0)
            {
               edt_uncal_mp->Text = RoundIntToStr(pwm->MeanP);
            }
            else
            {
               edt_uncal_mp->Text = "";
            }
         }
      }

      TADOTable* pSessionTable = dynamic_cast<TADOTable *> (dbmgr_get_dataset(DBMGR_MEASURE_PWM_SESSION_TABLE, false));
      if (pSessionTable!=NULL)
      {
        if (pwm->CreateNewSession(pSessionTable)==false)
        {
          ShowMessage("Monitoring Session could not be created.");
          return;
        }
      }
      else
      {
          ShowMessage("Session table does not exist.");
          return;
      }
      if (pwm->PrepareToStoreParamsToFile("Params.txt")==false)
      {
        ShowMessage("Could Not Store Trend Parameters to File...");
        return;
      }

      // Open the second comms port if parameter output has been selected
      if (pwm->AIxSendOut)
      {
         if (!comms_open(pwm->outputPort, true, true))
         {
            String S = LoadStr(MSG_COMMS_BUSY_OUTPUT_PORT) + " PortID = " + IntToStr((int)pwm->outputPort);
            MsgBox_show(TWARNING,
                              MSG_COMMS_ERROR,
                              S,
                              MSG_COMMS_BUSY_OUTPUT_PORT, "");
            return;
         }
      }

      // PM AGSM
      // Set the qc_scale before data capture for RTOF
      if (comms_is_module_12bit() == true)
      {
         pwm->Periph.qc_scale = 4;
      }
      else
      {
         pwm->Periph.qc_scale = 1;
      }

      if (comms_start(MEAS_PWM_ID))
      {
         if (frm_capture_pwm->pwm->AorticSendOut || frm_capture_pwm->pwm->PeriphSendOut)
         {
            bbtn_event_mark->Visible = true;
         }
      }
      else
      {
         PostMessage(this->Handle, WM_CLOSE, 0, 0);
      }

      msg_disable_messages();
   }
}

//---------------------------------------------------------------------------
void __fastcall Tfrm_capture_pwm::FormKeyPress(TObject *Sender, char &Key)
{
   if (Key == VK_SPACE)
   {
      // If OK is not enabled, then ignore the space bar
      if (bbtn_ok->Enabled)
      {
         msg_enable_messages();
         comms_stop();
         tmr_capture->Enabled = false;
         if ((capture_circbuff_full && calculated_trend_counter > 1) || pwm->TrendSamplePeriod == 0)
         {
            capture_reset(MEAS_PWM_ID);
            comms_close();
            // Close the second comms port if parameter output has been selected
            if (pwm->AIxSendOut)
            {
               comms_close(true);
            }
            ModalResult = mrOk;
         }
         else
         {
            capture_reset(MEAS_PWM_ID);
            comms_close();
            // Close the second comms port if parameter output has been selected
            if (pwm->AIxSendOut)
            {
               comms_close(true);
            }
            MsgBox(LoadStr(MSG_PWM_NO_TREND_POINTS),
                   SNOTIFICATION,
                   MB_OK | MB_ICONINFORMATION);
            ModalResult = mrNone;
            Close();
         }
      }
   }
   else if (Key == VK_ESCAPE)
   {
      msg_enable_messages();
      comms_stop();
      tmr_capture->Enabled = false;
      if (bbtn_ok->Enabled == false)
      {
         capture_reset(MEAS_PWM_ID);
         comms_close();
         // Close the second comms port if parameter output has been selected
         if (pwm->AIxSendOut)
         {
            comms_close(true);
         }
         ModalResult = mrNone;
         Close();
         return;
      }
      if (MsgBox_confirmation("Do you really want to Abort this Monitoring Session !\n\nClick Yes if you want to Cancel and not save this Session, otherwise\n\nClick No to save this Session and generate a PWM Session Report.",
                              "Cancel Monitoring Session") == IDYES)
      {
         capture_reset(MEAS_PWM_ID);
         comms_close();
         // Close the second comms port if parameter output has been selected
         if (pwm->AIxSendOut)
         {
            comms_close(true);
         }
         ModalResult = mrNone;
         Close();
      }
      else
      {
         if ((capture_circbuff_full && calculated_trend_counter > 1) || pwm->TrendSamplePeriod == 0)
         {
            capture_reset(MEAS_PWM_ID);
            comms_close();
            // Close the second comms port if parameter output has been selected
            if (pwm->AIxSendOut)
            {
               comms_close(true);
            }
            ModalResult = mrOk;
         }
         else
         {
            capture_reset(MEAS_PWM_ID);
            comms_close();
            // Close the second comms port if parameter output has been selected
            if (pwm->AIxSendOut)
            {
               comms_close(true);
            }
            MsgBox(LoadStr(MSG_PWM_NO_TREND_POINTS),
                   SNOTIFICATION,
                   MB_OK | MB_ICONINFORMATION);
            ModalResult = mrNone;
            Close();
         }
      }
   }
   else if (Key == VK_RETURN)
   {
      // Disable snapshots when outputting parameters
      if (!pwm->AIxSendOut)
      {
         if ((capture_time - last_report_time) > 10)
         {
            create_pwm_report();
            last_report_time = capture_time;
         }
      }
   }
}
//---------------------------------------------------------------------------
void __fastcall Tfrm_capture_pwm::tmr_captureTimer(TObject *Sender)
{
   unsigned short Hour;
   unsigned short Minute;
   unsigned short Second;
   unsigned short mSecond;

   COMMS_FOOTSWITCH_STATUS_TYPE  fsw_status;

   // real_time is elapsed time
   real_time = (TDateTime)(Time() - initial_time);

   // capture time is elapsed time in seconds
   real_time.DecodeTime(&Hour, &Minute, &Second, &mSecond);
   capture_time = ((Hour*60) + Minute)*60 + Second;

   // Display time
   pnl_time->Caption = real_time.FormatString("hh:nn:ss");

   if (bbtn_ok->Enabled)
   {
      fsw_status = comms_get_footswitch_status();

      if (fsw_status == COMMS_FOOTSWITCH_TWO)
      {
         if ((capture_time - last_report_time) > 5)
         {
            create_pwm_report();
            last_report_time = capture_time;
         }
      }
      else
      {
         if (fsw_status == COMMS_FOOTSWITCH_ONE)
         {
            bbtn_okClick(this);
         }
      }
      fsw_status = COMMS_FOOTSWITCH_NONE;
   }

   if (report_generation_period)
      {
         if ((capture_time % report_generation_period) == 0)
         {
            if ((capture_time - last_report_time) > 5)
            {
               create_pwm_report();
               last_report_time = capture_time;
            }
         }
      }

   count++;
   if ((count % 20) == 0)
   {
      pnl_header->Color = sphygmocor_white;

      if (capture_time >= 21600) // Abort after 6 hours
      {
         bbtn_okClick(Sender);
         return;
      }

      if (display_counter == 0)
      {
         bbtn_ok->Enabled = true;
         // Disable snapshots when outputting parameters
         if (pwm->AIxSendOut)
         {
            bbtn_snapshot->Enabled = false;
         }
         else
         {
            bbtn_snapshot->Enabled = true;
         }
         Application->ProcessMessages();
         lbl_capture_prompt->Caption =  "[ESC] or <Abort> To Stop Session";
         ++display_counter;
      }
      else if (display_counter == 1)
      {
         lbl_capture_prompt->Caption =  "[Space] or <Calculate> To Save Session";
         ++display_counter;
      }
      else
      {
         lbl_capture_prompt->Caption =  "[Enter] or <Snapshot> to generate a PWA Report";
         display_counter = 0;
      }
   }
}

//---------------------------------------------------------------------------
void __fastcall Tfrm_capture_pwm::FormDestroy(TObject *Sender)
{
   if (capture_ch1_buff != NULL)
   {
      delete [] capture_ch1_buff;
      capture_ch1_buff = NULL;
   }
   msg_enable_messages();
}

bool __fastcall Tfrm_capture_pwm::simulate_start(void)
{
   AnsiString sim_fname;
   bool       started;

   sim_fname = config_get_simulation_directory() + "\\" + CONFIG_PWM_SIMULATE;
   started = gBuffer.OpenFile(sim_fname);
   return started;
}

void __fastcall Tfrm_capture_pwm::simulate_stop(void)
{
   gBuffer.CloseFile();
}

void __fastcall Tfrm_capture_pwm::simulate_data(void)
{
   short int sample1;
   int       i;

   for (i = 0; i < 12; i++)
   {
      if (gBuffer.GetNextValueFromFile(&sample1))
      {
         capture_pwm_add_sample(sample1, true, false);
      }
      else
      {
         MsgBox("Simulation Failed.\n\nPress OK to continue.",
                SERROR, MB_OK);
         bbtn_stopClick(this);

      }
   }
}
void __fastcall Tfrm_capture_pwm::pnl_raResize(TObject *Sender)
{
  pnl_rad->Width = pnl_ra->Width/2;
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_capture_pwm::pnl_ra_ppResize(TObject *Sender)
{
  pnl_ppp->Width = pnl_ra_pp->Width/2;
}
//---------------------------------------------------------------------------

bool __fastcall Tfrm_capture_pwm::create_pwm_report(void)
{
   int        i;
   int        j;
   int        new_index;
   bool       create_report;
   short int  *sample_pressure_data;
   TDataSet   *pwm_table;

   create_report = true;

   sample_pressure_data = new short int[total_samples];
   pnl_header->Color = sphygmocor_white;
   if (capture_circbuff_full)
   {
      new_index = capture_circbuff_index + (total_samples - calc_samples);
      i = new_index;
      j = 0;
      while (((j < calc_samples) && (i < total_samples)))
      {
	     sample_pressure_data[j] = capture_ch1_buff[i];
         ++i;
         ++j;
      }
      i = 0;
      while (((j < calc_samples) && (i < (new_index - (total_samples - calc_samples)))))
      {
         sample_pressure_data[j] = capture_ch1_buff[i];
         ++i;
         ++j;
      }
      i = 0;
      while (create_report && i < calc_samples)
      {
         if (sample_pressure_data[i] < capture_raw_data_threshold)
         {
            create_report = false;
         }
         ++i;
      }

      if (!create_report)
      {
         //MsgBox(TWARNING, MSG_CAPTURE, MSG_CAPTURE_SIGNAL_TOO_LOW);
      }

      if (create_report)
      {
         if (edt_pwa_notes->GetTextLen() > 0)
         {
            pwm->Notes = edt_pwa_notes->Text;
            edt_pwa_notes->Text = "";
         }
         else
         {
            pwm->Notes = "";
         }
         Application->ProcessMessages();
         if ((comms_is_module_12bit() == true) && !pwm->Calibrated)
         {
            pwm->Periph.qc_scale = 4;
         }
         else
         {
            pwm->Periph.qc_scale = 1;
         }
         pwm->PrepareToCaptureSignal();
         pwm->Periph.CaptureSignal(sample_pressure_data, calc_samples);
         if (pwm->Calculate(false))
         {
            if (dbmgr_open(DBMGR_MEASURE_PWM_TABLE, false))
            {
               pwm_table = dbmgr_get_dataset(DBMGR_MEASURE_PWM_TABLE, false);
               if (pwm != NULL)
               {
                  try
                  {
                     pwm_table->Insert();
                  }
                  catch (Exception &exception)
                  {
                     dbmgr_close(DBMGR_MEASURE_PWM_TABLE, false);
                  }

                  pwm->Store(pwm_table, true, true);
               }
               dbmgr_close(DBMGR_MEASURE_PWM_TABLE, false);
               pnl_header->Color = sphygmocor_green;
            }
         }
         else
         {
            create_report = false;
            pnl_header->Color = sphygmocor_red;
         }
      }
      if (sample_pressure_data != NULL)
      {
         delete [] sample_pressure_data;
      }
   }
   else
   {
      pnl_header->Color = sphygmocor_red;
   }
   this->ActiveControl = NULL;
   Application->ProcessMessages();
   return (create_report);
}




void __fastcall Tfrm_capture_pwm::spdbtn_update_pressuresClick(
      TObject *Sender)
{
   int prev_sp;
   int prev_dp;
   int prev_mp;

   prev_sp = pwm->Sp;
   prev_dp = pwm->Dp;
   prev_mp = pwm->MeanP;

   pwm->Sp = edt_uncal_sp->Text.ToIntDef(0);
   pwm->Dp = edt_uncal_dp->Text.ToIntDef(0);
   pwm->MeanP = edt_uncal_mp->Text.ToIntDef(0);
   if (pwm->ValidateBeforeCalculate() == false)
   {
      pwm->Sp = prev_sp;
      pwm->Dp = prev_dp;
      pwm->MeanP = prev_mp;
      if (pwm->Dp > 0)
      {
         edt_uncal_dp->Text = RoundIntToStr(pwm->Dp);
      }
      else
      {
         edt_uncal_dp->Text = "";
      }
      if (pwm->Sp > 0)
      {
         edt_uncal_sp->Text = RoundIntToStr(pwm->Sp);
      }
      else
      {
         edt_uncal_sp->Text = "";
      }
      if (pwm->MeanP > 0)
      {
         edt_uncal_mp->Text = RoundIntToStr(pwm->MeanP);
      }
      else
      {
         edt_uncal_mp->Text = "";
      }
   }
   this->ActiveControl = NULL;
   Application->ProcessMessages();
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_capture_pwm::edt_pwa_notesKeyPress(TObject *Sender,
      char &Key)
{
   if (Key == VK_ESCAPE)
   {
      edt_pwa_notes->Text = "";
   }
   else if (Key == VK_RETURN)
   {
      if (bbtn_snapshot->Enabled)
      {
         this->ActiveControl = NULL;
         Application->ProcessMessages();
      }
   }
}

//---------------------------------------------------------------------------

void __fastcall Tfrm_capture_pwm::edt_uncal_spChange(TObject *Sender)
{
   if (edt_uncal_sp->Text.ToIntDef(-1) == -1)
   {
      edt_uncal_sp->Text = "";
   }
   else
   {
      if (edt_uncal_sp->Text.ToIntDef(-1) > MAX_SP)
      {
         edt_uncal_sp->Text = MAX_SP;
      }
      else
      {
         edt_uncal_mp->Text = "";
      }
   }
}

void __fastcall Tfrm_capture_pwm::edt_uncal_mpChange(TObject *Sender)
{
   if (edt_uncal_mp->Text.ToIntDef(-1) != -1)
   {
      edt_uncal_sp->Text = "";
   }
   else
   {
      edt_uncal_mp->Text = "";
   }
}

void __fastcall Tfrm_capture_pwm::edt_uncal_dpChange(TObject *Sender)
{
   if (edt_uncal_dp->Text.ToIntDef(-1) != -1)
   {
      if (edt_uncal_sp->Text.ToIntDef(-1) != -1 &&
          edt_uncal_sp->Text.ToInt() < edt_uncal_dp->Text.ToInt())
      {
         edt_uncal_sp->Text = edt_uncal_dp->Text;
      }
      if (edt_uncal_mp->Text.ToIntDef(-1) != -1 &&
          edt_uncal_mp->Text.ToInt() < edt_uncal_dp->Text.ToInt())
      {
         edt_uncal_mp->Text = edt_uncal_dp->Text;
      }
   }
   else
   {
      edt_uncal_dp->Text = "";
   }
}

void __fastcall Tfrm_capture_pwm::bbtn_event_markClick(TObject *Sender)
{
   if (frm_capture_pwm->pwm->AorticSendOut || frm_capture_pwm->pwm->PeriphSendOut)
   {
      comms_send_event_mark();
      pwm->EventMarker = 10.0;

      // Store and clear the event comment
      pwm->event_comment->Add(IntToStr(capture_time) + "-" + edt_pwa_notes->Text);
      edt_pwa_notes->Text = "";
   }
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_capture_pwm::ChartAIZoom(TObject *Sender)
{
   ChartAI->Color = sphygmocor_navy;
   ChartAI->BottomAxis->SetMinMax(0, chrt_trend_pressure->BottomAxis->Maximum);
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_capture_pwm::ChartAIUndoZoom(TObject *Sender)
{
   ChartAI->Color = sphygmocor_background;

}
//---------------------------------------------------------------------------

void __fastcall Tfrm_capture_pwm::ChartEDZoom(TObject *Sender)
{
   ChartED->Color = sphygmocor_navy;
   ChartED->BottomAxis->SetMinMax(0, chrt_trend_pressure->BottomAxis->Maximum);
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_capture_pwm::ChartEDUndoZoom(TObject *Sender)
{
   ChartED->Color = sphygmocor_background;
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_capture_pwm::ChartSEVRZoom(TObject *Sender)
{
   ChartSEVR->Color = sphygmocor_navy;
   ChartSEVR->BottomAxis->SetMinMax(0, chrt_trend_pressure->BottomAxis->Maximum);
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_capture_pwm::ChartSEVRUndoZoom(TObject *Sender)
{
   ChartSEVR->Color = sphygmocor_background;
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_capture_pwm::ChartHRZoom(TObject *Sender)
{
   ChartHR->Color = sphygmocor_navy;
   ChartHR->BottomAxis->SetMinMax(0, chrt_trend_pressure->BottomAxis->Maximum);
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_capture_pwm::ChartHRUndoZoom(TObject *Sender)
{
   ChartHR->Color = sphygmocor_background;
}
//---------------------------------------------------------------------------


void __fastcall Tfrm_capture_pwm::pnl_headerClick(TObject *Sender)
{
   edt_pwa_notes->Enabled = true;
   edt_pwa_notes->SetFocus();
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_capture_pwm::chrt_pressureClick(TObject *Sender)
{
   edt_pwa_notes->Enabled = false;
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_capture_pwm::chrt_trend_pressureClick(TObject *Sender)
{
   edt_pwa_notes->Enabled = false;   
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_capture_pwm::ChartHRClick(TObject *Sender)
{
   edt_pwa_notes->Enabled = false;   
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_capture_pwm::ChartSEVRClick(TObject *Sender)
{
   edt_pwa_notes->Enabled = false;   
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_capture_pwm::ChartEDClick(TObject *Sender)
{
   edt_pwa_notes->Enabled = false;   
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_capture_pwm::ChartAIClick(TObject *Sender)
{
   edt_pwa_notes->Enabled = false;
}
//---------------------------------------------------------------------------


void __fastcall Tfrm_capture_pwm::pnl_trendResize(TObject *Sender)
{
   int trend_height = pnl_trend_timing->Height/4;

   ChartAI->Height = trend_height;
   ChartED->Height = trend_height;
   ChartSEVR->Height = trend_height;
   chrt_trend_pressure->Width = pnl_trend->Width/2;
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_capture_pwm::pnl_main_chartResize(TObject *Sender)
{
   int main_height = frm_capture_pwm->Height/3.5;

   pnl_main_chart->Height = main_height;
}
//---------------------------------------------------------------------------



void __fastcall Tfrm_capture_pwm::bbtn_startClick(TObject *Sender)
{
   // Change chart colours
   chrt_pressure->Color = sphygmocor_black;
   chrt_trend_pressure->BackWall->Color = sphygmocor_black;
   ChartHR->BackWall->Color = sphygmocor_black;
   ChartSEVR->BackWall->Color = sphygmocor_black;
   ChartED->BackWall->Color = sphygmocor_black;
   ChartAI->BackWall->Color = sphygmocor_black;

   // Disabling the "Start Session" button initialises data calculation
   // Also initialise the timer
   bbtn_start->Enabled = false;
   tmr_capture->Enabled = true;
   initial_time = Time();
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_capture_pwm::bbtn_okClick(TObject *Sender)
{
   char simulate_space = VK_SPACE;
   FormKeyPress(Sender, simulate_space);
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_capture_pwm::bbtn_stopClick(TObject *Sender)
{
  char simulate_escape = VK_ESCAPE;
  FormKeyPress(Sender, simulate_escape);
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_capture_pwm::bbtn_snapshotClick(TObject *Sender)
{
   AnsiString file_name;
   PATIENT_RECORD_TYPE  pat;

   if (patient_get(&pat))
   {
      file_name = ExtractFilePath(ParamStr(0)) +"Export\\" +pat.surname +Now().FormatString("ddmmmyyyy-hhmmss") +"_pwm.wmf";
      chrt_pressure->SaveToMetafile(file_name);
   }
   if ((capture_time - last_report_time) > 10)
   {
      create_pwm_report();
      last_report_time = capture_time;
   }
}
//---------------------------------------------------------------------------


