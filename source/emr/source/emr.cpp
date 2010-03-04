//---------------------------------------------------------------------------
// PM V9
#include <vcl.h>
#pragma hdrstop

#include <Inifiles.hpp>
#include <emr/pubserv.h>
#include <log/pubserv.h>
#include <msg/pubserv.h>
#include <patient/pubserv.h>
#include <config/pubserv.h>
#include <meas/pubserv.h>
#include <scor/utils.h>
#include <scor/form_main.h>
#include "emr.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)

const String EMR_OUTBOUND_DEFAULT_DIRECTORY =   "EMROUTPUT\\";

const String EMR_INBOUND_DEFAULT_FILENAME =     "INBOUND.INI";

const String EMR_REQUIRED_SECTION =             "REQUIRED";
const String EMR_REQUIRED_SYSTEM_KEY =          "SYSTEMID";
const String EMR_REQUIRED_LAST_NAME_KEY =       "LASTNAME";
const String EMR_REQUIRED_FIRST_NAME_KEY =      "FIRSTNAME";
const String EMR_REQUIRED_DOB_KEY =             "DOB";
const String EMR_REQUIRED_SEX_KEY =             "SEX";

const String EMR_PATIENT_SECTION =              "PATIENT";
const String EMR_PATIENT_ID_KEY =               "PATIENTID";
const String EMR_PATIENT_OTHER_NAME_KEY =       "OTHERNAME";
const String EMR_PATIENT_STREET_KEY =           "STREET";
const String EMR_PATIENT_TOWN_KEY =             "TOWN";
const String EMR_PATIENT_STATE_KEY =            "STATE";
const String EMR_PATIENT_POSTCODE_KEY =         "POSTCODE";
const String EMR_PATIENT_COUNTRY_KEY =          "COUNTRY";
const String EMR_PATIENT_PHONENO_KEY =          "PHONENO";
const String EMR_PATIENT_CODE_KEY =             "CODE";
const String EMR_PATIENT_NOTES_KEY =            "PATIENTNOTES";
const String EMR_PATIENT_EDITING_KEY =          "EDITING";

const String EMR_STUDY_SECTION =                "STUDY";
const String EMR_STUDY_SP_KEY =                 "SP";
const String EMR_STUDY_MP_KEY =                 "MP";
const String EMR_STUDY_DP_KEY =                 "DP";
const String EMR_STUDY_HEIGHT_KEY =             "HEIGHT";
const String EMR_STUDY_FEET_KEY =               "FEET";
const String EMR_STUDY_INCH_KEY =               "INCH";
const String EMR_STUDY_WEIGHT_KEY =             "WEIGHT";
const String EMR_STUDY_POUND_KEY =              "POUND";
const String EMR_STUDY_MEDICATION_KEY =         "MEDICATION";
const String EMR_STUDY_NOTES_KEY =              "STUDYNOTES";
const String EMR_STUDY_OPERATOR_KEY =           "OPERATOR";

const String EMR_EXPORT_SECTION =               "EXPORT";
const String EMR_EXPORT_OUTBOUND_KEY =          "OUTBOUND";
const String EMR_EXPORT_OPTION_KEY =            "OPTION";
const String EMR_EXPORT_AUTOMATIC_KEY =         "AUTOMATIC";
const String EMR_EXPORT_SHUTDOWN_KEY =          "SHUTDOWN";
const String EMR_EXPORT_PRINTER_KEY =           "PRINTER";

EMR_RECORD_TYPE   emr_active;
EMR_RECORD_TYPE   emr_default;
bool              emr_initialised;
bool              emr_enabled;
bool              emr_default_mode;
bool              emr_report_export;
TIniFile          *emr_ini;

String            EMR_INIT_DATE;
String            outbound_default;

/* ###########################################################################
// initialise variables
*/
bool emr_initialise(void)
{
   emr_set_defaults();
   emr_reset_active_record();
   emr_initialised = true;
   return emr_initialised;
}

/* ###########################################################################
// Cleanup variables
*/
void emr_destroy(void)
{
   if (emr_ini != NULL)
   {
      delete (emr_ini);
   }

   if (emr_initialised)
   {
      emr_initialised = false;
   }
}

