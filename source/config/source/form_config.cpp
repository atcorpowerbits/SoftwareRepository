//------------ --------------------------------------------------------------
#include <vcl.h>
#include <FileCtrl.hpp>
#pragma hdrstop

#include <inc/std.h>
#include <log/pubserv.h>
#include <msg/pubserv.h>
#include <dbmgr/pubserv.h>
#include <comms/pubserv.h>
#include <patient/pubserv.h>
#include <emr/pubserv.h>
#include <scor/form_main.h>
#include <scor/form_selectdir.h>
#include <config/pubserv.h>
#include <config/pubtype.h>
#include <scor/utils.h>
#include "form_config.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

const String CONFIG_FILENAME = "SCOR.INI";

const String CONFIG_SYSTEM_SECTION = "SYSTEM";
const String CONFIG_SYSTEM_ID_KEY = "ID";
const String CONFIG_SYSTEM_CKSUM_KEY = "CKSUM";
const String CONFIG_SYSTEM_VERIFY_KEY = "VERIFY";

const String CONFIG_QC_SECTION = "Quality Control";
const String CONFIG_QC_PH_KEY =  "PH";
const String CONFIG_QC_PHV_KEY = "PHV";
const String CONFIG_QC_DV_KEY =  "DV";

const String CONFIG_COMMS_SECTION =  "Comms";
const String CONFIG_COMMS_PORT_KEY = "Port";

const String CONFIG_P_SENSITIVITY_SECTION =  "Pressure Sensitivity";
const String CONFIG_P_UPPER_LIMIT_KEY = "PSUL";

const String CONFIG_REPORT_STYLE_SECTION =  "Report Style";
const String CONFIG_REPORT_STYLE_KEY = "Style";
const String CONFIG_REPORT_STYLE_SCREEN_KEY = "Screen";
const String CONFIG_REPORT_STYLE_PTIV_KEY = "PTIV";
const String CONFIG_REPORT_STYLE_SRRI_KEY = "SRRI";
const String CONFIG_CLINICAL_AIXHR75_KEY = "AIXHR75";
const String CONFIG_CLINICAL_AIX_KEY = "AIX";

const String CONFIG_DATABASE_PACK_DATE_SECTION = "DBCHECK";
const String CONFIG_DATABASE_PACK_DATE_KEY = "DATE";

const String CONFIG_SYSTEM_LOCALE_SECTION = "System Locale";
const String CONFIG_MEASUREMENT_UNITS_KEY = "METRIC";

const String CONFIG_REPORT_TITLE_SECTION =  "Report Title";
const String CONFIG_REPORT_TITLE_KEY = "Title";

const String CONFIG_TONOMETER_SECTION = "Tonometer";
const String CONFIG_TONOMETER_KEY = "SERIAL NUMBER";

const String CONFIG_CAPTURE_STYLE_SECTION =  "Capture Style";
const String CONFIG_RTOF_KEY = "RTOF";
const String CONFIG_AUTO_CAPTURE_KEY = "Auto Capture";

// PM V9
const int CONFIG_DEFAULT_QC_PH = 80;
const int CONFIG_DEFAULT_QC_PHV = 5;
const int CONFIG_DEFAULT_QC_DV = 5;
const int CONFIG_DEFAULT_PRESSURE_UPPER_LIMIT = 4000;
const int CONFIG_DEFAULT_CAPABILITIES_NUMBER = 0;

const int CONFIG_MIN_QC_PH = 70;
const int CONFIG_MAX_QC_PH = 180;
const int CONFIG_MIN_QC_PHV = 1;
const int CONFIG_MAX_QC_PHV = 15;
const int CONFIG_MIN_QC_DV = 1;
const int CONFIG_MAX_QC_DV = 20;
const int CONFIG_MIN_PRESSURE_UPPER_LIMIT = 400;
const int CONFIG_MAX_PRESSURE_UPPER_LIMIT = 4000;

const String CONFIG_DEFAULT_SYSTEM_ID = "00001";
const String CONFIG_DEFAULT_REPORT_TITLE = SOFTWARE_DEFAULT_REPORT_TITLE;

const int CONFIG_PWA_OFFSET           = 14;
const int CONFIG_PWV_ONLY_OFFSET      = 24;
const int CONFIG_HRV_OFFSET           = 32;
const int CONFIG_PWV_OFFSET           = 42;
const int CONFIG_PWM_OFFSET           = 61;
const int CONFIG_STANDARD_ALL_OFFSET  = 73;   // PWA PWV PWM
const int CONFIG_PWM_ONLY_OFFSET      = 81;
const int CONFIG_EXTENDED_ALL_OFFSET  = 87;   // PWA PWV HRV
const int CONFIG_AVI_OFFSET           = 5;    // AVI can be added to any PWA offset
const int CONFIG_AUDIT_OFFSET         = 2;    // Audit mode can be added to any PWA or PWV offset
// PM V9
const int CONFIG_CLINICAL_OFFSET      = 4;    // Clinical mode applies to PWA and PWV only


VAR_EXPORT Tfrm_config         *frm_config;
VAR_EXPORT CONFIG_RECORD_TYPE  config;
VAR_EXPORT TIniFile            *config_ini;
VAR_EXPORT TStringList         *config_options_list;
VAR_EXPORT CONFIG_RECORD_TYPE  config_default;
VAR_EXPORT String              simulation_directory;

bool    config_initialised;

/*
** Code that manages the Form
*/

__fastcall Tfrm_config::Tfrm_config(TComponent* Owner)
  : TForm(Owner)
{
}

void __fastcall Tfrm_config::btn_defaultsClick(TObject *Sender)
{
   edt_qcph->Text = IntToStr(config_default.qc_ph);
   edt_qcphv->Text = IntToStr(config_default.qc_phv);
   edt_qcdv->Text = IntToStr(config_default.qc_dv);
   edt_p_upper_limit->Text = IntToStr(config_default.p_upper_limit);
   rbtn_metric->Checked = true;
}


