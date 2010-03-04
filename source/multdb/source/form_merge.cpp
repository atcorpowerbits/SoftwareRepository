//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
#include <vcl\FileCtrl.hpp>
#include <stdio.h>

#include <msg\pubserv.h>
#include <log\pubserv.h>
#include <dbmgr\pubserv.h>
#include <meas\pubserv.h>
#include <patient\pubserv.h>
#include <scor\utils.h>
#include <scor\form_selectdir.h>
#include <scor\form_main.h>
#include "form_merge.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
//Tfrm_merge *frm_merge;

bool merge_connect_database(TADOConnection *db, AnsiString the_path)
{
   AnsiString             expression;
   bool                   connected = true;
   AnsiString             alias_path;
   AnsiString             connection_string;

   alias_path = the_path;
   db->Connected = false;

   connection_string = "Provider=Microsoft.Jet.OLEDB.4.0;Data Source=" +alias_path +DBMGR_DATABASE_NAME+";" +";Persist Security Info=False";
   try
   {
      db->ConnectionString = connection_string;
      db->Connected = true;
   }
   catch (EDBEngineError &exception)
   {
       MsgBox_show(TERROR,
                   MSG_DBMGR_ERROR,
                   LoadStr(MSG_DBMGR_NO_DB),
                   MSG_DBMGR_NO_DB,
                   LoadStr(MSG_DBMGR_NO_DB) +exception.Message);
       connected = false;
   }
   return (connected);
}

bool merge_add_table(TADOConnection      *db,
                     TADOTable         *table,
                     DBMGR_ID_TYPE  id)
{
   bool         table_added = false;
   AnsiString   db_name;

   switch (id)
   {
      case DBMGR_PATIENT_TABLE:
         db_name = patient_get_table_name();
         break;

      case DBMGR_MEASURE_PWA_TABLE:
         db_name = meas_pwa_get_table_name();
         break;

      case DBMGR_MEASURE_PWV_TABLE:
         db_name = meas_pwv_get_table_name();
         break;

      default:
         db_name = NULL;
         break;
   }

   try
   {
      if (table != NULL && db_name != NULL)
      {
         table->Active = false;
         table->Connection = db;
         table->TableName = db_name;
         if (table)
         {
            table_added = true;
         }
      }
   }
   catch (EDBEngineError &exception)
   {
       MsgBox_show(TERROR,
                   MSG_DBMGR_ERROR,
                   LoadStr(MSG_DBMGR_ERROR_DB),
                   MSG_DBMGR_ERROR_DB,
                   LoadStr(MSG_DBMGR_ERROR_DB) +exception.Message);
       table_added = false;
   }
   return (table_added);
}

bool multb_merge_database_tables(TADOTable *tbl_patient,
                                 TADOTable *tbl_meas_pwa,
                                 TADOTable *tbl_meas_pwv)
{
   bool status;

   Tfrm_merge *frm_merge_tables = new Tfrm_merge(Application->MainForm,
                                                 tbl_patient,
                                                 tbl_meas_pwa,
                                                 tbl_meas_pwv);
   frm_merge_tables->ShowModal();
   status = (frm_merge_tables->ModalResult == mrYes);
   delete frm_merge_tables;
   return status;
}

//---------------------------------------------------------------------------
__fastcall Tfrm_merge::Tfrm_merge(TComponent  *Owner,
                                  TADOTable      *tbl_pat,
                                  TADOTable      *tbl_pwa,
                                  TADOTable      *tbl_pwv) : TForm(Owner)
{
   edt_source_dir->Text = ExtractFilePath(ParamStr(0));
   tbl_dest_pat = tbl_pat;
   tbl_dest_pwa = tbl_pwa;
   tbl_dest_pwv = tbl_pwv;
   success = false;
}


//---------------------------------------------------------
bool Tfrm_merge::merge_patient(TADOTable  *tbl_source,
                               TADOTable  *tbl_dest)
{
   int  source_records;
   int  dest_records;

   Screen->Cursor = crHourGlass;

   tbl_source->Open();
   tbl_dest->Open();

   dest_records = 0;
   source_records = tbl_source->RecordCount;

   //batch_move->Source = tbl_source;
   //batch_move->Destination = tbl_dest;
   try
   {
      batch_move->Execute();
   }
   catch (...)
   {
      btn_close->Enabled = true;
   }

   tbl_source->Close();
   tbl_dest->Close();

   Screen->Cursor = crDefault;

   dest_records = batch_move->MovedCount - batch_move->KeyViolCount;

   lbl_pat_status->Caption = "Patient Table: Merged " +IntToStr(dest_records) + " of " +
      IntToStr(source_records) + " records";

   return true;
}

