/*
 * pwa_data.h
 *
 * Created: 9/10/2012 11:16:00 AM
 *  Author: yoonl
 */ 


#ifndef PWA_DATA_H_
#define PWA_DATA_H_

#define DEFAULT_VALUE			(uint16_t)9999
#define DEFAULT_FLOAT_VALUE		(float)-1
//#define PWA_MAX_CAPTURE_TIME	(uint8_t)5
#define PRESSURE_PULSE_MAXLENGTH (uint16_t)260
#define MEAS_DEFAULT_SAMPLE_RATE (uint8_t)128
//#define DEFAULT_SAMPLE_RATE		(uint16_t)256
#define PWA_ACCEPTABLE_DATA_THRESHOLD	(uint8_t)120
#define DEFAULT_SMOOTH_ORDER	(uint8_t)2
#define DEFAULT_SPLINE_ORDER	(uint8_t)3
#define MAX						(bool)true
#define MIN						(bool)false
#define MORE					(bool)true
#define LESS					(bool)false
#define FIRST					(bool)true
#define GLOBAL					(bool)false
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

uint16_t *rawSignal; // Original waveform digital unit, 128 sample rate, but may not need if the board sample rate is 128.
float *floatSignal; // For Brachial and Peripheral signals calculation.
float *Central_floatSignal;
int16_t *integerOnsets; // For Brachial and Peripheral signals calculation.
uint16_t onsetsLength; // For Brachial and Peripheral signals calculation.
int16_t *Central_integerOnsets;
uint16_t Central_onsetsLength;

uint16_t signalLength; // For Brachial, Peripheral, Central signals calculation.

int16_t Brachial_SP;
int16_t Brachial_DP;
int16_t Brachial_MeanP;

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
}Peripheral_Parameters;

// Central output parameters for report.
typedef struct  
{
	int16_t ExpPulse_T1;
	int16_t ExpPulse_T2;
	float SP;
	float DP;
	float MeanP;
	float AGPH;
	float AP;
	float HR;
	float SEVR;
}Central_Parameters;

#endif /* PWA_DATA_H_ */