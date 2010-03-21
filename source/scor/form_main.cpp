//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
#include "utils.h"
#include "form_main.h"
#include "form_about.h"
#include "form_patient.h"
#include <log\pubserv.h>
#include <config\pubserv.h>
#include <comms\pubserv.h>
#include <patient\pubserv.h>
#include <report\pubserv.h>
#include <analysis\pubserv.h>
#include <capture\pubserv.h>
#include <meas\pubserv.h>
#include <dbmgr\pubserv.h>
#include <print\pubserv.h>
#include <export\pubserv.h>
#include <multdb\pubserv.h>
#include <msg\pubserv.h>
#include <cfr11\pubserv.h>
#include <emr\pubserv.h>
#include <rtof\pubserv.h>
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "GIFImage"
#pragma link "TeeDraw3D"
#pragma resource "*.dfm"
//---------------------------------------------------------------------------

Tfrm_main *frm_main;
bool      emma_first_time;
bool      emma_closing;
bool      emma_initialised;
const     String OLD_SCOR_DIR = "C:\\SPHYCOR\\DATA";
//---------------------------------------------------------------------------
TForm *emma_get_main_form_pointer(void)
{
   return (frm_main);
}

void emma_display_statusbar_message(AnsiString msg1, AnsiString msg2, AnsiString hint, TColor color)
{
   if (frm_main != NULL)
   {
      frm_main->lbl_message1->Font->Color = color;
      frm_main->lbl_message3->Font->Color = color;
      frm_main->lbl_message1->Caption = msg1;
      frm_main->lbl_message3->Caption = msg2;
      frm_main->lbl_message1->Hint = hint;
      frm_main->lbl_message3->Hint = hint;
      Application->ProcessMessages();
   }
}

void emma_display_statusbar_message(AnsiString msg1, AnsiString msg2, TColor color)
{
   if (frm_main != NULL)
   {
      frm_main->lbl_message2->Font->Color = color;
      frm_main->lbl_message2->Caption = msg1;
      frm_main->lbl_message4->Font->Color = color;
      frm_main->lbl_message4->Caption = msg2;
      Application->ProcessMessages();
   }
}

/*
//---------------------------------------------------------------------------
MEAS_ID_TYPE emma_get_study_mode(void)
{
   MEAS_ID_TYPE           meas_mode;
   CONFIG_SYSTEM_OPTIONS  cfg_options;

   cfg_options = config_get_system_options();

   if (cfg_options == CONFIG_PWV_ONLY_OPTION)
   {
      meas_mode = MEAS_PWV_ID;
   }
   else
   {
      switch (frm_main->cmbx_mode->ItemIndex)
      {
         case 0:
            meas_mode = MEAS_PWA_ID;
            break;

         case 1:
            if (cfg_options == CONFIG_PWV_OPTION || cfg_options == CONFIG_STANDARD_ALL_OPTION || cfg_options == CONFIG_EXTENDED_ALL_OPTION)
            {
               meas_mode = MEAS_PWV_ID;
            }
            else if (cfg_options == CONFIG_PWM_OPTION)
            {
               meas_mode = MEAS_PWM_ID;
            }
            else if (cfg_options == CONFIG_HRV_OPTION)
            {
               meas_mode = MEAS_HRV_ID;
            }
            else
            {
                meas_mode = MEAS_PWA_ID;
            }
            break;

         case 2:
            meas_mode = MEAS_PWM_ID;
            break;

         case 3:
            meas_mode = MEAS_HRV_ID;
            break;

         default:
            meas_mode = MEAS_PWA_ID;
            break;
      }
   }
   return meas_mode;
}

*/

