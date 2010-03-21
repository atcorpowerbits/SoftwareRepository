//---------------------------------------------------------------------------
#include <vcl.h>

#pragma hdrstop

#include <vcl\FileCtrl.hpp>
#include <stdio.h>

#include <msg\pubserv.h>
#include <meas\pubserv.h>
#include <export\pubserv.h>
#include <patient\pubserv.h>
#include <scor\utils.h>
#include "form_export.h"
#include "jpeg.hpp"

#pragma package(smart_init)
#pragma resource "*.dfm"

const int EXPORT_MODE_ONE_MEASUREMENT = 1;
const int EXPORT_MODE_PATIENT_MEASUREMENTS = 2;
const int EXPORT_MODE_ALL_MEASUREMENTS = 3;
const int EXPORT_MODE_ONE_GRAPHIC = 4;
const int EXPORTED_FILE_RECORD_SIZE = 1024; // Approximate size of one record

const int EXPORT_MODE_PWA = 1;
const int EXPORT_MODE_PWV = 2;
String FileName;
/*
** Public Services for object
*/

bool export_all_measurements(TDataSet* pTblPWA, String pFileName, TPWA* pPwa)
{
   Tfrm_export *frmExp = new Tfrm_export(Application->MainForm, pFileName, pTblPWA, pPwa, true, true);
   frmExp->ShowModal();
   bool ret = (frmExp->ModalResult == mrYes);
   delete frmExp;
   return ret;
}

bool export_patient_measurements(TDataSet *pTblPWA, String pFileName, TPWA* pPwa)
{
   Tfrm_export *frmExp = new Tfrm_export(Application->MainForm, pFileName, pTblPWA, pPwa, true);
   frmExp->ShowModal();
   bool ret = (frmExp->ModalResult == mrYes);
   delete frmExp;
   return ret;
}

bool export_measurement(TDataSet *pTblPWA, String pFileName, TPWA *pPwa, int the_session_id)
{
   Tfrm_export *frmExp = new Tfrm_export(Application->MainForm, pFileName, pTblPWA, pPwa, the_session_id);
   frmExp->ShowModal();
   bool ret = (frmExp->ModalResult == mrYes);
   delete frmExp;
   return ret;
}

bool export_all_measurements(TDataSet* pTblPWM, String pFileName, TPWM* pPwm)
{
   Tfrm_export *frmExp = new Tfrm_export(Application->MainForm,
                                         pFileName, pTblPWM,
                                         pPwm, true, true);
   frmExp->ShowModal();
   bool ret = (frmExp->ModalResult == mrYes);
   delete frmExp;
   return ret;
}

bool export_patient_measurements(TDataSet *pTblPWM, String pFileName, TPWM* pPwm)
{
   Tfrm_export *frmExp = new Tfrm_export(Application->MainForm,
                                         pFileName,
                                         pTblPWM, pPwm, true);
   frmExp->ShowModal();
   bool ret = (frmExp->ModalResult == mrYes);
   delete frmExp;
   return ret;
}


bool export_all_measurements(TDataSet* pTblPWV, String pFileName, TPWV* pPwv)
{
   Tfrm_export *frmExp = new Tfrm_export(Application->MainForm, pFileName, pTblPWV, pPwv, true, true);
   frmExp->ShowModal();
   bool ret = (frmExp->ModalResult == mrYes);
   delete frmExp;
   return ret;
}

bool export_patient_measurements(TDataSet *pTblPWV, String pFileName, TPWV* pPwv)
{
   Tfrm_export *frmExp = new Tfrm_export(Application->MainForm, pFileName, pTblPWV, pPwv, true);
   frmExp->ShowModal();
   bool ret = (frmExp->ModalResult == mrYes);
   delete frmExp;
   return ret;
}

bool export_measurement(TDataSet *pTblPWV, String pFileName, TPWV *pPwv)
{
   Tfrm_export *frmExp = new Tfrm_export(Application->MainForm, pFileName, pTblPWV, pPwv);
   frmExp->ShowModal();
   bool ret = (frmExp->ModalResult == mrYes);
   delete frmExp;
   return ret;
}

bool export_pwm_session(TDataSet *pTblTrend, String pFileName, TPWM *pPwm)
{
   Tfrm_export *frmExp = new Tfrm_export(Application->MainForm, pFileName, pTblTrend, pPwm);
   frmExp->ShowModal();
   bool ret = (frmExp->ModalResult == mrYes);
   delete frmExp;
   return ret;
}

bool export_all_measurements(TDataSet* pTblHRV, String pFileName, THRV* pHrv)
{
   Tfrm_export *frmExp = new Tfrm_export(Application->MainForm, pFileName, pTblHRV, pHrv, true, true);
   frmExp->ShowModal();
   bool ret = (frmExp->ModalResult == mrYes);
   delete frmExp;
   return ret;
}

