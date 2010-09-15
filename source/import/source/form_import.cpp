//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
#include <vcl\FileCtrl.hpp>
#include <stdio.h>

#include <msg\pubserv.h>
#include <meas\pubserv.h>
#include <log\pubserv.h>
#include <scor\utils.h>
#include "form_import.h"
#include <multdb\pubserv.h>
#include <scor\form_selectdir.h>
#include <scor\form_main.h>
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
Tfrm_import *frm_import;
int GetTriggerPointsFromArray(short int* TrigPts, const int pLength,
                              const int NofPoints);
//---------------------------------------------------------------------------
const String IMPORT_FAILED = ". Failed.";
//---------------------------------------------------------------------------
const String IMPORT_DBASE_SYSTEM_ID  = "SYSTEM_ID";
const String IMPORT_DBASE_NO         = "PATIENT_NO";
const String IMPORT_DBASE_SURNAME    = "FAM_NAME";
const String IMPORT_DBASE_FIRST_NAME = "FIRST_NAME";
const String IMPORT_DBASE_OTHER_NAME = "OTHER_NAME";
const String IMPORT_DBASE_SEX        = "SEX";
const String IMPORT_DBASE_DOB        = "DOB";
const String IMPORT_DBASE_ID         = "PATIENT_ID";
const String IMPORT_DBASE_ADDRESS1   = "ADDRESS1";
const String IMPORT_DBASE_ADDRESS2   = "ADDRESS2";
const String IMPORT_DBASE_ADDRESS3   = "ADDRESS3";
const String IMPORT_DBASE_CODE       = "CODE";
const String IMPORT_DBASE_SPARE1     = "CHARSPARE1";
const String IMPORT_DBASE_SPARE2     = "CHARSPARE2";
//---------------------------------------------------------------------------
// object main function to convert Dbase into MSAccess
//---------------------------------------------------------------------------
bool import_sphygmocor_database(String DbaseDir,
     TADOTable *pTblPatAccess, TADOTable *pTblMeasAccess,
     TADOTable *pTblPWVAccess, bool pCalculate)
{
  // frm_main->sbr_main->Panels->Items[0]->Text = "Import database";
  Tfrm_import *frmImp = new Tfrm_import(Application->MainForm,
              DbaseDir, pTblPatAccess, pTblMeasAccess,
              pTblPWVAccess, pCalculate);
  frmImp->ShowModal();
  bool ret = (frmImp->ModalResult == mrYes);
  delete frmImp;
  // frm_main->sbr_main->Panels->Items[0]->Text = "";
  return ret;
}
//---------------------------------------------------------------------------
__fastcall Tfrm_import::Tfrm_import(TComponent* Owner, String DbaseDir,
                       TADOTable *pTblPatAccess, TADOTable *pTblMeasAccess,
                       TADOTable *pTblPWVAccess, bool pCalculate)
  : TForm(Owner)
{
  edtDir->Text = DbaseDir;
  tblPatAccess = pTblPatAccess;
  tblMeasAccess = pTblMeasAccess;
  tblPWVAccess = pTblPWVAccess;
  Calculate = pCalculate;
  Success = false;
  PatTitle = lblPatTitle->Caption;
  MeasTitle = lblMeasTitle->Caption;
  PWVTitle = lblPWVTitle->Caption;
}
//---------------------------------------------------------------------------
void __fastcall Tfrm_import::btnImportClick(TObject *Sender)
{
  // Initialisation
  Success = false;
  lblPatTitle->Font->Color = clGray;
  lblMeasTitle->Font->Color = clGray;
  lblPWVTitle->Font->Color = clGray;

  lblPatTitle->Caption = PatTitle;
  lblMeasTitle->Caption = MeasTitle;
  lblPWVTitle->Caption = PWVTitle;

  btnClose->Enabled = false;
  // Validate directory
  if (DirectoryExists(edtDir->Text)==false)
  {
    MsgBox(TERROR, MSG_IMPORT_ERROR, MSG_IMPORT_NO_DIR, LoadStr(MSG_IMPORT_NO_DIR) + edtDir->Text);
    btnClose->Enabled = true;
    return;
  }
  // Validate Dbase files
  String fInd = edtDir->Text + "\\" + tblMeasDbase->TableName;
  if (FileExists(fInd)==false)
  {
    MsgBox(TERROR, MSG_IMPORT_ERROR, MSG_IMPORT_NO_FILE, LoadStr(MSG_IMPORT_NO_FILE) + fInd);
    btnClose->Enabled = true;
    return;
  }
  fInd = edtDir->Text + "\\" + tblPatDbase->TableName;
  if (FileExists(fInd)==false)
  {
    MsgBox(TERROR, MSG_IMPORT_ERROR, MSG_IMPORT_NO_FILE, LoadStr(MSG_IMPORT_NO_FILE) + fInd);
    btnClose->Enabled = true;
    return;
  }
  if (tblPWVAccess!=NULL)
  {
    fInd = edtDir->Text + "\\" + tblPWVDbase->TableName;
    if (FileExists(fInd)==false)
    {
      tblPWVAccess = NULL;
    }
  }
  // Validate IndexFiles
  fInd = edtDir->Text + "\\" + tblPatDbase->IndexFiles->Strings[0];
  if (FileExists(fInd)==false)
  {
    MsgBox(TERROR, MSG_IMPORT_ERROR, MSG_IMPORT_NO_FILE, LoadStr(MSG_IMPORT_NO_FILE) + fInd);
    btnClose->Enabled = true;
    return;
  }
  fInd = edtDir->Text + "\\" + tblMeasDbase->IndexFiles->Strings[0];
  if (FileExists(fInd)==false)
  {
    MsgBox(TERROR, MSG_IMPORT_ERROR, MSG_IMPORT_NO_FILE, LoadStr(MSG_IMPORT_NO_FILE) + fInd);
    btnClose->Enabled = true;
    return;
  }

  // Check whether enough space to import
  String dbt_file = ChangeFileExt(edtDir->Text + "\\" + tblMeasDbase->TableName, ".dbt");
  ULONG  dbt_file_size = emma_get_file_size(dbt_file) * 1.10; // 10% more
  if (dbt_file_size >  0)
  {
     ULONG free_space = emma_get_disk_space((UTINY)(Application->ExeName[1]));
     if (free_space < dbt_file_size)
     {
        MsgBox(TERROR, MSG_IMPORT_ERROR, MSG_IMPORT_NO_SPACE, LoadStr(MSG_IMPORT_NO_SPACE) + IntToStr(dbt_file_size));
        btnClose->Enabled = true;
        return;
     }
  }

  chkShowMsgClick(Sender);

  // Prepare tables
  tblMeasDbase->DatabaseName = edtDir->Text;
  tblPatDbase->DatabaseName = edtDir->Text;
  tblPWVDbase->DatabaseName = edtDir->Text;

  btnCancel->Enabled = true;
  CloseApp = false;
  ProgressBar1->Brush->Color = clWhite;
  log_write("Import started at " + Now().FormatString("dd mmm yyyy, hh:nn"));

  // Copy patient DB
  if (tblPatAccess!=NULL)
  {
    lblPatTitle->Font->Color = clBlack;
    Application->ProcessMessages();
    if (RestorePat(tblPatDbase, tblPatAccess)==false)
    {
      lblPatTitle->Caption = lblPatTitle->Caption + IMPORT_FAILED;
      btnClose->Enabled = true;
      msg_enable_messages();
      msg_disable_memo();
      return;
    }
  }

  // Copy Meas DB
  if (tblMeasAccess!=NULL)
  {
    lblMeasTitle->Font->Color = clBlack;
    Application->ProcessMessages();
    if (RestoreMeas(tblMeasDbase, tblMeasAccess, Calculate)==false)
    {
      lblMeasTitle->Caption = lblMeasTitle->Caption + IMPORT_FAILED;
      btnClose->Enabled = true;
      msg_enable_messages();
      msg_disable_memo();
      return;
    }
  }

  // Copy PWV DB
  if (tblPWVAccess!=NULL)
  {
    lblPWVTitle->Font->Color = clBlack;
    Application->ProcessMessages();
    if (RestorePWV(tblPWVDbase, tblPWVAccess, Calculate)==false)
    {
      lblPWVTitle->Caption = lblPWVTitle->Caption + IMPORT_FAILED;
      btnClose->Enabled = true;
      msg_enable_messages();
      msg_disable_memo();
      return;
    }
  }
  msg_enable_messages();
  msg_disable_memo();
  Success = true;
  // Write to log
  log_write(lblPatTitle->Caption + " from " + edtDir->Text);
  if (tblMeasAccess!=NULL)
  {
    log_write(lblMeasTitle->Caption + " from " + edtDir->Text);
  }
  if (tblPWVAccess!=NULL)
  {
    log_write(lblPWVTitle->Caption + " from " + edtDir->Text);
  }
  log_write("Import ended at " + Now().FormatString("dd mmm yyyy, hh:nn"));
  btnImport->Enabled = false;
  btnCancel->Enabled = false;
  btnSave->Enabled = (memMsg->Lines->Count > 0);
  btnClose->Enabled = true;
}
//---------------------------------------------------------------------------
void __fastcall Tfrm_import::btnCloseClick(TObject *Sender)
{
   if (Success)
   {
      ModalResult = mrYes;
   }
   else
   {
      ModalResult = mrNo;
   }
}
//---------------------------------------------------------------------------
void __fastcall Tfrm_import::btnSelectClick(TObject *Sender)
{
   String dir;
   if (emma_select_dir(this, "Select ShpygmoCor directory", dir) == true)
   {
      edtDir->Text = dir;
   }
}
//---------------------------------------------------------------------------------
bool Tfrm_import::RestoreMeas(TDataSet* pTable1, TDataSet* pTable2, bool pCalculate)
{
   int NofRec = 0;
   int NofAll;
   int inc = 0;

   TPWA *pwa = meas_get_current_pwa();

   pTable1->Open();
   pTable2->Open();
   pTable2->Edit();

   NofRec = 0;
   NofAll = pTable1->RecordCount;
   ProgressBar1->Max = NofAll;
   ProgressBar1->Visible = true;

   for (pTable1->First(), pTable2->First();
        !pTable1->Eof; pTable1->Next())
   {
      if (CloseApp == true)
      {
         return false;
      }
      ProgressBar1->Position = inc++;
      lblProg->Caption = IntToStr(inc) + " of " + IntToStr(NofAll);
      Application->ProcessMessages();
      try
      {
         pTable2->Insert();
         if (pwa->PopulateDBase(pTable1)== false)
         {
            continue;
         }
         if (pCalculate)
         {
            if (pwa->Calculate() == false)
            {
               continue;
            }

            // Store with rewriting DateTime and data revision
            if (pwa->StoreAccess(pTable2, true, false) == false)
            {
               continue;
            }
         }
         else
         {
            // Store without rewriting DateTime and data revision
            if (pwa->StoreAccess(pTable2, true, false) == false)
            {
               continue;
            }
         }
         NofRec++;
      }
      catch (Exception &exception)
      {
         pTable2->Cancel();
         continue;
      }
   }
   ProgressBar1->Visible = false;
   pTable1->Close();
   pTable2->Close();
   lblMeasTitle->Caption = lblMeasTitle->Caption +
      ". Imported " + IntToStr(NofRec) + " of " +
      IntToStr(NofAll) + " records";

   return true;
}

