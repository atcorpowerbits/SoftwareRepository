/*
     Copyright (C) ATCOR MEDICAL PTY LTD, 2010
 
     Filename     :     Settings Window
        
     Author       :     Nitesh Chhedda
 
     Description  :     Functionality implemented for Settings window.
*/
using AtCor.Scor.CrossCutting;
using AtCor.Scor.CrossCutting.Configuration;
using AtCor.Scor.CrossCutting.Logging;
using AtCor.Scor.CrossCutting.Messaging;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.IO.Ports;
using System.IO;
using System.Text;
using System.Threading;
using System.Windows.Forms;
using System;
using Telerik.WinControls;
using Telerik.WinControls.UI;
using Telerik.WinControls.UI.Docking;
using Telerik.WinControls.Enumerations;

namespace Gui.Atcor.Scor.Presentation
{         
     /**
     * @class Setting Window
     * @brief This class is used to set General as well as PWV settings for the application.On this window,all the necessary settings will be done which are required by the user at different stages in the application.
     */    
    public partial class frmSettingsWindow : Telerik.WinControls.UI.RadForm
    {
        #region Set constant values
        //GeneralSettings
        const int DOC_GENERAL_SETTINGS = 10066;
        const int GRP_SETUP_SCREEN = 10019;
        const int CHK_PATIENT_PRIVACY = 10065;
        const int GRP_HEIGHT_WEIGHT_UNITS = 10020;
        const int RAD_METRIC = 10021;
        const int RAD_IMPERIAL = 10022;
        const int GRP_BLOOD_PRESSURE = 10023;
        const int RAD_SP_DP = 10024;
        const int RAD_SP_MP = 10025;
        const int RAD_MP_DP = 10026;
        const int GRP_COMMS_PORT = 10027;
        const int GRP_REPORTS = 10028;
        const int LBL_REPORT_TITLE = 10029;
        const int LBL_REPORT_LOGO = 10030;
        const int BTN_CHANGE = 10031;
        const int BTN_SAVE = 10032;
        const int BTN_CANCEL = 10033;
        const int BTN_DEFAULTS = 10034;

        //PWV SETTINGS
        const int DOC_PWV_SETTINGS = 10035;
        const int GRP_PWV_DISTANCE_METHOD = 10036;
        const int RAD_SUBTRACTING = 10037;
        const int RAD_DIRECT = 10038;
        const int GRP_CUFF_LOCATION = 10039;
        const int CHK_FEMORAL_CUFF = 10040;
        const int GRP_SIMULATION_FILES = 10041;
        const int GRP_REPORT_SCREEN = 10042;
        const int CHK_REFERENCE_RANGE = 10043;
        const int GRP_PWV_DISTANCE_UNITS = 10044;
        const int RAD_MM = 10045;
        const int RAD_CM = 10046;
        const int GRP_CAPTURE_TIME = 10047;
        const int RAD_5_SEC = 10048;
        const int RAD_10_SEC = 10049;
        const int RAD_20_SEC = 10050;

        //error messages
        const int SYSTEM_ERROR = 10015;
        const int FILE_NOT_FOUND = 10055;
        const int INFORMATION = 10070;

        //STRINGS
        const string DAT_FILES = @".\\simulation\PWV\*.dat";
        const string PATH_SIMUALTION_FILES = @".\\simulation\pwv";
        const string FILE_DEFAULT = "DEFAULT";
        const string FILE_Default = "Default";
        const string MSG_SIMULATION_FILES = "No files with .dat extension were found.";
        const string LOGO_FILTER = "jpg files (*.jpg)|*.jpg|bmp files(*.bmp)|*.bmp";
        const string INTIAL_DRIVE = "C:";
        const string SELECT_LOGO = "Select a Report Logo";

        #endregion

        #region Global decalartions
        CrxConfigManager obj;
        OpenFileDialog dialog;
        CrxMessagingManager oMsgMgr = CrxMessagingManager.Instance;
       
        //Creating object of DefaultWindow.
        private DefaultWindow objDefaultWindow;

        //This variable is used to create a copy of the generalsettings structure which will be used update the 
        //configuration object after the save functionality is implemented.@n
        //This variable plays an important role in retriving the current values for the settings if Save fails.
        CrxStructGeneralSetting gnrlSettingsStruct;
        CrxStructPwvSetting pwvSettingsStruct;

        //Flag set when default button is clicked.
        bool defaultBtnClicked = false;       

        //Declaring delegates to implement cross-thread communication and for control assignment.
        private delegate void ReadConfigObject();

        private delegate void DisplaySettingsDelegate(object sender, DisplaySettingsEventArgs e);
                
        private delegate void SetUserSettingsDelegate(
                                                      CrxStructGeneralSetting genStructObj,
                                                      CrxStructPwvSetting pwvStructObj);

        private delegate void CloseAfterSaveDelegate();

        private delegate void DisplayMessageBoxDelegate(string message);
        
        //Declaring events for cross-thread communiction.         
        private event DisplaySettingsDelegate OnDisplayUserSettings;

        private event DisplaySettingsDelegate OnDefaultGeneralSettings;
        #endregion

        //Constructor of the form,initializes all the controls and the structure for General as well as PWV settings.       
        public frmSettingsWindow()
        {
            InitializeSettingsWindow();
        }

        /**Parameterized constructor to display messages in the Message Bay of the DefaultWindow.
        */ 
        public frmSettingsWindow(DefaultWindow objDfltWnd)
        {
            InitializeSettingsWindow();
            objDefaultWindow = objDfltWnd;
        }

