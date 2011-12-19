/*
     Copyright (C) ATCOR MEDICAL PTY LTD, 2010
 
    Filename     :      Setup
        
    Author       :      Nitesh Chhedda
 
    Description  :      Launches setup screen on Application load.
*/
using System;
using System.Data;
using System.Drawing;
using System.Windows.Forms;
using Telerik.WinControls;
using AtCor.Scor.CrossCutting.Configuration;
using AtCor.Scor.CrossCutting.DatabaseManager;
using AtCor.Scor.CrossCutting.Messaging;
using AtCor.Scor.CrossCutting.Logging;
using Telerik.WinControls.UI;
using AtCor.Scor.BusinessLogic;
using System.Configuration;
using System.Globalization;
using AtCor.Scor.DataAccess;
using System.Collections;
using AtCor.Scor.CrossCutting;

/**
 * @namespace AtCor.Scor.Gui.Presentation
 * @brief This namespace implements Presentation related classes.  
 */
namespace AtCor.Scor.Gui.Presentation
{
    /**
    * @class Setup
    * @brief This class will handle displaying of the setup screen controls.It will also check for exception handling and logging of events.
    */
    public partial class Setup : RadForm
    {
        #region Global declarations
        public static int AutoProgressbarDelay = 0, WaitButtonDelay = 0;
        const int FemoralToCuffDefaultMmValue = 200; // default femoral to cuff value in mm
        const int FemoralToCuffDefaultCmValue = FemoralToCuffDefaultMmValue / 10; // convert default femoral to cuff value to cm
        const int PatientListHideValue = 0; // minimum splitter distance to hide patient list
        const int PatientListShowValue = 356; // maximum splitter distance to show patient list
        float averageAorticXAxisInterval = ((float)(1000.0 / 128.0));
                
        readonly CrxDBManager dbMagr = CrxDBManager.Instance;
        readonly string serverNameString = string.Empty;
        readonly CrxConfigManager crxMgrObject = CrxConfigManager.Instance;         
        readonly CrxMessagingManager oMsgMgr = CrxMessagingManager.Instance;
        int heightInCentiConversion = 0, heightInFeetConversion = 0, heightInInchConversion = 0;
        int bobj;
        private int maxCuffPressure = 300;
        public bool isValueChanged = false;
        private bool isHeightOutsideIntegerLimits = false;
        private int waitTimer = 0;
        private int counter = 0;
        private int startIndex = -1;
        private ArrayList nibpSp = new ArrayList();
        private ArrayList nibpDp = new ArrayList();
        private ArrayList nibpMp = new ArrayList();
        private ArrayList nibpPp = new ArrayList();
        private GuiCommon.BpButtonMode buttonMode = GuiCommon.BpButtonMode.start;
        GuiFieldValidation objValidation;    

        // since we are combining date string from three different combo boxes
        // using format provider to give culture specific dates
        IFormatProvider culture = new CultureInfo(CultureInfo.CurrentCulture.LCID);

        // denotes the current mode of setup screen
        public enum CurrentMode
        {
            None,
            InsertMode,
            EditMode,
            SearchMode
        }

        // defines days in month 
        enum DaysInMonth
        { 
            LeapYear = 29,
            Days30 = 30,
            Days31 = 31
        }

        CurrentMode mode = CurrentMode.None; // 1 denotes insert & 2 denotes update for internal use
        CurrentMode prevMode; // save previous mode information
        bool isCellInitializeWidth; // check for gridview cell width at the time of initialization
        bool isSearchReset; // to check if fields are resetting in search mode
        bool isSearchOn; // this variable checks if search records are displayed in grid
        
        string originalgroupname = string.Empty;
        string orgPatientIdExt = string.Empty;
        private DefaultWindow objDefaultWindow;
        private BPAssessments objBpAssessment = new BPAssessments();
        #endregion

        /** Parameterized Constructor, used to display messages in default window      
         */
        public Setup(DefaultWindow defWindow)
        { 
            try
            {               
                InitializeComponent();                

                // subscribe for form changes
                SubscribeSetupFormChanges();
                ReadSettings();

                // Get delay values from ScorSystemParameters.xml file and set auto progress bar and wait button delay
                SetDelayValues();
                SetTextForSetupTab();
                SetSetupTagForValidations();

                crxMgrObject.GetBpUserSettings();
               
                // set the default window
                objDefaultWindow = defWindow;
                                
                // subscribe to Settings change event from settings window
                frmSettingsWindow.OnSettingsChangedEvent += SettingsChangedEventHandler;
                Report.OnPwvMeasurementChangedEvent += SettingsChangedEventHandler;
                PWAReport.OnPwaMeasurementChangedEvent += SettingsChangedEventHandlerPwa;
                                
                DefaultWindow.OnRestoreCompleteSuccess += Setup_Load;
                
                // initialize servername string
                serverNameString = GuiCommon.ServerNameString();
                SetupScreenTimer.Interval = DalModule.Instance.NibpCuffDataInterval;
                GuiCommon.SetShape(guilblLastNameDisplay, guilblFirstnameDisplay, guilblPatientIdDisplay, guilblFirstnameDisplay, guilblGender, guilblDay, guilblMonth, guilblYear, guiradlblPWASPDisplay, guiradlblPWAPPDisplay, guiradlblPWAMPDisplay, guiradlblPWADPDisplay, guiradlblQuickMapDisplay);
                GuiCommon.SetShape(guiradtxtsetupheight, guiradtxtImperialHeight, guiradtxtOperator, guiradtxtMedication, guiradtxtSP, guiradtxtDP, guiradtxtCarotid, guiradtxtCuff, guiradtxtFemoralToCuff, guiradtxtPatientID, guiradtxtFirstName, guiradtxtLastName, guiradtxtPWAHeight, guiradtxtPWAImperialHeight,  guiradtxtPwaOperator, guiradtxtMedicationNotes);
                GuiCommon.SetShape(guicmbDay, guicmbxMonth, guicmbxYear, guicmbxYear, guicmbxGender);
                GuiCommon.SetShape(guiradbtnCancel, guiradbtnSave);
            }
            catch (Exception ex)
            {
                GUIExceptionHandler.HandleException(ex, this);
            }          
        }

        public void LoadSetup()
        {
            try
            {
                GuiCommon.IsOnSetupScreen = true;
                bobj = GuiConstants.SystemId;

                GuiCommon.SystemIdentifier = bobj;
                objValidation = new GuiFieldValidation(guipnlMeasurementDetails);
                objValidation = new GuiFieldValidation(guipnlPWAMeasurementDetails);

                // This code is written so that below event is subscribed only for Setup mode and not for QuickStart
                if (GuiCommon.StartupScreen.ToUpper() == oMsgMgr.GetMessage(CrxStructCommonResourceMsg.Standard).ToUpper())
                {
                    BizEventContainer.Instance.OnBizNIBPDataEvent += new BizNIBPDataEventHandler(Instance_OnBizNIBPDataEvent);
                }

                // Set CuffPressure ProgressBar Values
                guiradCuffPressureProgBar.Minimum = Convert.ToInt32(GuiCommon.NumericValue.Zero);
                guiradCuffPressureProgBar.Maximum = maxCuffPressure;
                guiradCuffPressureProgBar.Value1 = Convert.ToInt32(GuiCommon.NumericValue.Zero);

                SetPatientPrivacy();
                LoadGroupNames();
                InitializePatientList();
               
                if (GuiCommon.FromPwaReport)
                {
                    // Calling this method to disable the RHS panel once the user comes from Report to Patient.
                    EnableDisableMeasurmenetPanelForPwvAndPwa();
                    GuiCommon.FromPwaReport = false;
                }
                else
                {
                    FillGender();
                    FillMonthAndYear();
                    LoadPatientList();
                }

                guiradlblPWASPDisplay.Font = guiradlblPWASPDisplay.Font = guiradlblPWAPPDisplay.Font = guiradlblPWAMPDisplay.Font = guiradlblPWADPDisplay.Font = guiradlblQuickMapDisplay.Font = new Font("Arial", 11);

                FillBpMeasurementData();
            }
            catch (Exception ex)
            {
                throw ex;
            }
        }        

        /** This method is called on the tick of wait interval  timer used on the Default window.
         * On the tick of the timer we enable the Capture button on the Setup screen along with the Capture tab.
         */
        public void EnableCaptureButton(bool value)
        {
            try
            {
                objDefaultWindow.radtabCapture.Enabled = value;
                guiradbtnCapture.Enabled = value;
                // commenting the below as part of review comment.
                // GuiCommon.CaptureToSetup = !value;
            }
            catch (Exception ex)
            {
                GUIExceptionHandler.HandleException(ex, this);
            }
        }

        /** This event is invoked from DefautWindow when, there are no records in the db and the user is trying to restore db.
         *  During this process if he does not have the permissions to restore this method will be executed.
         */
        public void CheckIfInInsertMode()
        {
            if (guiradgrdPatientList.Rows.Count == Convert.ToInt32(GuiCommon.NumericValue.Zero))
            {
                BrowseMode(false); 
            }
            else
            {
                return;
            }
        }

        public void SaveSetupData()
        {
            isSearchOn = false;
            guiradtxtsetupheight.Focus();

            // Check for duplicate 5 fields.
            // Check for duplicate patient id.
            // Save the demographic details into the database.
            try
            {
                if (ValidateDemographicDetails())
                {
                    if (mode == CurrentMode.InsertMode)
                    {
                        CheckForPatientIdToAddPatient();
                    }
                    else
                    {
                        CheckForPatientIdToUpdatePatient();
                    }

                    isValueChanged = false;
                }                  
            }
            catch (Exception ex)
            {
               // GUIExceptionHandler.HandleException(ex, this);
                throw (ex);
            }
        }

