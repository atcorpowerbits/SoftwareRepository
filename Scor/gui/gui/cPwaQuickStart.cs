using System;
using System.Data;
using System.Drawing;
using System.Windows.Forms;
using Telerik.WinControls;
using AtCor.Scor.CrossCutting;
using AtCor.Scor.CrossCutting.Configuration;
using AtCor.Scor.CrossCutting.Logging;
using AtCor.Scor.CrossCutting.DatabaseManager;
using AtCor.Scor.CrossCutting.Messaging;
using Telerik.WinControls.UI;
using Telerik.WinControls.Primitives;
using AtCor.Scor.BusinessLogic;
using System.Collections;
using System.Configuration;
using System.Globalization;
using AtCor.Scor.DataAccess;
using System.Threading;

namespace AtCor.Scor.Gui.Presentation
{    
    public partial class cPwaQuickStart : Telerik.WinControls.UI.RadForm
    {       
        private int startIndex = -1;
        private int counter = 0;
        private int waitButtonDelay = 0, autoProgressbarDelay = 0;
        private int waitTimer = 0;
        private GuiCommon.BpButtonMode buttonMode = GuiCommon.BpButtonMode.start;
        private DefaultWindow objDefaultWindow;
        private int maxCuffPressure = 300;
       
        private ArrayList nibpSp = new ArrayList();
        private ArrayList nibpDp = new ArrayList();
        private ArrayList nibpMp = new ArrayList();
        private ArrayList nibpPp = new ArrayList();

        private delegate void DisplaySettingsDelegate(object sender, BizNIBPDataEventArgs e);

        /**This constructor is invoked when the form is called from the Default window.         
         */ 
        public cPwaQuickStart(DefaultWindow defWindow)
        {
            // set the default window
            objDefaultWindow = defWindow;          
            InitializeComponent();
            GuiCommon.SetShape(guiradlblPwaSpValue, guiradlblPwaDpValue, guiradlblPwaPpValue);
        }

        /**This method is used to Start the capture.
         */
        public void StartCapture()
        {
            try
            {
                GuiCommon.bizNibpObject.FinishBP();

                // Deepak: 8-Nov-2011 :disabling this as per Victor's suggestion
                // This is a temporary workaround bcuase GetConfigInfo return NACKeven 
                // after NIBP_DISCONNECT is sent                
                // CrxLogger.Instance.Write("GUI: cPwaQuickstart::StartCapture(). Not checking for device connection to pevent any problems associated with NIBP_DISCONNECT");
                if (DalModule.Instance.CheckIfDeviceIsConnected())
                {
                    FillSessionWithMeasurementValues();

                    if (GuiCommon.bizPwaobject.Validate())
                    {
                        // go to capture screen once electonic module is found & data is valid                   
                        GuiCommon.CaptureChildForm = new Capture(objDefaultWindow)
                        {
                            TopLevel = false,
                            Dock = DockStyle.Fill,
                            FormBorderStyle = FormBorderStyle.None
                        };

                        // adds capture form under parent window control
                        var page = objDefaultWindow.radtabCapture;
                        GuiCommon.CaptureChildForm.Parent = page;
                        page.Controls.Clear();

                        page.Controls.Add(GuiCommon.CaptureChildForm);
                        GuiCommon.CaptureChildForm.Show();
                        ResetMeasurementFields();
                        objDefaultWindow.radpgTabCollection.SelectedPage = objDefaultWindow.radtabCapture;

                        guiradbtnQuickStartGetBp.Enabled = true;
                        objDefaultWindow.guicmbxCurrentMode.Enabled = false;
                        objDefaultWindow.radtabCapture.Enabled = true;
                        objDefaultWindow.radtabReport.Enabled = false;
                        guiradbtnAutoPWACancel.Visible = false;

                        if (GuiCommon.ErrorInCaptureProcess)
                        {
                            GuiCommon.ErrorInCaptureProcess = false;
                            GuiCommon.CaptureChildForm.ShowQuickStartAfterCaptureAbort();
                            objDefaultWindow.guicmbxCurrentMode.Enabled = true;
                            objDefaultWindow.radtabQuickStart.Enabled = true;
                        }
                    }
                    else
                    {
                        if (GuiCommon.CaptureTabClick)
                        {
                            // whenever exception is thrown while validating measurement details,
                            // navigate the user back to Setup screen.                            
                            objDefaultWindow.radpgTabCollection.SelectedPage = objDefaultWindow.radtabQuickStart;
                        }

                        RadMessageBox.Show(this, CrxMessagingManager.Instance.GetMessage(CrxStructCommonResourceMsg.ErrorValidating), CrxMessagingManager.Instance.GetMessage(CrxStructCommonResourceMsg.SystemError), MessageBoxButtons.OK, RadMessageIcon.Error);
                        guiradbtnAutoPWACancel.Visible = false;
                        objDefaultWindow.guicmbxCurrentMode.Enabled = true;
                        objDefaultWindow.radtabCapture.Enabled = false;
                    }
                }
                else
                {
                    // device not connected show error message
                    RadMessageBox.Show(this, CrxMessagingManager.Instance.GetMessage(CrxStructCommonResourceMsg.CaptureDeviceErrMsg), CrxMessagingManager.Instance.GetMessage(CrxStructCommonResourceMsg.SystemError), MessageBoxButtons.OK, RadMessageIcon.Error);
                    if (GuiCommon.CaptureTabClick)
                    {
                        objDefaultWindow.radpgTabCollection.SelectedPage = objDefaultWindow.guiradgrpbxPwvDistanceMethod;
                        objDefaultWindow.guiradgrpbxPwvDistanceMethod.Enabled = true;
                    }

                    guiradbtnAutoPWACancel.Visible = false;
                    objDefaultWindow.guicmbxCurrentMode.Enabled = true;
                    objDefaultWindow.radtabCapture.Enabled = false;
                }
            }
            catch (Exception ex)
            {
               throw (ex);
            }
        }

