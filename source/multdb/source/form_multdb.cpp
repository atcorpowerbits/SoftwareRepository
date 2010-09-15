//---------------------------------------------------------------------------
#include <vcl.h>
#include <sysutils.hpp>
#include <FileCtrl.hpp>
#include <ComObj.hpp>
#include <stdio.h>

#include <inc/std.h>
#include <dbmgr/pubserv.h>
#include <msg/pubserv.h>
#include <log/pubserv.h>
#include <patient/pubserv.h>
#include <config/pubserv.h>
#include <cfr11/pubserv.h>
#include <scor/form_main.h>
#include <scor/form_selectdir.h>
#include <scor/utils.h>

#include "form_multdb.h"
#pragma hdrstop
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

VAR_EXPORT  Tfrm_multdb *frm_multdb;
VAR_EXPORT  AnsiString  multdb_selected_dir;

const int MULTDB_MAX = 21;
const int MULTDB_DEFAULT_ID = 0;
const int MULTDB_NAME_LEN = 17;
const int MULTDB_DESC_LEN = 41;
const int MULTDB_DATE_LEN = 12;
const int MULTDB_PATH_LEN = 121;
const int MULTDB_INVALID_ID = -1;

const String MULTDB_BIN = "\\MULTDB.BIN";
const String MULTDB_DEFAULT_NAME = "DATA";
const String MULTDB_CONFIG_FNAME = CONFIG_SYSTEM_SUBDIR + MULTDB_BIN;
const String MULTDB_DEFAULT_DB = "The Default Database";
const String MULTDB_LDB = "\\scor.ldb";
const String MULTDB_ACTIVE_DB = "Active Database - ";
const String MULTDB_DATEFORMAT = "dd mmm yyyy";
const String MULTDB_UNKNOWN = "Unknown";
const String MULTDB_FAILED = "MULTDB_FAILED";
const String MULTDB_NEW = "New";

typedef struct
{
   char  name[MULTDB_NAME_LEN];
   char  desc[MULTDB_DESC_LEN];
   char  created[MULTDB_DATE_LEN];
   char  last_copied[MULTDB_DATE_LEN];
   char  last_updated[MULTDB_DATE_LEN];
   char  copied_to[MULTDB_PATH_LEN];
   char  updated_from[MULTDB_PATH_LEN];
   bool  can_delete;
} MULTDB_CONFIG_TYPE;

MULTDB_CONFIG_TYPE multdb[MULTDB_MAX];
int                multdb_active_id;
UTINY              multdb_num_defined;
AnsiString         multdb_previous_active_name;
bool               multdb_initialised;

TTreeNode *root_node;

bool multdb_write_setup(void);
void multdb_load_setup(void);
void multdb_recover_configuration(void);
void multdb_rearrange_config(UTINY id_deleted);

bool multdb_verify_name(char *name);
bool multdb_create_data_set(char *dbname);
bool multdb_set_active_name(char *dbname);
void multdb_set_active_id(int new_id);

bool multdb_perform_update(void);
bool multdb_perform_copy(void);
bool multdb_perform_merge(void);
bool multdb_check_directory(AnsiString dir_name);

bool multdb_initialise(void)
{
   UTINY  i;

   multdb_initialised = false;

   multdb_active_id = MULTDB_DEFAULT_ID;
   multdb_previous_active_name = MULTDB_DEFAULT_NAME;
   multdb_num_defined = 0;
   multdb_selected_dir = "";

   for (i = 0; i < MULTDB_MAX; i++)
   {
      multdb[i].name[0] = '\0';
      multdb[i].desc[0] = '\0';
      multdb[i].created[0] = '\0';
      multdb[i].last_copied[0] = '\0';
      multdb[i].last_updated[0] = '\0';
      multdb[i].copied_to[0] = '\0';
      multdb[i].updated_from[0] = '\0';
      multdb[i].can_delete = false;
   }
   strcpy(multdb[MULTDB_DEFAULT_ID].name, MULTDB_DEFAULT_NAME.c_str());
   strcpy(multdb[MULTDB_DEFAULT_ID].desc, MULTDB_DEFAULT_DB.c_str());

   multdb_load_setup();
   multdb_initialised = true;
   return (multdb_initialised);
}

void multdb_destroy(void)
{
   if (multdb_initialised)
   {
      (void)multdb_write_setup();
      multdb_initialised = false;
   }
}

void multdb_show_form(void)
{
  frm_multdb = new Tfrm_multdb(Application->MainForm);
  frm_multdb->ShowModal();
  delete frm_multdb;
}

bool multdb_write_setup(void)
{
   int         file_handle;
   int         ret_val;
   bool        success = false;
   UTINY       i = 0;
   AnsiString  multdb_cfg_file;

   multdb_cfg_file = ExtractFilePath(ParamStr(0)) + MULTDB_CONFIG_FNAME;
   if (FileExists(multdb_cfg_file))
   {
      file_handle = FileOpen(multdb_cfg_file, fmOpenWrite);
   }
   else
   {
      file_handle = FileCreate(multdb_cfg_file);
   }

   if (file_handle != -1)
   {
      i = MULTDB_MAX;
      FileWrite(file_handle,
                &i,
                sizeof(unsigned char));

      i = multdb_num_defined;
      FileWrite(file_handle,
                &i,
                sizeof(unsigned char));

      success = true;
      i = 0;
      while (i < MULTDB_MAX && success)
      {
         success = false;
         ret_val = FileWrite(file_handle,
                             &multdb[i],
                             sizeof(MULTDB_CONFIG_TYPE));
         if (ret_val == sizeof(MULTDB_CONFIG_TYPE))
         {
            success = true;
         }
         ++i;
      }
      FileClose(file_handle);
   }
   return (success);
}

void multdb_load_setup(void)
{
   UTINY        total_records = 0;
   UTINY        num_defined = 0;
   UTINY        i;
   bool         valid = false;
   int          record_read;
   int          file_handle;
   AnsiString   multdb_cfg_file;

   multdb_cfg_file = ExtractFilePath(ParamStr(0)) + MULTDB_CONFIG_FNAME;
   if (FileExists(multdb_cfg_file))
   {
      if ((file_handle = FileOpen(multdb_cfg_file, fmOpenRead)) != -1)
      {
         record_read = FileRead(file_handle,
                                &total_records,
                                sizeof(unsigned char));

         if ((record_read == 1) && (total_records <= MULTDB_MAX))
         {
            record_read = FileRead(file_handle,
                                  &num_defined,
                                   sizeof(unsigned char));
            if ((record_read == 1) && (num_defined < MULTDB_MAX))
            {
               i = 0;
               valid = true;
               while (i < total_records && valid)
               {
                  valid = false;
                  record_read = FileRead(file_handle,
                                         &multdb[i],
                                         sizeof(MULTDB_CONFIG_TYPE));

                  if (record_read == sizeof(MULTDB_CONFIG_TYPE))
                  {
                     valid = true;
                     if (i == 0)
                     {
                        if ((strcmpi(multdb[i].name, MULTDB_DEFAULT_NAME.c_str()) != 0))
                        {
                           valid = false;
                           log_write(MSG_MULTDB_INCORRECT_DATASET);
                        }
                     }
                  }
                  ++i;
               }
            }
            else
            {
               log_write(MSG_MULTDB_TOO_MANY);
            }
         }
         else
         {
            log_write(MSG_MULTDB_INCORRECT_HEADER);
         }
         FileClose(file_handle);
      }
      else
      {
         log_write(MSG_MULTDB_FILEOPENERROR);
      }
      if (valid)
      {
         multdb_num_defined = num_defined;
      }
   }
   else
   {
      multdb_recover_configuration();
      log_write(MSG_MULTDB_RECOVERED);
      if (multdb_write_setup())
      {
         valid = true;
      }
   }

   if (!valid)
   {
      multdb_recover_configuration();
      log_write(MSG_MULTDB_RECOVERED);
      multdb_write_setup();
   }
}

