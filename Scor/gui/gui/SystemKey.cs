/*
     Copyright (C) ATCOR MEDICAL PTY LTD, 2010
 
     Filename     :     System Key
        
     Author       :     Sonali Gulawe
 
     Description  :     Functionality implemented for handling system key
*/
using System;
using System.Drawing;
using System.Windows.Forms;
using Telerik.WinControls;
using System.Diagnostics;
using AtCor.Scor.CrossCutting.Messaging;
using AtCor.Scor.BusinessLogic;

namespace AtCor.Scor.Gui.Presentation
{
    public partial class SystemKey : Telerik.WinControls.UI.RadForm
    {
        public string LicenseKey;
        readonly CrxMessagingManager oMsgMgr = CrxMessagingManager.Instance;        

        public SystemKey()
        {
            Size = new Size(465, 182);
            
            MaximumSize = Size;
            MinimumSize = Size;
            InitializeComponent();

            // this.FormElement.TitleBar.CloseButton.Visibility = ElementVisibility.Collapsed;

            /** Suscribe to Validating event of the textbox
             */
            guiradtxtKeyPart1.Validating += GuiCommon.ValidatingNumericCharValues;
            guiradtxtKeyPart2.Validating += GuiCommon.ValidatingNumericCharValues; 
            guiradtxtKeyPart3.Validating += GuiCommon.ValidatingNumericCharValues; 
            guiradtxtKeyPart4.Validating += GuiCommon.ValidatingNumericCharValues; 
            guiradtxtKeyPart5.Validating += GuiCommon.ValidatingNumericCharValues;  

            GuiCommon.OnEnterButtonClick += guiradbtnOk_Click;
            SetTextForGeneralSettingsTab();            

            GuiCommon.SetShape(guiradtxtKeyPart1, guiradtxtKeyPart2, guiradtxtKeyPart3, guiradtxtKeyPart4, guiradtxtKeyPart5);
        }

        /** This method sets text for form title.
         */
        private void SetTextForGeneralSettingsTab()
        {
            guiradbtnCancel.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.BtnCancel);
            guiradbtnOk.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.BtnOkTxt);
            guiradlblErrormsg.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.LblInvalidKey);
            guiradlblSystemKey.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.LblPleaseEnterKey);

            if (GuiCommon.SystemKeyWindowValue == GuiCommon.SystemKeyWindowValues.Update)
            {
                Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.FrmNewSystemKey);
            }
            else
            {
                Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.FrmSystemKey);
            }
        }

        /** This method is called on the click of OK button,it is used to validate licenseKey which is entered textbox
         */
        private void guiradbtnOk_Click(object sender, EventArgs e)
        {
            try
            {
                LicenseKey = string.Concat(guiradtxtKeyPart1.Text, guiradtxtKeyPart2.Text, guiradtxtKeyPart3.Text, guiradtxtKeyPart4.Text, guiradtxtKeyPart5.Text);

                // Below code validates entered LicenseKey.
                if (BizInfo.Instance().ValidateLicenseKey(LicenseKey))
                {
                    GuiCommon.IsValidatedLicenseKey = true;

                    // Checks whether the form is opened on response of clicking System key menu.
                    if (GuiCommon.SystemKeyWindowValue == GuiCommon.SystemKeyWindowValues.Update)
                    {   
                        RadMessageBox.Show(this, oMsgMgr.GetMessage(CrxStructCommonResourceMsg.MsgPleaseRelaunch), oMsgMgr.GetMessage(CrxStructCommonResourceMsg.SystemError), MessageBoxButtons.OK, RadMessageIcon.Info);
                        Process.GetCurrentProcess().Kill();
                    }
                    else
                    {
                        // It closes system key form after successful validation of LicenseKey.
                        Close();
                    }
                }
                else
                {
                    GuiCommon.IsValidatedLicenseKey = false;
                    guiradlblErrormsg.Visible = true;
                }
            }
            catch (Exception ex)
            {
                if (InvokeRequired)
                {
                    ExceptionHandler handle = GUIExceptionHandler.HandleException;
                    Invoke(handle, ex, this);
                }
                else
                {
                    GUIExceptionHandler.HandleException(ex, this);
                }
            }      
        }

        /* This method is called on the click of cancel button, this is used to close application.
         */
        private void guiradbtnCancel_Click(object sender, EventArgs e)
        {
            if (GuiCommon.SystemKeyWindowValue == GuiCommon.SystemKeyWindowValues.Update)
            {
                // If form in opened from system key menu then clicking cancel button will just close system key form and user can proceed with application.
                Close();
            }
            else
            {
                // If form is called on launch of application then clicking cancel will close application.
                Process.GetCurrentProcess().Kill();
            }
        }

        /** This method is used to set the Focus of the textboxes,focus will directly go to next textbox if current textbox having 5 characters.
         */ 
        private void guiradtxtKeyPart1_TextChanged(object sender, EventArgs e)
        {
            guiradtxtKeyPart1.Text = guiradtxtKeyPart1.Text.Replace(" ", string.Empty);
            if (guiradtxtKeyPart1.Text.Length == 5)
            {
                guiradtxtKeyPart2.Focus();                
            }
        }

        private void guiradtxtKeyPart2_TextChanged(object sender, EventArgs e)
        {
            guiradtxtKeyPart2.Text = guiradtxtKeyPart2.Text.Replace(" ", string.Empty);     
            if (guiradtxtKeyPart2.Text.Length == 5)
            {
                guiradtxtKeyPart3.Focus();
            }
        }

        private void guiradtxtKeyPart3_TextChanged(object sender, EventArgs e)
        {
            guiradtxtKeyPart3.Text = guiradtxtKeyPart3.Text.Replace(" ", string.Empty);
            if (guiradtxtKeyPart3.Text.Length == 5)
            {
                guiradtxtKeyPart4.Focus();
            }
        }

        private void guiradtxtKeyPart4_TextChanged(object sender, EventArgs e)
        {
            guiradtxtKeyPart4.Text = guiradtxtKeyPart4.Text.Replace(" ", string.Empty);
            if (guiradtxtKeyPart4.Text.Length == 5)
            {
                guiradtxtKeyPart5.Focus();
            }
        }
        
        private void SystemKey_Load(object sender, EventArgs e)
        {
            AcceptButton = guiradbtnOk;
            CancelButton = guiradbtnCancel;
        }

        private void guiradtxtKeyPart5_TextChanged(object sender, EventArgs e)
        {
            guiradtxtKeyPart5.Text = guiradtxtKeyPart5.Text.Replace(" ", string.Empty);
        }          
    }
}