void __fastcall Tfrm_config::btn_config_saveClick(TObject *Sender)
{
   // Validation
   if (edt_qcph->Text.ToIntDef(-1) < CONFIG_MIN_QC_PH || edt_qcph->Text.ToIntDef(-1) > CONFIG_MAX_QC_PH)
   {
     MsgBox(TERROR, MSG_CONFIG_ERROR, MSG_CONFIG_OUT_OF_RANGE,
            LoadStr(MSG_CONFIG_OUT_OF_RANGE) + "[" + IntToStr(CONFIG_MIN_QC_PH) +
            "," + IntToStr(CONFIG_MAX_QC_PH) + "]");
     edt_qcph->SetFocus();
     return;
   }

   if (edt_qcphv->Text.ToIntDef(-1) < CONFIG_MIN_QC_PHV || edt_qcphv->Text.ToIntDef(-1) > CONFIG_MAX_QC_PHV)
   {
     MsgBox(TERROR, MSG_CONFIG_ERROR, MSG_CONFIG_OUT_OF_RANGE,
            LoadStr(MSG_CONFIG_OUT_OF_RANGE) + "[" + IntToStr(CONFIG_MIN_QC_PHV) +
            "," + IntToStr(CONFIG_MAX_QC_PHV) + "]");
     edt_qcphv->SetFocus();
     return;
   }

   if (edt_qcdv->Text.ToIntDef(-1) < CONFIG_MIN_QC_DV || edt_qcdv->Text.ToIntDef(-1) > CONFIG_MAX_QC_DV)
   {
     MsgBox(TERROR, MSG_CONFIG_ERROR, MSG_CONFIG_OUT_OF_RANGE,
            LoadStr(MSG_CONFIG_OUT_OF_RANGE) + "[" + IntToStr(CONFIG_MIN_QC_DV) +
            "," + IntToStr(CONFIG_MAX_QC_DV) + "]");
     edt_qcdv->SetFocus();
     return;
   }

   if ((edt_p_upper_limit->Text.ToIntDef(-1) < CONFIG_MIN_PRESSURE_UPPER_LIMIT) ||
       (edt_p_upper_limit->Text.ToIntDef(-1) > CONFIG_MAX_PRESSURE_UPPER_LIMIT))
   {
      MsgBox(TERROR, MSG_CONFIG_ERROR, MSG_CONFIG_SENSITIVITY_OUT_OF_RANGE,
             LoadStr(MSG_CONFIG_SENSITIVITY_OUT_OF_RANGE) + "[" + IntToStr(CONFIG_MIN_PRESSURE_UPPER_LIMIT) +
             "," + IntToStr(CONFIG_MAX_PRESSURE_UPPER_LIMIT) + "]");
     edt_p_upper_limit->SetFocus();
     return;
   }

   if (edt_tonometer->Text.ToIntDef(-1) > 0)
   {
      config.tonometer = (UINT32)edt_tonometer->Text.ToInt();
   }
   else
   {
      // If the audit option is set, a tonometer serial number must be entered
      if (config_get_audit_option())
      {
         MsgBox(TERROR, MSG_CONFIG_ERROR, MSG_SECURITY_TONOMETER,
            LoadStr(MSG_SECURITY_TONOMETER));
         edt_tonometer->SetFocus();
         return;
      }
      else
      {
         config.tonometer = CONFIG_DEFAULT_TONOMETER;
      }
   }

   // Store
   config.qc_ph = (UCOUNT)edt_qcph->Text.ToInt();
   config.qc_phv = (UTINY)edt_qcphv->Text.ToInt();
   config.qc_dv = (UTINY)edt_qcdv->Text.ToInt();
   config.p_upper_limit = (UCOUNT)edt_p_upper_limit->Text.ToInt();

   // Set the port to the item selected in the combobox.
   // If simulation is selected, save the current port as the old port first.
   int index = cmbx_comports->ItemIndex;
   if((COMMS_ID_TYPE) cmbx_comports->Items->Objects[index] == COMMS_PORT_SIMULATE)
   {
      config.old_port = config.port;
   }

   config.port = (COMMS_ID_TYPE) cmbx_comports->Items->Objects[index];

   // Close the comms port in case the previous comms port becomes unavailable
   comms_close();

   if (chkbx_blind_study->Checked)
   {
      config.report_style = CONFIG_BLIND_REPORT_STYLE;
   }
   else
   {
      config.report_style = CONFIG_DEFAULT_REPORT_STYLE;
   }

   if (chkbx_clinical_aixhr75->Checked)
   {
      config.clinical_aixhr75 = true;
   }
   else
   {
      config.clinical_aixhr75 = false;
   }

   if (chkbx_clinical_aix->Checked)
   {
      config.clinical_aix = true;
   }
   else
   {
      config.clinical_aix = false;
   }

   if (chkbx_detailed->Checked)
   {
      config.report_screen = CONFIG_DETAILED_REPORT_SCREEN;
   }
   else if (chkbx_clinical->Checked)
   {
      config.report_screen = CONFIG_CLINICAL_REPORT_SCREEN;
   }
   else
   {
      config.report_screen = CONFIG_DEFAULT_REPORT_SCREEN;
   }

   if (rbtn_metric->Checked)
   {
      config.locale = CONFIG_DEFAULT_LOCALE;
   }
   else
   {
      config.locale = CONFIG_IMPERIAL_LOCALE;
   }

   // PM V9
   if (chkbx_rtof->Checked)
   {
      config.rtof = true;
   }
   else
   {
      config.rtof = false;
   }

   if (chkbx_auto_capture->Checked)
   {
      config.auto_capture = true;
   }
   else
   {
      config.auto_capture = false;
   }

   if (config_ini != NULL)
   {
      if (config_ini->SectionExists(CONFIG_QC_SECTION))
      {
         config_ini->WriteInteger(CONFIG_QC_SECTION,
                                  CONFIG_QC_PH_KEY,
                                  config.qc_ph);
         config_ini->WriteInteger(CONFIG_QC_SECTION,
                                  CONFIG_QC_PHV_KEY,
                                  config.qc_phv);
         config_ini->WriteInteger(CONFIG_QC_SECTION,
                                  CONFIG_QC_DV_KEY,
                                  config.qc_dv);
      }

      if (config_ini->SectionExists(CONFIG_COMMS_SECTION))
      {
         // Never write simulation mode to the ini file as SphygmoCor would then
         // start-up in simulation mode.
         if (config.port == COMMS_PORT_SIMULATE)
         {
            config_ini->WriteInteger(CONFIG_COMMS_SECTION,
                                  CONFIG_COMMS_PORT_KEY,
                                  config.old_port);
         }
         else
         {
            config_ini->WriteInteger(CONFIG_COMMS_SECTION,
                                  CONFIG_COMMS_PORT_KEY,
                                  config.port);
         }
      }

      if (config_ini->SectionExists(CONFIG_P_SENSITIVITY_SECTION))
      {
         config_ini->WriteInteger(CONFIG_P_SENSITIVITY_SECTION,
                                  CONFIG_P_UPPER_LIMIT_KEY,
                                  config.p_upper_limit);
      }

      if (config_ini->SectionExists(CONFIG_REPORT_STYLE_SECTION))
      {
         config_ini->WriteInteger(CONFIG_REPORT_STYLE_SECTION,
                                  CONFIG_REPORT_STYLE_KEY,
                                  config.report_style);
         config_ini->WriteInteger(CONFIG_REPORT_STYLE_SECTION,
                                  CONFIG_REPORT_STYLE_SCREEN_KEY,
                                  config.report_screen);
         config_ini->WriteBool(CONFIG_REPORT_STYLE_SECTION,
                                  CONFIG_CLINICAL_AIXHR75_KEY,
                                  config.clinical_aixhr75);
         config_ini->WriteBool(CONFIG_REPORT_STYLE_SECTION,
                                  CONFIG_CLINICAL_AIX_KEY,
                                  config.clinical_aix);
      }

      if (config_ini->SectionExists(CONFIG_SYSTEM_LOCALE_SECTION))
      {
         config_ini->WriteInteger(CONFIG_SYSTEM_LOCALE_SECTION,
                                  CONFIG_MEASUREMENT_UNITS_KEY,
                                  config.locale);
      }

      if (config_ini->SectionExists(CONFIG_TONOMETER_SECTION))
      {
         config_ini->WriteInteger(CONFIG_TONOMETER_SECTION,
                                  CONFIG_TONOMETER_KEY,
                                  config.tonometer);
      }

      // PM V9
      if (config_ini->SectionExists(CONFIG_CAPTURE_STYLE_SECTION))
      {
         config_ini->WriteBool(CONFIG_CAPTURE_STYLE_SECTION,
                                  CONFIG_RTOF_KEY,
                                  config.rtof);
         config_ini->WriteBool(CONFIG_CAPTURE_STYLE_SECTION,
                                  CONFIG_AUTO_CAPTURE_KEY,
                                  config.auto_capture);
      }
   }
   Close();
}

