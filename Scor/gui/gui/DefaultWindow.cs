/*
     Copyright (C) ATCOR MEDICAL PTY LTD, 2010
 
    Filename     :      Default Window
        
    Author       :      Nitesh Chhedda
 
    Description  :      This is the Default Window on Application load.
*/
using AtCor.Scor.CrossCutting;
using AtCor.Scor.CrossCutting.Configuration;
using AtCor.Scor.CrossCutting.Logging;
using AtCor.Scor.CrossCutting.Messaging;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Diagnostics;
using System.Drawing;
using System.Text;
using System.Threading;
using System.Windows.Forms;
using System;
using Telerik.Charting;
using Telerik.WinControls.UI;
using Telerik.WinControls;
using Telerik.WinControls.Primitives;
using AtCor.Scor.BusinessLogic;
using System.Windows.Forms.DataVisualization.Charting;

namespace Gui.Atcor.Scor.Presentation
{
     /**
     * @class Class for Default Window when the application loads.
     * @brief This class will handle displaying of the default window controls.It will also check for multiple instances of the application,exception handling and logging of events.
     */   
    public partial class DefaultWindow : Telerik.WinControls.UI.RadRibbonForm
    {
        #region Set constant values
        //RIBBION BAR
        const int RIBBIONBAR_TEXT = 10002;
        const int MENU_SYSTEM = 10060;
        const int MENU_DATABASE = 10061;
        const int MENU_HELP = 10003;
        const int BTN_SETTINGS = 10004;
        const int BTN_FINDMODULE = 10005;
        const int BTN_PRINTERSETUP = 10006;
        const int BTN_EXIT = 10007;
        const int TAB_SETUP = 10062;
        const int TAB_CAPTURE = 10063;
        const int TAB_REPORT = 10064;

        //CAPTURE TAB
        const int LBL_TONOMETER = 10008;
        const int LBL_FEMORALCUFF = 10009;
        const int LBL_TIMESTATUS = 10010;
        const int LBL_PATIENTNAME = 10011;

        //Used to set message codes.
        //set message codes.All messages will come from messaging meanager and hence from resource file.        
        const int EXITSTR = 10001;
        const int STARTSTR = 10000;
        const int SYSTEM_ERROR = 10015;
        const int APP_NAME = 10012;
        const int APP_MSG = 10013;
        const int CAPTURE_FAILED = 10069;
        const int INFORMATION = 10070;
        const double HandShakePeriod = 2;
        #endregion        

        Series newSeries;        
        double screenwidth;
        double signalStrength;        
        ProgressBarPrimitive prim1;
                
        #region Global declarations
      
        int ticks = 0;
        bool isDirectClose; //Flag set to check if there are multiple instances of the application.         

        //object of Config Manager         
        CrxMessagingManager oMsgMgr = CrxMessagingManager.Instance;

        // sets message on the status bar of the main window.
        public void SetMessage(string message)
        {
            this.radlblMessage.Text = message;
        }

        #endregion
        
        /**Constructor of the form,initializes all the controls.
        *It will call IsProcessOpen method which will check if there is any other instance is running.
        */
        public DefaultWindow()
        {            
            try
            {
                //initialize class level variables                
                isDirectClose = false;

                //Logic to check multiple instances of the application.                 
                if (IsProcessOpen(oMsgMgr.GetMessage(APP_NAME)))
                {
                    isDirectClose = true;
                    DialogResult ds = RadMessageBox.Show(this, oMsgMgr.GetMessage(APP_MSG), oMsgMgr.GetMessage(10014), MessageBoxButtons.OK, RadMessageIcon.Error);
                    this.Close();
                }

                InitializeComponent();
                
                // Set the text for  Capture Tab form controls
                SetTextForRibbionControl();                

                // Set the text for  Capture Tab form controls
                SetTextForCaptureTab();                
            }
            catch (Exception ex)
            {
                RadMessageBox.Show(this, ex.Message, oMsgMgr.GetMessage(SYSTEM_ERROR), MessageBoxButtons.OK, RadMessageIcon.Error);
                CrxLogger oLogObject = CrxLogger.Instance;
                oLogObject.Write(ex.Message);                
            }
        }
        
