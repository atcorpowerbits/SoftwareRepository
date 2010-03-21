#ifndef REPORT_PUBTYPE
#define REPORT_PUBTYPE
#include <inc/std.h>

typedef enum
{
   RANGE_VERY_LOW = 1,
   RANGE_LOW,
   RANGE_NORMAL_LOW,
   RANGE_NORMAL_HIGH,
   RANGE_HIGH,
   RANGE_VERY_HIGH,
   RANGE_UNDEFINED
} CLINICAL_NORMALS_RANGE;

const int REPORT_MAX_PRINTED_MEMO_LENGTH = 100;
// PM CR
const int REPORT_SEVR_ABNORMAL = 120;

const String REFERENCE_RETURN = "Click Here to Return to the Clinical Screen";
const String REFERENCE_ENLARGE = "Click Here to Enlarge";

#endif

 