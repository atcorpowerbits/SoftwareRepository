/*
     Copyright (C) ATCOR MEDICAL PTY LTD, 2010
 
     Filename     :     Settings Window
        
     Author       :     Nitesh Chhedda
 
     Description  :     Functionality implemented for Settings window.
*/
using CrxConfiguration;
using CrxLogging;
using CrxMessaging;
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

namespace ScorGui
{
    /**
	 * @class       Setting Window
	 * @brief       This class is used to set General as well as PWV settings for the application.On this window,all the necessary settings will be done which are required by the user at different stages in the application.
	 */    
    public partial class SettingsWindow : Telerik.WinControls.UI.RadForm
    {
        #region Global decalartions
        CrxConfigManager obj;
        OpenFileDialog dialog;

        /**Flag set when default button is clicked.
         */ 
        bool defaultBtnClicked = false;       

        /**Declaring delegates to implement cross-thread communication and for control assignment.
         */ 
        private delegate void ReadConfigObject();

        private delegate void DisplaySettingsDelegate(CrxStructGeneralSetting obj);

        private delegate void DisplayDefaultGeneralSettings(CrxStructGeneralSetting obj);

        private delegate void SetUserSettingsDelegate(
                                                      bool patientPrivacy, int heightWeightUnits, 
                                                      int bloodPressure, string commPort, 
                                                      string reportTitle, string reportLogoPath);

        private delegate void CloseAfterSaveDelegate();

        private delegate void DisplayMessageBoxDelegate(string message);
        
        /**Declaring events for cross-thread communiction.
         */ 
        private event DisplaySettingsDelegate EventDisplayUserSettings;

        private event DisplayDefaultGeneralSettings EventDefaultGeneralSettings;
        #endregion

        /**Constructor of the form,initializes all the controls.
         */ 
        public SettingsWindow()
        {
            InitializeComponent();
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
                /**On windows load set the windows size to maximum.
                 */ 
                MinimizeBox = false;
                MaximizeBox = false;
                radbtnSave.Enabled = false;

                /**look for ports and list them in dropdown
                 */ 
                SearchPorts();

                /**Event to read Scor.config file containing the General User Settings.
                 */ 
                EventDisplayUserSettings += new DisplaySettingsDelegate(DisplaySetings);

                /**Thread for I/O operation.         
                 */ 
                Thread t1 = new Thread(ReadGeneralUserSettings);
                t1.Start();
            }            
            catch (Exception ex)
            {
                RadMessageBox.Show(this, ex.Message, "Scor System Error", MessageBoxButtons.OK, RadMessageIcon.Error);
                CrxLogger oLogObject = CrxLogger.Instance;
                oLogObject.Write(ex.Message);
            }
        }
        
