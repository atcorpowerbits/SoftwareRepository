//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include <export/pubserv.h>
#include <msg/pubserv.h>
#include <meas/pubserv.h>
#include <dbmgr/pubserv.h>
#include <patient/pubserv.h>
#include <scor/form_selectdir.h>
#include <scor/utils.h>
#include <config/pubserv.h>
//#include "attrib.h"
#include "form_export_database.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
Tfrm_export_database *frm_export_database;

const int export_maximum_period = 31;
const int EXPORTED_DATABASE_RECORD_SIZE = 30*1024;
const String EXPORT_DATETIMEFORMAT = "dd mmm yyyy, hh:nn:ss";
                                                                        
//---------------------------------------------------------------------------
__fastcall Tfrm_export_database::Tfrm_export_database(TComponent* Owner)
        : TForm(Owner)
{
   // Initialise data members
   export_index = new TStringList;
   patients = new TStringList;
   pwa_data = NULL;
}
//---------------------------------------------------------------------------
bool export_database_show(void)
{
   // Display the export database form
   bool status = false;

   Tfrm_export_database *frm_export_database = new Tfrm_export_database(Application->MainForm);

   if (frm_export_database != NULL)
   {
      frm_export_database->ShowModal();

      status = (frm_export_database->ModalResult == mrYes);
      delete frm_export_database;
   }
   return status;
}

void __fastcall Tfrm_export_database::FormShow(TObject *Sender)
{
   // Populate data members
   pwa_data = meas_get_current_pwa();

   dtpk_start->MaxDate = Date();
   dtpk_end->MaxDate = Date();
   dtpk_start->Date = Date();
   dtpk_end->Date = Date();
   lstbx_studies->Items->Clear();
   lstbx_exports->Items->Clear();
   bbtn_export_all->Enabled = false;
   bbtn_export_selected->Enabled = false;
   stop_export = false;
   memMsg->Clear();
}
//---------------------------------------------------------------------------
void __fastcall Tfrm_export_database::EnableButtons()
{
  //Enable appropriate buttons
  spbtn_deleteall->Enabled = (lstbx_exports->Items->Count > 0);
  spbtn_delete->Enabled = (lstbx_exports->SelCount > 0);
  spbtn_addall->Enabled = (lstbx_studies->Items->Count > 0);
  spbtn_add->Enabled = (lstbx_studies->SelCount > 0);
  bbtn_export_all->Enabled = (lstbx_studies->Items->Count > 0);
  bbtn_export_selected->Enabled = (lstbx_exports->Items->Count > 0);
}

void __fastcall Tfrm_export_database::dtpk_startChange(TObject *Sender)
{
   // Ensure the start date is before the end date
   // and that the maximum period is not exceeded
   if (dtpk_start->Date > dtpk_end->Date)
   {
      dtpk_end->Date = dtpk_start->Date;
   }
   if (int(dtpk_end->Date - dtpk_start->Date) > export_maximum_period)
   {
      dtpk_end->Date = dtpk_start->Date + export_maximum_period;
   }
}
//---------------------------------------------------------------------------
void __fastcall Tfrm_export_database::dtpk_endChange(TObject *Sender)
{
   // Ensure the start date is before the end date
   // and that the maximum period is not exceeded
   if (dtpk_start->Date > dtpk_end->Date)
   {
      dtpk_start->Date = dtpk_end->Date;
   }
   if (int(dtpk_end->Date - dtpk_start->Date) > export_maximum_period)
   {
      dtpk_start->Date = dtpk_end->Date - export_maximum_period;
   }
}
//---------------------------------------------------------------------------
void __fastcall Tfrm_export_database::bbtn_get_studiesClick(
      TObject *Sender)
{
   MEAS_ID_TYPE  meas_id;
   int           i;
   AnsiString    user_str;
   AnsiString    system_id;
   AnsiString    study_id;
   AnsiString    patient_num;
   TDateTime     meas_date;

   Screen->Cursor = crHourGlass;

   lstbx_studies->Items->Clear();
   lstbx_exports->Items->Clear();
   export_index->Clear();

   //find entries which are within start and end dates
   qry_date = dbmgr_setup_query(DBMGR_MEASURE_PWA_TABLE,
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
   lbl_total_studies->Caption = IntToStr((int)qry_date->RecordCount);
   lbl_progress_text->Caption = "";

   records = new int[qry_date->RecordCount];

   // Display each entry with the corresponding patient information
   for (i = 0; i < qry_date->RecordCount; i++)
   {
      lbl_progress_text->Caption = IntToStr((int)i + 1) + " of " +lbl_total_studies->Caption;
      Application->ProcessMessages();

      pwa_data->Populate(qry_date);
      user_str = pwa_data->DateTime.FormatString(EXPORT_DATETIMEFORMAT);
      system_id = pwa_data->System_ID;
      study_id =  pwa_data->Study_ID;
      patient_num = IntToStr((int)pwa_data->Patient_No);
      meas_date = pwa_data->DateTime;

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
         {      user_str = user_str + " - "   + qry_name->FieldByName(PATIENT_SURNAME)->AsString
                 + ", "    + qry_name->FieldByName(PATIENT_FIRST_NAME)->AsString;
         }
      }
      records[i] = i;
      lstbx_studies->Items->AddObject(user_str, (TObject *)&records[i]);
      lstbx_studies->Update();
      qry_date->Next();
   }
   lbl_progress_text->Caption = "";
   Screen->Cursor = crDefault;

   EnableButtons();
}
//---------------------------------------------------------------------------


