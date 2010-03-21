/*
**
** Copyright (C) PWV MEDICAL PTY LTD, 1998
**
**
** FILE NAME     : CAPTURE\PUBSERV.H
**
** PROJECT       : TITAN SWCI
**
** OBJECT        : CAPTURE
**
** DESCRIPTION   : Definition of objects Public services.
**
** AUTHOR        : Peter Harpas
**
** DATE CREATED  : 18/05/98
**
*/
#ifndef CAPTURE_PUBSERV
#define CAPTURE_PUBSERV
#include <inc/std.h>
#include <meas/pubtype.h>
#include <comms/pubtype.h>
#include <capture/pubtype.h>
#include "SyncObjs.hpp"

/*
** This service initialises the Capture object's internal data
** structures and must be invoked before any other service of the
** Capture object.
**
** A status value is returned to indicate the success, or otherwise, of the
** initialisation.
*/
bool capture_initialise(void);

/*
** This service releases all resources which have been allocated by the
** Capture object.
**
** After invoking this service, `capture_initialise' must be invoked before
** any other use may be made of the Capture object.
*/
void capture_destroy(void);

bool capture_show_form(MEAS_ID_TYPE meas_id);

void capture_simulation_get_data(void);

bool capture_simulation_start(void);

void capture_simulation_stop(void);

bool capture_add_sample(short int  psample,
                        bool       data_valid,
                        bool       check_fswitch);

bool capture_pwa_add_sample(short int pressure_sample,
                            bool      is_data_valid,
                            bool      check_fswitch);

bool capture_pwv_add_sample(short int  pressure_sample,
                            short int  ecg_sample,
                            bool       is_data_valid,
                            bool       check_fswitch);

bool capture_pwm_add_sample(short int   pressure_sample,
                            bool        is_data_valid,
                            bool        check_fswitch);

bool capture_hrv_add_sample(short int  *ecg_sample,
                            UTINY      ecg_buff_len,
                            bool       is_data_valid,
                            bool       check_fswitch);

bool capture_is_calibrated(void);

bool capture_pwm_get_autoscale_trends(void);

void capture_pwm_set_autoscale_trends(bool is_autoscale);

bool capture_from_tonometer(void);

void capture_set_from_tonometer(bool is_tonometer);

bool capture_do_loopback(void);

void capture_set_loopback(bool loopback);

bool capture_send_output(CAPTURE_PWM_CALIBRATE_CHANNEL_TYPE  op_channel);

COUNT capture_get_calibration_factor(CAPTURE_PWM_CALIBRATE_CHANNEL_TYPE  channel);

void capture_set_calibration_factor(CAPTURE_PWM_CALIBRATE_CHANNEL_TYPE  channel,
                                    UCOUNT                              cal_factor);

MEAS_ID_TYPE capture_get_current(void);
#endif
