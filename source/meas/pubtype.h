/*
**
** Copyright (C) PWV MEDICAL PTY LTD, 1998
**
** FILE NAME     : MEAS\PUBTYPE.H
**
** PROJECT       : TITAN SWCI
**
** OBJECT        : MEAS (Measurement)
**
** DESCRIPTION   : Definition of objects Public types.
**
** AUTHOR        : Sergei Eremenko
**
** DATE CREATED  : 28/10/98
**
*/
//---------------------------------------------------------------------------
#ifndef MEAS_PUBTYPE
#define MEAS_PUBTYPE

//#define PWV_SHORT_STUDY_ENABLED

//---------------------------------------------------------------------------
const int NOF_TF_COEFF = 33;
const int MEAS_MATH_DATA_REVISION = 130;

/*
** Minimum time in seconds to capture pressure waveform for a PWA Calculation
*/
const int MEAS_PWA_MIN_CAPTURE_TIME = 9;

const int MEAS_DEFAULT_SAMPLE_RATE = 128;

//---------------------------------------------------------------------------
const String PERIPH_PREFIX = "P_";
const String CENTRAL_PREFIX = "C_";
const String PREFIX_A = "A_";
const String PREFIX_B = "B_";
//---------------------------------------------------------------------------
const int MIN_PRESS = 0;
const int MAX_PRESS = 999;
const int MAX_TIME = 500;
const int MAX_HR = 200;
const int MIN_HR = 30;
const int MIN_DP = 30;
const int MAX_SP = 250;
const int MEAS_MAX_DPDT = 1650;
const int MEAS_MIN_DPDT = 350;
const int MIN_HEIGHT = 20;
const int MAX_HEIGHT = 220;
const int MIN_FEET = 0;
const int MIN_INCH = 8;
const int MAX_FEET = 7;
const int MAX_INCH = 3;
const int MIN_WEIGHT = 3;
const int MAX_WEIGHT = 227;
const int MIN_POUND = 6;
const int MAX_POUND = 500;
const int MAX_DISTANCE = 2200;
const int MIN_DISTANCE = 10;
const int DEFAULT_PH_PERCENT = 10;
const int MIN_PH_PERCENT = 1;
const int MAX_PH_PERCENT = 50;
const float PWV_TOO_LARGE  = 25; //This is largest that the calculated Pulse Wave Velocity can be
const float PWV_TOO_SMALL = 4;   //This is smallest that the calculated Pulse Wave Velocity can be
//---------------------------------------------------------------------------
const float PWA_MIN_T1              = 80.0;
const float PWA_MAX_T1              = 150.0;
const float PWA_MIN_T1_RATIO        = 70.0;
const int   PWA_MIN_OPERATOR_INDEX  = 75;
const int   PWA_GOOD_OPERATOR_INDEX = 85;
//---------------------------------------------------------------------------
const int DEFAULT_VALUE = 9999; // Default value for properties
//---------------------------------------------------------------------------
// Gradation for Quality T1, T2, ED
const int VERYSTRONG = 0;
const int STRONG = 1;
const int WEAK = 2;
const int VERYWEAK = 3;

#ifdef PWV_SHORT_STUDY_ENABLED
   const int PWV_SHORT_STUDY = 5;
   const int PWV_SHORT_STUDY_ID = 10;
#else
   const int PWV_SHORT_STUDY = 10;
   const int PWV_SHORT_STUDY_ID = 1;
#endif

//---------------------------------------------------------------------------
const String MPWA = "M_PWA";
const String MPWV = "M_PWV";
const String MPWM = "M_PWM";
const String MHRV = "M_HRV";
const String MPWMTREND = "PWM_TREND";
const String MPWMSESSION = "PWM_SESSION";
const String MPWMDEVICE = "PWM_DEVICE";
//---------------------------------------------------------------------------
// Both PWA and PWV table fields
const String MPW_SYSTEM_ID     = "SYSTEM_ID";
const String MPW_PATIENT_NO    = "PATIENT_NO";
const String MPW_DATE          = "DATE";
const String MPW_TIME          = "TIME";
const String MPW_DATA_REV      = "DATA_REV";
const String MPW_OPERATOR      = "OPERATOR";
const String MPW_SPARE1        = "SPARE1";
const String MPW_SP            = "SP";
const String MPW_DP            = "DP";
const String MPW_MP            = "MP";

