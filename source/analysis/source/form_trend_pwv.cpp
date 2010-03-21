//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include <stdlib.h>

#include <dbmgr/pubserv.h>
#include <patient/pubserv.h>
#include <meas/pubserv.h>
#include <msg/pubserv.h>
#include <log/pubserv.h>
#include <report/pubserv.h>
#include <export/pubserv.h>
#include <print/pubserv.h>
#include <analysis/pubserv.h>
#include <config/pubserv.h>
#include <scor/form_main.h>
#include <scor/utils.h>
#include "analysis.h"
#include "form_trend_pwv.h"
#include "form_analysis_pwv.h"
#include "form_select.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "ErrorBar"
#pragma resource "*.dfm"

const int TREND_PWV_PANEL_PRINT_HEIGHT = 480;
const int TREND_PWV_PANEL_PRINT_WIDTH = 960;

//---------------------------------------------------------------------------
__fastcall Tfrm_trend_pwv::Tfrm_trend_pwv(TComponent* Owner)
    : Child_Form(Owner)
{
    clicked_series = false;
    series_index = 0;
}
//---------------------------------------------------------------------------
void  __fastcall Tfrm_trend_pwv::FormShow(TObject *Sender)
{
  TStringList* lListOfMeasurements =
  (frm_analysis_pwv->analysis_selected_measurements->Count > 0 ?
   frm_analysis_pwv->analysis_selected_measurements : frm_analysis_pwv->analysis_all_measurements);

  if ((lListOfMeasurements->Count > 0) &&
      (frm_analysis_pwv->analysis_qry->RecordCount > 0))
  {
    ClearSeries();
    ShowCharts(lListOfMeasurements, false);
  }
  bbtn_print->Enabled = print_does_printer_exist();
  // If the audit option is set, disable export
   if (config_get_audit_option())
  {
      bbtn_export->Enabled = false;
  }
  SetFocus();
}
//---------------------------------------------------------------------------
void __fastcall Tfrm_trend_pwv::ShowCharts(TStringList *pList, bool is_print)
{
   int     nr = 0;
   int     valid_count = 0;
   String  title;
   TColor  axis_color;
   TColor  title_color;
   
   Screen->Cursor = crHourGlass;
   try
   {
    // Activate progress bar
    frm_main->prgbar_main->Visible = true;
    frm_main->prgbar_main->Min = 0;
    if (frm_analysis_pwv->analysis_qry->RecordCount > ANALYSIS_MAX_PWA_MEASUREMENTS)
    {
      frm_main->prgbar_main->Max = ANALYSIS_MAX_PWA_MEASUREMENTS;
    }
    else
    {
     frm_main->prgbar_main->Max = frm_analysis_pwv->analysis_qry->RecordCount;
    }
    frm_main->prgbar_main->Step = 1;
    frm_main->prgbar_main->Position = 0;

    lbl_pat->Caption = patient_get_name();

    if (is_print)
    {
      axis_color = sphygmocor_black;
      title_color = sphygmocor_maroon;
    }
    else
    {
      axis_color = sphygmocor_white;
      title_color = sphygmocor_white;
    }

    chrt_hrate->PrintResolution = -100;
    chrt_hrate->LeftAxis->LabelsFont->Color = axis_color;
    chrt_hrate->LeftAxis->Title->Font->Color = axis_color;
    chrt_hrate->Title->Font->Color = title_color;

    chrt_delta->PrintResolution = -100;
    chrt_delta->LeftAxis->LabelsFont->Color = axis_color;
    chrt_delta->LeftAxis->Title->Font->Color = axis_color;
    chrt_delta->Title->Font->Color = title_color;

    chrt_dist->PrintResolution = -100;
    chrt_dist->LeftAxis->LabelsFont->Color = axis_color;
    chrt_dist->LeftAxis->Title->Font->Color = axis_color;
    chrt_dist->BottomAxis->LabelsFont->Color = axis_color;
    chrt_dist->BottomAxis->Title->Font->Color = axis_color;
    chrt_dist->Title->Font->Color = title_color;

    int total_records = (pList->Count > ANALYSIS_MAX_PWV_MEASUREMENTS ?
      ANALYSIS_MAX_PWV_MEASUREMENTS : pList->Count);

    for (frm_analysis_pwv->analysis_qry->Last(); !frm_analysis_pwv->analysis_qry->Bof && valid_count < ANALYSIS_MAX_PWV_MEASUREMENTS; frm_analysis_pwv->analysis_qry->Prior())
    {
      frm_main->prgbar_main->Position = nr++;
      if (pList->IndexOf(frm_analysis_pwv->analysis_qry->FieldByName(MPW_DATETIME)->AsDateTime.FormatString(ANALYSIS_DATETIME_FORMAT)) < 0)
      {
         continue;
      }
      if (frm_analysis_pwv->analysis_pwv->Populate(frm_analysis_pwv->analysis_qry)==false)
      {
         continue;
      }
      // Distance
      if (frm_analysis_pwv->analysis_pwv->Distance != DEFAULT_VALUE)
      {
        title = frm_analysis_pwv->analysis_pwv->DateTime.FormatString(ANALYSIS_DATETIME_FORMAT);
        srs_dist_line->AddXY(total_records - valid_count,
                             frm_analysis_pwv->analysis_pwv->Distance,
                             title, clTeeColor);
      }
      else
      {
        srs_dist_line->AddNull(ANALYSIS_NOT_CALCULATED);
      }

      // Heart Rate Site A
      if (frm_analysis_pwv->analysis_pwv->SiteA.HeartRate != DEFAULT_VALUE)
      {
        srs_hrate_a->AddXY(total_records - valid_count,
                           math_Round(frm_analysis_pwv->analysis_pwv->SiteA.HeartRate),
                           "", clTeeColor);
      }
      else
      {
        srs_hrate_a->AddNull(ANALYSIS_NOT_CALCULATED);
      }
      // Heart Rate Site B
      if (frm_analysis_pwv->analysis_pwv->SiteB.HeartRate != DEFAULT_VALUE)
      {
        srs_hrate_b->AddXY(total_records - valid_count,
                           math_Round(frm_analysis_pwv->analysis_pwv->SiteB.HeartRate),
                           "", clTeeColor);
      }
      else
      {
        srs_hrate_b->AddNull(ANALYSIS_NOT_CALCULATED);
      }

      // Delta T Site A

      if (frm_analysis_pwv->analysis_pwv->SiteA.MeanDT != DEFAULT_VALUE)
      {
        title = frm_analysis_pwv->analysis_pwv->DateTime.FormatString(ANALYSIS_DATETIME_FORMAT);
        srs_delta_line_a->AddXY(total_records - valid_count,
                                math_Round(frm_analysis_pwv->analysis_pwv->SiteA.MeanDT),
                                "", clTeeColor);
        title = FormatFloat("###.#", frm_analysis_pwv->analysis_pwv->SiteA.MeanDT) +
                "±" + FormatFloat("##0.0", frm_analysis_pwv->analysis_pwv->SiteA.Deviation);
        srs_delta_error_a->AddErrorBar(total_records - valid_count,
                                       frm_analysis_pwv->analysis_pwv->SiteA.MeanDT,
                                       frm_analysis_pwv->analysis_pwv->SiteA.Deviation,
                                       title, clTeeColor);
      }
      else
      {
        srs_delta_line_a->AddNull(ANALYSIS_NOT_CALCULATED);
        srs_delta_error_a->AddNull(ANALYSIS_NOT_CALCULATED);
      }
      // Delta T Site B
      if (frm_analysis_pwv->analysis_pwv->SiteB.MeanDT != DEFAULT_VALUE)
      {
        title = frm_analysis_pwv->analysis_pwv->DateTime.FormatString(ANALYSIS_DATETIME_FORMAT);
        srs_delta_line_b->AddXY(total_records - valid_count,
                                math_Round(frm_analysis_pwv->analysis_pwv->SiteB.MeanDT),
                                "", clTeeColor);
        title = FormatFloat("###.#", frm_analysis_pwv->analysis_pwv->SiteB.MeanDT) +
                "±" + FormatFloat("##0.0", frm_analysis_pwv->analysis_pwv->SiteB.Deviation);
        srs_delta_error_b->AddErrorBar(total_records - valid_count,
                            frm_analysis_pwv->analysis_pwv->SiteB.MeanDT,
                            frm_analysis_pwv->analysis_pwv->SiteB.Deviation,
                            title, clTeeColor);
      }
      else
      {
        srs_delta_line_b->AddNull(ANALYSIS_NOT_CALCULATED);
        srs_delta_error_b->AddNull(ANALYSIS_NOT_CALCULATED);
      }

      // Main Delta T
      if (frm_analysis_pwv->analysis_pwv->MeanDT != DEFAULT_VALUE)
      {
        title = FormatFloat("###.#", frm_analysis_pwv->analysis_pwv->MeanDT) +
                "±" + FormatFloat("##0.0", frm_analysis_pwv->analysis_pwv->DeviationDT);
        srs_delta_error->AddErrorBar(total_records - valid_count,
                            frm_analysis_pwv->analysis_pwv->MeanDT,
                            frm_analysis_pwv->analysis_pwv->DeviationDT,
                            title, clTeeColor);
        title = frm_analysis_pwv->analysis_pwv->DateTime.FormatString(ANALYSIS_DATETIME_FORMAT);
        srs_delta->AddXY(total_records - valid_count,
                         math_Round(frm_analysis_pwv->analysis_pwv->MeanDT),
                         "", clTeeColor);
      }
      else
      {
        srs_delta->AddNull(ANALYSIS_NOT_CALCULATED);
        srs_delta_error->AddNull(ANALYSIS_NOT_CALCULATED);
      }
      valid_count++;
    }

    int hrate_min = min(srs_hrate_a->MinYValue(), srs_hrate_b->MinYValue()) - 10;
    int hrate_max = max(srs_hrate_a->MaxYValue(), srs_hrate_b->MaxYValue()) + 10;
    chrt_hrate->LeftAxis->SetMinMax(hrate_min, hrate_max);
    chrt_hrate->BottomAxis->SetMinMax(0, valid_count + 1);

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
  catch(Exception &exc)
  {
    log_write(SEXCEPTION +exc.Message);
  }
  Screen->Cursor = crDefault;
  frm_main->prgbar_main->Visible = false;
}

//---------------------------------------------------------------------------
void __fastcall Tfrm_trend_pwv::FormKeyPress(TObject *Sender, char &Key)
{
   Child_Form *analysis_form;
   if (Key == VK_SPACE || Key == VK_RETURN)
   {
      Hide();
      analysis_form = analysis_get_analysis_form_pointer();
      if (analysis_form != NULL)
      {
         frm_analysis_pwv->Caller = "Trend";
         analysis_form->Show();
      }
   }
}
//---------------------------------------------------------------------------
void __fastcall Tfrm_trend_pwv::ClearSeries()
{
   AnsiString name_str("TChart");
   TChart     *chrt;
   int        i;

   for (i = 0; i < ComponentCount; i++)
   {
      if (Components[i]->ClassNameIs(name_str))
      {
         chrt = (TChart *)Components[i];
         if (chrt != NULL)
         {
            for (int j = 0; j < chrt->SeriesCount(); j++)
            {
               chrt->Series[j]->Clear();
            }
         }
      }
   }
}

//---------------------------------------------------------------------------
void __fastcall Tfrm_trend_pwv::pnl_middleResize(TObject *Sender)
{
  chrt_hrate->Height = pnl_middle->Height * 0.3;
  chrt_delta->Height = pnl_middle->Height * 0.4;
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_trend_pwv::chrt_distGetAxisLabel(TChartAxis *Sender,
      TChartSeries *Series, int ValueIndex, AnsiString &LabelText)
{
    if (Sender == chrt_dist->BottomAxis)
    {
      TeeSplitInLines(LabelText, ",");
    }
}
//---------------------------------------------------------------------------
void __fastcall Tfrm_trend_pwv::chrt_hrateMouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
   TChart *chart;

   chart = dynamic_cast<TChart *>(Sender);
   if (chart != NULL)
   {
      if (chart == chrt_hrate)
      {
         srs_hrate_a->Marks->Visible = true;
         srs_hrate_b->Marks->Visible = true;
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
void __fastcall Tfrm_trend_pwv::chrt_hrateMouseUp(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
   TChart *chart = dynamic_cast<TChart *>(Sender);
   if (chart != NULL)
   {
      srs_hrate_a->Marks->Visible = false;
      srs_hrate_b->Marks->Visible = false;
      srs_delta->Marks->Visible = false;
      srs_delta_line_a->Marks->Visible = false;
      srs_delta_line_b->Marks->Visible = false;
      srs_dist_line->Marks->Visible = false;
   }
   clicked_series = false;
   series_index = 0;
}
//---------------------------------------------------------------------------
void __fastcall Tfrm_trend_pwv::chrt_hrateClickSeries(TCustomChart *Sender,
      TChartSeries *Series, int ValueIndex, TMouseButton Button,
      TShiftState Shift, int X, int Y)
{
   clicked_series = true;
   series_index = ValueIndex;

   srs_delta->Marks->Visible = true;
   srs_delta_line_a->Marks->Visible = true;
   srs_delta_line_b->Marks->Visible = true;
   srs_dist_line->Marks->Visible = true;
   srs_hrate_a->Marks->Visible = true;
   srs_hrate_b->Marks->Visible = true;
}
//---------------------------------------------------------------------------
void __fastcall Tfrm_trend_pwv::srs_hrate_aGetMarkText(
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


void __fastcall Tfrm_trend_pwv::bbtn_printClick(TObject *Sender)
{
   int                  analysis_width;
   int                  analysis_height;
   int                  left_margin;
   TRect                print_rect;
   TStringList          *tr_list;
   TPrinterOrientation  old_orient;
   TPrinter             *printer_ptr;
   AnsiString           S;
   AnsiString           name_str("TChart");

   if (this->Visible)
   {
      if (MsgBox(MSG_PRINT_REPORT, CONFIRMATION, MB_YESNO | MB_ICONQUESTION) != ID_YES)
      {
         //SetFocus();
         return;
      }
   }

  printer_ptr = print_get_printer_ptr();
  if (printer_ptr==NULL)
    return;

  Screen->Cursor = crHourGlass;

  tr_list = (frm_analysis_pwv->analysis_selected_measurements->Count > 0 ?
     frm_analysis_pwv->analysis_selected_measurements : frm_analysis_pwv->analysis_all_measurements);

   ClearSeries();
   ShowCharts(tr_list, true);
   old_orient = printer_ptr->Orientation;
   printer_ptr->Orientation  = poPortrait;
   printer_ptr->Title = "SphygmoCor PWV Trend";

   try
   {
       pnl_middle->Align = alNone;
       pnl_middle->Height = TREND_PWV_PANEL_PRINT_HEIGHT;
       pnl_middle->Width = TREND_PWV_PANEL_PRINT_WIDTH;
       chrt_hrate->Height = pnl_middle->Height * 0.3;
       chrt_delta->Height = pnl_middle->Height * 0.4;
       
       printer_ptr->BeginDoc();

      analysis_width =  printer_ptr->PageWidth;
      analysis_width = analysis_width - (analysis_width * 0.02);
      left_margin = analysis_width * 0.06;
      analysis_height = printer_ptr->PageHeight;

      print_rect.Top = analysis_height * 0.9;
      print_rect.Left = left_margin;
      print_rect.Right = analysis_width;
      print_rect.Bottom = analysis_height;
      print_do_footer(&print_rect, 0);

      print_rect.Top = analysis_height * 0.1;
      print_rect.Left = left_margin;
      print_rect.Right = analysis_width;
      print_rect.Bottom = analysis_height * 0.15;
      print_do_header(&print_rect, "SphygmoCor", "Pulse Wave Velocity Trend Report");
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

      print_rect.Top = 0.3 * analysis_height;
      print_rect.Left = left_margin;
      print_rect.Right = analysis_width;
      print_rect.Bottom = analysis_height * 0.5;
      chrt_hrate->PrintPartial(print_rect);

      print_rect.Top = 0.5 * analysis_height;
      print_rect.Left = left_margin;
      print_rect.Right = analysis_width;
      print_rect.Bottom = analysis_height * 0.75;
      chrt_delta->PrintPartial(print_rect);

      print_rect.Top = 0.75 * analysis_height;
      print_rect.Left = left_margin;
      print_rect.Right = analysis_width;
      print_rect.Bottom = analysis_height * 0.9;
      chrt_dist->PrintPartial(print_rect);

      printer_ptr->EndDoc();

      pnl_middle->Align = alClient;
   }
   catch (Exception &exception)
   {
      printer_ptr->Abort();
      printer_ptr->EndDoc();
   }
   printer_ptr->Orientation = old_orient;
   Screen->Cursor = crDefault;

   ClearSeries();
   ShowCharts(tr_list, false);
   //SetFocus();   
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_trend_pwv::bbtn_waveClick(TObject *Sender)
{
   Hide();
   char keypress = VK_SPACE;
   FormKeyPress(Sender, keypress);   
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_trend_pwv::bbtn_exportClick(TObject *Sender)
{
   Graphics::TBitmap*   bmp_image;
   PATIENT_RECORD_TYPE  pat;
   AnsiString           reptype_str = "TREND_";

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

