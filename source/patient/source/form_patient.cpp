#include <vcl.h>
#pragma hdrstop

#include <inc/std.h>
#include <dbmgr/pubserv.h>
#include <multdb/pubserv.h>
#include <meas/pubserv.h>
#include <config/pubserv.h>
#include <log/pubserv.h>
#include <capture/pubserv.h>
#include <scor/form_main.h>
#include <msg/pubserv.h>
#include <export/pubserv.h>
#include <patient/pubserv.h>
#include <interview/pubserv.h>
#include <cfr11/pubserv.h>
#include <comms/pubserv.h>
#include <emr/pubserv.h>
#include <scor/utils.h>
#include "form_welcome.h"
#include "form_patlist.h"
#include "form_patient.h"
#include "form_patlist_select.h"
#include "attrib.h"

#pragma package(smart_init)
#pragma link "TeeDraw3D"
#pragma resource "*.dfm"

Tfrm_patient *frm_patient;
MEAS_ID_TYPE patient_mode;
bool        patient_audit_mode;
   
//---------------------------------------------------------------------------
VAR_EXPORT  PATIENT_RECORD_TYPE  patient_active;
VAR_EXPORT  COUNT                patient_nof_measure;
bool                             patient_initialised;
bool                             patient_post_message;

//const String PATIENT_NAMES_EDIT_MASK = ">l<lllllllllllllllllllllll;0; ";
const String PATIENT_NAMES_EDIT_MASK = ">l<<>ccccccccccccccccccccccccc;0; ";
const String PATIENT_DATE_TIME_FORMAT = "dd mmm yyyy, hh:nn";
const String PATIENT_TABLE_NAME = "PATIENT";
const String PATIENT_INIT_STUDYID = "DATA";
const String PATIENT_COLUMN_FAMNAME = "Family Name";
const String PATIENT_COLUMN_PATID = "Patient ID";
const String PATIENT_COLUMN_DOB = "Date Of Birth";
const String PATIENT_OBJECT_NAME = "Patient Object ";

static Patient_Data_Event_Class  data_event;

String PATIENT_INIT_DATE;
String PATIENT_MIN_DOB;
//---------------------------------------------------------------------------


bool patient_initialise(void)
{
   patient_initialised = true;
   PATIENT_MIN_DOB = emma_build_country_date("01", "01", "1850");
   PATIENT_INIT_DATE = emma_build_country_date("01", "01", "1850");

   try
   {
      frm_patient = new Tfrm_patient(emma_get_main_form_pointer());
   }
   catch (Exception &exception)
   {
      MsgBox(PATIENT_OBJECT_NAME +SOBJECTINIT, MSG_SYSTEM_ERROR);
      log_write(SFATAL +PATIENT_OBJECT_NAME +SOBJECTINIT +exception.Message);
      patient_initialised = false;
   }

   patient_reset_active_record();
   if (frm_patient == NULL)
   {
      patient_initialised = false;
   }
   patient_post_message = true;
   return (patient_initialised);
}

void patient_destroy(void)
{
   if (frm_patient != NULL)
   {
      frm_patient->set_database_status();
   }
   patient_initialised = false;
}

bool patient_can_close(void)
{
   TDataSet     *patient_table;
   TDataSource  *dsrc_pat;
   bool         can_close = true;

   if (frm_patient != NULL && frm_patient->Visible)
   {
      if (dbmgr_is_open(DBMGR_PATIENT_TABLE, false))
      {
         dsrc_pat = dbmgr_get_data_source(DBMGR_PATIENT_TABLE, false);
         patient_table = dbmgr_get_dataset(DBMGR_PATIENT_TABLE, false);
         if (dsrc_pat != NULL)
         {
            if (dsrc_pat->State == dsEdit || dsrc_pat->State == dsInsert)
            {
               if (frm_patient->pnl_data->Enabled)
               {
                  frm_patient->pgctrl_int->ActivePage = frm_patient->tbsht_details;
                  //frm_patient->edt_pat_oname->SetFocus();
               }
               if (!patient_validate_record(patient_table))
               {
                  can_close = false;
               }
            }
         }
      }
   }
   return (can_close);
}

void patient_display_idle(bool is_idle)
{
   //frm_patient->pnl_data_area->Visible = !is_idle;
   frm_patient->Visible = !is_idle;
   if (is_idle)
   {
      security_lock_workstation();
   }
}

void patient_listing_preview(bool is_preview)
{
   if (MsgBox(MSG_PATIENT_LISTING, SCONFIRMATION,
              MB_YESNO | MB_ICONQUESTION) == ID_YES)
   {
      frm_patlist = new Tfrm_patlist(emma_get_main_form_pointer());
      if (frm_patlist != NULL)
      {
         emma_disable_speed_buttons();
         if (frm_patlist->report_patlist_setup())
         {
            if (is_preview)
            {
               frm_patlist->qckrp_pat_list->Preview();
            }
            else
            {
               frm_patlist->qckrp_pat_list->Print();
            }
            frm_patlist->report_patlist_cleanup();
         }
         else
         {
            ;
         }
         emma_enable_speed_buttons();
         delete frm_patlist;
         frm_patlist = NULL;
      }
   }
}

AnsiString patient_get_table_name(void)
{
   AnsiString S;
   S = PATIENT_TABLE_NAME;
   return S;
}

void patient_update_count(void)
{
   TDataSet *patient_table;

   patient_table = dbmgr_get_dataset(DBMGR_PATIENT_TABLE, false);
   if (patient_table != NULL)
   {
      if (frm_patient != NULL)
      {
         frm_patient->lbl_nof_patients->Caption = " Patients: " + IntToStr(patient_table->RecordCount);
      }
   }
}

void patient_update_active_database(void)
{
   if (frm_patient->Visible)
   {
      frm_patient->lbl_active_dbname->Caption = multdb_get_active_name();
   }
}

UCOUNT patient_get_count(void)
{
   TDataSet *patient_table;
   UCOUNT patient_count = 0;;

   patient_table = dbmgr_get_dataset(DBMGR_PATIENT_TABLE, false);
   if (patient_table != NULL)
   {
      if (frm_patient != NULL)
      {
         patient_count = (UCOUNT) patient_table->RecordCount;
      }
   }
   return patient_count;
}


bool patient_get_export_titles(String &export_title)
{
   export_title = export_title + "System ID" + "\t" +
      "Database ID" + "\t" +
      "Patient Number" + "\t" +
      "Surname" + "\t" +
      "First Name" + "\t" +
      "Sex" + "\t" +
      "Date Of Birth" + "\t" +
      "Patient ID" +"\t" +
      "Patient Code" + "\t" +
      "Patient Notes" + "\t";
   return true;
}

bool patient_get_export_data(String &export_data)
{
   if (!patient_active.number)
   {
      return false;
   }
   export_data =  export_data + patient_active.system_id + "\t" +
      patient_active.study_id + "\t" +
      IntToStr(patient_active.number) + "\t" +
      patient_active.surname + "\t" +
      patient_active.first_name + "\t" +
      patient_active.sex + "\t" +
      patient_active.dob.DateTimeString() + "\t" +
      patient_active.id + "\t" +
      patient_active.code + "\t" +
      MsgBox_ReplaceCarriage(patient_active.notes) + "\t";

   return true;
}
unsigned long patient_assign_new_number(void)
{
   long           pat_num;
   TDataSet       *patient_table;
   AnsiString     S;
   AnsiString     sysid_last;
   AnsiString     sysid_first;
   AnsiString     this_sysid;
   TADOQuery         *qry_next_num;
   AnsiString     studyid_first;
   AnsiString     studyid_last;
   AnsiString     this_studyid;
   bool           use_query;


   pat_num = -1;
   use_query = false;
   patient_table = dbmgr_get_dataset(DBMGR_PATIENT_TABLE, false);
   if (patient_table != NULL)
   {
      S = PATIENT_SYSTEM_ID +  ";" + PATIENT_STUDY_ID + ";" + PATIENT_NO;
      dbmgr_select_index(DBMGR_PATIENT_TABLE, S);
      if (patient_table->RecordCount > 0)
      {
         patient_table->First();
         sysid_first = patient_table->FieldByName(PATIENT_SYSTEM_ID)->AsString;
         studyid_first = patient_table->FieldByName(PATIENT_STUDY_ID)->AsString;
         patient_table->Last();
         sysid_last = patient_table->FieldByName(PATIENT_SYSTEM_ID)->AsString;
         studyid_first = patient_table->FieldByName(PATIENT_STUDY_ID)->AsString;
         this_sysid = config_get_system_id();
         this_studyid = multdb_get_active_name();
         if (sysid_last == sysid_first)
         {
            if ((sysid_last == this_sysid) && (studyid_last == this_studyid))
            {
               pat_num = patient_table->FieldByName(PATIENT_NO)->AsInteger;
            }
            else
            {
               use_query = true;
            }
         }
         else
         {
            use_query = true;
         }

         if (use_query)
         {
            qry_next_num = dbmgr_setup_query(DBMGR_PATIENT_TABLE,
                                             DBMGR_QUERY_PATIENT_NUMBER,
                                             PATIENT_SYSTEM_ID,
                                             PATIENT_STUDY_ID,
                                             "",
                                             this_sysid,
                                             this_studyid,
                                             "",
                                             PATIENT_NO);
            if (qry_next_num != NULL)
            {
               if (qry_next_num->RecordCount)
               {
                  qry_next_num->Last();
                  pat_num = qry_next_num->FieldByName(PATIENT_NO)->AsInteger;
               }
               else
               {
                  pat_num = 0;
               }
               qry_next_num->Close();
            }
         }
      }
      else
      {
         pat_num = 0;
      }
   }
   ++pat_num;
   return (pat_num);
}

void patient_enable_post_message(bool enable)
{
   patient_post_message = enable;
}

void patient_enable_database_events(bool enable, bool enable_change)
{
   TDataSet     *patient_table;
   TDataSource  *dsrc_pat;

   // In audit mode enable Patient Audit Query events,
   // Otherwise enable Patient Table events
   if (patient_audit_mode)
   {
      dsrc_pat = dbmgr_get_data_source(DBMGR_PATIENT_AUDIT_QUERY, false);
      patient_table = dbmgr_get_dataset(DBMGR_PATIENT_AUDIT_QUERY, false);
   }
   else
   {
      dsrc_pat = dbmgr_get_data_source(DBMGR_PATIENT_TABLE, false);
      patient_table = dbmgr_get_dataset(DBMGR_PATIENT_TABLE, false);
   }

   if (patient_table == NULL || dsrc_pat == NULL || frm_patient == NULL)
   {
      return;
   }

   if (enable)
   {
      frm_patient->grd_pat->DataSource = dsrc_pat;
      frm_patient->edt_pat_pid->DataSource = dsrc_pat;
      frm_patient->dbtxt_sysid->DataSource = dsrc_pat;
      frm_patient->dbtxt_dbid->DataSource = dsrc_pat;
      frm_patient->dbtxt_operator->DataSource = dsrc_pat;
      frm_patient->edt_pat_surname->DataSource = dsrc_pat;
      frm_patient->edt_pat_fname->DataSource = dsrc_pat;
      frm_patient->edt_pat_oname->DataSource = dsrc_pat;
      frm_patient->edt_pat_code->DataSource = dsrc_pat;
      frm_patient->mm_pat_notes->DataSource = dsrc_pat;
      frm_patient->edt_pat_street->DataSource = dsrc_pat;
      frm_patient->edt_pat_suburb->DataSource = dsrc_pat;
      frm_patient->edt_pat_state->DataSource = dsrc_pat;
      frm_patient->edt_pat_country->DataSource = dsrc_pat;
      frm_patient->edt_pat_pcode->DataSource = dsrc_pat;
      frm_patient->edt_pat_phone->DataSource = dsrc_pat;
      frm_patient->cmbx_pat_sex->DataSource = dsrc_pat;
      frm_patient->mm_pat_reason->DataSource = dsrc_pat;
      //frm_patient->dbnvg_pat->DataSource = dsrc_pat;

      // In audit mode there is no state change or need to validate records
      if (patient_audit_mode)
      {
         dsrc_pat->OnDataChange = data_event.record_changed;
         dsrc_pat->OnStateChange = NULL;
         dsrc_pat->AutoEdit = false;
      }
      else
      {
         dsrc_pat->OnDataChange = data_event.record_changed;
         dsrc_pat->OnStateChange = data_event.state_changed;
         patient_table->BeforePost = data_event.validate_record;
      }
   }
   else
   {
      if (enable_change)
      {
         dsrc_pat->OnDataChange = data_event.record_changed;
         dsrc_pat->OnStateChange = NULL;
         patient_table->BeforePost = NULL;
      }
      else
      {
         dsrc_pat->OnDataChange = NULL;
         dsrc_pat->OnStateChange = NULL;
         patient_table->BeforePost = NULL;
      }
      frm_patient->edt_pat_pid->DataSource = NULL;
      frm_patient->dbtxt_sysid->DataSource = NULL;
      frm_patient->dbtxt_dbid->DataSource = NULL;
      frm_patient->dbtxt_operator->DataSource = NULL;
      frm_patient->edt_pat_surname->DataSource = NULL;
      frm_patient->edt_pat_fname->DataSource = NULL;
      frm_patient->edt_pat_oname->DataSource = NULL;
      frm_patient->edt_pat_code->DataSource = NULL;
      frm_patient->mm_pat_notes->DataSource = NULL;
      frm_patient->edt_pat_street->DataSource = NULL;
      frm_patient->edt_pat_suburb->DataSource = NULL;
      frm_patient->edt_pat_state->DataSource = NULL;
      frm_patient->edt_pat_country->DataSource = NULL;
      frm_patient->edt_pat_pcode->DataSource = NULL;
      frm_patient->edt_pat_phone->DataSource = NULL;
      frm_patient->cmbx_pat_sex->DataSource = NULL;
      frm_patient->mm_pat_reason->DataSource = NULL;
      //frm_patient->dbnvg_pat->DataSource = NULL;
   }
}

