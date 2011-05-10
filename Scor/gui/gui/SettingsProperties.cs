/*
     Copyright (C) ATCOR MEDICAL PTY LTD, 2010
 
     Filename     :     Settings properties
        
     Author       :     Nitesh Chhedda
 
     Description  :     Common class for defining global variables, method, properties etc
*/
using System;
using AtCor.Scor.CrossCutting;
using AtCor.Scor.CrossCutting.Configuration;
using AtCor.Scor.CrossCutting.Messaging;
using AtCor.Scor.CrossCutting.Logging;
using AtCor.Scor.CrossCutting.DatabaseManager;
using System.Windows.Forms;
using System.Configuration;
using System.Data;
using Telerik.WinControls.UI;

/**
 * @namespace AtCor.Scor.Gui.Presentation
 * @brief This namespace implements Presentation related classes.
 * 
 */
namespace AtCor.Scor.Gui.Presentation
{
    /**
  * @class SettingsProperties
  * @brief This class contains global variables and methods which are used across different forms
  */
    public static class SettingsProperties
   {
       #region Global variable declaration
       public static bool SetupToReport = false;
       public static bool CaptureToReport = false;
       public static bool CaptureToSetup = false;
       public static bool HasMeasurementDetails = false;
       
       public static bool CaptureTabClick = true;
       public static RadPageViewPage TabFocused;
       public static bool IsWaitIntervalImposed = false; // this variable checks for 30 sec wait interval imposed by EM4 when coming from capture to setup
       public static bool IsFormChanged = false; // this variable tracks any changes to the application form 
       public static int ReportLoadCount = 0;
       #endregion

       #region Main / Parent window Handle
       public static DefaultWindow DefaultWindowForm;
       #endregion      

       public delegate void SetCaptureTabVisibility(bool value);

       public static event SetCaptureTabVisibility OnCaptureClosing;
       
       #region Child Form Handles
       public static Telerik.WinControls.UI.RadForm ReportChildForm;
        public static Telerik.WinControls.UI.RadForm CaptureChildForm;
        public static Telerik.WinControls.UI.RadForm SetupChildForm;

        public static Telerik.WinControls.UI.RadForm FrmRptBlnk;
        #endregion  

        #region PWV settings private variables

       static SettingsProperties()
       {
           PwvCurrentStudyDatetime = string.Empty;
           GroupName = string.Empty;
           GroupId = 0;
           PatientInternalNumber = 0;
           SystemIdentifier = 0;
       }

       #endregion

        #region General settings properties

       public static int SystemIdentifier { get; set; }

       public static int PatientInternalNumber { get; set; }

       public static int GroupId { get; set; }

       public static string GroupName { get; set; }      

       #endregion

        #region PWV settings properties

       public static string PwvCurrentStudyDatetime { get; set; }             

       #endregion

        #region methods..
       
       /** This method is called on the form closing of the capture screen,to impose wait interval.
        */
       public static void InvokeCaptureClosing(bool value)
       {
           OnCaptureClosing.Invoke(value);
       }

        /** This method retrieves database servername
        * */
        public static string ServerNameString()
        {
            CrxConfigManager crxMgrObject = CrxConfigManager.Instance;

            if (crxMgrObject.GeneralSettings.ServerName == null)
            {
                crxMgrObject.GeneralSettings.ServerName = ConfigurationManager.AppSettings["DefaultInstanceName"].ToString();
            }

            string serverName = crxMgrObject.GeneralSettings.MachineName.Trim() + @"\" + crxMgrObject.GeneralSettings.ServerName.Trim();

            if (serverName.EndsWith("\\"))
            {
                serverName = serverName.Replace("\\", string.Empty);
            }

            return serverName;
        }

