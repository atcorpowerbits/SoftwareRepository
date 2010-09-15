//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include <config/pubserv.h>
#include <comms/pubserv.h>
#include <msg/pubserv.h>
#include "form_splash.h"
#include "form_main.h"
#include "utils.h"

USEFORM("form_splash.cpp", frm_splash);
USEFORM("form_main.cpp", frm_main);
USEFORM("..\dbmgr\source\Dbmgr.cpp", dbmgr_dmod);
USEFORM("..\patient\source\form_patient.cpp", frm_patient);
USEFORM("..\report\source\form_report_pwv.cpp", frm_report_pwv);
USEFORM("..\capture\source\form_cappwa.cpp", frm_capture_pwa);
USEFORM("..\analysis\source\form_analysis_pwv.cpp", frm_analysis_pwv);
USEFORM("..\analysis\source\form_trend_pwv.cpp", frm_trend_pwv);
USEFORM("..\meas\source\form_pwa.cpp", frm_measure_pwa);
USEFORM("..\config\source\form_config.cpp", frm_config);
USEFORM("..\meas\source\form_recalculate_pwa.cpp", frm_recalculate_pwa);
USEFORM("form_about.cpp", frm_aboutbox);
USEFORM("..\capture\source\form_cappwv.cpp", frm_capture_pwv);
USEFORM("..\meas\source\form_pwv.cpp", frm_measure_pwv);
USEFORM("..\export\source\form_export.cpp", frm_export);
USEFORM("form_selectdir.cpp", frm_select_dir);
USEFORM("..\analysis\source\form_select.cpp", frm_select);
USEFORM("..\report\source\form_report_pwa.cpp", frm_report_pwa);
USEFORM("..\meas\source\form_recalculate_pwv.cpp", frm_recalculate_pwv);
USEFORM("..\analysis\source\form_trend_pwa.cpp", frm_trend_pwa);
USEFORM("..\analysis\source\form_analysis_pwa.cpp", frm_analysis_pwa);
USEFORM("..\patient\source\form_patlist.cpp", frm_patlist);
USEFORM("..\capture\source\form_cappwm.cpp", frm_capture_pwm);
USEFORM("..\report\source\form_report_pwm.cpp", frm_report_pwm);
USEFORM("..\meas\source\form_pwm.cpp", frm_measure_pwm);
USEFORM("..\multdb\source\form_merge.cpp", frm_merge);
USEFORM("..\print\source\form_batchprint.cpp", frm_batchprint);
USEFORM("..\export\source\form_export_database.cpp", frm_export_database);
USEFORM("..\multdb\source\form_multdb.cpp", frm_multdb);
USEFORM("..\capture\source\form_caphrv.cpp", frm_capture_hrv);
USEFORM("..\meas\source\form_hrv.cpp", frm_measure_hrv);
USEFORM("..\report\source\form_report_hrv.cpp", frm_report_hrv);
USEFORM("..\meas\source\form_recalculate_hrv.cpp", frm_recalculate_hrv);
USEFORM("..\cfr11\source\form_security.cpp", frm_security);
//---------------------------------------------------------------------------
HANDLE emma_is_running(char *mutex_name)
{
   int result;

   HANDLE mutex = CreateMutex(NULL, true, mutex_name);
   result = GetLastError();
   if (result != 0)
   {
      mutex = (HANDLE)0;
   }
   return (mutex);
}

void emma_startup(void)
{
   COMMS_ID_TYPE       port_id;

   if (emma_is_initialised())
   {
      port_id = config_get_comms_port();
      if (comms_open(port_id))
      {
         comms_detect_module();
         if (!comms_is_module_available())
         {
            comms_detect_module();
            if (!comms_is_module_available())
            {

               if (MsgBox(LoadStr(MSG_COMMS_EL_MODULE_NOT_FOUND) +"\n\n" +LoadStr(MSG_COMMS_TURN_ON),
                          SNOTIFICATION,
                          MB_YESNO | MB_ICONQUESTION) == IDYES)
               {
                  comms_detect_module();
                  if (!comms_is_module_available())
                  {
                     comms_detect_module();
                     if (!comms_is_module_available())
                     {
                        if (MsgBox(LoadStr(MSG_ELECTR_NOT_FOUND) + "\n\n" +
                                   LoadStr(MSG_CHECK_CONNECTION), SWARNING,
                                   MB_YESNO | MB_ICONQUESTION) == IDYES)
                        {
                           config_show();
                        }
                     }
                  }
               }
            }
         }
         comms_close();
      }
      else
      {
         if (port_id == COMMS_PORT_USB)
         {
            MsgBox(LoadStr(MSG_COMMS_EL_MODULE_NOT_FOUND) + "\n\n" +LoadStr(MSG_COMMS_CHECK_POWER_CONNECTION),
                   SNOTIFICATION,
                   MB_ICONINFORMATION | MB_OK);
         }
      }
   }
}

WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
    try
    {
        HANDLE mutex = emma_is_running("TITAN_EXE");
        if (mutex == 0)
        {
           MsgBox(MSG_APP_ALREADY_RUNNING);
           return 1;
        }

        frm_splash = new Tfrm_splash(Application);
        frm_splash->Show();
        frm_splash->Update();

        emma_set_date_formats();
        Application->Initialize();
        Application->Title = "SphygmoCor Cardiovascular Management Suite (CvMS)";
        Application->CreateForm(__classid(Tfrm_main), &frm_main);
        Application->CreateForm(__classid(Tfrm_config), &frm_config);
        frm_splash->lbl_loading->Caption = "Initialising Communications Port ...";
        emma_startup();

        frm_splash->Hide();
        frm_splash->Close();
        Application->Run();
    }
    catch (Exception &exception)
    {
        Application->ShowException(&exception);
    }
    return 0;
}
//---------------------------------------------------------------------------