        /**This method is used to disable the timers on the quickstart screen and enable the tabs on the default window.
         */
        public void DisableTimersAndResetTabs()
        {
            tmrGetCuffPressure.Enabled = tmrQsAutoPwa.Enabled = tmrWaitDuringAssessment.Enabled = false;

            if (GuiCommon.IsOnPwaReportForm)
            {
                objDefaultWindow.radtabReport.Enabled = true;
            }
            else
            {
                objDefaultWindow.radtabQuickStart.Enabled = true;
                objDefaultWindow.radtabCapture.Enabled = false;
                objDefaultWindow.radtabResult.Enabled = false;
                objDefaultWindow.guiradgrpbxPwvDistanceMethod.Enabled = true;
                objDefaultWindow.radtabReport.Enabled = false;
            }
        }

        /**This event is fired when the form is loaded,it is used to set the test of the controls. 
         */ 
        private void cPwaQuickStart_Load(object sender, EventArgs e)
        {
            try
            {
                tmrGetCuffPressure.Interval = DalModule.Instance.NibpCuffDataInterval;
                waitButtonDelay = CrxSytemParameters.Instance.GetIntegerTagValue("NIBP.Repeat.Rest");
                autoProgressbarDelay = CrxSytemParameters.Instance.GetIntegerTagValue("NIBP.AutoPWA.Rest");
                SetTextForGuiControls();
                guiradprgBarCuffPressure.Minimum = 0;
                guiradprgBarCuffPressure.Maximum = maxCuffPressure;
                guiradprgBarCuffPressure.Value1 = 0;
                objDefaultWindow.radlblMessage.Text = string.Empty;

                DisableTabs();
                EnableDisablePatientTab(true);

                // This code is written so that below event is subscribed only for QuickStart mode and not for Setup
                if (GuiCommon.StartupScreen.ToUpper() == CrxMessagingManager.Instance.GetMessage(CrxStructCommonResourceMsg.QuickStart).ToUpper())
                {
                    BizEventContainer.Instance.OnBizNIBPDataEvent += new BizNIBPDataEventHandler(Instance_OnBizNIBPDataEvent);
                }

                GuiCommon.FromQuickStart = true;

                objDefaultWindow.guiradmnuDatabase.Enabled = false;
                objDefaultWindow.radtabReport.Enabled = false;
                objDefaultWindow.guicmbxCurrentMode.Enabled = true;
            }
            catch (Exception ex)
            {
                GUIExceptionHandler.HandleException(ex, this);                
            }
        }

