//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "form_recalculate_hrv.h"
#include <dbmgr/pubserv.h>
#include <meas/pubserv.h>
#include <msg/pubserv.h>
#include <config/pubserv.h>
#include <emr/pubserv.h>
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
Tfrm_recalculate_hrv *frm_recalculate_hrv;

//---------------------------------------------------------------------------
bool meas_recalculate_hrv_show_form(TComponent* Owner, THRV* pHrv, TDataSet* pDataSet,
     String pPatientName, MEAS_SENDER_TYPE report_sender)
{
   bool ret;
   Tfrm_recalculate_hrv *lfrm = new Tfrm_recalculate_hrv(Owner, pHrv, pDataSet, pPatientName, report_sender);
   lfrm->ShowModal();
   ret = (lfrm->ModalResult == mrYes ? true : false);
   delete lfrm;
   return ret;
}
//---------------------------------------------------------------------------
__fastcall Tfrm_recalculate_hrv::Tfrm_recalculate_hrv(TComponent* Owner,
           THRV* pHrv, TDataSet* pDataSet, String pPatientName, MEAS_SENDER_TYPE report_sender)
  : TForm(Owner)
{
  hrv_current = pHrv;
  hrv_dataset = pDataSet;
  hrv_sender = report_sender;
  lbl_pat->Caption = pPatientName;
}
//---------------------------------------------------------------------------
void __fastcall Tfrm_recalculate_hrv::FormShow(TObject *Sender)
{
   double  bmi_height;

   if (hrv_current == NULL)
   {
      ModalResult = mrCancel;
      return;
   }

   // Populate controls
   if (hrv_current->Dp > 0)
   {
      edtDp->Text = RoundIntToStr(hrv_current->Dp);
   }
   if (hrv_current->Sp > 0)
   {
      edtSp->Text = RoundIntToStr(hrv_current->Sp);
   }
   if (hrv_current->MeanP > 0)
   {
      edtMp->Text = RoundIntToStr(hrv_current->MeanP);
   }

   edtMed->Text = hrv_current->Medication;
   edtNotes->Text = hrv_current->Notes;
   edtOperator->Text = hrv_current->Operator;

   if (hrv_current->Feet >= 0 && hrv_current->Feet != DEFAULT_VALUE)
  {
     edtFeet->Text = hrv_current->Feet;
  }
  else
  {
     edtFeet->Text = "";
  }

  if (hrv_current->Inch >= 0 && hrv_current->Inch != DEFAULT_VALUE)
  {
     edtInch->Text = hrv_current->Inch;
  }
  else
  {
     edtInch->Text = "";
  }

  if (hrv_current->Pound > 0 && hrv_current->Pound != DEFAULT_VALUE)
  {
     edtPound->Text = hrv_current->Pound;
  }
  else
  {
     edtPound->Text = "";
  }

  if (hrv_current->Height > 0 && hrv_current->Height != DEFAULT_VALUE)
   {
      edtHeight->Text = hrv_current->Height;
   }
   else
   {
      edtHeight->Text = "";
   }

   if (hrv_current->Weight > 0 && hrv_current->Weight != DEFAULT_VALUE)
   {
      edtWeight->Text = hrv_current->Weight;
   }
   else
   {
      edtWeight->Text = "";
   }

   if (edtWeight->Text.ToIntDef(-1) > 0 && edtHeight->Text.ToIntDef(-1) > 0)
   {
      bmi_height = (edtHeight->Text.ToDouble() / 100.0) * (edtHeight->Text.ToDouble() / 100.0);
      txtBmi->Caption = FormatFloat("0.##", edtWeight->Text.ToDouble() / bmi_height);
   }
   else
   {
      txtBmi->Caption = "";
   }

   // PM V9
   // The field that opened the modify form will be selected initially
   switch (hrv_sender)
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

      default:
         edtSp->SetFocus();
         break;
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

   edtDp->ReadOnly = false;
   edtSp->ReadOnly = false;
   edtMp->ReadOnly = false;
   edtMed->ReadOnly = false;
   edtNotes->ReadOnly = false;
   edtOperator->ReadOnly = false;
   edtFeet->ReadOnly = false;
   edtInch->ReadOnly = false;
   edtPound->ReadOnly = false;
   edtHeight->ReadOnly = false;
   edtWeight->ReadOnly = false;

   // PM V9
   // Enable or Disable study data from the EMR object
   if (recalculate_hrv_emr_mode())
   {
      ;
   }
}
//---------------------------------------------------------------------------
bool Tfrm_recalculate_hrv::UpdateHrv()
{
  // Update current HRV object
  hrv_current->Sp = edtSp->Text.ToIntDef(0);
  hrv_current->Dp = edtDp->Text.ToIntDef(0);
  hrv_current->MeanP = edtMp->Text.ToIntDef(0);
  hrv_current->time_elapsed = hrv_current->DateTime - hrv_current->StartTime;

  // Height and weight
  int weight = edtWeight->Text.ToIntDef(-1);
  int height = edtHeight->Text.ToIntDef(-1);
  if (height > 0)
  {
     hrv_current->Height = height;
  }
  else
  {
     hrv_current->Height = DEFAULT_VALUE;
  }
  if (weight > 0)
  {
     hrv_current->Weight = weight;
  }
  else
  {
     hrv_current->Weight = DEFAULT_VALUE;
  }
  hrv_current->Medication = MsgBox_ReplaceCarriage(edtMed->Text);
  hrv_current->Notes = MsgBox_ReplaceCarriage(edtNotes->Text);
  hrv_current->Operator = edtOperator->Text;

  // Validate
  if (hrv_current->ValidateBeforeCalculate()==false)
    return false;

  // Success
  return true;
}

