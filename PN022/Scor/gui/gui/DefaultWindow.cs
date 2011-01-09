/*
     Copyright (C) ATCOR MEDICAL PTY LTD, 2010
 
    Filename     :      Default Window
        
    Author       :      Nitesh Chhedda
 
    Description  :      This is the Default Window on Application load.
*/
using AtCor.Scor.CrossCutting;
using AtCor.Scor.CrossCutting.Configuration;  
using AtCor.Scor.CrossCutting.Logging;
using AtCor.Scor.CrossCutting.DatabaseManager;  
using AtCor.Scor.CrossCutting.Messaging; 
using System.Collections.Generic;
using System.ComponentModel;
using System.Configuration;
using System.Data;
using System.Data.SqlClient;
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
using Telerik.WinControls.Enumerations;
using Telerik.WinControls.UI.Docking;
using Telerik.WinControls.Themes.Design;
using AtCor.Scor.BusinessLogic;
using System.Windows.Forms.DataVisualization.Charting;
using System.Globalization;
using Microsoft.Win32;
using System.IO;

/**
 * @namespace AtCor.Scor.Gui.Presentation
 * @brief This namespace implements Presentation related classes.
 * 
 */
namespace AtCor.Scor.Gui.Presentation
{
     /**
    * @class DefaultWindow 
    * @brief Class for Default Window when the application loads. This class will handle displaying of the default window controls.It will also check for multiple instances of the application,exception handling and logging of events.
     */   
    public partial class DefaultWindow : Telerik.WinControls.UI.RadForm
    {
        #region Set constant values
    
        const double HandShakePeriod = 2;
        const int TonometerHeight = 4096;
        const int QualityIndicatorHeight = 500;
        const double ChartAreaMinimumY = 0.96;
        const double ChartAreaMaximumY = 1.04;
        #endregion        
        
        static int count = 0;
        static int countOne = 0;
        int bobj = 31256;               
        BizPWV obj;
        CrxConfigManager crxMgrObject = CrxConfigManager.Instance;
        Series newSeries;        
        double screenwidth;
        double signalStrength;        
        ProgressBarPrimitive prim1;
        CrxDBManager dbMagr; 
        #region Global declarations

        enum currentMode 
        {
            None,
            InsertMode,
            EditMode, 
            SearchMode
        }

        string mode = "0"; // 1 denotes insert & 2 denotes update
        int ticks = 0;        
        bool isDirectClose; // Flag set to check if there are multiple instances of the application.        
        bool isMeasurementTransfer = false;
        bool isCellInitializeWidth = false; // check for gridview cell width at the time of initialization
        bool isFormDataChanged = false; // flag to check if any form data is changed before closing the form
        bool isSearchReset = false; // to check if fields are resetting in search mode
        string originalgroupname = string.Empty;
        string groupnamechange = string.Empty;
        string orgPatientIdExt = string.Empty;

        // object of Config Manager         
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
                // dbMagr = CrxDBManager.Instance;
               // dbMagr.SetConnection(@"MUM-9638\SQLEXPRESS", "SQLCLIENT");
                // CrxStructGeneralSetting gnrlSettingsStruct = new CrxStructGeneralSetting();
                // crxMgrObject.SetGeneralUserSettings(gnrlSettingsStruct);
                crxMgrObject.GetGeneralUserSettings();

                // crxMgrObject.GeneralSettings = gnrlSettingsStruct;
                if (string.IsNullOrEmpty(crxMgrObject.GeneralSettings.ServerName))
                {
                    crxMgrObject.GeneralSettings.ServerName = SystemInformation.ComputerName + @"\SQLEXPRESS";
                    CrxLogger oLogObject = CrxLogger.Instance;
                    oLogObject.Write(oMsgMgr.GetMessage("SQL_SERVER_CHANGED_TO_LOCAL"));
                }

                if (string.IsNullOrEmpty(crxMgrObject.GeneralSettings.SourceData))
                {
                    crxMgrObject.GeneralSettings.SourceData = "SQLCLIENT";
                    CrxLogger oLogObject = CrxLogger.Instance;
                    oLogObject.Write(oMsgMgr.GetMessage("SQL_SERVER_CHANGED_TO_DEFAULT"));
                }
               
                int result = 0;
                dbMagr = CrxDBManager.Instance;
                result = dbMagr.SetConnection(crxMgrObject.GeneralSettings.ServerName, crxMgrObject.GeneralSettings.SourceData);

                // log message on connection status.
                if (result.Equals(0))
                {
                    CrxStructGeneralSetting gnrlSettingsStruct = new CrxStructGeneralSetting();
                    CrxLogger oLogObject = CrxLogger.Instance;
                    oLogObject.Write(oMsgMgr.GetMessage("SQL_SERVER_CONNECTED") + crxMgrObject.GeneralSettings.ServerName);
                    gnrlSettingsStruct.ServerName = crxMgrObject.GeneralSettings.ServerName;
                    gnrlSettingsStruct.SourceData = crxMgrObject.GeneralSettings.SourceData;
                    crxMgrObject.SetGeneralUserSettings(gnrlSettingsStruct);
                }

                if (result.Equals(1))
                {
                    CrxLogger oLogObject = CrxLogger.Instance;
                    oLogObject.Write(oMsgMgr.GetMessage("SQL_SERVER_CONN_FAILED") + crxMgrObject.GeneralSettings.ServerName);
                    SQLInstanceList frmObject = new SQLInstanceList();
                    frmObject.ShowDialog();
                    frmObject.ShowInTaskbar = false;
                }
                
                if (SQLInstanceList.isCancel == 1)
                {
                    SQLInstanceList.isCancel = 0;
                    this.Close();
                    Process.GetCurrentProcess().Kill();
                }

                    // initialize class level variables                
                    isDirectClose = false;

                    // Logic to check multiple instances of the application.                 
                    if (IsProcessOpen(oMsgMgr.GetMessage("APP_NAME")))
                    {
                        isDirectClose = true;
                        DialogResult ds = RadMessageBox.Show(this, oMsgMgr.GetMessage("APP_MSG"), oMsgMgr.GetMessage("EXEC_ERROR"), MessageBoxButtons.OK, RadMessageIcon.Error);
                        this.Close();
                    }

                    InitializeComponent();

                    // Set the text for  Capture Tab form controls
                    SetTextForRibbionControl();

                    // Set the text for  Capture Tab form controls
                    SetTextForCaptureTab();
                    SetTextForSetupTab();
                    ReadSettings();

                    // ThemeResolutionService.ApplyThemeToControlTree(radpgTabCollection, "Breeze");
                  
                    // subscrive to Settings change event from settings window
                    frmSettingsWindow.OnSettingsChangedEvent += new EventHandler(SettingsChangedEventHandler);
                