        /**This method is called when the constructor is initialized.It sets up the Settings screen.                */ 
        private void InitializeSettingsWindow()
        {
            InitializeComponent();
            gnrlSettingsStruct = new CrxStructGeneralSetting();
            pwvSettingsStruct = new CrxStructPwvSetting();
            //To prevent docking of the tabstrip.
            DragDropService service = this.radDock1.GetService<DragDropService>();
            service.Starting += new StateServiceStartingEventHandler(Service_Starting);

            //To disable right clicking on the tabstrip.
            ContextMenuService menuService = this.radDock1.GetService<ContextMenuService>();
            menuService.ContextMenuDisplaying += menuService_ContextMenuDisplaying;  
            this.MaximumSize = this.Size;
            this.MinimumSize = this.Size;
            
            // Populate the text value for General settings form controls
            SetTextForGeneralSettingsTab();            

            // Populate the text value for PWV settings form controls
            SetTextForPwvSettingsTab();            
        }

        /**This method sets the test for the labels ,buttons ,group boxes and so on, for the General settings on the GUI.
         */ 
        private void SetTextForGeneralSettingsTab()
        {
            //frmSettingsWindow=User Settings
            docWndGeneralSettings.Text = oMsgMgr.GetMessage(DOC_GENERAL_SETTINGS);
            radchkbxPatientPrivacy.Text = oMsgMgr.GetMessage(CHK_PATIENT_PRIVACY);
            radgrpbxSetupScreen.Text = oMsgMgr.GetMessage(GRP_SETUP_SCREEN);
            radgrpbxHeightWeightUnits.Text = oMsgMgr.GetMessage(GRP_HEIGHT_WEIGHT_UNITS);
            radradiobtnMeric.Text = oMsgMgr.GetMessage(RAD_METRIC);
            radradiobtnImperial.Text = oMsgMgr.GetMessage(RAD_IMPERIAL);
            radgrpbxBloodPressure.Text = oMsgMgr.GetMessage(GRP_BLOOD_PRESSURE);
            radradiobtnSPandDP.Text = oMsgMgr.GetMessage(RAD_SP_DP);
            radradiobtnSPandMP.Text = oMsgMgr.GetMessage(RAD_SP_MP);
            radradiobtnMPandDP.Text = oMsgMgr.GetMessage(RAD_MP_DP);
            radgrpbxCommsPort.Text = oMsgMgr.GetMessage(GRP_COMMS_PORT);
            radgrpbxReports.Text = oMsgMgr.GetMessage(GRP_REPORTS);
            radlblReportTitle.Text = oMsgMgr.GetMessage(LBL_REPORT_TITLE);
            radlblReportLogo.Text = oMsgMgr.GetMessage(LBL_REPORT_LOGO);
            radbtnChange.Text = oMsgMgr.GetMessage(BTN_CHANGE);
            radbtnSave.Text = oMsgMgr.GetMessage(BTN_SAVE);
            radbtnCancel.Text = oMsgMgr.GetMessage(BTN_CANCEL);
            radbtnDefaults.Text = oMsgMgr.GetMessage(BTN_DEFAULTS);
        }
        
        /**This method sets the test for the labels ,buttons ,group boxes and so on, for the PWV settings on the GUI.
         */ 
        private void SetTextForPwvSettingsTab()
        {
            docWndPWVSettings.Text = oMsgMgr.GetMessage(DOC_PWV_SETTINGS);
            radgrpbxPwvDistanceMethod.Text = oMsgMgr.GetMessage(GRP_PWV_DISTANCE_METHOD);
            radSubtracting.Text = oMsgMgr.GetMessage(RAD_SUBTRACTING);
            radDirect.Text = oMsgMgr.GetMessage(RAD_DIRECT);
            radgrpCuffLocation.Text = oMsgMgr.GetMessage(GRP_CUFF_LOCATION);
            radchkFemoralToCuff.Text = oMsgMgr.GetMessage(CHK_FEMORAL_CUFF);
            radgrpSimulationFiles.Text = oMsgMgr.GetMessage(GRP_SIMULATION_FILES);
            radgrpReportScreen.Text = oMsgMgr.GetMessage(GRP_REPORT_SCREEN);
            radchkReferenceRange.Text = oMsgMgr.GetMessage(CHK_REFERENCE_RANGE);
            radgrpPwvDistanceUnits.Text = oMsgMgr.GetMessage(GRP_PWV_DISTANCE_UNITS);
            radmm.Text = oMsgMgr.GetMessage(RAD_MM);
            radcm.Text = oMsgMgr.GetMessage(RAD_CM);
            radgrpCaptureTime.Text = oMsgMgr.GetMessage(GRP_CAPTURE_TIME);
            rad5Seconds.Text = oMsgMgr.GetMessage(RAD_5_SEC);
            rad10Seconds.Text = oMsgMgr.GetMessage(RAD_10_SEC);
            rad20Seconds.Text = oMsgMgr.GetMessage(RAD_20_SEC);
        }

        /**This method is used to prevents the user from rearranging the tabs horizontally and vertically.
        */ 
        private void Service_Starting(object sender, StateServiceStartingEventArgs e)
        {
            e.Cancel = true;
        }

