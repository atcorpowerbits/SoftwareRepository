using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using Telerik.WinControls;
using Telerik.WinControls.Primitives;
using Telerik.WinControls.UI;
using AtCor.Scor.CrossCutting.Messaging;
using AtCor.Scor.CrossCutting.Configuration;
using AtCor.Scor.CrossCutting.Logging;
using AtCor.Scor.CrossCutting.DatabaseManager;
using System.Windows.Forms.DataVisualization.Charting;

namespace AtCor.Scor.Gui.Presentation
{
    public partial class PWATestResult : Telerik.WinControls.UI.RadForm
    {
        private DefaultWindow objDefaultWindow;
        Series avgAorticPulseActualSeries;
        CrxMessagingManager oMsgMgr = CrxMessagingManager.Instance;
        decimal AverageAorticXAxisInterval = Math.Round((decimal)(1000.0 / 256.0));
       
        public PWATestResult(DefaultWindow defWindow)
        {
            InitializeComponent();

            // set the default window
            objDefaultWindow = defWindow;

            // initialize servername string
            // serverNameString = GuiCommon.ServerNameString();
            // obj = (BizPWV)BizSession.Instance().measurement;

            // subscribe report tab click event
            DefaultWindow.OnPWATestResultTabClick += PWATestResult_Load;

            Presentation.Capture.OnPWATestResultTabClick += PWATestResult_Load;
        }

        /**This method is used to round the text boxes and the label controls on the Report screen.
         */
        private void SetShape(params Control[] labelControl)
        {
            RoundRectShape shape = new RoundRectShape();
            shape.BottomLeftRounded = true;
            shape.BottomRightRounded = true;
            shape.TopLeftRounded = true;
            shape.TopRightRounded = true;
            shape.Radius = 5;

            foreach (Control control in labelControl)
            {
                RadLabel label = control as RadLabel;

                if (label != null)
                {
                    label.RootElement.BackColor = Color.Transparent;
                    ((FillPrimitive)label.LabelElement.Children[0]).NumberOfColors = 1;

                    label.LabelElement.Shape = shape;
                }

                RadTextBox textBox = control as RadTextBox;

                if (textBox != null)
                {
                    textBox.TextBoxElement.BackColor = Color.FromArgb(172, 177, 204);
                    textBox.TextBoxElement.Fill.BackColor = Color.FromArgb(172, 177, 204);

                    textBox.TextBoxElement.Border.Shape = shape;
                    textBox.TextBoxElement.Fill.Shape = shape;
                }
            }
        }

        private void PWATestResult_Load(object sender, EventArgs e)
        {   
            // Set Shapes of Labels 
            SetShape(guiradlblSPValueText, guiradlblPPValueText, guiradlblAPValueText, guiradlblAIxValueText, guiradlblHRValueText, guiradlblDPValueText, guiradlblTestSPDisplay, guiradlblPWADPDisplay, guiradlblTestResultMapDisplay, guiradlblQualityControlValue);
            
            // Display Calculated data on screen
            LoadTemporaryReport();
            
            // objDefaultWindow.guicmbxCurrentMode.Enabled = false;  
        }

