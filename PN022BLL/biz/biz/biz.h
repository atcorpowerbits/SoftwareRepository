// biz.h

#pragma once

#include <biz_namespace.h>

//using namespace System;

START_BIZ_NAMESPACE

const unsigned short DEFAULT_VALUE = 9999;											// Default value for properties
const float DEFAULT_FLOAT_VALUE = (float) -1;											// Default value for properties

// Measure Class
const unsigned short DEFAULT_SAMPLE_RATE = 256;										// 256 Hz for EM4
const unsigned short MIN_SAMPLE_RATE = 128;											// 128 Hz when downsampled
const unsigned short MAX_SAMPLE_RATE = 1024;										// 1024 Hz when upsampled
const unsigned short DEFAULT_CAPTURE_TIME = 5;										// 5 seconds
const unsigned short MIN_CAPTURE_TIME = 5;											// 5 seconds
const unsigned short MAX_CAPTURE_TIME = 20;											// 20 seconds
const unsigned short DATA_REVISION = 200;											// Identifies the mathematical revision of this application

// PWV Class
const unsigned short DEFAULT_FEMORAL_TO_CUFF_DISTANCE = 200;						// 200mm
const unsigned short MIN_PWV_DISTANCE = 10;
const unsigned short MAX_PWV_DISTANCE = 2200;
const unsigned short MIN_FEMORAL_TO_CUFF_DISTANCE = 10;
const unsigned short MAX_FEMORAL_TO_CUFF_DISTANCE = 700;
const float MIN_VALID_PULSELENGTH_PERCENT = (float) 0.70;							// Pulse is invalid if PulseLength percent -
const float MAX_VALID_PULSELENGTH_PERCENT = (float) 1.3;							// of Average < 0.7 or > 1.3
const float DEFAULT_CORRECTION_TIME = (float) 40;									// 40ms correction from cuff to femoral artery
const unsigned short MIN_NUMBER_OF_DELTAS = 3;										// Minimal number of VaLid pulse differences
const float MAX_PWV  = (float) 25;													// 25 m/s is the maximum calculated Pulse Wave Velocity
const float MIN_PWV = (float) 1;													// 1 m/s is the minimum calculated Pulse Wave Velocity
const float MIN_ADULT_PWV = (float) 4;												// 4 m/s is the minimum calculated Pulse Wave Velocity for an adult (>18 y.o.)
const float VALID_STANDARD_DEVIATION = (float) 0.1;									// A valid standard deviation is considered to be <= 10% of the Pulse Wave Velocity
const float HIGH_STANDARD_DEVIATION = (float) 0.30;									// A standard deviation > 30% of the Pulse Wave Velocity is considered high
const float	VALID_CAROTID_PULSE_HEIGHT = (float) 300;								// A valid carotid signal has an average pulse height above 300 digital units
const float	VALID_CAROTID_PULSE_HEIGHT_VARIATION = (float) 5;						// A valid carotid signal has an average pulse height variation below 5%
const float	VALID_FEMORAL_PULSE_HEIGHT = (float) 300;								// A valid femoral signal has an average pulse height above 300 digital units

typedef enum
{
  AUDIT_ORIGINAL,
  AUDIT_MODIFIED,
  AUDIT_DELETED,
  AUDIT_NOF_FLAGS
} auditChangeType;																	// Audit flag types

// Signal Class
const unsigned short MAX_HEART_RATE = 200;													// 200 bpm
const unsigned short MIN_HEART_RATE = 30;													// 30 bpm
const unsigned short MAX_SIGNAL_LENGTH = MAX_CAPTURE_TIME * DEFAULT_SAMPLE_RATE;	// 20 seconds * sampleRate
const unsigned short MIN_SIGNAL_LENGTH = MIN_CAPTURE_TIME * DEFAULT_SAMPLE_RATE;	// 5 seconds * sampleRate
const unsigned short MAX_ONSETS = (MAX_CAPTURE_TIME * MAX_HEART_RATE / 60) + 1;				// Maximum Pulses. Add 1 to allow for rounding
const unsigned short MIN_ONSETS = MIN_CAPTURE_TIME * MIN_HEART_RATE / 60;					// Minimum Pulses. OK to round down
const unsigned short MAX_PULSE_LENGTH = 60 * MAX_SAMPLE_RATE / MIN_HEART_RATE;				// Maximum length of a pulse
const unsigned short MIN_PULSE_LENGTH = 60 * MIN_SAMPLE_RATE / MAX_HEART_RATE;				// Minimum length of a pulse
const unsigned short TONOMETER_MIN_SIGNAL_HEIGHT = 40;								// Minimum amplitude in digital units
const unsigned short CUFF_MIN_SIGNAL_HEIGHT = 40;									// Minimum amplitude in digital units

// Math Class
const unsigned short DEFAULT_SPLINE_ORDER = 3;										// Cubic spline is optimal
const unsigned short DEFAULT_SMOOTH_ORDER = 2;										// Order of running average algoritm	
const unsigned short SIGNAL_SMOOTH_ORDER = 3;										// Smooth order of the signal class
const float SIGNAL_STEP = 1;														// Step size of the signal class
const float FIRST_DERIVATIVE_THRESHOLD1 = (float) 0.70;
const float FIRST_DERIVATIVE_THRESHOLD2 = (float) 0.65;
const float FIRST_DERIVATIVE_THRESHOLD3 = (float) 0.40;								// To find Average Peak of Der1

const unsigned int MEA_HEIGHT_CM_MIN = 20;
const unsigned int MEA_HEIGHT_CM_MAX= 220;
const unsigned int MEA_HEIGHT_INCH_MIN = 12;
const unsigned int MEA_HEIGHT_INCH_MAX = 100;
const unsigned int MEA_WEIGHT_KG_MIN = 3;
const unsigned int MEA_WEIGHT_KG_MAX = 227;
const unsigned int MEA_WEIGHT_LB_MIN = 7;
const unsigned int MEA_WEIGHT_LB_MAX = 500;
const unsigned int MEA_BP_MIN = 30;
const unsigned int MEA_BP_MAX = 250;
const unsigned int MEA_SP2DP_DIFF_MIN = 10;
const unsigned int MEA_MP2DP_DIFF_MIN = 5;
const unsigned int MEA_SP2MP_DIFF_MIN = 5;

const unsigned short PWV_DISTANCE_MIN = 10;
const unsigned short PWV_DISTANCE_MAX = 2200;
const unsigned short PWV_FEM2CUFF_MIN = 10;
const unsigned short PWV_FEM2CUFF_MAX = 700;
const unsigned short PWV_MAX_ONSETS = 30 * 3;

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

END_BIZ_NAMESPACE