        /**This method is used to disable the right clicking on the tab strip.
        */
        private void menuService_ContextMenuDisplaying(object sender, ContextMenuDisplayingEventArgs e)
        {
            //the menu request is associated with a valid DockWindow instance, which resides within a DocumentTabStrip
            if (e.MenuType == ContextMenuType.DockWindow &&
                e.DockWindow.DockTabStrip is DocumentTabStrip)
            {
                //remove the "Close" menu items
                for (int i = 0; i < e.MenuItems.Count; i++)
                {
                    RadMenuItemBase menuItem = e.MenuItems[i];                    
                    {
                        // In case you just want to disable to option you can set Enabled false
                        //menuItem.Enabled = false;
                        menuItem.Visibility = Telerik.WinControls.ElementVisibility.Collapsed;
                    }
                }
            }
        } 
               
        /**This method will be called when Settings option under System tab is clicked.
         *On load it will call the Config object via threading to populate the General user settings.
         *If any exception occurs it will be caught and displayed to the user using a message box.
         *The corresponding exception will also be logged in the log file.
         */
        private void SettingsWindow_Load(object sender, EventArgs e)
        {
            try
            {
                //On windows load set the windows size to maximum.                 
                MinimizeBox = false;
                MaximizeBox = false;
                radbtnSave.Enabled = false;
                documentTabStrip1.AllowDrop = false;                

                //Below line of code will,always set the focus on General Settings tab,everytime Settings window is loaded. 
                docWndGeneralSettings.Select(); 

                //look for ports and list them in dropdown.                 
                SearchPorts();
                PopulateSimulationType();                
                //Event to read Scor.config file containing the General User Settings.                 
                OnDisplayUserSettings += new DisplaySettingsDelegate(DisplaySetings);

                //Thread for I/O operation.                          
                Thread t1 = new Thread(ReadUserSettings);
                t1.Start();

                //
            }            
            catch (Exception ex)
            {
                RadMessageBox.Show(this, ex.Message, oMsgMgr.GetMessage(SYSTEM_ERROR), MessageBoxButtons.OK, RadMessageIcon.Error);
                CrxLogger oLogObject = CrxLogger.Instance;
                oLogObject.Write(ex.Message);
            }
        }
        
        /**Function to display General User Setting as well as General Default Settings.
         *It takes all the necessary settings value from the configuration object and populates the appropiate controls.
         *While populating the controls if any exception occurs it will shown to the user using a message box.
         *The corresponding exception will also be logged in the log file.
         */
        private void SetUserSettings(CrxStructGeneralSetting genStructObj, CrxStructPwvSetting pwvStructObj)
        {
            //Setting the settings on the controls in the form.             
            try
            {              
                //Set General Tab fields
                if (genStructObj != null)
                {
                    radchkbxPatientPrivacy.Checked = genStructObj.PatientPrivacy;

                    //This method is used to set the height weight units value to the corresponding GUI control.      
                    SetHeightWeightUnits(genStructObj.HeightandWeightUnit);

                    //This method is used to set the blood pressure value to the corresponding GUI control.    
                    SetBloodPressure(genStructObj.BloodPressureEntryOptions);

                    if (!defaultBtnClicked)
                    {
                        //This method is used to set the comm port value to the corresponding GUI control. 
                        SetCommPort(genStructObj.CommsPort);

                        //This method is used to set the report title value to the corresponding GUI control.     
                        SetReportTitle(genStructObj.ReportTitle);

                        //This method is used to set the report logo path value to the corresponding GUI control.         
                        SetReportLogo(genStructObj.ReportLogoPath);
                    }
                }                

                //Set PWV tab fields
                if (pwvStructObj != null)
                {
                    radchkFemoralToCuff.Checked = pwvStructObj.FemoralToCuff;
                    radchkReferenceRange.Checked = pwvStructObj.ReferenceRange;

                    //This method is used to set the PWV distance method value to the corresponding GUI control.       
                    SetPwvDistanceMethod(pwvStructObj.PWVDistanceMethod);

                    //This method is used to set the PWV distance units to the corresponding GUI control.                   
                    SetPwvDistanceUnits(pwvStructObj.PWVDistanceUnits);

                    //This method is used to set the Capture time to the corresponding GUI control.                    
                    SetCaptureTime(pwvStructObj.CaptureTime);

                    //This method is used to set the Simulation type value to the corresponding GUI control.   
                    SetSimulationType(pwvStructObj.SimulationType);
                }                
            }
            catch (Exception ex)
            {                
                if (this.InvokeRequired)
                {
                    DisplayMessageBoxDelegate messageBox = new DisplayMessageBoxDelegate(DisplayErrorMessage);
                    this.Invoke(messageBox, ex.Message);
                }

                CrxLogger oLogObject = CrxLogger.Instance;
                oLogObject.Write(ex.Message);
            }
            finally
            {
                //disable save button                 
                if (!defaultBtnClicked)
                {
                    radbtnSave.Enabled = false;                   
                }
            }
        }

        /**This method is used to set the PWV distance method value to the corresponding GUI control.
        */
        private void SetPwvDistanceMethod(int value)
        {
            switch (value)
            {
                case 0:
                    radSubtracting.ToggleState = Telerik.WinControls.Enumerations.ToggleState.On;
                    break;
                case 1:
                    radDirect.ToggleState = Telerik.WinControls.Enumerations.ToggleState.On;
                    break;
                default:
                    break;
            }
        }

        /**This method is used to set the PWV distance units to the corresponding GUI control.
        */
        private void SetPwvDistanceUnits(int value)
        {
            switch (value)
            {
                case 0:
                    radmm.ToggleState = Telerik.WinControls.Enumerations.ToggleState.On;
                    break;
                case 1:
                    radcm.ToggleState = Telerik.WinControls.Enumerations.ToggleState.On;
                    break;
                default:
                    break;
            }
        }

