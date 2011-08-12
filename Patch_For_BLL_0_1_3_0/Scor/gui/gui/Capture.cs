/*
     Copyright (C) ATCOR MEDICAL PTY LTD, 2010
 
     Filename     :     Capture screen
        
     Author       :     Nitesh Chhedda
 
     Description  :     Functionality implemented for Capture.
*/
using System;
using System.Drawing;
using System.Windows.Forms;
using Telerik.WinControls.Primitives;
using Telerik.WinControls;
using System.Windows.Forms.DataVisualization.Charting;
using AtCor.Scor.CrossCutting.Messaging;
using AtCor.Scor.BusinessLogic;
using AtCor.Scor.CrossCutting.Configuration;
using AtCor.Scor.CrossCutting.DatabaseManager;
using AtCor.Scor.CrossCutting.Logging;
using AtCor.Scor.DataAccess;
using System.Configuration;

namespace AtCor.Scor.Gui.Presentation
{
    public partial class Capture : Telerik.WinControls.UI.RadForm
    {
        #region Set constant values

        const int HandShakePeriod = 2;
        const int SampleRate = 256;
        const int TonometerHeight = 300;
        const int QualityIndicatorHeight = 500;
        const int TwoSecondsWindow = 512;
/*
        const int YCordinateForPlottingStraightLine = 600;
*/  
        const int RequestedValues = 32;
        const int GoodFemoralQualityIndicatorValue = 80;
        const int BadFemoralQualityIndicatorValue = 20;
        readonly CrxMessagingManager oMsgMgr = CrxMessagingManager.Instance;
        readonly CrxDBManager dbMagr = CrxDBManager.Instance;
        static uint xCoordinateTonometer = 0;
        static uint xCoordinateFemoralCuff = 0;
        private DefaultWindow objDefaultWindow;
        bool carotidFlag = false; // to check for carotid quality indicator
        bool femoralFlag = false; // to check for femoral quality indicator        
        volatile bool femoralPlotSwitch = false;
        volatile bool cuffstatechangeFlag = false;

        #endregion              

        public static event EventHandler OnReportTabClick;

        public static event EventHandler OnPWAReportTabClick;

        Series newSeries;
        Series femoralCuffSeries;

        double screenwidth;
        double signalStrength;
        ProgressBarPrimitive prim1;
        ProgressBarPrimitive prim2;

        // object of Config Manager                 
        CrxConfigManager obj;
        BizPWV bizObj;

        public Capture()
        {
            InitializeComponent();
            GuiCommon.SetFontForControls(this);
            SetTextForCaptureTab();            
        }
        
        public Capture(DefaultWindow defWindow)
        {
            InitializeComponent();
            GuiCommon.SetFontForControls(this);
            SetTextForCaptureTab();
            objDefaultWindow = defWindow;
        }       

        /** This event is fired when the user clicks on the cross button.
        */
        public void radbtnCross_Click(object sender, EventArgs e)
        {
            timer1.Enabled = false;

            // bizObj.SaveCaptureData();
            // string captureFilePath = DalModule.Instance.GetSavedFilePath();
            // RadMessageBox.Show(this, oMsgMgr.GetMessage(CrxStructCommonResourceMsg.GuiWaveformSaveMsg) + Environment.NewLine + captureFilePath, oMsgMgr.GetMessage(CrxStructCommonResourceMsg.SystemError), MessageBoxButtons.OK, RadMessageIcon.Error);            
            GenerateReportWhenCaptureIsEnabled();
        }

