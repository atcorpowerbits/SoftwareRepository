#ifndef REPORT_PUBSERV
#define REPORT_PUBSERV

#include <inc\std.h>
#include <meas\pubserv.h>
#include <patient\pubtype.h>
#include <scor\child.h>
#include <report\pubtype.h>

bool        report_initialise(void);
void        report_destroy(void);
Child_Form  *report_get_form_pointer(void);
bool        report_pwa_batch_print(TPWA                 *pwa_info,
                                   PATIENT_RECORD_TYPE  *patient,
                                   bool                 is_clinical);

bool        report_pwv_batch_print(TPWV                 *pwv_info,
                                   PATIENT_RECORD_TYPE  *patient);

CLINICAL_NORMALS_RANGE report_determine_ap_range(float ap, UCOUNT age, PWA_MEASURE_TYPE  MeasureType);
CLINICAL_NORMALS_RANGE report_determine_aixhr75_range(float aixhr75, UCOUNT age, PWA_MEASURE_TYPE  MeasureType);
CLINICAL_NORMALS_RANGE report_determine_aix_range(float aix, UCOUNT age, PWA_MEASURE_TYPE  MeasureType);
CLINICAL_NORMALS_RANGE report_determine_sevr_range(float sevr, float hr, UCOUNT age, PWA_MEASURE_TYPE  MeasureType);
CLINICAL_NORMALS_RANGE report_determine_ed_range(float ed, float hr, UCOUNT age, PWA_MEASURE_TYPE  MeasureType);
CLINICAL_NORMALS_RANGE report_determine_sp_range(float sp, UCOUNT age, PWA_MEASURE_TYPE  MeasureType);
CLINICAL_NORMALS_RANGE report_determine_pp_range(float pp, UCOUNT age, PWA_MEASURE_TYPE  MeasureType);
CLINICAL_NORMALS_RANGE report_determine_ppa_range(float ppa, UCOUNT age, PWA_MEASURE_TYPE  MeasureType);
int report_calculate_pwa_reference_score();
   
bool report_recalculate_all(TObject *Sender);

bool report_pwa_repeat_assessment(void);
#endif
