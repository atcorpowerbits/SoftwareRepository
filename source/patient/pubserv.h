#ifndef PATIENT_PUBSERV
#define PATIENT_PUBSERV

#include <inc/std.h>
#include <patient/pubtype.h>
#include <dbmgr/pubtype.h>
#include <meas/pubtype.h>
#include <scor/child.h>
#include <ADOdb.hpp>

bool patient_initialise(void);

void patient_destroy(void);

bool patient_can_close(void);

PATIENT_NUMBER_TYPE patient_get_number(void);

void patient_enable_post_message(bool enable);

void patient_enable_database_events(bool enable, bool enable_change);

bool patient_get(PATIENT_RECORD_TYPE *patient);

bool patient_set(PATIENT_RECORD_TYPE *patient);

bool patient_set(AnsiString     system_id,
                 AnsiString     study_id,
                 unsigned long  pat_no);

AnsiString patient_get_name(void);

AnsiString patient_get_age(void);

UCOUNT patient_get_age_at_date(TDateTime the_date);

AnsiString patient_get_study_id(void);

AnsiString patient_get_system_id(void);

bool patient_is_male(void);

void patient_update_measurement_count(void);

void patient_update_measurement_count(COUNT nof_measures);

UCOUNT  patient_get_nof_measurements(void);

void patient_update_count(void);

UCOUNT patient_get_count(void);

Child_Form *patient_get_form_pointer(void);

void patient_show(void);

void patient_listing_preview(bool is_print);

AnsiString patient_get_table_name(void);

bool patient_get_export_titles(String &export_title);

bool patient_get_export_data(String &export_data);

bool patient_populate_record(PATIENT_RECORD_TYPE *patient, TADOQuery *qry);

void patient_display_idle(bool is_idle);

MEAS_ID_TYPE patient_get_study_mode(void);

void patient_update_active_database(void);

String patient_get_error_str(void);
     
#endif