//---------------------------------------------------------------------------
void emma_disable_speed_buttons(void)
{
   frm_main->spdbtn_patient->Enabled = false;
   frm_main->spdbtn_measure->Enabled = false;
   frm_main->spdbtn_report->Enabled = false;
   frm_main->spdbtn_analysis->Enabled = false;
   frm_main->spdbtn_idle->Enabled = false;

   frm_main->Patient1->Enabled = false;
   frm_main->Study1->Enabled = false;
   frm_main->Report1->Enabled = false;
   frm_main->Analysis1->Enabled = false;
   frm_main->Mode1->Enabled = false;
   frm_main->Privacy1->Enabled = false;
}
//---------------------------------------------------------------------------
void emma_enable_speed_buttons(void)
{
   Child_Form             *patient_form;
   CONFIG_SYSTEM_OPTIONS  cfg_options;
   MEAS_ID_TYPE           study_mode;

   cfg_options = config_get_system_options();

   frm_main->spdbtn_patient->Enabled = true;
   frm_main->spdbtn_measure->Enabled = true;
   frm_main->spdbtn_report->Enabled = true;
   frm_main->spdbtn_analysis->Enabled = true;
   frm_main->spdbtn_idle->Enabled = true;

   frm_main->Patient1->Enabled = true;
   frm_main->Study1->Enabled = true;
   frm_main->Report1->Enabled = true;
   frm_main->Analysis1->Enabled = true;
   frm_main->Privacy1->Enabled = true;

   if (cfg_options == CONFIG_PWA_OPTION || cfg_options == CONFIG_PWV_ONLY_OPTION)
   {
   }
   else
   {
      patient_form = patient_get_form_pointer();
      if (patient_form != NULL && patient_form->Visible)
      {
         frm_main->Mode1->Enabled = true;
      }
      else
      {
         frm_main->Mode1->Enabled = false;
      }

      study_mode = patient_get_study_mode();
      if (study_mode == MEAS_PWM_ID || study_mode == MEAS_HRV_ID)
      {
         frm_main->spdbtn_analysis->Enabled = false;
         frm_main->Analysis1->Enabled = false;
      }
   }
   // PM V9
   // If editing is false, disable the Analysis button
   if (!emr_get_editing())
   {
      frm_main->spdbtn_analysis->Enabled = false;
      frm_main->Analysis1->Enabled = false;
   }
}