/* ###########################################################################
// Set default values
*/
void emr_set_defaults(void)
{
   // Default inbound location is in the program directory
   // Default system id and dob are the same as the Patient object
   EMR_INIT_DATE = emma_build_country_date("01", "01", "1850");

   // Inbound is a filename
   emr_default.inbound = ExtractFilePath(ParamStr(0)) + EMR_INBOUND_DEFAULT_FILENAME;
   emr_default.system_id = PATIENT_INIT_SYSTEMID;
   emr_default.surname = "";
   emr_default.first_name = "";
   emr_default.dob = StrToDate(EMR_INIT_DATE);
   emr_default.sex = "";
   emr_default.patient_id = "";
   emr_default.other_name = "";
   emr_default.street = "";
   emr_default.suburb = "";
   emr_default.state = "";
   emr_default.pcode = "";
   emr_default.country = "";
   emr_default.phone = "";
   emr_default.code = "";
   emr_default.patient_notes = "";
   emr_default.editing = false;
   emr_default.sp = DEFAULT_VALUE;
   emr_default.mp = DEFAULT_VALUE;
   emr_default.dp = DEFAULT_VALUE;
   emr_default.height = DEFAULT_VALUE;
   emr_default.feet = DEFAULT_VALUE;
   emr_default.inch = DEFAULT_VALUE;
   emr_default.weight = DEFAULT_VALUE;
   emr_default.pound = DEFAULT_VALUE;
   emr_default.medication = "";
   emr_default.study_notes = "";
   emr_default.operator_name = "";
   // Outbound is a directory
   emr_default.outbound = ExtractFilePath(ParamStr(0)) + EMR_OUTBOUND_DEFAULT_DIRECTORY;
   emr_default.option = EMR_STANDARD;
   emr_default.automatic = false;
   emr_default.shutdown = false;
   emr_default.printer = "Adobe PDF";

   emr_enabled = false;
   emr_default_mode = false;
   emr_report_export = false;
   outbound_default = emr_default.outbound;
}

/* ###########################################################################
// Set the active emr record to the default values
*/
void emr_reset_active_record(void)
{
   emr_active = emr_default;
}

