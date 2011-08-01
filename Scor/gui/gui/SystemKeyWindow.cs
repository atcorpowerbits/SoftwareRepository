/*
     Copyright (C) ATCOR MEDICAL PTY LTD, 2010
 
     Filename     :     About box
        
     Author       :     Sonali Gulawe
 
     Description  :     Functionality implemented for handling system key
*/
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using Telerik.WinControls;
using System.Diagnostics;
using AtCor.Scor.CrossCutting;
using AtCor.Scor.CrossCutting.Configuration;
using AtCor.Scor.CrossCutting.Messaging;
using Telerik.WinControls.UI;
using Telerik.WinControls.Primitives;
using AtCor.Scor.BusinessLogic;

namespace AtCor.Scor.Gui.Presentation
{
    public partial class SystemKeyWindow : Telerik.WinControls.UI.RadForm
    {
        public string LicenseKey;
        readonly CrxConfigManager crxMgrObject = CrxConfigManager.Instance;
        readonly CrxMessagingManager oMsgMgr = CrxMessagingManager.Instance;        

        public SystemKeyWindow()
        {
            InitializeComponent();
            this.FormElement.TitleBar.CloseButton.Visibility = ElementVisibility.Collapsed;

            // Allowing to enter only numeric and alphabets in the textboxes
            guiradtxtKeyPart1.KeyPress += GuiCommon.CheckForNumeric_CharValues;
            guiradtxtKeyPart2.KeyPress += GuiCommon.CheckForNumeric_CharValues;
            guiradtxtKeyPart3.KeyPress += GuiCommon.CheckForNumeric_CharValues;
            guiradtxtKeyPart4.KeyPress += GuiCommon.CheckForNumeric_CharValues;
            guiradtxtKeyPart5.KeyPress += GuiCommon.CheckForNumeric_CharValues;
                   
            // Populate the text value for General settings form controls
            SetTextForGeneralSettingsTab();            

            SetShape(guiradtxtKeyPart1, guiradtxtKeyPart2, guiradtxtKeyPart3, guiradtxtKeyPart4, guiradtxtKeyPart5);
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
                    // label.RootElement.BackColor = Color.Transparent;
                    ((FillPrimitive)label.LabelElement.Children[0]).NumberOfColors = 1;
                    label.LabelElement.Shape = shape;
                }

                RadTextBox textBox = control as RadTextBox;
                if (textBox != null)
                {
                    textBox.TextBoxElement.Border.Shape = shape;
                    textBox.TextBoxElement.Fill.Shape = shape;
                }

                RadDropDownList dropDownlist = control as RadDropDownList;
                if (dropDownlist != null)
                {
                    dropDownlist.DropDownListElement.Shape = shape;
                    dropDownlist.DropDownListElement.EditableElement.Shape = shape;

                    dropDownlist.DropDownListElement.ArrowButton.Shape = shape;
                    dropDownlist.DropDownListElement.ArrowButton.Fill.NumberOfColors = 1;
                    dropDownlist.DropDownListElement.ArrowButton.Fill.BackColor = Color.FromArgb(142, 150, 186);
                    ((FillPrimitive)dropDownlist.DropDownListElement.Children[3]).BackColor = Color.FromArgb(142, 150, 186);
                }
            }
        }

        private void SetTextForGeneralSettingsTab()
        {
            guiradbtnCancel.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.BtnCancel);
            guiradbtnOk.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.BtnOkTxt);
            guiradlblErrormsg.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.LblInvalidKey);
            guiradlblSystemKey.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.LblPleaseEnterKey);

            if (GuiCommon.SystemKeyWindowValue == "Update")
            {
                this.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.FrmNewSystemKey);
            }
            else
            {
                this.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.FrmSystemKey);
            }
        }

        private void guiradbtnOk_Click(object sender, EventArgs e)
        {
            try
            {
                LicenseKey = string.Concat(guiradtxtKeyPart1.Text, guiradtxtKeyPart2.Text, guiradtxtKeyPart3.Text, guiradtxtKeyPart4.Text, guiradtxtKeyPart5.Text);

                if (BizInfo.Instance().ValidateLicenseKey(LicenseKey))
                {
                    crxMgrObject.GeneralSettings.Key = LicenseKey;
                    crxMgrObject.SetGeneralUserSettings(crxMgrObject.GeneralSettings);
                    Close();
                    if (GuiCommon.SystemKeyWindowValue == "Update")
                    {
                        RadMessageBox.Show(this, oMsgMgr.GetMessage(CrxStructCommonResourceMsg.MsgPleaseRelaunch), oMsgMgr.GetMessage(CrxStructCommonResourceMsg.ApplicationMessage), MessageBoxButtons.OK, RadMessageIcon.Info);
                        Process.GetCurrentProcess().Kill();
                    }
                }
                else
                {
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

        private void guiradbtnCancel_Click(object sender, EventArgs e)
        {
            if (GuiCommon.SystemKeyWindowValue == "Update")
            {
                this.Close();
            }
            else
            {
                Process.GetCurrentProcess().Kill();
            }
        }

        /**Focus will directly go to next textbox if current textbox having 5 characters in it.
         */ 
        private void guiradtxtKeyPart1_TextChanged(object sender, EventArgs e)
        {
            if (guiradtxtKeyPart1.Text.Length == 5)
            {
                guiradtxtKeyPart2.Focus();
            }
        }

        private void guiradtxtKeyPart2_TextChanged(object sender, EventArgs e)
        {
            if (guiradtxtKeyPart2.Text.Length == 5)
            {
                guiradtxtKeyPart3.Focus();
            }
        }

        private void guiradtxtKeyPart3_TextChanged(object sender, EventArgs e)
        {
            if (guiradtxtKeyPart3.Text.Length == 5)
            {
                guiradtxtKeyPart4.Focus();
            }
        }

        private void guiradtxtKeyPart4_TextChanged(object sender, EventArgs e)
        {
            if (guiradtxtKeyPart4.Text.Length == 5)
            {
                guiradtxtKeyPart5.Focus();
            }
        }        
    }
}