//---------------------------------------------------------------------------
bool emma_is_initialised(void)
{
   return (emma_initialised);
}
//---------------------------------------------------------------------------
__fastcall Tfrm_main::Tfrm_main(TComponent* Owner)
    : TForm(Owner)
{
   emma_first_time = true;
   emma_initialised = false;
   emma_closing = false;
   //prgbar_main = NULL;
   if (!log_initialise()      ||
       !config_initialise()   ||
       !comms_initialise()    ||
       !dbmgr_initialise()    ||
       !multdb_initialise()   ||
       !patient_initialise()  ||
       !meas_initialise()     ||
       !report_initialise()   ||
       !analysis_initialise() ||
       !capture_initialise()  ||
       !print_initialise()    ||
       !security_initialise() ||
       !audit_initialise()    ||
       !emr_initialise()      ||
       !rtof_initialise())
   {
      Close();                                          
      Application->Terminate();
   }
   else
   {
      // Check for command line arguments
      config_decode_command_line();
      if (Screen->Height < 768 || Screen->Width < 1024)
      {
         MsgBox(MSG_CONFIG_DISPLAY_SETTINGS,
                SWARNING,
                MB_ICONEXCLAMATION | MB_OK);
      }
      Application->Title = "SphygmoCor " +SOFTWARE_MODEL_TYPE;
      //Application->HelpFile = ExtractFilePath(ParamStr(0)) +SOFTWARE_HELP_FILE;
      emma_initialised = true;
      log_write_start();
      /*prgbar_main = new TProgressBar(drw3d_status_bar);
      prgbar_main->Parent = drw3d_status_bar;
      prgbar_main->Left = 500;
      prgbar_main->Top = 4;
      prgbar_main->Height = 60;
      prgbar_main->Width = 300;
      prgbar_main->Visible = false; */
      lbl_active_database->Caption = "Active Database - " + multdb_get_active_name();
      Screen->OnActiveFormChange = ChangeActiveForm;
   }
}
//---------------------------------------------------------------------------
void __fastcall Tfrm_main::ChangeActiveForm(TObject *Sender)
{
   Child_Form *patient_form;
   Child_Form *measure_form;
   Child_Form *report_form;
   Child_Form *analysis_form;
   Child_Form *analysis_trend_form;

   // This function prevents problems with focus
   if (Screen->ActiveForm == frm_main)
   {
      patient_form = patient_get_form_pointer();
      if (patient_form == NULL)
      {
         return;
      }
      if (patient_form->Visible)
      {
         patient_form->SetFocus();
      }

      measure_form = meas_get_form_pointer();
      if (measure_form == NULL)
      {
         return;
      }
      if (measure_form->Visible)
      {                               
         measure_form->SetFocus();
      }

      report_form = report_get_form_pointer();
      if (report_form == NULL)
      {
         return;
      }
      if (report_form->Visible)
      {
         report_form->SetFocus();
      }

      analysis_form = analysis_get_analysis_form_pointer();
      if (analysis_form == NULL)
      {
         return;
      }
      if (analysis_form->Visible)
      {
         analysis_form->SetFocus();
      }

      analysis_trend_form = analysis_get_trend_form_pointer();
      if (analysis_trend_form == NULL)
      {
         return;
      }
      if (analysis_trend_form->Visible)
      {
         analysis_trend_form->SetFocus();
      }
   }
}
//---------------------------------------------------------------------------
void __fastcall Tfrm_main::FormShow(TObject *Sender)
{
   if (emma_initialised)
   {
      mnu_batch_print->Enabled = print_does_printer_exist();
   }

   // Determine the current mode and display it on the data mode label
   if (config_get_audit_option())
   {
      lbl_data_mode->Caption = AUDIT_ENABLED;
   }
   else if (emr_get_enabled())
   {
      if (emr_get_default_mode())
      {
         lbl_data_mode->Caption = EMR_DEFAULT_MODE;
      }
      else
      {
         lbl_data_mode->Caption = EMR_ENABLED;
      }
   }
   else
   {
      lbl_data_mode->Caption = "";
   }

   // PM V9
   // If editing is false, disable the Analysis button
   if (!emr_get_editing())
   {
      spdbtn_analysis->Enabled = false;
      Analysis1->Enabled = false;
   }

   lbl_message1->Caption = "";
   lbl_message2->Caption = "";
   lbl_message3->Caption = "";

   lbl_message1->Left = pnl_status_bar->Width * 0.55;
   lbl_message3->Left = pnl_status_bar->Width * 0.55;
   lbl_message2->Left = pnl_status_bar->Width / 3;
   lbl_message4->Left = pnl_status_bar->Width / 3;

   Child_Form *patient_form;
      
   if (emma_first_time)
   {
      emma_first_time = false;
      
      // The operator must successfully sign in to enter the system
      if (security_show())
      {
         patient_form = patient_get_form_pointer();
         if (patient_form != NULL)
         {
            patient_form->Show();
            // Only prompt for packing if editing is allowed
            if (emr_get_editing())
            {
               if (config_require_database_pack())
               {
                  if (MsgBox_confirmation("SphygmoCor has detected that Database Optimisation\n\nhas not been performed for a considerable period of time.\n\nWould you like to optimise the database ?",
                                          "Optimise Database") == IDYES)
                  {
                     mnu_packClick(Application);
                  }
               }
            }
         }
      }
      else
      {
         MsgBox(MSG_SECURITY_EXIT, SNOTIFICATION, MB_ICONSTOP | MB_OK);
         emma_disable_speed_buttons();
         mnu_batch_print->Enabled = false;
         mnu_merge->Enabled = false;
         mnu_pack->Enabled = false;
         mnu_export->Enabled = false;
         mnu_multdb->Enabled = false;
         mnu_listing->Enabled = false;
         mnu_export_database->Enabled = false;
         emma_display_statusbar_message("", "", "", sphygmocor_white);
         emma_display_statusbar_message("", "", sphygmocor_white);
      }
   }

   String lFileName = ExtractFilePath(Application->ExeName) + "ScorPrivacyImg.jpg";
   if (FileExists(lFileName))
   {
      img_privacy->Picture->LoadFromFile(lFileName);
      img_privacy->Visible = false;
   }
}


