#ifndef RTOF_PUBSERV
#define RTOF_PUBSERV

#include <rtof/pubtype.h>

bool rtof_initialise(void);

void rtof_destroy(void);

void rtof_set_defaults(void);

bool rtof_get(RTOF_RECORD_TYPE *rtof);

bool rtof_get_auto_capture(void);

bool rtof_add_sample(short int pressure_sample);

#endif
 