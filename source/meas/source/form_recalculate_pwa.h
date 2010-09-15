//---------------------------------------------------------------------------
#ifndef form_recalculate_pwaH
#define form_recalculate_pwaH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
#include <Mask.hpp>
#include <Buttons.hpp>
#include <ToolWin.hpp>
#include <vcl\db.hpp>
#include <ImgList.hpp>
#include <meas/pubserv.h>
//---------------------------------------------------------------------------
class Tfrm_recalculate_pwa : public TForm
{
__published:	// IDE-managed Components
  TPanel *Panel1;
  TPanel *Panel3;
  TPanel *pnlData;
   TLabel *lbl_artery;
  TComboBox *lstPA;
  TLabel *lbl_pat_title;
  TLabel *lbl_pat;
   TLabel *Label1;
   TLabel *Label2;
   TLabel *Label7;
   TLabel *Label13;
   TEdit *edtSp;
   TEdit *edtDp;
   TEdit *edtMp;
   TLabel *Label6;
   TLabel *Label8;
   TLabel *Label9;
   TLabel *txtBmi;
   TLabel *lbl_bmi_units;
   TLabel *lbl_feet;
   TLabel *lbl_inch;
   TLabel *lbl_pound;
   TLabel *lbl_height;
   TLabel *lbl_weight;
   TEdit *edtInch;
   TEdit *edtFeet;
   TEdit *edtPound;
   TEdit *edtHeight;
   TEdit *edtWeight;
   TLabel *Label3;
   TLabel *Label4;
   TLabel *lblOper;
   TMemo *edtMed;
   TMemo *edtNotes;
   TEdit *edtOperator;
   TGroupBox *grboxDist;
   TLabel *Label15;
   TLabel *Label16;
   TLabel *Label17;
   TLabel *Label18;
   TLabel *Label19;
   TEdit *edtDistance;
   TEdit *edtProximal;
   TEdit *edtDistal;
   TLabel *Label10;
   TMemo *edtInterpretation;
   TLabel *lbl_reason;
   TMemo *edtReason;
   TSpeedButton *bbtn_modify;
   TSpeedButton *bbtn_cancel;
  void __fastcall FormShow(TObject *Sender);
  void __fastcall edtSpChange(TObject *Sender);
  void __fastcall edtDpChange(TObject *Sender);
  void __fastcall edtMpChange(TObject *Sender);
  void __fastcall edtHeightChange(TObject *Sender);
  void __fastcall edtWeightChange(TObject *Sender);
   void __fastcall edtPoundChange(TObject *Sender);
   void __fastcall edtFeetChange(TObject *Sender);
   void __fastcall edtInchChange(TObject *Sender);
   void __fastcall edtDistanceChange(TObject *Sender);
   void __fastcall edtDistalChange(TObject *Sender);
   void __fastcall edtProximalChange(TObject *Sender);
   void __fastcall bbtn_modifyClick(TObject *Sender);
   void __fastcall bbtn_cancelClick(TObject *Sender);
private:	// User declarations
   void __fastcall CalcDistance();

   TPWA*             pwa_current;
   TDataSet*         pwa_dataset;
   AUDIT_MODE        pwa_audit_mode;
   MEAS_SENDER_TYPE  pwa_sender;
   bool UpdatePwa();
   bool recalculate_pwa_emr_mode(void);
public:		// User declarations
  __fastcall Tfrm_recalculate_pwa(TComponent* Owner,
             TPWA* pPwa, TDataSet* pDataSet, String pPatientName,
             AUDIT_MODE AuditMode, MEAS_SENDER_TYPE report_sender);
};
//---------------------------------------------------------------------------
// extern PACKAGE TfrmTonom *frmTonom;
//---------------------------------------------------------------------------
#endif
