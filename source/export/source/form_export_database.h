//---------------------------------------------------------------------------

#ifndef form_export_databaseH
#define form_export_databaseH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class Tfrm_export_database : public TForm
{
__published:	// IDE-managed Components
        TPanel *pnl_select;
        TPanel *pnl_status;
        TPanel *pnl_records;
        TPanel *pnl_start;
        TPanel *pnl_end;
        TDateTimePicker *dtpk_start;
        TDateTimePicker *dtpk_end;
        TLabel *Label1;
        TLabel *Label2;
        TPanel *pnl_studies;
        TPanel *pnl_exports;
        TPanel *pnl_centre;
        TListBox *lstbx_studies;
        TListBox *lstbx_exports;
        TLabel *Label4;
        TLabel *Label5;
        TLabel *Label7;
        TLabel *lbl_total_studies;
        TSpeedButton *spbtn_add;
        TSpeedButton *spbtn_addall;
        TSpeedButton *spbtn_delete;
        TSpeedButton *spbtn_deleteall;
        TPanel *pnl_buttons;
        TStatusBar *status_bar;
        TProgressBar *progress_bar;
        TBitBtn *bbtn_cancel_export;
        TLabel *lbl_progress_text;
        TPanel *pnl_warnings;
        TMemo *memMsg;
        TLabel *Label3;
   TSpeedButton *bbtn_get_studies;
   TSpeedButton *bbtn_export_all;
   TSpeedButton *bbtn_export_selected;
   TSpeedButton *bbtn_cancel;
   TSpeedButton *BitBtn1;
        void __fastcall FormShow(TObject *Sender);
        void __fastcall dtpk_startChange(TObject *Sender);
        void __fastcall dtpk_endChange(TObject *Sender);
        void __fastcall bbtn_get_studiesClick(TObject *Sender);
        void __fastcall spbtn_addClick(TObject *Sender);
        void __fastcall spbtn_addallClick(TObject *Sender);
        void __fastcall spbtn_deleteClick(TObject *Sender);
        void __fastcall spbtn_deleteallClick(TObject *Sender);
        void __fastcall lstbx_studiesClick(TObject *Sender);
        void __fastcall lstbx_exportsClick(TObject *Sender);
        void __fastcall bbtn_export_selectedClick(TObject *Sender);
        void __fastcall bbtn_export_allClick(TObject *Sender);
        void __fastcall bbtn_cancel_exportClick(TObject *Sender);
        void __fastcall FormDestroy(TObject *Sender);
   void __fastcall BitBtn1Click(TObject *Sender);
   void __fastcall bbtn_cancelClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
        TADOQuery      *qry_date;
        TADOQuery      *qry_name;
        TStringList    *export_index;
        TStringList    *patients;
        int            *records;
        TPWA           *pwa_data;
        TADOTable      *patient_table;
        TDataSet       *pwa_table;
        TDataSet       *copy_table;
        bool           stop_export;
        __fastcall Tfrm_export_database(TComponent* Owner);
        void __fastcall Tfrm_export_database::EnableButtons();
        void __fastcall Tfrm_export_database::export_database();
};
//---------------------------------------------------------------------------
extern PACKAGE Tfrm_export_database *frm_export_database;
//---------------------------------------------------------------------------
#endif
