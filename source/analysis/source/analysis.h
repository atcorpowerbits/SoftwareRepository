//---------------------------------------------------------------------------
#ifndef analysisH
#define analysisH
#include <vcl.h>
#include <meas/pubserv.h>

// PM V9
const int ANALYSIS_MAX_PWA_MEASUREMENTS = 30;
const int ANALYSIS_MAX_PWV_MEASUREMENTS = 30;

const String ANALYSIS_DATETIME_FORMAT = "dd mmm yyyy, hh:nn:ss";
const String ANALYSIS_DATETIME_EXPORT_FORMAT = "ddmmmyyyy";
const String ANALYSIS_FONT_NAME = "Arial";

const String ANALYSIS_NOT_CALCULATED = "n/c";

extern AnsiString analysis_first_study;
extern AnsiString analysis_last_study;
extern AnsiString analysis_first_export;
extern AnsiString analysis_last_export;

extern bool analysis_audit_initialised;

void analysis_print_study_data(TRect *print_rect);

// Clear list with deletion objects
void Analysis_ClearList(TStrings *pList);
//---------------------------------------------------------------------------
#endif
