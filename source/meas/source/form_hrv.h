//---------------------------------------------------------------------------
#ifndef form_hrvH
#define form_hrvH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
#include <Db.hpp>
#include <DBCtrls.hpp>
#include <DBTables.hpp>
#include <Mask.hpp>
#include <DBGrids.hpp>
#include <Grids.hpp>
#include <Buttons.hpp>
#include <ToolWin.hpp>
#include <Graphics.hpp>
#include <ImgList.hpp>
#include <jpeg.hpp>
#include <meas/pubserv.h>
#include <scor/child.h>
//---------------------------------------------------------------------------
class Tfrm_measure_hrv : public Child_Form
{
__published:	// IDE-managed Components
  TPanel *Panel3;
  TPanel *pnlData;
  TPanel *pnlWait;
  TLabel *lblStatus;
  TPanel *pnlFields;
  TImage *img_bkhearts;
   TImage *Image1;
   TRadioGroup *rdgrp_study;
   TPanel *pnlGrid;
   TPanel *pnl_patient_information;
   TLabel *lbl_pat;
   TLabel *lbl_pat_title;
   TPanel *pnl_assessments;
   TLabel *lbl_assessments_title;
   TDBGrid *grdMeas;
   TLabel *Label3;
   TLabel *Label4;
   TLabel *lblOper;
   TLabel *Label5;
   TLabel *Label7;
   TLabel *Label8;
   TLabel *txtBmi;
   TLabel *lbl_bmi_units;
   TLabel *lbl_feet;
   TLabel *lbl_inch;
   TLabel *lbl_pound;
   TLabel *lbl_height;
   TLabel *lbl_weight;
   TMemo *edtMed;
   TMemo *edtNotes;
   TEdit *edtOperator;
   TCheckBox *chkbx_hrv_loopback;
   TEdit *edtInch;
   TEdit *edtFeet;
   TEdit *edtPound;
   TEdit *edtHeight;
   TEdit *edtWeight;
   TLabel *Label2;
   TLabel *Label1;
   TLabel *Label10;
   TEdit *edtSp;
   TLabel *Label11;
   TEdit *edtDp;
   TEdit *edtMp;
   TImage *Image2;
   TSpeedButton *bbtn_capture;
  void __fastcall FormShow(TObject *Sender);
  void __fastcall FormHide(TObject *Sender);
  void __fastcall edtMpChange(TObject *Sender);
  void __fastcall edtDpChange(TObject *Sender);
  void __fastcall edtSpChange(TObject *Sender);
  void __fastcall FormKeyPress(TObject *Sender, char &Key);
  void __fastcall edtHeightChange(TObject *Sender);
  void __fastcall edtWeightChange(TObject *Sender);
   void __fastcall edtFeetChange(TObject *Sender);
   void __fastcall edtInchChange(TObject *Sender);
   void __fastcall edtPoundChange(TObject *Sender);
   void __fastcall bbtn_captureClick(TObject *Sender);




private:	// User declarations
  void __fastcall record_changed(TObject *Sender, TField  *Field);
public:		// User declarations
   THRV          *meas_hrv;
   THRVTime      *meas_hrvtime;
   THRVFrequency *meas_hrvfreq;
  __fastcall Tfrm_measure_hrv(TComponent* Owner);
  void __fastcall EmptyControls();
  bool __fastcall UpdateHRV();
};

extern Tfrm_measure_hrv *frm_measure_hrv;

bool meas_hrv_form_initialise(void);

bool meas_hrv_emr_mode(void);
#endif
