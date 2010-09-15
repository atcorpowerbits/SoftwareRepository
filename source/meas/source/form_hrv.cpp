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
#include <emr/pubserv.h>
#include <scor/form_main.h>
#include "form_hrv.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
Tfrm_measure_hrv *frm_measure_hrv;

TADOQuery* qry_hrv_study;

bool meas_hrv_form_initialise(void)
{
   frm_measure_hrv = new Tfrm_measure_hrv(emma_get_main_form_pointer());
   return frm_measure_hrv != NULL;
}


//---------------------------------------------------------------------------
__fastcall Tfrm_measure_hrv::Tfrm_measure_hrv(TComponent* Owner)
  : Child_Form(Owner)
{
}

//---------------------------------------------------------------------------
void __fastcall Tfrm_measure_hrv::FormShow(TObject *Sender)
{
   TDataSource          *ds_meas;
   PATIENT_RECORD_TYPE  pat;
   double               bmi_height;

   if (patient_get(&pat))
   {
      qry_hrv_study = dbmgr_setup_query(DBMGR_MEASURE_HRV_TABLE,
                                        DBMGR_QUERY_KEY,
                                        PATIENT_SYSTEM_ID,
                                        PATIENT_STUDY_ID,
                                        PATIENT_NO,
                                        pat.system_id,
                                        pat.study_id,
                                        IntToStr(pat.number),
                                        MPW_DATETIME);
      meas_hrv = meas_get_current_hrv();
      meas_hrvtime = meas_get_current_hrvtime();
      meas_hrvfreq = meas_get_current_hrvfreq();
      txtBmi->Caption = "";
      ds_meas = dbmgr_get_data_source(DBMGR_MEASURE_HRV_QUERY, false);
      if ((ds_meas != NULL) && (qry_hrv_study != NULL))
      {
         bbtn_capture->Enabled = true;
         grdMeas->DataSource = ds_meas;
         //navMeas->DataSource = ds_meas;
         ds_meas->OnDataChange = record_changed;
         qry_hrv_study->Last();

         bbtn_capture->Enabled = true;

         if (qry_hrv_study->RecordCount <= 0)
         {
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
            rdgrp_study->ItemIndex = 0;
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

         if (edtSp->Enabled)
         {
            edtSp->SetFocus();
         }
         lbl_pat->Caption = patient_get_name();

         // Display study data from the EMR object - if enabled
         if (meas_hrv_emr_mode())
         {
            ;
         }
      }
      else
      {
         log_write("HRV Query failed initialisation.");
      }
   }
}
//---------------------------------------------------------------------------
void __fastcall Tfrm_measure_hrv::record_changed(TObject *Sender, TField  *Field)
{
  if (frm_measure_hrv->pnlGrid->Visible == false)
  {
     return;
  }

  if (frm_measure_hrv->meas_hrv->Populate(qry_hrv_study) == false)
  {
    frm_measure_hrv->EmptyControls();
    return;
  }

  edtSp->Text = "";
  edtMp->Text = "";
  edtDp->Text = "";

  if (frm_measure_hrv->meas_hrv->Dp > 0)
  {
     frm_measure_hrv->edtDp->Text = RoundIntToStr(frm_measure_hrv->meas_hrv->Dp);
  }
  if (frm_measure_hrv->meas_hrv->Sp > 0)
  {
     frm_measure_hrv->edtSp->Text = RoundIntToStr(frm_measure_hrv->meas_hrv->Sp);
  }
  if (frm_measure_hrv->meas_hrv->MeanP > 0)
  {
     frm_measure_hrv->edtMp->Text = RoundIntToStr(frm_measure_hrv->meas_hrv->MeanP);
  }

  frm_measure_hrv->edtMed->Text = frm_measure_hrv->meas_hrv->Medication;
  frm_measure_hrv->edtNotes->Text = frm_measure_hrv->meas_hrv->Notes;
  frm_measure_hrv->edtOperator->Text = frm_measure_hrv->meas_hrv->Operator;

  if (frm_measure_hrv->meas_hrv->Feet >= 0 && frm_measure_hrv->meas_hrv->Feet != DEFAULT_VALUE)
  {
     frm_measure_hrv->edtFeet->Text = frm_measure_hrv->meas_hrv->Feet;
  }
  else
  {
     frm_measure_hrv->edtFeet->Text = "";
  }

  if (frm_measure_hrv->meas_hrv->Inch >= 0 && frm_measure_hrv->meas_hrv->Inch != DEFAULT_VALUE)
  {
     frm_measure_hrv->edtInch->Text = frm_measure_hrv->meas_hrv->Inch;
  }
  else
  {
     frm_measure_hrv->edtInch->Text = "";
  }

  if (frm_measure_hrv->meas_hrv->Pound > 0 && frm_measure_hrv->meas_hrv->Pound != DEFAULT_VALUE)
  {
     frm_measure_hrv->edtPound->Text = frm_measure_hrv->meas_hrv->Pound;
  }
  else
  {
     frm_measure_hrv->edtPound->Text = "";
  }

  if (frm_measure_hrv->meas_hrv->Height > 0 && frm_measure_hrv->meas_hrv->Height != DEFAULT_VALUE)
  {
     frm_measure_hrv->edtHeight->Text = frm_measure_hrv->meas_hrv->Height;
  }
  else
  {
     frm_measure_hrv->edtHeight->Text = "";
  }

  if (frm_measure_hrv->meas_hrv->Weight > 0 && frm_measure_hrv->meas_hrv->Weight != DEFAULT_VALUE)
  {
     frm_measure_hrv->edtWeight->Text = frm_measure_hrv->meas_hrv->Weight;
  }
  else
  {
     frm_measure_hrv->edtWeight->Text = "";
  }

  if (frm_measure_hrv->meas_hrv->Bmi > 0 && frm_measure_hrv->meas_hrv->Bmi != DEFAULT_VALUE)
  {
     frm_measure_hrv->txtBmi->Caption = FormatFloat("0.##", frm_measure_hrv->meas_hrv->Bmi);
  }
  else
  {
     frm_measure_hrv->txtBmi->Caption = "";
  }

  frm_measure_hrv->rdgrp_study->ItemIndex = (int) frm_measure_hrv->meas_hrv->MeasureType - 1;

  frm_measure_hrv->lbl_assessments_title->Caption = " Assessment "
                                                      + IntToStr(qry_hrv_study->RecNo) + " of "
                                                      + IntToStr(qry_hrv_study->RecordCount);
}

//---------------------------------------------------------------------------
void __fastcall Tfrm_measure_hrv::EmptyControls()
{
   lbl_pat->Caption = "";
   edtMed->Text = "";
   edtNotes->Text = "";
   edtOperator->Text = "";
   edtFeet->Text = "";
   edtInch->Text = "";
   edtPound->Text = "";
   edtHeight->Text = "";
   edtWeight->Text = "";
   txtBmi->Caption = "";
   chkbx_hrv_loopback->Checked = false;
   rdgrp_study->ItemIndex = 0;

   lbl_assessments_title->Caption = " Assessments";
}
//---------------------------------------------------------------------------
bool __fastcall Tfrm_measure_hrv::UpdateHRV()
{
   COMMS_ID_TYPE       port_id;

   port_id = config_get_comms_port();

   // Update current HRV object
   meas_hrv->Sp = edtSp->Text.ToIntDef(0);
   meas_hrv->Dp = edtDp->Text.ToIntDef(0);
   meas_hrv->MeanP = edtMp->Text.ToIntDef(0);

  // Memos
  meas_hrv->Medication = edtMed->Text;
  meas_hrv->Notes = edtNotes->Text;
  meas_hrv->Operator = edtOperator->Text;
  if (edtHeight->Text == "")
  {
     meas_hrv->Height = DEFAULT_VALUE;
  }
  else
  {
     meas_hrv->Height = edtHeight->Text.ToIntDef(DEFAULT_VALUE);
  }

  if (edtWeight->Text == "")
  {
     meas_hrv->Weight = DEFAULT_VALUE;
  }
  else
  {
     meas_hrv->Weight = edtWeight->Text.ToIntDef(DEFAULT_VALUE);
  }

  if (txtBmi->Caption != "")
  {
     meas_hrv->Bmi = txtBmi->Caption.ToDouble();
  }

  if (port_id == COMMS_PORT_SIMULATE)
  {
     meas_hrv->Simulation = true;
  }
  else
  {
     meas_hrv->Simulation = false;
  }

  // PM V9
  // Only validate the pressures if a value has been entered
  if (meas_hrv->Sp == 0 && meas_hrv->Dp == 0 && meas_hrv->MeanP == 0)
  {
      meas_hrv->ValidateSpDp = false;
  }
  else
  {
      meas_hrv->ValidateSpDp = true;
  }

  // Validate Pressures Sp, Dp, Mp
  if (meas_hrv->ValidateSpDp)
  {
      if (meas_hrv->ValidateSpDpMp()==false)
         return false;
  }

  // Validate Height and Weight
  if (meas_hrv->ValidateHtWt()==false)
  {
      return false;
  }

  capture_set_loopback(chkbx_hrv_loopback->Checked);

  meas_hrv->MeasureType = (HRV_MEASURE_TYPE) rdgrp_study->ItemIndex + 1;
  if (meas_hrv->ValidateMeasureType() == false)
  {
      return false;
  }
  return true;
}
//---------------------------------------------------------------------------
void __fastcall Tfrm_measure_hrv::FormHide(TObject *Sender)
{
   TDataSource *dsrc_measure;

   dsrc_measure = dbmgr_get_data_source(DBMGR_MEASURE_HRV_QUERY, false);
   if (dsrc_measure != NULL)
   {
      dsrc_measure->OnDataChange = NULL;
   }

   if (qry_hrv_study != NULL)
   {
      qry_hrv_study->Close();
   }
}
//---------------------------------------------------------------------------
void __fastcall Tfrm_measure_hrv::edtSpChange(TObject *Sender)
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
void __fastcall Tfrm_measure_hrv::edtMpChange(TObject *Sender)
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
void __fastcall Tfrm_measure_hrv::edtDpChange(TObject *Sender)
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
void __fastcall Tfrm_measure_hrv::edtHeightChange(TObject *Sender)
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
void __fastcall Tfrm_measure_hrv::edtWeightChange(TObject *Sender)
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

void __fastcall Tfrm_measure_hrv::FormKeyPress(TObject *Sender, char &Key)
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
void __fastcall Tfrm_measure_hrv::edtFeetChange(TObject *Sender)
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

void __fastcall Tfrm_measure_hrv::edtInchChange(TObject *Sender)
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

void __fastcall Tfrm_measure_hrv::edtPoundChange(TObject *Sender)
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
 ** meas_hrv_emr_mode()
 **
 ** DESCRIPTION
 **  Displays the study data specified by the EMR object
 ** INPUT
 **  Measure HRV Form
 ** OUTPUT
 **  None
 ** RETURN
 **  Boolean - success or not
*/
//---------------------------------------------------------------------------
bool meas_hrv_emr_mode(void)
{
   EMR_RECORD_TYPE      emr;
   bool                 success = false;

   frm_measure_hrv->edtDp->ReadOnly = false;
   frm_measure_hrv->edtSp->ReadOnly = false;
   frm_measure_hrv->edtMp->ReadOnly = false;
   frm_measure_hrv->edtMed->ReadOnly = false;
   frm_measure_hrv->edtNotes->ReadOnly = false;
   frm_measure_hrv->edtOperator->ReadOnly = false;
   frm_measure_hrv->edtFeet->ReadOnly = false;
   frm_measure_hrv->edtInch->ReadOnly = false;
   frm_measure_hrv->edtPound->ReadOnly = false;
   frm_measure_hrv->edtHeight->ReadOnly = false;
   frm_measure_hrv->edtWeight->ReadOnly = false;

   // Populate the study fields if the EMR patient is active
   if (emr_patient_is_active())
   {
      if (emr_get(&emr))
      {
         if (emr.dp != DEFAULT_VALUE)
         {
            frm_measure_hrv->edtDp->Text = IntToStr(emr.dp);
            if (!emr_get_editing())
            {
               // If DP has a value, then MP or SP will also have a value
               frm_measure_hrv->edtDp->ReadOnly = true;
               frm_measure_hrv->edtSp->ReadOnly = true;
               frm_measure_hrv->edtMp->ReadOnly = true;
            }
         }
         if (emr.sp != DEFAULT_VALUE)
         {
            frm_measure_hrv->edtSp->Text = IntToStr(emr.sp);
         }
         if (emr.mp != DEFAULT_VALUE)
         {
            frm_measure_hrv->edtMp->Text = IntToStr(emr.mp);
         }

         if (emr.medication != "")
         {
            frm_measure_hrv->edtMed->Text = emr.medication;
            if (!emr_get_editing())
            {
               frm_measure_hrv->edtMed->ReadOnly = true;
            }
         }
         if (emr.study_notes != "")
         {
            frm_measure_hrv->edtNotes->Text = emr.study_notes;
            if (!emr_get_editing())
            {
               frm_measure_hrv->edtNotes->ReadOnly = true;
            }
         }
         if (emr.operator_name != "")
         {
            frm_measure_hrv->edtOperator->Text = emr.operator_name;
            if (!emr_get_editing())
            {
               frm_measure_hrv->edtOperator->ReadOnly = true;
            }
         }
         // When the imperial values are populated, they automatically calculate
         // the nearest metric equivalent. So for accuracy, make sure the metric
         // values are populated last so they overwrite these values
         if (emr.feet != DEFAULT_VALUE)
         {
            frm_measure_hrv->edtFeet->Text = emr.feet;
            if (!emr_get_editing())
            {
               frm_measure_hrv->edtFeet->ReadOnly = true;
            }
         }
         if (emr.inch != DEFAULT_VALUE)
         {
            frm_measure_hrv->edtInch->Text = emr.inch;
            if (!emr_get_editing())
            {
               frm_measure_hrv->edtInch->ReadOnly = true;
            }
         }
         if (emr.pound != DEFAULT_VALUE)
         {
            frm_measure_hrv->edtPound->Text = emr.pound;
            if (!emr_get_editing())
            {
               frm_measure_hrv->edtPound->ReadOnly = true;
            }
         }
         if (emr.height != DEFAULT_VALUE)
         {
            frm_measure_hrv->edtHeight->Text = emr.height;
            if (!emr_get_editing())
            {
               frm_measure_hrv->edtHeight->ReadOnly = true;
            }
         }
         if (emr.weight != DEFAULT_VALUE)
         {
            frm_measure_hrv->edtWeight->Text = emr.weight;
            if (!emr_get_editing())
            {
               frm_measure_hrv->edtWeight->ReadOnly = true;
            }
         }
         success = true;
      }
   }
   return success;
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_measure_hrv::bbtn_captureClick(TObject *Sender)
{
   TDataSet   *hrv_table;
   bool       status;

   try
   {
     if (UpdateHRV() == false)
     {
        bbtn_capture->Enabled = true;
        //SetFocus();
        return;
     }

     meas_hrv_classes_initialise(1024);
     if (capture_show_form(MEAS_HRV_ID) == true)
     {
        pnlGrid->Enabled = false;
        pnlFields->Visible = false;
        pnlWait->Visible = true;
        Screen->Cursor = crHourGlass;
        lblStatus->Caption = "Calculating Results";
        Application->ProcessMessages();
        _sleep(1);
        if (meas_hrv->Calculate())
        {
           if (dbmgr_open(DBMGR_MEASURE_HRV_TABLE, false))
           {
              hrv_table = dbmgr_get_dataset(DBMGR_MEASURE_HRV_TABLE, false);
              status = false;
              if (hrv_table != NULL)
              {
                 lblStatus->Caption = "Saving Results to Database";
                 Application->ProcessMessages();
                 Sleep(100);
                 try
                 {
                    hrv_table->Insert();
                 }
                 catch (Exception &exception)
                 {
                    dbmgr_close(DBMGR_MEASURE_HRV_TABLE, false);
                    Screen->Cursor = crDefault;
                    pnlWait->Visible = false;
                    pnlGrid->Enabled = true;
                    pnlFields->Visible = true;
                    bbtn_capture->Enabled = true;

                    MsgBox(TERROR,
                           GetCurrentHRVMeasureDetails(),
                           MSG_DBREADWRITE_ERROR,
                           MSG_DBREADWRITE_ERROR,
                           exception.Message);

                    return;
                 }
                 status = meas_hrv->Store(hrv_table, true, false);
              }
              dbmgr_close(DBMGR_MEASURE_HRV_TABLE, false);
              if (status)
              {
                 lblStatus->Caption = "Generating Report Information";
                 Application->ProcessMessages();
                 Sleep(100);
                 patient_update_measurement_count((short)(qry_hrv_study->RecordCount + 1));
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

