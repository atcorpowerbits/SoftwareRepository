/* 
     Copyright (C) ATCOR MEDICAL PTY LTD, 2010 
  
     Filename     :     AnalysisPreview.cs 
        
     Author       :     Smarajit Mishra 
  
     Description  :     Creates an intermediate form for printing PWV analysis report. 
*/
using System;
using System.Collections.Generic;
using System.Drawing;
using System.Windows.Forms; 
using Telerik.WinControls;
using AtCor.Scor.CrossCutting.Configuration;
using AtCor.Scor.CrossCutting.DatabaseManager;
using AtCor.Scor.CrossCutting.Messaging;
using AtCor.Scor.CrossCutting;
using System.Windows.Forms.DataVisualization.Charting;
using System.Configuration;

namespace AtCor.Scor.Gui.Presentation
{
    public partial class AnaylsisPreview : Form
    {
        // readonly string for from field name and values
        public static readonly string Legends = "Legends";
        public static readonly string BubbleMaxSize = "BubbleMaxSize=";
        public static readonly string ZeroValue = "0";

        const int MaxLabelYValue = 12; // this denotes the maximum number of values to be displayed on Y axis so that it does not overlap                      
        const int LblVerticalAngle = -90; // angle of labels to display vertically on analysis screen when more records are are selected
        const int LblHorizontalAngle = 0; // angle of labels to display horizontally on analysis screen when few records are are selected

        readonly CrxMessagingManager oMsgMgr = CrxMessagingManager.Instance;
        readonly CrxDBManager dbMagr = CrxDBManager.Instance;
        readonly CrxConfigManager crxMgrObject = CrxConfigManager.Instance;
        readonly string serverNameString;
        string[] date; // date array to be used on analysis screen
        string[] heartRate; // heart rate array to be used on analysis screen
        string[] pWv; // pwv velocity array to be used on analysis screen
        string[] isStdDeviationValid; // standard deviation array to be used on analysis screen
        string[] sp; // SP vlaue array to be used on analysis screen
        string[] dp; // DP vlaue array to be used on analysis screen
        string[] mp; // MP vlaue array to be used on analysis screen
        int labelInterval;

        public AnaylsisPreview()
        {
            InitializeComponent();

            // initialize servername string
            serverNameString = GuiCommon.ServerNameString();
        }

        // denotes chart type on analysis screen
        enum ChartName
        {
            Pwv,
            HeartRate,
            BP
        }

        enum SeriesType
        {
            HeartLine = 0,
            HeartPoint,
            PwvLine,
            PwvPoint,
            SpLine,
            SpPoint,
            DpLine,
            DpPoint,
            MpLine,
            MpPoint,
            ErrorBar
        } // series used on analysis screen        

        private void AnaylsisPreview_Load(object sender, EventArgs e)
        {
            SetTextForLabels();
            PlotAnalysisTrendCharts(GuiConstants.DateWithComma);

            PwvPatientReport objPwvPatientReport = new PwvPatientReport(this);
            objPwvPatientReport.Show();
            objPwvPatientReport.Hide();

            Close();
            Dispose();
        }

        /** This method shows analysis trend graph
                 * */
        private void PlotAnalysisTrendCharts(string dateSelected)
        {
            try
            {
                // add chart titles & clear chart series
                guiradchartPulseWaveVelocity.Titles.Clear();
                guiradchartHeartRate.Titles.Clear();
                guiradchartPulseWaveVelocity.Series.Clear();
                guiradchartHeartRate.Series.Clear();
                guiradchartBP.Titles.Clear();
                guiradchartBP.Series.Clear();  

                // if date ends with comma, truncate it as it creates empty value in array for dates
                if (dateSelected.EndsWith(oMsgMgr.GetMessage(CrxStructCommonResourceMsg.GuiDisplayComma)))
                {
                    dateSelected = dateSelected.Remove(dateSelected.Length - 1);
                }

                date = dateSelected.Split(GuiConstants.Separator);

                // check for connection
                if (dbMagr.CheckConnection(serverNameString, crxMgrObject.GeneralSettings.SourceData) == 0)
                {
                    CrxStructPWVTrendData trendData = new CrxStructPWVTrendData();

                    // fetch records for selected assessments
                    dbMagr.GetPWVTrendData(GuiCommon.PatientInternalNumber, GuiCommon.GroupId, GuiCommon.SystemIdentifier, dateSelected + oMsgMgr.GetMessage(CrxStructCommonResourceMsg.GuiDisplayComma), trendData);
                    if (!string.IsNullOrEmpty(trendData.HeartRateArrStr) && !string.IsNullOrEmpty(trendData.PulseWaveVelocityArrStr))
                    {
                        PlotHeartRateTrend(trendData);
                        PlotPwVelocityTrend(trendData);
                        PlotBpTrend(trendData);
                    }
                }
                else
                {
                    DialogResult result = RadMessageBox.Show(this, GuiCommon.ConnectionErrorString(), oMsgMgr.GetMessage(CrxStructCommonResourceMsg.SystemError), MessageBoxButtons.RetryCancel, RadMessageIcon.Error);
                    if (result == DialogResult.Retry)
                    {
                        PlotAnalysisTrendCharts(dateSelected);
                    }
                }
            }
            catch (Exception ex)
            {
                GUIExceptionHandler.HandleException(ex, this);
            }
        }

