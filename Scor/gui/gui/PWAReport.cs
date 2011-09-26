using System;
using System.Data;
using System.Drawing;
using System.Windows.Forms;
using Telerik.WinControls;
using Telerik.WinControls.UI;
using AtCor.Scor.CrossCutting;
using AtCor.Scor.CrossCutting.Configuration;
using AtCor.Scor.CrossCutting.Logging;
using AtCor.Scor.CrossCutting.DatabaseManager;
using AtCor.Scor.CrossCutting.Messaging;
using AtCor.Scor.BusinessLogic;
using System.Windows.Forms.DataVisualization.Charting;
using Telerik.WinControls.Primitives;
using System.Collections;
using System.Collections.Generic;

namespace AtCor.Scor.Gui.Presentation
{
    public partial class PWAReport : RadForm
    {
        // Events              
        // Using the same event as that of PWV for showing values on the Setup screen for PWA mode.
        public static event EventHandler OnPwaMeasurementChangedEvent;

        const int MaxLabelYValue = 12; // this denotes the maximum number of values to be displayed on Y axis so that it does not overlap                      
        const int LblVerticalAngle = -90; // angle of labels to display vertically on analysis screen when more records are are selected
        const int LblHorizontalAngle = 0; // angle of labels to display horizontally on analysis screen when few records are are selected
        const string CulturalNeutralDateFormat = "yyyy-MM-dd HH:mm:ss"; // this is a cultural neutral format used for fetching data for different regional settings from back end

        readonly string serverNameString = string.Empty;
        readonly BizPatient patientObj = BizPatient.Instance();
        GuiFieldValidation objValidation;
        CrxMessagingManager oMsgMgr;
        CrxConfigManager crxMgrObject;
        CrxDBManager dbMagr;
       // BizPWA obj;

       // GuiFieldValidation objValidateReport;
        CrxStructPWAMeasurementData crxPwaData = new CrxStructPWAMeasurementData();
       CrxStructCuffPWAMeasurementData crxPwaCuffData = new CrxStructCuffPWAMeasurementData();
       CrxStructTonoPWAMeasurementData crxPwaTonoData = new CrxStructTonoPWAMeasurementData(); 
        int bobj;
        int numeberOfRecordsSelected;
        string dateToCompare = string.Empty; // used to compare dates when 30 sec wait interval is imposed to enable / disable repeat button based on last record selected
        string pwaIdWithComma = string.Empty;
        int recordsToDelete; // this variable holds value for number of records to delete and is used across dfifferent methods 
        string lastAssessmentDate = string.Empty;
        string pwaIdToCompare = string.Empty; // used to compare Pwa id when 30 sec wait interval is imposed to enable / disable repeat button based on last record selected
        string lastAssessmentPwaId = string.Empty;
        private DefaultWindow objDefaultWindow;
      
        string[] apRate; // Ap rate array to be used on analysis screen
        string[] hrRate; // Hr rate array to be used on analysis screen
        string[] spRate; // Sp rate array to be used on analysis screen
        string[] dpRate; // Dp rate array to be used on analysis screen
        string[] mpRate; // Mp rate array to be used on analysis screen
        string[] aix75Rate; // Aix rate array to be used on analysis screen
        string[] ppRate; // Pp rate array to be used on analysis screen

        // denotes tick and cross indexes to be assigned from ImageList
        enum TickCrossImage
        {
            Cross = 0,
            Tick = 1
        }

        enum InitializeCrxValue
        {
            UpdateData = 0,
            ValidationFailed,
            ReportCalculationFailed
        }
        
        public PWAReport(DefaultWindow defWindow)
        {
            try
            {
                InitializeComponent();

                // GuiCommon.SetFontForControls(this);
                // SetFontForChartTitles();

                //// subscribe for form changes
                // SubscribeReportFormChanges();
                InitializeReportScreenPWA();

                // set the default window
                objDefaultWindow = defWindow;

                // initialize servername string
                serverNameString = GuiCommon.ServerNameString();
               // obj = (BizPWA)BizSession.Instance().measurement;

                // subscribe report tab click event
                DefaultWindow.OnPWAReportTabClick += PWAReport_Load;
                              
                Presentation.Capture.OnPWAReportTabClick += PWAReport_Load;
                guiradtxtReportHeightInches.KeyPress += GuiCommon.CheckForNumericValues;
                guiradtxtReportHeight.KeyPress += GuiCommon.CheckForNumericValues;
                 GuiCommon.OnCaptureClosing += EnableRepeatAndCaptureTab;                
                 objValidation = new GuiFieldValidation(guipnlReportPatientMeasurementDetails);
            }
            catch (Exception ex)
            {
                GUIExceptionHandler.HandleException(ex, this);
            }
        }

        /**This method is called on the tick of wait interval  timer used on the Default window.
         * On the tick of the timer we enable the repeat button on the Report screen along with the Capture tab.
         */
        public void EnableRepeatAndCaptureTab(bool value)
        {
            try
            {
                // GuiCommon.IsWaitIntervalImposed = !value;
                GuiCommon.CaptureToSetup = !value;

                objDefaultWindow.radtabCapture.Enabled = false;
                guiradbtnRepeat.Enabled = value;

                if (value)
                {
                    CheckLastAssessmentSelected(pwaIdToCompare);
                }
            }
            catch (Exception ex)
            {
                GUIExceptionHandler.HandleException(ex, this);
            }
        }

        public void LoadPWAReport()
        {
            bobj = GuiConstants.SystemId;
            GuiCommon.CaptureToSetup = false;
            GuiCommon.SystemIdentifier = bobj;
            GuiCommon.ReportLoadCount++;

            // Clearing the capture time label on load.
            objDefaultWindow.radlblCaptureTime.Text = string.Empty;
          
            // set default text for report tab
            objDefaultWindow.radtabReport.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.TabReport);
            objDefaultWindow.radtabCapture.Enabled = false;
            InitializeReportAssessmentList();
            SetDefaultValuesOnLoad();
            SetPwaReportTagForValidation();

            // fill demographic & pwa measurement details & bring the LHS to browse mode
            FillDemographicDetailsReport();

            // initialize crx when user moves from setup to report... call populate method
            InitializeCrxFromSetupToReport(string.Empty);

            // binds assessment details related to patient
            FillPatientAssessmentDetailsReport();
           
