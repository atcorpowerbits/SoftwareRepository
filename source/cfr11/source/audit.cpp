//---------------------------------------------------------------------------
              

#include <vcl.h>
#pragma hdrstop

#include <cfr11/pubserv.h>
#include <dbmgr/pubserv.h>
#include <patient/pubserv.h>
#include <msg/pubserv.h>
#include <config/pubserv.h>
#include "audit.h"
#include "form_patient.h"
#include "form_main.h"
#include "form_report_pwa.h"
#include "form_report_pwv.h"
//---------------------------------------------------------------------------

#pragma package(smart_init)

bool audit_initialised;

String audit_patient_get_table_name()
{
  return PATIENT_AUDIT;
}                                                         

String audit_pwa_get_table_name()
{
  return MPWA_AUDIT;
}

String audit_pwv_get_table_name()
{
  return MPWV_AUDIT;
}
//---------------------------------------------------------------------------
bool audit_initialise()
{
   audit_initialised = true;

   return audit_initialised;
}
//---------------------------------------------------------------------------
void audit_destroy()
{
   audit_initialised = false;
}

/*---------------------------------------------------------------------------
// This function maintains the audit trail when a patient record is edited
*/
bool audit_patient_edit(TDataSet *patient_table)
{
   TDataSet             *patient_audit_table;
   TDataSource          *patient_audit_dsrc;
   bool                 success = false;

   // If the audit option is not set, post the changes to the patient table as is.
   if(!config_get_audit_option())
   {
      patient_table->Post();
      return true;
   }

   // Validate the new data and verify the operator's identity
   if (audit_patient_validate_record(patient_table))
   {
      if (security_show())
      {
         patient_audit_dsrc = dbmgr_get_data_source(DBMGR_PATIENT_AUDIT_TABLE, false);
         if (patient_audit_dsrc != NULL)
         {
            patient_audit_table = dbmgr_get_dataset(DBMGR_PATIENT_AUDIT_TABLE, false);
            if (patient_audit_table != NULL)
            {
               try
               {
                  // Insert audit data to the patient table
                  patient_table->FieldByName(PATIENT_AUDIT_OPERATOR)->Value = security_get_username();
                  patient_table->FieldByName(PATIENT_AUDIT_FLAG)->AsInteger = AUDIT_MODIFIED;
                  patient_table->Post();
                  // Copy record to the audit table
                  if (dbmgr_open(DBMGR_PATIENT_AUDIT_TABLE, false))
                  {
                     if (audit_copy_record(patient_table, patient_audit_table))
                     {
                        patient_audit_table->FieldByName(PATIENT_AUDIT_DATETIME)->AsDateTime = Now();
                        patient_audit_table->Post();
                        success = true;
                     }
                     dbmgr_close(DBMGR_PATIENT_AUDIT_TABLE, false);
                  }
               }
               catch (Exception &exception)
               {
                  MsgBox_show(TERROR,
                              MSG_DBREADWRITE_ERROR,
                              LoadStr(MSG_POST_ERROR),
                              MSG_POST_ERROR,
                              LoadStr(MSG_POST_ERROR) +patient_get_error_str() +exception.Message);
                  patient_audit_table->Cancel();
               }
            }
         }
      }
      else
      {
         patient_table->Cancel();
      }
   }
   return success;
}

/*---------------------------------------------------------------------------
// This function maintains the audit trail when a patient record is created
*/
bool audit_patient_insert(TDataSet *patient_table)
{
   TDataSet     *patient_audit_table;
   TDataSource  *patient_audit_dsrc;
   bool         success = false;

   // If the audit option is not set, post the changes to the patient table as is.
   if(!config_get_audit_option())
   {
      patient_table->Post();
      return true;
   }
                                                              
   // Verify the Operator's identity. Data validation is not required to insert a record
   if (security_show())
   {
      patient_audit_dsrc = dbmgr_get_data_source(DBMGR_PATIENT_AUDIT_TABLE, false);
      if (patient_audit_dsrc != NULL)
      {
         patient_audit_table = dbmgr_get_dataset(DBMGR_PATIENT_AUDIT_TABLE, false);
         if (patient_audit_table != NULL)
         {
            try
            {
               // Insert audit data to the patient table
               patient_table->FieldByName(PATIENT_AUDIT_OPERATOR)->Value = security_get_username();
               patient_table->FieldByName(PATIENT_AUDIT_FLAG)->AsInteger = AUDIT_ORIGINAL;
               patient_table->Post();
               // Copy record to the audit table
               if (dbmgr_open(DBMGR_PATIENT_AUDIT_TABLE, false))
               {
                  if (audit_copy_record(patient_table, patient_audit_table))
                  {
                     patient_audit_table->FieldByName(PATIENT_AUDIT_DATETIME)->AsDateTime = Now();
                     patient_audit_table->Post();
                     success = true;
                  }
                  dbmgr_close(DBMGR_PATIENT_AUDIT_TABLE, false);
               }
            }
            catch (Exception &exception)
            {
               MsgBox_show(TERROR,
                           MSG_DBREADWRITE_ERROR,
                           LoadStr(MSG_POST_ERROR),
                           MSG_POST_ERROR,
                           LoadStr(MSG_POST_ERROR) +patient_get_error_str() +exception.Message);
               patient_audit_table->Cancel();
            }
         }
      }
   }
   else
   {
      patient_table->Cancel();
   }
   return success;
}

