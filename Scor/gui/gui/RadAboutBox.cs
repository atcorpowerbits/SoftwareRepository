/*
     Copyright (C) ATCOR MEDICAL PTY LTD, 2010
 
     Filename     :     About box
        
     Author       :     Vibhuti Damania
 
     Description  :     Functionality implemented for displaying about box
*/
using System;
using System.Drawing;
using System.Text;
using AtCor.Scor.CrossCutting.Messaging;
using AtCor.Scor.CrossCutting.Printer;
using AtCor.Scor.BusinessLogic;
using System.Configuration;
using Telerik.WinControls.UI;
using System.Reflection;

namespace AtCor.Scor.Gui.Presentation
{
    /**
    * @class RadAboutBox
    * @brief This class will handle displaying of the default window controls.It will also check for multiple instances of the application,exception handling and logging of events.
    */
    partial class RadAboutBox : RadForm
    {
        readonly CrxMessagingManager oMsgMgr = CrxMessagingManager.Instance;
        StringBuilder sBPrint;
       
        /**Constructor of the form,initializes all the controls.
       *It will call set about box information and string for printing the same
       */        
        public RadAboutBox()
        {
            InitializeComponent();
            Text = CrxMessagingManager.Instance.GetMessage(CrxStructCommonResourceMsg.GuiAboutMenu);

            // guiradbtnOk.Text =CrxMessagingManager.Instance.GetMessage(CrxStructCommonResourceMsg.
            guiradbtnPrint.Text = CrxMessagingManager.Instance.GetMessage(CrxStructCommonResourceMsg.BtnPrint);

            // GuiCommon.SetFontForControls(this);

            // fix the size & location of about box panel
            Size = new Size(525, 370);
            Location = new Point(0, 0);
            radPanel1.Size = new Size(530, 340);
            radPanel1.Location = new Point(-1, -1);
            MaximumSize = Size;
            MinimumSize = Size;
            SetAboutBoxInformation();
            GuiCommon.SetShape(guiradlblCompanyName, guiradlblCopyrightNotice, guiradlblVersion, guiradlblSecurityMode, guiradlblInstalledID, guiradlblPWV, guiradlblPWA, guiradlblBP, guiradlblmoduleInfo, guiradlblLastCalibrationDate);
            GuiCommon.SetShape(guiradbtnPrint, guiradbtnOk);            
        }

        /** Begin: AtCor-<Drop2>-<Sprint2>, TM, <UserStory1>,4 july 2011
         * This function returns supported features for the current key.      
         */
        public string SetKeyFeatures()
        {
            string strFeatures = string.Empty;

            if (BizInfo.Instance().OptionResearch)
            {
                strFeatures = CrxMessagingManager.Instance.GetMessage(CrxStructCommonResourceMsg.LblOptionResearch);
            }
            else
            {
                strFeatures = CrxMessagingManager.Instance.GetMessage(CrxStructCommonResourceMsg.LblOptionClinical);
            }

            if (BizInfo.Instance().OptionPWV)
            {
                strFeatures = string.Concat(strFeatures, CrxMessagingManager.Instance.GetMessage(CrxStructCommonResourceMsg.LblOptionPwv));
            }

            if (BizInfo.Instance().OptionCPWA)
            {
                strFeatures = string.Concat(strFeatures, CrxMessagingManager.Instance.GetMessage(CrxStructCommonResourceMsg.LblOptioncPwa));
            }

            if (BizInfo.Instance().OptionTPWA)
            {
                strFeatures = string.Concat(strFeatures, CrxMessagingManager.Instance.GetMessage(CrxStructCommonResourceMsg.LblOptiontPwa));
            }

            if (BizInfo.Instance().OptionNIBP)
            {
                strFeatures = string.Concat(strFeatures, CrxMessagingManager.Instance.GetMessage(CrxStructCommonResourceMsg.LblOptionNibp));
            }

            if (BizInfo.Instance().OptionCaptureGuide)
            {
                strFeatures = string.Concat(strFeatures, CrxMessagingManager.Instance.GetMessage(CrxStructCommonResourceMsg.LblOptionCaptureGuide));
            }

            if (BizInfo.Instance().OptionAuditTrail)
            {
                strFeatures = string.Concat(strFeatures, CrxMessagingManager.Instance.GetMessage(CrxStructCommonResourceMsg.LblOptionAuditTrial));
            }

            return strFeatures;
        }

        // end  AtCor-<Drop2>-<Sprint2>, TM, <UserStory1>,4 july 2011

