//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include <inc/std.h>
#include <scor/form_main.h>
#include <log/pubserv.h>
#include <msg/pubserv.h>
#include <print/pubserv.h>
#include <patient/pubserv.h>
#include <config/pubserv.h>
#include <analysis/pubserv.h>
#include "analysis.h"
#include "form_analysis_pwa.h"
#include "form_trend_pwa.h"
#include "form_analysis_pwv.h"
#include "form_trend_pwv.h"
#include "form_select.h"

#pragma package(smart_init)

VAR_EXPORT AnsiString analysis_first_study;
VAR_EXPORT AnsiString analysis_last_study;
VAR_EXPORT AnsiString analysis_first_export;
VAR_EXPORT AnsiString analysis_last_export;

VAR_EXPORT bool analysis_audit_initialised;

Tfrm_trend_pwa *frm_trend_pwa;
Tfrm_analysis_pwa *frm_analysis_pwa;

Tfrm_trend_pwv *frm_trend_pwv;
Tfrm_analysis_pwv *frm_analysis_pwv;

bool analysis_initialised;

bool analysis_initialise(void)
{
   analysis_initialised = false;

   frm_trend_pwa = new Tfrm_trend_pwa(emma_get_main_form_pointer());
   frm_analysis_pwa = new Tfrm_analysis_pwa(emma_get_main_form_pointer());
   frm_analysis_pwv = NULL;
   frm_trend_pwv = NULL;

   analysis_first_study = "";
   analysis_last_study = "";
   analysis_first_export = "";
   analysis_last_export = "";

   analysis_audit_initialised = true;

   if (frm_trend_pwa && frm_analysis_pwa)
   {
      analysis_initialised = true;
   }
   else
   {
      log_write("Analysis Failed Initialisation");
   }
   return (analysis_initialised);
}

void analysis_destroy(void)
{
   if (analysis_initialised)
   {
      analysis_initialised = false;
   }
}

Child_Form  *analysis_get_analysis_form_pointer(void)
{
   Child_Form    *a_form;
   MEAS_ID_TYPE  meas_id;

   a_form = NULL;

   meas_id = patient_get_study_mode();

   switch (meas_id)
   {
      case MEAS_PWA_ID:
      case MEAS_PWM_ID:
      case MEAS_HRV_ID:
         a_form = frm_analysis_pwa;
         break;

      case MEAS_PWV_ID:
         if (frm_analysis_pwv == NULL)
         {
            frm_analysis_pwv = new Tfrm_analysis_pwv(emma_get_main_form_pointer());
         }
         a_form = frm_analysis_pwv;
         break;

      default:
         break;
   }
   return a_form;
}

Child_Form  *analysis_get_trend_form_pointer(void)
{
   Child_Form    *t_form;
   MEAS_ID_TYPE  meas_id;

   t_form = NULL;

   meas_id = patient_get_study_mode();

   switch (meas_id)
   {
      case MEAS_PWA_ID:
      case MEAS_PWM_ID:
      case MEAS_HRV_ID:
         t_form = frm_trend_pwa;
         break;
      case MEAS_PWV_ID:
         if (frm_trend_pwv == NULL)
         {
            frm_trend_pwv = new Tfrm_trend_pwv(emma_get_main_form_pointer());
         }
         t_form = frm_trend_pwv;
         break;
      default:
         break;
   }
   return t_form;
}

void analysis_print_study_data(TRect *print_rect)
{
   TPrinter    *print_ptr;
   AnsiString  S;

   print_ptr = print_get_printer_ptr();
   if (print_ptr == NULL)
   {
     return;
   }
   TFontStyles font_style;
   S = "Patient Studies  ";
   print_ptr->Canvas->TextOut(print_rect->Left,
                              print_rect->Top,
                              S);
   int text_width = print_ptr->Canvas->TextWidth(S);

   S = analysis_first_study + "  -  " + analysis_last_study;
   font_style << fsBold;
   print_ptr->Canvas->Font->Style = font_style;
   print_ptr->Canvas->TextOut(print_rect->Left + text_width,
                              print_rect->Top,
                              S);
}

//---------------------------------------------------------------------------
// Clear list with deletion objects
//---------------------------------------------------------------------------
void Analysis_ClearList(TStrings *pList)
{
  try
  {
    if (pList != NULL)
    {
      for (int i=0; i < pList->Count; i++)
      {
         if (pList->Objects[i] != NULL)
         {
            delete (TDateTime *)(pList->Objects[i]);
            pList->Objects[i] = NULL;
         }
      }
      pList->Clear();
    }
  }
  catch (Exception &exception)
  {
      log_write("Analysis " + SERROR +exception.Message);
  }
}

bool analysis_get_audit_initialised()
{
   MEAS_ID_TYPE  meas_id;

   meas_id = patient_get_study_mode();

   // If the audit option is set, find out if analysis was initialised,
   // taking deleted reports into account, otherwise return true
   if (!config_get_audit_option())
   {
      return true;
   }

   switch (meas_id)
   {
      case MEAS_PWA_ID:
         analysis_audit_initialised = analysis_pwa_get_audit_initialised();
         break;

      case MEAS_PWV_ID:
         analysis_audit_initialised = analysis_pwv_get_audit_initialised();
         break;

      default:
         break;
   }
   return analysis_audit_initialised;
}
