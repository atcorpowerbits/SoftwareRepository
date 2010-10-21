/**
    Copyright (C) ATCOR MEDICAL PTY LTD, 2010

    Filename	 :	math_library.cpp
	
	Author       :  Paul McBryde

    Description  :	DECLARATION of Math Class
*/
#include "stdafx.h"
#include "stdlib.h"
#include <math_library.h>

using namespace BIZ_NAMESPACE;
using namespace System;

#pragma hdrstop

/**
 ** ValidateArray()
 **
 ** DESCRIPTION:
 **  Validate the array boundaries.

 ** INPUT:
 **  input[size] - array.
 
 ** OUTPUT:
 **  none.

 ** RETURN:
 **  bool success or not.
*/
bool BizMath::ValidateArray(array<const float>^ input, unsigned short size)
{
	if (input == nullptr)
	{
		return false; 
	}
	
	// We cannot determine the length of an unmanaged array -
	// so check here first
	if (size > input->Length)
	{
		return false;
	}
	
	// Prevent the Garbage Collector from deleting the array
	pin_ptr<const float> corInput = &input[0];
	
	return BizCorValidateArray(corInput, size);
	
	/*if (input == nullptr)
	{
		return false; 
	}
	if (size < 1 || size >= DEFAULT_VALUE || size > input->Length)
	{
		return false;
	}
	for (int i = 0; i < size; i++)
	{
		if (input[i] >= DEFAULT_VALUE || input[i] <= -DEFAULT_VALUE)
		{
			return false;
		}
	}
	return true;*/
}

#pragma unmanaged
bool BizCorValidateArray(const float* input, unsigned short size)
{
	if (input == NULL)
	{
		return false; 
	}
	if (size < 1 || size >= DEFAULT_VALUE)// || size > sizeof(input) / sizeof(input[0]))
	{
		return false;
	}
	for (unsigned short i = 0; i < size; i++)
	{
		if (input[i] >= DEFAULT_VALUE || input[i] <= -DEFAULT_VALUE)
		{
			return false;
		}
	}
	return true;
}

#pragma managed
bool BizMath::ValidateArray(array<const unsigned short>^ input, unsigned short size)
{
	if (input == nullptr)
	{
		return false;
	}
	if (size < 1 || size >= DEFAULT_VALUE || size > input->Length)
	{
		return false;
	}
	for (unsigned short i = 0; i < size; i++)
	{
		if (input[i] >= DEFAULT_VALUE)
		{
			return false;
		}
	}
	return true;
}

/**
 ** TimeToIndex()
 **
 ** DESCRIPTION:
 **  Convert time in msec into index.

 ** INPUT:
 **  time,
 **  expandRate - rate of upsampling,
 **  sampleRate (usually 256) - rate of signal sampling.

 ** OUTPUT:
 **  index.

 ** RETURN:
 **  bool success or not.
*/

bool BizMath::TimeToIndex(const float time, const unsigned short expandRate,
                     const unsigned short sampleRate, short% index)
{
	// Validation
	if (expandRate < 1 || expandRate >= DEFAULT_VALUE)
	{
		return false;  
	}
	if (time <= 0. || time >= DEFAULT_VALUE)
	{
		return false;  

	}
	if (sampleRate < 1 || sampleRate >= DEFAULT_VALUE)
	{
		return false;
	}

	// Calculate index
	BizMath::Round(time * sampleRate * expandRate / 1000, index);
	return true;
}

/**
 ** IndexToTime()
 **
 ** DESCRIPTION:
 **  Convert index into time in msec.

 ** INPUT:
 **  index,
 **  expandRate - rate of upsampling,
 **  sampleRate (usually 256) - rate of signal sampling.

 ** OUTPUT:
 **  time.

 ** RETURN:
 **  bool success or not.
*/

bool BizMath::IndexToTime(const unsigned short index, const unsigned short expandRate,
                       const unsigned short sampleRate, float% time)
{
	// Validation
	if (expandRate < 1 || expandRate >= DEFAULT_VALUE)
	{
		return false;  
	}
	if (index >= DEFAULT_VALUE)
	{
		return false;  
	}
	if (sampleRate < 1 || sampleRate >= DEFAULT_VALUE)
	{
		return false;
	}

	// Calculate time
	time = index * (float)1000. / (sampleRate * expandRate);
	return true;
}

