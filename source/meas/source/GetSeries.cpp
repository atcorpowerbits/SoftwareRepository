//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
//#include <meas\source\PWA.h>
#include <meas\pubserv.h>
//---------------------------------------------------------------------------
#pragma package(smart_init)

/* ###########################################################################
 ** meas_GetSeriesForPulse (...)
 **
 ** DESCRIPTION
 **  Populate TChart series for a pulse from array of pulses pPulses
 **  with shifting up Pulses to the level of first pulse
 ** INPUT
 **  pSeries - TChart linear series
 **  pColor - Color of a series
 **  np - pulse number
 ** OUTPUT
 **  boolean success or not
*/
bool meas_GetSeriesForPulse(const int np, TPulse *pPulses, TLineSeries *pSeries,
                            const TColor pColor, const bool pWithTail)
{
  // Pulse validation
  if (np < 0)
    return false;
  if ((pPulses[np].Profile == NULL) || (pPulses[np].Length() < 1))
    return false;
  if (pWithTail == false)
  {
    float lUpStep = pPulses[np].Profile[0] - pPulses[0].Profile[0];
    for (int k = 0; k < pPulses[np].Length(); k++)
    {
      pSeries->AddXY(k, pPulses[np].Profile[k + pPulses[np].Start] - lUpStep, "", pColor);
    }
  }
  else // include tails
  {
    float lUpStep = pPulses[np].Profile[pPulses[np].Start]
                  - pPulses[0].Profile[pPulses[0].Start];
    for (int k = 0; k < pPulses[np].Size(); k++)
    {
      pSeries->AddXY(k, pPulses[np].Profile[k] - lUpStep, "", pColor);
    }
  }
  return true;
}