        /** This method plots heart rate trend graph
         * */
        private void PlotHeartRateTrend(CrxStructPWVTrendData trendData)
        {
            // define strings arrays for plotting heart rate & PWV
            heartRate = trendData.HeartRateArrStr.Split(GuiConstants.Separator);
            pWv = trendData.PulseWaveVelocityArrStr.Split(GuiConstants.Separator);
            isStdDeviationValid = trendData.IsStdDevValidArrStr.Split(GuiConstants.Separator);

            string[] heartPwvSort = trendData.HeartRateArrStr.Split(GuiConstants.Separator);
            /// Array.Sort(heartPwvSort);

            int[] heartPwvSortCalc = dbMagr.CommonStringArrToIntArr(heartPwvSort);
            Array.Sort(heartPwvSortCalc);

            // plot heart rate series
            if (heartRate.Length <= 0)
            {
                return;
            }

            heartPwvSort = dbMagr.CommonIntArrToStringArr(heartPwvSortCalc);

            // assign latest record valus to bottom labels
            // guiradlblReportHeartRateValue.Text = heartRate[heartRate.Length - 1].ToString() + oMsgMgr.GetMessage(CrxStructCommonResourceMsg.HeartrateUnit);
            double value = Math.Round(double.Parse(heartPwvSort[0]) * GuiConstants.ChartAreaMinimumY, MidpointRounding.ToEven);
            value = ((int)Math.Round(value / 10.0)) * 10;
            guiradchartHeartRate.ChartAreas[0].AxisY.Minimum = value;
            guiradchartHeartRate.ChartAreas[0].AxisY.Title = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.HeartrateLblAnalysis);
            guiradchartHeartRate.ChartAreas[0].AxisY.TitleFont = new Font(GuiConstants.FontName, guiradchartHeartRate.ChartAreas[0].AxisY.TitleFont.Size, FontStyle.Bold);

            value = Math.Round(heartPwvSortCalc[heartPwvSortCalc.Length - 1] * GuiConstants.ChartAreaMaximumY, MidpointRounding.ToEven);
            guiradchartHeartRate.ChartAreas[0].AxisY.Maximum = value;
            guiradchartHeartRate.ChartAreas[0].AxisY.IntervalOffset = 0;
            guiradchartHeartRate.ChartAreas[0].AxisY.Interval = 5;

            guiradchartHeartRate.ChartAreas[0].AxisY.MajorGrid.Enabled = true;
            guiradchartHeartRate.ChartAreas[0].AxisY.MajorGrid.LineDashStyle = ChartDashStyle.Dash;
            guiradchartHeartRate.ChartAreas[0].AxisY.MajorGrid.LineColor = Color.LightGray;
            guiradchartHeartRate.ChartAreas[0].AxisX.MajorGrid.Enabled = true;
            guiradchartHeartRate.ChartAreas[0].AxisX.MajorGrid.LineDashStyle = ChartDashStyle.Dash;
            guiradchartHeartRate.ChartAreas[0].AxisX.MajorGrid.LineColor = Color.LightGray;

            guiradchartHeartRate.ChartAreas[0].AxisX.IntervalOffset = 1;
            CalculateLabelIntervalX();

            BindCustomLabelForTrendCharts(guiradchartHeartRate, heartRate.Length);

            PlotTrendChartSeries(guiradchartHeartRate, heartRate, null, ChartName.HeartRate);
        }

