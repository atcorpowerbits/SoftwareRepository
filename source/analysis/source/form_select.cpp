//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
#include "form_select.h"
#include "analysis.h"
#include <meas\pubtype.h>
#include <config\pubserv.h>
#include <cfr11\pubtype.h>
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
Tfrm_select *frm_select;
//---------------------------------------------------------------------------
__fastcall Tfrm_select::Tfrm_select(TComponent* Owner, String pPatientName,
           TDataSet *pQuery, TStringList* pFullList, TStringList* pInputList, TStringList* pResultList,
           MEAS_ID_TYPE pMeasMode, int pMaxNofMeasurements, String *pPWAArtery)
  : TForm(Owner)
{
   qry_select = pQuery;
   if (qry_select->Active == false)
   {
    qry_select->Open();
   }

   FMaxNofMeasurements = pMaxNofMeasurements;
   FMeasMode = pMeasMode;

   FFullList = pFullList;

   input_list = pInputList;
   lst_in->Items->AddStrings(pInputList);

   result_list = pResultList;
   lst_out->Items->AddStrings(pResultList);

   lbl_pat->Caption = pPatientName;

   if ((FMeasMode == MEAS_PWA_ID) && pPWAArtery != NULL)
   {
     lst_artery->Clear();
     for (int i = 0; i < PWA_NOF_MEASURES - 1; i++) // Do not account AORTIC
     {
      lst_artery->Items->Add(PWAMTypeAsString[i]);
     }
     lst_artery->Items->Add("All");
     lst_artery->ItemIndex = lst_artery->Items->IndexOf(*pPWAArtery);
     FArtery = pPWAArtery;
     lst_artery->Visible = true;
     lbl_artery->Visible = true;
     lbl_pwa_artery->Visible = (lst_artery->Text == "All");
   }
   if (FMeasMode == MEAS_PWV_ID) // Only for PWV
   {
     lst_artery->Clear();
     lst_artery->Visible = false;
     lbl_artery->Visible = false;
     lbl_pwa_artery->Visible = false;
   }
   // PM V9
   // Only Radial measurements are available in Clinical mode
   if (config_get_clinical_option())
   {
     lst_artery->Clear();
     lst_artery->Visible = false;
     lbl_artery->Visible = false;
     lbl_pwa_artery->Visible = false;
   }
   lbl_pwa_artery_title->Visible = lbl_pwa_artery->Visible;
}
//---------------------------------------------------------------------------
void __fastcall Tfrm_select::FormShow(TObject *Sender)
{
  lblMax->Caption = IntToStr(FMaxNofMeasurements);
  lst_in->ItemIndex = 0;
  lst_inClick(Sender);
  EnableButtons();
  lst_in->SetFocus();
}
//---------------------------------------------------------------------------
void __fastcall Tfrm_select::lst_inClick(TObject *Sender)
{
  if (lst_in->ItemIndex < 0 || lst_in->Items->Count <= 0)
  {
    return;
  }

  // Try to find the record and display medication, notes and artery
  TLocateOptions SearchOptions;
  SearchOptions = SearchOptions<<loPartialKey;
  bool ret;
  try
  {
    TDateTime lDateTime = *((TDateTime *) (lst_in->Items->Objects[lst_in->ItemIndex]));
    ret = qry_select->Locate(MPW_DATETIME, lDateTime, SearchOptions);
  }
  catch (...)
  {
    ret = false;
  }

  if (ret)
  {
      mm_medication->Text = qry_select->FieldByName(MPW_MED)->AsString;
      mm_notes->Text = qry_select->FieldByName(MPW_NOTES)->AsString;
      if (lbl_pwa_artery->Visible)
      {
         if (lst_in->ItemIndex >= 0)
            lbl_pwa_artery->Caption = qry_select->FieldByName(MPWA_SUB_TYPE)->AsString;
         else
            lbl_pwa_artery->Caption = "";
      }
  }
  else
  {
    mm_medication->Text = "Not found";
    mm_notes->Text = "Not found";
    lbl_pwa_artery->Caption = "";
  }
  // Enable arrow button
  EnableButtons();
}
//---------------------------------------------------------------------------
void __fastcall Tfrm_select::EnableButtons()
{
  btn_delete_all->Enabled = (lst_out->Items->Count > 0);
  btn_delete->Enabled = (lst_out->SelCount > 0);
  btn_add_all->Enabled = (lst_in->Items->Count > 0 && lst_out->Items->Count < FMaxNofMeasurements);
  btn_add->Enabled = (lst_in->SelCount > 0 && lst_out->Items->Count < FMaxNofMeasurements);
  btnOk->Enabled = (lst_out->Items->Count >= 2 && lst_out->Items->Count <= FMaxNofMeasurements);
  lblAv->Caption = IntToStr(lst_in->Items->Count);
  lblSel->Caption = IntToStr(lst_out->Items->Count);
  SortList(lst_in->Items);
  SortList(lst_out->Items);
}
//---------------------------------------------------------------------------
void __fastcall Tfrm_select::btn_add_allClick(TObject *Sender)
{
  if (lst_out->Items->Count >= FMaxNofMeasurements)
  {
    btn_add_all->Enabled = false;
    return;
  }
  {
    int NofRec = FMaxNofMeasurements - lst_out->Items->Count; // Left to copy
    int lBegin = lst_in->Items->Count - NofRec;
    if (lBegin < 0) lBegin = 0;
    for (int i=lBegin; i < lst_in->Items->Count; i++)
    {
       lst_out->Items->AddObject(lst_in->Items->Strings[i], lst_in->Items->Objects[i]);
    }
    int lEnd = lst_in->Items->Count;
    for (int i=lBegin; i < lEnd; i++)
    {
       lst_in->Items->Delete(lst_in->Items->Count - 1);
    }
  }
  EnableButtons();
}
//---------------------------------------------------------------------------
void __fastcall Tfrm_select::btn_delete_allClick(TObject *Sender)
{
  lst_in->Items->AddStrings(lst_out->Items);
  lst_out->Clear();
  EnableButtons();
}
//---------------------------------------------------------------------------
void __fastcall Tfrm_select::btn_addClick(TObject *Sender)
{
  while (lst_in->SelCount > 0)
  {
    if (lst_out->Items->Count >= FMaxNofMeasurements)
    {
      break;
    }
    for (int i=0; i<lst_in->Items->Count; i++)
    {
      if (lst_in->Selected[i] && lst_out->Items->Count < FMaxNofMeasurements)
      {
        lst_out->Items->AddObject(lst_in->Items->Strings[i], lst_in->Items->Objects[i]);
        lst_in->Items->Delete(i);
      }
    }
  }
  EnableButtons();
  lst_in->ItemIndex = 0;
  lst_in->SetFocus();
}
//---------------------------------------------------------------------------
void __fastcall Tfrm_select::btn_deleteClick(TObject *Sender)
{
  while (lst_out->SelCount > 0)
  {
    for (int i=0; i<lst_out->Items->Count; i++)
    {
      if (lst_out->Selected[i])
      {
        lst_in->Items->AddObject(lst_out->Items->Strings[i], lst_out->Items->Objects[i]);
        lst_out->Items->Delete(i);
      }
    }
  }
  EnableButtons();
}
//---------------------------------------------------------------------------
void __fastcall Tfrm_select::lst_outClick(TObject *Sender)
{
  btn_delete->Enabled = (lst_out->SelCount > 0);
}
//---------------------------------------------------------------------------
void __fastcall Tfrm_select::btnOkClick(TObject *Sender)
{
  result_list->Clear();
  result_list->AddStrings(lst_out->Items);
  input_list->Clear();
  input_list->AddStrings(lst_in->Items);
  if (FMeasMode == MEAS_PWA_ID || FMeasMode == MEAS_PWM_ID)
  {
    *FArtery = lst_artery->Text;
  }
  ModalResult = mrOk;
}
//---------------------------------------------------------------------------
void __fastcall Tfrm_select::FormClose(TObject *Sender,
      TCloseAction &Action)
{
  lst_in->Clear();
  lst_out->Clear();
  lst_artery->Clear();
  mm_medication->Clear();
  mm_notes->Clear();
  Action = caFree;
}
//---------------------------------------------------------------------------
// Select artery (only for PWA)
//---------------------------------------------------------------------------
void __fastcall Tfrm_select::lst_arteryChange(TObject *Sender)
{
  if (lst_artery->Text=="")
    return;
  lbl_pwa_artery->Visible = (lst_artery->Text == "All");
  lbl_pwa_artery_title->Visible = (lst_artery->Text == "All");
  if (lbl_pwa_artery->Visible)
    lbl_pwa_artery->Caption = "";
  // Refresh queries
  lst_in->Clear();
  lst_out->Clear();
  int i = 0;
  for (qry_select->First();!qry_select->Eof; qry_select->Next())
  {
    // Ignore deleted reports
    //if (!config_get_audit_option() || qry_select->FieldByName(MPWA_AUDIT_FLAG)->AsInteger != AUDIT_DELETED)
    //{
      if ((PwaFindMeasureType(lst_artery->Text) == PWA_NOF_MEASURES)
        || (qry_select->FieldByName(MPWA_SUB_TYPE)->AsString == lst_artery->Text))
      {
         // Add Object references from the full list
         lst_in->Items->AddObject(FFullList->Strings[i], FFullList->Objects[i]);
      }
      i++;
    //}
  }
  lst_in->SetFocus();
  EnableButtons();
  lst_in->ItemIndex = 0;
  lst_inClick(Sender);
}
//---------------------------------------------------------------------------
void  __fastcall Tfrm_select::SortList(TStrings* pList)
{
  for (int i=0; i < pList->Count; i++)
  {
    for (int j=0; j < pList->Count-1; j++)
    {
      TDateTime lDate1 = *((TDateTime *) pList->Objects[j]);
      TDateTime lDate2 = *((TDateTime *) pList->Objects[j+1]);
      if (lDate2 < lDate1) pList->Exchange(j, j+1);
    }
  }
}
//---------------------------------------------------------------------------
void __fastcall Tfrm_select::btnCancelClick(TObject *Sender)
{
   ModalResult = mrCancel;
}
//---------------------------------------------------------------------------

