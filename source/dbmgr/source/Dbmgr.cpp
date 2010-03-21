//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include <stdio.h>
#include <config/pubserv.h>
#include <patient/pubserv.h>
#include <meas/pubserv.h>
#include <log/pubserv.h>
#include <msg/pubserv.h>
#include <cfr11/pubserv.h>
#include <scor/utils.h>
#include "form_splash.h"
#include <dbmgr/pubserv.h>
#include "dbmgr.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

const String DATETIME_DISPLAY_FORMAT = "dd mmm yyyy, hh:nn:ss";
const String DATE_DISPLAY_FORMAT = "dd mmm yyyy";
bool  dbmgr_initialised;
bool  dbmgr_hrv_conversion_required;
bool  dbmgr_audit_conversion_required;
bool  dbmgr_conversion_required;
AnsiString  dbmgr_default_path;
Tdbmgr_dmod *dbmgr_dmod;

bool dbmgr_table_exists(AnsiString table_name, bool is_copy);

//------------------------------------------------------------------------------

bool dbmgr_initialise(void)
{
   dbmgr_initialised = false;

   dbmgr_default_path = CONFIG_DATA_SUBDIR +"\\";

   Application->CreateForm(__classid(Tdbmgr_dmod), &dbmgr_dmod);

   if (dbmgr_dmod != NULL)
   {
      if (dbmgr_activate_database_set(dbmgr_default_path, false))
      {
         // Convert the database if required
         dbmgr_conversion(frm_splash->lbl_loading, dbmgr_default_path);
         if (!dbmgr_conversion_required)
         {
            dbmgr_initialised = true;
         }
      }
   }
   return (dbmgr_initialised);
}

void dbmgr_destroy(void)
{
   if (dbmgr_dmod)
   {
      if (dbmgr_initialised)
      {
         if (dbmgr_dmod->tbl_patient->Active)
         {
            dbmgr_dmod->tbl_patient->Close();
         }
         if (dbmgr_dmod->tbl_measure_pwa->Active)
         {
            dbmgr_dmod->tbl_measure_pwa->Close();
         }
         if (dbmgr_dmod->tbl_measure_pwv->Active)
         {
            dbmgr_dmod->tbl_measure_pwv->Close();
         }
         if (dbmgr_dmod->tbl_measure_pwm->Active)
         {
            dbmgr_dmod->tbl_measure_pwm->Close();
         }
         if (dbmgr_dmod->tbl_measure_pwm_trend->Active)
         {
            dbmgr_dmod->tbl_measure_pwm_trend->Close();
         }
         if (dbmgr_dmod->tbl_measure_pwm_session->Active)
         {
            dbmgr_dmod->tbl_measure_pwm_session->Close();
         }
         if (dbmgr_dmod->tbl_device_pwm->Active)
         {
            dbmgr_dmod->tbl_device_pwm->Close();
         }
         if (dbmgr_dmod->tbl_patient_copy->Active)
         {
            dbmgr_dmod->tbl_patient_copy->Close();
         }
         if (dbmgr_dmod->tbl_measure_pwa_copy->Active)
         {
            dbmgr_dmod->tbl_measure_pwa_copy->Close();
         }
         if (dbmgr_dmod->tbl_measure_hrv->Active)
         {
            dbmgr_dmod->tbl_measure_hrv->Close();
         }
         if (dbmgr_dmod->tbl_measure_hrv_copy->Active)
         {
            dbmgr_dmod->tbl_measure_hrv_copy->Close();
         }
         if (dbmgr_dmod->tbl_measure_pwv_copy->Active)
         {
            dbmgr_dmod->tbl_measure_pwv_copy->Close();
         }
         if (dbmgr_dmod->tbl_measure_pwm_copy->Active)
         {
            dbmgr_dmod->tbl_measure_pwm_copy->Close();
         }
         if (dbmgr_dmod->tbl_measure_pwm_session_copy->Active)
         {
            dbmgr_dmod->tbl_measure_pwm_session_copy->Close();
         }
         if (dbmgr_dmod->tbl_measure_pwm_trend_copy->Active)
         {
            dbmgr_dmod->tbl_measure_pwm_trend_copy->Close();
         }
         if (dbmgr_dmod->tbl_device_pwm_copy->Active)
         {
            dbmgr_dmod->tbl_device_pwm_copy->Close();
         }
         if (dbmgr_dmod->ADO_Connection_copy->Connected)
         {
            dbmgr_dmod->ADO_Connection_copy->Connected = false;
         }
         if (dbmgr_dmod->tbl_patient_audit->Active)
         {
            dbmgr_dmod->tbl_patient_audit->Close();
         }
         if (dbmgr_dmod->tbl_measure_pwa_audit->Active)
         {
            dbmgr_dmod->tbl_measure_pwa_audit->Close();
         }
         if (dbmgr_dmod->tbl_measure_pwv_audit->Active)
         {
            dbmgr_dmod->tbl_measure_pwv_audit->Close();
         }
         if (dbmgr_dmod->tbl_patient_audit_copy->Active)
         {
            dbmgr_dmod->tbl_patient_audit_copy->Close();
         }
         if (dbmgr_dmod->tbl_measure_pwa_audit_copy->Active)
         {
            dbmgr_dmod->tbl_measure_pwa_audit_copy->Close();
         }
         if (dbmgr_dmod->tbl_measure_pwv_audit_copy->Active)
         {
            dbmgr_dmod->tbl_measure_pwv_audit_copy->Close();
         }

         dbmgr_dmod->ADO_Connection->Connected = false;
         dbmgr_initialised = false;
      }
   }
}

bool dbmgr_disconnect_database_set(bool is_copy)
{
   bool disconnected = false;

   if (dbmgr_dmod)
   {
      if (is_copy)
      {
         if (dbmgr_dmod->tbl_patient_copy->Active)
         {
            dbmgr_dmod->tbl_patient_copy->Close();
         }
         if (dbmgr_dmod->tbl_measure_pwa_copy->Active)
         {
            dbmgr_dmod->tbl_measure_pwa_copy->Close();
         }
         if (dbmgr_dmod->tbl_measure_pwv_copy->Active)
         {
            dbmgr_dmod->tbl_measure_pwv_copy->Close();
         }
         if (dbmgr_dmod->tbl_measure_pwm_copy->Active)
         {
            dbmgr_dmod->tbl_measure_pwm_copy->Close();
         }
         if (dbmgr_dmod->tbl_measure_pwm_session_copy->Active)
         {
            dbmgr_dmod->tbl_measure_pwm_session_copy->Close();
         }
         if (dbmgr_dmod->tbl_measure_pwm_trend_copy->Active)
         {
            dbmgr_dmod->tbl_measure_pwm_trend_copy->Close();
         }
         if (dbmgr_dmod->tbl_device_pwm_copy->Active)
         {
            dbmgr_dmod->tbl_device_pwm_copy->Close();
         }
         if (dbmgr_dmod->tbl_measure_hrv_copy->Active)
         {
            dbmgr_dmod->tbl_measure_hrv_copy->Close();
         }
         if (dbmgr_dmod->tbl_patient_audit_copy->Active)
         {
            dbmgr_dmod->tbl_patient_audit_copy->Close();
         }
         if (dbmgr_dmod->tbl_measure_pwa_audit_copy->Active)
         {
            dbmgr_dmod->tbl_measure_pwa_audit_copy->Close();
         }
         if (dbmgr_dmod->tbl_measure_pwv_audit_copy->Active)
         {
            dbmgr_dmod->tbl_measure_pwv_audit_copy->Close();
         }
         dbmgr_dmod->ADO_Connection_copy->Connected = false;
         disconnected = !dbmgr_dmod->ADO_Connection_copy->Connected;;
      }
      else
      {
         if (dbmgr_dmod->tbl_patient->Active)
         {
            dbmgr_dmod->tbl_patient->Close();
         }
         if (dbmgr_dmod->tbl_measure_pwa->Active)
         {
            dbmgr_dmod->tbl_measure_pwa->Close();
         }
         if (dbmgr_dmod->tbl_measure_pwv->Active)
         {
            dbmgr_dmod->tbl_measure_pwv->Close();
         }
         if (dbmgr_dmod->tbl_measure_pwm->Active)
         {
            dbmgr_dmod->tbl_measure_pwm->Close();
         }
         if (dbmgr_dmod->tbl_measure_pwm_trend->Active)
         {
            dbmgr_dmod->tbl_measure_pwm_trend->Close();
         }
         if (dbmgr_dmod->tbl_measure_pwm_session->Active)
         {
            dbmgr_dmod->tbl_measure_pwm_session->Close();
         }
         if (dbmgr_dmod->tbl_device_pwm->Active)
         {
            dbmgr_dmod->tbl_device_pwm->Close();
         }
         if (dbmgr_dmod->tbl_measure_hrv->Active)
         {
            dbmgr_dmod->tbl_measure_hrv->Close();
         }
         if (dbmgr_dmod->tbl_patient_audit->Active)
         {
            dbmgr_dmod->tbl_patient_audit->Close();
         }
         if (dbmgr_dmod->tbl_measure_pwa_audit->Active)
         {
            dbmgr_dmod->tbl_measure_pwa_audit->Close();
         }
         if (dbmgr_dmod->tbl_measure_pwv_audit->Active)
         {
            dbmgr_dmod->tbl_measure_pwv_audit->Close();
         }
         dbmgr_dmod->ADO_Connection->Connected = false;
         disconnected = !dbmgr_dmod->ADO_Connection->Connected;
      }
   }
   return (disconnected);
}