        /** This method plots PWV velocity trend graph 
         * */
        private void PlotPwVelocityTrend(CrxStructPWVTrendData trendData)
        {
            // plot pwv trend series
            string[] stdDeviation = trendData.StandardDeviationArrStr.Split(GuiConstants.Separator);
            string[] heartPwvSort = trendData.PulseWaveVelocityArrStr.Split(GuiConstants.Separator);

            // sort array to get minimum & maximum value to set y axis range
            // Array.Sort(heartPwvSort);
            float[] heartPwvSortCalc = dbMagr.CommonStringArrToFloatArr(heartPwvSort);
            Array.Sort(heartPwvSortCalc);

            string[] stdDeviationSort = trendData.StandardDeviationArrStr.Split(GuiConstants.Separator);
            /// Array.Sort(stdDeviationSort);

            float[] stdDeviationSortCalc = dbMagr.CommonStringArrToFloatArr(stdDeviationSort);
            Array.Sort(stdDeviationSortCalc);

            if (pWv.Length <= 0)
            {
                return;
            }

            heartPwvSort = dbMagr.CommonFloatArrToStringArr(heartPwvSortCalc);
            stdDeviationSort = dbMagr.CommonFloatArrToStringArr(stdDeviationSortCalc);

            // set max value as largest pwv + largest std deviation
            // set min value as lowest pwv + largest std deviation
            double maxValue = double.Parse(heartPwvSort[heartPwvSort.Length - 1], CrxCommon.nCI) + double.Parse(stdDeviationSort[stdDeviationSort.Length - 1], CrxCommon.nCI) + 1;
            double minValue = double.Parse(heartPwvSort[0], CrxCommon.nCI) - double.Parse(stdDeviationSort[stdDeviationSort.Length - 1], CrxCommon.nCI) - 1;

            maxValue = Math.Round(maxValue, 0, MidpointRounding.ToEven);
            minValue = Math.Round(minValue);
            CalculateLabelIntervalYForPwvTrend(int.Parse(minValue.ToString()), int.Parse(maxValue.ToString()));

            double value = Math.Round(minValue * GuiConstants.ChartAreaMinimumY);
            guiradchartPulseWaveVelocity.ChartAreas[0].AxisY.Minimum = value;
            guiradchartPulseWaveVelocity.ChartAreas[0].AxisY.Title = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.PwvLblAnalysis);
            guiradchartPulseWaveVelocity.ChartAreas[0].AxisY.TitleFont = new Font(GuiConstants.FontName, guiradchartPulseWaveVelocity.ChartAreas[0].AxisY.TitleFont.Size, FontStyle.Bold);

            value = Math.Round(maxValue * GuiConstants.ChartAreaMaximumY, 0, MidpointRounding.AwayFromZero);
            guiradchartPulseWaveVelocity.ChartAreas[0].AxisY.Maximum = value;
            guiradchartPulseWaveVelocity.ChartAreas[0].AxisY.IntervalOffset = 0;
            guiradchartPulseWaveVelocity.ChartAreas[0].AxisY.Interval = 1;

            guiradchartPulseWaveVelocity.ChartAreas[0].AxisY.MajorGrid.Enabled = true;
            guiradchartPulseWaveVelocity.ChartAreas[0].AxisY.MajorGrid.LineDashStyle = ChartDashStyle.Dash;
            guiradchartPulseWaveVelocity.ChartAreas[0].AxisY.MajorGrid.LineColor = Color.LightGray;
            guiradchartPulseWaveVelocity.ChartAreas[0].AxisX.MajorGrid.Enabled = true;
            guiradchartPulseWaveVelocity.ChartAreas[0].AxisX.MajorGrid.LineDashStyle = ChartDashStyle.Dash;
            guiradchartPulseWaveVelocity.ChartAreas[0].AxisX.MajorGrid.LineColor = Color.LightGray;

            guiradchartPulseWaveVelocity.ChartAreas[0].AxisX.IntervalOffset = 1;

