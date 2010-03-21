//---------------------------------------------------------------------------
#include <vcl.h>
#include <Series.hpp>
#pragma hdrstop

#include <dbmgr/pubserv.h>
#include <meas/pubserv.h>
#include <patient/pubserv.h>
#include <print/pubserv.h>
#include <report/pubserv.h>
#include <export/pubserv.h>
#include <analysis/pubserv.h>
#include <msg/pubserv.h>
#include <log/pubserv.h>
#include <config/pubserv.h>
#include <scor/form_main.h>
#include <scor/utils.h>
#include "analysis.h"
#include "form_analysis_pwv.h"
#include "form_select.h"
#include "stdlib.h"
#include <dos.h>
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "ErrorBar"
#pragma resource "*.dfm"

const int ANALYSIS_PWV_PANEL_PRINT_HEIGHT = 360;
const int ANALYSIS_PWV_PANEL_PRINT_WIDTH = 720;

VAR_EXPORT bool analysis_pwv_audit_initialised;

//---------------------------------------------------------------------------
__fastcall Tfrm_analysis_pwv::Tfrm_analysis_pwv(TComponent* Owner)
    : Child_Form(Owner)
{
   clicked_series = false;
    series_index = 0;

    Caller = "";
    analysis_pwv = meas_get_current_pwv();
    analysis_input_measurements = new TStringList;
    analysis_selected_measurements = new TStringList;
    analysis_all_measurements = new TStringList;

    analysis_pwv_audit_initialised = true;
}

void __fastcall Tfrm_analysis_pwv::FormDestroy(TObject *Sender)
{
   ClearSeries();
   // Only the full list allocates memory and therefore needs to delete the objects
   analysis_input_measurements->Clear();
   analysis_selected_measurements->Clear();
   Analysis_ClearList(analysis_all_measurements);
   delete analysis_input_measurements;
   delete analysis_selected_measurements;
   delete analysis_all_measurements;
}
//---------------------------------------------------------------------------
void __fastcall Tfrm_analysis_pwv::FormShow(TObject *Sender)
{
   PATIENT_RECORD_TYPE  pat;
   analysis_pwv_audit_initialised = true;

   if (Caller == "Trend")
   {
      Caller = "";
      chrt_pwv->UndoZoom();
      chrt_hrate->UndoZoom();
      chrt_delta->UndoZoom();
      chrt_dist->UndoZoom();
      SetFocus();
      return;
   }
   Caller = "";

   if (patient_get(&pat) == false)
   {
      return;
   }

   // Only the full list allocates memory and therefore needs to delete the objects
   analysis_input_measurements->Clear();
   analysis_selected_measurements->Clear();
   Analysis_ClearList(analysis_all_measurements);

   // Select query for a patient
   if (config_get_audit_option())
   {
      // Query the database for reports that haven't been deleted
      analysis_qry = dbmgr_setup_query(DBMGR_MEASURE_PWV_TABLE,
                                          DBMGR_QUERY_AUDIT_FLAG,
                                          PATIENT_SYSTEM_ID,
                                          PATIENT_STUDY_ID,
                                          PATIENT_NO,
                                          MPWV_AUDIT_FLAG,
                                          pat.system_id,
                                          pat.study_id,
                                          IntToStr(pat.number),
                                          IntToStr(AUDIT_DELETED),
                                          MPW_DATETIME);
   }
   else
   {
      analysis_qry = dbmgr_setup_query(DBMGR_MEASURE_PWV_TABLE,
                                       DBMGR_QUERY_KEY,
                                       PATIENT_SYSTEM_ID,
                                       PATIENT_STUDY_ID,
                                       PATIENT_NO,
                                       pat.system_id,
                                       pat.study_id,
                                       IntToStr(pat.number),
                                       MPW_DATETIME);
   }

   if (config_get_audit_option())
   {
      if (analysis_qry->RecordCount < 2)
      {
         // If there aren't enough reports, set a flag and return
         MsgBox(TNOTIFICATION,
               MSG_AUDIT,
               MSG_AUDIT_NO_STUDIES_FOR_ANALYSIS,
               LoadStr(MSG_AUDIT_NO_STUDIES_FOR_ANALYSIS));
         analysis_pwv_audit_initialised = false;
         return;
      }
   }
      
   // Save all measurements in a list
   if (analysis_all_measurements->Count <= 0)
   {
      int i = 0;
      for (analysis_qry->First();!analysis_qry->Eof;analysis_qry->Next())
      {
         analysis_all_measurements->AddObject(analysis_qry->FieldByName(MPW_DATETIME)->AsDateTime.FormatString(ANALYSIS_DATETIME_FORMAT),
                              (TObject *)(new TDateTime(analysis_qry->FieldByName(MPW_DATETIME)->AsDateTime)));
         analysis_input_measurements->AddObject(analysis_all_measurements->Strings[i],
                                                      analysis_all_measurements->Objects[i]);
         i++;
      }
   }
   // Show all measurements
   ClearSeries();
   ShowCharts(analysis_qry, analysis_all_measurements, false);

   bbtn_print->Enabled = print_does_printer_exist();
   // If the audit option is set, disable export
   if (config_get_audit_option())
   {
      bbtn_export->Enabled = false;
   }
   SetFocus();
}

