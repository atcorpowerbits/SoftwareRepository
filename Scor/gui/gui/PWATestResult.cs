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
using AtCor.Scor.BusinessLogic;
using System.Configuration;

namespace AtCor.Scor.Gui.Presentation
{
    public partial class PWATestResult : Telerik.WinControls.UI.RadForm
    {
        private DefaultWindow objDefaultWindow;
        Series avgAorticPulseActualSeries;
        CrxMessagingManager oMsgMgr = CrxMessagingManager.Instance;
        float averageAorticXAxisInterval = (float)(1000.0 / 128.0);
        CrxConfigManager crxMgrObject = CrxConfigManager.Instance;
       
        public PWATestResult(DefaultWindow defWindow)
        {
            InitializeComponent();

            // set the default window
            objDefaultWindow = defWindow;           
        }

        /**This method is used to Navigate the user to the quickstart screen.
        */
        public void NavigateUserToQuickStartScreen()
        {
            if (!GuiCommon.IsReportGenerated)
            {
                DialogResult ds = RadMessageBox.Show(this, oMsgMgr.GetMessage(CrxStructCommonResourceMsg.GuiResultDataLossMsg), oMsgMgr.GetMessage(CrxStructCommonResourceMsg.Information), MessageBoxButtons.YesNo, RadMessageIcon.Info);
                switch (ds)
                {
                    case DialogResult.Yes:
                         GuiCommon.IsOnResultForm = false;
                         objDefaultWindow.radpgTabCollection.SelectedPage = objDefaultWindow.radtabQuickStart;
                         break;
                    case DialogResult.No:

                         GuiCommon.FromQuickStart = false;

                         if (!GuiCommon.IsOnSetupScreen)
                         {
                             objDefaultWindow.radpgTabCollection.SelectedPage = objDefaultWindow.radtabResult;
                             objDefaultWindow.radtabResult.Enabled = true;
                         }
                         else if (GuiCommon.IsOnPwaReportForm)
                         {
                             objDefaultWindow.radpgTabCollection.SelectedPage = objDefaultWindow.radtabReport;
                             objDefaultWindow.radtabReport.Enabled = true;  
                         }
                         else
                         {
                             objDefaultWindow.radpgTabCollection.SelectedPage = objDefaultWindow.guiradgrpbxPwvDistanceMethod;
                         }

                         break;
                    default:
                         break;
                }
            }
        }

        public void LoadTemporaryReport()
        {
            SetTextForLabels();
            GuiCommon.IsOnResultForm = true;
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
            objDefaultWindow.guiradgrpbxPwvDistanceMethod.Enabled = true;
        }

        public void LoadPWATestResult()
        {
            // Set Shapes of Labels 
            SetShape(guiradlblSPValueText, guiradlblPPValueText, guiradlblAPValueText, guiradlblAIxValueText, guiradlblHRValueText, guiradlblDPValueText, guiradlblTestSPDisplay, guiradlblPWADPDisplay, guiradlblTestResultMapDisplay, guiradlblQualityControlValue);

            // Display Calculated data on screen
            LoadTemporaryReport();
            SetTextForPwaTestResult();           
        }

        /** This method sets text for labels from resource file
        * */
        private void SetTextForLabels()
        {
            CrxConfigManager crxConfig = CrxConfigManager.Instance;
            string defaultImgPath = ConfigurationManager.AppSettings[GuiConstants.AppConfigParams.AtcorImageIcon.ToString()];
            guiPicBoxReportLogo.Image = string.IsNullOrEmpty(crxConfig.GeneralSettings.ReportLogoPath) ? Image.FromFile(defaultImgPath) : Image.FromFile(crxConfig.GeneralSettings.ReportLogoPath);
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

        /**This event is fired when the form is loaded.
        */ 
        private void PWATestResult_Load(object sender, EventArgs e)
        {            
            LoadPWATestResult();
        } 
      
        /**This event is fired when the user clicks on Patient button.
        */
        private void radbtnUpdate_Click(object sender, EventArgs e)
        {            
            objDefaultWindow.radpgTabCollection.SelectedPage = objDefaultWindow.guiradgrpbxPwvDistanceMethod;
            objDefaultWindow.guiradgrpbxPwvDistanceMethod.Enabled = true;
            objDefaultWindow.guiradmnuitemSettings.Enabled = false;
            objDefaultWindow.guiradmnuSystemKey.Enabled = false;
            objDefaultWindow.guicmbxCurrentMode.Enabled = false;             
        }

        /**This method is used to plot the central average aortic pulse waveform.
        */ 
        private void PlotAvgAorticPulseChart()
        {
            // set y axis (normal range values from Bizsession object in float)
            float[] avgAorticPulse = GuiCommon.quickStartCrxPwaData.C_AV_PULSE;
            guichartPWAReport.Series.Clear();

            // initialize series,chartype,add points to series and finally add series to chart.            
            // set display properties for Avg Aortic Pulse graph
            avgAorticPulseActualSeries = new Series
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
                    // Do Nothing
                }
                else
                {
                    avgAorticPulseActualSeries.Points.AddXY(averageAorticXAxisInterval * i, avgAorticPulse[i]);
                }
            }