        private void SetTextForRibbionControl()
        {
            radRibbonBar.Text = oMsgMgr.GetMessage(RIBBIONBAR_TEXT);
            rbnTabSystem.Text = oMsgMgr.GetMessage(MENU_SYSTEM);
            rbnTabDatabase.Text = oMsgMgr.GetMessage(MENU_DATABASE);
            rbnTabHelp.Text = oMsgMgr.GetMessage(MENU_HELP);
            radButtonElementSettings.Text = oMsgMgr.GetMessage(BTN_SETTINGS); 
            radButtonElementFindModule.Text = oMsgMgr.GetMessage(BTN_FINDMODULE);
            radButtonElementPrinterSetup.Text = oMsgMgr.GetMessage(BTN_PRINTERSETUP);
            radButtonElementExit.Text = oMsgMgr.GetMessage(BTN_EXIT);
            radtabSetup.Text = oMsgMgr.GetMessage(TAB_SETUP);
            radtabCapture.Text = oMsgMgr.GetMessage(TAB_CAPTURE);
            radtabReport.Text = oMsgMgr.GetMessage(TAB_REPORT);
        }

        private void SetTextForCaptureTab()
        {
            radlblTonometer.Text = oMsgMgr.GetMessage(LBL_TONOMETER);
            radlblFemoralCuff.Text = oMsgMgr.GetMessage(LBL_FEMORALCUFF);
            radlblTimeStatus.Text = oMsgMgr.GetMessage(LBL_TIMESTATUS);
            radlblPatientName.Text = oMsgMgr.GetMessage(LBL_PATIENTNAME);
            //radlblCaptureTime.Text= oMsgMgr.GetMessage(10002);
        }

        /**This method is invoked on the click of the Exit button under System menu.
         * It will close the main window.
         */
        private void radButtonElementExit_Click(object sender, EventArgs e)
        {  
            //Close the application on click of Exit button under System menu.
            this.Close();
        }

        /**This event is fired when window is closed.
         *It will ask for user confirmation before closing the window.
         */
        private void DefaultWindow_FormClosing(object sender, FormClosingEventArgs e)
        {
            try
            {
                //On form closing a confirmation is asked to the user to Save the unsaved data.             
                if (!isDirectClose)
                {
                    RadMessageBox.SetThemeName(oMsgMgr.GetMessage(10016));
                    DialogResult ds = RadMessageBox.Show(this, oMsgMgr.GetMessage(10017), oMsgMgr.GetMessage(10018), MessageBoxButtons.YesNoCancel, RadMessageIcon.Question);

                    //Keeping Yes and No separate for future use.                     
                    if (ds == DialogResult.Yes)
                    {
                        //Save data then exit.Application exited
                        CrxLogger oLogObject = CrxLogger.Instance;
                        oLogObject.Write(oMsgMgr.GetMessage(EXITSTR));
                    }

                    if (ds == DialogResult.No)
                    {
                        //DO NOT Save data then exit.                         
                        CrxLogger oLogObject = CrxLogger.Instance;
                        oLogObject.Write(oMsgMgr.GetMessage(EXITSTR));
                    }

                    if (ds == DialogResult.Cancel)
                    {
                        //Cancel the close event.                         
                        e.Cancel = true;
                    }
                }
            }
            catch (Exception ex)
            {
                RadMessageBox.Show(this, ex.Message, oMsgMgr.GetMessage(SYSTEM_ERROR), MessageBoxButtons.OK, RadMessageIcon.Error);
                CrxLogger oLogObject = CrxLogger.Instance;
                oLogObject.Write(ex.Message);               
            }
        }
        