void __fastcall Tfrm_config::FormShow(TObject *Sender)
{
   edt_qcph->Text = IntToStr(config.qc_ph);
   edt_qcphv->Text = IntToStr(config.qc_phv);
   edt_qcdv->Text = IntToStr(config.qc_dv);
   edt_p_upper_limit->Text = IntToStr(config.p_upper_limit);
   btn_select_dir->Visible = false;

   if (config.tonometer != CONFIG_DEFAULT_TONOMETER)
   {
      edt_tonometer->Text = IntToStr(config.tonometer);
   }

   config_enable_ports();

   // Never show the form with simulation mode selected
   if (config.port == COMMS_PORT_SIMULATE)
   {
      config.port = config.old_port;
   }

   // PM V9
   if (config.clinical_aixhr75)
   {
      chkbx_clinical_aixhr75->Checked = true;
   }
   if (config.clinical_aix)
   {
      chkbx_clinical_aix->Checked = true;
   }

   // PM V9
   if (config.clinical_enabled)
   {
      chkbx_blind_study->Visible = false;
   }
   else if (config.report_style == CONFIG_BLIND_REPORT_STYLE)
   {
      chkbx_blind_study->Checked = true;
      chkbx_clinical_aixhr75->Checked = false;
      chkbx_clinical_aix->Checked = false;
      chkbx_clinical_aixhr75->Enabled = false;
      chkbx_clinical_aix->Enabled = false;
   }

   // PM V9
   if (config.clinical_enabled)
   {
      grpbx_report_screen->Visible = false;
   }
   else if (config.report_screen == CONFIG_DETAILED_REPORT_SCREEN)
   {
      chkbx_detailed->Checked = true;
      chkbx_clinical->Checked = false;
   }
   else if (config.report_screen == CONFIG_CLINICAL_REPORT_SCREEN)
   {
      chkbx_detailed->Checked = false;
      chkbx_clinical->Checked = true;
   }
   else
   {
      chkbx_detailed->Checked = false;
      chkbx_clinical->Checked = false;
   }

   if(config.locale == CONFIG_DEFAULT_LOCALE)
   {
      rbtn_metric->Checked = true;
   }
   else if(config.locale == CONFIG_IMPERIAL_LOCALE)
   {
      rbtn_imperial->Checked = true;
   }

   // PM V9
   if(config.rtof)
   {
      chkbx_rtof->Checked = true;
   }
   if(config.auto_capture)
   {
      chkbx_auto_capture->Checked = true;
   }

   // Show the form with the current port selected.
   bool port_available = false;
   for (int i=0; i<cmbx_comports->Items->Count; i++)
   {
      if ((COMMS_ID_TYPE)cmbx_comports->Items->Objects[i] == config.port)
      {
         cmbx_comports->ItemIndex = i;
         port_available = true;
      }
   }
   // If the current port is no longer available set item index to '0'
   if (!port_available)
   {
      cmbx_comports->ItemIndex = 0;
   }

   // PM V9
   // If Data Audit Trail mode is enabled or EMR editing is not allowed,
   // then editing the Quality Control settings will be disabled
   if (config_get_audit_option())
   {
      grpbx_qc->Enabled = false;
   }
   else if (!emr_get_editing())
   {
      grpbx_qc->Enabled = false;
   }
   else
   {
      grpbx_qc->Enabled = true;
   }
}

void __fastcall Tfrm_config::btn_config_cancelClick(TObject *Sender)
{
   Close();
}
//---------------------------------------------------------------------------
/*
** External services provided by the Object
*/

