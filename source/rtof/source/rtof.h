//---------------------------------------------------------------------------

#ifndef rtofH
#define rtofH
#include <meas/pubserv.h>
#include <inc/std.h>
#include "capture.h"
//---------------------------------------------------------------------------

const int RTOF_MAX_PULSES	= CAPTURE_SECS_TOTAL * MAX_HR / 60.;

void rtof_reset(void);

#endif
