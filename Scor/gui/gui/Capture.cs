/*
     Copyright (C) ATCOR MEDICAL PTY LTD, 2010
 
     Filename     :     Capture screen
        
     Author       :     Nitesh Chhedda
 
     Description  :     Functionality implemented for Capture.
*/
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using Telerik.WinControls.Primitives;
using Telerik.WinControls;
using System.Windows.Forms.DataVisualization.Charting;
using AtCor.Scor.CrossCutting.Messaging;
using AtCor.Scor.BusinessLogic;
using AtCor.Scor.CrossCutting;
using AtCor.Scor.CrossCutting.Configuration;
using AtCor.Scor.CrossCutting.DatabaseManager;
using AtCor.Scor.CrossCutting.Logging;
using AtCor.Scor.DataAccess;     
using System.Threading;
using System.Configuration;
using System.IO;
using biz_stub;

namespace AtCor.Scor.Gui.Presentation
{
    public partial class Capture : Telerik.WinControls.UI.RadForm
    {
        #region Set constant values

        const int HandShakePeriod = 2;
        const int SampleRate = 256;
        const int TonometerHeight = 300;
        const int QualityIndicatorHeight = 500;
        const double ChartAreaMinimumY = 0.96;
        const double ChartAreaMaximumY = 1.04;
        static int inflationTick = 0;
        static int deflationTick = 0;
        static uint xCoordinateTonometer = 0;
        static uint xCoordinateFemoralCuff = 0;
        int minutes = 3;
        int seconds = 00;
        int deflationSeconds = 00;
        int deflationMinutes = 00;
        bool carotidFlag = false; // to check for carotid quality indicator
        bool femoralFlag = false; // to check for femoral quality indicator
        volatile bool femoralPlotSwitch = false;             
        volatile bool cuffstatechange_flag = false;
        
        #endregion        

        public static event EventHandler OnAbortInitializeTimer;

        public static event EventHandler OnReportTabClick;

        Series newSeries;
        Series femoralCuffSeries;
        Series flatLineSeries;
        double screenwidth;
        double signalStrength;
        ProgressBarPrimitive prim1;        
        CrxLogger oLogObject = CrxLogger.Instance;
        
        // object of Config Manager         
        CrxMessagingManager oMsgMgr = CrxMessagingManager.Instance;
        CrxConfigManager obj;
        string captureTime = string.Empty;
        ////DalDataBuffer dalDataBufferObj;
        private DefaultWindow objDefaultWindow;
        BizPWV bizObj;
        CrxDBManager dbMagr = CrxDBManager.Instance;

        /**This is the constructor fot the capture window.It is used to set the text for all the label controls on this page.
         */ 
        public Capture()
        {
            InitializeComponent();
            SetTextForCaptureTab();
            BizSession.Instance();            
        }

        public Capture(DefaultWindow defWindow)
        {
            InitializeComponent();
            SetTextForCaptureTab();
            objDefaultWindow = defWindow;            
        }

