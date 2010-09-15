//---------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include <config/pubserv.h>
#include <comms/pubserv.h>
#include <scor/utils.h>
#include <cfr11/pubserv.h>
#include <emr/pubserv.h>
#include "form_about.h"
//---------------------------------------------------------------------
#pragma resource "*.dfm"
Tfrm_aboutbox *frm_aboutbox;
//---------------------------------------------------------------------
__fastcall Tfrm_aboutbox::Tfrm_aboutbox(TComponent* AOwner)
	: TForm(AOwner)
{
}
//---------------------------------------------------------------------
void __fastcall Tfrm_aboutbox::btn_okClick(TObject *Sender)
{
  Close();
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_aboutbox::FormShow(TObject *Sender)
{
   CONFIG_SYSTEM_OPTIONS  cfg_options;

   lbl_sysid->Caption = config_get_system_id();
   lbl_version->Caption = "Version " + RELEASE_SOFTWARE_VERSION_LONG + config_get_clinical_string();

   cfg_options = config_get_system_options();

   switch (cfg_options)
   {
      case CONFIG_PWA_OPTION:
         lbl_pwa->Visible = true;
         lbl_pwv->Visible = false;
         lbl_pwm->Visible = false;
         lbl_hrv->Visible = false;
         break;

      case CONFIG_PWV_OPTION:
         lbl_pwa->Visible = true;
         lbl_pwv->Visible = true;
         lbl_pwm->Visible = false;
         lbl_hrv->Visible = false;
         break;

      case CONFIG_PWV_ONLY_OPTION:
         lbl_pwa->Visible = false;
         lbl_pwv->Visible = true;
         lbl_pwm->Visible = false;
         lbl_hrv->Visible = false;
         break;

      case CONFIG_PWM_OPTION:
         lbl_pwa->Visible = true;
         lbl_pwv->Visible = false;
         lbl_pwm->Visible = true;
         lbl_hrv->Visible = false;
         break;

      case CONFIG_HRV_OPTION:
         lbl_pwa->Visible = true;
         lbl_pwv->Visible = false;
         lbl_pwm->Visible = false;
         lbl_hrv->Visible = true;
         break;

      case CONFIG_STANDARD_ALL_OPTION:
         lbl_pwa->Visible = true;
         lbl_pwv->Visible = true;
         lbl_pwm->Visible = true;
         lbl_hrv->Visible = false;
         break;

      case CONFIG_EXTENDED_ALL_OPTION:
         lbl_pwa->Visible = true;
         lbl_pwv->Visible = true;
         lbl_pwm->Visible = false;
         lbl_hrv->Visible = true;
         break;

      default:
         lbl_pwa->Visible = true;
         lbl_pwv->Visible = false;
         lbl_pwm->Visible = false;
         lbl_hrv->Visible = false;
         break;
   }

   // If the hardware configuration is unknown, request and display the module string
   lbl_hardware->Caption = "";
   if (comms_get_modes_string() == CONFIG_NO_OPTION_STRING)
   {
      if (comms_is_module_available())
      {
         if (comms_request_hwconfig())
         {
            lbl_hardware->Caption = comms_get_emod_string() + " - " + comms_get_modes_string();
         }
      }
   }
   else
   {
      lbl_hardware->Caption = comms_get_emod_string() + " - " + comms_get_modes_string();
   }

   // Determine the current mode and display it on the data mode label
   if (config_get_audit_option())
   {
      lbl_data_mode->Caption = AUDIT_ENABLED;
   }
   else if (emr_get_enabled())
   {
      if (emr_get_default_mode())
      {
         lbl_data_mode->Caption = EMR_DEFAULT_MODE;
      }
      else
      {
         lbl_data_mode->Caption = EMR_ENABLED;
      }
   }
   else
   {
      lbl_data_mode->Caption = "";
   }
}
//---------------------------------------------------------------------------


void __fastcall Tfrm_aboutbox::btn_printClick(TObject *Sender)
{
   Print();     
}
//---------------------------------------------------------------------------