        /**This method is used to set the test on the controls.
         */ 
        private void SetTextForGuiControls()
        {
            try
            {
                guiradlblPwaSp.Text = CrxMessagingManager.Instance.GetMessage(CrxStructCommonResourceMsg.LabelSp);
                guiradlblPwaPp.Text = CrxMessagingManager.Instance.GetMessage(CrxStructCommonResourceMsg.LblPP) + ":";
                guiradlblPwaDp.Text = CrxMessagingManager.Instance.GetMessage(CrxStructCommonResourceMsg.LabelDp);
                guiradlblPwaMap.Text = CrxMessagingManager.Instance.GetMessage(CrxStructCommonResourceMsg.LblReportPwaBrachialMp);
                guiradbtnQuickStartGetBp.Text = CrxMessagingManager.Instance.GetMessage(CrxStructCommonResourceMsg.BtnStart);
                guiradbtnAutoPWACancel.Text = CrxMessagingManager.Instance.GetMessage(CrxStructCommonResourceMsg.BtnCapture);
                guiradlblQuickStartWarning.Text = CrxMessagingManager.Instance.GetMessage(CrxStructCommonResourceMsg.QuickStartWarning);
            }
            catch (Exception ex)
            {
                GUIExceptionHandler.HandleException(ex, this);
            }
        }
        
        private void QuickStartGetBP()
        {
            GuiCommon.IsReportGenerated = false;

            try
            {
                if ((buttonMode == GuiCommon.BpButtonMode.start) || (buttonMode == GuiCommon.BpButtonMode.repeat) || (buttonMode == GuiCommon.BpButtonMode.stopWait))
                {
                    guiradbtnQuickStartGetBp.Text = CrxMessagingManager.Instance.GetMessage(CrxStructCommonResourceMsg.BtnStop);
                    buttonMode = GuiCommon.BpButtonMode.stopInProgress;
                    objDefaultWindow.guicmbxCurrentMode.Enabled = false;
                    objDefaultWindow.guiradmnuScor.Enabled = false;
                    objDefaultWindow.radtabCapture.Enabled = false;
                    guiradprgbarAutoPwa.Minimum = 0;
                    guiradprgbarAutoPwa.Maximum = autoProgressbarDelay;
                    guiradprgbarAutoPwa.Value1 = 0;
                    ResetMeasurementFields();
                    guiradbtnAutoPWACancel.Text = CrxMessagingManager.Instance.GetMessage(CrxStructCommonResourceMsg.BtnCancel);
                    guiradbtnAutoPWACancel.Visible = false;                    
                    if (GuiCommon.bizNibpObject.StartAdultBP())
                    {
                        guiradprgBarCuffPressure.Visible = true;
                        EnableDisablePatientTab(false);
                        tmrGetCuffPressure.Start();
                    }                    
                    else
                    {
                        guiradbtnQuickStartGetBp.Text = CrxMessagingManager.Instance.GetMessage(CrxStructCommonResourceMsg.BtnStart);
                        buttonMode = GuiCommon.BpButtonMode.start;
                        objDefaultWindow.guicmbxCurrentMode.Enabled = true;
                        objDefaultWindow.guiradmnuScor.Enabled = true;
                    }
                }
                else if (buttonMode == GuiCommon.BpButtonMode.stopInProgress || buttonMode == GuiCommon.BpButtonMode.stopInWaitProgress)
                {
                    EnableDisablePatientTab(true);
                    waitTimer = 0;
                    tmrWaitDuringAssessment.Stop();
                    tmrWaitDuringAssessment.Enabled = false;
                    tmrGetCuffPressure.Stop();
                    tmrQsAutoPwa.Stop();
                    objDefaultWindow.guicmbxCurrentMode.Enabled = true;                    
                    objDefaultWindow.guiradmnuScor.Enabled = true;
                    GuiCommon.bizNibpObject.AbortBP();

                    // Reset Progressbar values
                    guiradprgBarCuffPressure.Value1 = 0;
                   
                    if (counter > 0)
                    {
                        SetAvgBpMeasurementData(); 
                        guiradbtnAutoPWACancel.Text = CrxMessagingManager.Instance.GetMessage(CrxStructCommonResourceMsg.BtnCapture);
                        guiradbtnAutoPWACancel.Visible = true;
                        objDefaultWindow.radtabCapture.Enabled = true;
                    }
                    
                    counter = 0;
                    objDefaultWindow.radlblMessage.Text = string.Empty;                    
                    guiradbtnQuickStartGetBp.Text = CrxMessagingManager.Instance.GetMessage(CrxStructCommonResourceMsg.BtnStart);
                    buttonMode = GuiCommon.BpButtonMode.repeat;
                    guiradprgBarCuffPressure.Visible = false; 
                }
            }
            catch (Exception ex)
            {
                throw (ex);                
            } 
        }

