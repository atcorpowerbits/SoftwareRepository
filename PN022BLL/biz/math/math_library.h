/*
    Copyright (C) ATCOR MEDICAL PTY LTD, 2010

    Filename	 :	math_library.h
	
	Author       :  Paul McBryde

    Description  :	DECLARATION of Math Class
*/

#pragma once
#include <biz.h>
using namespace System::Runtime::InteropServices;

namespace Biz {

	public ref class BizMath sealed
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
		static bool SmoothFirstDerivative(array<const float>^ input, const int size,  const int smoothOrder,
									const float step, array<float>^ firstDerivative, float% maximum);

		// find maximum and minimum value in array
		static bool MaximumInArray (array<const float>^ input, int size, float% maximum);
		static bool MinimumInArray (array<const float>^ input, int size, float% minimum);
		static bool MinimumMaximumInArray (array<const float>^ input, int size, float% minimum, float% maximum);
		static bool MinimumMaximumInArray (array<const short int>^ input, int size, short int% minimum, short int% maximum);
		static bool	MaximumInArrayIndex(array<const float>^ input, int size, int% maximumIndex);
		
		// Find SplineIndex (beginning of a spline) for pulse
		static bool GetSplineIndex(const float abscissa, const int splineIndex, const int size, int% newSplineIndex);

		// Find a value of spline approximation in point abscissa of pulse profile
		static bool Spline(const float abscissa, array<const float>^ input, float% output);

		// Smooth array using Running average algorithm
		static bool SmoothArray(array<float>^ input, const int size);

		// Find index of the first Extremal Maximum value for pulse between indexes start and end, greater than the threshold
		static bool IndexOfExtremum(array<const float>^ input, const int start, const int end,
								 const float threshold, int% index);
		
		// Find Value of function f at x-point
		static bool FunctionValue(array<const float>^ function, const int size, const float argument, float% value);

		// Validate the array boundaries
		static bool ValidateArray(array<const float>^ input, int size);
		static bool ValidateArray(array<const short int>^ input, int size); 
	};
}
extern bool BizCorValidateArray(const float* input, int size);
extern bool BizCorFunctionValue(const float* function, const int size, const float argument, float* value);
extern bool BizCorMaximumInArray (const float* input, int size, float* maximum);
extern bool BizCorMinimumMaximumInArray (const float* input, int size, float* minimum, float* maximum);
extern bool BizCorSmoothFirstDerivative(const float* input, const int size, const int smoothOrder,
										const float step, float* firstDerivative, float* maximum);
extern bool BizCorIndexOfExtremum(const float* input, const int start, const int end, 
										const float threshold, int* index);