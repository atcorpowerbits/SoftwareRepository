//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include <dbmgr/pubserv.h>
#include <multdb/pubserv.h>
#include <meas/pubserv.h>
#include <msg/pubserv.h>
#include <log/pubserv.h>
#include <patient/pubserv.h>
#include <capture/pubserv.h>
#include <config/pubserv.h>
#include <cfr11/pubserv.h>
#include <emr/pubserv.h>
#include <scor/form_main.h>
#include "form_pwv.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
Tfrm_measure_pwv *frm_measure_pwv;
TADOQuery* qryPwv;

bool meas_pwv_initialise(void)
{
   frm_measure_pwv = NULL;
   return true;
}

//---------------------------------------------------------------------------
__fastcall Tfrm_measure_pwv::Tfrm_measure_pwv(TComponent* Owner)
  : Child_Form(Owner)
{
}

void __fastcall Tfrm_measure_pwv::FormShow(TObject *Sender)
{
   TDataSource   *dsMeas;
   double        bmi_height;

   PATIENT_RECORD_TYPE  pat;
   try
   {
     /*#ifdef PWV_SHORT_STUDY_ENABLED
       if (rgCaptureA->Items->Count < 4)
       {
          rgCaptureA->Items->Insert(0, "5");
          rgCaptureB->Items->Insert(0, "5");
       }
     #endif
     */
     patient_get(&pat);
     qryPwv = dbmgr_setup_query(DBMGR_MEASURE_PWV_TABLE,
                                DBMGR_QUERY_KEY,
                                PATIENT_SYSTEM_ID,
                                PATIENT_STUDY_ID,
                                PATIENT_NO,
                                pat.system_id,
                                pat.study_id,
                                IntToStr(pat.number),
                                MPW_DATETIME);

     dsMeas = dbmgr_get_data_source(DBMGR_MEASURE_PWV_QUERY, false);

     if ((dsMeas != NULL) && (qryPwv != NULL))
     {
        bbtn_capture->Enabled = true;
        grdMeas->DataSource = dsMeas;
        //navMeas->DataSource = dsMeas;

        pwv = meas_get_current_pwv();

        dsMeas->OnDataChange = record_changed;
        qryPwv->Last();

        // Check whether it is a first measurement
        if (qryPwv->RecordCount <= 0)
        {
           EmptyControls();
           rgAlgorithmClick(Sender);
        }

        // Bmi
        if (edtWeight->Text.ToIntDef(-1) > 0 && edtHeight->Text.ToIntDef(-1) > 0)
        {
            bmi_height = (edtHeight->Text.ToDouble() / 100.0) * (edtHeight->Text.ToDouble() / 100.0);
            txtBmi->Caption = FormatFloat("0.##", edtWeight->Text.ToDouble() / bmi_height);
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

         // PM V9
         // Only the Intersecting Tangents algorithm is used in Clinical mode
         if (config_get_clinical_option())
         {
            rgAlgorithm->Visible = false;
         }
         else
         {
            rgAlgorithm->Visible = true;
         }

         // Display study data from the EMR object - if enabled
         if (meas_pwv_emr_mode())
         {
            ;
         }

         // Disable the operator field if the Audit Trail is enabled
         if (config_get_audit_option())
         {
            edtOperator->ReadOnly = true;
         }
         
        // Focusing
        if (edtSp->Enabled)
        {
            edtSp->SetFocus();
        }
        lbl_pat->Caption = patient_get_name();
      }
      else
      {
         log_write("PWV Query failed initialisation.");
      }
   }
   catch(Exception &e)
   {
      log_write(SEXCEPTION +e.Message);
   }
}
//---------------------------------------------------------------------------
void __fastcall Tfrm_measure_pwv::record_changed(TObject *Sender, TField  *Field)
{
  if (pwv->Populate(qryPwv) == false)
  {
    EmptyControls();
    return;
  }

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
      rgAlgorithm->ItemIndex = 2;
  }
  else
  {
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
      edtFeet->Text = pwv->Feet;
  else
      edtFeet->Text = "";

  if (pwv->Inch >= 0 && pwv->Inch != DEFAULT_VALUE)
      edtInch->Text = pwv->Inch;
  else
      edtInch->Text = "";

  if (pwv->Pound > 0 && pwv->Pound != DEFAULT_VALUE)
      edtPound->Text = pwv->Pound;
  else
      edtPound->Text = "";

  if (pwv->Height > 0 && pwv->Height != DEFAULT_VALUE)
    edtHeight->Text = pwv->Height;
  else
    edtHeight->Text = "";

  if (pwv->Weight > 0 && pwv->Weight != DEFAULT_VALUE)
    edtWeight->Text = pwv->Weight;
  else
    edtWeight->Text = "";

  if (pwv->Bmi > 0 && pwv->Bmi != DEFAULT_VALUE)
    txtBmi->Caption = FormatFloat("#0.##", pwv->Bmi);
  else
    txtBmi->Caption = "";

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

  #ifdef PWV_SHORT_STUDY_ENABLED
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
  #endif  */

  switch (pwv->SiteA.Nof10s)
  {
      case 1:
         rbtn10A->Checked = true;
         break;
      case 2:
         rbtn20A->Checked = true;
         break;
      case 3:
         rbtn30A->Checked = true;
         break;
  }

  switch (pwv->SiteB.Nof10s)
  {
      case 1:
         rbtn10B->Checked = true;
         break;
      case 2:
         rbtn20B->Checked = true;
         break;
      case 3:
         rbtn30B->Checked = true;
         break;
  }

  lbl_assessments_title->Caption = " Assessment "
                                    + IntToStr(qryPwv->RecNo) + " of "
                                    + IntToStr(qryPwv->RecordCount);
}
//---------------------------------------------------------------------------
void __fastcall Tfrm_measure_pwv::EmptyControls()
{
  lbl_pat->Caption = "";

  rbtnCarotidA->Checked = true;
  rbtnFemoralB->Checked = true;

  rbtn10A->Checked = true;
  rbtn10B->Checked = true;

  edtSp->Text = "";
  edtMp->Text = "";
  edtDp->Text = "";

  edtDistance->Text = "";
  edtDistal->Text = "";
  edtProximal->Text = "";

  rgAlgorithm->ItemIndex = 2;
  edtPHPercent->Text = DEFAULT_PH_PERCENT;

  edtOperator->Text = "";
  edtMed->Lines->Clear();
  edtNotes->Lines->Clear();
  edtHeight->Text = "";
  edtWeight->Text = "";
  edtFeet->Text = "";
  edtInch->Text = "";
  edtPound->Text = "";
  chkbx_loopback->Checked = false;
  txtBmi->Caption = "";

  lbl_assessments_title->Caption = " Assessments";
}

//---------------------------------------------------------------------------
// Update current PWV object
//---------------------------------------------------------------------------
bool __fastcall Tfrm_measure_pwv::UpdatePwv()
{
  COMMS_ID_TYPE       port_id;

  port_id = config_get_comms_port();

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

  if (rbtn10A->Checked)
  {
      pwv->SiteA.Nof10s = 1;
  }
  else if (rbtn20A->Checked)
  {
      pwv->SiteA.Nof10s = 2;
  }
  else if (rbtn30A->Checked)
  {
      pwv->SiteA.Nof10s = 3;
  }

  if (rbtn10B->Checked)
  {
      pwv->SiteB.Nof10s = 1;
  }
  else if (rbtn20B->Checked)
  {
      pwv->SiteB.Nof10s = 2;
  }
  else if (rbtn30B->Checked)
  {
      pwv->SiteB.Nof10s = 3;
  }

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
  if (config_get_audit_option())
  {
      pwv->Operator = security_get_username();
  }
  else
  {
      pwv->Operator = edtOperator->Text;
  }
  // Distance
  pwv->Distance = 0;
  pwv->DistancePx = 0;
  pwv->DistanceDt = 0;

  capture_set_loopback(chkbx_loopback->Checked);

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
  {
     pwv->Bmi = txtBmi->Caption.ToDouble();
  }

  if (port_id == COMMS_PORT_SIMULATE)
  {
     pwv->Simulation = true;
  }
  else
  {
     pwv->Simulation = false;
  }
  pwv->Tonometer = config_get_tonometer();

  // Update the audit object
  pwv->AuditFlag = AUDIT_ORIGINAL;
  pwv->Reason = "";

  // Validation
  if (pwv->ValidateBeforeCalculate()==false)
  {
    if (edtSp->Enabled)
    {
      edtSp->SetFocus();
    }
    return false;
  }

  // If the audit option is set, a tonometer serial number must be entered
  // Otherwise display a warning and call the configuration form
  if (config_get_audit_option())
  {
      if(pwv->Tonometer == CONFIG_DEFAULT_TONOMETER)
      {
         MsgBox_show(TWARNING,
                    MSG_VALIDATION_ERROR,
                    LoadStr(MSG_SECURITY_TONOMETER),
                    MSG_SECURITY_TONOMETER, "");
         config_show();
         return false;
      }
  }

  // Success
  return true;
}
//---------------------------------------------------------------------------
void __fastcall Tfrm_measure_pwv::FormHide(TObject *Sender)
{
   if (grdMeas->DataSource)
   {
     grdMeas->DataSource->OnDataChange = NULL;
   }
   if (qryPwv != NULL)
   {
      qryPwv->Close();
   }
}
//---------------------------------------------------------------------------
void __fastcall Tfrm_measure_pwv::edtSpChange(TObject *Sender)
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
void __fastcall Tfrm_measure_pwv::edtMpChange(TObject *Sender)
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
void __fastcall Tfrm_measure_pwv::edtDpChange(TObject *Sender)
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
void __fastcall Tfrm_measure_pwv::FormKeyPress(TObject *Sender, char &Key)
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
void __fastcall Tfrm_measure_pwv::edtHeightChange(TObject *Sender)
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
void __fastcall Tfrm_measure_pwv::edtWeightChange(TObject *Sender)
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
void __fastcall Tfrm_measure_pwv::rgAlgorithmClick(TObject *Sender)
{
  edtPHPercent->Visible = rgAlgorithm->ItemIndex == 0;
}
//---------------------------------------------------------------------------
void __fastcall Tfrm_measure_pwv::edtDistanceChange(TObject *Sender)
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
void __fastcall Tfrm_measure_pwv::edtDistalChange(TObject *Sender)
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
void __fastcall Tfrm_measure_pwv::edtProximalChange(TObject *Sender)
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
void __fastcall Tfrm_measure_pwv::CalcDistance()
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
void __fastcall Tfrm_measure_pwv::edtDistanceKeyPress(TObject *Sender,
      char &Key)
{
  edtDistal->Text = "";
  edtProximal->Text = "";
}
//---------------------------------------------------------------------------




void __fastcall Tfrm_measure_pwv::edtFeetChange(TObject *Sender)
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

void __fastcall Tfrm_measure_pwv::edtInchChange(TObject *Sender)
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

void __fastcall Tfrm_measure_pwv::edtPoundChange(TObject *Sender)
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
 ** meas_pwv_emr_mode()
 **
 ** DESCRIPTION
 **  Displays the study data specified by the EMR object
 ** INPUT
 **  Measure PWV Form
 ** OUTPUT
 **  None
 ** RETURN
 **  Boolean - success or not
*/
//---------------------------------------------------------------------------
bool meas_pwv_emr_mode(void)
{
   EMR_RECORD_TYPE      emr;
   bool                 success = false;

   frm_measure_pwv->edtDp->ReadOnly = false;
   frm_measure_pwv->edtSp->ReadOnly = false;
   frm_measure_pwv->edtMp->ReadOnly = false;
   frm_measure_pwv->edtMed->ReadOnly = false;
   frm_measure_pwv->edtNotes->ReadOnly = false;
   frm_measure_pwv->edtOperator->ReadOnly = false;
   frm_measure_pwv->edtFeet->ReadOnly = false;
   frm_measure_pwv->edtInch->ReadOnly = false;
   frm_measure_pwv->edtPound->ReadOnly = false;
   frm_measure_pwv->edtHeight->ReadOnly = false;
   frm_measure_pwv->edtWeight->ReadOnly = false;

   // Populate the study fields if the EMR patient is active
   if (emr_patient_is_active())
   {
      if (emr_get(&emr))
      {
         if (emr.dp != DEFAULT_VALUE)
         {
            frm_measure_pwv->edtDp->Text = IntToStr(emr.dp);
            if (!emr_get_editing())
            {
               // If DP has a value, then MP or SP will also have a value
               frm_measure_pwv->edtDp->ReadOnly = true;
               frm_measure_pwv->edtSp->ReadOnly = true;
               frm_measure_pwv->edtMp->ReadOnly = true;
            }
         }
         if (emr.sp != DEFAULT_VALUE)
         {
            frm_measure_pwv->edtSp->Text = IntToStr(emr.sp);
         }
         if (emr.mp != DEFAULT_VALUE)
         {
            frm_measure_pwv->edtMp->Text = IntToStr(emr.mp);
         }

         if (emr.medication != "")
         {
            frm_measure_pwv->edtMed->Text = emr.medication;
            if (!emr_get_editing())
            {
               frm_measure_pwv->edtMed->ReadOnly = true;
            }
         }
         if (emr.study_notes != "")
         {
            frm_measure_pwv->edtNotes->Text = emr.study_notes;
            if (!emr_get_editing())
            {
               frm_measure_pwv->edtNotes->ReadOnly = true;
            }
         }
         if (emr.operator_name != "")
         {
            frm_measure_pwv->edtOperator->Text = emr.operator_name;
            if (!emr_get_editing())
            {
               frm_measure_pwv->edtOperator->ReadOnly = true;
            }
         }
         // When the imperial values are populated, they automatically calculate
         // the nearest metric equivalent. So for accuracy, make sure the metric
         // values are populated last so they overwrite these values
         if (emr.feet != DEFAULT_VALUE)
         {
            frm_measure_pwv->edtFeet->Text = emr.feet;
            if (!emr_get_editing())
            {
               frm_measure_pwv->edtFeet->ReadOnly = true;
            }
         }
         if (emr.inch != DEFAULT_VALUE)
         {
            frm_measure_pwv->edtInch->Text = emr.inch;
            if (!emr_get_editing())
            {
               frm_measure_pwv->edtInch->ReadOnly = true;
            }
         }
         if (emr.pound != DEFAULT_VALUE)
         {
            frm_measure_pwv->edtPound->Text = emr.pound;
            if (!emr_get_editing())
            {
               frm_measure_pwv->edtPound->ReadOnly = true;
            }
         }
         if (emr.height != DEFAULT_VALUE)
         {
            frm_measure_pwv->edtHeight->Text = emr.height;
            if (!emr_get_editing())
            {
               frm_measure_pwv->edtHeight->ReadOnly = true;
            }
         }
         if (emr.weight != DEFAULT_VALUE)
         {
            frm_measure_pwv->edtWeight->Text = emr.weight;
            if (!emr_get_editing())
            {
               frm_measure_pwv->edtWeight->ReadOnly = true;
            }
         }
         success = true;
      }
   }
   return success;
}
void __fastcall Tfrm_measure_pwv::bbtn_captureClick(TObject *Sender)
{
   TDataSet   *pwv_table;
   bool       status;

   status = false;
   try
   {
      // If the audit option is set, the user must sign in
      if (security_show())
      {
         if (UpdatePwv() == false)
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

      if (capture_show_form(MEAS_PWV_ID) == true)
      {
         pnlGrid->Enabled = false;
         pnlFields->Visible = false;
         pnlWait->Visible = true;
         Screen->Cursor = crHourGlass;
         lblStatus->Caption = "Calculating Results";
         Application->ProcessMessages();
         if (pwv->Calculate())
         {
            lblStatus->Caption = "Opening Pulse Wave Velocity Database";
            if (dbmgr_open(DBMGR_MEASURE_PWV_TABLE, false))
            {
               pwv_table = dbmgr_get_dataset(DBMGR_MEASURE_PWV_TABLE, false);
               lblStatus->Caption = "Saving Results to Database";
               Application->ProcessMessages();
               try
               {
                  if (pwv_table != NULL)
                  {
                     pwv_table->Insert();
                  }
               }
               catch (Exception &exception)
               {
                  dbmgr_close(DBMGR_MEASURE_PWV_TABLE, false);
                  Screen->Cursor = crDefault;
                  pnlWait->Visible = false;
                  pnlGrid->Enabled = true;
                  pnlFields->Visible = true;
                  bbtn_capture->Enabled = true;
                  MsgBox(TERROR,
                         GetCurrentPwvMeasureDetails(),
                         MSG_DBREADWRITE_ERROR,
                         MSG_DBREADWRITE_ERROR,
                         exception.Message);
                    return;
               }
               if (pwv_table != NULL)
               {
                  status = pwv->Store(pwv_table, true, true);
               }
               dbmgr_close(DBMGR_MEASURE_PWV_TABLE, false);
               if (status)
               {
                  lblStatus->Caption = "Generating Report Information";
                  Application->ProcessMessages();
                  patient_update_measurement_count((short)(qryPwv->RecordCount + 1));
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
                  frm_main->spdbtn_reportClick(Sender);
               }
               else
               {
                  lblStatus->Caption = "Failed to Save the Report.";
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
            pwv->SaveToFile();
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
         bbtn_capture->Enabled = true;
         //SetFocus();
      }
   }
   catch (Exception &exception)
   {
      MsgBox("Report generation status is unknown.\n\nClose SphygmoCor, restart and check whether the report has been saved in the database.",
             SNOTIFICATION,
             MB_ICONSTOP | MB_OK);
      log_write(SWARNING + exception.Message);
   }
   Screen->Cursor = crDefault;
   pnlWait->Visible = false;
   pnlGrid->Enabled = true;
   pnlFields->Visible = true;
   bbtn_capture->Enabled = true;
}
//---------------------------------------------------------------------------