void multdb_set_active_id(int new_id)
{
   if (new_id != multdb_active_id)
   {
      multdb_active_id = new_id;
   }
}

UTINY multdb_get_active_id(void)
{
   return ((UTINY)multdb_active_id);
}

bool multdb_is_default(void)
{
   if (multdb_active_id == MULTDB_DEFAULT_ID)
   {
      return true;
   }
   else
   {
      return false;
   }
}

void multdb_set_delete_status(bool status)
{
   multdb[multdb_active_id].can_delete = status;
   multdb[MULTDB_DEFAULT_ID].can_delete = FALSE;
}

AnsiString multdb_get_active_name(void)
{
   AnsiString sactive;

   if (multdb_active_id == MULTDB_INVALID_ID)
   {
      sactive = MULTDB_DEFAULT_NAME;
   }
   else
   {
      sactive = (AnsiString)multdb[multdb_active_id].name;
   }
   return sactive;
}

bool multdb_set_active_name(char *dbname)
{
   bool   found = false;
   UTINY  i;

   i = 0;
   while (i < MULTDB_MAX && (i < multdb_num_defined + 1) && !found)
   {
      if (strcmpi(dbname, multdb[i].name) == 0)
      {
         found = true;
         multdb_set_active_id(i);
      }
      ++i;
   }
   return (found);
}

bool multdb_pack(void)
{
   Variant V;
   AnsiString  db_path;
   AnsiString  data_dir;
   AnsiString  source_db;
   AnsiString  rename_db;
   AnsiString  dest_db;
   AnsiString  log_msg;
   bool        success = false;

   if (MsgBox_confirmation("Packing optimises and repairs the current active database.\nThis operation can take several minutes depending on the size of the database and the level of optimisation required.\n\nBefore you proceed with packing you should have a recent backup or copy of your database.\n\nDo you want to continue ?",
                           SWARNING) != IDYES)
   {
      return success;
   }

   try
   {
      Screen->Cursor = crHourGlass;
      data_dir = MULTDB_DEFAULT_NAME + "\\";
      if (!multdb_is_default())
      {
         data_dir = data_dir + multdb_get_active_name() +"\\";
      }
      db_path = ExtractFilePath(ParamStr(0)) +data_dir;
      source_db = db_path +DBMGR_DATABASE_NAME;
      rename_db = db_path + DBMGR_PRE_PACK_DATABASE_NAME;
      dest_db = db_path + DBMGR_PACK_DATABASE_NAME;

      if (emma_is_space_available(source_db[1], source_db))
      {
         if (dbmgr_disconnect_database_set(false))
         {
            log_msg = "Packing Database " +source_db;
            log_write(log_msg);
            emma_display_statusbar_message("Please Wait... Packing Database", "", "", sphygmocor_white);
            V = CreateOleObject("DAO.DBEngine.36");
            if (FileExists(source_db))
            {
               if (FileExists(dest_db))
               {
                  DeleteFile(dest_db);
               }

               // Repair and then compact the database
               V.Exec(Procedure("CompactDatabase") << source_db << dest_db);
               if (FileExists(dest_db))
               {
                  if (FileExists(rename_db))
                  {
                     DeleteFile(rename_db);
                  }
                  // PM V9
                  // Added intermediate Rename database step
                  // If databases cannot be renamed, then the source database
                  // will not be deleted
                  if (RenameFile(source_db, rename_db))
                  {
                     // Copy the database with overwrite privileges
                     if (CopyFile(dest_db.c_str(), source_db.c_str(), false))
                     {
                        emma_display_statusbar_message("Packing Database Successful", "", "", sphygmocor_white);
                        success = true;
                     }
                     // If copy fails, recover the source database
                     else
                     {
                        RenameFile(rename_db, source_db);
                        emma_display_statusbar_message("Packing Database Failed", "Could Not Copy Packed Database", "Could Not Copy Packed Database", sphygmocor_maroon);
                        log_msg = "Packing Failed, Could Not Copy Packed Database.";
                        log_write(log_msg);
                     }
                  }
                  else
                  {
                     emma_display_statusbar_message("Packing Database Failed", "Could Not Rename Source Database", "Could Not Rename Source Database", sphygmocor_maroon);
                     log_msg = "Packing Failed, Could Not Rename Source Database.";
                     log_write(log_msg);
                  }
                  DeleteFile(dest_db);
               }
            }
            dbmgr_activate_database_set(data_dir, false);
         }
      }
      else
      {
         log_msg = LoadStr(MSG_MULTDB_NO_SPACE) +" Packing Failed. " +source_db;
         MsgBox(TERROR, MSG_DBMGR_ERROR, MSG_MULTDB_NO_SPACE, log_msg);
      }
   }
   catch (Exception &exception)
   {
       emma_display_statusbar_message("Packing Database Failed", "", "", sphygmocor_maroon);
       log_msg = "Packing Failed " +exception.Message;
       log_write(log_msg);
   }
   Screen->Cursor = crDefault;
   if (success)
   {
      if (multdb_is_default())
      {
         config_update_database_pack_date();
      }
   }
   return (success);
}

