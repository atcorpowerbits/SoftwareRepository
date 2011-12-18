using System;
using System.Collections.Generic;
using System.Drawing;
using System.Windows.Forms;
using AtCor.Scor.BusinessLogic;
using System.Windows.Forms.DataVisualization.Charting;
using System.Collections;
using AtCor.Scor.CrossCutting.Messaging;
using AtCor.Scor.CrossCutting.Configuration;
using System.Configuration;

namespace AtCor.Scor.Gui.Presentation
{
    public partial class ReportPreview : Form
    {        
        readonly CrxMessagingManager oMsgMgr = CrxMessagingManager.Instance;
        BizPWV obj;

        public ReportPreview()
        {
            InitializeComponent();
        }

        private void ReportPreview_Load(object sender, EventArgs e)
        {
            try
            {
                obj = (BizPWV)BizSession.Instance().measurement;

                SetTextForLabels();
                BindReportData();
                SetGraphForPatientAgeLimit();
                PlotSuperImposedWaveform(obj.femoralSignal.signal, obj.femoralSignal.floatOnsets, obj.carotidSignal.signal, obj.carotidSignal.floatOnsets, obj.femoralSignal.signalLength);
                PlotNormalRangeGraph();
                PlotReferenceRangeGraph();
                
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
        
        /** This method binds the report data from Biz session object
         * */
        private void BindReportData()
        {
            // Hardcoding 1 and 0 to set the index.Since this value is not going to change hence not moving it to config file.
            guilblStdDeviationImage.ImageIndex = obj.isStandardDeviationValid ? 1 : 0;
            guilblCarotidImage.ImageIndex = obj.isCarotidSignalValid ? 1 : 0;
            guilblFemoralImage.ImageIndex = obj.isFemoralSignalValid ? 1 : 0;
        }
      
        /** This method plots separate waveforms for carotid & femoral signals
         */
        private void PlotSuperImposedWaveform(IList<ushort> femoralSignalToPlot, float[] femoralOnSetPoints, IList<ushort> carotidSignalToPlot, float[] carotidOnSetPoints, ushort signalLength)
        {           
            // plot femoral series
            PlotCarotidFemoralSeries(femoralSignalToPlot, femoralOnSetPoints, signalLength, Color.Black, guiradChartFemoral);

            // plot carotid series
            PlotCarotidFemoralSeries(carotidSignalToPlot, carotidOnSetPoints, signalLength, Color.Blue, guichartCarotid);
        }

        /** This method plots series & onSet points for both femoral & carotid series
         * */
        private void PlotCarotidFemoralSeries(IList<ushort> signalToPlot, float[] onSetPoints, ushort signalLength, Color seriesColor, Chart chartToPLot)
        {
            const double ChartHeight = 500;
            const double MinXValue = 0;

            // plot on the waveform.
            double maxXValue = signalLength;

            // set y axis
            chartToPLot.ChartAreas[0].AxisY.Minimum = ChartHeight * GuiConstants.ChartAreaMinimumY;
            chartToPLot.ChartAreas[0].AxisY.Maximum = ChartHeight * GuiConstants.ChartAreaMaximumY;
            chartToPLot.ChartAreas[0].AxisY.Interval = 1;

            // set x axis
            chartToPLot.ChartAreas[0].AxisX.Minimum = MinXValue;
            chartToPLot.ChartAreas[0].AxisX.Maximum = maxXValue;
            chartToPLot.ChartAreas[0].AxisX.Interval = 1;

            // initialize series,chartype,add points to series and finally add series to chart.
            // Series for tonometer
            chartToPLot.Series.Clear();
            
            Series tonometerSeries = new Series
                                         {
                ChartType = SeriesChartType.FastLine,
                Color = seriesColor,
                XValueType = ChartValueType.Auto,
                YValuesPerPoint = 1
            };

            Hashtable carotidFemoralTable = new Hashtable();
            tonometerSeries.Points.Clear();
            for (int i = 0; i < signalLength; i++)
            {
                if (signalToPlot[i] > chartToPLot.ChartAreas[0].AxisY.Maximum)
                {
                    chartToPLot.ChartAreas[0].AxisY.Maximum = signalToPlot[i] * GuiConstants.ChartAreaMaximumY;
                }

                if (signalToPlot[i] < chartToPLot.ChartAreas[0].AxisY.Minimum)
                {
                    chartToPLot.ChartAreas[0].AxisY.Minimum = signalToPlot[i] * GuiConstants.ChartAreaMinimumY;
                }

                tonometerSeries.Points.AddXY(i, signalToPlot[i]);
                carotidFemoralTable[i] = signalToPlot[i];
            }

            Series tonometerOnsetSeries = new Series
                                              {
                ChartType = SeriesChartType.FastPoint,
                Color = Color.Green
            };

            Series tonometerOnsetSeries2 = new Series
                                               {
                ChartType = SeriesChartType.FastPoint,
                Color = Color.Red
            };

            tonometerOnsetSeries2.Points.Clear();
            tonometerOnsetSeries.Points.Clear();

            for (int j = 0; j < onSetPoints.Length; j++)
            {
                int valueToPLot = int.Parse(Math.Round(double.Parse(onSetPoints[j].ToString()), MidpointRounding.ToEven).ToString());
                int valueToPLot1 = Math.Abs(valueToPLot);

                if (valueToPLot < 0)
                {
                    tonometerOnsetSeries2.Points.AddXY(valueToPLot1, carotidFemoralTable[valueToPLot1]);
                    tonometerOnsetSeries2.Points[tonometerOnsetSeries2.Points.Count - 1].MarkerStyle = MarkerStyle.Circle;
                }
                else
                {
                    tonometerOnsetSeries.Points.AddXY(valueToPLot1, carotidFemoralTable[valueToPLot1]);
                    tonometerOnsetSeries.Points[tonometerOnsetSeries.Points.Count - 1].MarkerStyle = MarkerStyle.Circle;
                }
            }
            
            chartToPLot.Series.Add(tonometerSeries);
            chartToPLot.Series.Add(tonometerOnsetSeries);
            chartToPLot.Series.Add(tonometerOnsetSeries2);

            chartToPLot.ChartAreas[0].BackColor = Color.White;            
            chartToPLot.Invalidate();
        }

        /** This method plots normal range graph
         * */
        void PlotNormalRangeGraph()
        {
            try
            {
                if (guilblAgeRangeMsg.Text.Length == 0)
                {
                    // set the location and plot normal range series
                    guichartNormalRange.Location = new Point(59, 312);
                    PlotNormalReferenceRange(guichartNormalRange, obj.normalRange, AxisType.Primary, AxisType.Primary);
                }
            }
            catch (Exception ex)
            {
                GUIExceptionHandler.HandleException(ex, this);
            }
        }

        /** This method plots reference range graph
       * */
        void PlotReferenceRangeGraph()
        {
            try
            {
                if (guilblBPmsg.Text.Length == 0)
                {
                    // set the location and plot reference range series
                    guichartReferenceRange.Location = new Point(371, 311);
                    PlotNormalReferenceRange(guichartReferenceRange, obj.referenceRange, AxisType.Secondary, AxisType.Primary);
                }
            }
            catch (Exception ex)
            {
                GUIExceptionHandler.HandleException(ex, this);
            }
        }

        /** This method plots normal & reference range series
         * */
        private void PlotNormalReferenceRange(Chart rangeChart, float[] rangeToPlot, AxisType yAxisType, AxisType xAxisType)
        {
            // Since below declared value are not going to change hence hardcoding.
            const int NormalRefXInterval = 35; // interval used for x axis for normal & reference range graph
            const int NormalRefYInterval = 5; // interval used for y axis for normal & reference range graph
            const int ChartYAxisMin = 4;
            const int ChartYAxisMax = 25; 
            
            // set y axis (normal range values from Bizsession object in float)
            float[] normalReferenceRange = rangeToPlot;
            float[] sortedNormalReferenceRange = normalReferenceRange;
            Array.Sort(sortedNormalReferenceRange);

            rangeChart.Series.Clear();

            switch (yAxisType)
            {
                case AxisType.Secondary:
                    rangeChart.ChartAreas[0].AxisY2.Minimum = ChartYAxisMin;
                    rangeChart.ChartAreas[0].AxisY2.Maximum = ChartYAxisMax;
                    rangeChart.ChartAreas[0].AxisY2.Title = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.ReportNormalrangeYAxisTitle);
                    rangeChart.ChartAreas[0].AxisY2.TitleFont = new Font(GuiConstants.FontName, rangeChart.ChartAreas[0].AxisY2.TitleFont.Size, FontStyle.Bold);
                    rangeChart.ChartAreas[0].AxisY2.Interval = NormalRefYInterval;
                    break;

                default:
                    rangeChart.ChartAreas[0].AxisY.Minimum = ChartYAxisMin;
                    rangeChart.ChartAreas[0].AxisY.Maximum = ChartYAxisMax;
                    rangeChart.ChartAreas[0].AxisY.Title = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.ReportNormalrangeYAxisTitle);
                    rangeChart.ChartAreas[0].AxisY.TitleFont = new Font(GuiConstants.FontName, rangeChart.ChartAreas[0].AxisY.TitleFont.Size, FontStyle.Bold);
                    rangeChart.ChartAreas[0].AxisY.Interval = NormalRefYInterval;
                    break;
            }       

            // set x axis
            rangeChart.ChartAreas[0].AxisX.Minimum = BizConstants.MINIMUM_REFERENCE_RANGE_AGE; // 20
            rangeChart.ChartAreas[0].AxisX.Maximum = BizConstants.MAXIMUM_REFERENCE_RANGE_AGE; // 90;
            rangeChart.ChartAreas[0].AxisX.Title = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.ReportNormalrangeXAxisTitle);
            rangeChart.ChartAreas[0].AxisX.TitleFont = new Font(GuiConstants.FontName, rangeChart.ChartAreas[0].AxisX.TitleFont.Size, FontStyle.Bold);
            rangeChart.ChartAreas[0].AxisX.Interval = NormalRefXInterval;

