//* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
/*
    Copyright (C) PWV MEDICAL PTY LTD, 1998

    Filename 	  	:  Measure.H
    Author       :  Sergei Eremenko
    Revision     :  1.00
    Date         :  25 Aug 98

    Description 	:	DECLARATION of TMeasure Abstract Base Class
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
//---------------------------------------------------------------------------
#ifndef MeasureH
#define MeasureH
#include <vcl\db.hpp>
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Abstract Base Class for Measurement
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
class TMeasure
{
  private:

  public:
    String         DateFormat;
    String         DateTimeFormat;

    bool           MSAccess;    // true if DB is MSAccess
    short int      SecInc;

    String         System_ID;   // system id
    unsigned long  Patient_No;  // patient number
    String         Study_ID;

    float          Sp;          // systolic pressure entered by the operator
    float          Dp;          // diastolic pressure entered by the operator
    float          MeanP;       // Mean pressure entered by operator

    TDateTime      DateTime;    // date and time of measurement
    int            Secs;        // Seconds in measure time (in Spare1)
    int            DataRev;     // data revision number

    String         Medication;  // notes regarding medication for this patient
    String         Notes;       // miscellaneous notes for this measurement
    String    	    Operator;    // Operator Id
    String         Interpretation;  // notes regarding clinical interpretation for this patient

    float          Height;      // patient height in cm
    float          Weight;      // patient weight in kg
    float          Bmi;         // body mass index
    String         Spare1;      // spare field no.1 (not used - all blanks)

    float          Feet;        // patient height in ft
    float          Inch;        // patient height in in
    float          Pound;       // patient weight in lb

    int            SampleRate;    // Rate of measurement in Htz.
    
    bool           ValidateSpDp; // Whether to validate Sp, Dp, Mp

    int            Simulation; // Indicates a Simulated report

  protected:

    int            DefSampleRate; // Default sample rate
    // bool           ValidateSpDp; // Whether to validate Sp, Dp, Mp

    // Constructors, destructors
    TMeasure();
    void Initialise();
    // Member functions:
    void SetSampleRate(int pSampleRate);
    // populate TMeasure class properties from current record in pDataSet
    bool PopulateDBase(TDataSet* pDataSet);
    bool PopulateAccess(TDataSet* pDataSet);
    // Validate pressure
    bool ValidateSpDpMp();
     // Validate height and weight
    bool ValidateHtWt();
    // Validate measure class properties before storing in database
    bool ValidateBeforeStore();
    // Store class properties to current record in pDataSet
    bool StoreDBase(TDataSet* pDataSet, bool pRewriteKeyFields = true, bool pRewriteDate = true);
    bool StoreAccess(TDataSet* pDataSet, bool pRewriteKeyFields = true, bool pRewriteDate = true);

    // Export (print) measurement to string
    bool Export(String &pOut, const int pSessionID = 0);
    bool ExportPrintTitle(TDataSet* pDataSet, String &pOut);
};
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#endif
