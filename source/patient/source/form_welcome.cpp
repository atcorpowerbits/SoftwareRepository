//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include <patient/pubserv.h>
#include "form_welcome.h"
#include "form_main.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

void patient_show_welcome(void)
{
  Tfrm_patient_welcome *frm_pat_welcome = new Tfrm_patient_welcome(Application->MainForm);
  frm_pat_welcome->ShowModal();
  delete frm_pat_welcome;
}

//---------------------------------------------------------------------------
__fastcall Tfrm_patient_welcome::Tfrm_patient_welcome(TComponent* Owner)
  : TForm(Owner)
{
   anmt_welcome->Visible = true;
   anmt_welcome->Active = true;
}
//---------------------------------------------------------------------------
void __fastcall Tfrm_patient_welcome::btnEnterClick(TObject *Sender)
{
  Close();
}
//---------------------------------------------------------------------------
void __fastcall Tfrm_patient_welcome::btnImportClick(TObject *Sender)
{
  Close();
  Hide();
  frm_main->mnu_importClick(Sender);
}
//---------------------------------------------------------------------------

