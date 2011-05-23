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
using Telerik.WinControls;
using System.Windows.Forms;
using Telerik.WinControls.UI;
using Telerik.WinControls.Primitives;

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

            // GuiCommon.SetFontForControls(this);
            // fix the size & location of about box panel
            Size = new Size(525, 330);
            Location = new Point(0, 0);
            radPanel1.Size = new Size(530, 340);
            radPanel1.Location = new Point(-1, -1);
            MaximumSize = Size;
            MinimumSize = Size;
            SetAboutBoxInformation();
            SetShape(guiradlblCompanyName, guiradlblCopyrightNotice, guiradlblVersion, guiradlblSecurityMode, guiradlblInstalledID, guiradlblPWV, guiradlblPWA, guiradlblBP, guiradlblmoduleInfo, guiradlblLastCalibrationDate);
            SetShape(guiradbtnPrint, guiradbtnOk);
        }

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
                guiradlblVersion.Text = bizInformation.GetVersion();
                guiradlblInstalledID.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.GuiAboutInstallId);
                guiradlblPWV.Text = string.Format(oMsgMgr.GetMessage(CrxStructCommonResourceMsg.GuiAboutNoMeasuremtPwv), bizInformation.GetModuleNumberMeasurementsPWV());
                guiradlblPWA.Text = string.Format(oMsgMgr.GetMessage(CrxStructCommonResourceMsg.GuiAboutMeasuremtPwa), bizInformation.GetModuleNumberMeasurementsPWA());
                guiradlblBP.Text = string.Format(oMsgMgr.GetMessage(CrxStructCommonResourceMsg.GuiAboutMeasuremtBp), bizInformation.GetModuleNumberMeasurementsNIBP());
                guiradlblSecurityMode.Text = string.Format(oMsgMgr.GetMessage(CrxStructCommonResourceMsg.GuiAboutSecMode), bizInformation.GetSecurityMode());
                guiradlblmoduleInfo.Text = string.Format(oMsgMgr.GetMessage(CrxStructCommonResourceMsg.GuiAboutModuleTxt), bizInformation.GetModuleType(), bizInformation.GetModuleVersion(), bizInformation.GetModuleSN());

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