/* ###########################################################################
 ** emr_read_inbound(String inbound)
 **
 ** DESCRIPTION
 **  Reads the Inbound File and Populates the EMR Record
 ** INPUT
 **  Inbound filename String
 ** OUTPUT
 **  Sets EMR Default Mode to True or False
 ** RETURN
 **  True
*/
//---------------------------------------------------------------------------
bool emr_read_inbound(String inbound)
{
   // The presence of an inbound file will enable the EMR object, unless CFR11 is enabled
   if (config_get_audit_option())
   {
      MsgBox_show(TERROR,
                  MSG_EMR_ERROR,
                  LoadStr(MSG_EMR_CFR11),
                  MSG_EMR_CFR11,
                  LoadStr(MSG_EMR_CFR11));
      emr_enabled = false;
      return emr_enabled;
   }
   else
   {
      emr_enabled = true;
   }

   // The default outbound directory is a new folder with the same name as the Inbound file
   outbound_default = ExtractFileName(inbound);
   outbound_default = ChangeFileExt(outbound_default, "");
   emr_default.outbound = ExtractFilePath(ParamStr(0)) + EMR_OUTBOUND_DEFAULT_DIRECTORY + outbound_default + "\\";

   // If the inbound file cannot be found, or any part of the required section is
   // missing, the EMR object will be placed in Default Mode
   if (FileExists(inbound))
   {
      emr_active.inbound = inbound;
      emr_ini = new TIniFile(inbound);
      if (emr_ini != NULL)
      {
         // Populate the Required values, if they exist
         if (!emr_ini->SectionExists(EMR_REQUIRED_SECTION))
         {
            emr_default_mode = true;
            MsgBox_show(TERROR,
                        MSG_EMR_ERROR,
                        LoadStr(MSG_EMR_NO_REQUIRED_SECTION),
                        MSG_EMR_NO_REQUIRED_SECTION,
                        LoadStr(MSG_EMR_NO_REQUIRED_SECTION));
         }
         else
         {
            if (!emr_ini->ValueExists(EMR_REQUIRED_SECTION, EMR_REQUIRED_SYSTEM_KEY))
            {
               emr_default_mode = true;
               MsgBox_show(TERROR,
                           MSG_EMR_ERROR,
                           LoadStr(MSG_EMR_NO_SYSTEM_ID),
                           MSG_EMR_NO_SYSTEM_ID,
                           LoadStr(MSG_EMR_NO_SYSTEM_ID));
            }
            else
            {
               emr_active.system_id = emr_ini->ReadString(EMR_REQUIRED_SECTION,
                                                         EMR_REQUIRED_SYSTEM_KEY,
                                                         emr_default.system_id);
            }
            if (!emr_ini->ValueExists(EMR_REQUIRED_SECTION, EMR_REQUIRED_LAST_NAME_KEY))
            {
               emr_default_mode = true;
               MsgBox_show(TERROR,
                           MSG_EMR_ERROR,
                           LoadStr(MSG_EMR_NO_LAST_NAME),
                           MSG_EMR_NO_LAST_NAME,
                           LoadStr(MSG_EMR_NO_LAST_NAME));
            }
            else
            {
               emr_active.surname = emr_ini->ReadString(EMR_REQUIRED_SECTION,
                                                         EMR_REQUIRED_LAST_NAME_KEY,
                                                         emr_default.surname);
            }
            if (!emr_ini->ValueExists(EMR_REQUIRED_SECTION, EMR_REQUIRED_FIRST_NAME_KEY))
            {
               emr_default_mode = true;
               MsgBox_show(TERROR,
                           MSG_EMR_ERROR,
                           LoadStr(MSG_EMR_NO_FIRST_NAME),
                           MSG_EMR_NO_FIRST_NAME,
                           LoadStr(MSG_EMR_NO_FIRST_NAME));
            }
            else
            {
               emr_active.first_name = emr_ini->ReadString(EMR_REQUIRED_SECTION,
                                                         EMR_REQUIRED_FIRST_NAME_KEY,
                                                         emr_default.first_name);
            }
            if (!emr_ini->ValueExists(EMR_REQUIRED_SECTION, EMR_REQUIRED_DOB_KEY))
            {
               emr_default_mode = true;
               MsgBox_show(TERROR,
                           MSG_EMR_ERROR,
                           LoadStr(MSG_EMR_NO_DOB),
                           MSG_EMR_NO_DOB,
                           LoadStr(MSG_EMR_NO_DOB));
            }
            else
            {
               emr_active.dob = emr_ini->ReadDateTime(EMR_REQUIRED_SECTION,
                                                         EMR_REQUIRED_DOB_KEY,
                                                         emr_default.dob);
            }
            if (!emr_ini->ValueExists(EMR_REQUIRED_SECTION, EMR_REQUIRED_SEX_KEY))
            {
               emr_default_mode = true;
               MsgBox_show(TERROR,
                           MSG_EMR_ERROR,
                           LoadStr(MSG_EMR_NO_SEX),
                           MSG_EMR_NO_SEX,
                           LoadStr(MSG_EMR_NO_SEX));
            }
            else
            {
               emr_active.sex = emr_ini->ReadString(EMR_REQUIRED_SECTION,
                                                         EMR_REQUIRED_SEX_KEY,
                                                         emr_default.sex);
            }
         }

         // If all the required values were found, continue to populate the EMR Record
         // Any values that are not found will be populated with the default value
         if (!emr_default_mode)
         {
            if (emr_ini->SectionExists(EMR_PATIENT_SECTION))
            {
               emr_active.patient_id = emr_ini->ReadString(EMR_PATIENT_SECTION,
                                                            EMR_PATIENT_ID_KEY,
                                                            emr_default.patient_id);
               emr_active.other_name = emr_ini->ReadString(EMR_PATIENT_SECTION,
                                                            EMR_PATIENT_OTHER_NAME_KEY,
                                                            emr_default.other_name);
               emr_active.street = emr_ini->ReadString(EMR_PATIENT_SECTION,
                                                            EMR_PATIENT_STREET_KEY,
                                                            emr_default.street);
               emr_active.suburb = emr_ini->ReadString(EMR_PATIENT_SECTION,
                                                            EMR_PATIENT_TOWN_KEY,
                                                            emr_default.suburb);
               emr_active.state = emr_ini->ReadString(EMR_PATIENT_SECTION,
                                                            EMR_PATIENT_STATE_KEY,
                                                            emr_default.state);
               emr_active.pcode = emr_ini->ReadString(EMR_PATIENT_SECTION,
                                                            EMR_PATIENT_POSTCODE_KEY,
                                                            emr_default.pcode);
               emr_active.country = emr_ini->ReadString(EMR_PATIENT_SECTION,
                                                            EMR_PATIENT_COUNTRY_KEY,
                                                            emr_default.country);
               emr_active.phone = emr_ini->ReadString(EMR_PATIENT_SECTION,
                                                            EMR_PATIENT_PHONENO_KEY,
                                                            emr_default.phone);
               emr_active.code = emr_ini->ReadString(EMR_PATIENT_SECTION,
                                                            EMR_PATIENT_CODE_KEY,
                                                            emr_default.code);
               emr_active.patient_notes = emr_ini->ReadString(EMR_PATIENT_SECTION,
                                                            EMR_PATIENT_NOTES_KEY,
                                                            emr_default.patient_notes);
               emr_active.editing = emr_ini->ReadBool(EMR_PATIENT_SECTION,
                                                            EMR_PATIENT_EDITING_KEY,
                                                            emr_default.editing);
            }

            if (emr_ini->SectionExists(EMR_STUDY_SECTION))
            {
               emr_active.sp = emr_ini->ReadInteger(EMR_STUDY_SECTION,
                                                            EMR_STUDY_SP_KEY,
                                                            emr_default.sp);
               emr_active.mp = emr_ini->ReadInteger(EMR_STUDY_SECTION,
                                                            EMR_STUDY_MP_KEY,
                                                            emr_default.mp);
               emr_active.dp = emr_ini->ReadInteger(EMR_STUDY_SECTION,
                                                            EMR_STUDY_DP_KEY,
                                                            emr_default.dp);
               emr_active.height = emr_ini->ReadInteger(EMR_STUDY_SECTION,
                                                            EMR_STUDY_HEIGHT_KEY,
                                                            emr_default.height);
               emr_active.feet = emr_ini->ReadInteger(EMR_STUDY_SECTION,
                                                            EMR_STUDY_FEET_KEY,
                                                            emr_default.feet);
               emr_active.inch = emr_ini->ReadInteger(EMR_STUDY_SECTION,
                                                            EMR_STUDY_INCH_KEY,
                                                            emr_default.inch);
               emr_active.weight = emr_ini->ReadInteger(EMR_STUDY_SECTION,
                                                            EMR_STUDY_WEIGHT_KEY,
                                                            emr_default.weight);
               emr_active.pound = emr_ini->ReadInteger(EMR_STUDY_SECTION,
                                                            EMR_STUDY_POUND_KEY,
                                                            emr_default.pound);
               emr_active.medication = emr_ini->ReadString(EMR_STUDY_SECTION,
                                                            EMR_STUDY_MEDICATION_KEY,
                                                            emr_default.medication);
               emr_active.study_notes = emr_ini->ReadString(EMR_STUDY_SECTION,
                                                            EMR_STUDY_NOTES_KEY,
                                                            emr_default.study_notes);
               emr_active.operator_name = emr_ini->ReadString(EMR_STUDY_SECTION,
                                                            EMR_STUDY_OPERATOR_KEY,
                                                            emr_default.operator_name);
            }

            if (emr_ini->SectionExists(EMR_EXPORT_SECTION))
            {
               emr_active.outbound = emr_ini->ReadString(EMR_EXPORT_SECTION,
                                                            EMR_EXPORT_OUTBOUND_KEY,
                                                            emr_default.outbound);
               emr_active.option = (EMR_EXPORT_TYPE) emr_ini->ReadInteger(EMR_EXPORT_SECTION,
                                                            EMR_EXPORT_OPTION_KEY,
                                                            emr_default.option);
               emr_active.automatic = emr_ini->ReadBool(EMR_EXPORT_SECTION,
                                                            EMR_EXPORT_AUTOMATIC_KEY,
                                                            emr_default.automatic);
               emr_active.shutdown = emr_ini->ReadBool(EMR_EXPORT_SECTION,
                                                            EMR_EXPORT_SHUTDOWN_KEY,
                                                            emr_default.shutdown);
               emr_active.printer = emr_ini->ReadString(EMR_EXPORT_SECTION,
                                                            EMR_EXPORT_PRINTER_KEY,
                                                            emr_default.printer);
            }

            // If the EMR Record is not validated - enable Default Mode
            if (!emr_validate())
            {
               emr_default_mode = true;
            }
         }
      }
      else
      {
         emr_default_mode = true;
         MsgBox_show(TERROR,
                     MSG_EMR_ERROR,
                     LoadStr(MSG_EMR_NO_INI_FILE),
                     MSG_EMR_NO_INI_FILE,
                     LoadStr(MSG_EMR_NO_INI_FILE));
      }
   }
   else
   {
      emr_default_mode = true;
      MsgBox_show(TERROR,
                  MSG_EMR_ERROR,
                  LoadStr(MSG_EMR_NO_INBOUND_FILE),
                  MSG_EMR_NO_INBOUND_FILE,
                  LoadStr(MSG_EMR_NO_INBOUND_FILE));
   }

   // If Default Mode was enabled, reset the active record and inform the user
   // where their results will be exported
   if (emr_default_mode)
   {
      emr_reset_active_record();
      MsgBox_show(TERROR,
                  MSG_EMR_ERROR,
                  LoadStr(MSG_EMR_DEFAULT_MODE) + emr_active.outbound,
                  MSG_EMR_DEFAULT_MODE,
                  LoadStr(MSG_EMR_DEFAULT_MODE) + emr_active.outbound);
   }

   return emr_enabled;
}

