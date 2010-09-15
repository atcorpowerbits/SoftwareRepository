#ifndef MEAS_PUBSERV
#define MEAS_PUBSERV
//---------------------------------------------------------------------------
#include <meas\pubtype.h>
// #include <meas\source\PWASignals.h>
// #include <meas\source\Measure.h>
// #include <meas\source\Pressure.h>
// #include <meas\source\PWVSite.h>
// #include <meas\source\PWVSignals.h>
// #include <meas\source\Pulse.h>
// #include <meas\source\PWAPulse.h>
#include <meas\source\Mathem.h>
#include <meas\source\PWA.h>
#include <meas\source\PWV.h>
#include <meas\source\PWM.h>
#include <meas\source\hrvclass.h>
#include <meas\source\hrvtime.h>
#include <meas\source\HRVfrequency.h>
#include <meas\source\AVI.h>
#include <meas\source\Common.h>
// #include <meas\source\MsgBox.h>
// #include <meas\source\MsgDef.h>
#include <cfr11\pubtype.h>
#include <Series.hpp>
#include <scor\child.h>
//---------------------------------------------------------------------------

// Initialises the measurement objects resources.
bool meas_initialise(void);

void meas_destroy(void);

// Returns the pointer to the measurement data entry form
Child_Form  *meas_get_form_pointer();

String meas_pwa_get_table_name();
String meas_pwv_get_table_name();
String meas_hrv_get_table_name();

String meas_pwm_get_pwm_table_name();
String meas_pwm_get_session_table_name();
String meas_pwm_get_trend_table_name();
String meas_pwm_get_device_table_name();

// Show Recalculate form
bool meas_recalculate_show_form(TComponent* Owner, TPWA* pPwa, TDataSet* pDataSet,
     String pPatientName, AUDIT_MODE AuditMode, MEAS_SENDER_TYPE report_sender);
bool meas_recalculate_pwv_show_form(TComponent* Owner, TPWV* pPwv, TDataSet* pDataSet,
     String pPatientName, AUDIT_MODE AuditMode, MEAS_SENDER_TYPE report_sender);
bool meas_recalculate_hrv_show_form(TComponent* Owner, THRV* pHrv, TDataSet* pDataSet,
     String pPatientName, MEAS_SENDER_TYPE report_sender);

// Get series for a particular pulse
bool meas_GetSeriesForPulse(const int np, TPulse *pPulses, TLineSeries *pSeries,
                            const TColor pColor, const bool pWithTail = false);
// Get current PWA measurement
TPWA* meas_get_current_pwa();
// Get current PWV measurement
TPWV* meas_get_current_pwv();
// Get current PWM measurement
TPWM* meas_get_current_pwm();
// Get current HRV measurement
THRV* meas_get_current_hrv();
// Get current AVI measurement
TAVI* meas_get_current_avi();

THRVTime*  meas_get_current_hrvtime(void);
THRVFrequency*  meas_get_current_hrvfreq(void);
bool meas_hrv_classes_initialise(int sample_rate);

// return Date and time of measurement
TDateTime GetMeasureDateTime(TDataSet* pDataSet);
// Get string with measurement details
String GetCurrentPwaMeasureDetails();
// Get string with measurement details
String GetCurrentPwvMeasureDetails();
// Get string with measurement details
String GetCurrentPwmMeasureDetails();
// Get string with measurement details
String GetCurrentMeasureDetails();

String RoundIntToStr(float pValue);
#endif