       /** This method retrieves error message during network connection failure
        * */
        public static string ConnectionErrorString()
        {
            string errorMsg = string.Empty;

            // initialize servername string with static method ServerNameString()
            string servername = ServerNameString();
            CrxMessagingManager oMsgMgr = CrxMessagingManager.Instance;            
          
            // string for CONTACT_ATCOR_SUPPORT defined as per jira comments in SWREQ007
            if (!servername.Contains(SystemInformation.ComputerName))
            {
                // remote PC
                errorMsg += oMsgMgr.GetMessage(CrxStructCommonResourceMsg.SqlNetworkErrorStrg) + Environment.NewLine;
            }
            else
            {
                errorMsg += oMsgMgr.GetMessage(CrxStructCommonResourceMsg.SqlLocalErrorStrg) + Environment.NewLine;
            }

            errorMsg += oMsgMgr.GetMessage(CrxStructCommonResourceMsg.ContactAtcorSupport); 

            // log the error
            CrxLogger.Instance.Write(errorMsg);

            return errorMsg;
        }             

        /** This method opens print dialog for printer settings
         * It will set the aplication default printer to the one mentioned in scor.config file
         * For any changes in aplication default printer will be saved to scor.config
         * */
        public static void ViewPrintDialogToSetPrinter(PrintDialog printDialog)
        {
            CrxConfigManager crxMgrObject = CrxConfigManager.Instance;

            // read from config file and set default printer
            if (crxMgrObject.GeneralSettings.PrinterName != null && !string.IsNullOrEmpty(crxMgrObject.GeneralSettings.PrinterName))
            {
                // below line sets printername available in config file as default printer and also assigns this name to the current printer dialog
                printDialog.PrinterSettings.PrinterName = crxMgrObject.GeneralSettings.PrinterName;
            }

            // opens printer dialog            
            if (printDialog != null)
            {
                printDialog.ShowDialog();
                        
                // store the currently selected printer in config file... this will be done only if apply button is clicked in print dialog box
                crxMgrObject.GeneralSettings.PrinterName = printDialog.PrinterSettings.PrinterName;
            }

            crxMgrObject.SetGeneralUserSettings(crxMgrObject.GeneralSettings);
        }

        /** This method is sets the flag for form changed to true
         * This method is subscribe to textchanged event for each textboxes, selection changes for drop downs etc on all the pages applicable.
         * For any changes in textbox this method will be called which will set IsFormChanged flag to true
         * On application closing this flag will be checked & accordingly messages will be shown to user before closing
         * */
        public static void FormChanged(object sender, EventArgs e)
        {
            IsFormChanged = true;            
        }

        /** This method gets list of groupnames from database and binds the same to the combo box passed
        * */
        public static void BindGroupNames(ComboBox cmbxGroup, CrxDBManager dbMagr)
        {
            // fetches group name and binds it
            CrxMessagingManager oMsgMgr = CrxMessagingManager.Instance;

            DataSet ds = dbMagr.GetGroupLists();

            if (ds != null)
            {
                DataRow dr = ds.Tables[0].NewRow();
                dr[(int)CrxDBGroupList.GroupName] = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.SelectCaps);
                dr[(int)CrxDBGroupList.GroupIdentifier] = 0;

                ds.Tables[0].Rows.InsertAt(dr, 0);

                cmbxGroup.DataSource = ds.Tables[0];
                cmbxGroup.DisplayMember = CrxDBGroupList.GroupName.ToString();

                cmbxGroup.SelectedIndex = 0;
            }            
        }

       /** This method restricts input values to integers only
        * */
        public static void CheckForNumericValues(object sender, KeyPressEventArgs e)
        {
            if (!char.IsDigit(e.KeyChar))
            {
                e.Handled = true;
            }

            if (e.KeyChar == '\b')
            {
                e.Handled = false;
            }
        }

        /** This method sets font configured in app.config for the controls on form
         * It takes parameter radform
         * */
        public static void SetFontForControls(RadForm frm)
        {
            System.Drawing.Font font = new System.Drawing.Font(GuiConstants.FontName, 8);
            foreach (Control ctrl in frm.Controls)
            {
                if (ctrl.Font.Size == font.Size)
                {
                    ctrl.Font = font;
                }
                else
                {
                    font = new System.Drawing.Font(GuiConstants.FontName, ctrl.Font.Size);
                }
            }
        }
        #endregion
    }
}