// M_PWA table fields
const String MPWA_SUB_TYPE     = "SUB_TYPE";
const String MPW_STUDY_ID      = "STUDY_ID";
const String MPW_MED           = "MEDICATION";
const String MPW_NOTES         = "NOTES";
const String MPW_INTERPRETATION   = "MEMSPARE1";
const String MHRV_INTERPRETATION  = "MEM_SPARE1";
const String MPWA_SIGNAL_UPSAMPLE_RATE = "SIGNAL_UPSAMPLE_RATE";
const String MPWA_EXPPULSE_UPSAMPLE_RATE = "EXPPULSE_UPSAMPLE_RATE";
const String MPWA_TONOMETER    = "FLOATSPARE1";

const String MPWA_MED_1        = "MED_1";
const String MPWA_MED_2        = "MED_2";
const String MPWA_NOTES_1      = "NOTES_1";
const String MPWA_NOTES_2      = "NOTES_2";

const String MPW_HEIGHT        = "HEIGHT";
const String MPW_WEIGHT        = "WEIGHT";
const String MPW_BMI           = "BODY_MASS_INDEX";
const String MPW_SAMPLE_RATE   = "SAMPLE_RATE";
const String MPW_DATETIME      = "DATETIME";
const String MPW_SIMULATION    = "INTSPARE1";
const String MHRV_SIMULATION   = "INT_SPARE1";
const String MPWV_SIMULATION   = "FLOAT_SPARE1";

const String MPWA_CARDIAC_OUTPUT= "CARDIAC_OUTPUT";
const String MPWA_FLOW          = "FLOW";
const String MPWA_HR            = "HR";
const String MPWA_ED            = "ED";
const String MPWA_CALC_ED       = "CalcED";
const String MPWA_QUALITY_ED    = "QUALITY_ED";
const String MPWA_P_PULSES      = "P_PULSES";
const String MPWA_P_AV          = "P_AV";
const String MPWA_P_TRIGS       = "P_TRIGS";
const String MPWA_P_SP          = "P_SP";
const String MPWA_P_DP          = "P_DP";
const String MPWA_P_MEANP       = "P_MEANP";
const String MPWA_P_T1          = "P_T1";
const String MPWA_P_T2          = "P_T2";
const String MPWA_P_AI          = "P_AI";
const String MPWA_P_MAX_DPDT    = "P_MAX_DPDT";

const String MPWA_P_NOISE_FACTOR    = "P_NOISE_FACTOR";
const String MPWA_P_QC_PH           = "P_QC_PH";
const String MPWA_P_QC_PHV          = "P_QC_PHV";
const String MPWA_P_QC_PLV          = "P_QC_PLV";
const String MPWA_P_QC_DV           = "P_QC_DV";
const String MPWA_P_QC_SCALE_FACTOR = "P_QC_OTHER1";
const String MPWA_P_QC_SD           = "P_QC_OTHER2";
const String MPWA_P_QC_OI           = "P_QC_OTHER4";

const String MPWA_P_SPARE1          = "P_SPARE1";
const String MPWA_C_PULSES          = "C_PULSES";
const String MPWA_C_AV              = "C_AV";
const String MPWA_C_TRIGS           = "C_TRIGS";
const String MPWA_C_SP              = "C_SP";
const String MPWA_C_DP              = "C_DP";
const String MPWA_C_MEANP           = "C_MEANP";
const String MPWA_C_T1              = "C_T1";
const String MPWA_C_T2              = "C_T2";
const String MPWA_C_AI              = "C_AI";
const String MPWA_C_AP              = "C_AP";
const String MPWA_C_MPS             = "C_MPS";
const String MPWA_C_MPD             = "C_MPD";
const String MPWA_C_ESP             = "C_ESP";
const String MPWA_C_TTI             = "C_TTI";
const String MPWA_C_DTI             = "C_DTI";
const String MPWA_C_SVI             = "C_SVI";
const String MPWA_C_SPARE1          = "C_SPARE1";
const String MPWA_C_SPARE2          = "C_SPARE2";
const String MPWA_C_PERIOD          = "C_PERIOD";
const String MPWA_C_DD              = "C_DD";
const String MPWA_C_ED_PERIOD       = "C_ED_PERIOD";
const String MPWA_C_DD_PERIOD       = "C_DD_PERIOD";
const String MPWA_C_PH              = "C_PH";
const String MPWA_C_AGPH            = "C_AGPH";
const String MPWA_C_P1_HEIGHT       = "C_P1_HEIGHT";
const String MPWA_C_T1R             = "C_T1R";
const String MPWA_C_AL              = "C_AL";
const String MPWA_C_ATI             = "C_ATI";
const String MPWA_C_FLOW            = "C_FLOW";
const String MPWA_C_FORWARD         = "C_FORWARD";
const String MPWA_C_BACKWARD        = "C_BACKWARD";
const String MPWA_C_AVI             = "C_AVI";
const String MPWA_C_PPTT            = "C_PPTT";
const String MPWA_C_AVD             = "C_AVD";
const String MPWA_C_PWV             = "C_PWV";
const String MPWA_C_FORWARD_AREA    = "C_FORWARD_AREA";
const String MPWA_C_BACKWARD_AREA   = "C_BACKWARD_AREA";
const String MPWA_C_AREA_RATIO      = "C_AREA_RATIO";
const String MPWA_C_PULSE_RATIO     = "C_PULSE_RATIO";