//---------------------------------------------------------
bool Tfrm_import::RestorePat(TDataSet* pTable1, TDataSet* pTable2)
{
   int NofRec;
   int NofAll;
   int inc = 0;

   pTable1->Open();
   pTable2->Open();
   pTable2->Edit();

   NofRec = 0;
   NofAll = pTable1->RecordCount;

   ProgressBar1->Max = NofAll;
   ProgressBar1->Visible = true;

   String lStudyID = multdb_get_active_name();

   for (pTable1->First(), pTable2->First();
        !pTable1->Eof; pTable1->Next())
   {
      if (CloseApp == true)
      {
         return false;
      }
      ProgressBar1->Position = inc++;
      lblProg->Caption = IntToStr(inc) + " of " + IntToStr(NofAll);
      Application->ProcessMessages();
      try
      {
         TDateTime dob = pTable1->FieldByName(IMPORT_DBASE_DOB)->AsDateTime;
         String dob_str = dob.DateString();
         pTable2->AppendRecord(ARRAYOFCONST((
            pTable1->FieldByName(IMPORT_DBASE_SYSTEM_ID)->AsString,
            lStudyID,
            pTable1->FieldByName(IMPORT_DBASE_NO)->AsInteger,
            FormatName(pTable1->FieldByName(IMPORT_DBASE_SURNAME)->AsString),
            FormatName(pTable1->FieldByName(IMPORT_DBASE_FIRST_NAME)->AsString),
            pTable1->FieldByName(IMPORT_DBASE_OTHER_NAME)->AsString,
            pTable1->FieldByName(IMPORT_DBASE_SEX)->AsString,
            dob_str,
            //pTable1->FieldByName(IMPORT_DBASE_DOB)->AsString,
            pTable1->FieldByName(IMPORT_DBASE_ID)->AsString,
            pTable1->FieldByName(IMPORT_DBASE_CODE)->AsString,
            pTable1->FieldByName(IMPORT_DBASE_ADDRESS1)->AsString + " " +   // Street
            pTable1->FieldByName(IMPORT_DBASE_ADDRESS2)->AsString + " " +   // Town
            pTable1->FieldByName(IMPORT_DBASE_ADDRESS3)->AsString)));       // Country
         // ... Others are empty
         NofRec++;
         // pTable2->Post();
      }
      catch (Exception &exception)
      {
         if (grpMsg->Visible)
         {
            MsgStr = "Patient " + IntToStr(pTable1->FieldByName(IMPORT_DBASE_NO)->AsInteger) +
               + ", " + pTable1->FieldByName(IMPORT_DBASE_SURNAME)->AsString + " data have not been imported with error: \r\n" +
               exception.Message;
             memMsg->Lines->Add(MsgStr);
             memMsg->Lines->Add("");
         }
         pTable2->Cancel();
         continue;
      }
   }
   // Success
   ProgressBar1->Visible = false;
   pTable1->Close();
   pTable2->Close();
   lblPatTitle->Caption = lblPatTitle->Caption +
      ". Imported " + IntToStr(NofRec) + " of " +
      IntToStr(NofAll) + " records";
   return true;
}
//----------------------------------------------------------------
// Format name to make it LowerCase and First letter in Upper Case
//----------------------------------------------------------------
String Tfrm_import::FormatName(String pName)
{
  String pOut = pName.LowerCase();
  pOut[1] = *(UpperCase(pName[1]).c_str());
  return pOut;
}
//---------------------------------------------------------
bool Tfrm_import::RestorePWV(TDataSet* pTable1, TDataSet* pTable2, bool pCalculate)
{
   int NofRec = 0;
   int NofAll;
   int inc = 0;

   TPWV *pwv = meas_get_current_pwv();

   pTable1->Open();
   pTable2->Open();
   pTable2->Edit();

   NofRec = 0;
   NofAll = pTable1->RecordCount;

   ProgressBar1->Max = NofAll;
   ProgressBar1->Visible = true;

   // String lStudyID = multdb_get_active_name();

   for (pTable1->First(), pTable2->First();
        !pTable1->Eof;    pTable1->Next())
   {
      if (CloseApp == true)
      {
         return false;
      }
      ProgressBar1->Position = inc++;
      lblProg->Caption = IntToStr(inc) + " of " + IntToStr(NofAll);
      Application->ProcessMessages();
      try
      {
         pTable2->Insert();
         if (pwv->PopulateDBase(pTable1)== false)
         {
            continue;
         }
         if (pCalculate)
         {
            if (pwv->Calculate() == false)
            {
               continue;
            }

            // Store with rewriting DateTime and data revision
            if (pwv->StoreAccess(pTable2, true, false) == false)
            {
               continue;
            }
         }
         else
         {
            // Store without rewriting DateTime and data revision
            if (pwv->StoreAccess(pTable2, true, false) == false)
            {
               continue;
            }
         }

         NofRec++;
         // pTable2->Post();
      }
      catch (Exception &exception)
      {
         pTable2->Cancel();
         continue;
      }
   }
   // Success
   ProgressBar1->Visible = false;
   pTable1->Close();
   pTable2->Close();
   lblPWVTitle->Caption = lblPWVTitle->Caption +
      ". Imported " + IntToStr(NofRec) + " of " +
      IntToStr(NofAll) + " records";
   return true;
}
//---------------------------------------------------------------------------
/* ###########################################################################
 ** GetTriggerPointsFromArray
 **
 ** DESCRIPTION
 **  Get trigger points from populated TrigPts array and calculate their number
 ** INPUT
 ** OUTPUT
 ** RETURN
 **  boolean success or not
*/
//---------------------------------------------------------------------------
int GetTriggerPointsFromArray(short int* TrigPts, const int pLength,
                              const int NofPoints)
{
  // NofTPoints = 0;
  int NofTPoints = pLength;
  // Loop up to the first negative trigger point
  for (int i=0; i < pLength; i++)
  {
    if (TrigPts[i] < 0 || TrigPts[i] > NofPoints)
    {
      if (i!=0) NofTPoints = i;
      break;
    }
    else
    {
      if (i>0 && TrigPts[i] <= TrigPts[i-1])
      {
        NofTPoints = i;
        break;
      }
    }
  }
  // Validation is checked later
  return NofTPoints;
}

