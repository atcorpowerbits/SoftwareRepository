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
using System.Windows.Forms.DataVisualization.Charting;
using System.Configuration;

namespace AtCor.Scor.Gui.Presentation
{
    public partial class AnaylsisPreview : Form
    {
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
       // int[] xCoordinate; // array of x coordinates to display data to the closest datapoint        
        int labelInterval;

        // denotes chart type on analysis screen
        enum ChartName
        {
            Pwv,
            HeartRate
        }

        enum SeriesType
        {
            HeartLine = 0,
            HeartPoint,
            PwvLine,
            PwvPoint,
            ErrorBar
        } // series used on analysis screen

        public AnaylsisPreview()
        {
            InitializeComponent();

            // initialize servername string
            serverNameString = GuiCommon.ServerNameString();
        }

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
            Array.Sort(heartPwvSort);

            // plot heart rate series
            if (heartRate.Length > 0)
            {
                // assign latest record valus to bottom labels
               // guiradlblReportHeartRateValue.Text = heartRate[heartRate.Length - 1].ToString() + oMsgMgr.GetMessage(CrxStructCommonResourceMsg.HeartrateUnit);
                double value = Math.Round(double.Parse(heartPwvSort[0]) * GuiConstants.ChartAreaMinimumY, MidpointRounding.ToEven);
                guiradchartHeartRate.ChartAreas[0].AxisY.Minimum = value;
                guiradchartHeartRate.ChartAreas[0].AxisY.Title = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.HeartrateLblAnalysis);
                guiradchartHeartRate.ChartAreas[0].AxisY.TitleFont = new Font(GuiConstants.FontName, guiradchartHeartRate.ChartAreas[0].AxisY.TitleFont.Size);

                value = Math.Round(double.Parse(heartPwvSort[heartPwvSort.Length - 1]) * GuiConstants.ChartAreaMaximumY, MidpointRounding.ToEven);
                guiradchartHeartRate.ChartAreas[0].AxisY.Maximum = value;
                guiradchartHeartRate.ChartAreas[0].AxisY.IntervalOffset = 0;
                guiradchartHeartRate.ChartAreas[0].AxisY.Interval = 10;

                guiradchartHeartRate.ChartAreas[0].AxisX.IntervalOffset = 1;
                CalculateLabelIntervalX();

                BindCustomLabelForTrendCharts(guiradchartHeartRate, heartRate.Length);

                PlotTrendChartSeries(guiradchartHeartRate, heartRate, null, ChartName.HeartRate);
            }
        }

        /** This method plots PWV velocity trend graph 
         * */
        private void PlotPwVelocityTrend(CrxStructPWVTrendData trendData)
        {
            // plot pwv trend series
            string[] stdDeviation = trendData.StandardDeviationArrStr.Split(GuiConstants.Separator);
            string[] heartPwvSort = trendData.PulseWaveVelocityArrStr.Split(GuiConstants.Separator);

            // sort array to get minimum & maximum value to set y axis range
            Array.Sort(heartPwvSort);
            string[] stdDeviationSort = trendData.StandardDeviationArrStr.Split(GuiConstants.Separator);
            Array.Sort(stdDeviationSort);

            if (pWv.Length > 0)
            {
                // set max value as largest pwv + largest std deviation
                // set min value as lowest pwv + largest std deviation
                double maxValue = double.Parse(heartPwvSort[heartPwvSort.Length - 1]) + double.Parse(stdDeviationSort[stdDeviationSort.Length - 1]) + 1;
                double minValue = double.Parse(heartPwvSort[0]) - double.Parse(stdDeviationSort[stdDeviationSort.Length - 1]) - 1;

                maxValue = Math.Round(maxValue, 0, MidpointRounding.ToEven);
                minValue = Math.Round(minValue);
                CalculateLabelIntervalYForPwvTrend(int.Parse(minValue.ToString()), int.Parse(maxValue.ToString()));

                double value = Math.Round(minValue * GuiConstants.ChartAreaMinimumY);
                guiradchartPulseWaveVelocity.ChartAreas[0].AxisY.Minimum = value;
                guiradchartPulseWaveVelocity.ChartAreas[0].AxisY.Title = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.PwvLblAnalysis);
                guiradchartPulseWaveVelocity.ChartAreas[0].AxisY.TitleFont = new Font(GuiConstants.FontName, guiradchartPulseWaveVelocity.ChartAreas[0].AxisY.TitleFont.Size);

                value = Math.Round(maxValue * GuiConstants.ChartAreaMaximumY, 0, MidpointRounding.AwayFromZero);
                guiradchartPulseWaveVelocity.ChartAreas[0].AxisY.Maximum = value;
                guiradchartPulseWaveVelocity.ChartAreas[0].AxisY.IntervalOffset = 0;
                guiradchartPulseWaveVelocity.ChartAreas[0].AxisY.Interval = 1;

                guiradchartPulseWaveVelocity.ChartAreas[0].AxisX.IntervalOffset = 1;

                BindCustomLabelForTrendCharts(guiradchartPulseWaveVelocity, pWv.Length);
                PlotTrendChartSeries(guiradchartPulseWaveVelocity, pWv, stdDeviation, ChartName.Pwv);
            }
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

                trendChart.ChartAreas[0].AxisX.CustomLabels.Add(hrseries1 - 1, hrseries1 + 1, date[hrseries1].ToString());
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
                CustomProperties = "BubbleMaxSize=" + (20 - (labelInterval * 2) + 1),
                MarkerStyle = MarkerStyle.Circle,
                ShadowOffset = 2
            };

            trendLine.Points.Clear();
            trendPoint.Points.Clear();

            for (int hrseries1 = 0; hrseries1 < trendSeries.Count; hrseries1++)
            {
                // heartline.Points.AddXY(double.Parse(DateTime.Parse(date[hrseries1].ToString()).ToOADate().ToString()), double.Parse(heartRate[hrseries1].ToString()));
                trendLine.Points.AddXY(hrseries1, double.Parse(trendSeries[hrseries1]));
                trendPoint.Points.AddXY(hrseries1, double.Parse(trendSeries[hrseries1]));

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
                    double lowerErrorY = centerY - double.Parse(stdDeviationSeries[hrseries1]);
                    double upperErrorY = centerY + double.Parse(stdDeviationSeries[hrseries1]);
                    correctionLine.Points.AddXY(hrseries1, centerY, lowerErrorY, upperErrorY);

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
            string defaultImgPath = ConfigurationManager.AppSettings[GuiConstants.AppConfigParams.AtcorImageIcon.ToString()];  // ".\\atcor.ico";
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
                        cl.Text = DateTime.Parse(cl.Text).ToShortDateString() + Environment.NewLine + DateTime.Parse(cl.Text).ToLongTimeString();
                    }

                    foreach (CustomLabel cl in guiradchartHeartRate.ChartAreas[0].AxisX.CustomLabels)
                    {
                        cl.Text = DateTime.Parse(cl.Text).ToShortDateString() + Environment.NewLine + DateTime.Parse(cl.Text).ToLongTimeString();
                    }
                }
            }
            catch (Exception ex)
            {
                GUIExceptionHandler.HandleException(ex, this);
            }
        }        
    }
}
