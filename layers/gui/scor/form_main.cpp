//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "form_main.h"
#include "form_about.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "TeeDraw3D"
#pragma link "TeeProcs"
#pragma resource "*.dfm"
Tfrm_main *frm_main;
//---------------------------------------------------------------------------
__fastcall Tfrm_main::Tfrm_main(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_main::Exit1Click(TObject *Sender)
{
	Close();
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_main::About1Click(TObject *Sender)
{
  frm_aboutbox = new Tfrm_aboutbox(this);
  frm_aboutbox->btn_ok->Visible = true;
  frm_aboutbox->ShowModal();
  delete frm_aboutbox;
}
//---------------------------------------------------------------------------