/*---------------------------------------------------------------------------
// This function maintains the audit trail when a patient record is deleted
*/
bool audit_patient_delete(TDataSet *patient_table)
{
   TDataSet             *patient_audit_table;
   TDataSource          *patient_audit_dsrc;
   PATIENT_RECORD_TYPE  pat;
   bool                 success = false;

   // If the audit option is not set, let Patient handle the delete process
   if(!config_get_audit_option())
   {
      return true;
   }

   // Validate the data and verify the operator's identity
   if (audit_patient_validate_record(patient_table))
   {
      if (security_show())
      {
         patient_audit_dsrc = dbmgr_get_data_source(DBMGR_PATIENT_AUDIT_TABLE, false);
         if (patient_audit_dsrc != NULL)
         {
            patient_audit_table = dbmgr_get_dataset(DBMGR_PATIENT_AUDIT_TABLE, false);
            if (patient_audit_table != NULL)
            {
               try
               {
                  // PM V9
                  // Disable messages while deleting a patient
                  msg_disable_messages();

                  // Insert audit data to the patient table
                  patient_table->Edit();
                  patient_table->FieldByName(PATIENT_AUDIT_OPERATOR)->Value = security_get_username();
                  patient_table->FieldByName(PATIENT_AUDIT_FLAG)->AsInteger = AUDIT_DELETED;
                  patient_table->Post();
                  // Copy record to the audit table
                  if (dbmgr_open(DBMGR_PATIENT_AUDIT_TABLE, false))
                  {
                     if (audit_copy_record(patient_table, patient_audit_table))
                     {
                        patient_audit_table->FieldByName(PATIENT_AUDIT_DATETIME)->AsDateTime = Now();
                        patient_audit_table->Post();
                        success = true;
                     }
                     dbmgr_close(DBMGR_PATIENT_AUDIT_TABLE, false);
                  }

                  // Set the delete flag for the patient's PWA records
                  if (patient_get(&pat))
                  {
                     TDataSet *pwa_table = dbmgr_setup_query(DBMGR_MEASURE_PWA_TABLE,
                                              DBMGR_QUERY_KEY,
                                              PATIENT_SYSTEM_ID,
                                              PATIENT_STUDY_ID,
                                              PATIENT_NO,
                                              pat.system_id,
                                              pat.study_id,
                                              IntToStr(pat.number),
                                              MPW_DATETIME);
                     TPWA *pwa_current = meas_get_current_pwa();

                     // Scroll through the patient's PWA records
                     for (pwa_table->First(); !pwa_table->Eof; pwa_table->Next())
                     {
                        Application->ProcessMessages();
                        try
                        {
                           if (pwa_current->Populate(pwa_table))
                           {
                              // Set the delete flag if is has not been set already
                              if (pwa_current->AuditFlag != AUDIT_DELETED)
                              {
                                 // Insert the current record into the audit trail
                                 pwa_table->Edit();
                                 if (audit_pwa_insert(pwa_current, pwa_table, AUDIT_DELETING))
                                 {
                                    // Store audit data in the PWA table and copy into the audit trail
                                    pwa_current->Operator = security_get_username();
                                    pwa_current->Reason = "Deleted Patient";
                                    if (pwa_current->Store(pwa_table, false, false))
                                    {
                                       if (!audit_pwa_edit(pwa_table))
                                       {
                                          continue;
                                       }
                                    }
                                 }
                              }
                           }
                        }
                        catch (Exception &exception)
                        {
                           continue; // If something wrong still continue
                        }
                     }

                     // Set the delete flag for the patient's PWV records
                     TDataSet *pwv_table = dbmgr_setup_query(DBMGR_MEASURE_PWV_TABLE,
                                                 DBMGR_QUERY_KEY,
                                                 PATIENT_SYSTEM_ID,
                                                 PATIENT_STUDY_ID,
                                                 PATIENT_NO,
                                                 pat.system_id,
                                                 pat.study_id,
                                                 IntToStr(pat.number),
                                                 MPW_DATETIME);
                     TPWV *pwv_current = meas_get_current_pwv();
                     // Scroll through the patient's PWV records
                     for (pwv_table->First(); !pwv_table->Eof; pwv_table->Next())
                     {
                        Application->ProcessMessages();
                        try
                        {
                           if (pwv_current->Populate(pwv_table))
                           {
                              // Set the delete flag if is has not been set already
                              if (pwv_current->AuditFlag != AUDIT_DELETED)
                              {
                                 // Insert the current record into the audit trail
                                 pwv_table->Edit();
                                 if (audit_pwv_insert(pwv_current, pwv_table, AUDIT_DELETING))
                                 {
                                    // Store audit data in the PWV table and copy into the audit trail
                                    pwv_current->Operator = security_get_username();
                                    pwv_current->Reason = "Deleted Patient";
                                    if (pwv_current->Store(pwv_table, false, false))
                                    {
                                       if (!audit_pwv_edit(pwv_table))
                                       {
                                          continue;
                                       }
                                    }
                                 }
                              }
                           }
                        }
                        catch (Exception &exception)
                        {
                           continue; // If something wrong still continue
                        }
                     }
                  }
                  msg_enable_messages();
               }
               catch (Exception &exception)
               {
                  msg_enable_messages();
                  MsgBox_show(TERROR,
                              MSG_DBREADWRITE_ERROR,
                              LoadStr(MSG_POST_ERROR),
                              MSG_POST_ERROR,
                              LoadStr(MSG_POST_ERROR) +patient_get_error_str() +exception.Message);
                  patient_audit_table->Cancel();
               }
            }
         }
      }
   }
   return success;
}

