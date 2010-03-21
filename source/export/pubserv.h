//---------------------------------------------------------------------------
#ifndef ExportPubservH
#define ExportPubservH
#include <vcl\vcl.h>
#include <vcl\db.hpp>
#include <vcl\dbtables.hpp>
#include <export\pubtype.h>
#include <meas\pubserv.h>
//---------------------------------------------------------------------------
// object main function to convert Dbase into MSAccess
//---------------------------------------------------------------------------
bool export_all_measurements(TDataSet* pTblPWA, String pFileName, TPWA *pPwa);
bool export_patient_measurements(TDataSet *pTblPWA, String pFileName, TPWA *pPwa);
bool export_measurement(TDataSet *pTblPWA, String pFileName, TPWA *pPwa, int the_session_id);
bool export_all_measurements(TDataSet* pTblPWV, String pFileName, TPWV *pPwv);
bool export_patient_measurements(TDataSet *pTblPWV, String pFileName, TPWV *pPwv);
bool export_measurement(TDataSet *pTblPWV, String pFileName, TPWV *pPwv);
bool export_pwm_session(TDataSet *pTblTrend, String pFileName, TPWM *pPwm);
bool export_patient_measurements(TDataSet *pTblPWM, String pFileName, TPWM* pPwm);
bool export_all_measurements(TDataSet* pTblPWM, String pFileName, TPWM* pPwm);
bool export_all_measurements(TDataSet* pTblHRV, String pFileName, THRV* pHrv);
bool export_patient_measurements(TDataSet *pTblHRV, String pFileName, THRV* pHrv);
bool export_measurement(TDataSet *pTblHRV, String pFileName, THRV *pHrv);
bool export_graphic(Graphics::TBitmap *form_bmp, String pFileName);
bool export_database_show(void);
//---------------------------------------------------------------------------
#endif