                // ContextMenuService menuService = this.guiradgrdPatientList.GetService<ContextMenuService>();
                // menuService.ContextMenuDisplaying += menuService_ContextMenuDisplaying;
            }
            catch (CrxException crxex)
            {
                RadMessageBox.Show(this, oMsgMgr.GetMessage(crxex.ErrorString), oMsgMgr.GetMessage("SYSTEM_ERROR"), MessageBoxButtons.OK, RadMessageIcon.Error);
            }
            catch (Exception ex)
            {
                RadMessageBox.Show(this, ex.Message, oMsgMgr.GetMessage("SYSTEM_ERROR"), MessageBoxButtons.OK, RadMessageIcon.Error);
                CrxLogger oLogObject = CrxLogger.Instance;
                oLogObject.Write(ex.Message);                
            }
        }

        private void SetTextForSetupTab()
        {
            guiradlblPatient.Text = oMsgMgr.GetMessage("LBL_PATEINTS");
            guiradlblPatientId.Text = oMsgMgr.GetMessage("LBL_PATIENT_ID");
            guiradlblGroup.Text = oMsgMgr.GetMessage("LBL_GROUP");
            guiradlblFirstName.Text = oMsgMgr.GetMessage("LBL_FIRST_NAME");
            guiradlblDateOfBirth.Text = oMsgMgr.GetMessage("LBL_DOB");
            guirdlblGender.Text = oMsgMgr.GetMessage("LBL_GENDER");
            guiradlblLastName.Text = oMsgMgr.GetMessage("LBL_LAST_NAME");
            guilblHeight.Text = oMsgMgr.GetMessage("LBL_HEIGHT");
            guiradlblHeightUnits.Text = oMsgMgr.GetMessage("CM");
            guiradlblImperialHeight.Text = oMsgMgr.GetMessage("LBL_INCHES");
            guiradlblWeight.Text = oMsgMgr.GetMessage("LBL_WEIGHT"); 
            guiradlblWeightUnits.Text = oMsgMgr.GetMessage("KG");
            guiradlblOperator.Text = oMsgMgr.GetMessage("LBL_OPERATOR");
            guiradlblMedication.Text = oMsgMgr.GetMessage("LBL_NOTES");
            guiradlblSP.Text = oMsgMgr.GetMessage("SP");
            guiradlblDP.Text = oMsgMgr.GetMessage("DP");
            guiradlblPwvDistanceMethod.Text = oMsgMgr.GetMessage("LABEL_SUBTRACTING");
            guiradlblCarotid.Text = oMsgMgr.GetMessage("LABEL_CAROTID");
            guiradlblCarotidTonometerUnits.Text = oMsgMgr.GetMessage("MM");
            guiradlblCuff.Text = oMsgMgr.GetMessage("LABEL_CUFF");
            guiradlblCuffunits.Text = oMsgMgr.GetMessage("MM");
            guiradlblFemoralToCuff.Text = oMsgMgr.GetMessage("LABEL_FEMORAL_CUFF");
            guiradlblFemoralToCuffUnits.Text = oMsgMgr.GetMessage("MM");
            guiradlblPwvDistanceCalculation.Text = oMsgMgr.GetMessage("LABEL_PWV_DISTANCE");
            guiradlblPwvDistanceUnits.Text = oMsgMgr.GetMessage("MM");
            guiradbtnCapture.Text = oMsgMgr.GetMessage("BTN_CAPTURE");
        }

        /**This is Event handler which is called whenever the General settings and PWV settings are chaged in the Settings window.
        *It is used to changes the GUI controls as per the latest General and PWV settings.
        */
        void SettingsChangedEventHandler(object sender, EventArgs e)
        {
            try
            {
                if (InvokeRequired)
                {
                    this.Invoke(new EventHandler(SettingsChangedEventHandler));
                    return;                    
                } 
               
                // reset the measurement text fields and update according to the new settings.
                ResetPatientMeasurementFields();
                SetHeightWeightUnits();
                SetBloodPressure();
                SetPwvDistanceMethodAndUnits();

                // to update biz session object with changed setting values
                DisplayLastRecord(int.Parse(radlblpatientinternalnumber.Text.Trim()), int.Parse(radlblgroupid.Text));
                
                // SettingsProperties.CuffLocation
                if (crxMgrObject.PwvSettings.FemoralToCuff)
                {
                    guiradtxtFemoralToCuff.ReadOnly = false;
                }
                                
                if (crxMgrObject.GeneralSettings.PatientPrivacy)
                {
                    // patient privacy is enabled hide gridview
                    ShowHidePatientDetails(oMsgMgr.GetMessage("HIDE_SMALL"));
                    guiradbtnExpander.Text = oMsgMgr.GetMessage("SHOW_CAPS");
                }
                else
                {
                    // show gridview
                    ShowHidePatientDetails(oMsgMgr.GetMessage("SHOW_SMALL"));
                    guiradbtnExpander.Text = oMsgMgr.GetMessage("HIDE_CAPS");
                }
            }
            catch (Exception ex)
            {
                RadMessageBox.Show(this, ex.Message, oMsgMgr.GetMessage("SYSTEM_ERROR"), MessageBoxButtons.OK, RadMessageIcon.Error);
                CrxLogger oLogObject = CrxLogger.Instance;
                oLogObject.Write(ex.Message);
            }
        }

        /**This method is called to reset the measurement data fields. 
        */
        private void ResetPatientMeasurementFields()
        {
            guiradtxtsetupheight.Text = string.Empty;
            guiradtxtImperialHeight.Text = string.Empty;
            guiradtxtWeight.Text = string.Empty;
            guiradtxtSP.Text = string.Empty;
            guiradtxtDP.Text = string.Empty;
            guiradtxtCarotid.Text = string.Empty;
            guiradtxtCuff.Text = string.Empty;           
            guiradlblResult.Text = string.Empty;
            guiradtxtFemoralToCuff.Text = string.Empty;
            guiradtxtMedication.Text = string.Empty;
            guiradtxtOperator.Text = string.Empty;

            // guiradbtnCapture.Visible = false;  // commented for testing purpose sprint 4
        }

        /**This method is called to disable the right clicking on the Gridview.
        */
        private void menuService_ContextMenuDisplaying(object sender, ContextMenuDisplayingEventArgs e)
        {
            // the menu request is associated with a valid DockWindow instance, which resides within a DocumentTabStrip
              
            // remove the "Close" menu items
            for (int i = 0; i < e.MenuItems.Count; i++)
            {
                RadMenuItemBase menuItem = e.MenuItems[i];
                {
                    // In case you just want to disable to option you can set Enabled false
                    // menuItem.Enabled = false;
                    menuItem.Visibility = Telerik.WinControls.ElementVisibility.Collapsed;
                }
            }
        }

        /**This method is used to read the General and PWV settings from the configuration manager.
        */ 
        private void ReadSettings()
        {            
            crxMgrObject.GetGeneralUserSettings();
            crxMgrObject.GetPwvUserSettings();               
        }
        
        /**This method is called to set the text for the controls in the ribbon bar.The text is read from the resource file.
        */  
        private void SetTextForRibbionControl()
        {
            // radRibbonBar.Text = oMsgMgr.GetMessage("RIBBIONBAR_TEXT");
            // rbnTabSystem.Text = oMsgMgr.GetMessage("MENU_SYSTEM");
            // rbnTabDatabase.Text = oMsgMgr.GetMessage("MENU_DATABASE");
           // rbnTabHelp.Text = oMsgMgr.GetMessage("MENU_HELP");
            // radButtonElementSettings.Text = oMsgMgr.GetMessage("BTN_SETTINGS"); 
            // radButtonElementFindModule.Text = oMsgMgr.GetMessage("BTN_FINDMODULE");
            // radButtonElementPrinterSetup.Text = oMsgMgr.GetMessage("BTN_PRINTERSETUP");
            // radButtonElementExit.Text = oMsgMgr.GetMessage("BTN_EXIT");
            guiradgrpbxPwvDistanceMethod.Text = oMsgMgr.GetMessage("TAB_SETUP");
            radtabCapture.Text = oMsgMgr.GetMessage("TAB_CAPTURE");
            radtabReport.Text = oMsgMgr.GetMessage("TAB_REPORT");
        }

        /**This method is called to set the text for the controls in the Capture tab.The text is read from the resource file.
       */  
        private void SetTextForCaptureTab()
        {
            radlblTonometer.Text = oMsgMgr.GetMessage("LBL_TONOMETER");
            radlblFemoralCuff.Text = oMsgMgr.GetMessage("LBL_FEMORALCUFF");
            radlblTimeStatus.Text = oMsgMgr.GetMessage("LBL_TIMESTATUS");
            radlblPatientName.Text = oMsgMgr.GetMessage("LBL_PATIENTNAME");
        }

        /**This method is invoked on the click of the Exit button under System menu.
         * It will close the main window.
         */
        private void radButtonElementExit_Click(object sender, EventArgs e)
        {  
            // Close the application on click of Exit button under System menu.
            this.Close();

            // Process.GetCurrentProcess().Kill();            
        }

        /**This event is fired when window is closed.
         *It will ask for user confirmation before closing the window.
         */
        private void DefaultWindow_FormClosing(object sender, FormClosingEventArgs e)
        {
            try
            {
                // On form closing a confirmation is asked to the user to Save the unsaved data.                                       
                if (!isDirectClose)
                {
                    if (isFormDataChanged)
                    {
                        RadMessageBox.SetThemeName(oMsgMgr.GetMessage("MSG_DESERT"));
                        DialogResult ds = RadMessageBox.Show(this, oMsgMgr.GetMessage("MSG_SAVE_CHANGE"), oMsgMgr.GetMessage("MSG_SAVE_SETTINGS"), MessageBoxButtons.YesNoCancel, RadMessageIcon.Question);

                        // Keeping Yes and No separate for future use.                     
                        if (ds == DialogResult.Yes)
                        {
                            // Save data then exit.Application exited
                            CrxLogger oLogObject = CrxLogger.Instance;
                            oLogObject.Write(oMsgMgr.GetMessage("EXITSTR"));
                        }

                        if (ds == DialogResult.No)
                        {
                            // DO NOT Save data then exit.                         
                            CrxLogger oLogObject = CrxLogger.Instance;
                            oLogObject.Write(oMsgMgr.GetMessage("EXITSTR"));
                        }

                        if (ds == DialogResult.Cancel)
                        {
                            // Cancel the close event.                         
                            e.Cancel = true;
                        }
                    }
                }

                Process.GetCurrentProcess().Kill();
            }
            catch (Exception ex)
            {
                RadMessageBox.Show(this, ex.Message, oMsgMgr.GetMessage("SYSTEM_ERROR"), MessageBoxButtons.OK, RadMessageIcon.Error);
                CrxLogger oLogObject = CrxLogger.Instance;
                oLogObject.Write(ex.Message);               
            }
        }
        
        /**This is invoked on the load of the window.
         *Once the application is launched it will log the event into the log file.
         */
        private void DefaultWindow_Load(object sender, EventArgs e)
        {  
            try
            {
                // this.radpgTabCollection.ThemeName = "Office2010";                
                if (crxMgrObject.GeneralSettings.PatientPrivacy)
                {
                    // patient privacy is enabled hide gridview
                    ShowHidePatientDetails(oMsgMgr.GetMessage("HIDE_SMALL"));
                    guiradbtnExpander.Text = oMsgMgr.GetMessage("SHOW_CAPS");
                }
                else
                {
                    // show gridview
                    ShowHidePatientDetails(oMsgMgr.GetMessage("SHOW_SMALL"));
                    guiradbtnExpander.Text = oMsgMgr.GetMessage("HIDE_CAPS");
                }

                // fills day, month & year, loads group names & patient list
                radpgTabCollection.SelectedPage = guiradgrpbxPwvDistanceMethod; 
                guicmbxGender.SelectedIndex = 0;
                FillDay(0);
                FillMonthAndYear();
                LoadGroupNames();
                InitializePatientList();

               // InitializeReportAssessmentList();
                LoadPatientList();           
                              
                EnableMenuBarControls(); 
                
                // check if we can access the configuration file by reading general setting from config manager object.   
                CrxConfigManager oConfigMgr = CrxConfigManager.Instance;
                oConfigMgr.GetGeneralUserSettings();              

                // On windows load set the windows size to maximum.                 
                WindowState = FormWindowState.Maximized;

                // Log the event on successful load of the application.                 
                CrxLogger oLogObject = CrxLogger.Instance;
                oLogObject.Write(oMsgMgr.GetMessage("STARTSTR"));

                // Disable the pateint name and Capture time labels
                radlblCaptureTime.Enabled = false;
                radlblPatientName.Enabled = false;                

                // Code for assigning the handler.
                BizEventContainer.Instance.OnBizTonometerDataEvent += new BizTonometerDataEventHandler(UpdateTonoData);

                BizEventContainer.Instance.OnBizCarotidQualityEvent += new BizCarotidQualityEventHandler(qualityIndicator_CarotidQualityEvent);                

                // Quality indicator ProgressBarSetup
                prim1 = (ProgressBarPrimitive)this.radProgressBarQualityIndicator.ProgressBarElement.Children[1];
                radProgressBarQualityIndicator.Minimum = 0;
                radProgressBarQualityIndicator.Maximum = QualityIndicatorHeight;
                prim1.BackColor = prim1.BackColor2 = prim1.BackColor3 = prim1.BackColor4 = Color.Red;
                radbtnTick.Enabled = false;
            }
            catch (CrxException cfgExp)
            {
                // Exception if any will be logged and displayed(appropiate message) to the user.                  
                CrxMessagingManager oMsgMgr = CrxMessagingManager.Instance;
                string errorMessage = oMsgMgr.GetMessage(cfgExp.ErrorCode);
                
                // show error on screen                 
                RadMessageBox.Show(this, errorMessage, oMsgMgr.GetMessage("SYSTEM_ERROR"), MessageBoxButtons.OK, RadMessageIcon.Error);

                // write message in log file                
                CrxLogger oLogObject = CrxLogger.Instance;
                oLogObject.Write(errorMessage);

                // close the application.
                // do not ask question to save data.                 
                isDirectClose = true;
                this.Close();
            }
            catch (Exception ex)
            {
                RadMessageBox.Show(this, ex.Message, oMsgMgr.GetMessage("SYSTEM_ERROR"), MessageBoxButtons.OK, RadMessageIcon.Error);
                CrxLogger oLogObject = CrxLogger.Instance;
                oLogObject.Write(ex.Message);
            }
        }

        /**This method is used to populate the group names into the combo box from the database using database manager class. 
        */
        void LoadGroupNames()
        {
            // fetches group name and binds it
            try
            {
                DataSet ds = new DataSet();
                ds = dbMagr.GetGroupLists();

                DataRow dr = ds.Tables[0].NewRow();
                dr["GroupName"] = oMsgMgr.GetMessage("SELECT_CAPS"); // "--Select--";
                dr["GroupIdentifier"] = 0;

                ds.Tables[0].Rows.InsertAt(dr, 0);

                guicmbGroup.DataSource = ds.Tables[0];
                guicmbGroup.DisplayMember = "GroupName";

                guicmbGroup.SelectedIndex = 0;
            }
            catch (CrxException ex)
            {
                if (ex.ExceptionObject != null)
                {
                    RadMessageBox.Show(this, ex.ExceptionObject.Message, oMsgMgr.GetMessage("SYSTEM_ERROR"), MessageBoxButtons.OK, RadMessageIcon.Error);
                    CrxLogger oLogObject = CrxLogger.Instance;
                    oLogObject.Write(ex.ExceptionObject.Message);
                }
                else if (String.IsNullOrEmpty(ex.ErrorString))
                {
                    RadMessageBox.Show(this, oMsgMgr.GetMessage(ex.ErrorString), oMsgMgr.GetMessage("SYSTEM_ERROR"), MessageBoxButtons.OK, RadMessageIcon.Error);
                    CrxLogger oLogObject = CrxLogger.Instance;
                    oLogObject.Write(ex.ErrorString);
                }
            }
        }

        /**This method is called when the event handler of BizCarotidQualityEvent is executed.
         * Here depending upon the signal strength the progress bar color is displayed and the Tick button is enabled.
        */
        void qualityIndicator_CarotidQualityEvent(object sender, BizCarotidQualityEventArgs e)
        {
            countOne++;            

           // radlblPatientName.Text = countOne.ToString();
            chartTonometer.ChartAreas[0].AxisY.Minimum = e.signalMinimum * ChartAreaMinimumY;
            chartTonometer.ChartAreas[0].AxisY.Maximum = e.signalMaximum * ChartAreaMaximumY;
            
            signalStrength = e.signalMaximum - e.signalMinimum;
            if (signalStrength > QualityIndicatorHeight)
            {
                signalStrength = QualityIndicatorHeight;
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
                RadMessageBox.Show(this, ex.Message, oMsgMgr.GetMessage("SYSTEM_ERROR"), MessageBoxButtons.OK, RadMessageIcon.Error);
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
                // Open the settings dialog box.                 
                frmSettingsWindow settingWinObject = new frmSettingsWindow(this);
                settingWinObject.ShowDialog();
            }
            catch (Exception ex)
            {
                RadMessageBox.Show(this, ex.Message, oMsgMgr.GetMessage("SYSTEM_ERROR"), MessageBoxButtons.OK, RadMessageIcon.Error);
                CrxLogger oLogObject = CrxLogger.Instance;
                oLogObject.Write(ex.Message);             
            }
        }

        /**This method is called when the user clicks on the cross button during the capture.
        */  
        private void radbtnCross_Click(object sender, EventArgs e)
        {           
            CrossButtonAction();
        }

        /**This is called when the timer1 is enabled.
        */ 
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
                count++;

                // radlblCaptureTime.Text = count.ToString();
                int data = e.data;
                DateTime timeStamp = DateTime.Now;

                // set the maximum y-axis,if the incoming data has a point greater than the existing y-axis value then set the new data point as the y-axix maximum.
                if (data > chartTonometer.ChartAreas[0].AxisY.Maximum)
                {
                    chartTonometer.ChartAreas[0].AxisY.Maximum = data * 1.04;
                }

                // Add new data point to its series.
                newSeries.Points.AddXY(timeStamp.ToOADate(), data);

                // remove all points from the source series older than screen width seconds.
                double removeBefore = timeStamp.AddSeconds((double)screenwidth * (-1)).ToOADate();

                // remove oldest values to maintain a constant number of data points
                while (newSeries.Points[0].XValue < removeBefore)
                {
                    newSeries.Points.RemoveAt(0);
                }

                // set the x axis's minimum and maximum values.
                chartTonometer.ChartAreas[0].AxisX.Minimum = newSeries.Points[0].XValue;

                chartTonometer.ChartAreas[0].AxisX.Maximum = DateTime.FromOADate(newSeries.Points[0].XValue).AddSeconds(screenwidth).ToOADate();

                chartTonometer.Invalidate();

                // timer3.Enabled = true;
            }
            catch (Exception ex)
            {
                RadMessageBox.Show(this, ex.Message, oMsgMgr.GetMessage("SYSTEM_ERROR"), MessageBoxButtons.OK, RadMessageIcon.Error);
                CrxLogger oLogObject = CrxLogger.Instance;
                oLogObject.Write(ex.Message);
            }
        }

        /**This method is called when the Setup, Capture or Report tab is selected.
        */ 
        private void radpgTabCollection_Click(object sender, EventArgs e)
        {
            try
            {
                chartTonometer.Series.Clear();
                guiradmnuitemSettings.Enabled = true;

                // read the coms port and simulation type.
                if (radpgTabCollection.SelectedPage.Text.Equals(oMsgMgr.GetMessage("TAB_CAPTURE")))
                {
                    if (!radtabCapture.Enabled)
                    {
                        return;
                    }

                    SetTonometerWaveformProperties();
                    guiradgrpbxPwvDistanceMethod.Enabled = false;
                    radtabReport.Enabled = false;

                    // radRibbonBar.Enabled = false;
                    radlblPatientName.Enabled = true;
                    radlblTimeStatus.Text = "Time to Deflation 1:30"; // hardcoded for demo purpose(mockup).

                   // radlblPatientName.Text = "Default Patient"; // string.Empty; // Hardcoding since this will be removed in coming sprints as the patient name will be coming from the session/patient object.
                     radlblCaptureTime.Enabled = true;

                     // radlblCaptureTime.Text = BizSession.Instance().measurement.captureTime.ToString();
                    SetCaptureTimeInStatusBar();
                                        
                    radlblMessage.Text = "Simulation Mode"; // Hardcoding since this will be removed in coming sprints as it will be coming from the biz.dll 
                    Thread startCarotidTonometerCapture = new Thread(StartCarotidTonometerCapture);
                    startCarotidTonometerCapture.Start();
                    timer2.Enabled = true;
                }
                else if (radpgTabCollection.SelectedPage.Text.Equals(oMsgMgr.GetMessage("TAB_REPORT")))
                {
                    if (!radtabReport.Enabled)
                    {
                        return;
                    }

                    // open report form under report tab
                    // var childForm = new Report();
                    if (SettingsProperties.reportChildForm != null)
                    {
                        SettingsProperties.reportChildForm.Close();
                    }

                    SettingsProperties.reportChildForm = new Report();
                    SettingsProperties.reportChildForm.TopLevel = false;
                    SettingsProperties.reportChildForm.Dock = DockStyle.Fill;
                    SettingsProperties.reportChildForm.FormBorderStyle = System.Windows.Forms.FormBorderStyle.None;

                    // adds report form under parent window control
                    var page = radpgTabCollection.Pages[2];
                    SettingsProperties.reportChildForm.Parent = page;
                    page.Controls.Add(SettingsProperties.reportChildForm);
                    SettingsProperties.reportChildForm.Show();

                    // disable setting tab on menu bar
                    guiradmnuitemSettings.Enabled = false;                    
                }
                else if (radpgTabCollection.SelectedPage.Text.Equals(oMsgMgr.GetMessage("TAB_SETUP")))
                {
                    // load patient list on setup tab click
                    LoadPatientList();
                    
                    // var childForm = new Report();
                    
                    // adds report form under parent window control
                    // var page = radpgTabCollection.Pages[2];
                    
                    // page.Controls.Remove(childForm);       
                }
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
            // Start the capture of data points.
            BizSession.Instance().StartCapture();
        }

        /** This method is used to set the tonometer graphs properties.
        */  
        private void SetTonometerWaveformProperties()
        {            
            screenwidth = BizSession.Instance().measurement.captureTime + HandShakePeriod;
            
            // replace minValue with VerticalMin and VerticalMax.
            DateTime minValue = DateTime.Now;
            DateTime maxValue = minValue.AddSeconds(screenwidth);

            // Reset number of series in the chart.
            chartTonometer.Series.Clear();

            // set y axis
            chartTonometer.ChartAreas[0].AxisY.Minimum = 0;
            chartTonometer.ChartAreas[0].AxisY.Maximum = TonometerHeight;
            signalStrength = 0;

            // set x axis
            chartTonometer.ChartAreas[0].AxisX.Minimum = minValue.ToOADate();
            chartTonometer.ChartAreas[0].AxisX.Maximum = maxValue.ToOADate();

            // give name (for internal use) to the series used for plotting the points,its chart type and the color of the graph.
            newSeries = new Series("Tonometer");
            newSeries.ChartType = SeriesChartType.FastLine;
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
            guiradgrpbxPwvDistanceMethod.Enabled = true;
            radtabReport.Enabled = true;

            // radRibbonBar.Enabled = true;
            radpgTabCollection.SelectedPage = radtabReport;   
        }

        /**This method is called when the user clicks on the Cross button.
        */ 
        private void CrossButtonAction()
        {
            DialogResult ds = RadMessageBox.Show(this, oMsgMgr.GetMessage("CAPTURE_FAILED"), oMsgMgr.GetMessage("INFORMATION"), MessageBoxButtons.YesNo, RadMessageIcon.Info);
           if (ds == DialogResult.Yes)
           {
               Thread stopCarotidTonometerCapture = new Thread(StopCarotidTonometerCapture);
               stopCarotidTonometerCapture.Start();               
               guiradgrpbxPwvDistanceMethod.Enabled = true;
               radtabReport.Enabled = true;

               // radRibbonBar.Enabled = true;
               radpgTabCollection.SelectedPage = guiradgrpbxPwvDistanceMethod;
               radlblMessage.Text = string.Empty;
           }             
        }

        /** This method is used to stop the tonometer data capture.
        */  
        private void StopCarotidTonometerCapture()
        {
            BizSession.Instance().StopCapture();
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
            if (radpgTabCollection.SelectedPage.Text.Equals(oMsgMgr.GetMessage("TAB_CAPTURE")))
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

        private void timer3_Tick(object sender, EventArgs e)
        {
            count++;
            radlblCaptureTime.Text = count.ToString();
        }      

        /** This method is used to show the grid view when the Expand button is clicked.
        */ 
        private void guiradbtnExpander_Click(object sender, EventArgs e)
        {
            if (guiradbtnExpander.Text.ToLower().CompareTo(oMsgMgr.GetMessage("HIDE_SMALL")) == 0)
            {
                ShowHidePatientDetails(oMsgMgr.GetMessage("HIDE_SMALL"));
                guiradbtnExpander.Text = oMsgMgr.GetMessage("SHOW_CAPS");
            }
            else
            {
                ShowHidePatientDetails(oMsgMgr.GetMessage("SHOW_SMALL"));

                guiradbtnExpander.Text = oMsgMgr.GetMessage("HIDE_CAPS");
            }

            SetButtonsForHideMode();
        }

        /** This method is used to hide the grid view when the Expand button is clicked.
        */ 
        private void ShowHidePatientDetails(string value)
        {
            // hides patient gridview acoording to show / hide values
            if (value.ToLower().CompareTo(oMsgMgr.GetMessage("HIDE_SMALL")) == 0)
            {
                splitContainer1.SplitterDistance = 20;
            }
            else
            {
                splitContainer1.SplitterDistance = 350;
            }
        }
        
        /** This method is used to initialise the grid view.
        */
        private void InitializePatientList()
        {
            try
            {
                isCellInitializeWidth = true;
                guiradgrdPatientList.TableElement.BeginUpdate();

                guiradgrdPatientList.Columns.Add("SystemIdentifier", "SystemIdentifier", "SystemIdentifier");                
                guiradgrdPatientList.Columns[0].Width = 0;
                guiradgrdPatientList.Columns[0].IsVisible = false;

                guiradgrdPatientList.Columns.Add("PatientNumberInternal", "PatientNumberInternal", "PatientNumberInternal");                
                guiradgrdPatientList.Columns[1].Width = 65;
                guiradgrdPatientList.Columns[1].IsVisible = false;

                guiradgrdPatientList.Columns.Add("GroupIdentifier", "GroupIdentifier", "GroupIdentifier"); 
                guiradgrdPatientList.Columns[2].Width = 65;
                guiradgrdPatientList.Columns[2].IsVisible = false;

                guiradgrdPatientList.Columns.Add("GroupName", "Group", "GroupName");
                guiradgrdPatientList.Columns[3].Width = 87;

                guiradgrdPatientList.Columns.Add("PatientId", "Patient Id", "PatientIDExternalReference");  
                guiradgrdPatientList.Columns[4].Width = 87;

                guiradgrdPatientList.Columns.Add("LastName", "Last Name", "LastName");                
                guiradgrdPatientList.Columns[5].Width = 87;

                guiradgrdPatientList.Columns.Add("FirstName", "First Name", "FirstName");                
                guiradgrdPatientList.Columns[6].Width = 87;

                guiradgrdPatientList.Columns.Add("DateOfBirth", "Date Of Birth", "DateOfBirth");    
                guiradgrdPatientList.Columns[7].Width = 87;
                guiradgrdPatientList.Columns[7].FormatString = "{0:d/M/yyyy}";

                guiradgrdPatientList.Columns.Add("Gender", "Gender", "Gender");
                guiradgrdPatientList.Columns[8].Width = 87;

                guiradgrdPatientList.TableElement.EndUpdate();
                guiradgrdPatientList.AutoGenerateColumns = false;
                isCellInitializeWidth = false;
            }
            catch (Exception ex)
            {
                RadMessageBox.Show(this, ex.Message, oMsgMgr.GetMessage("SYSTEM_ERROR"), MessageBoxButtons.OK, RadMessageIcon.Error);
                CrxLogger oLogObject = CrxLogger.Instance;
                oLogObject.Write(ex.Message);
            }            
        }
      
        /** This method populates the patient data from the database into the Patient grid view.
        */ 
        private void LoadPatientList()
        {
            try
            {
                BrowseMode(true);                

                DataSet ds = new DataSet();
                ds = dbMagr.GetPatientDemographicRecords();

                // Call FetchRecords method from Database Manager
                guiradgrdPatientList.DataSource = ds.Tables[0];

                if (ds.Tables[0].Rows.Count > 0)
                {
                    BrowseMode(true);
                                        
                    guiradlblNumberOfPatients.Text = ds.Tables[0].Rows.Count.ToString();                    
                    GridViewRowInfo lastRow;

                    // Display last record details into the demographic fields.
                    lastRow = guiradgrdPatientList.Rows[guiradgrdPatientList.Rows.Count - 1];
                    lastRow.IsCurrent = true;
                    lastRow.IsSelected = true;
                    int patientIdInternal = 0;
                    int groupId = 0;
                    patientIdInternal = int.Parse(lastRow.Cells[1].Value.ToString());
                    groupId = int.Parse(lastRow.Cells[2].Value.ToString());
                    radlblpatientinternalnumber.Text = patientIdInternal.ToString();
                    radlblgroupid.Text = groupId.ToString();
                    DisplayLastRecord(patientIdInternal, groupId);
                }
                else
                {
                    // no records in table set to insert mode
                    ResetFields();
                    mode = currentMode.InsertMode.ToString(); // 1;
                    BrowseMode(false);
                    guiradlblNumberOfPatients.Text = "0";
                }
            }
            catch (CrxException ex)
            {
                if (ex.ExceptionObject != null)
                {
                    RadMessageBox.Show(this, ex.ExceptionObject.Message, oMsgMgr.GetMessage("SYSTEM_ERROR"), MessageBoxButtons.OK, RadMessageIcon.Error);
                    CrxLogger oLogObject = CrxLogger.Instance;
                    oLogObject.Write(ex.ExceptionObject.Message);
                }
                else if (String.IsNullOrEmpty(ex.ErrorString))
                {
                    RadMessageBox.Show(this, oMsgMgr.GetMessage(ex.ErrorString), oMsgMgr.GetMessage("SYSTEM_ERROR"), MessageBoxButtons.OK, RadMessageIcon.Error);
                    CrxLogger oLogObject = CrxLogger.Instance;
                    oLogObject.Write(ex.ErrorString);
                }
            }               
        }

        /** This method is used to load the demographic details of the last pateint in the Patientlist gridview.
         */ 
        private void DisplayLastRecord(int patientNumberInternal, int groupId)
        {
            try
            {               
                int systemIdentifier = bobj;

                ResetFields();
                if (mode == currentMode.None.ToString())
                {
                    BrowseMode(true);
                }
                else
                {
                    BrowseMode(false);
                }

                BrowseMode(true);
                DataSet dsPatientDemographicDetails = new DataSet();
                dsPatientDemographicDetails = dbMagr.GetPatientDemographicRecords(patientNumberInternal, systemIdentifier, groupId);
                DateTime date = DateTime.Parse(dsPatientDemographicDetails.Tables[0].Rows[0]["DateOfBirth"].ToString());

                // Populate the patient's demographic details in the form.
                guiradtxtPatientID.Text = dsPatientDemographicDetails.Tables[0].Rows[0]["PatientIDExternalReference"].ToString();
                guiradtxtFirstName.Text = dsPatientDemographicDetails.Tables[0].Rows[0]["FirstName"].ToString();
                guiradtxtLastName.Text = dsPatientDemographicDetails.Tables[0].Rows[0]["LastName"].ToString();
                guicmbGroup.Text = dsPatientDemographicDetails.Tables[0].Rows[0]["GroupName"].ToString();
                guicmbDay.SelectedItem = date.Day.ToString();
                originalgroupname = guicmbGroup.Text;
                orgPatientIdExt = guiradtxtPatientID.Text;
                guicmbxMonth.SelectedIndex = date.Month;
                guicmbxYear.SelectedItem = date.Year.ToString();
                guicmbxGender.Text = dsPatientDemographicDetails.Tables[0].Rows[0]["Gender"].ToString();

                // display patients first & last name at bottom
                if (!string.IsNullOrEmpty(guiradtxtFirstName.Text.Trim()))
                {
                    radlblPatientName.Text = guiradtxtFirstName.Text.Trim() + " " + guiradtxtLastName.Text.Trim();
                }
                else
                {
                    radlblPatientName.Text = guiradtxtLastName.Text.Trim();
                }

                radlblpatientinternalnumber.Text = patientNumberInternal.ToString();
                radlblgroupid.Text = groupId.ToString();

                // intialize bizpatient object with selected record
                string dob = guicmbDay.GetItemText(guicmbDay.SelectedItem) + "/" + guicmbxMonth.GetItemText(guicmbxMonth.SelectedItem) + "/" + guicmbxYear.GetItemText(guicmbxYear.SelectedItem);
                BizPatient patientObj = BizPatient.Instance();
                patientObj.dateOfBirth = DateTime.Parse(dob);
                patientObj.firstName = guiradtxtFirstName.Text.Trim();
                patientObj.gender = guicmbxGender.SelectedItem.ToString();
                patientObj.patientNumber = UInt32.Parse(radlblpatientinternalnumber.Text.Trim());
                patientObj.groupStudyId = guicmbGroup.Text;   
            
                // groupstudyId, patientnumber id to be retrieved
                patientObj.lastName = guiradtxtLastName.Text.Trim();
                patientObj.patientId = guiradtxtPatientID.Text.Trim();

                FillSessionObjFromDB();
            }
            catch (Exception ex)
            {
                RadMessageBox.Show(this, ex.Message, oMsgMgr.GetMessage("SYSTEM_ERROR"), MessageBoxButtons.OK, RadMessageIcon.Error);
                CrxLogger oLogObject = CrxLogger.Instance;
                oLogObject.Write(ex.Message);
            }
        }

        /** This method is used to enable & disable buttons based on modes and expand button text
         */ 
        private void SetButtonsForHideMode()
        {
            if (guiradbtnExpander.Text.ToLower().CompareTo("show") == 0)
            {                
                    guiradbtnEdit.Enabled = false;
                    guiradbtnDelete.Enabled = false;                              
            }
            else
            {
                if (mode == currentMode.InsertMode.ToString() || mode == currentMode.EditMode.ToString() || mode == currentMode.SearchMode.ToString())
                {
                    guiradbtnEdit.Enabled = false;
                    guiradbtnDelete.Enabled = false;
                }
                else
                {
                    guiradbtnEdit.Enabled = true;
                    guiradbtnDelete.Enabled = true;
                }
            }
        }

        /** This method makes the Demographic details of the patient read only(browse mode) when true and vice versa.
         */
        private void BrowseMode(bool value)
        {
            if (mode == currentMode.None.ToString())
            {
                radlblMessage.Text = string.Empty;
            }

            if (value)
            {
                // makes all input fields read only and disables combo boxes
                guiradtxtFirstName.ReadOnly = true;
                guiradtxtLastName.ReadOnly = true;
                guiradtxtPatientID.ReadOnly = true;

                guicmbGroup.Enabled = false;
                guicmbxGender.Enabled = false;
                guicmbDay.Enabled = false;
                guicmbxMonth.Enabled = false;
                guicmbxYear.Enabled = false;
                guiradbtnCancel.Enabled = false;
                guiradbtnSave.Enabled = false;
                guiradbtnSearch.Enabled = true;
                guiradbtnNew.Enabled = true;
                SetButtonsForHideMode();
                guipnlMeasurementDetails.Visible = true; // added by nitesh
            }
            else
            {
                // removes read only mode and sets button(disable / enable) depending on mode
                guiradtxtFirstName.ReadOnly = false;
                guiradtxtLastName.ReadOnly = false;
                guiradtxtPatientID.ReadOnly = false;
                guicmbGroup.Enabled = true;
                guicmbxGender.Enabled = true;
                guicmbDay.Enabled = true;
                guicmbxMonth.Enabled = true;
                guicmbxYear.Enabled = true;

                if (mode == currentMode.InsertMode.ToString())
                {
                    // insert mode
                    guiradbtnCancel.Enabled = true;
                    guiradbtnSave.Enabled = true;

                    guiradbtnSearch.Enabled = false;
                    guiradbtnEdit.Enabled = false;
                    guiradbtnDelete.Enabled = false;
                    guiradbtnNew.Enabled = false;
                }
                else if (mode == currentMode.EditMode.ToString())
                {
                    // edit mode
                    guiradbtnCancel.Enabled = true;
                    guiradbtnSave.Enabled = true;
                    guiradbtnSearch.Enabled = false;
                    guiradbtnEdit.Enabled = false;
                    guiradbtnDelete.Enabled = false;
                    guiradbtnNew.Enabled = false;

                    guipnlMeasurementDetails.Visible = false; 
                }
                else if (mode == currentMode.SearchMode.ToString())
                {
                    // search mode
                    guiradbtnCancel.Enabled = true;
                    guiradbtnSave.Enabled = false;
                    guiradbtnSearch.Enabled = false;
                    guiradbtnEdit.Enabled = false;
                    guiradbtnDelete.Enabled = false;
                    guiradbtnNew.Enabled = false;
                    guipnlMeasurementDetails.Visible = false; 
                }
                else
                {
                    // default
                    guiradbtnCancel.Enabled = true;
                    guiradbtnSave.Enabled = true;
                }
            }
        }

        /** This method is called on the click of the Save button,it is used to validate the demograhic details entered by the user and save the same into the database.
         *Any expection thrown while saving the details into the database will be caught by the configuration file and logged. 
         *This expection will be shown to the user using a message box,also it will be logged into the log file.
        */
        private void guiradbtnSave_Click(object sender, EventArgs e)
        {
            guiradtxtsetupheight.Focus(); 

            // Check for duplicate 5 fields.
            // Check for duplicate patient id.
            // Save the demographic details into the database.
            try
            {
                // radRibbonBar.Enabled = true;                
                if (ValidateDemographicDetails())
                {
                    if (mode == currentMode.InsertMode.ToString())
                    {
                        CheckForPatientIdToAddPatient();                       
                    }
                    else
                    {
                        CheckForPatientIdToUpdatePatient();                        
                    }
                }                
            }
            catch (Exception ex)
            {
                RadMessageBox.Show(this, ex.Message, oMsgMgr.GetMessage("SYSTEM_ERROR"), MessageBoxButtons.OK, RadMessageIcon.Error);
                CrxLogger oLogObject = CrxLogger.Instance;
                oLogObject.Write(ex.Message);
            }

            // Measurement data will be visible.
        }

        /**This method checks if a given patient id exists,while adding a record.
         */ 
        private void CheckForPatientIdToAddPatient()
        {
            // check if patient ID exists and add accordingly
            if (dbMagr.PatientIdExists(bobj, guiradtxtPatientID.Text.Trim()))
            {
                DialogResult result = RadMessageBox.Show(oMsgMgr.GetMessage("PATIENT_ALREADY_EXIST"), oMsgMgr.GetMessage("MESSAGE"), MessageBoxButtons.YesNo);
                if (result == DialogResult.Yes)
                {
                    // add new patient record with duplicate/existing patient ID
                    AddNewPatientDetails();
                }
            }
            else
            {
                // patient ID does not exists, add record
                AddNewPatientDetails();
            }
        }

        /**This method checks if a given patient id exists,while updating a record.
         */ 
        private void CheckForPatientIdToUpdatePatient()
        {
            // check if old patient ID is changed
            if (string.Compare(orgPatientIdExt, guiradtxtPatientID.Text.Trim(), true) != 0)
            {
                // check patient ID exists and update record accordingly
                if (dbMagr.PatientIdExists(bobj, guiradtxtPatientID.Text.Trim()))
                {
                    DialogResult result = RadMessageBox.Show(oMsgMgr.GetMessage("PATIENT_ALREADY_EXIST"), oMsgMgr.GetMessage("MESSAGE"), MessageBoxButtons.YesNo);
                    if (result == DialogResult.Yes)
                    {
                        // update patient record with duplicate/existing patient ID
                        UpdatePatientDetails();
                    }
                }
                else
                {
                    // patient ID does not exists, update record
                    UpdatePatientDetails();
                }
            }
            else
            {
                // patient ID not changed, update record
                UpdatePatientDetails();
            }
        }

        /** This method is used to set the height weight units in the GUI depending on the settings selected by the user.
        */ 
        private void SetHeightWeightUnits()
        {            
            // read height and weight units and accordingly show units for height and weight.Convert values accordingly.
            // read the properties for the setting the units for measurement data.            
            if (crxMgrObject.GeneralSettings.HeightandWeightUnit.Equals(0))
            {
                int maxDigit = 3;

                // metric units i.e cm and kg.
                guiradlblHeightUnits.Text = oMsgMgr.GetMessage("CM"); // "cm";
                guiradtxtsetupheight.MaxLength = maxDigit;
                guiradlblWeightUnits.Text = oMsgMgr.GetMessage("KG"); // "kg";
                guiradtxtImperialHeight.Visible = false;
                guiradlblImperialHeight.Visible = false;
            }
            else
            {
                int maxDigit = 2;

                // imperial units i.e ft and inches and lbs.
                guiradlblHeightUnits.Text = oMsgMgr.GetMessage("FEET"); // "ft";
                guiradtxtsetupheight.MaxLength = maxDigit;

                // change cm to ft 
                // show Inches.
                guiradtxtImperialHeight.Visible = true;
                guiradlblImperialHeight.Visible = true;

                // change unit of weight to lbs.
                guiradlblWeightUnits.Text = oMsgMgr.GetMessage("LBS"); // "lbs";
            }            
        }

        /** This method is used to set the blood pressure in the GUI depending on the settings selected by the user.
    */ 
        private void SetBloodPressure()
        {
            // read blood pressure and accordingly display the combination of SP,DP and MP.            
            if (crxMgrObject.GeneralSettings.BloodPressureEntryOptions.Equals(0))
            {
                // sp and dp
                guiradlblSP.Text = oMsgMgr.GetMessage("SP"); // "SP";
                guiradlblDP.Text = oMsgMgr.GetMessage("DP"); // "DP";
            }

            // SettingsProperties.BloodPressure.Equals(1)
            if (crxMgrObject.GeneralSettings.BloodPressureEntryOptions.Equals(1))
            {
                // sp and mp
                guiradlblSP.Text = oMsgMgr.GetMessage("SP"); // "SP";
                // change dp to mp
                 guiradlblDP.Text = oMsgMgr.GetMessage("MP");                
            }

            // SettingsProperties.BloodPressure.Equals(2)
            if (crxMgrObject.GeneralSettings.BloodPressureEntryOptions.Equals(2))
            {
                // mp and dp
                // sp to MP
                guiradlblSP.Text = oMsgMgr.GetMessage("MP");
                // change dp tp DP
                guiradlblDP.Text = oMsgMgr.GetMessage("DP");
            }            
        }

        /** This method is used to set the PWV distance methods/units in the GUI depending on the settings selected by the user.
    */ 
        private void SetPwvDistanceMethodAndUnits()
        {            
            // read pwv distance units and pwv distance method and accordingly dispaly the labels and textbox.Do the calculation of for PWV distance.Also read the cuff location for it to be editable or no. 
            if (crxMgrObject.PwvSettings.PWVDistanceMethod.Equals(0))
            {
                // subtracting method.
                guiradlblPwvDistanceMethod.Text = oMsgMgr.GetMessage("SUBTRACTING_METHOD"); // "Subtracting method";
                // Set text for Cuff measurement label.
                guiradlblCuff.Text = oMsgMgr.GetMessage("LABEL_CUFF");

                // show carotid lbl,text and units.
                guiradlblCarotid.Visible = true;
                guiradtxtCarotid.Visible = true;
                guiradlblCarotidTonometerUnits.Visible = true;
            }
            else
            {
                // hide carotid lbl,text and units.
                guiradlblCarotid.Visible = false;
                guiradtxtCarotid.Visible = false;
                guiradlblCarotidTonometerUnits.Visible = false;

                // direct method.
                guiradlblPwvDistanceMethod.Text = oMsgMgr.GetMessage("DIRECT_METHOD");
                guiradlblCuff.Text = oMsgMgr.GetMessage("LABEL_DIRECT");
            }

            // SettingsProperties.PwvDistanceUnits.Equals(0)
            if (crxMgrObject.PwvSettings.PWVDistanceUnits.Equals(0))
            {
                // mm
                int value = 20;
                guiradlblCarotidTonometerUnits.Text = oMsgMgr.GetMessage("MM");
                guiradlblCuffunits.Text = oMsgMgr.GetMessage("MM"); // "mm";
                guiradlblFemoralToCuffUnits.Text = oMsgMgr.GetMessage("MM"); // "mm";
                guiradtxtFemoralToCuff.Text = value.ToString();
                guiradlblPwvDistanceUnits.Text = oMsgMgr.GetMessage("MM"); // "mm";
            }
            else
            {
                // cm                    
                int value = 200;
                guiradlblCarotidTonometerUnits.Text = oMsgMgr.GetMessage("CM"); // "cm";
                guiradlblCuffunits.Text = oMsgMgr.GetMessage("CM"); 
                guiradlblFemoralToCuffUnits.Text = oMsgMgr.GetMessage("CM"); 
                guiradtxtFemoralToCuff.Text = value.ToString();
                guiradlblPwvDistanceUnits.Text = oMsgMgr.GetMessage("CM"); 
            }
        }

        /** This method is used to update the patient demographic details and save the same into the database.
    */ 
        private void UpdatePatientDetails()
        {
            try
            {
                // updates patient record
                if (!string.IsNullOrEmpty(guicmbGroup.Text))
                {
                    groupnamechange = guicmbGroup.Text.Trim();
                }
                else
                {
                    groupnamechange = guicmbGroup.GetItemText(guicmbGroup.SelectedItem);
                }

                SavePatient(groupnamechange);
            }
            catch (Exception ex)
            {
                RadMessageBox.Show(this, ex.Message, oMsgMgr.GetMessage("SYSTEM_ERROR"), MessageBoxButtons.OK, RadMessageIcon.Error);
                CrxLogger oLogObject = CrxLogger.Instance;
                oLogObject.Write(ex.Message);
            }
        }

        /** This method is used to save new group name.
         */ 
        private void AddNewPatientDetails()
        {
            try
            {
                if (!string.IsNullOrEmpty(guicmbGroup.Text))
                {
                    // user has entered new group check if it exists or not
                    SavePatient(guicmbGroup.Text);
                }
                else
                {
                    SavePatient(guicmbGroup.GetItemText(guicmbGroup.SelectedItem));
                }
            }
            catch (Exception ex)
            {
                RadMessageBox.Show(this, ex.Message, oMsgMgr.GetMessage("SYSTEM_ERROR"), MessageBoxButtons.OK, RadMessageIcon.Error);
                CrxLogger oLogObject = CrxLogger.Instance;
                oLogObject.Write(ex.Message);
            }
        }

        /** This method is used to called on click of Save button from the GUI.
         */
        private void SavePatient(string groupname)
        {
            // saves patient record to database
            int iRow = 0;

            // instantiate struct with values entered
            CrxStructPatientDemographicData patientData = new CrxStructPatientDemographicData();
            patientData.FirstName = guiradtxtFirstName.Text.Trim();
            patientData.Gender = guicmbxGender.GetItemText(guicmbxGender.SelectedItem);
            patientData.LastName = guiradtxtLastName.Text.Trim();
            string dob = guicmbDay.GetItemText(guicmbDay.SelectedItem) + "/" + guicmbxMonth.GetItemText(guicmbxMonth.SelectedItem) + "/" + guicmbxYear.GetItemText(guicmbxYear.SelectedItem);
            patientData.DateOfBirth = Convert.ToDateTime(dob);

            // set groupname to default if not selected
            patientData.GroupName = (string.IsNullOrEmpty(groupname) ? "Default" : (groupname.ToLower().CompareTo(oMsgMgr.GetMessage("SELECT_SMALL")) == 0) ? "Default" : groupname);
            patientData.SystemIdentifier = bobj;
            patientData.PatientIDExternalReference = guiradtxtPatientID.Text.Trim();

            // check if patient record exists and save accordingly
            int recordExists = dbMagr.PatientRecordExists(patientData);
            if (mode == currentMode.InsertMode.ToString())
            {
               // insert new record when patient does not exists
                switch (recordExists)
                {
                    case 0:
                        iRow = dbMagr.SavePatientData(patientData);
                        break;
                    case 1:
                        RadMessageBox.Show(this, oMsgMgr.GetMessage("PATIENT_ALREADY_EXISTS"), oMsgMgr.GetMessage("APPLICATION_MESSAGE"), MessageBoxButtons.OK, RadMessageIcon.Error);                        
                        break;
                }
            }
            else
            {
                // update patient record
                switch (recordExists)
                {
                    case 0:
                        patientData.PatientNumberInternal = int.Parse(radlblpatientinternalnumber.Text);
                        patientData.GroupIdentifier = int.Parse(radlblgroupid.Text);
                                                                        
                        if (string.Compare(originalgroupname, groupnamechange, true) != 0)
                        {
                            // group name changed for existing patient show message box
                            DialogResult ds = RadMessageBox.Show(this, oMsgMgr.GetMessage("TRANSFER_PATIENT"), oMsgMgr.GetMessage("APPLICATION_MESSAGE"), MessageBoxButtons.YesNo, RadMessageIcon.Question);
                            switch (ds)
                            { 
                                case DialogResult.Yes:
                                    iRow = dbMagr.UpdatePatientData(patientData, true);
                                    break;
                                case DialogResult.No:
                                    iRow = dbMagr.UpdatePatientData(patientData, false);
                                    break;
                            }                            
                        }
                        else
                        {
                            // group name not changed update patient details only
                            iRow = dbMagr.UpdatePatientData(patientData, isMeasurementTransfer);
                        }

                        break;
                    case 1:
                        patientData.PatientNumberInternal = int.Parse(radlblpatientinternalnumber.Text);
                        patientData.GroupIdentifier = int.Parse(radlblgroupid.Text);

                        // show message box to transfer existing measurements to new group
                        DialogResult result = RadMessageBox.Show(this, oMsgMgr.GetMessage("TRANSFER_PATIENT"), oMsgMgr.GetMessage("APPLICATION_MESSAGE"), MessageBoxButtons.YesNo, RadMessageIcon.Question);
                        switch (result)
                        { 
                            case DialogResult.Yes:
                                iRow = dbMagr.UpdatePatientData(patientData, true);
                                break;
                            case DialogResult.No:
                                iRow = dbMagr.UpdatePatientData(patientData, false);
                                break;
                        }

                        break;
                }
            }

            if (iRow > 0)
            {
                // if record added / updated successfully 
                guipnlMeasurementDetails.Visible = true;
                SetHeightWeightUnits();
                SetBloodPressure();
                SetPwvDistanceMethodAndUnits();

                // SettingsProperties.CuffLocation
                if (crxMgrObject.PwvSettings.FemoralToCuff)
                {
                    guiradtxtFemoralToCuff.ReadOnly = false;
                }

                LoadPatientList();
                guiradgrdPatientList.Enabled = true;

                // radRibbonBar.Enabled = true;
                mode = currentMode.None.ToString();
                BrowseMode(true);                

                // after saving add it to Bizpatient object    
                BizPatient patientObj = BizPatient.Instance();
                patientObj.dateOfBirth = DateTime.Parse(dob);
                patientObj.firstName = guiradtxtFirstName.Text.Trim();
                patientObj.gender = guicmbxGender.SelectedItem.ToString();
                patientObj.patientNumber = UInt32.Parse(patientData.PatientNumberInternal.ToString());
                patientObj.groupStudyId = guicmbGroup.Text;

                // groupstudyId, patientnumber id to be retrieved
                patientObj.lastName = guiradtxtLastName.Text.Trim();
                patientObj.patientId = guiradtxtPatientID.Text.Trim();               
            }
        }

        /** This method is called when the user clicks on the New button in the GUI.The user can enter new patient details.
         */ 
        private void guiradbtnNew_Click(object sender, EventArgs e)
        {
            // set the focus to the Patient Id field.
            guiradtxtPatientID.Focus(); 
            guipnlMeasurementDetails.Visible = false;
            DisableTabs(radpgTabCollection.SelectedPage.Name.ToLower());
            mode = currentMode.InsertMode.ToString(); // 1;
            ResetFields();
            BrowseMode(false);
            radlblMessage.Text = oMsgMgr.GetMessage("INSERT_MODE"); // "Insert Mode";
            FillDay(0);

            // radRibbonBar.Enabled = false;
            guiradgrdPatientList.Enabled = false;
        }

        /** 
         */ 
        private void DisableTabs(string currentTab)
        {
            // disables all the tabs except the currentTab
            for (int pageCount = 0; pageCount < radpgTabCollection.Pages.Count; pageCount++)
            {
                if (radpgTabCollection.Pages[pageCount].Name.ToLower() != currentTab)
                {
                    radpgTabCollection.Pages[pageCount].Enabled = false;
                }
            }
        }

        /** This method is called when the user clicks on the Search button in the GUI.
         */ 
        private void guiradbtnSearch_Click(object sender, EventArgs e)
        {
            guiradtxtPatientID.Focus();
            try
            {
                // get the patient record and cached it
                DataSet ds = new DataSet();
                ds = dbMagr.GetPatientDemographicRecords();
                AppDomain.CurrentDomain.SetData("cachePatient", ds);                
                
                // radRibbonBar.Enabled = true;
                radlblMessage.Text = oMsgMgr.GetMessage("SEARCH_MODE"); // "Search Mode";
                mode = currentMode.SearchMode.ToString();
                isSearchReset = true;
                ResetFields();
                BrowseMode(false);
                isSearchReset = false;
            }
            catch (Exception ex)
            {
                RadMessageBox.Show(this, ex.Message, oMsgMgr.GetMessage("SYSTEM_ERROR"), MessageBoxButtons.OK, RadMessageIcon.Error);
                CrxLogger oLogObject = CrxLogger.Instance;
                oLogObject.Write(ex.Message);
            }
        }

        /** This method is used to fill the months and year into the combo box in the GUI.It is called on the FormLoad event.
         */ 
        private void FillMonthAndYear()
        {
            try
            {
                // list of Month to be fetched from resource file.Need to decide which resource file.
                guicmbxMonth.Items.Insert(0, oMsgMgr.GetMessage("MONTH"));
                guicmbxMonth.SelectedIndex = 0;
                
                // reads min year from app.config and binds the drop down
                for (int year = int.Parse(ConfigurationSettings.AppSettings["MinYearForDOB"].ToString()); year <= DateTime.Now.Year; year++)
                {
                    guicmbxYear.Items.Add(year.ToString());
                }

                guicmbxYear.Items.Insert(0, oMsgMgr.GetMessage("YEAR"));
                guicmbxYear.SelectedIndex = 0;
            }
            catch (Exception ex)
            {
                RadMessageBox.Show(this, ex.Message, oMsgMgr.GetMessage("SYSTEM_ERROR"), MessageBoxButtons.OK, RadMessageIcon.Error);
                CrxLogger oLogObject = CrxLogger.Instance;
                oLogObject.Write(ex.Message);
            }
        }

        /** This method is used to fill days into the combo box in the GUI.It is called on the FormLoad event.
        */ 
        private void FillDay(int lastDay)
        {
            try
            {
                int selectedvaue = 0;
                
                // retrieve the selected index
                if (guicmbDay.SelectedIndex > 0)
                {
                    selectedvaue = guicmbDay.SelectedIndex;
                }

                // clear items in combo box
                guicmbDay.Items.Clear();

                // set to 31 if lastday is 0
                if (lastDay == 0)
                {
                    lastDay = 31;
                }

                // Fill day dropdown.
                for (int day = 1; day <= lastDay; day++)
                {
                    guicmbDay.Items.Add(day.ToString());
                }

                guicmbDay.Items.Insert(0, oMsgMgr.GetMessage("DAY"));

                // in case last day is less than previous selected value in combo box, set selected index to last day
                if (selectedvaue > lastDay)
                {
                    guicmbDay.SelectedIndex = lastDay;
                }
                else
                {
                    guicmbDay.SelectedIndex = selectedvaue;
                }
            }
            catch (Exception ex)
            {
                RadMessageBox.Show(this, ex.Message, oMsgMgr.GetMessage("SYSTEM_ERROR"), MessageBoxButtons.OK, RadMessageIcon.Error);
                CrxLogger oLogObject = CrxLogger.Instance;
                oLogObject.Write(ex.Message);
            }
        }

        /**This event is fired when the combox value of the month is changed.
         */
        private void guicmbxMonth_SelectedIndexChanged(object sender, EventArgs e)
        {
            try
            {
                // fetches days for a month according to month selected
                string methodName = (guicmbxMonth.GetItemText(guicmbxMonth.SelectedItem).ToLower().CompareTo(oMsgMgr.GetMessage("FEB_CONDITION")) == 0 ? "leapyear" : (guicmbxMonth.GetItemText(guicmbxMonth.SelectedItem).ToLower().Equals(oMsgMgr.GetMessage("APR_CONDITION")) || guicmbxMonth.GetItemText(guicmbxMonth.SelectedItem).ToLower().Equals(oMsgMgr.GetMessage("JUN_CONDITION")) || guicmbxMonth.GetItemText(guicmbxMonth.SelectedItem).ToLower().Equals(oMsgMgr.GetMessage("SEP_CONDITION")) || guicmbxMonth.GetItemText(guicmbxMonth.SelectedItem).ToLower().Equals(oMsgMgr.GetMessage("NOV_CONDITION"))) ? "30" : "31");

                switch (methodName)
                {
                    case "leapyear":
                        FillDayLeapYear();
                        break;
                    case "30":
                        FillDay(30);
                        break;
                    case "31":
                        FillDay(31);
                        break;
                }

                // if (guicmbxMonth.GetItemText(guicmbxMonth.SelectedItem).ToLower().Equals(oMsgMgr.GetMessage("FEB_CONDITION")))
                // {
                //    FillDayLeapYear();
                // }
                // else if (guicmbxMonth.GetItemText(guicmbxMonth.SelectedItem).ToLower().Equals(oMsgMgr.GetMessage("JAN_CONDITION")) || guicmbxMonth.GetItemText(guicmbxMonth.SelectedItem).ToLower().Equals(oMsgMgr.GetMessage("MAR_CONDITION")) || guicmbxMonth.GetItemText(guicmbxMonth.SelectedItem).ToLower().Equals(oMsgMgr.GetMessage("MAY_CONDITION")) || guicmbxMonth.GetItemText(guicmbxMonth.SelectedItem).ToLower().Equals(oMsgMgr.GetMessage("JUL_CONDITION")) || guicmbxMonth.GetItemText(guicmbxMonth.SelectedItem).ToLower().Equals(oMsgMgr.GetMessage("AUG_CONDITION")) || guicmbxMonth.GetItemText(guicmbxMonth.SelectedItem).ToLower().Equals(oMsgMgr.GetMessage("OCT_CONDITION")) || guicmbxMonth.GetItemText(guicmbxMonth.SelectedItem).ToLower().Equals(oMsgMgr.GetMessage("DEC_CONDITION")))
                // {
                //    FillDay(31);
                // }
                // else if (guicmbxMonth.GetItemText(guicmbxMonth.SelectedItem).ToLower().Equals(oMsgMgr.GetMessage("APR_CONDITION")) || guicmbxMonth.GetItemText(guicmbxMonth.SelectedItem).ToLower().Equals(oMsgMgr.GetMessage("JUN_CONDITION")) || guicmbxMonth.GetItemText(guicmbxMonth.SelectedItem).ToLower().Equals(oMsgMgr.GetMessage("SEP_CONDITION")) || guicmbxMonth.GetItemText(guicmbxMonth.SelectedItem).ToLower().Equals(oMsgMgr.GetMessage("NOV_CONDITION")))
                // {
                //    FillDay(30);
                // }

                // to fetch records in search mode
                if (!IsFieldsBlank(true) && mode == currentMode.SearchMode.ToString())
                {
                    GetSearchResults();
                }

                guilblMonth.Text = guicmbxMonth.Text;
            }
            catch (Exception ex)
            {
                RadMessageBox.Show(this, ex.Message, oMsgMgr.GetMessage("SYSTEM_ERROR"), MessageBoxButtons.OK, RadMessageIcon.Error);
                CrxLogger oLogObject = CrxLogger.Instance;
                oLogObject.Write(ex.Message);
            }
        }

        /**This event is fired when the combox value of the year is changed.
         */ 
        private void guicmbxYear_SelectedIndexChanged(object sender, EventArgs e)
        {
            try
            {
                // binds number of days for feb month according to year selected
                if (guicmbxMonth.GetItemText(guicmbxMonth.SelectedItem).ToLower().Equals("feb"))
                {
                    FillDayLeapYear();
                }

                // to fetch records in search mode
                if (!IsFieldsBlank(true) && mode == currentMode.SearchMode.ToString())
                {
                    GetSearchResults();
                }

                guilblYear.Text = guicmbxYear.Text;            
            }
            catch (Exception ex)
            {
                RadMessageBox.Show(this, ex.Message, oMsgMgr.GetMessage("SYSTEM_ERROR"), MessageBoxButtons.OK, RadMessageIcon.Error);
                CrxLogger oLogObject = CrxLogger.Instance;
                oLogObject.Write(ex.Message);
            }
        }

        /** This method is called to check if a year is leap year,if so accordingly the combobox values for the Months and Day are changed.
         */ 
        private void FillDayLeapYear()
        {
            try
            {
                // checks if year selected is leap year and calls fillday method to bind days
                if (guicmbxYear.SelectedIndex > 0)
                {
                    if (DateTime.IsLeapYear(int.Parse(guicmbxYear.GetItemText(guicmbxYear.SelectedItem))))
                    {
                        FillDay(28);
                    }
                    else
                    {
                        FillDay(29);
                    }
                }
                else
                {
                    FillDay(29);
                }
            }
            catch (Exception ex)
            {
                RadMessageBox.Show(this, ex.Message, oMsgMgr.GetMessage("SYSTEM_ERROR"), MessageBoxButtons.OK, RadMessageIcon.Error);
                CrxLogger oLogObject = CrxLogger.Instance;
                oLogObject.Write(ex.Message);
            }
        }

        /** This method is called to reset the dempgraphic data fields in the GUI
         */ 
        private void ResetFields()
        { 
            // to reset all input fields            
            guiradtxtPatientID.Text = string.Empty;
            guiradtxtLastName.Text = string.Empty;
            guiradtxtFirstName.Text = string.Empty;
            guicmbDay.SelectedIndex = 0;
            guicmbGroup.DataSource = null;
            guicmbGroup.Items.Clear();
            LoadGroupNames();            
            guicmbxGender.SelectedIndex = 0;
            guicmbxMonth.SelectedIndex = 0;
            guicmbxYear.SelectedIndex = 0;            
        }

        /**This method is called to validate the demographic details entered by the user.
         */ 
        private bool ValidateDemographicDetails()
        { 
            // validates mandatory demographic fields
            bool flag = true;
            if (guiradtxtLastName.Text.Trim().CompareTo(string.Empty) == 0)
            {
                flag = false;                
                RadMessageBox.Show(oMsgMgr.GetMessage("ENTER_LAST_NAME"), oMsgMgr.GetMessage("MESSAGE"), MessageBoxButtons.OK);
            }
            else if (guicmbDay.SelectedIndex == 0 || guicmbxMonth.SelectedIndex == 0 || guicmbxYear.SelectedIndex == 0)
            {
                flag = false;               
                RadMessageBox.Show(oMsgMgr.GetMessage("SELECT_DOB"), oMsgMgr.GetMessage("MESSAGE"), MessageBoxButtons.OK);
            }
            else if (guicmbxGender.SelectedIndex == 0)
            {
                flag = false;                
                RadMessageBox.Show(oMsgMgr.GetMessage("SELECT_GENDER"), oMsgMgr.GetMessage("MESSAGE"), MessageBoxButtons.OK);
            }
            
            return flag;
        }

        /**This event is calld when the user clicks on the Edit button in the GUI.The user can now edit th demographic details of the selected patient.
         */ 
        private void guiradbtnEdit_Click(object sender, EventArgs e)
        {
            guiradtxtPatientID.Focus();

            // brings the screen to input mode          
            if (int.Parse(guiradlblNumberOfPatients.Text.Trim()) != 0)
            {
                mode = currentMode.EditMode.ToString();
                BrowseMode(false);
                radlblMessage.Text = oMsgMgr.GetMessage("EDIT_MODE"); // "Edit Mode";
                
                // radRibbonBar.Enabled = false;
                guiradgrdPatientList.Enabled = false;
                guipnlMeasurementDetails.Visible = false;
            }
            else
            {               
                RadMessageBox.Show(oMsgMgr.GetMessage("NO_RECORDS_TO_EDIT"), oMsgMgr.GetMessage("MESSAGE"), MessageBoxButtons.OK);
            }
        }
        
        /** This method is called when a user selects a record from the patient list and clicks on Delete button. The user is asked for the confirmation whether he wants to delete the record.If yes the record is deleted from the database.
         */ 
        private void guiradbtnDelete_Click(object sender, EventArgs e)
        {
            try
            {
                // deletes patient from database for patient with 1 relation in patient group relation, else deletes relation of patient with that group from patient group relation table
                if (int.Parse(guiradlblNumberOfPatients.Text.Trim()) != 0)
                {
                    // radRibbonBar.Enabled = true;
                    CrxStructPatientDemographicData patientDemographicData = new CrxStructPatientDemographicData();

                    foreach (GridViewRowInfo row in guiradgrdPatientList.SelectedRows)
                    {
                        patientDemographicData.PatientNumberInternal = int.Parse(row.Cells[1].Value.ToString());
                        patientDemographicData.GroupIdentifier = int.Parse(row.Cells[2].Value.ToString());
                        patientDemographicData.SystemIdentifier = bobj;
                    }

                    DialogResult ds = RadMessageBox.Show(this, oMsgMgr.GetMessage("DELETE_PATEINT"), oMsgMgr.GetMessage("APPLICATION_MESSAGE"), MessageBoxButtons.YesNo, RadMessageIcon.Question);

                    if (ds == DialogResult.Yes)
                    {
                        dbMagr.DeletePatientData(patientDemographicData);

                        // refresh the db.            
                        LoadPatientList();
                    }
                }
                else
                {                    
                    RadMessageBox.Show(oMsgMgr.GetMessage("NO_RECORDS_TO_DELETE"), oMsgMgr.GetMessage("MESSAGE"), MessageBoxButtons.OK);
                }
            }
            catch (Exception ex)
            {
                RadMessageBox.Show(this, ex.Message, oMsgMgr.GetMessage("SYSTEM_ERROR"), MessageBoxButtons.OK, RadMessageIcon.Error);
                CrxLogger oLogObject = CrxLogger.Instance;
                oLogObject.Write(ex.Message);
            }           
        }

        /** This event is fired when the user leaves the text box where the Cuff value is entered.
         */ 
        private void guiradtxtCuff_Leave(object sender, EventArgs e)
        {
            EnableCaptureAndCalculatePwvDistance();
        }

        /** This method is called to calculate the PWV distance.
         */ 
        private void EnableCaptureAndCalculatePwvDistance()
        {
            try
            {
                if (crxMgrObject.PwvSettings.PWVDistanceMethod.Equals(0) && guiradtxtCarotid.Text.Length > 0 && guiradtxtCuff.Text.Length > 0 && guiradtxtFemoralToCuff.Text.Length > 0)
                {
                    guiradlblResult.Text = (int.Parse(guiradtxtCuff.Text) - int.Parse(guiradtxtCarotid.Text) - int.Parse(guiradtxtFemoralToCuff.Text)).ToString();
                    guiradbtnCapture.Visible = true;
                }

                if (crxMgrObject.PwvSettings.PWVDistanceMethod.Equals(1) && guiradtxtCuff.Text.Length > 0 && guiradtxtFemoralToCuff.Text.Length > 0)
                {
                    guiradlblResult.Text = (int.Parse(guiradtxtCuff.Text) - int.Parse(guiradtxtFemoralToCuff.Text)).ToString();
                    guiradbtnCapture.Visible = true;
                }
            }
            catch (Exception ex)
            {
                RadMessageBox.Show(this, ex.Message, oMsgMgr.GetMessage("SYSTEM_ERROR"), MessageBoxButtons.OK, RadMessageIcon.Error);
                CrxLogger oLogObject = CrxLogger.Instance;
                oLogObject.Write(ex.Message);
            }
        }

        /** This method is called when the user clicks on the Capture button,after enetering the Measurement Details for a patient.
         */ 
        private void guiradbtnCapture_Click(object sender, EventArgs e)
        {
            try
            {
                obj = (BizPWV)BizSession.Instance().measurement;
                SetHeightWeightValuesInBizSession();
                obj.notes = guiradtxtMedication.Text;
                obj.operatorId = guiradtxtOperator.Text;
                SetBloodPressureValuesInBizSession();
                SetPwvDistanceValuesInBizSession();

                // validate the measurement data.
                if (!obj.Validate())
                {
                    RadMessageBox.Show(this, oMsgMgr.GetMessage("ERROR_VALIDATING"), oMsgMgr.GetMessage("SYSTEM_ERROR"), MessageBoxButtons.OK, RadMessageIcon.Error);
                    guiradbtnCapture.Visible = false;

                    // return;
                }

                // radpgTabCollection.SelectedPage = radtabReport;

                // radpgTabCollection.SelectedPage = radtabReport;
                // save the measurement data into the bizsession object.            
                // obj.StartCapture();  commented by vibhuti 14 dec 2010
            }
            catch (Exception ex)
            {
                RadMessageBox.Show(this, ex.Message, oMsgMgr.GetMessage("SYSTEM_ERROR"), MessageBoxButtons.OK, RadMessageIcon.Error);
                CrxLogger oLogObject = CrxLogger.Instance;
                oLogObject.Write(ex.Message);
            }
        }

        /** This method is called to pass the measurement values to the BizSession.
         */ 
        private void SetHeightWeightValuesInBizSession()
        {
            if (crxMgrObject.GeneralSettings.HeightandWeightUnit.Equals(0))
            {
                if (!string.IsNullOrEmpty(guiradtxtsetupheight.Text.Trim()) && (!string.IsNullOrEmpty(guiradtxtWeight.Text.Trim())))
                {
                    obj.heightAndWeight.heightInCentimetres = (ushort)int.Parse(guiradtxtsetupheight.Text.Trim());
                    obj.heightAndWeight.weightInKilograms = (ushort)int.Parse(guiradtxtWeight.Text.Trim());
                }
            }

            if (crxMgrObject.GeneralSettings.HeightandWeightUnit.Equals(1))
            {
                if (!string.IsNullOrEmpty(guiradtxtsetupheight.Text.Trim()) && (!string.IsNullOrEmpty(guiradtxtWeight.Text.Trim())))
                {
                    obj.heightAndWeight.heightInInches = (ushort)int.Parse(guiradtxtsetupheight.Text);
                    obj.heightAndWeight.weightInPounds = (ushort)int.Parse(guiradtxtWeight.Text);
                }
            }
        }

        /** This method is called to pass the measurement values to the BizSession.
        */ 
        private void SetBloodPressureValuesInBizSession()
        {
            if (crxMgrObject.GeneralSettings.BloodPressureEntryOptions.Equals(0))
            {
                if ((!string.IsNullOrEmpty(guiradtxtSP.Text.Trim())) && (!string.IsNullOrEmpty(guiradtxtDP.Text.Trim())))
                {
                    obj.bloodPressure.SP.Reading = (ushort)int.Parse(guiradtxtSP.Text.Trim());
                    obj.bloodPressure.DP.Reading = (ushort)int.Parse(guiradtxtDP.Text.Trim());
                }
            }

            if (crxMgrObject.GeneralSettings.BloodPressureEntryOptions.Equals(1))
            {
                if ((!string.IsNullOrEmpty(guiradtxtSP.Text.Trim())) && (!string.IsNullOrEmpty(guiradtxtDP.Text.Trim())))
                {
                    obj.bloodPressure.SP.Reading = (ushort)int.Parse(guiradtxtSP.Text.Trim());
                    obj.bloodPressure.MP.Reading = (ushort)int.Parse(guiradtxtDP.Text.Trim());
                }
            }

            if (crxMgrObject.GeneralSettings.BloodPressureEntryOptions.Equals(2))
            {
                if ((!string.IsNullOrEmpty(guiradtxtDP.Text.Trim())) && (!string.IsNullOrEmpty(guiradtxtSP.Text.Trim())))
                {
                    obj.bloodPressure.MP.Reading = (ushort)int.Parse(guiradtxtSP.Text.Trim());
                    obj.bloodPressure.DP.Reading = (ushort)int.Parse(guiradtxtDP.Text.Trim());
                }
            }
        }

        /** This method is called to pass the measurement values to the BizSession.
        */ 
        private void SetPwvDistanceValuesInBizSession()
        {
            if (crxMgrObject.PwvSettings.PWVDistanceMethod.Equals(0))
            {
                if ((!string.IsNullOrEmpty(guiradtxtCarotid.Text.Trim())) && (!string.IsNullOrEmpty(guiradtxtCuff.Text.Trim())) && (!string.IsNullOrEmpty(guiradtxtFemoralToCuff.Text.Trim())))                
                {
                    // Subtracting.
                    obj.myCarotidDistance.distance = (ushort)int.Parse(guiradtxtCarotid.Text);
                    obj.myCuffDistance.distance = (ushort)int.Parse(guiradtxtCuff.Text);
                    obj.myFemoral2CuffDistance.distance = (ushort)int.Parse(guiradtxtFemoralToCuff.Text);
                    obj.calculatedDistance = (ushort)int.Parse(guiradlblResult.Text);
                }
            }

            if (crxMgrObject.PwvSettings.PWVDistanceMethod.Equals(1))
            {
                if (!string.IsNullOrEmpty(guiradtxtCuff.Text.Trim()))
                {
                    // Direct
                    obj.myPWVDirectDistance.distance = (ushort)int.Parse(guiradtxtCuff.Text);
                    obj.calculatedDistance = (ushort)int.Parse(guiradlblResult.Text);
                }
            }
        }

        /** This event is fire when the user leaves the field where the Carotid value is entered.
        */ 
        private void guiradtxtCarotid_Leave(object sender, EventArgs e)
        {
            EnableCaptureAndCalculatePwvDistance();
        }

        /** This event is fire when the user leaves the field where the Femoral to Cuff value is entered.
        */ 
        private void guiradtxtFemoralToCuff_Leave(object sender, EventArgs e)
        {
            EnableCaptureAndCalculatePwvDistance();
        }

        /** This event is fire when the user clicks on the Cancel button in the GUI.
        */ 
        private void guiradbtnCancel_Click(object sender, EventArgs e)
        {
            try
            {
                // returns the screen to browse mode
                int patientIdInternal = 0;
                int groupId = 0;

                // radRibbonBar.Enabled = true;                
                guiradgrdPatientList.Enabled = true;
                radlblMessage.Text = string.Empty;
                if (mode == currentMode.InsertMode.ToString())
                {
                    // insert mode
                    LoadPatientList();
                }
                else if (mode == currentMode.EditMode.ToString())
                {
                    // edit mode
                    patientIdInternal = int.Parse(radlblpatientinternalnumber.Text);
                    groupId = int.Parse(radlblgroupid.Text);
                    DisplayLastRecord(patientIdInternal, groupId);
                }
                else
                {
                    // reset mode to none
                    mode = currentMode.None.ToString();
                    LoadPatientList();
                }

                mode = currentMode.None.ToString();
                BrowseMode(true);
            }
            catch (Exception ex)
            {
                RadMessageBox.Show(this, ex.Message, oMsgMgr.GetMessage("SYSTEM_ERROR"), MessageBoxButtons.OK, RadMessageIcon.Error);
                CrxLogger oLogObject = CrxLogger.Instance;
                oLogObject.Write(ex.Message);
            }
        }

        /** This method is called when the Serach result is to be bound with the grid view.
         */
        private void BindSearchResults(string patientId, string lastName, string firstName, string gender, string dateOfBirth, string groupName)
        {
            try
            {
                // retrieves data from APPdomain cache, filters as per search criteria and binds it to the grid
                DataSet dsSearch = new DataSet();

                dsSearch = (DataSet)AppDomain.CurrentDomain.GetData("cachePatient"); 
                if (dsSearch.Tables[0].Rows.Count > 0)
                {
                    // creates a dataview for filtering records
                    DataView dvSearch = dsSearch.Tables[0].DefaultView;

                    string searchString = string.Empty;

                    // formulates search string based on criterias given
                    if (!string.IsNullOrEmpty(dateOfBirth))
                    {
                        searchString = "PatientIDExternalReference like '" + patientId + "%' and GroupName like '" + groupName + "%' and LastName like '" + lastName + "%' and FirstName like '" + firstName + "%' and Gender like '" + gender + "%' and " + string.Format(new CultureInfo("en-us").DateTimeFormat, "dateofbirth = #{0:d}#", DateTime.Parse(dateOfBirth));
                    }
                    else
                    {
                        searchString = "PatientIDExternalReference like '" + patientId + "%' and GroupName like '" + groupName + "%' and LastName like '" + lastName + "%' and FirstName like '" + firstName + "%' and Gender like '" + gender + "%'";
                    }

                    // filters record and binds to grid
                    dvSearch.RowFilter = searchString;

                    guiradgrdPatientList.DataSource = dvSearch;
                    guiradlblNumberOfPatients.Text = dvSearch.Count.ToString();
                }
            }
            catch (Exception ex)
            {
                RadMessageBox.Show(this, ex.Message, oMsgMgr.GetMessage("SYSTEM_ERROR"), MessageBoxButtons.OK, RadMessageIcon.Error);
                CrxLogger oLogObject = CrxLogger.Instance;
                oLogObject.Write(ex.Message);
            }
        }

        /** This event is fired on the text changed of the PatientId field.
         */ 
        private void guiradtxtPatientID_TextChanged(object sender, EventArgs e)
        {
            // gets patient records based on inputs given
            if (!IsFieldsBlank(false) && mode == currentMode.SearchMode.ToString())
            {
                GetSearchResults();
            }
        }

        void GetSearchResults()
        {
            try
            {
                string dob = string.Empty, gender = string.Empty, groupname = string.Empty;

                // get date of birth value
                if (guicmbDay.SelectedIndex > 0 && guicmbxMonth.SelectedIndex > 0 && guicmbxYear.SelectedIndex > 0)
                {
                    dob = guicmbxMonth.GetItemText(guicmbDay.SelectedItem) + "/" + guicmbDay.GetItemText(guicmbxMonth.SelectedItem) + "/" + guicmbxYear.GetItemText(guicmbxYear.SelectedItem);
                }

                // get selected item from gender drop down
                if (!string.IsNullOrEmpty(guicmbxGender.Text.Trim()) && !guicmbxGender.Text.Trim().ToLower().Contains(oMsgMgr.GetMessage("SELECT_SMALL")))
                {
                    gender = guicmbxGender.Text.Trim();
                }
                else if (guicmbxGender.SelectedIndex > 0)
                {
                    gender = guicmbxGender.GetItemText(guicmbxGender.SelectedItem.ToString().Trim());
                }

                if (!guicmbGroup.Text.ToLower().Contains(oMsgMgr.GetMessage("SELECT_SMALL")))
                {
                    groupname = guicmbGroup.Text;
                }

                // binds search results to grid
                BindSearchResults(guiradtxtPatientID.Text.Trim(), guiradtxtLastName.Text.Trim(), guiradtxtFirstName.Text.Trim(), gender, dob, groupname);
            }
            catch (Exception ex)
            {
                RadMessageBox.Show(this, ex.Message, oMsgMgr.GetMessage("SYSTEM_ERROR"), MessageBoxButtons.OK, RadMessageIcon.Error);
                CrxLogger oLogObject = CrxLogger.Instance;
                oLogObject.Write(ex.Message);
            }
        }

        /** This event is fired on the cell click of the PateintListGrid view.
          */ 
        private void guiradgrdPatientList_CellClick(object sender, GridViewCellEventArgs e)
        {            
                foreach (GridViewRowInfo row in guiradgrdPatientList.SelectedRows)
                {
                    // gets the selected row patientinternal number and fills demographic details area
                    isSearchReset = false;
                    mode = currentMode.None.ToString();
                    guiradbtnNew.Enabled = true;
                    guiradbtnEdit.Enabled = true;
                    radlblpatientinternalnumber.Text = row.Cells[1].Value.ToString();
                    radlblgroupid.Text = row.Cells[2].Value.ToString();
                    DisplayLastRecord(int.Parse(row.Cells[1].Value.ToString()), int.Parse(radlblgroupid.Text));                    
                }            
        }

        /** This event is fired on the text changed of the FirstName field.
         */ 
        private void guiradtxtFirstName_TextChanged(object sender, EventArgs e)
        {
            // gets patient records based on inputs given for first name
            if (!IsFieldsBlank(false) && mode == currentMode.SearchMode.ToString())
            {
                GetSearchResults();
            }
        }

        /** This event is fired on the text changed of the LastName field.
         */ 
        private void guiradtxtLastName_TextChanged(object sender, EventArgs e)
        {
            // gets patient records based on inputs given for last name
            if (!IsFieldsBlank(true) && mode == currentMode.SearchMode.ToString())
            {
                GetSearchResults();
            }
        }

        /** This event is fired on the selectionchanged of the Group combobox.
         */ 
        private void guicmbGroup_SelectedIndexChanged(object sender, EventArgs e)
        {
            // gets patient records based on inputs given for group name (when selected from drop down)
            if (!IsFieldsBlank(false) && mode == currentMode.SearchMode.ToString())
            {
                GetSearchResults();
            }
        }

        /** This event is fired on the text changed of the Group combobox.
         */ 
        private void guicmbGroup_TextChanged(object sender, EventArgs e)
        {
            // gets patient records based on inputs given for group name (when text changes)
            if (!IsFieldsBlank(false) && mode == currentMode.SearchMode.ToString())
            {
                GetSearchResults();
            }

            guilblGroup.Text = guicmbGroup.Text; 
        }

        /** This event is fired on the selectionchanged of the Gender combobox.
         */ 
        private void guicmbxGender_SelectedIndexChanged(object sender, EventArgs e)
        {
            // gets patient records based on inputs given for gender
            if (!IsFieldsBlank(true) && mode == currentMode.SearchMode.ToString())
            {
                GetSearchResults();
            }

            guilblGender.Text = guicmbxGender.Text;            
        }

        /** This event is fired on the selectionchanged of the Day(of DOB) combobox.
         */ 
        private void guicmbDay_SelectedIndexChanged(object sender, EventArgs e)
        {
            // gets patient records based on inputs given for day drop down (only if month & year values are selected)
            if (!IsFieldsBlank(true) && mode == currentMode.SearchMode.ToString()) 
            {
                GetSearchResults();
            }

            guilblDay.Text = guicmbDay.Text;            
        }

        /** This method is used to check if a field is blank or no while fetching search results.
         */ 
        private bool IsFieldsBlank(bool mandatory)
        {
            bool flag = true;

            // sets flag according to mandatory fields required 
            if (!isSearchReset)
            {
                if (mandatory)
                {
                   flag = (!string.IsNullOrEmpty(guiradtxtLastName.Text.Trim()) ? false : (!string.IsNullOrEmpty(guicmbGroup.Text.Trim()) && !guicmbGroup.Text.ToLower().Trim().Contains(oMsgMgr.GetMessage("SELECT_SMALL"))) ? false : (guicmbDay.SelectedIndex > 0 && guicmbxMonth.SelectedIndex > 0 && guicmbxYear.SelectedIndex > 0) ? false : guicmbxGender.SelectedIndex > 0 ? false : true);                  
                }
                else
                {
                    flag = false;
                }
            }
           
            return flag;
        }

        /** This event fires when enable property of guicmbGroup combo box changes
         */
        private void guicmbGroup_EnabledChanged(object sender, EventArgs e)
        {
            if (guicmbGroup.Enabled)
            {
                // make group combo box visible and labels invisible
                guicmbGroup.Visible = true;
                guicmbGroup.BringToFront();
                guilblGroup.Visible = false;
                guilblGroup.SendToBack();
            }
            else
            {
                // make group combo box invisible and labels visible
                guicmbGroup.Visible = false;
                guicmbGroup.SendToBack();
                guilblGroup.Visible = true;
                guilblGroup.BringToFront();
            }
        }

        /** This event fires when enable property of guicmbday combo box changes
        */
        private void guicmbDay_EnabledChanged(object sender, EventArgs e)
        {
            if (guicmbDay.Enabled)
            {
                // make combo box visible and labels invisible
                guicmbDay.Visible = true;
                guicmbDay.BringToFront();
                guilblDay.Visible = false;
                guilblDay.SendToBack();
            }
            else
            {
                // make combo box invisible and labels visible
                guicmbDay.Visible = false;
                guicmbDay.SendToBack();
                guilblDay.Visible = true;
                guilblDay.BringToFront();
            }
        }

        /** This event fires when enable property of guicmbmonth combo box changes
        */
        private void guicmbxMonth_EnabledChanged(object sender, EventArgs e)
        {
            if (guicmbxMonth.Enabled)
            {
                // makes combo box visible and labels invisible
                guicmbxMonth.Visible = true;
                guicmbxMonth.BringToFront();
                guilblMonth.Visible = false;
                guilblMonth.SendToBack();
            }
            else
            {
                // makes combo box invisible and labels visible
                guicmbxMonth.Visible = false;
                guicmbxMonth.SendToBack();
                guilblMonth.Visible = true;
                guilblMonth.BringToFront();
            }
        }

        /** This event fires when enable property of guicmbYear combo box changes
        */
        private void guicmbxYear_EnabledChanged(object sender, EventArgs e)
        {
            if (guicmbxYear.Enabled)
            {
                // makes combo box visible and labels invisible
                guicmbxYear.Visible = true;
                guicmbxYear.BringToFront();
                guilblYear.Visible = false;
                guilblYear.SendToBack();
            }
            else
            {
                // makes combo box invisible and labels visible
                guicmbxYear.Visible = false;
                guicmbxYear.SendToBack();
                guilblYear.Visible = true;
                guilblYear.BringToFront();
            }
        }

        /** This event fires when enable property of guicmbxGender combo box changes
        */
        private void guicmbxGender_EnabledChanged(object sender, EventArgs e)
        {
            if (guicmbxGender.Enabled)
            {
                // makes combo box visible and labels invisible
                guicmbxGender.Visible = true;
                guicmbxGender.BringToFront();
                guilblGender.Visible = false;
                guilblGender.SendToBack();
            }
            else
            {
                // makes combo box invisible and labels visible
                guicmbxGender.Visible = false;
                guicmbxGender.SendToBack();
                guilblGender.Visible = true;
                guilblGender.BringToFront();
            }
        }

        /** This event is fired when the user tries to change the width of the column of the grid view.
         */
        private void guiradgrdPatientList_ColumnWidthChanging(object sender, ColumnWidthChangingEventArgs e)
        {
            // cancels changing column width
            if (!isCellInitializeWidth)
            {
                e.Cancel = true;
            }
        }

        /** This event is fired when the user tries to right click on the grid view.
        */
        private void guiradgrdPatientList_ContextMenuOpening(object sender, ContextMenuOpeningEventArgs e)
        {
            // suppresses context menu appearing after right click on grid view header
            e.Cancel = true;
        }

        /** This event is fired when the user tries to change the height of the row of the grid view.
        */
        private void guiradgrdPatientList_RowHeightChanging(object sender, RowHeightChangingEventArgs e)
        {
            // cancels changing row height
            e.Cancel = true;
        }

        /** This event is fired when the user clicks tried to click on the OperatorGuide option on the menu bar.
        */
        private void guiradmnuitemOperatorGuide_Click(object sender, EventArgs e)
        {
            try
            {
                if (File.Exists(ConfigurationManager.AppSettings["OperatorGuidePath"].Replace("{culture}", Program.GetCurrentCulture())))
                {
                    System.Diagnostics.Process.Start(ConfigurationManager.AppSettings["OperatorGuidePath"].Replace("{culture}", Program.GetCurrentCulture()));
                }
                else
                {
                    RadMessageBox.Show(this, "PDF file does not exists", oMsgMgr.GetMessage("SYSTEM_ERROR"), MessageBoxButtons.OK, RadMessageIcon.Error);
                }
            }
            catch (Exception ex)
            {
                RadMessageBox.Show(this, ex.Message, oMsgMgr.GetMessage("SYSTEM_ERROR"), MessageBoxButtons.OK, RadMessageIcon.Error);
            }         
        }

        /** This event is fired when the user clicks tried to click on the Service Manual option on the menu bar.
        */
        private void guiradmnuitemServiceManual_Click(object sender, EventArgs e)
        {
            try
            {
                if (File.Exists(ConfigurationManager.AppSettings["ServiceManualPath"].Replace("{culture}", Program.GetCurrentCulture())))
                {
                  System.Diagnostics.Process.Start(ConfigurationManager.AppSettings["ServiceManualPath"].Replace("{culture}", Program.GetCurrentCulture()));
                }
                else
                {
                   RadMessageBox.Show(this, "PDF file does not exists", oMsgMgr.GetMessage("SYSTEM_ERROR"), MessageBoxButtons.OK, RadMessageIcon.Error);
                }
            }
            catch (Exception ex)
            {
                RadMessageBox.Show(this, ex.Message, oMsgMgr.GetMessage("SYSTEM_ERROR"), MessageBoxButtons.OK, RadMessageIcon.Error);                
            }
        }

        /** This event is fired when the user clicks tries to click on the Website option on the menu bar.
       */
        private void guiradmnuitemWebsite_Click(object sender, EventArgs e)
        {
            System.Diagnostics.Process.Start(ConfigurationManager.AppSettings["WebsiteURL"].ToString());
        }

        /** This method is called to Enable the menu controls.
         */ 
        private void EnableMenuBarControls()
        {
            guiradmnuScor.MenuElement.SystemButtons.Visibility = Telerik.WinControls.ElementVisibility.Visible;
            guiradmnuScor.MenuElement.CloseButton.Click += new EventHandler(CloseButton_Click);
            guiradmnuScor.MenuElement.MinimizeButton.Click += new EventHandler(MinimizeButton_Click);
        }


        /** This event is fired when the user clicks on the close button.
         */ 
        private void CloseButton_Click(object sender, EventArgs e)
        {
                this.Close();
        }

        /** This event is fired when the user clicks on the minimze button on the title bar.
         */ 
        private void MinimizeButton_Click(object sender, EventArgs e)
        {
            this.WindowState = FormWindowState.Minimized;
        }

        /** This method is used to set the capture time in the status bar.
         */ 
        private void SetCaptureTimeInStatusBar()
        {
            switch (crxMgrObject.PwvSettings.CaptureTime)
            {
                case 0:
                    radlblCaptureTime.Text = oMsgMgr.GetMessage("GRP_CAPTURE_TIME") + " " + oMsgMgr.GetMessage("RAD_5_SEC");
                    break;
                case 1:
                    radlblCaptureTime.Text = oMsgMgr.GetMessage("GRP_CAPTURE_TIME") + " " + oMsgMgr.GetMessage("RAD_10_SEC");
                    break;
                case 2:
                    radlblCaptureTime.Text = oMsgMgr.GetMessage("GRP_CAPTURE_TIME") + " " + oMsgMgr.GetMessage("RAD_20_SEC");
                    break;
                default:
                    break;
            }
        }

        /** This method is used to populate the session object with the database values.
         */ 
        private void FillSessionObjFromDB()
        {
            // fetch PWV measurement details for patient & populate Biz session object
            DataSet dsPWV = new DataSet();

            dsPWV = dbMagr.GetPWVMeasurementDetails(int.Parse(radlblpatientinternalnumber.Text.Trim()), int.Parse(radlblgroupid.Text.Trim()), bobj);

            if (dsPWV.Tables[0].Rows.Count > 0)
            {
                // populate session object                    
                SettingsProperties.GroupID = int.Parse(radlblgroupid.Text);
                SettingsProperties.PatientInternalNumber = int.Parse(radlblpatientinternalnumber.Text);
                SettingsProperties.PwvCurrentStudyDatetime = dsPWV.Tables[0].Rows[0]["Studydatetime"].ToString();
                obj = (BizPWV)BizSession.Instance().measurement;

                obj.bloodPressureEntryOption = string.IsNullOrEmpty(dsPWV.Tables[0].Rows[0]["bloodpressureentryoption"].ToString()) ? (ushort)0 : ushort.Parse(dsPWV.Tables[0].Rows[0]["bloodpressureentryoption"].ToString());

                switch (obj.bloodPressureEntryOption)
                {
                    case 0:
                        obj.bloodPressure.SP.Reading = ushort.Parse(dsPWV.Tables[0].Rows[0]["SP"].ToString());
                        obj.bloodPressure.DP.Reading = ushort.Parse(dsPWV.Tables[0].Rows[0]["DP"].ToString());
                        break;
                    case 1:
                        obj.bloodPressure.SP.Reading = ushort.Parse(dsPWV.Tables[0].Rows[0]["SP"].ToString());
                        obj.bloodPressure.MP.Reading = ushort.Parse(dsPWV.Tables[0].Rows[0]["MP"].ToString());
                        break;
                    case 2:
                        obj.bloodPressure.MP.Reading = ushort.Parse(dsPWV.Tables[0].Rows[0]["MP"].ToString());
                        obj.bloodPressure.DP.Reading = ushort.Parse(dsPWV.Tables[0].Rows[0]["DP"].ToString());
                        break;
                }

                obj.calculatedDistance = string.IsNullOrEmpty(dsPWV.Tables[0].Rows[0]["PWVDistance"].ToString()) ? (ushort)0 : ushort.Parse(dsPWV.Tables[0].Rows[0]["PWVDistance"].ToString());
                obj.heightAndWeight.heightInCentimetres = string.IsNullOrEmpty(dsPWV.Tables[0].Rows[0]["HeightInCentimetres"].ToString()) ? obj.heightAndWeight.heightInCentimetres : ushort.Parse(dsPWV.Tables[0].Rows[0]["HeightInCentimetres"].ToString());
                obj.heightAndWeight.heightInInches = string.IsNullOrEmpty(dsPWV.Tables[0].Rows[0]["HeightInInches"].ToString()) ? obj.heightAndWeight.heightInInches : ushort.Parse(dsPWV.Tables[0].Rows[0]["HeightInInches"].ToString());
                obj.heightAndWeight.weightInKilograms = string.IsNullOrEmpty(dsPWV.Tables[0].Rows[0]["WeightInKilograms"].ToString()) ? obj.heightAndWeight.weightInKilograms : ushort.Parse(dsPWV.Tables[0].Rows[0]["WeightInKilograms"].ToString());
                obj.heightAndWeight.weightInPounds = string.IsNullOrEmpty(dsPWV.Tables[0].Rows[0]["WeightInPounds"].ToString()) ? obj.heightAndWeight.weightInPounds : ushort.Parse(dsPWV.Tables[0].Rows[0]["WeightInPounds"].ToString());
                obj.notes = dsPWV.Tables[0].Rows[0]["Notes"].ToString();
                obj.operatorId = dsPWV.Tables[0].Rows[0]["Operator"].ToString();
                obj.myCarotidDistance.distance = string.IsNullOrEmpty(dsPWV.Tables[0].Rows[0]["Carotid"].ToString()) ? obj.myCarotidDistance.distance : ushort.Parse(dsPWV.Tables[0].Rows[0]["Carotid"].ToString());
                obj.myCuffDistance.distance = string.IsNullOrEmpty(dsPWV.Tables[0].Rows[0]["Cuff"].ToString()) ? obj.myCuffDistance.distance : ushort.Parse(dsPWV.Tables[0].Rows[0]["Cuff"].ToString());
                obj.myFemoral2CuffDistance.distance = string.IsNullOrEmpty(dsPWV.Tables[0].Rows[0]["FemoraltoCuff"].ToString()) ? obj.myFemoral2CuffDistance.distance : ushort.Parse(dsPWV.Tables[0].Rows[0]["FemoraltoCuff"].ToString());
                obj.myPWVDirectDistance.distance = string.IsNullOrEmpty(dsPWV.Tables[0].Rows[0]["direct"].ToString()) ? obj.myPWVDirectDistance.distance : ushort.Parse(dsPWV.Tables[0].Rows[0]["direct"].ToString());
                obj.heightAndWeight.bodyMassIndex = string.IsNullOrEmpty(dsPWV.Tables[0].Rows[0]["BodyMassIndex"].ToString()) ? (float)0 : float.Parse(dsPWV.Tables[0].Rows[0]["BodyMassIndex"].ToString());
                obj.Validate(); // calculates metric or imperial equivalents for height and weight and the body mass index.
                obj.Calculate(); // It will calculate all the members of the BizPWV class, including distanceMethod and patientAge 
                radtabReport.Enabled = true;

                // filling RHS pwv measurement data on setup screen                
                SetHeightWeightUnits();
                SetBloodPressure();
                SetPwvDistanceMethodAndUnits();
                PerformHeightWeightConversion();

                guiradtxtOperator.Text = dsPWV.Tables[0].Rows[0]["Operator"].ToString();
                guiradtxtMedication.Text = dsPWV.Tables[0].Rows[0]["Notes"].ToString();


                switch (crxMgrObject.GeneralSettings.BloodPressureEntryOptions)
                {
                    case 0: // SP & DP
                        guiradtxtSP.Text = dsPWV.Tables[0].Rows[0]["SP"].ToString().Equals("9999") ? string.Empty : dsPWV.Tables[0].Rows[0]["SP"].ToString();
                        guiradtxtDP.Text = dsPWV.Tables[0].Rows[0]["DP"].ToString().Equals("9999") ? string.Empty : dsPWV.Tables[0].Rows[0]["DP"].ToString();
                        break;
                    case 1: // SP & MP
                        guiradtxtSP.Text = dsPWV.Tables[0].Rows[0]["SP"].ToString().Equals("9999") ? string.Empty : dsPWV.Tables[0].Rows[0]["SP"].ToString();
                        guiradtxtDP.Text = dsPWV.Tables[0].Rows[0]["MP"].ToString().Equals("9999") ? string.Empty : dsPWV.Tables[0].Rows[0]["MP"].ToString();
                        break;
                    case 2: // MP & DP
                        guiradtxtSP.Text = dsPWV.Tables[0].Rows[0]["MP"].ToString().Equals("9999") ? string.Empty : dsPWV.Tables[0].Rows[0]["MP"].ToString();
                        guiradtxtDP.Text = dsPWV.Tables[0].Rows[0]["DP"].ToString().Equals("9999") ? string.Empty : dsPWV.Tables[0].Rows[0]["DP"].ToString();
                        break;
                    default:
                        guiradtxtSP.Text = string.Empty;
                        guiradtxtDP.Text = string.Empty;
                        break;
                }
                guiradtxtCuff.Text = dsPWV.Tables[0].Rows[0]["Carotid"].ToString().Equals("9999") ? dsPWV.Tables[0].Rows[0]["direct"].ToString() : dsPWV.Tables[0].Rows[0]["Cuff"].ToString().Equals("9999") ? string.Empty : dsPWV.Tables[0].Rows[0]["Cuff"].ToString();
                guiradtxtCarotid.Text = dsPWV.Tables[0].Rows[0]["Carotid"].ToString().Equals("9999") ? string.Empty : dsPWV.Tables[0].Rows[0]["Carotid"].ToString();
                guiradtxtFemoralToCuff.Text = dsPWV.Tables[0].Rows[0]["FemoraltoCuff"].ToString().Equals("9999") ? string.Empty : dsPWV.Tables[0].Rows[0]["FemoraltoCuff"].ToString();
                guiradlblResult.Text = dsPWV.Tables[0].Rows[0]["PWVDistance"].ToString();
            }
            else
            {
                // disable report and capture tab if measurement data not available for patient
                radtabReport.Enabled = false;
                radtabCapture.Enabled = false;

                // resets PWV fields on setup screen RHS
                ResetPatientMeasurementFields();
            }
        }

        /** This method is used calculate the conversion for height and weight.
         */ 
        private void PerformHeightWeightConversion()
        {
             int heightInInches = 0, heigthInFeet = 0;
                switch (crxMgrObject.GeneralSettings.HeightandWeightUnit)
                {
                    case 0:

                        // 0.3937007874
                        if (obj.heightAndWeight.heightInCentimetres.ToString() == "9999")
                        {
                            // convert height in centimeters to feet & inches
                            guiradtxtsetupheight.Text = Math.Round(double.Parse(obj.heightAndWeight.heightInInches.ToString()) * 2.54, MidpointRounding.ToEven).ToString();
                        }
                        else
                        {
                            // convert height in inches to feet & inches
                            guiradtxtsetupheight.Text = obj.heightAndWeight.heightInCentimetres.ToString();
                        }

                        if (obj.heightAndWeight.weightInKilograms.ToString() == "9999")
                        {
                            guiradtxtWeight.Text = Math.Round(double.Parse(obj.heightAndWeight.weightInPounds.ToString()) * 0.45359237, MidpointRounding.ToEven).ToString();
                        }
                        else
                        {
                            guiradtxtWeight.Text = obj.heightAndWeight.weightInKilograms.ToString();
                        }

                        break;
                    case 1:

                        // 0.3937007874
                        if (obj.heightAndWeight.heightInInches.ToString() == "9999")
                        {
                            // convert height in centimeters to feet & inches
                            double value = Math.Round(double.Parse(obj.heightAndWeight.heightInCentimetres.ToString()) * 0.3937007874, MidpointRounding.ToEven);
                            heightInInches = int.Parse(value.ToString()) % 12;
                            heigthInFeet = int.Parse(value.ToString()) / 12;
                        }
                        else
                        {
                            // convert height in inches to feet & inches
                            heightInInches = int.Parse(obj.heightAndWeight.heightInInches.ToString()) % 12;
                            heigthInFeet = int.Parse(obj.heightAndWeight.heightInInches.ToString()) / 12;
                        }

                        guiradtxtsetupheight.Text = heigthInFeet.ToString();
                        guiradtxtImperialHeight.Text = heightInInches.ToString();

                        if (obj.heightAndWeight.weightInPounds.ToString() == "9999")
                        {
                            guiradtxtWeight.Text = Math.Round(double.Parse(obj.heightAndWeight.weightInKilograms.ToString()) * 2.20462262, MidpointRounding.ToEven).ToString();
                        }
                        else
                        {
                            guiradtxtWeight.Text = obj.heightAndWeight.weightInPounds.ToString();
                        }

                        break;
                }
            }

        }
    }
