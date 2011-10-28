
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

namespace AtCor.Scor.Gui.Presentation
{
    public partial class PWAClinicalPreview : Form
    {
        readonly CrxMessagingManager oMsgMgr = CrxMessagingManager.Instance;
        BizPWA obj;
        float[] pRawSignals;
        short[] pRawSignalsOnset;
        Series singlePRawSignalPulse;
        decimal AverageAorticXAxisInterval = Math.Round((decimal)(1000.0 / 256.0));

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
        
            short high = 0;
            short low = 0;

            // If Augumentation Index is checked in PWA Settings tab 
            if (CrxConfigManager.Instance.PwaSettings.AugmentationIndex)
            {
                // crxPwaData.C_Agph = 9999;
                if (GuiCommon.crxPwaData.C_Agph != GuiConstants.DefaultValue)
                {
                    if (GuiCommon.bizPwaobject.GetAixRange(GuiCommon.crxPwaData.C_Agph, PWA_MEASURE_TYPE.PWA_RADIAL, ref high, ref low))
                    {
                        ShowAixTracker(100, -15, GuiCommon.crxPwaData.C_Agph, low, high, true);
                    }
                }
                else
                {
                    ShowAixTracker(100, -15, 0, 0, 0, false);
                }
            }
            else
            {
                // GuiCommon.bizPwaobject.AGPH_HR75 = 9999;
                if (GuiCommon.bizPwaobject.AGPH_HR75 != GuiConstants.DefaultValue)
                {
                    if (GuiCommon.bizPwaobject.GetAixhr75Range(GuiCommon.bizPwaobject.AGPH_HR75, PWA_MEASURE_TYPE.PWA_RADIAL, ref high, ref low))
                    {
                        ShowAixTracker(100, -15, GuiCommon.bizPwaobject.AGPH_HR75, low, high, true);
                    }
                }
                else
                {
                    ShowAixTracker(100, -15, 0, 0, 0, false);
                }
            }

            // crxPwaData.C_Sp = 9999;
            if (GuiCommon.crxPwaData.C_Sp != GuiConstants.DefaultValue)
            {
                if (GuiCommon.bizPwaobject.GetSPRange(GuiCommon.crxPwaData.C_Sp, PWA_MEASURE_TYPE.PWA_RADIAL, ref high, ref low))
                {
                    ShowSpTracker(150, 50, GuiCommon.crxPwaData.C_Sp, low, high, true);
                }
            }
            else
            {
                ShowSpTracker(150, 50, 0, 0, 0, false);
            }

            // crxPwaData.C_Ap = 9999;
            if (GuiCommon.crxPwaData.C_Ap != GuiConstants.DefaultValue)
            {
                if (GuiCommon.bizPwaobject.GetAPRange(GuiCommon.crxPwaData.C_Ap, PWA_MEASURE_TYPE.PWA_RADIAL, ref high, ref low))
                {
                    ShowApTracker(50, -10, GuiCommon.crxPwaData.C_Ap, low, high, true);
                }
            }
            else
            {
                ShowApTracker(50, -10, 0, 0, 0, false);
            }

            float centralPp;
            centralPp = GuiCommon.crxPwaData.C_Sp - GuiCommon.crxPwaData.C_Dp;

            // centralPp = 9999;
            if (centralPp != GuiConstants.DefaultValue)
            {
                if (GuiCommon.bizPwaobject.GetPPRange(centralPp, PWA_MEASURE_TYPE.PWA_RADIAL, ref high, ref low))
                {
                    ShowPpTracker(50, 0, centralPp, low, high, true);
                }
            }
            else
            {
                ShowPpTracker(50, 0, 0, 0, 0, false);
            }
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

