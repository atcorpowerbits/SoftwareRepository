//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include <meas/pubserv.h>
#include <msg/pubserv.h>
#include <dbmgr/pubserv.h>
#include <patient/pubserv.h>
#include <report/pubserv.h>
#include <print/pubserv.h>
#include <config/pubserv.h>
#include <scor/form_main.h>
#include "form_batchprint.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

const int bprint_maximum_period = 14;
const String BATCH_DATETIMEFORMAT = "dd mmm yyyy, hh:nn:ss";

bool print_batch_show(void)
{
   bool status = false;

   Tfrm_batchprint *frm_bp = new Tfrm_batchprint(Application->MainForm);

   if (frm_bp != NULL)
   {
      frm_bp->ShowModal();

      status = (frm_bp->ModalResult == mrYes);
      delete frm_bp;
   }
   return status;
}

//---------------------------------------------------------------------------
__fastcall Tfrm_batchprint::Tfrm_batchprint(TComponent* Owner)
    : TForm(Owner)
{
   print_index = new TStringList;

   pwa_data = NULL;
   pwv_data = NULL;
}
void __fastcall Tfrm_batchprint::FormShow(TObject *Sender)
{
   MEAS_ID_TYPE  meas_id;

   meas_id = patient_get_study_mode();

   switch (meas_id)
   {
      case MEAS_PWA_ID:
         pwa_data = meas_get_current_pwa();
         table_id = DBMGR_MEASURE_PWA_TABLE;
         // PM CR
         if (config_get_clinical_option())
         {
            chkbx_print_clinical->Visible = false;
            chkbx_print_clinical->Enabled = false;
            chkbx_print_clinical->Checked = true;
         }
         else
         {
            chkbx_print_clinical->Visible = true;
            chkbx_print_clinical->Enabled = true;
            chkbx_print_clinical->Checked = false;
         }
         break;
      case MEAS_PWV_ID:
         pwv_data = meas_get_current_pwv();
         table_id = DBMGR_MEASURE_PWV_TABLE;
         chkbx_print_clinical->Visible = false;
         chkbx_print_clinical->Enabled = false;
         chkbx_print_clinical->Checked = false;
         break;
      case MEAS_PWM_ID:
         pwm_data = meas_get_current_pwm();
         table_id = DBMGR_MEASURE_PWM_TABLE;
         chkbx_print_clinical->Visible = true;
         chkbx_print_clinical->Enabled = true;
         chkbx_print_clinical->Checked = false;
         break;
      default:
         break;
   }
   dtpk_start->MaxDate = Date();
   dtpk_end->MaxDate = Date();
   dtpk_start->Date = Date();
   dtpk_end->Date = Date();
   lstbx_in->Items->Clear();
   lstbx_out->Items->Clear();
   print_index->Clear();
   bbtn_print_selected->Enabled = false;
   bbtn_print_all->Enabled = false;
   stop_print = false;
}