/**
 ** Round()
 **
 ** DESCRIPTION:
 **  Round real numbers to nearest integer
 **		Example :
 **		3.78 -> 4, -3.78 -> -4
 **		3.27 -> 3, -3.27 -> -3
 **
 ** INPUT:
 **  input - double value to round.
 **
 ** OUTPUT:
 **  output - rounded integer.
 **
 ** RETURN:
 **  bool success or not.
*/

bool BizMath::Round(float input, short% output)
{
	// Validation
	if (input >= DEFAULT_VALUE || input <= -DEFAULT_VALUE)
	{
		return false;
	}
	  
	// Round positive number
	if( input >= 0.0 )
	{
		// Round down
		if ((input - ((long long int) input)) < 0.5)
		{
			output = Convert::ToInt16(Math::Floor(input));		
		}
		// Round up
		else
		{
			output = Convert::ToInt16(Math::Ceiling(input));	
		}
	}
	// Round negative number
	else
	{
		// Round down
		if ((input - ((long long int)input)) < -0.5 )
		{
			output = Convert::ToInt16(Math::Floor(input));		
		}
		// Round up
		else
		{
			output = Convert::ToInt16(Math::Ceiling(input));	
		}
	}

	return true;
}

/**
 ** RoundNearest20()
 **
 ** DESCRIPTION:
 **  Round integers to nearest multiple of 20
 **		Example :
 **		110 -> 120, -110 -> -100
 **     109 -> 100, -111 -> -120

 ** INPUT:
 **  input - integer value to round.

 ** OUTPUT:
 **  output - rounded integer.

 ** RETURN:
 **  bool success or not.
*/

bool BizMath::RoundNearest20(short input, short% output)
{
	short multiple;
	short remainder;

	// Validation
	if (input >= DEFAULT_VALUE || input <= -DEFAULT_VALUE)
	{
		return false;
	}

	// Round positive number
	if( input >= 0.0 )
	{
		multiple = input / 20;
		remainder = input % 20;
		// Round down
		if (remainder < 10)
		{
			output = 20 * multiple;		   
		}
		// Round up
		else
		{
			output = 20 * (multiple + 1);	
		}
	}
	// Round negative number
	else
	{
		multiple = input / 20;
		remainder = input % 20;
		// Round down
		if (remainder < -10)
		{
			output = 20 * (multiple - 1);	
		}
		// Round up
		else
		{
			output = 20 * multiple;			
		}
	}

	return true;
}

/**
 ** SmoothFirstDerivative()
 **
 ** DESCRIPTION:
 **  Calculate first derivative of a function
 **  using formula after smoothing
 **  input[k]' = 3/[n*(n+1)*(2n+1)] * Sum (j*input[k+j]) , j = -n...n

 ** INPUT:
 **  input[size] - function values,
 **  step - step of abscissa,
 **  n - smoothOrder - Smoothing order.

 ** OUTPUT:
 **  firstDerivative[size] - first derivative,
 **  maximum - maximum value of a derivative (cannot be the first or last 2 points).

 ** RETURN:
 **  bool success or not.
*/

bool BizMath::SmoothFirstDerivative(array<const unsigned short>^ input, const unsigned short size, const unsigned short smoothOrder,
                            const float step, array<float>^ firstDerivative, float% maximum)
{

	// Validation
	if (!ValidateArray(input, size))
	{
		return false;
	}

	// Prevent the Garbage Collector from deleting array's and -
	// output parameters
	pin_ptr<const unsigned short> corInput = &input[0];
	pin_ptr<float> corFirstDerivative = &firstDerivative[0];
	pin_ptr<float> corMaximum = &maximum;
	
	return BizCorSmoothFirstDerivative(corInput, size, smoothOrder,
                            step, corFirstDerivative, corMaximum);
	/*
	if (smoothOrder < 1 || smoothOrder >= DEFAULT_VALUE)
	{
		return false;
	}
	if (size < 2*smoothOrder)
	{
		return false;
	}
	if (step == 0 || step <= -DEFAULT_VALUE || step >= DEFAULT_VALUE) 
	{
		return false;
	}

	float doubleStep = step*2;

	// First points
	firstDerivative[0] = (-input[0] + input[1]) /step;
	
	// Start points (ForwardStep formula)
	for (int i = 1; i < smoothOrder; i++)
	{
		if (i == 1)
		{
			firstDerivative[i] = (input[i+1] - input[i-1]) /doubleStep;
		}
		else
		{
			firstDerivative[i] = (-2*input[i-2] - input[i-1] + input[i+1] + 2*input[i+2]) / ((float)10. * step);
		}
	}

	// Middle points
	float smoothingCoefficient = float(3)/(smoothOrder * (smoothOrder + 1) * (2*smoothOrder + 1)* step);
	for (int i = smoothOrder; i < size - smoothOrder; i++)
	{
		float sum = 0.;
		for (int j = -smoothOrder; j <= smoothOrder; j++)
		{
			if (j != 0) 
			{
				sum += j * input[i + j];
			}
		}
		firstDerivative[i] = sum * smoothingCoefficient;
	}

	// End points (BackStep formula)
	for (int i = size - smoothOrder; i < size - 1; i++)
	{
		if (i == size - 2)
		{
			firstDerivative[i] = (input[i+1] - input[i-1]) /doubleStep;
		}
		else
		{
			firstDerivative[i] = (-2*input[i-2] - input[i-1] + input[i+1] + 2*input[i+2]) / ((float)10. * step);
		}
	}
  
	// Last point
	firstDerivative[size - 1] = (input[size - 1] - input[size - 2]) /step;

	// Find the maximum, not including the first or last 2 points
	array<const float>^ subset = gcnew array<const float>(size - 3);
	Array::Copy(firstDerivative, 1, subset, 0, size - 3);
	// MaximumInArray cannot return false because we've already validated the array
	MaximumInArray(subset, size - 3, maximum);
	return true;*/
}

