//---------------------------------------------------------------------------
#ifndef HRVfrequencyH
#define HRVfrequencyH
#include "hrvclass.h"

typedef enum
{
   SpecRectangle,
   SpecTriangular,
   SpecCosine2,
   SpecGaussian,
   SpecHamming,
   SpecBlackman,
} HRV_FREQUENCY_SECTRUM_WINDOW_TYPE;



class THRVFrequency
{
 public:
   THRV                                 *hrv;
   float                                *RtoR_sampled;
   float                                *Time_sampled;
   float                                Power_Spectrum[HRV_FREQ_DEFAULT_SPECTRUM_SIZE];
   float                                Frequency[HRV_FREQ_DEFAULT_SPECTRUM_SIZE];
   int                                  number_of_points_sampled;
   int                                  number_of_points_spectrum;
   HRV_FREQUENCY_SECTRUM_WINDOW_TYPE    Active_Window;

   float                      LF_Power;
   float                      LF_Power_normlised;
   float                      HF_Power;
   float                      HF_Power_normlised;
   float                      LF_HF_Ratio;
   float                      LF_Freq_max;
   float                      HF_Freq_max;
   float                      Spectrum_Max;
   float                      TotalPower;

   THRVFrequency();
   ~THRVFrequency();
   void  Initialise();
   void  SetDefault();
   bool  Resample();
   bool  Calculate();
   bool  ValidateBeforeStore();
   bool  Store(TDataSet* pDataSet);
   bool  Populate(TDataSet* pDataSet);
   bool  ExportPrintTitle(TDataSet* pDataSet, String &pOut);
   bool  Export(String &pOut);

 private:

   bool PowerSpectrum();
   bool CalculateFreqParam();

 };
#endif

 