bool config_initialise(void)
{
   String     config_fname;
   String     msg;
   String     dir;
   UINT16     calc_crc16;
   TDateTime  today;
   String     source_pathfile;
   String     rename_pathfile;

   config_initialised = true;
   dir = ExtractFilePath(Application->ExeName);
   rename_pathfile = dir + CONFIG_DATA_SUBDIR + "//" + DBMGR_DATABASE_NAME;
   source_pathfile = dir + CONFIG_DATA_SUBDIR + "//" + DBMGR_OLD_DATABASE_NAME;

   if (DirectoryExists(dir + CONFIG_SYSTEM_SUBDIR) == false)
   {
      MsgBox_show(TFATAL,
                  MSG_SYSTEM_ERROR,
                  LoadStr(MSG_NO_SYSTEM_SUBDIR),
                  MSG_NO_SYSTEM_SUBDIR,
                  LoadStr(MSG_NO_SYSTEM_SUBDIR));
      config_initialised = false;
      return config_initialised;
   }

   if (DirectoryExists(dir + CONFIG_DATA_SUBDIR)==false)
   {
      MsgBox_show(TFATAL,
                  MSG_SYSTEM_ERROR,
                  LoadStr(MSG_NO_DATA_SUBDIR),
                  MSG_NO_DATA_SUBDIR,
                  LoadStr(MSG_NO_DATA_SUBDIR));
      config_initialised = false;
      return config_initialised;
   }

   // If the new database name doesn't exist, rename the old database
   // Do this here because config is initialised before dbmgr
   if (FileExists(rename_pathfile) == false)
   {
      if (FileExists(source_pathfile))
      {
         if (RenameFile(source_pathfile, rename_pathfile) == false)
         {
            MsgBox_show(TFATAL,
                     MSG_SYSTEM_ERROR,
                     LoadStr(MSG_OLD_DATABASE),
                     MSG_OLD_DATABASE,
                     LoadStr(MSG_OLD_DATABASE));
            config_initialised = false;
            return config_initialised;
         }
      }
      else
      {
         MsgBox_show(TFATAL,
                     MSG_SYSTEM_ERROR,
                     LoadStr(MSG_NO_DATABASE),
                     MSG_NO_DATABASE,
                     LoadStr(MSG_NO_DATABASE));
         config_initialised = false;
         return config_initialised;
      }
   }

   // database in system subdirectory (not fatal)
   if (FileExists(dir + CONFIG_SYSTEM_SUBDIR + "//" + DBMGR_DATABASE_NAME)==false)
   {
      MsgBox_show(TERROR,
                  MSG_SYSTEM_ERROR,
                  LoadStr(MSG_NO_DB_IN_SYSTEM_DIR),
                  MSG_NO_DB_IN_SYSTEM_DIR,
                  LoadStr(MSG_NO_DB_IN_SYSTEM_DIR));
   }

   config_options_list = NULL;
   today = Date();

   config_default.qc_ph = CONFIG_DEFAULT_QC_PH;
   config_default.qc_phv = CONFIG_DEFAULT_QC_PHV;
   config_default.qc_dv = CONFIG_DEFAULT_QC_DV;
   config_default.p_upper_limit = CONFIG_DEFAULT_PRESSURE_UPPER_LIMIT;
   config_default.report_style = CONFIG_DEFAULT_REPORT_STYLE;
   config_default.report_screen = CONFIG_DEFAULT_REPORT_SCREEN;
   config_default.report_title = CONFIG_DEFAULT_REPORT_TITLE;
   config_default.ptiv = CONFIG_DEFAULT_PTIV;
   config_default.srri = CONFIG_DEFAULT_SRRI;
   config_default.locale = CONFIG_DEFAULT_LOCALE;
   config_default.tonometer = CONFIG_DEFAULT_TONOMETER;

   // Obtain the list of communication ports.
   // If there are no ports, set port one as the default, otherwise assign the first port in the list.
   config_default.port_list = new TStringList;
   comms_detect_ports(config_default.port_list);
   if (config_default.port_list->Count == 0)
   {
      config_default.old_port = COMMS_PORT_ONE;
      config_default.port = COMMS_PORT_ONE;
   }
   else
   {
      config_default.old_port = (COMMS_ID_TYPE) config_default.port_list->Strings[0].ToInt();
      config_default.port = (COMMS_ID_TYPE) config_default.port_list->Strings[0].ToInt();
   }
   config_default.system_id = CONFIG_DEFAULT_SYSTEM_ID;
   config_default.last_pack_date = DateToStr(today);
   config_default.capabilities = CONFIG_DEFAULT_CAPABILITIES_NUMBER;
   config_default.option = CONFIG_PWA_OPTION;
   config_default.avi_enabled = false;
   config_default.crc16 = 0xaaaa;
   config_default.audit_enabled = false;
   config_default.rtof = true;
   config_default.auto_capture = true;
   config_default.clinical_enabled = false;
   config_default.clinical_aixhr75 = false;
   config_default.clinical_aix = false;

   simulation_directory = dir;

   config = config_default;

   config_fname = ExtractFilePath(ParamStr(0)) +CONFIG_SYSTEM_SUBDIR
      + "\\" +CONFIG_FILENAME;
   //config_fname = "\\\\192.168.1.133\\DownloadXMLOut\\scor.ini";
   config_ini = new TIniFile(config_fname);
   if (config_ini != NULL)
   {
      if (!config_ini->SectionExists(CONFIG_SYSTEM_SECTION))
      {
         config_initialised = false;
         msg = SERROR + ": " + LoadStr(MSG_CONFIG_NO_SYSID);
         MsgBox(msg, SERROR + " (#" + IntToStr(MSG_CONFIG_NO_SYSID) + ")");
         log_write(MSG_CONFIG_NO_SYSID);
      }
      else
      {
         config.system_id = config_ini->ReadString(CONFIG_SYSTEM_SECTION,
                                                   CONFIG_SYSTEM_ID_KEY,
                                                   config.system_id);
         config.crc16 = (UINT16)config_ini->ReadInteger(CONFIG_SYSTEM_SECTION,
                                                        CONFIG_SYSTEM_CKSUM_KEY,
                                                        config.crc16);
         calc_crc16 = config_check_system_id(config.system_id);
         if (calc_crc16 != config.crc16)
         {
            config_initialised = false;
            msg = SERROR + ": " + LoadStr(MSG_CONFIG_CHECKSUM_FAILED);
            MsgBox(msg, SERROR + " (#" + IntToStr(MSG_CONFIG_CHECKSUM_FAILED) + ")");
            log_write(MSG_CONFIG_CHECKSUM_FAILED);
            return (config_initialised);
         }
         config.capabilities = config_ini->ReadInteger(CONFIG_SYSTEM_SECTION,
                                                       CONFIG_SYSTEM_VERIFY_KEY,
                                                       config.capabilities);
         if (!config_determine_capabilities())
         {
            config_initialised = false;
            MsgBox("The Configuration file is out of date or has been tampered with.\n\nThe SphygmoCor System will now close.\n\nPlease contact AtCor Medical Technical Support.",
                    SWARNING,
                    MB_ICONEXCLAMATION | MB_OK);
         }
      }

      if (config_initialised)
      {
         if (!config_ini->SectionExists(CONFIG_QC_SECTION))
         {
            config_ini->WriteInteger(CONFIG_QC_SECTION,
                                     CONFIG_QC_PH_KEY,
                                     config.qc_ph);
            config_ini->WriteInteger(CONFIG_QC_SECTION,
                                     CONFIG_QC_PHV_KEY,
                                     config.qc_phv);
            config_ini->WriteInteger(CONFIG_QC_SECTION,
                                     CONFIG_QC_DV_KEY,
                                     config.qc_dv);
         }
         else
         {
            config.qc_ph = (UCOUNT)config_ini->ReadInteger(CONFIG_QC_SECTION,
                                                           CONFIG_QC_PH_KEY,
                                                           config.qc_ph);
            config.qc_phv = (UTINY)config_ini->ReadInteger(CONFIG_QC_SECTION,
                                                           CONFIG_QC_PHV_KEY,
                                                           config.qc_phv);
            config.qc_dv = (UTINY)config_ini->ReadInteger(CONFIG_QC_SECTION,
                                                          CONFIG_QC_DV_KEY,
                                                          config.qc_dv);
         }

         if (!config_ini->SectionExists(CONFIG_COMMS_SECTION))
         {
            config_ini->WriteInteger(CONFIG_COMMS_SECTION,
                                     CONFIG_COMMS_PORT_KEY,
                                     config.port);
         }
         else
         {
            // If there are no ports, put the system in simulation mode.
            // Otherwise, set both ports to the previously
            // used port stored in the ini file.
            if (config.port_list->Count == 0)
            {
               config.old_port = COMMS_PORT_SIMULATE;
               config.port = COMMS_PORT_SIMULATE;
            }
            else
            {
               config.port = (COMMS_ID_TYPE)config_ini->ReadInteger(CONFIG_COMMS_SECTION,
                                                                  CONFIG_COMMS_PORT_KEY,
                                                                  config.port);
               config.old_port = config.port;
            }
         }

         if (!config_ini->SectionExists(CONFIG_P_SENSITIVITY_SECTION))
         {
            config_ini->WriteInteger(CONFIG_P_SENSITIVITY_SECTION,
                                     CONFIG_P_UPPER_LIMIT_KEY,
                                     config.p_upper_limit);
         }
         else
         {
            config.p_upper_limit = (UCOUNT)config_ini->ReadInteger(CONFIG_P_SENSITIVITY_SECTION,
                                                                   CONFIG_P_UPPER_LIMIT_KEY,
                                                                   config.p_upper_limit);
         }
         if (!config_ini->SectionExists(CONFIG_REPORT_STYLE_SECTION))
         {
            config_ini->WriteInteger(CONFIG_REPORT_STYLE_SECTION,
                                     CONFIG_REPORT_STYLE_KEY,
                                     config.report_style);
            config_ini->WriteInteger(CONFIG_REPORT_STYLE_SECTION,
                                     CONFIG_REPORT_STYLE_SCREEN_KEY,
                                     config.report_screen);
            config_ini->WriteInteger(CONFIG_REPORT_STYLE_SECTION,
                                     CONFIG_REPORT_STYLE_PTIV_KEY,
                                     config.ptiv);
            config_ini->WriteInteger(CONFIG_REPORT_STYLE_SECTION,
                                     CONFIG_REPORT_STYLE_SRRI_KEY,
                                     config.srri);
            config_ini->WriteBool(CONFIG_REPORT_STYLE_SECTION,
                                  CONFIG_CLINICAL_AIXHR75_KEY,
                                  config.clinical_aixhr75);
            config_ini->WriteBool(CONFIG_REPORT_STYLE_SECTION,
                                  CONFIG_CLINICAL_AIX_KEY,
                                  config.clinical_aix);
         }
         else
         {
            config.report_style = (UTINY)config_ini->ReadInteger(CONFIG_REPORT_STYLE_SECTION,
                                                                 CONFIG_REPORT_STYLE_KEY,
                                                                 config.report_style);

            if (!config_ini->ValueExists(CONFIG_REPORT_STYLE_SECTION, CONFIG_REPORT_STYLE_SCREEN_KEY))
            {
               config_ini->WriteInteger(CONFIG_REPORT_STYLE_SECTION,
                                     CONFIG_REPORT_STYLE_SCREEN_KEY,
                                     config.report_screen);
            }
            else
            {
               config.report_screen = (UTINY)config_ini->ReadInteger(CONFIG_REPORT_STYLE_SECTION,
                                                                     CONFIG_REPORT_STYLE_SCREEN_KEY,
                                                                     config.report_screen);
            }

            if (!config_ini->ValueExists(CONFIG_REPORT_STYLE_SECTION, CONFIG_REPORT_STYLE_PTIV_KEY))
            {
               config_ini->WriteInteger(CONFIG_REPORT_STYLE_SECTION,
                                     CONFIG_REPORT_STYLE_PTIV_KEY,
                                     config.ptiv);
               config_ini->WriteInteger(CONFIG_REPORT_STYLE_SECTION,
                                     CONFIG_REPORT_STYLE_SRRI_KEY,
                                     config.srri);
            }
            else
            {
               config.ptiv = (UTINY)config_ini->ReadInteger(CONFIG_REPORT_STYLE_SECTION,
                                                                     CONFIG_REPORT_STYLE_PTIV_KEY,
                                                                     config.ptiv);
               config.srri = (UTINY)config_ini->ReadInteger(CONFIG_REPORT_STYLE_SECTION,
                                                                     CONFIG_REPORT_STYLE_SRRI_KEY,
                                                                     config.srri);
            }

            if (!config_ini->ValueExists(CONFIG_REPORT_STYLE_SECTION, CONFIG_CLINICAL_AIXHR75_KEY))
            {
               config_ini->WriteBool(CONFIG_REPORT_STYLE_SECTION,
                                  CONFIG_CLINICAL_AIXHR75_KEY,
                                  config.clinical_aixhr75);
               config_ini->WriteBool(CONFIG_REPORT_STYLE_SECTION,
                                  CONFIG_CLINICAL_AIX_KEY,
                                  config.clinical_aix);
            }
            else
            {
               config.clinical_aixhr75 = config_ini->ReadBool(CONFIG_REPORT_STYLE_SECTION,
                                                                     CONFIG_CLINICAL_AIXHR75_KEY,
                                                                     config.clinical_aixhr75);
               config.clinical_aix = config_ini->ReadBool(CONFIG_REPORT_STYLE_SECTION,
                                                                     CONFIG_CLINICAL_AIX_KEY,
                                                                     config.clinical_aix);
            }
         }

         if (!config_ini->SectionExists(CONFIG_DATABASE_PACK_DATE_SECTION))
         {
            config_ini->WriteString(CONFIG_DATABASE_PACK_DATE_SECTION,
                                    CONFIG_DATABASE_PACK_DATE_KEY,
                                    config.last_pack_date);
         }
         else
         {
            config.last_pack_date = config_ini->ReadString(CONFIG_DATABASE_PACK_DATE_SECTION,
                                                           CONFIG_DATABASE_PACK_DATE_KEY,
                                                           config.last_pack_date);
         }

         if (!config_ini->SectionExists(CONFIG_SYSTEM_LOCALE_SECTION))
         {
            config_ini->WriteInteger(CONFIG_SYSTEM_LOCALE_SECTION,
                                    CONFIG_MEASUREMENT_UNITS_KEY,
                                    config.locale);
         }
         else
         {
            config.locale = config_ini->ReadInteger(CONFIG_SYSTEM_LOCALE_SECTION,
                                                           CONFIG_MEASUREMENT_UNITS_KEY,
                                                           config.locale);
         }

         if (!config_ini->SectionExists(CONFIG_REPORT_TITLE_SECTION))
         {
            config_ini->WriteString(CONFIG_REPORT_TITLE_SECTION,
                                    CONFIG_REPORT_TITLE_KEY,
                                    config.report_title);
         }
         else
         {
            config.report_title = config_ini->ReadString(CONFIG_REPORT_TITLE_SECTION,
                                                         CONFIG_REPORT_TITLE_KEY,
                                                         config.report_title);
            if (config.report_title.IsEmpty())
            {
               config.report_title = CONFIG_DEFAULT_REPORT_TITLE;
            }
         }

         if (!config_ini->SectionExists(CONFIG_TONOMETER_SECTION))
         {
            config_ini->WriteInteger(CONFIG_TONOMETER_SECTION,
                                    CONFIG_TONOMETER_KEY,
                                    config.tonometer);
         }
         else
         {
            config.tonometer = config_ini->ReadInteger(CONFIG_TONOMETER_SECTION,
                                                           CONFIG_TONOMETER_KEY,
                                                           config.tonometer);
         }

         if (!config_ini->SectionExists(CONFIG_CAPTURE_STYLE_SECTION))
         {
            config_ini->WriteBool(CONFIG_CAPTURE_STYLE_SECTION,
                                  CONFIG_RTOF_KEY,
                                  config.rtof);
            config_ini->WriteBool(CONFIG_CAPTURE_STYLE_SECTION,
                                  CONFIG_AUTO_CAPTURE_KEY,
                                  config.auto_capture);
         }
         else
         {
            config.rtof = config_ini->ReadBool(CONFIG_CAPTURE_STYLE_SECTION,
                                                 CONFIG_RTOF_KEY,
                                                 config.rtof);

            config.auto_capture = config_ini->ReadBool(CONFIG_CAPTURE_STYLE_SECTION,
                                                       CONFIG_AUTO_CAPTURE_KEY,
                                                       config.auto_capture);
         }
      }
   }
   return (config_initialised);
}