//---------------------------------------------------------
bool Tfrm_merge::merge_pwa(TADOTable  *tbl_source,
                           TADOTable  *tbl_dest)
{
   int  source_records;
   int  dest_records;

   Screen->Cursor = crHourGlass;

   tbl_source->Open();
   tbl_dest->Open();

   dest_records = 0;
   source_records = tbl_source->RecordCount;

   //batch_move->Source = tbl_source;
   //batch_move->Destination = tbl_dest;
   try
   {
      batch_move->Execute();
   }
   catch (...)
   {
      btn_close->Enabled = true;
   }

   tbl_source->Close();
   tbl_dest->Close();

   Screen->Cursor = crDefault;

   dest_records = batch_move->MovedCount - batch_move->KeyViolCount;

   lbl_pwa_status->Caption = "PWA Measurement Table. Merged " +IntToStr(dest_records) + " of " +
      IntToStr(source_records) + " records";

   return true;
}

//---------------------------------------------------------
bool Tfrm_merge::merge_pwv(TADOTable  *tbl_source,
                           TADOTable  *tbl_dest)
{
   int  source_records;
   int  dest_records;

   Screen->Cursor = crHourGlass;

   tbl_source->Open();
   tbl_dest->Open();

   dest_records = 0;
   source_records = tbl_source->RecordCount;

   //batch_move->Source = tbl_source;
   //batch_move->Destination = tbl_dest;
   try
   {
      batch_move->Execute();
   }
   catch (...)
   {
      btn_close->Enabled = true;
   }

   tbl_source->Close();
   tbl_dest->Close();

   Screen->Cursor = crDefault;

   dest_records = batch_move->MovedCount - batch_move->KeyViolCount;

   lbl_pwv_status->Caption = "PWV Measurement Table. Merged " +IntToStr(dest_records) + " of " +
      IntToStr(source_records) + " records";

   return true;
}