        public void LoadTemporaryReport()
        {
            guiradlblTestSPDisplay.Text = guiradlblPWADPDisplay.Text = guiradlblSPValueText.Text = guiradlblPPValueText.Text = guiradlblAPValueText.Text = guiradlblAIxValueText.Text = guiradlblTestResultMapDisplay.Text = guiradlblHRValueText.Text = guiradlblDPValueText.Text = guiradlblQualityControlValue.Text = string.Empty;
            guiradlblTestSPDisplay.Text = GuiCommon.quickStartCrxPwaData.SP.ToString();            
            guiradlblPWADPDisplay.Text = GuiCommon.quickStartCrxPwaData.DP.ToString();
            guiradlblSPValueText.Text = Math.Round(GuiCommon.quickStartCrxPwaData.C_Sp).ToString();
            guiradlblPPValueText.Text = Math.Round((GuiCommon.quickStartCrxPwaData.C_Sp - GuiCommon.quickStartCrxPwaData.C_Dp)).ToString();
            guiradlblAPValueText.Text = Math.Round(GuiCommon.quickStartCrxPwaData.C_Ap).ToString();
            guiradlblAIxValueText.Text = Math.Round(GuiCommon.quickStartCrxPwaData.C_Agph).ToString();
            guiradlblTestResultMapDisplay.Text = Math.Round(GuiCommon.quickStartCrxPwaData.C_Meanp).ToString();
            guiradlblHRValueText.Text = Math.Round(GuiCommon.quickStartCrxPwaData.HR).ToString();
            guiradlblDPValueText.Text = Math.Round(GuiCommon.quickStartCrxPwaData.C_Dp).ToString();
            guiradlblQualityControlValue.Text = Math.Round(GuiCommon.quickStartCrxPwaCuffData.OperatorIndex).ToString();

            PlotAvgAorticPulseChart();
            objDefaultWindow.guicmbxCurrentMode.Enabled = false;

           // PlotAvgAorticPulseChart();
        }

        private void radbtnUpdate_Click(object sender, EventArgs e)
        {
            /*
            objDefaultWindow.radpgTabCollection.SelectedPage = objDefaultWindow.guiradgrpbxPwvDistanceMethod;
            objDefaultWindow.guiradgrpbxPwvDistanceMethod.Enabled = true;

            GuiCommon.SetupChildForm.Controls["guipnlPWAMeasurementDetails"].Visible = true;
            GuiCommon.SetupChildForm.Controls["guipnlPWAMeasurementDetails"].Controls["guipnlPWABPOtherDevice"].Visible = false;
            
            GuiCommon.SetupChildForm.Controls["guipnlPWAMeasurementDetails"].Controls["guiradbtnGetBp"].Visible = false;
            GuiCommon.SetupChildForm.Controls["guipnlPWAMeasurementDetails"].Controls["guiradbtnAutoPWACancel"].Visible = false;
            GuiCommon.SetupChildForm.Controls["guipnlPWAMeasurementDetails"].Controls["guiradlblBPProgressBar"].Visible = false;
            GuiCommon.SetupChildForm.Controls["guipnlPWAMeasurementDetails"].Controls["guiradbtnDisplayReport"].Visible = true;            
             */ 
        }

        private void PlotAvgAorticPulseChart()
        {
            // set y axis (normal range values from Bizsession object in float)
            float[] avgAorticPulse = GuiCommon.quickStartCrxPwaData.C_AV_PULSE;
            float[] avgTypicalAorticPulse = GuiCommon.quickStartCrxPwaData.C_Typical;

            guichartPWAReport.Series.Clear();

            // initialize series,chartype,add points to series and finally add series to chart.            
            // set display properties for Avg Aortic Pulse graph
            string name1 = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.GuiReportActual).ToString();
            Series newSeries = new Series
                {
                    ChartType = SeriesChartType.Spline,
                    Color = Color.MediumBlue,
                    BorderWidth = 2,

                   // Name = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.GuiReportActual),
                };

             avgAorticPulseActualSeries = new Series
            {
                ChartType = SeriesChartType.Spline,
                Color = Color.MediumBlue,
                BorderWidth = 2,
                Name = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.GuiReportActual),
            };

            // guichartPWAReport.Series.Clear();
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

            guichartPWAReport.Series.Add(avgAorticPulseActualSeries);

            // set properties for series 2 for plotting ideal graph
            Series avgAorticPulseIdealSeries = new Series
            {
                ChartType = SeriesChartType.Spline,
                Color = Color.DimGray,
                BorderWidth = 2,

               // Name = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.GuiReportTypical),
            };
            avgAorticPulseIdealSeries.Points.Clear();
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

            guichartPWAReport.Series.Add(avgAorticPulseIdealSeries);
            guichartPWAReport.Invalidate();
        }
    }
}