void config_destroy(void)
{
   config.qc_ph = 0;
   config.qc_phv = 0;
   config.qc_dv = 0;
   config.p_upper_limit = 0;
   config.port = COMMS_PORT_ONE;
   config.old_port = COMMS_PORT_ONE;
   config.report_style = 0;
   config.report_screen = 0;
   config.report_title = CONFIG_DEFAULT_REPORT_TITLE;
   config.ptiv = CONFIG_DEFAULT_PTIV;
   config.srri = CONFIG_DEFAULT_SRRI;
   config.locale = CONFIG_DEFAULT_LOCALE;
   config.tonometer = CONFIG_DEFAULT_TONOMETER;

   if (config_options_list != NULL)
   {
      delete config_options_list;
   }

   if (config_ini != NULL)
   {
      delete (config_ini);
   }

   if (config_initialised)
   {
      config_initialised = false;
   }

   if (config_default.port_list != NULL)
   {
      delete config_default.port_list;
   }
}

// PM V9
// Read command line arguments and act on them
void config_decode_command_line(void)
{
   int ParamNo = ParamCount();
   if (ParamNo == 2)
   {
      // The identifier -e is for EMR mode
      if (ParamStr(1) == "-e")
      {
         emr_read_inbound(ParamStr(2));
      }
   }

   // If EMR mode was not enabled at the command line then manually check for an
   // Inbound file.
   if (!emr_get_enabled())
   {
      String inbound_file = emr_get_inbound();
      if (inbound_file != "")
      {
         emr_read_inbound(inbound_file);
      }
   }
}

TStringList *config_get_options_list(void)
{
   return config_options_list;
}

CONFIG_SYSTEM_OPTIONS config_get_system_options(void)
{
   return (config.option);
}

bool config_get_avi_option(void)
{
   return (config.avi_enabled);
}

bool config_get_audit_option(void)
{
   return (config.audit_enabled);
}

void config_set_audit_option(bool audit_option)
{
   config.audit_enabled = audit_option;
}

// PM V9
bool config_get_clinical_option(void)
{
   return (config.clinical_enabled);
}

// PM V9
String config_get_clinical_string(void)
{
   String clinical_string = "";

   if (config.clinical_enabled)
   {
      clinical_string = " (Clinical)";
   }

   return clinical_string;
}