// Next are FieldNames without prefix P_ or C_
// to pick up pressures appropriate pressures
const String MPWA_NO_PULSES      = "PULSES";
const String MPWA_NO_AV          = "AV";
const String MPWA_NO_UNCAL_AV    = "UNCAL_AV";
const String MPWA_NO_EXPPULSE    = "EXPPULSE";
const String MPWA_NO_TRIGS       = "TRIGS";
const String MPWA_NO_SP          = "SP";
const String MPWA_NO_DP          = "DP";
const String MPWA_NO_MEANP       = "MEANP";
const String MPWA_NO_T1          = "T1";
const String MPWA_NO_CALCT1      = "T1Other";
const String MPWA_NO_T2          = "T2";
const String MPWA_NO_CALCT2      = "T2Other";
const String MPWA_NO_P1          = "P1";
const String MPWA_NO_P2          = "P2";
const String MPWA_NO_T1ED        = "T1ED";
const String MPWA_NO_T2ED        = "T2ED";
const String MPWA_NO_QT1         = "QUALITY_T1";
const String MPWA_NO_QT2         = "QUALITY_T2";
const String MPWA_NO_AI          = "AI";
const String MPWA_NO_ESP         = "ESP";
const String MPWA_NO_AP          = "AP";
const String MPWA_NO_MPS         = "MPS";
const String MPWA_NO_MPD         = "MPD";
const String MPWA_NO_TTI         = "TTI";
const String MPWA_NO_DTI         = "DTI";
const String MPWA_NO_SVI         = "SVI";
const String MPWA_NO_SPARE1      = "SPARE1";
const String MPWA_NO_SPARE2      = "SPARE2";

// MPWV Table Fields
const String MPWV_SP             = "SP";
const String MPWV_DP             = "DP";
const String MPWV_MP             = "MP";

const String MPWV_MED_1         = "MED1";
const String MPWV_MED_2         = "MED2";
const String MPWV_MED_3         = "MED3";
const String MPWV_MED_4         = "MED4";
const String MPWV_NOTES_1       = "NOTES1";
const String MPWV_NOTES_2       = "NOTES2";
const String MPWV_NOTES_3       = "NOTES3";
const String MPWV_NOTES_4       = "NOTES4";
const String MPWV_HEIGHT        = "HEIGHT";
const String MPWV_WEIGHT        = "WEIGHT";
const String MPWV_BMI           = "BMI";

const String MPWV_PX_DIST        = "PX_DIST";
const String MPWV_DT_DIST        = "DT_DIST";
const String MPWV_PWV_DIST       = "PWV_DIST";
const String MPWV_ALGORITHM      = "ALGORITHM";
const String MPWV_PHEIGHT_PC     = "PHEIGHT_PC";
const String MPWV_QC_SCALE_FACTOR = "INT_SPARE1";
const String MPWV_TONOMETER       = "FLOAT_SPARE2";

const String MPWV_TON_QC_PH      = "TON_QC_PH";
const String MPWV_TON_QC_PHV     = "TON_QC_PHV";
const String MPWV_TON_QC_PLV     = "TON_QC_PLV";
const String MPWV_TON_QC_BLV     = "TON_QC_BLV";
const String MPWV_ECG_QC_PH      = "ECG_QC_PH";
const String MPWV_ECG_QC_PHV     = "ECG_QC_PHV";
const String MPWV_ECG_QC_PLV     = "ECG_QC_PLV";
const String MPWV_ECG_QC_BLV     = "ECG_QC_BLV";

const String MPWV_PP_MDT         = "PP_MDT";
const String MPWV_PP_SDEV        = "PP_SDEV";
const String MPWV_PWV            = "PWV";
const String MPWV_PWVERR         = "PWVERR";