//---------------------------------------------------------------------------
void __fastcall Tfrm_main::mnu_print_setupClick(TObject *Sender)
{
   PrinterSetupDialog1->Execute();
}
//---------------------------------------------------------------------------
void __fastcall Tfrm_main::mnu_check_moduleClick(TObject *Sender)
{
   if (comms_open(config_get_comms_port()))
   {
      emma_display_statusbar_message("Looking For Module", "", "", sphygmocor_white);
      comms_detect_module();
      if (comms_is_module_available())
      {
         emma_display_statusbar_message("Module Found Successfully", "", "", sphygmocor_white);
      }
      else
      {
         emma_display_statusbar_message("Module Not Found", "", "", sphygmocor_maroon);
      }
      comms_close();
   }
}
//---------------------------------------------------------------------------
void __fastcall Tfrm_main::mnu_exitClick(TObject *Sender)
{
   Close();
}
//---------------------------------------------------------------------------
void __fastcall Tfrm_main::spdbtn_idleClick(TObject *Sender)
{
   Child_Form *patient_form;

   spdbtn_patientClick(this);
   patient_form = patient_get_form_pointer();
   if (patient_form != NULL)
   {
      spdbtn_idle->Down = true;
      // PM V9
      // Only display the image when on the privacy screen, otherwise the
      // switching between screens becomes very obvious to the user
      img_privacy->Visible = true;
      patient_display_idle(true);
   }
   Mode1->Enabled = false;
}

