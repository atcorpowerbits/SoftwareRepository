/*
**
** Copyright (C) PWV MEDICAL PTY LTD, 1998
**
**
** FILE NAME     : CONFIG\PUBSERV.H
**
** PROJECT       : S32 SWCI
**
** OBJECT        : CONFIG (Configuration)
**
** DESCRIPTION   : Definition of objects Public services.
**
** AUTHOR        : Peter Harpas
**
** DATE CREATED  : 18/05/98
**
*/
#ifndef CONFIG_PUBSERV
#define CONFIG_PUBSERV

#include <inc/std.h>
#include <comms/pubtype.h>
#include <config/pubtype.h>

/*
** This service initialises the Config object's internal data
** structures and must be invoked before any other service of the
** Config object.
**
** A status value is returned to indicate the success, or otherwise, of the
** initialisation.
*/
bool config_initialise(void);

/*
** This service releases all resources which have been allocated by the
** Config object.
**
** After invoking this service, `config_initialise' must be invoked before any
** other use may be made of the Config object.
*/
void config_destroy(void);

void config_show(void);

UCOUNT config_get_qc_pulse_height(void);

UTINY config_get_qc_pulse_height_variation(void);

UTINY config_get_qc_diastolic_variation(void);

COMMS_ID_TYPE config_get_comms_port(void);

AnsiString config_get_system_id(void);

bool config_require_database_pack(void);

void config_update_database_pack_date(void);

CONFIG_SYSTEM_OPTIONS config_get_system_options(void);

void config_disable_option(CONFIG_SYSTEM_OPTIONS coption);

TStringList *config_get_options_list(void);

UCOUNT config_get_pressure_upper_limit(void);

UTINY config_get_report_style(void);

UTINY config_get_report_screen(void);

UTINY config_get_ptiv(void);

void config_set_ptiv(UTINY);

UTINY config_get_srri(void);

String config_get_simulation_directory(void);

UTINY config_get_system_locale(void);

bool config_get_avi_option(void);

AnsiString config_get_report_title(void);

UINT32 config_get_tonometer(void);

bool config_get_audit_option(void);

void config_set_audit_option(bool audit_option);

void config_decode_command_line(void);

bool config_get_rtof(void);

bool config_get_auto_capture(void);

bool config_get_clinical_option(void);

String config_get_clinical_string(void);

bool config_get_clinical_aixhr75(void);

bool config_get_clinical_aix(void);

bool config_find_module(void);
#endif