bool dbmgr_activate_database_set(AnsiString the_path, bool is_copy)
{
   AnsiString             expression;
   bool                   initialised = true;
   DBMGR_ID_TYPE          id;
   AnsiString             alias_path;
   AnsiString             connection_string;
   TADOConnection         *ado_connection;
   TDataSet               *data_set;

   id = DBMGR_PATIENT_TABLE;
   dbmgr_hrv_conversion_required = false;
   dbmgr_audit_conversion_required = false;

   if (is_copy)
   {
      ado_connection = dbmgr_dmod->ADO_Connection_copy;
   }
   else
   {
      ado_connection = dbmgr_dmod->ADO_Connection;
   }

   while (id < DBMGR_LAST_TABLE)
   {
      dbmgr_close(id, is_copy);
      id = (DBMGR_ID_TYPE)(id + 1);
   }

   alias_path = ExtractFilePath(ParamStr(0)) +the_path;
   ado_connection->Connected = false;
   alias_path = alias_path + DBMGR_DATABASE_NAME;

   connection_string = "Provider=Microsoft.Jet.OLEDB.4.0;Data Source=" +alias_path +";" +";Persist Security Info=False";
   /*
   //connection_string = "Provider=Microsoft.ACE.OLEDB.12.0;Data Source=" +alias_path +";" +";Persist Security Info=False"; // Access 2007
   */
   try
   {
      ado_connection->ConnectionString = connection_string;
      ado_connection->Connected = true;

      id = DBMGR_PATIENT_TABLE;
      while (id < DBMGR_LAST_TABLE && initialised)
      {
         if (!dbmgr_perform_file_check(id, the_path, is_copy))
         {
            if (id == DBMGR_MEASURE_PWM_TABLE ||
                 id == DBMGR_MEASURE_PWM_TREND_TABLE ||
                 id == DBMGR_MEASURE_PWM_SESSION_TABLE ||
                 id == DBMGR_DEVICE_TABLE)
            {
               // If this is a version 6 database, write a message to the log
               // and continue with conversion
               log_write(SWARNING +" PWM Database Table Does Not Exist.");
            }
            else
            {
               if (id == DBMGR_MEASURE_HRV_TABLE)
               {
                  // If the HRV table does not exist
                  // then set the flag to perform a conversion
                  dbmgr_hrv_conversion_required = true;
               }
               else if (id == DBMGR_PATIENT_AUDIT_TABLE ||
                        id == DBMGR_MEASURE_PWA_AUDIT_TABLE ||
                        id == DBMGR_MEASURE_PWV_AUDIT_TABLE)
               {
                  // If the audit tables do not exist
                  // then set the flag to perform a conversion
                  dbmgr_audit_conversion_required = true;
               }
               else
               {
                  initialised = false;
                  MsgBox_show(TERROR,
                              MSG_DBMGR_ERROR,
                              LoadStr(MSG_DBMGR_FAIL_INIT),
                              MSG_DBMGR_FAIL_INIT,
                              LoadStr(MSG_DBMGR_FAIL_INIT));
               }
            }
            
         }
         id = (DBMGR_ID_TYPE) (id + 1);
      }
   }
   catch (Exception &exception)
   {
       MsgBox_show(TFATAL,
                   MSG_DBMGR_ERROR,
                   LoadStr(MSG_DBMGR_NO_DB),
                   MSG_DBMGR_NO_DB,
                   LoadStr(MSG_DBMGR_NO_DB) +exception.Message);
       initialised = false;
   }
   return (initialised);
}

bool dbmgr_perform_file_check(DBMGR_ID_TYPE  id,
                              AnsiString     db_path,
                              bool           is_copy)
{
   bool              files_found = false;
   TADOTable         *table;
   TDataSource       *data_source;
   TADOConnection    *ado_conn;
   AnsiString        db_name;
   AnsiString        file_name;
   table = NULL;
   data_source = NULL;
   try
   {
       switch (id)
       {
          case DBMGR_PATIENT_TABLE:
             if (is_copy)
             {
                data_source = dbmgr_dmod->dsrc_patient_copy;
                table = dbmgr_dmod->tbl_patient_copy;
                ado_conn =  dbmgr_dmod->ADO_Connection_copy;
             }
             else
             {
                data_source = dbmgr_dmod->dsrc_patient;
                table = dbmgr_dmod->tbl_patient;
                ado_conn = dbmgr_dmod->ADO_Connection;
                dbmgr_dmod->qry_patient->Connection = ado_conn;
                dbmgr_dmod->dsrc_qry_patient->DataSet = dbmgr_dmod->qry_patient;
             }
             db_name = patient_get_table_name();
             break;

          case DBMGR_MEASURE_PWA_TABLE:
             if (is_copy)
             {
                data_source = dbmgr_dmod->dsrc_measure_pwa_copy;
                table = dbmgr_dmod->tbl_measure_pwa_copy;
                ado_conn = dbmgr_dmod->ADO_Connection_copy;
             }
             else
             {
                data_source = dbmgr_dmod->dsrc_measure_pwa;
                table = dbmgr_dmod->tbl_measure_pwa;
                ado_conn = dbmgr_dmod->ADO_Connection;
                dbmgr_dmod->qry_measure_pwa->Connection = ado_conn;
                dbmgr_dmod->dsrc_qry_measure_pwa->DataSet = dbmgr_dmod->qry_measure_pwa;
             }
             db_name = meas_pwa_get_table_name();
             break;

          case DBMGR_MEASURE_PWV_TABLE:
             if (is_copy)
             {
                data_source = dbmgr_dmod->dsrc_measure_pwv_copy;
                table = dbmgr_dmod->tbl_measure_pwv_copy;
                ado_conn = dbmgr_dmod->ADO_Connection_copy;
             }
             else
             {
                data_source = dbmgr_dmod->dsrc_measure_pwv;
                table = dbmgr_dmod->tbl_measure_pwv;
                ado_conn = dbmgr_dmod->ADO_Connection;
                dbmgr_dmod->qry_measure_pwv->Connection = ado_conn;
                dbmgr_dmod->dsrc_qry_measure_pwv->DataSet = dbmgr_dmod->qry_measure_pwv;
             }
             db_name = meas_pwv_get_table_name();
             break;

           case DBMGR_MEASURE_PWM_TABLE:
             if (is_copy)
             {
                data_source = dbmgr_dmod->dsrc_measure_pwm_copy;
                table = dbmgr_dmod->tbl_measure_pwm_copy;
                ado_conn = dbmgr_dmod->ADO_Connection_copy;
             }
             else
             {
                data_source = dbmgr_dmod->dsrc_measure_pwm;
                table = dbmgr_dmod->tbl_measure_pwm;
                ado_conn = dbmgr_dmod->ADO_Connection;
                dbmgr_dmod->qry_measure_pwm->Connection = ado_conn;
                dbmgr_dmod->dsrc_qry_measure_pwm->DataSet = dbmgr_dmod->qry_measure_pwm;
             }
             db_name = meas_pwm_get_pwm_table_name();
             break;

            case DBMGR_MEASURE_PWM_TREND_TABLE:
             if (is_copy)
             {
                data_source = dbmgr_dmod->dsrc_measure_pwm_trend_copy;
                table = dbmgr_dmod->tbl_measure_pwm_trend_copy;
                ado_conn = dbmgr_dmod->ADO_Connection_copy;
             }
             else
             {
                data_source = dbmgr_dmod->dsrc_measure_pwm_trend;
                table = dbmgr_dmod->tbl_measure_pwm_trend;
                ado_conn = dbmgr_dmod->ADO_Connection;
                dbmgr_dmod->qry_measure_pwm_trend->Connection = ado_conn;
                dbmgr_dmod->dsrc_qry_measure_pwm_trend->DataSet = dbmgr_dmod->qry_measure_pwm_trend;
             }
             db_name = meas_pwm_get_trend_table_name();
             break;

          case DBMGR_MEASURE_PWM_SESSION_TABLE:
             if (is_copy)
             {
                data_source = dbmgr_dmod->dsrc_measure_pwm_session_copy;
                table = dbmgr_dmod->tbl_measure_pwm_session_copy;
                ado_conn = dbmgr_dmod->ADO_Connection_copy;
             }
             else
             {
                data_source = dbmgr_dmod->dsrc_measure_pwm_session;
                table = dbmgr_dmod->tbl_measure_pwm_session;
                ado_conn = dbmgr_dmod->ADO_Connection;
                dbmgr_dmod->qry_measure_pwm_session->Connection = ado_conn;
                dbmgr_dmod->dsrc_qry_measure_pwm_session->DataSet = dbmgr_dmod->qry_measure_pwm_session;
             }
             db_name = meas_pwm_get_session_table_name();
             break;

          case DBMGR_DEVICE_TABLE:
             if (is_copy)
             {
                data_source = dbmgr_dmod->dsrc_device_pwm_copy;
                table = dbmgr_dmod->tbl_device_pwm_copy;
                ado_conn = dbmgr_dmod->ADO_Connection_copy;
             }
             else
             {
                data_source = dbmgr_dmod->dsrc_device_pwm;
                table = dbmgr_dmod->tbl_device_pwm;
                ado_conn = dbmgr_dmod->ADO_Connection;
             }
             db_name = meas_pwm_get_device_table_name();
             break;

          case DBMGR_MEASURE_HRV_TABLE:
             if (is_copy)
             {
                data_source = dbmgr_dmod->dsrc_measure_hrv_copy;
                table = dbmgr_dmod->tbl_measure_hrv_copy;
                ado_conn = dbmgr_dmod->ADO_Connection_copy;
             }
             else
             {
                data_source = dbmgr_dmod->dsrc_measure_hrv;
                table = dbmgr_dmod->tbl_measure_hrv;
                ado_conn = dbmgr_dmod->ADO_Connection;
                dbmgr_dmod->qry_measure_hrv->Connection = ado_conn;
                dbmgr_dmod->dsrc_qry_measure_hrv->DataSet = dbmgr_dmod->qry_measure_hrv;
             }
             db_name = meas_hrv_get_table_name();
             break;

          case DBMGR_PATIENT_AUDIT_TABLE:
             if (is_copy)
             {
                data_source = dbmgr_dmod->dsrc_patient_audit_copy;
                table = dbmgr_dmod->tbl_patient_audit_copy;
                ado_conn = dbmgr_dmod->ADO_Connection_copy;
             }
             else
             {
                data_source = dbmgr_dmod->dsrc_patient_audit;
                table = dbmgr_dmod->tbl_patient_audit;
                ado_conn = dbmgr_dmod->ADO_Connection;
                dbmgr_dmod->qry_patient_audit->Connection = ado_conn;
                dbmgr_dmod->dsrc_qry_patient_audit->DataSet = dbmgr_dmod->qry_patient_audit;
             }
             db_name = audit_patient_get_table_name();
             break;

          case DBMGR_MEASURE_PWA_AUDIT_TABLE:
             if (is_copy)
             {
                data_source = dbmgr_dmod->dsrc_measure_pwa_audit_copy;
                table = dbmgr_dmod->tbl_measure_pwa_audit_copy;
                ado_conn = dbmgr_dmod->ADO_Connection_copy;
             }
             else
             {
                data_source = dbmgr_dmod->dsrc_measure_pwa_audit;
                table = dbmgr_dmod->tbl_measure_pwa_audit;
                ado_conn = dbmgr_dmod->ADO_Connection;
                dbmgr_dmod->qry_measure_pwa_audit->Connection = ado_conn;
                dbmgr_dmod->dsrc_qry_measure_pwa_audit->DataSet = dbmgr_dmod->qry_measure_pwa_audit;
             }
             db_name = audit_pwa_get_table_name();
             break;

          case DBMGR_MEASURE_PWV_AUDIT_TABLE:
             if (is_copy)
             {
                data_source = dbmgr_dmod->dsrc_measure_pwv_audit_copy;
                table = dbmgr_dmod->tbl_measure_pwv_audit_copy;
                ado_conn = dbmgr_dmod->ADO_Connection_copy;
             }
             else
             {
                data_source = dbmgr_dmod->dsrc_measure_pwv_audit;
                table = dbmgr_dmod->tbl_measure_pwv_audit;
                ado_conn = dbmgr_dmod->ADO_Connection;
                dbmgr_dmod->qry_measure_pwv_audit->Connection = ado_conn;
                dbmgr_dmod->dsrc_qry_measure_pwv_audit->DataSet = dbmgr_dmod->qry_measure_pwv_audit;
             }
             db_name = audit_pwv_get_table_name();
             break;

          default:
             break;
       }

       if (table)
       {
          table->Active = false;
          table->Connection = ado_conn;
          if (dbmgr_table_exists(db_name, is_copy))
          {
             table->TableName = db_name;
             data_source->DataSet = table;
             files_found = true;
          }
       }
   }
   catch (Exception &exception)
   {
       MsgBox_show(TERROR,
                   MSG_DBMGR_ERROR,
                   LoadStr(MSG_DBMGR_ERROR_DB),
                   MSG_DBMGR_ERROR_DB,
                   LoadStr(MSG_DBMGR_ERROR_DB) +exception.Message);
       files_found = false;
   }
   return (files_found);
}