void patient_reset_active_record(void)
{
   patient_active.system_id = PATIENT_INIT_SYSTEMID;
   patient_active.number = 0;
   patient_active.study_id = PATIENT_INIT_STUDYID;
   patient_active.id = "";
   patient_active.surname = "";
   patient_active.first_name = "";
   patient_active.other_name;
   patient_active.sex = "";
   patient_active.dob = StrToDate(PATIENT_INIT_DATE);
   patient_active.age = "";
   patient_active.street = "";
   patient_active.suburb = "";
   patient_active.state = "";
   patient_active.country = "";
   patient_active.phone = "";
   patient_active.pcode = "";
   patient_active.code = "";
   patient_active.notes = "";
   patient_active.profile = "";
   patient_active.audit_change = Now();
   patient_active.operator_name = "";
   patient_active.reason = "";
   patient_active.audit_flag = AUDIT_ORIGINAL;
   patient_nof_measure = PATIENT_RESET_MEAS_NUM;

   patient_mode = MEAS_PWA_ID;
}

String patient_get_error_str(void)
{
   String err_str = " ";

   err_str = err_str +patient_active.study_id +", " +IntToStr(patient_active.number) +", " +patient_active.surname +". ";
   return (err_str);
}

Child_Form *patient_get_form_pointer(void)
{
   return (frm_patient);
}

void  patient_show(void)
{
   if (frm_patient != NULL)
   {
      frm_patient->Show();
   }
}

void patient_update_measurement_count(void)
{
   TADOQuery      *qry_meas;
   DBMGR_ID_TYPE  table_id;
   MEAS_ID_TYPE   meas_id;


   if (patient_active.number && (patient_nof_measure == PATIENT_RESET_MEAS_NUM))
   {
      meas_id = patient_get_study_mode();
      switch (meas_id)
      {
         case MEAS_PWA_ID:
            table_id = DBMGR_MEASURE_PWA_TABLE;
            break;
         case MEAS_PWV_ID:
            table_id = DBMGR_MEASURE_PWV_TABLE;
            break;
         case MEAS_PWM_ID:
            table_id = DBMGR_MEASURE_PWM_SESSION_TABLE;
            break;
         case MEAS_HRV_ID:
            table_id = DBMGR_MEASURE_HRV_TABLE;
            break;
         default:
            break;
      }

      qry_meas = dbmgr_setup_query(table_id,
                                   DBMGR_QUERY_KEY,
                                   PATIENT_SYSTEM_ID,
                                   PATIENT_STUDY_ID,
                                   PATIENT_NO,
                                   patient_active.system_id,
                                   patient_active.study_id,
                                   IntToStr(patient_active.number));
      if (qry_meas != NULL)
      {
         patient_nof_measure = (short int) qry_meas->RecordCount;
         qry_meas->Close();
      }
      else
      {
         patient_nof_measure = PATIENT_RESET_MEAS_NUM;
      }
   }
}

void patient_update_measurement_count(COUNT nof_measures)
{
   if (patient_active.number)
   {
      patient_nof_measure = (COUNT)nof_measures;
   }
}

bool patient_get(PATIENT_RECORD_TYPE *patient)
{
   patient->system_id = patient_active.system_id;
   patient->number = patient_active.number;
   patient->study_id = patient_active.study_id;
   patient->id = patient_active.id;
   patient->surname = patient_active.surname;
   patient->first_name = patient_active.first_name;
   patient->other_name = patient_active.other_name;
   patient->sex = patient_active.sex;
   patient->dob = patient_active.dob;
   patient->age = patient_active.age;
   patient->street = patient_active.street;
   patient->suburb = patient_active.suburb;
   patient->state =  patient_active.state;
   patient->country = patient_active.country;
   patient->phone = patient_active.phone;
   patient->pcode = patient_active.pcode;
   patient->code = patient_active.code;
   patient->notes = patient_active.notes;
   patient->profile = patient_active.profile;
   patient->audit_change = patient_active.audit_change;
   patient->operator_name = patient_active.operator_name;
   patient->reason = patient_active.reason;
   patient->audit_flag = patient_active.audit_flag;
   return true;
}

bool patient_set(PATIENT_RECORD_TYPE *patient)
{
   patient_active.system_id = patient->system_id;
   patient_active.number = patient->number;
   patient_active.study_id = patient->study_id;
   patient_active.id = patient->id;
   patient_active.surname = patient->surname;
   patient_active.first_name = patient->first_name;
   patient_active.other_name = patient->other_name;
   patient_active.sex = patient->sex;
   patient_active.dob = patient->dob;
   patient_active.age = patient->age;
   patient_active.street = patient->street;
   patient_active.suburb = patient->suburb;
   patient_active.state =  patient->state;
   patient_active.country = patient->country;
   patient_active.phone = patient->phone;
   patient_active.pcode = patient->pcode;
   patient_active.code = patient->code;
   patient_active.notes = patient->notes;
   patient_active.profile = patient->profile;
   patient_active.audit_change = patient->audit_change;
   patient_active.operator_name = patient->operator_name;
   patient_active.reason = patient->reason;
   patient_active.audit_flag = patient->audit_flag;
   return true;
}

bool patient_set(AnsiString     system_id,
                 AnsiString     study_id,
                 unsigned long  pat_no)
{
   TDataSet        *patient_table;
   TLocateOptions  Opts;
   AnsiString      index;
   bool            status = false;

   if (system_id == patient_active.system_id &&
       study_id == patient_active.study_id &&
       pat_no == patient_active.number)
   {
      status = true;
   }
   else
   {
      Opts.Clear();
      Opts << loPartialKey;

      patient_table = dbmgr_get_dataset(DBMGR_PATIENT_TABLE, false);

      Variant locvalues[3];
      locvalues[0] = Variant(system_id);
      locvalues[1] = Variant(study_id);
      locvalues[2] = Variant(pat_no);

      if (patient_table != NULL)
      {
         index = PATIENT_SYSTEM_ID +  ";" + PATIENT_STUDY_ID + ";" + PATIENT_NO;
         try
         {
            if (patient_table->Locate(index,
                                      VarArrayOf(locvalues, 2),
                                      Opts))                     
            {
               status = true;
            }
         }
         catch (Exception& exception)
         {
            log_write(SEXCEPTION +exception.Message);
         }
      }
   }
   return (status);
}

bool patient_populate_record(PATIENT_RECORD_TYPE *patient, TADOQuery *qry)
{
   TDateTime    today;
   bool populated = false;

   if (qry != NULL && qry->RecordCount)
   {
      patient->system_id = qry->FieldByName(PATIENT_SYSTEM_ID)->AsString;
      patient->number = (PATIENT_NUMBER_TYPE)qry->FieldByName(PATIENT_NO)->AsInteger;
      patient->study_id = qry->FieldByName(PATIENT_STUDY_ID)->AsString;
      patient->id = qry->FieldByName(PATIENT_ID)->AsString;
      patient->surname = qry->FieldByName(PATIENT_SURNAME)->AsString;
      patient->first_name = qry->FieldByName(PATIENT_FIRST_NAME)->AsString;
      patient->other_name = qry->FieldByName(PATIENT_OTHER_NAME)->AsString;
      patient->sex = qry->FieldByName(PATIENT_SEX)->AsString;
      patient->dob = qry->FieldByName(PATIENT_DOB)->AsDateTime;

      today = Date();

      patient->age = IntToStr(patient_get_age_at_date(today));

      patient->street = qry->FieldByName(PATIENT_STREET)->AsString;
      patient->suburb = qry->FieldByName(PATIENT_SUBURB)->AsString;
      patient->state = qry->FieldByName(PATIENT_STATE)->AsString;
      patient->country = qry->FieldByName(PATIENT_COUNTRY)->AsString;
      patient->phone = qry->FieldByName(PATIENT_PHONE)->AsString;
      patient->pcode = qry->FieldByName(PATIENT_PCODE)->AsString;
      patient->code = qry->FieldByName(PATIENT_CODE)->AsString;
      patient->notes = qry->FieldByName(PATIENT_NOTES)->AsString;
      patient->operator_name = qry->FieldByName(PATIENT_AUDIT_OPERATOR)->AsString;
      patient->reason = qry->FieldByName(PATIENT_AUDIT_REASON)->AsString;
      patient->audit_flag = (AUDIT_FLAG_TYPE)qry->FieldByName(PATIENT_AUDIT_FLAG)->AsInteger;
      if (qry->FindField(PATIENT_AUDIT_DATETIME)!=NULL)
      {
         patient->audit_change = qry->FieldByName(PATIENT_AUDIT_DATETIME)->AsDateTime;
      }
      populated = true;
   }
   return populated;
}

PATIENT_NUMBER_TYPE patient_get_number(void)
{

  return (patient_active.number);
}

AnsiString patient_get_age(void)
{
  return (patient_active.age);
}

bool patient_is_male(void)
{
   bool is_male = false;
   if (patient_active.sex == "MALE")
   {
      is_male = true;
   }
   return (is_male);
}


UCOUNT patient_get_age_at_date(TDateTime the_date)
{
   UCOUNT  year_dob;
   UCOUNT  month_dob;
   UCOUNT  day_dob;
   UCOUNT  year_date;
   UCOUNT  month_date;
   UCOUNT  day_date;
   COUNT   age_at_date = 0;


   if (patient_active.number)
   {
      patient_active.dob.DecodeDate(&year_dob,
                                    &month_dob,
                                    &day_dob);
      the_date.DecodeDate(&year_date,
                          &month_date,
                          &day_date);
      age_at_date = (COUNT)(year_date  - year_dob);
      if (age_at_date < 0)
      {
         age_at_date = 0;
      }
      if (age_at_date)
      {
         if (month_dob > month_date)
         {
            age_at_date = age_at_date - 1;
         }
      }
   }
   return ((UCOUNT)(age_at_date));
}

AnsiString patient_get_study_id(void)
{
  return (patient_active.study_id);
}

AnsiString patient_get_system_id(void)
{
  return (patient_active.system_id);
}

UCOUNT  patient_get_nof_measurements(void)
{
   UCOUNT            nof_measure = 0;
   TADOQuery         *qry_meas;
   DBMGR_ID_TYPE     table_id;
   MEAS_ID_TYPE      meas_id;

   if (patient_active.number)
   {
      if (patient_nof_measure == PATIENT_RESET_MEAS_NUM)
      {
         meas_id = patient_get_study_mode();
         switch (meas_id)
         {
            case MEAS_PWA_ID:
               table_id = DBMGR_MEASURE_PWA_TABLE;
               break;
            case MEAS_PWV_ID:
               table_id = DBMGR_MEASURE_PWV_TABLE;
               break;
            case MEAS_PWM_ID:
               table_id = DBMGR_MEASURE_PWM_SESSION_TABLE;
               break;
            case MEAS_HRV_ID:
               table_id = DBMGR_MEASURE_HRV_TABLE;
               break;
            default:
               break;
         }
         qry_meas = dbmgr_setup_query(table_id,
                                      DBMGR_QUERY_KEY,
                                      PATIENT_SYSTEM_ID,
                                      PATIENT_STUDY_ID,
                                      PATIENT_NO,
                                      patient_active.system_id,
                                      patient_active.study_id,
                                      IntToStr(patient_active.number));

         if (qry_meas != NULL)
         {
            nof_measure = (short int) qry_meas->RecordCount;
            qry_meas->Close();
         }
         patient_nof_measure = nof_measure;
      }
      else
      {
         nof_measure = patient_nof_measure;
      }
   }
   return nof_measure;
}