//---------------------------------------------------------------------------
void __fastcall Tfrm_analysis_pwv::ClearSeries()
{
   int j;

   for (j = chrt_pwv->SeriesCount() - 1; j >= 0 ; j--)
   {
      chrt_pwv->Series[j]->Clear();
   }
   for (j = chrt_delta->SeriesCount() - 1; j >= 0 ; j--)
   {
      chrt_delta->Series[j]->Clear();
   }
   for (j = chrt_dist->SeriesCount() - 1; j >= 0 ; j--)
   {
      chrt_dist->Series[j]->Clear();
   }
   for (j = chrt_hrate->SeriesCount() - 1; j >= 0 ; j--)
   {
      chrt_hrate->Series[j]->Clear();
   }
   /*
   ** This is needed to eliminate the List Index out
   ** of bounds message produced by TChart.
   */
   chrt_hrate->Update();
}

//---------------------------------------------------------------------------
void __fastcall Tfrm_analysis_pwv::FormKeyPress(TObject *Sender, char &Key)
{
   // PM CR - removed space bar
   if (Key == VK_ESCAPE)
   {
      frm_main->spdbtn_patientClick(Sender);
   }
}
//---------------------------------------------------------------------------
void __fastcall Tfrm_analysis_pwv::ShowCharts(TDataSet    *analysis_qry,
                                              TStringList *pList,
                                              const bool  is_print)
{
  int     nr = 0;
  int     valid_count = 0;

  Screen->Cursor = crHourGlass;
  try
  {
    // Activate progress bar
    // PM V9
    frm_main->prgbar_main->Visible = true;
    frm_main->prgbar_main->Min = 0;
    frm_main->prgbar_main->Max = max(analysis_qry->RecordCount, ANALYSIS_MAX_PWV_MEASUREMENTS);
    frm_main->prgbar_main->Step = 1;
    frm_main->prgbar_main->Position = 0;


    lbl_pat->Caption = patient_get_name();
    //TErrorBarSeries *bar_series = dynamic_cast<TErrorBarSeries *>(chrt_pwv->Series[1]);
    srs_pwv_bar->ErrorStyle = essTopBottom;

     chrt_hrate->PrintResolution = -100;
     chrt_pwv->PrintResolution = -100;
     chrt_delta->PrintResolution = -100;
     chrt_dist->PrintResolution = -100;

    // Looping selected measurements

    int total_records = (pList->Count > ANALYSIS_MAX_PWV_MEASUREMENTS ?
        ANALYSIS_MAX_PWV_MEASUREMENTS : pList->Count);

    for (analysis_qry->Last(); !analysis_qry->Bof && valid_count < ANALYSIS_MAX_PWV_MEASUREMENTS; analysis_qry->Prior())
    {
      frm_main->prgbar_main->Position = nr++;
      if (pList->IndexOf(analysis_qry->FieldByName(MPW_DATETIME)->AsDateTime.FormatString(ANALYSIS_DATETIME_FORMAT)) < 0)
      {
        continue;
      }
      if (analysis_pwv->Populate(analysis_qry)==false)
      {
        continue;
      }
      // Find first and last studies
      if (valid_count == 0)
      {
        analysis_last_study = analysis_pwv->DateTime.FormatString(ANALYSIS_DATETIME_FORMAT);
      }
      else
      {
        analysis_first_study = analysis_pwv->DateTime.FormatString(ANALYSIS_DATETIME_FORMAT);
      }

      // PWV
      String title = FormatFloat("###.#", analysis_pwv->PWV) + "±" + FormatFloat("##0.0", analysis_pwv->PWVError);
      srs_pwv_bar->AddErrorBar(total_records - valid_count,
                              analysis_pwv->PWV,
                              analysis_pwv->PWVError,
                              title, clTeeColor);
      title = analysis_pwv->DateTime.FormatString(ANALYSIS_DATETIME_FORMAT);
      srs_pwv_line->AddXY(total_records - valid_count, analysis_pwv->PWV,
                          title,  srs_pwv_line->SeriesColor);

      // Heart Rate Site A
      if (analysis_pwv->SiteA.HeartRate != DEFAULT_VALUE)
      {
        srs_hrate_a->AddXY(total_records - valid_count, math_Round(analysis_pwv->SiteA.HeartRate),
                           "", clTeeColor);
      }
      else
      {
        srs_hrate_a->AddNull(ANALYSIS_NOT_CALCULATED);
      }
      // Heart Rate Site B
      if (analysis_pwv->SiteB.HeartRate != DEFAULT_VALUE)
      {
        srs_hrate_b->AddXY(total_records - valid_count, math_Round(analysis_pwv->SiteB.HeartRate),
                           "", clTeeColor);
      }
      else
      {
         srs_hrate_b->AddNull(ANALYSIS_NOT_CALCULATED);
      }

      // PM V9
      // Distance
      if (analysis_pwv->Distance != DEFAULT_VALUE)
      {
        title = analysis_pwv->DateTime.FormatString(ANALYSIS_DATETIME_FORMAT);
        srs_dist_line->AddXY(total_records - valid_count,
                             analysis_pwv->Distance,
                             title, clTeeColor);
      }
      else
      {
        srs_dist_line->AddNull(ANALYSIS_NOT_CALCULATED);
      }

      // Delta T Site A
      if (analysis_pwv->SiteA.MeanDT != DEFAULT_VALUE)
      {
        title = analysis_pwv->DateTime.FormatString(ANALYSIS_DATETIME_FORMAT);
        srs_delta_line_a->AddXY(total_records - valid_count,
                                math_Round(analysis_pwv->SiteA.MeanDT),
                                "", clTeeColor);
        title = FormatFloat("###.#", analysis_pwv->SiteA.MeanDT) +
                "±" + FormatFloat("##0.0", analysis_pwv->SiteA.Deviation);
        srs_delta_error_a->AddErrorBar(total_records - valid_count,
                                       analysis_pwv->SiteA.MeanDT,
                                       analysis_pwv->SiteA.Deviation,
                                       title, clTeeColor);
      }
      else
      {
        srs_delta_line_a->AddNull(ANALYSIS_NOT_CALCULATED);
        srs_delta_error_a->AddNull(ANALYSIS_NOT_CALCULATED);
      }
      // Delta T Site B
      if (analysis_pwv->SiteB.MeanDT != DEFAULT_VALUE)
      {
        title = analysis_pwv->DateTime.FormatString(ANALYSIS_DATETIME_FORMAT);
        srs_delta_line_b->AddXY(total_records - valid_count,
                                math_Round(analysis_pwv->SiteB.MeanDT),
                                "", clTeeColor);
        title = FormatFloat("###.#", analysis_pwv->SiteB.MeanDT) +
                "±" + FormatFloat("##0.0", analysis_pwv->SiteB.Deviation);
        srs_delta_error_b->AddErrorBar(total_records - valid_count,
                            analysis_pwv->SiteB.MeanDT,
                            analysis_pwv->SiteB.Deviation,
                            title, clTeeColor);
      }
      else
      {
        srs_delta_line_b->AddNull(ANALYSIS_NOT_CALCULATED);
        srs_delta_error_b->AddNull(ANALYSIS_NOT_CALCULATED);
      }

      // Main Delta T
      if (analysis_pwv->MeanDT != DEFAULT_VALUE)
      {
        title = FormatFloat("###.#", analysis_pwv->MeanDT) +
                "±" + FormatFloat("##0.0", analysis_pwv->DeviationDT);
        srs_delta_error->AddErrorBar(total_records - valid_count,
                            analysis_pwv->MeanDT,
                            analysis_pwv->DeviationDT,
                            title, clTeeColor);
        title = analysis_pwv->DateTime.FormatString(ANALYSIS_DATETIME_FORMAT);
        srs_delta->AddXY(total_records - valid_count,
                         math_Round(analysis_pwv->MeanDT),
                         "", clTeeColor);
      }
      else
      {
        srs_delta->AddNull(ANALYSIS_NOT_CALCULATED);
        srs_delta_error->AddNull(ANALYSIS_NOT_CALCULATED);
      }
      valid_count++;
    }

    if (valid_count > 1)
    {
       chrt_pwv->LeftAxis->SetMinMax((int)(srs_pwv_bar->MinYValue() * 0.8 - 0.5),
                                     (int)(srs_pwv_bar->MaxYValue() * 1.1 + 0.5));
       chrt_pwv->BottomAxis->SetMinMax(0, valid_count + 1);

       int hrate_min = min(srs_hrate_a->MinYValue(), srs_hrate_b->MinYValue()) - 10;
       int hrate_max = max(srs_hrate_a->MaxYValue(), srs_hrate_b->MaxYValue()) + 10;
       chrt_hrate->LeftAxis->SetMinMax(hrate_min, hrate_max);
       chrt_hrate->BottomAxis->SetMinMax(0, valid_count + 1);

       // PM V9
       double delta_min = srs_delta_error->MinYValue() * 0.8;
       double delta_max = max(srs_delta_error_a->MaxYValue(), srs_delta_error_b->MaxYValue());
       delta_max = max(delta_max, srs_delta->MaxYValue()) * 1.20;
       chrt_delta->LeftAxis->SetMinMax(delta_min, delta_max);
       chrt_delta->BottomAxis->SetMinMax(0, valid_count + 1);

       double dist_min = srs_dist_line->MinYValue() * 0.8;
       double dist_max = srs_dist_line->MaxYValue() * 1.2;
       chrt_dist->LeftAxis->SetMinMax(dist_min, dist_max);
       chrt_dist->BottomAxis->SetMinMax(0, valid_count + 1);
    }
    else
    {
      // PM CR
      bbtn_print->Enabled = false;
    }
  }
  catch(Exception &exc)
  {
    log_write(SEXCEPTION +exc.Message);
  }
  Screen->Cursor = crDefault;
  frm_main->prgbar_main->Visible = false;
}