        /**This method is used to set the Capture time to the corresponding GUI control.
        */
        private void SetCaptureTime(int value)
        {
            switch (value)
            {
                case 0:
                    rad5Seconds.ToggleState = Telerik.WinControls.Enumerations.ToggleState.On;
                    break;
                case 1:
                    rad10Seconds.ToggleState = Telerik.WinControls.Enumerations.ToggleState.On;
                    break;
                case 2:
                    rad20Seconds.ToggleState = Telerik.WinControls.Enumerations.ToggleState.On;
                    break;
                default:
                    break;
            }
        }

        /**This method is used to set the Simulation type value to the corresponding GUI control.
        */
        private void SetSimulationType(string value)
        {
            //Logic to fill the dropdown.
            try
            {
                List<string> fileList = new List<string>();
                
                if (value == null)
                {
                    PopulateSimulationType();
                    return;
                }

                if (Path.HasExtension(DAT_FILES))
                {
                    DirectoryInfo dirInfo = new DirectoryInfo(
PATH_SIMUALTION_FILES);
                    foreach (System.IO.FileInfo file in dirInfo.GetFiles())
                    {
                        fileList.Add(Path.GetFileNameWithoutExtension(file.ToString().ToUpper()));
                    }

                    if (fileList.Contains(value.ToUpper()))
                    {
                        comboSimulationFiles.Items.Remove(value);
                        comboSimulationFiles.Items.Insert(0, value);
                        comboSimulationFiles.SelectedIndex = 0;
                        return;
                    }

                    if (fileList.Contains(FILE_DEFAULT))
                    {
                        comboSimulationFiles.Items.Remove(FILE_Default);
                        comboSimulationFiles.Items.Insert(0, FILE_Default);
                        comboSimulationFiles.SelectedIndex = 0;
                        //this.objDefaultWindow.ChildMessage = "Since user selected file was not found,hence showing the Default simulation file.";
                        //this.objDefaultWindow.UpdateMessage();
                        return;
                    }

                    // if we are here, means we did not locate either the config file or the default file., so
                    // set index to first file.
                    PopulateSimulationType();
                }
                else
                {
                    // get the parent form object.
                    objDefaultWindow.SetMessage(oMsgMgr.GetMessage(FILE_NOT_FOUND));
                }                
            }
            catch (Exception ex)
            {
                RadMessageBox.Show(this, ex.Message, oMsgMgr.GetMessage(SYSTEM_ERROR), MessageBoxButtons.OK, RadMessageIcon.Error);
                CrxLogger oLogObject = CrxLogger.Instance;
                oLogObject.Write(ex.Message);
            } 
        }

        /**This method is used to set the height weight units value to the corresponding GUI control.
        */ 
        private void SetHeightWeightUnits(int value)
        {
            switch (value)
            {
                case 0:
                    radradiobtnMeric.ToggleState = Telerik.WinControls.Enumerations.ToggleState.On;
                    break;
                case 1:
                    radradiobtnImperial.ToggleState = Telerik.WinControls.Enumerations.ToggleState.On;
                    break;
                default:
                    break;
            }
        }

        /**This method is used to set the blood pressure value to the corresponding GUI control.
        */ 
        private void SetBloodPressure(int value)
        {
            switch (value)
            {
                case 0:
                    radradiobtnSPandDP.ToggleState = Telerik.WinControls.Enumerations.ToggleState.On;
                    break;
                case 1:
                    radradiobtnSPandMP.ToggleState = Telerik.WinControls.Enumerations.ToggleState.On;
                    break;
                case 2:
                    radradiobtnMPandDP.ToggleState = Telerik.WinControls.Enumerations.ToggleState.On;
                    break;
                default:
                    break;
            }
        }

        /**This method is used to set the comm port value to the corresponding GUI control.
        */ 
        private void SetCommPort(string value)
        {
            if (value != null && comboBoxCommsPort.Items.Contains(value))
            {
                comboBoxCommsPort.Items.Remove(value);
                comboBoxCommsPort.Items.Insert(0, value);
                comboBoxCommsPort.SelectedIndex = 0;
            }
        }

        /**This method is used to set the report title value to the corresponding GUI control.
        */ 
        private void SetReportTitle(string value)
        {
            if (value != null && value.Length > 0)
            {
                radtxtReportTitle.Text = value;
            }
        }

        /**This method is used to set the report logo path value to the corresponding GUI control.
        */ 
        private void SetReportLogo(string path)
        {
            if (path != null && path.Length > 0)
            {
                Image image = Image.FromFile(path);
                picbxReportLogo.Image = image;
                picbxReportLogo.ImageLocation = path;
                picbxReportLogo.Height = image.Height;
                picbxReportLogo.Width = image.Width;
            }
        }