bool dbmgr_open(DBMGR_ID_TYPE id, bool is_copy)
{
   TDataSet    *table;
   AnsiString  error_msg;
   bool        opened = false;

    if (id == 0)
   {
      return false;
   }

   if (dbmgr_is_open(id, is_copy))
   {
      opened = true;
   }
   else
   {
      table = dbmgr_get_dataset(id, is_copy);
      if (table)
      {
         try
         {
            table->Open();
            if (id == DBMGR_PATIENT_TABLE)
            {
              ((TDateField *)table->FieldByName(PATIENT_DOB))->DisplayFormat = DATE_DISPLAY_FORMAT;
            }
            opened = true;
         }
         catch (Exception& exception)
         {
            MsgBox_show(TERROR,
                        MSG_DBMGR_ERROR,
                        LoadStr(MSG_DBMGR_ERROR_OPEN_TABLE),
                        MSG_DBMGR_ERROR_OPEN_TABLE,
                        LoadStr(MSG_DBMGR_ERROR_OPEN_TABLE) +exception.Message);
            MsgBox("WE STRONGLY RECOMMEND EXITING THE SOFTWARE\nAND RESTARTING WINDOWS.",
                    SNOTIFICATION,
                    MB_ICONSTOP | MB_OK);
         }
      }
   }
   return opened;
}

bool dbmgr_close(DBMGR_ID_TYPE  id, bool is_copy)
{
   TDataSet *data_set;
   bool     closed = false;

   if (id == 0)
   {
      return false;
   }

   data_set = dbmgr_get_dataset(id, is_copy);

   if (data_set)
   {
      if (data_set->Active)
      {
         data_set->Close();
         closed = true;
      }
      else
      {
         closed = true;
      }
   }
   return closed;
}


bool dbmgr_is_open(DBMGR_ID_TYPE id, bool is_copy)
{
   TDataSet *table;
   bool     is_open = false;

   table = dbmgr_get_dataset(id, is_copy);

   if (table)
   {
      if (table->Active)
      {
         is_open = true;
      }
   }
   return (is_open);
}

TDataSet *dbmgr_get_dataset(DBMGR_ID_TYPE id, bool is_copy)
{
   TDataSet *data_set;

   data_set = (TDataSet *)0;

   switch (id)
   {
      case DBMGR_PATIENT_TABLE:
         if (is_copy)
         {
            data_set = dbmgr_dmod->tbl_patient_copy;
         }
         else
         {
            data_set = dbmgr_dmod->tbl_patient;
         }
         break;
      case DBMGR_MEASURE_PWA_TABLE:
         if (is_copy)
         {
            data_set = dbmgr_dmod->tbl_measure_pwa_copy;
         }
         else
         {
            data_set = dbmgr_dmod->tbl_measure_pwa;
         }
         break;
      case DBMGR_MEASURE_PWV_TABLE:
         if (is_copy)
         {
            data_set = dbmgr_dmod->tbl_measure_pwv_copy;
         }
         else
         {
            data_set = dbmgr_dmod->tbl_measure_pwv;
         }
         break;
      case DBMGR_MEASURE_PWM_TABLE:
         if (is_copy)
         {
            data_set = dbmgr_dmod->tbl_measure_pwm_copy;
         }
         else
         {
            data_set = dbmgr_dmod->tbl_measure_pwm;
         }
         break;
      case DBMGR_MEASURE_PWM_TREND_TABLE:
         if (is_copy)
         {
            data_set = dbmgr_dmod->tbl_measure_pwm_trend_copy;
         }
         else
         {
            data_set = dbmgr_dmod->tbl_measure_pwm_trend;
         }
         break;
      case DBMGR_MEASURE_PWM_SESSION_TABLE:
         if (is_copy)
         {
            data_set = dbmgr_dmod->tbl_measure_pwm_session_copy;
         }
         else
         {
            data_set = dbmgr_dmod->tbl_measure_pwm_session;
         }
         break;
      case DBMGR_DEVICE_TABLE:
         if (is_copy)
         {
            data_set = dbmgr_dmod->tbl_device_pwm_copy;
         }
         else
         {
            data_set = dbmgr_dmod->tbl_device_pwm;
         }
         break;
      case DBMGR_MEASURE_HRV_TABLE:
         if (is_copy)
         {
            data_set = dbmgr_dmod->tbl_measure_hrv_copy;
         }
         else
         {
            data_set = dbmgr_dmod->tbl_measure_hrv;
         }
         break;
      case DBMGR_PATIENT_AUDIT_TABLE:
         if (is_copy)
         {
            data_set = dbmgr_dmod->tbl_patient_audit_copy;
         }
         else
         {
            data_set = dbmgr_dmod->tbl_patient_audit;
         }
         break;
      case DBMGR_MEASURE_PWA_AUDIT_TABLE:
         if (is_copy)
         {
            data_set = dbmgr_dmod->tbl_measure_pwa_audit_copy;
         }
         else
         {
            data_set = dbmgr_dmod->tbl_measure_pwa_audit;
         }
         break;
      case DBMGR_MEASURE_PWV_AUDIT_TABLE:
         if (is_copy)
         {
            data_set = dbmgr_dmod->tbl_measure_pwv_audit_copy;
         }
         else
         {
            data_set = dbmgr_dmod->tbl_measure_pwv_audit;
         }
         break;
      case DBMGR_PATIENT_QUERY:
         data_set = dbmgr_dmod->qry_patient;
         break;
      case DBMGR_MEASURE_PWA_QUERY:
         data_set = dbmgr_dmod->qry_measure_pwa;
         break;
      case DBMGR_MEASURE_PWV_QUERY:
         data_set = dbmgr_dmod->qry_measure_pwv;
         break;
      case DBMGR_MEASURE_PWM_QUERY:
         data_set = dbmgr_dmod->qry_measure_pwm;
         break;
      case DBMGR_MEASURE_PWM_TREND_QUERY:
         data_set = dbmgr_dmod->qry_measure_pwm_trend;
         break;
      case DBMGR_MEASURE_PWM_SESSION_QUERY:
         data_set = dbmgr_dmod->qry_measure_pwm_session;
         break;
      case DBMGR_MEASURE_HRV_QUERY:
         data_set = dbmgr_dmod->qry_measure_hrv;
         break;
      case DBMGR_PATIENT_AUDIT_QUERY:
         data_set = dbmgr_dmod->qry_patient_audit;
         break;
      case DBMGR_MEASURE_PWA_AUDIT_QUERY:
         data_set = dbmgr_dmod->qry_measure_pwa_audit;
         break;
      case DBMGR_MEASURE_PWV_AUDIT_QUERY:
         data_set = dbmgr_dmod->qry_measure_pwv_audit;
         break;
      default:
         break;
   }
   return (data_set);
}