        /**This event is fired when the user clicks on the GetBp button.This button is used to start, stop and repeat the nibp simulation.
         */
        private void guiradbtnQuickStartGetBp_Click(object sender, EventArgs e)
        {
            try
            {
                // Deepak: this is temporary. TODO
                if (!DalModule.Instance.CheckIfDeviceIsConnected() && (buttonMode == GuiCommon.BpButtonMode.start))
                {
                    RadMessageBox.Show(this, CrxMessagingManager.Instance.GetMessage(CrxStructCommonResourceMsg.CaptureDeviceErrMsg), CrxMessagingManager.Instance.GetMessage(CrxStructCommonResourceMsg.SystemError), MessageBoxButtons.OK, RadMessageIcon.Error);
                    return;
                }

                QuickStartGetBP();
            }
            catch (Exception ex)
            {
                GUIExceptionHandler.HandleException(ex, this);
                DisableTimersAndResetTabs();
                objDefaultWindow.guiradmnuScor.Enabled = true;
                objDefaultWindow.guicmbxCurrentMode.Enabled = true;  
            }
        }

        /**This event is fired from the BLL,it is used tofetch the values for SP,DP,PP and MAP
         */ 
        private void Instance_OnBizNIBPDataEvent(object sender, BizNIBPDataEventArgs e)
        {
            try
            {
                if (e.nibpSuccess)
                {
                    if (guiradbtnQuickStartGetBp.InvokeRequired)
                    {
                        guiradbtnQuickStartGetBp.Invoke(new MethodInvoker(delegate
                        {
                            tmrGetCuffPressure.Stop();
                            guiradprgBarCuffPressure.Value1 = 0;
                            guiradprgBarCuffPressure.Visible = false;
                        }));
                    }

                    // These values are printed in the log to verify if the average for each assessment is calculated properly.
                    CrxLogger.Instance.Write("On Quickstart Value for SYS:" + GuiCommon.bizNibpObject.newSP);
                    CrxLogger.Instance.Write("On Quickstart  Value for DIA:" + GuiCommon.bizNibpObject.newDP);
                    CrxLogger.Instance.Write("On Quickstart Value for MAP:" + GuiCommon.bizNibpObject.newMP);
                    CrxLogger.Instance.Write("On Quickstart  Value for PP:" + GuiCommon.bizNibpObject.newPP);

                    nibpSp.Add(GuiCommon.bizNibpObject.newSP);
                    nibpDp.Add(GuiCommon.bizNibpObject.newDP);
                    nibpMp.Add(GuiCommon.bizNibpObject.newMP);
                    nibpPp.Add(GuiCommon.bizNibpObject.newPP);

                    if (CrxConfigManager.Instance.BpSettings.NumberofAssessments > 1 && counter < CrxConfigManager.Instance.BpSettings.NumberofAssessments - 1)
                    {
                        if (buttonMode != GuiCommon.BpButtonMode.stopInWaitProgress)
                        {
                            objDefaultWindow.radlblMessage.Text = "                  " + CrxMessagingManager.Instance.GetMessage(CrxStructCommonResourceMsg.BtnWait);
                            if (guiradbtnQuickStartGetBp.InvokeRequired)
                            {
                                guiradbtnQuickStartGetBp.Invoke(new MethodInvoker(delegate
                                {
                                    ShowBpMeasurement();
                                    guiradbtnQuickStartGetBp.Visible = true;
                                    guiradbtnQuickStartGetBp.Text = CrxMessagingManager.Instance.GetMessage(CrxStructCommonResourceMsg.BtnStop);
                                    tmrWaitDuringAssessment.Start();
                                    guiradprgbarAutoPwa.Visible = false;
                                    counter++;
                                }));
                            }
                        }
                    }
                    else
                    {
                        if (guiradbtnQuickStartGetBp.InvokeRequired)
                        {
                            guiradbtnQuickStartGetBp.Invoke(new MethodInvoker(delegate
                            {
                                SetAvgBpMeasurementData();
                                guiradbtnQuickStartGetBp.Visible = true;
                                guiradbtnQuickStartGetBp.Text = CrxMessagingManager.Instance.GetMessage(CrxStructCommonResourceMsg.BtnStart);
                                buttonMode = GuiCommon.BpButtonMode.repeat;
                                counter = 0;
                                objDefaultWindow.radlblMessage.Text = string.Empty;
                                guiradbtnAutoPWACancel.Visible = true;
                                if (CrxConfigManager.Instance.BpSettings.AutoPWASP || CrxConfigManager.Instance.BpSettings.AutoPWAPP || CrxConfigManager.Instance.BpSettings.AutoPWADP)
                                {
                                    guiradprgbarAutoPwa.Visible = false;
                                    guiradbtnQuickStartGetBp.Enabled = false;

                                    // Start progress bar for auto capture
                                    tmrQsAutoPwa.Start();
                                    guiradprgBarCuffPressure.Visible = false;
                                }
                                else
                                {
                                    objDefaultWindow.guiradmnuScor.Enabled = true;
                                    objDefaultWindow.radtabCapture.Enabled = true;
                                    objDefaultWindow.guicmbxCurrentMode.Enabled = true;
                                    guiradbtnAutoPWACancel.Text = CrxMessagingManager.Instance.GetMessage(CrxStructCommonResourceMsg.BtnCapture);
                                }
                            }));
                        }
                    }
                }
                else
                {
                    if (guipnlPWAMeasurementDetails.InvokeRequired)
                    {
                        guipnlPWAMeasurementDetails.Invoke(new MethodInvoker(delegate
                        {
                            RadMessageBox.Show(this, CrxMessagingManager.Instance.GetMessage(CrxStructCommonResourceMsg.NIBPValidationFailed), CrxMessagingManager.Instance.GetMessage(CrxStructCommonResourceMsg.SystemError), MessageBoxButtons.OK, RadMessageIcon.Error);
                            objDefaultWindow.guicmbxCurrentMode.Enabled = true;
                            objDefaultWindow.guiradmnuScor.Enabled = true;
                            if (counter > 0)
                            {
                                SetAvgBpMeasurementData();
                                guiradbtnAutoPWACancel.Text = CrxMessagingManager.Instance.GetMessage(CrxStructCommonResourceMsg.BtnCapture);
                                guiradbtnAutoPWACancel.Visible = true;
                                objDefaultWindow.radtabCapture.Enabled = true;
                                guiradbtnQuickStartGetBp.Text = CrxMessagingManager.Instance.GetMessage(CrxStructCommonResourceMsg.BtnStart);
                                buttonMode = GuiCommon.BpButtonMode.repeat;
                                objDefaultWindow.radlblMessage.Text = string.Empty;
                                SetAvgBpMeasurementData();
                            }
                        }));
                    }
                }
            }
            catch (Exception ex)
            {
                GUIExceptionHandler.HandleException(ex, this);
            }
        }

