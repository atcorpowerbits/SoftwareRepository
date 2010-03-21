//---------------------------------------------------------------------------
#ifndef captureH
#define captureH
#include <inc/std.h>
#include <meas/pubtype.h>
#include <capture/pubtype.h>

const int CAPTURE_MAX_RAW_VALUE      = 4000;
const int CAPTURE_MIN_RAW_VALUE      = 100;
const int CAPTURE_MIN_PULSE_HEIGHT   = 160;
const int CAPTURE_MAX_PULSE_HEIGHT   = 1000;
const int CAPTURE_DATA_THRESHOLD     = 120;
const int CAPTURE_INTERVAL           = 100;
const int CAPTURE_MIN_PULSE_HEIGHT_THRESHOLD       = 80; // for EM3, MM3

const int CAPTURE_OLD_MAX_RAW_VALUE      = 1000;
const int CAPTURE_OLD_MIN_RAW_VALUE      = 200;
const int CAPTURE_OLD_MIN_PULSE_HEIGHT   = 50;
const int CAPTURE_OLD_MAX_PULSE_HEIGHT   = 250;
const int CAPTURE_OLD_DATA_THRESHOLD     = 40;
const int CAPTURE_OLD_INTERVAL           = 25;
const int CAPTURE_OLD_MIN_PULSE_HEIGHT_THRESHOLD   = 20; //for EM2, MM2

const int CAPTURE_CAL_UPPER_PRESSURE_LIMIT = 250;
const int CAPTURE_CAL_MAX_RAW_VALUE        = 300;
const int CAPTURE_CAL_MIN_RAW_VALUE        = 20;
const int CAPTURE_CAL_MIN_PULSE_HEIGHT     = 16;
const int CAPTURE_CAL_MAX_PULSE_HEIGHT     = 160;
const int CAPTURE_CAL_DATA_THRESHOLD       = 10;

const int CAPTURE_SECS_TOTAL = 11;

const int CAPTURE_SECS_DISPLAY_RESET       = 120;
const int CAPTURE_SECS_DISPLAY_RESOLUTION  = 5;

const int CAPTURE_SECS_DISPLAY_RESCALE = 5;

const int CAPTURE_HRV_BUFFER           = 400;
const int CAPTURE_HRV_TREND_BUFFER     = 200;
const int CAPTURE_MAX_HRV_TREND        = 1600;
const int CAPTURE_MIN_HRV_TREND        = 400;

extern UCOUNT     capture_p_upper_limit;
extern UCOUNT     capture_raw_max;
extern UCOUNT     capture_raw_min;
extern UCOUNT     capture_raw_min_pulse_height;
extern UCOUNT     capture_raw_max_pulse_height;
extern UCOUNT     capture_raw_data_threshold;
extern UCOUNT     capture_raw_data_height_threshold;
extern int        capture_time;
extern  int       capture_raw_value;
extern int        capture_circbuff_index;
extern bool       capture_circbuff_full;
extern bool       capture_calibrated;
extern bool       capture_tonometer;
extern bool       capture_pwm_is_autoscale;
extern bool       capture_loopback;
extern COUNT      capture_pwm_calibration[];
extern short int  *capture_ch1_buff;
extern short int  *capture_ch2_buff;

void capture_reset(MEAS_ID_TYPE meas_id);
//---------------------------------------------------------------------------
#endif
