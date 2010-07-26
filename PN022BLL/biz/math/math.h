/*
    Copyright (C) ATCOR MEDICAL PTY LTD, 2010

    Filename	 :	math.h
	
	Author       :  Paul McBryde

    Description  :	DECLARATION of Math Class
*/

#pragma once
#include "..\biz\biz.h"

namespace Biz {

	public ref class BizMath
	{
	
	public:
		
		// Convert time in msec into index
		static int TimeToIndex(const float pTime, const int pExpandRate, const int pSampleRate);

		// Convert index into time in msec
		static float IndexToTime(const int pIndex, const int pExpandRate, const int pSampleRate);

		// Round real numbers to nearest integer
		static int Round(double pValue);

		// Round integers to nearest multiple of 20
		static int RoundNearest20(int pValue);

		// Calculate smooth first derivative of a function and find max
		static void SmoothDerivative1(const array<float>^ F, const int NofPoints,  const int SmoothOrder,
									const float pDt, array<float>^ pDer1, float% pMax);

		// find maximum and minimum value in array
		static float MaxInArray (const array<float>^ pA, int pSize);
		static float MinInArray (const array<float>^ pA, int pSize);
		static bool  MinMaxInArray (const array<float>^ pA, int pSize, float% pMin, float% pMax);
		static bool  MinMaxInArray (const array<short int>^ pA, int pSize, short int% pMin, short int% pMax);
		static int	 MaxInArrayIndex(const array<float>^ pA, int pSize);
		
		// Find SplineIndex (beginning of a spline) for pulse
		static int GetSplineIndex(const float x, const int SplineIndex,
								const int SplineOrder, const int pPulseLength);

		// Find a value of spline approximation of order SplineOrder in point x of
		// pulse profile together with different number of derivatives
		static bool Spline(const float x, const array<float>^ Profile, const int SplineOrder, float% Value);

		// Smooth array using Running average algorithm
		static bool SmoothArray(array<float>^ pArray, const int pSize, const int pSmoothOrder);

		// Smooth array using Savitsky - Golay smoothing filter
		static int IndexOfExtremum(const array<float>^ pProfile, const bool pMinOrMax, const bool pOnlyFirst, const int i1, const int i2,
								 const bool pLessOrMore, const float pLessOrMoreThan);
		
		// Find Value of function f at x-point
		static float FunctionValue(const array<float>^ pF, const int pNofPoints, const float pX);
	};
}