void config_disable_option(CONFIG_SYSTEM_OPTIONS coption)
{
   // Disable the HRV option
   if (coption == CONFIG_HRV_OPTION)
   {
      switch (config.option)
      {
         case CONFIG_HRV_OPTION:
            config.option = CONFIG_PWA_OPTION;
            break;
         case CONFIG_EXTENDED_ALL_OPTION:
            config.option = CONFIG_PWV_OPTION;
            break;
         default:
            break;
      }
   }
}

void config_show(void)
{
   frm_config->ShowModal();
}

UCOUNT config_get_qc_pulse_height(void)
{
   return (config.qc_ph);
}

UTINY config_get_qc_pulse_height_variation(void)
{
   return (config.qc_phv);
}

UTINY config_get_qc_diastolic_variation(void)
{
   return (config.qc_dv);
}

COMMS_ID_TYPE config_get_comms_port(void)
{
   return (config.port);
}

AnsiString config_get_system_id(void)
{
   return (config.system_id);
}

UCOUNT config_get_pressure_upper_limit(void)
{
   return (config.p_upper_limit);
}

UTINY config_get_report_style(void)
{
   return (config.report_style);
}

UTINY config_get_report_screen(void)
{
   return (config.report_screen);
}

AnsiString config_get_report_title(void)
{
   return (config.report_title);
}

UTINY config_get_ptiv(void)
{
   return (config.ptiv);
}

void config_set_ptiv(UTINY ptiv)
{
   config.ptiv = ptiv;
}

UTINY config_get_srri(void)
{
   return (config.srri);
}

UTINY config_get_system_locale(void)
{
   return (config.locale);
}

UINT32 config_get_tonometer(void)
{
   return (config.tonometer);
}

// PM V9
bool config_get_rtof(void)
{
   return (config.rtof);
}

// PM V9
bool config_get_auto_capture(void)
{
   return (config.auto_capture);
}

// PM V9
bool config_get_clinical_aixhr75(void)
{
   return (config.clinical_aixhr75);
}

// PM V9
bool config_get_clinical_aix(void)
{
   return (config.clinical_aix);
}

bool config_require_database_pack(void)
{
   bool       require_pack = false;
   TDateTime  today;
   TDateTime  last_pack;

   today = Date();

   try
   {
      last_pack = StrToDate(config.last_pack_date);
      if ((int)(today - last_pack) >= 90)
      {
         require_pack = true;
      }
   }
   catch (...)
   {
      config_update_database_pack_date();
   }
   return (require_pack);
}

void config_update_database_pack_date(void)
{
   AnsiString today;

   today = DateToStr(Date());
   config.last_pack_date = today;

   if (config_ini->SectionExists(CONFIG_DATABASE_PACK_DATE_SECTION))
   {
      config_ini->WriteString(CONFIG_DATABASE_PACK_DATE_SECTION,
                              CONFIG_DATABASE_PACK_DATE_KEY,
                              config.last_pack_date);
   }
}


