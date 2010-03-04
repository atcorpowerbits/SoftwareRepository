/*
**
** Copyright (C) PWV MEDICAL PTY LTD, 1998
**
**
** FILE NAME     : CONFIG\PUBTYPE.H
**
** PROJECT       : TITAN SWCI
**
** OBJECT        : CONFIG (Configuration Manager)
**
** DESCRIPTION   : Definition of objects Public types.
**
** AUTHOR        : Peter Harpas
**
** DATE CREATED  : 28/04/98
**
*/
#ifndef CONFIG_PUBTYPE
#define CONFIG_PUBTYPE
#include <inc/std.h>

const String CONFIG_SYSTEM_SUBDIR = "SYSTEM";
const String CONFIG_DATA_SUBDIR = "DATA";


typedef enum
{
   CONFIG_PWA_OPTION = 1,
   CONFIG_PWV_OPTION,      // Includes PWA
   CONFIG_PWM_OPTION,      // Includes PWA
   CONFIG_HRV_OPTION,      // Includes PWA
   CONFIG_STANDARD_ALL_OPTION,      // Includes PWA PWV PWM
   CONFIG_EXTENDED_ALL_OPTION,      // Includes PWA PWV HRV
   CONFIG_PWV_ONLY_OPTION,
   CONFIG_PWM_ONLY_OPTION,
   CONFIG_NO_OPTION
} CONFIG_SYSTEM_OPTIONS;

const String CONFIG_PWA_OPTION_STRING = "[P]";
const String CONFIG_PWV_OPTION_STRING = "[PV]";
const String CONFIG_PWM_OPTION_STRING = "[PM]";
const String CONFIG_HRV_OPTION_STRING = "[PH]";
const String CONFIG_STANDARD_ALL_OPTION_STRING = "[PVM]";
const String CONFIG_EXTENDED_ALL_OPTION_STRING = "[PVH]";
const String CONFIG_PWV_ONLY_OPTION_STRING = "[V]";
const String CONFIG_PWM_ONLY_OPTION_STRING = "[M]";
const String CONFIG_NO_OPTION_STRING = "";

const int CONFIG_DEFAULT_REPORT_STYLE = 1;
const int CONFIG_BLIND_REPORT_STYLE = 2;

const int CONFIG_DEFAULT_REPORT_SCREEN = 1;
const int CONFIG_DETAILED_REPORT_SCREEN = 2;
const int CONFIG_CLINICAL_REPORT_SCREEN = 3;

const int CONFIG_DEFAULT_PTIV = 0;
const int CONFIG_ENABLED_PTIV = 1;

const int CONFIG_DEFAULT_SRRI = 0;
const int CONFIG_ENABLED_SRRI = 1;

const String CONFIG_PWA_SIMULATE = "pwa.dat";
const String CONFIG_PWV_SITEA_SIMULATE = "pwvsitea.dat";
const String CONFIG_PWV_SITEB_SIMULATE = "pwvsiteb.dat";
const String CONFIG_PWM_SIMULATE = "pwm.dat";
const String CONFIG_HRV_SIMULATE = "hrv.dat";

const int CONFIG_DEFAULT_LOCALE = 0;
const int CONFIG_IMPERIAL_LOCALE = 1;
const int CONFIG_OTHER_LOCALE = 2;

const float CONVERT_INCH_TO_CM = 2.54;
const float CONVERT_FEET_TO_CM = 30.48;
const float CONVERT_POUND_TO_KILO = 0.4536;

const int CONFIG_DEFAULT_TONOMETER = 0;

const int CONFIG_DEFAULT_AUDIT = 0;
const int CONFIG_ENABLED_AUDIT = 1;
#endif