#ifndef EMR_PUBSERV
#define EMR_PUBSERV

#include <emr/pubtype.h>

bool emr_initialise(void);

void emr_destroy(void);

bool emr_read_inbound(String inbound);

bool emr_get_enabled(void);

bool emr_get_default_mode(void);

bool emr_get(EMR_RECORD_TYPE *emr);

String emr_get_inbound(void);

String emr_get_outbound(void);

EMR_EXPORT_TYPE emr_get_option(void);

bool emr_get_automatic(void);

bool emr_patient_is_active(void);

void emr_set_report_export(bool status);

bool emr_get_report_export(void);

void emr_export(void);

String emr_get_printer(void);

bool emr_get_editing(void);

bool emr_edit_active_patient(void);
#endif
 