AnsiString patient_get_name(void)
{
   AnsiString patient_name;
   patient_name = patient_active.surname + ", " +
      patient_active.first_name + " " + patient_active.other_name;
   return (patient_name);
}

void __fastcall Patient_Data_Event_Class::validate_record(TDataSet *DataSet)
{
   TADOTable      *patient_table;
   TDataSource *dsrc;
   AnsiString  S;

   patient_table = dynamic_cast<TADOTable *>(DataSet);

   dsrc = dbmgr_get_data_source(DBMGR_PATIENT_TABLE, false);
   if (dsrc != NULL)
   {
      if (dsrc->State == dsInsert)
      {
         S = "Added Patient " + patient_table->FieldByName(PATIENT_NO)->AsString;
         // If the hardware configuration is unknown, request the module string
         if (comms_get_modes_string() == CONFIG_NO_OPTION_STRING)
         {
            if (comms_is_module_available())
            {
               if (comms_request_hwconfig())
               {
                  S = S + " " + comms_get_emod_string() + " - " + comms_get_modes_string();
               }
            }
         }
         else
         {
            S = S + " " + comms_get_emod_string() + " - " + comms_get_modes_string();
         }
         log_write(S);
      }
   }
}

bool patient_validate_record(TDataSet *tbl)
{
   TDateTime min_dob;
   bool valid = true;
   String index;

   if (tbl == NULL)
   {
      valid = false;
   }
   else
   {
      if (tbl->FieldByName(PATIENT_SURNAME)->AsString.Length() == 0)
      {
         valid = false;
         frm_patient->edt_pat_surname->SetFocus();
      }
      else if (tbl->FieldByName(PATIENT_FIRST_NAME)->AsString.Length() == 0)
      {
         frm_patient->edt_pat_fname->SetFocus();
         valid = false;
      }
      else if (tbl->FieldByName(PATIENT_SEX)->AsString.Length() == 0)
      {
         frm_patient->cmbx_pat_sex->SetFocus();
         valid = false;
      }
      else if (tbl->FieldByName(PATIENT_DOB)->AsString.Length() == 0)
      {
         frm_patient->dtpck_pat_dob->SetFocus();
         valid = false;
      }
   }
   if (!valid)
   {
      MsgBox(MSG_CHECK_INPUT, SVALIDATION, MB_ICONEXCLAMATION);
   }
   else
   {
      // Check for a valid DOB
      min_dob = StrToDate(PATIENT_MIN_DOB);
      if (frm_patient->dtpck_pat_dob->DateTime <= min_dob)
      {
         MsgBox(MSG_OLD_PATIENT, SWARNING, MB_ICONEXCLAMATION);
         frm_patient->dtpck_pat_dob->SetFocus();
         valid = false;
      }
   }

   // Check age and show warning if patient is too young
   UCOUNT lAge = patient_get_age_at_date(Now());
   if (lAge <= PATIENT_YOUNG_AGE)
   {
      MsgBox(MSG_YOUNG_PATIENT, SWARNING, MB_ICONEXCLAMATION);
   }
   return (valid);
}

void __fastcall Patient_Data_Event_Class::validate_field(TField *Field)
{
  // Maybe later
}

void __fastcall Patient_Data_Event_Class::record_changed(TObject *Sender,
                                                         TField  *Field)
{
   TDataSet    *table;
   AnsiString  S;
   TDateTime   today = TDateTime::CurrentDate();
   TDataSource *dsrc_pat;

   dsrc_pat = dbmgr_get_data_source(DBMGR_PATIENT_TABLE, false);

   // In audit mode use the Patient Audit Query dataset,
   // Otherwise use the Patient table
   if (patient_audit_mode)
   {
      table = dbmgr_get_dataset(DBMGR_PATIENT_AUDIT_QUERY, false);
   }
   else
   {
      table = dbmgr_get_dataset(DBMGR_PATIENT_TABLE, false);
   }

   if (table == NULL)
   {
      return;
   }
   S = table->FieldByName(PATIENT_SYSTEM_ID)->AsString;

   if (S != patient_active.system_id)
   {
      patient_nof_measure = PATIENT_RESET_MEAS_NUM;
   }

   S = table->FieldByName(PATIENT_STUDY_ID)->AsString;
   if (S != patient_active.study_id)
   {
      patient_nof_measure = PATIENT_RESET_MEAS_NUM;
   }

   if (patient_active.number != (unsigned int) table->FieldByName(PATIENT_NO)->AsInteger)
   {
      patient_nof_measure = PATIENT_RESET_MEAS_NUM;
   }
   patient_active.system_id = table->FieldByName(PATIENT_SYSTEM_ID)->AsString;
   patient_active.number = table->FieldByName(PATIENT_NO)->AsInteger;
   patient_active.study_id = table->FieldByName(PATIENT_STUDY_ID)->AsString;
   patient_active.id = table->FieldByName(PATIENT_ID)->AsString;
   patient_active.surname = table->FieldByName(PATIENT_SURNAME)->AsString;
   patient_active.first_name = table->FieldByName(PATIENT_FIRST_NAME)->AsString;
   patient_active.other_name = table->FieldByName(PATIENT_OTHER_NAME)->AsString;
   patient_active.sex = table->FieldByName(PATIENT_SEX)->AsString;
   patient_active.street = table->FieldByName(PATIENT_STREET)->AsString;
   patient_active.suburb = table->FieldByName(PATIENT_SUBURB)->AsString;
   patient_active.country = table->FieldByName(PATIENT_COUNTRY)->AsString;
   patient_active.state = table->FieldByName(PATIENT_STATE)->AsString;
   patient_active.pcode = table->FieldByName(PATIENT_PCODE)->AsString;
   patient_active.phone = table->FieldByName(PATIENT_PHONE)->AsString;
   patient_active.code = table->FieldByName(PATIENT_CODE)->AsString;
   patient_active.notes = table->FieldByName(PATIENT_NOTES)->AsString;
   patient_active.operator_name = table->FieldByName(PATIENT_AUDIT_OPERATOR)->AsString;
   patient_active.reason = table->FieldByName(PATIENT_AUDIT_REASON)->AsString;
   patient_active.audit_flag = (AUDIT_FLAG_TYPE)table->FieldByName(PATIENT_AUDIT_FLAG)->AsInteger;
   if (table->FindField(PATIENT_AUDIT_DATETIME)!=NULL)
   {
      patient_active.audit_change = table->FieldByName(PATIENT_AUDIT_DATETIME)->AsDateTime;
   }

   // If the audit option is set, the display will depend on the audit flag
   if (config_get_audit_option())
   {
      S =  patient_active.operator_name;
      if (S.Length())
      {
         frm_patient->lbl_operator->Visible = true;
         frm_patient->dbtxt_operator->Visible = true;
      }
      else
      {
         frm_patient->lbl_operator->Visible = false;
         frm_patient->dbtxt_operator->Visible = false;
      }
      
      switch (patient_active.audit_flag)
      {
         // Original records can be edited and do not have an audit trail
         case AUDIT_ORIGINAL:
            frm_patient->lbl_operator->Caption = AUDIT_ORIGINAL_CAPTION;
            frm_patient->lbl_operator->Font->Color = sphygmocor_navy;
            frm_patient->dbtxt_operator->Font->Color = sphygmocor_navy;
            frm_patient->bbtn_pat_audit->Visible = false;
            frm_patient->bbtn_pat_edit->Enabled = true;
            state_changed(Sender);
            break;
         // Modified records can be edited and have an audit trail
         case AUDIT_MODIFIED:
            frm_patient->lbl_operator->Caption = AUDIT_MODIFIED_CAPTION;
            frm_patient->lbl_operator->Font->Color = sphygmocor_orange;
            frm_patient->dbtxt_operator->Font->Color = sphygmocor_orange;
            frm_patient->bbtn_pat_audit->Visible = true;
            frm_patient->bbtn_pat_edit->Enabled = true;
            state_changed(Sender);
            break;
         // Deleted records cannot be edited, deleted, exported nor can their
         // reports be viewed. The audit trail is enabled though
         case AUDIT_DELETED:
            frm_patient->lbl_operator->Caption = AUDIT_DELETED_CAPTION;
            frm_patient->lbl_operator->Font->Color = sphygmocor_red;
            frm_patient->dbtxt_operator->Font->Color = sphygmocor_red;
            frm_patient->bbtn_pat_audit->Visible = true;
            if (frm_patient->edit_mode)
            {
               frm_patient->edit_mode = false;
               frm_patient->bbtn_pat_insert->Enabled = true;
               frm_patient->bbtn_search_insert->Enabled = true;
               frm_patient->bbtn_pat_delete->Enabled = false;
               dsrc_pat->AutoEdit = false;
               frm_patient->bbtn_pat_edit->Caption = "&Edit";
               emma_display_statusbar_message("", "", sphygmocor_white);
               frm_patient->pnl_data->Enabled = false;
               frm_patient->pnl_questions->Enabled = false;
               frm_patient->bbtn_done->Enabled = false;
               if (frm_patient->pgctrl_pat->ActivePage == frm_patient->tbsht_pat_grid)
               {
                  frm_patient->grd_pat->SetFocus();
               }
            }
            emma_disable_speed_buttons();
            frm_main->mnu_export->Enabled = false;
            frm_main->mnu_batch_print->Enabled = false;
            frm_main->mnu_export_database->Enabled = false;
            frm_patient->bbtn_pat_edit->Enabled = false;
            break;
      }

      // In audit mode, the audit button returns to patient mode and records
      // cannot be edited
      if (patient_audit_mode)
      {
         frm_patient->bbtn_pat_audit->Visible = true;
         frm_patient->bbtn_pat_edit->Enabled = false;
      }
   }
   else
   {
      // If the audit option is not set, the operator display is hidden
      frm_patient->lbl_operator->Visible = false;
      frm_patient->dbtxt_operator->Visible = false;
      frm_patient->bbtn_pat_audit->Visible = false;
   }

   S =  table->FieldByName(PATIENT_DOB)->AsString;
   if (S.Length())
   {
      patient_active.dob = table->FieldByName(PATIENT_DOB)->AsDateTime;
      frm_patient->dtpck_pat_dob->Date = patient_active.dob;

      patient_active.age = IntToStr(patient_get_age_at_date(today));
   }

   // PM V9 CR
   // Check if this is the EMR patient and can they be edited
   if (emr_get_enabled())
   {
      if (!emr_edit_active_patient())
      {
         // If in Edit mode, change to Browse mode
         if (frm_patient->edit_mode)
         {
            frm_patient->edit_mode = false;
            frm_patient->bbtn_pat_insert->Enabled = true;
            frm_patient->bbtn_search_insert->Enabled = true;
            frm_patient->bbtn_pat_delete->Enabled = false;
            dsrc_pat->AutoEdit = false;
            frm_patient->bbtn_pat_edit->Caption = "&Edit";
            emma_display_statusbar_message("", "", sphygmocor_white);
            frm_patient->pnl_data->Enabled = false;
            frm_patient->pnl_questions->Enabled = false;
            frm_patient->bbtn_done->Enabled = false;
            if (frm_patient->pgctrl_pat->ActivePage == frm_patient->tbsht_pat_grid)
            {
               frm_patient->grd_pat->SetFocus();
            }
         }
         frm_patient->bbtn_pat_edit->Enabled = false;
      }
      else
      {
         // Because you're in EMR mode, the edit button may have been disabled
         // So enable it if not in Edit mode
         if (!frm_patient->edit_mode)
         {
            frm_patient->bbtn_pat_edit->Enabled = true;
         }
      }
   }
}