            // initialize series,chartype,add points to series and finally add series to chart.
            // Series for tonometer
            // set display properties for normal range graph
            Series rangeSeries = new Series
                                     {
                ChartType = SeriesChartType.FastLine,
                Color = Color.Black,
                BackGradientStyle = GradientStyle.None, 
                BackHatchStyle = ChartHatchStyle.None,
                BorderColor = Color.Black,
                BorderWidth = 1,               
                YAxisType = yAxisType,
                XAxisType = xAxisType
            };

            rangeSeries.Points.Clear();

            int ageToPlot = BizConstants.MINIMUM_REFERENCE_RANGE_AGE;
            for (int i = 0; i < normalReferenceRange.Length; i++)
            {
                rangeSeries.Points.AddXY(ageToPlot + i, normalReferenceRange[i]);
            }

            rangeChart.Series.Add(rangeSeries);
          
            // set properties for series 2 for plotting bubble
            Series rangeSeries2 = new Series
                                      {
                ChartType = SeriesChartType.Bubble,
                Color = Color.FromArgb(92, 81, 238),
                CustomProperties = "BubbleMaxSize=15",
                MarkerStyle = MarkerStyle.Circle,
                YAxisType = yAxisType,
                XAxisType = xAxisType
            };

            rangeSeries2.Points.Clear();
            rangeSeries2.Points.AddXY(double.Parse(obj.patientAge.ToString()), double.Parse(obj.meanPulseWaveVelocity.ToString()));
            rangeChart.Series.Add(rangeSeries2);
            rangeChart.Invalidate();
        }

