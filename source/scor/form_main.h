#ifndef MAIN_PUBTYPE
#define MAIN_PUBTYPE

#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
#include <ExtCtrls.hpp>
#include <ComCtrls.hpp>
#include <Menus.hpp>
#include <Dialogs.hpp>
#include <Graphics.hpp>
//VA:Builder6 header needed? #include "GIFImage.hpp"
#include "TeeDraw3D.hpp"
#include <TeeProcs.hpp>
#include <jpeg.hpp>
#include <meas/pubtype.h>


//---------------------------------------------------------------------------
class Tfrm_main : public TForm
{
__published:	// IDE-managed Components
  TPanel *pnl_main_tool;
  TMainMenu *mnmnu_main;
  TMenuItem *System1;
  TMenuItem *Help1;
  TMenuItem *mnu_settings;
  TMenuItem *mnu_check_module;
  TMenuItem *mnu_print_setup;
  TPrinterSetupDialog *PrinterSetupDialog1;
  TMenuItem *mnu_exit;
  TMenuItem *Patient1;
  TMenuItem *Study1;
  TMenuItem *Report1;
  TMenuItem *Analysis1;
  TMenuItem *mnuAbout;
  TMenuItem *mnu_batch_print;
  TImage *img_pwvmed_print;
    TMenuItem *mnu_view;
    TMenuItem *mnu_listing;
    TMenuItem *mnu_database;
    TMenuItem *mnu_export;
    TMenuItem *mnu_merge;
    TMenuItem *mnu_pack;
    TMenuItem *mnu_multdb;
    TMenuItem *N1;
    TMenuItem *N2;
    TMenuItem *N3;
        TDraw3D *drw3d_pnl_main_buttons;
        TSpeedButton *spdbtn_patient;
        TSpeedButton *spdbtn_measure;
        TSpeedButton *spdbtn_report;
        TSpeedButton *spdbtn_analysis;
        TSpeedButton *spdbtn_idle;
        TLabel *lbl_scor_mode;
        TImage *img_privacy;
        TMenuItem *mnu_export_database;
   TMenuItem *mnu_view_report;
   TMenuItem *mnu_recalculate_all;
   TMenuItem *Mode1;
   TMenuItem *Privacy1;
   TLabel *lbl_data_mode;
   TImage *img_trademark;
   TImage *img_plus_minus;
   TPanel *pnl_status_bar;
   TDraw3D *drw3d_status_bar;
   TImage *Image1;
   TLabel *lbl_message1;
   TLabel *lbl_message2;
   TLabel *lbl_active_database;
   TLabel *lbl_message3;
   TImage *img_print_clinical;
   TImage *img_print_reference_age;
   TMenuItem *mnu_find_module;
   TProgressBar *prgbar_main;
   TLabel *lbl_message4;
  void __fastcall FormShow(TObject *Sender);
  void __fastcall mnu_print_setupClick(TObject *Sender);
  void __fastcall mnu_check_moduleClick(TObject *Sender);
  void __fastcall mnu_exitClick(TObject *Sender);
  void __fastcall spdbtn_reportClick(TObject *Sender);
  void __fastcall spdbtn_analysisClick(TObject *Sender);
  void __fastcall spdbtn_measureClick(TObject *Sender);
  void __fastcall mnu_settingsClick(TObject *Sender);
  void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
  void __fastcall img_pwvmedClick(TObject *Sender);
  void __fastcall mnu_batch_printClick(TObject *Sender);
  void __fastcall mnu_export_click(TObject *Sender);
  void __fastcall mnu_multdbClick(TObject *Sender);
  void __fastcall FormDestroy(TObject *Sender);
    void __fastcall mnu_listingClick(TObject *Sender);
    void __fastcall mnu_mergeClick(TObject *Sender);
    void __fastcall mnu_packClick(TObject *Sender);
        void __fastcall mnu_export_databaseClick(TObject *Sender);
        void __fastcall spdbtn_idleClick(TObject *Sender);
   void __fastcall mnu_recalculate_allClick(TObject *Sender);
   void __fastcall Mode1Click(TObject *Sender);
   void __fastcall spdbtn_patientClick(TObject *Sender);
   void __fastcall mnu_find_moduleClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
   void __fastcall ChangeActiveForm(TObject *Sender);
   //TProgressBar *prgbar_main;
    __fastcall Tfrm_main(TComponent* Owner);
};

extern PACKAGE Tfrm_main *frm_main;

TForm *emma_get_main_form_pointer(void);

void emma_display_statusbar_message(AnsiString msg1, AnsiString msg2, AnsiString hint, TColor color);

void emma_display_statusbar_message(AnsiString msg1, AnsiString msg2, TColor color);

void emma_disable_speed_buttons(void);

void emma_enable_speed_buttons(void);

bool emma_is_initialised(void);


MEAS_ID_TYPE emma_get_study_mode(void);

#endif