        /**This method is used to populate the settings value on the controls.
         *Since we cannot assign values to the controls in different thread therefore invoking the parent thread.
         *Any expection thrown while reading values from the  xml file will be caught by the configuration file and caught. 
         *This expection will be shown to the user using a message box,also it will be logged into the log file.
         *Any other general excpetion will also be caught and displayed to the user.It will also be logged into the log file.         
         */
        private void DisplaySetings(object sender, DisplaySettingsEventArgs e)      
        {
            //Reading the settings from the configuration object.             
            try
            {                
                //Settings the user settings on the controls.Since we cannot assign values to the controls in different 
                //thread therefore invoking the parent thread.                 
                if (radchkbxPatientPrivacy.InvokeRequired || radgrpPwvDistanceUnits.InvokeRequired || radgrpCaptureTime.InvokeRequired)
                {
                    SetUserSettingsDelegate userSettings = new SetUserSettingsDelegate(SetUserSettings);
                    this.Invoke(userSettings, new object[] { e.GenObj, e.PwvObj });
                }
            }
            catch (CrxException cfgExp)
            {
                //Exception if any will be logged and displayed(appropiate message) to the user.                 
                CrxMessagingManager oMsgMgr = CrxMessagingManager.Instance;
                string errorMessage = oMsgMgr.GetMessage(cfgExp.ErrorCode);
                
                if (this.InvokeRequired)
                {
                    DisplayMessageBoxDelegate messageBox = new DisplayMessageBoxDelegate(DisplayErrorMessage);
                    this.Invoke(messageBox, errorMessage);
                }

                CrxLogger oLogObject = CrxLogger.Instance;
                oLogObject.Write(errorMessage);
            }
            catch (Exception ex)
            {
                if (this.InvokeRequired)
                {
                    DisplayMessageBoxDelegate messageBox = new DisplayMessageBoxDelegate(DisplayErrorMessage);
                    this.Invoke(messageBox, ex.Message);
                }

                CrxLogger oLogObject = CrxLogger.Instance;
                oLogObject.Write(ex.Message);
            }
        } // End DisplaySetings

        /**This method is called when the thread for reading General user settings is started.
         *It will call the corresponding event which in turn will read the settings from the configuration file.
         *Any expection thrown while reading values from the  xml file will be caught by the configuration file and caught. 
         *This expection will be shown to the user using a message box,also it will be logged into the log file.
         *Any other general excpetion will also be caught and displayed to the user.It will also be logged into the log file
         */
        private void ReadUserSettings()
        {
            //Logic to read General user settings from the configuration object.             
            try
            {                
                obj = CrxConfigManager.Instance;
                obj.GetGeneralUserSettings();
                obj.GetPwvUserSettings();

                // set event arguments to be passed
                DisplaySettingsEventArgs args = new DisplaySettingsEventArgs();
                args.GenObj = obj.GeneralSettings;
                args.PwvObj = obj.PwvSettings;                

                //Calling the event which displays the general settings on the GUI.                
                OnDisplayUserSettings(this, args);
            }
            catch (CrxException cfgExp)
            {
                //Exception if any will be logged and displayed(appropiate message) to the user.                 
                CrxMessagingManager oMsgMgr = CrxMessagingManager.Instance;
                string errorMessage = oMsgMgr.GetMessage(cfgExp.ErrorCode);
                
                if (this.InvokeRequired)
                {
                    DisplayMessageBoxDelegate messageBox = new DisplayMessageBoxDelegate(DisplayErrorMessage);
                    this.Invoke(messageBox, errorMessage);
                }

                CrxLogger oLogObject = CrxLogger.Instance;
                oLogObject.Write(errorMessage);

                if (cfgExp.ErrorCode == 100)
                {
                    if (this.InvokeRequired)
                    {
                        CloseAfterSaveDelegate closewindow = new CloseAfterSaveDelegate(CloseSettingWindowAfterSave);
                        this.Invoke(closewindow);
                    }
                }
            }
            catch (Exception ex)
            {
                if (this.InvokeRequired)
                {
                    DisplayMessageBoxDelegate messageBox = new DisplayMessageBoxDelegate(DisplayErrorMessage);
                    this.Invoke(messageBox, ex.Message);
                }

                CrxLogger oLogObject = CrxLogger.Instance;
                oLogObject.Write(ex.Message);              
            }
        }

        /**This method is called when the thread for reading Default user settings is started.
         *It will call the corresponding event which in turn will read the settings from the configuration file.
         *Any expection thrown while reading values from the  xml file will be caught by the configuration file and caught. 
         *This expection will be shown to the user using a message box,also it will be logged into the log file.
         *Any other general excpetion will also be caught and displayed to the user.It will also be logged into the log file
         */
        private void ReadDefaultSettings()
        {
            //Logic to read Default General Settings from the configuration object.             
            DisplaySettingsEventArgs args = new DisplaySettingsEventArgs();
            try
            {          
                obj = CrxConfigManager.Instance;
                int index = documentTabStrip1.SelectedIndex;
                
                if (index.Equals(0))
                {
                    //Read default general settings.
                    obj.GetGeneralDefaultSettings(gnrlSettingsStruct);

                    //Copying the general settings value from the configuration object into the user-defined args parameter 
                    //created.                                        
                    args.GenObj = gnrlSettingsStruct;
                    args.PwvObj = null;                    
                }

                if (index.Equals(1))
                {
                    //Read default Pwv settings.
                    obj.GetPwvDefaultSettings(pwvSettingsStruct);
                    
                    //Copying the general settings value from the configuration object into the user-defined args parameter 
                    //created.                                        
                    args.PwvObj = pwvSettingsStruct;
                    args.GenObj = null;                    
                }

                //Calling the event which displays the default general settings on the GUI.                
                OnDefaultGeneralSettings(this, args);
           }
            catch (CrxException cfgExp)
           {
               //Exception if any will be logged and displayed(appropiate message) to the user.                
                CrxMessagingManager oMsgMgr = CrxMessagingManager.Instance;
                string errorMessage = oMsgMgr.GetMessage(cfgExp.ErrorCode);               
                if (this.InvokeRequired)
                {
                    DisplayMessageBoxDelegate messageBox = new DisplayMessageBoxDelegate(DisplayErrorMessage);
                    this.Invoke(messageBox, errorMessage);
                }

                CrxLogger oLogObject = CrxLogger.Instance;
                oLogObject.Write(errorMessage);
            }
            catch (Exception ex)
            {
                if (this.InvokeRequired)
                {
                    DisplayMessageBoxDelegate messageBox = new DisplayMessageBoxDelegate(DisplayErrorMessage);
                    this.Invoke(messageBox, ex.Message);
                }

                CrxLogger oLogObject = CrxLogger.Instance;
                oLogObject.Write(ex.Message);
            }
        }
           
