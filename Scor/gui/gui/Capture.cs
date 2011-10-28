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
using System.Diagnostics;

/**
 * @namespace AtCor.Scor.Gui.Presentation
 * @brief This namespace implements Presentation related classes.  
 */
namespace AtCor.Scor.Gui.Presentation
{
    /**
   * @class Capture
   * @brief This class will handle displaying of the Capture screen controls.It will also check for exception handling and logging of events.
   */
    public partial class Capture : Telerik.WinControls.UI.RadForm
    {
        #region Set constant values        
        
        const int HandShakePeriod = 2;
        const int SampleRate = 256;
        const int TonometerHeight = 300;
        const int QualityIndicatorHeight = 30000;
        const int TwoSecondsWindow = 512;
        const int RequestedValues = 1000;
        const int GoodFemoralQualityIndicatorValue = 80;
        const int BadFemoralQualityIndicatorValue = 20;
        readonly CrxMessagingManager oMsgMgr = CrxMessagingManager.Instance;
        readonly CrxDBManager dbMagr = CrxDBManager.Instance;
        Stopwatch stopWatch;
/*
        const int YCordinateForPlottingStraightLine = 600;
*/         
        
        private DefaultWindow objDefaultWindow;
        bool carotidFlag = false; // to check for carotid quality indicator for PWV
        bool femoralFlag = false; // to check for femoral quality indicator for PWV            
        bool isFemoralCuffCaptureTrueForAutoCapture = false;
        bool isTonometerCaptureTrueForAutoCapture = false;
        volatile bool femoralPlotSwitch = false;
        volatile bool cuffstatechangeFlag = false;
        Color pulseHeightColor;
        Color pulseHeightColorForTonometer;        
        #endregion              
        
        public static event EventHandler OnReportTabClick;

        public static event EventHandler OnPWAReportTabClick;

        public static event EventHandler OnPWATestResultTabClick;

        public delegate void AccessGuiControls();

        Series newSeries;
        Series femoralCuffSeries;
        Series verticalGBSeriesForCuff;
        Series topGBSeries;
        Series bottomGBSeries;
        Series topGBSeriesForCuff;
        Series bottomGBSeriesForCuff;
        Series verticalGBSeries;
        CrxStructPWAMeasurementData pwaData;
        CrxStructTonoPWAMeasurementData pwaTonoStruct;
        CrxStructCuffPWAMeasurementData pwaCuffStruct;
        double screenwidth;
        double screenwidthForCuffChartInPWAMode;        
        ProgressBarPrimitive prim1;
        ProgressBarPrimitive prim2;
        StripLine bottomStrip = new StripLine();
        StripLine topStrip = new StripLine();        
        StripLine bottomStripTonometerChart = new StripLine();
        StripLine topStripTonometerChart = new StripLine();
        int upperValueForGuidanceBar = 0;
        int lowerValueForGuidanceBar = 0;
        int upperValueForGuidanceBarTonometerChart = 0;
        int lowerValueForGuidanceBarTonometerChart = 0;

        static uint xCoordinateTonometer = 0;
        static uint xCoordinateFemoralCuff = 0;
        static uint xCoordinatePwaChart = 0;

        // object of Config Manager                 
        CrxConfigManager obj;        

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
           GuiCommon.ScorControllerObject.ActionPerformedAfterClickingCancel();           
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
                radbtnCross.Focus();

                // tmrInflationTimer.Enabled = true;                
                obj = CrxConfigManager.Instance;
                obj.GetGeneralUserSettings();
                obj.GetPwvUserSettings();
                obj.GetPwaUserSettings(); 

                SubscribeToEvents();              
                GuiCommon.ScorControllerObject.InitialiseCaptureScreen();  

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

