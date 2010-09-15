//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
#include "form_recalculate_pwa.h"
#include <dbmgr/pubserv.h>
#include <meas/pubserv.h>
#include <msg/pubserv.h>
#include <config/pubserv.h>
#include <cfr11/pubserv.h>
#include <emr/pubserv.h>
#include <patient/pubserv.h>
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
Tfrm_recalculate_pwa *frm_recalculate_pwa;

//---------------------------------------------------------------------------
bool meas_recalculate_show_form(TComponent* Owner, TPWA* pPwa, TDataSet* pDataSet,
     String pPatientName, AUDIT_MODE AuditMode, MEAS_SENDER_TYPE report_sender)
{
   bool ret;
   Tfrm_recalculate_pwa *lfrm = new Tfrm_recalculate_pwa(Owner, pPwa, pDataSet, pPatientName, AuditMode, report_sender);
   lfrm->ShowModal();
   ret = (lfrm->ModalResult == mrYes ? true : false);
   delete lfrm;
   return ret;
}
//---------------------------------------------------------------------------
__fastcall Tfrm_recalculate_pwa::Tfrm_recalculate_pwa(TComponent* Owner,
           TPWA* pPwa, TDataSet* pDataSet, String pPatientName,
           AUDIT_MODE AuditMode, MEAS_SENDER_TYPE report_sender)
  : TForm(Owner)
{
  pwa_current = pPwa;
  pwa_dataset = pDataSet;
  lbl_pat->Caption = pPatientName;
  pwa_audit_mode = AuditMode;
  pwa_sender = report_sender;
  for (int i = 0; i < PWA_NOF_MEASURES; i++)
  {
     lstPA->Items->Add(PWAMTypeAsString[i]);
  }
}
//---------------------------------------------------------------------------
void __fastcall Tfrm_recalculate_pwa::FormShow(TObject *Sender)
{
   double  bmi_height;
   MEAS_ID_TYPE  study_mode;

   study_mode = patient_get_study_mode();

   if (pwa_current == NULL)
   {
      ModalResult = mrCancel;
      return;
   }

   // Populate controls
   lstPA->ItemIndex = pwa_current->MeasureType;

   if (pwa_current->Dp > 0)
   {
      edtDp->Text = RoundIntToStr(pwa_current->Dp);
   }
   if (pwa_current->Sp > 0)
   {
      edtSp->Text = RoundIntToStr(pwa_current->Sp);
   }
   if (pwa_current->MeanP > 0)
   {
      edtMp->Text = RoundIntToStr(pwa_current->MeanP);
   }

   edtMed->Text = pwa_current->Medication;
   edtNotes->Text = pwa_current->Notes;
   edtOperator->Text = pwa_current->Operator;
   edtInterpretation->Text = pwa_current->Interpretation;

   if (pwa_current->Feet >= 0 && pwa_current->Feet != DEFAULT_VALUE)
  {
     edtFeet->Text = pwa_current->Feet;
  }
  else
  {
     edtFeet->Text = "";
  }

  if (pwa_current->Inch >= 0 && pwa_current->Inch != DEFAULT_VALUE)
  {
     edtInch->Text = pwa_current->Inch;
  }
  else
  {
     edtInch->Text = "";
  }

  if (pwa_current->Pound > 0 && pwa_current->Pound != DEFAULT_VALUE)
  {
     edtPound->Text = pwa_current->Pound;
  }
  else
  {
     edtPound->Text = "";
  }

  if (pwa_current->Height > 0 && pwa_current->Height != DEFAULT_VALUE)
   {
      edtHeight->Text = pwa_current->Height;
   }
   else
   {
      edtHeight->Text = "";
   }

   if (pwa_current->Weight > 0 && pwa_current->Weight != DEFAULT_VALUE)
   {
      edtWeight->Text = pwa_current->Weight;
   }
   else
   {
      edtWeight->Text = "";
   }

   if (pwa_current->Bmi > 0 && pwa_current->Bmi != DEFAULT_VALUE)
   {
      txtBmi->Caption = FormatFloat("#0.##", pwa_current->Bmi);
   }
   else
   {
      txtBmi->Caption = "";
   }

   if (pwa_current->avi->Aortic_Distance > 0 && pwa_current->avi->Aortic_Distance != DEFAULT_VALUE)
   {
      edtDistance->Text = RoundIntToStr(pwa_current->avi->Aortic_Distance);
   }
   else
   {
      edtDistance->Text = "";
   }
   edtProximal->Text = "";
   edtDistal->Text = "";

   // PM V9
   // The field that opened the modify form will be selected initially
   switch (pwa_sender)
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

      case MEAS_INTERPRETATION:
         edtInterpretation->SelectAll();
         edtInterpretation->SetFocus();
         break;

      case MEAS_DISTANCE:
         edtDistance->SelectAll();
         edtDistance->SetFocus();
         break;

      case MEAS_AUDIT:
         edtReason->SelectAll();
         edtReason->SetFocus();
         break;

      default:
         edtInterpretation->SetFocus();
         break;
   }

   lstPA->Enabled = true;
   edtSp->Enabled = true;
   edtDp->Enabled = true;
   edtMp->Enabled = true;
   edtMed->ReadOnly = false;
   edtNotes->ReadOnly = false;
   edtOperator->ReadOnly = false;
   edtHeight->Enabled = true;
   edtFeet->Enabled = true;
   edtInch->Enabled = true;
   edtWeight->Enabled = true;
   edtPound->Enabled = true;
   grboxDist->Enabled = true;
   edtInterpretation->ReadOnly = false;
   edtReason->ReadOnly = false;
   bbtn_modify->Enabled = true;

   edtFeet->ReadOnly = false;
   edtInch->ReadOnly = false;
   edtPound->ReadOnly = false;
   edtHeight->ReadOnly = false;
   edtWeight->ReadOnly = false;

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

   // If the Audit Trail option is set, disable the Operator field
   if (config_get_audit_option() && study_mode == MEAS_PWA_ID)
   {
      lbl_reason->Visible = true;
      edtReason->Visible = true;
      edtOperator->ReadOnly = true;
      //edtReason->Text = pwa_current->Reason;
      edtReason->SetFocus();
   }
   else
   {
      lbl_reason->Visible = false;
      edtReason->Visible = false;
   }
   // PM V9
   // If the Clinical option is set, disable the Artery field
   if (config_get_clinical_option() && study_mode == MEAS_PWA_ID)
   {
      lbl_artery->Visible = false;
      lstPA->Visible = false;
   }
   else
   {
      lbl_artery->Visible = true;
      lstPA->Visible = true;
   }

   switch (pwa_audit_mode)
   {
      // In normal mode, the report can be modified
      case AUDIT_NORMAL:
         break;

      // In deleting mode, only the reason for change can be edited
      case AUDIT_DELETING:
         lstPA->Enabled = false;
         edtSp->Enabled = false;
         edtDp->Enabled = false;
         edtMp->Enabled = false;
         edtMed->ReadOnly = true;
         edtNotes->ReadOnly = true;
         edtHeight->Enabled = false;
         edtFeet->Enabled = false;
         edtInch->Enabled = false;
         edtWeight->Enabled = false;
         edtPound->Enabled = false;
         grboxDist->Enabled = false;
         edtInterpretation->ReadOnly = true;
         //edtReason->Enabled = true;
         //tbtn_recalc->Enabled = true;
         break;

      // In browsing mode, no changes can be made. This is simply to view edit
      // boxes in their entirety, including reason for change.
      case AUDIT_BROWSING:
         lstPA->Enabled = false;
         edtSp->Enabled = false;
         edtDp->Enabled = false;
         edtMp->Enabled = false;
         edtMed->ReadOnly = true;
         edtNotes->ReadOnly = true;
         edtHeight->Enabled = false;
         edtFeet->Enabled = false;
         edtInch->Enabled = false;
         edtWeight->Enabled = false;
         edtPound->Enabled = false;
         grboxDist->Enabled = false;
         edtInterpretation->ReadOnly = true;
         edtReason->Text = pwa_current->Reason;
         edtReason->ReadOnly = true;
         bbtn_modify->Enabled = false;
         break;
   }
   // PM CR
   // Interpretation cannot be entered for Simulated reports
   if (pwa_current->Simulation)
   {
      edtInterpretation->ReadOnly = true;
   }

   // PM V9
   // Enable or Disable study data from the EMR object
   if (recalculate_pwa_emr_mode())
   {
      ;
   }
}
//---------------------------------------------------------------------------
bool Tfrm_recalculate_pwa::UpdatePwa()
{
  // Update current PWA object
  pwa_current->MeasureType = (PWA_MEASURE_TYPE)lstPA->ItemIndex;
  pwa_current->Sp = edtSp->Text.ToIntDef(0);
  pwa_current->Dp = edtDp->Text.ToIntDef(0);
  pwa_current->MeanP = edtMp->Text.ToIntDef(0);

  // Height and weight
  int weight = edtWeight->Text.ToIntDef(-1);
  int height = edtHeight->Text.ToIntDef(-1);
  if (height > 0)
  {
     pwa_current->Height = height;
  }
  else
  {
     pwa_current->Height = DEFAULT_VALUE;
  }
  if (weight > 0)
  {
     pwa_current->Weight = weight;
  }
  else
  {
     pwa_current->Weight = DEFAULT_VALUE;
  }
  if (txtBmi->Caption != "")
      pwa_current->Bmi = txtBmi->Caption.ToDouble();

  pwa_current->Medication = edtMed->Text;
  pwa_current->Notes = edtNotes->Text;
  pwa_current->Operator = edtOperator->Text;

  pwa_current->Interpretation = edtInterpretation->Text;

  if (edtDistance->Text == "")
  {
     pwa_current->avi->Aortic_Distance = DEFAULT_VALUE;
  }
  else
  {
     pwa_current->avi->Aortic_Distance = edtDistance->Text.ToIntDef(DEFAULT_VALUE);
  }
  
  // Validate
  if (pwa_current->ValidateBeforeCalculate()==false)
    return false;

  // Success
  return true;
}
//---------------------------------------------------------------------------
void __fastcall Tfrm_recalculate_pwa::edtSpChange(TObject *Sender)
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
void __fastcall Tfrm_recalculate_pwa::edtMpChange(TObject *Sender)
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
void __fastcall Tfrm_recalculate_pwa::edtDpChange(TObject *Sender)
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
//---------------------------------------------------------------------------
void __fastcall Tfrm_recalculate_pwa::edtHeightChange(TObject *Sender)
{
  double bmi_height;
  double bmi;

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
     bmi = edtWeight->Text.ToDouble() / bmi_height;
     txtBmi->Caption = FormatFloat("0.##", bmi);
  }
}
//---------------------------------------------------------------------------
void __fastcall Tfrm_recalculate_pwa::edtWeightChange(TObject *Sender)
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
     bmi_height = (edtHeight->Text.ToDouble() / 100.0) * (edtHeight->Text.ToDouble() / 100.0);
     bmi = edtWeight->Text.ToDouble() / bmi_height;
     txtBmi->Caption = FormatFloat("0.##", bmi);
  }
}
//---------------------------------------------------------------------------
void __fastcall Tfrm_recalculate_pwa::edtPoundChange(TObject *Sender)
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