/* ###########################################################################
 ** emr_validate()
 **
 ** DESCRIPTION
 **  Validates the EMR object
 ** INPUT
 **  None
 ** OUTPUT
 **  None
 ** RETURN
 **  Boolean - if the required values were successful or not
*/
//---------------------------------------------------------------------------
bool emr_validate(void)
{
   bool        valid = true;
   bool        spmpdp = true;
   String      config_system_id;
   TDateTime   min_dob;
   TDateTime   max_dob;
   String      message;
   String      dest_path;
   String      default_path;
   String      exe_path;

   // EMR System ID must match the Config System ID
   config_system_id = config_get_system_id();
   if (emr_active.system_id.AnsiCompare(config_system_id) != 0)
   {
      valid = false;
      MsgBox_show(TERROR,
                  MSG_EMR_ERROR,
                  LoadStr(MSG_EMR_SYSTEM_ID_ERROR),
                  MSG_EMR_SYSTEM_ID_ERROR,
                  LoadStr(MSG_EMR_SYSTEM_ID_ERROR));
   }

   // EMR Surname and First Name must be alphabetic only
   if (!IsStringAlpha(emr_active.surname, emr_active.surname.Length()))
   {
      valid = false;
      MsgBox_show(TERROR,
                  MSG_EMR_ERROR,
                  LoadStr(MSG_EMR_LAST_NAME_ERROR),
                  MSG_EMR_LAST_NAME_ERROR,
                  LoadStr(MSG_EMR_LAST_NAME_ERROR));
   }
   if (!IsStringAlpha(emr_active.first_name, emr_active.first_name.Length()))
   {
      valid = false;
      MsgBox_show(TERROR,
                  MSG_EMR_ERROR,
                  LoadStr(MSG_EMR_FIRST_NAME_ERROR),
                  MSG_EMR_FIRST_NAME_ERROR,
                  LoadStr(MSG_EMR_FIRST_NAME_ERROR));
   }

   // EMR DOB must be readable and within the defined range
   min_dob = StrToDate(EMR_INIT_DATE);
   max_dob = Date();
   if (emr_active.dob <= min_dob || emr_active.dob >= max_dob)
   {
      valid = false;
      MsgBox_show(TERROR,
                  MSG_EMR_ERROR,
                  LoadStr(MSG_EMR_DOB_ERROR),
                  MSG_EMR_DOB_ERROR,
                  LoadStr(MSG_EMR_DOB_ERROR));
   }

   // EMR Sex must be male or female only. If you're unsure, just choose one :-)
   if (emr_active.sex.AnsiCompareIC("male") != 0 && emr_active.sex.AnsiCompareIC("female") != 0)
   {
      valid = false;
      MsgBox_show(TERROR,
                  MSG_EMR_ERROR,
                  LoadStr(MSG_EMR_SEX_ERROR),
                  MSG_EMR_SEX_ERROR,
                  LoadStr(MSG_EMR_SEX_ERROR));
   }

   // Validate EMR pressures
   // If DP was found, it must be within the defined range
   if (emr_active.dp != DEFAULT_VALUE)
   {
      if((emr_active.dp <= MIN_DP) || (emr_active.dp >= MAX_SP))
      {
         message = ".  Allowable Range [" +IntToStr(MIN_DP) +", " +IntToStr(MAX_SP) +"] ";
         MsgBox_show(TWARNING,
                     MSG_EMR_ERROR,
                     LoadStr(MSG_EMR_DP_OUT) + IntToStr(emr_active.dp) + message,
                     MSG_EMR_DP_OUT, "");
         spmpdp = false;
      }
      // If SP was found, MP will be ignored as only one should have a value.
      // SP must be greater than DP, less than the maximum and not produce a
      // pulse pressure less than the minimum
      else if (emr_active.sp != DEFAULT_VALUE)
      {
         if ((emr_active.sp <= emr_active.dp) || (emr_active.sp >= MAX_SP))
         {
            message = ".  Allowable Range [" +IntToStr(emr_active.dp) +", " +IntToStr(MAX_SP) +"] ";
            MsgBox_show(TWARNING,
                        MSG_EMR_ERROR,
                        LoadStr(MSG_EMR_SP_OUT) + IntToStr(emr_active.sp) + message,
                        MSG_EMR_SP_OUT, "");
            spmpdp = false;
         }
         else if (emr_active.sp - emr_active.dp < PWA_MIN_PRESSURE_PULSE_HEIGHT)
         {
            message = ".  Allowable Range [>" + IntToStr(PWA_MIN_PRESSURE_PULSE_HEIGHT) + "] ";
            MsgBox_show(TWARNING,
                        MSG_EMR_ERROR,
                        LoadStr(MSG_EMR_PH_TOO_SMALL) + IntToStr(emr_active.sp - emr_active.dp) + message,
                        MSG_EMR_PH_TOO_SMALL, "");
            spmpdp = false;
         }
         else
         {
            emr_active.mp = emr_default.mp;
         }
      }
      // If MP was found and SP was not, then MP must be greater than DP, less
      // than the maximum and not produce a pulse pressure less than the minimum
      else if (emr_active.mp != DEFAULT_VALUE)
      {
         if ((emr_active.mp <= emr_active.dp) || (emr_active.mp >= MAX_SP))
         {
            message = ".  Allowable Range [" +IntToStr(emr_active.dp) +", " +IntToStr(MAX_SP) +"] ";
            MsgBox_show(TWARNING,
                        MSG_EMR_ERROR,
                        LoadStr(MSG_EMR_MP_OUT) + IntToStr(emr_active.mp) + message,
                        MSG_EMR_MP_OUT, "");
            spmpdp = false;
         }
         else if (emr_active.mp - emr_active.dp < PWA_MIN_PRESSURE_PULSE_HEIGHT / 2)
         {
            message = ".  Allowable Range [>" + IntToStr(PWA_MIN_PRESSURE_PULSE_HEIGHT / 2) + "] ";
            MsgBox_show(TWARNING,
                        MSG_EMR_ERROR,
                        LoadStr(MSG_EMR_PH_TOO_SMALL) + IntToStr(emr_active.mp - emr_active.dp) + message,
                        MSG_EMR_PH_TOO_SMALL, "");
            spmpdp = false;
         }
      }
      // If neither SP or MP were found, pressure validation will fail
      else
      {
         MsgBox_show(TWARNING,
                     MSG_EMR_ERROR,
                     LoadStr(MSG_EMR_NO_SPMP),
                     MSG_EMR_NO_SPMP, "");
         spmpdp = false;
      }
   }
   else
   {
      spmpdp = false;
   }

   // If pressure validation failed, the pressures will be set to the default values
   if (!spmpdp)
   {
      emr_active.sp = emr_default.sp;
      emr_active.mp = emr_default.mp;
      emr_active.dp = emr_default.dp;
   }

   // If Height has a value, then the Feet and Inch fields in the Inbound file are ignored
   if (emr_active.height != DEFAULT_VALUE)
   {
      // Height must be within the defined range
      if (emr_active.height < MIN_HEIGHT || emr_active.height > MAX_HEIGHT)
      {
         message = ".  Allowable Range [" +IntToStr(MIN_HEIGHT) +", " +IntToStr(MAX_HEIGHT) +"] ";
         MsgBox_show(TWARNING,
                    MSG_EMR_ERROR,
                    LoadStr(MSG_EMR_HT_OUT) +IntToStr(emr_active.height) + "cm" + message,
                    MSG_EMR_HT_OUT, "");

         // If the height is not valid, set the defaults
         emr_active.height = emr_default.height;
         emr_active.feet = emr_default.feet;
         emr_active.inch = emr_default.inch;
      }
      else
      {
         // If the Metric height is valid, then calculate the Imperial values
         int temp = math_Round(emr_active.height / CONVERT_INCH_TO_CM);
         emr_active.inch = temp % 12;
         emr_active.feet = temp / 12;
      }
   }
   else if (emr_active.feet != DEFAULT_VALUE && emr_active.inch != DEFAULT_VALUE)
   {
      // Feet and Inch must be within the defined range
      if (emr_active.feet < MIN_FEET || emr_active.feet > MAX_FEET ||
         emr_active.inch < 0 || emr_active.inch > 11 ||
         (emr_active.feet == MIN_FEET && emr_active.inch < MIN_INCH) ||
         (emr_active.feet == MAX_FEET && emr_active.inch > MAX_INCH))
      {
         message = ".  Allowable Range [" + IntToStr(MIN_FEET) +"'" +IntToStr(MIN_INCH) + "\", "
                  + IntToStr(MAX_FEET) + "'" +IntToStr(MAX_INCH) + "\"] ";
         MsgBox_show(TWARNING,
                    MSG_EMR_ERROR,
                    LoadStr(MSG_EMR_HT_OUT) + IntToStr(emr_active.feet) + "ft, " +IntToStr(emr_active.inch) + "in" + message,
                    MSG_EMR_HT_OUT, "");

         // If the height is not valid, set the defaults
         emr_active.height = emr_default.height;
         emr_active.feet = emr_default.feet;
         emr_active.inch = emr_default.inch;
      }
      else
      {
         // If the Imperial height is valid, then calculate the Metric value
         emr_active.height = math_Round(CONVERT_INCH_TO_CM * (12 * emr_active.feet + emr_active.inch));
      }
   }
   else
   {
      // Set the defaults
      emr_active.height = emr_default.height;
      emr_active.feet = emr_default.feet;
      emr_active.inch = emr_default.inch;
   }

   // If Weight has a value, then the Pound field in the Inbound file is ignored
   if (emr_active.weight != DEFAULT_VALUE)
   {
      // Weight must be within the defined range
      if (emr_active.weight < MIN_WEIGHT || emr_active.weight > MAX_WEIGHT)
      {
         message = ".  Allowable Range [" +IntToStr(MIN_WEIGHT) +", " +IntToStr(MAX_WEIGHT) +"] ";
         MsgBox_show(TWARNING,
                    MSG_EMR_ERROR,
                    LoadStr(MSG_EMR_WT_OUT) +IntToStr(emr_active.weight) + "kg" + message,
                    MSG_EMR_WT_OUT, "");

         // If the weight is not valid, set the defaults
         emr_active.weight = emr_default.weight;
         emr_active.pound = emr_default.pound;
      }
      else
      {
         // If the Metric weight is valid, then calculate the Imperial value
         emr_active.pound = math_Round(emr_active.weight / CONVERT_POUND_TO_KILO);
      }
   }
   else if (emr_active.pound != DEFAULT_VALUE)
   {
      // Pound must be within the defined range
      if (emr_active.pound < MIN_POUND || emr_active.pound > MAX_POUND)
      {
         message = ".  Allowable Range [" +IntToStr(MIN_POUND) +", " +IntToStr(MAX_POUND) +"] ";
         MsgBox_show(TWARNING,
                    MSG_EMR_ERROR,
                    LoadStr(MSG_EMR_WT_OUT) +IntToStr(emr_active.pound) + "lb" + message,
                    MSG_EMR_WT_OUT, "");
         // If the weight is not valid, set the defaults
         emr_active.weight = emr_default.weight;
         emr_active.pound = emr_default.pound;
      }
      else
      {
         // If the Imperial weight is valid, then calculate the Metric value
         emr_active.weight = math_Round(CONVERT_POUND_TO_KILO * emr_active.pound);
      }
   }
   else
   {
      // If the weight is not valid, set the defaults
      emr_active.weight = emr_default.weight;
      emr_active.pound = emr_default.pound;
   }

   dest_path = emr_active.outbound.UpperCase();
   default_path = (ExtractFilePath(ParamStr(0)) + EMR_OUTBOUND_DEFAULT_DIRECTORY).UpperCase();
   exe_path = (ExtractFilePath(ParamStr(0))).UpperCase();

   // If the Outbound directory does not contain the default directory
   if (dest_path.AnsiPos(default_path) == 0)
   {
      // But does contain the exe directory, then it will be set to the default
      if (dest_path.AnsiPos(exe_path) != 0)
      {
         emr_active.outbound = emr_default.outbound;
         MsgBox_show(TWARNING,
                     MSG_EMR_ERROR,
                     LoadStr(MSG_EMR_OUTBOUND_ERROR) + emr_active.outbound,
                     MSG_EMR_OUTBOUND_ERROR,
                     LoadStr(MSG_EMR_OUTBOUND_ERROR) + emr_active.outbound);
      }
   }

   // The option number must be valid
   if (emr_active.option >= EMR_NOF_EXPORTS)
   {
      emr_active.option = emr_default.option;
      MsgBox_show(TWARNING,
                  MSG_EMR_ERROR,
                  LoadStr(MSG_EMR_OPTION_ERROR),
                  MSG_EMR_OPTION_ERROR,"");
   }
   return valid;
}