void __fastcall Tfrm_batchprint::query_database()
{
   MEAS_ID_TYPE  meas_id;
   int           i;
   AnsiString    user_str;
   AnsiString    system_id;
   AnsiString    study_id;
   AnsiString    patient_num;
   TDateTime     meas_date;

   Screen->Cursor = crHourGlass;

   lstbx_in->Items->Clear();
   lstbx_out->Items->Clear();
   print_index->Clear();

   //find entries which are within start and end dates
   qry_date = dbmgr_setup_query(table_id,
                                DBMGR_QUERY_DATETIME,
                                MPW_DATETIME,
                                "",
                                "",
                                AnsiString(int(dtpk_start->Date)),
                                AnsiString(int(dtpk_end->Date) + 1),
                                "",
                                MPW_DATETIME);

   if (qry_date == NULL || qry_date->RecordCount <= 0)
   {
     MsgBox(MSG_NO_RECORDS_FOR_THIS_PERIOD, SWARNING, MB_ICONEXCLAMATION);
     Screen->Cursor = crDefault;
     return;
   }
   qry_date->First();
   lbl_total_studies_num->Caption = IntToStr(qry_date->RecordCount);
   lbl_progress_text->Caption = "";

   meas_id = patient_get_study_mode();
   records = new int[qry_date->RecordCount];

   for (i = 0; i < qry_date->RecordCount; i++)
   {
      lbl_progress_text->Caption = IntToStr(i + 1) + " of " +lbl_total_studies_num->Caption;
      Application->ProcessMessages();
      switch (meas_id)
      {
         case MEAS_PWA_ID:
            pwa_data->Populate(qry_date);
            user_str = pwa_data->DateTime.FormatString(BATCH_DATETIMEFORMAT);
            system_id = pwa_data->System_ID;
            study_id =  pwa_data->Study_ID;
            patient_num = IntToStr(pwa_data->Patient_No);
            meas_date = pwa_data->DateTime;
            break;
         case MEAS_PWV_ID:
            pwv_data->Populate(qry_date);
            user_str = pwv_data->DateTime.FormatString(BATCH_DATETIMEFORMAT);
            system_id = pwv_data->System_ID;
            study_id =  pwv_data->Study_ID;
            patient_num = IntToStr(pwv_data->Patient_No);
            meas_date = pwv_data->DateTime;
            break;
         case MEAS_PWM_ID:
            pwm_data->Populate(qry_date);
            user_str = pwm_data->DateTime.FormatString(BATCH_DATETIMEFORMAT);
            system_id = pwm_data->System_ID;
            study_id =  pwm_data->Study_ID;
            patient_num = IntToStr(pwm_data->Patient_No);
            meas_date = pwm_data->DateTime;
            break;
         default:
            break;
      }

      qry_name = dbmgr_setup_query(DBMGR_PATIENT_TABLE,
                                   DBMGR_QUERY_KEY,
                                   PATIENT_SYSTEM_ID,
                                   PATIENT_STUDY_ID,
                                   PATIENT_NO,
                                   system_id,
                                   study_id,
                                   patient_num);
      if (qry_name != NULL)
      {
         if (qry_name->RecordCount == 1)
         {
            user_str = user_str + " - "   + qry_name->FieldByName(PATIENT_SURNAME)->AsString
                 + ", "    + qry_name->FieldByName(PATIENT_FIRST_NAME)->AsString;
         }
      }
      records[i] = i;
      lstbx_in->Items->AddObject(user_str, (TObject *)&records[i]);
      lstbx_in->Update();
      qry_date->Next();
   }
   lbl_progress_text->Caption = "";
   Screen->Cursor = crDefault;

   if (qry_date->RecordCount)
   {
      bbtn_print_all->Enabled = true;
   }

   EnableButtons();
}

//---------------------------------------------------------------------------
void __fastcall Tfrm_batchprint::EnableButtons()
{
  spbtn_deleteall->Enabled = (lstbx_out->Items->Count > 0);
  spbtn_delete->Enabled = (lstbx_out->SelCount > 0);
  spbtn_addall->Enabled = (lstbx_in->Items->Count > 0);
  spbtn_add->Enabled = (lstbx_in->SelCount > 0);
  bbtn_print_all->Enabled = (lstbx_in->Items->Count > 0);
  bbtn_print_selected->Enabled = (lstbx_out->Items->Count > 0);
}
void __fastcall Tfrm_batchprint::dtpk_startChange(TObject *Sender)
{
   if (dtpk_start->Date > dtpk_end->Date)
   {
      dtpk_end->Date = dtpk_start->Date;
   }
   if (int(dtpk_end->Date - dtpk_start->Date) > bprint_maximum_period)
   {
      dtpk_end->Date = dtpk_start->Date + bprint_maximum_period;
   }
}

void __fastcall Tfrm_batchprint::dtpk_endChange(TObject *Sender)
{
   if (dtpk_start->Date > dtpk_end->Date)
   {
      dtpk_start->Date = dtpk_end->Date;
   }
   if (int(dtpk_end->Date - dtpk_start->Date) > bprint_maximum_period)
   {
      dtpk_start->Date = dtpk_end->Date - bprint_maximum_period;
   }
}

void __fastcall Tfrm_batchprint::bbtn_get_recordsClick(TObject *Sender)
{
   this->query_database();
   EnableButtons();
}