TDataSource *dbmgr_get_data_source(DBMGR_ID_TYPE id, bool is_copy)
{
   TDataSource *data_source;

   data_source = NULL;

   switch (id)
   {
      case DBMGR_PATIENT_TABLE:
         if (is_copy)
         {
            data_source = dbmgr_dmod->dsrc_patient_copy;
         }
         else
         {
            data_source = dbmgr_dmod->dsrc_patient;
         }
         break;
      case DBMGR_MEASURE_PWA_TABLE:
         if (is_copy)
         {
            data_source = dbmgr_dmod->dsrc_measure_pwa_copy;
         }
         else
         {
            data_source = dbmgr_dmod->dsrc_measure_pwa;
         }
         break;
      case DBMGR_MEASURE_PWV_TABLE:
         if (is_copy)
         {
            data_source = dbmgr_dmod->dsrc_measure_pwv_copy;
         }
         else
         {
            data_source = dbmgr_dmod->dsrc_measure_pwv;
         }
         break;
      case DBMGR_MEASURE_PWM_TABLE:
         if (is_copy)
         {
            data_source = dbmgr_dmod->dsrc_measure_pwm_copy;
         }
         else
         {
            data_source = dbmgr_dmod->dsrc_measure_pwm;
         }
         break;
      case DBMGR_MEASURE_PWM_TREND_TABLE:
         if (is_copy)
         {
            data_source = dbmgr_dmod->dsrc_measure_pwm_trend_copy;
         }
         else
         {
            data_source = dbmgr_dmod->dsrc_measure_pwm_trend;
         }
         break;
      case DBMGR_MEASURE_PWM_SESSION_TABLE:
         if (is_copy)
         {
            data_source = dbmgr_dmod->dsrc_measure_pwm_session_copy;
         }
         else
         {
            data_source = dbmgr_dmod->dsrc_measure_pwm_session;
         }
         break;
      case DBMGR_DEVICE_TABLE:
         if (is_copy)
         {
            data_source = dbmgr_dmod->dsrc_device_pwm_copy;
         }
         else
         {
            data_source = dbmgr_dmod->dsrc_device_pwm;
         }
         break;
      case DBMGR_MEASURE_HRV_TABLE:
         data_source = dbmgr_dmod->dsrc_measure_hrv;
         break;
      case DBMGR_PATIENT_AUDIT_TABLE:
         if (is_copy)
         {
            data_source = dbmgr_dmod->dsrc_patient_audit_copy;
         }
         else
         {
            data_source = dbmgr_dmod->dsrc_patient_audit;
         }
         break;
      case DBMGR_MEASURE_PWA_AUDIT_TABLE:
         if (is_copy)
         {
            data_source = dbmgr_dmod->dsrc_measure_pwa_audit_copy;
         }
         else
         {
            data_source = dbmgr_dmod->dsrc_measure_pwa_audit;
         }
         break;
      case DBMGR_MEASURE_PWV_AUDIT_TABLE:
         if (is_copy)
         {
            data_source = dbmgr_dmod->dsrc_measure_pwv_audit_copy;
         }
         else
         {
            data_source = dbmgr_dmod->dsrc_measure_pwv_audit;
         }
         break;
      case DBMGR_PATIENT_QUERY:
         data_source = dbmgr_dmod->dsrc_qry_patient;
         break;
      case DBMGR_MEASURE_PWA_QUERY:
         data_source = dbmgr_dmod->dsrc_qry_measure_pwa;
         break;
      case DBMGR_MEASURE_PWV_QUERY:
         data_source = dbmgr_dmod->dsrc_qry_measure_pwv;
         break;
      case DBMGR_MEASURE_PWM_QUERY:
         data_source = dbmgr_dmod->dsrc_qry_measure_pwm;
         break;
      case DBMGR_MEASURE_PWM_TREND_QUERY:
         data_source = dbmgr_dmod->dsrc_qry_measure_pwm_trend;
         break;
      case DBMGR_MEASURE_PWM_SESSION_QUERY:
         data_source = dbmgr_dmod->dsrc_qry_measure_pwm_session;
         break;
      case DBMGR_MEASURE_HRV_QUERY:
         data_source = dbmgr_dmod->dsrc_qry_measure_hrv;
         break;
      case DBMGR_PATIENT_AUDIT_QUERY:
         data_source = dbmgr_dmod->dsrc_qry_patient_audit;
         break;
      case DBMGR_MEASURE_PWA_AUDIT_QUERY:
         data_source = dbmgr_dmod->dsrc_qry_measure_pwa_audit;
         break;
      case DBMGR_MEASURE_PWV_AUDIT_QUERY:
         data_source = dbmgr_dmod->dsrc_qry_measure_pwv_audit;
         break;
      default:
         break;
   }
   return (data_source);
}

bool dbmgr_table_exists(AnsiString table_name, bool is_copy)
{
   TStrings *SL = new TStringList;
   int i = 0;
   bool exists = false;

   if (is_copy)
   {
      dbmgr_dmod->ADO_Connection_copy->GetTableNames(SL, false);
   }
   else
   {
      dbmgr_dmod->ADO_Connection->GetTableNames(SL, false);
   }

   i = 0;
   while (i < SL->Count && !exists)
   {
      if (table_name == SL->Strings[i])
      {
         exists = true;
      }
      ++i;
   }
   delete SL;
   return (exists);
}

TADOQuery *dbmgr_setup_query(DBMGR_ID_TYPE     id,
                          DBMGR_QUERY_TYPE  qry_type,
                          String            field_name1,
                          String            field_name2,
                          String            field_name3,
                          String            value1,
                          String            value2,
                          String            value3)
{
   TADOQuery            *qry;
   DBMGR_ID_TYPE     qry_id;
   AnsiString        qry_string = NULL;
   AnsiString        table_name;
   AnsiString        error_msg;
   TDataChangeEvent  dsrc_change_event;
   TDataSource       *qry_data_source;

   qry = NULL;
   dsrc_change_event = NULL;

   switch (id)
   {
      case DBMGR_PATIENT_TABLE:
         qry_id = DBMGR_PATIENT_QUERY;
         table_name = patient_get_table_name();
         break;
      case DBMGR_MEASURE_PWA_TABLE:
         qry_id = DBMGR_MEASURE_PWA_QUERY;
         table_name = meas_pwa_get_table_name();
         break;
      case DBMGR_MEASURE_PWV_TABLE:
         qry_id = DBMGR_MEASURE_PWV_QUERY;
         table_name = meas_pwv_get_table_name();
         break;
      case DBMGR_MEASURE_PWM_TABLE:
         qry_id = DBMGR_MEASURE_PWM_QUERY;
         table_name = meas_pwm_get_pwm_table_name();
         break;
      case DBMGR_MEASURE_PWM_TREND_TABLE:
         qry_id = DBMGR_MEASURE_PWM_TREND_QUERY;
         table_name = meas_pwm_get_trend_table_name();
         break;
      case DBMGR_MEASURE_PWM_SESSION_TABLE:
         qry_id = DBMGR_MEASURE_PWM_SESSION_QUERY;
         table_name = meas_pwm_get_session_table_name();
         qry_data_source = dbmgr_get_data_source(DBMGR_MEASURE_PWM_SESSION_QUERY, false);
         break;
      case DBMGR_MEASURE_HRV_TABLE:
         qry_id = DBMGR_MEASURE_HRV_QUERY;
         table_name = meas_hrv_get_table_name();
         break;
      case DBMGR_PATIENT_AUDIT_TABLE:
         qry_id = DBMGR_PATIENT_AUDIT_QUERY;
         table_name = audit_patient_get_table_name();
         break;
      case DBMGR_MEASURE_PWA_AUDIT_TABLE:
         qry_id = DBMGR_MEASURE_PWA_AUDIT_QUERY;
         table_name = audit_pwa_get_table_name();
         break;
      case DBMGR_MEASURE_PWV_AUDIT_TABLE:
         qry_id = DBMGR_MEASURE_PWV_AUDIT_QUERY;
         table_name = audit_pwv_get_table_name();
         break;
      default:
         qry_id = (DBMGR_ID_TYPE) 0;
         break;
   }

   if (qry_id)
   {
      if (qry_type == DBMGR_QUERY_KEY)
      {
         if (field_name3.Length() &&
             value3.Length())
         {
            qry_string = "SELECT * FROM " + table_name +
                         " WHERE " + field_name1 + "=" + "\"" + value1 + "\"" +
                         " AND " + field_name2 + "=" + "\"" + value2 + "\"" +
                         " AND " + field_name3 + "=" + value3;
         }
      }
      else if (qry_type == DBMGR_QUERY_DATETIME)
      {
         if (value1.Length() &&
             value2.Length() &&
             field_name1.Length())
         {
            qry_string = "SELECT * FROM " + table_name +
                         " WHERE " + field_name1 + ">=" + StrToInt(value1) +
                         " AND " + field_name1 + "<=" + StrToInt(value2);
         }
      }
      else if (qry_type == DBMGR_QUERY_PATIENT_NUMBER)
      {
         if (value1.Length() &&
             value2.Length() &&
             field_name1.Length() &&
             field_name2.Length())
         {
            qry_string = "SELECT * FROM " +table_name +
                         " WHERE " + field_name1 + "=" + "\"" + value1 + "\""  +
                         " AND " +field_name2 + "=" + "\"" + value2  + "\"";
         }
      }
      // PM V9
      else if (qry_type == DBMGR_QUERY_PATIENT_SEARCH)
      {
         if (value1.Length())
         {
            if (value2.Length())
            {
               if (value3.Length())
               {
                  qry_string = "SELECT * FROM " + table_name +
                         " WHERE " + field_name1 + "=" + "\"" + value1 + "\"" +
                         " AND " + field_name2 + "=" + "\"" + value2 + "\"" +
                         " AND " + field_name3 + "=" + "\"" + value3 + "\"";
               }
               else
               {
                  qry_string = "SELECT * FROM " + table_name +
                         " WHERE " + field_name1 + "=" + "\"" + value1 + "\"" +
                         " AND " + field_name2 + "=" + "\"" + value2 + "\"";
               }
            }
            else if (value3.Length())
            {
               qry_string = "SELECT * FROM " + table_name +
                         " WHERE " + field_name1 + "=" + "\"" + value1 + "\"" +
                         " AND " + field_name3 + "=" + "\"" + value3 + "\"";
            }
            else
            {
               qry_string = "SELECT * FROM " + table_name +
                         " WHERE " + field_name1 + "=" + "\"" + value1 + "\"";
            }
         }
         else if (value2.Length())
         {
            if (value3.Length())
            {
               qry_string = "SELECT * FROM " + table_name +
                      " WHERE " + field_name2 + "=" + "\"" + value2 + "\"" +
                      " AND " + field_name3 + "=" + "\"" + value3 + "\"";
            }
            else
            {
               qry_string = "SELECT * FROM " + table_name +
                      " WHERE " + field_name2 + "=" + "\"" + value2 + "\"";
            }
         }
         else if (value3.Length())
         {
            qry_string = "SELECT * FROM " + table_name +
                      " WHERE " + field_name3 + "=" + "\"" + value3 + "\"";
         }
      }
      if (qry_string != NULL)
      {
         try
         {
            qry = dynamic_cast<TADOQuery *>(dbmgr_get_dataset(qry_id, false));
            qry->DisableControls();
            qry->Close();
            qry->SQL->Clear();
            qry->SQL->Add(qry_string);
            qry->Open();
            if (id == DBMGR_MEASURE_PWA_TABLE || id == DBMGR_MEASURE_PWV_TABLE || id == DBMGR_MEASURE_HRV_TABLE)
            {
               ((TDateTimeField *)qry->FieldByName(MPW_DATETIME))->DisplayFormat = DATETIME_DISPLAY_FORMAT;
            }
            if (id == DBMGR_MEASURE_PWM_SESSION_TABLE)
            {
               ((TDateTimeField *)qry->FieldByName(MPWM_SESSION_START))->DisplayFormat = DATETIME_DISPLAY_FORMAT;
            }
            if (id == DBMGR_PATIENT_AUDIT_TABLE || id == DBMGR_MEASURE_PWA_AUDIT_TABLE || id == DBMGR_MEASURE_PWV_AUDIT_TABLE)
            {
               ((TDateTimeField *)qry->FieldByName(MPWA_AUDIT_DATETIME))->DisplayFormat = DATETIME_DISPLAY_FORMAT;
            }
            if (qry_id == DBMGR_MEASURE_PWM_SESSION_QUERY)
            {
               if (qry_data_source != NULL)
               {
                  dsrc_change_event = qry_data_source->OnDataChange;
                  qry_data_source->OnDataChange = NULL;
               }
            }
            qry->EnableControls();
            if (qry_id == DBMGR_MEASURE_PWM_SESSION_QUERY)
            {
               if (qry_data_source != NULL)
               {
                  qry_data_source->OnDataChange = dsrc_change_event;
               }
            }

         }
         catch (Exception& exception)
         {
            String S = LoadStr(MSG_DBMGR_ERROR_QUERY) +table_name +" " +exception.Message;
            MsgBox_show(TERROR,
                        MSG_DBMGR_ERROR,
                        LoadStr(MSG_DBMGR_ERROR_QUERY),
                        MSG_DBMGR_ERROR_QUERY,
                        S);
         }
      }
   }
   return (qry);
}

