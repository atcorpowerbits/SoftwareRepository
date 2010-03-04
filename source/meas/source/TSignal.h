/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
      Copyright (C) PWV MEDICAL PTY LTD, 1998

	    Filename 	  	:  TSignal.H
      Author        :  Sergei Eremenko
      Revision      :  1.00
      Date          :  21 Dec 98

  	  Description 	:	DECLARATION of TSignal Class
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
//---------------------------------------------------------------------------
#ifndef TSignalH
#define TSignalH
#include <vcl\db.hpp>

const int SIGNAL_ECG_MIN_HEART_RATE = 30;
const int SIGNAL_ECG_MAX_HEART_RATE = 200;
const int SIGNAL_ECG_MIN_PULSEHEIGHT = 50;
const int SIGNAL_MAX_APPEND_LEN = 3072;    // max signal sample rate * 1/ min heart rate (bpm)
const int SIGNAL_ECG_MIN_SIGNAL_LENGTH = 128 * 5;

class TSignal
{
  friend class TPWA;
  friend class TPWV; //TPressure, TPWVSite;
  public:

    int           NofPoints;       // Number of accounted points in signal=SIGNAL_MAX_PPOINTS)
    int           NofOnsets;      // Actual number of onsets
    float         *Signal;        // Signal array
    short int     *Onsets;        // Trigger Points (mark start & end of pulses)
    short int     *TrigPts;       // Other name for TrigPts
    float         *FloatOnsets;   // Float onsets for PWV
    short int     SampleRate;     // Signal Sample rate
    // Quality control parameters
    float QC_PulseHeight;
    float QC_PulseHeightVariation;
    float QC_PulseLengthVariation;
    float QC_BaseLineVariation;

  private:
    bool  ReadyToCapture;
    int   CurrentIndex;
  protected:
    int   MaxNofPoints; // Maximal NofPoints
    int   MaxNofOnsets; // Maximal NofOnsets

    // Constructors, destructors
    TSignal();
    TSignal(const int pNofPoints, const int pNofOnsets);
    ~TSignal();
    // private functions


  public:
    // Member functions:

    // Initialise properties
    void Initialise(const int pSampleRate);
    void Allocate(const int pMaxNofPoints, const int pMaxNofOnsets);

    // Set default values for onsets not touching Signal
    void SetDefaults(const int pSampleRate);

    // populate TSignal class properties from current record in pDataSet
    bool Populate(TDataSet* pDataSet, const String pSignalField,
                  const String pOnsetsField, const String pFloatOnsetsField = "");

    // Store TSignal class properties to pDataSet
    bool Store(TDataSet* pDataSet, const String pSignalField,
               const String pOnsetsField, const String pFloatOnsetsField = "");

    // Store signal packet from tonometer in Signal array
    bool CaptureSignalPacket(const short int *pInput, const int pLength);

    // Store whole signal from tonometer in Signal array
    bool CaptureSignal(const float *pInput, const int pLength);

    // Store signal packet from tonometer in Signal array
    bool CaptureSignalPacket(const float *pInput, const int pLength);

    // Store whole signal from tonometer in Signal array
    bool CaptureSignal(const short int *pInput, const int pLength);

    void PrepareToCapture()
    {
      ReadyToCapture = true;
    }
    // Read Signal array from file
    bool ReadFromFile(const String pFileName, const int pColumn,
                      const int pNofColumns);
    // Save Signal to file
    bool SaveToFile(const String pFileName);
    // Getting current value of a signal
    bool GetNextValue(short int &pValue);
    // Setting CurrentIndex to -1
    void ResetIndex();

    // Generate Signal array as a SIN Wave
    bool Generate(const int pHeartRate, const int pAmplitude,
                  const int pBaseLine, const int pTimePhase,
                  const int pSignalDuration);

    // Validate Signal length
    bool ValidateSignalLength(const int pMinNofPoints);
    // Validate Signal amplitude
    bool ValidateSignalHeight(const int pMinHeight);

    // Validate pressure record before storing in Database
    bool ValidateBeforeStore(const int pMinNofPoints, const int pMinNofOnsets,
                             const int pMinHeight);

    // Get trigger points from populated TrigPts array and calculate their number
    bool GetFloatOnsetsFromArray(const int pLength, const int pFactor = 1);

    // Calculate Quality Control parameters for a Signal
    bool QualityControls();

    void Append(float *pBuffer, int pBuffer_length);
};

#endif
