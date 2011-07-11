/*
     Copyright (C) ATCOR MEDICAL PTY LTD, 2010
 
     Filename     :     Settings properties
        
     Author       :     Nitesh Chhedda
 
     Description  :     Common class for defining global variables, method, properties etc
*/
using System;
using System.Drawing;
using AtCor.Scor.CrossCutting.Configuration;
using AtCor.Scor.CrossCutting.Messaging;
using AtCor.Scor.CrossCutting.Logging;
using AtCor.Scor.CrossCutting.DatabaseManager;
using System.Windows.Forms;
using System.Configuration;
using System.Data;
using Telerik.WinControls;
using Telerik.WinControls.UI;
using AtCor.Scor.BusinessLogic;

/**
 * @namespace AtCor.Scor.Gui.Presentation
 * @brief This namespace implements Presentation related classes.
 * 
 */
namespace AtCor.Scor.Gui.Presentation
{
    /**
  * @class GuiCommon
  * @brief This class contains global variables and methods which are used across different forms
  */
    public static class GuiCommon
   {       
       #region Global variable declaration
       public static bool SetupToReport = false;
       public static bool CaptureToReport = false;
       public static bool CaptureToSetup = false;
       public static bool HasMeasurementDetails = false;
       public static bool IsPatientListEmpty = false; // this flag is used to check if the patient list on the setup screen is empty or not. 
       public static bool CaptureTabClick = true;
       public static RadPageViewPage TabFocused;
       public static bool IsWaitIntervalImposed = false; // this variable checks for 30 sec wait interval imposed by EM4 when coming from capture to setup
       public static bool IsFormChanged = false; // this variable tracks any changes to the application form 
       public static bool IsMenuItemShown = true;
       public static bool CaptureFormLoaded = false; // to check if capture form has loaded.
       // This variable is used during checking field limits on Setup screen.When user has clicked Rad tab capture and if one of the field has value which
       // is out of range.After the out of range message is shown the tabselection_changed event has already been fired due to which the capture functionality starts.
       // As this is wrong we are using the below variable to see if it is true then stop the tab from changing.
       public static bool IsValueOutsideLimits = false;
       public static bool IsMandatoryFieldEmpty = false;  
       public static int ReportLoadCount = 0;
       public static int ExitApp = 0;
       public static string MessageToBeDisplayed = string.Empty;
       #endregion

       #region Main / Parent window Handle
       public static DefaultWindow DefaultWindowForm;
       #endregion      

       public delegate void SetCaptureTabVisibility(bool value);

       public static event SetCaptureTabVisibility OnCaptureClosing;
       
       #region Child Form Handles
       public static RadForm ReportChildForm;
       public static RadForm CaptureChildForm;
       public static RadForm SetupChildForm;
       public static RadForm FrmRptBlnk;

       public static event EventHandler OnBizErrorEventInvocation;       
       #endregion  
        
        #region PWV settings private variables        

       static GuiCommon()
       {
           PwvCurrentStudyDatetime = string.Empty;
           GroupName = string.Empty;
           GroupId = 0;
           PatientInternalNumber = 0;
           SystemIdentifier = 0;

           // Subscribing to the biz.dll events.
           BizEventContainer.Instance.OnBizErrorEvent += Instance_OnBizErrorEvent; 
       }

       /**This event is invoked when BLL recevies DAL alarm events.
       */ 
       public static void Instance_OnBizErrorEvent(object sender, BizErrorEventArgs e)
       {
           // We have to check on which form the user is,when the alarm event is raised.
           // As of now the event can be raised when the user is either on the Capture screen , About box 
           // or the user has clicked on the Find module option under the System menu.
           if (CaptureFormLoaded)
           {
               // Take action if capture screen is loaded and alarm flag is raised.
               // in this case we need to stop the capture on the capture screen.
               string messageToBeDisplayed = e.data;
               object dummySender = new object();
               OnBizErrorEventInvocation.Invoke(dummySender, new EventArgs());               
            }
           else
           {
               // In any other case show a dialog box with the message from the biz.dll to the user.Also log the mesaage in the log file.               
               RadMessageBox.Show(e.data, CrxMessagingManager.Instance.GetMessage(CrxStructCommonResourceMsg.ApplicationMessage), MessageBoxButtons.OK, RadMessageIcon.Exclamation);
               CrxLogger.Instance.Write(e.data);
           }
       }   

       #endregion

        #region General settings properties

       public static int SystemIdentifier { get; set; }

       public static int PatientInternalNumber { get; set; }

       public static int GroupId { get; set; }

       public static string GroupName { get; set; }
       
       public static bool IsLandScape { get; set; }

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
                crxMgrObject.GeneralSettings.ServerName = ConfigurationManager.AppSettings[GuiConstants.AppConfigParams.DefaultInstanceName.ToString()];
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
            IsLandScape = false;

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
                IsLandScape = printDialog.PrinterSettings.DefaultPageSettings.Landscape;
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