#pragma unmanaged
bool BizCorSmoothFirstDerivative(const unsigned short* input, const unsigned short size, const unsigned short smoothOrder,
                            const float step, float* firstDerivative, float* maximum)
{

	if (smoothOrder < 1 || smoothOrder >= DEFAULT_VALUE)
	{
		return false;
	}
	if (size < 2 * smoothOrder)
	{
		return false;
	}
	if (step == 0 || step <= -DEFAULT_VALUE || step >= DEFAULT_VALUE) 
	{
		return false;
	}

	float doubleStep = step * 2;

	// First points
	firstDerivative[0] = (-input[0] + input[1]) /step;
	
	// Start points (ForwardStep formula)
	for (unsigned short i = 1; i < smoothOrder; i++)
	{
		if (i == 1)
		{
			firstDerivative[i] = (input[i+1] - input[i-1]) /doubleStep;
		}
		else
		{
			firstDerivative[i] = (-2*input[i-2] - input[i-1] + input[i+1] + 2*input[i+2]) / ((float)10. * step);
		}
	}

	// Middle points
	float smoothingCoefficient = float(3)/(smoothOrder * (smoothOrder + 1) * (2*smoothOrder + 1)* step);
	for (unsigned short i = smoothOrder; i < size - smoothOrder; i++)
	{
		float sum = 0.;
		for (short j = -smoothOrder; j <= smoothOrder; j++)
		{
			if (j != 0) 
			{
				sum += j * input[i + j];
			}
		}
		firstDerivative[i] = sum * smoothingCoefficient;
	}

	// End points (BackStep formula)
	for (unsigned short i = size - smoothOrder; i < size - 1; i++)
	{
		if (i == size - 2)
		{
			firstDerivative[i] = (input[i+1] - input[i-1]) /doubleStep;
		}
		else
		{
			firstDerivative[i] = (-2*input[i-2] - input[i-1] + input[i+1] + 2*input[i+2]) / ((float)10. * step);
		}
	}
  
	// Last point
	firstDerivative[size - 1] = (input[size - 1] - input[size - 2]) /step;

	// Find the maximum, not including the first or last 2 points
	BizCorMaximumInArray(&firstDerivative[1], size - 3, maximum);
	return true;
}
#pragma managed
/**
 ** MaximumInArray(),  MinimumInArray(),  MinimumMaximumInArray()
 **
 ** DESCRIPTION:
 **  find maximum/minimum value in array.

 ** INPUT:
 **  input[size] - array.

 ** OUTPUT:
 **  maximum/minimum value.

 ** RETURN:
 ** bool success or not.
*/

