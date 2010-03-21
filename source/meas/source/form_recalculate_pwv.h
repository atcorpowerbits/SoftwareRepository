//---------------------------------------------------------------------------
#ifndef form_recalculate_pwvH
#define form_recalculate_pwvH
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
#include <Graphics.hpp>
#include <meas/pubserv.h>
//---------------------------------------------------------------------------
class Tfrm_recalculate_pwv : public TForm
{
__published:	// IDE-managed Components
   TPanel *Panel1;
   TLabel *lbl_pat_title;
   TLabel *lbl_pat;
   TPanel *pnlData;
   TPanel *pnlFields;
   TLabel *Label1;
   TLabel *Label2;
   TLabel *Label7;
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
   TLabel *Label3;
   TLabel *Label4;
   TLabel *lblOper;
   TLabel *lbl_reason;
   TEdit *edtSp;
   TEdit *edtDp;
   TEdit *edtMp;
   TEdit *edtInch;
   TEdit *edtFeet;
   TEdit *edtPound;
   TEdit *edtHeight;
   TEdit *edtWeight;
   TMemo *edtMed;
   TMemo *edtNotes;
   TEdit *edtOperator;
   TMemo *edtReason;
   TGroupBox *grboxDist;
   TLabel *Label10;
   TLabel *Label5;
   TLabel *Label13;
   TLabel *Label20;
   TLabel *Label21;
   TEdit *edtDistance;
   TEdit *edtProximal;
   TEdit *edtDistal;
   TGroupBox *grbSite;
   TLabel *Label14;
   TLabel *Label15;
   TLabel *Label16;
   TLabel *Label17;
   TLabel *Label24;
   TLabel *Label25;
   TLabel *Label26;
   TLabel *Label27;
   TGroupBox *GroupBox1;
   TRadioButton *rbtnCarotidA;
   TRadioButton *rbtnRadialA;
   TRadioButton *rbtnFemoralA;
   TRadioButton *rbtnProximalA;
   TGroupBox *GroupBox2;
   TRadioButton *rbtnCarotidB;
   TRadioButton *rbtnRadialB;
   TRadioButton *rbtnFemoralB;
   TRadioButton *rbtnDistalB;
   TRadioGroup *rgAlgorithm;
   TEdit *edtPHPercent;
   TSpeedButton *bbtn_modify;
   TSpeedButton *bbtn_cancel;
  void __fastcall FormShow(TObject *Sender);
  void __fastcall edtSpChange(TObject *Sender);
  void __fastcall edtDpChange(TObject *Sender);
  void __fastcall edtMpChange(TObject *Sender);
  void __fastcall edtHeightChange(TObject *Sender);
  void __fastcall edtWeightChange(TObject *Sender);
  void __fastcall edtDistanceChange(TObject *Sender);
  void __fastcall edtDistalChange(TObject *Sender);
  void __fastcall edtProximalChange(TObject *Sender);
  void __fastcall rgAlgorithmClick(TObject *Sender);
  void __fastcall edtDistanceKeyPress(TObject *Sender, char &Key);
  void __fastcall FormKeyPress(TObject *Sender, char &Key);
   void __fastcall edtFeetChange(TObject *Sender);
   void __fastcall edtInchChange(TObject *Sender);
   void __fastcall edtPoundChange(TObject *Sender);
   void __fastcall bbtn_modifyClick(TObject *Sender);
   void __fastcall bbtn_cancelClick(TObject *Sender);
    
private:	// User declarations
   TPWV*             pwv;
   TDataSet*         pwv_dataset;
   AUDIT_MODE        pwv_audit_mode;
   MEAS_SENDER_TYPE  pwv_sender;
   bool __fastcall UpdatePwv();
   void __fastcall CalcDistance();
   bool recalculate_pwv_emr_mode(void);
public:		// User declarations
  __fastcall Tfrm_recalculate_pwv(TComponent* Owner, TPWV* pPwv,
               TDataSet* pDataSet, String pPatientName, AUDIT_MODE AuditMode, MEAS_SENDER_TYPE report_sender);
};
//---------------------------------------------------------------------------
// extern PACKAGE TfrmTonom *frmTonom;
//---------------------------------------------------------------------------
#endif