//---------------------------------------------------------------------------
void __fastcall Tfrm_merge::btn_selectClick(TObject *Sender)
{
   String dir;

   if (emma_select_dir(this, "Merge Source Database", dir) == true)
   {
      edt_source_dir->Text = dir;
      lbl_merge_status->Caption = "Merge from " +edt_source_dir->Text;
   }
   else
   {
      lbl_merge_status->Caption = "Awaiting Merge source database selection.";
   }
}
//---------------------------------------------------------------------------
void __fastcall Tfrm_merge::btn_mergeClick(TObject *Sender)
{
   String  db_file;
   ULONG   db_file_size;
   VLONG   free_space;

   if (MsgBox_confirmation("Merging combines your selected database with the current active database.\nThis operation can take several minutes depending on the size of the two databases.\n\nBefore you proceed with merging you should have a recent backup or copy of your databases.\n\nDo you want to continue ?",
                           SNOTIFICATION) != IDYES)
   {
      return;
   }

   success = false;

   lbl_pat_status->Caption = "Patient Table: Initiating Merge....";
   lbl_pwa_status->Caption = "PWA Measurement Table: Initiating Merge....";
   lbl_pwv_status->Caption = "PWV Measurement Table: Initiating Merge....";

   btn_close->Enabled = false;
   btn_merge->Enabled = false;

   // Validate file and directory
   db_file = edt_source_dir->Text +"\\" +DBMGR_DATABASE_NAME;
   if (FileExists(db_file) == false)
   {
      btn_close->Enabled = true;
      lbl_merge_status->Caption = "Merge Failed ... Source database does not exist.";
      return;
   }

   db_file_size = emma_get_file_size(db_file) * 1.10;
   if (db_file_size >  0)
   {
      free_space = emma_get_disk_space((UTINY)(Application->ExeName[1]));
      if (free_space < db_file_size)
      {
         btn_close->Enabled = true;
         lbl_merge_status->Caption = "Merge Failed ... Not enough space on disk.";
         return;
      }
   }

   edt_source_dir->Text = edt_source_dir->Text +"\\";
   if (merge_connect_database(db_merge, edt_source_dir->Text) == false)
   {
      btn_close->Enabled = true;
      lbl_merge_status->Caption = "Merge Failed ... Error connecting to source database.";
      return;
   }

   // Prepare tables

   if (merge_add_table(db_merge, tbl_source_pat, DBMGR_PATIENT_TABLE) == false)
   {
      btn_close->Enabled = true;
      lbl_merge_status->Caption = "Merge Failed ... Error opening Patient table.";
      return;
   }

   if (merge_add_table(db_merge, tbl_source_pwa, DBMGR_MEASURE_PWA_TABLE) == false)
   {
      btn_close->Enabled = true;
      lbl_merge_status->Caption = "Merge Failed ... Error Opening PWA table.";
      return;
   }

   if (merge_add_table(db_merge, tbl_source_pwv, DBMGR_MEASURE_PWV_TABLE) == false)
   {
      btn_close->Enabled = true;
      lbl_merge_status->Caption = "Merge Failed ... Error Opening PWV table.";
      return;
   }

   log_write("Merge started at " + Now().FormatString("dd mmm yyyy, hh:nn"));
   lbl_merge_status->Caption = "Merge Running ...";
   if (tbl_dest_pat != NULL)
   {
      lbl_pat_status->Font->Color = clMaroon;
      lbl_pat_status->Caption = "Patient Table: Merge Started....Please Wait....";
      Application->ProcessMessages();
      if (merge_patient(tbl_source_pat, tbl_dest_pat) == false)
      {
         lbl_pat_status->Caption = "Patient Table: Merge Failed.";
         lbl_merge_status->Caption = "Merge Failed ... Please close.";
         btn_close->Enabled = true;
         return;
      }
   }

   // Merge Meas DB
   if (tbl_dest_pwa != NULL)
   {
      lbl_pwa_status->Font->Color = clMaroon;
      lbl_pwa_status->Caption = "PWA Measurement Table: Merge Started....Please Wait....";
      Application->ProcessMessages();
      if (merge_pwa(tbl_source_pwa, tbl_dest_pwa) == false)
      {
         lbl_pwa_status->Caption = "PWA Measurement Table: Merge Failed.";
         btn_close->Enabled = true;
         lbl_merge_status->Caption = "Merge Failed ... Please close.";
         return;
      }
   }

   if (tbl_dest_pwv != NULL)
   {
      lbl_pwv_status->Font->Color = clMaroon;
      lbl_pwv_status->Caption = "PWV Measurement Table: Merge Started....Please Wait....";
      Application->ProcessMessages();
      if (merge_pwv(tbl_source_pwv, tbl_dest_pwv) == false)
      {
         lbl_pwv_status->Caption = "PWV Measurement Table: Merge Failed.";
         btn_close->Enabled = true;
         lbl_merge_status->Caption = "Merge Failed ... Please close.";
         return;
      }
   }

   success = true;

  // Write to log
  log_write(lbl_pat_status->Caption + " from " + edt_source_dir->Text);
  log_write(lbl_pwa_status->Caption + " from " + edt_source_dir->Text);
  log_write(lbl_pwv_status->Caption + " from " + edt_source_dir->Text);
  log_write("Merge ended at " + Now().FormatString("dd mmm yyyy, hh:nn"));

  lbl_merge_status->Caption = "Merge Successful !";
  btn_close->Enabled = true;
}

//---------------------------------------------------------------------------
void __fastcall Tfrm_merge::btn_closeClick(TObject *Sender)
{
   if (success)
   {
      ModalResult = mrYes;
   }
   else
   {
      ModalResult = mrNo;
   }
}

void __fastcall Tfrm_merge::FormClose(TObject *Sender,
      TCloseAction &Action)
{
   Action = caFree;
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_merge::FormShow(TObject *Sender)
{
   lbl_pat_status->Font->Color = clGray;
   lbl_pwa_status->Font->Color = clGray;
   lbl_pwv_status->Font->Color = clGray;

   lbl_pat_status->Caption = "Patient Table: Status ....";
   lbl_pwa_status->Caption = "PWA Measurement Table: Status ...";
   lbl_pwv_status->Caption = "PWV Measurement Table: Status ...";

   lbl_merge_status->Caption = "Awaiting Merge source database selection.";

}
//---------------------------------------------------------------------------

