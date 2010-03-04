//---------------------------------------------------------------------------
#include <vcl.h>
#include <Series.hpp>
#pragma hdrstop

#include <stdlib.h>
#include <math.h>

#include <dbmgr/pubserv.h>
#include <meas/pubserv.h>
#include <patient/pubserv.h>
#include <export/pubserv.h>
#include <print/pubserv.h>
#include <report/pubserv.h>
#include <analysis/pubserv.h>
#include <log/pubserv.h>
#include <msg/pubserv.h>
#include <config/pubserv.h>
#include <scor/form_main.h>
#include <scor/utils.h>
#include "analysis.h"
#include "form_analysis_pwa.h"
#include "form_select.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

const int ANALYSIS_PANEL_PRINT_HEIGHT = 320;
const int ANALYSIS_PANEL_PRINT_WIDTH = 640;

VAR_EXPORT bool analysis_pwa_audit_initialised;

//---------------------------------------------------------------------------
__fastcall Tfrm_analysis_pwa::Tfrm_analysis_pwa(TComponent* Owner)
    : Child_Form(Owner)
{
   Caller = "";
   analysis_input_measurements = new TStringList;
   analysis_selected_measurements = new TStringList;
   analysis_all_measurements = new TStringList;
   analysis_pwa_audit_initialised = true;
}

void __fastcall Tfrm_analysis_pwa::FormShow(TObject *Sender)
{
   MEAS_ID_TYPE  meas_mode;
   analysis_pwa_audit_initialised = true;

   if (Caller == "Trend")
   {
      Caller = "";
      chrt_periph->UndoZoom();
      chrt_central->UndoZoom();
      SetFocus();
      return;
   }
   Caller = "";

   PATIENT_RECORD_TYPE  pat;
   if (patient_get(&pat) == false)
   {
      return;
   }

   // Only the full list allocates memory and therefore needs to delete the objects
   analysis_input_measurements->Clear();
   analysis_selected_measurements->Clear();
   Analysis_ClearList(analysis_all_measurements);

   meas_mode = patient_get_study_mode();
   switch (meas_mode)
   {
      case MEAS_PWA_ID:
      {
         analysis_pwa = meas_get_current_pwa();
         if (config_get_audit_option())
         {
            // Query the database for reports that haven't been deleted
            analysis_qry = dbmgr_setup_query(DBMGR_MEASURE_PWA_TABLE,
                                          DBMGR_QUERY_AUDIT_FLAG,
                                          PATIENT_SYSTEM_ID,
                                          PATIENT_STUDY_ID,
                                          PATIENT_NO,
                                          MPWA_AUDIT_FLAG,
                                          pat.system_id,
                                          pat.study_id,
                                          IntToStr(pat.number),
                                          IntToStr(AUDIT_DELETED),
                                          MPW_DATETIME);
         }
         else
         {
            analysis_qry = dbmgr_setup_query(DBMGR_MEASURE_PWA_TABLE,
                                          DBMGR_QUERY_KEY,
                                          PATIENT_SYSTEM_ID,
                                          PATIENT_STUDY_ID,
                                          PATIENT_NO,
                                          pat.system_id,
                                          pat.study_id,
                                          IntToStr(pat.number),
                                          MPW_DATETIME);
         }
         break;
      }
      case MEAS_PWM_ID:
      {
         TPWM *pwm = meas_get_current_pwm();
         analysis_pwa= dynamic_cast<TPWA *>(pwm);
         analysis_qry = dbmgr_setup_query(DBMGR_MEASURE_PWM_TABLE,
                                          DBMGR_QUERY_KEY,
                                          PATIENT_SYSTEM_ID,
                                          PATIENT_STUDY_ID,
                                          PATIENT_NO,
                                          MPWM_SESSION_ID,
                                          pat.system_id,
                                          pat.study_id,
                                          IntToStr(pat.number),
                                          IntToStr(pwm->Session_ID),
                                          MPW_DATETIME);
         break;
      }
      default:
        return;
   }

   if ((analysis_qry==NULL) || (analysis_qry->Active == false))
   {
      return;
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
            analysis_pwa_audit_initialised = false;
            return;
      }
   }

   // Save all measurements in a list and allocate memory for objects
   if (analysis_all_measurements->Count <= 0)
   {
      for (analysis_qry->First();!analysis_qry->Eof;analysis_qry->Next())
      {
         analysis_all_measurements->AddObject(analysis_qry->FieldByName(MPW_DATETIME)->AsDateTime.FormatString(ANALYSIS_DATETIME_FORMAT),
                                              (TObject *)(new TDateTime(analysis_qry->FieldByName(MPW_DATETIME)->AsDateTime)));
      }
   }

   // The default is to diplay radial measurements only
   analysis_artery = "RADIAL";
   if (analysis_all_measurements->Count > 0)
   {
      int i = analysis_all_measurements->Count - 1;
      int count = 0;
      if (analysis_selected_measurements->Count <= 0)
      {
         for (analysis_qry->Last(); !analysis_qry->Bof; analysis_qry->Prior())
         {
            if (analysis_qry->FieldByName(MPWA_SUB_TYPE)->AsString == analysis_artery)
            {

               // Store the maximum number of pwa measurements in the selected measurements list
               if (count < ANALYSIS_MAX_PWA_MEASUREMENTS)
               {
                  analysis_selected_measurements->AddObject(analysis_all_measurements->Strings[i],
                                                            analysis_all_measurements->Objects[i]);
                  count++;
               }
               // Store the rest in the input measurements list
               else
               {
                  analysis_input_measurements->AddObject(analysis_all_measurements->Strings[i],
                                                            analysis_all_measurements->Objects[i]);
               }
            }
            i--;
         }
      }
   }

   // If there are less than 2 Radial measurements, then display All
   ClearSeries();
   if (analysis_selected_measurements->Count < 2)
   {
      analysis_artery = "All";
      analysis_selected_measurements->Clear();
      analysis_input_measurements->Clear();
      analysis_input_measurements->AddStrings(analysis_all_measurements);
      ShowCharts(analysis_qry, analysis_all_measurements);
   }
   else
   {
      ShowCharts(analysis_qry, analysis_selected_measurements);
   }

   lbl_periph_data->Caption = "";
   lbl_central_data->Caption = "";

   bbtn_print->Enabled = print_does_printer_exist();
   // If the audit option is set, disable export
   if (config_get_audit_option())
   {
      bbtn_export->Enabled = false;
   }
   SetFocus();
}

