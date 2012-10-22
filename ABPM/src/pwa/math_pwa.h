/*
 * math_pwa.h
 *
 * Created: 11/10/2012 9:53:51 AM
 *  Author: yoonl
 */ 


#ifndef MATH_PWA_H_
#define MATH_PWA_H_

#include "asf.h"
#include <stdio.h>

// Smooth array using Running average algorithm
bool Math_SmoothArray(float *pArray, const uint16_t pSize);

// Convert time in msec into index
bool Math_TimeToIndex(const float time, const uint8_t expandRate, const uint8_t sampleRate, int16_t *index);

// Round real numbers to nearest integer
bool Math_Round(float input, int16_t *output);
// Round real numbers to nearest integer, but return short for convinent way
int16_t Math_Round_Return(float input);

// Calculate smooth first derivative of a function and find max
bool Math_SmoothFirstDerivative(const float* input, const uint16_t size, const int8_t smoothOrder,
	const float step, float* firstDerivative, float* maximum);

// Find SplineIndex (beginning of a spline) for pulse
bool Math_GetSplineIndex(const float abscissa, const uint16_t splineIndex, const uint16_t size, uint16_t *newSplineIndex);

// Find a value of spline approximation of order SplineOrder in point abscissa of
// pulse profile together with different number of derivatives
bool Math_Spline(const float abscissa, const float* profile, const int8_t splineOrder, float* value, float *derivatives, const int8_t numOfDerivatives);

// Find index of the first Extremal Maximum value for pulse between indexes start and end, greater than the threshold
bool Math_IndexOfExtremum(const float *input, const bool minOrMax, const bool onlyFirst, const int16_t index1, const int16_t index2,
	const bool lessOrMore, const float lessOrMoreThan, int16_t* index);

// Find onsets using maxDer2 algorithm
bool Math_AlgorithmDer2(float* derivatives1, float* derivatives2, const float* floatSignal,
	uint16_t signalLength, uint16_t maximumOnsetsLength,
	const float pAvMaxDer1, const int16_t pMinTrigPt, const int16_t pMinPulseLength,
	int16_t* integerOnsets, uint8_t* onsetsLength);

#endif /* MATH_PWA_H_ */