bool multdb_create_data_set(char *dbname,
                            char *description,
                            char *date_created)
{
   AnsiString  dir_name;
   AnsiString  source_path;
   AnsiString  dest_path;
   AnsiString  msgbox_string;
   bool        status = false;

   if (multdb_num_defined < MULTDB_MAX - 1)
   {
      if (multdb_verify_name(dbname))
      {
         dir_name = ExtractFilePath(ParamStr(0)) + MULTDB_DEFAULT_NAME + "\\" +(AnsiString)dbname;
         if (!DirectoryExists(dir_name))
         {
            source_path = ExtractFilePath(ParamStr(0)) + CONFIG_SYSTEM_SUBDIR + "\\" + DBMGR_DATABASE_NAME;
            if (!FileExists(source_path))
            {
               status = false;
               msgbox_string = LoadStr(MSG_MULTDB_CANT_CREATE) +(AnsiString)dbname +".\n\n" +LoadStr(MSG_MULTDB_MISSING_DB);
               MsgBox(TERROR, MSG_MULTDB_ERROR, MSG_MULTDB_MISSING_DB, msgbox_string);
               return (status);
            }

            if (emma_is_space_available(source_path[1], source_path))
            {
               if (CreateDir(dir_name))
               {
                  if (FileExists(source_path))
                  {
                     dest_path = ExtractFilePath(ParamStr(0)) + MULTDB_DEFAULT_NAME + "\\" + (AnsiString)dbname + "\\" + DBMGR_DATABASE_NAME;
                     if (CopyFile(source_path.c_str(),
                                  dest_path.c_str(),
                                  true) != 0)
                     {
                        multdb_set_active_id(multdb_num_defined + 1);
                        strcpy(multdb[multdb_active_id].name, dbname);
                        strcpy(multdb[multdb_active_id].desc, description);
                        strcpy(multdb[multdb_active_id].created, date_created);
                        strcpy(multdb[multdb_active_id].copied_to, MULTDB_NEW.c_str());
                        strcpy(multdb[multdb_active_id].updated_from, MULTDB_NEW.c_str());
                        multdb[multdb_active_id].can_delete = true;
                        ++multdb_num_defined;
                        status = true;
                        multdb_write_setup();
                     }
                  }
               }
               else
               {
                 msgbox_string = LoadStr(MSG_MULTDB_CANT_CREATE) + (AnsiString)dbname +
                    ".\n\nFailed to create directory. " +dir_name;
                 MsgBox_show(TERROR,
                             MSG_MULTDB_ERROR,
                             msgbox_string,
                             MSG_MULTDB_CANT_CREATE, "");
               }
            }
            else
            {
               msgbox_string = LoadStr(MSG_MULTDB_CANT_CREATE) + (AnsiString)dbname +".\n\n" +LoadStr(MSG_MULTDB_NO_SPACE);
               MsgBox(TERROR, MSG_MULTDB_ERROR, MSG_MULTDB_NO_SPACE, msgbox_string);
            }
         }
         else
         {
            msgbox_string = LoadStr(MSG_MULTDB_CANT_CREATE) + (AnsiString)dbname +
                    ".\n\nDirectory Already Exists. " +dir_name;
            MsgBox(TERROR, MSG_MULTDB_ERROR, MSG_MULTDB_CANT_CREATE, msgbox_string);
         }
      }
      else
      {
         msgbox_string = LoadStr(MSG_MULTDB_CANT_CREATE) + (AnsiString)dbname +".\n\n" +LoadStr(MSG_MULTDB_ALREADY_EXIST);
         MsgBox_show(TWARNING,
                     MSG_MULTDB_ERROR,
                     msgbox_string,
                     MSG_MULTDB_ALREADY_EXIST, "");
      }
   }
   else
   {
      msgbox_string = LoadStr(MSG_MULTDB_CANT_CREATE) + (AnsiString)dbname +".\n\n" +LoadStr(MSG_MULTDB_MAX_EXCEEDED);
      MsgBox_show(TWARNING,
                  MSG_MULTDB_ERROR,
                  msgbox_string,
                  MSG_MULTDB_MAX_EXCEEDED, "");
   }
   return (status);
}

bool multdb_verify_name(char *name)
{
   UTINY i = 0;
   bool  valid = true;

   while (i < MULTDB_NAME_LEN && name[i] != '\0' && valid)
   {
      if (!isalnum(name[i]))
      {
         valid = false;
      }
      ++i;
   }

   i = 0;
   while (i < MULTDB_MAX && valid)
   {
      if (strcmpi(name, multdb[i].name) == 0)
      {
         valid = false;
      }
      ++i;
   }
   return (valid);
}

bool multdb_exists(char *name)
{
   UTINY i = 0;
   bool  exists = false;

   while (i < MULTDB_MAX && !exists)
   {
      if (strcmpi(name, multdb[i].name) == 0)
      {
         exists = true;
      }
      ++i;
   }
   return (exists);
}

void multdb_rearrange_config(UTINY id_deleted)
{
   UTINY i;

   if (id_deleted == multdb_num_defined)
   {
      for (i = 0; i < MULTDB_NAME_LEN; i++)
      {
         multdb[id_deleted].name[i] = '\0';
      }
      for (i = 0; i < MULTDB_DESC_LEN; i++)
      {
         multdb[id_deleted].desc[i] = '\0';
      }
      multdb[id_deleted].created[0] = '\0';
      multdb[id_deleted].last_copied[0] = '\0';
      multdb[id_deleted].copied_to[0] = '\0';
      multdb[id_deleted].last_updated[0] = '\0';
      multdb[id_deleted].updated_from[0] = '\0';
      multdb[id_deleted].can_delete = false;
   }
   else
   {
      for (i = id_deleted; i < multdb_num_defined; i++)
      {
         strcpy(multdb[i].name, multdb[i + 1].name);
         strcpy(multdb[i].desc, multdb[i + 1].desc);
         strcpy(multdb[i].created, multdb[i + 1].created);
         strcpy(multdb[i].last_copied, multdb[i + 1].last_copied);
         strcpy(multdb[i].copied_to, multdb[i + 1].copied_to);
         strcpy(multdb[i].last_updated, multdb[i + 1].last_updated);
         strcpy(multdb[i].updated_from, multdb[i + 1].updated_from);
         multdb[i].can_delete = multdb[i + 1].can_delete;
      }
      for (i = 0; i < MULTDB_NAME_LEN; i++)
      {
         multdb[multdb_num_defined].name[i] = '\0';
      }
      for (i = 0; i < MULTDB_DESC_LEN; i++)
      {
         multdb[multdb_num_defined].desc[i] = '\0';
      }
      multdb[multdb_num_defined].created[0] = '\0';
      multdb[multdb_num_defined].last_copied[0] = '\0';
      multdb[multdb_num_defined].copied_to[0] = '\0';
      multdb[multdb_num_defined].last_updated[0] = '\0';
      multdb[multdb_num_defined].updated_from[0] = '\0';
      multdb[multdb_num_defined].can_delete = false;
   }
   --multdb_num_defined;
   multdb_set_active_id(MULTDB_DEFAULT_ID);
   multdb_write_setup();
   frm_multdb->multdb_update_grid();
   frm_multdb->tv_multdb->Selected = frm_multdb->tv_multdb->Items[0].Item[multdb_active_id + 1];
   frm_multdb->lbl_active_db->Caption = multdb[multdb_active_id].name;
}

