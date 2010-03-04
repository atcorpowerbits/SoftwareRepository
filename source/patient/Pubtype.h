#ifndef PATIENT_PUBTYPE
#define PATIENT_PUBTYPE

#include <inc/std.h>
#include <cfr11/pubtype.h>

const String PATIENT_SYSTEM_ID  = "SYSTEM_ID";
const String PATIENT_NO         = "PATIENT_NO";
const String PATIENT_STUDY_ID   = "STUDY_ID";
const String PATIENT_SURNAME    = "FAM_NAME";
const String PATIENT_FIRST_NAME = "FIRST_NAME";
const String PATIENT_OTHER_NAME = "OTHER_NAME";
const String PATIENT_SEX        = "SEX";
const String PATIENT_DOB        = "DOB";
const String PATIENT_ID         = "PATIENT_ID";
const String PATIENT_STREET     = "STREET";
const String PATIENT_SUBURB     = "TOWN";
const String PATIENT_STATE      = "STATE";
const String PATIENT_COUNTRY    = "COUNTRY";
const String PATIENT_PCODE      = "ZIPCODE";
const String PATIENT_PHONE      = "PHONE";
const String PATIENT_CODE       = "CODE";
const String PATIENT_NOTES      = "NOTES";
const String PATIENT_EMAIL      = "EMAILADD";
const String PATIENT_SPARE1     = "CHARSPARE1";

const COUNT PATIENT_RESET_MEAS_NUM = -1;

const int PATIENT_YOUNG_AGE = 17;

const String PATIENT_INIT_SYSTEMID = "00001";

typedef unsigned long PATIENT_NUMBER_TYPE;

typedef struct
{
   String               system_id;
   PATIENT_NUMBER_TYPE  number;
   String               study_id;
   String               id;
   String               surname;
   String               first_name;
   String               other_name;
   String               sex;
   TDateTime            dob;
   String               age;
   String               street;
   String               suburb;
   String               state;
   String               country;
   String               phone;
   String               pcode;
   String               code;
   String               notes;
   String               profile;
   TDateTime            audit_change;
   String               operator_name;
   String               reason;
   AUDIT_FLAG_TYPE      audit_flag;
} PATIENT_RECORD_TYPE;
#endif