bool config_determine_capabilities(void)
{
   int sys_id = 0;
   int offset = 0;
   bool valid_option = false;


   // PM V9
   if (config.system_id != CONFIG_DEFAULT_SYSTEM_ID)
   {
      if (config.capabilities)
      {
         try
         {
            sys_id = StrToInt(config.system_id);
            offset = config.capabilities - sys_id;
            if (offset > 0)
            {
               config.avi_enabled = false;
               config.audit_enabled = false;
               config.clinical_enabled = false;

               switch (offset)
               {
                  case CONFIG_PWA_OFFSET:
                     config.option = CONFIG_PWA_OPTION;
                     valid_option = true;
                     break;
                  case CONFIG_PWA_OFFSET + CONFIG_AUDIT_OFFSET:
                     config.option = CONFIG_PWA_OPTION;
                     config.audit_enabled = true;
                     valid_option = true;
                     break;
                  case CONFIG_PWA_OFFSET + CONFIG_AVI_OFFSET:
                     config.option = CONFIG_PWA_OPTION;
                     config.avi_enabled = true;
                     valid_option = true;
                     break;
                  case CONFIG_PWA_OFFSET + CONFIG_AVI_OFFSET + CONFIG_AUDIT_OFFSET:
                     config.option = CONFIG_PWA_OPTION;
                     config.avi_enabled = true;
                     config.audit_enabled = true;
                     valid_option = true;
                     break;
                  case CONFIG_PWA_OFFSET + CONFIG_CLINICAL_OFFSET:
                     config.option = CONFIG_PWA_OPTION;
                     config.clinical_enabled = true;
                     valid_option = true;
                     break;
                  case CONFIG_PWA_OFFSET + CONFIG_AUDIT_OFFSET + CONFIG_CLINICAL_OFFSET:
                     config.option = CONFIG_PWA_OPTION;
                     config.audit_enabled = true;
                     config.clinical_enabled = true;
                     valid_option = true;
                     break;
                  case CONFIG_PWA_OFFSET + CONFIG_AVI_OFFSET + CONFIG_CLINICAL_OFFSET:
                     config.option = CONFIG_PWA_OPTION;
                     config.avi_enabled = true;
                     config.clinical_enabled = true;
                     valid_option = true;
                     break;
                  case CONFIG_PWA_OFFSET + CONFIG_AVI_OFFSET + CONFIG_AUDIT_OFFSET + CONFIG_CLINICAL_OFFSET:
                     config.option = CONFIG_PWA_OPTION;
                     config.avi_enabled = true;
                     config.audit_enabled = true;
                     config.clinical_enabled = true;
                     valid_option = true;
                     break;
                  case CONFIG_PWV_ONLY_OFFSET:
                     config.option = CONFIG_PWV_ONLY_OPTION;
                     valid_option = true;
                     break;
                  case CONFIG_PWV_ONLY_OFFSET + CONFIG_AUDIT_OFFSET:
                     config.option = CONFIG_PWV_ONLY_OPTION;
                     config.audit_enabled = true;
                     valid_option = true;
                     break;
                  case CONFIG_PWV_ONLY_OFFSET + CONFIG_CLINICAL_OFFSET:
                     config.option = CONFIG_PWV_ONLY_OPTION;
                     config.clinical_enabled = true;
                     valid_option = true;
                     break;
                  case CONFIG_PWV_ONLY_OFFSET + CONFIG_AUDIT_OFFSET + CONFIG_CLINICAL_OFFSET:
                     config.option = CONFIG_PWV_ONLY_OPTION;
                     config.audit_enabled = true;
                     config.clinical_enabled = true;
                     valid_option = true;
                     break;
                  case CONFIG_PWM_ONLY_OFFSET:
                     config.option = CONFIG_PWM_ONLY_OPTION;
                     valid_option = true;
                     break;
                  case CONFIG_HRV_OFFSET:
                     config.option = CONFIG_HRV_OPTION;
                     valid_option = true;
                     break;
                  case CONFIG_HRV_OFFSET + CONFIG_AUDIT_OFFSET:
                     config.option = CONFIG_HRV_OPTION;
                     config.audit_enabled = true;
                     valid_option = true;
                     break;
                  case CONFIG_HRV_OFFSET + CONFIG_AVI_OFFSET:
                     config.option = CONFIG_HRV_OPTION;
                     config.avi_enabled = true;
                     valid_option = true;
                     break;
                  case CONFIG_HRV_OFFSET + CONFIG_AUDIT_OFFSET + CONFIG_AVI_OFFSET:
                     config.option = CONFIG_HRV_OPTION;
                     config.avi_enabled = true;
                     config.audit_enabled = true;
                     valid_option = true;
                     break;
                  case CONFIG_PWV_OFFSET:
                     config.option = CONFIG_PWV_OPTION;
                     valid_option = true;
                     break;
                  case CONFIG_PWV_OFFSET + CONFIG_AUDIT_OFFSET:
                     config.option = CONFIG_PWV_OPTION;
                     config.audit_enabled = true;
                     valid_option = true;
                     break;
                  case CONFIG_PWV_OFFSET + CONFIG_AVI_OFFSET:
                     config.option = CONFIG_PWV_OPTION;
                     config.avi_enabled = true;
                     valid_option = true;
                     break;
                  case CONFIG_PWV_OFFSET + CONFIG_AUDIT_OFFSET + CONFIG_AVI_OFFSET:
                     config.option = CONFIG_PWV_OPTION;
                     config.avi_enabled = true;
                     config.audit_enabled = true;
                     valid_option = true;
                     break;
                  case CONFIG_PWV_OFFSET + CONFIG_CLINICAL_OFFSET:
                     config.option = CONFIG_PWV_OPTION;
                     config.clinical_enabled = true;
                     valid_option = true;
                     break;
                  case CONFIG_PWV_OFFSET + CONFIG_AUDIT_OFFSET + CONFIG_CLINICAL_OFFSET:
                     config.option = CONFIG_PWV_OPTION;
                     config.audit_enabled = true;
                     config.clinical_enabled = true;
                     valid_option = true;
                     break;
                  case CONFIG_PWV_OFFSET + CONFIG_AVI_OFFSET + CONFIG_CLINICAL_OFFSET:
                     config.option = CONFIG_PWV_OPTION;
                     config.avi_enabled = true;
                     config.clinical_enabled = true;
                     valid_option = true;
                     break;
                  case CONFIG_PWV_OFFSET + CONFIG_AUDIT_OFFSET + CONFIG_AVI_OFFSET + CONFIG_CLINICAL_OFFSET:
                     config.option = CONFIG_PWV_OPTION;
                     config.avi_enabled = true;
                     config.audit_enabled = true;
                     config.clinical_enabled = true;
                     valid_option = true;
                     break;
                  case CONFIG_PWM_OFFSET:
                     config.option = CONFIG_PWM_OPTION;
                     valid_option = true;
                     break;
                  case CONFIG_PWM_OFFSET + CONFIG_AUDIT_OFFSET:
                     config.option = CONFIG_PWM_OPTION;
                     config.audit_enabled = true;
                     valid_option = true;
                     break;
                  case CONFIG_PWM_OFFSET + CONFIG_AVI_OFFSET:
                     config.option = CONFIG_PWM_OPTION;
                     config.avi_enabled = true;
                     valid_option = true;
                     break;
                  case CONFIG_PWM_OFFSET + CONFIG_AUDIT_OFFSET + CONFIG_AVI_OFFSET:
                     config.option = CONFIG_PWM_OPTION;
                     config.avi_enabled = true;
                     config.audit_enabled = true;
                     valid_option = true;
                     break;
                  case CONFIG_STANDARD_ALL_OFFSET:
                     config.option = CONFIG_STANDARD_ALL_OPTION;
                     valid_option = true;
                     break;
                  case CONFIG_STANDARD_ALL_OFFSET + CONFIG_AUDIT_OFFSET:
                     config.option = CONFIG_STANDARD_ALL_OPTION;
                     config.audit_enabled = true;
                     valid_option = true;
                     break;
                  case CONFIG_STANDARD_ALL_OFFSET + CONFIG_AVI_OFFSET:
                     config.option = CONFIG_STANDARD_ALL_OPTION;
                     config.avi_enabled = true;
                     valid_option = true;
                     break;
                  case CONFIG_STANDARD_ALL_OFFSET + CONFIG_AUDIT_OFFSET + CONFIG_AVI_OFFSET:
                     config.option = CONFIG_STANDARD_ALL_OPTION;
                     config.avi_enabled = true;
                     config.audit_enabled = true;
                     valid_option = true;
                     break;
                  case CONFIG_EXTENDED_ALL_OFFSET:
                     config.option = CONFIG_EXTENDED_ALL_OPTION;
                     valid_option = true;
                     break;
                  case CONFIG_EXTENDED_ALL_OFFSET + CONFIG_AUDIT_OFFSET:
                     config.option = CONFIG_EXTENDED_ALL_OPTION;
                     config.audit_enabled = true;
                     valid_option = true;
                     break;
                  case CONFIG_EXTENDED_ALL_OFFSET + CONFIG_AVI_OFFSET:
                     config.option = CONFIG_EXTENDED_ALL_OPTION;
                     config.avi_enabled = true;
                     valid_option = true;
                     break;
                  case CONFIG_EXTENDED_ALL_OFFSET + CONFIG_AUDIT_OFFSET + CONFIG_AVI_OFFSET:
                     config.option = CONFIG_EXTENDED_ALL_OPTION;
                     config.avi_enabled = true;
                     config.audit_enabled = true;
                     valid_option = true;
                     break;
                  default:
                     config.option = CONFIG_PWA_OPTION;
                     break;
               }
            }
         }
         catch (...)
         {
            ;
         }
      }
   }

   config_options_list = new TStringList;

   switch (config.option)
   {
      case CONFIG_PWA_OPTION:
         config_options_list->Add("PWA");
         break;
      case CONFIG_PWV_OPTION:
         config_options_list->Add("PWA");
         config_options_list->Add("PWV");
         break;
      case CONFIG_HRV_OPTION:
         config_options_list->Add("PWA");
         config_options_list->Add("HRV");
         break;
      case CONFIG_PWV_ONLY_OPTION:
         config_options_list->Add("PWV");
         break;
      case CONFIG_PWM_ONLY_OPTION:
         config_options_list->Add("PWM");
         break;
      case CONFIG_PWM_OPTION:
         config_options_list->Add("PWA");
         config_options_list->Add("PWM");
         break;
      case CONFIG_STANDARD_ALL_OPTION:
         config_options_list->Add("PWA");
         config_options_list->Add("PWV");
         config_options_list->Add("PWM");
         break;
      case CONFIG_EXTENDED_ALL_OPTION:
         config_options_list->Add("PWA");
         config_options_list->Add("PWV");
         config_options_list->Add("HRV");
         break;
      default:
         config_options_list->Add("PWA");
         break;
   }
   return (valid_option);
}

UINT16 config_check_system_id(AnsiString str)
{
   int     i, j;
   UINT16  check_sum;
   UINT8   byte;

   check_sum = 0;
   for (i = 0; i < str.Length(); i++)
   {
      byte = str[i + 1];
      for (j = 1; j <= 8; j++)
      {
         if ((byte & 1) != (check_sum & 1))
         {
            check_sum = (UINT16)((check_sum / 2) ^ 0xA001);
         }
         else
         {
            check_sum = (UINT16)(check_sum / 2);
         }
         byte = (UINT8)(byte / 2);
      }
   }
   return check_sum;
}