bool multdb_delete(void)
{
   AnsiString   dir_path;
   AnsiString   file_path;
   AnsiString   msgbox_string;
   bool         status = false;
   bool         delete_error = false;

   if (multdb_num_defined)
   {
      if (multdb_active_id != MULTDB_DEFAULT_ID)
      {
         if (!multdb[multdb_active_id].can_delete)
         {
            msgbox_string = LoadStr(MSG_MULTDB_CANT_DELETE) + (AnsiString)multdb[multdb_active_id].name +".\n\n" +LoadStr(MSG_MULTDB_OPERATION_PERFORMED);
            MsgBox_show(TWARNING,
                        MSG_MULTDB_ERROR,
                        msgbox_string,
                        MSG_MULTDB_OPERATION_PERFORMED, "");
            return false;
         }

         if (strcmpi(multdb_previous_active_name.c_str(),
                     multdb[multdb_active_id].name) == 0)
         {
            msgbox_string = LoadStr(MSG_MULTDB_CANT_DELETE) + (AnsiString)multdb[multdb_active_id].name +".\n\n" +LoadStr(MSG_MULTDB_WAS_ACTIVE);
            MsgBox_show(TWARNING,
                        MSG_MULTDB_ERROR,
                        msgbox_string,
                        MSG_MULTDB_WAS_ACTIVE, "");
            return false;
         }

         msgbox_string = LoadStr(MSG_MULTDB_WILL_DELETE) + (AnsiString)multdb[multdb_active_id].name;
         if (MsgBox(msgbox_string  + ".\r\n" + LoadStr(MSG_MULTDB_SURE), SCONFIRMATION,
                    MB_ICONQUESTION | MB_YESNO) != ID_YES)
         {
            return false;
         }

         if (MsgBox(msgbox_string + ".\r\n" + LoadStr(MSG_MULTDB_ABSOLUTELY_SURE), SCONFIRMATION,
                    MB_ICONQUESTION | MB_YESNO) != ID_YES)
         {
            return false;
         }
         frm_multdb->pnl_buttons->Enabled = false;
         frm_multdb->anmt_multdb->CommonAVI = aviDeleteFile;
         frm_multdb->anmt_multdb->Visible = true;
         frm_multdb->anmt_multdb->Active = true;

         file_path = ExtractFilePath(ParamStr(0)) + MULTDB_DEFAULT_NAME + "\\" +
            (AnsiString)multdb[multdb_active_id].name + "\\" + DBMGR_DATABASE_NAME;

         if (FileExists(file_path))
         {
            if (DeleteFile(file_path))
            {
               // PM V9
               // Delete the record locking file
               file_path = ExtractFilePath(ParamStr(0)) + MULTDB_DEFAULT_NAME + "\\" +
                  (AnsiString)multdb[multdb_active_id].name + MULTDB_LDB;
               if (FileExists(file_path))
               {
                  DeleteFile(file_path);
               }
               // Delete the previous database
               file_path = ExtractFilePath(ParamStr(0)) + MULTDB_DEFAULT_NAME + "\\" +
                  (AnsiString)multdb[multdb_active_id].name + "\\" + DBMGR_PRE_DATABASE_NAME;
               if (FileExists(file_path))
               {
                  DeleteFile(file_path);
               }
               dir_path = ExtractFilePath(ParamStr(0)) + MULTDB_DEFAULT_NAME + "\\" + (AnsiString)multdb[multdb_active_id].name;
               if (RemoveDir(dir_path))
               {
                  status = true;
               }
               else
               {
                  delete_error = true;
                  msgbox_string =  LoadStr(MSG_MULTDB_CANT_DELETE_DIR) + dir_path;
                  log_write(msgbox_string);
               }
            }
            else
            {
               delete_error = true;
               msgbox_string = LoadStr(MSG_MULTDB_COULDNOT_DELETE) + file_path;
               log_write(msgbox_string);
            }
         }
         else
         {
            delete_error = true;
            msgbox_string = LoadStr(MSG_MULTDB_COULDNOT_DELETE) + file_path + LoadStr(MSG_MULTDB_NOT_EXIST);
            log_write(msgbox_string);
         }

         if (delete_error)
         {
            multdb_rearrange_config((UTINY)multdb_active_id);
            status = false;
         }
         frm_multdb->anmt_multdb->Active = false;
         frm_multdb->anmt_multdb->Visible = false;
         frm_multdb->pnl_buttons->Enabled = true;
      }
      else
      {
         MsgBox_show(TWARNING,
                     MSG_MULTDB_ERROR,
                     LoadStr(MSG_MULTDB_NO_DELETE_DEFAULT),
                     MSG_MULTDB_NO_DELETE_DEFAULT, "");
      }
      if (status)
      {
         msgbox_string = LoadStr(MSG_MULTDB_REMOVED) + dir_path;
         MsgBox(TNOTIFICATION, MSG_MULTDB_ERROR, MSG_MULTDB_REMOVED, msgbox_string);
         frm_multdb->tv_multdb->Items->Delete(frm_multdb->tv_multdb->Items[0].Item[multdb_active_id + 1]);
      }
      else
      {
         msgbox_string = LoadStr(MSG_MULTDB_FAIL_TO_DELETE) +dir_path;
         MsgBox_show(TWARNING,
                     MSG_MULTDB_ERROR,
                     msgbox_string,
                     MSG_MULTDB_FAIL_TO_DELETE, "");
      }
   }
   return (status);
}
//---------------------------------------------------------------------------
__fastcall Tfrm_multdb::Tfrm_multdb(TComponent* Owner)
  : TForm(Owner)
{
}

//---------------------------------------------------------------------------
void __fastcall Tfrm_multdb::FormShow(TObject *Sender)
{
   AnsiString   multdb_path;
   AnsiString   dataset_path;
   AnsiString   old_dataset_path;

   // Add the defined databases to the tree view
   root_node = tv_multdb->Items[0].Item[0];
   for (int j = 0; j <= multdb_num_defined; j++)
   {
      if (multdb[j].name[0] != '\0')
      {
         tv_multdb->Items->AddChild(root_node, multdb[j].name);

         // Check each database for the new database name. If it's not there,
         // rename the old database so that update, copy, delete and select can locate it
         multdb_path = MULTDB_DEFAULT_NAME + "\\";
         if ((j != MULTDB_DEFAULT_ID) &&
          (j != MULTDB_INVALID_ID))
         {
            multdb_path = multdb_path + multdb[j].name + "\\";
         }
         dataset_path = ExtractFilePath(ParamStr(0)) +multdb_path +DBMGR_DATABASE_NAME;
         old_dataset_path = ExtractFilePath(ParamStr(0)) +multdb_path +DBMGR_OLD_DATABASE_NAME;

         if (!FileExists(dataset_path))
         {
            if (FileExists(old_dataset_path))
            {
               if (RenameFile(old_dataset_path, dataset_path) == false)
               {
                  MsgBox(MSG_MULTDB_RENAME_FAILED,
                        SWARNING,
                        MB_ICONEXCLAMATION | MB_OK);
                        Close();
               }
            }
         }
      }
   }

   // Select the currently acitve database
   tv_multdb->Selected = tv_multdb->Items[0].Item[multdb_active_id + 1];
   multdb_update_grid();
   edt_name->Text = "";
   edt_desc->Text = "";
   pnl_animate->Visible = false;
   bbtn_new->Enabled = false;
   bbtn_multdb_abort->Enabled = true;

   if (multdb_active_id != MULTDB_INVALID_ID)
   {
      multdb_previous_active_name = (AnsiString)multdb[multdb_active_id].name;
      lbl_active_db->Caption = multdb[multdb_active_id].name;
   }
   if (multdb_num_defined == 0)
   {
      edt_name->SetFocus();
   }
   else
   {
      tv_multdb->SetFocus();
   }
   lbl_defined->Caption = IntToStr(multdb_num_defined);
}

