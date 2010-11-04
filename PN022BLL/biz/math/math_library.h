/*
    Copyright (C) ATCOR MEDICAL PTY LTD, 2010

    Filename	 :	math_library.h
	
	Author       :  Paul McBryde

    Description  :	DECLARATION of Math Class
*/

#pragma once
#include <biz.h>
#include <biz_constants.h>
#include <biz_namespace.h>

using namespace System::Runtime::InteropServices;

START_BIZ_NAMESPACE

public ref class BizMath sealed
{

public:
	
	// Convert time in msec into index
	static bool TimeToIndex(const float time, const unsigned short expandRate, const unsigned short sampleRate, short% index);

	// Convert index into time in msec
	static bool IndexToTime(const unsigned short index, const unsigned short expandRate, const unsigned short sampleRate, float% time);

	// Round real numbers to nearest integer
	static bool Round(float input, short% output);

	// Round integers to nearest multiple of 20
	static bool RoundNearest20(short input, short% output);

	// Calculate smooth first derivative of a function and find max
	static bool SmoothFirstDerivative(array<const unsigned short>^ input, const unsigned short size,  const unsigned short smoothOrder,
								const float step, array<float>^ firstDerivative, float% maximum);

	// find maximum and minimum value in array
	static bool MaximumInArray (array<const float>^ input, unsigned short size, float% maximum);
	static bool MinimumInArray (array<const float>^ input, unsigned short size, float% minimum);
	static bool MinimumMaximumInArray (array<const float>^ input, unsigned short size, float% minimum, float% maximum);
	static bool MinimumMaximumInArray (array<const unsigned short>^ input, unsigned short size, unsigned short% minimum, unsigned short% maximum);
	static bool	MaximumInArrayIndex(array<const float>^ input, unsigned short size, unsigned short% maximumIndex);
	
	// Find SplineIndex (beginning of a spline) for pulse
	static bool GetSplineIndex(const float abscissa, const unsigned short splineIndex, const unsigned short size, unsigned short% newSplineIndex);

	// Find a value of spline approximation in point abscissa of pulse profile
	static bool Spline(const float abscissa, array<const float>^ input, float% output);

	// Smooth array using Running average algorithm
	static bool SmoothArray(array<float>^ input, const unsigned short size);

	// Find index of the first Extremal Maximum value for pulse between indexes start and end, greater than the threshold
	static bool IndexOfExtremum(array<const float>^ input, const unsigned short start, const unsigned short end,
							 const float threshold, unsigned short% index);
	
	// Find Value of function f at x-point
	static bool FunctionValue(array<const unsigned short>^ function, const unsigned short size, const float argument, float% value);

	// Validate the array boundaries
	static bool ValidateArray(array<const float>^ input, unsigned short size);
	static bool ValidateArray(array<const unsigned short>^ input, unsigned short size); 
};

END_BIZ_NAMESPACE

extern bool BizCorValidateArray(const float* input, unsigned short size);
extern bool BizCorFunctionValue(const unsigned short* function, const unsigned short size, const float argument, float* value);
extern bool BizCorMaximumInArray (const float* input, unsigned short size, float* maximum);
extern bool BizCorMinimumMaximumInArray (const float* input, unsigned short size, float* minimum, float* maximum);
extern bool BizCorMinimumMaximumInArray (const unsigned short* input, unsigned short size, unsigned short* minimum, unsigned short* maximum);
extern bool BizCorSmoothFirstDerivative(const unsigned short* input, const unsigned short size, const unsigned short smoothOrder,
										const float step, float* firstDerivative, float* maximum);
extern bool BizCorIndexOfExtremum(const float* input, const unsigned short start, const unsigned short end, 
										const float threshold, unsigned short* index);