            // guiradlblSpNotCalc.Visible = !visible;
            if (visible)
            {
                guilblSPValue.Left = guilblSPSlider.Left + ((int)(spValue - spMinValue) * (guilblSPSlider.Width / (int)(spMaxValue - spMinValue)));
                guilblSPGoodMin.Left = guilblSPSlider.Left + ((int)(spGoodRangeMin - spMinValue) * (guilblSPSlider.Width / (int)(spMaxValue - spMinValue)));
                guilblSPGoodMinText.Left = guilblSPGoodMin.Left - (guilblSPGoodMinText.Width / 3);
                guilblSPGoodMax.Left = guilblSPSlider.Left + ((int)(spGoodRangeMax - spMinValue) * (guilblSPSlider.Width / (int)(spMaxValue - spMinValue)));

                guilblSPValueText.Left = guilblSPValue.Left - (guilblSPValueText.Width / 3) + 2;
                guilblSPGoodMaxText.Left = guilblSPGoodMax.Left - (guilblSPGoodMaxText.Width / 3);

                guilblSPValueText.Text = Math.Round(spValue).ToString();
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

            // guiradlblPpNotCalc.Visible = !visible;
            if (visible)
            {
                guilblPPValue.Left = guilblPPSlider.Left + ((int)(ppValue - ppMinValue) * (guilblPPSlider.Width / (int)(ppMaxValue - ppMinValue)));

                guilblPPGoodMin.Left = guilblPPSlider.Left + ((int)(ppGoodRangeMin - ppMinValue) * (guilblPPSlider.Width / (int)(ppMaxValue - ppMinValue)));
                guilblPPGoodMax.Left = guilblPPSlider.Left + ((int)(ppGoodRangeMax - ppMinValue) * (guilblPPSlider.Width / (int)(ppMaxValue - ppMinValue)));

                guilblPPValueText.Left = guilblPPValue.Left - (guilblPPValueText.Width / 3) + 3;
                guilblPPGoodMaxText.Left = guilblPPGoodMax.Left - (guilblPPGoodMaxText.Width / 3);
                guilblPPGoodMinText.Left = guilblPPGoodMin.Left - (guilblPPGoodMinText.Width / 3);

                guilblPPValueText.Text = Math.Round(ppValue).ToString();
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

            // guiradlblAixNotCalc.Visible = !visible;
            if (visible)
            {
                guilblAIxValue.Left = guilblAIxSlider.Left + (int)((value - minValue) * (guilblAIxSlider.Width / (int)(maxValue - minValue)));

                guilblAIxGoodMin.Left = guilblAIxSlider.Left + (int)((goodRangeMin - minValue) * (guilblAIxSlider.Width / (int)(maxValue - minValue)));
                guilblAIxGoodMax.Left = guilblAIxSlider.Left + (int)((goodRangeMax - minValue) * (guilblAIxSlider.Width / (int)(maxValue - minValue)));

                guilblAIxValueText.Left = guilblAIxValue.Left - (guilblAIxValueText.Width / 3) + 4;
                guilblAIxGoodMaxText.Left = guilblAIxGoodMax.Left - (guilblAIxGoodMaxText.Width / 3);
                guilblAIxGoodMinText.Left = guilblAIxGoodMin.Left - (guilblAIxGoodMinText.Width / 3);

                guilblAIxValueText.Text = Math.Round(value).ToString();
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

            // guiradlblApNotCalc.Visible = !visible;
            if (visible)
            {
                guilblAPValue.Left = guilblAPSlider.Left + ((int)(apValue - apMinValue) * (guilblAPSlider.Width / (int)(apMaxValue - apMinValue)));

                guilblAPGoodMin.Left = guilblAPSlider.Left + ((int)(apGoodRangeMin - apMinValue) * (guilblAPSlider.Width / (int)(apMaxValue - apMinValue)));
                guilblAPGoodMax.Left = guilblAPSlider.Left + ((int)(apGoodRangeMax - apMinValue) * (guilblAPSlider.Width / (int)(apMaxValue - apMinValue)));

                guilblAPValueText.Left = guilblAPValue.Left - (guilblAPValueText.Width / 3) + 5;
                guilblAPGoodMaxText.Left = guilblAPGoodMax.Left - (guilblAPGoodMaxText.Width / 3);
                guilblAPGoodMinText.Left = guilblAPGoodMin.Left - (guilblAPGoodMinText.Width / 3);

                guilblAPValueText.Text = Math.Round(apValue).ToString();
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
            guichartPWAReport.Series.Clear();

            // initialize series,chartype,add points to series and finally add series to chart.            
            // set display properties for Avg Aortic Pulse graph
            Series avgAorticPulseActualSeries = new Series
            {
                ChartType = SeriesChartType.Spline,
                Color = Color.MediumBlue,
                BorderWidth = 2,
                Name = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.GuiReportActual),
            };

            avgAorticPulseActualSeries.Points.Clear();

            for (int i = 0; i < avgAorticPulse.Length; i++)
            {
                if (avgAorticPulse[i] == 0)
                {
                    break;
                }
                else
                {
                    avgAorticPulseActualSeries.Points.AddXY(AverageAorticXAxisInterval * i, avgAorticPulse[i]);
                }
            }

            // set properties for series 2 for plotting ideal graph
            Series avgAorticPulseIdealSeries = new Series
            {
                ChartType = SeriesChartType.Spline,
                Color = Color.DimGray,
                BorderWidth = 2,
                Name = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.GuiReportTypical),
            };
          
            avgAorticPulseIdealSeries.Points.Clear();

            // Plot actual waveform.
            for (int i = 0; i < avgTypicalAorticPulse.Length; i++)
            {
                if (avgTypicalAorticPulse[i] == 0)
                {
                    break;
                }
                else
                {
                    avgAorticPulseIdealSeries.Points.AddXY(AverageAorticXAxisInterval * i, avgTypicalAorticPulse[i]);
                }
            }
           
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

            PlotpRawSignals(cRawSignals, cRawSignalsOnset);    
        }

        /** This method to set the Raw chart properties
       * */
        private void SetRawChartProperty(float[] cRawSignals, float[] pRawSignals)
        {
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
            guichrtPrawSignals.ChartAreas["area"].AxisY.Minimum = 500 * GuiConstants.ChartAreaMinimumY;
            guichrtPrawSignals.ChartAreas["area"].AxisY.Maximum = 500 * GuiConstants.ChartAreaMaximumY;
            guichrtPrawSignals.ChartAreas["area"].AxisY.Interval = 1;

            guichrtCrawSignals.ChartAreas["area"].AxisY.Minimum = 500 * GuiConstants.ChartAreaMinimumY;
            guichrtCrawSignals.ChartAreas["area"].AxisY.Maximum = 500 * GuiConstants.ChartAreaMaximumY;
            guichrtCrawSignals.ChartAreas["area"].AxisY.Interval = 1;

            // set x axis
            guichrtPrawSignals.ChartAreas["area"].AxisX.Minimum = 0;
            guichrtPrawSignals.ChartAreas["area"].AxisX.Maximum = pRawSignals.Length; // 608;
            guichrtPrawSignals.ChartAreas["area"].AxisX.Interval = 1;

            guichrtCrawSignals.ChartAreas["area"].AxisX.Minimum = 0;
            guichrtCrawSignals.ChartAreas["area"].AxisX.Maximum = cRawSignals.Length;
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

            guichrtCrawSignals.ChartAreas["area"].AxisY.Maximum = 500 * GuiConstants.ChartAreaMaximumY;

            for (int i = 0; i < cRawSignals.Length; i++)
            {
                if (cRawSignals[i] > guichrtCrawSignals.ChartAreas[0].AxisY.Maximum)
                {
                    guichrtCrawSignals.ChartAreas["area"].AxisY.Maximum = cRawSignals[i] * GuiConstants.ChartAreaMaximumY;
                }

                if (cRawSignals[i] < guichrtCrawSignals.ChartAreas[0].AxisY.Minimum)
                {
                    guichrtCrawSignals.ChartAreas["area"].AxisY.Minimum = cRawSignals[i] * GuiConstants.ChartAreaMinimumY;
                }

                cRawSignalsSeries.Points.AddXY(i, cRawSignals[i]);
                cRawSignalsTable[i] = cRawSignals[i];
            }
           
            for (int j = 0; j < cRawSignalsOnset.Length; j++)
            {
                int valueToPLot = int.Parse(Math.Round(double.Parse(cRawSignalsOnset[j].ToString()), MidpointRounding.ToEven).ToString());
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

            guichrtPrawSignals.ChartAreas["area"].AxisY.Minimum = 500 * GuiConstants.ChartAreaMinimumY;

            for (int i = 0; i < pRawSignals.Length; i++)
            {
                if (pRawSignals[i] > guichrtPrawSignals.ChartAreas[0].AxisY.Maximum)
                {
                    guichrtPrawSignals.ChartAreas["area"].AxisY.Maximum = pRawSignals[i] * GuiConstants.ChartAreaMaximumY;
                }

                if (pRawSignals[i] < guichrtPrawSignals.ChartAreas[0].AxisY.Minimum)
                {
                    guichrtPrawSignals.ChartAreas["area"].AxisY.Minimum = pRawSignals[i] * GuiConstants.ChartAreaMinimumY;
                }

                pRawSignalsSeries.Points.AddXY(i, pRawSignals[i]);
                pRawSignalsTable[i] = pRawSignals[i];
            }

            for (int j = 0; j < pRawSignalsOnset.Length; j++)
            {
                int valueToPLot = int.Parse(Math.Round(double.Parse(pRawSignalsOnset[j].ToString()), MidpointRounding.ToEven).ToString());
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
            int fixIndexForSinglePulse = pRawSignalsOnset[0];
            for (int i = 0; i < pRawSignalsOnset.Length - 1; i++)
            {
                singlePRawSignalPulse = new Series
                {
                    ChartType = SeriesChartType.FastLine,
                    Color = Color.Black,
                    XValueType = ChartValueType.Auto,
                    YValuesPerPoint = 1,

                    // ChartArea = "area"
                };

                singlePRawSignalPulse.Points.Clear();

                int startIndexForSinglePulse = pRawSignalsOnset[i];

                int endIndexForSinglePulse = pRawSignalsOnset[i + 1];
                for (int k = 0, j = startIndexForSinglePulse; j < endIndexForSinglePulse; j++, k++)
                {
                    // singlePRawSignalPulse.Points.AddXY(fixIndexForSinglePulse+k, pRawSignals[j]);
                    singlePRawSignalPulse.Points.AddXY(k, pRawSignals[j]);
                }

                chartSinglePRawSignal.Series.Add(singlePRawSignalPulse);
            }

            chartSinglePRawSignal.Invalidate();          
        }      
    }
}