bool export_patient_measurements(TDataSet *pTblHRV, String pFileName, THRV* pHrv)
{
   Tfrm_export *frmExp = new Tfrm_export(Application->MainForm, pFileName, pTblHRV, pHrv, true);
   frmExp->ShowModal();
   bool ret = (frmExp->ModalResult == mrYes);
   delete frmExp;
   return ret;
}

bool export_measurement(TDataSet *pTblHRV, String pFileName, THRV *pHrv)
{
   Tfrm_export *frmExp = new Tfrm_export(Application->MainForm, pFileName, pTblHRV, pHrv);
   frmExp->ShowModal();
   bool ret = (frmExp->ModalResult == mrYes);
   delete frmExp;
   return ret;
}

bool export_graphic(Graphics::TBitmap *form_bmp, String pFileName)
{
   Tfrm_export *frmExp = new Tfrm_export(Application->MainForm, pFileName, form_bmp);
   frmExp->ShowModal();
   bool ret = (frmExp->ModalResult == mrYes);
   delete frmExp;
   return ret;
}

/*
** Code to manage the Form for the object
*/

__fastcall Tfrm_export::Tfrm_export(TComponent* Owner,
                                    String      pFileName,
                                    TDataSet    *pTblPWA,
                                    TPWA        *pPwa,
                                    int         s_id) : TForm(Owner)
{
   edtFile->Text = pFileName;
   fTblMeas = pTblPWA;
   pwa = pPwa;
   pwv = NULL;
   pwm = NULL;
   hrv = NULL;
   session_id = s_id;
   Success = false;
   ExportMode = EXPORT_MODE_ONE_MEASUREMENT;
   ActTitle = "Export Current Measurement";
}

__fastcall Tfrm_export::Tfrm_export(TComponent* Owner,
                                    String      pFileName,
                                    TDataSet    *pTblPWA,
                                    TPWA        *pPwa,
                                    bool        mode) : TForm(Owner)
{
   edtFile->Text = pFileName;
   fTblMeas = pTblPWA;
   pwa = pPwa;
   pwv = NULL;
   pwm = NULL;
   hrv = NULL;
   session_id = 0;
   Success = false;
   ExportMode = EXPORT_MODE_PATIENT_MEASUREMENTS;
   ActTitle = "Export Patient Measurements";
}

__fastcall Tfrm_export::Tfrm_export(TComponent* Owner,
                                    String      pFileName,
                                    TDataSet    *pTblPWA,
                                    TPWA        *pPwa,
                                    bool        mode,
                                    bool        pAll) : TForm(Owner)
{
   edtFile->Text = pFileName;
   fTblMeas = pTblPWA;
   pwa = pPwa;
   pwv = NULL;
   pwm = NULL;
   hrv = NULL;
   session_id = 0;
   Success = false;
   ExportMode = EXPORT_MODE_ALL_MEASUREMENTS;
   ActTitle = "Export All Measurements";
}

__fastcall Tfrm_export::Tfrm_export(TComponent* Owner,
                                    String      pFileName,
                                    TDataSet    *pTblPWM,
                                    TPWM        *pPwm,
                                    bool        mode,
                                    bool        pAll) : TForm(Owner)
{
   edtFile->Text = pFileName;
   fTblMeas = pTblPWM;
   pwa = NULL;
   pwv = NULL;
   pwm = pPwm;
   hrv = NULL;
   session_id = 0;
   Success = false;
   ExportMode = EXPORT_MODE_ALL_MEASUREMENTS;
   ActTitle = "Export All Measurements";
}

__fastcall Tfrm_export::Tfrm_export(TComponent* Owner, String pFileName,
                                    TDataSet *pTblPWV, TPWV* pPwv)
  : TForm(Owner)
{
   edtFile->Text = pFileName;
   fTblMeas = pTblPWV;
   pwa = NULL;
   pwv = pPwv;
   pwm = NULL;
   hrv = NULL;
   session_id = 0;
   Success = false;
   ExportMode = EXPORT_MODE_ONE_MEASUREMENT;
   ActTitle = "Export Current Measurement";
}

__fastcall Tfrm_export::Tfrm_export(TComponent* Owner, String pFileName, TDataSet *pTblPWV, TPWV* pPwv, bool mode)
  : TForm(Owner)
{
   edtFile->Text = pFileName;
   fTblMeas = pTblPWV;
   pwa = NULL;
   pwv = pPwv;
   pwm = NULL;
   hrv = NULL;
   session_id = 0;
   Success = false;
   ExportMode = EXPORT_MODE_PATIENT_MEASUREMENTS;
   ActTitle = "Export Patient Measurements";
}