            guichartPWAReport.Series.Add(avgAorticPulseActualSeries);

          
            // Setting minimum and maximum of Y-axis for Chart
            avgAorticPulse = ResetNonZeroSizeofArray(avgAorticPulse);
            Array.Sort(avgAorticPulse);
            for (int i = 0; i < avgAorticPulse.Length; i++)
            {
                if (avgAorticPulse[i] == 0)
                {
                    // Do Nothing
                }
                else
                {
                    double value = Math.Round(avgAorticPulse[i] * GuiConstants.ChartAreaMinimumY, MidpointRounding.ToEven);
                    value = ((int)Math.Round(value / 10)) * 10;
                    guichartPWAReport.ChartAreas[0].AxisY.Minimum = value - 10;
                    break;
                }
            }

            double valueMax = Math.Round((avgAorticPulse[avgAorticPulse.Length - 1]) * GuiConstants.ChartAreaMaximumY, MidpointRounding.ToEven);
            valueMax = ((int)Math.Round(valueMax / 10)) * 10;
            guichartPWAReport.ChartAreas[0].AxisY.Maximum = valueMax + 10;
            guichartPWAReport.Invalidate();
        }

        /**This method is used to set the text of the gui controls.
        */ 
        private void SetTextForPwaTestResult()
        {
            guiradlblReportBrachailSpDp.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.LblBrachialSpDpMp);
            guiradlblPWASP.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.MsgCentralSp) + ":";
            guiradlblPWAPP.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.LblPP) + ":";
            guiradlblPWAAP.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.LblAp) + ":";
            guiradlblPWAAIx.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.LblAix) + ":";
            guiradlblTestResultMap.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.RptMapTitle) + ":";
            guiradlblPWAHR.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.FieldPatientHr) + ":";
            guiradlblPWADP.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.MsgCentralDp) + ":";
            guioradlblAvgCentralAortlcPulse.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.LblAvgCentralAorticPulse);
            guiradlblQualityControl.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.LblPwaQualityControl);
            radbtnPatient.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.TabPatient);
            guiradbtnCancel.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.BtnCancel);
            guiradbtnTestPrint.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.BtnPrint);
        }

        /**This event is fired when the user clicks on the Quickstart button.
        */ 
        private void guiradbtnCancel_Click(object sender, EventArgs e)
        {
            NavigateUserToQuickStartScreen();
        }      

        /**This method is used to remove all the zero values from a given array.
        */ 
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

        private void guiradbtnTestPrint_Click(object sender, EventArgs e)
        {
            try
            {
                PWACommonReportData.RptPrintType = CrxStructCommonResourceMsg.QuickStart;
                FillStructForPWAQuickStartReport();

                PWAPrintReport objPwaPrintReport = new PWAPrintReport(this);
                objPwaPrintReport.Show();
                objPwaPrintReport.Hide();
            }
            catch (Exception ex)
            {
                GUIExceptionHandler.HandleException(ex, this);
            }
        }

        private void FillStructForPWAQuickStartReport()
        {
            PWACommonReportData.RptHeader = string.IsNullOrEmpty(crxMgrObject.GeneralSettings.ReportTitle) ? BizInfo.Instance().GetCompanyName().Replace("(R)", "\u00AE") : crxMgrObject.GeneralSettings.ReportTitle.Replace("(R)", "\u00AE");

            PWACommonReportData.RptPatientDataHeader = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.RptPatientDataTitle);

            PWACommonReportData.RptPatientName = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.LblPatientName);

            PWACommonReportData.RptPatientId = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.LblPatientId);

            PWACommonReportData.RptPatientDob = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.LblReportDob);

            PWACommonReportData.RptPatientAgeGender = string.Format("{0}, {1}", oMsgMgr.GetMessage(CrxStructCommonResourceMsg.RptAgeTitle), oMsgMgr.GetMessage(CrxStructCommonResourceMsg.LblReportGender));
          
            PWACommonReportData.RptStudyDataHeader = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.RptMeasurementData);

            PWACommonReportData.RptPatientAssessment = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.RptDateAndTime);

            PWACommonReportData.RptPatientBP = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.RptBrachialBp);

            PWACommonReportData.RptPatientHeight = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.LblHeight);

            PWACommonReportData.RptGroupNameTitle = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.LblGroup);

            PWACommonReportData.RptGroupNameValue = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.EnvClinicalText);

            PWACommonReportData.RptSignatureTitle = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.RptSignatureTitle);

            PWACommonReportData.RptPhysicianTitle = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.RptPhysicianTitle);

            PWACommonReportData.RptDateAndTimeOfAssessment = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.GuiDatetimeTxt);
        }

        private void guichartPWAReport_Click(object sender, EventArgs e)
        {

        }
    }
}
