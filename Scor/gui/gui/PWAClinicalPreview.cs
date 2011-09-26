
/* 
     Copyright (C) ATCOR MEDICAL PTY LTD, 2010 
  
     Filename     :     PWAClinicalPreview.cs
        
     Author       :     Smarajit Mishra 
  
     Description  :     Creates an intermediate form for printing PWA clinical report. 
*/

using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using AtCor.Scor.BusinessLogic;
using AtCor.Scor.CrossCutting.Messaging;
using AtCor.Scor.CrossCutting.Configuration;
using System.Configuration;
using System.Windows.Forms.DataVisualization.Charting;
using AtCor.Scor.CrossCutting.DatabaseManager;

namespace AtCor.Scor.Gui.Presentation
{
    public partial class PWAClinicalPreview : Form
    {
        readonly CrxMessagingManager oMsgMgr = CrxMessagingManager.Instance;
        BizPWA obj;
        Series typicalSeries;
        Series actualSeries;

        public PWAClinicalPreview()
        {
            InitializeComponent();
        }

        private void PWAClinicalPreview_Load(object sender, EventArgs e)
        {
            try
            {                
                Hide();
                obj = (BizPWA)BizSession.Instance().measurement;
                SetTextForLabels();
                PopulateCentralClinicalParameters();
                PlotCentralPressueWaveform();
              
                PWAPrintReport objPwaPrintReport = new PWAPrintReport(this);
                objPwaPrintReport.Show();
                objPwaPrintReport.Hide();
                Close();
                Dispose();               
            }
            catch (Exception ex)
            {
                GUIExceptionHandler.HandleException(ex, this);
            }
        }

        private void PopulateCentralClinicalParameters()
        {
            guiradlblSphygmocorReferenceAge.Text = PWACommonReportData.RptReferenceAgeValue;

            ShowSpTracker(130, 90, GuiCommon.crxPwaData.C_Sp, 96, 120);
            float centralPp;
            centralPp = GuiCommon.crxPwaData.C_Sp - GuiCommon.crxPwaData.C_Dp;
            ShowPpTracker(25, 0, centralPp, 5, 20);
            ShowAixTracker(26, -8, GuiCommon.crxPwaData.C_Agph, -2, 20);
            ShowApTracker(12, -6, GuiCommon.crxPwaData.C_Ap, -3, 9);
        }

        private void ShowSpTracker(float spMaxValue, float spMinValue, float spValue, float spGoodRangeMin, float spGoodRangeMax)
        {
            // SP Tracker: Begin
             spMaxValue = 130;
             spMinValue = 90;
             spValue = 105;
             spGoodRangeMin = 96;
             spGoodRangeMax = 120;

             guilblSPValue.Left = guilblSPSlider.Left + ((int)(spValue - spMinValue) * (guilblSPSlider.Width / (int)(spMaxValue - spMinValue)));

             guilblSPGoodMinText.Left = guilblSPGoodMin.Left = guilblSPSlider.Left + ((int)(spGoodRangeMin - spMinValue) * (guilblSPSlider.Width / (int)(spMaxValue - spMinValue)));
             guilblSPGoodMax.Left = guilblSPSlider.Left + ((int)(spGoodRangeMax - spMinValue) * (guilblSPSlider.Width / (int)(spMaxValue - spMinValue)));

            guilblSPValueText.Left = guilblSPValue.Left - (guilblSPValueText.Width / 3) + 2;
            guilblSPGoodMaxText.Left = guilblSPGoodMax.Left - (guilblSPGoodMaxText.Width / 3);
            guilblSPGoodMinText.Left = guilblSPGoodMin.Left - (guilblSPGoodMinText.Width / 3);

            guilblSPValueText.Text = spValue.ToString();
            guilblSPGoodMaxText.Text = spGoodRangeMax.ToString();
            guilblSPGoodMinText.Text = spGoodRangeMin.ToString();

            if ((spValue < spGoodRangeMin) || (spValue > spGoodRangeMax))
            {
                guilblSPValue.BackColor = Color.Red;
            }
            else
            {
                guilblSPValue.BackColor = Color.LimeGreen;
            }

            // SP Tracker: End
        }