__fastcall Tfrm_export::Tfrm_export(TComponent* Owner, String pFileName, TDataSet *pTblPWV, TPWV* pPwv, bool mode, bool pAll)
                       : TForm(Owner)
{
   edtFile->Text = pFileName;
   fTblMeas = pTblPWV;
   pwa = NULL;
   pwv = pPwv;
   pwm = NULL;
   hrv = NULL;
   session_id = 0;
   Success = false;
   ExportMode = EXPORT_MODE_ALL_MEASUREMENTS;
   ActTitle = "Export All Measurements";
}

__fastcall Tfrm_export::Tfrm_export(TComponent* Owner, String pFileName,
                                    TDataSet *pTblTrend, TPWM* pPwm)
  : TForm(Owner)
{
   edtFile->Text = pFileName;
   fTblMeas = pTblTrend;
   pwa = NULL;
   pwv = NULL;
   pwm = pPwm;
   hrv = NULL;
   session_id = 0;
   Success = false;
   ExportMode = EXPORT_MODE_ONE_MEASUREMENT;
   ActTitle = "Export Current Session";
}

__fastcall Tfrm_export::Tfrm_export(TComponent* Owner,
                                    String      pFileName,
                                    TDataSet    *pTblPWM,
                                    TPWM        *pPwm,
                                    const bool   pwa_reports)
  : TForm(Owner)
{
   edtFile->Text = pFileName;
   fTblMeas = pTblPWM;
   pwa = NULL;
   pwv = NULL;
   pwm = pPwm;
   hrv = NULL;
   session_id = 0;
   Success = false;
   ExportMode = EXPORT_MODE_PATIENT_MEASUREMENTS;
   ActTitle = "Export Patient Session Measurements";
}

__fastcall Tfrm_export::Tfrm_export(TComponent* Owner, String pFileName,
                                    TDataSet *pTblHRV, THRV* pHrv)
  : TForm(Owner)
{
   edtFile->Text = pFileName;
   fTblMeas = pTblHRV;
   pwa = NULL;
   pwv = NULL;
   pwm = NULL;
   hrv = pHrv;
   session_id = 0;
   Success = false;
   ExportMode = EXPORT_MODE_ONE_MEASUREMENT;
   ActTitle = "Export Current Measurement";
}

__fastcall Tfrm_export::Tfrm_export(TComponent* Owner, String pFileName, TDataSet *pTblHRV, THRV* pHrv, bool mode)
  : TForm(Owner)
{
   edtFile->Text = pFileName;
   fTblMeas = pTblHRV;
   pwa = NULL;
   pwv = NULL;
   pwm = NULL;
   hrv = pHrv;
   session_id = 0;
   Success = false;
   ExportMode = EXPORT_MODE_PATIENT_MEASUREMENTS;
   ActTitle = "Export Patient Measurements";
}

__fastcall Tfrm_export::Tfrm_export(TComponent* Owner, String pFileName, TDataSet *pTblHRV, THRV* pHrv, bool mode, bool pAll)
                       : TForm(Owner)
{
   edtFile->Text = pFileName;
   fTblMeas = pTblHRV;
   pwa = NULL;
   pwv = NULL;
   pwm = NULL;
   hrv = pHrv;
   session_id = 0;
   Success = false;
   ExportMode = EXPORT_MODE_ALL_MEASUREMENTS;
   ActTitle = "Export All Measurements";
}

__fastcall Tfrm_export::Tfrm_export(TComponent* Owner, String pFileName, Graphics::TBitmap *form_bmp)
                       : TForm(Owner)
{
   edtFile->Text = pFileName;
   fTblMeas = NULL;
   bmp_image = form_bmp;
   pwa = NULL;
   pwv = NULL;
   pwm = NULL;
   hrv = NULL;
   session_id = 0;
   Success = false;
   ExportMode = EXPORT_MODE_ONE_GRAPHIC;
   ActTitle = "Export Current Graphic";
}

void __fastcall Tfrm_export::FormShow(TObject *Sender)
{
  lblTitle->Caption = ActTitle;
  lblProg->Caption = "";
}