//---------------------------------------------------------------------------
void __fastcall Tfrm_main::spdbtn_reportClick(TObject *Sender)
{
   Child_Form    *report_form;
   Child_Form    *patient_form;
   Child_Form    *analysis_form;
   Child_Form    *analysis_trend_form;
   Child_Form    *measure_form;

   Screen->Cursor = crHourGlass;
   img_privacy->Visible = false;

   patient_form = patient_get_form_pointer();

   measure_form = meas_get_form_pointer();
   if (measure_form == NULL)
   {
     return;
   }

   try
   {
      emma_disable_speed_buttons();

      analysis_form = analysis_get_analysis_form_pointer();
      analysis_trend_form = analysis_get_trend_form_pointer();

      if (patient_form->Visible)
      {
         patient_update_measurement_count();
      }

      if (patient_get_nof_measurements())
      {
          if (patient_form->Visible)
          {
             patient_form->Hide();
          }

          if (measure_form->Visible)
          {
             measure_form->Hide();
          }

          if (analysis_form->Visible)
          {
             analysis_form->Hide();
          }

          if (analysis_trend_form->Visible)
          {
             analysis_trend_form->Hide();
          }

          spdbtn_report->Down = true;
          report_form = report_get_form_pointer();
          if (report_form->Visible == false)
          {
             report_form->Show();
          }
      }
      else
      {
         MsgBox(LoadStr(MSG_NO_REPORTS_FOR_PATIENT),
                        SNOTIFICATION,
                        MB_ICONINFORMATION);

         if (patient_form->Visible)
         {
            spdbtn_patient->Down = true;
         }

         if (measure_form->Visible)
         {
            spdbtn_measure->Down = true;
         }

         if (analysis_form->Visible || analysis_trend_form->Visible)
         {
            spdbtn_analysis->Down = true;
         }
      }
   }
   catch (Exception &exception)
   {
      log_write(SERROR +exception.Message);
   }
   emma_enable_speed_buttons();
   Screen->Cursor = crDefault;
}
//---------------------------------------------------------------------------
void __fastcall Tfrm_main::spdbtn_analysisClick(TObject *Sender)
{
   Child_Form   *report_form;
   Child_Form   *patient_form;
   Child_Form   *analysis_form;
   Child_Form   *analysis_trend_form;
   Child_Form   *measure_form;
   MEAS_ID_TYPE  meas_mode = patient_get_study_mode();

   Screen->Cursor = crHourGlass;
   img_privacy->Visible = false;

   patient_form = patient_get_form_pointer();

   measure_form = meas_get_form_pointer();

   if (measure_form == NULL)
   {
      return;
   }
   report_form = report_get_form_pointer();
   analysis_trend_form = analysis_get_trend_form_pointer();

   try
   {
      emma_disable_speed_buttons();
      if (patient_form->Visible)
      {
         patient_update_measurement_count();
      }

      if (patient_get_nof_measurements() > 1)
      {
          if (patient_form->Visible)
          {
             patient_form->Hide();
          }

          if (measure_form->Visible)
          {
             measure_form->Hide();
          }

          if (report_form->Visible)
          {
              report_form->Hide();
          }

          spdbtn_analysis->Down = true;
          analysis_form = analysis_get_analysis_form_pointer();
          analysis_form->Show();

          // Only display the Trend Form if there are more than 2 reports
          // taking deleted reports into account if audit mode is enabled
          if (analysis_get_audit_initialised())
          {
             // PM V9
             // There is no trend form in PWV mode anymore
             if (meas_mode == MEAS_PWA_ID)
             {
                // Always show the trend form first
                if (analysis_form->Visible)
                {
                   analysis_form->Hide();
                }
                analysis_trend_form->Show();
             }
          }
      }
      else
      {
         MsgBox(MSG_NO_STUDIES_FOR_ANALYSIS, SNOTIFICATION, MB_ICONINFORMATION);

         if (patient_form->Visible)
         {
            spdbtn_patient->Down = true;
         }

         if (measure_form->Visible)
         {
            measure_form->Show();
            spdbtn_measure->Down = true;
         }

         if (report_form->Visible)
         {
            report_form->Show();
            spdbtn_report->Down = true;
         }
      }
   }
   catch (Exception &exception)
   {
      log_write(SERROR +exception.Message);
   }
   emma_enable_speed_buttons();
   Screen->Cursor = crDefault;
}
//---------------------------------------------------------------------------
void __fastcall Tfrm_main::spdbtn_measureClick(TObject *Sender)
{
   Child_Form   *report_form;
   Child_Form   *patient_form;
   Child_Form   *analysis_form;
   Child_Form   *analysis_trend_form;
   Child_Form   *measure_form;

   Screen->Cursor = crHourGlass;
   img_privacy->Visible = false;
   measure_form = meas_get_form_pointer();
   if (measure_form == NULL)
   {
      return;
   }

   try
   {
      patient_form = patient_get_form_pointer();
      if (patient_form->Visible)
      {
         patient_form->Hide();
      }

      report_form = report_get_form_pointer();
      if (report_form->Visible)
      {
         report_form->Hide();
      }

      analysis_trend_form = analysis_get_trend_form_pointer();
      if (analysis_trend_form->Visible)
      {
         analysis_trend_form->Hide();
      }

      analysis_form = analysis_get_analysis_form_pointer();
      if (analysis_form->Visible)
      {
         analysis_form->Hide();
      }

      emma_disable_speed_buttons();
      spdbtn_measure->Down = true;
      measure_form->Show();
   }
   catch (Exception &exception)
   {
      log_write(SERROR +exception.Message);
   }
   emma_enable_speed_buttons();
   Screen->Cursor = crDefault;
}
//---------------------------------------------------------------------------
void __fastcall Tfrm_main::mnu_settingsClick(TObject *Sender)
{
   config_show();
}
//---------------------------------------------------------------------------
void __fastcall Tfrm_main::FormClose(TObject *Sender, TCloseAction &Action)
{
   if (emma_initialised)
   {
      if (patient_can_close())
      {
         if (MsgBox(MSG_CLOSE_PROGRAM,
                    CONFIRMATION,
                    MB_YESNO | MB_ICONQUESTION) != ID_YES)
         {
           Action = caNone;
           return;
         }
      }
      else
      {
         Action = caNone;
         return;
      }
   }
   try
   {
     // Destroy all
     capture_destroy();
     comms_destroy();
     analysis_destroy();
     report_destroy();
     patient_destroy();
     meas_destroy();
     dbmgr_destroy();
     print_destroy();
     multdb_destroy();
     config_destroy();
     log_destroy();
     security_destroy();
     audit_destroy();
     emr_destroy();
     /*if (prgbar_main != NULL)
     {
        delete (prgbar_main);
        prgbar_main = NULL;
     }*/
   }
   catch (Exception &exc)
   {
      MsgBox_show(TERROR,
                  MSG_EXCEPTION,
                  LoadStr(MSG_EXCEPTION),
                  MSG_EXCEPTION,
                  LoadStr(MSG_EXCEPTION) +exc.Message);
   }
   emma_closing = true;
   emma_initialised = false;
   Action = caFree;
}