        /**This is onvoked on the load of the window.
         *Once the application is launched it will log the event into the log file.
         */
        private void DefaultWindow_Load(object sender, EventArgs e)
        {
            try
            {                
                radpgTabCollection.SelectedPage = radtabSetup;

                //check if we can access the configuration file by reading general setting from config manager object.   
                CrxConfigManager oConfigMgr = CrxConfigManager.Instance;
                oConfigMgr.GetGeneralUserSettings();              

                //On windows load set the windows size to maximum.                 
                WindowState = FormWindowState.Maximized;

                //Log the event on successful load of the application.                 
                CrxLogger oLogObject = CrxLogger.Instance;
                oLogObject.Write(oMsgMgr.GetMessage(STARTSTR));

                // Disable the pateint name and Capture time labels
                radlblCaptureTime.Enabled = false;
                radlblPatientName.Enabled = false;                

                // Code for assigning the handler.

                BizEventContainer.Instance.OnBizTonometerDataEvent += new BizTonometerDataEventHandler(UpdateTonoData);

                BizEventContainer.Instance.OnBizCarotidQualityEvent += new BizCarotidQualityEventHandler(qualityIndicator_CarotidQualityEvent);                

                // Quality indicator ProgressBarSetup
                prim1 = (ProgressBarPrimitive)this.radProgressBarQualityIndicator.ProgressBarElement.Children[1];
                radProgressBarQualityIndicator.Minimum = 0;
                radProgressBarQualityIndicator.Maximum = 500;
                prim1.BackColor = prim1.BackColor2 = prim1.BackColor3 = prim1.BackColor4 = Color.Red;
                radbtnTick.Enabled = false;
            }
            catch (CrxException cfgExp)
            {
                //Exception if any will be logged and displayed(appropiate message) to the user.                  
                CrxMessagingManager oMsgMgr = CrxMessagingManager.Instance;
                string errorMessage = oMsgMgr.GetMessage(cfgExp.ErrorCode);

                //show error on screen                 
                RadMessageBox.Show(this, errorMessage, oMsgMgr.GetMessage(SYSTEM_ERROR), MessageBoxButtons.OK, RadMessageIcon.Error);

                //write message in log file                
                CrxLogger oLogObject = CrxLogger.Instance;
                oLogObject.Write(errorMessage);

                //close the application.
                //do not ask question to save data.                 
                isDirectClose = true;
                this.Close();
            }
            catch (Exception ex)
            {
                RadMessageBox.Show(this, ex.Message, oMsgMgr.GetMessage(SYSTEM_ERROR), MessageBoxButtons.OK, RadMessageIcon.Error);
                CrxLogger oLogObject = CrxLogger.Instance;
                oLogObject.Write(ex.Message);
            }
        }

        /**This method is called when the event handler of BizCarotidQualityEvent is executed.
         * Here depending upon the signal strength the progress bar color is displayed and the Tick button is enabled.
        */
        void qualityIndicator_CarotidQualityEvent(object sender, BizCarotidQualityEventArgs e)
        {
            chartTonometer.ChartAreas[0].AxisY.Minimum = e.signalMinimum * 0.96;
            chartTonometer.ChartAreas[0].AxisY.Maximum = e.signalMaximum * 1.04;
            signalStrength = e.signalMaximum - e.signalMinimum;
            if (signalStrength > 500)
            {
                signalStrength = 500;
            }            

            radbtnTick.Enabled = e.enableOkayButton;
            
            prim1.BackColor = prim1.BackColor2 = prim1.BackColor3 = prim1.BackColor4 = e.signalStrengthColor;
            radProgressBarQualityIndicator.Value1 = (int)signalStrength;            
        }

        #region Code to check multiple instance of application.
        private bool IsProcessOpen(string name)
        {
            try
            {
                int count = 0;

                foreach (Process clsProcess in Process.GetProcesses())
                {
                    if (clsProcess.ProcessName.Contains(name))
                    {
                        count++;
                    }
                }

                if (count > 1)
                {
                    return true;
                }

                return false;
            }
            catch (Exception ex)
            {
                RadMessageBox.Show(this, ex.Message, "Scor System Error", MessageBoxButtons.OK, RadMessageIcon.Error);
                CrxLogger oLogObject = CrxLogger.Instance;
                oLogObject.Write(ex.Message);
                return false;
            }
        } 
        #endregion

