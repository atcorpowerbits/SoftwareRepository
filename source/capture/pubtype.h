/*
**
** Copyright (C) PWV MEDICAL PTY LTD, 1998
**
**
** FILE NAME     : CAPTURE\PUBTYPE.H
**
** PROJECT       : SCOR2000 SWCI
**
** OBJECT        : CAPTURE
**
** DESCRIPTION   : Definition of objects Public types.
**
** AUTHOR        : Peter Harpas
**
** DATE CREATED  : 8/2/2000
**
*/
#ifndef CAPTURE_PUBTYPE
#define CAPTURE_PUBTYPE
#include <inc/std.h>

typedef enum
{
   CAPTURE_PWM_INPUT_CHANNEL,
   CAPTURE_PWM_OUTPUT_CHANNEL_ONE,
   CAPTURE_PWM_OUTPUT_CHANNEL_TWO,
   CAPTURE_PWM_MAX_CALIBRATE_CHANNEL
} CAPTURE_PWM_CALIBRATE_CHANNEL_TYPE;

#endif