void __fastcall Tfrm_export::btnExportClick(TObject *Sender)
{
   int   lFileHandle;
   bool  ret;
   int   lExpRec = 0;
   int   lAllRec = 0;
   Success = false;

   // Check whether enough space to export
   if (ExportMode == EXPORT_MODE_ALL_MEASUREMENTS)
   {
      int nof_rec = fTblMeas->RecordCount;
      if (nof_rec > 0)
      {
        ULONG  need_size = nof_rec * EXPORTED_FILE_RECORD_SIZE;
        VLONG free_space = emma_get_disk_space((UTINY)(edtFile->Text[1]));
        if (free_space < need_size)
        {
          MsgBox(TERROR, MSG_EXPORT_ERROR, MSG_EXPORT_NO_SPACE, LoadStr(MSG_EXPORT_NO_SPACE) + RoundIntToStr(need_size));
          btnClose->Enabled = true;
          return;
        }
      }
   }

   // Check whether directory exist
   String lDir = ExtractFilePath(edtFile->Text);
   if (DirectoryExists(lDir)==false)
   {
      CreateDir(lDir);
   }

   btnClose->Enabled = false;

   // When exporting a graphic there is no need to create the file
   if (ExportMode != EXPORT_MODE_ONE_GRAPHIC)
   {
      if (FileExists(edtFile->Text))
      {
         DeleteFile(edtFile->Text);
      }
      lFileHandle = FileCreate(edtFile->Text);
      if (lFileHandle <= 0)
      {
         MsgBox(TERROR, MSG_EXPORT_ERROR, MSG_EXPORT_ERROR_FILE, LoadStr(MSG_EXPORT_ERROR_FILE) + edtFile->Text);
         btnClose->Enabled = true;
         return;
      }
   }

   // Messages
   msg_enable_messages();

   // Beginning...
   prgbar_export->Visible = true;
   btnExport->Enabled = false;
   btnSelect->Enabled = false;
   btnClose->Enabled = false;
   btnCancel->Enabled = true;
   CloseApp = false;

   Application->ProcessMessages();

   switch (ExportMode)
   {
      case EXPORT_MODE_ONE_MEASUREMENT:
         if (pwa != NULL)
         {
            if (session_id == 0)
            {
               ret = ExportOneMeasurement(pwa, lFileHandle, true);
            }
            else
            {
               /*
               ** This is a PWM export
               */
               ret = ExportOneMeasurement(pwa, lFileHandle, false);
            }
            lExpRec = 1;
            lAllRec = 1;
         }
         else if (pwv != NULL)
         {
            ret = ExportOneMeasurement(pwv, lFileHandle);
            lExpRec = 1;
            lAllRec = 1;
         }
         else if (pwm != NULL)
         {
            ret = ExportSessionTrend(lFileHandle, lExpRec, lAllRec);
         }
         else if (hrv != NULL)
         {
            ret = ExportOneMeasurement(hrv, lFileHandle);
            lExpRec = 1;
            lAllRec = 1;
         }
         break;

      case EXPORT_MODE_PATIENT_MEASUREMENTS:
         if (pwa!=NULL)
           ret = ExportPatientMeasurements(pwa, lFileHandle, lExpRec, lAllRec);
         else if (pwv!=NULL)
           ret = ExportPatientMeasurements(pwv, lFileHandle, lExpRec, lAllRec);
         else if (pwm!=NULL)
           ret = ExportPatientMeasurements(pwm, lFileHandle, lExpRec, lAllRec);
         else if (hrv!=NULL)
           ret = ExportPatientMeasurements(hrv, lFileHandle, lExpRec, lAllRec);
         break;

      case EXPORT_MODE_ALL_MEASUREMENTS:
         if (pwa!=NULL)
           ret = ExportAllMeasurements(pwa, lFileHandle, lExpRec, lAllRec);
         else if (pwv!=NULL)
           ret = ExportAllMeasurements(pwv, lFileHandle, lExpRec, lAllRec);
         else if (pwm!=NULL)
           ret = ExportAllMeasurements(pwm, lFileHandle, lExpRec, lAllRec);
         else if (hrv!=NULL)
           ret = ExportAllMeasurements(hrv, lFileHandle, lExpRec, lAllRec);
         break;

      case EXPORT_MODE_ONE_GRAPHIC:
         if (bmp_image != NULL)
         {
            ret = ExportOneGraphic(bmp_image, edtFile->Text);
            lExpRec = 1;                           
            lAllRec = 1;
         }
         break;

      default:
         break;
   }

   // Check success
   if (ret == false)
   {
      lblTitle->Caption = lblTitle->Caption + ". Failed.";
      FileClose(lFileHandle);
      btnClose->Enabled = true;
      btnSelect->Enabled = true;
      btnCancel->Enabled = false;
      btnExport->Enabled = true;
      msg_enable_messages();
      return;
   }

   // Success
   if (ExportMode != EXPORT_MODE_ONE_GRAPHIC)
   {
      FileClose(lFileHandle);
   }

   lblTitle->Caption = lblTitle->Caption +
      ".\r\nSuccessfully exported " + IntToStr(lExpRec) + " of " +
         IntToStr(lAllRec) + " records.";
   prgbar_export->Visible = false;
   lblProg->Caption = "";

   btnClose->Enabled = true;
   btnSelect->Enabled = false;
   btnCancel->Enabled = false;
   btnExport->Enabled = false;

   Success = true;
   return;
}