        private void ShowPpTracker(float ppMaxValue, float ppMinValue, float ppValue, float ppGoodRangeMin, float ppGoodRangeMax)
        {
            // PP Tracker: Begin
             ppMaxValue = 25;
             ppMinValue = 0;
             ppValue = 23;
             ppGoodRangeMin = 5;
             ppGoodRangeMax = 20;

             guilblPPValue.Left = guilblPPSlider.Left + ((int)(ppValue - ppMinValue) * (guilblPPSlider.Width / (int)(ppMaxValue - ppMinValue)));

             guilblPPGoodMinText.Left = guilblPPGoodMin.Left = guilblPPSlider.Left + ((int)(ppGoodRangeMin - ppMinValue) * (guilblPPSlider.Width / (int)(ppMaxValue - ppMinValue)));
            guilblPPGoodMax.Left = guilblPPSlider.Left + ((int)(ppGoodRangeMax - ppMinValue) * (guilblPPSlider.Width / (int)(ppMaxValue - ppMinValue)));

            guilblPPValueText.Left = guilblPPValue.Left - (guilblPPValueText.Width / 3) + 3;
            guilblPPGoodMaxText.Left = guilblPPGoodMax.Left - (guilblPPGoodMaxText.Width / 3);
            guilblPPGoodMinText.Left = guilblPPGoodMin.Left - (guilblPPGoodMinText.Width / 3);

            guilblPPValueText.Text = ppValue.ToString();
            guilblPPGoodMaxText.Text = ppGoodRangeMax.ToString();
            guilblPPGoodMinText.Text = ppGoodRangeMin.ToString();

            if ((ppValue < ppGoodRangeMin) || (ppValue > ppGoodRangeMax))
            {
                guilblPPValue.BackColor = Color.Red;
            }
            else
            {
                guilblPPValue.BackColor = Color.LimeGreen;
            }

            // PP Tracker: End
        }

        private void ShowAixTracker(float maxValue, float minValue, float value, float goodRangeMin, float goodRangeMax)
        {
            // AIx Tracker: Begin
             maxValue = 26;
             minValue = -8;
             value = 22;
             goodRangeMin = -2;
             goodRangeMax = 20;

            guilblAIxValue.Left = guilblAIxSlider.Left + (int)((value - minValue) * (guilblAIxSlider.Width / (maxValue - minValue)));

            guilblAIxGoodMinText.Left = guilblAIxGoodMin.Left = guilblAIxSlider.Left + (int)((goodRangeMin - minValue) * (guilblAIxSlider.Width / (maxValue - minValue)));
            guilblAIxGoodMax.Left = guilblAIxSlider.Left + (int)((goodRangeMax - minValue) * (guilblAIxSlider.Width / (maxValue - minValue)));

            guilblAIxValueText.Left = guilblAIxValue.Left - (guilblAIxValueText.Width / 3) + 4;
            guilblAIxGoodMaxText.Left = guilblAIxGoodMax.Left - (guilblAIxGoodMaxText.Width / 3);
            guilblAIxGoodMinText.Left = guilblAIxGoodMin.Left - (guilblAIxGoodMinText.Width / 3);

            guilblAIxValueText.Text = value.ToString();
            guilblAIxGoodMaxText.Text = goodRangeMax.ToString();
            guilblAIxGoodMinText.Text = goodRangeMin.ToString();

            if ((value < goodRangeMin) || (value > goodRangeMax))
            {
                guilblAIxValue.BackColor = Color.Red;
            }
            else
            {
                guilblAIxValue.BackColor = Color.LimeGreen;
            }

            // AIx Tracker: End
        }

        private void ShowApTracker(float apMaxValue, float apMinValue, float apValue, float apGoodRangeMin, float apGoodRangeMax)
        {
            // AP Tracker: Begin
             apMaxValue = 12;
             apMinValue = -6;
             apValue = 4;
             apGoodRangeMin = -3;
             apGoodRangeMax = 9;

             guilblAPValue.Left = guilblAPSlider.Left + ((int)(apValue - apMinValue) * (guilblAPSlider.Width / (int)(apMaxValue - apMinValue)));

             guilblAPGoodMinText.Left = guilblAPGoodMin.Left = guilblAPSlider.Left + ((int)(apGoodRangeMin - apMinValue) * (guilblAPSlider.Width / (int)(apMaxValue - apMinValue)));
             guilblAPGoodMax.Left = guilblAPSlider.Left + ((int)(apGoodRangeMax - apMinValue) * (guilblAPSlider.Width / (int)(apMaxValue - apMinValue)));

            guilblAPValueText.Left = guilblAPValue.Left - (guilblAPValueText.Width / 3) + 5;
            guilblAPGoodMaxText.Left = guilblAPGoodMax.Left - (guilblAPGoodMaxText.Width / 3);
            guilblAPGoodMinText.Left = guilblAPGoodMin.Left - (guilblAPGoodMinText.Width / 3);

            guilblAPValueText.Text = apValue.ToString();
            guilblAPGoodMaxText.Text = apGoodRangeMax.ToString();
            guilblAPGoodMinText.Text = apGoodRangeMin.ToString();

            if ((apValue < apGoodRangeMin) || (apValue > apGoodRangeMax))
            {
                guilblAPValue.BackColor = Color.Red;
            }
            else
            {
                guilblAPValue.BackColor = Color.LimeGreen;
            }

            // AP Tracker: End
        }

