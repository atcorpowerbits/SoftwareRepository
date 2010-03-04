#ifndef RTOF_PUBTYPE
#define RTOF_PUBTYPE

typedef struct
{
   short int	upper_guidance_band;
	short int	lower_guidance_band;
   TColor		pulse_height_color;
	TColor		pulse_height_variation_color;
	TColor		baseline_variation_color;
	String		pulse_height_label;
	String		pulse_height_variation_label;
	String		baseline_variation_label;
	TColor		waveform_color;
	bool		   capture;
}RTOF_RECORD_TYPE;

const int RTOF_MINIMUM_UPSTROKE_POINTS = 8;
const int RTOF_MINIMUM_DELAY_POINTS = 20;

#endif
 