        /** This method sets text for labels from resource file
         * */
        private void SetTextForLabels()
        {
            CrxConfigManager crxConfig = CrxConfigManager.Instance;
            string defaultImgPath = ConfigurationManager.AppSettings[GuiConstants.AppConfigParams.AtcorImageIcon.ToString()];
            guiPicBoxReportLogo.Image = string.IsNullOrEmpty(crxConfig.GeneralSettings.ReportLogoPath) ? Image.FromFile(defaultImgPath) : Image.FromFile(crxConfig.GeneralSettings.ReportLogoPath);            
        }

        /** This method checks if patient age is within specified limit and accordingly displays label text instead of
         * general & healthy population
         */
        private void SetGraphForPatientAgeLimit()
        {
            if (obj.patientAge > BizConstants.MAXIMUM_REFERENCE_RANGE_AGE || obj.patientAge < BizConstants.MINIMUM_REFERENCE_RANGE_AGE)
            {
                // Display message saying Age is outside the range.
                guilblBPmsg.Text = guilblAgeRangeMsg.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.GuiReportAgeOutsideRange);
            }
            else
            {
                // Hide the label and show the chart for Reference range garph.
                guilblAgeRangeMsg.Text = string.Empty;

                // check if BP values are available or not
                SetBloodPressureLabels();
            }
        }

        /** This method checks if blood pressure values are available or not 
         * and accordingly sets gray label text for reference range (general population) chart
         */
        private void SetBloodPressureLabels()
        {
            // if (CrxConfigManager.Instance.PwvSettings.PWVDistanceMethod.Equals((int)CrxGenPwvValue.CrxPwvDistMethodSubtract) &&
            //    ((obj.bloodPressure.DP.Reading.Equals(GuiConstants.DefaultValue) && obj.bloodPressure.MP.Reading.Equals(GuiConstants.DefaultValue)) ||
            //    (obj.bloodPressure.DP.Reading.Equals(GuiConstants.DefaultValue) && obj.bloodPressure.SP.Reading.Equals(GuiConstants.DefaultValue)) ||
            //    (obj.bloodPressure.MP.Reading.Equals(GuiConstants.DefaultValue) && obj.bloodPressure.SP.Reading.Equals(GuiConstants.DefaultValue)))
            //    || obj.heightAndWeight.heightInCentimetres.Equals(GuiConstants.DefaultValue) || obj.heightAndWeight.heightInInches.Equals(GuiConstants.DefaultValue))
            // {
            //   guilblBPmsg.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.GuiReportNoBp);
            // }
            // else
            // {
            //   guilblBPmsg.Text = string.Empty;
            // }
            if (PWVReportData.RptBpLabelsText.Equals(string.Empty))
            {
                guilblBPmsg.Text = string.Empty;
                PWVReportData.RptPatientHeightInternalValue = PWVReportData.RptPatientHeightValue;
                PWVPatientReportData.RptPatientHeightInternalValue = PWVPatientReportData.RptPatientHeight;
            }
            else
            {
                guilblBPmsg.Text = PWVReportData.RptBpLabelsText;
                PWVReportData.RptPatientHeightInternalValue = string.Empty;
                PWVPatientReportData.RptPatientHeightInternalValue = string.Empty;
            }            
        }
    }
}
