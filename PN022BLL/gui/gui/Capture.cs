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
        volatile bool femoralPlotSwitch = false;
        #endregion        

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
        DalDataBuffer dalDataBufferObj;
        private DefaultWindow objDefaultWindow;
        BizPWV bizObj = (BizPWV)BizSession.Instance().measurement; 

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
            }
            catch (CrxException cfgExp)
            {
                // Exception if any will be logged and displayed(appropiate message) to the user.                  
                CrxMessagingManager oMsgMgr = CrxMessagingManager.Instance;
                string errorMessage = oMsgMgr.GetMessage(cfgExp.ErrorCode);

                // show error on screen                 
                RadMessageBox.Show(this, oMsgMgr.GetMessage(cfgExp.ErrorString), oMsgMgr.GetMessage("SYSTEM_ERROR"), MessageBoxButtons.OK, RadMessageIcon.Error);

                // write message in log file                
                CrxLogger oLogObject = CrxLogger.Instance;
                oLogObject.Write(errorMessage);               
            }

           // radlblPatientName.Text = oMsgMgr.GetMessage("LBL_PATIENTNAME");
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
                DataAccess.DalEventContainer.Instance.OnDalCuffStatusEvent += new DalCuffStatusEventHandler_ORI(Instance_OnDalCuffStatusEvent);
                ////deepak

                SetTonometerWaveformProperties();

                // SetFemoralCuffWaveformProperties();
                StartCarotidTonometerCapture();
               
                // Quality indicator ProgressBarSetup
                prim1 = (ProgressBarPrimitive)this.radProgressBarQualityIndicator.ProgressBarElement.Children[1];
                radProgressBarQualityIndicator.Minimum = 0;
                radProgressBarQualityIndicator.Maximum = QualityIndicatorHeight;
                prim1.BackColor = prim1.BackColor2 = prim1.BackColor3 = prim1.BackColor4 = Color.Red;
                radbtnTick.Enabled = false;

                // start the 10 Sec timer wait for femoral plotting
                // TenSecWaitTmr.Enabled = true;
                // disable settings, backup, restore & cross button
                objDefaultWindow.guiradmnuitemSettings.Enabled = false;
                
                // objDefaultWindow.guiradmenuBackup.Enabled = false;
                // objDefaultWindow.guiradmenuRestore.Enabled = false;
                objDefaultWindow.guiradmnuScor.Enabled = false;

                // disable seup & report tabs
                objDefaultWindow.radtabReport.Enabled = false;
                objDefaultWindow.guiradgrpbxPwvDistanceMethod.Enabled = false;
                
                // throw new DalException("For test purpose");
                CrxLogger.Instance.Write("Capture Form Loading DONE");

                DisplayCaptureTime();
            }
            catch (CrxException cfgExp)
            {
                // Exception if any will be logged and displayed(appropiate message) to the user.                  
                CrxMessagingManager oMsgMgr = CrxMessagingManager.Instance;
                string errorMessage = oMsgMgr.GetMessage(cfgExp.ErrorCode);

                // show error on screen                 
                RadMessageBox.Show(this, oMsgMgr.GetMessage(cfgExp.ErrorString), oMsgMgr.GetMessage("SYSTEM_ERROR"), MessageBoxButtons.OK, RadMessageIcon.Error);

                // write message in log file                
                CrxLogger oLogObject = CrxLogger.Instance;
                oLogObject.Write(errorMessage);

                StopTimers();
            }
            catch (DalException ex)
            {
                RadMessageBox.Show(this, oMsgMgr.GetMessage(ex.ErrorString), oMsgMgr.GetMessage("SYSTEM_ERROR"), MessageBoxButtons.OK, RadMessageIcon.Error);
                CrxLogger oLogObject = CrxLogger.Instance;
                oLogObject.Write(ex.Message);
            }
            catch (Exception ex)
            {
                RadMessageBox.Show(this, ex.Message, oMsgMgr.GetMessage("SYSTEM_ERROR"), MessageBoxButtons.OK, RadMessageIcon.Error);
                CrxLogger oLogObject = CrxLogger.Instance;
                oLogObject.Write(ex.Message);
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
                    objDefaultWindow.radlblMessage.Text = oMsgMgr.GetMessage("GRP_CAPTURE_TIME") + ": " + oMsgMgr.GetMessage("RAD_5_SEC");
                    break;
                case 10:
                    objDefaultWindow.radlblMessage.Text = oMsgMgr.GetMessage("GRP_CAPTURE_TIME") + ": " + oMsgMgr.GetMessage("RAD_10_SEC");
                    break;
                case 20:
                    objDefaultWindow.radlblMessage.Text = oMsgMgr.GetMessage("GRP_CAPTURE_TIME") + ": " + oMsgMgr.GetMessage("RAD_20_SEC");
                    break;            
            }           
        }

        private void Instance_OnDalCuffStatusEvent(object sender, DalCuffStatusEventArgs_ORI args)
        {
            try
            {
                if (args.CuffStateFlag.Equals(DalCuffStateFlags.CUFF_STATE_INFLATED))
                {
                    CrxLogger.Instance.Write("Inflated Cuff");
                    
                    // guichartFemoralCuff.Series.Remove(flatLineSeries);
                    ResumeFemoralChartSeries(sender, args);

                    guiradprgbarTimeToInflatioDeflation.Minimum = 0;
                    guiradprgbarTimeToInflatioDeflation.Maximum = args.countDownTimerValue;
                    CrxLogger.Instance.Write("Inflated Cuff - args.countDownTimerValue = " + args.countDownTimerValue.ToString());
                    guiradprgbarTimeToInflatioDeflation.Value1 = 0;

                    // oLogObject.Write("After Setting the progressbar");
                    // Start plotting the values returned from the DAL.
                    // tempStr = args.CuffStateFlag.ToString("G");
                    femoralPlotSwitch = true;

                    // oLogObject.Write("After setting the flag");
                }
                else
                {
                    // PlotStraightLine();
                    femoralPlotSwitch = false;
                    ClearFemoralChartSeries(sender, args);
                    
                    CrxLogger.Instance.Write("OTHER THAN - Inflated Cuff");

                    guiradprgbarTimeToInflatioDeflation.Minimum = 0;
                    guiradprgbarTimeToInflatioDeflation.Maximum = args.countDownTimerValue;
                    CrxLogger.Instance.Write("OTHER THAN - Inflated Cuff - args.countDownTimerValue = " + args.countDownTimerValue.ToString());
                    guiradprgbarTimeToInflatioDeflation.Value1 = 0;                    
                }
            }
            catch (DalException ex)
            {
                RadMessageBox.Show(this, oMsgMgr.GetMessage(ex.ErrorString), oMsgMgr.GetMessage("SYSTEM_ERROR"), MessageBoxButtons.OK, RadMessageIcon.Error);
                CrxLogger oLogObject = CrxLogger.Instance;
                oLogObject.Write(ex.Message);
            }
        }

        private void ResumeFemoralChartSeries(object sender, EventArgs e)
        {
            if (InvokeRequired)
            {
                this.Invoke(new EventHandler(ResumeFemoralChartSeries));
                return;
            }

            radlblTimeStatus.Visible = true;
            SetFemoralCuffWaveformProperties();
        }

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
        }

        private void PlotStraightLine()
        {
            if (flatLineSeries != null)
            {
                guichartFemoralCuff.Series.Remove(flatLineSeries);
                flatLineSeries = null;
            }

            // Plot a straight line on the femoral chart.
            flatLineSeries = new Series("FlatLineSeries");
            flatLineSeries.ChartType = SeriesChartType.Line;
            flatLineSeries.Color = Color.Yellow;
            flatLineSeries.XValueType = ChartValueType.Int32;
            flatLineSeries.YValueType = ChartValueType.Int32;

            flatLineSeries.Points.AddY(100);

            // Add the series to the chart.
            guichartFemoralCuff.Series.Add(flatLineSeries);

            // Disable the progressbar(guiradprgbarTimeToInflatioDeflation) and the countdown timer label(radlblTimeStatus).            
        }

        private void UpdateCountdown(object sender, BizCountdownTimerEventArgs e)
        {
            // int data = e.data / 1000;
            // oLogObject.Write("Countdown timer getting called.");

        // ######################################################################################
        // We are not clear with the functionality of this event, hence we are subscribing to Dal's event.
        // ######################################################################################
        }

        private void UpdateCuffState(object sender, BizCuffStateEventArgs e)
        {           
            // ######################################################################################
            // We need cusff status along with count down timer value in the event arguments
            // so that progress bar and label can be set properly.
            // ######################################################################################

            // string state = e.data;
            // oLogObject.Write(state); // Inflated

            // if (e.data.Equals("Inflated"))
            // {    
            //   oLogObject.Write("Before Setting the progressbar");
            //   //guichartFemoralCuff.Series.Remove(flatLineSeries);

            // //guiradprgbarTimeToInflatioDeflation.Minimum = 0;
            // //guiradprgbarTimeToInflatioDeflation.Maximum = args.countDownTimerValue;
            // guiradprgbarTimeToInflatioDeflation.Value1 = Int32.Parse(e.data);

            // oLogObject.Write("After Setting the progressbar");
            // // Start plotting the values returned from the DAL.
            // //tempStr = args.CuffStateFlag.ToString("G");
                
            // femoralPlotSwitch = true;
            // oLogObject.Write("After setting the flag");
           
            // }
            // else
            // {
            //    PlotStraightLine();
            // }           
        }

        private void qualityIndicator_FemoraCuffEvent(object sender, BizFemoralQualityEventArgs e)
        {
            try
            {
                radlblcuffQuality.Visible = true;
                if (!radbtnTick.Enabled)
                {
                    radbtnTick.Enabled = e.enableOkayButton;
                }

                if (e.signalStrengthIsGood)
                {
                    // show tick image
                    radlblcuffQuality.Image = new Bitmap(Path.GetFullPath(ConfigurationManager.AppSettings["QualityIndicatorImage"].ToString()));
                }

                if (!e.signalStrengthIsGood)
                {
                    // show cross image
                    radlblcuffQuality.Image = new Bitmap(Path.GetFullPath(ConfigurationManager.AppSettings["QualityCrossImage"].ToString()));
                }
            }
            catch (Exception ex)
            {
                RadMessageBox.Show(this, ex.Message, oMsgMgr.GetMessage("SYSTEM_ERROR"), MessageBoxButtons.OK, RadMessageIcon.Error);
                CrxLogger oLogObject = CrxLogger.Instance;
                oLogObject.Write(ex.Message);
            }
        }

        /**This method is called when the event handler of BizCarotidQualityEvent is executed.
         * Here depending upon the signal strength the progress bar color is displayed and the Tick button is enabled.
        */
        private void qualityIndicator_CarotidQualityEvent(object sender, BizCarotidQualityEventArgs e)
        {
            try
            {
                oLogObject.Write("Method getting called.");
                chartTonometer.ChartAreas[0].AxisY.Minimum = e.signalMinimum * ChartAreaMinimumY;
                chartTonometer.ChartAreas[0].AxisY.Maximum = e.signalMaximum * ChartAreaMaximumY;

                signalStrength = e.signalMaximum - e.signalMinimum;
                if (signalStrength > QualityIndicatorHeight)
                {
                    signalStrength = QualityIndicatorHeight;
                }

                if (!radbtnTick.Enabled)
                {
                    radbtnTick.Enabled = e.enableOkayButton;
                }
                
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
                RadMessageBox.Show(this, ex.Message, oMsgMgr.GetMessage("SYSTEM_ERROR"), MessageBoxButtons.OK, RadMessageIcon.Error);
                CrxLogger oLogObject = CrxLogger.Instance;
                oLogObject.Write(ex.Message);
            }
        }
        
        /** This method is used to start the capture for tonometer waveform.
       */
        private void StartCarotidTonometerCapture()
        {
            try
            {
                DalModule dalModuleObj = DalModule.Instance;

                // ########################################################################
                // ------------TO DO ----------- 
                // To be removed once BLL starts calling set device strategy, and GUI default window load
                // should call this method to set device strategy based on the saved config settings
                // dalModuleObj.SetDeviceStrategy("Simulation");
                // ########################################################################
                dalModuleObj.StartCapture(obj.PwvSettings.CaptureTime, SampleRate);
                
                dalDataBufferObj = DalDataBuffer.Instance;
                timer1.Enabled = true;
            }
            catch (DalException ex)
            {
                RadMessageBox.Show(this, oMsgMgr.GetMessage(ex.ErrorString), oMsgMgr.GetMessage("SYSTEM_ERROR"), MessageBoxButtons.OK, RadMessageIcon.Error);
                CrxLogger oLogObject = CrxLogger.Instance;
                oLogObject.Write(ex.Message);
            }
            catch (Exception ex)
            {
                RadMessageBox.Show(this, ex.Message, oMsgMgr.GetMessage("SYSTEM_ERROR"), MessageBoxButtons.OK, RadMessageIcon.Error);
                CrxLogger oLogObject = CrxLogger.Instance;
                oLogObject.Write(ex.Message);
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

                returnedValues = dbuff.GetNextValues(32, ref startIndex);

                for (int i = 0; i < returnedValues; i++)
                {
                    structData = dbuff.GetValueAt(startIndex, i);

                    short tonometerData = (short)structData.tonometerData;

                    PlotTonometerData(tonometerData);

                    if (femoralPlotSwitch)
                    {
                        // increment progress bar
                        if (structData.countdownTimer % 256 == 0)
                        {
                            guiradprgbarTimeToInflatioDeflation.Value1 = guiradprgbarTimeToInflatioDeflation.Maximum - (int)structData.countdownTimer;
                            CrxLogger.Instance.Write("Progress Bar Value = " + guiradprgbarTimeToInflatioDeflation.Value1.ToString());

                            // Get time to display
                            // conver miliseconds to seconds first
                            seconds = structData.countdownTimer / (uint)1000;

                            // now get minutes and seconds 
                            minutes = (seconds >= 60) ? (seconds / 60) : 0;
                            seconds = (seconds >= 60) ? (seconds % 60) : seconds;

                            radlblTimeStatus.Text = oMsgMgr.GetMessage("LBL_TIMESTATUS") + " " + minutes.ToString() + ":" + ((seconds >= 10) ? string.Empty : "0") + seconds.ToString();
                        }

                        short femoralCuffData = (short)structData.cuffPulseData;
                        PlotFemoralCuffData(femoralCuffData);
                    }
                }
            }
            catch (DalException ex)
            {
                RadMessageBox.Show(this, oMsgMgr.GetMessage(ex.ErrorString), oMsgMgr.GetMessage("SYSTEM_ERROR"), MessageBoxButtons.OK, RadMessageIcon.Error);
                CrxLogger oLogObject = CrxLogger.Instance;
                oLogObject.Write(ex.Message);
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
                    radbtnTick.Enabled = true; 
                }
                
                // set the x axis's minimum and maximum values.
                chartTonometer.ChartAreas[0].AxisX.Minimum = newSeries.Points[0].XValue;
                chartTonometer.ChartAreas[0].AxisX.Maximum = newSeries.Points[0].XValue + screenwidth;
                chartTonometer.Invalidate();            
            }
            catch (Exception ex)
            {
                RadMessageBox.Show(this, ex.Message, oMsgMgr.GetMessage("SYSTEM_ERROR"), MessageBoxButtons.OK, RadMessageIcon.Error);               
                oLogObject.Write(ex.Message);
            }
        }

        /**This method is called to plot femoral cuff data.         
         */ 
        private void PlotFemoralCuffData(short femoralCuffData)
        {
            try
            {
                if (femoralPlotSwitch == false)
                {
                    return;
                }

                int data = femoralCuffData;

                // set the maximum y-axis,if the incoming data has a point greater than the existing y-axis value then set the new data point as the y-axix maximum.
                if (data > guichartFemoralCuff.ChartAreas[0].AxisY.Maximum)
                {
                    guichartFemoralCuff.ChartAreas[0].AxisY.Maximum = data * ChartAreaMaximumY;
                }

                if (data < guichartFemoralCuff.ChartAreas[0].AxisY.Minimum)
                {
                    guichartFemoralCuff.ChartAreas[0].AxisY.Minimum = data * ChartAreaMinimumY;
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
                RadMessageBox.Show(this, ex.Message, oMsgMgr.GetMessage("SYSTEM_ERROR"), MessageBoxButtons.OK, RadMessageIcon.Error);
                oLogObject.Write(ex.Message);
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

        /**This method is called when the user clicks on the Tick button.
       */
        private void radbtnTick_Click(object sender, EventArgs e)
        {
            TickButtonAction();
        }

        /** This event is fired when the user clicks on the cross button.
         */
        private void radbtnCross_Click(object sender, EventArgs e)
        {
            CrossButtonAction();
        }        

        /**This method enables the tabs and the ribbion and navigates the user to the Reports tab.          
        */
        private void TickButtonAction()
        {
          // Write generate report code over here.
           
            // if (!objDefaultWindow.radtabReport.Enabled)
            // {
            //    return;
            // }

            //// open report form under report tab
            // if (SettingsProperties.reportChildForm != null)
            // {
            //    SettingsProperties.reportChildForm.Close();
            // }
            
            // SettingsProperties.reportChildForm = new Report();
            // SettingsProperties.reportChildForm.TopLevel = false;
            // SettingsProperties.reportChildForm.Dock = DockStyle.Fill;
            // SettingsProperties.reportChildForm.FormBorderStyle = System.Windows.Forms.FormBorderStyle.None;

            //// adds report form under parent window control
            // var page = objDefaultWindow.radpgTabCollection.Pages[2];
            // SettingsProperties.reportChildForm.Parent = page;
            // page.Controls.Add(SettingsProperties.reportChildForm);
            // SettingsProperties.reportChildForm.Show();
            
            //// disable setting tab on menu bar
            // objDefaultWindow.guiradmnuitemSettings.Enabled = false;

            // Thread generateReport = new Thread(GeneratePwvReport);
            // generateReport.Start();

            // Calculate PWV report ,if it returns true then go to report else show message and go to Setup.
            // vibhuti: CalculatePWVReport called when tick is enabled
            CrxStructPWVMeasurementData crxpwv = new CrxStructPWVMeasurementData(); // vibhuti

            // if CalculatePWVReport returns true navigate to report screen else go back to setup
            // if (bizObj.CalculatePWVReport(crxpwv)) // VA:TM can't call it yet. BLL needs to change to use signal buffers in DAL
            // { //VA:See above
            guichartFemoralCuff.Series.Clear();
            guichartFemoralCuff.Series.Remove(femoralCuffSeries);

            // Clear and remove the tonometer waveform.
            chartTonometer.Series.Clear();
            chartTonometer.Series.Remove(newSeries);

            // Disable the tick button on the screen.
            radbtnTick.Enabled = false;

            StopTimers();

            objDefaultWindow.radpgTabCollection.SelectedPage = objDefaultWindow.radtabReport;
            objDefaultWindow.radlblMessage.Text = string.Empty;
            objDefaultWindow.radtabReport.Enabled = true;
            if (!objDefaultWindow.radtabReport.Enabled)
            {
                return;
            }

            // open report form under report tab
            if (SettingsProperties.reportChildForm != null)
            {
                SettingsProperties.reportChildForm.Close();
            }

            SettingsProperties.reportChildForm = new Report();
            SettingsProperties.reportChildForm.TopLevel = false;
            SettingsProperties.reportChildForm.Dock = DockStyle.Fill;
            SettingsProperties.reportChildForm.FormBorderStyle = System.Windows.Forms.FormBorderStyle.None;

            // adds report form under parent window control
            var page = objDefaultWindow.radpgTabCollection.Pages[2];
            SettingsProperties.reportChildForm.Parent = page;
            page.Controls.Add(SettingsProperties.reportChildForm);
            SettingsProperties.reportChildForm.Show();

            // disable setting tab on menu bar
            objDefaultWindow.guiradmnuitemSettings.Enabled = false;

            // disable settings, backup, restore & cross button
            objDefaultWindow.guiradmnuitemSettings.Enabled = false;
            objDefaultWindow.guiradmnuScor.Enabled = true;
            objDefaultWindow.guiradgrpbxPwvDistanceMethod.Enabled = true;
            objDefaultWindow.radtabCapture.Enabled = false;

            BizSession.Instance().StopCapture();
            BizFacade.Instance().StopCaptureSimulation(); // ################# TO BE REMOVED
            StopTimers();
            // } // VA:See a comment above by VA; TM also needs to handle if CalculatePWVReport failed.
        }

        private void GeneratePwvReport()
        {
            // Calculate PWV report ,if it returns true then go to report else show message and go to Setup.
            CrxStructPWVMeasurementData measurementObj = new CrxStructPWVMeasurementData();
            BizPatient patientObject = BizPatient.Instance();

            if (bizObj.CalculatePWVReport(measurementObj))
            {
                Thread generateReport = new Thread(GeneratePwvReport);
                
                // Clear and remove the femoral waveform.
                guichartFemoralCuff.Series.Clear();
                guichartFemoralCuff.Series.Remove(femoralCuffSeries);

                // Clear and remove the tonometer waveform.
                chartTonometer.Series.Clear();
                chartTonometer.Series.Remove(newSeries);

                // Disable the tick button on the screen.
                radbtnTick.Enabled = false;

                StopTimers();

                objDefaultWindow.radpgTabCollection.SelectedPage = objDefaultWindow.radtabReport;
                objDefaultWindow.radlblMessage.Text = string.Empty;
            }
            else
            {
                // Show message box displaying,error while generating report.
                RadMessageBox.Show(this, oMsgMgr.GetMessage("REPORT_GENERATION_ERROR"), oMsgMgr.GetMessage("SYSTEM_ERROR"), MessageBoxButtons.OK, RadMessageIcon.Error);

                // navigate the user to Setup screen.
                objDefaultWindow.radpgTabCollection.SelectedPage = objDefaultWindow.guiradgrpbxPwvDistanceMethod;
                objDefaultWindow.radlblMessage.Text = string.Empty;
            }
        }

        /**This method is called when the user clicks on the Cross button.
        */
        private void CrossButtonAction()
        {
            try
            {
                DialogResult ds = RadMessageBox.Show(this, oMsgMgr.GetMessage("CAPTURE_FAILED"), oMsgMgr.GetMessage("INFORMATION"), MessageBoxButtons.YesNo, RadMessageIcon.Info);
                if (ds == DialogResult.Yes)
                {
                    // Clear and remove the femoral waveform.
                    guichartFemoralCuff.Series.Clear();
                    guichartFemoralCuff.Series.Remove(femoralCuffSeries);

                    // Clear and remove the tonometer waveform.
                    chartTonometer.Series.Clear();
                    chartTonometer.Series.Remove(newSeries);

                    // Disable the tick button on the screen.
                    radbtnTick.Enabled = false;
                    StopTimers();

                    objDefaultWindow.radpgTabCollection.SelectedPage = objDefaultWindow.guiradgrpbxPwvDistanceMethod;
                    objDefaultWindow.radlblMessage.Text = string.Empty;

                    // disable settings, backup, restore & cross button
                    objDefaultWindow.guiradmnuitemSettings.Enabled = true;
                    objDefaultWindow.guiradmnuScor.Enabled = true;
                    objDefaultWindow.guiradgrpbxPwvDistanceMethod.Enabled = true;
                    objDefaultWindow.radtabReport.Enabled = true;

                    BizSession.Instance().StopCapture();
                    BizFacade.Instance().StopCaptureSimulation(); // ################# TO BE REMOVED
                    StopTimers();
                }
            }
            catch (Exception ex)
            {
                RadMessageBox.Show(this, ex.Message, oMsgMgr.GetMessage("SYSTEM_ERROR"), MessageBoxButtons.OK, RadMessageIcon.Error);
                CrxLogger oLogObject = CrxLogger.Instance;
                oLogObject.Write(ex.Message);
            }
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
                RadMessageBox.Show(this, ex.Message, oMsgMgr.GetMessage("SYSTEM_ERROR"), MessageBoxButtons.OK, RadMessageIcon.Error);
                CrxLogger oLogObject = CrxLogger.Instance;
                oLogObject.Write(ex.Message);
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
                RadMessageBox.Show(this, ex.Message, oMsgMgr.GetMessage("SYSTEM_ERROR"), MessageBoxButtons.OK, RadMessageIcon.Error);
                CrxLogger oLogObject = CrxLogger.Instance;
                oLogObject.Write(ex.Message);
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
                RadMessageBox.Show(this, ex.Message, oMsgMgr.GetMessage("SYSTEM_ERROR"), MessageBoxButtons.OK, RadMessageIcon.Error);
                CrxLogger oLogObject = CrxLogger.Instance;
                oLogObject.Write(ex.Message);
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
                CrossButtonAction();
            }
            else if (e.KeyCode == Keys.Space && radbtnTick.Enabled)
            {
                TickButtonAction(); 
            }
        }

        private void StopTimers()
        {
            // Disable all the timers on the capture screen
            timer1.Stop();
            tmrInflationTimer.Stop();
            tmrDeflationTimer.Stop();
            TenSecWaitTmr.Stop();            
        }

        private void Capture_FormClosing(object sender, FormClosingEventArgs e)
        {
        }

        private void Capture_FormClosed(object sender, FormClosedEventArgs e)
        {
            // Clear the charts.
            ////guichartFemoralCuff.Series.Clear();
            ////guichartFemoralCuff.Series.Remove(femoralCuffSeries);

            //// Clear and remove the tonometer waveform.
            ////chartTonometer.Series.Clear();
            ////chartTonometer.Series.Remove(newSeries);

            ////reset horizontal progress bar
            ////guiradprgbarTimeToInflatioDeflation.Minimum = 0;
            ////guiradprgbarTimeToInflatioDeflation.Maximum = 10;
            ////guiradprgbarTimeToInflatioDeflation.Value1 = 0;

            ////reset vertical progress bar
            ////radProgressBarQualityIndicator.Minimum = 0;
            ////radProgressBarQualityIndicator.Maximum = 10;
            ////radProgressBarQualityIndicator.Value1 = 0;

            ////reset femoral quality indicator
            ////radlblcuffQuality.Image.Dispose();
        }        
    }
}
