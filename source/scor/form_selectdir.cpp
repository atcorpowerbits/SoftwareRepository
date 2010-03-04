//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "form_selectdir.h"
#include "form_multdb.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

bool emma_select_dir(TComponent *owner, String select_title, AnsiString &dir)
{
  Tfrm_select_dir *frm_select_dir = new Tfrm_select_dir(owner,
                                                        select_title);
  frm_select_dir->ShowModal();
  bool ret = (frm_select_dir->ModalResult == mrYes);
  if (ret)
  {
     dir = frm_select_dir->selected_dir;
  }
  delete frm_select_dir;
  return ret;
}

__fastcall Tfrm_select_dir::Tfrm_select_dir(TComponent* Owner, String title)
  : TForm(Owner)
{
   Caption = title;
   selected_dir = "";
}

void __fastcall Tfrm_select_dir::bbtn_selectClick(TObject *Sender)
{
   selected_dir = lbl_path->Caption.UpperCase();
   ModalResult = mrYes;
}
//---------------------------------------------------------------------------
void __fastcall Tfrm_select_dir::bbtn_closeClick(TObject *Sender)
{
   selected_dir = "";
   Close();
}
//---------------------------------------------------------------------------
void __fastcall Tfrm_select_dir::FormActivate(TObject *Sender)
{
  lstbx_dir->SetFocus();
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_select_dir::cmbx_driveChange(TObject *Sender)
{
   bbtn_select->Enabled = true;
}
//---------------------------------------------------------------------------


void __fastcall Tfrm_select_dir::cmbx_driveClick(TObject *Sender)
{
   bbtn_select->Enabled = false;
}
//---------------------------------------------------------------------------


