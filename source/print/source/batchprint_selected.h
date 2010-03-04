//---------------------------------------------------------------------------
#ifndef batchprint_selectedH
#define batchprint_selectedH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Buttons.hpp>
#include <ComCtrls.hpp>
//---------------------------------------------------------------------------
class Tfrm_print : public TForm
{
__published:	// IDE-managed Components
    TPanel *pnl_print_all;
    TLabel *Label1;
    TLabel *lbl_period_text;
    TLabel *lbl_current_label;
    TLabel *lbl_period;
    TLabel *lbl_current;
    TProgressBar *ProgressBar1;
    TBitBtn *bbtn_cancel;
private:	// User declarations
public:		// User declarations
    __fastcall Tfrm_print(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE Tfrm_print *frm_print;
//---------------------------------------------------------------------------
#endif
