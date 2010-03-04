//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
#include <meas/pubserv.h>
#include "form_report_pwa.h"
#include "form_change_ed.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
Tfrm_pwa_change_ed *frm_pwa_change_ed;
//---------------------------------------------------------------------------
__fastcall Tfrm_pwa_change_ed::Tfrm_pwa_change_ed(TComponent* Owner)
  : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall Tfrm_pwa_change_ed::btn_move_ed_leftClick(TObject *Sender)
{
   int EDIndex = math_TimeToIndex(frm_report_pwa->report_pwa->Periph.ED,
                 frm_report_pwa->report_pwa->Periph.ExpandFactor,
                 frm_report_pwa->report_pwa->SampleRate);
   // Decrement
   EDIndex--;
   frm_report_pwa->report_pwa->RecalculateEDDependants(EDIndex);
   frm_report_pwa->report_display_average_pulse();
   frm_report_pwa->report_display_central_params();
}
//---------------------------------------------------------------------------
void __fastcall Tfrm_pwa_change_ed::btn_move_ed_rightClick(TObject *Sender)
{
   int EDIndex = math_TimeToIndex(frm_report_pwa->report_pwa->Periph.ED,
                 frm_report_pwa->report_pwa->Periph.ExpandFactor,
                 frm_report_pwa->report_pwa->SampleRate);
   // Decrement
   EDIndex++;
   frm_report_pwa->report_pwa->RecalculateEDDependants(EDIndex);
   frm_report_pwa->report_display_average_pulse();
   frm_report_pwa->report_display_central_params();
}
//---------------------------------------------------------------------------
void __fastcall Tfrm_pwa_change_ed::btn_move_ed_cancelClick(TObject *Sender)
{
   Close();
}
//---------------------------------------------------------------------------