//---------------------------------------------------------------------------
void __fastcall Tfrm_analysis_pwv::chrt_pwvMouseUp(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
   TChart *chart = dynamic_cast<TChart *>(Sender);
   if (chart != NULL)
   {
      srs_hrate_a->Marks->Visible = false;
      srs_hrate_b->Marks->Visible = false;
      srs_pwv_line->Marks->Visible = false;
      srs_pwv_bar->Marks->Visible = false;
      srs_delta->Marks->Visible = false;
      srs_delta_line_a->Marks->Visible = false;
      srs_delta_line_b->Marks->Visible = false;
      srs_dist_line->Marks->Visible = false;
   }
   clicked_series = false;
   series_index = 0;
}
//---------------------------------------------------------------------------
void __fastcall Tfrm_analysis_pwv::chrt_pwvGetAxisLabel(TChartAxis *Sender,
      TChartSeries *Series, int ValueIndex, AnsiString &LabelText)
{
   if (Sender == chrt_pwv->BottomAxis)
   {
      TeeSplitInLines(LabelText, ",");
   }
}
//---------------------------------------------------------------------------
void __fastcall Tfrm_analysis_pwv::pnl_separateResize(TObject *Sender)
{
  chrt_pwv->Height = pnl_separate->Height/3;
  chrt_delta->Height = pnl_separate->Height/4;
  chrt_dist->Height = pnl_separate->Height/6;
}
//---------------------------------------------------------------------------
void __fastcall Tfrm_analysis_pwv::chrt_hrateMouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
   TChart *chart = dynamic_cast<TChart *>(Sender);
   if (chart != NULL)
   {
      if (chart == chrt_hrate)
      {
         srs_hrate_a->Marks->Visible = true;
         srs_hrate_b->Marks->Visible = true;
      }
      if (chart == chrt_pwv)
      {
         srs_pwv_bar->Marks->Visible = true;
      }
      else if (chart == chrt_delta)
      {
          srs_delta->Marks->Visible = true;
          srs_delta_line_a->Marks->Visible = true;
          srs_delta_line_b->Marks->Visible = true;
      }
      else if (chart == chrt_dist)
      {
         srs_dist_line->Marks->Visible = true;
      }
   }
}
//---------------------------------------------------------------------------
void __fastcall Tfrm_analysis_pwv::chrt_hrateClickSeries(
      TCustomChart *Sender, TChartSeries *Series, int ValueIndex,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
   clicked_series = true;
   series_index = ValueIndex;
   srs_hrate_b->Marks->Visible = true;
   srs_hrate_a->Marks->Visible = true;
   srs_pwv_bar->Marks->Visible = true;
   srs_delta->Marks->Visible = true;
   srs_delta_line_a->Marks->Visible = true;
   srs_delta_line_b->Marks->Visible = true;
   srs_dist_line->Marks->Visible = true;
}
//---------------------------------------------------------------------------
void __fastcall Tfrm_analysis_pwv::srs_hrate_aGetMarkText(
      TChartSeries *Sender, int ValueIndex, AnsiString &MarkText)
{
   TeeSplitInLines(MarkText, ",");
   if (clicked_series)
   {
      if (ValueIndex != series_index)
      {
         MarkText = "";
      }
   }
}
//---------------------------------------------------------------------------

