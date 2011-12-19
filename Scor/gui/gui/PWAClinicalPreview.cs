
/* 
     Copyright (C) ATCOR MEDICAL PTY LTD, 2010 
  
     Filename     :     PWAClinicalPreview.cs
        
     Author       :     Smarajit Mishra 
  
     Description  :     Creates an intermediate form for printing PWA clinical report. 
*/

using System;
using System.Collections;
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
using Telerik.WinControls;
using Telerik.WinControls.UI;

namespace AtCor.Scor.Gui.Presentation
{
    public partial class PWAClinicalPreview : Form
    {
        readonly CrxMessagingManager oMsgMgr = CrxMessagingManager.Instance;
        readonly CrxConfigManager crxMgrObject = CrxConfigManager.Instance;
        BizPWA obj;
        float[] pRawSignals;
        short[] pRawSignalsOnset;
        Series singlePRawSignalPulse;
        decimal averageAorticXAxisInterval = Math.Round((decimal)(1000.0 / 256.0));

        // Series typicalSeries;
        // Series actualSeries;

        /** This method to initialize the PWA Clinical Preview
         * */
        public PWAClinicalPreview()
        {
            InitializeComponent();
        }

        /** This method to load the PWA Clinical Preview form
        * */
        private void PWAClinicalPreview_Load(object sender, EventArgs e)
        {
            try
            {                
                obj = (BizPWA)BizSession.Instance().measurement;

                guiradlblSysUnit.ForeColor = guiradlblPpUit.ForeColor = guiradlblApUnit.ForeColor = guiradlblAixUnit.ForeColor = Color.Black;

                SetTextForLabels();
                PopulateCentralClinicalParameters();
                PlotCentralPressueWaveform();
                PlotRawSignals();
                PlotSinglePRawSignalPulse();               
                PWAPrintReport objPwaPrintReport = new PWAPrintReport(this);

                // If Augumentation Index is checked in PWA Settings tab 
                if (crxMgrObject.PwaSettings.AugmentationIndex)
                {
                    guiradlblReportAIx.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.LblAix);
                    guiradlblAix.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.LblAix) + ":";
                }
                else
                {
                    guiradlblReportAIx.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.LblPwaReportAIX75);
                    guiradlblAix.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.LblPwaReportAIX75) + ":";
                }
                
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

        /** This method to Populate Central Clinical Parameters
        * */
        private void PopulateCentralClinicalParameters()
        {
            try
            {
                guiradlblSphygmocorReferenceAge.Text = PWACommonReportData.RptReferenceAgeValue;

                if (GuiCommon.bizPwaobject.ReferenceAge == GuiConstants.DefaultValue)
                {
                    guiradlblSphygmocorReferenceAge.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.LblSphygmoCorReferenceAgeNotCalculated);
                }

                short high = 0;
                short low = 0;

                // If Augumentation Index is checked in PWA Settings tab 
                if (crxMgrObject.PwaSettings.AugmentationIndex)
                {
                    if (GuiCommon.crxPwaData.C_Agph != GuiConstants.DefaultValue)
                    {
                        if (GuiCommon.bizPwaobject.GetAixRange(PWA_MEASURE_TYPE.PWA_RADIAL, ref high, ref low))
                        {
                            guipnlBpMeasurementValues.Visible = false;
                            guipnlSliderControls.Visible = true;
                            double[] temp = setSliderMinMaxForXAxis(new double[] { GuiCommon.crxPwaData.C_Agph, low, high }, guiradlblAixMaxRangeText, guiradlblAixMinRangeText);
                            ShowAixTracker(((float)temp[0]), ((float)temp[1]), GuiCommon.crxPwaData.C_Agph, low, high, true);
                            PWAClinicalReportData.RptSliderPanel = true;
                        }
                        else
                        {
                            guipnlBpMeasurementValues.Visible = true;
                            guipnlSliderControls.Visible = false;
                            guiradlblAixValue.Visible = true;
                            guiradlblAixNotCalc.Visible = false;
                            guiradlblAixValue.Text = Math.Round(GuiCommon.crxPwaData.C_Agph).ToString();
                            PWAClinicalReportData.RptSliderPanel = false;
                        }
                    }
                    else
                    {
                        guipnlBpMeasurementValues.Visible = true;
                        guipnlSliderControls.Visible = false;
                        guiradlblAixValue.Visible = false;
                        guiradlblAixNotCalc.Visible = true;
                        PWAClinicalReportData.RptSliderPanel = false;
                    }
                }
                else
                {
                    if (GuiCommon.bizPwaobject.AGPH_HR75 != GuiConstants.DefaultValue)
                    {
                        if (GuiCommon.bizPwaobject.GetAixhr75Range(PWA_MEASURE_TYPE.PWA_RADIAL, ref high, ref low))
                        {
                            guipnlBpMeasurementValues.Visible = false;
                            guipnlSliderControls.Visible = true;
                            double[] temp = setSliderMinMaxForXAxis(new double[] { GuiCommon.bizPwaobject.AGPH_HR75, low, high }, guiradlblAixMaxRangeText, guiradlblAixMinRangeText);
                            ShowAixTracker(((float)temp[0]), ((float)temp[1]), GuiCommon.bizPwaobject.AGPH_HR75, low, high, true);
                            PWAClinicalReportData.RptSliderPanel = true;
                        }
                        else
                        {
                            guipnlBpMeasurementValues.Visible = true;
                            guipnlSliderControls.Visible = false;
                            guiradlblAixValue.Visible = true;
                            guiradlblAixNotCalc.Visible = false;
                            guiradlblAixValue.Text = Math.Round(GuiCommon.crxPwaData.C_Agph).ToString();
                            PWAClinicalReportData.RptSliderPanel = false;
                        }
                    }
                    else
                    {
                        guipnlBpMeasurementValues.Visible = true;
                        guipnlSliderControls.Visible = false;
                        guiradlblAixValue.Visible = false;
                        guiradlblAixNotCalc.Visible = true;
                        PWAClinicalReportData.RptSliderPanel = false;
                    }
                }

                if (GuiCommon.crxPwaData.C_Sp != GuiConstants.DefaultValue)
                {
                    if (GuiCommon.bizPwaobject.GetSPRange(PWA_MEASURE_TYPE.PWA_RADIAL, ref high, ref low))
                    {
                        guipnlBpMeasurementValues.Visible = false;
                        guipnlSliderControls.Visible = true;
                        double[] temp = setSliderMinMaxForXAxis(new double[] { GuiCommon.crxPwaData.C_Sp, low, high }, guiradlblSpMaxRangeText, guiradlblSpMinRangeText);
                        ShowSpTracker(((float)temp[0]), ((float)temp[1]), GuiCommon.crxPwaData.C_Sp, low, high, true);
                        PWAClinicalReportData.RptSliderPanel = true;
                    }
                    else
                    {
                        guipnlBpMeasurementValues.Visible = true;
                        guipnlSliderControls.Visible = false;
                        guiradlblSpValue.Visible = true;
                        guiradlblSpNotCalc.Visible = false;
                        guiradlblSpValue.Text = Math.Round(GuiCommon.crxPwaData.C_Sp).ToString();
                        PWAClinicalReportData.RptSliderPanel = false;
                    }
                }
                else
                {
                    guipnlBpMeasurementValues.Visible = true;
                    guipnlSliderControls.Visible = false;
                    guiradlblSpValue.Visible = false;
                    guiradlblSpNotCalc.Visible = true;
                    PWAClinicalReportData.RptSliderPanel = false;
                }

                if (GuiCommon.crxPwaData.C_Ap != GuiConstants.DefaultValue)
                {
                    if (GuiCommon.bizPwaobject.GetAPRange(PWA_MEASURE_TYPE.PWA_RADIAL, ref high, ref low))
                    {
                        guipnlBpMeasurementValues.Visible = false;
                        guipnlSliderControls.Visible = true;
                        double[] temp = setSliderMinMaxForXAxis(new double[] { GuiCommon.crxPwaData.C_Ap, low, high }, guiradlblApMaxRangeText, guiradlblApMinRangeText);
                        ShowApTracker(((float)temp[0]), ((float)temp[1]), GuiCommon.crxPwaData.C_Ap, low, high, true);
                        PWAClinicalReportData.RptSliderPanel = true;
                    }
                    else
                    {
                        guipnlBpMeasurementValues.Visible = true;
                        guipnlSliderControls.Visible = false;
                        guiradlblApValue.Visible = true;
                        guiradlblApNotCalc.Visible = false;
                        guiradlblApValue.Text = Math.Round(GuiCommon.crxPwaData.C_Ap).ToString();
                        PWAClinicalReportData.RptSliderPanel = false;
                    }
                }
                else
                {
                    guipnlBpMeasurementValues.Visible = true;
                    guipnlSliderControls.Visible = false;
                    guiradlblApValue.Visible = false;
                    guiradlblApNotCalc.Visible = true;
                    PWAClinicalReportData.RptSliderPanel = false;
                }

                float centralPp;
                centralPp = GuiCommon.crxPwaData.C_Sp - GuiCommon.crxPwaData.C_Dp;

                if (centralPp != GuiConstants.DefaultValue)
                {
                    if (GuiCommon.bizPwaobject.GetPPRange(PWA_MEASURE_TYPE.PWA_RADIAL, ref high, ref low))
                    {
                        //guipnlBpMeasurementValues.SendToBack();
                        //guipnlSliderControls.BringToFront();
                        guipnlBpMeasurementValues.Visible = false;
                        guipnlSliderControls.Visible = true;
                        double[] temp = setSliderMinMaxForXAxis(new double[] { centralPp, low, high }, guiradlblPpMaxRangeText, guiradlblPpMinRangeText);
                        ShowPpTracker(((float)temp[0]), ((float)temp[1]), centralPp, low, high, true);
                        PWAClinicalReportData.RptSliderPanel = true;
                    }
                    else
                    {
                        // ShowPpTracker(50, 0, 0, 0, 0, false);
                        //guipnlBpMeasurementValues.BringToFront();
                        //guipnlSliderControls.SendToBack();
                        guipnlBpMeasurementValues.Visible = true;
                        guipnlSliderControls.Visible = false;
                        guiradlblPpValue.Visible = true;
                        guiradlblPpNotCalc.Visible = false;
                        guiradlblPpValue.Text = Math.Round(centralPp).ToString();
                        PWAClinicalReportData.RptSliderPanel = false;
                    }
                }
                else
                {
                    guipnlBpMeasurementValues.Visible = true;
                    guipnlSliderControls.Visible = false;
                    guiradlblPpValue.Visible = false;
                    guiradlblPpNotCalc.Visible = true;
                    PWAClinicalReportData.RptSliderPanel = false;
                }
            }
            catch (Exception ex)
            {
                GUIExceptionHandler.HandleException(ex, this);
            }
        }

        /** This method to Show SP Slider
        * */
        private void ShowSpTracker(float spMaxValue, float spMinValue, float spValue, float spGoodRangeMin, float spGoodRangeMax, bool visible)
        {
            try
            {
                // Hide/Show Sp Slider Labels
                guilblSPValueText.Visible = visible;
                guilblSPValue.Visible = visible;
                guilblSPGoodMin.Visible = visible;
                guilblSPGoodMinText.Visible = visible;
                guilblSPGoodMaxText.Visible = visible;
                guilblSPGoodMax.Visible = visible;

                if (visible)
                {
                    guilblSPValue.Left = guilblSPSlider.Left + ((int)(Math.Round(spValue) - spMinValue) * (guilblSPSlider.Width / (int)(spMaxValue - spMinValue))) - (guilblSPValue.Width / Convert.ToInt32(GuiCommon.NumericValue.Two));
                    guilblSPGoodMin.Left = guilblSPSlider.Left + ((int)(spGoodRangeMin - spMinValue) * (guilblSPSlider.Width / (int)(spMaxValue - spMinValue))) - (guilblSPGoodMin.Width / Convert.ToInt32(GuiCommon.NumericValue.Two));
                    guilblSPGoodMinText.Left = guilblSPGoodMin.Left - (guilblSPGoodMinText.Width / Convert.ToInt32(GuiCommon.NumericValue.Three));
                    guilblSPGoodMax.Left = guilblSPSlider.Left + ((int)(spGoodRangeMax - spMinValue) * (guilblSPSlider.Width / (int)(spMaxValue - spMinValue))) - (guilblSPGoodMax.Width / Convert.ToInt32(GuiCommon.NumericValue.Two));

                    guilblSPValueText.Left = guilblSPValue.Left - (guilblSPValueText.Width / Convert.ToInt32(GuiCommon.NumericValue.Three)) + Convert.ToInt32(GuiCommon.NumericValue.Two);
                    guilblSPGoodMaxText.Left = guilblSPGoodMax.Left - (guilblSPGoodMaxText.Width / Convert.ToInt32(GuiCommon.NumericValue.Three));

                    guilblSPValueText.Text = Math.Round(spValue).ToString();
                    guilblSPGoodMaxText.Text = spGoodRangeMax.ToString();
                    guilblSPGoodMinText.Text = spGoodRangeMin.ToString();

                    if ((Math.Round(spValue) < spGoodRangeMin) || (Math.Round(spValue) > spGoodRangeMax))
                    {
                        guilblSPValue.BackColor = Color.Red;
                    }
                    else
                    {
                        guilblSPValue.BackColor = Color.LimeGreen;
                    }
                }
            }
            catch (Exception ex)
            {
                throw (ex);
            }

            // SP Tracker: End
        }

        /** This method to Show DP Slider
        * */
        private void ShowPpTracker(float ppMaxValue, float ppMinValue, float ppValue, float ppGoodRangeMin, float ppGoodRangeMax, bool visible)
        {
            try
            {

                // Hide/Show Pp Slider Labels
                guilblPPValueText.Visible = visible;
                guilblPPValue.Visible = visible;
                guilblPPGoodMin.Visible = visible;
                guilblPPGoodMinText.Visible = visible;
                guilblPPGoodMaxText.Visible = visible;
                guilblPPGoodMax.Visible = visible;

                if (visible)
                {
                    guilblPPValue.Left = guilblPPSlider.Left + ((int)(Math.Round(ppValue) - ppMinValue) * (guilblPPSlider.Width / (int)(ppMaxValue - ppMinValue))) - (guilblPPValue.Width / Convert.ToInt32(GuiCommon.NumericValue.Two));

                    guilblPPGoodMin.Left = guilblPPSlider.Left + ((int)(ppGoodRangeMin - ppMinValue) * (guilblPPSlider.Width / (int)(ppMaxValue - ppMinValue))) - (guilblPPGoodMin.Width / Convert.ToInt32(GuiCommon.NumericValue.Two));
                    guilblPPGoodMax.Left = guilblPPSlider.Left + ((int)(ppGoodRangeMax - ppMinValue) * (guilblPPSlider.Width / (int)(ppMaxValue - ppMinValue))) - (guilblPPGoodMax.Width / Convert.ToInt32(GuiCommon.NumericValue.Two));

                    guilblPPValueText.Left = guilblPPValue.Left - (guilblPPValueText.Width / Convert.ToInt32(GuiCommon.NumericValue.Three)) + Convert.ToInt32(GuiCommon.NumericValue.Three);
                    guilblPPGoodMaxText.Left = guilblPPGoodMax.Left - (guilblPPGoodMaxText.Width / Convert.ToInt32(GuiCommon.NumericValue.Three));
                    guilblPPGoodMinText.Left = guilblPPGoodMin.Left - (guilblPPGoodMinText.Width / Convert.ToInt32(GuiCommon.NumericValue.Three));

                    guilblPPValueText.Text = Math.Round(ppValue).ToString();
                    guilblPPGoodMaxText.Text = ppGoodRangeMax.ToString();
                    guilblPPGoodMinText.Text = ppGoodRangeMin.ToString();

                    if ((Math.Round(ppValue) < ppGoodRangeMin) || (Math.Round(ppValue) > ppGoodRangeMax))
                    {
                        guilblPPValue.BackColor = Color.Red;
                    }
                    else
                    {
                        guilblPPValue.BackColor = Color.LimeGreen;
                    }
                }
            }
            catch (Exception ex)
            {
                throw ex;
            }
            // PP Tracker: End
        }

        /** This method to Show Aix Slider
        * */
        private void ShowAixTracker(float maxValue, float minValue, float value, float goodRangeMin, float goodRangeMax, bool visible)
        {
            try
            {
                // Hide/Show Aix Slider Labels
                guilblAIxValueText.Visible = visible;
                guilblAIxValue.Visible = visible;
                guilblAIxGoodMin.Visible = visible;
                guilblAIxGoodMinText.Visible = visible;
                guilblAIxGoodMaxText.Visible = visible;
                guilblAIxGoodMax.Visible = visible; 

                if (visible)
                {
                    guilblAIxValue.Left = guilblAIxSlider.Left + (int)((Math.Round(value) - minValue) * (guilblAIxSlider.Width / (int)(maxValue - minValue))) - (guilblAIxValue.Width / Convert.ToInt32(GuiCommon.NumericValue.Two));
                    guilblAIxGoodMin.Left = guilblAIxSlider.Left + (int)((goodRangeMin - minValue) * (guilblAIxSlider.Width / (int)(maxValue - minValue))) - (guilblAIxGoodMin.Width / Convert.ToInt32(GuiCommon.NumericValue.Two));

                    guilblAIxGoodMax.Left = guilblAIxSlider.Left + (int)((goodRangeMax - minValue) * (guilblAIxSlider.Width / (int)(maxValue - minValue))) - (guilblAIxGoodMax.Width / Convert.ToInt32(GuiCommon.NumericValue.Two));

                    guilblAIxValueText.Left = guilblAIxValue.Left - (guilblAIxValueText.Width / Convert.ToInt32(GuiCommon.NumericValue.Three)) + Convert.ToInt32(GuiCommon.NumericValue.Four);
                    guilblAIxGoodMaxText.Left = guilblAIxGoodMax.Left - (guilblAIxGoodMaxText.Width / Convert.ToInt32(GuiCommon.NumericValue.Three));
                    guilblAIxGoodMinText.Left = guilblAIxGoodMin.Left - (guilblAIxGoodMinText.Width / Convert.ToInt32(GuiCommon.NumericValue.Three));

                    guilblAIxValueText.Text = Math.Round(value).ToString();
                    guilblAIxGoodMaxText.Text = goodRangeMax.ToString();
                    guilblAIxGoodMinText.Text = goodRangeMin.ToString();

                    if ((Math.Round(value) < goodRangeMin) || (Math.Round(value) > goodRangeMax))
                    {
                        guilblAIxValue.BackColor = Color.Red;
                    }
                    else
                    {
                        guilblAIxValue.BackColor = Color.LimeGreen;
                    }
                }
            }
            catch (Exception ex)
            {
                throw (ex);
            }

            // AIx Tracker: End
        }

        /** This method to Show AP Slider
        * */
        private void ShowApTracker(float apMaxValue, float apMinValue, float apValue, float apGoodRangeMin, float apGoodRangeMax, bool visible)
        {
            try
            {
                // Hide/Show Ap Slider Labels
                guilblAPValueText.Visible = visible;
                guilblAPValue.Visible = visible;
                guilblAPGoodMin.Visible = visible;
                guilblAPGoodMinText.Visible = visible;
                guilblAPGoodMaxText.Visible = visible;
                guilblAPGoodMax.Visible = visible;

                if (visible)
                {
                    guilblAPValue.Left = (guilblAPSlider.Left + ((int)(Math.Round(apValue) - apMinValue) * (guilblAPSlider.Width / (int)(apMaxValue - apMinValue)))) - (guilblAPValue.Width / Convert.ToInt32(GuiCommon.NumericValue.Two));
                    guilblAPGoodMin.Left = (guilblAPSlider.Left + ((int)(apGoodRangeMin - apMinValue) * (guilblAPSlider.Width / (int)(apMaxValue - apMinValue)))) - (guilblAPGoodMin.Width / Convert.ToInt32(GuiCommon.NumericValue.Two));

                    guilblAPGoodMax.Left = guilblAPSlider.Left + ((int)(apGoodRangeMax - apMinValue) * (guilblAPSlider.Width / (int)(apMaxValue - apMinValue))) - (guilblAIxGoodMax.Width / Convert.ToInt32(GuiCommon.NumericValue.Two));

                    guilblAPValueText.Left = guilblAPValue.Left - (guilblAPValueText.Width / Convert.ToInt32(GuiCommon.NumericValue.Three)) + Convert.ToInt32(GuiCommon.NumericValue.Two);
                    guilblAPGoodMaxText.Left = guilblAPGoodMax.Left - (guilblAPGoodMaxText.Width / Convert.ToInt32(GuiCommon.NumericValue.Three));
                    guilblAPGoodMinText.Left = guilblAPGoodMin.Left - (guilblAPGoodMinText.Width / Convert.ToInt32(GuiCommon.NumericValue.Three));

                    guilblAPValueText.Text = Math.Round(apValue).ToString();
                    guilblAPGoodMaxText.Text = apGoodRangeMax.ToString();
                    guilblAPGoodMinText.Text = apGoodRangeMin.ToString();

                    if ((Math.Round(apValue) < apGoodRangeMin) || (Math.Round(apValue) > apGoodRangeMax))
                    {
                        guilblAPValue.BackColor = Color.Red;
                    }
                    else
                    {
                        guilblAPValue.BackColor = Color.LimeGreen;
                    }
                }
            }
            catch (Exception ex)
            {
                throw (ex);
            }

            // AP Tracker: End
        }

        /**This method plots Average Aortic Pulse graph
         * */   
        private void PlotCentralPressueWaveform()
        {
            try
            {
                // set y axis (normal range values from Bizsession object in float)
                float[] avgAorticPulse = GuiCommon.crxPwaData.C_AV_PULSE;
                float[] avgTypicalAorticPulse = GuiCommon.crxPwaData.C_Typical;

                for (int i = Convert.ToInt32(GuiCommon.NumericValue.Zero); i < avgAorticPulse.Length; i++)
                {
                    if (avgAorticPulse[i] == Convert.ToInt32(GuiCommon.NumericValue.Zero))
                    {
                        break;
                    }
                    else
                    {
                        guichartPWAReport.Series[0].Points.AddXY(averageAorticXAxisInterval * i, avgAorticPulse[i]);
                    }
                }

                guichartPWAReport.Series[1].Points.Clear();

                for (int i = Convert.ToInt32(GuiCommon.NumericValue.Zero); i < avgTypicalAorticPulse.Length; i++)
                {
                    if (avgTypicalAorticPulse[i] == Convert.ToInt32(GuiCommon.NumericValue.Zero))
                    {
                        break;
                    }
                    else
                    {
                        guichartPWAReport.Series[1].Points.AddXY(averageAorticXAxisInterval * i, avgTypicalAorticPulse[i]);
                    }
                }

                // Setting minimum and maximum of Y-axis for Chart
                float[] tempFloatArray = new float[avgAorticPulse.Length + avgTypicalAorticPulse.Length];

                Array.Copy(avgAorticPulse, tempFloatArray, avgAorticPulse.Length);
                Array.Copy(avgTypicalAorticPulse, Convert.ToInt32(GuiCommon.NumericValue.Zero), tempFloatArray, avgAorticPulse.Length, avgTypicalAorticPulse.Length);
                Array.Sort(tempFloatArray);
                for (int i = Convert.ToInt32(GuiCommon.NumericValue.Zero); i < tempFloatArray.Length; i++)
                {
                    if (tempFloatArray[i] == Convert.ToInt32(GuiCommon.NumericValue.Zero))
                    {
                    }
                    else
                    {
                        double value = Math.Round(tempFloatArray[i] * GuiConstants.ChartAreaMinimumY, MidpointRounding.ToEven);
                        value = ((int)Math.Round(value / Convert.ToInt32(GuiCommon.NumericValue.Ten))) * Convert.ToInt32(GuiCommon.NumericValue.Ten);
                        guichartPWAReport.ChartAreas[0].AxisY.Minimum = value - Convert.ToInt32(GuiCommon.NumericValue.Ten);
                        break;
                    }
                }

                double valueMax = Math.Round((tempFloatArray[tempFloatArray.Length - Convert.ToInt32(GuiCommon.NumericValue.One)]) * GuiConstants.ChartAreaMaximumY, MidpointRounding.ToEven);
                valueMax = ((int)Math.Round(valueMax / Convert.ToInt32(GuiCommon.NumericValue.Ten))) * Convert.ToInt32(GuiCommon.NumericValue.Ten);
                guichartPWAReport.ChartAreas[0].AxisY.Maximum = valueMax + Convert.ToInt32(GuiCommon.NumericValue.Ten);
                guichartPWAReport.Invalidate();
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
            }
            catch (Exception ex)
            {
                GUIExceptionHandler.HandleException(ex, this);
            }
        }

        /** This method to show Raw signals on the PWA preview
        * */
        private void PlotRawSignals()
        {
            try
            {
                guichrtCrawSignals.ChartAreas[0].BackColor = Color.Transparent;
                guichrtPrawSignals.ChartAreas[0].BackColor = Color.Transparent;

                float[] cRawSignals = ResetNonZeroSizeofArray(GuiCommon.crxPwaData.C_RAW_SIGNALS);
                short[] cRawSignalsOnset = ResetSizeofArray(GuiCommon.crxPwaData.C_ONSETS);
                pRawSignals = ResetNonZeroSizeofArray(GuiCommon.crxPwaCuffData.P_RAW_SIGNALS);
                pRawSignalsOnset = ResetSizeofArray(GuiCommon.crxPwaCuffData.P_ONSETS);

                PWACommonReportData.RptNumberOfWaveformsValue = (pRawSignalsOnset.Length - Convert.ToInt32(GuiCommon.NumericValue.One)).ToString();

                SetRawChartProperty(cRawSignals, pRawSignals);

                PlotcRawSignals(cRawSignals, cRawSignalsOnset);

                PlotpRawSignals(pRawSignals, pRawSignalsOnset);
            }
            catch (Exception ex)
            {
                GUIExceptionHandler.HandleException(ex, this);
            }
        }

        /** This method to set the Raw chart properties
       * */
        private void SetRawChartProperty(float[] cInputRawSignals, float[] pInputRawSignals)
        {
            try
            {
                float[] sortedpRawSignals = new float[pInputRawSignals.Length];
                for (int i = Convert.ToInt32(GuiCommon.NumericValue.Zero); i < pInputRawSignals.Length; i++)
                {
                    sortedpRawSignals[i] = pInputRawSignals[i];
                }

                Array.Sort(sortedpRawSignals);

                float[] sortedcRawSignals = new float[cInputRawSignals.Length];
                for (int i = Convert.ToInt32(GuiCommon.NumericValue.Zero); i < cInputRawSignals.Length; i++)
                {
                    sortedcRawSignals[i] = cInputRawSignals[i];
                }

                Array.Sort(sortedcRawSignals);

                guichrtPrawSignals.ChartAreas.Clear();
                guichrtPrawSignals.ChartAreas.Add(new ChartArea("area"));
                guichrtPrawSignals.ChartAreas["area"].AxisY.Enabled = AxisEnabled.False;
                guichrtPrawSignals.ChartAreas["area"].AxisX.Enabled = AxisEnabled.False;
                guichrtPrawSignals.ChartAreas["area"].AxisX.MajorGrid.Enabled = false;

                guichrtCrawSignals.ChartAreas.Clear();
                guichrtCrawSignals.ChartAreas.Add(new ChartArea("area"));
                guichrtCrawSignals.ChartAreas["area"].AxisY.Enabled = AxisEnabled.False;
                guichrtCrawSignals.ChartAreas["area"].AxisX.Enabled = AxisEnabled.False;
                guichrtCrawSignals.ChartAreas["area"].AxisX.MajorGrid.Enabled = false;

                // set y axis
                guichrtPrawSignals.ChartAreas["area"].AxisY.Minimum = sortedpRawSignals[0];
                guichrtPrawSignals.ChartAreas["area"].AxisY.Maximum = sortedpRawSignals[sortedpRawSignals.Length - Convert.ToInt32(GuiCommon.NumericValue.One)];
                guichrtPrawSignals.ChartAreas["area"].AxisY.Interval = Convert.ToInt32(GuiCommon.NumericValue.One);

                guichrtCrawSignals.ChartAreas["area"].AxisY.Minimum = sortedcRawSignals[0];
                guichrtCrawSignals.ChartAreas["area"].AxisY.Maximum = sortedcRawSignals[sortedcRawSignals.Length - Convert.ToInt32(GuiCommon.NumericValue.One)];
                guichrtCrawSignals.ChartAreas["area"].AxisY.Interval = Convert.ToInt32(GuiCommon.NumericValue.One);

                // set x axis
                guichrtPrawSignals.ChartAreas["area"].AxisX.Minimum = Convert.ToInt32(GuiCommon.NumericValue.Zero);
                guichrtPrawSignals.ChartAreas["area"].AxisX.Maximum = pInputRawSignals.Length; // 608;
                guichrtPrawSignals.ChartAreas["area"].AxisX.Interval = Convert.ToInt32(GuiCommon.NumericValue.One);

                guichrtCrawSignals.ChartAreas["area"].AxisX.Minimum = Convert.ToInt32(GuiCommon.NumericValue.Zero);
                guichrtCrawSignals.ChartAreas["area"].AxisX.Maximum = cInputRawSignals.Length;
                guichrtCrawSignals.ChartAreas["area"].AxisX.Interval = Convert.ToInt32(GuiCommon.NumericValue.One);

                // initialize series,chartype,add points to series and finally add series to chart.
                guichrtPrawSignals.Series.Clear();
                guichrtCrawSignals.Series.Clear();
            }
            catch (Exception ex)
            {
                GUIExceptionHandler.HandleException(ex, this);
            }
        }

        /** This method to draw C_RAW_SIGNALS data on the form
       * */
        private void PlotcRawSignals(float[] cRawSignals, short[] cRawSignalsOnset)
        {
            try
            {
                Series cRawSignalsSeries = new Series
                {
                    ChartType = SeriesChartType.FastLine,
                    Color = Color.Black,
                    XValueType = ChartValueType.Auto,
                    YValuesPerPoint = Convert.ToInt32(GuiCommon.NumericValue.One),
                    ChartArea = "area"
                };

                Series cRawSignalsSeriesOne = new Series
                {
                    ChartType = SeriesChartType.Point,
                    Color = Color.Green
                };

                Series cRawSignalsSeriesTwo = new Series
                {
                    ChartType = SeriesChartType.Point,
                    Color = Color.Red
                };

                cRawSignalsSeries.Points.Clear();

                Hashtable cRawSignalsTable = new Hashtable();
                cRawSignalsSeriesOne.Points.Clear();
                cRawSignalsSeriesTwo.Points.Clear();

                for (int i = Convert.ToInt32(GuiCommon.NumericValue.Zero); i < cRawSignals.Length; i++)
                {
                    cRawSignalsSeries.Points.AddXY(i, cRawSignals[i]);
                    cRawSignalsTable[i] = cRawSignals[i];
                }

                for (int j = Convert.ToInt32(GuiCommon.NumericValue.Zero); j < cRawSignalsOnset.Length; j++)
                {
                    int valueToPLot = int.Parse(Math.Round(double.Parse(cRawSignalsOnset[j].ToString(), CrxCommon.nCI), MidpointRounding.ToEven).ToString());
                    int valueToPLot1 = Math.Abs(valueToPLot);

                    if (valueToPLot < Convert.ToInt32(GuiCommon.NumericValue.Zero))
                    {
                        cRawSignalsSeriesTwo.Points.AddXY(valueToPLot1, cRawSignalsTable[valueToPLot1]);
                        cRawSignalsSeriesTwo.Points[cRawSignalsSeriesTwo.Points.Count - Convert.ToInt32(GuiCommon.NumericValue.One)].MarkerStyle = MarkerStyle.Circle;
                    }
                    else
                    {
                        cRawSignalsSeriesOne.Points.AddXY(valueToPLot1, cRawSignalsTable[valueToPLot1]);
                        cRawSignalsSeriesOne.Points[cRawSignalsSeriesOne.Points.Count - Convert.ToInt32(GuiCommon.NumericValue.One)].MarkerStyle = MarkerStyle.Circle;
                    }
                }

                guichrtCrawSignals.Series.Add(cRawSignalsSeries);
                guichrtCrawSignals.Series.Add(cRawSignalsSeriesOne);
                guichrtCrawSignals.Series.Add(cRawSignalsSeriesTwo);
                guichrtCrawSignals.Invalidate();
            }
            catch (Exception ex)
            {
                GUIExceptionHandler.HandleException(ex, this);
            }
        }

        /** This method to draw P_RAW_SIGNALS data on the form
      * */
        private void PlotpRawSignals(float[] pRawSignals, short[] pRawSignalsOnset)
        {
            try
            {
                Series pRawSignalsSeries = new Series
                {
                    ChartType = SeriesChartType.FastLine,
                    Color = Color.Black,
                    XValueType = ChartValueType.Auto,
                    YValuesPerPoint = Convert.ToInt32(GuiCommon.NumericValue.One),
                    ChartArea = "area"
                };

                Series pRawSignalsSeriesOne = new Series
                {
                    ChartType = SeriesChartType.Point,
                    Color = Color.Green
                };

                Series pRawSignalsSeriesTwo = new Series
                {
                    ChartType = SeriesChartType.Point,
                    Color = Color.Red
                };

                pRawSignalsSeries.Points.Clear();
                Hashtable pRawSignalsTable = new Hashtable();
                pRawSignalsSeriesOne.Points.Clear();
                pRawSignalsSeriesTwo.Points.Clear();

                for (int i = Convert.ToInt32(GuiCommon.NumericValue.Zero); i < pRawSignals.Length; i++)
                {
                    pRawSignalsSeries.Points.AddXY(i, pRawSignals[i]);
                    pRawSignalsTable[i] = pRawSignals[i];
                }

                for (int j = Convert.ToInt32(GuiCommon.NumericValue.Zero); j < pRawSignalsOnset.Length; j++)
                {
                    int valueToPLot = int.Parse(Math.Round(double.Parse(pRawSignalsOnset[j].ToString(), CrxCommon.nCI), MidpointRounding.ToEven).ToString());
                    int valueToPLot1 = Math.Abs(valueToPLot);

                    if (valueToPLot < Convert.ToInt32(GuiCommon.NumericValue.Zero))
                    {
                        pRawSignalsSeriesTwo.Points.AddXY(valueToPLot1, pRawSignalsTable[valueToPLot1]);
                        pRawSignalsSeriesTwo.Points[pRawSignalsSeriesTwo.Points.Count - Convert.ToInt32(GuiCommon.NumericValue.One)].MarkerStyle = MarkerStyle.Circle;
                    }
                    else
                    {
                        pRawSignalsSeriesOne.Points.AddXY(valueToPLot1, pRawSignalsTable[valueToPLot1]);
                        pRawSignalsSeriesOne.Points[pRawSignalsSeriesOne.Points.Count - Convert.ToInt32(GuiCommon.NumericValue.One)].MarkerStyle = MarkerStyle.Circle;
                    }
                }

                guichrtPrawSignals.Series.Add(pRawSignalsSeries);
                guichrtPrawSignals.Series.Add(pRawSignalsSeriesOne);
                guichrtPrawSignals.Series.Add(pRawSignalsSeriesTwo);
                guichrtPrawSignals.Invalidate();
            }
            catch (Exception ex)
            {
                GUIExceptionHandler.HandleException(ex, this);
            }
        }

        /** This method to Reset Non-Zero array data 
      * */
        private float[] ResetNonZeroSizeofArray(float[] rawSignalArr)
        {
            float[] tempArr;
            try
            {
                int arrLen = Convert.ToInt32(GuiCommon.NumericValue.Zero);
                for (arrLen = Convert.ToInt32(GuiCommon.NumericValue.Zero); arrLen < rawSignalArr.Length; arrLen++)
                {
                    if (rawSignalArr[arrLen] == 0.0)
                    {
                        break;
                    }
                }

                tempArr = new float[arrLen];

                for (int j = Convert.ToInt32(GuiCommon.NumericValue.Zero); j < arrLen; j++)
                {
                    tempArr[j] = rawSignalArr[j];
                }
            }
            catch (Exception ex)
            {
                throw (ex);
            }
            return tempArr;
        }

        /** This method to Reset Size array
      * */
        private short[] ResetSizeofArray(short[] rawSignalArr)
        {
            short[] tempArr;
            try
            {
                int arrLen = Convert.ToInt32(GuiCommon.NumericValue.Zero);
                for (arrLen = Convert.ToInt32(GuiCommon.NumericValue.Zero); arrLen < rawSignalArr.Length; arrLen++)
                {
                    if (rawSignalArr[arrLen] < Convert.ToInt32(GuiCommon.NumericValue.Zero))
                    {
                        break;
                    }
                }

                tempArr = new short[arrLen];

                for (int j = Convert.ToInt32(GuiCommon.NumericValue.Zero); j < arrLen; j++)
                {
                    tempArr[j] = rawSignalArr[j];
                }
            }
            catch (Exception ex)
            {
                throw (ex);
            }
            return tempArr;
        }

        /** This method to Plot the multiple P_RAW_SIGNALS on the Clinical report
      * */
        private void PlotSinglePRawSignalPulse()
        {
            try
            {
                float[] sortedpRawSignals = new float[pRawSignals.Length];
                for (int i = Convert.ToInt32(GuiCommon.NumericValue.Zero); i < pRawSignals.Length; i++)
                {
                    sortedpRawSignals[i] = pRawSignals[i];
                }

                Array.Sort(sortedpRawSignals);

                chartSinglePRawSignal.ChartAreas.Clear();
                chartSinglePRawSignal.ChartAreas.Add(new ChartArea("area"));
                chartSinglePRawSignal.ChartAreas["area"].AxisY.Enabled = AxisEnabled.False;
                chartSinglePRawSignal.ChartAreas["area"].AxisX.Enabled = AxisEnabled.False;
                chartSinglePRawSignal.ChartAreas["area"].AxisX.MajorGrid.Enabled = false;

                // set y axis
                chartSinglePRawSignal.ChartAreas["area"].AxisY.Minimum = sortedpRawSignals[0];
                chartSinglePRawSignal.ChartAreas["area"].AxisY.Maximum = sortedpRawSignals[sortedpRawSignals.Length - Convert.ToInt32(GuiCommon.NumericValue.One)];
                chartSinglePRawSignal.ChartAreas["area"].AxisY.Interval = Convert.ToInt32(GuiCommon.NumericValue.One);

                // initialize series,chartype,add points to series and finally add series to chart.
                chartSinglePRawSignal.Series.Clear();

                int fixIndexForSinglePulse = pRawSignalsOnset[0];
                for (int i = Convert.ToInt32(GuiCommon.NumericValue.Zero); i < pRawSignalsOnset.Length - Convert.ToInt32(GuiCommon.NumericValue.One); i++)
                {
                    singlePRawSignalPulse = new Series
                    {
                        ChartType = SeriesChartType.FastLine,
                        Color = Color.Black,
                        XValueType = ChartValueType.Auto,
                        YValuesPerPoint = Convert.ToInt32(GuiCommon.NumericValue.One),
                    };

                    singlePRawSignalPulse.Points.Clear();

                    int startIndexForSinglePulse = pRawSignalsOnset[i];

                    int endIndexForSinglePulse = pRawSignalsOnset[i + Convert.ToInt32(GuiCommon.NumericValue.One)];
                    for (int k = Convert.ToInt32(GuiCommon.NumericValue.Zero), j = startIndexForSinglePulse; j < endIndexForSinglePulse; j++, k++)
                    {
                        singlePRawSignalPulse.Points.AddXY(fixIndexForSinglePulse + k, pRawSignals[j]);
                    }

                    chartSinglePRawSignal.Series.Add(singlePRawSignalPulse);
                }

                chartSinglePRawSignal.Invalidate();
            }
            catch (Exception ex)
            {
                GUIExceptionHandler.HandleException(ex, this);
            }
        }

        /** This method is used to set the maximum and minimum value for X Axis on Slider
       * */
        // Any exception will be handled by DisplayClinicalParameterSliders Function
        private double[] setSliderMinMaxForXAxis(double[] data, RadLabel labelMax, RadLabel labelMin)
        {
            double max = 0.0;
            double min = 0.0;
            Array.Sort(data);
            double value = Math.Round(data[0] * GuiConstants.ChartAreaMinimumY, MidpointRounding.ToEven);

            value = ((int)Math.Round(value / Convert.ToInt32(GuiCommon.NumericValue.Ten))) * Convert.ToInt32(GuiCommon.NumericValue.Ten);

            if ((value == Convert.ToInt32(GuiCommon.NumericValue.Zero)) || (value < Convert.ToInt32(GuiCommon.NumericValue.Zero) && value > data[0]))
            {
                value = Math.Round(data[0]);
            }

            min = value - Convert.ToInt32(GuiCommon.NumericValue.Five);

            labelMin.Text = min.ToString();

            value = Math.Round((data[data.Length - Convert.ToInt32(GuiCommon.NumericValue.One)]) * GuiConstants.ChartAreaMaximumY, MidpointRounding.ToEven);

            value = ((int)Math.Round(value / Convert.ToInt32(GuiCommon.NumericValue.Ten))) * Convert.ToInt32(GuiCommon.NumericValue.Ten);

            max = value + Convert.ToInt32(GuiCommon.NumericValue.Five);

            labelMax.Text = max.ToString();

            return new double[] { max, min };
        }
    }
}