        /**This method is invoked when Settings button under System tab is clicked.
         */ 
        private void radButtonElementSettings_Click(object sender, EventArgs e)
        {
            try
            {
                //Open the settings dialog box.                 
                frmSettingsWindow settingWinObject = new frmSettingsWindow(this);
                settingWinObject.ShowDialog();
            }
            catch (Exception ex)
            {
                RadMessageBox.Show(this, ex.Message, oMsgMgr.GetMessage(SYSTEM_ERROR), MessageBoxButtons.OK, RadMessageIcon.Error);
                CrxLogger oLogObject = CrxLogger.Instance;
                oLogObject.Write(ex.Message);             
            }
        }

        private void radbtnCross_Click(object sender, EventArgs e)
        {
           // timer1.Enabled = true;           
            CrossButtonAction();
        }

        private void timer1_Tick(object sender, EventArgs e)
        {
            ticks++;
            radProgressBarQualityIndicator.Value1 = ticks;
            radProgressBar.Value1 = ticks;
            if (ticks == 100)
            {
                timer1.Enabled = false;
                ticks = 0;
            }
        }

        /**This method is called when the event handler of BizTonometerDataEventHandler is called is executed.
       * Here the plotting of points for the tonometer is done.
      */
        private void UpdateTonoData(Object sender, BizTonometerDataEventArgs e)
        {
            try
            {
                int data = e.data;
                DateTime timeStamp = DateTime.Now;

                // set the maximum y-axis,if the incoming data has a point greater than the existing y-axis value then set the new data point as the y-axix maximum.
                if (data > chartTonometer.ChartAreas[0].AxisY.Maximum)
                {
                    chartTonometer.ChartAreas[0].AxisY.Maximum = data * 1.04;
                }

                // Add new data point to its series.
                newSeries.Points.AddXY(timeStamp.ToOADate(), data);

                // remove all points from the source series older than 7 seconds.
                double removeBefore = timeStamp.AddSeconds((double)((screenwidth)) * (-1)).ToOADate();   

                //remove oldest values to maintain a constant number of data points
                while (newSeries.Points[0].XValue < removeBefore)
                {
                    newSeries.Points.RemoveAt(0);
                }

                // set the x axis's minimum and maximum values.
                chartTonometer.ChartAreas[0].AxisX.Minimum = newSeries.Points[0].XValue;
                //chartTonometer.ChartAreas[0].AxisX.Maximum = DateTime.FromOADate(newSeries.Points[0].XValue).AddSeconds(7).ToOADate();
                chartTonometer.ChartAreas[0].AxisX.Maximum = DateTime.FromOADate(newSeries.Points[0].XValue).AddSeconds(screenwidth).ToOADate();

                chartTonometer.Invalidate();
            }
            catch (Exception ex)
            {
                RadMessageBox.Show(this, ex.Message, oMsgMgr.GetMessage(SYSTEM_ERROR), MessageBoxButtons.OK, RadMessageIcon.Error);
                CrxLogger oLogObject = CrxLogger.Instance;
                oLogObject.Write(ex.Message);
            }
        }

        /**This method is called when the Setup, Capture or Report tab is selected.
        */ 
        private void radpgTabCollection_Click(object sender, EventArgs e)
        {            
            chartTonometer.Series.Clear();  
            //read the coms port and simulation type from??? 
            if (radpgTabCollection.SelectedPage.Text.Equals(oMsgMgr.GetMessage(TAB_CAPTURE)))
            {                
                SetTonometerWaveformProperties();
                radtabSetup.Enabled = false;
                radtabReport.Enabled = false;
                radRibbonBar.Enabled = false;
                radlblPatientName.Enabled = true;
                radlblPatientName.Text = "Default Patient"; //Hardcoding since this will be removed in coming sprints as the patient name will be coming from the session/patient object.
                radlblCaptureTime.Enabled = true;
                radlblCaptureTime.Text = BizSession.Instance().measurement.captureTime.ToString();
                radlblMessage.Text = "Simulation Mode"; //Hardcoding since this will be removed in coming sprints as it will be coming from the biz.dll                      
                BizSession.Instance().StartCapture();
                timer2.Enabled = true;
            }

            // get data from biz layer
            //BizSession.Instance().StartCapture();
            //timer2.Enabled = true;
        }

