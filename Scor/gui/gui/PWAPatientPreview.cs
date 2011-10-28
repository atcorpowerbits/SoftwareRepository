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

namespace AtCor.Scor.Gui.Presentation
{
    public partial class PWAPatientPreview : Form
    {
        readonly CrxMessagingManager oMsgMgr = CrxMessagingManager.Instance;        
        const int spSliderValueStartPoint = 100;
        const int spSliderPositionStartPoint = 10;
        const int spMultiplicationFactor = 7;
        const int dpMultiplicationFactor = 14;
        const int dpSliderValueStartPoint = 70;
        const int dpSliderPositionStartPoint = 10;
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
            CrxConfigManager crxConfig = CrxConfigManager.Instance;
            string defaultImgPath = ConfigurationManager.AppSettings[GuiConstants.AppConfigParams.AtcorImageIcon.ToString()];
            guiPicBoxReportLogo.Image = string.IsNullOrEmpty(crxConfig.GeneralSettings.ReportLogoPath) ? Image.FromFile(defaultImgPath) : Image.FromFile(crxConfig.GeneralSettings.ReportLogoPath);

            // guiPicBoxHumanLogo.Image = Image.FromFile(".\\\\Human.JPG");
            guiPicBoxHumanLogo.Image = Image.FromFile(ConfigurationManager.AppSettings[GuiConstants.AppConfigParams.HumanImage.ToString()]);
        }

        /** This method to plot the SP Slider
        * */
        private void PlotSpSlider()
        {
            int diffValue = Convert.ToInt32(GuiCommon.crxPwaData.SP) - spSliderValueStartPoint;
            int sliderPos = spSliderPositionStartPoint + (diffValue * spMultiplicationFactor);
            lblSpValue.Left = sliderPos;

            // "Normal";
            lblSpNormal.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.RptPwaNormalText);

            // "High Normal";
            lblSpHighNormal.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.RptPwaHighNormalText);

            // "Mild Hypertension";
            lblSpMildHypertension.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.RptPwaMildHypertensionText);

            // "Moderate hypertension";
            lblSpModerateHypertension.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.RptPwaModerateHypertensionText);

            // "Severe";
            lblSpSevere.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.RptPwaSevereText);  
        }

        /** This method to plot the DP Slider
       * */
        private void PlotDpSlider()
        {
            int diffValue = Convert.ToInt32(GuiCommon.crxPwaData.DP) - dpSliderValueStartPoint;
            int sliderPos = dpSliderPositionStartPoint + (diffValue * dpMultiplicationFactor);
            lblDpValue.Left = sliderPos;

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

        /** This method to plot the HR Slider
       * */
        private void PlotHrSlider()
        {
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
}