bool BizMath::MaximumInArray (array<const float>^ input, unsigned short size, float% maximum)
{
	// Validation
	if (!ValidateArray(input, size))
	{
		return false;
	}
	
	// Prevent the Garbage Collector from deleting the array
	pin_ptr<const float> corInput = &input[0];
	pin_ptr<float> corMaximum = &maximum;

	return BizCorMaximumInArray (corInput, size, corMaximum);
	/*maximum = input[0];
	// Find the maximum in the array
	for (int i = 0; i < size; i++)
	{
		if (input[i] > maximum)
		{
			maximum = input[i];
		}
	}
	return true;*/
}
#pragma unmanaged
bool BizCorMaximumInArray (const float* input, unsigned short size, float* maximum)
{
	*maximum = input[0];
	// Find the maximum in the array
	for (unsigned short i = 0; i < size; i++)
	{
		if (input[i] > *maximum)
		{
			*maximum = input[i];
		}
	}
	return true;
}
#pragma managed
bool BizMath::MinimumInArray (array<const float>^ input, unsigned short size, float% minimum)
{
	// Validation
	if (!ValidateArray(input, size))
	{
		return false;
	}

	minimum = input[0];
	// Find the minimum in the array
	for (unsigned short i = 0; i < size; i++)
	{
		if (input[i] < minimum)
		{
			minimum = input[i];
		}
	}
	return true;
}

bool BizMath::MinimumMaximumInArray (array<const float>^ input, unsigned short size, float% minimum, float% maximum)
{
	// Validation
	if (!ValidateArray(input, size))
	{
		return false;
	}
	// Prevent the Garbage Collector from deleting the array
	pin_ptr<const float> corInput = &input[0];
	pin_ptr<float> corMinimum = &minimum;
	pin_ptr<float> corMaximum = &maximum;

	return BizCorMinimumMaximumInArray (corInput, size, corMinimum, corMaximum);
	/*maximum = input[0];
	minimum = input[0];
	// Find the minimum and maximum in the array
	for (int i = 0; i < size; i++)
	{
		if (input[i] > maximum)
		{
			maximum = input[i];
		}
		if (input[i] < minimum)
		{
			minimum = input[i];
		}
	}
	return true;*/
}
#pragma unmanaged
bool BizCorMinimumMaximumInArray (const float* input, unsigned short size, float* minimum, float* maximum)
{
	*maximum = input[0];
	*minimum = input[0];
	// Find the minimum and maximum in the array
	for (unsigned short i = 0; i < size; i++)
	{
		if (input[i] > *maximum)
		{
			*maximum = input[i];
		}
		if (input[i] < *minimum)
		{
			*minimum = input[i];
		}
	}
	return true;
}
#pragma managed
bool BizMath::MinimumMaximumInArray (array<const unsigned short>^ input, unsigned short size, unsigned short% minimum, unsigned short% maximum)
{
	// Validation
	if (!ValidateArray(input, size))
	{
		return false;
	}

	// Prevent the Garbage Collector from deleting the array
	pin_ptr<const unsigned short> corInput = &input[0];
	pin_ptr<unsigned short> corMinimum = &minimum;
	pin_ptr<unsigned short> corMaximum = &maximum;

	return BizCorMinimumMaximumInArray (corInput, size, corMinimum, corMaximum);
	/*maximum = input[0];
	minimum = input[0];
	// Find the minimum and maximum in the array
	for (int i = 0; i < size; i++)
	{
		if (input[i] > maximum)
		{
			maximum = input[i];
		}
		if (input[i] < minimum)
		{
			minimum = input[i];
		}
	}
	return true;*/
}
#pragma unmanaged
bool BizCorMinimumMaximumInArray (const unsigned short* input, unsigned short size, unsigned short* minimum, unsigned short* maximum)
{
	*maximum = input[0];
	*minimum = input[0];
	// Find the minimum and maximum in the array
	for (unsigned short i = 0; i < size; i++)
	{
		if (input[i] > *maximum)
		{
			*maximum = input[i];
		}
		if (input[i] < *minimum)
		{
			*minimum = input[i];
		}
	}
	return true;
}
#pragma managed

/**
** Find the index of where the maximum resides within an array.
*/
bool BizMath::MaximumInArrayIndex(array<const float>^ input, unsigned short size, unsigned short% maximumIndex)
{
	// Validation
	if (!ValidateArray(input, size))
	{
		return false;
	}
	
	float maximum = input[0];
	maximumIndex = 0;
	// Find the index of the maximum in the array
	for (unsigned short i = 0; i < size; i++)
	{
		if (input[i] > maximum)
		{
			maximum = input[i];
			maximumIndex = i;
		}
	}
	return true;
}