bool __fastcall Tfrm_export::ExportOneMeasurement(TPWA *pwa,
                                                  int   lFileHandle,
                                                  bool  is_pwa)
{
   prgbar_export->Max = 100;
   String lOut = "";

   if (pwa->ExportPrintTitle(fTblMeas, lOut) == false)
   {
      return false;
   }

   lOut = lOut + "\r\n";
   FileWrite(lFileHandle, lOut.c_str(), lOut.Length());
   prgbar_export->Position = 30;
   lblProg->Caption = "1 of 1";
   Application->ProcessMessages();

   lOut = "";
   if (is_pwa)
   {
      if (pwa->Export(lOut)== false)
      {
         return false;
      }
   }
   else
   {
      if (pwa->Export(lOut, session_id) == false)
      {
         return false;
      }
   }
   lOut = lOut + "\r\n\r\n";
   FileWrite(lFileHandle, lOut.c_str(), lOut.Length());
   prgbar_export->Position = 60;

   if (pwa->ExportArrays(lFileHandle) == false)
   {
      return false;
   }
   // lOut = lOut + "\r\n\r\n";
   // FileWrite(lFileHandle, lOut.c_str(), lOut.Length());
   prgbar_export->Position = 100;
   return true;
}

bool __fastcall Tfrm_export::ExportOneMeasurement(TPWV *pwv, int lFileHandle)
{
   prgbar_export->Max = 100;
   String lOut = "";

   if (pwv->ExportPrintTitle(fTblMeas, lOut) == false)
   {
      return false;
   }

   lOut = lOut + "\r\n";
   FileWrite(lFileHandle, lOut.c_str(), lOut.Length());
   prgbar_export->Position = 30;
   lblProg->Caption = "1 of 1";
   Application->ProcessMessages();

   lOut = "";
   if (pwv->Export(lOut)== false)
   {
      return false;
   }
   // lOut = lOut + "\r\n\r\n";
   FileWrite(lFileHandle, lOut.c_str(), lOut.Length());
   prgbar_export->Position = 60;
   if (pwv->ExportArrays(lFileHandle) == false)
   {
      return false;
   }
   // lOut = lOut + "\r\n\r\n";
   // FileWrite(lFileHandle, lOut.c_str(), lOut.Length());
   prgbar_export->Position = 100;
   return true;
}

bool __fastcall Tfrm_export::ExportOneMeasurement(THRV *hrv, int lFileHandle)
{
   prgbar_export->Max = 100;
   String lOut = "";

   if (hrv->ExportPrintTitle(fTblMeas, lOut) == false)
   {
      return false;
   }

   lOut = lOut + "\r\n";
   FileWrite(lFileHandle, lOut.c_str(), lOut.Length());
   prgbar_export->Position = 30;
   lblProg->Caption = "1 of 1";
   Application->ProcessMessages();

   lOut = "";
   if (hrv->Export(lOut)== false)
   {
      return false;
   }
   // lOut = lOut + "\r\n\r\n";
   FileWrite(lFileHandle, lOut.c_str(), lOut.Length());
   prgbar_export->Position = 60;
   if (hrv->ExportArrays(lFileHandle) == false)
   {
      return false;
   }
   // lOut = lOut + "\r\n\r\n";
   // FileWrite(lFileHandle, lOut.c_str(), lOut.Length());
   prgbar_export->Position = 100;
   return true;
}

// Export pwm session
bool __fastcall Tfrm_export::ExportSessionTrend(int lFileHandle, int &pExpRec, int &pAllRec)
{
   pAllRec = fTblMeas->RecordCount;
   prgbar_export->Max = pAllRec;
   String lOut = "";

   // Loop on session's parameters
   pExpRec = 0;
   for (fTblMeas->First(); !fTblMeas->Eof; fTblMeas->Next())
   {
      if (CloseApp == true)
      {
         return false;
      }
      lOut = "";
      prgbar_export->StepBy(1);
      lblProg->Caption = IntToStr(prgbar_export->Position) + " of " + IntToStr(pAllRec);
      Application->ProcessMessages();
      try
      {
         if (pwm->ExportParam(fTblMeas, lOut) == false)
         {
            continue;
         }
         lOut = lOut + "\r\n";
         FileWrite(lFileHandle, lOut.c_str(), lOut.Length());
         pExpRec++;
      }
      catch (Exception &exception)
      {
        continue; // If something wrong still continue
      }
   }
   return true;
}

