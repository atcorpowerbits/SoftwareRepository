//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include <dbmgr/pubserv.h>
#include <multdb/pubserv.h>
#include <meas/pubserv.h>
#include <msg/pubserv.h>
#include <patient/pubserv.h>
#include <capture/pubserv.h>
#include <config/pubserv.h>
#include <comms/pubserv.h>
#include <scor/form_main.h>
#include "form_pwm.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
Tfrm_measure_pwm *frm_measure_pwm;
TADOQuery* qry_pwm;

bool meas_pwm_initialise(void)
{
   frm_measure_pwm = NULL;
   return true;
}

//---------------------------------------------------------------------------
__fastcall Tfrm_measure_pwm::Tfrm_measure_pwm(TComponent* Owner)
  : Child_Form(Owner)
{
}

//---------------------------------------------------------------------------
void __fastcall Tfrm_measure_pwm::FormShow(TObject *Sender)
{
   TDataSource          *dsMeas;
   PATIENT_RECORD_TYPE  pat;
   double               bmi_height;
   TStringList          *port_list;
   String               port;
   
   if (pgctrl_mx_settings != NULL)
   {
      pgctrl_mx_settings->ActivePage = tbsht_session;
   }
   patient_get(&pat);
   qry_pwm = dbmgr_setup_query(DBMGR_MEASURE_PWM_SESSION_TABLE,
                               DBMGR_QUERY_KEY,
                               PATIENT_SYSTEM_ID,
                               PATIENT_STUDY_ID,
                               PATIENT_NO,
                               pat.system_id,
                               pat.study_id,
                               IntToStr(pat.number),
                               MPWM_SESSION_START);

   dsMeas = dbmgr_get_data_source(DBMGR_MEASURE_PWM_SESSION_QUERY, false);

   grdMeas->DataSource = dsMeas;
   //navMeas->DataSource = dsMeas;

   rgTRP->ItemIndex = rgTRP->Items->IndexOf("10");
   rgRGP->ItemIndex = rgRGP->Items->IndexOf("10");
   chkbx_periph->Checked = false;
   chkbx_aortic->Checked = false;
   chkbx_autoscale_trends->Checked = false;

   dblstDevice->ListSource = dbmgr_get_data_source(DBMGR_DEVICE_TABLE, false);
   dblstDevice->ListSource->DataSet->Open();


   pwm = meas_get_current_pwm();

   dsMeas->OnDataChange = record_changed;

   bbtn_capture->Enabled = true;

   if (qry_pwm->RecordCount <= 0)
   {
      // PM CR
      record_changed(Sender, NULL);
      chkbx_autoscale_trends->Checked = false;
      chkRadial->Checked = true;
      chkAortic->Checked = false;
      edtSp->Text = "";
      edtMp->Text = "";
      edtDp->Text = "";
      edtOperator->Text = "";
      edtMed->Lines->Clear();
      edtNotes->Lines->Clear();
      edtFeet->Text = "";
      edtInch->Text = "";
      edtPound->Text = "";
      edtHeight->Text = "";
      edtWeight->Text = "";
      chkCalibrated->Checked = false;
      chkCalibratedClick(Sender);
   }
   else
   {
     qry_pwm->Last();
   }
   if (edtWeight->Text.ToIntDef(-1) > 0 && edtHeight->Text.ToIntDef(-1) > 0)
   {
      bmi_height = (edtHeight->Text.ToDouble() / 100.0) * (edtHeight->Text.ToDouble() / 100.0);
      txtBmi->Caption = FormatFloat("0.##", (edtWeight->Text.ToDouble()) / bmi_height);
   }
   else
   {
      txtBmi->Caption = "";
   }

   if (config_get_system_locale() == CONFIG_DEFAULT_LOCALE)
   {
      // Hide the Imperial system
      edtFeet->Visible = false;
      edtInch->Visible = false;
      edtPound->Visible = false;
      lbl_feet->Visible = false;
      lbl_inch->Visible = false;
      lbl_pound->Visible = false;
      edtHeight->Visible = true;
      edtWeight->Visible = true;
      lbl_height->Visible = true;
      lbl_weight->Visible = true;
   }
   else if (config_get_system_locale() == CONFIG_IMPERIAL_LOCALE)
   {
      // Hide the Metric system
      edtFeet->Visible = true;
      edtInch->Visible = true;
      edtPound->Visible = true;
      lbl_feet->Visible = true;
      lbl_inch->Visible = true;
      lbl_pound->Visible = true;
      edtHeight->Visible = false;
      edtWeight->Visible = false;
      lbl_height->Visible = false;
      lbl_weight->Visible = false;
   } 

   chkCalibratedClick(Sender);

   lbl_pat->Caption = patient_get_name();

   chkbx_aix->Checked = false;

   // Detect the ports everytime the pwm form is shown
   port_list = new TStringList;
   comms_detect_ports(port_list);

   // Add the detected ports to the combobox.
   if (port_list->Count != 0)
   {
      grpbx_parameter->Enabled = true;
      for (int i = 0; i < port_list->Count; i++)
      {
         port = port_list->Strings[i];
         cmbx_comports->Items->AddObject("COM " + port, (TObject *)(COMMS_ID_TYPE)port.ToInt());
      }
   }
   else
   {
      grpbx_parameter->Enabled = false;
   }

   if (port_list != NULL)
   {
      delete port_list;
   }

   grdMeas->SetFocus();
}
//---------------------------------------------------------------------------
void __fastcall Tfrm_measure_pwm::record_changed(TObject *Sender, TField  *Field)
{
   if (pnlGrid->Visible == false)
   {
      return;
   }

   EmptyControls();
   if (pwm->PopulateSession(qry_pwm) == false)
   {
      return;
   }

   switch (pwm->MeasureType)
   {
      case PWA_RADIAL:
         chkRadial->Checked = true;
         chkAortic->Checked = false;
         break;
      case PWA_AORTIC:
         chkRadial->Checked = false;
         chkAortic->Checked = true;
         break;
   }

   chkCalibrated->Checked = (pwm->Calibrated);

   if (pwm->Dp > 0)
   {
      edtDp->Text = RoundIntToStr(pwm->Dp);
   }
   else
   {
      edtDp->Text = "";
   }
   if (pwm->Sp > 0)
   {
      edtSp->Text = RoundIntToStr(pwm->Sp);
   }
   else
   {
      edtSp->Text = "";
   }
   if (pwm->MeanP > 0)
   {
      edtMp->Text = RoundIntToStr(pwm->MeanP);
   }
   else
   {
      edtMp->Text = "";
   }

   edtMed->Text = pwm->SessionMedication;
   edtNotes->Text = pwm->SessionNotes;
   edtOperator->Text = pwm->Operator;

   dblstDevice->KeyValue = pwm->DeviceID;
   if (pwm->Calibrated)
   {
      if (pwm->DeviceID != -1)
      {
         dblstDeviceClick(Sender);
      }
   }

   if (pwm->TrendSamplePeriod > 0)
   {
      rgTSP->ItemIndex = rgTSP->Items->IndexOf(IntToStr(pwm->TrendSamplePeriod));
   }
   else
   {
      rgTSP->ItemIndex = 0;
   }

   if (pwm->Feet >= 0 && pwm->Feet != DEFAULT_VALUE)
  {
     edtFeet->Text = pwm->Feet;
  }
  else
  {
     edtFeet->Text = "";
  }

  if (pwm->Inch >= 0 && pwm->Inch != DEFAULT_VALUE)
  {
     edtInch->Text = pwm->Inch;
  }
  else
  {
     edtInch->Text = "";
  }

  if (pwm->Pound > 0 && pwm->Pound != DEFAULT_VALUE)
  {
     edtPound->Text = pwm->Pound;
  }
  else
  {
     edtPound->Text = "";
  }

   if (pwm->Height > 0 && pwm->Height != DEFAULT_VALUE)
   {
      edtHeight->Text = pwm->Height;
   }
   else
   {
      edtHeight->Text = "";
   }

   if (pwm->Weight > 0 && pwm->Weight != DEFAULT_VALUE)
   {
      edtWeight->Text = pwm->Weight;
   }
   else
   {
      edtWeight->Text = "";
   }

   if (pwm->Bmi > 0 && pwm->Bmi != DEFAULT_VALUE)
   {
      txtBmi->Caption = FormatFloat("0.##", pwm->Bmi);
   }
   else
   {
      txtBmi->Caption = "";
   }

   if (qry_pwm->RecordCount > 0)
   {
      lbl_assessments_title->Caption = " Assessment "
                                    + IntToStr(qry_pwm->RecNo) + " of "
                                    + IntToStr(qry_pwm->RecordCount);
   }
}
//---------------------------------------------------------------------------
void __fastcall Tfrm_measure_pwm::EmptyControls()
{

  chkRadial->Checked = false;
  chkAortic->Checked = false;
  chkbx_autoscale_trends->Checked = false;

  edtMed->Text = "";
  edtNotes->Text = "";
  edtOperator->Text = "";

  edtFeet->Text = "";
  edtInch->Text = "";
  edtPound->Text = "";
  edtHeight->Text = "";
  edtWeight->Text = "";
  txtBmi->Caption = "";

  dblstDevice->KeyValue = -1;
  rgTSP->ItemIndex = -1;
  edt_cal_ratio->Text = "";
  edt_cal_offset->Text = "";

  lbl_assessments_title->Caption = " Assessments";
}
//---------------------------------------------------------------------------
bool __fastcall Tfrm_measure_pwm::UpdatePwm()
{
   AnsiString device_name;
   float      cal_ratio = 1.0;
   float      cal_offset = 0.0;
   COMMS_ID_TYPE       port_id;

   port_id = config_get_comms_port();

   // Update current PWM object
   pwm->MeasureType = PWA_NOF_MEASURES;
   if (chkRadial->Checked && !chkAortic->Checked)
   {
      pwm->MeasureType = PWA_RADIAL;
   }
   else if (!chkRadial->Checked && chkAortic->Checked)
   {
      pwm->MeasureType = PWA_AORTIC;
   }
   capture_pwm_set_autoscale_trends(chkbx_autoscale_trends->Checked);
   pwm->Calibrated = chkCalibrated->Checked;
   pwm->CalibrationRatio = 1.0;
   pwm->CalibrationOffset = 0.0;

   if (edtHeight->Text == "")
  {
     pwm->Height = DEFAULT_VALUE;
  }
  else
  {
     pwm->Height = edtHeight->Text.ToIntDef(DEFAULT_VALUE);
  }

  if (edtWeight->Text == "")
  {
     pwm->Weight = DEFAULT_VALUE;
  }
  else
  {
     pwm->Weight = edtWeight->Text.ToIntDef(DEFAULT_VALUE);
  }

  if (txtBmi->Caption != "")
  {
     pwm->Bmi = txtBmi->Caption.ToDouble();
  }

   if (pnlSpDp->Visible)
   {
      pwm->Sp = edtSp->Text.ToIntDef(0);
      pwm->Dp = edtDp->Text.ToIntDef(0);
      pwm->MeanP = edtMp->Text.ToIntDef(0);
      // Validate
      if (pwm->ValidateBeforeCalculate() == false)
      {
         return false;
      }
   }
   else
   {
      pwm->Sp = 0;
      pwm->Dp = 0;
      pwm->MeanP = 0;
      // Validate Height and Weight only
      if (pwm->ValidateHtWt()==false)
      {
         return false;
      }
   }

  if (dblstDevice->Visible)
  {
    pwm->DeviceID = (int)dblstDevice->KeyValue;
    if (pwm->DeviceID == 0 || pwm->DeviceID == -1)
    {
       MsgBox_warning(LoadStr(MSG_PWM_NO_DEVICE), SWARNING);
       return false;
    }
    try
    {
       cal_ratio = dblstDevice->ListSource->DataSet->FieldByName(MPWM_DEVICE_CALIBRATION_RATIO)->AsFloat;
    }
    catch (Exception &exception)
    {
       cal_ratio = 1.0;
    }

    try
    {
       cal_offset = dblstDevice->ListSource->DataSet->FieldByName(MPWM_DEVICE_CALIBRATION_OFFSET)->AsFloat;
    }
    catch (Exception &exception)
    {
       cal_offset = 0.0;
    }

    pwm->DeviceName = dblstDevice->ListSource->DataSet->FieldByName(MPWM_DEVICE_NAME)->AsString;
    pwm->CalibrationRatio = cal_ratio;
    pwm->CalibrationOffset = cal_offset;
    pwm->Continuous = dblstDevice->ListSource->DataSet->FieldByName(MPWM_DEVICE_CONTINUOUS)->AsBoolean;
    if (edt_cal_ratio->Visible)
    {
       if (edt_cal_ratio->Text != "")
       {
          try
          {
             pwm->CalibrationRatio = StrToFloat(edt_cal_ratio->Text);
             pwm->CalibrationOffset = StrToFloat(edt_cal_offset->Text);
             if (pwm->CalibrationRatio <= 0.)
             {
                pwm->CalibrationRatio = cal_ratio;
             }
             if  (edt_cal_ratio->Enabled)
             {
                if (dblstDevice->ListSource->DataSet->Active)
                {
                   dblstDevice->ListSource->DataSet->Edit();
                   dblstDevice->ListSource->DataSet->FieldByName(MPWM_DEVICE_CALIBRATION_RATIO)->AsFloat = pwm->CalibrationRatio;
                   dblstDevice->ListSource->DataSet->FieldByName(MPWM_DEVICE_CALIBRATION_OFFSET)->AsFloat = pwm->CalibrationOffset;
                   dblstDevice->ListSource->DataSet->Post();
                }
             }
          }
          catch (EConvertError &exception)
          {
             MsgBox("Error updating Device Table with exception:\r\n" + exception.Message, SERROR, MB_ICONSTOP);
             pwm->CalibrationRatio = cal_ratio;
             pwm->CalibrationOffset = cal_offset;
          }
       }
    }
  }
  else
  {
     if (rdgrp_pwm_input->ItemIndex == 1)
     {
        pwm->DeviceID = 0;
        pwm->DeviceName = "";
        pwm->CalibrationRatio = 1;
        pwm->CalibrationOffset = 0;
        pwm->Continuous = true;
        capture_set_from_tonometer(false);
     }
     else
     {
        pwm->DeviceID = 0;
        pwm->DeviceName = "";
        pwm->CalibrationRatio = 1;
        pwm->CalibrationOffset = 0;
        pwm->Continuous = true;
        capture_set_from_tonometer(true);
     }
  }

  if (rgTSP->ItemIndex == 0) // No Trend Selection
  {
     pwm->TrendSamplePeriod = 0;
     pwm->TrendRefreshPeriod = 0;
  }
  else
  {
     pwm->TrendSamplePeriod =   rgTSP->Items->Strings[rgTSP->ItemIndex].ToIntDef(5);
     pwm->TrendRefreshPeriod = (rgTRP->ItemIndex > 0 ? rgTRP->Items->Strings[rgTRP->ItemIndex].ToIntDef(0) : 0);
  }
  pwm->ReportGenerationPeriod = (rgRGP->ItemIndex > 0 ? rgRGP->Items->Strings[rgRGP->ItemIndex].ToIntDef(0) : 0);

  pwm->AorticSendOut = chkbx_aortic->Checked;
  pwm->PeriphSendOut = chkbx_periph->Checked;
  pwm->AIxSendOut = chkbx_aix->Checked;

  // Memos
  pwm->SessionMedication = edtMed->Text;
  pwm->SessionNotes = edtNotes->Text;
  pwm->Operator = edtOperator->Text;

   if (pwm->AIxSendOut)
   {
      // Only output parameters for Radial measurements
      if (pwm->MeasureType != PWA_RADIAL)
      {
         MsgBox_show(TWARNING,
                       MSG_VALIDATION_ERROR,
                       LoadStr(MSG_PWM_OUTPUT_INVALID_ARTERY),
                       MSG_PWM_OUTPUT_INVALID_ARTERY, "");
         return false;
      }
      // Set the port to the item selected in the combobox.
      int index = cmbx_comports->ItemIndex;
      if (index != -1)
      {
         pwm->outputPort = (COMMS_ID_TYPE) cmbx_comports->Items->Objects[index];

         // Make sure the output port is not the same as the module port
         if (pwm->outputPort == port_id)
         {
            MsgBox_show(TWARNING,
                       MSG_VALIDATION_ERROR,
                       LoadStr(MSG_PWM_INVALID_OUTPUT_PORT),
                       MSG_PWM_INVALID_OUTPUT_PORT, "");
            return false;
         }
      }
      else
      {
         MsgBox_show(TWARNING,
                       MSG_VALIDATION_ERROR,
                       LoadStr(MSG_PWM_NO_OUTPUT_PORT),
                       MSG_PWM_NO_OUTPUT_PORT, "");
         return false;
      }
      // Close the comms port in case the previous comms port becomes unavailable
      comms_close(true);
   }

  if (port_id == COMMS_PORT_SIMULATE)
  {
     pwm->Simulation = true;
  }
  else
  {
     pwm->Simulation = false;
  }

  return true;
}
//---------------------------------------------------------------------------
void __fastcall Tfrm_measure_pwm::FormHide(TObject *Sender)
{
   TDataSource *dsrc_measure;
   dsrc_measure = dbmgr_get_data_source(DBMGR_MEASURE_PWM_SESSION_QUERY, false);
   if (dsrc_measure != NULL)
   {
      dsrc_measure->OnDataChange = NULL;
   }

   if (dblstDevice->ListSource != NULL)
   {
      if (dblstDevice->ListSource->DataSet != NULL)
      {
         dblstDevice->ListSource->DataSet->Close();
         dblstDevice->ListSource = NULL;
      }
   }
   if (qry_pwm != NULL)
   {
      qry_pwm->Close();
   }

   cmbx_comports->Items->Clear();
}
//---------------------------------------------------------------------------
void __fastcall Tfrm_measure_pwm::edtSpChange(TObject *Sender)
{
  if (edtSp->Text.ToIntDef(-1)==-1)
  {
    edtSp->Text = "";
  }
  else
  {
    if (edtSp->Text.ToIntDef(-1) > MAX_SP)
    {
      edtSp->Text = MAX_SP;
    }
    else
    {
      edtMp->Text = "";
    }
  }
}
//---------------------------------------------------------------------------
void __fastcall Tfrm_measure_pwm::edtMpChange(TObject *Sender)
{
  if (edtMp->Text.ToIntDef(-1)!=-1)
  {
    edtSp->Text = "";
  }
  else
  {
    edtMp->Text = "";
  }
}
//---------------------------------------------------------------------------
void __fastcall Tfrm_measure_pwm::edtDpChange(TObject *Sender)
{
  if (edtDp->Text.ToIntDef(-1)!=-1)
  {
    edtSp->Enabled = true;
    edtMp->Enabled = true;
    if (edtSp->Text.ToIntDef(-1)!=-1 && edtSp->Text.ToInt() < edtDp->Text.ToInt())
    {
      edtSp->Text = edtDp->Text;
    }
    if (edtMp->Text.ToIntDef(-1)!=-1 && edtMp->Text.ToInt() < edtDp->Text.ToInt())
    {
      edtMp->Text = edtDp->Text;
    }
  }
  else
  {
    edtDp->Text = "";
  }
}
//---------------------------------------------------------------------------
void __fastcall Tfrm_measure_pwm::chkRadialClick(TObject *Sender)
{
  if (chkRadial->Checked)
  {
    chkAortic->Checked = false;
  }
  else
  {
     if (chkAortic->Checked == false)
     {
        chkAortic->Checked = true;
     }
  }
}
//---------------------------------------------------------------------------
void __fastcall Tfrm_measure_pwm::chkAorticClick(TObject *Sender)
{
  if (chkAortic->Checked)
  {
    chkRadial->Checked = false;
  }
  else
  {
     if (chkRadial->Checked == false)
     {
        chkRadial->Checked = true;
     }
  }
}
//---------------------------------------------------------------------------
void __fastcall Tfrm_measure_pwm::FormKeyPress(TObject *Sender, char &Key)
{
   if (Key == VK_RETURN)
   {
      bbtn_captureClick(Sender);
   }
   else if (Key == VK_ESCAPE)
   {
      frm_main->spdbtn_patientClick(Sender);
   }
}
//---------------------------------------------------------------------------
void __fastcall Tfrm_measure_pwm::edtHeightChange(TObject *Sender)
{
   double bmi_height;

   if (edtHeight->Text.ToIntDef(-1)<=0)
   {
      edtHeight->Text = "";
      txtBmi->Caption = "";
   }
   else if (edtHeight->Text.ToIntDef(-1) > MAX_HEIGHT)
   {
      edtHeight->Text = MAX_HEIGHT;
   }
   if (edtWeight->Text.ToIntDef(-1) > 0 && edtHeight->Text.ToIntDef(-1) > 0)
   {
      bmi_height = (edtHeight->Text.ToDouble() / 100.0) * (edtHeight->Text.ToDouble() / 100.0);
      txtBmi->Caption = FormatFloat("0.##", edtWeight->Text.ToDouble() / bmi_height);
   }
}
//---------------------------------------------------------------------------
void __fastcall Tfrm_measure_pwm::edtWeightChange(TObject *Sender)
{
   double bmi_height;

   if (edtWeight->Text.ToIntDef(-1)<=0)
   {
      edtWeight->Text = "";
      txtBmi->Caption = "";
   }
   else if (edtWeight->Text.ToIntDef(-1) > MAX_WEIGHT)
   {
      edtWeight->Text = MAX_WEIGHT;
   }
   if (edtWeight->Text.ToIntDef(-1) > 0 && edtHeight->Text.ToIntDef(-1) > 0)
   {
      bmi_height = (edtHeight->Text.ToDouble() / 100.0) * (edtHeight->Text.ToDouble() / 100.0);
      txtBmi->Caption = FormatFloat("0.##", edtWeight->Text.ToDouble() / bmi_height);
   }
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_measure_pwm::chkCalibratedClick(TObject *Sender)
{
   lblDevice->Visible = (chkCalibrated->Checked);
   dblstDevice->Visible = (chkCalibrated->Checked);
   pnlSpDp->Visible = (!chkCalibrated->Checked);
   rdgrp_pwm_input->Visible = (!chkCalibrated->Checked);
   if (!chkCalibrated->Checked)
   {
      edt_cal_ratio->Visible = false;
      lbl_cal_ratio->Visible = false;
      lbl_cal_units->Visible = false;
      lbl_offset_units->Visible = false;
      edt_cal_offset->Visible = false;
      lbl_cal_offset->Visible = false;
   }
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_measure_pwm::dblstDeviceClick(TObject *Sender)
{
   AnsiString device_name;

   if (dblstDevice->ListSource != NULL && dblstDevice->ListSource->DataSet != NULL)
   {
      device_name = dblstDevice->ListSource->DataSet->FieldByName(MPWM_DEVICE_NAME)->AsString;
      if (device_name.AnsiPos("Custom") == 0)
      {
         edt_cal_ratio->Visible = true;
         lbl_cal_ratio->Visible = true;
         lbl_cal_units->Visible = true;
         lbl_offset_units->Visible = true;
         edt_cal_offset->Visible = true;
         lbl_cal_offset->Visible = true;
         edt_cal_ratio->Text =  FormatFloat("0.###",
                                             dblstDevice->ListSource->DataSet->FieldByName(MPWM_DEVICE_CALIBRATION_RATIO)->AsFloat);
         edt_cal_offset->Text =  FormatFloat("0.###",
                                             dblstDevice->ListSource->DataSet->FieldByName(MPWM_DEVICE_CALIBRATION_OFFSET)->AsFloat);
         edt_cal_ratio->Enabled = false;
         edt_cal_offset->Enabled = false;
      }
      else
      {
         edt_cal_ratio->Visible = true;
         lbl_cal_ratio->Visible = true;
         lbl_cal_units->Visible = true;
         lbl_offset_units->Visible = true;
         edt_cal_offset->Visible = true;
         lbl_cal_offset->Visible = true;
         edt_cal_ratio->Text =  FormatFloat("0.###",
                                             dblstDevice->ListSource->DataSet->FieldByName(MPWM_DEVICE_CALIBRATION_RATIO)->AsFloat);
         edt_cal_offset->Text =  FormatFloat("0.###",
                                             dblstDevice->ListSource->DataSet->FieldByName(MPWM_DEVICE_CALIBRATION_OFFSET)->AsFloat);
         edt_cal_ratio->Enabled = true;
         edt_cal_offset->Enabled = true;
      }
   }
}
//---------------------------------------------------------------------------
void __fastcall Tfrm_measure_pwm::edtFeetChange(TObject *Sender)
{
   if (edtFeet->Text.ToIntDef(-1) == 7)
   {
      if (edtInch->Text.ToIntDef(-1) > MAX_INCH)
      {
         edtInch->Text = MAX_INCH;
      }
   }
   if (edtFeet->Text.ToIntDef(-1) == 0)
   {
      if (edtInch->Text.ToIntDef(-1) < MIN_INCH)
      {
         edtInch->Text = MIN_INCH;
      }
   }
   if (edtFeet->Text.ToIntDef(-1)<0)
   {
      edtFeet->Text = "";
      // PM V9
      // This allows the operator to remove height and weight completely
      edtHeight->Text = "";
      txtBmi->Caption = "";
   }
   else if (edtFeet->Text.ToIntDef(-1) > MAX_FEET)
   {
      edtFeet->Text = MAX_FEET;
   }
   if (edtFeet->Text.ToIntDef(-1) >= 0 && edtInch->Text.ToIntDef(-1) >= 0)
   {
      edtHeight->Text = math_Round(CONVERT_INCH_TO_CM * (12 * edtFeet->Text.ToDouble() + edtInch->Text.ToDouble()));
   }
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_measure_pwm::edtInchChange(TObject *Sender)
{
   if (edtInch->Text.ToIntDef(-1)<0)
   {
      edtInch->Text = "";
      // PM V9
      // This allows the operator to remove height and weight completely
      edtHeight->Text = "";
      txtBmi->Caption = "";
   }
   else if (edtInch->Text.ToIntDef(-1) > 11)
   {
      edtInch->Text = 11;
   }
   if (edtFeet->Text.ToIntDef(-1) >= 0 && edtInch->Text.ToIntDef(-1) >= 0)
   {
      edtHeight->Text = math_Round(CONVERT_INCH_TO_CM * (12 * edtFeet->Text.ToDouble() + edtInch->Text.ToDouble()));
   }
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_measure_pwm::edtPoundChange(TObject *Sender)
{
   if (edtPound->Text.ToIntDef(-1)<=0)
   {
      edtPound->Text = "";
      // PM V9
      // This allows the operator to remove height and weight completely
      edtWeight->Text = "";
      txtBmi->Caption = "";
   }
   else if (edtPound->Text.ToIntDef(-1) > MAX_POUND)
   {
      edtPound->Text = MAX_POUND;
   }
   if (edtPound->Text.ToIntDef(-1) >= 0)
   {
      edtWeight->Text = math_Round(CONVERT_POUND_TO_KILO * edtPound->Text.ToDouble());
   }
}
//---------------------------------------------------------------------------



void __fastcall Tfrm_measure_pwm::bbtn_captureClick(TObject *Sender)
{
   MEAS_ID_TYPE  meas_mode;

   meas_mode = patient_get_study_mode();

   if (UpdatePwm() == false)
   {
      return;
   }

   if (capture_show_form(meas_mode) == true)
   {
      pnlGrid->Enabled = false;
      pgctrl_mx_settings->Visible = false;
      pnl_buttons->Visible = false;
      pnlWait->Visible = true;
      Screen->Cursor = crHourGlass;
      lblStatus->Caption = "Storing Trends to Database...";
      Application->ProcessMessages();
      pwm->CloseParamsFile();
      TADOTable* pTrendTable = dynamic_cast<TADOTable *> (dbmgr_get_dataset(DBMGR_MEASURE_PWM_TREND_TABLE, false));
      if (pTrendTable != NULL)
      {
         if (pwm->TrendFileToDB("Params.txt", pTrendTable) <= 0)
         {
            ShowMessage("Error storing Trend!");
            TADOTable* pSessionTable = dynamic_cast<TADOTable *> (dbmgr_get_dataset(DBMGR_MEASURE_PWM_SESSION_TABLE, false));
            pwm->DeleteSession(pSessionTable);
            Screen->Cursor = crDefault;
            pnlWait->Visible = false;
            pgctrl_mx_settings->Visible = true;
            pnl_buttons->Visible = true;
            pnlGrid->Enabled = true;
            return;
         }
      }
      else
      {
         ShowMessage("No trend table");
         Screen->Cursor = crDefault;
         pnlWait->Visible = false;
         pnlGrid->Enabled = true;
         pgctrl_mx_settings->Visible = true;
         pnl_buttons->Visible = true;
         return;
      }
      lblStatus->Caption = "Closing Session...";
      Application->ProcessMessages();
      TADOTable* pSessionTable = dynamic_cast<TADOTable *> (dbmgr_get_dataset(DBMGR_MEASURE_PWM_SESSION_TABLE, false));
      pwm->CloseSession(pSessionTable);
      patient_update_measurement_count((short)(grdMeas->DataSource->DataSet->RecordCount + 1));
      multdb_set_delete_status(false);
      Screen->Cursor = crDefault;
      pnlWait->Visible = false;
      pnlGrid->Enabled = true;
      pgctrl_mx_settings->Visible = true;
      pnl_buttons->Visible = true;
      if (grdMeas->DataSource != NULL)
      {
         grdMeas->DataSource->OnDataChange = NULL;
      }
      grdMeas->DataSource = NULL;
      //navMeas->DataSource = NULL;
      if (qry_pwm != NULL)
      {
         qry_pwm->Close();
      }
      if (grdMeas->DataSource != NULL)
      {
         grdMeas->DataSource = NULL;
      }
      /*if (navMeas->DataSource != NULL)
      {
         navMeas->DataSource = NULL;
      }*/
      frm_main->spdbtn_reportClick(Sender);
   }
   else
   {
      pwm->CloseParamsFile();
      TADOTable* pSessionTable = dynamic_cast<TADOTable *> (dbmgr_get_dataset(DBMGR_MEASURE_PWM_SESSION_TABLE, false));
      pwm->DeleteSession(pSessionTable);
      /*
      grdMeas->DataSource->DataSet->Close();
      grdMeas->DataSource->DataSet->Open();
      grdMeas->DataSource->DataSet->Last();
      */
      //SetFocus();
   }
}
//---------------------------------------------------------------------------


void __fastcall Tfrm_measure_pwm::chkbx_aixClick(TObject *Sender)
{
   // Do not allow trends or report generation when outputting parameters as it-
   // will interfere with the pulse by pulse display of the parameter
   if (chkbx_aix->Checked)
   {
      rgTSP->ItemIndex = 0;
      rgTSP->Enabled = false;
      rgTRP->ItemIndex = 0;
      rgTRP->Enabled = false;
      rgRGP->ItemIndex = 0;
      rgRGP->Enabled = false;
      cmbx_comports->ItemIndex = 0;
   }
   else
   {
      rgTSP->Enabled = true;
      rgTRP->Enabled = true;
      rgRGP->Enabled = true;
   }
}
//---------------------------------------------------------------------------

