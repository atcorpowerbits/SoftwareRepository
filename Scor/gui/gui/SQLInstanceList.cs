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
using System.Data.Sql;
using System.Data;
using System.Windows.Forms;
using System;
using Telerik.WinControls.UI;
using System.Drawing;
using Telerik.WinControls.Primitives;
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
    public partial class SQLInstanceList : RadForm
    {
        public static int IsCancel;
        readonly CrxConfigManager crxMgrObject = CrxConfigManager.Instance;
        readonly CrxMessagingManager oMsgMgr = CrxMessagingManager.Instance;
        readonly CrxLogger oLogObject = CrxLogger.Instance;
        
        CrxDBManager dbMagr;
        string serverNameString = string.Empty;

        public delegate void InitializationMessage(string message);

        public static event InitializationMessage OnInitializationProcess;

        /**Constructor to initialize the components and diable the close icon on the title bar.
        */
        public SQLInstanceList()
        {
            InitializeComponent();
            serverNameString = GuiCommon.ServerNameString(); 
            
            // Disable the close button of the window.
            FormElement.TitleBar.CloseButton.Enabled = false;
            GuiCommon.SetShape(guicmbxSqlServerList);
        }       

        protected override CreateParams CreateParams
        {
            get
            {
                CreateParams myCp = base.CreateParams;
                myCp.ClassStyle = myCp.ClassStyle | GuiConstants.CpNocloseButton;
                return myCp;
            }
        }

        /**This event is fired on the load of the form.
         * It will list down all available server available on the LAN 
         * and accordingly the user is able to select the server and connect to it.
        */
        private void SQLInstanceList_Load(object sender, EventArgs e)
        {
            DisplayAndLogMessage();
            AcceptButton = guiradbtnConnect;
            CancelButton = guiradbtnCancel;
            MaximumSize = Size;
            MinimumSize = Size;
            
            // log status of database connection.
            try
            {
                // below code returns all the sql server instances available in a network with instance name for running instances, it gives values (server name, instance name, isclustered, version)
                SqlDataSourceEnumerator getCurInst = SqlDataSourceEnumerator.Instance;
                DataTable dt = getCurInst.GetDataSources();

                guicmbxSqlServerList.DataSource = dt;
                guicmbxSqlServerList.DisplayMember = "ServerName";
                OnInitializationProcess.Invoke(oMsgMgr.GetMessage(CrxStructCommonResourceMsg.BtnExit));
                SetTextForControls();
            }
            catch (Exception ex)
            {
                GUIExceptionHandler.HandleException(ex, this);
            }            
        }

        private void SetShape(params Control[] labelControl)
        {
            RoundRectShape shape = new RoundRectShape
                                       {
                                           BottomLeftRounded = true,
                                           BottomRightRounded = true,
                                           TopLeftRounded = true,
                                           TopRightRounded = true,
                                           Radius = 5
                                       };

            foreach (Control control in labelControl)
            {
                RadDropDownList dropDownlist = control as RadDropDownList;
                if (dropDownlist != null)
                {
                    dropDownlist.DropDownListElement.Shape = shape;
                    dropDownlist.DropDownListElement.EditableElement.Shape = shape;

                    dropDownlist.DropDownListElement.ArrowButton.Shape = shape;
                    dropDownlist.DropDownListElement.ArrowButton.Fill.NumberOfColors = 1;
                    dropDownlist.DropDownListElement.ArrowButton.Fill.BackColor = Color.FromArgb(142, 150, 186);
                    ((FillPrimitive)dropDownlist.DropDownListElement.Children[3]).BackColor = Color.FromArgb(142, 150, 186);
                }
            }        
        }

        /**This event is fired when the cancel button is clicked.It will close the application.
        */
        private void guiradbtnCancel_Click(object sender, EventArgs e)
        {
            IsCancel = 1;
            Close();            
        }

        /**This event is fired when the user clicks on connect after selecting a server 
         * from the drop down list.
        */
        private void guiradbtnConnect_Click(object sender, EventArgs e)
        {
            crxMgrObject.GeneralSettings.MachineName = guicmbxSqlServerList.Text;

            serverNameString = GuiCommon.ServerNameString(); 
 
            // set the source data settings to SQL as we are listing only SQL servers on the network
            crxMgrObject.GeneralSettings.SourceData = GuiConstants.SourceData;

            dbMagr = CrxDBManager.Instance;
            int result = dbMagr.SetConnection(serverNameString, crxMgrObject.GeneralSettings.SourceData);

            // Connection failed
            if (result.Equals(1)) 
            {
                DisplayAndLogMessage();
            }            
            else 
            {
                oLogObject.Write(oMsgMgr.GetMessage(CrxStructCommonResourceMsg.SqlServerConnected) + serverNameString);                
                crxMgrObject.SetGeneralUserSettings(crxMgrObject.GeneralSettings);  
                Close();
            }
        }

        /**This method is called to display the message on the connection status.
        */
        private void DisplayAndLogMessage()
        {
            guiradlblMessage.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.SqlServerUnableToConnect) + serverNameString + oMsgMgr.GetMessage(CrxStructCommonResourceMsg.GuiDisplayComma) + oMsgMgr.GetMessage(CrxStructCommonResourceMsg.GuiSelectSqlInstance);
            oLogObject.Write(oMsgMgr.GetMessage(CrxStructCommonResourceMsg.SqlServerFailed) + serverNameString); 
        }

        /**This method is used to set the text for the controls on the form.
        */
        private void SetTextForControls()
        {
            guiradbtnConnect.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.GuiSqlInstanceConnect);
            guiradbtnCancel.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.BtnCancel);
        }
    }
}
