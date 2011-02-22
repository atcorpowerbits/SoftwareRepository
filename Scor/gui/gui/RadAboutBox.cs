/*
     Copyright (C) ATCOR MEDICAL PTY LTD, 2010
 
     Filename     :     About box
        
     Author       :     Vibhuti Damania
 
     Description  :     Functionality implemented for displaying about box
*/
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Windows.Forms;
using System.Reflection;
using System.Text;
using AtCor.Scor.CrossCutting;
using AtCor.Scor.CrossCutting.Messaging;
using AtCor.Scor.CrossCutting.Configuration;
using AtCor.Scor.CrossCutting.Printer;
using System.Runtime.InteropServices;
using System.IO;
using AtCor.Scor.BusinessLogic;
using biz_stub;

namespace AtCor.Scor.Gui.Presentation
{
    /**
    * @class RadAboutBox
    * @brief This class will handle displaying of the default window controls.It will also check for multiple instances of the application,exception handling and logging of events.
    */
    partial class RadAboutBox : Telerik.WinControls.UI.RadForm
    {  
        // this dll & method is used to set default printer for application, it even sets network printer as default printer
        [DllImport("winspool.drv", CharSet = CharSet.Auto, SetLastError = true)]
        public static extern bool SetDefaultPrinter(string name);

        CrxConfigManager crxMgrObject = CrxConfigManager.Instance;
        CrxMessagingManager oMsgMgr = CrxMessagingManager.Instance;
        StringBuilder sBPrint = new StringBuilder(string.Empty);

        /**Constructor of the form,initializes all the controls.
       *It will call set about box information and string for printing the same
       */        
        public RadAboutBox()
        {
            InitializeComponent();
            
            // fix the size & location of about box panel
            this.Size = new Size(525, 330);
            this.Location = new Point(0, 0);
            radPanel1.Size = new Size(530, 340);
            radPanel1.Location = new Point(-1, -1);
            this.MaximumSize = this.Size;
            this.MinimumSize = this.Size;
            SetAboutBoxInformation();            
        }

        /** This method sets about box information in respective labels
         * */
        private void SetAboutBoxInformation()
        {
            try
            {
               // create bizinfo instance to get about box information
                BizInfo bizInformation = BizInfo.Instance();
                biz_stub.BizStub_BizSession bizStubInfo = new BizStub_BizSession();

                // \u00AE displays registered symbol
                // \u00A9 displays copyright symbol
                guiradlblCompanyName.Text = bizInformation.GetCompanyName().Replace("(R)", "\u00AE"); // oMsgMgr.GetMessage("GUI_ABOUT_COMPANY") + " \u00AE"; 
                guiradlblCopyrightNotice.Text = bizInformation.GetCopyright().Replace("(c)", "\u00A9"); // oMsgMgr.GetMessage("GUI_ABOUT_COPYRIGHT").Replace("[c]", "\u00A9");
                guiradlblVersion.Text = bizInformation.GetVersion(); // oMsgMgr.GetMessage("GUI_ABOUT_VERSION");
                guiradlblInstalledID.Text = oMsgMgr.GetMessage("GUI_ABOUT_INSTALL_ID");
                guiradlblPWV.Text = oMsgMgr.GetMessage("GUI_ABOUT_NO_MEASUREMT_PWV").Replace("{n}", bizInformation.GetModuleNumberMeasurementsPWV().ToString());
                guiradlblPWA.Text = oMsgMgr.GetMessage("GUI_ABOUT_MEASUREMT_PWA").Replace("{n}", bizInformation.GetModuleNumberMeasurementsPWA().ToString());
                guiradlblBP.Text = oMsgMgr.GetMessage("GUI_ABOUT_MEASUREMT_BP").Replace("{n}", bizInformation.GetModuleNumberMeasurementsNIBP().ToString());
                guiradlblSecurityMode.Text = oMsgMgr.GetMessage("GUI_ABOUT_SEC_MODE").Replace("{n}", bizStubInfo.GetSecurityMode());
                guiradlblmoduleInfo.Text = oMsgMgr.GetMessage("GUI_ABOUT_MODULE_TXT").Replace("{n1}", bizInformation.GetModuleType()).Replace("{n2}", bizInformation.GetModuleVersion()).Replace("{n3}", bizInformation.GetModuleSN());

                guiradlblLastCalibrationDate.Text = oMsgMgr.GetMessage("GUI_ABOUT_CALIB_DATE").Replace("{n}", bizInformation.GetModuleCalibrationDate());
                guiradlblCeMark.Text = oMsgMgr.GetMessage("GUI_ABOUT_CE_MARK"); // Image.FromFile(Path.GetFullPath("CE Mark SGS.JPG")); 
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
            this.Close();
        }
        
        /** This event fires when user clicks anywhere on about box.
         * It closes about box window
         * */
        private void radPanel1_Click(object sender, EventArgs e)
        {
            this.Close();
        }

        /** This method appends string to stringbuilder for printing about box content
         * */
        private void SetPrinterString()
        {
            try
            {
                sBPrint.AppendLine(guiradlblCompanyName.Text);
                sBPrint.AppendLine(guiradlblCopyrightNotice.Text);
                sBPrint.AppendLine(guiradlblVersion.Text);
                sBPrint.AppendLine(guiradlblSecurityMode.Text);
                sBPrint.AppendLine("________________________________________________________________\n");
                sBPrint.AppendLine(guiradlblInstalledID.Text);
                sBPrint.AppendLine("\t" + guiradlblPWV.Text);
                sBPrint.AppendLine("\t" + guiradlblPWA.Text);
                sBPrint.AppendLine("\t" + guiradlblBP.Text + "\n");                
                sBPrint.AppendLine(guiradlblmoduleInfo.Text);
                sBPrint.AppendLine(guiradlblLastCalibrationDate.Text);
                sBPrint.AppendLine(guiradlblCeMark.Text);
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
                SetPrinterString();
                CrxPrintManager printMgr = CrxPrintManager.Instance;
                crxMgrObject.GetGeneralUserSettings();
                SetDefaultPrinter(crxMgrObject.GeneralSettings.PrinterName);
                printMgr.AtCorPrintDocument(sBPrint.ToString());
            }
            catch (Exception ex)
            {
                GUIExceptionHandler.HandleException(ex, this);
            }            
        }       
    }
}
