//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "PWAPulse.h"
#include <msg\pubserv.h>
#include "Common.h"
#include "Mathem.h"
#include <math.h>
#include <stdlib.h>
//---------------------------------------------------------------------------
#pragma package(smart_init)
const float BEGIN_PERCENT = 0.03; // Calculate T1,T2,ED from this percent of length
// const float END_PERCENT = 0.66; // Cut pulse length by this percent
const int NORMAL_ED_MAX = 420;
const int SLOW_HR_ED_MAX = 450;
const float ED_MIN_PERCENT = 0.20; //0.17;
const float ED_MAX_PERCENT = 0.65;  // ED cannot be more then 65% of Length
const float ESP_MAX_PERCENT = 0.75; // ESP cannot be more then 75% of PulseHeight
const float LIMIT_T1T2_FACTOR = 1.2; // Central T2 cannot be more then 1.2* Periph T2
//const float FLAT_AREA_PERCENT = 0.85;
//const float FLATNESS = 0.33;
//---------------------------------------------------------------------------
TPWAPulse::TPWAPulse()
{
  // NofPoints to define limit length of Expanded pulse
  EndNofPoints = 20;
  // Local Zone - shift to prevent finding neighbourhood points
  LocalZoneNofPoints = 4; // NofPoints in local zone
  StabilityZoneNofPoints = 2; // NofPoints in stability zone for extremums
  OtherStabilityZoneNofPoints = 1; // NofPoints in stability zone for central wave
  Initialise();
}
//---------------------------------------------------------------------------
void TPWAPulse::Initialise(const int pSampleRate)
{
  T1 = DEFAULT_VALUE;
  T2 = DEFAULT_VALUE;
  ED = DEFAULT_VALUE;
  QualityT1 = DEFAULT_VALUE;
  QualityT2 = DEFAULT_VALUE;
  QualityED = DEFAULT_VALUE;
  OurCase = -1;
  MainPeak = -1;
  PeakBeforeMain = -1;
  PeakAfterMain = -1;
  ShoulderBeforePeak = 1;
  ShoulderAfterPeak = -1;
  PeakOfDer1 = -1;
  T2m = -1;
  EndT2 = -1;
  Tr = -1;
  TPulse::Initialise(pSampleRate);
}
/* ###########################################################################
 ** FindT1T2ED
 **
 ** DESCRIPTION
 **  Find points of T1, T2, ED (not real time) from ExpPulse
 ** INPUT
 ** TPressure class properties
 ** pED - predefined ED. For periph = -1, for central = Periph.ED
 ** Der1, Der2, Der3 - pulse waveform derivatives
 ** pExpandFactor (8) - Coefficient of expanding sample
 **                     frequency(in ExpandFactor times)
 ** pSampleRate (128) - Signal sample rate
 ** pCentralMainPeak - Main peak for Central Pulse waveform
 ** pPeriphMainPeak - Main peak for peripheral Pulse waveform
 ** pLimitT1T2 - Limit time for T2 (Central)
 ** CentralDer2 - Der2 for Central pulse
 ** OUTPUT
 ** TPressure class properties
 ** RETURN
 **  boolean success or not
*/
//---------------------------------------------------------------------------
bool TPWAPulse::FindT1T2ED (TPulse *Der1, TPulse *Der2, TPulse *Der3,
                const int pExpandFactor, const int pSampleRate,
                const int pED, const int pCentralMainPeak,
                const int pPeriphMainPeak, const int pLimitT1T2,
                TPulse *CentralDer1, TPulse *CentralDer2)
{
  // Is correspondence between Central and Radial to be used?
  bool UseCorrespondence = true; //false; // true;
  float* CD1P = (UseCorrespondence == true && CentralDer1 != NULL ?
                 CentralDer1->Profile : NULL);
  //float* CD2P = (UseCorrespondence == true && CentralDer2 != NULL ?
  //               CentralDer2->Profile : NULL);

  float* CD2P = NULL;

  // Initialisation
  T1 = DEFAULT_VALUE;
  T2 = DEFAULT_VALUE;
  ED = (pED > 0 && pED != DEFAULT_VALUE ?
        pED : DEFAULT_VALUE);

  QualityT1 = DEFAULT_VALUE;
  QualityT2 = DEFAULT_VALUE;
  QualityED = DEFAULT_VALUE;

  PeakAfterMain = -1;  // Main peak
  PeakBeforeMain = -1; // Peak before main
  PeakAfterMain = -1;  // Peak after main

  ShoulderBeforePeak = -1; // Shoulder before main peak
  ShoulderAfterPeak = -1;  // Shoulder after main peak
  T2m = -1;

  // PeakOfDer1 = -1;      // Peak of first derivative. May be don't need

  EndT2 = -1;
  // Local Zone - shift to prevent finding neighbourhood points
  int LocalZone = LocalZoneNofPoints * pExpandFactor;
  // Zone of stability to find stable extremums
  int StabilityZone = min (StabilityZoneNofPoints * pExpandFactor, LocalZone);
  // Zone of stability to find stable extremums with analysis stability of another function as well
  int OtherStabilityZone = min (OtherStabilityZoneNofPoints * pExpandFactor, StabilityZone);

  // Define Effective length of Pulse - the value for which T2 cannot be more
  float lHR = float(60.*pSampleRate*pExpandFactor)/(Length() - 1); // Heart rate
  // Calculate TopED - line ED(HR) from table for adult normals ED
  float lTopEDAtHRLow = 350; float lTopEDAtHRHigh = 220;
  float lHRLow = 50; float lHRHigh = 120;
  float la = (lTopEDAtHRLow - lTopEDAtHRHigh)/(lHRLow - lHRHigh);
  float lb = lTopEDAtHRLow - la*lHRLow;
  int lTopED = la*lHR + lb;
  int lNormalED = lTopED - 32;

/*
  int L = math_TimeToIndex(lTopED, pExpandFactor, pSampleRate);
  int lDefaultED = math_TimeToIndex(lNormalED, pExpandFactor, pSampleRate);
  int lLowED = math_TimeToIndex(lBottomED, pExpandFactor, pSampleRate);
  lLowED = max (lLowED, (int)(ED_MIN_PERCENT*Length));
*/
  // L - effective length of a pulse
  int lLength = Length();
  int L = (lLength/pExpandFactor > 100 ?
           lLength * 0.5 : lLength * 0.55);
           //Length * 0.45 : Length * 0.55);
  if (lLength/pExpandFactor < 85)
    L = lLength * 0.60;
//    L = Length * 0.60;
  if (lLength/pExpandFactor < 70)
//    L = Length * 0.70;
    L = lLength * 0.70;
  // ED cannot be more than ED_MAX msec (?)
  int lEdMax = (lHR < 60 ? SLOW_HR_ED_MAX : NORMAL_ED_MAX);
  L = min(L, math_TimeToIndex(lEdMax, pExpandFactor, pSampleRate));
  // int L = math_TimeToIndex(lTopED, pExpandFactor, pSampleRate);

  int lDefaultED = math_TimeToIndex(lNormalED, pExpandFactor, pSampleRate);

  // Index of 60 msec
  // int t60msec = math_TimeToIndex(60., pExpandFactor, pSampleRate);
  float t60msec = TimeToIndex(60.);

  // For fast HR decrease stability zones
  if (lHR > 90)
  {
    LocalZone /= 1.5;
    StabilityZone /= 1.5;
    OtherStabilityZone /= 1.5;
    t60msec /= 1.5;
  }
  else if (lHR < 55)
  {
    LocalZone *= 1.5;
    StabilityZone *= 1.5;
    OtherStabilityZone *= 1.5;
    t60msec *= 1.5;
  }
  // lLowED - bottom limit for ED
/*
  int lLowED = math_TimeToIndex(lBottomED, pExpandFactor, pSampleRate);
  lLowED = max (lLowED, (int)(ED_MIN_PERCENT*Length));
*/
  int lLowED = (int)(ED_MIN_PERCENT*lLength); // ED Cannot be less 17% of Length

  // Begin point of signal beginning after avoiding a few points
  int Begin = max (math_Round(BEGIN_PERCENT*L), LocalZone); // 3% of Length

  // MainPeak - Absolute maximum of a signal
  MainPeak = IndexOfExtremum(MAX, GLOBAL, Begin, L);
  if (MainPeak < 0)
  {
    MsgBox(TERROR, GetCurrentPwaMeasureDetails(), MSG_MATH_ERROR, MSG_NOT_FOUND_PEAK);
    return true;
  }
  // Reject if wrong
  if (pED > 0 && pED != DEFAULT_VALUE && MainPeak >= pED)
  {
    MsgBox(TERROR, GetCurrentPwaMeasureDetails(), MSG_MATH_ERROR, MSG_WRONG_PERIPH_ED);
    return true;
  }

  // Manage case where Periph ED not found
  if (pED == DEFAULT_VALUE)
  {
      T1 = MainPeak;
      T2 = DEFAULT_VALUE;
      QualityT1 = STRONG;
      QualityT2 = VERYWEAK;
      OurCase = 9;
      return true;
  }

  // Find PeakOfDer1
  int lPeakBeforeMain = IndexOfExtremum(MAX, GLOBAL, StabilityZone, MainPeak - StabilityZone);
  int lLimitOfPeakOfDer1 = (lPeakBeforeMain > 0 ? lPeakBeforeMain - StabilityZone
                                                : MainPeak - StabilityZone);
  PeakOfDer1 = Der1->IndexOfExtremum(MAX, GLOBAL, StabilityZone, lLimitOfPeakOfDer1,
                     StabilityZone, MORE, 0., NULL);
  if (PeakOfDer1 < 0)
  {
    PeakOfDer1 = Der1->IndexOfExtremum(MAX, GLOBAL, StabilityZone, lLimitOfPeakOfDer1,
                       OtherStabilityZone, MORE, 0., NULL);
  }
  if (PeakOfDer1 < 0)
  {
    PeakOfDer1 = Der1->IndexOfExtremum(MAX, GLOBAL, StabilityZone, lLimitOfPeakOfDer1 + StabilityZone/2,
                       OtherStabilityZone, MORE, 0., NULL);
  }
  if (PeakOfDer1 < 0)
  {
    // Check Begin point
    if (Begin >= MainPeak - LocalZone)
      Begin = MainPeak - LocalZone -1;
    if (Begin <= Start)
      Begin = Start + 1;
  }
  else
  {
    Begin = PeakOfDer1;
  }

  // Largest peak index for periph and central
  int lCentralLatestPeak = (pCentralMainPeak > 0 ? pCentralMainPeak : -1);
/*
  if (pCentralMainPeak > 0)
  {
    lCentralLatestPeak = (pCentralSecondPeak > pCentralMainPeak ?
                          pCentralSecondPeak : pCentralMainPeak);
  }
*/
  int lLatestPeak = (lCentralLatestPeak > 0 ?
                     max(lCentralLatestPeak, MainPeak) : MainPeak);

  // lEDBegin - left window where ED can be located
  int lEDBegin = max (lLatestPeak + LocalZone, lLowED);

  // Find EndT2 - limit distance between peak and ED. In most cases it is almost ED
  float lTreas;
  int EDMin = -1;
  // int CentralPeakOfDer2 = -1;    // Peak of Der2 for Central signal
  int PeakOfDer2 = -1;           // Peak of Der2 for Periph signal

  // For Central case EndT2 = ED
  if (ED != DEFAULT_VALUE)
  {
    // End of Window for Central T1, T2 should be less 110% of T2 for periph
    EndT2 = (pLimitT1T2 > 0 ? pLimitT1T2 * LIMIT_T1T2_FACTOR : ED -  StabilityZone);
  }
  else // For Periph case we need estimate End
  {
    // Periph Pressure[ED] should be less than 75% of PulseHeight
    float PHProc = 1. - ESP_MAX_PERCENT;
    float fP0 = Profile[MainPeak];
    float PHt = fP0 - Profile[Start];
    lTreas = fP0 - PHProc*PHt;

    // Try to find sharp minimum as ED and PeakOfDer2 nearby
    int lLimitPeakOfDer2 = L;
    EDMin = IndexOfExtremum(MIN, GLOBAL, lEDBegin, L, StabilityZone,
                            LESS, lTreas, Der2->Profile,
                            CD1P, LESS, 0., StabilityZone,
                            CD2P, MORE, 0., StabilityZone);
    if (EDMin < 0)
    {
      EDMin = IndexOfExtremum(MIN, FIRST, lEDBegin, L, OtherStabilityZone,
                              LESS, lTreas, Der2->Profile,
                              CD1P, LESS, 0., OtherStabilityZone,
                              CD2P, MORE, 0., OtherStabilityZone);
    }
    if (EDMin < 0)
    {
      EDMin = IndexOfExtremum(MIN, FIRST, lEDBegin, L, OtherStabilityZone,
                              LESS, lTreas, Der2->Profile,
                              CD1P, LESS, 0., 0,
                              CD2P, MORE, 0.);
    }
    if (EDMin > 0)
    {
      PeakOfDer2 = Der2->IndexOfExtremum(MAX, GLOBAL, EDMin - 2*LocalZone, EDMin/* + 2*LocalZone*/,
                            StabilityZone, MORE, 0., NULL,
                            Profile, LESS, lTreas, 0,
                            Der1->Profile, LESS, 0., 0,
                            CD1P, LESS, 0., 0,
                            CD2P, MORE, 0., OtherStabilityZone);
      // Try to find Peak of CentralDer2 near the both EDMin and PeakOfDer2
      /*
      if (UseCorrespondence && PeakOfDer2 > 0)
      {
        int lWinMin = (PeakOfDer2 < EDMin ?
                       PeakOfDer2 - OtherStabilityZone :
                       EDMin - LocalZone);
        int lWinMax = max (PeakOfDer2, EDMin) + 2*LocalZone;
        CentralPeakOfDer2 = CentralDer2->IndexOfExtremum(MAX, FIRST,
                            lWinMin, lWinMax, StabilityZone, MORE, 1.);
      }
      */
      lLimitPeakOfDer2 = EDMin /* + 2*LocalZone*/;
    }

    // If sharp minimum not found, extract ED from Der2 where Central.Der2 is stably positive in OtherStabilityZone
    if (PeakOfDer2 < 0)
    {
      PeakOfDer2 = Der2->IndexOfExtremum(MAX, GLOBAL, lEDBegin, lLimitPeakOfDer2,
                   StabilityZone, MORE, 0., NULL,
                   Profile, LESS, lTreas, 0,
                   Der1->Profile, LESS, 0., 0,
                   CD1P, LESS, 0., 0,
                   CD2P, MORE, 0., OtherStabilityZone);
      // Check if there another good peak after
      if (PeakOfDer2 > 0)
      {
        int lPeakOfDer2 = Der2->IndexOfExtremum(MAX, GLOBAL, PeakOfDer2, lLimitPeakOfDer2,
                     StabilityZone, MORE, Der2->Profile[PeakOfDer2]*0.5, NULL,
                     Profile, LESS, lTreas, 0,
                     Der1->Profile, LESS, 0., 0,
                     CD1P, LESS, 0., 0,
                     CD2P, MORE, 0., OtherStabilityZone);
        if (lPeakOfDer2 > PeakOfDer2)
          PeakOfDer2 = lPeakOfDer2;
      }
    }
    // If not found, extract ED from Der2 where Central.Der2 is positive without accounting stability
    if (PeakOfDer2 < 0)
    {
      PeakOfDer2 = Der2->IndexOfExtremum(MAX, GLOBAL, lEDBegin, lLimitPeakOfDer2,
                   StabilityZone, MORE, 0., NULL,
                   Profile, LESS, lTreas, 0,
                   Der1->Profile, LESS, 0., 0,
                   CD1P, LESS, 0., 0,
                   CD2P, MORE, 0.);
    }
    // If not found, extract ED from Der2 without accounting Central.Der
    if (EDMin < 0 && PeakOfDer2 < 0)
    {
      PeakOfDer2 = Der2->IndexOfExtremum(MAX, GLOBAL, lEDBegin, lLimitPeakOfDer2,
                   StabilityZone, MORE, 0., NULL,
                   Profile, LESS, lTreas, 0,
                   Der1->Profile, LESS, 0., 0,
                   CD1P, LESS, 0., 0);
    }
    // If not found, extract ED from Der2 decreasing Stability Zone
    if (EDMin < 0 && PeakOfDer2 < 0)
    {
      PeakOfDer2 = Der2->IndexOfExtremum(MAX, FIRST, lEDBegin, lLimitPeakOfDer2,
                   OtherStabilityZone, MORE, 0., NULL,
                   Profile, LESS, lTreas, 0,
                   Der1->Profile, LESS, 0., 0,
                   CD1P, LESS, 0., 0);
    }
    // If not found, extract ED from Der2 decreasing Stability Zone one more
    if (EDMin < 0 && PeakOfDer2 < 0)
    {
      PeakOfDer2 = Der2->IndexOfExtremum(MAX, FIRST, lEDBegin, lLimitPeakOfDer2,
                   OtherStabilityZone/2, MORE, 0., NULL,
                   Profile, LESS, lTreas, 0,
                   Der1->Profile, LESS, 0., 0,
                   CD1P, LESS, 0., 0);
    }

    // Work out EndT2 - limit zone for T2
    EndT2 = max(EDMin, PeakOfDer2);

    // If EndT2 (ED Candidate) not found, set it as DefaultED
    // If ED found, Decrease EndT2 to prevent finding T2 very close to ED
    if (EndT2 > 0)
    {
      // EndT2 -= LocalZone;
      EndT2 -= StabilityZone;
    }
    else
    {
      EndT2 = (lDefaultED > lEDBegin ? lDefaultED : L);
    }
  }

  // Now try to find T1, T2 in window [Begin, EndT2]

  // Distinquish between different types of pulses
  OurCase = 0;
  while (true)
  {
    PeakBeforeMain = IndexOfExtremum(MAX, FIRST, Begin, MainPeak - LocalZone,
                                     OtherStabilityZone, MORE, 0., Der2->Profile);
    if (PeakBeforeMain > 0) // If found
    {
      T1 = PeakBeforeMain;
      T2 = MainPeak;
      OurCase = 1;
      QualityT1 = VERYSTRONG;
      QualityT2 = VERYSTRONG;
      break;
    }

    // Find first peak between main peak and EndT2
    //PeakAfterMain = IndexOfExtremum(MAX, FIRST, MainPeak + LocalZone, EndT2,
    //                                OtherStabilityZone, MORE, 0., Der2->Profile);
    PeakAfterMain = IndexOfExtremum(MAX, FIRST, MainPeak + t60msec, EndT2,
                                    OtherStabilityZone, MORE, 0., Der2->Profile);
    // PeakAfterMain = IndexOfExtremum(MAX, FIRST, MainPeak + LocalZone, EndT2,
    //                                StabilityZone, MORE, 0., Der2->Profile);
    if (PeakAfterMain > 0) // If found
    {
      T1 = MainPeak;
      T2 = PeakAfterMain;
      QualityT1 = VERYSTRONG;
      QualityT2 = VERYSTRONG;
      OurCase = 2;
      break;
    }

    // There are no strong peaks before and after main peak

    // If Periph and Central peak are reasonably distant,
    // try to find PseudoPeak before Main for Central as features
    // of Der2 or Der3 (which one is closer to MainPeak of peripheral)
/*
    // Specify windows if peaks of periph and central is reasonably distant
    if (pED > 0 && pPeriphMainPeak > 0 && MainPeak - pPeriphMainPeak > t60msec)
    {
      // int ShoulderBeforePeak2 = Der2->IndexOfExtremum(MAX, GLOBAL, max (pPeriphMainPeak - LocalZone, Begin),
      //                          pPeriphMainPeak + LocalZone, StabilityZone, LESS, 0);
      int ShoulderBeforePeak2 = -1; // Ignore Der2 features
      int ShoulderBeforePeak3 = Der3->IndexOfExtremum(MAX, GLOBAL, max (pPeriphMainPeak - LocalZone, Begin),
                                pPeriphMainPeak + LocalZone, StabilityZone, MORE, 0.);
      if (ShoulderBeforePeak2 > 0 && ShoulderBeforePeak3 < 0)
      {
        ShoulderBeforePeak = ShoulderBeforePeak2;
        T1 = ShoulderBeforePeak;
        T2 = MainPeak;
        QualityT1 = STRONG;
        QualityT2 = VERYSTRONG;
        OurCase = 21;
        break;
      }
      if (ShoulderBeforePeak2 < 0 && ShoulderBeforePeak3 > 0)
      {
        ShoulderBeforePeak = ShoulderBeforePeak3;
        T1 = ShoulderBeforePeak;
        T2 = MainPeak;
        QualityT1 = STRONG;
        QualityT2 = VERYSTRONG;
        OurCase = 31;
        break;
      }
      // Both exist. Which one is closer to the Periph Main peak?
      if (ShoulderBeforePeak2 > 0 && ShoulderBeforePeak3 > 0)
      {
        if (abs(pPeriphMainPeak - ShoulderBeforePeak2) >= abs(pPeriphMainPeak - ShoulderBeforePeak3))
        {
          ShoulderBeforePeak = ShoulderBeforePeak3;
          T1 = ShoulderBeforePeak;
          T2 = MainPeak;
          QualityT1 = STRONG;
          QualityT2 = VERYSTRONG;
          OurCase = 31;
          break;
        }
        else
        {
          ShoulderBeforePeak = ShoulderBeforePeak2;
          T1 = ShoulderBeforePeak;
          T2 = MainPeak;
          QualityT1 = STRONG;
          QualityT2 = VERYSTRONG;
          OurCase = 21;
          break;
        }
      }
    }
*/
    // There are no peaks before and after main peak
    // Try to find PseudoPeak before Main as features of Der2

    // Try to find weak shoulders analysing Der2, Der3
/*
    // Specify windows if peaks of periph and central is reasonably distant
    if (pED <= 0 && pCentralMainPeak - MainPeak > t60msec)
    {
      ShoulderAfterPeak = Der2->IndexOfExtremum(MIN, GLOBAL, pCentralMainPeak - LocalZone,
                          pCentralMainPeak + LocalZone, StabilityZone);
      if (ShoulderAfterPeak > 0)
      {
        T1 = MainPeak;
        QualityT1 = STRONG;
        T2m = Der3->IndexOfExtremum(MIN, GLOBAL, pCentralMainPeak - LocalZone, ShoulderAfterPeak,
                                    StabilityZone, LESS, DEFAULT_VALUE, NULL,
                                    Der1->Profile, LESS, 0, StabilityZone);
        if (T2m > 0)
        {
          T2 = T2m;
          QualityT2 = STRONG;
          OurCase = 32;
        }
        else
        {
          T2 = ShoulderAfterPeak;
          QualityT2 = WEAK;
          OurCase = 22;
        }
        break;
      }
    }

    // No correspondence between Periph and Central
*/
    // Betweem MainPeak and Peak2 function dropped. Try to get Weak Shoulders
    //ShoulderBeforePeak = Der3->IndexOfExtremum(MAX, GLOBAL, Begin, MainPeak - LocalZone,
    //                                           OtherStabilityZone, MORE, 0.);
    //ShoulderAfterPeak  = Der2->IndexOfExtremum(MIN, GLOBAL, MainPeak + LocalZone, EndT2,
    //                                           StabilityZone);

    ShoulderBeforePeak = Der3->IndexOfExtremum(MAX, GLOBAL, Begin, MainPeak - LocalZone,
                                               OtherStabilityZone, MORE, 0.);
    ShoulderAfterPeak  = Der2->IndexOfExtremum(MIN, GLOBAL, MainPeak + LocalZone, EndT2,
                                               StabilityZone);

    // Shoulder before peak found
    if ((ShoulderAfterPeak < 0) && (ShoulderBeforePeak > 0))
    {
      T1 = ShoulderBeforePeak;
      T2 = MainPeak;
      QualityT1 = STRONG;
      QualityT2 = STRONG;
      OurCase = 33;
      break;
    }
    // Check ShoulderAfterPeak found
    if ((ShoulderAfterPeak > 0) && (ShoulderBeforePeak < 0))
    {
      T1 = MainPeak;
      QualityT1 = STRONG;
      T2m = Der3->IndexOfExtremum(MIN, GLOBAL, MainPeak + LocalZone, ShoulderAfterPeak,
                                  StabilityZone, LESS, DEFAULT_VALUE, NULL,
                                  Der1->Profile, LESS, 0, StabilityZone);
      if (T2m > 0)
      {
        T2 = T2m;
        QualityT2 = STRONG;
        OurCase = 34;
      }
      else
      {
        T2 = ShoulderAfterPeak;
        QualityT2 = WEAK;
        OurCase = 24;
      }
      break;
    }
    // Both shoulders found
    if ((ShoulderBeforePeak > 0) && (ShoulderAfterPeak > 0))
    {
/*
      // Give priority to shoulder before peak
      T1 = ShoulderBeforePeak;
      T2 = MainPeak;
      QualityT1 = STRONG;
      QualityT2 = WEAK;
      OurCase = 35;
      break;
*/
// Nov 2 1999 for PWM
      // Both shoulders exist. Seems flat area here
      T2m = Der3->IndexOfExtremum(MIN, GLOBAL, MainPeak + OtherStabilityZone, ShoulderAfterPeak,
                                  OtherStabilityZone, LESS, DEFAULT_VALUE, NULL,
                                  Der1->Profile, LESS, 0, OtherStabilityZone);
      if (T2m < 0)
      {
        T1 = ShoulderBeforePeak;
        T2 = MainPeak;
        QualityT1 = STRONG;
        QualityT2 = WEAK;
        OurCase = 35;
        break;
      }

      // Shoulders as Der3 before and after peak exist
      // try to find shoulder length
      float P0 = fabs(Profile[Start]);
      float P1 = fabs(Value(ShoulderBeforePeak)) - P0;
      float P2 = fabs(Value(T2m)) - P0;
      float Pt = fabs(Value(MainPeak)) - P0;
      float L1 = sqrt(pow(P1-Pt,2) + pow(ShoulderBeforePeak-MainPeak,2));
      float L2 = sqrt(pow(P2-Pt,2) + pow(T2m - MainPeak,2));

      if (P1 >= Pt || P2 >= Pt || L1 <= 0 || L2 <= 0)
      {
        T1 = ShoulderBeforePeak;
        T2 = MainPeak;
        QualityT1 = VERYWEAK;
        QualityT2 = WEAK;
        OurCase = 35;
        break;
      }
      // Compare shoulders
      if (L1 >= L2)
      {
        T1 = ShoulderBeforePeak;
        T2 = MainPeak;
        QualityT1 = STRONG;
        QualityT2 = WEAK;
        OurCase = 35;
        break;
      }
      else
      {
        T1 = MainPeak;
        T2 = T2m;
        QualityT1 = WEAK;
        QualityT2 = STRONG;
        OurCase = 36;
        break;
      }

/*    // FLAT AREA Algorithm
      float L1 = MainPeak - ShoulderBeforePeak;
      float L2 = T2m - MainPeak;
      float L12 = T2m - ShoulderBeforePeak;
      if (P1 >= Pt || P2 >= Pt || L1 <= 0 || L2 <= 0 || L12 <= 0)
      {
        T1 = ShoulderBeforePeak;
        T2 = MainPeak;
        QualityT1 = VERYWEAK;
        QualityT2 = WEAK;
        OurCase = 35;
        break;
      }
      //Check whether shoulders on the same level
      if (P1 < FLAT_AREA_PERCENT*Pt || P2 < FLAT_AREA_PERCENT*Pt)
      {
        if (L1 >= L2)
        {
          T1 = ShoulderBeforePeak;
          T2 = MainPeak;
          QualityT1 = STRONG;
          QualityT2 = WEAK;
          OurCase = 35;
          break;
        }
        else
        {
          T1 = MainPeak;
          T2 = T2m;
          QualityT1 = WEAK;
          QualityT2 = STRONG;
          OurCase = 36;
          break;
        }
      }
      //Shoulders on the same level. Compare them
      if (L1 <= FLATNESS*L12)
      {
        T1 = MainPeak;
        T2 = T2m;
        QualityT1 = WEAK;
        QualityT2 = STRONG;
        OurCase = 62;
        break;
      }
      if (L2 <= FLATNESS*L12)
      {
        T1 = ShoulderBeforePeak;
        T2 = MainPeak;
        QualityT1 = STRONG;
        QualityT2 = WEAK;
        OurCase = 61;
        break;
      }
      // Flat area case
      T1 = ShoulderBeforePeak;
      T2 = T2m;
      QualityT1 = STRONG;
      QualityT2 = STRONG;
      OurCase = 60;
      break;
*/
    }
/*
    // Weak Shoulders still not found. Try Very weak Shoulders
    ShoulderBeforePeak = Der3->IndexOfExtremum(MAX, GLOBAL, Begin, MainPeak - LocalZone,
                                               OtherStabilityZone, MORE, 0.);
    ShoulderAfterPeak  = Der2->IndexOfExtremum(MIN, GLOBAL, MainPeak + LocalZone, EndT2,
                                               OtherStabilityZone);
    if ((ShoulderAfterPeak < 0) && (ShoulderBeforePeak > 0))
    {
      T1 = ShoulderBeforePeak;
      T2 = MainPeak;
      QualityT1 = WEAK;
      QualityT2 = STRONG;
      OurCase = 37;
      break;
    }
    if ((ShoulderAfterPeak > 0) && (ShoulderBeforePeak < 0))
    {
      T1 = MainPeak;
      QualityT1 = STRONG;
      T2m = Der3->IndexOfExtremum(MIN, GLOBAL, MainPeak + LocalZone, ShoulderAfterPeak,
                                  OtherStabilityZone, LESS, DEFAULT_VALUE, NULL,
                                  Der1->Profile, LESS, 0, OtherStabilityZone);
      if (T2m > 0)
      {
        T2 = T2m;
        QualityT2 = STRONG;
        OurCase = 36;
      }
      else
      {
        T2 = ShoulderAfterPeak;
        QualityT2 = WEAK;
        OurCase = 26;
      }
      break;
    }
    // Both shoulders found
    if ((ShoulderBeforePeak > 0) && (ShoulderAfterPeak > 0))
    {
      // Both shoulders exist. Seems flat area here
      T2m = Der3->IndexOfExtremum(MIN, GLOBAL, MainPeak + LocalZone, ShoulderAfterPeak,
                                  OtherStabilityZone, LESS, DEFAULT_VALUE, NULL,
                                  Der1->Profile, LESS, 0, OtherStabilityZone);
      if (T2m < 0)
      {
        T1 = ShoulderBeforePeak;
        T2 = MainPeak;
        QualityT1 = VERYWEAK;
        QualityT2 = WEAK;
        OurCase = 39;
        break;
      }
      // Shoulders as Der3 before and after peak exist
      // try to find shoulder length
      float P0 = fabs(Profile[Start]);
      float P1 = fabs(Value(ShoulderBeforePeak)) - P0;
      float P2 = fabs(Value(T2m)) - P0;
      float Pt = fabs(Value(MainPeak)) - P0;
      if (P1 >= Pt || P2 >= Pt)
      {
        T1 = ShoulderBeforePeak;
        T2 = MainPeak;
        QualityT1 = VERYWEAK;
        QualityT2 = WEAK;
        OurCase = 39;
        break;
      }
      if (P1 < FLAT_AREA_PERCENT*Pt || P2 < FLAT_AREA_PERCENT*Pt)
      {
        T1 = ShoulderBeforePeak;
        T2 = MainPeak;
        QualityT1 = VERYWEAK;
        QualityT2 = WEAK;
        OurCase = 39;
        break;
      }
      T1 = ShoulderBeforePeak;
      T2 = T2m;
      QualityT1 = STRONG;
      QualityT2 = STRONG;
      OurCase = 62;
      break;
    }
*/

    // Try to find PseudoPeaks as a features of Der1
/*
    // Specify windows if peaks of periph and central is reasonably distant
    if (pED <= 0 && pCentralMainPeak - MainPeak > t60msec)
    {
//      ShoulderAfterPeak = Der1->IndexOfExtremum(MAX, GLOBAL,
//                          pCentralMainPeak - LocalZone, pCentralMainPeak + LocalZone,
//                          StabilityZone, LESS, 0., Der3->Profile);
      ShoulderAfterPeak = Der1->IndexOfExtremum(MAX, GLOBAL,
                          pCentralMainPeak - LocalZone, pCentralMainPeak + LocalZone,
                          LocalZone, LESS, 0., Der3->Profile);
      if (ShoulderAfterPeak > 0)
      {
        T1 = MainPeak;
        T2 = ShoulderAfterPeak;
        QualityT1 = VERYSTRONG;
        QualityT2 = WEAK; //VERYSTRONG;
        OurCase = 12;
        break;
      }
    }
    else if (pED > 0 && pPeriphMainPeak > 0 && MainPeak - pPeriphMainPeak > t60msec)
    {
//      ShoulderBeforePeak = Der1->IndexOfExtremum(MIN, GLOBAL,
//                           max (pPeriphMainPeak - LocalZone, Begin), pPeriphMainPeak + LocalZone,
//                           StabilityZone, MORE, 0, Der3->Profile);
      ShoulderBeforePeak = Der1->IndexOfExtremum(MIN, GLOBAL,
                           max (pPeriphMainPeak - LocalZone, Begin), pPeriphMainPeak + LocalZone,
                           LocalZone, MORE, 0, Der3->Profile);
      if (ShoulderBeforePeak > 0)
      {
        T1 = ShoulderBeforePeak;
        T2 = MainPeak;
        QualityT1 =  WEAK; //VERYSTRONG;
        QualityT2 = VERYSTRONG;
        OurCase = 11;
        break;
      }
    }

    // No correspondence between peaks in Periph and Central
//    ShoulderBeforePeak = Der1->IndexOfExtremum(MIN, GLOBAL, Begin, MainPeak - LocalZone,
//                         StabilityZone, MORE, 0, Der3->Profile);
//    ShoulderAfterPeak  = Der1->IndexOfExtremum(MAX, GLOBAL, MainPeak + LocalZone, EndT2 - StabilityZone,
//                         StabilityZone, LESS, 0., Der3->Profile);
    ShoulderBeforePeak = Der1->IndexOfExtremum(MIN, GLOBAL, Begin, MainPeak - LocalZone,
                         LocalZone, MORE, 0, Der3->Profile);
    ShoulderAfterPeak  = Der1->IndexOfExtremum(MAX, GLOBAL, MainPeak + LocalZone, EndT2 - StabilityZone,
                         LocalZone, LESS, 0., Der3->Profile);
    // Different cases
    // Shoulder 1 exist, Shoulder 2 not exist
    if (ShoulderBeforePeak > 0 && ShoulderAfterPeak < 0)
    {
      T1 = ShoulderBeforePeak;
      T2 = MainPeak;
      QualityT1 =  WEAK; //STRONG;
      QualityT2 = VERYSTRONG;
      OurCase = 13;
      break;
    }

    // Shoulder 1 not exist, Shoulder 2 exist
    if (ShoulderBeforePeak < 0 && ShoulderAfterPeak > 0)
    {
      T1 = MainPeak;
      T2 = ShoulderAfterPeak;
      QualityT1 = VERYSTRONG;
      QualityT2 =  WEAK; // STRONG;
      OurCase = 14;
      break;
    }

    // Shoulder 1 exist, Shoulder 2 exist
    if (ShoulderBeforePeak > 0 && ShoulderAfterPeak > 0)
    {
      // Compare values in shoulders : Which is close to 0?
      float P1 = fabs(Der1->Value(ShoulderBeforePeak));
      float P2 = fabs(Der1->Value(ShoulderAfterPeak));
      if (P1 > P2)
      {
        T1 = MainPeak;
        T2 = ShoulderAfterPeak;
        QualityT1 = STRONG;
        QualityT2 = WEAK;
        OurCase = 16;
        break;
      }
      else
      {
        T1 = ShoulderBeforePeak;
        T2 = MainPeak;
        QualityT1 = WEAK;
        QualityT2 = STRONG;
        OurCase = 15;
        break;
      }
    }

    // There is no peaks before and after main peak and no features in Waveform and Der1.
*/
    // No shoulders found.
    // Last chance to get very weak T1 as a negative max of der3
    // (usualy for very slow HR
    ShoulderBeforePeak = Der3->IndexOfExtremum(MAX, GLOBAL, Begin, MainPeak - LocalZone,
                                               OtherStabilityZone);
    if (ShoulderBeforePeak > 0)
    {
      T1 = ShoulderBeforePeak;
      T2 = MainPeak;
      QualityT1 = VERYWEAK;
      QualityT2 = STRONG;
      OurCase = 39;
      break;
    }

    {
      T1 = MainPeak;
      T2 = DEFAULT_VALUE;
      QualityT1 = STRONG;
      QualityT2 = WEAK;
      OurCase = 50;
      break;
    }
  }

  // Now T1, T2 found (if T2 exist)

  // Calculate ED for Peripheral
  if (pED < 0 || pED == DEFAULT_VALUE)
  {
    // lBegin - left ED window after T2
    int lBegin = (T2 > 0 && T2!=DEFAULT_VALUE ?
                  max (T2 + StabilityZone,lEDBegin) :
                  max (T1 + LocalZone,lEDBegin));
    // Increase EndT2 to catch sharp min
    if (EndT2 > 0)
//      EndT2 += 2*LocalZone; // Shift right EndT2 to catch srtong EndT2
      EndT2 += 2*StabilityZone; // Shift right EndT2 to catch srtong EndT2
    int lEndOfDer2 = (EDMin > 0 ? EDMin : EndT2);
    // Trying to find ED
    while (true)
    {
/*
      // If both EDMin and PeakOfDer2 exist, select which one is close to CentralPeakOfDer2
      if (CentralPeakOfDer2 > lBegin && PeakOfDer2 > lBegin && EDMin > lBegin)
      {
        ED = (abs(CentralPeakOfDer2 - PeakOfDer2) > abs(CentralPeakOfDer2 - EDMin) ?
              EDMin : PeakOfDer2);
        QualityED = VERYSTRONG;
        break;
      }
*/
/*
      // If T2 not found and Sharp min exist, take is as ED.
      if (EDMin > 0)
      {
        ED = EDMin;
        QualityED = STRONG;
        break;
      }
*/
      // Find ED as a feature of Der2 with accounting Central.Der2 > 0 in OtherStabilityZone
      ED = Der2->IndexOfExtremum(MAX, GLOBAL, lBegin, lEndOfDer2,
                                 StabilityZone, MORE, 0., NULL,
                                 // Profile, LESS, lTreas, 0,
                                 Der1->Profile, LESS, 0., 0,
                                 CD1P, LESS, 0., 0,
                                 CD2P, MORE, 0., OtherStabilityZone);
/*
      // Check whether ED close to sharp min
      if (EDMin > 0 && ED > 0 && EDMin - ED <= StabilityZone)
      {
        ED = EDMin;
      }
*/
/*
      // Young cases
      if (OurCase == 50 && ED > 0 && EDMin - ED > LocalZone)
      {
        // try to find very week T2 as a neg max of der3 (almost T2)
        int lVeryWeakShoulder = Der3->IndexOfExtremum(MAX, FIRST, ED, EDMin,
                                      OtherStabilityZone, LESS, 0., NULL,
                                      Der2->Profile, MORE, 0., OtherStabilityZone,
                                      Der1->Profile, LESS, 0., OtherStabilityZone);
        if (lVeryWeakShoulder > 0)
        {
          ED = EDMin;
          QualityED = WEAK;
          break;
        }
      }
*/

      if (ED > 0)
      {
         QualityED = VERYSTRONG;
         break;
      }

      ED = Der2->IndexOfExtremum(MAX, GLOBAL, lBegin, lEndOfDer2,
                                 StabilityZone, MORE, 0., NULL,
                                 // Profile, LESS, lTreas, 0,
                                 Der1->Profile, LESS, 0., 0,
                                 CD1P, LESS, 0., 0,
                                 CD2P, MORE, 0., 0);
      if (ED > 0)
      {
         QualityED = STRONG;
         break;
      }
      // If not found, do not account Central Der2
      if (EDMin < 0 && T2 != DEFAULT_VALUE)
      {
        ED = Der2->IndexOfExtremum(MAX, GLOBAL, lBegin, lEndOfDer2,
                                   StabilityZone, MORE, 0., NULL,
                                   // Profile, LESS, lTreas, 0,
                                   Der1->Profile, LESS, 0., 0,
                                   CD1P, LESS, 0., 0);
      }
      if (ED > 0)
      {
         QualityED = STRONG;
         break;
      }

      // If not found, decrease stability zone
      if (EDMin < 0 && T2 != DEFAULT_VALUE)
      {
         ED = Der2->IndexOfExtremum(MAX, FIRST, lBegin, lEndOfDer2,
                                   OtherStabilityZone, MORE, 0., NULL,
                                   // Profile, LESS, lTreas, 0,
                                   Der1->Profile, LESS, 0., 0,
                                   CD1P, LESS, 0., 0);
      }
      if (ED > 0)
      {
        QualityED = STRONG;
        break;
      }
      if (EDMin > 0 && T2 != DEFAULT_VALUE)
      {
         ED = Der2->IndexOfExtremum(MAX, FIRST, lBegin, lEndOfDer2,
                                   OtherStabilityZone, MORE, 0., NULL,
                                   // Profile, LESS, lTreas, 0,
                                   Der1->Profile, LESS, 0., 0,
                                   CD1P, LESS, 0., 0);
      }
      if (ED > 0)
      {
        QualityED = WEAK;
        break;
      }
      // If not found, but sharp min exist, take it as ED
      if (EDMin > 0 && float(EDMin)/lLength > 0.20 && float(EDMin)/lLength < 0.50)
      {
        ED = EDMin;
        QualityED = WEAK;
        break;
      }
      // If not found, avoid stability zone
      ED = Der2->IndexOfExtremum(MAX, FIRST, lBegin, lEndOfDer2,
            0, MORE, 0., NULL,
            // Profile, LESS, lTreas, 0,
            Der1->Profile, LESS, 0., 0,
            CD1P, LESS, 0., 0);
      if (ED > 0)
      {
        QualityED = WEAK;
        break;
      }

      // Increase window where ED can be up to L

      // Try to find Weak ED after increasing EndT2
      ED = Der2->IndexOfExtremum(MAX, GLOBAL, lBegin, L,
                                 StabilityZone, MORE, 0., NULL,
                                 // Profile, LESS, lTreas, 0,
                                 Der1->Profile, LESS, 0., 0,
                                 CD1P, LESS, 0., 0,
                                 CD2P, MORE, 0., OtherStabilityZone);
      if (ED > 0)
      {
         QualityED = WEAK;
         break;
      }
      // If not found, do not account Central Der2
      ED = Der2->IndexOfExtremum(MAX, GLOBAL, lBegin, L,
                                 StabilityZone, MORE, 0., NULL,
                                 // Profile, LESS, lTreas, 0,
                                 Der1->Profile, LESS, 0., 0,
                                 CD1P, LESS, 0., 0);
      if (ED > 0)
      {
         QualityED = WEAK;
         break;
      }
      // If not found, try to find sharp minimum with accounting Central Der2
      ED = IndexOfExtremum(MIN, GLOBAL, lBegin, L,
                           StabilityZone, LESS, lTreas, Der2->Profile,
                           // Profile, LESS, lTreas, 0,
                           Der1->Profile, LESS, 0., 0,
                           CD1P, LESS, 0., 0,
                           CD2P, MORE, 0.);
      if (ED > 0)
      {
         QualityED = WEAK;
         break;
      }

      // If not found, try to find sharp minimum without accounting Central Der
      ED = IndexOfExtremum(MIN, FIRST, lBegin, L, StabilityZone);
      if (ED > 0)
      {
        QualityED = VERYWEAK;
        break;
      }
      // If not found, avoid stability zone
      ED = Der2->IndexOfExtremum(MAX, FIRST, lBegin, L, 0, MORE, 0.);
      if (ED > 0)
      {
        QualityED = VERYWEAK;
        break;
      }

      // If still not found, try to find Weak ED after increasing window up to 65% of pulse length
      int lEnd = min ((int)(lLength*ED_MAX_PERCENT),
                       math_TimeToIndex(lEdMax, pExpandFactor, pSampleRate));
      ED = Der2->IndexOfExtremum(MAX, GLOBAL, lBegin, lEnd,
           StabilityZone, MORE, 0., NULL,
           // Profile, LESS, lTreas, 0,
           Der1->Profile, LESS, 0., 0,
           CD1P, LESS, 0., 0,
           CD2P, MORE, 0., OtherStabilityZone);
      if (ED > 0)
      {
         QualityED = WEAK;
         break;
      }
      ED = Der2->IndexOfExtremum(MAX, GLOBAL, lBegin, lEnd,
                                 StabilityZone, MORE, 0., NULL,
                                 // Profile, LESS, lTreas, 0,
                                 Der1->Profile, LESS, 0., 0,
                                 CD1P, LESS, 0., 0);
      if (ED > 0)
      {
         QualityED = WEAK;
         break;
      }
      ED = IndexOfExtremum(MIN, GLOBAL, lBegin, lEnd,
                           StabilityZone, LESS, lTreas, Der2->Profile,
                           CD1P, LESS, 0., 0,
                           CD2P, MORE, 0.);
      if (ED > 0)
      {
         QualityED = WEAK;
         break;
      }
      ED = IndexOfExtremum(MIN, FIRST, lBegin, lEnd,
                           StabilityZone, MORE, 0.);
      if (ED > 0)
      {
        QualityED = VERYWEAK;
        break;
      }
      ED = Der2->IndexOfExtremum(MAX, FIRST, lBegin, lEnd,
                                 0, MORE, 0.);
      if (ED > 0)
      {
        QualityED = VERYWEAK;
        break;
      }
      break;
    }
  }
  // Calculate Time of reflected wave Tr between T1 and ED
  // (only for Central wave)
  else
  {
    if (ED > 0 && ED != DEFAULT_VALUE && T1 > 0)
    {
      Tr = Der2->IndexOfExtremum(MAX, GLOBAL, T1, ED - StabilityZone, StabilityZone);
    }
  }

  // Now T1, T2, ED should be found
  // Extra validation
  if (ED < 0)
  {
    ED = DEFAULT_VALUE;
    QualityED = DEFAULT_VALUE;
  }
  // T1, T2
  if (T1 < 0)
  { // Stupid case
    T1 = MainPeak;
    T2 = DEFAULT_VALUE;
    QualityT1 = WEAK;
    QualityT2 = DEFAULT_VALUE;
    OurCase = -1;
  }
  else if (T2 < T1)
  {
    T2 = DEFAULT_VALUE;
    QualityT2 = DEFAULT_VALUE;
    OurCase = -1;
  }
  else if (ED > 0 && (T2 > 0 && T2 != DEFAULT_VALUE) && ED < T2)
  {
    ED = DEFAULT_VALUE;
    QualityED = DEFAULT_VALUE;
    OurCase = -1;
  }

  // return
  return true;
}

