//---------------------------------------------------------------------------
#ifndef form_multdbH
#define form_multdbH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Grids.hpp>
#include <Mask.hpp>
#include <ExtCtrls.hpp>
#include <ComCtrls.hpp>
#include <Buttons.hpp>
//---------------------------------------------------------------------------
class Tfrm_multdb : public TForm
{
__published:	// IDE-managed Components
  TPanel *pnl_buttons;
  TPanel *pnl_entry_new;
  TEdit *edt_desc;
  TPanel *pnl_grid;
  TLabel *lbl_db_title;
  TLabel *lbl_active_db;
  TLabel *lbl_name;
  TLabel *lbl_desc;
  TPanel *pnl_animate;
  TAnimate *anmt_multdb;
  TLabel *lbl_wait;
  TEdit *edt_name;
  TSpeedButton *spbtn_update_desc;
  TLabel *lbl_title_defined;
  TLabel *lbl_defined;
        TTreeView *tv_multdb;
        TLabel *Label1;
        TLabel *Label2;
        TLabel *Label3;
        TLabel *Label4;
        TLabel *Label5;
        TLabel *Label6;
        TLabel *Label7;
        TLabel *Label8;
        TLabel *Label9;
        TLabel *Label10;
        TLabel *Label11;
        TLabel *Label12;
   TSpeedButton *bbtn_new;
   TSpeedButton *bbtn_activate;
   TSpeedButton *bbtn_copy;
   TSpeedButton *bbtn_delete;
   TSpeedButton *bbtn_update;
   TSpeedButton *bbtn_multdb_abort;
   TSpeedButton *bbtn_multdb_ok;
  void __fastcall FormShow(TObject *Sender);
  void __fastcall edt_nameEnter(TObject *Sender);
  void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
  void __fastcall bbtn_multdb_okClick(TObject *Sender);
  void __fastcall bbtn_multdb_abortClick(TObject *Sender);
  void __fastcall bbtn_newClick(TObject *Sender);
  void __fastcall bbtn_activateClick(TObject *Sender);
  void __fastcall bbtn_copyClick(TObject *Sender);
  void __fastcall bbtn_updateClick(TObject *Sender);
  void __fastcall bbtn_deleteClick(TObject *Sender);

  void __fastcall spbtn_update_descClick(TObject *Sender);
  void __fastcall edt_nameChange(TObject *Sender);
  void __fastcall edt_descChange(TObject *Sender);
        void __fastcall tv_multdbClick(TObject *Sender);
        void __fastcall tv_multdbDblClick(TObject *Sender);
        void __fastcall edt_descClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
   void __fastcall multdb_update_grid(void);
  __fastcall Tfrm_multdb(TComponent* Owner);
   
};

//extern  Tfrm_multdb *frm_multdb;
//extern  AnsiString  multdb_selected_dir;

#endif
