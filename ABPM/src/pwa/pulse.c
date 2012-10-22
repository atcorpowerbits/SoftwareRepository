/*
 * pulse.c
 *
 * Created: 17/10/2012 2:03:33 PM
 *  Author: yoonl
 */ 

#include "pulse.h"
#include "pressure.h"
#include "math_pwa.h"

/* ###########################################################################
 ** Smooth()
 **
 ** DESCRIPTION
 **  Smooth pulse profile using running average algorithm
 ** INPUT
 **  pNofFilterPoints - Number of Filter points (usually 5, must be odd)
 ** OUTPUT
 **  smoothed profile
 ** RETURN
 **  true if success, false otherwise
*/
bool Smooth(float *pProfile, const int16_t pSize)
{
	return Math_SmoothArray(pProfile, pSize);
}