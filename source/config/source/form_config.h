#ifndef form_configH
#define form_configH

#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Buttons.hpp>
#include <ComCtrls.hpp>
#include <Inifiles.hpp>
#include <Dialogs.hpp>
#include <inc/std.h>
#include <config/pubtype.h>
#include <comms/pubtype.h>

class Tfrm_config : public TForm
{
__published:	// IDE-managed Components
  TPanel *pnl_config;
  TGroupBox *grpbx_qc;
  TEdit *edt_qcph;
  TLabel *lbl_qcph;
  TLabel *lbl_qcphv;
  TEdit *edt_qcphv;
  TLabel *lbl_qcdv;
  TEdit *edt_qcdv;
  TGroupBox *grpbx_comms;
  TGroupBox *grpbx_pressure_sensitivity;
  TLabel *lbl_upper_limit;
  TEdit *edt_p_upper_limit;
    TComboBox *cmbx_comports;
        TGroupBox *grpbx_report_styles;
        TCheckBox *chkbx_blind_study;
   TCheckBox *chkbx_clinical_aix;
   TGroupBox *grpbx_measurement_units;
   TRadioButton *rbtn_metric;
   TRadioButton *rbtn_imperial;
   TGroupBox *grpbx_tonometer;
   TEdit *edt_tonometer;
   TGroupBox *grpbx_report_screen;
   TCheckBox *chkbx_detailed;
   TCheckBox *chkbx_clinical;
   TGroupBox *grpbx_rtof;
   TCheckBox *chkbx_rtof;
   TCheckBox *chkbx_auto_capture;
   TCheckBox *chkbx_clinical_aixhr75;
   TPanel *pnl_buttons;
   TSpeedButton *btn_config_save;
   TSpeedButton *btn_config_cancel;
   TSpeedButton *btn_defaults;
   TSpeedButton *btn_select_dir;
  void __fastcall btn_defaultsClick(TObject *Sender);
  void __fastcall btn_config_saveClick(TObject *Sender);
  void __fastcall FormShow(TObject *Sender);
  void __fastcall btn_config_cancelClick(TObject *Sender);
  
  void __fastcall edt_qcphChange(TObject *Sender);
  void __fastcall edt_qcphvChange(TObject *Sender);
  void __fastcall edt_qcdvChange(TObject *Sender);
  void __fastcall edt_p_upper_limitChange(TObject *Sender);
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
        void __fastcall cmbx_comportsChange(TObject *Sender);
        void __fastcall btn_select_dirClick(TObject *Sender);
   void __fastcall chkbx_detailedClick(TObject *Sender);
   void __fastcall chkbx_clinicalClick(TObject *Sender);
   void __fastcall chkbx_blind_studyClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
  __fastcall Tfrm_config(TComponent* Owner);
};

typedef struct
{
   AnsiString             system_id;
   AnsiString             last_pack_date;
   AnsiString             report_title;
   UCOUNT                 capabilities;
   CONFIG_SYSTEM_OPTIONS  option;
   UINT16                 crc16;
   UCOUNT                 qc_ph;
   UTINY                  qc_phv;
   UTINY                  qc_dv;
   COMMS_ID_TYPE          old_port;
   COMMS_ID_TYPE          port;
   UCOUNT                 p_upper_limit;
   UTINY                  report_style;
   UTINY                  report_screen;
   UTINY                  ptiv;
   UTINY                  srri;
   TStringList            *port_list;
   UTINY                  locale;
   bool                   avi_enabled;
   UINT32                 tonometer;
   bool                   audit_enabled;
   bool                   rtof;
   bool                   auto_capture;
   bool                   clinical_enabled;
   bool                   clinical_aixhr75;
   bool                   clinical_aix;
} CONFIG_RECORD_TYPE;

UINT16 config_check_system_id(AnsiString str);

bool config_determine_capabilities(void);

bool config_enable_ports(void);

bool config_validate_directory(String directory);

void config_decode_command_line(void);

extern CONFIG_RECORD_TYPE  config;
extern PACKAGE Tfrm_config *frm_config;
extern TStringList         *config_options_list;
extern TIniFile            *config_ini;
extern String              simulation_directory;
#endif