        /**This method will be called on load function of this window.
         *It will look for ports which are available on the machine and populate it in the drop down list.
         *Any expection occured during this will be caught and shown to the user using Message box.
         *The corresponding exception will also be logged in the log file.
         */
        private void SearchPorts()
        {
            try
            {
                string[] ports = SerialPort.GetPortNames();

                //Append the port into the comboBox.                 
                foreach (string port in ports)
                {
                    comboBoxCommsPort.Items.Add(port);
                }

                comboBoxCommsPort.Items.Add("Simulation");
                comboBoxCommsPort.SelectedIndex = 0;
            }
            catch (Exception ex)
            {
                RadMessageBox.Show(this, ex.Message, oMsgMgr.GetMessage(SYSTEM_ERROR), MessageBoxButtons.OK, RadMessageIcon.Error);
                CrxLogger oLogObject = CrxLogger.Instance;
                oLogObject.Write(ex.Message);
            }
        }

        /**This method will be called on load function of this window.
         *It will look for simulation files available under PWV folder(stored under Simulation folder) on the machine and 
         *populate it in the drop down list.
         *Any expection occured during this will be caught and shown to the user using Message box.
         *The corresponding exception will also be logged in the log file.
         */
        private void PopulateSimulationType()
        {
            try
            {
                DirectoryInfo dirInfo = new DirectoryInfo(@"D:\Atcor_SVN\src\trunk\Scor\gui\gui\bin\Debug\Simulation\PWV");

                foreach (System.IO.FileInfo file in dirInfo.GetFiles())
                {
                    comboSimulationFiles.Items.Add(Path.GetFileNameWithoutExtension(file.ToString()));
                }

                comboSimulationFiles.SelectedIndex = 0;
            }
            catch (Exception ex)
            {
                RadMessageBox.Show(this, ex.Message, oMsgMgr.GetMessage(SYSTEM_ERROR), MessageBoxButtons.OK, RadMessageIcon.Error);
                CrxLogger oLogObject = CrxLogger.Instance;
                oLogObject.Write(ex.Message);
            }
        }

        /**This method is invoked on the Cancel button.It will close the Settings window without saving any data.
         *If any exception occurs it will be caught and displayed to the user using a message box.
         *The corresponding exception will also be logged in the log file.
         */
        private void radbtnCancel_Click(object sender, EventArgs e)
        {
             //Close the settings window on Cancel click.
             this.Close();
        }

        /**This method is invoked when Change button is clicked.
         *It sets the Report Logo image into the picture box using an open dialog box.
         *It will also Enable the Save button,since we are changing the setting.
         *If any exception occurs it will be caught and displayed to the user using a message box.
         *The corresponding exception will also be logged in the log file.
         */
        private void radbtnChange_Click(object sender, EventArgs e)
        {
            try
            {
                //Get the main application path and save the same to restore it back                 
                string appPath = Directory.GetCurrentDirectory();

                dialog = new OpenFileDialog();
                dialog.Filter = LOGO_FILTER;
                dialog.InitialDirectory = INTIAL_DRIVE;
                dialog.Title = SELECT_LOGO;
                if (dialog.ShowDialog() == DialogResult.OK)
                {
                    Image image = Image.FromFile(dialog.FileName);
                    picbxReportLogo.Image = image;
                    picbxReportLogo.ImageLocation = dialog.FileName;
                    picbxReportLogo.Height = image.Height;
                    picbxReportLogo.Width = image.Width;
                }

                if (radtxtReportTitle.ToString() == String.Empty)
                {
                    return; //user didn't select a file to open
                }

                radbtnSave.Enabled = true;

                // we are done processing default button event, now reset the aplication path.
                Directory.SetCurrentDirectory(appPath);
            }
            catch (Exception ex)
            {
                RadMessageBox.Show(this, ex.Message, oMsgMgr.GetMessage(SYSTEM_ERROR), MessageBoxButtons.OK, RadMessageIcon.Error);
                CrxLogger oLogObject = CrxLogger.Instance;
                oLogObject.Write(ex.Message);
            }
        }
        
        /**This method is invoked on click of Defaults button.
         * It will create a thread which will read and populate Default General Settings on the UI.
         * If any exception occurs it will be caught and displayed to the user using a message box.
         * The corresponding exception will also be logged in the log file.
         */ 
        private void radbtnDefaults_Click(object sender, EventArgs e)
        {
            try
            {
                OnDefaultGeneralSettings += new DisplaySettingsDelegate(DisplaySetings);
                Thread t2 = new Thread(ReadDefaultSettings);
                t2.Start();

                //Enabling the Save button.
                radbtnSave.Enabled = true;

                //Flag set,indicate save button is enabled.
                defaultBtnClicked = true;
            }
            catch (Exception ex)
            {
                RadMessageBox.Show(this, ex.Message,  oMsgMgr.GetMessage(SYSTEM_ERROR), MessageBoxButtons.OK, RadMessageIcon.Error);
                CrxLogger oLogObject = CrxLogger.Instance;
                oLogObject.Write(ex.Message);
            }
        }

