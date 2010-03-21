#include <vcl.h>
#include <vcl/dstring.h>

//---------------------------------------------------------------------------
#pragma hdrstop
//---------------------------------------------------------------------------
#include <math.h>
#include <report/pubserv.h>
#include <dbmgr/pubserv.h>
#include <multdb/pubserv.h>
#include <log/pubserv.h>
#include <patient/pubserv.h>
#include <meas/pubserv.h>
#include <msg/pubserv.h>
#include <config/pubserv.h>
#include <print/pubserv.h>
#include <export/pubserv.h>
#include <cfr11/pubserv.h>
#include <emr/pubserv.h>
#include <scor/form_main.h>
#include "form_report_pwa.h"
#include "form_report_pwv.h"
#include "form_report_pwm.h"
#include "form_report_hrv.h"
#include "jpeg.hpp"
#include "report.h"
#include "attrib.h"
#include "Registry.hpp"
#include "utils.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "TeeDraw3D"
#pragma link "GIFImage"
#pragma link "TeeOpenGL"
#pragma resource "*.dfm"

//---------------------------------------------------------------------------
Tfrm_report_pwa *frm_report_pwa;
const int REPORT_PANEL_AVERAGE_PRINT_HEIGHT = 162;
const int REPORT_PANEL_AVERAGE_PRINT_WIDTH = 640;
const int REPORT_PANEL_NORMALS_PRINT_HEIGHT = 343;
const int REPORT_PANEL_NORMALS_PRINT_HEIGHT2 = 170;
const int REPORT_PANEL_NORMALS_PRINT_WIDTH = 400; //864
const int REPORT_PRESSURES_GRAPH_PRINT_HEIGHT = 200;
const int REPORT_PRESSURES_GRAPH_PRINT_WIDTH = 200;
const int REPORT_REFERENCE_GRAPHS_PRINT_HEIGHT = 100;
const int REPORT_REFERENCE_GRAPHS_PRINT_WIDTH = 100;
const int REPORT_ACCEPTABLE_SHAPE_DEVIATION = 4;
const int REPORT_MIN_DISPLAYED_HEART_RATE = 40;
const int REPORT_MAX_DISPLAYED_HEART_RATE = 100;
const int REPORT_CLINICAL_CHART_CENTRE = 321;
const int REPORT_CLINICAL_AGE_GRAPH_PRINT_HEIGHT = 100;
const int REPORT_CLINICAL_HR_GRAPH_PRINT_HEIGHT = 50;
/* AP@HR75
float       ap_gradient_male = 0.19;
float       ap_gradient_female = 0.22;
float       ap_gradient = 0.0;
float       ap_y_intercept_male = -4.0;
float       ap_y_intercept_female = -1.8;
float       ap_y_intercept = 0.0;
float       ap_confidence_90_offset = 4.6; */
float       ap_gradient_male = 0.2403;
float       ap_gradient_female = 0.2708;
float       ap_gradient = 0.0;
float       ap_y_intercept_male = -4.4154;
float       ap_y_intercept_female = -2.581;
float       ap_y_intercept = 0.0;
float       ap_confidence_90_offset_male = 5.69;
float       ap_confidence_90_offset_female = 6.33;
float       ap_confidence_90_offset = 0.0;
float       aixhr75_coeff_1_male = -0.0066;
float       aixhr75_coeff_2_male = 1.1368;
float       aixhr75_y_intercept_male = -23.685;
float       aixhr75_coeff_1_female = -0.0066;
float       aixhr75_coeff_2_female = 1.0923;
float       aixhr75_y_intercept_female = -11.602;
float       aixhr75_coeff_1 = 0.0;
float       aixhr75_coeff_2 = 0.0;
float       aixhr75_y_intercept = 0.0;
float       aixhr75_confidence_90_offset = 11.5;
float       aix_coeff_1_male = -0.008;
float       aix_coeff_2_male = 1.31;
float       aix_y_intercept_male = -24.08;
float       aix_coeff_1_female = -0.011;
float       aix_coeff_2_female = 1.59;
float       aix_y_intercept_female = -20.7;
float       aix_coeff_1 = 0.0;
float       aix_coeff_2 = 0.0;
float       aix_y_intercept = 0.0;
float       aix_confidence_90_offset = 11.5;
float       sevr_coeff_1_male = 0.0365;
float       sevr_coeff_2_male = -6.9;
float       sevr_y_intercept_male = 454;
float       sevr_coeff_1_female = 0.0365;
float       sevr_coeff_2_female = -6.9;
float       sevr_y_intercept_female = 454;
float       sevr_coeff_1 = 0.0;
float       sevr_coeff_2 = 0.0;
float       sevr_y_intercept = 0.0;
float       sevr_confidence_90_offset_male = 25.5;
float       sevr_confidence_90_offset_female = 25.5;
float       sevr_confidence_90_offset = 0.0;
float       ed_pc_gradient = 0.31;
float       ed_ms_gradient = -1.81;
float       ed_gradient = 0.0;
float       ed_pc_y_intercept = 14.3;
float       ed_ms_y_intercept = 437.7;
float       ed_y_intercept = 0.0;
float       ed_pc_confidence_90_offset = 3.0;
float       ed_ms_confidence_90_offset = 26.5;
float       ed_confidence_90_offset = 0.0;
float       sp_gradient_male = 0.27;
float       sp_gradient_female = 0.381;
float       sp_gradient = 0.0;
float       sp_y_intercept_male = 99.69;
float       sp_y_intercept_female = 92.59;
float       sp_y_intercept = 0.0;
float       sp_confidence_90_offset_male = 11.9;
float       sp_confidence_90_offset_female = 13.5;
float       sp_confidence_90_offset = 0.0;
float       pp_gradient_male = 0.234;
float       pp_gradient_female = 0.39;
float       pp_gradient = 0.0;
float       pp_y_intercept_male = 23.59;
float       pp_y_intercept_female = 16.98;
float       pp_y_intercept = 0.0;
float       pp_confidence_90_offset_male = 8.7;
float       pp_confidence_90_offset_female = 10.1;
float       pp_confidence_90_offset = 0.0;
float       ppa_coeff_1_male = 0.01;
float       ppa_coeff_2_male = -2.09;
float       ppa_y_intercept_male = 206.6;
float       ppa_coeff_1_female = 0.02;
float       ppa_coeff_2_female = -2.53;
float       ppa_y_intercept_female = 204.63;
float       ppa_coeff_1 = 0.0;
float       ppa_coeff_2 = 0.0;
float       ppa_y_intercept = 0.0;
float       ppa_confidence_90_offset_male = 30.57;
float       ppa_confidence_90_offset_female = 25.86;
float       ppa_confidence_90_offset = 0.0;

String             pwm_title_string;
bool               pwa_first_time = true;
bool               report_initialised;
VAR_EXPORT UCOUNT  report_age;
COUNT              cv_age_ap;
float              ed_value;
float              report_aix_cutoff_high;
float              report_aix_cutoff_normal;
float              report_aix_cutoff_low;
float              report_aixhr75_cutoff_high;
float              report_aixhr75_cutoff_normal;
float              report_aixhr75_cutoff_low;
float              report_ap_cutoff_high;
float              report_ap_cutoff_normal;
float              report_ap_cutoff_low;
float              report_ed_cutoff_high;
float              report_ed_cutoff_normal;
float              report_ed_cutoff_low;
float              report_sevr_cutoff_high;
float              report_sevr_cutoff_normal;
float              report_sevr_cutoff_low;
float              report_sp_cutoff_high;
float              report_sp_cutoff_normal;
float              report_sp_cutoff_low;
float              report_pp_cutoff_high;
float              report_pp_cutoff_normal;
float              report_pp_cutoff_low;
float              report_ppa_cutoff_high;
float              report_ppa_cutoff_normal;
float              report_ppa_cutoff_low;

int                REPORT_CLINICAL_AGE_GRAPH_NORMAL_HEIGHT;
int                REPORT_CLINICAL_HR_GRAPH_NORMAL_HEIGHT;
int                REPORT_AVI_AVG_CENTRAL_NORMAL_HEIGHT;
int                avi_animation_count;
bool               avi_reflected_line = false;
bool               avi_forward_line = false;
bool               t1_line = false;
bool               t2_line = false;
bool               pwa_audit_mode = false;
bool               report_repeat_assessment = false;

bool report_initialise(void)
{
   report_age = 0;
   cv_age_ap = 0;
   report_aix_cutoff_high = 0.0;
   report_aix_cutoff_normal = 0.0;
   report_aix_cutoff_low = 0.0;
   report_aixhr75_cutoff_high = 0.0;
   report_aixhr75_cutoff_normal = 0.0;
   report_aixhr75_cutoff_low = 0.0;
   report_ap_cutoff_high = 0.0;
   report_ap_cutoff_normal = 0.0;
   report_ap_cutoff_low = 0.0;
   report_ed_cutoff_high = 0.0;
   report_ed_cutoff_normal = 0.0;
   report_ed_cutoff_low = 0.0;
   report_sevr_cutoff_high = 0.0;
   report_sevr_cutoff_low = 0.0;
   report_sevr_cutoff_normal = 0.0;
   report_sp_cutoff_high = 0.0;
   report_sp_cutoff_normal = 0.0;
   report_sp_cutoff_low = 0.0;
   report_pp_cutoff_high = 0.0;
   report_pp_cutoff_normal = 0.0;
   report_pp_cutoff_low = 0.0;
   report_ppa_cutoff_high = 0.0;
   report_ppa_cutoff_normal = 0.0;
   report_ppa_cutoff_low = 0.0;
   frm_report_pwv = NULL;
   frm_report_pwm = NULL;

   frm_report_pwa = new Tfrm_report_pwa(emma_get_main_form_pointer());
   if (frm_report_pwa != NULL)
   {
      report_initialised = true;
   }
   else
   {
      report_initialised = false;
      log_write("Report Failed Initialisation");
   }
   return (report_initialised);
}

void report_destroy(void)
{
   report_initialised = false;
}

Child_Form  *report_get_form_pointer()
{
   Child_Form    *report_form = NULL;
   MEAS_ID_TYPE  meas_mode;

   meas_mode = patient_get_study_mode();

   switch (meas_mode)
   {
      case MEAS_PWA_ID:
         report_form = frm_report_pwa;
         break;

      case MEAS_PWV_ID:
         if (frm_report_pwv == NULL)
         {
            frm_report_pwv = new Tfrm_report_pwv(emma_get_main_form_pointer());
         }
         report_form = frm_report_pwv;
         break;

      case MEAS_PWM_ID:
         if (frm_report_pwm == NULL)
         {
            frm_report_pwm = new Tfrm_report_pwm(emma_get_main_form_pointer());
         }
         report_form = frm_report_pwm;
         break;

      case MEAS_HRV_ID:
         if (frm_report_hrv == NULL)
         {
            frm_report_hrv = new Tfrm_report_hrv(emma_get_main_form_pointer());
         }
         report_form = frm_report_hrv;
         break;

      default:
         break;
   }
   return report_form;
}

CLINICAL_NORMALS_RANGE report_determine_ap_range(float ap, UCOUNT age, PWA_MEASURE_TYPE  MeasureType)
{
   float       ap_cutoff_high;
   float       ap_cutoff_low;
   float       ap_cutoff_normal;

   CLINICAL_NORMALS_RANGE  ap_normals_range;

   ap_normals_range = RANGE_UNDEFINED;

   report_ap_cutoff_high = 0.0;
   report_ap_cutoff_low = 0.0;
   report_ap_cutoff_normal = 0.0;

   if (patient_is_male())
   {
      ap_gradient = ap_gradient_male;
      ap_y_intercept = ap_y_intercept_male;
      ap_confidence_90_offset = ap_confidence_90_offset_male;
   }
   else
   {
      ap_gradient = ap_gradient_female;
      ap_y_intercept = ap_y_intercept_female;
      ap_confidence_90_offset = ap_confidence_90_offset_female;
   }

   // Do not display a range for young patients, carotid or aortic measurements
   if (age < PATIENT_YOUNG_AGE || MeasureType != PWA_RADIAL)
   {
      ap_normals_range = RANGE_UNDEFINED;
      return ap_normals_range;
   }

   ap_cutoff_high = ap_gradient * age + ap_y_intercept + ap_confidence_90_offset;
   ap_cutoff_low = ap_gradient * age + ap_y_intercept - ap_confidence_90_offset;
   ap_cutoff_normal = ap_gradient * age + ap_y_intercept;

   report_ap_cutoff_high = math_Round(ap_cutoff_high);
   report_ap_cutoff_low = math_Round(ap_cutoff_low);
   report_ap_cutoff_normal = math_Round(ap_cutoff_normal);

   if (ap > ap_cutoff_high)
   {
      ap_normals_range = RANGE_HIGH;
   }
   else if (ap < ap_cutoff_low)
   {
      ap_normals_range = RANGE_LOW;
   }
   else if (ap > ap_cutoff_normal &&
            ap <= ap_cutoff_high)
   {
      ap_normals_range = RANGE_NORMAL_HIGH;
   }
   else if (ap >= ap_cutoff_low &&
            ap <= ap_cutoff_normal)
   {
      ap_normals_range = RANGE_NORMAL_LOW;
   }
   return (ap_normals_range);
}

CLINICAL_NORMALS_RANGE report_determine_aixhr75_range(float aixhr75, UCOUNT age, PWA_MEASURE_TYPE  MeasureType)
{
   float       aixhr75_cutoff_high;
   float       aixhr75_cutoff_low;
   float       aixhr75_cutoff_normal;

   CLINICAL_NORMALS_RANGE  aixhr75_normals_range;

   aixhr75_normals_range = RANGE_UNDEFINED;

   report_aixhr75_cutoff_high = 0.0;
   report_aixhr75_cutoff_low = 0.0;
   report_aixhr75_cutoff_normal = 0.0;

   if (patient_is_male())
   {
      aixhr75_coeff_1 = aixhr75_coeff_1_male;
      aixhr75_coeff_2 = aixhr75_coeff_2_male;
      aixhr75_y_intercept = aixhr75_y_intercept_male;
   }
   else
   {
      aixhr75_coeff_1 = aixhr75_coeff_1_female;
      aixhr75_coeff_2 = aixhr75_coeff_2_female;
      aixhr75_y_intercept = aixhr75_y_intercept_female;
   }

   // Do not display a range for young patients, carotid or aortic measurements
   if (age < PATIENT_YOUNG_AGE || MeasureType != PWA_RADIAL)
   {
      aixhr75_normals_range = RANGE_UNDEFINED;
      return aixhr75_normals_range;
   }

   if (age > 0 && age < 150)
   {
      aixhr75_cutoff_high = ((aixhr75_coeff_1) * (age * age)) + (aixhr75_coeff_2 * age) + aixhr75_y_intercept + aixhr75_confidence_90_offset;
      aixhr75_cutoff_low = ((aixhr75_coeff_1) * (age * age)) + (aixhr75_coeff_2 * age) + aixhr75_y_intercept - aixhr75_confidence_90_offset;
      aixhr75_cutoff_normal = ((aixhr75_coeff_1) * (age * age)) + (aixhr75_coeff_2 * age) + aixhr75_y_intercept;

      report_aixhr75_cutoff_high = math_Round(aixhr75_cutoff_high);
      report_aixhr75_cutoff_low = math_Round(aixhr75_cutoff_low);
      report_aixhr75_cutoff_normal = math_Round(aixhr75_cutoff_normal);
      if (aixhr75 > aixhr75_cutoff_high)
      {
         aixhr75_normals_range = RANGE_HIGH;
      }
      else if (aixhr75 < aixhr75_cutoff_low)
      {
         aixhr75_normals_range = RANGE_LOW;
      }
      else if (aixhr75 > aixhr75_cutoff_normal &&
               aixhr75 <= aixhr75_cutoff_high)
      {
         aixhr75_normals_range = RANGE_NORMAL_HIGH;
      }
      else if (aixhr75 >= aixhr75_cutoff_low &&
               aixhr75 <= aixhr75_cutoff_normal)
      {
         aixhr75_normals_range = RANGE_NORMAL_LOW;
      }
   }
   return (aixhr75_normals_range);
}
// PM V9
CLINICAL_NORMALS_RANGE report_determine_aix_range(float aix, UCOUNT age, PWA_MEASURE_TYPE  MeasureType)
{
   float       aix_cutoff_high;
   float       aix_cutoff_low;
   float       aix_cutoff_normal;

   CLINICAL_NORMALS_RANGE  aix_normals_range;

   aix_normals_range = RANGE_UNDEFINED;

   report_aix_cutoff_high = 0.0;
   report_aix_cutoff_low = 0.0;
   report_aix_cutoff_normal = 0.0;

   if (patient_is_male())
   {
      aix_coeff_1 = aix_coeff_1_male;
      aix_coeff_2 = aix_coeff_2_male;
      aix_y_intercept = aix_y_intercept_male;
   }
   else
   {
      aix_coeff_1 = aix_coeff_1_female;
      aix_coeff_2 = aix_coeff_2_female;
      aix_y_intercept = aix_y_intercept_female;
   }

   // Do not display a range for young patients, carotid or aortic measurements
   if (age < PATIENT_YOUNG_AGE || MeasureType != PWA_RADIAL)
   {
      aix_normals_range = RANGE_UNDEFINED;
      return aix_normals_range;
   }

   if (age > 0 && age < 150)
   {
      aix_cutoff_high = ((aix_coeff_1) * (age * age)) + (aix_coeff_2 * age) + aix_y_intercept + aix_confidence_90_offset;
      aix_cutoff_low = ((aix_coeff_1) * (age * age)) + (aix_coeff_2 * age) + aix_y_intercept - aix_confidence_90_offset;
      aix_cutoff_normal = ((aix_coeff_1) * (age * age)) + (aix_coeff_2 * age) + aix_y_intercept;

      report_aix_cutoff_high = math_Round(aix_cutoff_high);
      report_aix_cutoff_low = math_Round(aix_cutoff_low);
      report_aix_cutoff_normal = math_Round(aix_cutoff_normal);
      if (aix > aix_cutoff_high)
      {
         aix_normals_range = RANGE_HIGH;
      }
      else if (aix < aix_cutoff_low)
      {
         aix_normals_range = RANGE_LOW;
      }
      else if (aix > aix_cutoff_normal &&
               aix <= aix_cutoff_high)
      {
         aix_normals_range = RANGE_NORMAL_HIGH;
      }
      else if (aix >= aix_cutoff_low &&
               aix <= aix_cutoff_normal)
      {
         aix_normals_range = RANGE_NORMAL_LOW;
      }
   }
   return (aix_normals_range);
}

CLINICAL_NORMALS_RANGE report_determine_sevr_range(float sevr, float hr, UCOUNT age, PWA_MEASURE_TYPE  MeasureType)
{
   float       sevr_cutoff_high;
   float       sevr_cutoff_low;
   float       sevr_cutoff_medium;
   CLINICAL_NORMALS_RANGE  sevr_normals_range;

   report_sevr_cutoff_high = 0.0;
   report_sevr_cutoff_low = 0.0;
   report_sevr_cutoff_normal = 0.0;
   sevr_normals_range = RANGE_UNDEFINED;

   if (patient_is_male())
   {
      sevr_coeff_1 = sevr_coeff_1_male;
      sevr_coeff_2 = sevr_coeff_2_male;
      sevr_y_intercept = sevr_y_intercept_male;
      sevr_confidence_90_offset = sevr_confidence_90_offset_male;
   }
   else
   {
      sevr_coeff_1 = sevr_coeff_1_female;
      sevr_coeff_2 = sevr_coeff_2_female;
      sevr_y_intercept = sevr_y_intercept_female;
      sevr_confidence_90_offset = sevr_confidence_90_offset_female;
   }

   // Do not display a range for young patients, carotid or aortic measurements
   if (age < PATIENT_YOUNG_AGE || MeasureType != PWA_RADIAL)
   {
      sevr_normals_range = RANGE_UNDEFINED;
      report_sevr_cutoff_high = 180;
      report_sevr_cutoff_low = 125;
      report_sevr_cutoff_normal = 150;
      return sevr_normals_range;
   }

   if (hr < REPORT_MIN_DISPLAYED_HEART_RATE)
   {
      hr = REPORT_MIN_DISPLAYED_HEART_RATE;
   }
   else if (hr > REPORT_MAX_DISPLAYED_HEART_RATE)
   {
      hr = REPORT_MAX_DISPLAYED_HEART_RATE;
   }
   
   sevr_cutoff_high = ((sevr_coeff_1) * (hr * hr)) + (sevr_coeff_2 * hr) + sevr_y_intercept + sevr_confidence_90_offset;
   sevr_cutoff_low = ((sevr_coeff_1) * (hr * hr)) + (sevr_coeff_2 * hr) + sevr_y_intercept - sevr_confidence_90_offset;
   sevr_cutoff_medium = ((sevr_coeff_1) * (hr * hr)) + (sevr_coeff_2 * hr) + sevr_y_intercept;

   report_sevr_cutoff_high = math_Round(sevr_cutoff_high);
   report_sevr_cutoff_low = math_Round(sevr_cutoff_low);
   report_sevr_cutoff_normal = math_Round(sevr_cutoff_medium);

   if (sevr < sevr_cutoff_low)
   {
      sevr_normals_range = RANGE_LOW;
   }
   else if (sevr > sevr_cutoff_high)
   {
      sevr_normals_range = RANGE_HIGH;
   }
   else if (sevr >= sevr_cutoff_low &&
            sevr <= sevr_cutoff_medium)
   {
      sevr_normals_range = RANGE_NORMAL_LOW;
   }
   else if (sevr > sevr_cutoff_medium &&
            sevr <= sevr_cutoff_high)
   {
      sevr_normals_range = RANGE_NORMAL_HIGH;
   }
   return (sevr_normals_range);
}

CLINICAL_NORMALS_RANGE report_determine_ed_range(float ed, float hr, UCOUNT age, PWA_MEASURE_TYPE  MeasureType)
{
   float       ed_cutoff_high;
   float       ed_cutoff_very_high;
   float       ed_cutoff_low;
   float       ed_cutoff_very_low;
   float       ed_cutoff_medium;

   CLINICAL_NORMALS_RANGE  ed_normals_range;

   report_ed_cutoff_high = 0.0;
   report_ed_cutoff_low = 0.0;
   ed_normals_range = RANGE_UNDEFINED;

   ed_gradient = ed_pc_gradient;
   ed_y_intercept = ed_pc_y_intercept;
   ed_confidence_90_offset = ed_pc_confidence_90_offset;

   // Do not display a range for young patients, carotid or aortic measurements
   if (age < PATIENT_YOUNG_AGE || MeasureType != PWA_RADIAL)
   {
      ed_normals_range = RANGE_UNDEFINED;
      return ed_normals_range;
   }

   if (hr < REPORT_MIN_DISPLAYED_HEART_RATE)
   {
      hr = REPORT_MIN_DISPLAYED_HEART_RATE;
   }
   else if (hr > REPORT_MAX_DISPLAYED_HEART_RATE)
   {
      hr = REPORT_MAX_DISPLAYED_HEART_RATE;
   }

   ed_cutoff_high = ed_gradient * hr + ed_y_intercept + ed_confidence_90_offset;
   ed_cutoff_low = ed_gradient * hr + ed_y_intercept - ed_confidence_90_offset;
   ed_cutoff_medium = ed_gradient * hr + ed_y_intercept;

   // very high and very low are the 95% confidence offsets
   ed_cutoff_very_high = ed_cutoff_high + ed_confidence_90_offset / 18;
   ed_cutoff_very_low = ed_cutoff_low - ed_confidence_90_offset / 18;

   report_ed_cutoff_high = math_Round(ed_cutoff_high);
   report_ed_cutoff_normal = math_Round(ed_cutoff_medium);
   report_ed_cutoff_low = math_Round(ed_cutoff_low);

   if (ed > ed_cutoff_very_high)
   {
      ed_normals_range = RANGE_VERY_HIGH;
   }
   else if (ed > ed_cutoff_high)
   {
      ed_normals_range = RANGE_HIGH;
   }
   else if (ed < ed_cutoff_very_low)
   {
      ed_normals_range = RANGE_VERY_LOW;
   }
   else if (ed < ed_cutoff_low)
   {
      ed_normals_range = RANGE_LOW;
   }
   else if (ed >= ed_cutoff_low &&
            ed <= ed_cutoff_medium)
   {
      ed_normals_range = RANGE_NORMAL_LOW;
   }
   else if (ed > ed_cutoff_medium &&
            ed <= ed_cutoff_high)
   {
      ed_normals_range = RANGE_NORMAL_HIGH;
   }
   return (ed_normals_range);
}

CLINICAL_NORMALS_RANGE report_determine_sp_range(float sp, UCOUNT age, PWA_MEASURE_TYPE  MeasureType)
{
   float       sp_cutoff_high;
   float       sp_cutoff_low;
   float       sp_cutoff_normal;

   CLINICAL_NORMALS_RANGE  sp_normals_range;

   report_sp_cutoff_high = 0.0;
   report_sp_cutoff_low = 0.0;
   report_sp_cutoff_normal = 0.0;
   sp_normals_range = RANGE_UNDEFINED;

   if (patient_is_male())
   {
      sp_gradient = sp_gradient_male;
      sp_y_intercept = sp_y_intercept_male;
      sp_confidence_90_offset = sp_confidence_90_offset_male;
   }
   else
   {
      sp_gradient = sp_gradient_female;
      sp_y_intercept = sp_y_intercept_female;
      sp_confidence_90_offset = sp_confidence_90_offset_female;
   }

   // Do not display a range for young patients, carotid or aortic measurements
   if (age < PATIENT_YOUNG_AGE || MeasureType != PWA_RADIAL)
   {
      sp_normals_range = RANGE_UNDEFINED;
      return sp_normals_range;
   }

   sp_cutoff_high = sp_gradient * age + sp_y_intercept + sp_confidence_90_offset;
   sp_cutoff_low = sp_gradient * age + sp_y_intercept - sp_confidence_90_offset;
   sp_cutoff_normal = sp_gradient * age + sp_y_intercept;

   report_sp_cutoff_high = math_Round(sp_cutoff_high);
   report_sp_cutoff_low = math_Round(sp_cutoff_low);
   report_sp_cutoff_normal = math_Round(sp_cutoff_normal);

   if (sp > sp_cutoff_high)
   {
      sp_normals_range = RANGE_HIGH;
   }
   else if (sp < sp_cutoff_low)
   {
      sp_normals_range = RANGE_LOW;
   }
   else if (sp > sp_cutoff_normal &&
            sp <= sp_cutoff_high)
   {
      sp_normals_range = RANGE_NORMAL_HIGH;
   }
   else if (sp >= sp_cutoff_low &&
            sp <= sp_cutoff_normal)
   {
      sp_normals_range = RANGE_NORMAL_LOW;
   }
   return (sp_normals_range);
}

CLINICAL_NORMALS_RANGE report_determine_pp_range(float pp, UCOUNT age, PWA_MEASURE_TYPE  MeasureType)
{
   float       pp_cutoff_high;
   float       pp_cutoff_low;
   float       pp_cutoff_normal;

   CLINICAL_NORMALS_RANGE  pp_normals_range;

   report_pp_cutoff_high = 0.0;
   report_pp_cutoff_low = 0.0;
   report_pp_cutoff_normal = 0.0;
   pp_normals_range = RANGE_UNDEFINED;
      
   if (patient_is_male())
   {
      pp_gradient = pp_gradient_male;
      pp_y_intercept = pp_y_intercept_male;
      pp_confidence_90_offset = pp_confidence_90_offset_male;
   }
   else
   {
      pp_gradient = pp_gradient_female;
      pp_y_intercept = pp_y_intercept_female;
      pp_confidence_90_offset = pp_confidence_90_offset_female;
   }

   // Do not display a range for young patients, carotid or aortic measurements
   if (age < PATIENT_YOUNG_AGE || MeasureType != PWA_RADIAL)
   {
      pp_normals_range = RANGE_UNDEFINED;
      return pp_normals_range;
   }

   pp_cutoff_high = pp_gradient * age + pp_y_intercept + pp_confidence_90_offset;
   pp_cutoff_low = pp_gradient * age + pp_y_intercept - pp_confidence_90_offset;
   pp_cutoff_normal = pp_gradient * age + pp_y_intercept;

   report_pp_cutoff_high = math_Round(pp_cutoff_high);
   report_pp_cutoff_low = math_Round(pp_cutoff_low);
   report_pp_cutoff_normal = math_Round(pp_cutoff_normal);

   if (pp > pp_cutoff_high)
   {
      pp_normals_range = RANGE_HIGH;
   }
   else if (pp < pp_cutoff_low)
   {
      pp_normals_range = RANGE_LOW;
   }
   else if (pp > pp_cutoff_normal &&
            pp <= pp_cutoff_high)
   {
      pp_normals_range = RANGE_NORMAL_HIGH;
   }
   else if (pp >= pp_cutoff_low &&
            pp <= pp_cutoff_normal)
   {
      pp_normals_range = RANGE_NORMAL_LOW;
   }
   return (pp_normals_range);
}

CLINICAL_NORMALS_RANGE report_determine_ppa_range(float ppa, UCOUNT age, PWA_MEASURE_TYPE  MeasureType)
{
   float       ppa_cutoff_high;
   float       ppa_cutoff_low;
   float       ppa_cutoff_normal;

   CLINICAL_NORMALS_RANGE  ppa_normals_range;

   ppa_normals_range = RANGE_UNDEFINED;

   report_ppa_cutoff_high = 0.0;
   report_ppa_cutoff_low = 0.0;
   report_ppa_cutoff_normal = 0.0;

   if (patient_is_male())
   {
      ppa_coeff_1 = ppa_coeff_1_male;
      ppa_coeff_2 = ppa_coeff_2_male;
      ppa_y_intercept = ppa_y_intercept_male;
      ppa_confidence_90_offset = ppa_confidence_90_offset_male;
   }
   else
   {
      ppa_coeff_1 = ppa_coeff_1_female;
      ppa_coeff_2 = ppa_coeff_2_female;
      ppa_y_intercept = ppa_y_intercept_female;
      ppa_confidence_90_offset = ppa_confidence_90_offset_female;
   }

   // Do not display a range for young patients, carotid or aortic measurements
   if (age < PATIENT_YOUNG_AGE || MeasureType != PWA_RADIAL)
   {
      ppa_normals_range = RANGE_UNDEFINED;
      return ppa_normals_range;
   }

   ppa_cutoff_high = ((ppa_coeff_1) * (age * age)) + (ppa_coeff_2 * age) + ppa_y_intercept + ppa_confidence_90_offset;
   ppa_cutoff_low = ((ppa_coeff_1) * (age * age)) + (ppa_coeff_2 * age) + ppa_y_intercept - ppa_confidence_90_offset;
   ppa_cutoff_normal = ((ppa_coeff_1) * (age * age)) + (ppa_coeff_2 * age) + ppa_y_intercept;

   report_ppa_cutoff_high = math_Round(ppa_cutoff_high);
   report_ppa_cutoff_low = math_Round(ppa_cutoff_low);
   report_ppa_cutoff_normal = math_Round(ppa_cutoff_normal);
   if (ppa > ppa_cutoff_high)
   {
      ppa_normals_range = RANGE_HIGH;
   }
   else if (ppa < ppa_cutoff_low)
   {
      ppa_normals_range = RANGE_LOW;
   }
   else if (ppa > ppa_cutoff_normal &&
            ppa <= ppa_cutoff_high)
   {
      ppa_normals_range = RANGE_NORMAL_HIGH;
   }
   else if (ppa >= ppa_cutoff_low &&
            ppa <= ppa_cutoff_normal)
   {
      ppa_normals_range = RANGE_NORMAL_LOW;
   }

   return (ppa_normals_range);
}

int report_determine_ap_relative_index(float ap, UCOUNT age, PWA_MEASURE_TYPE  MeasureType)
{
   float       ap_cutoff_high;
   float       ap_cutoff_low;
   float       tmp_calc;
   int         ap_relative_index;

   ap_relative_index = 0;

   if (ap == DEFAULT_VALUE)
   {
      return ap_relative_index;
   }

   if (patient_is_male())
   {
      ap_gradient = ap_gradient_male;
      ap_y_intercept = ap_y_intercept_male;
      ap_confidence_90_offset = ap_confidence_90_offset_male;
   }
   else
   {
      ap_gradient = ap_gradient_female;
      ap_y_intercept = ap_y_intercept_female;
      ap_confidence_90_offset = ap_confidence_90_offset_female;
   }

   // Do not display a range for young patients, carotid or aortic measurements
   if (age < PATIENT_YOUNG_AGE || MeasureType != PWA_RADIAL)
   {
      return ap_relative_index;
   }

   ap_cutoff_high = ap_gradient * age + ap_y_intercept + ap_confidence_90_offset;
   ap_cutoff_low = ap_gradient * age + ap_y_intercept - ap_confidence_90_offset;

   tmp_calc = (((ap - ap_cutoff_low) / (ap_cutoff_high - ap_cutoff_low)) * 100.0);
   ap_relative_index = tmp_calc;
   if (ap_relative_index == 0)
   {
      ap_relative_index = 1;
   }
   return (ap_relative_index);
}


int report_determine_aixhr75_relative_index(float aixhr75, UCOUNT age, PWA_MEASURE_TYPE  MeasureType)
{
   float       aixhr75_cutoff_high;
   float       aixhr75_cutoff_low;
   float       tmp_calc;
   int         aixhr75_relative_index;

   aixhr75_relative_index = 0;

   if (aixhr75 == DEFAULT_VALUE)
   {
      return aixhr75_relative_index;
   }

   if (patient_is_male())
   {
      aixhr75_coeff_1 = aixhr75_coeff_1_male;
      aixhr75_coeff_2 = aixhr75_coeff_2_male;
      aixhr75_y_intercept = aixhr75_y_intercept_male;
   }
   else
   {
      aixhr75_coeff_1 = aixhr75_coeff_1_female;
      aixhr75_coeff_2 = aixhr75_coeff_2_female;
      aixhr75_y_intercept = aixhr75_y_intercept_female;
   }

   // Do not display a range for young patients, carotid or aortic measurements
   if (age < PATIENT_YOUNG_AGE || MeasureType != PWA_RADIAL)
   {
      return aixhr75_relative_index;
   }

   if (age > 0 && age < 150)
   {
      aixhr75_cutoff_high = ((aixhr75_coeff_1) * (age * age)) + (aixhr75_coeff_2 * age) + aixhr75_y_intercept + aixhr75_confidence_90_offset;
      aixhr75_cutoff_low = ((aixhr75_coeff_1) * (age * age)) + (aixhr75_coeff_2 * age) + aixhr75_y_intercept - aixhr75_confidence_90_offset;

      tmp_calc = (((aixhr75 - aixhr75_cutoff_low) / (aixhr75_cutoff_high - aixhr75_cutoff_low)) * 100.0);
      aixhr75_relative_index = tmp_calc;
      if (aixhr75_relative_index == 0)
      {
         aixhr75_relative_index = 1;
      }
   }
   return (aixhr75_relative_index);
}

int report_determine_sevr_relative_index(float sevr, float hr, UCOUNT age, PWA_MEASURE_TYPE  MeasureType)
{
   float       sevr_cutoff_high;
   float       sevr_cutoff_low;
   float       tmp_calc;
   int         sevr_relative_index;

   sevr_relative_index = 0;

   if (sevr == DEFAULT_VALUE || hr == DEFAULT_VALUE)
   {
      return sevr_relative_index;
   }

   if (patient_is_male())
   {
      sevr_coeff_1 = sevr_coeff_1_male;
      sevr_coeff_2 = sevr_coeff_2_male;
      sevr_y_intercept = sevr_y_intercept_male;
      sevr_confidence_90_offset = sevr_confidence_90_offset_male;
   }
   else
   {
      sevr_coeff_1 = sevr_coeff_1_female;
      sevr_coeff_2 = sevr_coeff_2_female;
      sevr_y_intercept = sevr_y_intercept_female;
      sevr_confidence_90_offset = sevr_confidence_90_offset_female;
   }

   // Do not display a range for young patients, carotid or aortic measurements
   if (age < PATIENT_YOUNG_AGE || MeasureType != PWA_RADIAL)
   {
      return sevr_relative_index;
   }

   sevr_cutoff_high = ((sevr_coeff_1) * (hr * hr)) + (sevr_coeff_2 * hr) + sevr_y_intercept + sevr_confidence_90_offset;
   sevr_cutoff_low = ((sevr_coeff_1) * (hr * hr)) + (sevr_coeff_2 * hr) + sevr_y_intercept - sevr_confidence_90_offset;

   tmp_calc = (((sevr_cutoff_high - sevr) / (sevr_cutoff_high - sevr_cutoff_low)) * 100.0);
   sevr_relative_index = tmp_calc;
   if (sevr_relative_index == 0)
   {
      sevr_relative_index = 1;
   }
   return (sevr_relative_index);

}

int report_determine_ed_relative_index(float ed, float hr, UCOUNT age, PWA_MEASURE_TYPE  MeasureType)
{
   float       ed_cutoff_high;
   float       ed_cutoff_low;
   float       tmp_calc;
   int         ed_relative_index;

   ed_relative_index = 0;

   if (ed == DEFAULT_VALUE || hr == DEFAULT_VALUE)
   {
      return ed_relative_index;
   }

   ed_gradient = ed_pc_gradient;
   ed_y_intercept = ed_pc_y_intercept;
   ed_confidence_90_offset = ed_pc_confidence_90_offset;

   // Do not display a range for young patients, carotid or aortic measurements
   if (age < PATIENT_YOUNG_AGE || MeasureType != PWA_RADIAL)
   {
      return ed_relative_index;
   }

   ed_cutoff_high = ed_gradient * hr + ed_y_intercept + ed_confidence_90_offset;
   ed_cutoff_low = ed_gradient * hr + ed_y_intercept - ed_confidence_90_offset;

   tmp_calc = (((ed - ed_cutoff_low) / (ed_cutoff_high - ed_cutoff_low)) * 100.0);
   ed_relative_index = tmp_calc;
   if (ed_relative_index == 0)
   {
      ed_relative_index = 1;
   }
   return (ed_relative_index);

}

int report_determine_sp_relative_index(float sp, UCOUNT age, PWA_MEASURE_TYPE  MeasureType)
{
   float       sp_cutoff_high;
   float       sp_cutoff_low;
   float       tmp_calc;
   int         sp_relative_index;

   sp_relative_index = 0;

   if (sp == DEFAULT_VALUE)
   {
      return sp_relative_index;
   }

   if (patient_is_male())
   {
      sp_gradient = sp_gradient_male;
      sp_y_intercept = sp_y_intercept_male;
      sp_confidence_90_offset = sp_confidence_90_offset_male;
   }
   else
   {
      sp_gradient = sp_gradient_female;
      sp_y_intercept = sp_y_intercept_female;
      sp_confidence_90_offset = sp_confidence_90_offset_female;
   }

   // Do not display a range for young patients, carotid or aortic measurements
   if (age < PATIENT_YOUNG_AGE || MeasureType != PWA_RADIAL)
   {
      return sp_relative_index;
   }

   sp_cutoff_high = sp_gradient * age + sp_y_intercept + sp_confidence_90_offset;
   sp_cutoff_low = sp_gradient * age + sp_y_intercept - sp_confidence_90_offset;

   tmp_calc = (((sp - sp_cutoff_low) / (sp_cutoff_high - sp_cutoff_low)) * 100.0);
   sp_relative_index = tmp_calc;
   if (sp_relative_index == 0)
   {
      sp_relative_index = 1;
   }
   return (sp_relative_index);

}

int report_determine_pp_relative_index(float pp, UCOUNT age, PWA_MEASURE_TYPE  MeasureType)
{
   float       pp_cutoff_high;
   float       pp_cutoff_low;
   float       tmp_calc;
   int         pp_relative_index;

   pp_relative_index = 0;

   if (pp == DEFAULT_VALUE)
   {
      return pp_relative_index;
   }

   if (patient_is_male())
   {
      pp_gradient = pp_gradient_male;
      pp_y_intercept = pp_y_intercept_male;
      pp_confidence_90_offset = pp_confidence_90_offset_male;
   }
   else
   {
      pp_gradient = pp_gradient_female;
      pp_y_intercept = pp_y_intercept_female;
      pp_confidence_90_offset = pp_confidence_90_offset_female;
   }

   // Do not display a range for young patients, carotid or aortic measurements
   if (age < PATIENT_YOUNG_AGE || MeasureType != PWA_RADIAL)
   {
      return pp_relative_index;
   }

   pp_cutoff_high = pp_gradient * age + pp_y_intercept + pp_confidence_90_offset;
   pp_cutoff_low = pp_gradient * age + pp_y_intercept - pp_confidence_90_offset;

   tmp_calc = (((pp - pp_cutoff_low) / (pp_cutoff_high - pp_cutoff_low)) * 100.0);
   pp_relative_index = tmp_calc;
   if (pp_relative_index == 0)
   {
      pp_relative_index = 1;
   }
   return (pp_relative_index);
}

int report_calculate_pwa_reference_score(void)
{
   int pwa_reference_score = 0;
   int report_sevr_relidx;
   int report_ap_relidx;
   int report_pp_relidx;
   int report_ed_relidx;
   int report_sp_relidx;
   int report_aix_relidx;
   TPWA *report_pwa;

   // This function cannot use the report form object as it may be called to
   // export a database before report form initialisation.
   report_pwa = meas_get_current_pwa();

   // The export database function does not set the patient before populating,
   // therefore it must be called here to calculate the correct report age.
   if (patient_set(report_pwa->System_ID,
                     report_pwa->Study_ID,
                     report_pwa->Patient_No))
   {
      report_age = patient_get_age_at_date(report_pwa->DateTime);
      if (report_age)
      {
         report_sevr_relidx = report_determine_sevr_relative_index(report_pwa->Central.SVI,
                                                                  report_pwa->Central.HR,
                                                                  report_age,
                                                                  report_pwa->MeasureType);

         report_ap_relidx = report_determine_ap_relative_index(report_pwa->Central.AP,
                                                               report_age,
                                                               report_pwa->MeasureType);

         report_sp_relidx = report_determine_sp_relative_index(report_pwa->Central.Sp,
                                                               report_age,
                                                               report_pwa->MeasureType);

         report_aix_relidx = report_determine_aixhr75_relative_index(report_pwa->Central.AGPH_HR75,
                                                                     report_age,
                                                                     report_pwa->MeasureType);

         report_pp_relidx = report_determine_pp_relative_index((report_pwa->Central.Sp - report_pwa->Central.Dp),
                                                               report_age,
                                                               report_pwa->MeasureType);

         report_ed_relidx = report_determine_ed_relative_index(report_pwa->Central.EDPeriod,
                                                               report_pwa->Central.HR,
                                                               report_age,
                                                               report_pwa->MeasureType);
         if (report_sevr_relidx == 0 ||
            report_ap_relidx == 0   ||
            report_pp_relidx == 0   ||
            report_aix_relidx == 0  ||
            report_sp_relidx == 0   ||
            report_ed_relidx == 0)
         {
            pwa_reference_score = 0;
         }
         else
         {
            pwa_reference_score =  (report_sevr_relidx + report_ap_relidx + report_pp_relidx + report_ed_relidx + report_sp_relidx + report_aix_relidx) / 6;
         }
      }
      else
      {
         pwa_reference_score = 0;
      }
   }
   else
   {
      pwa_reference_score = 0;
   }
   return (pwa_reference_score);
}
//---------------------------------------------------------------------------
bool report_pwa_batch_print(TPWA                 *pwa_info,
                            PATIENT_RECORD_TYPE  *patient,
                            bool                 is_clinical)
{
   TLineSeries  *srs_periph_overlay;

   if (pwa_info != NULL && frm_report_pwa != NULL)
   {
      frm_report_pwa->report_pwa = pwa_info;
      for (int np = 0; np < REPORT_MAX_OVERLAY_PULSES; np++)
      {
         srs_periph_overlay = new TLineSeries(Application);
         srs_periph_overlay->LinePen->Width = 1;
         frm_report_pwa->chrt_pulse_overlay->AddSeries(srs_periph_overlay);
         srs_periph_overlay->Active = true;
      }

      patient_set(patient);
      report_age = 0;
      if (is_clinical)
      {
         frm_report_pwa->pgctrl_reports->ActivePage = frm_report_pwa->tbsht_clinical;
         // PM CR
         // This is a fix when batchprinting a Clinical report when the report
         // form has never been viewed
         if (pwa_first_time)
         {
            frm_report_pwa->pnl_clinical_sp->PaintTo(frm_main->img_print_clinical->Canvas->Handle, -60, 0);
            frm_report_pwa->pnl_clinical_pp->PaintTo(frm_main->img_print_clinical->Canvas->Handle, -60, 0);
            frm_report_pwa->pnl_clinical_ap->PaintTo(frm_main->img_print_clinical->Canvas->Handle, -60, 0);
            frm_report_pwa->pnl_clinical_aixhr75->PaintTo(frm_main->img_print_clinical->Canvas->Handle, -60, 0);
            frm_report_pwa->pnl_clinical_aix->PaintTo(frm_main->img_print_clinical->Canvas->Handle, -60, 0);
            frm_report_pwa->pnl_clinical_reference_age->PaintTo(frm_main->img_print_reference_age->Canvas->Handle, -40, 0);
            pwa_first_time = false;
         }
      }
      else
      {
         frm_report_pwa->pgctrl_reports->ActivePage = frm_report_pwa->tbsht_detailed;
      }
          
      frm_report_pwa->report_display_study();
      frm_report_pwa->report_display_signal();
      frm_report_pwa->report_display_average_pulse();
      frm_report_pwa->report_display_central_params();
      frm_report_pwa->bbtn_printClick(Application);

      int j = frm_report_pwa->chrt_pulse_overlay->SeriesCount() - 1;
      while (j >= 0)
      {
         frm_report_pwa->chrt_pulse_overlay->Series[j]->Clear();
         frm_report_pwa->chrt_pulse_overlay->Series[j]->Free();
         j = j - 1;
      }
      return true;
   }
   else
   {
      return false;
   }
}

//---------------------------------------------------------------------------
void __fastcall Tfrm_report_pwa::record_changed(TObject *Sender, TField  *Field)
{
    /*
   ** This removes the bug in TeeChart when the number of points
   ** in the previous series is less than the number of points in
   ** the current series.
   */
   chrt_avg_periph->OnMouseMove = NULL;
   chrt_avg_central->OnMouseMove = NULL;
   chrt_avg_central_periph->OnMouseMove = NULL;

   btn_move_ed_right->Enabled = true;
   btn_move_ed_left->Enabled = true;
   tbar_change_ed->Visible = false;

   tbar_change_t1t2->Visible = false;

   // PM V9
   // Only change the query in PWA mode. This is a fix for PWM mode in Version 9.
   if (study_mode == MEAS_PWA_ID)
   {
      // In audit mode query the PWA audit table, otherwise query the PWA table
      if (pwa_audit_mode)
      {
         report_qry = (TADOQuery *)dbmgr_get_dataset(DBMGR_MEASURE_PWA_AUDIT_QUERY, false);
      }
      else
      {
         report_qry = (TADOQuery *)dbmgr_get_dataset(DBMGR_MEASURE_PWA_QUERY, false);
      }
   }

   if (frm_report_pwa->report_qry != NULL)
   {
      if (frm_report_pwa->report_qry->RecordCount)
      {
         if (frm_report_pwa->report_pwa->Populate(frm_report_pwa->report_qry))
         {
            //ShowScrollBar(grd_report->Handle, SB_VERT, false);
            frm_report_pwa->lbl_assessments_title->Caption = " Assessment "
                                                      + IntToStr(frm_report_pwa->report_qry->RecNo) + " of "
                                                      + IntToStr(frm_report_pwa->report_qry->RecordCount);
            if (config_get_report_style() == CONFIG_BLIND_REPORT_STYLE)
            {
               frm_report_pwa->bbtn_print->Enabled = false;
            }
            else
            {
               frm_report_pwa->bbtn_print->Enabled = true;
            }
            frm_report_pwa->bbtn_modify->Enabled = true;
            /*
            ** For a calibrated device in PWM mode the entered value for
            ** Sp, Dp, Mp will be zero. Set to the value of peripheral in case
            ** require recalculation.
            */
            if (frm_report_pwa->report_pwa->Dp == 0)
            {
               frm_report_pwa->report_pwa->Dp = frm_report_pwa->report_pwa->Periph.Dp;
               frm_report_pwa->report_pwa->Sp = frm_report_pwa->report_pwa->Periph.Sp;
            }
            frm_report_pwa->report_display_study();
            frm_report_pwa->report_display_signal();
            frm_report_pwa->report_display_average_pulse();
            frm_report_pwa->report_display_central_params();
            frm_report_pwa->report_display_avi();

            // PM V9
            // Only enable the Recalculate All option when on the first record
            // and the audit and clinical options are not set
            if (frm_report_pwa->report_qry->RecNo == 1)
            {
               if (!config_get_audit_option() && !config_get_clinical_option())
               {
                  frm_main->mnu_recalculate_all->Enabled = true;
               }
            }
            else
            {
               frm_main->mnu_recalculate_all->Enabled = false;
            }

            // PM V9
            // Only enable the Repeat button when the last measurement is displayed
            // because this measurement's data is used in the repeat study
            // Only enable in PWA mode and not audit mode too
            frm_report_pwa->bbtn_repeat->Visible = false;
            if (frm_report_pwa->report_qry->RecNo == frm_report_pwa->report_qry->RecordCount)
            {
               if (study_mode == MEAS_PWA_ID && !pwa_audit_mode)
               {
                  frm_report_pwa->bbtn_repeat->Visible = true;
               }
            }

            Application->ProcessMessages();
         }
         else
         {
            frm_report_pwa->bbtn_print->Enabled = false;
            frm_report_pwa->bbtn_modify->Enabled = false;
         }
      }
   }
   chrt_avg_periph->OnMouseMove = chrt_avg_periphMouseMove;
   chrt_avg_central->OnMouseMove = chrt_avg_centralMouseMove;
   chrt_avg_central_periph->OnMouseMove = chrt_avg_central_periphMouseMove;
}
//---------------------------------------------------------------------------
__fastcall Tfrm_report_pwa::Tfrm_report_pwa(TComponent* Owner)
    : Child_Form(Owner)
{
}

void __fastcall Tfrm_report_pwa::FormShow(TObject *Sender)
{
   TPWA                 *pwa;
   PATIENT_RECORD_TYPE  pat;

   bbtn_session->Visible = false;

   if (pgctrl_reports != NULL)
   {
      if (config_get_clinical_option())
      {
         // PM V9
         // In Clinical mode, only the clinical screen is displayed and the user
         // cannot navigate to the other screens
         pgctrl_reports->ActivePage = tbsht_clinical;
         chrt_pulse_overlay->Parent = frm_report_pwa->pnl_operator_index;
         pnl_clinical->Parent = pnl_main;
         lbl_clinical_csp_title->OnClick = NULL;
         lbl_clinical_csp_title->ShowHint = false;
         lbl_clinical_csp_title->Cursor = crDefault;
         lbl_clinical_cpp_title->OnClick = NULL;
         lbl_clinical_cpp_title->ShowHint = false;
         lbl_clinical_cpp_title->Cursor = crDefault;
         lbl_clinical_ap_title->OnClick = NULL;
         lbl_clinical_ap_title->ShowHint = false;
         lbl_clinical_ap_title->Cursor = crDefault;
         lbl_clinical_aixhr75_title->OnClick = NULL;
         lbl_clinical_aixhr75_title->ShowHint = false;
         lbl_clinical_aixhr75_title->Cursor = crDefault;
         lbl_clinical_aix_title->OnClick = NULL;
         lbl_clinical_aix_title->ShowHint = false;
         lbl_clinical_aix_title->Cursor = crDefault;
      }
      else if (config_get_report_screen() == CONFIG_DETAILED_REPORT_SCREEN)
      {
         pgctrl_reports->ActivePage = tbsht_detailed;
         chrt_pulse_overlay->Parent = pnl_qc_pulse_overlay_back;
      }
      else if (config_get_report_screen() == CONFIG_CLINICAL_REPORT_SCREEN)
      {
         pgctrl_reports->ActivePage = tbsht_clinical;
         chrt_pulse_overlay->Parent = pnl_operator_index;
      }
      else if (pwa_first_time)
      {
         pgctrl_reports->ActivePage = tbsht_clinical;
         chrt_pulse_overlay->Parent = pnl_operator_index;
         pwa_first_time = false;
      }
   }
   
   if (patient_get(&pat))
   {
     study_mode = patient_get_study_mode();
     pwm_session_id = 0;
     switch (study_mode)
     {
        case MEAS_PWA_ID:
        {
           export_file = "_pwa";
           pwa = meas_get_current_pwa();
           pwm_title_string = "";
           report_qry = dbmgr_setup_query(DBMGR_MEASURE_PWA_TABLE,
                                          DBMGR_QUERY_KEY,
                                          PATIENT_SYSTEM_ID,
                                          PATIENT_STUDY_ID,
                                          PATIENT_NO,
                                          pat.system_id,
                                          pat.study_id,
                                          IntToStr(pat.number),
                                          MPW_DATETIME);


           ShowForm(Sender,
                    pwa,
                    dbmgr_get_data_source(DBMGR_MEASURE_PWA_QUERY, false));
           break;
        }
        case MEAS_PWM_ID:
        {
           export_file = "_pwm";
           pwm_title_string = " (PWM)";
           TPWM *pwm = meas_get_current_pwm();
           if (pwm == NULL)
           {
              report_qry = NULL;
           }
           else
           {
              pwm_session_id = pwm->Session_ID;
              pwa = dynamic_cast<TPWA *>(pwm);
              report_qry = dbmgr_setup_query(DBMGR_MEASURE_PWM_TABLE,
                                             DBMGR_QUERY_KEY,
                                             PATIENT_SYSTEM_ID,
                                             PATIENT_STUDY_ID,
                                             PATIENT_NO,
                                             MPWM_SESSION_ID,
                                             pat.system_id,
                                             pat.study_id,
                                             IntToStr(pat.number),
                                             IntToStr(pwm->Session_ID),
                                             MPW_DATETIME);
           }
           bbtn_session->Visible = true;
           ShowForm(Sender,
                    pwa,
                    dbmgr_get_data_source(DBMGR_MEASURE_PWM_QUERY, false));

           break;
        }
        default:
           break;
     }
     // If the audit option is set, disable export in PWA mode
     if (config_get_audit_option() && study_mode == MEAS_PWA_ID)
     {
         bbtn_export->Enabled = false;
     }
     else
     {
         bbtn_export->Enabled = true;
     }

     // PM V9
     // The Analysis buttons can be disabled by EMR
     pdf_file = "";
     if (emr_get_editing())
     {
         frm_main->spdbtn_analysis->Enabled = true;
         frm_main->Analysis1->Enabled = true;
     }
     else
     {
         frm_main->spdbtn_analysis->Enabled = false;
         frm_main->Analysis1->Enabled = false;
     }
     frm_main->mnu_settings->Enabled = false;
     
     // PM V9
     // If the EMR patient is active or default EMR mode is set - show the
     // Export All button
     // Make sure this is at the end of Show Form as this may shutdown the
     // software, if specified by the EMR object
     if (emr_patient_is_active() || emr_get_default_mode())
     {
         mnu_all->Visible = true;

         // If report export is enabled, perform an Export All and disable report export
         if (emr_get_report_export())
         {
            mnu_allClick(Sender);
            emr_set_report_export(false);
         }
     }
     else
     {
         mnu_all->Visible = false;
     }
   }
}
//---------------------------------------------------------------------------
void __fastcall Tfrm_report_pwa::ClearSeries()
{
   for (int i = 0; i < chrt_pulse_overlay->SeriesCount(); i++)
   {
      chrt_pulse_overlay->Series[i]->Clear();
   }
   for (int i = 0; i < chrt_avg_periph->SeriesCount(); i++)
   {
      chrt_avg_periph->Series[i]->Clear();
   }
   for (int i = 0; i < chrt_avg_central->SeriesCount(); i++)
   {
      chrt_avg_central->Series[i]->Clear();
   }

   for (int i = 0; i < chrt_pulse_periph->SeriesCount(); i++)
   {
      chrt_pulse_periph->Series[i]->Clear();
   }
   for (int i = 0; i < chrt_pulse_central->SeriesCount(); i++)
   {
      chrt_pulse_central->Series[i]->Clear();
   }

   for (int i = 0; i < chrt_avg_central_periph->SeriesCount(); i++)
   {
      chrt_avg_central_periph->Series[i]->Clear();
   }
}
//---------------------------------------------------------------------------
void __fastcall Tfrm_report_pwa::ShowForm(TObject *Sender, TPWA *pwa,
                                          TDataSource *pDataSource)
{
   TDataSource          *dsrc_report;
   PATIENT_RECORD_TYPE  pat;
   TLineSeries          *srs_periph_overlay;

   report_pwa = pwa;
   report_age = 0;
   FMeasDateTime = NULL;

   // Haemodynamic parameters and the print button are disabled for blind studies
   if (config_get_report_style() == CONFIG_BLIND_REPORT_STYLE)
   {
      pnl_params->Visible = false;
      pnl_clinical_parameters->Visible = false;
      bbtn_print->Enabled = false;
   }
   else
   {
      pnl_params->Visible = true;
      pnl_clinical_parameters->Visible = true;
      bbtn_print->Enabled = print_does_printer_exist();
      // PM V9
      // Only display AIx and AIx@HR75 if enabled
      if (config_get_clinical_aixhr75())
      {
         pnl_clinical_aixhr75->Visible = true;
      }
      else
      {
         pnl_clinical_aixhr75->Visible = false;
      }
      if (config_get_clinical_aix())
      {
         pnl_clinical_aix->Visible = true;
      }
      else
      {
         pnl_clinical_aix->Visible = false;
      }

      // PM V9
      // Adjust the display according to the paramters displayed
      if (!config_get_clinical_aixhr75() && !config_get_clinical_aix())
      {
         pnl_clinical_pressures->Height = 188;
         pnl_clinical_sp->Height = 81;
         pnl_clinical_pp->Height = 81;
         pnl_clinical_ap->Height = 81;
         pnl_clinical_aixhr75->Height = 81;
         pnl_clinical_aix->Height = 81;
      }
      else if (!config_get_clinical_aixhr75() || !config_get_clinical_aix())
      {
         pnl_clinical_pressures->Height = 171;
         pnl_clinical_sp->Height = 65;
         pnl_clinical_pp->Height = 65;
         pnl_clinical_ap->Height = 65;
         pnl_clinical_aixhr75->Height = 65;
         pnl_clinical_aix->Height = 65;
      }
      else
      {
         pnl_clinical_pressures->Height = 161;
         pnl_clinical_sp->Height = 54;
         pnl_clinical_pp->Height = 54;
         pnl_clinical_ap->Height = 54;
         pnl_clinical_aixhr75->Height = 54;
         pnl_clinical_aix->Height = 54;
      }
   }
   // PM CR
   if (patient_get(&pat))
   {
      dsrc_report = pDataSource;
      dsrc_report->AutoEdit = false;
      if ((report_qry != NULL) && report_qry->RecordCount)
      {
         patient_update_measurement_count((COUNT)(report_qry->RecordCount));

         grd_report->DataSource = dsrc_report;
         //nvg_report->DataSource = dsrc_report;

         for (int np = 0; np < REPORT_MAX_OVERLAY_PULSES; np++)
         {
            srs_periph_overlay = new TLineSeries(this);
            srs_periph_overlay->LinePen->Width = 1;
            chrt_pulse_overlay->AddSeries(srs_periph_overlay);
            srs_periph_overlay->Active = true;
         }

         lbl_pname->Caption = patient_get_name();

         lbl_pid->Caption = pat.id;
         lbl_pcode->Caption = pat.code;
         lbl_avi_pcode->Caption = lbl_pcode->Caption;
         lbl_address1->Caption = pat.street;
         lbl_avi_address1->Caption = lbl_address1->Caption;
         lbl_address2->Caption = pat.suburb + " " + pat.state + " " + pat.pcode;
         lbl_avi_address2->Caption = lbl_address2->Caption;
         lbl_address3->Caption = pat.country;
         lbl_avi_address3->Caption = lbl_address3->Caption;

         lbl_age->Caption = "";
         lbl_birth_date->Caption = pat.dob.FormatString(REPORT_PAT_DOB_DATE_FORMAT);
         lbl_sex->Caption = pat.sex;

         lbl_pavg_val->Caption = "";
         lbl_cavg_val->Caption = "";
         //lbl_avg_val->Caption = "";

         lbl_hwbmi->Caption = "";
         //ShowScrollBar(grd_report->Handle, SB_VERT, false);
         dsrc_report->OnDataChange = record_changed;
         report_qry->Last();
         grd_report->Enabled = true;
         if (grd_report->Visible)
         {
            grd_report->SetFocus();
         }
      }
      else
      {
         MsgBox(MSG_NO_REPORTS_TO_DISPLAY, SNOTIFICATION, MB_ICONINFORMATION);
      }
      Screen->Cursor = crDefault;
   }
}
//---------------------------------------------------------------------------
void __fastcall Tfrm_report_pwa::FormHide(TObject *Sender)
{
   int          j;

   if (grd_report->DataSource != NULL)
   {
      grd_report->DataSource->OnDataChange = NULL;
   }
   FMeasDateTime = NULL;

   if (study_mode == MEAS_PWM_ID)
   {
      frm_main->spdbtn_analysis->Enabled = false;
      frm_main->Analysis1->Enabled = false;
   }
   frm_main->mnu_settings->Enabled = true;
   frm_main->mnu_recalculate_all->Enabled = false;
   if (report_qry != NULL)
   {
      report_qry->Close();
   }
   j = chrt_pulse_overlay->SeriesCount() - 1;
   while (j >= 0)
   {
      chrt_pulse_overlay->Series[j]->Clear();
      chrt_pulse_overlay->Series[j]->Free();
      j = j - 1;
   }
   j = chrt_pulse_overlay->SeriesCount() - 1;
   ActiveControl = NULL;

   emma_display_statusbar_message("", "", "", sphygmocor_white);
   emma_display_statusbar_message("", "", sphygmocor_white);
}
//---------------------------------------------------------------------------
void __fastcall Tfrm_report_pwa::pnl_waveformResize(TObject *Sender)
{
   pnl_qc_back->Width = pnl_waveform->Width * 0.3;

   chrt_pulse_periph->Top = 1;
   chrt_pulse_periph->Left = 2;
   chrt_pulse_periph->Height = pnl_waveform->Height / 2 - 2;

   chrt_pulse_central->Top = pnl_waveform->Height / 2;
   chrt_pulse_central->Left = 2;

   lbl_qc1->Left = 10;
   lbl_qc2->Left = 10;
   lbl_qc3->Left = 10;
   lbl_qc4->Left = 10;
   lbl_qc5_dpdt->Left = 10;
   lbl_qc6->Left = 10;

   lbl_qc_title->Width = pnl_qc_back->Width;
}
//---------------------------------------------------------------------------
void __fastcall Tfrm_report_pwa::pnl_avgResize(TObject *Sender)
{
   pnl_avg_periph->Top = 1;
   pnl_avg_periph->Left = 1;
   pnl_avg_periph->Height = pnl_avg->Height;
   pnl_avg_periph->Width = pnl_avg->Width * 0.42;

   pnl_periph_pressure->Left = chrt_avg_periph->Left + chrt_avg_periph->Width + 1;
   pnl_periph_pressure->Height = pnl_avg->Height;
   pnl_periph_pressure->Width = pnl_avg->Width * 0.075;

   pnl_central_pressure->Left = pnl_periph_pressure->Left +
   pnl_periph_pressure->Width + pnl_avg->Width * 0.01 + 1;
   pnl_central_pressure->Height = pnl_avg->Height;
   pnl_central_pressure->Width = pnl_avg->Width * 0.075;

   lbl_csp_title->Left = pnl_central_pressure->Width - (lbl_csp_title->Width + 4);
   lbl_cdp_title->Left = lbl_csp_title->Left;
   lbl_cmp_title->Left = lbl_csp_title->Left;
   lbl_cpp_title->Left = lbl_csp_title->Left;

   lbl_csp->Left = pnl_central_pressure->Width - (lbl_csp->Width + 4);
   lbl_cdp->Left = pnl_central_pressure->Width - (lbl_cdp->Width + 4);
   lbl_cmp->Left = pnl_central_pressure->Width - (lbl_cmp->Width + 4);
   lbl_cpp->Left = pnl_central_pressure->Width - (lbl_cpp->Width + 4);

   pnl_avg_central->Top = 1;
   pnl_avg_central->Left = pnl_central_pressure->Left + pnl_central_pressure->Width +1;
   pnl_avg_central->Height = pnl_avg->Height;
   pnl_avg_central->Width = pnl_avg->Width * 0.42;
}
//---------------------------------------------------------------------------
void __fastcall Tfrm_report_pwa::chrt_avg_periphMouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
   if (chrt_avg_periph->Zoomed)
   {
      chrt_avg_periph->Series[0]->Marks->Arrow->Color = sphygmocor_white;
      chrt_avg_periph->Series[0]->Marks->Visible = true;
   }
}
//---------------------------------------------------------------------------
void __fastcall Tfrm_report_pwa::chrt_avg_periphMouseUp(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
   chrt_avg_periph->Series[0]->Marks->Visible = false;
}
//---------------------------------------------------------------------------
void __fastcall Tfrm_report_pwa::chrt_avg_periphMouseMove(TObject *Sender,
      TShiftState Shift, int X, int Y)
{
   long int in_region = -1;

   in_region = srs_avg_periph->Clicked(X,Y);

   // PM CR
   if (in_region != -1)
   {
      lbl_pavg_val->Caption = FormatFloat("0.0", srs_avg_periph->YValues->Value[in_region]);
   }
   else
   {
      lbl_pavg_val->Caption = "";
   }
}
//---------------------------------------------------------------------------
void __fastcall Tfrm_report_pwa::chrt_avg_centralMouseMove(TObject *Sender,
      TShiftState Shift, int X, int Y)
{
   long int in_region = -1;

   in_region = srs_avg_central->Clicked(X,Y);

   // PM CR
   if (in_region != -1)
   {
      lbl_cavg_val->Caption = FormatFloat("0.0", srs_avg_central->YValues->Value[in_region]);
   }
   else
   {
      lbl_cavg_val->Caption = "";
   }
}

//---------------------------------------------------------------------------
void __fastcall Tfrm_report_pwa::srs_avg_periphGetMarkText(
      TChartSeries *Sender, int ValueIndex, AnsiString &MarkText)
{
   int  point_count;
   int  point_num = 6;
   point_count = srs_avg_periph->LastValueIndex - srs_avg_periph->FirstValueIndex;

   if (point_count > 2 * point_num)
   {
      point_count = point_count / point_num;
   }
   else if (point_count <= point_num)
   {
      point_count = 1;
   }
   else
   {
      point_count = 2;
   }

   if ((ValueIndex - srs_avg_periph->FirstValueIndex + int(point_count/2))%point_count)
   {
      MarkText = "";
   }
   else
   {
      MarkText = FormatFloat("0.0", srs_avg_periph->YValues->Value[ValueIndex]);
   }
}
//---------------------------------------------------------------------------
void __fastcall Tfrm_report_pwa::chrt_avg_periphZoom(TObject *Sender)
{
   TLineSeries *series;
   TRect       zoom_rect;
   int         time_len;


   chrt_avg_periph->ClipPoints = true;
   zoom_rect.Top = chrt_avg_periph->LeftAxis->CalcYPosValue(chrt_avg_periph->LeftAxis->Maximum);
   zoom_rect.Bottom = chrt_avg_periph->LeftAxis->CalcYPosValue(chrt_avg_periph->LeftAxis->Minimum);
   zoom_rect.Left = chrt_avg_central->BottomAxis->CalcXPosValue(chrt_avg_periph->BottomAxis->Minimum);
   zoom_rect.Right = chrt_avg_central->BottomAxis->CalcXPosValue(chrt_avg_periph->BottomAxis->Maximum);
   time_len = chrt_avg_periph->BottomAxis->Maximum - chrt_avg_periph->BottomAxis->Minimum;
   if (time_len < 100)
   {
      series = dynamic_cast<TLineSeries *>(chrt_avg_periph->Series[0]);
      if (series)
      {
         series->Pointer->Visible = true;
      }
      chrt_avg_periph->BottomAxis->Increment = 10;
   }
   else if (time_len > 100 && time_len < 250)
   {
      chrt_avg_periph->BottomAxis->Increment = 50;
   }
   else if (time_len > 250 && time_len < 500)
   {
      chrt_avg_periph->BottomAxis->Increment = 100;
   }
   else if (time_len > 500 && time_len < 750)
   {
      chrt_avg_periph->BottomAxis->Increment = 150;
   }
   chrt_avg_central->ZoomRect(zoom_rect);
}
//---------------------------------------------------------------------------
void __fastcall Tfrm_report_pwa::chrt_avg_periphUndoZoom(TObject *Sender)
{
   TLineSeries *series;

   chrt_avg_periph->ClipPoints = false;
   series = dynamic_cast<TLineSeries *>(chrt_avg_periph->Series[0]);
   if (series)
   {
      series->Pointer->Visible = false;
   }
   chrt_avg_periph->BottomAxis->Increment = 200;
   chrt_avg_central->UndoZoom();
}
//---------------------------------------------------------------------------
void __fastcall Tfrm_report_pwa::chrt_avg_centralMouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
   if (chrt_avg_central->Zoomed)
   {
      chrt_avg_central->Series[0]->Marks->Visible = true;
   }
}
//---------------------------------------------------------------------------
void __fastcall Tfrm_report_pwa::chrt_avg_centralMouseUp(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
   chrt_avg_central->Series[0]->Marks->Visible = false;
}
//---------------------------------------------------------------------------
void __fastcall Tfrm_report_pwa::chrt_avg_centralZoom(TObject *Sender)
{
   TCustomSeries *series;
   int           time_len;

   chrt_avg_central->ClipPoints = true;
   time_len = chrt_avg_central->BottomAxis->Maximum - chrt_avg_central->BottomAxis->Minimum;

   if (time_len < 100)
   {
      series = dynamic_cast<TCustomSeries *>(chrt_avg_central->Series[0]);
      if (series)
      {
         series->Pointer->Visible = true;
      }
      chrt_avg_central->BottomAxis->Increment = 10;
   }
   else if (time_len > 100 && time_len < 250)
   {
      chrt_avg_central->BottomAxis->Increment = 50;
   }
   else if (time_len > 250 && time_len < 500)
   {
      chrt_avg_central->BottomAxis->Increment = 100;
   }
   else if (time_len > 500 && time_len < 750)
   {
      chrt_avg_central->BottomAxis->Increment = 150;
   }
}
//---------------------------------------------------------------------------
void __fastcall Tfrm_report_pwa::chrt_avg_centralUndoZoom(TObject *Sender)
{
   TCustomSeries *series;

   chrt_avg_central->ClipPoints = false;

   series = dynamic_cast<TCustomSeries *>(chrt_avg_central->Series[0]);
   if (series)
   {
      series->Pointer->Visible = false;
   }
   chrt_avg_central->BottomAxis->Increment = 200;
}
//---------------------------------------------------------------------------
void __fastcall Tfrm_report_pwa::srs_avg_centralGetMarkText(
                TChartSeries *Sender, int ValueIndex, AnsiString &MarkText)
{
   int  point_count;
   int  point_num = 6;
   point_count = srs_avg_central->LastValueIndex - srs_avg_central->FirstValueIndex;

   if (point_count > 2 * point_num)
   {
      point_count = point_count / point_num;
   }
   else if (point_count <= point_num)
   {
      point_count = 1;
   }
   else
   {
      point_count = 2;
   }

   if ((ValueIndex - srs_avg_central->FirstValueIndex + int(point_count/2))%point_count)
   {
      MarkText = "";
   }
   else
   {
      MarkText = FormatFloat("0.0", srs_avg_central->YValues->Value[ValueIndex]);
   }
}
//---------------------------------------------------------------------------
void Tfrm_report_pwa::print_report_header(TRect *print_area)
{
   AnsiString S1;
   AnsiString S2;
   AnsiString S3;

   S1 = config_get_report_title();
   if (pgctrl_reports->ActivePage == tbsht_detailed)
   {
      S2 = "Evaluation Report" +pwm_title_string;
   }
   else if (pgctrl_reports->ActivePage == tbsht_clinical)
   {
      S2 = "Clinical Assessment" +pwm_title_string;
   }
   else if (pgctrl_reports->ActivePage == tbsht_reference)
   {
      S2 = "Reference Range Assessment" +pwm_title_string;
   }
   else if (pgctrl_reports->ActivePage == tbsht_avi)
   {
      S2 = "Wave Reflection Assessment" +pwm_title_string;
   }
   print_do_header(print_area, S1, S2);
}
//---------------------------------------------------------------------------
void Tfrm_report_pwa::print_report_patient(TRect *print_area)
{
   print_do_patient_data(print_area, report_age, (frm_main->lbl_message1->Caption != ""), frm_main->lbl_message1->Caption, frm_main->lbl_message3->Caption, report_pwa->Simulation);
}

//---------------------------------------------------------------------------
int Tfrm_report_pwa::print_report_study(TPrinter *print_ptr, TRect *print_area)
{
   int          text_width;
   int          xpos;
   int          ypos;
   AnsiString   S;
   TRect        chart_rect;
   TFontStyles  font_style;

   TFontStyles  bold_font;
   bold_font.Clear();
   bold_font << fsBold;

   TFontStyles  normal_font;
   normal_font.Clear();

   font_style << fsBold;
   S = "STUDY DATA";
   print_ptr->Canvas->Font->Name = REPORT_FONT_NAME;
   print_ptr->Canvas->Font->Size = 12;
   print_ptr->Canvas->Font->Style = font_style;
   print_ptr->Canvas->TextOut(print_area->Left,
                              print_area->Top,
                              S);

   ypos = print_area->Top + print_ptr->Canvas->TextHeight(S);
   print_ptr->Canvas->Font->Name = REPORT_FONT_NAME;
   print_ptr->Canvas->Font->Size = 8;


   // DateTime
   S = lbl_date->Caption + ", " + lbl_time->Caption + "    ";
   print_ptr->Canvas->TextOut(print_area->Left,
                              ypos,
                              S);

   text_width = print_ptr->Canvas->TextWidth(S);
   xpos = print_area->Left + text_width;

   font_style.Clear();
   print_ptr->Canvas->Font->Style = font_style;

   // Height, Weight, BMI
   if (lbl_hwbmi->Caption != "")
   {
      S = lbl_hwbmi_title->Caption + " ";

      print_ptr->Canvas->TextOut(xpos,
                                 ypos,
                                 S);
      xpos = xpos + print_ptr->Canvas->TextWidth(S);

      font_style << fsBold;
      print_ptr->Canvas->Font->Style = font_style;
      S = lbl_hwbmi->Caption + "    ";
      print_ptr->Canvas->TextOut(xpos,
                                 ypos,
                                 S);
      xpos = xpos + print_ptr->Canvas->TextWidth(S);
   }

   font_style.Clear();
   print_ptr->Canvas->Font->Style = font_style;

   // Tonometer serial number
   if (lbl_tonometer->Visible)
   {
      S = lbl_tonometer_title->Caption + " ";

      print_ptr->Canvas->TextOut(xpos,
                                 ypos,
                                 S);
      xpos = xpos + print_ptr->Canvas->TextWidth(S);

      font_style << fsBold;
      print_ptr->Canvas->Font->Style = font_style;
      S = lbl_tonometer->Caption;
      print_ptr->Canvas->TextOut(xpos,
                                 ypos,
                                 S);
      xpos = xpos + print_ptr->Canvas->TextWidth(S);
   }
   font_style.Clear();
   print_ptr->Canvas->Font->Style = font_style;

   // Operator
   ypos = ypos + print_ptr->Canvas->TextHeight(S);
   xpos = print_area->Left;
   S = lbl_operator_title->Caption + "     ";
   print_ptr->Canvas->TextOut(xpos,
                              ypos,
                              S);
   xpos = xpos + print_ptr->Canvas->TextWidth(S);
   text_width = print_ptr->Canvas->TextWidth(S);

   font_style << fsBold;
   print_ptr->Canvas->Font->Style = font_style;
   S = lbl_operator->Caption + "    ";
   print_ptr->Canvas->TextOut(xpos,
                              ypos,
                              S);

   // Audit DateTime
   if (config_get_audit_option() && study_mode == MEAS_PWA_ID)
   {
      if (pwa_audit_mode)
      {
         if (report_pwa->AuditFlag == AUDIT_MODIFIED)
         {
            xpos = xpos + print_ptr->Canvas->TextWidth(S);
            font_style.Clear();
            print_ptr->Canvas->Font->Style = font_style;

            S = "on    ";
            print_ptr->Canvas->TextOut(xpos,
                                    ypos,
                                    S);
            xpos = xpos + print_ptr->Canvas->TextWidth(S);

            font_style << fsBold;
            print_ptr->Canvas->Font->Style = font_style;
            S = report_pwa->AuditChange.FormatString(REPORT_PAT_DOB_DATE_FORMAT) +
               ", " + report_pwa->AuditChange.TimeString() + " ";
            print_ptr->Canvas->TextOut(xpos,
                                    ypos,
                                    S);
         }
         xpos = xpos + print_ptr->Canvas->TextWidth(S);

         font_style << fsBold;
         print_ptr->Canvas->Font->Style = font_style;
         S = "(" + IntToStr(frm_report_pwa->report_qry->RecNo) + " of "
            + IntToStr(frm_report_pwa->report_qry->RecordCount) + ")    ";
         print_ptr->Canvas->TextOut(xpos,
                                    ypos,
                                    S);
      }
   }

   if (pgctrl_reports->ActivePage == tbsht_reference
       || pgctrl_reports->ActivePage == tbsht_avi)
   {
      xpos = xpos + print_ptr->Canvas->TextWidth(S);
      font_style.Clear();
      print_ptr->Canvas->Font->Style = font_style;

      // Peripheral Pressures
      S = "Peripheral Pressures ";
      print_ptr->Canvas->TextOut(xpos,
                                 ypos,
                                 S);
      xpos = xpos + print_ptr->Canvas->TextWidth(S);

      font_style << fsBold;
      print_ptr->Canvas->Font->Style = font_style;
      S = lbl_psp->Caption + "/" + lbl_pdp->Caption + " (" + lbl_pmp->Caption + ")" + "    ";
      print_ptr->Canvas->TextOut(xpos,
                                 ypos,
                                 S);
      xpos = xpos + print_ptr->Canvas->TextWidth(S);

      font_style.Clear();
      print_ptr->Canvas->Font->Style = font_style;

      // Peripheral Pulse Pressure
      S = lbl_ppp_title->Caption + " ";
      print_ptr->Canvas->TextOut(xpos,
                                 ypos,
                                 S);
      xpos = xpos + print_ptr->Canvas->TextWidth(S);

      font_style << fsBold;
      print_ptr->Canvas->Font->Style = font_style;
      S = lbl_ppp->Caption;
      print_ptr->Canvas->TextOut(xpos,
                                 ypos,
                                 S);
   }

   // Medication
   font_style.Clear();
   print_ptr->Canvas->Font->Style = font_style;
   S = "Medication:    ";
   ypos = ypos + print_ptr->Canvas->TextHeight(S);
   print_ptr->Canvas->TextOut(print_area->Left,
                              ypos,
                              S);
   print_ptr->Canvas->TextOut(print_area->Left + text_width,
                              ypos,
                              edt_med->Text);

   // Notes
   S = "Notes: ";
   ypos = ypos + print_ptr->Canvas->TextHeight(S);
   print_ptr->Canvas->TextOut(print_area->Left,
                              ypos,
                              S);
   print_ptr->Canvas->TextOut(print_area->Left + text_width,
                              ypos,
                              edt_notes->Text);

   // Reason for Change
   if (pgctrl_reports->ActivePage == tbsht_clinical)
   {
      if (report_pwa->Reason.Length() != 0)
      {
         S = "Reason for Change: ";
         ypos = ypos + print_ptr->Canvas->TextHeight(S);
         print_ptr->Canvas->TextOut(print_area->Left,
                                    ypos,
                                    S);
         text_width = print_ptr->Canvas->TextWidth(S);
         String report_reason = MsgBox_ReplaceCarriage(report_pwa->Reason);
         int report_reason_len = report_reason.Length();
         String report_reason_line1 = "";
         String report_reason_line2 = "";
         if (report_reason_len < 120)
         {
            print_ptr->Canvas->TextOut(print_area->Left + text_width,
                                       ypos,
                                       report_reason);
         }
         else
         {
            report_reason_line1 = report_reason.SubString(1, 120);
            report_reason_line2 = report_reason.SubString(121, report_reason_len - 120);
            print_ptr->Canvas->TextOut(print_area->Left + text_width,
                                       ypos,
                                       report_reason_line1);
            ypos = ypos + print_ptr->Canvas->TextHeight(S) + 5;
            print_ptr->Canvas->TextOut(print_area->Left + text_width,
                                       ypos,
                                       report_reason_line2);
         }
      }

      ypos = ypos + print_ptr->Canvas->TextHeight(S);
      // PM CR
   }
   else
   {
      ypos = ypos + print_ptr->Canvas->TextHeight(S);
   }
   return (ypos);
}

void Tfrm_report_pwa::print_report_qc(TPrinter *print_ptr, TRect *print_area)
{
   int          text_width;
   int          xpos;
   int          ypos;
   int          width;
   int          chart_ypos;
   AnsiString   S;
   TRect        chart_rect;
   TFontStyles  font_style;
   TFontStyles  bold_font;
   TFontStyles  normal_font;

   bold_font.Clear();
   bold_font << fsBold;

   normal_font.Clear();

   width  = print_area->Right - print_area->Left;
   chart_ypos = print_area->Top;
   ypos = print_area->Top;

   chart_rect.Top = chart_ypos;
   chart_rect.Left = print_area->Left;
   chart_rect.Right = width * 0.65;
   chart_rect.Bottom = chart_ypos + ((print_area->Bottom - chart_ypos) / 2 - 2);

   font_style << fsBold;
   S = "QUALITY CONTROL";
   print_ptr->Canvas->Font->Name = REPORT_FONT_NAME;
   print_ptr->Canvas->Font->Size = 12;
   print_ptr->Canvas->Font->Style = font_style;
   print_ptr->Canvas->TextOut(width * 0.8,
                              ypos,
                              S);
   font_style >> fsBold >> fsUnderline;
   print_ptr->Canvas->Font->Name = REPORT_FONT_NAME;
   print_ptr->Canvas->Font->Size = 8;
   print_ptr->Canvas->Font->Style = font_style;

   S = "Pulse Length Variation  ";

   text_width = print_ptr->Canvas->TextWidth(S);
   ypos = ypos + 3 * print_ptr->Canvas->TextHeight(S);

   S = "Pulse Height";
   xpos = width * 0.8 + text_width;

   print_ptr->Canvas->TextOut(width * 0.8,
                              ypos,
                              S);

   print_ptr->Canvas->Font->Style =
     (lbl_qc1->Font->Color == sphygmocor_red ? normal_font : bold_font);
   print_ptr->Canvas->TextOut(xpos,
                              ypos,
                              lbl_qc1->Caption);
   print_ptr->Canvas->Font->Style = normal_font;

   S = "Pulse Height Variation ";
   ypos = ypos + print_ptr->Canvas->TextHeight(S);
   print_ptr->Canvas->TextOut(width * 0.8,
                              ypos,
                              S);
   print_ptr->Canvas->Font->Style =
     (lbl_qc2->Font->Color == sphygmocor_red ? normal_font : bold_font);
   print_ptr->Canvas->TextOut(xpos,
                              ypos,
                              lbl_qc2->Caption + "%");
   print_ptr->Canvas->Font->Style = normal_font;

   S = "Diastolic Variation ";
   ypos = ypos + print_ptr->Canvas->TextHeight(S);
   print_ptr->Canvas->TextOut(width * 0.8,
                              ypos,
                              S);
   print_ptr->Canvas->Font->Style =
     (lbl_qc4->Font->Color == sphygmocor_red ? normal_font : bold_font);
   print_ptr->Canvas->TextOut(xpos,
                              ypos,
                              lbl_qc4->Caption + "%");
   print_ptr->Canvas->Font->Style = normal_font;

   S = "Shape Deviation ";
   ypos = ypos + print_ptr->Canvas->TextHeight(S);
   print_ptr->Canvas->TextOut(width * 0.8,
                              ypos,
                              S);
   if (lbl_qc6->Caption == "n/c ")
   {
      print_ptr->Canvas->TextOut(xpos,
                                 ypos,
                                 "n/c");
   }
   else
   {
      print_ptr->Canvas->Font->Style =
         (lbl_qc6->Font->Color == sphygmocor_red ? normal_font : bold_font);
      print_ptr->Canvas->TextOut(xpos,
                                 ypos,
                                 lbl_qc6->Caption + "%");
   }
   print_ptr->Canvas->Font->Style = normal_font;

   S = "Pulse Length Variation  ";
   ypos = ypos + print_ptr->Canvas->TextHeight(S);
   print_ptr->Canvas->TextOut(width * 0.8,
                              ypos,
                              S);
   print_ptr->Canvas->Font->Style = bold_font;
   print_ptr->Canvas->TextOut(xpos,
                              ypos,
                              lbl_qc3->Caption + "%");
   print_ptr->Canvas->Font->Style = normal_font;

   S = "dP/dt Max";
   ypos = ypos + print_ptr->Canvas->TextHeight(S);
   print_ptr->Canvas->TextOut(width * 0.8,
                              ypos,
                              S);
   print_ptr->Canvas->Font->Style = bold_font;
   print_ptr->Canvas->TextOut(xpos,
                              ypos,
                              lbl_qc5_dpdt->Caption);
   print_ptr->Canvas->Font->Style = normal_font;

   S = "Operator Index";
   ypos = ypos + (2 * print_ptr->Canvas->TextHeight(S));
   print_ptr->Canvas->Font->Size = 10;
   print_ptr->Canvas->TextOut(width * 0.8,
                              ypos,
                              S);
   if (report_pwa->Periph.OperatorIndex != DEFAULT_VALUE && report_pwa->Periph.OperatorIndex >= PWA_GOOD_OPERATOR_INDEX)
   {
      print_ptr->Canvas->Font->Style = bold_font;
   }
   print_ptr->Canvas->TextOut(xpos,
                              ypos,
                              lbl_qcidx->Caption);
   print_ptr->Canvas->Font->Style = normal_font;

   chrt_pulse_periph->PrintResolution = -100;
   chrt_pulse_periph->PrintProportional = false;
   chrt_pulse_periph->PrintPartial(chart_rect);

   chart_rect.Top = chart_rect.Bottom + 2;
   chart_rect.Left = print_area->Left;
   chart_rect.Right = width * 0.65;
   chart_rect.Bottom = print_area->Bottom - 2;
   chrt_pulse_central->PrintResolution = -100;
   chrt_pulse_central->PrintProportional = false;
   chrt_pulse_central->PrintPartial(chart_rect);

   chart_rect.Top = chart_ypos;
   chart_rect.Left = width * 0.70;
   chart_rect.Right = width * 0.80;
   chart_rect.Bottom = print_area->Bottom - 2;
   chrt_pulse_overlay->PrintResolution = -100;
   chrt_pulse_overlay->PrintProportional = false;
   chrt_pulse_overlay->MarginBottom = 0;
   chrt_pulse_overlay->MarginLeft = 0;
   chrt_pulse_overlay->PrintPartial(chart_rect);
}

void Tfrm_report_pwa::print_report_clinical_qc(TPrinter *print_ptr, TRect *print_area)
{
   int          text_width;
   int          xpos;
   int          ypos;
   int          width;
   AnsiString   S;
   TRect        chart_rect;
   TFontStyles  font_style;
   TFontStyles  bold_font;
   TFontStyles  normal_font;

   bold_font.Clear();
   bold_font << fsBold;

   normal_font.Clear();

   width  = print_area->Right - print_area->Left;

   font_style = normal_font;
   print_ptr->Canvas->Font->Name = REPORT_FONT_NAME;
   print_ptr->Canvas->Font->Size = 8;
   print_ptr->Canvas->Font->Style = font_style;

   S = "Pulse Length Variation  ";

   text_width = print_ptr->Canvas->TextWidth(S);
   ypos = print_area->Top;

   S = "Pulse Height";
   xpos = print_area->Left;

   print_ptr->Canvas->TextOut(xpos,
                              ypos,
                              S);

   print_ptr->Canvas->Font->Style =
     (lbl_qc1->Font->Color == sphygmocor_red ? normal_font : bold_font);
   print_ptr->Canvas->TextOut(xpos + text_width,
                              ypos,
                              lbl_qc1->Caption);
   print_ptr->Canvas->Font->Style = normal_font;

   S = "Pulse Height Variation ";
   ypos = ypos + print_ptr->Canvas->TextHeight(S);
   print_ptr->Canvas->TextOut(xpos,
                              ypos,
                              S);
   print_ptr->Canvas->Font->Style =
     (lbl_qc2->Font->Color == sphygmocor_red ? normal_font : bold_font);
   print_ptr->Canvas->TextOut(xpos + text_width,
                              ypos,
                              lbl_qc2->Caption + "%");
   print_ptr->Canvas->Font->Style = normal_font;
   ypos = ypos - print_ptr->Canvas->TextHeight(S);
   xpos = xpos + width / 2;

   S = "Diastolic Variation ";
   text_width = print_ptr->Canvas->TextWidth(S);
   print_ptr->Canvas->TextOut(xpos,
                              ypos,
                              S);
   print_ptr->Canvas->Font->Style =
     (lbl_qc4->Font->Color == sphygmocor_red ? normal_font : bold_font);
   print_ptr->Canvas->TextOut(xpos + text_width,
                              ypos,
                              lbl_qc4->Caption + "%");
   print_ptr->Canvas->Font->Style = normal_font;

   S = "Shape Deviation ";
   ypos = ypos + print_ptr->Canvas->TextHeight(S);
   print_ptr->Canvas->TextOut(xpos,
                              ypos,
                              S);
   if (lbl_qc6->Caption == "n/c ")
   {
      print_ptr->Canvas->TextOut(xpos + text_width,
                                 ypos,
                                 "n/c");
   }
   else
   {
      print_ptr->Canvas->Font->Style =
         (lbl_qc6->Font->Color == sphygmocor_red ? normal_font : bold_font);
      print_ptr->Canvas->TextOut(xpos + text_width,
                                 ypos,
                                 lbl_qc6->Caption + "%");
   }
   print_ptr->Canvas->Font->Style = normal_font;

   S = "Operator Index ";
   print_ptr->Canvas->Font->Size = 10;
   text_width = print_ptr->Canvas->TextWidth(S);
   ypos = ypos + print_ptr->Canvas->TextHeight(S);
   print_ptr->Canvas->TextOut(xpos - text_width,
                              ypos,
                              S);
   if (report_pwa->Periph.OperatorIndex != DEFAULT_VALUE && report_pwa->Periph.OperatorIndex >= PWA_GOOD_OPERATOR_INDEX)
   {
      print_ptr->Canvas->Font->Style = bold_font;
   }
   print_ptr->Canvas->TextOut(xpos,
                              ypos,
                              lbl_qcidx->Caption);
   print_ptr->Canvas->Font->Style = normal_font;
}

//---------------------------------------------------------------------------
void Tfrm_report_pwa::print_report_pressures(TPrinter *print_ptr, TRect *print_area, bool is_detailed)
{
   int          ypos;
   int          xpos;
   float        separation_factor;
   AnsiString   S;
   TFontStyles  font_style;
   TFontStyles  bold_font;
   TFontStyles  normal_font;

   bold_font.Clear();
   bold_font << fsBold;

   normal_font.Clear();

   separation_factor = 1.5;

   if (!is_detailed)
   {
      font_style << fsBold;
      print_ptr->Canvas->Font->Name = REPORT_FONT_NAME;
      print_ptr->Canvas->Font->Size = 10;
      print_ptr->Canvas->Font->Style = font_style;
      S = "Brachial";
      print_ptr->Canvas->TextOut(print_area->Left,
                                 print_area->Top,
                                 S);
      S = "Aortic";
      print_ptr->Canvas->TextOut(print_area->Right - print_ptr->Canvas->TextWidth(S) * 3 / 4,
                                 print_area->Top,
                                 S);
   }

   //Peripheral Systolic
   font_style.Clear();

   print_ptr->Canvas->Font->Name = REPORT_FONT_NAME;
   print_ptr->Canvas->Font->Size = 10;
   print_ptr->Canvas->Font->Style = font_style;
   S = "Sp";
   ypos = print_area->Top + ((separation_factor + 0.5) * print_ptr->Canvas->TextHeight(S));
   print_ptr->Canvas->TextOut(print_area->Left + 2,
                              ypos,
                              S);

   ypos = ypos + (separation_factor * print_ptr->Canvas->TextHeight(S));
   S = lbl_psp->Caption;
   font_style << fsBold;
   print_ptr->Canvas->Font->Name = REPORT_FONT_NAME;
   print_ptr->Canvas->Font->Size = 14;
   print_ptr->Canvas->Font->Style = font_style;
   print_ptr->Canvas->TextOut(print_area->Left + 2,
                              ypos,
                              S);

   //Central Systolic
   font_style.Clear();

   print_ptr->Canvas->Font->Name = REPORT_FONT_NAME;
   print_ptr->Canvas->Font->Size = 10;
   print_ptr->Canvas->Font->Style = font_style;
   ypos = ypos - (separation_factor * print_ptr->Canvas->TextHeight(S));
   S = "Sp";
   print_ptr->Canvas->TextOut(print_area->Right - 2 - print_ptr->Canvas->TextWidth(S),
                              ypos,
                              S);

   ypos = ypos + (separation_factor * print_ptr->Canvas->TextHeight(S));
   S = lbl_csp->Caption;
   font_style << fsBold;
   print_ptr->Canvas->Font->Name = REPORT_FONT_NAME;
   print_ptr->Canvas->Font->Size = 14;
   print_ptr->Canvas->Font->Style = font_style;
   print_ptr->Canvas->TextOut(print_area->Right - 2 - print_ptr->Canvas->TextWidth(S),
                              ypos,
                              S);

   //Peripheral Diastolic
   ypos = ypos + ((separation_factor + 0.5) * print_ptr->Canvas->TextHeight(S));

   font_style.Clear();

   print_ptr->Canvas->Font->Name = REPORT_FONT_NAME;
   print_ptr->Canvas->Font->Size = 10;
   print_ptr->Canvas->Font->Style = font_style;
   S = "Dp";
   print_ptr->Canvas->TextOut(print_area->Left + 2,
                              ypos,
                              S);

   ypos = ypos + (separation_factor * print_ptr->Canvas->TextHeight(S));
   S = lbl_pdp->Caption;
   font_style << fsBold;
   print_ptr->Canvas->Font->Name = REPORT_FONT_NAME;
   print_ptr->Canvas->Font->Size = 14;
   print_ptr->Canvas->Font->Style = font_style;
   print_ptr->Canvas->TextOut(print_area->Left + 2,
                              ypos,
                              S);

   //Central Diastolic
   font_style.Clear();

   print_ptr->Canvas->Font->Name = REPORT_FONT_NAME;
   print_ptr->Canvas->Font->Size = 10;
   print_ptr->Canvas->Font->Style = font_style;
   ypos = ypos - (separation_factor * print_ptr->Canvas->TextHeight(S));
   S = "Dp";
   print_ptr->Canvas->TextOut(print_area->Right - 2 - print_ptr->Canvas->TextWidth(S),
                              ypos,
                              S);

   ypos = ypos + (separation_factor * print_ptr->Canvas->TextHeight(S));
   S = lbl_cdp->Caption;
   font_style << fsBold;
   print_ptr->Canvas->Font->Name = REPORT_FONT_NAME;
   print_ptr->Canvas->Font->Size = 14;
   print_ptr->Canvas->Font->Style = font_style;
   print_ptr->Canvas->TextOut(print_area->Right - 2 - print_ptr->Canvas->TextWidth(S),
                              ypos,
                              S);

   //Peripheral Pulse Pressure
   ypos = ypos + ((separation_factor + 0.5) * print_ptr->Canvas->TextHeight(S));

   font_style.Clear();

   print_ptr->Canvas->Font->Name = REPORT_FONT_NAME;
   print_ptr->Canvas->Font->Size = 10;
   print_ptr->Canvas->Font->Style = font_style;
   S = "PP";
   print_ptr->Canvas->TextOut(print_area->Left + 2,
                              ypos,
                              S);

   ypos = ypos + (separation_factor * print_ptr->Canvas->TextHeight(S));
   S = lbl_ppp->Caption;
   font_style << fsBold;
   print_ptr->Canvas->Font->Name = REPORT_FONT_NAME;
   print_ptr->Canvas->Font->Size = 14;
   print_ptr->Canvas->Font->Style = font_style;
   print_ptr->Canvas->TextOut(print_area->Left + 2,
                              ypos,
                              S);

   //Central Pulse Pressure
   font_style.Clear();

   print_ptr->Canvas->Font->Name = REPORT_FONT_NAME;
   print_ptr->Canvas->Font->Size = 10;
   print_ptr->Canvas->Font->Style = font_style;
   ypos = ypos - (separation_factor * print_ptr->Canvas->TextHeight(S));
   S = "PP";
   print_ptr->Canvas->TextOut(print_area->Right - 2 - print_ptr->Canvas->TextWidth(S),
                              ypos,
                              S);

   ypos = ypos + (separation_factor * print_ptr->Canvas->TextHeight(S));
   S = lbl_cpp->Caption;
   font_style << fsBold;
   print_ptr->Canvas->Font->Name = REPORT_FONT_NAME;
   print_ptr->Canvas->Font->Size = 14;
   // PM V9
   // Only display Central Pulse Pressure in bold when less than 50mmHg,
   // Clinical report only
   if (is_detailed)
   {
      print_ptr->Canvas->Font->Style = font_style;
   }
   else
   {
      print_ptr->Canvas->Font->Style = (lbl_clinical_cpp->Font->Color == sphygmocor_red ? normal_font : bold_font);
   }
   print_ptr->Canvas->TextOut(print_area->Right - 2 - print_ptr->Canvas->TextWidth(S),
                              ypos,
                              S);


   //Peripheral Mean Pressure
   ypos = ypos + ((separation_factor + 0.5) * print_ptr->Canvas->TextHeight(S));
   font_style.Clear();

   print_ptr->Canvas->Font->Name = REPORT_FONT_NAME;
   print_ptr->Canvas->Font->Size = 10;
   print_ptr->Canvas->Font->Style = font_style;

   S = "MP";
   print_ptr->Canvas->TextOut(print_area->Left + 2,
                              ypos,
                              S);

   ypos = ypos + (separation_factor * print_ptr->Canvas->TextHeight(S));
   S = lbl_cmp->Caption;
   font_style << fsBold;
   print_ptr->Canvas->Font->Name = REPORT_FONT_NAME;
   print_ptr->Canvas->Font->Size = 14;
   print_ptr->Canvas->Font->Style = font_style;
   print_ptr->Canvas->TextOut(print_area->Left + 2,
                              ypos,
                              S);

   //Heart Rate
   font_style.Clear();

   print_ptr->Canvas->Font->Name = REPORT_FONT_NAME;
   print_ptr->Canvas->Font->Size = 10;
   print_ptr->Canvas->Font->Style = font_style;
   ypos = ypos - (separation_factor * print_ptr->Canvas->TextHeight(S));
   S = "HR";
   print_ptr->Canvas->TextOut(print_area->Right - 2 - print_ptr->Canvas->TextWidth(S),
                              ypos,
                              S);

   ypos = ypos + (separation_factor * print_ptr->Canvas->TextHeight(S));
   S = lbl_clinical_hr->Caption;
   font_style << fsBold;
   print_ptr->Canvas->Font->Name = REPORT_FONT_NAME;
   print_ptr->Canvas->Font->Size = 14;
   print_ptr->Canvas->Font->Style = font_style;
   print_ptr->Canvas->TextOut(print_area->Right - 2 - print_ptr->Canvas->TextWidth(S),
                              ypos,
                              S);
   // PM CR
}

//---------------------------------------------------------------------------
void Tfrm_report_pwa::print_report_clinical_pressures(TPrinter *print_ptr, TRect *print_area)
{
   int          ypos;
   AnsiString   S;
   TFontStyles  font_style;
   float separation_factor = 1.50;

   font_style << fsBold;
   print_ptr->Canvas->Font->Name = REPORT_FONT_NAME;
   print_ptr->Canvas->Font->Size = 10;
   print_ptr->Canvas->Font->Style = font_style;
   S = "Aortic";
   print_ptr->Canvas->TextOut(print_area->Left,
                              print_area->Top,
                              S);

   //Central Systolic
   font_style.Clear();
   print_ptr->Canvas->Font->Style = font_style;
   S = lbl_csp_title->Caption;
   ypos = print_area->Top + ((separation_factor + 0.5) * print_ptr->Canvas->TextHeight(S));
   print_ptr->Canvas->TextOut(print_area->Left + 2,
                              ypos,
                              S);

   ypos = ypos + print_ptr->Canvas->TextHeight(S);
   S = lbl_csp->Caption;
   font_style << fsBold;
   print_ptr->Canvas->Font->Name = REPORT_FONT_NAME;
   print_ptr->Canvas->Font->Size = 14;
   print_ptr->Canvas->Font->Style = font_style;
   print_ptr->Canvas->TextOut(print_area->Left + 2,
                              ypos,
                              S);

   //Central Diastolic
   ypos = ypos + (separation_factor * print_ptr->Canvas->TextHeight(S));

   font_style.Clear();

   print_ptr->Canvas->Font->Name = REPORT_FONT_NAME;
   print_ptr->Canvas->Font->Size = 10;
   print_ptr->Canvas->Font->Style = font_style;
   S = lbl_cdp_title->Caption;
   print_ptr->Canvas->TextOut(print_area->Left + 2,
                              ypos,
                              S);

   ypos = ypos + print_ptr->Canvas->TextHeight(S);
   S = lbl_cdp->Caption;
   font_style << fsBold;
   print_ptr->Canvas->Font->Name = REPORT_FONT_NAME;
   print_ptr->Canvas->Font->Size = 14;
   print_ptr->Canvas->Font->Style = font_style;
   print_ptr->Canvas->TextOut(print_area->Left + 2,
                              ypos,
                              S);

   //Central Mean Pressure
   ypos = ypos + (separation_factor * print_ptr->Canvas->TextHeight(S));

   font_style.Clear();

   print_ptr->Canvas->Font->Name = REPORT_FONT_NAME;
   print_ptr->Canvas->Font->Size = 10;
   print_ptr->Canvas->Font->Style = font_style;
   S = lbl_cmp_title->Caption;
   print_ptr->Canvas->TextOut(print_area->Left + 2,
                              ypos,
                              S);

   ypos = ypos + print_ptr->Canvas->TextHeight(S);
   S = lbl_cmp->Caption;
   font_style << fsBold;
   print_ptr->Canvas->Font->Name = REPORT_FONT_NAME;
   print_ptr->Canvas->Font->Size = 14;
   print_ptr->Canvas->Font->Style = font_style;
   print_ptr->Canvas->TextOut(print_area->Left + 2,
                              ypos,
                              S);

   //Central Pulse Pressure
   ypos = ypos + (separation_factor * print_ptr->Canvas->TextHeight(S));

   font_style.Clear();

   print_ptr->Canvas->Font->Name = REPORT_FONT_NAME;
   print_ptr->Canvas->Font->Size = 10;
   print_ptr->Canvas->Font->Style = font_style;
   S = lbl_cpp_title->Caption;
   print_ptr->Canvas->TextOut(print_area->Left + 2,
                              ypos,
                              S);

   ypos = ypos + print_ptr->Canvas->TextHeight(S);
   S = lbl_cpp->Caption;
   font_style << fsBold;
   print_ptr->Canvas->Font->Name = REPORT_FONT_NAME;
   print_ptr->Canvas->Font->Size = 14;
   print_ptr->Canvas->Font->Style = font_style;
   print_ptr->Canvas->TextOut(print_area->Left + 2,
                              ypos,
                              S);

   // Augmentation Pressure
   if (!config_get_clinical_option())
   {
      ypos = ypos + (separation_factor * print_ptr->Canvas->TextHeight(S));
      font_style.Clear();

      print_ptr->Canvas->Font->Name = REPORT_FONT_NAME;
      print_ptr->Canvas->Font->Size = 10;
      print_ptr->Canvas->Font->Style = font_style;


      S = lbl_clinical_ap_title->Caption;
      print_ptr->Canvas->TextOut(print_area->Left + 2,
                                    ypos,
                                    S);

      ypos = ypos + print_ptr->Canvas->TextHeight(S);

      font_style.Clear();
      S = lbl_clinical_ap->Caption;
      font_style << fsBold;
      print_ptr->Canvas->Font->Name = REPORT_FONT_NAME;
      print_ptr->Canvas->Font->Size = 14;
      print_ptr->Canvas->Font->Style = font_style;
      print_ptr->Canvas->TextOut(print_area->Left + 2,
                                    ypos,
                                    S);
   }
   else
   {
      ypos = ypos + (separation_factor * print_ptr->Canvas->TextHeight(S));
   }

   // Heart Rate
   ypos = ypos + (separation_factor * print_ptr->Canvas->TextHeight(S));
   font_style.Clear();

   print_ptr->Canvas->Font->Name = REPORT_FONT_NAME;
   print_ptr->Canvas->Font->Size = 10;
   print_ptr->Canvas->Font->Style = font_style;


   S = "HR";
   print_ptr->Canvas->TextOut(print_area->Left + 2,
                                 ypos,
                                 S);

   ypos = ypos + print_ptr->Canvas->TextHeight(S);

   font_style.Clear();
   S = lbl_clinical_hr->Caption;
   font_style << fsBold;
   print_ptr->Canvas->Font->Name = REPORT_FONT_NAME;
   print_ptr->Canvas->Font->Size = 14;
   print_ptr->Canvas->Font->Style = font_style;
   print_ptr->Canvas->TextOut(print_area->Left + 2,
                                 ypos,
                                 S);
}
//---------------------------------------------------------------------------
void Tfrm_report_pwa::print_report_central_params(TPrinter *print_ptr, TRect *print_area)
{
   int          width;
   int          xpos;
   int          text_width;
   int          text_height;
   int          line_num = 1;
   AnsiString   S;
   TFontStyles  font_style;
   TFontStyles  bold_font;

   bold_font.Clear();
   bold_font << fsBold;

   width = print_area->Right - print_area->Left;
   font_style.Clear();

   // Peripheral Data
   print_ptr->Canvas->Font->Name = REPORT_FONT_NAME;
   print_ptr->Canvas->Font->Size = 8;
   print_ptr->Canvas->Font->Style = font_style;
   text_width = print_ptr->Canvas->TextWidth(lbl_periph_data_title->Caption);
   print_ptr->Canvas->TextOut(print_area->Left,
                              print_area->Top - (print_area->Top * 0.02),
                              lbl_periph_data_title->Caption);

   print_ptr->Canvas->TextOut(print_area->Left + text_width,
                              print_area->Top - (print_area->Top * 0.02),
                              lbl_periph_data->Caption);

   // PP Amplification
   text_width = print_ptr->Canvas->TextWidth(lbl_ppamp->Caption) + print_ptr->Canvas->TextWidth("XXXX");
   print_ptr->Canvas->TextOut(print_area->Right - text_width,
                              print_area->Top - (print_area->Top * 0.02),
                              lbl_ppamp->Caption);
   text_width = text_width + print_ptr->Canvas->TextWidth(lbl_ppamplification_title->Caption);
   print_ptr->Canvas->TextOut(print_area->Right - text_width,
                              print_area->Top - (print_area->Top * 0.02),
                              lbl_ppamplification_title->Caption);


   font_style << fsBold;
   S = "CENTRAL HAEMODYNAMIC PARAMETERS";
   text_height = print_ptr->Canvas->TextHeight(S);
   print_ptr->Canvas->Font->Name = REPORT_FONT_NAME;
   print_ptr->Canvas->Font->Size = 12;
   print_ptr->Canvas->Font->Style = font_style;
   print_ptr->Canvas->TextOut(print_area->Left,
                              print_area->Top + (line_num * text_height),
                              S);

   ++line_num;
   ++line_num;
   font_style.Clear();
   print_ptr->Canvas->Font->Name = REPORT_FONT_NAME;
   print_ptr->Canvas->Font->Size = 8;
   print_ptr->Canvas->Font->Style = font_style;

   S = "Ejection Duration (ED)  ";
   /*
   ** Use this for a constant text height amongst headings
   */
   text_height = print_ptr->Canvas->TextHeight(S);
   text_width = print_ptr->Canvas->TextWidth(S);
   xpos = print_area->Left + text_width;

   S = "Heart Rate, Period ";
   print_ptr->Canvas->TextOut(print_area->Left,
                              print_area->Top + (line_num * text_height),
                              S);
   print_ptr->Canvas->Font->Style = bold_font;
   print_ptr->Canvas->TextOut(xpos,
                              print_area->Top + (line_num * text_height),//print_ptr->Canvas->TextHeight(S)),
                              lbl_hr->Caption);
   print_ptr->Canvas->Font->Style = font_style;
   ++line_num;

   S = "Ejection Duration (ED) ";
   print_ptr->Canvas->TextOut(print_area->Left,
                              print_area->Top + (line_num * text_height),
                              S);
    print_ptr->Canvas->Font->Style = lbl_ed->Font->Style;
    print_ptr->Canvas->TextOut(xpos,
                              print_area->Top + (line_num * text_height),
                              lbl_ed->Caption);
    print_ptr->Canvas->Font->Style = font_style;
   ++line_num;

   S = "Aortic T1, T2, Tr";
   print_ptr->Canvas->TextOut(print_area->Left,
                              print_area->Top + (line_num * text_height),
                              S);
   print_ptr->Canvas->Font->Style = bold_font;
   print_ptr->Canvas->TextOut(xpos,
                              print_area->Top + (line_num * text_height),
                              lbl_t1t2->Caption);
   print_ptr->Canvas->Font->Style = font_style;
   ++line_num;

   // Augmentation Load
   /*S = lbl_al_title->Caption + " ";
   print_ptr->Canvas->TextOut(print_area->Left,
                              print_area->Top + (line_num * text_height),
                              S);
   print_ptr->Canvas->Font->Style = lbl_svr->Font->Style;
   print_ptr->Canvas->TextOut(xpos,
                              print_area->Top + (line_num * text_height),
                              lbl_al->Caption);
   print_ptr->Canvas->Font->Style = font_style;*/
   line_num = 3;

   S = "Aortic AIx (AP/PP) @HR75  ";
   text_width = print_ptr->Canvas->TextWidth(S);
   xpos = width / 3 + text_width;

   S = "P1 Height(P1 - Dp) ";
   print_ptr->Canvas->TextOut(width / 3 + print_area->Left,
                              print_area->Top + (line_num * text_height),
                              S);
   print_ptr->Canvas->Font->Style = bold_font;
   print_ptr->Canvas->TextOut(xpos + print_area->Left,
                              print_area->Top + (line_num * text_height),
                              lbl_p1->Caption);
   print_ptr->Canvas->Font->Style = font_style;
   ++line_num;

   S = "Aortic Augmentation (AP) ";
   print_ptr->Canvas->TextOut(width / 3 + print_area->Left,
                              print_area->Top + (line_num * text_height),
                              S);
   print_ptr->Canvas->Font->Style = lbl_aug->Font->Style;
   print_ptr->Canvas->TextOut(xpos + print_area->Left,
                              print_area->Top + (line_num * text_height),
                              lbl_aug->Caption);
   print_ptr->Canvas->Font->Style = font_style;
   ++line_num;

   S = "Aortic AIx (AP/PP, P2/P1)  ";
   print_ptr->Canvas->TextOut(width / 3 + print_area->Left,
                              print_area->Top + (line_num * text_height),
                              S);
   print_ptr->Canvas->Font->Style = lbl_aug_idx->Font->Style;
   print_ptr->Canvas->TextOut(xpos + print_area->Left,
                              print_area->Top + (line_num * text_height),
                              lbl_aug_idx->Caption);
   print_ptr->Canvas->Font->Style = font_style;
   ++line_num;

   S = "Aortic AIx (AP/PP) @HR75  ";
   print_ptr->Canvas->TextOut(width / 3 + print_area->Left,
                              print_area->Top + (line_num * text_height),
                              S);
   print_ptr->Canvas->Font->Style = lbl_augidx_hr75->Font->Style;
   print_ptr->Canvas->TextOut(xpos + print_area->Left,
                              print_area->Top + (line_num * text_height),
                              lbl_augidx_hr75->Caption);
   print_ptr->Canvas->Font->Style = font_style;

   line_num = 3;

   S = lbl_pti_title->Caption + "  ";
   text_width = print_ptr->Canvas->TextWidth(S);
   xpos = 2 * width / 3 + text_width;

   // SEVR
   S = lbl_svr_title->Caption + " ";
   print_ptr->Canvas->TextOut(2 * width / 3 + print_area->Left,
                              print_area->Top + (line_num * text_height),
                              S);
   print_ptr->Canvas->Font->Style = lbl_svr->Font->Style;
   print_ptr->Canvas->TextOut(xpos + print_area->Left,
                              print_area->Top + (line_num * text_height),
                              lbl_svr->Caption);
   print_ptr->Canvas->Font->Style = font_style;
   ++line_num;

   // PTI
   S = lbl_pti_title->Caption + " ";
   print_ptr->Canvas->TextOut(2 * width / 3 + print_area->Left,
                              print_area->Top + (line_num * text_height),
                              S);
   print_ptr->Canvas->Font->Style = lbl_pti->Font->Style;
   print_ptr->Canvas->TextOut(xpos + print_area->Left,
                              print_area->Top + (line_num * text_height),
                              lbl_pti->Caption);
   print_ptr->Canvas->Font->Style = font_style;
   ++line_num;

   S = "End Systolic Pressure ";
   print_ptr->Canvas->TextOut(2 * width / 3 + print_area->Left,
                              print_area->Top + (line_num * text_height),
                              S);
   print_ptr->Canvas->Font->Style = lbl_endsyst->Font->Style;
   print_ptr->Canvas->TextOut(xpos + print_area->Left,
                              print_area->Top + (line_num * text_height),
                              lbl_endsyst->Caption);
   print_ptr->Canvas->Font->Style = font_style;
   ++line_num;
   
   // MP
   S = lbl_title_mp->Caption + " ";
   print_ptr->Canvas->TextOut(2 * width / 3 + print_area->Left,
                              print_area->Top + (line_num * text_height),
                              S);
   print_ptr->Canvas->Font->Style = lbl_mp->Font->Style;
   print_ptr->Canvas->TextOut(xpos + print_area->Left,
                              print_area->Top + (line_num * text_height),
                              lbl_mp->Caption);
   print_ptr->Canvas->Font->Style = font_style;
}

// PM V9
void Tfrm_report_pwa::print_report_clinical_central_params(TPrinter *print_ptr, TRect *print_area)
{
   TRect        rect;
   int          width;
   int          height;
   int          xpos;
   int          ypos;
   int          text_height;
   int          text_width;
   TFontStyles  font_style;
   String       S;
   TPicture*    picture;

   // Ensure the normals displays are visible for printing
   pnl_clinical_sp->Color = sphygmocor_white;
   lbl_clinical_csp_title->Font->Color = sphygmocor_black;
   lbl_clinical_csp_units->Font->Color = sphygmocor_black;
   shape_clinical_sp_lower->Pen->Color = sphygmocor_black;
   lbl_clinical_sp_lower->Font->Color = sphygmocor_black;
   shape_clinical_sp_upper->Pen->Color = sphygmocor_black;
   lbl_clinical_sp_upper->Font->Color = sphygmocor_black;
   // If the range is white, change to black. If it's red, leave it
   if (shape_clinical_sp->Brush->Color == sphygmocor_white)
   {
      shape_clinical_sp->Brush->Color = sphygmocor_black;
      shape_clinical_sp->Pen->Color = sphygmocor_black;
      lbl_clinical_sp->Font->Color = sphygmocor_black;
   }

   pnl_clinical_pp->Color = sphygmocor_white;
   lbl_clinical_cpp_title->Font->Color = sphygmocor_black;
   lbl_clinical_cpp_units->Font->Color = sphygmocor_black;
   shape_clinical_pp_lower->Pen->Color = sphygmocor_black;
   lbl_clinical_pp_lower->Font->Color = sphygmocor_black;
   shape_clinical_pp_upper->Pen->Color = sphygmocor_black;
   lbl_clinical_pp_upper->Font->Color = sphygmocor_black;
   if (shape_clinical_pp->Brush->Color == sphygmocor_white)
   {
      shape_clinical_pp->Brush->Color = sphygmocor_black;
      shape_clinical_pp->Pen->Color = sphygmocor_black;
      lbl_clinical_pp->Font->Color = sphygmocor_black;
   }

   pnl_clinical_ap->Color = sphygmocor_white;
   lbl_clinical_ap_title->Font->Color = sphygmocor_black;
   lbl_clinical_ap_units->Font->Color = sphygmocor_black;
   shape_clinical_ap_lower->Pen->Color = sphygmocor_black;
   lbl_clinical_ap_lower->Font->Color = sphygmocor_black;
   shape_clinical_ap_upper->Pen->Color = sphygmocor_black;
   lbl_clinical_ap_upper->Font->Color = sphygmocor_black;
   if (shape_clinical_ap->Brush->Color == sphygmocor_white)
   {
      shape_clinical_ap->Brush->Color = sphygmocor_black;
      shape_clinical_ap->Pen->Color = sphygmocor_black;
      lbl_clinical_ap->Font->Color = sphygmocor_black;
   }

   pnl_clinical_aixhr75->Color = sphygmocor_white;
   lbl_clinical_aixhr75_title->Font->Color = sphygmocor_black;
   lbl_clinical_aixhr75_units->Font->Color = sphygmocor_black;
   shape_clinical_aixhr75_lower->Pen->Color = sphygmocor_black;
   lbl_clinical_aixhr75_lower->Font->Color = sphygmocor_black;
   shape_clinical_aixhr75_upper->Pen->Color = sphygmocor_black;
   lbl_clinical_aixhr75_upper->Font->Color = sphygmocor_black;
   if (shape_clinical_aixhr75->Brush->Color == sphygmocor_white)
   {
      shape_clinical_aixhr75->Brush->Color = sphygmocor_black;
      shape_clinical_aixhr75->Pen->Color = sphygmocor_black;
      lbl_clinical_aixhr75->Font->Color = sphygmocor_black;
   }

   pnl_clinical_aix->Color = sphygmocor_white;
   lbl_clinical_aix_title->Font->Color = sphygmocor_black;
   lbl_clinical_aix_units->Font->Color = sphygmocor_black;
   shape_clinical_aix_lower->Pen->Color = sphygmocor_black;
   lbl_clinical_aix_lower->Font->Color = sphygmocor_black;
   shape_clinical_aix_upper->Pen->Color = sphygmocor_black;
   lbl_clinical_aix_upper->Font->Color = sphygmocor_black;
   if (shape_clinical_aix->Brush->Color == sphygmocor_white)
   {
      shape_clinical_aix->Brush->Color = sphygmocor_black;
      shape_clinical_aix->Pen->Color = sphygmocor_black;
      lbl_clinical_aix->Font->Color = sphygmocor_black;
   }

   pnl_clinical_reference_age->Color = sphygmocor_white;
   lbl_clinical_cv_age_title->Font->Color = sphygmocor_black;
   lbl_age_20->Font->Color = sphygmocor_black;
   lbl_age_30->Font->Color = sphygmocor_black;
   lbl_age_40->Font->Color = sphygmocor_black;
   lbl_age_50->Font->Color = sphygmocor_black;
   lbl_age_60->Font->Color = sphygmocor_black;
   lbl_age_70->Font->Color = sphygmocor_black;
   lbl_age_80->Font->Color = sphygmocor_black;
   lbl_clinical_hr_title->Visible = false;
   lbl_clinical_hr->Visible = false;

   width = print_area->Right - print_area->Left;
   height = print_area->Bottom - print_area->Top;
   //rect.Left = print_area->Left + width / 4;
   //rect.Right = print_area->Right - width / 4;

   print_ptr->Canvas->Font->Name = REPORT_FONT_NAME;
   print_ptr->Canvas->Font->Size = 8;

   // PM CR
   // Determine the scale between the screen and printer resolutions
   int x_scale = (GetDeviceCaps(print_ptr->Handle, LOGPIXELSX)) / (GetDeviceCaps(this->Canvas->Handle, LOGPIXELSX));
   int y_scale = (GetDeviceCaps(print_ptr->Handle, LOGPIXELSY)) / (GetDeviceCaps(this->Canvas->Handle, LOGPIXELSY));

   rect.Left = print_area->Left + print_ptr->Canvas->TextWidth(S);
   rect.Right = print_area->Left + pnl_clinical_sp->Width * x_scale;

   // Map the Printer resolution to the screen
   int previous_mode = SetMapMode(print_ptr->Canvas->Handle, MM_ANISOTROPIC);
   SetWindowExtEx(print_ptr->Canvas->Handle,
                GetDeviceCaps(this->Canvas->Handle, LOGPIXELSX),
                GetDeviceCaps(this->Canvas->Handle, LOGPIXELSY),
                NULL);
   SetViewportExtEx(print_ptr->Canvas->Handle,
                GetDeviceCaps(print_ptr->Canvas->Handle, LOGPIXELSX),
                GetDeviceCaps(print_ptr->Canvas->Handle, LOGPIXELSY),
                NULL);

   // Print Reference Age first because it overlaps the bottom panel
   // Reference Age
   xpos = print_area->Left / x_scale;
   ypos = print_area->Top / y_scale + 255;
   pnl_clinical_reference_age->PaintTo(print_ptr->Canvas->Handle, xpos, ypos);

   // SP
   ypos = print_area->Top / y_scale;
   pnl_clinical_sp->PaintTo(print_ptr->Canvas->Handle, xpos, ypos);

   // PP
   ypos = ypos + pnl_clinical_sp->Height;
   pnl_clinical_pp->PaintTo(print_ptr->Canvas->Handle, xpos, ypos);

   // AP
   ypos = ypos + pnl_clinical_pp->Height;
   pnl_clinical_ap->PaintTo(print_ptr->Canvas->Handle, xpos, ypos);

   // AIx
   // Only print if it is enabled
   if (config_get_clinical_aix())
   {
      ypos = ypos + pnl_clinical_ap->Height;
      pnl_clinical_aix->PaintTo(print_ptr->Canvas->Handle, xpos, ypos);
   }

   // AIx @ HR75
   // Only print if it is enabled
   if (config_get_clinical_aixhr75())
   {
      ypos = ypos + pnl_clinical_ap->Height;
      pnl_clinical_aixhr75->PaintTo(print_ptr->Canvas->Handle, xpos, ypos);
   }

   // Restore the printer mapping so the rest of the report prints correctly
   SetMapMode(print_ptr->Canvas->Handle, previous_mode);

   // Paint the entire panel to an image and then use StretchDraw so you can
   // control the dimensions on the printed report

   /*S = lbl_clinical_aixhr75_title->Caption + " ";
   xpos = print_area->Left;
   text_height = print_ptr->Canvas->TextHeight(S);

   rect.Left = print_area->Left + print_ptr->Canvas->TextWidth(S);
   rect.Right = print_area->Right - width / 2 + print_ptr->Canvas->TextWidth(S) / 2;

   // SP
   pnl_clinical_sp->PaintTo(frm_main->img_print_clinical->Canvas->Handle, -60, 0);
   rect.Top = print_area->Top;
   rect.Bottom = print_area->Top + frm_main->img_print_clinical->Height * y_scale;
   print_ptr->Canvas->StretchDraw(rect, frm_main->img_print_clinical->Picture->Bitmap);

   S = lbl_clinical_csp_title->Caption;
   ypos = rect.Top + text_height;
   print_ptr->Canvas->TextOut(xpos, ypos, S);

   S = lbl_clinical_csp_units->Caption;
   ypos = ypos + text_height;
   print_ptr->Canvas->TextOut(xpos, ypos, S);

   // PP
   pnl_clinical_pp->PaintTo(frm_main->img_print_clinical->Canvas->Handle, -60, 0);
   rect.Top = print_area->Top + height / 6;
   rect.Bottom = print_area->Top + height / 3;
   print_ptr->Canvas->StretchDraw(rect, frm_main->img_print_clinical->Picture->Bitmap);

   S = lbl_clinical_cpp_title->Caption;
   ypos = rect.Top + text_height;
   print_ptr->Canvas->TextOut(xpos, ypos, S);

   S = lbl_clinical_cpp_units->Caption;
   ypos = ypos + text_height;
   print_ptr->Canvas->TextOut(xpos, ypos, S);

   // AP
   pnl_clinical_ap->PaintTo(frm_main->img_print_clinical->Canvas->Handle, -60, 0);
   rect.Top = print_area->Top + height / 3;
   rect.Bottom = print_area->Top + height / 2;
   print_ptr->Canvas->StretchDraw(rect, frm_main->img_print_clinical->Picture->Bitmap);

   S = lbl_clinical_ap_title->Caption;
   ypos = rect.Top + text_height;
   print_ptr->Canvas->TextOut(xpos, ypos, S);

   S = lbl_clinical_ap_units->Caption;
   ypos = ypos + text_height;
   print_ptr->Canvas->TextOut(xpos, ypos, S);

   // AIx
   // Only print if it is enabled
   if (config_get_clinical_aix())
   {
      pnl_clinical_aix->PaintTo(frm_main->img_print_clinical->Canvas->Handle, -60, 0);
      rect.Top = print_area->Top + height / 2;
      rect.Bottom = print_area->Top + height * 2 / 3;
      print_ptr->Canvas->StretchDraw(rect, frm_main->img_print_clinical->Picture->Bitmap);

      S = lbl_clinical_aix_title->Caption;
      ypos = rect.Top + text_height;
      print_ptr->Canvas->TextOut(xpos, ypos, S);

      S = lbl_clinical_aix_units->Caption;
      ypos = ypos + text_height;
      print_ptr->Canvas->TextOut(xpos, ypos, S);
   }

   // AIx @ HR75
   // Only print if it is enabled
   if (config_get_clinical_aixhr75())
   {
      pnl_clinical_aixhr75->PaintTo(frm_main->img_print_clinical->Canvas->Handle, -60, 0);
      rect.Top = print_area->Top + height * 2 / 3;
      rect.Bottom = print_area->Top + height * 5 / 6;
      print_ptr->Canvas->StretchDraw(rect, frm_main->img_print_clinical->Picture->Bitmap);

      S = lbl_clinical_aixhr75_title->Caption;
      ypos = rect.Top + text_height;
      print_ptr->Canvas->TextOut(xpos, ypos, S);

      S = lbl_clinical_aixhr75_units->Caption;
      ypos = ypos + text_height;
      print_ptr->Canvas->TextOut(xpos, ypos, S);
   }

   // Reference Age
   pnl_clinical_reference_age->PaintTo(frm_main->img_print_reference_age->Canvas->Handle, -40, 0);
   rect.Top = print_area->Top + height * 5 / 6;
   rect.Bottom = print_area->Top + height;
   print_ptr->Canvas->StretchDraw(rect, frm_main->img_print_reference_age->Picture->Bitmap);
   */
   // Restore display
   pnl_clinical_sp->Color = sphygmocor_background;
   lbl_clinical_csp_title->Font->Color = sphygmocor_white;
   lbl_clinical_csp_units->Font->Color = sphygmocor_white;
   shape_clinical_sp_lower->Pen->Color = sphygmocor_white;
   lbl_clinical_sp_lower->Font->Color = sphygmocor_white;
   shape_clinical_sp_upper->Pen->Color = sphygmocor_white;
   lbl_clinical_sp_upper->Font->Color = sphygmocor_white;
   if (shape_clinical_sp->Brush->Color == sphygmocor_black)
   {
      shape_clinical_sp->Brush->Color = sphygmocor_white;
      shape_clinical_sp->Pen->Color = sphygmocor_white;
      lbl_clinical_sp->Font->Color = sphygmocor_white;
   }

   pnl_clinical_pp->Color = sphygmocor_background;
   lbl_clinical_cpp_title->Font->Color = sphygmocor_white;
   lbl_clinical_cpp_units->Font->Color = sphygmocor_white;
   shape_clinical_pp_lower->Pen->Color = sphygmocor_white;
   lbl_clinical_pp_lower->Font->Color = sphygmocor_white;
   shape_clinical_pp_upper->Pen->Color = sphygmocor_white;
   lbl_clinical_pp_upper->Font->Color = sphygmocor_white;
   if (shape_clinical_pp->Brush->Color == sphygmocor_black)
   {
      shape_clinical_pp->Brush->Color = sphygmocor_white;
      shape_clinical_pp->Pen->Color = sphygmocor_white;
      lbl_clinical_pp->Font->Color = sphygmocor_white;
   }

   pnl_clinical_ap->Color = sphygmocor_background;
   lbl_clinical_ap_title->Font->Color = sphygmocor_white;
   lbl_clinical_ap_units->Font->Color = sphygmocor_white;
   shape_clinical_ap_lower->Pen->Color = sphygmocor_white;
   lbl_clinical_ap_lower->Font->Color = sphygmocor_white;
   shape_clinical_ap_upper->Pen->Color = sphygmocor_white;
   lbl_clinical_ap_upper->Font->Color = sphygmocor_white;
   if (shape_clinical_ap->Brush->Color == sphygmocor_black)
   {
      shape_clinical_ap->Brush->Color = sphygmocor_white;
      shape_clinical_ap->Pen->Color = sphygmocor_white;
      lbl_clinical_ap->Font->Color = sphygmocor_white;
   }

   pnl_clinical_aixhr75->Color = sphygmocor_background;
   lbl_clinical_aixhr75_title->Font->Color = sphygmocor_white;
   lbl_clinical_aixhr75_units->Font->Color = sphygmocor_white;
   shape_clinical_aixhr75_lower->Pen->Color = sphygmocor_white;
   lbl_clinical_aixhr75_lower->Font->Color = sphygmocor_white;
   shape_clinical_aixhr75_upper->Pen->Color = sphygmocor_white;
   lbl_clinical_aixhr75_upper->Font->Color = sphygmocor_white;
   if (shape_clinical_aixhr75->Brush->Color == sphygmocor_black)
   {
      shape_clinical_aixhr75->Brush->Color = sphygmocor_white;
      shape_clinical_aixhr75->Pen->Color = sphygmocor_white;
      lbl_clinical_aixhr75->Font->Color = sphygmocor_white;
   }

   pnl_clinical_aix->Color = sphygmocor_background;
   lbl_clinical_aix_title->Font->Color = sphygmocor_white;
   lbl_clinical_aix_units->Font->Color = sphygmocor_white;
   shape_clinical_aix_lower->Pen->Color = sphygmocor_white;
   lbl_clinical_aix_lower->Font->Color = sphygmocor_white;
   shape_clinical_aix_upper->Pen->Color = sphygmocor_white;
   lbl_clinical_aix_upper->Font->Color = sphygmocor_white;
   if (shape_clinical_aix->Brush->Color == sphygmocor_black)
   {
      shape_clinical_aix->Brush->Color = sphygmocor_white;
      shape_clinical_aix->Pen->Color = sphygmocor_white;
      lbl_clinical_aix->Font->Color = sphygmocor_white;
   }

   pnl_clinical_reference_age->Color = sphygmocor_background;
   lbl_clinical_cv_age_title->Font->Color = sphygmocor_white;
   lbl_age_20->Font->Color = sphygmocor_white;
   lbl_age_30->Font->Color = sphygmocor_white;
   lbl_age_40->Font->Color = sphygmocor_white;
   lbl_age_50->Font->Color = sphygmocor_white;
   lbl_age_60->Font->Color = sphygmocor_white;
   lbl_age_70->Font->Color = sphygmocor_white;
   lbl_age_80->Font->Color = sphygmocor_white;
   lbl_clinical_hr_title->Visible = true;
   lbl_clinical_hr->Visible = true;

   // Interpretation
   ypos = print_area->Top + height * 0.08;
   xpos = rect.Right + width * 0.06;
   int x1 = xpos;
   int y1 = ypos;
   int x2 = print_area->Right;
   int y2 = print_area->Bottom;
   print_ptr->Canvas->Pen->Width = 3;
   print_ptr->Canvas->Pen->Color = sphygmocor_grey;
   print_ptr->Canvas->Rectangle(x1, y1, x2, y2);

   // Insert the title
   font_style << fsItalic;
   print_ptr->Canvas->Font->Style = font_style;
   S = "Interpretation: ";
   text_width = print_ptr->Canvas->TextWidth(S);
   ypos = ypos + print_ptr->Canvas->TextHeight(S);
   print_ptr->Canvas->TextOut(xpos + 10,
                              ypos,
                              S);

   // Display the Interpretation field over 3 lines
   font_style.Clear();
   print_ptr->Canvas->Font->Style = font_style;
   String report_intptn = MsgBox_ReplaceCarriage(report_pwa->Interpretation);
   int report_intptn_len = report_intptn.Length();
   String report_intptn_line1 = "";
   String report_intptn_line2 = "";
   String report_intptn_line3 = "";
   if (report_intptn_len < 50)
   {
      report_intptn_line1 = report_intptn.SubString(1, report_intptn_len);
   }
   else if (report_intptn_len < 100)
   {
      report_intptn_line1 = report_intptn.SubString(1, 50);
      report_intptn_line2 = report_intptn.SubString(51, report_intptn_len - 50);
   }
   else
   {
      report_intptn_line1 = report_intptn.SubString(1, 50);
      report_intptn_line2 = report_intptn.SubString(51, 50);
      report_intptn_line3 = report_intptn.SubString(101, report_intptn_len - 100);
   }
   print_ptr->Canvas->TextOut(xpos + text_width + 5,
                                 ypos,
                                 report_intptn_line1);
   print_ptr->Canvas->TextOut(xpos + text_width + 5,
                                 ypos + print_ptr->Canvas->TextHeight(S),
                                 report_intptn_line2);
   print_ptr->Canvas->TextOut(xpos + text_width + 5,
                                 ypos + (2 * print_ptr->Canvas->TextHeight(S)),
                                 report_intptn_line3);

   // Insert the Physician and Signature labels
   font_style << fsItalic;
   print_ptr->Canvas->Font->Style = font_style;
   S = "Physician: ";
   ypos = y2 - (6 * print_ptr->Canvas->TextHeight(S));
   print_ptr->Canvas->TextOut(xpos + 10,
                              ypos,
                              S);
   S = "Signature: ";
   ypos = y2 - (2 * print_ptr->Canvas->TextHeight(S));
   print_ptr->Canvas->TextOut(xpos + 10,
                              ypos,
                              S);
}
//---------------------------------------------------------------------------
void Tfrm_report_pwa::print_report_avi_params(TPrinter *print_ptr, TRect *print_area)
{
   int          xpos;
   int          text_width;
   int          text_height;
   int          line_num = 1;
   AnsiString   S;
   TFontStyles  font_style;
   TFontStyles  bold_font;

   bold_font.Clear();
   bold_font << fsBold;

   font_style.Clear();

   font_style << fsBold;
   S = "WAVE REFLECTION PARAMETERS";
   text_height = print_ptr->Canvas->TextHeight(S);
   print_ptr->Canvas->Font->Name = REPORT_FONT_NAME;
   print_ptr->Canvas->Font->Size = 10;
   print_ptr->Canvas->Font->Style = font_style;
   print_ptr->Canvas->TextOut(print_area->Left,
                              print_area->Top + (line_num * text_height),
                              S);

   ++line_num;
   ++line_num;
   ++line_num;
   font_style.Clear();
   print_ptr->Canvas->Font->Name = REPORT_FONT_NAME;
   print_ptr->Canvas->Font->Size = 8;
   print_ptr->Canvas->Font->Style = font_style;

   S = lbl_avi_distance_title->Caption + "  ";
   /*
   ** Use this for a constant text height amongst headings
   */
   text_height = print_ptr->Canvas->TextHeight(S);
   text_width = print_ptr->Canvas->TextWidth(S);
   xpos = print_area->Left + text_width;

   // Forward Pressure Pulse Height
   S = lbl_avi_ipph_title->Caption;
   print_ptr->Canvas->TextOut(print_area->Left,
                              print_area->Top + (line_num * text_height),
                              S);
    print_ptr->Canvas->Font->Style = lbl_ed->Font->Style;
    print_ptr->Canvas->TextOut(xpos,
                              print_area->Top + (line_num * text_height),
                              lbl_avi_ipph->Caption);
    print_ptr->Canvas->Font->Style = font_style;
   ++line_num;

   // Reflected Pressure Pulse Height
   S = lbl_avi_rpph_title->Caption;
   print_ptr->Canvas->TextOut(print_area->Left,
                              print_area->Top + (line_num * text_height),
                              S);
    print_ptr->Canvas->Font->Style = lbl_ed->Font->Style;
    print_ptr->Canvas->TextOut(xpos,
                              print_area->Top + (line_num * text_height),
                              lbl_avi_rpph->Caption);
    print_ptr->Canvas->Font->Style = font_style;
   ++line_num;

   // Reflection Index
   S = lbl_avi_ri_title->Caption;
   print_ptr->Canvas->TextOut(print_area->Left,
                              print_area->Top + (line_num * text_height),
                              S);
   print_ptr->Canvas->Font->Style = lbl_avi_ri->Font->Style;
   print_ptr->Canvas->TextOut(xpos,
                              print_area->Top + (line_num * text_height),
                              lbl_avi_ri->Caption);
   print_ptr->Canvas->Font->Style = font_style;
   ++line_num;
   ++line_num;
   
   // Forward Pressure Peak Time
   S = lbl_avi_ippt_title->Caption;
   print_ptr->Canvas->TextOut(print_area->Left,
                              print_area->Top + (line_num * text_height),
                              S);
   print_ptr->Canvas->Font->Style = bold_font;
   print_ptr->Canvas->TextOut(xpos,
                              print_area->Top + (line_num * text_height),
                              lbl_avi_ippt->Caption);
   print_ptr->Canvas->Font->Style = font_style;
   ++line_num;

   // Reflected Pressure Peak Time
   S = lbl_avi_rppt_title->Caption;
   print_ptr->Canvas->TextOut(print_area->Left,
                              print_area->Top + (line_num * text_height),
                              S);
   print_ptr->Canvas->Font->Style = bold_font;
   print_ptr->Canvas->TextOut(xpos,
                              print_area->Top + (line_num * text_height),
                              lbl_avi_rppt->Caption);
   print_ptr->Canvas->Font->Style = font_style;
   ++line_num;

   // Aortic Pulse Reflection Time
   S = lbl_avi_aptt_title->Caption;
   print_ptr->Canvas->TextOut(print_area->Left,
                              print_area->Top + (line_num * text_height),
                              S);
   print_ptr->Canvas->Font->Style = lbl_pti->Font->Style;
   print_ptr->Canvas->TextOut(xpos,
                              print_area->Top + (line_num * text_height),
                              lbl_avi_aptt->Caption);
   print_ptr->Canvas->Font->Style = font_style;
   ++line_num;
   // PM CR
   // Transmission Time
   S = lbl_avi_cftt_title->Caption;
   print_ptr->Canvas->TextOut(print_area->Left,
                              print_area->Top + (line_num * text_height),
                              S);
   print_ptr->Canvas->Font->Style = bold_font;
   print_ptr->Canvas->TextOut(xpos,
                              print_area->Top + (line_num * text_height),
                              lbl_avi_cftt->Caption);
   print_ptr->Canvas->Font->Style = font_style;
   ++line_num;

   // Distance
   S = lbl_avi_distance_title->Caption;
   print_ptr->Canvas->TextOut(print_area->Left,
                              print_area->Top + (line_num * text_height),
                              S);
   print_ptr->Canvas->Font->Style = lbl_svr->Font->Style;
   print_ptr->Canvas->TextOut(xpos,
                              print_area->Top + (line_num * text_height),
                              lbl_avi_distance->Caption);
   print_ptr->Canvas->Font->Style = font_style;
   ++line_num;

   // Pulse Wave Velocity
   S = lbl_avi_pwv_title->Caption;
   print_ptr->Canvas->Font->Size = 9;
   print_ptr->Canvas->TextOut(print_area->Left,
                              print_area->Top + (line_num * text_height),
                              S);
   print_ptr->Canvas->Font->Style = bold_font;
   print_ptr->Canvas->TextOut(xpos,
                              print_area->Top + (line_num * text_height),
                              lbl_avi_pwv->Caption);
   print_ptr->Canvas->Font->Style = font_style;
}
//---------------------------------------------------------------------------
void Tfrm_report_pwa::print_report_footer(TRect *print_area)
{
   print_do_footer(print_area, report_pwa->DataRev);
}

//---------------------------------------------------------------------------
void __fastcall Tfrm_report_pwa::srs_avg_t1_timingGetMarkText(
      TChartSeries *Sender, int ValueIndex, AnsiString &MarkText)
{
   if (ValueIndex == 0)
   {
      MarkText = RoundIntToStr(srs_avg_t1_timing->XValues->Value[ValueIndex]);
   }
   else
   {
      MarkText = RoundIntToStr(srs_avg_t1_timing->YValues->Value[ValueIndex]);
   }
}
//---------------------------------------------------------------------------
void Tfrm_report_pwa::report_display_study(void)
{
   PATIENT_RECORD_TYPE  pat;
   String hint;
   String lower_case;

   AnsiString S = PWAMTypeAsString[frm_report_pwa->report_pwa->MeasureType];

   lower_case = S.LowerCase();
   S = S.SubString(1,1) + lower_case.SubString(2, (S.Length() - 1));

   chrt_avg_periph->Title->Text->Clear();
   chrt_avg_periph->Title->Text->Add(S);

   if (!config_get_clinical_option())
   {
      lbl_clinical_peripheral->Caption = S;
   }

   lbl_date->Caption = frm_report_pwa->report_pwa->DateTime.FormatString(REPORT_PAT_DOB_DATE_FORMAT);
   lbl_time->Caption = frm_report_pwa->report_pwa->DateTime.TimeString();

   lbl_avi_date->Caption = lbl_date->Caption;
   lbl_avi_time->Caption = lbl_time->Caption;

   report_age = patient_get_age_at_date(report_pwa->DateTime);
   if (report_age)
   {
      lbl_age->Caption = IntToStr(report_age);
   }
   else
   {
      lbl_age->Caption = "???";
   }

   // PM V9
   // Messages are now displayed on the status bar
   // Reports are only valid for Radial measurements when the patient is of a mature age
   if (report_age >= PATIENT_YOUNG_AGE && report_pwa->MeasureType != PWA_CAROTID)
   {
      emma_display_statusbar_message("", "", "", sphygmocor_white);
      emma_display_statusbar_message("", "", sphygmocor_white);
      if (report_pwa->CalcIsInconclusive)
      {
         if (study_mode == MEAS_PWM_ID && report_pwa->InconclusiveNote == OPERATOR_INDEX_NOTE)
         {
            // PWM reports cannot be inconclusive because of Operator Index as it is not calculated
            report_pwa->CalcIsInconclusive = false;
         }
         else if (report_pwa->InconclusiveNote == OPERATOR_INDEX_NOTE)
         {
            emma_display_statusbar_message("Note:", report_pwa->InconclusiveNote,
                                          "", sphygmocor_maroon);
         }
         else
         {
            emma_display_statusbar_message("Note:", report_pwa->InconclusiveNote,
                                          ADVICE, sphygmocor_maroon);
         }
      }
   }
   else
   {
      if (report_age < PATIENT_YOUNG_AGE)
      {
         hint = "The SphygmoCor Transfer Function is Not Validated for Patients Under 18 Years of Age.";
         emma_display_statusbar_message("Not Validated:", "Patient Age.", hint, sphygmocor_maroon);
      }
      else
      {
         hint = "The Carotid-Central Transfer Function is Not Validated.";
         emma_display_statusbar_message("Not Validated:", "Carotid Measurement", hint, sphygmocor_maroon);
      }
   }
   // PM V9
   // Medications, Notes and Interpreation are now Edit boxes that utilise WordWrap
   edt_med->Text = MsgBox_ReplaceCarriage(frm_report_pwa->report_pwa->Medication.SubString(1, REPORT_MAX_PRINTED_MEMO_LENGTH));
   edt_interpretation->Text = MsgBox_ReplaceCarriage(frm_report_pwa->report_pwa->Interpretation.SubString(1, REPORT_MAX_PRINTED_MEMO_LENGTH));
   edt_notes->Text = MsgBox_ReplaceCarriage(frm_report_pwa->report_pwa->Notes.SubString(1, REPORT_MAX_PRINTED_MEMO_LENGTH));
   lbl_operator->Caption = frm_report_pwa->report_pwa->Operator;

   edtReason->Visible = false;
   lbl_reason_title->Visible = false;
   edt_avi_reason->Visible = false;
   lbl_avi_reason_title->Visible = false;
   bbtn_audit->Visible = false;

   lbl_operator_title->Caption = AUDIT_NO_CAPTION;
   lbl_operator_title->Font->Color = sphygmocor_black;
   lbl_operator->Font->Color = sphygmocor_navy;

   // If the audit option is set, display audit parameters.
   // There is no audit trail in PWM mode.
   if (config_get_audit_option() && study_mode == MEAS_PWA_ID)
   {
      S =  report_pwa->Operator;
      // If there is a reason for change, display it.
      if (report_pwa->Reason.Length() != 0)
      {
         edtReason->Text = MsgBox_ReplaceCarriage(report_pwa->Reason.SubString(1, REPORT_MAX_PRINTED_MEMO_LENGTH));
         edt_avi_reason->Text = edtReason->Text;
         lbl_reason_title->Visible = true;
         edtReason->Visible = true;
         lbl_avi_reason_title->Visible = true;
         edt_avi_reason->Visible = true;
      }

      switch (report_pwa->AuditFlag)
      {
         // The original report can be printed and deleted but has no audit trail
         case AUDIT_ORIGINAL:
            if (S.Length())
            {
               lbl_operator_title->Caption = AUDIT_ORIGINAL_CAPTION;
               lbl_operator_title->Font->Color = sphygmocor_navy;
            }
            bbtn_audit->Visible = false;
            if (config_get_report_style() != CONFIG_BLIND_REPORT_STYLE)
            {
               bbtn_print->Enabled = true;
            }
            bbtn_delete->Enabled = true;
            break;
         // The modified report can be printed and deleted and the audit trail can be viewed
         case AUDIT_MODIFIED:
            if (S.Length())
            {
               lbl_operator_title->Caption = AUDIT_MODIFIED_CAPTION;
               lbl_operator_title->Font->Color = sphygmocor_orange;
               lbl_operator->Font->Color = sphygmocor_orange;
            }
            bbtn_audit->Visible = true;
            if (config_get_report_style() != CONFIG_BLIND_REPORT_STYLE)
            {
               bbtn_print->Enabled = true;
            }
            bbtn_delete->Enabled = true;
            break;
         // The deleted report cannot be deleted nor printed but the audit trail can be viewed
         case AUDIT_DELETED:
            if (S.Length())
            {
               lbl_operator_title->Caption = AUDIT_DELETED_CAPTION;
               lbl_operator_title->Font->Color = sphygmocor_red;
               lbl_operator->Font->Color = sphygmocor_red;
            }
            bbtn_audit->Visible = true;
            bbtn_print->Enabled = false;
            bbtn_delete->Enabled = false;
            break;
      }

      // In audit mode, reports cannot be deleted and the audit button returns to the report screen
      if (pwa_audit_mode)
      {
         bbtn_audit->Visible = true;
         bbtn_delete->Enabled = false;
      }
   }

   if (report_pwa->Height > 0 && report_pwa->Height != DEFAULT_VALUE &&
         report_pwa->Weight > 0 && report_pwa->Weight != DEFAULT_VALUE &&
         report_pwa->Bmi > 0 && report_pwa->Bmi != DEFAULT_VALUE &&
         config_get_system_locale() == CONFIG_DEFAULT_LOCALE)
   {
      // Set bmi captions
     lbl_hwbmi->Caption = RoundIntToStr(report_pwa->Height) + "cm, " +
                                        RoundIntToStr(report_pwa->Weight) + "kg (" +
                                        FormatFloat("0.##", report_pwa->Bmi) + " kg/m²)";

   }
   else if (report_pwa->Height > 0 && report_pwa->Height != DEFAULT_VALUE &&
         config_get_system_locale() == CONFIG_DEFAULT_LOCALE)
   {
      // Set bmi captions
     lbl_hwbmi->Caption = RoundIntToStr(report_pwa->Height) + "cm";
   }
   else if (report_pwa->Weight > 0 && report_pwa->Weight != DEFAULT_VALUE &&
         config_get_system_locale() == CONFIG_DEFAULT_LOCALE)
   {
      // Set bmi captions
     lbl_hwbmi->Caption = RoundIntToStr(report_pwa->Weight) + "kg";
   }
   else if (report_pwa->Feet >= 0 && report_pwa->Feet != DEFAULT_VALUE &&
            report_pwa->Inch >= 0 && report_pwa->Inch != DEFAULT_VALUE &&
            report_pwa->Pound > 0 && report_pwa->Pound != DEFAULT_VALUE &&
            report_pwa->Bmi > 0 && report_pwa->Bmi != DEFAULT_VALUE &&
            config_get_system_locale() == CONFIG_IMPERIAL_LOCALE)
   {
      // Set bmi captions
     lbl_hwbmi->Caption = RoundIntToStr(report_pwa->Feet) + "ft, " +
                                        RoundIntToStr(report_pwa->Inch) + "in, " +
                                        RoundIntToStr(report_pwa->Pound) + "lb (" +
                                        FormatFloat("0.##", report_pwa->Bmi) + " kg/m²)";

   }
   else if (report_pwa->Feet >= 0 && report_pwa->Feet != DEFAULT_VALUE &&
            report_pwa->Inch >= 0 && report_pwa->Inch != DEFAULT_VALUE &&
            config_get_system_locale() == CONFIG_IMPERIAL_LOCALE)
   {
      // Set bmi captions
     lbl_hwbmi->Caption = RoundIntToStr(report_pwa->Feet) + "ft, " +
                                        RoundIntToStr(report_pwa->Inch) + "in";
   }
   else if (report_pwa->Pound > 0 && report_pwa->Pound != DEFAULT_VALUE &&
            config_get_system_locale() == CONFIG_IMPERIAL_LOCALE)
   {
      // Set bmi captions
     lbl_hwbmi->Caption = RoundIntToStr(report_pwa->Pound) + "lb";
   }
   else
   {
     lbl_hwbmi->Caption = "";
   }

   // PM V9
   // The Simulation label is displayed on the status bar
   if (report_pwa->Simulation)
   {
      emma_display_statusbar_message(SIMULATION, SIMULATION_NOTE, sphygmocor_maroon);
   }
   else
   {
      emma_display_statusbar_message("", "", sphygmocor_white);
   }

   // Only display the tonometer labels if it does not have the default value
   if (report_pwa->Tonometer == CONFIG_DEFAULT_TONOMETER)
   {
      lbl_tonometer_title->Visible = false;
      lbl_tonometer->Visible = false;
   }
   else
   {
      lbl_tonometer_title->Visible = true;
      lbl_tonometer->Visible = true;
      lbl_tonometer->Caption = IntToStr(report_pwa->Tonometer);
   }
   lbl_avi_tonometer_title->Visible = lbl_tonometer_title->Visible;
   lbl_avi_tonometer->Visible = lbl_tonometer->Visible;
   lbl_avi_tonometer->Caption = lbl_tonometer->Caption;
}
//---------------------------------------------------------------------------
void Tfrm_report_pwa::report_display_signal(void)
{
   int        i;
   float      qc_val;

   frm_report_pwa->chrt_pulse_periph->UndoZoom();
   frm_report_pwa->chrt_pulse_central->UndoZoom();
   frm_report_pwa->srs_pulse_periph->Title = "Peripheral";
   frm_report_pwa->srs_pulse_periph->Clear();
   frm_report_pwa->srs_pulse_central->Clear();
   frm_report_pwa->srs_trigs_periph->Clear();
   frm_report_pwa->srs_trigs_central->Clear();
   frm_report_pwa->srs_pulse_central->Title = "Aortic";

   frm_report_pwa->chrt_pulse_overlay->UndoZoom();
   for (i = 0; i < frm_report_pwa->chrt_pulse_overlay->SeriesCount(); i++)
   {
      frm_report_pwa->chrt_pulse_overlay->Series[i]->Clear();
   }

   qc_val = math_Round(frm_report_pwa->report_pwa->Periph.QC_PulseHeight);
   frm_report_pwa->lbl_qc1->Font->Color = sphygmocor_green;
   frm_report_pwa->lbl_clinical_qc_ph->Font->Color = sphygmocor_green;
   if (qc_val < config_get_qc_pulse_height())
   {
      frm_report_pwa->lbl_qc1->Font->Color = sphygmocor_red;
      frm_report_pwa->lbl_clinical_qc_ph->Font->Color = sphygmocor_red;
   }
   /*
   ** If this report was generated from a pulse wave monitoring report then
   ** the value for Average Pulse Height cannot be used for quality control purposes
   ** as the values are in mmHg for a calibrated report.   08/05/2002
   */
   if (study_mode == MEAS_PWM_ID)
   {
      frm_report_pwa->lbl_qc1->Font->Color = sphygmocor_white;
      frm_report_pwa->lbl_clinical_qc_ph->Font->Color = sphygmocor_white;
   }
   frm_report_pwa->lbl_qc1->Caption = RoundIntToStr(qc_val);
   frm_report_pwa->lbl_clinical_qc_ph->Caption = frm_report_pwa->lbl_qc1->Caption;

   qc_val = math_Round(frm_report_pwa->report_pwa->Periph.QC_PulseHeightVariation);
   frm_report_pwa->lbl_qc2->Font->Color = sphygmocor_green;
   frm_report_pwa->lbl_clinical_qc_phv->Font->Color = sphygmocor_green;
   if (qc_val > config_get_qc_pulse_height_variation())
   {
      frm_report_pwa->lbl_qc2->Font->Color = sphygmocor_red;
      frm_report_pwa->lbl_clinical_qc_phv->Font->Color = sphygmocor_red;
   }
   frm_report_pwa->lbl_qc2->Caption = RoundIntToStr(qc_val);
   frm_report_pwa->lbl_clinical_qc_phv->Caption = frm_report_pwa->lbl_qc2->Caption +" %";

   frm_report_pwa->lbl_qc3->Caption = RoundIntToStr(frm_report_pwa->report_pwa->Periph.QC_PulseLengthVariation);

   qc_val = math_Round(frm_report_pwa->report_pwa->Periph.QC_DiastolicVariation);
   frm_report_pwa->lbl_qc4->Font->Color = sphygmocor_green;
   frm_report_pwa->lbl_clinical_qc_dv->Font->Color = sphygmocor_green;
   if (qc_val > config_get_qc_diastolic_variation())
   {
      frm_report_pwa->lbl_qc4->Font->Color = sphygmocor_red;
      frm_report_pwa->lbl_clinical_qc_dv->Font->Color = sphygmocor_red;
   }
   frm_report_pwa->lbl_qc4->Caption = RoundIntToStr(qc_val);
   frm_report_pwa->lbl_clinical_qc_dv->Caption = frm_report_pwa->lbl_qc4->Caption +" %";

   // PM V9
   // Max dP/dt is always displayed in white
   qc_val = math_Round(frm_report_pwa->report_pwa->Periph.MaxdPdt);
   frm_report_pwa->lbl_qc5_dpdt->Caption = RoundIntToStr(qc_val);

   qc_val = math_Round(frm_report_pwa->report_pwa->Periph.QC_ShapeDeviation);
   frm_report_pwa->lbl_qc6->Font->Color = sphygmocor_green;
   frm_report_pwa->lbl_clinical_qc_sd->Font->Color = sphygmocor_green;
   if (qc_val == REPORT_ACCEPTABLE_SHAPE_DEVIATION)
   {
      frm_report_pwa->lbl_qc6->Font->Color = sphygmocor_white;
      frm_report_pwa->lbl_clinical_qc_sd->Font->Color = sphygmocor_white;
   }
   else if (qc_val > REPORT_ACCEPTABLE_SHAPE_DEVIATION)
   {
      frm_report_pwa->lbl_qc6->Font->Color = sphygmocor_red;
      frm_report_pwa->lbl_clinical_qc_sd->Font->Color = sphygmocor_red;
   }
   if (qc_val == 0)
   {
      frm_report_pwa->lbl_qc6->Caption = "n/c ";
      frm_report_pwa->lbl_qc6->Font->Color = sphygmocor_white;
      frm_report_pwa->lbl_clinical_qc_sd->Caption = "n/c ";
      frm_report_pwa->lbl_clinical_qc_sd->Font->Color = sphygmocor_white;
   }
   else
   {
      frm_report_pwa->lbl_qc6->Caption = RoundIntToStr(math_Round(qc_val));
      frm_report_pwa->lbl_clinical_qc_sd->Caption = frm_report_pwa->lbl_qc6->Caption +" %";
   }

   // Shift radial signal 16 points to get correspondence with convoluted Central signal
   int UpDownGap = 8;
   int lShift = (frm_report_pwa->report_pwa->MeasureType == PWA_AORTIC ?
                   0 : (int)((NOF_TF_COEFF - 1) / 2));
   for (i = lShift; i < (frm_report_pwa->report_pwa->Periph.NofPoints); i++)
   {
      frm_report_pwa->srs_pulse_periph->AddXY(i - lShift,
                                              frm_report_pwa->report_pwa->Periph.Signal[i],
                                              "", clTeeColor);
   }
   frm_report_pwa->chrt_pulse_periph->LeftAxis->SetMinMax(frm_report_pwa->srs_pulse_periph->MinYValue() - UpDownGap,
                                                          frm_report_pwa->srs_pulse_periph->MaxYValue() + UpDownGap);

   for (i = 0; i < (frm_report_pwa->report_pwa->Central.NofPoints); i++)
   {
      frm_report_pwa->srs_pulse_central->AddXY(i,
                                               frm_report_pwa->report_pwa->Central.Signal[i],
                                               "", clTeeColor);
   }
   frm_report_pwa->chrt_pulse_central->LeftAxis->SetMinMax(frm_report_pwa->srs_pulse_central->MinYValue() - UpDownGap,
                                                           frm_report_pwa->srs_pulse_central->MaxYValue() + UpDownGap);


   for (int k = 0; k < frm_report_pwa->report_pwa->Periph.NofPulses; k++)
   {
      float pY = frm_report_pwa->report_pwa->Periph.Signal[abs(frm_report_pwa->report_pwa->Periph.Pulses[k].Index)];
      frm_report_pwa->srs_trigs_periph->AddXY(frm_report_pwa->report_pwa->Periph.Pulses[k].Index - lShift,
                                              pY,"", sphygmocor_green);
   }
   for (int k = 0; k < frm_report_pwa->report_pwa->Central.NofPulses; k++)
   {
      float cY = frm_report_pwa->report_pwa->Central.Signal[abs(frm_report_pwa->report_pwa->Central.Pulses[k].Index)];
      frm_report_pwa->srs_trigs_central->AddXY(frm_report_pwa->report_pwa->Central.Pulses[k].Index, cY,
                                               "", sphygmocor_green);
   }

   for (i = 0; i < frm_report_pwa->report_pwa->Periph.NofPulses; i++)
   {
      if (i < REPORT_MAX_OVERLAY_PULSES)
      {
         meas_GetSeriesForPulse(i, frm_report_pwa->report_pwa->Periph.Pulses,
                                (TLineSeries *)frm_report_pwa->chrt_pulse_overlay->Series[i],
                                sphygmocor_grey);
      }
   }
}

//---------------------------------------------------------------------------

void Tfrm_report_pwa::report_display_ed(void)
{
   double min_periph;
   double min_central;
   double min_incident;
   double min_reflected;
   
   min_periph = srs_avg_periph->MinYValue();
   min_central = srs_avg_central->MinYValue();
   min_incident = srs_avi_forward->MinYValue();
   min_reflected = srs_avi_reflected->MinYValue();

   if (min_central < min_periph)
   {
      min_periph = min_central;
   }
   if (min_reflected < min_incident)
   {
      min_incident = min_reflected;
   }
   min_periph = min_periph * 0.98;
   min_central = min_central * 0.98;
   min_incident = min_incident * 0.98;

   srs_avg_ped->Clear();
   srs_avg_ped->Pointer->InflateMargins = true;

   srs_avg_ced->Clear();
   srs_avg_ced->Pointer->InflateMargins = true;

   srs_avg_clinical_ed->Clear();
   srs_avg_clinical_ed->Pointer->InflateMargins = true;

   srs_avi_avg_ed->Clear();
   srs_avi_avg_ed->Pointer->InflateMargins = true;

   srs_avi_reflected_ed->Clear();
   srs_avi_reflected_ed->Pointer->InflateMargins = true;

   srs_avi_flow_ed->Clear();
   srs_avi_flow_ed->Pointer->InflateMargins = true;

   if (report_pwa->Periph.ED != DEFAULT_VALUE)
   {
      if (fabs(report_pwa->Periph.ED - report_pwa->Periph.CalcED) < 0.5)
      {
         srs_avg_ped->Pointer->Style = psDiamond;
         srs_avg_ped->Pointer->Pen->Color = sphygmocor_black;
         srs_avg_ped->Pointer->HorizSize = 3;
         srs_avg_ped->Pointer->VertSize = 3;
         srs_avg_ped->LinePen->Style = psSolid;
         srs_avg_ped->Pointer->Brush->Color = sphygmocor_grey;
         srs_avg_ped->AddXY(report_pwa->Periph.ED,
                            min_periph, "", sphygmocor_grey);

         srs_avg_ped->AddXY(report_pwa->Periph.ED,
                            report_pwa->Periph.ESP,
                            "", sphygmocor_grey);

         srs_avg_ced->Pointer->Style = psDiamond;
         srs_avg_ced->Pointer->Pen->Color = sphygmocor_black;
         srs_avg_ced->Pointer->HorizSize = 3;
         srs_avg_ced->Pointer->VertSize = 3;
         srs_avg_ced->LinePen->Style = psSolid;
         srs_avg_ced->Pointer->Brush->Color = sphygmocor_grey;
         srs_avg_ced->AddXY(report_pwa->Periph.ED,
                            min_periph, "", sphygmocor_grey);

         srs_avg_ced->AddXY(report_pwa->Periph.ED,
                            report_pwa->Central.ESP,
                            "", sphygmocor_grey);

         srs_avg_clinical_ed->Pointer->Style = psDiamond;
         srs_avg_clinical_ed->Pointer->Pen->Color = sphygmocor_black;
         srs_avg_clinical_ed->Pointer->HorizSize = 3;
         srs_avg_clinical_ed->Pointer->VertSize = 3;
         srs_avg_clinical_ed->LinePen->Style = psSolid;
         srs_avg_clinical_ed->Pointer->Brush->Color = sphygmocor_grey;
         srs_avg_clinical_ed->AddXY(report_pwa->Periph.ED,
                                  min_central, "", sphygmocor_grey);

         srs_avg_clinical_ed->AddXY(report_pwa->Periph.ED,
                                  report_pwa->Central.ESP,
                                  "", sphygmocor_grey);
      }
      else
      {
         srs_avg_ped->Pointer->Style = psCircle;
         srs_avg_ped->Pointer->Pen->Color = sphygmocor_pink;
         srs_avg_ped->LinePen->Style = psDot;
         srs_avg_ped->Pointer->HorizSize = 2;
         srs_avg_ped->Pointer->VertSize = 2;
         srs_avg_ped->Pointer->Brush->Color = sphygmocor_pink;
         srs_avg_ped->AddXY(report_pwa->Periph.ED,
                            min_periph, "", sphygmocor_pink);
         srs_avg_ped->AddXY(report_pwa->Periph.ED,
                            report_pwa->Periph.ESP,
                            "", sphygmocor_pink);

         srs_avg_ced->Pointer->Style = psCircle;
         srs_avg_ced->Pointer->Pen->Color = sphygmocor_pink;
         srs_avg_ced->LinePen->Style = psDot;
         srs_avg_ced->Pointer->HorizSize = 2;
         srs_avg_ced->Pointer->VertSize = 2;
         srs_avg_ced->Pointer->Brush->Color = sphygmocor_pink;
         srs_avg_ced->AddXY(report_pwa->Periph.ED,
                            min_periph, "", sphygmocor_pink);
         srs_avg_ced->AddXY(report_pwa->Periph.ED,
                            report_pwa->Central.ESP,
                            "", sphygmocor_pink);

         srs_avg_clinical_ed->Pointer->Style = psCircle;
         srs_avg_clinical_ed->Pointer->Pen->Color = sphygmocor_pink;
         srs_avg_clinical_ed->LinePen->Style = psDot;
         srs_avg_clinical_ed->Pointer->HorizSize = 2;
         srs_avg_clinical_ed->Pointer->VertSize = 2;
         srs_avg_clinical_ed->Pointer->Brush->Color = sphygmocor_pink;
         srs_avg_clinical_ed->AddXY(report_pwa->Periph.ED,
                            min_central, "", sphygmocor_pink);
         srs_avg_clinical_ed->AddXY(report_pwa->Periph.ED,
                            report_pwa->Central.ESP,
                            "", sphygmocor_pink);
      }
   }
}

void Tfrm_report_pwa::report_display_t1(void)
{
   double min_periph;
   double min_central;
   double max_time;
   double min_time;

   min_periph = srs_avg_periph->MinYValue();
   min_central = srs_avg_central->MinYValue();
   max_time = REPORT_MAX_TIME;
   min_time = REPORT_MIN_TIME;

   if (min_central < min_periph)
   {
      min_periph = min_central;
   }
   min_periph = min_periph * 0.98;
   min_central = min_central * 0.98;

   srs_avg_t1->Clear();
   srs_avg_t1->Pointer->InflateMargins = true;

   srs_avg_t1_timing->Clear();
   srs_avg_t1_timing->Pointer->InflateMargins = true;

   srs_avg_clinical_t1->Clear();
   srs_avg_clinical_t1->Pointer->Visible = true;
   srs_avg_clinical_t1->Pointer->InflateMargins = true;
   srs_avg_clinical_t1->Marks->Visible = false;

   srs_avi_avg_t1->Clear();
   srs_avi_avg_t1->Pointer->Visible = true;
   srs_avi_avg_t1->Pointer->InflateMargins = true;
   srs_avi_avg_t1->Marks->Visible = false;

   if (report_pwa->Central.T1 != DEFAULT_VALUE)
   {
      if (fabs(report_pwa->Central.T1 - report_pwa->Central.CalcT1) < 0.5)
      {
         srs_avg_t1->AddXY(report_pwa->Central.T1,
                              min_periph,
                              "", sphygmocor_grey);
         srs_avg_t1->AddXY(report_pwa->Central.T1,
                              report_pwa->Central.P1,
                              "", sphygmocor_grey);
         srs_avg_t1->AddXY(max_time,
                              report_pwa->Central.P1,
                              "", sphygmocor_grey);

         srs_avg_t1_timing->Pointer->Style = psDiamond;
         srs_avg_t1_timing->Pointer->Pen->Color = sphygmocor_black;
         srs_avg_t1_timing->Pointer->HorizSize = 3;
         srs_avg_t1_timing->Pointer->VertSize = 3;
         srs_avg_t1_timing->Pointer->Brush->Color = sphygmocor_grey;
         srs_avg_t1_timing->AddXY(report_pwa->Central.T1,
                              min_periph,
                              "", sphygmocor_grey);
         srs_avg_t1_timing->AddXY(max_time,
                              report_pwa->Central.P1,
                              "", sphygmocor_grey);

         srs_avg_clinical_t1->Pointer->Style = psDiamond;
         srs_avg_clinical_t1->Pointer->Pen->Color = sphygmocor_black;
         srs_avg_clinical_t1->Pointer->HorizSize = 3;
         srs_avg_clinical_t1->Pointer->VertSize = 3;
         srs_avg_clinical_t1->Pointer->Brush->Color = sphygmocor_grey;
         srs_avg_clinical_t1->AddXY(report_pwa->Central.T1,
                                       min_central,
                                       "", sphygmocor_grey);
         srs_avg_clinical_t1->AddXY(min_time,
                                       report_pwa->Central.P1,
                                       "", sphygmocor_grey);

         srs_avi_avg_t1->Pointer->Style = psDiamond;
         srs_avi_avg_t1->Pointer->Pen->Color = sphygmocor_black;
         srs_avi_avg_t1->Pointer->HorizSize = 3;
         srs_avi_avg_t1->Pointer->VertSize = 3;
         srs_avi_avg_t1->Pointer->Brush->Color = sphygmocor_grey;
         srs_avi_avg_t1->AddXY(report_pwa->Central.T1,
                                 min_central,
                                 "", sphygmocor_grey);
         srs_avi_avg_t1->AddXY(min_time,
                                 report_pwa->Central.P1,
                                 "", sphygmocor_grey);
      }
      else
      {
         srs_avg_t1->AddXY(report_pwa->Central.T1,
                              min_periph,
                              "", sphygmocor_pink);
         srs_avg_t1->AddXY(report_pwa->Central.T1,
                              report_pwa->Central.P1,
                              "", sphygmocor_pink);
         srs_avg_t1->AddXY(max_time,
                              report_pwa->Central.P1,
                              "", sphygmocor_pink);

         srs_avg_t1_timing->Pointer->Style = psCircle;
         srs_avg_t1_timing->Pointer->Pen->Color = sphygmocor_pink;
         srs_avg_t1_timing->Pointer->HorizSize = 2;
         srs_avg_t1_timing->Pointer->VertSize = 2;
         srs_avg_t1_timing->Pointer->Brush->Color = sphygmocor_pink;
         srs_avg_t1_timing->AddXY(report_pwa->Central.T1,
                              min_periph,
                              "", sphygmocor_pink);
         srs_avg_t1_timing->AddXY(max_time,
                              report_pwa->Central.P1,
                              "", sphygmocor_pink);

         srs_avg_clinical_t1->Pointer->Style = psCircle;
         srs_avg_clinical_t1->Pointer->Pen->Color = sphygmocor_pink;
         srs_avg_clinical_t1->Pointer->HorizSize = 2;
         srs_avg_clinical_t1->Pointer->VertSize = 2;
         srs_avg_clinical_t1->Pointer->Brush->Color = sphygmocor_pink;
         srs_avg_clinical_t1->AddXY(report_pwa->Central.T1,
                                       min_central,
                                       "", sphygmocor_pink);
         srs_avg_clinical_t1->AddXY(min_time,
                                       report_pwa->Central.P1,
                                       "", sphygmocor_pink);

         srs_avi_avg_t1->Pointer->Style = psCircle;
         srs_avi_avg_t1->Pointer->Pen->Color = sphygmocor_pink;
         srs_avi_avg_t1->Pointer->HorizSize = 2;
         srs_avi_avg_t1->Pointer->VertSize = 2;
         srs_avi_avg_t1->Pointer->Brush->Color = sphygmocor_pink;
         srs_avi_avg_t1->AddXY(report_pwa->Central.T1,
                                 min_central,
                                 "", sphygmocor_pink);
         srs_avi_avg_t1->AddXY(min_time,
                                 report_pwa->Central.P1,
                                 "", sphygmocor_pink);
      }
   }
}

void Tfrm_report_pwa::report_display_t2(void)
{
   double min_periph;
   double min_central;
   double max_time;
   double min_time;

   min_periph = srs_avg_periph->MinYValue();
   min_central = srs_avg_central->MinYValue();
   max_time = REPORT_MAX_TIME;
   min_time = REPORT_MIN_TIME;

   if (min_central < min_periph)
   {
      min_periph = min_central;
   }
   min_periph = min_periph * 0.98;
   min_central = min_central * 0.98;

   srs_avg_t2->Clear();
   srs_avg_t2->Pointer->InflateMargins = true;

   srs_avg_t2_timing->Clear();
   srs_avg_t2_timing->Pointer->InflateMargins = true;

   srs_avg_clinical_t2->Clear();
   srs_avg_clinical_t2->Pointer->Visible = true;
   srs_avg_clinical_t2->Pointer->InflateMargins = true;
   srs_avg_clinical_t2->Marks->Visible = false;

   srs_avi_avg_t2->Clear();
   srs_avi_avg_t2->Pointer->Visible = true;
   srs_avi_avg_t2->Pointer->InflateMargins = true;
   srs_avi_avg_t2->Marks->Visible = false;
   
   if (report_pwa->Central.T2 != DEFAULT_VALUE)
   {
      if (fabs(report_pwa->Central.T2 - report_pwa->Central.CalcT2) < 0.5)
      {
         srs_avg_t2->AddXY(report_pwa->Central.T2,
                              min_periph,
                              "", sphygmocor_grey);
         srs_avg_t2->AddXY(report_pwa->Central.T2,
                              report_pwa->Central.P2,
                              "", sphygmocor_grey);
         srs_avg_t2->AddXY(max_time,
                              report_pwa->Central.P2,
                              "", sphygmocor_grey);

         srs_avg_t2_timing->Pointer->Style = psDiamond;
         srs_avg_t2_timing->Pointer->Pen->Color = sphygmocor_black;
         srs_avg_t2_timing->Pointer->HorizSize = 3;
         srs_avg_t2_timing->Pointer->VertSize = 3;
         srs_avg_t2_timing->Pointer->Brush->Color = sphygmocor_grey;
         srs_avg_t2_timing->AddXY(report_pwa->Central.T2,
                              min_periph,
                              "", sphygmocor_grey);
         srs_avg_t2_timing->AddXY(max_time,
                              report_pwa->Central.P2,
                              "", sphygmocor_grey);

         srs_avg_clinical_t2->Pointer->Style = psDiamond;
         srs_avg_clinical_t2->Pointer->Pen->Color = sphygmocor_black;
         srs_avg_clinical_t2->Pointer->HorizSize = 3;
         srs_avg_clinical_t2->Pointer->VertSize = 3;
         srs_avg_clinical_t2->Pointer->Brush->Color = sphygmocor_grey;
         srs_avg_clinical_t2->AddXY(report_pwa->Central.T2,
                                       min_central,
                                       "", sphygmocor_grey);
         srs_avg_clinical_t2->AddXY(min_time,
                                       report_pwa->Central.P2,
                                       "", sphygmocor_grey);

         srs_avi_avg_t2->Pointer->Style = psDiamond;
         srs_avi_avg_t2->Pointer->Pen->Color = sphygmocor_black;
         srs_avi_avg_t2->Pointer->HorizSize = 3;
         srs_avi_avg_t2->Pointer->VertSize = 3;
         srs_avi_avg_t2->Pointer->Brush->Color = sphygmocor_grey;
         srs_avi_avg_t2->AddXY(report_pwa->Central.T2,
                                 min_central,
                                 "", sphygmocor_grey);
         srs_avi_avg_t2->AddXY(min_time,
                                 report_pwa->Central.P2,
                                 "", sphygmocor_grey);
      }
      else
      {
         srs_avg_t2->AddXY(report_pwa->Central.T2,
                              min_periph,
                              "", sphygmocor_pink);
         srs_avg_t2->AddXY(report_pwa->Central.T2,
                              report_pwa->Central.P2,
                              "", sphygmocor_pink);
         srs_avg_t2->AddXY(max_time,
                              report_pwa->Central.P2,
                              "", sphygmocor_pink);

         srs_avg_t2_timing->Pointer->Style = psCircle;
         srs_avg_t2_timing->Pointer->Pen->Color = sphygmocor_pink;
         srs_avg_t2_timing->Pointer->HorizSize = 2;
         srs_avg_t2_timing->Pointer->VertSize = 2;
         srs_avg_t2_timing->Pointer->Brush->Color = sphygmocor_pink;
         srs_avg_t2_timing->AddXY(report_pwa->Central.T2,
                              min_periph,
                              "", sphygmocor_pink);
         srs_avg_t2_timing->AddXY(max_time,
                              report_pwa->Central.P2,
                              "", sphygmocor_pink);

         srs_avg_clinical_t2->Pointer->Style = psCircle;
         srs_avg_clinical_t2->Pointer->Pen->Color = sphygmocor_pink;
         srs_avg_clinical_t2->Pointer->HorizSize = 2;
         srs_avg_clinical_t2->Pointer->VertSize = 2;
         srs_avg_clinical_t2->Pointer->Brush->Color = sphygmocor_pink;
         srs_avg_clinical_t2->AddXY(report_pwa->Central.T2,
                                       min_central,
                                       "", sphygmocor_pink);
         srs_avg_clinical_t2->AddXY(min_time,
                                       report_pwa->Central.P2,
                                       "", sphygmocor_pink);

         srs_avi_avg_t2->Pointer->Style = psCircle;
         srs_avi_avg_t2->Pointer->Pen->Color = sphygmocor_pink;
         srs_avi_avg_t2->Pointer->HorizSize = 2;
         srs_avi_avg_t2->Pointer->VertSize = 2;
         srs_avi_avg_t2->Pointer->Brush->Color = sphygmocor_pink;
         srs_avi_avg_t2->AddXY(report_pwa->Central.T2,
                                 min_central,
                                 "", sphygmocor_pink);
         srs_avi_avg_t2->AddXY(min_time,
                                 report_pwa->Central.P2,
                                 "", sphygmocor_pink);
      }
   }
}
// PM V9
void Tfrm_report_pwa::report_display_ap(void)
{
   CLINICAL_NORMALS_RANGE  range;
   double                  min_time;
   TColor                  ap_color;
   TColor                  p1_color;
   TColor                  p2_color;

   min_time = REPORT_MIN_TIME;

   srs_avg_clinical_ap->Clear();
   srs_avg_clinical_p1->Clear();
   srs_avg_clinical_p2->Clear();

   if (report_pwa->Central.AP != DEFAULT_VALUE)
   {
      srs_avg_clinical_p1->Visible = true;
      srs_avg_clinical_p2->Visible = true;
      srs_avg_clinical_ap->Visible = true;
      range = report_determine_ap_range(report_pwa->Central.AP, report_age, report_pwa->MeasureType);
      // Determine which colour to display the AP lines, if undefined - don't display them
      switch (range)
      {
         case RANGE_LOW:
         case RANGE_NORMAL_LOW:
         case RANGE_NORMAL_HIGH:
            ap_color = sphygmocor_green;
            p1_color = sphygmocor_green;
            p2_color = sphygmocor_green;
            break;

         case RANGE_HIGH:
            ap_color = sphygmocor_red;
            p1_color = sphygmocor_red;
            p2_color = sphygmocor_red;
            break;

         case RANGE_UNDEFINED:
            srs_avg_clinical_p1->Visible = false;
            srs_avg_clinical_p2->Visible = false;
            srs_avg_clinical_ap->Visible = false;
            ap_color = chrt_avg_central_periph->BackWall->Color;
            p1_color = chrt_avg_central_periph->BackWall->Color;
            p2_color = chrt_avg_central_periph->BackWall->Color;
            break;
      }
      // If altered by the user, the pressure line will be pink
      if (fabs(report_pwa->Central.T1 - report_pwa->Central.CalcT1) >= 0.5)
      {
         p1_color = sphygmocor_pink;
      }
      if (fabs(report_pwa->Central.T2 - report_pwa->Central.CalcT2) >= 0.5)
      {
         p2_color = sphygmocor_pink;
      }
      // Draw pressure lines P1 and P2 and an AP line between them
      srs_avg_clinical_p1->AddXY(min_time,
                                 report_pwa->Central.P1,
                                 "", p1_color);
      srs_avg_clinical_p1->AddXY(report_pwa->Central.T1,
                                 report_pwa->Central.P1,
                                 "", p1_color);
      srs_avg_clinical_p2->AddXY(min_time,
                                 report_pwa->Central.P2,
                                 "", p2_color);
      srs_avg_clinical_p2->AddXY(report_pwa->Central.T2,
                                 report_pwa->Central.P2,
                                 "", p2_color);
      int x = report_pwa->Central.T1/2;
      srs_avg_clinical_ap->AddXY(x,
                                 report_pwa->Central.P1,
                                 "", ap_color);
      srs_avg_clinical_ap->AddXY(x,
                                 report_pwa->Central.P2,
                                 "", ap_color);
   }
}
//---------------------------------------------------------------------------
void Tfrm_report_pwa::report_display_average_pulse(void)
{
   int                     i;
   int                     timing_param;
   int                     pp_central;
   double                  max_central;
   double                  max_periph;
   double                  min_central;
   double                  min_periph;
   double                  max_time;
   double                  min_time;
   CLINICAL_NORMALS_RANGE  range;
   AnsiString              S;

   frm_report_pwa->chrt_avg_periph->UndoZoom();
   frm_report_pwa->srs_avg_periph->Clear();
   frm_report_pwa->srs_avg_ptiming->Clear();
   frm_report_pwa->srs_avg_ptiming->Pointer->Visible = true;
   frm_report_pwa->srs_avg_ptiming->Pointer->InflateMargins = true;
   frm_report_pwa->srs_avg_ptiming->Marks->Visible = false;


   frm_report_pwa->chrt_avg_central->UndoZoom();
   frm_report_pwa->srs_avg_central->Clear();

   frm_report_pwa->srs_avg_t1_timing->Clear();
   frm_report_pwa->srs_avg_t1_timing->Pointer->Visible = true;
   frm_report_pwa->srs_avg_t1_timing->Pointer->InflateMargins = true;
   frm_report_pwa->srs_avg_t1_timing->Marks->Visible = false;

   frm_report_pwa->srs_avg_t2_timing->Clear();
   frm_report_pwa->srs_avg_t2_timing->Pointer->Visible = true;
   frm_report_pwa->srs_avg_t2_timing->Pointer->InflateMargins = true;
   frm_report_pwa->srs_avg_t2_timing->Marks->Visible = false;

   frm_report_pwa->chrt_avg_central_periph->UndoZoom();
   frm_report_pwa->srs_avg_clinical_central->Clear();

   frm_report_pwa->srs_avg_t1->Clear();
   frm_report_pwa->srs_avg_t1->Visible = false;
   frm_report_pwa->srs_avg_t2->Clear();
   frm_report_pwa->srs_avg_t2->Visible = false;
   t1_line = false;
   t2_line = false;

   frm_report_pwa->lbl_psp->Caption = RoundIntToStr(frm_report_pwa->report_pwa->Periph.Sp);
   frm_report_pwa->lbl_clinical_psp->Caption = frm_report_pwa->lbl_psp->Caption;

   frm_report_pwa->lbl_pdp->Caption = RoundIntToStr(frm_report_pwa->report_pwa->Periph.Dp);
   frm_report_pwa->lbl_clinical_pdp->Caption = frm_report_pwa->lbl_pdp->Caption;

   if (frm_report_pwa->report_pwa->Periph.MeanP < DEFAULT_VALUE)
   {
      frm_report_pwa->lbl_pmp->Caption = RoundIntToStr(frm_report_pwa->report_pwa->Periph.MeanP);
   }
   else
   {
      frm_report_pwa->lbl_pmp->Caption = "n/c";
   }
   frm_report_pwa->lbl_clinical_pmp->Caption = frm_report_pwa->lbl_pmp->Caption;

   frm_report_pwa->lbl_ppp->Caption = IntToStr(frm_report_pwa->lbl_psp->Caption.ToInt() -
                                               frm_report_pwa->lbl_pdp->Caption.ToInt());
   frm_report_pwa->lbl_clinical_ppp->Caption = frm_report_pwa->lbl_ppp->Caption;

   frm_report_pwa->lbl_csp->Caption = RoundIntToStr(frm_report_pwa->report_pwa->Central.Sp);
   frm_report_pwa->lbl_clinical_csp->Caption = frm_report_pwa->lbl_csp->Caption;

   frm_report_pwa->lbl_cdp->Caption = RoundIntToStr(frm_report_pwa->report_pwa->Central.Dp);
   frm_report_pwa->lbl_clinical_cdp->Caption = frm_report_pwa->lbl_cdp->Caption;

   if (frm_report_pwa->report_pwa->Central.MeanP < DEFAULT_VALUE)
   {
      frm_report_pwa->lbl_cmp->Caption = RoundIntToStr(frm_report_pwa->report_pwa->Central.MeanP);
   }
   else
   {
      frm_report_pwa->lbl_cmp->Caption = "n/c";
   }
   frm_report_pwa->lbl_clinical_cmp->Caption = frm_report_pwa->lbl_cmp->Caption;

   // PM V9
   // Display Central Pulse Pressure in Red for values over 50mmHg,
   // on the clinical report only
   pp_central = frm_report_pwa->lbl_csp->Caption.ToInt() - frm_report_pwa->lbl_cdp->Caption.ToInt();
   frm_report_pwa->lbl_cpp->Caption = IntToStr(pp_central);
   frm_report_pwa->lbl_clinical_cpp->Caption = frm_report_pwa->lbl_cpp->Caption;

   if (pp_central >= 50)
   {
      frm_report_pwa->lbl_clinical_cpp->Font->Color = sphygmocor_red;
   }
   else
   {
      frm_report_pwa->lbl_clinical_cpp->Font->Color = sphygmocor_navy;
   }
   
   for (i = 0; i < frm_report_pwa->report_pwa->Periph.ExpPulse.Length(); i++)
   {
        float lt = frm_report_pwa->report_pwa->Periph.ExpPulse.IndexToTime(i);
        frm_report_pwa->srs_avg_periph->AddXY(lt,
                                        frm_report_pwa->report_pwa->Periph.ExpPulse.Profile[i],
                                        "", clTeeColor);
   }

   min_periph = frm_report_pwa->srs_avg_periph->MinYValue();
   max_periph = frm_report_pwa->srs_avg_periph->MaxYValue();


   for (i = 0; i < frm_report_pwa->report_pwa->Central.ExpPulse.Length(); i++)
   {
      float lt = frm_report_pwa->report_pwa->Central.ExpPulse.IndexToTime(i);
      frm_report_pwa->srs_avg_central->AddXY(lt,
                                             frm_report_pwa->report_pwa->Central.ExpPulse.Profile[i],
                                             "", clTeeColor);
      frm_report_pwa->srs_avg_clinical_central->AddXY(lt,
                                                   frm_report_pwa->report_pwa->Central.ExpPulse.Profile[i],
                                                    "", clTeeColor);
   }

   max_time = REPORT_MAX_TIME;
   min_time = REPORT_MIN_TIME;

   min_central = frm_report_pwa->srs_avg_central->MinYValue();
   max_central = frm_report_pwa->srs_avg_central->MaxYValue();

   if (min_central < min_periph)
   {
      min_periph = min_central;
   }
   if (max_central > max_periph)
   {
      max_periph = max_central;
   }
   min_periph = min_periph * 0.98;
   max_periph = max_periph * 1.04;
   min_central = min_central * 0.98;
   max_central = max_central * 1.04;

   report_display_ed();

   timing_param =  frm_report_pwa->report_pwa->Periph.T1;
   if (timing_param != DEFAULT_VALUE)
   {
      frm_report_pwa->srs_avg_ptiming->AddXY(frm_report_pwa->report_pwa->Periph.T1,
                                             min_periph,
                                             "", sphygmocor_green);
   }

   timing_param = frm_report_pwa->report_pwa->Periph.T2;
   if (timing_param != DEFAULT_VALUE)
   {
      frm_report_pwa->srs_avg_ptiming->AddXY(frm_report_pwa->report_pwa->Periph.T2,
                                             min_periph,
                                             "", sphygmocor_green);
   }

   report_display_t1();
   report_display_t2();
   report_display_ap();

   // periph holds the minimum and maximim values.
   frm_report_pwa->chrt_avg_central->RightAxis->SetMinMax(min_periph, max_periph);

   frm_report_pwa->chrt_avg_periph->LeftAxis->SetMinMax(min_periph, max_periph);
   frm_report_pwa->chrt_avg_central_periph->LeftAxis->SetMinMax(min_central, max_central);

   frm_report_pwa->chrt_avg_central->BottomAxis->SetMinMax(min_time, max_time);
   frm_report_pwa->chrt_avg_periph->BottomAxis->SetMinMax(min_time, max_time);
   frm_report_pwa->chrt_avg_central_periph->BottomAxis->SetMinMax(min_time, max_time);

   frm_report_pwa->chrt_avg_periph->LeftAxis->Increment = 10;
   frm_report_pwa->chrt_avg_periph->BottomAxis->Increment = 200;
   frm_report_pwa->chrt_avg_central->RightAxis->Increment = 10;
   frm_report_pwa->chrt_avg_central->BottomAxis->Increment = 200;
   frm_report_pwa->chrt_avg_central_periph->LeftAxis->Increment = 10;
   frm_report_pwa->chrt_avg_central_periph->BottomAxis->Increment = 200;

   if (frm_report_pwa->report_pwa->Central.P1 > frm_report_pwa->report_pwa->Central.P2)
   {
      srs_avg_t1_timing->Marks->ArrowLength = 5;
      srs_avg_t2_timing->Marks->ArrowLength = -18;
   }
   else
   {
      srs_avg_t1_timing->Marks->ArrowLength = -18;
      srs_avg_t2_timing->Marks->ArrowLength = 3;
   }

   report_display_clinical_normals();
   report_display_normals_ed();
   report_display_normals_sevr();
   report_display_normals_augidx();
   report_display_normals_aphr75();
   report_display_normals_sp();
   report_display_normals_pp();
   // PM CR
    /*
   ** If this report was generated from a pulse wave monitoring report then
   ** the value for Average Pulse Height and hence quality index
   ** cannot be used for quality control purposes as the values are
   ** in mmHg for a calibrated report.   08/05/2002
   */
   lbl_qcidx->Font->Color = sphygmocor_navy;
   lbl_clinical_operatoridx->Font->Color = lbl_qcidx->Font->Color;
   if (study_mode == MEAS_PWM_ID)
   {
      lbl_qcidx->Caption = "n/c";
      lbl_clinical_operatoridx->Caption = lbl_qcidx->Caption;
   }
   else
   {
      if (frm_report_pwa->report_pwa->Periph.OperatorIndex < PWA_MIN_OPERATOR_INDEX)
      {
         lbl_qcidx->Font->Color = sphygmocor_red;
         lbl_clinical_operatoridx->Font->Color = lbl_qcidx->Font->Color;
      }
      else
      {
         lbl_qcidx->Font->Color = sphygmocor_green;
         lbl_clinical_operatoridx->Font->Color = lbl_qcidx->Font->Color;
      }

      lbl_qcidx->Caption = IntToStr(frm_report_pwa->report_pwa->Periph.OperatorIndex);
      lbl_clinical_operatoridx->Caption = lbl_qcidx->Caption;
   }
}

void Tfrm_report_pwa::report_display_normals_ed(void)
{
   int         start_pt;
   int         end_pt;
   int         ed_low;
   int         ed_high;
   int         x, y;
   int         graph_height;
   float       position_ratio;
   int         indicator_left;
   float       displayed_ed;
   float       displayed_hr;
   AnsiString  S;

   if (frm_report_pwa->report_pwa->Central.HR != DEFAULT_VALUE)
   {
      start_pt = REPORT_MIN_DISPLAYED_HEART_RATE;
      end_pt = REPORT_MAX_DISPLAYED_HEART_RATE;

      srs_ed_normal_reference->Clear();
      srs_ed_lower_reference->Clear();
      srs_ed_upper_reference->Clear();

      frm_report_pwa->chrt_ed_reference->BottomAxis->SetMinMax(start_pt, end_pt);

      report_determine_ed_range(report_pwa->Central.EDPeriod, report_pwa->Central.HR, report_age, report_pwa->MeasureType);
      ed_low = ed_gradient * start_pt + ed_y_intercept - (2 * ed_confidence_90_offset);
      ed_high = ed_gradient * end_pt + ed_y_intercept + (2 * ed_confidence_90_offset);

      frm_report_pwa->chrt_ed_reference->LeftAxis->SetMinMax(ed_low, ed_high);

      x = start_pt;
      while (x <= end_pt)
      {
         srs_ed_normal_reference->AddXY(x,
                              ed_gradient * x + ed_y_intercept,
                              "", clTeeColor);
         srs_ed_lower_reference->AddXY(x,
                             ed_gradient * x + ed_y_intercept - ed_confidence_90_offset,
                             "", clTeeColor);
         srs_ed_upper_reference->AddXY(x,
                             ed_gradient * x + ed_y_intercept + ed_confidence_90_offset,
                             "", clTeeColor);
         x = x + 2;
      }
   }

   srs_ed_point_reference->Clear();
   if (report_pwa->Central.EDPeriod != DEFAULT_VALUE)
   {
      if (report_age >= PATIENT_YOUNG_AGE && frm_report_pwa->report_pwa->MeasureType == PWA_RADIAL)
      {
         displayed_ed = report_pwa->Central.EDPeriod;
         displayed_hr = frm_report_pwa->report_pwa->Central.HR;

         if (report_pwa->Central.EDPeriod > frm_report_pwa->chrt_ed_reference->LeftAxis->Maximum)
         {
            displayed_ed = frm_report_pwa->chrt_ed_reference->LeftAxis->Maximum;
         }
         else if (report_pwa->Central.EDPeriod < frm_report_pwa->chrt_ed_reference->LeftAxis->Minimum)
         {
            displayed_ed = frm_report_pwa->chrt_ed_reference->LeftAxis->Minimum;
         }
         if (frm_report_pwa->report_pwa->Central.HR >
            frm_report_pwa->chrt_ed_reference->BottomAxis->Maximum)
         {
            displayed_hr = frm_report_pwa->chrt_ed_reference->BottomAxis->Maximum;
         }
         else if (frm_report_pwa->report_pwa->Central.HR <
                  frm_report_pwa->chrt_ed_reference->BottomAxis->Minimum)
         {
            displayed_hr = frm_report_pwa->chrt_ed_reference->BottomAxis->Minimum;
         }
         displayed_ed = math_Round(displayed_ed);
         displayed_hr = math_Round(displayed_hr);

         srs_ed_point_reference->AddXY(displayed_hr, displayed_ed, "", clBlue);
      }
   }
}

void Tfrm_report_pwa::report_display_normals_sevr(void)
{
   AnsiString  S;
   int         start_pt;
   int         end_pt;
   int         x, y;
   int         graph_height;
   float       position_ratio;
   int         indicator_left;
   float       displayed_sevr;
   float       displayed_hr;

   srs_sevr_normal_reference->Clear();
   srs_sevr_lower_reference->Clear();
   srs_sevr_upper_reference->Clear();
   srs_sevr_flow->Clear();

   // Reference Range Graph
   if (frm_report_pwa->report_pwa->Central.HR != DEFAULT_VALUE)
   {
      start_pt = REPORT_MIN_DISPLAYED_HEART_RATE;
      end_pt = REPORT_MAX_DISPLAYED_HEART_RATE;

      frm_report_pwa->chrt_sevr_reference->BottomAxis->SetMinMax(start_pt, end_pt);

      report_determine_sevr_range(report_pwa->Central.SVI, report_pwa->Central.HR, report_age, report_pwa->MeasureType);
      x = ((sevr_coeff_1) * (end_pt * end_pt)) + (sevr_coeff_2 * end_pt) + sevr_y_intercept - (2 * sevr_confidence_90_offset);
      x = x / 10;
      x = (x + 1) * 10;
      y = ((sevr_coeff_1) * (start_pt * start_pt)) + (sevr_coeff_2 * start_pt) + sevr_y_intercept + (2 * sevr_confidence_90_offset);
      y = y / 10;
      y = (y + 1) * 10;
      frm_report_pwa->chrt_sevr_reference->LeftAxis->SetMinMax(x, y);
      x = start_pt;

      while (x <= end_pt)
      {
         srs_sevr_normal_reference->AddXY(x,
                                   ((sevr_coeff_1) * (x * x)) + (sevr_coeff_2 * x) + sevr_y_intercept,
                                   "", clTeeColor);
         srs_sevr_lower_reference->AddXY(x,
                                  ((sevr_coeff_1) * (x * x)) + (sevr_coeff_2 * x) + sevr_y_intercept - sevr_confidence_90_offset,
                                  "", clTeeColor);
         srs_sevr_upper_reference->AddXY(x,
                                  ((sevr_coeff_1) * (x * x)) + (sevr_coeff_2 * x) + sevr_y_intercept + sevr_confidence_90_offset,
                                  "", clTeeColor);
         x = x + 2;
      }

      // Flow Graph
      start_pt = 60;
      end_pt = report_sevr_cutoff_normal + report_sevr_cutoff_high - report_sevr_cutoff_low;
      end_pt = math_Round_nearest_20(end_pt);
      frm_report_pwa->chrt_sevr_flow_reference->BottomAxis->SetMinMax(start_pt, end_pt);
      frm_report_pwa->chrt_sevr_flow_reference->LeftAxis->SetMinMax(60, 120);
      x = start_pt;

      while (x <= end_pt)
      {
         if (x <= 100)
         {
            srs_sevr_flow->AddXY(x,
                                   x,
                                   "", sphygmocor_red);
         }
         else
         {
            // PM CR
            if (x > 100 && x <= REPORT_SEVR_ABNORMAL)
            {
               srs_sevr_flow->AddXY(x,
                                      100,
                                      "", sphygmocor_red);
            }
            else if (x > 100 && x <= report_sevr_cutoff_low)
            {
               srs_sevr_flow->AddXY(x,
                                      100,
                                      "", sphygmocor_red);
            }
            else if (x > report_sevr_cutoff_low && x <= report_sevr_cutoff_normal)
            {
               srs_sevr_flow->AddXY(x,
                                      100,
                                      "", sphygmocor_yellow);
            }
            else
            {
               srs_sevr_flow->AddXY(x,
                                      100,
                                      "", sphygmocor_green);
            }
         }
         x = x + 1;
      }
   }

   srs_sevr_point_reference->Clear();
   srs_sevr_flow_point->Clear();
   if (frm_report_pwa->report_pwa->Central.SVI != DEFAULT_VALUE)
   {
      if (report_age >= PATIENT_YOUNG_AGE && frm_report_pwa->report_pwa->MeasureType == PWA_RADIAL)
      {
         // Reference Range Graph
         displayed_sevr = frm_report_pwa->report_pwa->Central.SVI;
         displayed_hr = frm_report_pwa->report_pwa->Central.HR;

         if (frm_report_pwa->report_pwa->Central.SVI >
                frm_report_pwa->chrt_sevr_reference->LeftAxis->Maximum)
         {
            displayed_sevr = frm_report_pwa->chrt_sevr_reference->LeftAxis->Maximum;
         }
         else if (frm_report_pwa->report_pwa->Central.SVI <
                     frm_report_pwa->chrt_sevr_reference->LeftAxis->Minimum)
         {
            displayed_sevr = frm_report_pwa->chrt_sevr_reference->LeftAxis->Minimum;
         }
         if (frm_report_pwa->report_pwa->Central.HR >
                frm_report_pwa->chrt_sevr_reference->BottomAxis->Maximum)
         {
            displayed_hr = frm_report_pwa->chrt_sevr_reference->BottomAxis->Maximum;
         }
         else if (frm_report_pwa->report_pwa->Central.HR <
                     frm_report_pwa->chrt_sevr_reference->BottomAxis->Minimum)
         {
            displayed_hr = frm_report_pwa->chrt_sevr_reference->BottomAxis->Minimum;
         }
         displayed_sevr = math_Round(displayed_sevr);
         displayed_hr = math_Round(displayed_hr);

         srs_sevr_point_reference->AddXY(displayed_hr, displayed_sevr, "", clBlue);

         // Flow Graph
         if (frm_report_pwa->report_pwa->Central.SVI >
                frm_report_pwa->chrt_sevr_flow_reference->BottomAxis->Maximum)
         {
            srs_sevr_flow_point->AddXY(frm_report_pwa->chrt_sevr_flow_reference->BottomAxis->Maximum,
                                     100,
                                     "", clBlue);
         }
         else if (frm_report_pwa->report_pwa->Central.SVI <
                     frm_report_pwa->chrt_sevr_flow_reference->BottomAxis->Minimum)
         {
            srs_sevr_flow_point->AddXY(frm_report_pwa->chrt_sevr_flow_reference->BottomAxis->Minimum,
                                     frm_report_pwa->chrt_sevr_flow_reference->BottomAxis->Minimum,
                                     "", clBlue);
         }
         else
         {
            if (frm_report_pwa->report_pwa->Central.SVI > 100)
            {
               srs_sevr_flow_point->AddXY(frm_report_pwa->report_pwa->Central.SVI,
                                        100, "", clBlue);
            }
            else
            {
               srs_sevr_flow_point->AddXY(frm_report_pwa->report_pwa->Central.SVI,
                                       frm_report_pwa->report_pwa->Central.SVI,
                                       "", clBlue);
            }
         }
      }
   }
}

void Tfrm_report_pwa::report_display_normals_augidx(void)
{
   float       log_value;
   int         start_pt;
   int         end_pt;
   int         x;
   int         graph_height;
   float       position_ratio;
   int         indicator_left;
   AnsiString  S;

   start_pt = 20;
   end_pt = 90;

   frm_report_pwa->chrt_augidx_reference->BottomAxis->SetMinMax(start_pt, end_pt);
   frm_report_pwa->chrt_augidx_reference->LeftAxis->SetMinMax(((aixhr75_coeff_1) * (end_pt * end_pt)) + (aixhr75_coeff_2 * end_pt) + aixhr75_y_intercept + (2 * aixhr75_confidence_90_offset),
                                                            ((aixhr75_coeff_1) * (start_pt * start_pt)) + (aixhr75_coeff_2 * start_pt) + aixhr75_y_intercept - (1.5 * aixhr75_confidence_90_offset));
   x = start_pt;
   srs_aix_lower_reference->Clear();
   srs_aix_normal_reference->Clear();
   srs_aix_upper_reference->Clear();
   while (x <= end_pt)
   {
      srs_aix_lower_reference->AddXY(x,
                              ((aixhr75_coeff_1) * (x * x)) + (aixhr75_coeff_2 * x) + aixhr75_y_intercept - aixhr75_confidence_90_offset,
                              "", clTeeColor);

      srs_aix_normal_reference->AddXY(x,
                               ((aixhr75_coeff_1) * (x * x)) + (aixhr75_coeff_2 * x) + aixhr75_y_intercept,
                               "", clTeeColor);
      srs_aix_upper_reference->AddXY(x,
                              ((aixhr75_coeff_1) * (x * x)) + (aixhr75_coeff_2 * x) + aixhr75_y_intercept + aixhr75_confidence_90_offset,
                              "", clTeeColor);
      x = x + 2;
   }

   srs_aix_point_reference->Clear();
   srs_aix_hr75_point_reference->Clear();
   srs_aix_hr75_point_reference->Marks->Visible = false;
   if (report_age >= PATIENT_YOUNG_AGE && frm_report_pwa->report_pwa->MeasureType == PWA_RADIAL)
   {
      if (frm_report_pwa->report_pwa->Central.AGPH != DEFAULT_VALUE)
      {
         srs_aix_hr75_point_reference->Marks->Visible = true;
         if (frm_report_pwa->report_pwa->Central.AGPH >
                frm_report_pwa->chrt_augidx_reference->LeftAxis->Maximum)
         {
            srs_aix_point_reference->AddXY(report_age,
                                       frm_report_pwa->chrt_augidx_reference->LeftAxis->Maximum,
                                       "", clBlue);
         }
         else if (frm_report_pwa->report_pwa->Central.AGPH <
                     frm_report_pwa->chrt_augidx_reference->LeftAxis->Minimum)
         {
            srs_aix_point_reference->AddXY(report_age,
                                       frm_report_pwa->chrt_augidx_reference->LeftAxis->Minimum,
                                       "", clBlue);
         }
         else
         {
            srs_aix_point_reference->AddXY(report_age,
                                       math_Round(frm_report_pwa->report_pwa->Central.AGPH),
                                       "", clBlue);
         }
      }

      if (frm_report_pwa->report_pwa->Central.AGPH_HR75 != DEFAULT_VALUE)
      {

         if (frm_report_pwa->report_pwa->Central.AGPH_HR75 >
             frm_report_pwa->chrt_augidx_reference->LeftAxis->Maximum)
         {
            srs_aix_hr75_point_reference->AddXY(report_age,
                                         frm_report_pwa->chrt_augidx_reference->LeftAxis->Maximum,
                                         "", clYellow);
         }
         else if (frm_report_pwa->report_pwa->Central.AGPH_HR75 <
                  frm_report_pwa->chrt_augidx_reference->LeftAxis->Minimum)
         {
            srs_aix_hr75_point_reference->AddXY(report_age,
                                         frm_report_pwa->chrt_augidx_reference->LeftAxis->Minimum,
                                         "", clYellow);
         }
         else
         {
            srs_aix_hr75_point_reference->AddXY(report_age,
                                         math_Round(frm_report_pwa->report_pwa->Central.AGPH_HR75),
                                         "", clYellow);
         }
      }
   }

   if (frm_report_pwa->report_pwa->Central.HR > 75)  // Heart rate reference
   {
      srs_aix_hr75_point_reference->Marks->ArrowLength = 12;
   }
   else
   {
      srs_aix_hr75_point_reference->Marks->ArrowLength = -24;
   }
}

void Tfrm_report_pwa::report_display_normals_aphr75(void)
{
   float       log_value;
   int         start_pt;
   int         end_pt;
   int         x;
   int         graph_height;
   float       position_ratio;
   int         indicator_left;
   AnsiString  S;

   start_pt = 20;
   end_pt = 90;

   frm_report_pwa->chrt_ap_reference->BottomAxis->SetMinMax(start_pt, end_pt);
   frm_report_pwa->chrt_ap_reference->LeftAxis->SetMinMax(end_pt * ap_gradient + ap_y_intercept + (2 * ap_confidence_90_offset),
                                                        start_pt * ap_gradient + ap_y_intercept - (1.5 * ap_confidence_90_offset));
   x = start_pt;
   srs_ap_lower_reference->Clear();
   srs_ap_normal_reference->Clear();
   srs_ap_upper_reference->Clear();
   while (x <= end_pt)
   {
      srs_ap_lower_reference->AddXY(x,
                          ap_gradient * x + ap_y_intercept - ap_confidence_90_offset,
                          "", clTeeColor);

      srs_ap_normal_reference->AddXY(x,
                           ap_gradient * x + ap_y_intercept,
                           "", clTeeColor);
      srs_ap_upper_reference->AddXY(x,
                          ap_gradient * x + ap_y_intercept + ap_confidence_90_offset,
                          "", clTeeColor);
      x = x + 2;
   }

   srs_ap_point_reference->Clear();
   srs_ap_hr75_point_reference->Marks->Visible = false;
   srs_ap_hr75_point_reference->Visible = false;
   cv_age_ap = 0;
   if (report_age >= PATIENT_YOUNG_AGE && frm_report_pwa->report_pwa->MeasureType == PWA_RADIAL)
   {

      if (frm_report_pwa->report_pwa->Central.AP != DEFAULT_VALUE)
      {
         srs_ap_hr75_point_reference->Marks->Visible = true;
         if (frm_report_pwa->report_pwa->Central.AP >
                frm_report_pwa->chrt_ap_reference->LeftAxis->Maximum)
         {
            srs_ap_point_reference->AddXY(report_age,
                                   frm_report_pwa->chrt_ap_reference->LeftAxis->Maximum,
                                   "", clBlue);
         }
         else if (frm_report_pwa->report_pwa->Central.AP <
                     frm_report_pwa->chrt_ap_reference->LeftAxis->Minimum)
         {
            srs_ap_point_reference->AddXY(report_age,
                                   frm_report_pwa->chrt_ap_reference->LeftAxis->Minimum,
                                   "", clBlue);
         }
         else
         {
            srs_ap_point_reference->AddXY(report_age,
                                   math_Round(frm_report_pwa->report_pwa->Central.AP),
                                   "", clBlue);
         }

         // PM V9
         // Display reference age
         cv_age_ap = math_Round(frm_report_pwa->report_pwa->ReferenceAge);
         if (cv_age_ap != DEFAULT_VALUE)
         {
            shape_cv_range->Hint = "Statistical Estimate of \"Vascular Age\" Based on Central Parameters.";
            shape_cv_age->Visible = true;
            // Reference Age cannot be below 20 or above 80
            if (cv_age_ap < 20)
            {
               cv_age_ap = 20;
               shape_cv_age->Left = shape_cv_range->Left;
            }
            // If Reference Age is below 23 or above 77, the display cannot be
            // centred on the exact value. So place it at the extreme
            else if (cv_age_ap < 23)
            {
               shape_cv_age->Left = shape_cv_range->Left;
            }
            else if (cv_age_ap >= 80)
            {
               cv_age_ap = 80;
               shape_cv_age->Left = shape_cv_range->Left + shape_cv_range->Width - shape_cv_age->Width;
            }
            else if (cv_age_ap > 77)
            {
               shape_cv_age->Left = shape_cv_range->Left + shape_cv_range->Width - shape_cv_age->Width;
            }
            // Display the Reference Age shape centred precisely on the value
            else
            {
               shape_cv_age->Left = shape_cv_range->Left - (shape_cv_age->Width / 2) + ((shape_cv_range->Width) * (cv_age_ap - 20) / 60);
            }
         }
         else
         {
            // If Reference Age is not calculated - display a message on the
            // status bar, but only if there is not an inconclusive message
            shape_cv_age->Visible = false;
            if (report_pwa->Height == DEFAULT_VALUE || report_pwa->Height <= 0)
            {
               shape_cv_range->Hint = "Reference Age Not Calculated: Height Not Entered.";
               if (!report_pwa->CalcIsInconclusive)
               {
                  emma_display_statusbar_message("Reference Age Not Calculated:", "Height Not Entered.",
                                          "", sphygmocor_white);
               }
            }
            else if (report_pwa->Central.HR < 40)
            {
               shape_cv_range->Hint = "Reference Age Not Calculated: Heart Rate out of Range Low.";
               if (!report_pwa->CalcIsInconclusive)
               {
                  emma_display_statusbar_message("Reference Age Not Calculated:", "Heart Rate out of Range Low.",
                                          "", sphygmocor_white);
               }
            }
            else if (report_pwa->Central.HR > 110)
            {
               shape_cv_range->Hint = "Reference Age Not Calculated: Heart Rate out of Range High.";
               if (!report_pwa->CalcIsInconclusive)
               {
                  emma_display_statusbar_message("Reference Age Not Calculated:", "Heart Rate out of Range High.",
                                          "", sphygmocor_white);
               }
            }
         }
      }
      else
      {
         shape_cv_age->Visible = false;
         shape_cv_range->Hint = "Reference Age Not Calculated: AP Not Determined.";
         if (!report_pwa->CalcIsInconclusive)
         {
            emma_display_statusbar_message("Reference Age Not Calculated:", "AP Not Determined.",
                                    "", sphygmocor_white);
         }
      }

      if (frm_report_pwa->report_pwa->Central.AP_HR75 != DEFAULT_VALUE)
      {
         if (frm_report_pwa->report_pwa->Central.AP_HR75 >
             frm_report_pwa->chrt_ap_reference->LeftAxis->Maximum)
         {
            srs_ap_hr75_point_reference->AddXY(report_age,
                                     frm_report_pwa->chrt_ap_reference->LeftAxis->Maximum,
                                     "", clYellow);
         }
         else if (frm_report_pwa->report_pwa->Central.AP_HR75 <
                  frm_report_pwa->chrt_ap_reference->LeftAxis->Minimum)
         {
            srs_ap_hr75_point_reference->AddXY(report_age,
                                     frm_report_pwa->chrt_ap_reference->LeftAxis->Minimum,
                                     "", clYellow);
         }
         else
         {
            srs_ap_hr75_point_reference->AddXY(report_age,
                                     math_Round(frm_report_pwa->report_pwa->Central.AP_HR75),
                                     "", clYellow);
         }
      }
   }
   else
   {
      // PM V9
      // No need to display these messages in the status bar as there should
      // already be a Not Validated message
      shape_cv_age->Visible = false;
      if (report_age < PATIENT_YOUNG_AGE)
      {
         shape_cv_range->Hint = "Reference Age Not Calculated: Patient Under 18 Years of Age.";
      }
      else
      {
         shape_cv_range->Hint = "Reference Age Not Calculated: Radial Measurements Only.";
      }
   }


   if (frm_report_pwa->report_pwa->Central.HR > 75)  // Heart rate reference
   {
      srs_ap_hr75_point_reference->Marks->ArrowLength = 12;
   }
   else
   {
      srs_ap_hr75_point_reference->Marks->ArrowLength = -24;
   }
}

void Tfrm_report_pwa::report_display_normals_sp(void)
{
   float       log_value;
   int         start_pt;
   int         end_pt;
   int         x;
   int         graph_height;
   float       position_ratio;
   int         indicator_left;
   AnsiString  S;

   start_pt = 20;
   end_pt = 90;

   frm_report_pwa->chrt_sp_reference->BottomAxis->SetMinMax(start_pt, end_pt);
   frm_report_pwa->chrt_sp_reference->LeftAxis->SetMinMax(end_pt * sp_gradient + sp_y_intercept + (2 * sp_confidence_90_offset),
                                                        start_pt * sp_gradient + sp_y_intercept - (1.5 * sp_confidence_90_offset));
   x = start_pt;
   srs_sp_lower_reference->Clear();
   srs_sp_normal_reference->Clear();
   srs_sp_upper_reference->Clear();
   while (x <= end_pt)
   {
      srs_sp_lower_reference->AddXY(x,
                          sp_gradient * x + sp_y_intercept - sp_confidence_90_offset,
                          "", clTeeColor);

      srs_sp_normal_reference->AddXY(x,
                           sp_gradient * x + sp_y_intercept,
                           "", clTeeColor);
      srs_sp_upper_reference->AddXY(x,
                          sp_gradient * x + sp_y_intercept + sp_confidence_90_offset,
                          "", clTeeColor);
      x = x + 2;
   }

   srs_sp_point_reference->Clear();
   if (report_age >= PATIENT_YOUNG_AGE && frm_report_pwa->report_pwa->MeasureType == PWA_RADIAL)
   {
      if (frm_report_pwa->report_pwa->Central.Sp != DEFAULT_VALUE)
      {
         if (frm_report_pwa->report_pwa->Central.Sp >
            frm_report_pwa->chrt_sp_reference->LeftAxis->Maximum)
         {
            srs_sp_point_reference->AddXY(report_age,
                                   frm_report_pwa->chrt_sp_reference->LeftAxis->Maximum,
                                   "", clBlue);
         }
         else if (frm_report_pwa->report_pwa->Central.Sp <
                  frm_report_pwa->chrt_sp_reference->LeftAxis->Minimum)
         {
            srs_sp_point_reference->AddXY(report_age,
                                   frm_report_pwa->chrt_sp_reference->LeftAxis->Minimum,
                                   "", clBlue);
         }
         else
         {
            srs_sp_point_reference->AddXY(report_age,
                                   math_Round(frm_report_pwa->report_pwa->Central.Sp),
                                   "", clBlue);
         }
      }
   }
}

void Tfrm_report_pwa::report_display_normals_pp(void)
{
   float       pp;
   float       log_value;
   int         start_pt;
   int         end_pt;
   int         x;
   int         graph_height;
   float       position_ratio;
   int         indicator_left;
   AnsiString  S;

   start_pt = 20;
   end_pt = 90;

   frm_report_pwa->chrt_pp_reference->BottomAxis->SetMinMax(start_pt, end_pt);
   frm_report_pwa->chrt_pp_reference->LeftAxis->SetMinMax(end_pt * pp_gradient + pp_y_intercept + (2 * pp_confidence_90_offset),
                                                        start_pt * pp_gradient + pp_y_intercept - (1.5 * pp_confidence_90_offset));
   x = start_pt;
   srs_pp_lower_reference->Clear();
   srs_pp_normal_reference->Clear();
   srs_pp_upper_reference->Clear();
   while (x <= end_pt)
   {
      srs_pp_lower_reference->AddXY(x,
                          pp_gradient * x + pp_y_intercept - pp_confidence_90_offset,
                          "", clTeeColor);

      srs_pp_normal_reference->AddXY(x,
                           pp_gradient * x + pp_y_intercept,
                           "", clTeeColor);
      srs_pp_upper_reference->AddXY(x,
                          pp_gradient * x + pp_y_intercept + pp_confidence_90_offset,
                          "", clTeeColor);
      x = x + 2;
   }

   srs_pp_point_reference->Clear();
   pp = frm_report_pwa->report_pwa->Central.Sp - frm_report_pwa->report_pwa->Central.Dp;
   if (report_age >= PATIENT_YOUNG_AGE && frm_report_pwa->report_pwa->MeasureType == PWA_RADIAL)
   {
      if (pp != DEFAULT_VALUE)
      {
         if (pp > frm_report_pwa->chrt_pp_reference->LeftAxis->Maximum)
         {
            srs_pp_point_reference->AddXY(report_age,
                                   frm_report_pwa->chrt_pp_reference->LeftAxis->Maximum,
                                   "", clBlue);
         }
         else if (pp < frm_report_pwa->chrt_pp_reference->LeftAxis->Minimum)
         {
            srs_pp_point_reference->AddXY(report_age,
                                   frm_report_pwa->chrt_pp_reference->LeftAxis->Minimum,
                                   "", clBlue);
         }
         else
         {
            srs_pp_point_reference->AddXY(report_age,
                                   math_Round(pp),
                                   "", clBlue);
         }
      }
   }
}
// PM CR
// PM V9
void Tfrm_report_pwa::report_display_clinical_normals(void)
{
   float       region_width;
   float       lower_limit;
   float       pp;
   int         ap_length;
   int         aix_length;
   int         pp_length;
   int         sp_length;
   int         aixhr75_length;
   CLINICAL_NORMALS_RANGE  range;

   // SP
   range = report_determine_sp_range(frm_report_pwa->report_pwa->Central.Sp, report_age, frm_report_pwa->report_pwa->MeasureType);
   lbl_clinical_sp->Font->Color = sphygmocor_white;
   shape_clinical_sp->Brush->Color = sphygmocor_white;
   shape_clinical_sp->Pen->Color = sphygmocor_white;
   if (frm_report_pwa->report_pwa->Central.Sp == DEFAULT_VALUE)
   {
      lbl_clinical_sp->Caption = "n/c";
      lbl_clinical_sp->Left = shape_clinical_sp_range->Left + (shape_clinical_sp_range->Width * 2/ 3) - (lbl_clinical_sp->Width / 2);
      shape_clinical_sp->Visible = false;
      lbl_clinical_sp_lower->Visible = false;
      lbl_clinical_sp_upper->Visible = false;
   }
   else
   {
      shape_clinical_sp->Visible = true;
      lbl_clinical_sp_lower->Visible = true;
      lbl_clinical_sp_upper->Visible = true;
      lbl_clinical_sp->Caption = RoundIntToStr(frm_report_pwa->report_pwa->Central.Sp);
      sp_length = math_Round(frm_report_pwa->report_pwa->Central.Sp);
      switch (range)
      {
         case RANGE_LOW:
         case RANGE_NORMAL_LOW:
         case RANGE_NORMAL_HIGH:
            region_width = 3 * (report_sp_cutoff_normal - report_sp_cutoff_low);
            lower_limit = report_sp_cutoff_low - (report_sp_cutoff_normal - report_sp_cutoff_low);
            if (sp_length < lower_limit)
            {
               sp_length = shape_clinical_sp_range->Left;
            }
            else
            {
               sp_length = shape_clinical_sp_range->Left + math_Round(((sp_length - lower_limit) / region_width) * (float) shape_clinical_sp_range->Width);
            }
            shape_clinical_sp->Left = sp_length - (shape_clinical_sp->Width / 2);
            lbl_clinical_sp->Left = sp_length - (lbl_clinical_sp->Width / 2);
            lbl_clinical_sp_lower->Caption = RoundIntToStr(report_sp_cutoff_low);
            lbl_clinical_sp_upper->Caption = RoundIntToStr(report_sp_cutoff_high);
            break;

         case RANGE_HIGH:
            region_width = report_sp_cutoff_high - report_sp_cutoff_normal;
            lower_limit = report_sp_cutoff_high;
            if (sp_length > lower_limit + region_width)
            {
               sp_length = shape_clinical_sp_high->Left + shape_clinical_sp_high->Width;
            }
            else
            {
               sp_length = shape_clinical_sp_high->Left + math_Round(((sp_length - lower_limit) / region_width) * (float) shape_clinical_sp_high->Width);
            }
            shape_clinical_sp->Left = sp_length - (shape_clinical_sp->Width / 2);
            lbl_clinical_sp->Left = sp_length - (lbl_clinical_sp->Width / 2);
            lbl_clinical_sp_lower->Caption = RoundIntToStr(report_sp_cutoff_low);
            lbl_clinical_sp_upper->Caption = RoundIntToStr(report_sp_cutoff_high);
            lbl_clinical_sp->Font->Color = sphygmocor_red;
            shape_clinical_sp->Brush->Color = sphygmocor_red;
            shape_clinical_sp->Pen->Color = sphygmocor_red;
            break;

         case RANGE_UNDEFINED:
            lbl_clinical_sp->Caption = "n/a";
            lbl_clinical_sp->Left = shape_clinical_sp_range->Left + (shape_clinical_sp_range->Width * 2 / 3) - (lbl_clinical_sp->Width / 2);
            shape_clinical_sp->Visible = false;
            lbl_clinical_sp_lower->Visible = false;
            lbl_clinical_sp_upper->Visible = false;
            break;
      }
   }

   // PP
   // Rounding both SP and DP ensures that PP is equal to the displayed difference
   // between SP and DP
   pp = math_Round(frm_report_pwa->report_pwa->Central.Sp) - math_Round(frm_report_pwa->report_pwa->Central.Dp);
   range = report_determine_pp_range(pp, report_age, frm_report_pwa->report_pwa->MeasureType);
   lbl_clinical_pp->Font->Color = sphygmocor_white;
   shape_clinical_pp->Brush->Color = sphygmocor_white;
   shape_clinical_pp->Pen->Color = sphygmocor_white;
   if (pp == DEFAULT_VALUE)
   {
      lbl_clinical_pp->Caption = "n/c";
      lbl_clinical_pp->Left = shape_clinical_pp_range->Left + (shape_clinical_pp_range->Width * 2/ 3) - (lbl_clinical_pp->Width / 2);
      shape_clinical_pp->Visible = false;
      lbl_clinical_pp_lower->Visible = false;
      lbl_clinical_pp_upper->Visible = false;
   }
   else
   {
      shape_clinical_pp->Visible = true;
      lbl_clinical_pp_lower->Visible = true;
      lbl_clinical_pp_upper->Visible = true;
      lbl_clinical_pp->Caption = RoundIntToStr(pp);
      pp_length = math_Round(pp);
      switch (range)
      {
         case RANGE_LOW:
         case RANGE_NORMAL_LOW:
         case RANGE_NORMAL_HIGH:
            region_width = 3 * (report_pp_cutoff_normal - report_pp_cutoff_low);
            lower_limit = report_pp_cutoff_low - (report_pp_cutoff_normal - report_pp_cutoff_low);
            if (pp_length < lower_limit)
            {
               pp_length = shape_clinical_pp_range->Left;
            }
            else
            {
               pp_length = shape_clinical_pp_range->Left + math_Round(((pp_length - lower_limit) / region_width) * (float) shape_clinical_pp_range->Width);
            }
            shape_clinical_pp->Left = pp_length - (shape_clinical_pp->Width / 2);
            lbl_clinical_pp->Left = pp_length - (lbl_clinical_pp->Width / 2);
            lbl_clinical_pp_lower->Caption = RoundIntToStr(report_pp_cutoff_low);
            lbl_clinical_pp_upper->Caption = RoundIntToStr(report_pp_cutoff_high);
            break;

         case RANGE_HIGH:
            region_width = report_pp_cutoff_high - report_pp_cutoff_normal;
            lower_limit = report_pp_cutoff_high;
            if (pp_length > lower_limit + region_width)
            {
               pp_length = shape_clinical_pp_high->Left + shape_clinical_pp_high->Width;
            }
            else
            {
               pp_length = shape_clinical_pp_high->Left + math_Round(((pp_length - lower_limit) / region_width) * (float) shape_clinical_pp_high->Width);
            }
            shape_clinical_pp->Left = pp_length - (shape_clinical_pp->Width / 2);
            lbl_clinical_pp->Left = pp_length - (lbl_clinical_pp->Width / 2);
            lbl_clinical_pp_lower->Caption = RoundIntToStr(report_pp_cutoff_low);
            lbl_clinical_pp_upper->Caption = RoundIntToStr(report_pp_cutoff_high);
            lbl_clinical_pp->Font->Color = sphygmocor_red;
            shape_clinical_pp->Brush->Color = sphygmocor_red;
            shape_clinical_pp->Pen->Color = sphygmocor_red;
            break;

         case RANGE_UNDEFINED:
            lbl_clinical_pp->Caption = "n/a";
            lbl_clinical_pp->Left = shape_clinical_pp_range->Left + (shape_clinical_pp_range->Width * 2 / 3) - (lbl_clinical_pp->Width / 2);
            shape_clinical_pp->Visible = false;
            lbl_clinical_pp_lower->Visible = false;
            lbl_clinical_pp_upper->Visible = false;
            break;
      }
   }

   // AP
   range = report_determine_ap_range(frm_report_pwa->report_pwa->Central.AP, report_age, frm_report_pwa->report_pwa->MeasureType);
   lbl_clinical_ap->Font->Color = sphygmocor_white;
   shape_clinical_ap->Brush->Color = sphygmocor_white;
   shape_clinical_ap->Pen->Color = sphygmocor_white;
   if (frm_report_pwa->report_pwa->Central.AP == DEFAULT_VALUE)
   {
      lbl_clinical_ap->Caption = "n/c";
      lbl_clinical_ap->Left = shape_clinical_ap_range->Left + (shape_clinical_ap_range->Width * 2/ 3) - (lbl_clinical_ap->Width / 2);
      shape_clinical_ap->Visible = false;
      lbl_clinical_ap_lower->Visible = false;
      lbl_clinical_ap_upper->Visible = false;
   }
   else
   {
      shape_clinical_ap->Visible = true;
      lbl_clinical_ap_lower->Visible = true;
      lbl_clinical_ap_upper->Visible = true;
      lbl_clinical_ap->Caption = RoundIntToStr(frm_report_pwa->report_pwa->Central.AP);
      ap_length = math_Round(frm_report_pwa->report_pwa->Central.AP);
      switch (range)
      {
         case RANGE_LOW:
         case RANGE_NORMAL_LOW:
         case RANGE_NORMAL_HIGH:
            region_width = 3 * (report_ap_cutoff_normal - report_ap_cutoff_low);
            lower_limit = report_ap_cutoff_low - (report_ap_cutoff_normal - report_ap_cutoff_low);
            if (ap_length < lower_limit)
            {
               ap_length = shape_clinical_ap_range->Left;
            }
            else
            {
               ap_length = shape_clinical_ap_range->Left + math_Round(((ap_length - lower_limit) / region_width) * (float) shape_clinical_ap_range->Width);
            }
            shape_clinical_ap->Left = ap_length - (shape_clinical_ap->Width / 2);
            lbl_clinical_ap->Left = ap_length - (lbl_clinical_ap->Width / 2);
            lbl_clinical_ap_lower->Caption = RoundIntToStr(report_ap_cutoff_low);
            lbl_clinical_ap_upper->Caption = RoundIntToStr(report_ap_cutoff_high);
            break;

         case RANGE_HIGH:
            region_width = report_ap_cutoff_high - report_ap_cutoff_normal;
            lower_limit = report_ap_cutoff_high;
            if (ap_length > lower_limit + region_width)
            {
               ap_length = shape_clinical_ap_high->Left + shape_clinical_ap_high->Width;
            }
            else
            {
               ap_length = shape_clinical_ap_high->Left + math_Round(((ap_length - lower_limit) / region_width) * (float) shape_clinical_ap_high->Width);
            }
            shape_clinical_ap->Left = ap_length - (shape_clinical_ap->Width / 2);
            lbl_clinical_ap->Left = ap_length - (lbl_clinical_ap->Width / 2);
            lbl_clinical_ap_lower->Caption = RoundIntToStr(report_ap_cutoff_low);
            lbl_clinical_ap_upper->Caption = RoundIntToStr(report_ap_cutoff_high);
            lbl_clinical_ap->Font->Color = sphygmocor_red;
            shape_clinical_ap->Brush->Color = sphygmocor_red;
            shape_clinical_ap->Pen->Color = sphygmocor_red;
            break;

         case RANGE_UNDEFINED:
            lbl_clinical_ap->Caption = "n/a";
            lbl_clinical_ap->Left = shape_clinical_ap_range->Left + (shape_clinical_ap_range->Width * 2 / 3) - (lbl_clinical_ap->Width / 2);
            shape_clinical_ap->Visible = false;
            lbl_clinical_ap_lower->Visible = false;
            lbl_clinical_ap_upper->Visible = false;
            break;
      }
   }

   // AIxHR75
   range = report_determine_aixhr75_range(frm_report_pwa->report_pwa->Central.AGPH_HR75, report_age, frm_report_pwa->report_pwa->MeasureType);
   lbl_clinical_aixhr75->Font->Color = sphygmocor_white;
   shape_clinical_aixhr75->Brush->Color = sphygmocor_white;
   shape_clinical_aixhr75->Pen->Color = sphygmocor_white;
   if (frm_report_pwa->report_pwa->Central.AGPH_HR75 == DEFAULT_VALUE)
   {
      lbl_clinical_aixhr75->Caption = "n/c";
      lbl_clinical_aixhr75->Left = shape_clinical_aixhr75_range->Left + (shape_clinical_aixhr75_range->Width * 2/ 3) - (lbl_clinical_aixhr75->Width / 2);
      shape_clinical_aixhr75->Visible = false;
      lbl_clinical_aixhr75_lower->Visible = false;
      lbl_clinical_aixhr75_upper->Visible = false;
   }
   else
   {
      shape_clinical_aixhr75->Visible = true;
      lbl_clinical_aixhr75_lower->Visible = true;
      lbl_clinical_aixhr75_upper->Visible = true;
      lbl_clinical_aixhr75->Caption = RoundIntToStr(frm_report_pwa->report_pwa->Central.AGPH_HR75);
      aixhr75_length = math_Round(frm_report_pwa->report_pwa->Central.AGPH_HR75);
      switch (range)
      {
         case RANGE_LOW:
         case RANGE_NORMAL_LOW:
         case RANGE_NORMAL_HIGH:
            region_width = 3 * (report_aixhr75_cutoff_normal - report_aixhr75_cutoff_low);
            lower_limit = report_aixhr75_cutoff_low - (report_aixhr75_cutoff_normal - report_aixhr75_cutoff_low);
            if (aixhr75_length < lower_limit)
            {
               aixhr75_length = shape_clinical_aixhr75_range->Left;
            }
            else
            {
               aixhr75_length = shape_clinical_aixhr75_range->Left + math_Round(((aixhr75_length - lower_limit) / region_width) * (float) shape_clinical_aixhr75_range->Width);
            }
            shape_clinical_aixhr75->Left = aixhr75_length - (shape_clinical_aixhr75->Width / 2);
            lbl_clinical_aixhr75->Left = aixhr75_length - (lbl_clinical_aixhr75->Width / 2);
            lbl_clinical_aixhr75_lower->Caption = RoundIntToStr(report_aixhr75_cutoff_low);
            lbl_clinical_aixhr75_upper->Caption = RoundIntToStr(report_aixhr75_cutoff_high);
            break;

         case RANGE_HIGH:
            region_width = report_aixhr75_cutoff_high - report_aixhr75_cutoff_normal;
            lower_limit = report_aixhr75_cutoff_high;
            if (aixhr75_length > lower_limit + region_width)
            {
               aixhr75_length = shape_clinical_aixhr75_high->Left + shape_clinical_aixhr75_high->Width;
            }
            else
            {
               aixhr75_length = shape_clinical_aixhr75_high->Left + math_Round(((aixhr75_length - lower_limit) / region_width) * (float) shape_clinical_aixhr75_high->Width);
            }
            shape_clinical_aixhr75->Left = aixhr75_length - (shape_clinical_aixhr75->Width / 2);
            lbl_clinical_aixhr75->Left = aixhr75_length - (lbl_clinical_aixhr75->Width / 2);
            lbl_clinical_aixhr75_lower->Caption = RoundIntToStr(report_aixhr75_cutoff_low);
            lbl_clinical_aixhr75_upper->Caption = RoundIntToStr(report_aixhr75_cutoff_high);
            lbl_clinical_aixhr75->Font->Color = sphygmocor_red;
            shape_clinical_aixhr75->Brush->Color = sphygmocor_red;
            shape_clinical_aixhr75->Pen->Color = sphygmocor_red;
            break;

         case RANGE_UNDEFINED:
            lbl_clinical_aixhr75->Caption = "n/a";
            lbl_clinical_aixhr75->Left = shape_clinical_aixhr75_range->Left + (shape_clinical_aixhr75_range->Width * 2 / 3) - (lbl_clinical_aixhr75->Width / 2);
            shape_clinical_aixhr75->Visible = false;
            lbl_clinical_aixhr75_lower->Visible = false;
            lbl_clinical_aixhr75_upper->Visible = false;
            break;
      }
   }

   // AIx
   range = report_determine_aix_range(frm_report_pwa->report_pwa->Central.AGPH, report_age, frm_report_pwa->report_pwa->MeasureType);
   lbl_clinical_aix->Font->Color = sphygmocor_white;
   shape_clinical_aix->Brush->Color = sphygmocor_white;
   shape_clinical_aix->Pen->Color = sphygmocor_white;
   if (frm_report_pwa->report_pwa->Central.AGPH == DEFAULT_VALUE)
   {
      lbl_clinical_aix->Caption = "n/c";
      lbl_clinical_aix->Left = shape_clinical_aix_range->Left + (shape_clinical_aix_range->Width * 2/ 3) - (lbl_clinical_aix->Width / 2);
      shape_clinical_aix->Visible = false;
      lbl_clinical_aix_lower->Visible = false;
      lbl_clinical_aix_upper->Visible = false;
   }
   else
   {
      shape_clinical_aix->Visible = true;
      lbl_clinical_aix_lower->Visible = true;
      lbl_clinical_aix_upper->Visible = true;
      lbl_clinical_aix->Caption = RoundIntToStr(frm_report_pwa->report_pwa->Central.AGPH);
      aix_length = math_Round(frm_report_pwa->report_pwa->Central.AGPH);
      switch (range)
      {
         case RANGE_LOW:
         case RANGE_NORMAL_LOW:
         case RANGE_NORMAL_HIGH:
            region_width = 3 * (report_aix_cutoff_normal - report_aix_cutoff_low);
            lower_limit = report_aix_cutoff_low - (report_aix_cutoff_normal - report_aix_cutoff_low);
            if (aix_length < lower_limit)
            {
               aix_length = shape_clinical_aix_range->Left;
            }
            else
            {
               aix_length = shape_clinical_aix_range->Left + math_Round(((aix_length - lower_limit) / region_width) * (float) shape_clinical_aix_range->Width);
            }
            shape_clinical_aix->Left = aix_length - (shape_clinical_aix->Width / 2);
            lbl_clinical_aix->Left = aix_length - (lbl_clinical_aix->Width / 2);
            lbl_clinical_aix_lower->Caption = RoundIntToStr(report_aix_cutoff_low);
            lbl_clinical_aix_upper->Caption = RoundIntToStr(report_aix_cutoff_high);
            break;

         case RANGE_HIGH:
            region_width = report_aix_cutoff_high - report_aix_cutoff_normal;
            lower_limit = report_aix_cutoff_high;
            if (aix_length > lower_limit + region_width)
            {
               aix_length = shape_clinical_aix_high->Left + shape_clinical_aix_high->Width;
            }
            else
            {
               aix_length = shape_clinical_aix_high->Left + math_Round(((aix_length - lower_limit) / region_width) * (float) shape_clinical_aix_high->Width);
            }
            shape_clinical_aix->Left = aix_length - (shape_clinical_aix->Width / 2);
            lbl_clinical_aix->Left = aix_length - (lbl_clinical_aix->Width / 2);
            lbl_clinical_aix_lower->Caption = RoundIntToStr(report_aix_cutoff_low);
            lbl_clinical_aix_upper->Caption = RoundIntToStr(report_aix_cutoff_high);
            lbl_clinical_aix->Font->Color = sphygmocor_red;
            shape_clinical_aix->Brush->Color = sphygmocor_red;
            shape_clinical_aix->Pen->Color = sphygmocor_red;
            break;

         case RANGE_UNDEFINED:
            lbl_clinical_aix->Caption = "n/a";
            lbl_clinical_aix->Left = shape_clinical_aix_range->Left + (shape_clinical_aix_range->Width * 2 / 3) - (lbl_clinical_aix->Width / 2);
            shape_clinical_aix->Visible = false;
            lbl_clinical_aix_lower->Visible = false;
            lbl_clinical_aix_upper->Visible = false;
            break;
      }
   }
}
//---------------------------------------------------------------------------
void Tfrm_report_pwa::report_display_central_params(void)
{
   AnsiString   S;
   AnsiString   norms_S;
   TFontStyles ed_font_style;
   TFontStyles t1_font_style;
   TFontStyles t2_font_style;
   TFontStyles ap_font_style;
   PATIENT_RECORD_TYPE  pat;
   bool  ed_changed = false;
   bool  t1_changed = false;
   bool  t2_changed = false;

   ed_font_style.Clear();
   switch (frm_report_pwa->report_pwa->Periph.QualityED)
   {
      case VERYSTRONG:
      case STRONG:
         ed_font_style << fsBold;
      break;

      case WEAK:
      case VERYWEAK:
      break;

      default:
         ed_font_style << fsBold;
      break;
   }
   // Detailed screen
   frm_report_pwa->lbl_ed->Font->Style = ed_font_style;
   frm_report_pwa->lbl_svr->Font->Style = ed_font_style;
   frm_report_pwa->lbl_mp->Font->Style = ed_font_style;
   frm_report_pwa->lbl_endsyst->Font->Style = ed_font_style;
   frm_report_pwa->lbl_pti->Font->Style = ed_font_style;

   ap_font_style.Clear();
   ap_font_style << fsBold;
   t1_font_style.Clear();
   switch (frm_report_pwa->report_pwa->Central.QualityT1)
   {
      case VERYSTRONG:
      case STRONG:
         t1_font_style << fsBold;
         break;

      case WEAK:
      case VERYWEAK:
         ap_font_style.Clear();
         break;

      default:
         t1_font_style << fsBold;
         break;
   }

   t2_font_style.Clear();
   switch (frm_report_pwa->report_pwa->Central.QualityT2)
   {
      case VERYSTRONG:
      case STRONG:
         t2_font_style << fsBold;
         break;

      case WEAK:
      case VERYWEAK:
         ap_font_style.Clear();
         break;

      default:
         t2_font_style << fsBold;
         break;
   }
   // Detailed screen
   frm_report_pwa->lbl_aug_idx->Font->Style = ap_font_style;
   frm_report_pwa->lbl_augidx_hr75->Font->Style = ap_font_style;
   frm_report_pwa->lbl_aug->Font->Style = ap_font_style;

   // New Clinical screen
   frm_report_pwa->lbl_clinical_ap->Font->Style = ap_font_style;
   frm_report_pwa->lbl_clinical_aixhr75->Font->Style = ap_font_style;
   frm_report_pwa->lbl_clinical_aix->Font->Style = ap_font_style;

   //Heart Rate
   if (frm_report_pwa->report_pwa->Central.HR < DEFAULT_VALUE)
   {
        S = RoundIntToStr(frm_report_pwa->report_pwa->Central.HR) +" bpm, ";
        norms_S = RoundIntToStr(frm_report_pwa->report_pwa->Central.HR);
   }
   else
   {
        S = "n/c, ";
        norms_S = "n/c";
   }
   if (frm_report_pwa->report_pwa->Central.Period < DEFAULT_VALUE)
   {
        S = S + RoundIntToStr(frm_report_pwa->report_pwa->Central.Period) + " ms";
   }
   else
   {
        S = S + "n/c";
   }
   frm_report_pwa->lbl_hr->Caption = S;
   frm_report_pwa->lbl_clinical_hr->Caption = norms_S;

   if (patient_get(&pat))
   {
      S = "(" + lbl_clinical_hr->Caption + " bpm)";
      chrt_sevr_flow_reference->Title->Text->Clear();
      chrt_sevr_flow_reference->Title->Text->Add("SEVR " + S);
   }

   //Ejection Duration
   if (frm_report_pwa->report_pwa->Central.ED < DEFAULT_VALUE)
   {
        S = RoundIntToStr(frm_report_pwa->report_pwa->Central.ED) + " ms, ";
        if (fabs(frm_report_pwa->report_pwa->Central.ED - frm_report_pwa->report_pwa->Central.CalcED) > 0.5)
        {
            ed_changed = true;
        }
   }
   else
   {
        S = "n/c, ";
   }
   if (frm_report_pwa->report_pwa->Central.EDPeriod < DEFAULT_VALUE)
   {
        S = S + RoundIntToStr(frm_report_pwa->report_pwa->Central.EDPeriod) + "%";
   }
   else
   {
        S = S + "n/c";
   }
   if (ed_changed)
   {
      S = S + " (*)";
      frm_report_pwa->lbl_ed->ShowHint = true;
   }
   else
   {
      frm_report_pwa->lbl_ed->ShowHint = false;
   }
   frm_report_pwa->lbl_ed->Caption = S;

   //SVR
   if (frm_report_pwa->report_pwa->Central.SVI < DEFAULT_VALUE)
   {
      S =  RoundIntToStr(frm_report_pwa->report_pwa->Central.SVI) + "%";

   }
   else
   {
      S = "n/c";
   }
   frm_report_pwa->lbl_svr->Caption = S;

   //t1t2
   if (frm_report_pwa->report_pwa->Central.T1 < DEFAULT_VALUE)
   {
        S = RoundIntToStr(frm_report_pwa->report_pwa->Central.T1) + ", ";// + " ms, ";
        if (fabs(frm_report_pwa->report_pwa->Central.T1 - frm_report_pwa->report_pwa->Central.CalcT1) > 0.5)
        {
            t1_changed = true;
        }
   }
   else
   {
        S = "n/c, ";
   }
   if (frm_report_pwa->report_pwa->Central.T2 < DEFAULT_VALUE)
   {
        S = S + RoundIntToStr(frm_report_pwa->report_pwa->Central.T2) + ", ";// + " ms ";
        if (fabs(frm_report_pwa->report_pwa->Central.T2 - frm_report_pwa->report_pwa->Central.CalcT2) > 0.5)
        {
            t2_changed = true;
        }
   }
   else
   {
        S = S + "n/c, ";
   }

   if (frm_report_pwa->report_pwa->Central.Tr < DEFAULT_VALUE && frm_report_pwa->report_pwa->Central.Tr > 0)
   {
        S = S + RoundIntToStr(frm_report_pwa->report_pwa->Central.Tr); // + " ms ";
   }
   else
   {
        S = S + "n/c";
   }
   S = S + " ms";
   if (t1_changed || t2_changed)
   {
      S = S + " (*)";
      frm_report_pwa->lbl_t1t2->ShowHint = true;
   }
   else
   {
      frm_report_pwa->lbl_t1t2->ShowHint = false;
   }
   frm_report_pwa->lbl_t1t2->Caption = S;

   if (frm_report_pwa->report_pwa->Central.MPS < DEFAULT_VALUE)
   {
        S = RoundIntToStr(frm_report_pwa->report_pwa->Central.MPS) + ", ";
   }
   else
   {
        S = "n/c, ";
   }
   if (frm_report_pwa->report_pwa->Central.MPD < DEFAULT_VALUE)
   {
        S = S + RoundIntToStr(frm_report_pwa->report_pwa->Central.MPD) + " mmHg";
   }
   else
   {
        S = S + "n/c";
   }
   frm_report_pwa->lbl_mp->Caption = S;

   //endsys
   if (frm_report_pwa->report_pwa->Central.ESP < DEFAULT_VALUE)
   {
        S = RoundIntToStr(frm_report_pwa->report_pwa->Central.ESP) + " mmHg";
   }
   else
   {
        S = "n/c";
   }
   frm_report_pwa->lbl_endsyst->Caption = S;

   if (frm_report_pwa->report_pwa->Central.SVI < DEFAULT_VALUE)
   {
      S = RoundIntToStr(frm_report_pwa->report_pwa->Central.TTI) +", " +
          RoundIntToStr(frm_report_pwa->report_pwa->Central.DTI);
   }
   else
   {
        S = "n/c";
   }
   frm_report_pwa->lbl_pti->Caption = S;

   //augidx
   if (frm_report_pwa->report_pwa->Central.AGPH < DEFAULT_VALUE)
   {
        S = RoundIntToStr(math_Round(frm_report_pwa->report_pwa->Central.AGPH));
        S = S + "%, ";
        if (frm_report_pwa->report_pwa->Central.AGPH_HR75 == DEFAULT_VALUE)
        {
           norms_S = "n/c  ";
        }
        else
        {
           norms_S = RoundIntToStr(frm_report_pwa->report_pwa->Central.AGPH_HR75) + "%  ";
        }
   }
   else
   {
        S = "n/c, ";
        norms_S = "n/c  ";
   }


   if (frm_report_pwa->report_pwa->Central.AI1 < DEFAULT_VALUE)
   {
        S = S + RoundIntToStr(frm_report_pwa->report_pwa->Central.AI1) + "%";
   }
   else
   {
        S = S + "n/c";
   }
   frm_report_pwa->lbl_aug_idx->Caption = S;
   frm_report_pwa->lbl_augidx_hr75->Caption = norms_S;

   //AP
   if (frm_report_pwa->report_pwa->Central.AP >= DEFAULT_VALUE)
   {
      frm_report_pwa->lbl_aug->Caption = "n/c";
   }
   else
   {
      frm_report_pwa->lbl_aug->Caption = RoundIntToStr(math_Round(frm_report_pwa->report_pwa->Central.AP)) +" mmHg";
   }

   if (frm_report_pwa->report_pwa->AmplificationRatio >= DEFAULT_VALUE)
   {
      frm_report_pwa->lbl_ppamp->Caption = "n/c";
   }
   else
   {
      frm_report_pwa->lbl_ppamp->Caption = RoundIntToStr(frm_report_pwa->report_pwa->AmplificationRatio) + "%";
   }

   if (frm_report_pwa->report_pwa->Central.P1Height >= DEFAULT_VALUE)
   {
      frm_report_pwa->lbl_p1->Caption = "n/c";
   }
   else
   {
      frm_report_pwa->lbl_p1->Caption = RoundIntToStr(frm_report_pwa->report_pwa->Central.P1Height) +" mmHg";
   }

   // Periph T1, T2, AIx (AP /PP, P2/P1)
   if (frm_report_pwa->report_pwa->Periph.T1 < DEFAULT_VALUE)
   {
        S = RoundIntToStr(frm_report_pwa->report_pwa->Periph.T1) + "ms, ";
   }
   else
   {
        S = "n/c, ";
   }
   if (frm_report_pwa->report_pwa->Periph.T2 < DEFAULT_VALUE)
   {
        S = S + RoundIntToStr(frm_report_pwa->report_pwa->Periph.T2) + "ms, ";
   }
   else
   {
        S = S + "n/c, ";
   }
   if (frm_report_pwa->report_pwa->Periph.AGPH < DEFAULT_VALUE)
   {
        S = S + RoundIntToStr(frm_report_pwa->report_pwa->Periph.AGPH) + "%, ";
   }
   else
   {
        S = S + "n/c, ";
   }
   if (frm_report_pwa->report_pwa->Periph.AI1 < DEFAULT_VALUE)
   {
        S = S + RoundIntToStr(frm_report_pwa->report_pwa->Periph.AI1) + "%";
   }
   else
   {
        S = S + "n/c, ";
   }
   lbl_periph_data->Caption = S;

   // AL
   // This label is not visible in Version 8.0 - 9.0
   if (frm_report_pwa->report_pwa->Central.AL < DEFAULT_VALUE && frm_report_pwa->report_pwa->Central.AL > 0)
   {
      S = RoundIntToStr(frm_report_pwa->report_pwa->Central.AL) + "% (" + RoundIntToStr(frm_report_pwa->report_pwa->Central.ATI) + ")";
   }
   else
   {
      S = "n/c";
   }
   frm_report_pwa->lbl_al->Caption = S;
   Application->ProcessMessages();
}

void Tfrm_report_pwa::report_display_avi(void)
{
   int i;
   int timing_param;
   String S;
   float max_time;
   float min_time;
   float max_central;
   float min_central;
   float min_incident;
   float max_incident;
   float min_reflected;
   float max_reflected;
   float min_flow;
   float max_flow;
   int    ED_index;

   // PM CR
   chrt_avi_avg_central->UndoZoom();
   chrt_avi_flow->UndoZoom();
   chrt_avi_reflected->UndoZoom();
   srs_avi_avg_central->Clear();
   srs_avi_flow->Clear();
   srs_avi_forward->Clear();
   srs_avi_reflected->Clear();
   srs_avi_forward_line->Clear();
   srs_avi_reflected_line->Clear();
   srs_avi_forward_line->Visible = false;
   srs_avi_reflected_line->Visible = false;
   avi_forward_line = false;
   avi_reflected_line = false;

   srs_avi_forward_timing->Clear();
   srs_avi_forward_timing->Pointer->Visible = true;
   srs_avi_forward_timing->Pointer->InflateMargins = true;
   srs_avi_forward_timing->Marks->Visible = false;

   srs_avi_reflected_timing->Clear();
   srs_avi_reflected_timing->Pointer->Visible = true;
   srs_avi_reflected_timing->Pointer->InflateMargins = true;
   srs_avi_reflected_timing->Marks->Visible = false;

   srs_avi_avg_ed->Clear();
   srs_avi_avg_ed->Pointer->InflateMargins = true;

   srs_avi_reflected_ed->Clear();
   srs_avi_reflected_ed->Pointer->InflateMargins = true;

   srs_avi_flow_ed->Clear();
   srs_avi_flow_ed->Pointer->InflateMargins = true;

   // Only display AVI Tabsheet if it has been calculated and enabled
   if (config_get_avi_option() && report_pwa->avi->Aortic_Reflection_Time < DEFAULT_VALUE)
   {
      tbsht_avi->TabVisible = true;
   }
   else
   {
      tbsht_avi->TabVisible = false;
   }

   if (report_pwa->Central.CalAvPulse.Length() < DEFAULT_VALUE)
   {
      for (i = 0; i < report_pwa->Central.CalAvPulse.Length(); i++)
      {
         //float time = ((float) i / 128) * 1000;
         float time = report_pwa->Central.CalAvPulse.IndexToTime(i);
         srs_avi_avg_central->AddXY(time,
                                 report_pwa->Central.CalAvPulse.Profile[i],
                                 "" , clTeeColor);
         srs_avi_flow->AddXY(time,
                                 report_pwa->avi->Flow[i],
                                 "" , clTeeColor);
         srs_avi_forward->AddXY(time,
                                 report_pwa->avi->Forward_Pressure_Final[i],
                                 "" , clTeeColor);
         srs_avi_reflected->AddXY(time,
                                 report_pwa->avi->Backward_Pressure_Final[i],
                                 "" , clTeeColor);
      }
   }

   max_time = REPORT_MAX_TIME;
   min_time = REPORT_MIN_TIME;

   min_central = srs_avi_avg_central->MinYValue();
   max_central = srs_avi_avg_central->MaxYValue();
   min_incident = srs_avi_forward->MinYValue();
   max_incident = srs_avi_forward->MaxYValue();
   min_reflected = srs_avi_reflected->MinYValue();
   max_reflected = srs_avi_reflected->MaxYValue();
   min_flow = srs_avi_flow->MinYValue();
   max_flow = srs_avi_flow->MaxYValue();

   if (max_reflected > max_incident)
   {
      max_incident = max_reflected;
   }
   if (min_reflected < min_incident)
   {
      min_incident = min_reflected;
   }

   min_central = min_central * 0.98;
   max_central = max_central * 1.04;
   min_incident = min_incident * 0.98;
   max_incident = max_incident * 1.04;
   if (min_flow < 0)
   {
      min_flow = min_flow * 1.04;
   }
   else
   {
      min_flow = min_flow * 0.98;
   }
   max_flow = max_flow * 1.04;

   chrt_avi_avg_central->LeftAxis->SetMinMax(min_central, max_central);
   chrt_avi_avg_central->BottomAxis->SetMinMax(min_time, max_time);
   chrt_avi_avg_central->LeftAxis->Increment = 10;
   chrt_avi_avg_central->BottomAxis->Increment = 200;

   chrt_avi_reflected->RightAxis->SetMinMax(min_incident, max_incident);
   chrt_avi_reflected->BottomAxis->SetMinMax(min_time, max_time);
   chrt_avi_reflected->RightAxis->Increment = 10;
   chrt_avi_reflected->BottomAxis->Increment = 200;

   chrt_avi_flow->LeftAxis->SetMinMax(min_flow, max_flow);
   chrt_avi_flow->BottomAxis->SetMinMax(min_time, max_time);
   chrt_avi_flow->LeftAxis->Increment = 5;
   chrt_avi_flow->BottomAxis->Increment = 200;

   timing_param = report_pwa->avi->Forward_Pressure_Max_Time;
   if (timing_param != DEFAULT_VALUE)
   {
      srs_avi_forward_timing->AddXY(report_pwa->avi->Forward_Pressure_Max_Time,
                                 min_incident,
                                 "", clTeeColor);
      srs_avi_forward_timing->AddXY(max_time,
                                 report_pwa->avi->Forward_Pressure_Max,
                                 "", clTeeColor);
      srs_avi_forward_line->AddXY(report_pwa->avi->Forward_Pressure_Max_Time,
                                 min_incident,
                                 "", clTeeColor);
      srs_avi_forward_line->AddXY(report_pwa->avi->Forward_Pressure_Max_Time,
                                 report_pwa->avi->Forward_Pressure_Max,
                                 "", clTeeColor);
      srs_avi_forward_line->AddXY(max_time,
                                 report_pwa->avi->Forward_Pressure_Max,
                                 "", clTeeColor);
   }

   timing_param = report_pwa->avi->Backward_Pressure_Max_Time;
   if (timing_param != DEFAULT_VALUE)
   {
      srs_avi_reflected_timing->AddXY(report_pwa->avi->Backward_Pressure_Max_Time,
                                 min_incident,
                                 "", clTeeColor);
      srs_avi_reflected_timing->AddXY(max_time,
                                 report_pwa->avi->Backward_Pressure_Max,
                                 "", clTeeColor);
      srs_avi_reflected_line->AddXY(report_pwa->avi->Backward_Pressure_Max_Time,
                                 min_incident,
                                 "", clTeeColor);
      srs_avi_reflected_line->AddXY(report_pwa->avi->Backward_Pressure_Max_Time,
                                 report_pwa->avi->Backward_Pressure_Max,
                                 "", clTeeColor);
      srs_avi_reflected_line->AddXY(max_time,
                                 report_pwa->avi->Backward_Pressure_Max,
                                 "", clTeeColor);
   }

   if (report_pwa->Periph.ED != DEFAULT_VALUE)
   {
      ED_index = report_pwa->Central.CalAvPulse.TimeToIndex(report_pwa->Periph.ED);

      if (fabs(report_pwa->Periph.ED - report_pwa->Periph.CalcED) < 0.5)
      {
         srs_avi_avg_ed->Pointer->Style = psDiamond;
         srs_avi_avg_ed->Pointer->Pen->Color = sphygmocor_black;
         srs_avi_avg_ed->Pointer->HorizSize = 3;
         srs_avi_avg_ed->Pointer->VertSize = 3;
         srs_avi_avg_ed->LinePen->Style = psSolid;
         srs_avi_avg_ed->Pointer->Brush->Color = sphygmocor_grey;
         srs_avi_avg_ed->AddXY(report_pwa->Periph.ED,
                                  min_central, "", sphygmocor_grey);

         srs_avi_avg_ed->AddXY(report_pwa->Periph.ED,
                                  report_pwa->Central.ESP,
                                  "", sphygmocor_grey);

         srs_avi_reflected_ed->Pointer->Style = psDiamond;
         srs_avi_reflected_ed->Pointer->Pen->Color = sphygmocor_black;
         srs_avi_reflected_ed->Pointer->HorizSize = 3;
         srs_avi_reflected_ed->Pointer->VertSize = 3;
         srs_avi_reflected_ed->LinePen->Style = psSolid;
         srs_avi_reflected_ed->Pointer->Brush->Color = sphygmocor_grey;
         srs_avi_reflected_ed->AddXY(report_pwa->Periph.ED,
                                  min_incident, "", sphygmocor_grey);

         srs_avi_reflected_ed->AddXY(report_pwa->Periph.ED,
                                  report_pwa->avi->Forward_Pressure_Final[ED_index],
                                  "", sphygmocor_grey);

         srs_avi_flow_ed->Pointer->Style = psDiamond;
         srs_avi_flow_ed->Pointer->Pen->Color = sphygmocor_black;
         srs_avi_flow_ed->Pointer->HorizSize = 3;
         srs_avi_flow_ed->Pointer->VertSize = 3;
         srs_avi_flow_ed->Pointer->Brush->Color = sphygmocor_grey;
         srs_avi_flow_ed->AddXY(report_pwa->Periph.ED,
                                  0, "", sphygmocor_grey);
      }
      else
      {
         srs_avi_avg_ed->Pointer->Style = psCircle;
         srs_avi_avg_ed->Pointer->Pen->Color = sphygmocor_pink;
         srs_avi_avg_ed->LinePen->Style = psDot;
         srs_avi_avg_ed->Pointer->HorizSize = 2;
         srs_avi_avg_ed->Pointer->VertSize = 2;
         srs_avi_avg_ed->Pointer->Brush->Color = sphygmocor_pink;
         srs_avi_avg_ed->AddXY(report_pwa->Periph.ED,
                            min_central, "", sphygmocor_pink);
         srs_avi_avg_ed->AddXY(report_pwa->Periph.ED,
                            report_pwa->Central.ESP,
                            "", sphygmocor_pink);

         srs_avi_reflected_ed->Pointer->Style = psCircle;
         srs_avi_reflected_ed->Pointer->Pen->Color = sphygmocor_pink;
         srs_avi_reflected_ed->LinePen->Style = psDot;
         srs_avi_reflected_ed->Pointer->HorizSize = 2;
         srs_avi_reflected_ed->Pointer->VertSize = 2;
         srs_avi_reflected_ed->Pointer->Brush->Color = sphygmocor_pink;
         srs_avi_reflected_ed->AddXY(report_pwa->Periph.ED,
                                  min_incident, "", sphygmocor_pink);

         srs_avi_reflected_ed->AddXY(report_pwa->Periph.ED,
                                  report_pwa->avi->Forward_Pressure_Final[ED_index],
                                  "", sphygmocor_pink);

         srs_avi_flow_ed->Pointer->Style = psCircle;
         srs_avi_flow_ed->Pointer->Pen->Color = sphygmocor_pink;
         srs_avi_flow_ed->Pointer->HorizSize = 2;
         srs_avi_flow_ed->Pointer->VertSize = 2;
         srs_avi_flow_ed->Pointer->Brush->Color = sphygmocor_pink;
         srs_avi_flow_ed->AddXY(report_pwa->Periph.ED,
                            0, "", sphygmocor_pink);
      }
   }

   //APTT
   if (report_pwa->avi->Aortic_Reflection_Time < DEFAULT_VALUE)
   {
      S =  RoundIntToStr(report_pwa->avi->Aortic_Reflection_Time) + " ms";
   }
   else
   {
      S = "n/c";
   }
   lbl_avi_aptt->Caption = S;

   //IPPH
   if (report_pwa->avi->Forward_Pressure_Height < DEFAULT_VALUE)
   {
      S =  RoundIntToStr(report_pwa->avi->Forward_Pressure_Height) + " mmHg";
   }
   else
   {
      S = "n/c";
   }
   lbl_avi_ipph->Caption = S;

   //IPPT
   if (report_pwa->avi->Forward_Pressure_Max_Time < DEFAULT_VALUE)
   {
      S =  RoundIntToStr(report_pwa->avi->Forward_Pressure_Max_Time) + " ms";
   }
   else
   {
      S = "n/c";
   }
   lbl_avi_ippt->Caption = S;

   //RPPH
   if (report_pwa->avi->Backward_Pressure_Height < DEFAULT_VALUE)
   {
      S =  RoundIntToStr(report_pwa->avi->Backward_Pressure_Height) + " mmHg";
   }
   else
   {
      S = "n/c";
   }
   lbl_avi_rpph->Caption = S;

   //RPPT
   if (report_pwa->avi->Backward_Pressure_Max_Time < DEFAULT_VALUE)
   {
      S =  RoundIntToStr(report_pwa->avi->Backward_Pressure_Max_Time) + " ms";
   }
   else
   {
      S = "n/c";
   }
   lbl_avi_rppt->Caption = S;

   //RI
   if (report_pwa->avi->Reflection_Index < DEFAULT_VALUE)
   {
      S =  RoundIntToStr(report_pwa->avi->Reflection_Index) + "%";
   }
   else
   {
      S = "n/c";
   }
   lbl_avi_ri->Caption = S;

   //AD
   if (report_pwa->avi->Aortic_Distance < DEFAULT_VALUE)
   {
      S =  RoundIntToStr(report_pwa->avi->Aortic_Distance) + " mm";
   }
   else
   {
      S = "n/c";
   }
   lbl_avi_distance->Caption = S;

   //CFTT
   if (report_pwa->avi->Carotid_Femoral_Transmission_Time < DEFAULT_VALUE)
   {
      S =  RoundIntToStr(report_pwa->avi->Carotid_Femoral_Transmission_Time) + " ms";
   }
   else
   {
      S = "n/c";
   }
   lbl_avi_cftt->Caption = S;

   //SVI
   if (report_pwa->avi->SphygmoCor_Velocity_Index < DEFAULT_VALUE)
   {
      S =  FormatFloat("#0.0", report_pwa->avi->SphygmoCor_Velocity_Index) + " m/s";
   }
   else
   {
      S = "n/c";
   }
   lbl_avi_pwv->Caption = S; 
}
//---------------------------------------------------------------------------
void __fastcall Tfrm_report_pwa::FormKeyPress(TObject *Sender, char &Key)
{
   if (Key == VK_ESCAPE)
   {
      frm_main->spdbtn_patientClick(Sender);
   }
}

//---------------------------------------------------------------------------

void __fastcall Tfrm_report_pwa::lbl_ed_titleDblClick(TObject *Sender)
{
   // If the audit option is set, ED cannot be changed
   if (config_get_audit_option() && study_mode == MEAS_PWA_ID)
   {
      MsgBox(TNOTIFICATION,
            MSG_AUDIT,
            MSG_AUDIT_MODE,
            LoadStr(MSG_AUDIT_MODE));
      return;
   }
   if (frm_report_pwa->report_pwa->Central.ED < DEFAULT_VALUE)
   {
      tbar_change_ed->Visible = true;
      btn_move_ed_accept->Enabled = false;
      btn_move_ed_cancel->Enabled = false;
   }
}
//---------------------------------------------------------------------------
void __fastcall Tfrm_report_pwa::btn_move_ed_leftClick(TObject *Sender)
{
   int EDIndex = report_pwa->Periph.ExpPulse.TimeToIndex(report_pwa->Periph.ED);
   // Get and check next index
   int NextIndex = EDIndex - 2;
   bool AllowMoveLeft, AllowMoveRight;
   if (report_pwa->CheckEDLimitations(NextIndex, AllowMoveLeft, AllowMoveRight)==false)
   {
      btn_move_ed_right->Enabled = false;
      btn_move_ed_left->Enabled = false;
      return;
   }
   btn_move_ed_left->Enabled = AllowMoveLeft;
   btn_move_ed_right->Enabled = AllowMoveRight;
   // Decrement
   if (AllowMoveLeft == true)
   {
     report_pwa->RecalculateEDDependants(NextIndex);
     report_display_ed();
     report_display_central_params();
     report_display_avi();
     btn_move_ed_accept->Enabled = true;
     btn_move_ed_cancel->Enabled = true;
   }
}
//---------------------------------------------------------------------------
void __fastcall Tfrm_report_pwa::btn_move_ed_rightClick(TObject *Sender)
{
   int EDIndex = report_pwa->Periph.ExpPulse.TimeToIndex(report_pwa->Periph.ED);
   // Get and check next index
   int NextIndex = EDIndex + 2;
   bool AllowMoveLeft, AllowMoveRight;
   if (report_pwa->CheckEDLimitations(NextIndex, AllowMoveLeft, AllowMoveRight)==false)
   {
      btn_move_ed_right->Enabled = false;
      btn_move_ed_left->Enabled = false;
      return;
   }
   btn_move_ed_left->Enabled = AllowMoveLeft;
   btn_move_ed_right->Enabled = AllowMoveRight;
   // Decrement
   if (AllowMoveRight == true)
   {
     report_pwa->RecalculateEDDependants(NextIndex);
     report_display_ed();
     report_display_central_params();
     report_display_avi();
     btn_move_ed_accept->Enabled = true;
     btn_move_ed_cancel->Enabled = true;
   }
}
//---------------------------------------------------------------------------
void __fastcall Tfrm_report_pwa::btn_move_ed_cancelClick(TObject *Sender)
{
   tbar_change_ed->Visible = false;
   record_changed(Sender, NULL);
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_report_pwa::btn_move_ed_acceptClick(TObject *Sender)
{
   // Disable OnChange event to protect rewriting PWA
   grd_report->DataSource->OnDataChange = NULL;

  // Try to store parameters into database
   report_qry->Edit();

   if (report_pwa->Store(report_qry, false, false) == false)
   {
      // "Error storing measurememt parameters"
      report_qry->Cancel();
      grd_report->DataSource->OnDataChange = record_changed;
      return;
   }
   
   // Restore OnChange event
   grd_report->DataSource->OnDataChange = record_changed;

   // Refresh grid and charts
   record_changed(Sender, NULL);
   tbar_change_ed->Visible = false;
   /*if (grd_report->Visible)
   {
      grd_report->SetFocus();
   }*/
}
//---------------------------------------------------------------------------



void __fastcall Tfrm_report_pwa::chrt_avg_periphClickSeries(
      TCustomChart *Sender, TChartSeries *Series, int ValueIndex,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
   TPointSeries *point_series;

   point_series = dynamic_cast<TPointSeries *>(Series);

   if (point_series == srs_avg_ptiming)
   {
      lbl_pavg_val->Caption = RoundIntToStr(point_series->XValues->Value[ValueIndex]);
      lbl_pavg_val->Transparent = false;
   }
}
//---------------------------------------------------------------------------


void __fastcall Tfrm_report_pwa::chrt_avg_centralClickSeries(
      TCustomChart *Sender, TChartSeries *Series, int ValueIndex,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
   TPointSeries *point_series;

   point_series = dynamic_cast<TPointSeries *>(Series);

   if (point_series == srs_avg_t1_timing || point_series == srs_avg_t2_timing)
   {
      if (point_series->XValues->Value[ValueIndex] == REPORT_MAX_TIME)
      {
         lbl_cavg_val->Caption = RoundIntToStr(point_series->YValues->Value[ValueIndex]);
      }
      else
      {
         lbl_cavg_val->Caption = RoundIntToStr(point_series->XValues->Value[ValueIndex]);
      }
      lbl_cavg_val->Transparent = false;
   }
}
//---------------------------------------------------------------------------
// PM CR
void __fastcall Tfrm_report_pwa::mnu_graphicClick(TObject *Sender)
{
   Graphics::TBitmap*   bmp_image;
   PATIENT_RECORD_TYPE  pat;
   String               reptype_str = "CLINIC_";
   String               attach_fname;

   try
   {
      // PM V9
      // Display the status bar messages on the report form for the exported graphic
      pnl_status_bar->Visible = true;
      pnl_report_buttons->Visible = false;
      lbl_message1->Caption = frm_main->lbl_message1->Caption;
      lbl_message2->Caption = frm_main->lbl_message2->Caption;
      lbl_message3->Caption = frm_main->lbl_message3->Caption;
      lbl_message4->Caption = frm_main->lbl_message4->Caption;
      lbl_message1->Font->Color = frm_main->lbl_message1->Font->Color;
      lbl_message2->Font->Color = frm_main->lbl_message2->Font->Color;
      lbl_message3->Font->Color = frm_main->lbl_message3->Font->Color;
      lbl_message4->Font->Color = frm_main->lbl_message4->Font->Color;
      bmp_image = GetFormImage();
      if (bmp_image != NULL)
      {
         if (patient_get(&pat))
         {
            if (pgctrl_reports->ActivePage == tbsht_detailed)
            {
               reptype_str = "DETAIL_";
            }
            else if (pgctrl_reports->ActivePage == tbsht_reference)
            {
               reptype_str = "CLASSIFICATION_";
            }
            else if (pgctrl_reports->ActivePage == tbsht_avi)
            {
               reptype_str = "WR_";
            }

            // PM V9
            // If the EMR patient is active or default EMR mode is set - get the
            // export directory from the EMR object
            if (emr_patient_is_active() || emr_get_default_mode())
            {
               attach_fname = emr_get_outbound() + "PIC_" +reptype_str +pat.surname +"_"
                           +report_pwa->DateTime.FormatString("ddmmmyyyy-hhmmss") +export_file +".jpg";
            }
            else
            {
               attach_fname = ExtractFilePath(Application->ExeName) +EXPORT_SUBDIR +"PIC_" +reptype_str +pat.surname +"_"
                           +report_pwa->DateTime.FormatString("ddmmmyyyy-hhmmss") +export_file +".jpg";
            }

            // If successful, notify the EMR object
            if (export_graphic(bmp_image, attach_fname))
            {
               emr_export();
            }
         }
         delete bmp_image;
      }
   }
   catch (...)
   {
      (void)MsgBox_warning("Could Not Create Graphic.",
                           SWARNING);
   }

   pnl_report_buttons->Visible = true;
   pnl_status_bar->Visible = false;
   //grd_report->SetFocus();
}

void __fastcall Tfrm_report_pwa::mnu_textClick(TObject *Sender)
{
   PATIENT_RECORD_TYPE  pat;
   String               lFileName;

   if (patient_get(&pat))
   {
      // PM V9
      // If the EMR patient is active or default EMR mode is set - get the
      // export directory from the EMR object
      if (emr_patient_is_active() || emr_get_default_mode())
      {
         lFileName = emr_get_outbound() + pat.surname + "_"
                  + report_pwa->DateTime.FormatString("ddmmmyyyy-hhmmss") +export_file +".txt";
      }
      else
      {
         lFileName = ExtractFilePath(Application->ExeName) + EXPORT_SUBDIR + pat.surname + "_"
                  + report_pwa->DateTime.FormatString("ddmmmyyyy-hhmmss") +export_file +".txt";
      }

      // If successful, notify the EMR object
      if (export_measurement(grd_report->DataSource->DataSet,
                         lFileName,
                         frm_report_pwa->report_pwa,
                         pwm_session_id))
      {
         emr_export();
      }
   }
}
//---------------------------------------------------------------------------


void __fastcall Tfrm_report_pwa::pnl_canvasResize(TObject *Sender)
{
   pnl_waveform->Height = pnl_canvas->Height/5;

}
//---------------------------------------------------------------------------



void __fastcall Tfrm_report_pwa::pnl_chp_bottomResize(TObject *Sender)
{
   pnl_left->Width = pnl_chp_bottom->Width/3;
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_report_pwa::srs_ap_hr75_pointGetMarkText(
      TChartSeries *Sender, int ValueIndex, AnsiString &MarkText)
{
   MarkText = "HR75";
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_report_pwa::srs_augidx_hr75_pointGetMarkText(
      TChartSeries *Sender, int ValueIndex, AnsiString &MarkText)
{
   MarkText = "HR75";
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_report_pwa::chrt_avg_central_periphMouseDown(
      TObject *Sender, TMouseButton Button, TShiftState Shift, int X,
      int Y)
{
   if (chrt_avg_central_periph->Zoomed)
   {
      chrt_avg_central_periph->Series[0]->Marks->Arrow->Color = sphygmocor_white;
      chrt_avg_central_periph->Series[0]->Marks->Visible = true;
   }
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_report_pwa::chrt_avg_central_periphMouseUp(
      TObject *Sender, TMouseButton Button, TShiftState Shift, int X,
      int Y)
{
   chrt_avg_central_periph->Series[0]->Marks->Visible = false;
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_report_pwa::chrt_avg_central_periphZoom(
      TObject *Sender)
{
   TCustomSeries *series;
   int           time_len;

   chrt_avg_central_periph->ClipPoints = true;
   time_len = chrt_avg_central_periph->BottomAxis->Maximum - chrt_avg_central_periph->BottomAxis->Minimum;

   if (time_len < 100)
   {
      series = dynamic_cast<TCustomSeries *>(chrt_avg_central_periph->Series[0]);
      if (series)
      {
         series->Pointer->Visible = true;
      }
      chrt_avg_central_periph->BottomAxis->Increment = 10;
   }
   else if (time_len > 100 && time_len < 250)
   {
      chrt_avg_central_periph->BottomAxis->Increment = 50;
   }
   else if (time_len > 250 && time_len < 500)
   {
      chrt_avg_central_periph->BottomAxis->Increment = 100;
   }
   else if (time_len > 500 && time_len < 750)
   {
      chrt_avg_central_periph->BottomAxis->Increment = 150;
   }
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_report_pwa::chrt_avg_central_periphUndoZoom(
      TObject *Sender)
{
   TCustomSeries *series;
   TCustomSeries *series2;

   chrt_avg_central_periph->ClipPoints = false;

   series = dynamic_cast<TCustomSeries *>(chrt_avg_central_periph->Series[0]);
   if (series)
   {
      series->Pointer->Visible = false;
   }
   chrt_avg_central_periph->BottomAxis->Increment = 200;
}
//---------------------------------------------------------------------------


void __fastcall Tfrm_report_pwa::srs_avg_clinical_centralGetMarkText(
      TChartSeries *Sender, int ValueIndex, AnsiString &MarkText)
{
   int  point_count;
   int  point_num = 6;
   point_count = srs_avg_clinical_central->LastValueIndex - srs_avg_clinical_central->FirstValueIndex;

   if (point_count > 2 * point_num)
   {
      point_count = point_count / point_num;
   }
   else if (point_count <= point_num)
   {
      point_count = 1;
   }
   else
   {
      point_count = 2;
   }

   if ((ValueIndex - srs_avg_clinical_central->FirstValueIndex + int(point_count/2))%point_count)
   {
      MarkText = "";
   }
   else
   {
      MarkText = FormatFloat("0.0", srs_avg_clinical_central->YValues->Value[ValueIndex]);
   }
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_report_pwa::chrt_avg_central_periphMouseMove(
      TObject *Sender, TShiftState Shift, int X, int Y)
{
   /*
   ** PCH This function is no longer required in the clinicians screen
   ** Leave here for now in case required later
   long int in_region = -1;

   in_region = srs_avg_clinical_central->Clicked(X,Y);

   // Making the label transparent ensures the Pulse Pressures can be seen in
   // 600x800 resolution
   if (in_region != -1)
   {
      lbl_avg_val->Caption = FormatFloat("0.0", srs_avg_clinical_central->YValues->Value[in_region]);
      lbl_avg_val->Transparent = false;
   }
   else
   {
      lbl_avg_val->Caption = "";
      lbl_avg_val->Transparent = true;
   }
   */
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_report_pwa::lbl_clinical_csp_titleClick(
      TObject *Sender)
{
   chrt_sevr_flow_reference->Visible = false;
   chrt_sp_reference->Parent = pnl_reference_main;
   chrt_sp_reference->Hint = REFERENCE_RETURN;
   chrt_pp_reference->Parent = pnl_reference_one;
   chrt_pp_reference->Hint = REFERENCE_ENLARGE;
   chrt_ap_reference->Parent = pnl_reference_two;
   chrt_ap_reference->Hint = REFERENCE_ENLARGE;
   chrt_augidx_reference->Parent = pnl_reference_three;
   chrt_augidx_reference->Hint = REFERENCE_ENLARGE;
   chrt_ed_reference->Parent = pnl_reference_four;
   chrt_ed_reference->Hint = REFERENCE_ENLARGE;
   chrt_sevr_reference->Parent = pnl_reference_five;
   chrt_sevr_reference->Hint = REFERENCE_ENLARGE;
   pgctrl_reports->ActivePage = tbsht_reference;
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_report_pwa::tbsht_referenceResize(TObject *Sender)
{
   int width = tbsht_reference->Width / 3;
   int height = tbsht_reference->Height / 3;

   chrt_sevr_flow_reference->Height = height;
   pnl_reference_one->Height = height;
   pnl_reference_four->Width = width;
   pnl_reference_five->Width = width;
   pnl_reference_bottom->Height = height;
   pnl_reference_left->Width = width;
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_report_pwa::lbl_clinical_cpp_titleClick(
      TObject *Sender)
{
   chrt_sevr_flow_reference->Visible = false;
   chrt_pp_reference->Parent = pnl_reference_main;
   chrt_pp_reference->Hint = REFERENCE_RETURN;
   chrt_sp_reference->Parent = pnl_reference_one;
   chrt_sp_reference->Hint = REFERENCE_ENLARGE;
   chrt_ap_reference->Parent = pnl_reference_two;
   chrt_ap_reference->Hint = REFERENCE_ENLARGE;
   chrt_augidx_reference->Parent = pnl_reference_three;
   chrt_augidx_reference->Hint = REFERENCE_ENLARGE;
   chrt_ed_reference->Parent = pnl_reference_four;
   chrt_ed_reference->Hint = REFERENCE_ENLARGE;
   chrt_sevr_reference->Parent = pnl_reference_five;
   chrt_sevr_reference->Hint = REFERENCE_ENLARGE;
   pgctrl_reports->ActivePage = tbsht_reference;
}
//---------------------------------------------------------------------------


void __fastcall Tfrm_report_pwa::lbl_clinical_aixhr75_titleClick(
      TObject *Sender)
{
   chrt_sevr_flow_reference->Visible = false;
   chrt_augidx_reference->Parent = pnl_reference_main;
   chrt_augidx_reference->Hint = REFERENCE_RETURN;
   chrt_sp_reference->Parent = pnl_reference_one;
   chrt_sp_reference->Hint = REFERENCE_ENLARGE;
   chrt_pp_reference->Parent = pnl_reference_two;
   chrt_pp_reference->Hint = REFERENCE_ENLARGE;
   chrt_ap_reference->Parent = pnl_reference_three;
   chrt_ap_reference->Hint = REFERENCE_ENLARGE;
   chrt_ed_reference->Parent = pnl_reference_four;
   chrt_ed_reference->Hint = REFERENCE_ENLARGE;
   chrt_sevr_reference->Parent = pnl_reference_five;
   chrt_sevr_reference->Hint = REFERENCE_ENLARGE;
   pgctrl_reports->ActivePage = tbsht_reference;
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_report_pwa::lbl_clinical_ap_titleClick(
      TObject *Sender)
{
   chrt_sevr_flow_reference->Visible = false;
   chrt_ap_reference->Parent = pnl_reference_main;
   chrt_ap_reference->Hint = REFERENCE_RETURN;
   chrt_sp_reference->Parent = pnl_reference_one;
   chrt_sp_reference->Hint = REFERENCE_ENLARGE;
   chrt_pp_reference->Parent = pnl_reference_two;
   chrt_pp_reference->Hint = REFERENCE_ENLARGE;
   chrt_augidx_reference->Parent = pnl_reference_three;
   chrt_augidx_reference->Hint = REFERENCE_ENLARGE;
   chrt_ed_reference->Parent = pnl_reference_four;
   chrt_ed_reference->Hint = REFERENCE_ENLARGE;
   chrt_sevr_reference->Parent = pnl_reference_five;
   chrt_sevr_reference->Hint = REFERENCE_ENLARGE;
   pgctrl_reports->ActivePage = tbsht_reference;
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_report_pwa::lbl_clinical_ed_titleClick(
      TObject *Sender)
{
   chrt_sevr_flow_reference->Visible = false;
   chrt_ed_reference->Parent = pnl_reference_main;
   chrt_ed_reference->Hint = REFERENCE_RETURN;
   chrt_sp_reference->Parent = pnl_reference_one;
   chrt_sp_reference->Hint = REFERENCE_ENLARGE;
   chrt_pp_reference->Parent = pnl_reference_two;
   chrt_pp_reference->Hint = REFERENCE_ENLARGE;
   chrt_ap_reference->Parent = pnl_reference_three;
   chrt_ap_reference->Hint = REFERENCE_ENLARGE;
   chrt_augidx_reference->Parent = pnl_reference_four;
   chrt_augidx_reference->Hint = REFERENCE_ENLARGE;
   chrt_sevr_reference->Parent = pnl_reference_five;
   chrt_sevr_reference->Hint = REFERENCE_ENLARGE;
   pgctrl_reports->ActivePage = tbsht_reference;
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_report_pwa::lbl_clinical_sevr_titleClick(
      TObject *Sender)
{
   chrt_sevr_flow_reference->Visible = true;
   chrt_sevr_reference->Parent = pnl_reference_main;
   chrt_sevr_reference->Hint = REFERENCE_RETURN;
   chrt_sp_reference->Parent = pnl_reference_one;
   chrt_sp_reference->Hint = REFERENCE_ENLARGE;
   chrt_pp_reference->Parent = pnl_reference_two;
   chrt_pp_reference->Hint = REFERENCE_ENLARGE;
   chrt_ap_reference->Parent = pnl_reference_three;
   chrt_ap_reference->Hint = REFERENCE_ENLARGE;
   chrt_augidx_reference->Parent = pnl_reference_four;
   chrt_augidx_reference->Hint = REFERENCE_ENLARGE;
   chrt_ed_reference->Parent = pnl_reference_five;
   chrt_ed_reference->Hint = REFERENCE_ENLARGE;
   pgctrl_reports->ActivePage = tbsht_reference;
}
//---------------------------------------------------------------------------


void __fastcall Tfrm_report_pwa::chrt_sp_referenceClick(TObject *Sender)
{
   if (chrt_sp_reference->Parent == pnl_reference_main)
   {
      pgctrl_reports->ActivePage = tbsht_clinical;
   }
   else
   {
      lbl_clinical_csp_titleClick(Sender);
   }
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_report_pwa::chrt_pp_referenceClick(TObject *Sender)
{
   if (chrt_pp_reference->Parent == pnl_reference_main)
   {
      pgctrl_reports->ActivePage = tbsht_clinical;
   }
   else
   {
      lbl_clinical_cpp_titleClick(Sender);
   }
}
//---------------------------------------------------------------------------


void __fastcall Tfrm_report_pwa::chrt_augidx_referenceClick(
      TObject *Sender)
{
   if (chrt_augidx_reference->Parent == pnl_reference_main)
   {
      pgctrl_reports->ActivePage = tbsht_clinical;
   }
   else
   {
      lbl_clinical_aixhr75_titleClick(Sender);
   }
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_report_pwa::chrt_ap_referenceClick(TObject *Sender)
{
   if (chrt_ap_reference->Parent == pnl_reference_main)
   {
      pgctrl_reports->ActivePage = tbsht_clinical;
   }
   else
   {
      lbl_clinical_ap_titleClick(Sender);
   }
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_report_pwa::chrt_ed_referenceClick(TObject *Sender)
{
   if (chrt_ed_reference->Parent == pnl_reference_main)
   {
      pgctrl_reports->ActivePage = tbsht_clinical;
   }
   else
   {
      lbl_clinical_ed_titleClick(Sender);
   }
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_report_pwa::chrt_sevr_referenceClick(TObject *Sender)
{
   if (chrt_sevr_reference->Parent == pnl_reference_main)
   {
      pgctrl_reports->ActivePage = tbsht_clinical;
   }
   else
   {
      lbl_clinical_sevr_titleClick(Sender);
   }
}
//---------------------------------------------------------------------------
bool report_recalculate_all(TObject *Sender)
{
   String S;
   float Aortic_Distance;  

   S = frm_report_pwa->lbl_pname->Caption;
   if (frm_report_pwa->report_qry != NULL)
   {
      if (frm_report_pwa->report_qry->RecordCount)
      {
         if (MsgBox(LoadStr(MSG_UPDATE_ALL) + S + "\n\n" + LoadStr(MSG_ARE_YOU_SURE),
            SCONFIRMATION, MB_YESNO | MB_ICONWARNING) == ID_YES)
         {

            // Disable OnChange event
            frm_report_pwa->grd_report->DataSource->OnDataChange = NULL;

            // Call recalculate form
            bool ret = meas_recalculate_show_form(frm_report_pwa,
                                         frm_report_pwa->report_pwa,
                                         frm_report_pwa->report_qry,
                                         frm_report_pwa->lbl_pname->Caption,
                                         AUDIT_NORMAL, MEAS_DISTANCE);
            if (ret && frm_report_pwa->report_qry->RecordCount > 1)
            {
               Aortic_Distance = frm_report_pwa->report_pwa->avi->Aortic_Distance;

               frm_report_pwa->report_qry->First();
               // Skip the first report as the recalculate form does it
               frm_report_pwa->report_qry->Next();
               for (int i = 1; i < frm_report_pwa->report_qry->RecordCount; i++)
               {
                  if (frm_report_pwa->report_pwa->Populate(frm_report_pwa->report_qry))
                  {
                     if (frm_report_pwa->report_pwa->avi->Aortic_Distance == DEFAULT_VALUE)
                     {
                        frm_report_pwa->report_pwa->avi->Aortic_Distance = Aortic_Distance;
                     }
                     // Try to recalculate parameters
                     if (frm_report_pwa->report_pwa->Calculate())
                     {
                        // Try to store parameters into database
                        frm_report_pwa->report_qry->Edit();

                        if (frm_report_pwa->report_pwa->Store(frm_report_pwa->report_qry, false, false) == false)
                        {
                           // "Error storing measurememt parameters"
                           frm_report_pwa->report_qry->Cancel();
                           frm_report_pwa->grd_report->DataSource->OnDataChange = frm_report_pwa->record_changed;
                           return false;
                        }
                     }
                     else
                     {
                        // "Error calculating measurememt parameters",
                        MsgBox_show(TWARNING,
                                    MSG_MATH_ERROR,
                                    LoadStr(MSG_MEAS_ERROR_CALC),
                                    MSG_MEAS_ERROR_CALC, "");
                     }
                  }
                  frm_report_pwa->report_qry->Next();
                  Application->ProcessMessages();
               }
            }
         }
      }
   }
   // Restore OnChange event
   frm_report_pwa->grd_report->DataSource->OnDataChange = frm_report_pwa->record_changed;

   // Refresh grid and charts
   frm_report_pwa->record_changed(Sender, NULL);
   /*if (frm_report_pwa->grd_report->Visible)
   {
      frm_report_pwa->grd_report->SetFocus();
   }*/
   return true;
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_report_pwa::pnl_avi_graphsResize(TObject *Sender)
{
   pnl_avi_left->Width = pnl_avi_graphs->Width * 3 / 8;
   pnl_centre_avi_graphs->Width = pnl_avi_graphs->Width / 4;
   //chrt_avi_flow->Height = pnl_centre_avi_graphs->Height * 3 / 5;
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_report_pwa::chrt_avi_avg_centralZoom(TObject *Sender)
{
   TCustomSeries *series;
   int           time_len;

   chrt_avi_avg_central->ClipPoints = true;
   time_len = chrt_avi_avg_central->BottomAxis->Maximum - chrt_avi_avg_central->BottomAxis->Minimum;

   if (time_len < 100)
   {
      series = dynamic_cast<TCustomSeries *>(chrt_avi_avg_central->Series[0]);
      if (series)
      {
         series->Pointer->Visible = true;
      }
      chrt_avi_avg_central->BottomAxis->Increment = 10;
   }
   else if (time_len > 100 && time_len < 250)
   {
      chrt_avi_avg_central->BottomAxis->Increment = 50;
   }
   else if (time_len > 250 && time_len < 500)
   {
      chrt_avi_avg_central->BottomAxis->Increment = 100;
   }
   else if (time_len > 500 && time_len < 750)
   {
      chrt_avi_avg_central->BottomAxis->Increment = 150;
   }
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_report_pwa::chrt_avi_avg_centralUndoZoom(
      TObject *Sender)
{
   TCustomSeries *series;

   chrt_avi_avg_central->ClipPoints = false;

   series = dynamic_cast<TCustomSeries *>(chrt_avi_avg_central->Series[0]);
   if (series)
   {
      series->Pointer->Visible = false;
   }
   chrt_avi_avg_central->BottomAxis->Increment = 200;
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_report_pwa::chrt_avi_avg_centralMouseDown(
      TObject *Sender, TMouseButton Button, TShiftState Shift, int X,
      int Y)
{
   if (chrt_avi_avg_central->Zoomed)
   {
      chrt_avi_avg_central->Series[0]->Marks->Arrow->Color = sphygmocor_white;
      chrt_avi_avg_central->Series[0]->Marks->Visible = true;
   }   
}
//---------------------------------------------------------------------------
void __fastcall Tfrm_report_pwa::chrt_avi_avg_centralMouseUp(
      TObject *Sender, TMouseButton Button, TShiftState Shift, int X,
      int Y)
{
   chrt_avi_avg_central->Series[0]->Marks->Visible = false;
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_report_pwa::srs_avi_avg_centralGetMarkText(
      TChartSeries *Sender, int ValueIndex, AnsiString &MarkText)
{
   int  point_count;
   int  point_num = 6;
   point_count = srs_avi_avg_central->LastValueIndex - srs_avi_avg_central->FirstValueIndex;

   if (point_count > 2 * point_num)
   {
      point_count = point_count / point_num;
   }
   else if (point_count <= point_num)
   {
      point_count = 1;
   }
   else
   {
      point_count = 2;
   }

   if ((ValueIndex - srs_avi_avg_central->FirstValueIndex + int(point_count/2))%point_count)
   {
      MarkText = "";
   }
   else
   {
      MarkText = FormatFloat("0.0", srs_avi_avg_central->YValues->Value[ValueIndex]);
   }
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_report_pwa::chrt_avi_reflectedZoom(TObject *Sender)
{
   TCustomSeries *series;
   TCustomSeries *series2;
   int           time_len;

   chrt_avi_reflected->ClipPoints = true;
   time_len = chrt_avi_reflected->BottomAxis->Maximum - chrt_avi_reflected->BottomAxis->Minimum;

   if (time_len < 100)
   {
      series = dynamic_cast<TCustomSeries *>(chrt_avi_reflected->Series[0]);
      if (series)
      {
         series->Pointer->Visible = true;
      }
      series2 = dynamic_cast<TCustomSeries *>(chrt_avi_reflected->Series[1]);
      if (series2)
      {
         series2->Pointer->Visible = true;
      }
      chrt_avi_reflected->BottomAxis->Increment = 10;
   }
   else if (time_len > 100 && time_len < 250)
   {
      chrt_avi_reflected->BottomAxis->Increment = 50;
   }
   else if (time_len > 250 && time_len < 500)
   {
      chrt_avi_reflected->BottomAxis->Increment = 100;
   }
   else if (time_len > 500 && time_len < 750)
   {
      chrt_avi_reflected->BottomAxis->Increment = 150;
   }
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_report_pwa::chrt_avi_reflectedUndoZoom(
      TObject *Sender)
{
   TCustomSeries *series;
   TCustomSeries *series2;

   chrt_avi_reflected->ClipPoints = false;

   series = dynamic_cast<TCustomSeries *>(chrt_avi_reflected->Series[0]);
   if (series)
   {
      series->Pointer->Visible = false;
   }
   series2 = dynamic_cast<TCustomSeries *>(chrt_avi_reflected->Series[1]);
   if (series2)
   {
      series2->Pointer->Visible = false;
   }
   chrt_avi_reflected->BottomAxis->Increment = 200;
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_report_pwa::chrt_avi_reflectedMouseDown(
      TObject *Sender, TMouseButton Button, TShiftState Shift, int X,
      int Y)
{
   if (chrt_avi_reflected->Zoomed)
   {
      chrt_avi_reflected->Series[0]->Marks->Arrow->Color = sphygmocor_white;
      chrt_avi_reflected->Series[0]->Marks->Visible = true;
      chrt_avi_reflected->Series[1]->Marks->Arrow->Color = sphygmocor_white;
      chrt_avi_reflected->Series[1]->Marks->Visible = true;
   }
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_report_pwa::chrt_avi_reflectedMouseUp(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
   chrt_avi_reflected->Series[0]->Marks->Visible = false;
   chrt_avi_reflected->Series[1]->Marks->Visible = false;
}
//---------------------------------------------------------------------------


void __fastcall Tfrm_report_pwa::srs_avi_forwardGetMarkText(
      TChartSeries *Sender, int ValueIndex, AnsiString &MarkText)
{
   int  point_count;
   int  point_num = 6;
   point_count = srs_avi_forward->LastValueIndex - srs_avi_forward->FirstValueIndex;

   if (point_count > 2 * point_num)
   {
      point_count = point_count / point_num;
   }
   else if (point_count <= point_num)
   {
      point_count = 1;
   }
   else
   {
      point_count = 2;
   }

   if ((ValueIndex - srs_avi_forward->FirstValueIndex + int(point_count/2))%point_count)
   {
      MarkText = "";
   }
   else
   {
      MarkText = FormatFloat("0.0", srs_avi_forward->YValues->Value[ValueIndex]);
   }
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_report_pwa::srs_avi_reflectedGetMarkText(
      TChartSeries *Sender, int ValueIndex, AnsiString &MarkText)
{
   int  point_count;
   int  point_num = 6;
   point_count = srs_avi_reflected->LastValueIndex - srs_avi_reflected->FirstValueIndex;

   if (point_count > 2 * point_num)
   {
      point_count = point_count / point_num;
   }
   else if (point_count <= point_num)
   {
      point_count = 1;
   }
   else
   {
      point_count = 2;
   }

   if ((ValueIndex - srs_avi_reflected->FirstValueIndex + int(point_count/2))%point_count)
   {
      MarkText = "";
   }
   else
   {
      MarkText = FormatFloat("0.0", srs_avi_reflected->YValues->Value[ValueIndex]);
   }
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_report_pwa::chrt_avi_flowZoom(TObject *Sender)
{
   TCustomSeries *series;
   int           time_len;

   chrt_avi_flow->ClipPoints = true;
   time_len = chrt_avi_flow->BottomAxis->Maximum - chrt_avi_flow->BottomAxis->Minimum;

   if (time_len < 100)
   {
      series = dynamic_cast<TCustomSeries *>(chrt_avi_flow->Series[0]);
      if (series)
      {
         series->Pointer->Visible = true;
      }
      chrt_avi_flow->BottomAxis->Increment = 10;
   }
   else if (time_len > 100 && time_len < 250)
   {
      chrt_avi_flow->BottomAxis->Increment = 50;
   }
   else if (time_len > 250 && time_len < 500)
   {
      chrt_avi_flow->BottomAxis->Increment = 100;
   }
   else if (time_len > 500 && time_len < 750)
   {
      chrt_avi_flow->BottomAxis->Increment = 150;
   }
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_report_pwa::chrt_avi_flowUndoZoom(TObject *Sender)
{
   TCustomSeries *series;

   chrt_avi_flow->ClipPoints = false;

   series = dynamic_cast<TCustomSeries *>(chrt_avi_flow->Series[0]);
   if (series)
   {
      series->Pointer->Visible = false;
   }
   chrt_avi_flow->BottomAxis->Increment = 200;
}
//---------------------------------------------------------------------------


void __fastcall Tfrm_report_pwa::srs_avi_reflected_timingGetMarkText(
      TChartSeries *Sender, int ValueIndex, AnsiString &MarkText)
{
   if (ValueIndex == 0)
   {
      MarkText = RoundIntToStr(srs_avi_reflected_timing->XValues->Value[ValueIndex]);
   }
   else
   {
      MarkText = RoundIntToStr(srs_avi_reflected_timing->YValues->Value[ValueIndex]);
   }
}
//---------------------------------------------------------------------------



void __fastcall Tfrm_report_pwa::srs_avi_reflected_timingClick(
      TChartSeries *Sender, int ValueIndex, TMouseButton Button,
      TShiftState Shift, int X, int Y)
{
   if (avi_reflected_line)
   {
      srs_avi_reflected_line->Visible = false;
      srs_avi_reflected_timing->Marks->Visible = false;
      avi_reflected_line = false;
   }
   else
   {
      srs_avi_reflected_line->Visible = true;
      srs_avi_reflected_timing->Marks->Visible = true;
      avi_reflected_line = true;
   }
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_report_pwa::lbl_avi_rpph_titleClick(TObject *Sender)
{
   if (avi_reflected_line)
   {
      srs_avi_reflected_line->Visible = false;
      srs_avi_reflected_timing->Marks->Visible = false;
      avi_reflected_line = false;
   }
   else
   {
      srs_avi_reflected_line->Visible = true;
      srs_avi_reflected_timing->Marks->Visible = true;
      avi_reflected_line = true;
   }   
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_report_pwa::lbl_avi_rppt_titleClick(TObject *Sender)
{
   if (avi_reflected_line)
   {
      srs_avi_reflected_line->Visible = false;
      srs_avi_reflected_timing->Marks->Visible = false;
      avi_reflected_line = false;
   }
   else
   {
      srs_avi_reflected_line->Visible = true;
      srs_avi_reflected_timing->Marks->Visible = true;
      avi_reflected_line = true;
   }   
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_report_pwa::lbl_avi_ipph_titleClick(TObject *Sender)
{
   if (avi_forward_line)
   {
      srs_avi_forward_line->Visible = false;
      srs_avi_forward_timing->Marks->Visible = false;
      avi_forward_line = false;
   }
   else
   {
      srs_avi_forward_line->Visible = true;
      srs_avi_forward_timing->Marks->Visible = true;
      avi_forward_line = true;
   }
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_report_pwa::lbl_avi_ippt_titleClick(TObject *Sender)
{
   if (avi_forward_line)
   {
      srs_avi_forward_line->Visible = false;
      srs_avi_forward_timing->Marks->Visible = false;
      avi_forward_line = false;
   }
   else
   {
      srs_avi_forward_line->Visible = true;
      srs_avi_forward_timing->Marks->Visible = true;
      avi_forward_line = true;
   }   
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_report_pwa::srs_avi_forward_timingClick(
      TChartSeries *Sender, int ValueIndex, TMouseButton Button,
      TShiftState Shift, int X, int Y)
{
   if (avi_forward_line)
   {
      srs_avi_forward_line->Visible = false;
      srs_avi_forward_timing->Marks->Visible = false;
      avi_forward_line = false;
   }
   else
   {
      srs_avi_forward_line->Visible = true;
      srs_avi_forward_timing->Marks->Visible = true;
      avi_forward_line = true;
   }
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_report_pwa::srs_avi_forward_timingGetMarkText(
      TChartSeries *Sender, int ValueIndex, AnsiString &MarkText)
{
   if (ValueIndex == 0)
   {
      MarkText = RoundIntToStr(srs_avi_forward_timing->XValues->Value[ValueIndex]);
   }
   else
   {
      MarkText = RoundIntToStr(srs_avi_forward_timing->YValues->Value[ValueIndex]);
   }
}
//---------------------------------------------------------------------------


void __fastcall Tfrm_report_pwa::srs_avg_t1_timingClick(TChartSeries *Sender,
      int ValueIndex, TMouseButton Button, TShiftState Shift, int X, int Y)
{
   if (t1_line)
   {
      srs_avg_t1->Visible = false;
      srs_avg_t1_timing->Marks->Visible = false;
      t1_line = false;
   }
   else
   {
      srs_avg_t1->Visible = true;
      srs_avg_t1_timing->Marks->Visible = true;
      t1_line = true;
   }
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_report_pwa::lbl_t1t2_titleClick(TObject *Sender)
{
   if (t1_line && t2_line)
   {
      srs_avg_t1->Visible = false;
      srs_avg_t2->Visible = false;
      t1_line = false;
      t2_line = false;
      srs_avg_t1_timing->Marks->Visible = false;
      srs_avg_t2_timing->Marks->Visible = false;
   }
   else
   {
      srs_avg_t1->Visible = true;
      srs_avg_t2->Visible = true;
      t1_line = true;
      t2_line = true;
      srs_avg_t1_timing->Marks->Visible = true;
      srs_avg_t2_timing->Marks->Visible = true;
   }
}
//---------------------------------------------------------------------------


void __fastcall Tfrm_report_pwa::FormKeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
   if (Shift.Contains(ssAlt) && Key == 'X')
   {
      TPoint point = bbtn_export->ClientOrigin;
      int X = point.x;
      int Y = point.y + bbtn_export->Height;

      ppmnu_report->Popup(X, Y);
   }
}
//---------------------------------------------------------------------------


void __fastcall Tfrm_report_pwa::srs_avg_t2_timingClick(
      TChartSeries *Sender, int ValueIndex, TMouseButton Button,
      TShiftState Shift, int X, int Y)
{
   if (t2_line)
   {
      srs_avg_t2->Visible = false;
      srs_avg_t2_timing->Marks->Visible = false;
      t2_line = false;
   }
   else
   {
      srs_avg_t2->Visible = true;
      srs_avg_t2_timing->Marks->Visible = true;
      t2_line = true;
   }
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_report_pwa::srs_avg_t2_timingGetMarkText(
      TChartSeries *Sender, int ValueIndex, AnsiString &MarkText)
{
   if (ValueIndex == 0)
   {
      MarkText = RoundIntToStr(srs_avg_t2_timing->XValues->Value[ValueIndex]);
   }
   else
   {
      MarkText = RoundIntToStr(srs_avg_t2_timing->YValues->Value[ValueIndex]);
   }
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_report_pwa::lbl_t1t2_titleDblClick(TObject *Sender)
{
   // If the audit option is set, T1 and T2 cannot be changed
   if (config_get_audit_option() && study_mode == MEAS_PWA_ID)
   {
      MsgBox(TNOTIFICATION,
            MSG_AUDIT,
            MSG_AUDIT_MODE,
            LoadStr(MSG_AUDIT_MODE));
      return;
   }
   if (report_pwa->Central.T1 < DEFAULT_VALUE || report_pwa->Central.T2 < DEFAULT_VALUE)
   {
      tbar_change_t1t2->Visible = true;
      srs_avg_t1->Visible = true;
      srs_avg_t2->Visible = true;
      t1_line = true;
      t2_line = true;
      srs_avg_t1_timing->Marks->Visible = true;
      srs_avg_t2_timing->Marks->Visible = true;
      btn_move_t1_accept->Enabled = false;
      btn_move_t1_cancel->Enabled = false;
      btn_move_t2_accept->Enabled = false;
      btn_move_t2_cancel->Enabled = false;
   }
   if (report_pwa->Central.T1 < DEFAULT_VALUE)
   {
      btn_move_t1_left->Enabled = true;
      btn_move_t1_right->Enabled = true;
   }
   else
   {
      btn_move_t1_left->Enabled = false;
      btn_move_t1_right->Enabled = false;
   }
   if (report_pwa->Central.T2 < DEFAULT_VALUE)
   {
      btn_move_t2_left->Enabled = true;
      btn_move_t2_right->Enabled = true;
   }
   else
   {
      btn_move_t2_left->Enabled = false;
      btn_move_t2_right->Enabled = false;
   }
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_report_pwa::btn_move_t1_leftClick(TObject *Sender)
{
   int T1Index = report_pwa->Central.ExpPulse.TimeToIndex(report_pwa->Central.T1);
   // Get and check next index
   int NextIndex = T1Index - 2;
   bool AllowMoveLeft, AllowMoveRight;
   if (report_pwa->CheckT1Limitations(NextIndex, AllowMoveLeft, AllowMoveRight)==false)
   {
      btn_move_t1_right->Enabled = false;
      btn_move_t1_left->Enabled = false;
      return;
   }
   btn_move_t1_left->Enabled = AllowMoveLeft;
   btn_move_t1_right->Enabled = AllowMoveRight;
   // Decrement
   if (AllowMoveLeft == true)
   {
     report_pwa->RecalculateT1Dependants(NextIndex);
     report_display_t1();
     report_display_ap();
     report_display_central_params();
     report_display_avi();
     btn_move_t1_accept->Enabled = true;
     btn_move_t1_cancel->Enabled = true;
   }
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_report_pwa::btn_move_t1_rightClick(TObject *Sender)
{
   int T1Index = report_pwa->Central.ExpPulse.TimeToIndex(report_pwa->Central.T1);
   // Get and check next index
   int NextIndex = T1Index + 2;
   bool AllowMoveLeft, AllowMoveRight;
   if (report_pwa->CheckT1Limitations(NextIndex, AllowMoveLeft, AllowMoveRight)==false)
   {
      btn_move_t1_right->Enabled = false;
      btn_move_t1_left->Enabled = false;
      return;
   }
   btn_move_t1_left->Enabled = AllowMoveLeft;
   btn_move_t1_right->Enabled = AllowMoveRight;
   // Increment
   if (AllowMoveRight == true)
   {
     report_pwa->RecalculateT1Dependants(NextIndex);
     report_display_t1();
     report_display_ap();
     report_display_central_params();
     report_display_avi();
     btn_move_t1_accept->Enabled = true;
     btn_move_t1_cancel->Enabled = true;
   }
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_report_pwa::btn_move_t1_acceptClick(TObject *Sender)
{
   // Disable OnChange event to protect rewriting PWA
   grd_report->DataSource->OnDataChange = NULL;

  // Try to store parameters into database
   report_qry->Edit();

   if (report_pwa->Store(report_qry, false, false) == false)
   {
      // "Error storing measurememt parameters"
      report_qry->Cancel();
      grd_report->DataSource->OnDataChange = record_changed;
      return;
   }

   // Restore OnChange event
   grd_report->DataSource->OnDataChange = record_changed;

   // Refresh grid and charts
   record_changed(Sender, NULL);
   tbar_change_t1t2->Visible = false;
   /*if (grd_report->Visible)
   {
      grd_report->SetFocus();
   }*/
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_report_pwa::btn_move_t1_cancelClick(TObject *Sender)
{
   tbar_change_t1t2->Visible = false;
   record_changed(Sender, NULL);
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_report_pwa::btn_move_t2_leftClick(TObject *Sender)
{
   int T2Index = report_pwa->Central.ExpPulse.TimeToIndex(report_pwa->Central.T2);
   // Get and check next index
   int NextIndex = T2Index - 2;
   bool AllowMoveLeft, AllowMoveRight;
   if (report_pwa->CheckT2Limitations(NextIndex, AllowMoveLeft, AllowMoveRight)==false)
   {
      btn_move_t2_right->Enabled = false;
      btn_move_t2_left->Enabled = false;
      return;
   }
   btn_move_t2_left->Enabled = AllowMoveLeft;
   btn_move_t2_right->Enabled = AllowMoveRight;
   // Decrement
   if (AllowMoveLeft == true)
   {
     report_pwa->RecalculateT2Dependants(NextIndex);
     report_display_t2();
     report_display_ap();
     report_display_central_params();
     btn_move_t2_accept->Enabled = true;
     btn_move_t2_cancel->Enabled = true;
   }
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_report_pwa::btn_move_t2_rightClick(TObject *Sender)
{
   int T2Index = report_pwa->Central.ExpPulse.TimeToIndex(report_pwa->Central.T2);
   // Get and check next index
   int NextIndex = T2Index + 2;
   bool AllowMoveLeft, AllowMoveRight;
   if (report_pwa->CheckT2Limitations(NextIndex, AllowMoveLeft, AllowMoveRight)==false)
   {
      btn_move_t2_right->Enabled = false;
      btn_move_t2_left->Enabled = false;
      return;
   }
   btn_move_t2_left->Enabled = AllowMoveLeft;
   btn_move_t2_right->Enabled = AllowMoveRight;
   // Increment
   if (AllowMoveRight == true)
   {
     report_pwa->RecalculateT2Dependants(NextIndex);
     report_display_t2();
     report_display_ap();
     report_display_central_params();
     btn_move_t2_accept->Enabled = true;
     btn_move_t2_cancel->Enabled = true;
   }
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_report_pwa::btn_move_t2_acceptClick(TObject *Sender)
{
   // Disable OnChange event to protect rewriting PWA
   grd_report->DataSource->OnDataChange = NULL;

  // Try to store parameters into database
   report_qry->Edit();

   if (report_pwa->Store(report_qry, false, false) == false)
   {
      // "Error storing measurememt parameters"
      report_qry->Cancel();
      grd_report->DataSource->OnDataChange = record_changed;
      return;
   }

   // Restore OnChange event
   grd_report->DataSource->OnDataChange = record_changed;

   // Refresh grid and charts
   record_changed(Sender, NULL);
   tbar_change_t1t2->Visible = false;
   /*if (grd_report->Visible)
   {
      grd_report->SetFocus();
   }*/
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_report_pwa::btn_move_t2_cancelClick(TObject *Sender)
{
   tbar_change_t1t2->Visible = false;
   record_changed(Sender, NULL);
}
// PM V9
//---------------------------------------------------------------------------
/* ###########################################################################
// Perform an Export All according to the options set in the EMR object
*/
void __fastcall Tfrm_report_pwa::mnu_allClick(TObject *Sender)
{
   Graphics::TBitmap*   bmp_image;
   TTabSheet            *previous;
   String               filename;
   String               outbound_directory;
   PATIENT_RECORD_TYPE  pat;
   bool                 success = true;
   int                  page_count;
   String               retype_str;
   bool                 first_time = true;

   if (emr_get_enabled())
   {
      outbound_directory = emr_get_outbound();
      if (patient_get(&pat) && outbound_directory != "")
      {
         // Display the status bar messages on the report form for the exported graphic
         Screen->Cursor = crHourGlass;
         pnl_status_bar->Visible = true;
         pnl_report_buttons->Visible = false;
         lbl_message1->Caption = frm_main->lbl_message1->Caption;
         lbl_message2->Caption = frm_main->lbl_message2->Caption;
         lbl_message3->Caption = frm_main->lbl_message3->Caption;
         lbl_message4->Caption = frm_main->lbl_message4->Caption;
         lbl_message1->Font->Color = frm_main->lbl_message1->Font->Color;
         lbl_message2->Font->Color = frm_main->lbl_message2->Font->Color;
         lbl_message3->Font->Color = frm_main->lbl_message3->Font->Color;
         lbl_message4->Font->Color = frm_main->lbl_message4->Font->Color;
         // There is only one report to export in Clinical Mode
         if (config_get_clinical_option())
         {
            switch (emr_get_option())
            {
               // Exports the Clinical Report graphic and the text file
               case EMR_STANDARD:
               case EMR_CLINICAL:
               case EMR_DETAILED:
                  try
                  {
                     bmp_image = GetFormImage();
                     if (bmp_image != NULL)
                     {
                        filename = outbound_directory + "PIC_CLINIC_" + pat.surname + "_"
                                 + report_pwa->DateTime.FormatString("ddmmmyyyy-hhmmss") + export_file + ".jpg";
                        if (report_export_graphic(bmp_image, filename) == false)
                        {
                           success = false;
                        }
                        delete bmp_image;
                     }

                     filename = outbound_directory + pat.surname + "_"
                              + report_pwa->DateTime.FormatString("ddmmmyyyy-hhmmss") + export_file + ".txt";
                     if (report_export_measurement(filename) == false)
                     {
                        success = false;
                     }
                  }
                  catch (...)
                  {
                     (void)MsgBox_warning("Could Not Create Graphic.", SWARNING);
                     success = false;
                  }
                  break;

               // Exports the Clinical Report to pdf and the text file
               case EMR_ALL_PDF:
               case EMR_CLINICAL_PDF:
               case EMR_DETAILED_PDF:
                  pdf_file = "REPORT_CLINIC_" + pat.surname + "_"
                           + report_pwa->DateTime.FormatString("ddmmmyyyy-hhmmss") + export_file;
                  if (report_export_pdf() == false)
                  {
                     success = false;
                  }

                  filename = outbound_directory + pat.surname + "_"
                           + report_pwa->DateTime.FormatString("ddmmmyyyy-hhmmss") + export_file + ".txt";
                  if (report_export_measurement(filename) == false)
                  {
                     success = false;
                  }
                  break;

               // All option exports the Clinical Report as a graphic and pdf, plus the text file
               case EMR_ALL:
                  try
                  {
                     pdf_file = "REPORT_CLINIC_" + pat.surname + "_"
                              + report_pwa->DateTime.FormatString("ddmmmyyyy-hhmmss") + export_file;
                     if (report_export_pdf() == false)
                     {
                        success = false;
                     }

                     bmp_image = GetFormImage();
                     if (bmp_image != NULL)
                     {
                        filename = outbound_directory + "PIC_CLINIC_" + pat.surname + "_"
                                 + report_pwa->DateTime.FormatString("ddmmmyyyy-hhmmss") + export_file + ".jpg";
                        if (report_export_graphic(bmp_image, filename) == false)
                        {
                           success = false;
                        }
                        delete bmp_image;
                     }

                     filename = outbound_directory + pat.surname + "_"
                              + report_pwa->DateTime.FormatString("ddmmmyyyy-hhmmss") + export_file + ".txt";
                     if (report_export_measurement(filename) == false)
                     {
                        success = false;
                     }
                  }
                  catch (...)
                  {
                     (void)MsgBox_warning("Could Not Create Graphic.", SWARNING);
                     success = false;
                  }
                  break;
            }
         }
         else
         {
            previous = pgctrl_reports->ActivePage;
            switch (emr_get_option())
            {
               // Standard option exports all 3 graphics and the text file
               case EMR_STANDARD:
                  try
                  {
                     page_count = pgctrl_reports->PageCount;
                     for (int i = 0; i < page_count; i++)
                     {
                        pgctrl_reports->ActivePageIndex = i;
                        // The tabsheet hints contain the export prefixes
                        // So DO NOT change tabsheet hints!!!
                        retype_str = pgctrl_reports->ActivePage->Hint;
                        if (retype_str == "WR")
                        {
                           break;
                        }
                        bmp_image = GetFormImage();
                        if (bmp_image != NULL)
                        {
                           filename = outbound_directory + "PIC_" + retype_str + "_" + pat.surname + "_"
                                    + report_pwa->DateTime.FormatString("ddmmmyyyy-hhmmss") + export_file + ".jpg";
                           if (report_export_graphic(bmp_image, filename) == false)
                           {
                              success = false;
                           }
                           delete bmp_image;
                        }
                     }

                     filename = outbound_directory + pat.surname + "_"
                              + report_pwa->DateTime.FormatString("ddmmmyyyy-hhmmss") + export_file + ".txt";
                     if (report_export_measurement(filename) == false)
                     {
                        success = false;
                     }
                  }
                  catch (...)
                  {
                     (void)MsgBox_warning("Could Not Create Graphic.", SWARNING);
                     success = false;
                  }
                  break;

               // Clinical option exports the Clinical Report graphic and the text file
               case EMR_CLINICAL:
                  try
                  {
                     pgctrl_reports->ActivePage = tbsht_clinical;
                     bmp_image = GetFormImage();
                     if (bmp_image != NULL)
                     {
                        filename = outbound_directory + "PIC_CLINIC_" + pat.surname + "_"
                                 + report_pwa->DateTime.FormatString("ddmmmyyyy-hhmmss") + export_file + ".jpg";
                        if (report_export_graphic(bmp_image, filename) == false)
                        {
                           success = false;
                        }
                        delete bmp_image;
                     }

                     filename = outbound_directory + pat.surname + "_"
                              + report_pwa->DateTime.FormatString("ddmmmyyyy-hhmmss") + export_file + ".txt";
                     if (report_export_measurement(filename) == false)
                     {
                        success = false;
                     }
                  }
                  catch (...)
                  {
                     (void)MsgBox_warning("Could Not Create Graphic.", SWARNING);
                     success = false;
                  }
                  break;

               // Detailed option exports the Detailed Report graphic and the text file
               case EMR_DETAILED:
                  try
                  {
                     pgctrl_reports->ActivePage = tbsht_detailed;
                     bmp_image = GetFormImage();
                     if (bmp_image != NULL)
                     {
                        filename = outbound_directory + "PIC_DETAIL_" + pat.surname + "_"
                                 + report_pwa->DateTime.FormatString("ddmmmyyyy-hhmmss") + export_file + ".jpg";
                        if (report_export_graphic(bmp_image, filename) == false)
                        {
                           success = false;
                        }
                        delete bmp_image;
                     }

                     filename = outbound_directory + pat.surname + "_"
                              + report_pwa->DateTime.FormatString("ddmmmyyyy-hhmmss") + export_file + ".txt";
                     if (report_export_measurement(filename) == false)
                     {
                        success = false;
                     }
                  }
                  catch (...)
                  {
                     (void)MsgBox_warning("Could Not Create Graphic.", SWARNING);
                     success = false;
                  }
                  break;

               // All pdf option exports all 3 reports to pdf and the text file
               case EMR_ALL_PDF:
                  page_count = pgctrl_reports->PageCount;
                  for (int i = 0; i < page_count; i++)
                  {
                     pgctrl_reports->ActivePageIndex = i;
                     // The tabsheet hints contain the export prefixes
                     // So DO NOT change tabsheet hints!!!
                     retype_str = pgctrl_reports->ActivePage->Hint;
                     if (retype_str == "WR")
                     {
                        break;
                     }
                     // The first time after starting Windows that Adobe attempts to
                     // print consecutive reports, it will freeze because it needs time
                     // to setup. Adding a sleep in between printing reports fixes this.
                     if (first_time)
                     {
                        // A sleep is not necessary before the first report
                        first_time = false;
                     }
                     else
                     {
                        Sleep(3000);
                     }
                     pdf_file = "REPORT_" + retype_str + "_" + pat.surname + "_"
                                 + report_pwa->DateTime.FormatString("ddmmmyyyy-hhmmss") + export_file;
                     if (report_export_pdf() == false)
                     {
                        success = false;
                     }
                  }

                  filename = outbound_directory + pat.surname + "_"
                           + report_pwa->DateTime.FormatString("ddmmmyyyy-hhmmss") + export_file + ".txt";
                  if (report_export_measurement(filename) == false)
                  {
                     success = false;
                  }
                  break;

               // Clinical pdf option exports the Clinical Report to pdf and the text file
               case EMR_CLINICAL_PDF:
                  pgctrl_reports->ActivePage = tbsht_clinical;
                  pdf_file = "REPORT_CLINIC_" + pat.surname + "_"
                           + report_pwa->DateTime.FormatString("ddmmmyyyy-hhmmss") + export_file;
                  if (report_export_pdf() == false)
                  {
                     success = false;
                  }

                  filename = outbound_directory + pat.surname + "_"
                           + report_pwa->DateTime.FormatString("ddmmmyyyy-hhmmss") + export_file + ".txt";
                  if (report_export_measurement(filename) == false)
                  {
                     success = false;
                  }
                  break;

               // Detailed pdf exports the Detailed Report to pdf and the text file
               case EMR_DETAILED_PDF:
                  pgctrl_reports->ActivePage = tbsht_detailed;
                  pdf_file = "REPORT_DETAIL_" + pat.surname + "_"
                           + report_pwa->DateTime.FormatString("ddmmmyyyy-hhmmss") + export_file;
                  if (report_export_pdf() == false)
                  {
                     success = false;
                  }

                  filename = outbound_directory + pat.surname + "_"
                           + report_pwa->DateTime.FormatString("ddmmmyyyy-hhmmss") + export_file + ".txt";
                  if (report_export_measurement(filename) == false)
                  {
                     success = false;
                  }
                  break;

               // All option exports all 3 reports as graphics and pdf, plus the text file
               case EMR_ALL:
                  try
                  {
                     page_count = pgctrl_reports->PageCount;
                     for (int i = 0; i < page_count; i++)
                     {
                        pgctrl_reports->ActivePageIndex = i;
                        // The tabsheet hints contain the export prefixes
                        // So DO NOT change tabsheet hints!!!
                        retype_str = pgctrl_reports->ActivePage->Hint;
                        if (retype_str == "WR")
                        {
                           break;
                        }
                        // The first time after starting Windows that Adobe attempts to
                        // print consecutive reports, it will freeze because it needs time
                        // to setup. Adding a sleep in between printing reports fixes this.
                        if (first_time)
                        {
                           // A sleep is not necessary before the first report
                           first_time = false;
                        }
                        else
                        {
                           Sleep(3000);
                        }
                        pdf_file = "REPORT_" + retype_str + "_" + pat.surname + "_"
                                    + report_pwa->DateTime.FormatString("ddmmmyyyy-hhmmss") + export_file;
                        if (report_export_pdf() == false)
                        {
                           success = false;
                        }

                        bmp_image = GetFormImage();
                        if (bmp_image != NULL)
                        {
                           filename = outbound_directory + "PIC_" + retype_str + "_" + pat.surname + "_"
                                    + report_pwa->DateTime.FormatString("ddmmmyyyy-hhmmss") + export_file + ".jpg";
                           if (report_export_graphic(bmp_image, filename) == false)
                           {
                              success = false;
                           }
                           delete bmp_image;
                        }
                     }

                     filename = outbound_directory + pat.surname + "_"
                              + report_pwa->DateTime.FormatString("ddmmmyyyy-hhmmss") + export_file + ".txt";
                     if (report_export_measurement(filename) == false)
                     {
                        success = false;
                     }
                  }
                  catch (...)
                  {
                     (void)MsgBox_warning("Could Not Create Graphic.", SWARNING);
                     success = false;
                  }
                  break;
            }
            pgctrl_reports->ActivePage = previous;
         }
         pnl_report_buttons->Visible = true;
         pnl_status_bar->Visible = false;
         Screen->Cursor = crDefault;

         // If successful, notify the user and the EMR object
         if (success)
         {
            MsgBox_information("Files successfully exported to: " + outbound_directory, "Export All Successful");
            emr_export();
         }
         else
         {
            MsgBox_information("Some files were not exported successfully", "Export All Failed");
         }
      }
   }
}
// PM V9
/* ###########################################################################
// Exports the graphic bmp_image to the file jpeg_file_name without requiring
// user confirmation
*/
bool Tfrm_report_pwa::report_export_graphic(Graphics::TBitmap*   bmp_image,
                                                  String jpeg_file_name)
{
   bool         created = false;
   TJPEGImage*  jpg_image;

   Application->ProcessMessages();
   jpg_image = new TJPEGImage();
   if (jpg_image)
   {
      jpg_image->CompressionQuality = 75;
      jpg_image->Performance = jpBestSpeed;
      jpg_image->PixelFormat = jf24Bit;
      jpg_image->Smoothing = false;
      jpg_image->Assign(bmp_image);
      jpg_image->SaveToFile(jpeg_file_name);
      created = true;
      delete jpg_image;
      jpg_image = (TJPEGImage *)0;
   }
   return created;
}
// PM V9
/* ###########################################################################
// Exports the current PWA report as a text file to filename without requiring
// user confirmation
*/
bool Tfrm_report_pwa::report_export_measurement(String filename)
{
   int      lFileHandle;
   String   lOut = "";

   // Create the file
   if (FileExists(filename))
   {
      DeleteFile(filename);
   }
   lFileHandle = FileCreate(filename);
   if (lFileHandle <= 0)
   {
      MsgBox(TERROR, MSG_EXPORT_ERROR, MSG_EXPORT_ERROR_FILE, LoadStr(MSG_EXPORT_ERROR_FILE) + filename);
      return false;
   }

   Application->ProcessMessages();

   // Export the titles
   if (report_pwa->ExportPrintTitle(grd_report->DataSource->DataSet, lOut) == false)
   {
      return false;
   }

   lOut = lOut + "\r\n";
   FileWrite(lFileHandle, lOut.c_str(), lOut.Length());
   Application->ProcessMessages();

   // Export the parameters
   lOut = "";
   if (pwm_session_id == 0)
   {
      if (report_pwa->Export(lOut)== false)
      {
         return false;
      }
   }
   else
   {
      if (report_pwa->Export(lOut, pwm_session_id) == false)
      {
         return false;
      }
   }
   lOut = lOut + "\r\n\r\n";
   FileWrite(lFileHandle, lOut.c_str(), lOut.Length());

   // Export the Arrays
   if (report_pwa->ExportArrays(lFileHandle) == false)
   {
      return false;
   }

   FileClose(lFileHandle);
   return true;
}
// PM V9
/* ###########################################################################
// Exports the current PWA report as a pdf file without requiring user confirmation
*/
bool Tfrm_report_pwa::report_export_pdf()
{
   TPrinter *printer_ptr;
   int      index;
   bool     success = false;
   String   pdf_printer;

   Application->ProcessMessages();
   //Application->HandleMessage();

   printer_ptr = print_get_printer_ptr();
   if (printer_ptr == NULL)
   {
      return false;
   }

   // Get the printer from the EMR object
   pdf_printer = emr_get_printer();
   index = printer_ptr->Printers->IndexOf(pdf_printer);
   
   if (index >=0)
   {
      printer_ptr->PrinterIndex = index;

      // Then call the print function
      bbtn_printClick(this);
      Screen->Cursor = crHourGlass;
      success = true;
   }
   else
   {
      MsgBox_show(TERROR,
                  MSG_EMR_ERROR,
                  "The Printer: " + pdf_printer + LoadStr(MSG_EMR_PDF_ERROR),
                  MSG_EMR_PDF_ERROR,
                  "The Printer: " + pdf_printer + LoadStr(MSG_EMR_PDF_ERROR));
      success = false;
   }

   return success;
}



void __fastcall Tfrm_report_pwa::tbsht_detailedShow(TObject *Sender)
{
   // This should not be executed before the first FormShow
   if (!pwa_first_time)
   {
      chrt_pulse_overlay->Parent = pnl_qc_pulse_overlay_back;
   }
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_report_pwa::tbsht_clinicalShow(TObject *Sender)
{
   // This should not be executed before the first FormShow
   if (!pwa_first_time)
   {
      chrt_pulse_overlay->Parent = pnl_operator_index;
   }
}
//---------------------------------------------------------------------------
// PM V9
bool report_pwa_repeat_assessment(void)
{
   if (report_repeat_assessment)
   {
      report_repeat_assessment = false;
      return true;
   }
   else
   {
      return false;
   }
}
void __fastcall Tfrm_report_pwa::bbtn_deleteClick(TObject *Sender)
{
   AnsiString S;

   S = lbl_pname->Caption;
   if (report_qry != NULL)
   {
      if (MsgBox(LoadStr(MSG_DELETE_MEAS2) + S + "\n\n" + LoadStr(MSG_ARE_YOU_SURE),
          SCONFIRMATION, MB_YESNO | MB_ICONWARNING) == ID_YES)
      {
         // The operator must sign in to delete a record
         if(audit_pwa_delete())
         {
            try
            {
               // If the audit option is set, reports are never deleted
               // Instead, the audit flag is set to DELETED
               if (!config_get_audit_option() || study_mode == MEAS_PWM_ID)
               {
                  report_qry->Delete();
               }
            }
            catch (...)
            {
               return;
            }

            if (report_qry->RecordCount == 0)
            {
               MsgBox(MSG_NO_REPORTS_TO_DISPLAY, SNOTIFICATION, MB_ICONINFORMATION);
               patient_update_measurement_count(0);
               multdb_set_delete_status(false);
               Hide();
               frm_main->spdbtn_patientClick(Sender);
            }
            else
            {
               patient_update_measurement_count((short)(report_qry->RecordCount));
            }
         }
      }
   }   
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_report_pwa::bbtn_printClick(TObject *Sender)
{
   int                  report_width;
   int                  report_height;
   int                  left_margin;
   int                  ypos;
   int                  index;
   TLineSeries          *srs;
   TRect                print_rect;
   TPrinterOrientation  old_orient;
   TPrinter             *printer_ptr;
   AnsiString           S;

   if (this->Visible)
   {
      // PM V9
      // Do not ask for user confirmation when printing to pdf
      if (pdf_file == "")
      {
         if (MsgBox(MSG_PRINT_REPORT, CONFIRMATION, MB_YESNO | MB_ICONQUESTION) != ID_YES)
         {
            /*if (grd_report->Visible)
            {
               grd_report->SetFocus();
            }*/
            return;
         }
      }
   }

   printer_ptr = print_get_printer_ptr();
   if (printer_ptr == NULL)
   {
      return;
   }

   Screen->Cursor = crHourGlass;
   old_orient = printer_ptr->Orientation;
   printer_ptr->Orientation  = poPortrait;

   // PM V9
   // Set the title for pdf reports
   if (pdf_file == "")
   {
      printer_ptr->Title = "SphygmoCor PWA Report";
   }
   else
   {
      printer_ptr->Title = pdf_file;
      pdf_file = "";
   }
   try
   {
       // PM CR
       chrt_avg_periph->UndoZoom();
       chrt_avg_central->UndoZoom();
       chrt_pulse_periph->UndoZoom();
       chrt_pulse_central->UndoZoom();
       chrt_pulse_overlay->UndoZoom();
       chrt_avg_central_periph->UndoZoom();
       chrt_avi_avg_central->UndoZoom();
       chrt_avi_flow->UndoZoom();
       chrt_avi_reflected->UndoZoom();

       index = chrt_pulse_overlay->SeriesCount() - 1;
       while (index >= 0)
       {
          srs = (TLineSeries *)chrt_pulse_overlay->Series[index];
          srs->ColorRange(srs->XValues,
                             srs->MinXValue(),
                             srs->MaxXValue(),
                             sphygmocor_black);
          index--;
       }

       printer_ptr->BeginDoc();

       report_width =  printer_ptr->PageWidth;
       report_width = report_width - (report_width * 0.02);
       report_height = printer_ptr->PageHeight;
       left_margin = report_width * 0.06;

       print_rect.Top = report_height * 0.92;
       print_rect.Left = left_margin;
       print_rect.Right = report_width;
       print_rect.Bottom = report_height;
       print_report_footer(&print_rect);

       if (pgctrl_reports->ActivePage == tbsht_detailed)
       {
          print_rect.Top = report_height * 0.80;
          print_rect.Left = left_margin;
          print_rect.Right = report_width;
          print_rect.Bottom = report_height * 0.9;
          print_report_central_params(printer_ptr, &print_rect);
       }
       else if (pgctrl_reports->ActivePage == tbsht_clinical)
       {
          print_rect.Top = report_height * 0.60;
          print_rect.Left = left_margin;
          print_rect.Right = report_width;
          print_rect.Bottom = report_height * 0.92;
          print_report_clinical_central_params(printer_ptr, &print_rect);
       }
       else if (pgctrl_reports->ActivePage == tbsht_avi)
       {
          print_rect.Top = report_height * 0.65;
          print_rect.Left = left_margin;
          print_rect.Right = report_width;
          print_rect.Bottom = report_height * 0.95;
          print_report_avi_params(printer_ptr, &print_rect);
       }


       print_rect.Top = report_height * 0.1;
       print_rect.Left = left_margin;
       print_rect.Right = report_width;
       print_rect.Bottom = report_height * 0.15;
       print_report_header(&print_rect);
       print_do_atcor_image(&print_rect);

       print_rect.Top = print_rect.Bottom;
       print_rect.Left = left_margin;
       print_rect.Right = report_width;
       print_rect.Bottom = report_height * 0.22;
       print_report_patient(&print_rect);

       if (pgctrl_reports->ActivePage == tbsht_detailed)
       {
          print_rect.Top = report_height * 0.43;
          print_rect.Left = left_margin + (report_width - left_margin) * 0.44;
          print_rect.Right = left_margin + (report_width - left_margin) * 0.56;
          print_rect.Bottom = report_height * 0.78;
          print_report_pressures(printer_ptr, &print_rect, true);
       }

       print_rect.Top = report_height * 0.23;
       print_rect.Left = left_margin;
       print_rect.Right = report_width;
       print_rect.Bottom = report_height * 0.46;
       ypos = print_report_study(printer_ptr, &print_rect);

       if (pgctrl_reports->ActivePage == tbsht_detailed)
       {
          print_rect.Top = ypos;
          print_rect.Left = left_margin;
          print_rect.Right = report_width;
          print_rect.Bottom = report_height * 0.40;
          print_report_qc(printer_ptr, &print_rect);

          // Set the charts to the size displayed in 600x800 resolution
          pnl_avg->Align = alNone;
          pnl_avg->Height = REPORT_PANEL_AVERAGE_PRINT_HEIGHT;
          pnl_avg->Width = REPORT_PANEL_AVERAGE_PRINT_WIDTH;

          print_rect.Top = report_height * 0.43;
          print_rect.Left = left_margin;
          print_rect.Right = left_margin + (report_width - left_margin) * 0.44;
          print_rect.Bottom = report_height * 0.78;
          chrt_avg_periph->PrintResolution = -100;
          chrt_avg_periph->BottomAxis->LabelsFont->Color = sphygmocor_black;
          chrt_avg_periph->BottomAxis->Title->Font->Color = sphygmocor_black;
          chrt_avg_periph->LeftAxis->LabelsFont->Color = sphygmocor_black;
          chrt_avg_periph->LeftAxis->Title->Font->Color = sphygmocor_black;
          chrt_avg_periph->Title->Font->Color = sphygmocor_maroon;
          // PM CR
          chrt_avg_periph->BackWall->Pen->Visible = true;
          chrt_avg_periph->PrintPartial(print_rect);

          print_rect.Top = report_height * 0.43;
          print_rect.Left = left_margin + (report_width - left_margin) * 0.56;
          print_rect.Right = report_width;
          print_rect.Bottom = report_height * 0.78;
          chrt_avg_central->PrintResolution = -100;
          chrt_avg_central->BottomAxis->LabelsFont->Color = sphygmocor_black;
          chrt_avg_central->BottomAxis->Title->Font->Color = sphygmocor_black;
          chrt_avg_central->RightAxis->LabelsFont->Color = sphygmocor_black;
          chrt_avg_central->RightAxis->Title->Font->Color = sphygmocor_black;
          chrt_avg_central->Title->Font->Color = sphygmocor_maroon;
          // PM CR
          chrt_avg_central->BackWall->Pen->Visible = true;
          chrt_avg_central->PrintPartial(print_rect);

          printer_ptr->EndDoc();

          chrt_pulse_overlay->MarginBottom = 5;
          chrt_pulse_overlay->MarginLeft = 12;

          chrt_avg_central->BottomAxis->LabelsFont->Color = sphygmocor_white;
          chrt_avg_central->BottomAxis->Title->Font->Color = sphygmocor_white;
          chrt_avg_central->RightAxis->LabelsFont->Color = sphygmocor_white;
          chrt_avg_central->RightAxis->Title->Font->Color = sphygmocor_white;
          chrt_avg_central->Title->Font->Color = sphygmocor_white;
          // PM CR
          chrt_avg_central->BackWall->Pen->Visible = false;

          chrt_avg_periph->BottomAxis->LabelsFont->Color = sphygmocor_white;
          chrt_avg_periph->BottomAxis->Title->Font->Color = sphygmocor_white;
          chrt_avg_periph->LeftAxis->LabelsFont->Color = sphygmocor_white;
          chrt_avg_periph->LeftAxis->Title->Font->Color = sphygmocor_white;
          chrt_avg_periph->Title->Font->Color = sphygmocor_white;
          // PM CR
          chrt_avg_periph->BackWall->Pen->Visible = false;

          // Reset the charts to normal size
          pnl_avg->Align = alClient;
       }

       if (pgctrl_reports->ActivePage == tbsht_clinical)
       {
          print_rect.Top = report_height * 0.57;
          print_rect.Left = left_margin;
          print_rect.Right = left_margin + (report_width - left_margin) * 0.43;
          print_rect.Bottom = report_height * 0.62;
          print_report_clinical_qc(printer_ptr, &print_rect);

          ypos = ypos + report_height * 0.01;
          print_rect.Top = ypos;
          print_rect.Left = left_margin + (report_width - left_margin) * 0.35;
          print_rect.Right = left_margin + (report_width - left_margin) * 0.48;
          print_rect.Bottom = report_height * 0.65;
          print_report_pressures(printer_ptr, &print_rect, false);

          // Set the charts to the size displayed in 600x800 resolution
          chrt_avg_central_periph->Align = alNone;
          chrt_avg_central_periph->Height = REPORT_PRESSURES_GRAPH_PRINT_HEIGHT;
          chrt_avg_central_periph->Width = REPORT_PRESSURES_GRAPH_PRINT_WIDTH;

          print_rect.Top = ypos;
          print_rect.Left = left_margin + (report_width - left_margin) * 0.50;
          print_rect.Right = report_width;
          print_rect.Bottom = report_height * 0.62;
          chrt_avg_central_periph->PrintResolution = -100;
          chrt_avg_central_periph->BottomAxis->LabelsFont->Color = sphygmocor_black;
          chrt_avg_central_periph->BottomAxis->Title->Font->Color = sphygmocor_black;
          chrt_avg_central_periph->BottomAxis->Grid->Color = sphygmocor_black;
          chrt_avg_central_periph->LeftAxis->LabelsFont->Color = sphygmocor_black;
          chrt_avg_central_periph->LeftAxis->Title->Font->Color = sphygmocor_black;
          chrt_avg_central_periph->LeftAxis->Grid->Color = sphygmocor_black;
          chrt_avg_central_periph->Title->Font->Color = sphygmocor_maroon;
          // PM CR
          chrt_avg_central_periph->BackWall->Pen->Visible = true;
          chrt_avg_central_periph->PrintPartial(print_rect);

          print_rect.Top = ypos;
          print_rect.Left = left_margin;
          print_rect.Right = left_margin + (report_width - left_margin) * 0.33;
          print_rect.Bottom = ypos + (report_height * 0.06);

          chrt_pulse_periph->PrintResolution = -100;
          chrt_pulse_periph->PrintPartial(print_rect);

          chrt_pulse_overlay->Title->Visible = true;
          chrt_pulse_overlay->Title->Text->Clear();
          S = PWAMTypeAsString[report_pwa->MeasureType];
          chrt_pulse_overlay->Title->Text->Add(S +" Raw Data Quality Control");
          print_rect.Top = ypos + (report_height * 0.07);
          print_rect.Left = left_margin;
          print_rect.Right = left_margin + (report_width - left_margin) * 0.33;
          print_rect.Bottom = report_height * 0.57;
          chrt_pulse_overlay->PrintResolution = -100;
          chrt_pulse_overlay->MarginBottom = 0;
          chrt_pulse_overlay->MarginLeft = 0;
          chrt_pulse_overlay->PrintPartial(print_rect);

          printer_ptr->EndDoc();

          // Reset charts and series to original colours
          chrt_avg_central_periph->BottomAxis->LabelsFont->Color = sphygmocor_white;
          chrt_avg_central_periph->BottomAxis->Title->Font->Color = sphygmocor_white;
          chrt_avg_central_periph->BottomAxis->Grid->Color = sphygmocor_background;
          chrt_avg_central_periph->LeftAxis->LabelsFont->Color = sphygmocor_white;
          chrt_avg_central_periph->LeftAxis->Title->Font->Color = sphygmocor_white;
          chrt_avg_central_periph->LeftAxis->Grid->Color = sphygmocor_background;
          chrt_avg_central_periph->Title->Font->Color = sphygmocor_white;
          // PM CR
          chrt_avg_central_periph->BackWall->Pen->Visible = false;

          chrt_pulse_overlay->Title->Visible = false;
          chrt_pulse_overlay->MarginBottom = 5;
          chrt_pulse_overlay->MarginLeft = 12;

          // Reset the charts to normal size
          chrt_avg_central_periph->Align = alClient;
       }

       if (pgctrl_reports->ActivePage == tbsht_reference)
       {
          print_rect.Top = report_height * 0.52;
          print_rect.Left = left_margin;
          print_rect.Right = left_margin + (report_width - left_margin) * 0.43;
          print_rect.Bottom = report_height * 0.57;
          print_report_clinical_qc(printer_ptr, &print_rect);

          print_rect.Top = ypos;
          print_rect.Left = left_margin + (report_width - left_margin) * 0.44;
          print_rect.Right = left_margin + (report_width - left_margin) * 0.50;
          print_rect.Bottom = report_height * 0.57;
          print_report_clinical_pressures(printer_ptr, &print_rect);

          print_rect.Top = ypos;
          print_rect.Left = left_margin;
          print_rect.Right = left_margin + (report_width - left_margin) * 0.43;
          print_rect.Bottom = ypos + (report_height * 0.06);

          chrt_pulse_periph->PrintResolution = -100;
          chrt_pulse_periph->PrintPartial(print_rect);

          chrt_pulse_overlay->Title->Visible = true;
          chrt_pulse_overlay->Title->Text->Clear();
          S = PWAMTypeAsString[report_pwa->MeasureType];
          chrt_pulse_overlay->Title->Text->Add(S +" Raw Data Quality Control");
          print_rect.Top = ypos + (report_height * 0.06);
          print_rect.Left = left_margin;
          print_rect.Right = left_margin + (report_width - left_margin) * 0.43;
          print_rect.Bottom = report_height * 0.52;
          chrt_pulse_overlay->PrintResolution = -100;
          chrt_pulse_overlay->MarginBottom = 0;
          chrt_pulse_overlay->MarginLeft = 0;
          chrt_pulse_overlay->PrintPartial(print_rect);

          // Set the charts to the size displayed in optimal resolution
          chrt_ap_reference->Align = alNone;
          chrt_ap_reference->Width = REPORT_REFERENCE_GRAPHS_PRINT_WIDTH;
          chrt_ap_reference->Height = REPORT_REFERENCE_GRAPHS_PRINT_HEIGHT;
          chrt_ap_reference->BottomAxis->LabelsFont->Color = sphygmocor_black;
          chrt_ap_reference->BottomAxis->Title->Font->Color = sphygmocor_black;
          chrt_ap_reference->LeftAxis->LabelsFont->Color = sphygmocor_black;
          chrt_ap_reference->LeftAxis->Title->Font->Color = sphygmocor_black;
          chrt_ap_reference->Title->Font->Color = sphygmocor_maroon;

          chrt_augidx_reference->Align = alNone;
          chrt_augidx_reference->Width = REPORT_REFERENCE_GRAPHS_PRINT_WIDTH;
          chrt_augidx_reference->Height = REPORT_REFERENCE_GRAPHS_PRINT_HEIGHT;
          chrt_augidx_reference->BottomAxis->LabelsFont->Color = sphygmocor_black;
          chrt_augidx_reference->BottomAxis->Title->Font->Color = sphygmocor_black;
          chrt_augidx_reference->LeftAxis->LabelsFont->Color = sphygmocor_black;
          chrt_augidx_reference->LeftAxis->Title->Font->Color = sphygmocor_black;
          chrt_augidx_reference->Title->Font->Color = sphygmocor_maroon;

          chrt_sp_reference->Align = alNone;
          chrt_sp_reference->Width = REPORT_REFERENCE_GRAPHS_PRINT_WIDTH;
          chrt_sp_reference->Height = REPORT_REFERENCE_GRAPHS_PRINT_HEIGHT;
          chrt_sp_reference->BottomAxis->LabelsFont->Color = sphygmocor_black;
          chrt_sp_reference->BottomAxis->Title->Font->Color = sphygmocor_black;
          chrt_sp_reference->LeftAxis->LabelsFont->Color = sphygmocor_black;
          chrt_sp_reference->LeftAxis->Title->Font->Color = sphygmocor_black;
          chrt_sp_reference->Title->Font->Color = sphygmocor_maroon;

          chrt_pp_reference->Align = alNone;
          chrt_pp_reference->Width = REPORT_REFERENCE_GRAPHS_PRINT_WIDTH;
          chrt_pp_reference->Height = REPORT_REFERENCE_GRAPHS_PRINT_HEIGHT;
          chrt_pp_reference->BottomAxis->LabelsFont->Color = sphygmocor_black;
          chrt_pp_reference->BottomAxis->Title->Font->Color = sphygmocor_black;
          chrt_pp_reference->LeftAxis->LabelsFont->Color = sphygmocor_black;
          chrt_pp_reference->LeftAxis->Title->Font->Color = sphygmocor_black;
          chrt_pp_reference->Title->Font->Color = sphygmocor_maroon;

          chrt_ed_reference->Align = alNone;
          chrt_ed_reference->Width = REPORT_REFERENCE_GRAPHS_PRINT_WIDTH;
          chrt_ed_reference->Height = REPORT_REFERENCE_GRAPHS_PRINT_HEIGHT;
          chrt_ed_reference->BottomAxis->LabelsFont->Color = sphygmocor_black;
          chrt_ed_reference->BottomAxis->Title->Font->Color = sphygmocor_black;
          chrt_ed_reference->LeftAxis->LabelsFont->Color = sphygmocor_black;
          chrt_ed_reference->LeftAxis->Title->Font->Color = sphygmocor_black;
          chrt_ed_reference->Title->Font->Color = sphygmocor_maroon;

          chrt_sevr_reference->Align = alNone;
          chrt_sevr_reference->Width = REPORT_REFERENCE_GRAPHS_PRINT_WIDTH;
          chrt_sevr_reference->Height = REPORT_REFERENCE_GRAPHS_PRINT_HEIGHT;
          chrt_sevr_reference->BottomAxis->LabelsFont->Color = sphygmocor_black;
          chrt_sevr_reference->BottomAxis->Title->Font->Color = sphygmocor_black;
          chrt_sevr_reference->LeftAxis->LabelsFont->Color = sphygmocor_black;
          chrt_sevr_reference->LeftAxis->Title->Font->Color = sphygmocor_black;
          chrt_sevr_reference->Title->Font->Color = sphygmocor_maroon;

          chrt_sevr_flow_reference->Align = alNone;
          chrt_sevr_flow_reference->Width = REPORT_REFERENCE_GRAPHS_PRINT_WIDTH;
          chrt_sevr_flow_reference->Height = REPORT_REFERENCE_GRAPHS_PRINT_HEIGHT;
          chrt_sevr_flow_reference->BottomAxis->LabelsFont->Color = sphygmocor_black;
          chrt_sevr_flow_reference->BottomAxis->Title->Font->Color = sphygmocor_black;
          chrt_sevr_flow_reference->LeftAxis->LabelsFont->Color = sphygmocor_black;
          chrt_sevr_flow_reference->LeftAxis->Title->Font->Color = sphygmocor_black;
          chrt_sevr_flow_reference->Title->Font->Color = sphygmocor_maroon;

          if (chrt_ap_reference->Parent == pnl_reference_main)
          {
            // Increase the size of the main chart
            chrt_ap_reference->Width = REPORT_PRESSURES_GRAPH_PRINT_WIDTH;
            chrt_ap_reference->Height = REPORT_PRESSURES_GRAPH_PRINT_HEIGHT;
            chrt_sevr_reference->LeftAxis->Increment = 50;

            print_rect.Top = ypos;
            print_rect.Left = left_margin + (report_width - left_margin) * 0.48;
            print_rect.Right = report_width;
            print_rect.Bottom = report_height * 0.57;
            chrt_ap_reference->PrintResolution = -100;
            chrt_ap_reference->PrintPartial(print_rect);

            print_rect.Top = report_height * 0.58;
            print_rect.Left = left_margin;
            print_rect.Right = left_margin + (report_width - left_margin) * 0.33;
            print_rect.Bottom = report_height * 0.75;
            chrt_sp_reference->PrintResolution = -100;
            chrt_sp_reference->PrintPartial(print_rect);

            print_rect.Top = report_height * 0.75;
            print_rect.Left = left_margin;
            print_rect.Right = left_margin + (report_width - left_margin) * 0.33;     
            print_rect.Bottom = report_height * 0.92;
            chrt_pp_reference->PrintResolution = -100;
            chrt_pp_reference->PrintPartial(print_rect);

            print_rect.Top = report_height * 0.58;
            print_rect.Left = left_margin + (report_width - left_margin) * 0.34;
            print_rect.Right = left_margin + (report_width - left_margin) * 0.66;
            print_rect.Bottom = report_height * 0.75;
            chrt_augidx_reference->PrintResolution = -100;
            chrt_augidx_reference->PrintPartial(print_rect);

            print_rect.Top = report_height * 0.75;
            print_rect.Left = left_margin + (report_width - left_margin) * 0.34;
            print_rect.Right = left_margin + (report_width - left_margin) * 0.66;
            print_rect.Bottom = report_height * 0.92;
            chrt_ed_reference->PrintResolution = -100;
            chrt_ed_reference->PrintPartial(print_rect);

            print_rect.Top = report_height * 0.58;
            print_rect.Left = left_margin + (report_width - left_margin) * 0.67;
            print_rect.Right = report_width;
            print_rect.Bottom = report_height * 0.75;
            chrt_sevr_reference->PrintResolution = -100;
            chrt_sevr_reference->PrintPartial(print_rect);

            print_rect.Top = report_height * 0.75;
            print_rect.Left = left_margin + (report_width - left_margin) * 0.67;
            print_rect.Right = report_width;
            print_rect.Bottom = report_height * 0.92;
            chrt_sevr_flow_reference->PrintResolution = -100;
            chrt_sevr_flow_reference->PrintPartial(print_rect);

            printer_ptr->EndDoc();
          }
          else if (chrt_sp_reference->Parent == pnl_reference_main)
          {
            // Increase the size of the main chart
            chrt_sp_reference->Width = REPORT_PRESSURES_GRAPH_PRINT_WIDTH;
            chrt_sp_reference->Height = REPORT_PRESSURES_GRAPH_PRINT_HEIGHT;
            chrt_sevr_reference->LeftAxis->Increment = 50;

            print_rect.Top = ypos;
            print_rect.Left = left_margin + (report_width - left_margin) * 0.48;
            print_rect.Right = report_width;
            print_rect.Bottom = report_height * 0.57;
            chrt_sp_reference->PrintResolution = -100;
            chrt_sp_reference->PrintPartial(print_rect);

            print_rect.Top = report_height * 0.58;
            print_rect.Left = left_margin;
            print_rect.Right = left_margin + (report_width - left_margin) * 0.33;
            print_rect.Bottom = report_height * 0.75;
            chrt_pp_reference->PrintResolution = -100;
            chrt_pp_reference->PrintPartial(print_rect);

            print_rect.Top = report_height * 0.75;
            print_rect.Left = left_margin;
            print_rect.Right = left_margin + (report_width - left_margin) * 0.33;
            print_rect.Bottom = report_height * 0.92;
            chrt_ap_reference->PrintResolution = -100;
            chrt_ap_reference->PrintPartial(print_rect);

            print_rect.Top = report_height * 0.58;
            print_rect.Left = left_margin + (report_width - left_margin) * 0.34;
            print_rect.Right = left_margin + (report_width - left_margin) * 0.66;
            print_rect.Bottom = report_height * 0.75;
            chrt_augidx_reference->PrintResolution = -100;
            chrt_augidx_reference->PrintPartial(print_rect);

            print_rect.Top = report_height * 0.75;
            print_rect.Left = left_margin + (report_width - left_margin) * 0.34;
            print_rect.Right = left_margin + (report_width - left_margin) * 0.66;
            print_rect.Bottom = report_height * 0.92;
            chrt_ed_reference->PrintResolution = -100;
            chrt_ed_reference->PrintPartial(print_rect);

            print_rect.Top = report_height * 0.58;
            print_rect.Left = left_margin + (report_width - left_margin) * 0.67;
            print_rect.Right = report_width;
            print_rect.Bottom = report_height * 0.75;
            chrt_sevr_reference->PrintResolution = -100;
            chrt_sevr_reference->PrintPartial(print_rect);

            print_rect.Top = report_height * 0.75;
            print_rect.Left = left_margin + (report_width - left_margin) * 0.67;
            print_rect.Right = report_width;
            print_rect.Bottom = report_height * 0.92;
            chrt_sevr_flow_reference->PrintResolution = -100;
            chrt_sevr_flow_reference->PrintPartial(print_rect);

            printer_ptr->EndDoc();
          }
          else if (chrt_pp_reference->Parent == pnl_reference_main)
          {
            // Increase the size of the main chart
            chrt_pp_reference->Width = REPORT_PRESSURES_GRAPH_PRINT_WIDTH;
            chrt_pp_reference->Height = REPORT_PRESSURES_GRAPH_PRINT_HEIGHT;
            chrt_sevr_reference->LeftAxis->Increment = 50;

            print_rect.Top = ypos;
            print_rect.Left = left_margin + (report_width - left_margin) * 0.48;
            print_rect.Right = report_width;
            print_rect.Bottom = report_height * 0.57;
            chrt_pp_reference->PrintResolution = -100;
            chrt_pp_reference->PrintPartial(print_rect);

            print_rect.Top = report_height * 0.58;
            print_rect.Left = left_margin;
            print_rect.Right = left_margin + (report_width - left_margin) * 0.33;
            print_rect.Bottom = report_height * 0.75;
            chrt_sp_reference->PrintResolution = -100;
            chrt_sp_reference->PrintPartial(print_rect);

            print_rect.Top = report_height * 0.75;
            print_rect.Left = left_margin;
            print_rect.Right = left_margin + (report_width - left_margin) * 0.33;
            print_rect.Bottom = report_height * 0.92;
            chrt_ap_reference->PrintResolution = -100;
            chrt_ap_reference->PrintPartial(print_rect);

            print_rect.Top = report_height * 0.58;
            print_rect.Left = left_margin + (report_width - left_margin) * 0.34;
            print_rect.Right = left_margin + (report_width - left_margin) * 0.66;
            print_rect.Bottom = report_height * 0.75;
            chrt_augidx_reference->PrintResolution = -100;
            chrt_augidx_reference->PrintPartial(print_rect);

            print_rect.Top = report_height * 0.75;
            print_rect.Left = left_margin + (report_width - left_margin) * 0.34;
            print_rect.Right = left_margin + (report_width - left_margin) * 0.66;
            print_rect.Bottom = report_height * 0.92;
            chrt_ed_reference->PrintResolution = -100;
            chrt_ed_reference->PrintPartial(print_rect);

            print_rect.Top = report_height * 0.58;
            print_rect.Left = left_margin + (report_width - left_margin) * 0.67;
            print_rect.Right = report_width;
            print_rect.Bottom = report_height * 0.75;
            chrt_sevr_reference->PrintResolution = -100;
            chrt_sevr_reference->PrintPartial(print_rect);

            print_rect.Top = report_height * 0.75;
            print_rect.Left = left_margin + (report_width - left_margin) * 0.67;
            print_rect.Right = report_width;
            print_rect.Bottom = report_height * 0.92;
            chrt_sevr_flow_reference->PrintResolution = -100;
            chrt_sevr_flow_reference->PrintPartial(print_rect);

            printer_ptr->EndDoc();
          }
          else if (chrt_augidx_reference->Parent == pnl_reference_main)
          {
            // Increase the size of the main chart
            chrt_augidx_reference->Width = REPORT_PRESSURES_GRAPH_PRINT_WIDTH;
            chrt_augidx_reference->Height = REPORT_PRESSURES_GRAPH_PRINT_HEIGHT;
            chrt_sevr_reference->LeftAxis->Increment = 50;

            print_rect.Top = ypos;
            print_rect.Left = left_margin + (report_width - left_margin) * 0.48;
            print_rect.Right = report_width;
            print_rect.Bottom = report_height * 0.57;
            chrt_augidx_reference->PrintResolution = -100;
            chrt_augidx_reference->PrintPartial(print_rect);

            print_rect.Top = report_height * 0.58;
            print_rect.Left = left_margin;
            print_rect.Right = left_margin + (report_width - left_margin) * 0.33;
            print_rect.Bottom = report_height * 0.75;
            chrt_sp_reference->PrintResolution = -100;
            chrt_sp_reference->PrintPartial(print_rect);

            print_rect.Top = report_height * 0.75;
            print_rect.Left = left_margin;
            print_rect.Right = left_margin + (report_width - left_margin) * 0.33;
            print_rect.Bottom = report_height * 0.92;
            chrt_pp_reference->PrintResolution = -100;
            chrt_pp_reference->PrintPartial(print_rect);

            print_rect.Top = report_height * 0.58;
            print_rect.Left = left_margin + (report_width - left_margin) * 0.34;
            print_rect.Right = left_margin + (report_width - left_margin) * 0.66;
            print_rect.Bottom = report_height * 0.75;
            chrt_ap_reference->PrintResolution = -100;
            chrt_ap_reference->PrintPartial(print_rect);

            print_rect.Top = report_height * 0.75;
            print_rect.Left = left_margin + (report_width - left_margin) * 0.34;
            print_rect.Right = left_margin + (report_width - left_margin) * 0.66;
            print_rect.Bottom = report_height * 0.92;
            chrt_ed_reference->PrintResolution = -100;
            chrt_ed_reference->PrintPartial(print_rect);

            print_rect.Top = report_height * 0.58;
            print_rect.Left = left_margin + (report_width - left_margin) * 0.67;
            print_rect.Right = report_width;
            print_rect.Bottom = report_height * 0.75;
            chrt_sevr_reference->PrintResolution = -100;
            chrt_sevr_reference->PrintPartial(print_rect);

            print_rect.Top = report_height * 0.75;
            print_rect.Left = left_margin + (report_width - left_margin) * 0.67;
            print_rect.Right = report_width;
            print_rect.Bottom = report_height * 0.92;
            chrt_sevr_flow_reference->PrintResolution = -100;
            chrt_sevr_flow_reference->PrintPartial(print_rect);

            printer_ptr->EndDoc();
          }
          else if (chrt_ed_reference->Parent == pnl_reference_main)
          {
            // Increase the size of the main chart
            chrt_ed_reference->Width = REPORT_PRESSURES_GRAPH_PRINT_WIDTH;
            chrt_ed_reference->Height = REPORT_PRESSURES_GRAPH_PRINT_HEIGHT;
            chrt_sevr_reference->LeftAxis->Increment = 50;

            print_rect.Top = ypos;
            print_rect.Left = left_margin + (report_width - left_margin) * 0.48;
            print_rect.Right = report_width;
            print_rect.Bottom = report_height * 0.57;
            chrt_ed_reference->PrintResolution = -100;
            chrt_ed_reference->PrintPartial(print_rect);

            print_rect.Top = report_height * 0.58;
            print_rect.Left = left_margin;
            print_rect.Right = left_margin + (report_width - left_margin) * 0.33;
            print_rect.Bottom = report_height * 0.75;
            chrt_sp_reference->PrintResolution = -100;
            chrt_sp_reference->PrintPartial(print_rect);

            print_rect.Top = report_height * 0.75;
            print_rect.Left = left_margin;
            print_rect.Right = left_margin + (report_width - left_margin) * 0.33;
            print_rect.Bottom = report_height * 0.92;
            chrt_pp_reference->PrintResolution = -100;
            chrt_pp_reference->PrintPartial(print_rect);

            print_rect.Top = report_height * 0.58;
            print_rect.Left = left_margin + (report_width - left_margin) * 0.34;
            print_rect.Right = left_margin + (report_width - left_margin) * 0.66;
            print_rect.Bottom = report_height * 0.75;
            chrt_ap_reference->PrintResolution = -100;
            chrt_ap_reference->PrintPartial(print_rect);

            print_rect.Top = report_height * 0.75;
            print_rect.Left = left_margin + (report_width - left_margin) * 0.34;
            print_rect.Right = left_margin + (report_width - left_margin) * 0.66;
            print_rect.Bottom = report_height * 0.92;
            chrt_augidx_reference->PrintResolution = -100;
            chrt_augidx_reference->PrintPartial(print_rect);

            print_rect.Top = report_height * 0.58;
            print_rect.Left = left_margin + (report_width - left_margin) * 0.67;
            print_rect.Right = report_width;
            print_rect.Bottom = report_height * 0.75;
            chrt_sevr_reference->PrintResolution = -100;
            chrt_sevr_reference->PrintPartial(print_rect);

            print_rect.Top = report_height * 0.75;
            print_rect.Left = left_margin + (report_width - left_margin) * 0.67;
            print_rect.Right = report_width;
            print_rect.Bottom = report_height * 0.92;
            chrt_sevr_flow_reference->PrintResolution = -100;
            chrt_sevr_flow_reference->PrintPartial(print_rect);

            printer_ptr->EndDoc();
          }
          else if (chrt_sevr_reference->Parent == pnl_reference_main)
          {
            // Increase the size of the main chart
            chrt_sevr_reference->Width = REPORT_PRESSURES_GRAPH_PRINT_WIDTH;
            chrt_sevr_reference->Height = REPORT_PRESSURES_GRAPH_PRINT_HEIGHT;

            print_rect.Top = ypos;
            print_rect.Left = left_margin + (report_width - left_margin) * 0.48;
            print_rect.Right = report_width;
            print_rect.Bottom = report_height * 0.57;
            chrt_sevr_reference->PrintResolution = -100;
            chrt_sevr_reference->PrintPartial(print_rect);

            print_rect.Top = report_height * 0.58;
            print_rect.Left = left_margin;
            print_rect.Right = left_margin + (report_width - left_margin) * 0.33;
            print_rect.Bottom = report_height * 0.75;
            chrt_sp_reference->PrintResolution = -100;
            chrt_sp_reference->PrintPartial(print_rect);

            print_rect.Top = report_height * 0.75;
            print_rect.Left = left_margin;
            print_rect.Right = left_margin + (report_width - left_margin) * 0.33;
            print_rect.Bottom = report_height * 0.92;
            chrt_pp_reference->PrintResolution = -100;
            chrt_pp_reference->PrintPartial(print_rect);

            print_rect.Top = report_height * 0.58;
            print_rect.Left = left_margin + (report_width - left_margin) * 0.34;
            print_rect.Right = left_margin + (report_width - left_margin) * 0.66;
            print_rect.Bottom = report_height * 0.75;
            chrt_ap_reference->PrintResolution = -100;
            chrt_ap_reference->PrintPartial(print_rect);

            print_rect.Top = report_height * 0.75;
            print_rect.Left = left_margin + (report_width - left_margin) * 0.34;
            print_rect.Right = left_margin + (report_width - left_margin) * 0.66;
            print_rect.Bottom = report_height * 0.92;
            chrt_augidx_reference->PrintResolution = -100;
            chrt_augidx_reference->PrintPartial(print_rect);

            print_rect.Top = report_height * 0.58;
            print_rect.Left = left_margin + (report_width - left_margin) * 0.67;
            print_rect.Right = report_width;
            print_rect.Bottom = report_height * 0.75;
            chrt_ed_reference->PrintResolution = -100;
            chrt_ed_reference->PrintPartial(print_rect);

            print_rect.Top = report_height * 0.75;
            print_rect.Left = left_margin + (report_width - left_margin) * 0.67;
            print_rect.Right = report_width;
            print_rect.Bottom = report_height * 0.92;
            chrt_sevr_flow_reference->PrintResolution = -100;
            chrt_sevr_flow_reference->PrintPartial(print_rect);

            printer_ptr->EndDoc();
          }
          chrt_sevr_reference->LeftAxis->Increment = 20;

          int height = tbsht_reference->Height / 3;

          // Reset the charts to normal size
          chrt_ap_reference->Align = alClient;
          chrt_ap_reference->BottomAxis->LabelsFont->Color = sphygmocor_white;
          chrt_ap_reference->BottomAxis->Title->Font->Color = sphygmocor_white;
          chrt_ap_reference->LeftAxis->LabelsFont->Color = sphygmocor_white;
          chrt_ap_reference->LeftAxis->Title->Font->Color = sphygmocor_white;
          chrt_ap_reference->Title->Font->Color = sphygmocor_white;

          chrt_augidx_reference->Align = alClient;
          chrt_augidx_reference->BottomAxis->LabelsFont->Color = sphygmocor_white;
          chrt_augidx_reference->BottomAxis->Title->Font->Color = sphygmocor_white;
          chrt_augidx_reference->LeftAxis->LabelsFont->Color = sphygmocor_white;
          chrt_augidx_reference->LeftAxis->Title->Font->Color = sphygmocor_white;
          chrt_augidx_reference->Title->Font->Color = sphygmocor_white;

          chrt_sp_reference->Align = alClient;
          chrt_sp_reference->BottomAxis->LabelsFont->Color = sphygmocor_white;
          chrt_sp_reference->BottomAxis->Title->Font->Color = sphygmocor_white;
          chrt_sp_reference->LeftAxis->LabelsFont->Color = sphygmocor_white;
          chrt_sp_reference->LeftAxis->Title->Font->Color = sphygmocor_white;
          chrt_sp_reference->Title->Font->Color = sphygmocor_white;

          chrt_pp_reference->Align = alClient;
          chrt_pp_reference->BottomAxis->LabelsFont->Color = sphygmocor_white;
          chrt_pp_reference->BottomAxis->Title->Font->Color = sphygmocor_white;
          chrt_pp_reference->LeftAxis->LabelsFont->Color = sphygmocor_white;
          chrt_pp_reference->LeftAxis->Title->Font->Color = sphygmocor_white;
          chrt_pp_reference->Title->Font->Color = sphygmocor_white;

          chrt_ed_reference->Align = alClient;
          chrt_ed_reference->BottomAxis->LabelsFont->Color = sphygmocor_white;
          chrt_ed_reference->BottomAxis->Title->Font->Color = sphygmocor_white;
          chrt_ed_reference->LeftAxis->LabelsFont->Color = sphygmocor_white;
          chrt_ed_reference->LeftAxis->Title->Font->Color = sphygmocor_white;
          chrt_ed_reference->Title->Font->Color = sphygmocor_white;

          chrt_sevr_reference->Align = alClient;
          chrt_sevr_reference->BottomAxis->LabelsFont->Color = sphygmocor_white;
          chrt_sevr_reference->BottomAxis->Title->Font->Color = sphygmocor_white;
          chrt_sevr_reference->LeftAxis->LabelsFont->Color = sphygmocor_white;
          chrt_sevr_reference->LeftAxis->Title->Font->Color = sphygmocor_white;
          chrt_sevr_reference->Title->Font->Color = sphygmocor_white;

          chrt_sevr_flow_reference->Align = alBottom;
          chrt_sevr_flow_reference->Height = height;
          chrt_sevr_flow_reference->BottomAxis->LabelsFont->Color = sphygmocor_white;
          chrt_sevr_flow_reference->BottomAxis->Title->Font->Color = sphygmocor_white;
          chrt_sevr_flow_reference->LeftAxis->LabelsFont->Color = sphygmocor_white;
          chrt_sevr_flow_reference->LeftAxis->Title->Font->Color = sphygmocor_white;
          chrt_sevr_flow_reference->Title->Font->Color = sphygmocor_white;

          // Reset the charts and series to their original colours
          chrt_pulse_overlay->Title->Visible = false;
          chrt_pulse_overlay->MarginBottom = 5;
          chrt_pulse_overlay->MarginLeft = 12;
       }

       if (pgctrl_reports->ActivePage == tbsht_avi)
       {
          // Remember the normal chart sizes
          REPORT_AVI_AVG_CENTRAL_NORMAL_HEIGHT = chrt_avi_avg_central->Height;

          // Set the charts to the size displayed in 600x800 resolution
          chrt_avi_reflected->Align = alNone;
          pnl_centre_avi_graphs->Align = alNone;
          chrt_avi_avg_central->Align = alNone;
          chrt_avi_flow->Align = alNone;
          chrt_avi_flow->Height = REPORT_PRESSURES_GRAPH_PRINT_HEIGHT;
          chrt_avi_flow->Width = REPORT_PRESSURES_GRAPH_PRINT_WIDTH;
          chrt_avi_avg_central->Height = REPORT_PRESSURES_GRAPH_PRINT_HEIGHT;
          chrt_avi_avg_central->Width = REPORT_PRESSURES_GRAPH_PRINT_WIDTH;
          chrt_avi_reflected->Height = REPORT_PRESSURES_GRAPH_PRINT_HEIGHT;
          chrt_avi_reflected->Width = REPORT_PRESSURES_GRAPH_PRINT_WIDTH;

          print_rect.Top = ypos;
          print_rect.Left = left_margin;
          print_rect.Right = left_margin + (report_width - left_margin) * 0.4;
          print_rect.Bottom = report_height * 0.65;
          chrt_avi_avg_central->PrintResolution = -100;
          chrt_avi_avg_central->BottomAxis->LabelsFont->Color = sphygmocor_black;
          chrt_avi_avg_central->BottomAxis->Title->Font->Color = sphygmocor_black;
          chrt_avi_avg_central->LeftAxis->LabelsFont->Color = sphygmocor_black;
          chrt_avi_avg_central->LeftAxis->Title->Font->Color = sphygmocor_black;
          chrt_avi_avg_central->Title->Font->Color = sphygmocor_maroon;
          // PM CR
          chrt_avi_avg_central->BackWall->Pen->Visible = true;
          chrt_avi_avg_central->PrintPartial(print_rect);

          print_rect.Top = ypos;
          print_rect.Left = left_margin + (report_width - left_margin) * 0.4;
          print_rect.Right = left_margin + (report_width - left_margin) * 0.6;
          print_rect.Bottom = report_height * 0.65;
          chrt_avi_flow->PrintResolution = -100;
          chrt_avi_flow->BottomAxis->LabelsFont->Color = sphygmocor_black;
          chrt_avi_flow->BottomAxis->Title->Font->Color = sphygmocor_black;
          chrt_avi_flow->Title->Font->Color = sphygmocor_maroon;
          // PM CR
          chrt_avi_flow->BackWall->Pen->Visible = true;
          chrt_avi_flow->PrintPartial(print_rect);

          print_rect.Top = ypos;
          print_rect.Left = left_margin + (report_width - left_margin) * 0.6;
          print_rect.Right = report_width;
          print_rect.Bottom = report_height * 0.65;
          chrt_avi_reflected->PrintResolution = -100;
          chrt_avi_reflected->BottomAxis->LabelsFont->Color = sphygmocor_black;
          chrt_avi_reflected->BottomAxis->Title->Font->Color = sphygmocor_black;
          chrt_avi_reflected->RightAxis->LabelsFont->Color = sphygmocor_black;
          chrt_avi_reflected->RightAxis->Title->Font->Color = sphygmocor_black;
          chrt_avi_reflected->Title->Font->Color = sphygmocor_maroon;
          // PM CR
          chrt_avi_reflected->BackWall->Pen->Visible = true;
          chrt_avi_reflected->PrintPartial(print_rect);

          print_rect.Top = report_height * 0.65;
          print_rect.Left = left_margin + (report_width - left_margin) * 0.34;
          print_rect.Right = report_width;
          print_rect.Bottom = report_height * 0.93;
          //chrt_pwv_reference->PrintResolution = -100;
          //chrt_pwv_reference->PrintPartial(print_rect);

          printer_ptr->EndDoc();

          chrt_avi_avg_central->BottomAxis->LabelsFont->Color = sphygmocor_white;
          chrt_avi_avg_central->BottomAxis->Title->Font->Color = sphygmocor_white;
          chrt_avi_avg_central->LeftAxis->LabelsFont->Color = sphygmocor_white;
          chrt_avi_avg_central->LeftAxis->Title->Font->Color = sphygmocor_white;
          chrt_avi_avg_central->Title->Font->Color = sphygmocor_white;
          // PM CR
          chrt_avi_avg_central->BackWall->Pen->Visible = false;

          chrt_avi_flow->BottomAxis->LabelsFont->Color = sphygmocor_white;
          chrt_avi_flow->BottomAxis->Title->Font->Color = sphygmocor_white;
          chrt_avi_flow->Title->Font->Color = sphygmocor_white;
          // PM CR
          chrt_avi_flow->BackWall->Pen->Visible = false;

          chrt_avi_reflected->BottomAxis->LabelsFont->Color = sphygmocor_white;
          chrt_avi_reflected->BottomAxis->Title->Font->Color = sphygmocor_white;
          chrt_avi_reflected->RightAxis->LabelsFont->Color = sphygmocor_white;
          chrt_avi_reflected->RightAxis->Title->Font->Color = sphygmocor_white;
          chrt_avi_reflected->Title->Font->Color = sphygmocor_white;
          // PM CR
          chrt_avi_reflected->BackWall->Pen->Visible = false;

          // Reset the charts to normal size
          chrt_avi_avg_central->Align = alTop;
          chrt_avi_avg_central->Height = REPORT_AVI_AVG_CENTRAL_NORMAL_HEIGHT;
          pnl_centre_avi_graphs->Align = alLeft;
          chrt_avi_reflected->Align = alTop;
          chrt_avi_reflected->Height = REPORT_AVI_AVG_CENTRAL_NORMAL_HEIGHT;
          chrt_avi_flow->Align = alClient;
       }

       index = chrt_pulse_overlay->SeriesCount() - 1;
       while (index >= 0)
       {
          srs = (TLineSeries *)chrt_pulse_overlay->Series[index];
          srs->ColorRange(srs->XValues,
                             srs->MinXValue(),
                             srs->MaxXValue(),
                             sphygmocor_grey);
          index--;
       }
   }
   catch (Exception &exception)
   {
      printer_ptr->Abort();
      printer_ptr->EndDoc();
   }
   printer_ptr->Orientation = old_orient;
   Screen->Cursor = crDefault;
   /*if (this->Visible && grd_report->Visible)
   {
      grd_report->SetFocus();
   }*/   
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_report_pwa::bbtn_modifyClick(TObject *Sender)
{
   AUDIT_MODE        AuditMode;
   MEAS_SENDER_TYPE  report_sender;

   // The modify form can only be browsed for deleted reports and in audit mode
   if (report_pwa->AuditFlag == AUDIT_DELETED || pwa_audit_mode)
   {
      AuditMode = AUDIT_BROWSING;
   }
   else
   {
      AuditMode = AUDIT_NORMAL;
   }

   // PM V9
   // The field that opens the modify form will be selected on the modify form
   if (Sender == lbl_operator_title || Sender == lbl_operator)
   {
      report_sender = MEAS_OPERATOR;
   }
   else if (Sender == lbl_hwbmi_title || Sender == lbl_hwbmi)
   {
      report_sender = MEAS_BMI;
   }
   else if (Sender == lbl_med_title || Sender == edt_med)
   {
      report_sender = MEAS_MEDICATIONS;
   }
   else if (Sender == lbl_notes_title || Sender == edt_notes)
   {
      report_sender = MEAS_NOTES;
   }
   else if (Sender == edt_interpretation || Sender == lbl_interpretation_title)
   {
      report_sender = MEAS_INTERPRETATION;
   }
   else if (Sender == lbl_avi_distance_title || Sender == lbl_avi_distance)
   {
      report_sender = MEAS_DISTANCE;
   }
   else
   {
      report_sender = MEAS_INTERPRETATION;
   }

   // Disable OnChange event to protect rewriting PWA
   grd_report->DataSource->OnDataChange = NULL;

   // Call recalculate form
   bool ret = meas_recalculate_show_form(this,
                                         report_pwa,
                                         report_qry,
                                         lbl_pname->Caption,
                                         AuditMode,
                                         report_sender);
   // Restore OnChange event
   grd_report->DataSource->OnDataChange = record_changed;

   // Refresh grid and charts
   if (ret)
   {
      record_changed(this, NULL);
   }
   /*if (grd_report->Visible)
   {
      grd_report->SetFocus();
   }*/
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_report_pwa::bbtn_auditClick(TObject *Sender)
{
   if(config_get_audit_option() && study_mode == MEAS_PWA_ID)
   {
      if (pwa_audit_mode)
      {
         pwa_audit_mode = false;
         audit_pwa_hide();
      }
      else
      {
         pwa_audit_mode = true;
         if (!audit_pwa_show())
         {
            pwa_audit_mode = false;
         }
      }
   }   
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_report_pwa::bbtn_sessionClick(TObject *Sender)
{
  frm_main->spdbtn_reportClick(Sender);
  Hide();

   // PM V9
   // Display the simulation label on the status bar when returning from PWA Reports
   TPWM *pwm = meas_get_current_pwm();
   if (pwm->Simulation)
   {
      emma_display_statusbar_message(SIMULATION, SIMULATION_NOTE, sphygmocor_maroon);
   }
   else
   {
      emma_display_statusbar_message("", "", sphygmocor_white);
   }
}
//---------------------------------------------------------------------------
// PM V9
void __fastcall Tfrm_report_pwa::bbtn_repeatClick(TObject *Sender)
{
   report_repeat_assessment = true;
   frm_main->spdbtn_measureClick(Sender);   
}
//---------------------------------------------------------------------------