bool analysis_pwv_get_audit_initialised()
{
   return analysis_pwv_audit_initialised;
}
void __fastcall Tfrm_analysis_pwv::bbtn_printClick(TObject *Sender)
{
   int                  analysis_width;
   int                  analysis_height;
   int                  left_margin;
   TRect                print_rect;
   TPrinterOrientation  old_orient;
   TPrinter             *printer_ptr;
   TStringList          *an_list;
   AnsiString           S;

   printer_ptr = print_get_printer_ptr();
   if (printer_ptr==NULL)
   {
     return;
   }
   if (this->Visible)
   {
      if (MsgBox(MSG_PRINT_REPORT, CONFIRMATION, MB_YESNO | MB_ICONQUESTION) != ID_YES)
      {
        return;
      }
   }

   Screen->Cursor = crHourGlass;
   an_list = (frm_analysis_pwv->analysis_selected_measurements->Count > 0 ?
      frm_analysis_pwv->analysis_selected_measurements : frm_analysis_pwv->analysis_all_measurements);

   ClearSeries();
   ShowCharts(analysis_qry, an_list, true);

   old_orient = printer_ptr->Orientation;
   printer_ptr->Orientation  = poPortrait;
   printer_ptr->Title = "SphygmoCor PWV Analysis";

   try
   {
       pnl_separate->Align = alNone;
       pnl_separate->Height = ANALYSIS_PWV_PANEL_PRINT_HEIGHT;
       pnl_separate->Width = ANALYSIS_PWV_PANEL_PRINT_WIDTH;
       
       printer_ptr->BeginDoc();

       analysis_width =  printer_ptr->PageWidth;
       analysis_width = analysis_width - (analysis_width * 0.02);
       analysis_height = printer_ptr->PageHeight;
       left_margin = analysis_width * 0.06;

       print_rect.Top = analysis_height * 0.85;
       print_rect.Left = left_margin;
       print_rect.Right = analysis_width;
       print_rect.Bottom = analysis_height;
       print_do_footer(&print_rect, 0);

       print_rect.Top = analysis_height * 0.1;
       print_rect.Left = left_margin;
       print_rect.Right = analysis_width;
       print_rect.Bottom = analysis_height * 0.15;
       print_do_header(&print_rect, "SphygmoCor", "Pulse Wave Velocity Analysis");
       print_do_atcor_image(&print_rect);

       print_rect.Top = print_rect.Bottom;
       print_rect.Left = left_margin;
       print_rect.Right = analysis_width;
       print_rect.Bottom = analysis_height * 0.25;
       print_do_patient_data(&print_rect, 0, false, "", "", false);

       print_rect.Top = print_rect.Bottom;
       print_rect.Left = left_margin;
       print_rect.Right = analysis_width;
       print_rect.Bottom = analysis_height * 0.30;
       analysis_print_study_data(&print_rect);

       print_rect.Top = 0.30 * analysis_height;
       print_rect.Left = left_margin;
       print_rect.Right = analysis_width;
       print_rect.Bottom = analysis_height * 0.45;
       chrt_pwv->LeftAxis->LabelsFont->Color = sphygmocor_black;
       chrt_pwv->LeftAxis->Title->Font->Color = sphygmocor_black;
       chrt_pwv->BottomAxis->LabelsFont->Color = sphygmocor_black;
       chrt_pwv->BottomAxis->Title->Font->Color = sphygmocor_black;
       chrt_pwv->Title->Font->Color = sphygmocor_maroon;
       chrt_pwv->PrintPartial(print_rect);

       print_rect.Top = 0.45 * analysis_height;
       print_rect.Left = left_margin;
       print_rect.Right = analysis_width;
       print_rect.Bottom = analysis_height * 0.60;
       chrt_delta->LeftAxis->LabelsFont->Color = sphygmocor_black;
       chrt_delta->LeftAxis->Title->Font->Color = sphygmocor_black;
       chrt_delta->Title->Font->Color = sphygmocor_maroon;
       chrt_delta->PrintPartial(print_rect);

       print_rect.Top = 0.60 * analysis_height;
       print_rect.Left = left_margin;
       print_rect.Right = analysis_width;
       print_rect.Bottom = analysis_height * 0.70;
       chrt_dist->LeftAxis->LabelsFont->Color = sphygmocor_black;
       chrt_dist->LeftAxis->Title->Font->Color = sphygmocor_black;
       chrt_dist->Title->Font->Color = sphygmocor_maroon;
       chrt_dist->PrintPartial(print_rect);

       print_rect.Top = 0.70 * analysis_height;
       print_rect.Left = left_margin;
       print_rect.Right = analysis_width;
       print_rect.Bottom = analysis_height * 0.85;
       chrt_hrate->LeftAxis->LabelsFont->Color = sphygmocor_black;
       chrt_hrate->LeftAxis->Title->Font->Color = sphygmocor_black;
       chrt_hrate->Title->Font->Color = sphygmocor_maroon;
       chrt_hrate->PrintPartial(print_rect);

       printer_ptr->EndDoc();

       pnl_separate->Align = alClient;

       chrt_pwv->LeftAxis->LabelsFont->Color = sphygmocor_white;
       chrt_pwv->LeftAxis->Title->Font->Color = sphygmocor_white;
       chrt_pwv->BottomAxis->LabelsFont->Color = sphygmocor_white;
       chrt_pwv->BottomAxis->Title->Font->Color = sphygmocor_white;
       chrt_pwv->Title->Font->Color = sphygmocor_white;

       chrt_delta->LeftAxis->LabelsFont->Color = sphygmocor_white;
       chrt_delta->LeftAxis->Title->Font->Color = sphygmocor_white;
       chrt_delta->Title->Font->Color = sphygmocor_white;

       chrt_dist->LeftAxis->LabelsFont->Color = sphygmocor_white;
       chrt_dist->LeftAxis->Title->Font->Color = sphygmocor_white;
       chrt_dist->Title->Font->Color = sphygmocor_white;

       chrt_hrate->LeftAxis->LabelsFont->Color = sphygmocor_white;
       chrt_hrate->LeftAxis->Title->Font->Color = sphygmocor_white;
       chrt_hrate->Title->Font->Color = sphygmocor_white;
   }
   catch (Exception &exception)
   {
      printer_ptr->Abort();
      printer_ptr->EndDoc();
   }
   printer_ptr->Orientation = old_orient;
   Screen->Cursor = crDefault;
   ClearSeries();
   ShowCharts(analysis_qry, an_list, false);
   //SetFocus();   
}
//---------------------------------------------------------------------------