void __fastcall Tfrm_config::edt_qcphChange(TObject *Sender)
{
   if (edt_qcph->Text.ToIntDef(-1) <= 0)
   {
      edt_qcph->Text = "";
   }
}
//---------------------------------------------------------------------------
void __fastcall Tfrm_config::edt_qcphvChange(TObject *Sender)
{
  if (edt_qcphv->Text.ToIntDef(-1) <= 0)
    edt_qcphv->Text = "";
}
//---------------------------------------------------------------------------
void __fastcall Tfrm_config::edt_qcdvChange(TObject *Sender)
{
  if (edt_qcdv->Text.ToIntDef(-1) <= 0)
    edt_qcdv->Text = "";
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_config::edt_p_upper_limitChange(TObject *Sender)
{
   if (edt_p_upper_limit->Text.ToIntDef(-1) <= 0)
   {
      edt_p_upper_limit->Text = "";
   }
}
//---------------------------------------------------------------------------

bool config_enable_ports(void)
{
   int          i;
   String       port;
   int          port_number;
   bool         ports_available = false;

   // Detect the ports everytime the config form is shown
   config_default.port_list->Clear();
   comms_detect_ports(config_default.port_list);

   // Add the detected ports to the combobox.
   if (config.port_list->Count != 0)
   {
      for (i=0; i<config.port_list->Count; i++)
      {
         port = config.port_list->Strings[i];
         frm_config->cmbx_comports->Items->AddObject("COM " + port, (TObject *)(COMMS_ID_TYPE)port.ToInt());
      }
      ports_available = true;
   }

   // Always add Simulation to the combobox.
   //frm_config->cmbx_comports->Items->AddObject("USB", (TObject *)COMMS_PORT_USB);
   frm_config->cmbx_comports->Items->AddObject("Simulation", (TObject *)COMMS_PORT_SIMULATE);
   return ports_available;
}


void __fastcall Tfrm_config::FormClose(TObject *Sender,
      TCloseAction &Action)
{
   cmbx_comports->Items->Clear();
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_config::cmbx_comportsChange(TObject *Sender)
{
   int index = cmbx_comports->ItemIndex;
   if((COMMS_ID_TYPE) cmbx_comports->Items->Objects[index] == COMMS_PORT_SIMULATE)
   {
      btn_select_dir->Visible = true;
   }

}
//---------------------------------------------------------------------------

void __fastcall Tfrm_config::btn_select_dirClick(TObject *Sender)
{
   String directory;
   if (emma_select_dir(this, "Simulation Directory", directory))
   {
      //validate directory
      if (config_validate_directory(directory))
      {
         simulation_directory = directory;
      }
   }
}
//---------------------------------------------------------------------------

bool config_validate_directory(String directory)
{
   bool valid = true;

   MEAS_ID_TYPE  study_mode;

   // Only check for the simulation file required for the current measurement mode
   study_mode = patient_get_study_mode();
   switch (study_mode)
   {
      case MEAS_PWA_ID:
         if (!FileExists(directory + "\\" + CONFIG_PWA_SIMULATE))
         {
            MsgBox(LoadStr(MSG_COMMS_NO_FILE) + CONFIG_PWA_SIMULATE + "\n\n" +
               LoadStr(MSG_CONFIG_CHECK_FILENAME) + directory, SWARNING, MB_ICONSTOP);
            valid = false;
         }
         break;
      case MEAS_PWV_ID:
         if (!FileExists(directory + "\\" + CONFIG_PWV_SITEA_SIMULATE))
         {
            MsgBox(LoadStr(MSG_COMMS_NO_FILE) + CONFIG_PWV_SITEA_SIMULATE + "\n\n" +
               LoadStr(MSG_CONFIG_CHECK_FILENAME) + directory, SWARNING, MB_ICONSTOP);
            valid = false;
         }
         if (!FileExists(directory + "\\" + CONFIG_PWV_SITEB_SIMULATE))
         {
            MsgBox(LoadStr(MSG_COMMS_NO_FILE) + CONFIG_PWV_SITEB_SIMULATE + "\n\n" +
            LoadStr(MSG_CONFIG_CHECK_FILENAME) + directory, SWARNING, MB_ICONSTOP);
            valid = false;
         }
         break;
      case MEAS_PWM_ID:
         if (!FileExists(directory + "\\" + CONFIG_PWM_SIMULATE))
         {
            MsgBox(LoadStr(MSG_COMMS_NO_FILE) + CONFIG_PWM_SIMULATE + "\n\n" +
               LoadStr(MSG_CONFIG_CHECK_FILENAME) + directory, SWARNING, MB_ICONSTOP);
            valid = false;
         }
         break;
      case MEAS_HRV_ID:
         if (!FileExists(directory + "\\" + CONFIG_HRV_SIMULATE))
         {
            MsgBox(LoadStr(MSG_COMMS_NO_FILE) + CONFIG_HRV_SIMULATE + "\n\n" +
               LoadStr(MSG_CONFIG_CHECK_FILENAME) + directory, SWARNING, MB_ICONSTOP);
            valid = false;
         }
         break;
   }
   return valid;
}

String config_get_simulation_directory(void)
{
   return (simulation_directory);
}

void __fastcall Tfrm_config::chkbx_detailedClick(TObject *Sender)
{
   if (chkbx_detailed->Checked)
   {
      chkbx_clinical->Checked = false;
   }
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_config::chkbx_clinicalClick(TObject *Sender)
{
   if (chkbx_clinical->Checked)
   {
      chkbx_detailed->Checked = false;
   }
}
//---------------------------------------------------------------------------



void __fastcall Tfrm_config::chkbx_blind_studyClick(TObject *Sender)
{
   if (chkbx_blind_study->Checked)
   {
      chkbx_clinical_aixhr75->Checked = false;
      chkbx_clinical_aix->Checked = false;
      chkbx_clinical_aixhr75->Enabled = false;
      chkbx_clinical_aix->Enabled = false;
   }
   else
   {
      chkbx_clinical_aixhr75->Enabled = true;
      chkbx_clinical_aix->Enabled = true;
   }
}
//---------------------------------------------------------------------------
// PM V9
bool config_find_module(void)
{
   bool     success = false;
   String   port_string;

   // Check the current port first
   if (config.port != COMMS_PORT_SIMULATE)
   {
      if (comms_open(config.port, true))
      {
         comms_detect_module();
         if (comms_is_module_available())
         {
            return true;
         }
         comms_close();
      }
   }

   // Detect the ports everytime
   config_default.port_list->Clear();
   comms_detect_ports(config_default.port_list);

   config.old_port = config.port;

   if (config.port_list->Count != 0)
   {
      // Prepare progress bar
      frm_main->prgbar_main->Visible = true;
      frm_main->prgbar_main->Min = 0;
      frm_main->prgbar_main->Max = config.port_list->Count;
      frm_main->prgbar_main->Step = 1;
      frm_main->prgbar_main->Position = 0;

      // Try to detect a module at each port in the available list
      // BUG - If there are many ports, the second time this is run, some ports
      // will give the error "Comm Port in use or unavailable". Adding Sleeps
      // did not help.
      int i = 0;
      while(!success && i < config.port_list->Count)
      {
         Application->ProcessMessages();
         //Sleep(1000);
         port_string = config.port_list->Strings[i];
         config.port = (COMMS_ID_TYPE) port_string.ToInt();
         if (comms_open(config.port, true))
         {
            comms_detect_module();
            if (comms_is_module_available())
            {
               success = true;
            }
            //Sleep(1000);
            comms_close();
         }
         frm_main->prgbar_main->Position = i++;
      }
      frm_main->prgbar_main->Visible = false;
   }

   // if a module was found, write it to the configuration file
   if (success)
   {
      if (config_ini->SectionExists(CONFIG_COMMS_SECTION))
      {
         config_ini->WriteInteger(CONFIG_COMMS_SECTION,
                                  CONFIG_COMMS_PORT_KEY,
                                  config.port);
      }
   }
   // Otherwise, revert to the previous port
   else
   {
      config.port = config.old_port;
   }
   return success;
}

