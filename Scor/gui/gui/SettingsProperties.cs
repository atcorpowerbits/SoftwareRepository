/*
     Copyright (C) ATCOR MEDICAL PTY LTD, 2010
 
     Filename     :     Settings properties
        
     Author       :     Nitesh Chhedda
 
     Description  :     Common class for defining global variables, method, properties etc
*/
using System;
using AtCor.Scor.CrossCutting.Configuration;
using AtCor.Scor.CrossCutting.Messaging;
using AtCor.Scor.CrossCutting.Logging;
using System.Windows.Forms;
using System.Configuration;

namespace AtCor.Scor.Gui.Presentation
{
    // public delegate void SettingsChangedEventHandler(Object sender,EventArgs  args);   
   public static class SettingsProperties
   {
       ////#region struct
       ////public struct registyKeyInfo
       ////{
       ////   public static string environment = string.Empty;         
       ////};
       ////#endregion
            
       // public event SettingsChangedEventHandler OnSettingsChangedEvent;
       #region Global variable declaration
       public static bool SetupToReport = false;
       public static bool CaptureToReport = false;
       public static bool CaptureToSetup = false;
       public static bool HasMeasurementDetails = false;
       public static string Environment = string.Empty;
       public static bool CaptureTabClick = true;

       #region Main / Parent window Handle
       public static DefaultWindow defaultWindowForm;
       #endregion      

       public delegate void SetCaptureTabVisibility(bool value);

       public static event SetCaptureTabVisibility OnCaptureClosing;

       #endregion
       #region Child Form Handles
       public static Telerik.WinControls.UI.RadForm reportChildForm;
        public static Telerik.WinControls.UI.RadForm captureChildForm;
        public static Telerik.WinControls.UI.RadForm setupChildForm;

        public static Telerik.WinControls.UI.RadForm frmRptBlnk;
        #endregion

        #region Global variable declaration

        public static string Gci = string.Empty;
        public static bool IsWaitIntervalImposed = false; // this variable checks for 30 sec wait interval imposed by EM4 when coming from capture to setup
        public static bool IsFormChanged = false; // this variable tracks any changes to the application form 
        public static int ReportLoadCount = 0;
        #endregion

        #region General settings private variables

       #endregion

        #region PWV settings private variables

       static SettingsProperties()
       {
           ReferenceRange = false;
           CuffLocation = false;
           CaptureTime = 0;
           PwvDistanceMethod = 0;
           PwvDistanceUnits = 0;
           PwvCurrentStudyDatetime = string.Empty;
           PatientPrivacy = false;
           BloodPressure = 0;
           HeightWeightUnits = 0;
           GroupName = string.Empty;
           GroupID = 0;
           PatientInternalNumber = 0;
           SystemIdentifier = 0;
       }

       #endregion

        #region General settings properties

       public static int SystemIdentifier { get; set; }

       public static int PatientInternalNumber { get; set; }

       public static int GroupID { get; set; }

       public static string GroupName { get; set; }

       public static int HeightWeightUnits { get; set; }

       public static int BloodPressure { get; set; }

       public static bool PatientPrivacy { get; set; }

       #endregion

        #region PWV settings properties

       public static string PwvCurrentStudyDatetime { get; set; }

       public static int PwvDistanceUnits { get; set; }

       public static int PwvDistanceMethod { get; set; }

       public static int CaptureTime { get; set; }

       public static bool CuffLocation { get; set; }

       public static bool ReferenceRange { get; set; }

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

            string serverName;

            if (crxMgrObject.GeneralSettings.ServerName == null)
            {
                crxMgrObject.GeneralSettings.ServerName = ConfigurationManager.AppSettings["DefaultInstanceName"].ToString();
            }

            serverName = crxMgrObject.GeneralSettings.MachineName.Trim() + @"\" + crxMgrObject.GeneralSettings.ServerName.Trim();

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
                errorMsg += oMsgMgr.GetMessage("SQL_NETWORK_ERROR_STRG") + "\r\n\r\n";
            }
            else
            {
                errorMsg += oMsgMgr.GetMessage("SQL_LOCAL_ERROR_STRG") + "\r\n\r\n";
            }

            errorMsg += oMsgMgr.GetMessage("CONTACT_ATCOR_SUPPORT"); // +"\r\n" + oMsgMgr.GetMessage("CONTACT_ATCOR_SUPPORT1");

            // log the error
            CrxLogger.Instance.Write(errorMsg);

            return errorMsg;
        }

       /** This method gets environment information
        * */
        public static string GetEnvironment()
        {
            CrxMessagingManager oMsgMgr = CrxMessagingManager.Instance;

            // registyKeyInfo regKey = new registyKeyInfo(oMsgMgr.GetMessage("ENV_CLINICAL_TEXT"));
            Environment = oMsgMgr.GetMessage("ENV_CLINICAL_TEXT");
            return Environment;
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
        #endregion
    }
}
