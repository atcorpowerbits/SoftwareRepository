//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include <patient/pubserv.h>
#include "form_patlist_select.h"
#include "attrib.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
Tfrm_patlist_select *frm_patlist_select;

bool first_time;
//---------------------------------------------------------------------------
__fastcall Tfrm_patlist_select::Tfrm_patlist_select(TComponent* Owner)
    : TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_patlist_select::Button1Click(TObject *Sender)
{
   Button1->Enabled = false;
   Button2->Enabled = false;
   patient_listing_preview(this, false);
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_patlist_select::Button2Click(TObject *Sender)
{
   Button1->Enabled = false;
   Button2->Enabled = false;
   patient_listing_preview(this, true);
}
//---------------------------------------------------------------------------
void __fastcall Tfrm_patlist_select::Button3Click(TObject *Sender)
{
   ModalResult = mrCancel;
}
//---------------------------------------------------------------------------
void __fastcall Tfrm_patlist_select::FormShow(TObject *Sender)
{
   Button1->Enabled = true;
   Button2->Enabled = true;
   first_time = true;
}
//---------------------------------------------------------------------------
void __fastcall Tfrm_patlist_select::FormActivate(TObject *Sender)
{
   if (first_time)
   {
      first_time = false;
   }
   else
   {
      patient_print_preview = false;
   }
}
//---------------------------------------------------------------------------
