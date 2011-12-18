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
using System.Configuration;

namespace AtCor.Scor.Gui.Presentation
{
    public partial class PWAReport : RadForm
    {           
        readonly string serverNameString = string.Empty;
        readonly BizPatient patientObj = BizPatient.Instance();
        const int MaxLabelYValue = 12; // this denotes the maximum number of values to be displayed on Y axis so that it does not overlap                      
        const int LblVerticalAngle = -90; // angle of labels to display vertically on analysis screen when more records are are selected
        const int LblHorizontalAngle = 0; // angle of labels to display horizontally on analysis screen when few records are are selected
        const string CulturalNeutralDateFormat = "yyyy-MM-dd HH:mm:ss"; // this is a cultural neutral format used for fetching data for different regional settings from back end
        const int MaxNumberOfPointsForChart = 30; // This is used to set maximum number of points which can be displayed at any given time for PWV ananlysis chart.
        decimal averageAorticXAxisInterval = Math.Round((decimal)(1000.0 / 256.0));
        string dfBPVlaue = GuiConstants.SdefaultValue.ToString();

        // Events              
        // Using the same event as that of PWV for showing values on the Setup screen for PWA mode.   
        public static event EventHandler OnPwaMeasurementChangedEvent;
        
        GuiFieldValidation objValidation;
        CrxMessagingManager oMsgMgr;
        CrxConfigManager crxMgrObject;
        CrxDBManager dbMagr;
        private bool isValueChanged = false;
        private bool isHeightOutsideIntegerLimits = false;

        CrxStructPWAMeasurementData crxPwaData = new CrxStructPWAMeasurementData();
        CrxStructCuffPWAMeasurementData crxPwaCuffData = new CrxStructCuffPWAMeasurementData();
        CrxStructTonoPWAMeasurementData crxPwaTonoData = new CrxStructTonoPWAMeasurementData();
        int bobj;
        int numeberOfRecordsSelected;
        string dateToCompare = string.Empty; // used to compare dates when 30 sec wait interval is imposed to enable / disable repeat button based on last record selected
        string dateWithComma = string.Empty;
        string pwaIdWithComma = string.Empty;
        int recordsToDelete; // this variable holds value for number of records to delete and is used across dfifferent methods 
        string lastAssessmentDate = string.Empty;
        string pwaIdToCompare = string.Empty; // used to compare Pwa id when 30 sec wait interval is imposed to enable / disable repeat button based on last record selected
        string lastAssessmentPwaId = string.Empty;
        private DefaultWindow objDefaultWindow;     
        
        string[] date; // date array to be used on analysis screen
        bool isFromLoad = false; // This variable is used to denote wether call to method PopulateBizFromCrx is made on load of report or when assesment is selected
        string[] apRate; // Ap rate array to be used on analysis screen
        string[] hrRate; // Hr rate array to be used on analysis screen
        string[] spRate; // Sp rate array to be used on analysis screen
        string[] dpRate; // Dp rate array to be used on analysis screen
        string[] mpRate; // Mp rate array to be used on analysis screen
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
                // DefaultWindow.OnExitSavePwaReportChanges += guiradbtnreportsave_Click;                
                // DefaultWindow.OnReportTabClick += PWAReport_Load;                
                // DefaultWindow.OnPwaReportMenuItemClick += SaveChangesOnMenuFocus;                
                // Presentation.Capture.OnPWAReportTabClick += PWAReport_Load;                
                // GuiCommon.OnCaptureClosing += EnableRepeatAndCaptureTab;
                guiradtxtReportHeightInches.KeyPress += GuiCommon.CheckForNumericValues;
                guiradtxtReportHeight.KeyPress += GuiCommon.CheckForNumericValues;
                
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
                GuiCommon.CaptureToSetup = !value;

                // Disble the capture tab if the quickstart mode is on.
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
            objDefaultWindow.radtabResult.Enabled = false; 
            GuiCommon.IsOnPwaReportForm = true;
            GuiCommon.FromPwaReport = true;
            bobj = GuiConstants.SystemId;
            GuiCommon.CaptureToSetup = false;
            GuiCommon.SystemIdentifier = bobj;
            GuiCommon.ReportLoadCount++;

            // AtCor-Drop2-Sprint1
            SetTextForPWAReport();

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

            if (!string.IsNullOrEmpty(GuiCommon.InConclusiveMessageForPwaCapture))
            {
                guiradlblInconclusiveMessage.Text = string.Format("{0} {1}", CrxMessagingManager.Instance.GetMessage(CrxStructCommonResourceMsg.GuiInConclusivePwaReportInitialMesg), GuiCommon.InConclusiveMessageForPwaCapture);
            }

            DisableRepeatButtonForQuickStartMode();
        }

        /** This event fires when user tries to navigate to top menu tabs on report screen
         * It prompts user to save changes if user is in edit mode and accordingly navigates to top menu
         */

