//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "batchprint_selected.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
Tfrm_print *frm_print;
//---------------------------------------------------------------------------
__fastcall Tfrm_print::Tfrm_print(TComponent* Owner)
    : TForm(Owner)
{
}
//---------------------------------------------------------------------------