//---------------------------------------------------------------------------

bool audit_patient_validate_record(TDataSet *patient_table)
{
   bool valid = true;

   // Ensure the operator has entered a reason for any changes to the database
   if (patient_table == NULL)
   {
      valid = false;
   }
   else
   {
      if (patient_table->FieldByName(PATIENT_AUDIT_REASON)->AsString.Length() == 0)
      {
         valid = false;
         frm_patient->mm_pat_reason->SetFocus();
      }
   }
   if (!valid)
   {
      MsgBox(MSG_AUDIT_PATIENT_CHECK_INPUT, SVALIDATION, MB_ICONEXCLAMATION);
   }

   return (valid);
}

bool audit_copy_record(TDataSet *source_table, TDataSet *copy_table)
{
   // Inserts a record from the source table to the copy table
   copy_table->Insert();
   for (int j = 0; j < source_table->FieldCount; j++)
   {
      copy_table->Fields->Fields[j]->Value = source_table->Fields->Fields[j]->Value;
   }

   return true;
}

/*---------------------------------------------------------------------------
// Displays the Patient audit trail
*/
bool audit_patient_show()
{
   PATIENT_RECORD_TYPE  pat;
   TADOQuery *patient_audit_qry;
   TColumn *audit_column;
   bool success = false;

   if (patient_get(&pat))
   {
      try
      {
         // Query the Patient Audit table
         Screen->Cursor = crHourGlass;
         patient_audit_qry = dbmgr_setup_query(DBMGR_PATIENT_AUDIT_TABLE,
                                             DBMGR_QUERY_KEY,
                                             PATIENT_SYSTEM_ID,
                                             PATIENT_STUDY_ID,
                                             PATIENT_NO,
                                             pat.system_id,
                                             pat.study_id,
                                             pat.number,
                                             PATIENT_AUDIT_DATETIME);
         int NofRecords = (patient_audit_qry != NULL ? patient_audit_qry->RecordCount : 0);

         if (NofRecords > 0)
         {
            // Change the audit button and disable database events
            frm_patient->bbtn_pat_audit->Caption = AUDIT_PATIENT_BUTTON_CAPTION;
            frm_patient->mnuSort->Enabled = false;

            patient_enable_database_events(true, true);

            // Change the grid display
            frm_patient->grd_pat->Columns->Clear();
            audit_column = frm_patient->grd_pat->Columns->Add();
            audit_column->FieldName = PATIENT_AUDIT_DATETIME;
            audit_column->Title->Caption = AUDIT_COLUMN_TITLE;
            audit_column->Width = AUDIT_COLUMN_WIDTH;

            patient_audit_qry->Last();
            if (frm_patient->pgctrl_pat->ActivePage == frm_patient->tbsht_pat_grid)
            {
               frm_patient->grd_pat->SetFocus();
            }
            success = true;
         }
         else
         {
            MsgBox(MSG_AUDIT_PATIENT_NO_REPORTS_TO_DISPLAY, SNOTIFICATION, MB_ICONINFORMATION);
         }
      }
      catch (Exception &exception)
      {
         ;
      }
      Screen->Cursor = crDefault;
   }
   return success;
}

