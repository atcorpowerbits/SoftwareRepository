#include <vcl.h>
#include <vcl/dstring.h>
//---------------------------------------------------------------------------
#pragma hdrstop
//---------------------------------------------------------------------------
#include <stdlib.h>
#include <math.h>
#include <dbmgr/pubserv.h>
#include <multdb/pubserv.h>
#include <log/pubserv.h>
#include <patient/pubserv.h>
#include <meas/pubserv.h>
#include <msg/pubserv.h>
#include <config/pubserv.h>
#include <print/pubserv.h>
#include <export/pubserv.h>
#include <scor/form_main.h>
#include <report/pubserv.h>
#include <cfr11/pubserv.h>
#include <emr/pubserv.h>
#include <scor/utils.h>
#include "report.h"
#include "attrib.h"
#include "form_report_pwa.h"
#include "form_report_pwv.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
//---------------------------------------------------------------------------
Tfrm_report_pwv *frm_report_pwv;
const int REPORT_PANEL_CANVAS_PRINT_HEIGHT = 449;
const int REPORT_PANEL_CANVAS_PRINT_WIDTH = 650;
const int REPORT_PANEL_PARAMS_PRINT_HEIGHT = 80;
float       pwv_coeff_1_male = 0.0013;
float       pwv_coeff_2_male = -0.034;
float       pwv_y_intercept_male = 5.7;
float       pwv_coeff_1_female = 0.0013;
float       pwv_coeff_2_female = -0.034;
float       pwv_y_intercept_female = 5.7;
float       pwv_coeff_1 = 0.0;
float       pwv_coeff_2 = 0.0;
float       pwv_y_intercept = 0.0;
float       pwv_confidence_90_offset_male = 2.078;
float       pwv_confidence_90_offset_female = 2.078;
float       pwv_confidence_90_offset = 0.0;
bool        pwv_audit_mode = false;

bool report_pwv_batch_print(TPWV                *pwv_info,
                            PATIENT_RECORD_TYPE *patient)
{
   // If the PWV form has not been created we need to create it.
   (void)report_get_form_pointer();

   if (frm_report_pwv == NULL)
   {
      return false;
   }
   frm_report_pwv->report_pwv = pwv_info;

   frm_report_pwv->ClearSeries();
   frm_report_pwv->ClearResults();


   patient_set(patient);
   report_age = 0;
   frm_report_pwv->report_display_study();
   frm_report_pwv->report_display_signal(frm_report_pwv->ChartAP,
                                         frm_report_pwv->ChartAE,
                                         frm_report_pwv->ChartDT,
                                         &frm_report_pwv->report_pwv->SiteA,
                                         "Site A",
                                         frm_report_pwv->report_pwv->SampleRate);
   frm_report_pwv->report_display_signal(frm_report_pwv->ChartBP,
                                         frm_report_pwv->ChartBE,
                                         frm_report_pwv->ChartDT,
                                         &frm_report_pwv->report_pwv->SiteB,
                                         "Site B",
                                         frm_report_pwv->report_pwv->SampleRate);
   frm_report_pwv->report_display_quality();
   frm_report_pwv->report_display_params();
   frm_report_pwv->bbtn_printClick(Application);

   return true;
}