void __fastcall Tfrm_main::img_pwvmedClick(TObject *Sender)
{
  frm_aboutbox = new Tfrm_aboutbox(this);
  frm_aboutbox->btn_ok->Visible = true;
  frm_aboutbox->ShowModal();
  delete frm_aboutbox;
}
//---------------------------------------------------------------------------
void __fastcall Tfrm_main::mnu_batch_printClick(TObject *Sender)
{
   print_batch_show();
}
//---------------------------------------------------------------------------
void __fastcall Tfrm_main::mnu_export_click(TObject *Sender)
{
   Screen->Cursor = crHourGlass;
   MEAS_ID_TYPE  meas_mode = patient_get_study_mode();
   switch (meas_mode)
   {
      case MEAS_PWA_ID:
      {

         String lFileName = ExtractFilePath(Application->ExeName) + EXPORT_SUBDIR +
                "All_" + multdb_get_active_name() + "_" +Now().FormatString("ddmmmyyyy") + "_pwa.txt";
         if (dbmgr_open(DBMGR_MEASURE_PWA_TABLE, false)==true)
         {
            patient_enable_database_events(false, true);
            String S = PATIENT_SYSTEM_ID +  ";" + PATIENT_STUDY_ID + ";" + PATIENT_NO + ";" + MPW_DATETIME;
            dbmgr_select_index(DBMGR_MEASURE_PWA_TABLE, S);
            TDataSet *meas_pwa_table = (TDataSet *)dbmgr_get_dataset(DBMGR_MEASURE_PWA_TABLE, false);
            export_all_measurements(meas_pwa_table, lFileName, meas_get_current_pwa());
            dbmgr_close(DBMGR_MEASURE_PWA_TABLE, false);
            patient_enable_database_events(true, true);
         }
         break;
      }
      case MEAS_PWV_ID:
      {
         String lFileName = ExtractFilePath(Application->ExeName) + EXPORT_SUBDIR +
                "All_" + multdb_get_active_name() + "_" + Now().FormatString("ddmmmyyyy") + "_pwv.txt";
         if (dbmgr_open(DBMGR_MEASURE_PWV_TABLE, false)==true)
         {
            patient_enable_database_events(false, true);
            String S = PATIENT_SYSTEM_ID +  ";" + PATIENT_STUDY_ID + ";" + PATIENT_NO + ";" + MPW_DATETIME;
            dbmgr_select_index(DBMGR_MEASURE_PWV_TABLE, S);
            TDataSet *meas_pwv_table = (TDataSet *)dbmgr_get_dataset(DBMGR_MEASURE_PWV_TABLE, false);
            export_all_measurements(meas_pwv_table, lFileName, meas_get_current_pwv());
            dbmgr_close(DBMGR_MEASURE_PWV_TABLE, false);
            patient_enable_database_events(true, true);
         }
         break;
      }
      case MEAS_PWM_ID:
      {
         String lFileName = ExtractFilePath(Application->ExeName) + EXPORT_SUBDIR +
                "All_" + multdb_get_active_name() + "_" + Now().FormatString("ddmmmyyyy") + "_pwm.txt";
         if (dbmgr_open(DBMGR_MEASURE_PWM_TABLE, false)==true)
         {
            patient_enable_database_events(false, true);
            String S = PATIENT_SYSTEM_ID +  ";" + PATIENT_STUDY_ID + ";" + PATIENT_NO + ";" + MPW_DATETIME;
            dbmgr_select_index(DBMGR_MEASURE_PWM_TABLE, S);
            TDataSet *meas_pwm_table = (TDataSet *)dbmgr_get_dataset(DBMGR_MEASURE_PWM_TABLE, false);
            export_all_measurements(meas_pwm_table, lFileName, meas_get_current_pwm());
            dbmgr_close(DBMGR_MEASURE_PWM_TABLE, false);
            patient_enable_database_events(true, true);
         }
         break;
      }
      case MEAS_HRV_ID:
      {
         String lFileName = ExtractFilePath(Application->ExeName) + EXPORT_SUBDIR +
                "All_" + multdb_get_active_name() + "_" + Now().FormatString("ddmmmyyyy") + "_hrv.txt";
         if (dbmgr_open(DBMGR_MEASURE_HRV_TABLE, false)==true)
         {
            patient_enable_database_events(false, true);
            String S = PATIENT_SYSTEM_ID +  ";" + PATIENT_STUDY_ID + ";" + PATIENT_NO + ";" + MPW_DATETIME;
            dbmgr_select_index(DBMGR_MEASURE_HRV_TABLE, S);
            TDataSet *meas_hrv_table = (TDataSet *)dbmgr_get_dataset(DBMGR_MEASURE_HRV_TABLE, false);
            export_all_measurements(meas_hrv_table, lFileName, meas_get_current_hrv());
            dbmgr_close(DBMGR_MEASURE_HRV_TABLE, false);
            patient_enable_database_events(true, true);
         }
         break;
      }
   }
   Screen->Cursor = crDefault;
}
//---------------------------------------------------------------------------
void __fastcall Tfrm_main::mnu_multdbClick(TObject *Sender)
{
   multdb_show_form();
   patient_update_active_database();
}
//---------------------------------------------------------------------------
void __fastcall Tfrm_main::FormDestroy(TObject *Sender)
{
	 Screen->OnActiveFormChange = NULL;
}
//---------------------------------------------------------------------------



