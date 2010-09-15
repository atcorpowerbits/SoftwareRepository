//---------------------------------------------------------------------------
#include <vcl.h>
#include <dos.h>
#pragma hdrstop

#include <dbmgr/pubserv.h>
#include <log/pubserv.h>
#include <multdb/pubserv.h>
#include <meas/pubserv.h>
#include <msg/pubserv.h>
#include <patient/pubserv.h>
#include <capture/pubserv.h>
#include <config/pubserv.h>
#include <report/pubserv.h>
#include <cfr11/pubserv.h>
#include <emr/pubserv.h>
#include <scor/form_main.h>
#include "form_pwa.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
Tfrm_measure_pwa *frm_measure_pwa;
TADOQuery* qryTonom;

bool meas_pwa_initialise(void)
{
   frm_measure_pwa = new Tfrm_measure_pwa(emma_get_main_form_pointer());
   return frm_measure_pwa != NULL;
}

//---------------------------------------------------------------------------
__fastcall Tfrm_measure_pwa::Tfrm_measure_pwa(TComponent* Owner)
  : Child_Form(Owner)
{
}

//---------------------------------------------------------------------------
void __fastcall Tfrm_measure_pwa::FormShow(TObject *Sender)
{
   TDataSource          *dsMeas;
   PATIENT_RECORD_TYPE  pat;
   double               bmi_height;
   double               bmi_val;

   tmr_repeat_assessment->Enabled = false;
   if (patient_get(&pat))
   {
      qryTonom = dbmgr_setup_query(DBMGR_MEASURE_PWA_TABLE,
                                   DBMGR_QUERY_KEY,
                                   PATIENT_SYSTEM_ID,
                                   PATIENT_STUDY_ID,
                                   PATIENT_NO,
                                   pat.system_id,
                                   pat.study_id,
                                   IntToStr(pat.number),
                                   MPW_DATETIME);

      pwa_current = meas_get_current_pwa();
      dsMeas = dbmgr_get_data_source(DBMGR_MEASURE_PWA_QUERY, false);
      if ((dsMeas != NULL) && (qryTonom != NULL))
      {
         bbtn_capture->Enabled = true;
         grdMeas->DataSource = dsMeas;
         //navMeas->DataSource = dsMeas;
         dsMeas->OnDataChange = data_event.record_changed;
         qryTonom->Last();

         bbtn_capture->Enabled = true;

         if (qryTonom->RecordCount <= 0)
         {
            chkRadial->Checked = true;
            chkAortic->Checked = false;
            chkCarotid->Checked = false;
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
            edtDistance->Text = "";
            edtDistal->Text = "";
            edtProximal->Text = "";
         }
         if (edtSp->Enabled)
         {
            edtSp->SetFocus();
         }
         lbl_pat->Caption = patient_get_name();
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

         // Only display Aortic distance if AVI is enabled
         if (config_get_avi_option())
         {
            grboxDist->Visible = true;
         }
         else
         {
            grboxDist->Visible = false;
         }

         // Display study data from the EMR object - if enabled
         if (meas_pwa_emr_mode())
         {
            ;
         }

         // Disable the operator field if the Audit Trail is enabled
         if (config_get_audit_option())
         {
            edtOperator->ReadOnly = true;
         }

         // PM V9
         // Do not display Enable Output and Artery Selection options in Clinical mode
         if (config_get_clinical_option())
         {
            chkbx_pwa_loopback->Visible = false;
            chkRadial->Visible = false;
            chkCarotid->Visible = false;
            chkAortic->Visible = false;
            img_artery->Visible = false;
         }
         else
         {
            chkbx_pwa_loopback->Visible = true;
            chkRadial->Visible = true;
            chkCarotid->Visible = true;
            chkAortic->Visible = true;
            img_artery->Visible = true;
         }

         // PM V9
         // If the repeat assessment flag is set, enable the repeat timer
         if (report_pwa_repeat_assessment())
         {
            tmr_repeat_assessment->Enabled = true;
         }
      }
      else
      {
         log_write("PWA Query failed initialisation.");
      }
   }
}
//---------------------------------------------------------------------------
void __fastcall Tfrm_measure_pwa::Meas_Data_Event_Class::record_changed(TObject *Sender, TField  *Field)
{
  if (frm_measure_pwa->pnlGrid->Visible == false) return;

  if (frm_measure_pwa->pwa_current->Populate(qryTonom)==false)
  {
    frm_measure_pwa->EmptyControls();
    return;
  }

  switch (frm_measure_pwa->pwa_current->MeasureType)
  {
     case PWA_RADIAL:
      frm_measure_pwa->chkRadial->Checked = true;
      frm_measure_pwa->chkAortic->Checked = false;
      frm_measure_pwa->chkCarotid->Checked = false;
      break;
     case PWA_CAROTID:
      frm_measure_pwa->chkRadial->Checked = false;
      frm_measure_pwa->chkAortic->Checked = false;
      frm_measure_pwa->chkCarotid->Checked = true;
      break;
     case PWA_AORTIC:
      frm_measure_pwa->chkRadial->Checked = false;
      frm_measure_pwa->chkAortic->Checked = true;
      frm_measure_pwa->chkCarotid->Checked = false;
      break;
  }

  if (frm_measure_pwa->pwa_current->Dp > 0)
    frm_measure_pwa->edtDp->Text = RoundIntToStr(frm_measure_pwa->pwa_current->Dp);
  if (frm_measure_pwa->pwa_current->Sp > 0)
    frm_measure_pwa->edtSp->Text = RoundIntToStr(frm_measure_pwa->pwa_current->Sp);
  if (frm_measure_pwa->pwa_current->MeanP > 0)
    frm_measure_pwa->edtMp->Text = RoundIntToStr(frm_measure_pwa->pwa_current->MeanP);

  frm_measure_pwa->edtMed->Text = frm_measure_pwa->pwa_current->Medication;
  frm_measure_pwa->edtNotes->Text = frm_measure_pwa->pwa_current->Notes;
  frm_measure_pwa->edtOperator->Text = frm_measure_pwa->pwa_current->Operator;

  if (frm_measure_pwa->pwa_current->Feet >= 0 && frm_measure_pwa->pwa_current->Feet != DEFAULT_VALUE)
  {
     frm_measure_pwa->edtFeet->Text = frm_measure_pwa->pwa_current->Feet;
  }
  else
  {
     frm_measure_pwa->edtFeet->Text = "";
  }

  if (frm_measure_pwa->pwa_current->Inch >= 0 && frm_measure_pwa->pwa_current->Inch != DEFAULT_VALUE)
  {
     frm_measure_pwa->edtInch->Text = frm_measure_pwa->pwa_current->Inch;
  }
  else
  {
     frm_measure_pwa->edtInch->Text = "";
  }

  if (frm_measure_pwa->pwa_current->Pound > 0 && frm_measure_pwa->pwa_current->Pound != DEFAULT_VALUE)
  {
     frm_measure_pwa->edtPound->Text = frm_measure_pwa->pwa_current->Pound;
  }
  else
  {
     frm_measure_pwa->edtPound->Text = "";
  }

  if (frm_measure_pwa->pwa_current->Height > 0 && frm_measure_pwa->pwa_current->Height != DEFAULT_VALUE)
  {
     frm_measure_pwa->edtHeight->Text = frm_measure_pwa->pwa_current->Height;
  }
  else
  {
     frm_measure_pwa->edtHeight->Text = "";
  }

  if (frm_measure_pwa->pwa_current->Weight > 0 && frm_measure_pwa->pwa_current->Weight != DEFAULT_VALUE)
  {
     frm_measure_pwa->edtWeight->Text = frm_measure_pwa->pwa_current->Weight;
  }
  else
  {
     frm_measure_pwa->edtWeight->Text = "";
  }

  if (frm_measure_pwa->pwa_current->Bmi > 0 && frm_measure_pwa->pwa_current->Bmi != DEFAULT_VALUE)
  {
     // Set bmi captions and colours
     frm_measure_pwa->txtBmi->Caption = FormatFloat("0.##", frm_measure_pwa->pwa_current->Bmi);
  }
  else
  {
     frm_measure_pwa->txtBmi->Caption = "";
  }

  if (frm_measure_pwa->pwa_current->avi->Aortic_Distance > 0 && frm_measure_pwa->pwa_current->avi->Aortic_Distance != DEFAULT_VALUE)
  {
      frm_measure_pwa->edtDistance->Text = RoundIntToStr(frm_measure_pwa->pwa_current->avi->Aortic_Distance);
  }
  else
  {
    frm_measure_pwa->edtDistance->Text = "";
  }
  frm_measure_pwa->edtProximal->Text = "";
  frm_measure_pwa->edtDistal->Text = "";

  frm_measure_pwa->lbl_assessments_title->Caption = " Assessment "
                                                      + IntToStr(qryTonom->RecNo) + " of "
                                                      + IntToStr(qryTonom->RecordCount);

}
//---------------------------------------------------------------------------
void __fastcall Tfrm_measure_pwa::EmptyControls()
{
  lbl_pat->Caption = "";

  chkRadial->Checked = false;
  chkAortic->Checked = false;
  chkCarotid->Checked = false;

  edtMed->Text = "";
  edtNotes->Text = "";
  edtOperator->Text = "";

  edtFeet->Text = "";
  edtInch->Text = "";
  edtPound->Text = "";
  edtHeight->Text = "";
  edtWeight->Text = "";
  txtBmi->Caption = "";
  chkbx_pwa_loopback->Checked = false;

  edtDistance->Text = "";
  edtDistal->Text = "";
  edtProximal->Text = "";

  lbl_assessments_title->Caption = " Assessments";
}
//---------------------------------------------------------------------------
bool __fastcall Tfrm_measure_pwa::UpdatePwa()
{
  COMMS_ID_TYPE       port_id;

  port_id = config_get_comms_port();

  // Update current PWA object
  if (config_get_clinical_option())
  {
      pwa_current->MeasureType = PWA_RADIAL;
  }
  else if (chkRadial->Checked)
  {
     pwa_current->MeasureType = PWA_RADIAL;
  }
  else if (chkCarotid->Checked)
  {
     pwa_current->MeasureType = PWA_CAROTID;
  }
  else if (chkAortic->Checked)
  {
     pwa_current->MeasureType = PWA_AORTIC;
  }
  else
  {
     pwa_current->MeasureType =  PWA_NOF_MEASURES;
  }

  pwa_current->Sp = edtSp->Text.ToIntDef(0);
  pwa_current->Dp = edtDp->Text.ToIntDef(0);
  pwa_current->MeanP = edtMp->Text.ToIntDef(0);

  // Memos
  pwa_current->Medication = edtMed->Text;
  pwa_current->Notes = edtNotes->Text;
  if (config_get_audit_option())
  {
      pwa_current->Operator = security_get_username();
  }
  else
  {
      pwa_current->Operator = edtOperator->Text;
  }
  pwa_current->Interpretation = "";
  if (edtHeight->Text == "")
  {
     pwa_current->Height = DEFAULT_VALUE;
  }
  else
  {
     pwa_current->Height = edtHeight->Text.ToIntDef(DEFAULT_VALUE);
  }

  if (edtWeight->Text == "")
  {
     pwa_current->Weight = DEFAULT_VALUE;
  }
  else
  {
     pwa_current->Weight = edtWeight->Text.ToIntDef(DEFAULT_VALUE);
  }

  if (txtBmi->Caption != "")
  {
     pwa_current->Bmi = txtBmi->Caption.ToDouble();
  }

  if (edtDistance->Text == "")
  {
     pwa_current->avi->Aortic_Distance = DEFAULT_VALUE;
  }
  else
  {
     pwa_current->avi->Aortic_Distance = edtDistance->Text.ToIntDef(DEFAULT_VALUE);
  }

  if (port_id == COMMS_PORT_SIMULATE)
  {
     pwa_current->Simulation = true;
  }
  else
  {
     pwa_current->Simulation = false;
  }

  pwa_current->Tonometer = config_get_tonometer();

  // Update audit object
  pwa_current->AuditFlag = AUDIT_ORIGINAL;
  pwa_current->Reason = "";
  
  // Validate
  if (pwa_current->ValidateBeforeCalculate()==false)
    return false;

  // If the audit option is set, a tonometer serial number must be entered
  // Otherwise display a warning and call the configuration form
  if (config_get_audit_option())
  {
      if(pwa_current->Tonometer == CONFIG_DEFAULT_TONOMETER)
      {
         MsgBox_show(TWARNING,
                    MSG_VALIDATION_ERROR,
                    LoadStr(MSG_SECURITY_TONOMETER),
                    MSG_SECURITY_TONOMETER, "");
         config_show();
         return false;
      }
  }
  
  capture_set_loopback(chkbx_pwa_loopback->Checked);
  return true;
}
//---------------------------------------------------------------------------
void __fastcall Tfrm_measure_pwa::FormHide(TObject *Sender)
{
   TDataSource *dsrc_measure;

   dsrc_measure = dbmgr_get_data_source(DBMGR_MEASURE_PWA_QUERY, false);
   if (dsrc_measure != NULL)
   {
      dsrc_measure->OnDataChange = NULL;
   }

   if (qryTonom != NULL)
   {
      qryTonom->Close();
   }
}
//---------------------------------------------------------------------------
void __fastcall Tfrm_measure_pwa::edtSpChange(TObject *Sender)
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
void __fastcall Tfrm_measure_pwa::edtMpChange(TObject *Sender)
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
void __fastcall Tfrm_measure_pwa::edtDpChange(TObject *Sender)
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
void __fastcall Tfrm_measure_pwa::chkRadialClick(TObject *Sender)
{
   if (chkRadial->Checked)
   {
      chkAortic->Checked = false;
      chkCarotid->Checked = false;
   }
   else
   {
      if (chkAortic->Checked == false && chkCarotid->Checked == false)
      {
         chkCarotid->Checked = true;
      }
   }
}
//---------------------------------------------------------------------------
void __fastcall Tfrm_measure_pwa::chkAorticClick(TObject *Sender)
{
  if (chkAortic->Checked)
  {
    chkRadial->Checked = false;
    chkCarotid->Checked = false;
  }
  else
  {
    if (chkCarotid->Checked == false && chkRadial->Checked == false)
    {
       chkRadial->Checked = true;
    }
  }
}
//---------------------------------------------------------------------------
void __fastcall Tfrm_measure_pwa::chkCarotidClick(TObject *Sender)
{
  if (chkCarotid->Checked)
  {
    chkAortic->Checked = false;
    chkRadial->Checked = false;
  }
  else
  {
    if (chkAortic->Checked == false && chkRadial->Checked == false)
    {
       chkRadial->Checked = true;
    }
  }
}
//---------------------------------------------------------------------------
void __fastcall Tfrm_measure_pwa::FormKeyPress(TObject *Sender, char &Key)
{
   if (Key == VK_RETURN)
   {
      if (bbtn_capture->Enabled)
      {
         bbtn_capture->Enabled = false;
         bbtn_captureClick(Sender);
      }
   }
   else if (Key == VK_ESCAPE)
   {
      frm_main->spdbtn_patientClick(Sender);
   }
}
//---------------------------------------------------------------------------
void __fastcall Tfrm_measure_pwa::edtHeightChange(TObject *Sender)
{
   double bmi_height;
   double bmi;

   if (edtHeight->Text.ToIntDef(-1) <= 0)
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
      // Set bmi captions and colours
      bmi_height = (edtHeight->Text.ToDouble() / 100.0) * (edtHeight->Text.ToDouble() / 100.0);
      bmi = edtWeight->Text.ToDouble() / bmi_height;
      txtBmi->Caption = FormatFloat("0.##", bmi);
   }
}
//---------------------------------------------------------------------------
void __fastcall Tfrm_measure_pwa::edtWeightChange(TObject *Sender)
{
   double bmi_height;
   double bmi;

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
      // Set bmi captions and colours
      bmi_height = (edtHeight->Text.ToDouble() / 100.0) * (edtHeight->Text.ToDouble() / 100.0);
      bmi = edtWeight->Text.ToDouble() / bmi_height;
      txtBmi->Caption = FormatFloat("0.##", bmi);
   }
}
//---------------------------------------------------------------------------
void __fastcall Tfrm_measure_pwa::edtPoundChange(TObject *Sender)
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