        private void ReadGeneralSettingsFromGui()
        {
            //Setting the values into the configuration object.

            //set the patient privacy option accordingly.
            gnrlSettingsStruct.PatientPrivacy = false;
            if (radchkbxPatientPrivacy != null && radchkbxPatientPrivacy.Checked)
            {
                //set the patient privacy option accordingly.
                gnrlSettingsStruct.PatientPrivacy = true;
            }

            gnrlSettingsStruct.HeightandWeightUnit = 1;

            if (radradiobtnMeric.ToggleState == Telerik.WinControls.Enumerations.ToggleState.On)
            {
                gnrlSettingsStruct.HeightandWeightUnit = 0;
            }
            
            gnrlSettingsStruct.BloodPressureEntryOptions = 0;
            
            if (radradiobtnSPandMP.ToggleState == Telerik.WinControls.Enumerations.ToggleState.On)
            {
                gnrlSettingsStruct.BloodPressureEntryOptions = 1;
            }
            else if (radradiobtnMPandDP.ToggleState == Telerik.WinControls.Enumerations.ToggleState.On)
            {
                gnrlSettingsStruct.BloodPressureEntryOptions = 2;
            }

            gnrlSettingsStruct.CommsPort = comboBoxCommsPort.Text;
            if (radtxtReportTitle.Text != null && radtxtReportTitle.Text.Length > 0)
            {
                gnrlSettingsStruct.ReportTitle = radtxtReportTitle.Text.Trim();
            }
            else
            {
                radtxtReportTitle.Text = null;
            }

            gnrlSettingsStruct.ReportLogoPath = picbxReportLogo.ImageLocation;
        }

        private void ReadPwvSetingsFromGui()
        {
                 pwvSettingsStruct.FemoralToCuff = false;
                if (radchkFemoralToCuff != null && radchkFemoralToCuff.Checked)
                {
                    pwvSettingsStruct.FemoralToCuff = true;
                }

                pwvSettingsStruct.ReferenceRange = false;
                if (radchkReferenceRange != null && radchkReferenceRange.Checked)
                {
                    pwvSettingsStruct.ReferenceRange = true;
                }

                pwvSettingsStruct.PWVDistanceMethod = 0;
                if (radDirect.ToggleState == Telerik.WinControls.Enumerations.ToggleState.On)
                {
                    pwvSettingsStruct.PWVDistanceMethod = 1;
                }

                pwvSettingsStruct.PWVDistanceUnits = 1;

                if (radmm.ToggleState == Telerik.WinControls.Enumerations.ToggleState.On)
                {
                    pwvSettingsStruct.PWVDistanceUnits = 0;
                }

                pwvSettingsStruct.CaptureTime = 0;

                if (rad10Seconds.ToggleState == Telerik.WinControls.Enumerations.ToggleState.On)
                {
                    pwvSettingsStruct.CaptureTime = 1;
                }
                else if (rad20Seconds.ToggleState == Telerik.WinControls.Enumerations.ToggleState.On)
                {
                    pwvSettingsStruct.CaptureTime = 2;
                }

                pwvSettingsStruct.SimulationType = comboSimulationFiles.Text;
        }

        /**This method is invoked on click of Save button.
         *All the settings are read from the UI and stored in the configuration object.
         *Another thread will be created to which will save the settings into the XML file.
         *If any exception occurs it will be caught and displayed to the user using a message box.
         *The corresponding exception will also be logged in the log file.
         */
        private void radbtnSave_Click(object sender, EventArgs e)
        {
            try
            {            
                //Reading General Settings values from GUI into the General settings structure.
                ReadGeneralSettingsFromGui();
                
                //Reading PWV settings values from GUI into the PWV settings structure.
                ReadPwvSetingsFromGui();

                //Calling another thread to Save the User Settings.
                Thread t2 = new Thread(SaveSettings);
                t2.Start();
                defaultBtnClicked = false;
            }
            catch (Exception ex)
            {
                if (this.InvokeRequired)
                {
                    DisplayMessageBoxDelegate messageBox = new DisplayMessageBoxDelegate(DisplayErrorMessage);
                    this.Invoke(messageBox, ex.Message);
                }

                CrxLogger oLogObject = CrxLogger.Instance;
                oLogObject.Write(ex.Message);              
            }           
        }

        /**Method to close the settings window after Save button is clicked.
         */ 
        private void CloseSettingWindowAfterSave()
        {
            this.Close();
        }

        /**Method to pass the configruation object to the Configuration file.
         */ 
        private void SaveSettings()
        {
            try
            {
                obj = CrxConfigManager.Instance;
                obj.SetGeneralUserSettings(gnrlSettingsStruct);
                obj.SetPwvUserSettings(pwvSettingsStruct);  

                obj.GeneralSettings = gnrlSettingsStruct;
                obj.PwvSettings = pwvSettingsStruct;                 
            }
            catch (CrxException cfgExp)
            {
                CrxMessagingManager oMsgMgr = CrxMessagingManager.Instance;
                string errorMessage = oMsgMgr.GetMessage(cfgExp.ErrorCode);
                if (this.InvokeRequired)
                {
                    DisplayMessageBoxDelegate messageBox = new DisplayMessageBoxDelegate(DisplayErrorMessage);
                    this.Invoke(messageBox, errorMessage);
                }

                CrxLogger oLogObject = CrxLogger.Instance;
                oLogObject.Write(errorMessage);
            }
            finally
            {
                if (this.InvokeRequired)
                {
                    CloseAfterSaveDelegate closewindow = new CloseAfterSaveDelegate(CloseSettingWindowAfterSave);
                    this.Invoke(closewindow);
                }
            }            
        }

