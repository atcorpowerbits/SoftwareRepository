using System;
using System.Collections.Generic;
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
using AtCor.Scor.DataAccess;
using Telerik.WinControls.Enumerations;
using AtCor.Scor.BusinessLogic;
using System.Windows.Forms.DataVisualization.Charting;
using System.Collections;
using System.Text;
using System.Configuration;

namespace AtCor.Scor.Gui.Presentation
{
    public partial class PWAReport : RadForm
    {
        // Events              
        public static event EventHandler OnPwvMeasurementChangedEvent;

        const int MaxLabelYValue = 12; // this denotes the maximum number of values to be displayed on Y axis so that it does not overlap                      
        const int LblVerticalAngle = -90; // angle of labels to display vertically on analysis screen when more records are are selected
        const int LblHorizontalAngle = 0; // angle of labels to display horizontally on analysis screen when few records are are selected
        const string CulturalNeutralDateFormat = "yyyy-MM-dd HH:mm:ss"; // this is a cultural neutral format used for fetching data for different regional settings from back end

        readonly string serverNameString = string.Empty;
        readonly BizPatient patientObj = BizPatient.Instance();

        CrxMessagingManager oMsgMgr;
        CrxConfigManager crxMgrObject;
        CrxDBManager dbMagr;
        BizPWV obj;
        GuiFieldValidation objValidateReport;

        CrxStructPWVMeasurementData crxPWV = new CrxStructPWVMeasurementData();

        int bobj;

        string dateToCompare = string.Empty; // used to compare dates when 30 sec wait interval is imposed to enable / disable repeat button based on last record selected
        string dateWithComma = string.Empty;
        int recordsToDelete; // this variable holds value for number of records to delete and is used across dfifferent methods 
        string lastAssessmentDate = string.Empty;
        private DefaultWindow objDefaultWindow;

        // bool oneRecordSelect = true; // this variable is used to denote whether one single assessment record is selected and accordingly display report data
        string[] date; // date array to be used on analysis screen
        string[] heartRate; // heart rate array to be used on analysis screen
        string[] pWv; // pwv velocity array to be used on analysis screen
        string[] isStdDeviationValid; // standard deviation array to be used on analysis screen
        int[] xCoordinate; // array of x coordinates to display data to the closest datapoint

        int labelInterval;

        // denotes chart type on analysis screen
        enum ChartName
        {
            Pwv,
            HeartRate
        }

        enum SeriesType
        {
            HeartLine = 0,
            HeartPoint,
            PwvLine,
            PwvPoint,
            ErrorBar
        } // series used on analysis screen

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

        ChartName chartSelected; // this is used to hold value for current chart hovered / selected on analysis screen       

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
                obj = (BizPWV)BizSession.Instance().measurement;

                // subscribe report tab click event
                DefaultWindow.OnReportTabClick += PWAReport_Load;

                // DefaultWindow.OnExitSaveReportChanges += guiradbtnreportsave_Click;
                // DefaultWindow.OnReportMenuItemClick += SaveChangesOnMenuFocus;                
                Presentation.Capture.OnReportTabClick += PWAReport_Load;