void __fastcall Tfrm_batchprint::spbtn_addClick(TObject *Sender)
{
   int  i;

   while (lstbx_in->SelCount > 0)
   {
      for (i = 0; i < lstbx_in->Items->Count; i++)
      {
         if (lstbx_in->Selected[i])
         {
            lstbx_out->Items->AddObject(lstbx_in->Items->Strings[i],
                                        lstbx_in->Items->Objects[i]);
            lstbx_in->Items->Delete(i);
         }
      }
   }
   EnableButtons();
}
//---------------------------------------------------------------------------
void __fastcall Tfrm_batchprint::spbtn_addallClick(TObject *Sender)
{
   int i;
   int total_in;

   total_in = lstbx_in->Items->Count;
   for (i = 0; i < total_in; i++)
   {
      lstbx_in->Selected[i] = true;
   }

   for (i = 0; i < total_in; i++)
   {
      if (lstbx_in->Selected[i])
      {
         lstbx_out->Items->AddObject(lstbx_in->Items->Strings[i],
                                     lstbx_in->Items->Objects[i]);

      }
   }

   for (i = 0; i < total_in; i++)
   {
      lstbx_in->Items->Delete(lstbx_in->Items->Count - 1);
   }
   EnableButtons();
}
//---------------------------------------------------------------------------
void __fastcall Tfrm_batchprint::spbtn_deleteClick(TObject *Sender)
{
   int  i;

   while (lstbx_out->SelCount > 0)
   {
      for (i = 0; i < lstbx_out->Items->Count; i++)
      {
         if (lstbx_out->Selected[i])
         {
            lstbx_in->Items->AddObject(lstbx_out->Items->Strings[i],
                                       lstbx_out->Items->Objects[i]);
            lstbx_out->Items->Delete(i);
         }
      }
   }
   EnableButtons();
}

void __fastcall Tfrm_batchprint::spbtn_deleteallClick(TObject *Sender)
{
   int i;
   int total_out;

   total_out = lstbx_out->Items->Count;
   for (i = 0; i < total_out; i++)
   {
      lstbx_out->Selected[i] = true;
   }

   for (i = 0; i < total_out; i++)
   {
      if (lstbx_out->Selected[i])
      {
         lstbx_in->Items->AddObject(lstbx_out->Items->Strings[i],
                                    lstbx_out->Items->Objects[i]);
      }
   }

   for (i = 0; i < total_out; i++)
   {
      lstbx_out->Items->Delete(lstbx_out->Items->Count - 1);
   }
   EnableButtons();
}

void __fastcall Tfrm_batchprint::bbtn_print_selectedClick(TObject *Sender)
{
   int i = 0;
   int index;

   while (i < lstbx_out->Items->Count)
   {
      index = *((int *)lstbx_out->Items->Objects[i]);
      print_index->Add(index);
      ++i;
   }
   this->print();
}

void __fastcall Tfrm_batchprint::bbtn_print_allClick(TObject *Sender)
{
   int i;

   print_index->Clear();
   for (i = 0; i < qry_date->RecordCount; i++)
   {
      print_index->Add(i);
   }
   this->print();
}

void __fastcall Tfrm_batchprint::bbtn_cancel_printClick(TObject *Sender)
{
   stop_print = true;
   Abort();
}

