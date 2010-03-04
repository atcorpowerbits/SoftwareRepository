#ifndef ANALYSIS_PUBSERV
#define ANALYSIS_PUBSERV

#include <scor\child.h>

bool        analysis_initialise(void);
void        analysis_destroy(void);
Child_Form  *analysis_get_analysis_form_pointer(void);
Child_Form  *analysis_get_trend_form_pointer(void);
bool        analysis_get_audit_initialised();
bool        analysis_pwa_get_audit_initialised();
bool        analysis_pwv_get_audit_initialised();
#endif
