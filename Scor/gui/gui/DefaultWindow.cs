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
        string serverNameString = string.Empty;
        CrxConfigManager crxMgrObject = CrxConfigManager.Instance;
        
        CrxDBManager dbMagr;
        string currentpath = string.Empty; // vibhuti : to be placed in common file as global variable
        string dbOperation = string.Empty; // vibhuti: to be placed in common file as global variable
        
        // private delegate void ThreadException(Exception ex);
       // private event ThreadException OnThreadExceptionEvent;  
        public delegate void InitializationMessage(string message);

        public static event EventHandler OnRestoreCompleteSuccess;

        public static event EventHandler OnReportTabClick;

        public static event InitializationMessage OnInitializationProcess;

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
                // launches splash screen
                SplashScreen splsh = new SplashScreen();
                splsh.Show();
                splsh.Update();
                            
                isDirectClose = false;
                CrxLogger oLogObject = CrxLogger.Instance;
               
                // Logic to check multiple instances of the application.                 
                if (IsProcessOpen(oMsgMgr.GetMessage("APP_NAME")))
                {
                    // writes messages on splash screen by invoking OnInitializationProcess
                    OnInitializationProcess.Invoke(oMsgMgr.GetMessage("EXEC_ERROR"));
                    OnInitializationProcess.Invoke(oMsgMgr.GetMessage("BTN_EXIT"));
                    oLogObject.Write("instance exists");
                    isDirectClose = true;
                    DialogResult ds = RadMessageBox.Show(this, oMsgMgr.GetMessage("APP_MSG"), oMsgMgr.GetMessage("EXEC_ERROR"), MessageBoxButtons.OK, RadMessageIcon.Error);
                    this.Close();
                    Process.GetCurrentProcess().Kill();
                    return;
                }
                                
                crxMgrObject.GetGeneralUserSettings();
                if (string.IsNullOrEmpty(crxMgrObject.GeneralSettings.StartupScreen))
                {
                    // writes messages on splash screen by invoking OnInitializationProcess
                    OnInitializationProcess.Invoke(oMsgMgr.GetMessage("SYSTEM_ERROR"));
                    OnInitializationProcess.Invoke(oMsgMgr.GetMessage("BTN_EXIT"));
                    RadMessageBox.Show(this, oMsgMgr.GetMessage("CRX_ERR_FILE_CORRUPT"), oMsgMgr.GetMessage("SYSTEM_ERROR"), MessageBoxButtons.OK, RadMessageIcon.Error);
                    oLogObject.Write(oMsgMgr.GetMessage("CRX_ERR_FILE_CORRUPT"));
                    this.Close();
                    Process.GetCurrentProcess().Kill();
                    return;
                }
                              
                currentpath = Directory.GetCurrentDirectory();
               
                if (string.IsNullOrEmpty(crxMgrObject.GeneralSettings.MachineName))
                {
                    crxMgrObject.GeneralSettings.MachineName = SystemInformation.ComputerName;
                    oLogObject.Write(oMsgMgr.GetMessage("SQL_SERVER_CHANGED_TO_LOCAL"));
                }
               
                if (string.IsNullOrEmpty(crxMgrObject.GeneralSettings.SourceData))
                {
                    crxMgrObject.GeneralSettings.SourceData = "SQLCLIENT";
                    oLogObject.Write(oMsgMgr.GetMessage("SQL_SERVER_CHANGED_TO_DEFAULT"));
                }

                serverNameString = SettingsProperties.ServerNameString();
                int result = 0;
                dbMagr = CrxDBManager.Instance;
                result = dbMagr.SetConnection(serverNameString, crxMgrObject.GeneralSettings.SourceData.Trim());
               
                // log message on connection status.
                if (result.Equals(0))
                {
                    oLogObject.Write(oMsgMgr.GetMessage("SQL_SERVER_CONNECTED") + serverNameString);
                    crxMgrObject.SetGeneralUserSettings(crxMgrObject.GeneralSettings);

                    OnInitializationProcess.Invoke(oMsgMgr.GetMessage("SPLASH_SQL_CONN") + " " + serverNameString);
                }

                if (result.Equals(1))
                {
                    OnInitializationProcess.Invoke(oMsgMgr.GetMessage("SQL_SERVER_CONN_FAILED") + " " + serverNameString);
                    OnInitializationProcess.Invoke(oMsgMgr.GetMessage("BTN_EXIT"));
                    oLogObject.Write(oMsgMgr.GetMessage("SQL_SERVER_CONN_FAILED") + serverNameString);

                    SQLInstanceList frmObject = new SQLInstanceList();
                    frmObject.ShowInTaskbar = false;
                    frmObject.ShowDialog();                    
                }
                
                if (SQLInstanceList.IsCancel == 1)
                {
                    OnInitializationProcess.Invoke(oMsgMgr.GetMessage("BTN_EXIT"));
                    SQLInstanceList.IsCancel = 0;
                    this.Close();
                    Process.GetCurrentProcess().Kill();
                    return;
                }

                    serverNameString = SettingsProperties.ServerNameString();
                    InitializeComponent();
                    
                    // Set the text for  Capture Tab form controls
                    SetTextForRibbionControl();
                    
                    SetStartUpModeEnvironmentScreen(); 
                    
                    Report.OnReportScreenLoadComplere += new EventHandler(StopWaitingBar);

                    // Report.StartWaiting += new EventHandler(StartWaiting);
                    Report.OnReportInitializationProcess += new Report.InitializationMessage(DisplayMessage);
                    
                    // hide splash screen after initialization process
                    splsh.Hide();                   
            }         
            catch (Exception ex)
            {
                // show error type on splash screen, error on message box & quit application
                OnInitializationProcess.Invoke(oMsgMgr.GetMessage("SYSTEM_ERROR"));
                OnInitializationProcess.Invoke(oMsgMgr.GetMessage("BTN_EXIT"));
                GUIExceptionHandler.HandleException(ex, this);               
                this.Close();
                Process.GetCurrentProcess().Kill();
                return;
            }

            /* catch (CrxException crxex)
            {
                // show error type on splash screen, error on message box & quit application
                OnInitializationProcess.Invoke(oMsgMgr.GetMessage("SYSTEM_ERROR"));
                OnInitializationProcess.Invoke(oMsgMgr.GetMessage("BTN_EXIT"));                
                RadMessageBox.Show(this, oMsgMgr.GetMessage(crxex.ErrorString), oMsgMgr.GetMessage("SYSTEM_ERROR"), MessageBoxButtons.OK, RadMessageIcon.Error);                
                CrxLogger oLogObject = CrxLogger.Instance;
                oLogObject.Write(crxex.Message);
                // close the application if file is corrupted
                this.Close();
                Process.GetCurrentProcess().Kill();
                return;                           
            } */
        }

        /** This method sets Startup mode, startup screen & environment variables & initializes setup screen
         * */
        void SetStartUpModeEnvironmentScreen()
        {
            CrxStructGeneralSetting crxGen = new CrxStructGeneralSetting();
            crxMgrObject.GetGeneralDefaultSettings(crxGen);

            if (string.IsNullOrEmpty(crxGen.StartupScreen))
            {
                OnInitializationProcess.Invoke(oMsgMgr.GetMessage("SYSTEM_ERROR"));
                OnInitializationProcess.Invoke(oMsgMgr.GetMessage("BTN_EXIT"));
                RadMessageBox.Show(this, oMsgMgr.GetMessage("CRX_ERR_FILE_CORRUPT"), oMsgMgr.GetMessage("SYSTEM_ERROR"), MessageBoxButtons.OK, RadMessageIcon.Error);
                CrxLogger oLogObject = CrxLogger.Instance;
                oLogObject.Write(oMsgMgr.GetMessage("CRX_ERR_FILE_CORRUPT"));
                this.Close();
                Process.GetCurrentProcess().Kill();
                return;
            }

            radlblCurrentMode.Text = crxGen.StartupMode;
            guiradlblEnvironment.Text = crxGen.EnvironmentSettings;           
            OnInitializationProcess.Invoke(oMsgMgr.GetMessage("SPLASH_INI_MSG") + " " + crxGen.StartupMode + " " + oMsgMgr.GetMessage("MODE"));
            Thread.Sleep(2000);
            InitializeSetupScreen();
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
                GUIExceptionHandler.HandleException(ex, this);            
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

                // setting initial directory for save file dialog box
                saveFileDialog1.InitialDirectory = Environment.GetFolderPath(Environment.SpecialFolder.Personal);
                saveFileDialog1.RestoreDirectory = true;

                // set waiting bar
                guiWaitingStatusBar.WaitingStep = 10;
                guiWaitingStatusBar.WaitingSpeed = 50;
                guiWaitingStatusBar.Visible = false;

                OnDBBackupAndRestoreCompleteEvent += new EventHandler(DisplayStatusComplete);
                Migrate.OnMigrationStart += new Migrate.HandleMigration(DoMigration);
                
                // call method to check for mdb file to migrate data
                CheckForDataMigration();
            }          
            catch (Exception ex)
            {
               GUIExceptionHandler.HandleException(ex, this); 
            }

            /*  catch (CrxException cfgExp)
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
            } */
        }

        /** This method checks for mdb file & migrates data
         * */
        void CheckForDataMigration()
        {
            // check if migration file exist & then show popup
            if (dbMagr.MigrationFileExist())
            {
                DialogResult dsResult = RadMessageBox.Show(this, oMsgMgr.GetMessage("MIGRATE_FILE_MSG1") + "\r\n\r\n" + oMsgMgr.GetMessage("MIGRATE_FILE_MSG2"), oMsgMgr.GetMessage("APPLICATION_MESSAGE"), MessageBoxButtons.YesNo, RadMessageIcon.Info);

                if (dsResult == DialogResult.Yes)
                {
                    // redirect to migrate screen to select group
                    Migrate migrt = new Migrate();
                    migrt.ShowDialog();
                    migrt.ShowInTaskbar = false;

                    if (Migrate.IsMigrate == 1)
                    {
                        // start waiting progress bar on main thread
                        guiWaitingStatusBar.Visible = true;
                        guiWaitingStatusBar.StartWaiting();

                        // disable menu & tab page while restore is on
                        guiradmnuScor.Enabled = false;
                        radpgTabCollection.Enabled = false;
                    }
                }
            }
        }

        /** This method migrates records
         * */
        void DoMigration(string groupname)
        { 
            // call method to migrate records 
            Thread migThread = new Thread(new ParameterizedThreadStart(StartMigration));
            migThread.Start(groupname);
        }

        /** This method starts data migration
         * */
        void StartMigration(object groupname)
        {
           // code to migrate data
            try
            {
                int i = dbMagr.MigrateAtCorData(SettingsProperties.SystemIdentifier, groupname.ToString());

                if (i == 0)
                {
                    // successfully migrated data
                    dbOperation = oMsgMgr.GetMessage("MIGRATION_SUCCESS_MESSAGE");

                    // Invoke methods to stop progressbasr & reload setup screen
                    OnRestoreCompleteSuccess.Invoke(this, new EventArgs());
                    OnDBBackupAndRestoreCompleteEvent.Invoke(this, new EventArgs());
                }
                else
                {
                    // migration failed
                    dbOperation = oMsgMgr.GetMessage("MIGRATION_FAIL");

                    // Invoke methods to stop progressbasr & reload setup screen
                    OnDBBackupAndRestoreCompleteEvent.Invoke(this, new EventArgs());                    
                }
            }         
            catch (Exception ex)
            {
                // on exception stop waiting bar & show error message
                if (this.InvokeRequired)
                {
                    dbOperation = oMsgMgr.GetMessage("MIGRATION_FAIL");
                    OnDBBackupAndRestoreCompleteEvent.Invoke(this, new EventArgs());

                    ExceptionHandler exc = new ExceptionHandler(GUIExceptionHandler.HandleException);
                    this.Invoke(exc, ex, this);
                }
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
                GUIExceptionHandler.HandleException(ex, this);
                return false;
            }
        } 
        #endregion

        /** This method loads setup form
         * */
        void InitializeSetupScreen()
        {
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

            // initialize report screen at the time of application launch
            InitializeReportScreen();
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
                GUIExceptionHandler.HandleException(ex, this);                
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
                GUIExceptionHandler.HandleException(ex, this);
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
                GUIExceptionHandler.HandleException(ex, this);
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
            catch (Exception ex)
            {
                GUIExceptionHandler.HandleException(ex, this);
            }

           /* catch (CrxException ex)
            {
                RadMessageBox.Show(this, oMsgMgr.GetMessage(ex.ErrorString), oMsgMgr.GetMessage("SYSTEM_ERROR"), MessageBoxButtons.OK, RadMessageIcon.Error);
                CrxLogger oLogObject = CrxLogger.Instance;
                oLogObject.Write(ex.ErrorString);
                radlblMessage.Text = string.Empty;
            } */            
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
            catch (Exception ex)
            {
                if (this.InvokeRequired)
                {
                    dbOperation = oMsgMgr.GetMessage("BACKUP_FAIL");
                    OnDBBackupAndRestoreCompleteEvent.Invoke(this, new EventArgs());

                    ExceptionHandler excep = new ExceptionHandler(GUIExceptionHandler.HandleException);
                    this.Invoke(excep, ex, this);
                    ////DisplayMessageBoxDelegate messageBox = new DisplayMessageBoxDelegate(DisplayErrorMessage);
                    ////this.Invoke(messageBox, ex.Message, ex);                   
                }

                /*   catch (CrxException ex)
            {
                if (this.InvokeRequired)
                {
                    dbOperation = oMsgMgr.GetMessage("BACKUP_FAIL");
                    OnDBBackupAndRestoreCompleteEvent.Invoke(this, new EventArgs());

                    DisplayMessageBoxDelegate messageBox = new DisplayMessageBoxDelegate(DisplayErrorMessage);
                    this.Invoke(messageBox, ex.ErrorString, ex);                   
                }

                CrxLogger oLogObject = CrxLogger.Instance;
                oLogObject.Write(ex.ErrorString);
            } */
            }            
        }

        /** This method saves database backup at selected location
         * */
        void DoBackup(string path)
        {
            int success = 0;

            if (dbMagr.CheckConnection(serverNameString, crxMgrObject.GeneralSettings.SourceData) == 0) 
            {
              // save backup at selected location in shared folder
                if (!Path.GetExtension(path).Equals(BackupFileExt, StringComparison.CurrentCultureIgnoreCase))
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
            else
            {
                dbOperation = oMsgMgr.GetMessage("BACKUP_FAIL");
                OnDBBackupAndRestoreCompleteEvent.Invoke(this, new EventArgs());

                DisplayMessageBoxDelegate messageBox = new DisplayMessageBoxDelegate(ShowConnectionError);
                this.Invoke(messageBox, dbOperation, null); 
            }
        }
           
        /** This method shows network connection failure message for restore & backup operations
         * */
        void ShowConnectionError(string message, Exception ex)
        {
            // show error message db connection failed
            DialogResult result = RadMessageBox.Show(this, SettingsProperties.ConnectionErrorString(), oMsgMgr.GetMessage("SYSTEM_ERROR"), MessageBoxButtons.RetryCancel, RadMessageIcon.Error);
            if (result == DialogResult.Retry)
            {
                if (dbOperation.Equals(oMsgMgr.GetMessage("BACKUP_FAIL"), StringComparison.CurrentCultureIgnoreCase))
                {
                    this.Invoke(new EventHandler(guiradmenuBackup_Click));
                }
                else
                {
                    this.Invoke(new EventHandler(guiradmenuRestore_Click));
                }
            }
        }

        void StopWaitingBar(object sender, EventArgs e)
        {
            ////if (this.InvokeRequired)
            ////{
            ////    this.Invoke(new EventHandler(StopWaitingBar));
            ////    return;
            ////}
            ////radguiwaitingbar.Visible = false;
            ////radguiwaitingbar.EndWaiting();
            ////radguiwaitingbar.Dispose();
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
            if (dbOperation.Equals(oMsgMgr.GetMessage("BACKUP_TITLE"), StringComparison.CurrentCultureIgnoreCase))
            {
                radlblMessage.Text = oMsgMgr.GetMessage("BACKUP_DONE");

                // log the message
                CrxLogger oLogObject = CrxLogger.Instance;
                oLogObject.Write(oMsgMgr.GetMessage("BACKUP_DONE"));
            }
            else if (dbOperation.Equals(oMsgMgr.GetMessage("RESTORE_TITLE"), StringComparison.CurrentCultureIgnoreCase))
            {
                radlblMessage.Text = oMsgMgr.GetMessage("RESTORE_DONE");
                
                // log the message
                CrxLogger oLogObject = CrxLogger.Instance;
                oLogObject.Write(oMsgMgr.GetMessage("RESTORE_DONE"));
            }
            else if (dbOperation.Equals(oMsgMgr.GetMessage("MIGRATION_SUCCESS_MESSAGE"), StringComparison.CurrentCultureIgnoreCase))
            {
                radlblMessage.Text = oMsgMgr.GetMessage("MIGRATION_SUCCESS_MESSAGE");

                // log the message
               // CrxLogger oLogObject = CrxLogger.Instance;
               // oLogObject.Write(oMsgMgr.GetMessage("MIGRATION_SUCCESS_MESSAGE"));
            }
            else if (dbOperation.Equals(oMsgMgr.GetMessage("MIGRATION_FAIL"), StringComparison.CurrentCultureIgnoreCase))
            {
                radlblMessage.Text = oMsgMgr.GetMessage("MIGRATION_FAIL");

                // log the message
               // CrxLogger oLogObject = CrxLogger.Instance;
               // oLogObject.Write(oMsgMgr.GetMessage("MIGRATION_FAIL"));
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
                if (radpgTabCollection.SelectedPage.Text.Equals(oMsgMgr.GetMessage("TAB_CAPTURE"), StringComparison.CurrentCultureIgnoreCase))
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
                else if (radpgTabCollection.SelectedPage.Text.Equals(oMsgMgr.GetMessage("TAB_REPORT"), StringComparison.CurrentCultureIgnoreCase))
                {                    
                    if (!radtabReport.Enabled)
                    {
                        return;
                    }

                    // SettingsProperties.reportChildForm.Show(); 
                    if (SettingsProperties.CaptureToReport)
                    {
                        SettingsProperties.SetupToReport = false;
                    }
                    else
                    {
                        SettingsProperties.SetupToReport = true;
                    }

                   // SettingsProperties.reportChildForm.Update();
                   // SettingsProperties.reportChildForm.Visible = false;
                     
                     ////Thread reportLoad = new Thread(StartWaiting);
                     ////reportLoad.Priority = ThreadPriority.Highest; 
                     //// reportLoad.Start();
                     LoadReportScreen();
                    
                    // #####################################################################
                    // before show the empty screen and start the waiting bar
                    // Thread rptWaitScr = new Thread(ReportWaitScreen);
                    // rptWaitScr.Start();
                    // ReportBlankScreen frmRptBlnk = new ReportBlankScreen();
                    // frmRptBlnk.Dock = DockStyle.Fill;

                    // frmRptBlnk.Show();
                    // frmRptBlnk.BringToFront();

                    // #####################################################################  
                    // #####################################################################
                    // now close the wait form

                    // SettingsProperties.frmRptBlnk.Close();
                    // frmRptBlnk.Dispose();
                    // SettingsProperties.reportChildForm.BringToFront();

                    // #####################################################################

                    // disable setting tab on menu bar
                    guiradmnuitemSettings.Enabled = false;
                    radtabCapture.Enabled = false;                  
                }
                else if (radpgTabCollection.SelectedPage.Text.Equals(oMsgMgr.GetMessage("TAB_SETUP"), StringComparison.CurrentCultureIgnoreCase))
                {
                    // InitializeSetupScreen(); 
                    radlblCaptureTime.Text = string.Empty;
                    if (SettingsProperties.HasMeasurementDetails)
                    {
                        radtabCapture.Enabled = true;
                        radtabReport.Enabled = true;
                    }
                    else
                    {
                        radtabCapture.Enabled = false;
                        radtabReport.Enabled = false;
                    }

                    SettingsProperties.CaptureToReport = false;
                }
            }
            catch (Exception ex)
            {
                GUIExceptionHandler.HandleException(ex, this);
            }
        }

        void LoadReportScreen()
        {
            OnReportTabClick.Invoke(this, new EventArgs());
        }

        /** This method starts waiting progress bar
         * */
        void StartWaiting()
        {
            // radlblMessage.Text = "Report screen loading....";
            RadWaitingBar radguiwaitingbar = new RadWaitingBar();
            radguiwaitingbar.Location = new Point(379, 223);
            radguiwaitingbar.BringToFront();
            radguiwaitingbar.Visible = true;
            radguiwaitingbar.StartWaiting();
        }

        /** This method initialises report screen 
         * */
        void InitializeReportScreen()
        {
            SettingsProperties.SetupToReport = true;

            // open report form under report tab
            if (SettingsProperties.reportChildForm != null)
            {
                SettingsProperties.reportChildForm.Close();
                SettingsProperties.reportChildForm.Dispose();
            }

            SettingsProperties.reportChildForm = new Report(this);
            SettingsProperties.reportChildForm.TopLevel = false;
            SettingsProperties.reportChildForm.Dock = DockStyle.Fill;
            SettingsProperties.reportChildForm.FormBorderStyle = System.Windows.Forms.FormBorderStyle.None;

            // adds report form under parent window control
            var page = radpgTabCollection.Pages[2];
            SettingsProperties.reportChildForm.Parent = page;
            page.Controls.Add(SettingsProperties.reportChildForm);
            
            SettingsProperties.reportChildForm.Show();
        }

        // private void ReportWaitScreen()
        // {
        // SettingsProperties.frmRptBlnk = new ReportBlankScreen();
        // SettingsProperties.frmRptBlnk.Dock = DockStyle.Fill;

        // SettingsProperties.frmRptBlnk.ShowDialog();
        // //SettingsProperties.frmRptBlnk.BringToFront();
            
        // }

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
                        if (Path.GetExtension(openFileDialog1.FileName).Equals(BackupFileExt, StringComparison.CurrentCultureIgnoreCase))
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
            catch (Exception ex)
            {
                GUIExceptionHandler.HandleException(ex, this);
            }

            /*  catch (CrxException ex)
           {
               RadMessageBox.Show(this, oMsgMgr.GetMessage(ex.ErrorString), oMsgMgr.GetMessage("SYSTEM_ERROR"), MessageBoxButtons.OK, RadMessageIcon.Error);
               CrxLogger oLogObject = CrxLogger.Instance;
               oLogObject.Write(ex.ErrorString);
               radlblMessage.Text = string.Empty;
           } */
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

                if (dbMagr.CheckConnection(serverNameString, crxMgrObject.GeneralSettings.SourceData) == 0)
                {
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
                else
                {
                    dbOperation = oMsgMgr.GetMessage("RESTORE_FAIL");
                    OnDBBackupAndRestoreCompleteEvent.Invoke(this, new EventArgs());

                    DisplayMessageBoxDelegate messageBox = new DisplayMessageBoxDelegate(ShowConnectionError);
                    this.Invoke(messageBox, dbOperation, null);                        
                }
            }
            catch (Exception ex)
            {
                if (this.InvokeRequired)
                {
                    dbOperation = oMsgMgr.GetMessage("RESTORE_FAIL");
                    OnDBBackupAndRestoreCompleteEvent.Invoke(this, new EventArgs());

                    ExceptionHandler handle = new ExceptionHandler(GUIExceptionHandler.HandleException);
                    this.Invoke(handle, ex, this);

                    // GUIExceptionHandler.HandleException(ex, this);
                    ////DisplayMessageBoxDelegate messageBox = new DisplayMessageBoxDelegate(DisplayErrorMessage);
                    ////this.Invoke(messageBox, ex.Message, ex);                   
                }
            }

          /*  catch (CrxException ex)
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
            } */            
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
            // vibhuti: this will be replaced by common exception handling class
            ////if (ex.GetType() == typeof(CrxException))
            ////{
            ////    RadMessageBox.Show(this, errorMessage, oMsgMgr.GetMessage("SYSTEM_ERROR"), MessageBoxButtons.OK, RadMessageIcon.Error);
            ////}
            ////else
            ////{
            ////    RadMessageBox.Show(this, oMsgMgr.GetMessage(errorMessage), oMsgMgr.GetMessage("SYSTEM_ERROR"), MessageBoxButtons.OK, RadMessageIcon.Error);
            ////}
        }

        private void DisplayMessage(string message)
        {
            radlblMessage.Text = message;
        }
        }      
    }