        public static void BindGroupNames(RadDropDownList cmbxGroup, CrxDBManager dbMagr)
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
            Font font = new Font(GuiConstants.FontName, 11);
            foreach (Control ctrl in frm.Controls)
            {
                CrxLogger.Instance.Write(ctrl.Text);    
                if (ctrl.Font.Size == font.Size)
                {
                    font = new Font(GuiConstants.FontName, 11);
                    ctrl.Font = font;
                }
                else
                {
                    font = new Font(GuiConstants.FontName, ctrl.Font.Size);
                    ctrl.Font = font;
                }
            }
        }

        /**This method is used to check the status of the flags set in the GUI Field validation class.
         */ 
        public static void CheckIfMandatoryFieldIsEmpty()
        {            
            if (IsValueOutsideLimits || IsMandatoryFieldEmpty)
            {
                DefaultWindowForm.radpgTabCollection.SelectedPage = DefaultWindowForm.guiradgrpbxPwvDistanceMethod;
                DefaultWindowForm.guiradgrpbxPwvDistanceMethod.Enabled = true;
                return;
            }
        }
        #endregion
    }

    /**
 * @class PWVReportData
 * @brief This class is used to define properties which will be used for generating PWV report
     * The property values will be set in report screen once the user clicks print "PWV report" and these values
     * will be passed to Crystal report for printing PWV Report
 */
    public static class PWVReportData
    {
        public static string RptTitle { get; set; }

        public static string RptHeader { get; set; }

        public static string RptPatientData { get; set; }

        public static string RptPatientName { get; set; }

        public static string RptPatientNameValue { get; set; }

        public static string RptPatientId { get; set; }

        public static string RptPatientIdValue { get; set; }

        public static string RptPatientDob { get; set; }

        public static string RptPatientDobValue { get; set; }

        public static string RptPatientAge { get; set; }

        public static string RptPatientAgeValue { get; set; }

        public static string RptPatientGender { get; set; }

        public static string RptPatientGenderValue { get; set; }

        public static string RptStudyData { get; set; }

        public static string RptPatientAssessment { get; set; }

        public static string RptPatientAssessmentValue { get; set; }

        public static string RptPatientBP { get; set; }

        public static string RptPatientBPValue { get; set; }

        public static string RptPatientHeight { get; set; }

        public static string RptPatientHeightValue { get; set; }

        public static string RptPatientOperation { get; set; }

        public static string RptPatientOperationValue { get; set; }

        public static string RptPatientNotes { get; set; }

        public static string RptPatientNotesValue { get; set; }

        public static string RptPatientDistance { get; set; }

        public static string RptPatientDistanceValue { get; set; }

        public static string RptPatientPwv { get; set; }

        public static string RptPatientPwvValue { get; set; }

        public static string RptPatientHeartRate { get; set; }

        public static string RptPatientHeartRateValue { get; set; }

        public static string RptPatientStdDev { get; set; }

        public static string RptPatientHealthyPop { get; set; }

        public static string RptPatientGeneralPop { get; set; }

        public static string RptPatientCarotid { get; set; }

        public static string RptPatientFemoral { get; set; }

        public static string RptReportType { get; set; }

        public static bool RptGeneralPopulation { get; set; }

        public static bool RptHealthyPopulation { get; set; }
    }

    /**
* @class PWVPatientReportData
* @brief This class is used to define properties which will be used for generating PWV Patient report
   * The property values will be set in report screen once the user clicks print "PWV Patient report" and these values
   * will be passed to Crystal report for printing PWV Patient Report
*/
    public static class PWVPatientReportData
    {
        public static string RptPatientBP { get; set; }

        public static string RptPatientBPValue { get; set; }

        public static string RptPatientPwv { get; set; }

        public static string RptPatientPwvValue { get; set; }

        public static string RptPatientNameValue { get; set; }

        public static string RptPatientAge { get; set; }

        public static string RptPatientAgeValue { get; set; }

        public static string RptPatientGender { get; set; }

        public static string RptPatientGenderValue { get; set; }

        public static string RptPatientId { get; set; }

        public static string RptPatientIdValue { get; set; }

        public static string RptPatientBpRefRange { get; set; }

        public static string RptPatientHeight { get; set; }

        public static bool RptGeneralPopulation { get; set; }

        public static bool RptHealthyPopulation { get; set; }
    }

    /**
* @class PWVAnalysisData
* @brief This class is used to define properties which will be used for generating PWV Analysis report
    * The property values will be set in report screen once the user clicks print "PWV Analysis report" and these values
    * will be passed to Crystal report for printing PWV Analysis Report
*/
    public static class PWVAnalysisData
    {
        public static bool BPChartValidation { get; set; }

        public static string BpChartTextValue { get; set; }
    }
}
