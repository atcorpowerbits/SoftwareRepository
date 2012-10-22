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
#define PWA_MAX_CAPTURE_TIME	(uint8_t)5
#define PRESSURE_PULSE_MAXLENGTH (uint16_t)308
#define MEAS_DEFAULT_SAMPLE_RATE (uint8_t)128
#define DEFAULT_SAMPLE_RATE		(uint16_t)256
#define PWA_ACCEPTABLE_DATA_THRESHOLD_TONOMETER	(uint8_t)120
#define DEFAULT_SMOOTH_ORDER	(uint8_t)2
#define DEFAULT_SPLINE_ORDER	(uint8_t)3
#define MAX						(bool)true
#define MIN						(bool)false
#define MORE					(bool)true
#define LESS					(bool)false
#define FIRST					(bool)true
#define PWA_DER1_THRESHOLD1		(float)0.60
#define PWA_DER1_THRESHOLD2		(float)0.55
#define PWA_DER1_THRESHOLD3		(float)0.40 // To find Average Peak of derivatives1
#define PWA_MIN_NOF_ONSETS		(uint8_t)2
#define MIN_HR					(uint8_t)30
#define MAX_HR					(uint8_t)220
#define PRESSURE_MAX_PPOINTS	(uint16_t)948 //MEAS_DEFAULT_SAMPLE_RATE * PWA_MAX_CAPTURE_TIME + PRESSURE_PULSE_MAXLENGTH
#define PRESSURE_MAX_PULSES		(uint8_t)18 //PWA_MAX_CAPTURE_TIME * MAX_HR / 60
#define PRESSURE_MAX_TPOINTS	(uint8_t)19 //PRESSURE_MAX_PULSES + 1
#define PWA_DER1_ALGORITHM		(uint8_t)1
#define PWA_DER2_ALGORITHM		(uint8_t)2
#define NOF_TF_COEFF			(uint8_t)33
#define EXPPULSE_MAX_EXPAND_FACTOR	(uint8_t)8
#define PRESSURE_EXPPULSE_MAXLENGTH	(uint16_t)2464 //PRESSURE_PULSE_MAXLENGTH * EXPPULSE_MAX_EXPAND_FACTOR

uint16_t *rawSignals; // Original waveform digital unit, 128 sample rate
float *floatSignal;
int16_t *integerOnsets;
uint16_t signalLength;
uint16_t onsetsLength;

#endif /* PWA_DATA_H_ */