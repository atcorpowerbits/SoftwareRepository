//---------------------------------------------------------------------------
#ifndef form_pwmH
#define form_pwmH
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
class Tfrm_measure_pwm : public Child_Form
{
__published:	// IDE-managed Components
  TPanel *Panel3;
  TPanel *pnlData;
    TPanel *pnlWait;
    TLabel *lblStatus;
    TPageControl *pgctrl_mx_settings;
    TTabSheet *tbsht_session;
  TPanel *pnlFields;
  TLabel *lblDevice;
  TCheckBox *chkCalibrated;
    TTabSheet *tbsht_control;
  TPanel *Panel1;
  TRadioGroup *rgTSP;
  TRadioGroup *rgTRP;
  TRadioGroup *rgRGP;
  TDBLookupComboBox *dblstDevice;
    TGroupBox *grpbx_output;
  TCheckBox *chkbx_periph;
    TCheckBox *chkbx_aortic;
    TEdit *edt_cal_ratio;
    TLabel *lbl_cal_ratio;
    TLabel *lbl_cal_offset;
    TEdit *edt_cal_offset;
    TLabel *lbl_cal_units;
    TLabel *lbl_offset_units;
    TImage *img_hrt_bkgnd;
    TCheckBox *chkbx_autoscale_trends;
   TPanel *pnl_buttons;
   TRadioGroup *rdgrp_pwm_input;
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
   TImage *img_artery;
   TMemo *edtMed;
   TMemo *edtNotes;
   TEdit *edtOperator;
   TCheckBox *chkAortic;
   TCheckBox *chkRadial;
   TEdit *edtInch;
   TEdit *edtFeet;
   TEdit *edtPound;
   TEdit *edtHeight;
   TEdit *edtWeight;
   TPanel *pnlSpDp;
   TImage *img_waveform;
   TLabel *Label1;
   TLabel *Label6;
   TLabel *Label2;
   TLabel *Label11;
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
   TSpeedButton *bbtn_capture;
   TGroupBox *grpbx_parameter;
   TCheckBox *chkbx_aix;
   TComboBox *cmbx_comports;
   TLabel *Label9;
  void __fastcall FormShow(TObject *Sender);
  void __fastcall FormHide(TObject *Sender);
  void __fastcall edtMpChange(TObject *Sender);
  void __fastcall edtDpChange(TObject *Sender);
  void __fastcall edtSpChange(TObject *Sender);
  void __fastcall chkRadialClick(TObject *Sender);
  void __fastcall chkAorticClick(TObject *Sender);
  void __fastcall FormKeyPress(TObject *Sender, char &Key);
  void __fastcall edtHeightChange(TObject *Sender);
  void __fastcall edtWeightChange(TObject *Sender);
  void __fastcall chkCalibratedClick(TObject *Sender);

    void __fastcall dblstDeviceClick(TObject *Sender);
   void __fastcall edtFeetChange(TObject *Sender);
   void __fastcall edtInchChange(TObject *Sender);
   void __fastcall edtPoundChange(TObject *Sender);
   void __fastcall bbtn_captureClick(TObject *Sender);
   void __fastcall chkbx_aixClick(TObject *Sender);
    
    
private:	// User declarations
  void __fastcall record_changed(TObject *Sender, TField  *Field);
public:		// User declarations
   TPWM       *pwm;
  __fastcall Tfrm_measure_pwm(TComponent* Owner);
  void __fastcall EmptyControls();
  bool __fastcall UpdatePwm();
};

extern Tfrm_measure_pwm *frm_measure_pwm;

bool meas_pwm_initialise(void);
#endif