        /** This method is called to set the text for the label controls.
         */
        private void SetTextForCaptureTab()
        {
            try
            {
                guiradlblCarotidTonometer.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.LblTonometer);
                guiradlblFemoralCuff.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.LblFemoralcuff);
                radlblTimeStatus.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.LblTimestatus);
                radbtnTick.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.BtnOk);
                radbtnCross.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.BtnCancel);
            }
            catch (Exception ex)
            {
                GUIExceptionHandler.HandleException(ex, this);
            }
        }

        /** This event is raised on the load of the window,here the methods for plotting the tonometer and femoral cuff waveforms are written.
         * If any exception occurs it will be caught and displayed to the user using a message box.
         *The corresponding exception will also be logged in the log file.
         */
        private void Capture_Load(object sender, EventArgs e)
        {
            try
            {
                objDefaultWindow.guicmbxCurrentMode.Enabled = false;  
                GuiCommon.CaptureFormLoaded = true;
                bizObj = (BizPWV)BizSession.Instance().measurement;
                                
                radbtnCross.Focus();

                // tmrInflationTimer.Enabled = true;                
                obj = CrxConfigManager.Instance;
                obj.GetGeneralUserSettings();
                obj.GetPwvUserSettings();

                BizEventContainer.Instance.OnBizCarotidQualityEvent += qualityIndicator_CarotidQualityEvent;
                BizEventContainer.Instance.OnBizFemoralQualityEvent += qualityIndicator_FemoraCuffEvent;
                BizEventContainer.Instance.OnBizCuffStateEvent += UpdateCuffState;
                DefaultWindow.OnCaptureScreenTabClick += Capture_OnCaptureScreenTabClick;
                GuiCommon.OnBizErrorEventInvocation += GuiCommon_OnBizErrorEventInvocation;  
                SetTonometerWaveformProperties();
                SetFemoralCuffWaveformProperties(); // setting femoral properties as need to show flat line 
                StartCarotidTonometerCapture();

                // initially make progress bar & labels invisible
                guiradprgbarTimeToInflatioDeflation.Visible = false;
                radlblTimeStatus.Visible = false;
                guiradprgbarTimeToInflatioDeflation.Value1 = 0;
                guiradprgbarTimeToInflatioDeflation.Maximum = 0;

                // Quality indicator ProgressBarSetup
                prim1 = (ProgressBarPrimitive)radProgressBarQualityIndicator.ProgressBarElement.Children[1];
                prim2 = (ProgressBarPrimitive)radProgressBarFemoralIndicator.ProgressBarElement.Children[1];
                radProgressBarQualityIndicator.Minimum = 0;
                radProgressBarQualityIndicator.Maximum = QualityIndicatorHeight;                

                // Here enabling and disabling the capture button in order to make the capture button look rounded.
                radbtnTick.Enabled = true;
                radbtnTick.Enabled = false;

                // disable settings, backup, restore & cross button
                objDefaultWindow.guiradmnuitemSettings.Enabled = false;
                objDefaultWindow.guiradmnuSystemKey.Enabled = false;

                objDefaultWindow.guiradmnuScor.Enabled = false;

                // disable seup & report tabs
                objDefaultWindow.radtabReport.Enabled = false;
                objDefaultWindow.guiradgrpbxPwvDistanceMethod.Enabled = false;               

                DisplayCaptureTime();                
            }
            catch (Exception ex)
            {
                StopTimers();
                GUIExceptionHandler.HandleException(ex, this);
            }
        }

        private void GuiCommon_OnBizErrorEventInvocation(object sender, EventArgs e)
        {
            Invoke(new EventHandler(radbtnCross_Click));
        }

        /** This method displays capture time in bottom area
         * */
        void DisplayCaptureTime()
        {
            // set capture time in labels
            CrxConfigManager config = CrxConfigManager.Instance;
            switch (config.PwvSettings.CaptureTime)
            {
                case (int)CrxGenPwvValue.CrxPwvCapture5Seconds:
                    objDefaultWindow.radlblCaptureTime.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.GrpCaptureTime) + oMsgMgr.GetMessage(CrxStructCommonResourceMsg.GuiDisplayColon) + oMsgMgr.GetMessage(CrxStructCommonResourceMsg.Rad5Sec);
                    break;

                case (int)CrxGenPwvValue.CrxPwvCapture10Seconds:
                    objDefaultWindow.radlblCaptureTime.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.GrpCaptureTime) + oMsgMgr.GetMessage(CrxStructCommonResourceMsg.GuiDisplayColon) + oMsgMgr.GetMessage(CrxStructCommonResourceMsg.Rad10Sec);                    
                    break;

                case (int)CrxGenPwvValue.CrxPwvCapture20Seconds:
                    objDefaultWindow.radlblCaptureTime.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.GrpCaptureTime) + oMsgMgr.GetMessage(CrxStructCommonResourceMsg.GuiDisplayColon) + oMsgMgr.GetMessage(CrxStructCommonResourceMsg.Rad20Sec);
                    break;

                default:
                    break;
            }
        }
        
        /**This event is called when the cuff state is changed.
        * Depending upon which is the currrent cuff state the femoral cuff is plotted.
        * * If any exception occurs it will be caught and displayed to the user using a message box.
        *The corresponding exception will also be logged in the log file.
        */
        private void UpdateCuffState(object sender, BizCuffStateEventArgs e)
        {
            try
            {
                // value "inflated" is coming from biz e.data which determines whether cuff state is inflated or not
                // used for internal purpose
                if (e.data.ToLower().Equals("inflated"))
                {
                    guiradprgbarTimeToInflatioDeflation.Visible = true;
                    objDefaultWindow.radlblMessage.Text = string.Empty;
                    radlblTimeStatus.Visible = true;

                    objDefaultWindow.radlblMessage.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.GuiCaptureCuffInflated);
                    cuffstatechangeFlag = true;
                    femoralPlotSwitch = true;
                    objDefaultWindow.radlblCaptureTime.Visible = true;
                }
                else
                {
                    objDefaultWindow.radlblMessage.Text = string.Empty;
                    femoralPlotSwitch = false;
                    cuffstatechangeFlag = false;
                    guiradprgbarTimeToInflatioDeflation.Value1 = 0;
                    guiradprgbarTimeToInflatioDeflation.Update();

                    // make progress bar, time to deflation invisible & show cross
                    radlblTimeStatus.Visible = false;
                    objDefaultWindow.radlblMessage.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.GuiCaptureDeflatedMsg);

                    // make progress bar invisible & show cross image
                    guiradprgbarTimeToInflatioDeflation.Visible = false;

                    prim2.BackColor = Color.FromArgb(248, 237, 234);
                    prim2.BackColor2 = Color.FromArgb(210, 67, 39);
                    prim2.BackColor3 = Color.FromArgb(210, 67, 39);
                    prim2.BackColor4 = Color.FromArgb(248, 237, 234);
                    radProgressBarFemoralIndicator.Value1 = BadFemoralQualityIndicatorValue;                   
                }
            }
            catch (Exception ex)
            {
                GUIExceptionHandler.HandleException(ex, this);
            }
        }

        private void qualityIndicator_FemoraCuffEvent(object sender, BizFemoralQualityEventArgs e)
        {
            try
            {
                femoralFlag = e.enableOkayButton;                
                RefreshOkButton();

                if (e.signalStrengthIsGood)
                {
                    // show green color in the progress bar.
                    prim2.BackColor = Color.FromArgb(225, 240, 225);
                    prim2.BackColor2 = Color.FromArgb(1, 92, 1);
                    prim2.BackColor3 = Color.FromArgb(1, 92, 1);
                    prim2.BackColor4 = Color.FromArgb(225, 240, 225);
                    radProgressBarFemoralIndicator.Value1 = GoodFemoralQualityIndicatorValue; 
                }

                if (!e.signalStrengthIsGood)
                {
                    // show red color in the progress bar.                
                    prim2.BackColor = Color.FromArgb(248, 237, 234);
                    prim2.BackColor2 = Color.FromArgb(210, 67, 39);
                    prim2.BackColor3 = Color.FromArgb(210, 67, 39);
                    prim2.BackColor4 = Color.FromArgb(248, 237, 234);

                    radProgressBarFemoralIndicator.Value1 = BadFemoralQualityIndicatorValue;
                }
            }
            catch (Exception ex)
            {
                GUIExceptionHandler.HandleException(ex, this);
            }
        }

        /**This method is called when the event handler of BizCarotidQualityEvent is executed.
         * Here depending upon the signal strength the progress bar color is displayed and the Tick button is enabled.
        */
        private void qualityIndicator_CarotidQualityEvent(object sender, BizCarotidQualityEventArgs e)
        {
            try
            {
                // Due to some reason on some occasions the event arg max is less than min.
                // THis causes the application to stop.
                // This happens when recapture is done in simulation mode and during first capture for device mode.
                // The reason for the problem has not been found.
                // We are adding this code so as to continie using the application till the solution is found,
                if (e.signalMaximum < e.signalMinimum)
                {
                    // This message is for debugging purpose only             
                    CrxLogger.Instance.Write("qualityIndicator_CarotidQualityEvent Max is less than min, exiting function");
                    return;
                }

                // System.Diagnostics.Debug.Write("e.signalMinimum : " + e.signalMinimum + "\r\n");
                chartTonometer.ChartAreas[0].AxisY.Minimum = (e.signalMinimum - 1) * GuiConstants.ChartAreaMinimumY;

                // System.Diagnostics.Debug.Write("e.signalMaximum : " + e.signalMaximum + "\r\n");
                chartTonometer.ChartAreas[0].AxisY.Maximum = (e.signalMaximum + 1) * GuiConstants.ChartAreaMaximumY;                

                signalStrength = e.signalMaximum - e.signalMinimum;

                if (signalStrength > QualityIndicatorHeight)
                {
                    signalStrength = QualityIndicatorHeight;
                }              

                carotidFlag = e.enableOkayButton;

                // to enable tick button if both the events return true for enableokbutton
                RefreshOkButton();

                if (e.signalStrengthColor.Equals(Color.Red))
                {
                    prim1.BackColor = Color.FromArgb(248, 237, 234);
                    prim1.BackColor2 = Color.FromArgb(210, 67, 39);
                    prim1.BackColor3 = Color.FromArgb(210, 67, 39);
                    prim1.BackColor4 = Color.FromArgb(248, 237, 234);
                }
                else if (e.signalStrengthColor.Equals(Color.Yellow))
                {
                    prim1.BackColor = Color.FromArgb(249, 249, 239);
                    prim1.BackColor2 = Color.FromArgb(208, 208, 2);
                    prim1.BackColor3 = Color.FromArgb(208, 208, 2);
                    prim1.BackColor4 = Color.FromArgb(249, 249, 239);
                }
                else 
                {
                    prim1.BackColor = Color.FromArgb(225, 240, 225);
                    prim1.BackColor2 = Color.FromArgb(1, 92, 1);
                    prim1.BackColor3 = Color.FromArgb(1, 92, 1);
                    prim1.BackColor4 = Color.FromArgb(225, 240, 225);
                }

                radProgressBarQualityIndicator.Value1 = (int)signalStrength;
            }
            catch (Exception ex)
            {
                GUIExceptionHandler.HandleException(ex, this);
            }
        }

        /** This method is used to start the capture for tonometer waveform.
       */
        private void StartCarotidTonometerCapture()
        {
            try
            {
                // DalModule dalModuleObj = DalModule.Instance;

                // ########################################################################
                // ------------TO DO ----------- 
                // To be removed once BLL starts calling set device strategy, and GUI default window load
                // should call this method to set device strategy based on the saved config settings
                // dalModuleObj.SetDeviceStrategy("Simulation");
                // ########################################################################
                // dalModuleObj.StartCapture(obj.Pwv22528Settings.CaptureTime, SampleRate);

                // dalDataBufferObj = DalDataBuffer.Instance;
                // Start capturing    
                // Check the return value of biz.StartCapture
                if (!bizObj.StartCapture())
                {
                    // Show the following error message to the user."Capture cannot be started. If the problem persists check troubleshooting section in user manual or contact AtCor support http://atcormedical.com/request_support.html"
                   // string tempMessage = "Capture cannot be started. If the problem persists check troubleshooting section in user manual or contact AtCor support http://atcormedical.com/request_support.html";
                    RadMessageBox.Show(this, oMsgMgr.GetMessage(CrxStructCommonResourceMsg.GuiStartCaptureFailed), oMsgMgr.GetMessage(CrxStructCommonResourceMsg.SystemError), MessageBoxButtons.OK);

                    // Navigate the user to Setup screen.
                    objDefaultWindow.radpgTabCollection.SelectedPage = objDefaultWindow.guiradgrpbxPwvDistanceMethod;
                }                
                else
                {
                    timer1.Enabled = true;
                }
            }
            catch (Exception ex)
            {
                GUIExceptionHandler.HandleException(ex, this);
            }
        }

        /** This method is called to read value from the buffer, to be plotted on the graph.
         */
        private void ReadValueFromBuffer()
        {
            int countdowntimerInMilliseconds = 0;
            bool cdtimerIncrementedflag = false;

            try
            {
                int startIndex = -1;
                DalPwvDataStruct structData;
                DalDataBuffer dbuff = DalDataBuffer.Instance;

                int returnedValues = dbuff.GetNextValues(RequestedValues, ref startIndex);

                for (int i = 0; i < returnedValues; i++)
                {
                    structData = dbuff.GetValueAt(startIndex, i);

                    // this is done so that during the second inflated time the progress bar starts from 0%.
                    // previously, it used to show 100% for a fraction of a second.
                    if ((structData.countdownTimer * 1000) > countdowntimerInMilliseconds)
                    {
                        cdtimerIncrementedflag = true;
                    }

                    // since countdown timer is in seconds now converting it into milliseconds
                    countdowntimerInMilliseconds = structData.countdownTimer * 1000;
                    
                    ushort tonometerData = structData.tonometerData;

                    PlotTonometerData(tonometerData);

                    if (femoralPlotSwitch)
                    {
                        if (cuffstatechangeFlag && cdtimerIncrementedflag)
                        {
                            // CrxLogger.Instance.Write("COUNTDOWN: " + countdowntimerInMilliseconds.ToString());
                            guiradprgbarTimeToInflatioDeflation.Minimum = 0;
                            if (countdowntimerInMilliseconds > 0)
                            {
                                guiradprgbarTimeToInflatioDeflation.Maximum = countdowntimerInMilliseconds; // - int.Parse(deflationTime.ToString()); // (int)structData.countdownTimer
                            }

                            guiradprgbarTimeToInflatioDeflation.Value1 = 0;
                            cuffstatechangeFlag = false;
                            cdtimerIncrementedflag = false;
                        }

                        if ((guiradprgbarTimeToInflatioDeflation.Maximum - countdowntimerInMilliseconds) > 0)
                        {
                            guiradprgbarTimeToInflatioDeflation.Value1 = guiradprgbarTimeToInflatioDeflation.Maximum - countdowntimerInMilliseconds; // (int)structData.countdownTimer; // -int.Parse(deflationTime.ToString());
                        }

                        // Get time to display
                        // conver miliseconds to seconds first
                        uint seconds = structData.countdownTimer;

                        // now get minutes and seconds 
                        uint minutes = (seconds >= 60) ? (seconds / 60) : 0;
                        seconds = (seconds >= 60) ? (seconds % 60) : seconds;
                        radlblTimeStatus.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.LblTimestatus) + " " + minutes + oMsgMgr.GetMessage(CrxStructCommonResourceMsg.GuiDisplayColon) + ((seconds >= 10) ? string.Empty : "0") + seconds;

                        ushort femoralCuffData = structData.cuffPulseData;
                        PlotFemoralCuffData(femoralCuffData);
                        bizObj.Append(structData.tonometerData, structData.cuffPulseData);
                    }
                    else
                    {
                        guiradprgbarTimeToInflatioDeflation.Maximum = 0;

                        // plot flat line for femoral when cuff is not inflated as value 0
                        PlotFemoralCuffData(0);
                        bizObj.Append(structData.tonometerData, 0);
                    }
                }
                
                if (startIndex == 0)
                {
                    chartTonometer.ChartAreas[0].AxisY.Maximum = (dbuff.GetValueAt(startIndex, 0).tonometerData + 1) * GuiConstants.ChartAreaMaximumY;
                    chartTonometer.ChartAreas[0].AxisY.Minimum  = (dbuff.GetValueAt(startIndex, 0).tonometerData - 1) * GuiConstants.ChartAreaMinimumY;
                }                               
            }
            catch (Exception ex)
            {
                timer1.Enabled = false;
                GUIExceptionHandler.HandleException(ex, this);                
                if (radbtnTick.Enabled)
                {
                    DialogResult ds = RadMessageBox.Show(this, oMsgMgr.GetMessage(CrxStructCommonResourceMsg.GuiCaptureError), oMsgMgr.GetMessage(CrxStructCommonResourceMsg.SystemError), MessageBoxButtons.YesNoCancel, RadMessageIcon.Error);
                    switch (ds)
                    {
                        case DialogResult.Yes:
                            TickButtonAction();
                            break;
                        case DialogResult.No:
                            ShowSetupAfterCaptureAbort();
                            break;
                        default:
                            BizSession.Instance().StopCapture();
                            StopTimers();
                            guichartFemoralCuff.Series.Clear();
                            guichartFemoralCuff.Series.Remove(femoralCuffSeries);
                            chartTonometer.Series.Clear();
                            chartTonometer.Series.Remove(newSeries);
                            Invoke(new EventHandler(Capture_Load));
                            break;
                    }
                }
            }
        }

        /**This method is called to plot tonometer data.
         */
        private void PlotTonometerData(ushort tonometerData)
        {
            try
            {
                ushort data = tonometerData;
                
                // set the maximum y-axis,if the incoming data has a point greater than the existing y-axis value then set the new data point as the y-axix maximum.
                if (data > chartTonometer.ChartAreas[0].AxisY.Maximum)
                {
                    // System.Diagnostics.Debug.Write("data max : " + data + "\r\n");
                    chartTonometer.ChartAreas[0].AxisY.Maximum = (data + 1) * GuiConstants.ChartAreaMaximumY;
                }

                if (data < chartTonometer.ChartAreas[0].AxisY.Minimum)
                {
                    // System.Diagnostics.Debug.Write("data min : " + data + "\r\n");
                    chartTonometer.ChartAreas[0].AxisY.Minimum = (data - 1) * GuiConstants.ChartAreaMinimumY;
                }

                // System.Diagnostics.Debug.Print("data : " + data.ToString());
                // System.Diagnostics.Debug.Print("chartTonometer.ChartAreas[0].AxisY.Maximum : " + chartTonometer.ChartAreas[0].AxisY.Maximum.ToString());
                // System.Diagnostics.Debug.Print("chartTonometer.ChartAreas[0].AxisY.Minimum : " + chartTonometer.ChartAreas[0].AxisY.Minimum.ToString());

                // Add new data point to its series.        
                // System.Diagnostics.Debug.Write("datapoint : " + xCoordinateTonometer + " : " + data + "\r\n");
                newSeries.Points.AddXY(xCoordinateTonometer, data);
                xCoordinateTonometer++;
               
                // Here we check if the x-cordinate value has increased the screenwidth and the difference of the x-co-rdinate and the screenwidth is divisble by 256( 2 seconds window)
                // then slide the window 2 seconds forward and remove the starting points for 2 seconds.
                if ((xCoordinateTonometer > screenwidth) && (xCoordinateTonometer - screenwidth) % TwoSecondsWindow == 1)
                {
                    for (int i = 1; i <= TwoSecondsWindow; i++)
                    {
                        newSeries.Points.RemoveAt(0);
                    }

                    DataPoint dpMax = newSeries.Points.FindMaxByValue();
                    DataPoint dpMin = newSeries.Points.FindMinByValue();

                    // System.Diagnostics.Debug.Write("dpmax : " + dpMax + "\r\n");
                    // System.Diagnostics.Debug.Write("dpmin : " + dpMin + "\r\n");
                    // System.Diagnostics.Debug.Write("chartTonometer.ChartAreas[0].AxisY.Minimum : " + chartTonometer.ChartAreas[0].AxisY.Minimum + "\r\n");
                    // System.Diagnostics.Debug.Write("new chart min value : " + (dpMin.YValues[0] - 1) * GuiConstants.ChartAreaMinimumY + "\r\n");
                    chartTonometer.ChartAreas[0].AxisY.Maximum = (dpMax.YValues[0] + 1) * GuiConstants.ChartAreaMaximumY;
                    chartTonometer.ChartAreas[0].AxisY.Minimum = (dpMin.YValues[0] - 1) * GuiConstants.ChartAreaMinimumY;

                    // System.Diagnostics.Debug.Write("newSeries.Points[0].XValue : " + newSeries.Points[0].XValue + "\r\n");
                    chartTonometer.ChartAreas[0].AxisX.Minimum = newSeries.Points[0].XValue;

                    // System.Diagnostics.Debug.Write("newSeries.Points[0].XValue + screenwidth : " + newSeries.Points[0].XValue + screenwidth + "\r\n");
                    chartTonometer.ChartAreas[0].AxisX.Maximum = newSeries.Points[0].XValue + screenwidth;
                }

                // Here we plot the data points only, nothing to be done with respect to the axis.
                else if (xCoordinateTonometer >= screenwidth)
                {
                    // Nothing to be done.
                }                
                else
                {
                    // System.Diagnostics.Debug.Write("Else : newSeries.Points[0].XValue + screenwidth : " + newSeries.Points[0].XValue + screenwidth + "\r\n");
                    chartTonometer.ChartAreas[0].AxisX.Minimum = newSeries.Points[0].XValue;

                    // System.Diagnostics.Debug.Write("Else : newSeries.Points[0].XValue + screenwidth : " + newSeries.Points[0].XValue + screenwidth + "\r\n");
                    chartTonometer.ChartAreas[0].AxisX.Maximum = newSeries.Points[0].XValue + screenwidth;
                }
         
                chartTonometer.Invalidate();
            }
            catch (Exception ex)
            {
                CrxLogger.Instance.Write(ex.StackTrace);
                StopTimers();
                GUIExceptionHandler.HandleException(ex, this);
            }
        }

        /**This method is called to plot femoral cuff data.         
         */
        private void PlotFemoralCuffData(ushort femoralCuffData)
        {
            try
            {
                ushort data = femoralCuffData;

                // when cuff is not inflated data will have value 0 to plot, setting minimum y axis range for femoral chart to -10 to show flat line
                if (data == 0)
                {
                    guichartFemoralCuff.ChartAreas[0].AxisY.Minimum = -10;
                }
                else
                {
                    // if minimum value is less than 0 set it normal (data * ChartAreaMinimumY;)
                    if (guichartFemoralCuff.ChartAreas[0].AxisY.Minimum == -10)
                    {
                        guichartFemoralCuff.ChartAreas[0].AxisY.Minimum = data * GuiConstants.ChartAreaMinimumY;
                    }
                    else
                    {
                        if (data < guichartFemoralCuff.ChartAreas[0].AxisY.Minimum)
                        {
                            guichartFemoralCuff.ChartAreas[0].AxisY.Minimum = data * GuiConstants.ChartAreaMinimumY;
                        }
                    }
                }

                // set the maximum y-axis,if the incoming data has a point greater than the existing y-axis value then set the new data point as the y-axix maximum.
                if (data > guichartFemoralCuff.ChartAreas[0].AxisY.Maximum)
                {
                    guichartFemoralCuff.ChartAreas[0].AxisY.Maximum = data * GuiConstants.ChartAreaMaximumY;
                }

                // Add new data point to its series.                               
                femoralCuffSeries.Points.AddXY(xCoordinateFemoralCuff, data);
                xCoordinateFemoralCuff++;
                               
                if ((xCoordinateFemoralCuff > screenwidth) && (xCoordinateFemoralCuff - screenwidth) % TwoSecondsWindow == 1)
                {
                    for (int i = 1; i <= TwoSecondsWindow; i++)
                    {
                        femoralCuffSeries.Points.RemoveAt(0);
                    }

                    // Finding the max and min values for y-axis available in the series.
                    DataPoint dpMaxFemoral = femoralCuffSeries.Points.FindMaxByValue();
                    DataPoint dpMinFemoral = femoralCuffSeries.Points.FindMinByValue();

                    // Adjusting the max and min y axis of the chart to the max and min values respectively
                    // available in the series.
                    guichartFemoralCuff.ChartAreas[0].AxisY.Maximum = (dpMaxFemoral.YValues[0] + 1) * GuiConstants.ChartAreaMaximumY;
                    guichartFemoralCuff.ChartAreas[0].AxisY.Minimum = (dpMinFemoral.YValues[0] - 1) * GuiConstants.ChartAreaMinimumY;

                    // Adjusting the x-axis min and max after the 2 second shift.
                    guichartFemoralCuff.ChartAreas[0].AxisX.Minimum = femoralCuffSeries.Points[0].XValue;
                    guichartFemoralCuff.ChartAreas[0].AxisX.Maximum = femoralCuffSeries.Points[0].XValue + screenwidth;
                }
                else if (xCoordinateFemoralCuff >= screenwidth)
                {
                    // do nothing in this condition.
                }
                else
                {
                    // set the x axis's minimum and maximum values.
                    guichartFemoralCuff.ChartAreas[0].AxisX.Minimum = femoralCuffSeries.Points[0].XValue;
                    guichartFemoralCuff.ChartAreas[0].AxisX.Maximum = femoralCuffSeries.Points[0].XValue + screenwidth;
                }                

                guichartFemoralCuff.Invalidate();
            }
            catch (Exception ex)
            {
                GUIExceptionHandler.HandleException(ex, this);
            }
        }

        /** This method is used to set the tonometer graphs properties.
        */
        private void SetTonometerWaveformProperties()
        {
            // reset the tonometer x coordinate counter
            xCoordinateTonometer = 0;

            screenwidth = (obj.PwvSettings.CaptureTime + HandShakePeriod) * SampleRate;

            // Reset number of series in the chart.
            chartTonometer.Series.Clear();

            // set y axis
            // System.Diagnostics.Debug.Write("Min TonometerHeight : " + TonometerHeight + "\r\n");
            chartTonometer.ChartAreas[0].AxisY.Minimum = TonometerHeight - 1;

            // System.Diagnostics.Debug.Write("Max TonometerHeight : " + TonometerHeight + "\r\n");
            chartTonometer.ChartAreas[0].AxisY.Maximum = TonometerHeight + 1;

            signalStrength = 0;

            // set x axis
            // System.Diagnostics.Debug.Write("Zero : " + 0 + "\r\n");
            chartTonometer.ChartAreas[0].AxisX.Minimum = 0;

            // System.Diagnostics.Debug.Write("screenwidth : " + screenwidth + "\r\n");
            chartTonometer.ChartAreas[0].AxisX.Maximum = screenwidth;

            // series used for plotting the points,its chart type and the color of the graph.
            newSeries = new Series
                            {
                                ChartType = SeriesChartType.FastLine,
                                Color = Color.White,
                                XValueType = ChartValueType.Int32,
                                YValueType = ChartValueType.Int32
                            };

            // Add the series to the chart.
            chartTonometer.Series.Add(newSeries);
        }

        /** This method is used to set the femoral cuff graphs properties.
        */
        private void SetFemoralCuffWaveformProperties()
        {
            // reset the femoral x coordinate counter
            xCoordinateFemoralCuff = 0;

            screenwidth = (obj.PwvSettings.CaptureTime + HandShakePeriod) * SampleRate;

            // Reset number of series in the chart.
            guichartFemoralCuff.Series.Clear();

            // set y axis
            guichartFemoralCuff.ChartAreas[0].AxisY.Minimum = TonometerHeight - 1;
            guichartFemoralCuff.ChartAreas[0].AxisY.Maximum = TonometerHeight + 1;
            signalStrength = 0;

            // set x axis
            guichartFemoralCuff.ChartAreas[0].AxisX.Minimum = 0;
            guichartFemoralCuff.ChartAreas[0].AxisX.Maximum = screenwidth;

            // series used for plotting the points,its chart type and the color of the graph.
            femoralCuffSeries = new Series
                                    {
                                        ChartType = SeriesChartType.FastLine,
                                        Color = Color.Yellow,
                                        XValueType = ChartValueType.Int32,
                                        YValueType = ChartValueType.Int32
                                    };

            // Add the series to the chart.
            guichartFemoralCuff.Series.Add(femoralCuffSeries);
        }        

        /**This method is called when the user clicks on the Tick button.
       */
        private void radbtnTick_Click(object sender, EventArgs e)
        {            
            // BizErrorEventArgs bize = new BizErrorEventArgs ("mess");
            // GuiCommon.Instance_OnBizErrorEvent(this, bize);   
            if (!radbtnTick.Enabled)
            {
                return;
            }

            TickButtonAction();
            Close();
        }       

        /**This method enables the tabs and the ribbion and navigates the user to the Reports tab.          
         */
        private void TickButtonAction()
        {
            try
            {
                timer1.Enabled = false;

                objDefaultWindow.radlblMessage.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.GuiCaptureGeneratingReport);
                CrxStructPWVMeasurementData cdata = new CrxStructPWVMeasurementData();

                if (bizObj.CalculatePWVReport(cdata))
                {
                    // report calculation successful save report & navigate to report screen
                    StopCaptureAndSaveReport(cdata);
                }
                else
                {
                    // report calculation failed create text file and navigate to setup
                    CreateTextFileOnReportFailed();
                    ShowSetupAfterCaptureAbort();
                }
            }
            catch (Exception ex)
            {
                // for any exception during report calculation create text file, show error message & report calculation failed message
                StopTimers();
                CrxLogger.Instance.Write(ex.StackTrace);
                CreateTextFileOnReportFailed();
                GUIExceptionHandler.HandleException(ex, this);
                ShowSetupAfterCaptureAbort();
            }
        }

        /** This method creates text file and saves captured waveform and shows error message
         * */
        private void CreateTextFileOnReportFailed()
        {
            StopTimers();
            objDefaultWindow.radlblMessage.Text = string.Empty;

            // report calculation failed save captured data in text file                
            // this will create text file & will save data captured so far
            bizObj.SaveCaptureData();

            // GetSavedfile path should only be called once
            string captureFilePath = DalModule.Instance.GetSavedFilePath();

            // show error message alongwith filename
            RadMessageBox.Show(this, oMsgMgr.GetMessage(CrxStructCommonResourceMsg.ReportCalFailMsg) + Environment.NewLine + oMsgMgr.GetMessage(CrxStructCommonResourceMsg.GuiWaveformSaveMsg) + Environment.NewLine + captureFilePath, oMsgMgr.GetMessage(CrxStructCommonResourceMsg.SystemError), MessageBoxButtons.OK, RadMessageIcon.Error);

            // log the error
            CrxLogger.Instance.Write(oMsgMgr.GetMessage(CrxStructCommonResourceMsg.ReportCalFailMsg) + Environment.NewLine + oMsgMgr.GetMessage(CrxStructCommonResourceMsg.GuiWaveformSaveMsg) + Environment.NewLine + captureFilePath);
        }

        /** This method is called after successful report calculation
         * It stops capture & saves report in database
         * */
        private void StopCaptureAndSaveReport(CrxStructPWVMeasurementData cdata)
        {
            // hourglass cursor             
            System.Windows.Forms.Cursor.Current = Cursors.WaitCursor;
            
//VA:?            BizSession.Instance().StopCapture();            
            StopTimers();
            BizSession.Instance().StopCapture();            

            CrxConfigManager crxMgrObject = CrxConfigManager.Instance;
              
            // check db connection
            if (dbMagr.CheckConnection(GuiCommon.ServerNameString(), crxMgrObject.GeneralSettings.SourceData) == 0)
            {
                // capture with new measurement details.... insert a new record
                // capture will always add a new measurement record in backend even if it is conducted with same measurement data
                objDefaultWindow.radlblMessage.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.GuiCaptureSavingReport);
                SaveReportCalculation(cdata);
                System.Windows.Forms.Cursor.Current = Cursors.Default;
            }
            else
            {
                DialogResult result = RadMessageBox.Show(this, GuiCommon.ConnectionErrorString(), oMsgMgr.GetMessage(CrxStructCommonResourceMsg.SystemError), MessageBoxButtons.RetryCancel, RadMessageIcon.Error);
                if (result == DialogResult.Retry)
                {
                    SaveReportCalculation(cdata);
                }
                else
                {
                    // Navigate user back to the setup screen                    
                    ShowSetupAfterCaptureAbort();
                }
            }
        }

        /** This method saves report calclulation
         * */
        private void SaveReportCalculation(CrxStructPWVMeasurementData cdata)
        {
            int iRow = dbMagr.SavePWVMeasurementDetails(cdata);

            if (iRow > 0)
            {
                // redirect to report screen
                GuiCommon.SetupToReport = false;
                GuiCommon.PwvCurrentStudyDatetime = cdata.StudyDateTime.ToString();

                guichartFemoralCuff.Series.Clear();
                guichartFemoralCuff.Series.Remove(femoralCuffSeries);

                // Clear and remove the tonometer waveform.
                chartTonometer.Series.Clear();
                chartTonometer.Series.Remove(newSeries);

                // Disable the tick button on the screen.
                // radbtnTick.Enabled = false;                
                GuiCommon.CaptureToReport = true;
                objDefaultWindow.radpgTabCollection.SelectedPage = objDefaultWindow.radtabReport;
                objDefaultWindow.radlblMessage.Text = string.Empty;
                objDefaultWindow.radtabReport.Enabled = true;
                if (!objDefaultWindow.radtabReport.Enabled)
                {
                    return;
                }

                // call the report load event only once 
                // report load count is 1 when application is launched
                if (GuiCommon.ReportLoadCount == 1)
                {
                    GuiCommon.ReportLoadCount++;
                }
                else
                {
                    // invoke load method of report screen
                    OnReportTabClick.Invoke(this, new EventArgs());
                }

                // disable setting tab on menu bar
                objDefaultWindow.guiradmnuitemSettings.Enabled = false;
                objDefaultWindow.guiradmnuSystemKey.Enabled = false;

                // disable settings, backup, restore & cross button
                objDefaultWindow.guiradmnuitemSettings.Enabled = false;
                objDefaultWindow.guiradmnuScor.Enabled = true;
                objDefaultWindow.guiradgrpbxPwvDistanceMethod.Enabled = true;
                objDefaultWindow.radtabCapture.Enabled = false;
            }
            else
            {
                RadMessageBox.Show(this, oMsgMgr.GetMessage(CrxStructCommonResourceMsg.ReportSaveErr), oMsgMgr.GetMessage(CrxStructCommonResourceMsg.SystemError), MessageBoxButtons.OK, RadMessageIcon.Error);
            }
        }

        /**This method is called when the user clicks on the Cross button.
        */
        private void CrossButtonAction()
        {
            try
            {
                timer1.Enabled = false;
                DialogResult ds = RadMessageBox.Show(this, GuiCommon.MessageToBeDisplayed + " " + oMsgMgr.GetMessage(CrxStructCommonResourceMsg.CaptureFailed), oMsgMgr.GetMessage(CrxStructCommonResourceMsg.SystemError), MessageBoxButtons.YesNo, RadMessageIcon.Info);
                if (ds == DialogResult.Yes)
                {
                    ShowSetupAfterCaptureAbort();
                    Close();
                }
                else
                {
                    timer1.Enabled = true;
                }
            }
            catch (Exception ex)
            {
                GUIExceptionHandler.HandleException(ex, this);
            }
        }

        /** This method redirects to setup after capture abort
         * */
        void ShowSetupAfterCaptureAbort()
        {
            BizSession.Instance().StopCapture();
                       
            StopTimers();

            // Clear and remove the femoral waveform.
            guichartFemoralCuff.Series.Clear();
            guichartFemoralCuff.Series.Remove(femoralCuffSeries);

            // Clear and remove the tonometer waveform.
            chartTonometer.Series.Clear();
            chartTonometer.Series.Remove(newSeries);

            // Disable the tick button on the screen.
            radbtnTick.Enabled = false;

            objDefaultWindow.radpgTabCollection.SelectedPage = objDefaultWindow.guiradgrpbxPwvDistanceMethod;
            objDefaultWindow.radlblMessage.Text = string.Empty;
            objDefaultWindow.radlblCaptureTime.Text = string.Empty;

            // disable settings, backup, restore & cross button
            objDefaultWindow.guiradmnuitemSettings.Enabled = true;
            objDefaultWindow.guiradmnuSystemKey.Enabled = true;
            objDefaultWindow.guiradmnuScor.Enabled = true;
            objDefaultWindow.guiradgrpbxPwvDistanceMethod.Enabled = true;
            objDefaultWindow.radtabReport.Enabled = GuiCommon.HasMeasurementDetails;
            objDefaultWindow.guipictureboxError.Image = null;

            // set variable to enforce 30 secs timers on setup 
            GuiCommon.CaptureToSetup = true;

            // make progress bar & labels invisible
            guiradprgbarTimeToInflatioDeflation.Visible = false;
            radlblTimeStatus.Visible = false;
            guiradprgbarTimeToInflatioDeflation.Value1 = 0;
            guiradprgbarTimeToInflatioDeflation.Maximum = 0;
            radProgressBarQualityIndicator.Value1 = 0;            
        }

        /** This event is fired when the timer is enabled.
        * The tick event of the timer is called every 125 milliseconds.
        */
        private void timer1_Tick(object sender, EventArgs e)
        {
            ReadValueFromBuffer();
            BizSession.Instance().DispatchCaptureData();
        }

        /** This method is fired when the user presses any key from the keyboard on the Captrue screen.
         */ 
        private void Capture_KeyDown(object sender, KeyEventArgs e)
        {
            timer1.Enabled = false;
            if (e.KeyCode == Keys.Escape)
            {                
                GenerateReportWhenCaptureIsEnabled();
            }
            else if (e.KeyCode == Keys.Space && radbtnTick.Enabled)
            {
                TickButtonAction();
                Close();
            }
            else if (e.KeyCode == Keys.Space && !radbtnTick.Enabled)
            {
                e.SuppressKeyPress = true;
                timer1.Enabled = true;
            }           
        }

        /** This method stops all the timers,runing on the capture screen.
         * */
        private void StopTimers()
        {
            // Disable all the timers on the capture screen
            timer1.Stop();
        }

        /** This method is used to enable/disable the ok button on the Capture screen.
       * It depends on the QualityIndicator event of both tonometer and femoral cuff.
       */
        private void RefreshOkButton()
        {
            // to enable tick button if both the events return true for enableokbutton
            if (carotidFlag && femoralFlag)
            {
                radbtnTick.Enabled = true;
            }
            else
            {
                radbtnTick.Enabled = false;
            }
        }

        /**This event is called when the form is called,it will start a timer which will disabled the capture tab
         * Capture button on the Setup screen and the repeat button on the Report screen.
         */
        private void Capture_FormClosing(object sender, FormClosingEventArgs e)
        {
            try
            {
                tableLayoutPanel1.Visible = false;
                chartTonometer.Visible = false;      
                guichartFemoralCuff.Visible = false;      
                guiradlblCarotidTonometer.Visible = false;
                guiradlblFemoralCuff.Visible = false;      
                radProgressBarQualityIndicator.Visible = false;
                radProgressBarFemoralIndicator.Visible = false;                
                guiradlblTonometerThresholdPart1.Visible = false;
                guiradlblTonometerThresholdPart2.Visible = false;
                guiradlblFemoralThresholdPart1.Visible = false;
                guiradlblFemoralThresholdPart2.Visible = false;
                GuiCommon.CaptureFormLoaded = false;
                GuiCommon.CaptureChildForm = null;
                GuiCommon.InvokeCaptureClosing(false);
                objDefaultWindow.tmrImposeWaitTime.Interval = int.Parse(ConfigurationManager.AppSettings[GuiConstants.AppConfigParams.WaitInterval.ToString()]);
                GuiCommon.IsWaitIntervalImposed = true;
                objDefaultWindow.tmrImposeWaitTime.Start();
                objDefaultWindow.guicmbxCurrentMode.Enabled = true;
                this.Dispose(false);
            }
            catch (Exception ex)
            {
                GUIExceptionHandler.HandleException(ex, this);
            }           
        }

        /**This method will check if the capture button is enabled,if yes it will try generating a report.
         * If not,then navigate the user to the setup screen
         */ 
        private void GenerateReportWhenCaptureIsEnabled()
        {
            // if Ok btn is enabled and user clicks on Cancel then ask the user if he wants to generate report or abort.
            if (radbtnTick.Enabled)
            {
                DialogResult ds = RadMessageBox.Show(this, GuiCommon.MessageToBeDisplayed + " " + oMsgMgr.GetMessage(CrxStructCommonResourceMsg.CaptureTickMsg), oMsgMgr.GetMessage(CrxStructCommonResourceMsg.SystemError), MessageBoxButtons.YesNo, RadMessageIcon.Info);
                if (ds == DialogResult.Yes)
                {
                    TickButtonAction();
                }
                else
                {
                    // navigate user to Setup screen
                    ShowSetupAfterCaptureAbort();
                }

                Close();
            }
            else
            {
                CrossButtonAction();
            }                
         }

        private void Capture_OnCaptureScreenTabClick(object sender, EventArgs e)
        {           
           radbtnCross.Focus();            
        }        
    }
}