/*---------------------------------------------------------------------------
// Displays the Patient table
*/
void audit_patient_hide()
{
   TDataSource *patient_audit_qry_dsrc;
   TColumn *patient_id;
   TColumn *date_of_birth;
   TColumn *first_name;
   TColumn *family_name;

   patient_audit_qry_dsrc = dbmgr_get_data_source(DBMGR_PATIENT_AUDIT_QUERY, false);
   if (patient_audit_qry_dsrc != NULL)
   {
      // Change the audit button and enable database events
      frm_patient->bbtn_pat_audit->Caption = AUDIT_BUTTON_CAPTION;
      frm_patient->mnuSort->Enabled = true;

      patient_enable_database_events(true, true);
      frm_patient->FormShow(Application);

      // Change the grid display
      frm_patient->grd_pat->Columns->Clear();
      patient_id = frm_patient->grd_pat->Columns->Add();
      patient_id->FieldName = PATIENT_ID;
      patient_id->Title->Caption = AUDIT_PATIENT_ID_TITLE;
      patient_id->Width = AUDIT_PATIENTS_COLUMN_WIDTH;

      date_of_birth = frm_patient->grd_pat->Columns->Add();
      date_of_birth->FieldName = PATIENT_DOB;
      date_of_birth->Title->Caption = AUDIT_PATIENT_DOB_TITLE;
      date_of_birth->Width = AUDIT_PATIENTS_COLUMN_WIDTH;

      first_name = frm_patient->grd_pat->Columns->Add();
      first_name->FieldName = PATIENT_FIRST_NAME;
      first_name->Title->Caption = AUDIT_PATIENT_FIRST_NAME_TITLE;
      first_name->Width = AUDIT_PATIENTS_COLUMN_WIDTH;

      family_name = frm_patient->grd_pat->Columns->Add();
      family_name->FieldName = PATIENT_SURNAME;
      family_name->Title->Caption = AUDIT_PATIENT_SURNAME_TITLE;
      family_name->Width = AUDIT_PATIENTS_COLUMN_WIDTH;
   }
}

/*---------------------------------------------------------------------------
// Update the PWA object with audit data
*/
bool audit_update_pwa(TPWA *pwa_current, String reason)
{
   bool          success = false;
   MEAS_ID_TYPE  study_mode;

   study_mode = patient_get_study_mode();

   // If the audit option is not set, let PWA handle the update process
   if(!config_get_audit_option() || study_mode == MEAS_PWM_ID)
   {
      return true;
   }

   // Validate new data and verify the operator's identity
   pwa_current->Reason = reason;

   if (audit_pwa_validate_record(pwa_current))
   {
      if (security_show())
      {
         pwa_current->Operator = security_get_username();
         success = true;
      }
   }

   return success;
}

bool audit_pwa_validate_record(TPWA *pwa_current)
{
   bool valid = true;

   // Ensure the operator has entered a reason for any changes to the database
   if (pwa_current->Reason.Length() == 0)
   {
      MsgBox_show(TWARNING,
                    MSG_VALIDATION_ERROR,
                    LoadStr(MSG_AUDIT_CHECK_INPUT),
                    MSG_AUDIT_CHECK_INPUT, "");
      valid = false;
   }

   return (valid);
}