/* ###########################################################################
// Return if the EMR object is enabled
*/
bool emr_get_enabled(void)
{
   return emr_enabled;
}

/* ###########################################################################
// Return if the EMR object is in Default Mode
*/
bool emr_get_default_mode(void)
{
   return emr_default_mode;
}

/* ###########################################################################
// Set the report export to true or false
*/
void emr_set_report_export(bool status)
{
   emr_report_export = status;
}

/* ###########################################################################
// Return if the report export is set
*/
bool emr_get_report_export(void)
{
   return emr_report_export;
}

/* ###########################################################################
// Get the active EMR record
*/
bool emr_get(EMR_RECORD_TYPE *emr)
{
   emr->inbound = emr_active.inbound;
   emr->system_id = emr_active.system_id;
   emr->surname = emr_active.surname;
   emr->first_name = emr_active.first_name;
   emr->dob = emr_active.dob;
   emr->sex = emr_active.sex;
   emr->patient_id = emr_active.patient_id;
   emr->other_name = emr_active.other_name;
   emr->street = emr_active.street;
   emr->suburb = emr_active.suburb;
   emr->state =  emr_active.state;
   emr->pcode = emr_active.pcode;
   emr->country = emr_active.country;
   emr->phone = emr_active.phone;
   emr->code = emr_active.code;
   emr->patient_notes = emr_active.patient_notes;
   emr->editing = emr_active.editing;
   emr->sp = emr_active.sp;
   emr->mp = emr_active.mp;
   emr->dp = emr_active.dp;
   emr->height = emr_active.height;
   emr->feet = emr_active.feet;
   emr->inch = emr_active.inch;
   emr->weight = emr_active.weight;
   emr->pound = emr_active.pound;
   emr->medication = emr_active.medication;
   emr->study_notes = emr_active.study_notes;
   emr->operator_name = emr_active.operator_name;
   emr->outbound = emr_active.outbound;
   emr->option = emr_active.option;
   emr->automatic =  emr_active.automatic;
   emr->shutdown = emr_active.shutdown;
   emr->printer = emr_active.printer;
   return true;
}

