//---------------------------------------------------------------------------
#ifndef GetSeriesH
#define GetSeriesH
//---------------------------------------------------------------------------
#include "Pulse.h"
#include <Series.hpp>
//---------------------------------------------------------------------------
bool meas_GetSeriesForPulse(const int np, Pulse *pPulses, TLineSeries *pSeries,
                            const TColor pColor, const bool pWithTail = false);
#endif