void __fastcall Patient_Data_Event_Class::state_changed(TObject *Sender)
{
   TDataSource *patient_dsrc;
   MEAS_ID_TYPE  study_mode;

   // In audit mode, disable everything
   if (patient_audit_mode)
   {
      emma_disable_speed_buttons();

      frm_patient->bbtn_pat_insert->Enabled = false;
      frm_patient->bbtn_search_insert->Enabled = false;
      frm_patient->bbtn_pat_edit->Enabled = false;
      frm_patient->bbtn_pat_delete->Enabled = false;
      frm_patient->bbtn_pat_accept->Enabled = false;
      frm_patient->bbtn_pat_cancel->Enabled = false;

      frm_patient->spbtn_pwa_mode->Visible = false;
      frm_patient->spbtn_pwv_mode->Visible = false;
      frm_patient->spbtn_pwm_mode->Visible = false;
      frm_patient->spbtn_hrv_mode->Visible = false;

      frm_patient->pgctrl_pat->ActivePage = frm_patient->tbsht_pat_grid;
      frm_patient->pgctrl_int->ActivePage = frm_patient->tbsht_details;

      frm_patient->pnl_data->Enabled = false;
      frm_patient->pnl_questions->Enabled = false;
      frm_patient->bbtn_done->Enabled = false;
   
      frm_main->mnu_export->Enabled = false;
      frm_main->mnu_batch_print->Enabled = false;
      frm_main->mnu_merge->Enabled = false;
      frm_main->mnu_pack->Enabled = false;
      frm_main->mnu_multdb->Enabled = false;
      frm_main->mnu_listing->Enabled = false;
      frm_main->mnu_exit->Enabled = false;
      frm_main->mnu_export_database->Enabled = false;
      return;
   }
   // There is no state change for deleted records
   if (patient_active.audit_flag == AUDIT_DELETED)
   {
      return;
   }
   
   patient_dsrc = dbmgr_get_data_source(DBMGR_PATIENT_TABLE, false);
   if (patient_dsrc != NULL)
   {
      switch (patient_dsrc->State)
      {
         case dsInactive:
            // inactive
            break;
         case dsInsert:
            emma_disable_speed_buttons();

            frm_patient->bbtn_pat_accept->Enabled = true;
            frm_patient->bbtn_pat_cancel->Enabled = true;
            frm_patient->bbtn_pat_edit->Enabled = false;
            frm_patient->bbtn_pat_delete->Enabled = false;
            frm_patient->bbtn_pat_insert->Enabled = false;
            frm_patient->bbtn_search_insert->Enabled = false;
            frm_patient->lbl_pat_reason->Visible = false;
            frm_patient->mm_pat_reason->Visible = false;

            frm_patient->tbsht_pat_summary->Enabled = false;
            frm_patient->pgctrl_pat->Enabled = false;

            frm_main->mnu_export->Enabled = false;
            frm_main->mnu_batch_print->Enabled = false;
            frm_main->mnu_merge->Enabled = false;
            frm_main->mnu_pack->Enabled = false;
            frm_main->mnu_multdb->Enabled = false;
            frm_main->mnu_listing->Enabled = false;
            frm_main->mnu_exit->Enabled = false;
            frm_main->mnu_export_database->Enabled = false;
            emma_display_statusbar_message("Insert Mode", "", sphygmocor_white);
            break;

         case dsEdit:
            emma_disable_speed_buttons();

            frm_patient->bbtn_pat_accept->Enabled = true;
            frm_patient->bbtn_pat_cancel->Enabled = true;
            frm_patient->tbsht_pat_summary->Enabled = false;

            frm_main->mnu_export->Enabled = false;
            frm_main->mnu_batch_print->Enabled = false;
            frm_main->mnu_merge->Enabled = false;
            frm_main->mnu_pack->Enabled = false;
            frm_main->mnu_multdb->Enabled = false;
            frm_main->mnu_listing->Enabled = false;
            frm_main->mnu_export_database->Enabled = false;
            emma_display_statusbar_message("Edit Mode", "", sphygmocor_white);
            break;

         case dsBrowse:
            frm_patient->bbtn_pat_accept->Enabled = false;
            frm_patient->bbtn_pat_cancel->Enabled = false;
            frm_patient->bbtn_pat_insert->Enabled = true;
            frm_patient->bbtn_search_insert->Enabled = true;
            frm_patient->pnl_data->Enabled = false;
            frm_patient->pnl_questions->Enabled = false;
            frm_patient->bbtn_done->Enabled = false;
            if (config_get_audit_option())
            {
               frm_patient->lbl_pat_reason->Visible = true;
               frm_patient->mm_pat_reason->Visible = true;
            }
            frm_main->mnu_multdb->Enabled = true;
            // Disable merge for version 8.0
            frm_main->mnu_merge->Enabled = false;
            // PM V9
            // Only enable packing if editing is allowed
            if (emr_get_editing())
            {
               frm_main->mnu_pack->Enabled = true;
            }
            else
            {
               frm_main->mnu_pack->Enabled = false;
            }
            frm_main->mnu_exit->Enabled = true;

            study_mode = patient_get_study_mode();
            if (patient_dsrc->DataSet->RecordCount)
            {
               emma_enable_speed_buttons();
               frm_patient->tbsht_pat_summary->Enabled = true;
               if (!config_get_audit_option())
               {
                  frm_main->mnu_export->Enabled = true;
                  if (study_mode == MEAS_PWA_ID)
                  {
                     frm_main->mnu_export_database->Enabled = true;
                  }
               }
               frm_main->mnu_listing->Enabled = true;
               if (study_mode == MEAS_HRV_ID)
               {
                  frm_main->mnu_batch_print->Enabled = false;
               }
               else
               {
                  frm_main->mnu_batch_print->Enabled = true;
               }
            }
            else
            {
               emma_disable_speed_buttons();
               frm_patient->tbsht_pat_summary->Enabled = false;
               frm_main->mnu_export->Enabled = false;
               frm_main->mnu_listing->Enabled = false;
               frm_main->mnu_batch_print->Enabled = false;
               frm_main->mnu_export_database->Enabled = false;
               frm_patient->bbtn_pat_delete->Enabled = false;
               frm_patient->pnl_data->Enabled = false;
               frm_patient->pnl_questions->Enabled = false;
               frm_patient->bbtn_done->Enabled = false;
            }
            // PM V9
            // Only enable editing if EMR allows it
            if (emr_edit_active_patient())
            {
               frm_patient->bbtn_pat_edit->Enabled = true;
            }
            frm_patient->pgctrl_pat->Enabled = true;
            if (frm_patient->edit_mode)
            {
               if (patient_dsrc->DataSet->RecordCount)
               {
                  frm_patient->bbtn_pat_delete->Enabled = true;
                  frm_patient->pnl_data->Enabled = true;
                  frm_patient->pnl_questions->Enabled = true;
                  frm_patient->bbtn_done->Enabled = true;
                  if (config_get_audit_option())
                  {
                     frm_patient->lbl_pat_reason->Visible = true;
                     frm_patient->mm_pat_reason->Visible = true;
                  }
               }
            }
            emma_display_statusbar_message("", "", sphygmocor_white);
            break;
         default:
            break;
      }
   }
}

__fastcall Tfrm_patient::Tfrm_patient(TComponent* Owner)
    : Child_Form(Owner)
{
   edit_mode = false;
   patient_audit_mode = false;
   TDataSource *dsrc_pat;

   dsrc_pat = dbmgr_get_data_source(DBMGR_PATIENT_TABLE, false);

   if (dsrc_pat != NULL)
   {
      dsrc_pat->AutoEdit = false;

      grd_pat->DataSource = dsrc_pat;

      edt_pat_pid->DataSource = dsrc_pat;
      edt_pat_pid->DataField = PATIENT_ID;

      dbtxt_sysid->DataSource = dsrc_pat;
      dbtxt_sysid->DataField = PATIENT_SYSTEM_ID;

      dbtxt_dbid->DataSource = dsrc_pat;
      dbtxt_dbid->DataField = PATIENT_STUDY_ID;

      dbtxt_operator->DataSource = dsrc_pat;
      dbtxt_operator->DataField = PATIENT_AUDIT_OPERATOR;

      edt_pat_surname->DataSource = dsrc_pat;
      edt_pat_surname->DataField = PATIENT_SURNAME;

      edt_pat_fname->DataSource = dsrc_pat;
      edt_pat_fname->DataField = PATIENT_FIRST_NAME;

      edt_pat_oname->DataSource = dsrc_pat;
      edt_pat_oname->DataField = PATIENT_OTHER_NAME;

      edt_pat_code->DataSource = dsrc_pat;
      edt_pat_code->DataField = PATIENT_CODE;

      mm_pat_notes->DataSource = dsrc_pat;
      mm_pat_notes->DataField = PATIENT_NOTES;

      edt_pat_street->DataSource = dsrc_pat;
      edt_pat_street->DataField = PATIENT_STREET;

      edt_pat_suburb->DataSource = dsrc_pat;
      edt_pat_suburb->DataField = PATIENT_SUBURB;

      edt_pat_state->DataSource = dsrc_pat;
      edt_pat_state->DataField = PATIENT_STATE;

      edt_pat_country->DataSource = dsrc_pat;
      edt_pat_country->DataField = PATIENT_COUNTRY;

      edt_pat_pcode->DataSource = dsrc_pat;
      edt_pat_pcode->DataField = PATIENT_PCODE;

      edt_pat_phone->DataSource = dsrc_pat;
      edt_pat_phone->DataField = PATIENT_PHONE;

      cmbx_pat_sex->DataSource = dsrc_pat;
      cmbx_pat_sex->DataField = PATIENT_SEX;

      mm_pat_reason->DataSource = dsrc_pat;
      mm_pat_reason->DataField = PATIENT_AUDIT_REASON;
      // PM V9
      //dbnvg_pat->DataSource = dsrc_pat;
   }

   pnl_data->Enabled = false;
   pnl_questions->Enabled = false;
   bbtn_done->Enabled = false;
   pgctrl_pat->ActivePage = tbsht_pat_grid;
   pgctrl_int->ActivePage = tbsht_details;
   dtpck_pat_dob->DateFormat = dfLong;
   dtpck_pat_dob->MaxDate = (TDateTime::CurrentDate());
   dtpck_pat_dob->MinDate = StrToDate(PATIENT_MIN_DOB);
   dtpck_pat_dob->Date = (TDateTime::CurrentDate());

   dtpck_search_dob->DateFormat = dfLong;
   dtpck_search_dob->MaxDate = (TDateTime::CurrentDate());
   dtpck_search_dob->MinDate = StrToDate(PATIENT_MIN_DOB);
   dtpck_search_dob->Date = StrToDate(PATIENT_INIT_DATE);
}


void __fastcall Tfrm_patient::grd_patTitleClick(TColumn *Column)
{
   AnsiString index;

   if (Column->Title->Caption == PATIENT_COLUMN_FAMNAME)
   {
      Screen->Cursor = crHourGlass;
      dbmgr_select_index(DBMGR_PATIENT_TABLE,
                         PATIENT_SURNAME);
      Screen->Cursor = crDefault;
   }
   else if (Column->Title->Caption == PATIENT_COLUMN_PATID)
   {
      Screen->Cursor = crHourGlass;
      dbmgr_select_index(DBMGR_PATIENT_TABLE,
                         PATIENT_ID);
      Screen->Cursor = crDefault;
   }
   else if (Column->Title->Caption == PATIENT_COLUMN_DOB)
   {
      Screen->Cursor = crHourGlass;
      dbmgr_select_index(DBMGR_PATIENT_TABLE,
                         PATIENT_DOB);
      Screen->Cursor = crDefault;
   }
   else
   {
      Screen->Cursor = crHourGlass;
      index = PATIENT_SYSTEM_ID +  ";" + PATIENT_STUDY_ID + ";" + PATIENT_NO;
      dbmgr_select_index(DBMGR_PATIENT_TABLE,
                         index);
      Screen->Cursor = crDefault;
   }
}

