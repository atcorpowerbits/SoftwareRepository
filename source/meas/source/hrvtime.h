//---------------------------------------------------------------------------

#ifndef hrvtimeH
#define hrvtimeH

#include "hrvclass.h"
#define MAX_RTOR_INTERVAL       2000
#define MIN_RTOR_INTERVAL       300
#define MAX_HISTOGRAM_LENGTH    MAX_RTOR_INTERVAL/10

//---------------------------------------------------------------------------

class THRVTime
{
   public:
      THRV      *hrv;

      float     RtoR_differences[HRV_MAX_NUMBER_OF_PULSES];
      short int RtoR_histogram[MAX_HISTOGRAM_LENGTH];

      float     RtoR_mean;
      float     RtoR_max;
      float     RtoR_min;
      float     RtoR_max_min;
      float     RtoR_range;
      float     RtoR_SD;
      int       NN50;
      float     PNN50;
      float     RMS_SD;
      int       RtoR_mode;
      int       RtoR_mode_frequency;
      float     HRV_index;
      int       rounded_RtoR_max;
      int       rounded_RtoR_min;
      int       Triangular_index;
      int       Segment_length;
      int       No_of_segments;
      float     SDANN;
      float     SDNN;
      float     Valsalva_high;
      float     Valsalva_low;
      float     Valsalva_ratio;
      float     Stand_high;
      float     Stand_low;
      float     Stand_ratio;

      THRVTime();
      ~THRVTime();
      void      Initialise();
      void      SetDefaults();
      bool      Calculate();
      bool      FindIntervals();
      bool      CreateHistogram();
      bool      CreateSegments();
      bool      CalculateStandManoeuvre();
      bool      ValidateBeforeStore();
      bool      Store(TDataSet* pDataSet);
      bool      Populate(TDataSet* pDataSet);
      bool      ExportPrintTitle(TDataSet* pDataSet, String &pOut);
      bool      Export(String &pOut);

   private:
      float     segment[HRV_MAX_NUMBER_OF_PULSES];
      float     sdann[HRV_MAX_NUMBER_OF_PULSES];
      float     length;
      int       segment_time;
};

#endif

