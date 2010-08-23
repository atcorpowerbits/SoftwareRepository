// biz.h

#pragma once

using namespace System;

namespace Biz {

	const short DEFAULT_VALUE = 9999;			// Default value for properties
	
	const short MAX_HR = 200;					// 200 bpm
	const short MIN_HR = 30;					// 30 bpm

	const short DEFAULT_SPLINE_ORDER = 3;		// Cubic spline is optimal
	const short DEFAULT_SMOOTH_ORDER = 2;		// Order of running average algoritm	
	
	const short DEFAULT_SAMPLE_RATE = 256;	// 256 Hz for EM4
	const short MIN_CAPTURE_TIME = 5;			// 5 seconds
	const short MAX_CAPTURE_TIME = 20;		// 20 seconds
	
	const short MAX_SIGNAL_LENGTH = MAX_CAPTURE_TIME * DEFAULT_SAMPLE_RATE;	// 20 seconds * sampleRate
	const short MIN_SIGNAL_LENGTH = MIN_CAPTURE_TIME * DEFAULT_SAMPLE_RATE;	// 5 seconds * sampleRate
	const short MAX_ONSETS = (MAX_CAPTURE_TIME * MAX_HR / 60) + 1;			// Maximum Pulses. Add 1 to allow for rounding
	const short MIN_ONSETS = MIN_CAPTURE_TIME * MIN_HR / 60;				// Minimum Pulses. OK to round down

	const short TONOMETER_MIN_SIGNAL_HEIGHT = 40;							// Minimum amplitude in digital units
	const short CUFF_MIN_SIGNAL_HEIGHT = 40;								// Minimum amplitude in digital units
}

