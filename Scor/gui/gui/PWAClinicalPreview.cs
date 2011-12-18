
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
                SetTextForLabels();
                PopulateCentralClinicalParameters();
                PlotCentralPressueWaveform();
                PlotRawSignals();
                PlotSinglePRawSignalPulse();               
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

        /** This method to Populate Central Clinical Parameters
        * */
        private void PopulateCentralClinicalParameters()
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
                // crxPwaData.C_Agph = 9999;
                if (GuiCommon.crxPwaData.C_Agph != GuiConstants.DefaultValue)
                {
                    if (GuiCommon.bizPwaobject.GetAixRange(PWA_MEASURE_TYPE.PWA_RADIAL, ref high, ref low))
                    {
                        double[] temp = setSliderMinMaxForXAxis(new double[] { GuiCommon.crxPwaData.C_Agph, low, high }, guiradlblAixMaxRangeText, guiradlblAixMinRangeText);
                        ShowAixTracker(((float)temp[0]), ((float)temp[1]), GuiCommon.crxPwaData.C_Agph, low, high, true);
                    }
                    else
                    {
                        ShowAixTracker(0, 0, 0, 0, 0, false);
                    }
                }
                else
                {
                    ShowAixTracker(0, 0, 0, 0, 0, false);
                }
            }
            else
            {
                // GuiCommon.bizPwaobject.AGPH_HR75 = 9999;
                if (GuiCommon.bizPwaobject.AGPH_HR75 != GuiConstants.DefaultValue)
                {
                    if (GuiCommon.bizPwaobject.GetAixhr75Range(PWA_MEASURE_TYPE.PWA_RADIAL, ref high, ref low))
                    {
                        double[] temp = setSliderMinMaxForXAxis(new double[] { GuiCommon.bizPwaobject.AGPH_HR75, low, high }, guiradlblAixMaxRangeText, guiradlblAixMinRangeText);
                        ShowAixTracker(((float)temp[0]), ((float)temp[1]), GuiCommon.bizPwaobject.AGPH_HR75, low, high, true);
                    }
                    else
                    {
                        ShowAixTracker(0, 0, 0, 0, 0, false);
                    }
                }
                else
                {
                    ShowAixTracker(0, 0, 0, 0, 0, false);
                }
            }

            // crxPwaData.C_Sp = 9999;
            if (GuiCommon.crxPwaData.C_Sp != GuiConstants.DefaultValue)
            {
                if (GuiCommon.bizPwaobject.GetSPRange(PWA_MEASURE_TYPE.PWA_RADIAL, ref high, ref low))
                {
                    double[] temp = setSliderMinMaxForXAxis(new double[] { GuiCommon.crxPwaData.C_Sp, low, high }, guiradlblSpMaxRangeText, guiradlblSpMinRangeText);
                    ShowSpTracker(((float)temp[0]), ((float)temp[1]), GuiCommon.crxPwaData.C_Sp, low, high, true);
                }
                else
                {
                    ShowSpTracker(0, 0, 0, 0, 0, false);
                }
            }
            else
            {
                ShowSpTracker(0, 0, 0, 0, 0, false);
            }

            // crxPwaData.C_Ap = 9999;
            if (GuiCommon.crxPwaData.C_Ap != GuiConstants.DefaultValue)
            {
                if (GuiCommon.bizPwaobject.GetAPRange(PWA_MEASURE_TYPE.PWA_RADIAL, ref high, ref low))
                {
                    double[] temp = setSliderMinMaxForXAxis(new double[] { GuiCommon.crxPwaData.C_Ap, low, high }, guiradlblApMaxRangeText, guiradlblApMinRangeText);
                    ShowApTracker(((float)temp[0]), ((float)temp[1]), GuiCommon.crxPwaData.C_Ap, low, high, true);
                }
                else
                {
                    ShowApTracker(0, 0, 0, 0, 0, false);
                }
            }
            else
            {
                ShowApTracker(0, 0, 0, 0, 0, false);
            }

            float centralPp;
            centralPp = GuiCommon.crxPwaData.C_Sp - GuiCommon.crxPwaData.C_Dp;

            // centralPp = 9999;
            if (centralPp != GuiConstants.DefaultValue)
            {
                if (GuiCommon.bizPwaobject.GetPPRange(PWA_MEASURE_TYPE.PWA_RADIAL, ref high, ref low))
                {
                    double[] temp = setSliderMinMaxForXAxis(new double[] { centralPp, low, high }, guiradlblPpMaxRangeText, guiradlblPpMinRangeText);
                    ShowPpTracker(((float)temp[0]), ((float)temp[1]), centralPp, low, high, true);
                }
                else
                {
                    ShowPpTracker(50, 0, 0, 0, 0, false);
                }
            }
            else
            {
                ShowPpTracker(50, 0, 0, 0, 0, false);
            }

            // guipnlPWAReport.Refresh();
        }

        /** This method to Show SP Slider
        * */
        private void ShowSpTracker(float spMaxValue, float spMinValue, float spValue, float spGoodRangeMin, float spGoodRangeMax, bool visible)
        {
            // Hide/Show Sp Slider Labels
            guilblSPValueText.Visible = visible;
            guilblSPValue.Visible = visible;
            guilblSPGoodMin.Visible = visible;
            guilblSPGoodMinText.Visible = visible;
            guilblSPGoodMaxText.Visible = visible;
            guilblSPGoodMax.Visible = visible;
            guiradlblSpMaxRange.Visible = visible;
            guiradlblSpMinRange.Visible = visible;
            guiradlblSpMaxRangeText.Visible = visible;
            guiradlblSpMinRangeText.Visible = visible;
            guiradlblSpNotCalc.Visible = !visible;

            if (visible)
            {
                guilblSPValue.Left = guilblSPSlider.Left + ((int)(Math.Round(spValue) - spMinValue) * (guilblSPSlider.Width / (int)(spMaxValue - spMinValue))) - (guilblSPValue.Width / 2);
                guilblSPGoodMin.Left = guilblSPSlider.Left + ((int)(spGoodRangeMin - spMinValue) * (guilblSPSlider.Width / (int)(spMaxValue - spMinValue))) - (guilblSPGoodMin.Width / 2);
                guilblSPGoodMinText.Left = guilblSPGoodMin.Left - (guilblSPGoodMinText.Width / 3);
                guilblSPGoodMax.Left = guilblSPSlider.Left + ((int)(spGoodRangeMax - spMinValue) * (guilblSPSlider.Width / (int)(spMaxValue - spMinValue))) - (guilblSPGoodMax.Width / 2);

                guilblSPValueText.Left = guilblSPValue.Left - (guilblSPValueText.Width / 3) + 2;
                guilblSPGoodMaxText.Left = guilblSPGoodMax.Left - (guilblSPGoodMaxText.Width / 3);

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

            // SP Tracker: End
        }

        /** This method to Show DP Slider
        * */
        private void ShowPpTracker(float ppMaxValue, float ppMinValue, float ppValue, float ppGoodRangeMin, float ppGoodRangeMax, bool visible)
        {
            // Hide/Show Pp Slider Labels
            guilblPPValueText.Visible = visible;
            guilblPPValue.Visible = visible;
            guilblPPGoodMin.Visible = visible;
            guilblPPGoodMinText.Visible = visible;
            guilblPPGoodMaxText.Visible = visible;
            guilblPPGoodMax.Visible = visible;
            guiradlblPpMaxRange.Visible = visible;
            guiradlblPpMinRange.Visible = visible;
            guiradlblPpMinRangeText.Visible = visible;
            guiradlblPpMaxRangeText.Visible = visible;
            guiradlblPpNotCalc.Visible = !visible;

            if (visible)
            {
                guilblPPValue.Left = guilblPPSlider.Left + ((int)(Math.Round(ppValue) - ppMinValue) * (guilblPPSlider.Width / (int)(ppMaxValue - ppMinValue))) - (guilblPPValue.Width / 2);

                guilblPPGoodMin.Left = guilblPPSlider.Left + ((int)(ppGoodRangeMin - ppMinValue) * (guilblPPSlider.Width / (int)(ppMaxValue - ppMinValue))) - (guilblPPGoodMin.Width / 2);
                guilblPPGoodMax.Left = guilblPPSlider.Left + ((int)(ppGoodRangeMax - ppMinValue) * (guilblPPSlider.Width / (int)(ppMaxValue - ppMinValue))) - (guilblPPGoodMax.Width / 2);

                guilblPPValueText.Left = guilblPPValue.Left - (guilblPPValueText.Width / 3) + 3;
                guilblPPGoodMaxText.Left = guilblPPGoodMax.Left - (guilblPPGoodMaxText.Width / 3);
                guilblPPGoodMinText.Left = guilblPPGoodMin.Left - (guilblPPGoodMinText.Width / 3);

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

            // PP Tracker: End
        }

        /** This method to Show Aix Slider
        * */
        private void ShowAixTracker(float maxValue, float minValue, float value, float goodRangeMin, float goodRangeMax, bool visible)
        {
            // Hide/Show Aix Slider Labels
            guilblAIxValueText.Visible = visible;
            guilblAIxValue.Visible = visible;
            guilblAIxGoodMin.Visible = visible;
            guilblAIxGoodMinText.Visible = visible;
            guilblAIxGoodMaxText.Visible = visible;
            guilblAIxGoodMax.Visible = visible;
            guiradlblAixMaxRange.Visible = visible;
            guiradlblAixMinRange.Visible = visible;
            guiradlblAixMinRangeText.Visible = visible;
            guiradlblAixMaxRangeText.Visible = visible;
            guiradlblAixNotCalc.Visible = !visible;

            if (visible)
            {
                guilblAIxValue.Left = guilblAIxSlider.Left + (int)((Math.Round(value) - minValue) * (guilblAIxSlider.Width / (int)(maxValue - minValue))) - (guilblAIxValue.Width / 2);
                guilblAIxGoodMin.Left = guilblAIxSlider.Left + (int)((goodRangeMin - minValue) * (guilblAIxSlider.Width / (int)(maxValue - minValue))) - (guilblAIxGoodMin.Width / 2);

                guilblAIxGoodMax.Left = guilblAIxSlider.Left + (int)((goodRangeMax - minValue) * (guilblAIxSlider.Width / (int)(maxValue - minValue))) - (guilblAIxGoodMax.Width / 2);

                guilblAIxValueText.Left = guilblAIxValue.Left - (guilblAIxValueText.Width / 3) + 4;
                guilblAIxGoodMaxText.Left = guilblAIxGoodMax.Left - (guilblAIxGoodMaxText.Width / 3);
                guilblAIxGoodMinText.Left = guilblAIxGoodMin.Left - (guilblAIxGoodMinText.Width / 3);

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

            // AIx Tracker: End
        }

        /** This method to Show AP Slider
        * */
        private void ShowApTracker(float apMaxValue, float apMinValue, float apValue, float apGoodRangeMin, float apGoodRangeMax, bool visible)
        {
            // Hide/Show Ap Slider Labels
            guilblAPValueText.Visible = visible;
            guilblAPValue.Visible = visible;
            guilblAPGoodMin.Visible = visible;
            guilblAPGoodMinText.Visible = visible;
            guilblAPGoodMaxText.Visible = visible;
            guilblAPGoodMax.Visible = visible;
            guiradlblApMaxRange.Visible = visible;
            guiradlblApMinRange.Visible = visible;
            guiradlblApMaxRangeText.Visible = visible;
            guiradlblApMinRangeText.Visible = visible;
            guiradlblApNotCalc.Visible = !visible;
            if (visible)
            {
                guilblAPValue.Left = (guilblAPSlider.Left + ((int)(Math.Round(apValue) - apMinValue) * (guilblAPSlider.Width / (int)(apMaxValue - apMinValue)))) - (guilblAPValue.Width / 2);
                guilblAPGoodMin.Left = (guilblAPSlider.Left + ((int)(apGoodRangeMin - apMinValue) * (guilblAPSlider.Width / (int)(apMaxValue - apMinValue)))) - (guilblAPGoodMin.Width / 2);

                guilblAPGoodMax.Left = guilblAPSlider.Left + ((int)(apGoodRangeMax - apMinValue) * (guilblAPSlider.Width / (int)(apMaxValue - apMinValue))) - (guilblAIxGoodMax.Width / 2);

                guilblAPValueText.Left = guilblAPValue.Left - (guilblAPValueText.Width / 3) + 2;
                guilblAPGoodMaxText.Left = guilblAPGoodMax.Left - (guilblAPGoodMaxText.Width / 3);
                guilblAPGoodMinText.Left = guilblAPGoodMin.Left - (guilblAPGoodMinText.Width / 3);

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

            // AP Tracker: End
        }

        /**This method plots Average Aortic Pulse graph
         * */   
        private void PlotCentralPressueWaveform()
        {
            // set y axis (normal range values from Bizsession object in float)
            float[] avgAorticPulse = GuiCommon.crxPwaData.C_AV_PULSE;
            float[] avgTypicalAorticPulse = GuiCommon.crxPwaData.C_Typical;           

            // initialize series,chartype,add points to series and finally add series to chart.            
            // set display properties for Avg Aortic Pulse graph
            // Series avgAorticPulseActualSeries = new Series
            // {
            //    ChartType = SeriesChartType.Spline,
            //    Color = Color.MediumBlue,
            //    BorderWidth = 2,
            //    Name = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.GuiReportActual),
            // };

            // avgAorticPulseActualSeries.Points.Clear();

            // for (int i = 0; i < avgAorticPulse.Length; i++)
            // {
            //    if (avgAorticPulse[i] == 0)
            //    {
            //        break;
            //    }
            //    else
            //    {
            //        avgAorticPulseActualSeries.Points.AddXY(averageAorticXAxisInterval * i, avgAorticPulse[i]);
            //    }
            // }

            // set properties for series 2 for plotting ideal graph
            // Series avgAorticPulseIdealSeries = new Series
            // {
            //    ChartType = SeriesChartType.Spline,
            //    Color = Color.DimGray,
            //    BorderWidth = 2,
            //    Name = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.GuiReportTypical),
            // };
          
            // avgAorticPulseIdealSeries.Points.Clear();

            // Plot actual waveform.
            // for (int i = 0; i < avgTypicalAorticPulse.Length; i++)
            // {
            //    if (avgTypicalAorticPulse[i] == 0)
            //    {
            //        break;
            //    }
            //    else
            //    {
            //        avgAorticPulseIdealSeries.Points.AddXY(averageAorticXAxisInterval * i, avgTypicalAorticPulse[i]);
            //    }
            // }           
            // guichartPWAReport.Series.Add(avgAorticPulseActualSeries);
            // guichartPWAReport.Series.Add(avgAorticPulseIdealSeries);   
            for (int i = 0; i < avgAorticPulse.Length; i++)
            {
                if (avgAorticPulse[i] == 0)
                {
                    break;
                }
                else
                {
                    guichartPWAReport.Series[0].Points.AddXY(averageAorticXAxisInterval * i, avgAorticPulse[i]);
                }
            }

            guichartPWAReport.Series[1].Points.Clear();

            for (int i = 0; i < avgTypicalAorticPulse.Length; i++)
            {
                if (avgTypicalAorticPulse[i] == 0)
                {
                    break;
                }
                else
                {
                    guichartPWAReport.Series[1].Points.AddXY(averageAorticXAxisInterval * i, avgTypicalAorticPulse[i]);
                }
            }

            //// Setting minimum and maximum of Y-axis for Chart

            float[] tempFloatArray = new float[avgAorticPulse.Length + avgTypicalAorticPulse.Length];

            Array.Copy(avgAorticPulse, tempFloatArray, avgAorticPulse.Length);
            Array.Copy(avgTypicalAorticPulse, 0, tempFloatArray, avgAorticPulse.Length, avgTypicalAorticPulse.Length);
            Array.Sort(tempFloatArray);
            for (int i = 0; i < tempFloatArray.Length; i++)
            {
                if (tempFloatArray[i] == 0)
                {
                }
                else
                {
                    double value = Math.Round(tempFloatArray[i] * GuiConstants.ChartAreaMinimumY, MidpointRounding.ToEven);
                    value = ((int)Math.Round(value / 10)) * 10;
                    guichartPWAReport.ChartAreas[0].AxisY.Minimum = value - 10;
                    break;
                }
            }

            double valueMax = Math.Round((tempFloatArray[tempFloatArray.Length - 1]) * GuiConstants.ChartAreaMaximumY, MidpointRounding.ToEven);
            valueMax = ((int)Math.Round(valueMax / 10)) * 10;
            guichartPWAReport.ChartAreas[0].AxisY.Maximum = valueMax + 10;
            guichartPWAReport.Invalidate();
        }

        /** This method sets text for labels from resource file
         * */
        private void SetTextForLabels()
        {
            CrxConfigManager crxConfig = CrxConfigManager.Instance;
            string defaultImgPath = ConfigurationManager.AppSettings[GuiConstants.AppConfigParams.AtcorImageIcon.ToString()];
            guiPicBoxReportLogo.Image = string.IsNullOrEmpty(crxConfig.GeneralSettings.ReportLogoPath) ? Image.FromFile(defaultImgPath) : Image.FromFile(crxConfig.GeneralSettings.ReportLogoPath);
        }

        /** This method to show Raw signals on the PWA preview
        * */
        private void PlotRawSignals()
        {
            guichrtCrawSignals.ChartAreas[0].BackColor = Color.Transparent;
            guichrtPrawSignals.ChartAreas[0].BackColor = Color.Transparent;

            float[] cRawSignals = ResetNonZeroSizeofArray(GuiCommon.crxPwaData.C_RAW_SIGNALS);
            short[] cRawSignalsOnset = ResetSizeofArray(GuiCommon.crxPwaData.C_ONSETS);
            pRawSignals = ResetNonZeroSizeofArray(GuiCommon.crxPwaCuffData.P_RAW_SIGNALS);
            pRawSignalsOnset = ResetSizeofArray(GuiCommon.crxPwaCuffData.P_ONSETS);
  
            PWACommonReportData.RptNumberOfWaveformsValue = (pRawSignalsOnset.Length - 1).ToString();
            
            SetRawChartProperty(cRawSignals, pRawSignals);

            PlotcRawSignals(cRawSignals, cRawSignalsOnset);

            PlotpRawSignals(pRawSignals, pRawSignalsOnset);    
        }

        /** This method to set the Raw chart properties
       * */
        private void SetRawChartProperty(float[] cInputRawSignals, float[] pInputRawSignals)
        {
            float[] sortedpRawSignals = new float[pInputRawSignals.Length];
            for (int i = 0; i < pInputRawSignals.Length; i++)
            {
                sortedpRawSignals[i] = pInputRawSignals[i];
            }

            Array.Sort(sortedpRawSignals);

            float[] sortedcRawSignals = new float[cInputRawSignals.Length];
            for (int i = 0; i < cInputRawSignals.Length; i++)
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
            guichrtPrawSignals.ChartAreas["area"].AxisY.Maximum = sortedpRawSignals[sortedpRawSignals.Length - 1];
            guichrtPrawSignals.ChartAreas["area"].AxisY.Interval = 1;

            guichrtCrawSignals.ChartAreas["area"].AxisY.Minimum = sortedcRawSignals[0];
            guichrtCrawSignals.ChartAreas["area"].AxisY.Maximum = sortedcRawSignals[sortedcRawSignals.Length - 1];
            guichrtCrawSignals.ChartAreas["area"].AxisY.Interval = 1;

            // set x axis
            guichrtPrawSignals.ChartAreas["area"].AxisX.Minimum = 0;
            guichrtPrawSignals.ChartAreas["area"].AxisX.Maximum = pInputRawSignals.Length; // 608;
            guichrtPrawSignals.ChartAreas["area"].AxisX.Interval = 1;

            guichrtCrawSignals.ChartAreas["area"].AxisX.Minimum = 0;
            guichrtCrawSignals.ChartAreas["area"].AxisX.Maximum = cInputRawSignals.Length;
            guichrtCrawSignals.ChartAreas["area"].AxisX.Interval = 1;

            // initialize series,chartype,add points to series and finally add series to chart.
            guichrtPrawSignals.Series.Clear();
            guichrtCrawSignals.Series.Clear();
        }

        /** This method to draw C_RAW_SIGNALS data on the form
       * */
        private void PlotcRawSignals(float[] cRawSignals, short[] cRawSignalsOnset)
        {
            Series cRawSignalsSeries = new Series
            {
                ChartType = SeriesChartType.FastLine,
                Color = Color.Black,
                XValueType = ChartValueType.Auto,
                YValuesPerPoint = 1,
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

            for (int i = 0; i < cRawSignals.Length; i++)
            {
                cRawSignalsSeries.Points.AddXY(i, cRawSignals[i]);
                cRawSignalsTable[i] = cRawSignals[i];
            }
           
            for (int j = 0; j < cRawSignalsOnset.Length; j++)
            {
                int valueToPLot = int.Parse(Math.Round(double.Parse(cRawSignalsOnset[j].ToString(), CrxCommon.nCI), MidpointRounding.ToEven).ToString());
                int valueToPLot1 = Math.Abs(valueToPLot);

                if (valueToPLot < 0)
                {
                    cRawSignalsSeriesTwo.Points.AddXY(valueToPLot1, cRawSignalsTable[valueToPLot1]);
                    cRawSignalsSeriesTwo.Points[cRawSignalsSeriesTwo.Points.Count - 1].MarkerStyle = MarkerStyle.Circle;
                }
                else
                {
                    cRawSignalsSeriesOne.Points.AddXY(valueToPLot1, cRawSignalsTable[valueToPLot1]);
                    cRawSignalsSeriesOne.Points[cRawSignalsSeriesOne.Points.Count - 1].MarkerStyle = MarkerStyle.Circle;
                }
            }

            guichrtCrawSignals.Series.Add(cRawSignalsSeries);
            guichrtCrawSignals.Series.Add(cRawSignalsSeriesOne);
            guichrtCrawSignals.Series.Add(cRawSignalsSeriesTwo);
            guichrtCrawSignals.Invalidate();
        }

        /** This method to draw P_RAW_SIGNALS data on the form
      * */
        private void PlotpRawSignals(float[] pRawSignals, short[] pRawSignalsOnset)
        {
            Series pRawSignalsSeries = new Series
            {
                ChartType = SeriesChartType.FastLine,
                Color = Color.Black,
                XValueType = ChartValueType.Auto,
                YValuesPerPoint = 1,
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

            for (int i = 0; i < pRawSignals.Length; i++)
            {
                pRawSignalsSeries.Points.AddXY(i, pRawSignals[i]);
                pRawSignalsTable[i] = pRawSignals[i];
            }

            for (int j = 0; j < pRawSignalsOnset.Length; j++)
            {
                int valueToPLot = int.Parse(Math.Round(double.Parse(pRawSignalsOnset[j].ToString(), CrxCommon.nCI), MidpointRounding.ToEven).ToString());
                int valueToPLot1 = Math.Abs(valueToPLot);

                if (valueToPLot < 0)
                {
                    pRawSignalsSeriesTwo.Points.AddXY(valueToPLot1, pRawSignalsTable[valueToPLot1]);
                    pRawSignalsSeriesTwo.Points[pRawSignalsSeriesTwo.Points.Count - 1].MarkerStyle = MarkerStyle.Circle;
                }
                else
                {
                    pRawSignalsSeriesOne.Points.AddXY(valueToPLot1, pRawSignalsTable[valueToPLot1]);
                    pRawSignalsSeriesOne.Points[pRawSignalsSeriesOne.Points.Count - 1].MarkerStyle = MarkerStyle.Circle;
                }
            }

            guichrtPrawSignals.Series.Add(pRawSignalsSeries);
            guichrtPrawSignals.Series.Add(pRawSignalsSeriesOne);
            guichrtPrawSignals.Series.Add(pRawSignalsSeriesTwo);
            guichrtPrawSignals.Invalidate();
        }

        /** This method to Reset Non-Zero array data 
      * */
        private float[] ResetNonZeroSizeofArray(float[] rawSignalArr)
        {
            int arrLen = 0;
            for (arrLen = 0; arrLen < rawSignalArr.Length; arrLen++)
            {
                if (rawSignalArr[arrLen] == 0.0)
                {
                    break;
                }
            }

            float[] tempArr = new float[arrLen];

            for (int j = 0; j < arrLen; j++)
            {
                tempArr[j] = rawSignalArr[j];
            }

            return tempArr;
        }

        /** This method to Reset Size array
      * */
        private short[] ResetSizeofArray(short[] rawSignalArr)
        {
            int arrLen = 0;
            for (arrLen = 0; arrLen < rawSignalArr.Length; arrLen++)
            {
                if (rawSignalArr[arrLen] < 0)
                {
                    break;
                }
            }

            short[] tempArr = new short[arrLen];

            for (int j = 0; j < arrLen; j++)
            {
                tempArr[j] = rawSignalArr[j];
            }

            return tempArr;
        }

        /** This method to Plot the multiple P_RAW_SIGNALS on the Clinical report
      * */
        private void PlotSinglePRawSignalPulse()
        {
            float[] sortedpRawSignals = new float[pRawSignals.Length];
            for (int i = 0; i < pRawSignals.Length; i++)
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
            chartSinglePRawSignal.ChartAreas["area"].AxisY.Maximum = sortedpRawSignals[sortedpRawSignals.Length - 1];
            chartSinglePRawSignal.ChartAreas["area"].AxisY.Interval = 1;
        
            // initialize series,chartype,add points to series and finally add series to chart.
            chartSinglePRawSignal.Series.Clear();

            int fixIndexForSinglePulse = pRawSignalsOnset[0];
            for (int i = 0; i < pRawSignalsOnset.Length - 1; i++)
            {
                singlePRawSignalPulse = new Series
                {
                    ChartType = SeriesChartType.FastLine,
                    Color = Color.Black,
                    XValueType = ChartValueType.Auto,
                    YValuesPerPoint = 1,
                };

                singlePRawSignalPulse.Points.Clear();

                int startIndexForSinglePulse = pRawSignalsOnset[i];

                int endIndexForSinglePulse = pRawSignalsOnset[i + 1];
                for (int k = 0, j = startIndexForSinglePulse; j < endIndexForSinglePulse; j++, k++)
                {
                     singlePRawSignalPulse.Points.AddXY(fixIndexForSinglePulse + k, pRawSignals[j]);
                }

                chartSinglePRawSignal.Series.Add(singlePRawSignalPulse);
            }

            chartSinglePRawSignal.Invalidate();          
        }

        /** This method is used to set the maximum and minimum value for X Axis on Slider
       * */
        private double[] setSliderMinMaxForXAxis(double[] data, RadLabel labelMax, RadLabel labelMin)
        {
            double max = 0.0;
            double min = 0.0;
            Array.Sort(data);
            double value = Math.Round(data[0] * GuiConstants.ChartAreaMinimumY, MidpointRounding.ToEven);

            value = ((int)Math.Round(value / 10)) * 10;

            if ((value == 0) || (value < 0 && value > data[0]))
            {
                value = Math.Round(data[0]);
            }

            min = value - 5;

            labelMin.Text = min.ToString();

            value = Math.Round((data[data.Length - 1]) * GuiConstants.ChartAreaMaximumY, MidpointRounding.ToEven);

            value = ((int)Math.Round(value / 10)) * 10;

            max = value + 5;

            labelMax.Text = max.ToString();

            return new double[] { max, min };
        }
    }
}
