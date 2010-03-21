//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
#include "form_recalculate_pwv.h"
#include <dbmgr/pubserv.h>
#include <meas/pubserv.h>
#include <msg/pubserv.h>
#include <config/pubserv.h>
#include <cfr11/pubserv.h>
#include <emr/pubserv.h>
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
Tfrm_recalculate_pwv *frm_recalculate_pwv;

//---------------------------------------------------------------------------
bool meas_recalculate_pwv_show_form(TComponent* Owner, TPWV* pPwv, TDataSet* pDataSet,
     String pPatientName, AUDIT_MODE AuditMode, MEAS_SENDER_TYPE report_sender)
{
   bool ret;
   Tfrm_recalculate_pwv *lfrm = new Tfrm_recalculate_pwv(Owner, pPwv, pDataSet, pPatientName, AuditMode, report_sender);
   lfrm->ShowModal();
   ret = (lfrm->ModalResult == mrYes ? true : false);
   delete lfrm;
   return ret;
}
//---------------------------------------------------------------------------
__fastcall Tfrm_recalculate_pwv::Tfrm_recalculate_pwv(TComponent* Owner,
           TPWV* pPwv, TDataSet* pDataSet, String pPatientName, AUDIT_MODE AuditMode, MEAS_SENDER_TYPE report_sender)
  : TForm(Owner)
{
  pwv = pPwv;
  pwv_dataset = pDataSet;
  pwv_audit_mode = AuditMode;
  pwv_sender = report_sender;
  lbl_pat->Caption = pPatientName;
}
//---------------------------------------------------------------------------
void __fastcall Tfrm_recalculate_pwv::FormShow(TObject *Sender)
{
  // Validate
  if (pwv == NULL)
  {
     ModalResult = mrCancel;
     return;
  }

  /*#ifdef PWV_SHORT_STUDY_ENABLED
    if (rgCaptureA->Items->Count < 4)
    {
       rgCaptureA->Items->Insert(0, "5");
       rgCaptureB->Items->Insert(0, "5");
    }
  #endif */

  rbtnCarotidA->Checked = true;
  switch (pwv->SiteA.MeasureType)
  {
     case PWV_RADIAL:
      rbtnRadialA->Checked = true;
      break;
     case PWV_CAROTID:
      rbtnCarotidA->Checked = true;
      break;
     case PWV_FEMORAL:
      rbtnFemoralA->Checked = true;
      break;
     case PWV_PROXIMAL:
      rbtnProximalA->Checked = true;
      break;
  }

  rbtnFemoralB->Checked = true;
  switch (pwv->SiteB.MeasureType)
  {
     case PWV_RADIAL:
      rbtnRadialB->Checked = true;
      break;
     case PWV_CAROTID:
      rbtnCarotidB->Checked = true;
      break;
     case PWV_FEMORAL:
      rbtnFemoralB->Checked = true;
      break;
     case PWV_DISTAL:
      rbtnDistalB->Checked = true;
      break;
  }

  if (pwv->Distance > 0)
    edtDistance->Text = RoundIntToStr(pwv->Distance);
  else
    edtDistance->Text = "";

  if (pwv->DistancePx > 0)
    edtProximal->Text = RoundIntToStr(pwv->DistancePx);
  else
    edtProximal->Text = "";

  if (pwv->DistanceDt)
    edtDistal->Text = RoundIntToStr(pwv->DistanceDt);
  else
    edtDistal->Text = "";

   // PM V9
   // Only the Intersecting Tangents algorithm is used in Clinical mode
   if (config_get_clinical_option())
   {
      rgAlgorithm->Visible = false;
      rgAlgorithm->ItemIndex = 2;
   }
   else
   {
      rgAlgorithm->Visible = true;
      rgAlgorithm->ItemIndex = pwv->Algorithm - 1;
   }

  if (pwv->PHeightPercent > 0)
    edtPHPercent->Text = RoundIntToStr(pwv->PHeightPercent);
  else
    edtPHPercent->Text = "";
  rgAlgorithmClick(Sender);

  if (pwv->Dp > 0)
    edtDp->Text = RoundIntToStr(pwv->Dp);
  else
    edtDp->Text = "";

  if (pwv->Sp > 0)
    edtSp->Text = RoundIntToStr(pwv->Sp);
  else
    edtSp->Text = "";

  if (pwv->MeanP > 0)
    edtMp->Text = RoundIntToStr(pwv->MeanP);
  else
    edtMp->Text = "";

  edtMed->Text = pwv->Medication;
  edtNotes->Text = pwv->Notes;
  edtOperator->Text = pwv->Operator;

  if (pwv->Feet >= 0 && pwv->Feet != DEFAULT_VALUE)
  {
     edtFeet->Text = pwv->Feet;
  }
  else
  {
     edtFeet->Text = "";
  }

  if (pwv->Inch >= 0 && pwv->Inch != DEFAULT_VALUE)
  {
     edtInch->Text = pwv->Inch;
  }
  else
  {
     edtInch->Text = "";
  }

  if (pwv->Pound > 0 && pwv->Pound != DEFAULT_VALUE)
  {
     edtPound->Text = pwv->Pound;
  }
  else
  {
     edtPound->Text = "";
  }

  if (pwv->Height > 0 && pwv->Height != DEFAULT_VALUE)
  {
     edtHeight->Text = pwv->Height;
  }
  else
  {
     edtHeight->Text = "";
  }

  if (pwv->Weight > 0 && pwv->Weight != DEFAULT_VALUE)
  {
     edtWeight->Text = pwv->Weight;
  }
  else
  {
     edtWeight->Text = "";
  }

  if (pwv->Bmi > 0 && pwv->Bmi != DEFAULT_VALUE)
  {
     txtBmi->Caption = FormatFloat("#0.##", pwv->Bmi);
  }
  else
  {
     txtBmi->Caption = "";
  }

   // PM V9
   // The field that opened the modify form will be selected initially
   switch (pwv_sender)
   {
      case MEAS_OPERATOR:
         edtOperator->SelectAll();
         edtOperator->SetFocus();
         break;

      case MEAS_BMI:
         if (config_get_system_locale() == CONFIG_DEFAULT_LOCALE)
         {
            edtHeight->SelectAll();
            edtHeight->SetFocus();
         }
         else
         {
            edtFeet->SelectAll();
            edtFeet->SetFocus();
         }
         break;

      case MEAS_MEDICATIONS:
         edtMed->SelectAll();
         edtMed->SetFocus();
         break;

      case MEAS_NOTES:
         edtNotes->SelectAll();
         edtNotes->SetFocus();
         break;

      case MEAS_PRESSURES:
         edtSp->SelectAll();
         edtSp->SetFocus();
         break;

      case MEAS_DISTANCE:
         edtDistance->SelectAll();
         edtDistance->SetFocus();
         break;

      case MEAS_AUDIT:
         edtReason->SelectAll();
         edtReason->SetFocus();
         break;

      case MEAS_ALGORITHM:
         rgAlgorithm->SetFocus();
         break;

      default:
         edtSp->SetFocus();
         break;
   }

   edtSp->ReadOnly = false;
   edtMp->ReadOnly = false;
   edtDp->ReadOnly = false;
   grbSite->Enabled = true;
   edtHeight->Enabled = true;
   edtFeet->Enabled = true;
   edtInch->Enabled = true;
   edtWeight->Enabled = true;
   edtPound->Enabled = true;
   grboxDist->Enabled = true;
   rgAlgorithm->Enabled = true;
   edtMed->ReadOnly = false;
   edtNotes->ReadOnly = false;
   edtOperator->ReadOnly = false;
   edtReason->ReadOnly = false;
   bbtn_modify->Enabled = true;

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

   // If the Audit Trail option is set, disable the Operator field
   if (config_get_audit_option())
   {
      lbl_reason->Visible = true;
      edtReason->Visible = true;
      edtOperator->ReadOnly = true;
      //edtReason->Text = pwv->Reason;
      edtReason->SetFocus();
   }
   else
   {
      lbl_reason->Visible = false;
      edtReason->Visible = false;
   }

   switch (pwv_audit_mode)
   {
      // In normal mode, the report can be modified
      case AUDIT_NORMAL:
         break;

      // In deleting mode, only the reason for change can be edited
      case AUDIT_DELETING:
         edtSp->Enabled = false;
         edtMp->Enabled = false;
         edtDp->Enabled = false;
         grbSite->Enabled = false;
         edtHeight->Enabled = false;
         edtFeet->Enabled = false;
         edtInch->Enabled = false;
         edtWeight->Enabled = false;
         edtPound->Enabled = false;
         grboxDist->Enabled = false;
         rgAlgorithm->Enabled = false;
         edtMed->ReadOnly = true;
         edtNotes->ReadOnly = true;
         //edtReason->Enabled = true;
         //tbtn_recalc->Enabled = true;
         break;

      // In browsing mode, no changes can be made. This is simply to view edit
      // boxes in their entirety, including reason for change.
      case AUDIT_BROWSING:
         edtSp->Enabled = false;
         edtMp->Enabled = false;
         edtDp->Enabled = false;
         grbSite->Enabled = false;
         edtHeight->Enabled = false;
         edtFeet->Enabled = false;
         edtInch->Enabled = false;
         edtWeight->Enabled = false;
         edtPound->Enabled = false;
         grboxDist->Enabled = false;
         rgAlgorithm->Enabled = false;
         edtMed->ReadOnly = true;
         edtNotes->ReadOnly = true;
         edtReason->Text = pwv->Reason;
         edtReason->ReadOnly = true;
         bbtn_modify->Enabled = false;
         break;
   }
   // PM V9
   // Enable or Disable study data from the EMR object
   if (recalculate_pwv_emr_mode())
   {
      ;
   }

  /*#ifdef PWV_SHORT_STUDY_ENABLED
    if (pwv->SiteA.Nof10s == PWV_SHORT_STUDY_ID)
    {
       rgCaptureA->ItemIndex = 0;
    }
    else
    {
      rgCaptureA->ItemIndex = pwv->SiteA.Nof10s;
    }
  #else
    rgCaptureA->ItemIndex = pwv->SiteA.Nof10s - 1;
  #endif

  /*#ifdef PWV_SHORT_STUDY_ENABLED
    if (pwv->SiteB.Nof10s == PWV_SHORT_STUDY_ID)
    {
       rgCaptureB->ItemIndex = 0;
    }
    else
    {
       rgCaptureB->ItemIndex = pwv->SiteB.Nof10s;
    }
  #else
     rgCaptureB->ItemIndex = pwv->SiteB.Nof10s - 1;
  #endif */
}
//---------------------------------------------------------------------------
// Update current PWV object
//---------------------------------------------------------------------------
bool __fastcall Tfrm_recalculate_pwv::UpdatePwv()
{
  // Pressures
  pwv->Sp = edtSp->Text.ToIntDef(0);
  pwv->Dp = edtDp->Text.ToIntDef(0);
  pwv->MeanP = edtMp->Text.ToIntDef(0);

  // Measure type
  pwv->SiteA.MeasureType = PWV_NOF_MEASURES;
  if (rbtnRadialA->Checked)
    pwv->SiteA.MeasureType = PWV_RADIAL;
  else if (rbtnCarotidA->Checked)
    pwv->SiteA.MeasureType = PWV_CAROTID;
  else if (rbtnFemoralA->Checked)
    pwv->SiteA.MeasureType = PWV_FEMORAL;
  else if (rbtnProximalA->Checked)
    pwv->SiteA.MeasureType = PWV_PROXIMAL;

  pwv->SiteB.MeasureType = PWV_NOF_MEASURES;
  if (rbtnRadialB->Checked)
    pwv->SiteB.MeasureType = PWV_RADIAL;
  else if (rbtnCarotidB->Checked)
    pwv->SiteB.MeasureType = PWV_CAROTID;
  else if (rbtnFemoralB->Checked)
    pwv->SiteB.MeasureType = PWV_FEMORAL;
  else if (rbtnDistalB->Checked)
    pwv->SiteB.MeasureType = PWV_DISTAL;

  /*#ifdef PWV_SHORT_STUDY_ENABLED
    if (rgCaptureA->ItemIndex == 0)
    {
       pwv->SiteA.Nof10s = PWV_SHORT_STUDY_ID;
    }
    else
    {
       pwv->SiteA.Nof10s = rgCaptureA->ItemIndex;
    }
  #else
    pwv->SiteA.Nof10s = rgCaptureA->ItemIndex + 1;
  #endif

  #ifdef PWV_SHORT_STUDY_ENABLED
    if (rgCaptureB->ItemIndex == 0)
    {
       pwv->SiteB.Nof10s = PWV_SHORT_STUDY_ID;
    }
    else
    {
       pwv->SiteB.Nof10s = rgCaptureB->ItemIndex;
    }
  #else
    pwv->SiteB.Nof10s = rgCaptureB->ItemIndex + 1;
  #endif */

   // PM V9
   // Only the Intersecting Tangents algorithm is used in Clinical mode
   if (config_get_clinical_option())
   {
      pwv->Algorithm = 3;
   }
   else
   {
      pwv->Algorithm = rgAlgorithm->ItemIndex + 1;
   }

  pwv->PHeightPercent =
    (edtPHPercent->Visible ? edtPHPercent->Text.ToIntDef(-1) : -1);

  pwv->Medication = edtMed->Text;
  pwv->Notes = edtNotes->Text;
  pwv->Operator = edtOperator->Text;

  // Distance
  pwv->Distance = 0;
  pwv->DistancePx = 0;
  pwv->DistanceDt = 0;

  // CalcDistance();
  if (edtDistal->Text.ToIntDef(-1) > 0 || edtProximal->Text.ToIntDef(-1) > 0)
  {
    pwv->DistancePx = edtProximal->Text.ToIntDef(0);
    pwv->DistanceDt = edtDistal->Text.ToIntDef(0);
  }
  else if (edtDistance->Text.ToIntDef(-1) > 0)
  {
    pwv->Distance = edtDistance->Text.ToInt();
  }

  if (edtHeight->Text == "")
  {
     pwv->Height = DEFAULT_VALUE;
  }
  else
  {
     pwv->Height = edtHeight->Text.ToIntDef(DEFAULT_VALUE);
  }

  if (edtWeight->Text == "")
  {
     pwv->Weight = DEFAULT_VALUE;
  }
  else
  {
     pwv->Weight = edtWeight->Text.ToIntDef(DEFAULT_VALUE);
  }
  if (txtBmi->Caption != "")
    pwv->Bmi = txtBmi->Caption.ToDouble();

  // Validation
  if (pwv->ValidateBeforeCalculate()==false)
  {
    edtSp->SetFocus();
    return false;
  }

  // Success
  return true;
}
//---------------------------------------------------------------------------
void __fastcall Tfrm_recalculate_pwv::edtSpChange(TObject *Sender)
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
void __fastcall Tfrm_recalculate_pwv::edtMpChange(TObject *Sender)
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
void __fastcall Tfrm_recalculate_pwv::edtDpChange(TObject *Sender)
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
void __fastcall Tfrm_recalculate_pwv::FormKeyPress(TObject *Sender, char &Key)
{
  if (Key == VK_RETURN)
    bbtn_modifyClick(Sender);
}
//---------------------------------------------------------------------------
void __fastcall Tfrm_recalculate_pwv::edtHeightChange(TObject *Sender)
{
   double  bmi_height;

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
void __fastcall Tfrm_recalculate_pwv::edtWeightChange(TObject *Sender)
{
   double  bmi_height;

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
void __fastcall Tfrm_recalculate_pwv::rgAlgorithmClick(TObject *Sender)
{
  edtPHPercent->Visible = (rgAlgorithm->ItemIndex == 0);
  if (edtPHPercent->Visible && edtPHPercent->Text.ToIntDef(-1) < 0)
    edtPHPercent->Text = DEFAULT_PH_PERCENT;
}
//---------------------------------------------------------------------------
void __fastcall Tfrm_recalculate_pwv::edtDistanceChange(TObject *Sender)
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
void __fastcall Tfrm_recalculate_pwv::edtDistalChange(TObject *Sender)
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
void __fastcall Tfrm_recalculate_pwv::edtProximalChange(TObject *Sender)
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
void __fastcall Tfrm_recalculate_pwv::CalcDistance()
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
//---------------------------------------------------------------------------
void __fastcall Tfrm_recalculate_pwv::edtDistanceKeyPress(TObject *Sender,
      char &Key)
{
  edtDistal->Text = "";
  edtProximal->Text = "";
}
//---------------------------------------------------------------------------
void __fastcall Tfrm_recalculate_pwv::edtFeetChange(TObject *Sender)
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

void __fastcall Tfrm_recalculate_pwv::edtInchChange(TObject *Sender)
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

void __fastcall Tfrm_recalculate_pwv::edtPoundChange(TObject *Sender)
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
// PM V9
/* ###########################################################################
 ** recalculate_pwv_emr_mode()
 **
 ** DESCRIPTION
 **  Enables or Disables the study data specified by the EMR object
 ** INPUT
 **  Recalculate PWV Form
 ** OUTPUT
 **  None
 ** RETURN
 **  Boolean - success or not
*/
//---------------------------------------------------------------------------
bool Tfrm_recalculate_pwv::recalculate_pwv_emr_mode(void)
{
   EMR_RECORD_TYPE      emr;
   bool                 success = false;

   if (emr_patient_is_active())
   {
      if (emr_get(&emr))
      {
         if (!emr_get_editing())
         {
            if (emr.dp != DEFAULT_VALUE)
            {
               // If DP has a value, then MP or SP will also have a value
               edtDp->ReadOnly = true;
               edtSp->ReadOnly = true;
               edtMp->ReadOnly = true;
            }

            if (emr.medication != "")
            {
               edtMed->ReadOnly = true;
            }
            if (emr.study_notes != "")
            {
               edtNotes->ReadOnly = true;
            }
            if (emr.operator_name != "")
            {
               edtOperator->ReadOnly = true;
            }
            if (emr.feet != DEFAULT_VALUE)
            {
               edtFeet->ReadOnly = true;
            }
            if (emr.inch != DEFAULT_VALUE)
            {
               edtInch->ReadOnly = true;
            }
            if (emr.pound != DEFAULT_VALUE)
            {
               edtPound->ReadOnly = true;
            }
            if (emr.height != DEFAULT_VALUE)
            {
               edtHeight->ReadOnly = true;
            }
            if (emr.weight != DEFAULT_VALUE)
            {
               edtWeight->ReadOnly = true;
            }
            success = true;
         }
      }
   }
   return success;
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_recalculate_pwv::bbtn_modifyClick(TObject *Sender)
{
  // Validate
  if (pwv_dataset == NULL) return;
  // Update current measurement
   if (UpdatePwv() == false)
    return;
   // Update the audit object
  if (!audit_update_pwv(pwv, edtReason->Text)) return;

  // Try to recalculate parameters
  if (pwv->Calculate() == false)
  {
     // "Error calculating measurememt parameters",
     MsgBox_show(TWARNING,
                 MSG_MATH_ERROR,
                 LoadStr(MSG_MEAS_ERROR_CALC),
                 MSG_MEAS_ERROR_CALC, "");
     return;
  }

  // Try to store parameters into database
  pwv_dataset->Edit();
   // Store the original report to the Audit Trail
  if (!audit_pwv_insert(pwv, pwv_dataset, pwv_audit_mode)) return;

  if (pwv->Store(pwv_dataset, false, false) == false)
  {
    // "Error storing measurememt parameters"
    pwv_dataset->Cancel();
    return;
  }
  // Store the new report to the Audit Trail
  if (!audit_pwv_edit(pwv_dataset)) return;

  // Success
  ModalResult = mrYes;
}
//---------------------------------------------------------------------------
void __fastcall Tfrm_recalculate_pwv::bbtn_cancelClick(TObject *Sender)
{
   ModalResult = mrNo;
}
//---------------------------------------------------------------------------