void __fastcall Tfrm_recalculate_hrv::edtSpChange(TObject *Sender)
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
void __fastcall Tfrm_recalculate_hrv::edtMpChange(TObject *Sender)
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
void __fastcall Tfrm_recalculate_hrv::edtDpChange(TObject *Sender)
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
void __fastcall Tfrm_recalculate_hrv::edtHeightChange(TObject *Sender)
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
void __fastcall Tfrm_recalculate_hrv::edtWeightChange(TObject *Sender)
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
void __fastcall Tfrm_recalculate_hrv::edtPoundChange(TObject *Sender)
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
void __fastcall Tfrm_recalculate_hrv::edtFeetChange(TObject *Sender)
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
void __fastcall Tfrm_recalculate_hrv::edtInchChange(TObject *Sender)
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
// PM V9
/* ###########################################################################
 ** recalculate_hrv_emr_mode()
 **
 ** DESCRIPTION
 **  Enables or Disables the study data specified by the EMR object
 ** INPUT
 **  Recalculate HRV Form
 ** OUTPUT
 **  None
 ** RETURN
 **  Boolean - success or not
*/
//---------------------------------------------------------------------------
bool Tfrm_recalculate_hrv::recalculate_hrv_emr_mode(void)
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
void __fastcall Tfrm_recalculate_hrv::bbtn_modifyClick(TObject *Sender)
{
  // Validate
  if (hrv_dataset == NULL) return;
  // Update current measurement
   if (UpdateHrv() == false)
    return;
  // Try to recalculate parameters
  if (hrv_current->Calculate() == false)
  {
     // "Error calculating measurememt parameters",
     MsgBox_show(TWARNING,
                 MSG_MATH_ERROR,
                 LoadStr(MSG_MEAS_ERROR_CALC),
                 MSG_MEAS_ERROR_CALC, "");
     return;
  }

  // Try to store parameters into database
  hrv_dataset->Edit();
  if (hrv_current->Store(hrv_dataset, false, false) == false)
  {
    // "Error storing measurememt parameters"
    hrv_dataset->Cancel();
    return;
  }
  // Success
  ModalResult = mrYes;   
}
//---------------------------------------------------------------------------


void __fastcall Tfrm_recalculate_hrv::bbtn_cancelClick(TObject *Sender)
{
   ModalResult = mrNo;   
}
//---------------------------------------------------------------------------