TADOQuery *dbmgr_setup_query(DBMGR_ID_TYPE     id,
                          DBMGR_QUERY_TYPE  qry_type,
                          String            field_name1,
                          String            field_name2,
                          String            field_name3,
                          String            value1,
                          String            value2,
                          String            value3,
                          String            order)
{
   TADOQuery            *qry;
   DBMGR_ID_TYPE     qry_id;
   AnsiString        qry_string = NULL;
   AnsiString        table_name;
   AnsiString        error_msg;
   TDataChangeEvent  dsrc_change_event;
   TDataSource       *qry_data_source;

   qry = NULL;
   dsrc_change_event = NULL;

   switch (id)
   {
      case DBMGR_PATIENT_TABLE:
         qry_id = DBMGR_PATIENT_QUERY;
         table_name = patient_get_table_name();
         break;
      case DBMGR_MEASURE_PWA_TABLE:
         qry_id = DBMGR_MEASURE_PWA_QUERY;
         table_name = meas_pwa_get_table_name();
         break;
      case DBMGR_MEASURE_PWV_TABLE:
         qry_id = DBMGR_MEASURE_PWV_QUERY;
         table_name = meas_pwv_get_table_name();
         break;
      case DBMGR_MEASURE_PWM_TABLE:
         qry_id = DBMGR_MEASURE_PWM_QUERY;
         table_name = meas_pwm_get_pwm_table_name();
         break;
      case DBMGR_MEASURE_PWM_TREND_TABLE:
         qry_id = DBMGR_MEASURE_PWM_TREND_QUERY;
         table_name = meas_pwm_get_trend_table_name();
         break;
      case DBMGR_MEASURE_PWM_SESSION_TABLE:
         qry_id = DBMGR_MEASURE_PWM_SESSION_QUERY;
         table_name = meas_pwm_get_session_table_name();
         qry_data_source = dbmgr_get_data_source(DBMGR_MEASURE_PWM_SESSION_QUERY, false);
         break;
      case DBMGR_MEASURE_HRV_TABLE:
         qry_id = DBMGR_MEASURE_HRV_QUERY;
         table_name = meas_hrv_get_table_name();
         break;
      case DBMGR_PATIENT_AUDIT_TABLE:
         qry_id = DBMGR_PATIENT_AUDIT_QUERY;
         table_name = audit_patient_get_table_name();
         break;
      case DBMGR_MEASURE_PWA_AUDIT_TABLE:
         qry_id = DBMGR_MEASURE_PWA_AUDIT_QUERY;
         table_name = audit_pwa_get_table_name();
         break;
      case DBMGR_MEASURE_PWV_AUDIT_TABLE:
         qry_id = DBMGR_MEASURE_PWV_AUDIT_QUERY;
         table_name = audit_pwv_get_table_name();
         break;
      default:
         qry_id = (DBMGR_ID_TYPE) 0;
         break;
   }

   if (qry_id)
   {
      if (qry_type == DBMGR_QUERY_KEY)
      {
         if (field_name3.Length() &&
             value3.Length())
         {
            qry_string = "SELECT * FROM " + table_name +
                         " WHERE " + field_name1 + "=" + "\"" + value1 + "\"" +
                         " AND " + field_name2 + "=" + "\"" + value2 + "\"" +
                         " AND " + field_name3 + "=" + value3 +
                         " ORDER BY " + order;
         }
      }
      else if (qry_type == DBMGR_QUERY_DATETIME)
      {
         if (value1.Length() &&
             value2.Length() &&
             field_name1.Length())
         {
            qry_string = "SELECT * FROM " + table_name +
                         " WHERE " + field_name1 + ">=" + StrToInt(value1) +
                         " AND " + field_name1 + "<=" + StrToInt(value2) +
                         " ORDER BY " + order;
         }
      }
      else if (qry_type == DBMGR_QUERY_PATIENT_NUMBER)
      {
         if (value1.Length() &&
             value2.Length() &&
             field_name1.Length() &&
             field_name2.Length())
         {
            qry_string = "SELECT * FROM " +table_name +
                         " WHERE " + field_name1 + "=" + "\"" + value1 + "\""  +
                         " AND " +field_name2 + "=" + "\"" + value2  + "\"" +
                         " ORDER BY " + order;
         }
      }
      if (qry_string != NULL)
      {
         try
         {
            qry = dynamic_cast<TADOQuery *>(dbmgr_get_dataset(qry_id, false));
            qry->DisableControls();
            qry->Close();
            qry->SQL->Clear();
            qry->SQL->Add(qry_string);
            qry->Open();
            if (id == DBMGR_MEASURE_PWA_TABLE || id == DBMGR_MEASURE_PWV_TABLE || id == DBMGR_MEASURE_HRV_TABLE)
            {
               ((TDateTimeField *)qry->FieldByName(MPW_DATETIME))->DisplayFormat = DATETIME_DISPLAY_FORMAT;
            }
            if (id == DBMGR_MEASURE_PWM_SESSION_TABLE)
            {
               ((TDateTimeField *)qry->FieldByName(MPWM_SESSION_START))->DisplayFormat = DATETIME_DISPLAY_FORMAT;
            }
            if (id == DBMGR_PATIENT_AUDIT_TABLE || id == DBMGR_MEASURE_PWA_AUDIT_TABLE || id == DBMGR_MEASURE_PWV_AUDIT_TABLE)
            {
               ((TDateTimeField *)qry->FieldByName(MPWA_AUDIT_DATETIME))->DisplayFormat = DATETIME_DISPLAY_FORMAT;
            }
            if (qry_id == DBMGR_MEASURE_PWM_SESSION_QUERY)
            {
               if (qry_data_source != NULL)
               {
                  dsrc_change_event = qry_data_source->OnDataChange;
                  qry_data_source->OnDataChange = NULL;
               }
            }
            qry->EnableControls();
            if (qry_id == DBMGR_MEASURE_PWM_SESSION_QUERY)
            {
               if (qry_data_source != NULL)
               {
                  qry_data_source->OnDataChange = dsrc_change_event;
               }
            }

         }
         catch (Exception& exception)
         {
            String S = LoadStr(MSG_DBMGR_ERROR_QUERY) +table_name +" " +exception.Message;
            MsgBox_show(TERROR,
                        MSG_DBMGR_ERROR,
                        LoadStr(MSG_DBMGR_ERROR_QUERY),
                        MSG_DBMGR_ERROR_QUERY,
                        S);
         }
      }
   }
   return (qry);
}

