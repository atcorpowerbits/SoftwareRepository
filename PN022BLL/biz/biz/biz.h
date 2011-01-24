// biz.h

#pragma once

#include <biz_namespace.h>

using namespace System;

START_BIZ_NAMESPACE

// Must declare these again to be used in unmanaged functions
static const unsigned short DEFAULT_VALUE = 9999;											// Default value for properties
static const float DEFAULT_FLOAT_VALUE = (float) -1;											// Default value for properties

// Configuration
static const unsigned short CONFIG_ID_PWV = 0x01;
static const unsigned short CONFIG_ID_PWA_CUFF = 0x02;
static const unsigned short CONFIG_ID_PWA_TONO = 0x03;
static const unsigned short CONFIG_ID_PWA_CUFF_TONO = 0x04;
static const unsigned short CONFIG_ID_PWA_TONO_PWV	= 0x05;
static const unsigned short CONFIG_ID_PWA_CUFF_PWV = 0x06;
static const unsigned short CONFIG_ID_NIBP_PWV = 0x07;
static const unsigned short CONFIG_ID_NIBP = 0x08;
static const unsigned short CONFIG_ID_NIBP_PWA_CUFF_TONO =	0x09;
static const unsigned short CONFIG_ID_NIBP_PWA_CUFF = 0x0A;
static const unsigned short CONFIG_ID_NIBP_PWA_TONO = 0x0B;
static const unsigned short CONFIG_ID_NIBP_PWA_CUFF_PWV = 0x0C;
static const unsigned short CONFIG_ID_NIBP_PWA_TONO_PWV = 0x0D;
static const unsigned short CONFIG_ID_NIBP_PWA_CUFF_TONO_PWV = 0x0E;

// Measure Class
static const unsigned short DEFAULT_SAMPLE_RATE = 256;										// 256 Hz for EM4
static const unsigned short MIN_SAMPLE_RATE = 128;											// 128 Hz when downsampled
static const unsigned short MAX_SAMPLE_RATE = 1024;										// 1024 Hz when upsampled
static const unsigned short DEFAULT_CAPTURE_TIME = 5;										// 5 seconds
static const unsigned short MIN_CAPTURE_TIME = 5;											// 5 seconds
static const unsigned short MAX_CAPTURE_TIME = 20;											// 20 seconds
static const unsigned short QUALITY_REFRESH_INTERVAL = 1000;								// in msec
static const unsigned short DATA_REVISION = 200;											// Identifies the mathematical revision of this application
static const unsigned int MEA_HEIGHT_CM_MIN = 20;
static const unsigned int MEA_HEIGHT_CM_MAX= 221;
static const unsigned int MEA_HEIGHT_INCH_MIN = 8;
static const unsigned int MEA_HEIGHT_INCH_MAX = 87;
static const unsigned int MEA_WEIGHT_KG_MIN = 3;
static const unsigned int MEA_WEIGHT_KG_MAX = 227;
static const unsigned int MEA_WEIGHT_LB_MIN = 7;
static const unsigned int MEA_WEIGHT_LB_MAX = 500;
static const unsigned int MEA_BP_MIN = 30;
static const unsigned int MEA_BP_MAX = 250;
static const unsigned int MEA_SP2DP_DIFF_MIN = 10;
static const unsigned int MEA_MP2DP_DIFF_MIN = 5;
static const unsigned int MEA_SP2MP_DIFF_MIN = 5;
static const float CONVERT_INCH_TO_CM = (float) 2.54;
static const float CONVERT_POUND_TO_KILO = (float) 0.4536;

typedef enum
{
AUDIT_ORIGINAL,
AUDIT_MODIFIED,
AUDIT_DELETED,
AUDIT_NOF_FLAGS
} auditChangeType;																	// Audit flag types


// PWV Class
static const unsigned short DEFAULT_FEMORAL_TO_CUFF_DISTANCE = 200;						// 200mm
static const unsigned short PWV_DISTANCE_MIN = 10;
static const unsigned short PWV_DISTANCE_MAX = 2200;
static const unsigned short PWV_FEMORAL_TO_CUFF_DISTANCE_MIN = 10;
static const unsigned short PWV_FEMORAL_TO_CUFF_DISTANCE_MAX = 700;
static const float MIN_VALID_PULSELENGTH_PERCENT = (float) 0.70;							// Pulse is invalid if PulseLength percent -
static const float MAX_VALID_PULSELENGTH_PERCENT = (float) 1.3;								// of Average < 0.7 or > 1.3
static const float DEFAULT_CORRECTION_TIME = (float) 40;									// 40ms correction from cuff to femoral artery
static const unsigned short DEFAULT_DEFLATION_TIME = 7;										// secs ahead to deflate the cuff before completely deflated
static const unsigned short MIN_NUMBER_OF_DELTAS = 3;										// Minimal number of Valid pulse differences
static const float MAX_PWV  = (float) 25;													// 25 m/s is the maximum calculated Pulse Wave Velocity
static const float MIN_PWV = (float) 1;														// 1 m/s is the minimum calculated Pulse Wave Velocity
static const float MIN_ADULT_PWV = (float) 4;												// 4 m/s is the minimum calculated Pulse Wave Velocity for an adult (>18 y.o.)
static const float VALID_STANDARD_DEVIATION = (float) 0.1;									// A valid standard deviation is considered to be <= 10% of the Pulse Wave Velocity
static const float HIGH_STANDARD_DEVIATION = (float) 0.30;									// A standard deviation > 30% of the Pulse Wave Velocity is considered high
static const float VALID_CAROTID_PULSE_HEIGHT = (float) 300;								// A valid carotid signal has an average pulse height above 300 digital units
static const float VALID_CAROTID_PULSE_HEIGHT_VARIATION = (float) 5;						// A valid carotid signal has an average pulse height variation below 5%
static const float VALID_FEMORAL_PULSE_HEIGHT = (float) 300;								// A valid femoral signal has an average pulse height above 300 digital units
static const float NORMAL_RANGE_COEFFICIENT_1 = (float) 0;								// Coefficients of the polynomial equation for the normal range
static const float NORMAL_RANGE_COEFFICIENT_2 = (float) 0.2;
static const float NORMAL_RANGE_COEFFICIENT_3 = (float) 0;
static const float NORMAL_RANGE_CONFIDENCE_OFFSET = (float) 0;

