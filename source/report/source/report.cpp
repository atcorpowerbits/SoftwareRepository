//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include <inc/std.h>
#include <meas/pubserv.h>
#include <log/pubserv.h>
#include <patient/pubserv.h>
#include <report/pubserv.h>
#include "form_main.h"
#include "report.h"
#include "attrib.h"
#include "form_report_pwa.h"
#include "form_report_pwv.h"
#include "form_report_pwm.h"
#include "jpeg.hpp"
//---------------------------------------------------------------------------
#pragma package(smart_init)
/*bool               report_initialised;
VAR_EXPORT UCOUNT  report_age;

bool report_initialise(void)
{
   report_age = 0;
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

   meas_mode = emma_get_study_mode();

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

      default:
         break;
   }
   return report_form;
}


bool report_create_jpeg(Graphics::TBitmap *form_bmp, String jpeg_file_name)
{
   bool         created = false;
   TJPEGImage*  jpg_image;

   jpg_image = new TJPEGImage();
   if (jpg_image)
   {
      jpg_image->CompressionQuality = 75;
      jpg_image->Performance = jpBestSpeed;
      jpg_image->PixelFormat = jf24Bit;
      jpg_image->Smoothing = false;
      jpg_image->Assign(form_bmp);
      jpg_image->SaveToFile(jpeg_file_name);
      created = true;
      delete jpg_image;
      jpg_image = (TJPEGImage *)0;
   }
   return created;
}
 */

