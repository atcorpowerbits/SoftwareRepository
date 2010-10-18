// biz.h

#pragma once

//using namespace System;

namespace Biz {

	const short DEFAULT_VALUE = 9999;			// Default value for properties
	
	const short MAX_HR = 200;					// 200 bpm
	const short MIN_HR = 30;					// 30 bpm

	const short DEFAULT_SPLINE_ORDER = 3;		// Cubic spline is optimal
	const short DEFAULT_SMOOTH_ORDER = 2;		// Order of running average algoritm	
	const short SIGNAL_SMOOTH_ORDER = 3;		// Smooth order of the signal class
	const float SIGNAL_STEP = 1;				// Step size of the signal class
	
	const short DEFAULT_SAMPLE_RATE = 256;		// 256 Hz for EM4
	const short MIN_SAMPLE_RATE = 128;			// 128 Hz when downsampled
	const short MAX_SAMPLE_RATE	= 1024;			// 1024 Hz when upsampled
	const short MIN_CAPTURE_TIME = 5;			// 5 seconds
	const short MAX_CAPTURE_TIME = 20;			// 20 seconds
	
	const short MAX_SIGNAL_LENGTH = MAX_CAPTURE_TIME * DEFAULT_SAMPLE_RATE;	// 20 seconds * sampleRate
	const short MIN_SIGNAL_LENGTH = MIN_CAPTURE_TIME * DEFAULT_SAMPLE_RATE;	// 5 seconds * sampleRate
	const short MAX_ONSETS = (MAX_CAPTURE_TIME * MAX_HR / 60) + 1;			// Maximum Pulses. Add 1 to allow for rounding
	const short MIN_ONSETS = MIN_CAPTURE_TIME * MIN_HR / 60;				// Minimum Pulses. OK to round down
	const short MAX_PULSE_LENGTH = 60 * MAX_SAMPLE_RATE / MIN_HR;			// Maximum length of a pulse
	const short MIN_PULSE_LENGTH = 60 * MIN_SAMPLE_RATE / MAX_HR;			// Minimum length of a pulse

	const short TONOMETER_MIN_SIGNAL_HEIGHT = 40;							// Minimum amplitude in digital units
	const short CUFF_MIN_SIGNAL_HEIGHT = 40;								// Minimum amplitude in digital units

	const float FIRST_DERIVATIVE_THRESHOLD1 = (float) 0.70;
	const float FIRST_DERIVATIVE_THRESHOLD2 = (float) 0.65;
	const float FIRST_DERIVATIVE_THRESHOLD3 = (float) 0.40;			// To find Average Peak of Der1

	const unsigned short CAPTURE_EXTRA_FOR_HANDSHAKE = 2; // seconds

	const unsigned short CONFIG_ID_PWV = 0x01;
	const unsigned short CONFIG_ID_PWA_CUFF = 0x02;
	const unsigned short CONFIG_ID_PWA_TONO = 0x03;
	const unsigned short CONFIG_ID_PWA_CUFF_TONO = 0x04;
	const unsigned short CONFIG_ID_PWA_TONO_PWV	= 0x05;
	const unsigned short CONFIG_ID_PWA_CUFF_PWV = 0x06;
	const unsigned short CONFIG_ID_NIBP_PWV = 0x07;
	const unsigned short CONFIG_ID_NIBP = 0x08;
	const unsigned short CONFIG_ID_NIBP_PWA_CUFF_TONO =	0x09;
	const unsigned short CONFIG_ID_NIBP_PWA_CUFF = 0x0A;
	const unsigned short CONFIG_ID_NIBP_PWA_TONO = 0x0B;
	const unsigned short CONFIG_ID_NIBP_PWA_CUFF_PWV = 0x0C;
	const unsigned short CONFIG_ID_NIBP_PWA_TONO_PWV = 0x0D;
	const unsigned short CONFIG_ID_NIBP_PWA_CUFF_TONO_PWV = 0x0E;

	const unsigned int CUFF_STATE_DISCONNECTED = 1;
	const unsigned int CUFF_STATE_CONNECTED_DEFLATED = 2;
	const unsigned int CUFF_STATE_INFLATING = 3;
	const unsigned int CUFF_STATE_INFLATED = 4;
	const unsigned int CUFF_STATE_DEFLATING = 5;
	const unsigned int CUFF_STATE_RESTING = 6;
}