void __fastcall Tfrm_multdb::multdb_update_grid(void)
{
   //Initialise the labels
   Label1->Caption = "Description:";
   Label2->Caption = "Date Created:";
   Label3->Caption = "Last Copied:";
   Label4->Caption = "Copied To:";
   Label5->Caption = "Last Updated:";
   Label6->Caption = "Updated From:";

   // Display the selected database's details
   if (tv_multdb->Selected){
   Label7->Caption = multdb[tv_multdb->Selected->Index].desc;
   Label8->Caption = multdb[tv_multdb->Selected->Index].created;
   Label9->Caption = multdb[tv_multdb->Selected->Index].last_copied;
   Label10->Caption = multdb[tv_multdb->Selected->Index].copied_to;
   Label11->Caption = multdb[tv_multdb->Selected->Index].last_updated;
   Label12->Caption = multdb[tv_multdb->Selected->Index].updated_from;
   }
   else
   {
   Label7->Caption = "";
   Label8->Caption = "";
   Label9->Caption = "";
   Label10->Caption = "";
   Label11->Caption = "";
   Label12->Caption = "";
   }

   if (multdb_num_defined >= MULTDB_MAX)
   {
      bbtn_new->Enabled = false;
   }
   else
   {
      if (edt_desc->GetTextLen() && edt_name->GetTextLen())
      {
         bbtn_new->Enabled = true;
      }
   }

   if (multdb_is_default())
   {
      bbtn_delete->Enabled = false;
      bbtn_update->Enabled = false;
      spbtn_update_desc->Enabled = false;
   }
   else
   {
      bbtn_delete->Enabled = true;
      bbtn_update->Enabled = true;
      spbtn_update_desc->Enabled = true;
   }
   edt_name->Text = "";
   edt_desc->Text = "";
}

//---------------------------------------------------------------------------
void __fastcall Tfrm_multdb::edt_nameEnter(TObject *Sender)
{
   edt_name->SelStart = 0;
}
//---------------------------------------------------------------------------
void __fastcall Tfrm_multdb::FormClose(TObject *Sender,
      TCloseAction &Action)
{
   AnsiString S;

   multdb_write_setup();
   S = MULTDB_ACTIVE_DB + multdb_get_active_name();
   frm_main->lbl_active_database->Caption = S;
   pnl_animate->Visible = false;
}
//---------------------------------------------------------------------------
void __fastcall Tfrm_multdb::bbtn_multdb_okClick(TObject *Sender)
{
   TDataSet     *table_pat;
   AnsiString   multdb_path;
   AnsiString   dataset_path;
   AnsiString   log_msg;
   static bool  select_failed = false;

   if ((strcmpi(multdb_previous_active_name.c_str(),
               multdb[multdb_active_id].name) != 0) || select_failed)
   {
      multdb_path = MULTDB_DEFAULT_NAME + "\\";
      if ((multdb_active_id != MULTDB_DEFAULT_ID) &&
          (multdb_active_id != MULTDB_INVALID_ID))
      {
         multdb_path = multdb_path + multdb[multdb_active_id].name + "\\";
      }
      dataset_path = ExtractFilePath(ParamStr(0)) +multdb_path +DBMGR_DATABASE_NAME;

      if (FileExists(dataset_path))
      {
         Screen->Cursor = crHourGlass;
         dbmgr_close(DBMGR_PATIENT_TABLE, false);
         dbmgr_close(DBMGR_MEASURE_PWA_TABLE, false);
         if (dbmgr_activate_database_set(multdb_path, false))
         {
            // Check if the selected database needs to be converted
            // Display conversion status on the animation panel
            pnl_buttons->Enabled = false;
            anmt_multdb->CommonAVI = aviCopyFiles;
            pnl_animate->Visible = true;
            lbl_wait->Visible = true;
            anmt_multdb->Visible = true;
            anmt_multdb->Active = true;
            if (dbmgr_conversion(frm_multdb->lbl_wait, multdb_path))
            {
               lbl_wait->Caption = "";
               anmt_multdb->Active = false;
               anmt_multdb->Visible = false;
               lbl_wait->Visible = false;
               pnl_animate->Visible = false;
               pnl_buttons->Enabled = true;

               select_failed = false;
               dbmgr_open(DBMGR_PATIENT_TABLE, false);
               Screen->Cursor = crDefault;
               table_pat = dbmgr_get_dataset(DBMGR_PATIENT_TABLE, false);
               if (table_pat != NULL && dbmgr_is_open(DBMGR_PATIENT_TABLE, false))
               {
                  log_msg = "Database Manager - Selected " +multdb_get_active_name() +" Patients = " +IntToStr(table_pat->RecordCount);
                  log_write(log_msg);
                  patient_update_count();
                  if (table_pat->RecordCount == 0)
                  {
                     Close();
                     Hide();
                  }
               }
               ModalResult = mrOk;
            }
            else
            {
               lbl_wait->Caption = "";
               anmt_multdb->Active = false;
               anmt_multdb->Visible = false;
               lbl_wait->Visible = false;
               pnl_animate->Visible = false;
               pnl_buttons->Enabled = true;
               Screen->Cursor = crDefault;
               bbtn_multdb_abort->Enabled = false;
               select_failed = true;
               MsgBox(MSG_MULTDB_CONVERSION_FAILED,
                    SWARNING,
                    MB_ICONEXCLAMATION | MB_OK);
                    return;
            }
         }
         else
         {
            Screen->Cursor = crDefault;
            bbtn_multdb_abort->Enabled = false;
            select_failed = true;
            log_msg = LoadStr(MSG_MULTDB_SELECT_FAILED) +multdb_path;
            MsgBox(TERROR, MSG_MULTDB_ERROR, MSG_MULTDB_SELECT_FAILED, log_msg);
            return;
         }
      }
      else
      {
         select_failed = true;
         bbtn_multdb_abort->Enabled = false;
         //log_msg = LoadStr(MSG_MULTDB_SELECT_FAILED) +dataset_path +LoadStr(MSG_MULTDB_NOT_EXIST);
         //MsgBox(TERROR, MSG_MULTDB_ERROR, MSG_MULTDB_SELECT_FAILED, log_msg);
         log_write("MSG_MULTDB_SELECT_FAILED");
         return;
      }
   }
   else
   {
      ModalResult = mrOk;
   }
}