/**
 ** GetSplineIndex()
 **
 ** DESCRIPTION:
 **  Find SplineIndex (beginning of a spline) for pulse.

 ** INPUT:
 **  abscissa - abscissa of a point on a Pulse,
 **  size - length of a pulse.

 ** OUTPUT:
 **  newSplineIndex - new spline index.

 ** RETURN:
 **  bool success or not.
*/
bool BizMath::GetSplineIndex(const float abscissa, const unsigned short splineIndex, const unsigned short size, unsigned short% newSplineIndex)
{
	// Validation
	if (abscissa < 0 || abscissa >= DEFAULT_VALUE)
	{
		return false;
	}
	if (splineIndex >= DEFAULT_VALUE)
	{
		return false;
	}
	if (size < 1 || size >= DEFAULT_VALUE)
	{
		return false;
	}
	
	newSplineIndex = splineIndex;
	
	// Limit point in spline to switch on next spline
	int limit = 2; 

	// Step to increment spline initial point
	int step = 1;  

	// Special case for the pulse end
	if (abscissa >= size - (DEFAULT_SPLINE_ORDER + 1))
	{
		newSplineIndex = size - (DEFAULT_SPLINE_ORDER + 1);
	}
	// Check if the limit has been overcome
	else if (abscissa > splineIndex + limit)
	{
		newSplineIndex += step;
	}
	return true;
}

/**
 ** Spline()
 **
 ** DESCRIPTION:
 **  Find a value of polinomial spline approximation in point abscissa of Pulse profile.

 ** INPUT:
 **  abscissa - abscissa of a point on a Pulse,
 **  input[splineOrder + 1] - Pulse section.

 ** OUTPUT:
 **  output - pulse value.

 ** RETURN:
 **  bool success or not.
*/

bool BizMath::Spline(const float abscissa, array<const float>^ input, float% output)
{
	// Validation
	if (abscissa < 0 || abscissa >= DEFAULT_VALUE)
	{
		return false;
	}
	
	if (!ValidateArray(input, DEFAULT_SPLINE_ORDER + 1))
	{
		return false;
	} 

	// L-coordinates of spline
	float L2 = abscissa/DEFAULT_SPLINE_ORDER;
	float L1 = 1 - L2;

	// Calculate spline basic function
	static float function[4];
	function[0] = L1*(3*L1-1)*(3*L1-2)/2;
	function[1] = 9*L1*L2*(3*L1-1)/2;
	function[2] = 9*L1*L2*(3*L2-1)/2;
	function[3] = L2*(3*L2-1)*(3*L2-2)/2;
         
	// Calculate output
	output = 0.;
	for (unsigned short i = 0; i <= DEFAULT_SPLINE_ORDER; i++)
	{
		output += function[i]*input[i];
	}
	return true;
}

/**
 ** SmoothArray()
 **
 ** DESCRIPTION:
 **  Smooth array using Running average algorithm.

 ** INPUT:
 **  input[size] - float array.
 
 ** OUTPUT:
 **  input rewritten.

 ** RETURN:
 **  true if success, false otherwise.
*/
bool BizMath::SmoothArray(array<float>^ input, const unsigned short size)
{
	// Validation
	if (!ValidateArray(input, size))
	{
		return false;
	} 

	// Copy the input array
	array<float>^ copy = gcnew array<float>(size);
	Array::Copy(input, copy, size);

	// Smooth the first point
	float sum;
	input[0] = (copy[0] + copy[1]) / (float)2;
	
	// Smooth starting points
	for(unsigned short i = 1; i < DEFAULT_SMOOTH_ORDER; i++ )
	{
		sum = 0;
		unsigned short limit = i * 2 + 1;
		for(unsigned short j = 0; j < limit; j++)
		{
			sum += copy[j];
		}
		input[i] = sum / limit;
	}
  
	// Smooth middle points
	unsigned short nofFilterPoints = DEFAULT_SMOOTH_ORDER * 2 + 1;
	for (unsigned short i = DEFAULT_SMOOTH_ORDER; i < size - DEFAULT_SMOOTH_ORDER; i++)
	{
		sum = 0.;
		for (int j = -DEFAULT_SMOOTH_ORDER; j <= DEFAULT_SMOOTH_ORDER; j++)
		{
			sum += copy[i+j];
		}
		input[i] = sum / nofFilterPoints;
	}
	
	// Smooth end points
	for(unsigned short i = size - DEFAULT_SMOOTH_ORDER; i < size - 1; i++)
	{
		sum = 0;
		unsigned short limit = (size - 1 - i) * 2 + 1;
		for(unsigned short j = 0; j < limit; j++)
		{
			sum += copy[size - 1 - j];
		}
		input[i] = sum / limit;
	}
	
	// Smooth last point
	input[size - 1] = (copy[size - 1] + copy[size - 2]) / (float)2;
	
	// Success
	return true;
}