TADOQuery *dbmgr_setup_query(DBMGR_ID_TYPE     id,
                          DBMGR_QUERY_TYPE  qry_type,
                          String            field_name1,
                          String            field_name2,
                          String            field_name3,
                          String            field_name4,
                          String            value1,
                          String            value2,
                          String            value3,
                          String            value4)
{
   TADOQuery          *qry;
   DBMGR_ID_TYPE   qry_id;
   AnsiString      qry_string = NULL;
   AnsiString      table_name;
   AnsiString      error_msg;
   String          value5;

   qry = NULL;

   switch (id)
   {
      case DBMGR_PATIENT_TABLE:
         qry_id = DBMGR_PATIENT_QUERY;
         table_name = patient_get_table_name();
         break;
      case DBMGR_MEASURE_PWA_TABLE:
         qry_id = DBMGR_MEASURE_PWA_QUERY;
         table_name = meas_pwa_get_table_name();
         break;
      case DBMGR_MEASURE_PWV_TABLE:
         qry_id = DBMGR_MEASURE_PWV_QUERY;
         table_name = meas_pwv_get_table_name();
         break;
      case DBMGR_MEASURE_PWM_TABLE:
         qry_id = DBMGR_MEASURE_PWM_QUERY;
         table_name = meas_pwm_get_pwm_table_name();
         break;
      case DBMGR_MEASURE_PWM_TREND_TABLE:
         qry_id = DBMGR_MEASURE_PWM_TREND_QUERY;
         table_name = meas_pwm_get_trend_table_name();
         break;
      case DBMGR_MEASURE_PWM_SESSION_TABLE:
         qry_id = DBMGR_MEASURE_PWM_SESSION_QUERY;
         table_name = meas_pwm_get_session_table_name();
         break;
      case DBMGR_MEASURE_HRV_TABLE:
         qry_id = DBMGR_MEASURE_HRV_QUERY;
         table_name = meas_hrv_get_table_name();
         break;
      case DBMGR_PATIENT_AUDIT_TABLE:
         qry_id = DBMGR_PATIENT_AUDIT_QUERY;
         table_name = audit_patient_get_table_name();
         break;
      case DBMGR_MEASURE_PWA_AUDIT_TABLE:
         qry_id = DBMGR_MEASURE_PWA_AUDIT_QUERY;
         table_name = audit_pwa_get_table_name();
         break;
      case DBMGR_MEASURE_PWV_AUDIT_TABLE:
         qry_id = DBMGR_MEASURE_PWV_AUDIT_QUERY;
         table_name = audit_pwv_get_table_name();
         break;
      default:
         qry_id = (DBMGR_ID_TYPE) 0;
         break;
   }

   if (qry_id)
   {
      if (qry_type == DBMGR_QUERY_KEY)
      {
         if (field_name4.Length() &&
             value4.Length())
         {
            qry_string = "SELECT * FROM " + table_name +
                         " WHERE " + field_name1 + "=" + "\"" + value1 + "\"" +
                         " AND " + field_name2 + "=" + "\"" + value2 + "\"" +
                         " AND " + field_name3 + "=" +value3 +
                         " AND " + field_name4 + "=" +value4;
         }
      }
      else if (qry_type == DBMGR_QUERY_DATETIME)
      {
         if (value1.Length() &&
             value2.Length() &&
             field_name1.Length())
         {
            qry_string = "SELECT * FROM " + table_name +
                         " WHERE " + field_name1 + ">=" + StrToInt(value1) +
                         " AND " + field_name1 + "<=" + StrToInt(value2);
         }
      }
      else if (qry_type == DBMGR_QUERY_PATIENT_NUMBER)
      {
         if (value1.Length() &&
             value2.Length() &&
             field_name1.Length() &&
             field_name2.Length())
         {
            qry_string = "SELECT * FROM " +table_name +
                         " WHERE " + field_name1 + "=" + "\"" + value1 + "\""  +
                         " AND " +field_name2 + "=" + "\"" + value2  + "\"";
         }
      }
      if (qry_type == DBMGR_QUERY_AUDIT_FLAG)
      {
         if (field_name4.Length() &&
             value4.Length())
         {
            // This query includes records where the audit flag is null -
            // old records - but does not include deleted records
            qry_string = "SELECT * FROM " + table_name +
                         " WHERE " + field_name1 + "=" + "\"" + value1 + "\"" +
                         " AND " + field_name2 + "=" + "\"" + value2 + "\"" +
                         " AND " + field_name3 + "=" +value3 +
                         " AND (" + field_name4 + "<>" + value4 +
                         " OR " + field_name4 + " IS NULL)";
         }
      }
      // PM V9
      else if (qry_type == DBMGR_QUERY_PATIENT_SEARCH)
      {
         if (value4.Length())
         {
            // Querying the exact datetime does not work in sql, so query
            // between 2 values either side of the datetime required
            TDateTime dob = TDateTime(value4);
            value4 = String(double(dob - TDateTime( 0, 0, 0, 1)));
            value5 = String(double(dob + TDateTime( 0, 0, 0, 1)));

            if (value1.Length())
            {
               if (value2.Length())
               {
                  if (value3.Length())
                  {
                     qry_string = "SELECT * FROM " + table_name +
                            " WHERE " + field_name1 + "=" + "\"" + value1 + "\"" +
                            " AND " + field_name2 + "=" + "\"" + value2 + "\"" +
                            " AND " + field_name3 + "=" + "\"" + value3 + "\"" +
                            " AND " + field_name4 + ">=" + value4 +
                            " AND " + field_name4 + "<=" + value5;
                  }
                  else
                  {
                     qry_string = "SELECT * FROM " + table_name +
                            " WHERE " + field_name1 + "=" + "\"" + value1 + "\"" +
                            " AND " + field_name2 + "=" + "\"" + value2 + "\"" +
                            " AND " + field_name4 + ">=" + value4 +
                            " AND " + field_name4 + "<=" + value5;
                  }
               }
               else if (value3.Length())
               {
                  qry_string = "SELECT * FROM " + table_name +
                            " WHERE " + field_name1 + "=" + "\"" + value1 + "\"" +
                            " AND " + field_name3 + "=" + "\"" + value3 + "\"" +
                            " AND " + field_name4 + ">=" + value4 +
                            " AND " + field_name4 + "<=" + value5;
               }
               else
               {
                  qry_string = "SELECT * FROM " + table_name +
                            " WHERE " + field_name1 + "=" + "\"" + value1 + "\"" +
                            " AND " + field_name4 + ">=" + value4 +
                            " AND " + field_name4 + "<=" + value5;
               }
            }
            else if (value2.Length())
            {
               if (value3.Length())
               {
                  qry_string = "SELECT * FROM " + table_name +
                         " WHERE " + field_name2 + "=" + "\"" + value2 + "\"" +
                         " AND " + field_name3 + "=" + "\"" + value3 + "\"" +
                         " AND " + field_name4 + ">=" + value4 +
                         " AND " + field_name4 + "<=" + value5;
               }
               else
               {
                  qry_string = "SELECT * FROM " + table_name +
                         " WHERE " + field_name2 + "=" + "\"" + value2 + "\"" +
                         " AND " + field_name4 + ">=" + value4 +
                         " AND " + field_name4 + "<=" + value5;
               }
            }
            else if (value3.Length())
            {
               qry_string = "SELECT * FROM " + table_name +
                         " WHERE " + field_name3 + "=" + "\"" + value3 + "\"" +
                         " AND " + field_name4 + ">=" + value4 +
                         " AND " + field_name4 + "<=" + value5;
            }
            else
            {
               qry_string = "SELECT * FROM " + table_name +
                         " WHERE " + field_name4 + ">=" + value4 +
                         " AND " + field_name4 + "<=" + value5;
            }
         }
      }
      if (qry_string != NULL)
      {
         try
         {
            qry = dynamic_cast<TADOQuery *>(dbmgr_get_dataset(qry_id, false));
            qry->DisableControls();
            qry->Close();
            qry->SQL->Clear();
            qry->SQL->Add(qry_string);
            qry->Open();
            if (id == DBMGR_MEASURE_PWA_TABLE || id == DBMGR_MEASURE_PWV_TABLE || id == DBMGR_MEASURE_HRV_TABLE)
            {
               ((TDateTimeField *)qry->FieldByName(MPW_DATETIME))->DisplayFormat = DATETIME_DISPLAY_FORMAT;
            }
            if (id == DBMGR_MEASURE_PWM_SESSION_TABLE)
            {
               ((TDateTimeField *)qry->FieldByName(MPWM_SESSION_START))->DisplayFormat = DATETIME_DISPLAY_FORMAT;
            }
            if (id == DBMGR_PATIENT_AUDIT_TABLE || id == DBMGR_MEASURE_PWA_AUDIT_TABLE || id == DBMGR_MEASURE_PWV_AUDIT_TABLE)
            {
               ((TDateTimeField *)qry->FieldByName(MPWA_AUDIT_DATETIME))->DisplayFormat = DATETIME_DISPLAY_FORMAT;
            }
            qry->EnableControls();
         }
         catch (Exception& exception)
         {
            String S = LoadStr(MSG_DBMGR_ERROR_QUERY) +table_name +" " +exception.Message;
            MsgBox_show(TERROR,
                        MSG_DBMGR_ERROR,
                        LoadStr(MSG_DBMGR_ERROR_QUERY),
                        MSG_DBMGR_ERROR_QUERY, S);
         }
      }
   }
   return (qry);
}