//---------------------------------------------------------------------------
void __fastcall Tfrm_multdb::bbtn_multdb_abortClick(TObject *Sender)
{
   if (multdb_exists(multdb_previous_active_name.c_str()))
   {
      multdb_set_active_name(multdb_previous_active_name.c_str());
   }
   ModalResult = mrAbort;
}
//---------------------------------------------------------------------------
void __fastcall Tfrm_multdb::bbtn_newClick(TObject *Sender)
{
   TDateTime   dt;
   AnsiString  date_str;
   AnsiString  multdb_name;

   if (edt_name->GetTextLen() > 0 && edt_name->GetTextLen() < MULTDB_NAME_LEN)
   {
      if (edt_desc->GetTextLen() > 0 && edt_desc->GetTextLen() < MULTDB_DESC_LEN)
      {
         multdb_name = edt_name->Text.UpperCase();
         date_str = dt.CurrentDate().FormatString(MULTDB_DATEFORMAT);
         if (multdb_create_data_set(multdb_name.c_str(),
                                    edt_desc->Text.c_str(),
                                    date_str.c_str()))
         {
            tv_multdb->Items->AddChild(root_node, multdb[multdb_active_id].name);
            tv_multdb->Selected = tv_multdb->Items[0].Item[multdb_active_id + 1];
            multdb_update_grid();
            lbl_active_db->Caption = multdb[multdb_active_id].name;
            lbl_defined->Caption = IntToStr(multdb_num_defined);
            tv_multdb->SetFocus();
         }
         else
         {
            if (multdb_num_defined == (MULTDB_MAX - 1))
            {
               bbtn_new->Enabled = false;
               edt_desc->Text = "";
               edt_name->Text = "";
            }
         }
      }
      else
      {
         MsgBox(MSG_MULTDB_DESCRIPTION, MSG_MULTDB_CANT_CREATE);
         edt_desc->SetFocus();
      }
   }
   else
   {
      MsgBox(MSG_MULTDB_ALREADY_EXIST, MSG_MULTDB_CANT_CREATE);
      edt_name->SetFocus();
   }
}
//---------------------------------------------------------------------------
void __fastcall Tfrm_multdb::bbtn_activateClick(TObject *Sender)
{
   multdb_set_active_name(tv_multdb->Selected->Text.c_str());
   lbl_active_db->Caption = multdb[multdb_active_id].name;
   multdb_update_grid();
   tv_multdb->SetFocus();
}
//---------------------------------------------------------------------------
void __fastcall Tfrm_multdb::bbtn_copyClick(TObject *Sender)
{
   if (emma_select_dir(this, "Copy To ", multdb_selected_dir))
   {
      //this->SetFocus();
      if (multdb_perform_copy())
      {
         multdb_set_delete_status(true);
      }
      multdb_update_grid();
   }
}

void __fastcall Tfrm_multdb::bbtn_deleteClick(TObject *Sender)
{
   if (multdb_delete())
   {
      multdb_rearrange_config((UTINY)multdb_active_id);
      lbl_defined->Caption = IntToStr(multdb_num_defined);
   }
}

void __fastcall Tfrm_multdb::bbtn_updateClick(TObject *Sender)
{
   AnsiString msgbox_string;

   if (multdb_num_defined)
   {
   	  if (multdb_active_id != MULTDB_DEFAULT_ID)
   	  {
   		 if (!multdb[multdb_active_id].can_delete)
   		 {
            msgbox_string = LoadStr(MSG_MULTDB_CANT_UPDATE) + (AnsiString)multdb[multdb_active_id].name +".\n\n" +LoadStr(MSG_MULTDB_OPERATION_PERFORMED);
            MsgBox_show(TWARNING,
                        MSG_MULTDB_ERROR,
                        msgbox_string,
                        MSG_MULTDB_CANT_UPDATE, "");
            return;
		   }
         if (strcmpi(multdb_previous_active_name.c_str(),
                     multdb[multdb_active_id].name) == 0)
         {
            msgbox_string = LoadStr(MSG_MULTDB_CANT_UPDATE) + (AnsiString)multdb[multdb_active_id].name +".\n\n" +LoadStr(MSG_MULTDB_UPDATE_WAS_ACTIVE);
            MsgBox_show(TWARNING,
                        MSG_MULTDB_ERROR,
                        msgbox_string,
                        MSG_MULTDB_UPDATE_WAS_ACTIVE, "");
            return;
         }
         
         if (emma_select_dir(this, "Update From ", multdb_selected_dir))
       	 {
            //this->SetFocus();
            if (multdb_perform_update())
            {
               multdb_set_delete_status(true);
            }
            multdb_update_grid();
         }
	  }
   }
}void __fastcall Tfrm_multdb::spbtn_update_descClick(TObject *Sender)
{
   if (!multdb_is_default())
   {
      if (edt_desc->GetTextLen() > 0)
      {
         strcpy(multdb[tv_multdb->Selected->Index].desc, edt_desc->Text.c_str());
         multdb_update_grid();
         edt_desc->Text = "";
      }
   }
}