/*---------------------------------------------------------------------------
// Inserts a record into the PWA Audit trail if one does not exist already
*/
bool audit_pwa_insert(TPWA *pwa_current, TDataSet *pwa_dataset, AUDIT_MODE AuditMode)
{
   TDataSet             *pwa_audit_table;
   bool                 success = false;
   MEAS_ID_TYPE  study_mode;

   study_mode = patient_get_study_mode();

   // If the audit option is not set, do not insert a record
   if(!config_get_audit_option() || study_mode == MEAS_PWM_ID)
   {
      return true;
   }

   // If this is the original record add it to the audit trail
   if (pwa_current->AuditFlag == AUDIT_ORIGINAL)
   {
      pwa_audit_table = dbmgr_get_dataset(DBMGR_MEASURE_PWA_AUDIT_TABLE, false);
      if (pwa_audit_table != NULL)
      {
         try
         {
            // Add audit data and copy to the Audit table
            pwa_dataset->FieldByName(MPWA_AUDIT_FLAG)->AsInteger = AUDIT_ORIGINAL;
            if (dbmgr_open(DBMGR_MEASURE_PWA_AUDIT_TABLE, false))
            {
               if (audit_copy_record(pwa_dataset, pwa_audit_table))
               {
                  pwa_audit_table->FieldByName(MPWA_AUDIT_DATETIME)->AsDateTime = pwa_dataset->FieldByName(MPW_DATETIME)->AsDateTime;
                  pwa_audit_table->Post();
                  success = true;
               }
               dbmgr_close(DBMGR_MEASURE_PWA_AUDIT_TABLE, false);
            }
         }
         catch (Exception &exception)
         {
            MsgBox_show(TERROR,
                        MSG_DBREADWRITE_ERROR,
                        LoadStr(MSG_POST_ERROR),
                        MSG_POST_ERROR,
                        LoadStr(MSG_POST_ERROR) +GetCurrentMeasureDetails() +exception.Message);
            pwa_audit_table->Cancel();
         }
      }
   }
   else
   {
      success = true;
   }
   // Set the audit flag for the record in the PWA table
   if (AuditMode == AUDIT_DELETING)
   {
      pwa_current->AuditFlag = AUDIT_DELETED;
   }
   else
   {
      pwa_current->AuditFlag = AUDIT_MODIFIED;
   }
   return success;
}

/*---------------------------------------------------------------------------
// Adds the edited or deleted record to the audit trail
*/
bool audit_pwa_edit(TDataSet *pwa_dataset)
{
   TDataSet             *pwa_audit_table;
   bool                 success = false;
   MEAS_ID_TYPE  study_mode;

   study_mode = patient_get_study_mode();

   // If the audit option is not set, do not insert a record
   if(!config_get_audit_option() || study_mode == MEAS_PWM_ID)
   {
      return true;
   }

   pwa_audit_table = dbmgr_get_dataset(DBMGR_MEASURE_PWA_AUDIT_TABLE, false);
   if (pwa_audit_table != NULL)
   {
      try
      {
         // Copy to the audit table
         if (dbmgr_open(DBMGR_MEASURE_PWA_AUDIT_TABLE, false))
         {
            if (audit_copy_record(pwa_dataset, pwa_audit_table))
            {
               pwa_audit_table->FieldByName(MPWA_AUDIT_DATETIME)->AsDateTime = Now();
               pwa_audit_table->Post();
               success = true;
            }
            dbmgr_close(DBMGR_MEASURE_PWA_AUDIT_TABLE, false);
         }
      }
      catch (Exception &exception)
      {
         MsgBox_show(TERROR,
                        MSG_DBREADWRITE_ERROR,
                        LoadStr(MSG_POST_ERROR),
                        MSG_POST_ERROR,
                        LoadStr(MSG_POST_ERROR) +GetCurrentMeasureDetails() +exception.Message);
         pwa_audit_table->Cancel();
      }
   }
   return success;
}

/*---------------------------------------------------------------------------
// Allows the operator to enter a reason for deleting a report
*/
bool audit_pwa_delete()
{
   bool success = false;
   MEAS_ID_TYPE  study_mode;

   study_mode = patient_get_study_mode();

   // If the audit option is not set, let the report object handle the delete
   if(!config_get_audit_option() || study_mode == MEAS_PWM_ID)
   {
      return true;
   }

   // Inform the operator they must enter a reason for deleting a report
   MsgBox(TNOTIFICATION,
            MSG_AUDIT,
            MSG_AUDIT_DELETE,
            LoadStr(MSG_AUDIT_DELETE));

   // Disable OnChange event to protect rewriting PWA
   frm_report_pwa->grd_report->DataSource->OnDataChange = NULL;

   // Call recalculate form
   if (meas_recalculate_show_form(frm_report_pwa,
                                    frm_report_pwa->report_pwa,
                                    frm_report_pwa->report_qry,
                                    frm_report_pwa->lbl_pname->Caption,
                                    AUDIT_DELETING, MEAS_AUDIT))
   {
      success = true;
   }

   // Restore OnChange event
   frm_report_pwa->grd_report->DataSource->OnDataChange = frm_report_pwa->record_changed;

   // Refresh grid and charts
   if (success)
   {
      frm_report_pwa->record_changed(frm_report_pwa, NULL);
   }
   return success;
}