/* ###########################################################################
// Returns the inbound filename path
*/
String emr_get_inbound(void)
{
   String inbound_directory = emr_active.inbound;

   // If the inbound file does not exist
   if (FileExists(inbound_directory) == false)
   {
      // Check if the default file exists
      inbound_directory = emr_default.inbound;
      if (FileExists(inbound_directory) == false)
      {
         // Otherwise return NULL
         inbound_directory = "";
      }
   }
   return inbound_directory;
}

/* ###########################################################################
// Returns the outbound directory
*/
String emr_get_outbound(void)
{
   String outbound_directory = emr_active.outbound;

   // If the outbound directory does not exist
   if (DirectoryExists(outbound_directory) == false)
   {
      // Try to create it
      if (CreateDir(outbound_directory) == false)
      {
         // If this fails, check if the default directory exists
         outbound_directory = emr_default.outbound;
         if (DirectoryExists(outbound_directory) == false)
         {
            // If not, try to create it
            if (CreateDir(outbound_directory) == false)
            {
               // If this fails, set the outbound directory to NULL
               outbound_directory = "";
               MsgBox_show(TWARNING,
                     MSG_EMR_ERROR,
                     LoadStr(MSG_EMR_OUTBOUND_DEFAULT),
                     MSG_EMR_OUTBOUND_DEFAULT,
                     LoadStr(MSG_EMR_OUTBOUND_DEFAULT));
            }
            else
            {
               MsgBox_show(TWARNING,
                     MSG_EMR_ERROR,
                     LoadStr(MSG_EMR_OUTBOUND_CREATE) + outbound_directory,
                     MSG_EMR_OUTBOUND_CREATE,
                     LoadStr(MSG_EMR_OUTBOUND_CREATE) + outbound_directory);
            }
         }
         else
         {
            MsgBox_show(TWARNING,
                     MSG_EMR_ERROR,
                     LoadStr(MSG_EMR_OUTBOUND_CREATE) + outbound_directory,
                     MSG_EMR_OUTBOUND_CREATE,
                     LoadStr(MSG_EMR_OUTBOUND_CREATE) + outbound_directory);
         }
      }
   }
   return outbound_directory;
}

