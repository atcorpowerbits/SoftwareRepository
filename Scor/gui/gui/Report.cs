/*
     Copyright (C) ATCOR MEDICAL PTY LTD, 2010
 
     Filename     :     Settings Window
        
     Author       :     Nitesh Chhedda
 
     Description  :     Functionality implemented for Report tab.
*/

using System;
using System.Collections.Generic;
using System.Data;
using System.Drawing;
using System.Windows.Forms;
using Telerik.WinControls;
using Telerik.WinControls.UI;
using AtCor.Scor.CrossCutting.Configuration;
using AtCor.Scor.CrossCutting.Logging;
using AtCor.Scor.CrossCutting.DatabaseManager;
using AtCor.Scor.CrossCutting.Messaging;
using AtCor.Scor.DataAccess;
using Telerik.WinControls.Enumerations;
using AtCor.Scor.BusinessLogic;
using System.Windows.Forms.DataVisualization.Charting;
using System.Collections;
using System.Configuration;
using System.Text;

namespace AtCor.Scor.Gui.Presentation
{
    public partial class Report : RadForm
    {
        // Events
        public delegate void InitializationMessage(string message);
        
        public static event EventHandler OnPwvMeasurementChangedEvent;

        const int MaxLabelYValue = 12;  // this denotes the maximum number of values to be displayed on Y axis so that it does not overlap
        const int XInterval = 10; // this variable denotes the number by which x label interval would be calculated
        const double ChartAreaMinimumY = 0.96;
        const double ChartAreaMaximumY = 1.04;
        const int SysId = 31256; // system identifier
        const ushort DefaultValue = 9999;
        const short SdefaultValue = 9999;

       // public static event EventHandler StartWaiting;
        Series tonometerSeries;
        Series femoralSeries;
        Series tonometerOnsetSeries;
        Series tonometerOnsetSeries2;
        Series femoralOnsetSeries;
        Series femoralOnsetSeries2;
        Series normalRangeSeries;
        Series normalRangeSeries2;
        Series referenceRangeSeries;
        Series referenceRangeSeries2;
        Series pWVline;
        Series heartline;
        Series heartPoint;
        Series pWvPoint;

        CrxMessagingManager oMsgMgr;
        CrxConfigManager crxMgrObject;
        CrxDBManager dbMagr;
        BizPWV obj;
        BizPatient patientObj = BizPatient.Instance();
        CrxStructPWVMeasurementData crxPWV = new CrxStructPWVMeasurementData();

        int bobj;

        string serverNameString = string.Empty;
        string dateWithComma = string.Empty; // used to get comma separated date string to delete assessment
        string dateToCompare = string.Empty; // used to compare dates when 30 sec wait interval is imposed to enable / disable repeat button based on last record selected
        int recordsToDelete; 
        private DefaultWindow objDefaultWindow;
        bool oneRecordSelect = true;

        string[] date;
        string[] heartRate;
        string[] pWV;
        string[] isStdDeviationValid;
        int[] xCoordinate = null; // array of x coordinates to display data to the closest datapoint

        string lastAssessmentsDataTime = string.Empty;
        int pwvRecords;
        int labelInterval;
        readonly Font labelFontMax = new Font("Microsoft Sans Serif", 10);  // sets font max size for analysis chart x axis labels
        readonly Font labelFontMin = new Font("Microsoft Sans Serif", 6); // sets font min size for analysis chart x axis labels
        enum ChartName {Pwv, HeartRate};
        string chartSelected = string.Empty;
        
        /**Constructor of the form,initializes all the controls.
       * */
        public Report()
        {
           InitializeComponent();
           
           // subscribe for form changes
           SubscribeReportFormChanges();
           InitializeReportScreen();
           SetTextForReportScreen();

           // initialize servername string
           serverNameString = SettingsProperties.ServerNameString();
           obj = (BizPWV)BizSession.Instance().measurement;

            // subscribe to events
           DefaultWindow.OnReportTabClick += new EventHandler(Report_Load);
           Presentation.Capture.OnReportTabClick += new EventHandler(Report_Load);
           SettingsProperties.OnCaptureClosing += new SettingsProperties.SetCaptureTabVisibility(EnableRepeatAndCaptureTab);
        }

        /** Parameterized Constructor of the form,initializes all the controls.
      * */
        public Report(DefaultWindow defWindow)
        {
            try
            {                   
                InitializeComponent();

                // subscribe for form changes
                SubscribeReportFormChanges();
                InitializeReportScreen();
                
                // set the default window
                objDefaultWindow = defWindow;
                SetTextForReportScreen();

                // initialize servername string
                serverNameString = SettingsProperties.ServerNameString();
                obj = (BizPWV)BizSession.Instance().measurement;

                // subscribe report tab click event
                DefaultWindow.OnReportTabClick += new EventHandler(Report_Load);
                Presentation.Capture.OnReportTabClick += new EventHandler(Report_Load);
                SettingsProperties.OnCaptureClosing += new SettingsProperties.SetCaptureTabVisibility(EnableRepeatAndCaptureTab);
            }
            catch (Exception ex)
            {
                GUIExceptionHandler.HandleException(ex, this);
            }            
        }       

        /** This method initializes crx objects & chart series
         * */
        public void InitializeReportScreen()
        {
            dbMagr = CrxDBManager.Instance;
            oMsgMgr = CrxMessagingManager.Instance;
            crxMgrObject = CrxConfigManager.Instance;

            crxMgrObject.GetGeneralUserSettings();
            crxMgrObject.GetPwvUserSettings();

            // series names are defined for internal use only
            tonometerSeries = new Series("Tonometer");
            femoralSeries = new Series("Femoral");
            tonometerOnsetSeries = new Series("TonometerOnsetPoints");
            tonometerOnsetSeries2 = new Series("TonometerOnsetPoints2");
            femoralOnsetSeries = new Series("FemoralOnsetPoints");
            femoralOnsetSeries2 = new Series("FemoralOnsetPoints2");
            normalRangeSeries = new Series("NormalRange");
            normalRangeSeries2 = new Series("NormalRange2");
            referenceRangeSeries = new Series("ReferenceRange");
            referenceRangeSeries2 = new Series("ReferenceRange2");
            pWVline = new Series("pWVline");
            heartline = new Series("heartLine");
            heartPoint = new Series("heartPoint");
            pWvPoint = new Series("pWVPoint");
        }

        /**This is invoked on the load of report window.
         *fetches & binds report screen data 
         */
        private void Report_Load(object sender, EventArgs e)
        {
            if (InvokeRequired)
            {
                this.Invoke(new EventHandler(Report_Load));
                return;
            }

            bobj = SysId;
            SettingsProperties.CaptureToSetup = false;
            SettingsProperties.SystemIdentifier = bobj;
            SettingsProperties.IsFormChanged = false;
            SettingsProperties.ReportLoadCount++;
            
            // set default text for report tab
            objDefaultWindow.radtabReport.Text = oMsgMgr.GetMessage("TAB_REPORT");

            InitializeReportAssessmentList(this, new EventArgs());

            SetDefaultValuesOnLoad(this, new EventArgs());

            // fill demographic & pwv measurement details & bring the LHS to browse mode
            FillDemographicDetailsReport(this, new EventArgs());

            // initialize crx when user moves from setup to report... call populate method
            InitializeCrxFromSetupToReport(string.Empty); 

            // binds assessment details related to patient
            FillPatientAssessmentDetailsReport();

            CheckWaitIntervalImposed();
        }

         /** This method set default options for buttons on report screen & calculates patients age
         * */
        private void SetDefaultValuesOnLoad(object sender, EventArgs e)
        {
            // make only edit button visible
            guiradbtnreportcancel.Visible = false;
            guiradbtnreportedit.Visible = true;
            guiradbtnreportsave.Visible = false;
            guiradpnlAnalysis.Visible = false;
            objDefaultWindow.radtabReport.Text = oMsgMgr.GetMessage("TAB_REPORT");          
            
            obj.CalculateAge();
            objDefaultWindow.radlblMessage.Text = string.Empty;

            guiradlblReportDateTime.Visible = false;
            guiradlblReportDateTimeDisplay.Visible = false;
        }

        /** Sets text for labels on report scren
         * */
        private void SetTextForReportScreen()
        {
            try
            {
                guiradlblReportPwvDistance.Text = oMsgMgr.GetMessage("LABEL_PWV_DISTANCE");
                guiradchkAssesments.Text = oMsgMgr.GetMessage("LBL_REPORT_ASSESSMENTS");
                guiradlblReportPatientId.Text = oMsgMgr.GetMessage("LBL_PATIENT_ID");
                guiradlblReportPatientName.Text = oMsgMgr.GetMessage("LBL_PATIENT_NAME");
                guiradlblReportGroup.Text = oMsgMgr.GetMessage("LBL_GROUP");
                guiradlblReportDOB.Text = oMsgMgr.GetMessage("LBL_REPORT_DOB");
                guiradlblReportAge.Text = oMsgMgr.GetMessage("LBL_REPORT_AGE");
                guiradlblReportheightWeight.Text = oMsgMgr.GetMessage("LBL_HEIGHT");
                guiradlblReportWeight.Text = oMsgMgr.GetMessage("LBL_WEIGHT");
                guiradlblReportBmi.Text = oMsgMgr.GetMessage("LBL_REPORT_BMI");
                guiradlblReportOperator.Text = oMsgMgr.GetMessage("LBL_OPERATOR");
                guiradlblNotes.Text = oMsgMgr.GetMessage("LBL_NOTES");
                guiradlblReportPwvDistanceMethod.Text = oMsgMgr.GetMessage("LBL_REPORT_PWVMETHOD");
                guiradlblReportPwvDistance1.Text = oMsgMgr.GetMessage("LABEL_PWV_DISTANCE");

                guiradlblReportCarotid.Text = oMsgMgr.GetMessage("LBL_REPORT_CAROTID");
                guiradlblReportFemoral.Text = oMsgMgr.GetMessage("LBL_REPORT_FEMORAL");
                guiradAnalysisChartHeading.Text = oMsgMgr.GetMessage("LBL_REPORT_PWV");
                guiradlbReportNormalRange.Text = oMsgMgr.GetMessage("LBL_REPORT_NORMAL_RANGE");
                guiradlblReportReferenceRange.Text = oMsgMgr.GetMessage("LBL_REPORT_REFERENCE_RANGE");
                guiradlblReportHeartRate.Text = oMsgMgr.GetMessage("LBL_REPORT_HEART_RATE");
                guiradlblReportPulseWaveVelocity.Text = oMsgMgr.GetMessage("LBL_REPORT_PWV");
                radLabel6.Text = oMsgMgr.GetMessage("LBL_REPORT_STD_DEVIATION");
                guiradbtnreportsave.Text = oMsgMgr.GetMessage("BTN_SAVE");
                guiradbtnreportcancel.Text = oMsgMgr.GetMessage("BTN_CANCEL");
                guiradbtnreportedit.Text = oMsgMgr.GetMessage("BTN_EDIT");
                guiradbtnRepeat.Text = oMsgMgr.GetMessage("BTN_REPEAT");
                guiradbtnPrint.Text = oMsgMgr.GetMessage("BTN_PRINT");
                guiradbtnDelete.Text = oMsgMgr.GetMessage("BTN_DELETE");
                guiradlblCarotid.Text = oMsgMgr.GetMessage("LABEL_CAROTID");
                guiradlblReportCuff.Text = oMsgMgr.GetMessage("LABEL_CUFF");
                guiradlblReportFemoToCuff.Text = oMsgMgr.GetMessage("LABEL_FEMORAL_CUFF");               
            }            
            catch (Exception ex)
            {
                GUIExceptionHandler.HandleException(ex, this);
            }
        }

        /** This method enforces wait interval for 30 secs when navigated to report from capture screen
         * */
        private void StartWaitInterval()
        {
            if (!SettingsProperties.SetupToReport)
            {
                // read timer interval from config & start timer to enforce wait interval
                timer1.Interval = int.Parse(ConfigurationManager.AppSettings["WaitInterval"]);
                SettingsProperties.IsWaitIntervalImposed = true;
                timer1.Start();
            }
        }

        /**This method clears all input fields for PWV measurement 
        */
        void ClearReportFields()
        {
            guiradtxtReportHeight.Text = string.Empty;
            guiradtxtReportHeightInches.Text = string.Empty;
            guiradtxtReportWeight.Text = string.Empty;
            guiradtxtReportOperator.Text = string.Empty;
            guiradtxtReportNotes.Text = string.Empty;
            guiradtxtReportBloodPressure1.Text = string.Empty;
            guiradtxtReportBloodPressure2.Text = string.Empty;
            
            guiradtxtReportCuff.Text = string.Empty;
            guiradtxtReportFemoToCuff.Text = string.Empty;
        }

        /**This event fires on edit button click
       */
        private void guiradbtnreportedit_Click(object sender, EventArgs e)
        {
            // edit mode
            // Show edit mode in the status bar.
            objDefaultWindow.radlblMessage.Text = oMsgMgr.GetMessage("EDIT_MODE"); // "Edit Mode";

            // make display panel visible for PWV distance
            guiradpnldisplayPWVDistance.Visible = false;
            guiradpnlEditPWVdistance.Visible = true;

            guiradbtnreportedit.Visible = false;
            guiradbtnreportcancel.Visible = true;
            guiradbtnreportsave.Visible = true;

            ReportPWVDisplayMode(false);

            // populates PWV measurement fields as per Settings from config manager
            guiradlblReportCuffUnits.Text = guiradlblReportFemoralCuffUnits.Text = guiradlblCarotidUnits.Text = crxMgrObject.PwvSettings.PWVDistanceUnits.Equals(0) ? oMsgMgr.GetMessage("MM") : oMsgMgr.GetMessage("CM");
           
            guiradtxtReportFemoToCuff.Text = obj.myFemoral2CuffDistance.distance.ToString();
            SetPwvDistanceFieldForEditing();
            
            // set height & weight details
            guiradtxtReportHeight.Text = guiradlblReportHeightDisplay.Text;
            guiradtxtReportHeightInches.Text = guiradlblReportHeightInches.Text;
            guiradtxtReportWeight.Text = guiradlblReportWeightdisplay.Text;
            guiradtxtReportOperator.Text = guiradlblReportOperatordisplay.Text;
            guiradtxtReportNotes.Text = guiradlblReportNotesDisplay.Text;

            SetBloodPressureDataForEditing();  
          
            // in edit mode disable repeat & capture buttons
            guiradbtnRepeat.Enabled = false;
            objDefaultWindow.radtabCapture.Enabled = false;
        }
        
         /**This method sets Carotid, cuff & femoral to cuff values for editing as per PWV distance method
       */
        void SetPwvDistanceFieldForEditing()
        {
            switch (crxMgrObject.PwvSettings.PWVDistanceMethod)
            {
                case 0:
                    // subtracting
                    // display & populate carotid, cuff & femoral to cuff textboxes
                    guiradlblCarotid.Text = oMsgMgr.GetMessage("LABEL_CAROTID");
                    guiradlblReportCuff.Visible = true;
                    guiradtxtReportCuff.Visible = true;
                    guiradlblReportCuffUnits.Visible = true;
                    guiradlblReportFemoToCuff.Visible = true;
                    guiradtxtReportFemoToCuff.Visible = true;
                    guiradlblCarotid.Visible = true;

                    guiradtxtCarotid.Visible = true;
                    guiradlblCarotidUnits.Visible = true;
                    guiradlblReportFemoralCuffUnits.Visible = true;
                    guiradlblReportPwvDistanceMethodType.Text = oMsgMgr.GetMessage("REPORT_LBL_SUBTRACTING");
                    guiradtxtReportCuff.Text = obj.myCuffDistance.distance.Equals(DefaultValue) ? string.Empty : obj.myCuffDistance.distance.ToString();
                    guiradtxtCarotid.Text = obj.myCarotidDistance.distance.Equals(DefaultValue) ? string.Empty : obj.myCarotidDistance.distance.ToString();
                    break;
                case 1:
                    // direct
                    // display & populate direct & femoral to cuff textboxes
                    guiradlblCarotid.Text = oMsgMgr.GetMessage("LABEL_DIRECT");
                    guiradlblReportCuff.Visible = false;
                    guiradtxtReportCuff.Visible = false;
                    guiradlblReportCuffUnits.Visible = false;
                    guiradlblReportFemoToCuff.Visible = true;
                    guiradtxtReportFemoToCuff.Visible = true;
                    guiradlblCarotid.Visible = true;

                    guiradtxtCarotid.Visible = true;
                    guiradlblCarotidUnits.Visible = true;
                    guiradlblReportFemoralCuffUnits.Visible = true;
                    guiradlblReportPwvDistanceMethodType.Text = oMsgMgr.GetMessage("REPORT_LBL_DIRECT");

                    guiradtxtCarotid.Text = obj.myPWVDirectDistance.distance.Equals(DefaultValue) ? string.Empty : obj.myPWVDirectDistance.distance.ToString();
                    break;
                default:
                    break;
            }
        }

