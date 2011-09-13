using System;

using System.Data;
using System.Drawing;
using System.Windows.Forms;
using Telerik.WinControls;
using AtCor.Scor.CrossCutting.Configuration;
using AtCor.Scor.CrossCutting.DatabaseManager;
using AtCor.Scor.CrossCutting.Messaging;
using Telerik.WinControls.UI;
using Telerik.WinControls.Primitives;
using AtCor.Scor.BusinessLogic;
using System.Configuration;
using System.Globalization;
using AtCor.Scor.DataAccess;
using System.Threading;

namespace AtCor.Scor.Gui.Presentation
{
    public partial class QuickStart : Telerik.WinControls.UI.RadForm
    {
        #region Global declarations

        readonly CrxConfigManager crxMgrObject = CrxConfigManager.Instance;
        readonly CrxMessagingManager oMsgMgr = CrxMessagingManager.Instance;
        private int timer = 0;
        private int counter = 0;

        private DefaultWindow objDefaultWindow;

        public static event EventHandler OnQSPWACapture_ClickEvent;

        #endregion
        public QuickStart(DefaultWindow defWindow)
        {
            // set the default window
            objDefaultWindow = defWindow;
            DefaultWindow.OnModeChangeDisableTimer += new EventHandler(DefaultWindow_OnModeChangeDisableTimer); 
            InitializeComponent();
        }

        // Begin: AtCor-<Drop2>-<Sprint1>, TM, Prototype,9th June, 2011
        private void Quickstarttimer_Tick(object sender, EventArgs e)
        {
            // Display reading values
            guiradlblCuffPressureValue.Text = timer.ToString();

            if (timer >= 50)
            {
                if (crxMgrObject.BpSettings.NumberofAssessments > 1 && counter < crxMgrObject.BpSettings.NumberofAssessments)
                {
                    WaitBtnTimer.Enabled = true;
                    guiradbtnGetBp.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.BtnWait);
                    guiradbtnGetBp.Enabled = false;
                    guiradlblBPProgressBar.Visible = false;
                    guiradlblBpAssessmentsStatus.Visible = false;
                    guiradbtnGetBp.Enabled = false;
                }
                else
                {
                    guiradbtnGetBp.Enabled = true;
                    guiradbtnGetBp.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.BtnRepeat);
                    counter = 0;
                    guiradbtnAssessmentsDetails.Visible = true;
                    guiradlblBpAssessmentsStatus.Visible = false;
                    guiradlblBPProgressBar.Visible = true;
                    guiradbtnAutoPWACancel.Visible = true;

                    // Start progress bar for auto capture
                    QSProgressBarTimeStatusTimer.Enabled = true;
                }

                // display button text as "Repeat" (disabled)

                // Display old readings
                switch (counter)
                {
                    case 1:

                        guiradlblPWASPDisplay.Text = "140";
                        guiradlblPWAPPDisplay.Text = "60";
                        guiradlblPWAMPDisplay.Text = "110";
                        guiradlblPWADPDisplay.Text = "80";
                        break;
                    case 2:
                        guiradlblPWASPDisplay.Text = "155";
                        guiradlblPWAPPDisplay.Text = "50";
                        guiradlblPWAMPDisplay.Text = "150";
                        guiradlblPWADPDisplay.Text = "90";
                        break;
                    case 3:
                        guiradlblPWASPDisplay.Text = "140";
                        guiradlblPWAPPDisplay.Text = "70";
                        guiradlblPWAMPDisplay.Text = "140";
                        guiradlblPWADPDisplay.Text = "70";
                        break;
                    case 4:
                        guiradlblPWASPDisplay.Text = "155";
                        guiradlblPWAPPDisplay.Text = "70";
                        guiradlblPWAMPDisplay.Text = "120";
                        guiradlblPWADPDisplay.Text = "90";
                        break;
                    case 5:
                        guiradlblPWASPDisplay.Text = "160";
                        guiradlblPWAPPDisplay.Text = "70";
                        guiradlblPWAMPDisplay.Text = "130";
                        guiradlblPWADPDisplay.Text = "85";
                        break;
                }