void __fastcall Tfrm_export_database::spbtn_addClick(TObject *Sender)
{
   int  i;

   // Add a study to the export list
   while (lstbx_studies->SelCount > 0)
   {
      for (i = 0; i < lstbx_studies->Items->Count; i++)
      {
         if (lstbx_studies->Selected[i])
         {
            lstbx_exports->Items->AddObject(lstbx_studies->Items->Strings[i],
                                        lstbx_studies->Items->Objects[i]);
            lstbx_studies->Items->Delete(i);
         }
      }
   }
   EnableButtons();
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_export_database::spbtn_addallClick(TObject *Sender)
{
   int i;
   int total_in;

   // Add all the studies to the export list
   total_in = lstbx_studies->Items->Count;
   for (i = 0; i < total_in; i++)
   {
      lstbx_studies->Selected[i] = true;
   }

   for (i = 0; i < total_in; i++)
   {
      if (lstbx_studies->Selected[i])
      {
         lstbx_exports->Items->AddObject(lstbx_studies->Items->Strings[i],
                                     lstbx_studies->Items->Objects[i]);

      }
   }

   for (i = 0; i < total_in; i++)
   {
      lstbx_studies->Items->Delete(lstbx_studies->Items->Count - 1);
   }
   EnableButtons();
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_export_database::spbtn_deleteClick(TObject *Sender)
{
   int  i;

   // Remove a study from the export list
   while (lstbx_exports->SelCount > 0)
   {
      for (i = 0; i < lstbx_exports->Items->Count; i++)
      {
         if (lstbx_exports->Selected[i])
         {
            lstbx_studies->Items->AddObject(lstbx_exports->Items->Strings[i],
                                       lstbx_exports->Items->Objects[i]);
            lstbx_exports->Items->Delete(i);
         }
      }
   }
   EnableButtons();
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_export_database::spbtn_deleteallClick(TObject *Sender)
{
   int i;
   int total_out;

   // Remove all studies from the export list
   total_out = lstbx_exports->Items->Count;
   for (i = 0; i < total_out; i++)
   {
      lstbx_exports->Selected[i] = true;
   }

   for (i = 0; i < total_out; i++)
   {
      if (lstbx_exports->Selected[i])
      {
         lstbx_studies->Items->AddObject(lstbx_exports->Items->Strings[i],
                                    lstbx_exports->Items->Objects[i]);
      }
   }

   for (i = 0; i < total_out; i++)
   {
      lstbx_exports->Items->Delete(lstbx_exports->Items->Count - 1);
   }
   EnableButtons();
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_export_database::lstbx_studiesClick(TObject *Sender)
{
   EnableButtons();        
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_export_database::lstbx_exportsClick(TObject *Sender)
{
   EnableButtons();        
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_export_database::bbtn_export_selectedClick(
      TObject *Sender)
{
   int i = 0;
   int index;

   // Populate the export index and call export_database()
   while (i < lstbx_exports->Items->Count)
   {
      index = *((int *)lstbx_exports->Items->Objects[i]);
      export_index->Add(index);
      ++i;
   }
   this->export_database();
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_export_database::bbtn_export_allClick(TObject *Sender)
{
   int i;

   // Populate the export index and call export_database()
   export_index->Clear();
   for (i = 0; i < qry_date->RecordCount; i++)
   {
      export_index->Add(i);
   }
   this->export_database();
}
//---------------------------------------------------------------------------
void __fastcall Tfrm_export_database::export_database()
{
   String       source_path;
   String       database_path;
   String       dest_path;
   String       user_str;
   String       system_id;
   String       study_id;
   String       index;
   String       key_fields;
   int          move_by;
   ULONG        empty_database;
   int          nof_records;
   int          no_added = 0;
   int          patient_no;
   TLocateOptions Opts;
   TDateTime    DateTime;

   Opts.Clear();
   index = PATIENT_SYSTEM_ID +  ";" + PATIENT_STUDY_ID + ";" + PATIENT_NO;
   key_fields = MPW_SYSTEM_ID + ";" + MPW_STUDY_ID + ";" + MPW_PATIENT_NO + ";" + MPW_DATETIME;

   // Initialise database paths and check that enough disk space is available
   source_path = ExtractFilePath(ParamStr(0)) + CONFIG_SYSTEM_SUBDIR + "\\" + DBMGR_DATABASE_NAME;
   database_path = EXPORT_SUBDIR + "\\";
   dest_path = ExtractFilePath(ParamStr(0)) + database_path + DBMGR_DATABASE_NAME;
   empty_database = emma_get_file_size(source_path);
   nof_records = export_index->Count;
   if (nof_records > 0)
   {
      ULONG  need_size = nof_records * EXPORTED_DATABASE_RECORD_SIZE + empty_database;
      VLONG free_space = emma_get_disk_space(dest_path[1]);
      if (free_space < need_size)
      {
         MsgBox(TERROR, MSG_EXPORT_ERROR, MSG_EXPORT_NO_SPACE, LoadStr(MSG_EXPORT_NO_SPACE) + RoundIntToStr(need_size));
         Close();
         return;
      }
   }

   // Check if the export database is to be overwritten
   if (FileExists(dest_path))
   {
      int user = MsgBox(LoadStr(MSG_EXPORT_DATABASE), SCONFIRMATION, MB_YESNOCANCEL | MB_ICONQUESTION);
      switch(user)
      {
         case IDCANCEL:
            Close();
            return;

         case IDYES:
            DeleteFile(dest_path);
            CopyFile(source_path.c_str(), dest_path.c_str(), true);
            break;

         case IDNO:
            break;
      }
   }
   else
   {
      CopyFile(source_path.c_str(), dest_path.c_str(), true);
   }

   // Display and initialise the status bar
   pnl_buttons->Visible = false;
   pnl_status->Visible = true;
   pnl_select->Enabled = false;
   pnl_records->Visible = false;
   pnl_warnings->Visible = true;
   pnl_warnings->Align = alClient;
   memMsg->Height = 250;
   progress_bar->Position = 0;
   progress_bar->Max = export_index->Count - 1;
   status_bar->Panels->Items[0]->Text = "";
   user_str = AnsiString(0) + "/" + AnsiString(export_index->Count);
   status_bar->Panels->Items[1]->Text = user_str;

   // Copy the empty database from the system sub-directory
   try
   {
      if (FileExists(dest_path))
      {
         Screen->Cursor = crHourGlass;
         patient_table = dynamic_cast<TADOTable *>(dbmgr_get_dataset(DBMGR_PATIENT_TABLE, false));
         if (patient_table != NULL)
         {
            if (dbmgr_perform_simple_activation(database_path, true))
            {
               if (dbmgr_open(DBMGR_PATIENT_TABLE, true))
               {
                  copy_table = dbmgr_get_dataset(DBMGR_PATIENT_TABLE, true);
                  if (dbmgr_open(DBMGR_MEASURE_PWA_TABLE, true))
                  {
                     pwa_table = dbmgr_get_dataset(DBMGR_MEASURE_PWA_TABLE, true);
                     
                     // Scroll through the entries specified by the export index
                     for (int i = 0; i < export_index->Count; i++)
                     {
                        Application->ProcessMessages();
                        qry_date->First();
                        move_by = export_index->Strings[i].ToIntDef(0);
                        if (move_by < qry_date->RecordCount)
                        {
                           qry_date->MoveBy(move_by);
                           system_id = qry_date->FieldByName(MPW_SYSTEM_ID)->AsString;
                           study_id = qry_date->FieldByName(MPW_STUDY_ID)->AsString;
                           patient_no = qry_date->FieldByName(MPW_PATIENT_NO)->AsInteger;
                           DateTime = qry_date->FieldByName(MPW_DATETIME)->AsDateTime;
                           Variant locvalues[3];
                           locvalues[0] = Variant(system_id);
                           locvalues[1] = Variant(study_id);
                           locvalues[2] = Variant(patient_no);

                           if (patient_no)
                           {
                              // Copy the patient to the export database if it has not been done already
                              if (!copy_table->Locate(index, VarArrayOf(locvalues, 2), Opts))
                              {
                                 patient_table->Locate(index, VarArrayOf(locvalues, 2), Opts);
                                 copy_table->Append();
                                 for (int j = 0; j < patient_table->FieldCount; j++)
                                 {
                                    copy_table->Fields->Fields[j]->Value = patient_table->Fields->Fields[j]->Value;
                                 }
                                 copy_table->Post();
                              }
                              // Copy the study to the export database if it has not been done already
                              Variant locdetails[4];
                              locdetails[0] = Variant(system_id);
                              locdetails[1] = Variant(study_id);
                              locdetails[2] = Variant(patient_no);
                              locdetails[3] = Variant(DateTime);

                              if (pwa_table->Locate(key_fields, VarArrayOf(locdetails, 3), Opts))
                              {
                                 String MsgStr = "Error: Patient: " + IntToStr(patient_no) +
                                                " , Measurement: " + String(DateTime);
                                 memMsg->Lines->Add(MsgStr);
                                 memMsg->Lines->Add("Record already exists in the exported database");
                                 memMsg->Lines->Add("");
                                 memMsg->Lines->Add("------------------------------------");
                              }
                              else
                              {
                                 pwa_table->Append();
                                 for (int j = 0; j < qry_date->FieldCount; j++)
                                 {
                                    pwa_table->Fields->Fields[j]->Value = qry_date->Fields->Fields[j]->Value;
                                 }
                                 pwa_table->Post();
                                 no_added++;  
                              }
                           }
                        }
                        // Display the study being exported and update the status bar
                        user_str = qry_date->FieldByName(MPW_DATETIME)->AsString + " - "
                                        + patient_table->FieldByName(PATIENT_SURNAME)->AsString + ", "
                                        + patient_table->FieldByName(PATIENT_FIRST_NAME)->AsString;
                        status_bar->Panels->Items[0]->Text = user_str;
                        user_str = AnsiString(i + 1) + "/" + AnsiString(export_index->Count);
                        status_bar->Panels->Items[1]->Text = user_str;
                        progress_bar->Position = i;

                        // Allow the user to stop the export
                        if (stop_export)
                        {
                           break;
                        }
                     }
                  }
               }
               dbmgr_disconnect_database_set(true);
            }
         }
      }
   }
   catch (Exception &exception)
   {
       MsgBox_show(TERROR,
                 MSG_DBREADWRITE_ERROR,
                 LoadStr(MSG_POST_ERROR),
                 MSG_POST_ERROR,
                 LoadStr(MSG_POST_ERROR) +GetCurrentHRVMeasureDetails() +exception.Message);
   }

   memMsg->Lines->Add(IntToStr(no_added) + " of " + IntToStr(nof_records) + " records exported.");
   Screen->Cursor = crDefault;
   //Close();
}

void __fastcall Tfrm_export_database::bbtn_cancel_exportClick(
      TObject *Sender)
{
   // Allow the user to stop the export
   stop_export = true;
   Abort();
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_export_database::FormDestroy(TObject *Sender)
{
   // Cleanup the database and data members
   if (qry_date != NULL)
   {
      qry_date->Close();
   }
   if (qry_name != NULL)
   {
      qry_name->Close();
   }
   if (copy_table != NULL)
   {
      copy_table->Close();
   }
   if (pwa_table != NULL)
   {
      pwa_table->Close();
   }
   if (export_index != NULL)
   {
      export_index->Clear();
      delete export_index;
   }
   if (patients != NULL)
   {
      patients->Clear();
      delete patients;
   }
   if (records != NULL)
   {
      delete records;
   }
}
//---------------------------------------------------------------------------



void __fastcall Tfrm_export_database::BitBtn1Click(TObject *Sender)
{
   Close();   
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_export_database::bbtn_cancelClick(TObject *Sender)
{
   ModalResult = mrCancel;   
}
//---------------------------------------------------------------------------

