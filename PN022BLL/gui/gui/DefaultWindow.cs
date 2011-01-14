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
     * @class Class for Default Window when the application loads.
     * @brief This class will handle displaying of the default window controls.It will also check for multiple instances of the application,exception handling and logging of events.
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
        
        const string BackupFileExt = ".bak"; // vibhuti: to be placed in common file as global variable
        static int count = 0;
        
        CrxConfigManager crxMgrObject = CrxConfigManager.Instance;
        
        CrxDBManager dbMagr;
        string currentpath = string.Empty; // vibhuti : to be placed in common file as global variable
        
        string dbOperation = string.Empty; // vibhuti: to be placed in common file as global variable
                        
        // private delegate void ThreadException(Exception ex);
       // private event ThreadException OnThreadExceptionEvent;        
        public static event EventHandler OnRestoreCompleteSuccess;

        // Event to indicate completion of database backup process
        private event EventHandler OnDBBackupAndRestoreCompleteEvent;  

        private delegate void DisplayMessageBoxDelegate(string message, Exception ex);
       
        #region Global declarations
                     
        bool isDirectClose; // Flag set to check if there are multiple instances of the application.        
        bool isFormDataChanged = false; // flag to check if any form data is changed before closing the form
        
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
                // initialize class level variables                
                isDirectClose = false;

                CrxLogger oLogObject = CrxLogger.Instance;
                oLogObject.Write("check for instance");

                // Logic to check multiple instances of the application.                 
                if (IsProcessOpen(oMsgMgr.GetMessage("APP_NAME")))
                {
                    oLogObject.Write("instance exists");
                    isDirectClose = true;
                    DialogResult ds = RadMessageBox.Show(this, oMsgMgr.GetMessage("APP_MSG"), oMsgMgr.GetMessage("EXEC_ERROR"), MessageBoxButtons.OK, RadMessageIcon.Error);
                    this.Close();
                    Process.GetCurrentProcess().Kill();
                    return;
                }

                oLogObject.Write("scor loading.......");
                crxMgrObject.GetGeneralUserSettings();

                // set the global culture variable with value from scor.config & pass it to current culture
                SettingsProperties.gCI = string.IsNullOrEmpty(crxMgrObject.GeneralSettings.CultureInfo) ? ConfigurationManager.AppSettings["DefaultCulture"].ToString() : crxMgrObject.GeneralSettings.CultureInfo.Trim();
                Thread.CurrentThread.CurrentCulture = new CultureInfo(SettingsProperties.gCI); // allows to format the appearance of numbers, dates..etc
                Thread.CurrentThread.CurrentUICulture = new CultureInfo(SettingsProperties.gCI); // to work with resource files that are dynamically loaded in the windows form
                              
                currentpath = Directory.GetCurrentDirectory();
                if (currentpath.Equals(@"g:\Sprint 5\Scor\gui\gui\bin\debug", StringComparison.CurrentCultureIgnoreCase))
                { 
                    // sjdsac
                }

                // crxMgrObject.GeneralSettings = gnrlSettingsStruct;
                if (string.IsNullOrEmpty(crxMgrObject.GeneralSettings.ServerName))
                {
                    crxMgrObject.GeneralSettings.ServerName = SystemInformation.ComputerName + @"\SQLEXPRESS";
                    oLogObject.Write(oMsgMgr.GetMessage("SQL_SERVER_CHANGED_TO_LOCAL"));
                }

                if (string.IsNullOrEmpty(crxMgrObject.GeneralSettings.SourceData))
                {
                    crxMgrObject.GeneralSettings.SourceData = "SQLCLIENT";
                    oLogObject.Write(oMsgMgr.GetMessage("SQL_SERVER_CHANGED_TO_DEFAULT"));
                }
               
                int result = 0;
                dbMagr = CrxDBManager.Instance;
                result = dbMagr.SetConnection(crxMgrObject.GeneralSettings.ServerName, crxMgrObject.GeneralSettings.SourceData);

                // log message on connection status.
                if (result.Equals(0))
                {                   
                    oLogObject.Write(oMsgMgr.GetMessage("SQL_SERVER_CONNECTED") + crxMgrObject.GeneralSettings.ServerName);
                    crxMgrObject.SetGeneralUserSettings(crxMgrObject.GeneralSettings);
                }

                if (result.Equals(1))
                {
                    // CrxLogger oLogObject = CrxLogger.Instance;
                    oLogObject.Write(oMsgMgr.GetMessage("SQL_SERVER_CONN_FAILED") + crxMgrObject.GeneralSettings.ServerName);
                    SQLInstanceList frmObject = new SQLInstanceList();
                    frmObject.ShowDialog();
                    frmObject.ShowInTaskbar = false;
                }
                
                if (SQLInstanceList.IsCancel == 1)
                {
                    SQLInstanceList.IsCancel = 0;
                    this.Close();
                    Process.GetCurrentProcess().Kill();
                }
                
                    InitializeComponent();

                    // Set the text for  Capture Tab form controls
                    SetTextForRibbionControl();

                    // Initialize setup screen
                    InitializeSetupScreen();                    
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
        
        /**This method is called to set the text for the controls in the ribbon bar.The text is read from the resource file.
        */  
        private void SetTextForRibbionControl()
        {
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
        
        /**This method is invoked on the click of the Exit button under System menu.
         * It will close the main window.
         */
        private void radButtonElementExit_Click(object sender, EventArgs e)
        {  
            // Close the application on click of Exit button under System menu.
            this.Close();                    
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
                // fills day, month & year, loads group names & patient list
                radpgTabCollection.SelectedPage = guiradgrpbxPwvDistanceMethod; 
               
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

                // set waiting bar
                guiWaitingStatusBar.WaitingStep = 10;
                guiWaitingStatusBar.WaitingSpeed = 50;
                guiWaitingStatusBar.Visible = false;

                OnDBBackupAndRestoreCompleteEvent += new EventHandler(DisplayStatusComplete);                
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

                CrxLogger oLogObject = CrxLogger.Instance;
                oLogObject.Write("instances = " + count.ToString());
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

        /**This method is called when the user clicks on the cross button during the capture.
        */  
        private void radbtnCross_Click(object sender, EventArgs e)
        {           
            CrossButtonAction();
        }                    
     
        /** This method loads setup form
         * */
        void InitializeSetupScreen()
        {
            // if (InvokeRequired)
            // {
            //    this.Invoke(new ReloadForm(InitializeSetupScreen));
            //    return;
            // }
            if (!guiradgrpbxPwvDistanceMethod.Enabled)
            {
                return;
            }
          
            // open setup form under setup tab
            if (SettingsProperties.setupChildForm != null)
            {
                SettingsProperties.setupChildForm.Close();
                SettingsProperties.setupChildForm = null;
            }
            
            SettingsProperties.setupChildForm = new Setup(this);
            SettingsProperties.setupChildForm.TopLevel = false;
            SettingsProperties.setupChildForm.Dock = DockStyle.Fill;
            SettingsProperties.setupChildForm.FormBorderStyle = System.Windows.Forms.FormBorderStyle.None;
            
            // adds report form under parent window control
            var page = radpgTabCollection.Pages[0];
            SettingsProperties.setupChildForm.Parent = page;
            page.Controls.Add(SettingsProperties.setupChildForm);
            SettingsProperties.setupChildForm.Show(); 
        }

         /** This method is used to start the capture for tonometer waveform.
        */ 
        private void StartCarotidTonometerCapture()
        {
            // Start the capture of data points.
            BizSession.Instance().StartCapture();
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
            // if (radpgTabCollection.SelectedPage.Text.Equals(oMsgMgr.GetMessage("TAB_CAPTURE")))
            // {
            //    if (e.KeyCode == Keys.Escape)
            //    {
            //        CrossButtonAction();
            //    }                
            // }
        }

        private void timer3_Tick(object sender, EventArgs e)
        {
            count++;
            radlblCaptureTime.Text = count.ToString();
        }

        /** This method disables tab other than the parameter passed
         */ 
        private void DisableTabs(string currentTab)
        {
            // disables all the tabs except the currentTab
            for (int pageCount = 0; pageCount < radpgTabCollection.Pages.Count; pageCount++)
            {
                if (radpgTabCollection.Pages[pageCount].Text.ToLower() != currentTab)
                {
                    radpgTabCollection.Pages[pageCount].Enabled = false;
                }
            }
        }    
      
        /** This event is fired when the user clicks tried to click on the OperatorGuide option on the menu bar.
        */
        private void guiradmnuitemOperatorGuide_Click(object sender, EventArgs e)
        {
            try
            {
                if (File.Exists(ConfigurationManager.AppSettings["OperatorGuidePath"].Replace("{culture}", Program.GetCurrentCulture())))
                {
                    System.Diagnostics.Process.Start(Path.GetFullPath(ConfigurationManager.AppSettings["OperatorGuidePath"].Replace("{culture}", Program.GetCurrentCulture())));
                }
                else
                {
                    RadMessageBox.Show(this, oMsgMgr.GetMessage("PDF_FILE_ERROR"), oMsgMgr.GetMessage("SYSTEM_ERROR"), MessageBoxButtons.OK, RadMessageIcon.Error);
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
                  System.Diagnostics.Process.Start(Path.GetFullPath(ConfigurationManager.AppSettings["ServiceManualPath"].Replace("{culture}", Program.GetCurrentCulture())));
                }
                else
                {
                    RadMessageBox.Show(this, oMsgMgr.GetMessage("PDF_FILE_ERROR"), oMsgMgr.GetMessage("SYSTEM_ERROR"), MessageBoxButtons.OK, RadMessageIcon.Error);
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
            System.Diagnostics.Process.Start(ConfigurationManager.AppSettings["SupportURL"].ToString());
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

        /**This method is invoked when Settings button under System tab is clicked. 
         * It opens setting window
         */ 
        private void guiradmnuSettings_Click(object sender, EventArgs e)
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

        /** This event fires on backup button click of menu bar.
         * Open dialog box to select location to save database backup
         * */
        private void guiradmenuBackup_Click(object sender, EventArgs e)
        {
            try
            {
                radlblMessage.Text = string.Empty;

                // opens folder dialog box to select location
                saveFileDialog1.FileName = ConfigurationManager.AppSettings["DBDefaultFileName"].ToString() + ConfigurationManager.AppSettings["DBVersionNumber"].ToString() + BackupFileExt;
                saveFileDialog1.Title = oMsgMgr.GetMessage("BACKUP_TITLE");
                DialogResult result = saveFileDialog1.ShowDialog(); // folderBrowserDialog1.ShowDialog()

                if (result == DialogResult.OK)
                {
                    Directory.SetCurrentDirectory(currentpath);
                    dbOperation = oMsgMgr.GetMessage("BACKUP_TITLE");
                    
                    // save backup operation started on separate thread
                    Thread startDBBackup = new Thread(SaveBackupFile);
                    startDBBackup.Start();

                    // start waiting progress bar on main thread
                    guiWaitingStatusBar.Visible = true;
                    guiWaitingStatusBar.StartWaiting();

                    // disable menu & tab page while backup is on
                    guiradmnuScor.Enabled = false;
                    radpgTabCollection.Enabled = false;
                }                
            }
            catch (CrxException ex)
            {
                RadMessageBox.Show(this, oMsgMgr.GetMessage(ex.ErrorString), oMsgMgr.GetMessage("SYSTEM_ERROR"), MessageBoxButtons.OK, RadMessageIcon.Error);
                CrxLogger oLogObject = CrxLogger.Instance;
                oLogObject.Write(ex.ErrorString);
                radlblMessage.Text = string.Empty;
            }
            catch (Exception ex)
            {
                RadMessageBox.Show(this, ex.Message, oMsgMgr.GetMessage("SYSTEM_ERROR"), MessageBoxButtons.OK, RadMessageIcon.Error);
                CrxLogger oLogObject = CrxLogger.Instance;
                oLogObject.Write(ex.Message);
                radlblMessage.Text = string.Empty;
            }
        }
      
        /** This method truncates invalid file extensions and saves backup of database to location specified
         * */
        private void SaveBackupFile()
        {
            try
            {
                string path = saveFileDialog1.FileName;

                // int success = 0;
                // set current directory path for resource file
                Directory.SetCurrentDirectory(currentpath); // shri: make part of global class

                // log backup start process
                CrxLogger oLogObject = CrxLogger.Instance;
                oLogObject.Write(oMsgMgr.GetMessage("BACKUP_PROGRESS"));

                DoBackup(path);               
            }
            catch (CrxException ex)
            {
                if (this.InvokeRequired)
                {
                    dbOperation = oMsgMgr.GetMessage("BACKUP_FAIL");
                    OnDBBackupAndRestoreCompleteEvent.Invoke(this, new EventArgs());

                    DisplayMessageBoxDelegate messageBox = new DisplayMessageBoxDelegate(DisplayErrorMessage);
                    this.Invoke(messageBox, oMsgMgr.GetMessage(ex.ErrorString), ex);                   
                }

                CrxLogger oLogObject = CrxLogger.Instance;
                oLogObject.Write(ex.ErrorString);
            }
            catch (Exception ex)
            {
                if (this.InvokeRequired)
                {
                    dbOperation = oMsgMgr.GetMessage("BACKUP_FAIL");
                    OnDBBackupAndRestoreCompleteEvent.Invoke(this, new EventArgs());

                    DisplayMessageBoxDelegate messageBox = new DisplayMessageBoxDelegate(DisplayErrorMessage);
                    this.Invoke(messageBox, ex.Message, ex);                   
                }

                CrxLogger oLogObject = CrxLogger.Instance;
                oLogObject.Write(ex.Message);
            }            
        }

        /** This method saves database backup at selected location
         * */
        void DoBackup(string path)
        {
            int success = 0;

            // save backup at selected location in shared folder
            if (!Path.GetExtension(path).ToLower().Equals(BackupFileExt))
            {
                success = dbMagr.DatabaseBackup(path.Contains(":\\") ? path.Replace(path.Substring(0, path.IndexOf("\\")), "\\\\" + SystemInformation.ComputerName) + BackupFileExt : path + BackupFileExt); // folderBrowserDialog1.SelectedPath);
            }
            else
            {
                success = dbMagr.DatabaseBackup(path.Contains(":\\") ? path.Replace(path.Substring(0, path.IndexOf("\\")), "\\\\" + SystemInformation.ComputerName) : path); // folderBrowserDialog1.SelectedPath);
            }

            // on backup success invoke event to display status message
            if (success == 0)
            {
                OnDBBackupAndRestoreCompleteEvent.Invoke(this, new EventArgs());
            }
        }

        /** This event shows backup & restore status messages after its completion & stops waiting bar
         * */
        private void DisplayStatusComplete(object sender, EventArgs e)
        {
            // if invoked from other thread call the appropriate method
            if (InvokeRequired)
            {
                this.Invoke(new EventHandler(DisplayStatusComplete));
                return;
            }

            // end waiting status bar
            guiWaitingStatusBar.EndWaiting();
            guiWaitingStatusBar.Visible = false;

            // enable menu & tab page controls
            guiradmnuScor.Enabled = true;
            radpgTabCollection.Enabled = true;

            // show status message for restore & backup
            if (dbOperation.Equals(oMsgMgr.GetMessage("BACKUP_TITLE")))
            {
                radlblMessage.Text = oMsgMgr.GetMessage("BACKUP_DONE");

                // log the message
                CrxLogger oLogObject = CrxLogger.Instance;
                oLogObject.Write(oMsgMgr.GetMessage("BACKUP_DONE"));
            }
            else if (dbOperation.Equals(oMsgMgr.GetMessage("RESTORE_TITLE")))
            {
                radlblMessage.Text = oMsgMgr.GetMessage("RESTORE_DONE");
                ////this.Refresh();
                ////InitializeSetupScreen();
                ////Setup d = new Setup(this);
                ////d.LoadSetupScreen();
                ////d.Refresh();

                // log the message
                CrxLogger oLogObject = CrxLogger.Instance;
                oLogObject.Write(oMsgMgr.GetMessage("RESTORE_DONE"));
            }           
        }

        /**This method is called when the Setup, Capture or Report tab is selected.
       */ 
        private void radpgTabCollection_SelectedPageChanged(object sender, EventArgs e)
        {
            try
            {
                guiradmnuitemSettings.Enabled = true;

                // read the coms port and simulation type.
                if (radpgTabCollection.SelectedPage.Text.Equals(oMsgMgr.GetMessage("TAB_CAPTURE")))
                {
                    if (!radtabCapture.Enabled)
                    {
                        return;
                    }
                    
                    if (SettingsProperties.captureChildForm != null)
                    {
                        SettingsProperties.captureChildForm.Close();
                       //// SettingsProperties.captureChildForm.Dispose();
                    }

                    SettingsProperties.captureChildForm = new Capture(this);
                    SettingsProperties.captureChildForm.TopLevel = false;
                    SettingsProperties.captureChildForm.Dock = DockStyle.Fill;
                    SettingsProperties.captureChildForm.FormBorderStyle = System.Windows.Forms.FormBorderStyle.None;

                    // adds report form under parent window control
                    var page = radpgTabCollection.Pages[1];
                    SettingsProperties.captureChildForm.Parent = page;
                    page.Controls.Clear();
                    
                    page.Controls.Add(SettingsProperties.captureChildForm);
                    SettingsProperties.captureChildForm.Show();
                }
                else if (radpgTabCollection.SelectedPage.Text.Equals(oMsgMgr.GetMessage("TAB_REPORT")))
                {
                    if (!radtabReport.Enabled)
                    {
                        return;
                    }

                    // open report form under report tab
                    if (SettingsProperties.reportChildForm != null)
                    {
                        SettingsProperties.reportChildForm.Close();
                        SettingsProperties.reportChildForm.Dispose();
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
                    radtabCapture.Enabled = false;
                }
                else if (radpgTabCollection.SelectedPage.Text.Equals(oMsgMgr.GetMessage("TAB_SETUP")))
                {
                    // InitializeSetupScreen(); 
                    if (SettingsProperties.hasMeasurementDetails)
                    {
                        radtabCapture.Enabled = true;
                    }
                }
            }
            catch (Exception ex)
            {
                RadMessageBox.Show(this, ex.Message, oMsgMgr.GetMessage("SYSTEM_ERROR"), MessageBoxButtons.OK, RadMessageIcon.Error);
                CrxLogger oLogObject = CrxLogger.Instance;
                oLogObject.Write(ex.Message);
            }
        }

        /** This event fires when restore button is clicked on menu bar
         * */
        private void guiradmenuRestore_Click(object sender, EventArgs e)
        {
            try
            {
                radlblMessage.Text = string.Empty;

                // prompt user before restoring backup
                DialogResult dg = RadMessageBox.Show(this, oMsgMgr.GetMessage("RESTORE_MSG"), oMsgMgr.GetMessage("APPLICATION_MESSAGE"), MessageBoxButtons.YesNo, RadMessageIcon.Info);

                if (dg == DialogResult.Yes)
                {
                    // continue with restore backup
                    // sets title for dialog box
                    openFileDialog1.Title = oMsgMgr.GetMessage("RESTORE_TITLE");
                    DialogResult result = openFileDialog1.ShowDialog();

                    if (result == DialogResult.OK)
                    {
                        Directory.SetCurrentDirectory(currentpath);

                        // check for .bak file extension and restore backup
                        if (Path.GetExtension(openFileDialog1.FileName).ToLower().Equals(BackupFileExt))
                        {
                            // restore backup operation on separate thread
                            Thread startDBRestore = new Thread(RestoreBackupFile);
                            startDBRestore.Start();

                            // start waiting progress bar on main thread
                            guiWaitingStatusBar.Visible = true;
                            guiWaitingStatusBar.StartWaiting();

                            // disable menu & tab page while restore is on
                            guiradmnuScor.Enabled = false;
                            radpgTabCollection.Enabled = false;
                        }
                        else
                        {
                            RadMessageBox.Show(this, oMsgMgr.GetMessage("RESTORE_FILE_MSG"), oMsgMgr.GetMessage("EXEC_ERROR"), MessageBoxButtons.OK, RadMessageIcon.Error);
                        }
                    }
                }
            }
            catch (CrxException ex)
            {
                RadMessageBox.Show(this, oMsgMgr.GetMessage(ex.ErrorString), oMsgMgr.GetMessage("SYSTEM_ERROR"), MessageBoxButtons.OK, RadMessageIcon.Error);
                CrxLogger oLogObject = CrxLogger.Instance;
                oLogObject.Write(ex.ErrorString);
                radlblMessage.Text = string.Empty;
            }
            catch (Exception ex)
            {
                RadMessageBox.Show(this, ex.Message, oMsgMgr.GetMessage("SYSTEM_ERROR"), MessageBoxButtons.OK, RadMessageIcon.Error);
                CrxLogger oLogObject = CrxLogger.Instance;
                oLogObject.Write(ex.Message);
                radlblMessage.Text = string.Empty;
            }
        }

        /** This method restores databse backup
         * */
        private void RestoreBackupFile()
        {
            try
            {
                string path = openFileDialog1.FileName;
                int success = 0;

                // set current directory for resource file
                Directory.SetCurrentDirectory(currentpath); // shri: make part of global class
                dbOperation = oMsgMgr.GetMessage("RESTORE_TITLE");
                        
                // log message for restore started
                CrxLogger oLogObject = CrxLogger.Instance;
                oLogObject.Write(oMsgMgr.GetMessage("RESTORE_PROGRESS"));

                // restore database
                success = dbMagr.DatabaseRestore(path.Contains(":\\") ? path.Replace(path.Substring(0, path.IndexOf("\\")), "\\\\" + SystemInformation.ComputerName) : path);

                // on success of restore invoke event to show message
                if (success == 0)
                {                  
                  // Invoke methods to stop progressbasr & reload setup screen
                   OnRestoreCompleteSuccess.Invoke(this, new EventArgs());
                   OnDBBackupAndRestoreCompleteEvent.Invoke(this, new EventArgs());
                }
            }
            catch (CrxException ex)
            {
                if (this.InvokeRequired)
                {
                    dbOperation = oMsgMgr.GetMessage("RESTORE_FAIL");
                    OnDBBackupAndRestoreCompleteEvent.Invoke(this, new EventArgs());

                    DisplayMessageBoxDelegate messageBox = new DisplayMessageBoxDelegate(DisplayErrorMessage);
                    this.Invoke(messageBox, oMsgMgr.GetMessage(ex.ErrorString), ex);
                }
                
                CrxLogger oLogObject = CrxLogger.Instance;
                oLogObject.Write(ex.ErrorString);               
            }
            catch (Exception ex)
            {
                if (this.InvokeRequired)
                {
                    dbOperation = oMsgMgr.GetMessage("RESTORE_FAIL");
                    OnDBBackupAndRestoreCompleteEvent.Invoke(this, new EventArgs());

                    // ExceptionHandler handle = new ExceptionHandler(GUIExceptionHandler.HandleException);
                    // this.Invoke(handle,ex,this);
                    // GUIExceptionHandler.HandleException(ex, this);
                    DisplayMessageBoxDelegate messageBox = new DisplayMessageBoxDelegate(DisplayErrorMessage);
                    this.Invoke(messageBox, ex.Message, ex);                   
                }
                
                CrxLogger oLogObject = CrxLogger.Instance;
                oLogObject.Write(ex.Message);
            }
        }

        /**This event fires when Atcor Homepage menu item is selected
      */
        private void guiradmenuahomepage_Click(object sender, EventArgs e)
        {
            System.Diagnostics.Process.Start(ConfigurationManager.AppSettings["AtcorHomepage"].ToString());
        }

        /**This method will display the error message using the message box.
       */
        private void DisplayErrorMessage(string errorMessage, Exception ex)
        {
            if (ex.GetType() == typeof(CrxException))
            {
                RadMessageBox.Show(this, errorMessage, oMsgMgr.GetMessage("SYSTEM_ERROR"), MessageBoxButtons.OK, RadMessageIcon.Error);
            }
            else
            {
                RadMessageBox.Show(this, oMsgMgr.GetMessage(errorMessage), oMsgMgr.GetMessage("SYSTEM_ERROR"), MessageBoxButtons.OK, RadMessageIcon.Error);
            }
        }
        }
    }