        /** This method is called to set the text for the label controls.
         */ 
        private void SetTextForCaptureTab()
        {
            try
            {
                guiradlblCarotidTonometer.Text = oMsgMgr.GetMessage("LBL_TONOMETER");
                guiradlblFemoralCuff.Text = oMsgMgr.GetMessage("LBL_FEMORALCUFF");
                radlblTimeStatus.Text = oMsgMgr.GetMessage("LBL_TIMESTATUS");
                radbtnTick.Text = oMsgMgr.GetMessage("BTN_OK");
                radbtnCross.Text = oMsgMgr.GetMessage("BTN_CANCEL");
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
                
                BizFacade.Instance().SimulateCaptureData();
                
                radbtnCross.Focus();

               // tmrInflationTimer.Enabled = true;
                CrxLogger.Instance.Write("Reading Configuration Settings");
                obj = CrxConfigManager.Instance;
                obj.GetGeneralUserSettings();
                obj.GetPwvUserSettings();

                CrxLogger.Instance.Write("Subscribing to Events");
                BizEventContainer.Instance.OnBizCarotidQualityEvent += new BizCarotidQualityEventHandler(qualityIndicator_CarotidQualityEvent);
                BizEventContainer.Instance.OnBizFemoralQualityEvent += new BizFemoralQualityEventHandler(qualityIndicator_FemoraCuffEvent);
                BizEventContainer.Instance.OnBizCountdownTimerEvent += new BizCountdownTimerEventHandler(UpdateCountdown);
                BizEventContainer.Instance.OnBizCuffStateEvent += new BizCuffStateEventHandler(UpdateCuffState);
                                
                // DataAccess.DalEventContainer.Instance.OnDalCuffStatusEvent += new DalCuffStatusEventHandler_ORI(Instance_OnDalCuffStatusEvent);
                ////deepak

                SetTonometerWaveformProperties();
                SetFemoralCuffWaveformProperties(); // vibhuti: setting femoral properties as need to show flat line 
                StartCarotidTonometerCapture();

                // vibhuti: initially make progress bar & labels invisible
                guiradprgbarTimeToInflatioDeflation.Visible = false;
                radlblTimeStatus.Visible = false;
                guiradprgbarTimeToInflatioDeflation.Value1 = 0;
                guiradprgbarTimeToInflatioDeflation.Maximum = 0;
               
                // Quality indicator ProgressBarSetup
                prim1 = (ProgressBarPrimitive)this.radProgressBarQualityIndicator.ProgressBarElement.Children[1];
                radProgressBarQualityIndicator.Minimum = 0;
                radProgressBarQualityIndicator.Maximum = QualityIndicatorHeight;
                prim1.BackColor = prim1.BackColor2 = prim1.BackColor3 = prim1.BackColor4 = Color.Red;
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
                case 5:
                    objDefaultWindow.radlblCaptureTime.Text = oMsgMgr.GetMessage("GRP_CAPTURE_TIME") + ": " + oMsgMgr.GetMessage("RAD_5_SEC");
                    break;
                case 10:
                    objDefaultWindow.radlblCaptureTime.Text = oMsgMgr.GetMessage("GRP_CAPTURE_TIME") + ": " + oMsgMgr.GetMessage("RAD_10_SEC");
                    break;
                case 20:
                    objDefaultWindow.radlblCaptureTime.Text = oMsgMgr.GetMessage("GRP_CAPTURE_TIME") + ": " + oMsgMgr.GetMessage("RAD_20_SEC");
                    break;            
            }           
        }

         /** This method is used to resume plotting of femoral chart series after cuff state is inflated
         * */
        private void ResumeFemoralChartSeries(object sender, EventArgs e)
        {
            try
            {
                if (InvokeRequired)
                {
                    this.Invoke(new EventHandler(ResumeFemoralChartSeries));
                    return;
                }

                radlblTimeStatus.Visible = true;
                SetFemoralCuffWaveformProperties();
            }
            catch (Exception ex)
            {
                GUIExceptionHandler.HandleException(ex, this);
            }
        }

        /** This method clears femoral chart series
         * */
        private void ClearFemoralChartSeries(object sender, EventArgs e)
        {
            if (InvokeRequired)
            {
                this.Invoke(new EventHandler(ClearFemoralChartSeries));
                return;
            }

            radlblTimeStatus.Visible = false;
            guichartFemoralCuff.Series.Clear();
            guichartFemoralCuff.Series.Remove(femoralCuffSeries);

            // vibhuti: make progress bar invisible & show cross image
            guiradprgbarTimeToInflatioDeflation.Visible = false;
            radlblcuffQuality.Image = new Bitmap(Path.GetFullPath(ConfigurationManager.AppSettings["QualityCrossImage"].ToString()));          
        }

        /** This method plots a flat line when cuff is not in inflated state
         * */
        private void PlotStraightLine()
        {
            if (flatLineSeries != null)
            {
                guichartFemoralCuff.Series.Remove(flatLineSeries);
                femoralCuffSeries = null;
            }

            flatLineSeries.Points.AddXY(xCoordinateFemoralCuff, 600);
            xCoordinateFemoralCuff++;
                       
            if (xCoordinateFemoralCuff > screenwidth)
            {
                flatLineSeries.Points.RemoveAt(0);
            }

            guichartFemoralCuff.Invalidate();
        }

