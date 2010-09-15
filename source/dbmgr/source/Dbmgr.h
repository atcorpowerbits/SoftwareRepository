#ifndef dbmgrH
#define dbmgrH

#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Db.hpp>
#include <DBTables.hpp>
#include <ADODB.hpp>
#include <DB.hpp>

#include <dbmgr/pubtype.h>

#define DBMGR_DATABASE_EXT ".MDB"

//---------------------------------------------------------------------------
class Tdbmgr_dmod : public TDataModule
{
__published:	// IDE-managed Components
    TDataSource *dsrc_patient;
    TDataSource *dsrc_measure_pwa;
    TDataSource *dsrc_qry_patient;
    TDataSource *dsrc_qry_measure_pwa;
  TDataSource *dsrc_qry_measure_pwv;
  TDataSource *dsrc_measure_pwv;
    TDataSource *dsrc_measure_pwm;
    TDataSource *dsrc_qry_measure_pwm;
    TDataSource *dsrc_measure_pwm_trend;
    TDataSource *dsrc_qry_measure_pwm_trend;
    TDataSource *dsrc_measure_pwm_session;
    TDataSource *dsrc_qry_measure_pwm_session;
    TDataSource *dsrc_device_pwm;
        TADOConnection *ADO_Connection;
        TADOTable *tbl_patient;
        TADOTable *tbl_measure_pwa;
        TADOTable *tbl_measure_pwm_trend;
        TADOQuery *qry_patient;
        TADOQuery *qry_measure_pwa;
        TADOQuery *qry_measure_pwm_trend;
        TADOTable *tbl_measure_pwm;
        TADOTable *tbl_measure_pwm_session;
        TADOTable *tbl_measure_pwv;
        TADOTable *tbl_device_pwm;
        TADOQuery *qry_measure_pwv;
        TADOQuery *qry_measure_pwm;
        TADOQuery *qry_measure_pwm_session;
        TADOConnection *ADO_Connection_copy;
        TADOTable *tbl_patient_copy;
        TADOTable *tbl_measure_pwa_copy;
        TDataSource *dsrc_patient_copy;
        TDataSource *dsrc_measure_pwa_copy;
        TADOTable *tbl_measure_hrv;
        TDataSource *dsrc_measure_hrv;
        TDataSource *dsrc_qry_measure_hrv;
        TADOQuery *qry_measure_hrv;
   TDataSource *dsrc_measure_pwv_copy;
   TDataSource *dsrc_measure_pwm_copy;
   TDataSource *dsrc_measure_pwm_trend_copy;
   TDataSource *dsrc_measure_pwm_session_copy;
   TDataSource *dsrc_device_pwm_copy;
   TADOTable *tbl_measure_pwm_trend_copy;
   TADOTable *tbl_measure_pwm_copy;
   TADOTable *tbl_measure_pwm_session_copy;
   TADOTable *tbl_measure_pwv_copy;
   TADOTable *tbl_device_pwm_copy;
   TDataSource *dsrc_measure_hrv_copy;
   TADOTable *tbl_measure_hrv_copy;
   TDataSource *dsrc_patient_audit;
   TDataSource *dsrc_measure_pwa_audit;
   TDataSource *dsrc_qry_patient_audit;
   TDataSource *dsrc_qry_measure_pwa_audit;
   TADOTable *tbl_patient_audit;
   TADOTable *tbl_measure_pwa_audit;
   TADOQuery *qry_patient_audit;
   TADOQuery *qry_measure_pwa_audit;
   TADOTable *tbl_patient_audit_copy;
   TADOTable *tbl_measure_pwa_audit_copy;
   TDataSource *dsrc_patient_audit_copy;
   TDataSource *dsrc_measure_pwa_audit_copy;
   TDataSource *dsrc_measure_pwv_audit;
   TDataSource *dsrc_qry_measure_pwv_audit;
   TADOTable *tbl_measure_pwv_audit;
   TADOQuery *qry_measure_pwv_audit;
   TADOTable *tbl_measure_pwv_audit_copy;
   TDataSource *dsrc_measure_pwv_audit_copy;
private:	// User declarations
public:		// User declarations
    __fastcall Tdbmgr_dmod(TComponent* Owner);
};

bool dbmgr_perform_file_check(DBMGR_ID_TYPE  id,
                              AnsiString     db_path,
                              bool           is_copy);
bool dbmgr_convert_database(TLabel* status, AnsiString the_path);

bool dbmgr_copy_table(DBMGR_ID_TYPE  id);

bool dbmgr_copy_table_to_table(DBMGR_ID_TYPE  source, DBMGR_ID_TYPE  copy);

extern PACKAGE Tdbmgr_dmod *dbmgr_dmod;
#endif
