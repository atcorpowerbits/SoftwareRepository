//---------------------------------------------------------------------------
#ifndef form_pwaH
#define form_pwaH
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
#include <meas/pubserv.h>
#include <scor/child.h>
//---------------------------------------------------------------------------
class Tfrm_measure_pwa : public Child_Form
{
__published:	// IDE-managed Components
  TPanel *Panel3;
  TPanel *pnlGrid;
  TPanel *pnlData;
    TPanel *pnlWait;
    TLabel *lblStatus;
    TPanel *pnlFields;
    TMemo *edtMed;
    TLabel *Label3;
    TLabel *Label4;
    TMemo *edtNotes;
    TEdit *edtOperator;
    TLabel *lblOper;
  TEdit *edtSp;
  TEdit *edtDp;
  TEdit *edtMp;
  TCheckBox *chkCarotid;
  TCheckBox *chkAortic;
  TCheckBox *chkRadial;
  TLabel *Label1;
  TLabel *Label2;
  TLabel *Label6;
    TImage *img_bkhearts;
    TCheckBox *chkbx_pwa_loopback;
   TTimer *tmr_repeat_assessment;
   TPanel *pnl_patient_information;
   TLabel *lbl_pat;
   TLabel *lbl_pat_title;
   TPanel *pnl_assessments;
   TLabel *lbl_assessments_title;
   TDBGrid *grdMeas;
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
   TEdit *edtInch;
   TEdit *edtFeet;
   TEdit *edtPound;
   TEdit *edtHeight;
   TEdit *edtWeight;
   TImage *img_waveform;
   TLabel *Label9;
   TImage *img_artery;
   TGroupBox *grboxDist;
   TLabel *Label15;
   TLabel *Label16;
   TLabel *Label17;
   TLabel *Label18;
   TLabel *Label19;
   TEdit *edtDistance;
   TEdit *edtProximal;
   TEdit *edtDistal;
   TSpeedButton *bbtn_capture;
  void __fastcall FormShow(TObject *Sender);
  void __fastcall FormHide(TObject *Sender);
  void __fastcall edtMpChange(TObject *Sender);
  void __fastcall edtDpChange(TObject *Sender);
  void __fastcall edtSpChange(TObject *Sender);
  void __fastcall chkRadialClick(TObject *Sender);
  void __fastcall chkAorticClick(TObject *Sender);
  void __fastcall chkCarotidClick(TObject *Sender);
  void __fastcall FormKeyPress(TObject *Sender, char &Key);
  void __fastcall edtHeightChange(TObject *Sender);
  void __fastcall edtWeightChange(TObject *Sender);
   void __fastcall edtPoundChange(TObject *Sender);
   void __fastcall edtFeetChange(TObject *Sender);
   void __fastcall edtInchChange(TObject *Sender);
   void __fastcall edtDistanceChange(TObject *Sender);
   void __fastcall edtDistalChange(TObject *Sender);
   void __fastcall edtProximalChange(TObject *Sender);
   void __fastcall tmr_repeat_assessmentTimer(TObject *Sender);
   void __fastcall bbtn_captureClick(TObject *Sender);
    

private:	// User declarations
   void __fastcall CalcDistance();
   class Meas_Data_Event_Class
  {
    public:
      void __fastcall record_changed(TObject *Sender, TField  *Field);
  } data_event;
public:		// User declarations
   TPWA       *pwa_current;
  __fastcall Tfrm_measure_pwa(TComponent* Owner);
  void __fastcall EmptyControls();
  bool __fastcall UpdatePwa();
};

extern Tfrm_measure_pwa *frm_measure_pwa;

bool meas_pwa_initialise(void);

bool meas_pwa_emr_mode(void);
#endif