        /**This event is fired on th tick of the Cuff pressure timer.
         * In this method on every tick ,cuff pressure values are read from DAl and assigned to the progress bar to show the status of cuff pressure.
         */ 
        private void tmrGetCuffPressure_Tick(object sender, EventArgs e)
        {
            try
            {
                DalPwvDataStruct nibpStruct;
                ushort cuffPressureValue = 0;
                DalDataBuffer databufferObject = DalDataBuffer.Instance;
                int returnedValues = databufferObject.GetNextValues(1, ref startIndex);

                if (returnedValues == 0)
                {
                    return;
                }

                // Deepak: Offset should start from 0 not from 1. Correcting problem                
                nibpStruct = databufferObject.GetValueAt(startIndex, 0);

                // Display reading values
                // When measurement is in wait mode guiradbtnGetBp is visible
                guiradbtnQuickStartGetBp.Visible = true;
                guiradbtnQuickStartGetBp.Text = CrxMessagingManager.Instance.GetMessage(CrxStructCommonResourceMsg.BtnStop); 
                cuffPressureValue = nibpStruct.cuffPressure;                                   
                objDefaultWindow.radlblMessage.Text = string.Format(CrxMessagingManager.Instance.GetMessage(CrxStructCommonResourceMsg.GuiNibpAssessmentProgressMsg), (counter + 1));
                if (cuffPressureValue > maxCuffPressure)
                {
                    CrxLogger.Instance.Write("The cuff pressure progress bar value cannot be set to a value which is greater than its max value. The value is " + cuffPressureValue, ErrorSeverity.Error);
                }
                else
                {
                    guiradprgBarCuffPressure.Value1 = cuffPressureValue;
                }
            }
            catch (Exception ex)
            {
                GUIExceptionHandler.HandleException(ex, this);
            }
        }

