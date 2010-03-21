//---------------------------------------------------------------------------
#include <vcl.h>
#include <vcl\qrprev.hpp>
#pragma hdrstop

#include <scor/utils.h>
#include <dbmgr/pubserv.h>
#include <meas/pubserv.h>
#include <patient/pubserv.h>
#include <config/pubserv.h>
#include <multdb/pubserv.h>
#include <scor/form_main.h>
#include "form_patlist.h"
#include "attrib.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
Tfrm_patlist *frm_patlist;

DBMGR_ID_TYPE  table_id;
UCOUNT         total_patients;
UCOUNT         total_studies;
String         order;

const String PATIENT_LISTING_DATE_FORMAT = "dd mmm yyyy";
//---------------------------------------------------------------------------
__fastcall Tfrm_patlist::Tfrm_patlist(TComponent* Owner)
    : TForm(Owner)
{
   table_id = (DBMGR_ID_TYPE)0;
   total_patients = 0;
   total_studies = 0;
   order = "";

}
//---------------------------------------------------------------------------
bool __fastcall Tfrm_patlist::report_patlist_setup(void)
{
   TADOTable         *patient_table;
   TADOTable         *tbl_measure;
   MEAS_ID_TYPE   meas_id;
   bool           setup = false;
   AnsiString     date_str;
   TDateTime      dt;

   Screen->Cursor = crHourGlass;
   try
   {
      patient_table = dynamic_cast<TADOTable *>(dbmgr_get_dataset(DBMGR_PATIENT_TABLE, false));
      if (patient_table != NULL)
      {
         patient_enable_database_events(false, true);
         if (patient_table->IndexFieldNames != PATIENT_SURNAME)
         {
            dbmgr_select_index(DBMGR_PATIENT_TABLE,
                               PATIENT_SURNAME);

         }
         qckrp_pat_list->DataSet = patient_table;

         qrdb_surname->DataSet = patient_table;
         qrdb_surname->DataField = PATIENT_SURNAME;

         qrdb_firstname->DataSet = patient_table;
         qrdb_firstname->DataField = PATIENT_FIRST_NAME;

         qrdb_dob->DataSet = patient_table;
         qrdb_dob->DataField = PATIENT_DOB;

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

         tbl_measure = dynamic_cast<TADOTable *>(dbmgr_get_dataset(table_id, false));
         if (tbl_measure != NULL)
         {
            if (dbmgr_open(table_id, false))
            {
               total_studies = tbl_measure->RecordCount;
               total_patients = patient_get_count();
               setup = true;
               date_str = dt.CurrentDate().FormatString(PATIENT_LISTING_DATE_FORMAT);

               qrlbl_db_details->Caption = "AtCor Medical " +SOFTWARE_MODEL_TYPE +" "
                  +RELEASE_SOFTWARE_VERSION + config_get_clinical_string() + " (" +config_get_system_id() +") "
                  +IntToStr(MEAS_MATH_DATA_REVISION) +" " +multdb_get_active_name() +"  " +date_str;

               qrlbl_totals->Caption = "Patients : " +IntToStr((int)total_patients)
                  +"  Studies : " +IntToStr((int)total_studies);
            }
         }
      }
   }
   catch (...)
   {
      Screen->Cursor = crDefault;
      patient_enable_database_events(true, true);
   }
   Screen->Cursor = crDefault;
   return (setup);
}

void __fastcall Tfrm_patlist::report_patlist_cleanup(void)
{
   dbmgr_close(table_id, false);
   patient_enable_database_events(true, true);
}

void __fastcall Tfrm_patlist::qrbnd_sdetail_measuresBeforePrint(
      TQRCustomBand *Sender, bool &PrintBand)
{
   TDateTime dt_meas;
   TDataSet  *qry_meas;

   if (total_patients && total_studies)
   {
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
         if (qry_meas->RecordCount)
         {
            qrlbl_records->Caption = IntToStr(qry_meas->RecordCount);
            dt_meas = GetMeasureDateTime(qry_meas);
            qrlbl_first->Caption = dt_meas.FormatString(PATIENT_LISTING_DATE_FORMAT);

            qry_meas->Last();
            dt_meas = GetMeasureDateTime(qry_meas);
            qrlbl_last->Caption = dt_meas.FormatString(PATIENT_LISTING_DATE_FORMAT);
         }
         else
         {
            qrlbl_records->Caption = "Nil";
            qrlbl_first->Caption = "n/a";
            qrlbl_last->Caption = "n/a";
         }
         qry_meas->Close();
      }
   }
   else
   {
      qrlbl_records->Caption = "Nil";
      qrlbl_first->Caption = "n/a";
      qrlbl_last->Caption = "n/a";
   }
}
//---------------------------------------------------------------------------



void __fastcall Tfrm_patlist::qckrp_pat_listPreview(TObject *Sender)
{
   /*
   TQRStandardPreview *preview_form = new TQRStandardPreview(this);

   if (preview_form != NULL)
   {
      preview_form->WindowState = wsMaximized;
      preview_form->FormStyle = fsStayOnTop;
      preview_form->BorderIcons = BorderIcons - (TBorderIcons() << biMinimize);

      preview_form->QRPrinter = dynamic_cast<TQRPrinter*>(Sender);
      preview_form->Caption = "Patient Listing";
      preview_form->Show();
   }
   */
}
//---------------------------------------------------------------------------

