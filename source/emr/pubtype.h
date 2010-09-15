#ifndef EMR_PUBTYPE
#define EMR_PUBTYPE

// Main and About form captions
const String EMR_ENABLED = "Electronic Medical Records Mode";
const String EMR_DEFAULT_MODE = "Default Electronic Medical Records Mode";

typedef enum
{
  EMR_STANDARD,
  EMR_CLINICAL,
  EMR_DETAILED,
  EMR_ALL_PDF,
  EMR_CLINICAL_PDF,
  EMR_DETAILED_PDF,
  EMR_ALL,
  EMR_NOF_EXPORTS
} EMR_EXPORT_TYPE;

typedef struct
{
   String            inbound;
   String            system_id;
   String            surname;
   String            first_name;
   TDateTime         dob;
   String            sex;
   String            patient_id;
   String            other_name;
   String            street;
   String            suburb;
   String            state;
   String            pcode;
   String            country;
   String            phone;
   String            code;
   String            patient_notes;
   bool              editing;
   int		         sp;
   int               mp;
   int		         dp;
   int		         height;
   int		         feet;
   int		         inch;
   int		         weight;
   int		         pound;
   String            medication;
   String            study_notes;
   String            operator_name;
   String		      outbound;
   EMR_EXPORT_TYPE   option;
   bool		         automatic;
   bool		         shutdown;
   String            printer;
} EMR_RECORD_TYPE;

#endif
 