/**
 ** IndexOfExtremum()
 **
 ** DESCRIPTION:
 **  Find index of the first Extremal Maximum value for pulse
 **  between indexes start and end, greater than the threshold.

 ** INPUT:
 **  start, end - indexes,
 **  input - float array,
 **	 threshold.

 ** OUTPUT:
 **  Index.

 ** RETURN:
 **  true if success, false otherwise.
*/

bool BizMath::IndexOfExtremum(array<const float>^ input, const unsigned short start, const unsigned short end, 
							  const float threshold, unsigned short% index)
{
	// Validation
	if (!ValidateArray(input, end + 1))
	{
		return false;
	} 
	// Prevent the Garbage Collector from deleting array's and -
	// output parameters
	pin_ptr<const float> corInput = &input[0];
	pin_ptr<unsigned short> corIndex = &index;
	
	return BizCorIndexOfExtremum(corInput, start, end, threshold, corIndex);
	
	/*if (start < 0 || start > end - 2)
	{
		return false;
	}
	if (threshold <= -DEFAULT_VALUE || threshold > DEFAULT_VALUE)
	{
		return false;
	}
	
	// Find Extremum for Pulse where current > last, current >= next
	float current, last, next;
	for (int i = start + 1; i < end; i++)
	{
		current = input[i];
		// If threshold is the DEFAULT VALUE, then find the first extremum
		if (threshold == DEFAULT_VALUE || current > threshold)
		{
			last = input[i-1];
			next = input[i+1];

			// Check conditions for maximum
			if (current > last && current >= next)
			{
				index = i;
				return true;
			}
		}
	}
	// No extremum was found
	return false;*/
}

#pragma unmanaged
bool BizCorIndexOfExtremum(const float* input, const unsigned short start, const unsigned short end, 
							  const float threshold, unsigned short* index)
{
	// Validation
	if (start > end - 2)
	{
		return false;
	}
	if (threshold <= -DEFAULT_VALUE || threshold > DEFAULT_VALUE)
	{
		return false;
	}
	
	// Find Extremum for Pulse where current > last, current >= next
	float current, last, next;
	for (unsigned short i = start + 1; i < end; i++)
	{
		current = input[i];
		// If threshold is the DEFAULT VALUE, then find the first extremum
		if (threshold == DEFAULT_VALUE || current > threshold)
		{
			last = input[i-1];
			next = input[i+1];

			// Check conditions for maximum
			if (current > last && current >= next)
			{
				*index = i;
				return true;
			}
		}
	}
	// No extremum was found
	return false;
}
#pragma managed
/**
 ** FunctionValue()
 **
 ** DESCRIPTION:
 **  Find value of function at argument.

 ** INPUT:
 **  function[size] - function,
 **  argument - point to find value at.

 ** OUTPUT:
 **  value at point argument.

 ** RETURN:
 **  true if success, false otherwise.
*/
bool BizMath::FunctionValue(array<const unsigned short>^ function, const unsigned short size, const float argument, float% value)
{
	// Validation
	if (!ValidateArray(function, size))
	{
		return false;
	} 
	
	// Prevent the Garbage Collector from deleting the array
	pin_ptr<const unsigned short> corFunction = &function[0];
	pin_ptr<float> corValue = &value;
	
	return BizCorFunctionValue(corFunction, size, argument, corValue);
	/*if (argument < 0 || argument > size - 1)
	{
		return false;
	}

	// Catch start point
	if (argument == 0) 
	{
		value = function[0];
		return true;
	}

	// Finding Value
	for (int i = 1; i < size; i++)
	{
		float moment = (float)i;
		if (moment >= argument)
		{
			// Linear interpolation
			float N1 = moment - argument;
			float N2 = (float)1 - N1;
			value = N1*function[i-1] + N2*function[i];
			break;
		}
	}
	return true;*/
}
#pragma unmanaged
bool BizCorFunctionValue(const unsigned short* function, const unsigned short size, const float argument, float* value)
{
	// Validation
	if (argument < 0 || argument > size - 1)
	{
		return false;
	}

	// Catch start point
	if (argument == 0) 
	{
		*value = function[0];
		return true;
	}

	// Finding Value
	for (unsigned short i = 1; i < size; i++)
	{
		float moment = (float) i;
		if (moment >= argument)
		{
			// Linear interpolation
			float N1 = moment - argument;
			float N2 = (float)1 - N1;
			*value = N1 * function[i-1] + N2 * function[i];
			break;
		}
	}
	return true;
}