/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
      Copyright (C) PWV MEDICAL PTY LTD, 1998

	    Filename 	  	:  TSignal.H
      Author        :  Sergei Eremenko
      Revision      :  1.00
      Date          :  21 Dec 98

  	  Description 	:	DECLARATION of TSignal Class
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
//---------------------------------------------------------------------------
#ifndef PWASignalsH
#define PWASignalsH
#include "TSignal.h"
#include <vcl\db.hpp>
//---------------------------------------------------------------------------
const int PWA_DER1_ALGORITHM = 1;
const int PWA_DER2_ALGORITHM = 2;
const int PWA_TANGENT_DER1_ALGORITHM = 3;
const int PWA_TANGENT_DER2_ALGORITHM = 4;
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// TPWASignal class
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
class TPWASignal: public TSignal
{
  // friend class TPressure, TPWASite;
  public:
    float *Der1; // Signal derivative1
    float *Der2; // Signal derivative2
    // Constructors, destructors
    TPWASignal(const int pMaxNofPoints = 0, const int pMaxNofOnsets = 0);
    TPWASignal::~TPWASignal();
    void Allocate(const int pMaxNofPoints, const int pMaxNofOnsets);
    // Validate Signal
    bool ValidateSignal(const int pMinNofPoints);
    // Try to fix Dbase3 memo field format problem
    // bool FixUpDbase3Problem(const int pMinNofPoints);
    // Find Trigger points for signal
    bool FindOnsets(const int pAlgorithm, const int pMinTrigPt);
    // Find onsets using Der1 = 0 algorithm
    bool AlgorithmDer1(const float pMaxDer1, const int pMinTrigPt,
                       const int pMinPulseLength);
    // Find onsets using maxDer2 algorithm
    bool AlgorithmDer2(const float pMaxDer1, const int pMinTrigPt,
                       const int pMinPulseLength);
    // Find onsets using tangent algorithm (crossing of
    // pulse foot line by tangent at point of max dP/dt
    bool AlgorithmTangentDer1(const float pMaxDer1, const int pMinTrigPt,
                       const int pMinPulseLength);
    // Find onsets using tangent algorithm (crossing of
    // pulse foot line by tangent at point of max Der2
    bool AlgorithmTangentDer2(const float pMaxDer1, const int pMinTrigPt,
                       const int pMinPulseLength);
};
#endif
