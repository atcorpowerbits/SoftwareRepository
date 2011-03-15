/*
     Copyright (C) ATCOR MEDICAL PTY LTD, 2010
 
    Filename     :      Default Window
        
    Author       :      Nitesh Chhedda
 
    Description  :      This is the Default Window on Application load.
*/
using System.Linq;
using AtCor.Scor.CrossCutting.Configuration;  
using AtCor.Scor.CrossCutting.Logging;
using AtCor.Scor.CrossCutting.DatabaseManager;  
using AtCor.Scor.CrossCutting.Messaging;
using System.Configuration;
using System.Diagnostics;
using System.Threading;
using System.Windows.Forms;
using System;
using Telerik.WinControls.UI;
using Telerik.WinControls;
using AtCor.Scor.BusinessLogic;
using System.IO;
using AtCor.Scor.DataAccess;

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
    public partial class DefaultWindow : RadForm
    {
        // Code to minimize running application from taskbar

        const int WsMinimizebox = 0x20000;
        const int CsDblclks = 0x8;
        protected override CreateParams CreateParams
        {
            get
            {
                CreateParams cp = base.CreateParams;
                cp.Style |= WsMinimizebox;
                cp.ClassStyle |= CsDblclks;
                return cp;
            }
        }
        // Code Ended

        const string BackupFileExt = ".bak"; // to be placed in common file as global variable
        // static int count = 0;
        readonly string serverNameString = string.Empty;
        readonly CrxConfigManager crxMgrObject = CrxConfigManager.Instance;
        
        CrxDBManager dbMagr;
        string currentpath = string.Empty; 
        string dbOperation = string.Empty; 
        
        // private delegate void ThreadException(Exception ex);
       // private event ThreadException OnThreadExceptionEvent;  
        public delegate void InitializationMessage(string message);

        public static event EventHandler OnRestoreCompleteSuccess;

        public static event EventHandler OnReportTabClick;

        public static event EventHandler OnCaptureTabClick;

        public static event InitializationMessage OnInitializationProcess;

        // Event to indicate completion of database backup process
        private event EventHandler OnDBBackupAndRestoreCompleteEvent; 

        private delegate void DisplayMessageBoxDelegate(string message, Exception ex);

        private delegate void DisplayStatusMessageDelegate(string message);
        
        #region Global declarations
                     
        bool isDirectClose; // Flag set to check if there are multiple instances of the application.        
                
        // object of Config Manager         
        CrxMessagingManager oMsgMgr = CrxMessagingManager.Instance;

        // sets message on the status bar of the main window.
        public void SetMessage(string message)
        {
            radlblMessage.Text = message;            
        }

        #endregion
        
        /**Constructor of the form,initializes all the controls.
        *It will call IsProcessOpen method which will check if there is any other instance is running.
        */
        public DefaultWindow()
        {
            try
            {
                // Logic to check multiple instances of the application.                 
                if (IsProcessOpen(oMsgMgr.GetMessage("APP_NAME")))
                {
                    // writes messages on splash screen by invoking OnInitializationProcess
                    //OnInitializationProcess.Invoke(oMsgMgr.GetMessage("EXEC_ERROR"));
                    //OnInitializationProcess.Invoke(oMsgMgr.GetMessage("BTN_EXIT"));
                    isDirectClose = true;
                    RadMessageBox.Show(this, oMsgMgr.GetMessage("APP_MSG"), oMsgMgr.GetMessage("EXEC_ERROR"), MessageBoxButtons.OK, RadMessageIcon.Error);
                    this.Close();
                    Process.GetCurrentProcess().Kill();
                    return;
                }

                // launches splash screen
                SplashScreen splsh = new SplashScreen();
                splsh.Show();
                splsh.Update();               

                isDirectClose = false;

                // get current application directory
                currentpath = Directory.GetCurrentDirectory();
                           
                // check if startup screen is set in config file
                crxMgrObject.GetGeneralUserSettings();
                if (string.IsNullOrEmpty(crxMgrObject.GeneralSettings.StartupScreen))
                {
                    // writes messages on splash screen by invoking OnInitializationProcess
                    OnInitializationProcess.Invoke(oMsgMgr.GetMessage("SYSTEM_ERROR"));
                    OnInitializationProcess.Invoke(oMsgMgr.GetMessage("BTN_EXIT"));
                    RadMessageBox.Show(this, oMsgMgr.GetMessage("CRX_ERR_FILE_CORRUPT"), oMsgMgr.GetMessage("SYSTEM_ERROR"), MessageBoxButtons.OK, RadMessageIcon.Error);
                    CrxLogger.Instance.Write(oMsgMgr.GetMessage("CRX_ERR_FILE_CORRUPT"));
                    this.Close();
                    Process.GetCurrentProcess().Kill();
                    return;
                }
                              
                if (string.IsNullOrEmpty(crxMgrObject.GeneralSettings.MachineName))
                {
                    crxMgrObject.GeneralSettings.MachineName = SystemInformation.ComputerName;
                    CrxLogger.Instance.Write(oMsgMgr.GetMessage("SQL_SERVER_CHANGED_TO_LOCAL"));
                }
               
                if (string.IsNullOrEmpty(crxMgrObject.GeneralSettings.SourceData))
                {
                    crxMgrObject.GeneralSettings.SourceData = "SQLCLIENT";
                    CrxLogger.Instance.Write(oMsgMgr.GetMessage("SQL_SERVER_CHANGED_TO_DEFAULT"));
                }
              
                serverNameString = SettingsProperties.ServerNameString();

                dbMagr = CrxDBManager.Instance;
                int result = dbMagr.SetConnection(serverNameString, crxMgrObject.GeneralSettings.SourceData.Trim());
               
                // log message on connection status.
                if (result.Equals(0))
                {
                    // successfully connected
                    CrxLogger.Instance.Write(oMsgMgr.GetMessage("SQL_SERVER_CONNECTED") + serverNameString);
                    crxMgrObject.SetGeneralUserSettings(crxMgrObject.GeneralSettings);

                    OnInitializationProcess.Invoke(string.Format("{0} {1}", oMsgMgr.GetMessage("SPLASH_SQL_CONN"), serverNameString));
                }

                if (result.Equals(1))
                {
                    // not able to connect, show popuo message for selecting machine.
                    OnInitializationProcess.Invoke(string.Format("{0} {1}", oMsgMgr.GetMessage("SQL_SERVER_CONN_FAILED"), serverNameString));
                    OnInitializationProcess.Invoke(oMsgMgr.GetMessage("BTN_EXIT"));
                    CrxLogger.Instance.Write(oMsgMgr.GetMessage("SQL_SERVER_CONN_FAILED") + serverNameString);

                    // Get the list of SQL server instances on the network
                    SQLInstanceList frmObject = new SQLInstanceList();
                    frmObject.ShowInTaskbar = false;
                    frmObject.ShowDialog();                    
                }
                
                // user have clicked on cancel
                if (SQLInstanceList.IsCancel == 1)
                {
                    OnInitializationProcess.Invoke(oMsgMgr.GetMessage("BTN_EXIT"));
                    SQLInstanceList.IsCancel = 0;
                    this.Close();
                    Process.GetCurrentProcess().Kill();
                    return;
                }

                // DB connection string, save in class variable
                serverNameString = SettingsProperties.ServerNameString();
                InitializeComponent();
                
                // Set the text for  Capture Tab form controls
                SetTextForRibbionControl();

                // call bizdatavalidation class to set metric & distance units
                // crxMgrObject.GeneralSettings.HeightandWeightUnit
               // BizDataValidation.Instance().SetMeasSystem(UnitsType.UNITS_IMPERIAL, MetricDistanceUnits.METRIC_DISTANCE_MM);
                radpgTabCollection.SelectedPage = guiradgrpbxPwvDistanceMethod;       
                SetStartUpModeEnvironmentScreen();                              

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
                CrxLogger.Instance.Write(oMsgMgr.GetMessage("CRX_ERR_FILE_CORRUPT"));
                this.Close();
                Process.GetCurrentProcess().Kill();
                return;
            }

            // set up mode and environment texts on startup screen.
            radlblCurrentMode.Text = crxGen.StartupMode;
            guiradlblEnvironment.Text = crxGen.EnvironmentSettings;           
            OnInitializationProcess.Invoke(string.Format("{0} {1} {2}", oMsgMgr.GetMessage("SPLASH_INI_MSG"), crxGen.StartupMode, oMsgMgr.GetMessage("MODE")));
            
            // Follwig delay is used to display messages on splash screen before application launch
            // without this delay some of the messages in loading application is not displayed.
            Thread.Sleep(2000);
            InitializeSetupScreen();
        }

        /**This method is called to set the text for the controls in the ribbon bar.The text is read from the resource file.
        */  
        private void SetTextForRibbionControl()
        {
            guiradgrpbxPwvDistanceMethod.Text = oMsgMgr.GetMessage("TAB_SETUP");
            radtabCapture.Text = oMsgMgr.GetMessage("TAB_CAPTURE");
            radtabReport.Text = oMsgMgr.GetMessage("TAB_REPORT");
            guiradmnuFindPrinter.Text = oMsgMgr.GetMessage("GUI_PRINTER_SETUP");
            guiradmnuitemSettings.Text = oMsgMgr.GetMessage("GUI_SETTINGS_MENU");
            guiradmnuFindModule.Text = oMsgMgr.GetMessage("GUI_FIND_MODULE_MENU");
            guiradmnuExit.Text = oMsgMgr.GetMessage("GUI_EXIT_MENU");
            guiradmenuBackup.Text = oMsgMgr.GetMessage("GUI_BACKUP_MENU");
            guiradmenuRestore.Text = oMsgMgr.GetMessage("GUI_RESTORE_MENU");
            guiradmnuOperatorManual.Text = oMsgMgr.GetMessage("GUI_OPERATOR_GUIDE_MENU");
            guiradmnuServiceManual.Text = oMsgMgr.GetMessage("GUI_SERVICE_MANUAL_MENU");
            guiradmenuahomepage.Text = oMsgMgr.GetMessage("GUI_ATCOR_HOMEPAGE_MENU");
            guiradmnuitemAbout.Text = oMsgMgr.GetMessage("GUI_ABOUT_MENU");
        }
        
        /**This method is invoked on the click of the Exit button under System menu.
         * It will close the main window.
         */
        private void radButtonElementExit_Click(object sender, EventArgs e)
        {  
            // Close the application on click of Exit button under System menu.
            //ExitApplication();    
            this.Close();
        }

        /** This method checks for any changes in the current form if any and accordingly exits the application
         * after asking the user
         * */
        private void ExitApplication()
        {
            // check if any changes are made in current form
            if (!SettingsProperties.IsFormChanged)
            {
                this.Close();
                return;
            }
            
                // ask the user if he wants to close the application
                DialogResult ds = RadMessageBox.Show(this, oMsgMgr.GetMessage("GUI_EXIT_MSG"),
                                                     oMsgMgr.GetMessage("APPLICATION_MESSAGE"), MessageBoxButtons.YesNo,
                                                     RadMessageIcon.Question);

                if (ds == DialogResult.Yes)
                {
                    this.Close();
                }
            
        }

        /**This event is fired when window is closed.
         *It will ask for user confirmation before closing the window.
         */
        private void DefaultWindow_FormClosing(object sender, FormClosingEventArgs e)
        {
            int logExit = 0;
            try
            {
                // On form closing a confirmation is asked to the user to Save the unsaved data.                                       
                if (!isDirectClose)
                {
                    if (SettingsProperties.IsFormChanged)
                    {
                        RadMessageBox.SetThemeName(oMsgMgr.GetMessage("MSG_DESERT"));
                        DialogResult ds = RadMessageBox.Show(this, oMsgMgr.GetMessage("MSG_SAVE_CHANGE"), oMsgMgr.GetMessage("MSG_SAVE_SETTINGS"), MessageBoxButtons.YesNoCancel, RadMessageIcon.Question);

                        // Keeping Yes and No separate for future use.                     
                        if (ds == DialogResult.Yes)
                        {
                            // Save data then exit.Application exited
                            logExit = 0;
                        }
                        else if (ds == DialogResult.No)
                        {
                            logExit = 0;
                        }
                        else
                        {
                            logExit = 1;
                            return;
                        }
                    }
                }               
            }
            catch (Exception ex)
            {
                GUIExceptionHandler.HandleException(ex, this);
            }
            finally
            {
                // log the message when application closes
                // this will be logged even if there is an exception
                // logExit will be 1 if user chooses not to exit
                if (logExit == 0)
                {
                    CrxLogger.Instance.Write(oMsgMgr.GetMessage("EXITSTR"));
                    Process.GetCurrentProcess().Kill();
                }
            }
        }
        
        /**This is invoked on the load of the window.
         *Once the application is launched it will log the event into the log file.
         */
        private void DefaultWindow_Load(object sender, EventArgs e)
        {  
            try
            {
                // On application load check if the resource file exists.
              //  CheckForResourceFile();
                
                EnableMenuBarControls(); 
                
                // check if we can access the configuration file by reading general setting from config manager object.   
                CrxConfigManager oConfigMgr = CrxConfigManager.Instance;
                oConfigMgr.GetGeneralUserSettings();              

                // On windows load set the windows size to maximum.                 
                WindowState = FormWindowState.Maximized;

                // Log the event on successful load of the application.                 
                CrxLogger.Instance.Write(oMsgMgr.GetMessage("STARTSTR"));

                // save the current window object for exception handling class
                SettingsProperties.defaultWindowForm = this;

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
                int count = Process.GetProcesses().Count(clsProcess => clsProcess.ProcessName.Contains(name));

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
            SettingsProperties.setupChildForm.FormBorderStyle = FormBorderStyle.None;
            
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
/*
        private void DisableTabs(string currentTab)
        {
            // disables all the tabs except the currentTab
            foreach (RadPageViewPage t in radpgTabCollection.Pages.Where(t => t.Text.ToLower() != currentTab))
            {
                t.Enabled = false;
            }
        }
*/

        /** This event is fired when the user clicks tried to click on the OperatorGuide option on the menu bar.
        */
        private void guiradmnuitemOperatorGuide_Click(object sender, EventArgs e)
        {
            try
            {
                if (File.Exists(ConfigurationManager.AppSettings["OperatorGuidePath"].Replace("{culture}", Program.GetCurrentCulture())))
                {
                    Process.Start(Path.GetFullPath(ConfigurationManager.AppSettings["OperatorGuidePath"].Replace("{culture}", Program.GetCurrentCulture())));
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
                  Process.Start(Path.GetFullPath(ConfigurationManager.AppSettings["ServiceManualPath"].Replace("{culture}", Program.GetCurrentCulture())));
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
            Process.Start(ConfigurationManager.AppSettings["SupportURL"].ToString());
        }

        /** This method is called to Enable the menu controls.
         */ 
        private void EnableMenuBarControls()
        {
            guiradmnuScor.MenuElement.SystemButtons.Visibility = ElementVisibility.Visible;
            guiradmnuScor.MenuElement.CloseButton.Click += new EventHandler(CloseButton_Click);
            guiradmnuScor.MenuElement.MinimizeButton.Click += new EventHandler(MinimizeButton_Click);
        }

        /** This event is fired when the user clicks on the close button.
         */ 
        private void CloseButton_Click(object sender, EventArgs e)
        {
            // close the application
            //ExitApplication();
            this.Close();
        }

        /** This event is fired when the user clicks on the minimze button on the title bar.
         */ 
        private void MinimizeButton_Click(object sender, EventArgs e)
        {
            WindowState = FormWindowState.Minimized;
        }

        /** This method is used to set the capture time in the status bar.
         */ 
/*
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
*/

        /**This method is invoked when Settings button under System tab is clicked. 
         * It opens setting window
         */ 
        private void guiradmnuSettings_Click(object sender, EventArgs e)
        {
            try
            {
                // Open the settings dialog box.                 
                var settingWinObject = new frmSettingsWindow(this);
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
                DialogResult result = saveFileDialog1.ShowDialog();

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
                CrxLogger.Instance.Write(oMsgMgr.GetMessage("BACKUP_PROGRESS"));

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
                }                
            }            
        }

        /** This method saves database backup at selected location
         * */
        void DoBackup(string path)
        {
            if (dbMagr.CheckConnection(serverNameString, crxMgrObject.GeneralSettings.SourceData) == 0) 
            {
              // save backup at selected location in shared folder
                int success;
                success = !Path.GetExtension(path).Equals(BackupFileExt, StringComparison.CurrentCultureIgnoreCase) ? dbMagr.DatabaseBackup(path + BackupFileExt) : dbMagr.DatabaseBackup(path);

                // on backup success invoke event to display status message
                if (success == 0)
                {
                    dbOperation = oMsgMgr.GetMessage("BACKUP_DONE");
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
                this.Invoke(dbOperation.Equals(oMsgMgr.GetMessage("BACKUP_FAIL"),
                                               StringComparison.CurrentCultureIgnoreCase)
                                ? new EventHandler(guiradmenuBackup_Click)
                                : new EventHandler(guiradmenuRestore_Click));
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

            // show status message for restore & backup & migration.... dbOperation will contain respective messages
            radlblMessage.Text = dbOperation;         
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
                    NavigateToCapture();
                }
                else if (radpgTabCollection.SelectedPage.Text.Equals(oMsgMgr.GetMessage("TAB_REPORT"), StringComparison.CurrentCultureIgnoreCase))
                {
                    NavigateToReport();
                }
                else if (radpgTabCollection.SelectedPage.Text.Equals(oMsgMgr.GetMessage("TAB_SETUP"), StringComparison.CurrentCultureIgnoreCase))
                {                   
                    NavigateToSetup();
                }
            }
            catch (Exception ex)
            {
                GUIExceptionHandler.HandleException(ex, this);
            }
        }

        /**This method will navigate the user to the Capture screen.
         */ 
        private void NavigateToCapture()
        {
            try
            {
                if (!radtabCapture.Enabled)
                {
                    return;
                }

                if (SettingsProperties.CaptureTabClick)
                {
                    OnCaptureTabClick.Invoke(this, new EventArgs());
                }

                SettingsProperties.CaptureTabClick = true;
            }
            catch (Exception ex)
            {
                // whenever exception is thrown while validating measurement details,
                // navigate the user back to Setup screen.                
                radpgTabCollection.SelectedPage = guiradgrpbxPwvDistanceMethod;

                GUIExceptionHandler.HandleException(ex, this);
            }

        }

        /**This method will navigate the user to the Setup screen.
         */ 
        private void NavigateToSetup()
        {
            radtabCapture.Enabled = !SettingsProperties.IsWaitIntervalImposed;

            // InitializeSetupScreen(); 
            radtabReport.Text = oMsgMgr.GetMessage("TAB_REPORT");
            radlblCaptureTime.Text = string.Empty;
            radtabReport.Enabled = SettingsProperties.HasMeasurementDetails;

            SettingsProperties.CaptureToReport = false;
        }

        /**This method will navigate the user to the Report screen.
         */ 
        private void NavigateToReport()
        {
            if (!radtabReport.Enabled)
            {
                return;
            }

            SettingsProperties.SetupToReport = SettingsProperties.CaptureToReport ? false : true;

            if (SettingsProperties.ReportLoadCount == 1)
            {
                SettingsProperties.ReportLoadCount++;
            }
            else
            {
                LoadReportScreen();
            }

            // disable setting tab on menu bar
            guiradmnuitemSettings.Enabled = false;

            // radtabCapture.Enabled = false;   
        }

        /** This method invokes load event of report screen
         * It binds the record for selected patient on setup screen in report
         * */
        void LoadReportScreen()
        {
            // as report form is already loaded in memory, in order to refresh its data
            // we need to generate events, which in turn reload the report screen data.
            OnReportTabClick.Invoke(this, new EventArgs());
        }

        /** This method starts waiting progress bar
         * */
        void StartWaiting(object sender, EventArgs e)
        {
            //-------------- keep this code as we might need it for report loading issue-----------
            // radlblMessage.Text = "Report screen loading....";
            ////RadWaitingBar radguiwaitingbar = new RadWaitingBar();
            ////radguiwaitingbar.Location = new Point(379, 223);
            ////radguiwaitingbar.BringToFront();
            ////radguiwaitingbar.Visible = true;
            ////radguiwaitingbar.StartWaiting();
            ////if (InvokeRequired)
            ////{
            ////    this.Invoke(new EventHandler(StartWaiting));
            ////    return;
            ////}

            guiWaitingStatusBar.Visible = true;
            guiWaitingStatusBar.StartWaiting();            
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

            SettingsProperties.reportChildForm = new Report(this)
                                                     {
                                                         TopLevel = false,
                                                         Dock = DockStyle.Fill,
                                                         FormBorderStyle = FormBorderStyle.None
                                                     };

            // adds report form under parent window control
            var page = radpgTabCollection.Pages[2];
            SettingsProperties.reportChildForm.Parent = page;
            page.Controls.Add(SettingsProperties.reportChildForm);
            
            SettingsProperties.reportChildForm.Show();            
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
        }

        /** This method restores databse backup
         * */
        private void RestoreBackupFile()
        {
            try
            {
                string path = openFileDialog1.FileName;

                // set current directory for resource file
                Directory.SetCurrentDirectory(currentpath); // shri: make part of global class
                dbOperation = oMsgMgr.GetMessage("RESTORE_TITLE");
                        
                // log message for restore started
                CrxLogger.Instance.Write(oMsgMgr.GetMessage("RESTORE_PROGRESS"));

                if (dbMagr.CheckConnection(serverNameString, crxMgrObject.GeneralSettings.SourceData) == 0)
                {
                    // restore database
                    int success = dbMagr.DatabaseRestore(path);

                    // on success of restore invoke event to show message
                    if (success == 0)
                    {
                        dbOperation = oMsgMgr.GetMessage("RESTORE_DONE");

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
                }
            }           
        }

        /**This event fires when Atcor Homepage menu item is selected
      */
        private void guiradmenuahomepage_Click(object sender, EventArgs e)
        {
            Process.Start(ConfigurationManager.AppSettings["AtcorHomepage"]);
        }

        /**This method will display the error message using the message box.
       */
        private void DisplayErrorMessage(string errorMessage)
        {
            if (InvokeRequired)
            {
                this.Invoke(new DisplayStatusMessageDelegate(DisplayErrorMessage));
                return;
            }

            radlblMessage.Text = errorMessage;
        }

        /** This event fire on selecting About item in top menu bar 
         * It displays about box
         * */
        private void guiradmnuitemAbout_Click(object sender, EventArgs e)
        {
            var about = new RadAboutBox();
            about.ShowDialog();             
        }
        
        /** This event fires when Find Printer option is selected under system menu item
         * It allows user to select a printer & sets the same in config file
         * */
        private void guiradmnuFindPrinter_Click(object sender, EventArgs e)
        {
            guiradmnuExit.Enabled = false;
            SettingsProperties.ViewPrintDialogToSetPrinter(guiFindPrinterDialog);
            guiradmnuExit.Enabled = true;
        }

        /** This event fires when Find module option is click from top Systems menu
         * It finds electronic module and shows appropriate messages
         * */
        private void guiradmnuFindModule_Click(object sender, EventArgs e)
        {
            try
            {  
                // find module in a different thread... this will display messages alternatively as per status   
                Thread findMod = new Thread(FindElectronicModule);
                findMod.Start();
            }
            catch (Exception ex)
            {
                GUIExceptionHandler.HandleException(ex, this);
            }
        }

        /** This method searches for electronic module and shows appropriate messages
         * */
        private void FindElectronicModule()
        {
            try
            {
                DisplayStatusMessageDelegate messageBox = new DisplayStatusMessageDelegate(DisplayErrorMessage);
                this.Invoke(messageBox, oMsgMgr.GetMessage("GUI_SEARCH_ELECTRONIC_MOD"));
                // with out following wait, earlier message is not displayed.
                // Thread.Sleep(2000);

                // search module
                string portName = string.Empty;
                int retValue = DalModule.Instance.FindModule(ref portName);

                switch (retValue)
                {
                    case 0: // module not found
                        CrxLogger.Instance.Write(oMsgMgr.GetMessage("CAPTURE_DEVICE_ERR_MSG"));
                        DisplayMessageBoxDelegate findModuleErrorMessage = new DisplayMessageBoxDelegate(ShowFindModuleError);
                        Invoke(findModuleErrorMessage, oMsgMgr.GetMessage("GUI_ELECTRONIC_MOD_NOTFND"), null);
                        
                        break;

                    case 1: // module present on port, show message to user                    
                        Invoke(messageBox, oMsgMgr.GetMessage("GUI_ELECTRONIC_MOD_FND"));
                        break;

                    case 2: // module found on different port, show message to user
                        Invoke(messageBox, oMsgMgr.GetMessage("GUI_ELECTRONIC_MOD_FNDPORT") + portName);
                        break;

                    default:
                        break;
                }
            }
            catch (Exception ex)
            {
                if (InvokeRequired)
                {
                    ExceptionHandler excep = new ExceptionHandler(GUIExceptionHandler.HandleException);
                    Invoke(excep, ex, this);
                }
            }
        } // End FindElectronicModule

        /** This method is called when module is not found.
         * It displays error message asking user to continue with search for module
         * */
        void ShowFindModuleError(string message, Exception ex)
        {
            radlblMessage.Text = string.Empty;

            // ask user if another search is required                        
            DialogResult ds = RadMessageBox.Show(this, message, oMsgMgr.GetMessage("APPLICATION_MESSAGE"), MessageBoxButtons.YesNo, RadMessageIcon.Info);
            if (ds == DialogResult.Yes)
            {
                // find module again
                FindElectronicModule();
            }           
        }

        
        /**This method will check if resource file exists or no.
         * If the file does not exist,application will show an error message in the pop up,and close the application.
         */
        private void CheckForResourceFile()
        {
            try
            {
                // CrxMessagingManager.Instance.CheckResourceFileExist();
            }
            catch (Exception ex)
            {
                GUIExceptionHandler.HandleException(ex, this);
                this.Close();
            }
        }

        private void tmrImposeWaitTime_Tick(object sender, EventArgs e)
        {
            try
            {
                tmrImposeWaitTime.Enabled = false;
                SettingsProperties.IsWaitIntervalImposed = false;
                SettingsProperties.InvokeCaptureClosing(true);
            }
            catch (Exception ex)
            {
                GUIExceptionHandler.HandleException(ex, this);
                this.Close();
            }
        }

        /**This event is fired when the user tries to navigate across the page view,
         * using the direction keys on the keyboard.
         */ 
        private void DefaultWindow_KeyDown(object sender, KeyEventArgs e)
        {
            try
            {
                if (e.KeyCode == Keys.Left || e.KeyCode == Keys.Right || e.KeyCode == Keys.RButton)
                {
                    //return;
                    e.SuppressKeyPress = true;
                }
            }
            catch (Exception ex)
            {
                GUIExceptionHandler.HandleException(ex, this);
                this.Close();
            }
        }

   } // End class
} // End namespace