/*---------------------------------------------------------------------------
// Displays the PWA audit trail
*/
bool audit_pwa_show()
{
   TADOQuery *pwa_audit_qry;
   TDataSource *pwa_audit_qry_dsrc;
   bool success = false;

   try
   {
      // Query the PWA Audit table
      Screen->Cursor = crHourGlass;
      pwa_audit_qry = dbmgr_setup_query(DBMGR_MEASURE_PWA_AUDIT_TABLE,
                                             DBMGR_QUERY_AUDIT,
                                             PATIENT_SYSTEM_ID,
                                             PATIENT_STUDY_ID,
                                             PATIENT_NO,
                                             MPW_DATETIME,
                                             frm_report_pwa->report_pwa->System_ID,
                                             frm_report_pwa->report_pwa->Study_ID,
                                             frm_report_pwa->report_pwa->Patient_No,
                                             frm_report_pwa->report_pwa->DateTime,
                                             MPWA_AUDIT_DATETIME);

      int NofRecords = (pwa_audit_qry != NULL ? pwa_audit_qry->RecordCount : 0);

      if (NofRecords > 0)
      {
         // Change the audit button and disable speed buttons
         emma_disable_speed_buttons();
         frm_report_pwa->bbtn_audit->Caption = AUDIT_REPORT_BUTTON_CAPTION;
         pwa_audit_qry_dsrc = dbmgr_get_data_source(DBMGR_MEASURE_PWA_AUDIT_QUERY, false);
         if (pwa_audit_qry_dsrc != NULL)
         {
            // Change the record and grid display
            pwa_audit_qry_dsrc->OnDataChange = frm_report_pwa->record_changed;
            pwa_audit_qry_dsrc->AutoEdit = false;
            frm_report_pwa->grd_report->DataSource = pwa_audit_qry_dsrc;

            frm_report_pwa->grd_report->Columns->Items[0]->FieldName = MPWA_AUDIT_DATETIME;
            frm_report_pwa->grd_report->Columns->Items[0]->Title->Caption = AUDIT_COLUMN_TITLE;
         }
         pwa_audit_qry->Last();
         if (frm_report_pwa->grd_report->Visible)
         {
            frm_report_pwa->grd_report->SetFocus();
            success = true;
         }
      }
      else
      {
         MsgBox(MSG_AUDIT_NO_REPORTS_TO_DISPLAY, SNOTIFICATION, MB_ICONINFORMATION);
      }
   }
   catch (Exception &exception)
   {
      ;
   }
   Screen->Cursor = crDefault;
   return success;
}

/*---------------------------------------------------------------------------
// Displays the PWA table
*/
void audit_pwa_hide()
{
   TDataSource *pwa_qry_dsrc;
   TDataSource *pwa_audit_qry_dsrc;

   pwa_audit_qry_dsrc = dbmgr_get_data_source(DBMGR_MEASURE_PWA_AUDIT_QUERY, false);
   if (pwa_audit_qry_dsrc != NULL)
   {
      pwa_qry_dsrc = dbmgr_get_data_source(DBMGR_MEASURE_PWA_QUERY, false);
      if (pwa_qry_dsrc != NULL)
      {
         // Change the audit button and enable speed buttons
         emma_enable_speed_buttons();
         frm_report_pwa->bbtn_audit->Caption = AUDIT_BUTTON_CAPTION;

         // Change the record and grid display
         pwa_audit_qry_dsrc->OnDataChange = NULL;
         frm_report_pwa->grd_report->DataSource = pwa_qry_dsrc;
         
         frm_report_pwa->grd_report->Columns->Items[0]->FieldName = MPW_DATETIME;
         frm_report_pwa->grd_report->Columns->Items[0]->Title->Caption = AUDIT_REPORT_TITLE;

         frm_report_pwa->record_changed(frm_report_pwa, NULL);
         
         if (frm_report_pwa->grd_report->Visible)
         {
            frm_report_pwa->grd_report->SetFocus();
         }
      }
   }
}

/*---------------------------------------------------------------------------
// Update the PWV object with audit data
*/
bool audit_update_pwv(TPWV *pwv_current, String reason)
{
   bool                 success = false;

   // If the audit option is not set, let PWA handle the update process
   if(!config_get_audit_option())
   {
      return true;
   }

   pwv_current->Reason = reason;

   // Validate new data and verify the operator's identity
   if (audit_pwv_validate_record(pwv_current))
   {
      if (security_show())
      {
         pwv_current->Operator = security_get_username();
         success = true;
      }
   }

   return success;
}

bool audit_pwv_validate_record(TPWV *pwv_current)
{
   bool valid = true;

   // Ensure the operator has entered a reason for any changes to the database
   if (pwv_current->Reason.Length() == 0)
   {
      MsgBox_show(TWARNING,
                    MSG_VALIDATION_ERROR,
                    LoadStr(MSG_AUDIT_CHECK_INPUT),
                    MSG_AUDIT_CHECK_INPUT, "");
      valid = false;
   }

   return (valid);
}

