//---------------------------------------------------------------------------

#ifndef form_recalculate_hrvH
#define form_recalculate_hrvH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
#include <meas/pubserv.h>
//---------------------------------------------------------------------------
class Tfrm_recalculate_hrv : public TForm
{
__published:	// IDE-managed Components
   TPanel *Panel3;
   TPanel *pnlData;
   TPanel *Panel1;
   TLabel *lbl_pat_title;
   TLabel *lbl_pat;
   TLabel *Label1;
   TLabel *Label2;
   TLabel *Label7;
   TLabel *Label13;
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
   TSpeedButton *bbtn_modify;
   TSpeedButton *bbtn_cancel;
   void __fastcall FormShow(TObject *Sender);
   void __fastcall edtSpChange(TObject *Sender);
   void __fastcall edtMpChange(TObject *Sender);
   void __fastcall edtDpChange(TObject *Sender);
   void __fastcall edtHeightChange(TObject *Sender);
   void __fastcall edtWeightChange(TObject *Sender);
   void __fastcall edtPoundChange(TObject *Sender);
   void __fastcall edtFeetChange(TObject *Sender);
   void __fastcall edtInchChange(TObject *Sender);
   void __fastcall bbtn_modifyClick(TObject *Sender);
   void __fastcall bbtn_cancelClick(TObject *Sender);
private:	// User declarations
   THRV*             hrv_current;
   TDataSet*         hrv_dataset;
   MEAS_SENDER_TYPE  hrv_sender;
   bool UpdateHrv();
   bool recalculate_hrv_emr_mode(void);
public:		// User declarations
  __fastcall Tfrm_recalculate_hrv(TComponent* Owner,
             THRV* pHrv, TDataSet* pDataSet, String pPatientName, MEAS_SENDER_TYPE report_sender);
};
//---------------------------------------------------------------------------
extern PACKAGE Tfrm_recalculate_hrv *frm_recalculate_hrv;
//---------------------------------------------------------------------------
#endif