                // GuiCommon.OnCaptureClosing += EnableRepeatAndCaptureTab;
                // guichartSuperImposedWaveform.BackColor = Color.White;
                // guiradlblReportCarotid.ForeColor = Color.Blue;
            }
            catch (Exception ex)
            {
                GUIExceptionHandler.HandleException(ex, this);
            }
        }

        // AtCor-Drop2-Sprint1
        private void SetTextForPWAReport()
        {
            guiradlblReportAssessments.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.LblReportAssessments);
            guiradlblReportPatientId.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.LblPatientId);
            guiradlblReportPatientName.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.LblPatientName);

            // Commenting the below code as group name is not included in Clinical mode.
            // guiradlblReportGroup.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.LblGroup);
            guiradlblReportDOB.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.LblReportDob);
            guiradlblReportAge.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.LblReportAge);
            guiradlblReportheightWeight.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.LblHeight);

            // Commenting the below code as group name is not included in Clinical mode.
            // guiradlblReportWeight.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.LblWeight);
            // guiradlblReportBmi.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.LblReportBmi);
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
            guiradlblReportDP.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.LblDp);
            guiradlblSphygmocorReferenceAge.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.LblPwaSyphymocorRefAge);
            guioradlblAvgCentralAortlcPulse.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.LblAvgCentralAorticPulse);
            guiradlblQualityControl.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.LblPwaQualityControl);
            guiradlblReportBloodPressure1.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.LblPwaAnalysisSpDpMp);
            slashlabel.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.GuiDisplaySlash);
            lblOpeningBracket.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.LblPwaAnalysisOpeningBrace);
            lblClosingBracket.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.LblPwaAnalysisClosingBrace);
            guiradlblReportDPUnits.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.UnitsPressureMmhg);
            guiradlblInterpretation.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.LblPwaInterpretation);
            guiradlblReportGender.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.LblReportGender);
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

            GuiCommon.SetShape(guilblReportPatientIdValue, guilblReportDobValue, guilblReportAgeValue, guilblReportGenderValue, guiradlblreportSPdisplay, guiradlblReportBloodPressure2, guiradlblReportOperatordisplay, guiradlblReportHeightDisplay, guiradlblReportHeightInches, guiradlblReportBloodPressure3, guiradlblPWAReportInterpretationDisplay, guiradlblHRDisplay, guiradlblDPDisplay, guiradlblQualityControlValue);
            GuiCommon.SetShape(guiradtxtReportBloodPressure1, guiradtxtReportBloodPressure2, guiradtxtReportOperator, guiradtxtReportHeightInches, guiradtxtReportHeight, guiradtxtReportBloodPressure3);
        }

        /**This method is used to round the text boxes and the label controls on the Report screen.
         */

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
        }

        public void LoadPWAReport()
        {
            bobj = GuiConstants.SystemId;
            GuiCommon.CaptureToSetup = false;
            GuiCommon.SystemIdentifier = bobj;
            GuiCommon.ReportLoadCount++;

            // SetTextForReportScreen();
            // SetReportTagForValidation();
            // objValidateReport = new GuiFieldValidation(guipnlReportPatientMeasurementDetails, guiradpnlEditPWVdistance);

            // set default text for report tab
            objDefaultWindow.radtabReport.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.TabReport);

            InitializeReportAssessmentList();
            SetDefaultValuesOnLoad();

            // fill demographic & pwv measurement details & bring the LHS to browse mode
            FillDemographicDetailsReport();

            // initialize crx when user moves from setup to report... call populate method
            InitializeCrxFromSetupToReport(string.Empty);

            // binds assessment details related to patient
            FillPatientAssessmentDetailsReport();

            // to check if wait interval is imposed and accordingly disable/ enable capture tab & repeat buttons
            // CheckWaitIntervalImposed();
            // guichartSuperImposedWaveform.ChartAreas[0].BackColor = Color.White;
            // guichartSuperImposedWaveform.ChartAreas[0].ShadowColor = System.Drawing.Color.Transparent; 
            // Begin: AtCor-Drop2-Sprint1, TM, Prototype,9th June, 2011

            ShowAixTracker();

            ShowSpTracker();

            ShowPpTracker();

            ShowApTracker();

            ShowReferenceAgeTracker();
                          
            guipnlPWAReport.Visible = true;
            guipnlPWAReportAnalysis.Visible = false;

            // End: AtCor-Drop2-Sprint1, TM, Prototype,9th June, 2011
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
                    // hide date time display labels
                    // guiradlblReportDateTime.Visible = false;
                    // guiradlblReportDateTimeDisplay.Visible = false;
                    DataSet ds = dbMagr.GetPWVMeasurementDetails(int.Parse(patientObj.patientNumber.ToString()), GuiCommon.GroupId, bobj);

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

                        objDefaultWindow.radtabReport.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.TabReport);
                        lastAssessmentDate = dateToCompare = guiradgridReportAssessment.MasterTemplate.Rows[ds.Tables[0].Rows.Count - 1].Cells[1].Value.ToString();
                        dateWithComma = DateTime.Parse(guiradgridReportAssessment.MasterTemplate.Rows[ds.Tables[0].Rows.Count - 1].Cells[1].Value.ToString()).ToString(CulturalNeutralDateFormat) + oMsgMgr.GetMessage(CrxStructCommonResourceMsg.GuiDisplayComma);
                        recordsToDelete = 1;

                        if (!GuiCommon.SetupToReport)
                        {
                            // this will populate biz session obj from latest PWV details
                            InitializeCrxOnLoad(guiradgridReportAssessment.MasterTemplate.Rows[ds.Tables[0].Rows.Count - 1].Cells[1].Value.ToString());
                        }

                        GuiCommon.SetupToReport = false;

                        if (ds.Tables[0].Rows.Count == 1)
                        {
                            // guiradchkAssesments.Checked = true;
                            // guiradchkAssesments.Enabled = false;

                            // Since there is only one record in the assessment grid, and it should be checked by default hence making the check box readonly.
                            guiradgridReportAssessment.Rows[0].Cells[0].ReadOnly = true;
                        }

                        FillPWVMeasurementDetailsReport();

                        // SuperImposedWaveForm();
                        // CheckAgeLimit(obj.patientAge);
                        // PlotNormalRangeGraph();
                        // PlotReferenceRangeGraph();
                    }
                    else
                    {
                        guiradbtnreportedit.Enabled = false;
                        guiradbtnDelete.Enabled = false;
                        guiradbtnPrint.Enabled = false;

                        // ClearChartData();
                        // ResetMeasurementFields();
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

        /**This method fill PWV measurement details for a particular patient
        * */
        void FillPWVMeasurementDetailsReport()
        {
            const int LblReportNotesDisplayMaximumLength = 44; // denotes the maximum length of guiradlblReportNotesDisplay label
            // const int LblReportOperatorDisplayMaxLength = 13; // denotes the maximum length of guiradlblReportOperatordisplay label

            //// make display panel visible for PWV distance
            // guiradpnldisplayPWVDistance.Visible = true;
            // guiradpnlEditPWVdistance.Visible = false;

            //// create biz session instance & bind details to labels            
            //// guiradlblreportpwvdistancedisplay.Text = guiradlblreportpwvdistancedisplay1.Text = obj.calculatedDistance.ToString();            
            // if (crxMgrObject.PwvSettings.PWVDistanceUnits.Equals((int)CrxGenPwvValue.CrxPwvDistDistUnitsCM))
            // {
            //    guiradlblreportpwvdistancedisplay.Text = guiradlblreportpwvdistancedisplay1.Text = (obj.calculatedDistance / GuiConstants.DivisionFactor).ToString();
            // }
            // else
            // {
            //    guiradlblreportpwvdistancedisplay.Text = guiradlblreportpwvdistancedisplay1.Text = obj.calculatedDistance.ToString();
            // }

            // guiradlblReportPwvDistanceMethodType.Text = obj.myCarotidDistance.distance.Equals(GuiConstants.DefaultValue) ? oMsgMgr.GetMessage(CrxStructCommonResourceMsg.ReportLblDirect) : oMsgMgr.GetMessage(CrxStructCommonResourceMsg.ReportLblSubtracting);
            // guiradlblReportPwvDitanceUnits.Text = guiradlblReportPwvDitanceUnits1.Text = crxMgrObject.PwvSettings.PWVDistanceUnits.Equals(0) ? oMsgMgr.GetMessage(CrxStructCommonResourceMsg.Mm) : oMsgMgr.GetMessage(CrxStructCommonResourceMsg.Cm);

            // Commenting the below code as group name is not included in Clinical mode.
            // guiradlblReportBmiValue.Text = obj.heightAndWeight.bodyMassIndex.Equals(GuiConstants.DefaultValue) ? string.Empty : obj.heightAndWeight.bodyMassIndex.ToString();
            guiradlblReportOperatordisplay.Text = guiradtxtReportOperator.Text = obj.operatorId;

            // guiradlblReportNotesDisplay.Text = guiradtxtReportNotes.Text = obj.notes;

            //// Since AutoEllipsis propert works only on singleline we are using code to check maximum length for label
            // if (guiradlblReportNotesDisplay.Text.Length > LblReportNotesDisplayMaximumLength)
            // {
            //    guiradlblReportNotesDisplay.Text = guiradlblReportNotesDisplay.Text.Substring(0, LblReportNotesDisplayMaximumLength - 3);
            //    guiradlblReportNotesDisplay.Text = string.Format("{0}...", guiradlblReportNotesDisplay.Text);
            // }

            // set display text for SP, DP & MP labels
            // SetBloodPressureDisplayText();

            // calculates height & weight
            int heightInInches;
            int heigthInFeet;

            guiradlblReportHeightDisplay.Text = string.Empty;
            guiradlblReportHeightInches.Text = string.Empty;

            // Commenting the below code as group name is not included in Clinical mode.
            // guiradlblReportWeightdisplay.Text = string.Empty;
            switch (crxMgrObject.GeneralSettings.HeightandWeightUnit)
            {
                case (int)CrxGenPwvValue.CrxGenHeightWeightMetric:
                    guiradlblReportHeightDisplay.Text = obj.heightAndWeight.heightInCentimetres.Equals(GuiConstants.DefaultValue) ? string.Empty : obj.heightAndWeight.heightInCentimetres.ToString();

                    // guiradlblReportWeightUnits.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.Kg);
                    guiradlblReportHeightUnits.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.Cm);

                    // guiradlblReportWeightdisplay.Text = obj.heightAndWeight.weightInKilograms.Equals(GuiConstants.DefaultValue) ? string.Empty : obj.heightAndWeight.weightInKilograms.ToString();                                     
                    break;
                case (int)CrxGenPwvValue.CrxGenHeightWeightImperial:
                    if (obj.heightAndWeight.heightInInches != GuiConstants.DefaultValue)
                    {
                        // convert height in inches to feet & inches
                        heightInInches = int.Parse(obj.heightAndWeight.heightInInches.ToString()) % 12;
                        heigthInFeet = int.Parse(obj.heightAndWeight.heightInInches.ToString()) / 12;

                        guiradlblReportHeightDisplay.Text = heigthInFeet.ToString();
                        guiradlblReportHeightInches.Text = heightInInches.ToString();
                    }

                    // Commenting the below code as group name is not included in Clinical mode.
                    // guiradlblReportWeightdisplay.Text = obj.heightAndWeight.weightInPounds.Equals(GuiConstants.DefaultValue) ? string.Empty : obj.heightAndWeight.weightInPounds.ToString();

                    // guiradlblReportWeightUnits.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.Lbs);
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
        void InitializeCrxOnLoad(string studydatetime)
        {
            try
            {
                PopulateBizFromCrx(studydatetime);
            }
            catch (Exception ex)
            {
                GUIExceptionHandler.HandleException(ex, this);
            }
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

        /** This method popluates bizsession object based on single record selected for assessment
         * It fetches value based on datetime of assessment
         * */
        private void PopulateBizFromCrx(string studyDateTime)
        {
            DataSet dsPWV;

            try
            {
                // check db connection
                if (dbMagr.CheckConnection(serverNameString, crxMgrObject.GeneralSettings.SourceData) == 0)
                {
                    if (string.IsNullOrEmpty(studyDateTime))
                    {
                        dsPWV = dbMagr.GetPWVMeasurementDetails(int.Parse(patientObj.patientNumber.ToString()), int.Parse(patientObj.groupStudyId.ToString()), bobj);
                    }
                    else
                    {
                        // this will be called when other assessment is selected from assessment grid
                        GuiCommon.PwvCurrentStudyDatetime = studyDateTime;
                        CrxStructPWVMeasurementData cdata = new CrxStructPWVMeasurementData
                        {
                            StudyDateTime = DateTime.Parse(studyDateTime, CrxCommon.gCI),
                            SystemIdentifier = bobj,
                            PatientNumberInternal =
                                GuiCommon.PatientInternalNumber,
                            GroupIdentifier = GuiCommon.GroupId
                        };
                        CrxLogger.Instance.Write("GuiCommon.PwvCurrentStudyDatetime: PopulateBizFromCrx" + GuiCommon.PwvCurrentStudyDatetime.ToString());
                        dsPWV = dbMagr.GetPWVMeasurementDetails(cdata);
                    }

                    if (dsPWV.Tables[0].Rows.Count > 0)
                    {
                        crxPWV.StudyDateTime = DateTime.Parse(dsPWV.Tables[0].Rows[0][(int)CrxDBPWVMeasurementTableList.StudyDateTime].ToString(), CrxCommon.gCI);

                        // guiradlblReportDateTimeDisplay.Text = dsPWV.Tables[0].Rows[0][(int)CrxDBPWVMeasurementTableList.StudyDateTime].ToString();
                        GuiCommon.PwvCurrentStudyDatetime = dsPWV.Tables[0].Rows[0][(int)CrxDBPWVMeasurementTableList.StudyDateTime].ToString();
                        CrxLogger.Instance.Write("crxPWV.StudyDateTime:(PopulateBizFromCrx) " + crxPWV.StudyDateTime);
                        byte[] buffer = (byte[])dsPWV.Tables[0].Rows[0][(int)CrxDBPWVMeasurementTableList.NormalRange];

                        int len = buffer.Length / 4;

                        crxPWV.NormalRange = dbMagr.CommonByteArrtoFloatArr(len, buffer);

                        buffer = (byte[])dsPWV.Tables[0].Rows[0][(int)CrxDBPWVMeasurementTableList.ReferenceRange];
                        len = buffer.Length / 4;
                        crxPWV.ReferenceRange = dbMagr.CommonByteArrtoFloatArr(len, buffer);

                        buffer = (byte[])dsPWV.Tables[0].Rows[0][(int)CrxDBPWVMeasurementTableList.CarotidSignal];
                        len = buffer.Length / 2;
                        crxPWV.CarotidSignal = dbMagr.CommonByteArrtoShortArr(len, buffer);
                        crxPWV.CarotidSignalLength = (short)len;

                        buffer = (byte[])dsPWV.Tables[0].Rows[0][(int)CrxDBPWVMeasurementTableList.FemoralSignal];
                        len = buffer.Length / 2;
                        crxPWV.FemoralSignal = dbMagr.CommonByteArrtoShortArr(len, buffer);
                        crxPWV.FemoralSignalLength = (short)len;

                        buffer = (byte[])dsPWV.Tables[0].Rows[0][(int)CrxDBPWVMeasurementTableList.CarotidSignalFloatOnSets];
                        len = buffer.Length / 4;
                        crxPWV.CarotidSignalFloatOnSets = dbMagr.CommonByteArrtoFloatArr(len, buffer);
                        crxPWV.CarotidSignalOnSetsLength = (short)len;

                        buffer = (byte[])dsPWV.Tables[0].Rows[0][(int)CrxDBPWVMeasurementTableList.FemoralSignalFloatOnSets];
                        len = buffer.Length / 4;
                        crxPWV.FemoralSignalFloatOnSets = dbMagr.CommonByteArrtoFloatArr(len, buffer);
                        crxPWV.FemoralSignalOnSetsLength = (short)len;

                        // populating height, weight, blood pressure & distance values
                        // PopulateCrxWithOtherValues(dsPWV);

                        // populating other details i.e statistcis information
                        // PopulateCrxWithStatistics(dsPWV);
                        // obj.Populate(crxPWV);
                        // obj.Validate();
                    }
                }
                else
                {
                    DialogResult result = RadMessageBox.Show(this, GuiCommon.ConnectionErrorString(), oMsgMgr.GetMessage(CrxStructCommonResourceMsg.SystemError), MessageBoxButtons.RetryCancel, RadMessageIcon.Error);
                    if (result == DialogResult.Retry)
                    {
                        PopulateBizFromCrx(studyDateTime);
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
                // Commenting the below code as group name is not used anymore in Clinical environment.
                // guilblReportGroupValue.Text = string.Empty;
                guiradlblReportPatientName.Text = string.Empty;
                guilblReportPatientIdValue.Text = string.Empty;
                guilblReportDobValue.Text = string.Empty;
                guilblReportAgeValue.Text = string.Empty;
                guilblReportGenderValue.Text = string.Empty;

                // Commenting the below code as group name is not used anymore in Clinical environment.
                // guilblReportGroupValue.Text = GuiCommon.GroupName;
                guiradlblReportPatientName.Text = string.IsNullOrEmpty(patientObj.firstName) ? patientObj.lastName : patientObj.firstName + "  " + patientObj.lastName;
                guilblReportPatientIdValue.Text = patientObj.patientId;
                guilblReportDobValue.Text = patientObj.dateOfBirth.ToString(oMsgMgr.GetMessage(CrxStructCommonResourceMsg.ReportDateTimeFormat));
                guilblReportAgeValue.Text = obj.patientAge.ToString();
                guilblReportGenderValue.Text = patientObj.gender;
                ReportPWVDisplayMode(true);
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
                guiradgridReportAssessment.Columns[1].SortOrder = RadSortOrder.Ascending;
                guiradgridReportAssessment.GridElement.AlternatingRowColor = Color.LightGray;
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

            obj.CalculateAge();
            objDefaultWindow.radlblMessage.Text = string.Empty;

            // guiradlblReportDateTimeDisplay.Visible = false;
        }

        private void guiradbtnreportedit_Click_1(object sender, EventArgs e)
        {
            // edit mode            
            // Show edit mode in the status bar.
            // objDefaultWindow.radlblMessage.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.EditMode);
            ReportPWVDisplayMode(false);

            // populates PWV measurement fields as per Settings from config manager
            // guiradlblReportCuffUnits.Text = guiradlblReportFemoralCuffUnits.Text = guiradlblCarotidUnits.Text = crxMgrObject.PwvSettings.PWVDistanceUnits.Equals(0) ? oMsgMgr.GetMessage(CrxStructCommonResourceMsg.Mm) : oMsgMgr.GetMessage(CrxStructCommonResourceMsg.Cm);
            ushort tempVal = obj.myFemoral2CuffDistance.distance;

            // guiradtxtReportFemoToCuff.Text = crxMgrObject.PwvSettings.PWVDistanceUnits.Equals((int)CrxGenPwvValue.CrxPwvDistDistUnitsCM) ? (tempVal / GuiConstants.DivisionFactor).ToString() : tempVal.ToString();

            // SetPwvDistanceFieldForEditing();

            // set height & weight details
            guiradtxtReportHeight.Text = guiradlblReportHeightDisplay.Text;
            guiradtxtReportHeightInches.Text = guiradlblReportHeightInches.Text;

            // Commenting the below code as group name is not included in Clinical mode.
            // guiradtxtReportWeight.Text = guiradlblReportWeightdisplay.Text;
            // guiradtxtReportOperator.Text = guiradlblReportOperatordisplay.Text;
            // guiradtxtReportNotes.Text = guiradlblReportNotesDisplay.Text;
            // SetBloodPressureDataForEditing();

            // in edit mode disable repeat & capture buttons
            guiradbtnRepeat.Enabled = false;
            objDefaultWindow.radtabCapture.Enabled = false;

            GuiCommon.IsFormChanged = false;
        }

        /** This method displays PWV measurement section in display & edit mode
        */
        private void ReportPWVDisplayMode(bool value)
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

                guiradtxtReportHeight.Visible = false;

                guiradtxtReportOperator.Visible = false;

                // Commenting the below code as group name is not included in Clinical mode.
                guiradlblreportSPdisplay.BringToFront();
                guiradlblReportBloodPressure2.BringToFront();
                guiradlblReportBloodPressure3.BringToFront();
                guiradlblReportOperatordisplay.BringToFront();
                guiradlblReportHeightDisplay.BringToFront();

                // Commenting the below code as group name is not included in Clinical mode.
                // guiradlblReportWeightdisplay.BringToFront();
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

                // edit PWV details (show text boxes)
                // Commenting the below code as group name is not included in Clinical mode.
                // guiradtxtReportWeight.Visible = true;
                guiradtxtReportHeight.Visible = true;

                guiradtxtReportOperator.Visible = true;

                guiradtxtReportBloodPressure1.Visible = true;
                guiradtxtReportBloodPressure2.Visible = true;
                guiradtxtReportBloodPressure3.Visible = true;

                guiradtxtReportBloodPressure1.Focus();

                guiradlblreportSPdisplay.SendToBack();
                guiradlblReportBloodPressure2.SendToBack();
                guiradlblReportBloodPressure3.SendToBack();
                guiradlblReportOperatordisplay.SendToBack();
                guiradlblReportHeightDisplay.SendToBack();

                // Commenting the below code as group name is not included in Clinical mode.
                // guiradlblReportWeightdisplay.SendToBack();
                // guiradlblReportBmiValue.SendToBack();
                guiradtxtReportBloodPressure1.BringToFront();

                // Commenting the below code as group name is not included in Clinical mode.
                // guiradtxtReportWeight.BringToFront();
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
        }

        /** This method brings report screen left side measurement details section in display mode
        * It hides cancel & save button & unhides edit button
        * */
        private void SetPWADsiplayMode()
        {
            GuiCommon.IsFormChanged = false;
            objDefaultWindow.radlblMessage.Text = string.Empty;

            // cancels editing PWV details
            ReportPWVDisplayMode(true);

            guiradbtnreportcancel.Visible = false;
            guiradbtnreportedit.Visible = true;
            guiradbtnreportsave.Visible = false;
            guiradbtnPrint.Enabled = true;
            guiradbtnreportedit.Focus();

            // sets blood pressure display text in labels
            // SetBloodPressureDisplayText();

            // CheckLastAssessmentSelected(dateToCompare);
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
            dateWithComma = string.Empty;
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
                    dateWithComma += DateTime.Parse(row.Cells[1].Value.ToString()).ToString(CulturalNeutralDateFormat) + oMsgMgr.GetMessage(CrxStructCommonResourceMsg.GuiDisplayComma);
                }
            }

            GuiConstants.DateWithComma = dateWithComma;
            recordsToDelete = recordSelected;

            // below line of code will keep focus on current record selection in assessment grid
            guiradgridReportAssessment.MasterTemplate.EndUpdate(new DataViewChangedEventArgs(ViewChangedAction.DataChanged));
            guiradgridReportAssessment.MasterTemplate.SynchronizationService.AddListener(navigatorListener);

            // guiradchkAssesments.Enabled = guiradgridReportAssessment.Rows.Count == 1 ? false : true;

            // display analysis / report screen based on records selected
            DisplayReportOnSelection(recordSelected, dateWithComma);
        }

        private void DisplayReportOnSelection(int recordSelected, string datetime)
        {           
            dateToCompare = string.Empty;

            // check assessment checkbox if all assessments are selected in grid
            if (recordSelected == guiradgridReportAssessment.Rows.Count)
            {
                guiradbtnDelete.Enabled = true;

                if (recordSelected == 1)
                {
                    dateToCompare = datetime.Replace(oMsgMgr.GetMessage(CrxStructCommonResourceMsg.GuiDisplayComma), string.Empty);
                }

                guipnlPWAReportAnalysis.Visible = true;
                guipnlPWAReport.Visible = false;

                // PlotAnalysisTrendCharts(datetime);
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

                dateToCompare = datetime.Replace(oMsgMgr.GetMessage(CrxStructCommonResourceMsg.GuiDisplayComma), string.Empty);
                guiradbtnreportedit.Enabled = true;

                // CheckLastAssessmentSelected(dateToCompare);

                // when record selected is only one display record as per assessment selected
                // DisplayReportForSelectedAssesment(dateToCompare);
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
                // ReportPWVDisplayMode(true);
                // PlotAnalysisTrendCharts(datetime);
                objDefaultWindow.radtabReport.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.TabAnalysis);
            }
            else if (recordSelected == 0)
            {
                EnableDisableReportPrintButton(true);

                // disable delete & edit button when no record is selected
                guiradbtnDelete.Enabled = false;
                guiradbtnreportedit.Enabled = false;

                // CheckLastAssessmentSelected(string.Empty);
            }
            else
            {
                EnableDisableReportPrintButton(true);

                // for any other condition besides above, show report screen & enable capture & repeat buttons
                guiradbtnreportedit.Enabled = false;
                guipnlPWAReportAnalysis.Visible = false;
                if (!GuiCommon.IsWaitIntervalImposed)
                {
                    guiradbtnRepeat.Enabled = true;
                    objDefaultWindow.radtabCapture.Enabled = true;
                }

                objDefaultWindow.radtabReport.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.TabReport);
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

            // if value is false then show Analysis Print button.
            // To see patient analysis report,disable and send back the report print button and
            // at the same time enable and bring in front the Analysis print button.
            else
            {
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
            guiradAnalysisChartSphygmocorRefAge.Update();
            guiradAnalysisChartAP.Update();
        }

        private void guiradAnalysisChartHR_DoubleClick(object sender, EventArgs e)
        {           
            RenderEnlargedChart(guiradAnalysisChartHR);

            guiradAnalysisChartSP.Update();
            guiradAnalysisChartPP.Update();
            guiradAnalysisChartDPMP.Update();
            guiradAnalysisChartSphygmocorRefAge.Update();
            guiradAnalysisChartAP.Update();
        }

        private void guiradAnalysisChartSP_DoubleClick(object sender, EventArgs e)
        {           
            RenderEnlargedChart(guiradAnalysisChartSP);

            guiradAnalysisChartHR.Update();
            guiradAnalysisChartPP.Update();
            guiradAnalysisChartDPMP.Update();
            guiradAnalysisChartSphygmocorRefAge.Update();
            guiradAnalysisChartAP.Update();
        }

        private void guiradAnalysisChartSphygmocorRefAge_DoubleClick(object sender, EventArgs e)
        {           
            RenderEnlargedChart(guiradAnalysisChartSphygmocorRefAge);

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
            guiradAnalysisChartSphygmocorRefAge.Update();
            guiradAnalysisChartSP.Update();
        }

        private void guiradAnalysisChartPP_DoubleClick(object sender, EventArgs e)
        {            
            RenderEnlargedChart(guiradAnalysisChartPP);
            guiradAnalysisChartHR.Update();
            guiradAnalysisChartAP.Update();
            guiradAnalysisChartDPMP.Update();
            guiradAnalysisChartSphygmocorRefAge.Update();
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

            guiradAnalysisChartSphygmocorRefAge.BorderlineColor = Color.White;
            guiradAnalysisChartSphygmocorRefAge.BorderlineDashStyle = ChartDashStyle.Solid;
            guiradAnalysisChartSphygmocorRefAge.BorderlineWidth = 1;
            guiradAnalysisChartSphygmocorRefAge.BorderSkin.SkinStyle = BorderSkinStyle.None;
            guiradAnalysisChartSphygmocorRefAge.BorderSkin.BackColor = Color.Gray;
            guiradAnalysisChartSphygmocorRefAge.BorderSkin.BackGradientStyle = GradientStyle.None;
            guiradAnalysisChartSphygmocorRefAge.BorderSkin.BackHatchStyle = ChartHatchStyle.None;
            guiradAnalysisChartSphygmocorRefAge.BorderSkin.BorderColor = Color.Black;
            guiradAnalysisChartSphygmocorRefAge.BorderSkin.BorderDashStyle = ChartDashStyle.NotSet;
            guiradAnalysisChartSphygmocorRefAge.BorderSkin.BorderWidth = 1;
            guiradAnalysisChartSphygmocorRefAge.BorderSkin.PageColor = Color.White;
            guiradAnalysisChartSphygmocorRefAge.BringToFront();

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
            guiradAnalysisChartSphygmocorRefAge.Update();
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
            smallChart.BorderSkin.PageColor = Color.FromArgb((142), (150), (186));
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

        /**This method is used to show the Aix tracker on the PWA Report screen, depending upon its value.
         */ 
        private void ShowAixTracker()
        {
            // AIx Tracker: Begin
            int maxValue = 26;
            int minValue = -8;
            int value = 22;
            int goodRangeMin = -2;
            int goodRangeMax = 20;

            guilblAIxValue.Left = guilblAIxSlider.Left + (int)((value - minValue) * (guilblAIxSlider.Width / (maxValue - minValue)));

            guilblAIxGoodMinText.Left = guilblAIxGoodMin.Left = guilblAIxSlider.Left + (int)((goodRangeMin - minValue) * (guilblAIxSlider.Width / (maxValue - minValue)));
            guilblAIxGoodMax.Left = guilblAIxSlider.Left + (int)((goodRangeMax - minValue) * (guilblAIxSlider.Width / (maxValue - minValue)));

            guilblAIxValueText.Left = guilblAIxValue.Left - (guilblAIxValueText.Width / 3) - 1;
            guilblAIxGoodMaxText.Left = guilblAIxGoodMax.Left - (guilblAIxGoodMaxText.Width / 3);
            guilblAIxGoodMinText.Left = guilblAIxGoodMin.Left - (guilblAIxGoodMinText.Width / 3);

            guilblAIxValueText.Text = value.ToString();
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
        private void ShowSpTracker()
        {
            // SP Tracker: Begin
            int spMaxValue = 130;
            int spMinValue = 90;
            int spValue = 105;
            int spGoodRangeMin = 96;
            int spGoodRangeMax = 120;

            guilblSPValue.Left = guilblSPSlider.Left + (spValue - spMinValue) * (guilblSPSlider.Width / (spMaxValue - spMinValue));

            guilblSPGoodMinText.Left = guilblSPGoodMin.Left = guilblSPSlider.Left + (spGoodRangeMin - spMinValue) * (guilblSPSlider.Width / (spMaxValue - spMinValue));
            guilblSPGoodMax.Left = guilblSPSlider.Left + (spGoodRangeMax - spMinValue) * (guilblSPSlider.Width / (spMaxValue - spMinValue));

            guilblSPValueText.Left = guilblSPValue.Left - (guilblSPValueText.Width / 3) - 2;
            guilblSPGoodMaxText.Left = guilblSPGoodMax.Left - (guilblSPGoodMaxText.Width / 3);
            guilblSPGoodMinText.Left = guilblSPGoodMin.Left - (guilblSPGoodMinText.Width / 3);

            guilblSPValueText.Text = spValue.ToString();
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
        private void ShowPpTracker()
        {
            // PP Tracker: Begin
            int ppMaxValue = 25;
            int ppMinValue = 0;
            int ppValue = 23;
            int ppGoodRangeMin = 5;
            int ppGoodRangeMax = 20;

            guilblPPValue.Left = guilblPPSlider.Left + (ppValue - ppMinValue) * (guilblPPSlider.Width / (ppMaxValue - ppMinValue));

            guilblPPGoodMinText.Left = guilblPPGoodMin.Left = guilblPPSlider.Left + (ppGoodRangeMin - ppMinValue) * (guilblPPSlider.Width / (ppMaxValue - ppMinValue));
            guilblPPGoodMax.Left = guilblPPSlider.Left + (ppGoodRangeMax - ppMinValue) * (guilblPPSlider.Width / (ppMaxValue - ppMinValue));

            guilblPPValueText.Left = guilblPPValue.Left - (guilblPPValueText.Width / 3) + 1;
            guilblPPGoodMaxText.Left = guilblPPGoodMax.Left - (guilblPPGoodMaxText.Width / 3);
            guilblPPGoodMinText.Left = guilblPPGoodMin.Left - (guilblPPGoodMinText.Width / 3);

            guilblPPValueText.Text = ppValue.ToString();
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
        private void ShowApTracker()
        {
            // AP Tracker: Begin
            int apMaxValue = 12;
            int apMinValue = -6;
            int apValue = 4;
            int apGoodRangeMin = -3;
            int apGoodRangeMax = 9;

            guilblAPValue.Left = guilblAPSlider.Left + (apValue - apMinValue) * (guilblAPSlider.Width / (apMaxValue - apMinValue));

            guilblAPGoodMinText.Left = guilblAPGoodMin.Left = guilblAPSlider.Left + (apGoodRangeMin - apMinValue) * (guilblAPSlider.Width / (apMaxValue - apMinValue));
            guilblAPGoodMax.Left = guilblAPSlider.Left + (apGoodRangeMax - apMinValue) * (guilblAPSlider.Width / (apMaxValue - apMinValue));

            guilblAPValueText.Left = guilblAPValue.Left - (guilblAPValueText.Width / 3) + 3;
            guilblAPGoodMaxText.Left = guilblAPGoodMax.Left - (guilblAPGoodMaxText.Width / 3);
            guilblAPGoodMinText.Left = guilblAPGoodMin.Left - (guilblAPGoodMinText.Width / 3);

            guilblAPValueText.Text = apValue.ToString();
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
        private void ShowReferenceAgeTracker()
        {
            // Sphygmocor Reference Age Tracker: Begin
            int refAgeMaxValue = 80;
            int refAgeMinValue = 20;
            int refAgeValue = 60;
            int scale20 = 20;
            int scale30 = 30;
            int scale40 = 40;
            int scale50 = 50;
            int scale60 = 60;
            int scale70 = 70;
            int scale80 = 80;

            guilblRefAgeValue.Left = guilblRefAgeSlider.Left + (refAgeValue - refAgeMinValue) * (guilblRefAgeSlider.Width / (refAgeMaxValue - refAgeMinValue));
            guilblRefAgeValueText.Left = guilblRefAgeValue.Left - (guilblRefAgeValueText.Width / 3);
            guilblRefAgeValueText.Text = refAgeValue.ToString();

            guilblRefAgeValueMark1.Left = guilblRefAgeSlider.Left + (scale20 - refAgeMinValue) * (guilblRefAgeSlider.Width / (refAgeMaxValue - refAgeMinValue));
            guilblRefAgeValueMark1Text.Left = guilblRefAgeValueMark1.Left - (guilblRefAgeValueMark1.Width / 3) - 4;
            guilblRefAgeValueMark2.Left = guilblRefAgeSlider.Left + (scale30 - refAgeMinValue) * (guilblRefAgeSlider.Width / (refAgeMaxValue - refAgeMinValue));
            guilblRefAgeValueMark2Text.Left = guilblRefAgeValueMark2.Left - (guilblRefAgeValueMark2.Width / 3) - 4;
            guilblRefAgeValueMark3.Left = guilblRefAgeSlider.Left + (scale40 - refAgeMinValue) * (guilblRefAgeSlider.Width / (refAgeMaxValue - refAgeMinValue));
            guilblRefAgeValueMark3Text.Left = guilblRefAgeValueMark3.Left - (guilblRefAgeValueMark3.Width / 3) - 4;
            guilblRefAgeValueMark4.Left = guilblRefAgeSlider.Left + (scale50 - refAgeMinValue) * (guilblRefAgeSlider.Width / (refAgeMaxValue - refAgeMinValue));
            guilblRefAgeValueMark4Text.Left = guilblRefAgeValueMark4.Left - (guilblRefAgeValueMark4.Width / 3) - 4;
            guilblRefAgeValueMark5.Left = guilblRefAgeSlider.Left + (scale60 - refAgeMinValue) * (guilblRefAgeSlider.Width / (refAgeMaxValue - refAgeMinValue));
            guilblRefAgeValueMark5Text.Left = guilblRefAgeValueMark5.Left - (guilblRefAgeValueMark5.Width / 3) - 4;
            guilblRefAgeValueMark6.Left = guilblRefAgeSlider.Left + (scale70 - refAgeMinValue) * (guilblRefAgeSlider.Width / (refAgeMaxValue - refAgeMinValue));
            guilblRefAgeValueMark6Text.Left = guilblRefAgeValueMark6.Left - (guilblRefAgeValueMark6.Width / 3) - 4;
            guilblRefAgeValueMark7.Left = guilblRefAgeSlider.Left + (scale80 - refAgeMinValue) * (guilblRefAgeSlider.Width / (refAgeMaxValue - refAgeMinValue));
            guilblRefAgeValueMark7Text.Left = guilblRefAgeValueMark7.Left - (guilblRefAgeValueMark7.Width / 3) - 4;

            // Sphygmocor Reference Age Tracker: End   
        }
    }
}
