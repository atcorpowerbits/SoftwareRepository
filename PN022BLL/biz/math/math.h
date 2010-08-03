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
		static bool TimeToIndex(const float time, const int expandRate, const int sampleRate, int% index);

		// Convert index into time in msec
		static bool IndexToTime(const int index, const int expandRate, const int sampleRate, float% time);

		// Round real numbers to nearest integer
		static bool Round(double input, int% output);

		// Round integers to nearest multiple of 20
		static bool RoundNearest20(int input, int% output);

		// Calculate smooth first derivative of a function and find max
		static bool SmoothDerivative1(array<const float>^ input, const int size,  const int smoothOrder,
									const float step, array<float>^ firstDerivative, float% maximum);

		// find maximum and minimum value in array
		static bool MaxInArray (array<const float>^ input, int size, float% maximum);
		static bool MinInArray (array<const float>^ input, int size, float% minimum);
		static bool MinMaxInArray (array<const float>^ input, int size, float% minimum, float% maximum);
		static bool MinMaxInArray (array<const short int>^ input, int size, short int% minimum, short int% maximum);
		static bool	MaxInArrayIndex(array<const float>^ input, int size, int% maximumIndex);
		
		// Find SplineIndex (beginning of a spline) for pulse
		static int GetSplineIndex(const float x, const int SplineIndex,
								const int SplineOrder, const int pPulseLength);

		// Find a value of spline approximation of order SplineOrder in point x of
		// pulse profile together with different number of derivatives
		static bool Spline(const float x, array<const float>^ Profile, const int SplineOrder, float% Value);

		// Smooth array using Running average algorithm
		static bool SmoothArray(array<float>^ pArray, const int pSize, const int pSmoothOrder);

		// Smooth array using Savitsky - Golay smoothing filter
		static int IndexOfExtremum(array<const float>^ pProfile, const bool pMinOrMax, const bool pOnlyFirst, const int i1, const int i2,
								 const bool pLessOrMore, const float pLessOrMoreThan);
		
		// Find Value of function f at x-point
		static float FunctionValue(array<const float>^ pF, const int pNofPoints, const float pX);
	};
}