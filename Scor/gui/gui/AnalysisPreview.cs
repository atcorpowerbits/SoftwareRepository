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
        const int MaxNumberOfPointsForChart = 60; // This is used to set maximum number of points which can be displayed at any given time for PWV ananlysis chart.

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

        // series used on analysis screen    
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
        }     

        private void AnaylsisPreview_Load(object sender, EventArgs e)
        {
            try
            {
                SetTextForLabels();
                PlotAnalysisTrendCharts(GuiConstants.DateWithComma);

                PwvPatientReport objPwvPatientReport = new PwvPatientReport(this);
                objPwvPatientReport.Show();
                objPwvPatientReport.Hide();

                Close();
                Dispose();
            }
            catch (Exception ex)
            {
                GUIExceptionHandler.HandleException(ex, this);
            }
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
                    dateSelected = dateSelected.Remove(dateSelected.Length - Convert.ToInt32(GuiCommon.NumericValue.One));
                }

                date = dateSelected.Split(GuiConstants.Separator);

                string[] dateClac = dateSelected.Split(GuiConstants.Separator);

                string calcPwaIdWithComma = string.Empty;
                string calcDateWithComma = string.Empty;

                if (dateClac.Length > MaxNumberOfPointsForChart)
                {
                    // string[] tempPwaId = GuiConstants.PwaIdWithComma.Split(GuiConstants.Separator);

                    string[] calcDate = new string[MaxNumberOfPointsForChart];
                    date = new string[MaxNumberOfPointsForChart];

                    int clcStrt = dateClac.Length - MaxNumberOfPointsForChart;
                    for (int i = clcStrt, j = Convert.ToInt32(GuiCommon.NumericValue.Zero); i < dateClac.Length; i++, j++)
                    {
                        calcDate[j] = dateClac[i];
                        date[j] = dateClac[i];
                        string tempDateWithComma = string.Empty;
                        tempDateWithComma = dateClac[i].ToString();
                        calcDateWithComma = calcDateWithComma + tempDateWithComma + GuiConstants.Separator;
                    }                   
                }
                else
                {
                    calcPwaIdWithComma = GuiConstants.PwaIdWithComma;
                    calcDateWithComma = dateSelected;
                    date = dateSelected.Split(GuiConstants.Separator);                    
                }


                // check for connection
                if (dbMagr.CheckConnection(serverNameString, crxMgrObject.GeneralSettings.SourceData) == Convert.ToInt32(GuiCommon.NumericValue.Zero))
                {
                    CrxStructPWVTrendData trendData = new CrxStructPWVTrendData();

                    // fetch records for selected assessments
                    dbMagr.GetPWVTrendData(GuiCommon.PatientInternalNumber, GuiCommon.GroupId, GuiCommon.SystemIdentifier, calcDateWithComma + oMsgMgr.GetMessage(CrxStructCommonResourceMsg.GuiDisplayComma), trendData);
                    // dbMagr.GetPWVTrendData(GuiCommon.PatientInternalNumber, GuiCommon.GroupId, GuiCommon.SystemIdentifier, dateSelected + oMsgMgr.GetMessage(CrxStructCommonResourceMsg.GuiDisplayComma), trendData);
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
         * Any Exception will be handled by PlotAnalysisTrendCharts Function
         * */
        private void PlotHeartRateTrend(CrxStructPWVTrendData trendData)
        {
            try
            {
                // define strings arrays for plotting heart rate & PWV
                heartRate = trendData.HeartRateArrStr.Split(GuiConstants.Separator);
                pWv = trendData.PulseWaveVelocityArrStr.Split(GuiConstants.Separator);
                isStdDeviationValid = trendData.IsStdDevValidArrStr.Split(GuiConstants.Separator);

                string[] heartPwvSort = trendData.HeartRateArrStr.Split(GuiConstants.Separator);

                int[] heartPwvSortCalc = dbMagr.CommonStringArrToIntArr(heartPwvSort);
                Array.Sort(heartPwvSortCalc);

                // plot heart rate series
                if (heartRate.Length <= Convert.ToInt32(GuiCommon.NumericValue.Zero))
                {
                    return;
                }

                heartPwvSort = dbMagr.CommonIntArrToStringArr(heartPwvSortCalc);

                // assign latest record valus to bottom labels
                double value = Math.Round(double.Parse(heartPwvSort[0]) * GuiConstants.ChartAreaMinimumY, MidpointRounding.ToEven);
                value = ((int)Math.Round(value / 10.0)) * Convert.ToInt32(GuiCommon.NumericValue.Ten);
                guiradchartHeartRate.ChartAreas[0].AxisY.Minimum = value;
                guiradchartHeartRate.ChartAreas[0].AxisY.Title = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.HeartrateLblAnalysis);
                guiradchartHeartRate.ChartAreas[0].AxisY.TitleFont = new Font(GuiConstants.FontName, guiradchartHeartRate.ChartAreas[0].AxisY.TitleFont.Size, FontStyle.Bold);

                value = Math.Round(heartPwvSortCalc[heartPwvSortCalc.Length - Convert.ToInt32(GuiCommon.NumericValue.One)] * GuiConstants.ChartAreaMaximumY, MidpointRounding.ToEven);
                guiradchartHeartRate.ChartAreas[0].AxisY.Maximum = value;
                guiradchartHeartRate.ChartAreas[0].AxisY.IntervalOffset = Convert.ToInt32(GuiCommon.NumericValue.Zero);
                guiradchartHeartRate.ChartAreas[0].AxisY.Interval = Convert.ToInt32(GuiCommon.NumericValue.Five);

                guiradchartHeartRate.ChartAreas[0].AxisY.MajorGrid.Enabled = true;
                guiradchartHeartRate.ChartAreas[0].AxisY.MajorGrid.LineDashStyle = ChartDashStyle.Dash;
                guiradchartHeartRate.ChartAreas[0].AxisY.MajorGrid.LineColor = Color.LightGray;
                guiradchartHeartRate.ChartAreas[0].AxisX.MajorGrid.Enabled = true;
                guiradchartHeartRate.ChartAreas[0].AxisX.MajorGrid.LineDashStyle = ChartDashStyle.Dash;
                guiradchartHeartRate.ChartAreas[0].AxisX.MajorGrid.LineColor = Color.LightGray;

                guiradchartHeartRate.ChartAreas[0].AxisX.IntervalOffset = Convert.ToInt32(GuiCommon.NumericValue.One);
                CalculateLabelIntervalX();

                BindCustomLabelForTrendCharts(guiradchartHeartRate, heartRate.Length);

                PlotTrendChartSeries(guiradchartHeartRate, heartRate, null, ChartName.HeartRate);
            }
            catch (Exception ex)
            {
                throw (ex);
            }
        }

        /** This method plots PWV velocity trend graph 
         * Any Exception will be handled by PlotAnalysisTrendCharts Function
         * */
        private void PlotPwVelocityTrend(CrxStructPWVTrendData trendData)
        {
            try
            {
                // plot pwv trend series
                string[] stdDeviation = trendData.StandardDeviationArrStr.Split(GuiConstants.Separator);
                string[] heartPwvSort = trendData.PulseWaveVelocityArrStr.Split(GuiConstants.Separator);

                // sort array to get minimum & maximum value to set y axis range
                float[] heartPwvSortCalc = dbMagr.CommonStringArrToFloatArr(heartPwvSort);
                Array.Sort(heartPwvSortCalc);

                string[] stdDeviationSort = trendData.StandardDeviationArrStr.Split(GuiConstants.Separator);

                float[] stdDeviationSortCalc = dbMagr.CommonStringArrToFloatArr(stdDeviationSort);
                Array.Sort(stdDeviationSortCalc);

                if (pWv.Length <= Convert.ToInt32(GuiCommon.NumericValue.Zero))
                {
                    return;
                }

                heartPwvSort = dbMagr.CommonFloatArrToStringArr(heartPwvSortCalc);
                stdDeviationSort = dbMagr.CommonFloatArrToStringArr(stdDeviationSortCalc);

                // set max value as largest pwv + largest std deviation
                // set min value as lowest pwv + largest std deviation
                double maxValue = double.Parse(heartPwvSort[heartPwvSort.Length - Convert.ToInt32(GuiCommon.NumericValue.One)], CrxCommon.nCI) + double.Parse(stdDeviationSort[stdDeviationSort.Length - Convert.ToInt32(GuiCommon.NumericValue.One)], CrxCommon.nCI) + Convert.ToInt32(GuiCommon.NumericValue.One);
                double minValue = double.Parse(heartPwvSort[0], CrxCommon.nCI) - double.Parse(stdDeviationSort[stdDeviationSort.Length - Convert.ToInt32(GuiCommon.NumericValue.One)], CrxCommon.nCI) - Convert.ToInt32(GuiCommon.NumericValue.One);

                maxValue = Math.Round(maxValue, Convert.ToInt32(GuiCommon.NumericValue.Zero), MidpointRounding.ToEven);
                minValue = Math.Round(minValue);
                CalculateLabelIntervalYForPwvTrend(int.Parse(minValue.ToString()), int.Parse(maxValue.ToString()));

                double value = Math.Round(minValue * GuiConstants.ChartAreaMinimumY);
                guiradchartPulseWaveVelocity.ChartAreas[0].AxisY.Minimum = value;
                guiradchartPulseWaveVelocity.ChartAreas[0].AxisY.Title = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.PwvLblAnalysis);
                guiradchartPulseWaveVelocity.ChartAreas[0].AxisY.TitleFont = new Font(GuiConstants.FontName, guiradchartPulseWaveVelocity.ChartAreas[0].AxisY.TitleFont.Size, FontStyle.Bold);

                value = Math.Round(maxValue * GuiConstants.ChartAreaMaximumY, Convert.ToInt32(GuiCommon.NumericValue.Zero), MidpointRounding.AwayFromZero);
                guiradchartPulseWaveVelocity.ChartAreas[0].AxisY.Maximum = value;
                guiradchartPulseWaveVelocity.ChartAreas[0].AxisY.IntervalOffset = Convert.ToInt32(GuiCommon.NumericValue.Zero);
                guiradchartPulseWaveVelocity.ChartAreas[0].AxisY.Interval = Convert.ToInt32(GuiCommon.NumericValue.One);

                guiradchartPulseWaveVelocity.ChartAreas[0].AxisY.MajorGrid.Enabled = true;
                guiradchartPulseWaveVelocity.ChartAreas[0].AxisY.MajorGrid.LineDashStyle = ChartDashStyle.Dash;
                guiradchartPulseWaveVelocity.ChartAreas[0].AxisY.MajorGrid.LineColor = Color.LightGray;
                guiradchartPulseWaveVelocity.ChartAreas[0].AxisX.MajorGrid.Enabled = true;
                guiradchartPulseWaveVelocity.ChartAreas[0].AxisX.MajorGrid.LineDashStyle = ChartDashStyle.Dash;
                guiradchartPulseWaveVelocity.ChartAreas[0].AxisX.MajorGrid.LineColor = Color.LightGray;

                guiradchartPulseWaveVelocity.ChartAreas[0].AxisX.IntervalOffset = Convert.ToInt32(GuiCommon.NumericValue.One);

                BindCustomLabelForTrendCharts(guiradchartPulseWaveVelocity, pWv.Length);
                PlotTrendChartSeries(guiradchartPulseWaveVelocity, pWv, stdDeviation, ChartName.Pwv);
            }
            catch (Exception ex)
            {
                throw (ex);
            }
        }

        /** This method calculates label interval for Y axis label for PWV trend charts
         * Since the interval is 1 there is overlapping for label display when more labels are there
         * */
        private void CalculateLabelIntervalYForPwvTrend(int minValue, int maxValue)
        {
            // calculate the number of items which will display as y axis labels
            int numberOfLabel = maxValue - minValue + Convert.ToInt32(GuiCommon.NumericValue.One);

            if (numberOfLabel > MaxLabelYValue)
            {
                int yInterval = numberOfLabel % MaxLabelYValue;
                guiradchartPulseWaveVelocity.ChartAreas[0].AxisY.LabelStyle.Interval = yInterval.Equals(1) ? Convert.ToInt32(GuiCommon.NumericValue.Two) : yInterval;
            }
        }

        /** This method calculates label interval for x axis label for PWV trend & Heart rate charts
        * Since the interval is 1 there is overlapping for label display when more labels are there
        * */
        private void CalculateLabelIntervalX()
        {
            int XInterval = Convert.ToInt32(GuiCommon.NumericValue.Ten); // this variable denotes the number by which x label interval would be calculated

            int intvl = heartRate.Length / XInterval;

            if (intvl == Convert.ToInt32(GuiCommon.NumericValue.Zero))
            {
                intvl = Convert.ToInt32(GuiCommon.NumericValue.One);
            }

            guiradchartHeartRate.ChartAreas[0].AxisX.LabelStyle.Interval = intvl;
            labelInterval = intvl;
        }

        /** This method is used to bind custom labels for X-Axis for both Heart rate & Pwv Velocity trend chart
         * Any Exception will be handled by PlotAnalysisTrendCharts Function
         * */
        private void BindCustomLabelForTrendCharts(Chart trendChart, int seriesLength)
        {
            try
            {
                Font labelFontMax = new Font(ConfigurationManager.AppSettings[GuiConstants.AppConfigParams.AnalysisFontName.ToString()], float.Parse(ConfigurationManager.AppSettings[GuiConstants.AppConfigParams.AnalysisFontMax.ToString()]));  // sets font max size for analysis chart x axis labels
                Font labelFontMin = new Font(ConfigurationManager.AppSettings[GuiConstants.AppConfigParams.AnalysisFontName.ToString()], float.Parse(ConfigurationManager.AppSettings[GuiConstants.AppConfigParams.AnalysisFontMin.ToString()])); // sets font min size for analysis chart x axis labels

                trendChart.ChartAreas[0].AxisX.CustomLabels.Clear();

                for (int hrseries1 = Convert.ToInt32(GuiCommon.NumericValue.Zero); hrseries1 < seriesLength; hrseries1 = hrseries1 + labelInterval)
                {
                    if (hrseries1 > (Convert.ToInt32(GuiCommon.NumericValue.Five) * labelInterval))
                    {
                        trendChart.ChartAreas[0].AxisX.LabelStyle.Angle = LblVerticalAngle;
                        trendChart.ChartAreas[0].AxisX.LabelStyle.Font = labelFontMin;
                    }
                    else
                    {
                        trendChart.ChartAreas[0].AxisX.LabelStyle.Font = labelFontMax;
                        trendChart.ChartAreas[0].AxisX.LabelStyle.Angle = LblHorizontalAngle;
                    }

                    trendChart.ChartAreas[0].AxisX.CustomLabels.Add(hrseries1 - Convert.ToInt32(GuiCommon.NumericValue.One), hrseries1 + Convert.ToInt32(GuiCommon.NumericValue.One), string.Format("{0:g}", Convert.ToDateTime(date[hrseries1].ToString())));
                }
            }
            catch (Exception ex)
            {
                throw (ex);
            }
        }

        /** This method is used to plot chart series for PWV velocity & Heart rate.
         * It displays error bar for PWV velocity chart
         * Any Exception will be handled by PlotAnalysisTrendCharts Function
         * */
        private void PlotTrendChartSeries(Chart trendChart, IList<string> trendSeries, IList<string> stdDeviationSeries, ChartName trendType)
        {
            try
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
                    CustomProperties = BubbleMaxSize + (20 - (labelInterval * Convert.ToInt32(GuiCommon.NumericValue.Two)) + Convert.ToInt32(GuiCommon.NumericValue.One)),
                    MarkerStyle = MarkerStyle.Circle,
                    ShadowOffset = Convert.ToInt32(GuiCommon.NumericValue.Two)
                };

                trendLine.Points.Clear();
                trendPoint.Points.Clear();

                for (int hrseries1 = Convert.ToInt32(GuiCommon.NumericValue.Zero); hrseries1 < trendSeries.Count; hrseries1++)
                {
                    trendLine.Points.AddXY(hrseries1, double.Parse(trendSeries[hrseries1], CrxCommon.nCI));
                    trendPoint.Points.AddXY(hrseries1, double.Parse(trendSeries[hrseries1], CrxCommon.nCI));
                }

                // following line shows y axis data for the last data point
                trendChart.Series.Add(trendLine);
                trendChart.Series.Add(trendPoint);
                trendChart.Invalidate();
            }
            catch (Exception ex)
            {
                throw (ex);
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

        private void guiradchartPulseWaveVelocity_Customize(object sender, EventArgs e)
        {
            try
            {
                int SeriesPoints = Convert.ToInt32(GuiCommon.NumericValue.Three);

                if (pWv.Length > SeriesPoints)
                {
                    foreach (CustomLabel cl in guiradchartPulseWaveVelocity.ChartAreas[0].AxisX.CustomLabels)
                    {
                        cl.Text = DateTime.Parse(cl.Text).ToShortDateString() + Environment.NewLine + DateTime.Parse(cl.Text).ToShortTimeString();
                    }

                    foreach (CustomLabel cl in guiradchartHeartRate.ChartAreas[0].AxisX.CustomLabels)
                    {                      
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
         * Any Exception will be handled by PlotAnalysisTrendCharts Function
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
                if (sp.Length > Convert.ToInt32(GuiCommon.NumericValue.Zero) && dp.Length > Convert.ToInt32(GuiCommon.NumericValue.Zero) && mp.Length > Convert.ToInt32(GuiCommon.NumericValue.Zero))
                {
                    // set min and max for the chart and plot the BP.             
                    double spValue = Math.Round(double.Parse(spSort[0]) * GuiConstants.ChartAreaMinimumY, MidpointRounding.ToEven);
                    double dpValue = Math.Round(double.Parse(dpSort[0]) * GuiConstants.ChartAreaMinimumY, MidpointRounding.ToEven);
                    double mpValue = Math.Round(double.Parse(mpSort[0]) * GuiConstants.ChartAreaMinimumY, MidpointRounding.ToEven);
                    
                    spValue = ((int)Math.Round(spValue / 10.0)) * Convert.ToInt32(GuiCommon.NumericValue.Ten);
                    dpValue = ((int)Math.Round(dpValue / 10.0)) * Convert.ToInt32(GuiCommon.NumericValue.Ten);
                    mpValue = ((int)Math.Round(mpValue / 10.0)) * Convert.ToInt32(GuiCommon.NumericValue.Ten);

                    // Compare which blood pressure option is less.
                    double lowBpVlaue = CompareLowerBP(spValue, dpValue, mpValue);

                    guiradchartBP.ChartAreas[0].AxisY.Minimum = lowBpVlaue - Convert.ToInt32(GuiCommon.NumericValue.Ten);

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

                    spValue = Math.Round(double.Parse(spSort[spSort.Length - Convert.ToInt32(GuiCommon.NumericValue.One)]) * GuiConstants.ChartAreaMaximumY, MidpointRounding.ToEven);
                    dpValue = Math.Round(double.Parse(dpSort[dpSort.Length - Convert.ToInt32(GuiCommon.NumericValue.One)]) * GuiConstants.ChartAreaMaximumY, MidpointRounding.ToEven);
                    mpValue = Math.Round(double.Parse(mpSort[mpSort.Length - Convert.ToInt32(GuiCommon.NumericValue.One)]) * GuiConstants.ChartAreaMaximumY, MidpointRounding.ToEven);

                    // Compare which blood pressure option is more. 
                    double highBpVlaue = CompareHigherBP(spValue, dpValue, mpValue);

                    int yaxisInterval = YaxisIntervalOffsetBp(highBpVlaue, lowBpVlaue);

                    double tempMaxBpValue = 0.0;

                    guiradchartBP.ChartAreas[0].AxisY.Maximum = highBpVlaue + Convert.ToInt32(GuiCommon.NumericValue.Ten);

                    guiradchartBP.ChartAreas[0].AxisY.IntervalOffset = Convert.ToInt32(GuiCommon.NumericValue.Zero);
                    guiradchartBP.ChartAreas[0].AxisY.Interval = yaxisInterval; // 10;

                    guiradchartBP.ChartAreas[0].AxisY.MajorGrid.Enabled = true;
                    guiradchartBP.ChartAreas[0].AxisY.MajorGrid.LineDashStyle = ChartDashStyle.Dash;
                    guiradchartBP.ChartAreas[0].AxisY.MajorGrid.LineColor = Color.LightGray;
                    guiradchartBP.ChartAreas[0].AxisX.MajorGrid.Enabled = true;
                    guiradchartBP.ChartAreas[0].AxisX.MajorGrid.LineDashStyle = ChartDashStyle.Dash;
                    guiradchartBP.ChartAreas[0].AxisX.MajorGrid.LineColor = Color.LightGray;

                    guiradchartBP.ChartAreas[0].AxisX.IntervalOffset = Convert.ToInt32(GuiCommon.NumericValue.One);

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
                        // Show message in the BP Chart if no BP values available for the selected assessment
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
                throw (ex);
            }
        }

        // Any Exception will be handled by PlotAnalysisTrendCharts Function
        private void PlotBpSeries(Chart trendChart, IList<string> bloodPressure1, IList<string> bloodPressure2, IList<string> bloodPressure3, ChartName trendType)
        {
            try
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
                    CustomProperties = BubbleMaxSize + (20 - (labelInterval * Convert.ToInt32(GuiCommon.NumericValue.Two)) + Convert.ToInt32(GuiCommon.NumericValue.One)),
                    MarkerStyle = MarkerStyle.Triangle,
                    ShadowOffset = Convert.ToInt32(GuiCommon.NumericValue.Zero),
                    LegendText = " ",
                    MarkerSize = Convert.ToInt32(GuiCommon.NumericValue.Zero)
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
                    CustomProperties = BubbleMaxSize + (20 - (labelInterval * Convert.ToInt32(GuiCommon.NumericValue.Two)) + Convert.ToInt32(GuiCommon.NumericValue.One)),
                    MarkerStyle = MarkerStyle.Diamond,
                    ShadowOffset = Convert.ToInt32(GuiCommon.NumericValue.Zero),
                    LegendText = " ",
                    MarkerSize = Convert.ToInt32(GuiCommon.NumericValue.Zero)
                };

                bp1Line.Points.Clear();
                bp1Point.Points.Clear();
                bp2Line.Points.Clear();
                bp2Point.Points.Clear();

                for (int i = Convert.ToInt32(GuiCommon.NumericValue.Zero); i < bloodPressure1.Count; i++)
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

                for (int j = Convert.ToInt32(GuiCommon.NumericValue.Zero); j < bloodPressure2.Count; j++)
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

                trendChart.Series.Add(bp1Line);
                trendChart.Series.Add(bp1Point);
                trendChart.Series.Add(bp2Line);
                trendChart.Series.Add(bp2Point);

                trendChart.Invalidate();
            }
            catch (Exception ex)
            {
                throw (ex);
            }
        }

        private string[] SettingAxisValuesForChart(string[] listValue)
        {
            try
            {
                // default BP value
                string dfBPVlaue = GuiConstants.SdefaultValue.ToString();

                for (int i = Convert.ToInt32(GuiCommon.NumericValue.Zero); i < listValue.Length; i++)
                {
                    if (listValue[i].Equals(dfBPVlaue))
                    {
                        listValue[i] = ZeroValue;
                    }
                }
            }
            catch (Exception ex)
            {
                throw (ex);
            }

            return listValue;
        }

        /** This method calculates label interval for x axis label for BP charts
        * Since the interval is 1 there is overlapping for label display when more labels are there
        * */
        private void CalculateBpLabelIntervalX()
        {
            int XInterval = Convert.ToInt32(GuiCommon.NumericValue.Ten); // this variable denotes the number by which x label interval would be calculated

            int intvl = sp.Length / XInterval;

            if (intvl == Convert.ToInt32(GuiCommon.NumericValue.Zero))
            {
                intvl = Convert.ToInt32(GuiCommon.NumericValue.One);
            }

            guiradchartBP.ChartAreas[0].AxisX.LabelStyle.Interval = intvl;
            labelInterval = intvl;
        }

        private void guiradchartBP_Customize(object sender, EventArgs e)
        {
            try
            {
                int SeriesPoints = Convert.ToInt32(GuiCommon.NumericValue.Three);

                if (sp.Length > SeriesPoints)
                {
                    foreach (CustomLabel cl in guiradchartBP.ChartAreas[0].AxisX.CustomLabels)
                    {
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
            int bpInterval = Convert.ToInt32(GuiCommon.NumericValue.Ten);
            int tempInterval = Convert.ToInt32(GuiCommon.NumericValue.Zero);
            int TempValue = Convert.ToInt32(GuiCommon.NumericValue.Ten);
            int ValidInternal = Convert.ToInt32(GuiCommon.NumericValue.Fifteen);
            int MaxInterval = 20;           

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
