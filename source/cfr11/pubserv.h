#ifndef CFR11_PUBSERV
#define CFR11_PUBSERV

#include <cfr11\pubtype.h>
#include <patient\pubtype.h>
#include <vcl\dbtables.hpp>
#include <meas\pubserv.h>

// Security functions
bool security_initialise();
void security_destroy();
bool security_show();
String security_get_username();
void security_lock_workstation();

// Audit general functions
String audit_patient_get_table_name();
String audit_pwa_get_table_name();
String audit_pwv_get_table_name();
bool audit_initialise();
void audit_destroy();
bool audit_copy_record(TDataSet *source_table, TDataSet *copy_table);

// Audit Patient functions
bool audit_patient_edit(TDataSet *patient_table);
bool audit_patient_insert(TDataSet *patient_table);
bool audit_patient_delete(TDataSet *patient_table);
bool audit_patient_validate_record(TDataSet *patient_table);
bool audit_patient_show();
void audit_patient_hide();

// Audit PWA functions
bool audit_update_pwa(TPWA *pwa_current, String reason);
bool audit_pwa_insert(TPWA *pwa_current, TDataSet *pwa_dataset, AUDIT_MODE AuditMode);
bool audit_pwa_edit(TDataSet *pwa_dataset);
bool audit_pwa_delete();
bool audit_pwa_validate_record(TPWA *pwa_current);
bool audit_pwa_show();
void audit_pwa_hide();

// Audit PWV functions
bool audit_update_pwv(TPWV *pwv_current, String reason);
bool audit_pwv_insert(TPWV *pwv_current, TDataSet *pwv_dataset, AUDIT_MODE AuditMode);
bool audit_pwv_edit(TDataSet *pwv_dataset);
bool audit_pwv_delete();
bool audit_pwv_validate_record(TPWV *pwv_current);
bool audit_pwv_show();
void audit_pwv_hide();
#endif