/*---------------------------------------------------------------------------
// Inserts a record into the PWV Audit trail if one does not exist already
*/
bool audit_pwv_insert(TPWV *pwv_current, TDataSet *pwv_dataset, AUDIT_MODE AuditMode)
{
   TDataSet             *pwv_audit_table;
   bool                 success = false;

   // If the audit option is not set, do not insert a record
   if(!config_get_audit_option())
   {
      return true;
   }

   // If this is the original record add it to the audit trail
   if (pwv_current->AuditFlag == AUDIT_ORIGINAL)
   {
      pwv_audit_table = dbmgr_get_dataset(DBMGR_MEASURE_PWV_AUDIT_TABLE, false);
      if (pwv_audit_table != NULL)
      {
         try
         {
            // Add audit data and copy to the Audit table
            pwv_dataset->FieldByName(MPWV_AUDIT_FLAG)->AsInteger = AUDIT_ORIGINAL;

            if (dbmgr_open(DBMGR_MEASURE_PWV_AUDIT_TABLE, false))
            {
               if (audit_copy_record(pwv_dataset, pwv_audit_table))
               {
                  pwv_audit_table->FieldByName(MPWV_AUDIT_DATETIME)->AsDateTime = pwv_dataset->FieldByName(MPW_DATETIME)->AsDateTime;
                  pwv_audit_table->Post();
                  pwv_current->AuditFlag = AUDIT_MODIFIED;
                  success = true;
               }
               dbmgr_close(DBMGR_MEASURE_PWV_AUDIT_TABLE, false);
            }
         }
         catch (Exception &exception)
         {
            MsgBox_show(TERROR,
                        MSG_DBREADWRITE_ERROR,
                        LoadStr(MSG_POST_ERROR),
                        MSG_POST_ERROR,
                        LoadStr(MSG_POST_ERROR) +GetCurrentMeasureDetails() +exception.Message);
            pwv_audit_table->Cancel();
         }
      }
   }
   else
   {
      success = true;
   }
   // Set the audit flag for the record in the PWV table
   if (AuditMode == AUDIT_DELETING)
   {
      pwv_current->AuditFlag = AUDIT_DELETED;
   }
   return success;
}

/*---------------------------------------------------------------------------
// Adds the edited or deleted record to the audit trail
*/
bool audit_pwv_edit(TDataSet *pwv_dataset)
{
   TDataSet             *pwv_audit_table;
   bool                 success = false;

   // If the audit option is not set, do not insert a record
   if(!config_get_audit_option())
   {
      return true;
   }

   pwv_audit_table = dbmgr_get_dataset(DBMGR_MEASURE_PWV_AUDIT_TABLE, false);
   if (pwv_audit_table != NULL)
   {
      try
      {
         // Copy to the audit table
         if (dbmgr_open(DBMGR_MEASURE_PWV_AUDIT_TABLE, false))
         {
            if (audit_copy_record(pwv_dataset, pwv_audit_table))
            {
               pwv_audit_table->FieldByName(MPWV_AUDIT_DATETIME)->AsDateTime = Now();
               pwv_audit_table->Post();
               success = true;
            }
            dbmgr_close(DBMGR_MEASURE_PWV_AUDIT_TABLE, false);
         }
      }
      catch (Exception &exception)
      {
         MsgBox_show(TERROR,
                        MSG_DBREADWRITE_ERROR,
                        LoadStr(MSG_POST_ERROR),
                        MSG_POST_ERROR,
                        LoadStr(MSG_POST_ERROR) +GetCurrentMeasureDetails() +exception.Message);
         pwv_audit_table->Cancel();
      }
   }
   return success;
}

/*---------------------------------------------------------------------------
// Allows the operator to enter a reason for deleting a report
*/
bool audit_pwv_delete()
{
   bool success = false;

   // If the audit option is not set, let the report object handle the delete
   if(!config_get_audit_option())
   {
      return true;
   }

   // Inform the operator they must enter a reason for deleting a report
   MsgBox(TNOTIFICATION,
            MSG_AUDIT,
            MSG_AUDIT_DELETE,
            LoadStr(MSG_AUDIT_DELETE));

   // Disable OnChange event to protect rewriting PWV
   frm_report_pwv->grd_report->DataSource->OnDataChange = NULL;

   // Call recalculate form
   if (meas_recalculate_pwv_show_form(frm_report_pwv,
                                    frm_report_pwv->report_pwv,
                                    frm_report_pwv->report_qry,
                                    frm_report_pwv->lbl_pname->Caption,
                                    AUDIT_DELETING, MEAS_AUDIT))
   {
      success = true;
   }

   // Restore OnChange event
   frm_report_pwv->grd_report->DataSource->OnDataChange = frm_report_pwv->record_changed;

   // Refresh grid and charts
   if (success)
   {
      frm_report_pwv->record_changed(frm_report_pwv, NULL);
   }
   return success;
}