void __fastcall Tfrm_patient::dtpck_pat_dobChange(TObject *Sender)
{
   TDataSet     *table;
   TDataSource  *dsrc;
   TDateTime    min_dob;


   if (patient_active.dob != dtpck_pat_dob->DateTime)
   {
      dsrc = dbmgr_get_data_source(DBMGR_PATIENT_TABLE, false);
      table = dbmgr_get_dataset(DBMGR_PATIENT_TABLE, false);
      if (dsrc == NULL || table == NULL)
      {
         return;
      }
      min_dob = StrToDate(PATIENT_MIN_DOB);
      if (dtpck_pat_dob->DateTime > min_dob)
      {
         if (dsrc->State == dsInsert || dsrc->State == dsEdit)
         {
            table->FieldByName(PATIENT_DOB)->AsDateTime = dtpck_pat_dob->DateTime;
         }
         else
         {
            dsrc->OnDataChange = NULL;
            table->Edit();
            dsrc->OnDataChange = data_event.record_changed;
            table->FieldByName(PATIENT_DOB)->AsDateTime = dtpck_pat_dob->DateTime;
         }
      }
   }
}
void __fastcall Tfrm_patient::pgctrl_patChange(TObject *Sender)
{
   TADOQuery         *qry_meas;
   TDateTime      dt_meas;
   MEAS_ID_TYPE   meas_id;
   DBMGR_ID_TYPE  table_id;
   String         order;
   int            days;
   int            months;
   int            years;

   TDateTime     right_now = TDateTime().CurrentDate();

   if (pgctrl_pat->ActivePage == tbsht_pat_summary)
   {
      lbl_pat_name->Caption = patient_get_name();
      meas_id = patient_get_study_mode();
      switch (meas_id)
      {
         case MEAS_PWA_ID:
            table_id = DBMGR_MEASURE_PWA_TABLE;
            order = MPW_DATETIME;
            break;
         case MEAS_PWV_ID:
            table_id = DBMGR_MEASURE_PWV_TABLE;
            order = MPW_DATETIME;
            break;
         case MEAS_PWM_ID:
               table_id = DBMGR_MEASURE_PWM_SESSION_TABLE;
               order = MPWM_SESSION_START;
               break;
         case MEAS_HRV_ID:
               table_id = DBMGR_MEASURE_HRV_TABLE;
               order = MPW_DATETIME;
               break;
         default:
            break;
      }

      qry_meas = dbmgr_setup_query(table_id,
                                   DBMGR_QUERY_KEY,
                                   PATIENT_SYSTEM_ID,
                                   PATIENT_STUDY_ID,
                                   PATIENT_NO,
                                   patient_active.system_id,
                                   patient_active.study_id,
                                   IntToStr(patient_active.number),
                                   order);

      if (qry_meas != NULL)
      {
         lbl_total->Caption = qry_meas->RecordCount;

         patient_nof_measure = (short int) qry_meas->RecordCount;

         if (qry_meas->RecordCount)
         {
            qry_meas->First();
            dt_meas = GetMeasureDateTime(qry_meas);
            lbl_first->Caption = dt_meas.FormatString(PATIENT_DATE_TIME_FORMAT);

            qry_meas->Last();
            dt_meas = GetMeasureDateTime(qry_meas);
            lbl_last->Caption = dt_meas.FormatString(PATIENT_DATE_TIME_FORMAT);
            int temp = (int)(right_now - dt_meas);
            days = temp % 365;
            months = days / 30;
            years = temp / 365;
            if (temp < 0)
            {
               lbl_days->Caption = "Study after today!";
            }
            else if (years > 0)
            {
               lbl_days->Caption = IntToStr(years) + " years, " + IntToStr(months) + " months";
            }
            else
            {
               lbl_days->Caption = IntToStr(days) + " days";
            }
         }
         else
         {
            lbl_first->Caption = "n/a";
            lbl_last->Caption  = "n/a";
            lbl_days->Caption = "n/a";
         }
         // PM V9
         // Clear the Search fields
         pnl_summary->Visible = true;
         qry_meas->Close();
         edt_search_pid->Clear();
         edt_search_surname->Clear();
         edt_search_fname->Clear();
         dtpck_search_dob->DateTime = StrToDate(PATIENT_INIT_DATE);
         //edt_search_pid->SetFocus();
      }
   }
   else
   {
      // PM V9
      // Ensure the data panel is visible
      data_event.state_changed(Sender);
      pnl_data->Visible = true;
   }
}
//---------------------------------------------------------------------------
void __fastcall Tfrm_patient::grd_patDblClick(TObject *Sender)
{
   if (frm_main->spdbtn_measure->Enabled)
   {
      frm_main->spdbtn_measureClick(Sender);
   }
}
//---------------------------------------------------------------------------
void __fastcall Tfrm_patient::FormShow(TObject *Sender)
{
   TDataSet    *patient_table;
   TDataSource *patient_dsrc;
   AnsiString   index;
   MEAS_ID_TYPE  study_mode;
   CONFIG_SYSTEM_OPTIONS  cfg_options;

   cfg_options = config_get_system_options();
   switch (cfg_options)
   {

      case CONFIG_PWA_OPTION:
         pnl_mode_buttons->Visible = false;
         spbtn_pwa_mode->Visible = true;
         spbtn_pwv_mode->Visible = false;
         spbtn_pwm_mode->Visible = false;
         spbtn_hrv_mode->Visible = false;
         break;
      case CONFIG_PWV_ONLY_OPTION:
         pnl_mode_buttons->Visible = false;
         spbtn_pwa_mode->Visible = false;
         spbtn_pwv_mode->Visible = true;
         spbtn_pwm_mode->Visible = false;
         spbtn_hrv_mode->Visible = false;

         // Start in PWV Mode
         patient_mode = MEAS_PWV_ID;
         spbtn_pwv_modeClick(Sender);
         break;
      case CONFIG_PWV_OPTION:     // Includes PWA
         pnl_mode_buttons->Visible = true;
         spbtn_pwa_mode->Visible = true;
         spbtn_pwv_mode->Visible = true;
         spbtn_pwm_mode->Visible = false;
         spbtn_hrv_mode->Visible = false;
         break;
      case CONFIG_PWM_OPTION:     // Includes PWA
         pnl_mode_buttons->Visible = true;
         spbtn_pwa_mode->Visible = true;
         spbtn_pwv_mode->Visible = false;
         spbtn_pwm_mode->Visible = true;
         spbtn_hrv_mode->Visible = false;
         break;
      case CONFIG_HRV_OPTION:      // Includes PWA
         pnl_mode_buttons->Visible = true;
         spbtn_pwa_mode->Visible = true;
         spbtn_pwv_mode->Visible = false;
         spbtn_pwm_mode->Visible = false;
         spbtn_hrv_mode->Visible = true;
         break;
      case CONFIG_STANDARD_ALL_OPTION:      // Includes PWA PWV PWM
         pnl_mode_buttons->Visible = true;
         spbtn_pwa_mode->Visible = true;
         spbtn_pwv_mode->Visible = true;
         spbtn_pwm_mode->Visible = true;
         spbtn_hrv_mode->Visible = false;
         break;
      case CONFIG_EXTENDED_ALL_OPTION:      // Includes PWA PWV HRV
         pnl_mode_buttons->Visible = true;
         spbtn_pwa_mode->Visible = true;
         spbtn_pwv_mode->Visible = true;
         spbtn_pwm_mode->Visible = false;
         spbtn_hrv_mode->Visible = true;
         break;
      case CONFIG_PWM_ONLY_OPTION:
         pnl_mode_buttons->Visible = false;
         spbtn_pwa_mode->Visible = false;
         spbtn_pwv_mode->Visible = false;
         spbtn_pwm_mode->Visible = true;
         spbtn_hrv_mode->Visible = false;

         // Start in PWM Mode
         patient_mode = MEAS_PWM_ID;
         spbtn_pwm_modeClick(Sender);
         break;
      case CONFIG_NO_OPTION:
         pnl_mode_buttons->Visible = false;
         spbtn_pwa_mode->Visible = false;
         spbtn_pwv_mode->Visible = false;
         spbtn_pwm_mode->Visible = false;
         spbtn_hrv_mode->Visible = false;
         break;
      default:
         break;
   }
   if (dbmgr_open(DBMGR_PATIENT_TABLE, false))
   {
      patient_update_active_database();
      patient_dsrc = dbmgr_get_data_source(DBMGR_PATIENT_TABLE, false);
      if (patient_dsrc != NULL)
      {
         patient_dsrc->OnDataChange = data_event.record_changed;
         patient_dsrc->OnStateChange = data_event.state_changed;
      }

      frm_main->mnu_batch_print->Enabled = true;
      // Disable merge for version 8.0
      frm_main->mnu_merge->Enabled = false;
      // PM V9
      // Only enable packing if editing is allowed
      if (emr_get_editing())
      {
         frm_main->mnu_pack->Enabled = true;
      }
      else
      {
         frm_main->mnu_pack->Enabled = false;
      }
      frm_main->mnu_export->Enabled = true;
      frm_main->mnu_listing->Enabled = true;
      frm_main->mnu_multdb->Enabled = true;

      study_mode = patient_get_study_mode();
      if (study_mode == MEAS_PWA_ID)
      {
         frm_main->mnu_export_database->Enabled = true;
      }
      else
      {
         frm_main->mnu_export_database->Enabled = false;
      }

      if (study_mode == MEAS_HRV_ID)
      {
         frm_main->mnu_batch_print->Enabled = false;
      }
      else
      {
         frm_main->mnu_batch_print->Enabled = true;
      }

      pgctrl_pat->ActivePage = tbsht_pat_grid;
      pgctrl_int->ActivePage = tbsht_details;
      bbtn_pat_insert->Enabled = true;
      bbtn_search_insert->Enabled = true;
      patient_table = dbmgr_get_dataset(DBMGR_PATIENT_TABLE, false);
      if (patient_table != NULL)
      {
         patient_table->BeforePost = data_event.validate_record;
         lbl_nof_patients->Caption = " Patients: " + IntToStr(patient_table->RecordCount);
         // If this is the first time
         if (patient_active.number == 0)
         {
            // PM V9
            // Locate or create the patient using the EMR object - if enabled
            if (!patient_emr_mode(patient_table))
            {
               // Otherwise go to the last patient, if any
               if (patient_table->RecordCount)
               {
                  patient_table->Last();
               }
               else
               {
                  emma_disable_speed_buttons();
                  frm_main->mnu_batch_print->Enabled = false;
                  frm_main->mnu_export->Enabled = false;
                  frm_main->mnu_export_database->Enabled = false;
                  frm_main->mnu_listing->Enabled = false;
                  bbtn_pat_editClick(Sender);
               }
               
               // PM V9
               // In Clinical mode, display the Search tab and hide patient
               // details the first time
               if (config_get_clinical_option())
               {
                  pgctrl_pat->ActivePage = tbsht_pat_summary;
                  bbtn_search_resetClick(Sender);
               }
            }
            // PM V9
            // In Clinical EMR mode, display the Search tab and the EMR patient details
            else if (config_get_clinical_option())
            {
               pgctrl_pat->ActivePage = tbsht_pat_summary;
               pgctrl_patChange(Sender);
            }
         }
         // If not the first time, locate the active patient
         else
         {
            TLocateOptions Opts;
            Variant locvalues[3];

            Opts.Clear();
            Opts << loPartialKey;

            locvalues[0] = Variant(patient_active.system_id);
            locvalues[1] = Variant(patient_active.study_id);
            locvalues[2] = Variant(patient_active.number);

            index = PATIENT_SYSTEM_ID +  ";" + PATIENT_STUDY_ID + ";" + PATIENT_NO;
            patient_table->Locate(index, VarArrayOf(locvalues, 2), Opts);
            // PM V9
            // In Clinical mode, display the Search tab
            if (config_get_clinical_option())
            {
               pgctrl_pat->ActivePage = tbsht_pat_summary;
               pgctrl_patChange(Sender);
            }
         }
      }
      if (edit_mode)
      {
          emma_display_statusbar_message("Edit Mode", "", sphygmocor_white);
      }
      else
      {
         emma_display_statusbar_message("", "", sphygmocor_white);
      }
   }
   else
   {
       emma_disable_speed_buttons();
       bbtn_pat_insert->Enabled = false;
       bbtn_search_insert->Enabled = false;
       bbtn_pat_edit->Enabled = false;
       bbtn_pat_delete->Enabled = false;
       bbtn_pat_accept->Enabled = false;
       bbtn_pat_cancel->Enabled = false;
   }
   // PM CR

   // If the audit option is set, the reason for change is enabled and exports disabled
   if (config_get_audit_option())
   {
      lbl_pat_reason->Visible = true;
      mm_pat_reason->Visible = true;
      mnuExport->Enabled = false;
      frm_main->mnu_export->Enabled = false;
      frm_main->mnu_export_database->Enabled = false;
   }
   else
   {
      lbl_pat_reason->Visible = false;
      mm_pat_reason->Visible = false;
      mnuExport->Enabled = true;
   }

   frm_patient->SetFocus();
}
// PM V9
/* ###########################################################################
 ** patient_emr_mode(TDataSet *patient_table)
 **
 ** DESCRIPTION
 **  Creates or displays the patient specified by the EMR object
 ** INPUT
 **  Patient Table DataSet
 ** OUTPUT
 **  None
 ** RETURN
 **  Boolean - success or not
*/
//---------------------------------------------------------------------------
bool patient_emr_mode(TDataSet *patient_table)
{
   String               study_id;
   String               index;
   EMR_RECORD_TYPE      emr;
   PATIENT_NUMBER_TYPE  patient_number;
   bool                 success = false;

   // If EMR is enabled and not in Default Mode
   if (emr_get_enabled())
   {
      if (!emr_get_default_mode())
      {
         // Try to locate the patient
         if (emr_get(&emr))
         {
            study_id = multdb_get_active_name();
            if (patient_table->RecordCount)
            {
               TLocateOptions Opts;
               Variant locvalues[7];

               Opts.Clear();
               Opts << loCaseInsensitive;

               locvalues[0] = Variant(emr.system_id);
               locvalues[1] = Variant(study_id);
               locvalues[2] = Variant(emr.surname);
               locvalues[3] = Variant(emr.first_name);
               locvalues[4] = Variant(emr.dob);
               locvalues[5] = Variant(emr.sex);

               // If the patient id is not in the emr record
               // then search for the required fields only
               if (emr.patient_id == "")
               {
                  index = PATIENT_SYSTEM_ID +  ";" + PATIENT_STUDY_ID + ";" +
                          PATIENT_SURNAME +  ";" + PATIENT_FIRST_NAME + ";" +
                          PATIENT_DOB +  ";" + PATIENT_SEX;

                  if (patient_table->Locate(index,
                                            VarArrayOf(locvalues, 5),
                                            Opts))
                  {
                     success = true;
                  }
               }
               else
               {
                  // If the patient id is available, then add it to the search fields
                  locvalues[6] = Variant(emr.patient_id);

                  index = PATIENT_SYSTEM_ID +  ";" + PATIENT_STUDY_ID + ";" +
                          PATIENT_SURNAME +  ";" + PATIENT_FIRST_NAME + ";" +
                          PATIENT_DOB +  ";" + PATIENT_SEX + ";" + PATIENT_ID;

                  if (patient_table->Locate(index,
                                            VarArrayOf(locvalues, 6),
                                            Opts))
                  {
                     success = true;
                  }
                  // If a match is not found, check for an existing patient
                  // with the same patient id
                  else if (patient_table->Locate(PATIENT_ID,
                                            locvalues[6],
                                            Opts))
                  {
                     // If located ask the user what to do next
                     int user = MsgBox(LoadStr(MSG_EMR_PATIENT_ID_ERROR), SCONFIRMATION, MB_YESNOCANCEL | MB_ICONQUESTION);
                     switch(user)
                     {
                        // Exit EMR mode
                        case IDCANCEL:
                           // This will reset all the emr values and disable EMR mode
                           emr_initialise();
                           // Remove the EMR label
                           frm_main->lbl_data_mode->Caption = "";
                           // Enable options that may have been disabled by the
                           // EMR editing option
                           frm_main->mnu_pack->Enabled = true;
                           // If a patient has been selected, enable the Analysis button
                           if (frm_patient->pnl_data->Visible)
                           {
                              frm_main->spdbtn_analysis->Enabled = true;
                              frm_main->Analysis1->Enabled = true;
                           }
                           return true;

                        // Create a new patient
                        case IDYES:
                           break;

                        // Update the existing patient
                        case IDNO:
                           success = true;
                           break;
                     }
                  }

               }
            }
            if (success)
            {
               try
               {
                  // If the patient was located, update the fields contained in
                  // the EMR record including required fields as the user may
                  // choose to update an existing patient
                  patient_table->Edit();
                  patient_table->FieldByName(PATIENT_SYSTEM_ID)->Value = emr.system_id;
                  patient_table->FieldByName(PATIENT_STUDY_ID)->Value = study_id;
                  patient_table->FieldByName(PATIENT_SURNAME)->AsString = emr.surname;
                  patient_table->FieldByName(PATIENT_FIRST_NAME)->AsString = emr.first_name;
                  patient_table->FieldByName(PATIENT_SEX)->AsString = emr.sex;
                  patient_table->FieldByName(PATIENT_DOB)->AsDateTime = emr.dob;
                  if (emr.patient_id != "")
                  {
                     patient_table->FieldByName(PATIENT_ID)->AsString = emr.patient_id;
                  }
                  if (emr.other_name != "")
                  {
                     patient_table->FieldByName(PATIENT_OTHER_NAME)->AsString = emr.other_name;
                  }
                  if (emr.street != "")
                  {
                     patient_table->FieldByName(PATIENT_STREET)->AsString = emr.street;
                  }
                  if (emr.suburb != "")
                  {
                     patient_table->FieldByName(PATIENT_SUBURB)->AsString = emr.suburb;
                  }
                  if (emr.state != "")
                  {
                     patient_table->FieldByName(PATIENT_STATE)->AsString = emr.state;
                  }
                  if (emr.pcode != "")
                  {
                     patient_table->FieldByName(PATIENT_PCODE)->AsString = emr.pcode;
                  }
                  if (emr.country != "")
                  {
                     patient_table->FieldByName(PATIENT_COUNTRY)->AsString = emr.country;
                  }
                  if (emr.phone != "")
                  {
                     patient_table->FieldByName(PATIENT_PHONE)->AsString = emr.phone;
                  }
                  if (emr.code != "")
                  {
                     patient_table->FieldByName(PATIENT_CODE)->AsString = emr.code;
                  }
                  if (emr.patient_notes != "")
                  {
                     patient_table->FieldByName(PATIENT_NOTES)->AsString = emr.patient_notes;
                  }
                  patient_table->Post();

                  // Check age and show warning if patient is too young
                  UCOUNT lAge = patient_get_age_at_date(Now());
                  if (lAge <= PATIENT_YOUNG_AGE)
                  {
                     MsgBox(MSG_YOUNG_PATIENT, SWARNING, MB_ICONEXCLAMATION);
                  }
                  success = true;
               }
               catch (Exception &exception)
               {
                  MsgBox_show(TERROR,
                              MSG_DBREADWRITE_ERROR,
                              LoadStr(MSG_POST_ERROR),
                              MSG_POST_ERROR,
                              LoadStr(MSG_POST_ERROR) +patient_get_error_str() +exception.Message);
                  patient_table->Cancel();
               }
            }
            else
            {
               // If not located, create the patient
               patient_number = patient_assign_new_number();
               if (patient_number)
               {
                  try
                  {
                     patient_table->Insert();
                     patient_table->FieldByName(PATIENT_SYSTEM_ID)->Value = emr.system_id;
                     patient_table->FieldByName(PATIENT_STUDY_ID)->Value = study_id;
                     patient_table->FieldByName(PATIENT_NO)->AsInteger = patient_number;
                     patient_table->FieldByName(PATIENT_ID)->AsString = emr.patient_id;
                     patient_table->FieldByName(PATIENT_SURNAME)->AsString = emr.surname;
                     patient_table->FieldByName(PATIENT_FIRST_NAME)->AsString = emr.first_name;
                     patient_table->FieldByName(PATIENT_SEX)->AsString = emr.sex;
                     patient_table->FieldByName(PATIENT_DOB)->AsDateTime = emr.dob;
                     patient_table->FieldByName(PATIENT_OTHER_NAME)->AsString = emr.other_name;
                     patient_table->FieldByName(PATIENT_STREET)->AsString = emr.street;
                     patient_table->FieldByName(PATIENT_SUBURB)->AsString = emr.suburb;
                     patient_table->FieldByName(PATIENT_STATE)->AsString = emr.state;
                     patient_table->FieldByName(PATIENT_PCODE)->AsString = emr.pcode;
                     patient_table->FieldByName(PATIENT_COUNTRY)->AsString = emr.country;
                     patient_table->FieldByName(PATIENT_PHONE)->AsString = emr.phone;
                     patient_table->FieldByName(PATIENT_CODE)->AsString = emr.code;
                     patient_table->FieldByName(PATIENT_NOTES)->AsString = emr.patient_notes;
                     patient_table->Post();
                     frm_patient->lbl_nof_patients->Caption = " Patients: " + IntToStr(patient_table->RecordCount);

                     // Check age and show warning if patient is too young
                     UCOUNT lAge = patient_get_age_at_date(Now());
                     if (lAge <= PATIENT_YOUNG_AGE)
                     {
                        MsgBox(MSG_YOUNG_PATIENT, SWARNING, MB_ICONEXCLAMATION);
                     }
                     success = true;
                  }
                  catch (Exception &exception)
                  {
                     MsgBox_show(TERROR,
                                 MSG_DBREADWRITE_ERROR,
                                 LoadStr(MSG_POST_ERROR),
                                 MSG_POST_ERROR,
                                 LoadStr(MSG_POST_ERROR) +patient_get_error_str() +exception.Message);
                     patient_table->Cancel();
                  }
               }
               else
               {
                  MsgBox_show(TERROR,
                              MSG_PATIENT_ERROR,
                              LoadStr(MSG_PATIENT_NUMBER_ERROR),
                              MSG_PATIENT_NUMBER_ERROR,
                              LoadStr(MSG_PATIENT_NUMBER_ERROR));
               }
            }
         }
      }
   }
   return success;
}
//---------------------------------------------------------------------------
void __fastcall Tfrm_patient::FormHide(TObject *Sender)
{
   set_database_status();
   frm_main->mnu_batch_print->Enabled = false;
   frm_main->mnu_merge->Enabled = false;
   frm_main->mnu_pack->Enabled = false;
   frm_main->mnu_export->Enabled = false;
   frm_main->mnu_multdb->Enabled = false;
   frm_main->mnu_listing->Enabled = false;
   frm_main->mnu_export_database->Enabled = false;
   emma_display_statusbar_message("", "", "", sphygmocor_white);
   emma_display_statusbar_message("", "", sphygmocor_white);
}