void __fastcall Tfrm_analysis_pwv::bbtn_selectClick(TObject *Sender)
{
  Tfrm_select *frm_select = new Tfrm_select(this, lbl_pat->Caption, analysis_qry,
                            analysis_all_measurements, analysis_input_measurements, analysis_selected_measurements,
                            MEAS_PWV_ID, ANALYSIS_MAX_PWV_MEASUREMENTS);
  if (frm_select == NULL)
  {
    return;
  }
  frm_select->ShowModal();
  if ((frm_select->ModalResult == mrOk) &&
     (analysis_selected_measurements->Count > 1))
  {
    // Show form charts
    ClearSeries();
    ShowCharts(analysis_qry,  analysis_selected_measurements, false);
  }
  delete frm_select;
  //SetFocus();   
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_analysis_pwv::bbtn_exportClick(TObject *Sender)
{
   Graphics::TBitmap*   bmp_image;
   PATIENT_RECORD_TYPE  pat;
   AnsiString           reptype_str = "ANALYSIS_";

   try
   {
      bmp_image = GetFormImage();
      if (bmp_image != NULL)
      {
         if (patient_get(&pat))
         {
            String attach_fname = ExtractFilePath(Application->ExeName) +EXPORT_SUBDIR +"PIC_" +reptype_str +pat.surname +"_"
                      +analysis_first_export +"_" +analysis_last_export +"_pwv.jpg";
            export_graphic(bmp_image, attach_fname);
         }
         delete bmp_image;
      }
   }
   catch (...)
   {
      (void)MsgBox_warning("Could Not Create Graphic.",
                           SWARNING);
   }
}
//---------------------------------------------------------------------------