        /**This method sets SP, DP & MP values for editing in textboxes
      */
        void SetBloodPressureDataForEditing()
        {
            // sets SP, DP & MP values as per session & config object
            if (obj.bloodPressureEntryOption != ushort.Parse(crxMgrObject.GeneralSettings.BloodPressureEntryOptions.ToString()))
            {
                switch (crxMgrObject.GeneralSettings.BloodPressureEntryOptions)
                {
                    case 0:
                        // SP & DP
                        guiradlblReportBloodPressure1.Text = oMsgMgr.GetMessage("LABEL_SP"); // used for internal checking while changing settings.
                        guiradlblBloodPressure2.Text = oMsgMgr.GetMessage("LABEL_DP"); // used for internal checking while changing settings.

                        guiradtxtReportBloodPressure1.Text = (obj.bloodPressure.SP == null || obj.bloodPressure.SP.Reading.Equals(DefaultValue)) ? string.Empty : obj.bloodPressure.SP.Reading.ToString();
                        guiradtxtReportBloodPressure2.Text = (obj.bloodPressure.DP == null || obj.bloodPressure.DP.Reading.Equals(DefaultValue)) ? string.Empty : obj.bloodPressure.DP.Reading.ToString();
                        break;
                    case 1:
                        // SP & MP
                        guiradlblReportBloodPressure1.Text = oMsgMgr.GetMessage("LABEL_SP"); // used for internal checking while changing settings.
                        guiradlblBloodPressure2.Text = oMsgMgr.GetMessage("LABEL_MP"); // used for internal checking while changing settings.

                        guiradtxtReportBloodPressure1.Text = (obj.bloodPressure.SP == null || obj.bloodPressure.SP.Reading.Equals(DefaultValue)) ? string.Empty : obj.bloodPressure.SP.Reading.ToString();
                        guiradtxtReportBloodPressure2.Text = (obj.bloodPressure.MP == null || obj.bloodPressure.MP.Reading.Equals(DefaultValue)) ? string.Empty : obj.bloodPressure.MP.Reading.ToString();
                        break;
                    case 2:
                        // MP & DP
                        guiradlblReportBloodPressure1.Text = oMsgMgr.GetMessage("LABEL_MP"); // used for internal checking while changing settings.
                        guiradlblBloodPressure2.Text = oMsgMgr.GetMessage("LABEL_DP"); // used for internal checking while changing settings.

                        guiradtxtReportBloodPressure1.Text = (obj.bloodPressure.MP == null || obj.bloodPressure.MP.Reading.Equals(DefaultValue)) ? string.Empty : obj.bloodPressure.MP.Reading.ToString();
                        guiradtxtReportBloodPressure2.Text = (obj.bloodPressure.DP == null || obj.bloodPressure.DP.Reading.Equals(DefaultValue)) ? string.Empty : obj.bloodPressure.DP.Reading.ToString();
                        break;
                    default :
                        break;
                }
            }
            else
            {
                guiradtxtReportBloodPressure1.Text = guiradlblreportSPdisplay.Text;
                guiradtxtReportBloodPressure2.Text = guiradlblReportBloodPressure2.Text;
            }
        }
       
        /** This event fires on cancel button click
       */
        private void guiradbtnreportcancel_Click(object sender, EventArgs e)
        {
           // call method to bring report screen to display mode
            SetPWVDsiplayMode();
        }

        /** This method brings report screen left side measurement details section in display mode
         * It hides cancel & save button & unhides edit button
         * */
        private void SetPWVDsiplayMode()
        {
            objDefaultWindow.radlblMessage.Text = string.Empty;

            // make display panel visible
            guiradpnldisplayPWVDistance.Visible = true;
            guiradpnlEditPWVdistance.Visible = false;

            // cancels editing PWV details
            ReportPWVDisplayMode(true);
            guiradbtnreportcancel.Visible = false;
            guiradbtnreportedit.Visible = true;
            guiradbtnreportsave.Visible = false;

            // reset PWV distance method type text
            guiradlblReportPwvDistance.Text = oMsgMgr.GetMessage("LABEL_PWV_DISTANCE");
            guiradlblReportPwvDistanceMethodType.Text = obj.myCarotidDistance.distance.Equals(DefaultValue) ? oMsgMgr.GetMessage("REPORT_LBL_DIRECT") : oMsgMgr.GetMessage("REPORT_LBL_SUBTRACTING");
            guiradlblReportPwvDitanceUnits.Text = crxMgrObject.PwvSettings.PWVDistanceUnits.Equals(0) ? oMsgMgr.GetMessage("MM") : oMsgMgr.GetMessage("CM");

            // sets blood pressure display text in labels
            SetBloodPressureDisplayText();

            CheckLastAssessmentSelected(dateToCompare);
        }