const String MPWV_NOPSETS        = "NOPSETS";
const String MPWV_NODT           = "NODT";
const String MPWV_NOVALDT        = "NOVALDT";
const String MPWV_SUBTYPE        = "SUBTYPE";
const String MPWV_HR             = "HR";
const String MPWV_MDT            = "MDT";
const String MPWV_STD            = "SDEVDT";
const String MPWV_NOTONON        = "NOTONON";
const String MPWV_NOECGON        = "NOECGON";
const String MPWV_TONPULSES      = "TONPULSE";
const String MPWV_ECGPULSES      = "ECGPULSE";
const String MPWV_TONON          = "TONON";
const String MPWV_ECGON          = "ECGON";

const String MPWV_DT             = "DT";
const String MPWV_NOF_10_SETS    = "NOF_10_SETS";
const String MPWV_NOF_VALID_DT   = "NOF_VALID_DT";
const String MPWV_DEVIATION_DT   = "DEVIATION_DT";
const String MPWV_PP_DEVIATION   = "PP_DEVIATION";
const String MPWV_PWV_DISTERR    = "PWV_DISTERR";
const String MPWV_DISTERR        = "PWVDISTERR";
const String MPWV_TON_WAVEFORM   = "TON_WAVEFORM";
const String MPWV_ECG_WAVEFORM   = "ECG_WAVEFORM";
const String MPWV_TON_ONSETS     = "TON_ONSETS";
const String MPWV_ECG_ONSETS     = "ECG_ONSETS";

// MPWM Table Fields
const String MPWM_SESSION_ID = "SESSION_ID";
const String MPWM_PARAM_ID = "PARAM_ID";
const String MPWM_PARAM_NAME = "PARAM_NAME";
const String MPWM_PARAM_TREND = "PARAM_TREND";
const String MPWM_SESSION_START = "SESSION_START";
const String MPWM_SESSION_FINISHED = "SESSION_FINISHED";
const String MPWM_SESSION_NOTES = "NOTES";
const String MPWM_SESSION_CALIBRATED = "CALIBRATED";
const String MPWM_SESSION_DEVICE_ID = "DEVICE_ID";
const String MPWM_TREND_SAMPLE_PERIOD = "TREND_SAMPLE_PERIOD";
const String MPWM_DEVICE_CALIBRATION_RATIO = "CALIBRATION_FACTOR";
const String MPWM_DEVICE_CALIBRATION_OFFSET = "FLOATSPARE1";
const String MPWM_DEVICE_CONTINUOUS = "CONTINUOUS";
const String MPWM_DEVICE_NAME = "DEVICE_NAME";
const String MPWM_SESSION_EVENT_COMMENT = "OLESPARE1";

// MHRV Table Fields
const String MHRV_MEASURE_TYPE          = "METHOD";
const String MHRV_START_TIME            = "START_TIME";
const String MHRV_RTOR_INTERVALS        = "RTOR_INTERVALS";
const String MHRV_UNUSUAL_BEATS         = "UNUSUAL_BEATS";
const String MHRV_NUMBER_PULSES         = "NUMBER_PULSES";
const String MHRV_START_PULSE           = "START_PULSE";
const String MHRV_END_PULSE             = "END_PULSE";
const String MHRV_ECG                   = "ECG";
const String MHRV_HISTOGRAM             = "HISTOGRAM";
const String MHRV_MEAN                  = "MEAN";
const String MHRV_MAXIMUM               = "MAXIMUM";
const String MHRV_MINIMUM               = "MINIMUM";
const String MHRV_MAX_MIN               = "MAX/MIN";
const String MHRV_RANGE                 = "RANGE";
const String MHRV_STANDARD_DEVIATION    = "STANDARD_DEVIATION";
const String MHRV_MODE                  = "MODE";
const String MHRV_NN50                  = "NN50";
const String MHRV_PNN50                 = "PNN50";
const String MHRV_RMS_SD               = "RMS_SDD";
const String MHRV_HRV_INDEX             = "HRV_INDEX";
const String MHRV_TRIANGULAR_INDEX      = "TRIANGULAR_INDEX";
const String MHRV_SEGMENT_LENGTH        = "SEGMENT_LENGTH";
const String MHRV_NUMBER_SEGMENTS       = "NUMBER_SEGMENTS";
const String MHRV_SDANN                 = "SDANN";
const String MHRV_SDNN                  = "SDNN";
const String MHRV_POWER_SPECTRUM        = "POWER_SPECTRUM";
const String MHRV_FREQUENCY             = "FREQUENCY";
const String MHRV_SPECTRUM_POINTS       = "SPECTRUM_POINTS";
const String MHRV_LF_POWER              = "LF_POWER";
const String MHRV_LF_POWER_NORMALISED   = "LF_POWER_NORMALISED";
const String MHRV_HF_POWER              = "HF_POWER";
const String MHRV_HF_POWER_NORMALISED   = "HF_POWER_NORMALISED";
const String MHRV_LF_HF_RATIO           = "LF_HF_RATIO";
const String MHRV_LF_MAXIMUM            = "LF_MAXIMUM";
const String MHRV_HF_MAXIMUM            = "HF_MAXIMUM";
const String MHRV_SPECTRUM_MAXIMUM      = "SPECTRUM_MAXIMUM";
const String MHRV_TOTAL_POWER           = "TOTAL_POWER";
const String MHRV_BREATHING_HIGH        = "BREATHING_HIGH";
const String MHRV_BREATHING_LOW         = "BREATHING_LOW";
const String MHRV_BREATHING_RATIO       = "BREATHING_RATIO";
const String MHRV_STAND_HIGH            = "STAND_HIGH";
const String MHRV_STAND_LOW             = "STAND_LOW";
const String MHRV_STAND_RATIO           = "STAND_RATIO";
const String MHRV_VALSALVA_HIGH         = "VALSALVA_HIGH";
const String MHRV_VALSALVA_LOW          = "VALSALVA_LOW";
const String MHRV_VALSALVA_RATIO        = "VALSALVA_RATIO";



