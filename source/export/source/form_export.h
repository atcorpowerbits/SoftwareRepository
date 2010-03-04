//---------------------------------------------------------------------------
#ifndef form_exportH
#define form_exportH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Buttons.hpp>
#include <ComCtrls.hpp>
#include <Db.hpp>
#include <DBTables.hpp>
#include <Dialogs.hpp>
#include <meas\pubserv.h>
//---------------------------------------------------------------------------
class Tfrm_export : public TForm
{
__published:	// IDE-managed Components
  TPanel *pnl_buttons;
  TPanel *pnl_header;
  TPanel *pnl_file_select;
  TLabel *lbl_export_title;
  TEdit *edtFile;
  TOpenDialog *OpenDialog1;
  TPanel *pnl_status;
  TLabel *lblTitle;
  TProgressBar *prgbar_export;
  TLabel *lblProg;
   TSpeedButton *btnExport;
   TSpeedButton *btnCancel;
   TSpeedButton *btnClose;
   TSpeedButton *btnSelect;
  void __fastcall btnExportClick(TObject *Sender);

  void __fastcall btnCloseClick(TObject *Sender);
  void __fastcall btnSelectClick(TObject *Sender);
  void __fastcall FormShow(TObject *Sender);
  void __fastcall btnCancelClick(TObject *Sender);
private:	// User declarations
  int ExportMode;
  bool CloseApp;
  TDataSet* fTblMeas;
  TDataSet* fTblPatient;
  Graphics::TBitmap*   bmp_image;

  TPWA *pwa;
  TPWV *pwv;
  TPWM *pwm;
  THRV *hrv;

  bool __fastcall ExportOneMeasurement(TPWA *pwa, int lFileHandle, bool is_pwa);
  bool __fastcall ExportPatientMeasurements(TPWA *pwa, int lFileHandle, int &pExpRec, int &pAllRec);
  bool __fastcall ExportAllMeasurements(TPWA *pwa, int lFileHandle, int &pExpRec, int &pAllRec);
  bool __fastcall ExportOneMeasurement(TPWV *pwv, int lFileHandle);
  bool __fastcall ExportPatientMeasurements(TPWV *pwv, int lFileHandle, int &pExpRec, int &pAllRec);
  bool __fastcall ExportAllMeasurements(TPWV *pwv, int lFileHandle, int &pExpRec, int &pAllRec);
  bool __fastcall ExportSessionTrend(int lFileHandle, int &pExpRec, int &pAllRec);
  bool __fastcall ExportPatientMeasurements(TPWM *pwm, int lFileHandle, int &pExpRec, int &pAllRec);
  bool __fastcall ExportAllMeasurements(TPWM *pwm, int lFileHandle, int &pExpRec, int &pAllRec);
  bool __fastcall ExportOneMeasurement(THRV *hrv, int lFileHandle);
  bool __fastcall ExportPatientMeasurements(THRV *hrv, int lFileHandle, int &pExpRec, int &pAllRec);
  bool __fastcall ExportAllMeasurements(THRV *hrv, int lFileHandle, int &pExpRec, int &pAllRec);
  bool __fastcall ExportOneGraphic(Graphics::TBitmap*   bmp_image, String jpeg_file_name);

public:		// User declarations
  __fastcall Tfrm_export(TComponent* Owner, String pFileName, TDataSet *pTblPWA, TPWA *pPwa, int s_id);
  __fastcall Tfrm_export(TComponent* Owner, String pFileName, TDataSet *pTblPWA, TPWA *pPwa, bool mode);
  __fastcall Tfrm_export(TComponent* Owner, String pFileName, TDataSet *pTblPWA, TPWA *pPwa, bool mode, bool pAll);

  __fastcall Tfrm_export(TComponent* Owner, String pFileName, TDataSet *pTblPWV, TPWV *pPwv);
  __fastcall Tfrm_export(TComponent* Owner, String pFileName, TDataSet *pTblPWV, TPWV *pPwv, bool mode);
  __fastcall Tfrm_export(TComponent* Owner, String pFileName, TDataSet *pTblPWV, TPWV *pPwv, bool mode, bool pAll);

  __fastcall Tfrm_export(TComponent* Owner, String pFileName, TDataSet *pTblSession, TPWM *pPwm);
  __fastcall Tfrm_export(TComponent* Owner, String pFileName, TDataSet *pTblPWM, TPWM *pPwm, const bool pwa_reports);
  __fastcall Tfrm_export(TComponent* Owner, String pFileName, TDataSet *pTblPWM, TPWM* pPwm, bool mode, bool pAll);

  __fastcall Tfrm_export(TComponent* Owner, String pFileName, TDataSet *pTblHRV, THRV* pHrv);
  __fastcall Tfrm_export(TComponent* Owner, String pFileName, TDataSet *pTblHRV, THRV* pHrv, bool mode);
  __fastcall Tfrm_export(TComponent* Owner, String pFileName, TDataSet *pTblHRV, THRV* pHrv, bool mode, bool pAll);

  __fastcall Tfrm_export(TComponent* Owner, String pFileName, Graphics::TBitmap *form_bmp);

  bool Success;
  int session_id;
  String ActTitle;
};
//---------------------------------------------------------------------------
//extern PACKAGE Tfrm_export *frm_export;
//---------------------------------------------------------------------------
#endif
