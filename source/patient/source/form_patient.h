//---------------------------------------------------------------------------
#ifndef form_patientH
#define form_patientH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <vcl\ExtCtrls.hpp>
#include <vcl\ComCtrls.hpp>
#include <vcl\DBGrids.hpp>
#include "Grids.hpp"
#include <vcl\DBCtrls.hpp>
#include <vcl\Mask.hpp>
#include <vcl\Buttons.hpp>
#include <Menus.hpp>
#include <ToolWin.hpp>
#include <ImgList.hpp>
#include "TeeDraw3D.hpp"
#include <TeeProcs.hpp>
#include <CheckLst.hpp>
#include <Classes.hpp>
#include <scor\child.h>

class Tfrm_patient : public Child_Form
{
__published:	// IDE-managed Components
    TPanel *pnl_data_area;
    TPanel *pnl_grid;
    TPageControl *pgctrl_pat;
    TTabSheet *tbsht_pat_grid;
    TTabSheet *tbsht_pat_summary;
    TImageList *imglst_patient;
    TPopupMenu *pupmnu_pat_grid;
    TMenuItem *mnuSort;
    TMenuItem *mnuSortName;
    TMenuItem *mnuSortAge;
  TMenuItem *mnuSortPID;
    TMenuItem *mnuExport;
  TMenuItem *mnu_sort_patno;
        TPanel *pnl_mode_buttons;
        TDraw3D *drw3d_mode_panel;
        TSpeedButton *spbtn_pwa_mode;
        TSpeedButton *spbtn_pwv_mode;
        TSpeedButton *spbtn_pwm_mode;
        TSpeedButton *spbtn_hrv_mode;
        TLabel *lbl_mode_title;
   TPageControl *pgctrl_int;
   TTabSheet *tbsht_details;
   TTabSheet *tbsht_int;
   TPanel *pnl_buttons;
   TBitBtn *bbtn_done;
   TPanel *pnl_questions;
   TCheckListBox *chklstbx_interview;
   TPanel *pnl_summary;
   TLabel *lbl_title;
   TLabel *lbl_pat_name;
   TLabel *lbl_title_total;
   TLabel *lbl_total;
   TLabel *lbl_title_first;
   TLabel *lbl_title_last;
   TLabel *lbl_first;
   TLabel *lbl_last;
   TLabel *lbl_title_days;
   TLabel *lbl_days;
   TPanel *Panel1;
   TDBGrid *grd_search;
   TPanel *pnl_search;
   TLabel *Label1;
   TLabel *Label2;
   TLabel *Label3;
   TLabel *Label5;
   TLabel *Label6;
   TDateTimePicker *dtpck_search_dob;
   TEdit *edt_search_pid;
   TEdit *edt_search_surname;
   TEdit *edt_search_fname;
   TPanel *pnl_pat_data;
   TPanel *pnl_data;
   TLabel *lbl_pat_dob;
   TLabel *lbl_pat_fname;
   TLabel *lbl_pat_oname;
   TLabel *lbl_pat_sex;
   TLabel *lbl_pat_code;
   TLabel *lbl_pat_surname;
   TLabel *lbl_patid;
   TLabel *lbl_sysid_title;
   TLabel *lbl_pat_notes;
   TLabel *lbl_study_id;
   TDBText *dbtxt_sysid;
   TDBText *dbtxt_dbid;
   TLabel *lbl_active_dbname_title;
   TLabel *lbl_active_dbname;
   TLabel *lbl_pat_reason;
   TLabel *lbl_operator;
   TDBText *dbtxt_operator;
   TDBEdit *edt_pat_surname;
   TDBEdit *edt_pat_fname;
   TDBEdit *edt_pat_oname;
   TDBEdit *edt_pat_code;
   TDBEdit *edt_pat_pid;
   TDBComboBox *cmbx_pat_sex;
   TDateTimePicker *dtpck_pat_dob;
   TDBMemo *mm_pat_notes;
   TGroupBox *gbx_address;
   TLabel *lbl_street;
   TLabel *lbl_suburb;
   TLabel *lbl_state;
   TLabel *lbl_country;
   TLabel *lbl_phone;
   TLabel *lbl_pcode;
   TDBEdit *edt_pat_street;
   TDBEdit *edt_pat_suburb;
   TDBEdit *edt_pat_state;
   TDBEdit *edt_pat_pcode;
   TDBEdit *edt_pat_country;
   TDBEdit *edt_pat_phone;
   TDBMemo *mm_pat_reason;
   TPanel *pnl_pat_buttons;
   TPanel *pnl_pat;
   TDBGrid *grd_pat;
   TLabel *lbl_nof_patients;
   TSpeedButton *bbtn_pat_audit;
   TSpeedButton *bbtn_pat_edit;
   TSpeedButton *bbtn_pat_insert;
   TSpeedButton *bbtn_pat_accept;
   TSpeedButton *bbtn_pat_cancel;
   TSpeedButton *bbtn_pat_delete;
   TSpeedButton *bbtn_search_insert;
   TSpeedButton *bbtn_pat_search;
   TSpeedButton *bbtn_search_reset;
    void __fastcall grd_patTitleClick(TColumn *Column);
    void __fastcall dtpck_pat_dobChange(TObject *Sender);
    void __fastcall pgctrl_patChange(TObject *Sender);
    void __fastcall grd_patDblClick(TObject *Sender);
    void __fastcall FormShow(TObject *Sender);
    void __fastcall FormHide(TObject *Sender);
    void __fastcall mnu_sort_surname_click(TObject *Sender);
    void __fastcall mnu_sort_age_click(TObject *Sender);
    void __fastcall mnu_sort_patid_click(TObject *Sender);
    void __fastcall mnu_export_click(TObject *Sender);
    void __fastcall cmbx_pat_sexChange(TObject *Sender);
  void __fastcall mnu_sort_patnoClick(TObject *Sender);
  void __fastcall grd_patKeyPress(TObject *Sender, char &Key);
   void __fastcall spbtn_pwa_modeClick(TObject *Sender);
   void __fastcall spbtn_hrv_modeClick(TObject *Sender);
   void __fastcall spbtn_pwv_modeClick(TObject *Sender);
   void __fastcall spbtn_pwm_modeClick(TObject *Sender);
   void __fastcall edt_pat_fnameChange(TObject *Sender);
   void __fastcall edt_pat_surnameChange(TObject *Sender);
   void __fastcall edt_pat_onameChange(TObject *Sender);
   void __fastcall bbtn_doneClick(TObject *Sender);
   void __fastcall bbtn_pat_searchClick(TObject *Sender);
   void __fastcall bbtn_search_resetClick(TObject *Sender);
   void __fastcall edt_search_pidKeyPress(TObject *Sender, char &Key);
   void __fastcall edt_search_surnameKeyPress(TObject *Sender, char &Key);
   void __fastcall edt_search_fnameKeyPress(TObject *Sender, char &Key);
   void __fastcall dtpck_search_dobKeyPress(TObject *Sender, char &Key);
   void __fastcall bbtn_pat_editClick(TObject *Sender);
   void __fastcall bbtn_pat_insertClick(TObject *Sender);
   void __fastcall bbtn_pat_acceptClick(TObject *Sender);
   void __fastcall bbtn_pat_cancelClick(TObject *Sender);
   void __fastcall bbtn_pat_deleteClick(TObject *Sender);
   void __fastcall bbtn_pat_auditClick(TObject *Sender);

  
  
  
    
    
private:	// User declarations
public:		// User declarations
   bool edit_mode;
   virtual __fastcall Tfrm_patient(TComponent* Owner);
   void  __fastcall set_database_status(void);
};
extern Tfrm_patient *frm_patient;

void patient_reset_active_record(void);

bool patient_validate_record(TDataSet *tbl);

bool patient_emr_mode(TDataSet *patient_table);

#endif
