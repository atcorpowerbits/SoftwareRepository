/*
     Copyright (C) ATCOR MEDICAL PTY LTD, 2010
 
     Filename     :     Migrate
        
     Author       :     Vibhuti Damania
 
     Description  :     Functionality implemented for showing available group names for migration
*/

using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using Telerik.WinControls;
using AtCor.Scor.CrossCutting.Configuration;
using AtCor.Scor.CrossCutting.DatabaseManager;
using AtCor.Scor.CrossCutting.Logging;
using AtCor.Scor.CrossCutting.Messaging;
using AtCor.Scor.CrossCutting;
using System.Threading;

/**
 * @namespace AtCor.Scor.Gui.Presentation
 * @brief This namespace implements Presentation related classes.
 * 
 */
namespace AtCor.Scor.Gui.Presentation
{
    /**
    * @class Migrate
    * @brief This class is used to select groupnames from available groupname in current database to migrate patient records for selected group names
    */
    public partial class Migrate : Telerik.WinControls.UI.RadForm
    {                     
        public static int IsMigrate = 0;
        
        public delegate void HandleMigration(string groupName);

        public static event HandleMigration OnMigrationStart;

        private const int CP_NOCLOSE_BUTTON = 0x200;

        CrxMessagingManager oMsgMgr = CrxMessagingManager.Instance;
        CrxConfigManager crxMgrObject = CrxConfigManager.Instance;
        CrxLogger oLogObject = CrxLogger.Instance;
        CrxDBManager dbMagr;

        string serverNameString = string.Empty;        
        
        /**Constructor to initialize the components and disable the close icon on the title bar.
        */
        public Migrate()
        {
            InitializeComponent();
            
            serverNameString = SettingsProperties.ServerNameString(); 

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

        /**This event is fired on the load of the form. Fetches group name from database
       */
        private void Migrate_Load(object sender, EventArgs e)
        {
            SetText();
            LoadGroupNames();
        }

        void SetText()
        {
            guiradlblHeader.Text = oMsgMgr.GetMessage("MIGRATE_HEADER_TXT");
            this.Text = oMsgMgr.GetMessage("MIGRATE_TITLE_TXT");
            radbtnCancel.Text = oMsgMgr.GetMessage("BTN_CANCEL");
            radbtnMigrate.Text = oMsgMgr.GetMessage("BTN_MIGRATE");
        }

        /** This event fires when migrate button is clicked. It migrates existing records from the mdb file
         * */
        private void radbtnMigrate_Click(object sender, EventArgs e)
        {
            // check if group name is entered and call method to migrate record
            if (guicmbGroupNameList.Text.Equals(oMsgMgr.GetMessage("SELECT_CAPS"), StringComparison.CurrentCultureIgnoreCase) || string.IsNullOrEmpty(guicmbGroupNameList.Text.Trim()))
            {
                // show error
                RadMessageBox.Show(this, oMsgMgr.GetMessage("MIGRATE_VALIDATION_MSG"), oMsgMgr.GetMessage("SYSTEM_ERROR"), MessageBoxButtons.OK, RadMessageIcon.Error);
            }
            else
            { 
                // call migrate method in a separate thread
                IsMigrate = 1;
              
                OnMigrationStart.Invoke(guicmbGroupNameList.Text.Trim());
                this.Close();                
            }
        }
        
        /**This method is used to populate the group names into the combo box from the database using database manager class. 
     */
        void LoadGroupNames()
        {
            // fetches group name and binds it
            try
            {
                dbMagr = CrxDBManager.Instance;
                if (dbMagr.CheckConnection(serverNameString, crxMgrObject.GeneralSettings.SourceData) == 0)
                {
                    DataSet ds = new DataSet();
                    ds = dbMagr.GetGroupLists();

                    DataRow dr = ds.Tables[0].NewRow();
                    dr["GroupName"] = oMsgMgr.GetMessage("SELECT_CAPS"); // "--Select--";
                    dr["GroupIdentifier"] = 0;

                    ds.Tables[0].Rows.InsertAt(dr, 0);

                    guicmbGroupNameList.DataSource = ds.Tables[0];
                    guicmbGroupNameList.DisplayMember = "GroupName";

                    guicmbGroupNameList.SelectedIndex = 0;
                }
                else
                {
                    DialogResult result = RadMessageBox.Show(this, SettingsProperties.ConnectionErrorString(), oMsgMgr.GetMessage("SYSTEM_ERROR"), MessageBoxButtons.RetryCancel, RadMessageIcon.Error);
                    if (result == DialogResult.Retry)
                    {
                        LoadGroupNames();
                    }
                }
            }
            catch (Exception ex)
            {
                GUIExceptionHandler.HandleException(ex, this);
            }

          /*  catch (CrxException ex)
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
            }*/
        }

        /** This event fires on cancel button click. It closes migrate window
         * */
        private void radbtnCancel_Click(object sender, EventArgs e)
        {
            this.Close();
        }        
    }
}