        /** This method is used to set the height weight units for PWV mode in the GUI depending on the settings selected by the user.
         */
        public void SetPwvHeightWeightUnits()
        {
            try
            {
                // read height and weight units and accordingly show units for height and weight.Convert values accordingly.
                // read the properties for the setting the units for measurement data.
                switch (crxMgrObject.GeneralSettings.HeightandWeightUnit)
                {
                    case (int)CrxGenPwvValue.CrxGenHeightWeightMetric:

                        // metric units i.e cm
                        guiradlblHeightUnits.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.Cm);
                        guiradtxtImperialHeight.Visible = false;
                        guiradlblImperialHeight.Visible = false;
                        break;
                    case (int)CrxGenPwvValue.CrxGenHeightWeightImperial:

                        // imperial units i.e ft and inches and lbs.
                        guiradlblHeightUnits.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.Feet);

                        // show Inches.
                        guiradtxtImperialHeight.Visible = true;
                        guiradlblImperialHeight.Visible = true;
                        break;
                    default:
                        break;
                }
            }
            catch (Exception ex)
            {
                throw (ex);
            }
        }

        /** This method is used to set the height weight units for PWA mode in the GUI depending on the settings selected by the user.
         */
        public void SetPwaHeightWeightUnits()
        {
            try
            {
                // read height and weight units and accordingly show units for height and weight.Convert values accordingly.
                // read the properties for the setting the units for measurement data.
                switch (crxMgrObject.GeneralSettings.HeightandWeightUnit)
                {
                    case (int)CrxGenPwvValue.CrxGenHeightWeightMetric:
                        // metric units i.e cm and kg.                    
                        guiradlblPWAHeightUnit.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.Cm);
                        guiradtxtPWAImperialHeight.Visible = false;
                        guiradlblImperialHeightUnit.Visible = false;
                        break;
                    case (int)CrxGenPwvValue.CrxGenHeightWeightImperial:

                        // imperial units i.e ft and inches and lbs.
                        guiradlblPWAHeightUnit.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.Feet);

                        // show Inches.
                        guiradtxtPWAImperialHeight.Visible = true;
                        guiradlblImperialHeightUnit.Visible = true;
                        break;
                    default:
                        break;
                }
            }
            catch (Exception ex)
            {
                throw (ex);
            }
        }

        /** This method is called when user tries to navigate to top menu before exiting the current mode other than browse mode
         * It will prompt user to save the changes when in Insert & Edit mode, and will ask user to exit search mode if on search mode
         * and then will navigate to menu options selected by user
         */
        public void SaveChangesForModes()
        {
            try
            {
                GuiCommon.IsMenuItemShown = true;
                switch (mode)
                {
                    case CurrentMode.None:
                        // user in browse mode nothing to be done
                        break;
                    case CurrentMode.SearchMode:
                        // prompt user to exit search
                        DialogResult ds = RadMessageBox.Show(this, oMsgMgr.GetMessage(CrxStructCommonResourceMsg.GuiSetupSearchExitMsg), oMsgMgr.GetMessage(CrxStructCommonResourceMsg.SystemError), MessageBoxButtons.YesNoCancel, RadMessageIcon.Question);
                        switch (ds)
                        {
                            case DialogResult.Yes:
                            default:
                                // exit search mode and open menu items clicked by user                           
                                isSearchOn = false;
                                mode = CurrentMode.None;
                                LoadPatientList();

                                if (!(GuiCommon.IsReportGenerated || GuiCommon.FromQuickStart) && objDefaultWindow.guiradgrpbxPwvDistanceMethod.Text.Equals(oMsgMgr.GetMessage(CrxStructCommonResourceMsg.TabPatient)))
                                {
                                    objDefaultWindow.radtabReport.Enabled = false;
                                }
                                else
                                {
                                    // enable / disable  report tab based on measurement details
                                    objDefaultWindow.radtabReport.Enabled = GuiCommon.HasMeasurementDetails;
                                }

                                // below line of code enables capture tab based on 30 sec wait interval imposed by EM4
                                // if IsWaitIntervalImposed is true then disable capture button & vice versa
                                if (GuiCommon.CurrentMode.Equals(CrxStructCommonResourceMsg.Pwv))
                                {
                                    objDefaultWindow.radtabCapture.Enabled = !GuiCommon.IsWaitIntervalImposed;
                                }

                                break;
                            case DialogResult.No:
                                // do not exit search mode
                                GuiCommon.IsMenuItemShown = false;
                                break;
                            case DialogResult.Cancel:
                                // do not exit search mode
                                GuiCommon.IsMenuItemShown = false;
                                break;
                        }

                        break;
                    default:

                        // this will handle saving the values in edit & insert mode before navigating to menu items
                        if (isValueChanged)
                        {
                            DialogResult dsSave = RadMessageBox.Show(this, oMsgMgr.GetMessage(CrxStructCommonResourceMsg.MsgSaveChange), oMsgMgr.GetMessage(CrxStructCommonResourceMsg.SystemError), MessageBoxButtons.YesNoCancel, RadMessageIcon.Question);
                            switch (dsSave)
                            {
                                case DialogResult.Yes:
                                    // exit search mode and open menu items clicked by user
                                    Invoke(new EventHandler(guiradbtnSave_Click));

                                    break;
                                case DialogResult.Cancel:
                                    // do not exit search mode
                                    GuiCommon.IsMenuItemShown = false;
                                    objDefaultWindow.guicmbxCurrentMode.Enabled = false;
                                    break;
                                default:
                                    // Check if there are any records in the patient list.
                                    // There is a exception when the user is running the application on a fresh db,
                                    // by default the setup screen goes into Insert mode,at this moment if user clicks on the menu bar he will be prompted to 
                                    // save changes.This is not logical since he has not made any changes.
                                    // Hence following condition is checked.
                                    if (guiradgrdPatientList.RowCount.Equals(Convert.ToInt32(GuiCommon.NumericValue.Zero)))
                                    {
                                        GuiCommon.IsPatientListEmpty = true;
                                        return;
                                    }

                                    mode = CurrentMode.None;
                                    DisplayLastRecord(int.Parse(radlblpatientinternalnumber.Text.Trim()), int.Parse(radlblgroupid.Text));

                                    guiradgrdPatientList.Enabled = true;
                                    if (!(objDefaultWindow.guiradgrpbxPwvDistanceMethod.Text.Equals(oMsgMgr.GetMessage(CrxStructCommonResourceMsg.TabPatient))))
                                    {
                                        objDefaultWindow.guicmbxCurrentMode.Enabled = true;
                                    }

                                    // disable capture & enable / disable  report tab based on measurement details
                                    objDefaultWindow.radtabReport.Enabled = GuiCommon.HasMeasurementDetails;

                                    // below line of code enables capture tab based on 30 sec wait interval imposed by EM4
                                    // if IsWaitIntervalImposed is true then disable capture button & vice versa
                                    if (GuiCommon.CurrentMode.Equals(CrxStructCommonResourceMsg.Pwv))
                                    {
                                        objDefaultWindow.radtabCapture.Enabled = !GuiCommon.IsWaitIntervalImposed;
                                    }

                                    isValueChanged = false;
                                    break;
                            }
                        }

                        break;
                }
            }
            catch (Exception ex)
            {
                throw (ex);
            }
        }

        /** This method can be moved to Stratergy,but will not add much value.Hence keeping it here.
         */
        public void EnableDisableMeasurmenetPanelForPwvAndPwa()
        {
            if (GuiCommon.CurrentMode.Equals(CrxStructCommonResourceMsg.Pwv))
            {
                guipnlMeasurementDetails.Visible = true;
            }
            else
            {
                if (GuiCommon.IsReportGenerated || GuiCommon.FromQuickStart)
                {
                    guipnlPWAMeasurementDetails.Visible = false;
                    guipnlMeasurementDetails.Visible = false;
                }
                else
                {
                    guipnlPWAMeasurementDetails.Visible = true;
                    if ((GuiCommon.StartupScreen.ToUpper() == CrxStructCommonResourceMsg.QuickStart))
                    {
                        PlotAvgAorticPulseChart();
                    }
                    // setting the enabled property of the panel true to refresh the panel when the user clicks
                    // on save button or cancel button when the user is about to save the measurement detail in quickstart mode.
                    guipnlPWAMeasurementDetails.Enabled = true;
                }

                if (!(GuiCommon.StartupScreen.ToUpper() == CrxStructCommonResourceMsg.QuickStart))
                {
                    objDefaultWindow.guicmbxCurrentMode.Enabled = true;
                }
                else
                {
                    objDefaultWindow.guicmbxCurrentMode.Enabled = false;
                }
            }
        }

        /** This method is used to set the blood pressure in the GUI depending on the settings selected by the user.
         */
        public void SetPwvBloodPressure()
        {   
            guiradlblSP.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.LabelSp);
            guiradlblDP.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.LabelDp);
        }

        /** This method is used to set the PWV distance methods/units in the GUI depending on the settings selected by the user.
         */
        public void SetPwvDistanceMethodAndUnits()
        {
            try
            {
                // read pwv distance units and pwv distance method and accordingly dispaly the labels and textbox.Do the calculation of for PWV distance.Also read the cuff location for it to be editable or no. 
                switch (crxMgrObject.PwvSettings.PWVDistanceMethod)
                {
                    case (int)CrxGenPwvValue.CrxPwvDistMethodSubtract:
                        guiradlblPwvDistanceMethod.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.SubtractingMethod);
                        Image imageSubtracting = Image.FromFile(ConfigurationManager.AppSettings[GuiConstants.AppConfigParams.SetupScreenSubtracting.ToString()]);
                        picbxPwvDisMthdImage.Image = imageSubtracting;
                        picbxPwvDisMthdImage.ImageLocation = ConfigurationManager.AppSettings[GuiConstants.AppConfigParams.SetupScreenSubtracting.ToString()];

                        // show carotid lbl,text and units.
                        guiradlblCarotid.Visible = true;
                        guiradtxtCarotid.Visible = true;
                        guiradlblCarotidTonometerUnits.Visible = true;
                        break;
                    case (int)CrxGenPwvValue.CrxPwvDistMethodDirect:
                        // hide carotid lbl,text and units.
                        guiradlblCarotid.Visible = false;
                        guiradtxtCarotid.Visible = false;
                        guiradlblCarotidTonometerUnits.Visible = false;

                        // direct method.
                        guiradlblPwvDistanceMethod.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.DirectMethod);
                        Image imageDirect = Image.FromFile(ConfigurationManager.AppSettings[GuiConstants.AppConfigParams.SetupScreenDirect.ToString()]);
                        picbxPwvDisMthdImage.Image = imageDirect;
                        picbxPwvDisMthdImage.ImageLocation = ConfigurationManager.AppSettings[GuiConstants.AppConfigParams.SetupScreenDirect.ToString()];
                        break;

                    default:
                        break;
                }

                int value;
                switch (crxMgrObject.PwvSettings.PWVDistanceUnits)
                {
                    case (int)CrxGenPwvValue.CrxPwvDistDistUnitsMM:
                        if (string.IsNullOrEmpty(crxMgrObject.PwvSettings.FemoralToCuff))
                        {
                            value = Convert.ToInt32(GuiCommon.NumericValue.MinusOne);
                        }
                        else
                        {
                            value = int.Parse(crxMgrObject.PwvSettings.FemoralToCuff);
                        }

                        guiradlblCarotidTonometerUnits.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.Mm);
                        guiradlblCuffunits.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.Mm);
                        guiradlblFemoralToCuffUnits.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.Mm);

                        // Settings Validation for PWV Distance Method textboxes
                        guiradtxtCuff.MaxLength = Convert.ToInt32(GuiCommon.NumericValue.Four);
                        guiradtxtCarotid.MaxLength = Convert.ToInt32(GuiCommon.NumericValue.Three);
                        guiradtxtFemoralToCuff.MaxLength = Convert.ToInt32(GuiCommon.NumericValue.Three);

                        if (!GuiCommon.IsOnReportForm)
                        {
                            if (value.Equals(-1))
                            {
                                guiradtxtFemoralToCuff.Text = string.Empty;
                            }
                            else
                            {
                                guiradtxtFemoralToCuff.Text = value.ToString();
                            }
                        }

                        guiradlblPwvDistanceUnits.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.Mm);
                        break;

                    case (int)CrxGenPwvValue.CrxPwvDistDistUnitsCM:
                        if (string.IsNullOrEmpty(crxMgrObject.PwvSettings.FemoralToCuff))
                        {
                            value = Convert.ToInt32(GuiCommon.NumericValue.MinusOne);
                        }
                        else
                        {
                            value = int.Parse(crxMgrObject.PwvSettings.FemoralToCuff);
                        }

                        guiradlblCarotidTonometerUnits.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.Cm);
                        guiradlblCuffunits.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.Cm);
                        guiradlblFemoralToCuffUnits.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.Cm);

                        // Settings Validation for PWV Distance Method textboxes

                        guiradtxtCuff.MaxLength = Convert.ToInt32(GuiCommon.NumericValue.Three);
                        guiradtxtCarotid.MaxLength = Convert.ToInt32(GuiCommon.NumericValue.Two);
                        guiradtxtFemoralToCuff.MaxLength = Convert.ToInt32(GuiCommon.NumericValue.Two);
                        if (!GuiCommon.IsOnReportForm)
                        {
                            if (value.Equals(Convert.ToInt32(GuiCommon.NumericValue.MinusOne)))
                            {
                                guiradtxtFemoralToCuff.Text = string.Empty;
                            }
                            else
                            {
                                guiradtxtFemoralToCuff.Text = value.ToString();
                            }
                        }

                        guiradlblPwvDistanceUnits.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.Cm);
                        break;

                    default:
                        break;
                }
            }
            catch (Exception ex)
            {
                throw (ex);
            }
        }

        /** Begin: AtCor-Drop2-Sprint3, TM, SWREQ2011,21 july 2011
        /** This method fills PWA measurement details from DB in Bizsession
        */
        public void FillPwaDetailsSession()
        {
            try
            {
                DataSet dsPwa = dbMagr.GetCuffPWAMeasurementDetails(int.Parse(radlblpatientinternalnumber.Text.Trim()), int.Parse(radlblgroupid.Text), bobj);

                if (dsPwa.Tables[0].Rows.Count > Convert.ToInt32(GuiCommon.NumericValue.Zero))
                {
                    GuiCommon.HasMeasurementDetails = true;

                    GuiCommon.PwvCurrentStudyDatetime = dsPwa.Tables[0].Rows[0][(int)CrxDBGetCuffPWAMeasurementDetails.StudyDateTime].ToString();

                    FillPwaSessionData(dsPwa);
                    FillPwaHeightData();
                    guiradtxtMedicationNotes.Text = dsPwa.Tables[0].Rows[0][(int)CrxDBGetCuffPWAMeasurementDetails.Notes].ToString();
                }
                else
                {
                    // disable report and capture tab if measurement data not available for patient
                    objDefaultWindow.radtabReport.Enabled = false;

                    GuiCommon.HasMeasurementDetails = false;
                    GuiCommon.PwvCurrentStudyDatetime = string.Empty;

                    // resets PWA fields on setup screen RHS
                    ResetPatientMeasurementFields();
                    dsPwa = dbMagr.GetPWVMeasurementDetails(int.Parse(radlblpatientinternalnumber.Text.Trim()), int.Parse(radlblgroupid.Text), bobj);
                    if (dsPwa.Tables[0].Rows.Count > Convert.ToInt32(GuiCommon.NumericValue.Zero))
                    {
                        GuiCommon.bizPwaobject.heightAndWeight.heightInCentimetres = string.IsNullOrEmpty(dsPwa.Tables[0].Rows[0][(int)CrxDBPWVMeasurementTableList.HeightInCentimetres].ToString()) ? GuiCommon.bizPwaobject.heightAndWeight.heightInCentimetres : ushort.Parse(dsPwa.Tables[0].Rows[0][(int)CrxDBPWVMeasurementTableList.HeightInCentimetres].ToString());
                        GuiCommon.bizPwaobject.heightAndWeight.heightInInches = string.IsNullOrEmpty(dsPwa.Tables[0].Rows[0][(int)CrxDBPWVMeasurementTableList.HeightInInches].ToString()) ? GuiCommon.bizPwaobject.heightAndWeight.heightInInches : ushort.Parse(dsPwa.Tables[0].Rows[0][(int)CrxDBPWVMeasurementTableList.HeightInInches].ToString());
                        FillPwaHeightData();
                    }
                }
            }
            catch (Exception ex)
            {
                throw (ex);
            }
        }

        /** This method fills PWA measurement Height details on setup screen 
       */
        public void FillPwaHeightData()
        {
            try
            {
                // filling RHS pwa measurement data on setup screen 
                switch (crxMgrObject.GeneralSettings.HeightandWeightUnit)
                {
                    // converting to int as crxMgrObject.GeneralSettings.HeightandWeightUnit returns int
                    case (int)CrxGenPwvValue.CrxGenHeightWeightMetric:
                        PerformPwaHeightMetricConversion(ref heightInCentiConversion);
                        guiradtxtPWAHeight.Text = heightInCentiConversion.ToString().Equals("0") ? string.Empty : heightInCentiConversion.ToString();
                        break;

                    case (int)CrxGenPwvValue.CrxGenHeightWeightImperial:
                        if (GuiCommon.bizPwaobject.heightAndWeight.heightInInches != GuiConstants.DefaultValue)
                        {
                            PerformPwaHeightImperialConversion(ref heightInFeetConversion, ref heightInInchConversion);
                            guiradtxtPWAHeight.Text = heightInFeetConversion.ToString().Equals("0") ? string.Empty : heightInFeetConversion.ToString();
                            guiradtxtPWAImperialHeight.Text = heightInInchConversion.ToString().Equals("0") ? string.Empty : heightInInchConversion.ToString();
                        }
                        else
                        {
                            guiradtxtPWAHeight.Text = string.Empty;
                            guiradtxtPWAImperialHeight.Text = string.Empty;
                        }

                        break;

                    default:
                        break;
                }
            }
            catch (Exception ex)
            {
                throw (ex);
            }
        }

        /** This method fills PWV measurement Height details on setup screen 
        */
        public void FillPwvHeightData()
        {
            try
            {
                // filling RHS pwv measurement data on setup screen                
                switch (crxMgrObject.GeneralSettings.HeightandWeightUnit)
                {
                    // converting to int as crxMgrObject.GeneralSettings.HeightandWeightUnit returns int
                    case (int)CrxGenPwvValue.CrxGenHeightWeightMetric:
                        PerformHeightMetricConversion(ref heightInCentiConversion);
                        guiradtxtsetupheight.Text = heightInCentiConversion.ToString();
                        break;

                    case (int)CrxGenPwvValue.CrxGenHeightWeightImperial:
                        if (GuiCommon.bizObject.heightAndWeight.heightInInches != GuiConstants.DefaultValue)
                        {
                            PerformHeightImperialConversion(ref heightInFeetConversion, ref heightInInchConversion);
                            guiradtxtsetupheight.Text = heightInFeetConversion.ToString();
                            guiradtxtImperialHeight.Text = heightInInchConversion.ToString();
                        }
                        else
                        {
                            guiradtxtsetupheight.Text = string.Empty;
                            guiradtxtImperialHeight.Text = string.Empty;
                        }

                        break;
                    default:
                        break;
                }
            }
            catch (Exception ex)
            {
                throw (ex);
            }
        }

        /** This method fills PWV measurement details from DB in Bizsession
        */
        public void FillPwvDetailsSession()
        {
            try
            {
                DataSet dsPwv = dbMagr.GetPWVMeasurementDetails(int.Parse(radlblpatientinternalnumber.Text.Trim()), int.Parse(radlblgroupid.Text), bobj);
                if (dsPwv.Tables[0].Rows.Count > Convert.ToInt32(GuiCommon.NumericValue.Zero))
                {
                    GuiCommon.HasMeasurementDetails = true;

                    GuiCommon.PwvCurrentStudyDatetime = dsPwv.Tables[0].Rows[0][(int)CrxDBPWVMeasurementTableList.StudyDateTime].ToString();

                    FillSessionData(dsPwv);

                    FillPwvHeightData();

                    guiradtxtOperator.Text = dsPwv.Tables[0].Rows[0][(int)CrxDBPWVMeasurementTableList.Operator].ToString();
                    guiradtxtMedication.Text = dsPwv.Tables[0].Rows[0][(int)CrxDBPWVMeasurementTableList.Notes].ToString();

                    guiradtxtSP.Text = dsPwv.Tables[0].Rows[0][(int)CrxDBPWVMeasurementTableList.SP].ToString().Equals(GuiConstants.DefaultValue.ToString()) ? string.Empty : dsPwv.Tables[0].Rows[0][(int)CrxDBPWVMeasurementTableList.SP].ToString();
                    guiradtxtDP.Text = dsPwv.Tables[0].Rows[0][(int)CrxDBPWVMeasurementTableList.DP].ToString().Equals(GuiConstants.DefaultValue.ToString()) ? string.Empty : dsPwv.Tables[0].Rows[0][(int)CrxDBPWVMeasurementTableList.DP].ToString();
                    guiradtxtCuff.Text = dsPwv.Tables[0].Rows[0][(int)CrxDBPWVMeasurementTableList.Carotid].ToString().Equals(GuiConstants.DefaultValue.ToString()) ? dsPwv.Tables[0].Rows[0][(int)CrxDBPWVMeasurementTableList.Direct].ToString() : dsPwv.Tables[0].Rows[0][(int)CrxDBPWVMeasurementTableList.Cuff].ToString().Equals(GuiConstants.DefaultValue.ToString()) ? string.Empty : dsPwv.Tables[0].Rows[0][(int)CrxDBPWVMeasurementTableList.Cuff].ToString();
                    guiradtxtCarotid.Text = dsPwv.Tables[0].Rows[0][(int)CrxDBPWVMeasurementTableList.Carotid].ToString().Equals(GuiConstants.DefaultValue.ToString()) ? string.Empty : dsPwv.Tables[0].Rows[0][(int)CrxDBPWVMeasurementTableList.Carotid].ToString();
                    guiradtxtFemoralToCuff.Text = dsPwv.Tables[0].Rows[0][(int)CrxDBPWVMeasurementTableList.FemoraltoCuff].ToString().Equals(GuiConstants.DefaultValue.ToString()) ? string.Empty : dsPwv.Tables[0].Rows[0][(int)CrxDBPWVMeasurementTableList.FemoraltoCuff].ToString();
                    guiradlblResult.Text = dsPwv.Tables[0].Rows[0][(int)CrxDBPWVMeasurementTableList.PWVDistance].ToString();

                    ConvertMmToCm();
                }
                else
                {
                    // disable report and capture tab if measurement data not available for patient
                    objDefaultWindow.radtabReport.Enabled = false;

                    // below line of code enables capture tab based on 30 sec wait interval imposed by EM4
                    // if IsWaitIntervalImposed is true then disable capture button & vice versa
                    objDefaultWindow.radtabCapture.Enabled = !GuiCommon.IsWaitIntervalImposed;

                    GuiCommon.HasMeasurementDetails = false;
                    GuiCommon.PwvCurrentStudyDatetime = string.Empty;

                    // resets PWV fields on setup screen RHS
                    ResetPatientMeasurementFields();
                    int value;
                    if (string.IsNullOrEmpty(crxMgrObject.PwvSettings.FemoralToCuff))
                    {
                        value = Convert.ToInt32(GuiCommon.NumericValue.MinusOne);
                    }
                    else
                    {
                        value = int.Parse(crxMgrObject.PwvSettings.FemoralToCuff);
                    }

                    if (value.Equals(Convert.ToInt32(GuiCommon.NumericValue.MinusOne)))
                    {
                        guiradtxtFemoralToCuff.Text = string.Empty;
                    }
                    else
                    {
                        guiradtxtFemoralToCuff.Text = value.ToString();
                    }

                    dsPwv = dbMagr.GetCuffPWAMeasurementDetails(int.Parse(radlblpatientinternalnumber.Text.Trim()), int.Parse(radlblgroupid.Text), bobj);
                    if (dsPwv.Tables[0].Rows.Count > Convert.ToInt32(GuiCommon.NumericValue.Zero))
                    {
                        GuiCommon.bizObject.heightAndWeight.heightInCentimetres = string.IsNullOrEmpty(dsPwv.Tables[0].Rows[0][(int)CrxDBGetCuffPWAMeasurementDetails.HeightInCentimetres].ToString()) ? GuiCommon.bizObject.heightAndWeight.heightInCentimetres : ushort.Parse(dsPwv.Tables[0].Rows[0][(int)CrxDBGetCuffPWAMeasurementDetails.HeightInCentimetres].ToString());
                        GuiCommon.bizObject.heightAndWeight.heightInInches = string.IsNullOrEmpty(dsPwv.Tables[0].Rows[0][(int)CrxDBGetCuffPWAMeasurementDetails.HeightInInches].ToString()) ? GuiCommon.bizObject.heightAndWeight.heightInInches : ushort.Parse(dsPwv.Tables[0].Rows[0][(int)CrxDBGetCuffPWAMeasurementDetails.HeightInInches].ToString());
                        FillPwvHeightData();
                    }

                }
            }
            catch (Exception ex)
            {
                throw (ex);
            }
        }

        /** This event is used to set focus on the Pateint list when ever the user comes back to setup screen from Report.
         */
        public void SetFocusOnPatientList()
        {
            GuiCommon.IsOnSetupScreen = true;
            guiradgrdPatientList.Focus();
            if (guiradbtnGetBp.Text == oMsgMgr.GetMessage(CrxStructCommonResourceMsg.BtnStart) && (!ProgressBarTimeStatusTimer.Enabled))
            {               
                objDefaultWindow.guiradmnuDatabase.Enabled = true;
                objDefaultWindow.guiradmnuSystem.Enabled = true;
            }

            if (guiradbtnAutoPWACancel.Text == oMsgMgr.GetMessage(CrxStructCommonResourceMsg.BtnCapture) && (guiradbtnAutoPWACancel.Visible == true))
            {
                objDefaultWindow.radtabCapture.Enabled = true;
            }

            // Execute the following method if the user clicks Repeat button in PWA Report.
            CheckIfUserWantsToRepeatPWACapture();
        }

        public void StartCaptureProcess()
        {
            try
            {
                if (GuiCommon.StartupScreen.ToUpper() == oMsgMgr.GetMessage(CrxStructCommonResourceMsg.Standard).ToUpper() && !GuiCommon.IsOnReportForm)
                {
                    objValidation.SetMandatoryFields(guipnlMeasurementDetails);
                }

                if (GuiCommon.CurrentMode.Equals(CrxStructCommonResourceMsg.Pwa))
                {
                    ValidationBeforePwaCapture();
                }
                else
                {
                    ValidationBeforePwvCapture();
                }
            }
            catch (Exception ex)
            {
                GUIExceptionHandler.HandleException(ex, this);
                if (GuiCommon.CaptureTabClick)
                {
                    objDefaultWindow.radpgTabCollection.SelectedPage = objDefaultWindow.guiradgrpbxPwvDistanceMethod;
                    objDefaultWindow.guiradgrpbxPwvDistanceMethod.Enabled = true;
                }
            }
        }
              
        public void ChangeMode()
        {
            try
            {
                DisableTimer();
                DisplayLastRecord(GuiCommon.PatientInternalNumber, GuiCommon.GroupId);
            }
            catch (Exception ex)
            {
                throw (ex);
            }
        }

        /** This method is used to Validate age of the patient before validating measurement details.
         */
        public bool ValidatePatientAge()
        {
            bool retVal = false;

            if (GuiCommon.IsValueOutsideLimits)
            {
                GuiCommon.IsValueOutsideLimits = false;
                objDefaultWindow.radpgTabCollection.SelectedPage = objDefaultWindow.guiradgrpbxPwvDistanceMethod;
                objDefaultWindow.guiradgrpbxPwvDistanceMethod.Enabled = true;
                return retVal;
            }

            try
            {
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

                switch (captureEnum)
                {
                    case BizCaptureGate.CAPTURE_GOAHEAD:
                        // Go ahead with the capture.No Confirmation required.                        
                        retVal = true;
                        break;

                    case BizCaptureGate.CAPTURE_CANCEL:
                        // Cancel the capture and bring the user back to setup screen.
                        // Show the user ,warning message recevied from the biz.dll
                        RadMessageBox.Show(this, message, oMsgMgr.GetMessage(CrxStructCommonResourceMsg.SystemError), MessageBoxButtons.OK, RadMessageIcon.Exclamation);
                        objDefaultWindow.guiradmnuScor.Enabled = true;
                        retVal = false;
                        break;
                    case BizCaptureGate.CAPTURE_CONFIRM:
                        DialogResult result = RadMessageBox.Show(this, message, oMsgMgr.GetMessage(CrxStructCommonResourceMsg.SystemError), MessageBoxButtons.YesNo, RadMessageIcon.Exclamation);

                        // Show a popup box to the user with the string provided with Yes and No button.
                        // Yes is proceed with capture.
                        switch (result)
                        {
                            case DialogResult.Yes:
                                retVal = true;
                                break;
                            case DialogResult.No:
                                objDefaultWindow.guiradmnuScor.Enabled = true;
                                retVal = false;
                                break;
                            default:
                                break;
                        }

                        break;

                    default:
                        break;
                }

                return retVal;
            }
            catch (Exception ex)
            {
               // GUIExceptionHandler.HandleException(ex, this);
                return retVal;
                throw (ex);
            }
        }

        private void SetDelayValues()
        {
            try
            {
                AutoProgressbarDelay = CrxSytemParameters.Instance.GetIntegerTagValue("NIBP.AutoPWA.Rest");
                WaitButtonDelay = CrxSytemParameters.Instance.GetIntegerTagValue("NIBP.Repeat.Rest");
            }
            catch (Exception ex)
            {
               // GUIExceptionHandler.HandleException(ex, this);
                throw (ex);
            }
        }

        /**This method sets text for labels in patient demographic details region
      */
        private void SetTextForSetupTab()
        {
            guiradlblPatient.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.LblPateints);
            guiradlblPatientId.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.LblPatientId);
            guiradlblGroup.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.LblGroup);
            guiradlblFirstName.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.LblFirstName);
            guiradlblDateOfBirth.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.LblDob);
            guirdlblGender.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.LblGender);
            guiradlblLastName.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.LblLastName);
            guilblHeight.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.LblHeight);
            guiradlblHeightUnits.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.Cm);
            guiradlblImperialHeight.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.LblInches);            
            guiradlblOperator.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.LblOperator);
            guiradlblMedication.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.LblNotes);
            guiradlblSP.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.LabelSp);
            guiradlblDP.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.LabelDp);
            guiradlblPWAMP.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.LblReportPwaBrachialMp);
            guiradlblPwvDistanceMethod.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.LabelSubtracting);
            guiradlblCarotid.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.LblReportCarotidWithcolon);
            
            guiradlblCarotidTonometerUnits.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.Mm);
            guiradlblCuff.Text = crxMgrObject.PwvSettings.PWVDistanceMethod.Equals((int)CrxGenPwvValue.CrxPwvDistMethodSubtract) ? oMsgMgr.GetMessage(CrxStructCommonResourceMsg.LblReportCuffWithcolon) : oMsgMgr.GetMessage(CrxStructCommonResourceMsg.GuiDirect);
            guiradlblCuffunits.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.Mm);
            guiradlblBrachialBPMeasurement.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.LblSetupBrachialBp);
            guiradlblFemoralToCuff.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.LabelFemoralCuff);
            guiradlblFemoralToCuffUnits.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.Mm);
            guiradlblPwvDistanceCalculation.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.LabelPwvDistance);
            guiradlblPwvDistanceUnits.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.Mm);
            guiradllblPWAHeight.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.LblHeight);
            guiradlblPwaMedicationNotes.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.LblNotes);
            guiradlblPwaOperator.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.LblOperator);
            guiradbtnCapture.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.BtnCapture);
            guiradbtnNew.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.BtnNew);
            guiradbtnSearch.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.BtnSearch);
            guiradbtnEdit.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.BtnEdit);
            guiradbtnCancel.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.BtnCancel);
            guiradbtnSave.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.BtnSave);
            guiradbtnDelete.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.BtnDelete);
            guiradbtnGetBp.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.BtnStart);
            guiradbtnAutoPWACancel.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.BtnCancel);
            guiradlblSPUnits.Text = guiradlblDPUnits.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.UnitsPressureMmhg);
            guiradlblPWAPP.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.LblPP) + ":";         
            guiradlblPWAMP.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.LblReportPwaBrachialMp);
            if ((GuiCommon.StartupScreen.ToUpper() == CrxStructCommonResourceMsg.QuickStart))
            {
                guiradlblPWASP.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.MsgCentralSp);
                guiradlblPWADP.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.MsgCentralDp);
            }
            else
            {
                guiradlblPWASP.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.LabelSp);
                guiradlblPWADP.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.LabelDp);
            }
            guiradlblAvgCentralAorticPulse.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.LblAvgCentralAorticPulse);
        }

        /** This method sets tag property of textbox and labels for validating measurement details on setup screen.
         * It helps in identifying labels & textbox which are mandatory and marked for validation by business logic
         * */
        private void SetSetupTagForValidations()
        {
            if (crxMgrObject.PwvSettings.PWVDistanceMethod.Equals((int)CrxGenPwvValue.CrxPwvDistMethodSubtract))
            {
                guiradlblCuff.Tag = guiradtxtCuff.Tag = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.FemoralDistanceSternalNotchToFemoralCuff);
                guiradlblCarotid.Tag = guiradtxtCarotid.Tag = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.FemoralDistanceCarotidToSternalCuff);
            }

            if (crxMgrObject.PwvSettings.PWVDistanceMethod.Equals((int)CrxGenPwvValue.CrxPwvDistMethodDirect))
            {
                guiradlblCuff.Tag = guiradtxtCuff.Tag = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.FemoralDistanceCarotidToFemoralCuff);   
            }

            guiradlblFemoralToCuff.Tag = guiradtxtFemoralToCuff.Tag = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.FemoralDistanceFemoraltoCuff);
            guiradlblDP.Tag = guiradtxtDP.Tag = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.FieldPatientDp);
            guiradlblSP.Tag = guiradtxtSP.Tag = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.FieldPatientSp);
            guilblHeight.Tag = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.FieldPatientHeight);
            guiradtxtsetupheight.Tag = crxMgrObject.GeneralSettings.HeightandWeightUnit.Equals((int)CrxGenPwvValue.CrxGenHeightWeightMetric) ? oMsgMgr.GetMessage(CrxStructCommonResourceMsg.FieldPatientHeight) : oMsgMgr.GetMessage(CrxStructCommonResourceMsg.FieldPatientHeightFoot);
            guiradtxtImperialHeight.Tag = crxMgrObject.GeneralSettings.HeightandWeightUnit.Equals((int)CrxGenPwvValue.CrxGenHeightWeightMetric) ? string.Empty : oMsgMgr.GetMessage(CrxStructCommonResourceMsg.FieldPatientHeightInch);
            guiradtxtsetupheight.MaxLength = crxMgrObject.GeneralSettings.HeightandWeightUnit.Equals((int)CrxGenPwvValue.CrxGenHeightWeightMetric) ? 3 : 2;

            guiradtxtPWAHeight.Tag = crxMgrObject.GeneralSettings.HeightandWeightUnit.Equals((int)CrxGenPwvValue.CrxGenHeightWeightMetric) ? oMsgMgr.GetMessage(CrxStructCommonResourceMsg.FieldPatientHeight) : oMsgMgr.GetMessage(CrxStructCommonResourceMsg.FieldPatientHeightFoot);
            guiradtxtPWAHeight.MaxLength = crxMgrObject.GeneralSettings.HeightandWeightUnit.Equals((int)CrxGenPwvValue.CrxGenHeightWeightMetric) ? 3 : 2;
            guiradtxtPWAImperialHeight.Tag = crxMgrObject.GeneralSettings.HeightandWeightUnit.Equals((int)CrxGenPwvValue.CrxGenHeightWeightMetric) ? string.Empty : oMsgMgr.GetMessage(CrxStructCommonResourceMsg.FieldPatientHeightInch);         
        }
               
        /**This is Event handler which is called whenever the General settings and PWV settings are chaged in the Settings window.
        *It is used to changes the GUI controls as per the latest General and PWV settings.
        */
        private void SettingsChangedEventHandler(object sender, EventArgs e)
        {
            try
            {
                if (InvokeRequired)
                {
                    Invoke(new EventHandler(SettingsChangedEventHandler));
                    return;
                } 

                ResetPatientMeasurementDetailsAfterSavingSettings();
                GuiCommon.ScorControllerObject.SetHeightWeightUnits();
                     
                // set label text as per settings changed for distance method
                guiradlblCuff.Text = crxMgrObject.PwvSettings.PWVDistanceMethod.Equals((int)CrxGenPwvValue.CrxPwvDistMethodSubtract) ? oMsgMgr.GetMessage(CrxStructCommonResourceMsg.LblReportCuffWithcolon) : oMsgMgr.GetMessage(CrxStructCommonResourceMsg.GuiDirect);
                
                // set tags as per settings changed for height & weight
                guiradtxtsetupheight.Tag = crxMgrObject.GeneralSettings.HeightandWeightUnit.Equals((int)CrxGenPwvValue.CrxGenHeightWeightMetric) ? oMsgMgr.GetMessage(CrxStructCommonResourceMsg.FieldPatientHeight) : oMsgMgr.GetMessage(CrxStructCommonResourceMsg.FieldPatientHeightFoot);
                guiradtxtImperialHeight.Tag = crxMgrObject.GeneralSettings.HeightandWeightUnit.Equals((int)CrxGenPwvValue.CrxGenHeightWeightMetric) ? string.Empty : oMsgMgr.GetMessage(CrxStructCommonResourceMsg.FieldPatientHeightInch);

                guiradtxtPWAHeight.Tag = crxMgrObject.GeneralSettings.HeightandWeightUnit.Equals((int)CrxGenPwvValue.CrxGenHeightWeightMetric) ? oMsgMgr.GetMessage(CrxStructCommonResourceMsg.FieldPatientHeight) : oMsgMgr.GetMessage(CrxStructCommonResourceMsg.FieldPatientHeightFoot); 
                guiradtxtPWAImperialHeight.Tag = crxMgrObject.GeneralSettings.HeightandWeightUnit.Equals((int)CrxGenPwvValue.CrxGenHeightWeightMetric) ? string.Empty : oMsgMgr.GetMessage(CrxStructCommonResourceMsg.FieldPatientHeightInch);
              
                SetSetupTagForValidations();

                // set mandatory fields again after settings are changed from settings window
                if ((GuiCommon.StartupScreen.ToUpper() != oMsgMgr.GetMessage(CrxStructCommonResourceMsg.QuickStart).ToUpper()) && GuiCommon.IsOnSetupScreen)
                {
                    objValidation.SetMandatoryFields(guipnlMeasurementDetails);
                }
                
                if (!string.IsNullOrEmpty(radlblpatientinternalnumber.Text.Trim()) && !string.IsNullOrEmpty(radlblgroupid.Text) && mode != CurrentMode.InsertMode)
                {
                    // to update biz session object with changed setting values
                    DisplayLastRecord(int.Parse(radlblpatientinternalnumber.Text.Trim()), int.Parse(radlblgroupid.Text));
                    objDefaultWindow.guicmbxCurrentMode.Enabled = true;
                    if (GuiCommon.StartupScreen.ToUpper() == CrxStructCommonResourceMsg.QuickStart && objDefaultWindow.guiradgrpbxPwvDistanceMethod.Text.Equals(oMsgMgr.GetMessage(CrxStructCommonResourceMsg.TabPatient)))
                    {
                        objDefaultWindow.radtabReport.Enabled = false;
                    }                    
                }

                GuiCommon.ScorControllerObject.SetDistanceMethodAndUnits();   
                           
                SetPatientPrivacy();
                SetSetupTagForValidations();

                if (!GuiCommon.IsOnReportForm)
                {
                    CheckForResettingPwvDistanceFields();
                    if (GuiCommon.CurrentMode.Equals(CrxStructCommonResourceMsg.Pwv))
                    {
                        bool value = GuiCommon.bizObject.Initialise();
                    }
                    else
                    {
                        // Initialse PWA object.
                        GuiCommon.bizPwaobject.Initialise((crxMgrObject.PwaSettings.CaptureInput.Equals(Convert.ToInt32(CrxPwaCaptureInput.Tonometer)) ? CrxPwaCaptureInput.Tonometer : CrxPwaCaptureInput.Cuff));
                    }
                }              
            }
            catch (Exception ex)
            {
               GUIExceptionHandler.HandleException(ex, this);
               CrxLogger.Instance.Write(ex.StackTrace);   
            }
        }

        /**This is Event handler which is called whenever the General settings and PWV settings are chaged in the Settings window.
        *It is used to changes the GUI controls as per the latest General and PWV settings.
        */
        private void SettingsChangedEventHandlerPwa(object sender, EventArgs e)
        {
            try
            {
                if (InvokeRequired)
                {
                    Invoke(new EventHandler(SettingsChangedEventHandlerPwa));
                    return;
                }

                // reset the measurement text fields and update according to the new settings.
                guiradtxtPWAHeight.Text = string.Empty;
                guiradtxtPWAImperialHeight.Text = string.Empty;

                GuiCommon.ScorControllerObject.SetHeightWeightUnits();                
                guiradtxtPWAHeight.Tag = crxMgrObject.GeneralSettings.HeightandWeightUnit.Equals((int)CrxGenPwvValue.CrxGenHeightWeightMetric) ? oMsgMgr.GetMessage(CrxStructCommonResourceMsg.FieldPatientHeight) : oMsgMgr.GetMessage(CrxStructCommonResourceMsg.FieldPatientHeightFoot);
                guiradtxtPWAImperialHeight.Tag = crxMgrObject.GeneralSettings.HeightandWeightUnit.Equals((int)CrxGenPwvValue.CrxGenHeightWeightMetric) ? string.Empty : oMsgMgr.GetMessage(CrxStructCommonResourceMsg.FieldPatientHeightInch);

                SetSetupTagForValidations();                

                if (!string.IsNullOrEmpty(radlblpatientinternalnumber.Text.Trim()) && !string.IsNullOrEmpty(radlblgroupid.Text))
                {
                    // to update biz session object with changed setting values
                    DisplayLastRecord(int.Parse(radlblpatientinternalnumber.Text.Trim()), int.Parse(radlblgroupid.Text));
                    objDefaultWindow.guicmbxCurrentMode.Enabled = true;
                }             
              
                SetPatientPrivacy();
                SetSetupTagForValidations();
            }
            catch (Exception ex)
            {
                GUIExceptionHandler.HandleException(ex, this);
            }
        }

        /**This method is called to reset the measurement data fields on Setup RHS. 
       */
        private void ResetPatientMeasurementFields()
        {
            guiradtxtPWAHeight.Text = string.Empty;
            guiradtxtPWAImperialHeight.Text = string.Empty;
            guiradtxtMedicationNotes.Text = string.Empty;
            guiradtxtsetupheight.Text = string.Empty;
            guiradtxtImperialHeight.Text = string.Empty;            
            guiradtxtSP.Text = string.Empty;
            guiradtxtDP.Text = string.Empty;
            guiradtxtCarotid.Text = string.Empty;
            guiradtxtCuff.Text = string.Empty;
            guiradlblResult.Text = string.Empty;
            guiradtxtMedication.Text = string.Empty;
            guiradtxtOperator.Text = string.Empty;
        }

        /**This method is called to reset the measurement data fields on Setup RHS after editing the settings on the settings window. 
      */
        private void ResetPatientMeasurementDetailsAfterSavingSettings()
        {
            guiradtxtPWAHeight.Text = string.Empty;
            guiradtxtPWAImperialHeight.Text = string.Empty;
            guiradtxtMedicationNotes.Text = string.Empty;
            guiradtxtsetupheight.Text = string.Empty;
            guiradtxtImperialHeight.Text = string.Empty;
            guiradtxtSP.Text = string.Empty;
            guiradtxtDP.Text = string.Empty;
            guiradlblResult.Text = string.Empty;
            guiradtxtMedication.Text = string.Empty;
            guiradtxtOperator.Text = string.Empty;
        }

        /** This event fires when form is loaded.
         */
        private void Setup_Load(object sender, EventArgs e)
        {
            try
            {
                if (InvokeRequired)
                {
                    Invoke(new EventHandler(Setup_Load));
                    return;
                }

                LoadSetup();
            }
            catch (Exception ex)
            {
                GUIExceptionHandler.HandleException(ex, this);
            }
        }       

        /** This method sets the patient gridview as per the patient privacy setting from the config
         * */
        private void SetPatientPrivacy()
        {
            if (crxMgrObject.GeneralSettings.PatientPrivacy)
            {
                // patient privacy is enabled hide gridview
                ShowHidePatientDetails(oMsgMgr.GetMessage(CrxStructCommonResourceMsg.HideSmall));
                guiradbtnExpander.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.ShowCaps);
            }
            else
            {
                // show gridview
                ShowHidePatientDetails(oMsgMgr.GetMessage(CrxStructCommonResourceMsg.ShowSmall));
                guiradbtnExpander.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.HideCaps);
            }
        }

        /** This method binds gender values
         */
        private void FillGender()
        {
            try
            {
                guicmbxGender.Items.Clear();
                RadListDataItem genname = new RadListDataItem
                {
                    Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.SelectCaps),
                    Value = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.SelectCaps)
                };

                RadListDataItem genmale = new RadListDataItem
                {
                    Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.MaleTxt),
                    Value = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.MaleTxt)
                };

                RadListDataItem genfemale = new RadListDataItem
                {
                    Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.FemaleTxt),
                    Value = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.FemaleTxt)
                };
                guicmbxGender.Items.Add(genname);
                guicmbxGender.Items.Add(genmale);
                guicmbxGender.Items.Add(genfemale);
                guicmbxGender.SelectedIndex = Convert.ToInt32(GuiCommon.NumericValue.Zero);
            }
            catch (Exception ex)
            {
                throw (ex);
            }      
        }

        /**This method is used to populate the group names into the combo box from the database using database manager class. 
      */
        private void LoadGroupNames()
        {
            // fetches group name and binds it
            try
            {
                if (dbMagr.CheckConnection(serverNameString, crxMgrObject.GeneralSettings.SourceData) == Convert.ToInt32(GuiCommon.NumericValue.Zero))
                {
                    GuiCommon.BindGroupNames(guicmbGroup, dbMagr);
                }
                else
                {
                    DialogResult result = RadMessageBox.Show(this, GuiCommon.ConnectionErrorString(), oMsgMgr.GetMessage(CrxStructCommonResourceMsg.SystemError), MessageBoxButtons.RetryCancel, RadMessageIcon.Error);
                    if (result == DialogResult.Retry)
                    {
                        LoadGroupNames();
                    }
                }
            }            
            catch (Exception ex)
            {
               // GUIExceptionHandler.HandleException(ex, this);
                throw (ex);
            }            
        }       

        /** This method is used to show the grid view when the Expand button is clicked.
       */ 
        private void guiradbtnExpander_Click(object sender, EventArgs e)
        {
            try
            {
                if (string.Compare(guiradbtnExpander.Text, oMsgMgr.GetMessage(CrxStructCommonResourceMsg.HideSmall), StringComparison.CurrentCultureIgnoreCase) == Convert.ToInt32(GuiCommon.NumericValue.Zero))
                {
                    ShowHidePatientDetails(oMsgMgr.GetMessage(CrxStructCommonResourceMsg.HideSmall));
                    guiradbtnExpander.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.ShowCaps);
                }
                else
                {
                    ShowHidePatientDetails(oMsgMgr.GetMessage(CrxStructCommonResourceMsg.ShowSmall));
                    guiradbtnExpander.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.HideCaps);
                }

                SetButtonsForHideMode();
            }
            catch (Exception ex)
            {
                GUIExceptionHandler.HandleException(ex, this);
            }
        }

        /** This method is used to hide the grid view when the Expand button is clicked.
         * */
        private void ShowHidePatientDetails(string value)
        {
            // disable cancel button when there are no records in patient list
            if (guiradgrdPatientList.Rows.Count == Convert.ToInt32(GuiCommon.NumericValue.Zero))
            {
                guiradbtnCancel.Enabled = false;
            }

            // hides patient gridview acoording to show / hide values
            if (value.Equals(oMsgMgr.GetMessage(CrxStructCommonResourceMsg.HideSmall), StringComparison.CurrentCultureIgnoreCase))
            {
                splitContainer1.SplitterDistance = PatientListHideValue;
                guiradbtnEdit.Enabled = false;
                guiradbtnDelete.Enabled = false;
                guiradbtnSearch.Enabled = false;
                guiradgrdPatientList.Visible = false;

                // Disable the vertical scrollbar                                 
                guiradgrdPatientList.VerticalScrollState = ScrollState.AlwaysHide;
                radLabel1.Visible = true;
            }
            else
            {
                splitContainer1.SplitterDistance = PatientListShowValue;
                guiradgrdPatientList.Visible = true;
                guiradbtnSearch.Enabled = (mode == CurrentMode.None && guiradgrdPatientList.Rows.Count > Convert.ToInt32(GuiCommon.NumericValue.Zero)) ? true : false;
                guiradbtnDelete.Enabled = guiradbtnEdit.Enabled = (mode == CurrentMode.None && guiradgrdPatientList.Rows.Count > 0) ? true : false;
                
                // Enaable the vertical scrollbar
                guiradgrdPatientList.VerticalScrollState = ScrollState.AlwaysShow;
                radLabel1.Visible = false;
            }
        }

        /** This method is used to initialise the grid view.
        */
        private void InitializePatientList()
        {
            try
            {
                guiradgrdPatientList.Columns.Clear();
                isCellInitializeWidth = true;
                guiradgrdPatientList.TableElement.BeginUpdate();
                
                guiradgrdPatientList.Columns.Add(CrxDBGetPatientDetails.SystemIdentifier.ToString(), CrxDBGetPatientDetails.SystemIdentifier.ToString(), CrxDBGetPatientDetails.SystemIdentifier.ToString());
                guiradgrdPatientList.Columns[0].Width = Convert.ToInt32(GuiCommon.NumericValue.Zero);
                guiradgrdPatientList.Columns[0].IsVisible = false;

                guiradgrdPatientList.Columns.Add(CrxDBGetPatientDetails.PatientNumberInternal.ToString(), CrxDBGetPatientDetails.PatientNumberInternal.ToString(), CrxDBGetPatientDetails.PatientNumberInternal.ToString());
                guiradgrdPatientList.Columns[1].Width = 101;
                guiradgrdPatientList.Columns[1].IsVisible = false;

                guiradgrdPatientList.Columns.Add(CrxDBGetPatientDetails.GroupIdentifier.ToString(), CrxDBGetPatientDetails.GroupIdentifier.ToString(), CrxDBGetPatientDetails.GroupIdentifier.ToString());
                guiradgrdPatientList.Columns[2].Width = 101;
                guiradgrdPatientList.Columns[2].IsVisible = false;

                guiradgrdPatientList.Columns.Add(CrxDBGetPatientDetails.PatientIdExternalReference.ToString(), oMsgMgr.GetMessage(CrxStructCommonResourceMsg.GuiDisplayPatientId), CrxDBGetPatientDetails.PatientIdExternalReference.ToString());
                guiradgrdPatientList.Columns[3].Width = 101;

                guiradgrdPatientList.Columns.Add(CrxDBGetPatientDetails.LastName.ToString(), oMsgMgr.GetMessage(CrxStructCommonResourceMsg.GuiDisplayLastName), CrxDBGetPatientDetails.LastName.ToString());
                guiradgrdPatientList.Columns[4].Width = 101;

                guiradgrdPatientList.Columns.Add(CrxDBGetPatientDetails.FirstName.ToString(), oMsgMgr.GetMessage(CrxStructCommonResourceMsg.GuiDisplayFirstName), CrxDBGetPatientDetails.FirstName.ToString());
                guiradgrdPatientList.Columns[5].Width = 102;

                guiradgrdPatientList.Columns.Add(CrxDBGetPatientDetails.DateOfBirth.ToString(), oMsgMgr.GetMessage(CrxStructCommonResourceMsg.LblReportDob).Replace(oMsgMgr.GetMessage(CrxStructCommonResourceMsg.GuiDisplayColon), string.Empty), CrxDBGetPatientDetails.DateOfBirth.ToString());
                guiradgrdPatientList.Columns[6].Width = 101;

                // below is a c# format specifier and hence cannot be localized or created as constant
                guiradgrdPatientList.Columns[6].FormatString = "{0:" + CultureInfo.CurrentCulture.DateTimeFormat.ShortDatePattern + "}"; 

                guiradgrdPatientList.Columns.Add(CrxDBGetPatientDetails.Gender.ToString(), oMsgMgr.GetMessage(CrxStructCommonResourceMsg.GuiDisplayGender), CrxDBGetPatientDetails.Gender.ToString());
                guiradgrdPatientList.Columns[7].Width = 101;

                guiradgrdPatientList.EnableAlternatingRowColor = true;
                guiradgrdPatientList.GridElement.AlternatingRowColor = Color.Gray;
                           
                guiradgrdPatientList.TableElement.EndUpdate();
                guiradgrdPatientList.AutoGenerateColumns = false;
                isCellInitializeWidth = false;
            }
            catch (Exception ex)
            {
               // GUIExceptionHandler.HandleException(ex, this);
                throw (ex);
            }
        }

        /** This method populates the patient data from the database into the Patient grid view.
        */
        private void LoadPatientList()
        {
            try
                {
                if (dbMagr.CheckConnection(serverNameString, crxMgrObject.GeneralSettings.SourceData) == 0)
                {
                    DataSet ds = dbMagr.GetPatientDemographicRecords();

                    // Call FetchRecords method from Database Manager
                    guiradgrdPatientList.DataSource = ds.Tables[0];

                    if (ds.Tables[0].Rows.Count > Convert.ToInt32(GuiCommon.NumericValue.Zero))
                    {
                        mode = CurrentMode.None;
                        guiradgrdPatientList.Enabled = true;
                                                
                        guiradlblNumberOfPatients.Text = ds.Tables[0].Rows.Count.ToString();

                        // Display last record details into the demographic fields.
                        GridViewRowInfo lastRow = guiradgrdPatientList.Rows[guiradgrdPatientList.Rows.Count - 1];
                        lastRow.IsCurrent = true;
                        lastRow.IsSelected = true;
                        int patientIdInternal = int.Parse(lastRow.Cells[1].Value.ToString());
                        int groupId = int.Parse(lastRow.Cells[2].Value.ToString());
                        radlblpatientinternalnumber.Text = patientIdInternal.ToString();
                        radlblgroupid.Text = groupId.ToString();
                        DisplayLastRecord(patientIdInternal, groupId);
                        objDefaultWindow.guiradmenuBackup.Enabled = true;
                    }
                    else
                    {
                        guiradlblNumberOfPatients.Text = "0";

                        // no records in table set to insert mode
                        // disable capture & report tabs
                        objDefaultWindow.radtabReport.Enabled = objDefaultWindow.radtabCapture.Enabled = false;
                        objDefaultWindow.radlblPatientName.Text = string.Empty;

                        guiradtxtPatientID.Focus();
                        guipnlMeasurementDetails.Visible = false;
                        guipnlPWAMeasurementDetails.Visible = false;
                        mode = CurrentMode.InsertMode;                        
                        ResetFields();
                        ResetPatientMeasurementFields();
                        BrowseMode(false);
                        guiradbtnCancel.Enabled = false; 

                        FillDay(0);

                        guiradgrdPatientList.Enabled = false;
                        GuiCommon.HasMeasurementDetails = false;
                        GuiCommon.IsWaitIntervalImposed = false;
                        objDefaultWindow.radlblMessage.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.InsertMode);
                        radlblpatientinternalnumber.Text = radlblgroupid.Text = string.Empty;                        
                    }
                }
                else
                {
                    DialogResult result = RadMessageBox.Show(this, GuiCommon.ConnectionErrorString(), oMsgMgr.GetMessage(CrxStructCommonResourceMsg.SystemError), MessageBoxButtons.RetryCancel, RadMessageIcon.Error);
                    if (result == DialogResult.Retry)
                    {
                        LoadPatientList();
                    }
                }
            }
            catch (Exception ex)
            {
               // GUIExceptionHandler.HandleException(ex, this);
                throw (ex);
            }                   
        }

        /** This method is used to load the demographic details of the last pateint in the Patientlist gridview.
         */
        private void DisplayLastRecord(int patientNumberInternal, int groupId)
        {
            try
            {
                if (dbMagr.CheckConnection(serverNameString, crxMgrObject.GeneralSettings.SourceData) == Convert.ToInt32(GuiCommon.NumericValue.Zero))
                {
                    // reset demographic fields
                    ResetFields();
                    BrowseMode(mode == CurrentMode.None);

                    DataSet dsPatientDemographicDetails = dbMagr.GetPatientDemographicRecords(patientNumberInternal, bobj, groupId);

                    if (dsPatientDemographicDetails.Tables[0].Rows.Count > Convert.ToInt32(GuiCommon.NumericValue.Zero))
                    {                       
                        DateTime date = Convert.ToDateTime(dsPatientDemographicDetails.Tables[0].Rows[0][(int)CrxDBGetPatientDetailsById.DateOfBirth]);

                        // Populate the patient's demographic details in the form.
                        guiradtxtPatientID.Text = dsPatientDemographicDetails.Tables[0].Rows[0][(int)CrxDBGetPatientDetailsById.PatientIdExternalReference].ToString();
                        guiradtxtFirstName.Text = dsPatientDemographicDetails.Tables[0].Rows[0][(int)CrxDBGetPatientDetailsById.FirstName].ToString();
                        guiradtxtLastName.Text = dsPatientDemographicDetails.Tables[0].Rows[0][(int)CrxDBGetPatientDetailsById.LastName].ToString();
                        guicmbGroup.Text = dsPatientDemographicDetails.Tables[0].Rows[0][(int)CrxDBGetPatientDetailsById.GroupName].ToString();
                        originalgroupname = guicmbGroup.Text;
                        orgPatientIdExt = guiradtxtPatientID.Text;
                        guicmbxMonth.SelectedIndex = date.Month;
                        guicmbxYear.SelectedValue = date.Year;                        
                        guicmbDay.SelectedIndex = date.Day;
                        string tempGender = CultureInfo.CurrentCulture.TextInfo.ToTitleCase(dsPatientDemographicDetails.Tables[0].Rows[0][(int)CrxDBGetPatientDetailsById.Gender].ToString().Trim().ToUpper());
                        guicmbxGender.SelectedValue = tempGender.Trim().Equals(CrxStructCommonResourceMsg.MaleTxt) ? oMsgMgr.GetMessage(CrxStructCommonResourceMsg.MaleTxt) : oMsgMgr.GetMessage(CrxStructCommonResourceMsg.FemaleTxt);

                        // display patients first & last name at bottom
                        objDefaultWindow.radlblPatientName.Text = !string.IsNullOrEmpty(guiradtxtFirstName.Text.Trim()) ? string.Format("{0} {1}", guiradtxtFirstName.Text.Trim(), guiradtxtLastName.Text.Trim()) : guiradtxtLastName.Text.Trim();

                        radlblpatientinternalnumber.Text = patientNumberInternal.ToString();
                        radlblgroupid.Text = groupId.ToString();

                        // intialize bizpatient object with selected record
                        BizPatient patientObj = BizPatient.Instance();
                        patientObj.dateOfBirth = date;
                        patientObj.firstName = guiradtxtFirstName.Text.Trim();
                        patientObj.gender = guicmbxGender.Text.Trim().Equals(oMsgMgr.GetMessage(CrxStructCommonResourceMsg.MaleTxt)) ? CrxStructCommonResourceMsg.MaleTxt : CrxStructCommonResourceMsg.FemaleTxt;
                        patientObj.patientNumber = UInt32.Parse(radlblpatientinternalnumber.Text.Trim());
                        patientObj.groupStudyId = uint.Parse(groupId.ToString());
                        patientObj.systemId = uint.Parse(bobj.ToString());
                        
                        // groupstudyId, patientnumber id to be retrieved
                        patientObj.lastName = guiradtxtLastName.Text.Trim();
                        patientObj.patientId = guiradtxtPatientID.Text.Trim();
                        GuiCommon.GroupId = int.Parse(radlblgroupid.Text);
                        GuiCommon.GroupName = guicmbGroup.Text;
                        GuiCommon.PatientInternalNumber = int.Parse(radlblpatientinternalnumber.Text);
                        GuiCommon.SystemIdentifier = bobj;                         

                        // initialising RHS measurement display as per scor settings
                        GuiCommon.ScorControllerObject.SetHeightWeightUnits();
                        if (!(GuiCommon.CurrentMode.Equals(CrxStructCommonResourceMsg.Pwa) && objDefaultWindow.guiradgrpbxPwvDistanceMethod.Text.Equals(oMsgMgr.GetMessage(CrxStructCommonResourceMsg.TabPatient))))
                        {
                            GuiCommon.ScorControllerObject.SetBloodPressure();
                            GuiCommon.ScorControllerObject.SetDistanceMethodAndUnits();
                        }

                        FillSessionObjFromDB();
                        GuiCommon.IsFormChanged = false;
                        if (mode == CurrentMode.EditMode || mode == CurrentMode.InsertMode)
                        {
                            objDefaultWindow.radtabCapture.Enabled = false;
                            objDefaultWindow.radtabReport.Enabled = false;
                        }
                        else
                        {
                            objDefaultWindow.radtabQuickStart.Enabled = true;
                        }
                    }                                                    
                }
                else
                {
                    DialogResult result = RadMessageBox.Show(this, GuiCommon.ConnectionErrorString(), oMsgMgr.GetMessage(CrxStructCommonResourceMsg.SystemError), MessageBoxButtons.RetryCancel, RadMessageIcon.Error);
                    if (result == DialogResult.Retry)
                    {
                        DisplayLastRecord(patientNumberInternal, groupId);
                    }
                }
            }           
            catch (Exception ex)
            {
                GUIExceptionHandler.HandleException(ex, this);
            }           
        }

        /** This method is used to enable & disable buttons based on modes and expand button text
        */
        private void SetButtonsForHideMode()
        {
            try
            {
                if (string.Compare(guiradbtnExpander.Text, oMsgMgr.GetMessage(CrxStructCommonResourceMsg.ShowSmall), StringComparison.CurrentCultureIgnoreCase) == 0)
                {
                    guiradbtnEdit.Enabled = false;
                    guiradbtnDelete.Enabled = false;
                    if (mode == CurrentMode.None)
                    {
                        guiradbtnCancel.Enabled = false;
                    }
                    else
                    {
                        guiradbtnCancel.Enabled = guiradgrdPatientList.Rows.Count == Convert.ToInt32(GuiCommon.NumericValue.Zero) ? false : true;
                    }

                    objDefaultWindow.radlblPatientName.Visible = false;
                }
                else
                {
                    if (mode == CurrentMode.InsertMode || mode == CurrentMode.EditMode || mode == CurrentMode.SearchMode)
                    {
                        guiradbtnCancel.Enabled = guiradgrdPatientList.Rows.Count == Convert.ToInt32(GuiCommon.NumericValue.Zero) ? false : true;
                        guiradbtnEdit.Enabled = false;
                        guiradbtnDelete.Enabled = false;
                        objDefaultWindow.radlblPatientName.Visible = false;
                    }
                    else
                    {
                        guiradbtnEdit.Enabled = true;
                        guiradbtnDelete.Enabled = true;
                        if (isSearchOn)
                        {
                            guiradbtnCancel.Enabled = guiradgrdPatientList.Rows.Count <= Convert.ToInt32(GuiCommon.NumericValue.Zero) ? false : true;
                        }
                        else
                        {
                            guiradbtnCancel.Enabled = false;
                        }
                    }
                }
            }
            catch (Exception ex)
            {
                throw (ex);
            }
        }

        /** This method makes the Demographic details of the patient read only(browse mode) when true and vice versa.
         */
        private void BrowseMode(bool value)
        {
            try
            {
                if (mode == CurrentMode.None)
                {
                    objDefaultWindow.radlblMessage.Text = string.Empty;
                }

                if (value)
                {
                    // enable database backup & restore
                    objDefaultWindow.guiradmnuDatabase.Enabled = true;

                    // makes all input fields read only and disables combo boxes
                    guiradtxtFirstName.Enabled = false;
                    guiradtxtLastName.Enabled = false;
                    guiradtxtPatientID.Enabled = false;
                    guicmbGroup.Enabled = false;
                    guicmbxGender.Enabled = false;
                    guicmbDay.Enabled = false;
                    guicmbxMonth.Enabled = false;
                    guicmbxYear.Enabled = false;

                    // enable disable cancel button in browse mode based on isSearchOn value...
                    // this variable will be true when records are displayed in grid in search mode
                    guiradbtnCancel.Enabled = isSearchOn;
                    guiradbtnSave.Enabled = false;
                    guiradbtnSearch.Enabled = guiradbtnExpander.Text.Equals(oMsgMgr.GetMessage(CrxStructCommonResourceMsg.HideCaps)) && guiradgrdPatientList.Rows.Count > 0;
                    guiradbtnNew.Enabled = true;
                    SetButtonsForHideMode();

                    EnableDisableMeasurmenetPanelForPwvAndPwa();

                    if (!(GuiCommon.CurrentMode.Equals(CrxStructCommonResourceMsg.Pwa) && objDefaultWindow.guiradgrpbxPwvDistanceMethod.Text.Equals(oMsgMgr.GetMessage(CrxStructCommonResourceMsg.TabPatient))))
                    {
                        objDefaultWindow.guicmbxCurrentMode.Enabled = true;
                    }
                }
                else
                {
                    // disable database backup & restore
                    objDefaultWindow.guiradmnuDatabase.Enabled = mode != CurrentMode.InsertMode || guiradgrdPatientList.Rows.Count > 0 ? false : true;

                    // default enable property for these controls is True, hence seting this 
                    // property again to true on form load dose not call the handle enable event 
                    // hence purposefully setting them to false first. Fixed against PWVSW-229
                    guiradtxtFirstName.Enabled = false;
                    guiradtxtLastName.Enabled = false;
                    guiradtxtPatientID.Enabled = false;
                    guicmbGroup.Enabled = false;
                    guicmbxGender.Enabled = false;
                    guicmbDay.Enabled = false;
                    guicmbxMonth.Enabled = false;
                    guicmbxYear.Enabled = false;

                    // removes read only mode and sets button(disable / enable) depending on mode
                    guiradtxtFirstName.Enabled = true;
                    guiradtxtLastName.Enabled = true;
                    guiradtxtPatientID.Enabled = true;
                    guicmbGroup.Enabled = true;
                    guicmbxGender.Enabled = true;
                    guicmbDay.Enabled = true;
                    guicmbxMonth.Enabled = true;
                    guicmbxYear.Enabled = true;

                    if (mode == CurrentMode.InsertMode)
                    {
                        guiradbtnCancel.Enabled = guiradgrdPatientList.Rows.Count == Convert.ToInt32(GuiCommon.NumericValue.Zero) ? false : true;
                        guiradbtnSave.Enabled = true;
                        guiradbtnSearch.Enabled = false;
                        guiradbtnEdit.Enabled = false;
                        guiradbtnDelete.Enabled = false;
                        guiradbtnNew.Enabled = false;

                        HideMeasurementPanelDependingOnMode();
                    }
                    else if (mode == CurrentMode.EditMode)
                    {
                        guiradbtnCancel.Enabled = true;
                        guiradbtnSave.Enabled = true;
                        guiradbtnSearch.Enabled = false;
                        guiradbtnEdit.Enabled = false;
                        guiradbtnDelete.Enabled = false;
                        guiradbtnNew.Enabled = false;

                        HideMeasurementPanelDependingOnMode();
                    }
                    else if (mode == CurrentMode.SearchMode)
                    {
                        guiradbtnCancel.Enabled = true;
                        guiradbtnSave.Enabled = false;
                        guiradbtnSearch.Enabled = false;
                        guiradbtnEdit.Enabled = false;
                        guiradbtnDelete.Enabled = false;
                        guiradbtnNew.Enabled = false;

                        HideMeasurementPanelDependingOnMode();
                    }
                    else
                    {
                        guiradbtnCancel.Enabled = true;
                        guiradbtnSave.Enabled = true;
                    }


                    objDefaultWindow.guiradmenuBackup.Enabled = guiradgrdPatientList.Rows.Count == Convert.ToInt32(GuiCommon.NumericValue.Zero) ? false : true;

                    if (guiradgrdPatientList.Rows.Count <= Convert.ToInt32(GuiCommon.NumericValue.Zero))
                    {
                        guipnlPWAMeasurementDetails.Visible = guipnlMeasurementDetails.Visible = false;
                    }
                }
            }
            catch (Exception ex)
            {
                throw (ex);
            }
        }

        /** This method is called on the click of the Save button,it is used to validate the demograhic details entered by the user and save the same into the database.
         *  Any expection thrown while saving the details into the database will be caught by the configuration file and logged. 
         *  This expection will be shown to the user using a message box,also it will be logged into the log file.
         */
        private void guiradbtnSave_Click(object sender, EventArgs e)
        {
            try
            {
                SaveSetupData();

                // this is a scenarion where in the there are no patient in the system,the user tries to add the first pateint.here we need to add the Bp measurmenrt
                // in the RHS hence adding the below condition.THis happens only when the first pateint is added into the system.
                if (guiradgrdPatientList.Rows.Count.Equals(Convert.ToInt32(GuiCommon.NumericValue.One)))
                {
                    FillBpMeasurementData();
                }
            }
            catch (Exception ex)
            {
                GUIExceptionHandler.HandleException(ex, this);
            }
        }  

        /**This method checks if a given patient id exists,while adding a record.
         */
        private void CheckForPatientIdToAddPatient()
        {
            try
            {
                // check for db connection
                if (dbMagr.CheckConnection(serverNameString, crxMgrObject.GeneralSettings.SourceData) == Convert.ToInt32(GuiCommon.NumericValue.Zero))
                {
                    AddNewPatientDetails();
                }
                else
                {
                    DialogResult result = RadMessageBox.Show(this, GuiCommon.ConnectionErrorString(), oMsgMgr.GetMessage(CrxStructCommonResourceMsg.SystemError), MessageBoxButtons.RetryCancel, RadMessageIcon.Error);
                    if (result == DialogResult.Retry)
                    {
                        CheckForPatientIdToAddPatient();
                    }
                }
            }
            catch (Exception ex)
            {
                throw (ex);
            }
        }

        /**This method checks if a given patient id exists,while updating a record.
         */
        private void CheckForPatientIdToUpdatePatient()
        {
            try
            {
                // check for db connection
                if (dbMagr.CheckConnection(serverNameString, crxMgrObject.GeneralSettings.SourceData) == Convert.ToInt32(GuiCommon.NumericValue.Zero))
                {
                    // check if old patient ID is changed
                    if (string.Compare(orgPatientIdExt, guiradtxtPatientID.Text.Trim(), true, CultureInfo.CurrentCulture) != Convert.ToInt32(GuiCommon.NumericValue.Zero))
                    {
                        UpdatePatientDetails();
                    }
                    else
                    {
                        // patient ID not changed, update record
                        UpdatePatientDetails();
                    }
                }
                else
                {
                    DialogResult result = RadMessageBox.Show(this, GuiCommon.ConnectionErrorString(), oMsgMgr.GetMessage(CrxStructCommonResourceMsg.SystemError), MessageBoxButtons.RetryCancel, RadMessageIcon.Error);
                    if (result == DialogResult.Retry)
                    {
                        CheckForPatientIdToUpdatePatient();
                    }
                }
            }
            catch (Exception ex)
            {
                throw (ex);
            }
        }                  

        /** This method is used to update the patient demographic details and save the same into the database.
        */
        private void UpdatePatientDetails()
        {
            try
            {
                // updates patient record
                SavePatient(string.Empty);                
            }
            catch (Exception ex)
            {
               // GUIExceptionHandler.HandleException(ex, this);
                throw (ex);
            }
        }

        /** This method is used to save new group name.
         */
        private void AddNewPatientDetails()
        {
            try
            {
                SavePatient(string.Empty);                
            }
            catch (Exception ex)
            {
               // GUIExceptionHandler.HandleException(ex, this);
                throw (ex);
            }
        }

        /** This method saves (insert or update) patient demographic data 
         */
        private void SavePatient(string groupname)
        {
            try
            {
                // saves patient record to database
                // check for db connection
                if (dbMagr.CheckConnection(serverNameString, crxMgrObject.GeneralSettings.SourceData) == Convert.ToInt32(GuiCommon.NumericValue.Zero))
                {
                    // instantiate struct with values entered
                    CrxStructPatientDemographicData patientData = new CrxStructPatientDemographicData
                    {
                        FirstName = guiradtxtFirstName.Text.Trim(),
                        Gender = guicmbxGender.Text.Trim().Equals(oMsgMgr.GetMessage(CrxStructCommonResourceMsg.MaleTxt)) ? CrxStructCommonResourceMsg.MaleTxt : CrxStructCommonResourceMsg.FemaleTxt,
                        LastName = guiradtxtLastName.Text.Trim()
                    };
                    string dob = string.Format("{0}/{1}/{2}", guicmbDay.Text, guicmbxMonth.Text, guicmbxYear.Text);

                    patientData.DateOfBirth = Convert.ToDateTime(dob, culture);

                    // set groupname to default if not selected
                    patientData.GroupName = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.EnvClinicalText); // string.IsNullOrEmpty(groupname) ? oMsgMgr.GetMessage(CrxStructCommonResourceMsg.SysDefaultLowcase) : groupname.Equals(oMsgMgr.GetMessage(CrxStructCommonResourceMsg.SelectSmall), StringComparison.CurrentCultureIgnoreCase) ? oMsgMgr.GetMessage(CrxStructCommonResourceMsg.SysDefaultLowcase) : groupname;
                    patientData.SystemIdentifier = bobj;
                    patientData.PatientIDExternalReference = guiradtxtPatientID.Text.Trim();

                    SavePatientData(patientData);
                }
                else
                {
                    DialogResult result = RadMessageBox.Show(this, GuiCommon.ConnectionErrorString(), oMsgMgr.GetMessage(CrxStructCommonResourceMsg.SystemError), MessageBoxButtons.RetryCancel, RadMessageIcon.Error);
                    if (result == DialogResult.Retry)
                    {
                        SavePatient(groupname);
                    }
                }
            }
            catch (Exception ex)
            {
                throw (ex);
            }
        }

        /** This method saves patient data 
         * */
        private void SavePatientData(CrxStructPatientDemographicData patientData)
        {
            try
            {
                int iRow = Convert.ToInt32(GuiCommon.NumericValue.Zero);

                // check if patient record exists and save accordingly
                if (mode == CurrentMode.InsertMode)
                {
                    // insert new record when patient does not exists
                    if (dbMagr.PatientRecordExists(patientData) == Convert.ToInt32(GuiCommon.NumericValue.Zero))
                    {
                        iRow = dbMagr.SavePatientData(patientData);
                    }
                    else
                    {
                        RadMessageBox.Show(this, oMsgMgr.GetMessage(CrxStructCommonResourceMsg.PatientAlreadyExists), oMsgMgr.GetMessage(CrxStructCommonResourceMsg.SystemError), MessageBoxButtons.OK, RadMessageIcon.Error);
                    }
                }
                else
                {
                    // update patient record
                    patientData.PatientNumberInternal = int.Parse(radlblpatientinternalnumber.Text);
                    patientData.GroupIdentifier = int.Parse(radlblgroupid.Text);
                    if (dbMagr.PatientRecordExists(patientData) == Convert.ToInt32(GuiCommon.NumericValue.Zero))
                    {
                        iRow = dbMagr.UpdatePatientData(patientData, true);
                    }
                    else
                    {
                        RadMessageBox.Show(this, oMsgMgr.GetMessage(CrxStructCommonResourceMsg.PatientAlreadyExists), oMsgMgr.GetMessage(CrxStructCommonResourceMsg.SystemError), MessageBoxButtons.OK, RadMessageIcon.Error);
                    }
                }

                if (iRow > Convert.ToInt32(GuiCommon.NumericValue.Zero))
                {
                    DisplaySavedPatientData(patientData);
                    GuiCommon.IsFormChanged = false;
                }
            }
            catch (Exception ex)
            {
                throw (ex);
            }
        }

        /** This method displays data for patient being saved currently 
       */
        private void DisplaySavedPatientData(CrxStructPatientDemographicData patientData)
        {
            try
            {
                EnableDisableMeasurmenetPanelForPwvAndPwa();
                if (GuiCommon.CurrentMode.Equals(CrxStructCommonResourceMsg.Pwv))
                {
                    objDefaultWindow.radtabCapture.Enabled = guiradbtnCapture.Enabled = !GuiCommon.IsWaitIntervalImposed;
                }

                GuiCommon.ScorControllerObject.SetHeightWeightUnits();
                GuiCommon.ScorControllerObject.SetBloodPressure();
                GuiCommon.ScorControllerObject.SetDistanceMethodAndUnits();

                LoadPatientList();
                guiradgrdPatientList.Enabled = true;
            }
            catch (Exception ex)
            {
               // GUIExceptionHandler.HandleException(ex, this);
                throw (ex);
            }
        }

        /** This method is called when the user clicks on the New button in the GUI.The user can enter new patient details.
        */
        private void guiradbtnNew_Click(object sender, EventArgs e)
        {
            try
            {
                objDefaultWindow.guicmbxCurrentMode.Enabled = false;
                FillGender();
                isSearchOn = false;
                HideMeasurementPanelDependingOnMode();
                mode = CurrentMode.InsertMode;
                ResetFields();
                BrowseMode(false);

                FillDay(Convert.ToInt32(GuiCommon.NumericValue.Zero));

                guiradgrdPatientList.Enabled = false;

                // disable capture & report tab in insert mode
                objDefaultWindow.radtabReport.Enabled = false;
                objDefaultWindow.radtabCapture.Enabled = false;
                objDefaultWindow.radtabQuickStart.Enabled = false;
                objDefaultWindow.radlblMessage.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.InsertMode);
                objDefaultWindow.radlblPatientName.Text = string.Empty;

                GuiCommon.IsFormChanged = true;

                // set the focus to the Patient Id field.
                guiradtxtFirstName.Focus();
            }
            catch (Exception ex)
            {
                GUIExceptionHandler.HandleException(ex, this);
            }
        }

        /** This method is called when the user clicks on the Search button in the GUI.
         * It searches patient from gridview based on criteria given
        */
        private void guiradbtnSearch_Click(object sender, EventArgs e)
        {
            objDefaultWindow.guicmbxCurrentMode.Enabled = false;
            isSearchOn = false;          
            try
            {
                // check for db connection
                if (dbMagr.CheckConnection(serverNameString, crxMgrObject.GeneralSettings.SourceData) == 0)
                {
                    // get the patient record and cached it
                    DataSet ds = dbMagr.GetPatientDemographicRecords();

                    /** "cachePatient" is the name of cache which will store patient list in cache for searching patients
                     * Once the search start patients will be retrieved from the cache and dbManager will not be called for every search
                     * this name is used for internal use only
                     */
                    AppDomain.CurrentDomain.SetData("cachePatient", ds); 
                    objDefaultWindow.radlblMessage.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.SearchMode);
                    objDefaultWindow.radlblPatientName.Text = string.Empty;
                     
                    mode = prevMode = CurrentMode.SearchMode;
                    isSearchReset = true;
                    ResetFields();
                    BrowseMode(false);
                    isSearchReset = false;

                    // disable capture & report tab in search mode
                    objDefaultWindow.radtabReport.Enabled = false;
                    objDefaultWindow.radtabCapture.Enabled = false;
                    objDefaultWindow.radtabQuickStart.Enabled = false;
                    guiradtxtPatientID.Focus();
                }
                else
                {
                    DialogResult result = RadMessageBox.Show(this, GuiCommon.ConnectionErrorString(), oMsgMgr.GetMessage(CrxStructCommonResourceMsg.SystemError), MessageBoxButtons.RetryCancel, RadMessageIcon.Error);
                    if (result == DialogResult.Retry)
                    {
                        Invoke(new EventHandler(guiradbtnSearch_Click));
                    }
                }
            }
            catch (Exception ex)
            {
                GUIExceptionHandler.HandleException(ex, this);
            }
        }

        /** This method is used to fill the months and year into the combo box in the GUI.It is called on the FormLoad event.
                */
        private void FillMonthAndYear()
        {
            try
            {
                // list of Month to be fetched from resource file.Need to decide which resource file.
                if (!guicmbxMonth.Items.Equals(oMsgMgr.GetMessage(CrxStructCommonResourceMsg.Month)))
                {                    
                    guicmbxMonth.Items.Clear();
                    guicmbxMonth.SelectedIndex = Convert.ToInt32(GuiCommon.NumericValue.Zero);
                    guicmbxMonth.Items.Add(oMsgMgr.GetMessage(CrxStructCommonResourceMsg.Month));
                    guicmbxMonth.Items.Add(oMsgMgr.GetMessage(CrxStructCommonResourceMsg.GuiMonthJan));
                    guicmbxMonth.Items.Add(oMsgMgr.GetMessage(CrxStructCommonResourceMsg.GuiMonthFeb));
                    guicmbxMonth.Items.Add(oMsgMgr.GetMessage(CrxStructCommonResourceMsg.GuiMonthMar));
                    guicmbxMonth.Items.Add(oMsgMgr.GetMessage(CrxStructCommonResourceMsg.GuiMonthApr));
                    guicmbxMonth.Items.Add(oMsgMgr.GetMessage(CrxStructCommonResourceMsg.GuiMonthMay));
                    guicmbxMonth.Items.Add(oMsgMgr.GetMessage(CrxStructCommonResourceMsg.GuiMonthJun));
                    guicmbxMonth.Items.Add(oMsgMgr.GetMessage(CrxStructCommonResourceMsg.GuiMonthJul));
                    guicmbxMonth.Items.Add(oMsgMgr.GetMessage(CrxStructCommonResourceMsg.GuiMonthAug));
                    guicmbxMonth.Items.Add(oMsgMgr.GetMessage(CrxStructCommonResourceMsg.GuiMonthSep));
                    guicmbxMonth.Items.Add(oMsgMgr.GetMessage(CrxStructCommonResourceMsg.GuiMonthOct));
                    guicmbxMonth.Items.Add(oMsgMgr.GetMessage(CrxStructCommonResourceMsg.GuiMonthNov));
                    guicmbxMonth.Items.Add(oMsgMgr.GetMessage(CrxStructCommonResourceMsg.GuiMonthDec));
                    guicmbxMonth.SelectedIndex = Convert.ToInt32(GuiCommon.NumericValue.Zero);                                     
                }

                guicmbxYear.Items.Clear();                

                if (!guicmbxYear.Items.Equals(oMsgMgr.GetMessage(CrxStructCommonResourceMsg.Year)))
                {
                    guicmbxYear.Items.Add(oMsgMgr.GetMessage(CrxStructCommonResourceMsg.Year));                    
                }

                RadListDataItem yr;

                // reads min year from app.config and binds the drop down
                for (int year = int.Parse(ConfigurationManager.AppSettings[GuiConstants.AppConfigParams.MinYearForDob.ToString()]); year <= DateTime.Now.Year; year++)
                {
                    yr = new RadListDataItem { Text = year.ToString(), Value = year };

                    guicmbxYear.Items.Add(yr);
                }
            }
            catch (Exception ex)
            {
               // GUIExceptionHandler.HandleException(ex, this);
                throw (ex);
            }
        }

        /** This method is used to fill days into the combo box in the GUI.It is called on the FormLoad event.
        */
        private void FillDay(int lastDay)
        {
            try
            {
                int selectedvaue = Convert.ToInt32(GuiCommon.NumericValue.Zero);

                // retrieve the selected index
                if (guicmbDay.SelectedIndex > Convert.ToInt32(GuiCommon.NumericValue.Zero))
                {
                    selectedvaue = guicmbDay.SelectedIndex;
                }

                // clear items in combo box
                guicmbDay.Items.Clear();

                // set to 31 if lastday is 0
                if (lastDay == Convert.ToInt32(GuiCommon.NumericValue.Zero))
                {
                    lastDay = 31;
                }

                guicmbDay.Items.Add(oMsgMgr.GetMessage(CrxStructCommonResourceMsg.Day));

                // Fill day dropdown.
                for (int day = Convert.ToInt32(GuiCommon.NumericValue.One); day <= lastDay; day++)
                {
                    guicmbDay.Items.Add(day.ToString());
                }              

                // in case last day is less than previous selected value in combo box, set selected index to last day
                guicmbDay.SelectedIndex = selectedvaue > lastDay ? lastDay : selectedvaue;
            }
            catch (Exception ex)
            {
               // GUIExceptionHandler.HandleException(ex, this);
                throw (ex);
            }
        }      

        /** This method Bind days for month as per month selected in drop down
         */
        private void BindDaysForMonthSelected()
        {
            try
            {
                string selectedMonth = guicmbxMonth.Text;

                // fetches days for a month according to month selected
                DaysInMonth methodName = guicmbxMonth.Text.Equals(oMsgMgr.GetMessage(CrxStructCommonResourceMsg.GuiMonthFeb), StringComparison.CurrentCultureIgnoreCase) ? DaysInMonth.LeapYear : (guicmbxMonth.Text.Equals(oMsgMgr.GetMessage(CrxStructCommonResourceMsg.GuiMonthApr), StringComparison.CurrentCultureIgnoreCase) || guicmbxMonth.Text.Equals(oMsgMgr.GetMessage(CrxStructCommonResourceMsg.GuiMonthJun), StringComparison.CurrentCultureIgnoreCase) || guicmbxMonth.Text.Equals(oMsgMgr.GetMessage(CrxStructCommonResourceMsg.GuiMonthSep), StringComparison.CurrentCultureIgnoreCase) || guicmbxMonth.Text.Equals(oMsgMgr.GetMessage(CrxStructCommonResourceMsg.GuiMonthNov), StringComparison.CurrentCultureIgnoreCase)) ? DaysInMonth.Days30 : DaysInMonth.Days31;
                switch (methodName)
                {
                    case DaysInMonth.LeapYear:
                        FillDayLeapYear();
                        break;
                    case DaysInMonth.Days30:
                        FillDay(30);
                        break;
                    case DaysInMonth.Days31:
                        FillDay(31);
                        break;
                    default:
                        break;
                }
            }
            catch (Exception ex)
            {
               throw (ex);
            }
        }      

        /** This method is called to check if a year is leap year,if so accordingly the combobox values for the Months and Day are changed.
        */
        private void FillDayLeapYear()
        {
            try
            {
                // checks if year selected is leap year and calls fillday method to bind days
                if (guicmbxYear.SelectedIndex > Convert.ToInt32(GuiCommon.NumericValue.Zero))
                {
                   FillDay(DateTime.IsLeapYear(int.Parse(guicmbxYear.SelectedItem.Text)) ? 29 : 28);
                }
                else
                {
                    FillDay(28);
                }
            }
            catch (Exception ex)
            {
               // GUIExceptionHandler.HandleException(ex, this);
                throw (ex);
            }
        }

        /** This method is called to reset the dempgraphic data fields in the GUI
         */
        private void ResetFields()
        {
            try
            {
                // to reset all input fields            
                guiradtxtPatientID.Text = string.Empty;
                guiradtxtLastName.Text = string.Empty;
                guiradtxtFirstName.Text = string.Empty;
                guicmbDay.SelectedIndex = Convert.ToInt32(GuiCommon.NumericValue.Zero);
                guicmbGroup.DataSource = null;
                guicmbGroup.Items.Clear();
                LoadGroupNames();
                guicmbxGender.SelectedIndex = Convert.ToInt32(GuiCommon.NumericValue.Zero);
                guicmbxMonth.SelectedIndex = Convert.ToInt32(GuiCommon.NumericValue.Zero);
                guicmbxYear.SelectedIndex = Convert.ToInt32(GuiCommon.NumericValue.Zero);
            }
            catch (Exception ex)
            {
                throw (ex);
            }
        }

        /**This method is called to validate the demographic details entered by the user.
         */
        private bool ValidateDemographicDetails()
        {
            try
            {
                // validates mandatory demographic fields
                bool flag = true;

                if (guiradtxtLastName.Text.Trim().CompareTo(string.Empty) == Convert.ToInt32(GuiCommon.NumericValue.Zero))
                {
                    flag = false;
                    RadMessageBox.Show(oMsgMgr.GetMessage(CrxStructCommonResourceMsg.EnterLastName), oMsgMgr.GetMessage(CrxStructCommonResourceMsg.SystemError), MessageBoxButtons.OK);
                }
                else if (guicmbDay.SelectedIndex == Convert.ToInt32(GuiCommon.NumericValue.Zero) || guicmbxMonth.SelectedIndex == Convert.ToInt32(GuiCommon.NumericValue.Zero) || guicmbxYear.SelectedIndex == Convert.ToInt32(GuiCommon.NumericValue.Zero))
                {
                    flag = false;
                    RadMessageBox.Show(oMsgMgr.GetMessage(CrxStructCommonResourceMsg.SelectDob), oMsgMgr.GetMessage(CrxStructCommonResourceMsg.SystemError), MessageBoxButtons.OK);
                }
                else if (guicmbxGender.SelectedIndex == Convert.ToInt32(GuiCommon.NumericValue.Zero))
                {
                    flag = false;
                    RadMessageBox.Show(oMsgMgr.GetMessage(CrxStructCommonResourceMsg.SelectGender), oMsgMgr.GetMessage(CrxStructCommonResourceMsg.SystemError), MessageBoxButtons.OK);
                }
                else
                {
                    string dob = string.Format("{0}/{1}/{2}", guicmbDay.Text, guicmbxMonth.Text, guicmbxYear.Text);
                    DateTime dob1 = Convert.ToDateTime(dob, culture);
                    string tempText = DateTime.Now.ToString(culture);
                    DateTime sysDate = Convert.ToDateTime(tempText, culture);
                    if (dob1 > sysDate)
                    {
                        flag = false;
                        RadMessageBox.Show(oMsgMgr.GetMessage(CrxStructCommonResourceMsg.BirthDateCannotBeFutureDate), oMsgMgr.GetMessage(CrxStructCommonResourceMsg.SystemError), MessageBoxButtons.OK);                       
                    }              
                }

                GuiCommon.IsMenuItemShown = flag;
                GuiCommon.ExitApp = flag ? Convert.ToInt32(GuiCommon.NumericValue.Zero) : Convert.ToInt32(GuiCommon.NumericValue.One);
                return flag;
            }
            catch (Exception ex)
            {
               // GUIExceptionHandler.HandleException(ex, this);
                return false;
                throw (ex);
            }
        }

        /**This event is called when the user clicks on the Edit button in the GUI.The user can now edit th demographic details of the selected patient.
        */
        private void guiradbtnEdit_Click(object sender, EventArgs e)
        {
            try
            {
                isSearchOn = false;
                mode = CurrentMode.EditMode;
                BrowseMode(false);
                objDefaultWindow.radlblMessage.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.EditMode);

                guiradgrdPatientList.Enabled = false;
                HideMeasurementPanelDependingOnMode();
                objDefaultWindow.guicmbxCurrentMode.Enabled = false;

                // disable capture & report tab in edit mode
                objDefaultWindow.radtabReport.Enabled = false;
                objDefaultWindow.radtabCapture.Enabled = false;
                objDefaultWindow.radtabQuickStart.Enabled = false;
                GuiCommon.IsFormChanged = true;

                // set the focus to the Patient Id field.
                guiradtxtFirstName.Focus();
            }
            catch (Exception ex)
            {
                GUIExceptionHandler.HandleException(ex, this);
            }
        }

        /** This method is called when a user selects a record from the patient list and clicks on Delete button. The user is asked for the confirmation whether he wants to delete the record.If yes the record is deleted from the database.
         */
        private void guiradbtnDelete_Click(object sender, EventArgs e)
        {
            try
            {
                isSearchOn = false;               
                CrxStructPatientDemographicData patientDemographicData = new CrxStructPatientDemographicData();
                
                GridViewRowInfo row = guiradgrdPatientList.CurrentRow;
                patientDemographicData.PatientNumberInternal = int.Parse(row.Cells[1].Value.ToString());
                patientDemographicData.GroupIdentifier = int.Parse(row.Cells[2].Value.ToString());
                patientDemographicData.SystemIdentifier = bobj;

                DialogResult ds = RadMessageBox.Show(this, oMsgMgr.GetMessage(CrxStructCommonResourceMsg.DeletePateint), oMsgMgr.GetMessage(CrxStructCommonResourceMsg.SystemError), MessageBoxButtons.YesNo, RadMessageIcon.Question);

                if (ds == DialogResult.Yes)
                {
                    if (dbMagr.CheckConnection(serverNameString, crxMgrObject.GeneralSettings.SourceData) == Convert.ToInt32(GuiCommon.NumericValue.Zero))
                    {
                        dbMagr.DeletePatientData(patientDemographicData);

                        // refresh the db.            
                        LoadPatientList();
                    }
                    else
                    {
                        DialogResult result = RadMessageBox.Show(this, GuiCommon.ConnectionErrorString(), oMsgMgr.GetMessage(CrxStructCommonResourceMsg.SystemError), MessageBoxButtons.RetryCancel, RadMessageIcon.Error);
                        if (result == DialogResult.Retry)
                        {
                            // retry deleting patient details again
                            dbMagr.DeletePatientData(patientDemographicData);

                            // refresh the db.            
                            LoadPatientList();
                        }
                    }
                }
            }
            catch (Exception ex)
            {
                GUIExceptionHandler.HandleException(ex, this);
            }
        }

        /** This event gets fired when focus is moved from text box which takes cuff or direct values.
      * It checks if the value entered in textbox is within valid range and shows error accordingly
      */
        private void guiradtxtCuff_Leave(object sender, EventArgs e)
        {
            try
            {
                objValidation.CheckFieldLimits(guiradtxtCuff);
                EnableCaptureAndCalculatePwvDistance();
            }
            catch (Exception ex)
            {
                GUIExceptionHandler.HandleException(ex, this);
            }
        }

        /** This method is called to calculate the PWV distance.
         */
        private void EnableCaptureAndCalculatePwvDistance()
        {
            // Clearing the PWV distance so that previous calculated distance is not seen,if any of the current fields are blank.
            guiradlblResult.Text = string.Empty;
            try
            {
                if (crxMgrObject.PwvSettings.PWVDistanceMethod.Equals((int)CrxGenPwvValue.CrxPwvDistMethodSubtract) && guiradtxtCarotid.Text.Length > 0 && guiradtxtCuff.Text.Length > 0 && guiradtxtFemoralToCuff.Text.Length > 0)
                {
                    guiradlblResult.Text = (int.Parse(guiradtxtCuff.Text.Trim()) - int.Parse(guiradtxtCarotid.Text.Trim()) - int.Parse(guiradtxtFemoralToCuff.Text.Trim())).ToString();                  
                }

                if (crxMgrObject.PwvSettings.PWVDistanceMethod.Equals((int)CrxGenPwvValue.CrxPwvDistMethodDirect) && guiradtxtCuff.Text.Length > 0 && guiradtxtFemoralToCuff.Text.Length > 0)
                {
                    guiradlblResult.Text = (int.Parse(guiradtxtCuff.Text.Trim()) - int.Parse(guiradtxtFemoralToCuff.Text.Trim())).ToString();
                }
            }
            catch (Exception ex)
            {
               // GUIExceptionHandler.HandleException(ex, this);
                throw (ex);
            }
        }

        /** This event gets fired when focus is moved from text box which takes carotid.
         *  It checks if the value entered in textbox is within valid range and shows error accordingly
         */
        private void guiradtxtCarotid_Leave(object sender, EventArgs e)
        {
            try
            {
                objValidation.CheckFieldLimits(guiradtxtCarotid);
                EnableCaptureAndCalculatePwvDistance();
            }
            catch (Exception ex)
            {
                GUIExceptionHandler.HandleException(ex, this);
            }
        }

        /** This event gets fired when focus is moved from text box which takes femoral.
         *  It checks if the value entered in textbox is within valid range and shows error accordingly
         */
        private void guiradtxtFemoralToCuff_Leave(object sender, EventArgs e)
        {
            try
            {
                objValidation.CheckFieldLimits(guiradtxtFemoralToCuff);
                EnableCaptureAndCalculatePwvDistance();
            }
            catch (Exception ex)
            {
                GUIExceptionHandler.HandleException(ex, this);
            }
        }

        /** This event is fire when the user clicks on the Cancel button in the GUI.
         */
        private void guiradbtnCancel_Click(object sender, EventArgs e)
        {
            try
            {
                isSearchOn = false;
                
                // returns the screen to browse mode
                guiradbtnCapture.Visible = true;                              
                guiradgrdPatientList.Enabled = true;

                // added for regression defect
                objDefaultWindow.guicmbxCurrentMode.Enabled = true;
                objDefaultWindow.radlblMessage.Text = string.Empty;

                GuiCommon.IsFormChanged = false;
                if (mode == CurrentMode.InsertMode)
                {
                    LoadPatientList();
                }
                else if (mode == CurrentMode.EditMode)
                {
                    int patientIdInternal = int.Parse(radlblpatientinternalnumber.Text);
                    int groupId = int.Parse(radlblgroupid.Text);
                    if (prevMode == CurrentMode.SearchMode)
                    {
                        LoadPatientList();
                    }
                    else
                    {
                        mode = CurrentMode.None;
                        DisplayLastRecord(patientIdInternal, groupId);
                        GridViewRowInfo lastRow = guiradgrdPatientList.Rows[guiradgrdPatientList.Rows.Count - 1];
                        lastRow.IsCurrent = true;
                        lastRow.IsSelected = true;    
                    }                    
                }
                else
                {
                    // reset mode to none
                    mode = CurrentMode.None;
                    LoadPatientList();
                }

                prevMode = mode;
                mode = CurrentMode.None;
                BrowseMode(true);

                // disable capture & enable / disable  report tab based on measurement details
               // objDefaultWindow.radtabReport.Enabled = GuiCommon.HasMeasurementDetails;

                // below line of code enables capture tab based on 30 sec wait interval imposed by EM4
                // if IsWaitIntervalImposed is true then disable capture button & vice versa
                if (GuiCommon.CurrentMode.Equals(CrxStructCommonResourceMsg.Pwv))
                {
                    objDefaultWindow.radtabCapture.Enabled = !GuiCommon.IsWaitIntervalImposed;
                }
            }
            catch (Exception ex)
            {
                GUIExceptionHandler.HandleException(ex, this);
            }
        }

        /** This method is called when the Serach result is to be bound with the grid view.
        */
        private void BindSearchResults(string patientId, string lastName, string firstName, string gender, string dateOfBirth, string groupName)
        {
            try
            {
                // retrieves data from APPdomain cache, filters as per search criteria and binds it to the grid
                isSearchOn = true;

                /** "cachePatient" for internal use only
                 * will give search results from the cache of patients
                 */
                DataSet dsSearch = (DataSet)AppDomain.CurrentDomain.GetData("cachePatient");
                if (dsSearch.Tables[0].Rows.Count > Convert.ToInt32(GuiCommon.NumericValue.Zero))
                {
                    // creates a dataview for filtering records
                    DataView dvSearch = dsSearch.Tables[0].DefaultView;

                    string searchString;

                    // formulates search string based on criterias given
                    // this is a search query which will filter cached records based on the search parameters supplied
                    // it uses column names for internal use
                    if (!string.IsNullOrEmpty(dateOfBirth))
                    {
                        searchString = "PatientIDExternalReference like '" + patientId + "%' and LastName like '" + lastName + "%' and FirstName like '" + firstName + "%' and Gender like '" + gender + "%' and " + string.Format(new CultureInfo(CultureInfo.CurrentCulture.Name).DateTimeFormat, "dateofbirth = #{0:d}#", DateTime.Parse(dateOfBirth)); // and GroupName like '" + groupName + "%'
                    }
                    else
                    {
                        searchString = "PatientIDExternalReference like '" + patientId + "%' and LastName like '" + lastName + "%' and FirstName like '" + firstName + "%' and Gender like '" + gender + "%'"; // and GroupName like '" + groupName + "%'
                    }

                    // filters record and binds to grid
                    dvSearch.RowFilter = searchString;

                    guiradgrdPatientList.DataSource = dvSearch;

                    // Assignes count of total no of patient searched. 
                    guiradlblNumberOfPatients.Text = dvSearch.Count.ToString();
                    if (dvSearch.Count == Convert.ToInt32(GuiCommon.NumericValue.One))
                    {
                        prevMode = CurrentMode.SearchMode;
                        mode = CurrentMode.None;
                        DisplayLastRecord(int.Parse(guiradgrdPatientList.Rows[0].Cells[1].Value.ToString()), int.Parse(guiradgrdPatientList.Rows[0].Cells[2].Value.ToString()));
                        guiradbtnSearch.Enabled = true;
                        guiradbtnCancel.Enabled = true;
                    }
                    else if (dvSearch.Count > Convert.ToInt32(GuiCommon.NumericValue.One))
                    {
                        foreach (GridViewRowInfo row in guiradgrdPatientList.Rows)
                        {
                            row.IsSelected = false;
                            row.IsCurrent = false;
                        }
                    }                                        
                }
            }
            catch (Exception ex)
            {
               // GUIExceptionHandler.HandleException(ex, this);
                throw (ex);
            }
        }

        /** This event is fired on the text changed of the PatientId field.
         */
        private void guiradtxtPatientID_TextChanged(object sender, EventArgs e)
        {
            try
            {
                // gets patient records based on inputs given
                if (!IsFieldsBlank(false) && mode == CurrentMode.SearchMode)
                {
                    GetSearchResults();
                }

                if (mode == CurrentMode.EditMode || (guiradtxtPatientID.Text != string.Empty && mode == CurrentMode.InsertMode))
                {
                    isValueChanged = true;
                }
                else
                {
                    isValueChanged = false;
                }

                guilblPatientIdDisplay.Text = guiradtxtPatientID.Text;
            }
            catch (Exception ex)
            {
                GUIExceptionHandler.HandleException(ex, this);
            }         
        }

        /** This method gets filtered search result & binds it to grid view.
        */
        private void GetSearchResults()
        {
            try
            {
                string dob = string.Empty, gender = string.Empty, groupname = string.Empty;

                // get date of birth value
                if (guicmbDay.SelectedIndex > Convert.ToInt32(GuiCommon.NumericValue.Zero) && guicmbxMonth.SelectedIndex > Convert.ToInt32(GuiCommon.NumericValue.Zero) && guicmbxYear.SelectedIndex > Convert.ToInt32(GuiCommon.NumericValue.Zero))
                {                   
                    dob = string.Format("{0}/{1}/{2}", guicmbDay.SelectedItem, guicmbxMonth.SelectedItem, guicmbxYear.SelectedItem);
                }

                // get selected item from gender drop down
                if (!string.IsNullOrEmpty(guicmbxGender.Text.Trim()) && !guicmbxGender.Text.Trim().ToLower().Contains(oMsgMgr.GetMessage(CrxStructCommonResourceMsg.SelectSmall)))
                {                   
                    gender = guicmbxGender.Text.Trim().Equals(oMsgMgr.GetMessage(CrxStructCommonResourceMsg.MaleTxt)) ? CrxStructCommonResourceMsg.MaleTxt : CrxStructCommonResourceMsg.FemaleTxt;
                }
                else if (guicmbxGender.SelectedIndex > Convert.ToInt32(GuiCommon.NumericValue.Zero))
                {
                    gender = guicmbxGender.SelectedItem.ToString().Trim().Equals(oMsgMgr.GetMessage(CrxStructCommonResourceMsg.MaleTxt)) ? CrxStructCommonResourceMsg.MaleTxt : CrxStructCommonResourceMsg.FemaleTxt;
                }

                // binds search results to grid
                BindSearchResults(guiradtxtPatientID.Text.Trim(), guiradtxtLastName.Text.Trim(), guiradtxtFirstName.Text.Trim(), gender, dob, groupname);
            }
            catch (Exception ex)
            {
               // GUIExceptionHandler.HandleException(ex, this);
                throw (ex);
            }
        }

        /** This event is fired on the cell click of the PateintListGrid view.
        */
        private void guiradgrdPatientList_CellClick(object sender, GridViewCellEventArgs e)
        {
            try
            {               
                // gets the selected row patientinternal number and fills demographic details area
                if (guiradgrdPatientList.CurrentRow != null)
                {
                    isSearchReset = true;
                    GridViewRowInfo row = guiradgrdPatientList.CurrentRow;
                    mode = CurrentMode.None;
                    guiradbtnNew.Enabled = true;
                    radlblpatientinternalnumber.Text = row.Cells[1].Value.ToString();
                    radlblgroupid.Text = row.Cells[2].Value.ToString();
                    DisplayLastRecord(int.Parse(row.Cells[1].Value.ToString()), int.Parse(radlblgroupid.Text));
                }
            }
            catch (Exception ex)
            {
                GUIExceptionHandler.HandleException(ex, this);
            }
        }

        /** This event is fired on the text changed of the FirstName field.
        */
        private void guiradtxtFirstName_TextChanged(object sender, EventArgs e)
        {
            try
            {
                // gets patient records based on inputs given for first name
                if (!IsFieldsBlank(false) && mode == CurrentMode.SearchMode)
                {
                    GetSearchResults();
                }

                if (mode == CurrentMode.EditMode || (guiradtxtFirstName.Text != string.Empty && mode == CurrentMode.InsertMode))
                {
                    isValueChanged = true;
                }
                else
                {
                    isValueChanged = false;
                }

                guilblFirstnameDisplay.Text = guiradtxtFirstName.Text;

                if (guilblFirstnameDisplay.Text.Length > 10)
                {
                    guilblFirstnameDisplay.Text = guilblFirstnameDisplay.Text.Substring(Convert.ToInt32(GuiCommon.NumericValue.Zero), Convert.ToInt32(GuiCommon.NumericValue.Ten));
                    guilblFirstnameDisplay.Text = string.Format("{0}...", guilblFirstnameDisplay.Text);
                }
            }
            catch (Exception ex)
            {
                GUIExceptionHandler.HandleException(ex, this);
            }
        }      

        /** This event is fired on the text changed of the LastName field.
         */
        private void guiradtxtLastName_TextChanged(object sender, EventArgs e)
        {
            try
            {
                // gets patient records based on inputs given for last name
                if (!IsFieldsBlank(true) && mode == CurrentMode.SearchMode)
                {
                    GetSearchResults();
                }

                if (mode == CurrentMode.EditMode || (guiradtxtLastName.Text != string.Empty && mode == CurrentMode.InsertMode))
                {
                    isValueChanged = true;
                }
                else
                {
                    isValueChanged = false;
                }

                guilblLastNameDisplay.Text = guiradtxtLastName.Text;

                if (guilblLastNameDisplay.Text.Length > Convert.ToInt32(GuiCommon.NumericValue.Ten))
                {
                    guilblLastNameDisplay.Text = guilblLastNameDisplay.Text.Substring(Convert.ToInt32(GuiCommon.NumericValue.Zero), Convert.ToInt32(GuiCommon.NumericValue.Ten));
                    guilblLastNameDisplay.Text = string.Format("{0}...", guilblLastNameDisplay.Text);
                }
            }
            catch (Exception ex)
            {
                GUIExceptionHandler.HandleException(ex, this);
            }
        }

        /** This method is used to check if a field is blank or no while fetching search results.
        */
        private bool IsFieldsBlank(bool mandatory)
        {
            try
            {
                bool flag = true;

                // sets flag according to mandatory fields required 
                if (!isSearchReset)
                {
                    flag = mandatory && CheckForMandatoryFields();
                }

                return flag;
            }
            catch (Exception ex)
            {
                throw (ex);
            }
        }

        /** This method checks for mandatory fields for patient demographic details and accordingly returns value
         */
        private bool CheckForMandatoryFields()
        {
            try
            {
                bool flag;
                if (guicmbDay.SelectedIndex > Convert.ToInt32(GuiCommon.NumericValue.Zero) && guicmbxMonth.SelectedIndex > Convert.ToInt32(GuiCommon.NumericValue.Zero) && guicmbxYear.SelectedIndex > Convert.ToInt32(GuiCommon.NumericValue.Zero))
                {
                    flag = !string.IsNullOrEmpty(guiradtxtLastName.Text.Trim()) ? false : (guicmbDay.SelectedIndex > Convert.ToInt32(GuiCommon.NumericValue.Zero) && guicmbxMonth.SelectedIndex > Convert.ToInt32(GuiCommon.NumericValue.Zero) && guicmbxYear.SelectedIndex > Convert.ToInt32(GuiCommon.NumericValue.Zero)) ? false : guicmbxGender.SelectedIndex > Convert.ToInt32(GuiCommon.NumericValue.Zero) ? false : true;
                }
                else
                {
                    flag = false;
                }

                return flag;
            }
            catch (Exception ex)
            {
                throw (ex);
            }
        }

        /** This event is fired when the user tries to change the width of the column of the grid view.
          */
        private void guiradgrdPatientList_ColumnWidthChanging(object sender, ColumnWidthChangingEventArgs e)
        {
            try
            {
                // cancels changing column width
                if (!isCellInitializeWidth)
                {
                    e.Cancel = true;
                }
            }
            catch (Exception ex)
            {
                GUIExceptionHandler.HandleException(ex, this);
            }
        }

        /** This event is fired when the user tries to right click on the grid view.
       */
        private void guiradgrdPatientList_ContextMenuOpening(object sender, ContextMenuOpeningEventArgs e)
        {
            try
            {
                // suppresses context menu appearing after right click on grid view header
                e.Cancel = true;
            }
            catch (Exception ex)
            {
                GUIExceptionHandler.HandleException(ex, this);
            }
        }

        /** This event is fired when the user tries to change the height of the row of the grid view.
         */
        private void guiradgrdPatientList_RowHeightChanging(object sender, RowHeightChangingEventArgs e)
        {
            try
            {
                // cancels changing row height
                e.Cancel = true;
            }
            catch (Exception ex)
            {
                GUIExceptionHandler.HandleException(ex, this);
            }
        }

        /** This method is used to populate the session object with the database values.
        */
        private void FillSessionObjFromDB()
        {
            try
            {
                // check db connection
                if (dbMagr.CheckConnection(serverNameString, crxMgrObject.GeneralSettings.SourceData) == Convert.ToInt32(GuiCommon.NumericValue.Zero))
                {
                    // fetch measurement details for patient & populate Biz session object
                    GuiCommon.ScorControllerObject.FillSession();
                }
                else
                {
                    DialogResult result = RadMessageBox.Show(this, GuiCommon.ConnectionErrorString(), oMsgMgr.GetMessage(CrxStructCommonResourceMsg.SystemError), MessageBoxButtons.RetryCancel, RadMessageIcon.Error);
                    if (result == DialogResult.Retry)
                    {
                        FillSessionObjFromDB();
                    }
                }
            }
            catch (Exception ex)
            {
                throw (ex);
            }
        }
       
        /** This method is used calculate the metric conversion for height.
        */ 
        private void PerformHeightMetricConversion(ref int heightInCentiConversion)
        {
            try
            {
                heightInCentiConversion = GuiCommon.bizObject.heightAndWeight.heightInCentimetres.ToString().Equals(GuiConstants.DefaultValue.ToString()) ? Convert.ToInt32(GuiCommon.NumericValue.Zero) : int.Parse(GuiCommon.bizObject.heightAndWeight.heightInCentimetres.ToString());
            }
            catch (Exception ex)
            {
                throw (ex);
            }
        }

        /** This method is used calculate the Imperial conversion for height.
       */
        private void PerformHeightImperialConversion(ref int heightInFeetConversion, ref int heightInInchConversion)
        {
            try
            {
                heightInInchConversion = int.Parse(GuiCommon.bizObject.heightAndWeight.heightInInches.ToString()) % Convert.ToInt32(GuiCommon.NumericValue.Twelve);
                heightInFeetConversion = int.Parse(GuiCommon.bizObject.heightAndWeight.heightInInches.ToString()) / Convert.ToInt32(GuiCommon.NumericValue.Twelve);
            }
            catch (Exception ex)
            {
                throw (ex);
            }
        }

        /** This method is used calculate the metric conversion for height for pwa mode.
       */
        private void PerformPwaHeightMetricConversion(ref int heightInCentiConversion)
        {
            try
            {
                heightInCentiConversion = GuiCommon.bizPwaobject.heightAndWeight.heightInCentimetres.ToString().Equals(GuiConstants.DefaultValue.ToString()) ? Convert.ToInt32(GuiCommon.NumericValue.Zero) : int.Parse(GuiCommon.bizPwaobject.heightAndWeight.heightInCentimetres.ToString());
            }
            catch (Exception ex)
            {
                throw (ex);
            }
        }

        /** This method is used calculate the Imperial conversion for height for pwa mode.
       */
        private void PerformPwaHeightImperialConversion(ref int heightInFeetConversion, ref int heightInInchConversion)
        {
            try
            {
                heightInInchConversion = int.Parse(GuiCommon.bizPwaobject.heightAndWeight.heightInInches.ToString()) % Convert.ToInt32(GuiCommon.NumericValue.Twelve);
                heightInFeetConversion = int.Parse(GuiCommon.bizPwaobject.heightAndWeight.heightInInches.ToString()) / Convert.ToInt32(GuiCommon.NumericValue.Twelve);
            }
            catch (Exception ex)
            {
                throw (ex);
            }
        }
 
        /** This method initializes biz session object each time a patient record is selected/edited/added for pwv mode
        */
        private void FillSessionData(DataSet dsPwv)
        {
            try
            {
                FillSessionWithBloodPressureValues(dsPwv);
                FillSessionWithOtherValues(dsPwv);

                GuiCommon.bizObject.systemId = (uint)bobj;
                GuiCommon.bizObject.groupStudyId = (uint)GuiCommon.GroupId;

                objDefaultWindow.radtabReport.Enabled = true;
                objDefaultWindow.radtabCapture.Enabled = !GuiCommon.IsWaitIntervalImposed;
                GuiCommon.bizObject.patientNumber = (uint)GuiCommon.PatientInternalNumber;
            }
            catch (Exception ex)
            {
                throw (ex);
            }
        }

        /** This method initializes biz session object each time a patient record is selected/edited/added for pwa mode
        */      
        private void FillPwaSessionData(DataSet dsPwv)
        {
            try
            {
                FillPwaSessionWithOtherValues(dsPwv);

                if (!(GuiCommon.CurrentMode.Equals(CrxStructCommonResourceMsg.Pwa) && objDefaultWindow.guiradgrpbxPwvDistanceMethod.Text.Equals(oMsgMgr.GetMessage(CrxStructCommonResourceMsg.TabPatient))))
                {
                    FillPwaSessionWithBloodPressureValues(dsPwv);
                }

                GuiCommon.bizPwaobject.systemId = (uint)bobj;
                GuiCommon.bizPwaobject.groupStudyId = (uint)GuiCommon.GroupId;

                // THis is checked so that when the user is in quickstart mode and 
                // after doing a capture comes to the Patient  screen then, the Report tab should be 
                // disabled till the user has geenrated a report.
                if (!(GuiCommon.IsReportGenerated || GuiCommon.FromQuickStart) && objDefaultWindow.guiradgrpbxPwvDistanceMethod.Text.Equals(oMsgMgr.GetMessage(CrxStructCommonResourceMsg.TabPatient)))
                {
                    objDefaultWindow.radtabReport.Enabled = false;
                }
                else
                {
                    objDefaultWindow.radtabReport.Enabled = true;
                }
                GuiCommon.bizPwaobject.patientNumber = (uint)GuiCommon.PatientInternalNumber;
            }
            catch (Exception ex)
            {
                throw (ex);
            }
        }

        /** This method fills session with height & weight, distance values for pwa mode
         */
        private void FillPwaSessionWithOtherValues(DataSet dsPwv)
        {
            try
            {
                GuiCommon.bizPwaobject.heightAndWeight.heightInCentimetres = string.IsNullOrEmpty(dsPwv.Tables[0].Rows[0][(int)CrxDBGetCuffPWAMeasurementDetails.HeightInCentimetres].ToString()) ? GuiCommon.bizPwaobject.heightAndWeight.heightInCentimetres : ushort.Parse(dsPwv.Tables[0].Rows[0][(int)CrxDBGetCuffPWAMeasurementDetails.HeightInCentimetres].ToString());
                GuiCommon.bizPwaobject.heightAndWeight.heightInInches = string.IsNullOrEmpty(dsPwv.Tables[0].Rows[0][(int)CrxDBGetCuffPWAMeasurementDetails.HeightInInches].ToString()) ? GuiCommon.bizPwaobject.heightAndWeight.heightInInches : ushort.Parse(dsPwv.Tables[0].Rows[0][(int)CrxDBGetCuffPWAMeasurementDetails.HeightInInches].ToString());
                GuiCommon.bizPwaobject.heightAndWeight.weightInKilograms = string.IsNullOrEmpty(dsPwv.Tables[0].Rows[0][(int)CrxDBGetCuffPWAMeasurementDetails.WeightInKilograms].ToString()) ? GuiCommon.bizPwaobject.heightAndWeight.weightInKilograms : ushort.Parse(dsPwv.Tables[0].Rows[0][(int)CrxDBGetCuffPWAMeasurementDetails.WeightInKilograms].ToString());
                GuiCommon.bizPwaobject.heightAndWeight.weightInPounds = string.IsNullOrEmpty(dsPwv.Tables[0].Rows[0][(int)CrxDBGetCuffPWAMeasurementDetails.WeightInPounds].ToString()) ? GuiCommon.bizPwaobject.heightAndWeight.weightInPounds : ushort.Parse(dsPwv.Tables[0].Rows[0][(int)CrxDBGetCuffPWAMeasurementDetails.WeightInPounds].ToString());
                GuiCommon.bizPwaobject.notes = dsPwv.Tables[0].Rows[0][(int)CrxDBGetCuffPWAMeasurementDetails.Notes].ToString();
                GuiCommon.bizPwaobject.operatorId = dsPwv.Tables[0].Rows[0][(int)CrxDBGetCuffPWAMeasurementDetails.Operator].ToString();
                GuiCommon.bizPwaobject.heightAndWeight.bodyMassIndex = string.IsNullOrEmpty(dsPwv.Tables[0].Rows[0][(int)CrxDBGetCuffPWAMeasurementDetails.BodyMassIndex].ToString()) ? 0 : float.Parse(dsPwv.Tables[0].Rows[0][(int)CrxDBGetCuffPWAMeasurementDetails.BodyMassIndex].ToString());
            }
            catch (Exception ex)
            {
                throw (ex);
            }
        }

        /** This method fills session with blood pressure values for pwa mode
         */
        private void FillPwaSessionWithBloodPressureValues(DataSet dsPwv)
        {
            try
            {
                GuiCommon.bizPwaobject.bloodPressureEntryOption = string.IsNullOrEmpty(dsPwv.Tables[0].Rows[0][(int)CrxDBGetCuffPWAMeasurementDetails.BloodPressureEntryOption].ToString()) ? (ushort)0 : ushort.Parse(dsPwv.Tables[0].Rows[0][(int)CrxDBPWVMeasurementTableList.BloodPressureEntryOption].ToString());
                GuiCommon.bizPwaobject.bloodPressure.SP.Reading = ushort.Parse(dsPwv.Tables[0].Rows[0][(int)CrxDBGetCuffPWAMeasurementDetails.SP].ToString());
                GuiCommon.bizPwaobject.bloodPressure.DP.Reading = ushort.Parse(dsPwv.Tables[0].Rows[0][(int)CrxDBGetCuffPWAMeasurementDetails.DP].ToString());
            }
            catch (Exception ex)
            {
                throw (ex);
            }
        }

        /** This method fills session with height & weight, distance values for pwv mode
         */
        private void FillSessionWithOtherValues(DataSet dsPwv)
        {
            try
            {
                GuiCommon.bizObject.calculatedDistance = string.IsNullOrEmpty(dsPwv.Tables[0].Rows[0][(int)CrxDBPWVMeasurementTableList.PWVDistance].ToString()) ? (ushort)0 : ushort.Parse(dsPwv.Tables[0].Rows[0][(int)CrxDBPWVMeasurementTableList.PWVDistance].ToString());
                GuiCommon.bizObject.heightAndWeight.heightInCentimetres = string.IsNullOrEmpty(dsPwv.Tables[0].Rows[0][(int)CrxDBPWVMeasurementTableList.HeightInCentimetres].ToString()) ? GuiCommon.bizObject.heightAndWeight.heightInCentimetres : ushort.Parse(dsPwv.Tables[0].Rows[0][(int)CrxDBPWVMeasurementTableList.HeightInCentimetres].ToString());
                GuiCommon.bizObject.heightAndWeight.heightInInches = string.IsNullOrEmpty(dsPwv.Tables[0].Rows[0][(int)CrxDBPWVMeasurementTableList.HeightInInches].ToString()) ? GuiCommon.bizObject.heightAndWeight.heightInInches : ushort.Parse(dsPwv.Tables[0].Rows[0][(int)CrxDBPWVMeasurementTableList.HeightInInches].ToString());
                GuiCommon.bizObject.heightAndWeight.weightInKilograms = string.IsNullOrEmpty(dsPwv.Tables[0].Rows[0][(int)CrxDBPWVMeasurementTableList.WeightInKilograms].ToString()) ? GuiCommon.bizObject.heightAndWeight.weightInKilograms : ushort.Parse(dsPwv.Tables[0].Rows[0][(int)CrxDBPWVMeasurementTableList.WeightInKilograms].ToString());
                GuiCommon.bizObject.heightAndWeight.weightInPounds = string.IsNullOrEmpty(dsPwv.Tables[0].Rows[0][(int)CrxDBPWVMeasurementTableList.WeightInPounds].ToString()) ? GuiCommon.bizObject.heightAndWeight.weightInPounds : ushort.Parse(dsPwv.Tables[0].Rows[0][(int)CrxDBPWVMeasurementTableList.WeightInPounds].ToString());
                GuiCommon.bizObject.notes = dsPwv.Tables[0].Rows[0][(int)CrxDBPWVMeasurementTableList.Notes].ToString();
                GuiCommon.bizObject.operatorId = dsPwv.Tables[0].Rows[0][(int)CrxDBPWVMeasurementTableList.Operator].ToString();
                GuiCommon.bizObject.myCarotidDistance.distance = string.IsNullOrEmpty(dsPwv.Tables[0].Rows[0][(int)CrxDBPWVMeasurementTableList.Carotid].ToString()) ? GuiCommon.bizObject.myCarotidDistance.distance : ushort.Parse(dsPwv.Tables[0].Rows[0][(int)CrxDBPWVMeasurementTableList.Carotid].ToString());
                GuiCommon.bizObject.myCuffDistance.distance = string.IsNullOrEmpty(dsPwv.Tables[0].Rows[0][(int)CrxDBPWVMeasurementTableList.Cuff].ToString()) ? GuiCommon.bizObject.myCuffDistance.distance : ushort.Parse(dsPwv.Tables[0].Rows[0][(int)CrxDBPWVMeasurementTableList.Cuff].ToString());
                GuiCommon.bizObject.myFemoral2CuffDistance.distance = string.IsNullOrEmpty(dsPwv.Tables[0].Rows[0][(int)CrxDBPWVMeasurementTableList.FemoraltoCuff].ToString()) ? GuiCommon.bizObject.myFemoral2CuffDistance.distance : ushort.Parse(dsPwv.Tables[0].Rows[0][(int)CrxDBPWVMeasurementTableList.FemoraltoCuff].ToString());
                GuiCommon.bizObject.myPWVDirectDistance.distance = string.IsNullOrEmpty(dsPwv.Tables[0].Rows[0][(int)CrxDBPWVMeasurementTableList.Direct].ToString()) ? GuiCommon.bizObject.myPWVDirectDistance.distance : ushort.Parse(dsPwv.Tables[0].Rows[0][(int)CrxDBPWVMeasurementTableList.Direct].ToString());
                GuiCommon.bizObject.heightAndWeight.bodyMassIndex = string.IsNullOrEmpty(dsPwv.Tables[0].Rows[0][(int)CrxDBPWVMeasurementTableList.BodyMassIndex].ToString()) ? 0 : float.Parse(dsPwv.Tables[0].Rows[0][(int)CrxDBPWVMeasurementTableList.BodyMassIndex].ToString());
                GuiCommon.bizObject.distanceMethod = ushort.Parse(dsPwv.Tables[0].Rows[0][(int)CrxDBPWVMeasurementTableList.PWVDistanceMethod].ToString());
            }
            catch (Exception ex)
            {
                throw (ex);
            }
        }

        /** This method fills session with blood pressure values for pwv mode
         */
        private void FillSessionWithBloodPressureValues(DataSet dsPwv)
        {
            try
            {
                GuiCommon.bizObject.bloodPressureEntryOption = string.IsNullOrEmpty(dsPwv.Tables[0].Rows[0][(int)CrxDBPWVMeasurementTableList.BloodPressureEntryOption].ToString()) ? (ushort)0 : ushort.Parse(dsPwv.Tables[0].Rows[0][(int)CrxDBPWVMeasurementTableList.BloodPressureEntryOption].ToString());
                GuiCommon.bizObject.bloodPressure.SP.Reading = ushort.Parse(dsPwv.Tables[0].Rows[0][(int)CrxDBPWVMeasurementTableList.SP].ToString());
                GuiCommon.bizObject.bloodPressure.DP.Reading = ushort.Parse(dsPwv.Tables[0].Rows[0][(int)CrxDBPWVMeasurementTableList.DP].ToString());
            }
            catch (Exception ex)
            {
                throw (ex);
            }
        }

        /** This method is used calculate the conversion for height and weight.
         */
        private void PerformHeightWeightConversion()
        {
            int heightInInches, heigthInFeet;
            switch (crxMgrObject.GeneralSettings.HeightandWeightUnit)
            {
                // converting to int as crxMgrObject.GeneralSettings.HeightandWeightUnit returns int
                case (int)CrxGenPwvValue.CrxGenHeightWeightMetric:
                    guiradtxtsetupheight.Text = GuiCommon.bizObject.heightAndWeight.heightInCentimetres.ToString().Equals(GuiConstants.DefaultValue.ToString()) ? string.Empty : GuiCommon.bizObject.heightAndWeight.heightInCentimetres.ToString();
                    break;
                case (int)CrxGenPwvValue.CrxGenHeightWeightImperial:
                    if (GuiCommon.bizObject.heightAndWeight.heightInInches != GuiConstants.DefaultValue)
                    {
                        // convert height in inches to feet & inches
                        heightInInches = int.Parse(GuiCommon.bizObject.heightAndWeight.heightInInches.ToString()) % 12;
                        heigthInFeet = int.Parse(GuiCommon.bizObject.heightAndWeight.heightInInches.ToString()) / 12;

                        guiradtxtsetupheight.Text = heigthInFeet.ToString();
                        guiradtxtImperialHeight.Text = heightInInches.ToString();
                    }

                    break;
                default:
                    break;
            }
        }

        /** This event fires when enable property of guicmbday combo box changes
         */
        private void guicmbDay_EnabledChanged(object sender, EventArgs e)
        {
            try
            {
                if (guicmbDay.Enabled)
                {
                    // make combo box visible and labels invisible
                    guicmbDay.Visible = true;
                    guicmbDay.BringToFront();
                    guilblDay.Visible = false;
                    guilblDay.SendToBack();
                }
                else
                {
                    // make combo box invisible and labels visible
                    guicmbDay.Visible = false;
                    guicmbDay.SendToBack();
                    guilblDay.Visible = true;
                    guilblDay.BringToFront();
                }
            }
            catch (Exception ex)
            {
                GUIExceptionHandler.HandleException(ex, this);
            }
        }
     
        /** This event fires when enable property of guicmbxGender combo box changes
         */
        private void guicmbxGender_EnabledChanged(object sender, EventArgs e)
        {
            try
            {
                if (guicmbxGender.Enabled)
                {
                    // makes combo box visible and labels invisible
                    guicmbxGender.Visible = true;
                    guicmbxGender.BringToFront();
                    guilblGender.Visible = false;
                    guilblGender.SendToBack();
                }
                else
                {
                    // makes combo box invisible and labels visible
                    guicmbxGender.Visible = false;
                    guicmbxGender.SendToBack();
                    guilblGender.Visible = true;
                    guilblGender.BringToFront();
                }
            }
            catch (Exception ex)
            {
                GUIExceptionHandler.HandleException(ex, this);
            }
        }

        /** This method is used to read the General and PWV settings from the configuration manager.
         */
        private void ReadSettings()
        {
            try
            {
                crxMgrObject.GetGeneralUserSettings();
                crxMgrObject.GetPwvUserSettings();
            }
            catch (Exception ex)
            {
                throw (ex);
            }
        }

        /** This event fires when enable property of guiradtxtPatientID combo box changes
         */
        private void guiradtxtPatientID_EnabledChanged(object sender, EventArgs e)
        {
            try
            {
                if (guiradtxtPatientID.Enabled)
                {
                    // makes text box visible and labels invisible
                    guiradtxtPatientID.Visible = true;
                    guiradtxtPatientID.BringToFront();
                    guilblPatientIdDisplay.Visible = false;
                    guilblPatientIdDisplay.SendToBack();
                }
                else
                {
                    // makes text box invisible and labels visible
                    guiradtxtPatientID.Visible = false;
                    guiradtxtPatientID.SendToBack();
                    guilblPatientIdDisplay.Visible = true;
                    guilblPatientIdDisplay.BringToFront();
                }
            }
            catch (Exception ex)
            {
                GUIExceptionHandler.HandleException(ex, this);
            }
        }

        /** This event fires when enable property of guiradtxtFirstName combo box changes         
         */
        private void guiradtxtFirstName_EnabledChanged(object sender, EventArgs e)
        {
            try
            {
                if (guiradtxtFirstName.Enabled)
                {
                    // makes text box visible and labels invisible
                    guiradtxtFirstName.Visible = true;
                    guiradtxtFirstName.BringToFront();
                    guilblFirstnameDisplay.Visible = false;
                    guilblFirstnameDisplay.SendToBack();
                }
                else
                {
                    // makes text box invisible and labels visible
                    guiradtxtFirstName.Visible = false;
                    guiradtxtFirstName.SendToBack();
                    guilblFirstnameDisplay.Visible = true;
                    guilblFirstnameDisplay.BringToFront();
                }
            }
            catch (Exception ex)
            {
                GUIExceptionHandler.HandleException(ex, this);
            }
        }

        /** This event fires when enable property of guiradtxtLastName combo box changes
         */
        private void guiradtxtLastName_EnabledChanged(object sender, EventArgs e)
        {
            try
            {
                if (guiradtxtLastName.Enabled)
                {
                    // makes text box visible and labels invisible
                    guiradtxtLastName.Visible = true;
                    guiradtxtLastName.BringToFront();
                    guilblLastNameDisplay.Visible = false;
                    guilblLastNameDisplay.SendToBack();
                }
                else
                {
                    // makes text box invisible and labels visible
                    guiradtxtLastName.Visible = false;
                    guiradtxtLastName.SendToBack();
                    guilblLastNameDisplay.Visible = true;
                    guilblLastNameDisplay.BringToFront();
                }
            }
            catch (Exception ex)
            {
                GUIExceptionHandler.HandleException(ex, this);
            }
        }
       
        /** This event fires when setup screen Capture button is clicked
         * It validates measurement details and start capture process if validation succeeds
         */
        private void guiradbtnCapture_Click(object sender, EventArgs e)
        {
            try
            {
                // check if device is connected
                // fill the biz session object with measurement details
                // if validation succeeds start capture process
                if (GuiCommon.CurrentMode.Equals(CrxStructCommonResourceMsg.Pwv))
                {
                    GuiCommon.CaptureTabClick = false;
                    StartCaptureProcess();
                    // Commenting below line as part of reivew comment.
                    GuiCommon.CaptureTabClick = true;
                }
            }
            catch (Exception ex)
            {
                // In case of any exception being raised in the StartCaptureProcess()
                // Commenting below line as part of reivew comment.
                GuiCommon.CaptureTabClick = true;   
                GUIExceptionHandler.HandleException(ex, this);
            }
        }       
           
        /** This method fills session object with measurement data
         */
        private void FillSessionWithModifiedMeasuremt()
        {
            try
            {
                GuiCommon.bizObject.groupStudyId = (uint)GuiCommon.GroupId;
                GuiCommon.bizObject.systemId = (uint)GuiCommon.SystemIdentifier;
                GuiCommon.bizObject.patientNumber = (uint)GuiCommon.PatientInternalNumber;

                SetSessionWithModifiedHeightWeight();
                SetSessionWithModifiedBP();
                SetSessionWithModifiedDistance();

                GuiCommon.bizObject.notes = guiradtxtMedication.Text;
                GuiCommon.bizObject.operatorId = guiradtxtOperator.Text;
                GuiCommon.bizObject.bloodPressureEntryOption = (ushort)crxMgrObject.BpSettings.BloodPressure;
            }
            catch (Exception ex)
            {
               // GUIExceptionHandler.HandleException(ex, this);
                throw (ex);
            }
        }

        /** This method fills session object with measurement data
         */
        private void FillSessionWithModifiedMeasuremtForPwa()
        {
            try
            {
                GuiCommon.bizPwaobject.groupStudyId = (uint)GuiCommon.GroupId;
                GuiCommon.bizPwaobject.systemId = (uint)GuiCommon.SystemIdentifier;
                GuiCommon.bizPwaobject.patientNumber = (uint)GuiCommon.PatientInternalNumber;
                GuiCommon.bizPwaobject.notes = guiradtxtMedicationNotes.Text;

                SetSessionWithModifiedHeightWeightForPwa();
                SetSessionWithModifiedBPForPwa();

                GuiCommon.bizPwaobject.bloodPressureEntryOption = (ushort)crxMgrObject.BpSettings.BloodPressure;
            }
            catch (Exception ex)
            {
                throw (ex);
            }
        }

        /** Below function restrict user from adding invalid value for the height
         */
        private void GetValidationForHeight(int heightValue, RadTextBox ctrlTextBox)
        {
            if (heightValue > short.MaxValue || heightValue < Convert.ToInt32(GuiCommon.NumericValue.Zero))
            {
                string field = objValidation.GetLabelText(ctrlTextBox.Tag.ToString());
                isHeightOutsideIntegerLimits = true;
                string err = string.Format(oMsgMgr.GetMessage(CrxStructCommonResourceMsg.GuiLimitsFormat), field, 0, string.Empty, short.MaxValue, string.Empty);
                RadMessageBox.Show(err, oMsgMgr.GetMessage(CrxStructCommonResourceMsg.SystemError), MessageBoxButtons.OK, RadMessageIcon.Error);
                ctrlTextBox.Focus();
                ctrlTextBox.Text = string.Empty;
            }
            else
            {
                isHeightOutsideIntegerLimits = false;
            }
        }

        /** This method fills session with modified height for pwa
        */
        private void SetSessionWithModifiedHeightWeight()
        {
            try
            {
                // height 
                switch (crxMgrObject.GeneralSettings.HeightandWeightUnit)
                {
                    // converting to int as crxMgrObject.GeneralSettings.HeightandWeightUnit returns int
                    case (int)CrxGenPwvValue.CrxGenHeightWeightMetric:
                        GuiCommon.bizObject.heightAndWeight.heightInCentimetres = string.IsNullOrEmpty(guiradtxtsetupheight.Text) ? GuiConstants.DefaultValue : ushort.Parse(guiradtxtsetupheight.Text);
                        break;

                    case (int)CrxGenPwvValue.CrxGenHeightWeightImperial:
                        if ((guiradtxtsetupheight.Text.Length > Convert.ToInt32(GuiCommon.NumericValue.Zero)) || (guiradtxtImperialHeight.Text.Length > Convert.ToInt32(GuiCommon.NumericValue.Zero)))
                        {
                            // Checking if the inch/feet field is blank then setting it to zero.
                            // using local variable to store the text of guiradtxtImperialHeight and guiradtxtsetupheight.
                            string guiRadTxtImperialHeight = guiradtxtImperialHeight.Text.Equals(string.Empty) ? "0" : guiradtxtImperialHeight.Text;
                            string guiRadTxtSetUpheight = guiradtxtsetupheight.Text.Equals(string.Empty) ? "0" : guiradtxtsetupheight.Text;
                            int heightInInches = (int.Parse(guiRadTxtSetUpheight) * Convert.ToInt32(GuiCommon.NumericValue.Twelve)) + int.Parse(guiRadTxtImperialHeight);

                            GetValidationForHeight(heightInInches, guiradtxtsetupheight);

                            GuiCommon.bizObject.heightAndWeight.heightInInches = (ushort)heightInInches;
                        }
                        else
                        {
                            GuiCommon.bizObject.heightAndWeight.heightInInches = GuiConstants.DefaultValue;
                        }

                        break;

                    default:
                        break;
                }
            }
            catch (Exception ex)
            {
                throw (ex);
            }
        }

        /** This method fills session with modified height & weights
         */
        private void SetSessionWithModifiedHeightWeightForPwa()
        {
            try
            {
                switch (crxMgrObject.GeneralSettings.HeightandWeightUnit)
                {
                    // converting to int as crxMgrObject.GeneralSettings.HeightandWeightUnit returns int
                    case (int)CrxGenPwvValue.CrxGenHeightWeightMetric:
                        GuiCommon.bizPwaobject.heightAndWeight.heightInCentimetres = string.IsNullOrEmpty(guiradtxtPWAHeight.Text) ? GuiConstants.DefaultValue : ushort.Parse(guiradtxtPWAHeight.Text);
                        break;

                    case (int)CrxGenPwvValue.CrxGenHeightWeightImperial:
                        if ((guiradtxtPWAHeight.Text.Length > Convert.ToInt32(GuiCommon.NumericValue.Zero)) || (guiradtxtPWAImperialHeight.Text.Length > Convert.ToInt32(GuiCommon.NumericValue.Zero)))
                        {
                            // Checking if the inch/feet field is blank then setting it to zero.
                            // using local variable to store the text of guiradtxtImperialHeight and guiradtxtsetupheight.
                            string guiRadTxtImperialHeight = guiradtxtPWAImperialHeight.Text.Equals(string.Empty) ? "0" : guiradtxtPWAImperialHeight.Text;
                            string guiRadTxtSetUpheight = guiradtxtPWAHeight.Text.Equals(string.Empty) ? "0" : guiradtxtPWAHeight.Text;
                            int heightInInches = (int.Parse(guiRadTxtSetUpheight) * Convert.ToInt32(GuiCommon.NumericValue.Twelve)) + int.Parse(guiRadTxtImperialHeight);

                            GetValidationForHeight(heightInInches, guiradtxtsetupheight);

                            GuiCommon.bizPwaobject.heightAndWeight.heightInInches = (ushort)heightInInches;
                        }
                        else
                        {
                            GuiCommon.bizPwaobject.heightAndWeight.heightInInches = GuiConstants.DefaultValue;
                        }

                        break;
                    default:
                        break;
                }
            }
            catch (Exception ex)
            {
                throw (ex);
            }
        }

        /** This method fills session with modified blood pressure values
         */
        private void SetSessionWithModifiedBP()
        {
            try
            {
                GuiCommon.bizObject.bloodPressure.SP.Reading = string.IsNullOrEmpty(guiradtxtSP.Text) ? GuiConstants.DefaultValue : ushort.Parse(guiradtxtSP.Text);
                GuiCommon.bizObject.bloodPressure.DP.Reading = string.IsNullOrEmpty(guiradtxtDP.Text) ? GuiConstants.DefaultValue : ushort.Parse(guiradtxtDP.Text);
                GuiCommon.bizObject.bloodPressure.MP.Reading = GuiConstants.DefaultValue;
            }
            catch (Exception ex)
            {
                throw (ex);
            }
        }

        /** This method fills session with modified blood pressure values
        */
        private void SetSessionWithModifiedBPForPwa()
        {
            try
            {
                GuiCommon.bizPwaobject.bloodPressure.SP.Reading = string.IsNullOrEmpty(guiradlblPWASPDisplay.Text) ? GuiConstants.DefaultValue : ushort.Parse(guiradlblPWASPDisplay.Text);
                GuiCommon.bizPwaobject.bloodPressure.DP.Reading = string.IsNullOrEmpty(guiradlblPWADPDisplay.Text) ? GuiConstants.DefaultValue : ushort.Parse(guiradlblPWADPDisplay.Text);
                GuiCommon.bizPwaobject.bloodPressure.MP.Reading = string.IsNullOrEmpty(guiradlblPWAMPDisplay.Text) ? GuiConstants.DefaultValue : ushort.Parse(guiradlblPWAMPDisplay.Text);
                GuiCommon.bizPwaobject.MeanP = float.Parse(guiradlblPWAMPDisplay.Text);
                // GuiCommon.bizPwaobject.MeanP = float.Parse(GuiConstants.DefaultValue.ToString());
                GuiCommon.bizPwaobject.Sp = float.Parse(guiradlblPWASPDisplay.Text);
                GuiCommon.bizPwaobject.Dp = float.Parse(guiradlblPWADPDisplay.Text);
                GuiCommon.bizPwaobject.MeasureType = PWA_MEASURE_TYPE.PWA_RADIAL;
                GuiCommon.bizPwaobject.sampleRate = 256;
            }
            catch (Exception ex)
            {
                throw (ex);
            }
        }

        /** This method fills session with modified distance values
         */
        private void SetSessionWithModifiedDistance()
        {
            try
            {
                GuiCommon.bizObject.distanceMethod = (ushort)crxMgrObject.PwvSettings.PWVDistanceMethod;

                // distance values
                switch (crxMgrObject.PwvSettings.PWVDistanceMethod)
                {
                    case (int)CrxGenPwvValue.CrxPwvDistMethodSubtract:
                        // subtracting
                        // populate carotid, cuff & femoral to cuff textboxes
                        GuiCommon.bizObject.myCarotidDistance.distance = string.IsNullOrEmpty(guiradtxtCarotid.Text) ? GuiConstants.DefaultValue : ushort.Parse(guiradtxtCarotid.Text);
                        GuiCommon.bizObject.myCuffDistance.distance = string.IsNullOrEmpty(guiradtxtCuff.Text) ? GuiConstants.DefaultValue : ushort.Parse(guiradtxtCuff.Text);
                        GuiCommon.bizObject.myFemoral2CuffDistance.distance = string.IsNullOrEmpty(guiradtxtFemoralToCuff.Text) ? GuiConstants.DefaultValue : ushort.Parse(guiradtxtFemoralToCuff.Text);
                        GuiCommon.bizObject.myPWVDirectDistance.distance = GuiConstants.DefaultValue;
                        break;

                    case (int)CrxGenPwvValue.CrxPwvDistMethodDirect:
                        // direct
                        // populate direct & femoral to cuff textboxes
                        GuiCommon.bizObject.myCarotidDistance.distance = GuiConstants.DefaultValue;
                        GuiCommon.bizObject.myCuffDistance.distance = GuiConstants.DefaultValue;
                        GuiCommon.bizObject.myFemoral2CuffDistance.distance = string.IsNullOrEmpty(guiradtxtFemoralToCuff.Text) ? GuiConstants.DefaultValue : ushort.Parse(guiradtxtFemoralToCuff.Text);
                        GuiCommon.bizObject.myPWVDirectDistance.distance = string.IsNullOrEmpty(guiradtxtCuff.Text) ? GuiConstants.DefaultValue : ushort.Parse(guiradtxtCuff.Text);
                        break;

                    default:
                        break;
                }

                if (crxMgrObject.PwvSettings.PWVDistanceUnits.Equals((int)CrxGenPwvValue.CrxPwvDistDistUnitsCM))
                {
                    GuiCommon.bizObject.myCarotidDistance.distance = GuiCommon.bizObject.myCarotidDistance.distance.Equals(GuiConstants.DefaultValue) ? GuiCommon.bizObject.myCarotidDistance.distance : (ushort)(GuiCommon.bizObject.myCarotidDistance.distance * GuiConstants.DivisionFactor);
                    GuiCommon.bizObject.myCuffDistance.distance = GuiCommon.bizObject.myCuffDistance.distance.Equals(GuiConstants.DefaultValue) ? GuiCommon.bizObject.myCuffDistance.distance : (ushort)(GuiCommon.bizObject.myCuffDistance.distance * GuiConstants.DivisionFactor);
                    GuiCommon.bizObject.myFemoral2CuffDistance.distance = GuiCommon.bizObject.myFemoral2CuffDistance.distance.Equals(GuiConstants.DefaultValue) ? GuiCommon.bizObject.myFemoral2CuffDistance.distance : (ushort)(GuiCommon.bizObject.myFemoral2CuffDistance.distance * GuiConstants.DivisionFactor);
                    GuiCommon.bizObject.myPWVDirectDistance.distance = GuiCommon.bizObject.myPWVDirectDistance.distance.Equals(GuiConstants.DefaultValue) ? GuiCommon.bizObject.myPWVDirectDistance.distance : (ushort)(GuiCommon.bizObject.myPWVDirectDistance.distance * GuiConstants.DivisionFactor);
                }
            }
            catch (Exception ex)
            {
                throw (ex);
            }
        }

        /** This method subscribes all the text boxes & drop down for changes made to it.
         * To the form changed event which will determine for any changes made before application is closed
         */
        private void SubscribeSetupFormChanges()
        {
            try
            {
                // subscribe key press events for measurement fields to allow numeric values
                guiradtxtsetupheight.KeyPress += GuiCommon.CheckForNumericValues;
                guiradtxtImperialHeight.KeyPress += GuiCommon.CheckForNumericValues;

                guiradtxtPWAImperialHeight.KeyPress += GuiCommon.CheckForNumericValues;
                guiradtxtPWAHeight.KeyPress += GuiCommon.CheckForNumericValues;

                guiradtxtSP.KeyPress += GuiCommon.CheckForNumericValues;
                guiradtxtDP.KeyPress += GuiCommon.CheckForNumericValues;
                guiradtxtFemoralToCuff.KeyPress += GuiCommon.CheckForNumericValues;
                guiradtxtCarotid.KeyPress += GuiCommon.CheckForNumericValues;
                guiradtxtCuff.KeyPress += GuiCommon.CheckForNumericValues;
            }
            catch (Exception ex)
            {
                throw (ex);
            }
        }       

        /** Updates the setup screen label values when we scroll gridview through up-down keyboard arrow keys
         */
        private void guiradgrdPatientList_CurrentRowChanged(object sender, CurrentRowChangedEventArgs e)
        {
            try
            {
                if (e.CurrentRow != null && mode != CurrentMode.SearchMode)
                {
                    foreach (GridViewRowInfo row in guiradgrdPatientList.SelectedRows)
                    {
                        // gets the selected row patientinternal number and fills demographic details area
                        isSearchReset = false;
                        mode = CurrentMode.None;
                        guiradbtnNew.Enabled = true;
                        radlblpatientinternalnumber.Text = e.CurrentRow.Cells[1].Value.ToString();
                        radlblgroupid.Text = e.CurrentRow.Cells[2].Value.ToString();
                        DisplayLastRecord(int.Parse(e.CurrentRow.Cells[1].Value.ToString()), int.Parse(radlblgroupid.Text));
                        if (!(GuiCommon.CurrentMode.Equals(CrxStructCommonResourceMsg.Pwa) && objDefaultWindow.guiradgrpbxPwvDistanceMethod.Text.Equals(oMsgMgr.GetMessage(CrxStructCommonResourceMsg.TabPatient))))
                        {
                            guiradbtnGetBp.Visible = true;
                        }
                        else
                        {
                            guiradbtnGetBp.Visible = false;
                        }

                        if (GuiCommon.CurrentMode.Equals(CrxStructCommonResourceMsg.Pwa))
                        {
                            objDefaultWindow.radtabCapture.Enabled = false;
                        }

                        DisableTimer();
                        FillBpMeasurementData();
                    }
                }
            }
            catch (Exception ex)
            {
                GUIExceptionHandler.HandleException(ex, this);
            }
        }

        /** This event is fired when the user uses keyboard keys.
         * If the patient list is hidden and the user presses up or down keys from keyboard then 
         * user is not allowed to perform it.
         */
        private void Setup_KeyDown(object sender, KeyEventArgs e)
        {
            try
            {
                if (guiradbtnExpander.Text.Equals(oMsgMgr.GetMessage(CrxStructCommonResourceMsg.ExpanderInital)))
                {
                    if (e.KeyCode == Keys.Up || e.KeyCode == Keys.Down)
                    {
                        e.SuppressKeyPress = true;
                    }
                }
            }
            catch (Exception ex)
            {
                GUIExceptionHandler.HandleException(ex, this);
            } 
        }

        /** This event gets fired when focus is moved from height in centimeteres & height in feet text box.
         * It checks if the value entered in textbox is within valid range and shows error accordingly
         */
        private void guiradtxtsetupheight_Leave(object sender, EventArgs e)
        {
            try
            {
                objValidation.CheckIntegerFieldLimits(guiradtxtsetupheight);
            }
            catch (Exception ex)
            {
                GUIExceptionHandler.HandleException(ex, this);
            }
        }

        /** This event gets fired when focus is moved from height in inches text box.
        * It checks if the value entered in textbox is within valid range and shows error accordingly
        */
        private void guiradtxtImperialHeight_Leave(object sender, EventArgs e)
        {
            try
            {
                objValidation.CheckIntegerFieldLimits(guiradtxtImperialHeight);
            }
            catch (Exception ex)
            {
                GUIExceptionHandler.HandleException(ex, this);
            }
        }      

        /** This event gets fired when focus is moved from SP text box.
         * It checks if the value entered in textbox is within valid range and shows error accordingly
         */
        private void guiradtxtSP_Leave(object sender, EventArgs e)
        {
            try
            {
                objValidation.CheckFieldLimits(guiradtxtSP);
            }
            catch (Exception ex)
            {
                GUIExceptionHandler.HandleException(ex, this);
            }
        }

        /** This event gets fired when focus is moved from DP text box.
         * It checks if the value entered in textbox is within valid range and shows error accordingly
         */
        private void guiradtxtDP_Leave(object sender, EventArgs e)
        {
            try
            {
                objValidation.CheckFieldLimits(guiradtxtDP);
            }
            catch (Exception ex)
            {
                GUIExceptionHandler.HandleException(ex, this);
            }
        }

        /** This method is called to convert PWV distances from cm to mm.
         */
        private void ConvertMmToCm()
        {
            if (crxMgrObject.PwvSettings.PWVDistanceUnits.Equals((int)CrxGenPwvValue.CrxPwvDistDistUnitsCM))
            {
                guiradtxtCuff.Text = string.IsNullOrEmpty(guiradtxtCuff.Text) ? guiradtxtCuff.Text : (int.Parse(guiradtxtCuff.Text) / GuiConstants.DivisionFactor).ToString();
                guiradtxtCarotid.Text = string.IsNullOrEmpty(guiradtxtCarotid.Text) ? guiradtxtCarotid.Text : (int.Parse(guiradtxtCarotid.Text) / GuiConstants.DivisionFactor).ToString();
                guiradtxtFemoralToCuff.Text = string.IsNullOrEmpty(guiradtxtFemoralToCuff.Text) ? guiradtxtFemoralToCuff.Text : (int.Parse(guiradtxtFemoralToCuff.Text) / GuiConstants.DivisionFactor).ToString();
                guiradlblResult.Text = string.IsNullOrEmpty(guiradlblResult.Text) ? guiradlblResult.Text : (int.Parse(guiradlblResult.Text) / GuiConstants.DivisionFactor).ToString();
            }
        }

        /** To change the color of selected row.Also to implement color for alternating rows in the grid.
         */
        private void guiradgrdPatientList_RowFormatting(object sender, RowFormattingEventArgs e)
        {
            try
            {
                GridRowElement row = e.RowElement as GridRowElement;
                if (row != null)
                {
                    if (row.IsCurrent)
                    {
                        // row fill
                        row.DrawFill = true;
                        row.GradientStyle = GradientStyles.Solid;

                        row.BackColor = Color.FromArgb(172, 177, 204);

                        // row border
                        row.DrawBorder = true;
                        row.BorderBoxStyle = BorderBoxStyle.SingleBorder;
                        row.BorderColor = Color.Red;
                    }
                    else if (row.IsOdd)
                    {
                        row.DrawFill = true;
                        row.GradientStyle = GradientStyles.Solid;
                        row.BackColor = Color.LightGray;
                    }
                    else
                    {
                        row.ResetValue(LightVisualElement.DrawFillProperty, ValueResetFlags.Local);
                        row.ResetValue(LightVisualElement.GradientStyleProperty, ValueResetFlags.Local);
                        row.ResetValue(LightVisualElement.BackColorProperty, ValueResetFlags.Local);
                        row.ResetValue(LightVisualElement.DrawBorderProperty, ValueResetFlags.Local);
                        row.ResetValue(LightVisualElement.BorderBoxStyleProperty, ValueResetFlags.Local);
                        row.ResetValue(LightVisualElement.BorderColorProperty, ValueResetFlags.Local);
                    }
                }
            }
            catch (Exception ex)
            {
                GUIExceptionHandler.HandleException(ex, this);
            }
        }

        private void guiradgrdPatientList_CellFormatting(object sender, CellFormattingEventArgs e)
        {
            try
            {
                GridDataCellElement cell = e.CellElement as GridDataCellElement;
                if (cell != null)
                {
                    if (cell.IsCurrent)
                    {
                        // cell fill
                        cell.DrawFill = true;
                        cell.GradientStyle = GradientStyles.Solid;
                        cell.BackColor = Color.FromArgb(172, 177, 204);

                        // cell border
                        cell.DrawBorder = true;
                        cell.BorderBoxStyle = BorderBoxStyle.SingleBorder;
                        cell.BorderColor = Color.FromArgb(95, 105, 154);
                    }
                    else
                    {
                        cell.ResetValue(LightVisualElement.DrawFillProperty, ValueResetFlags.Local);
                        cell.ResetValue(LightVisualElement.GradientStyleProperty, ValueResetFlags.Local);
                        cell.ResetValue(LightVisualElement.BackColorProperty, ValueResetFlags.Local);

                        cell.ResetValue(LightVisualElement.DrawBorderProperty, ValueResetFlags.Local);
                        cell.ResetValue(LightVisualElement.BorderBoxStyleProperty, ValueResetFlags.Local);
                        cell.ResetValue(LightVisualElement.BorderColorProperty, ValueResetFlags.Local);
                    }
                }
            }
            catch (Exception ex)
            {
                GUIExceptionHandler.HandleException(ex, this);
            }
        }

        private void guicmbDay_SelectedIndexChanged(object sender, Telerik.WinControls.UI.Data.PositionChangedEventArgs e)
        {
            try
            {
                guilblDay.Text = guicmbDay.Text;

                // gets patient records based on inputs given for day drop down (only if month & year values are selected)
                if (!IsFieldsBlank(true) && mode == CurrentMode.SearchMode)
                {
                    GetSearchResults();
                }

                if (mode == CurrentMode.EditMode || (guicmbDay.SelectedIndex != Convert.ToInt32(GuiCommon.NumericValue.Zero) && mode == CurrentMode.InsertMode))
                {
                    isValueChanged = true;
                }
                else
                {
                    isValueChanged = false;
                }
            }
            catch (Exception ex)
            {
                GUIExceptionHandler.HandleException(ex, this);
            }
        }

        private void guicmbxMonth_SelectedIndexChanged(object sender, Telerik.WinControls.UI.Data.PositionChangedEventArgs e)
        {
            try
            {
                BindDaysForMonthSelected();

                // to fetch records in search mode
                if (!IsFieldsBlank(true) && mode == CurrentMode.SearchMode)
                {
                    GetSearchResults();
                }

                if (mode == CurrentMode.EditMode || (guicmbxMonth.SelectedIndex != Convert.ToInt32(GuiCommon.NumericValue.Zero) && mode == CurrentMode.InsertMode))
                {
                    isValueChanged = true;
                }
                else
                {
                    isValueChanged = false;
                }

                guilblMonth.Text = guicmbxMonth.Text;              
            }
            catch (Exception ex)
            {
                GUIExceptionHandler.HandleException(ex, this);
            }
        }

        private void guicmbxYear_SelectedIndexChanged(object sender, Telerik.WinControls.UI.Data.PositionChangedEventArgs e)
        {
            try
            {
                // binds number of days for feb month according to year selected
                if (guicmbxMonth.SelectedItem.Text.Equals(oMsgMgr.GetMessage(CrxStructCommonResourceMsg.GuiMonthFeb), StringComparison.CurrentCultureIgnoreCase))
                {
                    FillDayLeapYear();
                }

                // to fetch records in search mode
                if (!IsFieldsBlank(true) && mode == CurrentMode.SearchMode)
                {
                    GetSearchResults();
                }

                if (mode == CurrentMode.EditMode || (guicmbxYear.SelectedIndex != Convert.ToInt32(GuiCommon.NumericValue.Zero) && mode == CurrentMode.InsertMode))
                {
                    isValueChanged = true;
                }
                else
                {
                    isValueChanged = false;
                }

                guilblYear.Text = guicmbxYear.Text;                
            }
            catch (Exception ex)
            {
                GUIExceptionHandler.HandleException(ex, this);
            }
        }

        private void guicmbxYear_EnabledChanged(object sender, EventArgs e)
        {
            try
            {
                if (guicmbxYear.Enabled)
                {
                    // makes combo box visible and labels invisible
                    guicmbxYear.Visible = true;
                    guicmbxYear.BringToFront();
                    guilblYear.Visible = false;
                    guilblYear.SendToBack();
                }
                else
                {
                    // makes combo box invisible and labels visible
                    guicmbxYear.Visible = false;
                    guicmbxYear.SendToBack();
                    guilblYear.Visible = true;
                    guilblYear.BringToFront();
                }
            }
            catch (Exception ex)
            {
                GUIExceptionHandler.HandleException(ex, this);
            }
        }

        private void guicmbxMonth_EnabledChanged(object sender, EventArgs e)
        {
            try
            {
                if (guicmbxMonth.Enabled)
                {
                    // makes combo box visible and labels invisible
                    guicmbxMonth.Visible = true;
                    guicmbxMonth.BringToFront();
                    guilblMonth.Visible = false;
                    guilblMonth.SendToBack();
                }
                else
                {
                    // makes combo box invisible and labels visible
                    guicmbxMonth.Visible = false;
                    guicmbxMonth.SendToBack();
                    guilblMonth.Visible = true;
                    guilblMonth.BringToFront();
                }
            }
            catch (Exception ex)
            {
                GUIExceptionHandler.HandleException(ex, this);
            }
        }
       
        private void guicmbxGender_SelectedIndexChanged(object sender, Telerik.WinControls.UI.Data.PositionChangedEventArgs e)
        {
            try
            {
                // gets patient records based on inputs given for gender
                if (!IsFieldsBlank(true) && mode == CurrentMode.SearchMode)
                {
                    GetSearchResults();
                }

                if (mode == CurrentMode.EditMode || (guicmbxGender.SelectedIndex != Convert.ToInt32(GuiCommon.NumericValue.Zero) && mode == CurrentMode.InsertMode))
                {
                    isValueChanged = true;
                }
                else
                {
                    isValueChanged = false;
                }

                guilblGender.Text = guicmbxGender.Text;
            }
            catch (Exception ex)
            {
                GUIExceptionHandler.HandleException(ex, this);
            }
        }        
    
        private void CheckIfFieldValueIsOutsideRange()
        {
            if (GuiCommon.IsValueOutsideLimits)
            {
                objDefaultWindow.radpgTabCollection.SelectedPage = objDefaultWindow.guiradgrpbxPwvDistanceMethod;
                objDefaultWindow.guiradgrpbxPwvDistanceMethod.Enabled = true;
                return;
            }            
        }      

        /** This method is used to make all timer disable on mode change and on selected record change event in gridview.
         * This is needed because when we ar changing patient from grid and we are in middle of measurement of previous patient then measurement process should start from begining on selection 
         * of anothet patient.      
         */
        private void DisableTimer()
        {
            if (guiradgrdPatientList.Rows.Count > Convert.ToInt32(GuiCommon.NumericValue.Zero))
            {
                guiradgrdPatientList.Enabled = true;
            }

            SetupScreenTimer.Enabled = false;
            ProgressBarTimeStatusTimer.Enabled = false;
            EnableWaitButtonTimer.Enabled = false;
            guiradlblBPProgressBar.Visible = false;
            guiradbtnAutoPWACancel.Visible = false;
            guiradbtnAssessmentsDetails.Visible = false;
            guiradbtnGetBp.Enabled = true;
            counter = Convert.ToInt32(GuiCommon.NumericValue.Zero);
            guiradbtnAssessmentsDetails.Visible = false;
            guiradbtnGetBp.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.BtnStart);
            ResetMeasurementFields();
            objDefaultWindow.guiradmnuScor.Enabled = true;
            objDefaultWindow.guiradmnuScor.Enabled = true;
            objDefaultWindow.radtabCapture.Enabled = false;
            buttonMode = GuiCommon.BpButtonMode.start;
        }

        /** This function makes patient list,controls for demographic details and action buttons below patient list enable/disable depeding on measurement is in progress or not
         */
        private void BrowsemodeForMeasurement(bool value)
        {           
            objDefaultWindow.guicmbxCurrentMode.Enabled = value;
            guiradtxtPWAHeight.Enabled = value;
            guiradtxtPWAImperialHeight.Enabled = value;
            guiradtxtPwaOperator.Enabled = value;
            guiradtxtMedicationNotes.Enabled = value;
            guiradgrdPatientList.Enabled = value;
            guicmbGroup.Enabled = value;
            guiradbtnSearch.Enabled = value;
            guiradbtnNew.Enabled = value;
            guiradbtnEdit.Enabled = value;
            guiradbtnExpander.Enabled = value;
            guiradbtnDelete.Enabled = value;  
        }

        /** This event is fired when the user wants to get the BP values in the PWA mode.
         */
        private void guiradbtnGetBp_Click(object sender, EventArgs e)
        {
            try
            {
                if (!DalModule.Instance.CheckIfDeviceIsConnected())
                {
                    RadMessageBox.Show(this, oMsgMgr.GetMessage(CrxStructCommonResourceMsg.CaptureDeviceErrMsg), oMsgMgr.GetMessage(CrxStructCommonResourceMsg.SystemError), MessageBoxButtons.OK, RadMessageIcon.Error);
                    return;
                }

                GetBp();
            }
            catch (Exception ex)
            {
               GUIExceptionHandler.HandleException(ex, this);
               BrowsemodeForMeasurement(true);
            }
        }
        
        private void GetBp()
        {
            if (counter == Convert.ToInt32(GuiCommon.NumericValue.Zero))
            {
                // Following function validates height field value to be in range of ushort integer.
                CheckFieldLimitsForPWAHeight();     
                if (GuiCommon.IsValueOutsideIntegerLimits)
                {
                    return;
                }
            }           

            // Following code will be change when values will be read from Bp measurement Device
            try
            {                
                objDefaultWindow.guiradmnuScor.Enabled = false;

                // If Button text is "Start" or "Repeat"
                if ((buttonMode == GuiCommon.BpButtonMode.start) || (buttonMode == GuiCommon.BpButtonMode.repeat))
                {
                    if (ValidatePatientAge())
                    {
                        BrowsemodeForMeasurement(false);
                        objDefaultWindow.radtabReport.Enabled = false;

                        // Capture tab is disable when measurement is in progress
                        objDefaultWindow.radtabCapture.Enabled = false;

                        // Clear all measurement labels
                        guiradbtnGetBp.Enabled = true;
                        guiradbtnGetBp.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.BtnStop);
                        buttonMode = GuiCommon.BpButtonMode.stopInProgress;
                        guiradbtnAutoPWACancel.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.BtnCancel);
                        ResetMeasurementFields();

                        // Reset Progressbar values
                        guiradlblBPProgressBar.Minimum = Convert.ToInt32(GuiCommon.NumericValue.Zero);
                        guiradlblBPProgressBar.Maximum = AutoProgressbarDelay;
                        guiradlblBPProgressBar.Value1 = Convert.ToInt32(GuiCommon.NumericValue.Zero);
                        guiradCuffPressureProgBar.Value1 = Convert.ToInt32(GuiCommon.NumericValue.Zero);
                        guiradbtnAssessmentsDetails.Visible = false;

                        if (GuiCommon.bizNibpObject.StartAdultBP())
                        {
                            // Start the dummy timer to display BP readings
                            SetupScreenTimer.Enabled = true;
                            guiradCuffPressureProgBar.Visible = true;
                        }
                        else
                        {
                            guiradbtnGetBp.Text = CrxMessagingManager.Instance.GetMessage(CrxStructCommonResourceMsg.BtnStart);
                            buttonMode = GuiCommon.BpButtonMode.start;
                            objDefaultWindow.guicmbxCurrentMode.Enabled = true;
                            objDefaultWindow.guiradmnuScor.Enabled = true;
                            BrowsemodeForMeasurement(true);
                        }

                        // Hide progress bar
                        guiradlblBPProgressBar.Visible = false;
                        guiradbtnAutoPWACancel.Visible = false;
                    }
                    else
                    {
                        BrowsemodeForMeasurement(true);
                        guiradbtnAutoPWACancel.Visible = false;
                        objDefaultWindow.guicmbxCurrentMode.Enabled = true;
                        objDefaultWindow.radtabCapture.Enabled = false; 
                    }
                }
                else if (buttonMode == GuiCommon.BpButtonMode.stopWait)
                {
                    BrowsemodeForMeasurement(false);
                    objDefaultWindow.radtabReport.Enabled = false;

                    // Capture tab is disable when measurement is in progress
                    objDefaultWindow.radtabCapture.Enabled = false;

                    // Clear all measurement labels
                    guiradbtnGetBp.Enabled = true;
                    guiradbtnGetBp.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.BtnStop);
                    buttonMode = GuiCommon.BpButtonMode.stopInProgress;
                    guiradbtnAutoPWACancel.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.BtnCancel);
                    ResetMeasurementFields();

                    // Reset Progressbar values
                    guiradlblBPProgressBar.Minimum = Convert.ToInt32(GuiCommon.NumericValue.Zero);
                    guiradlblBPProgressBar.Maximum = AutoProgressbarDelay;
                    guiradlblBPProgressBar.Value1 = Convert.ToInt32(GuiCommon.NumericValue.Zero);
                    guiradbtnAssessmentsDetails.Visible = false;

                    if (GuiCommon.bizNibpObject.StartAdultBP())
                    {
                        // Start the dummy timer to display BP readings
                        SetupScreenTimer.Enabled = true;
                        guiradCuffPressureProgBar.Visible = true;
                    }

                    // Hide progress bar
                    guiradlblBPProgressBar.Visible = false;
                    guiradbtnAutoPWACancel.Visible = false;
                }
                else if (buttonMode == GuiCommon.BpButtonMode.stopInProgress || buttonMode == GuiCommon.BpButtonMode.stopInWaitProgress)
                {
                    if (counter > Convert.ToInt32(GuiCommon.NumericValue.Zero) && !GuiCommon.IsValueOutsideIntegerLimits)
                    {
                        SetAvgBpMeasurementData();
                        guiradbtnAutoPWACancel.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.BtnCapture);
                        guiradbtnAutoPWACancel.Visible = true;
                        objDefaultWindow.radtabCapture.Enabled = true;
                    }

                    waitTimer = Convert.ToInt32(GuiCommon.NumericValue.Zero);
                    EnableWaitButtonTimer.Stop();
                    SetupScreenTimer.Stop();
                    ProgressBarTimeStatusTimer.Stop();
                    GuiCommon.bizNibpObject.AbortBP();

                    // Reset Progressbar values
                    guiradCuffPressureProgBar.Value1 = Convert.ToInt32(GuiCommon.NumericValue.Zero);
                   
                    BrowsemodeForMeasurement(true);
                    objDefaultWindow.radtabReport.Enabled = GuiCommon.HasMeasurementDetails;
                    counter = Convert.ToInt32(GuiCommon.NumericValue.Zero);
                    objDefaultWindow.radlblMessage.Text = string.Empty;
                    SetupScreenTimer.Enabled = false;
                    guiradbtnGetBp.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.BtnStart);
                    buttonMode = GuiCommon.BpButtonMode.repeat;
                    guiradCuffPressureProgBar.Visible = false;
                    if (!ProgressBarTimeStatusTimer.Enabled)
                    {
                        objDefaultWindow.guiradmnuScor.Enabled = true;
                    }
                }
            }
            catch (Exception ex)
            {
                GUIExceptionHandler.HandleException(ex, this);
                DisableTimer();
                BrowsemodeForMeasurement(true);
                objDefaultWindow.radtabReport.Enabled = GuiCommon.HasMeasurementDetails;
            }
        }

        /** This method resets all BP measurement fields
         */
        private void ResetMeasurementFields()
        {
            guiradlblPWASPDisplay.Text = string.Empty;
            guiradlblPWAPPDisplay.Text = string.Empty;
            guiradlblPWAMPDisplay.Text = string.Empty;
            guiradlblPWADPDisplay.Text = string.Empty;
        }

        /** When there are more than one assessment,after every assessment this event fires.It wait for some time which is defined 
         * in xml file and calls guiradbtnGetBp click event to do next assessment.
         */
        private void EnableWaitButtonTimer_Tick(object sender, EventArgs e)
        {
            try
            {
                objDefaultWindow.radlblMessage.Text = "                  " + CrxMessagingManager.Instance.GetMessage(CrxStructCommonResourceMsg.BtnWait);
                guiradbtnGetBp.Visible = true;
                if (waitTimer >= (WaitButtonDelay - Convert.ToInt32(GuiCommon.NumericValue.One)))
                {
                    buttonMode = GuiCommon.BpButtonMode.stopWait;
                    EnableWaitButtonTimer.Stop();
                    waitTimer = Convert.ToInt32(GuiCommon.NumericValue.Zero);
                    objDefaultWindow.radlblMessage.Text = string.Empty; 
                
                    GetBp();

                    guiradbtnGetBp.Visible = true;
                }
                else
                {
                    buttonMode = GuiCommon.BpButtonMode.stopInWaitProgress;
                    waitTimer = waitTimer + Convert.ToInt32(GuiCommon.NumericValue.One);
                }
            }
            catch (Exception ex)
            {
                GUIExceptionHandler.HandleException(ex, this);
            }
        }
       
        /** This is dummy timer used to set Bp measurement stub values after 5 seconds. 
         * It checkes for assessment in progress and after completion of all assessment it enable
         * auto pwa progress bar.
         */
        private void SetupScreenTimer_Tick(object sender, EventArgs e)
        {
            try
            {
                // Display reading values
                DalPwvDataStruct nibpStruct;
                ushort cuffPressureValue = Convert.ToUInt16(GuiCommon.NumericValue.Zero);
                DalDataBuffer databufferObject = DalDataBuffer.Instance;
                int returnedValues = databufferObject.GetNextValues(Convert.ToInt32(GuiCommon.NumericValue.One), ref startIndex);
                if (returnedValues == Convert.ToInt32(GuiCommon.NumericValue.Zero))
                {
                    return;
                }

                // Deepak: Offset should start from 0 not from 1. returned values Indicates how many
                // Not an index in itselfCorrecting problem           
                nibpStruct = databufferObject.GetValueAt(startIndex, Convert.ToInt32(GuiCommon.NumericValue.Zero));

                guiradbtnGetBp.Visible = true;
                guiradbtnGetBp.Text = CrxMessagingManager.Instance.GetMessage(CrxStructCommonResourceMsg.BtnStop);

                // Display reading values
                cuffPressureValue = nibpStruct.cuffPressure;
                if (cuffPressureValue > maxCuffPressure)
                {
                    CrxLogger.Instance.Write("The cuff pressure progress bar value cannot be set to a value which is greater than its max value. The value is " + cuffPressureValue, ErrorSeverity.Error);    
                }
                else
                {
                    guiradCuffPressureProgBar.Value1 = cuffPressureValue;
                }
                objDefaultWindow.radlblMessage.Text = string.Format(CrxMessagingManager.Instance.GetMessage(CrxStructCommonResourceMsg.GuiNibpAssessmentProgressMsg), (counter + 1));
            }
            catch (Exception ex)
            {
                GUIExceptionHandler.HandleException(ex, this);
            }
        }

        /** This timer ticks every 1 sec and it ticks for time set in xml file and    
         * after time reaches to time set in xml file it start capture process automatically.
         * Before time reaches to specified value every sec it shows how much time is remaining 
         * for auto pwa in progress bar text area.
         */
        private void ProgressBarTimeStatusTimer_Tick(object sender, EventArgs e)
        {
            try
            {
                if (guiradlblBPProgressBar.Value1 >= AutoProgressbarDelay)
                {
                    objDefaultWindow.radlblMessage.Text = string.Empty;

                    // Stop Progress bar if the value exceeds cPWA Delay
                    ProgressBarTimeStatusTimer.Enabled = false;

                    // Hide Progress Bar
                    guiradlblBPProgressBar.Visible = false;
                    guiradbtnAutoPWACancel.Visible = false;

                    // Closes BpAssessment Form
                    objBpAssessment.Close();
                    CheckFieldLimitsForPWAHeight();

                    if (GuiCommon.IsValueOutsideIntegerLimits)
                    {
                        return;
                    }

                    // Call a method to go to Capture Screen
                   
                        // check if device is connected
                        // fill the biz session object with measurement details
                        // if validation succeeds start capture process
                        CrxPwaCaptureInput pwaCaptureInput = new CrxPwaCaptureInput();

                        bool value = GuiCommon.bizPwaobject.GetCurrentCaptureInput(ref pwaCaptureInput);
                        if (!Convert.ToInt32(pwaCaptureInput).Equals(crxMgrObject.PwaSettings.CaptureInput))
                        {
                            GuiCommon.bizPwaobject.Initialise(crxMgrObject.PwaSettings.CaptureInput.Equals(Convert.ToInt32(CrxPwaCaptureInput.Tonometer)) ? CrxPwaCaptureInput.Tonometer : CrxPwaCaptureInput.Cuff);
                        }

                        GuiCommon.CaptureTabClick = false;

                        objDefaultWindow.radtabCapture.Enabled = true;
                        objDefaultWindow.guiradmnuScor.Enabled = true;
                        StartCaptureProcess();
                        // Commenting below line as part of reivew comment.
                        // GuiCommon.CaptureTabClick = true;                    
                }
                else
                {
                    int displayValue = guiradlblBPProgressBar.Maximum - guiradlblBPProgressBar.Value1;

                    // Increment progress bar after every second
                    guiradlblBPProgressBar.Value1 = guiradlblBPProgressBar.Value1 + Convert.ToInt32(GuiCommon.NumericValue.One);
                    objDefaultWindow.radlblMessage.Text = string.Format(oMsgMgr.GetMessage(CrxStructCommonResourceMsg.LblPwaSetupProgressBarStartMsg), displayValue.ToString());
                }
            }
            catch (Exception ex)
            {
                GUIExceptionHandler.HandleException(ex, this);
            }
        }

        /** This event is used to cancel auto pwa or start manual capture.When text of the button is "cancel" then click event will
         * cancel auto pwa.When text of the button is "Capture" then click event will call capture process.
         */
        private void guiradbtnAutoPWACancel_Click(object sender, EventArgs e)
        {
            if (guiradbtnAutoPWACancel.Text == oMsgMgr.GetMessage(CrxStructCommonResourceMsg.BtnCancel))
            {
                // Hide Progress Bar
                guiradlblBPProgressBar.Visible = false;
                guiradbtnGetBp.Enabled = true;

                // Reset Progressbar values
                guiradlblBPProgressBar.Minimum = Convert.ToInt32(GuiCommon.NumericValue.Zero);
                guiradlblBPProgressBar.Maximum = AutoProgressbarDelay;
                guiradlblBPProgressBar.Value1 = Convert.ToInt32(GuiCommon.NumericValue.Zero);
                objDefaultWindow.radlblMessage.Text = string.Empty;
                objDefaultWindow.radtabCapture.Enabled = true;
                guiradbtnAutoPWACancel.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.BtnCapture);

                ProgressBarTimeStatusTimer.Stop();
                ProgressBarTimeStatusTimer.Enabled = false;
                BrowsemodeForMeasurement(true);
                objDefaultWindow.radtabReport.Enabled = GuiCommon.HasMeasurementDetails;
                if (guiradbtnGetBp.Text == oMsgMgr.GetMessage(CrxStructCommonResourceMsg.BtnStart) && (!ProgressBarTimeStatusTimer.Enabled))
                {
                    objDefaultWindow.guiradmnuScor.Enabled = true;                 
                }
            }
            else
            {  
                CheckFieldLimitsForPWAHeight();

                if (GuiCommon.IsValueOutsideIntegerLimits)
                {                    
                  return;
                }

                try
                {                    
                    // Coding for PWA mode.
                    CrxPwaCaptureInput pwaCaptureInput = new CrxPwaCaptureInput();              
                    bool value = GuiCommon.bizPwaobject.GetCurrentCaptureInput(ref pwaCaptureInput);
                    if (!Convert.ToInt32(pwaCaptureInput).Equals(crxMgrObject.PwaSettings.CaptureInput))
                    {
                        GuiCommon.bizPwaobject.Initialise(crxMgrObject.PwaSettings.CaptureInput.Equals(Convert.ToInt32(CrxPwaCaptureInput.Tonometer)) ? CrxPwaCaptureInput.Tonometer : CrxPwaCaptureInput.Cuff);
                    }    
               
                     GuiCommon.CaptureTabClick = false;
                     objDefaultWindow.radtabCapture.Enabled = true;

                     StartCaptureProcess();                    

                     guiradbtnAutoPWACancel.Visible = false;
                     // Commenting below line as part of reivew comment.
                     // GuiCommon.CaptureTabClick = true;
                }
                catch (Exception ex)
                {
                    // In case of any exception being raised in the StartCaptureProcess(sender, e);
                    // Commenting below line as part of reivew comment.
                    // GuiCommon.CaptureTabClick = true;
                    GUIExceptionHandler.HandleException(ex, this);
                }               
            }
        }

        /** This method is used to check any change made by the user to the PWV distance method.
         * If the user changes the PWV distnace method then,the PWV distance fields are cleard in the Setup screen
         * except for the femoral to cuff field.
         */
        private void CheckForResettingPwvDistanceFields()
        {
            if (!GuiCommon.OnLoadPwvDistanceMethod.Equals(crxMgrObject.PwvSettings.PWVDistanceMethod))
            {
                // Clear the PWV distance values when the PWV distance method is changed.
                guiradtxtCuff.Text = string.Empty;
                guiradtxtCarotid.Text = string.Empty;
            }
        }

        /** This method is used to check height field for PWA mode.
         */
        private void CheckFieldLimitsForPWAHeight()
        {
            try
            {
                // Nitesh,if the user enters 0 the validation will pass.When the user again tries to capture 
                // the value of GuiCommon.IsValueOutsideLimits is set to true becoause of which Bp measurement 
                // will not start.hence setting the value to false.
                GuiCommon.IsValueOutsideIntegerLimits = false;

                if (crxMgrObject.GeneralSettings.HeightandWeightUnit.Equals((int)CrxGenPwvValue.CrxGenHeightWeightMetric) && (!guiradtxtPWAHeight.Text.Equals(string.Empty)))
                {
                    objValidation.CheckIntegerFieldLimits(guiradtxtPWAHeight);
                }

                if (crxMgrObject.GeneralSettings.HeightandWeightUnit.Equals((int)CrxGenPwvValue.CrxGenHeightWeightImperial))
                {
                    if (!guiradtxtPWAHeight.Text.Equals(string.Empty))
                    {
                        objValidation.CheckIntegerFieldLimits(guiradtxtPWAHeight);
                        if (GuiCommon.IsValueOutsideIntegerLimits)
                        {
                            objValidation.CheckIntegerFieldLimits(guiradtxtPWAImperialHeight);
                            GuiCommon.IsValueOutsideIntegerLimits = true;
                        }
                        else
                        {
                            if (!guiradtxtPWAImperialHeight.Text.Equals(string.Empty))
                            {
                                objValidation.CheckIntegerFieldLimits(guiradtxtPWAImperialHeight);
                            }
                        }
                    }
                    else
                    {
                        if (!guiradtxtPWAImperialHeight.Text.Equals(string.Empty))
                        {
                            objValidation.CheckIntegerFieldLimits(guiradtxtPWAImperialHeight);
                        }
                    }
                }
            }

            catch (Exception ex)
            {
                GUIExceptionHandler.HandleException(ex, this);
            }
        }

        /** This event is used to show BP Assesment Dialog
         */
        private void guiradbtnAssessmentsDetails_Click(object sender, EventArgs e)
        {
            try
            {
                if (objBpAssessment != null)
                {
                    objBpAssessment = null;
                }

                objBpAssessment = new BPAssessments();
                objBpAssessment.ShowDialog();
            }
            catch (Exception ex)
            {
                GUIExceptionHandler.HandleException(ex, this);
            }
        }

        private void ValidationBeforePwaCapture()
        {
            try
            {
                GuiCommon.bizNibpObject.FinishBP();

                // Deepak: 8-Nov-2011 :disabling this as per Victor's suggestion
                // This is a temporary workaround bcuase GetConfigInfo return NACKeven 
                // after NIBP_DISCONNECT is sent
                // if (DalModule.Instance.CheckIfDeviceIsConnected())
                // CrxLogger.Instance.Write("GUI: Setup::ValidationBeforePwaCapture(). Not checking for device connection to pevent any problems associated with NIBP_DISCONNECT");
                if (DalModule.Instance.CheckIfDeviceIsConnected())
                {
                    FillSessionWithModifiedMeasuremtForPwa();

                    if (!isHeightOutsideIntegerLimits)
                    {
                        // check for valid measurement details
                        if (GuiCommon.bizPwaobject.Validate())
                        {
                            GetValidationForHeight(GuiCommon.bizPwaobject.heightAndWeight.heightInCentimetres, guiradtxtPWAHeight);
                            if (!isHeightOutsideIntegerLimits)
                            {
                                // go to capture screen once electonic module is found & data is valid                   
                                GuiCommon.CaptureChildForm = new Capture(objDefaultWindow)
                                {
                                    TopLevel = false,
                                    Dock = DockStyle.Fill,
                                    FormBorderStyle = FormBorderStyle.None
                                };

                                // adds capture form under parent window control
                                var page = objDefaultWindow.radtabCapture;
                                GuiCommon.CaptureChildForm.Parent = page;
                                page.Controls.Clear();

                                page.Controls.Add(GuiCommon.CaptureChildForm);
                                GuiCommon.CaptureChildForm.Show();
                                BrowsemodeForMeasurement(true);
                                ResetMeasurementFields();
                                guiradbtnGetBp.Enabled = true;
                                objDefaultWindow.radpgTabCollection.SelectedPage = objDefaultWindow.radtabCapture;
                                objDefaultWindow.guicmbxCurrentMode.Enabled = false;
                                objDefaultWindow.radtabCapture.Enabled = true;
                                objDefaultWindow.radtabReport.Enabled = false;
                                guiradbtnAutoPWACancel.Visible = false;

                                if (GuiCommon.ErrorInCaptureProcess)
                                {
                                    GuiCommon.ErrorInCaptureProcess = false;
                                    if (GuiCommon.CaptureChildForm != null)
                                    {
                                        GuiCommon.CaptureChildForm.ShowSetupAfterCaptureAbort();
                                    }
                                    else
                                    {
                                        NavigateuserToSetupFromCaptureWhenStartCaptureFails();
                                    }

                                    objDefaultWindow.guicmbxCurrentMode.Enabled = true;
                                }

                            }
                            else
                            {
                                if (GuiCommon.CaptureTabClick)
                                {
                                    // whenever exception is thrown while validating measurement details,
                                    // navigate the user back to Setup screen.                            
                                    objDefaultWindow.radpgTabCollection.SelectedPage = objDefaultWindow.guiradgrpbxPwvDistanceMethod;
                                }

                                BrowsemodeForMeasurement(true);
                                guiradbtnGetBp.Enabled = true;
                                guiradbtnAutoPWACancel.Visible = false;
                                objDefaultWindow.guicmbxCurrentMode.Enabled = true;
                                objDefaultWindow.radtabCapture.Enabled = false;
                            }
                        }
                        else
                        {
                            if (GuiCommon.CaptureTabClick)
                            {
                                // whenever exception is thrown while validating measurement details,
                                // navigate the user back to Setup screen.                            
                                objDefaultWindow.radpgTabCollection.SelectedPage = objDefaultWindow.guiradgrpbxPwvDistanceMethod;
                            }

                            BrowsemodeForMeasurement(true);
                            guiradbtnAutoPWACancel.Visible = false;
                            objDefaultWindow.guicmbxCurrentMode.Enabled = true;
                            objDefaultWindow.radtabCapture.Enabled = false;
                        }
                    }
                    else
                    {
                        if (GuiCommon.CaptureTabClick)
                        {
                            // whenever exception is thrown while validating measurement details,
                            // navigate the user back to Setup screen.                            
                            objDefaultWindow.radpgTabCollection.SelectedPage = objDefaultWindow.guiradgrpbxPwvDistanceMethod;
                        }

                        BrowsemodeForMeasurement(true);
                        guiradbtnAutoPWACancel.Visible = false;
                        objDefaultWindow.guicmbxCurrentMode.Enabled = true;
                        objDefaultWindow.radtabCapture.Enabled = false;
                    }
                }
                else
                {
                    // device not connected show error message
                    RadMessageBox.Show(this, oMsgMgr.GetMessage(CrxStructCommonResourceMsg.CaptureDeviceErrMsg), oMsgMgr.GetMessage(CrxStructCommonResourceMsg.SystemError), MessageBoxButtons.OK, RadMessageIcon.Error);
                    if (GuiCommon.CaptureTabClick)
                    {
                        objDefaultWindow.radpgTabCollection.SelectedPage = objDefaultWindow.guiradgrpbxPwvDistanceMethod;
                        objDefaultWindow.guiradgrpbxPwvDistanceMethod.Enabled = true;
                    }

                    BrowsemodeForMeasurement(true);
                    guiradbtnAutoPWACancel.Visible = false;
                    objDefaultWindow.guicmbxCurrentMode.Enabled = true;
                    objDefaultWindow.radtabCapture.Enabled = false;
                }
            }
            catch (Exception ex)
            {
                throw (ex);
            }
        }

        private void ValidationBeforePwvCapture()
        {
            try
            {
                CrxConfigManager.Instance.GetGeneralUserSettings();
                CrxConfigManager.Instance.GetPwvUserSettings();
                CrxConfigManager.Instance.GetPwaUserSettings();

                if (ValidatePatientAge())
                {
                    if (!objValidation.CheckMandatoryFields())
                    {
                        // check for electronic module is connected. 
                        if (DalModule.Instance.CheckIfDeviceIsConnected())
                        {
                            FillSessionWithModifiedMeasuremt();

                            if (!isHeightOutsideIntegerLimits)
                            {
                                // check for valid measurement details
                                if (GuiCommon.bizObject.Validate())
                                {
                                    GetValidationForHeight(GuiCommon.bizObject.heightAndWeight.heightInCentimetres, guiradtxtsetupheight);
                                    if (!isHeightOutsideIntegerLimits)
                                    {
                                        // go to capture screen once electonic module is found & data is valid                   
                                        GuiCommon.CaptureChildForm = new Capture(objDefaultWindow)
                                        {
                                            TopLevel = false,
                                            Dock = DockStyle.Fill,
                                            FormBorderStyle = FormBorderStyle.None
                                        };

                                        // adds capture form under parent window control
                                        var page = objDefaultWindow.radtabCapture;
                                        GuiCommon.CaptureChildForm.Parent = page;
                                        page.Controls.Clear();

                                        page.Controls.Add(GuiCommon.CaptureChildForm);

                                        GuiCommon.CaptureChildForm.Show();

                                        // GuiCommon.CaptureTabClick = false;                            
                                        objDefaultWindow.radpgTabCollection.SelectedPage = objDefaultWindow.radtabCapture;

                                        if (GuiCommon.ErrorInCaptureProcess)
                                        {
                                            GuiCommon.ErrorInCaptureProcess = false;

                                            if (GuiCommon.CaptureChildForm != null)
                                            {
                                                GuiCommon.CaptureChildForm.ShowSetupAfterCaptureAbort();
                                            }
                                            else
                                            {
                                                NavigateuserToSetupFromCaptureWhenStartCaptureFails();
                                            }

                                            objDefaultWindow.guicmbxCurrentMode.Enabled = true;
                                        }
                                    }
                                }
                                else
                                {
                                    if (GuiCommon.CaptureTabClick)
                                    {
                                        // whenever exception is thrown while validating measurement details,
                                        // navigate the user back to Setup screen.                            
                                        objDefaultWindow.radpgTabCollection.SelectedPage = objDefaultWindow.guiradgrpbxPwvDistanceMethod;
                                    }
                                }
                            }
                            else
                            {
                                isHeightOutsideIntegerLimits = true;
                            }
                        }
                        else
                        {
                            // device not connected show error message
                            RadMessageBox.Show(this, oMsgMgr.GetMessage(CrxStructCommonResourceMsg.CaptureDeviceErrMsg), oMsgMgr.GetMessage(CrxStructCommonResourceMsg.SystemError), MessageBoxButtons.OK, RadMessageIcon.Error);
                            if (GuiCommon.CaptureTabClick)
                            {
                                objDefaultWindow.radpgTabCollection.SelectedPage = objDefaultWindow.guiradgrpbxPwvDistanceMethod;
                                objDefaultWindow.guiradgrpbxPwvDistanceMethod.Enabled = true;
                            }
                        }
                    }
                }
                else
                {
                    if (GuiCommon.CaptureTabClick)
                    {
                        objDefaultWindow.radpgTabCollection.SelectedPage = objDefaultWindow.guiradgrpbxPwvDistanceMethod;
                        objDefaultWindow.guiradgrpbxPwvDistanceMethod.Enabled = true;
                    }
                }
            }
            catch (Exception ex)
            {
                throw (ex);
            }        
        }

        private bool ValidatePatientAgeForPwaMode()
        {
            bool retVal = false;
            if (GuiCommon.IsValueOutsideLimits)
            {
                GuiCommon.IsValueOutsideLimits = false;
                objDefaultWindow.radpgTabCollection.SelectedPage = objDefaultWindow.guiradgrpbxPwvDistanceMethod;
                objDefaultWindow.guiradgrpbxPwvDistanceMethod.Enabled = true;
                return retVal;
            }
            
            try
            {
                string message = string.Empty;
                switch (GuiCommon.bizPwaobject.ValidateAgeLimit(ref message))
                {
                    case BizCaptureGate.CAPTURE_GOAHEAD:
                        // Go ahead with the capture.No Confirmation required.                        
                        retVal = true;
                        break;

                    case BizCaptureGate.CAPTURE_CANCEL:
                        // Cancel the capture and bring the user back to setup screen.
                        // Show the user ,warning message recevied from the biz.dll
                        RadMessageBox.Show(this, message, oMsgMgr.GetMessage(CrxStructCommonResourceMsg.SystemError), MessageBoxButtons.OK, RadMessageIcon.Exclamation);
                        retVal = false;
                        break;

                    case BizCaptureGate.CAPTURE_CONFIRM:
                       // GuiCommon.ReportChildForm.Close();
                        DialogResult result = RadMessageBox.Show(this, message, oMsgMgr.GetMessage(CrxStructCommonResourceMsg.SystemError), MessageBoxButtons.YesNo, RadMessageIcon.Exclamation);

                        // Show a popup box to the user with the string provided with Yes and No button.
                        // Yes is proceed with capture.
                        switch (result)
                        {
                            case DialogResult.Yes:
                                retVal = true;
                                break;
                            case DialogResult.No:
                                retVal = false;
                                break;
                            default:
                                break;
                        }

                        break;

                    default:
                        break;
                }

                return retVal;
            }
            catch (Exception ex)
            {
               // GUIExceptionHandler.HandleException(ex, this);
                return retVal;
                throw (ex);
            }
        }

        /**This event is fired from the BLL,it is used tofetch the values for SP,DP,PP and MAP
         */
        private void Instance_OnBizNIBPDataEvent(object sender, BizNIBPDataEventArgs e)
        {
            try
            {
                if (e.nibpSuccess)
                {
                    if (guiradbtnGetBp.InvokeRequired)
                    {
                        guiradbtnGetBp.Invoke(new MethodInvoker(delegate
                        {
                            SetupScreenTimer.Stop();
                            guiradCuffPressureProgBar.Value1 = Convert.ToInt32(GuiCommon.NumericValue.Zero);
                            guiradCuffPressureProgBar.Visible = false;
                            waitTimer = Convert.ToInt32(GuiCommon.NumericValue.Zero);
                        }));
                    }

                    // These values are printed in the log to verify if the average for each assessment is calculated properly.
                    CrxLogger.Instance.Write("On Setup Value for SYS:" + GuiCommon.bizNibpObject.newSP);
                    CrxLogger.Instance.Write("On Setup Value for DIA:" + GuiCommon.bizNibpObject.newDP);
                    CrxLogger.Instance.Write("On Setup Value for MAP:" + GuiCommon.bizNibpObject.newMP);
                    CrxLogger.Instance.Write("On Setup Value for PP:" + GuiCommon.bizNibpObject.newPP);

                    nibpSp.Add(GuiCommon.bizNibpObject.newSP);
                    nibpDp.Add(GuiCommon.bizNibpObject.newDP);
                    nibpMp.Add(GuiCommon.bizNibpObject.newMP);
                    nibpPp.Add(GuiCommon.bizNibpObject.newPP);

                    if (CrxConfigManager.Instance.BpSettings.NumberofAssessments > 1 && counter < CrxConfigManager.Instance.BpSettings.NumberofAssessments - 1)
                    {
                        if (buttonMode != GuiCommon.BpButtonMode.stopInWaitProgress)
                        {
                            objDefaultWindow.radlblMessage.Text = "                  " + CrxMessagingManager.Instance.GetMessage(CrxStructCommonResourceMsg.BtnWait);
                            if (guiradbtnGetBp.InvokeRequired)
                            {
                                guiradbtnGetBp.Invoke(new MethodInvoker(delegate
                                {
                                    ShowBpMeasurement();
                                    guiradbtnGetBp.Visible = true;
                                    guiradbtnGetBp.Text = CrxMessagingManager.Instance.GetMessage(CrxStructCommonResourceMsg.BtnStop);
                                    EnableWaitButtonTimer.Start();

                                    guiradlblBPProgressBar.Visible = false;
                                    counter++;
                                }));
                            }
                        }
                    }
                    else
                    {
                        if (guiradbtnGetBp.InvokeRequired)
                        {
                            guiradbtnGetBp.Invoke(new MethodInvoker(delegate
                            {
                                SetAvgBpMeasurementData();
                                guiradbtnGetBp.Visible = true;
                                guiradbtnGetBp.Text = CrxMessagingManager.Instance.GetMessage(CrxStructCommonResourceMsg.BtnStart);
                                buttonMode = GuiCommon.BpButtonMode.repeat;
                                counter = Convert.ToInt32(GuiCommon.NumericValue.Zero);
                                objDefaultWindow.radlblMessage.Text = string.Empty;
                                guiradbtnAutoPWACancel.Visible = true;
                                if (CrxConfigManager.Instance.BpSettings.AutoPWASP || CrxConfigManager.Instance.BpSettings.AutoPWAPP || CrxConfigManager.Instance.BpSettings.AutoPWADP)
                                {
                                    guiradlblBPProgressBar.Visible = false;
                                    guiradbtnGetBp.Enabled = false;

                                    // Start progress bar for auto capture
                                    ProgressBarTimeStatusTimer.Start();
                                }
                                else
                                {
                                    objDefaultWindow.guiradmnuScor.Enabled = true;
                                    objDefaultWindow.radtabCapture.Enabled = true;
                                    objDefaultWindow.guicmbxCurrentMode.Enabled = true;
                                    guiradbtnAutoPWACancel.Text = CrxMessagingManager.Instance.GetMessage(CrxStructCommonResourceMsg.BtnCapture);
                                    BrowsemodeForMeasurement(true);
                                }
                            }));
                        }
                    }
                }
                else
                {
                    if (guipnlPWAMeasurementDetails.InvokeRequired)
                    {
                        guipnlPWAMeasurementDetails.Invoke(new MethodInvoker(delegate
                        {
                            RadMessageBox.Show(this, CrxMessagingManager.Instance.GetMessage(CrxStructCommonResourceMsg.NIBPValidationFailed), CrxMessagingManager.Instance.GetMessage(CrxStructCommonResourceMsg.SystemError), MessageBoxButtons.OK, RadMessageIcon.Error);
                            objDefaultWindow.guicmbxCurrentMode.Enabled = true;
                            objDefaultWindow.guiradmnuScor.Enabled = true;
                            if (counter > Convert.ToInt32(GuiCommon.NumericValue.Zero))
                            {
                                SetAvgBpMeasurementData();
                                guiradbtnAutoPWACancel.Text = CrxMessagingManager.Instance.GetMessage(CrxStructCommonResourceMsg.BtnCapture);
                                guiradbtnAutoPWACancel.Visible = true;
                                objDefaultWindow.radtabCapture.Enabled = true;
                                guiradbtnGetBp.Text = CrxMessagingManager.Instance.GetMessage(CrxStructCommonResourceMsg.BtnStart);
                                buttonMode = GuiCommon.BpButtonMode.repeat;
                                objDefaultWindow.radlblMessage.Text = string.Empty;
                                SetAvgBpMeasurementData();
                            }
                        }));
                    }
                }
            }
            catch (Exception ex)
            {
                GUIExceptionHandler.HandleException(ex, this);
            }
        }

        /**This method is used to show the Bp Measurement on the GUI.
        */
        private void ShowBpMeasurement()
        {
            guiradlblPWASPDisplay.Text = GuiCommon.bizNibpObject.newSP.ToString();
            guiradlblPWAPPDisplay.Text = GuiCommon.bizNibpObject.newPP.ToString();
            guiradlblPWADPDisplay.Text = GuiCommon.bizNibpObject.newDP.ToString();
            guiradlblPWAMPDisplay.Text = GuiCommon.bizNibpObject.newMP.ToString();
        }

        /**This method is used to call a method to calculate the average bp measurement.
         */
        private void SetAvgBpMeasurementData()
        {
            try
            {
                CalcuateAverage(nibpSp, guiradlblPWASPDisplay);
                CalcuateAverage(nibpDp, guiradlblPWADPDisplay);
                CalcuateAverage(nibpPp, guiradlblPWAPPDisplay);
                CalcuateAverage(nibpMp, guiradlblPWAMPDisplay);
                nibpDp.Clear();
                nibpMp.Clear();
                nibpPp.Clear();
                nibpSp.Clear();
            }
            catch (Exception ex)
            {
                GUIExceptionHandler.HandleException(ex, this);
            }
        }

        /**This method is used to calculate average value for Bp measurement.
        */
        private void CalcuateAverage(ArrayList list, RadLabel labelName)
        {
            try
            {
                int sum = Convert.ToInt32(GuiCommon.NumericValue.Zero);
                double average = Convert.ToInt32(GuiCommon.NumericValue.Zero);
                foreach (ushort i in list)
                {
                    sum = sum + i;
                }

                CrxLogger.Instance.Write("Sum :" + sum);

                average = (sum / list.Count);
                CrxLogger.Instance.Write("Avg :" + average);
                labelName.Text = Math.Round(average).ToString();
            }
            catch (Exception ex)
            {
                throw (ex);
            }
        }            

        /**This method is used to check if the user wants to Repeat a PWA capture.
         * This happens when the user clicks on the Repeat button on the PWA Report screen.
         */ 
        private void CheckIfUserWantsToRepeatPWACapture()
        {
            try
            {
                if (GuiCommon.RepeatButtonClickedStartNibpOnSetup)
                {
                    // Set the flag to false.
                    GuiCommon.RepeatButtonClickedStartNibpOnSetup = false;
                    GetBp();
                }
            }
            catch (Exception ex)
            {
                throw (ex);
            }
        }      
             
        /** This method is used to fill the Bp measurment data in the quickstart mode. 
        */
        private void FillBpMeasurementData()
        {
            try
            {
                if (GuiCommon.quickStartCrxPwaData == null)
                {
                    return;
                }

                // fill the Bp measurment data calculated on the result tab.
                if ((GuiCommon.CurrentMode.Equals(CrxStructCommonResourceMsg.Pwa) && objDefaultWindow.guiradgrpbxPwvDistanceMethod.Text.Equals(oMsgMgr.GetMessage(CrxStructCommonResourceMsg.TabPatient))))
                {
                    guiradlblPWASPDisplay.Text = string.IsNullOrEmpty(GuiCommon.quickStartCrxPwaData.C_Sp.ToString()) ? string.Empty : Math.Round(GuiCommon.quickStartCrxPwaData.C_Sp).ToString();
                    guiradlblPWADPDisplay.Text = string.IsNullOrEmpty(GuiCommon.quickStartCrxPwaData.C_Dp.ToString()) ? string.Empty : Math.Round(GuiCommon.quickStartCrxPwaData.C_Dp).ToString();
                    guiradlblPWAPPDisplay.Text = string.IsNullOrEmpty(((GuiCommon.quickStartCrxPwaData.C_Sp - GuiCommon.quickStartCrxPwaData.C_Dp)).ToString()) ? string.Empty : Math.Round((GuiCommon.quickStartCrxPwaData.C_Sp - GuiCommon.quickStartCrxPwaData.C_Dp)).ToString();
                    guiradlblQuickMapDisplay.Text = string.IsNullOrEmpty(GuiCommon.quickStartCrxPwaData.C_Meanp.ToString()) ? string.Empty : Math.Round(GuiCommon.quickStartCrxPwaData.C_Meanp).ToString();
                }
            }
            catch (Exception ex)
            {
                throw (ex);
            }
        }

        /** This event is fired when the user clicks on the Save to Patinet button.
         */
        private void guiradbtnSaveToPatient_Click(object sender, EventArgs e)
        {
            try
            {
                if (!ValidatePatientAgeForPwaMode())
                {
                    return;
                }

                // put height and medication notes in biz
                SetSessionWithModifiedHeightWeightForPwa();
                GuiCommon.bizPwaobject.notes = guiradtxtMedicationNotes.Text;
                GuiCommon.bizPwaobject.CalculateAge();

                // recalculate the report.
                // if the report generation is sucessful then save the report in the db and navigate the user to the report screen.
                System.Windows.Forms.Cursor.Current = Cursors.WaitCursor;                
                if (GuiCommon.bizPwaobject.RecalculatePWAReport(GuiCommon.quickStartCrxPwaData, GuiCommon.quickStartCrxPwaCuffData))
                {
                    if (!string.IsNullOrEmpty(GuiCommon.bizPwaobject.GetInconclusiveNoteMsgKey()))
                    {
                        GuiCommon.InConclusiveMessageForPwaCapture = CrxMessagingManager.Instance.GetMessage(GuiCommon.bizPwaobject.GetInconclusiveNoteMsgKey());
                    }

                    objDefaultWindow.radlblMessage.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.GuiCaptureSavingReport);

                    // report calculation successful save report & navigate to report screen
                    SaveReportInDatabase(GuiCommon.quickStartCrxPwaData, GuiCommon.quickStartCrxPwaCuffData);
                    System.Windows.Forms.Cursor.Current = Cursors.Default;
                }
                else
                {
                    System.Windows.Forms.Cursor.Current = Cursors.Default;

                    // if the report generation is not sucessful then prompt the user that report generation failed
                    // report calculation failed create text file.  
                    CreateTextFileForFailedReport();
                }
            }
            catch (Exception ex)
            {
                GUIExceptionHandler.HandleException(ex, this);
            }            
        }

        /** This method is used to save the report into the database.
         */
        private void SaveReportInDatabase(CrxStructPWAMeasurementData pwaMeasurementData, CrxStructCuffPWAMeasurementData pwaCuffData)
        {
            try
            {
                GridViewRowInfo row = guiradgrdPatientList.CurrentRow;

                pwaMeasurementData.PatientNumberInternal = int.Parse(row.Cells[1].Value.ToString());
                pwaMeasurementData.GroupIdentifier = int.Parse(row.Cells[2].Value.ToString());
                pwaMeasurementData.SystemIdentifier = bobj;

                // establish connection with the database.
                if (dbMagr.CheckConnection(GuiCommon.ServerNameString(), crxMgrObject.GeneralSettings.SourceData) == 0)
                {
                    int iRow = dbMagr.SaveCuffPWAMeasurementDetails(pwaMeasurementData, pwaCuffData);
                    if (iRow > Convert.ToInt32(GuiCommon.NumericValue.Zero))
                    {
                        GuiCommon.IsReportGenerated = true;

                        // redirect to report screen
                        GuiCommon.SetupToReport = false;                        
                        GuiCommon.PwvCurrentStudyDatetime = pwaMeasurementData.StudyDateTime.ToString();

                        // Disable the tick button on the screen.                                                    
                        objDefaultWindow.radpgTabCollection.SelectedPage = objDefaultWindow.radtabReport;
                        objDefaultWindow.radlblMessage.Text = string.Empty;
                        objDefaultWindow.radtabReport.Enabled = true;
                        if (!objDefaultWindow.radtabReport.Enabled)
                        {
                            return;
                        }

                        // call the report load event only once 
                        // report load count is 1 when application is launched
                        if (GuiCommon.ReportLoadCount == Convert.ToInt32(GuiCommon.NumericValue.One))
                        {
                            GuiCommon.ReportLoadCount++;
                        }
                        else
                        {
                            // invoke load method of report screen
                            GuiCommon.ScorControllerObject.LoadReport();
                        }

                        // disable setting tab on menu bar                
                        objDefaultWindow.guiradmnuSystemKey.Enabled = false;

                        // disable settings & cross button
                        objDefaultWindow.guiradmnuitemSettings.Enabled = false;
                        objDefaultWindow.guiradmnuScor.Enabled = true;
                        objDefaultWindow.guiradgrpbxPwvDistanceMethod.Enabled = true;
                        objDefaultWindow.radtabCapture.Enabled = false;
                    }
                    else
                    {
                        objDefaultWindow.radlblMessage.Text = string.Empty;
                        RadMessageBox.Show(this, oMsgMgr.GetMessage(CrxStructCommonResourceMsg.ReportSaveErr), oMsgMgr.GetMessage(CrxStructCommonResourceMsg.SystemError), MessageBoxButtons.OK, RadMessageIcon.Error);
                        objDefaultWindow.radpgTabCollection.SelectedPage = objDefaultWindow.guiradgrpbxPwvDistanceMethod;
                    }
                }
                else
                {
                    DialogResult result = RadMessageBox.Show(this, GuiCommon.ConnectionErrorString(), oMsgMgr.GetMessage(CrxStructCommonResourceMsg.SystemError), MessageBoxButtons.RetryCancel, RadMessageIcon.Error);
                    if (result == DialogResult.Retry)
                    {
                        SaveReportInDatabase(GuiCommon.quickStartCrxPwaData, GuiCommon.quickStartCrxPwaCuffData);
                    }
                    else
                    {
                        // keep the user on the patient screen.Do not navigate the user anywhere.
                        return;
                    }
                }
            }
            catch (Exception ex)
            {
              //  GUIExceptionHandler.HandleException(ex, this);
                throw (ex);
            }
        }

        /** This method is used to create a text file when the report calculation fails.
         */ 
        private void CreateTextFileForFailedReport()
        {
            try
            {
                objDefaultWindow.radlblMessage.Text = string.Empty;

                // report calculation failed save captured data in text file                
                // this will create text file & will save data captured so far                        
                GuiCommon.ScorControllerObject.SaveCaptureData();

                // GetSavedfile path should only be called once.
                string captureFilePath = DalModule.Instance.GetSavedFilePath();                
                
                // show error message alongwith filename
                RadMessageBox.Show(this, oMsgMgr.GetMessage(CrxStructCommonResourceMsg.ReportCalFailMsg) + Environment.NewLine + oMsgMgr.GetMessage(CrxStructCommonResourceMsg.GuiWaveformSaveMsg) + Environment.NewLine + captureFilePath, oMsgMgr.GetMessage(CrxStructCommonResourceMsg.SystemError), MessageBoxButtons.OK, RadMessageIcon.Error);

                // log the error
                CrxLogger.Instance.Write(oMsgMgr.GetMessage(CrxStructCommonResourceMsg.ReportCalFailMsg) + Environment.NewLine + oMsgMgr.GetMessage(CrxStructCommonResourceMsg.GuiWaveformSaveMsg) + Environment.NewLine + captureFilePath);                
            }
            catch (Exception ex)
            {
               // GUIExceptionHandler.HandleException(ex, this);
                throw (ex);
            }
        }

        /** This method can be moved to Stratergy,but will not add much value.Hence keeping it here.
         */
        private void HideMeasurementPanelDependingOnMode()
        {
            if (GuiCommon.CurrentMode.Equals(CrxStructCommonResourceMsg.Pwv))
            {
                guipnlMeasurementDetails.Visible = false;
            }
            else
            {
                if ((!(GuiCommon.IsReportGenerated || GuiCommon.FromQuickStart)) && mode != CurrentMode.None)
                {
                    guipnlPWAMeasurementDetails.Visible = true;
                    guipnlPWAMeasurementDetails.Enabled = false;
                    // PlotAvgAorticPulseChart(); 
                }
                else
                {
                    guipnlPWAMeasurementDetails.Visible = false;
                    guipnlPWAMeasurementDetails.Enabled = true;
                }
            }
        }

        public void NavigateuserToSetupFromCaptureWhenStartCaptureFails()
        {
            try
            {
                if (GuiCommon.StartupScreen.ToUpper().Equals(CrxStructCommonResourceMsg.QuickStart) && GuiCommon.CurrentMode.Equals(CrxStructCommonResourceMsg.Pwa))
                {
                    objDefaultWindow.radpgTabCollection.SelectedPage = objDefaultWindow.radtabQuickStart;
                }
                else
                {
                    objDefaultWindow.radpgTabCollection.SelectedPage = objDefaultWindow.guiradgrpbxPwvDistanceMethod;
                    objDefaultWindow.guicmbxCurrentMode.Enabled = true;

                    // set variable to enforce 30 secs timers on setup 
                    // commenting the below as part of review comment.
                    // GuiCommon.CaptureToSetup = true;
                }


                objDefaultWindow.radlblMessage.Text = string.Empty;
                objDefaultWindow.radlblCaptureTime.Text = string.Empty;

                // enable settings, backup, restore & cross button
                objDefaultWindow.guiradmnuitemSettings.Enabled = true;
                objDefaultWindow.guiradmnuSystemKey.Enabled = true;
                objDefaultWindow.guiradmnuScor.Enabled = true;
                objDefaultWindow.guiradgrpbxPwvDistanceMethod.Enabled = true;
                objDefaultWindow.radtabReport.Enabled = GuiCommon.HasMeasurementDetails;
                objDefaultWindow.guipictureboxError.Image = null;
            }
            catch (Exception ex)
            {
                throw (ex);
            }
        }

        // End: AtCor-<Drop2>-<Sprint7>, TM, <UserStory>  

        private void PlotAvgAorticPulseChart()
        {
            try
            {
                // set y axis (normal range values from Bizsession object in float)
                if (GuiCommon.quickStartCrxPwaData == null)
                {
                    return;
                }
                float[] avgAorticPulse = GuiCommon.quickStartCrxPwaData.C_AV_PULSE;

                // initialize series,chartype,add points to series and finally add series to chart.            
                // set display properties for Avg Aortic Pulse graph
                guichartPWAReport.Series[0].Points.Clear();


                for (int i = 0; i < avgAorticPulse.Length; i++)
                {
                    if (avgAorticPulse[i] == 0)
                    {
                        // Do Nothing
                    }
                    else
                    {
                        guichartPWAReport.Series[0].Points.AddXY(averageAorticXAxisInterval * i, avgAorticPulse[i]);
                    }
                }


                guichartPWAReport.Series[1].Points.Clear();

                // Setting minimum and maximum of Y-axis for Chart
                avgAorticPulse = ResetNonZeroSizeofArray(avgAorticPulse);
                Array.Sort(avgAorticPulse);
                for (int i = 0; i < avgAorticPulse.Length; i++)
                {
                    if (avgAorticPulse[i] == 0)
                    {
                        // Do Nothing
                    }
                    else
                    {
                        double value = Math.Round(avgAorticPulse[i] * GuiConstants.ChartAreaMinimumY, MidpointRounding.ToEven);
                        value = ((int)Math.Round(value / 10)) * 10;
                        guichartPWAReport.ChartAreas[0].AxisY.Minimum = value - 10;
                        break;
                    }
                }

                double valueMax = Math.Round((avgAorticPulse[avgAorticPulse.Length - 1]) * GuiConstants.ChartAreaMaximumY, MidpointRounding.ToEven);
                valueMax = ((int)Math.Round(valueMax / 10)) * 10;
                guichartPWAReport.ChartAreas[0].AxisY.Maximum = valueMax + 10;
                guichartPWAReport.Invalidate();
            }
            catch (Exception ex)
            {
                GUIExceptionHandler.HandleException(ex, this);
            }
        }

        /**This method is used to remove all the zero values from a given array.
      */
        private float[] ResetNonZeroSizeofArray(float[] rawSignalArr)
        {
            int arrLen = 0;
            for (arrLen = 0; arrLen < rawSignalArr.Length; arrLen++)
            {
                if (rawSignalArr[arrLen] == 0.0)
                {
                    break;
                }
            }

            float[] tempArr = new float[arrLen];

            for (int j = 0; j < arrLen; j++)
            {
                tempArr[j] = rawSignalArr[j];
            }

            return tempArr;
        }

    }   
}
