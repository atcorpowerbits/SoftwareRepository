//---------------------------------------------------------------------------
#ifndef CommonH
#define CommonH
#include <meas\pubtype.h>
//const bool MAXIMUM = true;
//const bool MINIMUM = false;
const bool MAX = true;
const bool MIN = false;
const bool STABLE = true;
const bool NOTSTABLE = false;
// const float PULSE_DEFAULT_VALUE = 9999;
const bool FIRST = true;
const bool GLOBAL = false;
const bool MORE = true;
const bool LESS = false;
//---------------------------------------------------------------------------
// Copy short int array into string with automatic encoding
String CopyToStringWithEncoding(short int *pBuffer, const int pLength);
//---------------------------------------------------------------------------
String PackToString(const short int *pBuffer, const int pLength);
String PackToString(const float *pBuffer, const int pLength, const int pDivider);
String PackFloatToString(const float *pBuffer, const int pLength);
String PackToString(TDelta *pDelta, const int pLength);
bool UnpackFromString(short int *pArray, const String pStr, const int pLen);
bool UnpackFromString(short int *pArray, const String pStr,
                      const int pLen, const int pFactor);
bool UnpackFromString(float *pArray, const String pStr, const int pLen);
bool UnpackFromString(float *pArray, const String pStr, const int pLen,
                      const int pFactor, const int NofPointsToIgnore = 0);
bool UnpackFromString(TDelta *pDelta, const String pStr, const int pLen);
bool UnpackFloatFromString(float *pArray, const String pStr, const int pLen, const int pFactor = 1);
// Encoding short int array to avoid bytes with all zeros
void Encode(short int* a, const int Length);
// Decoding short int array - function opposite to Encode()
void Decode(short int* a, const int Length);
String GetCurrentPwvMeasureDetails();
String GetCurrentPwaMeasureDetails();
String GetCurrentHRVMeasureDetails();
PWA_MEASURE_TYPE PwaFindMeasureType(String pStrMeasure);
PWV_MEASURE_TYPE PwvFindMeasureType(String pStrMeasure);
void DetermineBMIRange(float bmi, TShape* shape_bmi);
bool IsStringAlpha(String S, const int length);
bool IsDateValid(String S);
#endif