        /** This method binds demographic details of patient on report screen
       */
        private void FillDemographicDetailsReport(object sender, EventArgs e)
        {
            try
            {
                // clear patient fields before populating them.
                guilblReportGroupValue.Text = string.Empty;
                guilblReportPatientNameValue.Text = string.Empty;
                guilblReportPatientIdValue.Text = string.Empty;
                guilblReportDobValue.Text = string.Empty;
                guilblReportAgeValue.Text = string.Empty;
                guilblReportGenderValue.Text = string.Empty;

                // fill other details from bizpatient object
                BizPatient patientObj = BizPatient.Instance();

                guilblReportGroupValue.Text = SettingsProperties.GroupName; // patientObj.groupStudyId.ToString();

                StringBuilder checkName = new StringBuilder();
                String tempPatientName;

                tempPatientName = string.IsNullOrEmpty(patientObj.firstName) ? patientObj.lastName : patientObj.firstName + " " + patientObj.lastName;
                checkName.Append(tempPatientName);

                if (checkName.Length > 25)
                {
                    checkName.Remove(22, (checkName.Length - 22));
                    checkName.Append("...");
                }

                guilblReportPatientNameValue.Text = checkName.ToString();       

               
                guilblReportPatientIdValue.Text = patientObj.patientId;
                guilblReportDobValue.Text = patientObj.dateOfBirth.ToString("dd/MM/yyyy"); // used for internal use.
                
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
        private void InitializeReportAssessmentList(object sender, EventArgs e)
        {
            try
            {
                guiradgridReportAssessment.Columns.Clear();
                guiradgridReportAssessment.TableElement.BeginUpdate();
                
                GridViewCheckBoxColumn checkBoxColumn = new GridViewCheckBoxColumn();
                checkBoxColumn.Name = "CheckBox"; // internal use only
                
                guiradgridReportAssessment.Columns.Add(checkBoxColumn);
                guiradgridReportAssessment.Columns[0].IsVisible = true;
                guiradgridReportAssessment.Columns[0].Width = 22;
                guiradgridReportAssessment.Columns[0].ReadOnly = false;
                
                guiradgridReportAssessment.Columns.Add("StudyDateTime", "Study DateTime", "StudyDateTime"); // used for internal use.Not displayed on the GUI
                guiradgridReportAssessment.Columns[1].Width = 275;
                guiradgridReportAssessment.Columns[1].IsVisible = true;
                guiradgridReportAssessment.Columns[1].ReadOnly = true;
                guiradgridReportAssessment.Columns[1].SortOrder = RadSortOrder.Ascending;
                
                guiradgridReportAssessment.TableElement.EndUpdate();
                guiradgridReportAssessment.AutoGenerateColumns = false;
            }
            catch (Exception ex)
            {
                GUIExceptionHandler.HandleException(ex, this);
            }
        }

        /** This method displays PWV measurement section in display & edit mode
       */      
        private void ReportPWVDisplayMode(bool value)
        {
            if (value)
            {
                guiradbtnreportcancel.Visible = false;
                guiradbtnreportedit.Visible = true;
                guiradbtnreportsave.Visible = false;

                // show labels (display PWV details)
                guiradtxtReportWeight.Visible = false;
                guiradlblReportCuff.Visible = false;
                guiradtxtReportCuff.Visible = false;
                guiradlblReportCuffUnits.Visible = false;
                guiradlblReportFemoToCuff.Visible = false;
                guiradtxtReportFemoToCuff.Visible = false;
                guiradlblReportFemoralCuffUnits.Visible = false;
                guiradlblCarotid.Visible = false;
                guiradtxtCarotid.Visible = false;
                guiradlblCarotidUnits.Visible = false;

                guiradtxtReportHeight.Visible = false;
                guiradtxtReportOperator.Visible = false;
                guiradtxtReportBloodPressure1.Visible = false;
                guiradtxtReportBloodPressure1.SendToBack();
                guiradtxtReportBloodPressure2.SendToBack();
                guiradtxtReportOperator.SendToBack();
                guiradtxtReportWeight.SendToBack();
                guiradtxtReportNotes.SendToBack();
                guiradtxtReportHeight.SendToBack();
                guiradlblReportPwvDistance.BringToFront();
                guiradlblReportBloodPressure1.BringToFront();
                guiradlblReportBloodPressure2.BringToFront();
                guiradlblReportOperatordisplay.BringToFront();
                guiradlblReportHeightDisplay.BringToFront();
                guiradlblreportpwvdistancedisplay.BringToFront();

                guiradlblReportWeightdisplay.BringToFront();
                guiradlblReportNotesDisplay.BringToFront();
                               
               switch (crxMgrObject.GeneralSettings.HeightandWeightUnit)
                {
                    case 0: // if metric
                        guiradtxtReportHeightInches.Visible = false;
                        guiradlblheightinchec.Visible = false;
                        guiradlblReportHeightInches.Visible = false;
                        break;

                    case 1: // if Imperial
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

                // edit PWV details (show text boxes)
                guiradtxtReportWeight.Visible = true;

                guiradtxtReportHeight.Visible = true;
                guiradtxtReportOperator.Visible = true;
                guiradtxtReportBloodPressure1.Visible = true;
                guiradlblReportPwvDistance.SendToBack();
                guiradlblReportBloodPressure1.SendToBack();
                guiradlblReportBloodPressure2.SendToBack();
                guiradlblReportOperatordisplay.SendToBack();
                guiradlblReportHeightDisplay.SendToBack();
              
                guiradlblReportWeightdisplay.SendToBack();
                guiradlblReportBmiValue.SendToBack();
                guiradlblReportNotesDisplay.SendToBack();
                guiradlblreportpwvdistancedisplay.SendToBack();
                guiradtxtReportBloodPressure1.BringToFront();
             
                guiradtxtReportWeight.BringToFront();
                guiradtxtReportNotes.BringToFront();
                guiradtxtReportHeight.BringToFront();

                switch (crxMgrObject.GeneralSettings.HeightandWeightUnit)
                {
                    case 0:
                        guiradtxtReportHeightInches.Visible = false;
                        guiradlblheightinchec.Visible = false;
                        guiradlblReportHeightInches.Visible = false;
                        break;

                    case 1:
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
        
        /**This method fill PWV measurement details for a particular patient
        * */
        void FillPWVMeasurementDetailsReport()
        {
            // make display panel visible for PWV distance
            guiradpnldisplayPWVDistance.Visible = true;
            guiradpnlEditPWVdistance.Visible = false;
            
            // create biz session instance & bind details to labels
            guiradlblreportpwvdistancedisplay.Text = guiradlblreportpwvdistancedisplay1.Text = obj.calculatedDistance.ToString();
            
            guiradlblReportPwvDistanceMethodType.Text = obj.myCarotidDistance.distance.Equals(DefaultValue) ? oMsgMgr.GetMessage("REPORT_LBL_DIRECT") : oMsgMgr.GetMessage("REPORT_LBL_SUBTRACTING");
            guiradlblReportPwvDitanceUnits.Text = guiradlblReportPwvDitanceUnits1.Text = crxMgrObject.PwvSettings.PWVDistanceUnits.Equals(0) ? oMsgMgr.GetMessage("MM") : oMsgMgr.GetMessage("CM");

            guiradlblReportBmiValue.Text = obj.heightAndWeight.bodyMassIndex.Equals(DefaultValue) ? string.Empty : obj.heightAndWeight.bodyMassIndex.ToString(); // hard coded as value not available in session

            guiradlblReportOperatordisplay.Text = obj.operatorId;
            guiradlblReportNotesDisplay.Text = obj.notes;

            // set display text for SP, DP & MP labels
            SetBloodPressureDisplayText();

            // calculates height & weight
            int heightInInches;
            int heigthInFeet;

            guiradlblReportHeightDisplay.Text = string.Empty;
            guiradlblReportHeightInches.Text = string.Empty;
            guiradlblReportWeightdisplay.Text = string.Empty;

            switch (crxMgrObject.GeneralSettings.HeightandWeightUnit)
            {
                case 0:

                    // 0.3937007874 metric - in centimeteres
                    //if (obj.heightAndWeight.heightInCentimetres.Equals(DefaultValue)) 
                    //{
                    //    guiradlblReportHeightDisplay.Text = Math.Round(double.Parse(obj.heightAndWeight.heightInInches.ToString()) * 2.54, MidpointRounding.ToEven).ToString(); // convert height in centimeters to feet & inches
                    //}
                    //else
                    //{
                        // convert height in inches to feet & inches
                    
                    guiradlblReportHeightDisplay.Text = obj.heightAndWeight.heightInCentimetres.Equals(DefaultValue) ? string.Empty : obj.heightAndWeight.heightInCentimetres.ToString();
                   
                    //    guiradlblReportHeightInches.Text = obj.heightAndWeight.heightInInches.ToString(); 
                    //}

                    guiradlblReportWeightUnits.Text = oMsgMgr.GetMessage("KG");
                    guiradlblReportHeightUnits.Text = oMsgMgr.GetMessage("CM");
                    
                    // convert weight in pounds to kilograms
                    if (obj.heightAndWeight.weightInKilograms != DefaultValue)
                    {
                        guiradlblReportWeightdisplay.Text = obj.heightAndWeight.weightInKilograms.Equals(DefaultValue) ? string.Empty : obj.heightAndWeight.weightInKilograms.ToString(); 
                    }
                  
                    break;
                case 1:

                    // 0.3937007874 imperial in feets & inches
                    //if (obj.heightAndWeight.heightInInches.Equals(DefaultValue)) 
                    //{
                    //    double value = Math.Round(double.Parse(obj.heightAndWeight.heightInCentimetres.ToString()) * 0.3937007874, MidpointRounding.ToEven);                         // convert height in centimeters to feet & inches
                    //    heightInInches = int.Parse(value.ToString()) % 12;
                    //    heigthInFeet = int.Parse(value.ToString()) / 12;
                    //}
                    //else
                    //{
                    if (obj.heightAndWeight.heightInInches != DefaultValue)
                    {
                        // convert height in inches to feet & inches
                        heightInInches = int.Parse(obj.heightAndWeight.heightInInches.ToString()) % 12;
                        heigthInFeet = int.Parse(obj.heightAndWeight.heightInInches.ToString()) / 12;

                        guiradlblReportHeightDisplay.Text = heigthInFeet.ToString();
                        guiradlblReportHeightInches.Text = heightInInches.ToString();
                    }
                    //}       

                    // 2.20462262 

                    guiradlblReportWeightdisplay.Text = obj.heightAndWeight.weightInPounds.Equals(DefaultValue) ? string.Empty : obj.heightAndWeight.weightInPounds.ToString(); //.Equals(DefaultValue) ? Math.Round(double.Parse(obj.heightAndWeight.weightInKilograms.ToString()) * 2.20462262, MidpointRounding.ToEven).ToString() : obj.heightAndWeight.weightInPounds.ToString();
                                      
                    guiradlblReportWeightUnits.Text = oMsgMgr.GetMessage("LBS");
                    guiradlblReportHeightUnits.Text = oMsgMgr.GetMessage("FEET");
                    break;
                default:
                    break;
            }

            // for binding statistics
            BindPWVStatistics();            
        }

        /**This method repopulated obj with old values after validation fail
     * */
        void RepopulateSessionOnValidationFail()
        {
            // create biz session instance & bind details to labels
            obj.calculatedDistance = ushort.Parse(guiradlblreportpwvdistancedisplay1.Text.Trim());

            obj.heightAndWeight.bodyMassIndex = float.Parse(guiradlblReportBmiValue.Text.Trim());

            obj.operatorId = guiradlblReportOperatordisplay.Text;
            obj.notes = guiradlblReportNotesDisplay.Text;

            // set display text for SP, DP & MP labels
            SetBloodPressureDisplayText();

            // calculates height & weight
            int heightInInches;
            int heigthInFeet;

            switch (crxMgrObject.GeneralSettings.HeightandWeightUnit)
            {
                case 0:

                    // 0.3937007874
                    // convert height in inches to feet & inches
                    guiradlblReportHeightDisplay.Text = obj.heightAndWeight.heightInCentimetres.ToString();
                    guiradlblReportHeightInches.Text = obj.heightAndWeight.heightInInches.ToString();
                
                    // convert weight in pounds to kilograms
                    guiradlblReportWeightdisplay.Text = obj.heightAndWeight.weightInKilograms.Equals(DefaultValue) ? Math.Round(double.Parse(obj.heightAndWeight.weightInPounds.ToString()) * 0.45359237, MidpointRounding.ToEven).ToString() : obj.heightAndWeight.weightInKilograms.ToString();
                    break;

                case 1:

                    // 0.3937007874
                    if (obj.heightAndWeight.heightInInches.Equals(DefaultValue))
                    {
                        double value = Math.Round(double.Parse(obj.heightAndWeight.heightInCentimetres.ToString()) * 0.3937007874, MidpointRounding.ToEven);                         // convert height in centimeters to feet & inches
                        heightInInches = int.Parse(value.ToString()) % 12;
                        heigthInFeet = int.Parse(value.ToString()) / 12;
                    }
                    else
                    {
                        // convert height in inches to feet & inches
                        heightInInches = int.Parse(obj.heightAndWeight.heightInInches.ToString()) % 12;
                        heigthInFeet = int.Parse(obj.heightAndWeight.heightInInches.ToString()) / 12;
                    }

                    guiradlblReportHeightDisplay.Text = heigthInFeet.ToString();
                    guiradlblReportHeightInches.Text = heightInInches.ToString();

                    // 2.20462262 
                    guiradlblReportWeightdisplay.Text = obj.heightAndWeight.weightInPounds.Equals(DefaultValue) ? Math.Round(double.Parse(obj.heightAndWeight.weightInKilograms.ToString()) * 2.20462262, MidpointRounding.ToEven).ToString() : obj.heightAndWeight.weightInPounds.ToString();

                    guiradlblReportWeightUnits.Text = oMsgMgr.GetMessage("LBS");
                    guiradlblReportHeightUnits.Text = oMsgMgr.GetMessage("FEET");
                    break;
                default:
                    break;
            }
            
            // binds statictics information
            BindPWVStatistics();
        }

        /** Binds PWV statistics from db if not available in sesion object
         * */
        void BindPWVStatistics()
        {   
            // #0 will round to largest integer & #0.0 will round to one decimal place
           guiradlblReportHeartRateValue.Text = obj.meanHeartRate.ToString().Equals(DefaultValue.ToString()) ? string.Empty : obj.meanHeartRate.ToString("#0") + " " + oMsgMgr.GetMessage("HEARTRATE_UNIT");
           guiradlblReportPWVValue.Text = obj.meanPulseWaveVelocity.ToString().Equals(DefaultValue.ToString()) ? string.Empty : obj.meanPulseWaveVelocity.ToString("#0.0") + " " + oMsgMgr.GetMessage("PWV_UNIT");
           guiradlblStdDeviationImage.ImageIndex = obj.isStandardDeviationValid ? 1 : 0;
           guiradlblReportFemoralImage.ImageIndex = obj.isFemoralSignalValid ? 1 : 0;
           guiradlblReportCarotidImage.ImageIndex = obj.isCarotidSignalValid ? 1 : 0;            
        }

        /** This method fill statistics in biz session
         * */
        void FillSessionWithStatistics(DataSet dsPwv)
        {
            obj.meanHeartRate = string.IsNullOrEmpty(dsPwv.Tables[0].Rows[0]["MeanHeartRate"].ToString()) ? (float)0 : float.Parse(dsPwv.Tables[0].Rows[0]["MeanHeartRate"].ToString());
            obj.meanPulseWaveVelocity = string.IsNullOrEmpty(dsPwv.Tables[0].Rows[0]["MeanPulseWaveVelocity"].ToString()) ? (float)0 : float.Parse(dsPwv.Tables[0].Rows[0]["MeanPulseWaveVelocity"].ToString());
            obj.isStandardDeviationValid = string.IsNullOrEmpty(dsPwv.Tables[0].Rows[0]["IsStandardDeviationValid"].ToString()) ? false : bool.Parse(dsPwv.Tables[0].Rows[0]["IsStandardDeviationValid"].ToString());
            obj.isCarotidSignalValid = string.IsNullOrEmpty(dsPwv.Tables[0].Rows[0]["IsCarotidSignalValid"].ToString()) ? false : bool.Parse(dsPwv.Tables[0].Rows[0]["IsCarotidSignalValid"].ToString());
            obj.isFemoralSignalValid = string.IsNullOrEmpty(dsPwv.Tables[0].Rows[0]["IsFemoralSignalValid"].ToString()) ? false : bool.Parse(dsPwv.Tables[0].Rows[0]["IsFemoralSignalValid"].ToString());
        }
        
        /**This method fill assessment details for a particular patient
        * */
        void FillPatientAssessmentDetailsReport()
        {           
            // check db connection
            if (dbMagr.CheckConnection(serverNameString, crxMgrObject.GeneralSettings.SourceData) == 0)
            {
                // hide date time display labels
                guiradlblReportDateTime.Visible = false;
                guiradlblReportDateTimeDisplay.Visible = false;

                // fetches assessment for a particular patient
                DataSet ds = new DataSet();
              
                BizPatient pObj = BizPatient.Instance();
                ds = dbMagr.GetPWVMeasurementDetails(int.Parse(pObj.patientNumber.ToString()), SettingsProperties.GroupID, bobj);
                
                guiradgridReportAssessment.DataSource = ds.Tables[0];

                guiradchkAssesments.Checked = false;
                if (ds.Tables[0].Rows.Count > 0)
                {                    
                    guiradbtnreportedit.Enabled = true;

                    // sets assessment count for a label
                    guiradlblReportAssesmentCount.Text = "[" + ds.Tables[0].Rows.Count.ToString() + " " + oMsgMgr.GetMessage("REPORT_ASSESMENT_RECORD_COUNT") + " "  + ds.Tables[0].Rows.Count.ToString() + "]";
                    guiradchkAssesments.Enabled = true;
                    SettingsProperties.HasMeasurementDetails = true;
                    guiradgridReportAssessment.MasterGridViewTemplate.Rows[ds.Tables[0].Rows.Count - 1].Cells[0].Value = true;
                    guiradbtnDelete.Enabled = true;
                    guiradbtnPrint.Enabled = true;
                    guiradpnlAnalysis.Visible = false;
                    objDefaultWindow.radtabReport.Text = oMsgMgr.GetMessage("TAB_REPORT");
                    dateToCompare = lastAssessmentsDataTime = guiradgridReportAssessment.MasterGridViewTemplate.Rows[ds.Tables[0].Rows.Count - 1].Cells[1].Value.ToString();
                    
                    if (!SettingsProperties.SetupToReport)
                    {
                        // this will populate biz session obj from latest PWV details
                        InitializeCrxOnLoad(guiradgridReportAssessment.MasterGridViewTemplate.Rows[ds.Tables[0].Rows.Count - 1].Cells[1].Value.ToString());
                    }

                    if (ds.Tables[0].Rows.Count == 1)
                    {
                        guiradchkAssesments.Checked = true;
                    }
                    
                    FillPWVMeasurementDetailsReport();
                    SuperImposedWaveForm();
                    PlotNormalRangeGraph();
                    PlotReferenceRangeGraph();                   
                }
                else
                {
                    guiradbtnreportedit.Enabled = false;
                    guiradbtnDelete.Enabled = false;
                    guiradbtnPrint.Enabled = false;
                    ClearChartData();
                    ResetMeasurementFields();
                    SettingsProperties.HasMeasurementDetails = false;
                    guiradchkAssesments.Enabled = false;
                    guiradpnlAnalysis.Visible = false;                    
                    objDefaultWindow.radtabReport.Text = oMsgMgr.GetMessage("TAB_REPORT");
                    guiradlblReportAssesmentCount.Text = "[" + ds.Tables[0].Rows.Count.ToString() + " " + oMsgMgr.GetMessage("REPORT_ASSESMENT_RECORD_COUNT") + " " + ds.Tables[0].Rows.Count.ToString() + "]";
                    guiradbtnRepeat.Enabled = objDefaultWindow.radtabCapture.Enabled = false;
                }
            }
            else
            {
                DialogResult result = RadMessageBox.Show(this, SettingsProperties.ConnectionErrorString(), oMsgMgr.GetMessage("SYSTEM_ERROR"), MessageBoxButtons.RetryCancel, RadMessageIcon.Error);
                if (result == DialogResult.Retry)
                {
                    FillPatientAssessmentDetailsReport();
                }
            }           
        }

        /**This method sets SP, DP & MP value based on bloodPressureEntryOption in labels
         * */
        void SetBloodPressureDisplayText()
        {
            switch (obj.bloodPressureEntryOption)
            {
                case 0:
                    // sp & dp
                    guiradlblReportBloodPressure1.Text = oMsgMgr.GetMessage("LABEL_SP"); // hardcoded for internal use while changing user settings.
                    guiradlblBloodPressure2.Text = oMsgMgr.GetMessage("LABEL_DP"); // hardcoded for internal use while changing user settings.
                    guiradlblreportSPdisplay.Text = obj.bloodPressure.SP.Reading.Equals(DefaultValue) ? string.Empty : obj.bloodPressure.SP.Reading.ToString();
                    guiradlblReportBloodPressure2.Text = obj.bloodPressure.DP.Reading.Equals(DefaultValue) ? string.Empty : obj.bloodPressure.DP.Reading.ToString();
                    break;
                case 1:
                    // sp & mp
                    guiradlblReportBloodPressure1.Text = oMsgMgr.GetMessage("LABEL_SP"); // hardcoded for internal use while changing user settings.
                    guiradlblBloodPressure2.Text = oMsgMgr.GetMessage("LABEL_MP"); // hardcoded for internal use while changing user settings.
                    guiradlblreportSPdisplay.Text = obj.bloodPressure.SP.Reading.Equals(DefaultValue) ? string.Empty : obj.bloodPressure.SP.Reading.ToString();
                    guiradlblReportBloodPressure2.Text = obj.bloodPressure.MP.Reading.Equals(DefaultValue) ? string.Empty : obj.bloodPressure.MP.Reading.ToString();
                    break;
                case 2:
                    // mp & dp
                    guiradlblReportBloodPressure1.Text = oMsgMgr.GetMessage("LABEL_MP"); // hardcoded for internal use while changing user settings.
                    guiradlblBloodPressure2.Text = oMsgMgr.GetMessage("LABEL_DP"); // hardcoded for internal use while changing user settings.
                    guiradlblreportSPdisplay.Text = obj.bloodPressure.MP.Reading.Equals(DefaultValue) ? string.Empty : obj.bloodPressure.MP.Reading.ToString();
                    guiradlblReportBloodPressure2.Text = obj.bloodPressure.DP.Reading.Equals(DefaultValue) ? string.Empty : obj.bloodPressure.DP.Reading.ToString();
                    break;
                default:
                    break;
            }
            
            CheckBloodPressure();
        }

        /** This method checks for blood pressure values & 
         * accordingly displays text (Normal BP) on reference range graph
         * */
        private void CheckBloodPressure()
        {
            if (obj.bloodPressure.DP.Reading.Equals(DefaultValue) && obj.bloodPressure.MP.Reading.Equals(DefaultValue) && obj.bloodPressure.DP.Reading.Equals(DefaultValue))
            {
                guiradlblReportBpRange.Visible = false;
                guireportradlblReferenceMsg.Visible = true;
                guireportradlblReferenceMsg.BringToFront();               
                guichartReferenceRange.Visible = false;
            }
            else
            {
                guiradlblReportBpRange.Visible = true;
                guichartReferenceRange.Visible = true;
                guireportradlblReferenceMsg.Visible = false;
                guireportradlblReferenceMsg.SendToBack();
            }
        }

        /**This event fires on save button click, saves edited measurement data in database & session object
        * */
        private void guiradbtnreportsave_Click(object sender, EventArgs e)
        {
            try
            {
                objDefaultWindow.radlblMessage.Text = string.Empty;

                // check db connection
                if (dbMagr.CheckConnection(serverNameString, crxMgrObject.GeneralSettings.SourceData) == 0)
                {
                    // save PWV details in database and session object
                    CrxStructPWVMeasurementData crxPWV = new CrxStructPWVMeasurementData();

                    switch (InitializeCrx(crxPWV))
                    {
                        case 0:
                            // update measurement data
                            // save data                            
                            SaveMeasurementData(crxPWV);
                            CheckLastAssessmentSelected(dateToCompare);
                            break;
                        case 1:
                            // obj validation failed                            
                             RadMessageBox.Show(this, oMsgMgr.GetMessage("ERROR_VALIDATING"), oMsgMgr.GetMessage("SYSTEM_ERROR"), MessageBoxButtons.OK, RadMessageIcon.Error);
                             break;
                        case 2:
                            // report calculation failed
                            RadMessageBox.Show(this, oMsgMgr.GetMessage("REPORT_CALCULATE_ERROR"), oMsgMgr.GetMessage("SYSTEM_ERROR"), MessageBoxButtons.OK, RadMessageIcon.Error);                
                            break;
                        default:
                            break;
                    }
                }
                else
                {
                    DialogResult result = RadMessageBox.Show(this, SettingsProperties.ConnectionErrorString(), oMsgMgr.GetMessage("SYSTEM_ERROR"), MessageBoxButtons.RetryCancel, RadMessageIcon.Error);
                    if (result == DialogResult.Retry)
                    {
                        this.Invoke(new EventHandler(guiradbtnreportsave_Click));
                    }
                }
            }          
            catch (Exception ex)
            {
                GUIExceptionHandler.HandleException(ex, this);
            }           
        }

        /**This method is used to Save the measurement details into the database.
         */ 
        private void SaveMeasurementData(CrxStructPWVMeasurementData crxPWV)
        {
            // update measurement data
            // save data
            int iRow;
            crxPWV.StudyDateTime = DateTime.Parse(SettingsProperties.PwvCurrentStudyDatetime);
            iRow = guiradgridReportAssessment.Rows.Count > 0 ? dbMagr.UpdatePWVMeasurementDetails(crxPWV) : dbMagr.SavePWVMeasurementDetails(crxPWV);

            if (iRow > 0)
            {
                // record updated successfully
                // populate session object                   

                // get the latest date from crxPWV with which data is updated
                SettingsProperties.PwvCurrentStudyDatetime = crxPWV.StudyDateTime.ToString();

                FillPatientAssessmentDetailsReport();
                guiradlblReportPwvDistance.Text = oMsgMgr.GetMessage("LABEL_PWV_DISTANCE");

                // re populate label fields again and display mode = true
                ReportPWVDisplayMode(true);
                guiradbtnreportcancel.Visible = false;
                guiradbtnreportedit.Visible = true;
                guiradbtnreportsave.Visible = false;
                OnPwvMeasurementChangedEvent.Invoke(this, new EventArgs());
            }
        }

        /**This method initializes Crx structure to update changes
      * */
        void InitializeCrxOnLoad(string studydatetime)
        {
            try
            {
                    DataSet dsPwv = new DataSet();

                    // check db connection
                    if (dbMagr.CheckConnection(serverNameString, crxMgrObject.GeneralSettings.SourceData) == 0)
                    {
                        if (string.IsNullOrEmpty(studydatetime))
                        {
                            dsPwv = dbMagr.GetPWVMeasurementDetails(int.Parse(patientObj.patientNumber.ToString()), int.Parse(patientObj.groupStudyId.ToString()), bobj);
                        }
                        else
                        {
                            // this will be called when other assessment is selected from assessment grid
                            SettingsProperties.PwvCurrentStudyDatetime = studydatetime;
                            CrxStructPWVMeasurementData cdata = new CrxStructPWVMeasurementData();
                            cdata.StudyDateTime = DateTime.Parse(studydatetime);
                            cdata.SystemIdentifier = bobj;
                            cdata.PatientNumberInternal = SettingsProperties.PatientInternalNumber;
                            cdata.GroupIdentifier = SettingsProperties.GroupID;

                            dsPwv = dbMagr.GetPWVMeasurementDetails(cdata);
                        }

                        if (dsPwv.Tables[0].Rows.Count > 0)
                        {
                            crxPWV.StudyDateTime = DateTime.Parse(dsPwv.Tables[0].Rows[0]["Studydatetime"].ToString());
                            guiradlblReportDateTimeDisplay.Text = dsPwv.Tables[0].Rows[0]["Studydatetime"].ToString();
                            SettingsProperties.PwvCurrentStudyDatetime = dsPwv.Tables[0].Rows[0]["Studydatetime"].ToString();
                            obj = (BizPWV)BizSession.Instance().measurement;

                            int len;
                            byte[] buffer = (byte[])dsPwv.Tables[0].Rows[0]["NormalRange"];

                            len = buffer.Length / 4;
                            ////ushort[] carotid1 = new ushort[len];
                            crxPWV.NormalRange = dbMagr.CommonByteArrtoFloatArr(len, buffer);

                            buffer = (byte[])dsPwv.Tables[0].Rows[0]["ReferenceRange"];

                            len = buffer.Length / 4;
                            crxPWV.ReferenceRange = dbMagr.CommonByteArrtoFloatArr(len, buffer);
                             
                            buffer = (byte[])dsPwv.Tables[0].Rows[0]["CarotidSignal"];

                            len = buffer.Length / 2;
                            crxPWV.CarotidSignal = dbMagr.CommonByteArrtoShortArr(len, buffer);
                            crxPWV.CarotidSignalLength = (short)len;

                            buffer = (byte[])dsPwv.Tables[0].Rows[0]["FemoralSignal"];
                            len = buffer.Length / 2;
                            crxPWV.FemoralSignal = dbMagr.CommonByteArrtoShortArr(len, buffer);
                            crxPWV.FemoralSignalLength = (short)len;

                            buffer = (byte[])dsPwv.Tables[0].Rows[0]["CarotidSignalFloatOnSets"];
                            len = buffer.Length / 4;
                            crxPWV.CarotidSignalFloatOnSets = dbMagr.CommonByteArrtoFloatArr(len, buffer);
                            crxPWV.CarotidSignalOnSetsLength = (short)len;

                            buffer = (byte[])dsPwv.Tables[0].Rows[0]["FemoralSignalFloatOnSets"];
                            len = buffer.Length / 4;
                            crxPWV.FemoralSignalFloatOnSets = dbMagr.CommonByteArrtoFloatArr(len, buffer);
                            crxPWV.FemoralSignalOnSetsLength = (short)len;                           
                         
                            PopulateCrxWithOtherValues(dsPwv);

                            // populating other details
                            PopulateCrxWithStatistics(dsPwv);
                            obj.Populate(crxPWV);
                            obj.Validate();
                        }
                    }
                    else
                    {
                        DialogResult result = RadMessageBox.Show(this, SettingsProperties.ConnectionErrorString(), oMsgMgr.GetMessage("SYSTEM_ERROR"), MessageBoxButtons.RetryCancel, RadMessageIcon.Error);
                        if (result == DialogResult.Retry)
                        {
                            InitializeCrxOnLoad(studydatetime);
                        }
                    }               
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
                if (SettingsProperties.SetupToReport)
                {
                    DataSet dsPWV = new DataSet();
                    CrxLogger.Instance.Write("Patient name : " + BizPatient.Instance().firstName + " " + BizPatient.Instance().lastName);
                    // check db connection
                    if (dbMagr.CheckConnection(serverNameString, crxMgrObject.GeneralSettings.SourceData) == 0)
                    {
                        if (string.IsNullOrEmpty(studydatetime))
                        {
                            dsPWV = dbMagr.GetPWVMeasurementDetails(int.Parse(patientObj.patientNumber.ToString()), int.Parse(patientObj.groupStudyId.ToString()), bobj);
                        }
                        else
                        {
                            // this will be called when other assessment is selected from assessment grid
                            SettingsProperties.PwvCurrentStudyDatetime = studydatetime;
                            CrxStructPWVMeasurementData cdata = new CrxStructPWVMeasurementData();
                            cdata.StudyDateTime = DateTime.Parse(studydatetime);
                            cdata.SystemIdentifier = bobj;
                            cdata.PatientNumberInternal = SettingsProperties.PatientInternalNumber;
                            cdata.GroupIdentifier = SettingsProperties.GroupID;

                            dsPWV = dbMagr.GetPWVMeasurementDetails(cdata);
                        }

                        if (dsPWV.Tables[0].Rows.Count > 0)
                        {
                            crxPWV.StudyDateTime = DateTime.Parse(dsPWV.Tables[0].Rows[0]["Studydatetime"].ToString());
                            guiradlblReportDateTimeDisplay.Text = dsPWV.Tables[0].Rows[0]["Studydatetime"].ToString();
                            SettingsProperties.PwvCurrentStudyDatetime = dsPWV.Tables[0].Rows[0]["Studydatetime"].ToString();
                           
                            int len;
                            byte[] buffer = (byte[])dsPWV.Tables[0].Rows[0]["NormalRange"];

                            len = buffer.Length / 4;
                            CrxLogger.Instance.Write("Normal range length : " + len);
                            crxPWV.NormalRange = dbMagr.CommonByteArrtoFloatArr(len, buffer);

                            buffer = (byte[])dsPWV.Tables[0].Rows[0]["ReferenceRange"];
                            len = buffer.Length / 4;
                            crxPWV.ReferenceRange = dbMagr.CommonByteArrtoFloatArr(len, buffer);
                            CrxLogger.Instance.Write("Reference range length : " + len);
                            buffer = (byte[])dsPWV.Tables[0].Rows[0]["CarotidSignal"];
                            len = buffer.Length / 2;
                            crxPWV.CarotidSignal = dbMagr.CommonByteArrtoShortArr(len, buffer);
                            crxPWV.CarotidSignalLength = (short)len;

                            buffer = (byte[])dsPWV.Tables[0].Rows[0]["FemoralSignal"];
                            len = buffer.Length / 2;
                            crxPWV.FemoralSignal = dbMagr.CommonByteArrtoShortArr(len, buffer);
                            crxPWV.FemoralSignalLength = (short)len;

                            buffer = (byte[])dsPWV.Tables[0].Rows[0]["CarotidSignalFloatOnSets"];
                            len = buffer.Length / 4;
                            crxPWV.CarotidSignalFloatOnSets = dbMagr.CommonByteArrtoFloatArr(len, buffer);
                            crxPWV.CarotidSignalOnSetsLength = (short)len;

                            buffer = (byte[])dsPWV.Tables[0].Rows[0]["FemoralSignalFloatOnSets"];
                            len = buffer.Length / 4;
                            crxPWV.FemoralSignalFloatOnSets = dbMagr.CommonByteArrtoFloatArr(len, buffer);
                            crxPWV.FemoralSignalOnSetsLength = (short)len;
                           
                            // populating height, weight, blood pressure & distance values
                            PopulateCrxWithOtherValues(dsPWV);

                            // populating other details i.e statistcis information
                            PopulateCrxWithStatistics(dsPWV);
                            obj.Populate(crxPWV);
                            obj.Validate();
                        }
                    }
                    else
                    {
                        DialogResult result = RadMessageBox.Show(this, SettingsProperties.ConnectionErrorString(), oMsgMgr.GetMessage("SYSTEM_ERROR"), MessageBoxButtons.RetryCancel, RadMessageIcon.Error);
                        if (result == DialogResult.Retry)
                        {
                            InitializeCrxFromSetupToReport(studydatetime);
                        }
                    }
                }
            }
            catch (Exception ex)
            {
                GUIExceptionHandler.HandleException(ex, this);
            }
        }

        /** This method fills crx struct with height & weight, blood pressure, distance values
         * */
        void PopulateCrxWithOtherValues(DataSet dsPwv)
        {
            crxPWV.HeightInCentimetres = (short)dsPwv.Tables[0].Rows[0]["HeightInCentimetres"];
            crxPWV.HeightInInches = (short)dsPwv.Tables[0].Rows[0]["HeightInInches"];
            crxPWV.WeightInKilograms = (short)dsPwv.Tables[0].Rows[0]["WeightInKilograms"];
            crxPWV.WeightInPounds = (short)dsPwv.Tables[0].Rows[0]["WeightInPounds"];

            crxPWV.BodyMassIndex = float.Parse(dsPwv.Tables[0].Rows[0]["BodyMassIndex"].ToString());
            crxPWV.Operator = dsPwv.Tables[0].Rows[0]["Operator"].ToString();
            crxPWV.Notes = dsPwv.Tables[0].Rows[0]["Notes"].ToString();
            crxPWV.BloodPressureEntryOption = short.Parse(dsPwv.Tables[0].Rows[0]["BloodPressureEntryOption"].ToString());

            // sets SP, DP & MP value
            switch (crxPWV.BloodPressureEntryOption)
            {
                case 0: // hardcoded for internal use.
                    // sp & dp
                    crxPWV.SP = short.Parse(dsPwv.Tables[0].Rows[0]["SP"].ToString());
                    crxPWV.DP = short.Parse(dsPwv.Tables[0].Rows[0]["DP"].ToString());
                    crxPWV.MP = SdefaultValue;
                    break;
                case 1: // hardcoded for internal use.
                    // sp & mp
                    crxPWV.SP = short.Parse(dsPwv.Tables[0].Rows[0]["SP"].ToString());
                    crxPWV.DP = SdefaultValue;
                    crxPWV.MP = short.Parse(dsPwv.Tables[0].Rows[0]["MP"].ToString());
                    break;
                case 2:
                    // dp & mp
                    crxPWV.SP = SdefaultValue;
                    crxPWV.MP = short.Parse(dsPwv.Tables[0].Rows[0]["MP"].ToString());
                    crxPWV.DP = short.Parse(dsPwv.Tables[0].Rows[0]["DP"].ToString());
                    break;
                default:
                    break;
            }

            crxPWV.PWVDistanceMethod = short.Parse(dsPwv.Tables[0].Rows[0]["PWVDistanceMethod"].ToString());
            crxPWV.PWVDistance = short.Parse(dsPwv.Tables[0].Rows[0]["PWVDistance"].ToString());
            crxPWV.Direct = short.Parse(dsPwv.Tables[0].Rows[0]["Direct"].ToString());
            crxPWV.Carotid = short.Parse(dsPwv.Tables[0].Rows[0]["Carotid"].ToString());
            crxPWV.Cuff = short.Parse(dsPwv.Tables[0].Rows[0]["Cuff"].ToString());
            crxPWV.FemoraltoCuff = short.Parse(dsPwv.Tables[0].Rows[0]["FemoraltoCuff"].ToString());

            crxPWV.SystemIdentifier = bobj;
            crxPWV.GroupIdentifier = int.Parse(patientObj.groupStudyId.ToString());
            crxPWV.PatientNumberInternal = int.Parse(patientObj.patientNumber.ToString());
        }

        /** This method fills crx struct with statistics data
         * */
        void PopulateCrxWithStatistics(DataSet dsPwv)
        {
            crxPWV.Simulation = bool.Parse(dsPwv.Tables[0].Rows[0]["Simulation"].ToString());
            crxPWV.BloodPressureRange = dsPwv.Tables[0].Rows[0]["BloodPressureRange"].ToString();
            crxPWV.Age = short.Parse(dsPwv.Tables[0].Rows[0]["Age"].ToString());
            crxPWV.IsStandardDeviationValid = bool.Parse(dsPwv.Tables[0].Rows[0]["IsStandardDeviationValid"].ToString());
            crxPWV.IsFemoralSignalValid = bool.Parse(dsPwv.Tables[0].Rows[0]["IsFemoralSignalValid"].ToString());
            crxPWV.IsCarotidSignalValid = bool.Parse(dsPwv.Tables[0].Rows[0]["IsCarotidSignalValid"].ToString());
            crxPWV.CaptureTime = short.Parse(dsPwv.Tables[0].Rows[0]["CaptureTime"].ToString());
            crxPWV.MeanCorrectedTime = float.Parse(dsPwv.Tables[0].Rows[0]["MeanCorrectedTime"].ToString());
            crxPWV.MeanDeltaTime = float.Parse(dsPwv.Tables[0].Rows[0]["MeanDeltaTime"].ToString());
            crxPWV.MeanHeartRate = float.Parse(dsPwv.Tables[0].Rows[0]["MeanHeartRate"].ToString());
            crxPWV.MeanPulseWaveVelocity = float.Parse(dsPwv.Tables[0].Rows[0]["MeanPulseWaveVelocity"].ToString());
            crxPWV.SampleRate = short.Parse(dsPwv.Tables[0].Rows[0]["SampleRate"].ToString());
            crxPWV.StandardDeviation = float.Parse(dsPwv.Tables[0].Rows[0]["StandardDeviation"].ToString());
            crxPWV.CarotidSignalPulseHeight = float.Parse(dsPwv.Tables[0].Rows[0]["CarotidSignalPulseHeight"].ToString());
            crxPWV.CarotidSignalPulseHeightVariation = float.Parse(dsPwv.Tables[0].Rows[0]["CarotidSignalPulseHeightVariation"].ToString());
            crxPWV.CorrectionTime = float.Parse(dsPwv.Tables[0].Rows[0]["CorrectionTime"].ToString());
            crxPWV.DataRevision = short.Parse(dsPwv.Tables[0].Rows[0]["DataRevision"].ToString());
            crxPWV.FemoralSignalPulseHeight = float.Parse(dsPwv.Tables[0].Rows[0]["FemoralSignalPulseHeight"].ToString());
            crxPWV.NumberOfDeltas = short.Parse(dsPwv.Tables[0].Rows[0]["NumberOfDeltas"].ToString());
            crxPWV.NumberOfValidDeltas = short.Parse(dsPwv.Tables[0].Rows[0]["NumberOfValidDeltas"].ToString());
        }

        /**This method initializes Crx structure to update changes
        * */
        int InitializeCrx(CrxStructPWVMeasurementData crxPWV)
        {
            int flag = 0;

            // populate obj with entered data & check for validation
            // if it returns true then initialize crxPWV else return error & repopluate obj with original values                        
            if (ValidateSession())
            {
                // session object valid populate CRX object
                crxPWV.StudyDateTime = DateTime.Parse(SettingsProperties.PwvCurrentStudyDatetime);
                crxPWV.NormalRange = new float[0];
                crxPWV.ReferenceRange = new float[0];
                crxPWV.CarotidSignal = new ushort[0];
                crxPWV.FemoralSignal = new ushort[0];
                crxPWV.CarotidSignalFloatOnSets = new float[0];
                crxPWV.FemoralSignalFloatOnSets = new float[0];

                CalculateHeightAndWeightToUpdate(crxPWV);

                crxPWV.BodyMassIndex = guiradlblReportBmiValue.Text.Trim().Length > 0 ? float.Parse(guiradlblReportBmiValue.Text) : float.Parse(DefaultValue.ToString());
                crxPWV.Operator = guiradtxtReportOperator.Text.Trim();
                crxPWV.Notes = guiradtxtReportNotes.Text.Trim();
                crxPWV.BloodPressureEntryOption = short.Parse(crxMgrObject.GeneralSettings.BloodPressureEntryOptions.ToString());

                InitializeBPValues(crxPWV);
                CalculatePwvDistanceToUpdate(crxPWV);

                crxPWV.SystemIdentifier = bobj;
                crxPWV.GroupIdentifier = SettingsProperties.GroupID;
                crxPWV.PatientNumberInternal = SettingsProperties.PatientInternalNumber;

                BizPatient patientObj = BizPatient.Instance();

                // call recalculatepwvreport which will calculate PWV statistics & normal range values & will update biz session object.                             
                if (obj.RecalculatePWVReport(crxPWV))
                {
                    crxPWV.CarotidSignal = obj.carotidSignal.signal;
                    crxPWV.CarotidSignalFloatOnSets = obj.carotidSignal.floatOnsets;
                    crxPWV.CarotidSignalLength = short.Parse(obj.carotidSignal.signalLength.ToString());
                    crxPWV.CarotidSignalOnSetsLength = short.Parse(obj.carotidSignal.onsetsLength.ToString());
                    crxPWV.CarotidSignalPulseHeight = obj.carotidSignal.pulseHeight;
                    crxPWV.CarotidSignalPulseHeightVariation = obj.carotidSignal.pulseHeightVariation;
                    crxPWV.CorrectionTime = obj.correctionTime;
                    crxPWV.DataRevision = short.Parse(obj.dataRevision.ToString());
                    crxPWV.FemoralSignal = obj.femoralSignal.signal;
                    crxPWV.FemoralSignalFloatOnSets = obj.femoralSignal.floatOnsets;
                    crxPWV.FemoralSignalLength = short.Parse(obj.femoralSignal.signalLength.ToString());
                    crxPWV.FemoralSignalOnSetsLength = short.Parse(obj.femoralSignal.onsetsLength.ToString());
                    crxPWV.FemoralSignalPulseHeight = obj.femoralSignal.pulseHeight;
                    crxPWV.FemoralSignalPulseHeightVariation = obj.femoralSignal.pulseHeightVariation;
                    crxPWV.IsCarotidSignalValid = obj.isCarotidSignalValid;
                    crxPWV.IsFemoralSignalValid = obj.isFemoralSignalValid;
                    crxPWV.IsStandardDeviationValid = obj.isStandardDeviationValid;
                    crxPWV.MeanCorrectedTime = obj.meanCorrectedTime;
                    crxPWV.MeanDeltaTime = obj.meanDeltaTime;
                    crxPWV.MeanHeartRate = obj.meanHeartRate;
                    crxPWV.MeanPulseWaveVelocity = obj.meanPulseWaveVelocity;
                    crxPWV.NormalRange = obj.normalRange;
                    crxPWV.NumberOfDeltas = short.Parse(obj.numberOfDeltas.ToString());
                    crxPWV.NumberOfValidDeltas = short.Parse(obj.numberOfValidDeltas.ToString());
                    crxPWV.ReferenceRange = obj.referenceRange;
                    crxPWV.ReferenceRangeDistance = obj.referenceRangeDistance;
                    crxPWV.ReferenceRangePulseWaveVelocity = obj.referenceRangePulseWaveVelocity;
                    crxPWV.SampleRate = short.Parse(obj.sampleRate.ToString());
                    crxPWV.Simulation = obj.simulation;
                }
                else
                {
                    // error recalculating data
                    // do not save in database
                    flag = 2;
                }

                // binds statistics information
                BindPWVStatistics();
                crxPWV.IsStandardDeviationValid = obj.isStandardDeviationValid;
                crxPWV.IsCarotidSignalValid = obj.isCarotidSignalValid;
                crxPWV.IsFemoralSignalValid = obj.isFemoralSignalValid;
                crxPWV.MeanHeartRate = obj.meanHeartRate;
                crxPWV.MeanPulseWaveVelocity = obj.meanPulseWaveVelocity;
            }
            else
            {
                flag = 1;
            }

            return flag;
        }

        /** This method populates crx with blood pressure values from the textboxes
         * */
        private void InitializeBPValues(CrxStructPWVMeasurementData crxPWV)
        {
            

            // sets SP, DP & MP value
            switch (crxPWV.BloodPressureEntryOption)
            {
                case 0: // hardcoded for internal use.
                    // sp & dp
                    crxPWV.SP = string.IsNullOrEmpty(guiradtxtReportBloodPressure1.Text.Trim()) ? SdefaultValue : short.Parse(guiradtxtReportBloodPressure1.Text.Trim());
                    crxPWV.DP = string.IsNullOrEmpty(guiradtxtReportBloodPressure2.Text.Trim()) ? SdefaultValue : short.Parse(guiradtxtReportBloodPressure2.Text.Trim());
                    crxPWV.MP = SdefaultValue;
                    break;
                case 1: // hardcoded for internal use.
                    // sp & mp
                    crxPWV.SP = string.IsNullOrEmpty(guiradtxtReportBloodPressure1.Text.Trim()) ? SdefaultValue : short.Parse(guiradtxtReportBloodPressure1.Text.Trim());
                    crxPWV.DP = SdefaultValue;
                    crxPWV.MP = string.IsNullOrEmpty(guiradtxtReportBloodPressure2.Text.Trim()) ? SdefaultValue : short.Parse(guiradtxtReportBloodPressure2.Text.Trim());
                    break;
                case 2:
                    // dp & mp
                    crxPWV.SP = SdefaultValue;
                    crxPWV.MP = string.IsNullOrEmpty(guiradtxtReportBloodPressure1.Text.Trim()) ? SdefaultValue : short.Parse(guiradtxtReportBloodPressure1.Text.Trim());
                    crxPWV.DP = string.IsNullOrEmpty(guiradtxtReportBloodPressure2.Text.Trim()) ? SdefaultValue : short.Parse(guiradtxtReportBloodPressure2.Text.Trim());
                    break;
                default:
                    break;
            }
        }

        /** This method validates session data
         * */
        bool ValidateSession()
        {
            obj.heightAndWeight.bodyMassIndex = guiradlblReportBmiValue.Text.Trim().Length > 0 ? float.Parse(guiradlblReportBmiValue.Text) : float.Parse(DefaultValue.ToString());
            obj.operatorId = guiradtxtReportOperator.Text.Trim();
            obj.notes = guiradtxtReportNotes.Text.Trim();
            obj.bloodPressureEntryOption = ushort.Parse(crxMgrObject.GeneralSettings.BloodPressureEntryOptions.ToString());
            CalculateHeightAndWeightToValidateSession();
            CalculatePwvDistanceToValidateSession();

            // sets SP, DP & MP value
            switch (crxPWV.BloodPressureEntryOption)
            {
                case 0: // hardcoded for internal use.
                    // sp & dp
                    obj.bloodPressure.SP.Reading = string.IsNullOrEmpty(guiradtxtReportBloodPressure1.Text.Trim()) ? DefaultValue : ushort.Parse(guiradtxtReportBloodPressure1.Text.Trim());
                    obj.bloodPressure.DP.Reading = string.IsNullOrEmpty(guiradtxtReportBloodPressure2.Text.Trim()) ? DefaultValue : ushort.Parse(guiradtxtReportBloodPressure2.Text.Trim());
                    obj.bloodPressure.MP.Reading = DefaultValue;
                    break;
                case 1: // hardcoded for internal use.
                    // sp & mp
                    obj.bloodPressure.SP.Reading = string.IsNullOrEmpty(guiradtxtReportBloodPressure1.Text.Trim()) ? DefaultValue : ushort.Parse(guiradtxtReportBloodPressure1.Text.Trim());
                    obj.bloodPressure.DP.Reading = DefaultValue;
                    obj.bloodPressure.MP.Reading = string.IsNullOrEmpty(guiradtxtReportBloodPressure2.Text.Trim()) ? DefaultValue : ushort.Parse(guiradtxtReportBloodPressure2.Text.Trim());
                    break;
                case 2:
                    // dp & mp
                    obj.bloodPressure.SP.Reading = DefaultValue;
                    obj.bloodPressure.MP.Reading = string.IsNullOrEmpty(guiradtxtReportBloodPressure1.Text.Trim()) ? DefaultValue : ushort.Parse(guiradtxtReportBloodPressure1.Text.Trim());
                    obj.bloodPressure.DP.Reading = string.IsNullOrEmpty(guiradtxtReportBloodPressure2.Text.Trim()) ? DefaultValue : ushort.Parse(guiradtxtReportBloodPressure2.Text.Trim());
                    break;
                default:
                    break;
            }

            return obj.Validate();            
        }

        /**This method calcuates PWV distance values to update
        * */
        void CalculatePwvDistanceToUpdate(CrxStructPWVMeasurementData crxPWV)
        {
            // initially form session obj
           crxPWV.PWVDistanceMethod = short.Parse(crxMgrObject.PwvSettings.PWVDistanceMethod.ToString());
            crxPWV.PWVDistance = short.Parse(obj.calculatedDistance.ToString());
            crxPWV.Direct = short.Parse(obj.myPWVDirectDistance.distance.ToString());
            crxPWV.Carotid = short.Parse(obj.myCarotidDistance.distance.ToString());
            crxPWV.Cuff = short.Parse(obj.myCuffDistance.distance.ToString());
            crxPWV.FemoraltoCuff = short.Parse(obj.myFemoral2CuffDistance.distance.ToString());

            // calculate & intialise PWV distance only if there is change
            switch (crxPWV.PWVDistanceMethod)
            {
                case 0:
                    if ((guiradtxtCarotid.Text.Length > 0) && (guiradtxtReportCuff.Text.Length > 0) && (guiradtxtReportFemoToCuff.Text.Length > 0))
                    {
                        crxPWV.Direct = SdefaultValue;
                        crxPWV.Carotid = short.Parse(guiradtxtCarotid.Text.Trim());
                        crxPWV.Cuff = short.Parse(guiradtxtReportCuff.Text.Trim());
                        crxPWV.FemoraltoCuff = short.Parse(guiradtxtReportFemoToCuff.Text.Trim());
                        crxPWV.PWVDistance = (short)(crxPWV.Cuff - crxPWV.Carotid - crxPWV.FemoraltoCuff);
                        crxPWV.PWVDistanceMethod = 0;
                    }

                    break;

                case 1:
                    if ((guiradtxtCarotid.Text.Length > 0) && (guiradtxtReportFemoToCuff.Text.Length > 0))
                    {
                        crxPWV.Direct = short.Parse(guiradtxtCarotid.Text.Trim());
                        crxPWV.Carotid = SdefaultValue;
                        crxPWV.Cuff = SdefaultValue;
                        crxPWV.FemoraltoCuff = short.Parse(guiradtxtReportFemoToCuff.Text.Trim());
                        crxPWV.PWVDistance = (short)(crxPWV.Direct - crxPWV.FemoraltoCuff);
                        crxPWV.PWVDistanceMethod = 1; // guiradlblReportPwvDistanceMethodType.Text;
                    }

                    break;
                default:
                    break;
            }        
        }

        /**This method calcuates PWV distance values to validate obj
       * */
        void CalculatePwvDistanceToValidateSession()
        {
            // initially form session obj            
            obj.distanceMethod = ushort.Parse(crxMgrObject.PwvSettings.PWVDistanceMethod.ToString());
            
            // calculate & intialise PWV distance only if there is change
            switch (crxPWV.PWVDistanceMethod)
            {
                case 0:
                    if ((guiradtxtCarotid.Text.Length > 0) && (guiradtxtReportCuff.Text.Length > 0) && (guiradtxtReportFemoToCuff.Text.Length > 0))
                    {
                        obj.myPWVDirectDistance.distance = DefaultValue;
                        obj.myCarotidDistance.distance = ushort.Parse(guiradtxtCarotid.Text.Trim());
                        obj.myCuffDistance.distance = ushort.Parse(guiradtxtReportCuff.Text.Trim());
                        obj.myFemoral2CuffDistance.distance = ushort.Parse(guiradtxtReportFemoToCuff.Text.Trim());
                        obj.calculatedDistance = (ushort)(obj.myCuffDistance.distance - obj.myCarotidDistance.distance - obj.myFemoral2CuffDistance.distance);
                        obj.distanceMethod = 0; 
                    }

                    break;

                case 1:
                    if ((guiradtxtCarotid.Text.Length > 0) && (guiradtxtReportFemoToCuff.Text.Length > 0))
                    {
                        obj.myPWVDirectDistance.distance = ushort.Parse(guiradtxtCarotid.Text.Trim());
                        obj.myCarotidDistance.distance = DefaultValue;
                        obj.myCuffDistance.distance = DefaultValue;
                        obj.myFemoral2CuffDistance.distance = ushort.Parse(guiradtxtReportFemoToCuff.Text.Trim());
                        obj.calculatedDistance = (ushort)(obj.myPWVDirectDistance.distance - obj.myFemoral2CuffDistance.distance);
                        obj.distanceMethod = 1; // guiradlblReportPwvDistanceMethodType.Text;
                    }

                    break;
                default:
                    break;
            }
        }

        /**This method calculates height & weight to update bizsession object for validating data before saving
    */
        void CalculateHeightAndWeightToValidateSession()
        {
            // calculates height in inches & centimeters
            if (guiradtxtReportHeightInches.Visible)
            {
                // Convert the user input to hight and inches
                int heightinches = (int.Parse((string.IsNullOrEmpty(guiradtxtReportHeight.Text.Trim()) ? "0" : guiradtxtReportHeight.Text.Trim()).ToString()) * 12) + int.Parse((string.IsNullOrEmpty(guiradtxtReportHeightInches.Text.Trim()) ? "0" : guiradtxtReportHeightInches.Text.Trim()).ToString());
                obj.heightAndWeight.heightInInches = heightinches == 0 ? DefaultValue : ushort.Parse(heightinches.ToString());
                obj.heightAndWeight.weightInPounds = string.IsNullOrEmpty(guiradtxtReportWeight.Text.Trim()) ? DefaultValue : ushort.Parse(guiradtxtReportWeight.Text.Trim());
            }
            else
            {
                obj.heightAndWeight.heightInCentimetres = string.IsNullOrEmpty(guiradtxtReportHeight.Text.Trim()) ? DefaultValue : ushort.Parse(guiradtxtReportHeight.Text.Trim());
                obj.heightAndWeight.weightInKilograms = string.IsNullOrEmpty(guiradtxtReportWeight.Text.Trim()) ? DefaultValue : ushort.Parse(guiradtxtReportWeight.Text.Trim());               
            }
        }

        /**This method calculates height & weight to update changes
      */
        void CalculateHeightAndWeightToUpdate(CrxStructPWVMeasurementData crxPWV)
        {
            crxPWV.HeightInInches = crxPWV.WeightInPounds = crxPWV.HeightInCentimetres = crxPWV.WeightInKilograms = SdefaultValue;
            // calculates height in inches & centimeters
            if (guiradtxtReportHeightInches.Visible)
            {
                int heightinches = (int.Parse((string.IsNullOrEmpty(guiradtxtReportHeight.Text.Trim()) ? "0" : guiradtxtReportHeight.Text.Trim()).ToString()) * 12) + int.Parse((string.IsNullOrEmpty(guiradtxtReportHeightInches.Text.Trim()) ? "0" : guiradtxtReportHeightInches.Text.Trim()).ToString());
                crxPWV.HeightInInches = heightinches == 0 ? SdefaultValue : short.Parse(heightinches.ToString());
                crxPWV.WeightInPounds = string.IsNullOrEmpty(guiradtxtReportWeight.Text.Trim()) ? SdefaultValue : short.Parse(guiradtxtReportWeight.Text.Trim());

                // 1 pound is 0.453592 kilograms

                // 1 inch = 2.54 cm
               // crxPWV.WeightInKilograms = (short)Math.Round(double.Parse(crxPWV.WeightInPounds.ToString()) * 0.453592, MidpointRounding.ToEven);
              // crxPWV.HeightInCentimetres = (short)Math.Round(double.Parse(crxPWV.HeightInInches.ToString()) * 2.54, MidpointRounding.ToEven);
            }
            else
            {
                crxPWV.HeightInCentimetres = string.IsNullOrEmpty(guiradtxtReportHeight.Text.Trim()) ? SdefaultValue : short.Parse(guiradtxtReportHeight.Text.Trim());
                crxPWV.WeightInKilograms = string.IsNullOrEmpty(guiradtxtReportWeight.Text.Trim()) ? SdefaultValue : short.Parse(guiradtxtReportWeight.Text.Trim());

                // 1 kilogram = 2.20462262 pounds
                // 0.3937007874 inches in 1 centimeter
               // crxPWV.WeightInPounds = (short)Math.Round(double.Parse(crxPWV.WeightInKilograms.ToString()) * 2.20462262, MidpointRounding.ToEven);
               // crxPWV.HeightInInches = (short)Math.Round(double.Parse(crxPWV.HeightInCentimetres.ToString()) * 0.3937007874, MidpointRounding.ToEven);
            }
        }        

        /** Plots superimposed wave form series from BizSession.xls
         * */
        private void SuperImposedWaveForm()
        {
            try
            {               
                 crxMgrObject.PwvSettings.PWVDistanceMethod = obj.distanceMethod;

                 ushort[] femoralSignal = obj.femoralSignal.signal; // Array.ConvertAll(femoralValuesArray, new Converter<string, ushort>(Convert.ToUInt16));
                              
                obj.femoralSignal.CaptureSignal(femoralSignal, obj.femoralSignal.signalLength, 0, 0);
               
                ushort[] carotidSignal = obj.carotidSignal.signal; // Array.ConvertAll(carotidValuesArray, new Converter<string, ushort>(Convert.ToUInt16));
              
                obj.carotidSignal.CaptureSignal(carotidSignal, obj.carotidSignal.signalLength, 0, 0);
                bool status = obj.Calculate();

                // calling method to bind statistics returned from calculate() method
                BindPWVStatistics();
                
                if (status)
                {
                    // plot super impose wave form
                    ushort[] femoralSignalToPlot = obj.femoralSignal.signal;
                    float[] femoralOnSetPoints = obj.femoralSignal.floatOnsets;
                    ushort femoralOnSetPointLength = obj.femoralSignal.onsetsLength;
                    ushort[] carotidSignalToPlot = obj.carotidSignal.signal;
                    float[] carotidOnSetPoints = obj.carotidSignal.floatOnsets;
                    ushort carotidOnSetPointLenth = obj.carotidSignal.onsetsLength;

                    PlotSuperImposedWaveform(femoralSignalToPlot, femoralOnSetPoints, carotidSignalToPlot, carotidOnSetPoints, obj.femoralSignal.signalLength);
                }
                else
                { 
                    // dont plot & show error message
                    RadMessageBox.Show(this, oMsgMgr.GetMessage("DB_CORRUPT"), oMsgMgr.GetMessage("VALIDATION_ERROR"), MessageBoxButtons.OK);

                    // log the error
                    CrxLogger oLogObject = CrxLogger.Instance;
                    oLogObject.Write(oMsgMgr.GetMessage("DB_CORRUPT"));
                }
            }
            catch (Exception ex)
            {
                GUIExceptionHandler.HandleException(ex, this);
            }
        }

        private void PlotSuperImposedWaveform(IList<ushort> femoralSignalToPlot, float[] femoralOnSetPoints, ushort[] carotidSignalToPlot, float[] carotidOnSetPoints, ushort signalLength)
        {
            // plot on the waveform.
            const double chartHeight = 500;
            const double minXValue = 0;
            double maxXValue = signalLength;            

            // set y axis
            guichartSuperImposedWaveform.ChartAreas[0].AxisY.Minimum = chartHeight * ChartAreaMinimumY;
            guichartSuperImposedWaveform.ChartAreas[0].AxisY.Maximum = chartHeight * ChartAreaMaximumY;
            guichartSuperImposedWaveform.ChartAreas[0].AxisY.Interval = 1;

            // set x axis
            guichartSuperImposedWaveform.ChartAreas[0].AxisX.Minimum = minXValue;
            guichartSuperImposedWaveform.ChartAreas[0].AxisX.Maximum = maxXValue;
            guichartSuperImposedWaveform.ChartAreas[0].AxisX.Interval = 1;

            // initialize series,chartype,add points to series and finally add series to chart.
            // Series for tonometer
            guichartSuperImposedWaveform.Series.Clear();
            #region Carotid Tonometer            
            tonometerSeries.ChartType = SeriesChartType.FastLine;
            tonometerSeries.Color = Color.White;
            tonometerSeries.XValueType = ChartValueType.Auto;
            tonometerSeries.YValuesPerPoint = 1;
            Hashtable carotidTable = new Hashtable();
            tonometerSeries.Points.Clear();
            for (int i = 0; i < signalLength; i++)
            {
                if (carotidSignalToPlot[i] > guichartSuperImposedWaveform.ChartAreas[0].AxisY.Maximum)
                {
                    guichartSuperImposedWaveform.ChartAreas[0].AxisY.Maximum = carotidSignalToPlot[i] * ChartAreaMaximumY;
                }

                if (carotidSignalToPlot[i] < guichartSuperImposedWaveform.ChartAreas[0].AxisY.Minimum)
                {
                    guichartSuperImposedWaveform.ChartAreas[0].AxisY.Minimum = carotidSignalToPlot[i] * ChartAreaMinimumY;
                }

                tonometerSeries.Points.AddXY(i, carotidSignalToPlot[i]);
                carotidTable[i] = carotidSignalToPlot[i];
            }

            #region Carotid onSet points

            tonometerOnsetSeries.ChartType = SeriesChartType.FastPoint;
            tonometerOnsetSeries.Color = Color.Red;
            tonometerOnsetSeries2.ChartType = SeriesChartType.FastPoint;
            tonometerOnsetSeries2.Color = Color.Green;
            tonometerOnsetSeries2.Points.Clear();
            tonometerOnsetSeries.Points.Clear();
            for (int j = 0; j < carotidOnSetPoints.Length; j++)
            {
                int valueToPLot = int.Parse(Math.Round(double.Parse(carotidOnSetPoints[j].ToString()), MidpointRounding.ToEven).ToString());
                int valueToPLot1 = Math.Abs(valueToPLot);

                if (valueToPLot < 0)
                {
                    tonometerOnsetSeries2.Points.AddXY(valueToPLot1, carotidTable[valueToPLot1]);
                    tonometerOnsetSeries2.Points[tonometerOnsetSeries2.Points.Count - 1].MarkerStyle = MarkerStyle.Circle;
                }
                else
                {
                    tonometerOnsetSeries.Points.AddXY(valueToPLot1, carotidTable[valueToPLot1]);
                    tonometerOnsetSeries.Points[tonometerOnsetSeries.Points.Count - 1].MarkerStyle = MarkerStyle.Circle;
                }
            }

            #endregion
            #endregion

            #region Femoral cuff

            femoralSeries.ChartType = SeriesChartType.FastLine;
            femoralSeries.Color = Color.Yellow;
            femoralSeries.XValueType = ChartValueType.Auto;
            femoralSeries.YValuesPerPoint = 1;
            Hashtable femoralTable = new Hashtable();
            femoralSeries.Points.Clear();
            for (int i = 0; i < signalLength; i++)
            {
                if (femoralSignalToPlot[i] > guichartSuperImposedWaveform.ChartAreas[0].AxisY.Maximum)
                {
                    guichartSuperImposedWaveform.ChartAreas[0].AxisY.Maximum = femoralSignalToPlot[i] * ChartAreaMaximumY;
                }

                if (femoralSignalToPlot[i] < guichartSuperImposedWaveform.ChartAreas[0].AxisY.Minimum)
                {
                    guichartSuperImposedWaveform.ChartAreas[0].AxisY.Minimum = femoralSignalToPlot[i] * ChartAreaMinimumY;
                }

                femoralSeries.Points.AddXY(i, femoralSignalToPlot[i]);
                femoralTable[i] = femoralSignalToPlot[i];
            }

            #region Cuff Onset Points

            femoralOnsetSeries.ChartType = SeriesChartType.FastPoint;
            femoralOnsetSeries.Color = Color.Red;
            femoralOnsetSeries2.ChartType = SeriesChartType.FastPoint;
            femoralOnsetSeries2.Color = Color.Green;
            femoralOnsetSeries2.Points.Clear();
            
            femoralOnsetSeries.Points.Clear();
            for (int j = 0; j < femoralOnSetPoints.Length; j++)
            {
                int valueToPLotCuffOnset = int.Parse(Math.Round(double.Parse(femoralOnSetPoints[j].ToString()), MidpointRounding.ToEven).ToString());

                int valueToPLotCuffOnset1 = Math.Abs(valueToPLotCuffOnset);

                if (valueToPLotCuffOnset < 0)
                {
                    femoralOnsetSeries2.Points.AddXY(valueToPLotCuffOnset1, femoralTable[valueToPLotCuffOnset1]);
                    femoralOnsetSeries2.Points[femoralOnsetSeries2.Points.Count - 1].MarkerStyle = MarkerStyle.Circle;
                }
                else
                {
                    femoralOnsetSeries.Points.AddXY(valueToPLotCuffOnset1, femoralTable[valueToPLotCuffOnset1]);
                    femoralOnsetSeries.Points[femoralOnsetSeries.Points.Count - 1].MarkerStyle = MarkerStyle.Circle;
                }
            }

            #endregion
            #endregion

            guichartSuperImposedWaveform.Series.Add(tonometerSeries);
            guichartSuperImposedWaveform.Series.Add(femoralSeries);
            guichartSuperImposedWaveform.Series.Add(tonometerOnsetSeries);
            guichartSuperImposedWaveform.Series.Add(tonometerOnsetSeries2);
            guichartSuperImposedWaveform.Invalidate();
        }

        /**This event fires when checkbox is checked or unchecked on assessment gridview
          * */
        private void guiradgridReportAssessment_ValueChanged(object sender, EventArgs e)
        {
            try
            {
                if (guiradgridReportAssessment.ActiveEditor is RadCheckBoxEditor)
                {
                    if (guiradgridReportAssessment.ActiveEditor.Value.ToString() == "Off")
                    {
                        // if checkbox is unchecked
                        DisplaySelectedRecords(guiradgridReportAssessment.CurrentCell.RowIndex, false);
                        guiradchkAssesments.Checked = false;
                    }
                    else
                    {
                        // if checkbox is checked
                        DisplaySelectedRecords(-1, true);
                    }
                }
            }
            catch (Exception ex)
            {
                GUIExceptionHandler.HandleException(ex, this);
            }
        }
       
        /** This method displays report & analysis screen as per assessments selected
         * */
        private void DisplayReportOnSelection(int recordSelected, string datetime)
        {
            guiradlblReportDateTime.Visible = false;
            guiradlblReportDateTimeDisplay.Visible = false;
            dateToCompare = string.Empty;

            // check assessment checkbox if all assessments are selected in grid
            if (recordSelected == guiradgridReportAssessment.Rows.Count)
            {
                // check assessment checkbox if all assessments are selected in grid
                if (guiradchkAssesments.ToggleState != ToggleState.On)
                {
                    guiradchkAssesments.Checked = true;
                }
                
                guiradbtnDelete.Enabled = true;
            }
            else if (recordSelected == 1)
            {
                // if only 1 record is selected in assessment grid bind the measurement details 
                // pertaining to that patient
                guiradpnlAnalysis.Visible = false;
                guiradbtnDelete.Enabled = true;
                objDefaultWindow.radtabReport.Text = oMsgMgr.GetMessage("TAB_REPORT");
                //if (!SettingsProperties.IsWaitIntervalImposed)
                //{
                //    guiradbtnRepeat.Enabled = true;
                //    objDefaultWindow.radtabCapture.Enabled = true;
                //}

                dateToCompare = datetime.Replace(",", string.Empty);
                guiradbtnreportedit.Enabled = true;
                CheckLastAssessmentSelected(dateToCompare);
                // when record selected is only one display record as per assessment selected
                DisplayReportForSelectedAssesment(dateToCompare);
            }
            else if (recordSelected > 1)
            {
                // display analysis screen
                guiradbtnreportedit.Enabled = false;
                guiradpnlAnalysis.Visible = true;
                guiradbtnRepeat.Enabled = false;
                guiradbtnDelete.Enabled = true;
                objDefaultWindow.radtabCapture.Enabled = false;
                ReportPWVDisplayMode(true);
                PlotAnalysisTrendCharts();
                objDefaultWindow.radtabReport.Text = oMsgMgr.GetMessage("TAB_ANALYSIS");
            }
            else if (recordSelected == 0)
            {
                // disable delete & edit button when no record is selected
                guiradbtnDelete.Enabled = false;
                guiradbtnreportedit.Enabled = false;
                CheckLastAssessmentSelected(string.Empty);
            }
            else
            {
                // for any other condition besides above, shiw report screen & enable capture & repeat buttons
                guiradbtnreportedit.Enabled = false;
                guiradpnlAnalysis.Visible = false;
                if (!SettingsProperties.IsWaitIntervalImposed)
                {
                    guiradbtnRepeat.Enabled = true;
                    objDefaultWindow.radtabCapture.Enabled = true;
                }

                objDefaultWindow.radtabReport.Text = oMsgMgr.GetMessage("TAB_REPORT");
            }
        }     
              
        /** This method plots normal range graph
         * */
        void PlotNormalRangeGraph()
        {
            try
            {
                guichartNormalRange.Width = 306; // original width 306
                guichartNormalRange.Height = 170; // original height 170
                guichartNormalRange.Location = new Point(331, 232); // original location (331, 232)
                
                // set y axis (normal range values from Bizsession object in float)
                float[] normalrange = obj.normalRange; // { 11.0F, 10.2F, 5.0F, 13.0F, 20.0F, 16.0F, 19.0F, 9.0F, 17.0F, 15.0F };
                float[] sortedNormalRange = normalrange;
                Array.Sort(sortedNormalRange);

                guichartNormalRange.Series.Clear();              

                    // Array.Sort(normalrange);
                    guichartNormalRange.ChartAreas[0].AxisY.Minimum = double.Parse(sortedNormalRange[0].ToString());
                    guichartNormalRange.ChartAreas[0].AxisY.Maximum = double.Parse(sortedNormalRange[sortedNormalRange.Length - 1].ToString());
                    guichartNormalRange.ChartAreas[0].AxisY.Interval = 5;
                    guichartNormalRange.ChartAreas[0].AxisY.Title = oMsgMgr.GetMessage("REPORT_NORMALRANGE_Y_AXIS_TITLE");
                    
                    // set x axis
                    guichartNormalRange.ChartAreas[0].AxisX.Minimum = BizConstants.MINIMUM_REFERENCE_RANGE_AGE; // 20
                    guichartNormalRange.ChartAreas[0].AxisX.Maximum = BizConstants.MAXIMUM_REFERENCE_RANGE_AGE; // 90;
                    guichartNormalRange.ChartAreas[0].AxisX.Title = oMsgMgr.GetMessage("REPORT_NORMALRANGE_X_AXIS_TITLE");
                    guichartNormalRange.ChartAreas[0].AxisX.Interval = 35;
                
                    // initialize series,chartype,add points to series and finally add series to chart.
                    // Series for tonometer
                    // set display properties for normal range graph
                    normalRangeSeries.Points.Clear();
                    normalRangeSeries.ChartType = SeriesChartType.Area;
                    normalRangeSeries.Color = Color.Green;
                    normalRangeSeries.BorderColor = Color.Black;
                    normalRangeSeries.BorderWidth = 1;
                    normalRangeSeries.BackGradientStyle = GradientStyle.TopBottom;
                    int ageToPlot = BizConstants.MINIMUM_REFERENCE_RANGE_AGE;
                    for (int i = 0; i < normalrange.Length; i++)
                    {
                        normalRangeSeries.Points.AddXY((double)(ageToPlot + i), (double)((float)normalrange[i]));
                    }

                    guichartNormalRange.Series.Add(normalRangeSeries);                           
               
                // set properties for series 2 for plotting bubble
                normalRangeSeries2.ChartType = SeriesChartType.Bubble;
                normalRangeSeries2.Color = Color.FromArgb(92, 81, 238);
                normalRangeSeries2.CustomProperties = "BubbleMaxSize=15";
                normalRangeSeries2.MarkerStyle = MarkerStyle.Circle;
                normalRangeSeries2.ShadowOffset = 5;
                normalRangeSeries2.Points.Clear();
                normalRangeSeries2.Points.AddXY(double.Parse(obj.patientAge.ToString()), double.Parse(obj.meanPulseWaveVelocity.ToString())); // double.Parse(obj.meanPulseWaveVelocity.ToString())
                              
                guichartNormalRange.Series.Add(normalRangeSeries2);
                guichartNormalRange.Invalidate();
            }
            catch (Exception ex)
            {
                GUIExceptionHandler.HandleException(ex, this);
            }            
        }

        /** This method plots reference range graph
       * */
        void PlotReferenceRangeGraph()
        {
            try
            {
                guichartReferenceRange.Width = 306; // original width 306
                guichartReferenceRange.Height = 170; // original height 170
                guichartReferenceRange.Location = new Point(650, 232); // original location (650, 232)
              
                    // plot reference range graph
                    // set y axis (normal range values from Bizsession object in float)
                    // convert normal range float array to double
                    float[] referencerange = obj.referenceRange; // { 11.0F, 10.2F, 5.0F, 13.0F, 20.0F, 16.0F, 19.0F, 9.0F, 17.0F, 15.0F };
                    float[] sortedreferencerange = referencerange;

                    guichartReferenceRange.Series.Clear();

                    Array.Sort(sortedreferencerange);

                    guichartReferenceRange.ChartAreas[0].AxisY2.Minimum = double.Parse(((float)sortedreferencerange[0]).ToString());
                    guichartReferenceRange.ChartAreas[0].AxisY2.Maximum = double.Parse(((float)sortedreferencerange[sortedreferencerange.Length - 1]).ToString());
                    guichartReferenceRange.ChartAreas[0].AxisY2.Interval = 5;
                    guichartReferenceRange.ChartAreas[0].AxisY2.Title = oMsgMgr.GetMessage("REPORT_NORMALRANGE_Y_AXIS_TITLE");
                    
                    // set x axis
                    guichartReferenceRange.ChartAreas[0].AxisX.Minimum = (double)BizConstants.MINIMUM_REFERENCE_RANGE_AGE; // 20
                    guichartReferenceRange.ChartAreas[0].AxisX.Maximum = (double)BizConstants.MAXIMUM_REFERENCE_RANGE_AGE; // 90;
                    guichartReferenceRange.ChartAreas[0].AxisX.Title = oMsgMgr.GetMessage("REPORT_NORMALRANGE_X_AXIS_TITLE");
                    guichartNormalRange.ChartAreas[0].AxisX.Interval = 35;

                    // initialize series,chartype,add points to series and finally add series to chart.
                    // Series for tonometer
                    // set display properties for normal range graph
                    referenceRangeSeries.ChartType = SeriesChartType.Area;
                    referenceRangeSeries.Color = Color.Green;
                    referenceRangeSeries.BorderColor = Color.Black;
                    referenceRangeSeries.BorderWidth = 1;
                    referenceRangeSeries.BackGradientStyle = GradientStyle.TopBottom;
                    referenceRangeSeries.Points.Clear();
                    referenceRangeSeries.YAxisType = AxisType.Secondary;
                    referenceRangeSeries.XAxisType = AxisType.Primary;
                    int ageToPlot = BizConstants.MINIMUM_REFERENCE_RANGE_AGE;

                    for (int i = 0; i < referencerange.Length; i++)
                    {
                        referenceRangeSeries.Points.AddXY((double)(ageToPlot + i), (double)((float)referencerange[i]));
                    }

                    guichartReferenceRange.Series.Add(referenceRangeSeries);

                    // set properties for series 2 for plotting bubble
                    referenceRangeSeries2.ChartType = SeriesChartType.Bubble;
                    referenceRangeSeries2.Color = Color.FromArgb(92, 81, 238);
                    referenceRangeSeries2.CustomProperties = "BubbleMaxSize=15";
                    referenceRangeSeries2.MarkerStyle = MarkerStyle.Circle;
                    referenceRangeSeries2.ShadowOffset = 5;
                    referenceRangeSeries2.Points.Clear();
                    referenceRangeSeries2.YAxisType = AxisType.Secondary;
                    referenceRangeSeries2.XAxisType = AxisType.Primary;
                    referenceRangeSeries2.Points.AddXY(double.Parse(obj.patientAge.ToString()), double.Parse(obj.meanPulseWaveVelocity.ToString())); // double.Parse(normalrange[3].ToString())9.9

                    guichartReferenceRange.Series.Add(referenceRangeSeries2);
                    guichartReferenceRange.Invalidate();  
            }
            catch (Exception ex)
            {
                GUIExceptionHandler.HandleException(ex, this);
            }
        }
        
        /** This event fires when timer interval ends
         * */
        private void timer1_Tick(object sender, EventArgs e)
        {
            objDefaultWindow.radtabCapture.Enabled = true;
            guiradbtnRepeat.Enabled = true;
            SettingsProperties.IsWaitIntervalImposed = false;
            SettingsProperties.CaptureToSetup = false;
            timer1.Stop();
        }

        /** This event fires when assessment checkbox is selected.
         * If selected it selects all checkboxes in grid & vice versa
         * */
        private void guiradchkAssesments_ToggleStateChanged(object sender, StateChangedEventArgs args)
        {
            int numberOfRowsChecked;
            bool flag = !SettingsProperties.IsWaitIntervalImposed;

            // if checked select all records in grid   
            if (guiradchkAssesments.ToggleState == ToggleState.On)
                {
                    foreach (GridViewRowInfo t in guiradgridReportAssessment.Rows)
                    {
                        t.Cells["CheckBox"].Value = true;
                    }

                    guiradgridReportAssessment.SelectAll();
                    numberOfRowsChecked = guiradgridReportAssessment.Rows.Count;

                    if (numberOfRowsChecked.Equals(1))
                    {                        
                        guiradbtnRepeat.Enabled = flag;
                        objDefaultWindow.radtabCapture.Enabled = flag;
                        guiradbtnreportedit.Enabled = true;  
                    }
                    else
                    {
                        guiradbtnRepeat.Enabled = false;
                        objDefaultWindow.radtabCapture.Enabled = false;
                        guiradbtnreportedit.Enabled = false;  

                        // Plot the trend analysis as per the number of assessments selected
                        ReportPWVDisplayMode(true);
                        GetCommaSeparatedDates();
                        PlotAnalysisTrendCharts();
                        guiradpnlAnalysis.Visible = true;
                        objDefaultWindow.radtabReport.Text = oMsgMgr.GetMessage("TAB_ANALYSIS"); 
                    }
                    
                    oneRecordSelect = false;
                    guiradbtnDelete.Enabled = true;                                                     
                }

                if (guiradchkAssesments.ToggleState == ToggleState.Off)
                {
                    if (!oneRecordSelect && guiradgridReportAssessment.Rows.Count > 0)
                    {                        
                        foreach (GridViewRowInfo tRow in guiradgridReportAssessment.Rows)
                        {
                            tRow.Cells["CheckBox"].Value = false;
                        }

                        guiradgridReportAssessment.ClearSelection();
                        guiradbtnDelete.Enabled = true;
                        guiradbtnreportedit.Enabled = true;
                        guiradpnlAnalysis.Visible = false;
                        
                        guiradbtnRepeat.Enabled = flag;
                        objDefaultWindow.radtabCapture.Enabled = flag;                    

                        guiradgridReportAssessment.MasterGridViewTemplate.Rows[guiradgridReportAssessment.Rows.Count - 1].Cells[0].Value = true;
                        DisplayReportForSelectedAssesment(guiradgridReportAssessment.Rows[guiradgridReportAssessment.Rows.Count - 1].Cells[1].Value.ToString());                        
                        objDefaultWindow.radtabReport.Text = oMsgMgr.GetMessage("TAB_REPORT");
                        guiradlblReportDateTime.Visible = false;
                        guiradlblReportDateTimeDisplay.Visible = false;
                    } 
                }
        }

        /** This event deletes assessments of selected patients
         * */
        private void guiradbtnDelete_Click(object sender, EventArgs e)
        {
            try
            {
                recordsToDelete = 0;
                dateWithComma = string.Empty;
                GetCommaSeparatedDates();

                // display confirmation message box
                DialogResult result = RadMessageBox.Show(this, oMsgMgr.GetMessage("DELETE_PWV_MSG").Replace("{0}", recordsToDelete.ToString()), oMsgMgr.GetMessage("APPLICATION_MESSAGE"), MessageBoxButtons.YesNo);

                if (result == DialogResult.Yes)
                {
                    // delete selected records
                    CrxStructPWVMeasurementData crxData = new CrxStructPWVMeasurementData();
                    crxData.SystemIdentifier = bobj;
                    crxData.GroupIdentifier = SettingsProperties.GroupID;
                    crxData.PatientNumberInternal = SettingsProperties.PatientInternalNumber;
                    int del = dbMagr.DeletePWVMeasurementDetails(crxData, dateWithComma);

                    if (del == 1)
                    {
                        // records deleted successfully, bind assessment grid
                        FillPatientAssessmentDetailsReport();
                    }
                }
            }
            catch (Exception ex)
            {
                GUIExceptionHandler.HandleException(ex, this);
            }
        }

        /** This method gets comma separated dates for the selected assessments
         * */
        string GetCommaSeparatedDates()
        {
            dateWithComma = string.Empty;

            // count number of records to delete & format comma separated date string
            for (int iRow = 0; iRow < guiradgridReportAssessment.Rows.Count; iRow++)
            {
                // guiradgridReportAssessment.MasterGridViewTemplate.Rows[this.guiradgridReportAssessment.CurrentCell.RowIndex].Cells[0].Value.ToString())
                if (guiradgridReportAssessment.Rows[iRow].Cells["CheckBox"].Value != null)
                {
                    if (bool.Parse(guiradgridReportAssessment.Rows[iRow].Cells["CheckBox"].Value.ToString()))
                    {
                        recordsToDelete++;

                        // preparing comma separated string of dates
                        dateWithComma += guiradgridReportAssessment.Rows[iRow].Cells[1].Value.ToString() + ",";
                        guiradgridReportAssessment.Rows[iRow].IsSelected = true;
                    }
                }
            }

            return dateWithComma;
        }

        /** This method clears all chart series for tonometer, normal & reference range
         * */
        void ClearChartData()
        {
            guichartReferenceRange.Series.Clear();
            guichartNormalRange.Series.Clear();
            guichartNormalRange.Width = 250; // original width 306
            guichartNormalRange.Height = 125; // original height 170
            guichartNormalRange.Location = new Point(370, 232); // original location (331, 232)

            guichartReferenceRange.Width = 250; // original width 306
            guichartReferenceRange.Height = 125; // original height 170
            guichartReferenceRange.Location = new Point(660, 235); // original location (650, 232)
                       
            guichartSuperImposedWaveform.Series.Clear();
        }

        /** This method resets all PWV measurement fields
         * */
        void ResetMeasurementFields()
        {
            // populates PWV measurement fields as per Settings from config manager
            guiradlblReportCuffUnits.Text = string.Empty;
            guiradlblReportFemoralCuffUnits.Text = string.Empty;
            guiradlblCarotidUnits.Text = string.Empty;

            guiradtxtReportFemoToCuff.Text = string.Empty;
            guiradtxtReportCuff.Text = string.Empty;
            guiradlblReportCuffUnits.Text = string.Empty;
            guiradtxtReportFemoToCuff.Text = string.Empty;
            
            guiradtxtCarotid.Text = string.Empty;
            guiradlblCarotidUnits.Text = string.Empty;
            guiradlblReportFemoralCuffUnits.Text = string.Empty;
            guiradlblReportPwvDistanceMethodType.Text = oMsgMgr.GetMessage("REPORT_LBL_SUBTRACTING");
            guiradtxtReportCuff.Text = string.Empty;
            guiradtxtCarotid.Text = string.Empty;

            guiradtxtReportHeight.Text = string.Empty;
            guiradlblReportHeightDisplay.Text = string.Empty;
            guiradtxtReportHeightInches.Text = string.Empty;
            guiradlblReportHeightInches.Text = string.Empty;
            guiradtxtReportWeight.Text = string.Empty;
            guiradlblReportWeightdisplay.Text = string.Empty;
            guiradtxtReportOperator.Text = string.Empty;
            guiradlblReportOperatordisplay.Text = string.Empty;
            guiradtxtReportNotes.Text = string.Empty;
            guiradlblReportNotesDisplay.Text = string.Empty;

            guiradtxtReportBloodPressure1.Text = string.Empty;
            guiradtxtReportBloodPressure2.Text = string.Empty;

            guiradlblreportSPdisplay.Text = string.Empty;
            guiradlblReportBloodPressure2.Text = string.Empty;
            guiradlblReportBmiValue.Text = string.Empty;
            guiradlblreportpwvdistancedisplay1.Text = string.Empty;

            // reset pwv statistics
            guiradlblReportHeartRateValue.Text = string.Empty;
            guiradlblReportPWVValue.Text = string.Empty;
            guiradlblStdDeviationImage.ImageIndex = 0;
            guiradlblReportFemoralImage.ImageIndex = 0;
            guiradlblReportCarotidImage.ImageIndex = 0;
        }

        /** This event fires when Print button is clicked on report screen
         * It allows to print report screen data
         * */
        private void guiradbtnPrint_Click(object sender, EventArgs e)
        {
            // currently we are just showing print dialog
            SettingsProperties.ViewPrintDialogToSetPrinter(reportprintDialog);

            ////DialogResult dsPrint = reportprintDialog.ShowDialog();

            ////if (dsPrint == DialogResult.Yes)
            ////{ 
            ////    //reportprintDialog.PrinterSettings.PrinterName
            ////    // code to print the report screen
            ////}
        }

        /** This method shows analysis trend graph
                 * */
        private void PlotAnalysisTrendCharts()
        {
            try
            {
                guiradlblReportDateTime.Visible = true;
                guiradlblReportDateTimeDisplay.Visible = true;
                guiradlblReportDateTime.Text = oMsgMgr.GetMessage("GUI_DATETIME_TXT");
                
                // set report screen to display mode if & disable edit button
                guireportradlblReferenceMsg.Visible = false;
               // SetPWVDsiplayMode();
                guiradbtnreportedit.Enabled = false;

                // add chart titles & clear chart series
                guiradchartPulseWaveVelocity.Titles.Clear();
                guiradchartHeartRate.Titles.Clear();
                guiradchartPulseWaveVelocity.Titles.Add(oMsgMgr.GetMessage("LBL_REPORT_PWV"));
                guiradchartHeartRate.Titles.Add(oMsgMgr.GetMessage("LBL_REPORT_HEART_RATE"));
                guiradchartPulseWaveVelocity.Series.Clear();
                guiradchartHeartRate.Series.Clear();

                // clear all the points in series
                pWVline.Points.Clear();
                pWvPoint.Points.Clear();
                heartline.Points.Clear();
                heartPoint.Points.Clear();

                // if date ends with comma, truncate it as it creates empty value in array for dates
                char separator = ',';
                if (dateWithComma.EndsWith(","))
                {
                    dateWithComma = dateWithComma.Remove(dateWithComma.Length - 1);
                }

                date = dateWithComma.Split(separator);
                guiradlblReportDateTimeDisplay.Text = date[date.Length - 1].ToString();

                // check for connection
                if (dbMagr.CheckConnection(serverNameString, crxMgrObject.GeneralSettings.SourceData) == 0)
                {
                    CrxStructPWVTrendData trendData = new CrxStructPWVTrendData();

                    // fetch records for selected assessments
                    dbMagr.GetPWVTrendData(SettingsProperties.PatientInternalNumber, SettingsProperties.GroupID, SettingsProperties.SystemIdentifier, dateWithComma + ",", trendData);
                    if (!string.IsNullOrEmpty(trendData.HeartRateArrStr) && !string.IsNullOrEmpty(trendData.PulseWaveVelocityArrStr))
                    {
                        PlotHeartRateTrend(trendData);
                        PlotPWVelocityTrend(trendData);

                        // subscribing to gettooltiptext event of chart control, 
                        // this event will fetch datapoint values when mouse is hovered over the chart area
                        guiradchartPulseWaveVelocity.GetToolTipText += new System.EventHandler<System.Windows.Forms.DataVisualization.Charting.ToolTipEventArgs>(Chart_GetToolTipText);
                        
                        guiradchartHeartRate.GetToolTipText += new System.EventHandler<System.Windows.Forms.DataVisualization.Charting.ToolTipEventArgs>(Chart_GetToolTipText);
                    }
                }
                else
                {
                    DialogResult result = RadMessageBox.Show(this, SettingsProperties.ConnectionErrorString(), oMsgMgr.GetMessage("SYSTEM_ERROR"), MessageBoxButtons.RetryCancel, RadMessageIcon.Error);
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

        /** This method plots heart rate trend graph
         * */
        private void PlotHeartRateTrend(CrxStructPWVTrendData trendData)
        {
            const char separator = ',';

            // define strings arrays for plotting heart rate & PWV
            heartRate = trendData.HeartRateArrStr.Split(separator);
            pWV = trendData.PulseWaveVelocityArrStr.Split(separator);
            isStdDeviationValid = trendData.IsStdDevValidArrStr.Split(separator);
                        
            string[] heartPwvSort = trendData.HeartRateArrStr.Split(separator);
            Array.Sort(heartPwvSort);

            // plot heart rate series
            if (heartRate.Length > 0)
            {
                // assign latest record valus to bottom labels
                guiradlblReportHeartRateValue.Text = heartRate[heartRate.Length - 1].ToString() + oMsgMgr.GetMessage("HEARTRATE_UNIT");
               
                double value = Math.Round(double.Parse(heartPwvSort[0].ToString()) * 0.96, MidpointRounding.ToEven);
                guiradchartHeartRate.ChartAreas[0].AxisY.Minimum = value;
                guiradchartHeartRate.ChartAreas[0].AxisY.Title = oMsgMgr.GetMessage("HEARTRATE_LBL_ANALYSIS");

                value = Math.Round(double.Parse(heartPwvSort[heartPwvSort.Length - 1].ToString()) * 1.04, MidpointRounding.ToEven);
                guiradchartHeartRate.ChartAreas[0].AxisY.Maximum = value;
                guiradchartHeartRate.ChartAreas[0].AxisY.IntervalOffset = 0;
                guiradchartHeartRate.ChartAreas[0].AxisY.Interval = 10;

                guiradchartHeartRate.ChartAreas[0].AxisX.IntervalOffset = 1;
                CalculateLabelIntervalX();
                               
                // guiradchartHeartRate.ChartAreas[0].AxisX.Title = oMsgMgr.GetMessage("ANALYSIS_XAXIS_TITLE");
                guiradchartHeartRate.ChartAreas[0].AxisX.CustomLabels.Clear();

                for (int hrseries1 = 0; hrseries1 < heartRate.Length; hrseries1 = hrseries1 + labelInterval)
                {
                    if (hrseries1 > (5 * labelInterval))
                    {
                        guiradchartHeartRate.ChartAreas[0].AxisX.LabelStyle.Angle = -90;
                        guiradchartHeartRate.ChartAreas[0].AxisX.LabelStyle.Font = labelFontMin;
                    }
                    else
                    {
                        guiradchartHeartRate.ChartAreas[0].AxisX.LabelStyle.Font = labelFontMax;
                        guiradchartHeartRate.ChartAreas[0].AxisX.LabelStyle.Angle = 0;
                    }

                    guiradchartHeartRate.ChartAreas[0].AxisX.CustomLabels.Add(hrseries1 - 1, hrseries1 + 1, date[hrseries1].ToString());
                }

                // to plot line for heart rate graph
                heartline.Color = Color.FromArgb(121, 171, 231);
                heartline.ChartType = SeriesChartType.FastLine;
                heartline.Name = "Heart rate";
               
                heartline.XValueType = ChartValueType.Int32;

                // to plot points for heart rate graph                                                                                  
                heartPoint.Color = Color.FromArgb(121, 171, 231);
                heartPoint.ChartType = SeriesChartType.Bubble;
                heartPoint.Name = "Point";
              
                heartPoint.XValueType = ChartValueType.Int32;
                heartPoint.Color = Color.FromArgb(121, 171, 231);
                heartPoint.CustomProperties = "BubbleMaxSize=" + (15 - labelInterval * 2 + 1);
                heartPoint.MarkerStyle = MarkerStyle.Circle;
                heartPoint.ShadowOffset = 2;

                for (int hrseries1 = 0; hrseries1 < heartRate.Length; hrseries1++)
                {
                    heartline.Points.AddXY(hrseries1, double.Parse(heartRate[hrseries1].ToString()));
                    heartPoint.Points.AddXY(hrseries1, double.Parse(heartRate[hrseries1].ToString()));
                }

                // following line shows y axis data for the last data point
                // heartPoint.Points[heartRate.Length - 1].LabelForeColor = Color.Gray;
                // heartPoint.Points[heartRate.Length - 1].Label = heartRate[heartRate.Length - 1].ToString();                
                guiradchartHeartRate.Series.Add(heartline);
                guiradchartHeartRate.Series.Add(heartPoint);
                guiradchartHeartRate.Invalidate();
            }
        }

        /** This method plots PWV velocity trend graph 
         * */
        private void PlotPWVelocityTrend(CrxStructPWVTrendData trendData)
        {
            const char separator = ',';

            // plot pwv trend series
            string[] stdDeviation = trendData.StandardDeviationArrStr.Split(separator);
            string[] heartPwvSort = trendData.PulseWaveVelocityArrStr.Split(separator);

            // sort array to get minimum & maximum value to set y axis range
            Array.Sort(heartPwvSort);
            string[] stdDeviationSort = trendData.StandardDeviationArrStr.Split(separator);
            Array.Sort(stdDeviationSort);

            if (pWV.Length > 0)
            {
                // assign latest record valus to bottom labels
                guiradlblReportPWVValue.Text = pWV[pWV.Length - 1].ToString() + oMsgMgr.GetMessage("PWV_UNIT");
                guiradlblStdDeviationImage.ImageIndex = int.Parse(isStdDeviationValid[isStdDeviationValid.Length - 1].ToString());
            
                // set max value as largest pwv + largest std deviation
                // set min value as lowest pwv + largest std deviation
                double maxValue = double.Parse(heartPwvSort[heartPwvSort.Length - 1].ToString()) + double.Parse(stdDeviationSort[stdDeviationSort.Length - 1].ToString()) + 1;
                double minValue = double.Parse(heartPwvSort[0].ToString()) - double.Parse(stdDeviationSort[stdDeviationSort.Length - 1].ToString()) - 1;

                maxValue = Math.Round(maxValue, 0, MidpointRounding.ToEven);
                minValue = Math.Round(minValue);
                CalculateLabelIntervalYForPwvTrend(int.Parse(minValue.ToString()), int.Parse(MaxLabelYValue.ToString()));
                
                double value = Math.Round(minValue * ChartAreaMinimumY); 
                guiradchartPulseWaveVelocity.ChartAreas[0].AxisY.Minimum = value;
                guiradchartPulseWaveVelocity.ChartAreas[0].AxisY.Title = oMsgMgr.GetMessage("PWV_LBL_ANALYSIS");

                value = Math.Round(maxValue * ChartAreaMaximumY, 0, MidpointRounding.AwayFromZero);
                guiradchartPulseWaveVelocity.ChartAreas[0].AxisY.Maximum = value;
                guiradchartPulseWaveVelocity.ChartAreas[0].AxisY.IntervalOffset = 0;
                guiradchartPulseWaveVelocity.ChartAreas[0].AxisY.Interval = 1;
                
                
                guiradchartPulseWaveVelocity.ChartAreas[0].AxisX.IntervalOffset = 1;
                guiradchartPulseWaveVelocity.ChartAreas[0].AxisX.CustomLabels.Clear();                
               
                for (pwvRecords = 0; pwvRecords < pWV.Length; pwvRecords = pwvRecords + labelInterval)
                {
                    if (pwvRecords > (5 * labelInterval))
                    {
                        guiradchartPulseWaveVelocity.ChartAreas[0].AxisX.LabelStyle.Angle = -90;
                        guiradchartPulseWaveVelocity.ChartAreas[0].AxisX.LabelStyle.Font = labelFontMin;                        
                    }
                    else
                    {
                        guiradchartPulseWaveVelocity.ChartAreas[0].AxisX.LabelStyle.Font = labelFontMax;
                        guiradchartPulseWaveVelocity.ChartAreas[0].AxisX.LabelStyle.Angle = 0;
                    }

                    guiradchartPulseWaveVelocity.ChartAreas[0].AxisX.CustomLabels.Add(pwvRecords - 1, pwvRecords + 1, date[pwvRecords].ToString());
                }

                // to plot line for PWV graph                            
                pWVline.Color = Color.FromArgb(121, 171, 231);
                pWVline.ChartType = SeriesChartType.FastLine;
                pWVline.XValueType = ChartValueType.Int32;

                // to plot points for PWV graph
                pWvPoint.Color = Color.FromArgb(121, 171, 231);
                pWvPoint.ChartType = SeriesChartType.Bubble;

                pWvPoint.XValueType = ChartValueType.Int32;
                pWvPoint.Color = Color.FromArgb(121, 171, 231);
                pWvPoint.CustomProperties = "BubbleMaxSize=" + (15 - labelInterval * 2 + 1);
                pWvPoint.MarkerStyle = MarkerStyle.Circle;
                pWvPoint.ShadowOffset = 2;

                // double deviation = 0.5;
                double lowerErrorY = double.MinValue ;
                double upperErrorY = 0.0;
                for (int hrseries1 = 0; hrseries1 < pWV.Length; hrseries1++)
                {
                    // heartline.Points.AddXY(double.Parse(DateTime.Parse(date[hrseries1].ToString()).ToOADate().ToString()), double.Parse(heartRate[hrseries1].ToString()));
                    pWVline.Points.AddXY(hrseries1, double.Parse(pWV[hrseries1].ToString()));
                    pWvPoint.Points.AddXY(hrseries1, double.Parse(pWV[hrseries1].ToString()));

                    // add series dynamically for showing error bar on PWV chart
                    Series correctionLine = new Series("Errorbar" + hrseries1.ToString());
                    correctionLine.ChartType = SeriesChartType.ErrorBar;
                    correctionLine.XValueType = ChartValueType.Int32;
                    correctionLine.YValuesPerPoint = 3;
                    correctionLine.MarkerSize = 3;

                    correctionLine.MarkerStyle = MarkerStyle.None;
                    correctionLine.Color = Color.FromArgb(121, 171, 231);
                    correctionLine["PointWidth"] = "0.1";

                    double centerY = double.Parse(pWV[hrseries1].ToString());
                    lowerErrorY = centerY - double.Parse(stdDeviation[hrseries1].ToString());
                    upperErrorY = centerY + double.Parse(stdDeviation[hrseries1].ToString());
                    correctionLine.Points.AddXY(hrseries1, centerY, lowerErrorY, upperErrorY);

                    // guiradchartPulseWaveVelocity.ChartAreas[0].AxisX.CustomLabels.Add(double.Parse(hrseries1.ToString()), double.Parse(hrseries1.ToString()), date[hrseries1].ToString());                              
                    guiradchartPulseWaveVelocity.Series.Add(correctionLine);
                }

                // following line shows y axis data for the last data point
               // pWVPoint.Points[pWV.Length - 1].Label = pWV[pWV.Length - 1].ToString();
                guiradchartPulseWaveVelocity.Series.Add(pWVline);
                guiradchartPulseWaveVelocity.Series.Add(pWvPoint);
                guiradchartPulseWaveVelocity.Invalidate();
            }
        }

        /** This method calculates label interval for Y axis label for PWV trend charts
         * Since the interval is 1 there is overlapping for label display when more labels are there
         * */
        private void CalculateLabelIntervalYForPwvTrend(int minValue, int maxValue)
        {
            // calculate the number of items which will display as y axis labels
            int numberOfLabel = maxValue - minValue + 1;

            if (numberOfLabel > MaxLabelYValue)
            {
                int yInterval = numberOfLabel % MaxLabelYValue;
                guiradchartPulseWaveVelocity.ChartAreas[0].AxisY.LabelStyle.Interval = yInterval;
            }
        }

        /** This method calculates label interval for x axis label for PWV trend & Heart rate charts
        * Since the interval is 1 there is overlapping for label display when more labels are there
        * */
        private void CalculateLabelIntervalX()
        {
            int intvl = heartRate.Length / XInterval;

            if (intvl == 0)
            {
                intvl = 1;
            }

            guiradchartHeartRate.ChartAreas[0].AxisX.LabelStyle.Interval = intvl;
            labelInterval = intvl;
        }       

        /** This event fires when mouse pointer is hovered over PWV / heart rate trend analysis chart. 
         * It fetches datapoints (x & y values) for that control and displays data elated to it
         * */
        private void Chart_GetToolTipText(object sender, ToolTipEventArgs e)
        {
            try
            {
                
                // Check selected chart element and set tooltip text   
                if (e.HitTestResult.ChartElementType == ChartElementType.DataPoint)
                {
                    // This method fetches int array of x coordinates for x axis data points
                    GetXCoordinatesForChart();
                   
                    // get the point index to fetch data values from series   
                    // this point index always return higher point index if mouse cursor is hover between two data points
                    // so even if mouse cursor is nearer to point index 0 it will return point index 1 which is higher & next most point index
                    int i = e.HitTestResult.PointIndex;
                    int pointSelected = i;

                    if (i > 0)
                    {
                        // calculate midpoint between two x coordinates taking i as greater point index
                        int midPoint = int.Parse(xCoordinate[i].ToString()) - int.Parse(xCoordinate[i - 1].ToString());
                        midPoint = midPoint / 2;
                        midPoint = midPoint + int.Parse(xCoordinate[i - 1].ToString());
                        
                        // if current x co-ordinates are greater than midpoint, display data for point index i else display for for i - 1
                        if (e.X > midPoint)
                        {
                            // display data closest to datapoint at index i
                            // bind the hear rate, pwv, datetime & standard deviation values from arrays as per point index
                            guiradlblReportHeartRateValue.Text = heartRate[i].ToString() + oMsgMgr.GetMessage("HEARTRATE_UNIT");
                            guiradlblReportPWVValue.Text = pWV[i].ToString() + oMsgMgr.GetMessage("PWV_UNIT");
                            guiradlblStdDeviationImage.ImageIndex = int.Parse(isStdDeviationValid[i].ToString());
                            guiradlblReportDateTimeDisplay.Text = date[i].ToString();                           
                        }
                        else
                        {
                            // display data closest to datapoint at index i - 1
                            // bind the hear rate, pwv, datetime & standard deviation values from arrays as per point index
                            guiradlblReportHeartRateValue.Text = heartRate[i - 1].ToString() + oMsgMgr.GetMessage("HEARTRATE_UNIT");
                            guiradlblReportPWVValue.Text = pWV[i - 1].ToString() + oMsgMgr.GetMessage("PWV_UNIT");
                            guiradlblStdDeviationImage.ImageIndex = int.Parse(isStdDeviationValid[i - 1].ToString());
                            guiradlblReportDateTimeDisplay.Text = date[i - 1].ToString();
                            pointSelected = i - 1;
                        }
                    }
                    else
                    {
                        // bind the hear rate, pwv & standar deviation values from arrays as per point index
                        guiradlblReportHeartRateValue.Text = heartRate[i].ToString() + oMsgMgr.GetMessage("HEARTRATE_UNIT");
                        guiradlblReportPWVValue.Text = pWV[i].ToString() + oMsgMgr.GetMessage("PWV_UNIT"); ;
                        guiradlblStdDeviationImage.ImageIndex = int.Parse(isStdDeviationValid[i].ToString());
                        guiradlblReportDateTimeDisplay.Text = date[i].ToString();                        
                    }

                    if (chartSelected == ChartName.Pwv.ToString())
                    {
                        guiradchartPulseWaveVelocity.Series["pWVPoint"].Points[pointSelected].Color = Color.FromArgb(180, 207, 241); // "point" for internal use only
                    }
                    else
                    {
                        guiradchartHeartRate.Series["Point"].Points[pointSelected].Color = Color.FromArgb(180, 207, 241); // "point" for internal use only
                    }
                }
                else if (e.HitTestResult.ChartElementType == ChartElementType.AxisLabels)
                {
                    // if it is axislabel get the text of it to show as tool tip
                    CustomLabel s = (CustomLabel)e.HitTestResult.Object;
                    e.Text = s.Text;
                    ChangeDataPointColor();                   
                }
                else
                {
                    ChangeDataPointColor();
                }
            }
            catch (Exception ex)
            {
                GUIExceptionHandler.HandleException(ex, this);
            }
        }
      
        /** This event is fired when the user wants to repeat a particular measurement.
       * On click of the Repeat button, the user is navigated to the Capture screen 
         * where he can recapture the waveforms.
       */
        private void guiradbtnRepeat_Click(object sender, EventArgs e)
        {
            try
            {
                if (DalModule.Instance.CheckIfDeviceIsConnected())
                {
                    // Compare if the lastAssessmentsDataTime contains last assessments datatime.
                    if (guiradgridReportAssessment.CurrentCell != null)
                    {
                        if (!lastAssessmentsDataTime.Equals(guiradgridReportAssessment.Rows[guiradgridReportAssessment.CurrentCell.RowIndex].Cells[1].Value))
                        {
                            // populate the session object with last assessments data.
                            InitializeCrxOnLoad(lastAssessmentsDataTime);
                        }
                    }

                    // on the click of this button navigate the user to the capture screen whenre he can recapture the waveforms.                
                    if (SettingsProperties.captureChildForm != null)
                    {
                        SettingsProperties.captureChildForm.Close();
                    }

                    SettingsProperties.CaptureTabClick = false;

                    // SettingsProperties.captureChildForm = new Capture(this);
                    SettingsProperties.captureChildForm = new Capture(objDefaultWindow);

                    // SettingsProperties.captureChildForm = new Capture();
                    SettingsProperties.captureChildForm.TopLevel = false;
                    SettingsProperties.captureChildForm.Dock = DockStyle.Fill;
                    SettingsProperties.captureChildForm.FormBorderStyle = FormBorderStyle.None;

                    var page = objDefaultWindow.radpgTabCollection.Pages[1];
                    SettingsProperties.captureChildForm.Parent = page;
                    page.Controls.Clear();

                    page.Controls.Add(SettingsProperties.captureChildForm);
                    SettingsProperties.captureChildForm.Show();

                    objDefaultWindow.radpgTabCollection.SelectedPage = objDefaultWindow.radtabCapture;
                    objDefaultWindow.radtabCapture.Enabled = true;
                }
                else
                {
                    // device not connected show error message
                    RadMessageBox.Show(this, oMsgMgr.GetMessage("CAPTURE_DEVICE_ERR_MSG"), oMsgMgr.GetMessage("SYSTEM_ERROR"), MessageBoxButtons.OK, RadMessageIcon.Error);
                    if (SettingsProperties.CaptureTabClick)
                    {
                        objDefaultWindow.radpgTabCollection.SelectedPage = objDefaultWindow.radtabReport;
                        objDefaultWindow.radtabReport.Enabled = true;
                    }
                }
            }
            catch (Exception ex)
            {
                GUIExceptionHandler.HandleException(ex, this);
            }
        }
                
        /**  This method prepares an array of x co-ordinates for analysis trend chart.
         * This will help to determine the closest datapoint on mouse over         
         * */
        void GetXCoordinatesForChart()
        {
            xCoordinate = new int[pWVline.Points.Count];
            double xValue = 0.0;
            int iCount = 0;
            foreach (DataPoint dp in pWVline.Points)
            {
                // get the pixel values corresponding to datapoint value for X
                xValue = guiradchartPulseWaveVelocity.ChartAreas[0].AxisX.ValueToPixelPosition(double.Parse(dp.XValue.ToString()));
               
                // add to array of x co-ordinates
                xCoordinate[iCount] = int.Parse(Math.Round(xValue, MidpointRounding.ToEven).ToString());
                iCount++;
            }
        }

        /** This event customizes label display on PWV trend analysis chart
         * */
        private void guiradchartPulseWaveVelocity_Customize(object sender, EventArgs e)
        {
            if (pwvRecords > 3)
            {
                foreach (CustomLabel cl in guiradchartPulseWaveVelocity.ChartAreas[0].AxisX.CustomLabels)
                {
                    cl.Text = DateTime.Parse(cl.Text).ToShortDateString() + "\n" + DateTime.Parse(cl.Text).ToLongTimeString();                    
                }

                foreach (CustomLabel cl in guiradchartHeartRate.ChartAreas[0].AxisX.CustomLabels)
                {
                    cl.Text = DateTime.Parse(cl.Text).ToShortDateString() + "\n" + DateTime.Parse(cl.Text).ToLongTimeString();
                }
            }
        }
        
        /** This method checks for numeric input in textbox
         * It will allow only numeric entry in textboxes for blood pressure & distance values
       * */
        private void AllowNumericValues(object sender, KeyPressEventArgs e)
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
        
        /** this method checks for mutliple assessments selected and accordingly displays analysis screen
         * */
        private void DisplaySelectedRecords(int rowIndex, bool isChecked)
        {
            oneRecordSelect = true;
            int recordSelected = 0;
            dateWithComma = string.Empty;

            // below line of code will keep focus on current record selection in assessment grid
            IGridViewEventListener navigatorListener = this.guiradgridReportAssessment.GridNavigator as IGridViewEventListener;
            guiradgridReportAssessment.MasterTemplate.SynchronizationService.RemoveListener(navigatorListener);
 
            // this call begins the update of gridview selection using shift key
            guiradgridReportAssessment.MasterTemplate.BeginUpdate();
           
            foreach (GridViewRowInfo row in this.guiradgridReportAssessment.Rows)
            {
                if (row.IsSelected)
                {
                    // when this value is false it means
                    if (isChecked)
                    {
                        row.Cells["CheckBox"].Value = true;
                        recordSelected++;
                        dateWithComma += row.Cells[1].Value.ToString() + ",";
                    }
                }
                else if (row.Cells["CheckBox"].Value != null)
                {
                    if (bool.Parse(row.Cells["CheckBox"].Value.ToString()) && rowIndex != row.Index)
                    {
                        recordSelected++;
                        dateWithComma += row.Cells[1].Value.ToString() + ",";
                    }
                }
            }

            // below line of code will keep focus on current record selection in assessment grid
            guiradgridReportAssessment.MasterTemplate.EndUpdate(new DataViewChangedEventArgs(ViewChangedAction.DataChanged));
            guiradgridReportAssessment.MasterTemplate.SynchronizationService.AddListener(navigatorListener);

            // display analysis / report screen based on records selected
            DisplayReportOnSelection(recordSelected, dateWithComma);            
        }

        /** This method binds data to report screen as per the selected assesment
         * */
        private void DisplayReportForSelectedAssesment(string dateTime)
        {
            InitializeCrxOnLoad(dateTime);
            FillPWVMeasurementDetailsReport();
            SuperImposedWaveForm();
            PlotNormalRangeGraph();
            PlotReferenceRangeGraph();
        }

        /** This method subscribes all the text boxes & drop down for changes made to it.
        * To the form changed event which will determine for any changes made before application is closed
        * */
        private void SubscribeReportFormChanges()
        {
            guiradtxtReportCuff.TextChanged += SettingsProperties.FormChanged;
            guiradtxtCarotid.TextChanged += SettingsProperties.FormChanged;
            guiradtxtReportFemoToCuff.TextChanged += SettingsProperties.FormChanged;
            guiradtxtReportHeight.TextChanged += SettingsProperties.FormChanged;
            guiradtxtReportHeightInches.TextChanged += SettingsProperties.FormChanged;
            guiradtxtReportOperator.TextChanged += SettingsProperties.FormChanged;
            guiradtxtReportBloodPressure1.TextChanged += SettingsProperties.FormChanged;
            guiradtxtReportWeight.TextChanged += SettingsProperties.FormChanged;
            guiradtxtReportBloodPressure2.TextChanged += SettingsProperties.FormChanged;
            guiradtxtReportNotes.TextChanged += SettingsProperties.FormChanged;
        }

        /** This event disables right click on assessment grid
         * */
        private void guiradgridReportAssessment_ContextMenuOpening(object sender, ContextMenuOpeningEventArgs e)
        {
            e.Cancel = true;
        }

        /**This method is used to check if the timer on the Setup screen is still active or not.
         * The timer is used to impose a wait time after the user navigates away from the Capture screen.
         */
        private void CheckWaitIntervalImposed()
        {
            if (SettingsProperties.IsWaitIntervalImposed)
            {
                objDefaultWindow.radtabCapture.Enabled = false;
                guiradbtnRepeat.Enabled = false;
            }
            else
            {
                objDefaultWindow.radtabCapture.Enabled = true;
                guiradbtnRepeat.Enabled = true;
            }
        }

        /** This event fires when mouse is hovered over Heart trend chart
         * It sets the chart type which helps in determining which chart datapoints are hovered over
         * */
        private void guiradchartHeartRate_MouseHover(object sender, EventArgs e)
        {
            chartSelected = ChartName.HeartRate.ToString();          
            
        }

        /** This event fires when mouse is hovered over PWV chart
         * It sets the chart type which helps in determining which chart datapoints are hovered over
         * */
        private void guiradchartPulseWaveVelocity_MouseHover(object sender, EventArgs e)
        {
            chartSelected = ChartName.Pwv.ToString();
        }

        /** This method is used to set the default color of all data points once the mouse cursor is moved away fromt he points.
         * It resets the color for both heart rate & pulse wave velocity
         * */
        private void ChangeDataPointColor()
        {
           // check if pwv velocity trend chart is hovered
            if (chartSelected == ChartName.Pwv.ToString())
            {
                // for each points in bubble series reset the default color
                for (int i = 0; i < guiradchartPulseWaveVelocity.Series["pWVPoint"].Points.Count; i++)
                {
                    guiradchartPulseWaveVelocity.Series["pWVPoint"].Points[i].Color = Color.FromArgb(121, 171, 231); // "point" for internal use only                
                }
            }
            else
            {
                // for each points in bubble series reset the default color if chart hovered is pwv
                for (int i = 0; i < guiradchartHeartRate.Series["Point"].Points.Count; i++)
                {
                    guiradchartHeartRate.Series["Point"].Points[i].Color = Color.FromArgb(121, 171, 231); // "point" for internal use only                
                }
            }
        }

        /**This method is called on the tick of wait interval  timer used on the Default window.
         * On the tick of the timer we enable the repeat button on the Report screen along with the Capture tab.
         */
        public void EnableRepeatAndCaptureTab(bool value)
        {
            try
            {
                SettingsProperties.IsWaitIntervalImposed = !value;
                SettingsProperties.CaptureToSetup = !value;

                objDefaultWindow.radtabCapture.Enabled = value;
                guiradbtnRepeat.Enabled = value;

                if (value)
                {
                    CheckLastAssessmentSelected(dateToCompare);
                }
            }
            catch (Exception ex)
            {
                GUIExceptionHandler.HandleException(ex, this);
            }
        }

        /** This method checks whether last assessment is selected, if selected repeat & capture tabs are enabled & vice versa
         * */
        private void CheckLastAssessmentSelected(string dateTime)
        {
            bool setValue = lastAssessmentsDataTime.Equals(dateTime) && !SettingsProperties.IsWaitIntervalImposed;
            objDefaultWindow.radtabCapture.Enabled = setValue;
            guiradbtnRepeat.Enabled = setValue;
        }       
       
    }
}
