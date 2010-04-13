//---------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "form_about.h"
//---------------------------------------------------------------------
#pragma resource "*.dfm"
Tfrm_aboutbox *frm_aboutbox;
//---------------------------------------------------------------------
__fastcall Tfrm_aboutbox::Tfrm_aboutbox(TComponent* AOwner)
	: TForm(AOwner)
{
}
//---------------------------------------------------------------------
void __fastcall Tfrm_aboutbox::btn_okClick(TObject *Sender)
{
  Close();
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_aboutbox::FormShow(TObject *Sender)
{
}
//---------------------------------------------------------------------------


void __fastcall Tfrm_aboutbox::btn_printClick(TObject *Sender)
{
   Print();
}
//---------------------------------------------------------------------------