TADOQuery *dbmgr_setup_query(DBMGR_ID_TYPE     id,
                          DBMGR_QUERY_TYPE  qry_type,
                          String            field_name1,
                          String            field_name2,
                          String            field_name3,
                          String            field_name4,
                          String            value1,
                          String            value2,
                          String            value3,
                          String            value4,
                          String            order)
{
   TADOQuery          *qry;
   DBMGR_ID_TYPE   qry_id;
   AnsiString      qry_string = NULL;
   AnsiString      table_name;
   AnsiString      error_msg;
   String          value5;

   qry = NULL;

   switch (id)
   {
      case DBMGR_PATIENT_TABLE:
         qry_id = DBMGR_PATIENT_QUERY;
         table_name = patient_get_table_name();
         break;
      case DBMGR_MEASURE_PWA_TABLE:
         qry_id = DBMGR_MEASURE_PWA_QUERY;
         table_name = meas_pwa_get_table_name();
         break;
      case DBMGR_MEASURE_PWV_TABLE:
         qry_id = DBMGR_MEASURE_PWV_QUERY;
         table_name = meas_pwv_get_table_name();
         break;
      case DBMGR_MEASURE_PWM_TABLE:
         qry_id = DBMGR_MEASURE_PWM_QUERY;
         table_name = meas_pwm_get_pwm_table_name();
         break;
      case DBMGR_MEASURE_PWM_TREND_TABLE:
         qry_id = DBMGR_MEASURE_PWM_TREND_QUERY;
         table_name = meas_pwm_get_trend_table_name();
         break;
      case DBMGR_MEASURE_PWM_SESSION_TABLE:
         qry_id = DBMGR_MEASURE_PWM_SESSION_QUERY;
         table_name = meas_pwm_get_session_table_name();
         break;
      case DBMGR_MEASURE_HRV_TABLE:
         qry_id = DBMGR_MEASURE_HRV_QUERY;
         table_name = meas_hrv_get_table_name();
         break;
      case DBMGR_PATIENT_AUDIT_TABLE:
         qry_id = DBMGR_PATIENT_AUDIT_QUERY;
         table_name = audit_patient_get_table_name();
         break;
      case DBMGR_MEASURE_PWA_AUDIT_TABLE:
         qry_id = DBMGR_MEASURE_PWA_AUDIT_QUERY;
         table_name = audit_pwa_get_table_name();
         break;
      case DBMGR_MEASURE_PWV_AUDIT_TABLE:
         qry_id = DBMGR_MEASURE_PWV_AUDIT_QUERY;
         table_name = audit_pwv_get_table_name();
         break;
      default:
         qry_id = (DBMGR_ID_TYPE) 0;
         break;
   }

   if (qry_id)
   {
      if (qry_type == DBMGR_QUERY_KEY)
      {
         if (field_name4.Length() &&
             value4.Length())
         {
            qry_string = "SELECT * FROM " + table_name +
                         " WHERE " + field_name1 + "=" + "\"" + value1 + "\"" +
                         " AND " + field_name2 + "=" + "\"" + value2 + "\"" +
                         " AND " + field_name3 + "=" +value3 +
                         " AND " + field_name4 + "=" + value4 +
                         " ORDER BY " + order;
         }
      }
      else if (qry_type == DBMGR_QUERY_DATETIME)
      {
         if (value1.Length() &&
             value2.Length() &&
             field_name1.Length())
         {
            qry_string = "SELECT * FROM " + table_name +
                         " WHERE " + field_name1 + ">=" + StrToInt(value1) +
                         " AND " + field_name1 + "<=" + StrToInt(value2);
         }
      }
      else if (qry_type == DBMGR_QUERY_PATIENT_NUMBER)
      {
         if (value1.Length() &&
             value2.Length() &&
             field_name1.Length() &&
             field_name2.Length())
         {
            qry_string = "SELECT * FROM " +table_name +
                         " WHERE " + field_name1 + "=" + "\"" + value1 + "\""  +
                         " AND " +field_name2 + "=" + "\"" + value2  + "\"";
         }
      }
      else if (qry_type == DBMGR_QUERY_AUDIT)
      {
         if (field_name4.Length() &&
             value4.Length())
         {
            // Querying the exact datetime does not work in sql, so query
            // between 2 values either side of the datetime required
            TDateTime audit = TDateTime(value4);
            value4 = String(double(audit - TDateTime( 0, 0, 0, 1)));
            value5 = String(double(audit + TDateTime( 0, 0, 0, 1)));
            qry_string = "SELECT * FROM " + table_name +
                         " WHERE " + field_name1 + "=" + "\"" + value1 + "\"" +
                         " AND " + field_name2 + "=" + "\"" + value2 + "\"" +
                         " AND " + field_name3 + "=" +value3 +
                         " AND " + field_name4 + ">=" + value4 +
                         " AND " + field_name4 + "<=" + value5;
                         " ORDER BY " + order;
         }
      }
      if (qry_type == DBMGR_QUERY_AUDIT_FLAG)
      {
         if (field_name4.Length() &&
             value4.Length())
         {
            // This query includes records where the audit flag is null -
            // old records - but does not include deleted records
            qry_string = "SELECT * FROM " + table_name +
                         " WHERE " + field_name1 + "=" + "\"" + value1 + "\"" +
                         " AND " + field_name2 + "=" + "\"" + value2 + "\"" +
                         " AND " + field_name3 + "=" +value3 +
                         " AND (" + field_name4 + "<>" + value4 +
                         " OR " + field_name4 + " IS NULL)" +
                         " ORDER BY " + order;
         }
      }
      if (qry_string != NULL)
      {
         try
         {
            qry = dynamic_cast<TADOQuery *>(dbmgr_get_dataset(qry_id, false));
            qry->DisableControls();
            qry->Close();
            qry->SQL->Clear();
            qry->SQL->Add(qry_string);
            qry->Open();
            if (id == DBMGR_MEASURE_PWA_TABLE || id == DBMGR_MEASURE_PWV_TABLE || id == DBMGR_MEASURE_HRV_TABLE)
            {
               ((TDateTimeField *)qry->FieldByName(MPW_DATETIME))->DisplayFormat = DATETIME_DISPLAY_FORMAT;
            }
            if (id == DBMGR_MEASURE_PWM_SESSION_TABLE)
            {
               ((TDateTimeField *)qry->FieldByName(MPWM_SESSION_START))->DisplayFormat = DATETIME_DISPLAY_FORMAT;
            }
            if (id == DBMGR_PATIENT_AUDIT_TABLE || id == DBMGR_MEASURE_PWA_AUDIT_TABLE || id == DBMGR_MEASURE_PWV_AUDIT_TABLE)
            {
               ((TDateTimeField *)qry->FieldByName(MPWA_AUDIT_DATETIME))->DisplayFormat = DATETIME_DISPLAY_FORMAT;
            }
            qry->EnableControls();
         }
         catch (Exception& exception)
         {
            String S = LoadStr(MSG_DBMGR_ERROR_QUERY) +table_name +" " +exception.Message;
            MsgBox_show(TERROR,
                        MSG_DBMGR_ERROR,
                        LoadStr(MSG_DBMGR_ERROR_QUERY),
                        MSG_DBMGR_ERROR_QUERY, S);
         }
      }
   }
   return (qry);
}

bool dbmgr_select_index(DBMGR_ID_TYPE  id,
                        AnsiString     idx_name)
{
   TADOTable      *table;
   bool        reindexed = false;
   bool        was_open = false;
   AnsiString  error_msg;

   if (dbmgr_is_open(id, false))
   {
      dbmgr_close(id, false);
      was_open = true;
   }

   try
   {
      table = dynamic_cast<TADOTable *>(dbmgr_get_dataset(id, false));
      if (table)
      {
         table->IndexFieldNames = idx_name;
         reindexed = true;
      }
   }
   catch (Exception& exception)
   {
      MsgBox_show(TERROR,
                  MSG_DBMGR_ERROR,
                  LoadStr(MSG_DBMGR_ERROR_INDEX),
                  MSG_DBMGR_ERROR_INDEX,
                  LoadStr(MSG_DBMGR_ERROR_INDEX) +exception.Message);

      MsgBox("WE STRONGLY RECOMMEND EXITING SphygmoCor\nrestarting the computer and running SphygmoCor again.",
             SNOTIFICATION,
             MB_ICONSTOP | MB_OK);
      reindexed = false;
   }

   if (was_open)
   {
      dbmgr_open(id, false);
   }

   return (reindexed);
}

//---------------------------------------------------------------------------
__fastcall Tdbmgr_dmod::Tdbmgr_dmod(TComponent* Owner)
    : TDataModule(Owner)
{
}
//---------------------------------------------------------------------------

bool dbmgr_conversion(TLabel* status, AnsiString the_path)
{
   dbmgr_conversion_required = false;
   bool dbmgr_conversion_successful = false;

   // Perform an audit conversion if the flag has been set by dbmgr_activate_database_set
   if (dbmgr_audit_conversion_required)
   {
      dbmgr_conversion_required = true;
      MsgBox(TNOTIFICATION,
               MSG_DBMGR_ERROR,
               MSG_DBMGR_NO_AUDIT_TABLE,
               LoadStr(MSG_DBMGR_NO_AUDIT_TABLE));

      log_write("Starting Database Conversion");
      status->Caption = "Starting Database Conversion";
      Application->ProcessMessages();
      if (dbmgr_convert_database(status, the_path))
      {
         if (dbmgr_perform_file_check(DBMGR_PATIENT_AUDIT_TABLE, the_path, false))
         {
            if (dbmgr_perform_file_check(DBMGR_MEASURE_PWA_AUDIT_TABLE, the_path, false))
            {
               if (dbmgr_perform_file_check(DBMGR_MEASURE_PWV_AUDIT_TABLE, the_path, false))
               {
                  log_write("Database Conversion Successful.");
                  dbmgr_audit_conversion_required = false;
                  MsgBox_information("Audit Tables added to database.", "Conversion Successful");
                  dbmgr_conversion_successful = true;
               }
               else
               {
                  log_write("Database Conversion Failed...No PWV Audit Table");
                  MsgBox_warning("PWV Audit Table could not be found.", "Conversion Failed");
                  config_set_audit_option(false);
               }
            }
            else
            {
               log_write("Database Conversion Failed...No PWA Audit Table");
               MsgBox_warning("PWA Audit Table could not be found.", "Conversion Failed");
               config_set_audit_option(false);
            }
         }
         else
         {
            log_write("Database Conversion Failed...No Patient Audit Table");
            MsgBox_warning("Patient Audit Table could not be found.", "Conversion Failed");
            config_set_audit_option(false);
         }
      }
      else
      {
         log_write("Database Conversion Failed...Could not add Audit Tables");
         MsgBox_warning("Audit Tables could not be added.", "Conversion Failed");
         config_set_audit_option(false);
      }
   }

   if (!dbmgr_conversion_required)
   {
      dbmgr_conversion_successful = true;
   }
   return(dbmgr_conversion_successful);
}