        /**Function to display General User Setting as well as General Default Settings.
         *It takes all the necessary settings value from the configuration object and populates the appropiate controls.
         *While populating the controls if any exception occurs it will shown to the user using a message box.
         *The corresponding exception will also be logged in the log file.
         */
        private void SetUserSettings(bool patientPrivacy, int heightWeightUnits, int bloodPressure, string commPort, string reportTitle, string reportLogoPath)
        {
            /**Setting the settings on the controls in the form.
             */ 
            try
            {               
                radchkbxPatientPrivacy.Checked = patientPrivacy;

                switch (heightWeightUnits)
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

                switch (bloodPressure)
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

                if (!defaultBtnClicked)
                {
                    if (commPort != null && comboBoxCommsPort.Items.Contains(commPort))
                    {
                        comboBoxCommsPort.Items.Remove(commPort);
                        comboBoxCommsPort.Items.Insert(0, commPort);
                        comboBoxCommsPort.SelectedIndex = 0;
                    }

                    if (reportTitle != null && reportTitle.Length > 0)
                    {
                        radtxtReportTitle.Text = reportTitle;
                    }

                    if (reportLogoPath != null && reportLogoPath.Length > 0)
                    {
                        Image image = Image.FromFile(reportLogoPath);
                        picbxReportLogo.Image = image;
                        picbxReportLogo.ImageLocation = reportLogoPath;
                        picbxReportLogo.Height = image.Height;
                        picbxReportLogo.Width = image.Width;
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
            finally
            {
                /* disable save button
                 */ 
                if (!defaultBtnClicked)
                {
                    radbtnSave.Enabled = false;
                }
            }
        }

        /**This method is used to populate the settings value on the controls.
         *Since we cannot assign values to the controls in different thread therefore invoking the parent thread.
         *Any expection thrown while reading values from the  xml file will be caught by the configuration file and caught. 
         *This expection will be shown to the user using a message box,also it will be logged into the log file.
         *Any other general excpetion will also be caught and displayed to the user.It will also be logged into the log file
         */
        private void DisplaySetings(CrxStructGeneralSetting obj)
        {
            /**Reading the settings from the configuration object.
             */ 
            try
            {
                bool patientPrivacy = obj.PatientPrivacy;
                int heightWeightUnits = obj.HeightandWeightUnit;
                int bloodPressure = obj.BloodPressureEntryOptions;

                string commsPort = obj.CommsPort;
                string reportTitle = obj.ReportTitle;
                string reportLogoPath = obj.ReportLogoPath;

                /**Settings the user settings on the controls.Since we cannot assign values to the controls in different thread therefore invoking the parent thread.
                 */ 
                if (radchkbxPatientPrivacy.InvokeRequired || radgrpbxHeightWeightUnits.InvokeRequired || radgrpbxBloodPressure.InvokeRequired || comboBoxCommsPort.InvokeRequired)
                {
                    SetUserSettingsDelegate userSettings = new SetUserSettingsDelegate(SetUserSettings);
                    this.Invoke(userSettings, new object[] { patientPrivacy, heightWeightUnits, bloodPressure, commsPort, reportTitle, reportLogoPath });
                }
            }
            catch (ConfigException cfgExp)
            {
                /**Exception if any will be logged and displayed(appropiate message) to the user.
                 */ 
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
        private void ReadGeneralUserSettings()
        {
            /**Logic to read General user settings from the configuration object.
             */ 
            try
            {
                obj = CrxConfigManager.Instance;
                obj.GetGeneralUserSettings();
                EventDisplayUserSettings(obj.GeneralSettings);
            }
            catch (ConfigException cfgExp)
            {
                /**Exception if any will be logged and displayed(appropiate message) to the user.
                 */ 
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
        private void ReadDefaultUserSettings()
        {
            /**Logic to read Default General Settings from the configuration object.
             */ 
            try
            {
                obj = CrxConfigManager.Instance;
                obj.GetGeneralDefaultSettings();
                EventDefaultGeneralSettings(obj.GeneralSettings);
            }
            catch (ConfigException cfgExp)
            {
                /**Exception if any will be logged and displayed(appropiate message) to the user.
                 */
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

                /**Append the port into the comboBox.
                 */ 
                foreach (string port in ports)
                {
                    comboBoxCommsPort.Items.Add(port);
                }

                comboBoxCommsPort.Items.Add("Simulation");
                comboBoxCommsPort.SelectedIndex = 0;
            }
            catch (Exception ex)
            {
                RadMessageBox.Show(this, ex.Message, "Scor System Error", MessageBoxButtons.OK, RadMessageIcon.Error);
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
                /**Get the main application path and save the same to restore it back
                 */ 
                string appPath = Directory.GetCurrentDirectory();

                dialog = new OpenFileDialog();
                dialog.Filter = "jpg files (*.jpg)|*.jpg";
                dialog.InitialDirectory = "C:";
                dialog.Title = "Select a Report Logo";
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
                RadMessageBox.Show(this, ex.Message, "Scor System Error", MessageBoxButtons.OK, RadMessageIcon.Error);
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
                EventDefaultGeneralSettings += new DisplayDefaultGeneralSettings(DisplaySetings);
                Thread t2 = new Thread(ReadDefaultUserSettings);
                t2.Start();

                //Enabling the Save button.
                radbtnSave.Enabled = true;

                //Flag set,indicate save button is enabled.
                defaultBtnClicked = true;
            }
            catch (Exception ex)
            {
                RadMessageBox.Show(this, ex.Message, "Scor System Error", MessageBoxButtons.OK, RadMessageIcon.Error);
                CrxLogger oLogObject = CrxLogger.Instance;
                oLogObject.Write(ex.Message);
            }
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
                obj = CrxConfigManager.Instance;

                //Setting the values into the configuration object.

                if (radchkbxPatientPrivacy != null && radchkbxPatientPrivacy.Checked)
                {
                    //set the patient privacy option accordingly.
                    obj.GeneralSettings.PatientPrivacy = true;
                }
                else
                {
                    //set the patient privacy option accordingly.
                    obj.GeneralSettings.PatientPrivacy = false;
                }

                if (radradiobtnMeric.ToggleState == Telerik.WinControls.Enumerations.ToggleState.On)
                {
                    obj.GeneralSettings.HeightandWeightUnit = 0;
                }
                else
                {
                    obj.GeneralSettings.HeightandWeightUnit = 1;
                }

                if (radradiobtnSPandDP.ToggleState == Telerik.WinControls.Enumerations.ToggleState.On)
                {
                    obj.GeneralSettings.BloodPressureEntryOptions = 0;
                }
                else if (radradiobtnSPandMP.ToggleState == Telerik.WinControls.Enumerations.ToggleState.On)
                {
                    obj.GeneralSettings.BloodPressureEntryOptions = 1;
                }
                else if (radradiobtnMPandDP.ToggleState == Telerik.WinControls.Enumerations.ToggleState.On)
                {
                    obj.GeneralSettings.BloodPressureEntryOptions = 2;
                }

                obj.GeneralSettings.CommsPort = comboBoxCommsPort.Text;
                obj.GeneralSettings.ReportTitle = radtxtReportTitle.Text.Trim();
                obj.GeneralSettings.ReportLogoPath = picbxReportLogo.ImageLocation;

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
                obj.SetGeneralUserSettings(obj.GeneralSettings);
            }
            catch (ConfigException cfgExp)
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
            RadMessageBox.Show(this, errorMessage, "Scor System Error", MessageBoxButtons.OK, RadMessageIcon.Error);
        }

        /**This is a common function for Blood pessure ,Pateint privacy and height weight units.On change of any of the 
mentioned settings,Save button is enabled.
         *If any exception occurs it will be caught and displayed to the user using a message box.
         *The corresponding exception will also be logged in the log file.
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
         * If any exception occurs it will be caught and displayed to the user using a message box.
         * The corresponding exception will also be logged in the log file.
         */ 
        private void comboBoxCommsPort_SelectionChangeCommitted(object sender, EventArgs e)
        {
            radbtnSave.Enabled = true;
        }
    }
}
