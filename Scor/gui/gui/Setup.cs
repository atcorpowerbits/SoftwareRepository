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
using Telerik.WinControls.UI;
using AtCor.Scor.BusinessLogic;
using System.Configuration;
using System.Globalization;
using AtCor.Scor.DataAccess;

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
        const int PatientListHideValue = 10; // minimum splitter distance to hide patient list
        const int PatientListShowValue = 356; // maximum splitter distance to show patient list
                
        readonly CrxDBManager dbMagr = CrxDBManager.Instance;
        readonly string serverNameString = string.Empty;
        readonly CrxConfigManager crxMgrObject = CrxConfigManager.Instance;         
        readonly CrxMessagingManager oMsgMgr = CrxMessagingManager.Instance;
        int heightInCentiConversion = 0, heightInFeetConversion = 0, heightInInchConversion = 0;
        int bobj;

        // AtCor-Drop2-Sprint3, TM, Userstory 12,27th July, 2011
        private int timer = 0, waitTimer = 0;
        private int counter = 0;
        GuiFieldValidation objValidation;

        public static event EventHandler StartButtonClick;     

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
/*
        string groupnamechange = string.Empty;
*/
        string orgPatientIdExt = string.Empty;
        private DefaultWindow objDefaultWindow;
        private BPAssessments objBpAssessment = new BPAssessments();
        #endregion

        /**Parameterized Constructor, used to display messages in default window      
      */
        public Setup(DefaultWindow defWindow)
        { 
            try
            {               
                InitializeComponent();                

                // subscribe for form changes
                SubscribeSetupFormChanges();
                ReadSettings();
                SetTextForSetupTab();
                SetSetupTagForValidations();

                crxMgrObject.GetBpUserSettings();

                // Get delay values from ScorSystemParameters.xml file and set auto progress bar and wait button delay
                SetDelayValues();

                // set the default window
                objDefaultWindow = defWindow;
                                
                // subscribe to Settings change event from settings window
                frmSettingsWindow.OnSettingsChangedEvent += SettingsChangedEventHandler;
                DefaultWindow.OnRestoreCompleteSuccess += Setup_Load;
                DefaultWindow.OnCaptureTabClick += StartCaptureProcess;                
                DefaultWindow.OnExitSaveSetupChanges += guiradbtnSave_Click;
                DefaultWindow.OnSetupMenuItemClick += SaveChangesForModes;
                GuiCommon.OnCaptureClosing += EnableCaptureButton;
                Report.OnPwvMeasurementChangedEvent += SettingsChangedEventHandler;
                PWAReport.OnPwaMeasurementChangedEvent += SettingsChangedEventHandlerPwa;
                DefaultWindow.OnSetupScreenTabClick += SetFocusOnPatientList;
                DefaultWindow.OnRestoreOptionClick += CheckIfInInsertMode;
                StartButtonClick += guiradbtnGetBp_Click;              
                   
                // subscribe to Mode change event from Modes dropdown
                DefaultWindow.OnModeChangeEvent += ModeChangeEventHandler;

                // initialize servername string
                serverNameString = GuiCommon.ServerNameString();
                GuiCommon.SetShape(guilblLastNameDisplay, guilblFirstnameDisplay, guilblPatientIdDisplay, guilblFirstnameDisplay, guilblGender, guilblDay, guilblMonth, guilblYear, guiradlblPWASPDisplay, guiradlblPWAPPDisplay, guiradlblPWAMPDisplay, guiradlblPWADPDisplay, guiradlblCuffPressureValue);
                GuiCommon.SetShape(guiradtxtsetupheight, guiradtxtImperialHeight, guiradtxtOperator, guiradtxtMedication, guiradtxtSP, guiradtxtDP, guiradtxtCarotid, guiradtxtCuff, guiradtxtFemoralToCuff, guiradtxtPatientID, guiradtxtFirstName, guiradtxtLastName, guiradtxtPWAHeight, guiradtxtPWAImperialHeight, guiradtxtOthDevPWASP, guiradtxtOthDevPWADP, guiradtxtPwaOperator, guiradtxtMedicationNotes);
                GuiCommon.SetShape(guicmbDay, guicmbxMonth, guicmbxYear, guicmbxYear, guicmbxGender);
            }
            catch (Exception ex)
            {
                GUIExceptionHandler.HandleException(ex, this);
            }          
        }

        private void SetDelayValues()
        {
            try
            {
                AutoProgressbarDelay = CrxSytemParameters.Instance.GetIntegerTagValue("Gui.AutoPWAProgressbarDelay");
                WaitButtonDelay = CrxSytemParameters.Instance.GetIntegerTagValue("Gui.WaitButtonDelay");              
            }
            catch (Exception ex)
            {
                GUIExceptionHandler.HandleException(ex, this);
            }
        }

        /**This method is called on the tick of wait interval  timer used on the Default window.
       * On the tick of the timer we enable the Capture button on the Setup screen along with the Capture tab.
       */
        public void EnableCaptureButton(bool value)
        {
            try
            {
                objDefaultWindow.radtabCapture.Enabled = value;
                guiradbtnCapture.Enabled = value;
                GuiCommon.CaptureToSetup = !value;
            }
            catch (Exception ex)
            {
                GUIExceptionHandler.HandleException(ex, this);
            }
        }

        /** This event is invoked from DefautWindow when, there are no records in the db and the user is trying to restore db.
         *  During this process if he does not have the permissions to restore this method will be executed.
         */ 
        void CheckIfInInsertMode(object sender, EventArgs e)
        {
            if (guiradgrdPatientList.Rows.Count == 0)
            {
                BrowseMode(false); 
            }
            else
            {
                return;
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

           // guiradlblCarotid.Tag = guiradtxtCarotid.Tag = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.FieldDistanceCarotid);
           // guiradlblCuff.Tag = guiradtxtCuff.Tag = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.FieldDistanceCuffOrDirect);
            guiradlblFemoralToCuff.Tag = guiradtxtFemoralToCuff.Tag = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.FemoralDistanceFemoraltoCuff);
            guiradlblDP.Tag = guiradtxtDP.Tag = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.FieldPatientDp);
            guiradlblSP.Tag = guiradtxtSP.Tag = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.FieldPatientSp);
            guilblHeight.Tag = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.FieldPatientHeight);
            guiradtxtsetupheight.Tag = crxMgrObject.GeneralSettings.HeightandWeightUnit.Equals((int)CrxGenPwvValue.CrxGenHeightWeightMetric) ? oMsgMgr.GetMessage(CrxStructCommonResourceMsg.FieldPatientHeight) : oMsgMgr.GetMessage(CrxStructCommonResourceMsg.FieldPatientHeightFoot);
            guiradtxtImperialHeight.Tag = crxMgrObject.GeneralSettings.HeightandWeightUnit.Equals((int)CrxGenPwvValue.CrxGenHeightWeightMetric) ? string.Empty : oMsgMgr.GetMessage(CrxStructCommonResourceMsg.FieldPatientHeightInch);

            guiradtxtPWAHeight.Tag = crxMgrObject.GeneralSettings.HeightandWeightUnit.Equals((int)CrxGenPwvValue.CrxGenHeightWeightMetric) ? oMsgMgr.GetMessage(CrxStructCommonResourceMsg.FieldPatientHeight) : oMsgMgr.GetMessage(CrxStructCommonResourceMsg.FieldPatientHeightFoot);
            guiradtxtPWAImperialHeight.Tag = crxMgrObject.GeneralSettings.HeightandWeightUnit.Equals((int)CrxGenPwvValue.CrxGenHeightWeightMetric) ? string.Empty : oMsgMgr.GetMessage(CrxStructCommonResourceMsg.FieldPatientHeightInch);
         
            // guiradlblWeight.Tag = guiradtxtWeight.Tag = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.FieldPatientWeight); 
        }
               
        /**This is Event handler which is called whenever the General settings and PWV settings are chaged in the Settings window.
        *It is used to changes the GUI controls as per the latest General and PWV settings.
        */
        void SettingsChangedEventHandler(object sender, EventArgs e)
        {
            try
            {
                if (InvokeRequired)
                {
                    Invoke(new EventHandler(SettingsChangedEventHandler));
                    return;
                }               

                // reset the measurement text fields and update according to the new settings.
               // ResetPatientMeasurementFields();
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
                if (crxMgrObject.GeneralSettings.StartupScreen.ToUpper() != oMsgMgr.GetMessage(CrxStructCommonResourceMsg.QuickStart).ToUpper())
                {
                    objValidation.SetMandatoryFields(guipnlMeasurementDetails);
                }
                
                if (!string.IsNullOrEmpty(radlblpatientinternalnumber.Text.Trim()) && !string.IsNullOrEmpty(radlblgroupid.Text))
                {
                    // to update biz session object with changed setting values
                    DisplayLastRecord(int.Parse(radlblpatientinternalnumber.Text.Trim()), int.Parse(radlblgroupid.Text));
                }

                GuiCommon.ScorControllerObject.SetDistanceMethodAndUnits();                
                guiradtxtFemoralToCuff.Text = crxMgrObject.PwvSettings.FemoralToCuff;

                if (crxMgrObject.PwvSettings.PWVDistanceUnits.Equals((int)CrxGenPwvValue.CrxPwvDistDistUnitsCM))
                {
                    guiradtxtFemoralToCuff.Text = string.IsNullOrEmpty(guiradtxtFemoralToCuff.Text) ? guiradtxtFemoralToCuff.Text : (int.Parse(guiradtxtFemoralToCuff.Text) / GuiConstants.DivisionFactor).ToString();
                }

                SetPatientPrivacy();
                SetSetupTagForValidations();

                // CheckForResettingPwvDistanceFields();
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
                        // bool value = GuiCommon.bizPwaobject.Initialise(CrxPwaCaptureInput ;
                    }
                }              
            }
            catch (Exception ex)
            {
               GUIExceptionHandler.HandleException(ex, this);
            }
        }

        /**This is Event handler which is called whenever the General settings and PWV settings are chaged in the Settings window.
        *It is used to changes the GUI controls as per the latest General and PWV settings.
        */
        void SettingsChangedEventHandlerPwa(object sender, EventArgs e)
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
            guiradtxtsetupheight.Text = string.Empty;
            guiradtxtImperialHeight.Text = string.Empty;
            guiradtxtSP.Text = string.Empty;
            guiradtxtDP.Text = string.Empty;

           // guiradtxtCarotid.Text = string.Empty;
           // guiradtxtCuff.Text = string.Empty;
            guiradlblResult.Text = string.Empty;
            guiradtxtMedication.Text = string.Empty;
            guiradtxtOperator.Text = string.Empty;
        }

        /**This event fires when form is loaded.
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

                GuiCommon.IsOnSetupScreen = true; 
                bobj = GuiConstants.SystemId;
                GuiCommon.SystemIdentifier = bobj;
                objValidation = new GuiFieldValidation(guipnlMeasurementDetails);
                objValidation = new GuiFieldValidation(guipnlPWAMeasurementDetails);
                                
                SetPatientPrivacy();
                FillGender();
                FillDay(0);
                FillMonthAndYear();
                LoadGroupNames();
                InitializePatientList();
                LoadPatientList();
                if (GuiCommon.CurrentMode.Equals(CrxStructCommonResourceMsg.Pwa))
                {
                    objDefaultWindow.radtabCapture.Enabled = false;
                }

                guiradlblPWASPDisplay.Font = guiradlblPWASPDisplay.Font = guiradlblPWAPPDisplay.Font = guiradlblPWAMPDisplay.Font = guiradlblPWADPDisplay.Font = guiradlblCuffPressureValue.Font = guiradlblBpAssessmentsStatus.Font = new Font("Arial", 11);
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
         * */
        void FillGender()
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
            guicmbxGender.SelectedIndex = 0;            
        }

        /**This method is used to populate the group names into the combo box from the database using database manager class. 
      */
        void LoadGroupNames()
        {
            // fetches group name and binds it
            try
            {
                if (dbMagr.CheckConnection(serverNameString, crxMgrObject.GeneralSettings.SourceData) == 0)
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
                GUIExceptionHandler.HandleException(ex, this);
            }            
        }       

        /** This method is used to show the grid view when the Expand button is clicked.
       */ 
        private void guiradbtnExpander_Click(object sender, EventArgs e)
        {
            if (string.Compare(guiradbtnExpander.Text, oMsgMgr.GetMessage(CrxStructCommonResourceMsg.HideSmall), StringComparison.CurrentCultureIgnoreCase) == 0)
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

        /** This method is used to hide the grid view when the Expand button is clicked.
       */
        private void ShowHidePatientDetails(string value)
        {
            // disable cancel button when there are no records in patient list
            if (guiradgrdPatientList.Rows.Count == 0)
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

                // Disable the vertical scrollbar                                 
                guiradgrdPatientList.VerticalScrollState = ScrollState.AlwaysHide;
                radLabel1.Visible = true;
            }
            else
            {
                splitContainer1.SplitterDistance = PatientListShowValue;
                guiradbtnSearch.Enabled = (mode == CurrentMode.None && guiradgrdPatientList.Rows.Count > 1) ? true : false;
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
                guiradgrdPatientList.Columns[0].Width = 0;
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

                // guiradgrdPatientList.Columns.Add(CrxDBGetPatientDetails.GroupName.ToString(), oMsgMgr.GetMessage(CrxStructCommonResourceMsg.GuiDisplayGroup), CrxDBGetPatientDetails.GroupName.ToString());
                // guiradgrdPatientList.Columns[8].Width = 72;                             
                guiradgrdPatientList.TableElement.EndUpdate();
                guiradgrdPatientList.AutoGenerateColumns = false;
                isCellInitializeWidth = false;
            }
            catch (Exception ex)
            {
                GUIExceptionHandler.HandleException(ex, this);
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

                    if (ds.Tables[0].Rows.Count > 0)
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
                GUIExceptionHandler.HandleException(ex, this);
            }                   
        }

        /** This method is used to load the demographic details of the last pateint in the Patientlist gridview.
         */
        private void DisplayLastRecord(int patientNumberInternal, int groupId)
        {
            try
            {
                if (dbMagr.CheckConnection(serverNameString, crxMgrObject.GeneralSettings.SourceData) == 0)
                {
                    // reset demographic fields
                    ResetFields();
                    BrowseMode(mode == CurrentMode.None);

                    DataSet dsPatientDemographicDetails = dbMagr.GetPatientDemographicRecords(patientNumberInternal, bobj, groupId);

                    if (dsPatientDemographicDetails.Tables[0].Rows.Count > 0)
                    {
                        DateTime date = DateTime.Parse(dsPatientDemographicDetails.Tables[0].Rows[0][(int)CrxDBGetPatientDetailsById.DateOfBirth].ToString());
                        
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

                        // smarajit
                        string tempGender = CultureInfo.CurrentCulture.TextInfo.ToTitleCase(dsPatientDemographicDetails.Tables[0].Rows[0][(int)CrxDBGetPatientDetailsById.Gender].ToString().Trim().ToUpper());
                      
                        // guicmbxGender.SelectedValue = CultureInfo.CurrentCulture.TextInfo.ToTitleCase(dsPatientDemographicDetails.Tables[0].Rows[0][(int)CrxDBGetPatientDetailsById.Gender].ToString().Trim().ToLower());
                        guicmbxGender.SelectedValue = tempGender.Trim().Equals(CrxStructCommonResourceMsg.MaleTxt) ? oMsgMgr.GetMessage(CrxStructCommonResourceMsg.MaleTxt) : oMsgMgr.GetMessage(CrxStructCommonResourceMsg.FemaleTxt);
                      
                        // smarajit
                                               
                        // display patients first & last name at bottom
                        objDefaultWindow.radlblPatientName.Text = !string.IsNullOrEmpty(guiradtxtFirstName.Text.Trim()) ? string.Format("{0} {1}", guiradtxtFirstName.Text.Trim(), guiradtxtLastName.Text.Trim()) : guiradtxtLastName.Text.Trim();

                        radlblpatientinternalnumber.Text = patientNumberInternal.ToString();
                        radlblgroupid.Text = groupId.ToString();

                        // intialize bizpatient object with selected record
                        BizPatient patientObj = BizPatient.Instance();
                        patientObj.dateOfBirth = DateTime.Parse(date.ToShortDateString());
                        patientObj.firstName = guiradtxtFirstName.Text.Trim();

                        // smarajit
                        patientObj.gender = guicmbxGender.Text.Trim().Equals(oMsgMgr.GetMessage(CrxStructCommonResourceMsg.MaleTxt)) ? CrxStructCommonResourceMsg.MaleTxt : CrxStructCommonResourceMsg.FemaleTxt;

                        // patientObj.gender = guicmbxGender.Text.Trim();
                        // smarajit
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
                        GuiCommon.ScorControllerObject.SetBloodPressure();
                        GuiCommon.ScorControllerObject.SetDistanceMethodAndUnits();
                        
                        FillSessionObjFromDB();
                        GuiCommon.IsFormChanged = false;
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
            if (string.Compare(guiradbtnExpander.Text, oMsgMgr.GetMessage(CrxStructCommonResourceMsg.ShowSmall), StringComparison.CurrentCultureIgnoreCase) == 0)
            {
                guiradbtnEdit.Enabled = false;
                guiradbtnDelete.Enabled = false;

                // Nitesh
                if (mode == CurrentMode.None)
                {
                    guiradbtnCancel.Enabled = false;
                }
                else
                {
                   // guiradbtnCancel.Enabled = true;
                    guiradbtnCancel.Enabled = guiradgrdPatientList.Rows.Count == 0 ? false : true;
                }

                // Nitesh
                objDefaultWindow.radlblPatientName.Visible = false;
            }
            else
            {
                if (mode == CurrentMode.InsertMode || mode == CurrentMode.EditMode || mode == CurrentMode.SearchMode)
                {
                    // Nitesh
                    // guiradbtnCancel.Enabled = true;
                    guiradbtnCancel.Enabled = guiradgrdPatientList.Rows.Count == 0 ? false : true;

                    // Nitesh
                    guiradbtnEdit.Enabled = false;
                    guiradbtnDelete.Enabled = false;
                    objDefaultWindow.radlblPatientName.Visible = false;
                }
                else
                {
                    guiradbtnEdit.Enabled = true;
                    guiradbtnDelete.Enabled = true;

                   // objDefaultWindow.radlblPatientName.Visible = true;
                    guiradbtnCancel.Enabled = false;                    
                }
            }
        }

        /** This method makes the Demographic details of the patient read only(browse mode) when true and vice versa.
         */
        private void BrowseMode(bool value)
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
                guiradbtnSearch.Enabled = guiradbtnExpander.Text.Equals(oMsgMgr.GetMessage(CrxStructCommonResourceMsg.HideCaps)) && guiradgrdPatientList.Rows.Count > 1;
                guiradbtnNew.Enabled = true;
                SetButtonsForHideMode();                   
                guipnlMeasurementDetails.Visible = true;              
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
                    // insert mode
                    guiradbtnCancel.Enabled = guiradgrdPatientList.Rows.Count == 0 ? false : true;
                    guiradbtnSave.Enabled = true;
                    objDefaultWindow.guiradmnuDatabase.Enabled = false;
                    guiradbtnSearch.Enabled = false;
                    guiradbtnEdit.Enabled = false;
                    guiradbtnDelete.Enabled = false;
                    guiradbtnNew.Enabled = false;
                }
                else if (mode == CurrentMode.EditMode)
                {
                    // edit mode
                    guiradbtnCancel.Enabled = true;
                    guiradbtnSave.Enabled = true;
                    guiradbtnSearch.Enabled = false;
                    guiradbtnEdit.Enabled = false;
                    guiradbtnDelete.Enabled = false;
                    guiradbtnNew.Enabled = false;

                    guipnlMeasurementDetails.Visible = false;
                }
                else if (mode == CurrentMode.SearchMode)
                {
                    // search mode
                    guiradbtnCancel.Enabled = true;
                    guiradbtnSave.Enabled = false;
                    guiradbtnSearch.Enabled = false;
                    guiradbtnEdit.Enabled = false;
                    guiradbtnDelete.Enabled = false;
                    guiradbtnNew.Enabled = false;
                    guipnlMeasurementDetails.Visible = false;
                    objDefaultWindow.guiradmnuDatabase.Enabled = false;
                }
                else
                {
                    // default
                    guiradbtnCancel.Enabled = true;
                    guiradbtnSave.Enabled = true;
                }               
            }
        }

        /** This method is called on the click of the Save button,it is used to validate the demograhic details entered by the user and save the same into the database.
         *Any expection thrown while saving the details into the database will be caught by the configuration file and logged. 
         *This expection will be shown to the user using a message box,also it will be logged into the log file.
        */
        private void guiradbtnSave_Click(object sender, EventArgs e)
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
                }

                // GuiCommon.IsFormChanged = false;
            }
            catch (Exception ex)
            {
                GUIExceptionHandler.HandleException(ex, this);
            }
        }

        /** This method is called when user tries to navigate to top menu before exiting the current mode other than browse mode
         * It will prompt user to save the changes when in Insert & Edit mode, and will ask user to exit search mode if on search mode
         * and then will navigate to menu options selected by user
         */
        private void SaveChangesForModes(object sender, EventArgs e)
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
                                                      
                            // disable capture & enable / disable  report tab based on measurement details
                            objDefaultWindow.radtabReport.Enabled = GuiCommon.HasMeasurementDetails;

                            // below line of code enables capture tab based on 30 sec wait interval imposed by EM4
                            // if IsWaitIntervalImposed is true then disable capture button & vice versa
                            if (GuiCommon.CurrentMode.Equals(CrxStructCommonResourceMsg.Pwv))
                            {
                            objDefaultWindow.radtabCapture.Enabled = !GuiCommon.IsWaitIntervalImposed;
                            }

                            break;
                        case DialogResult.No :
                            // do not exit search mode
                            GuiCommon.IsMenuItemShown = false;
                            break;

                            // added code for defect
                        case DialogResult.Cancel:
                            // do not exit search mode
                            GuiCommon.IsMenuItemShown = false;
                            break; 
                    }
                   
                    break;
                default:

                    // Check if there are any records in the patient list.
                    // There is a exception when the user is running the application on a fresh db,
                    // by default the setup screen goes into Insert mode,at this moment if user clicks on the menu bar he will be prompted to 
                    // save changes.This is not logical since he has not made any changes.
                    // Hence following condition is checked.
                    // if (guiradgrdPatientList.RowCount.Equals(0))
                    // {
                    // return;
                    // }

                    // this will handle saving the values in edit & insert mode before navigating to menu items
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
                            break;
                        default:
                            // Check if there are any records in the patient list.
                            // There is a exception when the user is running the application on a fresh db,
                            // by default the setup screen goes into Insert mode,at this moment if user clicks on the menu bar he will be prompted to 
                            // save changes.This is not logical since he has not made any changes.
                            // Hence following condition is checked.
                            if (guiradgrdPatientList.RowCount.Equals(0))
                            {
                               GuiCommon.IsPatientListEmpty = true;
                               return;
                            }

                            mode = CurrentMode.None;
                            DisplayLastRecord(int.Parse(radlblpatientinternalnumber.Text.Trim()), int.Parse(radlblgroupid.Text));

                            guiradgrdPatientList.Enabled = true;

                            // disable capture & enable / disable  report tab based on measurement details
                            objDefaultWindow.radtabReport.Enabled = GuiCommon.HasMeasurementDetails;

                            // below line of code enables capture tab based on 30 sec wait interval imposed by EM4
                            // if IsWaitIntervalImposed is true then disable capture button & vice versa
                            if (GuiCommon.CurrentMode.Equals(CrxStructCommonResourceMsg.Pwv))
                            {
                                objDefaultWindow.radtabCapture.Enabled = !GuiCommon.IsWaitIntervalImposed;
                            }

                            break;
                    }

                    break;            
            }            
        }

        /**This method checks if a given patient id exists,while adding a record.
         */
        private void CheckForPatientIdToAddPatient()
        {
            // check for db connection
            if (dbMagr.CheckConnection(serverNameString, crxMgrObject.GeneralSettings.SourceData) == 0)
            {
                // Commenting the following code,as per requirement change PWVSW-282 in ATCOR JIRA.
                // check if patient ID exists and add accordingly
                /*
                if (dbMagr.PatientIdExists(bobj, guiradtxtPatientID.Text.Trim()))
                {
                    DialogResult result = RadMessageBox.Show(oMsgMgr.GetMessage(CrxStructCommonResourceMsg.PatientAlreadyExist), oMsgMgr.GetMessage(CrxStructCommonResourceMsg.SystemError), MessageBoxButtons.YesNo);
                    if (result == DialogResult.Yes)
                    {
                        // add new patient record with duplicate/existing patient ID
                        AddNewPatientDetails();
                    }
                }
                */
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

        /**This method checks if a given patient id exists,while updating a record.
         */
        private void CheckForPatientIdToUpdatePatient()
        {
            // check for db connection
            if (dbMagr.CheckConnection(serverNameString, crxMgrObject.GeneralSettings.SourceData) == 0)
            {
                // check if old patient ID is changed
                if (string.Compare(orgPatientIdExt, guiradtxtPatientID.Text.Trim(), true, CultureInfo.CurrentCulture) != 0)
                {
                    /*
                    // check patient ID exists and update record accordingly
                    if (dbMagr.PatientIdExists(bobj, guiradtxtPatientID.Text.Trim()))
                    {
                        DialogResult result = RadMessageBox.Show(oMsgMgr.GetMessage(CrxStructCommonResourceMsg.PatientAlreadyExist), oMsgMgr.GetMessage(CrxStructCommonResourceMsg.SystemError), MessageBoxButtons.YesNo);
                        if (result == DialogResult.Yes)
                        {
                            // update patient record with duplicate/existing patient ID
                            UpdatePatientDetails();
                        }
                    }
                    else
                    {
                        // patient ID does not exists, update record
                        UpdatePatientDetails();
                    }
                    */
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

        /** This method is used to set the height weight units for PWV mode in the GUI depending on the settings selected by the user.
      */
        public void SetPwvHeightWeightUnits()
        {
            // read height and weight units and accordingly show units for height and weight.Convert values accordingly.
            // read the properties for the setting the units for measurement data.
            switch (crxMgrObject.GeneralSettings.HeightandWeightUnit)
            {
                case (int)CrxGenPwvValue.CrxGenHeightWeightMetric:

                    // metric units i.e cm and kg.
                    guiradlblHeightUnits.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.Cm);    
                
                    // guiradlblWeightUnits.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.Kg); 
                    guiradtxtImperialHeight.Visible = false;
                    guiradlblImperialHeight.Visible = false;
                    break;
                case (int)CrxGenPwvValue.CrxGenHeightWeightImperial:

                    // imperial units i.e ft and inches and lbs.
                    guiradlblHeightUnits.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.Feet);

                    // change cm to ft 
                    // show Inches.
                    guiradtxtImperialHeight.Visible = true;
                    guiradlblImperialHeight.Visible = true;

                    // change unit of weight to lbs.Commenting the following code as it is not required.
                    // guiradlblWeightUnits.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.Lbs); 
                     break;
                default:
                    break;
            }                        
        }

        // Begin: AtCor-<Drop2>-<Sprint3>, TM, <SWREQ2011>,<21 july 2011>
        /** This method is used to set the height weight units for PWA mode in the GUI depending on the settings selected by the user.
    */
        public void SetPwaHeightWeightUnits()
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

                    // change cm to ft 
                    // show Inches.
                    guiradtxtPWAImperialHeight.Visible = true;
                    guiradlblImperialHeightUnit.Visible = true;

                    // change unit of weight to lbs.Commenting the following code as it is not required.
                    // guiradlblWeightUnits.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.Lbs); 
                      break;
                default:
                    break;
            }
        }

        // End:AtCor-<Drop2>-<Sprint3>, TM, <SWREQ2011>,<21 july 2011>

        /** This method is used to set the blood pressure in the GUI depending on the settings selected by the user.
    */
        public void SetPwvBloodPressure()
        {
            // read blood pressure and accordingly display the combination of SP,DP and MP. 
            // Pritam
            // switch (crxMgrObject.GeneralSettings.BloodPressureEntryOptions)
            // switch (crxMgrObject.BpSettings.BloodPressure)
            // {
            //    case (int)CrxGenPwvValue.CrxGenBPOptSPandDP:
                    guiradlblSP.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.LabelSp);
                    guiradlblDP.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.LabelDp);

                ////   break;
                // case (int)CrxGenPwvValue.CrxGenBPOptSPandMP:
                //    // sp and mp
                //    guiradlblSP.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.LabelSp);

                //// change dp to mp
                //    guiradlblDP.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.LabelMp);
                //    break;
                // case (int)CrxGenPwvValue.CrxGenBPOptMPandDP:
                //    // mp and dp
                //    // sp to MP
                //    guiradlblSP.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.LabelMp);

                //// change dp tp DP
                //    guiradlblDP.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.LabelDp);
                //    break;
                // default:
                //    break;
            // }
        }

        /** This method is used to set the PWV distance methods/units in the GUI depending on the settings selected by the user.
    */
        public void SetPwvDistanceMethodAndUnits()
        {   
            // read pwv distance units and pwv distance method and accordingly dispaly the labels and textbox.Do the calculation of for PWV distance.Also read the cuff location for it to be editable or no. 
            switch (crxMgrObject.PwvSettings.PWVDistanceMethod)
            {
                case (int)CrxGenPwvValue.CrxPwvDistMethodSubtract:
                    guiradlblPwvDistanceMethod.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.SubtractingMethod);
                    Image imageSubtracting = Image.FromFile(ConfigurationManager.AppSettings[GuiConstants.AppConfigParams.SetupScreenSubtracting.ToString()]);
                    picbxPwvDisMthdImage.Image = imageSubtracting;
                    picbxPwvDisMthdImage.ImageLocation = ConfigurationManager.AppSettings[GuiConstants.AppConfigParams.SetupScreenSubtracting.ToString()];

                    // picbxPwvDisMthdImage.Height = imageSubtracting.Height;
                    // picbxPwvDisMthdImage.Width = imageSubtracting.Width;

                    // Set text for Cuff measurement label.
                   // guiradlblCuff.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.LblReportCuffWithcolon);

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

                   // picbxPwvDisMthdImage.Height = imageDirect.Height;
                   // picbxPwvDisMthdImage.Width = imageDirect.Width;

                  // guiradlblCuff.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.GuiDirect);
                  // guiradlblCuff.Tag = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.GuiDirect);
                    break;

                default:
                    break;
            }           
                        
            int value;
            switch (crxMgrObject.PwvSettings.PWVDistanceUnits)
            {
                case (int)CrxGenPwvValue.CrxPwvDistDistUnitsMM:
                    // mm
                    // value = FemoralToCuffDefaultMmValue;
                    value = int.Parse(crxMgrObject.PwvSettings.FemoralToCuff);   
                    guiradlblCarotidTonometerUnits.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.Mm);
                    guiradlblCuffunits.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.Mm);
                    guiradlblFemoralToCuffUnits.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.Mm);
                    if (!GuiCommon.IsOnReportForm)
                    {
                        guiradtxtFemoralToCuff.Text = value.ToString();
                    }

                    guiradlblPwvDistanceUnits.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.Mm);
                    break;
                case (int)CrxGenPwvValue.CrxPwvDistDistUnitsCM:
                    // cm                    
                   // value = FemoralToCuffDefaultCmValue;
                    value = int.Parse(crxMgrObject.PwvSettings.FemoralToCuff);   
                    guiradlblCarotidTonometerUnits.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.Cm);
                    guiradlblCuffunits.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.Cm);
                    guiradlblFemoralToCuffUnits.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.Cm);
                    if (!GuiCommon.IsOnReportForm)
                    {
                        guiradtxtFemoralToCuff.Text = value.ToString();
                    }                    

                    guiradlblPwvDistanceUnits.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.Cm);
                    break;

                default:
                    break;
            }            
        }

        /** This method is used to update the patient demographic details and save the same into the database.
    */
        private void UpdatePatientDetails()
        {
            try
            {
                // updates patient record
               // groupnamechange = !string.IsNullOrEmpty(guicmbGroup.Text) ? guicmbGroup.Text.Trim() : guicmbGroup.GetItemText(guicmbGroup.SelectedItem);
                SavePatient(string.Empty);                
            }
            catch (Exception ex)
            {
                GUIExceptionHandler.HandleException(ex, this);
            }
        }

        /** This method is used to save new group name.
         */
        private void AddNewPatientDetails()
        {
            try
            {
                // SavePatient(!string.IsNullOrEmpty(guicmbGroup.Text)
                //                ? guicmbGroup.Text
                //                : guicmbGroup.GetItemText(guicmbGroup.SelectedItem));
                SavePatient(string.Empty);                
            }
            catch (Exception ex)
            {
                GUIExceptionHandler.HandleException(ex, this);
            }
        }

        /** This method saves (insert or update) patient demographic data 
       */
        private void SavePatient(string groupname)
        {
            // saves patient record to database
            // check for db connection
            if (dbMagr.CheckConnection(serverNameString, crxMgrObject.GeneralSettings.SourceData) == 0)
            {
                // instantiate struct with values entered
                CrxStructPatientDemographicData patientData = new CrxStructPatientDemographicData
                                                                  {
                                                                      FirstName = guiradtxtFirstName.Text.Trim(),

                                                                      // Gender = guicmbxGender.Text.Trim(),
                                                                      Gender = guicmbxGender.Text.Trim().Equals(oMsgMgr.GetMessage(CrxStructCommonResourceMsg.MaleTxt)) ? CrxStructCommonResourceMsg.MaleTxt : CrxStructCommonResourceMsg.FemaleTxt,
                                                                      LastName = guiradtxtLastName.Text.Trim()
                                                                  };
                string dob = string.Format("{0}/{1}/{2}", guicmbDay.Text, guicmbxMonth.Text, guicmbxYear.Text);

                // since we are combining date string from three different combo boxes
                // using format provider to give culture specific dates
                IFormatProvider culture = new CultureInfo(CultureInfo.CurrentCulture.LCID);
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

        /** This method saves patient data 
         * */
        private void SavePatientData(CrxStructPatientDemographicData patientData)
        {
            int iRow = 0;

            // check if patient record exists and save accordingly
            if (mode == CurrentMode.InsertMode)
            {
                // insert new record when patient does not exists
                if (dbMagr.PatientRecordExists(patientData) == 0)
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
                // To validate duplicate record  while saving into the database.
                // insert new record when patient does not exists

                // commented for removing groupname condition
                // if (dbMagr.PatientRecordExists(patientData) == 2)
                // {
                //    RadMessageBox.Show(this, (oMsgMgr.GetMessage(CrxStructCommonResourceMsg.PatientAlreadyExistforGroup) + oMsgMgr.GetMessage(CrxStructCommonResourceMsg.GuiDisplaySingleQuote) + patientData.GroupName + oMsgMgr.GetMessage(CrxStructCommonResourceMsg.GuiDisplaySingleQuote)), oMsgMgr.GetMessage(CrxStructCommonResourceMsg.SystemError), MessageBoxButtons.OK, RadMessageIcon.Error);
                //    return;
                // }                

                // update patient record
                patientData.PatientNumberInternal = int.Parse(radlblpatientinternalnumber.Text);
                patientData.GroupIdentifier = int.Parse(radlblgroupid.Text);
                if (dbMagr.PatientRecordExists(patientData) == 0)
                {
                    iRow = dbMagr.UpdatePatientData(patientData, true);
                }
                else
                {
                    RadMessageBox.Show(this, oMsgMgr.GetMessage(CrxStructCommonResourceMsg.PatientAlreadyExists), oMsgMgr.GetMessage(CrxStructCommonResourceMsg.SystemError), MessageBoxButtons.OK, RadMessageIcon.Error);
                } 
            }

            if (iRow > 0)
            {
                DisplaySavedPatientData(patientData);
                GuiCommon.IsFormChanged = false;

                // UnSubscribeToTextChangedEvent();
            }
        }

        /** This method displays data for patient being saved currently 
       * */
        private void DisplaySavedPatientData(CrxStructPatientDemographicData patientData)
        {
            // if record added / updated successfully 
            guipnlMeasurementDetails.Visible = true;
            if (GuiCommon.CurrentMode.Equals(CrxStructCommonResourceMsg.Pwv))
            {
            objDefaultWindow.radtabCapture.Enabled = guiradbtnCapture.Enabled = !GuiCommon.IsWaitIntervalImposed;
            }

            GuiCommon.ScorControllerObject.SetHeightWeightUnits();
            GuiCommon.ScorControllerObject.SetBloodPressure();
            GuiCommon.ScorControllerObject.SetDistanceMethodAndUnits();

            LoadPatientList();
            guiradgrdPatientList.Enabled = true;

            // added for regression defect
            objDefaultWindow.guicmbxCurrentMode.Enabled = true;
        }

        /** This method is called when the user clicks on the New button in the GUI.The user can enter new patient details.
        */
        private void guiradbtnNew_Click(object sender, EventArgs e)
        {
            isSearchOn = false;

            // set the focus to the Patient Id field.
            guiradtxtPatientID.Focus();
            guipnlMeasurementDetails.Visible = false;

            mode = CurrentMode.InsertMode;
            ResetFields();
            BrowseMode(false);
           
            FillDay(0);

            guiradgrdPatientList.Enabled = false;

            // disable capture & report tab in insert mode
            objDefaultWindow.radtabReport.Enabled = false;
            objDefaultWindow.radtabCapture.Enabled = false;

            objDefaultWindow.radlblMessage.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.InsertMode);
            objDefaultWindow.radlblPatientName.Text = string.Empty;

            GuiCommon.IsFormChanged = true;

            // SubscribeToTextChangedEvent();
        }

        /** This method is called when the user clicks on the Search button in the GUI.
         * It searches patient from gridview based on criteria given
        */
        private void guiradbtnSearch_Click(object sender, EventArgs e)
        {
            isSearchOn = false;
            guiradtxtPatientID.Focus();
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
                     * */
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
                    guicmbxMonth.SelectedIndex = 0;
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
                    guicmbxMonth.SelectedIndex = 0;                                     
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
                GUIExceptionHandler.HandleException(ex, this);
            }
        }

        /** This method is used to fill days into the combo box in the GUI.It is called on the FormLoad event.
        */
        private void FillDay(int lastDay)
        {
            try
            {
                int selectedvaue = 0;

                // retrieve the selected index
                if (guicmbDay.SelectedIndex > 0)
                {
                    selectedvaue = guicmbDay.SelectedIndex;
                }

                // clear items in combo box
                guicmbDay.Items.Clear();

                // set to 31 if lastday is 0
                if (lastDay == 0)
                {
                    lastDay = 31;
                }

                guicmbDay.Items.Add(oMsgMgr.GetMessage(CrxStructCommonResourceMsg.Day));

                // Fill day dropdown.
                for (int day = 1; day <= lastDay; day++)
                {
                    guicmbDay.Items.Add(day.ToString());
                }              

                // in case last day is less than previous selected value in combo box, set selected index to last day
                guicmbDay.SelectedIndex = selectedvaue > lastDay ? lastDay : selectedvaue;
            }
            catch (Exception ex)
            {
                GUIExceptionHandler.HandleException(ex, this);
            }
        }      

        /** This method Bind days for month as per month selected in drop down
         * */
        private void BindDaysForMonthSelected()
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

        /** This method is called to check if a year is leap year,if so accordingly the combobox values for the Months and Day are changed.
        */
        private void FillDayLeapYear()
        {
            try
            {
                // checks if year selected is leap year and calls fillday method to bind days
                if (guicmbxYear.SelectedIndex > 0)
                {
                   // FillDay(DateTime.IsLeapYear(int.Parse(guicmbxYear.GetItemText(guicmbxYear.SelectedItem))) ? 29 : 28);
                    FillDay(DateTime.IsLeapYear(int.Parse(guicmbxYear.SelectedItem.Text)) ? 29 : 28);
                }
                else
                {
                    FillDay(28);
                }
            }
            catch (Exception ex)
            {
                GUIExceptionHandler.HandleException(ex, this);
            }
        }

        /** This method is called to reset the dempgraphic data fields in the GUI
         */
        private void ResetFields()
        {
            // to reset all input fields            
            guiradtxtPatientID.Text = string.Empty;
            guiradtxtLastName.Text = string.Empty;
            guiradtxtFirstName.Text = string.Empty;
            guicmbDay.SelectedIndex = 0;
            guicmbGroup.DataSource = null;
            guicmbGroup.Items.Clear();
            LoadGroupNames();
            guicmbxGender.SelectedIndex = 0;
            guicmbxMonth.SelectedIndex = 0;
            guicmbxYear.SelectedIndex = 0;
        }

        /**This method is called to validate the demographic details entered by the user.
         */
        private bool ValidateDemographicDetails()
        {
            // validates mandatory demographic fields
            bool flag = true;
            if (guiradtxtLastName.Text.Trim().CompareTo(string.Empty) == 0)
            {
                flag = false;
                RadMessageBox.Show(oMsgMgr.GetMessage(CrxStructCommonResourceMsg.EnterLastName), oMsgMgr.GetMessage(CrxStructCommonResourceMsg.SystemError), MessageBoxButtons.OK);
            }
            else if (guicmbDay.SelectedIndex == 0 || guicmbxMonth.SelectedIndex == 0 || guicmbxYear.SelectedIndex == 0)
            {
                flag = false;
                RadMessageBox.Show(oMsgMgr.GetMessage(CrxStructCommonResourceMsg.SelectDob), oMsgMgr.GetMessage(CrxStructCommonResourceMsg.SystemError), MessageBoxButtons.OK);
            }
            else if (guicmbxGender.SelectedIndex == 0)
            {
                flag = false;
                RadMessageBox.Show(oMsgMgr.GetMessage(CrxStructCommonResourceMsg.SelectGender), oMsgMgr.GetMessage(CrxStructCommonResourceMsg.SystemError), MessageBoxButtons.OK);
            }

            GuiCommon.IsMenuItemShown = flag;
            GuiCommon.ExitApp = flag ? 0 : 1;
            return flag;
        }

        /**This event is called when the user clicks on the Edit button in the GUI.The user can now edit th demographic details of the selected patient.
        */
        private void guiradbtnEdit_Click(object sender, EventArgs e)
        {
            isSearchOn = false;
            guiradtxtPatientID.Focus();

            // brings the screen to input mode
            // guiradlblNumberOfPatients.Text is commented because according to new requirement label is not needed anymore
            // if (int.Parse(guiradlblNumberOfPatients.Text.Trim()) != 0)
           // {
                mode = CurrentMode.EditMode;
                BrowseMode(false);
                objDefaultWindow.radlblMessage.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.EditMode);

                guiradgrdPatientList.Enabled = false;
                guipnlMeasurementDetails.Visible = false;

                // added for regression defect
                objDefaultWindow.guicmbxCurrentMode.Enabled = false;

                // disable capture & report tab in edit mode
                objDefaultWindow.radtabReport.Enabled = false;
                objDefaultWindow.radtabCapture.Enabled = false;

                GuiCommon.IsFormChanged = true;

                // SubscribeToTextChangedEvent();

            // }
            // else
            // {
            //    RadMessageBox.Show(oMsgMgr.GetMessage(CrxStructCommonResourceMsg.NoRecordsToEdit), oMsgMgr.GetMessage(CrxStructCommonResourceMsg.SystemError), MessageBoxButtons.OK);
            // }
        }

        /** This method is called when a user selects a record from the patient list and clicks on Delete button. The user is asked for the confirmation whether he wants to delete the record.If yes the record is deleted from the database.
         */
        private void guiradbtnDelete_Click(object sender, EventArgs e)
        {
            try
            {
                isSearchOn = false;

                // deletes patient from database for patient with 1 relation in patient group relation, else deletes relation of patient with that group from patient group relation table
                // guiradlblNumberOfPatients.Text is commented because according to new requirement label is not needed anymore
                // if (int.Parse(guiradlblNumberOfPatients.Text.Trim()) != 0)
                // {
                    CrxStructPatientDemographicData patientDemographicData = new CrxStructPatientDemographicData();
                    
                    GridViewRowInfo row = guiradgrdPatientList.CurrentRow;
                    patientDemographicData.PatientNumberInternal = int.Parse(row.Cells[1].Value.ToString());
                    patientDemographicData.GroupIdentifier = int.Parse(row.Cells[2].Value.ToString());
                    patientDemographicData.SystemIdentifier = bobj;

                    DialogResult ds = RadMessageBox.Show(this, oMsgMgr.GetMessage(CrxStructCommonResourceMsg.DeletePateint), oMsgMgr.GetMessage(CrxStructCommonResourceMsg.SystemError), MessageBoxButtons.YesNo, RadMessageIcon.Question);

                    if (ds == DialogResult.Yes)
                    {
                        if (dbMagr.CheckConnection(serverNameString, crxMgrObject.GeneralSettings.SourceData) == 0)
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
                
                // else
                // {
                //    RadMessageBox.Show(oMsgMgr.GetMessage(CrxStructCommonResourceMsg.NoRecordsToDelete), oMsgMgr.GetMessage(CrxStructCommonResourceMsg.SystemError), MessageBoxButtons.OK);
                // }
            }
            catch (Exception ex)
            {
                GUIExceptionHandler.HandleException(ex, this);
            }
        }

        /** This event gets fired when focus is moved from text box which takes cuff or direct values.
      * It checks if the value entered in textbox is within valid range and shows error accordingly
      * */
        private void guiradtxtCuff_Leave(object sender, EventArgs e)
        {
            objValidation.CheckFieldLimits(guiradtxtCuff);
            EnableCaptureAndCalculatePwvDistance();
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
                GUIExceptionHandler.HandleException(ex, this);
            }
        }

        /** This event gets fired when focus is moved from text box which takes carotid.
       * It checks if the value entered in textbox is within valid range and shows error accordingly
       * */
        private void guiradtxtCarotid_Leave(object sender, EventArgs e)
        {
            objValidation.CheckFieldLimits(guiradtxtCarotid);
            EnableCaptureAndCalculatePwvDistance();
        }

        /** This event gets fired when focus is moved from text box which takes femoral.
      * It checks if the value entered in textbox is within valid range and shows error accordingly
      * */
        private void guiradtxtFemoralToCuff_Leave(object sender, EventArgs e)
        {
            objValidation.CheckFieldLimits(guiradtxtFemoralToCuff);
            EnableCaptureAndCalculatePwvDistance();
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

                // UnSubscribeToTextChangedEvent();
                if (mode == CurrentMode.InsertMode)
                {
                    // insert mode
                    LoadPatientList();
                }
                else if (mode == CurrentMode.EditMode)
                {
                    // edit mode
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
                objDefaultWindow.radtabReport.Enabled = GuiCommon.HasMeasurementDetails;

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
                 * */
                DataSet dsSearch = (DataSet)AppDomain.CurrentDomain.GetData("cachePatient");
                if (dsSearch.Tables[0].Rows.Count > 0)
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
                    if (dvSearch.Count == 1)
                    {
                        // dvSearch.AllowEdit = true;
                        prevMode = CurrentMode.SearchMode;
                        mode = CurrentMode.None;
                        DisplayLastRecord(int.Parse(guiradgrdPatientList.Rows[0].Cells[1].Value.ToString()), int.Parse(guiradgrdPatientList.Rows[0].Cells[2].Value.ToString()));
                        guiradbtnSearch.Enabled = true;
                        guiradbtnCancel.Enabled = true;
                    }
                    else if (dvSearch.Count > 1)
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
                GUIExceptionHandler.HandleException(ex, this);
            }
        }

        /** This event is fired on the text changed of the PatientId field.
         */
        private void guiradtxtPatientID_TextChanged(object sender, EventArgs e)
        {
            // gets patient records based on inputs given
            if (!IsFieldsBlank(false) && mode == CurrentMode.SearchMode)
            {
                GetSearchResults();
            }

            guilblPatientIdDisplay.Text = guiradtxtPatientID.Text;
        }

        /** This method gets filtered search result & binds it to grid view.
        */
        private void GetSearchResults()
        {
            try
            {
                string dob = string.Empty, gender = string.Empty, groupname = string.Empty;

                // get date of birth value
                if (guicmbDay.SelectedIndex > 0 && guicmbxMonth.SelectedIndex > 0 && guicmbxYear.SelectedIndex > 0)
                {
                    // dob = string.Format("{0}/{1}/{2}", guicmbxMonth.GetItemText(guicmbDay.SelectedItem), guicmbDay.GetItemText(guicmbxMonth.SelectedItem), guicmbxYear.GetItemText(guicmbxYear.SelectedItem));
                   //  dob = string.Format("{0}/{1}/{2}", guicmbxMonth.GetItemText(guicmbDay.SelectedItem), guicmbxMonth.SelectedItem, guicmbxYear.GetItemText(guicmbxYear.SelectedItem));
                    dob = string.Format("{0}/{1}/{2}", guicmbDay.SelectedItem, guicmbxMonth.SelectedItem, guicmbxYear.SelectedItem);
                }

                // get selected item from gender drop down
                if (!string.IsNullOrEmpty(guicmbxGender.Text.Trim()) && !guicmbxGender.Text.Trim().ToLower().Contains(oMsgMgr.GetMessage(CrxStructCommonResourceMsg.SelectSmall)))
                {
                    // smarajit
                    // gender = guicmbxGender.Text.Trim();
                    gender = guicmbxGender.Text.Trim().Equals(oMsgMgr.GetMessage(CrxStructCommonResourceMsg.MaleTxt)) ? CrxStructCommonResourceMsg.MaleTxt : CrxStructCommonResourceMsg.FemaleTxt;
                   
                    // smarajit
                }
                else if (guicmbxGender.SelectedIndex > 0)
                {
                    // gender = guicmbxGender.SelectedItem.ToString().Trim();
                    gender = guicmbxGender.SelectedItem.ToString().Trim().Equals(oMsgMgr.GetMessage(CrxStructCommonResourceMsg.MaleTxt)) ? CrxStructCommonResourceMsg.MaleTxt : CrxStructCommonResourceMsg.FemaleTxt;
                }

                // if (!guicmbGroup.Text.ToLower().Contains(oMsgMgr.GetMessage(CrxStructCommonResourceMsg.SelectSmall)))
                // {
                //    groupname = guicmbGroup.Text;
                // }

                // binds search results to grid
                BindSearchResults(guiradtxtPatientID.Text.Trim(), guiradtxtLastName.Text.Trim(), guiradtxtFirstName.Text.Trim(), gender, dob, groupname);
            }
            catch (Exception ex)
            {
                GUIExceptionHandler.HandleException(ex, this);
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
            // gets patient records based on inputs given for first name
            if (!IsFieldsBlank(false) && mode == CurrentMode.SearchMode)
            {
                GetSearchResults();
            }

            guilblFirstnameDisplay.Text = guiradtxtFirstName.Text;                                       
        }      

        /** This event is fired on the text changed of the LastName field.
        */
        private void guiradtxtLastName_TextChanged(object sender, EventArgs e)
        {
            // gets patient records based on inputs given for last name
            if (!IsFieldsBlank(true) && mode == CurrentMode.SearchMode)
            {
                GetSearchResults();
            }
           
            guilblLastNameDisplay.Text = guiradtxtLastName.Text;            
        }

        /** This method is used to check if a field is blank or no while fetching search results.
        */
        private bool IsFieldsBlank(bool mandatory)
        {
            bool flag = true;

            // sets flag according to mandatory fields required 
            if (!isSearchReset)
            {
                flag = mandatory && CheckForMandatoryFields();
            }

            return flag;
        }

        /** This method checks for mandatory fields for patient demographic details and accordingly returns value
         * */
        private bool CheckForMandatoryFields()
        {
            bool flag;
            if (guicmbDay.SelectedIndex > 0 && guicmbxMonth.SelectedIndex > 0 && guicmbxYear.SelectedIndex > 0)
            {
                // (!string.IsNullOrEmpty(guicmbGroup.Text.Trim()) && !guicmbGroup.Text.ToLower().Trim().Contains(oMsgMgr.GetMessage(CrxStructCommonResourceMsg.SelectSmall))) ? false :
                flag = !string.IsNullOrEmpty(guiradtxtLastName.Text.Trim()) ? false : (guicmbDay.SelectedIndex > 0 && guicmbxMonth.SelectedIndex > 0 && guicmbxYear.SelectedIndex > 0) ? false : guicmbxGender.SelectedIndex > 0 ? false : true;
            }
            else
            {
                flag = false;
            }

            return flag;
        }

        /** This event is fired when the user tries to change the width of the column of the grid view.
          */
        private void guiradgrdPatientList_ColumnWidthChanging(object sender, ColumnWidthChangingEventArgs e)
        {
            // cancels changing column width
            if (!isCellInitializeWidth)
            {
                e.Cancel = true;
            }
        }

        /** This event is fired when the user tries to right click on the grid view.
       */
        private void guiradgrdPatientList_ContextMenuOpening(object sender, ContextMenuOpeningEventArgs e)
        {
            // suppresses context menu appearing after right click on grid view header
            e.Cancel = true;
        }

        /** This event is fired when the user tries to change the height of the row of the grid view.
        */
        private void guiradgrdPatientList_RowHeightChanging(object sender, RowHeightChangingEventArgs e)
        {
            // cancels changing row height
            e.Cancel = true;
        }

        /** This method is used to populate the session object with the database values.
        */
        private void FillSessionObjFromDB()
        {
            // check db connection
            if (dbMagr.CheckConnection(serverNameString, crxMgrObject.GeneralSettings.SourceData) == 0)
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

        /** Begin: AtCor-Drop2-Sprint3, TM, SWREQ2011,21 july 2011
          /** This method fills PWA measurement details from DB in Bizsession
      * */
        public void FillPwaDetailsSession()
        {
            DataSet dsPwv = dbMagr.GetCuffPWAMeasurementDetails(int.Parse(radlblpatientinternalnumber.Text.Trim()), int.Parse(radlblgroupid.Text), bobj);
            
            if (dsPwv.Tables[0].Rows.Count > 0)
            {
                GuiCommon.HasMeasurementDetails = true;

                GuiCommon.PwvCurrentStudyDatetime = dsPwv.Tables[0].Rows[0][(int)CrxDBGetCuffPWAMeasurementDetails.StudyDateTime].ToString();

                FillPwaSessionData(dsPwv);

                // filling RHS pwv measurement data on setup screen 
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
            else
            {
                // disable report and capture tab if measurement data not available for patient
                objDefaultWindow.radtabReport.Enabled = false;

                // below line of code enables capture tab based on 30 sec wait interval imposed by EM4
                // if IsWaitIntervalImposed is true then disable capture button & vice versa
               // objDefaultWindow.radtabCapture.Enabled = !GuiCommon.IsWaitIntervalImposed;
                GuiCommon.HasMeasurementDetails = false;
                GuiCommon.PwvCurrentStudyDatetime = string.Empty;

                // resets PWV fields on setup screen RHS
                ResetPatientMeasurementFields();
            }
        }        

        /** This method is used calculate the metric conversion for height.
        */ 
        private void PerformHeightMetricConversion(ref int heightInCentiConversion)
        {
            heightInCentiConversion = GuiCommon.bizObject.heightAndWeight.heightInCentimetres.ToString().Equals(GuiConstants.DefaultValue.ToString()) ? 0 : int.Parse(GuiCommon.bizObject.heightAndWeight.heightInCentimetres.ToString());
        }

        /** This method is used calculate the Imperial conversion for height.
       */
        private void PerformHeightImperialConversion(ref int heightInFeetConversion, ref int heightInInchConversion)
        {
            heightInInchConversion = int.Parse(GuiCommon.bizObject.heightAndWeight.heightInInches.ToString()) % 12;
            heightInFeetConversion = int.Parse(GuiCommon.bizObject.heightAndWeight.heightInInches.ToString()) / 12;
        }

        /** This method is used calculate the metric conversion for height for pwa mode.
       */
        private void PerformPwaHeightMetricConversion(ref int heightInCentiConversion)
        {
            heightInCentiConversion = GuiCommon.bizPwaobject.heightAndWeight.heightInCentimetres.ToString().Equals(GuiConstants.DefaultValue.ToString()) ? 0 : int.Parse(GuiCommon.bizPwaobject.heightAndWeight.heightInCentimetres.ToString());
        }

        /** This method is used calculate the Imperial conversion for height for pwa mode.
       */
        private void PerformPwaHeightImperialConversion(ref int heightInFeetConversion, ref int heightInInchConversion)
        {
            heightInInchConversion = int.Parse(GuiCommon.bizPwaobject.heightAndWeight.heightInInches.ToString()) % 12;
            heightInFeetConversion = int.Parse(GuiCommon.bizPwaobject.heightAndWeight.heightInInches.ToString()) / 12;
        }

        // End : AtCor-<Drop2>-<Sprint3>, TM, <SWREQ2011>,<21 july 2011>

        /** This method fills PWV measurement details from DB in Bizsession
         * */
        public void FillPwvDetailsSession()
        {                
            DataSet dsPwv = dbMagr.GetPWVMeasurementDetails(int.Parse(radlblpatientinternalnumber.Text.Trim()), int.Parse(radlblgroupid.Text), bobj);
            if (dsPwv.Tables[0].Rows.Count > 0)
            {
                GuiCommon.HasMeasurementDetails = true;

                GuiCommon.PwvCurrentStudyDatetime = dsPwv.Tables[0].Rows[0][(int)CrxDBPWVMeasurementTableList.StudyDateTime].ToString();
                
                FillSessionData(dsPwv);

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

                guiradtxtOperator.Text = dsPwv.Tables[0].Rows[0][(int)CrxDBPWVMeasurementTableList.Operator].ToString();
                guiradtxtMedication.Text = dsPwv.Tables[0].Rows[0][(int)CrxDBPWVMeasurementTableList.Notes].ToString();                              
                                
                // switch (crxMgrObject.GeneralSettings.BloodPressureEntryOptions)
                // switch (crxMgrObject.BpSettings.BloodPressure)
                // {
                //    // converting to int as crxMgrObject.GeneralSettings.BloodPressureEntryOptions returns int
                //    case (int)CrxGenPwvValue.CrxGenBPOptSPandDP: 
                      guiradtxtSP.Text = dsPwv.Tables[0].Rows[0][(int)CrxDBPWVMeasurementTableList.SP].ToString().Equals(GuiConstants.DefaultValue.ToString()) ? string.Empty : dsPwv.Tables[0].Rows[0][(int)CrxDBPWVMeasurementTableList.SP].ToString();
                     guiradtxtDP.Text = dsPwv.Tables[0].Rows[0][(int)CrxDBPWVMeasurementTableList.DP].ToString().Equals(GuiConstants.DefaultValue.ToString()) ? string.Empty : dsPwv.Tables[0].Rows[0][(int)CrxDBPWVMeasurementTableList.DP].ToString();
                ////        break;
                //    case (int)CrxGenPwvValue.CrxGenBPOptSPandMP:
                //        guiradtxtSP.Text = dsPwv.Tables[0].Rows[0][(int)CrxDBPWVMeasurementTableList.SP].ToString().Equals(GuiConstants.DefaultValue.ToString()) ? string.Empty : dsPwv.Tables[0].Rows[0][(int)CrxDBPWVMeasurementTableList.SP].ToString();
                //        guiradtxtDP.Text = dsPwv.Tables[0].Rows[0][(int)CrxDBPWVMeasurementTableList.MP].ToString().Equals(GuiConstants.DefaultValue.ToString()) ? string.Empty : dsPwv.Tables[0].Rows[0][(int)CrxDBPWVMeasurementTableList.MP].ToString();
                //        break;
                //    case (int)CrxGenPwvValue.CrxGenBPOptMPandDP:
                //        guiradtxtSP.Text = dsPwv.Tables[0].Rows[0][(int)CrxDBPWVMeasurementTableList.MP].ToString().Equals(GuiConstants.DefaultValue.ToString()) ? string.Empty : dsPwv.Tables[0].Rows[0][(int)CrxDBPWVMeasurementTableList.MP].ToString();
                //        guiradtxtDP.Text = dsPwv.Tables[0].Rows[0][(int)CrxDBPWVMeasurementTableList.DP].ToString().Equals(GuiConstants.DefaultValue.ToString()) ? string.Empty : dsPwv.Tables[0].Rows[0][(int)CrxDBPWVMeasurementTableList.DP].ToString();
                //        break;
                //    default:
                //        guiradtxtSP.Text = string.Empty;
                //        guiradtxtDP.Text = string.Empty;
                //        break;
                // }            
                 guiradtxtCuff.Text = dsPwv.Tables[0].Rows[0][(int)CrxDBPWVMeasurementTableList.Carotid].ToString().Equals(GuiConstants.DefaultValue.ToString()) ? dsPwv.Tables[0].Rows[0][(int)CrxDBPWVMeasurementTableList.Direct].ToString() : dsPwv.Tables[0].Rows[0][(int)CrxDBPWVMeasurementTableList.Cuff].ToString().Equals(GuiConstants.DefaultValue.ToString()) ? string.Empty : dsPwv.Tables[0].Rows[0][(int)CrxDBPWVMeasurementTableList.Cuff].ToString();
                guiradtxtCarotid.Text = dsPwv.Tables[0].Rows[0][(int)CrxDBPWVMeasurementTableList.Carotid].ToString().Equals(GuiConstants.DefaultValue.ToString()) ? string.Empty : dsPwv.Tables[0].Rows[0][(int)CrxDBPWVMeasurementTableList.Carotid].ToString();
                              
               // guiradtxtFemoralToCuff.Text = femoralValue.Length == 0 ? femoralValue : crxMgrObject.PwvSettings.PWVDistanceUnits.Equals((int)CrxGenPwvValue.CrxPwvDistDistUnitsMM) ? femoralValue : Convert.ToString((int.Parse(femoralValue) / 10));
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
            }
        }

        /** This method initializes biz session object each time a patient record is selected/edited/added for pwv mode
        */
        private void FillSessionData(DataSet dsPwv)
        {
            FillSessionWithBloodPressureValues(dsPwv);
            FillSessionWithOtherValues(dsPwv);

            GuiCommon.bizObject.systemId = (uint)bobj;
            GuiCommon.bizObject.groupStudyId = (uint)GuiCommon.GroupId;

            objDefaultWindow.radtabReport.Enabled = true;
            objDefaultWindow.radtabCapture.Enabled = !GuiCommon.IsWaitIntervalImposed;
            GuiCommon.bizObject.patientNumber = (uint)GuiCommon.PatientInternalNumber;           
        }

         /** This method initializes biz session object each time a patient record is selected/edited/added for pwa mode
        */      
        private void FillPwaSessionData(DataSet dsPwv)
        {
            FillPwaSessionWithBloodPressureValues(dsPwv);
            FillPwaSessionWithOtherValues(dsPwv);

            GuiCommon.bizPwaobject.systemId = (uint)bobj;
            GuiCommon.bizPwaobject.groupStudyId = (uint)GuiCommon.GroupId;

            objDefaultWindow.radtabReport.Enabled = true;

            // objDefaultWindow.radtabCapture.Enabled = !GuiCommon.IsWaitIntervalImposed;
            GuiCommon.bizPwaobject.patientNumber = (uint)GuiCommon.PatientInternalNumber;
        }

        /** This method fills session with height & weight, distance values for pwa mode
        * */
        private void FillPwaSessionWithOtherValues(DataSet dsPwv)
        {
            GuiCommon.bizPwaobject.heightAndWeight.heightInCentimetres = string.IsNullOrEmpty(dsPwv.Tables[0].Rows[0][(int)CrxDBGetCuffPWAMeasurementDetails.HeightInCentimetres].ToString()) ? GuiCommon.bizPwaobject.heightAndWeight.heightInCentimetres : ushort.Parse(dsPwv.Tables[0].Rows[0][(int)CrxDBGetCuffPWAMeasurementDetails.HeightInCentimetres].ToString());
            GuiCommon.bizPwaobject.heightAndWeight.heightInInches = string.IsNullOrEmpty(dsPwv.Tables[0].Rows[0][(int)CrxDBGetCuffPWAMeasurementDetails.HeightInInches].ToString()) ? GuiCommon.bizPwaobject.heightAndWeight.heightInInches : ushort.Parse(dsPwv.Tables[0].Rows[0][(int)CrxDBGetCuffPWAMeasurementDetails.HeightInInches].ToString());
            GuiCommon.bizPwaobject.heightAndWeight.weightInKilograms = string.IsNullOrEmpty(dsPwv.Tables[0].Rows[0][(int)CrxDBGetCuffPWAMeasurementDetails.WeightInKilograms].ToString()) ? GuiCommon.bizPwaobject.heightAndWeight.weightInKilograms : ushort.Parse(dsPwv.Tables[0].Rows[0][(int)CrxDBGetCuffPWAMeasurementDetails.WeightInKilograms].ToString());
            GuiCommon.bizPwaobject.heightAndWeight.weightInPounds = string.IsNullOrEmpty(dsPwv.Tables[0].Rows[0][(int)CrxDBGetCuffPWAMeasurementDetails.WeightInPounds].ToString()) ? GuiCommon.bizPwaobject.heightAndWeight.weightInPounds : ushort.Parse(dsPwv.Tables[0].Rows[0][(int)CrxDBGetCuffPWAMeasurementDetails.WeightInPounds].ToString());
            GuiCommon.bizPwaobject.notes = dsPwv.Tables[0].Rows[0][(int)CrxDBGetCuffPWAMeasurementDetails.Notes].ToString();
            GuiCommon.bizPwaobject.operatorId = dsPwv.Tables[0].Rows[0][(int)CrxDBGetCuffPWAMeasurementDetails.Operator].ToString();
            GuiCommon.bizPwaobject.heightAndWeight.bodyMassIndex = string.IsNullOrEmpty(dsPwv.Tables[0].Rows[0][(int)CrxDBGetCuffPWAMeasurementDetails.BodyMassIndex].ToString()) ? 0 : float.Parse(dsPwv.Tables[0].Rows[0][(int)CrxDBGetCuffPWAMeasurementDetails.BodyMassIndex].ToString());         
        }

        /** This method fills session with blood pressure values for pwa mode
         * */
        private void FillPwaSessionWithBloodPressureValues(DataSet dsPwv)
        {
            GuiCommon.bizPwaobject.bloodPressureEntryOption = string.IsNullOrEmpty(dsPwv.Tables[0].Rows[0][(int)CrxDBGetCuffPWAMeasurementDetails.BloodPressureEntryOption].ToString()) ? (ushort)0 : ushort.Parse(dsPwv.Tables[0].Rows[0][(int)CrxDBPWVMeasurementTableList.BloodPressureEntryOption].ToString());
            GuiCommon.bizPwaobject.bloodPressure.SP.Reading = ushort.Parse(dsPwv.Tables[0].Rows[0][(int)CrxDBGetCuffPWAMeasurementDetails.SP].ToString());
            GuiCommon.bizPwaobject.bloodPressure.DP.Reading = ushort.Parse(dsPwv.Tables[0].Rows[0][(int)CrxDBGetCuffPWAMeasurementDetails.DP].ToString());            
        }

        /** This method fills session with height & weight, distance values for pwv mode
         * */
        private void FillSessionWithOtherValues(DataSet dsPwv)
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

        /** This method fills session with blood pressure values for pwv mode
         * */
        private void FillSessionWithBloodPressureValues(DataSet dsPwv)
        {
            GuiCommon.bizObject.bloodPressureEntryOption = string.IsNullOrEmpty(dsPwv.Tables[0].Rows[0][(int)CrxDBPWVMeasurementTableList.BloodPressureEntryOption].ToString()) ? (ushort)0 : ushort.Parse(dsPwv.Tables[0].Rows[0][(int)CrxDBPWVMeasurementTableList.BloodPressureEntryOption].ToString());
              
            // switch (obj.bloodPressureEntryOption)
            // {
            //    // converting to ushort as obj.bloodPressureEntryOption returns ushort
            //    case (ushort)CrxGenPwvValue.CrxGenBPOptSPandDP:
            GuiCommon.bizObject.bloodPressure.SP.Reading = ushort.Parse(dsPwv.Tables[0].Rows[0][(int)CrxDBPWVMeasurementTableList.SP].ToString());
            GuiCommon.bizObject.bloodPressure.DP.Reading = ushort.Parse(dsPwv.Tables[0].Rows[0][(int)CrxDBPWVMeasurementTableList.DP].ToString());
            ////        break;
            //    case (ushort)CrxGenPwvValue.CrxGenBPOptSPandMP:
            //        obj.bloodPressure.SP.Reading = ushort.Parse(dsPwv.Tables[0].Rows[0][(int)CrxDBPWVMeasurementTableList.SP].ToString());
            //        obj.bloodPressure.MP.Reading = ushort.Parse(dsPwv.Tables[0].Rows[0][(int)CrxDBPWVMeasurementTableList.MP].ToString());
            //        break;
            //    case (ushort)CrxGenPwvValue.CrxGenBPOptMPandDP:
            //        obj.bloodPressure.MP.Reading = ushort.Parse(dsPwv.Tables[0].Rows[0][(int)CrxDBPWVMeasurementTableList.MP].ToString());
            //        obj.bloodPressure.DP.Reading = ushort.Parse(dsPwv.Tables[0].Rows[0][(int)CrxDBPWVMeasurementTableList.DP].ToString());
            //        break;
            //    default:
            //        break;
            // }
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

                   // guiradtxtWeight.Text = obj.heightAndWeight.weightInKilograms.ToString().Equals(GuiConstants.DefaultValue.ToString()) ? string.Empty : obj.heightAndWeight.weightInKilograms.ToString();
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

                   // guiradtxtWeight.Text = obj.heightAndWeight.weightInPounds.Equals(GuiConstants.DefaultValue) ? string.Empty : obj.heightAndWeight.weightInPounds.ToString();
                    break;
                default:
                    break;
            }
        }

        /** This event fires when enable property of guicmbday combo box changes
        */
        private void guicmbDay_EnabledChanged(object sender, EventArgs e)
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
     
        /** This event fires when enable property of guicmbxGender combo box changes
        */
        private void guicmbxGender_EnabledChanged(object sender, EventArgs e)
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

        /**This method is used to read the General and PWV settings from the configuration manager.
       */
        private void ReadSettings()
        {
            crxMgrObject.GetGeneralUserSettings();
            crxMgrObject.GetPwvUserSettings();
        }

        /** This event fires when enable property of guiradtxtPatientID combo box changes
        */
        private void guiradtxtPatientID_EnabledChanged(object sender, EventArgs e)
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

        /** This event fires when enable property of guiradtxtFirstName combo box changes
        */
        private void guiradtxtFirstName_EnabledChanged(object sender, EventArgs e)
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

        /** This event fires when enable property of guiradtxtLastName combo box changes
        */
        private void guiradtxtLastName_EnabledChanged(object sender, EventArgs e)
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
       
        /** This event fires when setup screen Capture button is clicked
         * It validates measurement details and start capture process if validation succeeds
         * */
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
                    StartCaptureProcess(sender, e);
                    GuiCommon.CaptureTabClick = true;
                }
            }
            catch (Exception ex)
            {
                // In case of any exception being raised in the StartCaptureProcess(sender, e);
                GuiCommon.CaptureTabClick = true;   
                GUIExceptionHandler.HandleException(ex, this);
            }
        }

        /** This method is invoked when user clicks capture button or capture tab
         * It checks for device connected or not, validates the measurement details and starts capture if data entered is valid
         * */
        private void StartCaptureProcess(object sender, EventArgs e)
        {
            if (crxMgrObject.GeneralSettings.StartupScreen.ToUpper() == oMsgMgr.GetMessage(CrxStructCommonResourceMsg.Setup).ToUpper() && !GuiCommon.IsOnReportForm)
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

        /** This method fills session object with measurement data
          * */
        private void FillSessionWithModifiedMeasuremt()
        {
            GuiCommon.bizObject.groupStudyId = (uint)GuiCommon.GroupId;
            GuiCommon.bizObject.systemId = (uint)GuiCommon.SystemIdentifier;
            GuiCommon.bizObject.patientNumber = (uint)GuiCommon.PatientInternalNumber;
            
            SetSessionWithModifiedHeightWeight();
            SetSessionWithModifiedBP();
            SetSessionWithModifiedDistance();

            GuiCommon.bizObject.notes = guiradtxtMedication.Text;
            GuiCommon.bizObject.operatorId = guiradtxtOperator.Text;
            
            // obj.bloodPressureEntryOption = (ushort)crxMgrObject.GeneralSettings.BloodPressureEntryOptions;
            GuiCommon.bizObject.bloodPressureEntryOption = (ushort)crxMgrObject.BpSettings.BloodPressure;
        }

        /** This method fills session object with measurement data
         * */
        private void FillSessionWithModifiedMeasuremtForPwa()
        {
            GuiCommon.bizPwaobject.groupStudyId = (uint)GuiCommon.GroupId;
            GuiCommon.bizPwaobject.systemId = (uint)GuiCommon.SystemIdentifier;
            GuiCommon.bizPwaobject.patientNumber = (uint)GuiCommon.PatientInternalNumber;

            SetSessionWithModifiedHeightWeightForPwa();
            SetSessionWithModifiedBPForPwa();
          
            // GuiCommon.bizObject.notes = guiradtxtMedication.Text;
            // GuiCommon.bizObject.operatorId = guiradtxtOperator.Text;

            // obj.bloodPressureEntryOption = (ushort)crxMgrObject.GeneralSettings.BloodPressureEntryOptions;
            GuiCommon.bizPwaobject.bloodPressureEntryOption = (ushort)crxMgrObject.BpSettings.BloodPressure;
        }

        /** This method fills session with modified height for pwa
        * */
        private void SetSessionWithModifiedHeightWeight()
        { 
            // height 
            switch (crxMgrObject.GeneralSettings.HeightandWeightUnit)
            {
                // converting to int as crxMgrObject.GeneralSettings.HeightandWeightUnit returns int
                case (int)CrxGenPwvValue.CrxGenHeightWeightMetric:
                    GuiCommon.bizObject.heightAndWeight.heightInCentimetres = string.IsNullOrEmpty(guiradtxtsetupheight.Text) ? GuiConstants.DefaultValue : ushort.Parse(guiradtxtsetupheight.Text);

                    // obj.heightAndWeight.weightInKilograms = string.IsNullOrEmpty(guiradtxtWeight.Text) ? GuiConstants.DefaultValue : ushort.Parse(guiradtxtWeight.Text);
                    break;

                case (int)CrxGenPwvValue.CrxGenHeightWeightImperial:
                    if ((guiradtxtsetupheight.Text.Length > 0) || (guiradtxtImperialHeight.Text.Length > 0))
                    {
                        // Checking if the inch/feet field is blank then setting it to zero.
                        // using local variable to store the text of guiradtxtImperialHeight and guiradtxtsetupheight.
                        string guiRadTxtImperialHeight = guiradtxtImperialHeight.Text.Equals(string.Empty) ? "0" : guiradtxtImperialHeight.Text;
                        string guiRadTxtSetUpheight = guiradtxtsetupheight.Text.Equals(string.Empty) ? "0" : guiradtxtsetupheight.Text;
                        int heightInInches = (int.Parse(guiRadTxtSetUpheight) * 12) + int.Parse(guiRadTxtImperialHeight);
                        GuiCommon.bizObject.heightAndWeight.heightInInches = (ushort)heightInInches;
                    }
                    else
                    {
                        GuiCommon.bizObject.heightAndWeight.heightInInches = GuiConstants.DefaultValue;
                    }

                    // Commenting the following code as weight is not required in PWV.
                    // obj.heightAndWeight.weightInPounds = string.IsNullOrEmpty(guiradtxtWeight.Text) ? GuiConstants.DefaultValue : ushort.Parse(guiradtxtWeight.Text);
                   break;

                default:
                    break;
            }
        }

        /** This method fills session with modified height & weights
         * */
        private void SetSessionWithModifiedHeightWeightForPwa()
        {  
            // height & weight
            switch (crxMgrObject.GeneralSettings.HeightandWeightUnit)
            {
                // converting to int as crxMgrObject.GeneralSettings.HeightandWeightUnit returns int
                case (int)CrxGenPwvValue.CrxGenHeightWeightMetric:
                    GuiCommon.bizPwaobject.heightAndWeight.heightInCentimetres = string.IsNullOrEmpty(guiradtxtPWAHeight.Text) ? GuiConstants.DefaultValue : ushort.Parse(guiradtxtPWAHeight.Text);
                     break;

                case (int)CrxGenPwvValue.CrxGenHeightWeightImperial:
                    if ((guiradtxtPWAHeight.Text.Length > 0) || (guiradtxtPWAImperialHeight.Text.Length > 0))
                    {
                        // Checking if the inch/feet field is blank then setting it to zero.
                        // using local variable to store the text of guiradtxtImperialHeight and guiradtxtsetupheight.
                        string guiRadTxtImperialHeight = guiradtxtPWAImperialHeight.Text.Equals(string.Empty) ? "0" : guiradtxtPWAImperialHeight.Text;
                        string guiRadTxtSetUpheight = guiradtxtPWAHeight.Text.Equals(string.Empty) ? "0" : guiradtxtPWAHeight.Text;                        
                        int heightInInches = (int.Parse(guiRadTxtSetUpheight) * 12) + int.Parse(guiRadTxtImperialHeight);
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

        /** This method fills session with modified blood pressure values
         * */

        private void SetSessionWithModifiedBP()
        {
            GuiCommon.bizObject.bloodPressure.SP.Reading = string.IsNullOrEmpty(guiradtxtSP.Text) ? GuiConstants.DefaultValue : ushort.Parse(guiradtxtSP.Text);
            GuiCommon.bizObject.bloodPressure.DP.Reading = string.IsNullOrEmpty(guiradtxtDP.Text) ? GuiConstants.DefaultValue : ushort.Parse(guiradtxtDP.Text);
            GuiCommon.bizObject.bloodPressure.MP.Reading = GuiConstants.DefaultValue;

            //// blood pressure values
            // switch (obj.bloodPressureEntryOption)
            // {
            //    case (int)CrxGenPwvValue.CrxGenBPOptSPandDP: 
                   
            ////       break;
            ////    case (int)CrxGenPwvValue.CrxGenBPOptSPandMP: 
            //        obj.bloodPressure.SP.Reading = string.IsNullOrEmpty(guiradtxtSP.Text) ? GuiConstants.DefaultValue : ushort.Parse(guiradtxtSP.Text);
            //        obj.bloodPressure.MP.Reading = string.IsNullOrEmpty(guiradtxtDP.Text) ? GuiConstants.DefaultValue : ushort.Parse(guiradtxtDP.Text);
            //        obj.bloodPressure.DP.Reading = GuiConstants.DefaultValue;
            //        break;
            ////    case (int)CrxGenPwvValue.CrxGenBPOptMPandDP:
            //        obj.bloodPressure.MP.Reading = string.IsNullOrEmpty(guiradtxtSP.Text) ? GuiConstants.DefaultValue : ushort.Parse(guiradtxtSP.Text);
            //        obj.bloodPressure.DP.Reading = string.IsNullOrEmpty(guiradtxtDP.Text) ? GuiConstants.DefaultValue : ushort.Parse(guiradtxtDP.Text);
            //        obj.bloodPressure.SP.Reading = GuiConstants.DefaultValue;
            //        break;
            ////    default:
            //        obj.bloodPressure.SP.Reading = GuiConstants.DefaultValue;
            //        obj.bloodPressure.DP.Reading = GuiConstants.DefaultValue;
            //        obj.bloodPressure.MP.Reading = GuiConstants.DefaultValue;
            //        break;
            // }
        }

        /** This method fills session with modified blood pressure values
        * */

        private void SetSessionWithModifiedBPForPwa()
        {
            GuiCommon.bizPwaobject.bloodPressure.SP.Reading = string.IsNullOrEmpty(guiradlblPWASPDisplay.Text) ? GuiConstants.DefaultValue : ushort.Parse(guiradlblPWASPDisplay.Text);
            GuiCommon.bizPwaobject.bloodPressure.DP.Reading = string.IsNullOrEmpty(guiradlblPWADPDisplay.Text) ? GuiConstants.DefaultValue : ushort.Parse(guiradlblPWADPDisplay.Text);
            GuiCommon.bizPwaobject.bloodPressure.MP.Reading = string.IsNullOrEmpty(guiradlblPWAMPDisplay.Text) ? GuiConstants.DefaultValue : ushort.Parse(guiradlblPWAMPDisplay.Text);

            GuiCommon.bizPwaobject.Sp = float.Parse(guiradlblPWASPDisplay.Text);
            GuiCommon.bizPwaobject.Dp = float.Parse(guiradlblPWADPDisplay.Text);                    
            GuiCommon.bizPwaobject.MeasureType = PWA_MEASURE_TYPE.PWA_RADIAL;
        }

        /** This method fills session with modified distance values
         * */
        private void SetSessionWithModifiedDistance()
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

                    // obj.calculatedDistance = string.IsNullOrEmpty(guiradlblResult.Text) ? GuiConstants.DefaultValue : ushort.Parse(guiradlblResult.Text);
                    GuiCommon.bizObject.myPWVDirectDistance.distance = GuiConstants.DefaultValue;
                    break;

                case (int)CrxGenPwvValue.CrxPwvDistMethodDirect:
                    // direct
                    // populate direct & femoral to cuff textboxes
                    GuiCommon.bizObject.myCarotidDistance.distance = GuiConstants.DefaultValue;
                    GuiCommon.bizObject.myCuffDistance.distance = GuiConstants.DefaultValue;
                    GuiCommon.bizObject.myFemoral2CuffDistance.distance = string.IsNullOrEmpty(guiradtxtFemoralToCuff.Text) ? GuiConstants.DefaultValue : ushort.Parse(guiradtxtFemoralToCuff.Text);

                    // obj.calculatedDistance = string.IsNullOrEmpty(guiradlblResult.Text) ? GuiConstants.DefaultValue : ushort.Parse(guiradlblResult.Text);
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

        /** This method subscribes all the text boxes & drop down for changes made to it.
         * To the form changed event which will determine for any changes made before application is closed
         * */
        private void SubscribeSetupFormChanges()
        {
            //// subscribe text change events to determine any form changes
            // guiradtxtPatientID.TextChanged += GuiCommon.FormChanged;
            // guiradtxtFirstName.TextChanged += GuiCommon.FormChanged;
            // guiradtxtLastName.TextChanged += GuiCommon.FormChanged;           
            // guicmbxYear.SelectedIndexChanged += GuiCommon.FormChanged;
            // guicmbxGender.SelectedIndexChanged += GuiCommon.FormChanged;
            // guicmbxMonth.SelectedIndexChanged += GuiCommon.FormChanged;
            // guicmbDay.TextChanged += GuiCommon.FormChanged;
           
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

        /** Updates the setup screen label values when we scroll gridview through up-down keyboard arrow keys
         * */
        private void guiradgrdPatientList_CurrentRowChanged(object sender, CurrentRowChangedEventArgs e)
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
                    guiradbtnGetBp.Visible = true;
                    if (GuiCommon.CurrentMode.Equals(CrxStructCommonResourceMsg.Pwa))
                    {
                        objDefaultWindow.radtabCapture.Enabled = false;
                    }

                    DisableTimer();
                }
            }
        }

        /** This event is fired when the user uses keyboard keys.
         * If the patient list is hidden and the user presses up or down keys from keyboard then 
         * user is not allowed to perform it.
         */ 
        private void Setup_KeyDown(object sender, KeyEventArgs e)
        {
            if (guiradbtnExpander.Text.Equals(oMsgMgr.GetMessage(CrxStructCommonResourceMsg.ExpanderInital)))
            {
                if (e.KeyCode == Keys.Up || e.KeyCode == Keys.Down)
                {
                    e.SuppressKeyPress = true;
                }
            } 
        }

        /** This event gets fired when focus is moved from height in centimeteres & height in feet text box.
         * It checks if the value entered in textbox is within valid range and shows error accordingly
         * */
        private void guiradtxtsetupheight_Leave(object sender, EventArgs e)
        {
            objValidation.CheckIntegerFieldLimits(guiradtxtsetupheight);
        }

        /** This event gets fired when focus is moved from height in inches text box.
        * It checks if the value entered in textbox is within valid range and shows error accordingly
        * */
        private void guiradtxtImperialHeight_Leave(object sender, EventArgs e)
        {
           objValidation.CheckIntegerFieldLimits(guiradtxtImperialHeight);
        }      

        /** This event gets fired when focus is moved from SP text box.
       * It checks if the value entered in textbox is within valid range and shows error accordingly
       * */
        private void guiradtxtSP_Leave(object sender, EventArgs e)
        {
            objValidation.CheckFieldLimits(guiradtxtSP);
        }

        /** This event gets fired when focus is moved from DP text box.
      * It checks if the value entered in textbox is within valid range and shows error accordingly
      * */
        private void guiradtxtDP_Leave(object sender, EventArgs e)
        {
            objValidation.CheckFieldLimits(guiradtxtDP);
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

        private void guiradgrdPatientList_CellFormatting(object sender, CellFormattingEventArgs e)
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

        private void guicmbDay_SelectedIndexChanged(object sender, Telerik.WinControls.UI.Data.PositionChangedEventArgs e)
        {           
            guilblDay.Text = guicmbDay.Text;

            // gets patient records based on inputs given for day drop down (only if month & year values are selected)
            if (!IsFieldsBlank(true) && mode == CurrentMode.SearchMode)
            {
                GetSearchResults();
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
                // if (guicmbxMonth.GetItemText(guicmbxMonth.SelectedItem).Equals(oMsgMgr.GetMessage(CrxStructCommonResourceMsg.FebCondition), StringComparison.CurrentCultureIgnoreCase))
                if (guicmbxMonth.SelectedItem.Text.Equals(oMsgMgr.GetMessage(CrxStructCommonResourceMsg.GuiMonthFeb), StringComparison.CurrentCultureIgnoreCase))
                {
                    FillDayLeapYear();
                }

                // to fetch records in search mode
                if (!IsFieldsBlank(true) && mode == CurrentMode.SearchMode)
                {
                    GetSearchResults();
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

        private void guicmbxMonth_EnabledChanged(object sender, EventArgs e)
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
       
        private void guicmbxGender_SelectedIndexChanged(object sender, Telerik.WinControls.UI.Data.PositionChangedEventArgs e)
        {
            // gets patient records based on inputs given for gender
                if (!IsFieldsBlank(true) && mode == CurrentMode.SearchMode)
                {
                    GetSearchResults();
                }

                guilblGender.Text = guicmbxGender.Text;
        }

        /** This method is used to Validate age of the patient before validating measurement details.
         */ 
        private bool ValidatePatientAge()
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
                        retVal = false;
                        break;

                    case BizCaptureGate.CAPTURE_CONFIRM:
                        GuiCommon.ReportChildForm.Close();  
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
                GUIExceptionHandler.HandleException(ex, this);
                return retVal;
            }
        }

        /** This event is used to set focus on the Pateint list when ever the user comes back to setup screen from Report.
         */
        private void SetFocusOnPatientList(object sender, EventArgs e)
        {
            GuiCommon.IsOnSetupScreen = true; 
            guiradgrdPatientList.Focus();
            if (guiradbtnGetBp.Text == oMsgMgr.GetMessage(CrxStructCommonResourceMsg.BtnRepeat) && (!ProgressBarTimeStatusTimer.Enabled))
            {
                // objDefaultWindow.guiradmnuScor.Enabled = true;
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

        private void CheckIfFieldValueIsOutsideRange()
        {
            if (GuiCommon.IsValueOutsideLimits)
            {
                objDefaultWindow.radpgTabCollection.SelectedPage = objDefaultWindow.guiradgrpbxPwvDistanceMethod;
                objDefaultWindow.guiradgrpbxPwvDistanceMethod.Enabled = true;
                return;
            }            
        }

        /** Begin: AtCor-Drop2-Sprint3, TM, SWREQ2012,SWREQ2013,SWREQ2014,SWREQ2015,27 july 2011

        /** This method is used to make all timer disable on mode change and on selected record change event in gridview.
        * This is needed because when we ar changing patient from grid and we are in middle of measurement of previous patient then measurement process should start from begining on selection 
        * of anothet patient.      
        */
        void DisableTimer()
        {
            if (guiradgrdPatientList.Rows.Count > 0)
            {
                guiradgrdPatientList.Enabled = true;
            }

            SetupScreenTimer.Enabled = false;
            ProgressBarTimeStatusTimer.Enabled = false;
            EnableWaitButtonTimer.Enabled = false;
            guiradlblBPProgressBar.Visible = false;
            guiradbtnAutoPWACancel.Visible = false;
            guiradlblCuffPressureValue.Text = string.Empty;
            guiradlblCuffPressure.Visible = false;
            guiradlblCuffPressureValue.Visible = false;
            guiradlblCuffPressureUnit.Visible = false;
            guiradbtnAssessmentsDetails.Visible = false;
            guiradbtnGetBp.Enabled = true;
            counter = 0;
            guiradlblBpAssessmentsStatus.Visible = false;
            guiradbtnAssessmentsDetails.Visible = false;
            guiradbtnGetBp.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.BtnStart);
            ResetMeasurementFields();
            objDefaultWindow.guiradmnuScor.Enabled = true;

            // objDefaultWindow.guiradmnuDatabase.Enabled = true;
            // objDefaultWindow.guiradmnuSystem.Enabled = true;
            objDefaultWindow.guiradmnuScor.Enabled = true;

            // objDefaultWindow.guiradmnuDatabase.Enabled = true;
            // objDefaultWindow.guiradmnuSystem.Enabled = true;
            objDefaultWindow.radtabCapture.Enabled = false;
        } 

        /**This event gets fired on mode change from dropdown
         * */
        void ModeChangeEventHandler(object sender, EventArgs e)
        {
            DisableTimer();
            DisplayLastRecord(GuiCommon.PatientInternalNumber, GuiCommon.GroupId);
        }

        /** This function makes patient list,controls for demographic details and action buttons below patient list enable/disable depeding on measurement is in progress or not
         */
        void BrowsemodeForMeasurement(bool value)
        {
           // objDefaultWindow.radtabReport.Enabled = value;
            objDefaultWindow.guicmbxCurrentMode.Enabled = value;
            guiradtxtPWAHeight.Enabled = value;
            guiradtxtPWAImperialHeight.Enabled = value;
            guiradtxtPwaOperator.Enabled = value;
            guiradtxtMedicationNotes.Enabled = value;
            guiradgrdPatientList.Enabled = value;

           // guiradtxtFirstName.Enabled = value;
           // guiradtxtLastName.Enabled = value;
           // guiradtxtPatientID.Enabled = value;
            guicmbGroup.Enabled = value;

           // guicmbxGender.Enabled = value;
           // guicmbDay.Enabled = value;
           // guicmbxMonth.Enabled = value;
           // guicmbxYear.Enabled = value;
           // guiradbtnCancel.Enabled = value;
           // guiradbtnSave.Enabled = value;
            guiradbtnSearch.Enabled = value;
            guiradbtnNew.Enabled = value;
            guiradbtnEdit.Enabled = value;
            guiradbtnExpander.Enabled = value;
            guiradbtnDelete.Enabled = value;  
        }

        /**This event is fired when the user wants to get the BP values in the PWA mode.
         */ 
        private void guiradbtnGetBp_Click(object sender, EventArgs e)
        {
            if (counter == 0)
            {
            // Following function validates height field value to be in range of ushort integer.
            CheckFieldLimitsForPWAHeight();    
        
            // // if (GuiCommon.IsValueOutsideLimits && (!guiradtxtPWAHeight.Text.Equals(string.Empty)) && !guiradtxtPWAImperialHeight.Text.Equals(string.Empty))
                if (GuiCommon.IsValueOutsideIntegerLimits)
                {
                    return;
                }
            }           

         // Following code will be change when values will be read from Bp measurement Device
            try
            {
                timer = 0;
                int noOfAssessments = crxMgrObject.BpSettings.NumberofAssessments;             
                
                objDefaultWindow.guiradmnuScor.Enabled = false;

                // If Button text is "Start" or "Repeat"
                if ((guiradbtnGetBp.Text == oMsgMgr.GetMessage(CrxStructCommonResourceMsg.BtnStart)) || (guiradbtnGetBp.Text == oMsgMgr.GetMessage(CrxStructCommonResourceMsg.BtnRepeat)) || (guiradbtnGetBp.Text == oMsgMgr.GetMessage(CrxStructCommonResourceMsg.BtnWait)))
                {
                    BrowsemodeForMeasurement(false);
                    objDefaultWindow.radtabReport.Enabled = false;

                    // Capture tab is disable when measurement is in progress
                    objDefaultWindow.radtabCapture.Enabled = false;

                    // showing message(assessment in progress) in message progress bar 
                    objDefaultWindow.radlblMessage.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.LblReportAssessment) + " " + Convert.ToString(counter + 1) + " " + oMsgMgr.GetMessage(CrxStructCommonResourceMsg.MsgInProgress);
                        
                        // guiradlblBpAssessmentsStatus.Text = "Assessment: " + Convert.ToString(counter + 1) + " In Progress...";
                        // guiradlblBpAssessmentsStatus.Visible = true;

                        // Clear all measurement labels
                        guiradbtnGetBp.Enabled = true;
                        guiradbtnGetBp.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.BtnStop);
                        guiradbtnAutoPWACancel.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.BtnCancel);
                        ResetMeasurementFields();
                        guiradbtnAssessmentsDetails.Visible = false;

                        // Display Cuff Pressure labels
                        guiradlblCuffPressure.Visible = true;
                        guiradlblCuffPressureValue.Visible = true;
                        guiradlblCuffPressureUnit.Visible = true;

                        // Start the dummy timer to display BP readings
                        SetupScreenTimer.Enabled = true;

                        // Hide progress bar
                        guiradlblBPProgressBar.Visible = false;
                        guiradbtnAutoPWACancel.Visible = false;

                        // Stop cPWA timers
                        ProgressBarTimeStatusTimer.Enabled = false;

                        // Reset Progressbar values
                        guiradlblCuffPressureValue.Text = "0";
                        guiradlblBPProgressBar.Minimum = 0;
                        guiradlblBPProgressBar.Maximum = AutoProgressbarDelay;
                        guiradlblBPProgressBar.Value1 = 0;

                        // guiradlblBPProgressBar.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.LblPwaSetupProgressBarEndMsg);
                        guiradlblBPProgressBar.Text = string.Format(oMsgMgr.GetMessage(CrxStructCommonResourceMsg.LblPwaSetupProgressBarStartMsg), Convert.ToString(AutoProgressbarDelay));

                    // Commented on 26 august to implement 2018 userstory's 3 acceptance criteria
                       // counter++;                   
                }
                else if (guiradbtnGetBp.Text == oMsgMgr.GetMessage(CrxStructCommonResourceMsg.BtnStop))
                {
                    // Added on 26 august to implement 2018 userstory's 3 acceptance criteria
                    if (counter >= 1 && !GuiCommon.IsValueOutsideIntegerLimits)
                    {
                        SetAvgBpMeasurementData(counter);
                        guiradbtnAutoPWACancel.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.BtnCapture);
                        guiradbtnAutoPWACancel.Visible = true;
                        objDefaultWindow.radtabCapture.Enabled = true;
                    }

                    BrowsemodeForMeasurement(true);
                    objDefaultWindow.radtabReport.Enabled = GuiCommon.HasMeasurementDetails;
                    counter = 0;
                    objDefaultWindow.radlblMessage.Text = string.Empty;
                    guiradlblBpAssessmentsStatus.Visible = false;
                    SetupScreenTimer.Enabled = false;
                    guiradbtnGetBp.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.BtnRepeat);
                    if (!ProgressBarTimeStatusTimer.Enabled)
                    {                      
                        objDefaultWindow.guiradmnuScor.Enabled = true;
                    }

                    guiradlblCuffPressure.Visible = false;
                    guiradlblCuffPressureValue.Visible = false;
                    guiradlblCuffPressureUnit.Visible = false;
                }
            }
            catch (Exception ex)
            {
                GUIExceptionHandler.HandleException(ex, this);
            }
        }

        /** This method resets all BP measurement fields
         * */
        void ResetMeasurementFields()
        {
            guiradlblPWASPDisplay.Text = string.Empty;
            guiradlblPWAPPDisplay.Text = string.Empty;
            guiradlblPWAMPDisplay.Text = string.Empty;
            guiradlblPWADPDisplay.Text = string.Empty;
        }

        /** When there are more than one assessment,after every assessment this event fires.It wait for some time which is defined 
         * in xml file and calls guiradbtnGetBp click event to do next assessment.
         * */
        private void EnableWaitButtonTimer_Tick(object sender, EventArgs e)
        {
            if (waitTimer >= (WaitButtonDelay - 1))
            {
                // guiradbtnGetBp.Enabled = true;
                // guiradbtnGetBp.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.BtnRepeat);
                // guiradbtnAutoPWACancel.Visible = true;               
                    EnableWaitButtonTimer.Stop();
               
                // Start progress bar for auto capture
                // guiradlblBPProgressBar.Visible = true;
                // ProgressBarTimeStatusTimer.Start();
                objDefaultWindow.radlblMessage.Text = string.Empty;
                StartButtonClick.Invoke(sender, e);
                guiradbtnGetBp.Visible = true;
            }
            else
            {              
                waitTimer = waitTimer + 1;               
            }
        }

        /**This is a stub method used to populate the BP values in PWA mode.
         * Values have been hardcoded for time being as these values will be coming from the device via the dal layer.
         */
        private void SetBpMeasurementData(int counter)
        {
            // This is stub method for reading Bp measurement data
            switch (counter)
            {
                case 1:

                    guiradlblPWASPDisplay.Text = "140";
                    guiradlblPWAPPDisplay.Text = "60";
                    guiradlblPWAMPDisplay.Text = "110";
                    guiradlblPWADPDisplay.Text = "80";
                    break;
                case 2:
                    guiradlblPWASPDisplay.Text = "155";
                    guiradlblPWAPPDisplay.Text = "50";
                    guiradlblPWAMPDisplay.Text = "150";
                    guiradlblPWADPDisplay.Text = "90";
                    break;
                case 3:
                    guiradlblPWASPDisplay.Text = "140";
                    guiradlblPWAPPDisplay.Text = "70";
                    guiradlblPWAMPDisplay.Text = "140";
                    guiradlblPWADPDisplay.Text = "70";
                    break;
                case 4:
                    guiradlblPWASPDisplay.Text = "155";
                    guiradlblPWAPPDisplay.Text = "70";
                    guiradlblPWAMPDisplay.Text = "120";
                    guiradlblPWADPDisplay.Text = "90";
                    break;
                case 5:
                    guiradlblPWASPDisplay.Text = "160";
                    guiradlblPWAPPDisplay.Text = "70";
                    guiradlblPWAMPDisplay.Text = "130";
                    guiradlblPWADPDisplay.Text = "85";
                    break;
            }
        }

        /**This is a stub method used to populate the Average BP values in PWA mode when all the assessments done.
       * Values have been hardcoded for time being as these values will be coming from the device via the dal layer.
       */
        private void SetAvgBpMeasurementData(int counter)
        { // This is stub method for reading Bp measurement data
            switch (counter)
            {
                case 1:

                    guiradlblPWASPDisplay.Text = "140";
                    guiradlblPWAPPDisplay.Text = "60";
                    guiradlblPWAMPDisplay.Text = "110";
                    guiradlblPWADPDisplay.Text = "80";
                    break;
                case 2:
                    guiradlblPWASPDisplay.Text = "148"; // round(140+155/2)
                    guiradlblPWAPPDisplay.Text = "55";  // 60+50/2
                    guiradlblPWAMPDisplay.Text = "130"; // 110+150/2
                    guiradlblPWADPDisplay.Text = "85"; // 80+90/2
                    break;
                case 3:
                    guiradlblPWASPDisplay.Text = "145";  // round(140+155+140/3)
                    guiradlblPWAPPDisplay.Text = "60";    // round(60+50+70/3)
                    guiradlblPWAMPDisplay.Text = "133"; // round(110+150+140/3)
                    guiradlblPWADPDisplay.Text = "80"; // round(80+90+70/3)
                    break;
                case 4:
                    guiradlblPWASPDisplay.Text = "148";  // round(140+155+140+155/4)
                    guiradlblPWAPPDisplay.Text = "63";  // round(60+50+70+70/4)
                    guiradlblPWAMPDisplay.Text = "130"; // round(110+150+140+120/4)
                    guiradlblPWADPDisplay.Text = "90";  // round(80+90+70+90/4)
                    break;
                case 5:
                    guiradlblPWASPDisplay.Text = "150"; // round(140+155+140+155+160/5)
                    guiradlblPWAPPDisplay.Text = "64";  // round(60+50+70+70+70/5)
                    guiradlblPWAMPDisplay.Text = "130"; // round(110+150+140+120+130/5)
                    guiradlblPWADPDisplay.Text = "83";  // round(80+90+70+90+85/5)
                    break;
            }
        }

        /** This is dummy timer used to set Bp measurement stub values after 5 seconds. 
        * It checkes for assessment in progress and after completion of all assessment it enable
        * auto pwa progress bar.
        * */
        private void SetupScreenTimer_Tick(object sender, EventArgs e)
        {
            // Display reading values
            guiradlblCuffPressureValue.Text = timer.ToString();
            if (timer >= 50)
            {
                if (crxMgrObject.BpSettings.NumberofAssessments > 1 && counter < crxMgrObject.BpSettings.NumberofAssessments - 1)
                {
                    guiradlblBpAssessmentsStatus.Visible = false;
                    EnableWaitButtonTimer.Start();
                    objDefaultWindow.radlblMessage.Text = "                " + oMsgMgr.GetMessage(CrxStructCommonResourceMsg.BtnWait);
                   guiradbtnGetBp.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.BtnWait);

                    // When measurement is in wait mode guiradbtnGetBp is hidden
                    guiradbtnGetBp.Visible = false;
                    guiradbtnGetBp.Enabled = false;                    
                    guiradlblBPProgressBar.Visible = false;
                    counter++; 
                    SetBpMeasurementData(counter);
                }
                else
                {
                    // When all the assessment finished it will come in else part.
                    counter++; 
                    SetAvgBpMeasurementData(counter);
                    guiradbtnGetBp.Enabled = true;
                    guiradbtnGetBp.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.BtnRepeat);
                    counter = 0;
                    objDefaultWindow.radlblMessage.Text = string.Empty;  
                  
                    // disable display button if number of assessments is 1
                    // if (crxMgrObject.BpSettings.NumberofAssessments != 1)
                    // {
                    //    guiradbtnAssessmentsDetails.Visible = true;
                    // }
                    guiradlblBpAssessmentsStatus.Visible = false;
                    guiradbtnAutoPWACancel.Visible = true;
                    if (crxMgrObject.BpSettings.AutoPWASP || crxMgrObject.BpSettings.AutoPWAPP || crxMgrObject.BpSettings.AutoPWADP)
                    {
                        guiradlblBPProgressBar.Visible = true;      
                
                        // Start progress bar for auto capture
                        ProgressBarTimeStatusTimer.Enabled = true;
                    }
                    else
                    {
                         objDefaultWindow.guiradmnuScor.Enabled = true;                      
                        objDefaultWindow.radtabCapture.Enabled = true;
                        guiradbtnAutoPWACancel.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.BtnCapture);
                        BrowsemodeForMeasurement(true);
                        objDefaultWindow.radtabReport.Enabled = GuiCommon.HasMeasurementDetails;
                    }                 
                }
               
                waitTimer = 0;

                // Hide Cuff Pressure labels
                guiradlblCuffPressure.Visible = false;
                guiradlblCuffPressureValue.Visible = false;
                guiradlblCuffPressureUnit.Visible = false;

                // Stop timer
                SetupScreenTimer.Enabled = false;            
                guiradlblBPProgressBar.Minimum = 0;
                guiradlblBPProgressBar.Maximum = AutoProgressbarDelay;
                guiradlblBPProgressBar.Value1 = 0;

                // guiradlblBPProgressBar.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.LblPwaSetupProgressBarEndMsg);
                // Below line will assign text to Progress bar depending on delay assigned in System XML file PWA enabled in 0:5 
                guiradlblBPProgressBar.Text = string.Format(oMsgMgr.GetMessage(CrxStructCommonResourceMsg.LblPwaSetupProgressBarStartMsg), Convert.ToString(AutoProgressbarDelay));                           
            }
            else
            {
                timer = timer + 10;
            }
        }

        /** This timer ticks every 1 sec and it ticks for time set in xml file and    
         * after time reaches to time set in xml file it start capture process automatically.
         * Before time reaches to specified value every sec it shows how much time is remaining 
         * for auto pwa in progress bar text area.
        * */
        private void ProgressBarTimeStatusTimer_Tick(object sender, EventArgs e)
        {
            if (guiradlblBPProgressBar.Value1 >= AutoProgressbarDelay)
            {
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
                try
                {                   
                    // check if device is connected
                    // fill the biz session object with measurement details
                    // if validation succeeds start capture process
                    CrxPwaCaptureInput pwaCaptureInput = new CrxPwaCaptureInput();

                    // pwaObj = (BizPWA)BizSession.Instance().measurement;
                    bool value = GuiCommon.bizPwaobject.GetCurrentCaptureInput(ref pwaCaptureInput);
                    if (!Convert.ToInt32(pwaCaptureInput).Equals(crxMgrObject.PwaSettings.CaptureInput))
                    {
                        GuiCommon.bizPwaobject.Initialise(crxMgrObject.PwaSettings.CaptureInput.Equals(Convert.ToInt32(CrxPwaCaptureInput.Tonometer)) ? CrxPwaCaptureInput.Tonometer : CrxPwaCaptureInput.Cuff);
                    }        

                    GuiCommon.CaptureTabClick = false;
                   
                    objDefaultWindow.radtabCapture.Enabled = true;
                    objDefaultWindow.guiradmnuScor.Enabled = true;                                     
                    StartCaptureProcess(sender, e);
                   
                   // objDefaultWindow.guicmbxCurrentMode.Enabled = false;
                 //   objDefaultWindow.radtabReport.Enabled = false;
                    GuiCommon.CaptureTabClick = true;
                }
                catch (Exception ex)
                {
                    // In case of any exception being raised in the StartCaptureProcess(sender, e);
                    GuiCommon.CaptureTabClick = true;
                    GUIExceptionHandler.HandleException(ex, this);
                }
            }
            else
            {
                // Increment progress bar after every second
                guiradlblBPProgressBar.Value1 = guiradlblBPProgressBar.Value1 + 1;
                int displayValue = guiradlblBPProgressBar.Maximum - guiradlblBPProgressBar.Value1;
                guiradlblBPProgressBar.Text = string.Format(oMsgMgr.GetMessage(CrxStructCommonResourceMsg.LblPwaSetupProgressBarStartMsg), displayValue.ToString());
            }
        }

        /** This event is used to cancel auto pwa or start manual capture.When text of the button is "cancel" then click event will
         * cancel auto pwa.When text of the button is "Capture" then click event will call capture process.
       * */
        private void guiradbtnAutoPWACancel_Click(object sender, EventArgs e)
        {
            if (guiradbtnAutoPWACancel.Text == oMsgMgr.GetMessage(CrxStructCommonResourceMsg.BtnCancel))
            {
                //// Hide Progress Bar
                guiradlblBPProgressBar.Visible = false;

                //// Reset Progressbar values
                guiradlblBPProgressBar.Minimum = 0;
                guiradlblBPProgressBar.Maximum = AutoProgressbarDelay;
                guiradlblBPProgressBar.Value1 = 0;
                objDefaultWindow.radtabCapture.Enabled = true;

                // guiradlblBPProgressBar.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.LblPwaSetupProgressBarEndMsg);
                guiradlblBPProgressBar.Text = string.Format(oMsgMgr.GetMessage(CrxStructCommonResourceMsg.LblPwaSetupProgressBarStartMsg), Convert.ToString(AutoProgressbarDelay));
                guiradbtnAutoPWACancel.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.BtnCapture);

                ProgressBarTimeStatusTimer.Stop();
                ProgressBarTimeStatusTimer.Enabled = false;
                BrowsemodeForMeasurement(true);
                objDefaultWindow.radtabReport.Enabled = GuiCommon.HasMeasurementDetails;
                if (guiradbtnGetBp.Text == oMsgMgr.GetMessage(CrxStructCommonResourceMsg.BtnRepeat) && (!ProgressBarTimeStatusTimer.Enabled))
                {
                    objDefaultWindow.guiradmnuScor.Enabled = true;                 
                }
            }
            else
            {               
                // Call a method to go to Capture Screen
                CheckFieldLimitsForPWAHeight();

                if (GuiCommon.IsValueOutsideIntegerLimits)
                {                    
                  return;
                }

                try
                {                    
                    // Coding for PWA mode.
                    CrxPwaCaptureInput pwaCaptureInput = new CrxPwaCaptureInput();

                    // pwaObj = (BizPWA)BizSession.Instance().measurement;
                    // pwaObj = (BizPWA)BizSession.Instance().measurement;                
                    bool value = GuiCommon.bizPwaobject.GetCurrentCaptureInput(ref pwaCaptureInput);
                    if (!Convert.ToInt32(pwaCaptureInput).Equals(crxMgrObject.PwaSettings.CaptureInput))
                    {
                        GuiCommon.bizPwaobject.Initialise(crxMgrObject.PwaSettings.CaptureInput.Equals(Convert.ToInt32(CrxPwaCaptureInput.Tonometer)) ? CrxPwaCaptureInput.Tonometer : CrxPwaCaptureInput.Cuff);
                    }    
               
                     GuiCommon.CaptureTabClick = false;
                     objDefaultWindow.radtabCapture.Enabled = true;                
                     StartCaptureProcess(sender, e);                    
                     guiradbtnAutoPWACancel.Visible = false;
                     GuiCommon.CaptureTabClick = true;
                }
                catch (Exception ex)
                {
                    // In case of any exception being raised in the StartCaptureProcess(sender, e);
                    GuiCommon.CaptureTabClick = true;
                    GUIExceptionHandler.HandleException(ex, this);
                }               
            }
        }

        /**This method is used to check any change made by the user to the PWV distance method.
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

        /**This method is used to check height field for PWA mode.
         */ 
        private void CheckFieldLimitsForPWAHeight()
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

        /** This event is used to show BP Assesment Dialog
         * */
        private void guiradbtnAssessmentsDetails_Click(object sender, EventArgs e)
        {
            if (objBpAssessment != null)
            {
                objBpAssessment = null;

                // objBpAssessment.ShowDialog();
            }

            objBpAssessment = new BPAssessments();
            objBpAssessment.ShowDialog();            
        }

        private void ValidationBeforePwaCapture()
        {
            if (ValidatePatientAge())
            {
                if (DalModule.Instance.CheckIfDeviceIsConnected())
                {
                    FillSessionWithModifiedMeasuremtForPwa();
                     // check for valid measurement details
                    if (GuiCommon.bizPwaobject.Validate())
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
                        BrowsemodeForMeasurement(true);
                        ResetMeasurementFields();
                        objDefaultWindow.radpgTabCollection.SelectedPage = objDefaultWindow.radtabCapture;
                        objDefaultWindow.guicmbxCurrentMode.Enabled = false;
                        objDefaultWindow.radtabCapture.Enabled = true;
                        objDefaultWindow.radtabReport.Enabled = false;
                        guiradbtnAutoPWACancel.Visible = false;
                    }
                    else
                    {
                        if (GuiCommon.CaptureTabClick)
                        {
                            // whenever exception is thrown while validating measurement details,
                            // navigate the user back to Setup screen.                            
                            objDefaultWindow.radpgTabCollection.SelectedPage = objDefaultWindow.guiradgrpbxPwvDistanceMethod;
                        }                        
                        RadMessageBox.Show(this, oMsgMgr.GetMessage(CrxStructCommonResourceMsg.ErrorValidating), oMsgMgr.GetMessage(CrxStructCommonResourceMsg.SystemError), MessageBoxButtons.OK, RadMessageIcon.Error);
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
                        // AtCor-Drop2-Sprint1
                        /* if ((GuiCommon.Mode == GuiCommon.Modes.cPWA) && (GuiCommon.Workflow == GuiCommon.Workflows.Quick))
                          {
                             objdefaultwindow.radpgtabcollection.selectedpage = objdefaultwindow.radtabquickstart;
                             objdefaultwindow.radtabquickstart.enabled = true;
                             objdefaultwindow.radtabresult.enabled = true;
                          }
                          else
                          { */                        
                        objDefaultWindow.radpgTabCollection.SelectedPage = objDefaultWindow.guiradgrpbxPwvDistanceMethod;
                        objDefaultWindow.guiradgrpbxPwvDistanceMethod.Enabled = true;
                        // }
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
                    objDefaultWindow.radpgTabCollection.SelectedPage = objDefaultWindow.guiradgrpbxPwvDistanceMethod;
                    objDefaultWindow.guiradgrpbxPwvDistanceMethod.Enabled = true;                   
                }
                BrowsemodeForMeasurement(true);
                guiradbtnAutoPWACancel.Visible = false;
                objDefaultWindow.guicmbxCurrentMode.Enabled = true;
                objDefaultWindow.radtabCapture.Enabled = false; 
            } 
        }

        private void ValidationBeforePwvCapture()
        {
            if (ValidatePatientAge())
            {
                if (!objValidation.CheckMandatoryFields())
                {
                    // check for electronic module is connected. 
                    if (DalModule.Instance.CheckIfDeviceIsConnected())
                    {
                        FillSessionWithModifiedMeasuremt();

                        // check for valid measurement details
                        if (GuiCommon.bizObject.Validate())
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
                                ((Capture)GuiCommon.CaptureChildForm).ShowSetupAfterCaptureAbort();
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

                            // capture tab & capture button
                            RadMessageBox.Show(this, oMsgMgr.GetMessage(CrxStructCommonResourceMsg.ErrorValidating), oMsgMgr.GetMessage(CrxStructCommonResourceMsg.SystemError), MessageBoxButtons.OK, RadMessageIcon.Error);
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
                        GuiCommon.ReportChildForm.Close();
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
                GUIExceptionHandler.HandleException(ex, this);
                return retVal;
            }
        }

        /**This method is used to check if the user wants to Repeat a PWA capture.
         * This happens when the user clicks on the Repeat button on the PWA Report screen.
         */ 
        private void CheckIfUserWantsToRepeatPWACapture()
        {
            if (GuiCommon.RepeatButtonClickedStartNibpOnSetup)
            {
                // Set the flag to false.
                GuiCommon.RepeatButtonClickedStartNibpOnSetup = false;
                Invoke(new EventHandler(guiradbtnGetBp_Click));
            }
        }

       /** End: AtCor-Drop2-Sprint3, TM, SWREQ2012,SWREQ2013,SWREQ2014,SWREQ2015, 1 August 2011
        */
    }   
}