        private void SetTonometerWaveformProperties()
        {
            screenwidth = BizSession.Instance().measurement.captureTime + HandShakePeriod;
            
            //replace minValue with VerticalMin and VerticalMax.
            DateTime minValue = DateTime.Now;
            DateTime maxValue = minValue.AddSeconds(screenwidth);

            // Reset number of series in the chart.
            chartTonometer.Series.Clear();

            //set y axis
            chartTonometer.ChartAreas[0].AxisY.Minimum = 0;
            chartTonometer.ChartAreas[0].AxisY.Maximum = 4096;
            signalStrength = 0;

            // set x axis
            chartTonometer.ChartAreas[0].AxisX.Minimum = minValue.ToOADate();
            chartTonometer.ChartAreas[0].AxisX.Maximum = maxValue.ToOADate();

            // give name (for internal use) to the series used for plotting the points,its chart type and the color of the graph.
            newSeries = new Series("Tonometer");
            newSeries.ChartType = SeriesChartType.Spline;
            newSeries.Color = Color.White;

            // Add the series to the chart.
            chartTonometer.Series.Add(newSeries); 
        }

        /**This method is called when the user clicks on the Tick button.
        */ 
        private void radbtnTick_Click(object sender, EventArgs e)
        {
            TickButtonAction();           
        }

        /**This method enables the tabs and the ribbion and navigates the user to the Reports tab.          
        */ 
        private void TickButtonAction()
        {
            radtabSetup.Enabled = true;
            radtabReport.Enabled = true;
            radRibbonBar.Enabled = true;
            radpgTabCollection.SelectedPage = radtabReport;   
        }

        /**This method is called when the user clicks on the Cross button.
        */ 
        private void CrossButtonAction()
        {
            //timer2.Enabled = false; 
            DialogResult ds = RadMessageBox.Show(this, oMsgMgr.GetMessage(CAPTURE_FAILED), oMsgMgr.GetMessage(INFORMATION), MessageBoxButtons.YesNo, RadMessageIcon.Info);
           if (ds == DialogResult.Yes)
           {
               radtabSetup.Enabled = true;
               radtabReport.Enabled = true;
               radRibbonBar.Enabled = true;
               radpgTabCollection.SelectedPage = radtabSetup;
           }            
        }

        /**This method is called when the user clicks Spacebar from the keyboard.
        */
        private void radbtnTick_KeyDown(object sender, KeyEventArgs e)
        {
            if (radbtnTick.Enabled)
            {
                if (e.KeyCode == Keys.Space)
                {
                    TickButtonAction();
                }
            }
        }

        /**This method is called when the user clicks Escape from the keyboard.
        */
        private void radbtnCross_KeyDown(object sender, KeyEventArgs e)
        {
            if (e.KeyCode == Keys.Escape)
            {
                CrossButtonAction();
            }
        }       

        /**This method will invoke the Capture of tonometer data.
        */ 
        private void timer2_Tick(object sender, EventArgs e)
        {
            BizSession.Instance().DispatchCaptureData();
        }

        private void DefaultWindow_KeyDown(object sender, KeyEventArgs e)
        {
            if (radpgTabCollection.SelectedPage.Text.Equals(oMsgMgr.GetMessage(TAB_CAPTURE)))
            {
                if (e.KeyCode == Keys.Escape)
                {
                    CrossButtonAction();
                }

                if (radbtnTick.Enabled)
                {
                    if (e.KeyCode == Keys.Space)
                    {
                        TickButtonAction();
                    }
                }
            }
        }   
    }
}