void __fastcall Tfrm_analysis_pwa::ShowCharts(TDataSet *analysis_qry, TStringList *pList)
{
  TLineSeries    *line_series;
  TPointSeries   *central_point_series;
  TPointSeries   *periph_point_series;
  TColor         ed_col;
  String         title;

  int     j;
  int     k;
  int     ed_idx;
  int     corrupt_count = 0;
  int     valid_count = 0;
  double  max_central = 0.0F;
  double  max_periph = 0.0F;
  double  min_central = 200.0F;
  double  min_periph = 200.0F;
  double  max_time = 0;

  float max_cal_central = 0.0F;
  float max_cal_peripheral = 0.0F;
  float min_cal_central = 0.0F;
  float min_cal_peripheral = 0.0F;
  float graph_value;

  analysis_pwa = meas_get_current_pwa();

  // Activate progress bar
  // PM V9
  Screen->Cursor = crHourGlass;
  frm_main->prgbar_main->Visible = true;
  frm_main->prgbar_main->Min = 0;
  frm_main->prgbar_main->Max = max(analysis_qry->RecordCount, ANALYSIS_MAX_PWA_MEASUREMENTS);
  frm_main->prgbar_main->Step = 1;
  frm_main->prgbar_main->Position = 0;

  lbl_pat->Caption = patient_get_name();
  if (config_get_clinical_option())
  {
      lbl_art->Caption = "";
  }
  else
  {
      lbl_art->Caption = "  (" + analysis_artery + " Arteries)";
  }
  central_point_series = new TPointSeries(this);
  central_point_series->Title = "ED";
  central_point_series->Pointer->HorizSize = 3;
  central_point_series->Pointer->VertSize = 3;
  central_point_series->Pointer->Style = psRectangle;
  central_point_series->Pointer->Pen->Color = sphygmocor_black;

  periph_point_series = new TPointSeries(this);
  periph_point_series->Title = "ED";
  periph_point_series->Pointer->HorizSize = 3;
  periph_point_series->Pointer->VertSize = 3;
  periph_point_series->Pointer->Style = psRectangle;
  periph_point_series->Pointer->Pen->Color = sphygmocor_black;

  // Looping selected measurements
  int nr = 0; k = 0;
  for (analysis_qry->Last(); !analysis_qry->Bof && k < ANALYSIS_MAX_PWA_MEASUREMENTS; analysis_qry->Prior())
  {
    frm_main->prgbar_main->Position = nr++;
    if (pList->IndexOf(analysis_qry->FieldByName(MPW_DATETIME)->AsDateTime.FormatString(ANALYSIS_DATETIME_FORMAT)) < 0)
    {
      continue;
    }
    if (analysis_pwa->Populate(analysis_qry)==false)
    {
      ++corrupt_count;
      continue;
    }

    // Find first and last studies
    if (valid_count > 0)
    {
       analysis_first_study = analysis_pwa->DateTime.FormatString(ANALYSIS_DATETIME_FORMAT);
       analysis_first_export = analysis_pwa->DateTime.FormatString(ANALYSIS_DATETIME_EXPORT_FORMAT);
    }
    else
    {
       analysis_last_study = analysis_pwa->DateTime.FormatString(ANALYSIS_DATETIME_FORMAT);
       analysis_last_export = analysis_pwa->DateTime.FormatString(ANALYSIS_DATETIME_EXPORT_FORMAT);
    }

    line_series = new TLineSeries(this);
    line_series->LinePen->Visible = true;
    line_series->Pointer->Visible = false;
    line_series->Title = analysis_pwa->DateTime.FormatString(ANALYSIS_DATETIME_FORMAT) +
                         ", " + RoundIntToStr(analysis_pwa->Periph.Sp) + "/" + RoundIntToStr(analysis_pwa->Periph.Dp)
                         + "(" + RoundIntToStr(analysis_pwa->Periph.MeanP) + ")";
    title = analysis_pwa->DateTime.FormatString(ANALYSIS_DATETIME_FORMAT);

    float offset = (140 - 60);
    float lGain;
    if (analysis_pwa->Periph.CalAvPulse.MinMax(min_cal_peripheral,
                                               max_cal_peripheral))
    {
      lGain = offset / (max_cal_peripheral - min_cal_peripheral);
      for (j = 0; j < analysis_pwa->Periph.CalAvPulse.Length(); j++)
      {
         //scale each graph between 140mmHg and 60mmHg
         graph_value = lGain * (analysis_pwa->Periph.CalAvPulse.Profile[j] - min_cal_peripheral) + offset;
         //ensure that each graph doesn't overlap with others
         line_series->AddXY(j * (1000.0 / analysis_pwa->SampleRate),
                            graph_value + (k * 15),
                            "", sphygmocor_black);
      }
    }
    if (analysis_pwa->Periph.ED != DEFAULT_VALUE && (analysis_pwa->Periph.ED < analysis_pwa->Central.Period))
    {
       ed_idx = math_TimeToIndex(analysis_pwa->Periph.ED, 1, analysis_pwa->SampleRate);
       if (ed_idx > 0)
       {
          if ((fabs(analysis_pwa->Periph.ED - analysis_pwa->Periph.CalcED) > 0.5))
          {
             ed_col = sphygmocor_pink;
          }
          else
          {
             ed_col = sphygmocor_grey;
          }
          periph_point_series->AddXY(analysis_pwa->Periph.ED,
                                     line_series->YValues->Value[ed_idx],
                                     "", ed_col);
       }
    }
    chrt_periph->AddSeries(line_series);
    line_series->Active = true;

    if (line_series->MaxYValue() > max_periph)
    {
       max_periph = line_series->MaxYValue();
    }
    if (line_series->MinYValue() < min_periph)
    {
       min_periph = line_series->MinYValue();
    }

    line_series = new TLineSeries(this);

    line_series->LinePen->Visible = true;
    line_series->Pointer->Visible = false;

    line_series->Title = analysis_pwa->DateTime.FormatString(ANALYSIS_DATETIME_FORMAT)
                         + ", " + RoundIntToStr(analysis_pwa->Central.Sp) + "/" + RoundIntToStr(analysis_pwa->Central.Dp)
                         + "(" + RoundIntToStr(analysis_pwa->Central.MeanP) + ")";

    if (analysis_pwa->Central.CalAvPulse.MinMax(min_cal_central, max_cal_central))
    {
      lGain = offset / (max_cal_central - min_cal_central);
      for (j = 0; j < analysis_pwa->Central.CalAvPulse.Length(); j++)
      {
           graph_value = lGain * (analysis_pwa->Central.CalAvPulse.Profile[j] - min_cal_central) + offset;
           //ensure that each graph doesn't overlap with others
           line_series->AddXY(j * (1000.0 / analysis_pwa->SampleRate),
                              graph_value + (k * 15),
                              "", sphygmocor_navy);
      }
    }

    if (analysis_pwa->Central.ED != DEFAULT_VALUE && (analysis_pwa->Central.ED < analysis_pwa->Central.Period))
    {
       ed_idx = math_TimeToIndex(analysis_pwa->Central.ED, 1, analysis_pwa->SampleRate);
       if (ed_idx > 0)
       {
          ed_col = (fabs(analysis_pwa->Central.ED - analysis_pwa->Central.CalcED) < 0.5 ?
                    sphygmocor_grey : sphygmocor_pink);
          central_point_series->AddXY(analysis_pwa->Central.ED,
                                      line_series->YValues->Value[ed_idx], "", ed_col);
       }
    }

    chrt_central->AddSeries(line_series);
    line_series->Active = true;

    if (line_series->MaxYValue() > max_central)
    {
       max_central = line_series->MaxYValue();
    }
    if (line_series->MinYValue() < min_central)
    {
       min_central = line_series->MinYValue();
    }
    if (max_time < analysis_pwa->Periph.CalAvPulse.Length())
    {
       max_time = analysis_pwa->Periph.CalAvPulse.Length();
    }
    ++valid_count;
    k++;
  }

  if (valid_count > 1)
  {
     chrt_periph->AddSeries(periph_point_series);
     chrt_central->AddSeries(central_point_series);
     central_point_series->Active = true;
     periph_point_series->Active = true;

     if (max_periph < max_central)
     {
        max_periph = max_central;
     }

     if (min_periph > min_central)
     {
        min_periph = min_central;
     }
     max_periph += 10;

     max_time = 1000;
     chrt_periph->LeftAxis->SetMinMax(min_periph, max_periph);
     chrt_central->LeftAxis->SetMinMax(min_periph, max_periph);
     chrt_periph->BottomAxis->SetMinMax(0, max_time);
     chrt_central->BottomAxis->SetMinMax(0, max_time);
     frm_main->prgbar_main->Visible = false;
     Screen->Cursor = crDefault;
     bbtn_print->Enabled = true;
     bbtn_trend->Enabled = true;

     lbl_first_last_waveform->Caption = analysis_first_study +" - " +analysis_last_study;
     lbl_first->Caption = analysis_first_study;
     lbl_last->Caption = analysis_last_study;
  }
  else
  {
     // put in a message and log
     Screen->Cursor = crDefault;
     frm_main->prgbar_main->Visible = false;
     bbtn_print->Enabled = false;
     bbtn_trend->Enabled = false;
     MsgBox(TERROR, MSG_SYSTEM_ERROR, MSG_ANALYSIS_INVALID_COUNT);
  }
}
//---------------------------------------------------------------------------
void __fastcall Tfrm_analysis_pwa::ClearSeries()
{
   for (int j = chrt_periph->SeriesCount() - 1; j >= 0 ; j--)
   {
      chrt_periph->Series[j]->Clear();
      chrt_periph->Series[j]->Free();
   }
   for (int j = chrt_central->SeriesCount() - 1; j >= 0 ; j--)
   {
      chrt_central->Series[j]->Clear();
      chrt_central->Series[j]->Free();
   }
   chrt_periph->UndoZoom();
   chrt_central->UndoZoom();
}
//---------------------------------------------------------------------------
void __fastcall Tfrm_analysis_pwa::chrt_periphMouseMove(TObject *Sender,
      TShiftState Shift, int X, int Y)
{
   bool     clicked_series = false;
   long int in_region;
   int      j;
   TChart   *chart;
   TLabel   *lbl_data;

   chart = dynamic_cast<TChart *>(Sender);
   if (chart)
   {
      if (chart == chrt_periph)
      {
         lbl_data = lbl_periph_data;
      }
      else
      {
         lbl_data = lbl_central_data;
      }
      j = chart->SeriesCount() - 1;
      while (j >= 0 && !clicked_series)
      {
         in_region = chart->Series[j]->Clicked(X, Y);
         if (in_region != -1)
         {
            if (chart->Series[j]->Title == "ED")
            {
               lbl_data->Caption = "ED = " + RoundIntToStr(chart->Series[j]->XValues->Value[in_region]) + " ms";
            }
            else
            {
               lbl_data->Caption = chart->Series[j]->Title;
            }
            clicked_series = true;
         }
         j = j - 1;
      }
      if (!clicked_series)
      {
         lbl_data->Caption = "";
      }
   }
}
//---------------------------------------------------------------------------
void __fastcall Tfrm_analysis_pwa::FormKeyPress(TObject *Sender, char &Key)
{
   // Show trend form if SPACE pressed
   if (Key == VK_SPACE || Key == VK_RETURN)
   {
      bbtn_trendClick(Sender);
   }
   else if (Key == VK_ESCAPE)
   {
      frm_main->spdbtn_patientClick(Sender);
   }
}
//---------------------------------------------------------------------------
void __fastcall Tfrm_analysis_pwa::pnl_separateResize(TObject *Sender)
{
   chrt_periph->Width  = pnl_separate->Width * 0.46;
   chrt_central->Width = pnl_separate->Width * 0.46;
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_analysis_pwa::FormDestroy(TObject *Sender)
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

bool analysis_pwa_get_audit_initialised()
{
   return analysis_pwa_audit_initialised;
}
void __fastcall Tfrm_analysis_pwa::bbtn_printClick(TObject *Sender)
{
   TLineSeries          *srs;
   int                  analysis_width;
   int                  analysis_height;
   int                  left_margin;
   TRect                print_rect;
   TPrinterOrientation  old_orient;
   TPrinter             *printer_ptr;
   AnsiString           S;
   int                  j;

   if (this->Visible)
   {
      if (MsgBox(MSG_PRINT_REPORT, CONFIRMATION, MB_YESNO | MB_ICONQUESTION) != ID_YES)
      {
        return;
      }
   }

   printer_ptr = print_get_printer_ptr();
   Screen->Cursor = crHourGlass;
   old_orient = printer_ptr->Orientation;
   printer_ptr->Orientation  = poPortrait;
   printer_ptr->Title = "SphygmoCor PWA Analysis";
   try
   {
       // PM CR
       chrt_periph->UndoZoom();
       chrt_central->UndoZoom();

       pnl_separate->Align = alNone;
       pnl_separate->Height = ANALYSIS_PANEL_PRINT_HEIGHT;
       pnl_separate->Width = ANALYSIS_PANEL_PRINT_WIDTH;

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
       print_do_header(&print_rect, "SphygmoCor", "Patient Waveform Analysis");
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
       print_rect.Right = left_margin + (analysis_width - left_margin) * 0.48;
       print_rect.Bottom = analysis_height * 0.85;
       chrt_periph->PrintResolution = -100;
       chrt_periph->BottomAxis->LabelsFont->Color = sphygmocor_black;
       chrt_periph->BottomAxis->Title->Font->Color = sphygmocor_black;
       chrt_periph->Title->Font->Color = sphygmocor_maroon;
       chrt_periph->PrintPartial(print_rect);

       print_rect.Top = 0.3 * analysis_height;
       print_rect.Left = left_margin + (analysis_width - left_margin) * 0.52;
       print_rect.Right = analysis_width;
       print_rect.Bottom = analysis_height * 0.85;
       chrt_central->PrintResolution = -100;
       chrt_central->BottomAxis->LabelsFont->Color = sphygmocor_black;
       chrt_central->BottomAxis->Title->Font->Color = sphygmocor_black;
       chrt_central->Title->Font->Color = sphygmocor_maroon;
       chrt_central->PrintPartial(print_rect);

       printer_ptr->EndDoc();
       // PM CR - moved these after EndDoc
       chrt_periph->BottomAxis->LabelsFont->Color = sphygmocor_white;
       chrt_periph->BottomAxis->Title->Font->Color = sphygmocor_white;
       chrt_periph->Title->Font->Color = sphygmocor_white;

       chrt_central->BottomAxis->LabelsFont->Color = sphygmocor_white;
       chrt_central->BottomAxis->Title->Font->Color = sphygmocor_white;
       chrt_central->Title->Font->Color = sphygmocor_white;

       pnl_separate->Align = alClient;
   }
   catch (Exception &exception)
   {
      printer_ptr->Abort();
      printer_ptr->EndDoc();
   }
   printer_ptr->Orientation = old_orient;
   Screen->Cursor = crDefault;
   //SetFocus();   
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_analysis_pwa::bbtn_trendClick(TObject *Sender)
{
   Hide();
   Child_Form *analysis_trend_form;
   analysis_trend_form = analysis_get_trend_form_pointer();
   if (analysis_trend_form != NULL)
   {
      analysis_trend_form->Show();
   }   
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_analysis_pwa::bbtn_selectClick(TObject *Sender)
{
   Tfrm_select *frm_select = new Tfrm_select(this,
                                             lbl_pat->Caption, analysis_qry,
                                             analysis_all_measurements,
                                             analysis_input_measurements,
                                             analysis_selected_measurements,
                                             MEAS_PWA_ID,
                                             ANALYSIS_MAX_PWA_MEASUREMENTS,
                                             &analysis_artery);
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
      ShowCharts(analysis_qry,  analysis_selected_measurements);
   }
   delete frm_select;
   pnl_buttons->SetFocus();   
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_analysis_pwa::bbtn_exportClick(TObject *Sender)
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
                      +analysis_first_export +"_" +analysis_last_export +"_pwa.jpg";
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


