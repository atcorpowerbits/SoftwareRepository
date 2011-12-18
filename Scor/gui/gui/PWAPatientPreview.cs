/* 
     Copyright (C) ATCOR MEDICAL PTY LTD, 2010 
  
     Filename     :     PWAPatientPreview.cs
        
     Author       :     Smarajit Mishra 
  
     Description  :     Creates an intermediate form for printing PWA Patient report. 
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
using AtCor.Scor.CrossCutting;

namespace AtCor.Scor.Gui.Presentation
{
    public partial class PWAPatientPreview : Form
    {
        readonly CrxMessagingManager oMsgMgr = CrxMessagingManager.Instance;
        readonly CrxDBManager oDbMgr = CrxDBManager.Instance; 
        const int spSliderValueStartPoint = 100;
        const int spSliderValueEndPoint = 200;
        const int spSliderPositionStartPoint = 10;
        const int spMultiplicationFactor = 7;
        const int dpMultiplicationFactor = 14;
        const int dpSliderValueStartPoint = 70;
        const int dpSliderValueEndPoint = 120;
        const int dpSliderPositionStartPoint = 10;
        int arraySize = ((BizConstants.MAXIMUM_REFERENCE_RANGE_AGE - BizConstants.MINIMUM_REFERENCE_RANGE_AGE) / 2) + 1;
        BizPWA obj;

        /** This method to Intialize the PWA Patient Preview
        * */
        public PWAPatientPreview()
        {
            InitializeComponent();
        }

        /** This method to load the PWA Patient Preview form
        * */
        private void PWAPatientPreview_Load(object sender, EventArgs e)
        {
            try
            {
                obj = (BizPWA)BizSession.Instance().measurement;
                SetTextForLabels();
                PlotSpSlider();
                PlotDpSlider();
                PlotHrSlider();
                PlotPatientReportChart();

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

        /** This method sets text for labels from resource file
         * */
        private void SetTextForLabels()
        {
            CrxConfigManager crxConfig = CrxConfigManager.Instance;
            string defaultImgPath = ConfigurationManager.AppSettings[GuiConstants.AppConfigParams.AtcorImageIcon.ToString()];
            guiPicBoxReportLogo.Image = string.IsNullOrEmpty(crxConfig.GeneralSettings.ReportLogoPath) ? Image.FromFile(defaultImgPath) : Image.FromFile(crxConfig.GeneralSettings.ReportLogoPath);

            // guiPicBoxHumanLogo.Image = Image.FromFile(".\\\\Human.JPG");
            guiPicBoxHumanLogo.Image = Image.FromFile(ConfigurationManager.AppSettings[GuiConstants.AppConfigParams.HumanImage.ToString()]);
        }

        /** This method to plot the SP Slider
        * */
        private void PlotSpSlider()
        {
            // Validation to show Sp level on the slider or not
            // If SP value is smaller than 110 or greater than 200 then lbl should be hidden
            if (GuiCommon.crxPwaData.SP < spSliderValueStartPoint || GuiCommon.crxPwaData.SP > spSliderValueEndPoint)
            {
                lblSpValue.Hide();
            }
            else
            {
                int diffValue = Convert.ToInt32(GuiCommon.crxPwaData.SP) - spSliderValueStartPoint;
                int sliderPos = spSliderPositionStartPoint + (diffValue * spMultiplicationFactor);
                lblSpValue.Left = sliderPos;
            }

            // "Normal";
            lblSpNormal.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.RptPwaNormalText);

            // "High Normal";
            lblSpHighNormal.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.RptPwaHighNormalText);

            // "Mild Hypertension";
            lblSpMildHypertension.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.RptPwaMildHypertensionText);

            // "Moderate hypertension";
            lblSpModerateHypertension.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.RptPwaModerateHypertensionText);

            // "Severe";
            lblSpSevere.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.RptPwaSevereText);  
        }

        /** This method to plot the DP Slider
       * */
        private void PlotDpSlider()
        {
            // Validation to show Dp level on the slider or not
            // If DP value is smaller than 70 or greater than 120 then lbl should be hidden
            if (GuiCommon.crxPwaData.DP < dpSliderValueStartPoint || GuiCommon.crxPwaData.DP > dpSliderValueEndPoint)
            {
                lblDpValue.Hide();
            }
            else
            {
                int diffValue = Convert.ToInt32(GuiCommon.crxPwaData.DP) - dpSliderValueStartPoint;
                int sliderPos = dpSliderPositionStartPoint + (diffValue * dpMultiplicationFactor);
                lblDpValue.Left = sliderPos;
            }          

            // "Normal";
            lblDpNormal.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.RptPwaNormalText);

            // "High Normal";
            lblDpHighNormal.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.RptPwaHighNormalText);

            // "Mild Hypertension";
            lblDpMildHypertension.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.RptPwaMildHypertensionText);

            // "Moderate hypertension";
            lblDpModerateHypertension.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.RptPwaModerateHypertensionText);

            // "Severe";
            lblDpSevere.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.RptPwaSevereText); 
        }

        /** This method to plot the HR Slider
       * */
        private void PlotHrSlider()
        {
            // "Excellent";
            lblHrExcellent.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.RptPwaExcellentText);

            // "Good";
            lblHrGood.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.RptPwaGoodText);

            // "Above average";
            lblHrAboveAverage.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.RptPwaAboveAverageText);

            // "Average";
            lblHrAverage.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.RptPwaAverageText);

            // "Below average";
            lblHrBelowAverage.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.RptPwaBelowAverageText);

            // "Poor";
            lblHrPoor.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.RptPwaPoorText);
        }

        private void PlotPatientReportChart()
        {
            try
            {
                PlotApReferenceChart();
                PlotSpReferenceChart();
                PlotPpReferenceChart();
                PlotAixReferenceChart();
                PlotPatientSlider();
            }
            catch (Exception ex)
            {
                GUIExceptionHandler.HandleException(ex, this);
            }
        }

        private void PlotPatientSlider()
        {
            try
            {
                short[] spArray = new short[5];
                bool check = obj.GetBrachialSPRange(PWA_MEASURE_TYPE.PWA_BRACHIAL, spArray, 5);
            }
            catch (Exception ex)
            {
                GUIExceptionHandler.HandleException(ex, this);
            }
        }

        private void PlotApReferenceChart()
        {
            float[] lowerReference = new float[arraySize];
            float[] normalReference = new float[arraySize];
            float[] upperReference = new float[arraySize];

            float minYAxis = 0f;
            float maxYAxis = 0f;
            obj.GetAPReferenceChart(lowerReference, normalReference, upperReference, ref minYAxis, ref maxYAxis);

            guichartAp.ChartAreas[0].AxisX.Minimum = BizConstants.MINIMUM_REFERENCE_RANGE_AGE;
            guichartAp.ChartAreas[0].AxisX.Maximum = BizConstants.MAXIMUM_REFERENCE_RANGE_AGE;

            guichartAp.Titles[0].Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.RptPwaApChartText);

            int value = ((int)Math.Round(minYAxis / 10)) * 10;
            guichartAp.ChartAreas[0].AxisY.Minimum = value - 10;
            value = ((int)Math.Round(maxYAxis / 10)) * 10;
            guichartAp.ChartAreas[0].AxisY.Maximum = value + 10;

            guichartAp.ChartAreas[0].AxisY.Interval = 10;
            guichartAp.ChartAreas[0].AxisX.Interval = 10;

            guichartAp.Series[0].Points.Clear();
            guichartAp.Series[1].Points.Clear();
            guichartAp.Series[2].Points.Clear();
            guichartAp.Series[3].Points.Clear();

            int interval = (Convert.ToInt32(BizConstants.MAXIMUM_REFERENCE_RANGE_AGE - BizConstants.MINIMUM_REFERENCE_RANGE_AGE)) / (normalReference.Length - 1);
            {
                for (int i = Convert.ToInt32(BizConstants.MINIMUM_REFERENCE_RANGE_AGE), j = 0; j < normalReference.Length; i = i + interval, j++)
                {
                    guichartAp.Series[0].Points.AddXY(i, Convert.ToDouble(lowerReference[j], CrxCommon.nCI));
                    guichartAp.Series[1].Points.AddXY(i, Convert.ToDouble(normalReference[j], CrxCommon.nCI));
                    guichartAp.Series[2].Points.AddXY(i, Convert.ToDouble(upperReference[j], CrxCommon.nCI));                
                }

                if (!GuiCommon.crxPwaData.C_Ap.Equals(GuiConstants.DefaultValue))
                {
                    guichartAp.Series[3].Points.AddXY(Convert.ToDouble(obj.patientAge), Math.Round(GuiCommon.crxPwaData.C_Ap));
                }

                guichartAp.Invalidate();
            }
        }

        private void PlotSpReferenceChart()
        {
            float[] lowerReference = new float[arraySize];
            float[] normalReference = new float[arraySize];
            float[] upperReference = new float[arraySize];

            float minYAxis = 0f;
            float maxYAxis = 0f;
            obj.GetSPReferenceChart(lowerReference, normalReference, upperReference, ref minYAxis, ref maxYAxis);

            guichartSp.ChartAreas[0].AxisX.Minimum = BizConstants.MINIMUM_REFERENCE_RANGE_AGE;
            guichartSp.ChartAreas[0].AxisX.Maximum = BizConstants.MAXIMUM_REFERENCE_RANGE_AGE;

            guichartSp.Titles[0].Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.RptPwaSpChartText);

            int value = ((int)Math.Round(minYAxis / 10)) * 10;
            guichartSp.ChartAreas[0].AxisY.Minimum = value - 10;
            value = ((int)Math.Round(maxYAxis / 10)) * 10;
            guichartSp.ChartAreas[0].AxisY.Maximum = value + 10;

            guichartSp.ChartAreas[0].AxisY.Interval = 10;
            guichartSp.ChartAreas[0].AxisX.Interval = 10;

            guichartSp.Series[0].Points.Clear();
            guichartSp.Series[1].Points.Clear();
            guichartSp.Series[2].Points.Clear();
            guichartSp.Series[3].Points.Clear();

            int interval = Convert.ToInt32(BizConstants.MAXIMUM_REFERENCE_RANGE_AGE - BizConstants.MINIMUM_REFERENCE_RANGE_AGE) / (normalReference.Length - 1);
            {
                for (int i = Convert.ToInt32(BizConstants.MINIMUM_REFERENCE_RANGE_AGE), j = 0; j < normalReference.Length; i = i + interval, j++)
                {
                    guichartSp.Series[0].Points.AddXY(i, Convert.ToDouble(lowerReference[j], CrxCommon.nCI));
                    guichartSp.Series[1].Points.AddXY(i, Convert.ToDouble(normalReference[j], CrxCommon.nCI));
                    guichartSp.Series[2].Points.AddXY(i, Convert.ToDouble(upperReference[j], CrxCommon.nCI));
                }

                if (!GuiCommon.crxPwaData.C_Sp.Equals(GuiConstants.DefaultValue))
                {
                    guichartSp.Series[3].Points.AddXY(Convert.ToDouble(obj.patientAge), Math.Round(GuiCommon.crxPwaData.C_Sp));
                }

                guichartSp.Invalidate();
            }
        }

        private void PlotPpReferenceChart()
        {
            float[] lowerReference = new float[arraySize];
            float[] normalReference = new float[arraySize];
            float[] upperReference = new float[arraySize];

            float minYAxis = 0f;
            float maxYAxis = 0f;
            obj.GetPPReferenceChart(lowerReference, normalReference, upperReference, ref minYAxis, ref maxYAxis);

            guichartPp.ChartAreas[0].AxisX.Minimum = BizConstants.MINIMUM_REFERENCE_RANGE_AGE;
            guichartPp.ChartAreas[0].AxisX.Maximum = BizConstants.MAXIMUM_REFERENCE_RANGE_AGE;

            guichartPp.Titles[0].Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.RptPwaPpChartText);

            int value = ((int)Math.Round(minYAxis / 10)) * 10;
            guichartPp.ChartAreas[0].AxisY.Minimum = value - 10;
            value = ((int)Math.Round(maxYAxis / 10)) * 10;
            guichartPp.ChartAreas[0].AxisY.Maximum = value + 10;

            guichartPp.ChartAreas[0].AxisY.Interval = 10;
            guichartPp.ChartAreas[0].AxisX.Interval = 10;

            guichartPp.Series[0].Points.Clear();
            guichartPp.Series[1].Points.Clear();
            guichartPp.Series[2].Points.Clear();
            guichartPp.Series[3].Points.Clear();

            int interval = Convert.ToInt32(BizConstants.MAXIMUM_REFERENCE_RANGE_AGE - BizConstants.MINIMUM_REFERENCE_RANGE_AGE) / (normalReference.Length - 1);
            {
                for (int i = Convert.ToInt32(BizConstants.MINIMUM_REFERENCE_RANGE_AGE), j = 0; j < normalReference.Length; i = i + interval, j++)
                {
                    guichartPp.Series[0].Points.AddXY(i, Convert.ToDouble(lowerReference[j], CrxCommon.nCI));
                    guichartPp.Series[1].Points.AddXY(i, Convert.ToDouble(normalReference[j], CrxCommon.nCI));
                    guichartPp.Series[2].Points.AddXY(i, Convert.ToDouble(upperReference[j], CrxCommon.nCI));
                }

                if (!PWAClinicalReportData.RptPPAroticValue.Equals(string.Empty))
                {
                    guichartPp.Series[3].Points.AddXY(Convert.ToDouble(obj.patientAge), Convert.ToInt32(PWAClinicalReportData.RptPPAroticValue));
                }

                guichartPp.Invalidate();
            }
        }

        private void PlotAixReferenceChart()
        {
            float[] lowerReference = new float[arraySize];
            float[] normalReference = new float[arraySize];
            float[] upperReference = new float[arraySize];

            float minYAxis = 0f;
            float maxYAxis = 0f;
            obj.GetAixReferenceChart(lowerReference, normalReference, upperReference, ref minYAxis, ref maxYAxis);

            guichartAix.ChartAreas[0].AxisX.Minimum = BizConstants.MINIMUM_REFERENCE_RANGE_AGE;
            guichartAix.ChartAreas[0].AxisX.Maximum = BizConstants.MAXIMUM_REFERENCE_RANGE_AGE;

            guichartAix.Titles[0].Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.RptPwaAixChartText);

            int value = ((int)Math.Round(minYAxis / 10)) * 10;
            guichartAix.ChartAreas[0].AxisY.Minimum = value - 10;
            value = ((int)Math.Round(maxYAxis / 10)) * 10;
            guichartAix.ChartAreas[0].AxisY.Maximum = value + 10;

            guichartAix.ChartAreas[0].AxisY.Interval = 10;
            guichartAix.ChartAreas[0].AxisX.Interval = 10;

            guichartAix.Series[0].Points.Clear();
            guichartAix.Series[1].Points.Clear();
            guichartAix.Series[2].Points.Clear();
            guichartAix.Series[3].Points.Clear();

            int interval = Convert.ToInt32(BizConstants.MAXIMUM_REFERENCE_RANGE_AGE - BizConstants.MINIMUM_REFERENCE_RANGE_AGE) / (normalReference.Length - 1);
            {
                for (int i = Convert.ToInt32(BizConstants.MINIMUM_REFERENCE_RANGE_AGE), j = 0; j < normalReference.Length; i = i + interval, j++)
                {
                    guichartAix.Series[0].Points.AddXY(i, Convert.ToDouble(lowerReference[j], CrxCommon.nCI));
                    guichartAix.Series[1].Points.AddXY(i, Convert.ToDouble(normalReference[j], CrxCommon.nCI));
                    guichartAix.Series[2].Points.AddXY(i, Convert.ToDouble(upperReference[j], CrxCommon.nCI));
                }

                if (!GuiCommon.crxPwaData.C_Agph.Equals(GuiConstants.DefaultValue))
                {
                    guichartAix.Series[3].Points.AddXY(Convert.ToDouble(obj.patientAge), Math.Round(GuiCommon.crxPwaData.C_Agph));
                }

                guichartAix.Invalidate();
            }
        }
    }
}