void __fastcall Tfrm_recalculate_pwa::edtFeetChange(TObject *Sender)
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

void __fastcall Tfrm_recalculate_pwa::edtInchChange(TObject *Sender)
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

void __fastcall Tfrm_recalculate_pwa::edtDistanceChange(TObject *Sender)
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


void __fastcall Tfrm_recalculate_pwa::edtDistalChange(TObject *Sender)
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


void __fastcall Tfrm_recalculate_pwa::edtProximalChange(TObject *Sender)
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

void __fastcall Tfrm_recalculate_pwa::CalcDistance()
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
 ** recalculate_pwa_emr_mode()
 **
 ** DESCRIPTION
 **  Enables or Disables the study data specified by the EMR object
 ** INPUT
 **  Recalculate PWA Form
 ** OUTPUT
 **  None
 ** RETURN
 **  Boolean - success or not
*/
//---------------------------------------------------------------------------
bool Tfrm_recalculate_pwa::recalculate_pwa_emr_mode(void)
{
   EMR_RECORD_TYPE      emr;
   bool                 success = false;

   // If this is the EMR patient and editing is false, then disable any fields
   // that have been populated from the EMR object
   if (emr_patient_is_active())
   {
      if (emr_get(&emr))
      {
         if (!emr_get_editing())
         {
            lstPA->Enabled = false;

            if (emr.dp != DEFAULT_VALUE)
            {
               // If DP has a value, then MP or SP will also have a value
               edtSp->Enabled = false;
               edtDp->Enabled = false;
               edtMp->Enabled = false;
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

void __fastcall Tfrm_recalculate_pwa::bbtn_modifyClick(TObject *Sender)
{
  // Validate
  if (pwa_dataset == NULL) return;
  // Update current measurement
   if (UpdatePwa() == false)
    return;
   // Update audit object
  if (!audit_update_pwa(pwa_current, edtReason->Text)) return;
  
  // Try to recalculate parameters
  if (pwa_current->Calculate() == false)
  {
     // "Error calculating measurememt parameters",
     MsgBox_show(TWARNING,
                 MSG_MATH_ERROR,
                 LoadStr(MSG_MEAS_ERROR_CALC),
                 MSG_MEAS_ERROR_CALC, "");
     return;
  }

  // Try to store parameters into database
  pwa_dataset->Edit();
   // Store the original report to the Audit Trail
  if (!audit_pwa_insert(pwa_current, pwa_dataset, pwa_audit_mode)) return;

  if (pwa_current->Store(pwa_dataset, false, false) == false)
  {
    // "Error storing measurememt parameters"
    pwa_dataset->Cancel();
    return;
  }
  // Store new report in the Audit Trail
  if (!audit_pwa_edit(pwa_dataset)) return;
  
  // Success
  ModalResult = mrYes;   
}
//---------------------------------------------------------------------------
void __fastcall Tfrm_recalculate_pwa::bbtn_cancelClick(TObject *Sender)
{
   ModalResult = mrNo;
}
//---------------------------------------------------------------------------

