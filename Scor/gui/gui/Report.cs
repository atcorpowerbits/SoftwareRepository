/*
     Copyright (C) ATCOR MEDICAL PTY LTD, 2010
 
     Filename     :     Report Window
        
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
using AtCor.Scor.CrossCutting;
using AtCor.Scor.CrossCutting.Configuration;
using AtCor.Scor.CrossCutting.Logging;
using AtCor.Scor.CrossCutting.DatabaseManager;
using AtCor.Scor.CrossCutting.Messaging;
using AtCor.Scor.DataAccess;
using AtCor.Scor.BusinessLogic;
using System.Windows.Forms.DataVisualization.Charting;
using System.Collections;
using System.Text;
using System.Configuration;
using Telerik.WinControls.Primitives;

namespace AtCor.Scor.Gui.Presentation
{
    public partial class Report : RadForm
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
        int numeberOfRecordsSelected;

        // bool isControlAndUpArrowKeyPressed = false; 
        string dateToCompare = string.Empty; // used to compare dates when 30 sec wait interval is imposed to enable / disable repeat button based on last record selected
        string dateWithComma = string.Empty;
        int recordsToDelete; // this variable holds value for number of records to delete and is used across dfifferent methods 
        string lastAssessmentDate = string.Empty;
        private DefaultWindow objDefaultWindow;
        private bool isValueChanged = false;
        private bool IsHeightOutsideIntegerLimits = false;

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
      
        /** Parameterized Constructor of the form,initializes all the controls.
      * */
        public Report(DefaultWindow defWindow)
        {
            try
            {
                InitializeComponent();

              // GuiCommon.SetFontForControls(this);
                SetFontForChartTitles();

                // subscribe for form changes
                SubscribeReportFormChanges();
                InitializeReportScreen();
                
                // set the default window
                objDefaultWindow = defWindow;

                // initialize servername string
                serverNameString = GuiCommon.ServerNameString();
                obj = (BizPWV)BizSession.Instance().measurement;

                // subscribe report tab click event                
                DefaultWindow.OnReportTabClick += Report_Load;

               // DefaultWindow.OnExitSaveReportChanges += SaveChangesOnEdit;
                DefaultWindow.OnReportMenuItemClick += SaveChangesOnMenuFocus;
                
                Presentation.Capture.OnReportTabClick += Report_Load;

                GuiCommon.OnCaptureClosing += EnableRepeatAndCaptureTab;
                guichartSuperImposedWaveform.BackColor = Color.White;              
                guiradlblReportCarotid.ForeColor = Color.Blue;                
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
            SetShape(guilblReportPatientIdValue, guilblReportDobValue, guilblReportAgeValue, guilblReportGenderValue, guiradlblreportSPdisplay, guiradlblReportBloodPressure2, guiradlblReportOperatordisplay, guiradlblReportNotesDisplay, guiradlblReportPwvDistanceMethodType, guiradlblreportpwvdistancedisplay1, guiradlblreportpwvdistancedisplay, guiradlblReportHeightDisplay, guiradlblReportHeightInches, guiradlblInterpretationDisplay);
            SetShape(guiradtxtReportBloodPressure1, guiradtxtReportBloodPressure2, guiradtxtReportOperator, guiradtxtReportNotes, guiradtxtReportCuff, guiradtxtCarotid, guiradtxtReportFemoToCuff, guiradtxtReportHeightInches, guiradtxtReportHeight, guiradtxtInterpretation);
        }

        /**This method is called on the tick of wait interval  timer used on the Default window.
         * On the tick of the timer we enable the repeat button on the Report screen along with the Capture tab.
         */
        public void EnableRepeatAndCaptureTab(bool value)
        {
            try
            {
                GuiCommon.IsWaitIntervalImposed = !value;
                GuiCommon.CaptureToSetup = !value;

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

        public void LoadPWVReport()
        {
            // This variable is set when the user is on Report screen.
            
            
            GuiCommon.IsOnReportForm = true;

            // Clearing the capture time label on load.
            objDefaultWindow.radlblCaptureTime.Text = string.Empty;
            
            bobj = GuiConstants.SystemId;
            GuiCommon.CaptureToSetup = false;
            GuiCommon.SystemIdentifier = bobj;
            GuiCommon.ReportLoadCount++;

            SetTextForReportScreen();
            SetReportTagForValidation();
            objValidateReport = new GuiFieldValidation(guipnlReportPatientMeasurementDetails, guiradpnlEditPWVdistance);

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
            CheckWaitIntervalImposed();
            CheckForSimualtionMode(); 
        }

        /**This is invoked on the load of report window.
        *fetches & binds report screen data 
        */
        private void Report_Load(object sender, EventArgs e)
        {
            if (GuiCommon.CurrentMode == CrxStructCommonResourceMsg.Pwv)
            {
                // below statement checks if Invoke required and calls the report load event again to populate report data
                // without this report data will not be loaded when it this event is invoked from other windows
                if (InvokeRequired)
                {
                    Invoke(new EventHandler(Report_Load));
                    return;
                }

                LoadPWVReport();
                CheckForSimualtionMode();
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
            guiradpnlAnalysis.Visible = false;
            objDefaultWindow.radtabReport.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.TabReport);

            if (GuiCommon.StartupScreen != oMsgMgr.GetMessage(CrxStructCommonResourceMsg.QuickStart))
            {
                obj.CalculateAge();
            }

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
                guiradlblReportPwvDitanceUnits.Text = guiradlblReportPwvDitanceUnits1.Text = crxMgrObject.PwvSettings.PWVDistanceUnits.Equals(0) ? oMsgMgr.GetMessage(CrxStructCommonResourceMsg.Mm) : oMsgMgr.GetMessage(CrxStructCommonResourceMsg.Cm);
                guiradlblReportPwvDistance.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.LabelPwvDistance);
                guiradlblReportAssessments.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.LblReportAssessments);
                guiradlblReportPatientId.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.LblPatientId);
                guiradlblReportPatientName.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.LblPatientName);
                guiradlblReportGender.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.LblReportGender);

                // Commenting the below code as group name is not included in Clinical mode.
               // guiradlblReportGroup.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.LblGroup);
                guiradlblReportDOB.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.LblReportDob);
                guiradlblReportAge.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.LblReportAge);
                guiradlblReportheightWeight.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.LblHeight);
                guiradlblPatientDetails.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.PrtPwvTextPatientDetails); 

                // Commenting the below code as group name is not included in Clinical mode.
               // guiradlblReportWeight.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.LblWeight);
               // guiradlblReportBmi.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.LblReportBmi);
                guiradlblReportOperator.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.LblOperator);
                guiradlblNotes.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.LblNotes);
                guiradlblReportPwvDistanceMethod.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.LblReportPwvmethod);
                guiradlblReportPwvDistance1.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.LabelPwvDistance);
                guiradlblPwvTime.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.LblPwvReportTime);
                guiradlblReportCarotid.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.LblReportCarotid);
                guiradlblReportFemoral.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.LblReportFemoral);
                guiradAnalysisChartHeading.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.LblReportPwv);
                guiradlbReportNormalRange.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.LblReportNormalRange);
                guiradlblReportReferenceRange.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.LblReportReferenceRange);
                guiradlblReportHeartRate.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.LblReportHeartRate);
                guiradlblReportPulseWaveVelocity.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.LblReportPwv);
                guiradlblQc.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.LblReportStdDeviation);
                guiradbtnreportsave.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.BtnSave);
                guiradbtnreportcancel.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.BtnCancel);
                guiradbtnreportedit.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.BtnEdit);
                guiradbtnRepeat.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.BtnRepeat);
                guiradbtnPrint.Text = guiradbtnAnalysisPrint.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.BtnPrint);
               
                guiradbtnDelete.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.BtnDelete);
                guiradlblCarotid.Text = crxMgrObject.PwvSettings.PWVDistanceMethod.Equals((int)CrxGenPwvValue.CrxPwvDistMethodSubtract) ? oMsgMgr.GetMessage(CrxStructCommonResourceMsg.LabelCarotid) : oMsgMgr.GetMessage(CrxStructCommonResourceMsg.GuiDirect);                
                guiradlblReportCuff.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.LblReportCuffWithcolon); 
                guiradlblReportFemoToCuff.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.LabelFemoralCuff);
                guireportradlblReferenceMsg.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.GuiReportNoBp);
                guiPrintPatientReport.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.GuiSettingsPwvPatientReport);
                guiprintPwvReport.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.GuiSettingsPwvReport);
                guiradbtnPrint.DefaultItem = crxMgrObject.PwvSettings.DefaultReport.Equals(oMsgMgr.GetMessage(CrxStructCommonResourceMsg.GuiSettingsPwvPatientReport)) ? guiPrintPatientReport : guiprintPwvReport;
                guiradlblReportBpRange.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.GuiReportLblBpRange);

                guiradlblRefRangeDescription.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.GuiRptRefRangeDesc);                    
            }            
            catch (Exception ex)
            {
                GUIExceptionHandler.HandleException(ex, this);
            }
        }

        /** This method sets tag property of textbox and labels for validating measurement details on report screen.
          * It helps in identifying labels & textbox which are mandatory and marked for validation by business logic
          * */
        private void SetReportTagForValidation()
        {
            guiradlblCarotid.Tag = guiradtxtCarotid.Tag = crxMgrObject.PwvSettings.PWVDistanceMethod.Equals((int)CrxGenPwvValue.CrxPwvDistMethodSubtract) ? oMsgMgr.GetMessage(CrxStructCommonResourceMsg.FemoralDistanceCarotidToSternalCuff) : oMsgMgr.GetMessage(CrxStructCommonResourceMsg.FemoralDistanceCarotidToFemoralCuff);
            guiradlblReportCuff.Tag = guiradtxtReportCuff.Tag = crxMgrObject.PwvSettings.PWVDistanceMethod.Equals((int)CrxGenPwvValue.CrxPwvDistMethodSubtract) ? oMsgMgr.GetMessage(CrxStructCommonResourceMsg.FemoralDistanceSternalNotchToFemoralCuff) : string.Empty;
            guiradlblReportFemoToCuff.Tag = guiradtxtReportFemoToCuff.Tag = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.FemoralDistanceFemoraltoCuff);
            guiradlblReportBloodPressure1.Tag = guiradtxtReportBloodPressure1.Tag = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.FieldPatientSp);
            guiradlblBloodPressure2.Tag = guiradtxtReportBloodPressure2.Tag = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.FieldPatientDp);
            guiradlblReportheightWeight.Tag = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.FieldPatientHeight);
            guiradtxtReportHeight.Tag = crxMgrObject.GeneralSettings.HeightandWeightUnit.Equals((int)CrxGenPwvValue.CrxGenHeightWeightMetric) ? oMsgMgr.GetMessage(CrxStructCommonResourceMsg.FieldPatientHeight) : oMsgMgr.GetMessage(CrxStructCommonResourceMsg.FieldPatientHeightFoot);
            guiradtxtReportHeightInches.Tag = crxMgrObject.GeneralSettings.HeightandWeightUnit.Equals((int)CrxGenPwvValue.CrxGenHeightWeightMetric) ? string.Empty : oMsgMgr.GetMessage(CrxStructCommonResourceMsg.FieldPatientHeightInch);
            
           // Commenting the below code as group name is not included in Clinical mode.
           // guiradlblReportWeight.Tag = guiradtxtReportWeight.Tag = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.FieldPatientWeight);
        }

        /**This event fires on edit button click
       */
        private void guiradbtnreportedit_Click(object sender, EventArgs e)
        {           
            // edit mode            
            // Show edit mode in the status bar.
            objDefaultWindow.guiradmnuDatabase.Enabled = false;
            objDefaultWindow.radlblMessage.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.EditMode);

            // guiradtxtReportFemoToCuff.ReadOnly = !crxMgrObject.PwvSettings.FemoralToCuff;
            
            // make display panel visible for PWV distance
            guiradpnldisplayPWVDistance.Visible = false;
            guiradpnlEditPWVdistance.Visible = true;
            ReportPWVDisplayMode(false);

            // populates PWV measurement fields as per Settings from config manager
            guiradlblReportCuffUnits.Text = guiradlblReportFemoralCuffUnits.Text = guiradlblCarotidUnits.Text = crxMgrObject.PwvSettings.PWVDistanceUnits.Equals(0) ? oMsgMgr.GetMessage(CrxStructCommonResourceMsg.Mm) : oMsgMgr.GetMessage(CrxStructCommonResourceMsg.Cm);
            ushort tempVal = obj.myFemoral2CuffDistance.distance;
            guiradtxtReportFemoToCuff.Text = crxMgrObject.PwvSettings.PWVDistanceUnits.Equals((int)CrxGenPwvValue.CrxPwvDistDistUnitsCM) ? (tempVal / GuiConstants.DivisionFactor).ToString() : tempVal.ToString();
            guiradtxtReportFemoToCuff.Text = guiradtxtReportFemoToCuff.Text.Equals("0") ? string.Empty : guiradtxtReportFemoToCuff.Text;
            SetPwvDistanceFieldForEditing();
            
            // set height & weight details
            guiradtxtReportHeight.Text = guiradlblReportHeightDisplay.Text;
            guiradtxtReportHeightInches.Text = guiradlblReportHeightInches.Text;

            // Commenting the below code as group name is not included in Clinical mode.
            // guiradtxtReportWeight.Text = guiradlblReportWeightdisplay.Text;
           // guiradtxtReportOperator.Text = guiradlblReportOperatordisplay.Text;
            guiradtxtReportNotes.Text = guiradlblReportNotesDisplay.Text;
            SetBloodPressureDataForEditing();

            guiradbtnreportedit.Visible = false;
            guiradbtnreportcancel.Visible = true;
            guiradbtnreportsave.Visible = true;
          
            // in edit mode disable repeat & capture buttons
            guiradbtnRepeat.Enabled = false;
            objDefaultWindow.radtabCapture.Enabled = false;

            // GuiCommon.IsFormChanged = false;
            GuiCommon.IsFormChanged = true;
        }
        
         /**This method sets Carotid, cuff & femoral to cuff values for editing as per PWV distance method
       */
        private void SetPwvDistanceFieldForEditing()
        {
            ushort tempVal;
           
            // This line is commented to show pwv distance method details according to database
            // value for that perticuler assesment instead of showing for the latest Config value, so it
            // will not give error which was appearing on edit when we were changing distance method from settings to 
            // other distance method(different than which was actual for that record) (22 august 2011  PWVSW-368)
            // switch (crxMgrObject.PwvSettings.PWVDistanceMethod)
            switch (crxPWV.PWVDistanceMethod)
            {
                case (int)CrxGenPwvValue.CrxPwvDistMethodSubtract:
                    // subtracting
                    // display & populate carotid, cuff & femoral to cuff textboxes
                   guiradlblReportCuff.Tag = guiradtxtReportCuff.Tag = crxPWV.PWVDistanceMethod.Equals((int)CrxGenPwvValue.CrxPwvDistMethodSubtract) ? oMsgMgr.GetMessage(CrxStructCommonResourceMsg.FemoralDistanceSternalNotchToFemoralCuff) : string.Empty;
                   guiradlblCarotid.Tag = guiradtxtCarotid.Tag = crxPWV.PWVDistanceMethod.Equals((int)CrxGenPwvValue.CrxPwvDistMethodSubtract) ? oMsgMgr.GetMessage(CrxStructCommonResourceMsg.FemoralDistanceCarotidToSternalCuff) : oMsgMgr.GetMessage(CrxStructCommonResourceMsg.FemoralDistanceCarotidToFemoralCuff);
                   if (!objValidateReport.mandatoryTextboxes.Contains(guiradtxtReportCuff))
                   {
                       objValidateReport.mandatoryTextboxes.Add(guiradtxtReportCuff);
                   }

                   guiradlblCarotid.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.LabelCarotid);
                    guiradlblReportCuff.Visible = true;
                    guiradtxtReportCuff.Visible = true;
                    guiradlblReportCuffUnits.Visible = true;
                    guiradlblReportFemoToCuff.Visible = true;
                    guiradtxtReportFemoToCuff.Visible = true;
                    guiradlblCarotid.Visible = true;

                    guiradtxtCarotid.Visible = true;
                    guiradlblCarotidUnits.Visible = true;
                    guiradlblReportFemoralCuffUnits.Visible = true;
                    guiradlblReportPwvDistanceMethodType.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.ReportLblSubtracting);
                                        
                    tempVal = obj.myCuffDistance.distance.Equals(GuiConstants.DefaultValue) ? (ushort)0 : obj.myCuffDistance.distance;
                    guiradtxtReportCuff.Text = crxMgrObject.PwvSettings.PWVDistanceUnits.Equals((int)CrxGenPwvValue.CrxPwvDistDistUnitsCM) ? (tempVal / GuiConstants.DivisionFactor).ToString() : tempVal.ToString();
                    
                    tempVal = obj.myCarotidDistance.distance.Equals(GuiConstants.DefaultValue) ? (ushort)0 : obj.myCarotidDistance.distance;
                    guiradtxtCarotid.Text = crxMgrObject.PwvSettings.PWVDistanceUnits.Equals((int)CrxGenPwvValue.CrxPwvDistDistUnitsCM) ? (tempVal / GuiConstants.DivisionFactor).ToString() : tempVal.ToString();

                    break;
                case (int)CrxGenPwvValue.CrxPwvDistMethodDirect:
                    // direct
                    // display & populate direct & femoral to cuff textboxes
                    guiradlblCarotid.Tag = guiradtxtCarotid.Tag = crxPWV.PWVDistanceMethod.Equals((int)CrxGenPwvValue.CrxPwvDistMethodSubtract) ? oMsgMgr.GetMessage(CrxStructCommonResourceMsg.FemoralDistanceCarotidToSternalCuff) : oMsgMgr.GetMessage(CrxStructCommonResourceMsg.FemoralDistanceCarotidToFemoralCuff);
                    objValidateReport.mandatoryTextboxes.Remove(guiradtxtReportCuff); 
                    guiradlblCarotid.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.LabelDirect);
                    guiradlblReportCuff.Visible = false;
                    guiradtxtReportCuff.Visible = false;
                    guiradlblReportCuffUnits.Visible = false;
                    guiradlblReportFemoToCuff.Visible = true;
                    guiradtxtReportFemoToCuff.Visible = true;
                    guiradlblCarotid.Visible = true;

                    guiradtxtCarotid.Visible = true;
                    guiradlblCarotidUnits.Visible = true;
                    guiradlblReportFemoralCuffUnits.Visible = true;
                    guiradlblReportPwvDistanceMethodType.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.ReportLblDirect);
                    tempVal = obj.myPWVDirectDistance.distance.Equals(GuiConstants.DefaultValue) ? (ushort)0 : obj.myPWVDirectDistance.distance;
                    guiradtxtCarotid.Text = crxMgrObject.PwvSettings.PWVDistanceUnits.Equals((int)CrxGenPwvValue.CrxPwvDistDistUnitsCM) ? (tempVal / GuiConstants.DivisionFactor).ToString() : tempVal.ToString();
                    
                    break;
                default:
                    break;
            }
        }

        /**This method sets SP, DP & MP values for editing in textboxes
      */
        private void SetBloodPressureDataForEditing()
        {
            // sets SP, DP & MP values as per session & config object

            // Pritam

            // if (obj.bloodPressureEntryOption != ushort.Parse(crxMgrObject.GeneralSettings.BloodPressureEntryOptions.ToString()))
            if (obj.bloodPressureEntryOption != ushort.Parse(crxMgrObject.BpSettings.BloodPressure.ToString()))
            {
                // Pritam
                // switch (crxMgrObject.GeneralSettings.BloodPressureEntryOptions)
                guiradlblReportBloodPressure1.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.Sp);
                guiradlblBloodPressure2.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.LabelDp);

                guiradtxtReportBloodPressure1.Text = (obj.bloodPressure.SP == null || obj.bloodPressure.SP.Reading.Equals(GuiConstants.DefaultValue)) ? string.Empty : obj.bloodPressure.SP.Reading.ToString();
                guiradtxtReportBloodPressure2.Text = (obj.bloodPressure.DP == null || obj.bloodPressure.DP.Reading.Equals(GuiConstants.DefaultValue)) ? string.Empty : obj.bloodPressure.DP.Reading.ToString();

                // switch (crxMgrObject.BpSettings.BloodPressure)
                // {
                //    case (int)CrxGenPwvValue.CrxGenBPOptSPandDP:
                //        // SP & DP
                       
                ////       break;
                //    case (int)CrxGenPwvValue.CrxGenBPOptSPandMP:
                //        // SP & MP
                //        guiradlblReportBloodPressure1.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.Sp); 
                //        guiradlblBloodPressure2.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.LabelMp); 

                ////       guiradtxtReportBloodPressure1.Text = (obj.bloodPressure.SP == null || obj.bloodPressure.SP.Reading.Equals(GuiConstants.DefaultValue)) ? string.Empty : obj.bloodPressure.SP.Reading.ToString();
                //        guiradtxtReportBloodPressure2.Text = (obj.bloodPressure.MP == null || obj.bloodPressure.MP.Reading.Equals(GuiConstants.DefaultValue)) ? string.Empty : obj.bloodPressure.MP.Reading.ToString();
                //        break;
                //    case (int)CrxGenPwvValue.CrxGenBPOptMPandDP:
                //        // MP & DP
                //        guiradlblReportBloodPressure1.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.Mp);
                //        guiradlblBloodPressure2.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.LabelDp);

                // guiradtxtReportBloodPressure1.Text = (obj.bloodPressure.MP == null || obj.bloodPressure.MP.Reading.Equals(GuiConstants.DefaultValue)) ? string.Empty : obj.bloodPressure.MP.Reading.ToString();
                // guiradtxtReportBloodPressure2.Text = (obj.bloodPressure.DP == null || obj.bloodPressure.DP.Reading.Equals(GuiConstants.DefaultValue)) ? string.Empty : obj.bloodPressure.DP.Reading.ToString();
                // break;
                // default:
                //        break;
                // }
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
            CheckForSimualtionMode();
            GuiCommon.IsFormChanged = false;
        }

        /** This method brings report screen left side measurement details section in display mode
         * It hides cancel & save button & unhides edit button
         * */
        private void SetPWVDsiplayMode()
        {            
            objDefaultWindow.radlblMessage.Text = string.Empty;
            objDefaultWindow.guiradmnuDatabase.Enabled = true;

            // make display panel visible
            guiradpnldisplayPWVDistance.Visible = true;
            guiradpnlEditPWVdistance.Visible = false;

            // cancels editing PWV details
            ReportPWVDisplayMode(true);
            guiradbtnreportcancel.Visible = false;
            guiradbtnreportedit.Visible = true;
            guiradbtnreportsave.Visible = false;
            guiradbtnPrint.Enabled = true;
            guiradbtnreportedit.Focus();

            // reset PWV distance method type text
            guiradlblReportPwvDistance.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.LabelPwvDistance);
            guiradlblReportPwvDistanceMethodType.Text = obj.myCarotidDistance.distance.Equals(GuiConstants.DefaultValue) ? oMsgMgr.GetMessage(CrxStructCommonResourceMsg.ReportLblDirect) : oMsgMgr.GetMessage(CrxStructCommonResourceMsg.ReportLblSubtracting);
            guiradlblReportPwvDitanceUnits.Text = crxMgrObject.PwvSettings.PWVDistanceUnits.Equals(0) ? oMsgMgr.GetMessage(CrxStructCommonResourceMsg.Mm) : oMsgMgr.GetMessage(CrxStructCommonResourceMsg.Cm);

            // sets blood pressure display text in labels
            SetBloodPressureDisplayText();

            CheckLastAssessmentSelected(dateToCompare);
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

                // guilblReportDobValue.Text = patientObj.dateOfBirth.ToString(oMsgMgr.GetMessage(CrxStructCommonResourceMsg.ReportDateTimeFormat),CrxCommon.gCI);
                guilblReportDobValue.Text = patientObj.dateOfBirth.ToShortDateString();
                guilblReportAgeValue.Text = obj.patientAge.ToString();
                guilblReportGenderValue.Text = patientObj.gender.Equals(CrxStructCommonResourceMsg.MaleTxt) ? oMsgMgr.GetMessage(CrxStructCommonResourceMsg.MaleTxt) : oMsgMgr.GetMessage(CrxStructCommonResourceMsg.FemaleTxt); 

                // guilblReportGenderValue.Text = patientObj.gender;
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
                guiradgridReportAssessment.Columns.Add(oMsgMgr.GetMessage(CrxStructCommonResourceMsg.ReportAssesmentsFormat), oMsgMgr.GetMessage(CrxStructCommonResourceMsg.GuiDisplayStudyDateTime), "StudyDateTime");
                guiradgridReportAssessment.Columns[1].Width = 275;
                guiradgridReportAssessment.Columns[1].IsVisible = true;
                guiradgridReportAssessment.Columns[1].ReadOnly = true;
                guiradgridReportAssessment.Columns[1].FormatString = "{0:g}";

               // guiradgridReportAssessment.Columns[1].SortOrder = RadSortOrder.Ascending;
                guiradgridReportAssessment.GridElement.AlternatingRowColor = Color.LightGray;
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
                guiradbtnreportedit.Focus();
                guiradbtnreportsave.Visible = false;

                guiradbtnDelete.Enabled = true;

               // guiradbtnPrint.Enabled = true;
                // guiradchkAssesments.Enabled = guiradgridReportAssessment.Rows.Count > 1 ? true : false;
                guiradgridReportAssessment.Enabled = true;
                
                // show labels (display PWV details)
                // Commenting the below code as group name is not included in Clinical mode.
                // guiradtxtReportWeight.Visible = false;
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
                
                // guiradtxtInterpretation.Visible = false;
                guiradtxtReportBloodPressure1.SendToBack();
                guiradtxtReportBloodPressure2.SendToBack();
                guiradtxtReportOperator.SendToBack();

                // guiradtxtInterpretation.SendToBack();

                // Commenting the below code as group name is not included in Clinical mode.
                // guiradtxtReportWeight.SendToBack();
                guiradtxtReportNotes.SendToBack();
                guiradtxtReportHeight.SendToBack();
                guiradlblReportPwvDistance.BringToFront();
                guiradlblReportBloodPressure1.BringToFront();
                guiradlblReportBloodPressure2.BringToFront();
                guiradlblReportOperatordisplay.BringToFront();
                guiradlblReportHeightDisplay.BringToFront();
                guiradlblreportpwvdistancedisplay.BringToFront();

                // guiradlblInterpretationDisplay.BringToFront();

                // Commenting the below code as group name is not included in Clinical mode.
                // guiradlblReportWeightdisplay.BringToFront();
                guiradlblReportNotesDisplay.BringToFront();
                               
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

               // guiradtxtReportOperator.Visible = true;
                guiradtxtReportBloodPressure1.Visible = true;

               // guiradtxtInterpretation.Visible = true;
                guiradtxtReportBloodPressure1.Focus();
                guiradlblReportPwvDistance.SendToBack();
                guiradlblReportBloodPressure1.SendToBack();
                guiradlblReportBloodPressure2.SendToBack();
                guiradlblReportOperatordisplay.SendToBack();
                guiradlblReportHeightDisplay.SendToBack();

                // Commenting the below code as group name is not included in Clinical mode.
                // guiradlblReportWeightdisplay.SendToBack();
                // guiradlblReportBmiValue.SendToBack();
                guiradlblReportNotesDisplay.SendToBack();

                // guiradlblInterpretationDisplay.SendToBack();
                guiradlblreportpwvdistancedisplay.SendToBack();
                guiradtxtReportBloodPressure1.BringToFront();

                // Commenting the below code as group name is not included in Clinical mode.
                // guiradtxtReportWeight.BringToFront();
                guiradtxtReportNotes.BringToFront();
                guiradtxtReportHeight.BringToFront();

                // guiradtxtInterpretation.BringToFront();
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
        
        /**This method fill PWV measurement details for a particular patient
        * */
        void FillPWVMeasurementDetailsReport()
        {
            const int LblReportNotesDisplayMaximumLength = 44; // denotes the maximum length of guiradlblReportNotesDisplay label
           // const int LblReportOperatorDisplayMaxLength = 13; // denotes the maximum length of guiradlblReportOperatordisplay label
                        
            // make display panel visible for PWV distance
            guiradpnldisplayPWVDistance.Visible = true;
            guiradpnlEditPWVdistance.Visible = false;
            
            // create biz session instance & bind details to labels            
            // guiradlblreportpwvdistancedisplay.Text = guiradlblreportpwvdistancedisplay1.Text = obj.calculatedDistance.ToString();            
            if (crxMgrObject.PwvSettings.PWVDistanceUnits.Equals((int)CrxGenPwvValue.CrxPwvDistDistUnitsCM))
            {
                guiradlblreportpwvdistancedisplay.Text = guiradlblreportpwvdistancedisplay1.Text = (obj.calculatedDistance / GuiConstants.DivisionFactor).ToString();
            }
            else
            {
                guiradlblreportpwvdistancedisplay.Text = guiradlblreportpwvdistancedisplay1.Text = obj.calculatedDistance.ToString();
            }

            guiradlblReportPwvDistanceMethodType.Text = obj.myCarotidDistance.distance.Equals(GuiConstants.DefaultValue) ? oMsgMgr.GetMessage(CrxStructCommonResourceMsg.ReportLblDirect) : oMsgMgr.GetMessage(CrxStructCommonResourceMsg.ReportLblSubtracting);
            guiradlblReportPwvDitanceUnits.Text = guiradlblReportPwvDitanceUnits1.Text = crxMgrObject.PwvSettings.PWVDistanceUnits.Equals(0) ? oMsgMgr.GetMessage(CrxStructCommonResourceMsg.Mm) : oMsgMgr.GetMessage(CrxStructCommonResourceMsg.Cm);

            // Commenting the below code as group name is not included in Clinical mode.
            // guiradlblReportBmiValue.Text = obj.heightAndWeight.bodyMassIndex.Equals(GuiConstants.DefaultValue) ? string.Empty : obj.heightAndWeight.bodyMassIndex.ToString();
            guiradlblReportOperatordisplay.Text = guiradtxtReportOperator.Text = obj.operatorId;
            guiradlblReportNotesDisplay.Text = guiradtxtReportNotes.Text = obj.notes;

            // Since AutoEllipsis propert works only on singleline we are using code to check maximum length for label
            if (guiradlblReportNotesDisplay.Text.Length > LblReportNotesDisplayMaximumLength)
            {
                guiradlblReportNotesDisplay.Text = guiradlblReportNotesDisplay.Text.Substring(0, LblReportNotesDisplayMaximumLength - 3);
                guiradlblReportNotesDisplay.Text = string.Format("{0}...", guiradlblReportNotesDisplay.Text);
            }

            // set display text for SP, DP & MP labels
            SetBloodPressureDisplayText();

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
                    guiradtxtReportHeight.MaxLength = 3;

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

                    guiradtxtReportHeight.MaxLength = 2;

                    // Commenting the below code as group name is not included in Clinical mode.
                    // guiradlblReportWeightdisplay.Text = obj.heightAndWeight.weightInPounds.Equals(GuiConstants.DefaultValue) ? string.Empty : obj.heightAndWeight.weightInPounds.ToString();

                    // guiradlblReportWeightUnits.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.Lbs);
                    guiradlblReportHeightUnits.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.Feet);
                    break;
                default:
                    break;
            }

            // for binding statistics
            BindPWVStatistics();            
        }              

        /** Binds PWV statistics from db if not available in sesion object
         * */
        void BindPWVStatistics()
        {   
            // #0 will round to largest integer & #0.0 will round to one decimal place
            guiradlblReportHeartRateValue.Text = obj.meanHeartRate.ToString().Equals(GuiConstants.DefaultValue.ToString()) ? string.Empty : obj.meanHeartRate.ToString("#0") + " " + oMsgMgr.GetMessage(CrxStructCommonResourceMsg.HeartrateUnit);
            guiradlblReportPWVValue.Text = obj.meanPulseWaveVelocity.ToString().Equals(GuiConstants.DefaultValue.ToString()) ? string.Empty : obj.meanPulseWaveVelocity.ToString("#0.0") + " " + oMsgMgr.GetMessage(CrxStructCommonResourceMsg.PwvUnit);
            guiradlblStdDeviationImage.ImageIndex = obj.isStandardDeviationValid ? (int)TickCrossImage.Tick : (int)TickCrossImage.Cross;
            guiradlblReportFemoralImage.ImageIndex = obj.isFemoralSignalValid ? (int)TickCrossImage.Tick : (int)TickCrossImage.Cross;
            guiradlblReportCarotidImage.ImageIndex = obj.isCarotidSignalValid ? (int)TickCrossImage.Tick : (int)TickCrossImage.Cross;
      
            // guiradlblPwvTimeValue.Text = Convert.ToDateTime(obj.meanCorrectedTime.ToString()).Millisecond.ToString();
            guiradlblPwvTimeValue.Text = Math.Round(obj.meanCorrectedTime).ToString() + " " + oMsgMgr.GetMessage(CrxStructCommonResourceMsg.UnitsTimeMs);
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
                    guiradlblReportDateTime.Visible = false;
                    guiradlblReportDateTimeDisplay.Visible = false;

                    DataSet ds = dbMagr.GetPWVMeasurementDetails(int.Parse(patientObj.patientNumber.ToString()), GuiCommon.GroupId, bobj);

                    guiradgridReportAssessment.DataSource = ds.Tables[0];
                    guiradgridReportAssessment.Columns[1].SortOrder = RadSortOrder.Ascending;

                   // guiradchkAssesments.Checked = false;
                    if (ds.Tables[0].Rows.Count > 0)
                    {
                        guiradbtnreportedit.Enabled = true;

                        // sets assessment count for a label
                        guiradlblReportAssesmentCount.Text = string.Format("{0}{1} {2} {3}{4}", oMsgMgr.GetMessage(CrxStructCommonResourceMsg.GuiDisplayLeftSqrBracket), ds.Tables[0].Rows.Count, oMsgMgr.GetMessage(CrxStructCommonResourceMsg.ReportAssesmentRecordCount), ds.Tables[0].Rows.Count, oMsgMgr.GetMessage(CrxStructCommonResourceMsg.GuiDisplayRightSqrBracket));                       
                        GuiCommon.HasMeasurementDetails = true;
                        guiradgridReportAssessment.MasterTemplate.Rows[ds.Tables[0].Rows.Count - 1].Cells[0].Value = true;
                        guiradbtnDelete.Enabled = true;
                        guiradbtnRepeat.Enabled = true;
                        objDefaultWindow.radtabCapture.Enabled = true;  
                        guiradbtnPrint.Enabled = true;
                        guiradpnlAnalysis.Visible = false;
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
                            // If there is only one assessment in the grid,we need to show the split button to the user and hide the normal button used to print the analysis report.
                            guiradbtnAnalysisPrint.SendToBack();
                            guiradbtnPrint.BringToFront();
                            guiradbtnPrint.Enabled = true;
                        }

                        FillPWVMeasurementDetailsReport();                        
                        
                        SuperImposedWaveForm();
                        CheckAgeLimit(obj.patientAge);                        
                        PlotNormalRangeGraph();
                        PlotReferenceRangeGraph();                        
                    }
                    else
                    {
                        guichartReferenceRange.Visible = true;
                        guireportradlblReferenceMsg.Visible = false;
                        guiradbtnreportedit.Enabled = false;
                        guiradbtnDelete.Enabled = false;
                        guiradbtnPrint.Enabled = false;
                        guiradbtnAnalysisPrint.Enabled = false;
                        ClearChartData();
                        ResetMeasurementFields();
                        OnPwvMeasurementChangedEvent.Invoke(this, new EventArgs());
                        GuiCommon.HasMeasurementDetails = false;                        
                        guiradpnlAnalysis.Visible = false;
                        objDefaultWindow.radtabReport.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.TabReport);
                        guiradlblReportAssesmentCount.Text = string.Format("{0}{1} {2} {3}{4}", oMsgMgr.GetMessage(CrxStructCommonResourceMsg.GuiDisplayLeftSqrBracket), ds.Tables[0].Rows.Count.ToString(), oMsgMgr.GetMessage(CrxStructCommonResourceMsg.ReportAssesmentRecordCount), ds.Tables[0].Rows.Count.ToString(), oMsgMgr.GetMessage(CrxStructCommonResourceMsg.GuiDisplayRightSqrBracket));
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

        /**This method sets SP, DP & MP value based on bloodPressureEntryOption in labels
         * */
        void SetBloodPressureDisplayText()
        {
            guiradlblReportBloodPressure1.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.Sp);
            guiradlblBloodPressure2.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.LabelDp);
            guiradlblreportSPdisplay.Text = obj.bloodPressure.SP.Reading.Equals(GuiConstants.DefaultValue) ? string.Empty : obj.bloodPressure.SP.Reading.ToString();
            guiradlblReportBloodPressure2.Text = obj.bloodPressure.DP.Reading.Equals(GuiConstants.DefaultValue) ? string.Empty : obj.bloodPressure.DP.Reading.ToString();

            // switch (obj.bloodPressureEntryOption)
            // {
            //    case (int)CrxGenPwvValue.CrxGenBPOptSPandDP:
            //       // sp & dp                   
            ////       break;
            //    case (int)CrxGenPwvValue.CrxGenBPOptSPandMP:
            //        // sp & mp
            //        guiradlblReportBloodPressure1.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.Sp); // hardcoded for internal use while changing user settings.
            //        guiradlblBloodPressure2.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.LabelMp); // hardcoded for internal use while changing user settings.
            //        guiradlblreportSPdisplay.Text = obj.bloodPressure.SP.Reading.Equals(GuiConstants.DefaultValue) ? string.Empty : obj.bloodPressure.SP.Reading.ToString();
            //        guiradlblReportBloodPressure2.Text = obj.bloodPressure.MP.Reading.Equals(GuiConstants.DefaultValue) ? string.Empty : obj.bloodPressure.MP.Reading.ToString();
            //        break;
            //    case (int)CrxGenPwvValue.CrxGenBPOptMPandDP:
            //        // mp & dp
            //        guiradlblReportBloodPressure1.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.Mp); // hardcoded for internal use while changing user settings.
            //        guiradlblBloodPressure2.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.LabelDp); // hardcoded for internal use while changing user settings.
            //        guiradlblreportSPdisplay.Text = obj.bloodPressure.MP.Reading.Equals(GuiConstants.DefaultValue) ? string.Empty : obj.bloodPressure.MP.Reading.ToString();
            //        guiradlblReportBloodPressure2.Text = obj.bloodPressure.DP.Reading.Equals(GuiConstants.DefaultValue) ? string.Empty : obj.bloodPressure.DP.Reading.ToString();
            //        break;
            //    default:
            //        break;
            // }
            
           // CheckBloodPressure();
            CheckAgeLimit(obj.patientAge);
        }

        /** This method checks for blood pressure values & 
         * accordingly displays text (Normal BP) on reference range graph
         * */
        private void CheckBloodPressure()
        {
            BizDataLimits lim = BizDataValidation.Instance().GetLimits(oMsgMgr.GetMessage(CrxStructCommonResourceMsg.FieldPatientHeight));

            // read limits and units 
            int min = lim.GetMin();
            int max = lim.GetMax();

            PWVReportData.RptBpLabelsText = string.Empty;

            // if (CrxConfigManager.Instance.PwvSettings.PWVDistanceMethod.Equals((int)CrxGenPwvValue.CrxPwvDistMethodSubtract) &&
            // if (crxPWV.PWVDistanceMethod.Equals((int)CrxGenPwvValue.CrxPwvDistMethodSubtract) &&
            // || obj.heightAndWeight.heightInCentimetres.Equals(GuiConstants.DefaultValue) || obj.heightAndWeight.heightInCentimetres.Equals(GuiConstants.DefaultValue))
            if ((obj.bloodPressure.DP.Reading.Equals(GuiConstants.DefaultValue) && obj.bloodPressure.MP.Reading.Equals(GuiConstants.DefaultValue)) ||
            (obj.bloodPressure.DP.Reading.Equals(GuiConstants.DefaultValue) && obj.bloodPressure.SP.Reading.Equals(GuiConstants.DefaultValue)) ||
            (obj.bloodPressure.MP.Reading.Equals(GuiConstants.DefaultValue) && obj.bloodPressure.SP.Reading.Equals(GuiConstants.DefaultValue)))           
            {
                guiradlblReportReferenceRange.Visible = true;
                guiradlblReportBpRange.Visible = false;
                guiradlblRefRangeDescription.Visible = false;
                guireportradlblReferenceMsg.Visible = true;
                guireportradlblReferenceMsg.BringToFront();
                guireportradlblReferenceMsg.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.GuiReportNoBp);
                guichartReferenceRange.Visible = false;
                PWVReportData.RptBpLabelsText = guireportradlblReferenceMsg.Text;
            }
            else if ((crxMgrObject.GeneralSettings.HeightandWeightUnit.Equals((int)CrxGenPwvValue.CrxGenHeightWeightMetric) && (obj.heightAndWeight.heightInCentimetres > max || obj.heightAndWeight.heightInCentimetres < min)) || (crxMgrObject.GeneralSettings.HeightandWeightUnit.Equals((int)CrxGenPwvValue.CrxGenHeightWeightImperial) && (obj.heightAndWeight.heightInInches > max || obj.heightAndWeight.heightInInches < min)))
            {
                guiradlblReportReferenceRange.Visible = true;
                guiradlblReportBpRange.Visible = false;
                guiradlblRefRangeDescription.Visible = false;
                guireportradlblReferenceMsg.Visible = true;
                guireportradlblReferenceMsg.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.GuiReportPatientHeightOutsideRange);
                guireportradlblReferenceMsg.BringToFront();
                guichartReferenceRange.Visible = false;
               PWVReportData.RptBpLabelsText = guireportradlblReferenceMsg.Text;
            }
            else
            {
                if (CrxConfigManager.Instance.PwvSettings.ReferenceRange)
                {
                    guiradlblReportReferenceRange.Visible = true;
                    guiradlblReportBpRange.Visible = true;
                    guiradlblRefRangeDescription.Visible = true;
                    guichartReferenceRange.Visible = true;
                    guireportradlblReferenceMsg.Visible = false;
                    guireportradlblReferenceMsg.SendToBack();
                }
            }
        }
        
        /**
         */
        public void SaveChangesOnEdit(object sender, EventArgs e)
        {
            try
            {               
                objDefaultWindow.radlblMessage.Text = string.Empty;
                objDefaultWindow.guiradmnuDatabase.Enabled = true;
                
                // check if mandatory fields are entered
                if (!objValidateReport.CheckMandatoryFields())
                {                    
                    // check db connection
                    if (dbMagr.CheckConnection(serverNameString, crxMgrObject.GeneralSettings.SourceData) == 0)
                    {
                        // save PWV details in database and session object
                        CrxStructPWVMeasurementData crxPWV = new CrxStructPWVMeasurementData();

                        /* InitializeCrx(crxPWV) returns integer
                         * 0 => update measurement data
                         * 1 => validation failed
                         * 2 => report calculation failed
                         */
                          switch (InitializeCrx(crxPWV))
                        {
                            case (int)InitializeCrxValue.UpdateData:

                                // update measurement data
                                // save data                            
                                SaveMeasurementData(crxPWV);
                                CheckLastAssessmentSelected(dateToCompare);
                                guiradgridReportAssessment.Enabled = true;
                                break;
                            case (int)InitializeCrxValue.ValidationFailed:

                                // obj validation failed  
                                if (!IsHeightOutsideIntegerLimits)
                                {
                                   // RadMessageBox.Show(this, oMsgMgr.GetMessage(CrxStructCommonResourceMsg.ErrorValidating), oMsgMgr.GetMessage(CrxStructCommonResourceMsg.SystemError), MessageBoxButtons.OK, RadMessageIcon.Error);
                                    PopulateBizFromCrx(dateToCompare);
                                }

                                break;
                            case (int)InitializeCrxValue.ReportCalculationFailed:

                                // report calculation failed
                                RadMessageBox.Show(this, oMsgMgr.GetMessage(CrxStructCommonResourceMsg.ReportCalculateError), oMsgMgr.GetMessage(CrxStructCommonResourceMsg.SystemError), MessageBoxButtons.OK, RadMessageIcon.Error);
                                break;
                            default:
                                break;
                        }

                        GuiCommon.IsFormChanged = false;                        
                         isValueChanged = false;                
                    }
                    else
                    {
                        DialogResult result = RadMessageBox.Show(this, GuiCommon.ConnectionErrorString(), oMsgMgr.GetMessage(CrxStructCommonResourceMsg.SystemError), MessageBoxButtons.RetryCancel, RadMessageIcon.Error);
                        if (result == DialogResult.Retry)
                        {
                            Invoke(new EventHandler(guiradbtnreportsave_Click));
                        }
                    }
                }
                else
                {
                    GuiCommon.IsFormChanged = true;
                    GuiCommon.ExitApp = GuiCommon.IsMenuItemShown ? 0 : 1;
                }

                CheckForSimualtionMode();                    
            }
            catch (Exception ex)
            {
                GUIExceptionHandler.HandleException(ex, this);
            }         
        }
         
        /**This event fires on save button click, saves edited measurement data in database & session object
        * */
        private void guiradbtnreportsave_Click(object sender, EventArgs e)
        {
            SaveChangesOnEdit(sender, e);        
        }

        /**This method is used to Save the measurement details into the database.
         */ 
        private void SaveMeasurementData(CrxStructPWVMeasurementData crxPWV)
        {
            // update measurement data
            // save data            
            crxPWV.StudyDateTime = DateTime.Parse(GuiCommon.PwvCurrentStudyDatetime, CrxCommon.gCI);
            int iRow = guiradgridReportAssessment.Rows.Count > 0 ? dbMagr.UpdatePWVMeasurementDetails(crxPWV) : dbMagr.SavePWVMeasurementDetails(crxPWV);

            if (iRow > 0)
            {
                // record updated successfully
                // populate session object                   

                // get the latest date from crxPWV with which data is updated
                GuiCommon.PwvCurrentStudyDatetime = crxPWV.StudyDateTime.ToString();
                CrxLogger.Instance.Write("GuiCommon.PwvCurrentStudyDatetime:(SaveMeasurementData) " + GuiCommon.PwvCurrentStudyDatetime);

                FillPatientAssessmentDetailsReport();
                guiradlblReportPwvDistance.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.LabelPwvDistance);

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
                        DateTime formatdate;
                        formatdate = Convert.ToDateTime(dsPWV.Tables[0].Rows[0][(int)CrxDBPWVMeasurementTableList.StudyDateTime].ToString());
                        guiradlblReportDateTimeDisplay.Text = string.Format("{0:g}", formatdate);
                        
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
                        PopulateCrxWithOtherValues(dsPWV);

                        // populating other details i.e statistcis information
                        PopulateCrxWithStatistics(dsPWV);
                        obj.Populate(crxPWV);
                        obj.Validate();
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

        /** This method fills crx struct with height & weight, blood pressure, distance values
         * */
        void PopulateCrxWithOtherValues(DataSet dsPwv)
        {
            crxPWV.HeightInCentimetres = (short)dsPwv.Tables[0].Rows[0][(int)CrxDBPWVMeasurementTableList.HeightInCentimetres];
            crxPWV.HeightInInches = (short)dsPwv.Tables[0].Rows[0][(int)CrxDBPWVMeasurementTableList.HeightInInches];
            crxPWV.WeightInKilograms = (short)dsPwv.Tables[0].Rows[0][(int)CrxDBPWVMeasurementTableList.WeightInKilograms];
            crxPWV.WeightInPounds = (short)dsPwv.Tables[0].Rows[0][(int)CrxDBPWVMeasurementTableList.WeightInPounds];

            crxPWV.BodyMassIndex = float.Parse(dsPwv.Tables[0].Rows[0][(int)CrxDBPWVMeasurementTableList.BodyMassIndex].ToString());
            crxPWV.Operator = dsPwv.Tables[0].Rows[0][(int)CrxDBPWVMeasurementTableList.Operator].ToString();
            crxPWV.Notes = dsPwv.Tables[0].Rows[0][(int)CrxDBPWVMeasurementTableList.Notes].ToString();
            crxPWV.BloodPressureEntryOption = short.Parse(dsPwv.Tables[0].Rows[0][(int)CrxDBPWVMeasurementTableList.BloodPressureEntryOption].ToString());

            crxPWV.SP = short.Parse(dsPwv.Tables[0].Rows[0][(int)CrxDBPWVMeasurementTableList.SP].ToString());
            crxPWV.DP = short.Parse(dsPwv.Tables[0].Rows[0][(int)CrxDBPWVMeasurementTableList.DP].ToString());
            crxPWV.MP = GuiConstants.SdefaultValue;

            // sets SP, DP & MP value
            // switch (crxPWV.BloodPressureEntryOption)
            // {
            //    case (int)CrxGenPwvValue.CrxGenBPOptSPandDP: 
            //        // sp & dp                  
            ////       break;
            //    case (int)CrxGenPwvValue.CrxGenBPOptSPandMP: 
            //        // sp & mp
            //        crxPWV.SP = short.Parse(dsPwv.Tables[0].Rows[0][(int)CrxDBPWVMeasurementTableList.SP].ToString());
            //        crxPWV.DP = GuiConstants.SdefaultValue;
            //        crxPWV.MP = short.Parse(dsPwv.Tables[0].Rows[0][(int)CrxDBPWVMeasurementTableList.MP].ToString());
            //        break;
            //    case (int)CrxGenPwvValue.CrxGenBPOptMPandDP:
            //        // dp & mp
            //        crxPWV.SP = GuiConstants.SdefaultValue;
            //        crxPWV.MP = short.Parse(dsPwv.Tables[0].Rows[0][(int)CrxDBPWVMeasurementTableList.MP].ToString());
            //        crxPWV.DP = short.Parse(dsPwv.Tables[0].Rows[0][(int)CrxDBPWVMeasurementTableList.DP].ToString());
            //        break;
            //    default:
            //        break;
            // }
            crxPWV.PWVDistanceMethod = short.Parse(dsPwv.Tables[0].Rows[0][(int)CrxDBPWVMeasurementTableList.PWVDistanceMethod].ToString());
            crxPWV.PWVDistance = short.Parse(dsPwv.Tables[0].Rows[0][(int)CrxDBPWVMeasurementTableList.PWVDistance].ToString());
            crxPWV.Direct = short.Parse(dsPwv.Tables[0].Rows[0][(int)CrxDBPWVMeasurementTableList.Direct].ToString());
            crxPWV.Carotid = short.Parse(dsPwv.Tables[0].Rows[0][(int)CrxDBPWVMeasurementTableList.Carotid].ToString());
            crxPWV.Cuff = short.Parse(dsPwv.Tables[0].Rows[0][(int)CrxDBPWVMeasurementTableList.Cuff].ToString());
            crxPWV.FemoraltoCuff = short.Parse(dsPwv.Tables[0].Rows[0][(int)CrxDBPWVMeasurementTableList.FemoraltoCuff].ToString());

            crxPWV.SystemIdentifier = bobj;
            crxPWV.GroupIdentifier = int.Parse(patientObj.groupStudyId.ToString());
            crxPWV.PatientNumberInternal = int.Parse(patientObj.patientNumber.ToString());
        }

        /** This method fills crx struct with statistics data
         * */
        void PopulateCrxWithStatistics(DataSet dsPwv)
        {
            crxPWV.Simulation = bool.Parse(dsPwv.Tables[0].Rows[0][(int)CrxDBPWVMeasurementTableList.Simulation].ToString());
            crxPWV.BloodPressureRange = dsPwv.Tables[0].Rows[0][(int)CrxDBPWVMeasurementTableList.BloodPressureRange].ToString();
            crxPWV.Age = short.Parse(dsPwv.Tables[0].Rows[0][(int)CrxDBPWVMeasurementTableList.Age].ToString());
            crxPWV.IsStandardDeviationValid = bool.Parse(dsPwv.Tables[0].Rows[0][(int)CrxDBPWVMeasurementTableList.IsStandardDeviationValid].ToString());
            crxPWV.IsFemoralSignalValid = bool.Parse(dsPwv.Tables[0].Rows[0][(int)CrxDBPWVMeasurementTableList.IsFemoralSignalValid].ToString());
            crxPWV.IsCarotidSignalValid = bool.Parse(dsPwv.Tables[0].Rows[0][(int)CrxDBPWVMeasurementTableList.IsCarotidSignalValid].ToString());
            crxPWV.CaptureTime = short.Parse(dsPwv.Tables[0].Rows[0][(int)CrxDBPWVMeasurementTableList.CaptureTime].ToString());
            crxPWV.MeanCorrectedTime = float.Parse(dsPwv.Tables[0].Rows[0][(int)CrxDBPWVMeasurementTableList.MeanCorrectedTime].ToString());
            crxPWV.MeanDeltaTime = float.Parse(dsPwv.Tables[0].Rows[0][(int)CrxDBPWVMeasurementTableList.MeanDeltaTime].ToString());
            crxPWV.MeanHeartRate = float.Parse(dsPwv.Tables[0].Rows[0][(int)CrxDBPWVMeasurementTableList.MeanHeartRate].ToString());
            crxPWV.MeanPulseWaveVelocity = float.Parse(dsPwv.Tables[0].Rows[0][(int)CrxDBPWVMeasurementTableList.MeanPulseWaveVelocity].ToString());
            crxPWV.SampleRate = short.Parse(dsPwv.Tables[0].Rows[0][(int)CrxDBPWVMeasurementTableList.SampleRate].ToString());
            crxPWV.StandardDeviation = float.Parse(dsPwv.Tables[0].Rows[0][(int)CrxDBPWVMeasurementTableList.StandardDeviation].ToString());
            crxPWV.CarotidSignalPulseHeight = float.Parse(dsPwv.Tables[0].Rows[0][(int)CrxDBPWVMeasurementTableList.CarotidSignalPulseHeight].ToString());
            crxPWV.CarotidSignalPulseHeightVariation = float.Parse(dsPwv.Tables[0].Rows[0][(int)CrxDBPWVMeasurementTableList.CarotidSignalPulseHeightVariation].ToString());
            crxPWV.CorrectionTime = float.Parse(dsPwv.Tables[0].Rows[0][(int)CrxDBPWVMeasurementTableList.CorrectionTime].ToString());
            crxPWV.DataRevision = short.Parse(dsPwv.Tables[0].Rows[0][(int)CrxDBPWVMeasurementTableList.DataRevision].ToString());
            crxPWV.FemoralSignalPulseHeight = float.Parse(dsPwv.Tables[0].Rows[0][(int)CrxDBPWVMeasurementTableList.FemoralSignalPulseHeight].ToString());
            crxPWV.NumberOfDeltas = short.Parse(dsPwv.Tables[0].Rows[0][(int)CrxDBPWVMeasurementTableList.NumberOfDeltas].ToString());
            crxPWV.NumberOfValidDeltas = short.Parse(dsPwv.Tables[0].Rows[0][(int)CrxDBPWVMeasurementTableList.NumberOfValidDeltas].ToString());
        }

        /**This method initializes Crx structure to update changes
        * */
        int InitializeCrx(CrxStructPWVMeasurementData crxPwv)
        {
            int flag = 0;

            // populate obj with entered data & check for validation
            // if it returns true then initialize crxPWV else return error & repopluate obj with original values                        
            if (ValidateSession())
            {
                // session object valid populate CRX object
                crxPwv.StudyDateTime = DateTime.Parse(GuiCommon.PwvCurrentStudyDatetime, CrxCommon.gCI);
                CrxLogger.Instance.Write("crxPwv.StudyDateTime: (InitializeCrx)" + crxPwv.StudyDateTime);   
                crxPwv.NormalRange = new float[0];
                crxPwv.ReferenceRange = new float[0];
                crxPwv.CarotidSignal = new ushort[0];
                crxPwv.FemoralSignal = new ushort[0];
                crxPwv.CarotidSignalFloatOnSets = new float[0];
                crxPwv.FemoralSignalFloatOnSets = new float[0];
                 
                CalculateHeightAndWeightToUpdate(crxPwv);

               // crxPwv.BodyMassIndex = guiradlblReportBmiValue.Text.Trim().Length > 0 ? float.Parse(guiradlblReportBmiValue.Text) : float.Parse(GuiConstants.DefaultValue.ToString());
                crxPwv.Operator = guiradtxtReportOperator.Text.Trim();
                crxPwv.Notes = guiradtxtReportNotes.Text.Trim();

                // Pritam
                // crxPwv.BloodPressureEntryOption = short.Parse(crxMgrObject.GeneralSettings.BloodPressureEntryOptions.ToString());
                crxPwv.BloodPressureEntryOption = short.Parse(crxMgrObject.BpSettings.BloodPressure.ToString());

                InitializeBPValues(crxPwv);

                CalculatePwvDistanceToUpdate(crxPwv);

                crxPwv.SystemIdentifier = bobj;
                crxPwv.GroupIdentifier = GuiCommon.GroupId;
                crxPwv.PatientNumberInternal = GuiCommon.PatientInternalNumber;
                
                // call recalculatepwvreport which will calculate PWV statistics & normal range values & will update biz session object.                             
                if (obj.RecalculatePWVReport(crxPwv))
                {
                    crxPwv.CarotidSignal = obj.carotidSignal.signal;
                    crxPwv.CarotidSignalFloatOnSets = obj.carotidSignal.floatOnsets;
                    crxPwv.CarotidSignalLength = short.Parse(obj.carotidSignal.signalLength.ToString());
                    crxPwv.CarotidSignalOnSetsLength = short.Parse(obj.carotidSignal.onsetsLength.ToString());
                    crxPwv.CarotidSignalPulseHeight = obj.carotidSignal.pulseHeight;
                    crxPwv.CarotidSignalPulseHeightVariation = obj.carotidSignal.pulseHeightVariation;
                    crxPwv.CorrectionTime = obj.correctionTime;
                    crxPwv.DataRevision = short.Parse(obj.dataRevision.ToString());
                    crxPwv.FemoralSignal = obj.femoralSignal.signal;
                    crxPwv.FemoralSignalFloatOnSets = obj.femoralSignal.floatOnsets;
                    crxPwv.FemoralSignalLength = short.Parse(obj.femoralSignal.signalLength.ToString());
                    crxPwv.FemoralSignalOnSetsLength = short.Parse(obj.femoralSignal.onsetsLength.ToString());
                    crxPwv.FemoralSignalPulseHeight = obj.femoralSignal.pulseHeight;
                    crxPwv.FemoralSignalPulseHeightVariation = obj.femoralSignal.pulseHeightVariation;
                    crxPwv.IsCarotidSignalValid = obj.isCarotidSignalValid;
                    crxPwv.IsFemoralSignalValid = obj.isFemoralSignalValid;
                    crxPwv.IsStandardDeviationValid = obj.isStandardDeviationValid;
                    crxPwv.MeanCorrectedTime = obj.meanCorrectedTime;
                    crxPwv.MeanDeltaTime = obj.meanDeltaTime;
                    crxPwv.MeanHeartRate = obj.meanHeartRate;
                    crxPwv.MeanPulseWaveVelocity = obj.meanPulseWaveVelocity;
                    crxPwv.NormalRange = obj.normalRange;
                    crxPwv.NumberOfDeltas = short.Parse(obj.numberOfDeltas.ToString());
                    crxPwv.NumberOfValidDeltas = short.Parse(obj.numberOfValidDeltas.ToString());
                    crxPwv.ReferenceRange = obj.referenceRange;
                    crxPwv.ReferenceRangeDistance = obj.referenceRangeDistance;
                    crxPwv.ReferenceRangePulseWaveVelocity = obj.referenceRangePulseWaveVelocity;
                    crxPwv.SampleRate = short.Parse(obj.sampleRate.ToString());
                    crxPwv.Simulation = obj.simulation;
                }
                else
                {
                    // error recalculating data
                    // do not save in database
                    flag = 2;
                }

                // binds statistics information
                crxPwv.IsStandardDeviationValid = obj.isStandardDeviationValid;
                crxPwv.IsCarotidSignalValid = obj.isCarotidSignalValid;
                crxPwv.IsFemoralSignalValid = obj.isFemoralSignalValid;
                crxPwv.MeanHeartRate = obj.meanHeartRate;
                crxPwv.MeanPulseWaveVelocity = obj.meanPulseWaveVelocity;
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
            // switch (crxPWV.BloodPressureEntryOption)
            // {
            //    case (int)CrxGenPwvValue.CrxGenBPOptSPandDP: 
                    // sp & dp
                    crxPWV.SP = string.IsNullOrEmpty(guiradtxtReportBloodPressure1.Text.Trim()) ? GuiConstants.SdefaultValue : short.Parse(guiradtxtReportBloodPressure1.Text.Trim());
                    crxPWV.DP = string.IsNullOrEmpty(guiradtxtReportBloodPressure2.Text.Trim()) ? GuiConstants.SdefaultValue : short.Parse(guiradtxtReportBloodPressure2.Text.Trim());
                    crxPWV.MP = GuiConstants.SdefaultValue;
            ////        break;
            //    case (int)CrxGenPwvValue.CrxGenBPOptSPandMP: 
            //        // sp & mp
            //        crxPWV.SP = string.IsNullOrEmpty(guiradtxtReportBloodPressure1.Text.Trim()) ? GuiConstants.SdefaultValue : short.Parse(guiradtxtReportBloodPressure1.Text.Trim());
            //        crxPWV.DP = GuiConstants.SdefaultValue;
            //        crxPWV.MP = string.IsNullOrEmpty(guiradtxtReportBloodPressure2.Text.Trim()) ? GuiConstants.SdefaultValue : short.Parse(guiradtxtReportBloodPressure2.Text.Trim());
            //        break;
            //    case (int)CrxGenPwvValue.CrxGenBPOptMPandDP:
            //        // dp & mp
            //        crxPWV.SP = GuiConstants.SdefaultValue;
            //        crxPWV.MP = string.IsNullOrEmpty(guiradtxtReportBloodPressure1.Text.Trim()) ? GuiConstants.SdefaultValue : short.Parse(guiradtxtReportBloodPressure1.Text.Trim());
            //        crxPWV.DP = string.IsNullOrEmpty(guiradtxtReportBloodPressure2.Text.Trim()) ? GuiConstants.SdefaultValue : short.Parse(guiradtxtReportBloodPressure2.Text.Trim());
            //        break;
            //    default:
            //        break;
            // }
        }

        /** This method validates session data
         * */
        bool ValidateSession()
        {
            // Commenting the below code as group name is not included in Clinical mode.
          //  obj.heightAndWeight.bodyMassIndex = guiradlblReportBmiValue.Text.Trim().Length > 0 ? float.Parse(guiradlblReportBmiValue.Text) : float.Parse(GuiConstants.DefaultValue.ToString());
            obj.operatorId = guiradtxtReportOperator.Text.Trim();
            obj.notes = guiradtxtReportNotes.Text.Trim();

            // Pritam
            // obj.bloodPressureEntryOption = ushort.Parse(crxMgrObject.GeneralSettings.BloodPressureEntryOptions.ToString());
             obj.bloodPressureEntryOption = ushort.Parse(crxMgrObject.BpSettings.BloodPressure.ToString());

            CalculateHeightAndWeightToValidateSession();
            CalculatePwvDistanceToValidateSession();
                        
            // sets SP, DP & MP value
            // Pritam

            // switch (crxMgrObject.GeneralSettings.BloodPressureEntryOptions)
            // switch (crxMgrObject.BpSettings.BloodPressure)
            // {
            //    case (int)CrxGenPwvValue.CrxGenBPOptSPandDP: 
                    // sp & dp
                    obj.bloodPressure.SP.Reading = string.IsNullOrEmpty(guiradtxtReportBloodPressure1.Text.Trim()) ? GuiConstants.DefaultValue : ushort.Parse(guiradtxtReportBloodPressure1.Text.Trim());
                    obj.bloodPressure.DP.Reading = string.IsNullOrEmpty(guiradtxtReportBloodPressure2.Text.Trim()) ? GuiConstants.DefaultValue : ushort.Parse(guiradtxtReportBloodPressure2.Text.Trim());
                    obj.bloodPressure.MP.Reading = GuiConstants.DefaultValue;

            ////        break;
            //    case (int)CrxGenPwvValue.CrxGenBPOptSPandMP:
            //        // sp & mp
            //        obj.bloodPressure.SP.Reading = string.IsNullOrEmpty(guiradtxtReportBloodPressure1.Text.Trim()) ? GuiConstants.DefaultValue : ushort.Parse(guiradtxtReportBloodPressure1.Text.Trim());
            //        obj.bloodPressure.DP.Reading = GuiConstants.DefaultValue;
            //        obj.bloodPressure.MP.Reading = string.IsNullOrEmpty(guiradtxtReportBloodPressure2.Text.Trim()) ? GuiConstants.DefaultValue : ushort.Parse(guiradtxtReportBloodPressure2.Text.Trim());
            //        break;
            //    case (int)CrxGenPwvValue.CrxGenBPOptMPandDP:
            //        // dp & mp
            //        obj.bloodPressure.SP.Reading = GuiConstants.DefaultValue;
            //        obj.bloodPressure.MP.Reading = string.IsNullOrEmpty(guiradtxtReportBloodPressure1.Text.Trim()) ? GuiConstants.DefaultValue : ushort.Parse(guiradtxtReportBloodPressure1.Text.Trim());
            //        obj.bloodPressure.DP.Reading = string.IsNullOrEmpty(guiradtxtReportBloodPressure2.Text.Trim()) ? GuiConstants.DefaultValue : ushort.Parse(guiradtxtReportBloodPressure2.Text.Trim());
            //        break;
            //    default:
            //        break;
            // }
                    if (!IsHeightOutsideIntegerLimits)
                    {
                        bool isValidate = obj.Validate();
                        if (isValidate)
                        {
                            GetValidationForHeight(int.Parse(obj.heightAndWeight.heightInCentimetres.ToString()));
                            return !IsHeightOutsideIntegerLimits;
                        }
                        else
                        {
                            return isValidate;
                        }
                    }
                    else
                    {
                        return false;
                    }
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
                case (int)CrxGenPwvValue.CrxPwvDistMethodSubtract:
                    if ((guiradtxtCarotid.Text.Length > 0) && (guiradtxtReportCuff.Text.Length > 0) && (guiradtxtReportFemoToCuff.Text.Length > 0))
                    {
                        crxPWV.Direct = GuiConstants.SdefaultValue;
                        crxPWV.Carotid = short.Parse(guiradtxtCarotid.Text.Trim());
                        crxPWV.Cuff = short.Parse(guiradtxtReportCuff.Text.Trim());
                        crxPWV.FemoraltoCuff = short.Parse(guiradtxtReportFemoToCuff.Text.Trim());
                        crxPWV.PWVDistance = (short)(crxPWV.Cuff - crxPWV.Carotid - crxPWV.FemoraltoCuff);
                    }

                    break;

                case (int)CrxGenPwvValue.CrxPwvDistMethodDirect:
                    if ((guiradtxtCarotid.Text.Length > 0) && (guiradtxtReportFemoToCuff.Text.Length > 0))
                    {
                        crxPWV.Direct = short.Parse(guiradtxtCarotid.Text.Trim());
                        crxPWV.Carotid = GuiConstants.SdefaultValue;
                        crxPWV.Cuff = GuiConstants.SdefaultValue;
                        crxPWV.FemoraltoCuff = short.Parse(guiradtxtReportFemoToCuff.Text.Trim());
                        crxPWV.PWVDistance = (short)(crxPWV.Direct - crxPWV.FemoraltoCuff);
                    }

                    break;
                default:
                    break;
            }

            if (crxMgrObject.PwvSettings.PWVDistanceUnits.Equals((int)CrxGenPwvValue.CrxPwvDistDistUnitsCM))
            {
               crxPWV.Direct = crxPWV.Direct.Equals(GuiConstants.SdefaultValue) ? crxPWV.Direct : (short)(crxPWV.Direct * GuiConstants.DivisionFactor);
               crxPWV.Carotid = crxPWV.Carotid.Equals(GuiConstants.SdefaultValue) ? crxPWV.Carotid : (short)(crxPWV.Carotid * GuiConstants.DivisionFactor);
               crxPWV.Cuff = crxPWV.Cuff.Equals(GuiConstants.SdefaultValue) ? crxPWV.Cuff : (short)(crxPWV.Cuff * GuiConstants.DivisionFactor);
               crxPWV.FemoraltoCuff = (short)(crxPWV.FemoraltoCuff * GuiConstants.DivisionFactor);
               crxPWV.PWVDistance = (short)(crxPWV.PWVDistance * GuiConstants.DivisionFactor);
            }
        }

        /**This method calcuates PWV distance values to validate obj
       * */
        void CalculatePwvDistanceToValidateSession()
        {
            // initially form session obj      

            // This line is commented to show pwv distance method details according to database
            // value for that perticuler assesment instead of showing for the latest Config value, so it
            // will not give error which was appearing on edit when we were changing distance method from settings to 
            // other distance method(different than which was actual for that record) (22 august 2011 PWVSW-368)
            // obj.distanceMethod = ushort.Parse(crxMgrObject.PwvSettings.PWVDistanceMethod.ToString());
            obj.distanceMethod = ushort.Parse(crxPWV.PWVDistanceMethod.ToString());
                        
            // calculate & intialise PWV distance only if there is change
            switch (obj.distanceMethod)
            {
                case (int)CrxGenPwvValue.CrxPwvDistMethodSubtract:
                    CalculatePwvDistanceForSubtractionMethod();
                    break;

                case (int)CrxGenPwvValue.CrxPwvDistMethodDirect:
                    CalculatePwvDistanceForDirectMethod();

                    break;
                default:
                    break;
            }
        }

        /** Below function restrict user from adding invalid value for the height
         */
        private void GetValidationForHeight(int heightValue)
        {
            if (heightValue > short.MaxValue || heightValue < 0)
            {
                string field = objValidateReport.GetLabelText(guiradtxtReportHeight.Tag.ToString());
                IsHeightOutsideIntegerLimits = true;
                string err = string.Format(oMsgMgr.GetMessage(CrxStructCommonResourceMsg.GuiLimitsFormat), field, 0, string.Empty, short.MaxValue, string.Empty);
                RadMessageBox.Show(err, oMsgMgr.GetMessage(CrxStructCommonResourceMsg.SystemError), MessageBoxButtons.OK, RadMessageIcon.Error);
                guiradtxtReportHeight.Focus();
                guiradtxtReportHeight.Text = string.Empty;
            }
            else
            {
                IsHeightOutsideIntegerLimits = false;
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
                                         
                // check if value is within min & max limits               
                GetValidationForHeight(heightinches);               
                obj.heightAndWeight.heightInInches = heightinches == 0 ? GuiConstants.DefaultValue : ushort.Parse(heightinches.ToString());

              // obj.heightAndWeight.weightInPounds = string.IsNullOrEmpty(guiradtxtReportWeight.Text.Trim()) ? GuiConstants.DefaultValue : ushort.Parse(guiradtxtReportWeight.Text.Trim());
            }
            else
            {
                obj.heightAndWeight.heightInCentimetres = string.IsNullOrEmpty(guiradtxtReportHeight.Text.Trim()) ? GuiConstants.DefaultValue : ushort.Parse(guiradtxtReportHeight.Text.Trim());
                IsHeightOutsideIntegerLimits = false;

               // obj.heightAndWeight.weightInKilograms = string.IsNullOrEmpty(guiradtxtReportWeight.Text.Trim()) ? GuiConstants.DefaultValue : ushort.Parse(guiradtxtReportWeight.Text.Trim());               
            }
        }

        /**This method calculates height & weight to update changes
      */
        void CalculateHeightAndWeightToUpdate(CrxStructPWVMeasurementData crxPwv)
        {
            crxPwv.HeightInInches = crxPwv.WeightInPounds = crxPwv.HeightInCentimetres = crxPwv.WeightInKilograms = GuiConstants.SdefaultValue;

            // calculates height in inches & centimeters
            if (guiradtxtReportHeightInches.Visible)
            {
                int heightinches = (int.Parse((string.IsNullOrEmpty(guiradtxtReportHeight.Text.Trim()) ? "0" : guiradtxtReportHeight.Text.Trim())) * 12) + int.Parse((string.IsNullOrEmpty(guiradtxtReportHeightInches.Text.Trim()) ? "0" : guiradtxtReportHeightInches.Text.Trim()));
                crxPwv.HeightInInches = heightinches == 0 ? GuiConstants.SdefaultValue : short.Parse(heightinches.ToString());

              // crxPwv.WeightInPounds = string.IsNullOrEmpty(guiradtxtReportWeight.Text.Trim()) ? GuiConstants.SdefaultValue : short.Parse(guiradtxtReportWeight.Text.Trim());        
            }
            else
            {
                crxPwv.HeightInCentimetres = string.IsNullOrEmpty(guiradtxtReportHeight.Text.Trim()) ? GuiConstants.SdefaultValue : short.Parse(guiradtxtReportHeight.Text.Trim());

              // crxPwv.WeightInKilograms = string.IsNullOrEmpty(guiradtxtReportWeight.Text.Trim()) ? GuiConstants.SdefaultValue : short.Parse(guiradtxtReportWeight.Text.Trim());
            }
        }        

        /** Plots superimposed wave form series from BizSession.xls
         * */
        private void SuperImposedWaveForm()
        {
            try
            {
                guichartSuperImposedWaveform.ChartAreas[0].BackColor = Color.White;                

                // crxMgrObject.PwvSettings.PWVDistanceMethod = obj.distanceMethod;
                ushort[] femoralSignal = obj.femoralSignal.signal;
                obj.femoralSignal.CaptureSignal(femoralSignal, obj.femoralSignal.signalLength, 0, 0);
                ushort[] carotidSignal = obj.carotidSignal.signal;
                obj.carotidSignal.CaptureSignal(carotidSignal, obj.carotidSignal.signalLength, 0, 0);
                bool status = obj.Calculate();

               // CrxLogger.Instance.Write("Status: (SuperImposedWaveform)" + status.ToString()); 
                 // calling method to bind statistics returned from calculate() method
                BindPWVStatistics();
                
                if (status)
                {
                    // plot super impose wave form
                    ushort[] femoralSignalToPlot = obj.femoralSignal.signal;
                    float[] femoralOnSetPoints = obj.femoralSignal.floatOnsets;
                    ushort[] carotidSignalToPlot = obj.carotidSignal.signal;
                    float[] carotidOnSetPoints = obj.carotidSignal.floatOnsets;

                    PlotSuperImposedWaveform(femoralSignalToPlot, femoralOnSetPoints, carotidSignalToPlot, carotidOnSetPoints, obj.femoralSignal.signalLength);
                }
                else
                { 
                    // dont plot & show error message
                    RadMessageBox.Show(this, oMsgMgr.GetMessage(CrxStructCommonResourceMsg.DbCorrupt), oMsgMgr.GetMessage(CrxStructCommonResourceMsg.SystemError), MessageBoxButtons.OK);

                    // log the error
                    CrxLogger.Instance.Write(oMsgMgr.GetMessage(CrxStructCommonResourceMsg.DbCorrupt));
                }
            }
            catch (Exception ex)
            {
                CrxLogger.Instance.Write(ex.StackTrace);
                GUIExceptionHandler.HandleException(ex, this);
            }
        }

        /**This method is a generic method which decides which chart needs to be plotted i.e. either Femoral or Carotid.
         * This method was written to avoid duplicate code.
         */ 
        private void PlotSuperImposedWaveform(IList<ushort> femoralSignalToPlot, float[] femoralOnSetPoints, IList<ushort> carotidSignalToPlot, float[]carotidOnSetPoints, ushort signalLength)
        {
            const double ChartHeight = 500;
            const double MinXValue = 0;

            // plot on the waveform.
            double dblMaxXValue = signalLength;

            // new chart area
            guichartSuperImposedWaveform.ChartAreas.Clear();
            guichartSuperImposedWaveform.ChartAreas.Add(new ChartArea("area"));
            guichartSuperImposedWaveform.ChartAreas["area"].AxisY.Enabled = AxisEnabled.False;
            guichartSuperImposedWaveform.ChartAreas["area"].AxisX.Enabled = AxisEnabled.False;
            guichartSuperImposedWaveform.ChartAreas["area"].AxisX.MajorGrid.Enabled = false;
           
            guichartSuperImposedWaveform.ChartAreas["area"].AxisY2.MajorGrid.Enabled = false;
            guichartSuperImposedWaveform.ChartAreas["area"].AxisY2.Interval = 1;
            guichartSuperImposedWaveform.ChartAreas["area"].AxisY2.Minimum = ChartHeight * GuiConstants.ChartAreaMinimumY;
            guichartSuperImposedWaveform.ChartAreas["area"].AxisY2.Maximum = ChartHeight * GuiConstants.ChartAreaMaximumY;
            guichartSuperImposedWaveform.ChartAreas["area"].AxisY2.LabelStyle.Enabled = false;
            guichartSuperImposedWaveform.ChartAreas["area"].AxisY2.MajorTickMark.Enabled = false;
            guichartSuperImposedWaveform.ChartAreas["area"].AxisY2.LineDashStyle = ChartDashStyle.NotSet;

            // set y axis
            guichartSuperImposedWaveform.ChartAreas["area"].AxisY.Minimum = ChartHeight * GuiConstants.ChartAreaMinimumY;
            guichartSuperImposedWaveform.ChartAreas["area"].AxisY.Maximum = ChartHeight * GuiConstants.ChartAreaMaximumY;
            guichartSuperImposedWaveform.ChartAreas["area"].AxisY.Interval = 1;

            // set x axis
            guichartSuperImposedWaveform.ChartAreas["area"].AxisX.Minimum = MinXValue;
            guichartSuperImposedWaveform.ChartAreas["area"].AxisX.Maximum = dblMaxXValue;
            guichartSuperImposedWaveform.ChartAreas["area"].AxisX.Interval = 1;

            // initialize series,chartype,add points to series and finally add series to chart.
            // Series for tonometer
            guichartSuperImposedWaveform.Series.Clear();
            
            // plot carotid series
            PlotCarotidSeries(carotidSignalToPlot, carotidOnSetPoints, signalLength, Color.Blue);
            
            // plot femoral series
            PlotFemoralSeries(femoralSignalToPlot, femoralOnSetPoints, signalLength, Color.FromArgb(54, 64, 86));                       
        }

        /** This method plots series & onSet points for carotid series
        * */
        private void PlotCarotidSeries(IList<ushort> signalToPlot, float[] onSetPoints, ushort signalLength, Color seriesColor)
        {
            Series tonometerOneSeries = new Series
            {
                ChartType = SeriesChartType.FastLine,
                Color = seriesColor,
                XValueType = ChartValueType.Auto,
                YValuesPerPoint = 1,
                ChartArea = "area",
                YAxisType = AxisType.Secondary,
            };

            Hashtable carotidFemoralTable = new Hashtable();
            tonometerOneSeries.Points.Clear();

                    for (int i = 0; i < signalLength; i++)
                    {
                        if (signalToPlot[i] > guichartSuperImposedWaveform.ChartAreas[0].AxisY2.Maximum)
                        {
                            guichartSuperImposedWaveform.ChartAreas["area"].AxisY2.Maximum = signalToPlot[i] * GuiConstants.ChartAreaMaximumY;
                        }

                        if (signalToPlot[i] < guichartSuperImposedWaveform.ChartAreas[0].AxisY2.Minimum)
                        {
                            guichartSuperImposedWaveform.ChartAreas["area"].AxisY2.Minimum = signalToPlot[i] * GuiConstants.ChartAreaMinimumY;
                        }

                        /*Begin: AtCor-<Drop2>-<Sprint4>, TM, <PWVSW-327>,<16 August 2011>
                 */
                        tonometerOneSeries.Points.AddXY(i, signalToPlot[i]);
                        carotidFemoralTable[i] = signalToPlot[i];
                    }

                    Series tonometerCarotidOnsetSeriesOne = new Series
                    {
                        ChartType = SeriesChartType.Point,
                        Color = Color.Green,
                        YAxisType = AxisType.Secondary
                    };

                    Series tonometerCarotidOnsetSeriesTwo = new Series
                    {
                        ChartType = SeriesChartType.Point,
                        Color = Color.Red,
                        YAxisType = AxisType.Secondary,
                    };

                    tonometerCarotidOnsetSeriesOne.Points.Clear();
                    tonometerCarotidOnsetSeriesTwo.Points.Clear();

            for (int j = 0; j < onSetPoints.Length; j++)
            {
                int valueToPLot = int.Parse(Math.Round(double.Parse(onSetPoints[j].ToString()), MidpointRounding.ToEven).ToString());
                int valueToPLot1 = Math.Abs(valueToPLot);

                if (valueToPLot < 0)
                {
                    tonometerCarotidOnsetSeriesTwo.Points.AddXY(valueToPLot1, carotidFemoralTable[valueToPLot1]);
                    tonometerCarotidOnsetSeriesTwo.Points[tonometerCarotidOnsetSeriesTwo.Points.Count - 1].MarkerStyle = MarkerStyle.Circle;
                }
                else
                {
                    tonometerCarotidOnsetSeriesOne.Points.AddXY(valueToPLot1, carotidFemoralTable[valueToPLot1]);
                    tonometerCarotidOnsetSeriesOne.Points[tonometerCarotidOnsetSeriesOne.Points.Count - 1].MarkerStyle = MarkerStyle.Circle;
                }
            }

            guichartSuperImposedWaveform.Series.Add(tonometerOneSeries);
            guichartSuperImposedWaveform.Series.Add(tonometerCarotidOnsetSeriesOne);
            guichartSuperImposedWaveform.Series.Add(tonometerCarotidOnsetSeriesTwo);
            guichartSuperImposedWaveform.Invalidate();
        }

        /** This method plots series & onSet points for femoral series
* */
        private void PlotFemoralSeries(IList<ushort> signalToPlot, float[] onSetPoints, ushort signalLength, Color seriesColor)
        {
            const double ChartHeight = 500;
            Series tonometerTwoSeries = new Series
            {
                ChartType = SeriesChartType.FastLine,
                Color = seriesColor,
                XValueType = ChartValueType.Auto,
                YValuesPerPoint = 1,
                ChartArea = "area"
            };

            Hashtable carotidFemoralTable = new Hashtable();
            tonometerTwoSeries.Points.Clear();

            guichartSuperImposedWaveform.ChartAreas["area"].AxisY.Minimum = ChartHeight * GuiConstants.ChartAreaMinimumY;
            guichartSuperImposedWaveform.ChartAreas["area"].AxisY.Maximum = ChartHeight * GuiConstants.ChartAreaMaximumY;
            for (int i = 0; i < signalLength; i++)
            {
                if (signalToPlot[i] > guichartSuperImposedWaveform.ChartAreas[0].AxisY.Maximum)
                {
                    guichartSuperImposedWaveform.ChartAreas["area"].AxisY.Maximum = signalToPlot[i] * GuiConstants.ChartAreaMaximumY;
                }

                if (signalToPlot[i] < guichartSuperImposedWaveform.ChartAreas[0].AxisY.Minimum)
                {
                    guichartSuperImposedWaveform.ChartAreas["area"].AxisY.Minimum = signalToPlot[i] * GuiConstants.ChartAreaMinimumY;
                }

                /*Begin: AtCor-<Drop2>-<Sprint4>, TM, <PWVSW-327>,<16 August 2011>
         */
                tonometerTwoSeries.Points.AddXY(i, signalToPlot[i]);
                carotidFemoralTable[i] = signalToPlot[i];
            }

            Series tonometerFemoralOnsetSeriesOne = new Series
            {
                ChartType = SeriesChartType.Point,
                Color = Color.Green
            };

            Series tonometerFemoralOnsetSeriesTwo = new Series
            {
                ChartType = SeriesChartType.Point,
                Color = Color.Red
            };

            tonometerFemoralOnsetSeriesTwo.Points.Clear();
            tonometerFemoralOnsetSeriesOne.Points.Clear();

            for (int j = 0; j < onSetPoints.Length; j++)
            {
                int valueToPLot = int.Parse(Math.Round(double.Parse(onSetPoints[j].ToString()), MidpointRounding.ToEven).ToString());
                int valueToPLot1 = Math.Abs(valueToPLot);

                if (valueToPLot < 0)
                {
                    tonometerFemoralOnsetSeriesTwo.Points.AddXY(valueToPLot1, carotidFemoralTable[valueToPLot1]);
                    tonometerFemoralOnsetSeriesTwo.Points[tonometerFemoralOnsetSeriesTwo.Points.Count - 1].MarkerStyle = MarkerStyle.Circle;
                }
                else
                {
                    tonometerFemoralOnsetSeriesOne.Points.AddXY(valueToPLot1, carotidFemoralTable[valueToPLot1]);
                    tonometerFemoralOnsetSeriesOne.Points[tonometerFemoralOnsetSeriesOne.Points.Count - 1].MarkerStyle = MarkerStyle.Circle;
                }
            }

            guichartSuperImposedWaveform.Series.Add(tonometerTwoSeries);
            guichartSuperImposedWaveform.Series.Add(tonometerFemoralOnsetSeriesOne);
            guichartSuperImposedWaveform.Series.Add(tonometerFemoralOnsetSeriesTwo);
            guichartSuperImposedWaveform.Invalidate();
        }

        /**This event fires when checkbox is checked or unchecked on assessment gridview
          * */
        private void guiradgridReportAssessment_ValueChanged(object sender, EventArgs e)
        {            
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
                guiradbtnDelete.Enabled = true;
                if (recordSelected == 1)
                {                    
                    dateToCompare = datetime.Replace(oMsgMgr.GetMessage(CrxStructCommonResourceMsg.GuiDisplayComma), string.Empty);
                }
                
                DisplayAnalysisScreen();
                PlotAnalysisTrendCharts(datetime);
                objDefaultWindow.radtabReport.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.TabAnalysis);
            }
            else if (recordSelected == 1)
            {                
                EnableDisableReportPrintButton(true);

                // if only 1 record is selected in assessment grid bind the measurement details 
                // pertaining to that patient
                guiradpnlAnalysis.Visible = false;
                guiradbtnDelete.Enabled = true;
                objDefaultWindow.radtabReport.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.TabReport);
                
                dateToCompare = datetime.Replace(oMsgMgr.GetMessage(CrxStructCommonResourceMsg.GuiDisplayComma), string.Empty);
                guiradbtnreportedit.Enabled = true;
                CheckLastAssessmentSelected(dateToCompare);       
         
                // when record selected is only one display record as per assessment selected
                DisplayReportForSelectedAssesment(dateToCompare);                
            }
            else if (recordSelected > 1)
            {                
                DisplayAnalysisScreen();

                // EnableDisableReportPrintButton(false);

                //// display analysis screen
                // guiradbtnreportedit.Enabled = false;
                // guiradpnlAnalysis.Visible = true;
                // guiradbtnRepeat.Enabled = false;
                // guiradbtnDelete.Enabled = true;
                // objDefaultWindow.radtabCapture.Enabled = false;
                // ReportPWVDisplayMode(true);
                PlotAnalysisTrendCharts(datetime);
                objDefaultWindow.radtabReport.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.TabAnalysis);
            }
            else if (recordSelected == 0)
            {
                EnableDisableReportPrintButton(true); 

                // disable delete & edit button when no record is selected
                guiradbtnDelete.Enabled = false;
                guiradbtnreportedit.Enabled = false;
                guiradbtnPrint.Enabled = false;
                CheckLastAssessmentSelected(string.Empty);
            }
            else
            {
                EnableDisableReportPrintButton(true);

                // for any other condition besides above, show report screen & enable capture & repeat buttons
                guiradbtnreportedit.Enabled = false;
                guiradpnlAnalysis.Visible = false;
                if (!GuiCommon.IsWaitIntervalImposed)
                {
                    guiradbtnRepeat.Enabled = true;
                    objDefaultWindow.radtabCapture.Enabled = true;
                }

                objDefaultWindow.radtabReport.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.TabReport);
            }
        }     
              
        /** This method plots normal range graph
         * */
        private void PlotNormalRangeGraph()
        {
            try
            {
                // set the location and plot normal range series
                guichartNormalRange.Location = new Point(331, 232);
                if (CrxConfigManager.Instance.PwvSettings.NormalRange)
                {
                    PlotNormalReferenceRange(guichartNormalRange, obj.normalRange, AxisType.Primary, AxisType.Primary);
                }                
                else
                {
                    guichartNormalRange.Visible = false;
                    guiradlbReportNormalRange.Visible = false;
                }         
            }
            catch (Exception ex)
            {
                GUIExceptionHandler.HandleException(ex, this);
            }            
        }

        /** This method plots reference range graph
       * */
        private void PlotReferenceRangeGraph()
        {
            try
            {
                // set the location and plot reference range series
                guichartReferenceRange.Location = new Point(650, 232);
                if (CrxConfigManager.Instance.PwvSettings.ReferenceRange)
                {
                    PlotNormalReferenceRange(guichartReferenceRange, obj.referenceRange, AxisType.Secondary, AxisType.Primary);
                }
                else
                {
                    guichartReferenceRange.Visible = false;
                    guiradlblReportReferenceRange.Visible = false;
                    guiradlblReportBpRange.Visible = false;
                    guiradlblRefRangeDescription.Visible = false;
                    guireportradlblReferenceMsg.Visible = false;
                }         
            }
            catch (Exception ex)
            {
                GUIExceptionHandler.HandleException(ex, this);
            }
        }

        /** This is a common generic method to plot both General and healthy population chart.
         * It gets called from both PlotNormalRangeGraph() and PlotReferenceRangeGraph() methods.
         */
        private void PlotNormalReferenceRange(Chart rangeChart, float[] rangeToPlot, AxisType yAxisType, AxisType xAxisType)
        {
            const int NormalRefYInterval = 5; // interval used for y axis for normal & reference range graph
            const int NormalRefXInterval = 15; // interval used for x axis for normal & reference range graph
            const int ChartYAxisMin = 4;
            const int ChartYAxisMax = 25; 

            // set y axis (normal range values from Bizsession object in float)
            float[] normalReferenceRange = rangeToPlot;
            float[] sortedNormalReferenceRange = normalReferenceRange;
            Array.Sort(sortedNormalReferenceRange);

            rangeChart.Series.Clear();

            switch (yAxisType)
            {                
                case AxisType.Secondary:
                    rangeChart.ChartAreas[0].AxisY2.Minimum = ChartYAxisMin; // double.Parse(sortedNormalReferenceRange[0].ToString());
                    rangeChart.ChartAreas[0].AxisY2.Maximum = ChartYAxisMax; // double.Parse(sortedNormalReferenceRange[sortedNormalReferenceRange.Length - 1].ToString());
                    rangeChart.ChartAreas[0].AxisY2.Title = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.ReportNormalrangeYAxisTitle);
                    rangeChart.ChartAreas[0].AxisY2.TitleFont = new Font(GuiConstants.FontName, rangeChart.ChartAreas[0].AxisY2.TitleFont.Size, FontStyle.Bold);
                    rangeChart.ChartAreas[0].AxisY2.Interval = NormalRefYInterval;
                    break;

                default:  // case AxisType.Primary:
                    rangeChart.ChartAreas[0].AxisY.Minimum = ChartYAxisMin; // double.Parse(sortedNormalReferenceRange[0].ToString());
                    rangeChart.ChartAreas[0].AxisY.Maximum = ChartYAxisMax; // double.Parse(sortedNormalReferenceRange[sortedNormalReferenceRange.Length - 1].ToString());
                    rangeChart.ChartAreas[0].AxisY.Title = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.ReportNormalrangeYAxisTitle);
                    rangeChart.ChartAreas[0].AxisY.TitleFont = new Font(GuiConstants.FontName, rangeChart.ChartAreas[0].AxisY.TitleFont.Size, FontStyle.Bold);
                    rangeChart.ChartAreas[0].AxisY.Interval = NormalRefYInterval;
                    break;              
            }         

            // set x axis
            rangeChart.ChartAreas[0].AxisX.Minimum = BizConstants.MINIMUM_REFERENCE_RANGE_AGE; // 20
            rangeChart.ChartAreas[0].AxisX.Maximum = BizConstants.MAXIMUM_REFERENCE_RANGE_AGE; // 90;
            rangeChart.ChartAreas[0].AxisX.Title = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.ReportNormalrangeXAxisTitle);
            rangeChart.ChartAreas[0].AxisX.TitleFont = new Font(GuiConstants.FontName, rangeChart.ChartAreas[0].AxisX.TitleFont.Size, FontStyle.Bold);
            rangeChart.ChartAreas[0].AxisX.Interval = NormalRefXInterval;

            // initialize series,chartype,add points to series and finally add series to chart.            
            // set display properties for normal range graph
            Series rangeSeries = new Series
                                     {
                ChartType = SeriesChartType.Area,
                Color = Color.Green,
                BorderColor = Color.Black,
                BorderWidth = 1,
                BackGradientStyle = GradientStyle.TopBottom,
                YAxisType = yAxisType,
                XAxisType = xAxisType
            };

            rangeSeries.Points.Clear();

            int ageToPlot = BizConstants.MINIMUM_REFERENCE_RANGE_AGE;
            for (int i = 0; i < normalReferenceRange.Length; i++)
            {
                rangeSeries.Points.AddXY(ageToPlot + i, normalReferenceRange[i]);
            }

            rangeChart.Series.Add(rangeSeries);

            // set properties for series 2 for plotting bubble
            Series rangeSeries2 = new Series
                                      {
                ChartType = SeriesChartType.Bubble,
                Color = Color.FromArgb(92, 81, 238),
                CustomProperties = "BubbleMaxSize=15",
                MarkerStyle = MarkerStyle.Circle,
                ShadowOffset = 5,
                YAxisType = yAxisType,
                XAxisType = xAxisType
            };

            rangeSeries2.Points.Clear();
            rangeSeries2.Points.AddXY(double.Parse(obj.patientAge.ToString()), double.Parse(obj.meanPulseWaveVelocity.ToString("#0")));

            rangeChart.Series.Add(rangeSeries2);
            rangeChart.Invalidate();
        }

        /** This event deletes assessments of selected patients
         * */
        private void guiradbtnDelete_Click(object sender, EventArgs e)
        {
            try
            {
               // recordsToDelete = 0;
               // string dateWithComma = GetCommaSeparatedDates();                
                // display confirmation message box
                DialogResult result = RadMessageBox.Show(this, oMsgMgr.GetMessage(CrxStructCommonResourceMsg.DeletePwvMsg).Replace("{0}", recordsToDelete.ToString()), oMsgMgr.GetMessage(CrxStructCommonResourceMsg.SystemError), MessageBoxButtons.YesNo);

                if (result == DialogResult.Yes)
                {
                    // delete selected records
                    CrxStructPWVMeasurementData crxData = new CrxStructPWVMeasurementData
                                                              {
                                                                  SystemIdentifier = bobj,
                                                                  GroupIdentifier = GuiCommon.GroupId,
                                                                  PatientNumberInternal =
                                                                      GuiCommon.PatientInternalNumber
                                                              };
                    int del = dbMagr.DeletePWVMeasurementDetails(crxData, dateWithComma);

                    if (del == 1)
                    {
                        // records deleted successfully, bind assessment grid
                        FillPatientAssessmentDetailsReport();
                        CheckLastAssessmentSelected(dateToCompare);

                        // guiradlblReportPwvDistanceMethodType.Text = crxMgrObject.PwvSettings.PWVDistanceMethod.Equals((int)CrxGenPwvValue.CrxPwvDistMethodDirect) ? oMsgMgr.GetMessage(CrxStructCommonResourceMsg.ReportLblDirect) : oMsgMgr.GetMessage(CrxStructCommonResourceMsg.ReportLblSubtracting); 
                    }
                }

                guipnlPatientDetails.Refresh();
                CheckForSimualtionMode();
            }
            catch (Exception ex)
            {
                GUIExceptionHandler.HandleException(ex, this);
            }
        }

        /** This method gets comma separated dates for the selected assessments
         * */
        private string GetCommaSeparatedDates()
        {
             dateWithComma = string.Empty;

            // count number of records to delete & format comma separated date string
            recordsToDelete = guiradgridReportAssessment.Rows.Count;
            for (int iRow = 0; iRow < recordsToDelete; iRow++)
            {
                // preparing comma separated string of dates                        
                dateWithComma += DateTime.Parse(guiradgridReportAssessment.Rows[iRow].Cells[1].Value.ToString()).ToString(CulturalNeutralDateFormat) + oMsgMgr.GetMessage(CrxStructCommonResourceMsg.GuiDisplayComma);               
            }

            GuiConstants.DateWithComma = dateWithComma;
            return dateWithComma;
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
            guiradlblReportPwvDistanceMethodType.Text = crxMgrObject.PwvSettings.PWVDistanceMethod.Equals((int)CrxGenPwvValue.CrxPwvDistMethodDirect) ? oMsgMgr.GetMessage(CrxStructCommonResourceMsg.ReportLblDirect) : oMsgMgr.GetMessage(CrxStructCommonResourceMsg.ReportLblSubtracting); 
            guiradtxtReportCuff.Text = string.Empty;
            guiradtxtCarotid.Text = string.Empty;

            guiradtxtReportHeight.Text = string.Empty;
            guiradlblReportHeightDisplay.Text = string.Empty;
            guiradtxtReportHeightInches.Text = string.Empty;
            guiradlblReportHeightInches.Text = string.Empty;

            // guiradtxtReportWeight.Text = string.Empty;
            // guiradlblReportWeightdisplay.Text = string.Empty;
            guiradtxtReportOperator.Text = string.Empty;
            guiradlblReportOperatordisplay.Text = string.Empty;
            guiradtxtReportNotes.Text = string.Empty;
            guiradlblReportNotesDisplay.Text = string.Empty;

            guiradtxtReportBloodPressure1.Text = string.Empty;
            guiradtxtReportBloodPressure2.Text = string.Empty;

            guiradlblreportSPdisplay.Text = string.Empty;
            guiradlblReportBloodPressure2.Text = string.Empty;

           // guiradlblReportBmiValue.Text = string.Empty;
            guiradlblreportpwvdistancedisplay1.Text = string.Empty;

            // reset pwv statistics
            guiradlblReportHeartRateValue.Text = string.Empty;
            guiradlblReportPWVValue.Text = string.Empty;
            guiradlblStdDeviationImage.ImageIndex = 0;
            guiradlblReportFemoralImage.ImageIndex = 0;
            guiradlblReportCarotidImage.ImageIndex = 0;
        }
       
        /** This method shows analysis trend graph
                 * */
        private void PlotAnalysisTrendCharts(string dateSelected)
        {
            try
            {              
                guiradlblReportDateTime.Visible = true;
                guiradlblReportDateTimeDisplay.Visible = true;
                guiradlblReportDateTime.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.GuiDatetimeTxt);
                
                // set report screen to display mode if & disable edit button
                guireportradlblReferenceMsg.Visible = false;
                guiradlblReportNormalMsg.Visible = false;
                guiradbtnreportedit.Enabled = false;

                // add chart titles & clear chart series
                guiradchartPulseWaveVelocity.Titles.Clear();
                guiradchartHeartRate.Titles.Clear();
                Font font = new Font(GuiConstants.FontName, 11);
                Title itemPwv = new Title
                                    {
                                        Font = font,
                                        Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.LblReportPwv),
                                        ForeColor = Color.WhiteSmoke
                                    };

                // guiradchartPulseWaveVelocity.Titles.Add(oMsgMgr.GetMessage(CrxStructCommonResourceMsg.LblReportPwv));
                guiradchartPulseWaveVelocity.Titles.Add(itemPwv);
                Title itemHeartRate = new Title
                                          {
                                              Font = font,
                                              Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.LblReportHeartRate),
                                              ForeColor = Color.WhiteSmoke
                                          };

                // guiradchartHeartRate.Titles.Add(oMsgMgr.GetMessage(CrxStructCommonResourceMsg.LblReportHeartRate));
                guiradchartHeartRate.Titles.Add(itemHeartRate); 
                guiradchartPulseWaveVelocity.Series.Clear();
                guiradchartHeartRate.Series.Clear();
               
                // if date ends with comma, truncate it as it creates empty value in array for dates
                if (dateSelected.EndsWith(oMsgMgr.GetMessage(CrxStructCommonResourceMsg.GuiDisplayComma)))
                {
                    dateSelected = dateSelected.Remove(dateSelected.Length - 1);
                }

                date = dateSelected.Split(GuiConstants.Separator);

                guiradlblReportDateTimeDisplay.Text = string.Format("{0:g}", Convert.ToDateTime(date[date.Length - 1]));

                // check for connection
                if (dbMagr.CheckConnection(serverNameString, crxMgrObject.GeneralSettings.SourceData) == 0)
                {
                    CrxStructPWVTrendData trendData = new CrxStructPWVTrendData();

                    // fetch records for selected assessments
                    dbMagr.GetPWVTrendData(GuiCommon.PatientInternalNumber, GuiCommon.GroupId, GuiCommon.SystemIdentifier, dateSelected + oMsgMgr.GetMessage(CrxStructCommonResourceMsg.GuiDisplayComma), trendData);
                    if (!string.IsNullOrEmpty(trendData.HeartRateArrStr) && !string.IsNullOrEmpty(trendData.PulseWaveVelocityArrStr))
                    {
                        PlotHeartRateTrend(trendData);
                        PlotPWVelocityTrend(trendData);

                        // subscribing to gettooltiptext event of chart control, 
                        // this event will fetch datapoint values when mouse is hovered over the chart area
                        guiradchartPulseWaveVelocity.GetToolTipText += Chart_GetToolTipText;
                        
                        guiradchartHeartRate.GetToolTipText += Chart_GetToolTipText;
                    }
                }
                else
                {
                    DialogResult result = RadMessageBox.Show(this, GuiCommon.ConnectionErrorString(), oMsgMgr.GetMessage(CrxStructCommonResourceMsg.SystemError), MessageBoxButtons.RetryCancel, RadMessageIcon.Error);
                    if (result == DialogResult.Retry)
                    {
                        PlotAnalysisTrendCharts(dateSelected);
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
            // define strings arrays for plotting heart rate & PWV
            heartRate = trendData.HeartRateArrStr.Split(GuiConstants.Separator);
            pWv = trendData.PulseWaveVelocityArrStr.Split(GuiConstants.Separator);

           // pwvTime = crxPWV.MeanCorrectedTime ;
            isStdDeviationValid = trendData.IsStdDevValidArrStr.Split(GuiConstants.Separator);

            string[] heartPwv = trendData.HeartRateArrStr.Split(GuiConstants.Separator);

            double[] heartPwvSort = CommonStringArrToDoubleArr(heartPwv);
            Array.Sort(heartPwvSort);
            heartPwv = CommonDoubleArrToStringArr(heartPwvSort);

            // plot heart rate series
            if (heartRate.Length > 0)
            {
                // assign latest record valus to bottom labels
                guiradlblReportHeartRateValue.Text = heartRate[heartRate.Length - 1] + " "  + oMsgMgr.GetMessage(CrxStructCommonResourceMsg.HeartrateUnit);
               
                double value = Math.Round(double.Parse(heartPwv[0]) * GuiConstants.ChartAreaMinimumY, MidpointRounding.ToEven);
                
                value = ((int)Math.Round(value / 10.0)) * 10;
                
                guiradchartHeartRate.ChartAreas[0].AxisY.Minimum = value;
                guiradchartHeartRate.ChartAreas[0].AxisY.Title = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.HeartrateLblAnalysis);
                guiradchartHeartRate.ChartAreas[0].AxisY.TitleFont = new Font(GuiConstants.FontName, guiradchartHeartRate.ChartAreas[0].AxisY.TitleFont.Size, FontStyle.Bold);
                value = Math.Round(double.Parse(heartPwv[heartPwv.Length - 1]) * GuiConstants.ChartAreaMaximumY, MidpointRounding.ToEven);
                guiradchartHeartRate.ChartAreas[0].AxisY.Maximum = value;
                guiradchartHeartRate.ChartAreas[0].AxisY.IntervalOffset = 0;
                guiradchartHeartRate.ChartAreas[0].AxisY.Interval = 5;

                guiradchartHeartRate.ChartAreas[0].AxisX.IntervalOffset = 1;
                CalculateLabelIntervalX();

                BindCustomLabelForTrendCharts(guiradchartHeartRate, heartRate.Length);

                PlotTrendChartSeries(guiradchartHeartRate, heartRate, null, ChartName.HeartRate);                
            }
        }

        /** This method plots PWV velocity trend graph 
         * */
        private void PlotPWVelocityTrend(CrxStructPWVTrendData trendData)
        {            
            // plot pwv trend series
            string[] stdDeviation = trendData.StandardDeviationArrStr.Split(GuiConstants.Separator);
            string[] heartPwv = trendData.PulseWaveVelocityArrStr.Split(GuiConstants.Separator);

            double[] stdDeviationSort = CommonStringArrToDoubleArr(stdDeviation);
            double[] heartPwvSort = CommonStringArrToDoubleArr(heartPwv);

            // sort array to get minimum & maximum value to set y axis range
            Array.Sort(heartPwvSort);
            Array.Sort(stdDeviationSort);
            stdDeviation = CommonDoubleArrToStringArr(stdDeviationSort);
            heartPwv = CommonDoubleArrToStringArr(heartPwvSort);    
              if (pWv.Length > 0)
            {
                // assign latest record valus to bottom labels
                guiradlblReportPWVValue.Text = pWv[pWv.Length - 1] + " " + oMsgMgr.GetMessage(CrxStructCommonResourceMsg.PwvUnit);
                guiradlblStdDeviationImage.ImageIndex = int.Parse(isStdDeviationValid[isStdDeviationValid.Length - 1]);
            
                // set max value as largest pwv + largest std deviation
                // set min value as lowest pwv + largest std deviation
                double maxValue = double.Parse(heartPwv[heartPwv.Length - 1], CrxCommon.nCI) + double.Parse(stdDeviation[stdDeviation.Length - 1], CrxCommon.nCI) + 1;
                double minValue = double.Parse(heartPwv[0], CrxCommon.nCI) - double.Parse(stdDeviation[stdDeviation.Length - 1], CrxCommon.nCI) - 1;

                maxValue = Math.Round(maxValue, 0, MidpointRounding.ToEven);
                minValue = Math.Round(minValue);
                CalculateLabelIntervalYForPwvTrend(int.Parse(minValue.ToString()), int.Parse(maxValue.ToString()));

                double value = Math.Round(minValue * GuiConstants.ChartAreaMinimumY); 
                guiradchartPulseWaveVelocity.ChartAreas[0].AxisY.Minimum = value;
                guiradchartPulseWaveVelocity.ChartAreas[0].AxisY.Title = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.PwvLblAnalysis);
                guiradchartPulseWaveVelocity.ChartAreas[0].AxisY.TitleFont = new Font(GuiConstants.FontName, guiradchartPulseWaveVelocity.ChartAreas[0].AxisY.TitleFont.Size, FontStyle.Bold);

                value = Math.Round(maxValue * GuiConstants.ChartAreaMaximumY, 0, MidpointRounding.AwayFromZero);
                guiradchartPulseWaveVelocity.ChartAreas[0].AxisY.Maximum = value;
                guiradchartPulseWaveVelocity.ChartAreas[0].AxisY.IntervalOffset = 0;
                guiradchartPulseWaveVelocity.ChartAreas[0].AxisY.Interval = 1;                
                
                guiradchartPulseWaveVelocity.ChartAreas[0].AxisX.IntervalOffset = 1;

                BindCustomLabelForTrendCharts(guiradchartPulseWaveVelocity, pWv.Length);
                PlotTrendChartSeries(guiradchartPulseWaveVelocity, pWv, stdDeviation, ChartName.Pwv);               
            }
        }

        /** This method is used to bind custom labels for X-Axis for both Heart rate & Pwv Velocity trend chart
         * */
        private void BindCustomLabelForTrendCharts(Chart trendChart, int seriesLength)
        {
            Font labelFontMax = new Font(ConfigurationManager.AppSettings[GuiConstants.AppConfigParams.AnalysisFontName.ToString()].ToString(), float.Parse(ConfigurationManager.AppSettings[GuiConstants.AppConfigParams.AnalysisFontMax.ToString()].ToString()));  // sets font max size for analysis chart x axis labels
            Font labelFontMin = new Font(ConfigurationManager.AppSettings[GuiConstants.AppConfigParams.AnalysisFontName.ToString()].ToString(), float.Parse(ConfigurationManager.AppSettings[GuiConstants.AppConfigParams.AnalysisFontMin.ToString()].ToString())); // sets font min size for analysis chart x axis labels

            trendChart.ChartAreas[0].AxisX.CustomLabels.Clear();

            for (int hrseries1 = 0; hrseries1 < seriesLength; hrseries1 = hrseries1 + labelInterval)
            {
                if (hrseries1 > (5 * labelInterval))
                {
                    trendChart.ChartAreas[0].AxisX.LabelStyle.Angle = LblVerticalAngle;
                    trendChart.ChartAreas[0].AxisX.LabelStyle.Font = labelFontMin;
                }
                else
                {
                    trendChart.ChartAreas[0].AxisX.LabelStyle.Font = labelFontMax;
                    trendChart.ChartAreas[0].AxisX.LabelStyle.Angle = LblHorizontalAngle;
                }

                // trendChart.ChartAreas[0].AxisX.CustomLabels.Add(hrseries1 - 1, hrseries1 + 1, date[hrseries1].ToString());
                trendChart.ChartAreas[0].AxisX.CustomLabels.Add(hrseries1 - 1, hrseries1 + 1, string.Format("{0:g}", Convert.ToDateTime(date[hrseries1].ToString())));
            }
        }

        /** This method is used to plot chart series for PWV velocity & Heart rate.
         * It displays error bar for PWV velocity chart
         * */
        private void PlotTrendChartSeries(Chart trendChart, IList<string> trendSeries, IList<string> stdDeviationSeries, ChartName trendType)
        {
            // to plot line for PWV graph  
            Series trendLine = new Series(stdDeviationSeries == null ? ((int)SeriesType.HeartLine).ToString() : ((int)SeriesType.PwvLine).ToString())
            {
                Color = Color.FromArgb(121, 171, 231),
                ChartType = SeriesChartType.FastLine,
                XValueType = ChartValueType.Int32
            };

            // to plot points for PWV graph
            Series trendPoint = new Series(stdDeviationSeries == null ? ((int)SeriesType.HeartPoint).ToString() : ((int)SeriesType.PwvPoint).ToString())
            {
                Color = Color.FromArgb(121, 171, 231),
                ChartType = SeriesChartType.Bubble,
                XValueType = ChartValueType.Int32,
                CustomProperties = "BubbleMaxSize=" + (20 - (labelInterval * 2) + 1),
                MarkerStyle = MarkerStyle.Circle,
                ShadowOffset = 2
            };

            trendLine.Points.Clear();
            trendPoint.Points.Clear();

            for (int hrseries1 = 0; hrseries1 < trendSeries.Count; hrseries1++)
            {
                // heartline.Points.AddXY(double.Parse(DateTime.Parse(date[hrseries1].ToString()).ToOADate().ToString()), double.Parse(heartRate[hrseries1].ToString()));
                trendLine.Points.AddXY(hrseries1, double.Parse(trendSeries[hrseries1], CrxCommon.nCI));
                trendPoint.Points.AddXY(hrseries1, double.Parse(trendSeries[hrseries1], CrxCommon.nCI));

                if (trendType == ChartName.Pwv)
                {
                    // add series dynamically for showing error bar on PWV chart
                    Series correctionLine = new Series(((int)SeriesType.ErrorBar) + hrseries1.ToString())
                    {
                        ChartType = SeriesChartType.ErrorBar,
                        XValueType = ChartValueType.Int32,
                        YValuesPerPoint = 3,
                        MarkerSize = 3,
                        MarkerStyle = MarkerStyle.None,
                        Color = Color.FromArgb(121, 171, 231)
                    };

                    correctionLine["PointWidth"] = "0.1";

                    double centerY = double.Parse(pWv[hrseries1]);
                    if (stdDeviationSeries != null)
                    {
                        double lowerErrorY = centerY - double.Parse(stdDeviationSeries[hrseries1], CrxCommon.nCI);
                        double upperErrorY = centerY + double.Parse(stdDeviationSeries[hrseries1], CrxCommon.nCI);
                        correctionLine.Points.AddXY(hrseries1, centerY, lowerErrorY, upperErrorY);
                    }

                    trendChart.Series.Add(correctionLine);
                }
            }

            // following line shows y axis data for the last data point
            trendChart.Series.Add(trendLine);
            trendChart.Series.Add(trendPoint);
            trendChart.Invalidate();
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
                guiradchartPulseWaveVelocity.ChartAreas[0].AxisY.LabelStyle.Interval = yInterval.Equals(1) ? 2 : yInterval;
            }
        }

        /** This method calculates label interval for x axis label for PWV trend & Heart rate charts
        * Since the interval is 1 there is overlapping for label display when more labels are there
        * */
        private void CalculateLabelIntervalX()
        {
            const int XInterval = 10; // this variable denotes the number by which x label interval would be calculated
        
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
                ChangeDataPointColor();

                // Check selected chart element and set tooltip text   
                switch (e.HitTestResult.ChartElementType)
                {
                    case ChartElementType.DataPoint:
                        if (e.HitTestResult.Series.ChartType != SeriesChartType.ErrorBar)
                        {
                            // This method fetches int array of x coordinates for x axis data points
                            GetXCoordinatesForChart(e.HitTestResult.Series);

                            // get the point index to fetch data values from series   
                            // this point index always return higher point index if mouse cursor is hover between two data points
                            // so even if mouse cursor is nearer to point index 0 it will return point index 1 which is higher & next most point index
                            int i = e.HitTestResult.PointIndex;
                            int pointSelected = i;

                            if (i > 0)
                            {
                                // calculate midpoint between two x coordinates taking i as greater point index
                                int midPoint = int.Parse(xCoordinate[i].ToString()) -
                                               int.Parse(xCoordinate[i - 1].ToString());
                                midPoint = midPoint / 2;
                                midPoint = midPoint + int.Parse(xCoordinate[i - 1].ToString());

                                // if current x co-ordinates are greater than midpoint, display data for point index i else display for for i - 1
                                if (e.X > midPoint)
                                {
                                    // display data closest to datapoint at index i
                                    // bind the hear rate, pwv, datetime & standard deviation values from arrays as per point index
                                    guiradlblReportHeartRateValue.Text = heartRate[i] + " " +
                                                                         oMsgMgr.GetMessage(CrxStructCommonResourceMsg.HeartrateUnit);
                                    guiradlblReportPWVValue.Text = pWv[i] + " " + oMsgMgr.GetMessage(CrxStructCommonResourceMsg.PwvUnit);
                                    guiradlblStdDeviationImage.ImageIndex = int.Parse(isStdDeviationValid[i]);
                                    guiradlblReportDateTimeDisplay.Text = string.Format("{0:g}", Convert.ToDateTime(date[i]));
                                }
                                else
                                {
                                    // display data closest to datapoint at index i - 1
                                    // bind the hear rate, pwv, datetime & standard deviation values from arrays as per point index
                                    guiradlblReportHeartRateValue.Text = heartRate[i - 1] + " " +
                                                                         oMsgMgr.GetMessage(CrxStructCommonResourceMsg.HeartrateUnit);
                                    guiradlblReportPWVValue.Text = pWv[i - 1] + " " +
                                                                   oMsgMgr.GetMessage(CrxStructCommonResourceMsg.PwvUnit);
                                    guiradlblStdDeviationImage.ImageIndex =
                                        int.Parse(isStdDeviationValid[i - 1]);
                                    guiradlblReportDateTimeDisplay.Text = string.Format("{0:g}", Convert.ToDateTime(date[i - 1]));
                                    pointSelected = i - 1;
                                }
                            }
                            else
                            {
                                // bind the hear rate, pwv & standar deviation values from arrays as per point index
                                guiradlblReportHeartRateValue.Text = heartRate[i] + " " +
                                                                     oMsgMgr.GetMessage(CrxStructCommonResourceMsg.HeartrateUnit);
                                guiradlblReportPWVValue.Text = pWv[i] + " " + oMsgMgr.GetMessage(CrxStructCommonResourceMsg.PwvUnit);
                                
                                guiradlblStdDeviationImage.ImageIndex = int.Parse(isStdDeviationValid[i]);
                                guiradlblReportDateTimeDisplay.Text = string.Format("{0:g}", Convert.ToDateTime(date[i]));
                            }

                            if (chartSelected == ChartName.Pwv)
                            {
                                guiradchartPulseWaveVelocity.Series[((int)SeriesType.PwvPoint).ToString()].Points[pointSelected].Color =
                                    Color.FromArgb(180, 207, 241); 
                            }
                            else
                            {
                                guiradchartHeartRate.Series[((int)SeriesType.HeartPoint).ToString()].Points[pointSelected].Color = Color.FromArgb(180, 207, 241);                               
                            }
                        }

                        break;
                    case ChartElementType.AxisLabels:
                        // if it is axislabel get the text of it to show as tool tip
                        CustomLabel s = (CustomLabel)e.HitTestResult.Object;
                        e.Text = s.Text;                       
                        break;
                    default:                       
                        break;
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
                    // on the click of this button navigate the user to the capture screen whenre he can recapture the waveforms.                
                    if (GuiCommon.CaptureChildForm != null)
                    {
                        GuiCommon.CaptureChildForm.Close();
                    }

                    GuiCommon.CaptureTabClick = false;

                    // GuiCommon.captureChildForm = new Capture(this);
                    GuiCommon.CaptureChildForm = new Capture(objDefaultWindow)
                                                              {
                                                                  TopLevel = false,
                                                                  Dock = DockStyle.Fill,
                                                                  FormBorderStyle = FormBorderStyle.None
                                                              };

                    // GuiCommon.captureChildForm = new Capture();
                    var page = objDefaultWindow.radtabCapture;
                    GuiCommon.CaptureChildForm.Parent = page;
                    page.Controls.Clear();

                    page.Controls.Add(GuiCommon.CaptureChildForm);
                    GuiCommon.CaptureChildForm.Show();

                    objDefaultWindow.radpgTabCollection.SelectedPage = objDefaultWindow.radtabCapture;
                    objDefaultWindow.radtabCapture.Enabled = true;
                }
                else
                {
                    // device not connected show error message
                    RadMessageBox.Show(this, oMsgMgr.GetMessage(CrxStructCommonResourceMsg.CaptureDeviceErrMsg), oMsgMgr.GetMessage(CrxStructCommonResourceMsg.SystemError), MessageBoxButtons.OK, RadMessageIcon.Error);
                    if (GuiCommon.CaptureTabClick)
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
        void GetXCoordinatesForChart(Series chartSeries)
        {
            xCoordinate = new int[chartSeries.Points.Count];
            double xValue = 0.0;
            int iCount = 0;
            foreach (DataPoint dp in chartSeries.Points)
            {
                // get the pixel values corresponding to datapoint value for X
                xValue = chartSelected == ChartName.Pwv ? guiradchartPulseWaveVelocity.ChartAreas[0].AxisX.ValueToPixelPosition(double.Parse(dp.XValue.ToString())) : guiradchartHeartRate.ChartAreas[0].AxisX.ValueToPixelPosition(double.Parse(dp.XValue.ToString())); 
               
                // add to array of x co-ordinates
                xCoordinate[iCount] = int.Parse(Math.Round(xValue, MidpointRounding.ToEven).ToString());
                iCount++;
            }
        }

        /** This event customizes label display on PWV trend analysis chart
         * */
        private void guiradchart_Customize(object sender, EventArgs e)
        {
            try
            {
                const int SeriesPoints = 3;
                if (pWv != null)
                {
                    if (pWv.Length > SeriesPoints)
                    {
                        foreach (CustomLabel cl in guiradchartPulseWaveVelocity.ChartAreas[0].AxisX.CustomLabels)
                        {
                            // cl.Text = DateTime.Parse(cl.Text).ToShortDateString() + Environment.NewLine + DateTime.Parse(cl.Text).ToLongTimeString();
                            cl.Text = DateTime.Parse(cl.Text).ToShortDateString() + Environment.NewLine + DateTime.Parse(cl.Text).ToShortTimeString();
                        }

                        foreach (CustomLabel cl in guiradchartHeartRate.ChartAreas[0].AxisX.CustomLabels)
                        {
                            // cl.Text = DateTime.Parse(cl.Text).ToShortDateString() + Environment.NewLine + DateTime.Parse(cl.Text).ToLongTimeString();
                            cl.Text = DateTime.Parse(cl.Text).ToShortDateString() + Environment.NewLine + DateTime.Parse(cl.Text).ToShortTimeString();
                        }
                    }
                }
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
            numeberOfRecordsSelected = recordsToDelete = recordSelected;
            CheckForSimualtionMode();

            // below line of code will keep focus on current record selection in assessment grid
            guiradgridReportAssessment.MasterTemplate.EndUpdate(new DataViewChangedEventArgs(ViewChangedAction.DataChanged));
            guiradgridReportAssessment.MasterTemplate.SynchronizationService.AddListener(navigatorListener);

           // guiradchkAssesments.Enabled = guiradgridReportAssessment.Rows.Count == 1 ? false : true;

            // display analysis / report screen based on records selected
            DisplayReportOnSelection(recordSelected, dateWithComma);            
        }

        /** This method binds data to report screen as per the selected assesment
         * */
        private void DisplayReportForSelectedAssesment(string dateTime)
        {
           // if (!GuiCommon.SetupToReport)
            {
                InitializeCrxOnLoad(dateTime);
                FillPWVMeasurementDetailsReport();

                SuperImposedWaveForm();
                CheckAgeLimit(obj.patientAge);               
                PlotNormalRangeGraph();
                PlotReferenceRangeGraph();                
            }
        }

        /** This method subscribes all the text boxes & drop down for changes made to it.
        * To the form changed event which will determine for any changes made before application is closed
        * */
        private void SubscribeReportFormChanges()
        {
            // subscribe text change events to determine any form changes
            /**
            guiradtxtReportCuff.TextChanged += GuiCommon.FormChanged;
            guiradtxtCarotid.TextChanged += GuiCommon.FormChanged;
            guiradtxtReportFemoToCuff.TextChanged += GuiCommon.FormChanged;
            guiradtxtReportHeight.TextChanged += GuiCommon.FormChanged;
            guiradtxtReportHeightInches.TextChanged += GuiCommon.FormChanged;
            guiradtxtReportOperator.TextChanged += GuiCommon.FormChanged;
            guiradtxtReportBloodPressure1.TextChanged += GuiCommon.FormChanged;
           

            // Commenting the below code as group name is not included in Clinical mode.
            // guiradtxtReportWeight.TextChanged += GuiCommon.FormChanged;
            guiradtxtReportBloodPressure2.TextChanged += GuiCommon.FormChanged;
            guiradtxtReportNotes.TextChanged += GuiCommon.FormChanged;
             */

            // subscribe key press events for measurement fields to allow numeric values
            guiradtxtCarotid.KeyPress += GuiCommon.CheckForNumericValues;
            guiradtxtReportCuff.KeyPress += GuiCommon.CheckForNumericValues;
            guiradtxtReportFemoToCuff.KeyPress += GuiCommon.CheckForNumericValues;
            guiradtxtReportHeight.KeyPress += GuiCommon.CheckForNumericValues;
            guiradtxtReportHeightInches.KeyPress += GuiCommon.CheckForNumericValues;
            guiradtxtReportBloodPressure1.KeyPress += GuiCommon.CheckForNumericValues;
            guiradtxtReportBloodPressure2.KeyPress += GuiCommon.CheckForNumericValues;

            // Commenting the below code as group name is not included in Clinical mode.
            // guiradtxtReportWeight.KeyPress += GuiCommon.CheckForNumericValues;
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
            if (GuiCommon.IsWaitIntervalImposed)
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
        private void guiradchartHeartRate_MouseMove(object sender, MouseEventArgs e)
        {
            chartSelected = ChartName.HeartRate;
        }       

        /** This event fires when mouse is hovered over PWV chart
         * It sets the chart type which helps in determining which chart datapoints are hovered over
         * */
        private void guiradchartPulseWaveVelocity_MouseMove(object sender, MouseEventArgs e)
        {
            chartSelected = ChartName.Pwv;
        }

        /** This method is used to set the default color of all data points once the mouse cursor is moved away fromt he points.
         * It resets the color for both heart rate & pulse wave velocity
         * */
        private void ChangeDataPointColor()
        {             
            switch (chartSelected)
            { 
                case ChartName.Pwv:
                    ChartDataPoints(guiradchartPulseWaveVelocity, ((int)SeriesType.PwvPoint).ToString());
                    break;
                case ChartName.HeartRate:
                    ChartDataPoints(guiradchartHeartRate, ((int)SeriesType.HeartPoint).ToString());
                    break;
                default:
                    break;
            }                       
        }

        /** This method sets default data point color for both heart rate & Pwv velocity charts
         * */
        private void ChartDataPoints(Chart trendChart, string seriesType)
        {
            foreach (DataPoint t in trendChart.Series[seriesType].Points)
            {
                t.Color = Color.FromArgb(121, 171, 231); // "point" for internal use only                
            }
        }
        
        /** This method checks whether last assessment is selected, if selected repeat & capture tabs are enabled & vice versa
         * */
        private void CheckLastAssessmentSelected(string dateTime)
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
                lastAssessmentDate = string.IsNullOrEmpty(lastAssessmentDate) ? string.Empty : DateTime.Parse(lastAssessmentDate).ToString(CulturalNeutralDateFormat);
                dateTime = string.IsNullOrEmpty(dateTime) ? string.Empty : DateTime.Parse(dateTime).ToString(CulturalNeutralDateFormat);
                setValue = lastAssessmentDate.Equals(dateTime) && !GuiCommon.IsWaitIntervalImposed && guiradbtnreportedit.Visible && objDefaultWindow.radtabReport.Text != oMsgMgr.GetMessage(CrxStructCommonResourceMsg.TabAnalysis) && guiradgridReportAssessment.Rows.Count > 0;
            }

            objDefaultWindow.radtabCapture.Enabled = setValue;
            guiradbtnRepeat.Enabled = setValue;            
        }       
        
        /** This event gets fired when focus is moved from text box which takes SP/Dp/Mp value.
        * It checks if the value entered in textbox is within valid range and shows error accordingly
        * */
        private void guiradtxtReportBloodPressure1_Leave(object sender, EventArgs e)
        {
            objValidateReport.CheckFieldLimits(guiradtxtReportBloodPressure1);
            guipnlPatientDetails.Refresh();
        }

        /** This event gets fired when focus is moved from text box which takes SP/Dp/Mp value.
           * It checks if the value entered in textbox is within valid range and shows error accordingly
           * */
        private void guiradtxtReportBloodPressure2_Leave(object sender, EventArgs e)
        {
            objValidateReport.CheckFieldLimits(guiradtxtReportBloodPressure2);
            guipnlPatientDetails.Refresh();
        }

        /** This event gets fired when focus is moved from text box which takes cuff / direct values.
          * It checks if the value entered in textbox is within valid range and shows error accordingly
          * */
        private void guiradtxtReportCuff_Leave(object sender, EventArgs e)
        {
            objValidateReport.CheckFieldLimits(guiradtxtReportCuff);
            guipnlPatientDetails.Refresh();
        }

        /** This event gets fired when focus is moved from text box which takes femoral to cuff values.
          * It checks if the value entered in textbox is within valid range and shows error accordingly
          * */
        private void guiradtxtReportFemoToCuff_Leave(object sender, EventArgs e)
        {
           objValidateReport.CheckFieldLimits(guiradtxtReportFemoToCuff);
           guipnlPatientDetails.Refresh();
        }

        /** This event gets fired when focus is moved from text box which takes height in cm || height in feet values.
          * It checks if the value entered in textbox is within valid range and shows error accordingly
          * */
        private void guiradtxtReportHeight_Leave(object sender, EventArgs e)
        {
            objValidateReport.CheckIntegerFieldLimitsRemoveInvalidValue(guiradtxtReportHeight);
            guipnlPatientDetails.Refresh();
        }

        /** This event gets fired when focus is moved from text box which takes height in inches values.
          * It checks if the value entered in textbox is within valid range and shows error accordingly
          * */
        private void guiradtxtReportHeightInches_Leave(object sender, EventArgs e)
        {
            objValidateReport.CheckIntegerFieldLimitsRemoveInvalidValue(guiradtxtReportHeightInches);
            guipnlPatientDetails.Refresh();
        }

        /** This event gets fired when focus is moved from text box which takes weight in lbs || kgs values.
          * It checks if the value entered in textbox is within valid range and shows error accordingly
          * */
        private void guiradtxtReportWeight_Leave(object sender, EventArgs e)
        {
           // objValidateReport.CheckFieldLimits(guiradtxtReportWeight);
        }

        /** This event gets fired when focus is moved from text box which takes carotid values.
         * It checks if the value entered in textbox is within valid range and shows error accordingly
         * */
        private void guiradtxtCarotid_Leave(object sender, EventArgs e)
        {
            objValidateReport.CheckFieldLimits(guiradtxtCarotid);
            guipnlPatientDetails.Refresh();
        }

        /**This method is called to check if the specified patient's date in within the specified range or not.
         */
        private void CheckAgeLimit(int age)
        {
            if (age > BizConstants.MAXIMUM_REFERENCE_RANGE_AGE || age < BizConstants.MINIMUM_REFERENCE_RANGE_AGE)
            {                
                // Make the labels visible true,bring it to front and hide the Graph.
                guireportradlblReferenceMsg.Visible = true;
                guireportradlblReferenceMsg.BringToFront();
                guichartReferenceRange.Visible = false;
                guiradlblReportReferenceRange.Visible = true;
                guiradlblReportBpRange.Visible = false;
                guiradlblRefRangeDescription.Visible = false;

                // Similarly for Normal range.
                guiradlblReportNormalMsg.Visible = true;
                guiradlblReportNormalMsg.BringToFront();
                guichartNormalRange.Visible = false;
                guiradlbReportNormalRange.Visible = true;

                // Display message saying Age is outside the range.
                guireportradlblReferenceMsg.Text = guiradlblReportNormalMsg.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.GuiReportAgeOutsideRange);
            }
            else
            {
                if (CrxConfigManager.Instance.PwvSettings.NormalRange)
                {
                    // Hide the label and show the chart for Normal range garph.
                    guiradlblReportNormalMsg.Visible = false;
                    guiradlblReportNormalMsg.SendToBack();
                    guichartNormalRange.Visible = true;
                    guiradlbReportNormalRange.Visible = true;
                }

                CheckBloodPressure();
            }          
        }

        /** This method fille structure "PWVReportData" with the values to be printed on PWV report.
         * This values will be used in Crystal Reports.
         * */
        private void FillStructForPWVReport()
        {
           // PWVReportData pwvRpt;
            PWVReportData.RptHeader = string.IsNullOrEmpty(crxMgrObject.GeneralSettings.ReportTitle) ? BizInfo.Instance().GetCompanyName().Replace("(R)", "\u00AE") : crxMgrObject.GeneralSettings.ReportTitle.Replace("(R)", "\u00AE");

            // PWVReportData.RptHeader = BizInfo.Instance().GetCompanyName().Replace("(R)", "\u00AE");
            PWVReportData.RptPatientAge = guiradlblReportAge.Text;
            PWVReportData.RptPatientAgeValue = obj.patientAge.ToString();
            PWVReportData.RptPatientAssessment = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.LblReportAssessment);
            PWVReportData.RptPatientAssessmentValue = string.Format("{0:g}", Convert.ToDateTime(GuiCommon.PwvCurrentStudyDatetime)); // GuiCommon.PwvCurrentStudyDatetime;
            PWVReportData.RptPatientBP = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.LblReportBp);
            PWVReportData.RptPatientBPValue = SetBPForPWVReport();
            
           // PWVReportData.RptTitle = string.IsNullOrEmpty(crxMgrObject.GeneralSettings.ReportTitle) ? string.Empty : crxMgrObject.GeneralSettings.ReportTitle;
            PWVReportData.RptPatientCarotid = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.LblReportRecordedCarotid);
            PWVReportData.RptPatientData = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.LblReportPatientData);
            PWVReportData.RptPatientDistance = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.LblReportDiatance);
            PWVReportData.RptPatientDistanceValue = string.Format("{0} {1}", obj.calculatedDistance.ToString(), (CrxConfigManager.Instance.PwvSettings.PWVDistanceUnits.Equals(0) ? oMsgMgr.GetMessage(CrxStructCommonResourceMsg.Mm) : oMsgMgr.GetMessage(CrxStructCommonResourceMsg.Cm)));
            PWVReportData.RptPatientDob = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.LblReportDob);
            PWVReportData.RptPatientDobValue = patientObj.dateOfBirth.ToString(oMsgMgr.GetMessage(CrxStructCommonResourceMsg.ReportDateTimeFormat));
            PWVReportData.RptPatientFemoral = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.LblReportRecordedFemoral);
            PWVReportData.RptPatientGender = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.LblReportGender);
            PWVReportData.RptPatientGenderValue = patientObj.gender.Equals(CrxStructCommonResourceMsg.MaleTxt) ? oMsgMgr.GetMessage(CrxStructCommonResourceMsg.MaleTxt) : oMsgMgr.GetMessage(CrxStructCommonResourceMsg.FemaleTxt); // patientObj.gender;
            PWVReportData.RptPatientGeneralPop = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.LblReportReferenceRange);
            PWVReportData.RptPatientHealthyPop = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.LblReportNormalRange);
            PWVReportData.RptPatientHeartRate = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.LblReportHR);
            PWVReportData.RptPatientHeartRateValue = string.Format("{0} {1}", obj.meanHeartRate.ToString("#0"), oMsgMgr.GetMessage(CrxStructCommonResourceMsg.HeartrateUnit));
            PWVReportData.RptPatientHeight = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.LblHeight);
            
            PWVReportData.RptPatientHeightValue = SetHeightForReportPrint();
            PWVReportData.RptPatientId = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.LblPatientId);
            PWVReportData.RptPatientIdValue = patientObj.patientId;
            PWVReportData.RptPatientName = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.LblPatientName);
            PWVReportData.RptPatientNameValue = string.IsNullOrEmpty(patientObj.firstName) ? patientObj.lastName : string.Format("{0} {1}", patientObj.firstName, patientObj.lastName);
            PWVReportData.RptPatientNotes = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.LblNotes);
            PWVReportData.RptPatientNotesValue = obj.notes;
            PWVReportData.RptPatientOperation = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.LblOperator);
            PWVReportData.RptPatientOperationValue = obj.operatorId;
            PWVReportData.RptPatientPwv = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.LblReportPwvLbl); 
            PWVReportData.RptPatientPwvValue = string.Format("{0} {1}", obj.meanPulseWaveVelocity.ToString("#0.0"), oMsgMgr.GetMessage(CrxStructCommonResourceMsg.PwvUnit));
            PWVReportData.RptPatientStdDev = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.LblReportStdLbl); 
            PWVReportData.RptStudyData = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.LblReportStudyData);
            PWVReportData.RptGeneralPopulation = crxMgrObject.PwvSettings.ReferenceRange;
            PWVReportData.RptHealthyPopulation = crxMgrObject.PwvSettings.NormalRange;            
        }

        /** This method fille structure "PWVPatientReportData" with the values to be printed on PWV Patient report.
        * This values will be used in Crystal Reports.
        * */
        private void FillStructForPWVPatientReport()
        {
            PWVPatientReportData.RptPatientAge = guiradlblReportAge.Text;
            PWVPatientReportData.RptPatientAgeValue = obj.patientAge.ToString();
            PWVPatientReportData.RptPatientBP = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.LblReportBp);
            PWVPatientReportData.RptPatientBPValue = SetBPForPWVReport();            

            PWVPatientReportData.RptPatientGender = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.LblReportGender);
            PWVPatientReportData.RptPatientGenderValue = patientObj.gender;
            PWVPatientReportData.RptPatientNameValue = string.IsNullOrEmpty(patientObj.firstName) ? patientObj.lastName : string.Format("{0} {1}", patientObj.firstName, patientObj.lastName);
            PWVPatientReportData.RptPatientId = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.LblPatientId);
            PWVPatientReportData.RptPatientIdValue = patientObj.patientId;
            PWVPatientReportData.RptPatientPwv = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.LblReportPwvLbl);
            PWVPatientReportData.RptPatientPwvValue = string.Format("{0} {1}", obj.meanPulseWaveVelocity.ToString("#0.0"), oMsgMgr.GetMessage(CrxStructCommonResourceMsg.PwvUnit));
            PWVPatientReportData.RptPatientHeight = SetHeightForReportPrint();

            PWVPatientReportData.RptGeneralPopulation = crxMgrObject.PwvSettings.ReferenceRange;
            PWVPatientReportData.RptHealthyPopulation = crxMgrObject.PwvSettings.NormalRange;
        }

        /** This method sets BP value for showing in PWV report when it is printed
         * */
        private string SetBPForPWVReport()
        {
            string blpValue = string.Empty;
            if (!((obj.bloodPressure.DP.Reading.Equals(GuiConstants.DefaultValue) && obj.bloodPressure.MP.Reading.Equals(GuiConstants.DefaultValue)) || (obj.bloodPressure.SP.Reading.Equals(GuiConstants.DefaultValue) && obj.bloodPressure.DP.Reading.Equals(GuiConstants.DefaultValue)) || (obj.bloodPressure.SP.Reading.Equals(GuiConstants.DefaultValue) && obj.bloodPressure.MP.Reading.Equals(GuiConstants.DefaultValue))))
            {
                blpValue = obj.bloodPressure.SP.Reading.ToString() + oMsgMgr.GetMessage(CrxStructCommonResourceMsg.GuiDisplaySlash) + obj.bloodPressure.DP.Reading.ToString() + " " + oMsgMgr.GetMessage(CrxStructCommonResourceMsg.UnitsPressureMmhg);

                // switch (obj.bloodPressureEntryOption)
                // {
                //    case (int)CrxGenPwvValue.CrxGenBPOptSPandDP:
                      
                // break;
                //    case (int)CrxGenPwvValue.CrxGenBPOptMPandDP:
                //        blpValue = obj.bloodPressure.MP.Reading.ToString() + oMsgMgr.GetMessage(CrxStructCommonResourceMsg.GuiDisplaySlash) + obj.bloodPressure.DP.Reading.ToString();
                //        break;
                //    case (int)CrxGenPwvValue.CrxGenBPOptSPandMP:
                //        blpValue = obj.bloodPressure.SP.Reading.ToString() + oMsgMgr.GetMessage(CrxStructCommonResourceMsg.GuiDisplaySlash) + obj.bloodPressure.MP.Reading.ToString();
                //        break;
                //    default:
                //        break;
                // }
            }

            return blpValue;
        }

        /** This event fires on any key down on report screen. It suppresses space bar on assessment gridview as pressing space bar when focus is on gridview
         * allows selecting / deselecting assessments
         */
        private void Report_KeyDown(object sender, KeyEventArgs e)
        {
            if (e.KeyCode == Keys.Space && guiradgridReportAssessment.Focus())
            {
                e.SuppressKeyPress = true;
            }

            if (e.KeyCode == Keys.Escape)
            {
                e.SuppressKeyPress = true;
            }

            if (e.KeyCode == Keys.Left || e.KeyCode == Keys.Right)
            {
                e.SuppressKeyPress = false;
            }
        }

        /** This method sets height for passing it to the crystal report for print reports
         */
        private string SetHeightForReportPrint()
        {
            string height = string.Empty;
            switch (CrxConfigManager.Instance.GeneralSettings.HeightandWeightUnit)
            {
                case (int)CrxGenPwvValue.CrxGenHeightWeightMetric:
                    height = obj.heightAndWeight.heightInCentimetres.Equals(GuiConstants.DefaultValue) ? string.Empty : (obj.heightAndWeight.heightInCentimetres.ToString() + " " + oMsgMgr.GetMessage(CrxStructCommonResourceMsg.Cm));
                    break;
                case (int)CrxGenPwvValue.CrxGenHeightWeightImperial:

                    if (obj.heightAndWeight.heightInInches != GuiConstants.DefaultValue)
                    {
                        // convert height in inches to feet & inches
                        int heightInInches = int.Parse(obj.heightAndWeight.heightInInches.ToString()) % 12;
                        int heigthInFeet = int.Parse(obj.heightAndWeight.heightInInches.ToString()) / 12;

                        height = string.Format("{0}{1}{2} {3}{4}", heigthInFeet.ToString(), oMsgMgr.GetMessage(CrxStructCommonResourceMsg.Feet), oMsgMgr.GetMessage(CrxStructCommonResourceMsg.GuiDisplayComma), heightInInches.ToString(), oMsgMgr.GetMessage(CrxStructCommonResourceMsg.UnitsDistanceInch));
                    }

                    break;
                default:
                    break;
            }

            return height;
        }

        /** This event fires when user tries to navigate to top menu tabs on report screen
         * It prompts user to save changes if user is in edit mode and accordingly navigates to top menu
         */
        private void SaveChangesOnMenuFocus(object sender, EventArgs e)
        {
            GuiCommon.IsMenuItemShown = true;
            if (!guiradbtnreportedit.Visible)
            {
                if (isValueChanged)
                {
                    DialogResult ds = RadMessageBox.Show(this, oMsgMgr.GetMessage(CrxStructCommonResourceMsg.MsgSaveChange), oMsgMgr.GetMessage(CrxStructCommonResourceMsg.SystemError), MessageBoxButtons.YesNoCancel, RadMessageIcon.Question);

                    // Keeping Yes and No separate for future use.                     
                    switch (ds)
                    {
                        case DialogResult.Yes:

                            // save changes before navigating to report screen
                            Invoke(new EventHandler(guiradbtnreportsave_Click));
                            
                            break;
                        case DialogResult.No:

                            // navigate to menu item without saving changes
                            SetPWVDsiplayMode();
                            isValueChanged = false;
                            break;
                        default:

                            // stay on report screen
                            GuiCommon.IsMenuItemShown = false;
                            break;
                    }                    
                }
            }
        }

        /** This method prints Patient PWV report
        */
        private void guiPrintPatientReport_Click_1(object sender, EventArgs e)
        {
            FillStructForPWVPatientReport();
            PWVReportData.RptReportType = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.GuiSettingsPwvPatientReport);

            StringBuilder sbRange = new StringBuilder(string.Empty);

            // call obj.GetBpRefRange(int age) to get array of reference value objects 
            // refValue array contains all reference data required for the report 
            BizBpRefValue[] refValue = obj.GetBpRefRange(obj.patientAge);

            char padChar = ' ';

            // to get the range text in local language and PWV reference value 
            foreach (BizBpRefValue rv in refValue)
            {
                // append the ranges and value in stringbuilder
                sbRange.AppendLine(string.Format("{0} {1}{2}  {3}", oMsgMgr.GetMessage(CrxStructCommonResourceMsg.PwvBlText), rv.Value.ToString("#0.0").PadLeft(5, padChar), CrxMessagingManager.Instance.GetMessage(CrxStructCommonResourceMsg.GuiDisplayColon), CrxMessagingManager.Instance.GetMessage(rv.Range.ToString())));
            }

            // assign the BP range fetched from BLL interface to structure
            PWVPatientReportData.RptPatientBpRefRange = sbRange.ToString();

            ReportPreview rpPreview = new ReportPreview();
            rpPreview.Show();
        }

        /** This method prints PWV report as per the report screen
       * */       
        private void guiprintPwvReport_Click(object sender, EventArgs e)
        {
            FillStructForPWVReport();
            PWVReportData.RptReportType = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.GuiSettingsPwvReport);
            ReportPreview rpPreview = new ReportPreview();
            rpPreview.Show();
        }        
        
        /**This event is fired when the user releases the keyboard key after pressing it.
         * Here we change the focus from on control to another.
         */ 
        private void Report_KeyUp(object sender, KeyEventArgs e)
        {
            const string ControlName = ""; // "guiraddocwnd";
            if (e.KeyCode == Keys.Tab && ((Report)sender).ActiveControl.Name.Equals(ControlName))
            {
                if (objDefaultWindow.radtabReport.Text.Equals(oMsgMgr.GetMessage(CrxStructCommonResourceMsg.TabAnalysis)))
                {
                    // if ((guiradchkAssesments.Focused == false))
                    // {
                    guiradlblReportAssessments.Focus();
                }
                else
                {
                    guiradbtnreportedit.Focus();
                }                
            }
        }

        /**This method is used to set the chart titles for the charts used.
         */ 
        private void SetFontForChartTitles()
        {
            const int FontSize = 11;
            Font font = new Font(GuiConstants.FontName, FontSize, FontStyle.Bold);
            guiradAnalysisChartHeading.Font = guiradlbReportNormalRange.Font = guiradlblReportReferenceRange.Font = font;
        }

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

                   // ((FillPrimitive)label.LabelElement.Children[0]).BackColor = Color.FromArgb(172, 177, 204);

                    // ((FillPrimitive)label.LabelElement.Children[0]).BackColor = Color.FromArgb(255,255,255); 
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

        /**This method is used to check configuration settings for Range graphs.
         */ 
        private void CheckConfigSettingsForRangeGraphs()
        {
            // Healthy population
            if (!CrxConfigManager.Instance.PwvSettings.NormalRange)
            {
                guichartNormalRange.Visible = false;
                guiradlbReportNormalRange.Visible = false;
                guiradlblReportNormalMsg.Visible = false;
            }
            else
            {
                guichartNormalRange.Visible = true;
                guiradlbReportNormalRange.Visible = true;
                guiradlblReportNormalMsg.Visible = true;
            }

            // European General Popualtion
            if (!CrxConfigManager.Instance.PwvSettings.ReferenceRange)
            {
                guichartReferenceRange.Visible = false;
                guiradlblReportReferenceRange.Visible = false;
                guiradlblRefRangeDescription.Visible = false;
                guiradlblReportBpRange.Visible = false;
                guireportradlblReferenceMsg.Visible = false;
            }
            else
            {
                guichartReferenceRange.Visible = true;
                guiradlblReportReferenceRange.Visible = true;
                guiradlblRefRangeDescription.Visible = true;
                guiradlblReportBpRange.Visible = true;
                guireportradlblReferenceMsg.Visible = true;
            }
        }

        /**This event is fired when user clicks on the Print button to print the Patient Analysis Report.
         */ 
        private void guiradbtnAnalysisPrint_Click(object sender, EventArgs e)
        {
            try
            {
                FillStructForPWVReport();
                PWVReportData.RptReportType = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.GuiSettingsPwvAnalysis);
                AnaylsisPreview analysisPreview = new AnaylsisPreview();
                analysisPreview.Show();
            }
            catch (Exception ex)
            {
                GUIExceptionHandler.HandleException(ex, this);
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

        /** This event is used to set the alternate color for the assessment grid's records.
         */ 
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
                    /*
                    if (IsControlAndUpArrowKeyPressed)
                    {
                        IsControlAndUpArrowKeyPressed = false;
                        row.BackColor = Color.Aqua;
                        row.DrawBorder = true;
                        row.BorderBoxStyle = BorderBoxStyle.SingleBorder;
                        row.BorderColor = Color.Black;
                    }*/
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

        /**This method is fired when row selection is changes in the assessments grid.
         */ 
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

        /**This method is used to display the analysis screen when the user selects multiplpe assesments.
         */ 
        private void DisplayAnalysisScreen()
        {
            EnableDisableReportPrintButton(false);

            // display analysis screen
            guiradbtnreportedit.Enabled = false;
            guiradpnlAnalysis.Visible = true;
            guiradbtnRepeat.Enabled = false;
            guiradbtnDelete.Enabled = true;
            objDefaultWindow.radtabCapture.Enabled = false;
            ReportPWVDisplayMode(true);            
        }

        /**This method is used to calculate PWv distance for Subtraction method.
         */ 
        private void CalculatePwvDistanceForSubtractionMethod()
        {
            // if ((guiradtxtCarotid.Text.Length > 0) && (guiradtxtReportCuff.Text.Length > 0) && (guiradtxtReportFemoToCuff.Text.Length > 0))
            if ((guiradtxtCarotid.Text.Length > 0) && (guiradtxtReportCuff.Text.Length > 0))
            {
                obj.myPWVDirectDistance.distance = GuiConstants.DefaultValue;
                obj.myCarotidDistance.distance = (crxMgrObject.PwvSettings.PWVDistanceUnits.Equals((int)CrxGenPwvValue.CrxPwvDistDistUnitsCM)) ? (ushort)(ushort.Parse(guiradtxtCarotid.Text.Trim()) * GuiConstants.DivisionFactor) : ushort.Parse(guiradtxtCarotid.Text.Trim());
                obj.myCuffDistance.distance = (crxMgrObject.PwvSettings.PWVDistanceUnits.Equals((int)CrxGenPwvValue.CrxPwvDistDistUnitsCM)) ? (ushort)(ushort.Parse(guiradtxtReportCuff.Text.Trim()) * GuiConstants.DivisionFactor) : ushort.Parse(guiradtxtReportCuff.Text.Trim());
                if (guiradtxtReportFemoToCuff.Text.Trim().Equals(string.Empty))
                {
                    obj.myFemoral2CuffDistance.distance = 0;
                }
                else
                {
                    obj.myFemoral2CuffDistance.distance = (crxMgrObject.PwvSettings.PWVDistanceUnits.Equals((int)CrxGenPwvValue.CrxPwvDistDistUnitsCM)) ? (ushort)(ushort.Parse(guiradtxtReportFemoToCuff.Text.Trim()) * GuiConstants.DivisionFactor) : ushort.Parse(guiradtxtReportFemoToCuff.Text.Trim());
                }
            }
        }

        /**This method is used to calculate PWV Distance for Direct method.
         */ 
        private void CalculatePwvDistanceForDirectMethod()
        {
           // if ((guiradtxtCarotid.Text.Length > 0) && (guiradtxtReportFemoToCuff.Text.Length > 0))
            if ((guiradtxtCarotid.Text.Length > 0))
            {
                obj.myPWVDirectDistance.distance = (crxMgrObject.PwvSettings.PWVDistanceUnits.Equals((int)CrxGenPwvValue.CrxPwvDistDistUnitsCM)) ? (ushort)(ushort.Parse(guiradtxtCarotid.Text.Trim()) * GuiConstants.DivisionFactor) : ushort.Parse(guiradtxtCarotid.Text.Trim());
                obj.myCarotidDistance.distance = GuiConstants.DefaultValue;
                obj.myCuffDistance.distance = GuiConstants.DefaultValue;
                if (guiradtxtReportFemoToCuff.Text.Trim().Equals(string.Empty))
                {
                    obj.myFemoral2CuffDistance.distance = 0;
                }
                else
                {
                    obj.myFemoral2CuffDistance.distance = (crxMgrObject.PwvSettings.PWVDistanceUnits.Equals((int)CrxGenPwvValue.CrxPwvDistDistUnitsCM)) ? (ushort)(ushort.Parse(guiradtxtReportFemoToCuff.Text.Trim()) * GuiConstants.DivisionFactor) : ushort.Parse(guiradtxtReportFemoToCuff.Text.Trim());
                }
            }
        }

        /*Begin: AtCor-<Drop2>-<Sprint4>, TM, <PWVSW-392>,<11 August 2011>
         */

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
        
        /** This method is used to convert String array to Double array
         * */
        private double[] CommonStringArrToDoubleArr(string[] sortArr)
        {
            double[] bpSort = new double[sortArr.Length];

            for (int i = 0; i < sortArr.Length; i++)
            {
                bpSort[i] = Convert.ToDouble(sortArr[i]);
            }

            return bpSort;
        }

        /** This method is used to convert Double array to String array
        * */
        private string[] CommonDoubleArrToStringArr(double[] sortArr)
        {
            string[] bpSort = new string[sortArr.Length];

            for (int i = 0; i < sortArr.Length; i++)
            {
                bpSort[i] = Convert.ToString(sortArr[i]);
            }

            return bpSort;
        }        

        private void guiradtxtReportCuff_TextChanged(object sender, EventArgs e)
        {
            if (!guiradbtnreportedit.Visible)
            {
                isValueChanged = true;
            }
        }

        private void guiradtxtCarotid_TextChanged(object sender, EventArgs e)
        {
            if (!guiradbtnreportedit.Visible)
            {
                isValueChanged = true;
            }
        }

        private void guiradtxtReportFemoToCuff_TextChanged(object sender, EventArgs e)
        {
            if (!guiradbtnreportedit.Visible)
            {
                isValueChanged = true;
            }
        }

        private void guiradtxtReportBloodPressure1_TextChanged(object sender, EventArgs e)
        {
            if (!guiradbtnreportedit.Visible)
            {
                isValueChanged = true;
            }
        }

        private void guiradtxtReportBloodPressure2_TextChanged(object sender, EventArgs e)
        {
            if (!guiradbtnreportedit.Visible)
            {
                isValueChanged = true;
            }
        }

        private void guiradtxtReportHeight_TextChanged(object sender, EventArgs e)
        {
            if (!guiradbtnreportedit.Visible)
            {
                isValueChanged = true;
            }
        }

        private void guiradtxtReportHeightInches_TextChanged(object sender, EventArgs e)
        {
            if (!guiradbtnreportedit.Visible)
            {
                isValueChanged = true;
            }
        }  
   
        /*End: AtCor-<Drop2>-<Sprint4>, TM, <PWVSW-392>,<11 August 2011>
         */
    }
}