        /**This method plots  Average Aortic Pulse graph
         * */   
        private void PlotCentralPressueWaveform()
        {
            // set y axis (normal range values from Bizsession object in float)
            float[] avgAorticPulse = GuiCommon.crxPwaData.C_AV_PULSE;
            guichartPWAReport.Series.Clear();

            // initialize series,chartype,add points to series and finally add series to chart.            
            // set display properties for Avg Aortic Pulse graph
            Series avgAorticPulseActualSeries = new Series
            {
                ChartType = SeriesChartType.Spline,
                Color = Color.MediumBlue,
                BorderWidth = 2,
                Name = "Actual",
            };

            // set properties for series 2 for plotting ideal graph
            Series avgAorticPulseIdealSeries = new Series
            {
                ChartType = SeriesChartType.Spline,
                Color = Color.DimGray,
                BorderWidth = 2,
                Name = "Typical",
            };

            avgAorticPulseActualSeries.Points.Clear();
            avgAorticPulseIdealSeries.Points.Clear();

            // Plot actual waveform.
            for (int i = 0; i < avgAorticPulse.Length; i++)
            {
                avgAorticPulseActualSeries.Points.AddXY(i, avgAorticPulse[i]);
            }

            AddDataPointsIdealgraph(avgAorticPulseIdealSeries);
            guichartPWAReport.Series.Add(avgAorticPulseActualSeries);
            guichartPWAReport.Series.Add(avgAorticPulseIdealSeries);    
        }

        /** This method sets text for labels from resource file
         * */
        private void SetTextForLabels()
        {
            CrxConfigManager crxConfig = CrxConfigManager.Instance;
            string defaultImgPath = ConfigurationManager.AppSettings[GuiConstants.AppConfigParams.AtcorImageIcon.ToString()];
            guiPicBoxReportLogo.Image = string.IsNullOrEmpty(crxConfig.GeneralSettings.ReportLogoPath) ? Image.FromFile(defaultImgPath) : Image.FromFile(crxConfig.GeneralSettings.ReportLogoPath);
        }       

        private void AddDataPointsIdealgraph(Series avgAorticPulseSeries2)
        {
            avgAorticPulseSeries2.Points.AddXY(45, 0);
            avgAorticPulseSeries2.Points.AddXY(55, 35);
            avgAorticPulseSeries2.Points.AddXY(65, 75);
            avgAorticPulseSeries2.Points.AddXY(75, 105);
            avgAorticPulseSeries2.Points.AddXY(85, 118);
            avgAorticPulseSeries2.Points.AddXY(91, 121);
            avgAorticPulseSeries2.Points.AddXY(95, 130);
            avgAorticPulseSeries2.Points.AddXY(103, 156);
            avgAorticPulseSeries2.Points.AddXY(106, 158);
            avgAorticPulseSeries2.Points.AddXY(108, 160);
            avgAorticPulseSeries2.Points.AddXY(114, 158);
            avgAorticPulseSeries2.Points.AddXY(116, 156);
            avgAorticPulseSeries2.Points.AddXY(117, 154);
            avgAorticPulseSeries2.Points.AddXY(119, 140);
            avgAorticPulseSeries2.Points.AddXY(125, 131);
            avgAorticPulseSeries2.Points.AddXY(127, 130);
            avgAorticPulseSeries2.Points.AddXY(136, 126);
            avgAorticPulseSeries2.Points.AddXY(140, 120);
            avgAorticPulseSeries2.Points.AddXY(145, 104);
            avgAorticPulseSeries2.Points.AddXY(155, 73);
            avgAorticPulseSeries2.Points.AddXY(165, 50);
            avgAorticPulseSeries2.Points.AddXY(171, 40);
            avgAorticPulseSeries2.Points.AddXY(176, 32);
            avgAorticPulseSeries2.Points.AddXY(187, 21);
            avgAorticPulseSeries2.Points.AddXY(195, 10);
        }     
    }
}
