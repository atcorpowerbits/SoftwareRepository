//---------------------------------------------------------------------------
#ifndef MathemH
#define MathemH
#include "Common.h"
const int DER_CENTRAL_SCHEME = 0;
const int DER_RIGHT_SCHEME = 1;
//---------------------------------------------------------------------------
// Mathematical functions prototypes
//---------------------------------------------------------------------------
// Convert time in msec into index
int math_TimeToIndex(const float pTime, const int pExpandRate,
                     const int pSampleRate);
// Convert index into time in msec
float math_IndexToTime(const int pIndex, const int pExpandRate,
                       const int pSampleRate);
// Round real numbers to nearest integer
int math_Round (double pValue);

// Round integers to nearest multiple of 20
int math_Round_nearest_20 (int pValue);

// Calculate first derivative of a function and find max
void math_Derivative1(const float* pFunct, const int NofPoints, const float pDt,
                      float* pDer1, float &pMax);
// Calculate smooth first derivative of a function and find max
void math_SmoothDerivative1(const float* F, const int NofPoints,  const int SmoothOrder,
                            const float pDt, float* pDer1, float &pMax);
// Calculate first derivative with 3-points formula
void math_Deriv1(const float* F, const int NofPoints,
                 const float pDt, float* pDer1, float &pMax);

// Calculate 1,2,3 derivatives
void math_Derivatives123(const float* F, const int NofPoints, const float pDt,
                         float* pDer1, float* pDer2, float* pDer3,
                         float &pMaxDer1, float &pMaxDer2, float &pMaxDer3,
                         const int pOrder = 3, const int pFormulaType = DER_CENTRAL_SCHEME);
                         
// find maximum and minimum value in array
float math_MaxInArray (const float *pA, int pSize);
float math_MinInArray (const float *pA, int pSize);
bool  math_MinMaxInArray (const float *pA, int pSize, float &pMin, float &pMax);
bool  math_MinMaxInArray (const short int *pA, int pSize, short int &pMin, short int &pMax);
int math_MaxInArrayIndex(const float *pA, int pSize);
bool math_MaxAfterMinInArray (const float *pA, int pSize, float &pMin, float &pMax);

float math_MeanInArray (const float *pA, int pSize);

float math_STDinArray(int *pA,int pSize);

double math_STDinArray(float *pA,int pSize);

double math_RMSinArray(float *pA, int pSize);

bool math_IndexMaxInArray (const int *pA, int pSize, int &pIndex, int &pMax);

bool math_IndexMaxInArray (const short int *pA, int pSize, int &pIndex, int &pMax);

// Find SplineIndex (beginning of a spline) for pulse
int math_GetSplineIndex(const float x, const int SplineIndex,
                        const int SplineOrder, const int pPulseLength);
//  Find SplineIndex (beginning of nearest spline) and
//  Nof closest splines for point x on pulse (for Hermitial interpolation)
bool math_GetSplineOverlay(const float x, int& SplineIndex, int& NofSplines,
                           const int SplineOrder, const int pPulseLength);

// Find a value of spline approximation of order SplineOrder in point x of
// pulse profile together with different number of derivatives
bool math_Spline(const float x, const float* Profile, const int SplineOrder, float &Value,
                 float *Der1 = NULL, const int NofDer = 0);

// Find a value of cubic (hermitian) spline approximation of order SplineOrder in point x of
// Pulse profile together with 3 derivatives
bool math_Hermit(const float x, const float* Profile, const float* D1, float &Value,
                 float &Der1, float &Der2, float &Der3);

// Find an index of first positive/negative crossing
// of function Profile[...] between indexes i1, i2
int math_IndexOfFirstPositiveCrossing(const float *Profile, const int i1, const int i2);
int math_IndexOfFirstNegativeCrossing(const float *Profile, const int i1, const int i2);
// Find an index of second positive/negative crossing
// of function Profile[Length]
int math_IndexOfSecondPositiveCrossing(const float *Profile, const int Begin, const int Length);
int math_IndexOfSecondNegativeCrossing(const float *Profile, const int Begin, const int Length);
// Check if the function Profile[...] positive between indexes i1, i2
bool math_IsPositive(const float *Profile, const int i1, const int i2);
// Smooth array using Running average algorithm
bool math_SmoothArray(float *pArray, const int pSize, const int pSmoothOrder = 2);
// Smooth array using Savitsky - Golay smoothing filter
bool math_SGSmoothArray(float *pArray, const int pSize, const int pSmoothOrder);
// Find index of Extremal (local) Maximal (or Minimal) value for pulse
// between indexes i1, i2 with checking stability and limits
int math_IndexOfExtremum(const float *pProfile, const bool pMinOrMax, const bool pOnlyFirst, const int i1, const int i2,
                         const bool pLessOrMore = LESS, const float pLessOrMoreThan = DEFAULT_VALUE);
// Find float index of Maximal value of a quadratic interpolation
// of a function constructed for tripple f(x1), f(x2), f(x3)
float math_IndexOfQuadrInterpMax(const float x1, const float x2, const float x3,
                                 const float f1, const float f2, const  float f3, float &fmax);
// Find Value of function f at x-point
float math_FunctionValue(const float* pF, const int pNofPoints, const float pX);

#define max(__a,__b)    (((__a) > (__b)) ? (__a) : (__b))
#define min(__a,__b)    (((__a) < (__b)) ? (__a) : (__b))

#endif
