//---------------------------------------------------------------------------
#ifndef PWAPulseH
#define PWAPulseH
//---------------------------------------------------------------------------
#include "Pulse.h"
//---------------------------------------------------------------------------
// PWAPulse class
//---------------------------------------------------------------------------
class TPWAPulse : public TPulse
{
  public:
    int T1;        // Index of the 1st peak
    int T2;        // Index of the 2nd peak
    int ED;        // Index of ejection duration
    int QualityT1; // quality of T1
    int QualityT2; // quality of T2
    int QualityED; // quality of ED
    // Variables for lgorithm to find T1, T2, ED
    int OurCase;   // Distinquish cases
    int MainPeak;  // main (highest) peak
    int PeakBeforeMain; // peak before main
    int PeakAfterMain;  // peak after main
    int ShoulderBeforePeak; // Shoulder before main peak
    int ShoulderAfterPeak;  // Shoulder after main peak
    int PeakOfDer1;         // Peak of first derivative

    int T2m;                // Min der3 for T2
    int Tr;                 // Time of reflected wave (Max Der2)

    int EndT2;              // End of effective length of pulse after cut tail
    int EndNofPoints;       // NofPoints to define limit length of Expanded pulse
    // Local Zone - shift to prevent finding neighbourhood points
    int LocalZoneNofPoints;          // NofPoints in local zone
    int StabilityZoneNofPoints;      //NofPoints to analyse extremum stability
    int OtherStabilityZoneNofPoints; //NofPoints to analyse extremum stability
    TPWAPulse();
    // Member functions:
    void Initialise(const int pSampleRate = 0);

    // Find points of T1, T2, ED (not real time)
    bool FindT1T2ED (TPulse *Der1, TPulse *Der2, TPulse *Der3, const int pExpandFactor, const int pSampleRate,
        const int pED = -1, const int pCentralMainPeak = -1,  /*const int pCentralSecondPeak = -1,*/
        const int pPeriphMainPeak = -1, const int pLimitT1T2 = -1,
        TPulse *CentralDer1 = NULL, TPulse *CentralDer2 = NULL);

};
#endif
