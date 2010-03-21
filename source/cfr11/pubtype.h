#ifndef CFR11_PUBTYPE
#define CFR11_PUBTYPE

// Security form messages
const String SECURITY_LOGIN = "Please sign into the SphygmoCor system using a Windows Logon:";
const String SECURITY_SIGNATURE = "You are about to modify or create a record.\n\nPlease sign in using your personal Windows User account to verify your identity.\n\nThe information you provide will be stored with the record as a legally binding\n Electronic Signature and you will be held accountable for your actions.";

// Operator label captions
const String AUDIT_NO_CAPTION = "Operator:";
const String AUDIT_ORIGINAL_CAPTION = "Created by:";
const String AUDIT_MODIFIED_CAPTION = "Modified by:";
const String AUDIT_DELETED_CAPTION = "Deleted by:";

// Audit button labels
const String AUDIT_BUTTON_CAPTION = "Audit &Trail";
const String AUDIT_PATIENT_BUTTON_CAPTION = "Patien&ts";
const String AUDIT_REPORT_BUTTON_CAPTION = "Repor&ts";

// Audit button images
const int AUDIT_PATIENTS_IMAGE = 10;
const int AUDIT_TRAIL_PATIENT_IMAGE = 9;
const int AUDIT_PWA_REPORTS_IMAGE = 8;
const int AUDIT_TRAIL_PWA_IMAGE = 7;
const int AUDIT_PWV_REPORTS_IMAGE = 6;
const int AUDIT_TRAIL_PWV_IMAGE = 5;

// Audit grid columns
const String AUDIT_COLUMN_TITLE = "Change Time";
const String AUDIT_PATIENT_ID_TITLE = "Patient ID";
const String AUDIT_PATIENT_DOB_TITLE = "Date Of Birth";
const String AUDIT_PATIENT_FIRST_NAME_TITLE = "First Name";
const String AUDIT_PATIENT_SURNAME_TITLE = "Family Name";
const String AUDIT_REPORT_TITLE = "Study Time";
const int AUDIT_COLUMN_WIDTH = 260;
const int AUDIT_PATIENTS_COLUMN_WIDTH = 100;

// Audit table names
const String PATIENT_AUDIT = "PATIENT_AUDIT";
const String MPWA_AUDIT = "M_PWA_AUDIT";
const String MPWV_AUDIT = "M_PWV_AUDIT";

// extra PATIENT_AUDIT table fields
const String PATIENT_AUDIT_DATETIME          = "DATETIME_CHANGE";
const String PATIENT_AUDIT_OPERATOR          = "CHARSPARE2";
const String PATIENT_AUDIT_REASON            = "MEMOSPARE1";
const String PATIENT_AUDIT_FLAG              = "LNUMSPARE1";

// extra M_PWA_AUDIT table fields
const String MPWA_AUDIT_DATETIME    = "DATETIME_CHANGE";
const String MPWA_AUDIT_REASON      = "MEMSPARE2";
const String MPWA_AUDIT_FLAG        = "INTSPARE2";

// extra M_PWV_AUDIT table fields
const String MPWV_AUDIT_DATETIME    = "DATETIME_CHANGE";
const String MPWV_AUDIT_REASON      = "MEM_SPARE2";
const String MPWV_AUDIT_FLAG        = "INT_SPARE2";

// Main and About form caption
const String AUDIT_ENABLED = "Data Audit Trail Mode";

// Audit flag types
typedef enum
{
  AUDIT_ORIGINAL,
  AUDIT_MODIFIED,
  AUDIT_DELETED,
  AUDIT_NOF_FLAGS
} AUDIT_FLAG_TYPE;

const String AUDITTypeAsString [AUDIT_NOF_FLAGS] =
{
   "ORIGINAL",
   "MODIFIED",
   "DELETED"
};

// Recalculate and Modify form modes
typedef enum
{
  AUDIT_NORMAL,
  AUDIT_DELETING,
  AUDIT_BROWSING
} AUDIT_MODE;
#endif