//---------------------------------------------------------------------------
__fastcall Tfrm_report_pwv::Tfrm_report_pwv(TComponent* Owner)
    : Child_Form(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall Tfrm_report_pwv::FormShow(TObject *Sender)
{
   TDataSource          *dsrc_report;
   PATIENT_RECORD_TYPE  pat;

   report_pwv = meas_get_current_pwv();
   ClearSeries();
   ClearResults();
   report_age = 0;
   if (patient_get(&pat))
   {
      dsrc_report = dbmgr_get_data_source(DBMGR_MEASURE_PWV_QUERY, false);
      dsrc_report->AutoEdit = false;

      report_qry = dbmgr_setup_query(DBMGR_MEASURE_PWV_TABLE,
                                     DBMGR_QUERY_KEY,
                                     PATIENT_SYSTEM_ID,
                                     PATIENT_STUDY_ID,
                                     PATIENT_NO,
                                     pat.system_id,
                                     pat.study_id,
                                     IntToStr(pat.number),
                                     MPW_DATETIME);
                                     
      if ((report_qry != NULL) && report_qry->RecordCount > 0)
      {
         grd_report->DataSource = dsrc_report;
         //nvg_report->DataSource = dsrc_report;

         report_display_patient_info(&pat);

         dsrc_report->OnDataChange = record_changed;
         report_qry->Last();
      }
      else
      {
         MsgBox(MSG_NO_REPORTS_TO_DISPLAY, SNOTIFICATION, MB_ICONINFORMATION);
      }
   }

   // If the audit option is set, disable export
   if (config_get_audit_option())
   {
      bbtn_export->Enabled = false;
   }

   // PM V9
   // Only the Intersecting Tangents algorithm is used in Clinical mode
   if (config_get_clinical_option())
   {
      lblAlg->Visible = false;
      lblAlg_title->Visible = false;
   }
   else
   {
      lblAlg->Visible = true;
      lblAlg_title->Visible = true;
   }

   grdRes->Col = 1;
   grdRes->Row = 3;
   grdRes->Cells[0][0] = "Site A-B";
   grdRes->Cells[1][0] = "MeanT(ms)";
   grdRes->Cells[2][0] = " SD(ms)";
   grdRes->Cells[3][0] = " N";
   grdRes->Cells[4][0] = "HR(bpm)";

   bbtn_print->Enabled = print_does_printer_exist();

   // PM V9 CR
   // If the EMR patient is active or default EMR mode is set - show the
   // Export All button
   // Make sure this is at the end of Show Form as this may shutdown the
   // software, if specified by the EMR object
   if (emr_patient_is_active() || emr_get_default_mode())
   {
      mnu_all->Visible = true;

      // If report export is enabled, perform an Export All and disable report export
      if (emr_get_report_export())
      {
         mnu_allClick(Sender);
         emr_set_report_export(false);
      }
   }
   else
   {
      mnu_all->Visible = false;
   }

   pdf_file = "";
   grd_report->SetFocus();
}
//---------------------------------------------------------------------------
void __fastcall Tfrm_report_pwv::FormHide(TObject *Sender)
{
   if (grd_report->DataSource != NULL)
   {
      grd_report->DataSource->OnDataChange = NULL;
   }
   if (report_qry != NULL)
   {
      report_qry->Close();
   }
   ClearSeries();
   ClearResults();

   emma_display_statusbar_message("", "", "", sphygmocor_white);
   emma_display_statusbar_message("", "", sphygmocor_white);
}
//---------------------------------------------------------------------------
void __fastcall Tfrm_report_pwv::record_changed(TObject *Sender, TField  *Field)
{
  // In audit mode, query the PWV audit table, otherwise query the PWV table
  if (pwv_audit_mode)
  {
      report_qry = (TADOQuery *)dbmgr_get_dataset(DBMGR_MEASURE_PWV_AUDIT_QUERY, false);
  }
  else
  {
      report_qry = (TADOQuery *)dbmgr_get_dataset(DBMGR_MEASURE_PWV_QUERY, false);
  }

  if (report_qry != NULL)
  {
    if (report_qry->RecordCount > 0)
    {
       ClearSeries();
       ClearResults();
       if (report_pwv->Populate(report_qry)==true)
       {
          lbl_assessments_title->Caption = " Assessment "
                                                      + IntToStr(report_qry->RecNo) + " of "
                                                      + IntToStr(report_qry->RecordCount);
          bbtn_print->Enabled = true;
          bbtn_modify->Enabled = true;
          report_display_study();
          report_display_signal(ChartAP, ChartAE, ChartDT, &report_pwv->SiteA, "Site A", report_pwv->SampleRate);
          report_display_signal(ChartBP, ChartBE, ChartDT, &report_pwv->SiteB, "Site B", report_pwv->SampleRate);
          report_display_quality();
          report_display_params();
          report_display_pwv_normals();
       }
       else
       {
          bbtn_print->Enabled = false;
          bbtn_modify->Enabled = false;
       }
    }
  }
}
//---------------------------------------------------------------------------
void Tfrm_report_pwv::ClearSeries()
{
  for (int np = 0; np < ChartAP->SeriesCount(); np++)
  {
    ChartAP->Series[np]->Clear();
  }
  for (int np = 0; np < ChartAE->SeriesCount(); np++)
  {
    ChartAE->Series[np]->Clear();
  }
  for (int np = 0; np < ChartDT->SeriesCount(); np++)
  {
    ChartDT->Series[np]->Clear();
  }
  for (int np = 0; np < ChartBP->SeriesCount(); np++)
  {
    ChartBP->Series[np]->Clear();
  }
  for (int np = 0; np < ChartBE->SeriesCount(); np++)
  {
    ChartBE->Series[np]->Clear();
  }

  ChartAP->Title->Text->Strings[0] = "Site A";
  ChartAP->LeftAxis->Minimum = 0;
  ChartAP->LeftAxis->Maximum = ChartAP->LeftAxis->Minimum;
  ChartAE->LeftAxis->Minimum = -10000;
  ChartAE->LeftAxis->Maximum = ChartAE->LeftAxis->Minimum;
  ChartBP->Title->Text->Strings[0] = "Site B";
  ChartBP->LeftAxis->Minimum = 0;
  ChartBP->LeftAxis->Maximum = ChartBP->LeftAxis->Minimum;
  ChartBE->LeftAxis->Minimum = -10000;
  ChartBE->LeftAxis->Maximum = ChartBE->LeftAxis->Minimum;
}
//---------------------------------------------------------------------------
void Tfrm_report_pwv::ClearResults()
{
  lblQC_PH_AT->Caption = "";
  lblQC_PHV_AT->Caption = "";
  lblQC_PLV_AT->Caption = "";
  lblQC_BLV_AT->Caption = "";
  lblQC_PH_BT->Caption = "";
  lblQC_PHV_BT->Caption = "";
  lblQC_PLV_BT->Caption = "";
  lblQC_BLV_BT->Caption = "";

  lblQC_PH_AE->Caption = "";
  lblQC_PHV_AE->Caption = "";
  lblQC_PLV_AE->Caption = "";
  lblQC_BLV_AE->Caption = "";
  lblQC_PH_BE->Caption = "";
  lblQC_PHV_BE->Caption = "";
  lblQC_PLV_BE->Caption = "";
  lblQC_BLV_BE->Caption = "";

  lbl_dist->Caption = "";
  lblPWV->Caption = "";

  for (int col=0; col < grdRes->ColCount; col++)
  for (int row=1; row < grdRes->RowCount; row++)
  grdRes->Cells[col][row] = "";

  lbl_date->Caption = "";
  lbl_time->Caption = "";
  edt_med->Text = "";
  edt_notes->Text = "";
  lbl_operator->Caption = "";
  lbl_hwbmi->Caption = "";
  lblSpDpMp->Caption = "";
  lblAlg->Caption = "";
}
//---------------------------------------------------------------------------
void __fastcall Tfrm_report_pwv::pnlABResize(TObject *Sender)
{
  pnlA->Height = pnlAB->Height/2 - 1;    
}
//---------------------------------------------------------------------------
void Tfrm_report_pwv::report_display_patient_info(PATIENT_RECORD_TYPE  *pat)
{
  lbl_pname->Caption = patient_get_name();
  lbl_pid->Caption = pat->id;
  lbl_pcode->Caption = pat->code;
  lbl_address1->Caption = pat->street;
  lbl_address2->Caption = pat->suburb + " " + pat->state + " " + pat->pcode;
  lbl_address3->Caption = pat->country;
  lbl_birth_date->Caption = pat->dob.FormatString(REPORT_PAT_DOB_DATE_FORMAT);
  lbl_sex->Caption = pat->sex;
}
//---------------------------------------------------------------------------
void Tfrm_report_pwv::report_display_study()
{
   String S;

   lbl_date->Caption = report_pwv->DateTime.FormatString(REPORT_PAT_DOB_DATE_FORMAT);
   lbl_time->Caption = report_pwv->DateTime.TimeString();

   report_age = patient_get_age_at_date(report_pwv->DateTime);
   lbl_age->Caption = IntToStr(report_age);

   edt_med->Text = MsgBox_ReplaceCarriage(report_pwv->Medication.SubString(1, REPORT_MAX_PRINTED_MEMO_LENGTH));
   edt_notes->Text = MsgBox_ReplaceCarriage(report_pwv->Notes.SubString(1, REPORT_MAX_PRINTED_MEMO_LENGTH));
   lbl_operator->Caption = report_pwv->Operator;
   if (report_pwv->Height > 0 && report_pwv->Height != DEFAULT_VALUE &&
       report_pwv->Weight > 0 && report_pwv->Weight != DEFAULT_VALUE &&
       report_pwv->Bmi > 0 && report_pwv->Bmi != DEFAULT_VALUE &&
       config_get_system_locale() == CONFIG_DEFAULT_LOCALE)
   {
     lbl_hwbmi->Caption = RoundIntToStr(report_pwv->Height) + "cm, " +
                                   RoundIntToStr(report_pwv->Weight) + "kg (" +
                                   FormatFloat("0.0#", report_pwv->Bmi) + "kg/m²)";
   }
   else if (report_pwv->Height > 0 && report_pwv->Height != DEFAULT_VALUE &&
         config_get_system_locale() == CONFIG_DEFAULT_LOCALE)
   {
      // Set bmi captions
     lbl_hwbmi->Caption = RoundIntToStr(report_pwv->Height) + "cm";
   }
   else if (report_pwv->Weight > 0 && report_pwv->Weight != DEFAULT_VALUE &&
         config_get_system_locale() == CONFIG_DEFAULT_LOCALE)
   {
      // Set bmi captions
     lbl_hwbmi->Caption = RoundIntToStr(report_pwv->Weight) + "kg";
   }
   else if (report_pwv->Feet >= 0 && report_pwv->Feet != DEFAULT_VALUE &&
            report_pwv->Inch >= 0 && report_pwv->Inch != DEFAULT_VALUE &&
            report_pwv->Pound > 0 && report_pwv->Pound != DEFAULT_VALUE &&
            report_pwv->Bmi > 0 && report_pwv->Bmi != DEFAULT_VALUE &&
            config_get_system_locale() == CONFIG_IMPERIAL_LOCALE)
   {
      // Set bmi captions
     lbl_hwbmi->Caption = RoundIntToStr(report_pwv->Feet) + "ft, " +
                                        RoundIntToStr(report_pwv->Inch) + "in, " +
                                        RoundIntToStr(report_pwv->Pound) + "lb (" +
                                        FormatFloat("0.##", report_pwv->Bmi) + " kg/m²)";
   }
   else if (report_pwv->Feet >= 0 && report_pwv->Feet != DEFAULT_VALUE &&
            report_pwv->Inch >= 0 && report_pwv->Inch != DEFAULT_VALUE &&
            config_get_system_locale() == CONFIG_IMPERIAL_LOCALE)
   {
      // Set bmi captions
     lbl_hwbmi->Caption = RoundIntToStr(report_pwv->Feet) + "ft, " +
                                        RoundIntToStr(report_pwv->Inch) + "in";
   }
   else if (report_pwv->Pound > 0 && report_pwv->Pound != DEFAULT_VALUE &&
            config_get_system_locale() == CONFIG_IMPERIAL_LOCALE)
   {
      // Set bmi captions
     lbl_hwbmi->Caption = RoundIntToStr(report_pwv->Pound) + "lb";
   }
   else
   {
     lbl_hwbmi->Caption = "";
   }
   // Sp, Dp, Mp
   if (report_pwv->Sp > 0 && report_pwv->Sp != DEFAULT_VALUE &&
      report_pwv->Dp > 0 && report_pwv->Dp != DEFAULT_VALUE)
   {
      lblSpDpMp->Caption = RoundIntToStr(report_pwv->Sp) + "/" +
                           RoundIntToStr(report_pwv->Dp) + " (-)";
   }
   else if (report_pwv->MeanP > 0 && report_pwv->MeanP != DEFAULT_VALUE &&
            report_pwv->Dp > 0 && report_pwv->Dp != DEFAULT_VALUE)
   {
      lblSpDpMp->Caption = "-/" + RoundIntToStr(report_pwv->Dp) + " (" +
                           RoundIntToStr(report_pwv->MeanP) + ")";
   }
   else
   {
      lblSpDpMp->Caption = "";
   }
   // Algorithm
   if (report_pwv->Algorithm == 1)
     lblAlg->Caption = "Pulse Height percent (" + IntToStr((int)report_pwv->PHeightPercent) + "%)";
   else if (report_pwv->Algorithm == 2)
     lblAlg->Caption = "Max 1st derivative";
   else if (report_pwv->Algorithm == 3)
     lblAlg->Caption = "Intersecting tangent";
   else if (report_pwv->Algorithm == 4)
     lblAlg->Caption = "Max 2nd derivative";
   else
     lblAlg->Caption = "";

   // PM V9
   // The simulation label is displayed on the status bar
   if (report_pwv->Simulation)
   {
      emma_display_statusbar_message(SIMULATION, SIMULATION_NOTE, sphygmocor_maroon);
   }
   else
   {
      emma_display_statusbar_message("", "", sphygmocor_white);
   }
   lbl_reason_title->Visible = false;
   lbl_reason->Visible = false;

   // If the audit option is set, display audit parameters.
   if (config_get_audit_option())
   {
      S =  report_pwv->Operator;
      lbl_operator_title->Caption = AUDIT_NO_CAPTION;
      lbl_operator_title->Font->Color = sphygmocor_black;
      lbl_operator->Font->Color = sphygmocor_navy;
      // If there is a reason for change, display it.
      if (report_pwv->Reason.Length() != 0)
      {
         lbl_reason->Caption = MsgBox_ReplaceCarriage(report_pwv->Reason);
         lbl_reason_title->Visible = true;
         lbl_reason->Visible = true;
      }

      switch (report_pwv->AuditFlag)
      {
         // The original report can be printed and deleted but has no audit trail
         case AUDIT_ORIGINAL:
            if (S.Length())
            {
               lbl_operator_title->Caption = AUDIT_ORIGINAL_CAPTION;
               lbl_operator_title->Font->Color = sphygmocor_navy;
            }
            bbtn_audit->Visible = false;
            bbtn_print->Enabled = true;
            bbtn_delete->Enabled = true;
            bbtn_createpwa->Enabled = true;
            break;
         // The modified report can be printed and deleted and the audit trail can be viewed
         case AUDIT_MODIFIED:
            if (S.Length())
            {
               lbl_operator_title->Caption = AUDIT_MODIFIED_CAPTION;
               lbl_operator_title->Font->Color = sphygmocor_orange;
               lbl_operator->Font->Color = sphygmocor_orange;
            }
            bbtn_audit->Visible = true;
            bbtn_print->Enabled = true;
            bbtn_delete->Enabled = true;
            bbtn_createpwa->Enabled = true;
            break;
         // The deleted report cannot be deleted nor printed but the audit trail can be viewed
         case AUDIT_DELETED:
            if (S.Length())
            {
               lbl_operator_title->Caption = AUDIT_DELETED_CAPTION;
               lbl_operator_title->Font->Color = sphygmocor_red;
               lbl_operator->Font->Color = sphygmocor_red;
            }
            bbtn_audit->Visible = true;
            bbtn_print->Enabled = false;
            bbtn_delete->Enabled = false;
            bbtn_createpwa->Enabled = false;
            break;
      }

      // In audit mode, reports cannot be deleted and the audit button returns to the report screen
      if (pwv_audit_mode)
      {
         bbtn_audit->Visible = true;
         bbtn_delete->Enabled = false;
         bbtn_createpwa->Enabled = false;
      } 
   }
   else
   {
      bbtn_audit->Visible = false;
   }

   // Only display the tonometer labels if it does not have the default value
   if (report_pwv->Tonometer == CONFIG_DEFAULT_TONOMETER)
   {
      lbl_tonometer_title->Visible = false;
      lbl_tonometer->Visible = false;
   }
   else
   {
      lbl_tonometer_title->Visible = true;
      lbl_tonometer->Visible = true;
      lbl_tonometer->Caption = IntToStr(report_pwv->Tonometer);
   }
}
//---------------------------------------------------------------------------
void Tfrm_report_pwv::report_display_signal(TChart *ChartP, TChart *ChartE,
                                            TChart *ChartDT, TPWVSite* pSite,
                                            String pSiteTitle, const int pSampleRate)
{
  TPointSeries *ton_onsets = dynamic_cast<TPointSeries *>(ChartP->Series[1]);
  TPointSeries *ecg_onsets = dynamic_cast<TPointSeries *>(ChartE->Series[1]);
  TPointSeries *dt_series = dynamic_cast<TPointSeries *>(ChartDT->Series[0]);
  TPointSeries *ton_neg_onsets = dynamic_cast<TPointSeries *>(ChartP->Series[2]);
  TPointSeries *ecg_neg_onsets = dynamic_cast<TPointSeries *>(ChartE->Series[2]);
  TPointSeries *dt_neg_series = dynamic_cast<TPointSeries *>(ChartDT->Series[1]);
  if (ton_onsets==NULL || ecg_onsets==NULL || dt_series==NULL ||
      ton_neg_onsets==NULL || ecg_neg_onsets==NULL || dt_neg_series==NULL)
  {
    return;
  }

  ChartP->Title->Text->Strings[0] = pSiteTitle + " - " + PWVMTypeAsString[pSite->MeasureType];
  ecg_onsets->Pointer->Style = psCircle;
  ton_onsets->Pointer->Style = psCircle;
  dt_series->Pointer->Style = psCircle;
  // Signals
  for (int k = 0; k < pSite->Tonom.NofPoints; k++)
  {
    ChartP->Series[0]->AddXY(float(k)/pSampleRate, pSite->Tonom.Signal[k], "", clTeeColor);
  }
  for (int k = 0; k < pSite->ECG.NofPoints; k++)
  {
    ChartE->Series[0]->AddXY(float(k)/pSampleRate, pSite->ECG.Signal[k], "", clTeeColor);
  }

  //float y;
  for (int k = 0; k < pSite->Tonom.NofOnsets; k++)
  {
    float y = math_FunctionValue(pSite->Tonom.Signal, pSite->Tonom.NofPoints, fabs(pSite->Tonom.FloatOnsets[k]));
    if (pSite->Tonom.FloatOnsets[k]>0)
      ton_onsets->AddXY(fabs(pSite->Tonom.FloatOnsets[k])/pSampleRate, y, "", clTeeColor);
    else
      ton_neg_onsets->AddXY(fabs(pSite->Tonom.FloatOnsets[k])/pSampleRate, y, "", clTeeColor);
  }
  for (int k = 0; k < pSite->ECG.NofOnsets; k++)
  {
    float y = math_FunctionValue(pSite->ECG.Signal, pSite->ECG.NofPoints, fabs(pSite->ECG.FloatOnsets[k]));
    if (pSite->ECG.FloatOnsets[k]>0)
      ecg_onsets->AddXY(fabs(pSite->ECG.FloatOnsets[k])/pSampleRate, y /*lAEMin*/ ,"", clTeeColor);
    else
      ecg_neg_onsets->AddXY(fabs(pSite->ECG.FloatOnsets[k])/pSampleRate, y /*lAEMin*/ ,"", clTeeColor);
  }

  ChartP->BottomAxis->Minimum = 0;
  ChartP->BottomAxis->Maximum = max(ChartP->Series[0]->MaxXValue(), ChartE->Series[0]->MaxXValue());
  ChartP->LeftAxis->Minimum = 0;
  ChartP->LeftAxis->Maximum = ChartP->Series[0]->MaxYValue() + 10;
  ChartP->LeftAxis->Minimum = ChartP->Series[0]->MinYValue() - 10;

  ChartE->BottomAxis->Minimum = 0;
  ChartE->BottomAxis->Maximum = max(ChartP->Series[0]->MaxXValue(), ChartE->Series[0]->MaxXValue());
  ChartE->LeftAxis->Minimum = -10000;
  ChartE->LeftAxis->Maximum = ChartE->Series[0]->MaxYValue() + 10;
  ChartE->LeftAxis->Minimum = ChartE->Series[0]->MinYValue() - 10;

  // DeltaT Series
  for (int k = 0; k < pSite->NofDT; k++)
  {
    if (pSite->DeltaT[k].Valid)
      dt_series->AddXY(k, pSite->DeltaT[k].Value, "", clTeeColor);
    else
      dt_neg_series->AddXY(k, pSite->DeltaT[k].Value, "", clTeeColor);
  }
  ChartDT->LeftAxis->Minimum = 0;
  ChartDT->LeftAxis->Maximum = max(dt_series->MaxYValue(), dt_neg_series->MaxYValue()) + 30;
  ChartDT->LeftAxis->Minimum = min(dt_series->MinYValue(), dt_neg_series->MinYValue()) - 30;
}
//---------------------------------------------------------------------------
void Tfrm_report_pwv::report_display_quality()
{
  if (report_pwv->SiteA.Tonom.QC_PulseHeight < DEFAULT_VALUE)
  {
    lblQC_PH_AT->Caption = FormatFloat("##0", report_pwv->SiteA.Tonom.QC_PulseHeight);
  }
  else
  {
    lblQC_PH_AT->Caption = "?";
  }

  if (report_pwv->SiteA.Tonom.QC_PulseHeightVariation < DEFAULT_VALUE)
  {
    lblQC_PHV_AT->Caption = FormatFloat("#0", report_pwv->SiteA.Tonom.QC_PulseHeightVariation);
  }
  else
  {
    lblQC_PHV_AT->Caption = "?";
  }

  if (report_pwv->SiteA.Tonom.QC_PulseLengthVariation < DEFAULT_VALUE)
  {
    lblQC_PLV_AT->Caption = FormatFloat("#0", report_pwv->SiteA.Tonom.QC_PulseLengthVariation);
  }
  else
  {
    lblQC_PLV_AT->Caption = "?";
  }

  if (report_pwv->SiteA.Tonom.QC_BaseLineVariation < DEFAULT_VALUE)
  {
    lblQC_BLV_AT->Caption = FormatFloat("#0", report_pwv->SiteA.Tonom.QC_BaseLineVariation);
  }
  else
  {
    lblQC_BLV_AT->Caption = "?";
  }

  // Site B
  if (report_pwv->SiteB.Tonom.QC_PulseHeight < DEFAULT_VALUE)
  {
    lblQC_PH_BT->Caption = FormatFloat("##0", report_pwv->SiteB.Tonom.QC_PulseHeight);
  }
  else
  {
    lblQC_PH_BT->Caption = "?";
  }

  if (report_pwv->SiteB.Tonom.QC_PulseHeightVariation < DEFAULT_VALUE)
  {
    lblQC_PHV_BT->Caption = FormatFloat("#0", report_pwv->SiteB.Tonom.QC_PulseHeightVariation);
  }
  else
  {
    lblQC_PHV_BT->Caption = "?";
  }

  if (report_pwv->SiteB.Tonom.QC_PulseLengthVariation < DEFAULT_VALUE)
  {
    lblQC_PLV_BT->Caption = FormatFloat("#0", report_pwv->SiteB.Tonom.QC_PulseLengthVariation);
  }
  else
  {
    lblQC_PLV_BT->Caption = "?";
  }

  if (report_pwv->SiteB.Tonom.QC_BaseLineVariation < DEFAULT_VALUE)
  {
    lblQC_BLV_BT->Caption = FormatFloat("#0", report_pwv->SiteB.Tonom.QC_BaseLineVariation);
  }
  else
  {
    lblQC_BLV_BT->Caption = "?";
  }
  
  if (report_pwv->SiteA.ECG.QC_PulseHeight < DEFAULT_VALUE)
    lblQC_PH_AE->Caption = FormatFloat("##0", report_pwv->SiteA.ECG.QC_PulseHeight);
  else
    lblQC_PH_AE->Caption = "?";

  if (report_pwv->SiteA.ECG.QC_PulseHeightVariation < DEFAULT_VALUE)
    lblQC_PHV_AE->Caption = FormatFloat("##0", report_pwv->SiteA.ECG.QC_PulseHeightVariation);
  else
    lblQC_PHV_AE->Caption = "?";

  if (report_pwv->SiteA.ECG.QC_PulseLengthVariation < DEFAULT_VALUE)
    lblQC_PLV_AE->Caption = FormatFloat("##0", report_pwv->SiteA.ECG.QC_PulseLengthVariation);
  else
    lblQC_PLV_AE->Caption = "?";

  if (report_pwv->SiteA.ECG.QC_BaseLineVariation < DEFAULT_VALUE)
    lblQC_BLV_AE->Caption = FormatFloat("##0", report_pwv->SiteA.ECG.QC_BaseLineVariation);
  else
    lblQC_BLV_AE->Caption = "?";

  if (report_pwv->SiteB.ECG.QC_PulseHeight < DEFAULT_VALUE)
    lblQC_PH_BE->Caption = FormatFloat("##0", report_pwv->SiteB.ECG.QC_PulseHeight);
  else
    lblQC_PH_BE->Caption = "?";

  if (report_pwv->SiteB.ECG.QC_PulseHeightVariation < DEFAULT_VALUE)
    lblQC_PHV_BE->Caption = FormatFloat("##0", report_pwv->SiteB.ECG.QC_PulseHeightVariation);
  else
    lblQC_PHV_BE->Caption = "?";

  if (report_pwv->SiteB.ECG.QC_PulseLengthVariation < DEFAULT_VALUE)
    lblQC_PLV_BE->Caption = FormatFloat("##0", report_pwv->SiteB.ECG.QC_PulseLengthVariation);
  else
    lblQC_PLV_BE->Caption = "?";

  if (report_pwv->SiteB.ECG.QC_BaseLineVariation < DEFAULT_VALUE)
    lblQC_BLV_BE->Caption = FormatFloat("##0", report_pwv->SiteB.ECG.QC_BaseLineVariation);
  else
    lblQC_BLV_BE->Caption = "?";
}
//---------------------------------------------------------------------------
void Tfrm_report_pwv::report_display_params()
{
   float PWVSD = 0.0;
   TFontStyles quality_font_style;
   quality_font_style.Clear();

   grdRes->Cells[0][1] = "ECG-" + PWVMTypeAsString[report_pwv->SiteA.MeasureType].SubString(1,3);
   grdRes->Cells[1][1] = FormatFloat("##0.0", report_pwv->SiteA.MeanDT);
   grdRes->Cells[2][1] = FormatFloat("#0.0", report_pwv->SiteA.Deviation);
   grdRes->Cells[3][1] = IntToStr(report_pwv->SiteA.NofValidDT);
   grdRes->Cells[4][1] = RoundIntToStr(report_pwv->SiteA.HeartRate);

   grdRes->Cells[0][2] = "ECG-" + PWVMTypeAsString[report_pwv->SiteB.MeasureType].SubString(1,3);
   grdRes->Cells[1][2] = FormatFloat("##0.0", report_pwv->SiteB.MeanDT);
   grdRes->Cells[2][2] = FormatFloat("#0.0", report_pwv->SiteB.Deviation);
   grdRes->Cells[3][2] = IntToStr(report_pwv->SiteB.NofValidDT);
   if (report_pwv->hr_diff_ok)
   {
      grdRes->Cells[4][2] = RoundIntToStr(report_pwv->SiteB.HeartRate);
   }
   else
   {
      grdRes->Cells[4][2] = RoundIntToStr(report_pwv->SiteB.HeartRate) +"*";
   }

   grdRes->Cells[0][3] = PWVMTypeAsString[report_pwv->SiteA.MeasureType].SubString(1,3)
                 + "-" + PWVMTypeAsString[report_pwv->SiteB.MeasureType].SubString(1,3);
   grdRes->Cells[1][3] = FormatFloat("##0.0", report_pwv->MeanDT);

   grdRes->Cells[2][3] = FormatFloat("#0.0", report_pwv->DeviationDT);

   lbl_dist->Caption = RoundIntToStr(report_pwv->Distance) + " mm";
   if (report_pwv->SiteA.deviation_ok && report_pwv->SiteB.deviation_ok && report_pwv->hr_diff_ok)
   {
      quality_font_style << fsBold;
   }
   PWVSD = report_pwv->DeviationDT / report_pwv->MeanDT * 100.0;
   lblPWV->Font->Style = quality_font_style;
   lblPWV->Caption  = FormatFloat("#0.0", report_pwv->PWV)
              + " ± " + FormatFloat("#0.0",report_pwv->PWVError);
   lblPWVSD->Font->Style = quality_font_style;
   // PM V9
   // SD is colour coded for adult Carotid-Femoral measurements
   if (report_age >= PATIENT_YOUNG_AGE &&
      ((report_pwv->SiteA.MeasureType == PWV_CAROTID && report_pwv->SiteB.MeasureType == PWV_FEMORAL) ||
      (report_pwv->SiteA.MeasureType == PWV_FEMORAL && report_pwv->SiteB.MeasureType == PWV_CAROTID)))
   {
      if (PWVSD > 10.0)
      {
         lblPWVSD->Font->Color = sphygmocor_red;
      }
      else
      {
         lblPWVSD->Font->Color = sphygmocor_green;
      }
   }
   else
   {
      lblPWVSD->Font->Color = sphygmocor_navy;
   }
   lblPWVSD->Caption  = FormatFloat("#0.0", PWVSD) + " %";
   lblPWVSD_title->Caption  = PWVMTypeAsString[report_pwv->SiteA.MeasureType].SubString(1,3)
                 + "-" + PWVMTypeAsString[report_pwv->SiteB.MeasureType].SubString(1,3) + " PTT SD";

   // MeanDeltaT Series
   for (int k = 0; k < report_pwv->SiteA.NofDT; k++)
   {
      srs_sitea_meandt->AddXY(k, report_pwv->SiteA.MeanDT, "", clBlue);
   }
   for (int k = 0; k < report_pwv->SiteB.NofDT; k++)
   {
      srs_siteb_meandt->AddXY(k, report_pwv->SiteB.MeanDT, "", clBlue);
   }                                                                  
}
//---------------------------------------------------------------------------
void Tfrm_report_pwv::report_display_pwv_normals()
{
   float       log_value;
   int         start_pt;
   int         end_pt;
   int         x;
   int         graph_height;
   float       position_ratio;
   int         indicator_left;
   AnsiString  S;

   start_pt = 20;
   end_pt = 90;

   if (patient_is_male())
   {
      pwv_coeff_1 = pwv_coeff_1_male;
      pwv_coeff_2 = pwv_coeff_2_male;
      pwv_y_intercept = pwv_y_intercept_male;
      pwv_confidence_90_offset = pwv_confidence_90_offset_male;
   }
   else
   {
      pwv_coeff_1 = pwv_coeff_1_female;
      pwv_coeff_2 = pwv_coeff_2_female;
      pwv_y_intercept = pwv_y_intercept_female;
      pwv_confidence_90_offset = pwv_confidence_90_offset_female;
   }
   // PM CR
   chrt_pwv_reference->BottomAxis->SetMinMax(start_pt, end_pt);
   chrt_pwv_reference->LeftAxis->SetMinMax(((pwv_coeff_1) * (end_pt * end_pt)) + (pwv_coeff_2 * end_pt) + pwv_y_intercept + (2 * pwv_confidence_90_offset),
                                       ((pwv_coeff_1) * (start_pt * start_pt)) + (pwv_coeff_2 * start_pt) + pwv_y_intercept - (1.5 * pwv_confidence_90_offset));

   x = start_pt;
   srs_pwv_lower_reference->Clear();
   srs_pwv_normal_reference->Clear();
   srs_pwv_upper_reference->Clear();
   while (x <= end_pt)
   {
      srs_pwv_lower_reference->AddXY(x,
                       ((pwv_coeff_1) * (x * x)) + (pwv_coeff_2 * x) + pwv_y_intercept - pwv_confidence_90_offset,
                       "", clTeeColor);

      srs_pwv_normal_reference->AddXY(x,
                        ((pwv_coeff_1) * (x * x)) + (pwv_coeff_2 * x) + pwv_y_intercept,
                        "", clTeeColor);
      srs_pwv_upper_reference->AddXY(x,
                       ((pwv_coeff_1) * (x * x)) + (pwv_coeff_2 * x) + pwv_y_intercept + pwv_confidence_90_offset,
                       "", clTeeColor);
      x = x + 2;
   }

   srs_pwv_point_reference->Clear();
   if (report_age >= PATIENT_YOUNG_AGE &&
      ((report_pwv->SiteA.MeasureType == PWV_CAROTID && report_pwv->SiteB.MeasureType == PWV_FEMORAL) ||
      (report_pwv->SiteA.MeasureType == PWV_FEMORAL && report_pwv->SiteB.MeasureType == PWV_CAROTID)))
   {
      if (report_pwv->PWV != DEFAULT_VALUE)
      {
         if (report_pwv->PWV > chrt_pwv_reference->LeftAxis->Maximum)
         {
            srs_pwv_point_reference->AddXY(report_age,
                                chrt_pwv_reference->LeftAxis->Maximum,
                                "", clBlue);
         }
         else if (report_pwv->PWV < chrt_pwv_reference->LeftAxis->Minimum)
         {
            srs_pwv_point_reference->AddXY(report_age,
                                chrt_pwv_reference->LeftAxis->Minimum,
                                "", clBlue);
         }
         else
         {
            srs_pwv_point_reference->AddXY(report_age,
                                report_pwv->PWV,
                                "", clBlue);
         }
      }
   }
}
//---------------------------------------------------------------------------
void Tfrm_report_pwv::print_report_header(TRect *print_area)
{
   print_do_header(print_area, "SphygmoCor", "Pulse Wave Velocity Report");
}
//---------------------------------------------------------------------------
void Tfrm_report_pwv::print_report_patient(TRect *print_area)
{
   print_do_patient_data(print_area, report_age, false, "", "", report_pwv->Simulation);
}
//---------------------------------------------------------------------------
void Tfrm_report_pwv::print_report_study(TPrinter *print_ptr, TRect *print_area)
{
   int          text_width;
   int          xpos;
   int          ypos;
   int          x_offset;
   int          chart_ypos;
   AnsiString   S;
   TRect        chart_rect;
   TFontStyles  font_style;

   TFontStyles  bold_font;
   bold_font.Clear();
   bold_font << fsBold;

   TFontStyles  normal_font;
   normal_font.Clear();

   int width  = print_area->Right - print_area->Left;

   font_style << fsBold;
   S = "STUDY DATA";
   print_ptr->Canvas->Font->Name = REPORT_FONT_NAME;
   print_ptr->Canvas->Font->Size = 12;
   print_ptr->Canvas->Font->Style = font_style;
   print_ptr->Canvas->TextOut(print_area->Left,
                              print_area->Top,
                              S);

   ypos = print_area->Top + print_ptr->Canvas->TextHeight(S);

   print_ptr->Canvas->Font->Name = REPORT_FONT_NAME;
   print_ptr->Canvas->Font->Size = 8;
   print_ptr->Canvas->Font->Style = font_style;

   // DateTime
   S = lbl_date->Caption + ", " + lbl_time->Caption + "    ";
   print_ptr->Canvas->TextOut(print_area->Left,
                              ypos,
                              S);

   xpos = print_area->Left + print_ptr->Canvas->TextWidth(S);

   font_style.Clear();
   print_ptr->Canvas->Font->Style = font_style;

   // Height, Weight, BMI
   if (lbl_hwbmi->Caption != "")
   {
      S = lbl_hwbmi_title->Caption + " ";

      print_ptr->Canvas->TextOut(xpos,
                                 ypos,
                                 S);
      xpos = xpos + print_ptr->Canvas->TextWidth(S);

      font_style << fsBold;
      print_ptr->Canvas->Font->Style = font_style;
      S = lbl_hwbmi->Caption + "    ";
      print_ptr->Canvas->TextOut(xpos,
                                 ypos,
                                 S);
      xpos = xpos + print_ptr->Canvas->TextWidth(S);

   }
   // Algorithm
   if (lblAlg->Visible)
   {
      S = "Algorithm: ";
      font_style.Clear();
      print_ptr->Canvas->Font->Style = font_style;

      print_ptr->Canvas->TextOut(xpos,
                                 ypos,
                                 S);

      xpos = xpos + print_ptr->Canvas->TextWidth(S);

      font_style << fsBold;
      print_ptr->Canvas->Font->Style = font_style;
      S = lblAlg->Caption +"    ";
      print_ptr->Canvas->TextOut(xpos,
                                 ypos,
                                 S);
   }

   // PM CR
   font_style.Clear();
   print_ptr->Canvas->Font->Style = font_style;
   S = "Medications:    ";
   text_width = print_ptr->Canvas->TextWidth(S);

   // Operator
   ypos = ypos + print_ptr->Canvas->TextHeight(S);
   S = lbl_operator_title->Caption + " ";
   print_ptr->Canvas->TextOut(print_area->Left,
                              ypos,
                              S);

   xpos = print_area->Left + text_width;
   font_style << fsBold;
   print_ptr->Canvas->Font->Style = font_style;

   S = lbl_operator->Caption + " ";
   print_ptr->Canvas->TextOut(xpos,
                              ypos,
                              S);

   // Audit DateTime
   if (config_get_audit_option())
   {
      if (pwv_audit_mode)
      {
         if (report_pwv->AuditFlag == AUDIT_MODIFIED)
         {
            xpos = xpos + print_ptr->Canvas->TextWidth(S);
            font_style.Clear();
            print_ptr->Canvas->Font->Style = font_style;

            S = "on ";
            print_ptr->Canvas->TextOut(xpos,
                                    ypos,
                                    S);
            xpos = xpos + print_ptr->Canvas->TextWidth(S);

            font_style << fsBold;
            print_ptr->Canvas->Font->Style = font_style;
            S = report_pwv->AuditChange.FormatString(REPORT_PAT_DOB_DATE_FORMAT) +
               ", " + report_pwv->AuditChange.TimeString() + " ";
            print_ptr->Canvas->TextOut(xpos,
                                    ypos,
                                    S);
         }
         xpos = xpos + print_ptr->Canvas->TextWidth(S);

         font_style << fsBold;
         print_ptr->Canvas->Font->Style = font_style;
         S = "(" + IntToStr(report_qry->RecNo) + " of "
            + IntToStr(report_qry->RecordCount) + ")    ";
         print_ptr->Canvas->TextOut(xpos,
                                    ypos,
                                    S);
      }
   }

   // PWV Distance
   xpos = xpos + print_ptr->Canvas->TextWidth(S);
   font_style.Clear();
   print_ptr->Canvas->Font->Style = font_style;
   S = "Distance: ";
   print_ptr->Canvas->TextOut(xpos,
                              ypos,
                              S);

   xpos = xpos + print_ptr->Canvas->TextWidth(S);
   font_style << fsBold;
   print_ptr->Canvas->Font->Style = font_style;
   S = lbl_dist->Caption +"    ";
   print_ptr->Canvas->TextOut(xpos,
                              ypos,
                              S);

   // Peripheral Pressure
   xpos = xpos + print_ptr->Canvas->TextWidth(S);
   font_style.Clear();
   print_ptr->Canvas->Font->Style = font_style;
   S = "Blood Pressure: ";
   print_ptr->Canvas->TextOut(xpos,
                              ypos,
                              S);

   xpos = xpos + print_ptr->Canvas->TextWidth(S);
   font_style << fsBold;
   print_ptr->Canvas->Font->Style = font_style;
   S = lblSpDpMp->Caption + "    ";
   print_ptr->Canvas->TextOut(xpos,
                              ypos,
                              S);

   // Tonometer serial number
   if (lbl_tonometer->Visible)
   {
      xpos = xpos + print_ptr->Canvas->TextWidth(S);
      font_style.Clear();
      print_ptr->Canvas->Font->Style = font_style;
      S = lbl_tonometer_title->Caption + " ";

      print_ptr->Canvas->TextOut(xpos,
                                 ypos,
                                 S);
      xpos = xpos + print_ptr->Canvas->TextWidth(S);

      font_style << fsBold;
      print_ptr->Canvas->Font->Style = font_style;
      S = lbl_tonometer->Caption + "    ";
      print_ptr->Canvas->TextOut(xpos,
                                 ypos,
                                 S);
   }

   // Medication
   font_style.Clear();
   print_ptr->Canvas->Font->Style = font_style;
   S = "Medications:";
   ypos = ypos + print_ptr->Canvas->TextHeight(S);
   print_ptr->Canvas->TextOut(print_area->Left,
                              ypos,
                              S);
   print_ptr->Canvas->TextOut(print_area->Left + text_width,
                              ypos,
                              edt_med->Text);

   // Notes
   S = "Notes:";
   ypos = ypos + print_ptr->Canvas->TextHeight(S);
   print_ptr->Canvas->TextOut(print_area->Left,
                              ypos,
                              S);
   print_ptr->Canvas->TextOut(print_area->Left + text_width,
                              ypos,
                              edt_notes->Text);

   // Reason for Change
   if (report_pwv->Reason.Length() != 0)
   {
      S = "Reason for Change: ";
      ypos = ypos + print_ptr->Canvas->TextHeight(S);
      print_ptr->Canvas->TextOut(print_area->Left,
                                    ypos,
                                    S);
      text_width = print_ptr->Canvas->TextWidth(S);
      String report_reason = MsgBox_ReplaceCarriage(report_pwv->Reason);
      int report_reason_len = report_reason.Length();
      String report_reason_line1 = "";
      String report_reason_line2 = "";
      if (report_reason_len < 120)
      {
         print_ptr->Canvas->TextOut(print_area->Left + text_width,
                                       ypos,
                                       report_reason);
      }
      else
      {
         report_reason_line1 = report_reason.SubString(1, 120);
         report_reason_line2 = report_reason.SubString(121, report_reason_len - 120);
         print_ptr->Canvas->TextOut(print_area->Left + text_width,
                                       ypos,
                                       report_reason_line1);
         ypos = ypos + print_ptr->Canvas->TextHeight(S) + 5;
         print_ptr->Canvas->TextOut(print_area->Left + text_width,
                                       ypos,
                                       report_reason_line2);
      }
   }

   ypos = ypos + (2 * print_ptr->Canvas->TextHeight(S));
   chart_ypos = ypos;

   chart_rect.Top = chart_ypos;
   chart_rect.Left = print_area->Left;
   chart_rect.Right = width * 0.66;
   chart_rect.Bottom = print_area->Bottom - 4;

   font_style << fsBold;
   S = "QUALITY CONTROL";
   print_ptr->Canvas->Font->Name = REPORT_FONT_NAME;
   print_ptr->Canvas->Font->Size = 12;
   print_ptr->Canvas->Font->Style = font_style;
   print_ptr->Canvas->TextOut(width * 0.7,
                              ypos,
                              S);
   font_style >> fsBold >> fsUnderline;
   print_ptr->Canvas->Font->Name = REPORT_FONT_NAME;
   print_ptr->Canvas->Font->Size = 8;
   print_ptr->Canvas->Font->Style = font_style;

   S = "Pressure  ";
   text_width = print_ptr->Canvas->TextWidth(S);
   ypos = ypos + 2 * print_ptr->Canvas->TextHeight(S);
   xpos = width * 0.7 + text_width;

   S = "Site A";
   print_ptr->Canvas->Font->Style = bold_font;
   print_ptr->Canvas->TextOut(width * 0.7,
                              ypos,
                              S);

   S = "aPH    PHv     PLv    BLv";
   print_ptr->Canvas->Font->Style = normal_font;
   print_ptr->Canvas->TextOut(xpos,
                              ypos,
                              S);

   ypos = ypos + print_ptr->Canvas->TextHeight(S);
   print_ptr->Canvas->Font->Style = normal_font;
   S = "Pressure  ";
   print_ptr->Canvas->TextOut(width * 0.7,
                              ypos,
                              S);
   // PM V9
   // Quality control is not colour coded, so always display them as bold
   print_ptr->Canvas->Font->Style = bold_font;
   print_ptr->Canvas->TextOut(xpos,
                              ypos,
                              lblQC_PH_AT->Caption);

   x_offset = print_ptr->Canvas->TextWidth("WWW ");
   print_ptr->Canvas->Font->Style = bold_font;
   print_ptr->Canvas->TextOut(xpos + x_offset,
                              ypos,
                              lblQC_PHV_AT->Caption);
   print_ptr->Canvas->Font->Style = normal_font;

   x_offset = print_ptr->Canvas->TextWidth("WWW ") * 2;
   print_ptr->Canvas->Font->Style = bold_font;
   print_ptr->Canvas->TextOut(xpos + x_offset,
                              ypos,
                              lblQC_PLV_AT->Caption);
   print_ptr->Canvas->Font->Style = normal_font;

   x_offset = print_ptr->Canvas->TextWidth("WWW ") * 3;
   print_ptr->Canvas->Font->Style = bold_font;
   print_ptr->Canvas->TextOut(xpos + x_offset,
                              ypos,
                              lblQC_BLV_AT->Caption);
   print_ptr->Canvas->Font->Style = normal_font;

   S = "ECG  ";
   x_offset = 0;
   ypos = ypos + print_ptr->Canvas->TextHeight(S);
   print_ptr->Canvas->TextOut(width * 0.7,
                              ypos,
                              S);
   print_ptr->Canvas->Font->Style = bold_font;
   print_ptr->Canvas->TextOut(xpos,
                              ypos,
                              lblQC_PH_AE->Caption);

   x_offset = print_ptr->Canvas->TextWidth("WWW ");
   print_ptr->Canvas->Font->Style = bold_font;
   print_ptr->Canvas->TextOut(xpos + x_offset,
                              ypos,
                              lblQC_PHV_AE->Caption);
   print_ptr->Canvas->Font->Style = normal_font;

   x_offset = print_ptr->Canvas->TextWidth("WWW ") * 2;
   print_ptr->Canvas->Font->Style = bold_font;
   print_ptr->Canvas->TextOut(xpos + x_offset,
                              ypos,
                              lblQC_PLV_AE->Caption);
   print_ptr->Canvas->Font->Style = normal_font;

   x_offset = print_ptr->Canvas->TextWidth("WWW ") * 3;
   print_ptr->Canvas->Font->Style = bold_font;
   print_ptr->Canvas->TextOut(xpos + x_offset,
                              ypos,
                              lblQC_BLV_AE->Caption);
   print_ptr->Canvas->Font->Style = normal_font;

   ypos = ypos + 2 * print_ptr->Canvas->TextHeight(S);

   S = "Site B";
   print_ptr->Canvas->Font->Style = bold_font;
   print_ptr->Canvas->TextOut(width * 0.7,
                              ypos,
                              S);

   print_ptr->Canvas->Font->Style = normal_font;
   S = "Pressure  ";
   ypos = ypos + print_ptr->Canvas->TextHeight(S);
   print_ptr->Canvas->TextOut(width * 0.7,
                              ypos,
                              S);
   print_ptr->Canvas->Font->Style = bold_font;
   print_ptr->Canvas->TextOut(xpos,
                              ypos,
                              lblQC_PH_BT->Caption);
   print_ptr->Canvas->Font->Style = normal_font;
   x_offset = print_ptr->Canvas->TextWidth("WWW ");
   print_ptr->Canvas->Font->Style = bold_font;
   print_ptr->Canvas->TextOut(xpos + x_offset,
                              ypos,
                              lblQC_PHV_BT->Caption);
   print_ptr->Canvas->Font->Style = normal_font;

   x_offset = print_ptr->Canvas->TextWidth("WWW ") * 2;
   print_ptr->Canvas->Font->Style = bold_font;
   print_ptr->Canvas->TextOut(xpos + x_offset,
                              ypos,
                              lblQC_PLV_BT->Caption);
   print_ptr->Canvas->Font->Style = normal_font;

   x_offset = print_ptr->Canvas->TextWidth("WWW ") * 3;
   print_ptr->Canvas->Font->Style = bold_font;
   print_ptr->Canvas->TextOut(xpos + x_offset,
                              ypos,
                              lblQC_BLV_BT->Caption);
   print_ptr->Canvas->Font->Style = normal_font;

   S = "ECG  ";
   ypos = ypos + print_ptr->Canvas->TextHeight(S);
   print_ptr->Canvas->TextOut(width * 0.7,
                              ypos,
                              S);
   print_ptr->Canvas->Font->Style = bold_font;
   print_ptr->Canvas->TextOut(xpos,
                              ypos,
                              lblQC_PH_BE->Caption);
   x_offset = print_ptr->Canvas->TextWidth("WWW ");
   print_ptr->Canvas->Font->Style = bold_font;
   print_ptr->Canvas->TextOut(xpos + x_offset,
                              ypos,
                              lblQC_PHV_BE->Caption);
   print_ptr->Canvas->Font->Style = normal_font;

   x_offset = print_ptr->Canvas->TextWidth("WWW ") * 2;
   print_ptr->Canvas->Font->Style = bold_font;
   print_ptr->Canvas->TextOut(xpos + x_offset,
                              ypos,
                              lblQC_PLV_BE->Caption);
   print_ptr->Canvas->Font->Style = normal_font;

   x_offset = print_ptr->Canvas->TextWidth("WWW ") * 3;
   print_ptr->Canvas->Font->Style = bold_font;
   print_ptr->Canvas->TextOut(xpos + x_offset,
                              ypos,
                              lblQC_BLV_BE->Caption);
   print_ptr->Canvas->Font->Style = normal_font;

   ChartDT->PrintResolution = -100;
   ChartDT->LeftAxis->LabelsFont->Color = sphygmocor_black;
   ChartDT->PrintProportional = false;

   ChartDT->PrintPartial(chart_rect);

   ChartDT->LeftAxis->LabelsFont->Color = sphygmocor_white;
}
//---------------------------------------------------------------------------
void Tfrm_report_pwv::print_report_pwv_params(TPrinter *print_ptr, TRect *print_area)
{
   AnsiString   S;
   TFontStyles  font_style;
   TFontStyles  bold_font;
   int          row;
   int          col;
   int          x_scale;
   int          y_scale;
   int          ypos;
   TRect        print_rect;

   bold_font.Clear();
   bold_font << fsBold;

   S = "PULSE WAVE VELOCITY CALCULATION";
   print_ptr->Canvas->Font->Name = REPORT_FONT_NAME;
   print_ptr->Canvas->Font->Size = 12;
   print_ptr->Canvas->Font->Style = bold_font;
   print_ptr->Canvas->TextOut(print_area->Left,
                              print_area->Top,
                              S);

   x_scale = (GetDeviceCaps(print_ptr->Handle, LOGPIXELSX)) / this->PixelsPerInch;
   y_scale = (GetDeviceCaps(print_ptr->Handle, LOGPIXELSY)) / this->PixelsPerInch;

   print_ptr->Canvas->Brush->Color = clWhite; //clBlack;
   print_ptr->Canvas->Brush->Style = bsSolid;
   font_style.Clear();
   print_ptr->Canvas->Font->Name = REPORT_FONT_NAME;
   print_ptr->Canvas->Font->Size = 8;
   print_ptr->Canvas->Font->Color = clBlack;
   print_ptr->Canvas->Font->Style = font_style;

   for (row = 0; row < grdRes->RowCount; ++row)
   {
      for (col = 0; col < grdRes->ColCount; ++col)
      {
         print_rect = grdRes->CellRect(col, row);
         print_rect.Left = print_area->Left + print_rect.Left * x_scale;
         print_rect.Right = print_area->Left + print_rect.Right * x_scale;
         print_rect.Top = print_area->Top + (2 * print_ptr->Canvas->TextHeight(S)) + (print_rect.Top * y_scale);
         print_rect.Bottom = print_area->Top + (2 * print_ptr->Canvas->TextHeight(S)) + (print_rect.Bottom * y_scale);
         /*
         ** Windows 2000 and Xp printing engines can not handle the Text Rect Command
         ** thus has been changed to use the TextOut Command. 24/05/2002.
         ** NCR 10-0079
         ** print_ptr->Canvas->TextRect(print_rect,
         **                            print_rect.Left + (print_rect.Right - print_rect.Left - print_ptr->Canvas->TextWidth(grdRes->Cells[col][row])) / 2,
         **                            print_rect.Top + (print_rect.Bottom - print_rect.Top - print_ptr->Canvas->TextHeight(grdRes->Cells[col][row])) / 2,
         **                            grdRes->Cells[col][row]);
         */
         print_ptr->Canvas->TextOut(print_rect.Left + (print_rect.Right - print_rect.Left - (int)print_ptr->Canvas->TextWidth(grdRes->Cells[col][row])) / 2,
                                    print_rect.Top + (print_rect.Bottom - print_rect.Top - print_ptr->Canvas->TextHeight(grdRes->Cells[col][row])) / 2,
                                    grdRes->Cells[col][row]);
      }
   }

   print_ptr->Canvas->Font->Name = REPORT_FONT_NAME;
   print_ptr->Canvas->Font->Size = 14;
   if (report_pwv->SiteA.deviation_ok && report_pwv->SiteB.deviation_ok && report_pwv->hr_diff_ok)
   {
      print_ptr->Canvas->Font->Style = bold_font;
   }
   else
   {
      print_ptr->Canvas->Font->Style = font_style;
   }

   //S = "Pulse Wave Velocity = " + lblPWV->Caption +" (m/s) ";
   S = "Pulse Wave Velocity (m/s) = " + FormatFloat("#0.0", report_pwv->PWV) + " ";
   ypos = print_area->Bottom - (2 * print_ptr->Canvas->TextHeight(S));
   print_ptr->Canvas->TextOut(print_area->Left,
                              print_area->Bottom - (2 * print_ptr->Canvas->TextHeight(S)),
                              S);

   // PM V9
   // This is a fix for non-unicode operating systems (eg. Japan)
   print_rect.Left = print_area->Left + print_ptr->Canvas->TextWidth(S);
   S = "R";
   print_rect.Right = print_rect.Left + print_ptr->Canvas->TextWidth(S);
   print_rect.Top = ypos + print_ptr->Canvas->TextHeight(S) / 8;
   print_rect.Bottom = print_rect.Top + print_ptr->Canvas->TextHeight(S) * 3 / 4;

   print_ptr->Canvas->StretchDraw(print_rect, frm_main->img_plus_minus->Picture->Bitmap);

   S = " " + FormatFloat("#0.0",report_pwv->PWVError);
   ypos = print_area->Bottom - (2 * print_ptr->Canvas->TextHeight(S));
   print_ptr->Canvas->TextOut(print_rect.Right,
                              print_area->Bottom - (2 * print_ptr->Canvas->TextHeight(S)),
                              S);

   print_ptr->Canvas->Font->Size = 10;
   S = lblPWVSD_title->Caption + " = " + lblPWVSD->Caption;
   print_ptr->Canvas->TextOut(print_area->Left,
                              print_area->Bottom - (print_ptr->Canvas->TextHeight(S)),
                              S);
}

//---------------------------------------------------------------------------
void Tfrm_report_pwv::print_report_footer(TRect *print_area)
{
  print_do_footer(print_area, report_pwv->DataRev);
}
//---------------------------------------------------------------------------
void __fastcall Tfrm_report_pwv::FormKeyPress(TObject *Sender, char &Key)
{
  if (Key == VK_ESCAPE)
  {
    frm_main->spdbtn_patientClick(Sender);
  }
}

void __fastcall Tfrm_report_pwv::pnlAChartsResize(TObject *Sender)
{
  pnlAT->Height = pnlACharts->Height/2;  
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_report_pwv::pnlBChartsResize(TObject *Sender)
{
  pnlBT->Height = pnlBCharts->Height/2;
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_report_pwv::grdResDrawCell(TObject *Sender, int Col,
      int Row, TRect &Rect, TGridDrawState State)
{
   bool quality_ok;
   TFontStyles font_style;
   font_style.Clear();

   grdRes->Canvas->Brush->Color = pnl_params->Color;
   if (Col == 0 || Row == 0)
   {
      grdRes->Canvas->Font->Color = sphygmocor_white;
      font_style.Clear();
   }
   else
   {
      grdRes->Canvas->Font->Color = sphygmocor_navy;
      font_style << fsBold;
   }
   grdRes->Canvas->Font->Style = font_style;

   if (Col == 2 && (Row == 1 || Row == 2))
   {
      //grdRes->Canvas->Brush->Color = clBlack;
      if (Row == 1)
      {
         quality_ok = report_pwv->SiteA.deviation_ok;
      }
      else
      {
         quality_ok = report_pwv->SiteB.deviation_ok;
      }

      if (quality_ok)
      {
         grdRes->Canvas->Font->Color = sphygmocor_green;
      }
      else
      {
         grdRes->Canvas->Font->Color = sphygmocor_red;
      }
   }

   grdRes->Canvas->TextRect(Rect,
                            Rect.Left + (Rect.Right - Rect.Left - Canvas->TextWidth(grdRes->Cells[Col][Row])) / 2,
                            Rect.Top + (Rect.Bottom - Rect.Top - Canvas->TextHeight(grdRes->Cells[Col][Row])) / 2,
                            grdRes->Cells[Col][Row]);
}

//---------------------------------------------------------------------------
void __fastcall Tfrm_report_pwv::mnuitm_pwv_astextClick(TObject *Sender)
{
   PATIENT_RECORD_TYPE  pat;
   String               lFileName;

   if (patient_get(&pat))
   {
      // PM V9
      // If the EMR patient is active or default EMR mode is set - get the
      // export directory from the EMR object
      if (emr_patient_is_active() || emr_get_default_mode())
      {
         lFileName = emr_get_outbound() + pat.surname + "_"
                  + report_pwv->DateTime.FormatString("ddmmmyyyy-hhmmss") +"_pwv.txt";
      }
      else
      {
         lFileName = ExtractFilePath(Application->ExeName) + EXPORT_SUBDIR + pat.surname + "_"
                  + report_pwv->DateTime.FormatString("ddmmmyyyy-hhmmss") + "_pwv.txt";
      }

      // If successful, notify the EMR object
      if (export_measurement(grd_report->DataSource->DataSet, lFileName, report_pwv))
      {
         emr_export();
      }
   }
}
//---------------------------------------------------------------------------
void __fastcall Tfrm_report_pwv::pnl_paramsResize(TObject *Sender)
{
   ChartDT->Width = (pnl_params->Width - 2 - pnl_pwv->Width) / 2;    
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_report_pwv::FormKeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
   if (Shift.Contains(ssAlt) && Key == 'X')
   {
      TPoint point = bbtn_export->ClientOrigin;
      int X = point.x;
      int Y = point.y + bbtn_export->Height;

      pupmnu_export_pwv->Popup(X, Y);
   }
}
// PM V9
//---------------------------------------------------------------------------
/* ###########################################################################
// Perform an Export All according to the options set in the EMR object
*/
void __fastcall Tfrm_report_pwv::mnu_allClick(TObject *Sender)
{
   Graphics::TBitmap*   bmp_image;
   String               filename;
   String               outbound_directory;
   PATIENT_RECORD_TYPE  pat;
   bool                 success = true;

   if (emr_get_enabled())
   {
      outbound_directory = emr_get_outbound();
      if (patient_get(&pat) && outbound_directory != "")
      {
         // Display the status bar messages on the report form for the exported graphic
         Screen->Cursor = crHourGlass;
         pnl_status_bar->Visible = true;
         pnl_report_buttons->Visible = false;
         lbl_message1->Caption = frm_main->lbl_message1->Caption;
         lbl_message2->Caption = frm_main->lbl_message2->Caption;
         lbl_message3->Caption = frm_main->lbl_message3->Caption;
         lbl_message4->Caption = frm_main->lbl_message4->Caption;
         lbl_message1->Font->Color = frm_main->lbl_message1->Font->Color;
         lbl_message2->Font->Color = frm_main->lbl_message2->Font->Color;
         lbl_message3->Font->Color = frm_main->lbl_message3->Font->Color;
         lbl_message4->Font->Color = frm_main->lbl_message4->Font->Color;
         switch (emr_get_option())
         {
            // These options export the Report graphic and the text file
            case EMR_STANDARD:
            case EMR_CLINICAL:
            case EMR_DETAILED:
               try
               {
                  bmp_image = GetFormImage();
                  if (bmp_image != NULL)
                  {
                     filename = outbound_directory + "PIC_" + pat.surname + "_"
                              + report_pwv->DateTime.FormatString("ddmmmyyyy-hhmmss") + "_pwv.jpg";
                     if (report_export_graphic(bmp_image, filename) == false)
                     {
                        success = false;
                     }
                     delete bmp_image;
                  }

                  filename = outbound_directory + pat.surname + "_"
                           + report_pwv->DateTime.FormatString("ddmmmyyyy-hhmmss") + "_pwv.txt";
                  if (report_export_measurement(filename) == false)
                  {
                     success = false;
                  }
               }
               catch (...)
               {
                  (void)MsgBox_warning("Could Not Create Graphic.", SWARNING);
                  success = false;
               }
               break;

            // These options export the Report to pdf and a text file
            case EMR_ALL_PDF:
            case EMR_CLINICAL_PDF:
            case EMR_DETAILED_PDF:
               pdf_file = "REPORT_" + pat.surname + "_"
                        + report_pwv->DateTime.FormatString("ddmmmyyyy-hhmmss") + "_pwv";
               if (report_export_pdf() == false)
               {
                  success = false;
               }

               filename = outbound_directory + pat.surname + "_"
                        + report_pwv->DateTime.FormatString("ddmmmyyyy-hhmmss") + "_pwv.txt";
               if (report_export_measurement(filename) == false)
               {
                  success = false;
               }
               break;

            // All option exports the Report as a graphic, pdf and a text file
            case EMR_ALL:
               try
               {
                  bmp_image = GetFormImage();
                  if (bmp_image != NULL)
                  {
                     filename = outbound_directory + "PIC_" + pat.surname + "_"
                              + report_pwv->DateTime.FormatString("ddmmmyyyy-hhmmss") + "_pwv.jpg";
                     if (report_export_graphic(bmp_image, filename) == false)
                     {
                        success = false;
                     }
                     delete bmp_image;
                  }

                  pdf_file = "REPORT_" + pat.surname + "_"
                           + report_pwv->DateTime.FormatString("ddmmmyyyy-hhmmss") + "_pwv";
                  if (report_export_pdf() == false)
                  {
                     success = false;
                  }

                  filename = outbound_directory + pat.surname + "_"
                           + report_pwv->DateTime.FormatString("ddmmmyyyy-hhmmss") + "_pwv.txt";
                  if (report_export_measurement(filename) == false)
                  {
                     success = false;
                  }
               }
               catch (...)
               {
                  (void)MsgBox_warning("Could Not Create Graphic.", SWARNING);
                  success = false;
               }
               break;
         }
         pnl_report_buttons->Visible = true;
         pnl_status_bar->Visible = false;
         Screen->Cursor = crDefault;

         // If successful, notify the user and the EMR object
         if (success)
         {
            MsgBox_information("Files successfully exported to: " + outbound_directory, "Export All Successful");
            emr_export();
         }
         else
         {
            MsgBox_information("Some files were not exported successfully", "Export All Failed");
         }
      }
   }
}
// PM V9
/* ###########################################################################
// Exports the graphic bmp_image to the file jpeg_file_name without requiring
// user confirmation
*/
bool Tfrm_report_pwv::report_export_graphic(Graphics::TBitmap*   bmp_image,
                                                  String jpeg_file_name)
{
   bool         created = false;
   TJPEGImage*  jpg_image;

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
   return created;
}
// PM V9
/* ###########################################################################
// Exports the current PWV report as a text file to filename without requiring
// user confirmation
*/
bool Tfrm_report_pwv::report_export_measurement(String filename)
{
   int      lFileHandle;
   String   lOut = "";

   // Create the file
   if (FileExists(filename))
   {
      DeleteFile(filename);
   }
   lFileHandle = FileCreate(filename);
   if (lFileHandle <= 0)
   {
      MsgBox(TERROR, MSG_EXPORT_ERROR, MSG_EXPORT_ERROR_FILE, LoadStr(MSG_EXPORT_ERROR_FILE) + filename);
      return false;
   }

   Application->ProcessMessages();

   // Export the titles
   if (report_pwv->ExportPrintTitle(grd_report->DataSource->DataSet, lOut) == false)
   {
      return false;
   }

   lOut = lOut + "\r\n";
   FileWrite(lFileHandle, lOut.c_str(), lOut.Length());
   Application->ProcessMessages();

   // Export the parameters
   lOut = "";
   if (report_pwv->Export(lOut)== false)
   {
      return false;
   }

   lOut = lOut + "\r\n\r\n";
   FileWrite(lFileHandle, lOut.c_str(), lOut.Length());

   // Export the Arrays
   if (report_pwv->ExportArrays(lFileHandle) == false)
   {
      return false;
   }

   FileClose(lFileHandle);
   return true;
}
// PM V9
/* ###########################################################################
// Exports the current PWV report as a pdf file without requiring user confirmation
*/
bool Tfrm_report_pwv::report_export_pdf()
{
   TPrinter *printer_ptr;
   int      index;
   bool     success = false;
   String   pdf_printer;

   Application->ProcessMessages();
   //Application->HandleMessage();

   printer_ptr = print_get_printer_ptr();
   if (printer_ptr == NULL)
   {
      return false;
   }

   // Get the printer from the EMR object
   pdf_printer = emr_get_printer();
   index = printer_ptr->Printers->IndexOf(pdf_printer);
   
   if (index >=0)
   {
      printer_ptr->PrinterIndex = index;

      // Then call the print function
      bbtn_printClick(this);
      Screen->Cursor = crHourGlass;
      success = true;
   }
   else
   {
      MsgBox_show(TERROR,
                  MSG_EMR_ERROR,
                  "The Printer: " + pdf_printer + LoadStr(MSG_EMR_PDF_ERROR),
                  MSG_EMR_PDF_ERROR,
                  "The Printer: " + pdf_printer + LoadStr(MSG_EMR_PDF_ERROR));
      success = false;
   }

   return success;
}

void __fastcall Tfrm_report_pwv::bbtn_printClick(TObject *Sender)
{
   int                  report_width;
   int                  report_height;
   int                  left_margin;
   int                  pnl_params_height;
   TRect                print_rect;
   TPrinterOrientation  old_orient;
   TPrinter             *printer_ptr;
   AnsiString           S;

   if (this->Visible)
   {
      // PM V9
      // Do not ask for user confirmation when printing to pdf
      if (pdf_file == "")
      {
         if (MsgBox(MSG_PRINT_REPORT, CONFIRMATION, MB_YESNO | MB_ICONQUESTION) != ID_YES)
         {
            return;
         }
      }
   }

   printer_ptr = print_get_printer_ptr();
   if (printer_ptr == NULL)
   {
      return;
   }

   Screen->Cursor = crHourGlass;
   old_orient = printer_ptr->Orientation;
   printer_ptr->Orientation  = poPortrait;
   
   // PM V9
   // Set the title for pdf reports
   if (pdf_file == "")
   {
      printer_ptr->Title = "SphygmoCor PWV Report";
   }
   else
   {
      printer_ptr->Title = pdf_file;
      pdf_file = "";
   }
   try
   {
       // PM CR
       ChartAP->UndoZoom();
       ChartAE->UndoZoom();
       ChartBP->UndoZoom();
       ChartBE->UndoZoom();

       printer_ptr->BeginDoc();

       // Set the canvas to the size displayed in 600x800 resolution
       pnl_canvas->Align = alNone;
       pnl_pwv->Align = alNone;
       pnl_params_height = pnl_params->Height;
       pnl_params->Height = REPORT_PANEL_PARAMS_PRINT_HEIGHT;
       pnl_canvas->Height = REPORT_PANEL_CANVAS_PRINT_HEIGHT;
       pnl_canvas->Width = REPORT_PANEL_CANVAS_PRINT_WIDTH;

       report_width =  printer_ptr->PageWidth;
       report_width = report_width - (report_width * 0.02);
       report_height = printer_ptr->PageHeight;
       left_margin = report_width * 0.06;

       print_rect.Top = report_height * 0.87;
       print_rect.Left = left_margin;
       print_rect.Right = report_width;
       print_rect.Bottom = report_height;
       print_report_footer(&print_rect);

       print_rect.Top = report_height * 0.76;
       print_rect.Left = left_margin;
       print_rect.Right = report_width;
       print_rect.Bottom = report_height * 0.9;
       print_report_pwv_params(printer_ptr, &print_rect);

       print_rect.Top = report_height * 0.1;
       print_rect.Left = left_margin;
       print_rect.Right = report_width;
       print_rect.Bottom = report_height * 0.15;
       print_report_header(&print_rect);
       print_do_atcor_image(&print_rect);

       print_rect.Top = print_rect.Bottom;
       print_rect.Left = left_margin;
       print_rect.Right = report_width;
       print_rect.Bottom = report_height * 0.23;
       print_report_patient(&print_rect);

       print_rect.Top = report_height * 0.23;
       print_rect.Left = left_margin;
       print_rect.Right = report_width;
       print_rect.Bottom = report_height * 0.45;
       print_report_study(printer_ptr, &print_rect);

       print_rect.Top = report_height * 0.48;
       print_rect.Left = left_margin;
       print_rect.Right = report_width;
       print_rect.Bottom = report_height * 0.54;

       ChartAP->PrintResolution = -100;
       ChartAP->Title->Font->Color = sphygmocor_maroon;
       ChartAP->BackColor = sphygmocor_white;
       srs_sitea_pressure->ColorRange(srs_sitea_pressure->XValues,
                                      srs_sitea_pressure->MinXValue(),
                                      srs_sitea_pressure->MaxXValue(),
                                      sphygmocor_black);
       ChartAP->PrintPartial(print_rect);

       print_rect.Top = report_height * 0.54;
       print_rect.Left = left_margin;
       print_rect.Right = report_width;
       print_rect.Bottom = report_height * 0.60;

       ChartAE->PrintResolution = -100;
       ChartAE->BottomAxis->LabelsFont->Color = sphygmocor_black;
       ChartAE->BackColor = sphygmocor_white;
       srs_sitea_ecg->ColorRange(srs_sitea_ecg->XValues,
                                 srs_sitea_ecg->MinXValue(),
                                 srs_sitea_ecg->MaxXValue(),
                                 sphygmocor_navy);
       ChartAE->PrintPartial(print_rect);

       print_rect.Top = report_height * 0.62;
       print_rect.Left = left_margin;
       print_rect.Right = report_width;
       print_rect.Bottom = report_height * 0.68;

       ChartBP->PrintResolution = -100;
       ChartBP->Title->Font->Color = sphygmocor_maroon;
       ChartBP->BackColor = sphygmocor_white;
       srs_siteb_pressure->ColorRange(srs_siteb_pressure->XValues,
                                      srs_siteb_pressure->MinXValue(),
                                      srs_siteb_pressure->MaxXValue(),
                                      sphygmocor_black);
       ChartBP->PrintPartial(print_rect);

       print_rect.Top = report_height * 0.68;
       print_rect.Left = left_margin;
       print_rect.Right = report_width;
       print_rect.Bottom = report_height * 0.74;

       ChartBE->PrintResolution = -100;
       ChartBE->BottomAxis->LabelsFont->Color = sphygmocor_black;
       ChartBE->BackColor = sphygmocor_white;
       srs_siteb_ecg->ColorRange(srs_siteb_ecg->XValues,
                                 srs_siteb_ecg->MinXValue(),
                                 srs_siteb_ecg->MaxXValue(),
                                 sphygmocor_navy);
       ChartBE->PrintPartial(print_rect);

       print_rect.Top = report_height * 0.76;
       print_rect.Left = left_margin + (report_width * 0.45);
       print_rect.Right = report_width;
       print_rect.Bottom = report_height * 0.88;
       chrt_pwv_reference->PrintResolution = -100;
       chrt_pwv_reference->BottomAxis->LabelsFont->Color = sphygmocor_black;
       chrt_pwv_reference->BottomAxis->Title->Font->Color = sphygmocor_black;
       chrt_pwv_reference->LeftAxis->LabelsFont->Color = sphygmocor_black;
       chrt_pwv_reference->LeftAxis->Title->Font->Color = sphygmocor_black;
       chrt_pwv_reference->Title->Font->Color = sphygmocor_maroon;
       chrt_pwv_reference->PrintPartial(print_rect);

       printer_ptr->EndDoc();

       // Reset the canvas to normal
       pnl_canvas->Align = alClient;
       pnl_pwv->Align = alLeft;
       pnl_params->Height = pnl_params_height;

       ChartAP->Title->Font->Color = sphygmocor_white;
       ChartAP->BackColor = sphygmocor_black;
       ChartAE->BottomAxis->LabelsFont->Color = sphygmocor_white;
       ChartAE->BackColor = sphygmocor_black;
       ChartBP->Title->Font->Color = sphygmocor_white;
       ChartBP->BackColor = sphygmocor_black;
       ChartBE->BottomAxis->LabelsFont->Color = sphygmocor_white;
       ChartBE->BackColor = sphygmocor_black;

       srs_sitea_pressure->ColorRange(srs_sitea_pressure->XValues,
                                      srs_sitea_pressure->MinXValue(),
                                      srs_sitea_pressure->MaxXValue(),
                                      sphygmocor_white);
       srs_sitea_ecg->ColorRange(srs_sitea_ecg->XValues,
                                 srs_sitea_ecg->MinXValue(),
                                 srs_sitea_ecg->MaxXValue(),
                                 sphygmocor_yellow);
       srs_siteb_pressure->ColorRange(srs_siteb_pressure->XValues,
                                      srs_siteb_pressure->MinXValue(),
                                      srs_siteb_pressure->MaxXValue(),
                                      sphygmocor_white);
       srs_siteb_ecg->ColorRange(srs_siteb_ecg->XValues,
                                 srs_siteb_ecg->MinXValue(),
                                 srs_siteb_ecg->MaxXValue(),
                                 sphygmocor_yellow);

       chrt_pwv_reference->BottomAxis->LabelsFont->Color = sphygmocor_white;
       chrt_pwv_reference->BottomAxis->Title->Font->Color = sphygmocor_white;
       chrt_pwv_reference->LeftAxis->LabelsFont->Color = sphygmocor_white;
       chrt_pwv_reference->LeftAxis->Title->Font->Color = sphygmocor_white;
       chrt_pwv_reference->Title->Font->Color = sphygmocor_white;

   }
   catch (Exception &exception)
   {
      printer_ptr->Abort();
      printer_ptr->EndDoc();
   }
   printer_ptr->Orientation = old_orient;
   Screen->Cursor = crDefault;
   /*if (this->Visible)
   {
      grd_report->SetFocus();
   }*/   
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_report_pwv::bbtn_deleteClick(TObject *Sender)
{
   AnsiString S;

   S = lbl_pname->Caption;
   if (report_qry != NULL)
   {
      if (MsgBox(LoadStr(MSG_DELETE_MEAS2) + S + "\n\n" + LoadStr(MSG_ARE_YOU_SURE),
          SCONFIRMATION, MB_YESNO | MB_ICONQUESTION) == ID_YES)
      {
         // The operator must sign in to delete a record
         if(audit_pwv_delete())
         {
            try
            {
               // If the audit option is set, reports are never deleted
               // Instead, the audit flag is set to DELETED
               if (!config_get_audit_option())
               {
                  report_qry->Delete();
               }
            }
            catch (...)
            {
               return;
            }

            if (report_qry->RecordCount == 0)
            {
               MsgBox(MSG_NO_REPORTS_TO_DISPLAY, SNOTIFICATION, MB_ICONINFORMATION);
               patient_update_measurement_count(0);
               multdb_set_delete_status(false);
               Hide();
               frm_main->spdbtn_patientClick(Sender);
            }
            else
            {
               patient_update_measurement_count((short)(report_qry->RecordCount));
            }
         }
      }
   }   
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_report_pwv::bbtn_modifyClick(TObject *Sender)
{
   AUDIT_MODE        AuditMode;
   MEAS_SENDER_TYPE  report_sender;

   // The modify form can only be browsed for deleted reports and in audit mode
   if (report_pwv->AuditFlag == AUDIT_DELETED || pwv_audit_mode)
   {
      AuditMode = AUDIT_BROWSING;
   }
   else
   {
      AuditMode = AUDIT_NORMAL;
   }

   // PM V9
   // The field that opens the modify form will be selected on the modify form
   if (Sender == lbl_operator_title || Sender == lbl_operator)
   {
      report_sender = MEAS_OPERATOR;
   }
   else if (Sender == lbl_hwbmi_title || Sender == lbl_hwbmi)
   {
      report_sender = MEAS_BMI;
   }
   else if (Sender == lbl_med_title || Sender == edt_med)
   {
      report_sender = MEAS_MEDICATIONS;
   }
   else if (Sender == lbl_notes_title || Sender == edt_notes)
   {
      report_sender = MEAS_NOTES;
   }
   else if (Sender == lbl_pressure_title || Sender == lblSpDpMp)
   {
      report_sender = MEAS_PRESSURES;
   }
   else if (Sender == lbl_dist_title || Sender == lbl_dist)
   {
      report_sender = MEAS_DISTANCE;
   }
   else if (Sender == lblAlg_title || Sender == lblAlg)
   {
      report_sender = MEAS_ALGORITHM;
   }
   else
   {
      report_sender = MEAS_PRESSURES;
   }

  // Disable OnChange event to protect rewriting PWV
  grd_report->DataSource->OnDataChange = NULL;
  // Call recalculate form
  bool ret = meas_recalculate_pwv_show_form(this, report_pwv, report_qry,
               lbl_pname->Caption, AuditMode, report_sender);
  // Restore OnChange event
  grd_report->DataSource->OnDataChange = record_changed;
  // Refresh grid and charts
  if (ret)
  {
     record_changed(this, NULL);
  }
  //grd_report->SetFocus();   
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_report_pwv::bbtn_createpwaClick(TObject *Sender)
{
   TPWA            *pwa_from_pwv;
   short int       *pwa_data;
   int             nof_signal_points;
   TDataSet        *pwa_table;
   TLocateOptions  search_options;
   Variant         locate_details[4];
   AnsiString      feedback_str;
   bool            sitea_can_create = false;
   bool            siteb_can_create = false;
   bool            sitea_is_radial = false;
   bool            siteb_is_radial = false;
   bool            report_exists = false;
   int             aortic_sp = 0;
   int             aortic_mp = 0;
   int             aortic_dp = 0;

   // The operator must sign in to create a PWA report
   if(security_show())
   {
      if (report_pwv->SiteA.MeasureType == PWV_RADIAL || report_pwv->SiteB.MeasureType == PWV_RADIAL )
      {
         if (report_pwv->SiteA.MeasureType == PWV_RADIAL)
         {
            sitea_can_create = true;
            sitea_is_radial = true;
            feedback_str = "Would you like to create a Pulse Wave Analysis report\n\nfor " +lbl_pname->Caption +",\n\nusing the Radial pressure waveform of Site A?";
         }
         else
         {
            siteb_can_create = true;
            siteb_is_radial = true;
            feedback_str = "Would you like to create a Pulse Wave Analysis report\n\nfor " +lbl_pname->Caption +",\n\nusing the Radial pressure waveform of Site B?";
         }
  
      
         if (MsgBox_confirmation(feedback_str,
                                 "Create PWA Report") == ID_YES)
         {
            pwa_from_pwv = meas_get_current_pwa();
            pwa_from_pwv->MeasureType = PWA_RADIAL;
            pwa_from_pwv->Sp = report_pwv->Sp;
            pwa_from_pwv->Dp = report_pwv->Dp;
            pwa_from_pwv->MeanP = report_pwv->MeanP;
            pwa_from_pwv->System_ID = report_pwv->System_ID;
            pwa_from_pwv->Patient_No = report_pwv->Patient_No;
            pwa_from_pwv->Study_ID = report_pwv->Study_ID;
            pwa_from_pwv->DateTime = report_pwv->DateTime;
            pwa_from_pwv->DataRev = report_pwv->DataRev;
            pwa_from_pwv->Medication = report_pwv->Medication;
            pwa_from_pwv->Notes = report_pwv->Notes;
            if (config_get_audit_option())
            {
               pwa_from_pwv->Operator = security_get_username();
            }
            else
            {
               pwa_from_pwv->Operator = report_pwv->Operator;
            }
            pwa_from_pwv->Height = report_pwv->Height;
            pwa_from_pwv->Weight = report_pwv->Weight;
            pwa_from_pwv->Bmi = report_pwv->Bmi;
            pwa_from_pwv->Feet = report_pwv->Feet;
            pwa_from_pwv->Inch = report_pwv->Inch;
            pwa_from_pwv->Pound = report_pwv->Pound;
            pwa_from_pwv->Periph.qc_scale = 1;

            if (report_pwv->Simulation)
            {
               pwa_from_pwv->Simulation = true;
            }
            else
            {
               pwa_from_pwv->Simulation = false;
            }

            pwa_from_pwv->Tonometer = CONFIG_DEFAULT_TONOMETER;

            pwa_from_pwv->AuditFlag = AUDIT_ORIGINAL;
            pwa_from_pwv->Reason = "";

            if (report_age <= PATIENT_YOUNG_AGE)
            {
               feedback_str = "The Transfer Function is not validated for patients under 18 years of age.\n\nNo PWA Report will be produced for this arterial site.";
               MsgBox_information(feedback_str, "Create PWA Report");
            }
            else
            {
               Screen->Cursor = crHourGlass;
               emma_display_statusbar_message("Opening PWA Table ...", "", "", sphygmocor_white);
               if (dbmgr_open(DBMGR_MEASURE_PWA_TABLE, false))
               {
                  pwa_table = dbmgr_get_dataset(DBMGR_MEASURE_PWA_TABLE, false);
                  if (pwa_table != NULL)
                  {
                     emma_display_statusbar_message("Searching PWA Table ...", "", "", sphygmocor_white);
                     search_options.Clear();

                     locate_details[0] = pwa_from_pwv->System_ID;
                     locate_details[1] = pwa_from_pwv->Study_ID;
                     locate_details[2] = pwa_from_pwv->Patient_No;
                     locate_details[3] = pwa_from_pwv->DateTime;

                     String key_fields_str = MPW_SYSTEM_ID + ";" + MPW_STUDY_ID + ";" + MPW_PATIENT_NO + ";" + MPW_DATETIME;

                     report_exists = pwa_table->Locate(key_fields_str,
                                                      VarArrayOf(locate_details, 3),
                                                      search_options);
                  }
                  if (report_exists)
                  {
                     if (sitea_can_create)
                     {
                        feedback_str = "You have already created and saved a report for\n\n" +lbl_pname->Caption +" using the Radial\nartery pressure waveform of Site A !!";
                     }
                     else
                     {
                        feedback_str = "You have already created and saved a report for\n\n" +lbl_pname->Caption +" using the Radial\nartery pressure waveform of Site B!!";
                     }
  
                     MsgBox_information(feedback_str,
                                       "Create PWA Report");
                  }
                  else
                  {
                     emma_display_statusbar_message("Generating PWA Report ...", "", "", sphygmocor_white);
                     nof_signal_points = MEAS_DEFAULT_SAMPLE_RATE * MEAS_PWA_MIN_CAPTURE_TIME;
                     pwa_data = new short int[nof_signal_points];
                     if (sitea_can_create)
                     {
                        for (int i = 0; i < nof_signal_points; i++)
                        {
                           pwa_data[i] = report_pwv->SiteA.Tonom.Signal[i];
                        }
                     }
                     else
                     {
                        for (int i = 0; i < nof_signal_points; i++)
                        {
                           pwa_data[i] = report_pwv->SiteB.Tonom.Signal[i];
                        }
                     }

                     pwa_from_pwv->PrepareToCaptureSignal();
                     pwa_from_pwv->Periph.CaptureSignal(pwa_data,
                                                      nof_signal_points);

                     delete [] pwa_data;
                     if (pwa_from_pwv->Calculate())
                     {
                        try
                        {
                           pwa_table->Insert();
                        }
                        catch (Exception &exception)
                        {
                           dbmgr_close(DBMGR_MEASURE_PWA_TABLE, false);
                           Screen->Cursor = crDefault;
                           MsgBox_show(TERROR,
                                       MSG_DBREADWRITE_ERROR,
                                       "Could not save the Pulse Wave Analysis Report To Database.",
                                       MSG_DBREADWRITE_ERROR,
                                       "PWV to PWA " +GetCurrentPwaMeasureDetails() + exception.Message);
                           emma_display_statusbar_message("", "", "", sphygmocor_white);
                           return;
                        }
                        emma_display_statusbar_message("Saving PWA Report ...", "", "", sphygmocor_white);
                        if (pwa_from_pwv->Store(pwa_table, true, false))
                        {
                           aortic_sp = math_Round(pwa_from_pwv->Central.Sp);
                           aortic_mp = math_Round(pwa_from_pwv->Central.MeanP);
                           aortic_dp = math_Round(pwa_from_pwv->Central.Dp);
                           if (sitea_can_create)
                           {
                              feedback_str = "PWA Report created for " +lbl_pname->Caption +".\n\nThis report was created using the " +PWVMTypeAsString[report_pwv->SiteA.MeasureType] +" artery \npressure waveform of Site A and date stamped with\n" +lbl_date->Caption +", " +lbl_time->Caption +".\n\nAortic Sp, Mp, Dp: " +IntToStr(aortic_sp) +", " +IntToStr(aortic_mp) +", " +IntToStr(aortic_dp);
                           }
                           else
                           {
                              feedback_str = "PWA Report created for " +lbl_pname->Caption +".\n\nThis report was created using the " +PWVMTypeAsString[report_pwv->SiteB.MeasureType] +" artery \npressure waveform of Site B and date stamped with\n" +lbl_date->Caption +", " +lbl_time->Caption +".\n\nAortic Sp, Mp, Dp: " +IntToStr(aortic_sp) +", " +IntToStr(aortic_mp) +", " +IntToStr(aortic_dp);
                           }
                           MsgBox_information(feedback_str,
                                             "Create PWA Report");
                        }
                     }
                  }
                  dbmgr_close(DBMGR_MEASURE_PWA_TABLE, false);
               }
               Screen->Cursor = crDefault;
               emma_display_statusbar_message("", "", "", sphygmocor_white);
            }
         }
      }

      if (report_pwv->SiteA.MeasureType == PWV_CAROTID || report_pwv->SiteB.MeasureType == PWV_CAROTID)
      {
         if (report_pwv->SiteA.MeasureType == PWV_CAROTID)
         {
            sitea_can_create = true;
            feedback_str = "Would you like to create a Pulse Wave Analysis report\n\nfor " +lbl_pname->Caption +",\n\nusing the Carotid pressure waveform of Site A?";
         }
         else
         {
            siteb_can_create = true;
            feedback_str = "Would you like to create a Pulse Wave Analysis report\n\nfor " +lbl_pname->Caption +",\n\nusing the Carotid pressure waveform of Site B?";
         }
      
         if (MsgBox_confirmation(feedback_str,
                                 "Create PWA Report") == ID_YES)
         {
            pwa_from_pwv = meas_get_current_pwa();

            if (aortic_sp == 0 && aortic_dp == 0)
            {
               pwa_from_pwv->Sp = report_pwv->Sp;
               pwa_from_pwv->Dp = report_pwv->Dp;
               pwa_from_pwv->MeanP = report_pwv->MeanP;
            }
            else
            {
               pwa_from_pwv->Sp = aortic_sp;
               pwa_from_pwv->Dp = aortic_dp;
               pwa_from_pwv->MeanP = aortic_mp;
            }
   
            pwa_from_pwv->System_ID = report_pwv->System_ID;
            pwa_from_pwv->Patient_No = report_pwv->Patient_No;
            pwa_from_pwv->Study_ID = report_pwv->Study_ID;
            pwa_from_pwv->DateTime = report_pwv->DateTime + TDateTime(0,0,1,0);
            pwa_from_pwv->DataRev = report_pwv->DataRev;
            pwa_from_pwv->Medication = report_pwv->Medication;
            pwa_from_pwv->Notes = report_pwv->Notes;
            if (config_get_audit_option())
            {
               pwa_from_pwv->Operator = security_get_username();
            }
            else
            {
               pwa_from_pwv->Operator = report_pwv->Operator;
            }
            pwa_from_pwv->Height = report_pwv->Height;
            pwa_from_pwv->Weight = report_pwv->Weight;
            pwa_from_pwv->Bmi = report_pwv->Bmi;
            pwa_from_pwv->Feet = report_pwv->Feet;
            pwa_from_pwv->Inch = report_pwv->Inch;
            pwa_from_pwv->Pound = report_pwv->Pound;
            pwa_from_pwv->Periph.qc_scale = 1;

            if (report_pwv->Simulation)
            {
               pwa_from_pwv->Simulation = true;
            }
            else
            {
               pwa_from_pwv->Simulation = false;
            }

            pwa_from_pwv->Tonometer = CONFIG_DEFAULT_TONOMETER;

            pwa_from_pwv->AuditFlag = AUDIT_ORIGINAL;
            pwa_from_pwv->Reason = "";

            if (report_age <= PATIENT_YOUNG_AGE)
            {
               feedback_str = "The Transfer Function is not validated for patients under 18 years of age.\n\nA PWA Report will be produced for this \narterial site using the No Processing Option.";
               MsgBox_information(feedback_str, "Create PWA Report");
               pwa_from_pwv->MeasureType = PWA_AORTIC;
            }
            else
            {
               feedback_str = "Which method would you like to use?\n\nClick Yes to use the Carotid transfer function, otherwise\n\nClick No to use the No Processing function";
               if (MsgBox_confirmation(feedback_str,
                                       "Create PWA Report") == ID_YES)
               {
                  pwa_from_pwv->MeasureType = PWA_CAROTID;
               }
               else
               {
                  pwa_from_pwv->MeasureType = PWA_AORTIC;
               }
            }

            Screen->Cursor = crHourGlass;
            emma_display_statusbar_message("Opening PWA Table ...", "", "", sphygmocor_white);
            if (dbmgr_open(DBMGR_MEASURE_PWA_TABLE, false))
            {
               pwa_table = dbmgr_get_dataset(DBMGR_MEASURE_PWA_TABLE, false);
               if (pwa_table != NULL)
               {
                  emma_display_statusbar_message("Searching PWA Table ...", "", "", sphygmocor_white);
                  search_options.Clear();

                  locate_details[0] = pwa_from_pwv->System_ID;
                  locate_details[1] = pwa_from_pwv->Study_ID;
                  locate_details[2] = pwa_from_pwv->Patient_No;
                  locate_details[3] = pwa_from_pwv->DateTime;

                  String key_fields_str = MPW_SYSTEM_ID + ";" + MPW_STUDY_ID + ";" + MPW_PATIENT_NO + ";" + MPW_DATETIME;

                  report_exists = pwa_table->Locate(key_fields_str,
                                                 VarArrayOf(locate_details, 3),
                                                 search_options);
               }
               if (report_exists)
               {
                  if (sitea_can_create && !sitea_is_radial)
                  {
                     feedback_str = "You have already created and saved a report for\n\n" +lbl_pname->Caption +" using the Carotid\nartery pressure waveform of Site A !!";
                  }
                  else
                  {
                     feedback_str = "You have already created and saved a report for\n\n" +lbl_pname->Caption +" using the Carotid\nartery pressure waveform of Site B!!";
                  }

                  MsgBox_information(feedback_str,
                                  "Create PWA Report");
               }
               else
               {
                  emma_display_statusbar_message("Generating PWA Report ...", "", "", sphygmocor_white);
                  nof_signal_points = MEAS_DEFAULT_SAMPLE_RATE * MEAS_PWA_MIN_CAPTURE_TIME;
                  pwa_data = new short int[nof_signal_points];
                  if (sitea_can_create && !sitea_is_radial)
                  {
                     for (int i = 0; i < nof_signal_points; i++)
                     {
                        pwa_data[i] = report_pwv->SiteA.Tonom.Signal[i];
                     }
                  }
                  else
                  {
                     for (int i = 0; i < nof_signal_points; i++)
                     {
                        pwa_data[i] = report_pwv->SiteB.Tonom.Signal[i];
                     }
                  }
           
                  pwa_from_pwv->PrepareToCaptureSignal();
                  pwa_from_pwv->Periph.CaptureSignal(pwa_data,
                                                  nof_signal_points);
                  delete [] pwa_data;
                  if (pwa_from_pwv->Calculate())
                  {
                     try
                     {
                        pwa_table->Insert();
                     }
                     catch (Exception &exception)
                     {
                        dbmgr_close(DBMGR_MEASURE_PWA_TABLE, false);
                        Screen->Cursor = crDefault;
                        MsgBox_show(TERROR,
                                    MSG_DBREADWRITE_ERROR,
                                    "Could not save the Pulse Wave Analysis Report To Database.",
                                    MSG_DBREADWRITE_ERROR,
                                    "PWV to PWA " +GetCurrentPwaMeasureDetails() + exception.Message);
                        emma_display_statusbar_message("", "", "", sphygmocor_white);
                        return;
                     }
                     emma_display_statusbar_message("Saving PWA Report ...", "", "", sphygmocor_white);
                     if (pwa_from_pwv->Store(pwa_table, true, false))
                     {
                        if (sitea_can_create && !sitea_is_radial)
                        {
                           feedback_str = "PWA Report created for " +lbl_pname->Caption +".\n\nThis report was created using the " +PWVMTypeAsString[report_pwv->SiteA.MeasureType] +" artery \npressure waveform of Site A and date stamped with\n" +pwa_from_pwv->DateTime.FormatString(REPORT_STUDY_DATETIME_FORMAT) +".";
                        }
                        else
                        {
                           feedback_str = "PWA Report created for " +lbl_pname->Caption +".\n\nThis report was created using the " +PWVMTypeAsString[report_pwv->SiteB.MeasureType] +" artery \npressure waveform of Site B and date stamped with\n" +pwa_from_pwv->DateTime.FormatString(REPORT_STUDY_DATETIME_FORMAT) +".";
                        }
                        MsgBox_information(feedback_str,
                                        "Create PWA Report");
                     }
                  }
               }
               dbmgr_close(DBMGR_MEASURE_PWA_TABLE, false);
            }
            Screen->Cursor = crDefault;
            emma_display_statusbar_message("", "", "", sphygmocor_white);
         }
      }

      if (sitea_can_create == false && siteb_can_create == false)
      {
         MsgBox_information("Only a Radial or Carotid pressure waveform can\nbe used to generate a PWA report.",
                           "Create PWA Report");
      }
   }
   //grd_report->SetFocus();   
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_report_pwv::bbtn_exportClick(TObject *Sender)
{
   Graphics::TBitmap*   bmp_image;
   PATIENT_RECORD_TYPE  pat;
   String               attach_fname;

   try
   {
      // PM V9
      // Display the status bar messages on the report form for the exported graphic
      pnl_status_bar->Visible = true;
      pnl_report_buttons->Visible = false;
      lbl_message1->Caption = frm_main->lbl_message1->Caption;
      lbl_message2->Caption = frm_main->lbl_message2->Caption;
      lbl_message3->Caption = frm_main->lbl_message3->Caption;
      lbl_message4->Caption = frm_main->lbl_message4->Caption;
      lbl_message1->Font->Color = frm_main->lbl_message1->Font->Color;
      lbl_message2->Font->Color = frm_main->lbl_message2->Font->Color;
      lbl_message3->Font->Color = frm_main->lbl_message3->Font->Color;
      lbl_message4->Font->Color = frm_main->lbl_message4->Font->Color;
      bmp_image = GetFormImage();
      if (bmp_image != NULL)
      {
         if (patient_get(&pat))
         {
            // PM V9
            // If the EMR patient is active or default EMR mode is set - get the
            // export directory from the EMR object
            if (emr_patient_is_active() || emr_get_default_mode())
            {
               attach_fname = emr_get_outbound() + "PIC_" + pat.surname +"_"
                           +report_pwv->DateTime.FormatString("ddmmmyyyy-hhmmss") + "_pwv.jpg";
            }
            else
            {
               attach_fname = ExtractFilePath(Application->ExeName) +EXPORT_SUBDIR +"PIC_" +pat.surname +"_"
                      +frm_report_pwv->report_pwv->DateTime.FormatString("ddmmmyyyy-hhmmss") +"_pwv.jpg";
            }

            // If successful, notify the EMR object
            if (export_graphic(bmp_image, attach_fname))
            {
               emr_export();
            }
         }
         delete bmp_image;
      }
   }
   catch (...)
   {
      (void)MsgBox_warning("Could Not Create Graphic.",
                           SWARNING);
   }

   pnl_report_buttons->Visible = true;
   pnl_status_bar->Visible = false;
   //grd_report->SetFocus();   
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_report_pwv::bbtn_auditClick(TObject *Sender)
{
   if(config_get_audit_option())
   {
      if (pwv_audit_mode)
      {
         pwv_audit_mode = false;
         audit_pwv_hide();
      }
      else
      {
         pwv_audit_mode = true;
         if (!audit_pwv_show())
         {
            pwv_audit_mode = false;
         }
      }
   }
}
//---------------------------------------------------------------------------