void __fastcall Tfrm_measure_pwa::edtFeetChange(TObject *Sender)
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

void __fastcall Tfrm_measure_pwa::edtInchChange(TObject *Sender)
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

void __fastcall Tfrm_measure_pwa::edtDistanceChange(TObject *Sender)
{
  if (edtDistance->Text.ToIntDef(-1)==-1)
  {
    edtDistance->Text = "";
  }
  else
  {
    if (edtDistance->Text.ToIntDef(-1) > MAX_DISTANCE)
    {
      edtDistance->Text = MAX_DISTANCE;
    }
  }   
}
//---------------------------------------------------------------------------


void __fastcall Tfrm_measure_pwa::edtDistalChange(TObject *Sender)
{
  if (edtDistal->Text.ToIntDef(-1)!=-1)
  {
    CalcDistance();
  }
  else
  {
    edtDistal->Text = "";
  }   
}
//---------------------------------------------------------------------------


void __fastcall Tfrm_measure_pwa::edtProximalChange(TObject *Sender)
{
  if (edtProximal->Text.ToIntDef(-1)!=-1)
  {
    CalcDistance();
  }
  else
  {
    edtProximal->Text = "";
  }   
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_measure_pwa::CalcDistance()
{
  if (edtDistal->Text.ToIntDef(-1) > 0 && edtProximal->Text.ToIntDef(-1) > 0)
  {
    int lDist = edtDistal->Text.ToInt() - edtProximal->Text.ToInt();
    if (lDist >= MIN_DISTANCE && lDist <= MAX_DISTANCE)
      edtDistance->Text = IntToStr(lDist);
    else
      edtDistance->Text = "";
  }
  else
    edtDistance->Text = "";
}

// PM V9
/* ###########################################################################
 ** meas_pwa_emr_mode()
 **
 ** DESCRIPTION
 **  Displays the study data specified by the EMR object
 ** INPUT
 **  Measure PWA Form
 ** OUTPUT
 **  None
 ** RETURN
 **  Boolean - success or not
*/
//---------------------------------------------------------------------------
bool meas_pwa_emr_mode(void)
{
   EMR_RECORD_TYPE      emr;
   bool                 success = false;

   // Enable all the data entry fields
   frm_measure_pwa->chkRadial->Enabled = true;
   frm_measure_pwa->chkAortic->Enabled = true;
   frm_measure_pwa->chkCarotid->Enabled = true;
   frm_measure_pwa->edtDp->ReadOnly = false;
   frm_measure_pwa->edtSp->ReadOnly = false;
   frm_measure_pwa->edtMp->ReadOnly = false;
   frm_measure_pwa->edtMed->ReadOnly = false;
   frm_measure_pwa->edtNotes->ReadOnly = false;
   frm_measure_pwa->edtOperator->ReadOnly = false;
   frm_measure_pwa->edtFeet->ReadOnly = false;
   frm_measure_pwa->edtInch->ReadOnly = false;
   frm_measure_pwa->edtPound->ReadOnly = false;
   frm_measure_pwa->edtHeight->ReadOnly = false;
   frm_measure_pwa->edtWeight->ReadOnly = false;

   // Populate the study fields if the EMR patient is active
   if (emr_patient_is_active())
   {
      if (emr_get(&emr))
      {
         // If editing is not allowed, only Radial measurements can be performed
         // and any fields that are populated cannot be edited
         if (!emr_get_editing())
         {
            frm_measure_pwa->chkRadial->Checked = true;
            frm_measure_pwa->chkAortic->Checked = false;
            frm_measure_pwa->chkCarotid->Checked = false;

            frm_measure_pwa->chkRadial->Enabled = false;
            frm_measure_pwa->chkAortic->Enabled = false;
            frm_measure_pwa->chkCarotid->Enabled = false;
         }

         if (emr.dp != DEFAULT_VALUE)
         {
            frm_measure_pwa->edtDp->Text = IntToStr(emr.dp);
            if (!emr_get_editing())
            {
               // If DP has a value, then MP or SP will also have a value
               frm_measure_pwa->edtDp->ReadOnly = true;
               frm_measure_pwa->edtSp->ReadOnly = true;
               frm_measure_pwa->edtMp->ReadOnly = true;
            }
         }
         if (emr.sp != DEFAULT_VALUE)
         {
            frm_measure_pwa->edtSp->Text = IntToStr(emr.sp);
         }
         if (emr.mp != DEFAULT_VALUE)
         {
            frm_measure_pwa->edtMp->Text = IntToStr(emr.mp);
         }

         if (emr.medication != "")
         {
            frm_measure_pwa->edtMed->Text = emr.medication;
            if (!emr_get_editing())
            {
               frm_measure_pwa->edtMed->ReadOnly = true;
            }
         }
         if (emr.study_notes != "")
         {
            frm_measure_pwa->edtNotes->Text = emr.study_notes;
            if (!emr_get_editing())
            {
               frm_measure_pwa->edtNotes->ReadOnly = true;
            }
         }
         if (emr.operator_name != "")
         {
            frm_measure_pwa->edtOperator->Text = emr.operator_name;
            if (!emr_get_editing())
            {
               frm_measure_pwa->edtOperator->ReadOnly = true;
            }
         }

         // When the imperial values are populated, they automatically calculate
         // the nearest metric equivalent. So for accuracy, make sure the metric
         // values are populated last so they overwrite these values
         if (emr.feet != DEFAULT_VALUE)
         {
            frm_measure_pwa->edtFeet->Text = emr.feet;
            if (!emr_get_editing())
            {
               frm_measure_pwa->edtFeet->ReadOnly = true;
            }
         }
         if (emr.inch != DEFAULT_VALUE)
         {
            frm_measure_pwa->edtInch->Text = emr.inch;
            if (!emr_get_editing())
            {
               frm_measure_pwa->edtInch->ReadOnly = true;
            }
         }
         if (emr.pound != DEFAULT_VALUE)
         {
            frm_measure_pwa->edtPound->Text = emr.pound;
            if (!emr_get_editing())
            {
               frm_measure_pwa->edtPound->ReadOnly = true;
            }
         }
         if (emr.height != DEFAULT_VALUE)
         {
            frm_measure_pwa->edtHeight->Text = emr.height;
            if (!emr_get_editing())
            {
               frm_measure_pwa->edtHeight->ReadOnly = true;
            }
         }
         if (emr.weight != DEFAULT_VALUE)
         {
            frm_measure_pwa->edtWeight->Text = emr.weight;
            if (!emr_get_editing())
            {
               frm_measure_pwa->edtWeight->ReadOnly = true;
            }
         }
         success = true;
      }
   }
   return success;
}

void __fastcall Tfrm_measure_pwa::tmr_repeat_assessmentTimer(
      TObject *Sender)
{
   // PM V9
   // Go straight to the capture screen
   bbtn_captureClick(Sender);
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_measure_pwa::bbtn_captureClick(TObject *Sender)
{
   TDataSet   *pwa_table;
   bool       status;

   tmr_repeat_assessment->Enabled = false;
   try
   {
     // If the audit option is set, the operator must sign in
     if (security_show())
     {
         if (UpdatePwa() == false)
         {
            bbtn_capture->Enabled = true;
            //SetFocus();
            return;
         }
     }
     else
     {
         return;
     }
//#ifdef SPHYGMOCOR_USA
     if (pwa_current->MeasureType == PWA_CAROTID)
     {
        if (MsgBox("The Carotid Transfer Function has not yet been approved\nfor clinical use in the U.S.A.\n\nThe Carotid Transfer Function is to be used only for Research purposes in the U.S.A.\n\nDo you Accept these conditions ?",
                   SCONFIRMATION,
                   MB_YESNO | MB_ICONQUESTION) == ID_NO)
        {
           bbtn_capture->Enabled = true;
           //SetFocus();
           return;
        }
     }
//#endif

     Screen->Cursor = crHourGlass;
     if (capture_show_form(MEAS_PWA_ID) == true)
     {
        pnlGrid->Enabled = false;
        pnlFields->Visible = false;
        pnlWait->Visible = true;
        lblStatus->Caption = "Calculating Results";
        Application->ProcessMessages();
        if (pwa_current->Calculate())
        {
           lblStatus->Caption = "Opening Pulse Wave Analysis Database";
           Application->ProcessMessages();
           if (dbmgr_open(DBMGR_MEASURE_PWA_TABLE, false))
           {
              pwa_table = dbmgr_get_dataset(DBMGR_MEASURE_PWA_TABLE, false);
              status = false;
              if (pwa_table != NULL)
              {
                 lblStatus->Caption = "Saving Results to Database";
                 Application->ProcessMessages();
                 _sleep(1);
                 try
                 {
                    pwa_table->Insert();
                 }
                 catch (Exception &exception)
                 {
                    dbmgr_close(DBMGR_MEASURE_PWA_TABLE, false);
                    Screen->Cursor = crDefault;
                    pnlWait->Visible = false;
                    pnlGrid->Enabled = true;
                    pnlFields->Visible = true;
                    bbtn_capture->Enabled = true;
                    MsgBox(TERROR,
                           GetCurrentPwaMeasureDetails(),
                           MSG_DBREADWRITE_ERROR,
                           MSG_DBREADWRITE_ERROR,
                           exception.Message);
                    return;
                 }
                 status = pwa_current->Store(pwa_table, true, true);
              }
              dbmgr_close(DBMGR_MEASURE_PWA_TABLE, false);
              if (status)
              {
                 lblStatus->Caption = "Generating Report Information";
                 Application->ProcessMessages();
                 _sleep(1);
                 patient_update_measurement_count((short)(qryTonom->RecordCount + 1));
                 multdb_set_delete_status(false);
                 // If the EMR patient is active
                 if (emr_patient_is_active())
                 {
                     // And automatic export is enabled
                     if (emr_get_automatic())
                     {
                        // Then set the report export status to true
                        emr_set_report_export(true);
                     }
                 }
                 // PM V9
                 // Write the capture time taken to the log for feedback of customer usability
                 log_write("Successful PWA measurement for" + GetCurrentPwaMeasureDetails() + ", CaptureTime " + pwa_current->CaptureTime);
                 frm_main->spdbtn_reportClick(Sender);
              }
              else
              {
                 lblStatus->Caption = "Failed to save the Report.";
                 Application->ProcessMessages();
              }
           }
           else
           {
              lblStatus->Caption = "Failed to Open the Database.";
              Application->ProcessMessages();
           }
        }
        else
        {
           //pwa_current->SaveToFile();
           MsgBox_show(TWARNING,
                       MSG_MATH_ERROR,
                       LoadStr(MSG_MEAS_ERROR_CALC),
                       MSG_MEAS_ERROR_CALC, "");
        }
        Screen->Cursor = crDefault;
        pnlWait->Visible = false;
        pnlGrid->Enabled = true;
        pnlFields->Visible = true;
     }
     else
     {
       //SetFocus();
       bbtn_capture->Enabled = true;
     }
   }
   catch (Exception &exception)
   {
      MsgBox("Report Generation status is unknown.\n\nClose SphygmoCor, restart and check whether the report has been saved in the database.",
             SNOTIFICATION,
             MB_ICONEXCLAMATION | MB_OK);
      log_write(SWARNING + exception.Message);
   }
   Screen->Cursor = crDefault;
   pnlWait->Visible = false;
   pnlGrid->Enabled = true;
   pnlFields->Visible = true;
   bbtn_capture->Enabled = true;
}
//---------------------------------------------------------------------------

