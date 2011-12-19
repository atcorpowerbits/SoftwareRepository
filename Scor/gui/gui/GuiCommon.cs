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
using Telerik.WinControls.Primitives;
using System.ComponentModel;

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
       public static CrxStructPWAMeasurementData crxPwaData;
       public static CrxStructCuffPWAMeasurementData crxPwaCuffData;
       public static CrxStructPWAMeasurementData quickStartCrxPwaData;
       public static CrxStructCuffPWAMeasurementData quickStartCrxPwaCuffData;
       public static bool IsValidatedLicenseKey = false; // This flag is used to check whether LicenseKey is valdiated or not.
       public static SystemKeyWindowValues SystemKeyWindowValue = SystemKeyWindowValues.ADD; // values :0.Add 1.Update     Checking whether system key form is called for updating or adding system key.
       public static string CurrentMode = string.Empty;       
       public static string InConclusiveMessageForPwaCapture = string.Empty;
       public static bool SetupToReport = false;
       public static bool CaptureToReport = false;
      // public static bool CaptureToSetup = false;
      // public static bool SetupToTestResult = false;
        // THis flag is used to check whether a selected patient has previous assesments or not.
       public static bool HasMeasurementDetails = false;
       public static bool IsPatientListEmpty = false; // this flag is used to check if the patient list on the setup screen is empty or not. 
       public static bool CaptureTabClick = true;
       public static RadPageViewPage TabFocused;
       public static bool IsWaitIntervalImposed = false; // this variable checks for 30 sec wait interval imposed by EM4 when coming from capture to setup
       public static bool IsFormChanged = false; // this variable tracks any changes to the application form 
       public static bool IsMenuItemShown = true;
       public static bool CaptureFormLoaded = false; // to check if capture form has loaded.
       public static bool IsOnReportForm = false; // This variable is used to check if the user is on the report screen.
       // This variable is used during checking field limits on Setup screen.When user has clicked Rad tab capture and if one of the field has value which
       // is out of range.After the out of range message is shown the tabselection_changed event has already been fired due to which the capture functionality starts.
       // As this is wrong we are using the below variable to see if it is true then stop the tab from changing.
       public static bool IsOnSetupScreen = false;  
       public static bool IsValueOutsideLimits = false;
       public static bool IsValueOutsideIntegerLimits = false;
       public static bool IsMandatoryFieldEmpty = false;  
       public static int ReportLoadCount = 0;
       public static int ExitApp = 0;
       public static int OnLoadPwvDistanceMethod; 
       public static string MessageToBeDisplayed = string.Empty;       
       public static ScorController ScorControllerObject = new ScorController();

       // public static bool AutoPWA = true;
       // public static int AutoPWADelay = 15;
       // public static int RepeatDelay = 5;
       public static bool RepeatButtonClickedStartNibpOnSetup = false;
       public static bool ErrorInCaptureProcess = false;
       public static bool IsBizErrorEventRaised = false;
       public static bool CheckPatientPrivacy = false;
       // public static bool IsSetUpFormDirty = false;
       public static BizPWV bizObject;
       public static BizPWA bizPwaobject;
       public static BizNIBP bizNibpObject = new BizNIBP();
       public static CrxStructGeneralSetting GeneralSettingsStruct = new CrxStructGeneralSetting();
      // public static bool AgeValidation = false;
       public static SelectedChart SelChart = SelectedChart.sp;
       public static bool IsOnResultForm = false;
       public static bool IsReportGenerated = false;
       public static bool IsOnPwaReportForm = false;
       public static bool FromQuickStart = false;
       public static bool FromPwaReport = false;
       #endregion

       #region Main / Parent window Handle
       public static DefaultWindow DefaultWindowForm;
       #endregion      

       public delegate void SetCaptureTabVisibility(bool value);

       public delegate void AccessGuiControls(string message);

      // public static event SetCaptureTabVisibility OnCaptureClosing;
       public static event EventHandler OnEnterButtonClick;

       #region Global Varialbles

       public static string StartupScreen;

       public enum SystemKeyWindowValues
       {
           ADD = 0,
           Update = 1
       }

       public enum BPRange
       {
           BpOptimalRange = 119,
           BpNormalMinRange = 120,
           BpNormalMaxRange = 129,
           BpHighNormalMinRange = 130,
           BpHighNormalMaxRange = 139,
           BpGradeIhtMinRange = 140,
           BpGradeIhtMaxRange = 159,
           BpGradeIiAndIiiHtRange = 160
       }
       public enum NumericValue
       {
           MinusOne = -1,
           Zero = 0,
           One = 1,
           Two = 2,
           Three = 3,
           Four = 4,
           Five = 5,
           Six = 6,
           Seven = 7,
           Eight = 8,
           Nine = 9,
           Ten = 10,
           Twelve = 12,   
           Fifteen = 15,               
           TwentyFive = 25, 
           Hundred = 100,
       }
       public enum SelectedChart
       {
           sp,
           dpMp,
           pp,
           hr,
           aix,
           ap
       }

       public enum BpButtonMode
       { 
         start,
         repeat,
         stopInProgress,
         stopWait,
         stopInWaitProgress
       }
       #endregion

       #region Child Form Handles

       public static Report ReportChildForm;
       public static Capture CaptureChildForm;
       public static Setup SetupChildForm;
       public static Report FrmRptBlnk;
       public static PWAReport PWAReportChildForm;
       public static PWATestResult PWATestResultChildForm;
       public static cPwaQuickStart QuickStartChildForm;
       public static SystemKey SystemKey;


       #endregion  
        
       #region PWV settings private variables        

       static GuiCommon()
       {
           PwvCurrentStudyDatetime = string.Empty;
           PwaCurrentStudyDatetime = string.Empty;
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
           CrxLogger.Instance.Write(e.data);   

           // We have to check on which form the user is,when the alarm event is raised.
           // As of now the event can be raised when the user is either on the Capture screen , About box 
           // or the user has clicked on the Find module option under the System menu.
           if (CaptureFormLoaded)
           {
               if (!IsBizErrorEventRaised)
               {
                   IsBizErrorEventRaised = true;
                   GuiCommon.ScorControllerObject.StopCapture();

                   // Take action if capture screen is loaded and alarm flag is raised.
                   // in this case we need to stop the capture on the capture screen.
                   MessageToBeDisplayed = e.data;
                   object dummySender = new object();
                   
                   ScorControllerObject.ActionPerformedAfterClickingCancel();                   
               }
               else
               {
                   DisplayErrorMessage(e.data);
               }
            }
           else
           {              
               DisplayErrorMessage(e.data);
           }
       }

       public static void DisplayErrorMessage(string message)
       {
           if (DefaultWindowForm.InvokeRequired)
           {
               AccessGuiControls d = new AccessGuiControls(DisplayErrorMessage);

               // this.Invoke(d);
               DefaultWindowForm.Invoke(d,message);
           }
           else
           {
               RadMessageBox.Show(message, CrxMessagingManager.Instance.GetMessage(CrxStructCommonResourceMsg.SystemError), MessageBoxButtons.OK, RadMessageIcon.Exclamation);
               CrxLogger.Instance.Write(message);
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

       public static string PwaCurrentStudyDatetime { get; set; }

       public static string PwaCurrentId { get; set; }  
       #endregion

        #region methods..
       
       /** This method is called on the form closing of the capture screen,to impose wait interval.
        */
       public static void InvokeCaptureClosing(bool value)
       {           
           // From Setup
           // commenting the below as part of review comment.
           // CaptureToSetup = !value;

           DefaultWindowForm.radtabCapture.Enabled = value;
           SetupChildForm.Controls["guipnlMeasurementDetails"].Controls["guiradbtnCapture"].Enabled = value;
           
           // For Corresponding Report forms 
           ScorControllerObject.EnableRepeatAndCaptureTab(value);
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

        public static void SetShape(params Control[] labelControl)
        {
            RoundRectShape shape = new RoundRectShape();
            shape.BottomLeftRounded = true;
            shape.BottomRightRounded = true;
            shape.TopLeftRounded = true;
            shape.TopRightRounded = true;
            shape.Radius = 5;

            foreach (Control control in labelControl)
            {
                RadLabel label = control as RadLabel;
                if (label != null)
                {
                    ((FillPrimitive)label.LabelElement.Children[0]).NumberOfColors = 1;
                    label.LabelElement.Shape = shape;
                }

                RadTextBox textBox = control as RadTextBox;
                if (textBox != null)
                {
                    textBox.TextBoxElement.Border.Shape = shape;
                    textBox.TextBoxElement.Fill.Shape = shape;
                }

                RadButton button = control as RadButton;
                if (button != null)
                {
                    shape.Radius = 2;
                    button.ButtonElement.Shape = shape;
                    button.ButtonElement.BorderElement.Shape = shape;
                }

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

            errorMsg += string.Format(oMsgMgr.GetMessage(CrxStructCommonResourceMsg.ContactAtcorSupport),oMsgMgr.GetMessage(CrxStructCommonResourceMsg.ContactAtcorSupportCommon)); 

            // log the error
            CrxLogger.Instance.Write(errorMsg);

            return errorMsg;
        }

        /** This method is used to Validate age of the patient before validating measurement details.
       */
        public static bool ValidatePatientAgeForReport()
        {

            try
            {    // fetches group name and binds it
                CrxMessagingManager oMsgMgr = CrxMessagingManager.Instance;
                string message = string.Empty;
                BizCaptureGate captureEnum;
                if (GuiCommon.CurrentMode.Equals(CrxStructCommonResourceMsg.Pwa))
                {
                    captureEnum = GuiCommon.bizPwaobject.ValidateAgeLimit(ref message);
                }
                else
                {
                    captureEnum = GuiCommon.bizObject.ValidateAgeLimit(ref message);
                }
                if (captureEnum.Equals(BizCaptureGate.CAPTURE_CANCEL))
                {
                    RadMessageBox.Show(message, oMsgMgr.GetMessage(CrxStructCommonResourceMsg.SystemError), MessageBoxButtons.OK, RadMessageIcon.Exclamation);
                    DefaultWindowForm.radpgTabCollection.SelectedPage = DefaultWindowForm.guiradgrpbxPwvDistanceMethod;
                    DefaultWindowForm.guiradgrpbxPwvDistanceMethod.Enabled = true;
                    return false;
                }
                else
                {
                    return true;
                }

            }
            catch (Exception ex)
            {
                return false;
                throw ex;               
            }
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
            try
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
            catch (Exception ex)
            {
                throw ex;
            }
        }

        public static void BindGroupNames(RadDropDownList cmbxGroup, CrxDBManager dbMagr)
        {
            try
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
            catch (Exception ex)
            {
                throw ex;
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

        /** Begin: AtCor-Drop2-Sprint2, TM, UserStory1,04 July 2011
        /* This method restricts input values to integers and characters only.
         * This method is called on keypress event of the textbox.
        * */
        public static void CheckForNumeric_CharValues(object sender, KeyPressEventArgs e)
        {
            if (!char.IsLetterOrDigit(e.KeyChar))
            {
                e.Handled = true;
            }

            if (e.KeyChar == '\b')
            {
                e.Handled = false;
            }

            if (e.KeyChar == ' ')
            {
                ((RadTextBoxBase)(sender)).Text = string.Empty;
            }

            if (e.KeyChar == (char)13)
            {
                OnEnterButtonClick.Invoke(sender, e);
            }
        }

        /** This method restricts input values to integers and characters only.
         * This method is called on Validating event of the textbox.
         */
        public static void ValidatingNumericCharValues(object sender, CancelEventArgs e)
        {
            CrxMessagingManager oMsgMgr = CrxMessagingManager.Instance;
            char[] array = ((RadTextBoxBase)(sender)).Text.ToCharArray();
            for (int i = 0; i < array.Length; i++)
            {
                if (!char.IsLetterOrDigit(array[i]))
                {
                   // If textbox contain value other than letter and digit then it highlight textbox and shows message to the user.
                    ((RadTextBoxBase)(sender)).Select(0, ((RadTextBoxBase)(sender)).Text.Length);
                    RadMessageBox.Show(oMsgMgr.GetMessage(CrxStructCommonResourceMsg.MsgSpecialCharacter), oMsgMgr.GetMessage(CrxStructCommonResourceMsg.SystemError), MessageBoxButtons.OK, RadMessageIcon.Error);                   
                    e.Cancel = true;
                    return;
                }
            }
        }    
  
        // End : AtCor-<Drop2>-<Sprint2>, TM, <UserStory1>,12 July 2011

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
     * will be passed to Crystal report for printing PWV Report*/
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

        public static string RptBpLabelsText { get; set; }

        public static string RptPatientHeightInternalValue { get; set; }
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

        public static string RptPatientHeightInternalValue { get; set; }
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

    /**
    * @class PWACommonReportData
    * @brief This class is used to define properties which will be used for generating PWA Clinical/Evaluation report
      * The property values will be set in report screen once the user clicks print "PWA Clinical/Evaluation report" and these values
      * will be passed to Crystal report for printing PWA Patient Report
    */
    public static class PWACommonReportData
    {
        public static string RptPrintType { get; set; }

        public static int RptPwaId { get; set; }

        public static string RptReferenceAgeValue { get; set; }

        public static string RptHeader { get; set; }

        public static string RptPatientDataHeader { get; set; }

        public static string RptPatientName { get; set; }

        public static string RptPatientNameValue { get; set; }

        public static string RptPatientId { get; set; }

        public static string RptPatientIdValue { get; set; }

        public static string RptPatientDob { get; set; }

        public static string RptPatientDobValue { get; set; }

        public static string RptPatientAgeGender { get; set; }

        public static string RptPatientAgeGenderValue { get; set; }

        public static string RptPatientAge { get; set; }

        public static string RptPatientAgeValue { get; set; }

        public static string RptPatientGender { get; set; }

        public static string RptPatientGenderValue { get; set; }

        public static string RptStudyDataHeader { get; set; }

        public static string RptPatientAssessment { get; set; }

        public static string RptPatientAssessmentValue { get; set; }

        public static string RptPatientBP { get; set; }

        public static string RptPatientBPValue { get; set; }
      
        public static string RptPatientHeight { get; set; }

        public static string RptPatientHeightValue { get; set; }

        public static string RptDatabaseVersionTitle { get; set; }

        public static string RptDatabaseVersionValue { get; set; }

        public static string RptWaveformPlotTitle { get; set; }

        public static string RptWaveformPlotValue { get; set; }

        public static string RptNumberOfWaveformsTitle { get; set; }

        public static string RptNumberOfWaveformsValue { get; set; }

        public static string RptQualityControlTitle { get; set; }

        public static string RptQualityControlValue { get; set; }

        public static string RptSignatureTitle { get; set; }

        public static string RptPhysicianTitle { get; set; }

        public static string RptSimulationModeTitle { get; set; }

        public static string RptGroupNameTitle { get; set; }

        public static string RptGroupNameValue { get; set; }

        public static string RptNoteTitle { get; set; }

        public static string RptNoteValue { get; set; }

        public static string RptDateAndTimeOfAssessment { get; set; }
    }

    /**
    * @class PWAClinicalReportData
    * @brief This class is used to define properties which will be used for generating PWA Clinical report
      * The property values will be set in report screen once the user clicks print "PWA Clinical report" and these values
      * will be passed to Crystal report for printing PWV Clinical Report
    */
    public static class PWAClinicalReportData
    {
        public static string RptClinicalParametersTitle { get; set; }

        public static string RptCentralPressureWaveformTitle { get; set; }

        public static string RptBrachialTitle { get; set; }

        public static string RptAroticTitle { get; set; }

        public static string RptSPTitle { get; set; }

        public static string RptSPBrachialValue { get; set; }

        public static string RptSPAroticValue { get; set; }

        public static string RptDPTitle { get; set; }

        public static string RptDPBrachialValue { get; set; }

        public static string RptDPAroticValue { get; set; }

        public static string RptMPTitle { get; set; }

        public static string RptMPBrachialValue { get; set; }

        public static string RptMPAroticValue { get; set; }

        public static string RptPPTitle { get; set; }

        public static string RptPPBrachialValue { get; set; }

        public static string RptPPAroticValue { get; set; }

        public static string RptHRTitle { get; set; }

        public static string RptHRBrachialValue { get; set; }

        public static string RptHRAroticValue { get; set; }

        public static string RptInterpretationTitle { get; set; }

        public static string RptInterpretationValue { get; set; }

        public static bool RptSliderPanel { get; set; }
    }

    /**
    * @class PWAEvaluationReportData
    * @brief This class is used to define properties which will be used for generating PWA Evaluation report
       * The property values will be set in report screen once the user clicks print "PWA Evaluation report" and these values
       * will be passed to Crystal report for printing PWA Evaluation Report
    */
    public static class PWAEvaluationReportData
    {
        public static string RptCentralPressureWaveformTitle { get; set; }

        public static string RptHeartRatePeriodTitle { get; set; }

        public static string RptHeartRatePeriodValue { get; set; }

        public static string RptCentralHaemodynamicParametersTitle { get; set; }

        public static string RptAroticT1T2Title { get; set; }

        public static string RptAorticT1T2Value { get; set; }

        public static string RptP1HeightTitle { get; set; }

        public static string RptP1HeightValue { get; set; }

        public static string RptAorticAixTitle { get; set; }

        public static string RptAorticAixValue { get; set; }

        public static string RptAorticAIxHR75Title { get; set; }

        public static string RptAorticAIxHR75Value { get; set; }

        public static string RptAorticAugmentationAP_PPTitle { get; set; }

        public static string RptAorticAugmentationAP_PPValue { get; set; }

        public static string RptEndSystolicPressureTitle { get; set; }

        public static string RptEndSystolicPressureValue { get; set; }

        public static string RptMPSystoleDiastoleTitle { get; set; }

        public static string RptMPSystoleDiastoleValue { get; set; }
    }

    /**
    * @class PWAPatientReportData
    * @brief This class is used to define properties which will be used for generating PWA Clinical/Evaluation report
      * The property values will be set in report screen once the user clicks print "PWA Patient report" and these values
      * will be passed to Crystal report for printing PWA Patient Report
    */
    public static class PWAPatientReportData
    {
        public static string RptPatientAssessment { get; set; }
    }

    /**
   * @class PWAAnalysisReportData
   * @brief This class is used to define properties which will be used for generating PWA Clinical/Evaluation report
     * The property values will be set in report screen once the user clicks print "PWA Analysis report" and these values
     * will be passed to Crystal report for printing PWA Patient Report
   */
    public static class PWAAnalysisReportData
    {
        public static string RptPatientAssessmentValue { get; set; }
    }
}