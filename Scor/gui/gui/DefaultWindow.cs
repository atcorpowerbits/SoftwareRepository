/*
     Copyright (C) ATCOR MEDICAL PTY LTD, 2010
 
    Filename     :      Default Window
        
        Author       :  Nitesh Chhedda
 
     Description  :      This is the Default Window on Application load.
*/
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

namespace AtCor {
namespace Scor {
namespace Presentation
{
    /**
	 * @class		Class for Default Window when the application loads.
	 * @brief		This class will handle displaying of the default window controls.It will also check for multiple instances of the application,exception handling and logging of events.
	 */   
    public partial class DefaultWindow : Telerik.WinControls.UI.RadRibbonForm
    {
        #region Global declarations
        /**Used to set message codes.
        *set message codes.All messages will come from messaging meanager and hence from resource file.
        */
        const int EXITSTR = 10001;
        const int STARTSTR = 10000;

        //Creating object of onfiguration file.
        //CrxConfigManager obj;

        /**Flag set to check if there are multiple instances of the application.
         */
        bool isDirectClose;

        /**object of Config Manager
         */ 
        CrxMessagingManager oCrxMgr;
        
        //public delegate object ReadConfigObject();
        
        #endregion
        
        /**Constructor of the form,initializes all the controls.
        *It will call IsProcessOpen method which will check if there is any other instance is running.
        */
        public DefaultWindow()
        {
            try
            {
                /** initialize class level variables
                */
                isDirectClose = false;
                oCrxMgr = CrxMessagingManager.Instance;

                /**Logic to check multiple instances of the application.
                 */ 
                if (IsProcessOpen("scor"))
                {
                    isDirectClose = true;
                    DialogResult ds = RadMessageBox.Show(this, "Another instance already running, cannot continue.", "Scor Execution Error", MessageBoxButtons.OK, RadMessageIcon.Error);
                    this.Close();
                }

                InitializeComponent();
            }
            catch (Exception ex)
            {
                RadMessageBox.Show(this, ex.Message, "Scor System Error", MessageBoxButtons.OK, RadMessageIcon.Error);
                CrxLogger oLogObject = CrxLogger.Instance;
                oLogObject.Write(ex.Message);                
            }
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
            /**On form closing a confirmation is asked to the user to Save the unsaved data.
             */
                if (!isDirectClose)
                {
                    RadMessageBox.SetThemeName("Desert");
                    DialogResult ds = RadMessageBox.Show(this, "Do you want to save changes?", "Save Settings", MessageBoxButtons.YesNoCancel, RadMessageIcon.Question);

                    /** Keeping Yes and No separate for future use.
                     */
                    if (ds == DialogResult.Yes)
                    {
                        //Save data then exit.Application exited
                        CrxLogger oLogObject = CrxLogger.Instance;
                        oLogObject.Write(oCrxMgr.GetMessage(EXITSTR));
                    }

                    if (ds == DialogResult.No)
                    {
                        /**DO NOT Save data then exit.
                         */ 
                        CrxLogger oLogObject = CrxLogger.Instance;
                        oLogObject.Write(oCrxMgr.GetMessage(EXITSTR));
                    }

                    if (ds == DialogResult.Cancel)
                    {
                        /**Cancel the close event.
                         */ 
                        e.Cancel = true;
                    }
                }
            }
            catch (Exception ex)
            {
                RadMessageBox.Show(this, ex.Message, "Scor System Error", MessageBoxButtons.OK, RadMessageIcon.Error);
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
                /** check if we can access the configuration file by reading general setting from config manager object.
                 */ 
                CrxConfigManager oConfigMgr = CrxConfigManager.Instance;
                oConfigMgr.GetGeneralUserSettings();              

                /**On windows load set the windows size to maximum.
                 */ 
                WindowState = FormWindowState.Maximized;

                /**Log the event on successful load of the application.
                 */ 
                CrxLogger oLogObject = CrxLogger.Instance;
                oLogObject.Write(oCrxMgr.GetMessage(STARTSTR));
            }
            catch (ConfigException cfgExp)
            {
                /**Exception if any will be logged and displayed(appropiate message) to the user.
                 */ 
                CrxMessagingManager oMsgMgr = CrxMessagingManager.Instance;
                string errorMessage = oMsgMgr.GetMessage(cfgExp.ErrorCode);

                /**show error on screen
                 */ 
                RadMessageBox.Show(this, errorMessage, "Scor System Error", MessageBoxButtons.OK, RadMessageIcon.Error);

                /**write message in log file
                 */ 
                CrxLogger oLogObject = CrxLogger.Instance;
                oLogObject.Write(errorMessage);

                /**close the application.
                *do not ask question to save data.
                 */
                isDirectClose = true;
                this.Close();
            }
            catch (Exception ex)
            {
                RadMessageBox.Show(this, ex.Message, "Scor System Error", MessageBoxButtons.OK, RadMessageIcon.Error);
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
                /**Open the settings dialog box.
                 */ 
                SettingsWindow settingWinObject = new SettingsWindow();
                settingWinObject.ShowDialog();
            }
            catch (Exception ex)
            {
                RadMessageBox.Show(this, ex.Message, "Scor System Error", MessageBoxButtons.OK, RadMessageIcon.Error);
                CrxLogger oLogObject = CrxLogger.Instance;
                oLogObject.Write(ex.Message);             
            }
        }
    }
}
}
}
