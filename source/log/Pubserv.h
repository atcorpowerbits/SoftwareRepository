/*
**
** Copyright (C) PWV MEDICAL PTY LTD, 1998
**
**
** FILE NAME     : LOG\PUBSERV.H
**
** PROJECT       : TITAN SWCI
**
** OBJECT        : LOG
**
** DESCRIPTION   : Definition of objects Public services.
**
** AUTHOR        : Peter Harpas
**
** DATE CREATED  : 18/05/98
**
*/
#ifndef LOG_PUBSERV
#define LOG_PUBSERV
#include <inc/std.h>

/*
** This service initialises the Log object's internal data
** structures and must be invoked before any other service of the
** Log object.
**
** A status value is returned to indicate the success, or otherwise, of the
** initialisation.
*/
bool log_initialise(void);

/*
** This service releases all resources which have been allocated by the
** Log object.
**
** After invoking this service, `log_initialise' must be invoked before any
** other use may be made of the Log object.
*/
void log_destroy(void);

/*
** This service writes the string specified by 'log_msg' to the log
** file.
*/
void log_write(AnsiString  log_msg);

void log_write_start(void);

// Write a string picked up from Resource file to log file
void log_write(int log_number);

#endif