bool dbmgr_convert_database(TLabel* status, AnsiString the_path)
{
   AnsiString       source_path;
   AnsiString       source_pathfile;
   AnsiString       rename_pathfile;
   AnsiString       default_path;
   AnsiString       dest_path;
   ULONG        database_size;
   bool         converted = false;
   bool         converted_audit = false;
   bool         new_database_copied = true;

   // Initialise database paths and check that enough disk space is available
   source_path = ExtractFilePath(ParamStr(0)) + the_path;
   source_pathfile = source_path + DBMGR_DATABASE_NAME;
   rename_pathfile = source_path + DBMGR_PRE_DATABASE_NAME;
   default_path = ExtractFilePath(ParamStr(0)) + CONFIG_SYSTEM_SUBDIR + "\\" + DBMGR_DATABASE_NAME;
   dest_path = ExtractFilePath(ParamStr(0)) + DBMGR_DATABASE_NAME;
   database_size = emma_get_file_size(source_pathfile);
   VLONG free_space = emma_get_disk_space(dest_path[1]);
   if (free_space < 1.2 * database_size)
   {
      MsgBox(TERROR, MSG_DBMGR_ERROR, MSG_DBMGR_NO_SPACE, LoadStr(MSG_DBMGR_NO_SPACE) + IntToStr((int)database_size));
      return false;
   }

   // Check if there is a database in the destination directory
   if (FileExists(dest_path))
   {
      if (CopyFile(default_path.c_str(), dest_path.c_str(), false) == 0)
      {
         new_database_copied = false;
      }
   }
   else
   {
      if (CopyFile(default_path.c_str(), dest_path.c_str(), true) == 0)
      {
         new_database_copied = false;
      }
   }

   if (FileExists(dest_path) && new_database_copied)
   {
      Screen->Cursor = crHourGlass;
      if (dbmgr_perform_simple_activation("", true))
      {
         status->Caption = "Converting Patient Table";
         Application->ProcessMessages();
         if (dbmgr_copy_table(DBMGR_PATIENT_TABLE))
         {
            status->Caption = "Converting PWA Table";
            Application->ProcessMessages();
            if (dbmgr_copy_table(DBMGR_MEASURE_PWA_TABLE))
            {
               status->Caption = "Converting PWV Table";
               Application->ProcessMessages();
               if (dbmgr_copy_table(DBMGR_MEASURE_PWV_TABLE))
               {
                  status->Caption = "Converting PWM Tables";
                  Application->ProcessMessages();
                  if (dbmgr_copy_table(DBMGR_MEASURE_PWM_SESSION_TABLE))
                  {
                     if (dbmgr_copy_table(DBMGR_MEASURE_PWM_TREND_TABLE))
                     {
                        if (dbmgr_copy_table(DBMGR_MEASURE_PWM_TABLE))
                        {
                           if (dbmgr_audit_conversion_required)
                           {
                              // When performing an audit conversion, copy the
                              // patient table to the audit trail because
                              // patient table edits are linked to the database
                              // and cannot be traced.
                              status->Caption = "Copying Patient Table";
                              Application->ProcessMessages();
                              if (dbmgr_copy_table_to_table(DBMGR_PATIENT_TABLE, DBMGR_PATIENT_AUDIT_TABLE))
                              {
                                 converted_audit = true;
                              }
                              else
                              {
                                 log_write("Database Conversion Failed..Copy Patient Audit Table");
                              }
                           }
                           else
                           {
                              converted_audit = true;
                           }
                           if (converted_audit)
                           {
                              if (!dbmgr_hrv_conversion_required)
                              {
                                 // If the database already has a HRV table
                                 // then copy the records to the new database
                                 status->Caption = "Converting HRV Table";
                                 Application->ProcessMessages();
                                 if (dbmgr_copy_table(DBMGR_MEASURE_HRV_TABLE))
                                 {
                                    converted = true;
                                 }
                                 else
                                 {
                                    log_write("Database Conversion Failed..Copy HRV Table");
                                 }
                              }
                              else
                              {
                                 converted = true;
                              }
                           }
                        }
                        else
                        {
                           log_write("Database Conversion Failed..Copy PWM Table");
                        }
                     }
                     else
                     {
                        log_write("Database Conversion Failed..Copy PWM Trend Table");
                     }
                  }
                  else
                  {
                     log_write("Database Conversion Failed..Copy PWM Session Table");
                  }
               }
               else
               {
                  log_write("Database Conversion Failed..Copy PWV Table");
               }
            }
            else
            {
               log_write("Database Conversion Failed..Copy PWA Table");
            }
         }
         else
         {
            log_write("Database Conversion Failed..Copy Patient Table");
         }
         dbmgr_disconnect_database_set(true);

         if (converted)
         {
            dbmgr_disconnect_database_set(false);
            if (FileExists(rename_pathfile))
            {
               DeleteFile(rename_pathfile);
            }
            if (RenameFile(source_pathfile, rename_pathfile))
            {
               if (CopyFile(dest_path.c_str(), source_pathfile.c_str(), false) == 0)
               {
                  RenameFile(rename_pathfile, source_pathfile);
                  converted = false;
               }
            }
            else
            {
               converted = false;
               log_write("Database Conversion Failed..Rename");
            }
            DeleteFile(dest_path);
            if (dbmgr_perform_simple_activation(dbmgr_default_path, true))
            {
               dbmgr_initialised = true;
            }
            else
            {
               converted = false;
            }
         }
         else
         {
            dbmgr_initialised = true;
         }
      }
      Screen->Cursor = crDefault;
   }
   else
   {
      dbmgr_initialised = true;
   }
   return converted;
}

bool dbmgr_copy_table(DBMGR_ID_TYPE  id)
{
   TADOTable    *source_table;
   TADOTable    *copy_table;
   AnsiString   tbl_name;

   try
   {
      tbl_name = "Unknown";
      if (dbmgr_open(id, false))
      {
         source_table = dynamic_cast<TADOTable *>(dbmgr_get_dataset(id, false));
         source_table->First();
         tbl_name = source_table->TableName;
         tbl_name = tbl_name +" Copy Table ";
         if (dbmgr_open(id, true))
         {
            copy_table = dynamic_cast<TADOTable *>(dbmgr_get_dataset(id, true));

            for (int i = 0; i < source_table->RecordCount; i++)
            {
               copy_table->Append();
               for (int j = 0; j < source_table->FieldCount; j++)
               {
                  copy_table->Fields->Fields[j]->Value = source_table->Fields->Fields[j]->Value;
               }
               copy_table->Post();
               source_table->Next();
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
                   LoadStr(MSG_POST_ERROR) +tbl_name +exception.Message);
       return false;
   }
   return true;
}

bool dbmgr_copy_table_to_table(DBMGR_ID_TYPE  source, DBMGR_ID_TYPE  copy)
{
   TADOTable    *source_table;
   TADOTable    *copy_table;
   AnsiString   tbl_name;

   try
   {
      tbl_name = "Unknown";
      if (dbmgr_open(source, false))
      {
         source_table = dynamic_cast<TADOTable *>(dbmgr_get_dataset(source, false));
         source_table->First();
         tbl_name = source_table->TableName;
         tbl_name = tbl_name +" Copy Table ";
         if (dbmgr_open(copy, true))
         {
            copy_table = dynamic_cast<TADOTable *>(dbmgr_get_dataset(copy, true));

            for (int i = 0; i < source_table->RecordCount; i++)
            {
               copy_table->Append();
               for (int j = 0; j < source_table->FieldCount; j++)
               {
                  copy_table->Fields->Fields[j]->Value = source_table->Fields->Fields[j]->Value;
               }
               copy_table->Post();
               source_table->Next();
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
                   LoadStr(MSG_POST_ERROR) +tbl_name +exception.Message);
       return false;
   }
   return true;
}

bool dbmgr_perform_simple_activation(AnsiString the_path, bool is_copy)
{
   AnsiString             expression;
   bool                   activated = true;
   DBMGR_ID_TYPE          id;
   AnsiString             alias_path;
   AnsiString             connection_string;
   TADOConnection         *ado_connection;

   id = DBMGR_PATIENT_TABLE;

   if (is_copy)
   {
      ado_connection = dbmgr_dmod->ADO_Connection_copy;
   }
   else
   {
      ado_connection = dbmgr_dmod->ADO_Connection;
   }

   while (id < DBMGR_LAST_TABLE)
   {
      dbmgr_close(id, is_copy);
      id = (DBMGR_ID_TYPE)(id + 1);
   }

   alias_path = ExtractFilePath(ParamStr(0)) +the_path;
   ado_connection->Connected = false;
   alias_path = alias_path + DBMGR_DATABASE_NAME;

   connection_string = "Provider=Microsoft.Jet.OLEDB.4.0;Data Source=" +alias_path +";" +";Persist Security Info=False";
   try
   {
      ado_connection->ConnectionString = connection_string;
      ado_connection->Connected = true;

      id = DBMGR_PATIENT_TABLE;
      while (id < DBMGR_LAST_TABLE && activated)
      {
         dbmgr_perform_file_check(id, the_path, is_copy);
         id = (DBMGR_ID_TYPE) (id + 1);
      }
   }
   catch (Exception &exception)
   {
       MsgBox_show(TFATAL,
                   MSG_DBMGR_ERROR,
                   LoadStr(MSG_DBMGR_NO_DB),
                   MSG_DBMGR_NO_DB,
                   LoadStr(MSG_DBMGR_NO_DB) +exception.Message);
       activated = false;
   }
   return (activated);
}

