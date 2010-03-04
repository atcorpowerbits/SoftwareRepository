//---------------------------------------------------------------------------
#ifndef form_batchprintH
#define form_batchprintH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
#include <ToolWin.hpp>
#include <Buttons.hpp>
#include <meas\pubserv.h>
//---------------------------------------------------------------------------
class Tfrm_batchprint : public TForm
{
__published:	// IDE-managed Components
    TPanel *pnl_buttons;
    TPanel *pnl_select;
    TPanel *pnl_end;
    TLabel *Label3;
    TPanel *pnl_start;
    TLabel *Label4;
    TDateTimePicker *dtpk_start;
    TDateTimePicker *dtpk_end;
    TPanel *pnl_status;
    TPanel *pnl_records;
    TPanel *pnl_not_printed;
    TPanel *pnl_centre;
    TPanel *pnl_printed;
    TLabel *lbl_print_sel_title;
    TListBox *lstbx_out;
    TListBox *lstbx_in;
    TStatusBar *status_bar;
    TBitBtn *bbtn_cancel_print;
    TProgressBar *progress_bar;
    TSpeedButton *spbtn_add;
    TSpeedButton *spbtn_addall;
    TSpeedButton *spbtn_delete;
    TSpeedButton *spbtn_deleteall;
    TLabel *lbl_print_all_title;
    TCheckBox *chkbx_print_clinical;
    TLabel *lbl_total_studies;
    TLabel *lbl_total_studies_num;
    TLabel *lbl_progress_text;
   TSpeedButton *bbtn_get_records;
   TSpeedButton *bbtn_print_all;
   TSpeedButton *bbtn_print_selected;
   TSpeedButton *bbtn_cancel;
   TSpeedButton *SpeedButton1;
   TSpeedButton *SpeedButton2;
   TSpeedButton *SpeedButton3;
    void __fastcall FormShow(TObject *Sender);
    void __fastcall dtpk_startChange(TObject *Sender);
    void __fastcall dtpk_endChange(TObject *Sender);
    void __fastcall bbtn_get_recordsClick(TObject *Sender);
    void __fastcall bbtn_print_selectedClick(TObject *Sender);
    void __fastcall bbtn_print_allClick(TObject *Sender);
    void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
    void __fastcall bbtn_cancel_printClick(TObject *Sender);
    void __fastcall spbtn_addClick(TObject *Sender);
    void __fastcall spbtn_addallClick(TObject *Sender);
    void __fastcall spbtn_deleteClick(TObject *Sender);
    void __fastcall spbtn_deleteallClick(TObject *Sender);
    
  void __fastcall FormDestroy(TObject *Sender);
  void __fastcall lstbx_inClick(TObject *Sender);
  void __fastcall lstbx_outClick(TObject *Sender);
   void __fastcall bbtn_cancelClick(TObject *Sender);
  
private:	// User declarations
  void __fastcall EnableButtons();
public:		// User declarations
    TADOQuery         *qry_date;
    TADOQuery         *qry_name;
    TStringList    *print_index;
    TStringList    *in;
    TStringList    *out;
    int            *records;
    bool           stop_print;
    TPWA           *pwa_data;
    TPWV           *pwv_data;
    TPWM           *pwm_data;
    DBMGR_ID_TYPE  table_id;
    void __fastcall print(void);
    void __fastcall query_database();
     __fastcall Tfrm_batchprint(TComponent* Owner);
};
//---------------------------------------------------------------------------
//extern PACKAGE Tfrm_batchprint *frm_batchprint;
//---------------------------------------------------------------------------
#endif