        /** This method sets about box information in respective labels
         * */
        private void SetAboutBoxInformation()
        {
            try
            {
               // create bizinfo instance to get about box information
                BizInfo bizInformation = BizInfo.Instance();
               
                // \u00AE displays registered symbol
                // \u00A9 displays copyright symbol
                guiradlblCompanyName.Text = bizInformation.GetCompanyName().Replace("(R)", "\u00AE"); 
                guiradlblCopyrightNotice.Text = bizInformation.GetCopyright().Replace("(c)", "\u00A9");
                guiradlblVersion.Text = string.Format("{0}{1}", oMsgMgr.GetMessage(CrxStructCommonResourceMsg.SplashLblVersionTxt), Assembly.GetExecutingAssembly().GetName().Version.ToString());    // bizInformation.GetVersion();
                guiradlblInstalledID.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.GuiAboutInstallId);
                guiradlblPWV.Text = string.Format(oMsgMgr.GetMessage(CrxStructCommonResourceMsg.GuiAboutNoMeasuremtPwv), bizInformation.GetModuleNumberMeasurementsPWV());
                guiradlblPWA.Text = string.Format(oMsgMgr.GetMessage(CrxStructCommonResourceMsg.GuiAboutMeasuremtPwa), bizInformation.GetModuleNumberMeasurementsPWA());
                guiradlblBP.Text = string.Format(oMsgMgr.GetMessage(CrxStructCommonResourceMsg.GuiAboutMeasuremtBp), bizInformation.GetModuleNumberMeasurementsNIBP());
                guiradlblSecurityMode.Text = string.Format(oMsgMgr.GetMessage(CrxStructCommonResourceMsg.GuiAboutSecMode), bizInformation.GetSecurityMode());
                guiradlblmoduleInfo.Text = string.Format(oMsgMgr.GetMessage(CrxStructCommonResourceMsg.GuiAboutModuleTxt), bizInformation.GetModuleType(), bizInformation.GetModuleVersion(), bizInformation.GetModuleSN());
                guiradlblKeyFeatures.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.LblKey) + ": " + SetKeyFeatures();
                guiradlblLastCalibrationDate.Text = string.Format(oMsgMgr.GetMessage(CrxStructCommonResourceMsg.GuiAboutCalibDate), bizInformation.GetModuleCalibrationDate());

                if (string.IsNullOrEmpty(ConfigurationManager.AppSettings[GuiConstants.AppConfigParams.CeMarkImage.ToString()]))
                {
                    guiradlblCeMark.BackColor = Color.FromArgb(191, 219, 255);
                }
                else
                {
                    guiradlblCeMark.Image = oMsgMgr.GetImage(ConfigurationManager.AppSettings[GuiConstants.AppConfigParams.CeMarkImage.ToString()]);
                }
            }
            catch (Exception ex)
            {
                GUIExceptionHandler.HandleException(ex, this);
            }
        }     

        /** This event fires when user clicks OK button on about box.
         * It closes about box window
         * */
        private void guiradbtnOk_Click(object sender, EventArgs e)
        {
            Close();
        }

        /** This method appends string to stringbuilder for printing about box content
         * */
        private void SetPrinterString()
        {
            try
            {
                sBPrint = new StringBuilder(string.Empty);
                sBPrint.AppendLine(guiradlblCompanyName.Text);
                sBPrint.AppendLine(guiradlblCopyrightNotice.Text);
                sBPrint.AppendLine(guiradlblVersion.Text);
                sBPrint.AppendLine(guiradlblSecurityMode.Text);
                sBPrint.AppendLine("________________________________________________________________\n");
                sBPrint.AppendLine(guiradlblInstalledID.Text);
                sBPrint.AppendLine(string.Format("\t{0}", guiradlblPWV.Text));
                sBPrint.AppendLine(string.Format("\t{0}", guiradlblPWA.Text));
                sBPrint.AppendLine(string.Format("\t{0}\n", guiradlblBP.Text));                
                sBPrint.AppendLine(guiradlblmoduleInfo.Text);
                sBPrint.AppendLine(guiradlblLastCalibrationDate.Text);
                sBPrint.AppendLine(string.Empty);
            }
            catch (Exception ex)
            {
                GUIExceptionHandler.HandleException(ex, this);
            }
        }

        /** This event fires when print button is clicked on about box
         * It prints about box content
         * */
        private void guiradbtnPrint_Click(object sender, EventArgs e)
        {
            try
            {
                // sets the string to be sent to printer for printing
                SetPrinterString();

                // call crx printmanager to print the document
                CrxPrintManager printMgr = CrxPrintManager.Instance;

                // printMgr.AtCorPrintDocument(sBPrint.ToString(), oMsgMgr.GetImage(ConfigurationManager.AppSettings["CEMarkImage"].ToString()));
                printMgr.AtCorPrintAboutBox(sBPrint.ToString(), oMsgMgr.GetImage(ConfigurationManager.AppSettings[GuiConstants.AppConfigParams.CeMarkImage.ToString()]));  
            }
            catch (Exception ex)
            {
                GUIExceptionHandler.HandleException(ex, this);
            }            
        }       
    }
}