            // If Augumentation Index is checked in PWA Settings tab 
            if (crxMgrObject.PwaSettings.AugmentationIndex)
            {
                guiradlblReportAIx.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.LblAix);
            }
            else
            {
                guiradlblReportAIx.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.LblPwaReportAIX75);
            }
             
            guipnlPWAReport.Visible = true;
            guipnlPWAReportAnalysis.Visible = false;
            // if (!string.IsNullOrEmpty(GuiCommon.bizPwaobject.GetInconclusiveNoteMsgKey()))
            if (!string.IsNullOrEmpty(GuiCommon.InConclusiveMessageForPwaCapture))
            {
                objDefaultWindow.radlblMessage.Text = string.Format("{0} {1}", CrxMessagingManager.Instance.GetMessage(CrxStructCommonResourceMsg.GuiInConclusivePwaReportInitialMesg), GuiCommon.InConclusiveMessageForPwaCapture);
                GuiCommon.InConclusiveMessageForPwaCapture = string.Empty;
                GuiCommon.DefaultWindowForm.guialertmsgTimer.Enabled = true;                
                GuiCommon.DefaultWindowForm.guialertmsgTimer.Tick += new EventHandler(DisplayInconclusiveMessage);                
            }            
        }

        /** This method sets tag property of textbox and labels for validating measurement details on report screen.
          * It helps in identifying labels & textbox which are mandatory and marked for validation by business logic
          * */
        private void SetPwaReportTagForValidation()
        {
            guiradtxtReportHeight.Tag = crxMgrObject.GeneralSettings.HeightandWeightUnit.Equals((int)CrxGenPwvValue.CrxGenHeightWeightMetric) ? oMsgMgr.GetMessage(CrxStructCommonResourceMsg.FieldPatientHeight) : oMsgMgr.GetMessage(CrxStructCommonResourceMsg.FieldPatientHeightFoot);
            guiradtxtReportHeightInches.Tag = crxMgrObject.GeneralSettings.HeightandWeightUnit.Equals((int)CrxGenPwvValue.CrxGenHeightWeightMetric) ? string.Empty : oMsgMgr.GetMessage(CrxStructCommonResourceMsg.FieldPatientHeightInch);
        }

        // AtCor-Drop2-Sprint1
        private void SetTextForPWAReport()
        {
            guiradlblReportAssessments.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.LblReportAssessments);
            guiradlblReportPatientId.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.LblPatientId);
            guiradlblReportPatientName.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.LblPatientName);
            guiPwaClinicalReport.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.PwaClinicalReport);
            // guiPwaEvaluationReport.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.PwaEvaluationReport);

            // Commenting the below code as group name is not included in Clinical mode.
            // guiradlblReportGroup.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.LblGroup);
            guiradlblReportDOB.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.LblReportDob);
            guiradlblReportAge.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.LblReportAge);
            guiradlblReportheightWeight.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.LblHeight);          
            guiradlblReportOperator.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.LblOperator);

            // guiradlblNotes.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.LblNotes);
            guiradbtnreportsave.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.BtnSave);
            guiradbtnreportcancel.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.BtnCancel);
            guiradbtnreportedit.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.BtnEdit);
            guiradbtnRepeat.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.BtnRepeat);
            guiradbtnPrint.Text = guiradbtnAnalysisPrint.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.BtnPrint);
            guiradbtnDelete.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.BtnDelete);
            guiradlblPWASP.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.Sp);
            guiradlblPWAPP.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.LblPP);
            guiradlblPWAAP.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.LblAp);
            guiradlblReportAIx.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.LblAix);
            guiradlblReportHR.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.LblHr);
            guiradlblReportDP.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.LblCentralDp);
            guiradlblSphygmocorReferenceAge.Text = String.Format("{0}{1}", oMsgMgr.GetMessage(CrxStructCommonResourceMsg.LblPwaSyphymocorRefAge), " > 70");
            guioradlblAvgCentralAortlcPulse.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.LblAvgCentralAorticPulse);
            guiradlblQualityControl.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.LblPwaQualityControl);
            slashlabel.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.GuiDisplaySlash);
            guiradlblReportDPUnits.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.UnitsPressureMmhg);
            guiradlblInterpretation.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.LblPwaInterpretation);
            guiradlblReportGender.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.LblReportGender);
            // guiradbtnPrint.DefaultItem = crxMgrObject.PwaSettings.DefaultReport.Equals(CrxStructCommonResourceMsg.PwaClinicalReport) ? guiPwaClinicalReport : guiPwaEvaluationReport;
            guiradbtnPrint.DefaultItem = guiPwaClinicalReport;
        }

        private void InitializeReportScreenPWA()
        {
            dbMagr = CrxDBManager.Instance;
            oMsgMgr = CrxMessagingManager.Instance;
            crxMgrObject = CrxConfigManager.Instance;

            // AtCor-Drop2-Sprint1
            SetTextForPWAReport();
            
            crxMgrObject.GetGeneralUserSettings();
            
            crxMgrObject.GetPwvUserSettings();

            crxMgrObject.GetPwaUserSettings();

            SetShape(guiradlblReportNotesDisplay, guilblReportPatientIdValue, guilblReportDobValue, guilblReportAgeValue, guilblReportGenderValue, guiradlblreportSPdisplay, guiradlblreportDPdisplay, guiradlblReportOperatordisplay, guiradlblReportHeightDisplay, guiradlblReportHeightInches, guiradlblreportMPdisplay, guiradlblInterpretationDisplay, guiradlblCentralDp, guiradlblCentralHr, guiradlblCentralQualityControl);
            SetShape(guiradtxtMedicationNotesValue, guiradtxtReportBloodPressure1, guiradtxtReportBloodPressure2, guiradtxtReportOperator, guiradtxtReportHeightInches, guiradtxtReportHeight, guiradtxtReportBloodPressure3, guiradtxtCentralDpValue, guiradtxtCentralHrValue, guiradtxtCentralQualityControlValue, guiradtxtInterpretation);
        }

        // End: AtCor-Drop2-Sprint1, TM, Prototype,9th June, 2011

        /**This method is used to round the text boxes and the label controls on the Report screen.
        */
        private void SetShape(params Control[] labelControl)
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
                    label.RootElement.BackColor = Color.Transparent;
                    ((FillPrimitive)label.LabelElement.Children[0]).NumberOfColors = 1;

                    label.LabelElement.Shape = shape;
                }

                RadTextBox textBox = control as RadTextBox;

                if (textBox != null)
                {
                    textBox.TextBoxElement.BackColor = Color.FromArgb(172, 177, 204);
                    textBox.TextBoxElement.Fill.BackColor = Color.FromArgb(172, 177, 204);

                    textBox.TextBoxElement.Border.Shape = shape;
                    textBox.TextBoxElement.Fill.Shape = shape;
                }
            }
        }

        private void PWAReport_Load(object sender, EventArgs e)
        {                           
            // below statement checks if Invoke required and calls the report load event again to populate report data
            // without this report data will not be loaded when it this event is invoked from other windows
            if (InvokeRequired)
            {
                Invoke(new EventHandler(PWAReport_Load));
                return;
            }

            LoadPWAReport();
            CheckForSimualtionMode();
        }
        
        /**This method fill assessment details for a particular patient
        * */
        void FillPatientAssessmentDetailsReport()
        {
            try
            {
                // check db connection
                if (dbMagr.CheckConnection(serverNameString, crxMgrObject.GeneralSettings.SourceData) == 0)
                {        
                    DataSet ds = dbMagr.GetCuffPWAMeasurementDetails(int.Parse(patientObj.patientNumber.ToString()), GuiCommon.GroupId, bobj);
                                        
                    guiradgridReportAssessment.DataSource = ds.Tables[0];

                    // guiradchkAssesments.Checked = false;
                    if (ds.Tables[0].Rows.Count > 0)
                    {
                        guiradbtnreportedit.Enabled = true;

                        // sets assessment count for a label                        
                        GuiCommon.HasMeasurementDetails = true;
                        guiradgridReportAssessment.MasterTemplate.Rows[ds.Tables[0].Rows.Count - 1].Cells[0].Value = true;
                        guiradbtnDelete.Enabled = true;
                        guiradbtnPrint.Enabled = true;
                        guiradbtnRepeat.Enabled = true;
                        objDefaultWindow.radtabReport.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.TabReport);

                       // lastAssessmentDate = dateToCompare = guiradgridReportAssessment.MasterTemplate.Rows[ds.Tables[0].Rows.Count - 1].Cells[1].Value.ToString();
                        lastAssessmentPwaId = pwaIdToCompare = guiradgridReportAssessment.MasterTemplate.Rows[ds.Tables[0].Rows.Count - 1].Cells[2].Value.ToString();
                        pwaIdWithComma = guiradgridReportAssessment.MasterTemplate.Rows[ds.Tables[0].Rows.Count - 1].Cells[2].Value.ToString() + oMsgMgr.GetMessage(CrxStructCommonResourceMsg.GuiDisplayComma);
                        recordsToDelete = 1;

                        if (!GuiCommon.SetupToReport)
                        {
                            // this will populate biz session obj from latest PWA details
                            InitializeCrxOnLoad(guiradgridReportAssessment.MasterTemplate.Rows[ds.Tables[0].Rows.Count - 1].Cells[2].Value.ToString());
                        }

                        GuiCommon.SetupToReport = false;

                        if (ds.Tables[0].Rows.Count == 1)
                        {
                            // guiradchkAssesments.Checked = true;
                            // guiradchkAssesments.Enabled = false;

                            // Since there is only one record in the assessment grid, and it should be checked by default hence making the check box readonly.
                            guiradgridReportAssessment.Rows[0].Cells[0].ReadOnly = true;
                            guipnlPWAReport.Visible = true;
                            guipnlPWAReportAnalysis.Visible = false;
                        }

                        FillPWAMeasurementDetailsReport();
                        ShowAixTracker(26, -8, crxPwaData.C_Agph, -2, 20);
                        ShowSpTracker(130, 90, crxPwaData.C_Sp, 96, 120);
                        float centralPp;
                        centralPp = crxPwaData.C_Sp - crxPwaData.C_Dp;
                        ShowPpTracker(25, 0, centralPp, 5, 20);
                        ShowApTracker(12, -6, crxPwaData.C_Ap, -3, 9);
                        PlotAvgAorticPulseChart();                        
                    }
                    else
                    {
                        guiradbtnreportedit.Enabled = false;
                        guiradbtnDelete.Enabled = false;
                        guiradbtnPrint.Enabled = false;
                        ClearChartData();
                        ResetMeasurementFields();
                        guipnlPWAReport.Visible = true;
                        guipnlPWAReportAnalysis.Visible = false;
                        GuiCommon.HasMeasurementDetails = false;
                        objDefaultWindow.radtabReport.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.TabReport);
                        guiradbtnRepeat.Enabled = objDefaultWindow.radtabCapture.Enabled = false;
                    }
                }
                else
                {
                    DialogResult result = RadMessageBox.Show(this, GuiCommon.ConnectionErrorString(), oMsgMgr.GetMessage(CrxStructCommonResourceMsg.SystemError), MessageBoxButtons.RetryCancel, RadMessageIcon.Error);
                    if (result == DialogResult.Retry)
                    {
                        FillPatientAssessmentDetailsReport();
                    }
                }
            }
            catch (Exception ex)
            {
                GUIExceptionHandler.HandleException(ex, this);
            }
        }

        /**This method fill PWA measurement details for a particular patient
        * */
        void FillPWAMeasurementDetailsReport()
        {
            const int LblReportNotesDisplayMaximumLength = 44; // denotes the maximum length of guiradlblReportNotesDisplay label

            // create biz session instance & bind details to labels                                 
            guiradlblReportOperatordisplay.Text = guiradtxtReportOperator.Text = GuiCommon.bizPwaobject.operatorId;

            guiradlblReportNotesDisplay.Text = guiradtxtMedicationNotesValue.Text = GuiCommon.bizPwaobject.notes;
                    
            //// Since AutoEllipsis propert works only on singleline we are using code to check maximum length for label
            if (guiradlblReportNotesDisplay.Text.Length > LblReportNotesDisplayMaximumLength)
            {
                guiradlblReportNotesDisplay.Text = guiradlblReportNotesDisplay.Text.Substring(0, LblReportNotesDisplayMaximumLength - 3);
                guiradlblReportNotesDisplay.Text = string.Format("{0}...", guiradlblReportNotesDisplay.Text);
            }

            guiradlblInterpretationDisplay.Text = guiradtxtInterpretation.Text = GuiCommon.bizPwaobject.interpretation;
            
            // set display text for SP, DP & MP labels
            SetBloodPressureDisplayText();

            guiradlblSphygmocorReferenceAge.Text = String.Format("{0}{1}", oMsgMgr.GetMessage(CrxStructCommonResourceMsg.LblPwaSyphymocorRefAge), " > " + Math.Round(GuiCommon.bizPwaobject.ReferenceAge).ToString());

            // calculates height & weight
            int heightInInches;
            int heigthInFeet;

            guiradlblReportHeightDisplay.Text = string.Empty;
            guiradlblReportHeightInches.Text = string.Empty;

            switch (crxMgrObject.GeneralSettings.HeightandWeightUnit)
            {
                case (int)CrxGenPwvValue.CrxGenHeightWeightMetric:
                    guiradlblReportHeightDisplay.Text = GuiCommon.bizPwaobject.heightAndWeight.heightInCentimetres.Equals(GuiConstants.DefaultValue) ? string.Empty : GuiCommon.bizPwaobject.heightAndWeight.heightInCentimetres.ToString();

                    // guiradlblReportWeightUnits.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.Kg);
                    guiradlblReportHeightUnits.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.Cm);

                    // guiradlblReportWeightdisplay.Text = GuiCommon.bizPwaobject.heightAndWeight.weightInKilograms.Equals(GuiConstants.DefaultValue) ? string.Empty : GuiCommon.bizPwaobject.heightAndWeight.weightInKilograms.ToString();                                     
                    break;
                case (int)CrxGenPwvValue.CrxGenHeightWeightImperial:
                    if (GuiCommon.bizPwaobject.heightAndWeight.heightInInches != GuiConstants.DefaultValue)
                    {
                        // convert height in inches to feet & inches
                        heightInInches = int.Parse(GuiCommon.bizPwaobject.heightAndWeight.heightInInches.ToString()) % 12;
                        heigthInFeet = int.Parse(GuiCommon.bizPwaobject.heightAndWeight.heightInInches.ToString()) / 12;

                        guiradlblReportHeightDisplay.Text = heigthInFeet.ToString();
                        guiradlblReportHeightInches.Text = heightInInches.ToString();
                    }
                 
                    guiradlblReportHeightUnits.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.Feet);
                    break;
                default:
                    break;
            }

            // for binding statistics
            // BindPWVStatistics();
        }

        /**This method initializes Crx structure to update changes
    * */
        void InitializeCrxOnLoad(string pwaid)
        {
            try
            {
                PopulateBizFromCrx(pwaid);
            }
            catch (Exception ex)
            {
                GUIExceptionHandler.HandleException(ex, this);
            }
        }

        void SetBloodPressureDisplayText()
        { 
            guiradlblReportBloodPressure1.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.LblBrachialSpDpMp);
            guiradlblReportMP.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.LblReportPwaBrachialMp);
            guiradlblreportSPdisplay.Text = GuiCommon.bizPwaobject.Sp.Equals(GuiConstants.DefaultValue) ? string.Empty : Math.Round(GuiCommon.bizPwaobject.Sp).ToString();
            guiradlblreportDPdisplay.Text = GuiCommon.bizPwaobject.Dp.Equals(GuiConstants.DefaultValue) ? string.Empty : Math.Round(GuiCommon.bizPwaobject.Dp).ToString();
            guiradlblreportMPdisplay.Text = crxPwaData.C_Meanp.Equals(GuiConstants.DefaultValue) ? string.Empty : Math.Round(crxPwaData.C_Meanp).ToString();
            guiradlblCentralDp.Text = crxPwaData.C_Dp.Equals(GuiConstants.DefaultValue) ? string.Empty : Math.Round(crxPwaData.C_Dp).ToString();
            guiradlblCentralHr.Text = crxPwaData.HR.Equals(GuiConstants.DefaultValue) ? string.Empty : Math.Round(crxPwaData.HR).ToString();
            guiradlblCentralQualityControl.Text = crxPwaCuffData.P_QC_OTHER4.Equals(GuiConstants.DefaultValue) ? string.Empty : Math.Round(crxPwaCuffData.P_QC_OTHER4).ToString();           
        }

        /**This method initializes Crx structure to update changes
    * */
        void InitializeCrxFromSetupToReport(string studydatetime)
        {
            try
            {
                if (GuiCommon.SetupToReport)
                {
                    PopulateBizFromCrx(studydatetime);
                }
            }
            catch (Exception ex)
            {
                CrxLogger.Instance.Write(ex.StackTrace);
                GUIExceptionHandler.HandleException(ex, this);
            }
        }

        private void PrepareArrayObjectsForPwaMode(CrxStructPWAMeasurementData pwaData, CrxStructCuffPWAMeasurementData pwaCuffStruct)
        {
            // Initialising CrxStructPWAMeasurementData structure.
            pwaData.C_RAW_SIGNALS = new float[GuiCommon.bizPwaobject.GetRawSignalArraySize()];
            pwaData.C_AV_PULSE = new float[GuiCommon.bizPwaobject.GetPulseArraySize()];
            pwaData.C_TRIGS = new short[GuiCommon.bizPwaobject.GetTrigArraySize()];
            pwaData.C_ONSETS = new short[GuiCommon.bizPwaobject.GetTrigArraySize()];
            pwaData.C_Uncal_Av = new float[GuiCommon.bizPwaobject.GetPulseArraySize()];
            pwaData.C_ResemblePulse = new float[GuiCommon.bizPwaobject.GetResembleArraySize()];
            pwaData.C_Flow = new float[GuiCommon.bizPwaobject.GetPulseArraySize()];
            pwaData.C_Forward = new float[GuiCommon.bizPwaobject.GetPulseArraySize()];
            pwaData.C_Backward = new float[GuiCommon.bizPwaobject.GetPulseArraySize()];
          
            // Initialising CrxStructCuffPWAMeasurementData structure.
            pwaCuffStruct.P_RAW_SIGNALS = new float[GuiCommon.bizPwaobject.GetRawSignalArraySize()];
            pwaCuffStruct.P_AV_PULSE = new float[GuiCommon.bizPwaobject.GetPulseArraySize()];
            pwaCuffStruct.P_TRIGS = new short[GuiCommon.bizPwaobject.GetTrigArraySize()];
            pwaCuffStruct.P_ONSETS = new short[GuiCommon.bizPwaobject.GetTrigArraySize()];
            pwaCuffStruct.P_UNCAL_AV = new float[GuiCommon.bizPwaobject.GetPulseArraySize()];
            pwaCuffStruct.P_ResemblePulse = new float[GuiCommon.bizPwaobject.GetResembleArraySize()];
        }
      
        /** This method popluates bizsession object based on single record selected for assessment
         * It fetches value based on datetime of assessment
         * */
        private void PopulateBizFromCrx(string pwaid)
        {
            DataSet dsPWA;

            try
            {
                // check db connection
                if (dbMagr.CheckConnection(serverNameString, crxMgrObject.GeneralSettings.SourceData) == 0)
                {                   
                    if (string.IsNullOrEmpty(pwaid))
                    {
                        dsPWA = dbMagr.GetCuffPWAMeasurementDetails(int.Parse(patientObj.patientNumber.ToString()), int.Parse(patientObj.groupStudyId.ToString()), bobj);                        
                    }
                    else
                    {
                        // this will be called when other assessment is selected from assessment grid
                        GuiCommon.PwaCurrentId = pwaid;
                        CrxStructCuffPWAMeasurementData cdata = new CrxStructCuffPWAMeasurementData
                        {
                            PWA_Id = Convert.ToInt32(pwaid)
                        };
                        CrxStructPWAMeasurementData pdata = new CrxStructPWAMeasurementData
                        {
                            PWA_Id = Convert.ToInt32(pwaid)
                        };
                        PrepareArrayObjectsForPwaMode(pdata, cdata);
                        dsPWA = dbMagr.GetCuffPWAMeasurementDetails(pdata, cdata);                       
                        
                    }

                    if (dsPWA.Tables[0].Rows.Count > 0)
                    {
                        GuiCommon.PwaCurrentStudyDatetime = dsPWA.Tables[0].Rows[0][(int)CrxDBGetCuffPWAMeasurementDetails.StudyDateTime].ToString();
                        PrepareArrayObjectsForPwaMode(crxPwaData, crxPwaCuffData);
                        crxPwaData.AuditChange = DateTime.Parse(dsPWA.Tables[0].Rows[0][(int)CrxDBGetCuffPWAMeasurementDetails.AuditChange].ToString(), CrxCommon.gCI);
                        crxPwaData.Age = short.Parse(dsPWA.Tables[0].Rows[0][(int)CrxDBGetCuffPWAMeasurementDetails.Age].ToString());
                         crxPwaData.BloodPressureRange = dsPWA.Tables[0].Rows[0][(int)CrxDBGetCuffPWAMeasurementDetails.BloodPressureRange].ToString();
                        crxPwaData.BodyMassIndex = float.Parse(dsPWA.Tables[0].Rows[0][(int)CrxDBGetCuffPWAMeasurementDetails.BodyMassIndex].ToString());
                        crxPwaData.C_Agph = float.Parse(dsPWA.Tables[0].Rows[0][(int)CrxDBGetCuffPWAMeasurementDetails.C_Agph].ToString());
                        crxPwaData.C_Ai = float.Parse(dsPWA.Tables[0].Rows[0][(int)CrxDBGetCuffPWAMeasurementDetails.C_Ai].ToString());
                        crxPwaData.C_Al = float.Parse(dsPWA.Tables[0].Rows[0][(int)CrxDBGetCuffPWAMeasurementDetails.C_Al].ToString());
                        crxPwaData.C_Ap = float.Parse(dsPWA.Tables[0].Rows[0][(int)CrxDBGetCuffPWAMeasurementDetails.C_Ap].ToString());
                        crxPwaData.C_Area_Ratio = float.Parse(dsPWA.Tables[0].Rows[0][(int)CrxDBGetCuffPWAMeasurementDetails.C_Area_Ratio].ToString());
                        crxPwaData.C_Ati = float.Parse(dsPWA.Tables[0].Rows[0][(int)CrxDBGetCuffPWAMeasurementDetails.C_Ati].ToString());
                        byte[] buffer = (byte[])dsPWA.Tables[0].Rows[0][(int)CrxDBGetCuffPWAMeasurementDetails.C_AV_PULSE];
                        int len = buffer.Length / 4;
                        float[] tempFloat = dbMagr.CommonByteArrtoFloatArr(len, buffer);
                        for (int i = 0; i < tempFloat.Length; i++)
                        {
                            crxPwaData.C_AV_PULSE[i] = tempFloat[i];
                        }
                        
                        crxPwaData.C_Avd = float.Parse(dsPWA.Tables[0].Rows[0][(int)CrxDBGetCuffPWAMeasurementDetails.C_Avd].ToString());
                        crxPwaData.C_Avi = float.Parse(dsPWA.Tables[0].Rows[0][(int)CrxDBGetCuffPWAMeasurementDetails.C_Avi].ToString());

                        buffer = (byte[])dsPWA.Tables[0].Rows[0][(int)CrxDBGetCuffPWAMeasurementDetails.C_Backward];
                        len = buffer.Length / 4;
                        tempFloat = dbMagr.CommonByteArrtoFloatArr(len, buffer);
                        for (int i = 0; i < tempFloat.Length; i++)
                        {
                            crxPwaData.C_Backward[i] = tempFloat[i];
                        }

                        crxPwaData.C_Backward_Area = float.Parse(dsPWA.Tables[0].Rows[0][(int)CrxDBGetCuffPWAMeasurementDetails.C_Backward_Area].ToString());
                        crxPwaData.C_Dd = float.Parse(dsPWA.Tables[0].Rows[0][(int)CrxDBGetCuffPWAMeasurementDetails.C_Dd].ToString());
                        crxPwaData.C_DdPeriod = float.Parse(dsPWA.Tables[0].Rows[0][(int)CrxDBGetCuffPWAMeasurementDetails.C_DdPeriod].ToString());
                        crxPwaData.C_Dp = float.Parse(dsPWA.Tables[0].Rows[0][(int)CrxDBGetCuffPWAMeasurementDetails.C_Dp].ToString());
                        crxPwaData.C_Dti = float.Parse(dsPWA.Tables[0].Rows[0][(int)CrxDBGetCuffPWAMeasurementDetails.C_Dti].ToString());
                        crxPwaData.C_EdPeriod = float.Parse(dsPWA.Tables[0].Rows[0][(int)CrxDBGetCuffPWAMeasurementDetails.C_EdPeriod].ToString());
                        crxPwaData.C_Esp = float.Parse(dsPWA.Tables[0].Rows[0][(int)CrxDBGetCuffPWAMeasurementDetails.C_Esp].ToString());
                        crxPwaData.C_FloatSpare1 = float.Parse(dsPWA.Tables[0].Rows[0][(int)CrxDBGetCuffPWAMeasurementDetails.C_FloatSpare1].ToString());
                        crxPwaData.C_FloatSpare2 = float.Parse(dsPWA.Tables[0].Rows[0][(int)CrxDBGetCuffPWAMeasurementDetails.C_FloatSpare2].ToString());
                        buffer = (byte[])dsPWA.Tables[0].Rows[0][(int)CrxDBGetCuffPWAMeasurementDetails.C_Flow];
                        len = buffer.Length / 4;
                        tempFloat = dbMagr.CommonByteArrtoFloatArr(len, buffer);
                        for (int i = 0; i < tempFloat.Length; i++)
                        {
                            crxPwaData.C_Flow[i] = tempFloat[i];
                        }
                       
                        buffer = (byte[])dsPWA.Tables[0].Rows[0][(int)CrxDBGetCuffPWAMeasurementDetails.C_Forward];
                        len = buffer.Length / 4;
                        tempFloat = dbMagr.CommonByteArrtoFloatArr(len, buffer);
                        for (int i = 0; i < tempFloat.Length; i++)
                        {
                            crxPwaData.C_Forward[i] = tempFloat[i];
                        }
                        
                        crxPwaData.C_Forward_Area = float.Parse(dsPWA.Tables[0].Rows[0][(int)CrxDBGetCuffPWAMeasurementDetails.C_Forward_Area].ToString());
                        crxPwaData.C_IntSpare1 = int.Parse(dsPWA.Tables[0].Rows[0][(int)CrxDBGetCuffPWAMeasurementDetails.C_IntSpare1].ToString());
                        crxPwaData.C_IntSpare2 = int.Parse(dsPWA.Tables[0].Rows[0][(int)CrxDBGetCuffPWAMeasurementDetails.C_IntSpare2].ToString());
                        crxPwaData.C_Math_Params = int.Parse(dsPWA.Tables[0].Rows[0][(int)CrxDBGetCuffPWAMeasurementDetails.C_Math_Params].ToString());
                        crxPwaData.C_Meanp = float.Parse(dsPWA.Tables[0].Rows[0][(int)CrxDBGetCuffPWAMeasurementDetails.C_Meanp].ToString());
                        crxPwaData.C_MemSpare1 = float.Parse(dsPWA.Tables[0].Rows[0][(int)CrxDBGetCuffPWAMeasurementDetails.C_MemSpare1].ToString());
                        crxPwaData.C_MemSpare2 = float.Parse(dsPWA.Tables[0].Rows[0][(int)CrxDBGetCuffPWAMeasurementDetails.C_MemSpare2].ToString());
                        crxPwaData.C_Mpd = float.Parse(dsPWA.Tables[0].Rows[0][(int)CrxDBGetCuffPWAMeasurementDetails.C_Mpd].ToString());
                        crxPwaData.C_Mps = float.Parse(dsPWA.Tables[0].Rows[0][(int)CrxDBGetCuffPWAMeasurementDetails.C_Mps].ToString());
                        crxPwaData.C_Ole_Spare = dsPWA.Tables[0].Rows[0][(int)CrxDBGetCuffPWAMeasurementDetails.C_Ole_Spare].ToString();
                        
                        buffer = (byte[])dsPWA.Tables[0].Rows[0][(int)CrxDBGetCuffPWAMeasurementDetails.C_ONSETS];
                        len = buffer.Length / 4;
                        short[] temp = dbMagr.CommonByteArrtoShortArr(buffer, len);
                        for (int i = 0; i < temp.Length; i++)
                        {
                            crxPwaData.C_ONSETS[i] = temp[i];
                        }

                        for (int i = temp.Length; i < crxPwaData.C_ONSETS.Length; i++)
                        {
                            crxPwaData.C_ONSETS[i] = -1;
                        }

                        crxPwaData.C_P1 = float.Parse(dsPWA.Tables[0].Rows[0][(int)CrxDBGetCuffPWAMeasurementDetails.C_P1].ToString());
                        crxPwaData.C_P1_Height = float.Parse(dsPWA.Tables[0].Rows[0][(int)CrxDBGetCuffPWAMeasurementDetails.C_P1_Height].ToString());
                        crxPwaData.C_P2 = float.Parse(dsPWA.Tables[0].Rows[0][(int)CrxDBGetCuffPWAMeasurementDetails.C_P2].ToString());
                        crxPwaData.C_Period = float.Parse(dsPWA.Tables[0].Rows[0][(int)CrxDBGetCuffPWAMeasurementDetails.C_Period].ToString());
                        crxPwaData.C_Ph = float.Parse(dsPWA.Tables[0].Rows[0][(int)CrxDBGetCuffPWAMeasurementDetails.C_Ph].ToString());
                        crxPwaData.C_Pptt = float.Parse(dsPWA.Tables[0].Rows[0][(int)CrxDBGetCuffPWAMeasurementDetails.C_Pptt].ToString());
                        crxPwaData.C_Pulse_Ratio = float.Parse(dsPWA.Tables[0].Rows[0][(int)CrxDBGetCuffPWAMeasurementDetails.C_Pulse_Ratio].ToString());
                        crxPwaData.C_Pwv = float.Parse(dsPWA.Tables[0].Rows[0][(int)CrxDBGetCuffPWAMeasurementDetails.C_Pwv].ToString());
                        crxPwaData.C_Qc_Other1 = float.Parse(dsPWA.Tables[0].Rows[0][(int)CrxDBGetCuffPWAMeasurementDetails.C_Qc_Other1].ToString());
                        crxPwaData.C_Qc_Other2 = float.Parse(dsPWA.Tables[0].Rows[0][(int)CrxDBGetCuffPWAMeasurementDetails.C_Qc_Other2].ToString());
                        crxPwaData.C_Qc_Other3 = float.Parse(dsPWA.Tables[0].Rows[0][(int)CrxDBGetCuffPWAMeasurementDetails.C_Qc_Other3].ToString());
                        crxPwaData.C_Qc_Other4 = float.Parse(dsPWA.Tables[0].Rows[0][(int)CrxDBGetCuffPWAMeasurementDetails.C_Qc_Other4].ToString());
                        crxPwaData.C_Quality_T1 = int.Parse(dsPWA.Tables[0].Rows[0][(int)CrxDBGetCuffPWAMeasurementDetails.C_Quality_T1].ToString());
                        crxPwaData.C_Quality_T2 = int.Parse(dsPWA.Tables[0].Rows[0][(int)CrxDBGetCuffPWAMeasurementDetails.C_Quality_T2].ToString());

                        buffer = (byte[])dsPWA.Tables[0].Rows[0][(int)CrxDBGetCuffPWAMeasurementDetails.C_RAW_SIGNALS];
                        len = buffer.Length / 4;
                        tempFloat = dbMagr.CommonByteArrtoFloatArr(len, buffer);
                        for (int i = 0; i < tempFloat.Length; i++)
                        {
                            crxPwaData.C_RAW_SIGNALS[i] = tempFloat[i];
                        }

                        buffer = (byte[])dsPWA.Tables[0].Rows[0][(int)CrxDBGetCuffPWAMeasurementDetails.C_ResemblePulse];
                        len = buffer.Length / 4;
                        tempFloat = dbMagr.CommonByteArrtoFloatArr(len, buffer);
                        for (int i = 0; i < tempFloat.Length; i++)
                        {
                            crxPwaData.C_ResemblePulse[i] = tempFloat[i];
                        }

                        crxPwaData.C_Sp = float.Parse(dsPWA.Tables[0].Rows[0][(int)CrxDBGetCuffPWAMeasurementDetails.C_Sp].ToString());
                        crxPwaData.C_Svi = float.Parse(dsPWA.Tables[0].Rows[0][(int)CrxDBGetCuffPWAMeasurementDetails.C_Svi].ToString());
                        crxPwaData.C_T1 = float.Parse(dsPWA.Tables[0].Rows[0][(int)CrxDBGetCuffPWAMeasurementDetails.C_T1].ToString());
                        crxPwaData.C_T1ED = float.Parse(dsPWA.Tables[0].Rows[0][(int)CrxDBGetCuffPWAMeasurementDetails.C_T1ED].ToString());
                        crxPwaData.C_T1i = float.Parse(dsPWA.Tables[0].Rows[0][(int)CrxDBGetCuffPWAMeasurementDetails.C_T1i].ToString());
                        crxPwaData.C_T1m = float.Parse(dsPWA.Tables[0].Rows[0][(int)CrxDBGetCuffPWAMeasurementDetails.C_T1m].ToString());
                        crxPwaData.C_T1other = float.Parse(dsPWA.Tables[0].Rows[0][(int)CrxDBGetCuffPWAMeasurementDetails.C_T1other].ToString());
                        crxPwaData.C_T1r = float.Parse(dsPWA.Tables[0].Rows[0][(int)CrxDBGetCuffPWAMeasurementDetails.C_T1r].ToString());
                        crxPwaData.C_T2 = float.Parse(dsPWA.Tables[0].Rows[0][(int)CrxDBGetCuffPWAMeasurementDetails.C_T2].ToString());
                        crxPwaData.C_T2ED = float.Parse(dsPWA.Tables[0].Rows[0][(int)CrxDBGetCuffPWAMeasurementDetails.C_T2ED].ToString());
                        crxPwaData.C_T2i = float.Parse(dsPWA.Tables[0].Rows[0][(int)CrxDBGetCuffPWAMeasurementDetails.C_T2i].ToString());
                        crxPwaData.C_T2M = float.Parse(dsPWA.Tables[0].Rows[0][(int)CrxDBGetCuffPWAMeasurementDetails.C_T2M].ToString());
                        crxPwaData.C_T2Other = float.Parse(dsPWA.Tables[0].Rows[0][(int)CrxDBGetCuffPWAMeasurementDetails.C_T2Other].ToString());
                        crxPwaData.C_T2R = float.Parse(dsPWA.Tables[0].Rows[0][(int)CrxDBGetCuffPWAMeasurementDetails.C_T2R].ToString());

                        buffer = (byte[])dsPWA.Tables[0].Rows[0][(int)CrxDBGetCuffPWAMeasurementDetails.C_TRIGS];
                        len = buffer.Length / 4;

                       // crxPwaData.C_TRIGS = dbMagr.CommonByteArrtoShortArr(buffer,len);
                        short[] temp1 = dbMagr.CommonByteArrtoShortArr(buffer, len);
                        for (int i = 0; i < temp1.Length; i++)
                        {
                            crxPwaData.C_TRIGS[i] = temp1[i];
                        }

                        for (int i = temp1.Length; i < crxPwaData.C_TRIGS.Length; i++)
                        {
                            crxPwaData.C_TRIGS[i] = -1;
                        }

                        crxPwaData.C_Tti = float.Parse(dsPWA.Tables[0].Rows[0][(int)CrxDBGetCuffPWAMeasurementDetails.C_Tti].ToString());

                        buffer = (byte[])dsPWA.Tables[0].Rows[0][(int)CrxDBGetCuffPWAMeasurementDetails.C_Uncal_Av];
                        len = buffer.Length / 4;                       
                        tempFloat = dbMagr.CommonByteArrtoFloatArr(len, buffer);
                        for (int i = 0; i < tempFloat.Length; i++)
                        {
                            crxPwaData.C_Uncal_Av[i] = tempFloat[i];
                        }

                        crxPwaData.CalcED = float.Parse(dsPWA.Tables[0].Rows[0][(int)CrxDBGetCuffPWAMeasurementDetails.CalcED].ToString());
                        crxPwaData.CalDP = int.Parse(dsPWA.Tables[0].Rows[0][(int)CrxDBGetCuffPWAMeasurementDetails.CalDP].ToString());
                        crxPwaData.CalMP = int.Parse(dsPWA.Tables[0].Rows[0][(int)CrxDBGetCuffPWAMeasurementDetails.CalMP].ToString());
                        crxPwaData.CalSP = int.Parse(dsPWA.Tables[0].Rows[0][(int)CrxDBGetCuffPWAMeasurementDetails.CalSP].ToString());
                        crxPwaData.CaptureInput = short.Parse(dsPWA.Tables[0].Rows[0][(int)CrxDBGetCuffPWAMeasurementDetails.CaptureInput].ToString());
                        crxPwaData.CaptureTime = short.Parse(dsPWA.Tables[0].Rows[0][(int)CrxDBGetCuffPWAMeasurementDetails.CaptureTime].ToString());
                        crxPwaData.DataRev = int.Parse(dsPWA.Tables[0].Rows[0][(int)CrxDBGetCuffPWAMeasurementDetails.DataRev].ToString());
                        crxPwaData.DP = short.Parse(dsPWA.Tables[0].Rows[0][(int)CrxDBGetCuffPWAMeasurementDetails.DP].ToString());
                        crxPwaData.ED = float.Parse(dsPWA.Tables[0].Rows[0][(int)CrxDBGetCuffPWAMeasurementDetails.ED].ToString());
                        crxPwaData.EDMax = int.Parse(dsPWA.Tables[0].Rows[0][(int)CrxDBGetCuffPWAMeasurementDetails.EDMax].ToString());
                        crxPwaData.EDMin = int.Parse(dsPWA.Tables[0].Rows[0][(int)CrxDBGetCuffPWAMeasurementDetails.EDMin].ToString());
                        crxPwaData.EDOther = int.Parse(dsPWA.Tables[0].Rows[0][(int)CrxDBGetCuffPWAMeasurementDetails.EDOther].ToString());
                        crxPwaData.ExpPulseUpSampleRate = int.Parse(dsPWA.Tables[0].Rows[0][(int)CrxDBGetCuffPWAMeasurementDetails.ExpPulseUpSampleRate].ToString());
                        crxPwaData.FloatSpare1 = float.Parse(dsPWA.Tables[0].Rows[0][(int)CrxDBGetCuffPWAMeasurementDetails.FloatSpare1].ToString());
                        crxPwaData.Flow = int.Parse(dsPWA.Tables[0].Rows[0][(int)CrxDBGetCuffPWAMeasurementDetails.Flow].ToString());
                        crxPwaData.GroupIdentifier = int.Parse(dsPWA.Tables[0].Rows[0][(int)CrxDBGetCuffPWAMeasurementDetails.GroupIdentifier].ToString());
                        crxPwaData.HeightInCentimetres = short.Parse(dsPWA.Tables[0].Rows[0][(int)CrxDBGetCuffPWAMeasurementDetails.HeightInCentimetres].ToString());
                        crxPwaData.HeightInInches = short.Parse(dsPWA.Tables[0].Rows[0][(int)CrxDBGetCuffPWAMeasurementDetails.HeightInInches].ToString());
                        crxPwaData.HR = float.Parse(dsPWA.Tables[0].Rows[0][(int)CrxDBGetCuffPWAMeasurementDetails.HR].ToString());
                        crxPwaData.IntSpare2 = int.Parse(dsPWA.Tables[0].Rows[0][(int)CrxDBGetCuffPWAMeasurementDetails.IntSpare2].ToString());
                        crxPwaData.Medication = dsPWA.Tables[0].Rows[0][(int)CrxDBGetCuffPWAMeasurementDetails.Medication].ToString();
                        crxPwaData.MemSpare1 = dsPWA.Tables[0].Rows[0][(int)CrxDBGetCuffPWAMeasurementDetails.MemSpare1].ToString();
                        crxPwaData.MemSpare2 = dsPWA.Tables[0].Rows[0][(int)CrxDBGetCuffPWAMeasurementDetails.MemSpare2].ToString();
                        crxPwaData.Message = dsPWA.Tables[0].Rows[0][(int)CrxDBGetCuffPWAMeasurementDetails.Message].ToString();
                        crxPwaData.MP = short.Parse(dsPWA.Tables[0].Rows[0][(int)CrxDBGetCuffPWAMeasurementDetails.MP].ToString());
                        crxPwaData.Notes = dsPWA.Tables[0].Rows[0][(int)CrxDBGetCuffPWAMeasurementDetails.Notes].ToString();
                        crxPwaData.Operator = dsPWA.Tables[0].Rows[0][(int)CrxDBGetCuffPWAMeasurementDetails.Operator].ToString();
                        crxPwaData.PatientNumberInternal = int.Parse(dsPWA.Tables[0].Rows[0][(int)CrxDBGetCuffPWAMeasurementDetails.PatientNumberInternal].ToString());
                        crxPwaData.PWA_Id = short.Parse(dsPWA.Tables[0].Rows[0][(int)CrxDBGetCuffPWAMeasurementDetails.PWA_Id].ToString());
                        crxPwaData.QualityED = int.Parse(dsPWA.Tables[0].Rows[0][(int)CrxDBGetCuffPWAMeasurementDetails.QualityED].ToString());
                        crxPwaData.SampleRate = int.Parse(dsPWA.Tables[0].Rows[0][(int)CrxDBGetCuffPWAMeasurementDetails.SampleRate].ToString());
                        crxPwaData.SignalUpSampleRate = int.Parse(dsPWA.Tables[0].Rows[0][(int)CrxDBGetCuffPWAMeasurementDetails.SignalUpSampleRate].ToString());
                        crxPwaData.Simulation = bool.Parse(dsPWA.Tables[0].Rows[0][(int)CrxDBGetCuffPWAMeasurementDetails.Simulation].ToString());
                        crxPwaData.SP = short.Parse(dsPWA.Tables[0].Rows[0][(int)CrxDBGetCuffPWAMeasurementDetails.SP].ToString());
                        crxPwaData.StudyDateTime = DateTime.Parse(dsPWA.Tables[0].Rows[0][(int)CrxDBGetCuffPWAMeasurementDetails.StudyDateTime].ToString());
                        crxPwaData.SubType = dsPWA.Tables[0].Rows[0][(int)CrxDBGetCuffPWAMeasurementDetails.SubType].ToString();
                        crxPwaData.SystemIdentifier = int.Parse(dsPWA.Tables[0].Rows[0][(int)CrxDBGetCuffPWAMeasurementDetails.SystemIdentifier].ToString());
                        crxPwaData.Units = dsPWA.Tables[0].Rows[0][(int)CrxDBGetCuffPWAMeasurementDetails.Units].ToString();
                        crxPwaData.WeightInKilograms = short.Parse(dsPWA.Tables[0].Rows[0][(int)CrxDBGetCuffPWAMeasurementDetails.WeightInKilograms].ToString());
                        crxPwaData.WeightInPounds = short.Parse(dsPWA.Tables[0].Rows[0][(int)CrxDBGetCuffPWAMeasurementDetails.WeightInPounds].ToString());
                        buffer = (byte[])dsPWA.Tables[0].Rows[0][(int)CrxDBGetCuffPWAMeasurementDetails.P_AV_PULSE];
                        len = buffer.Length / 4;
                        tempFloat = dbMagr.CommonByteArrtoFloatArr(len, buffer);
                        for (int i = 0; i < tempFloat.Length; i++)
                        {
                            crxPwaCuffData.P_AV_PULSE[i] = tempFloat[i];
                        }

                        crxPwaCuffData.P_DP = float.Parse(dsPWA.Tables[0].Rows[0][(int)CrxDBGetCuffPWAMeasurementDetails.P_DP].ToString());
                        crxPwaCuffData.P_FLOATSPARE1 = float.Parse(dsPWA.Tables[0].Rows[0][(int)CrxDBGetCuffPWAMeasurementDetails.P_FLOATSPARE1].ToString());
                        crxPwaCuffData.P_FLOATSPARE2 = float.Parse(dsPWA.Tables[0].Rows[0][(int)CrxDBGetCuffPWAMeasurementDetails.P_FLOATSPARE2].ToString());
                        crxPwaCuffData.P_INTSPARE1 = int.Parse(dsPWA.Tables[0].Rows[0][(int)CrxDBGetCuffPWAMeasurementDetails.P_INTSPARE1].ToString());
                        crxPwaCuffData.P_INTSPARE2 = int.Parse(dsPWA.Tables[0].Rows[0][(int)CrxDBGetCuffPWAMeasurementDetails.P_INTSPARE2].ToString());
                        crxPwaCuffData.P_MATH_PARAMS = int.Parse(dsPWA.Tables[0].Rows[0][(int)CrxDBGetCuffPWAMeasurementDetails.P_MATH_PARAMS].ToString());
                        crxPwaCuffData.P_MAX_DPDT = float.Parse(dsPWA.Tables[0].Rows[0][(int)CrxDBGetCuffPWAMeasurementDetails.P_MAX_DPDT].ToString());
                        crxPwaCuffData.P_MEANP = float.Parse(dsPWA.Tables[0].Rows[0][(int)CrxDBGetCuffPWAMeasurementDetails.P_MEANP].ToString());
                        crxPwaCuffData.P_MEMSPARE1 = float.Parse(dsPWA.Tables[0].Rows[0][(int)CrxDBGetCuffPWAMeasurementDetails.P_MEMSPARE1].ToString());
                        crxPwaCuffData.P_MEMSPARE2 = float.Parse(dsPWA.Tables[0].Rows[0][(int)CrxDBGetCuffPWAMeasurementDetails.P_MEMSPARE2].ToString());
                        crxPwaCuffData.P_NOISE_FACTOR = int.Parse(dsPWA.Tables[0].Rows[0][(int)CrxDBGetCuffPWAMeasurementDetails.P_NOISE_FACTOR].ToString());
                        crxPwaCuffData.P_OLE_SPARE = dsPWA.Tables[0].Rows[0][(int)CrxDBGetCuffPWAMeasurementDetails.P_OLE_SPARE].ToString();
                        buffer = (byte[])dsPWA.Tables[0].Rows[0][(int)CrxDBGetCuffPWAMeasurementDetails.P_ONSETS];
                        len = buffer.Length / 4;
                        temp1 = dbMagr.CommonByteArrtoShortArr(buffer, len);
                        for (int i = 0; i < temp1.Length; i++)
                        {
                            crxPwaCuffData.P_ONSETS[i] = temp1[i];
                        }

                        crxPwaCuffData.P_QC_DV = float.Parse(dsPWA.Tables[0].Rows[0][(int)CrxDBGetCuffPWAMeasurementDetails.P_QC_DV].ToString());
                        crxPwaCuffData.P_QC_OTHER1 = float.Parse(dsPWA.Tables[0].Rows[0][(int)CrxDBGetCuffPWAMeasurementDetails.P_QC_OTHER1].ToString());
                        crxPwaCuffData.P_QC_OTHER2 = float.Parse(dsPWA.Tables[0].Rows[0][(int)CrxDBGetCuffPWAMeasurementDetails.P_QC_OTHER2].ToString());
                        crxPwaCuffData.P_QC_OTHER3 = float.Parse(dsPWA.Tables[0].Rows[0][(int)CrxDBGetCuffPWAMeasurementDetails.P_QC_OTHER3].ToString());
                        crxPwaCuffData.P_QC_OTHER4 = float.Parse(dsPWA.Tables[0].Rows[0][(int)CrxDBGetCuffPWAMeasurementDetails.P_QC_OTHER4].ToString());
                        crxPwaCuffData.P_QC_PH = float.Parse(dsPWA.Tables[0].Rows[0][(int)CrxDBGetCuffPWAMeasurementDetails.P_QC_PH].ToString());
                        crxPwaCuffData.P_QC_PHV = float.Parse(dsPWA.Tables[0].Rows[0][(int)CrxDBGetCuffPWAMeasurementDetails.P_QC_PHV].ToString());
                        crxPwaCuffData.P_QC_PLV = float.Parse(dsPWA.Tables[0].Rows[0][(int)CrxDBGetCuffPWAMeasurementDetails.P_QC_PLV].ToString());
                        buffer = (byte[])dsPWA.Tables[0].Rows[0][(int)CrxDBGetCuffPWAMeasurementDetails.P_RAW_SIGNALS];
                        len = buffer.Length / 4;
                        tempFloat = dbMagr.CommonByteArrtoFloatArr(len, buffer);
                        for (int i = 0; i < tempFloat.Length; i++)
                        {
                            crxPwaCuffData.P_RAW_SIGNALS[i] = tempFloat[i];
                        }
                      
                        buffer = (byte[])dsPWA.Tables[0].Rows[0][(int)CrxDBGetCuffPWAMeasurementDetails.P_ResemblePulse];
                        len = buffer.Length / 4;
                        tempFloat = dbMagr.CommonByteArrtoFloatArr(len, buffer);
                        for (int i = 0; i < tempFloat.Length; i++)
                        {
                            crxPwaCuffData.P_ResemblePulse[i] = tempFloat[i];
                        }

                        crxPwaCuffData.P_SP = float.Parse(dsPWA.Tables[0].Rows[0][(int)CrxDBGetCuffPWAMeasurementDetails.P_SP].ToString());
                        crxPwaCuffData.P_T1I = float.Parse(dsPWA.Tables[0].Rows[0][(int)CrxDBGetCuffPWAMeasurementDetails.P_T1I].ToString());
                        crxPwaCuffData.P_T1M = float.Parse(dsPWA.Tables[0].Rows[0][(int)CrxDBGetCuffPWAMeasurementDetails.P_T1M].ToString());
                        crxPwaCuffData.P_T1Other = float.Parse(dsPWA.Tables[0].Rows[0][(int)CrxDBGetCuffPWAMeasurementDetails.P_T1Other].ToString());
                        crxPwaCuffData.P_T1R = float.Parse(dsPWA.Tables[0].Rows[0][(int)CrxDBGetCuffPWAMeasurementDetails.P_T1R].ToString());
                        crxPwaCuffData.P_T2I = float.Parse(dsPWA.Tables[0].Rows[0][(int)CrxDBGetCuffPWAMeasurementDetails.P_T2I].ToString());
                        crxPwaCuffData.P_T2M = float.Parse(dsPWA.Tables[0].Rows[0][(int)CrxDBGetCuffPWAMeasurementDetails.P_T2M].ToString());
                        crxPwaCuffData.P_T2Other = float.Parse(dsPWA.Tables[0].Rows[0][(int)CrxDBGetCuffPWAMeasurementDetails.P_T2Other].ToString());
                        crxPwaCuffData.P_T2R = float.Parse(dsPWA.Tables[0].Rows[0][(int)CrxDBGetCuffPWAMeasurementDetails.P_T2R].ToString());
                        buffer = (byte[])dsPWA.Tables[0].Rows[0][(int)CrxDBGetCuffPWAMeasurementDetails.P_TRIGS];
                        len = buffer.Length / 4;
                        temp1 = dbMagr.CommonByteArrtoShortArr(buffer, len);
                        for (int i = 0; i < temp1.Length; i++)
                        {
                            crxPwaCuffData.P_TRIGS[i] = temp1[i];
                        }

                        buffer = (byte[])dsPWA.Tables[0].Rows[0][(int)CrxDBGetCuffPWAMeasurementDetails.P_UNCAL_AV];
                        len = buffer.Length / 4;                      
                        tempFloat = dbMagr.CommonByteArrtoFloatArr(len, buffer);
                        for (int i = 0; i < tempFloat.Length; i++)
                        {
                            crxPwaCuffData.P_UNCAL_AV[i] = tempFloat[i];
                        }

                        CrxPwaCaptureInput pwaCaptureInput = new CrxPwaCaptureInput();
                        bool value = GuiCommon.bizPwaobject.GetCurrentCaptureInput(ref pwaCaptureInput);

                        if (!Convert.ToInt32(pwaCaptureInput).Equals(crxPwaData.CaptureInput))
                        {
                            GuiCommon.bizPwaobject.Initialise(crxPwaData.CaptureInput.Equals(Convert.ToInt32(CrxPwaCaptureInput.Tonometer)) ? CrxPwaCaptureInput.Tonometer : CrxPwaCaptureInput.Cuff);
                        }  

                        GuiCommon.bizPwaobject.Populate(crxPwaData, crxPwaCuffData);
                        GuiCommon.bizPwaobject.Validate();
                        GuiCommon.crxPwaData = crxPwaData;
                        GuiCommon.crxPwaCuffData = crxPwaCuffData;
                    }                   
                }
                else
                {
                    DialogResult result = RadMessageBox.Show(this, GuiCommon.ConnectionErrorString(), oMsgMgr.GetMessage(CrxStructCommonResourceMsg.SystemError), MessageBoxButtons.RetryCancel, RadMessageIcon.Error);
                    if (result == DialogResult.Retry)
                    {
                        PopulateBizFromCrx(pwaid);
                    }
                }
            }
            catch (Exception ex)
            {
                CrxLogger.Instance.Write(ex.StackTrace);
                GUIExceptionHandler.HandleException(ex, this);
            }
        }        

        /** This method binds demographic details of patient on report screen
      */
        private void FillDemographicDetailsReport()
        {
            try
            {
                // clear patient fields before populating them.             
                guiradlblReportPatientName.Text = string.Empty;
                guilblReportPatientIdValue.Text = string.Empty;
                guilblReportDobValue.Text = string.Empty;
                guilblReportAgeValue.Text = string.Empty;
                guilblReportGenderValue.Text = string.Empty;
                guiradlblReportPatientName.Text = string.IsNullOrEmpty(patientObj.firstName) ? patientObj.lastName : patientObj.firstName + "  " + patientObj.lastName;
                guilblReportPatientIdValue.Text = patientObj.patientId;
                guilblReportDobValue.Text = patientObj.dateOfBirth.ToShortDateString();
                guilblReportAgeValue.Text = GuiCommon.bizPwaobject.patientAge.ToString();
                guilblReportGenderValue.Text = patientObj.gender;
                ReportPWADisplayMode(true);
            }
            catch (Exception ex)
            {
                GUIExceptionHandler.HandleException(ex, this);
            }
        }

        /** This method is used to initialise the assessment grid view.
        */
        private void InitializeReportAssessmentList()
        {
            try
            {
                guiradgridReportAssessment.Columns.Clear();
                guiradgridReportAssessment.TableElement.BeginUpdate();

                // object initialiser property, assigned checkbox column type to name
                GridViewCheckBoxColumn checkBoxColumn = new GridViewCheckBoxColumn { Name = "CheckBox" };

                guiradgridReportAssessment.Columns.Add(checkBoxColumn);
                guiradgridReportAssessment.Columns[0].IsVisible = true;
                guiradgridReportAssessment.Columns[0].Width = 22;
                guiradgridReportAssessment.Columns[0].ReadOnly = false;
                guiradgridReportAssessment.Columns[0].IsVisible = false;

                guiradgridReportAssessment.Columns.Add(oMsgMgr.GetMessage(CrxStructCommonResourceMsg.ReportAssesmentsFormat), oMsgMgr.GetMessage(CrxStructCommonResourceMsg.GuiDisplayStudyDateTime), oMsgMgr.GetMessage(CrxStructCommonResourceMsg.ReportAssesmentsFormat));
                guiradgridReportAssessment.Columns[1].Width = 275;
                guiradgridReportAssessment.Columns[1].IsVisible = true;
                guiradgridReportAssessment.Columns[1].ReadOnly = true;

                guiradgridReportAssessment.Columns.Add("PWA_Id", "PWA_Id", "PWA_Id");
                guiradgridReportAssessment.Columns[2].Width = 50;
                guiradgridReportAssessment.Columns[2].IsVisible = false;
                guiradgridReportAssessment.Columns[2].ReadOnly = true;    

                guiradgridReportAssessment.Columns[2].SortOrder = RadSortOrder.Ascending;
                guiradgridReportAssessment.GridElement.AlternatingRowColor = Color.LightGray;
                guiradgridReportAssessment.Columns[1].FormatString = "{0:g}";                     
          
                guiradgridReportAssessment.TableElement.EndUpdate();
                guiradgridReportAssessment.AutoGenerateColumns = false;          
            }
            catch (Exception ex)
            {
                GUIExceptionHandler.HandleException(ex, this);
            }
        }

        /** This method set default options for buttons on report screen & calculates patients age
        * */
        private void SetDefaultValuesOnLoad()
        {
            // make only edit button visible
            guiradbtnreportcancel.Visible = false;
            guiradbtnreportedit.Visible = true;
            guiradbtnreportsave.Visible = false;
            objDefaultWindow.radtabReport.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.TabReport);

            if (crxMgrObject.GeneralSettings.StartupScreen != oMsgMgr.GetMessage(CrxStructCommonResourceMsg.QuickStart))
            {
                GuiCommon.bizPwaobject.CalculateAge();
            }
            
            objDefaultWindow.radlblMessage.Text = string.Empty;
        }

        private void guiradbtnreportedit_Click_1(object sender, EventArgs e)
        {
            // edit mode            
            // Show edit mode in the status bar.
            // objDefaultWindow.radlblMessage.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.EditMode);
            ReportPWADisplayMode(false);

            // set height details
            guiradtxtReportHeight.Text = guiradlblReportHeightDisplay.Text;
            guiradtxtReportHeightInches.Text = guiradlblReportHeightInches.Text;
          
            // guiradtxtReportOperator.Text = guiradlblReportOperatordisplay.Text;
                guiradtxtMedicationNotesValue.Text = guiradlblReportNotesDisplay.Text;
          
            // in edit mode disable repeat & capture buttons
            guiradbtnRepeat.Enabled = false;
            objDefaultWindow.radtabCapture.Enabled = false;

            GuiCommon.IsFormChanged = false;
        }

        /** This method displays PWA measurement section in display & edit mode
        */
        private void ReportPWADisplayMode(bool value)
        {
            if (value)
            {
                guiradbtnreportcancel.Visible = false;
                guiradbtnreportedit.Visible = true;
                guiradbtnreportedit.Focus();
                guiradbtnreportsave.Visible = false;
                guiradbtnDelete.Enabled = true;

                // guiradbtnPrint.Enabled = true;
                // guiradchkAssesments.Enabled = guiradgridReportAssessment.Rows.Count > 1 ? true : false;
                guiradgridReportAssessment.Enabled = true;

                guiradtxtReportBloodPressure1.Visible = false;
                guiradtxtReportBloodPressure2.Visible = false;
                guiradtxtReportBloodPressure3.Visible = false;
                guiradtxtReportOperator.Visible = false;
                guiradtxtCentralDpValue.Visible = false;
                guiradtxtCentralHrValue.Visible = false;
                guiradtxtMedicationNotesValue.Visible = false;
                guiradtxtInterpretation.Visible = false;
                guiradtxtCentralQualityControlValue.Visible = false;
                //guiradtxtInterpretation.Text = string.Empty;
                guiradtxtReportHeight.Visible = false;

                guiradtxtReportOperator.Visible = false;

                // Commenting the below code as group name is not included in Clinical mode.
                guiradlblreportSPdisplay.BringToFront();
                guiradlblreportDPdisplay.BringToFront();
                guiradlblreportMPdisplay.BringToFront();

                // guiradlblReportOperatordisplay.BringToFront();
                guiradlblReportHeightDisplay.BringToFront();
                guiradlblInterpretationDisplay.BringToFront();
                guiradlblCentralDp.BringToFront();
                guiradlblCentralHr.BringToFront();
                guiradlblCentralQualityControl.BringToFront();

                // guiradlblReportNotesDisplay.BringToFront();
                guiradlblCentralDp.Visible = true;
                guiradlblCentralHr.Visible = true;
                guiradlblCentralQualityControl.Visible = true;

                // guiradlblReportNotesDisplay.Visible = true;
                guiradlblInterpretationDisplay.Visible = true;
              
                switch (crxMgrObject.GeneralSettings.HeightandWeightUnit)
                {
                    case (int)CrxGenPwvValue.CrxGenHeightWeightMetric: // metric
                        guiradtxtReportHeightInches.Visible = false;
                        guiradlblheightinchec.Visible = false;
                        guiradlblReportHeightInches.Visible = false;
                        break;

                    case (int)CrxGenPwvValue.CrxGenHeightWeightImperial: // Imperial
                        guiradtxtReportHeightInches.Visible = false;
                        guiradtxtReportHeightInches.SendToBack();
                        guiradlblheightinchec.Visible = true;
                        guiradlblReportHeightInches.Visible = true;
                        guiradlblReportHeightInches.BringToFront();
                        break;
                    default:
                        break;
                }
            }
            else
            {
                guiradbtnreportcancel.Visible = true;
                guiradbtnreportedit.Visible = false;
                guiradbtnreportsave.Visible = true;

                guiradbtnDelete.Enabled = false;
                guiradbtnPrint.Enabled = false;
                guiradbtnRepeat.Enabled = false;
                guiradgridReportAssessment.Enabled = false;

                // edit PWA details (show text boxes)               
                guiradtxtReportHeight.Visible = true;
                guiradtxtInterpretation.Visible = true;

                // guiradtxtReportBloodPressure1.Focus();
                guiradlblreportSPdisplay.SendToBack();
                guiradlblreportDPdisplay.SendToBack();
                guiradlblreportMPdisplay.SendToBack();

                // guiradlblReportOperatordisplay.SendToBack();
                guiradlblReportHeightDisplay.SendToBack();
                guiradlblCentralDp.SendToBack();
                guiradlblCentralHr.SendToBack();
                guiradlblCentralQualityControl.SendToBack();
                guiradlblInterpretationDisplay.SendToBack();
                guiradlblCentralDp.Visible = true;
                guiradlblCentralHr.Visible = true;
                guiradlblCentralQualityControl.Visible = true;

                // guiradlblReportNotesDisplay.Visible = true;
                guiradlblInterpretationDisplay.Visible = true;             
                guiradtxtReportBloodPressure1.BringToFront();           
                guiradtxtReportHeight.BringToFront();

                switch (crxMgrObject.GeneralSettings.HeightandWeightUnit)
                {
                    case (int)CrxGenPwvValue.CrxGenHeightWeightMetric:
                        guiradtxtReportHeightInches.Visible = false;
                        guiradlblheightinchec.Visible = false;
                        guiradlblReportHeightInches.Visible = false;
                        break;

                    case (int)CrxGenPwvValue.CrxGenHeightWeightImperial:
                        guiradtxtReportHeightInches.Visible = true;
                        guiradlblheightinchec.Visible = true;
                        guiradlblReportHeightInches.Visible = false;
                        guiradtxtReportHeightInches.BringToFront();
                        guiradlblReportHeightInches.SendToBack();
                        break;
                    default:
                        break;
                }
            }
        }

        private void guiradbtnreportcancel_Click(object sender, EventArgs e)
        {
            // call method to bring report screen to display mode
            SetPWADsiplayMode();
            CheckForSimualtionMode();
        }

        /** This method brings report screen left side measurement details section in display mode
        * It hides cancel & save button & unhides edit button
        * */
        private void SetPWADsiplayMode()
        {
            GuiCommon.IsFormChanged = false;
            objDefaultWindow.radlblMessage.Text = string.Empty;

            // cancels editing PWA details
            ReportPWADisplayMode(true);

            guiradbtnreportcancel.Visible = false;
            guiradbtnreportedit.Visible = true;
            guiradbtnreportsave.Visible = false;
            guiradbtnPrint.Enabled = true;
            guiradbtnreportedit.Focus();
            guiradtxtInterpretation.Text = GuiCommon.bizPwaobject.interpretation;
            CheckLastAssessmentSelected(pwaIdToCompare);
        }

        /** This method checks whether last assessment is selected, if selected repeat & capture tabs are enabled & vice versa
        * */
        private void CheckLastAssessmentSelected(string pwaId)
        {
            // check if there are any assessments in the grid, if no then disable the Repeat button and the Capture tab.
            // if there are records in the grid then go with the normal flow.        
            bool setValue;
            if (GuiCommon.TabFocused == objDefaultWindow.guiradgrpbxPwvDistanceMethod)
            {
                setValue = !GuiCommon.IsWaitIntervalImposed;
            }
            else
            {               
                lastAssessmentPwaId = string.IsNullOrEmpty(lastAssessmentPwaId) ? string.Empty : lastAssessmentPwaId;
                pwaId = string.IsNullOrEmpty(pwaId) ? string.Empty : pwaId;
                setValue = lastAssessmentPwaId.Equals(pwaId) && guiradbtnreportedit.Visible && objDefaultWindow.radtabReport.Text != oMsgMgr.GetMessage(CrxStructCommonResourceMsg.TabAnalysis) && guiradgridReportAssessment.Rows.Count > 0;
            }

            // objDefaultWindow.radtabCapture.Enabled = setValue;
            guiradbtnRepeat.Enabled = setValue;
        }    
 
        private void guiradgridReportAssessment_ContextMenuOpening(object sender, ContextMenuOpeningEventArgs e)
        {
            e.Cancel = true;
        }

        private void guiradgridReportAssessment_RowFormatting(object sender, RowFormattingEventArgs e)
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
                    // change the color to gray if the row is not selected. 
                    if (!row.IsSelected)
                    {
                        row.DrawFill = true;
                        row.GradientStyle = GradientStyles.Solid;
                        row.BackColor = Color.LightGray;
                    }
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

        private void guiradgridReportAssessment_SelectionChanged(object sender, EventArgs e)
        {
            try
            {
                // DisplaySelectedRecords(guiradgridReportAssessment.CurrentCell.RowIndex, false);
                DisplaySelectedRecords(-1, false);
            }
            catch (Exception ex)
            {
                GUIExceptionHandler.HandleException(ex, this);
            }
        }

        /** this method checks for mutliple assessments selected and accordingly displays analysis screen
         * */
        private void DisplaySelectedRecords(int rowIndex, bool isChecked)
        {
            // oneRecordSelect = true;
            int recordSelected = 0;
            pwaIdWithComma = string.Empty;
            objDefaultWindow.radlblMessage.Text = string.Empty;

            // below line of code will keep focus on current record selection in assessment grid
            IGridViewEventListener navigatorListener = guiradgridReportAssessment.GridNavigator as IGridViewEventListener;
            guiradgridReportAssessment.MasterTemplate.SynchronizationService.RemoveListener(navigatorListener);

            // this call begins the update of gridview selection using shift key
            guiradgridReportAssessment.MasterTemplate.BeginUpdate();

            foreach (GridViewRowInfo row in guiradgridReportAssessment.Rows)
            {
                if (row.IsSelected)
                {
                    recordSelected++;
                    pwaIdWithComma += row.Cells[2].Value.ToString() + oMsgMgr.GetMessage(CrxStructCommonResourceMsg.GuiDisplayComma);
                }
            }

            GuiConstants.PwaIdWithComma = pwaIdWithComma;
            numeberOfRecordsSelected = recordsToDelete = recordSelected;
            CheckForSimualtionMode();

            // below line of code will keep focus on current record selection in assessment grid
            guiradgridReportAssessment.MasterTemplate.EndUpdate(new DataViewChangedEventArgs(ViewChangedAction.DataChanged));
            guiradgridReportAssessment.MasterTemplate.SynchronizationService.AddListener(navigatorListener);

            // guiradchkAssesments.Enabled = guiradgridReportAssessment.Rows.Count == 1 ? false : true;

            // display analysis / report screen based on records selected
            DisplayReportOnSelection(recordSelected, pwaIdWithComma);
        }

        /** This method binds data to report screen as per the selected assesment
        * */
        private void DisplayReportForSelectedAssesment(string pwaid)
        {
            // if (!GuiCommon.SetupToReport)
            {
                InitializeCrxOnLoad(pwaid);
                FillPWAMeasurementDetailsReport();
                PlotAvgAorticPulseChart();
                ShowAixTracker(26, -8, crxPwaData.C_Agph, -2, 20);
                ShowSpTracker(130, 90, crxPwaData.C_Sp, 96, 120);
                float centralPp;
                centralPp = crxPwaData.C_Sp - crxPwaData.C_Dp;
                ShowPpTracker(25, 0, centralPp, 5, 20);
                ShowApTracker(12, -6, crxPwaData.C_Ap, -3, 9);               
            }
        }

        private void DisplayReportOnSelection(int recordSelected, string pwaid)
        {           
            dateToCompare = string.Empty;
            pwaIdToCompare = string.Empty;

            // check assessment checkbox if all assessments are selected in grid
            if (recordSelected == guiradgridReportAssessment.Rows.Count)
            {
                guiradbtnDelete.Enabled = true;

                if (recordSelected == 1)
                {
                    // dateToCompare = datetime.Replace(oMsgMgr.GetMessage(CrxStructCommonResourceMsg.GuiDisplayComma), string.Empty);
                    pwaIdToCompare = pwaid.Replace(oMsgMgr.GetMessage(CrxStructCommonResourceMsg.GuiDisplayComma), string.Empty);
                }

                guipnlPWAReportAnalysis.Visible = true;
                guipnlPWAReport.Visible = false;

                PlotAnalysisTrendCharts();
                objDefaultWindow.radtabReport.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.TabAnalysis);
            }
            else if (recordSelected == 1)
            {
                EnableDisableReportPrintButton(true);

                // if only 1 record is selected in assessment grid bind the measurement details 
                // pertaining to that patient                
                guipnlPWAReportAnalysis.Visible = false;
                guipnlPWAReport.Visible = true;
 
                guipnlPWAReportAnalysis.SendToBack();
                guipnlPWAReport.BringToFront();

                guiradbtnDelete.Enabled = true;
                 
                objDefaultWindow.radtabReport.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.TabReport);

               // dateToCompare = datetime.Replace(oMsgMgr.GetMessage(CrxStructCommonResourceMsg.GuiDisplayComma), string.Empty);
                pwaIdToCompare = pwaid.Replace(oMsgMgr.GetMessage(CrxStructCommonResourceMsg.GuiDisplayComma), string.Empty);
                guiradbtnreportedit.Enabled = true;

                CheckLastAssessmentSelected(pwaIdToCompare);

                // when record selected is only one display record as per assessment selected
                DisplayReportForSelectedAssesment(pwaIdToCompare);
            }
            else if (recordSelected > 1)
            {
                // DisplayAnalysisScreen();
                guipnlPWAReportAnalysis.Visible = true;
                guipnlPWAReport.Visible = false;

                // EnableDisableReportPrintButton(false);

                //// display analysis screen
                // guiradbtnreportedit.Enabled = false;
                // guiradpnlAnalysis.Visible = true;
                // guiradbtnRepeat.Enabled = false;
                // guiradbtnDelete.Enabled = true;
                // objDefaultWindow.radtabCapture.Enabled = false;
                // ReportPWADisplayMode(true);
                 PlotAnalysisTrendCharts();
                objDefaultWindow.radtabReport.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.TabAnalysis);
            }
            else if (recordSelected == 0)
            {
                EnableDisableReportPrintButton(true);

                // disable delete & edit button when no record is selected
                guiradbtnDelete.Enabled = false;
                guiradbtnreportedit.Enabled = false;

                 CheckLastAssessmentSelected(string.Empty);
            }
            else
            {
                EnableDisableReportPrintButton(true);

                // for any other condition besides above, show report screen & enable capture & repeat buttons
                guiradbtnreportedit.Enabled = false;
                guipnlPWAReportAnalysis.Visible = false;

                // if (!GuiCommon.IsWaitIntervalImposed)
                // {
                    guiradbtnRepeat.Enabled = true;

                // objDefaultWindow.radtabCapture.Enabled = true;
                // }
                objDefaultWindow.radtabReport.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.TabReport);
            }
        }

        /** This method shows analysis trend graph
                 * */
        private void PlotAnalysisTrendCharts()
        {
            try
            {
                guiradbtnreportedit.Enabled = false;

                // check for connection
                if (dbMagr.CheckConnection(serverNameString, crxMgrObject.GeneralSettings.SourceData) == 0)
                {
                    CrxStructPWATrendData trendData = new CrxStructPWATrendData();

                    // fetch records for selected assessments
                    // dbMagr.GetPWVTrendData(GuiCommon.PatientInternalNumber, GuiCommon.GroupId, GuiCommon.SystemIdentifier, dateSelected + oMsgMgr.GetMessage(CrxStructCommonResourceMsg.GuiDisplayComma), trendData);
                    dbMagr.GetPWATrendData(pwaIdWithComma, trendData);

                    // if (!string.IsNullOrEmpty(trendData.ApValidArrStr) && !string.IsNullOrEmpty(trendData.PulseWaveVelocityArrStr))
                    if (!string.IsNullOrEmpty(trendData.ApValidArrStr) && !string.IsNullOrEmpty(trendData.HrValidArrStr) && !string.IsNullOrEmpty(trendData.SpValidArrStr) && !string.IsNullOrEmpty(trendData.DpValidArrStr) && !string.IsNullOrEmpty(trendData.MpValidArrStr))
                    {
                        PlotApTrendData(trendData);
                        PlotHrTrendData(trendData);
                        PlotSpTrendData(trendData);
                        PlotDpMpTrendData(trendData);
                        PlotPpTrendData(trendData);
                    }
                }
                else
                {
                    DialogResult result = RadMessageBox.Show(this, GuiCommon.ConnectionErrorString(), oMsgMgr.GetMessage(CrxStructCommonResourceMsg.SystemError), MessageBoxButtons.RetryCancel, RadMessageIcon.Error);
                    if (result == DialogResult.Retry)
                    {
                        PlotAnalysisTrendCharts();
                    }
                }
            }
            catch (Exception ex)
            {
                GUIExceptionHandler.HandleException(ex, this);
            }
        }

        /**This method is used to display Report print button/Analysis print button depending upon the number of
         * assessments selected.         
         */
        private void EnableDisableReportPrintButton(bool value)
        {
            // if value is true,then show Report Print button.
            // To See patient report, disable and send back the analysis print button and
            // at the same time enable and bring in front the Report print button.
            if (value)
            {
                guiradbtnPrint.BringToFront();
                guiradbtnPrint.Enabled = true;

                guiradbtnAnalysisPrint.SendToBack();
                guiradbtnAnalysisPrint.Enabled = false;
            }          
            else
            {  
                // if value is false then show Analysis Print button.
                // To see patient analysis report,disable and send back the report print button and
                // at the same time enable and bring in front the Analysis print button.
                guiradbtnPrint.SendToBack();
                guiradbtnPrint.Enabled = false;

                guiradbtnAnalysisPrint.BringToFront();
                guiradbtnAnalysisPrint.Enabled = true;
            }
        }

        private void guiradAnalysisChartDPMP_DoubleClick(object sender, EventArgs e)
        {           
            RenderEnlargedChart(guiradAnalysisChartDPMP);

            guilblLargeDPLegend.Visible = true;
            guilblLargeMPLegend.Visible = true;

            guiradAnalysisChartSP.Update();
            guiradAnalysisChartPP.Update();
            guiradAnalysisChartHR.Update();
            guiradAnalysisChartAix75.Update();
            guiradAnalysisChartAP.Update();
        }

        private void guiradAnalysisChartHR_DoubleClick(object sender, EventArgs e)
        {           
            RenderEnlargedChart(guiradAnalysisChartHR);

            guiradAnalysisChartSP.Update();
            guiradAnalysisChartPP.Update();
            guiradAnalysisChartDPMP.Update();
            guiradAnalysisChartAix75.Update();
            guiradAnalysisChartAP.Update();
        }

        private void guiradAnalysisChartSP_DoubleClick(object sender, EventArgs e)
        {           
            RenderEnlargedChart(guiradAnalysisChartSP);

            guiradAnalysisChartHR.Update();
            guiradAnalysisChartPP.Update();
            guiradAnalysisChartDPMP.Update();
            guiradAnalysisChartAix75.Update();
            guiradAnalysisChartAP.Update();
        }

        private void guiradAnalysisChartSphygmocorRefAge_DoubleClick(object sender, EventArgs e)
        {           
            RenderEnlargedChart(guiradAnalysisChartAix75);

            guiradAnalysisChartHR.Update();
            guiradAnalysisChartAP.Update();
            guiradAnalysisChartPP.Update();
            guiradAnalysisChartDPMP.Update();
            guiradAnalysisChartSP.Update();
        }

        private void guiradAnalysisChartAP_DoubleClick(object sender, EventArgs e)
        {            
            RenderEnlargedChart(guiradAnalysisChartAP);
            
            guiradAnalysisChartHR.Update();
            guiradAnalysisChartPP.Update();
            guiradAnalysisChartDPMP.Update();
            guiradAnalysisChartAix75.Update();
            guiradAnalysisChartSP.Update();
        }

        private void guiradAnalysisChartPP_DoubleClick(object sender, EventArgs e)
        {            
            RenderEnlargedChart(guiradAnalysisChartPP);
            guiradAnalysisChartHR.Update();
            guiradAnalysisChartAP.Update();
            guiradAnalysisChartDPMP.Update();
            guiradAnalysisChartAix75.Update();
            guiradAnalysisChartSP.Update();
        }

        private void RenderEnlargedChart(Chart smallChart)
        {
            guiradAnalysisChartPP.BorderlineColor = Color.White;
            guiradAnalysisChartPP.BorderlineDashStyle = ChartDashStyle.Solid;
            guiradAnalysisChartPP.BorderlineWidth = 1;
            guiradAnalysisChartPP.BorderSkin.SkinStyle = BorderSkinStyle.None;
            guiradAnalysisChartPP.BorderSkin.BackColor = Color.Gray;
            guiradAnalysisChartPP.BorderSkin.BackGradientStyle = GradientStyle.None;
            guiradAnalysisChartPP.BorderSkin.BackHatchStyle = ChartHatchStyle.None;
            guiradAnalysisChartPP.BorderSkin.BorderColor = Color.Black;
            guiradAnalysisChartPP.BorderSkin.BorderDashStyle = ChartDashStyle.NotSet;
            guiradAnalysisChartPP.BorderSkin.BorderWidth = 1;
            guiradAnalysisChartPP.BorderSkin.PageColor = Color.White;
            guiradAnalysisChartPP.BringToFront();

            guiradAnalysisChartAP.BorderlineColor = Color.White;
            guiradAnalysisChartAP.BorderlineDashStyle = ChartDashStyle.Solid;
            guiradAnalysisChartAP.BorderlineWidth = 1;
            guiradAnalysisChartAP.BorderSkin.SkinStyle = BorderSkinStyle.None;
            guiradAnalysisChartAP.BorderSkin.BackColor = Color.Gray;
            guiradAnalysisChartAP.BorderSkin.BackGradientStyle = GradientStyle.None;
            guiradAnalysisChartAP.BorderSkin.BackHatchStyle = ChartHatchStyle.None;
            guiradAnalysisChartAP.BorderSkin.BorderColor = Color.Black;
            guiradAnalysisChartAP.BorderSkin.BorderDashStyle = ChartDashStyle.NotSet;
            guiradAnalysisChartAP.BorderSkin.BorderWidth = 1;
            guiradAnalysisChartAP.BorderSkin.PageColor = Color.White;
            guiradAnalysisChartAP.BringToFront();

            guiradAnalysisChartHR.BorderlineColor = Color.White;
            guiradAnalysisChartHR.BorderlineDashStyle = ChartDashStyle.Solid;
            guiradAnalysisChartHR.BorderlineWidth = 1;
            guiradAnalysisChartHR.BorderSkin.SkinStyle = BorderSkinStyle.None;
            guiradAnalysisChartHR.BorderSkin.BackColor = Color.Gray;
            guiradAnalysisChartHR.BorderSkin.BackGradientStyle = GradientStyle.None;
            guiradAnalysisChartHR.BorderSkin.BackHatchStyle = ChartHatchStyle.None;
            guiradAnalysisChartHR.BorderSkin.BorderColor = Color.Black;
            guiradAnalysisChartHR.BorderSkin.BorderDashStyle = ChartDashStyle.NotSet;
            guiradAnalysisChartHR.BorderSkin.BorderWidth = 1;
            guiradAnalysisChartHR.BorderSkin.PageColor = Color.White;
            guiradAnalysisChartHR.BringToFront();

            guiradAnalysisChartDPMP.BorderlineColor = Color.White;
            guiradAnalysisChartDPMP.BorderlineDashStyle = ChartDashStyle.Solid;
            guiradAnalysisChartDPMP.BorderlineWidth = 1;
            guiradAnalysisChartDPMP.BorderSkin.SkinStyle = BorderSkinStyle.None;
            guiradAnalysisChartDPMP.BorderSkin.BackColor = Color.Gray;
            guiradAnalysisChartDPMP.BorderSkin.BackGradientStyle = GradientStyle.None;
            guiradAnalysisChartDPMP.BorderSkin.BackHatchStyle = ChartHatchStyle.None;
            guiradAnalysisChartDPMP.BorderSkin.BorderColor = Color.Black;
            guiradAnalysisChartDPMP.BorderSkin.BorderDashStyle = ChartDashStyle.NotSet;
            guiradAnalysisChartDPMP.BorderSkin.BorderWidth = 1;
            guiradAnalysisChartDPMP.BorderSkin.PageColor = Color.White;
            guiradAnalysisChartDPMP.BringToFront();
            lblDPLegend.BringToFront();
            lblMPLegend.BringToFront();

            guiradAnalysisChartAix75.BorderlineColor = Color.White;
            guiradAnalysisChartAix75.BorderlineDashStyle = ChartDashStyle.Solid;
            guiradAnalysisChartAix75.BorderlineWidth = 1;
            guiradAnalysisChartAix75.BorderSkin.SkinStyle = BorderSkinStyle.None;
            guiradAnalysisChartAix75.BorderSkin.BackColor = Color.Gray;
            guiradAnalysisChartAix75.BorderSkin.BackGradientStyle = GradientStyle.None;
            guiradAnalysisChartAix75.BorderSkin.BackHatchStyle = ChartHatchStyle.None;
            guiradAnalysisChartAix75.BorderSkin.BorderColor = Color.Black;
            guiradAnalysisChartAix75.BorderSkin.BorderDashStyle = ChartDashStyle.NotSet;
            guiradAnalysisChartAix75.BorderSkin.BorderWidth = 1;
            guiradAnalysisChartAix75.BorderSkin.PageColor = Color.White;
            guiradAnalysisChartAix75.BringToFront();

            guiradAnalysisChartSP.BorderlineColor = Color.White;
            guiradAnalysisChartSP.BorderlineDashStyle = ChartDashStyle.Solid;
            guiradAnalysisChartSP.BorderlineWidth = 1;
            guiradAnalysisChartSP.BorderSkin.SkinStyle = BorderSkinStyle.None;
            guiradAnalysisChartSP.BorderSkin.BackColor = Color.Gray;
            guiradAnalysisChartSP.BorderSkin.BackGradientStyle = GradientStyle.None;
            guiradAnalysisChartSP.BorderSkin.BackHatchStyle = ChartHatchStyle.None;
            guiradAnalysisChartSP.BorderSkin.BorderColor = Color.Black;
            guiradAnalysisChartSP.BorderSkin.BorderDashStyle = ChartDashStyle.NotSet;
            guiradAnalysisChartSP.BorderSkin.BorderWidth = 1;
            guiradAnalysisChartSP.BorderSkin.PageColor = Color.White;
            guiradAnalysisChartSP.BringToFront();

            guiradAnalysisChartPP.Update();
            guiradAnalysisChartHR.Update();
            guiradAnalysisChartAP.Update();
            guiradAnalysisChartDPMP.Update();
            guiradAnalysisChartAix75.Update();
            guiradAnalysisChartSP.Update();

            // Setting the properties for Clicked Chart
            smallChart.BorderlineColor = Color.White;
            smallChart.BorderlineDashStyle = ChartDashStyle.Solid;
            smallChart.BorderlineWidth = 3;
            smallChart.BorderSkin.SkinStyle = BorderSkinStyle.Emboss;
            smallChart.BorderSkin.BackColor = Color.Transparent;
            smallChart.BorderSkin.BackGradientStyle = GradientStyle.None;
            smallChart.BorderSkin.BackHatchStyle = ChartHatchStyle.BackwardDiagonal;
            smallChart.BorderSkin.BorderColor = Color.Transparent;
            smallChart.BorderSkin.BorderDashStyle = ChartDashStyle.Solid;
            smallChart.BorderSkin.BorderWidth = 2;
            smallChart.BorderSkin.PageColor = Color.FromArgb(142, 150, 186);
            smallChart.SendToBack();

            ElementPosition obj = new ElementPosition();
            obj.X = Convert.ToInt32(6.926702);
            obj.Y = Convert.ToInt32(14.8504);
            obj.Height = 79;
            obj.Width = Convert.ToInt32(84.18234);

            smallChart.ChartAreas[0].Position = obj;

            guiradLargeChart.Titles.Clear();
            guiradLargeChart.Titles.Add(smallChart.Titles[0].Text);
            guiradLargeChart.Titles[0].ForeColor = Color.WhiteSmoke;
            guiradLargeChart.Titles[0].Font = new Font("Arial", 11, FontStyle.Bold);

            guiradLargeChart.ChartAreas[0].AxisX.Minimum = smallChart.ChartAreas[0].AxisX.Minimum;
            guiradLargeChart.ChartAreas[0].AxisX.Maximum = smallChart.ChartAreas[0].AxisX.Maximum;
            guiradLargeChart.ChartAreas[0].AxisX.Interval = smallChart.ChartAreas[0].AxisX.Interval;
            guiradLargeChart.ChartAreas[0].AxisX.Crossing = smallChart.ChartAreas[0].AxisX.Crossing;
            guiradLargeChart.ChartAreas[0].AxisX.LabelStyle.Enabled = smallChart.ChartAreas[0].AxisX.LabelStyle.Enabled;

            guiradLargeChart.ChartAreas[0].AxisX.MajorGrid.Enabled = smallChart.ChartAreas[0].AxisX.MajorGrid.Enabled;
            guiradLargeChart.ChartAreas[0].AxisX.MajorGrid.LineColor = smallChart.ChartAreas[0].AxisX.MajorGrid.LineColor;
            guiradLargeChart.ChartAreas[0].AxisX.MajorGrid.LineDashStyle = smallChart.ChartAreas[0].AxisX.MajorGrid.LineDashStyle;
            guiradLargeChart.ChartAreas[0].AxisX.MajorGrid.LineWidth = smallChart.ChartAreas[0].AxisX.MajorGrid.LineWidth;
            guiradLargeChart.ChartAreas[0].AxisX.MajorTickMark.Enabled = false;

            guiradLargeChart.ChartAreas[0].AxisX.MinorGrid.Enabled = smallChart.ChartAreas[0].AxisX.MinorGrid.Enabled;
            guiradLargeChart.ChartAreas[0].AxisX.MinorGrid.LineColor = smallChart.ChartAreas[0].AxisX.MinorGrid.LineColor;
            guiradLargeChart.ChartAreas[0].AxisX.MinorGrid.LineDashStyle = smallChart.ChartAreas[0].AxisX.MinorGrid.LineDashStyle;
            guiradLargeChart.ChartAreas[0].AxisX.MinorGrid.LineWidth = smallChart.ChartAreas[0].AxisX.MinorGrid.LineWidth;
            guiradLargeChart.ChartAreas[0].AxisX.MinorTickMark.Enabled = false;

            guiradLargeChart.ChartAreas[0].AxisY.Minimum = smallChart.ChartAreas[0].AxisY.Minimum;
            guiradLargeChart.ChartAreas[0].AxisY.Maximum = smallChart.ChartAreas[0].AxisY.Maximum;
            guiradLargeChart.ChartAreas[0].AxisY.Interval = smallChart.ChartAreas[0].AxisY.Interval;
            guiradLargeChart.ChartAreas[0].AxisY.Crossing = smallChart.ChartAreas[0].AxisY.Crossing;

            guiradLargeChart.ChartAreas[0].AxisY.MajorGrid.Enabled = smallChart.ChartAreas[0].AxisY.MajorGrid.Enabled;
            guiradLargeChart.ChartAreas[0].AxisY.MajorGrid.LineColor = smallChart.ChartAreas[0].AxisY.MajorGrid.LineColor;
            guiradLargeChart.ChartAreas[0].AxisY.MajorGrid.LineDashStyle = smallChart.ChartAreas[0].AxisY.MajorGrid.LineDashStyle;
            guiradLargeChart.ChartAreas[0].AxisY.MajorGrid.LineWidth = smallChart.ChartAreas[0].AxisY.MajorGrid.LineWidth;
            guiradLargeChart.ChartAreas[0].AxisY.LabelStyle.ForeColor = smallChart.ChartAreas[0].AxisY.LabelStyle.ForeColor;

            guiradLargeChart.ChartAreas[0].AxisY.MinorGrid.Enabled = smallChart.ChartAreas[0].AxisY.MinorGrid.Enabled;
            guiradLargeChart.ChartAreas[0].AxisY.MinorGrid.LineColor = smallChart.ChartAreas[0].AxisY.MinorGrid.LineColor;
            guiradLargeChart.ChartAreas[0].AxisY.MinorGrid.LineDashStyle = smallChart.ChartAreas[0].AxisY.MinorGrid.LineDashStyle;
            guiradLargeChart.ChartAreas[0].AxisY.MinorGrid.LineWidth = smallChart.ChartAreas[0].AxisY.MinorGrid.LineWidth;
            guiradLargeChart.ChartAreas[0].AxisY.MinorTickMark.Enabled = false;

            guilblLargeDPLegend.Visible = false;
            guilblLargeMPLegend.Visible = false;

            guiradLargeChart.Series.Clear();

            foreach (Series series in smallChart.Series)
            {
                guiradLargeChart.Series.Add(series);
            }

            guiradLargeChart.Invalidate();
        }

        /** This method clears all chart series for tonometer, normal & reference range
       * */
        void ClearChartData()
        {           
           guichartPWAReport.Series.Clear();           
        }

        /** This method resets all PWA measurement fields
       * */
        void ResetMeasurementFields()
        {           
            guiradlblCentralDp.Text = string.Empty;
            guiradlblCentralHr.Text = string.Empty;
            guiradlblCentralQualityControl.Text = string.Empty;
            guiradlblInterpretationDisplay.Text = string.Empty;
            guiradlblReportOperatordisplay.Text = string.Empty;
         
            guiradtxtReportHeight.Text = string.Empty;
            guiradlblReportHeightDisplay.Text = string.Empty;
            guiradtxtReportHeightInches.Text = string.Empty;
            guiradlblReportHeightInches.Text = string.Empty;
                      
            guiradtxtReportOperator.Text = string.Empty;
            guiradlblReportOperatordisplay.Text = string.Empty;
            guiradtxtInterpretation.Text = string.Empty;
            guiradlblReportNotesDisplay.Text = string.Empty;

            guiradtxtReportBloodPressure1.Text = string.Empty;
            guiradtxtReportBloodPressure2.Text = string.Empty;
            guiradlblreportDPdisplay.Text = string.Empty;
            guiradlblreportSPdisplay.Text = string.Empty;
            guiradlblreportMPdisplay.Text = string.Empty;
        }

        /**This method plots  Average Aortic Pulse graph
       * */        
        private void PlotAvgAorticPulseChart()
        {
            // set y axis (normal range values from Bizsession object in float)
            float[] avgAorticPulse = crxPwaData.C_AV_PULSE;          
            guichartPWAReport.Series.Clear();            

            // initialize series,chartype,add points to series and finally add series to chart.            
            // set display properties for Avg Aortic Pulse graph
            Series avgAorticPulseActualSeries = new Series
            {
                ChartType = SeriesChartType.Spline,
                Color = Color.MediumBlue,
                BorderWidth = 2,
                Name = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.GuiReportActual),
                  
            };

            avgAorticPulseActualSeries.Points.Clear();

            for (int i = 0; i < avgAorticPulse.Length; i++)
            {
                avgAorticPulseActualSeries.Points.AddXY(i, avgAorticPulse[i]);
            }

            guichartPWAReport.Series.Add(avgAorticPulseActualSeries);

            // set properties for series 2 for plotting ideal graph
            Series avgAorticPulseIdealSeries = new Series
            {
                ChartType = SeriesChartType.Spline,
                Color = Color.DimGray,
                BorderWidth = 2,
                Name = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.GuiReportTypical),
            };

            avgAorticPulseIdealSeries.Points.Clear();
            AddDataPointsIdealgraph(avgAorticPulseIdealSeries);

            guichartPWAReport.Series.Add(avgAorticPulseIdealSeries);

            guichartPWAReport.Invalidate();          
        }

        private void AddDataPointsIdealgraph(Series avgAorticPulseSeries2)
        {
            avgAorticPulseSeries2.Points.AddXY(45, 0);
            avgAorticPulseSeries2.Points.AddXY(55, 35);
            avgAorticPulseSeries2.Points.AddXY(65, 75);
            avgAorticPulseSeries2.Points.AddXY(75, 105);
            avgAorticPulseSeries2.Points.AddXY(85, 118);
            avgAorticPulseSeries2.Points.AddXY(91, 121);
            avgAorticPulseSeries2.Points.AddXY(95, 130);
            avgAorticPulseSeries2.Points.AddXY(103, 156);
            avgAorticPulseSeries2.Points.AddXY(106, 158);
            avgAorticPulseSeries2.Points.AddXY(108, 160);
            avgAorticPulseSeries2.Points.AddXY(114, 158);
            avgAorticPulseSeries2.Points.AddXY(116, 156);
            avgAorticPulseSeries2.Points.AddXY(117, 154);
            avgAorticPulseSeries2.Points.AddXY(119, 140);
            avgAorticPulseSeries2.Points.AddXY(125, 131);
            avgAorticPulseSeries2.Points.AddXY(127, 130);
            avgAorticPulseSeries2.Points.AddXY(136, 126);
            avgAorticPulseSeries2.Points.AddXY(140, 120);
            avgAorticPulseSeries2.Points.AddXY(145, 104);
            avgAorticPulseSeries2.Points.AddXY(155, 73);
            avgAorticPulseSeries2.Points.AddXY(165, 50);
            avgAorticPulseSeries2.Points.AddXY(171, 40);
            avgAorticPulseSeries2.Points.AddXY(176, 32);
            avgAorticPulseSeries2.Points.AddXY(187, 21);
            avgAorticPulseSeries2.Points.AddXY(195, 10);
        }

        /**This method is used to show the Aix tracker on the PWA Report screen, depending upon its value.
         */
        private void ShowAixTracker(float maxValue, float minValue, float value, float goodRangeMin, float goodRangeMax)
        {
            // AIx Tracker: Begin
            maxValue = 26;
            minValue = -8;
            value = 22;
            goodRangeMin = -2;
            goodRangeMax = 20;

            guilblAIxValue.Left = guilblAIxSlider.Left + (int)((value - minValue) * (guilblAIxSlider.Width / (int)(maxValue - minValue)));

            guilblAIxGoodMin.Left = guilblAIxSlider.Left + (int)((goodRangeMin - minValue) * (guilblAIxSlider.Width / (int)(maxValue - minValue)));
            guilblAIxGoodMax.Left = guilblAIxSlider.Left + (int)((goodRangeMax - minValue) * (guilblAIxSlider.Width / (int)(maxValue - minValue)));

            guilblAIxValueText.Left = guilblAIxValue.Left - (guilblAIxValueText.Width / 3) + 4;
            guilblAIxGoodMaxText.Left = guilblAIxGoodMax.Left - (guilblAIxGoodMaxText.Width / 3);
            guilblAIxGoodMinText.Left = guilblAIxGoodMin.Left - (guilblAIxGoodMinText.Width / 3);

            guilblAIxValueText.Text = Math.Round(value).ToString();
            guilblAIxGoodMaxText.Text = goodRangeMax.ToString();
            guilblAIxGoodMinText.Text = goodRangeMin.ToString();

            if ((value < goodRangeMin) || (value > goodRangeMax))
            {
                guilblAIxValue.BackColor = Color.Red;
            }
            else
            {
                guilblAIxValue.BackColor = Color.LimeGreen;
            }

            // AIx Tracker: End
        }

        /**This method is used to show the SP tracker on the PWA Report screen, depending upon its value.
        */
        private void ShowSpTracker(float spMaxValue, float spMinValue, float spValue, float spGoodRangeMin, float spGoodRangeMax)
        {
            // SP Tracker: Begin
            spMaxValue = 130;
            spMinValue = 90;
            spValue = 105;
            spGoodRangeMin = 96;
            spGoodRangeMax = 120;

            guilblSPValue.Left = guilblSPSlider.Left + ((int)(spValue - spMinValue) * (guilblSPSlider.Width / (int)(spMaxValue - spMinValue)));

            guilblSPGoodMin.Left = guilblSPSlider.Left + ((int)(spGoodRangeMin - spMinValue) * (guilblSPSlider.Width / (int)(spMaxValue - spMinValue)));
            guilblSPGoodMinText.Left = guilblSPGoodMin.Left - (guilblSPGoodMinText.Width / 3);
            guilblSPGoodMax.Left = guilblSPSlider.Left + ((int)(spGoodRangeMax - spMinValue) * (guilblSPSlider.Width / (int)(spMaxValue - spMinValue)));

            guilblSPValueText.Left = guilblSPValue.Left - (guilblSPValueText.Width / 3) + 2;
            guilblSPGoodMaxText.Left = guilblSPGoodMax.Left - (guilblSPGoodMaxText.Width / 3);            

            guilblSPValueText.Text = Math.Round(spValue).ToString();
            guilblSPGoodMaxText.Text = spGoodRangeMax.ToString();
            guilblSPGoodMinText.Text = spGoodRangeMin.ToString();

            if ((spValue < spGoodRangeMin) || (spValue > spGoodRangeMax))
            {
                guilblSPValue.BackColor = Color.Red;
            }
            else
            {
                guilblSPValue.BackColor = Color.LimeGreen;
            }

            // SP Tracker: End
        }

        /**This method is used to show the PP tracker on the PWA Report screen, depending upon its value.
        */
        private void ShowPpTracker(float ppMaxValue, float ppMinValue, float ppValue, float ppGoodRangeMin, float ppGoodRangeMax)
        {
            // PP Tracker: Begin
            ppMaxValue = 25;
            ppMinValue = 0;
            ppValue = 23;
            ppGoodRangeMin = 5;
            ppGoodRangeMax = 20;

            guilblPPValue.Left = guilblPPSlider.Left + ((int)(ppValue - ppMinValue) * (guilblPPSlider.Width / (int)(ppMaxValue - ppMinValue)));

            guilblPPGoodMin.Left = guilblPPSlider.Left + ((int)(ppGoodRangeMin - ppMinValue) * (guilblPPSlider.Width / (int)(ppMaxValue - ppMinValue)));
            guilblPPGoodMax.Left = guilblPPSlider.Left + ((int)(ppGoodRangeMax - ppMinValue) * (guilblPPSlider.Width / (int)(ppMaxValue - ppMinValue)));

            guilblPPValueText.Left = guilblPPValue.Left - (guilblPPValueText.Width / 3) + 3;
            guilblPPGoodMaxText.Left = guilblPPGoodMax.Left - (guilblPPGoodMaxText.Width / 3);
            guilblPPGoodMinText.Left = guilblPPGoodMin.Left - (guilblPPGoodMinText.Width / 3);

            guilblPPValueText.Text = Math.Round(ppValue).ToString();
            guilblPPGoodMaxText.Text = ppGoodRangeMax.ToString();
            guilblPPGoodMinText.Text = ppGoodRangeMin.ToString();

            if ((ppValue < ppGoodRangeMin) || (ppValue > ppGoodRangeMax))
            {
                guilblPPValue.BackColor = Color.Red;
            }
            else
            {
                guilblPPValue.BackColor = Color.LimeGreen;
            }

            // PP Tracker: End
        }

        /**This method is used to show the AP tracker on the PWA Report screen, depending upon its value.
        */
        private void ShowApTracker(float apMaxValue, float apMinValue, float apValue, float apGoodRangeMin, float apGoodRangeMax)
        {
            // AP Tracker: Begin
            apMaxValue = 12;
            apMinValue = -6;
            apValue = 4;
            apGoodRangeMin = -3;
            apGoodRangeMax = 9;

            guilblAPValue.Left = guilblAPSlider.Left + ((int)(apValue - apMinValue) * (guilblAPSlider.Width / (int)(apMaxValue - apMinValue)));

            guilblAPGoodMin.Left = guilblAPSlider.Left + ((int)(apGoodRangeMin - apMinValue) * (guilblAPSlider.Width / (int)(apMaxValue - apMinValue)));
            guilblAPGoodMax.Left = guilblAPSlider.Left + ((int)(apGoodRangeMax - apMinValue) * (guilblAPSlider.Width / (int)(apMaxValue - apMinValue)));

            guilblAPValueText.Left = guilblAPValue.Left - (guilblAPValueText.Width / 3) + 5;
            guilblAPGoodMaxText.Left = guilblAPGoodMax.Left - (guilblAPGoodMaxText.Width / 3);
            guilblAPGoodMinText.Left = guilblAPGoodMin.Left - (guilblAPGoodMinText.Width / 3);

            guilblAPValueText.Text = Math.Round(apValue).ToString();
            guilblAPGoodMaxText.Text = apGoodRangeMax.ToString();
            guilblAPGoodMinText.Text = apGoodRangeMin.ToString();

            if ((apValue < apGoodRangeMin) || (apValue > apGoodRangeMax))
            {
                guilblAPValue.BackColor = Color.Red;
            }
            else
            {
                guilblAPValue.BackColor = Color.LimeGreen;
            }

            // AP Tracker: End
        }

        /**This method is used to show the Scor refernce range tracker on the PWA Report screen, depending upon its value.
        */ 

        /** This method Populates data point values on the mouse hover in guiradLargeChart Chart
        */
        private void guiradLargeChart_Paint(object sender, PaintEventArgs e)
        {
            SetToolTip(((Chart)sender));
        }

        /** This method Populates data point values on the mouse hover in guiradAnalysisChartHR Chart
        */
        private void guiradAnalysisChartHR_Paint(object sender, PaintEventArgs e)
        {
            SetToolTip(((Chart)sender));
        }
       
        /** This method Populates data point values on the mouse hover in guiradAnalysisChartSP Chart
                */
        private void guiradAnalysisChartSP_Paint(object sender, PaintEventArgs e)
        {
            SetToolTip(((Chart)sender));
        }

        /** This method Populates data point values on the mouse hover in guiradAnalysisChartPP Chart
                 */
        private void guiradAnalysisChartPP_Paint(object sender, PaintEventArgs e)
        {
            SetToolTip(((Chart)sender));
        }

        /** This method Populates data point values on the mouse hover in guiradAnalysisChartAP Chart
                 */
        private void guiradAnalysisChartAP_Paint(object sender, PaintEventArgs e)
        {
            SetToolTip(((Chart)sender));
        }

        /** This method Populates data point values on the mouse hover in guiradAnalysisChartAix75 Chart
                 */
        private void guiradAnalysisChartAix75_Paint(object sender, PaintEventArgs e)
        {
            SetToolTip(((Chart)sender));
        }

        /** This method Populates data point values on the mouse hover in guiradAnalysisChartDPMP Chart
                 */
        private void guiradAnalysisChartDPMP_Paint(object sender, PaintEventArgs e)
        {
            SetToolTip(((Chart)sender));
        }

        private void SetToolTip(Chart chart)
        {
            int seriesIndex = chart.Series.Count;
            for (int i = 0; i < seriesIndex; i++)
            {
                int columnIndex = chart.Series[i].Points.Count;
                for (int j = 0; j < columnIndex; j++)
                {
                    chart.Series[i].Points[j].ToolTip = "(#VALX,#VAL)";
                }
            }
        }

        private void guipnlPatientDetails_Paint(object sender, PaintEventArgs e)
        {
            e.Graphics.DrawRectangle(
            Pens.Black,
            e.ClipRectangle.Left,
            e.ClipRectangle.Top,
            e.ClipRectangle.Width - 1,
            e.ClipRectangle.Height - 1);
            OnPaint(e);
        }

        /**This event is fired when the user tried to repeat a PWA capture.In this case, the user will be redirected to 
         */ 
        private void guiradbtnRepeat_Click(object sender, EventArgs e)
        {
            try
            {
                // Set this flag to true.
                // When the user is navigated to the setup screen the GetBP will start automatically.
                GuiCommon.RepeatButtonClickedStartNibpOnSetup = true;

                objDefaultWindow.radpgTabCollection.SelectedPage = objDefaultWindow.guiradgrpbxPwvDistanceMethod;
                objDefaultWindow.radlblMessage.Text = string.Empty;
            }
            catch (Exception ex)
            {
                GUIExceptionHandler.HandleException(ex, this);
            }
        }

        private void guiradbtnDelete_Click(object sender, EventArgs e)
        {
            try
            {
                // display confirmation message box
                DialogResult result = RadMessageBox.Show(this, oMsgMgr.GetMessage(CrxStructCommonResourceMsg.DeletePwvMsg).Replace("{0}", recordsToDelete.ToString()), oMsgMgr.GetMessage(CrxStructCommonResourceMsg.SystemError), MessageBoxButtons.YesNo);

                if (result == DialogResult.Yes)
                {
                    // delete selected records
                    int del = dbMagr.DeleteCuffPWAMeasurementDetails(pwaIdWithComma);

                    if (del == 1)
                    {
                        // records deleted successfully, bind assessment grid
                        FillPatientAssessmentDetailsReport();
                        CheckLastAssessmentSelected(pwaIdToCompare);

                        // guiradlblReportPwvDistanceMethodType.Text = crxMgrObject.PwvSettings.PWVDistanceMethod.Equals((int)CrxGenPwvValue.CrxPwvDistMethodDirect) ? oMsgMgr.GetMessage(CrxStructCommonResourceMsg.ReportLblDirect) : oMsgMgr.GetMessage(CrxStructCommonResourceMsg.ReportLblSubtracting); 
                    }
                }

                CheckForSimualtionMode();
            }
            catch (Exception ex)
            {
                GUIExceptionHandler.HandleException(ex, this);
            }
        }

        /** This method plots Ap trend graph
         * */
        private void PlotApTrendData(CrxStructPWATrendData trendData)
        {
            apRate = trendData.ApValidArrStr.Split(GuiConstants.Separator);

            // plot heart rate series
            if (apRate.Length > 0)
            {
                for (int series = 0; series < apRate.Length; series++)
                {
                    guiradAnalysisChartAP.Series[0].Points.AddXY(series, double.Parse(apRate[series], CrxCommon.nCI));
                    guiradAnalysisChartAP.Series[1].Points.AddXY(series, double.Parse(apRate[series], CrxCommon.nCI));
                }

                guiradAnalysisChartAP.Invalidate();
            }
        }

        /** This method plots Hr trend graph
         * */
        private void PlotHrTrendData(CrxStructPWATrendData trendData)
        {
            hrRate = trendData.HrValidArrStr.Split(GuiConstants.Separator);

            // plot heart rate series
            if (hrRate.Length > 0)
            {
                for (int series = 0; series < hrRate.Length; series++)
                {
                    guiradAnalysisChartHR.Series[0].Points.AddXY(series, double.Parse(hrRate[series], CrxCommon.nCI));
                    guiradAnalysisChartHR.Series[1].Points.AddXY(series, double.Parse(hrRate[series], CrxCommon.nCI));
                }

                guiradAnalysisChartHR.Invalidate();
            }
        }

        /** This method plots Pp trend graph
         * */
        private void PlotPpTrendData(CrxStructPWATrendData trendData)
        {
            spRate = trendData.SpValidArrStr.Split(GuiConstants.Separator);
            dpRate = trendData.DpValidArrStr.Split(GuiConstants.Separator);
            ppRate = new string[spRate.Length];
            for (int index = 0; index < spRate.Length; index++)
            {
                ppRate[index] = Convert.ToString(double.Parse(spRate[index]) - double.Parse(dpRate[index]));
            }

            // plot Pp rate series
            if (ppRate.Length > 0)
            {
                for (int series = 0; series < ppRate.Length; series++)
                {
                    guiradAnalysisChartPP.Series[0].Points.AddXY(series, double.Parse(ppRate[series], CrxCommon.nCI));
                    guiradAnalysisChartPP.Series[1].Points.AddXY(series, double.Parse(ppRate[series], CrxCommon.nCI));
                }

                guiradAnalysisChartPP.Invalidate();
            }
        }

        /** This method plots Sp trend graph
        * */
        private void PlotSpTrendData(CrxStructPWATrendData trendData)
        {
            spRate = trendData.SpValidArrStr.Split(GuiConstants.Separator);
            if (spRate.Length > 0)
            {
                for (int series = 0; series < spRate.Length; series++)
                {
                    guiradAnalysisChartSP.Series[0].Points.AddXY(series, double.Parse(spRate[series], CrxCommon.nCI));
                    guiradAnalysisChartSP.Series[1].Points.AddXY(series, double.Parse(spRate[series], CrxCommon.nCI));
                }

                guiradAnalysisChartSP.Invalidate();
            }
        }

        /** This method plots DpMp trend graph
       * */
        private void PlotDpMpTrendData(CrxStructPWATrendData trendData)
        {
            dpRate = trendData.DpValidArrStr.Split(GuiConstants.Separator);
            mpRate = trendData.MpValidArrStr.Split(GuiConstants.Separator);

            // plot Dp & Mp series
            if (dpRate.Length > 0 && mpRate.Length > 0)
            {
                for (int series = 0; series < mpRate.Length && series < dpRate.Length; series++)
                {
                    guiradAnalysisChartDPMP.Series[0].Points.AddXY(series, double.Parse(dpRate[series], CrxCommon.nCI));
                    guiradAnalysisChartDPMP.Series[1].Points.AddXY(series, double.Parse(dpRate[series], CrxCommon.nCI));
                    guiradAnalysisChartDPMP.Series[2].Points.AddXY(series, double.Parse(mpRate[series], CrxCommon.nCI));
                    guiradAnalysisChartDPMP.Series[3].Points.AddXY(series, double.Parse(mpRate[series], CrxCommon.nCI));
                }

                guiradAnalysisChartDPMP.Invalidate();
            }
        }

        /**This method is used to check if the report is generate in the Simulation mode or not.
         * If it is generated in Simulation mode then display appropiate message in the message alert area.
         */
        private void CheckForSimualtionMode()
        {
            if (!(numeberOfRecordsSelected > 1))
            {
                if (crxMgrObject.GeneralSettings.CommsPort.Equals(oMsgMgr.GetMessage(CrxStructCommonResourceMsg.Simulation).ToUpper()) && guiradgridReportAssessment.Rows.Count > 0)
                {
                    objDefaultWindow.radlblMessage.Text = CrxMessagingManager.Instance.GetMessage(CrxStructCommonResourceMsg.GuiSimulationModeMessage);
                }
                else
                {
                    objDefaultWindow.radlblMessage.Text = string.Empty;
                }
            }
        }

        /**This method calculates height & weight to update bizsession object for validating data before saving
   */
        void CalculateHeightAndWeightToValidateSession()
        {
            // calculates height in inches & centimeters
            if (guiradtxtReportHeightInches.Visible)
            {
                // Convert the user input to height and inches
                int heightinches = (int.Parse((string.IsNullOrEmpty(guiradtxtReportHeight.Text.Trim()) ? "0" : guiradtxtReportHeight.Text.Trim())) * 12) + int.Parse((string.IsNullOrEmpty(guiradtxtReportHeightInches.Text.Trim()) ? "0" : guiradtxtReportHeightInches.Text.Trim()));
                GuiCommon.bizPwaobject.heightAndWeight.heightInInches = heightinches == 0 ? GuiConstants.DefaultValue : ushort.Parse(heightinches.ToString());
            }
            else
            {
                GuiCommon.bizPwaobject.heightAndWeight.heightInCentimetres = string.IsNullOrEmpty(guiradtxtReportHeight.Text.Trim()) ? GuiConstants.DefaultValue : ushort.Parse(guiradtxtReportHeight.Text.Trim());
            }
        }

        /**This method calculates height & weight to update changes
     */
        void CalculateHeightAndWeightToUpdate(CrxStructPWAMeasurementData crxPwa)
        {
            crxPwa.HeightInInches = crxPwa.WeightInPounds = crxPwa.HeightInCentimetres = crxPwa.WeightInKilograms = GuiConstants.SdefaultValue;

            // calculates height in inches & centimeters
            if (guiradtxtReportHeightInches.Visible)
            {
                int heightinches = (int.Parse((string.IsNullOrEmpty(guiradtxtReportHeight.Text.Trim()) ? "0" : guiradtxtReportHeight.Text.Trim())) * 12) + int.Parse((string.IsNullOrEmpty(guiradtxtReportHeightInches.Text.Trim()) ? "0" : guiradtxtReportHeightInches.Text.Trim()));
                crxPwa.HeightInInches = heightinches == 0 ? GuiConstants.SdefaultValue : short.Parse(heightinches.ToString());

                // crxPwv.WeightInPounds = string.IsNullOrEmpty(guiradtxtReportWeight.Text.Trim()) ? GuiConstants.SdefaultValue : short.Parse(guiradtxtReportWeight.Text.Trim());        
            }
            else
            {
                crxPwa.HeightInCentimetres = string.IsNullOrEmpty(guiradtxtReportHeight.Text.Trim()) ? GuiConstants.SdefaultValue : short.Parse(guiradtxtReportHeight.Text.Trim());

                // crxPwv.WeightInKilograms = string.IsNullOrEmpty(guiradtxtReportWeight.Text.Trim()) ? GuiConstants.SdefaultValue : short.Parse(guiradtxtReportWeight.Text.Trim());
            }
        }        

        /** This method validates session data
        * */
        bool ValidateSession(CrxStructPWAMeasurementData crxPwa)
        {
            GuiCommon.bizPwaobject.Sp = string.IsNullOrEmpty(guiradlblreportSPdisplay.Text.Trim()) ? GuiConstants.DefaultValue : float.Parse(guiradlblreportSPdisplay.Text.Trim());
            GuiCommon.bizPwaobject.Dp = string.IsNullOrEmpty(guiradlblreportDPdisplay.Text.Trim()) ? GuiConstants.DefaultValue : float.Parse(guiradlblreportDPdisplay.Text.Trim()); 
            GuiCommon.bizPwaobject.MeasureType = PWA_MEASURE_TYPE.PWA_RADIAL;
            CalculateHeightAndWeightToValidateSession();            
            return GuiCommon.bizPwaobject.Validate();
        }        

        /**This method initializes Crx structure to update changes
      * */
        int InitializeCrx(CrxStructPWAMeasurementData crxPwa, CrxStructCuffPWAMeasurementData crxCuffPwa)
        {
            int flag = 0;

            // populate GuiCommon.bizPwaobject with entered data & check for validation
            // if it returns true then initialize crxPWA else return error & repopluate GuiCommon.bizPwaobject with original values                        
            if (ValidateSession(crxPwa))
            {
                crxPwa.PWA_Id = int.Parse(GuiCommon.PwaCurrentId);
                crxCuffPwa.PWA_Id = int.Parse(GuiCommon.PwaCurrentId);
                CalculateHeightAndWeightToUpdate(crxPwa);

                crxPwa.MemSpare1 = guiradtxtInterpretation.Text.Trim();           

                crxPwa.SystemIdentifier = bobj;
                crxPwa.GroupIdentifier = GuiCommon.GroupId;
                crxPwa.PatientNumberInternal = GuiCommon.PatientInternalNumber;             
                
                // call recalculatepwareport which will calculate PWA statistics values & will update biz session object.                             
                if (GuiCommon.bizPwaobject.Populate(crxPwa, crxCuffPwa))
                {
                    if (!GuiCommon.bizPwaobject.RecalculatePWAReport(crxPwa, crxCuffPwa))
                    {
                        // error recalculating data
                        // do not save in database
                        flag = 2;
                    }
                }
                else
                { 
                    // error populating data
                    // do not save in database
                    flag = 2;
                }
            }
            else
            {
                flag = 1;
            }

            return flag;
        }

        /**This method is used to Save the measurement details into the database.
         */
        private void SaveMeasurementData(CrxStructPWAMeasurementData crxPWA, CrxStructCuffPWAMeasurementData crxCuffPWA)
        {
            // update measurement data
            // save data          
            crxPWA.StudyDateTime = DateTime.Parse(GuiCommon.PwaCurrentStudyDatetime, CrxCommon.gCI);
            crxPWA.PWA_Id = int.Parse(GuiCommon.PwaCurrentId);
            int iRow = guiradgridReportAssessment.Rows.Count > 0 ? dbMagr.UpdateCuffPWAMeasurementDetails(crxPWA, crxCuffPWA) : dbMagr.SaveCuffPWAMeasurementDetails(crxPWA, crxCuffPWA);

            if (iRow > 0)
            {
                // record updated successfully
                // populate session object                   

                // get the latest date from crxPWA with which data is updated
                GuiCommon.PwaCurrentStudyDatetime = crxPWA.StudyDateTime.ToString();
                GuiCommon.PwaCurrentId = crxPWA.PWA_Id.ToString();
                CrxLogger.Instance.Write("GuiCommon.PwaCurrentStudyDatetime:(SaveMeasurementData) " + GuiCommon.PwvCurrentStudyDatetime);

                FillPatientAssessmentDetailsReport();              

                // re populate label fields again and display mode = true
                ReportPWADisplayMode(true);
                guiradbtnreportcancel.Visible = false;
                guiradbtnreportedit.Visible = true;

                guiradbtnreportsave.Visible = false;
                OnPwaMeasurementChangedEvent.Invoke(this, new EventArgs());
            }
        }

        private void guiradbtnreportsave_Click(object sender, EventArgs e)
        {
            try
            {
                objDefaultWindow.radlblMessage.Text = string.Empty;
               
                    // check db connection
                    if (dbMagr.CheckConnection(serverNameString, crxMgrObject.GeneralSettings.SourceData) == 0)
                    {
                        // save PWA details in database and session object
                        // CrxStructPWAMeasurementData crxPwaData = new CrxStructPWAMeasurementData();
                        // CrxStructCuffPWAMeasurementData crxPwaCuffData = new CrxStructCuffPWAMeasurementData();

                        /* InitializeCrx(crxPwaData,crxPwaCuffData) returns integer
                         * 0 => update measurement data
                         * 1 => validation failed
                         * 2 => report calculation failed
                         */
                        switch (InitializeCrx(crxPwaData, crxPwaCuffData))
                        {
                            case (int)InitializeCrxValue.UpdateData:
                                // update measurement data
                                // save data                            
                                SaveMeasurementData(crxPwaData, crxPwaCuffData);
                                CheckLastAssessmentSelected(pwaIdToCompare);
                                guiradgridReportAssessment.Enabled = true;
                                break;
                            case (int)InitializeCrxValue.ValidationFailed:
                                // GuiCommon.bizPwaobject validation failed                            
                                RadMessageBox.Show(this, oMsgMgr.GetMessage(CrxStructCommonResourceMsg.ErrorValidating), oMsgMgr.GetMessage(CrxStructCommonResourceMsg.SystemError), MessageBoxButtons.OK, RadMessageIcon.Error);
                                break;
                            case (int)InitializeCrxValue.ReportCalculationFailed:
                                // report calculation failed
                                RadMessageBox.Show(this, oMsgMgr.GetMessage(CrxStructCommonResourceMsg.ReportCalculateError), oMsgMgr.GetMessage(CrxStructCommonResourceMsg.SystemError), MessageBoxButtons.OK, RadMessageIcon.Error);
                                break;
                            default:
                                break;
                        }

                        GuiCommon.IsFormChanged = false;
                    }
                    else
                    {
                        DialogResult result = RadMessageBox.Show(this, GuiCommon.ConnectionErrorString(), oMsgMgr.GetMessage(CrxStructCommonResourceMsg.SystemError), MessageBoxButtons.RetryCancel, RadMessageIcon.Error);
                        if (result == DialogResult.Retry)
                        {
                            Invoke(new EventHandler(guiradbtnreportsave_Click));
                        }
                    }                

                CheckForSimualtionMode();
            }
            catch (Exception ex)
            {
                GUIExceptionHandler.HandleException(ex, this);
            }    
        }      
       
        /** This event gets fired when focus is moved from height in inches text box.
       * It checks if the value entered in textbox is within valid range and shows error accordingly
       * */  
        private void guiradtxtReportHeightInches_Leave(object sender, EventArgs e)
        {
            objValidation.CheckIntegerFieldLimits(guiradtxtReportHeightInches);
        }

        /** This event gets fired when focus is moved from height in centimeteres & height in feet text box.
       * It checks if the value entered in textbox is within valid range and shows error accordingly
       * */
        private void guiradtxtReportHeight_Leave(object sender, EventArgs e)
        {
            objValidation.CheckIntegerFieldLimits(guiradtxtReportHeight);
        }

        /** This method fille structure "PWAClinicalEvaluationReport" with the values to be printed on PWV report.
* This values will be used in Crystal Reports.
* */
        private void FillStructForPWACommonReport()
        {
            PWACommonReportData.RptPwaId = crxPwaData.PWA_Id;

            PWACommonReportData.RptReferenceAgeValue = String.Format("{0}{1}", oMsgMgr.GetMessage(CrxStructCommonResourceMsg.LblPwaSyphymocorRefAge), " > " + Math.Round(GuiCommon.bizPwaobject.ReferenceAge).ToString());

            PWACommonReportData.RptHeader = string.IsNullOrEmpty(crxMgrObject.GeneralSettings.ReportTitle) ? BizInfo.Instance().GetCompanyName().Replace("(R)", "\u00AE") : crxMgrObject.GeneralSettings.ReportTitle.Replace("(R)", "\u00AE");

            PWACommonReportData.RptPatientDataHeader = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.RptPatientDataTitle);

            PWACommonReportData.RptPatientName = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.LblPatientName);
            PWACommonReportData.RptPatientNameValue = string.IsNullOrEmpty(patientObj.firstName) ? patientObj.lastName : string.Format("{0} {1}", patientObj.firstName, patientObj.lastName);

            PWACommonReportData.RptPatientId = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.LblPatientId);
            PWACommonReportData.RptPatientIdValue = patientObj.patientId;

            PWACommonReportData.RptPatientDob = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.LblReportDob);
            //PWACommonReportData.RptPatientDobValue = patientObj.dateOfBirth.ToString(oMsgMgr.GetMessage(CrxStructCommonResourceMsg.ReportDateTimeFormat));
            PWACommonReportData.RptPatientDobValue = patientObj.dateOfBirth.ToShortDateString();

            PWACommonReportData.RptPatientAge = string.Format("{0},{1}", oMsgMgr.GetMessage(CrxStructCommonResourceMsg.RptAgeTitle), oMsgMgr.GetMessage(CrxStructCommonResourceMsg.LblReportGender));
            //PWACommonReportData.RptPatientAgeValue = obj.patientAge.ToString();
            PWACommonReportData.RptPatientAgeValue = string.Format("{0},{1}", GuiCommon.bizPwaobject.patientAge.ToString(), oMsgMgr.GetMessage(patientObj.gender));

            //PWACommonReportData.RptPatientGender = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.LblReportGender);
            //PWACommonReportData.RptPatientGenderValue = oMsgMgr.GetMessage(patientObj.gender);

            PWACommonReportData.RptStudyDataHeader = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.RptMeasurementData);

            PWACommonReportData.RptPatientAssessment = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.RptDateAndTime);
            PWACommonReportData.RptPatientAssessmentValue = string.Format("{0:g}.", Convert.ToDateTime(GuiCommon.PwaCurrentStudyDatetime)); // GuiCommon.PwvCurrentStudyDatetime;

            PWACommonReportData.RptPatientBP = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.RptBrachialBp);

            PWACommonReportData.RptPatientBPValue = SetBPForPWAReport();

            PWACommonReportData.RptPatientHeight = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.LblHeight);

            PWACommonReportData.RptPatientHeightValue = SetPatientHeightValue();
            
            PWACommonReportData.RptDatabaseVersionTitle = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.RptDatabaseVersionTitle);

            PWACommonReportData.RptDatabaseVersionValue = GuiCommon.bizPwaobject.dataRevision.ToString();// string.Empty;

            PWACommonReportData.RptWaveformPlotTitle = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.RptWaveformPlotTitle);

            PWACommonReportData.RptWaveformPlotValue = string.Empty;

            PWACommonReportData.RptNumberOfWaveformsTitle = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.RptNumberOfWaveformsTitle);

            PWACommonReportData.RptNumberOfWaveformsValue = string.Empty;

            PWACommonReportData.RptQualityControlTitle = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.RptQualityControlTitle);

            PWACommonReportData.RptQualityControlValue = crxPwaCuffData.P_QC_OTHER4.ToString();

            PWACommonReportData.RptSignatureTitle = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.RptSignatureTitle);

            PWACommonReportData.RptPhysicianTitle = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.RptPhysicianTitle);

            PWACommonReportData.RptSimulationModeTitle = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.RptSimulationModeTitle);
        }

        /** This method fille structure "PWAClinicalReport" with the values to be printed on PWV report.
       * This values will be used in Crystal Reports.
       * */
        private void FillStructForPWAClinicalReport()
        {
            PWAClinicalReportData.RptClinicalParametersTitle = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.RptClinicalParametersTitle);

            PWAClinicalReportData.RptCentralPressureWaveformTitle = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.RptCentralPressureWaveformTitle);

            //PWAClinicalReportData.RptInterpretationTitle = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.RptInterpretationTitle);
            PWAClinicalReportData.RptInterpretationTitle = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.LblNotes);

            PWAClinicalReportData.RptInterpretationValue = crxPwaData.Medication;// string.Empty;
           
            PWAClinicalReportData.RptBrachialTitle = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.RptBrachialTitle);

            PWAClinicalReportData.RptAroticTitle = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.RptAroticTitle);

            PWAClinicalReportData.RptSPTitle = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.Sp);

            PWAClinicalReportData.RptDPTitle = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.Dp);

            PWAClinicalReportData.RptMPTitle = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.RptMapTitle);

            PWAClinicalReportData.RptPPTitle = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.FieldPatientPp);

            PWAClinicalReportData.RptHRTitle = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.FieldPatientHr);

            PWAClinicalReportData.RptSPBrachialValue = crxPwaData.SP.Equals(GuiConstants.DefaultValue) ? string.Empty : crxPwaData.SP.ToString();
            PWAClinicalReportData.RptDPBrachialValue = crxPwaData.DP.Equals(GuiConstants.DefaultValue) ? string.Empty : crxPwaData.DP.ToString();
            PWAClinicalReportData.RptMPBrachialValue = crxPwaData.C_Meanp.Equals(GuiConstants.DefaultValue) ? string.Empty : Math.Round(crxPwaData.C_Meanp).ToString();
            RptPwaFillBrachialValue();
            PWAClinicalReportData.RptHRBrachialValue = crxPwaData.HR.Equals(GuiConstants.DefaultValue) ? string.Empty : Math.Round(crxPwaData.HR).ToString();

            PWAClinicalReportData.RptSPAroticValue = crxPwaData.C_Sp.Equals(GuiConstants.DefaultValue) ? string.Empty : Math.Round(crxPwaData.C_Sp).ToString();
            PWAClinicalReportData.RptDPAroticValue = crxPwaData.C_Dp.Equals(GuiConstants.DefaultValue) ? string.Empty : Math.Round(crxPwaData.C_Dp).ToString();
            PWAClinicalReportData.RptMPAroticValue = crxPwaData.C_Meanp.Equals(GuiConstants.DefaultValue) ? string.Empty : Math.Round(crxPwaData.C_Meanp).ToString();
            RptPwaFillAroticValue();
            PWAClinicalReportData.RptHRAroticValue = crxPwaData.HR.Equals(GuiConstants.DefaultValue) ? string.Empty : Math.Round(crxPwaData.HR).ToString();
        }

        /** This method fille structure "PWAEvaluationReport" with the values to be printed on PWV report.
       * This values will be used in Crystal Reports.
       * */
        private void FillStructForPWAEvaluationReport()
        {
            PWAEvaluationReportData.RptCentralPressureWaveformTitle = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.RptCentralPressureWaveformTitle);

            PWAEvaluationReportData.RptCentralHaemodynamicParametersTitle = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.RptCentralHaemodynamicParametersTitle);

            PWAEvaluationReportData.RptHeartRatePeriodTitle = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.RptHeartRatePeriodTitle);

            PWAEvaluationReportData.RptHeartRatePeriodValue = string.Format("{0},{1}", Math.Round(crxPwaData.HR), Math.Round(crxPwaData.C_Period));

            PWAEvaluationReportData.RptAroticT1T2Title = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.RptAroticT1T2Title);

            PWAEvaluationReportData.RptAorticT1T2Value = string.Format("{0},{1},{2}", Math.Round(crxPwaData.C_T1), Math.Round(crxPwaData.C_T2), Math.Round(crxPwaData.C_T1r));

            PWAEvaluationReportData.RptP1HeightTitle = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.RptP1HeightTitle);

            PWAEvaluationReportData.RptP1HeightValue = Math.Round(crxPwaData.C_P1_Height).ToString();

            PWAEvaluationReportData.RptAorticAixTitle = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.RptAorticAixTitle);

            PWAEvaluationReportData.RptAorticAixValue = Math.Round(crxPwaData.C_Agph).ToString();

            PWAEvaluationReportData.RptAorticAIxHR75Title = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.RptAorticAIxHR75Title);

            PWAEvaluationReportData.RptAorticAIxHR75Value = string.Empty;

            PWAEvaluationReportData.RptAorticAugmentationAP_PPTitle = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.RptAorticAugmentationAP_PPTitle);

            PWAEvaluationReportData.RptAorticAugmentationAP_PPValue = string.Format("{0},{1}", Math.Round(crxPwaData.C_Ap), PWAClinicalReportData.RptPPAroticValue);

            PWAEvaluationReportData.RptEndSystolicPressureTitle = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.RptEndSystolicPressureTitle);

            PWAEvaluationReportData.RptEndSystolicPressureValue = Math.Round(crxPwaData.C_Esp).ToString();

            PWAEvaluationReportData.RptMPSystoleDiastoleTitle = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.RptMPSystoleDiastoleTitle);

            PWAEvaluationReportData.RptMPSystoleDiastoleValue = string.Format("{0},{1}", Math.Round(crxPwaData.C_Mps), Math.Round(crxPwaData.C_Mpd));
        }

        /** This method "SetBPForPWAReport" will return string for BP values
      * This values will be used in Crystal Reports.
      * */
        private string SetBPForPWAReport()
        {
            string blpValue = string.Empty;
            blpValue = GuiCommon.bizPwaobject.bloodPressure.SP.Reading.ToString() + oMsgMgr.GetMessage(CrxStructCommonResourceMsg.GuiDisplaySlash) + GuiCommon.bizPwaobject.bloodPressure.DP.Reading.ToString();                    
            return blpValue;
        }

        /** This event "guiradbtnPrint_Click" is called when user click print button 
         * */
        private void guiradbtnPrint_Click(object sender, EventArgs e)
        {
            FillStructForPWACommonReport();
            FillStructForPWAClinicalReport();
            FillStructForPWAEvaluationReport();
            
            PWACommonReportData.RptPrintType = crxMgrObject.PwaSettings.DefaultReport;

            PWAClinicalPreview rpPreview = new PWAClinicalPreview();
            rpPreview.Show();
        }

        /** This event "guiPwaClinicalReport_Click" is called when user click "Clinical" print button 
        * */
        private void guiPwaClinicalReport_Click(object sender, EventArgs e)
        {
            FillStructForPWACommonReport();
            FillStructForPWAClinicalReport();
            PWACommonReportData.RptPrintType = CrxStructCommonResourceMsg.PwaClinicalReport;
            PWAClinicalPreview rpPreview = new PWAClinicalPreview();    
            rpPreview.Show();
        }

        /** This method "RptPwaFillBrachialValue" will return string for filling Brachial values
        * This values will be used in Crystal Reports.
        * */
        private void RptPwaFillBrachialValue()
        {
            if (PWAClinicalReportData.RptSPBrachialValue.Equals(string.Empty)
               && PWAClinicalReportData.RptDPBrachialValue.Equals(string.Empty))
            {
                PWAClinicalReportData.RptPPBrachialValue = string.Empty;
            }
            else if (PWAClinicalReportData.RptSPBrachialValue.Equals(string.Empty)
               && !PWAClinicalReportData.RptDPBrachialValue.Equals(string.Empty))
            {
                PWAClinicalReportData.RptPPBrachialValue = PWAClinicalReportData.RptDPBrachialValue;
            }
            else if (!PWAClinicalReportData.RptSPBrachialValue.Equals(string.Empty)
                && PWAClinicalReportData.RptDPBrachialValue.Equals(string.Empty))
            {
                PWAClinicalReportData.RptPPBrachialValue = PWAClinicalReportData.RptSPBrachialValue;
            }
            else
            {
                PWAClinicalReportData.RptPPBrachialValue = (crxPwaData.SP - crxPwaData.DP).ToString();
            }
        }

        /** This method "RptPwaFillAroticValue" will return string for filling Aortic values
       * This values will be used in Crystal Reports.
       * */
        private void RptPwaFillAroticValue()
        {
            if (PWAClinicalReportData.RptSPAroticValue.Equals(string.Empty)
               && PWAClinicalReportData.RptDPAroticValue.Equals(string.Empty))
            {
                PWAClinicalReportData.RptPPAroticValue = string.Empty;
            }
            else if (PWAClinicalReportData.RptSPAroticValue.Equals(string.Empty)
               && !PWAClinicalReportData.RptDPAroticValue.Equals(string.Empty))
            {
                PWAClinicalReportData.RptPPAroticValue = PWAClinicalReportData.RptDPAroticValue;
            }
            else if (!PWAClinicalReportData.RptSPAroticValue.Equals(string.Empty)
                && PWAClinicalReportData.RptDPAroticValue.Equals(string.Empty))
            {
                PWAClinicalReportData.RptPPAroticValue = PWAClinicalReportData.RptSPAroticValue;
            }
            else
            {
                PWAClinicalReportData.RptPPAroticValue = Math.Round(crxPwaData.C_Sp - crxPwaData.C_Dp).ToString();
            }
        }

        private void DisplayInconclusiveMessage(object sender, EventArgs e)
        {
            GuiCommon.DefaultWindowForm.guialertmsgTimer.Enabled = false;
            if (GuiCommon.IsOnSetupScreen)
            {
                objDefaultWindow.radlblMessage.Text = string.Empty;
            }
            else
            {
                objDefaultWindow.radlblMessage.Text = CrxMessagingManager.Instance.GetMessage(CrxStructCommonResourceMsg.GuiSimulationModeMessage);
            }
            GuiCommon.DefaultWindowForm.guialertmsgTimer.Tick -= new EventHandler(DisplayInconclusiveMessage);
        }

        /** This method "SetPatientHeightValue" will return string for filling Height Weight values
      * This values will be used in Crystal Reports.
      * */
        private string SetPatientHeightValue()
        {
            int heightInInches = int.Parse(GuiCommon.bizPwaobject.heightAndWeight.heightInInches.ToString()) % 12;

            int heigthInFeet = int.Parse(GuiCommon.bizPwaobject.heightAndWeight.heightInInches.ToString()) / 12;

            string HeightValue = CrxConfigManager.Instance.GeneralSettings.HeightandWeightUnit.Equals((int)CrxGenPwvValue.CrxGenHeightWeightMetric) ?
                GuiCommon.bizPwaobject.heightAndWeight.heightInCentimetres.Equals(GuiConstants.DefaultValue) ? string.Empty : GuiCommon.bizPwaobject.heightAndWeight.heightInCentimetres.ToString() + " " + oMsgMgr.GetMessage(CrxStructCommonResourceMsg.Cm)
                : GuiCommon.bizPwaobject.heightAndWeight.heightInInches.Equals(GuiConstants.DefaultValue) ? string.Empty : heigthInFeet.ToString() + " " + oMsgMgr.GetMessage(CrxStructCommonResourceMsg.Feet) + " , " + heightInInches + " " + oMsgMgr.GetMessage(CrxStructCommonResourceMsg.Inch);//string.Empty;            

            return HeightValue;
        }
    }
}
