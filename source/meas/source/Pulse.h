//---------------------------------------------------------------------------
#ifndef PulseH
#define PulseH
//---------------------------------------------------------------------------
#include "Common.h"
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// TPulse class
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
class TPulse
{
  private:
    short int FLength;   // Length of Pulse between [Start,End]
    short int FMaxSize;  // Maximal possible size of a pulse array
    short int FSize;     // Size of array for pulse
  public:
    float *Profile;     // Pointer on Pulse beginning
    short int Index;    // Index of Pulse beginning in Signal Array
    short int Start;    // Start point of the pulse
    short int End;      // End point of the pulse

    short int SampleRate; // Pulse sample rate

    // Constructor
    TPulse();
    void Initialise(const int pSampleRate = 0);
    // Allocate memory for a pulse
    void Allocate(const int pSize);
    // Free memory for a pulse
    void Free();
    // Validate pulse
    bool Validate();
    // SetSize()
    void SetSize(const int pSize);
    // SetSize()
    void SetMaxSize(const int pMaxSize);
    // Set Length of a pulse from Start to End point
    void SetLength(const int pLength);
    // Extract float Pulse signal from memo field and divide by Divider
    bool ExtractFromBuffer(const char *cProfile, const short int pSize,
                           const int Divider, const int pBase = 2);
    // Find Min, Max for pulse
    bool MinMax(float &pMin, float &pMax);
    // Find Max/Min for pulse between indexes i1, i2
    float Max(const int i1, const int i2);
    float Min(const int i1, const int i2);
    // Find index of maximal (or minimal) value for pulse between indexes i1, i2
    int IndexOfMax(const int i1, const int i2);
    int IndexOfMin(const int i1, const int i2);
    // Find index of Extremal (local) Maximal (or Minimal) value for pulse
    // between indexes i1, i2 with checking stability and limits
    int IndexOfExtremum(const bool pMinOrMax, const bool pOnlyFirst,
                        const int i1, const int i2,

            const int pStabilityZone = 0, const bool pLessOrMore = LESS,
            const float pLessOrMoreThan = DEFAULT_VALUE, const float *Der2 = NULL,

            const float *pOtherFunction = NULL, const bool pOtherLessOrMore = LESS,
            const float pOtherLessOrMoreThan = DEFAULT_VALUE, const int pOtherStabilityZone = 0,

            const float *pOtherFunction2 = NULL, const bool pOtherLessOrMore2 = LESS,
            const float pOtherLessOrMoreThan2 = DEFAULT_VALUE, const int pOtherStabilityZone2 = 0,

            const float *pOtherFunction3 = NULL, const bool pOtherLessOrMore3 = LESS,
            const float pOtherLessOrMoreThan3 = DEFAULT_VALUE, const int pOtherStabilityZone3 = 0,

            const float *pOtherFunction4 = NULL, const bool pOtherLessOrMore4 = LESS,
            const float pOtherLessOrMoreThan4 = DEFAULT_VALUE, const int pOtherStabilityZone4 = 0);

    // Smooth profile using running average algorithm
    bool Smooth(const int pSmoothOrder = 2);
    // Find Gain, Offset coefficients to calibrate pulse in Range [pDp, pSp]
    bool GainOffset(float &pGain, float &pOffset, const float pDp, const float pSp);
    // Find Value of a pulse in x-point pTime
    // assuming each point "contains" SampleRate
    float ValueAsTime(const float pTime); //, const int pSampleRate);
    // Find Value of a pulse in x-point pPoint
    float Value(const float pPoint);
    // Convert Index into time in msec
    float IndexToTime(const int pIndex);
    // Convert Time into index assuming 0 correspond to start point
    int TimeToIndex(const float pTime);
    // Find Average value of a pulse
    float Average();
    // Find pulse average value on interval [pBegin, pEnd]
    float Average(int pBegin, int pEnd);
    // Integrate pulse profile using trapesoid formula on interval [pBegin, pEnd]:
    float Integral();
    float Integral(int pBegin, int pEnd);
    float Integral(int pBegin, int pEnd, int pBaseLine);
    // Find Sum of a pulse sample values
    float Sum();
    // Find pulse sum on  interval [pBegin, pEnd]
    float Sum (int pBegin, int pEnd);
    // Find maximum the 1st derivative of pulse between indexes i1, i2
    float MaxDerivative1(const int i1, const int i2, const int pSmoothOrder = 2);
    // Find pulse end value (Profile[Length-1])
    float PulseEndValue();
    // Find pulse height (Max - Min)
    float Height();
    // Find pulse height (Max - Profile[0])
    float QC_Height();
    // Calculate pulse length between [Start, End]
    int Length();
    // Calculate pulse array size between [0, FSize]
    int Size();
    // Shift Start point to 0 position
    bool Shift();
    // Resample pulse from high to low frequency
    // (for example, from 1024 to 128 Htz)
    bool DownSample(TPulse *pPulse, const int pDownSampleRate);
    // Calculate pulse profile by convolution of input pulse
    bool Convolution(TPulse *pPulse, const float *pTfc, const int pNofTFC);
    // Create a copy of input pulse
    bool Copy(TPulse *pPulse);

  private:
    // Check interval pBegin, pEnd is inside the pulse and show message if not
    bool IsIntervalValid (const int pBegin, const int pEnd, const bool pShowMessage = true);
    // Check extremum stability
    bool IsExtremumStable(const int ExtPoint, const int pBegin, const int pEnd,
      const bool pMaxOrMin, const float *Der2 = NULL);
    // Check whether the function is changing sign (so unstable) in window [i1,i2]
    bool CheckCondition(const int i, const int i1, const int i2,
                        const float *pOtherFunction, const bool pOtherLessOrMore,
                        const float pOtherLessOrMoreThan, const int pOtherStabilityZone);
};
#endif