/*---------------------------------------------------------------------------
// Displays the PWV audit trail
*/
bool audit_pwv_show()
{
   TADOQuery *pwv_audit_qry;
   TDataSource *pwv_audit_qry_dsrc;
   bool success = false;

   try
   {
      // Query the PWV Audit table
      Screen->Cursor = crHourGlass;
      pwv_audit_qry = dbmgr_setup_query(DBMGR_MEASURE_PWV_AUDIT_TABLE,
                                             DBMGR_QUERY_AUDIT,
                                             PATIENT_SYSTEM_ID,
                                             PATIENT_STUDY_ID,
                                             PATIENT_NO,
                                             MPW_DATETIME,
                                             frm_report_pwv->report_pwv->System_ID,
                                             frm_report_pwv->report_pwv->Study_ID,
                                             frm_report_pwv->report_pwv->Patient_No,
                                             frm_report_pwv->report_pwv->DateTime,
                                             MPWV_AUDIT_DATETIME);

      int NofRecords = (pwv_audit_qry != NULL ? pwv_audit_qry->RecordCount : 0);

      if (NofRecords > 0)
      {
         // Change the audit button and disable speed buttons
         emma_disable_speed_buttons();
         frm_report_pwv->bbtn_audit->Caption = AUDIT_REPORT_BUTTON_CAPTION;
         pwv_audit_qry_dsrc = dbmgr_get_data_source(DBMGR_MEASURE_PWV_AUDIT_QUERY, false);
         if (pwv_audit_qry_dsrc != NULL)
         {
            // Change the record and grid display
            pwv_audit_qry_dsrc->OnDataChange = frm_report_pwv->record_changed;
            pwv_audit_qry_dsrc->AutoEdit = false;
            frm_report_pwv->grd_report->DataSource = pwv_audit_qry_dsrc;
            //frm_report_pwv->nvg_report->DataSource = pwv_audit_qry_dsrc;

            frm_report_pwv->grd_report->Columns->Items[0]->FieldName = MPWV_AUDIT_DATETIME;
            frm_report_pwv->grd_report->Columns->Items[0]->Title->Caption = AUDIT_COLUMN_TITLE;
         }
         pwv_audit_qry->Last();
         if (frm_report_pwv->grd_report->Visible)
         {
            frm_report_pwv->grd_report->SetFocus();
            success = true;
         }
      }
      else
      {
         MsgBox(MSG_AUDIT_NO_REPORTS_TO_DISPLAY, SNOTIFICATION, MB_ICONINFORMATION);
      }
   }
   catch (Exception &exception)
   {
      ;
   }
   Screen->Cursor = crDefault;
   return success;
}

/*---------------------------------------------------------------------------
// Displays the PWV table
*/
void audit_pwv_hide()
{
   TDataSource *pwv_qry_dsrc;
   TDataSource *pwv_audit_qry_dsrc;

   pwv_audit_qry_dsrc = dbmgr_get_data_source(DBMGR_MEASURE_PWV_AUDIT_QUERY, false);
   if (pwv_audit_qry_dsrc != NULL)
   {
      pwv_qry_dsrc = dbmgr_get_data_source(DBMGR_MEASURE_PWV_QUERY, false);
      if (pwv_qry_dsrc != NULL)
      {
         // Change the audit button and enable speed buttons
         emma_enable_speed_buttons();
         frm_report_pwv->bbtn_audit->Caption = AUDIT_BUTTON_CAPTION;
         
         // Change the record and grid display
         pwv_audit_qry_dsrc->OnDataChange = NULL;
         frm_report_pwv->grd_report->DataSource = pwv_qry_dsrc;
         //frm_report_pwv->nvg_report->DataSource = pwv_qry_dsrc;

         frm_report_pwv->grd_report->Columns->Items[0]->FieldName = MPW_DATETIME;
         frm_report_pwv->grd_report->Columns->Items[0]->Title->Caption = AUDIT_REPORT_TITLE;

         frm_report_pwv->record_changed(frm_report_pwv, NULL);
         
         if (frm_report_pwv->grd_report->Visible)
         {
            frm_report_pwv->grd_report->SetFocus();
         }
      }
   }
}