                // Hide Cuff Pressure labels
                guiradlblCuffPressure.Visible = false;
                guiradlblCuffPressureValue.Visible = false;
                guiradlblCuffPressureUnit.Visible = false;

                // Stop timer
                QuickStartTimer.Enabled = false;

                // Repeat Button Delay Timer enabled for 5 seconds
                // EnableRepeatBttnTimer.Interval = GuiCommon.RepeatDelay;
                // EnableRepeatBttnTimer.Enabled = true;
                guiradlblBPProgressBar.Minimum = 0;
                guiradlblBPProgressBar.Maximum = GuiCommon.AutoPWADelay;
                guiradlblBPProgressBar.Value1 = 0;
                guiradlblBPProgressBar.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.LblPwaSetupProgressBarEndMsg);
            }
            else
            {
                timer = timer + 10;
            }
        }
       
        private void QSPWACapture_Click(object sender, EventArgs e)
        {
            try
            {
                // Commented For Future Use
                // check if device is connected
                // fill the biz session object with measurement details
                // if validation succeeds start capture process
                // GuiCommon.CaptureTabClick = false;
                // OnQSPWACapture_ClickEvent.Invoke(sender, e);
                // GuiCommon.CaptureTabClick = true;
            }
            catch (Exception ex)
            {
                GUIExceptionHandler.HandleException(ex, this);
            }
        }

        private void QSEnableRepeatBttnTimer_Tick(object sender, EventArgs e)
        {
            // Enable BP Capture button
          // guiradbtnGetBp.Enabled = true;

            // display Progress bar Cancel button for auto capture
            // guiradlblBPProgressBar.Visible = true;
           // guiradbtnAutoPWACancel.Visible = true;

            // Stop Repeat Button timer
            QSEnableRepeatBttnTimer.Enabled = false;

            // Start progress bar for auto capture
           // QSProgressBarTimeStatusTimer.Enabled = true;
        }

        private void QSProgressBarTimeStatusTimer_Tick(object sender, EventArgs e)
        {
            if (guiradlblBPProgressBar.Value1 >= GuiCommon.AutoPWADelay)
            {
                // Stop Progress bar if the value exceeds PWA Delay
                QSProgressBarTimeStatusTimer.Enabled = false;

                // Hide Progress Bar
                guiradlblBPProgressBar.Visible = false;
                guiradbtnAutoPWACancel.Visible = false;

                // Commented For Future Use
                // Call a method to go to Capture Screen
                // GuiCommon.CaptureTabClick = false;
                // OnQSPWACapture_ClickEvent.Invoke(sender, e);
                // GuiCommon.CaptureTabClick = true;
            }
            else
            {
                // Increment progress bar after every second
                guiradlblBPProgressBar.Value1 = guiradlblBPProgressBar.Value1 + 1;
                int displayValue = guiradlblBPProgressBar.Maximum - guiradlblBPProgressBar.Value1;
                guiradlblBPProgressBar.Text = "PWA enabled in 0:" + displayValue.ToString();
            }
        }

        private void QuickStart_Load(object sender, EventArgs e)
        {
            guiradlblPWASPDisplay.Font = guiradlblPWASPDisplay.Font = guiradlblPWAPPDisplay.Font = guiradlblPWAMPDisplay.Font = guiradlblPWADPDisplay.Font = guiradlblCuffPressureValue.Font = new Font("Arial", 11);
            SetShape(guiradlblPWASPDisplay, guiradlblPWAPPDisplay, guiradlblPWAMPDisplay, guiradlblPWADPDisplay);
            SetShape(guiradtxtOthDevPWASP, guiradtxtOthDevPWADP);

            // DefaultWindow.OnModeChangeDisableTimer += DisableTimer;
           
            // For Future Use
            // if (GuiCommon.BPDevice == GuiCommon.BPDevices.Sphygmocor)
            // {
                guipnlPWABPOtherDevice.Visible = false;
                guiradbtnGetBp.Text = "Start";
                guiradbtnAutoPWACancel.Text = "Cancel";
                guiradbtnAutoPWACancel.Visible = false;

            // }
            // For Future Use
            // else
            // {   
            //    guipnlPWABPOtherDevice.Visible = true;
            //    guiradbtnAutoPWACancel.Text = "Capture";
            //    guiradbtnAutoPWACancel.Visible = true;
            // }
        }

        void DefaultWindow_OnModeChangeDisableTimer(object sender, EventArgs e)
        {
            QuickStartTimer.Enabled = false;
            QSEnableRepeatBttnTimer.Enabled = false;
            QSProgressBarTimeStatusTimer.Enabled = false;
            WaitBtnTimer.Enabled = false;
            guiradlblBPProgressBar.Visible = false;
            guiradbtnAutoPWACancel.Visible = false;
            guiradbtnGetBp.Enabled = true;
            guiradbtnGetBp.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.BtnStart);
            guiradlblPWASPDisplay.Text = string.Empty;
            guiradlblPWAPPDisplay.Text = string.Empty;
            guiradlblPWAMPDisplay.Text = string.Empty;
            guiradlblPWADPDisplay.Text = string.Empty;
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

        private void guiradbtnGetBp_Click(object sender, EventArgs e)
        {
            int noOfAssessments = crxMgrObject.BpSettings.NumberofAssessments;
            timer = 0;

            // If Button text is "Get BP" or "Repeat"
             if ((guiradbtnGetBp.Text == oMsgMgr.GetMessage(CrxStructCommonResourceMsg.BtnStart)) || (guiradbtnGetBp.Text == oMsgMgr.GetMessage(CrxStructCommonResourceMsg.BtnRepeat)) || (guiradbtnGetBp.Text == oMsgMgr.GetMessage(CrxStructCommonResourceMsg.BtnWait)))
            {
                // To Check number of BP Measurements to be taken depending on Settings window dropdown   
                if (counter < noOfAssessments)
                {
                guiradlblBpAssessmentsStatus.Text = "Assessment: " + Convert.ToString(counter + 1) + " In Progress...";
                guiradlblBpAssessmentsStatus.Visible = true;

                // Clear all measurement labels
                guiradbtnGetBp.Enabled = true;
                guiradbtnGetBp.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.BtnStop);
                guiradbtnAutoPWACancel.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.BtnCancel);
                guiradbtnAssessmentsDetails.Visible = false;

                // GuiCommon.DefaultWindowForm.radtabCapture.Enabled = false;
                // GuiCommon.DefaultWindowForm.radtabReport.Enabled = false;
                // GuiCommon.DefaultWindowForm
                guiradlblPWASPDisplay.Text = string.Empty;
                guiradlblPWAPPDisplay.Text = string.Empty;
                guiradlblPWAMPDisplay.Text = string.Empty;
                guiradlblPWADPDisplay.Text = string.Empty;

                // Display Cuff Pressure labels
                guiradlblCuffPressure.Visible = true;
                guiradlblCuffPressureValue.Visible = true;
                guiradlblCuffPressureUnit.Visible = true;

                // Start the dummy timer to display BP readings
                QuickStartTimer.Enabled = true;

                // Hide progress bar
                guiradlblBPProgressBar.Visible = false;
                guiradbtnAutoPWACancel.Visible = false;

                // Stop cPWA and Repeat Button timers
                QSProgressBarTimeStatusTimer.Enabled = false;
                QSEnableRepeatBttnTimer.Enabled = false;

                // Reset Progressbar values
                guiradlblCuffPressureValue.Text = "0";
                guiradlblBPProgressBar.Minimum = 0;
                guiradlblBPProgressBar.Maximum = GuiCommon.AutoPWADelay;
                guiradlblBPProgressBar.Value1 = 0;
                guiradlblBPProgressBar.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.LblPwaSetupProgressBarEndMsg);
                counter++;
                }
            }
             else if (guiradbtnGetBp.Text == oMsgMgr.GetMessage(CrxStructCommonResourceMsg.BtnStop))
             {
                 counter = 0;
                 guiradlblBpAssessmentsStatus.Visible = false;
                 QuickStartTimer.Enabled = false;
                 guiradbtnGetBp.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.BtnRepeat);

                 // GuiCommon.DefaultWindowForm.radtabCapture.Enabled = true;
                 // GuiCommon.DefaultWindowForm.radtabReport.Enabled = true;
                 // GuiCommon.DefaultWindowForm.guiradgrpbxPwvDistanceMethod.Enabled = true;

                 // Display old values
                 guiradlblPWASPDisplay.Text = string.Empty + ((140 + 155 + 140 + 155 + 160) / 5);
                 guiradlblPWAPPDisplay.Text = string.Empty + ((60 + 50 + 70 + 70 + 70) / 5);
                 guiradlblPWAMPDisplay.Text = string.Empty + ((110 + 150 + 140 + 120 + 130) / 5);
                 guiradlblPWADPDisplay.Text = string.Empty + ((80 + 90 + 70 + 90 + 85) / 5);

                 guiradlblCuffPressure.Visible = false;
                 guiradlblCuffPressureValue.Visible = false;
                 guiradlblCuffPressureUnit.Visible = false;
             } 
        }

        private void guiradbtnAutoPWACancel_Click(object sender, EventArgs e)
        {
            if (guiradbtnAutoPWACancel.Text == "Cancel")
            {
                // Hide Progress Bar
                guiradlblBPProgressBar.Visible = false;

                // GuiCommon.DefaultWindowForm.radtabCapture.Enabled = true;
                // GuiCommon.DefaultWindowForm.radtabReport.Enabled = true;
                // GuiCommon.DefaultWindowForm.guiradgrpbxPwvDistanceMethod.Enabled = true;

                // Reset Progressbar values
                guiradlblBPProgressBar.Minimum = 0;
                guiradlblBPProgressBar.Maximum = GuiCommon.AutoPWADelay;
                guiradlblBPProgressBar.Value1 = 0;
                guiradlblBPProgressBar.Text = "PWA enabled in 0:15";
                guiradbtnAutoPWACancel.Text = "Capture";

                QSProgressBarTimeStatusTimer.Stop();
                QSProgressBarTimeStatusTimer.Enabled = false;
            }
            else
            {
                // For Future Use
                // Call a method to go to Capture Screen
                // GuiCommon.CaptureTabClick = false;
                // OnQSPWACapture_ClickEvent.Invoke(sender, e);
                // GuiCommon.CaptureTabClick = true;
            }
        }

        private void WaitBtnTimer_Tick(object sender, EventArgs e)
        {
            if (timer >= 55)
            {
                WaitBtnTimer.Enabled = false;
                guiradbtnGetBp.Enabled = true;
                guiradbtnGetBp.Text = "Repeat";
                guiradlblBPProgressBar.Visible = true;
                guiradbtnAutoPWACancel.Visible = true;
                
                // Start progress bar for auto capture
                QSProgressBarTimeStatusTimer.Enabled = true;
            }
            else
            {
                timer = timer + 1;
            }           
        }

        private void guiradbtnAssessmentsDetails_Click(object sender, EventArgs e)
        {
            BPAssessments objBpAssessment = new BPAssessments();
            objBpAssessment.Show();
        }       
       
        // End   : AtCor-<Drop2>-<Sprint1>, TM, Prototype,9th June, 2011
    }
}