bool __fastcall Tfrm_export::ExportPatientMeasurements(TPWA *pwa, int lFileHandle, int &pExpRec, int &pAllRec)
{
   int inc = 0;

   pAllRec = fTblMeas->RecordCount;
   prgbar_export->Max = pAllRec;
   String lOut = "";

   if (pwa->ExportPrintTitle(fTblMeas, lOut) == false)
   {
      return false;
   }

   lOut = lOut + "\r\n";
   FileWrite(lFileHandle, lOut.c_str(), lOut.Length());

   // Loop on patient's measurement
   pExpRec = 0;
   for (fTblMeas->First(); !fTblMeas->Eof; fTblMeas->Next())
   {
      if (CloseApp == true)
      {
         return false;
      }
      lOut = "";
      prgbar_export->Position = inc++;
      lblProg->Caption = IntToStr(inc) + " of " + IntToStr(pAllRec);
      Application->ProcessMessages();
      try
      {
         if (pwa->Populate(fTblMeas) == false)
         {
            continue;
         }
         if (pwa->Export(lOut) == false)
         {
            continue;
         }
         lOut = lOut + "\r\n";
         FileWrite(lFileHandle, lOut.c_str(), lOut.Length());
         pExpRec++;
      }
      catch (Exception &exception)
      {
        continue; // If something wrong still continue
      }
   }
   return true;
}

bool __fastcall Tfrm_export::ExportPatientMeasurements(TPWM *pwm, int lFileHandle, int &pExpRec, int &pAllRec)
{
   int inc = 0;

   pAllRec = fTblMeas->RecordCount;
   prgbar_export->Max = pAllRec;
   String lOut = "";

   if (pwm->ExportPrintTitle(fTblMeas, lOut) == false)
   {
      return false;
   }

   lOut = lOut + "\r\n";
   FileWrite(lFileHandle, lOut.c_str(), lOut.Length());

   // Loop on patient's measurement
   pExpRec = 0;
   for (fTblMeas->First(); !fTblMeas->Eof; fTblMeas->Next())
   {
      if (CloseApp == true)
      {
         return false;
      }
      lOut = "";
      prgbar_export->Position = inc++;
      lblProg->Caption = IntToStr(inc) + " of " + IntToStr(pAllRec);
      Application->ProcessMessages();
      try
      {
         if (pwm->Populate(fTblMeas) == false)
         {
            continue;
         }
         if (pwm->Export(lOut, pwm->Session_ID) == false)
         {
            continue;
         }
         lOut = lOut + "\r\n";
         FileWrite(lFileHandle, lOut.c_str(), lOut.Length());
         pExpRec++;
      }
      catch (Exception &exception)
      {
        continue; // If something wrong still continue
      }
   }
  return true;
}

bool __fastcall Tfrm_export::ExportPatientMeasurements(TPWV *pwv, int lFileHandle, int &pExpRec, int &pAllRec)
{
   int inc = 0;

   pAllRec = fTblMeas->RecordCount;
   prgbar_export->Max = pAllRec;
   String lOut = "";

   if (pwv->ExportPrintTitle(fTblMeas, lOut) == false)
   {
      return false;
   }

   lOut = lOut + "\r\n";
   FileWrite(lFileHandle, lOut.c_str(), lOut.Length());

   // Loop on patient's measurement
   pExpRec = 0;
   for (fTblMeas->First(); !fTblMeas->Eof; fTblMeas->Next())
   {
      if (CloseApp == true)
      {
         return false;
      }
      lOut = "";
      prgbar_export->Position = inc++;
      lblProg->Caption = IntToStr(inc) + " of " + IntToStr(pAllRec);
      Application->ProcessMessages();
      try
      {
         if (pwv->Populate(fTblMeas) == false)
         {
            continue;
         }
         if (pwv->Export(lOut) == false)
         {
            continue;
         }
         lOut = lOut + "\r\n";
         FileWrite(lFileHandle, lOut.c_str(), lOut.Length());
         pExpRec++;
      }
      catch (Exception &exception)
      {
        continue; // If something wrong still continue
      }
   }
  return true;
}

