/*
     Copyright (C) ATCOR MEDICAL PTY LTD, 2010
 
     Filename     :     SQL Instance List
        
     Author       :     Nitesh Chhedda
 
     Description  :     Functionality implemented for showing available Servers on LAN.
*/

using AtCor.Scor.CrossCutting.Configuration;
using AtCor.Scor.CrossCutting.DatabaseManager;
using AtCor.Scor.CrossCutting.Logging;
using AtCor.Scor.CrossCutting.Messaging;
using AtCor.Scor.CrossCutting;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data.Sql;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using System;
using Telerik.WinControls;

/**
 * @namespace AtCor.Scor.Gui.Presentation
 * @brief This namespace implements Presentation related classes.
 * 
 */
namespace AtCor.Scor.Gui.Presentation
{
    /**
    * @class SQLInstanceList
    * @brief This class is used to set show all the available SQL Server in a drop down list.
     *       On selection of one of the server the class checks for the authentication with the server.Once the authentication is done,the new server name is logged inot the config file.
    */
    public partial class SQLInstanceList : Telerik.WinControls.UI.RadForm
    {
        public static int IsCancel = 0;
        private const int CP_NOCLOSE_BUTTON = 0x200;
        SqlDataSourceEnumerator getCurInst = SqlDataSourceEnumerator.Instance;
        CrxConfigManager crxMgrObject = CrxConfigManager.Instance;
        CrxMessagingManager oMsgMgr = CrxMessagingManager.Instance;
        CrxLogger oLogObject = CrxLogger.Instance;
        DataTable dt;
        CrxDBManager dbMagr;
        string serverNameString = string.Empty;

        public delegate void InitializationMessage(string message);

        public static event InitializationMessage OnInitializationProcess;

        /**Constructor to initialize the components and diable the close icon on the title bar.
        */
        public SQLInstanceList()
        {
            InitializeComponent();
            serverNameString = SettingsProperties.ServerNameString(); // crxMgrObject.GeneralSettings.MachineName.Trim() + "\\" + crxMgrObject.GeneralSettings.ServerName.Trim();
            // Disable the close button of the window.
            this.FormElement.TitleBar.CloseButton.Enabled = false;
        }       

        protected override CreateParams CreateParams
        {
            get
            {
                CreateParams myCp = base.CreateParams;
                myCp.ClassStyle = myCp.ClassStyle | CP_NOCLOSE_BUTTON;
                return myCp;
            }
        }

        /**This event is fired on the load of the form.It will list down all available server available on the LAN and accordingly the user is able to select the server and connect to it.
        */
        private void SQLInstanceList_Load(object sender, EventArgs e)
        {
            DisplayAndLogMessage();
            this.AcceptButton = guiradbtnConnect;
            this.CancelButton = guiradbtnCancel;
            
            // log status of database connection.
            try
            {
                // below code returns all the sql server instances available in a network with instance name for running instances, it gives values (server name, instance name, isclustered, version)
                SqlDataSourceEnumerator getCurInst = SqlDataSourceEnumerator.Instance;
                dt = getCurInst.GetDataSources();

                guicmbxSqlServerList.DataSource = dt;
                guicmbxSqlServerList.DisplayMember = "ServerName";
                OnInitializationProcess.Invoke(oMsgMgr.GetMessage("BTN_EXIT"));
            }
            catch (Exception ex)
            {
                GUIExceptionHandler.HandleException(ex, this);
            }            
        }

        /**This event is fired when the cancel button is clicked.It will close the application.
        */
        private void guiradbtnCancel_Click(object sender, EventArgs e)
        {
            IsCancel = 1;
            this.Close();            
        }

        /**This event is fired when the user clicks on connect after selecting a server from the drop down list.
        */
        private void guiradbtnConnect_Click(object sender, EventArgs e)
        {
                int result = 0;

                // guiradlblMessage.Text = string.Empty;
                crxMgrObject.GeneralSettings.MachineName = guicmbxSqlServerList.Text;
                crxMgrObject.GeneralSettings.ServerName = "SQLEXPRESS";
                serverNameString = SettingsProperties.ServerNameString(); // crxMgrObject.GeneralSettings.MachineName.Trim() + crxMgrObject.GeneralSettings.ServerName.Trim();
 
            crxMgrObject.GeneralSettings.SourceData = "SQLCLIENT";
            dbMagr = CrxDBManager.Instance;
            result = dbMagr.SetConnection(serverNameString, crxMgrObject.GeneralSettings.SourceData);
            if (result.Equals(1))
            {
                DisplayAndLogMessage();
            }
            else
            {
                oLogObject.Write(oMsgMgr.GetMessage("SQL_SERVER_CONNECTED") + serverNameString);                
                crxMgrObject.SetGeneralUserSettings(crxMgrObject.GeneralSettings);  
                this.Close();
            }
        }

        /**This method is called to display the message on the connection status.
        */
        private void DisplayAndLogMessage()
        {
            guiradlblMessage.Text = oMsgMgr.GetMessage("SQL_SERVER_UNABLE_TO_CONNECT") + serverNameString + ",select another server from the below list.";
            oLogObject.Write(oMsgMgr.GetMessage("SQL_SERVER_FAILED") + serverNameString); 
        }

        /**This event is fired when the selection in the drop down is changed.
         */ 
        private void guicmbxSqlServerList_SelectedIndexChanged(object sender, EventArgs e)
        {
           // guiradlblMessage.Text = string.Empty; 
        }
    }
}
