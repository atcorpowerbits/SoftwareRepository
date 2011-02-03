/*
     Copyright (C) ATCOR MEDICAL PTY LTD, 2010
 
     Filename     :     Settings Window
        
     Author       :     Nitesh Chhedda
 
     Description  :     Functionality implemented for Report tab.
*/

using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using Telerik.WinControls;
using Telerik.WinControls.UI;
using AtCor.Scor.CrossCutting;
using AtCor.Scor.CrossCutting.Configuration;
using AtCor.Scor.CrossCutting.Logging;
using AtCor.Scor.CrossCutting.DatabaseManager;
using AtCor.Scor.CrossCutting.Messaging;
using Telerik.WinControls.Primitives;
using Telerik.WinControls.Enumerations;
using Telerik.WinControls.UI.Docking;
using Telerik.WinControls.Themes.Design;
using AtCor.Scor.BusinessLogic;
using System.Windows.Forms.DataVisualization.Charting;
using System.Globalization;
using System.Collections;
using System.Configuration;
using System.Threading;

namespace AtCor.Scor.Gui.Presentation
{
    public partial class Report : Telerik.WinControls.UI.RadForm
    {
        ////#region Reading Excel File
        ////Microsoft.Office.Interop.Excel.Application application;
        ////Microsoft.Office.Interop.Excel.Workbook book;
        ////Microsoft.Office.Interop.Excel.Worksheet sheet;
        ////#endregion

        // Events
        public delegate void InitializationMessage(string message);
        
        public static event InitializationMessage OnReportInitializationProcess;
        
        public static event EventHandler OnPWVMeasurementChangedEvent;

        public static event EventHandler OnReportScreenLoadComplere;

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

        CrxMessagingManager oMsgMgr;
        CrxConfigManager crxMgrObject;
        CrxDBManager dbMagr;
        BizPWV obj;
        BizPatient patientObj = BizPatient.Instance();
        CrxStructPWVMeasurementData crxPWV = new CrxStructPWVMeasurementData();
        int bobj = 31256; // systemid, since BIZ is not generating system id, hence hard coded as of Sprint 4
        string serverNameString = string.Empty;
        string dateWithComma = string.Empty; // used to get comma separated date string to delete assessment
        int recordsToDelete = 0;
        private DefaultWindow objDefaultWindow;
        bool oneRecordSelect = true;

        /**Constructor of the form,initializes all the controls.
       * */
        public Report()
        {
           InitializeComponent();
           InitializeReportScreen();
           SetTextForReportScreen();

           // initialize servername string
           serverNameString = SettingsProperties.ServerNameString();
           obj = (BizPWV)BizSession.Instance().measurement;
           DefaultWindow.OnReportTabClick += new EventHandler(Report_Load);
           AtCor.Scor.Gui.Presentation.Capture.OnReportTabClick += new EventHandler(Report_Load);            
        }

        /** Parameterized Constructor of the form,initializes all the controls.
      * */
        public Report(DefaultWindow defWindow)
        {
            try
            {                
                InitializeComponent();
                InitializeReportScreen();

                // set the default window
                objDefaultWindow = defWindow;
                SetTextForReportScreen();

                // initialize servername string
                serverNameString = SettingsProperties.ServerNameString();
                obj = (BizPWV)BizSession.Instance().measurement;

                // subscribe report tab click event
                DefaultWindow.OnReportTabClick += new EventHandler(Report_Load);
                AtCor.Scor.Gui.Presentation.Capture.OnReportTabClick += new EventHandler(Report_Load);
            }
            catch (Exception ex)
            {
                GUIExceptionHandler.HandleException(ex, this);
            }

            /* catch (CrxException crxex)
            {
                 RadMessageBox.Show(this, oMsgMgr.GetMessage(crxex.ErrorString), oMsgMgr.GetMessage("SYSTEM_ERROR"), MessageBoxButtons.OK, RadMessageIcon.Error);
            } */
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

            this.UseWaitCursor = true;
            SettingsProperties.CaptureToSetup = false;
            SettingsProperties.SystemIdentifier = bobj;
            InitializeReportAssessmentList(sender, e);
           
            SetDefaultValuesOnLoad(sender, e);

            // fill demographic & pwv measurement details & bring the LHS to browse mode
            FillDemographicDetailsReport(sender, e);

            // vibhuti: initialize crx when user moves from setup to report... call populate method
             InitializeCrxFromSetupToReport(string.Empty); // vibhuti
 
            // binds assessment details related to patient
            FillPatientAssessmentDetailsReport(sender, e);            
            
            OnReportScreenLoadComplere.Invoke(this, new EventArgs());
            this.UseWaitCursor = false;
        }

        /** This method set default options for buttons on report screen & calculates patients age
         * */
        private void SetDefaultValuesOnLoad(object sender, EventArgs e)
        {
            // make only edit button visible
            guiradbtnreportcancel.Visible = false;
            guiradbtnreportedit.Visible = true;
            guiradbtnreportsave.Visible = false;

            obj.CalculateAge();
            objDefaultWindow.radlblMessage.Text = string.Empty;
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
                guiradlblCarotid.Text = oMsgMgr.GetMessage("LBL_REPORT_CAROTID_WITHCOLON");
                guiradlblReportCuff.Text = oMsgMgr.GetMessage("LBL_REPORT_CUFF_WITHCOLON");
                guiradlblReportFemoToCuff.Text = oMsgMgr.GetMessage("LABEL_FEMORAL_CUFF");               
            }            
            catch (Exception ex)
            {
                GUIExceptionHandler.HandleException(ex, this);
            }

            /* catch (CrxException cfgExp)
             {
                 // Exception if any will be logged and displayed(appropiate message) to the user.                  
                 CrxMessagingManager oMsgMgr = CrxMessagingManager.Instance;
                 string errorMessage = oMsgMgr.GetMessage(cfgExp.ErrorCode);

                 // show error on screen                 
                 RadMessageBox.Show(this, oMsgMgr.GetMessage(cfgExp.ErrorString), oMsgMgr.GetMessage("SYSTEM_ERROR"), MessageBoxButtons.OK, RadMessageIcon.Error);

                 // write message in log file                
                 CrxLogger oLogObject = CrxLogger.Instance;
                 oLogObject.Write(errorMessage);
             }*/
        }