//---------------------------------------------------------------------------
typedef enum
{
  PWA_RADIAL,
  PWA_CAROTID,
  PWA_AORTIC,
  PWA_NOF_MEASURES
} PWA_MEASURE_TYPE;

const String PWAMTypeAsString [PWA_NOF_MEASURES] =
{
   "RADIAL",
   "CAROTID",
   "NPROC"
};
//---------------------------------------------------------------------------
typedef enum
{
  PWV_RADIAL,
  PWV_CAROTID,
  PWV_FEMORAL,
  PWV_PROXIMAL,
  PWV_DISTAL,
  PWV_NOF_MEASURES
} PWV_MEASURE_TYPE;

const String PWVMTypeAsString [PWV_NOF_MEASURES] =
{
   "RADIAL",
   "CAROTID",
   "FEMORAL",
   "PROXIMAL",
   "DISTAL"
};
//---------------------------------------------------------------------------
typedef enum
{
   HRV_NORMAL = 1,
   HRV_VALSALVA,
   HRV_STAND,
   HRV_NOF_MEASURES
} HRV_MEASURE_TYPE;

const String HRVMTypeAsString [HRV_NOF_MEASURES] =
{
   "HRV CALCULATION",
   "VALSALVA MANOEUVRE",
   "STAND MANOEUVRE"
};
//---------------------------------------------------------------------------
// Delta T data structure
//---------------------------------------------------------------------------
typedef struct
{
	float Value; // time differences (in ms) between tonometer & ECG pulse onsets
							 // time difference of (-1) value indicates that the delta t could not
							 // be calculated due to tonometer or ECG onset being missing
	bool Valid;  // delta t is valid/invalid
  // short int Valid;
} TDelta;

typedef enum
{
   MEAS_NONE,
   MEAS_PWA_ID,
   MEAS_PWV_ID,
   MEAS_PWM_ID,
   MEAS_HRV_ID
} MEAS_ID_TYPE;

const String AORTIC_TI_NOTE         = "Waveform Timing out of Range. [Aortic T1]";
const String PERIPHERAL_TI_NOTE     = "Waveform Timing out of Range. [Peripheral T1]";
const String T1_RATIO_NOTE          = "Waveform Timing out of Range. [T1 Difference]";
const String OPERATOR_INDEX_NOTE    = "Operator Index low. [<75]";
const String AORTIC_AIX_NOTE        = "Aortic Augmentation Index > 50%.";
const String MAXDPDT_NOTE           = "Systolic Upstroke out of Range. [<350mmHg/s]";
const String SIMULATION             = "SIMULATION MODE";
const String SIMULATION_NOTE        = "NOT ACTUAL PATIENT DATA";
const String ADVICE                 = "Repeat the Measurement. If the Warning Message Persists with Good Operator Index, then the Waveforms are Not the Result of Noise Artifacts.";

#define HRV_MAX_REJECTED_PERCENTAGE    50
#define HRV_MAX_RMS_SD                 200
#define HRV_MAX_PNN50                  75

typedef enum
{
  MEAS_OPERATOR,
  MEAS_BMI,
  MEAS_MEDICATIONS,
  MEAS_NOTES,
  MEAS_INTERPRETATION,
  MEAS_AUDIT,
  MEAS_PRESSURES,
  MEAS_DISTANCE,
  MEAS_ALGORITHM
} MEAS_SENDER_TYPE;

#endif
