//---------------------------------------------------------------------------
#ifndef form_mergeH
#define form_mergeH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <Db.hpp>
#include <DBTables.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
#include <ExtCtrls.hpp>
#include <ADODB.hpp>
#include <DB.hpp>
//---------------------------------------------------------------------------
class Tfrm_merge : public TForm
{
__published:	// IDE-managed Components
    TPanel *pnl_dir;
    TLabel *lbl_dir_title;
    TBitBtn *btn_select;
    TEdit *edt_source_dir;
    TPanel *pnl_buttons;
    TBitBtn *btn_merge;
    TBitBtn *btn_close;
    TPanel *Panel1;
    TLabel *lbl_pat_status;
    TLabel *lbl_pwa_status;
    TBatchMove *batch_move;
    TPanel *pnl_merge_status;
    TLabel *lbl_merge_status;
    TLabel *lbl_pwv_status;
        TADOConnection *db_merge;
        TADOTable *tbl_source_pwa;
        TADOTable *tbl_source_pat;
        TADOTable *tbl_source_pwv;
    void __fastcall btn_selectClick(TObject *Sender);
    void __fastcall btn_mergeClick(TObject *Sender);
    void __fastcall btn_closeClick(TObject *Sender);
    void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
    void __fastcall FormShow(TObject *Sender);
private:	// User declarations
    bool merge_pwa(TADOTable *tbl_source, TADOTable *tbl_dest);
    bool merge_pwv(TADOTable *tbl_source, TADOTable *tbl_dest);
    bool merge_patient(TADOTable *tbl_source, TADOTable *tbl_dest);
public:		// User declarations
    __fastcall Tfrm_merge(TComponent* Owner,
                          TADOTable      *tbl_pat,
                          TADOTable      *tbl_pwa,
                          TADOTable      *tbl_pwv);
    TADOTable *tbl_dest_pat;
    TADOTable *tbl_dest_pwa;
    TADOTable *tbl_dest_pwv;
    bool success;
};
//---------------------------------------------------------------------------
//extern PACKAGE Tfrm_merge *frm_merge;
//---------------------------------------------------------------------------
#endif