        /**This method is used to show the Bp Measurement on the GUI.
         */ 
        private void ShowBpMeasurement()
        {
            guiradlblPwaSpValue.Text = GuiCommon.bizNibpObject.newSP.ToString();
            guiradlblPwaPpValue.Text = GuiCommon.bizNibpObject.newPP.ToString();
            guiradlblPwaDpValue.Text = GuiCommon.bizNibpObject.newDP.ToString();
            guiradlblPwaMapValue.Text = GuiCommon.bizNibpObject.newMP.ToString();
        }

        /**This method is used to call a method to calculate the average bp measurement.
         */ 
        private void SetAvgBpMeasurementData()
        {
            try
            {
                CalcuateAverage(nibpSp, guiradlblPwaSpValue);
                CalcuateAverage(nibpDp, guiradlblPwaDpValue);
                CalcuateAverage(nibpPp, guiradlblPwaPpValue);
                CalcuateAverage(nibpMp, guiradlblPwaMapValue);
                nibpDp.Clear();
                nibpMp.Clear();
                nibpPp.Clear();
                nibpSp.Clear();
            }
            catch (Exception ex)
            {
                GUIExceptionHandler.HandleException(ex, this);
            }
        }        

        /**This method is used to calculate average value for Bp measurement.
         */ 
        private void CalcuateAverage(ArrayList list, RadLabel labelName)
        {
            try
            {
                int sum = 0;
                double average = 0;
                foreach (ushort i in list)
                {
                    sum = sum + i;
                }

                average = sum / list.Count;
                labelName.Text = Math.Round(average).ToString();
            }
            catch (Exception ex)
            {
                throw (ex);
            }
        }

        /**This event is fired on the tick of the Wait timer.        
        */ 
        private void tmrWaitDuringAssessment_Tick(object sender, EventArgs e)
        {
            try
            {                
                objDefaultWindow.radlblMessage.Text = "                  " + CrxMessagingManager.Instance.GetMessage(CrxStructCommonResourceMsg.BtnWait);
               
                guiradbtnQuickStartGetBp.Visible = true;                
                if (waitTimer >= (waitButtonDelay - 1))
                {
                    buttonMode = GuiCommon.BpButtonMode.stopWait;
                    tmrWaitDuringAssessment.Stop();
                    waitTimer = 0;
                    objDefaultWindow.radlblMessage.Text = string.Empty; 
                    QuickStartGetBP();
                    guiradbtnQuickStartGetBp.Visible = true;
                }
                else
                {
                    buttonMode = GuiCommon.BpButtonMode.stopInWaitProgress;
                    waitTimer += 1;
                }
            }
            catch (Exception ex)
            {
                GUIExceptionHandler.HandleException(ex, this);
            }
        }

