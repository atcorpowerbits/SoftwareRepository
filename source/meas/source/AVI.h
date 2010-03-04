//---------------------------------------------------------------------------

#ifndef AVIH
#define AVIH

#include "pressure.h"
#include <fftw3.h>
//---------------------------------------------------------------------------
class TAVI
{
  public:
    float         *Flow;
    float         MaxDpDt;
    float         Forward_Max;
    int           T1_index;
    int           ED_index;
    int           MaxDpDt_index;
    int           Forward_index;
    int           Forward_Max_index;
    int           SpectrumLength;
    //int           SmoothOrder;
    float         *Pressure_Spectrum;
    float         *Flow_Spectrum;
    float         *Frequency;
    float         *Pressure_Harmonics;
    float         *Flow_Harmonics;
    float         *Forward_Pressure;
    float         *Backward_Pressure;
    float         *Forward_Pressure_Refined;
    float         *Backward_Pressure_Refined;
    float         *Forward_Pressure_Final;
    float         *Backward_Pressure_Final;
    float         *Cross_Correlation;
    float         Impedance;
    float         Forward_Vector_Max;
    float         Forward_Vector_Min;
    float         Backward_Vector_Max;
    float         Backward_Vector_Min;
    float         Forward_Pressure_Max;
    float         Forward_Pressure_Max_Time;
    float         Forward_Pressure_Max_Time_Index;
    float         Forward_Pressure_Height;
    float         Backward_Pressure_Max;
    float         Backward_Pressure_Max_Time;
    float         Backward_Pressure_Max_Time_Index;
    float         Backward_Pressure_Height;
    int           Reflection_Index;
    float         Aortic_Reflection_Lag;
    float         Aortic_Reflection_Time;
    float         Carotid_Femoral_Transmission_Time;
    float         Aortic_Distance;
    float         SphygmoCor_Velocity_Index;
    fftwf_complex *Pressure_Output;
    fftwf_complex *Flow_Output;
    fftwf_plan    Pressure_Plan;
    fftwf_plan    Flow_Plan;

    TPressureCentral *AVICentral;  // Central pressure results
    
    // Constructor and Destructor
    TAVI();
    ~TAVI();

    void Initialise();
    void SetDefaults();
    bool ValidateBeforeCalculate();
    bool Calculate(TPressureCentral *Central);
    bool ValidateBeforeStore();
    bool Store(TDataSet* pDataSet, TPressureCentral *Central);
    bool Populate(TDataSet* pDataSet, TPressureCentral *Central);

    // Export (print) measurement to string
    bool ExportPrintTitle(TDataSet* pDataSet, String &pOut);
    bool Export(String &pOut);
    bool ExportArrays(int pFileHandle);

    bool Recalculate();
    void CalculateFlow(float T1);
    bool FourierTransform();
    float Magnitude(float real, float imaginary);
    bool Harmonics();
    void CalculateImpedance();
    void CalculatePressureWaves();
    void RecalculateFlow();
    void CrossCorrelation();
  private:
};
#endif
 