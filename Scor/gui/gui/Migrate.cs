/*
     Copyright (C) ATCOR MEDICAL PTY LTD, 2010
 
     Filename     :     Migrate
        
     Author       :     Vibhuti Damania
 
     Description  :     Functionality implemented for showing available group names for migration
*/

using System;
using System.Windows.Forms;
using Telerik.WinControls;
using AtCor.Scor.CrossCutting.Configuration;
using AtCor.Scor.CrossCutting.DatabaseManager;
using AtCor.Scor.CrossCutting.Messaging;
using Telerik.WinControls.UI;

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
    public partial class Migrate : RadForm
    {                     
        public static int IsMigrate = 0;
        
        public delegate void HandleMigration(string groupName);

        public static event HandleMigration OnMigrationStart;
        
        readonly CrxMessagingManager oMsgMgr = CrxMessagingManager.Instance;
        readonly CrxConfigManager crxMgrObject = CrxConfigManager.Instance;
        CrxDBManager dbMagr;

        readonly string serverNameString = string.Empty;        
        
        /**Constructor to initialize the components and disable the close icon on the title bar.
        */
        public Migrate()
        {
            InitializeComponent();
            GuiCommon.SetFontForControls(this);
            serverNameString = GuiCommon.ServerNameString(); 

            GuiCommon.SetShape(guicmbGroupNameList);           
        }

        /**This event is fired on the load of the form. Fetches group name from database
       */
        private void Migrate_Load(object sender, EventArgs e)
        {
            try
            {
                SetText();
                LoadGroupNames();
            }
            catch (Exception ex)
            {
                GUIExceptionHandler.HandleException(ex, this);  
            }
        }

        private  void SetText()
        {
            try
            {
                guiradlblHeader.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.MigrateHeaderTxt);
                Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.MigrateTitleTxt);
                radbtnCancel.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.BtnCancel);
                radbtnMigrate.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.BtnMigrate);
            }
            catch (Exception ex)
            {
                GUIExceptionHandler.HandleException(ex, this);
            }
        }

        /** This event fires when migrate button is clicked. It migrates existing records from the mdb file
         * */
        private void radbtnMigrate_Click(object sender, EventArgs e)
        {
            try
            {
                // check if group name is entered and call method to migrate record
                if (guicmbGroupNameList.Text.Equals(oMsgMgr.GetMessage(CrxStructCommonResourceMsg.SelectCaps), StringComparison.CurrentCultureIgnoreCase) || string.IsNullOrEmpty(guicmbGroupNameList.Text.Trim()))
                {
                    // show error
                    RadMessageBox.Show(this, oMsgMgr.GetMessage(CrxStructCommonResourceMsg.MigrateValidationMsg), oMsgMgr.GetMessage(CrxStructCommonResourceMsg.SystemError), MessageBoxButtons.OK, RadMessageIcon.Error);
                }
                else
                {
                    // call migrate method in a separate thread
                    IsMigrate = Convert.ToInt32(GuiCommon.NumericValue.One);

                    OnMigrationStart.Invoke(guicmbGroupNameList.Text.Trim());
                    Close();
                }
            }
            catch (Exception ex)
            {
                GUIExceptionHandler.HandleException(ex, this);  
            }
        }
        
        /**This method is used to populate the group names into the combo box from the database using database manager class. 
     */
        private void LoadGroupNames()
        {
            // fetches group name and binds it
            try
            {
                dbMagr = CrxDBManager.Instance;
                if (dbMagr.CheckConnection(serverNameString, crxMgrObject.GeneralSettings.SourceData) == Convert.ToInt32(GuiCommon.NumericValue.Zero))
                {
                   GuiCommon.BindGroupNames(guicmbGroupNameList, dbMagr);
                }
                else
                {
                    DialogResult result = RadMessageBox.Show(this, GuiCommon.ConnectionErrorString(), oMsgMgr.GetMessage(CrxStructCommonResourceMsg.SystemError), MessageBoxButtons.RetryCancel, RadMessageIcon.Error);
                    if (result == DialogResult.Retry)
                    {
                        LoadGroupNames();
                    }
                    else
                    {
                        Close();
                    }
                }
            }
            catch (Exception ex)
            {
                GUIExceptionHandler.HandleException(ex, this);
            }          
        }

        /** This event fires on cancel button click. It closes migrate window
         * */
        private void radbtnCancel_Click(object sender, EventArgs e)
        {
            try
            {
                Close();
            }
            catch (Exception ex)
            {
                GUIExceptionHandler.HandleException(ex, this);
            }
        }        
    }
}