        /**This event is fired on th tick of the Cuff pressure timer.
        * In this method on every tick, the auto Pwa progress bar is shown.
        */  
        private void tmrQsAutoPwa_Tick(object sender, EventArgs e)
        {
            try
            {
                if (guiradprgbarAutoPwa.Value1 >= autoProgressbarDelay)
                {
                    objDefaultWindow.radlblMessage.Text = string.Empty;

                    // Stop Progress bar if the value exceeds cPWA Delay
                    tmrQsAutoPwa.Enabled = false;

                    // Hide Progress Bar
                    guiradprgbarAutoPwa.Visible = false;
                    guiradbtnAutoPWACancel.Visible = false;

                    // fill the biz session object with measurement details
                    // if validation succeeds start capture process
                    CrxPwaCaptureInput pwaCaptureInput = new CrxPwaCaptureInput();
                    bool value = GuiCommon.bizPwaobject.GetCurrentCaptureInput(ref pwaCaptureInput);
                    if (!Convert.ToInt32(pwaCaptureInput).Equals(CrxConfigManager.Instance.PwaSettings.CaptureInput))
                    {
                        GuiCommon.bizPwaobject.Initialise(CrxConfigManager.Instance.PwaSettings.CaptureInput.Equals(Convert.ToInt32(CrxPwaCaptureInput.Tonometer)) ? CrxPwaCaptureInput.Tonometer : CrxPwaCaptureInput.Cuff);
                    }

                    GuiCommon.CaptureTabClick = false;

                    objDefaultWindow.radtabCapture.Enabled = true;
                    objDefaultWindow.guiradmnuScor.Enabled = true;
                    objDefaultWindow.guicmbxCurrentMode.Enabled = true;
                    objDefaultWindow.radpgTabCollection.SelectedPage = objDefaultWindow.radtabCapture;
                    // Commenting below line as part of reivew comment.
                    // GuiCommon.CaptureTabClick = true;
                }           
                else
                {
                    // Increment progress bar after every second
                    tmrGetCuffPressure.Stop();
                    
                    int displayValue = guiradprgbarAutoPwa.Maximum - guiradprgbarAutoPwa.Value1;
                    guiradprgbarAutoPwa.Value1 = guiradprgbarAutoPwa.Value1 + 1;                  
                    objDefaultWindow.radlblMessage.Text = string.Format(CrxMessagingManager.Instance.GetMessage(CrxStructCommonResourceMsg.LblPwaSetupProgressBarStartMsg), displayValue.ToString());                   
                }
            }
            catch (Exception ex)
            {
                // In case of any exception being raised in the StartCaptureProcess(sender, e);
                // Commenting below line as part of reivew comment.
                // GuiCommon.CaptureTabClick = true;
                GUIExceptionHandler.HandleException(ex, this);
            }
        }

        /**This methods is used to fill the Biz PWA object with Bp measurement.
       */
        private void FillSessionWithMeasurementValues()
        {
            try
            {
                GuiCommon.bizPwaobject.Sp = string.IsNullOrEmpty(guiradlblPwaSpValue.Text) ? GuiConstants.DefaultValue : float.Parse(guiradlblPwaSpValue.Text);
                GuiCommon.bizPwaobject.Dp = string.IsNullOrEmpty(guiradlblPwaDpValue.Text) ? GuiConstants.DefaultValue : float.Parse(guiradlblPwaDpValue.Text);
                GuiCommon.bizPwaobject.MeanP = string.IsNullOrEmpty(guiradlblPwaMapValue.Text) ? GuiConstants.DefaultValue : float.Parse(guiradlblPwaMapValue.Text);
                GuiCommon.bizPwaobject.heightAndWeight.heightInCentimetres = GuiConstants.DefaultValue;
                GuiCommon.bizPwaobject.heightAndWeight.heightInInches = GuiConstants.DefaultValue;
                GuiCommon.bizPwaobject.MeasureType = PWA_MEASURE_TYPE.PWA_RADIAL;
                GuiCommon.bizPwaobject.systemId = GuiConstants.DefaultValue;
                GuiCommon.bizPwaobject.sampleRate = GuiConstants.DefaultValue;
                GuiCommon.bizPwaobject.patientNumber = GuiConstants.DefaultValue;
                GuiCommon.bizPwaobject.sampleRate = 256;
            }
            catch (Exception ex)
            {
                GUIExceptionHandler.HandleException(ex, this);
            }
        }

        /**This method is used to reset the Bp meausrement labels on the form.
         */
        private void ResetMeasurementFields()
        {
            guiradlblPwaSpValue.Text = string.Empty;
            guiradlblPwaPpValue.Text = string.Empty;
            guiradlblPwaDpValue.Text = string.Empty;
            guiradlblPwaMapValue.Text = string.Empty;
        }

