/*
     Copyright (C) ATCOR MEDICAL PTY LTD, 2010
 
    Filename     :      Default Window
        
    Author       :      Nitesh Chhedda
 
    Description  :      This is the Default Window on Application load.
*/
using System.Linq;
using AtCor.Scor.CrossCutting;    
using AtCor.Scor.CrossCutting.Configuration;  
using AtCor.Scor.CrossCutting.Logging;
using AtCor.Scor.CrossCutting.DatabaseManager;  
using AtCor.Scor.CrossCutting.Messaging;
using AtCor.Scor.BusinessLogic;
using System.Configuration;
using System.Collections.Generic;    
using System.Diagnostics;
using System.Threading;
using System.Windows.Forms;
using System;
using Telerik.WinControls.UI;
using Telerik.WinControls;
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
    public partial class DefaultWindow : RadForm, IMessageFilter
    {
        // Code to minimize running application from taskbar
        public const string BackupFileExt = ".bak";                

        public static event EventHandler OnSetupMenuItemClick;

        public static event EventHandler OnReportMenuItemClick;

        // below events will be invoked if user wants to save changes before exiting application from Setup & report screen
        public static event EventHandler OnExitSaveSetupChanges;

        public static event EventHandler OnExitSaveReportChanges;

        public static event EventHandler OnCaptureScreenTabClick;

        public static event EventHandler OnSetupScreenTabClick;

        public static event EventHandler OnRestoreOptionClick;

        // AtCor - Drop2-Sprint1
        public static event EventHandler OnPWAReportTabClick;        

        protected override CreateParams CreateParams
        {
            get
            {
                CreateParams cp = base.CreateParams;
                cp.Style |= GuiConstants.WsMinimizebox;
                cp.ClassStyle |= GuiConstants.CsDblclks;
                return cp;
            }
        }

        // Code Ended        
        readonly string serverNameString = string.Empty;
        readonly CrxConfigManager crxMgrObject = CrxConfigManager.Instance;

        readonly CrxDBManager dbMagr;
        readonly string currentpath = string.Empty; 
        string dbOperation = string.Empty; 
        
        public delegate void InitializationMessage(string message);

        public static event EventHandler OnRestoreCompleteSuccess;

        public static event EventHandler OnReportTabClick;

        public static event EventHandler OnCaptureTabClick;

        public static event InitializationMessage OnInitializationProcess;

        // Event to indicate completion of database backup process
        private event EventHandler OnDbBackupAndRestoreCompleteEvent; 
              
        // Event to indicate mode change
        public static event EventHandler OnModeChangeEvent;

       // public static event EventHandler OnModeChangeDisableTimer;
        private delegate void DisplayStatusMessageDelegate(string message);
        
        #region Global declarations
                     
        bool isDirectClose; // Flag set to check if there are multiple instances of the application.       

        // object of Config Manager         
        readonly CrxMessagingManager oMsgMgr = CrxMessagingManager.Instance;
        SplashScreen splsh = new SplashScreen();
        #endregion
        
        /**Constructor of the form,initializes all the controls.
        *It will call IsProcessOpen method which will check if there is any other instance is running.
        */
        public DefaultWindow()
        {
            try
            {
                // Get configuration settings.
                crxMgrObject.GetGeneralUserSettings();
                crxMgrObject.GetPwvUserSettings();                
                GUIExceptionHandler.RegisterUnHandledExceptionHandler();
                if (Screen.PrimaryScreen.WorkingArea.Width < 1024 && Screen.PrimaryScreen.WorkingArea.Height < 768)
                {
                    RadMessageBox.Show(oMsgMgr.GetMessage(CrxStructCommonResourceMsg.GuiScreenResolutionMsg), oMsgMgr.GetMessage(CrxStructCommonResourceMsg.AppName), MessageBoxButtons.OK, RadMessageIcon.Error);
                    CrxLogger.Instance.Write("Closing application as screen resolution is set below the 1024*768");   
                    Process.GetCurrentProcess().Kill();                    
                }
               
                CrxEventContainer.Instance.OnShowStatusEvent += GUIExceptionHandler.ShowStatusMessage;
              
                isDirectClose = false;

                // Logic to check multiple instances of the application.                 
                if (IsProcessOpen(oMsgMgr.GetMessage(CrxStructCommonResourceMsg.AppName)))
                {
                    isDirectClose = true;
                    RadMessageBox.Show(this, oMsgMgr.GetMessage(CrxStructCommonResourceMsg.AppMsg), oMsgMgr.GetMessage(CrxStructCommonResourceMsg.SystemError), MessageBoxButtons.OK, RadMessageIcon.Error);
                    Process.GetCurrentProcess().Kill();
                }

                // launches splash screen                
                splsh.Show();
                splsh.Update(); 
                
                // get current application directory
                currentpath = Directory.GetCurrentDirectory();

                // set the current culture in thread
                Thread.CurrentThread.CurrentCulture = Thread.CurrentThread.CurrentUICulture = CrxCommon.gCI;
                
                // check if startup screen is set in config file                          
                CheckMachineNameOnStartUp();
                serverNameString = GuiCommon.ServerNameString();
                 
                // Begin: AtCor-<Drop2>-<Sprint2>, TM, <UserStory1>,30 jun 2011
                OnInitializationProcess.Invoke(oMsgMgr.GetMessage(CrxStructCommonResourceMsg.MsgValidatingSystemKey));
                if (!BizInfo.Instance().ValidateLicenseKey())
                {
                    GuiCommon.SystemKeyWindowValue = GuiCommon.SystemKeyWindowValues.ADD;
                    var systemKey = new SystemKey { ShowInTaskbar = false };
                    systemKey.ShowDialog();
                }
                else
                {
                    GuiCommon.IsValidatedLicenseKey = true;
                }

                if (GuiCommon.IsValidatedLicenseKey)
                {
                    // End   : AtCor-<Drop2>-<Sprint2>, TM, <UserStory1>,30 jun 2011
                    dbMagr = CrxDBManager.Instance;
                    int result = dbMagr.SetConnection(serverNameString, crxMgrObject.GeneralSettings.SourceData.Trim());

                    // log message on connection status.
                    if (result.Equals(0))
                    {
                        // successfully connected
                        CrxLogger.Instance.Write(oMsgMgr.GetMessage(CrxStructCommonResourceMsg.SqlServerConnected) + serverNameString);
                        crxMgrObject.SetGeneralUserSettings(crxMgrObject.GeneralSettings);

                        OnInitializationProcess.Invoke(string.Format("{0} {1}", oMsgMgr.GetMessage(CrxStructCommonResourceMsg.SplashSqlConn), serverNameString));
                    }

                    if (result.Equals(1))
                    {
                        // not able to connect, show popuo message for selecting machine.
                        OnInitializationProcess.Invoke(string.Format("{0} {1}", oMsgMgr.GetMessage(CrxStructCommonResourceMsg.SqlServerConnFailed), serverNameString));
                        OnInitializationProcess.Invoke(oMsgMgr.GetMessage(CrxStructCommonResourceMsg.BtnExit));
                        CrxLogger.Instance.Write(oMsgMgr.GetMessage(CrxStructCommonResourceMsg.SqlServerConnFailed) + serverNameString);

                        // Get the list of SQL server instances on the network
                        SQLInstanceList frmObject = new SQLInstanceList { ShowInTaskbar = false };
                        frmObject.ShowDialog();
                    }

                    // user have clicked on cancel
                    if (SQLInstanceList.IsCancel == 1)
                    {
                        OnInitializationProcess.Invoke(oMsgMgr.GetMessage(CrxStructCommonResourceMsg.BtnExit));
                        SQLInstanceList.IsCancel = 0;
                        Close();
                        Process.GetCurrentProcess().Kill();
                        return;
                    }

                    // DB connection string, save in class variable
                    serverNameString = GuiCommon.ServerNameString();
                    InitializeComponent();
                    GuiCommon.SetFontForControls(this);

                    // Set the text for  Capture Tab form controls
                    SetTextForRibbionControl();

                    // Set the metric & height weight unit for Biz validations
                    GuiFieldValidation.SetMeasForBizValidation();

                   // radpgTabCollection.SelectedPage = GuiCommon.TabFocused = guiradgrpbxPwvDistanceMethod;       
                    // SetStartUpModeEnvironmentScreen();

                    // Begin: AtCor-Drop2-Sprint2, TM, SWREQ2003, 06-July-2011                
                    InitializeSetupScreen();
                    radpgTabCollection.SelectedPage = GuiCommon.TabFocused = guiradgrpbxPwvDistanceMethod;       
                    PopulateCurrentModeDropDown();
                    ValidateStartUpMode();
                    SetStrategy(crxMgrObject.GeneralSettings.StartupMode);
                }
                else
                {
                    Process.GetCurrentProcess().Kill();
                }

                // End: AtCor-Drop2-Sprint2, TM, SWREQ2003, 06-July-2011

                // hide splash screen after initialization process
                splsh.Hide();

                // Disable Right Click
                Application.AddMessageFilter(this);
                FormClosed += DsblRghtClk_FormClosed;

                GuiCommon.SetShape(guicmbxCurrentMode);
            }         
            catch (Exception ex)
            {
                // show error type on splash screen, error on message box & quit application
                OnInitializationProcess.Invoke(oMsgMgr.GetMessage(CrxStructCommonResourceMsg.SystemError));
                OnInitializationProcess.Invoke(oMsgMgr.GetMessage(CrxStructCommonResourceMsg.BtnExit));
                GUIExceptionHandler.HandleException(ex, this);               
                Process.GetCurrentProcess().Kill();
            }            
        }

        /** This method disables mouse right click
        * */
        public bool PreFilterMessage(ref Message m)
        {
            // Filter out WM_NCRBUTTONDOWN/UP/DBLCLK
            if (m.Msg == 0xA4 || m.Msg == 0xA5 || m.Msg == 0xA6)
            {
                return true;
            }

            // Filter out WM_RBUTTONDOWN/UP/DBLCLK
            if (m.Msg == 0x204 || m.Msg == 0x205 || m.Msg == 0x206)
            {
                return true;
            }

            return false;
        }        
       
        /** This method disable right click of mouse on whole form 
         */ 
        private void DsblRghtClk_FormClosed(object sender, FormClosedEventArgs e)
        {
            Application.RemoveMessageFilter(this);
        }              

        /**This method is called to set the text for the controls in the ribbon bar.The text is read from the resource file.
        */  
        private void SetTextForRibbionControl()
        {
            guiradmnuSystem.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.MenuSystem);
            guiradmnuDatabase.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.MenuDatabase);
            guiradmnuHelp.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.MenuHelp);
            guiradmnuWebsite.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.GuiMenuSupport);
            guiradgrpbxPwvDistanceMethod.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.Setup);
            radtabCapture.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.TabCapture);
            radtabReport.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.TabReport);
            guiradmnuFindPrinter.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.GuiPrinterSetup);
            guiradmnuitemSettings.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.GuiSettingsMenu);
            guiradmnuFindModule.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.GuiFindModuleMenu);
            guiradmnuExit.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.GuiExitMenu);
            guiradmenuBackup.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.GuiBackupMenu);
            guiradmenuRestore.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.GuiRestoreMenu);
            guiradmnuOperatorManual.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.GuiOperatorGuideMenu);
            guiradmnuServiceManual.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.GuiServiceManualMenu);
            guiradmenuahomepage.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.GuiAtcorHomepageMenu);
            guiradmnuitemAbout.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.GuiAboutMenu);
        }
        
        /**This method is invoked on the click of the Exit button under System menu.
         * It will close the main window.
         */
        private void radButtonElementExit_Click(object sender, EventArgs e)
        {  
            // Close the application on click of Exit button under System menu.
            Close();
        }

        /** This method exits closes the application if startup screen is not found in config file
         * */
        private void ExitApplication()
        {            
            // writes messages on splash screen by invoking OnInitializationProcess
            OnInitializationProcess.Invoke(oMsgMgr.GetMessage(CrxStructCommonResourceMsg.SystemError));
            OnInitializationProcess.Invoke(oMsgMgr.GetMessage(CrxStructCommonResourceMsg.BtnExit));
            RadMessageBox.Show(this, oMsgMgr.GetMessage(CrxStructCommonResourceMsg.CrxErrFileCorrupt), oMsgMgr.GetMessage(CrxStructCommonResourceMsg.SystemError), MessageBoxButtons.OK, RadMessageIcon.Error);
            CrxLogger.Instance.Write(oMsgMgr.GetMessage(CrxStructCommonResourceMsg.CrxErrFileCorrupt));
            Process.GetCurrentProcess().Kill();                       
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
                    if (GuiCommon.IsFormChanged)
                    {
                        logExit = SaveChanges();
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
                    CrxLogger.Instance.Write(oMsgMgr.GetMessage(CrxStructCommonResourceMsg.Exitstr));
                    Process.GetCurrentProcess().Kill();
                }
            }
        }

        /**This method is called when the user wants to save changes before closing the application.
         */ 
        private int SaveChanges()
        {
            int saveChanges = 0; 
            RadMessageBox.SetThemeName(oMsgMgr.GetMessage(CrxStructCommonResourceMsg.MsgDesert));
            DialogResult ds = RadMessageBox.Show(this, oMsgMgr.GetMessage(CrxStructCommonResourceMsg.MsgSaveChange), oMsgMgr.GetMessage(CrxStructCommonResourceMsg.SystemError), MessageBoxButtons.YesNoCancel, RadMessageIcon.Question);

            // Keeping Yes and No separate for future use.                     
            switch (ds)
            {
                case DialogResult.Yes:
                    // save changes before exiting application
                    if (GuiCommon.TabFocused == guiradgrpbxPwvDistanceMethod)
                    {
                        // save changes on setup screen and exit
                        OnExitSaveSetupChanges.Invoke(this, new EventArgs());
                    }
                    else if (GuiCommon.TabFocused == radtabReport)
                    {
                        OnExitSaveReportChanges.Invoke(this, new EventArgs());
                    }

                    saveChanges = GuiCommon.ExitApp;
                    break;
                case DialogResult.No:
                    saveChanges = 0;
                    break;
                default:
                    saveChanges = 1;
                    break;
            }

            return saveChanges;
        }
        
        /**This is invoked on the load of the window.
         *Once the application is launched it will log the event into the log file.
         */
        private void DefaultWindow_Load(object sender, EventArgs e)
        {  
            try
            {
                // Set the windows size to maximum.                 
                WindowState = FormWindowState.Normal;

                EnableMenuBarControls();
                CheckAnnualCalibration();

                // check if we can access the configuration file by reading general setting from config manager object.   
                CrxConfigManager oConfigMgr = CrxConfigManager.Instance;
                oConfigMgr.GetGeneralUserSettings();              

                // Log the event on successful load of the application.                 
                CrxLogger.Instance.Write(oMsgMgr.GetMessage(CrxStructCommonResourceMsg.Startstr));

                // save the current window object for exception handling class
                GuiCommon.DefaultWindowForm = this;

                // Disable the pateint name and Capture time labels
                radlblCaptureTime.Enabled = false;
                radlblPatientName.Enabled = false;

                // setting initial directory for save file dialog box
                // Folders such MyComputer are called virtual folders and they have
                // pre-defined GUIDs that OpenFileDialog can open them. below setting will point to MyComputer folder while taking backup
                saveFileDialog.InitialDirectory = openFileDialog.InitialDirectory = "::{20D04FE0-3AEA-1069-A2D8-08002B30309D}";                
                saveFileDialog.RestoreDirectory = openFileDialog.RestoreDirectory = true;

                // set waiting bar
                guiWaitingStatusBar.WaitingStep = 10;
                guiWaitingStatusBar.WaitingSpeed = 50;
                guiWaitingStatusBar.Visible = false;                

                OnDbBackupAndRestoreCompleteEvent += DisplayStatusComplete;
                Migrate.OnMigrationStart += DoMigration;
                
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
                DialogResult dsResult = RadMessageBox.Show(this, oMsgMgr.GetMessage(CrxStructCommonResourceMsg.MigrateFileMsg1) + Environment.NewLine + oMsgMgr.GetMessage(CrxStructCommonResourceMsg.MigrateFileMsg2), oMsgMgr.GetMessage(CrxStructCommonResourceMsg.SystemError), MessageBoxButtons.YesNo, RadMessageIcon.Info);

                if (dsResult == DialogResult.Yes)
                {
                    #region Commenting this peice of code as it we are not showing group names during migration
                    /*
                    // redirect to migrate screen to select group
                    Migrate migrt = new Migrate { ShowInTaskbar = false };
                    migrt.ShowDialog();

                    * Migrate.IsMigrate =1> indicates user responded "yes" to data migration                     
                    if (Migrate.IsMigrate == 1)
                    {*/
                    #endregion

                    // This is hardcoded as it needs to be saved into the config file in English.
                    // Localising  this string will result into error on the capture screen.
                    const string groupName = "Clinical";
                    DoMigration(groupName);

                    // start waiting progress bar on main thread
                        guiWaitingStatusBar.Visible = true;
                        guiWaitingStatusBar.StartWaiting();

                        // disable menu & tab page while restore is on
                        guiradmnuScor.Enabled = false;
                        radpgTabCollection.Enabled = false;

                   // }
                }
            }
        }

        /** This method migrates records
         * */
        void DoMigration(string groupname)
        { 
            // call method to migrate records 
            Thread migThread = new Thread(StartMigration);
            radlblMessage.Text = string.Empty; 
            migThread.Start(groupname);
        }

        /** This method starts data migration
         * */
        void StartMigration(object groupname)
        {
           // code to migrate data
            try
            {
                /***
                 * Result => 0 success
                 * result != 0 failed
                 */
                int result = dbMagr.MigrateAtCorData(GuiCommon.SystemIdentifier, groupname.ToString());

                if (0 == result)
                {
                    dbOperation = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.MigrationSuccessMessage);

                    // Invoke methods to stop progressbasr & reload setup screen
                    OnRestoreCompleteSuccess.Invoke(this, new EventArgs());
                    OnDbBackupAndRestoreCompleteEvent.Invoke(this, new EventArgs());
                }
                else
                {
                    dbOperation = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.MigrationFail);

                    // Invoke methods to stop progressbasr & reload setup screen
                    OnDbBackupAndRestoreCompleteEvent.Invoke(this, new EventArgs());                    
                }
            }         
            catch (Exception ex)
            {
                // on exception stop waiting bar & show error message
                if (InvokeRequired)
                {
                    dbOperation = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.MigrationFail);
                    OnDbBackupAndRestoreCompleteEvent.Invoke(this, new EventArgs());

                    ExceptionHandler exc = GUIExceptionHandler.HandleException;
                    Invoke(exc, ex, this);
                }
            } 
        }
              
        #region Code to check multiple instance of application.
        private bool IsProcessOpen(string name)
        {
            try
            {
                int count = Process.GetProcesses().Count(clsProcess => clsProcess.ProcessName.Equals(name));
                return count > 1;
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
            if (GuiCommon.SetupChildForm != null)
            {
                GuiCommon.SetupChildForm.Close();
                GuiCommon.SetupChildForm = null;
            }
            
            GuiCommon.SetupChildForm = new Setup(this)
                                                    {
                                                        TopLevel = false,
                                                        Dock = DockStyle.Fill,
                                                        FormBorderStyle = FormBorderStyle.None
                                                    };

            // adds report form under parent window control
            var page = radpgTabCollection.Pages[0];

            GuiCommon.SetupChildForm.Parent = page;

            page.Controls.Add(GuiCommon.SetupChildForm);

            GuiCommon.SetupChildForm.Show();
        }
       
        /** This event is fired when the user clicks tried to click on the OperatorGuide option on the menu bar.
        */
        private void guiradmnuitemOperatorGuide_Click(object sender, EventArgs e)
        {
            try
            {
                if (File.Exists(ConfigurationManager.AppSettings[GuiConstants.AppConfigParams.OperatorGuidePath.ToString()].Replace("{culture}", Program.GetCurrentCulture())))
                {
                    Process.Start(Path.GetFullPath(ConfigurationManager.AppSettings[GuiConstants.AppConfigParams.OperatorGuidePath.ToString()].Replace("{culture}", Program.GetCurrentCulture())));
                }
                else
                {
                    RadMessageBox.Show(this, oMsgMgr.GetMessage(CrxStructCommonResourceMsg.PdfFileError), oMsgMgr.GetMessage(CrxStructCommonResourceMsg.SystemError), MessageBoxButtons.OK, RadMessageIcon.Error);
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
                if (File.Exists(ConfigurationManager.AppSettings[GuiConstants.AppConfigParams.ServiceManualPath.ToString()].Replace("{culture}", Program.GetCurrentCulture())))
                {
                    Process.Start(Path.GetFullPath(ConfigurationManager.AppSettings[GuiConstants.AppConfigParams.ServiceManualPath.ToString()].Replace("{culture}", Program.GetCurrentCulture())));
                }
                else
                {
                    RadMessageBox.Show(this, oMsgMgr.GetMessage(CrxStructCommonResourceMsg.PdfFileError), oMsgMgr.GetMessage(CrxStructCommonResourceMsg.SystemError), MessageBoxButtons.OK, RadMessageIcon.Error);
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
            Process.Start(ConfigurationManager.AppSettings[GuiConstants.AppConfigParams.SupportUrl.ToString()]);
        }

        /** This method is called to Enable the menu controls.
         */ 
        private void EnableMenuBarControls()
        {
            guiradmnuScor.MenuElement.SystemButtons.Visibility = ElementVisibility.Visible;
            guiradmnuScor.MenuElement.CloseButton.Click += CloseButton_Click;
            guiradmnuScor.MenuElement.MinimizeButton.Click += MinimizeButton_Click;
        }

        /** This event is fired when the user clicks on the close button.
         */ 
        private void CloseButton_Click(object sender, EventArgs e)
        {
            // close the application
            Close();
        }

        /** This event is fired when the user clicks on the minimze button on the title bar.
         */ 
        private void MinimizeButton_Click(object sender, EventArgs e)
        {
            WindowState = FormWindowState.Minimized;            
        }
        
        /**This method is invoked when Settings button under System tab is clicked. 
         * It opens setting window
         */ 
        private void guiradmnuSettings_Click(object sender, EventArgs e)
        {
            try
            {
                // invoke method on setup screen which will check if the current mode is insert & new then prompt the user
                // to save changes before navigating to setup screen
                SaveChangeOnNavigatingMenu(sender, e);

                // Open the settings dialog box. 
                if (GuiCommon.IsMenuItemShown)
                {
                    var settingWinObject = new frmSettingsWindow { ShowInTaskbar = false };
                     
                    settingWinObject.ShowDialog();
                }               
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

                SaveChangeOnNavigatingMenu(sender, e);
                if (IsPatientListOnSetupEmpty())
                {
                    return;
                }

                if (GuiCommon.IsMenuItemShown)
                {
                    // opens folder dialog box to select location
                    saveFileDialog.FileName = ConfigurationManager.AppSettings[GuiConstants.AppConfigParams.DbDefaultFileName.ToString()] + ConfigurationManager.AppSettings[GuiConstants.AppConfigParams.DbVersionNumber.ToString()] + BackupFileExt;
                    saveFileDialog.Title = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.BackupTitle);
                    DialogResult result = saveFileDialog.ShowDialog();

                    if (result == DialogResult.OK)
                    {
                        Directory.SetCurrentDirectory(currentpath);
                        dbOperation = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.BackupTitle);

                        // save backup operation started on separate thread
                        Thread startDbBackup = new Thread(SaveBackupFile);
                        startDbBackup.Start();

                        // start waiting progress bar on main thread
                        guiWaitingStatusBar.Visible = true;
                        guiWaitingStatusBar.StartWaiting();

                        // disable menu & tab page while backup is on
                        guiradmnuScor.Enabled = false;
                        radpgTabCollection.Enabled = false;
                    }
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
                string path = saveFileDialog.FileName;

                // log backup start process
                CrxLogger.Instance.Write(oMsgMgr.GetMessage(CrxStructCommonResourceMsg.BackupProgress));

                DoBackup(path);               
            }         
            catch (Exception ex)
            {
                if (InvokeRequired)
                {
                    dbOperation = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.BackupFail);
                    OnDbBackupAndRestoreCompleteEvent.Invoke(this, new EventArgs());

                    ExceptionHandler excep = GUIExceptionHandler.HandleException;
                    Invoke(excep, ex, this);
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
                int success = !Path.GetExtension(path).Equals(BackupFileExt, StringComparison.CurrentCultureIgnoreCase) ? dbMagr.DatabaseBackup(path + BackupFileExt) : dbMagr.DatabaseBackup(path);

                // on backup success invoke event to display status message
                if (success == 0)
                {
                    dbOperation = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.BackupDone);
                    OnDbBackupAndRestoreCompleteEvent.Invoke(this, new EventArgs());
                }
            }
            else
            {
                dbOperation = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.BackupFail);
                OnDbBackupAndRestoreCompleteEvent.Invoke(this, new EventArgs());

                DisplayStatusMessageDelegate messageBox = ShowConnectionError;
                Invoke(messageBox, dbOperation); 
            }
        }
           
        /** This method shows network connection failure message for restore & backup operations
         * */
        void ShowConnectionError(string message)
        {
            // show error message db connection failed
            DialogResult result = RadMessageBox.Show(this, GuiCommon.ConnectionErrorString(), oMsgMgr.GetMessage(CrxStructCommonResourceMsg.SystemError), MessageBoxButtons.RetryCancel, RadMessageIcon.Error);
            if (result == DialogResult.Retry)
            {
                Invoke(dbOperation.Equals(  
                                          oMsgMgr.GetMessage(CrxStructCommonResourceMsg.BackupFail),
                                          StringComparison.CurrentCultureIgnoreCase) ? new EventHandler(guiradmenuBackup_Click) : new EventHandler(guiradmenuRestore_Click));
            }
        }

        /** This event shows backup & restore status messages after its completion & stops waiting bar
         * */
        private void DisplayStatusComplete(object sender, EventArgs e)
        {
            // if invoked from other thread call the appropriate method
            if (InvokeRequired)
            {
                Invoke(new EventHandler(DisplayStatusComplete));
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
            OnRestoreOptionClick.Invoke(this, new EventArgs());     
        }

        /**This method is called when the Setup, Capture or Report tab is selected.
       */ 
        private void radpgTabCollection_SelectedPageChanged(object sender, EventArgs e)
        {
            try
            {
                guiradmnuitemSettings.Enabled = true;
                guiradmnuSystemKey.Enabled = true;

                // read the coms port and simulation type.
                if (radpgTabCollection.SelectedPage.Text.Equals(oMsgMgr.GetMessage(CrxStructCommonResourceMsg.TabCapture), StringComparison.CurrentCultureIgnoreCase))
                {
                    if (guicmbxCurrentMode.Text != CrxStructCommonResourceMsg.Pwa)
                    {
                        NavigateToCapture();

                        GuiCommon.TabFocused = radtabCapture;
                        GuiCommon.IsFormChanged = false;

                        // User is navigating away from the Report screen.
                        GuiCommon.IsOnReportForm = false;
                        GuiCommon.CheckIfMandatoryFieldIsEmpty();
                    }
                }
                else if (radpgTabCollection.SelectedPage.Text.Equals(oMsgMgr.GetMessage(CrxStructCommonResourceMsg.TabReport), StringComparison.CurrentCultureIgnoreCase))
                {
                    NavigateToReport();
                   
                    GuiCommon.TabFocused = radtabReport;
                    GuiCommon.IsFormChanged = false;
                }
                else if (radpgTabCollection.SelectedPage.Text.Equals(oMsgMgr.GetMessage(CrxStructCommonResourceMsg.Setup), StringComparison.CurrentCultureIgnoreCase))
                {                   
                    NavigateToSetup();
                   
                    GuiCommon.TabFocused = guiradgrpbxPwvDistanceMethod;

                    // User is navigating away from the Report screen.
                    GuiCommon.IsOnReportForm = false;
                    GuiCommon.IsFormChanged = false;
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

                if (GuiCommon.CaptureTabClick)
                {                   
                   OnCaptureTabClick.Invoke(this, new EventArgs());            
                }

                GuiCommon.CaptureTabClick = true;
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
            radtabCapture.Enabled = !GuiCommon.IsWaitIntervalImposed;            

            // InitializeSetupScreen(); 
            radtabReport.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.TabReport);
            radlblCaptureTime.Text = string.Empty;
            radtabReport.Enabled = GuiCommon.HasMeasurementDetails;

            GuiCommon.CaptureToReport = false;
            OnSetupScreenTabClick.Invoke(this, new EventArgs());
        }

        /**This method will navigate the user to the Report screen.
         */ 
        private void NavigateToReport()
        {
            if (!radtabReport.Enabled)
            {
                return;
            }

            GuiCommon.SetupToReport = GuiCommon.CaptureToReport ? false : true;

            if (GuiCommon.ReportLoadCount == 1)
            {
                GuiCommon.ReportLoadCount++;                
            }
            else
            {
                LoadReportScreen();
            }

            // disable setting tab on menu bar
            guiradmnuitemSettings.Enabled = false;
            guiradmnuSystemKey.Enabled = false;
        }

        /** This method invokes load event of report screen
         * It binds the record for selected patient on setup screen in report
         * */
        private void LoadReportScreen()
        {
            // as report form is already loaded in memory, in order to refresh its data
            // we need to generate events, which in turn reloads the report screen data.
            GuiCommon.ScorControllerObject.LoadReport();          
        }              

        /** This method initialises report screen 
         * */
        void InitializeReportScreen()
        {
            GuiCommon.SetupToReport = true;

            // open report form under report tab
            if (GuiCommon.ReportChildForm != null)
            {
                GuiCommon.ReportChildForm.Close();
                GuiCommon.ReportChildForm.Dispose();
            }

            // uncomment me 
            if (GuiCommon.PWAReportChildForm != null)
            {
                GuiCommon.PWAReportChildForm.Close();
                GuiCommon.PWAReportChildForm.Dispose();
            } 

            GuiCommon.ReportChildForm = new Report(this)
                                                     {
                                                         TopLevel = false,
                                                         Dock = DockStyle.Fill,
                                                         FormBorderStyle = FormBorderStyle.None
                                                     };
            
            // adds report form under parent window control
            var page = radpgTabCollection.Pages[2];

            GuiCommon.ReportChildForm.Parent = page;
            page.Controls.Add(GuiCommon.ReportChildForm);

            GuiCommon.ReportChildForm.Show();            
            page.Controls[GuiCommon.ReportChildForm.Name].BringToFront();         
        }

        /**This method is used to initialise the Report screen in PWA mode.
       */
        private void InitializePWAReportScreen()
        {
            try
            {
                GuiCommon.SetupToReport = true;

                // open report form under report tab
                if (GuiCommon.PWAReportChildForm != null)
                {
                    GuiCommon.PWAReportChildForm.Close();
                    GuiCommon.PWAReportChildForm.Dispose();
                }

                // open report form under report tab
                if (GuiCommon.ReportChildForm != null)
                {
                    GuiCommon.ReportChildForm.Close();
                    GuiCommon.ReportChildForm.Dispose();
                }

                GuiCommon.PWAReportChildForm = new PWAReport(this)
                {
                    TopLevel = false,
                    Dock = DockStyle.Fill,
                    FormBorderStyle = FormBorderStyle.None
                };

                // adds report form under parent window control
                var page = radpgTabCollection.Pages[2];                

                GuiCommon.PWAReportChildForm.Parent = page;
                page.Controls.Add(GuiCommon.PWAReportChildForm);              
                
                GuiCommon.PWAReportChildForm.Show();
                page.Controls[GuiCommon.PWAReportChildForm.Name].BringToFront();                
            }
            catch (Exception ex)
            {
                GUIExceptionHandler.HandleException(ex, this);
            }
        }

        /** This event fires when restore button is clicked on menu bar
         * */
        private void guiradmenuRestore_Click(object sender, EventArgs e)
        {
            try
            {
                radlblMessage.Text = string.Empty;

                SaveChangeOnNavigatingMenu(sender, e);

                if (GuiCommon.IsMenuItemShown)
                {
                    // prompt user before restoring backup
                    DialogResult dg = RadMessageBox.Show(this, oMsgMgr.GetMessage(CrxStructCommonResourceMsg.RestoreMsg), oMsgMgr.GetMessage(CrxStructCommonResourceMsg.SystemError), MessageBoxButtons.YesNo, RadMessageIcon.Info);

                    if (dg == DialogResult.Yes)
                    {
                        // continue with restore backup
                        // sets title for dialog box
                        openFileDialog.Title = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.RestoreTitle);
                        DialogResult result = openFileDialog.ShowDialog();

                        if (result == DialogResult.OK)
                        {
                            Directory.SetCurrentDirectory(currentpath);

                            // check for .bak file extension and restore backup
                            if (Path.GetExtension(openFileDialog.FileName).Equals(BackupFileExt, StringComparison.CurrentCultureIgnoreCase))
                            {
                                // restore backup operation on separate thread
                                Thread startDbRestore = new Thread(RestoreBackupFile);
                                startDbRestore.Start();

                                // start waiting progress bar on main thread
                                guiWaitingStatusBar.Visible = true;
                                guiWaitingStatusBar.StartWaiting();

                                // disable menu & tab page while restore is on
                                guiradmnuScor.Enabled = false;
                                radpgTabCollection.Enabled = false;
                            }
                            else
                            {
                                RadMessageBox.Show(this, oMsgMgr.GetMessage(CrxStructCommonResourceMsg.RestoreFileMsg), oMsgMgr.GetMessage(CrxStructCommonResourceMsg.SystemError), MessageBoxButtons.OK, RadMessageIcon.Error);
                            }
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
                string path = openFileDialog.FileName;

                // set current directory for resource file
                dbOperation = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.RestoreTitle);
                        
                // log message for restore started
                CrxLogger.Instance.Write(oMsgMgr.GetMessage(CrxStructCommonResourceMsg.RestoreProgress));

                if (dbMagr.CheckConnection(serverNameString, crxMgrObject.GeneralSettings.SourceData) == 0)
                {
                    // restore database
                    int success = dbMagr.DatabaseRestore(path);

                    // on success of restore invoke event to show message
                    if (success == 0)
                    {
                        dbOperation = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.RestoreDone);

                      // Invoke methods to stop progressbasr & reload setup screen
                       OnRestoreCompleteSuccess.Invoke(this, new EventArgs());
                       OnDbBackupAndRestoreCompleteEvent.Invoke(this, new EventArgs());
                    }
                }
                else
                {
                    dbOperation = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.RestoreFail);
                    OnDbBackupAndRestoreCompleteEvent.Invoke(this, new EventArgs());

                    DisplayStatusMessageDelegate messageBox = ShowConnectionError;
                    Invoke(messageBox, dbOperation);                        
                }
            }
            catch (Exception ex)
            {
                if (InvokeRequired)
                {
                    dbOperation = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.RestoreFail);
                    OnDbBackupAndRestoreCompleteEvent.Invoke(this, new EventArgs());

                    ExceptionHandler handle = GUIExceptionHandler.HandleException;
                    Invoke(handle, ex, this);                                     
                }
            }           
        }

        /**This event fires when Atcor Homepage menu item is selected
      */
        private void guiradmenuahomepage_Click(object sender, EventArgs e)
        {
            Process.Start(ConfigurationManager.AppSettings[GuiConstants.AppConfigParams.AtcorHomepage.ToString()]);
        }

        /**This method will display the error message using the message box.
       */
        private void DisplayErrorMessage(string errorMessage)
        {
            if (InvokeRequired)
            {
                Invoke(new DisplayStatusMessageDelegate(DisplayErrorMessage));
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
            GuiCommon.ViewPrintDialogToSetPrinter(guiFindPrinterDialog);            
        }

        /** This event fires when Find module option is click from top Systems menu
         * It finds electronic module and shows appropriate messages
         * */
        private void guiradmnuFindModule_Click(object sender, EventArgs e)
        {
            try
            {
                SaveChangeOnNavigatingMenu(sender, e);

                if (GuiCommon.IsMenuItemShown)
                {
                    // find module in a different thread... this will display messages alternatively as per status   
                    Thread findMod = new Thread(FindElectronicModule);
                    findMod.Start();
                }
            }
            catch (Exception ex)
            {
                GUIExceptionHandler.HandleException(ex, this);
            }
        }

        /** This method checks if user is on setup or report screen and promts user to save any changes made on those screens
         * before navigating to top menu items
         */
        private void SaveChangeOnNavigatingMenu(object sender, EventArgs e)
        {
            if (GuiCommon.TabFocused == guiradgrpbxPwvDistanceMethod)
            {
                OnSetupMenuItemClick.Invoke(sender, e);
            }
            else if (GuiCommon.TabFocused == radtabReport)
            {
                OnReportMenuItemClick.Invoke(sender, e);
            }
        }

        /** This method searches for electronic module and shows appropriate messages
         * */
        private void FindElectronicModule()
        {
            try
            {
                DisplayStatusMessageDelegate messageBox = DisplayErrorMessage;
                Invoke(messageBox, oMsgMgr.GetMessage(CrxStructCommonResourceMsg.GuiSearchElectronicMod));

                // with out following wait, earlier message is not displayed.
                // Thread.Sleep(2000);

                // search module
                string portName = string.Empty;
                
                // int retValue = DalModule.Instance.FindModule(ref portName);

                /**  FindModule call returns integer
                 *  0 => module not found
                 *  1 => module found
                 *  2 => module found on different port
                 * */
                switch (DalModule.Instance.FindModule(ref portName))
                {  
                    case DalFindModuleResult.ModuleNotFound: // module not found
                        CrxLogger.Instance.Write(oMsgMgr.GetMessage(CrxStructCommonResourceMsg.CaptureDeviceErrMsg));
                        DisplayStatusMessageDelegate findModuleErrorMessage = ShowFindModuleError;
                        Invoke(findModuleErrorMessage, oMsgMgr.GetMessage(CrxStructCommonResourceMsg.GuiElectronicModNotfnd));
                         
                        break;

                    case DalFindModuleResult.ModuleFoundOnConfigPort: // module present on port , show message to user                    
                        Invoke(messageBox, oMsgMgr.GetMessage(CrxStructCommonResourceMsg.GuiElectronicModFnd));
                        break;

                    case DalFindModuleResult.ModuleFoundOnDifferentPort: // module found on different port , show message to user
                        Invoke(messageBox, oMsgMgr.GetMessage(CrxStructCommonResourceMsg.GuiElectronicModFndport) + portName);
                        break;

                    default:
                        break;
                }
            }
            catch (Exception ex)
            {
                if (InvokeRequired)
                {
                    ExceptionHandler excep = GUIExceptionHandler.HandleException;
                    Invoke(excep, ex, this);
                }
            }
        } // End FindElectronicModule

        /** This method is called when module is not found.
         * It displays error message asking user to continue with search for module
         * */
        void ShowFindModuleError(string message)
        {
            radlblMessage.Text = string.Empty;

            // ask user if another search is required                        
            DialogResult ds = RadMessageBox.Show(this, message, oMsgMgr.GetMessage(CrxStructCommonResourceMsg.SystemError), MessageBoxButtons.YesNo, RadMessageIcon.Info);
            if (ds == DialogResult.Yes)
            {
                // find module again
                FindElectronicModule();
            }           
        }

        /** This event fires when interval imposed by EM4 device (currently configured in app.config) lapses
         * It disables the timer & enables capturetab & capture buttons on setup & report screen
         * */
        private void tmrImposeWaitTime_Tick(object sender, EventArgs e)
        {
            try
            {
                tmrImposeWaitTime.Enabled = false;
                GuiCommon.IsWaitIntervalImposed = false;
                GuiCommon.InvokeCaptureClosing(true);
            }
            catch (Exception ex)
            {
                GUIExceptionHandler.HandleException(ex, this);
                Close();
            }
        }

        /**This event is fired when the user tries to navigate across the page view,
         * using the direction keys on the keyboard.
         */ 
        private void DefaultWindow_KeyDown(object sender, KeyEventArgs e)
        {
            try
            {
                if (!radpgTabCollection.SelectedPage.Enabled)
                {
                    if (e.KeyCode == Keys.Left || e.KeyCode == Keys.Right || e.KeyCode == Keys.RButton)
                    {
                        e.SuppressKeyPress = true;
                    }
                }
            }
            catch (Exception ex)
            {
                GUIExceptionHandler.HandleException(ex, this);
                Close();
            }
        }

        /**This event is fired when the user clicks on one of the tabs.
         * When the user clicks on the Capture tab we invoke the load of the capture form.
         */ 
        private void radpgTabCollection_Click(object sender, EventArgs e)
        {
            // if (radpgTabCollection.SelectedPage.Text.Equals(oMsgMgr.GetMessage(CrxStructCommonResourceMsg.TabCapture), StringComparison.CurrentCultureIgnoreCase))
            // {
            //    // When the capture form has loaded ,this event is invoked.
            //    if (GuiCommon.CaptureFormLoaded)
            //    {
            //        OnCaptureScreenTabClick.Invoke(this, new EventArgs());
            //    }
            //    else
            //    {
            //        radpgTabCollection.SelectedPage = guiradgrpbxPwvDistanceMethod;
            //        guiradgrpbxPwvDistanceMethod.Enabled = true;
            //    }
            // } 
        }                     

        /** This method is called to check the start up screen,machine name and the soruce data of the application,
         * from the configuration file.
         */ 
        private void CheckMachineNameOnStartUp()
        {
            if (string.IsNullOrEmpty(crxMgrObject.GeneralSettings.StartupScreen))
            {
                ExitApplication();
            }
                          
            if (string.IsNullOrEmpty(crxMgrObject.GeneralSettings.MachineName))
            {
                crxMgrObject.GeneralSettings.MachineName = SystemInformation.ComputerName;
                CrxLogger.Instance.Write(oMsgMgr.GetMessage(CrxStructCommonResourceMsg.SqlServerChangedToLocal));
            }
           
            if (string.IsNullOrEmpty(crxMgrObject.GeneralSettings.SourceData))
            {
                crxMgrObject.GeneralSettings.SourceData = GuiConstants.SourceData;
                CrxLogger.Instance.Write(oMsgMgr.GetMessage(CrxStructCommonResourceMsg.SqlServerChangedToDefault));
            }
        }

        /** This method is used to check the annual calibration of the EM4 device.
         */ 
        private void CheckAnnualCalibration()
        {
            try
            {
                DateTime calibrationDate = DalModule.Instance.GetLastCalibrationDate();
                if (calibrationDate < DateTime.Now)
                {
                    RadMessageBox.Show(this, string.Format(oMsgMgr.GetMessage(CrxStructCommonResourceMsg.GuiAnnualCallibrationMesg), calibrationDate), oMsgMgr.GetMessage(CrxStructCommonResourceMsg.SystemError), MessageBoxButtons.OKCancel, RadMessageIcon.Info);
                }
            }
            catch (Exception ex)
            {
                GUIExceptionHandler.HandleException(ex, this);
                Close();
            }
        }

        private void DefaultWindow_Activated(object sender, EventArgs e)
        {
            Height = Screen.PrimaryScreen.WorkingArea.Height;
            Width = Screen.PrimaryScreen.WorkingArea.Width;
            Left = Screen.PrimaryScreen.WorkingArea.Left;
            Top = Screen.PrimaryScreen.WorkingArea.Top;

            guiradpnlDefaultWin.Top = (Screen.PrimaryScreen.WorkingArea.Height / 2) - (guiradpnlDefaultWin.Height / 2);
            guiradpnlDefaultWin.Left = (Screen.PrimaryScreen.WorkingArea.Width / 2) - (guiradpnlDefaultWin.Width / 2);
        }

        /**This method is used to check if the patient list on the setup screen is empty or not.
         * Accordingly it returns a boolean value.
         */ 
        private bool IsPatientListOnSetupEmpty()
        {
            if (GuiCommon.IsPatientListEmpty)
            {
                GuiCommon.IsPatientListEmpty = false;
                return true;
            }
            else
            {
                return false;
            }
        }

        // Begin: AtCor-Drop2-Sprint2, TM, SWREQ2003, 06-July-2011
        /**Populating drop down for Current mode from BizInfo class.
         */ 
        private void PopulateCurrentModeDropDown()
        {
            try
            {
                RadListDataItem mode; 
                List<string> modeList = new List<string>();
                guicmbxCurrentMode.Items.Clear();   
                if (BizInfo.Instance().OptionPWV)
                {
                    // guicmbxCurrentMode.Items.Add(oMsgMgr.GetMessage(CrxStructCommonResourceMsg.Pwv));                                       
                    modeList.Add(oMsgMgr.GetMessage(CrxStructCommonResourceMsg.Pwv));
                }

                if (BizInfo.Instance().OptionCPWA || BizInfo.Instance().OptionTPWA)
                {
                    // guicmbxCurrentMode.Items.Add(oMsgMgr.GetMessage(CrxStructCommonResourceMsg.Pwa));
                    modeList.Add(oMsgMgr.GetMessage(CrxStructCommonResourceMsg.Pwa));
                }
             
                foreach (string t in modeList)
                {
                    mode = new RadListDataItem { Text = t.ToString(), Value = t.ToString() };
                    guicmbxCurrentMode.Items.Add(mode);
                }
                  
                if (guicmbxCurrentMode.Items.Count > 0)
                {
                    guicmbxCurrentMode.SelectedIndex = 0;
                }

                // if (BizInfo.Instance().OptionTPWA)
                // {
                //    guicmbxCurrentMode.Items.Add("TPWA");
                // }
            }
            catch (Exception ex)
            {
                GUIExceptionHandler.HandleException(ex, this);                
            }
        }

        /**This method is used to validate the current mode in the scor.config with the available modes
         * in the System key.
         */         
        private void ValidateStartUpMode()
        {
            try
            {
                if ((!crxMgrObject.GeneralSettings.StartupMode.Equals(string.Empty)) && crxMgrObject.GeneralSettings.StartupMode.Equals(CrxStructCommonResourceMsg.Pwv) && BizInfo.Instance().OptionPWV && (!crxMgrObject.GeneralSettings.StartupScreen.Equals(oMsgMgr.GetMessage(CrxStructCommonResourceMsg.QuickStart))))
                {
                   ValidatePWVMode();
                   return;
                }
                else if ((!crxMgrObject.GeneralSettings.StartupMode.Equals(string.Empty)) && crxMgrObject.GeneralSettings.StartupMode.Equals(CrxStructCommonResourceMsg.Pwa) && (BizInfo.Instance().OptionCPWA || BizInfo.Instance().OptionTPWA))
                {
                   ValidatePWAMode();
                   return;
                }
                else
                {
                    splsh.Close();
                    RadMessageBox.Show(this, oMsgMgr.GetMessage(CrxStructCommonResourceMsg.ModeMismatchMsg), oMsgMgr.GetMessage(CrxStructCommonResourceMsg.SystemError), MessageBoxButtons.OK, RadMessageIcon.Exclamation);

                    // Logging the above message into the log file.
                    CrxLogger.Instance.Write(oMsgMgr.GetMessage(CrxStructCommonResourceMsg.ModeMismatchMsg));   

                    // Log the System key, startup mode, startup screen into the log file.
                    CrxLogger.Instance.Write(String.Format("SystemKey: {0},StartupMode: {1}, StartUp Screen: {2}", crxMgrObject.GeneralSettings.Key, crxMgrObject.GeneralSettings.StartupMode, crxMgrObject.GeneralSettings.StartupScreen));   

                    // What should happen to the application after showing the pop up box.
                    Process.GetCurrentProcess().Kill();                                        
                }
            }
            catch (Exception ex)
            {
                GUIExceptionHandler.HandleException(ex, this);
            }
        }

        /**This method is used to set the stratergy as to in which mode should the application be launched.
     */
        private void SetStrategy(string sMode)
        {
            try
            {
                if (sMode == CrxStructCommonResourceMsg.Pwv)
                {
                    GuiCommon.CurrentMode = CrxStructCommonResourceMsg.Pwv;
                    GuiCommon.ScorControllerObject.SetScorStrategy(new Pwv());  

                    // Do GUI changes accordingly.
                    SetPWVMode();                                    
                }

                if (sMode == CrxStructCommonResourceMsg.Pwa)
                {
                    GuiCommon.ScorControllerObject.SetScorStrategy(new CuffPwa());
                    GuiCommon.CurrentMode = CrxStructCommonResourceMsg.Pwa; 

                    // Do GUI changes accordingly.
                    SetPWAMode();
                }
            }
            catch (Exception ex)
            {
                GUIExceptionHandler.HandleException(ex, this);
                Close();
            }
        }

        /**This method is used to set the GUI as per the PWV mode.
         */ 
        private void SetPWAMode()
        {
            try
            {
                // string startUpScreen = crxMgrObject.GeneralSettings.StartupScreen;
                // string environment = BizInfo.Instance().OptionResearch == true ? "Research" : "Clinical";
                CrxStructGeneralSetting crxGen = new CrxStructGeneralSetting();

                crxMgrObject.GetGeneralDefaultSettings(crxGen);

                if (string.IsNullOrEmpty(crxGen.StartupScreen))
                {
                    ExitApplication();
                }

                // set up mode texts on startup screen.
                // guicmbxCurrentMode.Text = crxGen.StartupMode;

                // setup environment label on startup screen.
                SetEnvironment();

                // display message on the splash screen
                OnInitializationProcess.Invoke(string.Format("{0} {1} {2}", oMsgMgr.GetMessage(CrxStructCommonResourceMsg.SplashIniMsg), crxMgrObject.GeneralSettings.StartupMode, oMsgMgr.GetMessage(CrxStructCommonResourceMsg.Mode)));

                //// initalize setup screen
                // InitializeSetupScreen();

                // initialize report screen at the time of application launch
                InitializePWAReportScreen();

                // Hide/Show Controls on the screen based on mode
                DisplayPWAMode();
            }
            catch (Exception ex)
            {
                GUIExceptionHandler.HandleException(ex, this);
                Close();
            }
        }

        // End: AtCor-Drop2-Sprint2, TM, SWREQ2003, 06-July-2011

        /** This method sets Startup mode, startup screen & environment variables & initializes setup screen
         * */
        private void SetPWVMode()
        {
            try
            {
                // string startUpScreen = crxMgrObject.GeneralSettings.StartupScreen;
                // string environment = BizInfo.Instance().OptionResearch == true ? "Research" : "Clinical";
                CrxStructGeneralSetting crxGen = new CrxStructGeneralSetting();

                crxMgrObject.GetGeneralDefaultSettings(crxGen);

                if (string.IsNullOrEmpty(crxGen.StartupScreen))
                {
                    ExitApplication();
                }

                // set up mode texts on startup screen.
                // guicmbxCurrentMode.Text = crxGen.StartupMode;
                SetEnvironment();

                // display message on the splash screen
                OnInitializationProcess.Invoke(string.Format("{0} {1} {2}", oMsgMgr.GetMessage(CrxStructCommonResourceMsg.SplashIniMsg), crxMgrObject.GeneralSettings.StartupMode, oMsgMgr.GetMessage(CrxStructCommonResourceMsg.Mode)));

                // Initalize setup screen
                // InitializeSetupScreen();

                // initialize report screen at the time of application launch
                InitializeReportScreen();

                // Hide/Show Controls on the screen based on mode
                DisplayPWVMode();
            }
            catch (Exception ex)
            {
                GUIExceptionHandler.HandleException(ex, this);
                Close();
            }
        }

        /**This method is used to set the environment of the application.
         */ 
        private void SetEnvironment()
        {            
            // setup environment label on startup screen.
            guiradlblEnvironment.BringToFront();
            guiradlblEnvironment.Focus();
            if (BizInfo.Instance().OptionResearch)
            {
                guiradlblEnvironment.Text = CrxCommon.ApplicationEnvironment = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.ResearchEnv); // "Research";
            }
            else
            {
                guiradlblEnvironment.Text = CrxCommon.ApplicationEnvironment = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.ClinicalEnv); // "Clinical";
            }
        }

        /**This method is used to display the application in PWV mode.
         */ 
        private void DisplayPWVMode()
        {
            GuiCommon.SetupChildForm.Controls["guipnlMeasurementDetails"].Visible = true;
            GuiCommon.SetupChildForm.Controls["guipnlMeasurementDetails"].BringToFront(); 
            GuiCommon.SetupChildForm.Controls["guipnlPWAMeasurementDetails"].Visible = false;
            GuiCommon.SetupChildForm.Controls["guipnlPWAMeasurementDetails"].SendToBack();
            OnModeChangeEvent.Invoke(this, new EventArgs());
            /*To be used in future sprints.
            radtabCapture.Item.Visibility = ElementVisibility.Visible;
            guiradgrpbxPwvDistanceMethod.Item.Visibility = ElementVisibility.Visible;
            radtabReport.Item.Visibility = ElementVisibility.Visible;
            // this will be used for quickstart
                radtabTestResults.Item.Visibility = ElementVisibility.Hidden;
                radtabQuickStart.Item.Visibility = ElementVisibility.Hidden;
                        
            radpgTabCollection.Pages.ChangeIndex(guiradgrpbxPwvDistanceMethod, 1);
            radpgTabCollection.Pages.ChangeIndex(radtabCapture, 2);
            radpgTabCollection.Pages.ChangeIndex(radtabReport, 3);
            // this will be used for quickstart
                radpgTabCollection.Pages.ChangeIndex(radtabQuickStart, 0);
                radpgTabCollection.Pages.ChangeIndex(radtabTestResults, 4);*/

            // Check if the user is on the Report screen, if yes then do not navigate it to the Setup screen.
            if (!GuiCommon.IsOnReportForm)
            {
                radpgTabCollection.SelectedPage = guiradgrpbxPwvDistanceMethod;
                GuiCommon.TabFocused = guiradgrpbxPwvDistanceMethod;
            }
        }

        /**This method is used to display the application in PWA mode.
         */ 
        private void DisplayPWAMode()
        {
            GuiCommon.SetupChildForm.Controls["guipnlMeasurementDetails"].Visible = false;
            GuiCommon.SetupChildForm.Controls["guipnlMeasurementDetails"].SendToBack(); 
            GuiCommon.SetupChildForm.Controls["guipnlPWAMeasurementDetails"].Visible = true;
            GuiCommon.SetupChildForm.Controls["guipnlPWAMeasurementDetails"].BringToFront();
            OnModeChangeEvent.Invoke(this, new EventArgs());

            /* ************************************
             * This section is used for quick start
             * This has been commeted out for now 
             *************************************/
            /*To be  used in future sprints.
            GuiCommon.QuickStartChildForm.Controls["guipnlPWAMeasurementDetails"].Controls["guipnlPWABPOtherDevice"].Visible = false;

            if (GuiCommon.Workflow == GuiCommon.Workflows.Quick)
            {

               GuiCommon.QuickStartChildForm.Controls["guipnlPWAMeasurementDetails"].Controls["guiradbtnGetBp"].Text = "Get BP";
               GuiCommon.QuickStartChildForm.Controls["guipnlPWAMeasurementDetails"].Controls["guiradbtnAutoPWACancel"].Text = "Cancel";
               GuiCommon.QuickStartChildForm.Controls["guipnlPWAMeasurementDetails"].Controls["guiradbtnAutoPWACancel"].Visible = false;
               GuiCommon.SetupChildForm.Controls["guipnlPWAMeasurementDetails"].Controls["guiradbtnDisplayReport"].Visible = true;

               radtabQuickStart.Item.Visibility = ElementVisibility.Visible;
               radtabCapture.Item.Visibility = ElementVisibility.Visible;
               radtabTestResults.Item.Visibility = ElementVisibility.Visible;
               guiradgrpbxPwvDistanceMethod.Item.Visibility = ElementVisibility.Visible;
               radtabReport.Item.Visibility = ElementVisibility.Visible;

               radpgTabCollection.Pages.ChangeIndex(radtabQuickStart, 0);
               radpgTabCollection.Pages.ChangeIndex(radtabCapture, 1);
               radpgTabCollection.Pages.ChangeIndex(radtabTestResults, 2);
               radpgTabCollection.Pages.ChangeIndex(guiradgrpbxPwvDistanceMethod, 3);
               radpgTabCollection.Pages.ChangeIndex(radtabReport, 4);

               radpgTabCollection.SelectedPage = radtabQuickStart;
               GuiCommon.TabFocused = radtabQuickStart;

            }
            else
            {

                GuiCommon.SetupChildForm.Controls["guipnlPWAMeasurementDetails"].Controls["guiradbtnGetBp"].Text = "Get BP";
                GuiCommon.SetupChildForm.Controls["guipnlPWAMeasurementDetails"].Controls["guiradbtnAutoPWACancel"].Text = "Cancel";
                GuiCommon.SetupChildForm.Controls["guipnlPWAMeasurementDetails"].Controls["guiradbtnAutoPWACancel"].Visible = false;
                GuiCommon.SetupChildForm.Controls["guipnlPWAMeasurementDetails"].Controls["guiradbtnDisplayReport"].Visible = false;

                radtabQuickStart.Item.Visibility = ElementVisibility.Hidden;
                radtabCapture.Item.Visibility = ElementVisibility.Visible;
                radtabTestResults.Item.Visibility = ElementVisibility.Hidden;
                guiradgrpbxPwvDistanceMethod.Item.Visibility = ElementVisibility.Visible;
                radtabReport.Item.Visibility = ElementVisibility.Visible;

                radpgTabCollection.Pages.ChangeIndex(radtabQuickStart, 0);
                radpgTabCollection.Pages.ChangeIndex(guiradgrpbxPwvDistanceMethod, 1);
                radpgTabCollection.Pages.ChangeIndex(radtabCapture, 2);
                radpgTabCollection.Pages.ChangeIndex(radtabReport, 3);
                radpgTabCollection.Pages.ChangeIndex(radtabTestResults, 4);*/

              // radpgTabCollection.SelectedPage = guiradgrpbxPwvDistanceMethod;
              // GuiCommon.TabFocused = guiradgrpbxPwvDistanceMethod;

            // }
        }

        /**This event is fired when the user tries to change the mode in the drop down box.
         */ 
        private void guicmbxCurrentMode_SelectedIndexChanged(object sender, Telerik.WinControls.UI.Data.PositionChangedEventArgs e)
        {
            SetStrategy(guicmbxCurrentMode.Text);   
        }

        /** Begin: AtCor-<Drop2>-<Sprint2>, TM, <UserStory2>,4 july 2011
         * This method is called on click of Sysetm key menu in menu bar, It displays System Key box.
         */
        private void guiradmnuSystemKey_Click(object sender, EventArgs e)
        {
            GuiCommon.SystemKeyWindowValue = GuiCommon.SystemKeyWindowValues.Update;
            var systemKey = new SystemKey { ShowInTaskbar = false }; 
            systemKey.ShowDialog();
        }

        /**This method is used to validate PWV mode.
         */ 
        private void ValidatePWVMode()
        {           
            foreach (RadListDataItem radlistdataitem in guicmbxCurrentMode.Items)
            {
                if (radlistdataitem.Text.Equals(oMsgMgr.GetMessage(CrxStructCommonResourceMsg.Pwv)))
                {
                    radlistdataitem.Selected = true;
                    break;
                }
            }
        }

        /**This method is used to validate PWA mode.
       */ 
        private void ValidatePWAMode()
        {           
            foreach (RadListDataItem radlistdataitem in guicmbxCurrentMode.Items)
            {
                if (radlistdataitem.Text.Equals(oMsgMgr.GetMessage(CrxStructCommonResourceMsg.Pwa)))
                {
                    radlistdataitem.Selected = true;
                    break;
                }
            }
        }

        private void radpgTabCollection_MouseDown(object sender, MouseEventArgs e)
        {
            if (radpgTabCollection.SelectedPage.Text.Equals(oMsgMgr.GetMessage(CrxStructCommonResourceMsg.TabCapture), StringComparison.CurrentCultureIgnoreCase))
            {
                // When the capture form has loaded ,this event is invoked.
                if (GuiCommon.CaptureFormLoaded)
                {
                    OnCaptureScreenTabClick.Invoke(this, new EventArgs());
                }
                else
                {
                    radpgTabCollection.SelectedPage = guiradgrpbxPwvDistanceMethod;
                    guiradgrpbxPwvDistanceMethod.Enabled = true;
                }
            } 
        }

        /**  End   : AtCor-<Drop2>-<Sprint2>, TM, <UserStory2>,4 july 2011
         */
   } // End class
} // End namespace
