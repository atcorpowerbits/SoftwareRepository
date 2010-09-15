//---------------------------------------------------------------------------
#ifndef form_pwvH
#define form_pwvH
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
#include <scor/child.h>
#include <meas/pubserv.h>
//---------------------------------------------------------------------------
class Tfrm_measure_pwv : public Child_Form
{
__published:	// IDE-managed Components
    TPanel *pnl_info;
  TPanel *pnlData;
  TPanel *pnlFields;
  TImage *Image1;
  TRadioGroup *rgAlgorithm;
   TGroupBox *grbSite;
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
   TCheckBox *chkbx_loopback;
   TEdit *edtInch;
   TEdit *edtFeet;
   TEdit *edtPound;
   TEdit *edtHeight;
   TEdit *edtWeight;
   TGroupBox *grboxDist;
   TLabel *Label10;
   TLabel *Label11;
   TLabel *Label12;
   TLabel *Label20;
   TLabel *Label21;
   TEdit *edtDistance;
   TEdit *edtProximal;
   TEdit *edtDistal;
   TEdit *edtPHPercent;
   TGroupBox *GroupBox1;
   TLabel *Label13;
   TLabel *Label14;
   TLabel *Label15;
   TLabel *Label16;
   TLabel *Label17;
   TLabel *Label18;
   TLabel *Label19;
   TLabel *Label22;
   TRadioButton *rbtnCarotidA;
   TRadioButton *rbtnRadialA;
   TRadioButton *rbtnFemoralA;
   TRadioButton *rbtnProximalA;
   TGroupBox *GroupBox2;
   TRadioButton *rbtnCarotidB;
   TRadioButton *rbtnRadialB;
   TRadioButton *rbtnFemoralB;
   TRadioButton *rbtnDistalB;
   TLabel *Label23;
   TGroupBox *GroupBox3;
   TRadioButton *rbtn10A;
   TRadioButton *rbtn20A;
   TRadioButton *rbtn30A;
   TLabel *Label24;
   TLabel *Label25;
   TGroupBox *GroupBox4;
   TRadioButton *rbtn10B;
   TRadioButton *rbtn20B;
   TRadioButton *rbtn30B;
   TLabel *Label26;
   TLabel *Label1;
   TLabel *Label6;
   TLabel *Label2;
   TLabel *Label9;
   TEdit *edtSp;
   TEdit *edtDp;
   TEdit *edtMp;
   TPanel *pnlGrid;
   TPanel *pnl_patient_information;
   TLabel *lbl_pat;
   TLabel *lbl_pat_title;
   TPanel *pnl_assessments;
   TLabel *lbl_assessments_title;
   TDBGrid *grdMeas;
   TPanel *pnlWait;
   TLabel *lblStatus;
   TImage *img_bkhearts;
   TSpeedButton *bbtn_capture;
  void __fastcall FormShow(TObject *Sender);
  void __fastcall FormHide(TObject *Sender);
  void __fastcall edtMpChange(TObject *Sender);
  void __fastcall edtDpChange(TObject *Sender);
  void __fastcall edtSpChange(TObject *Sender);
  void __fastcall FormKeyPress(TObject *Sender, char &Key);
  void __fastcall edtHeightChange(TObject *Sender);
  void __fastcall edtWeightChange(TObject *Sender);
  void __fastcall rgAlgorithmClick(TObject *Sender);
  void __fastcall edtDistanceChange(TObject *Sender);
  void __fastcall edtDistalChange(TObject *Sender);
  void __fastcall edtProximalChange(TObject *Sender);
  void __fastcall edtDistanceKeyPress(TObject *Sender, char &Key);
   void __fastcall edtFeetChange(TObject *Sender);
   void __fastcall edtInchChange(TObject *Sender);
   void __fastcall edtPoundChange(TObject *Sender);
   void __fastcall bbtn_captureClick(TObject *Sender);
    
    
    
private:	// User declarations
  void __fastcall CalcDistance();
  void __fastcall record_changed(TObject *Sender, TField  *Field);
public:		// User declarations
   TPWV       *pwv;
  __fastcall Tfrm_measure_pwv(TComponent* Owner);
  void __fastcall EmptyControls();
  bool __fastcall UpdatePwv();
};

extern Tfrm_measure_pwv *frm_measure_pwv;

bool meas_pwv_initialise(void);

bool meas_pwv_emr_mode(void);
#endif
