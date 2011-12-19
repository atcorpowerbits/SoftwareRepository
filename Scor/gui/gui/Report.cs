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
        public static event EventHandler OnPwvMeasurementChangedEvent;

        const int MaxLabelYValue = 12; // this denotes the maximum number of values to be displayed on Y axis so that it does not overlap                      
        const int LblVerticalAngle = -90; // angle of labels to display vertically on analysis screen when more records are are selected
        const int LblHorizontalAngle = 0; // angle of labels to display horizontally on analysis screen when few records are are selected
        const string CulturalNeutralDateFormat = "yyyy-MM-dd HH:mm:ss"; // this is a cultural neutral format used for fetching data for different regional settings from back end
        const int MaxNumberOfPointsForChart = 60; // This is used to set maximum number of points which can be displayed at any given time for PWV ananlysis chart.
        readonly string serverNameString = string.Empty;
        readonly BizPatient patientObj = BizPatient.Instance();        
        CrxMessagingManager oMsgMgr;
        CrxConfigManager crxMgrObject;
        CrxDBManager dbMagr;      
        GuiFieldValidation objValidateReport;
        
        CrxStructPWVMeasurementData crxPWV = new CrxStructPWVMeasurementData();
        
        int bobj;
        int numeberOfRecordsSelected;
        
        string dateToCompare = string.Empty; // used to compare dates when 30 sec wait interval is imposed to enable / disable repeat button based on last record selected
        string dateWithComma = string.Empty;
        int recordsToDelete; // this variable holds value for number of records to delete and is used across dfifferent methods 
        string lastAssessmentDate = string.Empty;
        private DefaultWindow objDefaultWindow;
        private bool isValueChanged = false;
        private bool isHeightOutsideIntegerLimits = false;
        bool isFromLoad = false; // This variable is used to denote wether call to method PopulateBizFromCrx is made on load of report or when assesment is selected

        string[] date; // date array to be used on analysis screen
        string[] heartRate; // heart rate array to be used on analysis screen
        string[] pWv; // pwv velocity array to be used on analysis screen
        string[] pwvTime;
        string[] isStdDeviationValid; // standard deviation array to be used on analysis screen
        int[] xCoordinate; // array of x coordinates to display data to the closest datapoint
               
        int labelInterval;

        // denotes chart type on analysis screen
        enum ChartName 
        {
            Pwv, 
            HeartRate
        }

        // series used on analysis screen
        enum SeriesType 
        { 
            HeartLine = 0, 
            HeartPoint, 
            PwvLine, 
            PwvPoint, 
            ErrorBar
        } 

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
            InitializeComponent();
          
            SetFontForChartTitles();

            // subscribe for form changes
            SubscribeReportFormChanges();
            InitializeReportScreen();
            
            // set the default window
            objDefaultWindow = defWindow;

            // initialize servername string
            serverNameString = GuiCommon.ServerNameString();                
            guichartSuperImposedWaveform.BackColor = Color.White;
            guiradlblReportCarotid.ForeColor = Color.Blue;
        }             

        /** This method initializes crx objects & chart series
        * */
        public void InitializeReportScreen()
        {
            try
            {
                dbMagr = CrxDBManager.Instance;
                oMsgMgr = CrxMessagingManager.Instance;
                crxMgrObject = CrxConfigManager.Instance;

                crxMgrObject.GetGeneralUserSettings();
                crxMgrObject.GetPwvUserSettings();
                SetShape(guilblReportPatientIdValue, guilblReportDobValue, guilblReportAgeValue, guilblReportGenderValue, guiradlblreportSPdisplay, guiradlblReportBloodPressure2, guiradlblReportOperatordisplay, guiradlblReportNotesDisplay, guiradlblReportPwvDistanceMethodType, guiradlblreportpwvdistancedisplay1, guiradlblreportpwvdistancedisplay, guiradlblReportHeightDisplay, guiradlblReportHeightInches, guiradlblInterpretationDisplay);
                SetShape(guiradtxtReportBloodPressure1, guiradtxtReportBloodPressure2, guiradtxtReportOperator, guiradtxtReportNotes, guiradtxtReportCuff, guiradtxtCarotid, guiradtxtReportFemoToCuff, guiradtxtReportHeightInches, guiradtxtReportHeight, guiradtxtInterpretation);
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
                GuiCommon.IsWaitIntervalImposed = !value;
                // commenting the below as part of review comment.
                // GuiCommon.CaptureToSetup = !value;

                objDefaultWindow.radtabCapture.Enabled = value;
                guiradbtnRepeat.Enabled = value;                            

                if (value)
                {
                    CheckLastAssessmentSelected(dateToCompare);
                }
            }
            catch (Exception ex)
            {
                throw (ex);
            }
        }

        // Any exception will be handeld by Report_Load Event
        public void LoadPWVReport()
        {
            try
            {               
                // This variable is set when the user is on Report screen.
                GuiCommon.IsOnReportForm = true;

                // Clearing the capture time label on load.
                objDefaultWindow.radlblCaptureTime.Text = string.Empty;

                bobj = GuiConstants.SystemId;
                // commenting the below as part of review comment.
                // GuiCommon.CaptureToSetup = false;
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

                // binds assessment details related to patient
                FillPatientAssessmentDetailsReport();

                // to check if wait interval is imposed and accordingly disable/ enable capture tab & repeat buttons
                CheckWaitIntervalImposed();
                CheckForSimualtionMode();              
            }
            catch (Exception ex)
            {
                throw (ex);
            }
        }
       
        public void SaveChangesOnMenuFocus()
        {
            try
            {
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
                                GuiCommon.IsMenuItemShown = true;
                                break;
                            default:

                                // stay on report screen
                                GuiCommon.IsMenuItemShown = false;
                                break;
                        }
                    }
                }
            }
            catch (Exception ex)
            {
                throw (ex);
            }
        }

        // Any Exception will be handled by guiradbtnreportsave_Click Event
        public void SaveChangesOnEdit()
        {
            try
            {
                objDefaultWindow.radlblMessage.Text = string.Empty;
                objDefaultWindow.guiradmnuDatabase.Enabled = true;

                // check if mandatory fields are entered
                if (!objValidateReport.CheckMandatoryFields())
                {
                    // check db connection
                    if (dbMagr.CheckConnection(serverNameString, crxMgrObject.GeneralSettings.SourceData) == Convert.ToInt32(GuiCommon.NumericValue.Zero))
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
                                GuiCommon.IsMenuItemShown = true;
                                isValueChanged = false;
                                GuiCommon.IsFormChanged = false;
                                break;
                            case (int)InitializeCrxValue.ValidationFailed:

                                // GuiCommon.bizObject validation failed  
                                if (!isHeightOutsideIntegerLimits)
                                {
                                    PopulateBizFromCrx(dateToCompare);
                                }

                                GuiCommon.IsMenuItemShown = false;
                                isValueChanged = true;
                                GuiCommon.IsFormChanged = true;
                                break;
                            case (int)InitializeCrxValue.ReportCalculationFailed:

                                // report calculation failed
                                RadMessageBox.Show(this, oMsgMgr.GetMessage(CrxStructCommonResourceMsg.ReportCalculateError), oMsgMgr.GetMessage(CrxStructCommonResourceMsg.SystemError), MessageBoxButtons.OK, RadMessageIcon.Error);
                                GuiCommon.IsMenuItemShown = false;
                                isValueChanged = false;
                                GuiCommon.IsFormChanged = false;
                                break;
                            default:
                                break;
                        }
                    }
                    else
                    {
                        DialogResult result = RadMessageBox.Show(this, GuiCommon.ConnectionErrorString(), oMsgMgr.GetMessage(CrxStructCommonResourceMsg.SystemError), MessageBoxButtons.RetryCancel, RadMessageIcon.Error);
                        if (result == DialogResult.Retry)
                        {
                            Invoke(new EventHandler(guiradbtnreportsave_Click));
                        }
                    }

                    GuiCommon.ExitApp = GuiCommon.IsMenuItemShown ? Convert.ToInt32(GuiCommon.NumericValue.Zero) : Convert.ToInt32(GuiCommon.NumericValue.One);
                }
                else
                {
                    GuiCommon.IsFormChanged = true;
                    GuiCommon.ExitApp = GuiCommon.IsMenuItemShown ? Convert.ToInt32(GuiCommon.NumericValue.Zero) : Convert.ToInt32(GuiCommon.NumericValue.One);
                }

                CheckForSimualtionMode();
            }
            catch (Exception ex)
            {
                throw (ex);
            }
        }

      

        /**This is invoked on the load of report window.
        * fetches & binds report screen data 
        */
        private void Report_Load(object sender, EventArgs e)
        {
            try
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
            catch (Exception ex)
            {
                GUIExceptionHandler.HandleException(ex, this);
            }
        }

        /** This method set default options for buttons on report screen & calculates patients age
         * */
        // Any exception will be handeld by Report_Load Event
        private void SetDefaultValuesOnLoad()
        {
            // make only edit button visible
            guiradbtnreportcancel.Visible = false;
            guiradbtnreportedit.Visible = true;
            guiradbtnreportsave.Visible = false;
            guiradpnlAnalysis.Visible = false;

            objDefaultWindow.radtabReport.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.TabReport);            
            GuiCommon.bizObject.CalculateAge();          

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
                guiradlblReportPwvDitanceUnits.Text = guiradlblReportPwvDitanceUnits1.Text = crxMgrObject.PwvSettings.PWVDistanceUnits.Equals(Convert.ToInt32(GuiCommon.NumericValue.Zero)) ? oMsgMgr.GetMessage(CrxStructCommonResourceMsg.Mm) : oMsgMgr.GetMessage(CrxStructCommonResourceMsg.Cm);
                guiradlblReportPwvDistance.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.LabelPwvDistance);
                guiradlblReportAssessments.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.LblReportAssessments);
                guiradlblReportPatientId.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.LblPatientId);
                guiradlblReportPatientName.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.LblPatientName);
                guiradlblReportGender.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.LblReportGender);
                guiradlblReportDOB.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.LblReportDob);
                guiradlblReportAge.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.LblReportAge);
                guiradlblReportheightWeight.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.LblHeight);
                guiradlblPatientDetails.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.PrtPwvTextPatientDetails); 
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
                guiradbtnPrint.DefaultItem = crxMgrObject.PwvSettings.DefaultReport.Equals(CrxStructCommonResourceMsg.PwvPatientReport) ? guiPrintPatientReport : guiprintPwvReport;
               // guiradlblReportBpRange.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.GuiReportLblBpRange);
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
            try
            {
                guiradlblCarotid.Tag = guiradtxtCarotid.Tag = crxMgrObject.PwvSettings.PWVDistanceMethod.Equals((int)CrxGenPwvValue.CrxPwvDistMethodSubtract) ? oMsgMgr.GetMessage(CrxStructCommonResourceMsg.FemoralDistanceCarotidToSternalCuff) : oMsgMgr.GetMessage(CrxStructCommonResourceMsg.FemoralDistanceCarotidToFemoralCuff);
                guiradlblReportCuff.Tag = guiradtxtReportCuff.Tag = crxMgrObject.PwvSettings.PWVDistanceMethod.Equals((int)CrxGenPwvValue.CrxPwvDistMethodSubtract) ? oMsgMgr.GetMessage(CrxStructCommonResourceMsg.FemoralDistanceSternalNotchToFemoralCuff) : string.Empty;
                guiradlblReportFemoToCuff.Tag = guiradtxtReportFemoToCuff.Tag = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.FemoralDistanceFemoraltoCuff);
                guiradlblReportBloodPressure1.Tag = guiradtxtReportBloodPressure1.Tag = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.FieldPatientSp);
                guiradlblBloodPressure2.Tag = guiradtxtReportBloodPressure2.Tag = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.FieldPatientDp);
                guiradlblReportheightWeight.Tag = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.FieldPatientHeight);
                guiradtxtReportHeight.Tag = crxMgrObject.GeneralSettings.HeightandWeightUnit.Equals((int)CrxGenPwvValue.CrxGenHeightWeightMetric) ? oMsgMgr.GetMessage(CrxStructCommonResourceMsg.FieldPatientHeight) : oMsgMgr.GetMessage(CrxStructCommonResourceMsg.FieldPatientHeightFoot);
                guiradtxtReportHeightInches.Tag = crxMgrObject.GeneralSettings.HeightandWeightUnit.Equals((int)CrxGenPwvValue.CrxGenHeightWeightMetric) ? string.Empty : oMsgMgr.GetMessage(CrxStructCommonResourceMsg.FieldPatientHeightInch);
            }
            catch (Exception ex)
            {
                GUIExceptionHandler.HandleException(ex, this);
            }
       }

        /**This event fires on edit button click
        */
        private void guiradbtnreportedit_Click(object sender, EventArgs e)
        {
            try
            {
                // Show edit mode in the status bar.
                objDefaultWindow.guiradmnuDatabase.Enabled = false;
                objDefaultWindow.radlblMessage.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.EditMode);

                // make display panel visible for PWV distance
                guiradpnldisplayPWVDistance.Visible = false;
                guiradpnlEditPWVdistance.Visible = true;
                ReportPWVDisplayMode(false);
                guiradbtnAnalysisPrint.Enabled = false;

                // populates PWV measurement fields as per Settings from config manager
                guiradlblReportCuffUnits.Text = guiradlblReportFemoralCuffUnits.Text = guiradlblCarotidUnits.Text = crxMgrObject.PwvSettings.PWVDistanceUnits.Equals(Convert.ToInt32(GuiCommon.NumericValue.Zero)) ? oMsgMgr.GetMessage(CrxStructCommonResourceMsg.Mm) : oMsgMgr.GetMessage(CrxStructCommonResourceMsg.Cm);
                ushort tempVal = GuiCommon.bizObject.myFemoral2CuffDistance.distance;
                guiradtxtReportFemoToCuff.Text = crxMgrObject.PwvSettings.PWVDistanceUnits.Equals((int)CrxGenPwvValue.CrxPwvDistDistUnitsCM) ? (tempVal / GuiConstants.DivisionFactor).ToString() : tempVal.ToString();
                guiradtxtReportFemoToCuff.Text = guiradtxtReportFemoToCuff.Text.Equals("0") ? string.Empty : guiradtxtReportFemoToCuff.Text;
                SetPwvDistanceFieldForEditing();

                // set height & weight details
                guiradtxtReportHeight.Text = guiradlblReportHeightDisplay.Text;
                guiradtxtReportHeightInches.Text = guiradlblReportHeightInches.Text;
                guiradtxtReportNotes.Text = GuiCommon.bizObject.notes;

                SetBloodPressureDataForEditing();
                isValueChanged = false; 
                guiradbtnreportedit.Visible = false;
                guiradbtnreportcancel.Visible = true;
                guiradbtnreportsave.Visible = true;
              
                // in edit mode disable repeat & capture buttons
                guiradbtnRepeat.Enabled = false;
                objDefaultWindow.radtabCapture.Enabled = false;
                objDefaultWindow.guicmbxCurrentMode.Enabled = false;
                objDefaultWindow.guiradgrpbxPwvDistanceMethod.Enabled = false;
                GuiCommon.IsFormChanged = true;
            }
            catch (Exception ex)
            {
                GUIExceptionHandler.HandleException(ex, this);
            }
        }
        
        /**This method sets Carotid, cuff & femoral to cuff values for editing as per PWV distance method
       */
        private void SetPwvDistanceFieldForEditing()
        {
            try
            {
                ushort tempVal;

                // Settings Validation for Field limits of PWV Distance Method textboxes
                switch (crxMgrObject.PwvSettings.PWVDistanceUnits)
                {
                    case (int)CrxGenPwvValue.CrxPwvDistDistUnitsMM:
                        guiradtxtReportCuff.MaxLength = Convert.ToInt32(GuiCommon.NumericValue.Four);
                        guiradtxtCarotid.MaxLength = Convert.ToInt32(GuiCommon.NumericValue.Three);
                        guiradtxtReportFemoToCuff.MaxLength = Convert.ToInt32(GuiCommon.NumericValue.Three);
                        break;
                    case (int)CrxGenPwvValue.CrxPwvDistDistUnitsCM:
                        guiradtxtReportCuff.MaxLength = Convert.ToInt32(GuiCommon.NumericValue.Three);
                        guiradtxtCarotid.MaxLength = Convert.ToInt32(GuiCommon.NumericValue.Two);
                        guiradtxtReportFemoToCuff.MaxLength = Convert.ToInt32(GuiCommon.NumericValue.Two);
                        break;
                    default:
                        break;
                }

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

                        tempVal = GuiCommon.bizObject.myCuffDistance.distance.Equals(GuiConstants.DefaultValue) ? (ushort)0 : GuiCommon.bizObject.myCuffDistance.distance;
                        guiradtxtReportCuff.Text = crxMgrObject.PwvSettings.PWVDistanceUnits.Equals((int)CrxGenPwvValue.CrxPwvDistDistUnitsCM) ? (tempVal / GuiConstants.DivisionFactor).ToString() : tempVal.ToString();

                        tempVal = GuiCommon.bizObject.myCarotidDistance.distance.Equals(GuiConstants.DefaultValue) ? (ushort)0 : GuiCommon.bizObject.myCarotidDistance.distance;
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
                        tempVal = GuiCommon.bizObject.myPWVDirectDistance.distance.Equals(GuiConstants.DefaultValue) ? (ushort)0 : GuiCommon.bizObject.myPWVDirectDistance.distance;
                        guiradtxtCarotid.Text = crxMgrObject.PwvSettings.PWVDistanceUnits.Equals((int)CrxGenPwvValue.CrxPwvDistDistUnitsCM) ? (tempVal / GuiConstants.DivisionFactor).ToString() : tempVal.ToString();


                        switch (crxMgrObject.PwvSettings.PWVDistanceUnits)
                        {
                            case (int)CrxGenPwvValue.CrxPwvDistDistUnitsMM:                             
                                guiradtxtCarotid.MaxLength = Convert.ToInt32(GuiCommon.NumericValue.Four);                               
                                break;
                            case (int)CrxGenPwvValue.CrxPwvDistDistUnitsCM:                               
                                guiradtxtCarotid.MaxLength = Convert.ToInt32(GuiCommon.NumericValue.Three);                              
                                break;
                            default:
                                break;
                        }

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

        /**This method sets SP, DP & MP values for editing in textboxes
       */
        private void SetBloodPressureDataForEditing()
        {
            try
            {
                // sets SP, DP & MP values as per session & config object
                if (GuiCommon.bizObject.bloodPressureEntryOption != ushort.Parse(crxMgrObject.BpSettings.BloodPressure.ToString()))
                {
                    guiradlblReportBloodPressure1.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.Sp);
                    guiradlblBloodPressure2.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.LabelDp);

                    guiradtxtReportBloodPressure1.Text = (GuiCommon.bizObject.bloodPressure.SP == null || GuiCommon.bizObject.bloodPressure.SP.Reading.Equals(GuiConstants.DefaultValue)) ? string.Empty : GuiCommon.bizObject.bloodPressure.SP.Reading.ToString();
                    guiradtxtReportBloodPressure2.Text = (GuiCommon.bizObject.bloodPressure.DP == null || GuiCommon.bizObject.bloodPressure.DP.Reading.Equals(GuiConstants.DefaultValue)) ? string.Empty : GuiCommon.bizObject.bloodPressure.DP.Reading.ToString();
                }
                else
                {
                    guiradtxtReportBloodPressure1.Text = guiradlblreportSPdisplay.Text;
                    guiradtxtReportBloodPressure2.Text = guiradlblReportBloodPressure2.Text;
                }
            }
            catch (Exception ex)
            {
                GUIExceptionHandler.HandleException(ex, this);
            }
        }
       
        /** This event fires on cancel button click
        */
        private void guiradbtnreportcancel_Click(object sender, EventArgs e)
        {
            try
            {
                // call method to bring report screen to display mode
                SetPWVDsiplayMode();
                CheckForSimualtionMode();
                GuiCommon.IsFormChanged = false;
            }
            catch (Exception ex)
            {
                GUIExceptionHandler.HandleException(ex, this);
            }
        }

        /** This method brings report screen left side measurement details section in display mode
        * It hides cancel & save button & unhides edit button
        * */
        private void SetPWVDsiplayMode()
        {
            try
            {
                objDefaultWindow.radlblMessage.Text = string.Empty;
                objDefaultWindow.guiradmnuDatabase.Enabled = true;
                objDefaultWindow.guiradgrpbxPwvDistanceMethod.Enabled = true;
                objDefaultWindow.guicmbxCurrentMode.Enabled = true;

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
                guiradlblReportPwvDistanceMethodType.Text = GuiCommon.bizObject.myCarotidDistance.distance.Equals(GuiConstants.DefaultValue) ? oMsgMgr.GetMessage(CrxStructCommonResourceMsg.ReportLblDirect) : oMsgMgr.GetMessage(CrxStructCommonResourceMsg.ReportLblSubtracting);
                guiradlblReportPwvDitanceUnits.Text = crxMgrObject.PwvSettings.PWVDistanceUnits.Equals(0) ? oMsgMgr.GetMessage(CrxStructCommonResourceMsg.Mm) : oMsgMgr.GetMessage(CrxStructCommonResourceMsg.Cm);

                // sets blood pressure display text in labels
                SetBloodPressureDisplayText();

                CheckLastAssessmentSelected(dateToCompare);
            }
            catch (Exception ex)
            {
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
                guilblReportAgeValue.Text = GuiCommon.bizObject.patientAge.ToString();
                guilblReportGenderValue.Text = patientObj.gender.Equals(CrxStructCommonResourceMsg.MaleTxt) ? oMsgMgr.GetMessage(CrxStructCommonResourceMsg.MaleTxt) : oMsgMgr.GetMessage(CrxStructCommonResourceMsg.FemaleTxt); 
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
            try
            {
                if (value)
                {
                    guiradbtnreportcancel.Visible = false;
                    guiradbtnreportedit.Visible = true;
                    guiradbtnreportedit.Focus();
                    guiradbtnreportsave.Visible = false;
                    guiradbtnDelete.Enabled = true;
                    guiradgridReportAssessment.Enabled = true;
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
                    guiradtxtReportNotes.SendToBack();
                    guiradtxtReportHeight.SendToBack();
                    guiradlblReportPwvDistance.BringToFront();
                    guiradlblReportBloodPressure1.BringToFront();
                    guiradlblReportBloodPressure2.BringToFront();
                    guiradlblReportOperatordisplay.BringToFront();
                    guiradlblReportHeightDisplay.BringToFront();
                    guiradlblreportpwvdistancedisplay.BringToFront();
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
                    guiradtxtReportHeight.Visible = true;
                    guiradtxtReportBloodPressure1.Visible = true;
                    guiradtxtReportBloodPressure1.Focus();
                    guiradlblReportPwvDistance.SendToBack();
                    guiradlblReportBloodPressure1.SendToBack();
                    guiradlblReportBloodPressure2.SendToBack();
                    guiradlblReportOperatordisplay.SendToBack();
                    guiradlblReportHeightDisplay.SendToBack();
                    guiradlblReportNotesDisplay.SendToBack();
                    guiradlblreportpwvdistancedisplay.SendToBack();
                    guiradtxtReportBloodPressure1.BringToFront();
                    guiradtxtReportNotes.BringToFront();
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
            catch (Exception ex)
            {
                GUIExceptionHandler.HandleException(ex, this);
            }
        }
        
        /**This method fill PWV measurement details for a particular patient
        * */
        private void FillPWVMeasurementDetailsReport()
        {
            try
            {
                const int LblReportNotesDisplayMaximumLength = GuiConstants.MedicationNotesMaxLength; // denotes the maximum length of guiradlblReportNotesDisplay label

                // make display panel visible for PWV distance
                guiradpnldisplayPWVDistance.Visible = true;
                guiradpnlEditPWVdistance.Visible = false;

                if (crxMgrObject.PwvSettings.PWVDistanceUnits.Equals((int)CrxGenPwvValue.CrxPwvDistDistUnitsCM))
                {
                    guiradlblreportpwvdistancedisplay.Text = guiradlblreportpwvdistancedisplay1.Text = (GuiCommon.bizObject.calculatedDistance / GuiConstants.DivisionFactor).ToString();
                }
                else
                {
                    guiradlblreportpwvdistancedisplay.Text = guiradlblreportpwvdistancedisplay1.Text = GuiCommon.bizObject.calculatedDistance.ToString();
                }

                guiradlblReportPwvDistanceMethodType.Text = GuiCommon.bizObject.myCarotidDistance.distance.Equals(GuiConstants.DefaultValue) ? oMsgMgr.GetMessage(CrxStructCommonResourceMsg.ReportLblDirect) : oMsgMgr.GetMessage(CrxStructCommonResourceMsg.ReportLblSubtracting);
                guiradlblReportPwvDitanceUnits.Text = guiradlblReportPwvDitanceUnits1.Text = crxMgrObject.PwvSettings.PWVDistanceUnits.Equals(Convert.ToInt32(GuiCommon.NumericValue.Zero)) ? oMsgMgr.GetMessage(CrxStructCommonResourceMsg.Mm) : oMsgMgr.GetMessage(CrxStructCommonResourceMsg.Cm);
                guiradlblReportOperatordisplay.Text = guiradtxtReportOperator.Text = GuiCommon.bizObject.operatorId;
                guiradlblReportNotesDisplay.Text = guiradtxtReportNotes.Text = GuiCommon.bizObject.notes;

                // Since AutoEllipsis propert works only on singleline we are using code to check maximum length for label
                if (guiradlblReportNotesDisplay.Text.Length > LblReportNotesDisplayMaximumLength)
                {
                    guiradlblReportNotesDisplay.Text = guiradlblReportNotesDisplay.Text.Substring(Convert.ToInt32(GuiCommon.NumericValue.Zero), LblReportNotesDisplayMaximumLength - Convert.ToInt32(GuiCommon.NumericValue.Three));
                    guiradlblReportNotesDisplay.Text = string.Format("{0}...", guiradlblReportNotesDisplay.Text);
                }

                // set display text for SP, DP & MP labels
                SetBloodPressureDisplayText();

                // calculates height & weight
                int heightInInches;
                int heigthInFeet;

                guiradlblReportHeightDisplay.Text = string.Empty;
                guiradlblReportHeightInches.Text = string.Empty; 

                switch (crxMgrObject.GeneralSettings.HeightandWeightUnit)
                {
                    case (int)CrxGenPwvValue.CrxGenHeightWeightMetric:
                        guiradlblReportHeightDisplay.Text = GuiCommon.bizObject.heightAndWeight.heightInCentimetres.Equals(GuiConstants.DefaultValue) ? string.Empty : GuiCommon.bizObject.heightAndWeight.heightInCentimetres.ToString();
                        guiradlblReportHeightUnits.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.Cm);
                        guiradtxtReportHeight.MaxLength = Convert.ToInt32(GuiCommon.NumericValue.Three);
                        break;
                    case (int)CrxGenPwvValue.CrxGenHeightWeightImperial:
                        if (GuiCommon.bizObject.heightAndWeight.heightInInches != GuiConstants.DefaultValue)
                        {
                            // convert height in inches to feet & inches
                            heightInInches = int.Parse(GuiCommon.bizObject.heightAndWeight.heightInInches.ToString()) % Convert.ToInt32(GuiCommon.NumericValue.Twelve);
                            heigthInFeet = int.Parse(GuiCommon.bizObject.heightAndWeight.heightInInches.ToString()) / Convert.ToInt32(GuiCommon.NumericValue.Twelve);
                            guiradlblReportHeightDisplay.Text = heigthInFeet.ToString();
                            guiradlblReportHeightInches.Text = heightInInches.ToString();
                        }

                        guiradtxtReportHeight.MaxLength = Convert.ToInt32(GuiCommon.NumericValue.Two);
                        guiradlblReportHeightUnits.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.Feet);
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

        /** Binds PWV statistics from db if not available in sesion object
        * */
        private void BindPWVStatistics()
        {   
            // #0 will round to largest integer & #0.0 will round to one decimal place
            guiradlblReportHeartRateValue.Text = GuiCommon.bizObject.meanHeartRate.ToString().Equals(GuiConstants.DefaultValue.ToString()) ? string.Empty : GuiCommon.bizObject.meanHeartRate.ToString("#0") + " " + oMsgMgr.GetMessage(CrxStructCommonResourceMsg.HeartrateUnit);
            guiradlblReportPWVValue.Text = GuiCommon.bizObject.meanPulseWaveVelocity.ToString().Equals(GuiConstants.DefaultValue.ToString()) ? string.Empty : GuiCommon.bizObject.meanPulseWaveVelocity.ToString("#0.0") + " " + oMsgMgr.GetMessage(CrxStructCommonResourceMsg.PwvUnit);
            guiradlblStdDeviationImage.ImageIndex = GuiCommon.bizObject.isStandardDeviationValid ? (int)TickCrossImage.Tick : (int)TickCrossImage.Cross;
            guiradlblReportFemoralImage.ImageIndex = GuiCommon.bizObject.isFemoralSignalValid ? (int)TickCrossImage.Tick : (int)TickCrossImage.Cross;
            guiradlblReportCarotidImage.ImageIndex = GuiCommon.bizObject.isCarotidSignalValid ? (int)TickCrossImage.Tick : (int)TickCrossImage.Cross;
            guiradlblPwvTimeValue.Text = Math.Round(GuiCommon.bizObject.meanCorrectedTime).ToString() + " " + oMsgMgr.GetMessage(CrxStructCommonResourceMsg.UnitsTimeMs);
        }
               
        /**This method fill assessment details for a particular patient
        * */
        private void FillPatientAssessmentDetailsReport()
        {
            try
            {
                // check db connection
                if (dbMagr.CheckConnection(serverNameString, crxMgrObject.GeneralSettings.SourceData) == Convert.ToInt32(GuiCommon.NumericValue.Zero))
                {
                    // hide date time display labels
                    guiradlblReportDateTime.Visible = false;
                    guiradlblReportDateTimeDisplay.Visible = false;

                    DataSet ds = dbMagr.GetPWVMeasurementDetails(int.Parse(patientObj.patientNumber.ToString()), GuiCommon.GroupId, bobj);
                    isFromLoad = false;
                    objDefaultWindow.guiradgrpbxPwvDistanceMethod.Enabled = true;
                    objDefaultWindow.guicmbxCurrentMode.Enabled = true;

                    if (ds.Tables[0].Rows.Count > Convert.ToInt32(GuiCommon.NumericValue.Zero))
                    {
                        guiradgridReportAssessment.Columns[1].SortOrder = RadSortOrder.Ascending;
                        lastAssessmentDate = dateToCompare = ds.Tables[0].Rows[0]["StudyDateTime"].ToString();
                        dateWithComma = DateTime.Parse(ds.Tables[0].Rows[0]["StudyDateTime"].ToString()).ToString(CulturalNeutralDateFormat) + oMsgMgr.GetMessage(CrxStructCommonResourceMsg.GuiDisplayComma);
                        guiradgridReportAssessment.DataSource = ds.Tables[0];
                        guiradbtnreportedit.Enabled = true;

                        // sets assessment count for a label
                        guiradlblReportAssesmentCount.Text = string.Format("{0}{1} {2} {3}{4}", oMsgMgr.GetMessage(CrxStructCommonResourceMsg.GuiDisplayLeftSqrBracket), ds.Tables[0].Rows.Count, oMsgMgr.GetMessage(CrxStructCommonResourceMsg.ReportAssesmentRecordCount), ds.Tables[0].Rows.Count, oMsgMgr.GetMessage(CrxStructCommonResourceMsg.GuiDisplayRightSqrBracket));
                        GuiCommon.HasMeasurementDetails = true;
                        guiradgridReportAssessment.MasterTemplate.Rows[ds.Tables[0].Rows.Count - Convert.ToInt32(GuiCommon.NumericValue.One)].Cells[0].Value = true;
                        guiradbtnDelete.Enabled = true;
                        guiradbtnRepeat.Enabled = true;
                        objDefaultWindow.radtabCapture.Enabled = true;
                        guiradbtnPrint.Enabled = true;
                        guiradpnlAnalysis.Visible = false;
                        objDefaultWindow.radtabReport.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.TabReport);
                        recordsToDelete = Convert.ToInt32(GuiCommon.NumericValue.One);                      
                        GuiCommon.SetupToReport = false;

                        if (ds.Tables[0].Rows.Count == Convert.ToInt32(GuiCommon.NumericValue.One))
                        {
                            // If there is only one assessment in the grid,we need to show the split button to the user and hide the normal button used to print the analysis report.
                            guiradbtnAnalysisPrint.SendToBack();
                            guiradbtnPrint.BringToFront();
                            guiradbtnPrint.Enabled = true;
                        }

                        FillPWVMeasurementDetailsReport();                        
                        
                        SuperImposedWaveForm();
                        CheckAgeLimit(GuiCommon.bizObject.patientAge);                        
                        PlotNormalRangeGraph();
                        PlotReferenceRangeGraph();                        
                    }
                    else
                    {
                        guiradgridReportAssessment.DataSource = null;
                        guichartReferenceRange.Visible = true;
                        guireportradlblReferenceMsg.Visible = false;
                        guiradbtnreportedit.Enabled = false;
                        guiradbtnDelete.Enabled = false;
                        guiradbtnPrint.Enabled = false;
                        guiradbtnAnalysisPrint.Enabled = false;
                        ClearChartData();
                        guiradpnldisplayPWVDistance.Visible = true;
                        guiradpnlEditPWVdistance.Visible = false;                       
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
        private void SetBloodPressureDisplayText()
        {
            guiradlblReportBloodPressure1.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.Sp);
            guiradlblBloodPressure2.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.LabelDp);
            guiradlblreportSPdisplay.Text = GuiCommon.bizObject.bloodPressure.SP.Reading.Equals(GuiConstants.DefaultValue) ? string.Empty : GuiCommon.bizObject.bloodPressure.SP.Reading.ToString();
            guiradlblReportBloodPressure2.Text = GuiCommon.bizObject.bloodPressure.DP.Reading.Equals(GuiConstants.DefaultValue) ? string.Empty : GuiCommon.bizObject.bloodPressure.DP.Reading.ToString();
            CheckAgeLimit(GuiCommon.bizObject.patientAge);
            if (!GuiCommon.bizObject.bloodPressure.SP.Reading.Equals(GuiConstants.DefaultValue))
            {
                if (GuiCommon.bizObject.bloodPressure.SP.Reading <= Convert.ToInt32(GuiCommon.BPRange.BpOptimalRange))
                {
                    guiradlblReportBpRange.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.BpOptimalRange); 
                }
                else if (GuiCommon.bizObject.bloodPressure.SP.Reading >= Convert.ToInt32(GuiCommon.BPRange.BpNormalMinRange) && GuiCommon.bizObject.bloodPressure.SP.Reading < Convert.ToInt32(GuiCommon.BPRange.BpNormalMaxRange))
                {
                    guiradlblReportBpRange.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.BpNormalRange); 
                }
                else if (GuiCommon.bizObject.bloodPressure.SP.Reading >= Convert.ToInt32(GuiCommon.BPRange.BpHighNormalMinRange) && GuiCommon.bizObject.bloodPressure.SP.Reading <= Convert.ToInt32(GuiCommon.BPRange.BpHighNormalMaxRange))
                {
                    guiradlblReportBpRange.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.BpHighNormalRange); 
                }
                else if (GuiCommon.bizObject.bloodPressure.SP.Reading >= Convert.ToInt32(GuiCommon.BPRange.BpGradeIhtMinRange) && GuiCommon.bizObject.bloodPressure.SP.Reading <= Convert.ToInt32(GuiCommon.BPRange.BpGradeIhtMaxRange))
                {
                    guiradlblReportBpRange.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.BpGradeIhtRange); 
                }
                else if (GuiCommon.bizObject.bloodPressure.SP.Reading >= Convert.ToInt32(GuiCommon.BPRange.BpGradeIiAndIiiHtRange))
                {
                    guiradlblReportBpRange.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.BpGradeIiAndIiiHtRange); 
                }               
            }
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

            if ((GuiCommon.bizObject.bloodPressure.DP.Reading.Equals(GuiConstants.DefaultValue) && GuiCommon.bizObject.bloodPressure.MP.Reading.Equals(GuiConstants.DefaultValue)) ||
            (GuiCommon.bizObject.bloodPressure.DP.Reading.Equals(GuiConstants.DefaultValue) && GuiCommon.bizObject.bloodPressure.SP.Reading.Equals(GuiConstants.DefaultValue)) ||
            (GuiCommon.bizObject.bloodPressure.MP.Reading.Equals(GuiConstants.DefaultValue) && GuiCommon.bizObject.bloodPressure.SP.Reading.Equals(GuiConstants.DefaultValue)))           
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
            else if ((crxMgrObject.GeneralSettings.HeightandWeightUnit.Equals((int)CrxGenPwvValue.CrxGenHeightWeightMetric) && (GuiCommon.bizObject.heightAndWeight.heightInCentimetres > max || GuiCommon.bizObject.heightAndWeight.heightInCentimetres < min)) || (crxMgrObject.GeneralSettings.HeightandWeightUnit.Equals((int)CrxGenPwvValue.CrxGenHeightWeightImperial) && (GuiCommon.bizObject.heightAndWeight.heightInInches > max || GuiCommon.bizObject.heightAndWeight.heightInInches < min)))
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
         
        /**This event fires on save button click, saves edited measurement data in database & session object
        * */
        private void guiradbtnreportsave_Click(object sender, EventArgs e)
        {
            try
            {
                SaveChangesOnEdit();
            }
            catch (Exception ex)
            {
                GUIExceptionHandler.HandleException(ex, this);
            }
        }

        /**This method is used to Save the measurement details into the database.
         * Any Exception will be handled by guiradbtnreportsave_Click Event
        */
        private void SaveMeasurementData(CrxStructPWVMeasurementData crxPWV)
        {
            try
            {
                // update measurement data
                // save data            
                crxPWV.StudyDateTime = DateTime.Parse(GuiCommon.PwvCurrentStudyDatetime, CrxCommon.gCI);
                int iRow = guiradgridReportAssessment.Rows.Count > Convert.ToInt32(GuiCommon.NumericValue.Zero) ? dbMagr.UpdatePWVMeasurementDetails(crxPWV) : dbMagr.SavePWVMeasurementDetails(crxPWV);

                if (iRow > Convert.ToInt32(GuiCommon.NumericValue.Zero))
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
            catch (Exception ex)
            {
                throw (ex);
            }
        }

        /**This method initializes Crx structure to update changes
       * */
        private void InitializeCrxOnLoad(string studydatetime)
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

        /** This method popluates bizsession object based on single record selected for assessment
        * It fetches value based on datetime of assessment
        * */
        private void PopulateBizFromCrx(string studyDateTime)
        {
            DataSet dsPWV;

            try
            {
                // check db connection
                if (dbMagr.CheckConnection(serverNameString, crxMgrObject.GeneralSettings.SourceData) == Convert.ToInt32(GuiCommon.NumericValue.Zero))
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

                    if (dsPWV.Tables[0].Rows.Count > Convert.ToInt32(GuiCommon.NumericValue.Zero))
                    {
                        crxPWV.StudyDateTime = DateTime.Parse(dsPWV.Tables[0].Rows[0][(int)CrxDBPWVMeasurementTableList.StudyDateTime].ToString(), CrxCommon.gCI);
                        DateTime formatdate;
                        formatdate = Convert.ToDateTime(dsPWV.Tables[0].Rows[0][(int)CrxDBPWVMeasurementTableList.StudyDateTime].ToString());
                        guiradlblReportDateTimeDisplay.Text = string.Format("{0:g}", formatdate);
                        
                        GuiCommon.PwvCurrentStudyDatetime = dsPWV.Tables[0].Rows[0][(int)CrxDBPWVMeasurementTableList.StudyDateTime].ToString();
                        CrxLogger.Instance.Write("crxPWV.StudyDateTime:(PopulateBizFromCrx) " + crxPWV.StudyDateTime);   
                        byte[] buffer = (byte[])dsPWV.Tables[0].Rows[0][(int)CrxDBPWVMeasurementTableList.NormalRange];

                        int len = buffer.Length / Convert.ToInt32(GuiCommon.NumericValue.Four);

                        crxPWV.NormalRange = dbMagr.CommonByteArrtoFloatArr(len, buffer);

                        buffer = (byte[])dsPWV.Tables[0].Rows[0][(int)CrxDBPWVMeasurementTableList.ReferenceRange];
                        len = buffer.Length / Convert.ToInt32(GuiCommon.NumericValue.Four);
                        crxPWV.ReferenceRange = dbMagr.CommonByteArrtoFloatArr(len, buffer);

                        buffer = (byte[])dsPWV.Tables[0].Rows[0][(int)CrxDBPWVMeasurementTableList.CarotidSignal];
                        len = buffer.Length / Convert.ToInt32(GuiCommon.NumericValue.Two);
                        crxPWV.CarotidSignal = dbMagr.CommonByteArrtoShortArr(len, buffer);
                        crxPWV.CarotidSignalLength = (short)len;

                        buffer = (byte[])dsPWV.Tables[0].Rows[0][(int)CrxDBPWVMeasurementTableList.FemoralSignal];
                        len = buffer.Length / Convert.ToInt32(GuiCommon.NumericValue.Two);
                        crxPWV.FemoralSignal = dbMagr.CommonByteArrtoShortArr(len, buffer);
                        crxPWV.FemoralSignalLength = (short)len;

                        buffer = (byte[])dsPWV.Tables[0].Rows[0][(int)CrxDBPWVMeasurementTableList.CarotidSignalFloatOnSets];
                        len = buffer.Length / Convert.ToInt32(GuiCommon.NumericValue.Four);
                        crxPWV.CarotidSignalFloatOnSets = dbMagr.CommonByteArrtoFloatArr(len, buffer);
                        crxPWV.CarotidSignalOnSetsLength = (short)len;

                        buffer = (byte[])dsPWV.Tables[0].Rows[0][(int)CrxDBPWVMeasurementTableList.FemoralSignalFloatOnSets];
                        len = buffer.Length / Convert.ToInt32(GuiCommon.NumericValue.Four);
                        crxPWV.FemoralSignalFloatOnSets = dbMagr.CommonByteArrtoFloatArr(len, buffer);
                        crxPWV.FemoralSignalOnSetsLength = (short)len;

                        // populating height, weight, blood pressure & distance values
                        PopulateCrxWithOtherValues(dsPWV);

                        // populating other details i.e statistcis information
                        PopulateCrxWithStatistics(dsPWV);
                         GuiCommon.bizObject.Populate(crxPWV);
                         GuiCommon.bizObject.Validate();
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
         * Any exception will be handeld by PopulateBizFromCrx Function
        * */        
        private void PopulateCrxWithOtherValues(DataSet dsPwv)
        {
            try
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
            catch (Exception ex)
            {
                throw (ex);
            }
        }

        /** This method fills crx struct with statistics data
         * Any exception will be handeld by PopulateBizFromCrx Function
        * */        
        private void PopulateCrxWithStatistics(DataSet dsPwv)
        {
            try
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
            catch (Exception ex)
            {
                throw (ex);
            }
        }

        /**This method initializes Crx structure to update changes.
         * Any exception will be handled by guiradbtnreportsave_Click Event.
        * */
        private int InitializeCrx(CrxStructPWVMeasurementData crxPwv)
        {
            int flag = Convert.ToInt32(GuiCommon.NumericValue.Zero);
            // populate  GuiCommon.bizObject with entered data & check for validation
            // if it returns true then initialize crxPWV else return error & repopluate  GuiCommon.bizObject with original values                        
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

                crxPwv.Operator = guiradtxtReportOperator.Text.Trim();
                crxPwv.Notes = guiradtxtReportNotes.Text.Trim();
                crxPwv.BloodPressureEntryOption = short.Parse(crxMgrObject.BpSettings.BloodPressure.ToString());

                InitializeBPValues(crxPwv);

                CalculatePwvDistanceToUpdate(crxPwv);

                crxPwv.SystemIdentifier = bobj;
                crxPwv.GroupIdentifier = GuiCommon.GroupId;
                crxPwv.PatientNumberInternal = GuiCommon.PatientInternalNumber;
                
                // call recalculatepwvreport which will calculate PWV statistics & normal range values & will update biz session object.                             
                if (GuiCommon.bizObject.RecalculatePWVReport(crxPwv))
                {
                    crxPwv.CarotidSignal = GuiCommon.bizObject.carotidSignal.signal;
                    crxPwv.CarotidSignalFloatOnSets = GuiCommon.bizObject.carotidSignal.floatOnsets;
                    crxPwv.CarotidSignalLength = short.Parse(GuiCommon.bizObject.carotidSignal.signalLength.ToString());
                    crxPwv.CarotidSignalOnSetsLength = short.Parse(GuiCommon.bizObject.carotidSignal.onsetsLength.ToString());
                    crxPwv.CarotidSignalPulseHeight = GuiCommon.bizObject.carotidSignal.pulseHeight;
                    crxPwv.CarotidSignalPulseHeightVariation = GuiCommon.bizObject.carotidSignal.pulseHeightVariation;
                    crxPwv.CorrectionTime = GuiCommon.bizObject.correctionTime;
                    crxPwv.DataRevision = short.Parse(GuiCommon.bizObject.dataRevision.ToString());
                    crxPwv.FemoralSignal = GuiCommon.bizObject.femoralSignal.signal;
                    crxPwv.FemoralSignalFloatOnSets = GuiCommon.bizObject.femoralSignal.floatOnsets;
                    crxPwv.FemoralSignalLength = short.Parse(GuiCommon.bizObject.femoralSignal.signalLength.ToString());
                    crxPwv.FemoralSignalOnSetsLength = short.Parse(GuiCommon.bizObject.femoralSignal.onsetsLength.ToString());
                    crxPwv.FemoralSignalPulseHeight = GuiCommon.bizObject.femoralSignal.pulseHeight;
                    crxPwv.FemoralSignalPulseHeightVariation = GuiCommon.bizObject.femoralSignal.pulseHeightVariation;
                    crxPwv.IsCarotidSignalValid = GuiCommon.bizObject.isCarotidSignalValid;
                    crxPwv.IsFemoralSignalValid = GuiCommon.bizObject.isFemoralSignalValid;
                    crxPwv.IsStandardDeviationValid = GuiCommon.bizObject.isStandardDeviationValid;
                    crxPwv.MeanCorrectedTime = GuiCommon.bizObject.meanCorrectedTime;
                    crxPwv.MeanDeltaTime = GuiCommon.bizObject.meanDeltaTime;
                    crxPwv.MeanHeartRate = GuiCommon.bizObject.meanHeartRate;
                    crxPwv.MeanPulseWaveVelocity = GuiCommon.bizObject.meanPulseWaveVelocity;
                    crxPwv.NormalRange = GuiCommon.bizObject.normalRange;
                    crxPwv.NumberOfDeltas = short.Parse(GuiCommon.bizObject.numberOfDeltas.ToString());
                    crxPwv.NumberOfValidDeltas = short.Parse(GuiCommon.bizObject.numberOfValidDeltas.ToString());
                    crxPwv.ReferenceRange = GuiCommon.bizObject.referenceRange;
                    crxPwv.ReferenceRangeDistance = GuiCommon.bizObject.referenceRangeDistance;
                    crxPwv.ReferenceRangePulseWaveVelocity = GuiCommon.bizObject.referenceRangePulseWaveVelocity;
                    crxPwv.SampleRate = short.Parse(GuiCommon.bizObject.sampleRate.ToString());
                    crxPwv.Simulation = GuiCommon.bizObject.simulation;
                }
                else
                {
                    // error recalculating data
                    // do not save in database
                    flag = Convert.ToInt32(GuiCommon.NumericValue.Two);
                }

                // binds statistics information
                crxPwv.IsStandardDeviationValid = GuiCommon.bizObject.isStandardDeviationValid;
                crxPwv.IsCarotidSignalValid = GuiCommon.bizObject.isCarotidSignalValid;
                crxPwv.IsFemoralSignalValid = GuiCommon.bizObject.isFemoralSignalValid;
                crxPwv.MeanHeartRate = GuiCommon.bizObject.meanHeartRate;
                crxPwv.MeanPulseWaveVelocity = GuiCommon.bizObject.meanPulseWaveVelocity;
            }
            else
            {
                flag = Convert.ToInt32(GuiCommon.NumericValue.One);
            }

            return flag;
        }

        /** This method populates crx with blood pressure values from the textboxes
         * Any exception will be handeld by guiradbtnreportsave_Click Event
        * */        
        private void InitializeBPValues(CrxStructPWVMeasurementData crxPWV)
        {  
            crxPWV.SP = string.IsNullOrEmpty(guiradtxtReportBloodPressure1.Text.Trim()) ? GuiConstants.SdefaultValue : short.Parse(guiradtxtReportBloodPressure1.Text.Trim());
            crxPWV.DP = string.IsNullOrEmpty(guiradtxtReportBloodPressure2.Text.Trim()) ? GuiConstants.SdefaultValue : short.Parse(guiradtxtReportBloodPressure2.Text.Trim());
            crxPWV.MP = GuiConstants.SdefaultValue;           
        }

        /** This method validates session data
         * Any exception will be handeld by guiradbtnreportsave_Click Event
        * */        
        private bool ValidateSession()
        {
            GuiCommon.bizObject.operatorId = guiradtxtReportOperator.Text.Trim();
            GuiCommon.bizObject.notes = guiradtxtReportNotes.Text.Trim();
            GuiCommon.bizObject.bloodPressureEntryOption = ushort.Parse(crxMgrObject.BpSettings.BloodPressure.ToString());
            CalculateHeightAndWeightToValidateSession();
            CalculatePwvDistanceToValidateSession();
            GuiCommon.bizObject.bloodPressure.SP.Reading = string.IsNullOrEmpty(guiradtxtReportBloodPressure1.Text.Trim()) ? GuiConstants.DefaultValue : ushort.Parse(guiradtxtReportBloodPressure1.Text.Trim());
            GuiCommon.bizObject.bloodPressure.DP.Reading = string.IsNullOrEmpty(guiradtxtReportBloodPressure2.Text.Trim()) ? GuiConstants.DefaultValue : ushort.Parse(guiradtxtReportBloodPressure2.Text.Trim());
            GuiCommon.bizObject.bloodPressure.MP.Reading = GuiConstants.DefaultValue;            
            if (!isHeightOutsideIntegerLimits)
            {
                bool isValidate = GuiCommon.bizObject.Validate();
                if (isValidate)
                {
                    GetValidationForHeight(int.Parse(GuiCommon.bizObject.heightAndWeight.heightInCentimetres.ToString()));
                    return !isHeightOutsideIntegerLimits;
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
         * Any exception will be handeld by guiradbtnreportsave_Click Event
        * */
        private void CalculatePwvDistanceToUpdate(CrxStructPWVMeasurementData crxPWV)
        {
           crxPWV.PWVDistanceMethod = short.Parse(crxMgrObject.PwvSettings.PWVDistanceMethod.ToString());
           crxPWV.PWVDistance = short.Parse(GuiCommon.bizObject.calculatedDistance.ToString());
           crxPWV.Direct = short.Parse(GuiCommon.bizObject.myPWVDirectDistance.distance.ToString());
           crxPWV.Carotid = short.Parse(GuiCommon.bizObject.myCarotidDistance.distance.ToString());
           crxPWV.Cuff = short.Parse(GuiCommon.bizObject.myCuffDistance.distance.ToString());
           crxPWV.FemoraltoCuff = short.Parse(GuiCommon.bizObject.myFemoral2CuffDistance.distance.ToString());

            // calculate & intialise PWV distance only if there is change
            switch (crxPWV.PWVDistanceMethod)
            {
                case (int)CrxGenPwvValue.CrxPwvDistMethodSubtract:
                    if ((guiradtxtCarotid.Text.Length > Convert.ToInt32(GuiCommon.NumericValue.Zero)) && (guiradtxtReportCuff.Text.Length > Convert.ToInt32(GuiCommon.NumericValue.Zero)) && (guiradtxtReportFemoToCuff.Text.Length > Convert.ToInt32(GuiCommon.NumericValue.Zero)))
                    {
                        crxPWV.Direct = GuiConstants.SdefaultValue;
                        crxPWV.Carotid = short.Parse(guiradtxtCarotid.Text.Trim());
                        crxPWV.Cuff = short.Parse(guiradtxtReportCuff.Text.Trim());
                        crxPWV.FemoraltoCuff = short.Parse(guiradtxtReportFemoToCuff.Text.Trim());
                        crxPWV.PWVDistance = (short)(crxPWV.Cuff - crxPWV.Carotid - crxPWV.FemoraltoCuff);
                    }

                    break;

                case (int)CrxGenPwvValue.CrxPwvDistMethodDirect:
                    if ((guiradtxtCarotid.Text.Length > Convert.ToInt32(GuiCommon.NumericValue.Zero)) && (guiradtxtReportFemoToCuff.Text.Length > Convert.ToInt32(GuiCommon.NumericValue.Zero)))
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
         * Any exception will be handeld by guiradbtnreportsave_Click Event
        * */
        private void CalculatePwvDistanceToValidateSession()
        {           
            GuiCommon.bizObject.distanceMethod = ushort.Parse(crxPWV.PWVDistanceMethod.ToString());
                        
            // calculate & intialise PWV distance only if there is change
            switch (GuiCommon.bizObject.distanceMethod)
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
         * Any exception will be handeld by guiradbtnreportsave_Click Event
        */
        private void GetValidationForHeight(int heightValue)
        {
            if (heightValue > short.MaxValue || heightValue < Convert.ToInt32(GuiCommon.NumericValue.Zero))
            {
                string field = objValidateReport.GetLabelText(guiradtxtReportHeight.Tag.ToString());
                isHeightOutsideIntegerLimits = true;
                string err = string.Format(oMsgMgr.GetMessage(CrxStructCommonResourceMsg.GuiLimitsFormat), field, 0, string.Empty, short.MaxValue, string.Empty);
                RadMessageBox.Show(err, oMsgMgr.GetMessage(CrxStructCommonResourceMsg.SystemError), MessageBoxButtons.OK, RadMessageIcon.Error);
                guiradtxtReportHeight.Focus();
                guiradtxtReportHeight.Text = string.Empty;
            }
            else
            {
                isHeightOutsideIntegerLimits = false;
            }
        }

        /**This method calculates height & weight to update bizsession object for validating data before saving
         * Any exception will be handeld by guiradbtnreportsave_Click Event
        */
        private void CalculateHeightAndWeightToValidateSession()
        {
            // calculates height in inches & centimeters
            if (guiradtxtReportHeightInches.Visible)
            {
                // Convert the user input to height and inches
                int heightinches = (int.Parse((string.IsNullOrEmpty(guiradtxtReportHeight.Text.Trim()) ? "0" : guiradtxtReportHeight.Text.Trim())) * Convert.ToInt32(GuiCommon.NumericValue.Twelve)) + int.Parse((string.IsNullOrEmpty(guiradtxtReportHeightInches.Text.Trim()) ? "0" : guiradtxtReportHeightInches.Text.Trim()));
                                         
                // check if value is within min & max limits               
                GetValidationForHeight(heightinches);
                GuiCommon.bizObject.heightAndWeight.heightInInches = heightinches == Convert.ToInt32(GuiCommon.NumericValue.Zero) ? GuiConstants.DefaultValue : ushort.Parse(heightinches.ToString());
            }
            else
            {
                 GuiCommon.bizObject.heightAndWeight.heightInCentimetres = string.IsNullOrEmpty(guiradtxtReportHeight.Text.Trim()) ? GuiConstants.DefaultValue : ushort.Parse(guiradtxtReportHeight.Text.Trim());
                 isHeightOutsideIntegerLimits = false;
            }
        }

        /**This method calculates height & weight to update changes
         * Any exception will be handeld by guiradbtnreportsave_Click Event
        */
        private void CalculateHeightAndWeightToUpdate(CrxStructPWVMeasurementData crxPwv)
        {
            crxPwv.HeightInInches = crxPwv.WeightInPounds = crxPwv.HeightInCentimetres = crxPwv.WeightInKilograms = GuiConstants.SdefaultValue;

            // calculates height in inches & centimeters
            if (guiradtxtReportHeightInches.Visible)
            {
                int heightinches = (int.Parse((string.IsNullOrEmpty(guiradtxtReportHeight.Text.Trim()) ? "0" : guiradtxtReportHeight.Text.Trim())) * Convert.ToInt32(GuiCommon.NumericValue.Twelve)) + int.Parse((string.IsNullOrEmpty(guiradtxtReportHeightInches.Text.Trim()) ? "0" : guiradtxtReportHeightInches.Text.Trim()));
                crxPwv.HeightInInches = heightinches == Convert.ToInt32(GuiCommon.NumericValue.Zero) ? GuiConstants.SdefaultValue : short.Parse(heightinches.ToString());
            }
            else
            {
                crxPwv.HeightInCentimetres = string.IsNullOrEmpty(guiradtxtReportHeight.Text.Trim()) ? GuiConstants.SdefaultValue : short.Parse(guiradtxtReportHeight.Text.Trim());
            }
        }        

        /** Plots superimposed wave form series from BizSession.xls
        * */
        private void SuperImposedWaveForm()
        {
            try
            {
                guichartSuperImposedWaveform.ChartAreas[0].BackColor = Color.White;                                
                ushort[] femoralSignal = GuiCommon.bizObject.femoralSignal.signal;
                GuiCommon.bizObject.femoralSignal.CaptureSignal(femoralSignal, GuiCommon.bizObject.femoralSignal.signalLength, Convert.ToUInt16(GuiCommon.NumericValue.Zero), Convert.ToUInt16(GuiCommon.NumericValue.Zero));
                ushort[] carotidSignal = GuiCommon.bizObject.carotidSignal.signal;
                GuiCommon.bizObject.carotidSignal.CaptureSignal(carotidSignal, GuiCommon.bizObject.carotidSignal.signalLength, Convert.ToUInt16(GuiCommon.NumericValue.Zero), Convert.ToUInt16(GuiCommon.NumericValue.Zero));
                bool status = GuiCommon.bizObject.Calculate();
                              
                // calling method to bind statistics returned from calculate() method
                BindPWVStatistics();
                
                if (status)
                {
                    // plot super impose wave form
                    ushort[] femoralSignalToPlot = GuiCommon.bizObject.femoralSignal.signal;
                    float[] femoralOnSetPoints = GuiCommon.bizObject.femoralSignal.floatOnsets;
                    ushort[] carotidSignalToPlot = GuiCommon.bizObject.carotidSignal.signal;
                    float[] carotidOnSetPoints = GuiCommon.bizObject.carotidSignal.floatOnsets;

                    PlotSuperImposedWaveform(femoralSignalToPlot, femoralOnSetPoints, carotidSignalToPlot, carotidOnSetPoints,  GuiCommon.bizObject.femoralSignal.signalLength);
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
         * Any exception will be handeld by SuperImposedWaveForm Function
        */        
        private void PlotSuperImposedWaveform(IList<ushort> femoralSignalToPlot, float[] femoralOnSetPoints, IList<ushort> carotidSignalToPlot, float[]carotidOnSetPoints, ushort signalLength)
        {
            try
            {                
                const double MinXValue = 0;

                // plot on the waveform.
                double dblMaxXValue = signalLength;

                // new chart area                
                guichartSuperImposedWaveform.ChartAreas["area"].AxisY.IsStartedFromZero = false;
                guichartSuperImposedWaveform.ChartAreas["area"].AxisY.Enabled = AxisEnabled.False;                

                guichartSuperImposedWaveform.ChartAreas["area"].AxisY2.IsStartedFromZero = false;
                guichartSuperImposedWaveform.ChartAreas["area"].AxisY2.MajorGrid.Enabled = false;
                guichartSuperImposedWaveform.ChartAreas["area"].AxisY2.LabelStyle.Enabled = false;
                guichartSuperImposedWaveform.ChartAreas["area"].AxisY2.MajorTickMark.Enabled = false;
                guichartSuperImposedWaveform.ChartAreas["area"].AxisY2.LineDashStyle = ChartDashStyle.NotSet;

                // set x axis
                guichartSuperImposedWaveform.ChartAreas["area"].AxisX.Enabled = AxisEnabled.False;
                guichartSuperImposedWaveform.ChartAreas["area"].AxisX.MajorGrid.Enabled = false;
                guichartSuperImposedWaveform.ChartAreas["area"].AxisX.Minimum = MinXValue - Convert.ToInt32(GuiCommon.NumericValue.Ten);
                guichartSuperImposedWaveform.ChartAreas["area"].AxisX.Maximum = dblMaxXValue;
                guichartSuperImposedWaveform.ChartAreas["area"].AxisX.Interval = Convert.ToInt32(GuiCommon.NumericValue.One);

                // initialize series,chartype,add points to series and finally add series to chart.
                // Series for tonometer
                guichartSuperImposedWaveform.Series.Clear();

                // plot carotid series
                PlotCarotidSeries(carotidSignalToPlot, carotidOnSetPoints, signalLength, Color.Blue);

                // plot femoral series
                PlotFemoralSeries(femoralSignalToPlot, femoralOnSetPoints, signalLength, Color.FromArgb(54, 64, 86));
            }
            catch (Exception ex)
            {
                throw (ex);
            }
        }

        /** This method plots series & onSet points for carotid series
        * */
        // Any exception will be handeld by SuperImposedWaveForm Function
        private void PlotCarotidSeries(IList<ushort> signalToPlot, float[] onSetPoints, ushort signalLength, Color seriesColor)
        {
            try
            {
                Series tonometerOneSeries = new Series
                {
                    ChartType = SeriesChartType.FastLine,
                    Color = seriesColor,
                    XValueType = ChartValueType.Auto,
                    YValuesPerPoint = Convert.ToInt32(GuiCommon.NumericValue.One),
                    ChartArea = "area",
                    YAxisType = AxisType.Secondary,
                };

                Hashtable carotidFemoralTable = new Hashtable();
                tonometerOneSeries.Points.Clear();

                double [] TempArray = new double[signalLength];

                for (int i = Convert.ToInt32(GuiCommon.NumericValue.Zero); i < signalLength; i++)
                {           
                    tonometerOneSeries.Points.AddXY(i, signalToPlot[i]);
                    carotidFemoralTable[i] = signalToPlot[i];
                }

                ArrayList list = new ArrayList(carotidFemoralTable.Values);
                list.Sort();

                double value = Math.Round(Convert.ToDouble(list[Convert.ToInt32(GuiCommon.NumericValue.Zero)]) * GuiConstants.ChartAreaMinimumY, MidpointRounding.ToEven);
                value = ((int)Math.Round(value / Convert.ToInt32(GuiCommon.NumericValue.Ten))) * Convert.ToInt32(GuiCommon.NumericValue.Ten);
                guichartSuperImposedWaveform.ChartAreas[0].AxisY2.Minimum = value - Convert.ToInt32(GuiCommon.NumericValue.Hundred);
                value = Math.Round((Convert.ToDouble(list[list.Count - Convert.ToInt32(GuiCommon.NumericValue.One)])) * GuiConstants.ChartAreaMaximumY, MidpointRounding.ToEven);
                value = ((int)Math.Round(value / Convert.ToInt32(GuiCommon.NumericValue.Ten))) * Convert.ToInt32(GuiCommon.NumericValue.Ten);
                guichartSuperImposedWaveform.ChartAreas[0].AxisY2.Maximum = value + Convert.ToInt32(GuiCommon.NumericValue.Hundred);

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


                for (int j = Convert.ToInt32(GuiCommon.NumericValue.Zero); j < onSetPoints.Length; j++)
                {
                    int valueToPLot = int.Parse(Math.Round(double.Parse(onSetPoints[j].ToString()), MidpointRounding.ToEven).ToString());
                    int valueToPLot1 = Math.Abs(valueToPLot);

                    if (valueToPLot < Convert.ToInt32(GuiCommon.NumericValue.Zero) && valueToPLot != Convert.ToInt32(GuiCommon.NumericValue.MinusOne))
                    {
                        tonometerCarotidOnsetSeriesTwo.Points.AddXY(valueToPLot1, carotidFemoralTable[valueToPLot1]);
                        tonometerCarotidOnsetSeriesTwo.Points[tonometerCarotidOnsetSeriesTwo.Points.Count - Convert.ToInt32(GuiCommon.NumericValue.One)].MarkerStyle = MarkerStyle.Circle;
                    }
                    else if (valueToPLot > Convert.ToInt32(GuiCommon.NumericValue.Zero))
                    {
                        tonometerCarotidOnsetSeriesOne.Points.AddXY(valueToPLot1, carotidFemoralTable[valueToPLot1]);
                        tonometerCarotidOnsetSeriesOne.Points[tonometerCarotidOnsetSeriesOne.Points.Count - Convert.ToInt32(GuiCommon.NumericValue.One)].MarkerStyle = MarkerStyle.Circle;
                    }
                }

                guichartSuperImposedWaveform.Series.Add(tonometerOneSeries);
                guichartSuperImposedWaveform.Series.Add(tonometerCarotidOnsetSeriesOne);
                guichartSuperImposedWaveform.Series.Add(tonometerCarotidOnsetSeriesTwo);
                guichartSuperImposedWaveform.Invalidate();
            }
            catch (Exception ex)
            {
                throw (ex);
            }
        }

        /** This method plots series & onSet points for femoral series
         * Any exception will be handeld by SuperImposedWaveForm Function
        * */
        private void PlotFemoralSeries(IList<ushort> signalToPlot, float[] onSetPoints, ushort signalLength, Color seriesColor)
        {
            try
            {                
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
                
                for (int i = Convert.ToInt32(GuiCommon.NumericValue.Zero); i < signalLength; i++)
                {
                    tonometerTwoSeries.Points.AddXY(i, signalToPlot[i]);
                    carotidFemoralTable[i] = signalToPlot[i];
                }

                ArrayList list = new ArrayList(carotidFemoralTable.Values);
                list.Sort();

                double value = Math.Round(Convert.ToDouble(list[Convert.ToInt32(GuiCommon.NumericValue.Zero)]) * GuiConstants.ChartAreaMinimumY, MidpointRounding.ToEven);
                value = ((int)Math.Round(value / Convert.ToInt32(GuiCommon.NumericValue.Ten))) * Convert.ToInt32(GuiCommon.NumericValue.Ten);
                guichartSuperImposedWaveform.ChartAreas[0].AxisY.Minimum = value - Convert.ToInt32(GuiCommon.NumericValue.Hundred);
                value = Math.Round((Convert.ToDouble(list[list.Count - Convert.ToInt32(GuiCommon.NumericValue.One)])) * GuiConstants.ChartAreaMaximumY, MidpointRounding.ToEven);
                value = ((int)Math.Round(value / Convert.ToInt32(GuiCommon.NumericValue.Ten))) * Convert.ToInt32(GuiCommon.NumericValue.Ten);
                guichartSuperImposedWaveform.ChartAreas[0].AxisY.Maximum = value + Convert.ToInt32(GuiCommon.NumericValue.Hundred);
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

                for (int j = Convert.ToInt32(GuiCommon.NumericValue.Zero); j < onSetPoints.Length; j++)
                {
                    int valueToPLot = int.Parse(Math.Round(double.Parse(onSetPoints[j].ToString()), MidpointRounding.ToEven).ToString());
                    int valueToPLot1 = Math.Abs(valueToPLot);

                    if (valueToPLot < Convert.ToInt32(GuiCommon.NumericValue.Zero) && valueToPLot != Convert.ToInt32(GuiCommon.NumericValue.MinusOne))
                    {
                        tonometerFemoralOnsetSeriesTwo.Points.AddXY(valueToPLot1, carotidFemoralTable[valueToPLot1]);
                        tonometerFemoralOnsetSeriesTwo.Points[tonometerFemoralOnsetSeriesTwo.Points.Count - Convert.ToInt32(GuiCommon.NumericValue.One)].MarkerStyle = MarkerStyle.Circle;
                    }
                    else if (valueToPLot > Convert.ToInt32(GuiCommon.NumericValue.Zero))
                    {
                        tonometerFemoralOnsetSeriesOne.Points.AddXY(valueToPLot1, carotidFemoralTable[valueToPLot1]);
                        tonometerFemoralOnsetSeriesOne.Points[tonometerFemoralOnsetSeriesOne.Points.Count - Convert.ToInt32(GuiCommon.NumericValue.One)].MarkerStyle = MarkerStyle.Circle;
                    }
                }

                guichartSuperImposedWaveform.Series.Add(tonometerTwoSeries);
                guichartSuperImposedWaveform.Series.Add(tonometerFemoralOnsetSeriesOne);
                guichartSuperImposedWaveform.Series.Add(tonometerFemoralOnsetSeriesTwo);
                guichartSuperImposedWaveform.Invalidate();
            }
            catch (Exception ex)
            {
                throw (ex);
            }
        }

        /**This event fires when checkbox is checked or unchecked on assessment gridview
        * */
        private void guiradgridReportAssessment_ValueChanged(object sender, EventArgs e)
        {            
        }
       
        /** This method displays report & analysis screen as per assessments selected
         * Any exception will be handled by guiradgridReportAssessment_SelectionChanged Event
        * */        
        private void DisplayReportOnSelection(int recordSelected, string datetime)
        {
            try
            {
                guiradlblReportDateTime.Visible = false;
                guiradlblReportDateTimeDisplay.Visible = false;
                dateToCompare = string.Empty;

                if (recordSelected == Convert.ToInt32(GuiCommon.NumericValue.One))
                {
                    EnableDisableReportPrintButton(true);

                    // if only 1 record is selected in assessment grid bind the measurement details 
                    // pertaining to that patient
                    guiradpnlAnalysis.Visible = false;
                    guiradbtnDelete.Enabled = true;
                    guiradlblReportBpRange.Visible = true;
                    objDefaultWindow.radtabReport.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.TabReport);

                    dateToCompare = datetime.Replace(oMsgMgr.GetMessage(CrxStructCommonResourceMsg.GuiDisplayComma), string.Empty);
                    guiradbtnreportedit.Enabled = true;
                    CheckLastAssessmentSelected(dateToCompare);
                    string lastAssessmentDate1 = DateTime.Parse(lastAssessmentDate).ToString(CulturalNeutralDateFormat);

                    // when record selected is only one display record as per assessment selected
                    if (lastAssessmentDate1 == dateToCompare || isFromLoad)
                    {
                        DisplayReportForSelectedAssesment(dateToCompare);
                        isFromLoad = true;
                    }
                }
                else if (recordSelected > Convert.ToInt32(GuiCommon.NumericValue.One))
                {
                    DisplayAnalysisScreen();
                    PlotAnalysisTrendCharts(datetime);
                    objDefaultWindow.radtabReport.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.TabAnalysis);
                }
                else if (recordSelected == Convert.ToInt32(GuiCommon.NumericValue.Zero))
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
            catch (Exception ex)
            {
                throw (ex);
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
                    PlotNormalReferenceRange(guichartNormalRange,  GuiCommon.bizObject.normalRange, AxisType.Primary, AxisType.Primary);
                }                
                else
                {
                    guichartNormalRange.Visible = false;
                    guiradlbReportNormalRange.Visible = false;
                }         
            }
            catch (Exception ex)
            {
                throw (ex);
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
                    PlotNormalReferenceRange(guichartReferenceRange,  GuiCommon.bizObject.referenceRange, AxisType.Secondary, AxisType.Primary);
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
                throw (ex);
            }
        }

        /** This is a common generic method to plot both General and healthy population chart.
         * Any exception will be handled by PlotNormalRangeGraph Function
        * It gets called from both PlotNormalRangeGraph() and PlotReferenceRangeGraph() methods.
        */        
        private void PlotNormalReferenceRange(Chart rangeChart, float[] rangeToPlot, AxisType yAxisType, AxisType xAxisType)
        {
            try
            {
                int NormalRefYInterval = Convert.ToInt32(GuiCommon.NumericValue.Five); // interval used for y axis for normal & reference range graph
                int NormalRefXInterval = Convert.ToInt32(GuiCommon.NumericValue.Fifteen); // interval used for x axis for normal & reference range graph
                int ChartYAxisMin = Convert.ToInt32(GuiCommon.NumericValue.Four);
                int ChartYAxisMax = Convert.ToInt32(GuiCommon.NumericValue.TwentyFive);

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
                    BorderWidth = Convert.ToInt32(GuiCommon.NumericValue.One),
                    BackGradientStyle = GradientStyle.DiagonalLeft,
                    YAxisType = yAxisType,
                    XAxisType = xAxisType
                };

                rangeSeries.Points.Clear();

                int ageToPlot = BizConstants.MINIMUM_REFERENCE_RANGE_AGE;
                for (int i = Convert.ToInt32(GuiCommon.NumericValue.Zero); i < normalReferenceRange.Length; i++)
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
                    ShadowOffset = Convert.ToInt32(GuiCommon.NumericValue.Five),
                    YAxisType = yAxisType,
                    XAxisType = xAxisType
                };

                rangeSeries2.Points.Clear();
                rangeSeries2.Points.AddXY(double.Parse(GuiCommon.bizObject.patientAge.ToString()), double.Parse(GuiCommon.bizObject.meanPulseWaveVelocity.ToString("#0")));

                rangeChart.Series.Add(rangeSeries2);
                rangeChart.Invalidate();
            }
            catch (Exception ex)
            {
                throw (ex);
            }
        }

        /** This event deletes assessments of selected patients
        * */
        private void guiradbtnDelete_Click(object sender, EventArgs e)
        {
            try
            {                           
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

                    if (del == Convert.ToInt32(GuiCommon.NumericValue.One))
                    {
                        // records deleted successfully, bind assessment grid
                        FillPatientAssessmentDetailsReport();
                        CheckLastAssessmentSelected(dateToCompare);
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
            for (int iRow = Convert.ToInt32(GuiCommon.NumericValue.Zero); iRow < recordsToDelete; iRow++)
            {
                // preparing comma separated string of dates                        
                dateWithComma += DateTime.Parse(guiradgridReportAssessment.Rows[iRow].Cells[1].Value.ToString()).ToString(CulturalNeutralDateFormat) + oMsgMgr.GetMessage(CrxStructCommonResourceMsg.GuiDisplayComma);               
            }

            GuiConstants.DateWithComma = dateWithComma;
            return dateWithComma;
        }

        /** This method clears all chart series for tonometer, normal & reference range
        * */
        private void ClearChartData()
        {
            guichartReferenceRange.Series.Clear();
            guichartNormalRange.Series.Clear();                       
            guichartSuperImposedWaveform.Series.Clear();
        }

        /** This method resets all PWV measurement fields
        * */
        private void ResetMeasurementFields()
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
            guiradtxtReportOperator.Text = string.Empty;
            guiradlblReportOperatordisplay.Text = string.Empty;
            guiradtxtReportNotes.Text = string.Empty;
            guiradlblReportNotesDisplay.Text = string.Empty;
            guiradtxtReportBloodPressure1.Text = string.Empty;
            guiradtxtReportBloodPressure2.Text = string.Empty;
            guiradlblreportSPdisplay.Text = string.Empty;
            guiradlblReportBloodPressure2.Text = string.Empty;
            guiradlblreportpwvdistancedisplay1.Text = string.Empty;

            // reset pwv statistics
            guiradlblReportHeartRateValue.Text = string.Empty;
            guiradlblReportPWVValue.Text = string.Empty;
            guiradlblPwvTimeValue.Text = string.Empty;
            guiradlblStdDeviationImage.ImageIndex = Convert.ToInt32(GuiCommon.NumericValue.Zero);
            guiradlblReportFemoralImage.ImageIndex = Convert.ToInt32(GuiCommon.NumericValue.Zero);
            guiradlblReportCarotidImage.ImageIndex = Convert.ToInt32(GuiCommon.NumericValue.Zero);
            guiradlblPwvTimeValue.Text = string.Empty;
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

                guiradchartPulseWaveVelocity.Titles.Add(itemPwv);
                Title itemHeartRate = new Title
                {
                    Font = font,
                    Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.LblReportHeartRate),
                    ForeColor = Color.WhiteSmoke
                };
               
                guiradchartHeartRate.Titles.Add(itemHeartRate); 
                guiradchartPulseWaveVelocity.Series.Clear();
                guiradchartHeartRate.Series.Clear();
               
                // if date ends with comma, truncate it as it creates empty value in array for dates
                if (dateSelected.EndsWith(oMsgMgr.GetMessage(CrxStructCommonResourceMsg.GuiDisplayComma)))
                {
                    dateSelected = dateSelected.Remove(dateSelected.Length - Convert.ToInt32(GuiCommon.NumericValue.One));
                }

                date = dateSelected.Split(GuiConstants.Separator);

                string[] dateClac = dateSelected.Split(GuiConstants.Separator);

                string calcPwaIdWithComma = string.Empty;
                string calcDateWithComma = string.Empty;

                if (dateClac.Length > MaxNumberOfPointsForChart)
                {
                    // string[] tempPwaId = GuiConstants.PwaIdWithComma.Split(GuiConstants.Separator);

                    string[] calcDate = new string[MaxNumberOfPointsForChart];
                    date = new string[MaxNumberOfPointsForChart];

                    int clcStrt = dateClac.Length - MaxNumberOfPointsForChart;
                    for (int i = clcStrt, j = 0; i < dateClac.Length; i++, j++)
                    {
                        calcDate[j] = dateClac[i];
                        date[j] = dateClac[i];
                        string tempDateWithComma = string.Empty;
                        tempDateWithComma = dateClac[i].ToString();
                        calcDateWithComma = calcDateWithComma + tempDateWithComma + GuiConstants.Separator;
                    }
                    objDefaultWindow.radlblMessage.Text = string.Format(oMsgMgr.GetMessage(CrxStructCommonResourceMsg.MaximumPointsMessage), MaxNumberOfPointsForChart);
                }
                else
                {
                    calcPwaIdWithComma = GuiConstants.PwaIdWithComma;
                    calcDateWithComma = dateSelected;
                    date = dateSelected.Split(GuiConstants.Separator);
                    objDefaultWindow.radlblMessage.Text = string.Empty;
                }

                guiradlblReportDateTimeDisplay.Text = string.Format("{0:g}", Convert.ToDateTime(date[date.Length - Convert.ToInt32(GuiCommon.NumericValue.One)]));

                // check for connection
                if (dbMagr.CheckConnection(serverNameString, crxMgrObject.GeneralSettings.SourceData) == Convert.ToInt32(GuiCommon.NumericValue.Zero))
                {
                    CrxStructPWVTrendData trendData = new CrxStructPWVTrendData();

                    // fetch records for selected assessments
                    // dbMagr.GetPWVTrendData(GuiCommon.PatientInternalNumber, GuiCommon.GroupId, GuiCommon.SystemIdentifier, dateSelected + oMsgMgr.GetMessage(CrxStructCommonResourceMsg.GuiDisplayComma), trendData);
                       dbMagr.GetPWVTrendData(GuiCommon.PatientInternalNumber, GuiCommon.GroupId, GuiCommon.SystemIdentifier, calcDateWithComma + oMsgMgr.GetMessage(CrxStructCommonResourceMsg.GuiDisplayComma), trendData);
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
         * Any exception will be handled by PlotAnalysisTrendCharts Function
        * */
        private void PlotHeartRateTrend(CrxStructPWVTrendData trendData)
        {           
            // define strings arrays for plotting heart rate & PWV
            heartRate = trendData.HeartRateArrStr.Split(GuiConstants.Separator);
            pWv = trendData.PulseWaveVelocityArrStr.Split(GuiConstants.Separator);
            pwvTime = trendData.MeanCorrectedTimeArrStr.Split(GuiConstants.Separator);
            isStdDeviationValid = trendData.IsStdDevValidArrStr.Split(GuiConstants.Separator);

            string[] heartPwv = trendData.HeartRateArrStr.Split(GuiConstants.Separator);

            double[] heartPwvSort = CommonStringArrToDoubleArr(heartPwv);
            Array.Sort(heartPwvSort);
            heartPwv = CommonDoubleArrToStringArr(heartPwvSort);

            // plot heart rate series
            if (heartRate.Length > 0)
            {
                // assign latest record valus to bottom labels
                guiradlblReportHeartRateValue.Text = heartRate[heartRate.Length - Convert.ToInt32(GuiCommon.NumericValue.One)] + " " + oMsgMgr.GetMessage(CrxStructCommonResourceMsg.HeartrateUnit);
               
                double value = Math.Round(double.Parse(heartPwv[0]) * GuiConstants.ChartAreaMinimumY, MidpointRounding.ToEven);

                value = ((int)Math.Round(value / 10.0)) * Convert.ToInt32(GuiCommon.NumericValue.Ten);
                
                guiradchartHeartRate.ChartAreas[0].AxisY.Minimum = value;
                guiradchartHeartRate.ChartAreas[0].AxisY.Minimum = value - Convert.ToInt32(GuiCommon.NumericValue.Ten);
                guiradchartHeartRate.ChartAreas[0].AxisY.Title = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.HeartrateLblAnalysis);
                guiradchartHeartRate.ChartAreas[0].AxisY.TitleFont = new Font(GuiConstants.FontName, guiradchartHeartRate.ChartAreas[0].AxisY.TitleFont.Size, FontStyle.Bold);
                value = Math.Round(double.Parse(heartPwv[heartPwv.Length - Convert.ToInt32(GuiCommon.NumericValue.One)]) * GuiConstants.ChartAreaMaximumY, MidpointRounding.ToEven);
                guiradchartHeartRate.ChartAreas[0].AxisY.Maximum = value;
                guiradchartHeartRate.ChartAreas[0].AxisY.Maximum = value + Convert.ToInt32(GuiCommon.NumericValue.Ten);
                guiradchartHeartRate.ChartAreas[0].AxisY.IntervalOffset = Convert.ToInt32(GuiCommon.NumericValue.Zero);
                guiradchartHeartRate.ChartAreas[0].AxisY.Interval = Convert.ToInt32(GuiCommon.NumericValue.Five);

                guiradchartHeartRate.ChartAreas[0].AxisX.IntervalOffset = Convert.ToInt32(GuiCommon.NumericValue.One);
                CalculateLabelIntervalX();

                BindCustomLabelForTrendCharts(guiradchartHeartRate, heartRate.Length);

                PlotTrendChartSeries(guiradchartHeartRate, heartRate, null, ChartName.HeartRate);                
            }
        }

        /** This method plots PWV velocity trend graph 
         * Any exception will be handled by PlotAnalysisTrendCharts Function
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
            if (pWv.Length > Convert.ToInt32(GuiCommon.NumericValue.Zero))
            {
                // assign latest record valus to bottom labels
                guiradlblReportPWVValue.Text = pWv[pWv.Length - Convert.ToInt32(GuiCommon.NumericValue.One)] + " " + oMsgMgr.GetMessage(CrxStructCommonResourceMsg.PwvUnit);
                guiradlblStdDeviationImage.ImageIndex = int.Parse(isStdDeviationValid[isStdDeviationValid.Length - Convert.ToInt32(GuiCommon.NumericValue.One)]);
                guiradlblPwvTimeValue.Text = pwvTime[pwvTime.Length - Convert.ToInt32(GuiCommon.NumericValue.One)] + " " + oMsgMgr.GetMessage(CrxStructCommonResourceMsg.UnitsTimeMs);
                
                // set max value as largest pwv + largest std deviation
                // set min value as lowest pwv + largest std deviation
                double maxValue = double.Parse(heartPwv[heartPwv.Length - Convert.ToInt32(GuiCommon.NumericValue.One)], CrxCommon.nCI) + double.Parse(stdDeviation[stdDeviation.Length - Convert.ToInt32(GuiCommon.NumericValue.One)], CrxCommon.nCI) + Convert.ToInt32(GuiCommon.NumericValue.One);
                double minValue = double.Parse(heartPwv[0], CrxCommon.nCI) - double.Parse(stdDeviation[stdDeviation.Length - Convert.ToInt32(GuiCommon.NumericValue.One)], CrxCommon.nCI) - Convert.ToInt32(GuiCommon.NumericValue.One);

                maxValue = Math.Round(maxValue, Convert.ToInt32(GuiCommon.NumericValue.Zero), MidpointRounding.ToEven);
                minValue = Math.Round(minValue);
                CalculateLabelIntervalYForPwvTrend(int.Parse(minValue.ToString()), int.Parse(maxValue.ToString()));

                double value = Math.Round(minValue * GuiConstants.ChartAreaMinimumY); 
                guiradchartPulseWaveVelocity.ChartAreas[0].AxisY.Minimum = value;
                guiradchartPulseWaveVelocity.ChartAreas[0].AxisY.Title = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.PwvLblAnalysis);
                guiradchartPulseWaveVelocity.ChartAreas[0].AxisY.TitleFont = new Font(GuiConstants.FontName, guiradchartPulseWaveVelocity.ChartAreas[0].AxisY.TitleFont.Size, FontStyle.Bold);

                value = Math.Round(maxValue * GuiConstants.ChartAreaMaximumY, Convert.ToInt32(GuiCommon.NumericValue.Zero), MidpointRounding.AwayFromZero);
                guiradchartPulseWaveVelocity.ChartAreas[0].AxisY.Maximum = value;
                guiradchartPulseWaveVelocity.ChartAreas[0].AxisY.IntervalOffset = Convert.ToInt32(GuiCommon.NumericValue.Zero);
                guiradchartPulseWaveVelocity.ChartAreas[0].AxisY.Interval = Convert.ToInt32(GuiCommon.NumericValue.One);

                guiradchartPulseWaveVelocity.ChartAreas[0].AxisX.IntervalOffset = Convert.ToInt32(GuiCommon.NumericValue.One);

                BindCustomLabelForTrendCharts(guiradchartPulseWaveVelocity, pWv.Length);
                PlotTrendChartSeries(guiradchartPulseWaveVelocity, pWv, stdDeviation, ChartName.Pwv);               
            }
        }

        /** This method is used to bind custom labels for X-Axis for both Heart rate & Pwv Velocity trend chart
         * Any exception will be handled by PlotAnalysisTrendCharts Function
        * */
        private void BindCustomLabelForTrendCharts(Chart trendChart, int seriesLength)
        {
            try
            {
                Font labelFontMax = new Font(ConfigurationManager.AppSettings[GuiConstants.AppConfigParams.AnalysisFontName.ToString()].ToString(), float.Parse(ConfigurationManager.AppSettings[GuiConstants.AppConfigParams.AnalysisFontMax.ToString()].ToString()));  // sets font max size for analysis chart x axis labels
                Font labelFontMin = new Font(ConfigurationManager.AppSettings[GuiConstants.AppConfigParams.AnalysisFontName.ToString()].ToString(), float.Parse(ConfigurationManager.AppSettings[GuiConstants.AppConfigParams.AnalysisFontMin.ToString()].ToString())); // sets font min size for analysis chart x axis labels

                trendChart.ChartAreas[0].AxisX.CustomLabels.Clear();

                for (int hrseries1 = 0; hrseries1 < seriesLength; hrseries1 = hrseries1 + labelInterval)
                {
                    if (hrseries1 > (Convert.ToInt32(GuiCommon.NumericValue.Five) * labelInterval))
                    {
                        trendChart.ChartAreas[0].AxisX.LabelStyle.Angle = LblVerticalAngle;
                        trendChart.ChartAreas[0].AxisX.LabelStyle.Font = labelFontMin;
                    }
                    else
                    {
                        trendChart.ChartAreas[0].AxisX.LabelStyle.Font = labelFontMax;
                        trendChart.ChartAreas[0].AxisX.LabelStyle.Angle = LblHorizontalAngle;
                    }

                    trendChart.ChartAreas[0].AxisX.CustomLabels.Add(hrseries1 - Convert.ToInt32(GuiCommon.NumericValue.One), hrseries1 + Convert.ToInt32(GuiCommon.NumericValue.One), string.Format("{0:g}", Convert.ToDateTime(date[hrseries1].ToString())));
                }
            }
            catch (Exception ex)
            {
                throw (ex);
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
                CustomProperties = "BubbleMaxSize= " + (20 - (labelInterval * Convert.ToInt32(GuiCommon.NumericValue.Two)) + Convert.ToInt32(GuiCommon.NumericValue.One)),
                MarkerStyle = MarkerStyle.Circle,
                ShadowOffset = Convert.ToInt32(GuiCommon.NumericValue.Two)
            };

            trendLine.Points.Clear();
            trendPoint.Points.Clear();

            for (int hrseries1 = Convert.ToInt32(GuiCommon.NumericValue.Zero); hrseries1 < trendSeries.Count; hrseries1++)
            {                
                trendLine.Points.AddXY(hrseries1, double.Parse(trendSeries[hrseries1], CrxCommon.nCI));
                trendPoint.Points.AddXY(hrseries1, double.Parse(trendSeries[hrseries1], CrxCommon.nCI));

                //if (trendType == ChartName.Pwv)
                //{
                //    // add series dynamically for showing error bar on PWV chart
                //    Series correctionLine = new Series(((int)SeriesType.ErrorBar) + hrseries1.ToString())
                //    {
                //        ChartType = SeriesChartType.ErrorBar,
                //        XValueType = ChartValueType.Int32,
                //        YValuesPerPoint = 3,
                //        MarkerSize = 3,
                //        MarkerStyle = MarkerStyle.None,
                //        Color = Color.FromArgb(121, 171, 231)
                //    };

                //    correctionLine["PointWidth"] = "0.1";

                //    double centerY = double.Parse(pWv[hrseries1]);
                //    if (stdDeviationSeries != null)
                //    {
                //        double lowerErrorY = centerY - double.Parse(stdDeviationSeries[hrseries1], CrxCommon.nCI);
                //        double upperErrorY = centerY + double.Parse(stdDeviationSeries[hrseries1], CrxCommon.nCI);
                //        correctionLine.Points.AddXY(hrseries1, centerY, lowerErrorY, upperErrorY);
                //    }

                //    trendChart.Series.Add(correctionLine);
                //}
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
            int numberOfLabel = maxValue - minValue + Convert.ToInt32(GuiCommon.NumericValue.One);

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
            int XInterval = Convert.ToInt32(GuiCommon.NumericValue.Ten); // this variable denotes the number by which x label interval would be calculated
        
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

                            if (i > Convert.ToInt32(GuiCommon.NumericValue.Zero))
                            {
                                // calculate midpoint between two x coordinates taking i as greater point index
                                int midPoint = int.Parse(xCoordinate[i].ToString()) -
                                               int.Parse(xCoordinate[i - Convert.ToInt32(GuiCommon.NumericValue.One)].ToString());
                                midPoint = midPoint / 2;
                                midPoint = midPoint + int.Parse(xCoordinate[i - Convert.ToInt32(GuiCommon.NumericValue.One)].ToString());

                                // if current x co-ordinates are greater than midpoint, display data for point index i else display for for i - 1
                                if (e.X > midPoint)
                                {
                                    // display data closest to datapoint at index i
                                    // bind the hear rate, pwv, datetime & standard deviation values from arrays as per point index
                                    guiradlblReportHeartRateValue.Text = heartRate[i] + " " +
                                                                         oMsgMgr.GetMessage(CrxStructCommonResourceMsg.HeartrateUnit);
                                    guiradlblReportPWVValue.Text = pWv[i] + " " + oMsgMgr.GetMessage(CrxStructCommonResourceMsg.PwvUnit);
                                    guiradlblStdDeviationImage.ImageIndex = int.Parse(isStdDeviationValid[i]);
                                    guiradlblPwvTimeValue.Text = pwvTime[i] + " " + oMsgMgr.GetMessage(CrxStructCommonResourceMsg.UnitsTimeMs);
                                    guiradlblReportDateTimeDisplay.Text = string.Format("{0:g}", Convert.ToDateTime(date[i]));
                                }
                                else
                                {
                                    // display data closest to datapoint at index i - 1
                                    // bind the hear rate, pwv, datetime & standard deviation values from arrays as per point index
                                    guiradlblReportHeartRateValue.Text = heartRate[i - Convert.ToInt32(GuiCommon.NumericValue.One)] + " " +
                                                                         oMsgMgr.GetMessage(CrxStructCommonResourceMsg.HeartrateUnit);
                                    guiradlblReportPWVValue.Text = pWv[i - Convert.ToInt32(GuiCommon.NumericValue.One)] + " " +
                                                                   oMsgMgr.GetMessage(CrxStructCommonResourceMsg.PwvUnit);
                                    guiradlblPwvTimeValue.Text = pwvTime[i - Convert.ToInt32(GuiCommon.NumericValue.One)] + " " + oMsgMgr.GetMessage(CrxStructCommonResourceMsg.UnitsTimeMs);
                                    guiradlblStdDeviationImage.ImageIndex =
                                        int.Parse(isStdDeviationValid[i - Convert.ToInt32(GuiCommon.NumericValue.One)]);
                                    guiradlblReportDateTimeDisplay.Text = string.Format("{0:g}", Convert.ToDateTime(date[i - 1]));
                                    pointSelected = i - Convert.ToInt32(GuiCommon.NumericValue.One);
                                }
                            }
                            else
                            {
                                // bind the hear rate, pwv & standar deviation values from arrays as per point index
                                guiradlblReportHeartRateValue.Text = heartRate[i] + " " +
                                                                     oMsgMgr.GetMessage(CrxStructCommonResourceMsg.HeartrateUnit);
                                guiradlblReportPWVValue.Text = pWv[i] + " " + oMsgMgr.GetMessage(CrxStructCommonResourceMsg.PwvUnit);
                                guiradlblPwvTimeValue.Text = pwvTime[i] + " " + oMsgMgr.GetMessage(CrxStructCommonResourceMsg.UnitsTimeMs);
                                
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
                if (((Setup)GuiCommon.SetupChildForm).ValidatePatientAge())
                {
                    if (DalModule.Instance.CheckIfDeviceIsConnected())
                    {
                        // on the click of this button navigate the user to the capture screen whenre he can recapture the waveforms.                
                        if (GuiCommon.CaptureChildForm != null)
                        {
                            GuiCommon.CaptureChildForm.Close();
                        }

                        GuiCommon.CaptureTabClick = false;
                        
                        GuiCommon.CaptureChildForm = new Capture(objDefaultWindow)
                        {
                              TopLevel = false,
                              Dock = DockStyle.Fill,
                              FormBorderStyle = FormBorderStyle.None
                        };

                        var page = objDefaultWindow.radtabCapture;
                        GuiCommon.CaptureChildForm.Parent = page;
                        page.Controls.Clear();

                        page.Controls.Add(GuiCommon.CaptureChildForm);
                        GuiCommon.CaptureChildForm.Show();

                        objDefaultWindow.radpgTabCollection.SelectedPage = objDefaultWindow.radtabCapture;
                        objDefaultWindow.radtabCapture.Enabled = true;

                        if (GuiCommon.ErrorInCaptureProcess)
                        {
                            GuiCommon.ErrorInCaptureProcess = false;

                            if (GuiCommon.CaptureChildForm != null)
                            {
                                GuiCommon.CaptureChildForm.ShowSetupAfterCaptureAbort();
                            }
                            else
                            {
                                GuiCommon.SetupChildForm.NavigateuserToSetupFromCaptureWhenStartCaptureFails();
                            }

                            objDefaultWindow.guicmbxCurrentMode.Enabled = true;
                        }
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
                else
                {
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
        private void GetXCoordinatesForChart(Series chartSeries)
        {
            try
            {
                xCoordinate = new int[chartSeries.Points.Count];
                double xValue = 0.0;
                int iCount = Convert.ToInt32(GuiCommon.NumericValue.Zero);
                foreach (DataPoint dp in chartSeries.Points)
                {
                    // get the pixel values corresponding to datapoint value for X
                    xValue = chartSelected == ChartName.Pwv ? guiradchartPulseWaveVelocity.ChartAreas[0].AxisX.ValueToPixelPosition(double.Parse(dp.XValue.ToString())) : guiradchartHeartRate.ChartAreas[0].AxisX.ValueToPixelPosition(double.Parse(dp.XValue.ToString()));

                    // add to array of x co-ordinates
                    xCoordinate[iCount] = int.Parse(Math.Round(xValue, MidpointRounding.ToEven).ToString());
                    iCount++;
                }
            }
            catch (Exception ex)
            {
                GUIExceptionHandler.HandleException(ex, this);
            }
        }

        /** This event customizes label display on PWV trend analysis chart
        * */
        private void guiradchart_Customize(object sender, EventArgs e)
        {
            try
            {
                int SeriesPoints = Convert.ToInt32(GuiCommon.NumericValue.Three);
                if (pWv != null)
                {
                    if (pWv.Length > SeriesPoints)
                    {
                        foreach (CustomLabel cl in guiradchartPulseWaveVelocity.ChartAreas[0].AxisX.CustomLabels)
                        {
                            cl.Text = DateTime.Parse(cl.Text).ToShortDateString() + Environment.NewLine + DateTime.Parse(cl.Text).ToShortTimeString();
                        }

                        foreach (CustomLabel cl in guiradchartHeartRate.ChartAreas[0].AxisX.CustomLabels)
                        {                           
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
         * Any exception will be handled by guiradgridReportAssessment_SelectionChanged Event
        * */
        private void DisplaySelectedRecords(int rowIndex, bool isChecked)
        {
            try
            {
                int recordSelected = Convert.ToInt32(GuiCommon.NumericValue.Zero);
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

                // display analysis / report screen based on records selected
                DisplayReportOnSelection(recordSelected, dateWithComma);
            }
            catch (Exception ex)
            {
                throw (ex);
            }
        }

        /** This method binds data to report screen as per the selected assesment
         * Any exception will be handled by guiradgridReportAssessment_SelectionChanged Event
        * */
        private void DisplayReportForSelectedAssesment(string dateTime)
        {
            try
            {
                InitializeCrxOnLoad(dateTime);
                FillPWVMeasurementDetailsReport();

                SuperImposedWaveForm();
                CheckAgeLimit(GuiCommon.bizObject.patientAge);
                PlotNormalRangeGraph();
                PlotReferenceRangeGraph();
            }
            catch (Exception ex)
            {
                throw (ex);
            }
        }

        /** This method subscribes all the text boxes & drop down for changes made to it.
        * To the form changed event which will determine for any changes made before application is closed
        * */
        private void SubscribeReportFormChanges()
        {
            try
            {
                // subscribe key press events for measurement fields to allow numeric values
                guiradtxtCarotid.KeyPress += GuiCommon.CheckForNumericValues;
                guiradtxtReportCuff.KeyPress += GuiCommon.CheckForNumericValues;
                guiradtxtReportFemoToCuff.KeyPress += GuiCommon.CheckForNumericValues;
                guiradtxtReportHeight.KeyPress += GuiCommon.CheckForNumericValues;
                guiradtxtReportHeightInches.KeyPress += GuiCommon.CheckForNumericValues;
                guiradtxtReportBloodPressure1.KeyPress += GuiCommon.CheckForNumericValues;
                guiradtxtReportBloodPressure2.KeyPress += GuiCommon.CheckForNumericValues;
            }
            catch (Exception ex)
            {
                GUIExceptionHandler.HandleException(ex, this);
            }
        }

        /** This event disables right click on assessment grid
        * */
        private void guiradgridReportAssessment_ContextMenuOpening(object sender, ContextMenuOpeningEventArgs e)
        {
            try
            {
                e.Cancel = true;
            }
            catch (Exception ex)
            {
                GUIExceptionHandler.HandleException(ex, this);
            }
        }

        /**This method is used to check if the timer on the Setup screen is still active or not.
        * The timer is used to impose a wait time after the user navigates away from the Capture screen.
        */
        private void CheckWaitIntervalImposed()
        {
            try
            {
                if (GuiCommon.IsWaitIntervalImposed)
                {
                    objDefaultWindow.radtabCapture.Enabled = false;
                    guiradbtnRepeat.Enabled = false;
                }
                else
                {
                    if (guiradgridReportAssessment.Rows.Count > Convert.ToInt32(GuiCommon.NumericValue.Zero))
                    {
                        objDefaultWindow.radtabCapture.Enabled = true;
                    }
                    else
                    {
                        objDefaultWindow.radtabCapture.Enabled = false;
                    }

                    guiradbtnRepeat.Enabled = true;
                }
            }
            catch (Exception ex)
            {
                GUIExceptionHandler.HandleException(ex, this);
            }
        }

        /** This event fires when mouse is hovered over Heart trend chart
         * It sets the chart type which helps in determining which chart datapoints are hovered over
         * */
        private void guiradchartHeartRate_MouseMove(object sender, MouseEventArgs e)
        {
            try
            {
                chartSelected = ChartName.HeartRate;
            }
            catch (Exception ex)
            {
                GUIExceptionHandler.HandleException(ex, this);
            }
        }       

        /** This event fires when mouse is hovered over PWV chart
        * It sets the chart type which helps in determining which chart datapoints are hovered over
        * */
        private void guiradchartPulseWaveVelocity_MouseMove(object sender, MouseEventArgs e)
        {
            try
            {
                chartSelected = ChartName.Pwv;
            }
            catch (Exception ex)
            {
                GUIExceptionHandler.HandleException(ex, this);
            }
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
         * Any exception will be handled by guiradgridReportAssessment_SelectionChanged Event
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
            try
            {
                objValidateReport.CheckFieldLimits(guiradtxtReportBloodPressure1);
                guipnlPatientDetails.Refresh();
            }
            catch (Exception ex)
            {
                GUIExceptionHandler.HandleException(ex, this);
            }
        }

        /** This event gets fired when focus is moved from text box which takes SP/Dp/Mp value.
        * It checks if the value entered in textbox is within valid range and shows error accordingly
        * */
        private void guiradtxtReportBloodPressure2_Leave(object sender, EventArgs e)
        {
            try
            {
                objValidateReport.CheckFieldLimits(guiradtxtReportBloodPressure2);
                guipnlPatientDetails.Refresh();
            }
            catch (Exception ex)
            {
                GUIExceptionHandler.HandleException(ex, this);
            }
        }

        /** This event gets fired when focus is moved from text box which takes cuff / direct values.
        * It checks if the value entered in textbox is within valid range and shows error accordingly
        * */
        private void guiradtxtReportCuff_Leave(object sender, EventArgs e)
        {
            try
            {
                objValidateReport.CheckFieldLimits(guiradtxtReportCuff);
                guipnlPatientDetails.Refresh();
            }
            catch (Exception ex)
            {
                GUIExceptionHandler.HandleException(ex, this);
            }
        }

        /** This event gets fired when focus is moved from text box which takes femoral to cuff values.
        * It checks if the value entered in textbox is within valid range and shows error accordingly
        * */
        private void guiradtxtReportFemoToCuff_Leave(object sender, EventArgs e)
        {
            try
            {
                objValidateReport.CheckFieldLimits(guiradtxtReportFemoToCuff);
                guipnlPatientDetails.Refresh();
            }
            catch (Exception ex)
            {                  
             GUIExceptionHandler.HandleException(ex, this);
            }
        }

        /** This event gets fired when focus is moved from text box which takes height in cm || height in feet values.
        * It checks if the value entered in textbox is within valid range and shows error accordingly
        * */
        private void guiradtxtReportHeight_Leave(object sender, EventArgs e)
        {
            try
            {
                objValidateReport.CheckIntegerFieldLimitsRemoveInvalidValue(guiradtxtReportHeight);
                guipnlPatientDetails.Refresh();
            }
            catch (Exception ex)
            {
                GUIExceptionHandler.HandleException(ex, this);
            }
        }

        /** This event gets fired when focus is moved from text box which takes height in inches values.
        * It checks if the value entered in textbox is within valid range and shows error accordingly
        * */
        private void guiradtxtReportHeightInches_Leave(object sender, EventArgs e)
        {
            try
            {
                objValidateReport.CheckIntegerFieldLimitsRemoveInvalidValue(guiradtxtReportHeightInches);
                guipnlPatientDetails.Refresh();
            }
            catch (Exception ex)
            {
                GUIExceptionHandler.HandleException(ex, this);
            }
        }
        

        /** This event gets fired when focus is moved from text box which takes carotid values.
        * It checks if the value entered in textbox is within valid range and shows error accordingly
        * */
        private void guiradtxtCarotid_Leave(object sender, EventArgs e)
        {
            try
            {
                objValidateReport.CheckFieldLimits(guiradtxtCarotid);
                guipnlPatientDetails.Refresh();
            }
            catch (Exception ex)
            {
                GUIExceptionHandler.HandleException(ex, this);
            }
        }

        /**This method is called to check if the specified patient's date in within the specified range or not.
         * Any exception will be handled by FillPatientAssessmentDetailsReport Function
        */
        private void CheckAgeLimit(int age)
        {
            try
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
            catch (Exception ex)
            {
                throw (ex);
            }
        }

        /** This method fille structure "PWVReportData" with the values to be printed on PWV report.
        * This values will be used in Crystal Reports.
        * */
        private void FillStructForPWVReport()
        {
            try
            {
                PWVReportData.RptHeader = string.IsNullOrEmpty(crxMgrObject.GeneralSettings.ReportTitle) ? BizInfo.Instance().GetCompanyName().Replace("(R)", "\u00AE") : crxMgrObject.GeneralSettings.ReportTitle.Replace("(R)", "\u00AE");
                PWVReportData.RptPatientAge = guiradlblReportAge.Text;
                PWVReportData.RptPatientAgeValue = GuiCommon.bizObject.patientAge.ToString();
                PWVReportData.RptPatientAssessment = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.LblReportAssessment);
                PWVReportData.RptPatientAssessmentValue = string.Format("{0:g}", Convert.ToDateTime(GuiCommon.PwvCurrentStudyDatetime));
                PWVReportData.RptPatientBP = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.LblReportBp);
                PWVReportData.RptPatientBPValue = SetBPForPWVReport();
                PWVReportData.RptPatientCarotid = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.LblReportRecordedCarotid);
                PWVReportData.RptPatientData = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.LblReportPatientData);
                PWVReportData.RptPatientDistance = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.LblReportDiatance);
                PWVReportData.RptPatientDistanceValue = string.Format("{0} {1}", GuiCommon.bizObject.calculatedDistance.ToString(), (CrxConfigManager.Instance.PwvSettings.PWVDistanceUnits.Equals(0) ? oMsgMgr.GetMessage(CrxStructCommonResourceMsg.Mm) : oMsgMgr.GetMessage(CrxStructCommonResourceMsg.Cm)));
                PWVReportData.RptPatientDob = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.LblReportDob);
                PWVReportData.RptPatientDobValue = patientObj.dateOfBirth.ToString(oMsgMgr.GetMessage(CrxStructCommonResourceMsg.ReportDateTimeFormat));
                PWVReportData.RptPatientFemoral = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.LblReportRecordedFemoral);
                PWVReportData.RptPatientGender = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.LblReportGender);
                PWVReportData.RptPatientGenderValue = patientObj.gender.Equals(CrxStructCommonResourceMsg.MaleTxt) ? oMsgMgr.GetMessage(CrxStructCommonResourceMsg.MaleTxt) : oMsgMgr.GetMessage(CrxStructCommonResourceMsg.FemaleTxt);
                PWVReportData.RptPatientGeneralPop = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.LblReportReferenceRange);
                PWVReportData.RptPatientHealthyPop = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.LblReportNormalRange);
                PWVReportData.RptPatientHeartRate = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.LblReportHR);
                PWVReportData.RptPatientHeartRateValue = string.Format("{0} {1}", GuiCommon.bizObject.meanHeartRate.ToString("#0"), oMsgMgr.GetMessage(CrxStructCommonResourceMsg.HeartrateUnit));
                PWVReportData.RptPatientHeight = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.LblHeight);
                PWVReportData.RptPatientHeightValue = SetHeightForReportPrint();
                PWVReportData.RptPatientId = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.LblPatientId);
                PWVReportData.RptPatientIdValue = patientObj.patientId;
                PWVReportData.RptPatientName = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.LblPatientName);
                PWVReportData.RptPatientNameValue = string.IsNullOrEmpty(patientObj.firstName) ? patientObj.lastName : string.Format("{0} {1}", patientObj.firstName, patientObj.lastName);
                PWVReportData.RptPatientNotes = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.LblNotes);
                PWVReportData.RptPatientNotesValue = GuiCommon.bizObject.notes;
                PWVReportData.RptPatientOperation = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.LblOperator);
                PWVReportData.RptPatientOperationValue = GuiCommon.bizObject.operatorId;
                PWVReportData.RptPatientPwv = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.LblReportPwvLbl);
                PWVReportData.RptPatientPwvValue = string.Format("{0} {1}", GuiCommon.bizObject.meanPulseWaveVelocity.ToString("#0.0"), oMsgMgr.GetMessage(CrxStructCommonResourceMsg.PwvUnit));
                PWVReportData.RptPatientStdDev = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.LblReportStdLbl);
                PWVReportData.RptStudyData = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.LblReportStudyData);
                PWVReportData.RptGeneralPopulation = crxMgrObject.PwvSettings.ReferenceRange;
                PWVReportData.RptHealthyPopulation = crxMgrObject.PwvSettings.NormalRange;
            }
            catch (Exception ex)
            {
                throw (ex);
            }
        }

        /** This method fille structure "PWVPatientReportData" with the values to be printed on PWV Patient report.
        * This values will be used in Crystal Reports.
        * */
        private void FillStructForPWVPatientReport()
        {
            try
            {
                PWVPatientReportData.RptPatientAge = guiradlblReportAge.Text;
                PWVPatientReportData.RptPatientAgeValue = GuiCommon.bizObject.patientAge.ToString();
                PWVPatientReportData.RptPatientBP = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.LblReportBp);
                PWVPatientReportData.RptPatientBPValue = SetBPForPWVReport();

                PWVPatientReportData.RptPatientGender = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.LblReportGender);
                PWVPatientReportData.RptPatientGenderValue = patientObj.gender;
                PWVPatientReportData.RptPatientNameValue = string.IsNullOrEmpty(patientObj.firstName) ? patientObj.lastName : string.Format("{0} {1}", patientObj.firstName, patientObj.lastName);
                PWVPatientReportData.RptPatientId = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.LblPatientId);
                PWVPatientReportData.RptPatientIdValue = patientObj.patientId;
                PWVPatientReportData.RptPatientPwv = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.LblReportPwvLbl);
                PWVPatientReportData.RptPatientPwvValue = string.Format("{0} {1}", GuiCommon.bizObject.meanPulseWaveVelocity.ToString("#0.0"), oMsgMgr.GetMessage(CrxStructCommonResourceMsg.PwvUnit));
                PWVPatientReportData.RptPatientHeight = SetHeightForReportPrint();

                PWVPatientReportData.RptGeneralPopulation = crxMgrObject.PwvSettings.ReferenceRange;
                PWVPatientReportData.RptHealthyPopulation = crxMgrObject.PwvSettings.NormalRange;
            }
            catch (Exception ex)
            {
                throw (ex);
            }
        }

        /** This method sets BP value for showing in PWV report when it is printed
        * */
        private string SetBPForPWVReport()
        {
            string blpValue = string.Empty;
            try
            {
                if (!((GuiCommon.bizObject.bloodPressure.DP.Reading.Equals(GuiConstants.DefaultValue) && GuiCommon.bizObject.bloodPressure.MP.Reading.Equals(GuiConstants.DefaultValue)) || (GuiCommon.bizObject.bloodPressure.SP.Reading.Equals(GuiConstants.DefaultValue) && GuiCommon.bizObject.bloodPressure.DP.Reading.Equals(GuiConstants.DefaultValue)) || (GuiCommon.bizObject.bloodPressure.SP.Reading.Equals(GuiConstants.DefaultValue) && GuiCommon.bizObject.bloodPressure.MP.Reading.Equals(GuiConstants.DefaultValue))))
                {
                    blpValue = GuiCommon.bizObject.bloodPressure.SP.Reading.ToString() + oMsgMgr.GetMessage(CrxStructCommonResourceMsg.GuiDisplaySlash) + GuiCommon.bizObject.bloodPressure.DP.Reading.ToString() + " " + oMsgMgr.GetMessage(CrxStructCommonResourceMsg.UnitsPressureMmhg);
                }
            }
            catch (Exception ex)
            {
                GUIExceptionHandler.HandleException(ex, this);
            }
            return blpValue;
        }

        /** This event fires on any key down on report screen. It suppresses space bar on assessment gridview as pressing space bar when focus is on gridview
        * allows selecting / deselecting assessments
        */
        private void Report_KeyDown(object sender, KeyEventArgs e)
        {
            try
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
            catch (Exception ex)
            {
                GUIExceptionHandler.HandleException(ex, this);
            }
        }

        /** This method sets height for passing it to the crystal report for print reports
        */
        private string SetHeightForReportPrint()
        {
            string height = string.Empty;
            try
            {
                switch (CrxConfigManager.Instance.GeneralSettings.HeightandWeightUnit)
                {
                    case (int)CrxGenPwvValue.CrxGenHeightWeightMetric:
                        height = GuiCommon.bizObject.heightAndWeight.heightInCentimetres.Equals(GuiConstants.DefaultValue) ? string.Empty : (GuiCommon.bizObject.heightAndWeight.heightInCentimetres.ToString() + " " + oMsgMgr.GetMessage(CrxStructCommonResourceMsg.Cm));
                        break;
                    case (int)CrxGenPwvValue.CrxGenHeightWeightImperial:

                        if (GuiCommon.bizObject.heightAndWeight.heightInInches != GuiConstants.DefaultValue)
                        {
                            // convert height in inches to feet & inches
                            int heightInInches = int.Parse(GuiCommon.bizObject.heightAndWeight.heightInInches.ToString()) % 12;
                            int heigthInFeet = int.Parse(GuiCommon.bizObject.heightAndWeight.heightInInches.ToString()) / 12;

                            height = string.Format("{0}{1}{2} {3}{4}", heigthInFeet.ToString(), oMsgMgr.GetMessage(CrxStructCommonResourceMsg.Feet), oMsgMgr.GetMessage(CrxStructCommonResourceMsg.GuiDisplayComma), heightInInches.ToString(), oMsgMgr.GetMessage(CrxStructCommonResourceMsg.UnitsDistanceInch));
                        }

                        break;
                    default:
                        break;
                }
            }
            catch (Exception ex)
            {
                GUIExceptionHandler.HandleException(ex, this);
            }
            return height;
        }
      
        /** This method prints Patient PWV report
        */
        private void guiPrintPatientReport_Click_1(object sender, EventArgs e)
        {
            try
            {
                FillStructForPWVPatientReport();
                PWVReportData.RptReportType = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.GuiSettingsPwvPatientReport);

                StringBuilder sbRange = new StringBuilder(string.Empty);

                // refValue array contains all reference data required for the report 
                BizBpRefValue[] refValue = GuiCommon.bizObject.GetBpRefRange(GuiCommon.bizObject.patientAge);

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
            catch (Exception ex)
            {
                GUIExceptionHandler.HandleException(ex, this);
            }
        }

        /** This method prints PWV report as per the report screen
        * */       
        private void guiprintPwvReport_Click(object sender, EventArgs e)
        {
            try
            {
                FillStructForPWVReport();
                PWVReportData.RptReportType = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.GuiSettingsPwvReport);
                ReportPreview rpPreview = new ReportPreview();
                rpPreview.Show();
            }
            catch (Exception ex)
            {
                GUIExceptionHandler.HandleException(ex, this);
            }
        }        
        
        /**This event is fired when the user releases the keyboard key after pressing it.
        * Here we change the focus from on control to another.
        */ 
        private void Report_KeyUp(object sender, KeyEventArgs e)
        {
            try
            {
                const string ControlName = "";
                if (e.KeyCode == Keys.Tab && ((Report)sender).ActiveControl.Name.Equals(ControlName))
                {
                    if (objDefaultWindow.radtabReport.Text.Equals(oMsgMgr.GetMessage(CrxStructCommonResourceMsg.TabAnalysis)))
                    {
                        guiradlblReportAssessments.Focus();
                    }
                    else
                    {
                        guiradbtnreportedit.Focus();
                    }
                }
            }
            catch (Exception ex)
            {
                GUIExceptionHandler.HandleException(ex, this);
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
            shape.Radius = Convert.ToInt32(GuiCommon.NumericValue.Five);

            foreach (Control control in labelControl)
            {
                RadLabel label = control as RadLabel;
                if (label != null)
                {
                    label.RootElement.BackColor = Color.Transparent;
                    ((FillPrimitive)label.LabelElement.Children[0]).NumberOfColors = Convert.ToInt32(GuiCommon.NumericValue.One);
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
            try
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
            catch (Exception ex)
            {
                GUIExceptionHandler.HandleException(ex, this);
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
            try
            {
                e.Graphics.DrawRectangle(
                Pens.Black,
                e.ClipRectangle.Left,
                e.ClipRectangle.Top,
                e.ClipRectangle.Width - Convert.ToInt32(GuiCommon.NumericValue.One),
                e.ClipRectangle.Height - Convert.ToInt32(GuiCommon.NumericValue.One));
                OnPaint(e);
            }
            catch (Exception ex)
            {
                GUIExceptionHandler.HandleException(ex, this);
            }
        }

        /** This event is used to set the alternate color for the assessment grid's records.
        */ 
        private void guiradgridReportAssessment_RowFormatting(object sender, RowFormattingEventArgs e)
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
            catch (Exception ex)
            {
                GUIExceptionHandler.HandleException(ex, this);
            }
        }

        /**This method is fired when row selection is changes in the assessments grid.
        */ 
        private void guiradgridReportAssessment_SelectionChanged(object sender, EventArgs e)
        {
            try
            {
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
            guiradlblReportBpRange.Visible = false;
            ReportPWVDisplayMode(true);            
        }

        /**This method is used to calculate PWv distance for Subtraction method.
         * Any exception will be handeld by guiradbtnreportsave_Click Event
        */
        private void CalculatePwvDistanceForSubtractionMethod()
        {
            if ((guiradtxtCarotid.Text.Length > Convert.ToInt32(GuiCommon.NumericValue.Zero)) && (guiradtxtReportCuff.Text.Length > Convert.ToInt32(GuiCommon.NumericValue.Zero)))
            {
                 GuiCommon.bizObject.myPWVDirectDistance.distance = GuiConstants.DefaultValue;
                 GuiCommon.bizObject.myCarotidDistance.distance = (crxMgrObject.PwvSettings.PWVDistanceUnits.Equals((int)CrxGenPwvValue.CrxPwvDistDistUnitsCM)) ? (ushort)(ushort.Parse(guiradtxtCarotid.Text.Trim()) * GuiConstants.DivisionFactor) : ushort.Parse(guiradtxtCarotid.Text.Trim());
                 GuiCommon.bizObject.myCuffDistance.distance = (crxMgrObject.PwvSettings.PWVDistanceUnits.Equals((int)CrxGenPwvValue.CrxPwvDistDistUnitsCM)) ? (ushort)(ushort.Parse(guiradtxtReportCuff.Text.Trim()) * GuiConstants.DivisionFactor) : ushort.Parse(guiradtxtReportCuff.Text.Trim());
                if (guiradtxtReportFemoToCuff.Text.Trim().Equals(string.Empty))
                {
                    GuiCommon.bizObject.myFemoral2CuffDistance.distance = Convert.ToUInt16(GuiCommon.NumericValue.Zero);
                }
                else
                {
                     GuiCommon.bizObject.myFemoral2CuffDistance.distance = (crxMgrObject.PwvSettings.PWVDistanceUnits.Equals((int)CrxGenPwvValue.CrxPwvDistDistUnitsCM)) ? (ushort)(ushort.Parse(guiradtxtReportFemoToCuff.Text.Trim()) * GuiConstants.DivisionFactor) : ushort.Parse(guiradtxtReportFemoToCuff.Text.Trim());
                }
            }
        }

        /**This method is used to calculate PWV Distance for Direct method.
         * Any exception will be handeld by guiradbtnreportsave_Click Event
        */        
        private void CalculatePwvDistanceForDirectMethod()
        {
            if ((guiradtxtCarotid.Text.Length > Convert.ToInt32(GuiCommon.NumericValue.Zero)))
            {
                 GuiCommon.bizObject.myPWVDirectDistance.distance = (crxMgrObject.PwvSettings.PWVDistanceUnits.Equals((int)CrxGenPwvValue.CrxPwvDistDistUnitsCM)) ? (ushort)(ushort.Parse(guiradtxtCarotid.Text.Trim()) * GuiConstants.DivisionFactor) : ushort.Parse(guiradtxtCarotid.Text.Trim());
                 GuiCommon.bizObject.myCarotidDistance.distance = GuiConstants.DefaultValue;
                 GuiCommon.bizObject.myCuffDistance.distance = GuiConstants.DefaultValue;
                if (guiradtxtReportFemoToCuff.Text.Trim().Equals(string.Empty))
                {
                    GuiCommon.bizObject.myFemoral2CuffDistance.distance = Convert.ToUInt16(GuiCommon.NumericValue.Zero);
                }
                else
                {
                     GuiCommon.bizObject.myFemoral2CuffDistance.distance = (crxMgrObject.PwvSettings.PWVDistanceUnits.Equals((int)CrxGenPwvValue.CrxPwvDistDistUnitsCM)) ? (ushort)(ushort.Parse(guiradtxtReportFemoToCuff.Text.Trim()) * GuiConstants.DivisionFactor) : ushort.Parse(guiradtxtReportFemoToCuff.Text.Trim());
                }
            }
        }        

        /**This method is used to check if the report is generate in the Simulation mode or not.
        * If it is generated in Simulation mode then display appropiate message in the message alert area.
        */ 
        private void CheckForSimualtionMode()
        {
            if (!(numeberOfRecordsSelected > Convert.ToInt32(GuiCommon.NumericValue.One)))
            {
                if (crxMgrObject.GeneralSettings.CommsPort.Equals(oMsgMgr.GetMessage(CrxStructCommonResourceMsg.Simulation).ToUpper()) && guiradgridReportAssessment.Rows.Count > Convert.ToInt32(GuiCommon.NumericValue.Zero))
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

            for (int i = Convert.ToInt32(GuiCommon.NumericValue.Zero); i < sortArr.Length; i++)
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

            for (int i = Convert.ToInt32(GuiCommon.NumericValue.Zero); i < sortArr.Length; i++)
            {
                bpSort[i] = Convert.ToString(sortArr[i]);
            }

            return bpSort;
        }        

        private void guiradtxtReportCuff_TextChanged(object sender, EventArgs e)
        {
            try
            {
                if (!guiradbtnreportedit.Visible)
                {
                    isValueChanged = true;
                }
            }
            catch (Exception ex)
            {
                GUIExceptionHandler.HandleException(ex, this);
            }
        }

        private void guiradtxtCarotid_TextChanged(object sender, EventArgs e)
        {
            try
            {
                if (!guiradbtnreportedit.Visible)
                {
                    isValueChanged = true;
                }
            }
            catch (Exception ex)
            {
                GUIExceptionHandler.HandleException(ex, this);
            }
        }

        private void guiradtxtReportFemoToCuff_TextChanged(object sender, EventArgs e)
        {
            try
            {
                if (!guiradbtnreportedit.Visible)
                {
                    isValueChanged = true;
                }
            }
            catch (Exception ex)
            {
                GUIExceptionHandler.HandleException(ex, this);
            }
        }

        private void guiradtxtReportBloodPressure1_TextChanged(object sender, EventArgs e)
        {
            try
            {
                if (!guiradbtnreportedit.Visible)
                {
                    isValueChanged = true;
                }
            }
            catch (Exception ex)
            {
                GUIExceptionHandler.HandleException(ex, this);
            }
        }

        private void guiradtxtReportBloodPressure2_TextChanged(object sender, EventArgs e)
        {
            try
            {
                if (!guiradbtnreportedit.Visible)
                {
                    isValueChanged = true;
                }
            }
            catch (Exception ex)
            {
                GUIExceptionHandler.HandleException(ex, this);
            }
        }

        private void guiradtxtReportHeight_TextChanged(object sender, EventArgs e)
        {
            try
            {
                if (!guiradbtnreportedit.Visible)
                {
                    isValueChanged = true;
                }
            }
            catch (Exception ex)
            {
                GUIExceptionHandler.HandleException(ex, this);
            }
        }

        private void guiradtxtReportHeightInches_TextChanged(object sender, EventArgs e)
        {
            try
            {
                if (!guiradbtnreportedit.Visible)
                {
                    isValueChanged = true;
                }
            }
            catch (Exception ex)
            {
                GUIExceptionHandler.HandleException(ex, this);
            }
        }
    }
}