//---------------------------------------------------------------------------
void __fastcall Tfrm_import::btnClearClick(TObject *Sender)
{
   memMsg->Clear();
}
/*
//---------------------------------------------------------------------------
void __fastcall Tfrm_import::AddMsg(String pMsg)
{
  memMsg->Lines->Add();
  if (memMsg->Lines->Count > edtCap->Text.ToIntDef(200))
  {
    memMsg->Lines->Clear();
  }
}
*/
//---------------------------------------------------------------------------
void __fastcall Tfrm_import::chkShowMsgClick(TObject *Sender)
{
   grpMsg->Visible = chkShowMsg->Checked;
   msg_disable_messages();
   // Messages
   if (chkShowMsg->Checked)
   {
      msg_enable_memo(memMsg);
   }
   else
   {
      msg_disable_memo();
   }
   // Application->ProcessMessages();
}
//---------------------------------------------------------------------------
void __fastcall Tfrm_import::memMsgChange(TObject *Sender)
{
  const int MEMO_STRINGS_TO_CLEAR = 4;
  if (memMsg->Lines->Count > edtCap->Text.ToIntDef(200))
  {
   // memMsg->Lines->Clear();
   // Clear beginning of a memo
   for (int i=0; i < MEMO_STRINGS_TO_CLEAR; memMsg->Lines->Delete(i++));
   Application->ProcessMessages();
  }
}
//---------------------------------------------------------------------------
void __fastcall Tfrm_import::FormClose(TObject *Sender, TCloseAction &Action)
{
   msg_enable_messages();
   msg_disable_memo();
   memMsg->Lines->Clear();
   if (ModalResult == mrCancel)
   {
      Screen->Cursor = crHourGlass;
      if (tblMeasAccess!=NULL)
      {
         tblMeasAccess->Close();
         tblMeasAccess->EmptyTable();
      }
      if (tblPWVAccess!=NULL)
      {
         tblPWVAccess->Close();
         tblPWVAccess->EmptyTable();
      }
      if (tblPatAccess!=NULL)
      {
         tblPatAccess->Close();
         tblPatAccess->EmptyTable();
      }
      Screen->Cursor = crDefault;
   }
   Action = caFree;
}
//---------------------------------------------------------------------------
void __fastcall Tfrm_import::btnCancelClick(TObject *Sender)
{
  // Application->ProcessMessages();
   CloseApp = true;
   memMsg->Lines->Add("");
   memMsg->Lines->Add("Cancelled by user");
   Abort();
}
//---------------------------------------------------------------------------
void __fastcall Tfrm_import::FormShow(TObject *Sender)
{
   lblProg->Caption = "";
}
//---------------------------------------------------------------------------
void __fastcall Tfrm_import::btnSaveClick(TObject *Sender)
{
  SaveDialogMsg->InitialDir = edtDir->Text;
  if (SaveDialogMsg->Execute() == true)
  {
    memMsg->Lines->SaveToFile(SaveDialogMsg->FileName);
  }
}
//---------------------------------------------------------------------------

