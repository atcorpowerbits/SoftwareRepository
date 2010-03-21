//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "Common.h"
#include "Mathem.h"
#include <DateUtils.hpp>
#include "utils.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
/* ###########################################################################
 ** CopyToStringWithEncoding()
 **
 ** DESCRIPTION
 **  Copy short int array into string with automatic encoding
 ** INPUT
 **  pBuffer[pLength] - array
 ** OUTPUT
 **  pBuffer[pLength] - Output edcoded Array
 ** RETURN
 **  String contained encoded array
*/
//---------------------------------------------------------------------------
String CopyToStringWithEncoding(short int *pBuffer, const int pLength)
{
  String Str = "";
  // Validation
  if (pLength <= 0) return Str;
  // Encoding
  // Encode(pBuffer, pLength);
  // Copy to String buffer
  Str.SetLength(pLength*sizeof(short int));
  memcpy(Str.c_str(), pBuffer, pLength*sizeof(short int));
  return Str;
}
//---------------------------------------------------------------------------
String PackToString(const short int *pBuffer, const int pLength)
{
  String Str = "";
  // Validation
  if (pLength <= 0) return Str;
  // Memcopy
  Str.SetLength(pLength*sizeof(short int));
  memcpy(Str.c_str(), pBuffer, pLength*sizeof(short int));
  return Str;
}
//---------------------------------------------------------------------------
String PackToString(const float *pBuffer, const int pLength, const int pFactor)
{
   short int num;
   String Str = "";

  // Validation
  if (pLength > 0)
  {
     // Copy to String buffer multiplying on pFactor
     Str.SetLength(pLength * sizeof(short int));
     for (int i = 0; i < pLength; i++)
     {
       num = (short int) (pBuffer[i] * pFactor);
       memcpy((Str.c_str() + i * sizeof(short int)), &num, sizeof(short int));
     }
  }
  return Str;
}
//---------------------------------------------------------------------------
String PackToString(TDelta *pDelta, const int pLength)
{
  String Str = "";
  // Validation
  if (pLength <= 0)
    return Str;
  // Copy to String buffer multiplying on pFactor
  Str.SetLength(pLength*(sizeof(short int) + sizeof(float)));
  // Memcopy
  for (int i=0; i<pLength; i++)
  {
    float num = pDelta[i].Value;
    short int pValid = (pDelta[i].Valid == true ? (short int)1 : (short int)0);
    memcpy((Str.c_str() + i*(sizeof(float) + sizeof(short int))), &num, sizeof(float));
    memcpy((Str.c_str() + sizeof(float) + i*(sizeof(float) + sizeof(short int))), &pValid, sizeof(short int));
  }
  // Return
  return Str;
}
//---------------------------------------------------------------------------
String PackFloatToString(const float *pBuffer, const int pLength)
{
  String Str = "";
  // Validation
  if (pLength <= 0) return Str;
  // Memcopy
  Str.SetLength(pLength*sizeof(float));
  memcpy(Str.c_str(), pBuffer, pLength*sizeof(float));

  return Str;
}
//---------------------------------------------------------------------------
bool UnpackFromString(short int *pArray, const String pStr, const int pLen)
{
  // Validation
  if (pStr.Length() < pLen || pLen < sizeof(short int))
    return false;

  memcpy(pArray, pStr.c_str(), pLen);
  return true;
}
//---------------------------------------------------------------------------
bool UnpackFromString(float *pArray, const String pStr, const int pLen)
{
  // Validation
  if (pStr.Length() < pLen || pLen < sizeof(float))
    return false;

  memcpy(pArray, pStr.c_str(), pLen);
  return true;
}
//----------------------------------------------------------------------------------------
bool UnpackFromString(float *pArray, const String pStr, const int pLen,
                      const int pFactor, const int NofPointsToIgnore)
{
  // Validation
  if (pStr.Length() < pLen || pLen < sizeof(short int) || pFactor <= 0)
    return false;
  // Memcopy
  int l2 = pLen/sizeof(short int);
  short int num = -1;
  for (int i=NofPointsToIgnore; i<l2; i++)
  {
    memcpy(&num, (pStr.c_str() + i*sizeof(short int)), sizeof(short int));
    pArray[i-NofPointsToIgnore] = float(num) / pFactor;
  }
  return true;
}
//----------------------------------------------------------------------------------------
bool UnpackFloatFromString(float *pArray, const String pStr, const int pLen, const int pFactor)
{
  int pBaseBytes = sizeof(float);
  // Validation
  if (pStr.Length() < pLen || pLen < pBaseBytes || pFactor <= 0)
    return false;
  // Memcopy
  int l2 = pLen/pBaseBytes;
  float num = -1.;
  for (int i=0; i<l2; i++)
  {
    memcpy(&num, pStr.c_str() + i*pBaseBytes, pBaseBytes);
    pArray[i] = num * pFactor;
  }
  return true;
}
//----------------------------------------------------------------------------------------
bool UnpackFromString(short int *pArray, const String pStr,
                      const int pLen, const int pFactor)
{
  // Validation
  if (pStr.Length() < pLen || pLen < sizeof(float) || pFactor <= 0)
    return false;
  // Memcopy
  int l2 = pLen/sizeof(float);
  float fnum = -1.;
  for (int i=0; i<l2; i++)
  {
    memcpy(&fnum, (pStr.c_str() + i*sizeof(float)), sizeof(float));
    pArray[i] = (fnum > 0 ? (short int) (fnum * pFactor) : fnum);
  }
  return true;
}
//---------------------------------------------------------------------------
bool UnpackFromString(TDelta *pDelta, const String pStr, const int pLen)
{
  // Validation
  if (pStr.Length() < pLen || pLen < (sizeof(float) + sizeof(short int)))
    return false;
  // Memcopy
  // memcpy(pDelta, pStr.c_str(), pLen);
  int l2 = pLen/(sizeof(float) + sizeof(short int));
  //short int num;
  float num;
  short int inum;
  for (int i=0; i<l2; i++)
  {
    memcpy(&num, (pStr.c_str() + i*(sizeof(float) + sizeof(short int))), sizeof(float));
    pDelta[i].Value = float(num);
    memcpy(&inum, (pStr.c_str() + sizeof(float) + i*(sizeof(float) + sizeof(short int))), sizeof(short int));

    pDelta[i].Valid = inum > 0;
    // pDelta[i].Valid = inum;
  }
  return true;
}
/* ###########################################################################
 ** Encode()
 **
 ** DESCRIPTION
 **  Encoding short int array to avoid bytes with all zeros.
 **  After encoding 2 highest bits became lost
 ** INPUT
 **  a[Length] - array
 ** OUTPUT
 **  a[Length] - output edcoded Array
 ** RETURN
 **  NONE
*/
//---------------------------------------------------------------------------
void Encode(short int* a, const int Length)
{
  // Shift 2 bytes 1 position left and put 1 to both highest and lowest bits
  for (int i=0; i<Length; i++)
   // -1 as a sign the end of array is not encoded
   if (a[i] != -1) a[i] = (short int) ((a[i] << 1) | 0x8001);
}
/* ###########################################################################
 ** Decode()
 **
 ** DESCRIPTION
 **  Decoding short int array - function opposite to Encode()
 **  After encoding highest and lowest bits became lost
 ** INPUT
 **  a[Length] - array
 ** OUTPUT
 **  a[Length] - output decoded Array
 ** RETURN
 **  NONE
*/
//---------------------------------------------------------------------------
void Decode(short int* a, const int Length)
{
  // Put 0 to both highest and lowest bits and shift 2 bytes on 1 position right
  for (int i=0; i<Length; i++)
   // -1 as a sign the end of array is not decoded
   if (a[i] != -1) a[i] = (short int) ((a[i] & 0x7ffe) >> 1);
}
//---------------------------------------------------------------------------
/* ###########################################################################
 ** MEASURE_TYPE FindMeasureType(String pStrMeasure)
 **
 ** DESCRIPTION
 **  Convert String pStrMeasure to appropriate MeasureType
 ** INPUT
 **  pStrMeasure - Strings ("Radial", "Carotid", ...)
 ** OUTPUT
 **  appropriate MeasureType (RADIAL, CAROTID, ...)
 **  if invalid String, return MeasureType = NOF_MEASURES
*/
//---------------------------------------------------------------------------
PWA_MEASURE_TYPE PwaFindMeasureType(String pStrMeasure)
{
  for (int i=0; i < PWA_NOF_MEASURES; i++)
  {
    if (pStrMeasure==PWAMTypeAsString[i])
    {
      return (PWA_MEASURE_TYPE)i;
    }
  }
  return PWA_NOF_MEASURES;
}
//---------------------------------------------------------------------------
PWV_MEASURE_TYPE PwvFindMeasureType(String pStrMeasure)
{
  for (int i=0; i < PWV_NOF_MEASURES; i++)
  {
    if (pStrMeasure==PWVMTypeAsString[i])
    {
      return (PWV_MEASURE_TYPE)i;
    }
  }
  return PWV_NOF_MEASURES;
}
//---------------------------------------------------------------------------
String RoundIntToStr(float pValue)
{
  return IntToStr(math_Round(pValue));
}
//---------------------------------------------------------------------------
void DetermineBMIRange(float bmi, TShape* shape_bmi)
{
   // Given the bmi, this function sets the bmi captions and shape colours

   shape_bmi->Visible = true;
   if (bmi > 30)
   {
      shape_bmi->Brush->Color = sphygmocor_red;
   }
   else if (bmi >= 25 && bmi <= 30)
   {
     shape_bmi->Brush->Color = sphygmocor_yellow;
   }
   else if (bmi >= 20 && bmi < 25)
   {
      shape_bmi->Brush->Color = sphygmocor_green;
   }
   else
   {
      shape_bmi->Brush->Color = sphygmocor_yellow;
   }
}
//---------------------------------------------------------------------------
bool IsStringAlpha(String S, const int length)
{
   if (S.Length() < length)
   {
      return false;
   }

   for (int i = 1; i < length + 1; i++)
   {
      if (!isalpha(S[i]))
      {
         return false;
      }
   }
   return true;
}
//---------------------------------------------------------------------------
bool IsDateValid(String S)
{
   Word days, months, years;
   TDateTime   min_dob;

   if (S.Length() != 10)
   {
      return false;
   }
   if ((!S.IsDelimiter("/", 3)) || (!S.IsDelimiter("/", 6)))
   {
      return false;
   }
   try
   {
      days = (S.SubString(1, 2)).ToInt();
      months = (S.SubString(4, 2)).ToInt();
      years = (S.SubString(7, 4)).ToInt();
      if (!IsValidDate(years, months, days))
      {
         return false;
      }
   }
   catch (Exception &exception)
   {
      return false;
   }
   return true;
}