        private void UpdateCountdown(object sender, BizCountdownTimerEventArgs e)
        {
            // int data = e.data / 1000;
            // oLogObject.Write("Countdown timer getting called.");

        // ######################################################################################
        // We are not clear with the functionality of this event, hence we are subscribing to Dal's event.
        // ######################################################################################
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
                if (e.data.ToLower().Equals("inflated"))
                {
                    guiradprgbarTimeToInflatioDeflation.Visible = true;
                    objDefaultWindow.radlblMessage.Text = string.Empty;
                    radlblTimeStatus.Visible = true;

                    objDefaultWindow.radlblMessage.Text = oMsgMgr.GetMessage("GUI_CAPTURE_CUFF_INFLATED");
                    cuffstatechange_flag = true;
                    femoralPlotSwitch = true;
                    objDefaultWindow.radlblCaptureTime.Visible = true;
                }
                else
                {
                    objDefaultWindow.radlblMessage.Text = string.Empty;
                    femoralPlotSwitch = false;
                    cuffstatechange_flag = false;
                    guiradprgbarTimeToInflatioDeflation.Value1 = 0;
                    guiradprgbarTimeToInflatioDeflation.Update();

                    // make progress bar, time to deflation invisible & show cross
                    radlblTimeStatus.Visible = false;
                    objDefaultWindow.radlblMessage.Text = oMsgMgr.GetMessage("GUI_CAPTURE_DEFLATED_MSG");

                    // make progress bar invisible & show cross image
                    guiradprgbarTimeToInflatioDeflation.Visible = false;

                    radlblcuffQuality.Image = new Bitmap(Path.GetFullPath(ConfigurationManager.AppSettings["QualityCrossImage"].ToString()));
                    pictureBox1.Image = Image.FromFile(Path.GetFullPath(ConfigurationManager.AppSettings["QualityCrossImage"].ToString()));
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
                radlblcuffQuality.Visible = true;
                femoralFlag = e.enableOkayButton;

                RefreshOkButton();

                if (e.signalStrengthIsGood)
                {
                    // show tick image
                    radlblcuffQuality.Image = new Bitmap(Path.GetFullPath(ConfigurationManager.AppSettings["QualityIndicatorImage"].ToString()));
                    pictureBox1.Image = Image.FromFile(Path.GetFullPath(ConfigurationManager.AppSettings["QualityIndicatorImage"].ToString()));
                }

                if (!e.signalStrengthIsGood)
                {
                    // show cross image
                    radlblcuffQuality.Image = new Bitmap(Path.GetFullPath(ConfigurationManager.AppSettings["QualityCrossImage"].ToString()));
                    pictureBox1.Image = Image.FromFile(Path.GetFullPath(ConfigurationManager.AppSettings["QualityCrossImage"].ToString()));
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
                chartTonometer.ChartAreas[0].AxisY.Minimum = e.signalMinimum * ChartAreaMinimumY;
                chartTonometer.ChartAreas[0].AxisY.Maximum = e.signalMaximum * ChartAreaMaximumY;
                oLogObject.Write(e.signalMaximum.ToString());
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
                    prim1.BackColor = Color.FromArgb(252, 115, 115);
                    prim1.BackColor2 = Color.FromArgb(253, 33, 33);
                    prim1.BackColor3 = Color.FromArgb(253, 33, 33);
                    prim1.BackColor4 = Color.FromArgb(252, 115, 115);
                }

                if (e.signalStrengthColor.Equals(Color.Yellow))
                {
                    prim1.BackColor = Color.FromArgb(255, 255, 138);
                    prim1.BackColor2 = Color.FromArgb(240, 210, 0);
                    prim1.BackColor3 = Color.FromArgb(240, 210, 0);
                    prim1.BackColor4 = Color.FromArgb(255, 255, 138);
                }

                if (e.signalStrengthColor.Equals(Color.Green))
                {
                    prim1.BackColor = Color.FromArgb(153, 238, 167);
                    prim1.BackColor2 = Color.FromArgb(148, 236, 165);
                    prim1.BackColor3 = Color.Green;
                    prim1.BackColor4 = Color.FromArgb(4, 208, 36);
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
            try
            {               
                uint seconds = 0;
                uint minutes = 0;
                int startIndex = -1;
                int returnedValues = -1;
                DalPwvDataStruct structData;
                DalDataBuffer dbuff = DalDataBuffer.Instance;
                int countdowntimerInMilliseconds = 0; 

                returnedValues = dbuff.GetNextValues(32, ref startIndex);

                for (int i = 0; i < returnedValues; i++)
                {
                    structData = dbuff.GetValueAt(startIndex, i);
                    
                    // since countdown timer is in seconds now converting it into milliseconds
                    countdowntimerInMilliseconds = (int)structData.countdownTimer * 1000;                   
                    short tonometerData = (short)structData.tonometerData;  
                    PlotTonometerData(tonometerData);

                    if (femoralPlotSwitch)
                    {
                        if (cuffstatechange_flag)
                        {                           
                            CrxLogger.Instance.Write("COUNTDOWN: " + countdowntimerInMilliseconds.ToString());
                            guiradprgbarTimeToInflatioDeflation.Minimum = 0;
                            if (countdowntimerInMilliseconds > 0) 
                            {
                                guiradprgbarTimeToInflatioDeflation.Maximum = countdowntimerInMilliseconds; // - int.Parse(deflationTime.ToString()); // (int)structData.countdownTimer
                            }

                            guiradprgbarTimeToInflatioDeflation.Value1 = 0;
                            cuffstatechange_flag = false;                           
                        }   
                    
                        if ((guiradprgbarTimeToInflatioDeflation.Maximum - countdowntimerInMilliseconds) > 0) 
                        {
                            guiradprgbarTimeToInflatioDeflation.Value1 = guiradprgbarTimeToInflatioDeflation.Maximum - countdowntimerInMilliseconds; // (int)structData.countdownTimer; // -int.Parse(deflationTime.ToString());
                            CrxLogger.Instance.Write("Progress Bar Value = " + guiradprgbarTimeToInflatioDeflation.Value1.ToString());
                        }                            

                        // Get time to display
                        // conver miliseconds to seconds first
                       // seconds = structData.countdownTimer / (uint)1000;
                        seconds = structData.countdownTimer;
                       
                        // now get minutes and seconds 
                        minutes = (seconds >= 60) ? (seconds / 60) : 0;                           
                        seconds = (seconds >= 60) ? (seconds % 60) : seconds;
                        CrxLogger.Instance.Write(oMsgMgr.GetMessage("LBL_TIMESTATUS") + " " + minutes.ToString() + ":" + ((seconds >= 10) ? string.Empty : "0") + seconds.ToString());
                        radlblTimeStatus.Text = oMsgMgr.GetMessage("LBL_TIMESTATUS") + " " + minutes.ToString() + ":" + ((seconds >= 10) ? string.Empty : "0") + seconds.ToString();                           

                        short femoralCuffData = (short)structData.cuffPulseData;
                        PlotFemoralCuffData(femoralCuffData);
                        
                        bizObj.Append((ushort)structData.tonometerData, (ushort)structData.cuffPulseData);                        
                    }
                    else
                    {
                        // plot flat line for femoral when cuff is not inflated as value 0
                        PlotFemoralCuffData(0);
                        bizObj.Append((ushort)structData.tonometerData, 0);                        
                    }
                }
            }             
            catch (Exception ex)
            {
                GUIExceptionHandler.HandleException(ex, this);
                timer1.Enabled = false;
                if (radbtnTick.Enabled)
                {
                    DialogResult ds = RadMessageBox.Show(this, oMsgMgr.GetMessage("GUI_CAPTURE_ERROR"), oMsgMgr.GetMessage("SYSTEM_ERROR"), MessageBoxButtons.AbortRetryIgnore, RadMessageIcon.Error);
                    if (ds == DialogResult.Yes)
                    {
                        // Click Yes to generate report.
                        TickButtonAction();
                    }
                    else if (ds == DialogResult.No)
                    {
                        // Click No to abort report generation and go back to Setup screen.
                        ShowSetupAfterCaptureAbort();
                    }
                    else 
                    {
                        // Click Cancel to restart the Capture process.                        
                        BizSession.Instance().StopCapture();
                        BizFacade.Instance().StopCaptureSimulation();
                        StopTimers();
                        guichartFemoralCuff.Series.Clear();
                        guichartFemoralCuff.Series.Remove(femoralCuffSeries);

                        // Clear and remove the tonometer waveform.
                        chartTonometer.Series.Clear();
                        chartTonometer.Series.Remove(newSeries);
                        this.Invoke(new EventHandler(Capture_Load));
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
                    chartTonometer.ChartAreas[0].AxisY.Maximum = data * ChartAreaMaximumY;
                }

                if (data < chartTonometer.ChartAreas[0].AxisY.Minimum)
                {
                    chartTonometer.ChartAreas[0].AxisY.Minimum = data * ChartAreaMinimumY;
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
                        guichartFemoralCuff.ChartAreas[0].AxisY.Minimum = data * ChartAreaMinimumY;
                    }
                    else
                    {
                        if (data < guichartFemoralCuff.ChartAreas[0].AxisY.Minimum)
                        {
                            guichartFemoralCuff.ChartAreas[0].AxisY.Minimum = data * ChartAreaMinimumY;
                        }
                    }
                }

                // set the maximum y-axis,if the incoming data has a point greater than the existing y-axis value then set the new data point as the y-axix maximum.
                if (data > guichartFemoralCuff.ChartAreas[0].AxisY.Maximum)
                {
                    guichartFemoralCuff.ChartAreas[0].AxisY.Maximum = data * ChartAreaMaximumY;
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

            // BizSession.Instance().measurement.captureTime + HandShakePeriod;
            screenwidth = (obj.PwvSettings.CaptureTime + HandShakePeriod) * SampleRate; 
            
            // screenwidth = (10 + 2)* 256;           

            // Reset number of series in the chart.
            chartTonometer.Series.Clear();

            // set y axis
            chartTonometer.ChartAreas[0].AxisY.Minimum = TonometerHeight;
            chartTonometer.ChartAreas[0].AxisY.Maximum = TonometerHeight;
            signalStrength = 0;

            // set x axis
            chartTonometer.ChartAreas[0].AxisX.Minimum = 0;
            chartTonometer.ChartAreas[0].AxisX.Maximum = screenwidth; 

            // give name (for internal use) to the series used for plotting the points,its chart type and the color of the graph.
            newSeries = new Series("Tonometer");
            newSeries.ChartType = SeriesChartType.FastLine;
            newSeries.Color = Color.White;
            newSeries.XValueType = ChartValueType.Int32;
            newSeries.YValueType = ChartValueType.Int32;

            // Add the series to the chart.
            chartTonometer.Series.Add(newSeries);            
        }

        /** This method is used to set the femoral cuff graphs properties.
        */
        private void SetFemoralCuffWaveformProperties()
        {
            // reset the femoral x coordinate counter
            xCoordinateFemoralCuff = 0;

            // BizSession.Instance().measurement.captureTime + HandShakePeriod;
            screenwidth = (obj.PwvSettings.CaptureTime + HandShakePeriod) * SampleRate; 
            
            // screenwidth = (10 + 2) * 256;

            // Reset number of series in the chart.
            guichartFemoralCuff.Series.Clear();
           
            // set y axis
            guichartFemoralCuff.ChartAreas[0].AxisY.Minimum = TonometerHeight;
            guichartFemoralCuff.ChartAreas[0].AxisY.Maximum = TonometerHeight;
            signalStrength = 0;

            // set x axis
            guichartFemoralCuff.ChartAreas[0].AxisX.Minimum = 0;
            guichartFemoralCuff.ChartAreas[0].AxisX.Maximum = screenwidth;

            // give name (for internal use) to the series used for plotting the points,its chart type and the color of the graph.
            femoralCuffSeries = new Series("Femoral Cuff");
            femoralCuffSeries.ChartType = SeriesChartType.FastLine;
            femoralCuffSeries.Color = Color.Yellow;
            femoralCuffSeries.XValueType = ChartValueType.Int32;
            femoralCuffSeries.YValueType = ChartValueType.Int32;

            // Add the series to the chart.
            guichartFemoralCuff.Series.Add(femoralCuffSeries); 
        }

        /** This method is used to set the femoral cuff graphs properties.
      */
        private void SetFlatLineWaveformProperties()
        {
            // reset the femoral x coordinate counter
            xCoordinateFemoralCuff = 0;

            // BizSession.Instance().measurement.captureTime + HandShakePeriod;
            screenwidth = (obj.PwvSettings.CaptureTime + HandShakePeriod) * SampleRate;

            // screenwidth = (10 + 2) * 256;

            // Reset number of series in the chart.
            guichartFemoralCuff.Series.Clear();

            // set y axis
            guichartFemoralCuff.ChartAreas[0].AxisY.Minimum = TonometerHeight;
            guichartFemoralCuff.ChartAreas[0].AxisY.Maximum = TonometerHeight;
            signalStrength = 0;

            // set x axis
            guichartFemoralCuff.ChartAreas[0].AxisX.Minimum = 0;
            guichartFemoralCuff.ChartAreas[0].AxisX.Maximum = screenwidth;

            // give name (for internal use) to the series used for plotting the points,its chart type and the color of the graph.
            flatLineSeries = new Series("Flat line");
            flatLineSeries.ChartType = SeriesChartType.FastLine;
            flatLineSeries.Color = Color.Yellow;
            flatLineSeries.XValueType = ChartValueType.Int32;
            flatLineSeries.YValueType = ChartValueType.Int32;

            // Add the series to the chart.
            guichartFemoralCuff.Series.Add(flatLineSeries);
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
        }

        /** This event is fired when the user clicks on the cross button.
         */
        private void radbtnCross_Click(object sender, EventArgs e)
        {
            timer1.Enabled = false;

            // if Ok btn is enabled and user clicks on Cancel then ask the user if he wants to generate report or abort.
            if (radbtnTick.Enabled)
            {
                DialogResult ds = RadMessageBox.Show(this, oMsgMgr.GetMessage("CAPTURE_TICK_MSG"), oMsgMgr.GetMessage("INFORMATION"), MessageBoxButtons.YesNo, RadMessageIcon.Info);
                if (ds == DialogResult.Yes)
                {
                    TickButtonAction();
                }
                else
                {
                    // navigate user to Setup screen
                    ShowSetupAfterCaptureAbort();
                }
            }
            else
            {
                CrossButtonAction();
            }
        }

        /**This method enables the tabs and the ribbion and navigates the user to the Reports tab.          
         */
        private void TickButtonAction()
        {
            try
            {
                timer1.Enabled = false;

                // Write generate report code over here.
                objDefaultWindow.radlblMessage.Text = oMsgMgr.GetMessage("GUI_CAPTURE_GENERATING_REPORT");
                CrxStructPWVMeasurementData cdata = new CrxStructPWVMeasurementData();

                if (bizObj.CalculatePWVReport(cdata))
                {                    
                    StopCaptureAndSaveReport(cdata);
                }
                else
                {
                    CreateTextFileOnReportFailed();
                    ShowSetupAfterCaptureAbort();
                }
            }
            catch (Exception ex)
            {
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

            // create stub instance to get file path of the text file saved
            biz_stub.BizStub_BizSession bizstub = new BizStub_BizSession();

            // report calculation failed save captured data in text file
            bizObj.SaveCaptureData(); // this will create text file & will save data captured so far

            // show error message alongwith filename
            RadMessageBox.Show(this, oMsgMgr.GetMessage("REPORT_CAL_FAIL_MSG") + "\r\n\r\n" + oMsgMgr.GetMessage("GUI_WAVEFORM_SAVE_MSG") + "\r\n" + bizstub.GetSavedFileName(), oMsgMgr.GetMessage("EXEC_ERROR"), MessageBoxButtons.OK, RadMessageIcon.Error);

            // log the error
            oLogObject.Write(oMsgMgr.GetMessage("REPORT_CAL_FAIL_MSG") + "\r\n\r\n" + oMsgMgr.GetMessage("GUI_WAVEFORM_SAVE_MSG") + "\r\n" + bizstub.GetSavedFileName());            
        }

        /** This method is called after successful report calculation
         * It stops capture & saves report in database
         * */
        private void StopCaptureAndSaveReport(CrxStructPWVMeasurementData cdata)
        {
            BizSession.Instance().StopCapture();
            BizFacade.Instance().StopCaptureSimulation(); // ################# TO BE REMOVED
            StopTimers();

            CrxConfigManager crxMgrObject = CrxConfigManager.Instance;

            // check db connection
            if (dbMagr.CheckConnection(SettingsProperties.ServerNameString(), crxMgrObject.GeneralSettings.SourceData) == 0)
            {
                // capture with new measurement details.... insert a new record
                // capture will always add a new measurement record in backend even if it is conducted with same measurement data
                objDefaultWindow.radlblMessage.Text = oMsgMgr.GetMessage("GUI_CAPTURE_SAVING_REPORT");
                SaveReportCalculation(cdata);
            }
            else
            {
                DialogResult result = RadMessageBox.Show(this, SettingsProperties.ConnectionErrorString(), oMsgMgr.GetMessage("SYSTEM_ERROR"), MessageBoxButtons.RetryCancel, RadMessageIcon.Error);
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
            int iRow = 0;
            iRow = dbMagr.SavePWVMeasurementDetails(cdata);

            if (iRow > 0)
            {
                // redirect to report screen
                SettingsProperties.SetupToReport = false;
                SettingsProperties.PwvCurrentStudyDatetime = cdata.StudyDateTime.ToString();

                guichartFemoralCuff.Series.Clear();
                guichartFemoralCuff.Series.Remove(femoralCuffSeries);

                // Clear and remove the tonometer waveform.
                chartTonometer.Series.Clear();
                chartTonometer.Series.Remove(newSeries);

                // Disable the tick button on the screen.
                // radbtnTick.Enabled = false;
                SettingsProperties.SetupToReport = false;
                SettingsProperties.CaptureToReport = true;
                objDefaultWindow.radpgTabCollection.SelectedPage = objDefaultWindow.radtabReport;
                objDefaultWindow.radlblMessage.Text = string.Empty;
                objDefaultWindow.radtabReport.Enabled = true;
                if (!objDefaultWindow.radtabReport.Enabled)
                {
                    return;
                }

                // invoke load method of report screen
                 OnReportTabClick.Invoke(this, new EventArgs());                                    

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
                RadMessageBox.Show(this, oMsgMgr.GetMessage("REPORT_SAVE_ERR"), oMsgMgr.GetMessage("SYSTEM_ERROR"), MessageBoxButtons.OK, RadMessageIcon.Error);
            }
        }

        /**This method is called when the user clicks on the Cross button.
        */
        private void CrossButtonAction()
        {
            try
            {
                timer1.Enabled = false;
                DialogResult ds = RadMessageBox.Show(this, oMsgMgr.GetMessage("CAPTURE_FAILED"), oMsgMgr.GetMessage("INFORMATION"), MessageBoxButtons.YesNo, RadMessageIcon.Info);
                if (ds == DialogResult.Yes)
                {
                    ShowSetupAfterCaptureAbort();
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
            BizFacade.Instance().StopCaptureSimulation(); // ################# TO BE REMOVED
            StopTimers();

            // Clear and remove the femoral waveform.
            guichartFemoralCuff.Series.Clear();
            guichartFemoralCuff.Series.Remove(femoralCuffSeries);

            // Clear and remove the tonometer waveform.
            chartTonometer.Series.Clear();
            chartTonometer.Series.Remove(newSeries);

            // Disable the tick button on the screen.
            radbtnTick.Enabled = false;

           // StopTimers();
            objDefaultWindow.radpgTabCollection.SelectedPage = objDefaultWindow.guiradgrpbxPwvDistanceMethod;
            objDefaultWindow.radlblMessage.Text = string.Empty;
            objDefaultWindow.radlblCaptureTime.Text = string.Empty;

            // disable settings, backup, restore & cross button
            objDefaultWindow.guiradmnuitemSettings.Enabled = true;
            objDefaultWindow.guiradmnuScor.Enabled = true;
            objDefaultWindow.guiradgrpbxPwvDistanceMethod.Enabled = true;
            objDefaultWindow.radtabReport.Enabled = true;
            objDefaultWindow.guipictureboxError.Image = null;
           
            // set variable to enforce 30 secs timers on setup 
            SettingsProperties.CaptureToSetup = true;

            // make progress bar & labels invisible
            guiradprgbarTimeToInflatioDeflation.Visible = false;
            radlblTimeStatus.Visible = false;
            guiradprgbarTimeToInflatioDeflation.Value1 = 0;
            guiradprgbarTimeToInflatioDeflation.Maximum = 0;
            radProgressBarQualityIndicator.Value1 = 0;
            pictureBox1.Image = null;
            
            OnAbortInitializeTimer.Invoke(this, new EventArgs()); 
        }

        /** This event is raised on the tick of the tmrInflationTimer.
         * This method shows the time to delfation using a progress bar and a countdown timer.
         * If any exception occurs it will be caught and displayed to the user using a message box.
         *The corresponding exception will also be logged in the log file.
         */
        private void tmrInflationTimer_Tick(object sender, EventArgs e)
        {
            try
            {
                guiradprgbarTimeToInflatioDeflation.Minimum = 0;
                guiradprgbarTimeToInflatioDeflation.Maximum = 180;
                inflationTick++;
                guiradprgbarTimeToInflatioDeflation.Value1 = inflationTick;

                if (inflationTick == 180)
                {
                    inflationTick = 0;
                    tmrInflationTimer.Enabled = false;

                    tmrDeflationTimer.Enabled = true;

                    /*When the countdown timer for 3 mins ends,we need to stop plotting the femoral cuff waveform.
                    Hence setting this flag to false.*/
                    guichartFemoralCuff.Series.Clear();
                    guichartFemoralCuff.Series.Remove(femoralCuffSeries);

                    femoralPlotSwitch = false;
                }

                if (seconds < 1)
                {
                    seconds = 59;
                    if (minutes.Equals(0))
                    {
                        minutes = 2;
                    }
                    else
                    {
                        minutes -= 1;
                    }
                }
                else
                {
                    seconds -= 1;
                }

                radlblTimeStatus.Text = oMsgMgr.GetMessage("LBL_TIMESTATUS") + minutes.ToString() + ":" + ((seconds >= 10) ? string.Empty : "0") + seconds.ToString();
            }
            catch (Exception ex)
            {
                GUIExceptionHandler.HandleException(ex, this);
            }
        }

        /** This event is raised on the tick of the tmrDeflationTimer.
         * This method shows the time to inflation using a progress bar and a countdown timer.
         * If any exception occurs it will be caught and displayed to the user using a message box.
         *The corresponding exception will also be logged in the log file.
         */
        private void tmrDeflationTimer_Tick(object sender, EventArgs e)
        {
            try
            {
                guiradprgbarTimeToInflatioDeflation.Minimum = 0;
                guiradprgbarTimeToInflatioDeflation.Maximum = 30;
                deflationTick++;
                guiradprgbarTimeToInflatioDeflation.Value1 = deflationTick;
                
                if (deflationSeconds < 1)
                {
                    deflationSeconds = 29;
                }
                else
                {
                    deflationSeconds -= 1;
                }

                if (deflationTick == 30)
                {
                    deflationTick = 0;
                    tmrDeflationTimer.Enabled = false;

                    tmrInflationTimer.Enabled = true;
                    
                    /*When the countdown timer's 30 secs timer ends,we need to start plotting the femoral cuff 
                     waveform again,hence setting this flag to true.*/
                    SetFemoralCuffWaveformProperties();

                    femoralPlotSwitch = true;
                }

                radlblTimeStatus.Text = oMsgMgr.GetMessage("CAPTURE_TIME_TO_INFLATION") + deflationMinutes.ToString() + ":" + ((deflationSeconds >= 10) ? string.Empty : "0") + deflationSeconds.ToString();
            }
            catch (Exception ex)
            {
                GUIExceptionHandler.HandleException(ex, this);
            }
        }

        /** This timer event is called on Form load,it will tick for 10 seconds and then clear the tonometer waveform and stop the timer itself.
         */ 
        private void TenSecWaitTmr_Tick(object sender, EventArgs e)
        {
            try
            {
                radbtnTick.Enabled = false;
                chartTonometer.Series.Clear();
                chartTonometer.Series.Remove(newSeries);
                SetTonometerWaveformProperties();

                // start plotting femoral waveform
                SetFemoralCuffWaveformProperties();

                femoralPlotSwitch = true;

                TenSecWaitTmr.Enabled = false;
            }
            catch (Exception ex)
            {
                GUIExceptionHandler.HandleException(ex, this);
            }
        }

        /** This event is fired when the timer is enabled.
        * The tick event of the timer is called every 125 milliseconds.
        */
        private void timer1_Tick(object sender, EventArgs e)
        {            
            ReadValueFromBuffer();
            BizSession.Instance().DispatchCaptureData();           
        }

        private void Capture_KeyDown(object sender, KeyEventArgs e)
        {
            if (e.KeyCode == Keys.Escape)
            {
                if (radbtnTick.Enabled)
                {
                    timer1.Enabled = false;
                    DialogResult ds = RadMessageBox.Show(this, oMsgMgr.GetMessage("CAPTURE_TICK_MSG"), oMsgMgr.GetMessage("INFORMATION"), MessageBoxButtons.YesNo, RadMessageIcon.Info);
                    if (ds == DialogResult.Yes)
                    {
                        TickButtonAction();
                    }
                    else
                    {
                        // navigate user to Setup screen
                        ShowSetupAfterCaptureAbort();
                    }
                }
                else
                {
                    CrossButtonAction();
                }
            }
            else if (e.KeyCode == Keys.Space && radbtnTick.Enabled)
            {
                TickButtonAction();
            }
        }

        /** This method stops all the timers
         * */
        private void StopTimers()
        {
            // Disable all the timers on the capture screen
            timer1.Stop();
            tmrInflationTimer.Stop();
            tmrDeflationTimer.Stop();
            TenSecWaitTmr.Stop();            
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
    }
}
