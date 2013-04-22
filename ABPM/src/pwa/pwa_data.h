/*
 * pwa_data.h
 *
 * Global parameters to be used in PWA calculations and PWA error codes.
 *
 * Copyright (c) Atcor Medical Pty. Ltd., 2013
 *
 * Created: 9/10/2012 11:16:00 AM
 *  Author: yoonl
 */ 


#ifndef PWA_DATA_H_
#define PWA_DATA_H_

#define DEFAULT_VALUE			(uint16_t)9999
#define PRESSURE_PULSE_MAXLENGTH (uint16_t)260
#define MEAS_DEFAULT_SAMPLE_RATE (uint8_t)128
#define PWA_ACCEPTABLE_DATA_THRESHOLD	(uint8_t)120
#define DEFAULT_SMOOTH_ORDER	(uint8_t)2
#define DEFAULT_SPLINE_ORDER	(uint8_t)3
#define MAX						(bool)true
#define MIN						(bool)false
#define MORE					(bool)true
#define LESS					(bool)false
#define FIRST					(bool)true
#define GLOBAL					(bool)false
#define VERYSTRONG				(int8_t)0
#define STRONG					(int8_t)1
#define WEAK					(int8_t)2
#define VERYWEAK				(int8_t)3
#define PWA_MIN_T1				(float)80.0
#define PWA_MAX_T1				(float)150.0
#define PWA_DER1_THRESHOLD1		(float)0.60
#define PWA_DER1_THRESHOLD2		(float)0.55
#define PWA_DER1_THRESHOLD3		(float)0.40 // To find Average Peak of derivatives1
#define PWA_MIN_NOF_ONSETS		(uint8_t)2
#define MIN_HR					(uint8_t)30
#define MAX_HR					(uint8_t)220
#define PRESSURE_MAX_PPOINTS	(uint16_t)680 //MEAS_DEFAULT_SAMPLE_RATE * PWA_MAX_CAPTURE_TIME + 40(length of transformation + coefficient)
#define PRESSURE_MAX_PULSES		(uint8_t)19 //PWA_MAX_CAPTURE_TIME * MAX_HR / 60
#define PRESSURE_MAX_TPOINTS	(uint8_t)20 //PRESSURE_MAX_PULSES + 1
#define PWA_DER1_ALGORITHM		(uint8_t)1
#define PWA_DER2_ALGORITHM		(uint8_t)2
#define PWA_TANGENT_DER1_ALGORITHM (uint8_t)3
#define PWA_TANGENT_DER2_ALGORITHM (uint8_t)4
#define NOF_TF_COEFF			(uint8_t)33
#define EXPPULSE_MAX_EXPAND_FACTOR	(uint8_t)2
#define PRESSURE_EXPPULSE_MAXLENGTH	(uint16_t)520 //PRESSURE_PULSE_MAXLENGTH * EXPPULSE_MAX_EXPAND_FACTOR
#define HR_MIN_THRESHOLD		(uint8_t)40
#define HR_MAX_THRESHOLD		(uint8_t)110
#define QUALITY_THRESHOLD		(uint8_t)40 // If Operator Index is greater/equal than this value, it means tick, otherwise cross in the report.
#define NIBP_ADULT_MIN_SP		(uint8_t)50
#define NIBP_ADULT_MAX_SP		(uint16_t)260
#define NIBP_ADULT_MIN_DP		(uint8_t)40
#define NIBP_ADULT_MAX_DP		(uint8_t)200
#define MEA_SP2DP_DIFF_MIN		(uint8_t)10


// Major input parameters for PWA calculation given by SunTech.
static volatile int16_t Brachial_SP = 0;
static volatile int16_t Brachial_DP = 0;

// Peripheral output parameters to be used for Periph/Central calculation.
typedef struct
{
	float Gain;
	float Offset;
	float IntegralAver;
	int16_t PeriphMainPeak;
	int16_t ExpPulse_T1;
	int16_t ExpPulse_T2;
	int16_t ExpPulse_T2m;
	int16_t ExpPulse_ShoulderAfterPeak;
	int16_t ExpPulse_ED;
	int16_t QualityT1;
	int16_t OperatorIndex;
}Peripheral_Parameters;

// Central output parameters for report.
typedef struct  
{
	int16_t ExpPulse_T1;
	int16_t ExpPulse_T2;
	float SP;
	float DP;
	float PP; // SP - DP
	float MeanP;
	float AGPH; // Augmentation Index
	float AGPH_HR75; // Augmentation Index normalised for HR 75
	float AP; // Augmented Pressure
	float HR;
}Central_Parameters;

// Quality Control parameters
typedef struct 
{
	float QC_PulseHeightVariation;
	float QC_PulseLengthVariation;
	float QC_PulseHeight;
	float QC_DiastolicVariation;
	float QC_ShapeDeviation;
}QC_Parameters;

// PWA Error Codes, low level error code regarding for processing PWA algorithm, 8 bytes max.
extern uint16_t PWA_Error_Code;
typedef enum
{
	PWA_MSG_OUT_OF_MEMORY = 2000,
	PWA_MSG_CAPTURE_SIGNAL_TOO_LOW,
	PWA_MSG_SIGNAL_TOO_SHORT,
	PWA_MSG_TRIGGER_ERR,
	PWA_MSG_CALCPULSES_ERR,
	PWA_MSG_TOO_BAD_SIGNAL,
	PWA_MSG_WRONG_PULSE,
	PWA_MSG_SMOOTH_ERR,
	PWA_MSG_IRREGULAR_TRIGPTS,
	PWA_MSG_EXPANDPULSE_ERR,
	PWA_MSG_CALCSYSTONSET_ERR,
	PWA_MSG_DOWNSAMPLE_ERR,
	PWA_MSG_CALIBRATE_AVPULSE_PERIPH_ERR,
	PWA_MSG_CALIBRATE_AVPULSE_CENTRAL_ERR,
	PWA_MSG_HR_OUT,
	PWA_MSG_POINT_OUT_OF_PULSE,
	PWA_SP_OUT_OF_RANGE,
	PWA_DP_OUT_OF_RANGE,
	PWA_SP_DP_TOO_CLOSE,
}pwa_error_code_t;

#endif /* PWA_DATA_H_ */