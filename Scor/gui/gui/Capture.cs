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

        Series newSeries;
        Series femoralCuffSeries;

        double screenwidth;
        double signalStrength;
        ProgressBarPrimitive prim1;
        ProgressBarPrimitive prim2;

        // object of Config Manager                 
        CrxConfigManager obj;
        BizPWV bizObj;        
        
        public Capture(DefaultWindow defWindow)
        {
            InitializeComponent();
            GuiCommon.SetFontForControls(this);
            SetTextForCaptureTab();
            objDefaultWindow = defWindow;
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
                CrxLogger.Instance.Write("Loading Capture Form");

                bizObj = (BizPWV)BizSession.Instance().measurement;
                                
                radbtnCross.Focus();

                // tmrInflationTimer.Enabled = true;
                CrxLogger.Instance.Write("Reading Configuration Settings");
                obj = CrxConfigManager.Instance;
                obj.GetGeneralUserSettings();
                obj.GetPwvUserSettings();

                CrxLogger.Instance.Write("Subscribing to Events");
                BizEventContainer.Instance.OnBizCarotidQualityEvent += qualityIndicator_CarotidQualityEvent;
                BizEventContainer.Instance.OnBizFemoralQualityEvent += qualityIndicator_FemoraCuffEvent;
                BizEventContainer.Instance.OnBizCuffStateEvent += UpdateCuffState;
                DefaultWindow.OnCaptureScreenTabClick += Capture_OnCaptureScreenTabClick;                
                
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
                radbtnTick.Enabled = false;

                // disable settings, backup, restore & cross button
                objDefaultWindow.guiradmnuitemSettings.Enabled = false;

                objDefaultWindow.guiradmnuScor.Enabled = false;

                // disable seup & report tabs
                objDefaultWindow.radtabReport.Enabled = false;
                objDefaultWindow.guiradgrpbxPwvDistanceMethod.Enabled = false;

                CrxLogger.Instance.Write("Capture Form Loading DONE");

                DisplayCaptureTime();
            }
            catch (Exception ex)
            {
                StopTimers();
                GUIExceptionHandler.HandleException(ex, this);
            }
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
                // radlblcuffQuality.Visible = true;               
                femoralFlag = e.enableOkayButton;                
                RefreshOkButton();

                if (e.signalStrengthIsGood)
                {
                    // show tick image                   
                    prim2.BackColor = Color.FromArgb(225, 240, 225);
                    prim2.BackColor2 = Color.FromArgb(1, 92, 1);
                    prim2.BackColor3 = Color.FromArgb(1, 92, 1);
                    prim2.BackColor4 = Color.FromArgb(225, 240, 225);
                    radProgressBarFemoralIndicator.Value1 = GoodFemoralQualityIndicatorValue; 
                }

                if (!e.signalStrengthIsGood)
                {
                    // show cross image                   
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
                chartTonometer.ChartAreas[0].AxisY.Minimum = e.signalMinimum * GuiConstants.ChartAreaMinimumY;
                chartTonometer.ChartAreas[0].AxisY.Maximum = e.signalMaximum * GuiConstants.ChartAreaMaximumY;
                CrxLogger.Instance.Write(e.signalMaximum.ToString());
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
                // dalModuleObj.StartCapture(obj.PwvSettings.CaptureTime, SampleRate);

                // dalDataBufferObj = DalDataBuffer.Instance;
                // Start capturing                
                bizObj.StartCapture();
                timer1.Enabled = true;
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
            uint seconds;
            uint minutes;
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

                    if ((structData.countdownTimer * 1000) > countdowntimerInMilliseconds)
                    {
                        cdtimerIncrementedflag = true;
                    }

                    // since countdown timer is in seconds now converting it into milliseconds
                    countdowntimerInMilliseconds = structData.countdownTimer * 1000;
                    short tonometerData = (short)structData.tonometerData;
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
                        seconds = structData.countdownTimer;

                        // now get minutes and seconds 
                        minutes = (seconds >= 60) ? (seconds / 60) : 0;
                        seconds = (seconds >= 60) ? (seconds % 60) : seconds;
                        radlblTimeStatus.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.LblTimestatus) + " " + minutes.ToString() + oMsgMgr.GetMessage(CrxStructCommonResourceMsg.GuiDisplayColon) + ((seconds >= 10) ? string.Empty : "0") + seconds.ToString();

                        short femoralCuffData = (short)structData.cuffPulseData;
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
        private void PlotTonometerData(short tonometerData)
        {
            try
            {
                int data = tonometerData;

                // set the maximum y-axis,if the incoming data has a point greater than the existing y-axis value then set the new data point as the y-axix maximum.
                if (data > chartTonometer.ChartAreas[0].AxisY.Maximum)
                {
                    chartTonometer.ChartAreas[0].AxisY.Maximum = data * GuiConstants.ChartAreaMaximumY;
                }

                if (data < chartTonometer.ChartAreas[0].AxisY.Minimum)
                {
                    chartTonometer.ChartAreas[0].AxisY.Minimum = data * GuiConstants.ChartAreaMinimumY;
                }

                // Add new data point to its series.               
                newSeries.Points.AddXY(xCoordinateTonometer, data);
                xCoordinateTonometer++;

                if (xCoordinateTonometer > screenwidth)
                {
                    newSeries.Points.RemoveAt(0);
                }

                // set the x axis's minimum and maximum values.
                chartTonometer.ChartAreas[0].AxisX.Minimum = newSeries.Points[0].XValue;
                chartTonometer.ChartAreas[0].AxisX.Maximum = newSeries.Points[0].XValue + screenwidth;
                chartTonometer.Invalidate();
            }
            catch (Exception ex)
            {
                GUIExceptionHandler.HandleException(ex, this);
            }
        }

        /**This method is called to plot femoral cuff data.         
         */
        private void PlotFemoralCuffData(short femoralCuffData)
        {
            try
            {
                int data = femoralCuffData;

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

                if (xCoordinateFemoralCuff > screenwidth)
                {
                    femoralCuffSeries.Points.RemoveAt(0);
                }

                // set the x axis's minimum and maximum values.
                guichartFemoralCuff.ChartAreas[0].AxisX.Minimum = femoralCuffSeries.Points[0].XValue;
                guichartFemoralCuff.ChartAreas[0].AxisX.Maximum = femoralCuffSeries.Points[0].XValue + screenwidth;
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
            chartTonometer.ChartAreas[0].AxisY.Minimum = TonometerHeight;
            chartTonometer.ChartAreas[0].AxisY.Maximum = TonometerHeight;
            signalStrength = 0;

            // set x axis
            chartTonometer.ChartAreas[0].AxisX.Minimum = 0;
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
            guichartFemoralCuff.ChartAreas[0].AxisY.Minimum = TonometerHeight;
            guichartFemoralCuff.ChartAreas[0].AxisY.Maximum = TonometerHeight;
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
            if (!radbtnTick.Enabled)
            {
                return;
            }

            TickButtonAction();
            Close();
        }

        /** This event is fired when the user clicks on the cross button.
         */
        private void radbtnCross_Click(object sender, EventArgs e)
        {
            timer1.Enabled = false;
            GenerateReportWhenCaptureIsEnabled();
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
            RadMessageBox.Show(this, oMsgMgr.GetMessage(CrxStructCommonResourceMsg.ReportCalFailMsg) + Environment.NewLine + oMsgMgr.GetMessage(CrxStructCommonResourceMsg.GuiWaveformSaveMsg) + Environment.NewLine + captureFilePath, oMsgMgr.GetMessage(CrxStructCommonResourceMsg.ExecError), MessageBoxButtons.OK, RadMessageIcon.Error);

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
            
            BizSession.Instance().StopCapture();            
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
                DialogResult ds = RadMessageBox.Show(this, oMsgMgr.GetMessage(CrxStructCommonResourceMsg.CaptureFailed), oMsgMgr.GetMessage(CrxStructCommonResourceMsg.Information), MessageBoxButtons.YesNo, RadMessageIcon.Info);
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
                GuiCommon.CaptureChildForm = null;
                GuiCommon.InvokeCaptureClosing(false);
                objDefaultWindow.tmrImposeWaitTime.Interval = int.Parse(ConfigurationManager.AppSettings["WaitInterval"]);
                GuiCommon.IsWaitIntervalImposed = true;
                objDefaultWindow.tmrImposeWaitTime.Start();
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
                DialogResult ds = RadMessageBox.Show(this, oMsgMgr.GetMessage(CrxStructCommonResourceMsg.CaptureTickMsg), oMsgMgr.GetMessage(CrxStructCommonResourceMsg.Information), MessageBoxButtons.YesNo, RadMessageIcon.Info);
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
