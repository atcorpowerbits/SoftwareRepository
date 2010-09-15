/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
      Copyright (C) PWV MEDICAL PTY LTD, 1998

	    Filename 	  	:  TSignal.H
      Author        :  Sergei Eremenko
      Revision      :  1.00
      Date          :  21 Dec 98

  	  Description 	:	DECLARATION of TSignal Class
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
//---------------------------------------------------------------------------
#ifndef PWVSignalsH
#define PWVSignalsH
#include "TSignal.h"
#include <vcl\db.hpp>
//---------------------------------------------------------------------------
const int PWV_MIN_NOF_ONSETS = 4;
const int PWVSITE_MAX_ONSETS = 30 * 3;
const int PWV_TON_MIN_PULSEHEIGHT = 40;
const int PWV_ECG_MIN_PULSEHEIGHT = 80;

typedef enum
{
   ECG_ALGORITHM_ONSET_PEAKS,
   ECG_ALGORITHM_ONSET_LENGTH,
   ECG_ALGORITHM_ONSET_FILTER
} PWV_ECG_ONSET_ALGORITHM_TYPE;



//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// TPWVTonomSignal class
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
class TPWVTonomSignal: public TSignal
{
  // friend class TPressure, TPWVSite;
  public:
    float *Der1; // Signal derivative1
    float *Der2; // Signal derivative2
    // Constructors, destructors
    TPWVTonomSignal(const int pMaxNofPoints = 0, const int pMaxNofOnsets = 0);
    TPWVTonomSignal::~TPWVTonomSignal();
    void Allocate(const int pMaxNofPoints, const int pMaxNofOnsets);
    // Validate Signal
    bool ValidateSignal(const int pMinNofPoints);
    // Find Trigger points for TSignal signal
    bool FindOnsets(const int pAlgorithm, const float pHeightPercent = 0.);
    // Find onsets using Percent of PulseHeight algorithm
    bool Algorithm1(const float pMaxDer1, const int pMinPulseLength, const float pHeightPercent = 0.);
    // Find onsets using maxdP/dt algorithm
    bool Algorithm2(const float pMaxDer1, const int pMinPulseLength);
    // Find onsets using tangent algorithm (crossing of
    // pulse foot line by tangent at point of max dP/dt
    bool Algorithm3(const float pMaxDer1, const int pMinPulseLength);
    // Find onsets using maxDer2 algorithm
    bool Algorithm4(const float pMaxDer1, const int pMinPulseLength, const float *Der2);
};
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// TPWVECGSignal class
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
class TPWVECGSignal: public TSignal
{
  // friend class TPressure, TPWVSite;
  public:
    // Constructors, destructors
    TPWVECGSignal(const int pMaxNofPoints = 0, const int pMaxNofOnsets = 0);
    // Validate Signal
    bool ValidateSignal(const int pMinNofPoints);

    bool FindOnsets(PWV_ECG_ONSET_ALGORITHM_TYPE pAlgorithm, const float pHeightPercent, const float pMinPulseHeight);
    // Find trigger points (onsets) as percentage of Pulse Height for abstract signal

    // Find average pulse height for a signal
    float FindAvPulseHeight(const float pThresHold, const float pMinPulseHeight);

    // Find foot of ECG Signal as a peak of Der2
    void FindFoot(const int i1, const int i2, const float lThreshold, float &pFoot, float &pValue);

    private:
    bool Algorithm1(const float pHeightPercent, const int pMinPulseLength, const float pMinPulseHeight);
    // Find onsets as peak indexes
    bool Algorithm2(const int pMinPulseLength);

    // Detects the R peak in the QRS complex using a morphological filter
    bool Algorithm_QRS_Filter(void);

    void Openingn(int pb, float *pSignal, float *pOpened);

    void Closingn(int pb, float *pOpened, float *pClosed);

    bool Erosion(int pb, float*pSignal, float *pErosion);

    bool Dilation(int pb, float*pSignal, float *pDilation);


};
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#endif