/* ###########################################################################
// Return the current EMR export option
*/
EMR_EXPORT_TYPE emr_get_option(void)
{
   return emr_active.option;
}

/* ###########################################################################
// Return if automatic export is set
*/
bool emr_get_automatic(void)
{
   return emr_active.automatic;
}

/* ###########################################################################
// Return if the current patient and the EMR patient are the same
*/
bool emr_patient_is_active(void)
{
   bool                 success = false;
   PATIENT_RECORD_TYPE  pat;

   if (emr_enabled)
   {
      if (!emr_default_mode)
      {
         if (patient_get(&pat))
         {
            if ((emr_active.system_id.AnsiCompareIC(pat.system_id) == 0) &&
                  (emr_active.surname.AnsiCompareIC(pat.surname) == 0) &&
                  (emr_active.first_name.AnsiCompareIC(pat.first_name) == 0) &&
                  (emr_active.dob == pat.dob) &&
                  (emr_active.sex.AnsiCompareIC(pat.sex) == 0))
            {
               success = true;
            }
         }
      }
   }
   return success;
}

/* ###########################################################################
// To be performed after any report export operation
*/
void emr_export(void)
{
   // If EMR is enabled and the EMR patient is active
   if (emr_patient_is_active())
   {
      // Delete the inbound file, if it exists
      if (FileExists(emr_active.inbound))
      {
         DeleteFile(emr_active.inbound);
      }

      // Shutdown SphygmoCor, if the option is set
      if (emr_active.shutdown)
      {
         frm_main->Close();
      }
   }
}

/* ###########################################################################
// Return the current EMR printer
*/
String emr_get_printer(void)
{
   return emr_active.printer;
}

/* ###########################################################################
// Return if patient editing is enabled
*/
bool emr_get_editing(void)
{
   bool edit = true;

   if (emr_enabled)
   {
      edit = emr_active.editing;
   }

   return edit;
}

/* ###########################################################################
// Return if the current patient can be edited
*/
bool emr_edit_active_patient(void)
{
   bool edit = true;
   
   if (emr_patient_is_active() && !emr_active.editing)
   {
      edit = false;
   }

   return edit;
}