void __fastcall Tfrm_main::mnu_listingClick(TObject *Sender)
{
   patient_listing_preview(true);
}
//---------------------------------------------------------------------------


void __fastcall Tfrm_main::mnu_mergeClick(TObject *Sender)
{
   TADOTable   *pat_table;
   TADOTable   *meas_pwa_table;
   TADOTable   *meas_pwv_table;
   Child_Form  *patient_form;
   bool        patient_was_open = false;
   bool        measure_pwa_was_open = false;
   bool        measure_pwv_was_open = false;

   patient_form = patient_get_form_pointer();
   if (patient_form != NULL)
   {
      if (patient_form->Visible)
      {
         if (dbmgr_is_open(DBMGR_PATIENT_TABLE, false))
         {
            dbmgr_close(DBMGR_PATIENT_TABLE, false);
            patient_was_open = true;
         }
         if (dbmgr_is_open(DBMGR_MEASURE_PWA_TABLE, false))
         {
            dbmgr_close(DBMGR_MEASURE_PWA_TABLE, false);
            measure_pwa_was_open = true;
         }
         if (dbmgr_is_open(DBMGR_MEASURE_PWV_TABLE, false))
         {
            dbmgr_close(DBMGR_MEASURE_PWV_TABLE, false);
            measure_pwv_was_open = true;
         }
         pat_table = (TADOTable *)dbmgr_get_dataset(DBMGR_PATIENT_TABLE, false);
         meas_pwa_table = (TADOTable *)dbmgr_get_dataset(DBMGR_MEASURE_PWA_TABLE, false);
         meas_pwv_table = (TADOTable *)dbmgr_get_dataset(DBMGR_MEASURE_PWV_TABLE, false);

         patient_enable_post_message(false);
         patient_enable_database_events(false, false);
         multb_merge_database_tables(pat_table,
                                     meas_pwa_table,
                                     meas_pwv_table);
         patient_enable_database_events(true, true);
         patient_enable_post_message(true);

         if (patient_was_open)
         {
            if (dbmgr_open(DBMGR_PATIENT_TABLE, false))
            {
               patient_update_count();
            }
         }
         if (measure_pwa_was_open)
         {
            dbmgr_open(DBMGR_MEASURE_PWA_TABLE, false);
         }
         if (measure_pwv_was_open)
         {
            dbmgr_open(DBMGR_MEASURE_PWV_TABLE, false);
         }
      }
   }
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_main::mnu_packClick(TObject *Sender)
{
   Child_Form  *patient_form;

   patient_form = patient_get_form_pointer();
   if (patient_form != NULL)
   {
      if (patient_form->Visible)
      {
         patient_enable_post_message(false);
         patient_enable_database_events(false, false);
         multdb_pack();
         patient_enable_database_events(true, true);
         patient_enable_post_message(true);
         if (dbmgr_open(DBMGR_PATIENT_TABLE, false))
         {
            patient_update_count();
         }
      }
   }
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_main::mnu_export_databaseClick(TObject *Sender)
{
   export_database_show();
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_main::mnu_recalculate_allClick(TObject *Sender)
{
   report_recalculate_all(Sender);
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_main::Mode1Click(TObject *Sender)
{
   MEAS_ID_TYPE  study_mode;
   Child_Form  *patient_form;

   patient_form = patient_get_form_pointer();
   if (patient_form != NULL)
   {
      if (patient_form->Visible)
      {
         study_mode = patient_get_study_mode();
         switch (study_mode)
         {
            case MEAS_PWA_ID:
               if (frm_patient->spbtn_hrv_mode->Visible)
               {
                  frm_patient->spbtn_hrv_modeClick(Sender);
               }
               else if (frm_patient->spbtn_pwv_mode->Visible)
               {
                  frm_patient->spbtn_pwv_modeClick(Sender);
               }
               else if (frm_patient->spbtn_pwm_mode->Visible)
               {
                  frm_patient->spbtn_pwm_modeClick(Sender);
               }
               break;

            case MEAS_HRV_ID:
               if (frm_patient->spbtn_pwv_mode->Visible)
               {
                  frm_patient->spbtn_pwv_modeClick(Sender);
               }
               else if (frm_patient->spbtn_pwm_mode->Visible)
               {
                  frm_patient->spbtn_pwm_modeClick(Sender);
               }
               else if (frm_patient->spbtn_pwa_mode->Visible)
               {
                  frm_patient->spbtn_pwa_modeClick(Sender);
               }
               break;

            case MEAS_PWV_ID:
               if (frm_patient->spbtn_pwm_mode->Visible)
               {
                  frm_patient->spbtn_pwm_modeClick(Sender);
               }
               else if (frm_patient->spbtn_pwa_mode->Visible)
               {
                  frm_patient->spbtn_pwa_modeClick(Sender);
               }
               else if (frm_patient->spbtn_hrv_mode->Visible)
               {
                  frm_patient->spbtn_hrv_modeClick(Sender);
               }
               break;

            case MEAS_PWM_ID:
               if (frm_patient->spbtn_pwa_mode->Visible)
               {
                  frm_patient->spbtn_pwa_modeClick(Sender);
               }
               else if (frm_patient->spbtn_hrv_mode->Visible)
               {
                  frm_patient->spbtn_hrv_modeClick(Sender);
               }
               else if (frm_patient->spbtn_pwv_mode->Visible)
               {
                  frm_patient->spbtn_pwv_modeClick(Sender);
               }
               break;
         }
      }
   }
}
//---------------------------------------------------------------------------


void __fastcall Tfrm_main::spdbtn_patientClick(TObject *Sender)
{
   Child_Form *patient_form;
   Child_Form *measure_form;
   Child_Form *report_form;
   Child_Form *analysis_form;
   Child_Form *analysis_trend_form;

   Screen->Cursor = crHourGlass;
   mnu_settings->Enabled = true;
   img_privacy->Visible = false;

   measure_form = meas_get_form_pointer();
   if (measure_form == NULL)
   {
      return;
   }
   if (measure_form->Visible)
   {
      measure_form->Hide();
   }

   report_form = report_get_form_pointer();
   if (report_form == NULL)
   {
      return;
   }
   if (report_form->Visible)
   {
      report_form->Hide();
   }

   analysis_form = analysis_get_analysis_form_pointer();
   if (analysis_form == NULL)
   {
      return;
   }
   if (analysis_form->Visible)
   {
      analysis_form->Hide();
   }

   analysis_trend_form = analysis_get_trend_form_pointer();
   if (analysis_trend_form == NULL)
   {
      return;
   }
   if (analysis_trend_form->Visible)
   {
      analysis_trend_form->Hide();
   }

   patient_form = patient_get_form_pointer();
   if (patient_form != NULL)
   {
      spdbtn_patient->Down = true;
      patient_display_idle(false);
      patient_form->Show();
      Mode1->Enabled = true;
   }
   Screen->Cursor = crDefault;
}
//---------------------------------------------------------------------------
void __fastcall Tfrm_main::mnu_find_moduleClick(TObject *Sender)
{
   if (MsgBox_confirmation("This will search available Comms Ports for the Electronics Module.\nThis operation can take several minutes depending on the number of ports.\n\nDo you want to continue?",
                           SWARNING) != IDYES)
   {
      return;
   }

   Screen->Cursor = crHourGlass;
   emma_display_statusbar_message("Looking For Module", "", "", sphygmocor_white);
   if (config_find_module())
   {
      emma_display_statusbar_message("Module Found Successfully", "", "", sphygmocor_white);
      log_write("Find Module: Module Found Successfully on Port " + IntToStr(config_get_comms_port()));
   }
   else
   {
      emma_display_statusbar_message("Module Not Found", "", "", sphygmocor_maroon);
      log_write("Find Module: Module Not Found.");
   }
   Screen->Cursor = crDefault;
}
//---------------------------------------------------------------------------