        /**This method will display the error message using the message box.
         */ 
        private void DisplayErrorMessage(string errorMessage)
        {
            RadMessageBox.Show(this, errorMessage, oMsgMgr.GetMessage(SYSTEM_ERROR), MessageBoxButtons.OK, RadMessageIcon.Error);
        }

        /**This is a common function for Blood pessure ,Pateint privacy and height weight units,Femoral to cuff,Reference 
         * range,Capture time, PWV distance method and PWV distance.On change of any of the     
         * mentioned settings,Save button is enabled.
        */
        private void radchkbxPatientPrivacy_MouseClick(object sender, MouseEventArgs e)
        {
            radbtnSave.Enabled = true;
        }

        /**Enable Save button when text is changes in the Report Title.
         *If any exception occurs it will be caught and displayed to the user using a message box.
         *The corresponding exception will also be logged in the log file.
         */
        private void radtxtReportTitle_TextChanged(object sender, EventArgs e)
        {
            radbtnSave.Enabled = true;
        }

        /**Enable save button when user selects a value from the drop down list
        */ 
        private void comboBoxCommsPort_SelectionChangeCommitted(object sender, EventArgs e)
        {
            radbtnSave.Enabled = true;
        }

        private void radbtnPwvCancel_Click(object sender, EventArgs e)
        {
            //Close the settings window on Cancel click.
            this.Close();
        }        

        /**Enable save button when user selects a value from the drop down list
        */ 
        private void comboSimulationFiles_SelectionChangeCommitted(object sender, EventArgs e)
        {
            if (this.comboSimulationFiles.GetItemText(this.comboSimulationFiles.SelectedItem).Length.Equals(0))
            {
                RadMessageBox.Show(this, "Please select a Simulation File.", oMsgMgr.GetMessage(INFORMATION), MessageBoxButtons.OK, RadMessageIcon.Error);
            }
            else
            {
                radbtnSave.Enabled = true;
            }
        }

        /**This method is invoked on click of Defaults button.
        * It will create a thread which will read and populate Default PWV Settings on the UI.
        * If any exception occurs it will be caught and displayed to the user using a message box.
        * The corresponding exception will also be logged in the log file.
        */ 
        private void radbtnPwvDefaults_Click(object sender, EventArgs e)
        {
             try
            {
                OnDefaultGeneralSettings += new DisplaySettingsDelegate(DisplaySetings);
                Thread t3 = new Thread(ReadDefaultPWVSettings);
                t3.Start();
                 
                //Enabling the Save button.
                //radbtnPwvSave.Enabled = true;

                //Flag set,indicate save button is enabled.
                defaultBtnClicked = true;
            }
            catch (Exception ex)
            {
                RadMessageBox.Show(this, ex.Message, oMsgMgr.GetMessage(SYSTEM_ERROR), MessageBoxButtons.OK, RadMessageIcon.Error);
                CrxLogger oLogObject = CrxLogger.Instance;
                oLogObject.Write(ex.Message);
            }
        }

        /**This method is called when the thread for reading Default PWV settings is started.
         *It will call the corresponding event which in turn will read the settings from the configuration file.
         *Any expection thrown while reading values from the  xml file will be caught by the configuration file and caught. 
         *This expection will be shown to the user using a message box,also it will be logged into the log file.
         *Any other general excpetion will also be caught and displayed to the user.It will also be logged into the log file
         */
        private void ReadDefaultPWVSettings()
        {
            try
            {
                obj = CrxConfigManager.Instance;
                obj.GetPwvDefaultSettings(pwvSettingsStruct);                  

                //Copying the general settings value from the configuration object into the user-defined args parameter 
                //created.                
                DisplaySettingsEventArgs args = new DisplaySettingsEventArgs();               
                args.PwvObj = pwvSettingsStruct;

                //Calling the event which displays the default general settings on the GUI.                
                OnDefaultGeneralSettings(this, args);
            }
            catch (CrxException cfgExp)
            {
                //Exception if any will be logged and displayed(appropiate message) to the user.                 
                CrxMessagingManager oMsgMgr = CrxMessagingManager.Instance;
                string errorMessage = oMsgMgr.GetMessage(cfgExp.ErrorCode);
                if (this.InvokeRequired)
                {
                    DisplayMessageBoxDelegate messageBox = new DisplayMessageBoxDelegate(DisplayErrorMessage);
                    this.Invoke(messageBox, errorMessage);
                }

                CrxLogger oLogObject = CrxLogger.Instance;
                oLogObject.Write(errorMessage);
            }
            catch (Exception ex)
            {
                if (this.InvokeRequired)
                {
                    DisplayMessageBoxDelegate messageBox = new DisplayMessageBoxDelegate(DisplayErrorMessage);
                    this.Invoke(messageBox, ex.Message);
                }

                CrxLogger oLogObject = CrxLogger.Instance;
                oLogObject.Write(ex.Message);
            }
        }                
    }

    /**
    * @class DisplaySettingEventArgs
    * @brief This class is written to create user defined args types which are used in events. 
    */
    public class DisplaySettingsEventArgs : EventArgs
    {
        public CrxStructGeneralSetting GenObj;
        public CrxStructPwvSetting PwvObj;
    }
}
