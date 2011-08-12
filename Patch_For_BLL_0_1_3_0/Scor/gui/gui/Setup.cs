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
                
        const int PatientMinChar = 14; // minimum characters required to display patient name on current lable width
        const int FemoralToCuffDefaultMmValue = 200; // default femoral to cuff value in mm
        const int FemoralToCuffDefaultCmValue = FemoralToCuffDefaultMmValue / 10; // convert default femoral to cuff value to cm
        const int PatientListHideValue = 10; // minimum splitter distance to hide patient list
        const int PatientListShowValue = 356; // maximum splitter distance to show patient list
                
        readonly CrxDBManager dbMagr = CrxDBManager.Instance;
        readonly string serverNameString = string.Empty;
        readonly CrxConfigManager crxMgrObject = CrxConfigManager.Instance;
        readonly CrxMessagingManager oMsgMgr = CrxMessagingManager.Instance;
        
        int bobj;
        BizPWV obj;
        GuiFieldValidation objValidation;

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
                DefaultWindow.OnSetupScreenTabClick += SetFocusOnPatientList;
                DefaultWindow.OnRestoreOptionClick += CheckIfInInsertMode;  
//VA:?                obj = (BizPWV)BizSession.Instance().measurement;              
                
                // initialize servername string
                serverNameString = GuiCommon.ServerNameString();
                GuiCommon.SetShape(guilblLastNameDisplay, guilblFirstnameDisplay, guilblPatientIdDisplay, guilblFirstnameDisplay, guilblGender, guilblDay, guilblMonth, guilblYear, guiradlblPWASPDisplay, guiradlblPWAPPDisplay, guiradlblPWAMPDisplay, guiradlblPWADPDisplay, guiradlblPWAHRDisplay, guiradlblCuffPressureValue);
                GuiCommon.SetShape(guiradtxtsetupheight, guiradtxtImperialHeight, guiradtxtWeight, guiradtxtOperator, guiradtxtMedication, guiradtxtSP, guiradtxtDP, guiradtxtCarotid, guiradtxtCuff, guiradtxtFemoralToCuff, guiradtxtPatientID, guiradtxtFirstName, guiradtxtLastName, guiradtxtPWAHeight, guiradtxtPWAImperialHeight, guiradtxtOthDevPWASP, guiradtxtOthDevPWADP);
                GuiCommon.SetShape(guicmbDay, guicmbxMonth, guicmbxYear, guicmbxYear, guicmbxGender);
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
            // guiradlblPatient.Text is commented because according to new requirement label is not needed anymore
            // guiradlblPatient.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.LblPateints);
            guiradlblPatientId.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.LblPatientId);
            guiradlblGroup.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.LblGroup);
            guiradlblFirstName.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.LblFirstName);
            guiradlblDateOfBirth.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.LblDob);
            guirdlblGender.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.LblGender);
            guiradlblLastName.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.LblLastName);
            guilblHeight.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.LblHeight);
            guiradlblHeightUnits.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.Cm);
            guiradlblImperialHeight.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.LblInches);
            guiradlblWeight.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.LblWeight);
            guiradlblWeightUnits.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.Kg);
            guiradlblOperator.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.LblOperator);
            guiradlblMedication.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.LblNotes);
            guiradlblSP.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.LabelSp);
            guiradlblDP.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.LabelDp);
            guiradlblPwvDistanceMethod.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.LabelSubtracting);
            guiradlblCarotid.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.LblReportCarotidWithcolon);
            guiradlblCarotidTonometerUnits.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.Mm);
            guiradlblCuff.Text = crxMgrObject.PwvSettings.PWVDistanceMethod.Equals((int)CrxGenPwvValue.CrxPwvDistMethodSubtract) ? oMsgMgr.GetMessage(CrxStructCommonResourceMsg.LblReportCuffWithcolon) : oMsgMgr.GetMessage(CrxStructCommonResourceMsg.GuiDirect);
            guiradlblCuffunits.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.Mm);
            guiradlblFemoralToCuff.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.LabelFemoralCuff);
            guiradlblFemoralToCuffUnits.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.Mm);
            guiradlblPwvDistanceCalculation.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.LabelPwvDistance);
            guiradlblPwvDistanceUnits.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.Mm);
            guiradbtnCapture.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.BtnCapture);
            guiradbtnNew.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.BtnNew);
            guiradbtnSearch.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.BtnSearch);
            guiradbtnEdit.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.BtnEdit);
            guiradbtnCancel.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.BtnCancel);
            guiradbtnSave.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.BtnSave);
            guiradbtnDelete.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.BtnDelete);
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
            guiradlblWeight.Tag = guiradtxtWeight.Tag = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.FieldPatientWeight); 
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
                ResetPatientMeasurementFields();
                SetHeightWeightUnits();
                SetBloodPressure();

                // SetPwvDistanceMethodAndUnits();
                
                // set label text as per settings changed for distance method
                guiradlblCuff.Text = crxMgrObject.PwvSettings.PWVDistanceMethod.Equals((int)CrxGenPwvValue.CrxPwvDistMethodSubtract) ? oMsgMgr.GetMessage(CrxStructCommonResourceMsg.LblReportCuffWithcolon) : oMsgMgr.GetMessage(CrxStructCommonResourceMsg.GuiDirect);
                
                // set tags as per settings changed for height & weight
                guiradtxtsetupheight.Tag = crxMgrObject.GeneralSettings.HeightandWeightUnit.Equals((int)CrxGenPwvValue.CrxGenHeightWeightMetric) ? oMsgMgr.GetMessage(CrxStructCommonResourceMsg.FieldPatientHeight) : oMsgMgr.GetMessage(CrxStructCommonResourceMsg.FieldPatientHeightFoot);
                guiradtxtImperialHeight.Tag = crxMgrObject.GeneralSettings.HeightandWeightUnit.Equals((int)CrxGenPwvValue.CrxGenHeightWeightMetric) ? string.Empty : oMsgMgr.GetMessage(CrxStructCommonResourceMsg.FieldPatientHeightInch);
                SetSetupTagForValidations();

                // set mandatory fields again after settings are changed from settings window
                objValidation.SetMandatoryFields(guipnlMeasurementDetails);
                
                if (!string.IsNullOrEmpty(radlblpatientinternalnumber.Text.Trim()) && !string.IsNullOrEmpty(radlblgroupid.Text))
                {
                    // to update biz session object with changed setting values
                    DisplayLastRecord(int.Parse(radlblpatientinternalnumber.Text.Trim()), int.Parse(radlblgroupid.Text));
                }

                SetPwvDistanceMethodAndUnits();
                guiradtxtFemoralToCuff.ReadOnly = !crxMgrObject.PwvSettings.FemoralToCuff;

                SetPatientPrivacy();
                SetSetupTagForValidations();   
                bool value = obj.Initialise();
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
            guiradtxtsetupheight.Text = string.Empty;
            guiradtxtImperialHeight.Text = string.Empty;
            guiradtxtWeight.Text = string.Empty;
            guiradtxtSP.Text = string.Empty;
            guiradtxtDP.Text = string.Empty;
            guiradtxtCarotid.Text = string.Empty;
            guiradtxtCuff.Text = string.Empty;
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

                obj = (BizPWV)BizSession.Instance().measurement;
                bobj = GuiConstants.SystemId;
                GuiCommon.SystemIdentifier = bobj;
                objValidation = new GuiFieldValidation(guipnlMeasurementDetails);
                                
                SetPatientPrivacy();
                FillGender();
                FillDay(0);
                FillMonthAndYear();
                LoadGroupNames();
                InitializePatientList();
                LoadPatientList();
                guiradlblPWASPDisplay.Font = guiradlblPWASPDisplay.Font = guiradlblPWAPPDisplay.Font = guiradlblPWAMPDisplay.Font = guiradlblPWADPDisplay.Font = guiradlblCuffPressureValue.Font = guiradlblPWAHRDisplay.Font = new Font("Arial", 11);
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

                        // guiradlblNumberOfPatients.Text is commented because according to new requirement label is not needed anymore
                        // guiradlblNumberOfPatients.Text = ds.Tables[0].Rows.Count.ToString();

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

                        guicmbxGender.SelectedValue = CultureInfo.CurrentCulture.TextInfo.ToTitleCase(dsPatientDemographicDetails.Tables[0].Rows[0][(int)CrxDBGetPatientDetailsById.Gender].ToString().Trim().ToLower());
                                               
                        // display patients first & last name at bottom
                        objDefaultWindow.radlblPatientName.Text = !string.IsNullOrEmpty(guiradtxtFirstName.Text.Trim()) ? string.Format("{0} {1}", guiradtxtFirstName.Text.Trim(), guiradtxtLastName.Text.Trim()) : guiradtxtLastName.Text.Trim();

                        radlblpatientinternalnumber.Text = patientNumberInternal.ToString();
                        radlblgroupid.Text = groupId.ToString();

                        // intialize bizpatient object with selected record
                        BizPatient patientObj = BizPatient.Instance();
                        patientObj.dateOfBirth = DateTime.Parse(date.ToShortDateString());
                        patientObj.firstName = guiradtxtFirstName.Text.Trim();
                        patientObj.gender = guicmbxGender.Text.Trim();
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
                                              
                        if (crxMgrObject.PwvSettings.FemoralToCuff)
                        {
                            guiradtxtFemoralToCuff.ReadOnly = false;
                        }

                        // initialising RHS measurement display as per scor settings
                        SetHeightWeightUnits();
                        SetBloodPressure();
                        SetPwvDistanceMethodAndUnits();
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
                    guiradbtnCancel.Enabled = true;
                }

                // Nitesh
                objDefaultWindow.radlblPatientName.Visible = false;
            }
            else
            {
                if (mode == CurrentMode.InsertMode || mode == CurrentMode.EditMode || mode == CurrentMode.SearchMode)
                {
                    // Nitesh
                    guiradbtnCancel.Enabled = true;

                    // Nitesh
                    guiradbtnEdit.Enabled = false;
                    guiradbtnDelete.Enabled = false;
                    objDefaultWindow.radlblPatientName.Visible = false;
                }
                else
                {
                    guiradbtnEdit.Enabled = true;
                    guiradbtnDelete.Enabled = true;
                    objDefaultWindow.radlblPatientName.Visible = true;
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
                
                GuiCommon.IsFormChanged = false;
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
                            objDefaultWindow.radtabCapture.Enabled = !GuiCommon.IsWaitIntervalImposed;
                            break;
                        case DialogResult.No:
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
                            objDefaultWindow.radtabCapture.Enabled = !GuiCommon.IsWaitIntervalImposed;
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

        /** This method is used to set the height weight units in the GUI depending on the settings selected by the user.
      */
        private void SetHeightWeightUnits()
        {
            // read height and weight units and accordingly show units for height and weight.Convert values accordingly.
            // read the properties for the setting the units for measurement data.
            switch (crxMgrObject.GeneralSettings.HeightandWeightUnit)
            {
                case (int)CrxGenPwvValue.CrxGenHeightWeightMetric:
                    // metric units i.e cm and kg.
                    guiradlblHeightUnits.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.Cm); 
                    guiradlblWeightUnits.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.Kg); 
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

                    // change unit of weight to lbs.
                    guiradlblWeightUnits.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.Lbs); 
                    break;

                default:
                    break;
            }                        
        }

        /** This method is used to set the blood pressure in the GUI depending on the settings selected by the user.
    */
        private void SetBloodPressure()
        {
            // read blood pressure and accordingly display the combination of SP,DP and MP. 
            // Pritam
            // switch (crxMgrObject.GeneralSettings.BloodPressureEntryOptions)
            switch (crxMgrObject.BpSettings.BloodPressure)
            {
                case (int)CrxGenPwvValue.CrxGenBPOptSPandDP:
                    guiradlblSP.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.LabelSp); 
                    guiradlblDP.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.LabelDp); 
                    break;
                case (int)CrxGenPwvValue.CrxGenBPOptSPandMP:
                    // sp and mp
                    guiradlblSP.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.LabelSp);

                    // change dp to mp
                    guiradlblDP.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.LabelMp);
                    break;
                case (int)CrxGenPwvValue.CrxGenBPOptMPandDP:
                    // mp and dp
                    // sp to MP
                    guiradlblSP.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.LabelMp);

                    // change dp tp DP
                    guiradlblDP.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.LabelDp);
                    break;
                default:
                    break;
            }                      
        }

        /** This method is used to set the PWV distance methods/units in the GUI depending on the settings selected by the user.
    */
        private void SetPwvDistanceMethodAndUnits()
        {
            // Clear the PWV distance values when the PWV distance method is changed.
            guiradtxtCuff.Text = string.Empty;
            guiradtxtCarotid.Text = string.Empty;

            // read pwv distance units and pwv distance method and accordingly dispaly the labels and textbox.Do the calculation of for PWV distance.Also read the cuff location for it to be editable or no. 
            switch (crxMgrObject.PwvSettings.PWVDistanceMethod)
            {
                case (int)CrxGenPwvValue.CrxPwvDistMethodSubtract:
                    guiradlblPwvDistanceMethod.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.SubtractingMethod);
                    Image imageSubtracting = Image.FromFile(ConfigurationManager.AppSettings[GuiConstants.AppConfigParams.SetupScreenSubtracting.ToString()]);
                    picbxPwvDisMthdImage.Image = imageSubtracting;
                    picbxPwvDisMthdImage.ImageLocation = ConfigurationManager.AppSettings[GuiConstants.AppConfigParams.SetupScreenSubtracting.ToString()];
                    picbxPwvDisMthdImage.Height = imageSubtracting.Height;
                    picbxPwvDisMthdImage.Width = imageSubtracting.Width;

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
                    picbxPwvDisMthdImage.Height = imageDirect.Height;
                    picbxPwvDisMthdImage.Width = imageDirect.Width;

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
                    value = FemoralToCuffDefaultMmValue;
                    guiradlblCarotidTonometerUnits.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.Mm);
                    guiradlblCuffunits.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.Mm);
                    guiradlblFemoralToCuffUnits.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.Mm);
                    guiradtxtFemoralToCuff.Text = value.ToString();
                    guiradlblPwvDistanceUnits.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.Mm);
                    break;
                case (int)CrxGenPwvValue.CrxPwvDistDistUnitsCM:
                    // cm                    
                    value = FemoralToCuffDefaultCmValue;
                    guiradlblCarotidTonometerUnits.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.Cm);
                    guiradlblCuffunits.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.Cm);
                    guiradlblFemoralToCuffUnits.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.Cm);
                    guiradtxtFemoralToCuff.Text = value.ToString();
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
                                                                      Gender = guicmbxGender.Text.Trim(),
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
            }
        }

        /** This method displays data for patient being saved currently 
       * */
        private void DisplaySavedPatientData(CrxStructPatientDemographicData patientData)
        {
            // if record added / updated successfully 
            guipnlMeasurementDetails.Visible = true;
            objDefaultWindow.radtabCapture.Enabled = guiradbtnCapture.Enabled = !GuiCommon.IsWaitIntervalImposed;      
            SetHeightWeightUnits();
            SetBloodPressure();
            SetPwvDistanceMethodAndUnits();
                        
            if (crxMgrObject.PwvSettings.FemoralToCuff)
            {
                guiradtxtFemoralToCuff.ReadOnly = false;
            }

            LoadPatientList();
            guiradgrdPatientList.Enabled = true;
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

                // disable capture & report tab in edit mode
                objDefaultWindow.radtabReport.Enabled = false;
                objDefaultWindow.radtabCapture.Enabled = false;

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
                objDefaultWindow.radlblMessage.Text = string.Empty;
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
                objDefaultWindow.radtabCapture.Enabled = !GuiCommon.IsWaitIntervalImposed;
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
                    
                    if (dvSearch.Count == 1)
                    {
                        // dvSearch.AllowEdit = true;
                        prevMode = CurrentMode.SearchMode;
                        mode = CurrentMode.None;
                        DisplayLastRecord(int.Parse(guiradgrdPatientList.Rows[0].Cells[1].Value.ToString()), int.Parse(guiradgrdPatientList.Rows[0].Cells[2].Value.ToString()));
                        guiradbtnSearch.Enabled = false;
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
                    gender = guicmbxGender.Text.Trim();
                }
                else if (guicmbxGender.SelectedIndex > 0)
                {
                    gender = guicmbxGender.SelectedItem.ToString().Trim();
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
                    isSearchReset = false;
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
                // fetch PWV measurement details for patient & populate Biz session object
                FillPWVDetailsSession();                
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

        /** This method fills PWV measurement details from DB in Bizsession
         * */
        private void FillPWVDetailsSession()
        {
            DataSet dsPwv = dbMagr.GetPWVMeasurementDetails(int.Parse(radlblpatientinternalnumber.Text.Trim()), int.Parse(radlblgroupid.Text), bobj);

            if (dsPwv.Tables[0].Rows.Count > 0)
            {
                GuiCommon.HasMeasurementDetails = true;

                GuiCommon.PwvCurrentStudyDatetime = dsPwv.Tables[0].Rows[0][(int)CrxDBPWVMeasurementTableList.StudyDateTime].ToString();
                FillSessionData(dsPwv);

                // filling RHS pwv measurement data on setup screen 
                PerformHeightWeightConversion();                        

                guiradtxtOperator.Text = dsPwv.Tables[0].Rows[0][(int)CrxDBPWVMeasurementTableList.Operator].ToString();
                guiradtxtMedication.Text = dsPwv.Tables[0].Rows[0][(int)CrxDBPWVMeasurementTableList.Notes].ToString();                              
                                
                // switch (crxMgrObject.GeneralSettings.BloodPressureEntryOptions)
                switch (crxMgrObject.BpSettings.BloodPressure)
                {
                    // converting to int as crxMgrObject.GeneralSettings.BloodPressureEntryOptions returns int
                    case (int)CrxGenPwvValue.CrxGenBPOptSPandDP: 
                        guiradtxtSP.Text = dsPwv.Tables[0].Rows[0][(int)CrxDBPWVMeasurementTableList.SP].ToString().Equals(GuiConstants.DefaultValue.ToString()) ? string.Empty : dsPwv.Tables[0].Rows[0][(int)CrxDBPWVMeasurementTableList.SP].ToString();
                        guiradtxtDP.Text = dsPwv.Tables[0].Rows[0][(int)CrxDBPWVMeasurementTableList.DP].ToString().Equals(GuiConstants.DefaultValue.ToString()) ? string.Empty : dsPwv.Tables[0].Rows[0][(int)CrxDBPWVMeasurementTableList.DP].ToString();
                        break;
                    case (int)CrxGenPwvValue.CrxGenBPOptSPandMP:
                        guiradtxtSP.Text = dsPwv.Tables[0].Rows[0][(int)CrxDBPWVMeasurementTableList.SP].ToString().Equals(GuiConstants.DefaultValue.ToString()) ? string.Empty : dsPwv.Tables[0].Rows[0][(int)CrxDBPWVMeasurementTableList.SP].ToString();
                        guiradtxtDP.Text = dsPwv.Tables[0].Rows[0][(int)CrxDBPWVMeasurementTableList.MP].ToString().Equals(GuiConstants.DefaultValue.ToString()) ? string.Empty : dsPwv.Tables[0].Rows[0][(int)CrxDBPWVMeasurementTableList.MP].ToString();
                        break;
                    case (int)CrxGenPwvValue.CrxGenBPOptMPandDP:
                        guiradtxtSP.Text = dsPwv.Tables[0].Rows[0][(int)CrxDBPWVMeasurementTableList.MP].ToString().Equals(GuiConstants.DefaultValue.ToString()) ? string.Empty : dsPwv.Tables[0].Rows[0][(int)CrxDBPWVMeasurementTableList.MP].ToString();
                        guiradtxtDP.Text = dsPwv.Tables[0].Rows[0][(int)CrxDBPWVMeasurementTableList.DP].ToString().Equals(GuiConstants.DefaultValue.ToString()) ? string.Empty : dsPwv.Tables[0].Rows[0][(int)CrxDBPWVMeasurementTableList.DP].ToString();
                        break;
                    default:
                        guiradtxtSP.Text = string.Empty;
                        guiradtxtDP.Text = string.Empty;
                        break;
                }                

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

        /** This method initializes biz session object each time a patient record is selected/edited/added
        */
        private void FillSessionData(DataSet dsPwv)
        {
            FillSessionWithBloodPressureValues(dsPwv);
            FillSessionWithOtherValues(dsPwv);
           
            obj.systemId = (uint)bobj;
            obj.groupStudyId = (uint)GuiCommon.GroupId;

            objDefaultWindow.radtabReport.Enabled = true;
            objDefaultWindow.radtabCapture.Enabled = !GuiCommon.IsWaitIntervalImposed;
            obj.patientNumber = (uint)GuiCommon.PatientInternalNumber;           
        }

        /** This method fills session with height & weight, distance values
         * */
        private void FillSessionWithOtherValues(DataSet dsPwv)
        {
            obj.calculatedDistance = string.IsNullOrEmpty(dsPwv.Tables[0].Rows[0][(int)CrxDBPWVMeasurementTableList.PWVDistance].ToString()) ? (ushort)0 : ushort.Parse(dsPwv.Tables[0].Rows[0][(int)CrxDBPWVMeasurementTableList.PWVDistance].ToString());
            obj.heightAndWeight.heightInCentimetres = string.IsNullOrEmpty(dsPwv.Tables[0].Rows[0][(int)CrxDBPWVMeasurementTableList.HeightInCentimetres].ToString()) ? obj.heightAndWeight.heightInCentimetres : ushort.Parse(dsPwv.Tables[0].Rows[0][(int)CrxDBPWVMeasurementTableList.HeightInCentimetres].ToString());
            obj.heightAndWeight.heightInInches = string.IsNullOrEmpty(dsPwv.Tables[0].Rows[0][(int)CrxDBPWVMeasurementTableList.HeightInInches].ToString()) ? obj.heightAndWeight.heightInInches : ushort.Parse(dsPwv.Tables[0].Rows[0][(int)CrxDBPWVMeasurementTableList.HeightInInches].ToString());
            obj.heightAndWeight.weightInKilograms = string.IsNullOrEmpty(dsPwv.Tables[0].Rows[0][(int)CrxDBPWVMeasurementTableList.WeightInKilograms].ToString()) ? obj.heightAndWeight.weightInKilograms : ushort.Parse(dsPwv.Tables[0].Rows[0][(int)CrxDBPWVMeasurementTableList.WeightInKilograms].ToString());
            obj.heightAndWeight.weightInPounds = string.IsNullOrEmpty(dsPwv.Tables[0].Rows[0][(int)CrxDBPWVMeasurementTableList.WeightInPounds].ToString()) ? obj.heightAndWeight.weightInPounds : ushort.Parse(dsPwv.Tables[0].Rows[0][(int)CrxDBPWVMeasurementTableList.WeightInPounds].ToString());
            obj.notes = dsPwv.Tables[0].Rows[0][(int)CrxDBPWVMeasurementTableList.Notes].ToString();
            obj.operatorId = dsPwv.Tables[0].Rows[0][(int)CrxDBPWVMeasurementTableList.Operator].ToString();
            obj.myCarotidDistance.distance = string.IsNullOrEmpty(dsPwv.Tables[0].Rows[0][(int)CrxDBPWVMeasurementTableList.Carotid].ToString()) ? obj.myCarotidDistance.distance : ushort.Parse(dsPwv.Tables[0].Rows[0][(int)CrxDBPWVMeasurementTableList.Carotid].ToString());
            obj.myCuffDistance.distance = string.IsNullOrEmpty(dsPwv.Tables[0].Rows[0][(int)CrxDBPWVMeasurementTableList.Cuff].ToString()) ? obj.myCuffDistance.distance : ushort.Parse(dsPwv.Tables[0].Rows[0][(int)CrxDBPWVMeasurementTableList.Cuff].ToString());
            obj.myFemoral2CuffDistance.distance = string.IsNullOrEmpty(dsPwv.Tables[0].Rows[0][(int)CrxDBPWVMeasurementTableList.FemoraltoCuff].ToString()) ? obj.myFemoral2CuffDistance.distance : ushort.Parse(dsPwv.Tables[0].Rows[0][(int)CrxDBPWVMeasurementTableList.FemoraltoCuff].ToString());
            obj.myPWVDirectDistance.distance = string.IsNullOrEmpty(dsPwv.Tables[0].Rows[0][(int)CrxDBPWVMeasurementTableList.Direct].ToString()) ? obj.myPWVDirectDistance.distance : ushort.Parse(dsPwv.Tables[0].Rows[0][(int)CrxDBPWVMeasurementTableList.Direct].ToString());
            obj.heightAndWeight.bodyMassIndex = string.IsNullOrEmpty(dsPwv.Tables[0].Rows[0][(int)CrxDBPWVMeasurementTableList.BodyMassIndex].ToString()) ? 0 : float.Parse(dsPwv.Tables[0].Rows[0][(int)CrxDBPWVMeasurementTableList.BodyMassIndex].ToString());
            obj.distanceMethod = ushort.Parse(dsPwv.Tables[0].Rows[0][(int)CrxDBPWVMeasurementTableList.PWVDistanceMethod].ToString());          
        }

        /** This method fills session with blood pressure values
         * */
        private void FillSessionWithBloodPressureValues(DataSet dsPwv)
        {
            obj.bloodPressureEntryOption = string.IsNullOrEmpty(dsPwv.Tables[0].Rows[0][(int)CrxDBPWVMeasurementTableList.BloodPressureEntryOption].ToString()) ? (ushort)0 : ushort.Parse(dsPwv.Tables[0].Rows[0][(int)CrxDBPWVMeasurementTableList.BloodPressureEntryOption].ToString());

            switch (obj.bloodPressureEntryOption)
            {
                // converting to ushort as obj.bloodPressureEntryOption returns ushort
                case (ushort)CrxGenPwvValue.CrxGenBPOptSPandDP:
                    obj.bloodPressure.SP.Reading = ushort.Parse(dsPwv.Tables[0].Rows[0][(int)CrxDBPWVMeasurementTableList.SP].ToString());
                    obj.bloodPressure.DP.Reading = ushort.Parse(dsPwv.Tables[0].Rows[0][(int)CrxDBPWVMeasurementTableList.DP].ToString());
                    break;
                case (ushort)CrxGenPwvValue.CrxGenBPOptSPandMP:
                    obj.bloodPressure.SP.Reading = ushort.Parse(dsPwv.Tables[0].Rows[0][(int)CrxDBPWVMeasurementTableList.SP].ToString());
                    obj.bloodPressure.MP.Reading = ushort.Parse(dsPwv.Tables[0].Rows[0][(int)CrxDBPWVMeasurementTableList.MP].ToString());
                    break;
                case (ushort)CrxGenPwvValue.CrxGenBPOptMPandDP:
                    obj.bloodPressure.MP.Reading = ushort.Parse(dsPwv.Tables[0].Rows[0][(int)CrxDBPWVMeasurementTableList.MP].ToString());
                    obj.bloodPressure.DP.Reading = ushort.Parse(dsPwv.Tables[0].Rows[0][(int)CrxDBPWVMeasurementTableList.DP].ToString());
                    break;
                default:
                    break;
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
                    guiradtxtsetupheight.Text = obj.heightAndWeight.heightInCentimetres.ToString().Equals(GuiConstants.DefaultValue.ToString()) ? string.Empty : obj.heightAndWeight.heightInCentimetres.ToString();

                    guiradtxtWeight.Text = obj.heightAndWeight.weightInKilograms.ToString().Equals(GuiConstants.DefaultValue.ToString()) ? string.Empty : obj.heightAndWeight.weightInKilograms.ToString();
                    break;
                case (int)CrxGenPwvValue.CrxGenHeightWeightImperial:
                    if (obj.heightAndWeight.heightInInches != GuiConstants.DefaultValue)
                    {
                        // convert height in inches to feet & inches
                        heightInInches = int.Parse(obj.heightAndWeight.heightInInches.ToString()) % 12;
                        heigthInFeet = int.Parse(obj.heightAndWeight.heightInInches.ToString()) / 12;

                        guiradtxtsetupheight.Text = heigthInFeet.ToString();
                        guiradtxtImperialHeight.Text = heightInInches.ToString();
                    }

                    guiradtxtWeight.Text = obj.heightAndWeight.weightInPounds.Equals(GuiConstants.DefaultValue) ? string.Empty : obj.heightAndWeight.weightInPounds.ToString();
                   
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
                GuiCommon.CaptureTabClick = false;              
                StartCaptureProcess(sender, e);
                GuiCommon.CaptureTabClick = true;              
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
            if (ValidatePatientAge())
            {
                // if (GuiCommon.IsValueOutsideLimits)
                // {
                // GuiCommon.IsValueOutsideLimits = false;
                // objDefaultWindow.radpgTabCollection.SelectedPage = objDefaultWindow.guiradgrpbxPwvDistanceMethod;
                // objDefaultWindow.guiradgrpbxPwvDistanceMethod.Enabled = true;
                // return;
                // }
                if (!objValidation.CheckMandatoryFields())
                {
                    // check for electronic module is connected. 
                    if (DalModule.Instance.CheckIfDeviceIsConnected())
                    {
                        FillSessionWithModifiedMeasuremt();

                        // check for valid measurement details
                        if (obj.Validate())
                        {
                            // go to capture screen once electonic module is found & data is valid                   
                            GuiCommon.CaptureChildForm = new Capture(objDefaultWindow)
                                                                      {
                                                                          TopLevel = false,
                                                                          Dock = DockStyle.Fill,
                                                                          FormBorderStyle = FormBorderStyle.None
                                                                      };

                            // adds capture form under parent window control
                            var page = objDefaultWindow.radpgTabCollection.Pages[1];
                            GuiCommon.CaptureChildForm.Parent = page;
                            page.Controls.Clear();

                            page.Controls.Add(GuiCommon.CaptureChildForm);
                            GuiCommon.CaptureChildForm.Show();

                            // GuiCommon.CaptureTabClick = false;
                            objDefaultWindow.radpgTabCollection.SelectedPage = objDefaultWindow.radtabCapture;
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

        /** This method fills session object with measurement data
          * */
        private void FillSessionWithModifiedMeasuremt()
        {
            obj.groupStudyId = (uint)GuiCommon.GroupId;
            obj.systemId = (uint)GuiCommon.SystemIdentifier;
            obj.patientNumber = (uint)GuiCommon.PatientInternalNumber;
            
            SetSessionWithModifiedHeightWeight();
            SetSessionWithModifiedBP();
            SetSessionWithModifiedDistance();

            obj.notes = guiradtxtMedication.Text;
            obj.operatorId = guiradtxtOperator.Text;
            
            // obj.bloodPressureEntryOption = (ushort)crxMgrObject.GeneralSettings.BloodPressureEntryOptions;
            obj.bloodPressureEntryOption = (ushort)crxMgrObject.BpSettings.BloodPressure;
        }

        /** This method fills session with modified height & weights
         * */
        private void SetSessionWithModifiedHeightWeight()
        {  
            // height & weight
            switch (crxMgrObject.GeneralSettings.HeightandWeightUnit)
            {
                // converting to int as crxMgrObject.GeneralSettings.HeightandWeightUnit returns int
                case (int)CrxGenPwvValue.CrxGenHeightWeightMetric:
                    obj.heightAndWeight.heightInCentimetres = string.IsNullOrEmpty(guiradtxtsetupheight.Text) ? GuiConstants.DefaultValue : ushort.Parse(guiradtxtsetupheight.Text);
                    obj.heightAndWeight.weightInKilograms = string.IsNullOrEmpty(guiradtxtWeight.Text) ? GuiConstants.DefaultValue : ushort.Parse(guiradtxtWeight.Text);
                    break;

                case (int)CrxGenPwvValue.CrxGenHeightWeightImperial:
                    if ((guiradtxtsetupheight.Text.Length > 0) || (guiradtxtImperialHeight.Text.Length > 0))
                    {
                        // Checking if the inch/feet field is blank then setting it to zero.
                        // using local variable to store the text of guiradtxtImperialHeight and guiradtxtsetupheight.
                        string guiRadTxtImperialHeight = guiradtxtImperialHeight.Text.Equals(string.Empty) ? "0" : guiradtxtImperialHeight.Text;
                        string guiRadTxtSetUpheight = guiradtxtsetupheight.Text.Equals(string.Empty) ? "0" : guiradtxtsetupheight.Text;                        
                        int heightInInches = (int.Parse(guiRadTxtSetUpheight) * 12) + int.Parse(guiRadTxtImperialHeight);
                        obj.heightAndWeight.heightInInches = (ushort)heightInInches;
                    }
                    else
                    {
                        obj.heightAndWeight.heightInInches = GuiConstants.DefaultValue;
                    }

                    obj.heightAndWeight.weightInPounds = string.IsNullOrEmpty(guiradtxtWeight.Text) ? GuiConstants.DefaultValue : ushort.Parse(guiradtxtWeight.Text);
                    break;
                default:
                    break;
            }
        }

        /** This method fills session with modified blood pressure values
         * */
        private void SetSessionWithModifiedBP()
        {
            // blood pressure values
            switch (obj.bloodPressureEntryOption)
            {
                case (int)CrxGenPwvValue.CrxGenBPOptSPandDP: 
                    obj.bloodPressure.SP.Reading = string.IsNullOrEmpty(guiradtxtSP.Text) ? GuiConstants.DefaultValue : ushort.Parse(guiradtxtSP.Text);
                    obj.bloodPressure.DP.Reading = string.IsNullOrEmpty(guiradtxtDP.Text) ? GuiConstants.DefaultValue : ushort.Parse(guiradtxtDP.Text);
                    obj.bloodPressure.MP.Reading = GuiConstants.DefaultValue;
                    break;

                case (int)CrxGenPwvValue.CrxGenBPOptSPandMP: 
                    obj.bloodPressure.SP.Reading = string.IsNullOrEmpty(guiradtxtSP.Text) ? GuiConstants.DefaultValue : ushort.Parse(guiradtxtSP.Text);
                    obj.bloodPressure.MP.Reading = string.IsNullOrEmpty(guiradtxtDP.Text) ? GuiConstants.DefaultValue : ushort.Parse(guiradtxtDP.Text);
                    obj.bloodPressure.DP.Reading = GuiConstants.DefaultValue;
                    break;

                case (int)CrxGenPwvValue.CrxGenBPOptMPandDP:
                    obj.bloodPressure.MP.Reading = string.IsNullOrEmpty(guiradtxtSP.Text) ? GuiConstants.DefaultValue : ushort.Parse(guiradtxtSP.Text);
                    obj.bloodPressure.DP.Reading = string.IsNullOrEmpty(guiradtxtDP.Text) ? GuiConstants.DefaultValue : ushort.Parse(guiradtxtDP.Text);
                    obj.bloodPressure.SP.Reading = GuiConstants.DefaultValue;
                    break;

                default:
                    obj.bloodPressure.SP.Reading = GuiConstants.DefaultValue;
                    obj.bloodPressure.DP.Reading = GuiConstants.DefaultValue;
                    obj.bloodPressure.MP.Reading = GuiConstants.DefaultValue;
                    break;
            }
        }

        /** This method fills session with modified distance values
         * */
        private void SetSessionWithModifiedDistance()
        {
            obj.distanceMethod = (ushort)crxMgrObject.PwvSettings.PWVDistanceMethod;

            // distance values
            switch (crxMgrObject.PwvSettings.PWVDistanceMethod)
            {
                case (int)CrxGenPwvValue.CrxPwvDistMethodSubtract:
                    // subtracting
                    // populate carotid, cuff & femoral to cuff textboxes
                    obj.myCarotidDistance.distance = string.IsNullOrEmpty(guiradtxtCarotid.Text) ? GuiConstants.DefaultValue : ushort.Parse(guiradtxtCarotid.Text);
                    obj.myCuffDistance.distance = string.IsNullOrEmpty(guiradtxtCuff.Text) ? GuiConstants.DefaultValue : ushort.Parse(guiradtxtCuff.Text);
                    obj.myFemoral2CuffDistance.distance = string.IsNullOrEmpty(guiradtxtFemoralToCuff.Text) ? GuiConstants.DefaultValue : ushort.Parse(guiradtxtFemoralToCuff.Text);

                    // obj.calculatedDistance = string.IsNullOrEmpty(guiradlblResult.Text) ? GuiConstants.DefaultValue : ushort.Parse(guiradlblResult.Text);
                    obj.myPWVDirectDistance.distance = GuiConstants.DefaultValue;
                    break;

                case (int)CrxGenPwvValue.CrxPwvDistMethodDirect:
                    // direct
                    // populate direct & femoral to cuff textboxes
                    obj.myCarotidDistance.distance = GuiConstants.DefaultValue;
                    obj.myCuffDistance.distance = GuiConstants.DefaultValue;
                    obj.myFemoral2CuffDistance.distance = string.IsNullOrEmpty(guiradtxtFemoralToCuff.Text) ? GuiConstants.DefaultValue : ushort.Parse(guiradtxtFemoralToCuff.Text);

                    // obj.calculatedDistance = string.IsNullOrEmpty(guiradlblResult.Text) ? GuiConstants.DefaultValue : ushort.Parse(guiradlblResult.Text);
                    obj.myPWVDirectDistance.distance = string.IsNullOrEmpty(guiradtxtCuff.Text) ? GuiConstants.DefaultValue : ushort.Parse(guiradtxtCuff.Text);
                    break;

                default:
                    break;
            }

            if (crxMgrObject.PwvSettings.PWVDistanceUnits.Equals((int)CrxGenPwvValue.CrxPwvDistDistUnitsCM))
            {
                obj.myCarotidDistance.distance = obj.myCarotidDistance.distance.Equals(GuiConstants.DefaultValue) ? obj.myCarotidDistance.distance : (ushort)(obj.myCarotidDistance.distance * GuiConstants.DivisionFactor);
                obj.myCuffDistance.distance = obj.myCuffDistance.distance.Equals(GuiConstants.DefaultValue) ? obj.myCuffDistance.distance : (ushort)(obj.myCuffDistance.distance * GuiConstants.DivisionFactor);
                obj.myFemoral2CuffDistance.distance = obj.myFemoral2CuffDistance.distance.Equals(GuiConstants.DefaultValue) ? obj.myFemoral2CuffDistance.distance : (ushort)(obj.myFemoral2CuffDistance.distance * GuiConstants.DivisionFactor);
                obj.myPWVDirectDistance.distance = obj.myPWVDirectDistance.distance.Equals(GuiConstants.DefaultValue) ? obj.myPWVDirectDistance.distance : (ushort)(obj.myPWVDirectDistance.distance * GuiConstants.DivisionFactor);  
            }
        }

        /** This method subscribes all the text boxes & drop down for changes made to it.
         * To the form changed event which will determine for any changes made before application is closed
         * */
        private void SubscribeSetupFormChanges()
        {
            // subscribe text change events to determine any form changes
            guiradtxtPatientID.TextChanged += GuiCommon.FormChanged;
            guiradtxtFirstName.TextChanged += GuiCommon.FormChanged;
            guiradtxtLastName.TextChanged += GuiCommon.FormChanged;           
            guicmbxYear.SelectedIndexChanged += GuiCommon.FormChanged;
            guicmbxGender.SelectedIndexChanged += GuiCommon.FormChanged;
            guicmbxMonth.SelectedIndexChanged += GuiCommon.FormChanged;
            guicmbDay.TextChanged += GuiCommon.FormChanged;
           
            // subscribe key press events for measurement fields to allow numeric values
            guiradtxtsetupheight.KeyPress += GuiCommon.CheckForNumericValues;
            guiradtxtImperialHeight.KeyPress += GuiCommon.CheckForNumericValues;
            guiradtxtWeight.KeyPress += GuiCommon.CheckForNumericValues;
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
            objValidation.CheckFieldLimits(guiradtxtsetupheight);
        }

        /** This event gets fired when focus is moved from height in inches text box.
        * It checks if the value entered in textbox is within valid range and shows error accordingly
        * */
        private void guiradtxtImperialHeight_Leave(object sender, EventArgs e)
        {
            objValidation.CheckFieldLimits(guiradtxtImperialHeight);
        }

        /** This event gets fired when focus is moved from weight text box.
       * It checks if the value entered in textbox is within valid range and shows error accordingly
       * */
        private void guiradtxtWeight_Leave(object sender, EventArgs e)
        {
            objValidation.CheckFieldLimits(guiradtxtWeight);
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
            // if (GuiCommon.CaptureChildForm.Equals(null))
            // {
            //    GuiCommon.CaptureChildForm.Close();
            //    // GuiCommon.CaptureChildForm = null;
            // }
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
                switch (obj.ValidateAgeLimit(ref message))
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
            guiradgrdPatientList.Focus();
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
    }   
}