                radProgressBarFemoralIndicator.Minimum = 0;
                radProgressBarFemoralIndicator.Maximum = QualityIndicatorHeight;

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
            }
            catch (Exception ex)
            {
                StopTimers();
                GUIExceptionHandler.HandleException(ex, this);
            }
        }       

        /** This method displays capture time in bottom area
         * */
        void DisplayCaptureTimeForPwvCapture()
        {
            // objDefaultWindow.radlblCaptureTime.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.GrpCaptureTime) + oMsgMgr.GetMessage(CrxStructCommonResourceMsg.GuiDisplayColon) + CrxConfigManager.Instance.PwaSettings.CaptureTime.ToString();   
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
                   // guiradprgbarTimeToInflatioDeflation.Visible = true;
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

                    // radProgressBarFemoralIndicator.Value1 = BadFemoralQualityIndicatorValue;                   
                }

                if (e.data.ToLower().Equals("inflating"))
                {                    
                    objDefaultWindow.radlblMessage.Text = string.Empty;

                    femoralPlotSwitch = false;
                    cuffstatechangeFlag = false;
                    guiradprgbarTimeToInflatioDeflation.Value1 = 0;
                    guiradprgbarTimeToInflatioDeflation.Update();

                    // make progress bar, time to deflation invisible & show cross
                    radlblTimeStatus.Visible = false;
                    objDefaultWindow.radlblMessage.Text = CrxMessagingManager.Instance.GetMessage(CrxStructCommonResourceMsg.GuiCaptureCuffInflatingMsg);

                    // make progress bar invisible & show cross image
                    guiradprgbarTimeToInflatioDeflation.Visible = false;

                    prim2.BackColor = Color.FromArgb(248, 237, 234);
                    prim2.BackColor2 = Color.FromArgb(210, 67, 39);
                    prim2.BackColor3 = Color.FromArgb(210, 67, 39);
                    prim2.BackColor4 = Color.FromArgb(248, 237, 234);

                    // radProgressBarFemoralIndicator.Value1 = BadFemoralQualityIndicatorValue;
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
                if (GuiCommon.CurrentMode.Equals(CrxStructCommonResourceMsg.Pwv))
                {
                    /*
                    femoralFlag = e.enableOkayButton;
                    RefreshOkButton();

                    if (e.signalStrengthIsGood)
                    {
                        // show green color in the progress bar.
                        prim2.BackColor = Color.FromArgb(225, 240, 225);
                        prim2.BackColor2 = Color.FromArgb(1, 92, 1);
                        prim2.BackColor3 = Color.FromArgb(1, 92, 1);
                        prim2.BackColor4 = Color.FromArgb(225, 240, 225);
                        // radProgressBarFemoralIndicator.Value1 = GoodFemoralQualityIndicatorValue;
                        radProgressBarFemoralIndicator.Value1 = e.signalStrengthHeight;
                    }

                    if (!e.signalStrengthIsGood)
                    {
                        // show red color in the progress bar.                
                        prim2.BackColor = Color.FromArgb(248, 237, 234);
                        prim2.BackColor2 = Color.FromArgb(210, 67, 39);
                        prim2.BackColor3 = Color.FromArgb(210, 67, 39);
                        prim2.BackColor4 = Color.FromArgb(248, 237, 234);

                        // radProgressBarFemoralIndicator.Value1 = BadFemoralQualityIndicatorValue;
                        radProgressBarFemoralIndicator.Value1 = e.signalStrengthHeight;
                    }
                    */

                    radProgressBarFemoralIndicator.Value1 = e.signalStrengthHeight;
                    if (e.signalStrengthColor.Equals(Color.Red))
                    {
                        prim2.BackColor = Color.FromArgb(248, 237, 234);
                        prim2.BackColor2 = Color.FromArgb(210, 67, 39);
                        prim2.BackColor3 = Color.FromArgb(210, 67, 39);
                        prim2.BackColor4 = Color.FromArgb(248, 237, 234);
                    }
                    else if (e.signalStrengthColor.Equals(Color.Yellow))
                    {
                        prim2.BackColor = Color.FromArgb(249, 249, 239);
                        prim2.BackColor2 = Color.FromArgb(208, 208, 2);
                        prim2.BackColor3 = Color.FromArgb(208, 208, 2);
                        prim2.BackColor4 = Color.FromArgb(249, 249, 239);
                    }
                    else
                    {
                        prim2.BackColor = Color.FromArgb(225, 240, 225);
                        prim2.BackColor2 = Color.FromArgb(1, 92, 1);
                        prim2.BackColor3 = Color.FromArgb(1, 92, 1);
                        prim2.BackColor4 = Color.FromArgb(225, 240, 225);
                    }                    
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
                /*
                // Due to some reason on some occasions the event arg max is less than min.
                // THis causes the application to stop.
                // This happens when recapture is done in simulation mode and during first capture for device mode.
                // The reason for the problem has not been found.
                // We are adding this code so as to continie using the application till the solution is found,
                if (e.signalMaximum < e.signalMinimum)
                {
                    // This message is for debugging purpose only             
                    // CrxLogger.Instance.Write("qualityIndicator_CarotidQualityEvent Max is less than min, exiting function");
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
                //RefreshOkButton();
                */

                radProgressBarQualityIndicator.Value1 = e.signalStrengthHeight;

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
                // Check the return value of biz.StartCapture
                if (!GuiCommon.ScorControllerObject.StartCapture())                                                                
                {
                    // Show the following error message to the user."Capture cannot be started. If the problem persists check troubleshooting section in user manual or contact AtCor support http://atcormedical.com/request_support.html"                   
                    RadMessageBox.Show(this, oMsgMgr.GetMessage(CrxStructCommonResourceMsg.GuiStartCaptureFailed), oMsgMgr.GetMessage(CrxStructCommonResourceMsg.SystemError), MessageBoxButtons.OK);
                    GuiCommon.ErrorInCaptureProcess = true;
                }                
                else
                {
                    tmrPwvCaptureMode.Enabled = true;                    
                }
            }
            catch (Exception ex)
            {
                GUIExceptionHandler.HandleException(ex, this);
            }
        }

        private void StartPwaCapture()
        {
            if (!GuiCommon.ScorControllerObject.StartCapture())
            {
                // Show the following error message to the user."Capture cannot be started. If the problem persists check troubleshooting section in user manual or contact AtCor support http://atcormedical.com/request_support.html"
                // string tempMessage = "Capture cannot be started. If the problem persists check troubleshooting section in user manual or contact AtCor support http://atcormedical.com/request_support.html";
                RadMessageBox.Show(this, oMsgMgr.GetMessage(CrxStructCommonResourceMsg.GuiStartCaptureFailed), oMsgMgr.GetMessage(CrxStructCommonResourceMsg.SystemError), MessageBoxButtons.OK);
                GuiCommon.ErrorInCaptureProcess = true;               
            }
            else
            {
                tmrPwaCaptureMode.Enabled = true;
            }
        }

        /** This method is called to read value from the buffer, to be plotted on the graph.
         */
        private void ReadValueFromBuffer()
        {         
            stopWatch = Stopwatch.StartNew();            
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
                        // uint minutes = (seconds >= 60) ? (seconds / 60) : 0;
                        // seconds = (seconds >= 60) ? (seconds % 60) : seconds;
                        radlblTimeStatus.Text = string.Format(oMsgMgr.GetMessage(CrxStructCommonResourceMsg.LblTimestatus), oMsgMgr.GetMessage(CrxStructCommonResourceMsg.GuiDisplayColon), ((seconds >= 10) ? string.Empty : "0"), seconds);                       

                        ushort femoralCuffData = structData.cuffPulseData;
                        PlotFemoralCuffData(femoralCuffData);
                        GuiCommon.bizObject.Append(structData.tonometerData, structData.cuffPulseData);
                    }
                    else
                    {
                        guiradprgbarTimeToInflatioDeflation.Maximum = 0;

                        // plot flat line for femoral when cuff is not inflated as value 0
                        PlotFemoralCuffData(0);
                        GuiCommon.bizObject.Append(structData.tonometerData, 0);
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
                tmrPwvCaptureMode.Enabled = false;
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
                    chartTonometer.ChartAreas[0].AxisY.Minimum = (data - 1) * GuiConstants.ChartAreaMinimumY;                    
                }
                
                // Add new data point to its series.                        
                newSeries.Points.AddXY(xCoordinateTonometer, data + 5);                
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
                    
                    chartTonometer.ChartAreas[0].AxisY.Maximum = (dpMax.YValues[0] + 1) * GuiConstants.ChartAreaMaximumY;
                    chartTonometer.ChartAreas[0].AxisY.Minimum = (dpMin.YValues[0] - 1) * GuiConstants.ChartAreaMinimumY;
                    
                    chartTonometer.ChartAreas[0].AxisX.Minimum = newSeries.Points[0].XValue;                    
                    chartTonometer.ChartAreas[0].AxisX.Maximum = newSeries.Points[0].XValue + screenwidth;
                }
                else if (xCoordinateTonometer >= screenwidth)
                {
                    // Here we plot the data points only, nothing to be done with respect to the axis.
                    // Nothing to be done.                    
                }                
                else
                {                    
                    chartTonometer.ChartAreas[0].AxisX.Minimum = newSeries.Points[0].XValue;                 
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
               // System.Diagnostics.Debug.Write(Environment.NewLine + "Argument value is (PlotFemoralCuffData):" + femoralCuffData.ToString());
                ushort data = femoralCuffData;

                // when cuff is not inflated data will have value 0 to plot, setting minimum y axis range for femoral chart to -10 to show flat line
                if (data == 0)
                {
                    guichartFemoralCuff.ChartAreas[0].AxisY.Minimum = -100;
                }
                else
                {
                    // if minimum value is less than 0 set it normal (data * ChartAreaMinimumY;)
                    if (guichartFemoralCuff.ChartAreas[0].AxisY.Minimum == -100)
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

                // Add strip lines to the chart.                
               // topStrip.StripWidth = 1;
               // topStrip.IntervalOffset = upperValueForGuidanceBar;
                
              // bottomStrip.StripWidth = 1;
               bottomStrip.IntervalOffset = lowerValueForGuidanceBar;
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

            // topStripTonometerChart.StripWidthType = DateTimeIntervalType.NotSet;
            // topStripTonometerChart.StripWidth = 1;
            topGBSeries = new Series
            {
                ChartType = SeriesChartType.FastLine,
                Color = Color.Transparent,
                XValueType = ChartValueType.Int32,
                YValueType = ChartValueType.Int32
            };

            topGBSeries.BorderWidth = 1;

            bottomGBSeries = new Series
            {
                ChartType = SeriesChartType.FastLine,
                Color = Color.Transparent,
                XValueType = ChartValueType.Int32,
                YValueType = ChartValueType.Int32
            };

            bottomGBSeries.BorderWidth = 1;

            verticalGBSeries = new Series
            {
                ChartType = SeriesChartType.FastLine,
                Color = Color.Transparent,
                XValueType = ChartValueType.Int32,
                YValueType = ChartValueType.Int32
            };

            verticalGBSeries.BorderWidth = 3;

            // Add the series to the chart.            
            chartTonometer.Series.Add(newSeries);
            chartTonometer.Series.Add(topGBSeries);
            chartTonometer.Series.Add(bottomGBSeries);
            chartTonometer.Series.Add(verticalGBSeries);
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
            
            // set x axis
            guichartFemoralCuff.ChartAreas[0].AxisX.Minimum = 0;
            guichartFemoralCuff.ChartAreas[0].AxisX.Maximum = screenwidth;

            // series used for plotting the points,its chart type and the color of the graph.
            femoralCuffSeries = new Series
                                    {
                                        ChartType = SeriesChartType.FastLine,
                                        Color = Color.White,
                                        XValueType = ChartValueType.Int32,
                                        YValueType = ChartValueType.Int32
                                    };

            topGBSeriesForCuff = new Series
            {
                ChartType = SeriesChartType.FastLine,
                Color = Color.Transparent,
                XValueType = ChartValueType.Int32,
                YValueType = ChartValueType.Int32
            };

            topGBSeriesForCuff.BorderWidth = 1;

            bottomGBSeriesForCuff = new Series
            {
                ChartType = SeriesChartType.FastLine,
                Color = Color.Transparent,
                XValueType = ChartValueType.Int32,
                YValueType = ChartValueType.Int32
            };

            bottomGBSeriesForCuff.BorderWidth = 1;            

            verticalGBSeriesForCuff = new Series
            {
                ChartType = SeriesChartType.FastLine,
                Color = Color.Transparent,
                XValueType = ChartValueType.Int32,
                YValueType = ChartValueType.Int32
            };

            verticalGBSeriesForCuff.BorderWidth = 3;

            // Add the series to the chart.
            guichartFemoralCuff.Series.Add(topGBSeriesForCuff);
            guichartFemoralCuff.Series.Add(bottomGBSeriesForCuff);
            guichartFemoralCuff.Series.Add(femoralCuffSeries);    
            guichartFemoralCuff.Series.Add(verticalGBSeriesForCuff);  
        }        

        /**This method is called when the user clicks on the Tick button.
       */
        private void radbtnTick_Click(object sender, EventArgs e)
        {            
            if (!radbtnTick.Enabled)
            {
                return;
            }
            
            GuiCommon.ScorControllerObject.CalculateReportAfterSuccessfulCapture();   
            Close();
        }       

        /**This method enables the tabs and the ribbion and navigates the user to the Reports tab.          
         */
        public void TickButtonAction()
        {
            try
            {
                tmrPwvCaptureMode.Enabled = false;

                objDefaultWindow.radlblMessage.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.GuiCaptureGeneratingReport);
                CrxStructPWVMeasurementData cdata = new CrxStructPWVMeasurementData();

                if (GuiCommon.bizObject.CalculatePWVReport(cdata))
                {                      
                    // report calculation successful save report & navigate to report screen
                    StopCaptureAndSaveReport(cdata);
                }
                else
                {
                    // report calculation failed create text file and navigate to setup
                    // CreateTextFileOnReportFailed();
                    GuiCommon.ScorControllerObject.CreateTextFileForFailedCapture(); 
                    ShowSetupAfterCaptureAbort();
                }
            }
            catch (Exception ex)
            {
                // for any exception during report calculation create text file, show error message & report calculation failed message
                StopTimers();
                CrxLogger.Instance.Write(ex.StackTrace);                
                GuiCommon.ScorControllerObject.CreateTextFileForFailedCapture(); 
                GUIExceptionHandler.HandleException(ex, this);
                ShowSetupAfterCaptureAbort();
            }
        }

        /** This method creates text file and saves captured waveform and shows error message
         * */
        public void CreateTextFileOnReportFailed()
        {
            StopTimers();
            objDefaultWindow.radlblMessage.Text = string.Empty;

            // report calculation failed save captured data in text file                
            // this will create text file & will save data captured so far
            // GuiCommon.bizObject.SaveCaptureData();
            GuiCommon.ScorControllerObject.SaveCaptureData();  

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
            
            // BizSession.Instance().StopCapture();            
            GuiCommon.ScorControllerObject.StopCapture();  
            StopTimers();

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
            cdata.Simulation = CrxConfigManager.Instance.GeneralSettings.CommsPort.Equals(CrxStructCommonResourceMsg.Simulation) ? true : false;          
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
                    GuiCommon.ScorControllerObject.LoadReport();

                    // OnReportTabClick.Invoke(this, new EventArgs());                   
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
        public void CrossButtonAction()
        {
            try
            {
                if (chartTonometer.InvokeRequired)
                {
                    AccessGuiControls d = new AccessGuiControls(CrossButtonAction);
                    this.Invoke(d);
                }
                else
                {
                    tmrPwvCaptureMode.Enabled = false;

                    if (GuiCommon.IsBizErrorEventRaised)
                    {
                        RadMessageBox.Show(this, GuiCommon.MessageToBeDisplayed + " " + oMsgMgr.GetMessage(CrxStructCommonResourceMsg.GuiCaptureCanNotContinue), oMsgMgr.GetMessage(CrxStructCommonResourceMsg.SystemError), MessageBoxButtons.OK, RadMessageIcon.Info);
                        ShowSetupAfterCaptureAbort();
                        GuiCommon.IsBizErrorEventRaised = false;
                        return;
                    }
                    else
                    {
                        DialogResult ds = RadMessageBox.Show(this, GuiCommon.MessageToBeDisplayed + " " + oMsgMgr.GetMessage(CrxStructCommonResourceMsg.CaptureFailed), oMsgMgr.GetMessage(CrxStructCommonResourceMsg.SystemError), MessageBoxButtons.YesNo, RadMessageIcon.Info);
                        if (ds == DialogResult.Yes)
                        {
                            ShowSetupAfterCaptureAbort();
                            Close();
                        }
                        else
                        {
                            tmrPwvCaptureMode.Enabled = true;
                        }
                    }
                }
            }
            catch (Exception ex)
            {
                GUIExceptionHandler.HandleException(ex, this);
            }
        }

        /** This method redirects to setup after capture abort
         * */
        public void ShowSetupAfterCaptureAbort()
        {
            GuiCommon.ScorControllerObject.StopCapture();
            if (GuiCommon.StartupScreen.ToUpper().Equals(CrxStructCommonResourceMsg.QuickStart) && GuiCommon.CurrentMode.Equals(CrxStructCommonResourceMsg.Pwa))
            {
                ShowQuickStartAfterCaptureAbort();
            }
            else
            {                
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

                // enable settings, backup, restore & cross button
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
        }

        public void ShowQuickStartAfterCaptureAbort()
        {
            GuiCommon.ScorControllerObject.StopCapture();
            StopTimers();

            // Clear and remove the femoral waveform.
            guichartFemoralCuff.Series.Clear();
            guichartFemoralCuff.Series.Remove(femoralCuffSeries);

            // Clear and remove the tonometer waveform.
            chartTonometer.Series.Clear();
            chartTonometer.Series.Remove(newSeries);

            // Disable the tick button on the screen.
            radbtnTick.Enabled = false;

            objDefaultWindow.radpgTabCollection.SelectedPage = objDefaultWindow.radtabQuickStart;
            objDefaultWindow.radlblMessage.Text = string.Empty;
            objDefaultWindow.radlblCaptureTime.Text = string.Empty;

            // enable settings, backup, restore & cross button
            objDefaultWindow.guiradmnuitemSettings.Enabled = true;
            objDefaultWindow.guiradmnuSystemKey.Enabled = true;
            objDefaultWindow.guiradmnuScor.Enabled = true;
            objDefaultWindow.radtabQuickStart.Enabled = true;

            // objDefaultWindow.radtabReport.Enabled = GuiCommon.HasMeasurementDetails;
            objDefaultWindow.guipictureboxError.Image = null;

            // set variable to enforce 30 secs timers on setup 
            // GuiCommon.CaptureToSetup = true;
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
        private void tmrPwvCaptureMode_Tick(object sender, EventArgs e)
        {            
            ReadValueFromBuffer();
            BizSession.Instance().DispatchCaptureData();
        }

        /** This method is fired when the user presses any key from the keyboard on the Captrue screen.
         */ 
        private void Capture_KeyDown(object sender, KeyEventArgs e)
        {
            GuiCommon.ScorControllerObject.HandleKeyDownEventOnCaptureScreen(e);           
        }

        /** This method stops all the timers,runing on the capture screen.
         * */
        private void StopTimers()
        {
            if (GuiCommon.CurrentMode.Equals(CrxStructCommonResourceMsg.Pwv))
            {
                // Disable all the timers on the capture screen
                tmrPwvCaptureMode.Stop();
            }
               
            if (GuiCommon.CurrentMode.Equals(CrxStructCommonResourceMsg.Pwa))
            {
                tmrPwaCaptureMode.Stop(); 
            }
        }

        /** This method is used to enable/disable the ok button on the Capture screen for PWV mode.
       * It depends on the QualityIndicator event of both tonometer and femoral cuff.
       */
        public void RefreshOkButtonForPwvMode()
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

        /** This method is used to enable/disable the ok button on the Capture screen for PWA mode.
        * It depends on the QualityIndicator event of both tonometer and femoral cuff.
        */
        public void RefreshOkButtonForPwaMode()
        {
            if (carotidFlag || femoralFlag)
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
                // Unsubscribe to biz.dll events
                BizEventContainer.Instance.OnBizPWAQualityEvent -= qualityIndicator_OnBizPWAQualityEvent;
                BizEventContainer.Instance.OnBizRTOFPWACuffEvent -= guidanceBars_OnBizRTOFPWACuffEvent;
                BizEventContainer.Instance.OnBizRTOFPWVTonometerEvent -= guidanceBars_OnBizRTOFPWVTonometerEvent;
                BizEventContainer.Instance.OnBizRTOFPWVCuffEvent -= guidanceBars_OnBizRTOFPWVCuffEvent;

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

                if (objDefaultWindow.radpgTabCollection.SelectedPage.Text.Equals(oMsgMgr.GetMessage(CrxStructCommonResourceMsg.TabResult), StringComparison.CurrentCultureIgnoreCase))
                {
                    objDefaultWindow.guicmbxCurrentMode.Enabled = false;
                }
                else
                {
                    objDefaultWindow.guicmbxCurrentMode.Enabled = true;
                }

                Dispose(false);
                xCoordinatePwaChart = xCoordinateFemoralCuff = xCoordinateTonometer = 0;
                screenwidth = screenwidthForCuffChartInPWAMode = 0;
                femoralFlag = carotidFlag = false;
                if (GuiCommon.StartupScreen.ToUpper().Equals(CrxStructCommonResourceMsg.QuickStart) && GuiCommon.CurrentMode.Equals(CrxStructCommonResourceMsg.Pwa))
                {
                    objDefaultWindow.radtabQuickStart.Enabled = true;
                }
            }
            catch (Exception ex)
            {
                GUIExceptionHandler.HandleException(ex, this);
            }           
        }

        /**This method will check if the capture button is enabled,if yes it will try generating a report.
         * If not,then navigate the user to the setup screen
         */
        public void GenerateReportWhenCaptureIsEnabled()
        {
            if (radbtnTick.InvokeRequired)
            {
                AccessGuiControls d = new AccessGuiControls(GenerateReportWhenCaptureIsEnabled);
                this.Invoke(d);
            }
            else
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

                GuiCommon.MessageToBeDisplayed = string.Empty;
            }          
         }

        private void Capture_OnCaptureScreenTabClick(object sender, EventArgs e)
        {           
           radbtnCross.Focus();            
        }

        // Begin: AtCor-<Drop2>-<Sprint4>, TM, <SWREQ2022,SWREQ20223,SWREQ2024,SWREQ2015>,<17 August 2011>

        /**This method is used to set the Capture screen according to PWA mode.
         * It hides the tonometer chart and displays a enlarged cuff chart,it also shows an enlarge quality indicator.
         */ 
        private void ChangeCaptureScreenForPwaMode()
        {
            radProgressBarQualityIndicator.Visible = false;
            chartTonometer.Visible = false;
            guiradlblCarotidTonometer.Visible = false;

            guiradlblTonometerThresholdPart1.Visible = false;
            guiradlblTonometerThresholdPart2.Visible = false;
            guiradlblFemoralCuff.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.LblBrachialCuff);

            guiradlblFemoralCuff.Top = guiradlblCarotidTonometer.Top;
            guichartFemoralCuff.Top = chartTonometer.Top;
            radProgressBarFemoralIndicator.Top = radProgressBarQualityIndicator.Top;
            guichartFemoralCuff.Height = Height - tableLayoutPanel1.Height - guiradlblFemoralCuff.Height - 30;

            radProgressBarFemoralIndicator.Height = guichartFemoralCuff.Height;
            guiradlblFemoralThresholdPart1.Top = radProgressBarQualityIndicator.Top + (radProgressBarFemoralIndicator.Height * 60 / 100);
            guiradlblFemoralThresholdPart2.Top = radProgressBarQualityIndicator.Top + (radProgressBarFemoralIndicator.Height * 60 / 100) - (guiradlblFemoralThresholdPart2.Height / 2);
            
            // For Future use.
            // if (GuiCommon.Workflow == GuiCommon.Workflows.Quick)
            // {
            //    objDefaultWindow.radtabQuickStart.Enabled = false;
            //    objDefaultWindow.radtabResult.Enabled = false;
            // }
        }

        /**This method is used to initialise the Capture screen as per the mode selected by the user.
         */ 
        public void InitialSettingsForPwvModeCapture()
        {
            ShowGuiControlsForPwvMode();
            objDefaultWindow.radlblMessage.Text = string.Empty; 
            SetTonometerWaveformProperties();
            SetFemoralCuffWaveformProperties();
            StartCarotidTonometerCapture();
            DisplayCaptureTimeForPwvCapture();
        }

        private void ShowGuiControlsForPwvMode()
        {
            // Show Chart titles.            
            guiradlblCarotidTonometer.Visible = true;
            guiradlblFemoralCuff.Visible = true;

            // Show Charts.
            chartTonometer.Visible = true;
            guichartFemoralCuff.Visible = true;

            // Show buttons. 
            radbtnTick.Visible = true;
            radbtnCross.Visible = true;

            // Show Progress Bar.            
            radProgressBarQualityIndicator.Visible = true;
            guiradlblTonometerThresholdPart1.Visible = true;
            guiradlblTonometerThresholdPart1.BringToFront();
            guiradlblTonometerThresholdPart2.Visible = true;
            guiradlblTonometerThresholdPart2.BringToFront();

            radProgressBarFemoralIndicator.Visible = true;
            guiradlblFemoralThresholdPart1.Visible = true;
            guiradlblFemoralThresholdPart1.BringToFront();
            guiradlblFemoralThresholdPart2.Visible = true;
            guiradlblFemoralThresholdPart2.BringToFront();
        }

        /**This method is used to initialise the Capture screen as per the mode 
         */ 
        public void InitialSettingsForPwaModeCapture()
        {
            if (GuiCommon.StartupScreen.ToUpper().Equals(CrxStructCommonResourceMsg.QuickStart) && GuiCommon.CurrentMode.Equals(CrxStructCommonResourceMsg.Pwa))
            {
                objDefaultWindow.radtabQuickStart.Enabled = false;  
            }
            
            SetChartPropertiesForPwaChart();          
            StartPwaCapture();          
            DisplayCaptureTimeForPwaCapture();          
            ChangeCaptureScreenForPwaMode();
            ShowGuiControlsForPwaMode();
        }

        private void ShowGuiControlsForPwaMode()
        {
            // Show Chart title.
            guiradlblFemoralCuff.Visible = true;

            // Show Chart
            guichartFemoralCuff.Visible = true;

            // Show Button.
            radbtnTick.Visible = true;
            radbtnCross.Visible = true;

            // Show Progress bar for cuff
            radProgressBarFemoralIndicator.Visible = true;
            guiradlblFemoralThresholdPart1.Visible = true;
            guiradlblFemoralThresholdPart1.BringToFront();
            guiradlblFemoralThresholdPart2.Visible = true;
            guiradlblFemoralThresholdPart2.BringToFront();
        }

        /**This method is called in the load function of the Capture screen,it is used to subscribe to events from Dal and Business logic.
         */ 
        private void SubscribeToEvents()
        {
            // Subscribing to PWV events.
            BizEventContainer.Instance.OnBizCarotidQualityEvent += qualityIndicator_CarotidQualityEvent;
            BizEventContainer.Instance.OnBizFemoralQualityEvent += qualityIndicator_FemoraCuffEvent;
            BizEventContainer.Instance.OnBizCuffStateEvent += UpdateCuffState;
            DefaultWindow.OnCaptureScreenTabClick += Capture_OnCaptureScreenTabClick;

            // GuiCommon.OnBizErrorEventInvocation += GuiCommon_OnBizErrorEventInvocation;

            // RTOF events for PWV
            if (CrxConfigManager.Instance.PwvSettings.GuidanceBars || CrxConfigManager.Instance.PwvSettings.AutoCapture)
            {
                BizEventContainer.Instance.OnBizRTOFPWVTonometerEvent += guidanceBars_OnBizRTOFPWVTonometerEvent;
                BizEventContainer.Instance.OnBizRTOFPWVCuffEvent += guidanceBars_OnBizRTOFPWVCuffEvent;
            }

            // Capture button enable disable events.
            BizEventContainer.Instance.OnBizCaptureButtonCuffEvent += new BizCaptureButtonCuffEventHandler(Instance_EnableDisableCaptureButtonForCuffWaveform);
            BizEventContainer.Instance.OnBizCaptureButtonTonoEvent += new BizCaptureButtonTonoEventHandler(Instance_EnableDisableCaptureButtonForTonometerWaveform);  

            // Subscribing to PWA events.                     
            BizEventContainer.Instance.OnBizPWAQualityEvent += qualityIndicator_OnBizPWAQualityEvent;

            if (CrxConfigManager.Instance.PwaSettings.GuidanceBars || CrxConfigManager.Instance.PwaSettings.AutoCapture)
            {
                BizEventContainer.Instance.OnBizRTOFPWACuffEvent += guidanceBars_OnBizRTOFPWACuffEvent;
            }
        }

        private void Instance_EnableDisableCaptureButtonForTonometerWaveform(object sender, BizCaptureButtonTonoEventArgs e)
        {
            carotidFlag = e.buttonEnabled;

            // GuiCommon.ScorControllerObject.EnableDisableCaptureButton();  
            if (GuiCommon.CurrentMode.Equals(CrxStructCommonResourceMsg.Pwa))
            {
                RefreshOkButtonForPwaMode();
            }
            else
            {
                RefreshOkButtonForPwvMode();
            }
        }

        private void Instance_EnableDisableCaptureButtonForCuffWaveform(object sender, BizCaptureButtonCuffEventArgs e)
        {
            femoralFlag = e.buttonEnabled;

            // GuiCommon.ScorControllerObject.EnableDisableCaptureButton();
            if (GuiCommon.CurrentMode.Equals(CrxStructCommonResourceMsg.Pwa))
            {
                RefreshOkButtonForPwaMode(); 
            }
            else
            {
                RefreshOkButtonForPwvMode(); 
            }
        }
        
        /**This method is used to display the capture time on the capture screen when the capture is in progress.
         */ 
        private void DisplayCaptureTimeForPwaCapture()
        {
           // objDefaultWindow.radlblCaptureTime.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.GrpCaptureTime) + oMsgMgr.GetMessage(CrxStructCommonResourceMsg.GuiDisplayColon) + CrxConfigManager.Instance.PwaSettings.CaptureTime.ToString();
            switch (CrxConfigManager.Instance.PwaSettings.CaptureTime)
            {
                case (int)CrxGenPwaValue.CrxPwaCapture5Seconds:
                    objDefaultWindow.radlblCaptureTime.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.GrpCaptureTime) + oMsgMgr.GetMessage(CrxStructCommonResourceMsg.GuiDisplayColon) + oMsgMgr.GetMessage(CrxStructCommonResourceMsg.Rad5Sec);
                    break;

                case (int)CrxGenPwaValue.CrxPwaCapture10Seconds:
                    objDefaultWindow.radlblCaptureTime.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.GrpCaptureTime) + oMsgMgr.GetMessage(CrxStructCommonResourceMsg.GuiDisplayColon) + oMsgMgr.GetMessage(CrxStructCommonResourceMsg.Rad10Sec);
                    break;

                case (int)CrxGenPwaValue.CrxPwaCapture20Seconds:
                    objDefaultWindow.radlblCaptureTime.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.GrpCaptureTime) + oMsgMgr.GetMessage(CrxStructCommonResourceMsg.GuiDisplayColon) + oMsgMgr.GetMessage(CrxStructCommonResourceMsg.Rad20Sec);
                    break;

                default:
                    break;
            }
        }

        /**This method is used to set the chart properties for PWA chart.
         */ 
        private void SetChartPropertiesForPwaChart()
        {
            xCoordinatePwaChart = 0;
            screenwidthForCuffChartInPWAMode = (CrxConfigManager.Instance.PwaSettings.CaptureTime + HandShakePeriod) * SampleRate;

            // Reset number of series in the chart.
            guichartFemoralCuff.Series.Clear();

            // set y axis
            guichartFemoralCuff.ChartAreas[0].AxisY.Minimum = TonometerHeight - 1;
            guichartFemoralCuff.ChartAreas[0].AxisY.Maximum = TonometerHeight + 1;
            
            // set x axis
            guichartFemoralCuff.ChartAreas[0].AxisX.Minimum = 0;
            guichartFemoralCuff.ChartAreas[0].AxisX.Maximum = screenwidth;

            // series used for plotting the points,its chart type and the color of the graph.
            femoralCuffSeries = new Series
            {
                ChartType = SeriesChartType.FastLine,
                Color = Color.White,                
                XValueType = ChartValueType.Int32,  
                YValueType = ChartValueType.Int32,
                BorderWidth = 1
            };

            topGBSeriesForCuff = new Series
            {
                ChartType = SeriesChartType.FastLine,
                Color = Color.Transparent,
                XValueType = ChartValueType.Int32,
                YValueType = ChartValueType.Int32
            };

            topGBSeriesForCuff.BorderWidth = 1;

            bottomGBSeriesForCuff = new Series
            {
                ChartType = SeriesChartType.FastLine,
                Color = Color.Transparent,
                XValueType = ChartValueType.Int32,
                YValueType = ChartValueType.Int32
            };

            bottomGBSeriesForCuff.BorderWidth = 1;     
 
            verticalGBSeriesForCuff = new Series
            {
                ChartType = SeriesChartType.FastLine,
                Color = Color.Transparent,
                XValueType = ChartValueType.Int32,
                YValueType = ChartValueType.Int32
            };

            verticalGBSeriesForCuff.BorderWidth = 3;

            // Add the series to the chart.            
            guichartFemoralCuff.Series.Add(topGBSeriesForCuff);
            guichartFemoralCuff.Series.Add(bottomGBSeriesForCuff);
            guichartFemoralCuff.Series.Add(femoralCuffSeries);
            guichartFemoralCuff.Series.Add(verticalGBSeriesForCuff);
        }

        /**This event is fired on the tick of the timer for PWA capture,it fires every 125 milliseconds.
         */ 
        private void tmrPwaCaptureMode_Tick(object sender, EventArgs e)
        {          
            ReadValueFromBufferForPwa();         
            BizSession.Instance().DispatchCaptureData();
        }

        /** This method is called to read value from the buffer, to be plotted on the graph.This method is called during PWA capture.
         */
        private void ReadValueFromBufferForPwa()
        {
            int countdowntimerInMillisecondsForPwa = 0;
            bool cdtimerIncrementedflagForPwa = false;

            try
            {
                int startIndex = -1;
                DalPwvDataStruct structData;                
                int returnedValues = DalDataBuffer.Instance.GetNextValues(RequestedValues, ref startIndex);

                for (int i = 0; i < returnedValues; i++)
                {
                    structData = DalDataBuffer.Instance.GetValueAt(startIndex, i);

                    // this is done so that during the second inflated time the progress bar starts from 0%.
                    // previously, it used to show 100% for a fraction of a second.
                    if ((structData.countdownTimer * 1000) > countdowntimerInMillisecondsForPwa)
                    {
                        cdtimerIncrementedflagForPwa = true;
                    }

                    // since countdown timer is in seconds now converting it into milliseconds
                    countdowntimerInMillisecondsForPwa = structData.countdownTimer * 1000;

                    // if (CrxConfigManager.Instance.PwaSettings.CaptureInput.Equals(Convert.ToInt32(CrxPwaCaptureInput.Tonometer)))
                    // {
                    //    ushort tonometerData = structData.tonometerData;
                    //    PlotTonometerData(tonometerData);
                    //    GuiCommon.bizPwaobject.Append(tonometerData); 
                    // }

                    // if (CrxConfigManager.Instance.PwaSettings.CaptureInput.Equals(Convert.ToInt32(CrxPwaCaptureInput.Cuff)))
                    // {
                    //    ushort femoralCuffData = structData.cuffPulseData;
                    //    PlotFemoralCuffData(femoralCuffData);
                    //    GuiCommon.bizPwaobject.Append(femoralCuffData); 
                    // }
                    if (femoralPlotSwitch)
                    {
                        if (cuffstatechangeFlag && cdtimerIncrementedflagForPwa)
                        {
                           // System.Diagnostics.Debug.Write(Environment.NewLine + "Value for time to deflattion timer is set to 0.");
                            guiradprgbarTimeToInflatioDeflation.Minimum = 0;
                            if (countdowntimerInMillisecondsForPwa > 0)
                            {
                               // System.Diagnostics.Debug.Write(Environment.NewLine + "Value for time to deflattion timer is incrementing.");
                                guiradprgbarTimeToInflatioDeflation.Maximum = countdowntimerInMillisecondsForPwa; // - int.Parse(deflationTime.ToString()); // (int)structData.countdownTimer
                            }

                          // System.Diagnostics.Debug.Write(Environment.NewLine + "Value1 for time to deflattion timer is set to 0.");
                            guiradprgbarTimeToInflatioDeflation.Value1 = 0;
                            cuffstatechangeFlag = false;
                            cdtimerIncrementedflagForPwa = false;
                        }

                        if ((guiradprgbarTimeToInflatioDeflation.Maximum - countdowntimerInMillisecondsForPwa) > 0)
                        {
                           // System.Diagnostics.Debug.Write(Environment.NewLine + "Value1 for time to deflattion timer is set to countodown timer value which is :" + (guiradprgbarTimeToInflatioDeflation.Maximum - countdowntimerInMillisecondsForPwa).ToString()); 
                            guiradprgbarTimeToInflatioDeflation.Value1 = guiradprgbarTimeToInflatioDeflation.Maximum - countdowntimerInMillisecondsForPwa; // (int)structData.countdownTimer; // -int.Parse(deflationTime.ToString());
                        }

                        // Get time to display
                        // conver miliseconds to seconds first
                        uint seconds = structData.countdownTimer;

                        // now get minutes and seconds 
                        // uint minutes = (seconds >= 60) ? (seconds / 60) : 0;
                        // seconds = (seconds >= 60) ? (seconds % 60) : seconds;
                        // radlblTimeStatus.Text = string.Format(oMsgMgr.GetMessage(CrxStructCommonResourceMsg.LblTimestatus), oMsgMgr.GetMessage(CrxStructCommonResourceMsg.GuiDisplayColon), ((seconds >= 10) ? string.Empty : "0"), seconds);
                        radlblTimeStatus.Text = string.Format(oMsgMgr.GetMessage(CrxStructCommonResourceMsg.LblTimestatus), oMsgMgr.GetMessage(CrxStructCommonResourceMsg.GuiDisplayColon), ((seconds >= 10) ? string.Empty : "0"), seconds);
                        if (CrxConfigManager.Instance.PwaSettings.CaptureInput.Equals(Convert.ToInt32(CrxPwaCaptureInput.Cuff)))
                        {
                            ushort femoralCuffData = structData.cuffPulseData;
                            PlotFemoralCuffInPwaMode(femoralCuffData);  
                            GuiCommon.bizPwaobject.Append(femoralCuffData);
                        }
                    }
                    else
                    {
                        guiradprgbarTimeToInflatioDeflation.Maximum = 0;

                        // plot flat line for femoral when cuff is not inflated as value 0
                        // PlotFemoralCuffData(0);
                        PlotFemoralCuffInPwaMode(0); 
                        GuiCommon.bizPwaobject.Append(0);
                    }
                }
            }
            catch (Exception ex)
            {
                tmrPwaCaptureMode.Enabled = false;
                GUIExceptionHandler.HandleException(ex, this);
                if (radbtnTick.Enabled)
                {
                    DialogResult ds = RadMessageBox.Show(this, oMsgMgr.GetMessage(CrxStructCommonResourceMsg.GuiCaptureError), oMsgMgr.GetMessage(CrxStructCommonResourceMsg.SystemError), MessageBoxButtons.YesNoCancel, RadMessageIcon.Error);
                    switch (ds)
                    {
                        case DialogResult.Yes:
                            TickButtonActionForPwaMode();
                            break;
                        case DialogResult.No:
                            ShowSetupAfterCaptureAbort();
                            break;
                        default:                            
                            GuiCommon.ScorControllerObject.StopCapture();  
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

        /**This method is called when the user wants to generate a report in PWV mode.
         */ 
        public void ActionPerformedAfterClickingCancelForPwvMode()
        {
            tmrPwvCaptureMode.Enabled = false;
            GenerateReportWhenCaptureIsEnabled();
        }

        /**This method is called when the user wants to generate a report in PWA mode.
         */ 
        public void ActionPerformedAfterClickingCancelForPwaMode()
        {
            tmrPwaCaptureMode.Enabled = false;
            GenerateReportWhenCaptureIsEnabledForPwaMode();
        }

        /**This method is called when the user wants to generate a report in PWA mode.
        */ 
        private void GenerateReportWhenCaptureIsEnabledForPwaMode()
        {
            if (radbtnTick.InvokeRequired)
            {
                AccessGuiControls d = new AccessGuiControls(GenerateReportWhenCaptureIsEnabled);
                this.Invoke(d);
            }
            else
            {
                // if Ok btn is enabled and user clicks on Cancel then ask the user if he wants to generate report or abort.
                if (radbtnTick.Enabled)
                {
                    DialogResult ds = RadMessageBox.Show(this, GuiCommon.MessageToBeDisplayed + " " + oMsgMgr.GetMessage(CrxStructCommonResourceMsg.CaptureTickMsg), oMsgMgr.GetMessage(CrxStructCommonResourceMsg.SystemError), MessageBoxButtons.YesNo, RadMessageIcon.Info);
                    if (ds == DialogResult.Yes)
                    {
                        TickButtonActionForPwaMode();
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
                    CrossButtonActionForPwaMode();
                }

                GuiCommon.MessageToBeDisplayed = string.Empty;
            }
        }

        /**This method is called when the user wants to generate a report in PWA mode.
        */ 
        public void TickButtonActionForPwaMode()
        {
            try
            {
                // Adding a temporary message box saying "Calculation of Report not yet implemented."
                tmrPwaCaptureMode.Enabled = false;                       
                         
                GuiCommon.ScorControllerObject.StopCapture();
                StopTimers();
                GuiCommon.SetupToReport = false;           

                guichartFemoralCuff.Series.Clear();
                guichartFemoralCuff.Series.Remove(femoralCuffSeries);

                // Clear and remove the tonometer waveform.
                chartTonometer.Series.Clear();
                chartTonometer.Series.Remove(newSeries);                 
           
                objDefaultWindow.radlblMessage.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.GuiCaptureGeneratingReport);

                // Following code needs to be reviewed for PWA report calculation.
                pwaData = new CrxStructPWAMeasurementData();
                object pDataSetPeriph;

                if (CrxConfigManager.Instance.PwaSettings.CaptureInput.Equals(Convert.ToInt32(CrxPwaCaptureInput.Tonometer)))
                {
                    pDataSetPeriph = new CrxStructTonoPWAMeasurementData();
                }
                else
                {
                    pDataSetPeriph = new CrxStructCuffPWAMeasurementData();
                }

                PrepareArrayObjectsForPwaMode();

                if (CrxConfigManager.Instance.PwaSettings.CaptureInput.Equals(Convert.ToInt32(CrxPwaCaptureInput.Tonometer)))
                {
                    pDataSetPeriph = (object)pwaTonoStruct;
                }
                else
                {
                    pDataSetPeriph = (object)pwaCuffStruct;
                }

                // Implementation of report generation for PWA report.
                if (GuiCommon.bizPwaobject.CalculatePWAReport(pwaData, pDataSetPeriph))
                {
                    if (!string.IsNullOrEmpty(GuiCommon.bizPwaobject.GetInconclusiveNoteMsgKey()))
                    {
                        GuiCommon.InConclusiveMessageForPwaCapture = CrxMessagingManager.Instance.GetMessage(GuiCommon.bizPwaobject.GetInconclusiveNoteMsgKey());
                    }

                    // report calculation successful save report & navigate to report screen
                    StopCaptureAndSaveReportForPwaMode(pwaData, pwaCuffStruct);
                }
                else
                {
                    // report calculation failed create text file and navigate to setup
                    // CreateTextFileOnReportFailedForPwaMode();
                    GuiCommon.ScorControllerObject.CreateTextFileForFailedCapture(); 
                    ShowSetupAfterCaptureAbort();
                }                                 
            }
            catch (Exception ex)
            {
                // for any exception during report calculation create text file, show error message & report calculation failed message
                StopTimers();
                CrxLogger.Instance.Write(ex.StackTrace);                
                GuiCommon.ScorControllerObject.CreateTextFileForFailedCapture(); 
                GUIExceptionHandler.HandleException(ex, this);
                ShowSetupAfterCaptureAbort();
            }
        }

        /**This method is called when the user wants to generate a report in PWA mode and the start up screen is quickstart. 
        */ 
        public void TickButtonActionForcPwaQuickStart()
        {
            try
            {
                // Adding a temporary message box saying "Calculation of Report not yet implemented."
                tmrPwaCaptureMode.Enabled = false;

                GuiCommon.ScorControllerObject.StopCapture();
                StopTimers();

                // Clear and remove series.
                guichartFemoralCuff.Series.Clear();
                guichartFemoralCuff.Series.Remove(femoralCuffSeries);

                // Clear and remove the tonometer waveform.
                chartTonometer.Series.Clear();
                chartTonometer.Series.Remove(newSeries);

                objDefaultWindow.radlblMessage.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.GuiCaptureGeneratingReport);

                pwaData = new CrxStructPWAMeasurementData();
                object pDataSetPeriph;

                if (CrxConfigManager.Instance.PwaSettings.CaptureInput.Equals(Convert.ToInt32(CrxPwaCaptureInput.Tonometer)))
                {
                    pDataSetPeriph = new CrxStructTonoPWAMeasurementData();
                }
                else
                {
                    pDataSetPeriph = new CrxStructCuffPWAMeasurementData();
                }

                PrepareArrayObjectsForPwaMode();

                if (CrxConfigManager.Instance.PwaSettings.CaptureInput.Equals(Convert.ToInt32(CrxPwaCaptureInput.Tonometer)))
                {
                    pDataSetPeriph = (object)pwaTonoStruct;
                }
                else
                {
                    pDataSetPeriph = (object)pwaCuffStruct;
                }

                if (GuiCommon.bizPwaobject.CalculatePWAReport(pwaData, pDataSetPeriph))
                {
                    if (!string.IsNullOrEmpty(GuiCommon.bizPwaobject.GetInconclusiveNoteMsgKey()))
                    {
                        GuiCommon.InConclusiveMessageForPwaCapture = CrxMessagingManager.Instance.GetMessage(GuiCommon.bizPwaobject.GetInconclusiveNoteMsgKey());
                    }

                    // report calculation successful save report & navigate to report screen
                    StopCaptureAndSaveReportForPwaMode(pwaData, pwaCuffStruct);
                }
                else
                {
                    // report calculation failed create text file and navigate to setup
                    // CreateTextFileOnReportFailedForPwaMode();
                    GuiCommon.ScorControllerObject.CreateTextFileForFailedCapture();
                    ShowSetupAfterCaptureAbort();
                }
            }
            catch (Exception ex)
            {
                // for any exception during report calculation create text file, show error message & report calculation failed message
                StopTimers();
                CrxLogger.Instance.Write(ex.StackTrace);
                GuiCommon.ScorControllerObject.CreateTextFileForFailedCapture();
                GUIExceptionHandler.HandleException(ex, this);
                ShowSetupAfterCaptureAbort();
            }
        }

        /**This method is used to stop the capture and save the report generated into the database.
         */
        private void StopCaptureAndSaveReportForPwaMode(CrxStructPWAMeasurementData pwaMeasurementDataStruct, CrxStructCuffPWAMeasurementData pwaCuffData)
        {            
            // hourglass cursor             
            System.Windows.Forms.Cursor.Current = Cursors.WaitCursor;
                    
            GuiCommon.ScorControllerObject.StopCapture();
            StopTimers();

            CrxConfigManager crxMgrObject = CrxConfigManager.Instance;

            // check db connection
            if (dbMagr.CheckConnection(GuiCommon.ServerNameString(), crxMgrObject.GeneralSettings.SourceData) == 0)
            {
                // capture with new measurement details.... insert a new record
                // capture will always add a new measurement record in backend even if it is conducted with same measurement data
                objDefaultWindow.radlblMessage.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.GuiCaptureSavingReport);
                SavePwaReportCalculation(pwaMeasurementDataStruct, pwaCuffData);
                System.Windows.Forms.Cursor.Current = Cursors.Default;
            }
            else
            {
                DialogResult result = RadMessageBox.Show(this, GuiCommon.ConnectionErrorString(), oMsgMgr.GetMessage(CrxStructCommonResourceMsg.SystemError), MessageBoxButtons.RetryCancel, RadMessageIcon.Error);
                if (result == DialogResult.Retry)
                {
                    SavePwaReportCalculation(pwaMeasurementDataStruct, pwaCuffData); 
                }
                else
                {
                    // Navigate user back to the setup screen                    
                    ShowSetupAfterCaptureAbort();
                }
            }
        }

        /**This method is used to create a text file if the report calcuation fails.
         */ 
        public void CreateTextFileOnReportFailedForPwaMode()
        {
            StopTimers();
            objDefaultWindow.radlblMessage.Text = string.Empty;

            // report calculation failed save captured data in text file                
            // this will create text file & will save data captured so far                        
            GuiCommon.ScorControllerObject.SaveCaptureData();            

            // GetSavedfile path should only be called once.
            string captureFilePath = DalModule.Instance.GetSavedFilePath();

            // show error message alongwith filename
            RadMessageBox.Show(this, oMsgMgr.GetMessage(CrxStructCommonResourceMsg.ReportCalFailMsg) + Environment.NewLine + oMsgMgr.GetMessage(CrxStructCommonResourceMsg.GuiWaveformSaveMsg) + Environment.NewLine + captureFilePath, oMsgMgr.GetMessage(CrxStructCommonResourceMsg.SystemError), MessageBoxButtons.OK, RadMessageIcon.Error);

            // log the error
            CrxLogger.Instance.Write(oMsgMgr.GetMessage(CrxStructCommonResourceMsg.ReportCalFailMsg) + Environment.NewLine + oMsgMgr.GetMessage(CrxStructCommonResourceMsg.GuiWaveformSaveMsg) + Environment.NewLine + captureFilePath);
        }

        /**This method is called when the user clicks the cancel button to stop the capture in PWA mode.
         */ 
        private void CrossButtonActionForPwaMode()
        {
            try
            {
                tmrPwaCaptureMode.Enabled = false;
                if (GuiCommon.IsBizErrorEventRaised)
                {
                    GuiCommon.IsBizErrorEventRaised = false;
                    RadMessageBox.Show(this, GuiCommon.MessageToBeDisplayed + " " + oMsgMgr.GetMessage(CrxStructCommonResourceMsg.GuiCaptureCanNotContinue), oMsgMgr.GetMessage(CrxStructCommonResourceMsg.SystemError), MessageBoxButtons.OK, RadMessageIcon.Info);
                    ShowSetupAfterCaptureAbort();
                    return;
                }
                else
                {
                    DialogResult ds = RadMessageBox.Show(this, GuiCommon.MessageToBeDisplayed + " " + oMsgMgr.GetMessage(CrxStructCommonResourceMsg.CaptureFailed), oMsgMgr.GetMessage(CrxStructCommonResourceMsg.SystemError), MessageBoxButtons.YesNo, RadMessageIcon.Info);
                    if (ds == DialogResult.Yes)
                    {
                        ShowSetupAfterCaptureAbort();
                        Close();
                    }
                    else
                    {
                        tmrPwaCaptureMode.Enabled = true;
                    }
                }
            }
            catch (Exception ex)
            {
                GUIExceptionHandler.HandleException(ex, this);
            }
        }

        /**This method is used to handle keyboard events for PWV mode.
         */ 
        public void HandleKeyDownEventForPwvMode(KeyEventArgs e)
        {
            tmrPwvCaptureMode.Enabled = false;
            
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
                tmrPwvCaptureMode.Enabled = true;
            }
            else
            {
                e.SuppressKeyPress = true;
                tmrPwvCaptureMode.Enabled = true;
            }
        }

        /**This method is used to handle keyboard events for PWA mode.
         */ 
        public void HandleKeyDownEventForPwaMode(KeyEventArgs e)
        {
            tmrPwaCaptureMode.Enabled = false;
            if (e.KeyCode == Keys.Escape)
            {
                GenerateReportWhenCaptureIsEnabledForPwaMode();
            }
            else if (e.KeyCode == Keys.Space && radbtnTick.Enabled)
            {
                TickButtonActionForPwaMode();
                Close();
            }
            else if (e.KeyCode == Keys.Space && !radbtnTick.Enabled)
            {
                e.SuppressKeyPress = true;
                tmrPwaCaptureMode.Enabled = true;
            }
            else
            {
                e.SuppressKeyPress = true;
                tmrPwaCaptureMode.Enabled = true;
            }
        }

        /**This method is used to plot the cuff waveform in PWA mode.
         * This method is called every 125 milliseconds.
         */ 
        private void PlotFemoralCuffInPwaMode(ushort data)
        {
            try
            {
                // when cuff is not inflated data will have value 0 to plot, setting minimum y axis range for femoral chart to -10 to show flat line
                if (data == 0)
                {
                    guichartFemoralCuff.ChartAreas[0].AxisY.Minimum = -100;
                }
                else
                {
                    // if minimum value is less than 0 set it normal (data * ChartAreaMinimumY;)
                    if (guichartFemoralCuff.ChartAreas[0].AxisY.Minimum == -100)
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
                femoralCuffSeries.Points.AddXY(xCoordinatePwaChart, data);
                xCoordinatePwaChart++;

                if ((xCoordinatePwaChart > screenwidthForCuffChartInPWAMode) && (xCoordinatePwaChart - screenwidthForCuffChartInPWAMode) % TwoSecondsWindow == 1)
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
                    guichartFemoralCuff.ChartAreas[0].AxisX.Maximum = femoralCuffSeries.Points[0].XValue + screenwidthForCuffChartInPWAMode;
                }
                else if (xCoordinatePwaChart >= screenwidthForCuffChartInPWAMode)
                {
                    // do nothing in this condition.
                }
                else
                {
                    // set the x axis's minimum and maximum values.
                    guichartFemoralCuff.ChartAreas[0].AxisX.Minimum = femoralCuffSeries.Points[0].XValue;
                    guichartFemoralCuff.ChartAreas[0].AxisX.Maximum = femoralCuffSeries.Points[0].XValue + screenwidthForCuffChartInPWAMode;
                }

                if (CrxConfigManager.Instance.PwaSettings.GuidanceBars)
                {
                    // Add strip lines to the chart.                
                    topStrip.StripWidth = 1;
                    topStrip.IntervalOffset = upperValueForGuidanceBar;

                    bottomStrip.StripWidth = 1;
                    bottomStrip.IntervalOffset = lowerValueForGuidanceBar;                 
                }

                guichartFemoralCuff.Invalidate();
            }
            catch (Exception ex)
            {
                GUIExceptionHandler.HandleException(ex, this);
            }
        }

        // End: AtCor-<Drop2>-<Sprint4>, TM, <SWREQ2022,SWREQ2023,SWREQ2024,SWREQ2025>,<17 August 2011>

        // Begin: AtCor-<Drop2>-<Sprint5>, TM, <SWREQ2025,SWREQ2027,<1 September 2011>

        /**This method is used to initialize CRx objects for PWA measurement and Cuff structures.
         */ 
        private void PrepareArrayObjectsForPwaMode()
        {
            // Initialising CrxStructPWAMeasurementData structure.
            pwaData.C_RAW_SIGNALS = new float[GuiCommon.bizPwaobject.GetRawSignalArraySize()];
            pwaData.C_AV_PULSE = new float[GuiCommon.bizPwaobject.GetPulseArraySize()];
            pwaData.C_TRIGS = new short[GuiCommon.bizPwaobject.GetTrigArraySize()];
            pwaData.C_ONSETS = new short[GuiCommon.bizPwaobject.GetTrigArraySize()];
            pwaData.C_Uncal_Av = new float[GuiCommon.bizPwaobject.GetPulseArraySize()];
            pwaData.C_ResemblePulse = new float[GuiCommon.bizPwaobject.GetResembleArraySize()];
            pwaData.C_Typical = new float[GuiCommon.bizPwaobject.GetPulseArraySize()];
            pwaData.C_Forward = new float[GuiCommon.bizPwaobject.GetPulseArraySize()];
            pwaData.C_Backward = new float[GuiCommon.bizPwaobject.GetPulseArraySize()];

            // Initialising CrxStructTonoPWAMeasurementData structure.
            pwaTonoStruct = new CrxStructTonoPWAMeasurementData();
            pwaTonoStruct.P_RAW_SIGNALS = new float[GuiCommon.bizPwaobject.GetRawSignalArraySize()];
            pwaTonoStruct.P_AV_PULSE = new float[GuiCommon.bizPwaobject.GetPulseArraySize()];
            pwaTonoStruct.P_TRIGS = new short[GuiCommon.bizPwaobject.GetTrigArraySize()];
            pwaTonoStruct.P_ONSETS = new short[GuiCommon.bizPwaobject.GetTrigArraySize()];
            pwaTonoStruct.P_UNCAL_AV = new float[GuiCommon.bizPwaobject.GetPulseArraySize()];
            pwaTonoStruct.P_ResemblePulse = new float[GuiCommon.bizPwaobject.GetResembleArraySize()];

            // Initialising CrxStructCuffPWAMeasurementData structure.
            pwaCuffStruct = new CrxStructCuffPWAMeasurementData();
            pwaCuffStruct.P_RAW_SIGNALS = new float[GuiCommon.bizPwaobject.GetRawSignalArraySize()];
            pwaCuffStruct.P_AV_PULSE = new float[GuiCommon.bizPwaobject.GetPulseArraySize()];
            pwaCuffStruct.P_TRIGS = new short[GuiCommon.bizPwaobject.GetTrigArraySize()];
            pwaCuffStruct.P_ONSETS = new short[GuiCommon.bizPwaobject.GetTrigArraySize()];
            pwaCuffStruct.P_UNCAL_AV = new float[GuiCommon.bizPwaobject.GetPulseArraySize()];
            pwaCuffStruct.P_ResemblePulse = new float[GuiCommon.bizPwaobject.GetResembleArraySize()];
        }

        /**This method is used to assign -1 value to the C_TRIGS & C_ONSETS arrays of the CrxStructPWAMeasurementData 
         * if the arrays contains 0 value.
           * It takes in crx structure as input.
           */ 
        private void InitialzeOnsetsAndTrigsArray(CrxStructPWAMeasurementData cdata)
        {
            for (int i = 0; i < cdata.C_TRIGS.Length; i++)
            {
                if (cdata.C_TRIGS[i] == 0)
                {
                    cdata.C_TRIGS[i] = -1;
                }
            }

            for (int i = 0; i < cdata.C_ONSETS.Length; i++)
            {
                if (cdata.C_ONSETS[i] == 0)
                {
                    cdata.C_ONSETS[i] = -1;
                }
            }
        }

        /**This method is used to save the Pwa measurement details into the database.
         * It takes in 2 crx structures as input.
         */ 
        private void SavePwaReportCalculation(CrxStructPWAMeasurementData pwaMeasurementData, CrxStructCuffPWAMeasurementData pwaCuffData)
        {
            if (GuiCommon.StartupScreen.ToUpper().Equals(CrxStructCommonResourceMsg.QuickStart) && GuiCommon.CurrentMode.Equals(CrxStructCommonResourceMsg.Pwa))
            {
                GuiCommon.quickStartCrxPwaData = pwaMeasurementData;
                GuiCommon.quickStartCrxPwaCuffData = pwaCuffData;
                GenerateTemporaryReport(pwaMeasurementData, pwaCuffData);
            }
            else
            {
                InitialzeOnsetsAndTrigsArray(pwaMeasurementData);
                pwaMeasurementData.Simulation = CrxConfigManager.Instance.GeneralSettings.CommsPort.Equals(CrxStructCommonResourceMsg.Simulation) ? true : false;
                int iRow = dbMagr.SaveCuffPWAMeasurementDetails(pwaMeasurementData, pwaCuffData);
                if (iRow > 0)
                {
                    // redirect to report screen
                    GuiCommon.SetupToReport = false;

                    // pwaMeasurementData.PWA_Id;  
                    GuiCommon.PwvCurrentStudyDatetime = pwaMeasurementData.StudyDateTime.ToString();
                    guichartFemoralCuff.Series.Clear();
                    guichartFemoralCuff.Series.Remove(femoralCuffSeries);

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
                        GuiCommon.ScorControllerObject.LoadReport();
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
                    objDefaultWindow.radpgTabCollection.SelectedPage = objDefaultWindow.guiradgrpbxPwvDistanceMethod;
                }
            }
        }

        /**This method is called to generate a temporary report in quickstart mode,data caluclated in this method will be shown in the result tab.
         */ 
        private void GenerateTemporaryReport(CrxStructPWAMeasurementData pwaMeasurementData, CrxStructCuffPWAMeasurementData pwaCuffData)
        {
            GuiCommon.PwvCurrentStudyDatetime = pwaMeasurementData.StudyDateTime.ToString();
            guichartFemoralCuff.Series.Clear();
            guichartFemoralCuff.Series.Remove(femoralCuffSeries);

            // GuiCommon.CaptureToReport = true;
            objDefaultWindow.radpgTabCollection.SelectedPage = objDefaultWindow.radtabResult;
            objDefaultWindow.radlblMessage.Text = string.Empty;
            objDefaultWindow.radlblCaptureTime.Text = string.Empty;  
            objDefaultWindow.radtabResult.Enabled = true;

            if (!objDefaultWindow.radtabResult.Enabled)
            {
                return;
            }

           // GuiCommon.ScorControllerObject.LoadTemporaryReport();              

            // disable setting tab on menu bar
            objDefaultWindow.guiradmnuitemSettings.Enabled = false;
            objDefaultWindow.guiradmnuSystemKey.Enabled = false;
            objDefaultWindow.guicmbxCurrentMode.Enabled = false;

            // disable settings, backup, restore & cross button
            objDefaultWindow.guiradmnuitemSettings.Enabled = false;
            objDefaultWindow.guiradmnuScor.Enabled = true;
            objDefaultWindow.radtabQuickStart.Enabled = true;
            objDefaultWindow.radtabCapture.Enabled = false;
        }

        /**This event is used to provide quality indicator information for PWa.
         */ 
        private void qualityIndicator_OnBizPWAQualityEvent(object sender, BizPWAQualityEventArgs e)
        {
            try
            {                
                if (BizInfo.Instance().OptionCPWA)
                {    
                    /*
                    // System.Diagnostics.Debug.Write(Environment.NewLine + "Inside qualityIndicator_FemoraCuffEvent for PWa mode.");
                    // femoralFlagPwaMode = e.enableOkayButton;
                    // RefreshOkButton();
                    if (e.enableOkayButton)
                    {
                        // System.Diagnostics.Debug.Write(Environment.NewLine + "Signal Strength is good for PWA mode.");   
                        // show green color in the progress bar.
                        prim2.BackColor = Color.FromArgb(225, 240, 225);
                        prim2.BackColor2 = Color.FromArgb(1, 92, 1);
                        prim2.BackColor3 = Color.FromArgb(1, 92, 1);
                        prim2.BackColor4 = Color.FromArgb(225, 240, 225);

                        //radProgressBarFemoralIndicator.Value1 = GoodFemoralQualityIndicatorValue;
                        radProgressBarFemoralIndicator.Value1 = e.signalStrengthHeight; 
                    }

                    if (!e.enableOkayButton)
                    {
                        // System.Diagnostics.Debug.Write(Environment.NewLine + "Signal Strength is bad for PWA mode.");   
                        // show red color in the progress bar.                
                        prim2.BackColor = Color.FromArgb(248, 237, 234);
                        prim2.BackColor2 = Color.FromArgb(210, 67, 39);
                        prim2.BackColor3 = Color.FromArgb(210, 67, 39);
                        prim2.BackColor4 = Color.FromArgb(248, 237, 234);
                        // radProgressBarFemoralIndicator.Value1 = BadFemoralQualityIndicatorValue;
                        radProgressBarFemoralIndicator.Value1 = e.signalStrengthHeight;
                    }
                     */

                    radProgressBarFemoralIndicator.Value1 = e.signalStrengthHeight;
                    if (e.signalStrengthColor.Equals(Color.Red))
                    {
                        prim2.BackColor = Color.FromArgb(248, 237, 234);
                        prim2.BackColor2 = Color.FromArgb(210, 67, 39);
                        prim2.BackColor3 = Color.FromArgb(210, 67, 39);
                        prim2.BackColor4 = Color.FromArgb(248, 237, 234);
                    }
                    else if (e.signalStrengthColor.Equals(Color.Yellow))
                    {
                        prim2.BackColor = Color.FromArgb(249, 249, 239);
                        prim2.BackColor2 = Color.FromArgb(208, 208, 2);
                        prim2.BackColor3 = Color.FromArgb(208, 208, 2);
                        prim2.BackColor4 = Color.FromArgb(249, 249, 239);
                    }
                    else
                    {
                        prim2.BackColor = Color.FromArgb(225, 240, 225);
                        prim2.BackColor2 = Color.FromArgb(1, 92, 1);
                        prim2.BackColor3 = Color.FromArgb(1, 92, 1);
                        prim2.BackColor4 = Color.FromArgb(225, 240, 225);
                    }
                }

                if (BizInfo.Instance().OptionTPWA)
                {
                    // to be implemented same as PWV tonometer.                  
                    /*
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
                    //RefreshOkButton();
                    */

                    radProgressBarQualityIndicator.Value1 = e.signalStrengthHeight;

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
                }
            }
            catch (Exception ex)
            {
                GUIExceptionHandler.HandleException(ex, this);
            }
        }

        /**This event is used to provide guidance bar information for PWA cuff waveforms.
         */ 
        private void guidanceBars_OnBizRTOFPWACuffEvent(object sender, BizRTOFEventArgs e)
        {
            try
            {
                if (CrxConfigManager.Instance.PwaSettings.GuidanceBars)
                {
                    if (e.data_rtof.upper_guidance_band != BizConstants.DEFAULT_VALUE)
                    {
                        upperValueForGuidanceBar = e.data_rtof.upper_guidance_band;
                        lowerValueForGuidanceBar = e.data_rtof.lower_guidance_band;

                        SetColorForWaveform(e, femoralCuffSeries);
                        SetColorForPulseVariation(e, topGBSeriesForCuff, bottomGBSeriesForCuff, verticalGBSeriesForCuff);                        
                    }
                    else
                    {
                        topGBSeriesForCuff.Points.Clear();
                        bottomGBSeriesForCuff.Points.Clear();
                        verticalGBSeriesForCuff.Points.Clear();
                        upperValueForGuidanceBar = lowerValueForGuidanceBar = -9999;
                        
                        femoralCuffSeries.Color = Color.White;
                        femoralCuffSeries.BorderWidth = 1;
                    }

                    if (upperValueForGuidanceBar != -9999 || lowerValueForGuidanceBar != -9999)
                    {
                        topGBSeriesForCuff.Points.Clear();
                        topGBSeriesForCuff.Points.AddXY(guichartFemoralCuff.ChartAreas[0].AxisX.Minimum, upperValueForGuidanceBar);
                        topGBSeriesForCuff.Points.AddXY(guichartFemoralCuff.ChartAreas[0].AxisX.Maximum, upperValueForGuidanceBar);

                        bottomGBSeriesForCuff.Points.Clear();
                        bottomGBSeriesForCuff.Points.AddXY(guichartFemoralCuff.ChartAreas[0].AxisX.Minimum, lowerValueForGuidanceBar);
                        bottomGBSeriesForCuff.Points.AddXY(guichartFemoralCuff.ChartAreas[0].AxisX.Maximum, lowerValueForGuidanceBar);

                        verticalGBSeriesForCuff.Points.Clear();
                        verticalGBSeriesForCuff.Points.AddXY(guichartFemoralCuff.ChartAreas[0].AxisX.Maximum - 2, lowerValueForGuidanceBar);
                        verticalGBSeriesForCuff.Points.AddXY(guichartFemoralCuff.ChartAreas[0].AxisX.Maximum - 2, upperValueForGuidanceBar);  
                    }
                }

                if (CrxConfigManager.Instance.PwaSettings.AutoCapture && e.data_rtof.capture)
                {
                    GuiCommon.ScorControllerObject.CalculateReportAfterSuccessfulCapture();
                    Close();
                }
            }
            catch (Exception ex)
            {
                GUIExceptionHandler.HandleException(ex, this);
            }
        }

        /**This event is used to provide guidance bar information for PWV tonometer waveforms.
         */ 
        private void guidanceBars_OnBizRTOFPWVTonometerEvent(object sender, BizRTOFEventArgs e)
        {
            try
            {
                if (CrxConfigManager.Instance.PwvSettings.GuidanceBars)
                {
                    if (e.data_rtof.upper_guidance_band != BizConstants.DEFAULT_VALUE)
                    {
                        upperValueForGuidanceBarTonometerChart = e.data_rtof.upper_guidance_band;                        
                        lowerValueForGuidanceBarTonometerChart = e.data_rtof.lower_guidance_band;

                        SetColorForTonometerWaveform(e);
                        SetColorForPulseVariation(e, topGBSeries, bottomGBSeries, verticalGBSeries);                        
                    }
                    else
                    {
                        topGBSeries.Points.Clear();
                        bottomGBSeries.Points.Clear();
                        verticalGBSeries.Points.Clear();
                        upperValueForGuidanceBarTonometerChart = lowerValueForGuidanceBarTonometerChart = -9999;    
                        
                        newSeries.Color = Color.White;
                        newSeries.BorderWidth = 1;
                    }

                    if (upperValueForGuidanceBarTonometerChart != -9999 || lowerValueForGuidanceBarTonometerChart != -9999)
                    {                        
                        topGBSeries.Points.Clear();
                        topGBSeries.Points.AddXY(chartTonometer.ChartAreas[0].AxisX.Minimum, upperValueForGuidanceBarTonometerChart + 5);
                        topGBSeries.Points.AddXY(chartTonometer.ChartAreas[0].AxisX.Maximum, upperValueForGuidanceBarTonometerChart + 5);

                        bottomGBSeries.Points.Clear();
                        bottomGBSeries.Points.AddXY(chartTonometer.ChartAreas[0].AxisX.Minimum, lowerValueForGuidanceBarTonometerChart + 5);
                        bottomGBSeries.Points.AddXY(chartTonometer.ChartAreas[0].AxisX.Maximum, lowerValueForGuidanceBarTonometerChart + 5);

                        verticalGBSeries.Points.Clear();
                        verticalGBSeries.Points.AddXY(chartTonometer.ChartAreas[0].AxisX.Maximum - 2, lowerValueForGuidanceBarTonometerChart + 5);
                        verticalGBSeries.Points.AddXY(chartTonometer.ChartAreas[0].AxisX.Maximum - 2, upperValueForGuidanceBarTonometerChart + 5);                        
                    }
                }

                isTonometerCaptureTrueForAutoCapture = e.data_rtof.capture;                
                GenerateReport();
            }
            catch (Exception ex)
            {
                GUIExceptionHandler.HandleException(ex, this);
            }
        }

        /**This event is used to provide guidance bar information for PWV cuff waveforms.
        */ 
        private void guidanceBars_OnBizRTOFPWVCuffEvent(object sender, BizRTOFEventArgs e)
        {
            try
            {
                if (CrxConfigManager.Instance.PwvSettings.GuidanceBars)
                {
                    if (e.data_rtof.upper_guidance_band != BizConstants.DEFAULT_VALUE)
                    {
                        upperValueForGuidanceBar = e.data_rtof.upper_guidance_band;
                        lowerValueForGuidanceBar = e.data_rtof.lower_guidance_band;

                        SetColorForWaveform(e, femoralCuffSeries);
                        SetColorForPulseVariation(e, topGBSeriesForCuff, bottomGBSeriesForCuff, verticalGBSeriesForCuff);                        
                    }
                    else
                    {
                        topGBSeriesForCuff.Points.Clear();
                        bottomGBSeriesForCuff.Points.Clear();
                        verticalGBSeriesForCuff.Points.Clear();
                        upperValueForGuidanceBar = lowerValueForGuidanceBar = -9999;
                        
                        femoralCuffSeries.Color = Color.White;
                        femoralCuffSeries.BorderWidth = 1;
                    }

                    if (upperValueForGuidanceBar != -9999 || lowerValueForGuidanceBar != -9999)
                    {
                        topGBSeriesForCuff.Points.Clear();
                        topGBSeriesForCuff.Points.AddXY(guichartFemoralCuff.ChartAreas[0].AxisX.Minimum, upperValueForGuidanceBar);
                        topGBSeriesForCuff.Points.AddXY(guichartFemoralCuff.ChartAreas[0].AxisX.Maximum, upperValueForGuidanceBar);   

                        bottomGBSeriesForCuff.Points.Clear();
                        bottomGBSeriesForCuff.Points.AddXY(guichartFemoralCuff.ChartAreas[0].AxisX.Minimum, lowerValueForGuidanceBar);
                        bottomGBSeriesForCuff.Points.AddXY(guichartFemoralCuff.ChartAreas[0].AxisX.Maximum, lowerValueForGuidanceBar);

                        verticalGBSeriesForCuff.Points.Clear();
                        verticalGBSeriesForCuff.Points.AddXY(guichartFemoralCuff.ChartAreas[0].AxisX.Maximum - 2, lowerValueForGuidanceBar);
                        verticalGBSeriesForCuff.Points.AddXY(guichartFemoralCuff.ChartAreas[0].AxisX.Maximum - 2, upperValueForGuidanceBar);  
                    }
                }
               
                isFemoralCuffCaptureTrueForAutoCapture = e.data_rtof.capture;                
                GenerateReport();
            }
            catch (Exception ex)
            {
                GUIExceptionHandler.HandleException(ex, this);
            }
        }          

        /**This method is used to Set the color of the waveform when guidance bar option is checked.
         */ 
        private void SetColorForWaveform(BizRTOFEventArgs data, Series chartseries)
        {            
            switch (data.data_rtof.waveform_color)
            {
                case RTOF_COLOR.clLime:
                    chartseries.Color = Color.Green;
                    chartseries.BorderWidth = 3;
                    break;
                case RTOF_COLOR.clRed:
                    chartseries.Color = Color.Red;
                    chartseries.BorderWidth = 3;
                    break;
                case RTOF_COLOR.clWhite:
                    chartseries.Color = Color.White;
                    chartseries.BorderWidth = 1;
                    break;
                case RTOF_COLOR.clYellow:
                    chartseries.Color = Color.Yellow;
                    chartseries.BorderWidth = 3;
                    break;
                default: 
                    break;
            }
        }

        /** This method is used to set the color of the pulse variation when the guidance bar option is checked.
         */
        private void SetColorForPulseVariation(BizRTOFEventArgs data, Series chartTopStripLine, Series chartBottomStripLine, Series verticalSeries)
        {
            switch (data.data_rtof.pulse_height_variation_color)
            {
                case RTOF_COLOR.clLime:
                    chartTopStripLine.Color = Color.Green;
                    break;
                case RTOF_COLOR.clRed:
                    chartTopStripLine.Color = Color.Red;
                    break;
                case RTOF_COLOR.clWhite:
                    chartTopStripLine.Color = Color.White;
                    break;
                case RTOF_COLOR.clYellow:
                    chartTopStripLine.Color = Color.Yellow;
                    break;
                default:
                    break;
            }

            switch (data.data_rtof.baseline_variation_color)
            {
                case RTOF_COLOR.clLime:
                    chartBottomStripLine.Color = Color.Green;
                    break;
                case RTOF_COLOR.clRed:
                    chartBottomStripLine.Color = Color.Red;
                    break;
                case RTOF_COLOR.clWhite:
                    chartBottomStripLine.Color = Color.White;
                    break;
                case RTOF_COLOR.clYellow:
                    chartBottomStripLine.Color = Color.Yellow;
                    break;
                default:
                    break;
            }

            switch (data.data_rtof.pulse_height_color)
            {
                case RTOF_COLOR.clLime:
                    verticalSeries.Color = Color.Green;
                    break;
                case RTOF_COLOR.clRed:
                    verticalSeries.Color = Color.Red;
                    break;
                case RTOF_COLOR.clWhite:
                    verticalSeries.Color = Color.White;
                    break;
                case RTOF_COLOR.clYellow:
                    verticalSeries.Color = Color.Yellow;
                    break;
                default:
                    break;
            }
        }

        /**This method is used to set the height color of the vertical guidance bar when guidance bar option is checked.
         */ 
        private void SetPulseHeightColor(BizRTOFEventArgs data)
        {
            CrxLogger.Instance.Write("Color for Femoral Chart: " + data.data_rtof.pulse_height_color);

            // to be implemented.
            switch (data.data_rtof.pulse_height_color)
            {
                case RTOF_COLOR.clLime:
                    pulseHeightColor = pulseHeightColorForTonometer = Color.Green;
                    break;
                case RTOF_COLOR.clRed:
                    pulseHeightColor = pulseHeightColorForTonometer = Color.Red;
                    break;
                case RTOF_COLOR.clWhite:
                    pulseHeightColor = pulseHeightColorForTonometer = Color.White;
                    break;
                case RTOF_COLOR.clYellow:
                    pulseHeightColor = pulseHeightColorForTonometer = Color.Yellow;
                    break;
                default:
                    break;
            }
        }        

        /**This method is used to set the color of the Tonometer waveform when the Guidance bar option is checked.
         */ 
        private void SetColorForTonometerWaveform(BizRTOFEventArgs data)
        {
            if (newSeries == null)
            {
                 newSeries = new Series
                            {
                                ChartType = SeriesChartType.FastLine,
                                Color = Color.White,
                                XValueType = ChartValueType.Int32,
                                YValueType = ChartValueType.Int32
                            };
            }

            switch (data.data_rtof.waveform_color)
            {
                case RTOF_COLOR.clLime:
                    newSeries.Color = Color.Green;
                    newSeries.BorderWidth = 3;
                    break;
                case RTOF_COLOR.clRed:
                    newSeries.Color = Color.Red;
                    newSeries.BorderWidth = 3;
                    break;
                case RTOF_COLOR.clWhite:
                    newSeries.Color = Color.White;
                    newSeries.BorderWidth = 1;
                    break;
                case RTOF_COLOR.clYellow:
                    newSeries.Color = Color.Yellow;
                    newSeries.BorderWidth = 3;
                    break;
                default:
                    break;
            }
        }

        /**This method is used to generate PWV report when Auto capture is enabled.
         */ 
        private void GenerateReport()
        {            
            if (CrxConfigManager.Instance.PwvSettings.AutoCapture && isFemoralCuffCaptureTrueForAutoCapture && isTonometerCaptureTrueForAutoCapture)
            {
                GuiCommon.ScorControllerObject.CalculateReportAfterSuccessfulCapture();
                Close();
            }
        }       

        // End: AtCor-<Drop2>-<Sprint5>, TM, <SWREQ2025,SWREQ2027,<1 September 2011>
    }
}