void __fastcall Tfrm_patient::set_database_status(void)
{
   TDataSet    *patient_table;
   TDataSource *patient_dsrc;

   patient_dsrc = dbmgr_get_data_source(DBMGR_PATIENT_TABLE, false);
   if (patient_dsrc != NULL)
   {
      bbtn_pat_acceptClick(this);
      patient_dsrc->OnDataChange = NULL;
      patient_dsrc->OnStateChange = NULL;
   }

   patient_table = dbmgr_get_dataset(DBMGR_PATIENT_TABLE, false);
   if (patient_table != NULL)
   {
      patient_table->BeforePost = NULL;
   }
   dbmgr_close(DBMGR_PATIENT_TABLE, false);
}
//---------------------------------------------------------------------------
void __fastcall Tfrm_patient::mnu_sort_surname_click(TObject *Sender)
{
   Screen->Cursor = crHourGlass;
   dbmgr_select_index(DBMGR_PATIENT_TABLE, PATIENT_SURNAME);
   Screen->Cursor = crDefault;
}
//---------------------------------------------------------------------------
void __fastcall Tfrm_patient::mnu_sort_age_click(TObject *Sender)
{
   Screen->Cursor = crHourGlass;
   dbmgr_select_index(DBMGR_PATIENT_TABLE, PATIENT_DOB);
   Screen->Cursor = crDefault;
}
//---------------------------------------------------------------------------
void __fastcall Tfrm_patient::mnu_sort_patid_click(TObject *Sender)
{
   Screen->Cursor = crHourGlass;
   dbmgr_select_index(DBMGR_PATIENT_TABLE, PATIENT_ID);
   Screen->Cursor = crDefault;
}

void __fastcall Tfrm_patient::mnu_sort_patnoClick(TObject *Sender)
{
   AnsiString S;

   S = PATIENT_SYSTEM_ID +  ";" + PATIENT_STUDY_ID + ";" + PATIENT_NO;

   Screen->Cursor = crHourGlass;
   dbmgr_select_index(DBMGR_PATIENT_TABLE, S);
   Screen->Cursor = crDefault;
}
//---------------------------------------------------------------------------
void __fastcall Tfrm_patient::mnu_export_click(TObject *Sender)
{
   MEAS_ID_TYPE  meas_mode = patient_get_study_mode();
   switch (meas_mode)
   {
      case MEAS_PWA_ID:
      {
        String lFileName = ExtractFilePath(Application->ExeName) + EXPORT_SUBDIR +
                           "Patient_" + patient_active.surname + "_pwa.txt";
        TDataSet *lTblPWA = dbmgr_setup_query(DBMGR_MEASURE_PWA_TABLE,
                                              DBMGR_QUERY_KEY,
                                              PATIENT_SYSTEM_ID,
                                              PATIENT_STUDY_ID,
                                              PATIENT_NO,
                                              patient_active.system_id,
                                              patient_active.study_id,
                                              IntToStr(patient_active.number),
                                              MPW_DATETIME);
        export_patient_measurements(lTblPWA, lFileName, meas_get_current_pwa());
        break;
      }
      case MEAS_PWV_ID:
      {
        String lFileName = ExtractFilePath(Application->ExeName) + EXPORT_SUBDIR +
                           "Patient_" + patient_active.surname + "_pwv.txt";
        TDataSet *lTblPWV = dbmgr_setup_query(DBMGR_MEASURE_PWV_TABLE,
                                              DBMGR_QUERY_KEY,
                                              PATIENT_SYSTEM_ID,
                                              PATIENT_STUDY_ID,
                                              PATIENT_NO,
                                              patient_active.system_id,
                                              patient_active.study_id,
                                              IntToStr(patient_active.number),
                                              MPW_DATETIME);
        export_patient_measurements(lTblPWV, lFileName, meas_get_current_pwv());
        break;
      }
      case MEAS_PWM_ID:
      {
        String lFileName = ExtractFilePath(Application->ExeName) + EXPORT_SUBDIR +
                           "Patient_" + patient_active.surname + "_pwm.txt";
        TDataSet *lTblPWM = dbmgr_setup_query(DBMGR_MEASURE_PWM_TABLE,
                                              DBMGR_QUERY_KEY,
                                              PATIENT_SYSTEM_ID,
                                              PATIENT_STUDY_ID,
                                              PATIENT_NO,
                                              patient_active.system_id,
                                              patient_active.study_id,
                                              IntToStr(patient_active.number),
                                              MPW_DATETIME);
        export_patient_measurements(lTblPWM, lFileName, meas_get_current_pwm());
        break;
      }
      case MEAS_HRV_ID:
      {
        String lFileName = ExtractFilePath(Application->ExeName) + EXPORT_SUBDIR +
                           "Patient_" + patient_active.surname + "_hrv.txt";
        TDataSet *lTblHRV = dbmgr_setup_query(DBMGR_MEASURE_HRV_TABLE,
                                              DBMGR_QUERY_KEY,
                                              PATIENT_SYSTEM_ID,
                                              PATIENT_STUDY_ID,
                                              PATIENT_NO,
                                              patient_active.system_id,
                                              patient_active.study_id,
                                              IntToStr(patient_active.number),
                                              MPW_DATETIME);
        export_patient_measurements(lTblHRV, lFileName, meas_get_current_hrv());
        break;
      }
   }
}
//---------------------------------------------------------------------------
void __fastcall Tfrm_patient::cmbx_pat_sexChange(TObject *Sender)
{
   TDataSet     *table;
   TDataSource  *dsrc;

   dsrc = dbmgr_get_data_source(DBMGR_PATIENT_TABLE, false);
   if (dsrc != NULL && (dsrc->State == dsInsert || dsrc->State == dsEdit))
   {
      table = dbmgr_get_dataset(DBMGR_PATIENT_TABLE, false);
      if (table != NULL)
      {
         table->FieldByName(PATIENT_SEX)->AsString = cmbx_pat_sex->Text;
      }
   }
}
//---------------------------------------------------------------------------