        /**This event is fired when the user clicks on the Cancel/Capture button.
         */
        private void guiradbtnAutoPWACancel_Click(object sender, EventArgs e)
        {
            try
            {
                if (guiradbtnAutoPWACancel.Text == CrxMessagingManager.Instance.GetMessage(CrxStructCommonResourceMsg.BtnCancel))
                {
                    EnableDisablePatientTab(true);

                    // Hide Progress Bar
                    guiradprgbarAutoPwa.Visible = false;
                    guiradbtnQuickStartGetBp.Enabled = true;
                    guiradbtnQuickStartGetBp.Text = CrxMessagingManager.Instance.GetMessage(CrxStructCommonResourceMsg.BtnStart);
                    buttonMode = GuiCommon.BpButtonMode.repeat;

                    // Reset Progressbar values
                    guiradprgbarAutoPwa.Minimum = 0;
                    guiradprgbarAutoPwa.Maximum = autoProgressbarDelay;
                    guiradprgbarAutoPwa.Value1 = 0;
                    objDefaultWindow.radtabCapture.Enabled = true;
                    objDefaultWindow.radlblMessage.Text = string.Empty;

                    guiradbtnAutoPWACancel.Text = CrxMessagingManager.Instance.GetMessage(CrxStructCommonResourceMsg.BtnCapture);

                    tmrQsAutoPwa.Stop();
                    tmrQsAutoPwa.Enabled = false;
                    if (guiradbtnQuickStartGetBp.Text == CrxMessagingManager.Instance.GetMessage(CrxStructCommonResourceMsg.BtnStart) && (!tmrQsAutoPwa.Enabled))
                    {
                        objDefaultWindow.guiradmnuScor.Enabled = true;
                        objDefaultWindow.guicmbxCurrentMode.Enabled = true;
                    }
                }
                else
                {
                   
                        // Coding for PWA mode.
                        CrxPwaCaptureInput pwaCaptureInput = new CrxPwaCaptureInput();
                        bool value = GuiCommon.bizPwaobject.GetCurrentCaptureInput(ref pwaCaptureInput);
                        if (!Convert.ToInt32(pwaCaptureInput).Equals(CrxConfigManager.Instance.PwaSettings.CaptureInput))
                        {
                            GuiCommon.bizPwaobject.Initialise(CrxConfigManager.Instance.PwaSettings.CaptureInput.Equals(Convert.ToInt32(CrxPwaCaptureInput.Tonometer)) ? CrxPwaCaptureInput.Tonometer : CrxPwaCaptureInput.Cuff);
                        }
                        GuiCommon.CaptureTabClick = false;
                        objDefaultWindow.radtabCapture.Enabled = true;
                        objDefaultWindow.radpgTabCollection.SelectedPage = objDefaultWindow.radtabCapture;
                        guiradbtnAutoPWACancel.Visible = false;
                        // Commenting below line as part of reivew comment.
                        // GuiCommon.CaptureTabClick = true;                   
                }
            }
            catch (Exception ex)
            {
                // Commenting below line as part of reivew comment.
                // GuiCommon.CaptureTabClick = true;

                // In case of any exception being raised in the StartCaptureProcess(sender, e);
                GUIExceptionHandler.HandleException(ex, this);
            }
        }

        /**This method is used to disable the tabs on the default window.
         */
        private void DisableTabs()
        {
            // Disable Capture,Result, Patient and Report tab.
            objDefaultWindow.radtabCapture.Enabled = false;
            objDefaultWindow.radtabReport.Enabled = false;
            objDefaultWindow.radtabResult.Enabled = false;
            objDefaultWindow.guiradgrpbxPwvDistanceMethod.Enabled = false;
        }

        /**This event is fired when the form is closed. 
         */
        private void cPwaQuickStart_FormClosing(object sender, FormClosingEventArgs e)
        {
            try
            {
                if (GuiCommon.StartupScreen.ToUpper().Equals(CrxStructCommonResourceMsg.QuickStart))
                {
                    DisableTimersAndResetTabs();
                }
            }
            catch (Exception ex)
            {
                GUIExceptionHandler.HandleException(ex, this);
            }
        }

        /**This method is used to enable /disable the patient tab when the nibp measurement is in progress.
        */
        private void EnableDisablePatientTab(bool value)
        {
            if ((GuiCommon.CurrentMode.Equals(CrxStructCommonResourceMsg.Pwa) && objDefaultWindow.guiradgrpbxPwvDistanceMethod.Text.Equals(CrxMessagingManager.Instance.GetMessage(CrxStructCommonResourceMsg.TabPatient))))
            {
                if (value)
                {
                    objDefaultWindow.guiradgrpbxPwvDistanceMethod.Enabled = value;
                }
                else
                {
                    objDefaultWindow.guiradgrpbxPwvDistanceMethod.Enabled = value;
                }
            }
        }       
    }
}