bool __fastcall Tfrm_export::ExportPatientMeasurements(THRV *hrv, int lFileHandle, int &pExpRec, int &pAllRec)
{
   int inc = 0;

   pAllRec = fTblMeas->RecordCount;
   prgbar_export->Max = pAllRec;
   String lOut = "";

   if (hrv->ExportPrintTitle(fTblMeas, lOut) == false)
   {
      return false;
   }

   lOut = lOut + "\r\n";
   FileWrite(lFileHandle, lOut.c_str(), lOut.Length());

   // Loop on patient's measurement
   pExpRec = 0;
   for (fTblMeas->First(); !fTblMeas->Eof; fTblMeas->Next())
   {
      if (CloseApp == true)
      {
         return false;
      }
      lOut = "";
      prgbar_export->Position = inc++;
      lblProg->Caption = IntToStr(inc) + " of " + IntToStr(pAllRec);
      Application->ProcessMessages();
      try
      {
         if (hrv->Populate(fTblMeas) == false)
         {
            continue;
         }
         if (hrv->Export(lOut) == false)
         {
            continue;
         }
         lOut = lOut + "\r\n";
         FileWrite(lFileHandle, lOut.c_str(), lOut.Length());
         pExpRec++;
      }
      catch (Exception &exception)
      {
        continue; // If something wrong still continue
      }
   }
  return true;
}

bool __fastcall Tfrm_export::ExportAllMeasurements(TPWA *pwa, int lFileHandle,
                                                   int &pExpRec, int &pAllRec)
{
   int inc = 0;

   pAllRec = fTblMeas->RecordCount;
   prgbar_export->Max = pAllRec;
   String lOut = "";

   if (pwa->ExportPrintTitle(fTblMeas, lOut) == false)
   {
      return false;
   }
   lOut = lOut + "\r\n";
   FileWrite(lFileHandle, lOut.c_str(), lOut.Length());

   // Loop on patient's measurement

   pExpRec = 0;
   for (fTblMeas->First(); !fTblMeas->Eof; fTblMeas->Next())
   {
      if (CloseApp == true)
      {
         return false;
      }
      lOut = "";
      prgbar_export->Position = inc++;
      lblProg->Caption = IntToStr(inc) + " of " + IntToStr(pAllRec);
      Application->ProcessMessages();
      try
      {
         /*
         ** If any of the following conditions fail the code sequence is
         ** halted and a new record is set for processing.
         */
         if (pwa->Populate(fTblMeas) == false)
         {
            continue;
         }
         if (patient_set(pwa->System_ID, pwa->Study_ID, pwa->Patient_No) == false)
         {
           continue;
         }
         if (pwa->Export(lOut) == false)
         {
            continue;
         }
         lOut = lOut + "\r\n";
         FileWrite(lFileHandle, lOut.c_str(), lOut.Length());
         pExpRec++;
      }
      catch (Exception &exception)
      {
         continue;
      }
   }
   return true;
}

bool __fastcall Tfrm_export::ExportAllMeasurements(TPWV *pwv, int lFileHandle,
                                                   int &pExpRec, int &pAllRec)
{
   int inc = 0;

   pAllRec = fTblMeas->RecordCount;
   prgbar_export->Max = pAllRec;
   String lOut = "";

   if (pwv->ExportPrintTitle(fTblMeas, lOut) == false)
   {
      return false;
   }
   lOut = lOut + "\r\n";
   FileWrite(lFileHandle, lOut.c_str(), lOut.Length());

   // Loop on patient's measurement

   pExpRec = 0;
   for (fTblMeas->First(); !fTblMeas->Eof; fTblMeas->Next())
   {
      if (CloseApp == true)
      {
         return false;
      }
      lOut = "";
      prgbar_export->Position = inc++;
      lblProg->Caption = IntToStr(inc) + " of " + IntToStr(pAllRec);
      Application->ProcessMessages();
      try
      {
         /*
         ** If any of the following conditions fail the code sequence is
         ** halted and a new record is set for processing.
         */
         if (pwv->Populate(fTblMeas) == false)
         {
            continue;
         }
         if (patient_set(pwv->System_ID, pwv->Study_ID, pwv->Patient_No) == false)
         {
           continue;
         }
         if (pwv->Export(lOut) == false)
         {
            continue;
         }
         lOut = lOut + "\r\n";
         FileWrite(lFileHandle, lOut.c_str(), lOut.Length());
         pExpRec++;
      }
      catch (Exception &exception)
      {
         continue;
      }
   }
   return true;
}

