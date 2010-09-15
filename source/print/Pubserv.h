/*
**
** Copyright (C) PWV MEDICAL PTY LTD, 1998
**
**
** FILE NAME     : PRINT\PUBSERV.H
**
** PROJECT       : TITAN SWCI
**
** OBJECT        : PRINT (Printer)
**
** DESCRIPTION   : Definition of objects Public services.
**
** AUTHOR        : Peter Harpas
**
** DATE CREATED  : 18/05/98
**
*/
#ifndef PRINT_PUBSERV
#define PRINT_PUBSERV
#include <inc/std.h>
#include <vcl/printers.hpp>

extern "C"
{

/*
** This service initialises the Printer object's internal data
** structures and must be invoked before any other service of the
** Printer object.
**
** A status value is returned to indicate the success, or otherwise, of the
** initialisation.
*/
bool print_initialise(void);

/*
** This service releases all resources which have been allocated by the
** Printer object.
**
** After invoking this service, `print_initialise' must be invoked before any
** other use may be made of the Printer object.
*/
void print_destroy(void);

/*
** This returns the pointer to the Printer object.
*/
TPrinter *print_get_printer_ptr(void);

/*
** This checks whether the printer exist withing the system
*/
bool print_does_printer_exist();


void print_do_header(TRect       *print_rect,
                     AnsiString  title1,
                     AnsiString  title2);

void print_do_footer(TRect *print_rect, int maths_revision);

void print_do_patient_data(TRect *print_rect, UCOUNT age, bool is_invalid, String warning, String hint, int simulation);

void print_do_atcor_image(TRect   *print_rect);

bool print_batch_show(void);
}

#endif
