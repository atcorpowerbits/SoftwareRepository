/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
      Copyright (C) PWV MEDICAL PTY LTD, 1998

	  Filename 	  	:  PWM.H
      Author        :
      Revision      :  1.00
      Date          :  25 Aug 98

  	  Description 	:	DECLARATION of TPWM Measurement Class
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
//---------------------------------------------------------------------------
#ifndef PWMH
#define PWMH

#include <comms/pubtype.h>
#include "TStack.h"
#include <Series.hpp>
#include <ADOdb.hpp>

//---------------------------------------------------------------------------
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// TPWM (tonometry) measurement Class
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
class TPWM : public TPWA
{
  public:

    int       Session_ID;
    TDateTime SessionStart;
    TDateTime SessionFinished;
    String    SessionNotes;
    String    SessionMedication;

    int DeviceID;
    String DeviceName;
    bool Calibrated;
    bool Continuous;
    float CalibrationRatio;
    float CalibrationOffset;

    int   TrendSamplePeriod;
    int   TrendRefreshPeriod;
    int   ReportGenerationPeriod;
    bool  AorticSendOut;
    bool  PeriphSendOut;
    bool  AIxSendOut;
    float EventMarker;
    TStringList    *event_comment;
    float          *periph_buffer;
    int            periph_buff_len;
    COMMS_ID_TYPE  outputPort;

    // Constructors, destructors
    TPWM();
    ~TPWM();

    // Member functions:

    // Initialise properties
    void Initialise();

    // Set Defaults
    void SetDefaults();
    
    // Populate class properties from current record in pDataSet
    bool Populate(TDataSet* pDataSet);

    // Store class properties to current record in pDataSet
    bool Store(TDataSet* pDataSet, bool pRewriteKeyFields = true, bool pRewriteDate = true);

    // Store radial signal packet from tonometer in RadialBuffer
    bool StoreSignalPacket(const short int *pInput, const int pLength);

    // Calculate aortic value for Radial buffer and return
    float GetAorticValue();

    // Calculate report for this moment of monitoring
    bool Calculate(bool append, bool singlePulse = false);

    // Prepare to store monitored parameters to file with automatic closing
    bool PrepareToStoreParamsToFile(const String pFileName,
                                    const int pLimitNofStrings = 10,
                                    TStrings *pParamList = NULL);
    // Store monitored parameters to file with automatic closing
    int StoreParamsToFile(String &ErrorString);
    void CloseParamsFile();

    // Populate class properties from current record in Session table
    bool PopulateSession(TDataSet* pDataSet);
    // Create new record in PWMSession table
    bool CreateNewSession(TADOTable *pSessionTable);
    bool CloseSession(TADOTable *pSessionTable);
    bool DeleteSession(TADOTable *pSessionTable, bool pOnlyIncomplete=true);

    // Create PWMTrend Table from PWMTrend file
    int TrendFileToDB(const String pTrendFile, TADOTable *pTrendTable);

    // Create Trend Series for specific parameter
    bool CreateTrendSeries(TDataSet *pTrendTable, TChartSeries *pSeries);

    // Get Calibration Factor from Device table
    bool FindCalibrationFactor(TADOTable *pDeviceTable);

    // Get index of parameter in params map
    int GetParamIndex(const String pParamName);

    // Export trend param to string
    bool ExportParam(TDataSet *pTrendTable, String &pOut);

    // Store the event comment string list to database
    bool UpdateEventComments(TDataSet *dataset_session);

    // Get the stored session time
    int GetMarkerIndicator(AnsiString marker_string);

    // Get the stored event comment
    AnsiString GetMarkerString(AnsiString marker_string);

    // Validate Height and Weight
    bool ValidateHtWt();

  private:
    TAtCorStack<float> *RadialBuffer;
    bool ReadyToCapture; // Is ready to capture signal
    // Convert RadialBuffer Signal To Central using convolution
    float Convolution1(const float *pTfc);

    String FParamsFileName;
    int FFileHandle;
    int FNofStrings;
    int FAllStoredStrings;
    int FLimitNofStrings;
    TStringList *FParamList;

    // Variables for MedWave device
    TAtCorStack<short int> *OldValues;
    bool WeAreInPeak;
    bool Beginning;

    // Create map of parameters to be stored to file
    void CreateParamsMap();

    // Set ReadyToStore property to true
    void PrepareToCapture();

    // Storing packet with extracting pulse for MedWave device
    bool StoreSignalPacket(const short int *pInput, const int pLength, bool &ReadyToCalculate);
};
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#endif