bool __fastcall Tfrm_export::ExportAllMeasurements(TPWM *pwm, int lFileHandle,
                                                   int &pExpRec, int &pAllRec)
{
   int inc = 0;

   pAllRec = fTblMeas->RecordCount;
   prgbar_export->Max = pAllRec;
   String lOut = "";

   if (pwm->ExportPrintTitle(fTblMeas, lOut) == false)
   {
      return false;
   }
   lOut = lOut + "\r\n";
   FileWrite(lFileHandle, lOut.c_str(), lOut.Length());

   // Loop on patient's measurement

   pExpRec = 0;
   for (fTblMeas->First(); !fTblMeas->Eof; fTblMeas->Next())
   {
      if (CloseApp == true)
      {
         return false;
      }
      lOut = "";
      prgbar_export->Position = inc++;
      lblProg->Caption = IntToStr(inc) + " of " + IntToStr(pAllRec);
      Application->ProcessMessages();
      try
      {
         /*
         ** If any of the following conditions fail the code sequence is
         ** halted and a new record is set for processing.
         */
         if (pwm->Populate(fTblMeas) == false)
         {
            continue;
         }
         if (patient_set(pwm->System_ID, pwm->Study_ID, pwm->Patient_No) == false)
         {
           continue;
         }
         if (pwm->Export(lOut, pwm->Session_ID) == false)
         {
            continue;
         }
         lOut = lOut + "\r\n";
         FileWrite(lFileHandle, lOut.c_str(), lOut.Length());
         pExpRec++;
      }
      catch (Exception &exception)
      {
         continue;
      }
   }
   return true;
}

bool __fastcall Tfrm_export::ExportAllMeasurements(THRV *hrv, int lFileHandle,
                                                   int &pExpRec, int &pAllRec)
{
   int inc = 0;

   pAllRec = fTblMeas->RecordCount;
   prgbar_export->Max = pAllRec;
   String lOut = "";

   if (hrv->ExportPrintTitle(fTblMeas, lOut) == false)
   {
      return false;
   }
   lOut = lOut + "\r\n";
   FileWrite(lFileHandle, lOut.c_str(), lOut.Length());

   // Loop on patient's measurement
   
   pExpRec = 0;
   for (fTblMeas->First(); !fTblMeas->Eof; fTblMeas->Next())
   {
      if (CloseApp == true)
      {
         return false;
      }
      lOut = "";
      prgbar_export->Position = inc++;
      lblProg->Caption = IntToStr(inc) + " of " + IntToStr(pAllRec);
      Application->ProcessMessages();
      try
      {
         /*
         ** If any of the following conditions fail the code sequence is
         ** halted and a new record is set for processing.
         */
         if (hrv->Populate(fTblMeas) == false)
         {
            continue;
         }
         if (patient_set(hrv->System_ID, hrv->Study_ID, hrv->Patient_No) == false)
         {
           continue;
         }
         if (hrv->Export(lOut) == false)
         {
            continue;
         }
         lOut = lOut + "\r\n";
         FileWrite(lFileHandle, lOut.c_str(), lOut.Length());
         pExpRec++;
      }
      catch (Exception &exception)
      {
         continue;
      }
   }
   return true;
}

bool __fastcall Tfrm_export::ExportOneGraphic(Graphics::TBitmap*   bmp_image,
                                                  String jpeg_file_name)
{
   bool         created = false;
   TJPEGImage*  jpg_image;

   prgbar_export->Max = 100;
   lblProg->Caption = "1 of 1";
   Application->ProcessMessages();
   jpg_image = new TJPEGImage();
   if (jpg_image)
   {
      jpg_image->CompressionQuality = 75;
      jpg_image->Performance = jpBestSpeed;
      jpg_image->PixelFormat = jf24Bit;
      jpg_image->Smoothing = false;
      jpg_image->Assign(bmp_image);
      jpg_image->SaveToFile(jpeg_file_name);
      created = true;
      delete jpg_image;
      jpg_image = (TJPEGImage *)0;
   }
   prgbar_export->Position = 100;
   return created;
}

void __fastcall Tfrm_export::btnCloseClick(TObject *Sender)
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

void __fastcall Tfrm_export::btnSelectClick(TObject *Sender)
{
   if (FileName.IsEmpty())
   {
      FileName = edtFile->Text;
   }
   else
   {
      FileName = ExtractFilePath(FileName) + ExtractFileName(edtFile->Text);
   }
   OpenDialog1->FileName = FileName;
   OpenDialog1->InitialDir = ExtractFileDir(FileName);
   if (ExportMode == EXPORT_MODE_ONE_GRAPHIC)
   {                                                                    
      OpenDialog1->Filter = "Graphic files|*.JPG|All Files|*.*";
      OpenDialog1->DefaultExt = "*.jpg";
   }
   else
   {
      OpenDialog1->Filter = "Text files|*.TXT|All Files|*.*";
      OpenDialog1->DefaultExt = "*.txt";
   }
   if (OpenDialog1->Execute())
   {
      FileName = OpenDialog1->FileName;
      edtFile->Text = FileName;
   }
}

void __fastcall Tfrm_export::btnCancelClick(TObject *Sender)
{
   CloseApp = true;
   Abort();
}
//---------------------------------------------------------------------------