public enum BloodPressureEnumeration														// Blood pressure categories based on SP
{
	BLOOD_PRESSURE_OPTIMAL,
	BLOOD_PRESSURE_NORMAL,
	BLOOD_PRESSURE_HIGH_NORMAL,
	BLOOD_PRESSURE_GRADE_I,
	BLOOD_PRESSURE_GRADE_II_III
};

static const unsigned short BLOOD_PRESSURE_OPTIMAL_LIMIT = 120;								// Defines the optimal blood pressure range (mmHg)
static const unsigned short BLOOD_PRESSURE_NORMAL_LIMIT = 130;								// Defines the normal blood pressure range (mmHg)
static const unsigned short BLOOD_PRESSURE_HIGH_NORMAL_LIMIT = 140;							// Defines the high normal blood pressure range (mmHg)
static const unsigned short BLOOD_PRESSURE_GRADE_I_LIMIT = 160;								// Defines the grade I blood pressure range (mmHg)
static const float SUBRACTING_DISTANCE_CONVERSION_FACTOR = (float) 0.45;					// Used to calculate the reference range distance (mm)
static const float HEIGHT_CONVERSION_FACTOR = (float) 2.1;									// Used to calculate the reference range distance (mm)
static const float SUBRACTING_DISTANCE_CONVERSION_OFFSET = (float) 80;						// Used to calculate the reference range distance (mm)
static const float PULSE_WAVE_VELOCITY_CONVERSION_FACTOR = (float) 0.8;						// Used to calculate the reference range pulse wave velocity (m/s)
	
// Quality Class
static const unsigned short QUALITY_UPDATE_INTERVAL = 1;									// Update quality information every 1 second
static const unsigned short TONOMETER_SIGNAL_STRENGTH_POOR = 200;							// Indicates a poor signal
static const unsigned short TONOMETER_SIGNAL_STRENGTH_GOOD = 300;							// Indicates a good signal
static const unsigned short MINIMUM_TONOMETER_SIGNAL_STRENGTH = 80;							// Indicates a valid signal strength
static const unsigned short MINIMUM_TONOMETER_BASELINE = 120;								// Indicates a valid signal baseline
static const unsigned short CUFF_SIGNAL_STRENGTH_GOOD = 300;							    // Indicates a good signal
static const unsigned short MINIMUM_CUFF_SIGNAL_STRENGTH = 80;						        // Indicates a valid signal strength
static const unsigned short MINIMUM_CUFF_BASELINE = 120;								     // Indicates a valid signal baseline

// Signal Class
static const unsigned short MAX_HEART_RATE = 220;													// 200 bpm
static const unsigned short MIN_HEART_RATE = 30;													// 30 bpm
static const unsigned short MAX_SIGNAL_LENGTH = MAX_CAPTURE_TIME * DEFAULT_SAMPLE_RATE;	// 20 seconds * sampleRate
static const unsigned short MIN_SIGNAL_LENGTH = MIN_CAPTURE_TIME * DEFAULT_SAMPLE_RATE;	// 5 seconds * sampleRate
static const unsigned short MAX_ONSETS = (MAX_CAPTURE_TIME * MAX_HEART_RATE / 60) + 1;				// Maximum Pulses. Add 1 to allow for rounding
static const unsigned short MIN_ONSETS = MIN_CAPTURE_TIME * MIN_HEART_RATE / 60;					// Minimum Pulses. OK to round down
static const unsigned short MAX_PULSE_LENGTH = 60 * MAX_SAMPLE_RATE / MIN_HEART_RATE;				// Maximum length of a pulse
static const unsigned short MIN_PULSE_LENGTH = 60 * MIN_SAMPLE_RATE / MAX_HEART_RATE;				// Minimum length of a pulse
static const unsigned short TONOMETER_MIN_SIGNAL_HEIGHT = 40;								// Minimum amplitude in digital units
static const unsigned short CUFF_MIN_SIGNAL_HEIGHT = 40;									// Minimum amplitude in digital units

public enum SignalTypeEnumeration														// Signal types
{
	CAROTID_SIGNAL,
	FEMORAL_SIGNAL
};

// Math Class
static const unsigned short DEFAULT_SPLINE_ORDER = 3;										// Cubic spline is optimal
static const unsigned short DEFAULT_SMOOTH_ORDER = 2;										// Order of running average algoritm	
static const unsigned short SIGNAL_SMOOTH_ORDER = 3;										// Smooth order of the signal class
static const float SIGNAL_STEP = 1;														// Step size of the signal class
static const float FIRST_DERIVATIVE_THRESHOLD1 = (float) 0.70;
static const float FIRST_DERIVATIVE_THRESHOLD2 = (float) 0.65;
static const float FIRST_DERIVATIVE_THRESHOLD3 = (float) 0.40;								// To find Average Peak of Der1

END_BIZ_NAMESPACE