        // private void SaveChangesOnMenuFocus(object sender, EventArgs e)
        public void SaveChangesOnMenuFocus()
        {
            // GuiCommon.IsMenuItemShown = true;
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
                            SetPWADsiplayMode();
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

        public void SaveChangesOnEdit()
        {
            try
            {
                objDefaultWindow.radlblMessage.Text = string.Empty;
                objDefaultWindow.guiradmnuDatabase.Enabled = true;

                // check db connection
                if (dbMagr.CheckConnection(serverNameString, crxMgrObject.GeneralSettings.SourceData) == 0)
                {
                    // save PWA details in database and session object

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
                            GuiCommon.IsMenuItemShown = true;
                            isValueChanged = false;
                            GuiCommon.IsFormChanged = false;
                            break;
                        case (int)InitializeCrxValue.ValidationFailed:
                            if (!isHeightOutsideIntegerLimits)
                            {
                                RadMessageBox.Show(this, oMsgMgr.GetMessage(CrxStructCommonResourceMsg.ErrorValidating), oMsgMgr.GetMessage(CrxStructCommonResourceMsg.SystemError), MessageBoxButtons.OK, RadMessageIcon.Error);
                            }

                            PopulateBizFromCrx(pwaIdToCompare);
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

                GuiCommon.ExitApp = GuiCommon.IsMenuItemShown ? 0 : 1;
                CheckForSimualtionMode();
            }
            catch (Exception ex)
            {
                GUIExceptionHandler.HandleException(ex, this);
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
            guiPwaPatientReport.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.PwaPatientReport);
            guiradlblReportDOB.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.LblReportDob);
            guiradlblReportAge.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.LblReportAge);
            guiradlblReportheightWeight.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.LblHeight);
            guiradlblReportOperator.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.LblOperator);
            guiradlblInconclusiveMessage.Text = String.Empty;

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
            guiradlblSphygmocorReferenceAge.Text = String.Format("{0}{1}", oMsgMgr.GetMessage(CrxStructCommonResourceMsg.LblPwaSyphymocorRefAge), " > " + Math.Round(GuiCommon.bizPwaobject.ReferenceAge).ToString());
            guiradlblAixNotCalc.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.LblReportPwaNotCalculated);
            guiradlblApNotCalc.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.LblReportPwaNotCalculated);
            guiradlblPpNotCalc.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.LblReportPwaNotCalculated);
            guiradlblSpNotCalc.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.LblReportPwaNotCalculated);
            if (GuiCommon.bizPwaobject.ReferenceAge == GuiConstants.DefaultValue)
            {
                guiradlblSphygmocorReferenceAge.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.LblSphygmoCorReferenceAgeNotCalculated);
            }

            guioradlblAvgCentralAortlcPulse.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.LblAvgCentralAorticPulse);
            guiradlblQualityControl.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.LblPwaQualityControl);
            slashlabel.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.GuiDisplaySlash);
            guiradlblReportDPUnits.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.UnitsPressureMmhg);
            guiradlblInterpretation.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.LblPwaInterpretation);
            guiradlblReportGender.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.LblReportGender);

            // guiradbtnPrint.DefaultItem = guiPwaClinicalReport;
            guiradbtnPrint.DefaultItem = crxMgrObject.PwaSettings.DefaultReport.Equals(CrxStructCommonResourceMsg.PwaClinicalReport) ? guiPwaClinicalReport : guiPwaPatientReport;
        }

        private void InitializeReportScreenPWA()
        {
            dbMagr = CrxDBManager.Instance;
            oMsgMgr = CrxMessagingManager.Instance;
            crxMgrObject = CrxConfigManager.Instance;        
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
                    isFromLoad = false;
                    objDefaultWindow.guiradgrpbxPwvDistanceMethod.Enabled = true;
                    objDefaultWindow.guicmbxCurrentMode.Enabled = true;
                    if (ds.Tables[0].Rows.Count > 0)
                    {
                        lastAssessmentPwaId = pwaIdToCompare = ds.Tables[0].Rows[0]["PWA_Id"].ToString();
                        pwaIdWithComma = ds.Tables[0].Rows[0]["PWA_Id"].ToString() + oMsgMgr.GetMessage(CrxStructCommonResourceMsg.GuiDisplayComma);
                       
                        guiradgridReportAssessment.DataSource = ds.Tables[0];
                        guiradbtnreportedit.Enabled = true;

                        // sets assessment count for a label                        
                        GuiCommon.HasMeasurementDetails = true;
                        guiradbtnDelete.Enabled = true;
                        guiradbtnPrint.Enabled = true;
                        guiradbtnRepeat.Enabled = true;
                        objDefaultWindow.radtabReport.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.TabReport);
                        recordsToDelete = 1;
                        dateWithComma = DateTime.Parse(guiradgridReportAssessment.MasterTemplate.Rows[ds.Tables[0].Rows.Count - 1].Cells[0].Value.ToString()).ToString(CulturalNeutralDateFormat) + oMsgMgr.GetMessage(CrxStructCommonResourceMsg.GuiDisplayComma);
                        
                        // if (!GuiCommon.SetupToReport)
                        // {
                        //    // this will populate biz session obj from latest PWA details
                        //    InitializeCrxOnLoad(guiradgridReportAssessment.MasterTemplate.Rows[ds.Tables[0].Rows.Count - 1].Cells["PWA_Id"].Value.ToString());
                        // }                       
                        GuiCommon.SetupToReport = false;

                        if (ds.Tables[0].Rows.Count == 1)
                        {
                            guipnlPWAReport.Visible = true;
                            guipnlPWAReportAnalysis.Visible = false;
                        }

                        FillPWAMeasurementDetailsReport();
                        DisplayClinicalParameterSliders();
                        PlotAvgAorticPulseChart();
                    }
                    else
                    {
                        guiradgridReportAssessment.DataSource = null;
                        guiradbtnreportedit.Enabled = false;
                        guiradbtnDelete.Enabled = false;
                        guiradbtnPrint.Enabled = false;
                        ClearData();
                        DisplayClinicalParameterSliders();
                        ResetMeasurementFields();
                        OnPwaMeasurementChangedEvent.Invoke(this, new EventArgs());
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

        // TODO: determine the line Low and High Values
        private void DisplayClinicalParameterSliders() 
        {            
            short high = 0;
            short low = 0;
            
            // If Augumentation Index is checked in PWA Settings tab 
            if (crxMgrObject.PwaSettings.AugmentationIndex)
            {
               // crxPwaData.C_Agph = 9999;
                if (crxPwaData.C_Agph != GuiConstants.DefaultValue)
                {
                    if (GuiCommon.bizPwaobject.GetAixRange(PWA_MEASURE_TYPE.PWA_RADIAL, ref high, ref low))
                    {
                        double[] temp = setSliderMinMaxForXAxis(new double[] { crxPwaData.C_Agph, low, high }, guiradlblAixMaxRangeText, guiradlblAixMinRangeText);
                        ShowAixTracker(((float)temp[0]), ((float)temp[1]), crxPwaData.C_Agph, low, high, true);
                    }
                    else
                    {
                        ShowAixTracker(0, 0, 0, 0, 0, false);
                    }
                }
                else
                {
                    ShowAixTracker(0, 0, 0, 0, 0, false);
                }
            }
            else
            {
               // GuiCommon.bizPwaobject.AGPH_HR75 = 9999;
                if (GuiCommon.bizPwaobject.AGPH_HR75 != GuiConstants.DefaultValue)
                {
                    if (GuiCommon.bizPwaobject.GetAixhr75Range(PWA_MEASURE_TYPE.PWA_RADIAL, ref high, ref low))
                    {
                        double[] temp = setSliderMinMaxForXAxis(new double[] { GuiCommon.bizPwaobject.AGPH_HR75, low, high }, guiradlblAixMaxRangeText, guiradlblAixMinRangeText);
                        ShowAixTracker(((float)temp[0]), ((float)temp[1]), GuiCommon.bizPwaobject.AGPH_HR75, low, high, true);
                    }
                    else
                    {
                        ShowAixTracker(0, 0, 0, 0, 0, false);
                    }
                }
                else
                {
                    ShowAixTracker(0, 0, 0, 0, 0, false);
                }
            }

           // crxPwaData.C_Sp = 9999;
            if (crxPwaData.C_Sp != GuiConstants.DefaultValue)
            {
                if (GuiCommon.bizPwaobject.GetSPRange(PWA_MEASURE_TYPE.PWA_RADIAL, ref high, ref low))
                {
                    double[] temp = setSliderMinMaxForXAxis(new double[] { crxPwaData.C_Sp, low, high }, guiradlblSpMaxRangeText, guiradlblSpMinRangeText);
                    ShowSpTracker(((float)temp[0]), ((float)temp[1]), crxPwaData.C_Sp, low, high, true);
                }
                else
                {
                    ShowSpTracker(0, 0, 0, 0, 0, false);
                }
            }
            else
            {
                ShowSpTracker(0, 0, 0, 0, 0, false);
            }

            // crxPwaData.C_Ap = 9999;
            if (crxPwaData.C_Ap != GuiConstants.DefaultValue)
            {
                if (GuiCommon.bizPwaobject.GetAPRange(PWA_MEASURE_TYPE.PWA_RADIAL, ref high, ref low))
                {
                   double[] temp = setSliderMinMaxForXAxis(new double[] { crxPwaData.C_Ap, low, high }, guiradlblApMaxRangeText, guiradlblApMinRangeText);
                   ShowApTracker(((float)temp[0]), ((float)temp[1]), crxPwaData.C_Ap, low, high, true);
                }
                else
                {
                    ShowApTracker(0, 0, 0, 0, 0, false);
                }
            }
            else
            {
                ShowApTracker(0, 0, 0, 0, 0, false);
            }

            float centralPp;
            centralPp = crxPwaData.C_Sp - crxPwaData.C_Dp;

            // centralPp = 9999;
            if (centralPp != GuiConstants.DefaultValue)
            {
                if (GuiCommon.bizPwaobject.GetPPRange(PWA_MEASURE_TYPE.PWA_RADIAL, ref high, ref low))
                {
                    double[] temp = setSliderMinMaxForXAxis(new double[] { centralPp, low, high }, guiradlblPpMaxRangeText, guiradlblPpMinRangeText);
                    ShowPpTracker(((float)temp[0]), ((float)temp[1]), centralPp, low, high, true);
                }
                else
                {
                    ShowPpTracker(50, 0, 0, 0, 0, false);
                }
            }
            else
            {
                ShowPpTracker(50, 0, 0, 0, 0, false);
            }

            guipnlPWAReport.Refresh();
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

            if (GuiCommon.bizPwaobject.ReferenceAge == GuiConstants.DefaultValue)
            {
                guiradlblSphygmocorReferenceAge.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.LblSphygmoCorReferenceAgeNotCalculated);
            }

            if (!string.IsNullOrEmpty(GuiCommon.InConclusiveMessageForPwaCapture))
            {
                CrxLogger.Instance.Write("Message in GUI: " + GuiCommon.InConclusiveMessageForPwaCapture);
                guiradlblInconclusiveMessage.Text = string.Format("{0} {1}", CrxMessagingManager.Instance.GetMessage(CrxStructCommonResourceMsg.GuiInConclusivePwaReportInitialMesg), GuiCommon.InConclusiveMessageForPwaCapture);
            }
            else
            { 
                guiradlblInconclusiveMessage.Text = string.Empty;
            }

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
                    guiradtxtReportHeight.MaxLength = 3;

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

                    guiradtxtReportHeight.MaxLength = 2;
                    guiradlblReportHeightUnits.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.Feet);
                    break;
                default:
                    break;
            }

            // set height details
            guiradtxtReportHeight.Text = guiradlblReportHeightDisplay.Text;
            guiradtxtReportHeightInches.Text = guiradlblReportHeightInches.Text;
           
           // guiradtxtMedicationNotesValue.Text = guiradlblReportNotesDisplay.Text;
            guiradtxtMedicationNotesValue.Text = crxPwaData.Notes;
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
            guiradlblCentralQualityControl.Text = crxPwaCuffData.OperatorIndex.Equals(GuiConstants.DefaultValue) ? string.Empty : Math.Round(crxPwaCuffData.OperatorIndex).ToString();
        }

        /**This method initializes Crx structure to update changes
    * */
        void InitializeCrxFromSetupToReport(string pwaid)
        {
            try
            {
                if (GuiCommon.SetupToReport)
                {
                    PopulateBizFromCrx(pwaid);
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
            pwaData.C_Typical = new float[GuiCommon.bizPwaobject.GetPulseArraySize()];
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
                        GuiCommon.PwaCurrentId = dsPWA.Tables[0].Rows[0][(int)CrxDBGetCuffPWAMeasurementDetails.PWA_Id].ToString();
                        GuiCommon.PwaCurrentStudyDatetime = dsPWA.Tables[0].Rows[0][(int)CrxDBGetCuffPWAMeasurementDetails.StudyDateTime].ToString();
                        PrepareArrayObjectsForPwaMode(crxPwaData, crxPwaCuffData);
                        crxPwaData = getCrxPWAData(dsPWA, crxPwaData);
                        crxPwaCuffData = getCrxPWACuffData(dsPWA, crxPwaCuffData);
                        CrxPwaCaptureInput pwaCaptureInput = new CrxPwaCaptureInput();
                        bool value = GuiCommon.bizPwaobject.GetCurrentCaptureInput(ref pwaCaptureInput);

                        if (!Convert.ToInt32(pwaCaptureInput).Equals(crxPwaData.CaptureInput))
                        {
                            GuiCommon.bizPwaobject.Initialise(crxPwaData.CaptureInput.Equals(Convert.ToInt32(CrxPwaCaptureInput.Tonometer)) ? CrxPwaCaptureInput.Tonometer : CrxPwaCaptureInput.Cuff);
                        }                     

                        GuiCommon.bizPwaobject.Populate(crxPwaData, crxPwaCuffData);
                        if (!string.IsNullOrEmpty(GuiCommon.bizPwaobject.GetInconclusiveNoteMsgKey()))
                        {
                            GuiCommon.InConclusiveMessageForPwaCapture = string.Empty;
                            GuiCommon.InConclusiveMessageForPwaCapture = CrxMessagingManager.Instance.GetMessage(GuiCommon.bizPwaobject.GetInconclusiveNoteMsgKey());
                            CrxLogger.Instance.Write("Message from BLL: " + GuiCommon.InConclusiveMessageForPwaCapture);
                        }
                        else
                        {
                            GuiCommon.InConclusiveMessageForPwaCapture = string.Empty;
                        }

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

                // guilblReportDobValue.Text = patientObj.dateOfBirth.ToString();
                guilblReportAgeValue.Text = GuiCommon.bizPwaobject.patientAge.ToString();
                guilblReportGenderValue.Text = patientObj.gender.Equals(CrxStructCommonResourceMsg.MaleTxt) ? oMsgMgr.GetMessage(CrxStructCommonResourceMsg.MaleTxt) : oMsgMgr.GetMessage(CrxStructCommonResourceMsg.FemaleTxt); 
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

                guiradgridReportAssessment.Columns.Add(oMsgMgr.GetMessage(CrxStructCommonResourceMsg.ReportAssesmentsFormat), oMsgMgr.GetMessage(CrxStructCommonResourceMsg.GuiDisplayStudyDateTime), "StudyDateTime");
                guiradgridReportAssessment.Columns[0].Width = 275;
                guiradgridReportAssessment.Columns[0].IsVisible = true;
                guiradgridReportAssessment.Columns[0].ReadOnly = true;

                guiradgridReportAssessment.Columns.Add("PWA_Id", "PWA_Id", "PWA_Id");
                guiradgridReportAssessment.Columns[1].Width = 50;
                guiradgridReportAssessment.Columns[1].IsVisible = false;
                guiradgridReportAssessment.Columns[1].ReadOnly = true;

                guiradgridReportAssessment.Columns[1].SortOrder = RadSortOrder.Ascending;
                guiradgridReportAssessment.GridElement.AlternatingRowColor = Color.LightGray;
                guiradgridReportAssessment.Columns[0].FormatString = "{0:g}";

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

           // if (GuiCommon.StartupScreen != oMsgMgr.GetMessage(CrxStructCommonResourceMsg.QuickStart))
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
            objDefaultWindow.guiradmnuDatabase.Enabled = false;
            ReportPWADisplayMode(false);

            // set height details
            guiradtxtReportHeight.Text = guiradlblReportHeightDisplay.Text;
            guiradtxtReportHeightInches.Text = guiradlblReportHeightInches.Text;
            guiradtxtMedicationNotesValue.Text = GuiCommon.bizPwaobject.notes;

            // guiradtxtReportOperator.Text = guiradlblReportOperatordisplay.Text;
            // guiradtxtMedicationNotesValue.Text = guiradlblReportNotesDisplay.Text;
           // guiradlblReportNotesDisplay.Text = crxPwaData.Notes;
            guiradbtnreportcancel.Visible = true;
            guiradbtnreportedit.Visible = false;
            guiradbtnreportsave.Visible = true;

            // in edit mode disable repeat & capture buttons
            guiradbtnRepeat.Enabled = false;
            objDefaultWindow.radtabCapture.Enabled = false;
            objDefaultWindow.guiradgrpbxPwvDistanceMethod.Enabled = false;
            objDefaultWindow.guicmbxCurrentMode.Enabled = false;
            GuiCommon.IsFormChanged = true;
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
                guiradgridReportAssessment.Enabled = true;
                guiradtxtReportBloodPressure1.Visible = false;
                guiradtxtReportBloodPressure2.Visible = false;
                guiradtxtReportBloodPressure3.Visible = false;
                guiradtxtReportOperator.Visible = false;
                guiradtxtCentralDpValue.Visible = false;
                guiradtxtCentralHrValue.Visible = false;
                guiradtxtMedicationNotesValue.Visible = false;

                // guiradtxtInterpretation.Visible = false;
                guiradtxtCentralQualityControlValue.Visible = false;

                // guiradtxtInterpretation.Text = string.Empty;
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

                guiradlblReportNotesDisplay.BringToFront();
                guiradlblCentralDp.Visible = true;
                guiradlblCentralHr.Visible = true;
                guiradlblCentralQualityControl.Visible = true;

                guiradlblReportNotesDisplay.Visible = true;

                // guiradlblInterpretationDisplay.Visible = true;
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
                guiradbtnDelete.Enabled = false;
                guiradbtnPrint.Enabled = false;
                guiradbtnRepeat.Enabled = false;
                guiradgridReportAssessment.Enabled = false;

                // edit PWA details (show text boxes)               
                guiradtxtReportHeight.Visible = true;
                guiradtxtMedicationNotesValue.Visible = true;

                // guiradtxtInterpretation.Visible = true;
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
                guiradlblReportNotesDisplay.SendToBack();
                guiradlblCentralDp.Visible = true;
                guiradlblCentralHr.Visible = true;
                guiradlblCentralQualityControl.Visible = true;
                guiradlblReportNotesDisplay.Visible = true;

                // guiradlblInterpretationDisplay.Visible = true;             
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
            GuiCommon.IsFormChanged = false;
        }

        /** This method brings report screen left side measurement details section in display mode
        * It hides cancel & save button & unhides edit button
        * */
        private void SetPWADsiplayMode()
        {
            GuiCommon.IsFormChanged = false;
            objDefaultWindow.radlblMessage.Text = string.Empty;
            objDefaultWindow.guiradmnuDatabase.Enabled = true;
            objDefaultWindow.guiradgrpbxPwvDistanceMethod.Enabled = true;
            objDefaultWindow.guicmbxCurrentMode.Enabled = true;

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
                    pwaIdWithComma += row.Cells["PWA_Id"].Value.ToString() + oMsgMgr.GetMessage(CrxStructCommonResourceMsg.GuiDisplayComma);

                    // pwaIdWithComma += row.Cells[2].Value.ToString() + oMsgMgr.GetMessage(CrxStructCommonResourceMsg.GuiDisplayComma);
                }
            }

            foreach (GridViewRowInfo row in guiradgridReportAssessment.Rows)
            {
                if (row.IsSelected)
                {
                    // recordSelected++;
                    dateWithComma += DateTime.Parse(row.Cells[0].Value.ToString()).ToString(CulturalNeutralDateFormat) + oMsgMgr.GetMessage(CrxStructCommonResourceMsg.GuiDisplayComma);
                }
            }

            GuiConstants.DateWithComma = string.Empty;
            GuiConstants.DateWithComma = dateWithComma;
            GuiConstants.PwaIdWithComma = pwaIdWithComma;
            numeberOfRecordsSelected = recordsToDelete = recordSelected;
            CheckForSimualtionMode();

            // below line of code will keep focus on current record selection in assessment grid
            guiradgridReportAssessment.MasterTemplate.EndUpdate(new DataViewChangedEventArgs(ViewChangedAction.DataChanged));
            guiradgridReportAssessment.MasterTemplate.SynchronizationService.AddListener(navigatorListener);

            // display analysis / report screen based on records selected
            DisplayReportOnSelection(recordSelected, pwaIdWithComma, dateWithComma);
        }

        /** This method binds data to report screen as per the selected assesment
        * */
        private void DisplayReportForSelectedAssesment(string pwaid)
        {
            InitializeCrxOnLoad(pwaid);
            FillPWAMeasurementDetailsReport();
            PlotAvgAorticPulseChart();
            DisplayClinicalParameterSliders();        
        }

        private void DisplayReportOnSelection(int recordSelected, string pwaid, string dateTime)
        {
            pwaIdToCompare = string.Empty;

            if (recordSelected == 1)
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

                pwaIdToCompare = pwaid.Replace(oMsgMgr.GetMessage(CrxStructCommonResourceMsg.GuiDisplayComma), string.Empty);
                guiradbtnreportedit.Enabled = true;

                CheckLastAssessmentSelected(pwaIdToCompare);

                // when record selected is only one display record as per assessment selected
                if (lastAssessmentPwaId == pwaIdToCompare || isFromLoad)
                {
                    DisplayReportForSelectedAssesment(pwaIdToCompare);
                    isFromLoad = true;
                }
            }
            else if (recordSelected > 1)
            {
                EnableDisableReportPrintButton(false);

                guipnlPWAReportAnalysis.Visible = true;
                guipnlPWAReport.Visible = false;
                guiradbtnRepeat.Enabled = false;
                guiradbtnreportedit.Enabled = false;
                PlotAnalysisTrendCharts(dateTime);
                if (GuiCommon.SelChart == GuiCommon.SelectedChart.sp)
                {
                    RenderEnlargedChart(guiradAnalysisChartSP);
                }
                else if (GuiCommon.SelChart == GuiCommon.SelectedChart.pp)
                {
                    RenderEnlargedChart(guiradAnalysisChartPP);
                }
                else if (GuiCommon.SelChart == GuiCommon.SelectedChart.ap)
                {
                    RenderEnlargedChart(guiradAnalysisChartAP);
                }
                else if (GuiCommon.SelChart == GuiCommon.SelectedChart.dpMp)
                {
                    RenderEnlargedChart(guiradAnalysisChartDPMP);
                    guilblLargeDPLegend.Visible = true;
                    guilblLargeMPLegend.Visible = true;
                }
                else if (GuiCommon.SelChart == GuiCommon.SelectedChart.hr)
                {
                    RenderEnlargedChart(guiradAnalysisChartHR);
                }
                else if (GuiCommon.SelChart == GuiCommon.SelectedChart.aix)
                {
                    RenderEnlargedChart(guiradAnalysisChartAix75);
                }

                guiradLargeChart.ChartAreas[0].Position = new ElementPosition(3, 3, 94, 94);

                if (date.Length < MaxNumberOfPointsForChart)
                {
                    guiradLargeChart.ChartAreas[0].AxisX.Maximum = date.Length;
                }
                else
                {
                    guiradLargeChart.ChartAreas[0].AxisX.Maximum = MaxNumberOfPointsForChart;
                }

                objDefaultWindow.radtabReport.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.TabAnalysis);

                // CalculateLabelIntervalX();
                BindCustomLabelForTrendCharts(apRate.Length);
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
                guiradbtnRepeat.Enabled = true;
                objDefaultWindow.radtabReport.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.TabReport);
            }
        }

        /** This method shows analysis trend graph
                 * */
        private void PlotAnalysisTrendCharts(string dateSelected)
        {
            try
            {
                guiradbtnreportedit.Enabled = false;

                // if date ends with comma, truncate it as it creates empty value in array for dates
                if (dateSelected.EndsWith(oMsgMgr.GetMessage(CrxStructCommonResourceMsg.GuiDisplayComma)))
                {
                    dateSelected = dateSelected.Remove(dateSelected.Length - 1);
                }

                string[] dateClac = dateSelected.Split(GuiConstants.Separator);

                string calcPwaIdWithComma = string.Empty;
                string calcDateWithComma = string.Empty;

                if (dateClac.Length > MaxNumberOfPointsForChart)
                {
                    string[] tempPwaId = GuiConstants.PwaIdWithComma.Split(GuiConstants.Separator);

                    string[] calcDate = new string[MaxNumberOfPointsForChart];
                    string[] calcPwaId = new string[MaxNumberOfPointsForChart];
                    date = new string[MaxNumberOfPointsForChart];

                    int clcStrt = dateClac.Length - MaxNumberOfPointsForChart;
                    for (int i = clcStrt, j = 0; i < dateClac.Length; i++, j++)
                    {
                        calcDate[j] = dateClac[i];
                        date[j] = dateClac[i];
                        calcPwaId[j] = tempPwaId[i];
                        string tempIdWithComma = string.Empty;
                        tempIdWithComma = tempPwaId[i].ToString();
                        calcPwaIdWithComma = calcPwaIdWithComma + tempIdWithComma + GuiConstants.Separator;
                        string tempDateWithComma = string.Empty;
                        tempDateWithComma = dateClac[i].ToString();
                        calcDateWithComma = calcDateWithComma + tempDateWithComma + GuiConstants.Separator;
                    }
                }
                else
                {
                    calcPwaIdWithComma = GuiConstants.PwaIdWithComma;
                    calcDateWithComma = dateSelected;
                    date = dateSelected.Split(GuiConstants.Separator);
                }

                date = dateSelected.Split(GuiConstants.Separator);

                // check for connection
                if (dbMagr.CheckConnection(serverNameString, crxMgrObject.GeneralSettings.SourceData) == 0)
                {
                    CrxStructPWATrendData trendData = new CrxStructPWATrendData();

                    // fetch records for selected assessments
                    dbMagr.GetPWATrendData(calcPwaIdWithComma, trendData);

                    if (!string.IsNullOrEmpty(trendData.ApValidArrStr) && !string.IsNullOrEmpty(trendData.HrValidArrStr) && !string.IsNullOrEmpty(trendData.SpValidArrStr) && !string.IsNullOrEmpty(trendData.DpValidArrStr) && !string.IsNullOrEmpty(trendData.MpValidArrStr))
                    {
                        PlotApTrendData(trendData);
                        PlotHrTrendData(trendData);
                        PlotSpTrendData(trendData);
                        PlotDpMpTrendData(trendData);
                        PlotPpTrendData(trendData);
                        PlotAixTrendData(calcPwaIdWithComma);
                        guiradLargeChart.GetToolTipText += Chart_GetToolTipText;
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
            GuiCommon.SelChart = GuiCommon.SelectedChart.dpMp;
            RenderEnlargedChart(guiradAnalysisChartDPMP);
            BindCustomLabelForTrendCharts(date.Length);
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
            GuiCommon.SelChart = GuiCommon.SelectedChart.hr;
            RenderEnlargedChart(guiradAnalysisChartHR);
            BindCustomLabelForTrendCharts(date.Length);
            guiradAnalysisChartSP.Update();
            guiradAnalysisChartPP.Update();
            guiradAnalysisChartDPMP.Update();
            guiradAnalysisChartAix75.Update();
            guiradAnalysisChartAP.Update();
        }

        private void guiradAnalysisChartSP_DoubleClick(object sender, EventArgs e)
        {
            GuiCommon.SelChart = GuiCommon.SelectedChart.sp;
            RenderEnlargedChart(guiradAnalysisChartSP);
            BindCustomLabelForTrendCharts(date.Length);
            guiradAnalysisChartHR.Update();
            guiradAnalysisChartPP.Update();
            guiradAnalysisChartDPMP.Update();
            guiradAnalysisChartAix75.Update();
            guiradAnalysisChartAP.Update();
        }

        private void guiradAnalysisChartSphygmocorRefAge_DoubleClick(object sender, EventArgs e)
        {
            GuiCommon.SelChart = GuiCommon.SelectedChart.aix;
            RenderEnlargedChart(guiradAnalysisChartAix75);
            BindCustomLabelForTrendCharts(date.Length);
            guiradAnalysisChartHR.Update();
            guiradAnalysisChartAP.Update();
            guiradAnalysisChartPP.Update();
            guiradAnalysisChartDPMP.Update();
            guiradAnalysisChartSP.Update();
        }

        private void guiradAnalysisChartAP_DoubleClick(object sender, EventArgs e)
        {
            GuiCommon.SelChart = GuiCommon.SelectedChart.ap;
            RenderEnlargedChart(guiradAnalysisChartAP);
            BindCustomLabelForTrendCharts(date.Length);
            guiradAnalysisChartHR.Update();
            guiradAnalysisChartPP.Update();
            guiradAnalysisChartDPMP.Update();
            guiradAnalysisChartAix75.Update();
            guiradAnalysisChartSP.Update();
        }

        private void guiradAnalysisChartPP_DoubleClick(object sender, EventArgs e)
        {
            GuiCommon.SelChart = GuiCommon.SelectedChart.pp;
            RenderEnlargedChart(guiradAnalysisChartPP);
            BindCustomLabelForTrendCharts(date.Length);
            guiradAnalysisChartHR.Update();
            guiradAnalysisChartAP.Update();
            guiradAnalysisChartDPMP.Update();
            guiradAnalysisChartAix75.Update();
            guiradAnalysisChartSP.Update();
        }

        private void RenderEnlargedChart(Chart selectedChart)
        {
            setSmallChartProperties(guiradAnalysisChartPP);
            setSmallChartProperties(guiradAnalysisChartAP);
            setSmallChartProperties(guiradAnalysisChartDPMP);
            setSmallChartProperties(guiradAnalysisChartAix75);
            setSmallChartProperties(guiradAnalysisChartSP);
            setSmallChartProperties(guiradAnalysisChartHR);

            lblDPLegend.BringToFront();
            lblMPLegend.BringToFront();

            // Setting the properties for Clicked Chart
            selectedChart.BorderlineColor = Color.White;
            selectedChart.BorderlineDashStyle = ChartDashStyle.Solid;
            selectedChart.BorderlineWidth = 3;
            selectedChart.BorderSkin.SkinStyle = BorderSkinStyle.Emboss;
            selectedChart.BorderSkin.BackColor = Color.Transparent;
            selectedChart.BorderSkin.BackGradientStyle = GradientStyle.None;
            selectedChart.BorderSkin.BackHatchStyle = ChartHatchStyle.BackwardDiagonal;
            selectedChart.BorderSkin.BorderColor = Color.Transparent;
            selectedChart.BorderSkin.BorderDashStyle = ChartDashStyle.Solid;
            selectedChart.BorderSkin.BorderWidth = 2;
            selectedChart.BorderSkin.PageColor = Color.FromArgb(142, 150, 186);     
            selectedChart.SendToBack();

            ElementPosition obj = new ElementPosition();
            obj.X = Convert.ToInt32(6.926702);
            obj.Y = Convert.ToInt32(14.8504);
            obj.Height = 79;
            obj.Width = Convert.ToInt32(84.18234);

            selectedChart.ChartAreas[0].Position = obj;
            guiradLargeChart.Titles[0].Text = selectedChart.Titles[0].Text;
            guiradLargeChart.Titles[0].ForeColor = Color.WhiteSmoke;
            guiradLargeChart.Titles[0].Font = new Font("Arial", 8, FontStyle.Bold);
            guiradLargeChart.Titles[0].Position = new ElementPosition(3f, 1f, 94f, 3.119616f);

            guiradLargeChart.ChartAreas[0].AxisX.Minimum = selectedChart.ChartAreas[0].AxisX.Minimum;
            guiradLargeChart.ChartAreas[0].AxisX.Maximum = selectedChart.ChartAreas[0].AxisX.Maximum;
            guiradLargeChart.ChartAreas[0].AxisX.Interval = selectedChart.ChartAreas[0].AxisX.Interval;
            guiradLargeChart.ChartAreas[0].AxisX.Crossing = selectedChart.ChartAreas[0].AxisX.Crossing;
            guiradLargeChart.ChartAreas[0].AxisX.LabelStyle.Enabled = selectedChart.ChartAreas[0].AxisX.LabelStyle.Enabled;

            guiradLargeChart.ChartAreas[0].AxisX.MajorGrid.Enabled = selectedChart.ChartAreas[0].AxisX.MajorGrid.Enabled;
            guiradLargeChart.ChartAreas[0].AxisX.MajorGrid.LineColor = selectedChart.ChartAreas[0].AxisX.MajorGrid.LineColor;
            guiradLargeChart.ChartAreas[0].AxisX.MajorGrid.LineDashStyle = selectedChart.ChartAreas[0].AxisX.MajorGrid.LineDashStyle;
            guiradLargeChart.ChartAreas[0].AxisX.MajorGrid.LineWidth = selectedChart.ChartAreas[0].AxisX.MajorGrid.LineWidth;
            guiradLargeChart.ChartAreas[0].AxisX.MajorTickMark.Enabled = true;

            guiradLargeChart.ChartAreas[0].AxisX.MinorGrid.Enabled = selectedChart.ChartAreas[0].AxisX.MinorGrid.Enabled;
            guiradLargeChart.ChartAreas[0].AxisX.MinorGrid.LineColor = selectedChart.ChartAreas[0].AxisX.MinorGrid.LineColor;
            guiradLargeChart.ChartAreas[0].AxisX.MinorGrid.LineDashStyle = selectedChart.ChartAreas[0].AxisX.MinorGrid.LineDashStyle;
            guiradLargeChart.ChartAreas[0].AxisX.MinorGrid.LineWidth = selectedChart.ChartAreas[0].AxisX.MinorGrid.LineWidth;
            guiradLargeChart.ChartAreas[0].AxisX.MinorTickMark.Enabled = false;

            guiradLargeChart.ChartAreas[0].AxisY.Minimum = selectedChart.ChartAreas[0].AxisY.Minimum;
            guiradLargeChart.ChartAreas[0].AxisY.Maximum = selectedChart.ChartAreas[0].AxisY.Maximum;
            guiradLargeChart.ChartAreas[0].AxisY.Interval = selectedChart.ChartAreas[0].AxisY.Interval;
            guiradLargeChart.ChartAreas[0].AxisY.Crossing = selectedChart.ChartAreas[0].AxisY.Crossing;

            guiradLargeChart.ChartAreas[0].AxisY.MajorGrid.Enabled = selectedChart.ChartAreas[0].AxisY.MajorGrid.Enabled;
            guiradLargeChart.ChartAreas[0].AxisY.MajorGrid.LineColor = selectedChart.ChartAreas[0].AxisY.MajorGrid.LineColor;
            guiradLargeChart.ChartAreas[0].AxisY.MajorGrid.LineDashStyle = selectedChart.ChartAreas[0].AxisY.MajorGrid.LineDashStyle;
            guiradLargeChart.ChartAreas[0].AxisY.MajorGrid.LineWidth = selectedChart.ChartAreas[0].AxisY.MajorGrid.LineWidth;
            guiradLargeChart.ChartAreas[0].AxisY.LabelStyle.ForeColor = selectedChart.ChartAreas[0].AxisY.LabelStyle.ForeColor;

            guiradLargeChart.ChartAreas[0].AxisY.MinorGrid.Enabled = selectedChart.ChartAreas[0].AxisY.MinorGrid.Enabled;
            guiradLargeChart.ChartAreas[0].AxisY.MinorGrid.LineColor = selectedChart.ChartAreas[0].AxisY.MinorGrid.LineColor;
            guiradLargeChart.ChartAreas[0].AxisY.MinorGrid.LineDashStyle = selectedChart.ChartAreas[0].AxisY.MinorGrid.LineDashStyle;
            guiradLargeChart.ChartAreas[0].AxisY.MinorGrid.LineWidth = selectedChart.ChartAreas[0].AxisY.MinorGrid.LineWidth;
            guiradLargeChart.ChartAreas[0].AxisY.MinorTickMark.Enabled = false;
            guiradLargeChart.ChartAreas[0].AxisX.LabelStyle.Enabled = true;
            guiradLargeChart.ChartAreas[0].AxisX.LabelStyle.ForeColor = Color.WhiteSmoke;

            // guiradLargeChart.ChartAreas[0].Position = new ElementPosition(3, 3, 94, 94);
            guilblLargeDPLegend.Visible = false;
            guilblLargeMPLegend.Visible = false;

            guiradLargeChart.Series.Clear();

            foreach (Series series in selectedChart.Series)
            {
                guiradLargeChart.Series.Add(series);
            }

            foreach (Series series in guiradLargeChart.Series)
            {
                series.CustomProperties = "BubbleMaxSize=7";
            }

            // guiradLargeChart.Invalidate();
        }

        private void setSmallChartProperties(Chart smallChart)
        {
            smallChart.BorderlineColor = Color.White;
            smallChart.BorderlineDashStyle = ChartDashStyle.Solid;
            smallChart.BorderlineWidth = 1;
            smallChart.BorderSkin.SkinStyle = BorderSkinStyle.None;
            smallChart.BorderSkin.BackColor = Color.Gray;
            smallChart.BorderSkin.BackGradientStyle = GradientStyle.None;
            smallChart.BorderSkin.BackHatchStyle = ChartHatchStyle.None;
            smallChart.BorderSkin.BorderColor = Color.Black;
            smallChart.BorderSkin.BorderDashStyle = ChartDashStyle.NotSet;
            smallChart.BorderSkin.BorderWidth = 1;
            smallChart.BorderSkin.PageColor = Color.White;
            foreach (Series item in smallChart.Series)
            {
                item.CustomProperties = "BubbleMaxSize=15";
            }

            smallChart.BringToFront();
            smallChart.Update();
        }

        /** This method clears all chart series for tonometer, normal & reference range
       * */
        private void ClearData()
        {
            // guichartPWAReport.Series.Clear();
            guichartPWAReport.Series[0].Points.Clear();
            guichartPWAReport.Series[1].Points.Clear();

            GuiCommon.bizPwaobject.AGPH_HR75 = GuiConstants.DefaultValue;
            crxPwaData.C_Agph = GuiConstants.DefaultValue;
            crxPwaData.C_Sp = GuiConstants.DefaultValue;
            crxPwaData.C_Ap = GuiConstants.DefaultValue;
            crxPwaData.C_Dp = 0;
            guiradlblInconclusiveMessage.Text = String.Empty;
            guiradlblSphygmocorReferenceAge.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.LblSphygmoCorReferenceAgeNotCalculated);
        }

        /** This method resets all PWA measurement fields
       * */
        private void ResetMeasurementFields()
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
            guiradtxtMedicationNotesValue.Text = string.Empty;
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
            float[] avgTypicalAorticPulse = crxPwaData.C_Typical;

            guichartPWAReport.Series[0].Points.Clear();

            for (int i = 0; i < avgAorticPulse.Length; i++)
            {
                if (avgAorticPulse[i] == 0)
                {
                    break;
                }
                else
                {
                    guichartPWAReport.Series[0].Points.AddXY(averageAorticXAxisInterval * i, avgAorticPulse[i]);
                }
            }

            guichartPWAReport.Series[1].Points.Clear();

            for (int i = 0; i < avgTypicalAorticPulse.Length; i++)
            {
                if (avgTypicalAorticPulse[i] == 0)
                {
                    break;
                }
                else
                {
                    guichartPWAReport.Series[1].Points.AddXY(averageAorticXAxisInterval * i, avgTypicalAorticPulse[i]);
                }
            }

            //// Setting minimum and maximum of Y-axis for Chart

            float[] tempFloatArray = new float[avgAorticPulse.Length + avgTypicalAorticPulse.Length];

            Array.Copy(avgAorticPulse, tempFloatArray, avgAorticPulse.Length);
            Array.Copy(avgTypicalAorticPulse, 0, tempFloatArray, avgAorticPulse.Length, avgTypicalAorticPulse.Length);
            Array.Sort(tempFloatArray);
            for (int i = 0; i < tempFloatArray.Length; i++)
            {
                if (tempFloatArray[i] == 0)
                {
                }
                else
                {
                    double value = Math.Round(tempFloatArray[i] * GuiConstants.ChartAreaMinimumY, MidpointRounding.ToEven);
                    value = ((int)Math.Round(value / 10)) * 10;
                    guichartPWAReport.ChartAreas[0].AxisY.Minimum = value - 10;
                    break;
                }
            }

            double valueMax = Math.Round((tempFloatArray[tempFloatArray.Length - 1]) * GuiConstants.ChartAreaMaximumY, MidpointRounding.ToEven);
            valueMax = ((int)Math.Round(valueMax / 10)) * 10;
            guichartPWAReport.ChartAreas[0].AxisY.Maximum = valueMax + 10;
            guichartPWAReport.Invalidate();
        }        

        /**This method is used to show the Aix tracker on the PWA Report screen, depending upon its value.
         */
        private void ShowAixTracker(float maxValue, float minValue, float value, float goodRangeMin, float goodRangeMax, bool visible)
        {
            // Hide/Show Aix Slider Labels
            guilblAIxValueText.Visible = visible;
            guilblAIxValue.Visible = visible;
            guilblAIxGoodMin.Visible = visible;
            guilblAIxGoodMinText.Visible = visible;
            guilblAIxGoodMaxText.Visible = visible;
            guilblAIxGoodMax.Visible = visible;
            guiradlblAixMaxRange.Visible = visible;
            guiradlblAixMinRange.Visible = visible;
            guiradlblAixMinRangeText.Visible = visible;
            guiradlblAixMaxRangeText.Visible = visible;
            guiradlblAixNotCalc.Visible = !visible;

            if (visible)
            {                    
                guilblAIxValue.Left = guilblAIxSlider.Left + (int)((Math.Round(value) - minValue) * (guilblAIxSlider.Width / (int)(maxValue - minValue))) - (guilblAIxValue.Width / 2);
                guilblAIxGoodMin.Left = guilblAIxSlider.Left + (int)((goodRangeMin - minValue) * (guilblAIxSlider.Width / (int)(maxValue - minValue))) - (guilblAIxGoodMin.Width / 2);

                guilblAIxGoodMax.Left = guilblAIxSlider.Left + (int)((goodRangeMax - minValue) * (guilblAIxSlider.Width / (int)(maxValue - minValue))) - (guilblAIxGoodMax.Width / 2);

                guilblAIxValueText.Left = guilblAIxValue.Left - (guilblAIxValueText.Width / 3) + 4;
                guilblAIxGoodMaxText.Left = guilblAIxGoodMax.Left - (guilblAIxGoodMaxText.Width / 3);
                guilblAIxGoodMinText.Left = guilblAIxGoodMin.Left - (guilblAIxGoodMinText.Width / 3);

                guilblAIxValueText.Text = Math.Round(value).ToString();
                guilblAIxGoodMaxText.Text = goodRangeMax.ToString();
                guilblAIxGoodMinText.Text = goodRangeMin.ToString();

                if ((Math.Round(value) < goodRangeMin) || (Math.Round(value) > goodRangeMax))
                {
                    guilblAIxValue.BackColor = Color.Red;
                }
                else
                {
                    guilblAIxValue.BackColor = Color.LimeGreen;
                }
            }           

            // AIx Tracker: End
        }

        /**This method is used to show the SP tracker on the PWA Report screen, depending upon its value.
        */
        private void ShowSpTracker(float spMaxValue, float spMinValue, float spValue, float spGoodRangeMin, float spGoodRangeMax, bool visible)
        {
            // Hide/Show Sp Slider Labels
            guilblSPValueText.Visible = visible;
            guilblSPValue.Visible = visible;
            guilblSPGoodMin.Visible = visible;
            guilblSPGoodMinText.Visible = visible;
            guilblSPGoodMaxText.Visible = visible;
            guilblSPGoodMax.Visible = visible;
            guiradlblSpMaxRange.Visible = visible;
            guiradlblSpMinRange.Visible = visible;
            guiradlblSpMaxRangeText.Visible = visible;
            guiradlblSpMinRangeText.Visible = visible;
            guiradlblSpNotCalc.Visible = !visible;

            if (visible) 
            {             
                guilblSPValue.Left = guilblSPSlider.Left + ((int)(Math.Round(spValue) - spMinValue) * (guilblSPSlider.Width / (int)(spMaxValue - spMinValue))) - (guilblSPValue.Width / 2);
                guilblSPGoodMin.Left = guilblSPSlider.Left + ((int)(spGoodRangeMin - spMinValue) * (guilblSPSlider.Width / (int)(spMaxValue - spMinValue))) - (guilblSPGoodMin.Width / 2);
                guilblSPGoodMinText.Left = guilblSPGoodMin.Left - (guilblSPGoodMinText.Width / 3);
                guilblSPGoodMax.Left = guilblSPSlider.Left + ((int)(spGoodRangeMax - spMinValue) * (guilblSPSlider.Width / (int)(spMaxValue - spMinValue))) - (guilblSPGoodMax.Width / 2);

                guilblSPValueText.Left = guilblSPValue.Left - (guilblSPValueText.Width / 3) + 2;
                guilblSPGoodMaxText.Left = guilblSPGoodMax.Left - (guilblSPGoodMaxText.Width / 3);

                guilblSPValueText.Text = Math.Round(spValue).ToString();
                guilblSPGoodMaxText.Text = spGoodRangeMax.ToString();
                guilblSPGoodMinText.Text = spGoodRangeMin.ToString();

                if ((Math.Round(spValue) < spGoodRangeMin) || (Math.Round(spValue) > spGoodRangeMax))
                {
                    guilblSPValue.BackColor = Color.Red;
                }
                else
                {
                    guilblSPValue.BackColor = Color.LimeGreen;
                }
            }
            
            // SP Tracker: End
        }

        /**This method is used to show the PP tracker on the PWA Report screen, depending upon its value.
        */
        private void ShowPpTracker(float ppMaxValue, float ppMinValue, float ppValue, float ppGoodRangeMin, float ppGoodRangeMax, bool visible)
        {
            // Hide/Show Pp Slider Labels
            guilblPPValueText.Visible = visible;
            guilblPPValue.Visible = visible;
            guilblPPGoodMin.Visible = visible;
            guilblPPGoodMinText.Visible = visible;
            guilblPPGoodMaxText.Visible = visible;
            guilblPPGoodMax.Visible = visible;
            guiradlblPpMaxRange.Visible = visible;
            guiradlblPpMinRange.Visible = visible;
            guiradlblPpMinRangeText.Visible = visible;
            guiradlblPpMaxRangeText.Visible = visible;
            guiradlblPpNotCalc.Visible = !visible;

            if (visible)
            {
                guilblPPValue.Left = guilblPPSlider.Left + ((int)(Math.Round(ppValue) - ppMinValue) * (guilblPPSlider.Width / (int)(ppMaxValue - ppMinValue))) - (guilblPPValue.Width / 2);

                guilblPPGoodMin.Left = guilblPPSlider.Left + ((int)(ppGoodRangeMin - ppMinValue) * (guilblPPSlider.Width / (int)(ppMaxValue - ppMinValue))) - (guilblPPGoodMin.Width / 2);
                guilblPPGoodMax.Left = guilblPPSlider.Left + ((int)(ppGoodRangeMax - ppMinValue) * (guilblPPSlider.Width / (int)(ppMaxValue - ppMinValue))) - (guilblPPGoodMax.Width / 2);

                guilblPPValueText.Left = guilblPPValue.Left - (guilblPPValueText.Width / 3) + 3;
                guilblPPGoodMaxText.Left = guilblPPGoodMax.Left - (guilblPPGoodMaxText.Width / 3);
                guilblPPGoodMinText.Left = guilblPPGoodMin.Left - (guilblPPGoodMinText.Width / 3);

                guilblPPValueText.Text = Math.Round(ppValue).ToString();
                guilblPPGoodMaxText.Text = ppGoodRangeMax.ToString();
                guilblPPGoodMinText.Text = ppGoodRangeMin.ToString();

                if ((Math.Round(ppValue) < ppGoodRangeMin) || (Math.Round(ppValue) > ppGoodRangeMax))
                {
                    guilblPPValue.BackColor = Color.Red;
                }
                else
                {
                    guilblPPValue.BackColor = Color.LimeGreen;
                }
            }

            // PP Tracker: End
        }

        /**This method is used to show the AP tracker on the PWA Report screen, depending upon its value.
        */
        private void ShowApTracker(float apMaxValue, float apMinValue, float apValue, float apGoodRangeMin, float apGoodRangeMax, bool visible)
        {
            // Hide/Show Ap Slider Labels
            guilblAPValueText.Visible = visible;
            guilblAPValue.Visible = visible;
            guilblAPGoodMin.Visible = visible;
            guilblAPGoodMinText.Visible = visible;
            guilblAPGoodMaxText.Visible = visible;
            guilblAPGoodMax.Visible = visible;
            guiradlblApMaxRange.Visible = visible;
            guiradlblApMinRange.Visible = visible;
            guiradlblApMaxRangeText.Visible = visible;
            guiradlblApMinRangeText.Visible = visible;
            guiradlblApNotCalc.Visible = !visible;

            if (visible) 
            {
                guilblAPValue.Left = (guilblAPSlider.Left + ((int)(Math.Round(apValue) - apMinValue) * (guilblAPSlider.Width / (int)(apMaxValue - apMinValue)))) - (guilblAPValue.Width / 2);
                guilblAPGoodMin.Left = (guilblAPSlider.Left + ((int)(apGoodRangeMin - apMinValue) * (guilblAPSlider.Width / (int)(apMaxValue - apMinValue)))) - (guilblAPGoodMin.Width / 2);

                guilblAPGoodMax.Left = guilblAPSlider.Left + ((int)(apGoodRangeMax - apMinValue) * (guilblAPSlider.Width / (int)(apMaxValue - apMinValue))) - (guilblAIxGoodMax.Width / 2);

                guilblAPValueText.Left = guilblAPValue.Left - (guilblAPValueText.Width / 3) + 2;
                guilblAPGoodMaxText.Left = guilblAPGoodMax.Left - (guilblAPGoodMaxText.Width / 3);
                guilblAPGoodMinText.Left = guilblAPGoodMin.Left - (guilblAPGoodMinText.Width / 3);

                guilblAPValueText.Text = Math.Round(apValue).ToString();
                guilblAPGoodMaxText.Text = apGoodRangeMax.ToString();
                guilblAPGoodMinText.Text = apGoodRangeMin.ToString();

                if ((Math.Round(apValue) < apGoodRangeMin) || (Math.Round(apValue) > apGoodRangeMax))
                {
                    guilblAPValue.BackColor = Color.Red;
                }
                else
                {
                    guilblAPValue.BackColor = Color.LimeGreen;
                }
            }

            // AP Tracker: End
        }

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
                    chart.Series[i].Points[j].ToolTip = "(#VAL)";
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
                    }
                }

                guipnlPWAReport.Refresh();
                guipnlPatientDetails.Refresh();
                CheckForSimualtionMode();
            }
            catch (Exception ex)
            {
                GUIExceptionHandler.HandleException(ex, this);
            }
        }

        /** This method is used to set the maximum and minimum value for X Axis on Slider
        * */
        private double[] setSliderMinMaxForXAxis(double[] data, RadLabel labelMax, RadLabel labelMin)
        {
            double max = 0.0;
            double min = 0.0;
            Array.Sort(data);
            double value = Math.Round(data[0] * GuiConstants.ChartAreaMinimumY, MidpointRounding.ToEven);
            
            value = ((int)Math.Round(value / 10)) * 10;

            if ((value == 0) || (value < 0 && value > data[0])) 
            {
                value = Math.Round(data[0]);
            }
            
            min = value - 5;
            
            labelMin.Text = min.ToString();
            
            value = Math.Round((data[data.Length - 1]) * GuiConstants.ChartAreaMaximumY, MidpointRounding.ToEven);
            
            value = ((int)Math.Round(value / 10)) * 10;
            
            max = value + 5;
            
            labelMax.Text = max.ToString();
            
            return new double[] { max, min };
        }

        /** This method is used to set the maximum and minimum value for Y- Axis
         * */
        private void setChartMinMaxForYAxis(Chart chartObject, double[] data, out double minValue) 
        {
            double[] tempData = RemoveDefaultValuesFromArrList(data);
            Array.Sort(tempData);
            if (tempData.Length > 0)
            {
                double value = Math.Round(tempData[0] * GuiConstants.ChartAreaMinimumY, MidpointRounding.ToEven);
                value = ((int)Math.Round(value / 10)) * 10;
                chartObject.ChartAreas[0].AxisY.Minimum = value - 10;
                minValue = value - 10;
                value = Math.Round((tempData[tempData.Length - 1]) * GuiConstants.ChartAreaMaximumY, MidpointRounding.ToEven);
                value = ((int)Math.Round(value / 10)) * 10;
                chartObject.ChartAreas[0].AxisY.Maximum = value + 10;
                chartObject.ChartAreas[0].AxisY.Interval = 10;
            }
            else
            {
                minValue = 0;
                chartObject.ChartAreas[0].AxisY.Minimum = 0;
                chartObject.ChartAreas[0].AxisY.Maximum = 10;
            }
        }

        /** This method plots Aix trend graph
         * */
        private void PlotAixTrendData(string pwaIdWithComma)
        {
            double[] aixDataArr = prepareAix75Data(pwaIdWithComma);
            string[] aixArr = CrxDBManager.Instance.CommonDoubleArrToStringArr(aixDataArr);

            guiradAnalysisChartAix75.Series[0].Points.Clear();
            guiradAnalysisChartAix75.Series[1].Points.Clear();
            double minValue = 0;

            setChartMinMaxForYAxis(guiradAnalysisChartAix75, aixDataArr, out minValue);

            // plot Aix rate series
            if (aixArr.Length > 0)
            {
                for (int series = 0; series < aixDataArr.Length; series++)
                {
                    // check if value is 9999
                    if (!aixArr[series].Equals(dfBPVlaue))
                    {
                        guiradAnalysisChartAix75.Series[0].Points.AddXY(series, double.Parse(aixArr[series], CrxCommon.nCI));
                        guiradAnalysisChartAix75.Series[1].Points.AddXY(series, double.Parse(aixArr[series], CrxCommon.nCI));
                    }
                    else
                    {
                        minValue = minValue - 10;
                        guiradAnalysisChartAix75.Series[1].Points.AddXY(series, minValue);
                    }
                }

                if (aixDataArr.Length <= MaxNumberOfPointsForChart)
                {
                    guiradAnalysisChartAix75.ChartAreas[0].AxisX.Maximum = aixDataArr.Length;
                }
                else
                {
                    guiradAnalysisChartAix75.ChartAreas[0].AxisX.Maximum = MaxNumberOfPointsForChart;
                }
            }
        }

        /** This method plots Ap trend graph
         * */
        private void PlotApTrendData(CrxStructPWATrendData trendData)
        {
            guiradAnalysisChartAP.Series[0].Points.Clear();
            guiradAnalysisChartAP.Series[1].Points.Clear();

            apRate = trendData.ApValidArrStr.Split(GuiConstants.Separator);
            double[] tempDouble = CrxDBManager.Instance.CommonStringArrToDoubleArr(trendData.ApValidArrStr.Split(GuiConstants.Separator));
            double minValue = 0;
            setChartMinMaxForYAxis(guiradAnalysisChartAP, tempDouble, out minValue);

            // plot heart rate series
            if (apRate.Length > 0)
            {
                for (int series = 0; series < apRate.Length; series++)
                {
                    // check if value is 9999
                    if (!apRate[series].Equals(dfBPVlaue))
                    {
                        guiradAnalysisChartAP.Series[0].Points.AddXY(series, double.Parse(apRate[series], CrxCommon.nCI));
                        guiradAnalysisChartAP.Series[1].Points.AddXY(series, double.Parse(apRate[series], CrxCommon.nCI));
                    }
                    else
                    {
                        minValue = minValue - 10;
                        guiradAnalysisChartAP.Series[1].Points.AddXY(series, minValue);
                    }
                }

                if (apRate.Length <= MaxNumberOfPointsForChart)
                {
                    guiradAnalysisChartAP.ChartAreas[0].AxisX.Maximum = apRate.Length;
                }
                else
                {
                    guiradAnalysisChartAP.ChartAreas[0].AxisX.Maximum = MaxNumberOfPointsForChart;
                }
            }
        }

        /** This method plots Hr trend graph
         * */
        private void PlotHrTrendData(CrxStructPWATrendData trendData)
        {
            hrRate = trendData.HrValidArrStr.Split(GuiConstants.Separator);

            guiradAnalysisChartHR.Series[0].Points.Clear();
            guiradAnalysisChartHR.Series[1].Points.Clear();
            double[] tempDouble = CrxDBManager.Instance.CommonStringArrToDoubleArr(trendData.HrValidArrStr.Split(GuiConstants.Separator));

            double minValue;
            setChartMinMaxForYAxis(guiradAnalysisChartHR, tempDouble, out minValue);

            // plot heart rate series
            if (hrRate.Length > 0)
            {
                for (int series = 0; series < hrRate.Length; series++)
                {
                    /// guiradAnalysisChartHR.Series[0].Points.AddXY(series, double.Parse(hrRate[series], CrxCommon.nCI));
                    /// guiradAnalysisChartHR.Series[1].Points.AddXY(series, double.Parse(hrRate[series], CrxCommon.nCI));

                    // check if value is 9999
                    if (!hrRate[series].Equals(GuiConstants.SdefaultValue.ToString()))
                    {
                        guiradAnalysisChartHR.Series[0].Points.AddXY(series, double.Parse(hrRate[series], CrxCommon.nCI));
                        guiradAnalysisChartHR.Series[1].Points.AddXY(series, double.Parse(hrRate[series], CrxCommon.nCI));
                    }
                    else
                    {
                        guiradAnalysisChartHR.Series[1].Points.AddXY(series, minValue);
                    }
                }

                if (hrRate.Length <= MaxNumberOfPointsForChart)
                {
                    guiradAnalysisChartHR.ChartAreas[0].AxisX.Maximum = hrRate.Length;
                }
                else
                {
                    guiradAnalysisChartHR.ChartAreas[0].AxisX.Maximum = MaxNumberOfPointsForChart;
                }
            }
        }

        /** This method plots Pp trend graph
         * */
        private void PlotPpTrendData(CrxStructPWATrendData trendData)
        {
            guiradAnalysisChartPP.Series[0].Points.Clear();
            guiradAnalysisChartPP.Series[1].Points.Clear();

            spRate = trendData.SpValidArrStr.Split(GuiConstants.Separator);
            dpRate = trendData.DpValidArrStr.Split(GuiConstants.Separator);
            ppRate = new string[spRate.Length];

            for (int index = 0; index < spRate.Length; index++)
            {
                ppRate[index] = Convert.ToString(double.Parse(spRate[index]) - double.Parse(dpRate[index]));
            }

            double[] tempDouble = CrxDBManager.Instance.CommonStringArrToDoubleArr(ppRate);

            double minValue;
            setChartMinMaxForYAxis(guiradAnalysisChartPP, tempDouble, out minValue );

            // plot Pp rate series
            if (ppRate.Length > 0)
            {
                for (int series = 0; series < ppRate.Length; series++)
                {
                    // check if value is 9999
                    if (!ppRate[series].Equals(GuiConstants.SdefaultValue.ToString()))
                    {
                        guiradAnalysisChartPP.Series[0].Points.AddXY(series, double.Parse(ppRate[series], CrxCommon.nCI));
                        guiradAnalysisChartPP.Series[1].Points.AddXY(series, double.Parse(ppRate[series], CrxCommon.nCI));
                    }
                    else
                    {
                        guiradAnalysisChartPP.Series[1].Points.AddXY(series, minValue);
                    }
                }

                if (ppRate.Length <= MaxNumberOfPointsForChart)
                {
                    guiradAnalysisChartPP.ChartAreas[0].AxisX.Maximum = ppRate.Length;
                }
                else
                {
                    guiradAnalysisChartPP.ChartAreas[0].AxisX.Maximum = MaxNumberOfPointsForChart;
                }
            }
        }

        /** This method plots Sp trend graph
        * */
        private void PlotSpTrendData(CrxStructPWATrendData trendData)
        {
            guiradAnalysisChartSP.Series[0].Points.Clear();
            guiradAnalysisChartSP.Series[1].Points.Clear();

            spRate = trendData.SpValidArrStr.Split(GuiConstants.Separator);
            double[] tempDouble = CrxDBManager.Instance.CommonStringArrToDoubleArr(trendData.SpValidArrStr.Split(GuiConstants.Separator));

            double minValue;
            setChartMinMaxForYAxis(guiradAnalysisChartSP, tempDouble, out minValue);
            if (spRate.Length > 0)
            {
                for (int series = 0; series < spRate.Length; series++)
                {
                    // check if value is 9999
                    if (!spRate[series].Equals(GuiConstants.SdefaultValue.ToString()))
                    {
                        guiradAnalysisChartSP.Series[0].Points.AddXY(series, double.Parse(spRate[series], CrxCommon.nCI));
                        guiradAnalysisChartSP.Series[1].Points.AddXY(series, double.Parse(spRate[series], CrxCommon.nCI));
                    }
                    else
                    {
                        guiradAnalysisChartSP.Series[1].Points.AddXY(series, minValue);
                    }
                }

                if (spRate.Length <= MaxNumberOfPointsForChart)
                {
                    guiradAnalysisChartSP.ChartAreas[0].AxisX.Maximum = spRate.Length;
                }
                else
                {
                    guiradAnalysisChartSP.ChartAreas[0].AxisX.Maximum = MaxNumberOfPointsForChart;
                }
            }
        }

        /** This method plots DpMp trend graph
       * */
        private void PlotDpMpTrendData(CrxStructPWATrendData trendData)
        {
            guiradAnalysisChartDPMP.Series[0].Points.Clear();
            guiradAnalysisChartDPMP.Series[1].Points.Clear();
            guiradAnalysisChartDPMP.Series[2].Points.Clear();
            guiradAnalysisChartDPMP.Series[3].Points.Clear();

            dpRate = trendData.DpValidArrStr.Split(GuiConstants.Separator);
            mpRate = trendData.MpValidArrStr.Split(GuiConstants.Separator);

            double[] tempDouble = CrxDBManager.Instance.CommonStringArrToDoubleArr((trendData.DpValidArrStr + GuiConstants.Separator 
                + trendData.MpValidArrStr).Split(GuiConstants.Separator));

            double minValue;
            setChartMinMaxForYAxis(guiradAnalysisChartDPMP, tempDouble, out minValue);

            // plot Dp & Mp series
            if (dpRate.Length > 0 && mpRate.Length > 0)
            {
                for (int series = 0; series < mpRate.Length && series < dpRate.Length; series++)
                {
                    // check if value is 9999
                    if (!dpRate[series].Equals(GuiConstants.SdefaultValue.ToString()))
                    {
                        guiradAnalysisChartDPMP.Series[0].Points.AddXY(series, double.Parse(dpRate[series], CrxCommon.nCI));
                        guiradAnalysisChartDPMP.Series[1].Points.AddXY(series, double.Parse(dpRate[series], CrxCommon.nCI));
                    }
                    else
                    {
                        guiradAnalysisChartDPMP.Series[1].Points.AddXY(series, minValue);
                    }

                    if (!mpRate[series].Equals(GuiConstants.SdefaultValue.ToString()))
                    {
                        guiradAnalysisChartDPMP.Series[2].Points.AddXY(series, double.Parse(mpRate[series], CrxCommon.nCI));
                        guiradAnalysisChartDPMP.Series[3].Points.AddXY(series, double.Parse(mpRate[series], CrxCommon.nCI));
                    }
                    else
                    {
                        guiradAnalysisChartDPMP.Series[3].Points.AddXY(series, minValue);
                    }
                }

                if (dpRate.Length <= MaxNumberOfPointsForChart)
                {
                    guiradAnalysisChartDPMP.ChartAreas[0].AxisX.Maximum = dpRate.Length;
                }
                else
                {
                    guiradAnalysisChartDPMP.ChartAreas[0].AxisX.Maximum = MaxNumberOfPointsForChart;
                }
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
                          
                // check if value is within min & max limits               
                GetValidationForHeight(heightinches);
                GuiCommon.bizPwaobject.heightAndWeight.heightInInches = heightinches == 0 ? GuiConstants.DefaultValue : ushort.Parse(heightinches.ToString());
            }
            else
            {
                GuiCommon.bizPwaobject.heightAndWeight.heightInCentimetres = string.IsNullOrEmpty(guiradtxtReportHeight.Text.Trim()) ? GuiConstants.DefaultValue : ushort.Parse(guiradtxtReportHeight.Text.Trim());
                isHeightOutsideIntegerLimits = false;
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
                crxPwa.HeightInCentimetres = GuiCommon.bizPwaobject.heightAndWeight.heightInCentimetres == GuiConstants.SdefaultValue ? GuiConstants.SdefaultValue : short.Parse(GuiCommon.bizPwaobject.heightAndWeight.heightInCentimetres.ToString());
            }
            else
            {
                crxPwa.HeightInCentimetres = string.IsNullOrEmpty(guiradtxtReportHeight.Text.Trim()) ? GuiConstants.SdefaultValue : short.Parse(guiradtxtReportHeight.Text.Trim());
                crxPwa.HeightInInches = GuiCommon.bizPwaobject.heightAndWeight.heightInInches == GuiConstants.SdefaultValue ? GuiConstants.SdefaultValue : short.Parse(GuiCommon.bizPwaobject.heightAndWeight.heightInInches.ToString());
            }
        }

        /** Below function restrict user from adding invalid value for the height
         */
        private void GetValidationForHeight(int heightValue)
        {
            if (heightValue > short.MaxValue || heightValue < 0)
            {
                string field = objValidation.GetLabelText(guiradtxtReportHeight.Tag.ToString());
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

        /** This method validates session data
        * */
        bool ValidateSession(CrxStructPWAMeasurementData crxPwa)
        {
            GuiCommon.bizPwaobject.Sp = string.IsNullOrEmpty(guiradlblreportSPdisplay.Text.Trim()) ? GuiConstants.DefaultValue : float.Parse(guiradlblreportSPdisplay.Text.Trim());
            GuiCommon.bizPwaobject.Dp = string.IsNullOrEmpty(guiradlblreportDPdisplay.Text.Trim()) ? GuiConstants.DefaultValue : float.Parse(guiradlblreportDPdisplay.Text.Trim());
            GuiCommon.bizPwaobject.MeasureType = PWA_MEASURE_TYPE.PWA_RADIAL;
            CalculateHeightAndWeightToValidateSession();
            GuiCommon.bizPwaobject.notes = guiradtxtMedicationNotesValue.Text.Trim();

            if (!isHeightOutsideIntegerLimits)
            {
                bool isValidate = GuiCommon.bizPwaobject.Validate();
                if (isValidate)
                {
                    GetValidationForHeight(int.Parse(GuiCommon.bizPwaobject.heightAndWeight.heightInCentimetres.ToString()));
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

                crxPwa.Interpretation = guiradtxtInterpretation.Text.Trim();
                crxPwa.Notes = guiradtxtMedicationNotesValue.Text.Trim();

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
            SaveChangesOnEdit();
        }      

        /** This event gets fired when focus is moved from height in inches text box.
       * It checks if the value entered in textbox is within valid range and shows error accordingly
       * */
        private void guiradtxtReportHeightInches_Leave(object sender, EventArgs e)
        {
            objValidation.CheckIntegerFieldLimitsRemoveInvalidValue(guiradtxtReportHeightInches);
        }

        /** This event gets fired when focus is moved from height in centimeteres & height in feet text box.
       * It checks if the value entered in textbox is within valid range and shows error accordingly
       * */
        private void guiradtxtReportHeight_Leave(object sender, EventArgs e)
        {
            objValidation.CheckIntegerFieldLimitsRemoveInvalidValue(guiradtxtReportHeight);
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

            PWACommonReportData.RptPatientDobValue = patientObj.dateOfBirth.ToShortDateString();

            PWACommonReportData.RptPatientAgeGender = string.Format("{0}, {1}", oMsgMgr.GetMessage(CrxStructCommonResourceMsg.RptAgeTitle), oMsgMgr.GetMessage(CrxStructCommonResourceMsg.LblReportGender));

            PWACommonReportData.RptPatientAgeGenderValue = string.Format("{0}, {1}", GuiCommon.bizPwaobject.patientAge.ToString(), oMsgMgr.GetMessage(patientObj.gender));

            PWACommonReportData.RptPatientAge = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.LblReportAge);
            
            PWACommonReportData.RptPatientAgeValue = GuiCommon.bizPwaobject.patientAge.ToString();
            
            PWACommonReportData.RptPatientGender = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.LblReportGender);
            
            PWACommonReportData.RptPatientGenderValue = oMsgMgr.GetMessage(patientObj.gender);
            
            PWACommonReportData.RptStudyDataHeader = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.RptMeasurementData);

            PWACommonReportData.RptPatientAssessment = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.RptDateAndTime);

            // GuiCommon.PwvCurrentStudyDatetime;
            PWACommonReportData.RptPatientAssessmentValue = string.Format("{0:g}", Convert.ToDateTime(GuiCommon.PwaCurrentStudyDatetime)); 

            PWACommonReportData.RptPatientBP = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.RptBrachialBp);

            PWACommonReportData.RptPatientBPValue = SetBPForPWAReport();

            PWACommonReportData.RptPatientHeight = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.LblHeight);

            PWACommonReportData.RptPatientHeightValue = SetPatientHeightValue();

            // PWACommonReportData.RptDatabaseVersionTitle = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.RptDatabaseVersionTitle);
            // PWACommonReportData.RptDatabaseVersionValue = GuiCommon.bizPwaobject.dataRevision.ToString();// string.Empty;
            PWACommonReportData.RptGroupNameTitle = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.LblGroup);

            PWACommonReportData.RptGroupNameValue = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.EnvClinicalText);

            PWACommonReportData.RptWaveformPlotTitle = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.RptWaveformPlotTitle);

            PWACommonReportData.RptWaveformPlotValue = string.Empty;

            PWACommonReportData.RptNumberOfWaveformsTitle = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.RptNumberOfWaveformsTitle);

            // PWACommonReportData.RptNumberOfWaveformsValue = string.Empty;
            PWACommonReportData.RptQualityControlTitle = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.RptQualityControlTitle);

            PWACommonReportData.RptQualityControlValue = crxPwaCuffData.OperatorIndex.ToString();

            PWACommonReportData.RptSignatureTitle = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.RptSignatureTitle);

            PWACommonReportData.RptPhysicianTitle = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.RptPhysicianTitle);

            PWACommonReportData.RptSimulationModeTitle = crxPwaData.Simulation.Equals(true) ? oMsgMgr.GetMessage(CrxStructCommonResourceMsg.RptSimulationModeTitle) : string.Empty;

            PWACommonReportData.RptNoteTitle = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.RptNoteTitle);

            PWACommonReportData.RptNoteValue = GuiCommon.InConclusiveMessageForPwaCapture.Equals(string.Empty) ? string.Empty : GuiCommon.InConclusiveMessageForPwaCapture;
        }

        /** This method fille structure "PWAClinicalReport" with the values to be printed on PWV report.
       * This values will be used in Crystal Reports.
       * */
        private void FillStructForPWAClinicalReport()
        {
            PWAClinicalReportData.RptClinicalParametersTitle = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.RptClinicalParametersTitle);

            PWAClinicalReportData.RptCentralPressureWaveformTitle = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.RptCentralPressureWaveformTitle);

            // PWAClinicalReportData.RptInterpretationTitle = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.RptInterpretationTitle);
            PWAClinicalReportData.RptInterpretationTitle = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.LblNotes);

            PWAClinicalReportData.RptInterpretationValue = crxPwaData.Notes;

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

         /** This method fill structure "PWAPatientReport" with the values to be printed on PWV report.
       * This values will be used in Crystal Reports.
       * */
        private void FillStructForPWAPatientReport()
        {
            PWAClinicalReportData.RptSPAroticValue = crxPwaData.C_Sp.Equals(GuiConstants.DefaultValue) ? string.Empty : Math.Round(crxPwaData.C_Sp).ToString();
            PWAClinicalReportData.RptDPAroticValue = crxPwaData.C_Dp.Equals(GuiConstants.DefaultValue) ? string.Empty : Math.Round(crxPwaData.C_Dp).ToString();
            RptPwaFillAroticValue();
            PWAClinicalReportData.RptHRAroticValue = crxPwaData.HR.Equals(GuiConstants.DefaultValue) ? string.Empty : Math.Round(crxPwaData.HR).ToString();
            PWAPatientReportData.RptPatientAssessment = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.RptDateAndMeasurement);
        }

        /** This method "SetBPForPWAReport" will return string for BP values
      * This values will be used in Crystal Reports.
      * */
        private string SetBPForPWAReport()
        {
            string blpValue = string.Empty;
            blpValue = string.Format("{0} {1}", GuiCommon.bizPwaobject.bloodPressure.SP.Reading.ToString() + oMsgMgr.GetMessage(CrxStructCommonResourceMsg.GuiDisplaySlash) + GuiCommon.bizPwaobject.bloodPressure.DP.Reading.ToString(), oMsgMgr.GetMessage(CrxStructCommonResourceMsg.UnitsPressureMmhg));
            return blpValue;
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

        /** This event "guiPwaPatientReport_Click" is called when user click "Patient" print button 
      * */
        private void guiPwaPatientReport_Click(object sender, EventArgs e)
        {
            PWACommonReportData.RptPrintType = CrxStructCommonResourceMsg.PwaPatientReport;
            FillStructForPWACommonReport();
            FillStructForPWAPatientReport();
            PWAPatientPreview rpPreview = new PWAPatientPreview();
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

        /** This method "SetPatientHeightValue" will return string for filling Height Weight values
      * This values will be used in Crystal Reports.
      * */
        private string SetPatientHeightValue()
        {
            int heightInInches = int.Parse(GuiCommon.bizPwaobject.heightAndWeight.heightInInches.ToString()) % 12;

            int heigthInFeet = int.Parse(GuiCommon.bizPwaobject.heightAndWeight.heightInInches.ToString()) / 12;

            string heightValue = CrxConfigManager.Instance.GeneralSettings.HeightandWeightUnit.Equals((int)CrxGenPwvValue.CrxGenHeightWeightMetric) ?
                GuiCommon.bizPwaobject.heightAndWeight.heightInCentimetres.Equals(GuiConstants.DefaultValue) ? string.Empty : GuiCommon.bizPwaobject.heightAndWeight.heightInCentimetres.ToString() + " " + oMsgMgr.GetMessage(CrxStructCommonResourceMsg.Cm)
                : GuiCommon.bizPwaobject.heightAndWeight.heightInInches.Equals(GuiConstants.DefaultValue) ? string.Empty : heigthInFeet.ToString() + " " + oMsgMgr.GetMessage(CrxStructCommonResourceMsg.Feet) + " , " + heightInInches + " " + oMsgMgr.GetMessage(CrxStructCommonResourceMsg.Inch);            

            return heightValue;
        }

        private void guipnlSliderControls_Paint(object sender, PaintEventArgs e)
        {
            ControlPaint.DrawBorder(e.Graphics, this.guipnlSliderControls.DisplayRectangle, System.Drawing.Color.WhiteSmoke, ButtonBorderStyle.Solid); 
        }

        private void guipnlAverageAorticChart_Paint(object sender, PaintEventArgs e)
        {
            ControlPaint.DrawBorder(e.Graphics, this.guipnlAverageAorticChart.DisplayRectangle, System.Drawing.Color.WhiteSmoke, ButtonBorderStyle.Solid); 
        }

        /** This method is used to bind custom labels for X-Axis for Analysis trend charts
        * */
        private void BindCustomLabelForTrendCharts(int seriesLength)
        {
            Font labelFontMax = new Font(ConfigurationManager.AppSettings[GuiConstants.AppConfigParams.AnalysisFontName.ToString()].ToString(), float.Parse(ConfigurationManager.AppSettings[GuiConstants.AppConfigParams.AnalysisFontMax.ToString()].ToString()));  // sets font max size for analysis chart x axis labels
            Font labelFontMin = new Font(ConfigurationManager.AppSettings[GuiConstants.AppConfigParams.AnalysisFontName.ToString()].ToString(), float.Parse(ConfigurationManager.AppSettings[GuiConstants.AppConfigParams.AnalysisFontMin.ToString()].ToString())); // sets font min size for analysis chart x axis labels
            guiradLargeChart.ChartAreas[0].AxisX.CustomLabels.Clear();
            guiradLargeChart.ChartAreas[0].AxisX.LabelStyle.Angle = LblHorizontalAngle;
            guiradLargeChart.ChartAreas[0].AxisX.LabelStyle.Font = labelFontMax;

                for (int hrseries1 = 0; hrseries1 < seriesLength; hrseries1++)
                {
                    // if (hrseries1 > (5 * labelInterval))
                    if (hrseries1 == 1)
                    {
                        guiradLargeChart.ChartAreas[0].AxisX.LabelStyle.Font = new Font(ConfigurationManager.AppSettings[GuiConstants.AppConfigParams.AnalysisFontName.ToString()].ToString(), float.Parse(ConfigurationManager.AppSettings[GuiConstants.AppConfigParams.AnalysisFontMax.ToString()].ToString()) - 2);
                    }
                    else if (hrseries1 == 2)
                    {
                        guiradLargeChart.ChartAreas[0].AxisX.LabelStyle.Font = new Font(ConfigurationManager.AppSettings[GuiConstants.AppConfigParams.AnalysisFontName.ToString()].ToString(), float.Parse(ConfigurationManager.AppSettings[GuiConstants.AppConfigParams.AnalysisFontMin.ToString()].ToString()) + 1);
                    }
                    else if (hrseries1 >= 3)
                    {
                        guiradLargeChart.ChartAreas[0].AxisX.LabelStyle.Font = new Font(ConfigurationManager.AppSettings[GuiConstants.AppConfigParams.AnalysisFontName.ToString()].ToString(), float.Parse(ConfigurationManager.AppSettings[GuiConstants.AppConfigParams.AnalysisFontMin.ToString()].ToString()) + 1);
                        guiradLargeChart.ChartAreas[0].AxisX.LabelStyle.Angle = LblVerticalAngle;
                    }

                    if (seriesLength > 09 && seriesLength <= 19)
                    {
                        if (hrseries1 % 2 == 0)
                        {
                            guiradLargeChart.ChartAreas[0].AxisX.CustomLabels.Add(hrseries1 - 1, hrseries1 + 1, string.Format("{0:g}", Convert.ToDateTime(date[hrseries1].ToString())));
                        }
                    }
                    else if (seriesLength > 19)
                    {
                        if (hrseries1 % 3 == 0)
                        {
                            guiradLargeChart.ChartAreas[0].AxisX.CustomLabels.Add(hrseries1 - 1, hrseries1 + 1, string.Format("{0:g}", Convert.ToDateTime(date[hrseries1].ToString())));
                        }
                    }
                    else
                    {
                        guiradLargeChart.ChartAreas[0].AxisX.CustomLabels.Add(hrseries1 - 1, hrseries1 + 1, string.Format("{0:g}", Convert.ToDateTime(date[hrseries1].ToString())));
                    }
                }
        }

        private CrxStructPWAMeasurementData getCrxPWAData(DataSet dsPWA, CrxStructPWAMeasurementData crxPwaData1)
        {
            if (dsPWA.Tables[0].Rows.Count > 0)
            {
                crxPwaData1.AuditChange = DateTime.Parse(dsPWA.Tables[0].Rows[0][(int)CrxDBGetCuffPWAMeasurementDetails.AuditChange].ToString(), CrxCommon.gCI);
                crxPwaData1.Age = short.Parse(dsPWA.Tables[0].Rows[0][(int)CrxDBGetCuffPWAMeasurementDetails.Age].ToString());
                crxPwaData1.BloodPressureRange = dsPWA.Tables[0].Rows[0][(int)CrxDBGetCuffPWAMeasurementDetails.BloodPressureRange].ToString();
                crxPwaData1.BodyMassIndex = float.Parse(dsPWA.Tables[0].Rows[0][(int)CrxDBGetCuffPWAMeasurementDetails.BodyMassIndex].ToString());
                crxPwaData1.C_Agph = float.Parse(dsPWA.Tables[0].Rows[0][(int)CrxDBGetCuffPWAMeasurementDetails.C_Agph].ToString());
                crxPwaData1.C_Ai = float.Parse(dsPWA.Tables[0].Rows[0][(int)CrxDBGetCuffPWAMeasurementDetails.C_Ai].ToString());
                crxPwaData1.C_Al = float.Parse(dsPWA.Tables[0].Rows[0][(int)CrxDBGetCuffPWAMeasurementDetails.C_Al].ToString());
                crxPwaData1.C_Ap = float.Parse(dsPWA.Tables[0].Rows[0][(int)CrxDBGetCuffPWAMeasurementDetails.C_Ap].ToString());
                crxPwaData1.C_Area_Ratio = float.Parse(dsPWA.Tables[0].Rows[0][(int)CrxDBGetCuffPWAMeasurementDetails.C_Area_Ratio].ToString());
                crxPwaData1.C_Ati = float.Parse(dsPWA.Tables[0].Rows[0][(int)CrxDBGetCuffPWAMeasurementDetails.C_Ati].ToString());
                byte[] buffer = (byte[])dsPWA.Tables[0].Rows[0][(int)CrxDBGetCuffPWAMeasurementDetails.C_AV_PULSE];
                int len = buffer.Length / 4;
                crxPwaData1.C_AV_PULSE = dbMagr.CommonByteArrtoFloatArr(len, buffer);
                crxPwaData1.C_Avd = float.Parse(dsPWA.Tables[0].Rows[0][(int)CrxDBGetCuffPWAMeasurementDetails.C_Avd].ToString());
                crxPwaData1.C_Avi = float.Parse(dsPWA.Tables[0].Rows[0][(int)CrxDBGetCuffPWAMeasurementDetails.C_Avi].ToString());
                buffer = (byte[])dsPWA.Tables[0].Rows[0][(int)CrxDBGetCuffPWAMeasurementDetails.C_Backward];
                len = buffer.Length / 4;
                crxPwaData1.C_Backward = dbMagr.CommonByteArrtoFloatArr(len, buffer);
                crxPwaData1.C_Backward_Area = float.Parse(dsPWA.Tables[0].Rows[0][(int)CrxDBGetCuffPWAMeasurementDetails.C_Backward_Area].ToString());
                crxPwaData1.C_Dd = float.Parse(dsPWA.Tables[0].Rows[0][(int)CrxDBGetCuffPWAMeasurementDetails.C_Dd].ToString());
                crxPwaData1.C_DdPeriod = float.Parse(dsPWA.Tables[0].Rows[0][(int)CrxDBGetCuffPWAMeasurementDetails.C_DdPeriod].ToString());
                crxPwaData1.C_Dp = float.Parse(dsPWA.Tables[0].Rows[0][(int)CrxDBGetCuffPWAMeasurementDetails.C_Dp].ToString());
                crxPwaData1.C_Dti = float.Parse(dsPWA.Tables[0].Rows[0][(int)CrxDBGetCuffPWAMeasurementDetails.C_Dti].ToString());
                crxPwaData1.C_EdPeriod = float.Parse(dsPWA.Tables[0].Rows[0][(int)CrxDBGetCuffPWAMeasurementDetails.C_EdPeriod].ToString());
                crxPwaData1.C_Esp = float.Parse(dsPWA.Tables[0].Rows[0][(int)CrxDBGetCuffPWAMeasurementDetails.C_Esp].ToString());
                crxPwaData1.C_FloatSpare1 = float.Parse(dsPWA.Tables[0].Rows[0][(int)CrxDBGetCuffPWAMeasurementDetails.C_FloatSpare1].ToString());
                crxPwaData1.C_FloatSpare2 = float.Parse(dsPWA.Tables[0].Rows[0][(int)CrxDBGetCuffPWAMeasurementDetails.C_FloatSpare2].ToString());
                buffer = (byte[])dsPWA.Tables[0].Rows[0][(int)CrxDBGetCuffPWAMeasurementDetails.C_Typical];
                len = buffer.Length / 4;
                crxPwaData1.C_Typical = dbMagr.CommonByteArrtoFloatArr(len, buffer);
                buffer = (byte[])dsPWA.Tables[0].Rows[0][(int)CrxDBGetCuffPWAMeasurementDetails.C_Forward];
                len = buffer.Length / 4;
                crxPwaData1.C_Forward = dbMagr.CommonByteArrtoFloatArr(len, buffer);
                crxPwaData1.C_Forward_Area = float.Parse(dsPWA.Tables[0].Rows[0][(int)CrxDBGetCuffPWAMeasurementDetails.C_Forward_Area].ToString());
                crxPwaData1.C_IntSpare1 = int.Parse(dsPWA.Tables[0].Rows[0][(int)CrxDBGetCuffPWAMeasurementDetails.C_IntSpare1].ToString());
                crxPwaData1.C_IntSpare2 = int.Parse(dsPWA.Tables[0].Rows[0][(int)CrxDBGetCuffPWAMeasurementDetails.C_IntSpare2].ToString());
                crxPwaData1.C_Math_Params = int.Parse(dsPWA.Tables[0].Rows[0][(int)CrxDBGetCuffPWAMeasurementDetails.C_Math_Params].ToString());
                crxPwaData1.C_Meanp = float.Parse(dsPWA.Tables[0].Rows[0][(int)CrxDBGetCuffPWAMeasurementDetails.C_Meanp].ToString());
                crxPwaData1.C_MemSpare1 = float.Parse(dsPWA.Tables[0].Rows[0][(int)CrxDBGetCuffPWAMeasurementDetails.C_MemSpare1].ToString());
                crxPwaData1.C_MemSpare2 = float.Parse(dsPWA.Tables[0].Rows[0][(int)CrxDBGetCuffPWAMeasurementDetails.C_MemSpare2].ToString());
                crxPwaData1.C_Mpd = float.Parse(dsPWA.Tables[0].Rows[0][(int)CrxDBGetCuffPWAMeasurementDetails.C_Mpd].ToString());
                crxPwaData1.C_Mps = float.Parse(dsPWA.Tables[0].Rows[0][(int)CrxDBGetCuffPWAMeasurementDetails.C_Mps].ToString());
                crxPwaData1.C_Ole_Spare = dsPWA.Tables[0].Rows[0][(int)CrxDBGetCuffPWAMeasurementDetails.C_Ole_Spare].ToString();
                buffer = (byte[])dsPWA.Tables[0].Rows[0][(int)CrxDBGetCuffPWAMeasurementDetails.C_ONSETS];
                len = buffer.Length / 2;
                crxPwaData1.C_ONSETS = dbMagr.CommonByteArrtoShortArr(buffer, len);               
                crxPwaData1.C_P1 = float.Parse(dsPWA.Tables[0].Rows[0][(int)CrxDBGetCuffPWAMeasurementDetails.C_P1].ToString());
                crxPwaData1.C_P1_Height = float.Parse(dsPWA.Tables[0].Rows[0][(int)CrxDBGetCuffPWAMeasurementDetails.C_P1_Height].ToString());
                crxPwaData1.C_P2 = float.Parse(dsPWA.Tables[0].Rows[0][(int)CrxDBGetCuffPWAMeasurementDetails.C_P2].ToString());
                crxPwaData1.C_Period = float.Parse(dsPWA.Tables[0].Rows[0][(int)CrxDBGetCuffPWAMeasurementDetails.C_Period].ToString());
                crxPwaData1.C_Ph = float.Parse(dsPWA.Tables[0].Rows[0][(int)CrxDBGetCuffPWAMeasurementDetails.C_Ph].ToString());
                crxPwaData1.C_Pptt = float.Parse(dsPWA.Tables[0].Rows[0][(int)CrxDBGetCuffPWAMeasurementDetails.C_Pptt].ToString());
                crxPwaData1.C_Pulse_Ratio = float.Parse(dsPWA.Tables[0].Rows[0][(int)CrxDBGetCuffPWAMeasurementDetails.C_Pulse_Ratio].ToString());
                crxPwaData1.C_Pwv = float.Parse(dsPWA.Tables[0].Rows[0][(int)CrxDBGetCuffPWAMeasurementDetails.C_Pwv].ToString());
                crxPwaData1.C_Qc_Other1 = float.Parse(dsPWA.Tables[0].Rows[0][(int)CrxDBGetCuffPWAMeasurementDetails.C_Qc_Other1].ToString());
                crxPwaData1.C_Qc_Other2 = float.Parse(dsPWA.Tables[0].Rows[0][(int)CrxDBGetCuffPWAMeasurementDetails.C_Qc_Other2].ToString());
                crxPwaData1.C_Qc_Other3 = float.Parse(dsPWA.Tables[0].Rows[0][(int)CrxDBGetCuffPWAMeasurementDetails.C_Qc_Other3].ToString());
                crxPwaData1.C_Qc_Other4 = float.Parse(dsPWA.Tables[0].Rows[0][(int)CrxDBGetCuffPWAMeasurementDetails.C_Qc_Other4].ToString());
                crxPwaData1.C_Quality_T1 = int.Parse(dsPWA.Tables[0].Rows[0][(int)CrxDBGetCuffPWAMeasurementDetails.C_Quality_T1].ToString());
                crxPwaData1.C_Quality_T2 = int.Parse(dsPWA.Tables[0].Rows[0][(int)CrxDBGetCuffPWAMeasurementDetails.C_Quality_T2].ToString());
                buffer = (byte[])dsPWA.Tables[0].Rows[0][(int)CrxDBGetCuffPWAMeasurementDetails.C_RAW_SIGNALS];
                len = buffer.Length / 4;
                crxPwaData1.C_RAW_SIGNALS = dbMagr.CommonByteArrtoFloatArr(len, buffer);
                buffer = (byte[])dsPWA.Tables[0].Rows[0][(int)CrxDBGetCuffPWAMeasurementDetails.C_ResemblePulse];
                len = buffer.Length / 4;
                crxPwaData1.C_ResemblePulse = dbMagr.CommonByteArrtoFloatArr(len, buffer);
                crxPwaData1.C_Sp = float.Parse(dsPWA.Tables[0].Rows[0][(int)CrxDBGetCuffPWAMeasurementDetails.C_Sp].ToString());
                crxPwaData1.C_Svi = float.Parse(dsPWA.Tables[0].Rows[0][(int)CrxDBGetCuffPWAMeasurementDetails.C_Svi].ToString());
                crxPwaData1.C_T1 = float.Parse(dsPWA.Tables[0].Rows[0][(int)CrxDBGetCuffPWAMeasurementDetails.C_T1].ToString());
                crxPwaData1.C_T1ED = float.Parse(dsPWA.Tables[0].Rows[0][(int)CrxDBGetCuffPWAMeasurementDetails.C_T1ED].ToString());
                crxPwaData1.C_T1i = float.Parse(dsPWA.Tables[0].Rows[0][(int)CrxDBGetCuffPWAMeasurementDetails.C_T1i].ToString());
                crxPwaData1.C_T1m = float.Parse(dsPWA.Tables[0].Rows[0][(int)CrxDBGetCuffPWAMeasurementDetails.C_T1m].ToString());
                crxPwaData1.C_T1other = float.Parse(dsPWA.Tables[0].Rows[0][(int)CrxDBGetCuffPWAMeasurementDetails.C_T1other].ToString());
                crxPwaData1.C_T1r = float.Parse(dsPWA.Tables[0].Rows[0][(int)CrxDBGetCuffPWAMeasurementDetails.C_T1r].ToString());
                crxPwaData1.C_T2 = float.Parse(dsPWA.Tables[0].Rows[0][(int)CrxDBGetCuffPWAMeasurementDetails.C_T2].ToString());
                crxPwaData1.C_T2ED = float.Parse(dsPWA.Tables[0].Rows[0][(int)CrxDBGetCuffPWAMeasurementDetails.C_T2ED].ToString());
                crxPwaData1.C_T2i = float.Parse(dsPWA.Tables[0].Rows[0][(int)CrxDBGetCuffPWAMeasurementDetails.C_T2i].ToString());
                crxPwaData1.C_T2M = float.Parse(dsPWA.Tables[0].Rows[0][(int)CrxDBGetCuffPWAMeasurementDetails.C_T2M].ToString());
                crxPwaData1.C_T2Other = float.Parse(dsPWA.Tables[0].Rows[0][(int)CrxDBGetCuffPWAMeasurementDetails.C_T2Other].ToString());
                crxPwaData1.C_T2R = float.Parse(dsPWA.Tables[0].Rows[0][(int)CrxDBGetCuffPWAMeasurementDetails.C_T2R].ToString());
                buffer = (byte[])dsPWA.Tables[0].Rows[0][(int)CrxDBGetCuffPWAMeasurementDetails.C_TRIGS];
                len = buffer.Length / 2;
                crxPwaData1.C_TRIGS = dbMagr.CommonByteArrtoShortArr(buffer, len);
                crxPwaData1.C_Tti = float.Parse(dsPWA.Tables[0].Rows[0][(int)CrxDBGetCuffPWAMeasurementDetails.C_Tti].ToString());
                buffer = (byte[])dsPWA.Tables[0].Rows[0][(int)CrxDBGetCuffPWAMeasurementDetails.C_Uncal_Av];
                len = buffer.Length / 4;
                crxPwaData1.C_Uncal_Av = dbMagr.CommonByteArrtoFloatArr(len, buffer);
                crxPwaData1.CalcED = float.Parse(dsPWA.Tables[0].Rows[0][(int)CrxDBGetCuffPWAMeasurementDetails.CalcED].ToString());
                crxPwaData1.CalDP = int.Parse(dsPWA.Tables[0].Rows[0][(int)CrxDBGetCuffPWAMeasurementDetails.CalDP].ToString());
                crxPwaData1.CalMP = int.Parse(dsPWA.Tables[0].Rows[0][(int)CrxDBGetCuffPWAMeasurementDetails.CalMP].ToString());
                crxPwaData1.CalSP = int.Parse(dsPWA.Tables[0].Rows[0][(int)CrxDBGetCuffPWAMeasurementDetails.CalSP].ToString());
                crxPwaData1.CaptureInput = short.Parse(dsPWA.Tables[0].Rows[0][(int)CrxDBGetCuffPWAMeasurementDetails.CaptureInput].ToString());
                crxPwaData1.CaptureTime = short.Parse(dsPWA.Tables[0].Rows[0][(int)CrxDBGetCuffPWAMeasurementDetails.CaptureTime].ToString());
                crxPwaData1.DataRev = int.Parse(dsPWA.Tables[0].Rows[0][(int)CrxDBGetCuffPWAMeasurementDetails.DataRev].ToString());
                crxPwaData1.DP = short.Parse(dsPWA.Tables[0].Rows[0][(int)CrxDBGetCuffPWAMeasurementDetails.DP].ToString());
                crxPwaData1.ED = float.Parse(dsPWA.Tables[0].Rows[0][(int)CrxDBGetCuffPWAMeasurementDetails.ED].ToString());
                crxPwaData1.EDMax = int.Parse(dsPWA.Tables[0].Rows[0][(int)CrxDBGetCuffPWAMeasurementDetails.EDMax].ToString());
                crxPwaData1.EDMin = int.Parse(dsPWA.Tables[0].Rows[0][(int)CrxDBGetCuffPWAMeasurementDetails.EDMin].ToString());
                crxPwaData1.EDOther = int.Parse(dsPWA.Tables[0].Rows[0][(int)CrxDBGetCuffPWAMeasurementDetails.EDOther].ToString());
                crxPwaData1.ExpPulseUpSampleRate = int.Parse(dsPWA.Tables[0].Rows[0][(int)CrxDBGetCuffPWAMeasurementDetails.ExpPulseUpSampleRate].ToString());
                crxPwaData1.FloatSpare1 = float.Parse(dsPWA.Tables[0].Rows[0][(int)CrxDBGetCuffPWAMeasurementDetails.FloatSpare1].ToString());
                crxPwaData1.Flow = int.Parse(dsPWA.Tables[0].Rows[0][(int)CrxDBGetCuffPWAMeasurementDetails.Flow].ToString());
                crxPwaData1.GroupIdentifier = int.Parse(dsPWA.Tables[0].Rows[0][(int)CrxDBGetCuffPWAMeasurementDetails.GroupIdentifier].ToString());
                crxPwaData1.HeightInCentimetres = short.Parse(dsPWA.Tables[0].Rows[0][(int)CrxDBGetCuffPWAMeasurementDetails.HeightInCentimetres].ToString());
                crxPwaData1.HeightInInches = short.Parse(dsPWA.Tables[0].Rows[0][(int)CrxDBGetCuffPWAMeasurementDetails.HeightInInches].ToString());
                crxPwaData1.HR = float.Parse(dsPWA.Tables[0].Rows[0][(int)CrxDBGetCuffPWAMeasurementDetails.HR].ToString());
                crxPwaData1.AuditFlag = int.Parse(dsPWA.Tables[0].Rows[0][(int)CrxDBGetCuffPWAMeasurementDetails.AuditFlag].ToString());
                crxPwaData1.Medication = dsPWA.Tables[0].Rows[0][(int)CrxDBGetCuffPWAMeasurementDetails.Medication].ToString();
                crxPwaData1.Interpretation = dsPWA.Tables[0].Rows[0][(int)CrxDBGetCuffPWAMeasurementDetails.Interpretation].ToString();
                crxPwaData1.AuditReason = dsPWA.Tables[0].Rows[0][(int)CrxDBGetCuffPWAMeasurementDetails.AuditReason].ToString();
                crxPwaData1.Message = dsPWA.Tables[0].Rows[0][(int)CrxDBGetCuffPWAMeasurementDetails.Message].ToString();
                crxPwaData1.MP = short.Parse(dsPWA.Tables[0].Rows[0][(int)CrxDBGetCuffPWAMeasurementDetails.MP].ToString());
                crxPwaData1.Notes = dsPWA.Tables[0].Rows[0][(int)CrxDBGetCuffPWAMeasurementDetails.Notes].ToString();
                crxPwaData1.Operator = dsPWA.Tables[0].Rows[0][(int)CrxDBGetCuffPWAMeasurementDetails.Operator].ToString();
                crxPwaData1.PatientNumberInternal = int.Parse(dsPWA.Tables[0].Rows[0][(int)CrxDBGetCuffPWAMeasurementDetails.PatientNumberInternal].ToString());
                crxPwaData1.PWA_Id = short.Parse(dsPWA.Tables[0].Rows[0][(int)CrxDBGetCuffPWAMeasurementDetails.PWA_Id].ToString());
                crxPwaData1.QualityED = int.Parse(dsPWA.Tables[0].Rows[0][(int)CrxDBGetCuffPWAMeasurementDetails.QualityED].ToString());
                crxPwaData1.SampleRate = int.Parse(dsPWA.Tables[0].Rows[0][(int)CrxDBGetCuffPWAMeasurementDetails.SampleRate].ToString());
                crxPwaData1.SignalUpSampleRate = int.Parse(dsPWA.Tables[0].Rows[0][(int)CrxDBGetCuffPWAMeasurementDetails.SignalUpSampleRate].ToString());
                crxPwaData1.Simulation = bool.Parse(dsPWA.Tables[0].Rows[0][(int)CrxDBGetCuffPWAMeasurementDetails.Simulation].ToString());
                crxPwaData1.SP = short.Parse(dsPWA.Tables[0].Rows[0][(int)CrxDBGetCuffPWAMeasurementDetails.SP].ToString());
                crxPwaData1.StudyDateTime = DateTime.Parse(dsPWA.Tables[0].Rows[0][(int)CrxDBGetCuffPWAMeasurementDetails.StudyDateTime].ToString());
                crxPwaData1.SubType = dsPWA.Tables[0].Rows[0][(int)CrxDBGetCuffPWAMeasurementDetails.SubType].ToString();
                crxPwaData1.SystemIdentifier = int.Parse(dsPWA.Tables[0].Rows[0][(int)CrxDBGetCuffPWAMeasurementDetails.SystemIdentifier].ToString());
                crxPwaData1.Units = dsPWA.Tables[0].Rows[0][(int)CrxDBGetCuffPWAMeasurementDetails.Units].ToString();
                crxPwaData1.WeightInKilograms = short.Parse(dsPWA.Tables[0].Rows[0][(int)CrxDBGetCuffPWAMeasurementDetails.WeightInKilograms].ToString());
                crxPwaData1.WeightInPounds = short.Parse(dsPWA.Tables[0].Rows[0][(int)CrxDBGetCuffPWAMeasurementDetails.WeightInPounds].ToString());
            }

            return crxPwaData1;
        }

        private CrxStructCuffPWAMeasurementData getCrxPWACuffData(DataSet dsPWA, CrxStructCuffPWAMeasurementData crxPwaCuffData1)
        {
            if (dsPWA.Tables[0].Rows.Count > 0)
            {
                byte[] buffer = (byte[])dsPWA.Tables[0].Rows[0][(int)CrxDBGetCuffPWAMeasurementDetails.P_AV_PULSE];
                int len = buffer.Length / 4;               
                crxPwaCuffData1.P_AV_PULSE = dbMagr.CommonByteArrtoFloatArr(len, buffer);
                crxPwaCuffData1.P_DP = float.Parse(dsPWA.Tables[0].Rows[0][(int)CrxDBGetCuffPWAMeasurementDetails.P_DP].ToString());
                crxPwaCuffData1.P_FLOATSPARE1 = float.Parse(dsPWA.Tables[0].Rows[0][(int)CrxDBGetCuffPWAMeasurementDetails.P_FLOATSPARE1].ToString());
                crxPwaCuffData1.P_FLOATSPARE2 = float.Parse(dsPWA.Tables[0].Rows[0][(int)CrxDBGetCuffPWAMeasurementDetails.P_FLOATSPARE2].ToString());
                crxPwaCuffData1.P_INTSPARE1 = int.Parse(dsPWA.Tables[0].Rows[0][(int)CrxDBGetCuffPWAMeasurementDetails.P_INTSPARE1].ToString());
                crxPwaCuffData1.P_INTSPARE2 = int.Parse(dsPWA.Tables[0].Rows[0][(int)CrxDBGetCuffPWAMeasurementDetails.P_INTSPARE2].ToString());
                crxPwaCuffData1.P_MATH_PARAMS = int.Parse(dsPWA.Tables[0].Rows[0][(int)CrxDBGetCuffPWAMeasurementDetails.P_MATH_PARAMS].ToString());
                crxPwaCuffData1.P_MAX_DPDT = float.Parse(dsPWA.Tables[0].Rows[0][(int)CrxDBGetCuffPWAMeasurementDetails.P_MAX_DPDT].ToString());
                crxPwaCuffData1.P_MEANP = float.Parse(dsPWA.Tables[0].Rows[0][(int)CrxDBGetCuffPWAMeasurementDetails.P_MEANP].ToString());
                crxPwaCuffData1.P_MEMSPARE1 = float.Parse(dsPWA.Tables[0].Rows[0][(int)CrxDBGetCuffPWAMeasurementDetails.P_MEMSPARE1].ToString());
                crxPwaCuffData1.P_MEMSPARE2 = float.Parse(dsPWA.Tables[0].Rows[0][(int)CrxDBGetCuffPWAMeasurementDetails.P_MEMSPARE2].ToString());
                crxPwaCuffData1.P_NOISE_FACTOR = int.Parse(dsPWA.Tables[0].Rows[0][(int)CrxDBGetCuffPWAMeasurementDetails.P_NOISE_FACTOR].ToString());
                crxPwaCuffData1.P_OLE_SPARE = dsPWA.Tables[0].Rows[0][(int)CrxDBGetCuffPWAMeasurementDetails.P_OLE_SPARE].ToString();
                buffer = (byte[])dsPWA.Tables[0].Rows[0][(int)CrxDBGetCuffPWAMeasurementDetails.P_ONSETS];
                len = buffer.Length / 2;
                crxPwaCuffData1.P_ONSETS = dbMagr.CommonByteArrtoShortArr(buffer, len);
                crxPwaCuffData1.P_QC_DV = float.Parse(dsPWA.Tables[0].Rows[0][(int)CrxDBGetCuffPWAMeasurementDetails.P_QC_DV].ToString());
                crxPwaCuffData1.QC_Scale = float.Parse(dsPWA.Tables[0].Rows[0][(int)CrxDBGetCuffPWAMeasurementDetails.QC_Scale].ToString());
                crxPwaCuffData1.QC_ShapeDeviation = float.Parse(dsPWA.Tables[0].Rows[0][(int)CrxDBGetCuffPWAMeasurementDetails.QC_ShapeDeviation].ToString());
                crxPwaCuffData1.P_QC_OTHER3 = float.Parse(dsPWA.Tables[0].Rows[0][(int)CrxDBGetCuffPWAMeasurementDetails.P_QC_OTHER3].ToString());
                crxPwaCuffData1.OperatorIndex = float.Parse(dsPWA.Tables[0].Rows[0][(int)CrxDBGetCuffPWAMeasurementDetails.OperatorIndex].ToString());
                crxPwaCuffData1.P_QC_PH = float.Parse(dsPWA.Tables[0].Rows[0][(int)CrxDBGetCuffPWAMeasurementDetails.P_QC_PH].ToString());
                crxPwaCuffData1.P_QC_PHV = float.Parse(dsPWA.Tables[0].Rows[0][(int)CrxDBGetCuffPWAMeasurementDetails.P_QC_PHV].ToString());
                crxPwaCuffData1.P_QC_PLV = float.Parse(dsPWA.Tables[0].Rows[0][(int)CrxDBGetCuffPWAMeasurementDetails.P_QC_PLV].ToString());
                buffer = (byte[])dsPWA.Tables[0].Rows[0][(int)CrxDBGetCuffPWAMeasurementDetails.P_RAW_SIGNALS];
                len = buffer.Length / 4;
                crxPwaCuffData1.P_RAW_SIGNALS = dbMagr.CommonByteArrtoFloatArr(len, buffer);
                buffer = (byte[])dsPWA.Tables[0].Rows[0][(int)CrxDBGetCuffPWAMeasurementDetails.P_ResemblePulse];
                len = buffer.Length / 4;
                crxPwaCuffData1.P_ResemblePulse = dbMagr.CommonByteArrtoFloatArr(len, buffer);
                crxPwaCuffData1.P_SP = float.Parse(dsPWA.Tables[0].Rows[0][(int)CrxDBGetCuffPWAMeasurementDetails.P_SP].ToString());
                crxPwaCuffData1.P_T1I = float.Parse(dsPWA.Tables[0].Rows[0][(int)CrxDBGetCuffPWAMeasurementDetails.P_T1I].ToString());
                crxPwaCuffData1.P_T1M = float.Parse(dsPWA.Tables[0].Rows[0][(int)CrxDBGetCuffPWAMeasurementDetails.P_T1M].ToString());
                crxPwaCuffData1.P_T1Other = float.Parse(dsPWA.Tables[0].Rows[0][(int)CrxDBGetCuffPWAMeasurementDetails.P_T1Other].ToString());
                crxPwaCuffData1.P_T1R = float.Parse(dsPWA.Tables[0].Rows[0][(int)CrxDBGetCuffPWAMeasurementDetails.P_T1R].ToString());
                crxPwaCuffData1.P_T2I = float.Parse(dsPWA.Tables[0].Rows[0][(int)CrxDBGetCuffPWAMeasurementDetails.P_T2I].ToString());
                crxPwaCuffData1.P_T2M = float.Parse(dsPWA.Tables[0].Rows[0][(int)CrxDBGetCuffPWAMeasurementDetails.P_T2M].ToString());
                crxPwaCuffData1.P_T2Other = float.Parse(dsPWA.Tables[0].Rows[0][(int)CrxDBGetCuffPWAMeasurementDetails.P_T2Other].ToString());
                crxPwaCuffData1.P_T2R = float.Parse(dsPWA.Tables[0].Rows[0][(int)CrxDBGetCuffPWAMeasurementDetails.P_T2R].ToString());
                buffer = (byte[])dsPWA.Tables[0].Rows[0][(int)CrxDBGetCuffPWAMeasurementDetails.P_TRIGS];
                len = buffer.Length / 2;
                crxPwaCuffData1.P_TRIGS = dbMagr.CommonByteArrtoShortArr(buffer, len);

                buffer = (byte[])dsPWA.Tables[0].Rows[0][(int)CrxDBGetCuffPWAMeasurementDetails.P_UNCAL_AV];
                len = buffer.Length / 4;
                crxPwaCuffData1.P_UNCAL_AV = dbMagr.CommonByteArrtoFloatArr(len, buffer);
            }

            return (crxPwaCuffData1);
        }

        private double[] prepareAix75Data(string selectedAssesmentIds)
        {
            string[] selectedIds = selectedAssesmentIds.Split(GuiConstants.Separator);
            double[] aixData = new double[selectedIds.Length - 1];

            BizPWA aixBizPWA = (BizPWA)BizSession.Instance().measurement;
            CrxPwaCaptureInput pwaCaptureInput = new CrxPwaCaptureInput();
            bool value = GuiCommon.bizPwaobject.GetCurrentCaptureInput(ref pwaCaptureInput);
            if (!Convert.ToInt32(pwaCaptureInput).Equals(crxPwaData.CaptureInput))
            {
                if (crxPwaData.CaptureInput.Equals(Convert.ToInt32(CrxPwaCaptureInput.Tonometer)))
                {
                    aixBizPWA.Initialise(CrxPwaCaptureInput.Tonometer);
                }
                else
                {
                    aixBizPWA.Initialise(CrxPwaCaptureInput.Cuff);
                }
            }

            for (int counter = 0; counter < aixData.Length; counter++)
            {
                CrxStructCuffPWAMeasurementData cdataAix = new CrxStructCuffPWAMeasurementData
                {
                    PWA_Id = Convert.ToInt32(selectedIds[counter])
                };
                CrxStructPWAMeasurementData pdataAix = new CrxStructPWAMeasurementData
                {
                    PWA_Id = Convert.ToInt32(selectedIds[counter])
                };
                PrepareArrayObjectsForPwaMode(pdataAix, cdataAix);

                DataSet dsPWAAix = dbMagr.GetCuffPWAMeasurementDetails(pdataAix, cdataAix);

                CrxStructPWAMeasurementData crxPwaDataAix = new CrxStructPWAMeasurementData();
                CrxStructCuffPWAMeasurementData crxPwaCuffDataAix = new CrxStructCuffPWAMeasurementData();

                PrepareArrayObjectsForPwaMode(crxPwaDataAix, crxPwaCuffDataAix);
                
                crxPwaDataAix = getCrxPWAData(dsPWAAix, crxPwaDataAix);
                crxPwaCuffDataAix = getCrxPWACuffData(dsPWAAix, crxPwaCuffDataAix);

                aixBizPWA.Populate(crxPwaDataAix, crxPwaCuffDataAix);
                aixBizPWA.Validate();
                aixData[counter] = Math.Round(aixBizPWA.AGPH_HR75);
                CrxLogger.Instance.Write("Aix75 Data :" + Math.Round(aixBizPWA.AGPH_HR75));
            }

            return aixData;
        }

        private void guiradtxtImperialHeight_TextChanged(object sender, EventArgs e)
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

        private void guiradtxtMedicationNotesValue_TextChanged(object sender, EventArgs e)
        {
            if (!guiradbtnreportedit.Visible)
            {
                isValueChanged = true;
            }
        }

        /** This event fires when mouse pointer is hovered over PWV / heart rate trend analysis chart. 
         * It fetches datapoints (x & y values) for that control and displays data elated to it
         * */
        private void Chart_GetToolTipText(object sender, ToolTipEventArgs e)
        {
            try
            {
                  switch (e.HitTestResult.ChartElementType)
                  {
                // Check selected chart element and set tooltip text   
                // if it is axislabel get the text of it to show as tool tip
                      case ChartElementType.AxisLabels:
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

        /** This event customizes label display on PWA trend Large chart
        * */
        private void guiradLargeChart_Customize(object sender, EventArgs e)
        {
            try
            {
                const int SeriesPoints = 3;
                if (apRate != null)
                {
                    if (apRate.Length > SeriesPoints)
                    {
                        foreach (CustomLabel cl in guiradLargeChart.ChartAreas[0].AxisX.CustomLabels)
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

        private void guiradbtnAnalysisPrint_Click(object sender, EventArgs e)
        {
            PWACommonReportData.RptPrintType = CrxStructCommonResourceMsg.PwaAnalysisReport;
            FillStructForPWACommonReport();
            PWAAnalysisPreview rpPreview = new PWAAnalysisPreview();
            rpPreview.Show();
        }

        private void DisableRepeatButtonForQuickStartMode()
        {
            if (GuiCommon.StartupScreen.ToUpper().Equals(CrxStructCommonResourceMsg.QuickStart) && GuiCommon.CurrentMode.Equals(CrxStructCommonResourceMsg.Pwa))
            {
                guiradbtnRepeat.Visible = false;
            }
            else
            {
                guiradbtnRepeat.Visible = true;
            }
        }

        /** This method to remove default values "9999" from the array
        * */
        private double[] RemoveDefaultValuesFromArrList(double[] arr)
        {           
            ArrayList a = new ArrayList();
           
            for (int i = 0; i < arr.Length; i++)
            {
                if (!arr[i].Equals(GuiConstants.DefaultValue))
                {
                    a.Add(arr[i]);
                }                
            }

            double[] tempArr = new double[a.Count];

            for (int j = 0; j < a.Count; j++)
            {
                tempArr[j] = Convert.ToDouble(a.ToArray().GetValue(j));
            }

            return tempArr;
        }        
    }
}
