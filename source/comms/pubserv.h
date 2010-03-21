/*
**
** Copyright (C) PWV MEDICAL PTY LTD, 1998
**
**
** FILE NAME     : COMMS\PUBSERV.H
**
** PROJECT       : S32 SWCI
**
** OBJECT        : COMMS (Communications)
**
** DESCRIPTION   : Definition of objects Public services.
**
** AUTHOR        : Peter Harpas
**
** DATE CREATED  : 18/05/98
**
*/
#ifndef COMMS_PUBSERV
#define COMMS_PUBSERV
#include <inc/std.h>
#include <meas/pubtype.h>
#include <comms/pubtype.h>


extern "C"
{

/*
** This service initialises the Communication object's internal data
** structures and must be invoked before any other service of the
** Communication object.
**
** A status value is returned to indicate the success, or otherwise, of the
** initialisation.
*/
bool comms_initialise(void);

/*
** This service releases all resources which have been allocated by the
** Communication object.
**
** After invoking this service, `comms_initialise' must be invoked before any
** other use may be made of the Communication object.
*/
void comms_destroy(void);

/*
** This service opens the comms port specified by 'port_id'.
**
** A status value is returned to indicate the success of opening the
** serial communications port.
**
*/
bool comms_open(COMMS_ID_TYPE port_id, bool disable_errors = false);

/*
** This service closes an already open comms port specified by 'port_id'.
*/
void comms_close(void);

void comms_reset(void);

bool comms_start(MEAS_ID_TYPE meas_id);

void comms_stop(void);

void comms_send(UINT16 *send_data, UCOUNT send_length);

void comms_send_event_mark(void);

void comms_detect_module(void);

bool comms_is_module_available(void);

bool comms_is_module_12bit(void);

bool comms_is_module_usb(void);

COMMS_FOOTSWITCH_STATUS_TYPE comms_get_footswitch_status(void);

void comms_reset_footswitch(void);

void comms_detect_ports(TStringList *port_list);

bool comms_port_exists(void);

void comms_display_error(void);

bool comms_request_hwconfig(void);

String comms_get_modes_string(void);

String comms_get_emod_string(void);
};
#endif