        /** This method enforces wait interval for 30 secs when navigated to report from capture screen
         * */
        private void StartWaitInterval()
        {
            if (!SettingsProperties.SetupToReport)
            {
                // read timer interval from config & start timer to enforce wait interval
                timer1.Interval = int.Parse(ConfigurationManager.AppSettings["WaitInterval"].ToString());
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
                    guiradlblCarotid.Text = oMsgMgr.GetMessage("REPORT_LBL_CAROTID");
                    guiradlblReportCuff.Visible = true;
                    guiradtxtReportCuff.Visible = true;
                    guiradlblReportCuffUnits.Visible = true;
                    guiradlblReportFemoToCuff.Visible = true;
                    guiradtxtReportFemoToCuff.Visible = true;
                    guiradlblCarotid.Visible = true;

                    // guiradlblCarotid.Text = oMsgMgr.GetMessage("REPORT_LBL_CAROTID"); 
                    guiradtxtCarotid.Visible = true;
                    guiradlblCarotidUnits.Visible = true;
                    guiradlblReportFemoralCuffUnits.Visible = true;
                    guiradlblReportPwvDistanceMethodType.Text = oMsgMgr.GetMessage("REPORT_LBL_SUBTRACTING");
                    guiradtxtReportCuff.Text = obj.myCuffDistance.distance.Equals(9999) ? string.Empty : obj.myCuffDistance.distance.ToString();
                    guiradtxtCarotid.Text = obj.myCarotidDistance.distance.Equals(9999) ? string.Empty : obj.myCarotidDistance.distance.ToString();
                    break;
                case 1:
                    // direct
                    // display & populate direct & femoral to cuff textboxes
                    guiradlblCarotid.Text = oMsgMgr.GetMessage("REPORT_LBL_DIRECT");
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
                    guiradtxtCarotid.Text = obj.myPWVDirectDistance.distance.Equals(9999) ? string.Empty : obj.myPWVDirectDistance.distance.ToString();
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

                        guiradtxtReportBloodPressure1.Text = (obj.bloodPressure.SP == null || obj.bloodPressure.SP.Reading.ToString().Equals("9999")) ? string.Empty : obj.bloodPressure.SP.Reading.ToString();
                        guiradtxtReportBloodPressure2.Text = (obj.bloodPressure.DP == null || obj.bloodPressure.DP.Reading.ToString().Equals("9999")) ? string.Empty : obj.bloodPressure.DP.Reading.ToString();
                        break;
                    case 1:
                        // SP & MP
                        guiradlblReportBloodPressure1.Text = oMsgMgr.GetMessage("LABEL_SP"); // used for internal checking while changing settings.
                        guiradlblBloodPressure2.Text = oMsgMgr.GetMessage("LABEL_MP"); // used for internal checking while changing settings.

                        guiradtxtReportBloodPressure1.Text = (obj.bloodPressure.SP == null || obj.bloodPressure.SP.Reading.ToString().Equals("9999")) ? string.Empty : obj.bloodPressure.SP.Reading.ToString();
                        guiradtxtReportBloodPressure2.Text = (obj.bloodPressure.MP == null || obj.bloodPressure.MP.Reading.ToString().Equals("9999")) ? string.Empty : obj.bloodPressure.MP.Reading.ToString();
                        break;
                    case 2:
                        // MP & DP
                        guiradlblReportBloodPressure1.Text = oMsgMgr.GetMessage("LABEL_MP"); // used for internal checking while changing settings.
                        guiradlblBloodPressure2.Text = oMsgMgr.GetMessage("LABEL_DP"); // used for internal checking while changing settings.

                        guiradtxtReportBloodPressure1.Text = (obj.bloodPressure.MP == null || obj.bloodPressure.MP.Reading.ToString().Equals("9999")) ? string.Empty : obj.bloodPressure.MP.Reading.ToString();
                        guiradtxtReportBloodPressure2.Text = (obj.bloodPressure.DP == null || obj.bloodPressure.DP.Reading.ToString().Equals("9999")) ? string.Empty : obj.bloodPressure.DP.Reading.ToString();
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
            guiradlblReportPwvDistanceMethodType.Text = obj.myCarotidDistance.distance.ToString().Equals("9999") ? oMsgMgr.GetMessage("REPORT_LBL_DIRECT") : oMsgMgr.GetMessage("REPORT_LBL_SUBTRACTING");
            guiradlblReportPwvDitanceUnits.Text = crxMgrObject.PwvSettings.PWVDistanceUnits.Equals(0) ? oMsgMgr.GetMessage("MM") : oMsgMgr.GetMessage("CM");

            // sets blood pressure display text in labels
            SetBloodPressureDisplayText();
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
                guilblReportPatientNameValue.Text = string.IsNullOrEmpty(patientObj.firstName) ? patientObj.lastName : patientObj.firstName + " " + patientObj.lastName;
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
                guiradgridReportAssessment.Columns[1].Width = 270;
                guiradgridReportAssessment.Columns[1].IsVisible = true;
                guiradgridReportAssessment.Columns[1].ReadOnly = true;

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
            
            guiradlblReportPwvDistanceMethodType.Text = obj.myCarotidDistance.distance.ToString().Equals("9999") ? oMsgMgr.GetMessage("REPORT_LBL_DIRECT") : oMsgMgr.GetMessage("REPORT_LBL_SUBTRACTING");
            guiradlblReportPwvDitanceUnits.Text = guiradlblReportPwvDitanceUnits1.Text = crxMgrObject.PwvSettings.PWVDistanceUnits.Equals(0) ? oMsgMgr.GetMessage("MM") : oMsgMgr.GetMessage("CM");
            
            guiradlblReportBmiValue.Text = obj.heightAndWeight.bodyMassIndex.ToString(); // hard coded as value not available in session

            guiradlblReportOperatordisplay.Text = obj.operatorId;
            guiradlblReportNotesDisplay.Text = obj.notes;

            // set display text for SP, DP & MP labels
            SetBloodPressureDisplayText();

            // calculates height & weight
            int heightInInches = 0;
            int heigthInFeet = 0;

            switch (crxMgrObject.GeneralSettings.HeightandWeightUnit)
            {
                case 0:

                    // 0.3937007874
                    if (obj.heightAndWeight.heightInCentimetres.ToString() == "9999") 
                    {
                        guiradlblReportHeightDisplay.Text = Math.Round(double.Parse(obj.heightAndWeight.heightInInches.ToString()) * 2.54, MidpointRounding.ToEven).ToString(); // convert height in centimeters to feet & inches
                    }
                    else
                    {
                        // convert height in inches to feet & inches
                        guiradlblReportHeightDisplay.Text = obj.heightAndWeight.heightInCentimetres.ToString();
                        guiradlblReportHeightInches.Text = obj.heightAndWeight.heightInInches.ToString(); 
                    }

                    guiradlblReportWeightUnits.Text = oMsgMgr.GetMessage("KG");
                    guiradlblReportHeightUnits.Text = oMsgMgr.GetMessage("CM");
                    
                    // convert weight in pounds to kilograms
                    guiradlblReportWeightdisplay.Text = obj.heightAndWeight.weightInKilograms.ToString().Equals("9999") ? Math.Round(double.Parse(obj.heightAndWeight.weightInPounds.ToString()) * 0.45359237, MidpointRounding.ToEven).ToString() : obj.heightAndWeight.weightInKilograms.ToString();
                  
                    break;
                case 1:

                    // 0.3937007874
                    if (obj.heightAndWeight.heightInInches.ToString() == "9999") 
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
                    guiradlblReportWeightdisplay.Text = obj.heightAndWeight.weightInPounds.ToString().Equals("9999") ? Math.Round(double.Parse(obj.heightAndWeight.weightInKilograms.ToString()) * 2.20462262, MidpointRounding.ToEven).ToString() : obj.heightAndWeight.weightInPounds.ToString();
                   
                    guiradlblReportWeightUnits.Text = oMsgMgr.GetMessage("LBS");
                    guiradlblReportHeightUnits.Text = oMsgMgr.GetMessage("FEET");
                    break;
            }

            // vibhuti: workaround code for binding statistics
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
            int heightInInches = 0;
            int heigthInFeet = 0;

            switch (crxMgrObject.GeneralSettings.HeightandWeightUnit)
            {
                case 0:

                    // 0.3937007874
                          // convert height in inches to feet & inches
                        guiradlblReportHeightDisplay.Text = obj.heightAndWeight.heightInCentimetres.ToString();
                        guiradlblReportHeightInches.Text = obj.heightAndWeight.heightInInches.ToString();
                    
                        // convert weight in pounds to kilograms
                    guiradlblReportWeightdisplay.Text = obj.heightAndWeight.weightInKilograms.ToString().Equals("9999") ? Math.Round(double.Parse(obj.heightAndWeight.weightInPounds.ToString()) * 0.45359237, MidpointRounding.ToEven).ToString() : obj.heightAndWeight.weightInKilograms.ToString();

                    break;
                case 1:

                    // 0.3937007874
                    if (obj.heightAndWeight.heightInInches.ToString() == "9999")
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
                    guiradlblReportWeightdisplay.Text = obj.heightAndWeight.weightInPounds.ToString().Equals("9999") ? Math.Round(double.Parse(obj.heightAndWeight.weightInKilograms.ToString()) * 2.20462262, MidpointRounding.ToEven).ToString() : obj.heightAndWeight.weightInPounds.ToString();

                    guiradlblReportWeightUnits.Text = oMsgMgr.GetMessage("LBS");
                    guiradlblReportHeightUnits.Text = oMsgMgr.GetMessage("FEET");
                    break;
            }

            // vibhuti: workaround code for binding statistics
            BindPWVStatistics();
        }

        /** Binds PWV statistics from db if not available in sesion object
         * */
        void BindPWVStatistics()
        {            
                guiradlblReportHeartRateValue.Text = obj.meanHeartRate.ToString() + " " + oMsgMgr.GetMessage("HEARTRATE_UNIT");
                guiradlblReportPWVValue.Text = obj.meanPulseWaveVelocity.ToString() + " " + oMsgMgr.GetMessage("PWV_UNIT");
                guiradlblStdDeviationImage.ImageIndex = obj.isStandardDeviationValid ? 1 : 0;
                guiradlblReportFemoralImage.ImageIndex = obj.isFemoralSignalValid ? 1 : 0;
                guiradlblReportCarotidImage.ImageIndex = obj.isCarotidSignalValid ? 1 : 0;           
        }

        /** This method fill statistics in biz session
         * */
        void FillSessionWithStatistics(DataSet dsPWV)
        {
            obj.meanHeartRate = string.IsNullOrEmpty(dsPWV.Tables[0].Rows[0]["MeanHeartRate"].ToString()) ? (float)0 : float.Parse(dsPWV.Tables[0].Rows[0]["MeanHeartRate"].ToString());
            obj.meanPulseWaveVelocity = string.IsNullOrEmpty(dsPWV.Tables[0].Rows[0]["MeanPulseWaveVelocity"].ToString()) ? (float)0 : float.Parse(dsPWV.Tables[0].Rows[0]["MeanPulseWaveVelocity"].ToString());
            obj.isStandardDeviationValid = string.IsNullOrEmpty(dsPWV.Tables[0].Rows[0]["IsStandardDeviationValid"].ToString()) ? false : bool.Parse(dsPWV.Tables[0].Rows[0]["IsStandardDeviationValid"].ToString());
            obj.isCarotidSignalValid = string.IsNullOrEmpty(dsPWV.Tables[0].Rows[0]["IsCarotidSignalValid"].ToString()) ? false : bool.Parse(dsPWV.Tables[0].Rows[0]["IsCarotidSignalValid"].ToString());
            obj.isFemoralSignalValid = string.IsNullOrEmpty(dsPWV.Tables[0].Rows[0]["IsFemoralSignalValid"].ToString()) ? false : bool.Parse(dsPWV.Tables[0].Rows[0]["IsFemoralSignalValid"].ToString());
        }
        
        /**This method fill assessment details for a particular patient
        * */
        void FillPatientAssessmentDetailsReport(object sender, EventArgs e)
        {
            // check db connection
            if (dbMagr.CheckConnection(serverNameString, crxMgrObject.GeneralSettings.SourceData) == 0)
            {
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
                    guiradgridReportAssessment.MasterGridViewTemplate.Rows[0].Cells[0].Value = true;
                    guiradbtnDelete.Enabled = true;
                    guiradbtnPrint.Enabled = true;                    

                    // this will populate biz session obj from latest PWV details
                    InitializeCrxOnLoad(string.Empty); // vibhuti: commented for workaround
                    // // workaround method
                   // FillSessionForSelectedAssessment(guiradgridReportAssessment.MasterGridViewTemplate.Rows[0].Cells[1].Value.ToString());
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
                    guiradlblReportAssesmentCount.Text = "[" + ds.Tables[0].Rows.Count.ToString() + " " + oMsgMgr.GetMessage("REPORT_ASSESMENT_RECORD_COUNT") + " " + ds.Tables[0].Rows.Count.ToString() + "]";
                }
            }
            else
            {
                DialogResult result = RadMessageBox.Show(this, SettingsProperties.ConnectionErrorString(), oMsgMgr.GetMessage("SYSTEM_ERROR"), MessageBoxButtons.RetryCancel, RadMessageIcon.Error);
                if (result == DialogResult.Retry)
                {
                    FillPatientAssessmentDetailsReport(sender, e);
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
                    guiradlblreportSPdisplay.Text = obj.bloodPressure.SP.Reading.Equals(9999) ? string.Empty : obj.bloodPressure.SP.Reading.ToString();
                    guiradlblReportBloodPressure2.Text = obj.bloodPressure.DP.Reading.Equals(9999) ? string.Empty : obj.bloodPressure.DP.Reading.ToString();
                    break;
                case 1:
                    // sp & mp
                    guiradlblReportBloodPressure1.Text = oMsgMgr.GetMessage("LABEL_SP"); // hardcoded for internal use while changing user settings.
                    guiradlblBloodPressure2.Text = oMsgMgr.GetMessage("LABEL_MP"); // hardcoded for internal use while changing user settings.
                    guiradlblreportSPdisplay.Text = obj.bloodPressure.SP.Reading.Equals(9999) ? string.Empty : obj.bloodPressure.SP.Reading.ToString();
                    guiradlblReportBloodPressure2.Text = obj.bloodPressure.MP.Reading.Equals(9999) ? string.Empty : obj.bloodPressure.MP.Reading.ToString();
                    break;
                case 2:
                    // mp & dp
                    guiradlblReportBloodPressure1.Text = oMsgMgr.GetMessage("LABEL_MP"); // hardcoded for internal use while changing user settings.
                    guiradlblBloodPressure2.Text = oMsgMgr.GetMessage("LABEL_DP"); // hardcoded for internal use while changing user settings.
                    guiradlblreportSPdisplay.Text = obj.bloodPressure.MP.Reading.Equals(9999) ? string.Empty : obj.bloodPressure.MP.Reading.ToString();
                    guiradlblReportBloodPressure2.Text = obj.bloodPressure.DP.Reading.Equals(9999) ? string.Empty : obj.bloodPressure.DP.Reading.ToString();
                    break;
            }
            
           // CheckBloodPressure();
        }

        /** This method checks for blood pressure values & accordingly displays text (Normal BP) on reference range graph
         * */
        private void CheckBloodPressure()
        {
            if ((obj.bloodPressure.SP.Reading.Equals(9999) && obj.bloodPressure.DP.Reading.Equals(9999)) ||

            (obj.bloodPressure.SP.Reading.Equals(9999) && obj.bloodPressure.MP.Reading.Equals(9999)) ||

            (obj.bloodPressure.DP.Reading.Equals(9999) && obj.bloodPressure.MP.Reading.Equals(9999)))
            {
                guiradlblReportBpRange.Visible = false;
            }
            else
            {
                guiradlblReportBpRange.Visible = true;
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
                            int iRow = 0;
                            crxPWV.StudyDateTime = DateTime.Parse(SettingsProperties.PwvCurrentStudyDatetime);
                            if (guiradgridReportAssessment.Rows.Count > 0)
                            {                               
                                iRow = dbMagr.UpdatePWVMeasurementDetails(crxPWV);
                            }
                            else
                            {
                                iRow = dbMagr.SavePWVMeasurementDetails(crxPWV);
                            }

                            if (iRow > 0)
                            {
                                // record updated successfully
                                // populate session object                   
                               // FillSessionObjAfterEdit(crxPWV);

                                // get th latest date from crxPWV with which data is updated
                                SettingsProperties.PwvCurrentStudyDatetime = crxPWV.StudyDateTime.ToString();

                                FillPatientAssessmentDetailsReport(sender, e);
                                guiradlblReportPwvDistance.Text = oMsgMgr.GetMessage("LABEL_PWV_DISTANCE");

                                // re populate label fields again and display mode = true
                                ReportPWVDisplayMode(true);
                                guiradbtnreportcancel.Visible = false;
                                guiradbtnreportedit.Visible = true;
                                guiradbtnreportsave.Visible = false;
                                OnPWVMeasurementChangedEvent.Invoke(this, new EventArgs());
                            }

                            break;
                        case 1:
                            // obj validation failed                            
                             RadMessageBox.Show(this, oMsgMgr.GetMessage("ERROR_VALIDATING"), oMsgMgr.GetMessage("SYSTEM_ERROR"), MessageBoxButtons.OK, RadMessageIcon.Error);
                             break;
                        case 2:
                            // report calculation failed
                            RadMessageBox.Show(this, oMsgMgr.GetMessage("REPORT_CALCULATE_ERROR"), oMsgMgr.GetMessage("SYSTEM_ERROR"), MessageBoxButtons.OK, RadMessageIcon.Error);                
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

            /* catch (CrxException ex)
           {
              // GUIExceptionHandler excep = new GUIExceptionHandler(ex, this);
               RadMessageBox.Show(this, ex.ErrorString, oMsgMgr.GetMessage("SYSTEM_ERROR"), MessageBoxButtons.OK, RadMessageIcon.Error);
               CrxLogger oLogObject = CrxLogger.Instance;
               oLogObject.Write(ex.ErrorString);
           } */
        }

        /**This method initializes Crx structure to update changes
      * */
        void InitializeCrxOnLoad(string studydatetime)
        {
            try
            {
                // if (SettingsProperties.SetupToReport)
                // {
                    DataSet dsPWV = new DataSet();

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
                            SettingsProperties.PwvCurrentStudyDatetime = dsPWV.Tables[0].Rows[0]["Studydatetime"].ToString();
                            obj = (BizPWV)BizSession.Instance().measurement;

                            int len = 0;
                            byte[] buffer = (byte[])dsPWV.Tables[0].Rows[0]["NormalRange"];

                            len = buffer.Length / 4;
                            ////ushort[] carotid1 = new ushort[len];
                            crxPWV.NormalRange = dbMagr.CommonByteArrtoFloatArr(len, buffer);

                            buffer = (byte[])dsPWV.Tables[0].Rows[0]["ReferenceRange"];

                            len = buffer.Length / 4;
                            crxPWV.ReferenceRange = dbMagr.CommonByteArrtoFloatArr(len, buffer);
                             
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
                         /*   application = new Microsoft.Office.Interop.Excel.ApplicationClass();
                            book = application.Workbooks.Open(ConfigurationManager.AppSettings["XcelPath"].ToString(), 0, true, 5, string.Empty, string.Empty, false, Microsoft.Office.Interop.Excel.XlPlatform.xlWindows, string.Empty, true, false, 0, true, false, false);

                            sheet = (Microsoft.Office.Interop.Excel.Worksheet)book.Worksheets[1];

                            //// obj1.myPWVDirectDistance.distance = Convert.ToUInt16(((Microsoft.Office.Interop.Excel.Range)sheet.Cells[2, 8]).Value2.ToString());
                            string femoral = ((Microsoft.Office.Interop.Excel.Range)sheet.Cells[2, 12]).Value2.ToString();
                            string carotid = ((Microsoft.Office.Interop.Excel.Range)sheet.Cells[2, 11]).Value2.ToString();
                            ushort signalLength = Convert.ToUInt16(((Microsoft.Office.Interop.Excel.Range)sheet.Cells[2, 10]).Value2.ToString());
                            //// obj1.PrepareToCaptureSignal();
                            string[] femoralValuesArray = new string[5120];
                            femoralValuesArray = femoral.Split(',');
                            ushort[] femoralSignal = Array.ConvertAll(femoralValuesArray, new Converter<string, ushort>(Convert.ToUInt16));
                            obj.femoralSignal.CaptureSignal(femoralSignal, (ushort)signalLength, 0, (ushort)(signalLength - 1));

                            string[] carotidValuesArray = new string[5120];
                            carotidValuesArray = carotid.Split(',');
                            ushort[] carotidSignal = Array.ConvertAll(carotidValuesArray, new Converter<string, ushort>(Convert.ToUInt16));
                            obj.carotidSignal.CaptureSignal(carotidSignal, (ushort)signalLength, 0, (ushort)(signalLength - 1));
                            bool status = obj.Calculate();

                            if (obj.Calculate())
                            {
                                ushort[] femoralSignalToPlot = obj.femoralSignal.signal;
                                float[] femoralOnSetPoints = obj.femoralSignal.floatOnsets;
                                ushort femoralOnSetPointLength = obj.femoralSignal.onsetsLength;
                                ushort[] carotidSignalToPlot = obj.carotidSignal.signal;
                                float[] carotidOnSetPoints = obj.carotidSignal.floatOnsets;
                                ushort carotidOnSetPointLenth = obj.carotidSignal.onsetsLength;

                                int len = 0;
                                byte[] buffer = (byte[])dsPWV.Tables[0].Rows[0]["NormalRange"];

                                len = buffer.Length / 4;
                                ////ushort[] carotid1 = new ushort[len];
                                crxPWV.NormalRange = dbMagr.CommonByteArrtoFloatArr(len, buffer);

                                buffer = (byte[])dsPWV.Tables[0].Rows[0]["ReferenceRange"];

                                len = buffer.Length / 4;
                                crxPWV.ReferenceRange = dbMagr.CommonByteArrtoFloatArr(len, buffer);

                                // buffer = (byte[])dsPWV.Tables[0].Rows[0]["CarotidSignal"];

                                // len = buffer.Length / 2;
                                crxPWV.CarotidSignal = carotidSignalToPlot; // dbMagr.CommonByteArrtoShortArr(len, buffer);
                                crxPWV.CarotidSignalLength = short.Parse(carotidSignalToPlot.Length.ToString()); // (short)len;

                                // buffer = (byte[])dsPWV.Tables[0].Rows[0]["FemoralSignal"];
                                // len = buffer.Length / 2;
                                crxPWV.FemoralSignal = femoralSignalToPlot; // dbMagr.CommonByteArrtoShortArr(len, buffer);
                                crxPWV.FemoralSignalLength = short.Parse(femoralSignalToPlot.Length.ToString()); // (short)len;

                                // buffer = (byte[])dsPWV.Tables[0].Rows[0]["CarotidSignalFloatOnSets"];
                                // len = buffer.Length / 4;
                                crxPWV.CarotidSignalFloatOnSets = carotidOnSetPoints; // dbMagr.CommonByteArrtoFloatArr(len, buffer);
                                crxPWV.CarotidSignalOnSetsLength = short.Parse(carotidOnSetPoints.Length.ToString()); // (short)len;

                                // buffer = (byte[])dsPWV.Tables[0].Rows[0]["FemoralSignalFloatOnSets"];
                                // len = buffer.Length / 4;
                                crxPWV.FemoralSignalFloatOnSets = femoralOnSetPoints; // dbMagr.CommonByteArrtoFloatArr(len, buffer);
                                crxPWV.FemoralSignalOnSetsLength = short.Parse(femoralOnSetPoints.Length.ToString()); // (short)len;                           
                            }
                            else
                            {
                                crxPWV.NormalRange = new float[0];
                                crxPWV.ReferenceRange = new float[0];
                                crxPWV.CarotidSignal = new ushort[0];
                                crxPWV.FemoralSignal = new ushort[0];
                                crxPWV.CarotidSignalFloatOnSets = new float[0];
                                crxPWV.FemoralSignalFloatOnSets = new float[0];
                            }
                            */
                            PopulateCrxWithOtherValues(dsPWV);

                            // populating other details
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
                            InitializeCrxOnLoad(studydatetime);
                        }
                    }

               // }
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
                            SettingsProperties.PwvCurrentStudyDatetime = dsPWV.Tables[0].Rows[0]["Studydatetime"].ToString();
                            obj = (BizPWV)BizSession.Instance().measurement;

                            int len = 0;
                            byte[] buffer = (byte[])dsPWV.Tables[0].Rows[0]["NormalRange"];

                            len = buffer.Length / 4;
                            ////ushort[] carotid1 = new ushort[len];
                            crxPWV.NormalRange = dbMagr.CommonByteArrtoFloatArr(len, buffer);

                            buffer = (byte[])dsPWV.Tables[0].Rows[0]["ReferenceRange"];

                            len = buffer.Length / 4;
                            crxPWV.ReferenceRange = dbMagr.CommonByteArrtoFloatArr(len, buffer);

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
                            /*   application = new Microsoft.Office.Interop.Excel.ApplicationClass();
                               book = application.Workbooks.Open(ConfigurationManager.AppSettings["XcelPath"].ToString(), 0, true, 5, string.Empty, string.Empty, false, Microsoft.Office.Interop.Excel.XlPlatform.xlWindows, string.Empty, true, false, 0, true, false, false);

                               sheet = (Microsoft.Office.Interop.Excel.Worksheet)book.Worksheets[1];

                               //// obj1.myPWVDirectDistance.distance = Convert.ToUInt16(((Microsoft.Office.Interop.Excel.Range)sheet.Cells[2, 8]).Value2.ToString());
                               string femoral = ((Microsoft.Office.Interop.Excel.Range)sheet.Cells[2, 12]).Value2.ToString();
                               string carotid = ((Microsoft.Office.Interop.Excel.Range)sheet.Cells[2, 11]).Value2.ToString();
                               ushort signalLength = Convert.ToUInt16(((Microsoft.Office.Interop.Excel.Range)sheet.Cells[2, 10]).Value2.ToString());
                               //// obj1.PrepareToCaptureSignal();
                               string[] femoralValuesArray = new string[5120];
                               femoralValuesArray = femoral.Split(',');
                               ushort[] femoralSignal = Array.ConvertAll(femoralValuesArray, new Converter<string, ushort>(Convert.ToUInt16));
                               obj.femoralSignal.CaptureSignal(femoralSignal, (ushort)signalLength, 0, (ushort)(signalLength - 1));

                               string[] carotidValuesArray = new string[5120];
                               carotidValuesArray = carotid.Split(',');
                               ushort[] carotidSignal = Array.ConvertAll(carotidValuesArray, new Converter<string, ushort>(Convert.ToUInt16));
                               obj.carotidSignal.CaptureSignal(carotidSignal, (ushort)signalLength, 0, (ushort)(signalLength - 1));
                               bool status = obj.Calculate();

                               if (obj.Calculate())
                               {
                                   ushort[] femoralSignalToPlot = obj.femoralSignal.signal;
                                   float[] femoralOnSetPoints = obj.femoralSignal.floatOnsets;
                                   ushort femoralOnSetPointLength = obj.femoralSignal.onsetsLength;
                                   ushort[] carotidSignalToPlot = obj.carotidSignal.signal;
                                   float[] carotidOnSetPoints = obj.carotidSignal.floatOnsets;
                                   ushort carotidOnSetPointLenth = obj.carotidSignal.onsetsLength;

                                   int len = 0;
                                   byte[] buffer = (byte[])dsPWV.Tables[0].Rows[0]["NormalRange"];

                                   len = buffer.Length / 4;
                                   ////ushort[] carotid1 = new ushort[len];
                                   crxPWV.NormalRange = dbMagr.CommonByteArrtoFloatArr(len, buffer);

                                   buffer = (byte[])dsPWV.Tables[0].Rows[0]["ReferenceRange"];

                                   len = buffer.Length / 4;
                                   crxPWV.ReferenceRange = dbMagr.CommonByteArrtoFloatArr(len, buffer);

                                   // buffer = (byte[])dsPWV.Tables[0].Rows[0]["CarotidSignal"];

                                   // len = buffer.Length / 2;
                                   crxPWV.CarotidSignal = carotidSignalToPlot; // dbMagr.CommonByteArrtoShortArr(len, buffer);
                                   crxPWV.CarotidSignalLength = short.Parse(carotidSignalToPlot.Length.ToString()); // (short)len;

                                   // buffer = (byte[])dsPWV.Tables[0].Rows[0]["FemoralSignal"];
                                   // len = buffer.Length / 2;
                                   crxPWV.FemoralSignal = femoralSignalToPlot; // dbMagr.CommonByteArrtoShortArr(len, buffer);
                                   crxPWV.FemoralSignalLength = short.Parse(femoralSignalToPlot.Length.ToString()); // (short)len;

                                   // buffer = (byte[])dsPWV.Tables[0].Rows[0]["CarotidSignalFloatOnSets"];
                                   // len = buffer.Length / 4;
                                   crxPWV.CarotidSignalFloatOnSets = carotidOnSetPoints; // dbMagr.CommonByteArrtoFloatArr(len, buffer);
                                   crxPWV.CarotidSignalOnSetsLength = short.Parse(carotidOnSetPoints.Length.ToString()); // (short)len;

                                   // buffer = (byte[])dsPWV.Tables[0].Rows[0]["FemoralSignalFloatOnSets"];
                                   // len = buffer.Length / 4;
                                   crxPWV.FemoralSignalFloatOnSets = femoralOnSetPoints; // dbMagr.CommonByteArrtoFloatArr(len, buffer);
                                   crxPWV.FemoralSignalOnSetsLength = short.Parse(femoralOnSetPoints.Length.ToString()); // (short)len;                           
                               }
                               else
                               {
                                   crxPWV.NormalRange = new float[0];
                                   crxPWV.ReferenceRange = new float[0];
                                   crxPWV.CarotidSignal = new ushort[0];
                                   crxPWV.FemoralSignal = new ushort[0];
                                   crxPWV.CarotidSignalFloatOnSets = new float[0];
                                   crxPWV.FemoralSignalFloatOnSets = new float[0];
                               }
                               */
                            PopulateCrxWithOtherValues(dsPWV);

                            // populating other details
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
                            InitializeCrxOnLoad(studydatetime);
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
        void PopulateCrxWithOtherValues(DataSet dsPWV)
        {
            crxPWV.HeightInCentimetres = (short)dsPWV.Tables[0].Rows[0]["HeightInCentimetres"];
            crxPWV.HeightInInches = (short)dsPWV.Tables[0].Rows[0]["HeightInInches"];
            crxPWV.WeightInKilograms = (short)dsPWV.Tables[0].Rows[0]["WeightInKilograms"];
            crxPWV.WeightInPounds = (short)dsPWV.Tables[0].Rows[0]["WeightInPounds"];

            crxPWV.BodyMassIndex = float.Parse(dsPWV.Tables[0].Rows[0]["BodyMassIndex"].ToString());
            crxPWV.Operator = dsPWV.Tables[0].Rows[0]["Operator"].ToString();
            crxPWV.Notes = dsPWV.Tables[0].Rows[0]["Notes"].ToString();
            crxPWV.BloodPressureEntryOption = short.Parse(dsPWV.Tables[0].Rows[0]["BloodPressureEntryOption"].ToString());

            // sets SP, DP & MP value
            switch (crxPWV.BloodPressureEntryOption)
            {
                case 0: // hardcoded for internal use.
                    // sp & dp
                    crxPWV.SP = short.Parse(dsPWV.Tables[0].Rows[0]["SP"].ToString());
                    crxPWV.DP = short.Parse(dsPWV.Tables[0].Rows[0]["DP"].ToString());
                    crxPWV.MP = 9999;
                    break;
                case 1: // hardcoded for internal use.
                    // sp & mp
                    crxPWV.SP = short.Parse(dsPWV.Tables[0].Rows[0]["SP"].ToString());
                    crxPWV.DP = 9999;
                    crxPWV.MP = short.Parse(dsPWV.Tables[0].Rows[0]["MP"].ToString());
                    break;
                case 2:
                    // dp & mp
                    crxPWV.SP = 9999;
                    crxPWV.MP = short.Parse(dsPWV.Tables[0].Rows[0]["MP"].ToString());
                    crxPWV.DP = short.Parse(dsPWV.Tables[0].Rows[0]["DP"].ToString());
                    break;
            }

            crxPWV.PWVDistanceMethod = short.Parse(dsPWV.Tables[0].Rows[0]["PWVDistanceMethod"].ToString());
            crxPWV.PWVDistance = short.Parse(dsPWV.Tables[0].Rows[0]["PWVDistance"].ToString());
            crxPWV.Direct = short.Parse(dsPWV.Tables[0].Rows[0]["Direct"].ToString());
            crxPWV.Carotid = short.Parse(dsPWV.Tables[0].Rows[0]["Carotid"].ToString());
            crxPWV.Cuff = short.Parse(dsPWV.Tables[0].Rows[0]["Cuff"].ToString());
            crxPWV.FemoraltoCuff = short.Parse(dsPWV.Tables[0].Rows[0]["FemoraltoCuff"].ToString());

            crxPWV.SystemIdentifier = bobj;
            crxPWV.GroupIdentifier = int.Parse(patientObj.groupStudyId.ToString());
            crxPWV.PatientNumberInternal = int.Parse(patientObj.patientNumber.ToString());
        }

        /** This method fills crx struct with statistics data
         * */
        void PopulateCrxWithStatistics(DataSet dsPWV)
        {
            crxPWV.Simulation = bool.Parse(dsPWV.Tables[0].Rows[0]["Simulation"].ToString());
            crxPWV.BloodPressureRange = dsPWV.Tables[0].Rows[0]["BloodPressureRange"].ToString();
            crxPWV.Age = short.Parse(dsPWV.Tables[0].Rows[0]["Age"].ToString());
            crxPWV.IsStandardDeviationValid = bool.Parse(dsPWV.Tables[0].Rows[0]["IsStandardDeviationValid"].ToString());
            crxPWV.IsFemoralSignalValid = bool.Parse(dsPWV.Tables[0].Rows[0]["IsFemoralSignalValid"].ToString());
            crxPWV.IsCarotidSignalValid = bool.Parse(dsPWV.Tables[0].Rows[0]["IsCarotidSignalValid"].ToString());
            crxPWV.CaptureTime = short.Parse(dsPWV.Tables[0].Rows[0]["CaptureTime"].ToString());
            crxPWV.MeanCorrectedTime = float.Parse(dsPWV.Tables[0].Rows[0]["MeanCorrectedTime"].ToString());
            crxPWV.MeanDeltaTime = float.Parse(dsPWV.Tables[0].Rows[0]["MeanDeltaTime"].ToString());
            crxPWV.MeanHeartRate = float.Parse(dsPWV.Tables[0].Rows[0]["MeanHeartRate"].ToString());
            crxPWV.MeanPulseWaveVelocity = float.Parse(dsPWV.Tables[0].Rows[0]["MeanPulseWaveVelocity"].ToString());
            crxPWV.SampleRate = short.Parse(dsPWV.Tables[0].Rows[0]["SampleRate"].ToString());
            crxPWV.StandardDeviation = float.Parse(dsPWV.Tables[0].Rows[0]["StandardDeviation"].ToString());
            crxPWV.CarotidSignalPulseHeight = float.Parse(dsPWV.Tables[0].Rows[0]["CarotidSignalPulseHeight"].ToString());
            crxPWV.CarotidSignalPulseHeightVariation = float.Parse(dsPWV.Tables[0].Rows[0]["CarotidSignalPulseHeightVariation"].ToString());
            crxPWV.CorrectionTime = float.Parse(dsPWV.Tables[0].Rows[0]["CorrectionTime"].ToString());
            crxPWV.DataRevision = short.Parse(dsPWV.Tables[0].Rows[0]["DataRevision"].ToString());
            crxPWV.FemoralSignalPulseHeight = float.Parse(dsPWV.Tables[0].Rows[0]["FemoralSignalPulseHeight"].ToString());
            crxPWV.NumberOfDeltas = short.Parse(dsPWV.Tables[0].Rows[0]["NumberOfDeltas"].ToString());
            crxPWV.NumberOfValidDeltas = short.Parse(dsPWV.Tables[0].Rows[0]["NumberOfValidDeltas"].ToString());
        }

        /**This method initializes Crx structure to update changes
        * */
        int InitializeCrx(CrxStructPWVMeasurementData crxPWV)
        {
            int flag = 0;

            // populate obj with entered data & check for validation
            // if it returns true then initialize crxPWV else return error & repopluate obj with original values

            // vibhuti: to be removed on
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

                crxPWV.BodyMassIndex = float.Parse(guiradlblReportBmiValue.Text);
                crxPWV.Operator = guiradtxtReportOperator.Text.Trim();
                crxPWV.Notes = guiradtxtReportNotes.Text.Trim();
                crxPWV.BloodPressureEntryOption = short.Parse(crxMgrObject.GeneralSettings.BloodPressureEntryOptions.ToString());

                // sets SP, DP & MP value
                switch (crxPWV.BloodPressureEntryOption)
                {
                    case 0: // hardcoded for internal use.
                        // sp & dp
                        crxPWV.SP = string.IsNullOrEmpty(guiradtxtReportBloodPressure1.Text.Trim()) ? (short)9999 : short.Parse(guiradtxtReportBloodPressure1.Text.Trim());
                        crxPWV.DP = string.IsNullOrEmpty(guiradtxtReportBloodPressure2.Text.Trim()) ? (short)9999 : short.Parse(guiradtxtReportBloodPressure2.Text.Trim());
                        crxPWV.MP = 9999;
                        break;
                    case 1: // hardcoded for internal use.
                        // sp & mp
                        crxPWV.SP = string.IsNullOrEmpty(guiradtxtReportBloodPressure1.Text.Trim()) ? (short)9999 : short.Parse(guiradtxtReportBloodPressure1.Text.Trim());
                        crxPWV.DP = 9999;
                        crxPWV.MP = string.IsNullOrEmpty(guiradtxtReportBloodPressure2.Text.Trim()) ? (short)9999 : short.Parse(guiradtxtReportBloodPressure2.Text.Trim());
                        break;
                    case 2:
                        // dp & mp
                        crxPWV.SP = 9999;
                        crxPWV.MP = string.IsNullOrEmpty(guiradtxtReportBloodPressure1.Text.Trim()) ? (short)9999 : short.Parse(guiradtxtReportBloodPressure1.Text.Trim());
                        crxPWV.DP = string.IsNullOrEmpty(guiradtxtReportBloodPressure2.Text.Trim()) ? (short)9999 : short.Parse(guiradtxtReportBloodPressure2.Text.Trim());
                        break;
                }

                CalculatePwvDistanceToUpdate(crxPWV);

                crxPWV.SystemIdentifier = bobj;
                crxPWV.GroupIdentifier = SettingsProperties.GroupID;
                crxPWV.PatientNumberInternal = SettingsProperties.PatientInternalNumber;

                BizPatient patientObj = BizPatient.Instance();

                // obj.RecalculatePWVReport();
                // vibhuti: call recalculatepwvreport which will calculate PWV statistics & normal range values & will update biz session object.
                // after this call populate crxPWV with statistics & pwv value to update database.
                
                // vibhuti to be removed once recalculate method is working
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

                // current workaround for functionality to work
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

        /** This method validates session data
         * */
        bool ValidateSession()
        {            
            obj.heightAndWeight.bodyMassIndex = float.Parse(guiradlblReportBmiValue.Text);
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
                    obj.bloodPressure.SP.Reading = string.IsNullOrEmpty(guiradtxtReportBloodPressure1.Text.Trim()) ? (ushort)9999 : ushort.Parse(guiradtxtReportBloodPressure1.Text.Trim());
                    obj.bloodPressure.DP.Reading = string.IsNullOrEmpty(guiradtxtReportBloodPressure2.Text.Trim()) ? (ushort)9999 : ushort.Parse(guiradtxtReportBloodPressure2.Text.Trim());
                    obj.bloodPressure.MP.Reading = 9999;
                    break;
                case 1: // hardcoded for internal use.
                    // sp & mp
                    obj.bloodPressure.SP.Reading = string.IsNullOrEmpty(guiradtxtReportBloodPressure1.Text.Trim()) ? (ushort)9999 : ushort.Parse(guiradtxtReportBloodPressure1.Text.Trim());
                    obj.bloodPressure.DP.Reading = 9999;
                    obj.bloodPressure.MP.Reading = string.IsNullOrEmpty(guiradtxtReportBloodPressure2.Text.Trim()) ? (ushort)9999 : ushort.Parse(guiradtxtReportBloodPressure2.Text.Trim());
                    break;
                case 2:
                    // dp & mp
                    obj.bloodPressure.SP.Reading = 9999;
                    obj.bloodPressure.MP.Reading = string.IsNullOrEmpty(guiradtxtReportBloodPressure1.Text.Trim()) ? (ushort)9999 : ushort.Parse(guiradtxtReportBloodPressure1.Text.Trim());
                    obj.bloodPressure.DP.Reading = string.IsNullOrEmpty(guiradtxtReportBloodPressure2.Text.Trim()) ? (ushort)9999 : ushort.Parse(guiradtxtReportBloodPressure2.Text.Trim());
                    break;
            }

            return obj.Validate();            
        }

        /**This method calcuates PWV distance values to update
        * */
        void CalculatePwvDistanceToUpdate(CrxStructPWVMeasurementData crxPWV)
        {
            // initially form session obj
            // crxPWV.PWVDistanceMethod = (crxMgrObject.PwvSettings.PWVDistanceMethod == 0) ? oMsgMgr.GetMessage("REPORT_LBL_SUBTRACTING") : oMsgMgr.GetMessage("REPORT_LBL_DIRECT");
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
                    if (!string.IsNullOrEmpty(guiradtxtCarotid.Text.Trim()) && !string.IsNullOrEmpty(guiradtxtReportCuff.Text.Trim()) && !string.IsNullOrEmpty(guiradtxtReportFemoToCuff.Text.Trim()))
                    {
                        crxPWV.Direct = 9999;
                        crxPWV.Carotid = short.Parse(guiradtxtCarotid.Text.Trim());
                        crxPWV.Cuff = short.Parse(guiradtxtReportCuff.Text.Trim());
                        crxPWV.FemoraltoCuff = short.Parse(guiradtxtReportFemoToCuff.Text.Trim());
                        crxPWV.PWVDistance = (short)(crxPWV.Cuff - crxPWV.Carotid - crxPWV.FemoraltoCuff);
                        crxPWV.PWVDistanceMethod = 0; // guiradlblReportPwvDistanceMethodType.Text;
                    }

                    break;

                case 1:
                    if (!string.IsNullOrEmpty(guiradtxtCarotid.Text.Trim()) && !string.IsNullOrEmpty(guiradtxtReportFemoToCuff.Text.Trim()))
                    {
                        crxPWV.Direct = short.Parse(guiradtxtCarotid.Text.Trim());
                        crxPWV.Carotid = 9999;
                        crxPWV.Cuff = 9999;
                        crxPWV.FemoraltoCuff = short.Parse(guiradtxtReportFemoToCuff.Text.Trim());
                        crxPWV.PWVDistance = (short)(crxPWV.Direct - crxPWV.FemoraltoCuff);
                        crxPWV.PWVDistanceMethod = 1; // guiradlblReportPwvDistanceMethodType.Text;
                    }

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
                    if (!string.IsNullOrEmpty(guiradtxtCarotid.Text.Trim()) && !string.IsNullOrEmpty(guiradtxtReportCuff.Text.Trim()) && !string.IsNullOrEmpty(guiradtxtReportFemoToCuff.Text.Trim()))
                    {
                        obj.myPWVDirectDistance.distance = 9999;
                        obj.myCarotidDistance.distance = ushort.Parse(guiradtxtCarotid.Text.Trim());
                        obj.myCuffDistance.distance = ushort.Parse(guiradtxtReportCuff.Text.Trim());
                        obj.myFemoral2CuffDistance.distance = ushort.Parse(guiradtxtReportFemoToCuff.Text.Trim());
                        obj.calculatedDistance = (ushort)(obj.myCuffDistance.distance - obj.myCarotidDistance.distance - obj.myFemoral2CuffDistance.distance);
                        obj.distanceMethod = 0; // guiradlblReportPwvDistanceMethodType.Text;
                    }

                    break;

                case 1:
                    if (!string.IsNullOrEmpty(guiradtxtCarotid.Text.Trim()) && !string.IsNullOrEmpty(guiradtxtReportFemoToCuff.Text.Trim()))
                    {
                        obj.myPWVDirectDistance.distance = ushort.Parse(guiradtxtCarotid.Text.Trim());
                        obj.myCarotidDistance.distance = 9999;
                        obj.myCuffDistance.distance = 9999;
                        obj.myFemoral2CuffDistance.distance = ushort.Parse(guiradtxtReportFemoToCuff.Text.Trim());
                        obj.calculatedDistance = (ushort)(obj.myPWVDirectDistance.distance - obj.myFemoral2CuffDistance.distance);
                        obj.distanceMethod = 1; // guiradlblReportPwvDistanceMethodType.Text;
                    }

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
                int heightinches = (int.Parse((string.IsNullOrEmpty(guiradtxtReportHeight.Text.Trim()) ? "0" : guiradtxtReportHeight.Text.Trim()).ToString()) * 12) + int.Parse((string.IsNullOrEmpty(guiradtxtReportHeightInches.Text.Trim()) ? "0" : guiradtxtReportHeightInches.Text.Trim()).ToString());
                obj.heightAndWeight.heightInInches = ushort.Parse(heightinches.ToString());
                obj.heightAndWeight.weightInPounds = ushort.Parse((string.IsNullOrEmpty(guiradtxtReportWeight.Text.Trim()) ? "0" : guiradtxtReportWeight.Text.Trim()).ToString());

                // (string.IsNullOrEmpty(guiradtxtReportHeight.Text.Trim()) ? "0" : guiradtxtReportHeight.Text.Trim()).ToString()
                // 1 pound is 0.453592 kilograms

                // 1 inch = 2.54 cm
               obj.heightAndWeight.weightInKilograms = (ushort)Math.Round(double.Parse(crxPWV.WeightInPounds.ToString()) * 0.453592, MidpointRounding.ToEven);
               obj.heightAndWeight.heightInCentimetres = (ushort)Math.Round(double.Parse(crxPWV.HeightInInches.ToString()) * 2.54, MidpointRounding.ToEven);
            }
            else
            {
                obj.heightAndWeight.heightInCentimetres = ushort.Parse((string.IsNullOrEmpty(guiradtxtReportHeight.Text.Trim()) ? "0" : guiradtxtReportHeight.Text.Trim()).ToString());
                obj.heightAndWeight.weightInKilograms = ushort.Parse((string.IsNullOrEmpty(guiradtxtReportWeight.Text.Trim()) ? "0" : guiradtxtReportWeight.Text.Trim()).ToString());

                // 1 kilogram = 2.20462262 pounds
                // 0.3937007874 inches in 1 centimeter
                obj.heightAndWeight.weightInPounds = (ushort)Math.Round(double.Parse(crxPWV.WeightInKilograms.ToString()) * 2.20462262, MidpointRounding.ToEven);
                obj.heightAndWeight.heightInInches = (ushort)Math.Round(double.Parse(crxPWV.HeightInCentimetres.ToString()) * 0.3937007874, MidpointRounding.ToEven);
            }
        }

        /**This method calculates height & weight to update changes
      */
        void CalculateHeightAndWeightToUpdate(CrxStructPWVMeasurementData crxPWV)
        {
            // calculates height in inches & centimeters
            if (guiradtxtReportHeightInches.Visible)
            {
                int heightinches = (int.Parse((string.IsNullOrEmpty(guiradtxtReportHeight.Text.Trim()) ? "0" : guiradtxtReportHeight.Text.Trim()).ToString()) * 12) + int.Parse((string.IsNullOrEmpty(guiradtxtReportHeightInches.Text.Trim()) ? "0" : guiradtxtReportHeightInches.Text.Trim()).ToString());
                crxPWV.HeightInInches = short.Parse(heightinches.ToString());
                crxPWV.WeightInPounds = short.Parse((string.IsNullOrEmpty(guiradtxtReportWeight.Text.Trim()) ? "0" : guiradtxtReportWeight.Text.Trim()).ToString());

                // (string.IsNullOrEmpty(guiradtxtReportHeight.Text.Trim()) ? "0" : guiradtxtReportHeight.Text.Trim()).ToString()
                // 1 pound is 0.453592 kilograms

                // 1 inch = 2.54 cm
                crxPWV.WeightInKilograms = (short)Math.Round(double.Parse(crxPWV.WeightInPounds.ToString()) * 0.453592, MidpointRounding.ToEven);
                crxPWV.HeightInCentimetres = (short)Math.Round(double.Parse(crxPWV.HeightInInches.ToString()) * 2.54, MidpointRounding.ToEven);
            }
            else
            {
                crxPWV.HeightInCentimetres = short.Parse((string.IsNullOrEmpty(guiradtxtReportHeight.Text.Trim()) ? "0" : guiradtxtReportHeight.Text.Trim()).ToString());
                crxPWV.WeightInKilograms = short.Parse((string.IsNullOrEmpty(guiradtxtReportWeight.Text.Trim()) ? "0" : guiradtxtReportWeight.Text.Trim()).ToString());

                // 1 kilogram = 2.20462262 pounds
                // 0.3937007874 inches in 1 centimeter
                crxPWV.WeightInPounds = (short)Math.Round(double.Parse(crxPWV.WeightInKilograms.ToString()) * 2.20462262, MidpointRounding.ToEven);
                crxPWV.HeightInInches = (short)Math.Round(double.Parse(crxPWV.HeightInCentimetres.ToString()) * 0.3937007874, MidpointRounding.ToEven);
            }
        }

        /**This method popluates biz session object after updating PWV measurement details
          * */
        void FillSessionObjAfterEdit(CrxStructPWVMeasurementData crxPWV)
        {
           // obj = (BizPWV)BizSession.Instance().measurement;
            obj.bloodPressureEntryOption = ushort.Parse(crxPWV.BloodPressureEntryOption.ToString());

            switch (obj.bloodPressureEntryOption)
            {
                case 0:
                    obj.bloodPressure.SP.Reading = ushort.Parse(crxPWV.SP.ToString());
                    obj.bloodPressure.DP.Reading = ushort.Parse(crxPWV.DP.ToString());
                    break;
                case 1:
                    obj.bloodPressure.SP.Reading = ushort.Parse(crxPWV.SP.ToString());
                    obj.bloodPressure.MP.Reading = ushort.Parse(crxPWV.MP.ToString());
                    break;
                case 2:
                    obj.bloodPressure.MP.Reading = ushort.Parse(crxPWV.MP.ToString());
                    obj.bloodPressure.DP.Reading = ushort.Parse(crxPWV.DP.ToString());
                    break;
            }

            obj.calculatedDistance = (ushort)crxPWV.PWVDistance;
            obj.heightAndWeight.heightInCentimetres = (ushort)crxPWV.HeightInCentimetres;
            obj.heightAndWeight.heightInInches = (ushort)crxPWV.HeightInInches;
            obj.heightAndWeight.weightInKilograms = (ushort)crxPWV.WeightInKilograms;
            obj.heightAndWeight.weightInPounds = (ushort)crxPWV.WeightInPounds;
            obj.notes = crxPWV.Notes;
            obj.operatorId = crxPWV.Operator;
            obj.myCarotidDistance.distance = (ushort)crxPWV.Carotid;
            obj.myCuffDistance.distance = (ushort)crxPWV.Cuff;
            obj.myFemoral2CuffDistance.distance = (ushort)crxPWV.FemoraltoCuff;
            obj.myPWVDirectDistance.distance = (ushort)crxPWV.Direct;
        }

        /**This event fires on text change of cuff distance
           * */
        private void guiradtxtReportCuff_TextChanged(object sender, EventArgs e)
        {
            // validate for any non numeric value entered 
            if (!string.IsNullOrEmpty(guiradtxtReportCuff.Text.Trim()))
            {
                if (System.Text.RegularExpressions.Regex.IsMatch(guiradtxtReportCuff.Text.Trim(), "[^0-9]"))
                {
                    guiradtxtReportCuff.Text = guiradtxtReportCuff.Text.Remove(guiradtxtReportCuff.Text.Length - 1);
                }               
            }
        }

        /**This event fires on text change of carotid distance
           * */
        private void guiradtxtCarotid_TextChanged(object sender, EventArgs e)
        {
            // // validate for any non numeric value entered 
            if (!string.IsNullOrEmpty(guiradtxtCarotid.Text.Trim()))
            {
                if (System.Text.RegularExpressions.Regex.IsMatch(guiradtxtCarotid.Text.Trim(), "[^0-9]"))
                {
                    guiradtxtCarotid.Text = guiradtxtCarotid.Text.Remove(guiradtxtCarotid.Text.Length - 1);
                }
            }
        }

        /**This event fires on text change of femoral to cuff distance
          * */
        private void guiradtxtReportFemoToCuff_TextChanged(object sender, EventArgs e)
        {
            // // validate for any non numeric value entered 
            if (!string.IsNullOrEmpty(guiradtxtReportFemoToCuff.Text.Trim()))
            {
                if (System.Text.RegularExpressions.Regex.IsMatch(guiradtxtReportFemoToCuff.Text.Trim(), "[^0-9]"))
                {
                    guiradtxtReportFemoToCuff.Text = guiradtxtReportFemoToCuff.Text.Remove(guiradtxtReportFemoToCuff.Text.Length - 1);
                }
            }
        }

        /** Plots superimposed wave form series from BizSession.xls
         * */
        private void SuperImposedWaveForm()
        {
            try
            {
               /* BizPWV obj1 = (BizPWV)BizSession.Instance().measurement;
                obj1.systemId = (uint)bobj;

                 obj1.patientNumber = (uint)SettingsProperties.PatientInternalNumber;
                 obj1.groupStudyId = (uint)SettingsProperties.GroupID;
                * */
                 crxMgrObject.PwvSettings.PWVDistanceMethod = obj.distanceMethod;

               // application = new Microsoft.Office.Interop.Excel.ApplicationClass();
               // book = application.Workbooks.Open(ConfigurationManager.AppSettings["XcelPath"].ToString(), 0, true, 5, string.Empty, string.Empty, false, Microsoft.Office.Interop.Excel.XlPlatform.xlWindows, string.Empty, true, false, 0, true, false, false);

               // sheet = (Microsoft.Office.Interop.Excel.Worksheet)book.Worksheets[1];

                // obj1.myPWVDirectDistance.distance = Convert.ToUInt16(((Microsoft.Office.Interop.Excel.Range)sheet.Cells[2, 8]).Value2.ToString());
             // string femoral = obj.femoralSignal.signal ((Microsoft.Office.Interop.Excel.Range)sheet.Cells[2, 12]).Value2.ToString();
             // string carotid = ((Microsoft.Office.Interop.Excel.Range)sheet.Cells[2, 11]).Value2.ToString();
             // ushort signalLength = Convert.ToUInt16(((Microsoft.Office.Interop.Excel.Range)sheet.Cells[2, 10]).Value2.ToString());
                
                // obj1.PrepareToCaptureSignal();
              // string[] femoralValuesArray = new string[5120];
              // femoralValuesArray = femoral.Split(',');
              // ushort[] femoralSignal = Array.ConvertAll(femoralValuesArray, new Converter<string, ushort>(Convert.ToUInt16));
                obj.femoralSignal.CaptureSignal(obj.femoralSignal.signal, obj.femoralSignal.signalLength, 0, (ushort)(obj.femoralSignal.signalLength - 1));

                // string[] carotidValuesArray = new string[5120];
               // carotidValuesArray = carotid.Split(',');
              // ushort[] carotidSignal = Array.ConvertAll(carotidValuesArray, new Converter<string, ushort>(Convert.ToUInt16));
                obj.carotidSignal.CaptureSignal(obj.carotidSignal.signal, obj.carotidSignal.signalLength, 0, (ushort)(obj.carotidSignal.signalLength - 1));
                bool status = obj.Calculate();

                if (status)
                {
                    // plot super impose wave form
                    ushort[] femoralSignalToPlot = obj.femoralSignal.signal;
                    float[] femoralOnSetPoints = obj.femoralSignal.floatOnsets;
                    ushort femoralOnSetPointLength = obj.femoralSignal.onsetsLength;
                    ushort[] carotidSignalToPlot = obj.carotidSignal.signal;
                    float[] carotidOnSetPoints = obj.carotidSignal.floatOnsets;
                    ushort carotidOnSetPointLenth = obj.carotidSignal.onsetsLength;

                    PlotSuperImposedWaveform(femoralSignalToPlot, femoralOnSetPoints, carotidSignalToPlot, carotidOnSetPoints, obj.carotidSignal.signalLength);

                    // fetches current running proccesses & kills process for excel sheet
                    System.Diagnostics.Process[] arr = System.Diagnostics.Process.GetProcesses();

                    for (int i = 0; i < arr.Length; i++)
                    {
                        if (arr[i].ProcessName.ToString().ToLower().Equals("excel"))
                        {
                            arr[i].Kill();
                            break;
                        }
                    }
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

        private void PlotSuperImposedWaveform(ushort[] femoralSignalToPlot, float[] femoralOnSetPoints, ushort[] carotidSignalToPlot, float[] carotidOnSetPoints, ushort signalLength)
        {
            // plot on the waveform.
            const double ChartHeight = 500;
            const double MinXValue = 0;
            double maxXValue = signalLength;

            // set y axis
            guichartSuperImposedWaveform.ChartAreas[0].AxisY.Minimum = ChartHeight * 0.96;
            guichartSuperImposedWaveform.ChartAreas[0].AxisY.Maximum = ChartHeight * 1.04;

            // set x axis
            guichartSuperImposedWaveform.ChartAreas[0].AxisX.Minimum = MinXValue;
            guichartSuperImposedWaveform.ChartAreas[0].AxisX.Maximum = maxXValue;

            // initialize series,chartype,add points to series and finally add series to chart.
            // Series for tonometer
            guichartSuperImposedWaveform.Series.Clear();
            #region Carotid Tonometer            
            tonometerSeries.ChartType = SeriesChartType.Spline;
            tonometerSeries.Color = Color.White;
            tonometerSeries.XValueType = ChartValueType.Auto;
            tonometerSeries.YValuesPerPoint = 1;
            Hashtable carotidTable = new Hashtable();
            tonometerSeries.Points.Clear();
            for (int i = 0; i < carotidSignalToPlot.Length; i++)
            {
                if (carotidSignalToPlot[i] > guichartSuperImposedWaveform.ChartAreas[0].AxisY.Maximum)
                {
                    guichartSuperImposedWaveform.ChartAreas[0].AxisY.Maximum = carotidSignalToPlot[i] * 1.04;
                }

                if (carotidSignalToPlot[i] < guichartSuperImposedWaveform.ChartAreas[0].AxisY.Minimum)
                {
                    guichartSuperImposedWaveform.ChartAreas[0].AxisY.Minimum = carotidSignalToPlot[i] * 0.96;
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
            int valueToPLot = 0, valueToPLot1 = 0;
            for (int j = 0; j < carotidOnSetPoints.Length; j++)
            {
                valueToPLot = int.Parse(Math.Round(double.Parse(carotidOnSetPoints[j].ToString()), MidpointRounding.ToEven).ToString());
                valueToPLot1 = Math.Abs(valueToPLot);

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

           // PlotCarotidTonometerSeries(carotidSignalToPlot, carotidOnSetPoints);
          // PlotFemoralSeries(femoralSignalToPlot, femoralOnSetPoints);
            #region Femoral cuff

            femoralSeries.ChartType = SeriesChartType.Spline;
            femoralSeries.Color = Color.Yellow;
            femoralSeries.XValueType = ChartValueType.Auto;
            femoralSeries.YValuesPerPoint = 1;
            Hashtable femoralTable = new Hashtable();
            femoralSeries.Points.Clear();
            for (int i = 0; i < femoralSignalToPlot.Length; i++)
            {
                if (femoralSignalToPlot[i] > guichartSuperImposedWaveform.ChartAreas[0].AxisY.Maximum)
                {
                    guichartSuperImposedWaveform.ChartAreas[0].AxisY.Maximum = femoralSignalToPlot[i] * 1.04;
                }

                if (femoralSignalToPlot[i] < guichartSuperImposedWaveform.ChartAreas[0].AxisY.Minimum)
                {
                    guichartSuperImposedWaveform.ChartAreas[0].AxisY.Minimum = femoralSignalToPlot[i] * 0.96;
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
            int valueToPLotCuffOnset = 0, valueToPLotCuffOnset1 = 0;
            for (int j = 0; j < femoralOnSetPoints.Length; j++)
            {
                valueToPLotCuffOnset = int.Parse(Math.Round(double.Parse(femoralOnSetPoints[j].ToString()), MidpointRounding.ToEven).ToString());

                valueToPLotCuffOnset1 = Math.Abs(valueToPLotCuffOnset);

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

        void PlotCarotidTonometerSeries(ushort[] carotidSignalToPlot, float[] carotidOnSetPoints)
        {
            #region Carotid Tonometer

            tonometerSeries.ChartType = SeriesChartType.Spline;
            tonometerSeries.Color = Color.White;
            tonometerSeries.XValueType = ChartValueType.Auto;
            tonometerSeries.YValuesPerPoint = 1;
            Hashtable carotidTable = new Hashtable();

            for (int i = 0; i < carotidSignalToPlot.Length; i++)
            {
                if (carotidSignalToPlot[i] > guichartSuperImposedWaveform.ChartAreas[0].AxisY.Maximum)
                {
                    guichartSuperImposedWaveform.ChartAreas[0].AxisY.Maximum = carotidSignalToPlot[i] * 1.04;
                }

                if (carotidSignalToPlot[i] < guichartSuperImposedWaveform.ChartAreas[0].AxisY.Minimum)
                {
                    guichartSuperImposedWaveform.ChartAreas[0].AxisY.Minimum = carotidSignalToPlot[i] * 0.96;
                }

                tonometerSeries.Points.AddXY(i, carotidSignalToPlot[i]);
                carotidTable[i] = carotidSignalToPlot[i];
            }

            #region Carotid onSet points

            tonometerOnsetSeries.ChartType = SeriesChartType.FastPoint;
            tonometerOnsetSeries.Color = Color.Red;
            tonometerOnsetSeries2.ChartType = SeriesChartType.FastPoint;
            tonometerOnsetSeries2.Color = Color.Green;
            int valueToPLot = 0, valueToPLot1 = 0;
            for (int j = 0; j < carotidOnSetPoints.Length; j++)
            {
                valueToPLot = int.Parse(Math.Round(double.Parse(carotidOnSetPoints[j].ToString()), MidpointRounding.ToEven).ToString());
                valueToPLot1 = Math.Abs(valueToPLot);

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
        }

        void PlotFemoralSeries(ushort[] femoralSignalToPlot, float[] femoralOnSetPoints)
        {
            #region Femoral cuff

            femoralSeries.ChartType = SeriesChartType.Spline;
            femoralSeries.Color = Color.Yellow;
            femoralSeries.XValueType = ChartValueType.Auto;
            femoralSeries.YValuesPerPoint = 1;
            Hashtable femoralTable = new Hashtable();
            
            for (int i = 0; i < femoralSignalToPlot.Length; i++)
            {
                if (femoralSignalToPlot[i] > guichartSuperImposedWaveform.ChartAreas[0].AxisY.Maximum)
                {
                    guichartSuperImposedWaveform.ChartAreas[0].AxisY.Maximum = femoralSignalToPlot[i] * 1.04;
                }

                if (femoralSignalToPlot[i] < guichartSuperImposedWaveform.ChartAreas[0].AxisY.Minimum)
                {
                    guichartSuperImposedWaveform.ChartAreas[0].AxisY.Minimum = femoralSignalToPlot[i] * 0.96;
                }

                femoralSeries.Points.AddXY(i, femoralSignalToPlot[i]);
                femoralTable[i] = femoralSignalToPlot[i];
            }

            #region Cuff Onset Points

            femoralOnsetSeries.ChartType = SeriesChartType.FastPoint;
            femoralOnsetSeries.Color = Color.Red;
            femoralOnsetSeries2.ChartType = SeriesChartType.FastPoint;
            femoralOnsetSeries2.Color = Color.Green;

            int valueToPLotCuffOnset = 0, valueToPLotCuffOnset1 = 0;
            for (int j = 0; j < femoralOnSetPoints.Length; j++)
            {
                valueToPLotCuffOnset = int.Parse(Math.Round(double.Parse(femoralOnSetPoints[j].ToString()), MidpointRounding.ToEven).ToString());

                valueToPLotCuffOnset1 = Math.Abs(valueToPLotCuffOnset);

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
        }

        /**This event fires when checkbox is clicked on assessment gridview
          * */
        private void guiradgridReportAssessment_ValueChanged(object sender, EventArgs e)
        {
              if (this.guiradgridReportAssessment.ActiveEditor is RadCheckBoxEditor)
                {
                    // index = this.guiradgridReportAssessment.CurrentCell.RowIndex;
                    // object value = this.guiradgridReportAssessment.ActiveEditor.Value;
                    oneRecordSelect = true;
                    if (guiradgridReportAssessment.ActiveEditor.Value.ToString() == "Off")
                    {
                        // if unchecked disable delete button
                        DisableDeleteButton(this.guiradgridReportAssessment.CurrentCell.RowIndex);
                        this.guiradgridReportAssessment.Rows[this.guiradgridReportAssessment.CurrentCell.RowIndex].IsSelected = false;
                    }
                    else
                    {
                        // if checked count number of patients selected & enable delete button
                        guiradbtnDelete.Enabled = true;

                        if (CountPatientSelected(1) == 1)
                        {
                            // if only 1 record is selected in assessment grid bind the measurement details pertaining to that patient
                            guiradbtnreportedit.Enabled = true;
                            InitializeCrxOnLoad(this.guiradgridReportAssessment.Rows[this.guiradgridReportAssessment.CurrentCell.RowIndex].Cells[1].Value.ToString());
                            FillPWVMeasurementDetailsReport();
                            SuperImposedWaveForm();
                            PlotNormalRangeGraph();
                            PlotReferenceRangeGraph();
                        }
                        else
                        {
                            guiradbtnreportedit.Enabled = false;
                        }
                       
                        this.guiradgridReportAssessment.Rows[this.guiradgridReportAssessment.CurrentCell.RowIndex].IsSelected = true;
                    }
                }            
        }

        /** This method disables delete button if none of the assessments are selected
         * */ 
        void DisableDeleteButton(int currentRowIndex)
        {
            guiradchkAssesments.Checked = false;
           
            int selected = 0;

            // check if any assessment other than current is selected
            for (int i = 0; i < guiradgridReportAssessment.Rows.Count; i++)
            {
                if (i != currentRowIndex)
                {
                    if (guiradgridReportAssessment.Rows[i].Cells["CheckBox"].Value != null)
                    {
                        if (bool.Parse(guiradgridReportAssessment.Rows[i].Cells["CheckBox"].Value.ToString()))
                        {
                            guiradbtnDelete.Enabled = true;
                            guiradbtnreportedit.Enabled = true;
                            selected = 1;
                            break;
                        }
                    }
                }
            }

            if (selected == 0)
            {
                guiradbtnDelete.Enabled = false;
                guiradbtnreportedit.Enabled = false;
            }           
        }

        /** This method returns count of selected patients in grid
         * */
        int CountPatientSelected(int currentRecord)
        {
            int selected = currentRecord;
            
            for (int i = 0; i < guiradgridReportAssessment.Rows.Count; i++)
            {
               if (guiradgridReportAssessment.Rows[i].Cells["CheckBox"].Value != null)
               {
                        if (bool.Parse(guiradgridReportAssessment.Rows[i].Cells["CheckBox"].Value.ToString()))
                        {
                            guiradbtnDelete.Enabled = true;
                            guiradbtnreportedit.Enabled = true;
                            selected++;                            
                        }
               }                
            }

            // check assessment checkbox if all assessments are selected in grid
            if (selected == guiradgridReportAssessment.Rows.Count)
            {
                guiradchkAssesments.Checked = true;
            }

            return selected;
        }

        /** This method fills session object with selected assessments
         * */
        void FillSessionForSelectedAssessment(string studyDateTime)
        { 
             DataSet dsPWV = new DataSet();

            CrxStructPWVMeasurementData cdata = new CrxStructPWVMeasurementData();
            cdata.PatientNumberInternal = SettingsProperties.PatientInternalNumber;
            cdata.GroupIdentifier = SettingsProperties.GroupID;
            cdata.SystemIdentifier = bobj;
            cdata.StudyDateTime = DateTime.Parse(studyDateTime);
            dsPWV = dbMagr.GetPWVMeasurementDetails(cdata);

            if (dsPWV.Tables[0].Rows.Count > 0)
            {
               SettingsProperties.PwvCurrentStudyDatetime = dsPWV.Tables[0].Rows[0]["Studydatetime"].ToString();
               FillSessionData(dsPWV);
            }
        }

        /** This method initializes biz session object each time a patient record is selected/edited/added
       */
        void FillSessionData(DataSet dsPWV)
        {
            // obj = (BizPWV)BizSession.Instance().measurement;
            FillSessionWithBloodPressure(dsPWV);
            FillSessionWithMetricAndDistance(dsPWV);
            /*  byte[] buffer = (byte[])dsPWV.Tables[0].Rows[0]["CarotidSignal"];
          
              int len = buffer.Length / 2;
              ushort[] carotid1 = new ushort[len];
              carotid1 =  dbMagr.CommonByteArrtoShortArr(len, buffer);
           */

            // vibhuti: initializing mean heart rate , pulse wave velocity & other statistics as per workaround
            obj.meanHeartRate = string.IsNullOrEmpty(dsPWV.Tables[0].Rows[0]["MeanHeartRate"].ToString()) ? (float)0 : float.Parse(dsPWV.Tables[0].Rows[0]["MeanHeartRate"].ToString());
            obj.meanPulseWaveVelocity = string.IsNullOrEmpty(dsPWV.Tables[0].Rows[0]["MeanPulseWaveVelocity"].ToString()) ? (float)0 : float.Parse(dsPWV.Tables[0].Rows[0]["MeanPulseWaveVelocity"].ToString());
            obj.isStandardDeviationValid = string.IsNullOrEmpty(dsPWV.Tables[0].Rows[0]["IsStandardDeviationValid"].ToString()) ? false : bool.Parse(dsPWV.Tables[0].Rows[0]["IsStandardDeviationValid"].ToString());
            obj.isCarotidSignalValid = string.IsNullOrEmpty(dsPWV.Tables[0].Rows[0]["IsCarotidSignalValid"].ToString()) ? false : bool.Parse(dsPWV.Tables[0].Rows[0]["IsCarotidSignalValid"].ToString());
            obj.isFemoralSignalValid = string.IsNullOrEmpty(dsPWV.Tables[0].Rows[0]["IsFemoralSignalValid"].ToString()) ? false : bool.Parse(dsPWV.Tables[0].Rows[0]["IsFemoralSignalValid"].ToString());

            // commented : vibhuti as resets value to 9999 after initialising
            // obj.Validate(); // calculates metric or imperial equivalents for height and weight and the body mass index.
            // obj.Calculate(); // It will calculate all the members of the BizPWV class, including distanceMethod and patientAge                                     
        }

        /** This method fills blood pressure values in Biz object
         * */
        void FillSessionWithBloodPressure(DataSet dsPWV)
        {
            obj.bloodPressureEntryOption = string.IsNullOrEmpty(dsPWV.Tables[0].Rows[0]["bloodpressureentryoption"].ToString()) ? (ushort)0 : ushort.Parse(dsPWV.Tables[0].Rows[0]["bloodpressureentryoption"].ToString());

            switch (obj.bloodPressureEntryOption)
            {
                case 0:
                    obj.bloodPressure.SP.Reading = ushort.Parse(dsPWV.Tables[0].Rows[0]["SP"].ToString());
                    obj.bloodPressure.DP.Reading = ushort.Parse(dsPWV.Tables[0].Rows[0]["DP"].ToString());
                    break;
                case 1:
                    obj.bloodPressure.SP.Reading = ushort.Parse(dsPWV.Tables[0].Rows[0]["SP"].ToString());
                    obj.bloodPressure.MP.Reading = ushort.Parse(dsPWV.Tables[0].Rows[0]["MP"].ToString());
                    break;
                case 2:
                    obj.bloodPressure.MP.Reading = ushort.Parse(dsPWV.Tables[0].Rows[0]["MP"].ToString());
                    obj.bloodPressure.DP.Reading = ushort.Parse(dsPWV.Tables[0].Rows[0]["DP"].ToString());
                    break;
            }
        }

        /** This method fills bix object with metric & distance values
        * */
        void FillSessionWithMetricAndDistance(DataSet dsPWV)
        {
            obj.calculatedDistance = string.IsNullOrEmpty(dsPWV.Tables[0].Rows[0]["PWVDistance"].ToString()) ? (ushort)0 : ushort.Parse(dsPWV.Tables[0].Rows[0]["PWVDistance"].ToString());
            obj.heightAndWeight.heightInCentimetres = string.IsNullOrEmpty(dsPWV.Tables[0].Rows[0]["HeightInCentimetres"].ToString()) ? obj.heightAndWeight.heightInCentimetres : ushort.Parse(dsPWV.Tables[0].Rows[0]["HeightInCentimetres"].ToString());
            obj.heightAndWeight.heightInInches = string.IsNullOrEmpty(dsPWV.Tables[0].Rows[0]["HeightInInches"].ToString()) ? obj.heightAndWeight.heightInInches : ushort.Parse(dsPWV.Tables[0].Rows[0]["HeightInInches"].ToString());
            obj.heightAndWeight.weightInKilograms = string.IsNullOrEmpty(dsPWV.Tables[0].Rows[0]["WeightInKilograms"].ToString()) ? obj.heightAndWeight.weightInKilograms : ushort.Parse(dsPWV.Tables[0].Rows[0]["WeightInKilograms"].ToString());
            obj.heightAndWeight.weightInPounds = string.IsNullOrEmpty(dsPWV.Tables[0].Rows[0]["WeightInPounds"].ToString()) ? obj.heightAndWeight.weightInPounds : ushort.Parse(dsPWV.Tables[0].Rows[0]["WeightInPounds"].ToString());
            obj.notes = dsPWV.Tables[0].Rows[0]["Notes"].ToString();
            obj.operatorId = dsPWV.Tables[0].Rows[0]["Operator"].ToString();
            obj.myCarotidDistance.distance = string.IsNullOrEmpty(dsPWV.Tables[0].Rows[0]["Carotid"].ToString()) ? obj.myCarotidDistance.distance : ushort.Parse(dsPWV.Tables[0].Rows[0]["Carotid"].ToString());
            obj.myCuffDistance.distance = string.IsNullOrEmpty(dsPWV.Tables[0].Rows[0]["Cuff"].ToString()) ? obj.myCuffDistance.distance : ushort.Parse(dsPWV.Tables[0].Rows[0]["Cuff"].ToString());
            obj.myFemoral2CuffDistance.distance = string.IsNullOrEmpty(dsPWV.Tables[0].Rows[0]["FemoraltoCuff"].ToString()) ? obj.myFemoral2CuffDistance.distance : ushort.Parse(dsPWV.Tables[0].Rows[0]["FemoraltoCuff"].ToString());
            obj.myPWVDirectDistance.distance = string.IsNullOrEmpty(dsPWV.Tables[0].Rows[0]["direct"].ToString()) ? obj.myPWVDirectDistance.distance : ushort.Parse(dsPWV.Tables[0].Rows[0]["direct"].ToString());
            obj.heightAndWeight.bodyMassIndex = string.IsNullOrEmpty(dsPWV.Tables[0].Rows[0]["BodyMassIndex"].ToString()) ? (float)0 : float.Parse(dsPWV.Tables[0].Rows[0]["BodyMassIndex"].ToString());            
        }

        /** This method plots normal range graph
         * */
        void PlotNormalRangeGraph()
        {
            try
            {
                // set y axis (normal range values from Bizsession object in float)
                // float[] normalrange = obj.normalRange;
                // convert normal range float array to double
                float[] normalrange = obj.normalRange; // { 11.0F, 10.2F, 5.0F, 13.0F, 20.0F, 16.0F, 19.0F, 9.0F, 17.0F, 15.0F };

               // DataSet dsPWV = new DataSet();
               // dsPWV = dbMagr.GetPWVMeasurementDetails(SettingsProperties.PatientInternalNumber, SettingsProperties.GroupID, bobj);

               //// throw new CrxException("For test purpose");
                
               /*
                if (dsPWV.Tables[0].Rows.Count > 0)
                {
                    byte[] buffer = (byte[])dsPWV.Tables[0].Rows[0]["NormalRange"];

                    int len = buffer.Length / 4;
                    float[] yValues = new float[len];
                    yValues = dbMagr.CommonByteArrtoFloatArr(len, buffer);
                    if (yValues.Length > 0)
                    {
                        normalrange = yValues;
                     }
                } */

                guichartNormalRange.Series.Clear();              

                    Array.Sort(normalrange);
                    guichartNormalRange.ChartAreas[0].AxisY.Minimum = double.Parse(((float)normalrange[0]).ToString());
                    guichartNormalRange.ChartAreas[0].AxisY.Maximum = double.Parse(((float)normalrange[normalrange.Length - 1]).ToString());
                    guichartNormalRange.ChartAreas[0].AxisY.Interval = 5;
                    guichartNormalRange.ChartAreas[0].AxisY.Title = oMsgMgr.GetMessage("REPORT_NORMALRANGE_Y_AXIS_TITLE");
                    
                    // set x axis
                    guichartNormalRange.ChartAreas[0].AxisX.Minimum = (double)BizConstants.MINIMUM_REFERENCE_RANGE_AGE; // 20
                    guichartNormalRange.ChartAreas[0].AxisX.Maximum = (double)BizConstants.MAXIMUM_REFERENCE_RANGE_AGE; // 90;
                    guichartNormalRange.ChartAreas[0].AxisX.Title = oMsgMgr.GetMessage("REPORT_NORMALRANGE_X_AXIS_TITLE");
                
                    // initialize series,chartype,add points to series and finally add series to chart.
                    // Series for tonometer
                    // set display properties for normal range graph
                    normalRangeSeries.Points.Clear();
                    normalRangeSeries.ChartType = SeriesChartType.Area;
                    normalRangeSeries.Color = Color.Green;
                    normalRangeSeries.BorderColor = Color.Black;
                    normalRangeSeries.BorderWidth = 1;
                    normalRangeSeries.BackGradientStyle = GradientStyle.TopBottom;

                    for (int i = 0; i < normalrange.Length; i++)
                    {
                        normalRangeSeries.Points.AddXY((double)i, (double)((float)normalrange[i]));
                    }

                    guichartNormalRange.Series.Add(normalRangeSeries);                           
               
                // set properties for series 2 for plotting bubble
                normalRangeSeries2.ChartType = SeriesChartType.Bubble;
                normalRangeSeries2.Color = Color.FromArgb(121, 171, 231);
                normalRangeSeries2.CustomProperties = "BubbleMaxSize=15";
                normalRangeSeries2.MarkerStyle = MarkerStyle.Circle;
                normalRangeSeries2.ShadowOffset = 5;
                normalRangeSeries2.Points.Clear();
                normalRangeSeries2.Points.AddXY(double.Parse(obj.patientAge.ToString()), 9.9); // double.Parse(obj.meanPulseWaveVelocity.ToString())
                              
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
                if (obj.bloodPressure.DP.Reading.Equals(9999) && obj.bloodPressure.MP.Reading.Equals(9999) && obj.bloodPressure.SP.Reading.Equals(9999))
                {
                    ////guichartReferenceRange.ChartAreas[0].BackColor = Color.Gray;
                    ////guichartReferenceRange.Series[0].Color = Color.Gray;
                    ////guichartReferenceRange.Enabled = false;
                    // cannot plot reference without BP
                   // guichartReferenceRange.Series.Clear();
                    guireportradlblReferenceMsg.Visible = true;
                    guireportradlblReferenceMsg.BringToFront();
                    guiradlblReportBpRange.Visible = false;
                }
                else
                {
                    guireportradlblReferenceMsg.SendToBack();
                    guiradlblReportBpRange.Visible = false;

                    // plot reference range graph
                    // set y axis (normal range values from Bizsession object in float)
                    // convert normal range float array to double
                    float[] referencerange = obj.referenceRange; // { 11.0F, 10.2F, 5.0F, 13.0F, 20.0F, 16.0F, 19.0F, 9.0F, 17.0F, 15.0F };

                    guichartReferenceRange.Series.Clear();

                    Array.Sort(referencerange);

                    guichartReferenceRange.ChartAreas[0].AxisY2.Minimum = double.Parse(((float)referencerange[0]).ToString());
                    guichartReferenceRange.ChartAreas[0].AxisY2.Maximum = double.Parse(((float)referencerange[referencerange.Length - 1]).ToString());
                    guichartReferenceRange.ChartAreas[0].AxisY2.Interval = 5;
                    guichartReferenceRange.ChartAreas[0].AxisY2.Title = oMsgMgr.GetMessage("REPORT_NORMALRANGE_Y_AXIS_TITLE");
                    
                    // set x axis
                    guichartReferenceRange.ChartAreas[0].AxisX.Minimum = (double)BizConstants.MINIMUM_REFERENCE_RANGE_AGE; // 20
                    guichartReferenceRange.ChartAreas[0].AxisX.Maximum = (double)BizConstants.MAXIMUM_REFERENCE_RANGE_AGE; // 90;
                    guichartReferenceRange.ChartAreas[0].AxisX.Title = oMsgMgr.GetMessage("REPORT_NORMALRANGE_X_AXIS_TITLE");

                    // initialize series,chartype,add points to series and finally add series to chart.
                    // Series for tonometer
                    // set display properties for normal range graph
                    referenceRangeSeries.ChartType = SeriesChartType.Area;
                    referenceRangeSeries.Color = Color.Green;
                    referenceRangeSeries.BorderColor = Color.Black;
                    referenceRangeSeries.BorderWidth = 1;
                    referenceRangeSeries.BackGradientStyle = GradientStyle.TopBottom;
                    referenceRangeSeries.Points.Clear();

                    for (int i = 0; i < referencerange.Length; i++)
                    {
                        referenceRangeSeries.Points.AddXY((double)i, (double)((float)referencerange[i]));
                    }

                    guichartReferenceRange.Series.Add(normalRangeSeries);

                    // set properties for series 2 for plotting bubble
                    referenceRangeSeries2.ChartType = SeriesChartType.Bubble;
                    referenceRangeSeries2.Color = Color.FromArgb(121, 171, 231);
                    referenceRangeSeries2.CustomProperties = "BubbleMaxSize=15";
                    referenceRangeSeries2.MarkerStyle = MarkerStyle.Circle;
                    referenceRangeSeries2.ShadowOffset = 5;
                    referenceRangeSeries2.Points.Clear();
                    referenceRangeSeries2.Points.AddXY(double.Parse(obj.patientAge.ToString()), double.Parse(obj.meanPulseWaveVelocity.ToString())); // double.Parse(normalrange[3].ToString())9.9

                    guichartReferenceRange.Series.Add(normalRangeSeries2);
                    guichartReferenceRange.Invalidate();                                        
                }
            }
            catch (Exception ex)
            {
                GUIExceptionHandler.HandleException(ex, this);
            }
        }
        
        /** This event fires when timer interval ends, enables repeat button & capture tab
         * */
        private void timer1_Tick(object sender, EventArgs e)
        { 
            ////objDefaultWindow.radtabCapture.Enabled = true;
            ////guiradbtnRepeat.Enabled = true;
            ////timer1.Stop();
            ////timer1.Dispose();
        }

        /** This event fires when assessment checkbox is selected. If selected it selects all checkboxes in grid & vice versa
         * */
        private void guiradchkAssesments_ToggleStateChanged(object sender, StateChangedEventArgs args)
        {            
            // if checked select all records in grid   
            if (guiradchkAssesments.ToggleState == ToggleState.On)
                { 
                    for (int i = 0; i < guiradgridReportAssessment.Rows.Count; i++)
                    {
                        guiradgridReportAssessment.Rows[i].Cells["CheckBox"].Value = true;
                        guiradgridReportAssessment.Rows[i].IsSelected = true;                        
                    }

                    oneRecordSelect = false;
                    guiradbtnDelete.Enabled = true;
                    guiradbtnreportedit.Enabled = false;
                }

                if (guiradchkAssesments.ToggleState == ToggleState.Off)
                {
                    if (!oneRecordSelect)
                    {
                        for (int j = 0; j < guiradgridReportAssessment.Rows.Count; j++)
                        {
                            guiradgridReportAssessment.Rows[j].Cells["CheckBox"].Value = false;
                            guiradgridReportAssessment.Rows[j].IsSelected = false;
                        }

                        guiradbtnDelete.Enabled = false;
                        guiradbtnreportedit.Enabled = false;
                    } 
                }
        }

        /** This event deletes assessments of selected patients
         * */
        private void guiradbtnDelete_Click(object sender, EventArgs e)
        {
            recordsToDelete = 0;
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
                        }                       
                    }                                  
            }

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
                    FillPatientAssessmentDetailsReport(sender, e);
                }
            }
        }

        /** This method clears all chart series for tonometer, normal & reference range
         * */
        void ClearChartData()
        {
            guichartReferenceRange.Series.Clear();
            guichartNormalRange.Series.Clear();
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
    }
}