void __fastcall Tfrm_patient::grd_patKeyPress(TObject *Sender, char &Key)
{
  if (Key == VK_RETURN)
  {
    grd_patDblClick(Sender);
  }
}
//---------------------------------------------------------------------------
// PM CR


MEAS_ID_TYPE patient_get_study_mode(void)
{
   return patient_mode;
}

void __fastcall Tfrm_patient::spbtn_pwa_modeClick(TObject *Sender)
{
   patient_mode = MEAS_PWA_ID;

   frm_main->spdbtn_analysis->Enabled = true;
   frm_main->Analysis1->Enabled = true;
   if (!config_get_audit_option())
   {
      frm_main->mnu_export_database->Enabled = true;
   }
   else
   {
      if (patient_active.audit_flag == AUDIT_DELETED)
      {
         frm_main->spdbtn_analysis->Enabled = false;
         frm_main->Analysis1->Enabled = false;
      }
   }
   // If a patient has not been selected, disable the Analysis button
   if (!pnl_data->Visible)
   {
      frm_main->spdbtn_analysis->Enabled = false;
      frm_main->Analysis1->Enabled = false;
   }
   // PM V9
   // If editing is false, disable the Analysis button
   if (!emr_get_editing())
   {
      frm_main->spdbtn_analysis->Enabled = false;
      frm_main->Analysis1->Enabled = false;
   }
   frm_main->mnu_batch_print->Enabled = true;
   frm_main->lbl_scor_mode->Caption = "Pulse Wave Analysis";
   patient_update_measurement_count(PATIENT_RESET_MEAS_NUM);

   spbtn_pwa_mode->Down = true;
   spbtn_hrv_mode->Down = false;
   spbtn_pwv_mode->Down = false;
   spbtn_pwm_mode->Down = false;
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_patient::spbtn_hrv_modeClick(TObject *Sender)
{
   patient_mode = MEAS_HRV_ID;

   frm_main->spdbtn_analysis->Enabled = false;
   frm_main->Analysis1->Enabled = false;
   frm_main->mnu_export_database->Enabled = false;
   frm_main->mnu_batch_print->Enabled = false;
   frm_main->lbl_scor_mode->Caption = "Heart Rate Variability";

   patient_update_measurement_count(PATIENT_RESET_MEAS_NUM);

   spbtn_pwa_mode->Down = false;
   spbtn_hrv_mode->Down = true;
   spbtn_pwv_mode->Down = false;
   spbtn_pwm_mode->Down = false;
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_patient::spbtn_pwv_modeClick(TObject *Sender)
{
   patient_mode = MEAS_PWV_ID;

   frm_main->spdbtn_analysis->Enabled = true;
   frm_main->Analysis1->Enabled = true;
   if (config_get_audit_option())
   {
      if (patient_active.audit_flag == AUDIT_DELETED)
      {
         frm_main->spdbtn_analysis->Enabled = false;
         frm_main->Analysis1->Enabled = false;
      }
   }
   // If a patient has not been selected, disable the Analysis button
   if (!pnl_data->Visible)
   {
      frm_main->spdbtn_analysis->Enabled = false;
      frm_main->Analysis1->Enabled = false;
   }
   // PM V9
   // If editing is false, disable the Analysis button
   if (!emr_get_editing())
   {
      frm_main->spdbtn_analysis->Enabled = false;
      frm_main->Analysis1->Enabled = false;
   }
   frm_main->mnu_export_database->Enabled = false;
   frm_main->mnu_batch_print->Enabled = true;
   frm_main->lbl_scor_mode->Caption = "Pulse Wave Velocity";

   patient_update_measurement_count(PATIENT_RESET_MEAS_NUM);

   spbtn_pwa_mode->Down = false;
   spbtn_hrv_mode->Down = false;
   spbtn_pwv_mode->Down = true;
   spbtn_pwm_mode->Down = false;
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_patient::spbtn_pwm_modeClick(TObject *Sender)
{
   patient_mode = MEAS_PWM_ID;

   frm_main->spdbtn_analysis->Enabled = false;
   frm_main->Analysis1->Enabled = false;
   frm_main->mnu_export_database->Enabled = false;
   frm_main->mnu_batch_print->Enabled = true;
   frm_main->lbl_scor_mode->Caption = "Pulse Wave Monitoring";

   patient_update_measurement_count(PATIENT_RESET_MEAS_NUM);

   spbtn_pwa_mode->Down = false;
   spbtn_hrv_mode->Down = false;
   spbtn_pwv_mode->Down = false;
   spbtn_pwm_mode->Down = true;
}
//---------------------------------------------------------------------------


void __fastcall Tfrm_patient::edt_pat_fnameChange(TObject *Sender)
{
   String fname;
   String upper_case;
   String capital;

   fname = edt_pat_fname->Text;

   // Capitalise the first letter
   upper_case = fname.UpperCase();
   capital = upper_case.SubString(1,1) + fname.SubString(2, (fname.Length() - 1));
   edt_pat_fname->Text = capital;

   // Make sure the cursor is at the end
   edt_pat_fname->SelStart = fname.Length();
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_patient::edt_pat_surnameChange(TObject *Sender)
{
   String surname;
   String upper_case;
   String capital;

   surname = edt_pat_surname->Text;

   // Capitalise the first letter
   upper_case = surname.UpperCase();
   capital = upper_case.SubString(1,1) + surname.SubString(2, (surname.Length() - 1));
   edt_pat_surname->Text = capital;

   // Make sure the cursor is at the end
   edt_pat_surname->SelStart = surname.Length();
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_patient::edt_pat_onameChange(TObject *Sender)
{
   String oname;
   String upper_case;
   String capital;

   oname = edt_pat_oname->Text;

   // Capitalise the first letter
   upper_case = oname.UpperCase();
   capital = upper_case.SubString(1,1) + oname.SubString(2, (oname.Length() - 1));
   edt_pat_oname->Text = capital;

   // Make sure the cursor is at the end
   edt_pat_oname->SelStart = oname.Length();
}
//---------------------------------------------------------------------------


void __fastcall Tfrm_patient::bbtn_doneClick(TObject *Sender)
{
   String codes;
   TDataSource *dsrc_pat;

   // Display the codes in the notes DBMemo
   codes = interview_get_codes(chklstbx_interview);
   dsrc_pat = dbmgr_get_data_source(DBMGR_PATIENT_TABLE, false);
   dsrc_pat->DataSet->Edit();
   if (mm_pat_notes->Lines->Count)
   {
      if (mm_pat_notes->Lines->Strings[0].AnsiPos("Profile:") == 0)
      {
         mm_pat_notes->Lines->Insert(0, codes);
      }
      else
      {
         mm_pat_notes->Lines->Strings[0] = codes;
      }
   }
   else
   {
      mm_pat_notes->Lines->Insert(0, codes);
   }
   pgctrl_int->ActivePage = tbsht_details;

   // This ensures the responses are displayed on the interview tabsheet
   data_event.record_changed(Sender, NULL);
}
//---------------------------------------------------------------------------
// PM CR

// PM V9
void __fastcall Tfrm_patient::bbtn_pat_searchClick(TObject *Sender)
{
   TDataSet             *patient_table;
   TDataSource          *ds_patient_search;
   String               patient_id;
   String               patient_surname;
   String               patient_fname;
   TDateTime            patient_dob;
   String               index;
   String               system_id;
   String               study_id;
   PATIENT_NUMBER_TYPE  patient_no;
   TADOQuery            *qry_patient_search;
   TDateTime            min_dob;
   
   // Read Search parameters from the Search tab
   patient_id = edt_search_pid->Text;
   patient_surname = edt_search_surname->Text;
   patient_fname = edt_search_fname->Text;
   patient_dob = dtpck_search_dob->DateTime;
   min_dob = StrToDate(PATIENT_MIN_DOB);
   grd_search->Visible = false;

   patient_table = dbmgr_get_dataset(DBMGR_PATIENT_TABLE, false);
   if (patient_table != NULL)
   {
      // If a dob has been entered, include it in the query
      if (patient_dob > min_dob)
      {
         qry_patient_search = dbmgr_setup_query(DBMGR_PATIENT_TABLE,
                                   DBMGR_QUERY_PATIENT_SEARCH,
                                   PATIENT_ID,
                                   PATIENT_SURNAME,
                                   PATIENT_FIRST_NAME,
                                   PATIENT_DOB,
                                   patient_id,
                                   patient_surname,
                                   patient_fname,
                                   patient_dob);
      }
      else
      {
         // Inform the user if no parameters have been entered
         if (patient_id == "" && patient_surname == "" && patient_fname == "")
         {
            MsgBox(MSG_PATIENT_NO_SEARCH_PARAMETERS, SVALIDATION, MB_ICONEXCLAMATION);
            return;
         }
         // Otherwise, query the database
         else
         {
            qry_patient_search = dbmgr_setup_query(DBMGR_PATIENT_TABLE,
                                   DBMGR_QUERY_PATIENT_SEARCH,
                                   PATIENT_ID,
                                   PATIENT_SURNAME,
                                   PATIENT_FIRST_NAME,
                                   patient_id,
                                   patient_surname,
                                   patient_fname);
         }
      }

      ds_patient_search = dbmgr_get_data_source(DBMGR_PATIENT_QUERY, false);
      if ((ds_patient_search != NULL) && (qry_patient_search != NULL))
      {
         // If the patient is located, display them
         if (qry_patient_search->RecordCount == 1)
         {
            data_event.search_changed(Sender, NULL);
         }
         // If there's more than one match, display the list in the search grid
         else if (qry_patient_search->RecordCount > 1)
         {
            grd_search->Visible = true;
            grd_search->DataSource = ds_patient_search;
            grd_search->SetFocus();
            ds_patient_search->OnDataChange = data_event.search_changed;
         }
         else
         {
            MsgBox(MSG_PATIENT_NO_PATIENTS, SVALIDATION, MB_ICONEXCLAMATION);
         }
      }
   }
}
// PM V9
// Set and display the patient selected in the search grid
//---------------------------------------------------------------------------
void __fastcall Patient_Data_Event_Class::search_changed(TObject *Sender,
                                                         TField  *Field)
{
   TDataSet             *table;
   String               system_id;
   String               study_id;
   PATIENT_NUMBER_TYPE  patient_no;

   table = dbmgr_get_dataset(DBMGR_PATIENT_QUERY, false);

   if (table == NULL)
   {
      return;
   }

   system_id = table->FieldByName(PATIENT_SYSTEM_ID)->AsString;
   patient_no = (PATIENT_NUMBER_TYPE)table->FieldByName(PATIENT_NO)->AsInteger;
   study_id = table->FieldByName(PATIENT_STUDY_ID)->AsString;

   if (patient_set(system_id, study_id, patient_no))
   {
      data_event.state_changed(Sender);
      frm_patient->pnl_data->Visible = true;
      frm_patient->pgctrl_patChange(Sender);
   }
}

// PM V9
// Clear the search fields and hide patient details
void __fastcall Tfrm_patient::bbtn_search_resetClick(TObject *Sender)
{
   TDataSource *ds_patient_search = dbmgr_get_data_source(DBMGR_PATIENT_QUERY, false);

   if (ds_patient_search != NULL)
   {
      emma_disable_speed_buttons();
      bbtn_pat_edit->Enabled = false;
      bbtn_pat_delete->Enabled = false;
      edt_search_pid->Clear();
      edt_search_surname->Clear();
      edt_search_fname->Clear();
      dtpck_search_dob->DateTime = StrToDate(PATIENT_INIT_DATE);
      grd_search->Visible = false;
      ds_patient_search->OnDataChange = NULL;
      pnl_data->Visible = false;
      pnl_summary->Visible = false;
      //edt_search_pid->SetFocus();
   }
}
//---------------------------------------------------------------------------

// PM V9
void __fastcall Tfrm_patient::edt_search_pidKeyPress(TObject *Sender,
      char &Key)
{
   if (Key == VK_RETURN)
   {
      bbtn_pat_searchClick(Sender);
   }
}
//---------------------------------------------------------------------------
// PM V9
void __fastcall Tfrm_patient::edt_search_surnameKeyPress(TObject *Sender,
      char &Key)
{
   if (Key == VK_RETURN)
   {
      bbtn_pat_searchClick(Sender);
   }   
}
//---------------------------------------------------------------------------
// PM V9
void __fastcall Tfrm_patient::edt_search_fnameKeyPress(TObject *Sender,
      char &Key)
{
   if (Key == VK_RETURN)
   {
      bbtn_pat_searchClick(Sender);
   }   
}
//---------------------------------------------------------------------------
// PM V9
void __fastcall Tfrm_patient::dtpck_search_dobKeyPress(TObject *Sender,
      char &Key)
{
   if (Key == VK_RETURN)
   {
      bbtn_pat_searchClick(Sender);
   }   
}
//---------------------------------------------------------------------------


void __fastcall Tfrm_patient::bbtn_pat_editClick(TObject *Sender)
{
   TDataSource *dsrc_pat;
   TDataSet    *table_pat;

   dsrc_pat = dbmgr_get_data_source(DBMGR_PATIENT_TABLE, false);
   if (edit_mode)
   {
      edit_mode = false;
   }
   else
   {
      edit_mode = true;
   }

   bbtn_pat_insert->Enabled = true;
   bbtn_search_insert->Enabled = true;
   bbtn_pat_delete->Enabled = edit_mode;
   // PM V9
   // Hide patient details in Clinical mode
   if (config_get_clinical_option())
   {
      pgctrl_pat->ActivePage = tbsht_pat_summary;
   }
   else
   {
      pgctrl_pat->ActivePage = tbsht_pat_grid;
   }
   pgctrl_patChange(Sender);

   if (edit_mode)
   {
      dsrc_pat->AutoEdit = true;
      bbtn_pat_edit->Caption = "Brows&e";
      table_pat = dbmgr_get_dataset(DBMGR_PATIENT_TABLE, false);
      if (table_pat->RecordCount)
      {
         pnl_data->Enabled = true;
         pnl_questions->Enabled = true;
         bbtn_done->Enabled = true;
         if (pgctrl_int->ActivePage == tbsht_details)
         {
            edt_pat_surname->SetFocus();
         }
         bbtn_pat_delete->Enabled = true;
      }
      else
      {
         pnl_data->Enabled = false;
         pnl_questions->Enabled = false;
         bbtn_done->Enabled = false;
         bbtn_pat_delete->Enabled = false;
         if (pgctrl_pat->ActivePage == tbsht_pat_grid)
         {
            grd_pat->SetFocus();
         }
      }

   }
   else
   {
      dsrc_pat->AutoEdit = false;
      bbtn_pat_acceptClick(Sender);
      bbtn_pat_edit->Caption = "&Edit";
      emma_display_statusbar_message("", "", sphygmocor_white);
      pnl_data->Enabled = false;
      pnl_questions->Enabled = false;
      bbtn_done->Enabled = false;
      if (pgctrl_pat->ActivePage == tbsht_pat_grid)
      {
         grd_pat->SetFocus();
      }
   }   
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_patient::bbtn_pat_insertClick(TObject *Sender)
{
   TDataSet             *patient_table;
   TDataSource          *patient_dsrc;
   PATIENT_NUMBER_TYPE  patient_number;
   AnsiString           S;

   patient_dsrc = dbmgr_get_data_source(DBMGR_PATIENT_TABLE, false);

   if (patient_dsrc == NULL)
   {
      return;
   }
   // PM V9
   // Hide patient details in Clinical mode
   if (config_get_clinical_option())
   {
      pgctrl_pat->ActivePage = tbsht_pat_summary;
      bbtn_search_resetClick(Sender);
   }
   else
   {
      pgctrl_pat->ActivePage = tbsht_pat_grid;
   }
   pgctrl_int->ActivePage = tbsht_details;

   if (patient_dsrc->State == dsEdit)
   {
      bbtn_pat_acceptClick(Sender);
   }
   S = LoadStr(MSG_NEW_PATIENT_RECORD) +"\n\nThis patient will be entered into the\n" +multdb_get_active_name() +" Database Set.";
   if (MsgBox_confirmation(S, SCONFIRMATION) == ID_YES)
   {
      patient_table = dbmgr_get_dataset(DBMGR_PATIENT_TABLE, false);
      if (patient_table != NULL)
      {
         patient_number = patient_assign_new_number();
         if (patient_number)
         {
            try
            {
               patient_table->Insert();
               patient_table->FieldByName(PATIENT_SYSTEM_ID)->Value = config_get_system_id();
               patient_table->FieldByName(PATIENT_STUDY_ID)->Value = multdb_get_active_name();
               patient_table->FieldByName(PATIENT_NO)->AsInteger = patient_number;
               dtpck_pat_dob->Date = StrToDate(PATIENT_INIT_DATE);
               patient_table->FieldByName(PATIENT_DOB)->AsDateTime = dtpck_pat_dob->DateTime;
               pnl_data->Visible = true;
               pnl_data->Enabled = true;
               pnl_questions->Enabled = true;
               bbtn_done->Enabled = true;
               edt_pat_surname->SetFocus();
            }
            catch (Exception &exception)
            {
               MsgBox_show(TERROR,
                           MSG_DBREADWRITE_ERROR,
                           LoadStr(MSG_PATIENT_INSERT_ERROR),
                           MSG_PATIENT_INSERT_ERROR,
                           patient_get_error_str() +exception.Message);
               patient_table->Cancel();
               if (pgctrl_pat->ActivePage == tbsht_pat_grid)
               {
                  grd_pat->SetFocus();
               }
            }
         }
         else
         {
            MsgBox_show(TERROR,
                        MSG_PATIENT_ERROR,
                        LoadStr(MSG_PATIENT_NUMBER_ERROR),
                        MSG_PATIENT_NUMBER_ERROR,
                        LoadStr(MSG_PATIENT_NUMBER_ERROR));
         }
      }
   }
   else
   {
      if (pgctrl_pat->ActivePage == tbsht_pat_grid)
      {
         grd_pat->SetFocus();
      }
   }   
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_patient::bbtn_pat_acceptClick(TObject *Sender)
{
   TDataSet     *table;
   TDataSource  *dsrc;

   dsrc = dbmgr_get_data_source(DBMGR_PATIENT_TABLE, false);
   if (dsrc != NULL && (dsrc->State == dsInsert || dsrc->State == dsEdit))
   {
      if (MsgBox(MSG_ACCEPT_CHANGES, SCONFIRMATION, MB_YESNO | MB_ICONQUESTION) == IDYES)
      {
         // This is here as a workaround when the user selects update whilst in
         // the family name, first name fields
         edt_pat_oname->SetFocus();
         pgctrl_int->ActivePage = tbsht_details;
         table = dbmgr_get_dataset(DBMGR_PATIENT_TABLE, false);
         if (table != NULL)
         {
            try
            {
               if (dsrc->State == dsEdit)
               {
                  if (patient_validate_record(table))
                  {
                     audit_patient_edit(table);
                  }
               }
               else
               {
                  if (patient_validate_record(table))
                  {
                     if(audit_patient_insert(table))
                     {
                        lbl_nof_patients->Caption = " Patients: " + IntToStr(table->RecordCount);
                     }
                  }
               }
               // PM V9
               // Hide patient details in Clinical mode
               if (config_get_clinical_option())
               {
                  pgctrl_pat->ActivePage = tbsht_pat_summary;
               }
               else
               {
                  pgctrl_pat->ActivePage = tbsht_pat_grid;
               }
               pgctrl_patChange(Sender);
            }
            catch (Exception &exception)
            {
               MsgBox_show(TERROR,
                           MSG_DBREADWRITE_ERROR,
                           LoadStr(MSG_POST_ERROR),
                           MSG_POST_ERROR,
                           LoadStr(MSG_POST_ERROR) +patient_get_error_str() +exception.Message);
               table->Cancel();
               return;
            }
         }
      }
      else
      {
         bbtn_pat_cancelClick(Sender);
      }
   }   
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_patient::bbtn_pat_cancelClick(TObject *Sender)
{
   TDataSet *patient_table;
   TDataSource  *dsrc;

   dsrc = dbmgr_get_data_source(DBMGR_PATIENT_TABLE, false);
   if (dsrc != NULL && (dsrc->State == dsInsert || dsrc->State == dsEdit))
   {
      if (MsgBox(MSG_ABORT_CHANGES, SCONFIRMATION, MB_YESNO | MB_ICONQUESTION) == ID_YES)
      {
         // PM V9
         // Hide patient details in Clinical mode
         if (config_get_clinical_option())
         {
            pgctrl_pat->ActivePage = tbsht_pat_summary;
            if (dsrc->State == dsInsert)
            {
               bbtn_search_resetClick(Sender);
            }
         }
         else
         {
            pgctrl_pat->ActivePage = tbsht_pat_grid;
         }
         //pgctrl_patChange(Sender);
         patient_table = dbmgr_get_dataset(DBMGR_PATIENT_TABLE, false);
         if (patient_table != NULL)
         {
            patient_table->Cancel();
         }
      }
   }   
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_patient::bbtn_pat_deleteClick(TObject *Sender)
{
   TDataSet *patient_table;
   AnsiString S;

   S = patient_get_name();

   if (MsgBox(LoadStr(MSG_DELETE_PATIENT) + S, SCONFIRMATION,
              MB_YESNO | MB_ICONQUESTION) == ID_YES)
   {
      if (MsgBox(LoadStr(MSG_DELETE_MEAS1) + "\n\n" + LoadStr(MSG_ARE_YOU_SURE),
          SCONFIRMATION, MB_YESNO | MB_ICONQUESTION) == ID_YES)
      {
         patient_table = dbmgr_get_dataset(DBMGR_PATIENT_TABLE, false);
         if (patient_table != NULL)
         {
            try
            {
               // This is here as a workaround when the user selects delete whilst in
               // the reason for change field
               edt_pat_oname->SetFocus();
               if (audit_patient_delete(patient_table))
               {
                  S = "Deleted Patient " + IntToStr(patient_active.number);
                  // If the audit option is set, patients are never deleted
                  // the audit flag is simply set to DELETED
                  if(!config_get_audit_option())
                  {
                     patient_table->Delete();
                  }
                  log_write(S);
                  lbl_nof_patients->Caption = " Patients: " + IntToStr(patient_table->RecordCount);
                  multdb_set_delete_status(false);
                  if (patient_table->RecordCount == 0)
                  {
                     emma_disable_speed_buttons();
                     bbtn_pat_delete->Enabled = false;
                     pnl_data->Enabled = false;
                     pnl_questions->Enabled = false;
                     bbtn_done->Enabled = false;
                     lbl_pat_reason->Visible = false;
                     mm_pat_reason->Visible = false;
                     tbsht_pat_summary->Enabled = false;
                     frm_main->mnu_export->Enabled = false;
                     frm_main->mnu_export_database->Enabled = false;
                     frm_main->mnu_listing->Enabled = false;
                     frm_main->mnu_batch_print->Enabled = false;
                  }
                  // PM V9
                  // Hide patient details in Clinical mode
                  if (config_get_clinical_option())
                  {
                     pgctrl_pat->ActivePage = tbsht_pat_summary;
                     bbtn_search_resetClick(Sender);
                  }
                  else
                  {
                     pgctrl_pat->ActivePage = tbsht_pat_grid;
                  }
               }
            }
            catch (Exception &exception)
            {
               MsgBox_show(TERROR,
                           MSG_PATIENT_ERROR,
                           LoadStr(MSG_PATIENT_DELETE_ERROR),
                           MSG_PATIENT_DELETE_ERROR,
                           LoadStr(MSG_PATIENT_DELETE_ERROR) +exception.Message +patient_get_error_str());
               patient_table->Cancel();
               return;
            }
         }
      }
   }
   if (pgctrl_pat->ActivePage == tbsht_pat_grid)
   {
      grd_pat->SetFocus();
   }   
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_patient::bbtn_pat_auditClick(TObject *Sender)
{
   // Toggle the audit trail display and flag
   if (patient_audit_mode)
   {
      patient_audit_mode = false;
      audit_patient_hide();
   }
   else
   {
      patient_audit_mode = true;
      if (!audit_patient_show())
      {
         patient_audit_mode = false;
      }
   }
}
//---------------------------------------------------------------------------


