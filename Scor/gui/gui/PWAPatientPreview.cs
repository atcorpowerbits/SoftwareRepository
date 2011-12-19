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
        readonly CrxSytemParameters oCrxSysParam = CrxSytemParameters.Instance;
        const int spSliderValueStartPoint = 100;
        const int spSliderValueEndPoint = 200;
        const int spSliderPositionStartPoint = 10;
        const int spMultiplicationFactor = 7;
        const int dpMultiplicationFactor = 14;
        const int dpSliderValueStartPoint = 70;
        const int dpSliderValueEndPoint = 120;
        const int dpSliderPositionStartPoint = 10;
        int arraySize = ((BizConstants.MAXIMUM_REFERENCE_RANGE_AGE - BizConstants.MINIMUM_REFERENCE_RANGE_AGE) / Convert.ToInt32(GuiCommon.NumericValue.Two)) + Convert.ToInt32(GuiCommon.NumericValue.One);
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
            try
            {
                CrxConfigManager crxConfig = CrxConfigManager.Instance;
                string defaultImgPath = ConfigurationManager.AppSettings[GuiConstants.AppConfigParams.AtcorImageIcon.ToString()];
                guiPicBoxReportLogo.Image = string.IsNullOrEmpty(crxConfig.GeneralSettings.ReportLogoPath) ? Image.FromFile(defaultImgPath) : Image.FromFile(crxConfig.GeneralSettings.ReportLogoPath);
                guiPicBoxHumanLogo.Image = Image.FromFile(ConfigurationManager.AppSettings[GuiConstants.AppConfigParams.HumanImage.ToString()]);
            }
            catch (Exception ex)
            {
                GUIExceptionHandler.HandleException(ex, this);
            }
        }

        /** This method to plot the SP Slider
        * */
        // Any exception will be handled by PWAPatientPreview_Load Event
        private void PlotSpSlider()
        {
            bool chkDefaultSlider = true;
            try
            {
                string tempArrSize = string.Empty;
                tempArrSize = oCrxSysParam.GetStringTagValue("PWA.Cuff.PatientReport.RangeArraySize.SP");
                
                if(!string.IsNullOrEmpty(tempArrSize))
                {
                    short arrSize = Convert.ToInt16(tempArrSize);

                    if (arrSize >= (short)Number.Two && arrSize <= (short)Number.Seven)
                    {
                        SetSpSliderPosition(arrSize);
                        chkDefaultSlider = false;
                    }                   
                }

                if (chkDefaultSlider == true)
                {
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
                    lblSpNormal.TextAlign = ContentAlignment.MiddleCenter;

                    // "High Normal";
                    lblSpHighNormal.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.RptPwaHighNormalText);
                    lblSpHighNormal.TextAlign = ContentAlignment.MiddleCenter;

                    // "Mild Hypertension";
                    lblSpMildHypertension.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.RptPwaMildHypertensionText);
                    lblSpMildHypertension.TextAlign = ContentAlignment.MiddleCenter;

                    // "Moderate hypertension";
                    lblSpModerateHypertension.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.RptPwaModerateHypertensionText);
                    lblSpModerateHypertension.TextAlign = ContentAlignment.MiddleCenter;

                    // "Severe";
                    lblSpSevere.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.RptPwaSevereText);
                    lblSpSevere.TextAlign = ContentAlignment.MiddleCenter;

                }
            }             
            catch (Exception ex)
            {
                throw (ex);
            }
        }

        /** This method to plot the DP Slider
        * */
        // Any exception will be handled by PWAPatientPreview_Load Event
        private void PlotDpSlider()
        {
            bool chkDefaultSlider = true;
            try
            {                
                string tempArrSize = string.Empty;
                tempArrSize = oCrxSysParam.GetStringTagValue("PWA.Cuff.PatientReport.RangeArraySize.DP");

                if (!string.IsNullOrEmpty(tempArrSize))
                {
                    short arrSize = Convert.ToInt16(tempArrSize);

                    if (arrSize >= (short)Number.Two && arrSize <= (short)Number.Seven)
                    {
                        SetDpSliderPosition(arrSize);
                        chkDefaultSlider = false;
                    }
                }

                if (chkDefaultSlider == true)
                {
                    // Validation to show Dp level on the slider or not
                    // If DP value is smaller than smallet array value or greater than highest array value then lbl should be hidden
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
            }
            catch (Exception ex)
            {
                throw (ex);
            }
        }

        /** This method to plot the HR Slider
       * */
        // Any exception will be handled by PWAPatientPreview_Load Event
        private void PlotHrSlider()
        {
            bool chkDefaultSlider = true;

            try
            {
                string tempArrSize = string.Empty;
                tempArrSize = oCrxSysParam.GetStringTagValue("PWA.Cuff.PatientReport.RangeArraySize.HR");

                if (!string.IsNullOrEmpty(tempArrSize))
                {
                    short arrSize = Convert.ToInt16(tempArrSize);

                    if (arrSize >= (short)Number.Two && arrSize <= (short)Number.Seven)
                    {
                        SetHrSliderPosition(arrSize);
                        chkDefaultSlider = false;
                    }
                }

                if (chkDefaultSlider == true)
                {
                    // Validation to show Dp level on the slider or not
                    // If DP value is smaller than smallet array value or greater than highest array value then lbl should be hidden
                    if (GuiCommon.crxPwaData.HR < dpSliderValueStartPoint || GuiCommon.crxPwaData.HR > dpSliderValueEndPoint)
                    {
                        lblDpValue.Hide();
                    }
                    else
                    {
                        int diffValue = Convert.ToInt32(GuiCommon.crxPwaData.DP) - dpSliderValueStartPoint;
                        int sliderPos = dpSliderPositionStartPoint + (diffValue * dpMultiplicationFactor);
                        lblDpValue.Left = sliderPos;
                    }
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
            }
            catch (Exception ex)
            {
                throw (ex);
            }
        }

        private void PlotPatientReportChart()
        {
            try
            {
                PlotApReferenceChart();
                PlotSpReferenceChart();
                PlotPpReferenceChart();
                PlotAixReferenceChart();
            }
            catch (Exception ex)
            {
                GUIExceptionHandler.HandleException(ex, this);
            }
        }

        // Any exception will be handled by PlotPatientReportChart function
        private void PlotApReferenceChart()
        {
            try
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

                int value = ((int)Math.Round(minYAxis / Convert.ToInt32(GuiCommon.NumericValue.Ten))) * Convert.ToInt32(GuiCommon.NumericValue.Ten);
                guichartAp.ChartAreas[0].AxisY.Minimum = value - Convert.ToInt32(GuiCommon.NumericValue.Ten);
                value = ((int)Math.Round(maxYAxis / Convert.ToInt32(GuiCommon.NumericValue.Ten))) * Convert.ToInt32(GuiCommon.NumericValue.Ten);
                guichartAp.ChartAreas[0].AxisY.Maximum = value + Convert.ToInt32(GuiCommon.NumericValue.Ten);

                guichartAp.ChartAreas[0].AxisY.Interval = Convert.ToInt32(GuiCommon.NumericValue.Ten);
                guichartAp.ChartAreas[0].AxisX.Interval = Convert.ToInt32(GuiCommon.NumericValue.Ten);

                guichartAp.Series[0].Points.Clear();
                guichartAp.Series[1].Points.Clear();
                guichartAp.Series[2].Points.Clear();
                guichartAp.Series[3].Points.Clear();

                int interval = (Convert.ToInt32(BizConstants.MAXIMUM_REFERENCE_RANGE_AGE - BizConstants.MINIMUM_REFERENCE_RANGE_AGE)) / (normalReference.Length - Convert.ToInt32(GuiCommon.NumericValue.One));
                {
                    for (int i = Convert.ToInt32(BizConstants.MINIMUM_REFERENCE_RANGE_AGE), j = Convert.ToInt32(GuiCommon.NumericValue.Zero); j < normalReference.Length; i = i + interval, j++)
                    {
                        guichartAp.Series[0].Points.AddXY(i, Convert.ToDouble(lowerReference[j], CrxCommon.nCI));
                        guichartAp.Series[1].Points.AddXY(i, Convert.ToDouble(normalReference[j], CrxCommon.nCI));
                        guichartAp.Series[2].Points.AddXY(i, Convert.ToDouble(upperReference[j], CrxCommon.nCI));
                    }

                    if (!GuiCommon.crxPwaData.C_Ap.Equals(GuiConstants.DefaultValue) && (obj.patientAge >= BizConstants.MINIMUM_REFERENCE_RANGE_AGE && obj.patientAge <= BizConstants.MAXIMUM_REFERENCE_RANGE_AGE))
                    {
                        guichartAp.Series[3].Points.AddXY(Convert.ToDouble(obj.patientAge), Math.Round(GuiCommon.crxPwaData.C_Ap));
                    }

                    guichartAp.Invalidate();
                }
            }
            catch (Exception ex)
            {
                throw (ex);
            }
        }

        // Any exception will be handled by PlotPatientReportChart function
        private void PlotSpReferenceChart()
        {
            try
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

                int value = ((int)Math.Round(minYAxis / Convert.ToInt32(GuiCommon.NumericValue.Ten))) * Convert.ToInt32(GuiCommon.NumericValue.Ten);
                guichartSp.ChartAreas[0].AxisY.Minimum = value - Convert.ToInt32(GuiCommon.NumericValue.Ten);
                value = ((int)Math.Round(maxYAxis / Convert.ToInt32(GuiCommon.NumericValue.Ten))) * Convert.ToInt32(GuiCommon.NumericValue.Ten);
                guichartSp.ChartAreas[0].AxisY.Maximum = value + Convert.ToInt32(GuiCommon.NumericValue.Ten);

                guichartSp.ChartAreas[0].AxisY.Interval = Convert.ToInt32(GuiCommon.NumericValue.Ten);
                guichartSp.ChartAreas[0].AxisX.Interval = Convert.ToInt32(GuiCommon.NumericValue.Ten);

                guichartSp.Series[0].Points.Clear();
                guichartSp.Series[1].Points.Clear();
                guichartSp.Series[2].Points.Clear();
                guichartSp.Series[3].Points.Clear();

                int interval = Convert.ToInt32(BizConstants.MAXIMUM_REFERENCE_RANGE_AGE - BizConstants.MINIMUM_REFERENCE_RANGE_AGE) / (normalReference.Length - Convert.ToInt32(GuiCommon.NumericValue.One));
                {
                    for (int i = Convert.ToInt32(BizConstants.MINIMUM_REFERENCE_RANGE_AGE), j = Convert.ToInt32(GuiCommon.NumericValue.Zero); j < normalReference.Length; i = i + interval, j++)
                    {
                        guichartSp.Series[0].Points.AddXY(i, Convert.ToDouble(lowerReference[j], CrxCommon.nCI));
                        guichartSp.Series[1].Points.AddXY(i, Convert.ToDouble(normalReference[j], CrxCommon.nCI));
                        guichartSp.Series[2].Points.AddXY(i, Convert.ToDouble(upperReference[j], CrxCommon.nCI));
                    }

                    if (!GuiCommon.crxPwaData.C_Sp.Equals(GuiConstants.DefaultValue)  && (obj.patientAge >= BizConstants.MINIMUM_REFERENCE_RANGE_AGE && obj.patientAge <= BizConstants.MAXIMUM_REFERENCE_RANGE_AGE))
                    {
                        guichartSp.Series[3].Points.AddXY(Convert.ToDouble(obj.patientAge), Math.Round(GuiCommon.crxPwaData.C_Sp));
                    }

                    guichartSp.Invalidate();
                }
            }
            catch (Exception ex)
            {
                throw (ex);
            }
        }

        // Any exception will be handled by PlotPatientReportChart function
        private void PlotPpReferenceChart()
        {
            try
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

                int value = ((int)Math.Round(minYAxis / Convert.ToInt32(GuiCommon.NumericValue.Ten))) * Convert.ToInt32(GuiCommon.NumericValue.Ten);
                guichartPp.ChartAreas[0].AxisY.Minimum = value - Convert.ToInt32(GuiCommon.NumericValue.Ten);
                value = ((int)Math.Round(maxYAxis / Convert.ToInt32(GuiCommon.NumericValue.Ten))) * Convert.ToInt32(GuiCommon.NumericValue.Ten);
                guichartPp.ChartAreas[0].AxisY.Maximum = value + Convert.ToInt32(GuiCommon.NumericValue.Ten);

                guichartPp.ChartAreas[0].AxisY.Interval = Convert.ToInt32(GuiCommon.NumericValue.Ten);
                guichartPp.ChartAreas[0].AxisX.Interval = Convert.ToInt32(GuiCommon.NumericValue.Ten);

                guichartPp.Series[0].Points.Clear();
                guichartPp.Series[1].Points.Clear();
                guichartPp.Series[2].Points.Clear();
                guichartPp.Series[3].Points.Clear();

                int interval = Convert.ToInt32(BizConstants.MAXIMUM_REFERENCE_RANGE_AGE - BizConstants.MINIMUM_REFERENCE_RANGE_AGE) / (normalReference.Length - Convert.ToInt32(GuiCommon.NumericValue.One));
                {
                    for (int i = Convert.ToInt32(BizConstants.MINIMUM_REFERENCE_RANGE_AGE), j = Convert.ToInt32(GuiCommon.NumericValue.Zero); j < normalReference.Length; i = i + interval, j++)
                    {
                        guichartPp.Series[0].Points.AddXY(i, Convert.ToDouble(lowerReference[j], CrxCommon.nCI));
                        guichartPp.Series[1].Points.AddXY(i, Convert.ToDouble(normalReference[j], CrxCommon.nCI));
                        guichartPp.Series[2].Points.AddXY(i, Convert.ToDouble(upperReference[j], CrxCommon.nCI));
                    }

                    if (!PWAClinicalReportData.RptPPAroticValue.Equals(string.Empty) && (obj.patientAge >= BizConstants.MINIMUM_REFERENCE_RANGE_AGE && obj.patientAge <= BizConstants.MAXIMUM_REFERENCE_RANGE_AGE))
                    {
                        guichartPp.Series[3].Points.AddXY(Convert.ToDouble(obj.patientAge), Convert.ToInt32(PWAClinicalReportData.RptPPAroticValue));
                    }

                    guichartPp.Invalidate();
                }
            }
            catch (Exception ex)
            {
                throw (ex);
            }
        }

        // Any exception will be handled by PlotPatientReportChart function
        private void PlotAixReferenceChart()
        {
            try
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

                int value = ((int)Math.Round(minYAxis / Convert.ToInt32(GuiCommon.NumericValue.Ten))) * Convert.ToInt32(GuiCommon.NumericValue.Ten);
                guichartAix.ChartAreas[0].AxisY.Minimum = value - Convert.ToInt32(GuiCommon.NumericValue.Ten);
                value = ((int)Math.Round(maxYAxis / Convert.ToInt32(GuiCommon.NumericValue.Ten))) * Convert.ToInt32(GuiCommon.NumericValue.Ten);
                guichartAix.ChartAreas[0].AxisY.Maximum = value + Convert.ToInt32(GuiCommon.NumericValue.Ten);

                guichartAix.ChartAreas[0].AxisY.Interval = Convert.ToInt32(GuiCommon.NumericValue.Ten);
                guichartAix.ChartAreas[0].AxisX.Interval = Convert.ToInt32(GuiCommon.NumericValue.Ten);

                guichartAix.Series[0].Points.Clear();
                guichartAix.Series[1].Points.Clear();
                guichartAix.Series[2].Points.Clear();
                guichartAix.Series[3].Points.Clear();

                int interval = Convert.ToInt32(BizConstants.MAXIMUM_REFERENCE_RANGE_AGE - BizConstants.MINIMUM_REFERENCE_RANGE_AGE) / (normalReference.Length - Convert.ToInt32(GuiCommon.NumericValue.One));
                {
                    for (int i = Convert.ToInt32(BizConstants.MINIMUM_REFERENCE_RANGE_AGE), j = Convert.ToInt32(GuiCommon.NumericValue.Zero); j < normalReference.Length; i = i + interval, j++)
                    {
                        guichartAix.Series[0].Points.AddXY(i, Convert.ToDouble(lowerReference[j], CrxCommon.nCI));
                        guichartAix.Series[1].Points.AddXY(i, Convert.ToDouble(normalReference[j], CrxCommon.nCI));
                        guichartAix.Series[2].Points.AddXY(i, Convert.ToDouble(upperReference[j], CrxCommon.nCI));
                    }

                    if (!GuiCommon.crxPwaData.C_Agph.Equals(GuiConstants.DefaultValue) && (obj.patientAge >= BizConstants.MINIMUM_REFERENCE_RANGE_AGE && obj.patientAge <= BizConstants.MAXIMUM_REFERENCE_RANGE_AGE))
                    {
                        guichartAix.Series[3].Points.AddXY(Convert.ToDouble(obj.patientAge), Math.Round(GuiCommon.crxPwaData.C_Agph));
                    }

                    guichartAix.Invalidate();
                }
            }
            catch (Exception ex)
            {
                throw (ex);
            }
        }

        private void SetSpSliderPosition(short arrSize)
        {
            try
            {
                short[] spArray = new short[arrSize];
                bool check = obj.GetBrachialSPRange(GuiCommon.bizPwaobject.MeasureType, spArray, arrSize);

                if (!check)
                {
                    arrSize = (short)Number.One;
                }

                //string[] textSpArray = new string[arrSize - Convert.ToInt32(GuiCommon.NumericValue.One)];
                string[] textSpArray = new string[6];

                // "Normal";
                //lblSpNormal.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.RptPwaNormalText);
                textSpArray[0] = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.RptPwaNormalText);

                // "High Normal";
                //lblSpHighNormal.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.RptPwaHighNormalText);
                textSpArray[1] = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.RptPwaHighNormalText);

                // "Mild Hypertension";
                //lblSpMildHypertension.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.RptPwaMildHypertensionText);
                textSpArray[2] = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.RptPwaMildHypertensionText);

                // "Moderate hypertension";
                //lblSpModerateHypertension.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.RptPwaModerateHypertensionText);
                textSpArray[3] = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.RptPwaModerateHypertensionText);

                // "Low hypertension" 
                textSpArray[4] = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.RptPwaLowHypertensionText);

                // "Severe";
                //lblSpSevere.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.RptPwaSevereText);
                textSpArray[5] = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.RptPwaSevereText);

                    switch (arrSize)
                    {
                        case (short)Number.Two:
                            guilblSPNormal.Hide();
                            guilblSPNormalValue.Hide();
                            guilblSPMildHypertension.Hide();
                            guilblSPMildHypertensionValue.Hide();
                            guilblSPModeratehypertension.Hide();
                            guilblSPModeratehypertensionValue.Hide();
                            guilblSPlowhypertension.Hide();
                            guilblSPLowValue.Hide();
                            guilblSPSevere.Hide();
                            guilblSPSevereValue.Hide();
                            guilblSpStartPoint.Hide();
                            guilblSpEndPoint.Hide();

                            lblSpHighNormal.Hide();
                            lblSpMildHypertension.Hide();
                            lblSpModerateHypertension.Hide();
                            lblSpLowHypertension.Hide();
                            lblSpSevere.Hide();

                            lblSpNormal.Left = ((guilblSPSlider.Left + ((guilblSPSlider.Right - guilblSPSlider.Left) / Convert.ToInt32(GuiCommon.NumericValue.Two))) - (lblSpNormal.Width / Convert.ToInt32(GuiCommon.NumericValue.Two)));
                            lblSpNormal.Text = textSpArray[0];

                            break;
                        case (short)Number.Three:
                            guilblSPNormal.Left = guilblSPSlider.Left + ((spArray[1] - spArray[0]) * guilblSPSlider.Width / (int)(spArray[spArray.Length - Convert.ToInt32(GuiCommon.NumericValue.One)] - spArray[0])) - (guilblSPNormal.Width / Convert.ToInt32(GuiCommon.NumericValue.Two));
                            guilblSPNormalValue.Left = guilblSPNormal.Left - (guilblSPNormalValue.Width / Convert.ToInt32(GuiCommon.NumericValue.Three)) + Convert.ToInt32(GuiCommon.NumericValue.Four);
                            guilblSPNormalValue.Text = spArray[1].ToString();

                            lblSpNormal.Left = ((guilblSPSlider.Left + ((guilblSPNormal.Left - guilblSPSlider.Left) / Convert.ToInt32(GuiCommon.NumericValue.Two))) - (lblSpNormal.Width / Convert.ToInt32(GuiCommon.NumericValue.Two)));
                            lblSpHighNormal.Left = ((guilblSPNormal.Left + ((guilblSPSlider.Right - guilblSPNormal.Left) / Convert.ToInt32(GuiCommon.NumericValue.Two))) - (lblSpHighNormal.Width / Convert.ToInt32(GuiCommon.NumericValue.Two)));

                            lblSpNormal.Text = textSpArray[0];
                            lblSpHighNormal.Text = textSpArray[1];

                            guilblSPMildHypertension.Hide();
                            guilblSPMildHypertensionValue.Hide();
                            guilblSPModeratehypertension.Hide();
                            guilblSPModeratehypertensionValue.Hide();
                            guilblSPlowhypertension.Hide();
                            guilblSPLowValue.Hide();
                            guilblSPSevere.Hide();
                            guilblSPSevereValue.Hide();
                            guilblSpStartPoint.Hide();
                            guilblSpEndPoint.Hide();

                            lblSpMildHypertension.Hide();
                            lblSpModerateHypertension.Hide();
                            lblSpLowHypertension.Hide();
                            lblSpSevere.Hide();

                            break;

                        case (short)Number.Four:

                            guilblSPNormal.Left = guilblSPSlider.Left + ((spArray[1] - spArray[0]) * guilblSPSlider.Width / (int)(spArray[spArray.Length - Convert.ToInt32(GuiCommon.NumericValue.One)] - spArray[0])) - (guilblSPNormal.Width / Convert.ToInt32(GuiCommon.NumericValue.Two));
                            guilblSPNormalValue.Left = guilblSPNormal.Left - (guilblSPNormalValue.Width / Convert.ToInt32(GuiCommon.NumericValue.Three)) + Convert.ToInt32(GuiCommon.NumericValue.Four);
                            guilblSPNormalValue.Text = spArray[1].ToString();

                            guilblSPMildHypertension.Left = guilblSPSlider.Left + ((spArray[2] - spArray[0]) * guilblSPSlider.Width / (int)(spArray[spArray.Length - Convert.ToInt32(GuiCommon.NumericValue.One)] - spArray[0])) - (guilblSPMildHypertension.Width / Convert.ToInt32(GuiCommon.NumericValue.Two));
                            guilblSPMildHypertensionValue.Left = guilblSPMildHypertension.Left - (guilblSPMildHypertensionValue.Width / Convert.ToInt32(GuiCommon.NumericValue.Three));
                            guilblSPMildHypertensionValue.Text = spArray[2].ToString();

                            lblSpNormal.Left = ((guilblSPSlider.Left + ((guilblSPNormal.Left - guilblSPSlider.Left) / Convert.ToInt32(GuiCommon.NumericValue.Two))) - (lblSpNormal.Width / Convert.ToInt32(GuiCommon.NumericValue.Two)));
                            lblSpHighNormal.Left = ((guilblSPNormal.Left + ((guilblSPMildHypertension.Left - guilblSPNormal.Left) / Convert.ToInt32(GuiCommon.NumericValue.Two))) - (lblSpHighNormal.Width / Convert.ToInt32(GuiCommon.NumericValue.Two)));
                            lblSpMildHypertension.Left = ((guilblSPMildHypertension.Left + ((guilblSPSlider.Right - guilblSPMildHypertension.Left) / Convert.ToInt32(GuiCommon.NumericValue.Two))) - (lblSpMildHypertension.Width / Convert.ToInt32(GuiCommon.NumericValue.Two)));

                            lblSpNormal.Text = textSpArray[0];
                            lblSpHighNormal.Text = textSpArray[1];
                            lblSpMildHypertension.Text = textSpArray[2];

                            guilblSPModeratehypertension.Hide();
                            guilblSPModeratehypertensionValue.Hide();
                            guilblSPlowhypertension.Hide();
                            guilblSPLowValue.Hide();
                            guilblSPSevere.Hide();
                            guilblSPSevereValue.Hide();
                            guilblSpStartPoint.Hide();
                            guilblSpEndPoint.Hide();

                            lblSpModerateHypertension.Hide();
                            lblSpLowHypertension.Hide();
                            lblSpSevere.Hide();

                            break;

                        case (short)Number.Five:
                            guilblSPNormal.Left = guilblSPSlider.Left + ((spArray[1] - spArray[0]) * guilblSPSlider.Width / (int)(spArray[spArray.Length - Convert.ToInt32(GuiCommon.NumericValue.One)] - spArray[0])) - (guilblSPNormal.Width / Convert.ToInt32(GuiCommon.NumericValue.Two));
                            guilblSPNormalValue.Left = guilblSPNormal.Left - (guilblSPNormalValue.Width / Convert.ToInt32(GuiCommon.NumericValue.Three)) + Convert.ToInt32(GuiCommon.NumericValue.Four);
                            guilblSPNormalValue.Text = spArray[1].ToString();

                            guilblSPMildHypertension.Left = guilblSPSlider.Left + ((spArray[2] - spArray[0]) * guilblSPSlider.Width / (int)(spArray[spArray.Length - Convert.ToInt32(GuiCommon.NumericValue.One)] - spArray[0])) - (guilblSPMildHypertension.Width / Convert.ToInt32(GuiCommon.NumericValue.Two));
                            guilblSPMildHypertensionValue.Left = guilblSPMildHypertension.Left - (guilblSPMildHypertensionValue.Width / Convert.ToInt32(GuiCommon.NumericValue.Three));
                            guilblSPMildHypertensionValue.Text = spArray[2].ToString();

                            guilblSPModeratehypertension.Left = guilblSPSlider.Left + ((spArray[3] - spArray[0]) * guilblSPSlider.Width / (int)(spArray[spArray.Length - Convert.ToInt32(GuiCommon.NumericValue.One)] - spArray[0])) - (guilblSPModeratehypertension.Width / Convert.ToInt32(GuiCommon.NumericValue.Two));
                            guilblSPModeratehypertensionValue.Left = guilblSPModeratehypertension.Left - (guilblSPModeratehypertensionValue.Width / Convert.ToInt32(GuiCommon.NumericValue.Three));
                            guilblSPModeratehypertensionValue.Text = spArray[3].ToString();

                            lblSpNormal.Left = ((guilblSPSlider.Left + ((guilblSPNormal.Left - guilblSPSlider.Left) / Convert.ToInt32(GuiCommon.NumericValue.Two))) - (lblSpNormal.Width / Convert.ToInt32(GuiCommon.NumericValue.Two)));
                            lblSpHighNormal.Left = ((guilblSPNormal.Left + ((guilblSPMildHypertension.Left - guilblSPNormal.Left) / Convert.ToInt32(GuiCommon.NumericValue.Two))) - (lblSpHighNormal.Width / Convert.ToInt32(GuiCommon.NumericValue.Two)));
                            lblSpMildHypertension.Left = ((guilblSPMildHypertension.Left + ((guilblSPModeratehypertension.Left - guilblSPMildHypertension.Left) / Convert.ToInt32(GuiCommon.NumericValue.Two))) - (lblSpMildHypertension.Width / Convert.ToInt32(GuiCommon.NumericValue.Two)));
                            lblSpModerateHypertension.Left = ((guilblSPModeratehypertension.Left + ((guilblSPSlider.Right - guilblSPModeratehypertension.Left) / Convert.ToInt32(GuiCommon.NumericValue.Two))) - (lblSpModerateHypertension.Width / Convert.ToInt32(GuiCommon.NumericValue.Two)));

                            lblSpNormal.Text = textSpArray[0];
                            lblSpHighNormal.Text = textSpArray[1];
                            lblSpMildHypertension.Text = textSpArray[2];
                            lblSpModerateHypertension.Text = textSpArray[3];

                            guilblSPlowhypertension.Hide();
                            guilblSPLowValue.Hide();
                            guilblSPSevere.Hide();
                            guilblSPSevereValue.Hide();
                            guilblSpStartPoint.Hide();
                            guilblSpEndPoint.Hide();

                            lblSpLowHypertension.Hide();
                            lblSpSevere.Hide();

                            break;

                        case (short)Number.Six:
                            guilblSPNormal.Left = guilblSPSlider.Left + ((spArray[1] - spArray[0]) * guilblSPSlider.Width / (int)(spArray[spArray.Length - Convert.ToInt32(GuiCommon.NumericValue.One)] - spArray[0])) - (guilblSPNormal.Width / Convert.ToInt32(GuiCommon.NumericValue.Two));
                            guilblSPNormalValue.Left = guilblSPNormal.Left - (guilblSPNormalValue.Width / Convert.ToInt32(GuiCommon.NumericValue.Three)) + Convert.ToInt32(GuiCommon.NumericValue.Four);
                            guilblSPNormalValue.Text = spArray[1].ToString();

                            guilblSPMildHypertension.Left = guilblSPSlider.Left + ((spArray[2] - spArray[0]) * guilblSPSlider.Width / (int)(spArray[spArray.Length - Convert.ToInt32(GuiCommon.NumericValue.One)] - spArray[0])) - (guilblSPMildHypertension.Width / Convert.ToInt32(GuiCommon.NumericValue.Two));
                            guilblSPMildHypertensionValue.Left = guilblSPMildHypertension.Left - (guilblSPMildHypertensionValue.Width / Convert.ToInt32(GuiCommon.NumericValue.Three));
                            guilblSPMildHypertensionValue.Text = spArray[2].ToString();

                            guilblSPModeratehypertension.Left = guilblSPSlider.Left + ((spArray[3] - spArray[0]) * guilblSPSlider.Width / (int)(spArray[spArray.Length - Convert.ToInt32(GuiCommon.NumericValue.One)] - spArray[0])) - (guilblSPModeratehypertension.Width / Convert.ToInt32(GuiCommon.NumericValue.Two));
                            guilblSPModeratehypertensionValue.Left = guilblSPModeratehypertension.Left - (guilblSPModeratehypertensionValue.Width / Convert.ToInt32(GuiCommon.NumericValue.Three));
                            guilblSPModeratehypertensionValue.Text = spArray[3].ToString();

                            guilblSPlowhypertension.Left = guilblSPSlider.Left + ((spArray[4] - spArray[0]) * guilblSPSlider.Width / (int)(spArray[spArray.Length - Convert.ToInt32(GuiCommon.NumericValue.One)] - spArray[0])) - (guilblSPlowhypertension.Width / Convert.ToInt32(GuiCommon.NumericValue.Two));
                            guilblSPLowValue.Left = guilblSPlowhypertension.Left - (guilblSPLowValue.Width / Convert.ToInt32(GuiCommon.NumericValue.Three));
                            guilblSPLowValue.Text = spArray[4].ToString();

                            lblSpNormal.Left = ((guilblSPSlider.Left + ((guilblSPNormal.Left - guilblSPSlider.Left) / Convert.ToInt32(GuiCommon.NumericValue.Two))) - (lblSpNormal.Width / Convert.ToInt32(GuiCommon.NumericValue.Two)));
                            lblSpHighNormal.Left = ((guilblSPNormal.Left + ((guilblSPMildHypertension.Left - guilblSPNormal.Left) / Convert.ToInt32(GuiCommon.NumericValue.Two))) - (lblSpHighNormal.Width / Convert.ToInt32(GuiCommon.NumericValue.Two)));
                            lblSpMildHypertension.Left = ((guilblSPMildHypertension.Left + ((guilblSPModeratehypertension.Left - guilblSPMildHypertension.Left) / Convert.ToInt32(GuiCommon.NumericValue.Two))) - (lblSpMildHypertension.Width / Convert.ToInt32(GuiCommon.NumericValue.Two)));
                            lblSpModerateHypertension.Left = ((guilblSPModeratehypertension.Left + ((guilblSPLowValue.Left - guilblSPModeratehypertension.Left) / Convert.ToInt32(GuiCommon.NumericValue.Two))) - (lblSpModerateHypertension.Width / Convert.ToInt32(GuiCommon.NumericValue.Two)));
                            lblSpLowHypertension.Left = ((guilblSPLowValue.Left + ((guilblSPSlider.Right - guilblSPLowValue.Left) / Convert.ToInt32(GuiCommon.NumericValue.Two))) - (lblSpLowHypertension.Width / Convert.ToInt32(GuiCommon.NumericValue.Two)));

                            lblSpNormal.Text = textSpArray[0];
                            lblSpHighNormal.Text = textSpArray[1];
                            lblSpMildHypertension.Text = textSpArray[2];
                            lblSpModerateHypertension.Text = textSpArray[3];
                            lblSpLowHypertension.Text = textSpArray[4];

                            guilblSPSevere.Hide();
                            guilblSPSevereValue.Hide();
                            guilblSpStartPoint.Hide();
                            guilblSpEndPoint.Hide();
                            lblSpSevere.Hide();

                            break;
                        case (short)Number.Seven:
                            guilblSPNormal.Left = guilblSPSlider.Left + ((spArray[1] - spArray[0]) * guilblSPSlider.Width / (int)(spArray[spArray.Length - Convert.ToInt32(GuiCommon.NumericValue.One)] - spArray[0])) - (guilblSPNormal.Width / Convert.ToInt32(GuiCommon.NumericValue.Two));
                            guilblSPNormalValue.Left = guilblSPNormal.Left - (guilblSPNormalValue.Width / Convert.ToInt32(GuiCommon.NumericValue.Three)) + Convert.ToInt32(GuiCommon.NumericValue.Four);
                            guilblSPNormalValue.Text = spArray[1].ToString();

                            guilblSPMildHypertension.Left = guilblSPSlider.Left + ((spArray[2] - spArray[0]) * guilblSPSlider.Width / (int)(spArray[spArray.Length - Convert.ToInt32(GuiCommon.NumericValue.One)] - spArray[0])) - (guilblSPMildHypertension.Width / Convert.ToInt32(GuiCommon.NumericValue.Two));
                            guilblSPMildHypertensionValue.Left = guilblSPMildHypertension.Left - (guilblSPMildHypertensionValue.Width / Convert.ToInt32(GuiCommon.NumericValue.Three));
                            guilblSPMildHypertensionValue.Text = spArray[2].ToString();

                            guilblSPModeratehypertension.Left = guilblSPSlider.Left + ((spArray[3] - spArray[0]) * guilblSPSlider.Width / (int)(spArray[spArray.Length - Convert.ToInt32(GuiCommon.NumericValue.One)] - spArray[0])) - (guilblSPModeratehypertension.Width / Convert.ToInt32(GuiCommon.NumericValue.Two));
                            guilblSPModeratehypertensionValue.Left = guilblSPModeratehypertension.Left - (guilblSPModeratehypertensionValue.Width / Convert.ToInt32(GuiCommon.NumericValue.Three));
                            guilblSPModeratehypertensionValue.Text = spArray[3].ToString();

                            guilblSPlowhypertension.Left = guilblSPSlider.Left + ((spArray[4] - spArray[0]) * guilblSPSlider.Width / (int)(spArray[spArray.Length - Convert.ToInt32(GuiCommon.NumericValue.One)] - spArray[0])) - (guilblSPlowhypertension.Width / Convert.ToInt32(GuiCommon.NumericValue.Two));
                            guilblSPLowValue.Left = guilblSPlowhypertension.Left - (guilblSPLowValue.Width / Convert.ToInt32(GuiCommon.NumericValue.Three));
                            guilblSPLowValue.Text = spArray[4].ToString();

                            guilblSPSevere.Left = guilblSPSlider.Left + ((spArray[5] - spArray[0]) * guilblSPSlider.Width / (int)(spArray[spArray.Length - Convert.ToInt32(GuiCommon.NumericValue.One)] - spArray[0])) - (guilblSPSevere.Width / Convert.ToInt32(GuiCommon.NumericValue.Two));
                            guilblSPSevereValue.Left = guilblSPSevere.Left - (guilblSPSevereValue.Width / Convert.ToInt32(GuiCommon.NumericValue.Three));
                            guilblSPSevereValue.Text = spArray[5].ToString();

                            lblSpNormal.Left = ((guilblSPSlider.Left + ((guilblSPNormal.Left - guilblSPSlider.Left) / Convert.ToInt32(GuiCommon.NumericValue.Two))) - (lblSpNormal.Width / Convert.ToInt32(GuiCommon.NumericValue.Two)));
                            lblSpHighNormal.Left = ((guilblSPNormal.Left + ((guilblSPMildHypertension.Left - guilblSPNormal.Left) / Convert.ToInt32(GuiCommon.NumericValue.Two))) - (lblSpHighNormal.Width / Convert.ToInt32(GuiCommon.NumericValue.Two)));
                            lblSpMildHypertension.Left = ((guilblSPMildHypertension.Left + ((guilblSPModeratehypertension.Left - guilblSPMildHypertension.Left) / Convert.ToInt32(GuiCommon.NumericValue.Two))) - (lblSpMildHypertension.Width / Convert.ToInt32(GuiCommon.NumericValue.Two)));
                            lblSpModerateHypertension.Left = ((guilblSPModeratehypertension.Left + ((guilblSPLowValue.Left - guilblSPModeratehypertension.Left) / Convert.ToInt32(GuiCommon.NumericValue.Two))) - (lblSpModerateHypertension.Width / Convert.ToInt32(GuiCommon.NumericValue.Two)));
                            lblSpLowHypertension.Left = ((guilblSPLowValue.Left + ((guilblSPSevere.Left - guilblSPLowValue.Left) / Convert.ToInt32(GuiCommon.NumericValue.Two))) - (lblSpLowHypertension.Width / Convert.ToInt32(GuiCommon.NumericValue.Two)));
                            lblSpSevere.Left = ((guilblSPSevere.Left + ((guilblSPSlider.Right - guilblSPSevere.Left) / Convert.ToInt32(GuiCommon.NumericValue.Two))) - (lblSpSevere.Width / Convert.ToInt32(GuiCommon.NumericValue.Two)));

                            lblSpNormal.Text = textSpArray[0];
                            lblSpHighNormal.Text = textSpArray[1];
                            lblSpMildHypertension.Text = textSpArray[2];
                            lblSpModerateHypertension.Text = textSpArray[3];
                            lblSpLowHypertension.Text = textSpArray[4];
                            lblSpSevere.Text = textSpArray[5];

                            guilblSpStartPoint.Hide();
                            guilblSpEndPoint.Hide();

                            break;
                        default:
                            guilblSPNormal.Hide();
                            guilblSPNormalValue.Hide();
                            guilblSPMildHypertension.Hide();
                            guilblSPMildHypertensionValue.Hide();
                            guilblSPModeratehypertension.Hide();
                            guilblSPModeratehypertensionValue.Hide();
                            guilblSPlowhypertension.Hide();
                            guilblSPLowValue.Hide();
                            guilblSPSevere.Hide();
                            guilblSPSevereValue.Hide();
                            guilblSpStartPoint.Hide();
                            guilblSpEndPoint.Hide();

                            lblSpNormal.Hide();
                            lblSpHighNormal.Hide();
                            lblSpMildHypertension.Hide();
                            lblSpModerateHypertension.Hide();
                            lblSpLowHypertension.Hide();
                            lblSpSevere.Hide();
                            guilblSPSlider.Hide();
                            break;

                    }
                                
                // Validation to show Sp level on the slider or not
                // If SP value is smaller than smallet array value or greater than highest array value then lbl should be hidden
                    if (GuiCommon.crxPwaData.SP < spArray[0] || GuiCommon.crxPwaData.SP > spArray[spArray.Length - Convert.ToInt32(GuiCommon.NumericValue.One)] || (!check))
                {                   
                    lblSpValue.Hide();

                    if (!check)
                    {
                        guilblSpStartPoint.Hide();
                        guilblSpEndPoint.Hide();
                    }
                    else
                    {
                        guilblSpStartPoint.Show();
                        guilblSpEndPoint.Show();
                    }
                }
                else
                {
                    lblSpValue.Left = guilblSPSlider.Left + ((GuiCommon.crxPwaData.SP - spArray[0]) * guilblSPSlider.Width / (int)(spArray[spArray.Length - Convert.ToInt32(GuiCommon.NumericValue.One)] - spArray[0])) - (lblSpValue.Width / Convert.ToInt32(GuiCommon.NumericValue.Two));
                }           
            }
            catch (Exception eObj)
            {
                throw eObj;
            }
        }         

        private void SetDpSliderPosition(short arrSize)
        {
            try
            {
                short[] dpArray = new short[arrSize];
                bool check = obj.GetBrachialDPRange(GuiCommon.bizPwaobject.MeasureType, dpArray, arrSize);

                if (!check)
                {
                    arrSize = (short)Number.One;
                }

                //string[] textDpArray = new string[arrSize - Convert.ToInt32(GuiCommon.NumericValue.One)];
                string[] textDpArray = new string[6];

                // "Normal";
                //lblDpNormal.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.RptPwaNormalText);
                textDpArray[0] = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.RptPwaNormalText);

                // "High Normal";
                //lblDpHighNormal.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.RptPwaHighNormalText);
                textDpArray[1] = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.RptPwaHighNormalText);

                // "Mild Hypertension";
                //lblDpMildHypertension.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.RptPwaMildHypertensionText);
                textDpArray[2] = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.RptPwaMildHypertensionText);

                // "Moderate hypertension";
                //lblDpModerateHypertension.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.RptPwaModerateHypertensionText);
                textDpArray[3] = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.RptPwaModerateHypertensionText);

                // "Low hypertension" 
                textDpArray[4] = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.RptPwaLowHypertensionText);

                // "Severe";
                //lblDpSevere.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.RptPwaSevereText);
                textDpArray[5] = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.RptPwaSevereText);

                switch (arrSize)
                {
                    case (short)Number.Two:
                        guilblDPNormal.Hide();
                        guilblDPNormalValue.Hide();
                        guilblDPMildHypertension.Hide();
                        guilblDPMildHypertensionValue.Hide();
                        guilblDPModeratehypertension.Hide();
                        guilblDPModeratehypertensionValue.Hide();
                        guilblDPLowhypertension.Hide();
                        guilblDPLowhypertensionValue.Hide();
                        guilblDPSevere.Hide();
                        guilblDPSevereValue.Hide();
                        guilblDpStartPoint.Hide();
                        guilblDpEndPoint.Hide();

                        lblDpHighNormal.Hide();
                        lblDpMildHypertension.Hide();
                        lblDpModerateHypertension.Hide();
                        lblDpLowHypertension.Hide();
                        lblDpSevere.Hide();

                        lblDpNormal.Left = ((guilblDPSlider.Left + ((guilblDPSlider.Right - guilblDPSlider.Left) / Convert.ToInt32(GuiCommon.NumericValue.Two))) - (lblDpNormal.Width / Convert.ToInt32(GuiCommon.NumericValue.Two)));
                        lblDpNormal.Text = textDpArray[0];

                        break;
                    case (short)Number.Three:
                        guilblDPNormal.Left = guilblDPSlider.Left + ((dpArray[1] - dpArray[0]) * guilblDPSlider.Width / (int)(dpArray[dpArray.Length - Convert.ToInt32(GuiCommon.NumericValue.One)] - dpArray[0])) - (guilblDPNormal.Width / Convert.ToInt32(GuiCommon.NumericValue.Two));
                        guilblDPNormalValue.Left = guilblDPNormal.Left - (guilblDPNormalValue.Width / 3) + 4;
                        guilblDPNormalValue.Text = dpArray[1].ToString();

                        lblDpNormal.Left = ((guilblDPSlider.Left + ((guilblDPNormal.Left - guilblDPSlider.Left) / Convert.ToInt32(GuiCommon.NumericValue.Two))) - (lblDpNormal.Width / Convert.ToInt32(GuiCommon.NumericValue.Two)));
                        lblDpHighNormal.Left = ((guilblDPNormal.Left + ((guilblDPSlider.Right - guilblDPNormal.Left) / Convert.ToInt32(GuiCommon.NumericValue.Two))) - (lblDpHighNormal.Width / Convert.ToInt32(GuiCommon.NumericValue.Two)));

                        lblDpNormal.Text = textDpArray[0];
                        lblDpHighNormal.Text = textDpArray[1];

                        guilblDPMildHypertension.Hide();
                        guilblDPMildHypertensionValue.Hide();
                        guilblDPModeratehypertension.Hide();
                        guilblDPModeratehypertensionValue.Hide();
                        guilblDPLowhypertension.Hide();
                        guilblDPLowhypertensionValue.Hide();
                        guilblDPSevere.Hide();
                        guilblDPSevereValue.Hide();
                        guilblDpStartPoint.Hide();
                        guilblDpEndPoint.Hide();

                        lblDpMildHypertension.Hide();
                        lblDpModerateHypertension.Hide();
                        lblDpLowHypertension.Hide();
                        lblDpSevere.Hide();

                        break;

                    case (short)Number.Four:
                        guilblDPNormal.Left = guilblDPSlider.Left + ((dpArray[1] - dpArray[0]) * guilblDPSlider.Width / (int)(dpArray[dpArray.Length - Convert.ToInt32(GuiCommon.NumericValue.One)] - dpArray[0])) - (guilblDPNormal.Width / Convert.ToInt32(GuiCommon.NumericValue.Two));
                        guilblDPNormalValue.Left = guilblDPNormal.Left - (guilblDPNormalValue.Width / 3) + 4;
                        guilblDPNormalValue.Text = dpArray[1].ToString();

                        guilblDPMildHypertension.Left = guilblDPSlider.Left + ((dpArray[2] - dpArray[0]) * guilblDPSlider.Width / (int)(dpArray[dpArray.Length - Convert.ToInt32(GuiCommon.NumericValue.One)] - dpArray[0])) - (guilblDPMildHypertension.Width / Convert.ToInt32(GuiCommon.NumericValue.Two));
                        guilblDPMildHypertensionValue.Left = guilblDPMildHypertension.Left - (guilblDPMildHypertensionValue.Width / 3);
                        guilblDPMildHypertensionValue.Text = dpArray[2].ToString();

                        lblDpNormal.Left = ((guilblDPSlider.Left + ((guilblDPNormal.Left - guilblDPSlider.Left) / Convert.ToInt32(GuiCommon.NumericValue.Two))) - (lblDpNormal.Width / Convert.ToInt32(GuiCommon.NumericValue.Two)));
                        lblDpHighNormal.Left = ((guilblDPNormal.Left + ((guilblDPMildHypertension.Left - guilblDPNormal.Left) / Convert.ToInt32(GuiCommon.NumericValue.Two))) - (lblDpHighNormal.Width / Convert.ToInt32(GuiCommon.NumericValue.Two)));
                        lblDpMildHypertension.Left = ((guilblDPMildHypertension.Left + ((guilblDPSlider.Right - guilblDPMildHypertension.Left) / Convert.ToInt32(GuiCommon.NumericValue.Two))) - (lblDpMildHypertension.Width / Convert.ToInt32(GuiCommon.NumericValue.Two)));

                        lblDpNormal.Text = textDpArray[0];
                        lblDpHighNormal.Text = textDpArray[1];
                        lblDpMildHypertension.Text = textDpArray[2];

                        guilblDPModeratehypertension.Hide();
                        guilblDPModeratehypertensionValue.Hide();
                        guilblDPLowhypertension.Hide();
                        guilblDPLowhypertensionValue.Hide();
                        guilblDPSevere.Hide();
                        guilblDPSevereValue.Hide();
                        guilblDpStartPoint.Hide();
                        guilblDpEndPoint.Hide();

                        lblDpModerateHypertension.Hide();
                        lblDpLowHypertension.Hide();
                        lblDpSevere.Hide();

                        break;

                    case (short)Number.Five:
                        guilblDPNormal.Left = guilblDPSlider.Left + ((dpArray[1] - dpArray[0]) * guilblDPSlider.Width / (int)(dpArray[dpArray.Length - Convert.ToInt32(GuiCommon.NumericValue.One)] - dpArray[0])) - (guilblDPNormal.Width / Convert.ToInt32(GuiCommon.NumericValue.Two));
                        guilblDPNormalValue.Left = guilblDPNormal.Left - (guilblDPNormalValue.Width / 3) + 4;
                        guilblDPNormalValue.Text = dpArray[1].ToString();

                        guilblDPMildHypertension.Left = guilblDPSlider.Left + ((dpArray[2] - dpArray[0]) * guilblDPSlider.Width / (int)(dpArray[dpArray.Length - Convert.ToInt32(GuiCommon.NumericValue.One)] - dpArray[0])) - (guilblDPMildHypertension.Width / Convert.ToInt32(GuiCommon.NumericValue.Two));
                        guilblDPMildHypertensionValue.Left = guilblDPMildHypertension.Left - (guilblDPMildHypertensionValue.Width / 3);
                        guilblDPMildHypertensionValue.Text = dpArray[2].ToString();

                        guilblDPModeratehypertension.Left = guilblDPSlider.Left + ((dpArray[3] - dpArray[0]) * guilblDPSlider.Width / (int)(dpArray[dpArray.Length - Convert.ToInt32(GuiCommon.NumericValue.One)] - dpArray[0])) - (guilblDPModeratehypertension.Width / Convert.ToInt32(GuiCommon.NumericValue.Two));
                        guilblDPModeratehypertensionValue.Left = guilblDPModeratehypertension.Left - (guilblDPModeratehypertensionValue.Width / 3);
                        guilblDPModeratehypertensionValue.Text = dpArray[3].ToString();

                        lblDpNormal.Left = ((guilblDPSlider.Left + ((guilblDPNormal.Left - guilblDPSlider.Left) / Convert.ToInt32(GuiCommon.NumericValue.Two))) - (lblDpNormal.Width / Convert.ToInt32(GuiCommon.NumericValue.Two)));
                        lblDpHighNormal.Left = ((guilblDPNormal.Left + ((guilblDPMildHypertension.Left - guilblDPNormal.Left) / Convert.ToInt32(GuiCommon.NumericValue.Two))) - (lblDpHighNormal.Width / Convert.ToInt32(GuiCommon.NumericValue.Two)));
                        lblDpMildHypertension.Left = ((guilblDPMildHypertension.Left + ((guilblDPModeratehypertension.Left - guilblDPMildHypertension.Left) / Convert.ToInt32(GuiCommon.NumericValue.Two))) - (lblDpMildHypertension.Width / Convert.ToInt32(GuiCommon.NumericValue.Two)));
                        lblDpModerateHypertension.Left = ((guilblDPModeratehypertension.Left + ((guilblDPSlider.Right - guilblDPModeratehypertension.Left) / Convert.ToInt32(GuiCommon.NumericValue.Two))) - (lblDpModerateHypertension.Width / Convert.ToInt32(GuiCommon.NumericValue.Two)));

                        lblDpNormal.Text = textDpArray[0];
                        lblDpHighNormal.Text = textDpArray[1];
                        lblDpMildHypertension.Text = textDpArray[2];
                        lblDpModerateHypertension.Text = textDpArray[3];

                        guilblDPLowhypertension.Hide();
                        guilblDPLowhypertensionValue.Hide();
                        guilblDPSevere.Hide();
                        guilblDPSevereValue.Hide();
                        guilblDpStartPoint.Hide();
                        guilblDpEndPoint.Hide();

                        lblDpLowHypertension.Hide();
                        lblDpSevere.Hide();

                        break;
                    case (short)Number.Six:
                        guilblDPNormal.Left = guilblDPSlider.Left + ((dpArray[1] - dpArray[0]) * guilblDPSlider.Width / (int)(dpArray[dpArray.Length - Convert.ToInt32(GuiCommon.NumericValue.One)] - dpArray[0])) - (guilblDPNormal.Width / Convert.ToInt32(GuiCommon.NumericValue.Two));
                        guilblDPNormalValue.Left = guilblDPNormal.Left - (guilblDPNormalValue.Width / 3) + 4;
                        guilblDPNormalValue.Text = dpArray[1].ToString();

                        guilblDPMildHypertension.Left = guilblDPSlider.Left + ((dpArray[2] - dpArray[0]) * guilblDPSlider.Width / (int)(dpArray[dpArray.Length - Convert.ToInt32(GuiCommon.NumericValue.One)] - dpArray[0])) - (guilblDPMildHypertension.Width / Convert.ToInt32(GuiCommon.NumericValue.Two));
                        guilblDPMildHypertensionValue.Left = guilblDPMildHypertension.Left - (guilblDPMildHypertensionValue.Width / 3);
                        guilblDPMildHypertensionValue.Text = dpArray[2].ToString();

                        guilblDPModeratehypertension.Left = guilblDPSlider.Left + ((dpArray[3] - dpArray[0]) * guilblDPSlider.Width / (int)(dpArray[dpArray.Length - Convert.ToInt32(GuiCommon.NumericValue.One)] - dpArray[0])) - (guilblDPModeratehypertension.Width / Convert.ToInt32(GuiCommon.NumericValue.Two));
                        guilblDPModeratehypertensionValue.Left = guilblDPModeratehypertension.Left - (guilblDPModeratehypertensionValue.Width / 3);
                        guilblDPModeratehypertensionValue.Text = dpArray[3].ToString();

                        guilblDPLowhypertension.Left = guilblDPSlider.Left + ((dpArray[4] - dpArray[0]) * guilblDPSlider.Width / (int)(dpArray[dpArray.Length - Convert.ToInt32(GuiCommon.NumericValue.One)] - dpArray[0])) - (guilblDPLowhypertension.Width / Convert.ToInt32(GuiCommon.NumericValue.Two));
                        guilblDPLowhypertensionValue.Left = guilblDPLowhypertension.Left - (guilblDPNormalValue.Width / 3);
                        guilblDPLowhypertensionValue.Text = dpArray[4].ToString();

                        lblDpNormal.Left = ((guilblDPSlider.Left + ((guilblDPNormal.Left - guilblDPSlider.Left) / Convert.ToInt32(GuiCommon.NumericValue.Two))) - (lblDpNormal.Width / Convert.ToInt32(GuiCommon.NumericValue.Two)));
                        lblDpHighNormal.Left = ((guilblDPNormal.Left + ((guilblDPMildHypertension.Left - guilblDPNormal.Left) / Convert.ToInt32(GuiCommon.NumericValue.Two))) - (lblDpHighNormal.Width / Convert.ToInt32(GuiCommon.NumericValue.Two)));
                        lblDpMildHypertension.Left = ((guilblDPMildHypertension.Left + ((guilblDPModeratehypertension.Left - guilblDPMildHypertension.Left) / Convert.ToInt32(GuiCommon.NumericValue.Two))) - (lblDpMildHypertension.Width / Convert.ToInt32(GuiCommon.NumericValue.Two)));
                        lblDpModerateHypertension.Left = ((guilblDPModeratehypertension.Left + ((guilblDPLowhypertensionValue.Left - guilblDPModeratehypertension.Left) / Convert.ToInt32(GuiCommon.NumericValue.Two))) - (lblDpModerateHypertension.Width / Convert.ToInt32(GuiCommon.NumericValue.Two)));
                        // lblDpSevere.Left = ((guilblDPSevere.Left + ((guilblDPSevere.Right - guilblDPModeratehypertension.Left) /Convert.ToInt32(GuiCommon.NumericValue.Two))) - (lblDpSevere.Width /Convert.ToInt32(GuiCommon.NumericValue.Two)));
                        lblDpLowHypertension.Left = ((guilblDPLowhypertensionValue.Left + ((guilblDPSlider.Right - guilblDPLowhypertensionValue.Left) / Convert.ToInt32(GuiCommon.NumericValue.Two))) - (lblDpLowHypertension.Width / Convert.ToInt32(GuiCommon.NumericValue.Two)));

                        lblDpNormal.Text = textDpArray[0];
                        lblDpHighNormal.Text = textDpArray[1];
                        lblDpMildHypertension.Text = textDpArray[2];
                        lblDpModerateHypertension.Text = textDpArray[3];
                        lblDpLowHypertension.Text = textDpArray[4];

                        guilblDPSevere.Hide();
                        guilblDPSevereValue.Hide();
                        guilblDpStartPoint.Hide();
                        guilblDpEndPoint.Hide();

                        lblDpSevere.Hide();

                        break;
                    case (short)Number.Seven:
                        guilblDPNormal.Left = guilblDPSlider.Left + ((dpArray[1] - dpArray[0]) * guilblDPSlider.Width / (int)(dpArray[dpArray.Length - Convert.ToInt32(GuiCommon.NumericValue.One)] - dpArray[0])) - (guilblDPNormal.Width / Convert.ToInt32(GuiCommon.NumericValue.Two));
                        guilblDPNormalValue.Left = guilblDPNormal.Left - (guilblDPNormalValue.Width / 3) + 4;
                        guilblDPNormalValue.Text = dpArray[1].ToString();

                        guilblDPMildHypertension.Left = guilblDPSlider.Left + ((dpArray[2] - dpArray[0]) * guilblDPSlider.Width / (int)(dpArray[dpArray.Length - Convert.ToInt32(GuiCommon.NumericValue.One)] - dpArray[0])) - (guilblDPMildHypertension.Width / Convert.ToInt32(GuiCommon.NumericValue.Two));
                        guilblDPMildHypertensionValue.Left = guilblDPMildHypertension.Left - (guilblDPMildHypertensionValue.Width / 3);
                        guilblDPMildHypertensionValue.Text = dpArray[2].ToString();

                        guilblDPModeratehypertension.Left = guilblDPSlider.Left + ((dpArray[3] - dpArray[0]) * guilblDPSlider.Width / (int)(dpArray[dpArray.Length - Convert.ToInt32(GuiCommon.NumericValue.One)] - dpArray[0])) - (guilblDPModeratehypertension.Width / Convert.ToInt32(GuiCommon.NumericValue.Two));
                        guilblDPModeratehypertensionValue.Left = guilblDPModeratehypertension.Left - (guilblDPModeratehypertensionValue.Width / 3);
                        guilblDPModeratehypertensionValue.Text = dpArray[3].ToString();

                        guilblDPLowhypertension.Left = guilblDPSlider.Left + ((dpArray[4] - dpArray[0]) * guilblDPSlider.Width / (int)(dpArray[dpArray.Length - Convert.ToInt32(GuiCommon.NumericValue.One)] - dpArray[0])) - (guilblDPLowhypertension.Width / Convert.ToInt32(GuiCommon.NumericValue.Two));
                        guilblDPLowhypertensionValue.Left = guilblDPLowhypertension.Left - (guilblDPNormalValue.Width / 3);
                        guilblDPLowhypertensionValue.Text = dpArray[4].ToString();

                        guilblDPSevere.Left = guilblDPSlider.Left + ((dpArray[5] - dpArray[0]) * guilblDPSlider.Width / (int)(dpArray[dpArray.Length - Convert.ToInt32(GuiCommon.NumericValue.One)] - dpArray[0])) - (guilblDPSevere.Width / Convert.ToInt32(GuiCommon.NumericValue.Two));
                        guilblDPSevereValue.Left = guilblDPSevere.Left - (guilblDPSevereValue.Width / 3);
                        guilblDPSevereValue.Text = dpArray[5].ToString();

                        lblDpNormal.Left = ((guilblDPSlider.Left + ((guilblDPNormal.Left - guilblDPSlider.Left) / Convert.ToInt32(GuiCommon.NumericValue.Two))) - (lblDpNormal.Width / Convert.ToInt32(GuiCommon.NumericValue.Two)));
                        lblDpHighNormal.Left = ((guilblDPNormal.Left + ((guilblDPMildHypertension.Left - guilblDPNormal.Left) / Convert.ToInt32(GuiCommon.NumericValue.Two))) - (lblDpHighNormal.Width / Convert.ToInt32(GuiCommon.NumericValue.Two)));
                        lblDpMildHypertension.Left = ((guilblDPMildHypertension.Left + ((guilblDPModeratehypertension.Left - guilblDPMildHypertension.Left) / Convert.ToInt32(GuiCommon.NumericValue.Two))) - (lblDpMildHypertension.Width / Convert.ToInt32(GuiCommon.NumericValue.Two)));
                        lblDpModerateHypertension.Left = ((guilblDPModeratehypertension.Left + ((guilblDPLowhypertensionValue.Left - guilblDPModeratehypertension.Left) / Convert.ToInt32(GuiCommon.NumericValue.Two))) - (lblDpModerateHypertension.Width / Convert.ToInt32(GuiCommon.NumericValue.Two)));
                        lblDpLowHypertension.Left = ((guilblDPLowhypertensionValue.Left + ((guilblDPSevere.Left - guilblDPLowhypertensionValue.Left) / Convert.ToInt32(GuiCommon.NumericValue.Two))) - (lblDpLowHypertension.Width / Convert.ToInt32(GuiCommon.NumericValue.Two)));
                        lblDpSevere.Left = ((guilblDPSevere.Left + ((guilblDPSlider.Right - guilblDPSevere.Left) / Convert.ToInt32(GuiCommon.NumericValue.Two))) - (lblDpSevere.Width / Convert.ToInt32(GuiCommon.NumericValue.Two)));

                        lblDpNormal.Text = textDpArray[0];
                        lblDpHighNormal.Text = textDpArray[1];
                        lblDpMildHypertension.Text = textDpArray[2];
                        lblDpModerateHypertension.Text = textDpArray[3];
                        lblDpLowHypertension.Text = textDpArray[4];
                        lblDpSevere.Text = textDpArray[5];

                        guilblDpStartPoint.Hide();
                        guilblDpEndPoint.Hide();

                        break;
                    default:
                        guilblDPNormal.Hide();
                        guilblDPNormalValue.Hide();
                        guilblDPMildHypertension.Hide();
                        guilblDPMildHypertensionValue.Hide();
                        guilblDPModeratehypertension.Hide();
                        guilblDPModeratehypertensionValue.Hide();
                        guilblDPLowhypertension.Hide();
                        guilblDPLowhypertensionValue.Hide();
                        guilblDPSevere.Hide();
                        guilblDPSevereValue.Hide();
                        guilblDpStartPoint.Hide();
                        guilblDpEndPoint.Hide();

                        lblDpNormal.Hide();
                        lblDpHighNormal.Hide();
                        lblDpMildHypertension.Hide();
                        lblDpModerateHypertension.Hide();
                        lblDpLowHypertension.Hide();
                        lblDpSevere.Hide();

                        guilblDPSlider.Hide();

                        break;
                }

                // Validation to show Dp level on the slider or not
                // If DP value is smaller than smallet array value or greater than highest array value then lbl should be hidden
                if (GuiCommon.crxPwaData.DP < dpArray[0] || GuiCommon.crxPwaData.DP > dpArray[dpArray.Length - Convert.ToInt32(GuiCommon.NumericValue.One)] || !(check))
                {
                    lblDpValue.Hide();

                    if(!check)
                    {
                        guilblDpStartPoint.Hide();
                        guilblDpEndPoint.Hide();
                    }
                    else
                    {
                        guilblDpStartPoint.Show();
                        guilblDpEndPoint.Show();
                    }
                }
                else
                {
                    //int diffValue = Convert.ToInt32(GuiCommon.crxPwaData.DP) - dpSliderValueStartPoint;
                    //int sliderPos = dpSliderPositionStartPoint + (diffValue * dpMultiplicationFactor);
                    //lblDpValue.Left = sliderPos;
                    lblDpValue.Left = guilblDPSlider.Left + ((GuiCommon.crxPwaData.DP - dpArray[0]) * guilblDPSlider.Width / (int)(dpArray[dpArray.Length - Convert.ToInt32(GuiCommon.NumericValue.One)] - dpArray[0])) - (lblDpValue.Width / Convert.ToInt32(GuiCommon.NumericValue.Two));
                }              
            }
            catch (Exception eObj)
            {
                throw eObj;
            }
        }

        private void SetHrSliderPosition(short arrSize)
        {
            try
            {
                short[] hrArray = new short[arrSize];
                
                bool check = obj.GetHRRange(GuiCommon.crxPwaData.HR, GuiCommon.bizPwaobject.MeasureType, hrArray, arrSize);

                if (!check)
                {
                    arrSize = (short)Number.One;
                }

                switch (arrSize)
                {
                    case (short)Number.Two:
                        guilblHrExcellent.Hide();
                        guilblHrGood.Hide();
                        guilblHrAboveAverage.Hide();
                        guilblHrAverage.Hide();
                        guilblHrBelowAverage.Hide();

                        // "Excellent";
                        lblHrExcellent.Left = ((guilblHrSlider.Left + ((guilblHrSlider.Right - guilblHrSlider.Left) / Convert.ToInt32(GuiCommon.NumericValue.Two))) - (lblHrExcellent.Width / Convert.ToInt32(GuiCommon.NumericValue.Two)));
                        lblHrExcellent.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.RptPwaExcellentText);

                        lblHrGood.Hide();
                        lblHrAboveAverage.Hide();
                        lblHrAverage.Hide();
                        lblHrBelowAverage.Hide();
                        lblHrPoor.Hide();

                        break;
                    case (short)Number.Three:
                        guilblHrExcellent.Left = guilblHrSlider.Left + ((hrArray[1] - hrArray[0]) * guilblHrSlider.Width / (int)(hrArray[hrArray.Length - Convert.ToInt32(GuiCommon.NumericValue.One)] - hrArray[0])) - (guilblHrExcellent.Width / Convert.ToInt32(GuiCommon.NumericValue.Two));
                        
                        guilblHrGood.Hide();
                        guilblHrAboveAverage.Hide();
                        guilblHrAverage.Hide();
                        guilblHrBelowAverage.Hide();

                        // "Excellent";
                        lblHrExcellent.Left = ((guilblHrSlider.Left + ((guilblHrExcellent.Left - guilblHrSlider.Left) / Convert.ToInt32(GuiCommon.NumericValue.Two))) - (lblHrExcellent.Width / Convert.ToInt32(GuiCommon.NumericValue.Two)));
                        lblHrExcellent.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.RptPwaExcellentText);

                        // "Good";
                        lblHrGood.Left = ((guilblHrExcellent.Left + ((guilblHrSlider.Right - guilblHrExcellent.Left) / Convert.ToInt32(GuiCommon.NumericValue.Two))) - (lblHrGood.Width / Convert.ToInt32(GuiCommon.NumericValue.Two)));
                        lblHrGood.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.RptPwaGoodText);

                        lblHrAboveAverage.Hide();
                        lblHrAverage.Hide();
                        lblHrBelowAverage.Hide();
                        lblHrPoor.Hide();
                  
                        break;
                    case (short)Number.Four:
                        guilblHrExcellent.Left = guilblHrSlider.Left + ((hrArray[1] - hrArray[0]) * guilblHrSlider.Width / (int)(hrArray[hrArray.Length - Convert.ToInt32(GuiCommon.NumericValue.One)] - hrArray[0])) - (guilblHrExcellent.Width / Convert.ToInt32(GuiCommon.NumericValue.Two));

                        guilblHrGood.Left = guilblHrSlider.Left + ((hrArray[2] - hrArray[0]) * guilblHrSlider.Width / (int)(hrArray[hrArray.Length - Convert.ToInt32(GuiCommon.NumericValue.One)] - hrArray[0])) - (guilblHrGood.Width / Convert.ToInt32(GuiCommon.NumericValue.Two));

                        guilblHrAboveAverage.Hide();
                        guilblHrAverage.Hide();
                        guilblHrBelowAverage.Hide();

                        // "Excellent";
                        lblHrExcellent.Left = ((guilblHrSlider.Left + ((guilblHrExcellent.Left - guilblHrSlider.Left) / Convert.ToInt32(GuiCommon.NumericValue.Two))) - (lblHrExcellent.Width / Convert.ToInt32(GuiCommon.NumericValue.Two)));
                        lblHrExcellent.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.RptPwaExcellentText);

                        // "Good";
                        lblHrGood.Left = ((guilblHrExcellent.Left + ((guilblHrGood.Left - guilblHrExcellent.Left) / Convert.ToInt32(GuiCommon.NumericValue.Two))) - (lblHrGood.Width / Convert.ToInt32(GuiCommon.NumericValue.Two)));
                        lblHrGood.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.RptPwaGoodText);

                        // "Above average";
                        lblHrAboveAverage.Left = ((guilblHrGood.Left + ((guilblHrSlider.Right - guilblHrGood.Left) / Convert.ToInt32(GuiCommon.NumericValue.Two))) - (lblHrAboveAverage.Width / Convert.ToInt32(GuiCommon.NumericValue.Two)));
                        lblHrAboveAverage.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.RptPwaAboveAverageText);

                        lblHrAverage.Hide();
                        lblHrBelowAverage.Hide();
                        lblHrPoor.Hide();

                        break;
                    case (short)Number.Five:
                        guilblHrExcellent.Left = guilblHrSlider.Left + ((hrArray[1] - hrArray[0]) * guilblHrSlider.Width / (int)(hrArray[hrArray.Length - Convert.ToInt32(GuiCommon.NumericValue.One)] - hrArray[0])) - (guilblHrExcellent.Width / Convert.ToInt32(GuiCommon.NumericValue.Two));

                        guilblHrGood.Left = guilblHrSlider.Left + ((hrArray[2] - hrArray[0]) * guilblHrSlider.Width / (int)(hrArray[hrArray.Length - Convert.ToInt32(GuiCommon.NumericValue.One)] - hrArray[0])) - (guilblHrGood.Width / Convert.ToInt32(GuiCommon.NumericValue.Two));

                        guilblHrAboveAverage.Left = guilblHrSlider.Left + ((hrArray[3] - hrArray[0]) * guilblHrSlider.Width / (int)(hrArray[hrArray.Length - Convert.ToInt32(GuiCommon.NumericValue.One)] - hrArray[0])) - (guilblHrAboveAverage.Width / Convert.ToInt32(GuiCommon.NumericValue.Two));

                        guilblHrAverage.Hide();
                        guilblHrBelowAverage.Hide();

                        lblHrBelowAverage.Hide();
                        lblHrPoor.Hide();

                        // "Excellent";
                        lblHrExcellent.Left = ((guilblHrSlider.Left + ((guilblHrExcellent.Left - guilblHrSlider.Left) / Convert.ToInt32(GuiCommon.NumericValue.Two))) - (lblHrExcellent.Width / Convert.ToInt32(GuiCommon.NumericValue.Two)));
                        lblHrExcellent.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.RptPwaExcellentText);

                        // "Good";
                        lblHrGood.Left = ((guilblHrExcellent.Left + ((guilblHrGood.Left - guilblHrExcellent.Left) / Convert.ToInt32(GuiCommon.NumericValue.Two))) - (lblHrGood.Width / Convert.ToInt32(GuiCommon.NumericValue.Two)));
                        lblHrGood.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.RptPwaGoodText);

                        // "Above average";
                        lblHrAboveAverage.Left = ((guilblHrGood.Left + ((guilblHrAboveAverage.Left - guilblHrGood.Left) / Convert.ToInt32(GuiCommon.NumericValue.Two))) - (lblHrAboveAverage.Width / Convert.ToInt32(GuiCommon.NumericValue.Two)));
                        lblHrAboveAverage.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.RptPwaAboveAverageText);

                        // "Average";
                        lblHrAverage.Left = ((guilblHrAboveAverage.Left + ((guilblHrSlider.Right - guilblHrAboveAverage.Left) / Convert.ToInt32(GuiCommon.NumericValue.Two))) - (lblHrAverage.Width / Convert.ToInt32(GuiCommon.NumericValue.Two)));
                        lblHrAverage.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.RptPwaAverageText);

                        lblHrBelowAverage.Hide();
                        lblHrPoor.Hide();
                     
                        break;
                    case (short)Number.Six:
                        guilblHrExcellent.Left = guilblHrSlider.Left + ((hrArray[1] - hrArray[0]) * guilblHrSlider.Width / (int)(hrArray[hrArray.Length - Convert.ToInt32(GuiCommon.NumericValue.One)] - hrArray[0])) - (guilblHrExcellent.Width / Convert.ToInt32(GuiCommon.NumericValue.Two));

                        guilblHrGood.Left = guilblHrSlider.Left + ((hrArray[2] - hrArray[0]) * guilblHrSlider.Width / (int)(hrArray[hrArray.Length - Convert.ToInt32(GuiCommon.NumericValue.One)] - hrArray[0])) - (guilblHrGood.Width / Convert.ToInt32(GuiCommon.NumericValue.Two));

                        guilblHrAboveAverage.Left = guilblHrSlider.Left + ((hrArray[3] - hrArray[0]) * guilblHrSlider.Width / (int)(hrArray[hrArray.Length - Convert.ToInt32(GuiCommon.NumericValue.One)] - hrArray[0])) - (guilblHrAboveAverage.Width / Convert.ToInt32(GuiCommon.NumericValue.Two));

                        guilblHrAverage.Left = guilblHrSlider.Left + ((hrArray[4] - hrArray[0]) * guilblHrSlider.Width / (int)(hrArray[hrArray.Length - Convert.ToInt32(GuiCommon.NumericValue.One)] - hrArray[0])) - (guilblHrAverage.Width / Convert.ToInt32(GuiCommon.NumericValue.Two));

                        guilblHrBelowAverage.Hide();

                        // "Excellent";
                        lblHrExcellent.Left = ((guilblHrSlider.Left + ((guilblHrExcellent.Left - guilblHrSlider.Left) / Convert.ToInt32(GuiCommon.NumericValue.Two))) - (lblHrExcellent.Width / Convert.ToInt32(GuiCommon.NumericValue.Two)));
                        lblHrExcellent.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.RptPwaExcellentText);

                        // "Good";
                        lblHrGood.Left = ((guilblHrExcellent.Left + ((guilblHrGood.Left - guilblHrExcellent.Left) / Convert.ToInt32(GuiCommon.NumericValue.Two))) - (lblHrGood.Width / Convert.ToInt32(GuiCommon.NumericValue.Two)));
                        lblHrGood.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.RptPwaGoodText);

                        // "Above average";
                        lblHrAboveAverage.Left = ((guilblHrGood.Left + ((guilblHrAboveAverage.Left - guilblHrGood.Left) / Convert.ToInt32(GuiCommon.NumericValue.Two))) - (lblHrAboveAverage.Width / Convert.ToInt32(GuiCommon.NumericValue.Two)));
                        lblHrAboveAverage.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.RptPwaAboveAverageText);

                        // "Average";
                        lblHrAverage.Left = ((guilblHrAboveAverage.Left + ((guilblHrAverage.Left - guilblHrAboveAverage.Left) / Convert.ToInt32(GuiCommon.NumericValue.Two))) - (lblHrAverage.Width / Convert.ToInt32(GuiCommon.NumericValue.Two)));
                        lblHrAverage.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.RptPwaAverageText);

                        // "Below average";
                        lblHrBelowAverage.Left = ((guilblHrAverage.Left + ((guilblHrSlider.Right - guilblHrAverage.Left) / Convert.ToInt32(GuiCommon.NumericValue.Two))) - (lblHrBelowAverage.Width / Convert.ToInt32(GuiCommon.NumericValue.Two)));
                        lblHrBelowAverage.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.RptPwaBelowAverageText);

                        lblHrPoor.Hide();

                        break;
                    case (short)Number.Seven:
                        guilblHrExcellent.Left = guilblHrSlider.Left + ((hrArray[1] - hrArray[0]) * guilblHrSlider.Width / (int)(hrArray[hrArray.Length - Convert.ToInt32(GuiCommon.NumericValue.One)] - hrArray[0])) - (guilblHrExcellent.Width / Convert.ToInt32(GuiCommon.NumericValue.Two));

                        guilblHrGood.Left = guilblHrSlider.Left + ((hrArray[2] - hrArray[0]) * guilblHrSlider.Width / (int)(hrArray[hrArray.Length - Convert.ToInt32(GuiCommon.NumericValue.One)] - hrArray[0])) - (guilblHrGood.Width / Convert.ToInt32(GuiCommon.NumericValue.Two));

                        guilblHrAboveAverage.Left = guilblHrSlider.Left + ((hrArray[3] - hrArray[0]) * guilblHrSlider.Width / (int)(hrArray[hrArray.Length - Convert.ToInt32(GuiCommon.NumericValue.One)] - hrArray[0])) - (guilblHrAboveAverage.Width / Convert.ToInt32(GuiCommon.NumericValue.Two));

                        guilblHrAverage.Left = guilblHrSlider.Left + ((hrArray[4] - hrArray[0]) * guilblHrSlider.Width / (int)(hrArray[hrArray.Length - Convert.ToInt32(GuiCommon.NumericValue.One)] - hrArray[0])) - (guilblHrAverage.Width / Convert.ToInt32(GuiCommon.NumericValue.Two));

                        guilblHrBelowAverage.Left = guilblHrSlider.Left + ((hrArray[5] - hrArray[0]) * guilblHrSlider.Width / (int)(hrArray[hrArray.Length - Convert.ToInt32(GuiCommon.NumericValue.One)] - hrArray[0])) - (guilblHrBelowAverage.Width / Convert.ToInt32(GuiCommon.NumericValue.Two));

                        // "Excellent";
                        lblHrExcellent.Left = ((guilblHrSlider.Left + ((guilblHrExcellent.Left - guilblHrSlider.Left) / Convert.ToInt32(GuiCommon.NumericValue.Two))) - (lblHrExcellent.Width / Convert.ToInt32(GuiCommon.NumericValue.Two)));
                        lblHrExcellent.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.RptPwaExcellentText);

                        // "Good";
                        lblHrGood.Left = ((guilblHrExcellent.Left + ((guilblHrGood.Left - guilblHrExcellent.Left) / Convert.ToInt32(GuiCommon.NumericValue.Two))) - (lblHrGood.Width / Convert.ToInt32(GuiCommon.NumericValue.Two)));
                        lblHrGood.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.RptPwaGoodText);

                        // "Above average";
                        lblHrAboveAverage.Left = ((guilblHrGood.Left + ((guilblHrAboveAverage.Left - guilblHrGood.Left) / Convert.ToInt32(GuiCommon.NumericValue.Two))) - (lblHrAboveAverage.Width / Convert.ToInt32(GuiCommon.NumericValue.Two)));
                        lblHrAboveAverage.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.RptPwaAboveAverageText);

                        // "Average";
                        lblHrAverage.Left = ((guilblHrAboveAverage.Left + ((guilblHrAverage.Left - guilblHrAboveAverage.Left) / Convert.ToInt32(GuiCommon.NumericValue.Two))) - (lblHrAverage.Width / Convert.ToInt32(GuiCommon.NumericValue.Two)));
                        lblHrAverage.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.RptPwaAverageText);

                        // "Below average";
                        lblHrBelowAverage.Left = ((guilblHrAverage.Left + ((guilblHrBelowAverage.Left - guilblHrAverage.Left) / Convert.ToInt32(GuiCommon.NumericValue.Two))) - (lblHrBelowAverage.Width / Convert.ToInt32(GuiCommon.NumericValue.Two)));
                        lblHrBelowAverage.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.RptPwaBelowAverageText);

                        // "Poor";
                        lblHrPoor.Left = ((guilblHrBelowAverage.Left + ((guilblHrSlider.Right - guilblHrBelowAverage.Left) / Convert.ToInt32(GuiCommon.NumericValue.Two))) - (lblHrPoor.Width / Convert.ToInt32(GuiCommon.NumericValue.Two)));
                        lblHrPoor.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.RptPwaPoorText);

                        break;                 
                    default:

                        guilblHrExcellent.Hide();
                        guilblHrGood.Hide();
                        guilblHrAboveAverage.Hide();
                        guilblHrAverage.Hide();
                        guilblHrBelowAverage.Hide();
                                               
                        lblHrExcellent.Hide();
                        lblHrGood.Hide();
                        lblHrAboveAverage.Hide();
                        lblHrAverage.Hide();
                        lblHrBelowAverage.Hide();
                        lblHrPoor.Hide();

                        guilblHrSlider.Hide();

                        break;
                }

                // Validation to show Dp level on the slider or not
                // If DP value is smaller than smallet array value or greater than highest array value then lbl should be hidden
                if (GuiCommon.crxPwaData.HR < hrArray[0] || GuiCommon.crxPwaData.HR > hrArray[hrArray.Length - Convert.ToInt32(GuiCommon.NumericValue.One)] || (!check))
                {
                    lblHrValue.Hide();
                }
                else
                {
                    //int diffValue = Convert.ToInt32(GuiCommon.crxPwaData.HR) - dpSliderValueStartPoint;
                    //int sliderPos = dpSliderPositionStartPoint + (diffValue * dpMultiplicationFactor);
                    //lblHrValue.Left = sliderPos;
                    lblHrValue.Left = guilblHrSlider.Left + ((Convert.ToInt16(GuiCommon.crxPwaData.HR) - hrArray[0]) * guilblHrSlider.Width / (int)(hrArray[hrArray.Length - Convert.ToInt32(GuiCommon.NumericValue.One)] - hrArray[0])) - (lblHrValue.Width / Convert.ToInt32(GuiCommon.NumericValue.Two));
                }
            }
            catch (Exception eObj)
            {
                throw eObj;
            }
        }
    }
}