bool multdb_perform_update(void)
{
   AnsiString  dest_path;
   AnsiString  source_path;
   AnsiString  old_path;
   AnsiString  source_path_dir;
   AnsiString  date_str;
   AnsiString  msgbox_string;
   TDateTime   dt;
   bool        updated = false;

   dest_path = ExtractFilePath(ParamStr(0));
   dest_path = dest_path + MULTDB_DEFAULT_NAME + "\\" + multdb_get_active_name() + "\\" +DBMGR_DATABASE_NAME;
   source_path = multdb_selected_dir + "\\" + DBMGR_DATABASE_NAME;
   old_path = multdb_selected_dir + "\\" + DBMGR_OLD_DATABASE_NAME;

   if (AnsiCompareFileName(source_path, dest_path) == 0)
   {
      MsgBox_show(TWARNING,
                  MSG_MULTDB_ERROR,
                  LoadStr(MSG_MULTDB_CANT_COPY_TO_ITSELF),
                  MSG_MULTDB_CANT_COPY_TO_ITSELF, "");
      return (updated);
   }

   // Check for the new database name, if it's not there, rename the old database
   if (!FileExists(source_path))
   {
      if (FileExists(old_path))
      {
         if (RenameFile(old_path, source_path) == false)
         {
            MsgBox(MSG_MULTDB_RENAME_FAILED,
                        SWARNING,
                        MB_ICONEXCLAMATION | MB_OK);
                        return (updated);
         }
      }
   }

   if (multdb_check_directory(multdb_selected_dir))
   {
      if (emma_is_space_available(dest_path[1], source_path))
      {
         frm_multdb->pnl_buttons->Enabled = false;
         frm_multdb->anmt_multdb->CommonAVI = aviCopyFiles;
         frm_multdb->pnl_animate->Visible = true;
         frm_multdb->lbl_wait->Visible = true;
         frm_multdb->lbl_wait->Caption = "Please Wait...Copying Database";
         frm_multdb->anmt_multdb->Visible = true;
         frm_multdb->anmt_multdb->Active = true;

         if (CopyFile(source_path.c_str(),
                      dest_path.c_str(),
                      false) == 0)
         {
             multdb[multdb_active_id].last_updated[0] = '\0';
             strcpy(multdb[multdb_active_id].updated_from,
                   MULTDB_FAILED.c_str());
             msgbox_string = LoadStr(MSG_MULTDB_UPDATE_FAILED) + source_path + " ," + dest_path;
             log_write(msgbox_string);
         }
         else
         {
            updated = true;
            date_str = dt.CurrentDate().FormatString(MULTDB_DATEFORMAT);
            strcpy(multdb[multdb_active_id].last_updated,
                   date_str.c_str());

            source_path_dir = ExtractFileDir(source_path);
            strncpy(multdb[multdb_active_id].updated_from,
                    source_path_dir.c_str(),
                    MULTDB_PATH_LEN);
            multdb[multdb_active_id].updated_from[MULTDB_PATH_LEN - 1] = '\0';
         }
         frm_multdb->lbl_wait->Caption = "";
         frm_multdb->anmt_multdb->Active = false;
         frm_multdb->anmt_multdb->Visible = false;
         frm_multdb->lbl_wait->Visible = false;
         frm_multdb->pnl_animate->Visible = false;
         frm_multdb->pnl_buttons->Enabled = true;
      }
      else
      {
         msgbox_string = LoadStr(MSG_MULTDB_UPDATE_FAILED) +source_path + ".\nTo " + dest_path +".\n\n" +LoadStr(MSG_MULTDB_UPDATE_NO_SPACE);
         MsgBox(TERROR, MSG_MULTDB_ERROR, MSG_MULTDB_UPDATE_NO_SPACE, msgbox_string);
      }
   }
   else
   {
      msgbox_string = LoadStr(MSG_MULTDB_UPDATE_WRONG) + multdb_get_active_name();
      MsgBox(TERROR, MSG_MULTDB_ERROR, MSG_MULTDB_UPDATE_WRONG, msgbox_string);
   }

   if (updated)
   {
      msgbox_string = LoadStr(MSG_MULTDB_UPDATE_SUCCESS) + source_path_dir + " to " + dest_path;
      MsgBox(TNOTIFICATION, MSG_MULTDB_ERROR, MSG_MULTDB_UPDATE_SUCCESS, msgbox_string);
      log_write(msgbox_string);
   }

   return (updated);
}

bool multdb_perform_copy(void)
{
   bool        can_copy;
   AnsiString  dest_path;
   AnsiString  source_path;
   AnsiString  exe_path;
   AnsiString  EXE_path;
   AnsiString  short_path;
   AnsiString  SHORT_path;
   AnsiString  date_str;
   AnsiString  msgbox_string;
   TDateTime   dt;
   
   can_copy = true;
   exe_path = ExtractFilePath(ParamStr(0));

   // This is a fix for Windows XP because it translates paths to upper case
   EXE_path = exe_path.UpperCase();

   // This is a fix for Operating Systems that convert paths to their short path names
   short_path = ExtractShortPathName(exe_path);
   SHORT_path = ExtractShortPathName(EXE_path);

   if (multdb_check_directory(multdb_selected_dir))
   {
      dest_path = multdb_selected_dir;
      if (dest_path.AnsiPos(exe_path) != 0 || dest_path.AnsiPos(EXE_path) != 0)
      {
         can_copy = false;
      }
      if (dest_path.AnsiPos(short_path) != 0 || dest_path.AnsiPos(SHORT_path) != 0)
      {
         can_copy = false;
      }
   }
   else
   {
      // only a drive name selected
      if (multdb_selected_dir.Length() == 3)
      {
         dest_path = multdb_selected_dir +multdb_get_active_name();
      }
      else
      {
         dest_path = multdb_selected_dir + "\\" + multdb_get_active_name();
      }

      if (dest_path.AnsiPos(exe_path) != 0 || dest_path.AnsiPos(EXE_path) != 0)
      {
         can_copy = false;
         msgbox_string = LoadStr(MSG_MULTDB_CANT_COPY) + dest_path;
         log_write(msgbox_string);
      }
      if (dest_path.AnsiPos(short_path) != 0 || dest_path.AnsiPos(SHORT_path) != 0)
      {
         can_copy = false;
         msgbox_string = LoadStr(MSG_MULTDB_CANT_COPY) + dest_path;
         log_write(msgbox_string);
      }

      if (can_copy)
      {
         if (!DirectoryExists(dest_path))
         {
            if (!CreateDir(dest_path))
            {
               can_copy = false;
               msgbox_string = LoadStr(MSG_MULTDB_CANT_CREATE_DEST) + dest_path;
               log_write(msgbox_string);
            }
         }
      }
   }

   if (can_copy)
   {
      dest_path = dest_path + "\\" + DBMGR_DATABASE_NAME;
      if (FileExists(dest_path))
      {
         int user = MsgBox(LoadStr(MSG_MULTDB_DATABASE_EXISTS), SCONFIRMATION, MB_YESNO | MB_ICONQUESTION);
         switch(user)
         {
            case IDNO:
               can_copy = false;
               break;
         }
      }
      if (can_copy)
      {
         source_path = ExtractFilePath(ParamStr(0));
         if (multdb_is_default())
         {
            source_path = source_path + MULTDB_DEFAULT_NAME + "\\" + DBMGR_DATABASE_NAME;
         }
         else
         {
            source_path = source_path + MULTDB_DEFAULT_NAME + "\\" + multdb_get_active_name() + "\\" +DBMGR_DATABASE_NAME;
         }

         if (emma_is_space_available(dest_path[1], source_path))
         {
            frm_multdb->pnl_buttons->Enabled = false;
            frm_multdb->anmt_multdb->CommonAVI = aviCopyFiles;
            frm_multdb->pnl_animate->Visible = true;
            frm_multdb->lbl_wait->Visible = true;
            frm_multdb->lbl_wait->Caption = "Please Wait...Copying Database";
            frm_multdb->anmt_multdb->Visible = true;
            frm_multdb->anmt_multdb->Active = true;
            Application->ProcessMessages();

            if (CopyFile(source_path.c_str(),
                      dest_path.c_str(),
                      false) == 0)
            {
               can_copy = false;
               multdb[multdb_active_id].last_copied[0] = '\0';
               strcpy(multdb[multdb_active_id].copied_to, MULTDB_FAILED.c_str());
               msgbox_string = LoadStr(MSG_MULTDB_COPY_FAILED) +source_path + "\nTo " +dest_path;
               MsgBox(TERROR, MSG_MULTDB_ERROR, MSG_MULTDB_COPY_FAILED, msgbox_string);
            }
            else
            {
               date_str = dt.CurrentDate().FormatString(MULTDB_DATEFORMAT);
               strcpy(multdb[multdb_active_id].last_copied,
                   date_str.c_str());

               exe_path = ExtractFileDir(dest_path);
               strncpy(multdb[multdb_active_id].copied_to,
                    exe_path.c_str(),
                    MULTDB_PATH_LEN);
               multdb[multdb_active_id].copied_to[MULTDB_PATH_LEN - 1] = '\0';
            }

            frm_multdb->lbl_wait->Caption = "";
            frm_multdb->anmt_multdb->Active = false;
            frm_multdb->anmt_multdb->Visible = false;
            frm_multdb->lbl_wait->Visible = false;
            frm_multdb->pnl_animate->Visible = false;
            frm_multdb->pnl_buttons->Enabled = true;
         }
         else
         {
            msgbox_string = LoadStr(MSG_MULTDB_COPY_FAILED) + source_path + "\nTo " +dest_path +".\n\n" +LoadStr(MSG_MULTDB_COPY_NO_SPACE);
            MsgBox(TERROR, MSG_MULTDB_ERROR, MSG_MULTDB_COPY_NO_SPACE, msgbox_string);
            can_copy = false;
         }
      }
   }
   else
   {
      msgbox_string = LoadStr(MSG_MULTDB_COPY_FAILED) +multdb_get_active_name() +"\nTo " + dest_path +".\n\n" +LoadStr(MSG_MULTDB_CHECK_COPY);
      MsgBox(TERROR, MSG_MULTDB_ERROR, MSG_MULTDB_CHECK_COPY, msgbox_string);
      can_copy = false;
   }

   if (can_copy)
   {
      msgbox_string = LoadStr(MSG_MULTDB_COPY_SUCCESS) +source_path +"\nto " + dest_path;
      MsgBox(TNOTIFICATION, MSG_MULTDB_ERROR, MSG_MULTDB_COPY_SUCCESS, msgbox_string);
      log_write(msgbox_string);
   }
   return (can_copy);
}