            BindCustomLabelForTrendCharts(guiradchartPulseWaveVelocity, pWv.Length);
            PlotTrendChartSeries(guiradchartPulseWaveVelocity, pWv, stdDeviation, ChartName.Pwv);
        }

        /** This method calculates label interval for Y axis label for PWV trend charts
         * Since the interval is 1 there is overlapping for label display when more labels are there
         * */
        private void CalculateLabelIntervalYForPwvTrend(int minValue, int maxValue)
        {
            // calculate the number of items which will display as y axis labels
            int numberOfLabel = maxValue - minValue + 1;

            if (numberOfLabel > MaxLabelYValue)
            {
                int yInterval = numberOfLabel % MaxLabelYValue;
                guiradchartPulseWaveVelocity.ChartAreas[0].AxisY.LabelStyle.Interval = yInterval.Equals(1) ? 2 : yInterval;
            }
        }

        /** This method calculates label interval for x axis label for PWV trend & Heart rate charts
        * Since the interval is 1 there is overlapping for label display when more labels are there
        * */
        private void CalculateLabelIntervalX()
        {
            const int XInterval = 10; // this variable denotes the number by which x label interval would be calculated

            int intvl = heartRate.Length / XInterval;

            if (intvl == 0)
            {
                intvl = 1;
            }

            guiradchartHeartRate.ChartAreas[0].AxisX.LabelStyle.Interval = intvl;
            labelInterval = intvl;
        }
      
        /** This method is used to bind custom labels for X-Axis for both Heart rate & Pwv Velocity trend chart
         * */
        private void BindCustomLabelForTrendCharts(Chart trendChart, int seriesLength)
        {
            Font labelFontMax = new Font(ConfigurationManager.AppSettings[GuiConstants.AppConfigParams.AnalysisFontName.ToString()], float.Parse(ConfigurationManager.AppSettings[GuiConstants.AppConfigParams.AnalysisFontMax.ToString()]));  // sets font max size for analysis chart x axis labels
            Font labelFontMin = new Font(ConfigurationManager.AppSettings[GuiConstants.AppConfigParams.AnalysisFontName.ToString()], float.Parse(ConfigurationManager.AppSettings[GuiConstants.AppConfigParams.AnalysisFontMin.ToString()])); // sets font min size for analysis chart x axis labels

            trendChart.ChartAreas[0].AxisX.CustomLabels.Clear();

            for (int hrseries1 = 0; hrseries1 < seriesLength; hrseries1 = hrseries1 + labelInterval)
            {
                if (hrseries1 > (5 * labelInterval))
                {
                    trendChart.ChartAreas[0].AxisX.LabelStyle.Angle = LblVerticalAngle;
                    trendChart.ChartAreas[0].AxisX.LabelStyle.Font = labelFontMin;
                }
                else
                {
                    trendChart.ChartAreas[0].AxisX.LabelStyle.Font = labelFontMax;
                    trendChart.ChartAreas[0].AxisX.LabelStyle.Angle = LblHorizontalAngle;
                }

                // trendChart.ChartAreas[0].AxisX.CustomLabels.Add(hrseries1 - 1, hrseries1 + 1, date[hrseries1].ToString());
                trendChart.ChartAreas[0].AxisX.CustomLabels.Add(hrseries1 - 1, hrseries1 + 1, string.Format("{0:g}", Convert.ToDateTime(date[hrseries1].ToString())));
            }
        }

        /** This method is used to plot chart series for PWV velocity & Heart rate.
         * It displays error bar for PWV velocity chart
         * */
        private void PlotTrendChartSeries(Chart trendChart, IList<string> trendSeries, IList<string> stdDeviationSeries, ChartName trendType)
        {
            // to plot line for PWV graph  
            Series trendLine = new Series(stdDeviationSeries == null ? ((int)SeriesType.HeartLine).ToString() : ((int)SeriesType.PwvLine).ToString())
            {
                Color = Color.Blue,
                ChartType = SeriesChartType.FastLine,
                XValueType = ChartValueType.Int32
            };

            // to plot points for PWV graph
            Series trendPoint = new Series(stdDeviationSeries == null ? ((int)SeriesType.HeartPoint).ToString() : ((int)SeriesType.PwvPoint).ToString())
            {
                Color = Color.Blue,
                ChartType = SeriesChartType.Bubble,
                XValueType = ChartValueType.Int32,
                CustomProperties = BubbleMaxSize + (20 - (labelInterval * 2) + 1),
                MarkerStyle = MarkerStyle.Circle,
                ShadowOffset = 2
            };

            trendLine.Points.Clear();
            trendPoint.Points.Clear();

            for (int hrseries1 = 0; hrseries1 < trendSeries.Count; hrseries1++)
            {
                trendLine.Points.AddXY(hrseries1, double.Parse(trendSeries[hrseries1], CrxCommon.nCI));
                trendPoint.Points.AddXY(hrseries1, double.Parse(trendSeries[hrseries1], CrxCommon.nCI));

                if (trendType == ChartName.Pwv)
                {
                    // add series dynamically for showing error bar on PWV chart
                    Series correctionLine = new Series(((int)SeriesType.ErrorBar) + hrseries1.ToString())
                    {
                        ChartType = SeriesChartType.ErrorBar,
                        XValueType = ChartValueType.Int32,
                        YValuesPerPoint = 3,
                        MarkerSize = 3,
                        MarkerStyle = MarkerStyle.None,
                        Color = Color.BlueViolet
                    };

                    correctionLine["PointWidth"] = "0.1";

                    double centerY = double.Parse(pWv[hrseries1]);
                    if (stdDeviationSeries != null)
                    {
                        double lowerErrorY = centerY - double.Parse(stdDeviationSeries[hrseries1], CrxCommon.nCI);
                        double upperErrorY = centerY + double.Parse(stdDeviationSeries[hrseries1], CrxCommon.nCI);
                        correctionLine.Points.AddXY(hrseries1, centerY, lowerErrorY, upperErrorY);
                    }

                    trendChart.Series.Add(correctionLine);
                }
            }

            // following line shows y axis data for the last data point
            trendChart.Series.Add(trendLine);
            trendChart.Series.Add(trendPoint);
            trendChart.Invalidate();
        }
       
        /** This method sets text for labels from resource file
         * */
        private void SetTextForLabels()
        {
            CrxConfigManager crxConfig = CrxConfigManager.Instance;
            string defaultImgPath = ConfigurationManager.AppSettings[GuiConstants.AppConfigParams.AtcorImageIcon.ToString()];
            guiPicBoxReportLogo.Image = string.IsNullOrEmpty(crxConfig.GeneralSettings.ReportLogoPath) ? Image.FromFile(defaultImgPath) : Image.FromFile(crxConfig.GeneralSettings.ReportLogoPath);
        }

        private void guiradchartPulseWaveVelocity_Customize(object sender, EventArgs e)
        {
            try
            {
                const int SeriesPoints = 3;

                if (pWv.Length > SeriesPoints)
                {
                    foreach (CustomLabel cl in guiradchartPulseWaveVelocity.ChartAreas[0].AxisX.CustomLabels)
                    {
                        // cl.Text = DateTime.Parse(cl.Text).ToShortDateString() + Environment.NewLine + DateTime.Parse(cl.Text).ToLongTimeString();
                        cl.Text = DateTime.Parse(cl.Text).ToShortDateString() + Environment.NewLine + DateTime.Parse(cl.Text).ToShortTimeString();
                    }

                    foreach (CustomLabel cl in guiradchartHeartRate.ChartAreas[0].AxisX.CustomLabels)
                    {
                        // cl.Text = DateTime.Parse(cl.Text).ToShortDateString() + Environment.NewLine + DateTime.Parse(cl.Text).ToLongTimeString();
                        cl.Text = DateTime.Parse(cl.Text).ToShortDateString() + Environment.NewLine + DateTime.Parse(cl.Text).ToShortTimeString();
                    }
                }
            }
            catch (Exception ex)
            {
                GUIExceptionHandler.HandleException(ex, this);
            }
        }

        /** This method plots BP Trend graph 
         * */
        private void PlotBpTrend(CrxStructPWVTrendData trendData)
        {
            try
            {
                sp = trendData.SpValidArrStr.Split(GuiConstants.Separator);
                dp = trendData.DpValidArrStr.Split(GuiConstants.Separator);
                mp = trendData.MpValidArrStr.Split(GuiConstants.Separator);

                string[] spSort = trendData.SpValidArrStr.Split(GuiConstants.Separator);
                string[] dpSort = trendData.DpValidArrStr.Split(GuiConstants.Separator);
                string[] mpSort = trendData.MpValidArrStr.Split(GuiConstants.Separator);

                int[] spSortArr = dbMagr.CommonStringArrToIntArr(spSort);
                int[] dpSortArr = dbMagr.CommonStringArrToIntArr(dpSort);
                int[] mpSortArr = dbMagr.CommonStringArrToIntArr(mpSort);

                // sort array to get minimum & maximum value to set y axis range
                Array.Sort(spSortArr);
                Array.Sort(dpSortArr);
                Array.Sort(mpSortArr);

                spSort = dbMagr.CommonIntArrToStringArr(spSortArr);
                dpSort = dbMagr.CommonIntArrToStringArr(dpSortArr);
                mpSort = dbMagr.CommonIntArrToStringArr(mpSortArr);

                // Check the combination of the Blood pressure options.
                if (sp.Length > 0 && dp.Length > 0 && mp.Length > 0)
                {
                    // set min and max for the chart and plot the BP.             
                    double spValue = Math.Round(double.Parse(spSort[0]) * GuiConstants.ChartAreaMinimumY, MidpointRounding.ToEven);
                    double dpValue = Math.Round(double.Parse(dpSort[0]) * GuiConstants.ChartAreaMinimumY, MidpointRounding.ToEven);
                    double mpValue = Math.Round(double.Parse(mpSort[0]) * GuiConstants.ChartAreaMinimumY, MidpointRounding.ToEven);
                    
                    spValue = ((int)Math.Round(spValue / 10.0)) * 10;
                    dpValue = ((int)Math.Round(dpValue / 10.0)) * 10;
                    mpValue = ((int)Math.Round(mpValue / 10.0)) * 10;

                    // Compare which blood pressure option is less.
                    double lowBpVlaue = CompareLowerBP(spValue, dpValue, mpValue);

                    guiradchartBP.ChartAreas[0].AxisY.Minimum = lowBpVlaue - 10;

                    guiradchartBP.ChartAreas[0].AxisY.Title = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.BpLblAnalysis);
                    guiradchartBP.ChartAreas[0].AxisY.TitleFont = new Font(GuiConstants.FontName, guiradchartBP.ChartAreas[0].AxisY.TitleFont.Size, FontStyle.Bold);

                    // Modifying default value
                    spSort = SettingAxisValuesForChart(spSort);
                    dpSort = SettingAxisValuesForChart(dpSort);
                    mpSort = SettingAxisValuesForChart(mpSort);

                    spSortArr = dbMagr.CommonStringArrToIntArr(spSort);
                    dpSortArr = dbMagr.CommonStringArrToIntArr(dpSort);
                    mpSortArr = dbMagr.CommonStringArrToIntArr(mpSort);

                    // sort array to get minimum & maximum value to set y axis range
                    Array.Sort(spSortArr);
                    Array.Sort(dpSortArr);
                    Array.Sort(mpSortArr);

                    spSort = dbMagr.CommonIntArrToStringArr(spSortArr);
                    dpSort = dbMagr.CommonIntArrToStringArr(dpSortArr);
                    mpSort = dbMagr.CommonIntArrToStringArr(mpSortArr);

                    spValue = Math.Round(double.Parse(spSort[spSort.Length - 1]) * GuiConstants.ChartAreaMaximumY, MidpointRounding.ToEven);
                    dpValue = Math.Round(double.Parse(dpSort[dpSort.Length - 1]) * GuiConstants.ChartAreaMaximumY, MidpointRounding.ToEven);
                    mpValue = Math.Round(double.Parse(mpSort[mpSort.Length - 1]) * GuiConstants.ChartAreaMaximumY, MidpointRounding.ToEven);

                    // Compare which blood pressure option is more. 
                    double highBpVlaue = CompareHigherBP(spValue, dpValue, mpValue);

                    int yaxisInterval = YaxisIntervalOffsetBp(highBpVlaue, lowBpVlaue);

                    double tempMaxBpValue = 0.0;

                    guiradchartBP.ChartAreas[0].AxisY.Maximum = highBpVlaue + 10;

                    guiradchartBP.ChartAreas[0].AxisY.IntervalOffset = 0;
                    guiradchartBP.ChartAreas[0].AxisY.Interval = yaxisInterval; // 10;

                    guiradchartBP.ChartAreas[0].AxisY.MajorGrid.Enabled = true;
                    guiradchartBP.ChartAreas[0].AxisY.MajorGrid.LineDashStyle = ChartDashStyle.Dash;
                    guiradchartBP.ChartAreas[0].AxisY.MajorGrid.LineColor = Color.LightGray;
                    guiradchartBP.ChartAreas[0].AxisX.MajorGrid.Enabled = true;
                    guiradchartBP.ChartAreas[0].AxisX.MajorGrid.LineDashStyle = ChartDashStyle.Dash;
                    guiradchartBP.ChartAreas[0].AxisX.MajorGrid.LineColor = Color.LightGray;

                    guiradchartBP.ChartAreas[0].AxisX.IntervalOffset = 1;

                    CalculateBpLabelIntervalX();
                    BindCustomLabelForTrendCharts(guiradchartBP, sp.Length);

                    if (highBpVlaue > tempMaxBpValue)
                    {
                        PlotBpSeries(guiradchartBP, sp, dp, mp, ChartName.BP);
                        PWVAnalysisData.BPChartValidation = false;
                        PWVAnalysisData.BpChartTextValue = string.Empty;
                    }
                    else
                    {
                        // Show mwssage in the BP Chart if no BP values available for the selected assessment
                        PWVAnalysisData.BpChartTextValue = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.GuiPrintPwvAnalysisBpChartValue);
                        PWVAnalysisData.BPChartValidation = true;
                    }                

                    // Manipulation of Legends and Legends Title
                    Legend legendBP = guiradchartBP.Legends.FindByName(Legends);
                    legendBP.Title = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.GuiPrintPwvAnalysisLegendTitle);
                    
                    guiradchartBP.Legends.Clear();
                    guiradchartBP.Legends.Add(legendBP);
                }
            }
            catch (Exception ex)
            {
                GUIExceptionHandler.HandleException(ex, this);
            }
        }

        private void PlotBpSeries(Chart trendChart, IList<string> bloodPressure1, IList<string> bloodPressure2, IList<string> bloodPressure3, ChartName trendType)
        {      
            // default BP value
            string dfBPVlaue = GuiConstants.SdefaultValue.ToString();

            // to plot line for BP graph,SP value.  
            Series bp1Line = new Series(((int)SeriesType.SpLine).ToString())
            {
                Color = Color.Blue,
                ChartType = SeriesChartType.FastLine,
                XValueType = ChartValueType.Int32,
                
                MarkerStyle = MarkerStyle.Triangle,
                MarkerBorderColor = Color.DarkBlue,
                MarkerColor = Color.DarkBlue,
                MarkerSize = 80,
                MarkerBorderWidth = 50,
                LegendText = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.Sp)                
            };

            // to plot point for BP graph.,SP value
            Series bp1Point = new Series(((int)SeriesType.SpPoint).ToString())
            {
                Color = Color.DarkBlue,
                ChartType = SeriesChartType.Bubble,
                XValueType = ChartValueType.Int32,
                CustomProperties = BubbleMaxSize + (20 - (labelInterval * 2) + 1),
                MarkerStyle = MarkerStyle.Triangle,
                ShadowOffset = 0,
                LegendText = " ",
                MarkerSize = 0                
            };

            // to plot line for BP graph,DP value. 
            Series bp2Line = new Series(((int)SeriesType.DpLine).ToString())
            {
                Color = Color.Blue,
                ChartType = SeriesChartType.FastLine,
                XValueType = ChartValueType.Int32,
                
                MarkerStyle = MarkerStyle.Diamond,
                MarkerBorderColor = Color.DarkRed,
                MarkerColor = Color.DarkRed,
                MarkerSize = 80,
                MarkerBorderWidth = 80,
                LegendText = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.Dp)
            };

            // to plot point for BP graph.,DP value
            Series bp2Point = new Series(((int)SeriesType.DpPoint).ToString())
            {
                Color = Color.DarkRed,
                ChartType = SeriesChartType.Bubble,
                XValueType = ChartValueType.Int32,
                CustomProperties = BubbleMaxSize + (20 - (labelInterval * 2) + 1),
                MarkerStyle = MarkerStyle.Diamond,
                ShadowOffset = 0,
                LegendText = " ",
                MarkerSize = 0
            };

            //// to plot line for BP graph,MP value. 
            // Series bp3Line = new Series(((int)SeriesType.MpLine).ToString())
            // {
            //    Color = Color.Blue,
            //    ChartType = SeriesChartType.FastLine,
            //    XValueType = ChartValueType.Int32,                
            //    MarkerStyle = MarkerStyle.Square,
            //    MarkerBorderColor = Color.DarkGreen,
            //    MarkerColor = Color.DarkGreen,
            //    MarkerSize = 80,
            //    MarkerBorderWidth = 50,
            //    LegendText = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.Mp)
            // };
            //// to plot point for BP graph.,MP value
            // Series bp3Point = new Series(((int)SeriesType.MpPoint).ToString())
            // {
            //    Color = Color.DarkGreen,
            //    ChartType = SeriesChartType.Bubble,
            //    XValueType = ChartValueType.Int32,
            //    CustomProperties = BubbleMaxSize + (20 - (labelInterval * 2) + 1),
            //    MarkerStyle = MarkerStyle.Square,
            //    ShadowOffset = 0,
            //    LegendText = " ",
            //    MarkerSize = 0
            // };
            bp1Line.Points.Clear();
            bp1Point.Points.Clear();
            bp2Line.Points.Clear();
            bp2Point.Points.Clear();

            // bp3Line.Points.Clear();
            // bp3Point.Points.Clear();
            for (int i = 0; i < bloodPressure1.Count; i++)
            {
                // check if value is 9999
                if (!bloodPressure1[i].Equals(dfBPVlaue))
                {
                    bp1Line.Points.AddXY(i, double.Parse(bloodPressure1[i]));
                    bp1Point.Points.AddXY(i, double.Parse(bloodPressure1[i]));
                }
                else
                {
                    bp1Point.Points.AddXY(i, double.Parse(ZeroValue));
                }
            }

            for (int j = 0; j < bloodPressure2.Count; j++)
            {
                // check if value is 9999
                if (!bloodPressure2[j].Equals(dfBPVlaue))
                {
                    bp2Line.Points.AddXY(j, double.Parse(bloodPressure2[j]));
                    bp2Point.Points.AddXY(j, double.Parse(bloodPressure2[j]));
                }
                else
                {
                    bp2Point.Points.AddXY(j, double.Parse(ZeroValue));
                }
            }

            // for (int j = 0; j < bloodPressure3.Count; j++)
            // {
            //    // check if value is 9999
            //    if (!bloodPressure3[j].Equals(dfBPVlaue))
            //    {
            //        bp3Line.Points.AddXY(j, double.Parse(bloodPressure3[j]));
            //        bp3Point.Points.AddXY(j, double.Parse(bloodPressure3[j]));
            //    }
            //    else
            //    {
            //        bp3Point.Points.AddXY(j, double.Parse(ZeroValue));
            //    }
            // }
            trendChart.Series.Add(bp1Line);
            trendChart.Series.Add(bp1Point);
            trendChart.Series.Add(bp2Line);
            trendChart.Series.Add(bp2Point);

            // trendChart.Series.Add(bp3Line);
            // trendChart.Series.Add(bp3Point);
            trendChart.Invalidate();
        }

        private string[] SettingAxisValuesForChart(string[] listValue)
        {
            // default BP value
            string dfBPVlaue = GuiConstants.SdefaultValue.ToString();

            for (int i = 0; i < listValue.Length; i++)
            {
                if (listValue[i].Equals(dfBPVlaue))
                {
                    listValue[i] = ZeroValue;
                }
            }

            return listValue;
        }

        /** This method calculates label interval for x axis label for BP charts
        * Since the interval is 1 there is overlapping for label display when more labels are there
        * */
        private void CalculateBpLabelIntervalX()
        {
            const int XInterval = 10; // this variable denotes the number by which x label interval would be calculated

            int intvl = sp.Length / XInterval;

            if (intvl == 0)
            {
                intvl = 1;
            }

            guiradchartBP.ChartAreas[0].AxisX.LabelStyle.Interval = intvl;
            labelInterval = intvl;
        }

        private void guiradchartBP_Customize(object sender, EventArgs e)
        {
            try
            {
                const int SeriesPoints = 3;

                if (sp.Length > SeriesPoints)
                {
                    foreach (CustomLabel cl in guiradchartBP.ChartAreas[0].AxisX.CustomLabels)
                    {
                        // cl.Text = DateTime.Parse(cl.Text).ToShortDateString() + Environment.NewLine + DateTime.Parse(cl.Text).ToLongTimeString();
                        cl.Text = DateTime.Parse(cl.Text).ToShortDateString() + Environment.NewLine + DateTime.Parse(cl.Text).ToShortTimeString();
                    }
                }
            }
            catch (Exception ex)
            {
                GUIExceptionHandler.HandleException(ex, this);
            }
        }     

        private double CompareLowerBP(double spValue, double dpValue, double mpValue)
        {
            // Compare which blood pressure option is less. 
            double bpValue = spValue > dpValue ? dpValue : spValue;
            bpValue = bpValue > mpValue ? mpValue : bpValue;
            return bpValue;
        }

        private double CompareHigherBP(double spValue, double dpValue, double mpValue)
        {
            double bpValue = spValue > dpValue ? spValue : dpValue;
            bpValue = bpValue > mpValue ? bpValue : mpValue;
            return bpValue; 
        }

        private int YaxisIntervalOffsetBp(double highBpVlaue, double lowBpVlaue)
        {
            int bpInterval = 10;
            int tempInterval = 0;
            const int TempValue = 10;
            const int ValidInternal = 15;
            const int MaxInterval = 20;           

            if (highBpVlaue != 0.0)
            {
                highBpVlaue = highBpVlaue + TempValue;
                lowBpVlaue = lowBpVlaue - TempValue;

                tempInterval = Convert.ToInt32(highBpVlaue - lowBpVlaue);
                tempInterval = tempInterval / TempValue;

                if (tempInterval < ValidInternal)
                {
                    bpInterval = TempValue;
                }
                else
                {
                    bpInterval = MaxInterval;
                }
            }         

            return bpInterval;
        }
    }
}
