#ifndef hrvclassH
#define hrvclassH

#include "TSignal.h"
#include "Measure.h"

#define HRV_MAX_SESSION_TIME           180 // Maximum session is 120 minutes
#define HRV_MAX_CAPTURE_PULSES         32000 // The maximum value for a positive integer in Access is 32768
#define HRV_MAX_NUMBER_OF_PULSES       (SIGNAL_ECG_MAX_HEART_RATE * HRV_MAX_SESSION_TIME)  // Max pulses = Max HR for max session time
#define HRV_MAX_TIME_LENGTH            (60 * HRV_MAX_SESSION_TIME) // Max session time in seconds
#define HRV_MAX_REJECTED_PULSES        1400 // Maximum rejected pulses before capture stops
#define HRV_MAX_CAPTURE_TIME           12 // 12 seconds is the maximum screen capture time
#define HRV_MIN_CAPTURE_TIME           6  // 6 seconds is the minimum screen capture time
#define HRV_MAX_NUM_PULSES_IN_SWEEP    (3 * HRV_MAX_CAPTURE_TIME) // Assumes a capture screen of 12 seconds and a HR of 180
#define HRV_MAX_ECG_SAMPLE_RATE        1024 // Hz
#define HRV_MIN_ECG_SAMPLE_RATE        128  // Hz
#define HRV_ECG_MAX_NOF_POINTS         (HRV_MAX_CAPTURE_TIME * HRV_MAX_ECG_SAMPLE_RATE) // Max screen capture time * max sample rate
#define HRV_ECG_MIN_PULSEHEIGHT        80 // The minimum height of a captured signal
#define HRV_RTOR_SAMPLING_PERIOD       1.0 // Sampling period of the frequency spectrum
#define HRV_MIN_CLINICAL_TIME          5 // The minimum capture time in minutes to display clinical normals
#define HRV_SAVED_ECG_LENGTH           (3 * 60 * HRV_MIN_ECG_SAMPLE_RATE) // The last 3 minutes of the ECG are saved
#define HRV_SAVED_ECG_RESOLUTION       (5 * HRV_MIN_ECG_SAMPLE_RATE) // Number of ECG points saved in a 5 second capture screen
#define HRV_FREQ_DEFAULT_SPECTRUM_SIZE 128 // Size of the Fourier Transform spectrum
#define SIGNAL_ECG_MIN_ONSETS          2 // The minimum onsets in a capture screen
#define SIGNAL_ECG_MAX_ONSETS          HRV_MAX_NUM_PULSES_IN_SWEEP // The maximum onsets in a capture screen

bool meas_hrv_initialise(void);

void meas_hrv_destroy(void);

class THRVECGSignal: public TSignal
{
   public:
      // Constructors, destructors
      THRVECGSignal(const int pMaxNofPoints = 0, const int pMaxNofOnsets = 0);
      THRVECGSignal::~THRVECGSignal();

      // Validate Signal
      bool ValidateSignal(const int pMinNofPoints);
      bool FindOnsets(const int pAlgorithm);
      String   onset_error;
   private:
      bool Algorithm_QRS_Filter(void);
      void Openingn(int pb, float *pSignal, float *pOpened);
      void Closingn(int pb, float *pOpened, float *pClosed);
      bool Erosion(int pb, float*pSignal, float *pErosion);
      bool Dilation(int pb, float*pSignal, float *pDilation);

};

class THRV : public TMeasure
{
  public:
      // The raw ecg signal
     THRVECGSignal ecg;

     // Ecg append buffer
     float        *ecg_signal_buffer;
     int          ecg_signal_buffer_len;

     // The displayed ecg signal
     short int    *ecg_signal;
     int          ecg_signal_length;

     // The time of the first captured screen and captured time
     TDateTime  StartTime;
     TDateTime  time_elapsed;

     // Number of pulses captured
     int        PulsesInSession;
     int        StartPulse;
     int        EndPulse;
     int        NofOnsets;

     // Number of Pulses not rejected
     int        PulsesInSession_refined;

     // R to R intervals every sweep
     float      rtor_intervals[HRV_MAX_NUM_PULSES_IN_SWEEP];

     // R to R intervals captured and their time index
     float      RtoR_raw[HRV_MAX_NUMBER_OF_PULSES];
     float      Time_raw[HRV_MAX_NUMBER_OF_PULSES];

     // R to R intervals not rejected and their time index
     float      RtoR_raw_refined [HRV_MAX_NUMBER_OF_PULSES];
     float      Time_raw_refined [HRV_MAX_NUMBER_OF_PULSES];

     // Index of rejected R to R intervals
     short int  index_rejected_rtor[HRV_MAX_REJECTED_PULSES];
     int        number_rejected_rtor;
     int        number_rejected_rtor_tot;

     // Calculated parameters displayed on the capture screen
     float AveHeartRate;
     float AveRtoR;
     float SumRtoR;

     // For the HRV Session File
     int       lFileHandle;

     // The validation error written to the log
     String    error_string;

     // Calculation, Valsalva or Stand
     HRV_MEASURE_TYPE   MeasureType;

     // Constructor and Destructor
     THRV();
     ~THRV();

     // Initialise properties
     void  Initialise(const int pECGSampleRate);
     void  SetDefaults(const int pECGSampleRate);
     void PrepareToCaptureSignal(void);

     // Perform all mathematics for this measurement
     bool Calculate(void);

     // Remove rejected R to R intervals
     void RefineRtoR(void);

     // Calculate R to R intervals
     bool PulseCalc(void);

     // Perform the append and mathematics each sweep
     bool CalculatePulses(void);

     // Locate rejected pulses
     void DetermineUnusualBeats(void);

     // Validation checks
     bool ValidateBeforeCalculate(void);
     bool ValidateBeforeStore(void);

     // Store class properties to current record in pDataSet
     bool Store(TDataSet* pDataSet, bool pRewriteKeyFields, bool pRewriteDate);

     // Populate class properties from current record in pDataSet
     bool Populate(TDataSet* pDataSet);

     // Save the ECG signal to a file
     bool SaveToFile();

     // Save the ECG signal to be displayed
     bool SaveECG();

     // Overide TMeasure's validate functions
     bool ValidateSpDpMp();
     bool ValidateHtWt();

     bool ValidateMeasureType();

     // Export (print) measurement to string
     bool ExportPrintTitle(TDataSet* pDataSet, String &pOut);
     bool Export(String &pOut);
     bool ExportArrays(int pFileHandle);

   private:
      int     nof_ecg_pulses;
      int     PulseCounter;
      float   rtor_intervals_prev;
      int     ecg_sample_rate;
};

#endif