void __fastcall Tfrm_batchprint::print()
{
   PATIENT_RECORD_TYPE  *pat;
   MEAS_ID_TYPE         meas_id;
   int                  i;
   int                  move_by;
   AnsiString           user_str;
   AnsiString           system_id;
   AnsiString           study_id;
   AnsiString           patient_num;
   TDateTime            meas_date;

   pat = new PATIENT_RECORD_TYPE;
   
   pnl_buttons->Visible = false;
   pnl_status->Visible = true;
   pnl_select->Enabled = false;
   pnl_records->Enabled = false;
   progress_bar->Position = 0;
   progress_bar->Max = print_index->Count - 1;

   meas_id = patient_get_study_mode();
   //move through print_index

   try
   {
      for (i = 0; i < print_index->Count; i++)
      {
         Application->ProcessMessages();
         qry_date->First();
         move_by = print_index->Strings[i].ToIntDef(0);
         if (move_by < qry_date->RecordCount)
         {
            qry_date->MoveBy(move_by);
            switch (meas_id)
            {
               case MEAS_PWA_ID:
                  pwa_data->Populate(qry_date);
                  user_str = pwa_data->DateTime.FormatString(BATCH_DATETIMEFORMAT);
                  system_id = pwa_data->System_ID;
                  study_id =  pwa_data->Study_ID;
                  patient_num = IntToStr(pwa_data->Patient_No);
                  meas_date = pwa_data->DateTime;
                  break;
               case MEAS_PWV_ID:
                  pwv_data->Populate(qry_date);
                  user_str = pwv_data->DateTime.FormatString(BATCH_DATETIMEFORMAT);
                  system_id = pwv_data->System_ID;
                  study_id =  pwv_data->Study_ID;
                  patient_num = IntToStr(pwv_data->Patient_No);
                  meas_date = pwv_data->DateTime;
                  break;
               case MEAS_PWM_ID:
                  pwm_data->Populate(qry_date);
                  user_str = pwm_data->DateTime.FormatString(BATCH_DATETIMEFORMAT);
                  system_id = pwm_data->System_ID;
                  study_id =  pwm_data->Study_ID;
                  patient_num = IntToStr(pwm_data->Patient_No);
                  meas_date = pwm_data->DateTime;
                  break;
               default:
                  break;
            }
            //find patient data
            qry_name = dbmgr_setup_query(DBMGR_PATIENT_TABLE,
                                         DBMGR_QUERY_KEY,
                                         PATIENT_SYSTEM_ID,
                                         PATIENT_STUDY_ID,
                                         PATIENT_NO,
                                         system_id,
                                         study_id,
                                         patient_num);
            //populate patient parameters
            if (qry_name != NULL)
            {
               patient_populate_record(pat, qry_name);

               //update status bar fields
               qry_name->First();
               if (qry_name->RecordCount == 1)
               {
                  user_str = user_str + " - "   + qry_name->FieldByName(PATIENT_SURNAME)->AsString
                             + ", "    + qry_name->FieldByName(PATIENT_FIRST_NAME)->AsString;
               }
               status_bar->Panels->Items[0]->Text = user_str;

               user_str = AnsiString(i + 1) + "/" + AnsiString(print_index->Count);
               status_bar->Panels->Items[1]->Text = user_str;

               //update progress_bar
               progress_bar->Position = i;

               //print report
               switch (meas_id)
               {
                  case MEAS_PWA_ID:
                     report_pwa_batch_print(pwa_data, pat, chkbx_print_clinical->Checked);
                     break;
                  case MEAS_PWV_ID:
                     report_pwv_batch_print(pwv_data, pat);
                     break;
                  case MEAS_PWM_ID:
                     pwa_data = dynamic_cast<TPWA *>(pwm_data);
                     report_pwa_batch_print(pwa_data, pat, chkbx_print_clinical->Checked);
                     break;
                  default:
                     break;
               }

               if (stop_print)
               {
                  break;
               }
            }
         }
      }
   }
   catch (...)
   {
      ;
   }

   if (qry_date != NULL)
   {
      qry_date->Close();
   }
   if (qry_name != NULL)
   {
      qry_name->Close();
   }
   delete pat;

   Close();
}

void __fastcall Tfrm_batchprint::FormClose(TObject *Sender,
      TCloseAction &Action)
{
   Action = caFree;
}
//---------------------------------------------------------------------------
void __fastcall Tfrm_batchprint::FormDestroy(TObject *Sender)
{
   if (print_index != NULL)
   {
      print_index->Clear();
      delete print_index;
   }
   if (records != NULL)
   {
      delete records;
   }
}
void __fastcall Tfrm_batchprint::lstbx_inClick(TObject *Sender)
{
  EnableButtons();
}
//---------------------------------------------------------------------------
void __fastcall Tfrm_batchprint::lstbx_outClick(TObject *Sender)
{
  EnableButtons();
}
//---------------------------------------------------------------------------
void __fastcall Tfrm_batchprint::bbtn_cancelClick(TObject *Sender)
{
   ModalResult = mrCancel;
}
//---------------------------------------------------------------------------