bool multdb_check_directory(AnsiString dir_name)
{
   AnsiString  multdb_dir;
   int         i;
   int         length;
   bool        found = false;

   length = dir_name.Length();
   i = length;

   while (!found && i > 0)
   {
      if (dir_name.IsPathDelimiter(i))
      {
         found = true;
      }
      else
      {
         --i;
      }
   }

   if (found)
   {
      multdb_dir = dir_name.SubString(i + 1, length - i);
      found = false;
      if (multdb_dir.AnsiCompareIC(multdb_get_active_name()) == 0)
      {
         found = true;
      }
   }
   return (found);
}

void multdb_recover_configuration(void)
{
   AnsiString     path_name;
   AnsiString     filepath_name;
   AnsiString     date_str;
   TDateTime      dt;
   TSearchRec     sr;

   multdb_num_defined = 0;

   strcpy(multdb[MULTDB_DEFAULT_ID].name, MULTDB_DEFAULT_NAME.c_str());
   strcpy(multdb[MULTDB_DEFAULT_ID].desc, MULTDB_DEFAULT_DB.c_str());
   strcpy(multdb[MULTDB_DEFAULT_ID].created, MULTDB_UNKNOWN.c_str());
   multdb[MULTDB_DEFAULT_ID].can_delete = false;

   multdb[MULTDB_DEFAULT_ID].last_copied[0] = '\0';
   strcpy(multdb[MULTDB_DEFAULT_ID].copied_to, MULTDB_UNKNOWN.c_str());
   multdb[MULTDB_DEFAULT_ID].last_updated[0] = '\0';
   multdb[MULTDB_DEFAULT_ID].updated_from[0] = '\0';

   path_name =  ExtractFilePath(ParamStr(0)) + MULTDB_DEFAULT_NAME +"\\*.";

   if (FindFirst(path_name, faDirectory, sr) == 0)
   {
      if (sr.Name[1] != '.')
      {
         if (sr.Name.Length() <= MULTDB_NAME_LEN)
         {
            filepath_name = ExtractFilePath(ParamStr(0)) + MULTDB_DEFAULT_NAME +
                            sr.Name + "\\" +DBMGR_DATABASE_NAME;
            if (FileExists(filepath_name))
            {
               strcpy(multdb[multdb_num_defined + 1].name, sr.Name.c_str());

               dt = FileDateToDateTime(sr.Time);
               date_str = dt.FormatString(MULTDB_DATEFORMAT);
               strcpy(multdb[multdb_num_defined + 1].created, date_str.c_str());

               multdb[multdb_num_defined + 1].can_delete = false;
               multdb[multdb_num_defined + 1].last_copied[0] = '\0';
               strcpy(multdb[multdb_num_defined + 1].copied_to, MULTDB_UNKNOWN.c_str());
               multdb[multdb_num_defined + 1].last_updated[0] = '\0';
               strcpy(multdb[multdb_num_defined + 1].updated_from, MULTDB_UNKNOWN.c_str());
               ++multdb_num_defined;;
            }
         }
      }
      while (FindNext(sr) == 0)
      {
         if (sr.Name[1] != '.')
         {
            if (sr.Name.Length() <= MULTDB_NAME_LEN)
            {
               filepath_name = ExtractFilePath(ParamStr(0)) + MULTDB_DEFAULT_NAME +
                               "\\" + sr.Name + "\\" +DBMGR_DATABASE_NAME;
               if (FileExists(filepath_name))
               {
                  strcpy(multdb[multdb_num_defined + 1].name, sr.Name.c_str());

                  dt = FileDateToDateTime(sr.Time);
                  date_str = dt.FormatString(MULTDB_DATEFORMAT);
                  strcpy(multdb[multdb_num_defined + 1].created, date_str.c_str());

                  multdb[multdb_num_defined + 1].can_delete = false;
                  multdb[multdb_num_defined + 1].last_copied[0] = '\0';
                  strcpy(multdb[multdb_num_defined + 1].copied_to, MULTDB_UNKNOWN.c_str());
                  multdb[multdb_num_defined + 1].last_updated[0] = '\0';
                  strcpy(multdb[multdb_num_defined + 1].updated_from, MULTDB_UNKNOWN.c_str());
                  ++multdb_num_defined;;
               }
            }
         }
      }
      FindClose(sr);
   }
}



void __fastcall Tfrm_multdb::edt_nameChange(TObject *Sender)
{
   bbtn_new->Enabled = false;
   if (edt_name->GetTextLen())
   {
      if (edt_desc->GetTextLen())
      {
         bbtn_new->Enabled = true;
      }
   }
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_multdb::edt_descChange(TObject *Sender)
{
   bbtn_new->Enabled = false;
   if (edt_desc->GetTextLen())
   {
      if (edt_name->GetTextLen())
      {
         bbtn_new->Enabled = true;
      }
   }
}
//---------------------------------------------------------------------------



void __fastcall Tfrm_multdb::tv_multdbClick(TObject *Sender)
{
   multdb_update_grid();
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_multdb::tv_multdbDblClick(TObject *Sender)
{
   bbtn_activateClick(Sender);
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_multdb::edt_descClick(TObject *Sender)
{
   // Display the active database's description
   edt_desc->Text = multdb[tv_multdb->Selected->Index].desc;
}
//---------------------------------------------------------------------------


