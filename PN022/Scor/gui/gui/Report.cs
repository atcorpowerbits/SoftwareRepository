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

namespace AtCor.Scor.Gui.Presentation
{
    /**
     * @class Report
     * @brief This class encapsualtes Report relation functionality.
     */
    public partial class Report : Telerik.WinControls.UI.RadForm
    {
        #region Reading Excel File
        Microsoft.Office.Interop.Excel.Application application;
        Microsoft.Office.Interop.Excel.Workbook book;
        Microsoft.Office.Interop.Excel.Worksheet sheet;
        #endregion

        Series tonometerSeries;
        Series femoralSeries;
        Series tonometerOnsetSeries;
        Series tonometerOnsetSeries2;
        Series femoralOnsetSeries;
        Series femoralOnsetSeries2;

        CrxMessagingManager oMsgMgr;
        CrxConfigManager crxMgrObject;
        CrxDBManager dbMagr;
        BizPWV obj;
        int bobj = 31256; // systemid, since BIZ is not generating system id, hence hard coded as of Sprint 4
        
        /**Constructor of the form,initializes all the controls.
       * */
        public Report()
        {
            InitializeComponent();

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
        }

        /**This is invoked on the load of report window.
         *fetches & binds report screen data 
         */
        private void Report_Load(object sender, EventArgs e)
        {
            // initialises assessment gridview with required columns
            InitializeReportAssessmentList();

            // make only edit button visible
            guiradbtnreportcancel.Visible = false;
            guiradbtnreportedit.Visible = true;
            guiradbtnreportsave.Visible = false;

            // fill demographic & pwv measurement details & bring the LHS to browse mode
            FillDemographicDetailsReport();

            guiradlblReportPwvDistance.Text = oMsgMgr.GetMessage("LABEL_PWV_DISTANCE");

            ReportPWVDisplayMode(true);
            
            FillPWVMeasurementDetailsReport();

            // binds assessment details related to patient
            FillPatientAssessmentDetailsReport();
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
            guiradbtnreportedit.Visible = false;
            guiradbtnreportcancel.Visible = true;
            guiradbtnreportsave.Visible = true;

            guiradlblReportPwvDistanceMethod.Visible = false;

            guiradlblReportPwvDistanceMethodType.Visible = false;
            ReportPWVDisplayMode(false);

            // ClearReportFields();

            // populates PWV measurement fields as per Settings from config manager
            guiradlblReportCuffUnits.Text = crxMgrObject.PwvSettings.PWVDistanceUnits.Equals(0) ? oMsgMgr.GetMessage("MM") : oMsgMgr.GetMessage("CM");
            guiradlblReportFemoralCuffUnits.Text = crxMgrObject.PwvSettings.PWVDistanceUnits.Equals(0) ? oMsgMgr.GetMessage("MM") : oMsgMgr.GetMessage("CM");
            guiradlblCarotidUnits.Text = crxMgrObject.PwvSettings.PWVDistanceUnits.Equals(0) ? oMsgMgr.GetMessage("MM") : oMsgMgr.GetMessage("CM");

            guiradtxtReportFemoToCuff.Text = obj.myFemoral2CuffDistance.distance.ToString();
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

            // set height & weight details
            guiradtxtReportHeight.Text = guiradlblReportHeightDisplay.Text;
            guiradtxtReportHeightInches.Text = guiradlblReportHeightInches.Text;
            guiradtxtReportWeight.Text = guiradlblReportWeightdisplay.Text;
            guiradtxtReportOperator.Text = guiradlblReportOperatordisplay.Text;
            guiradtxtReportNotes.Text = guiradlblReportNotesDisplay.Text;

            // sets SP, DP & MP values as per session & config object
            if (obj.bloodPressureEntryOption != ushort.Parse(crxMgrObject.GeneralSettings.BloodPressureEntryOptions.ToString()))
            {
                switch (crxMgrObject.GeneralSettings.BloodPressureEntryOptions)
                {
                    case 0:
                        // SP & DP
                        guiradlblReportBloodPressure1.Text = "SP"; // used for internal checking while changing settings.
                        guiradlblBloodPressure2.Text = "DP"; // used for internal checking while changing settings.

                        if (obj.bloodPressure.SP == null || obj.bloodPressure.SP.Reading.ToString().Equals("9999"))
                        {
                            guiradtxtReportBloodPressure1.Text = string.Empty;
                        }
                        else
                        {
                            guiradtxtReportBloodPressure1.Text = obj.bloodPressure.SP.Reading.ToString();
                        }

                        if (obj.bloodPressure.DP == null || obj.bloodPressure.DP.Reading.ToString().Equals("9999"))
                        {
                            guiradtxtReportBloodPressure2.Text = string.Empty;
                        }
                        else
                        {
                            guiradtxtReportBloodPressure2.Text = obj.bloodPressure.DP.Reading.ToString();
                        }

                        //guiradtxtReportBloodPressure1.Text = (obj.bloodPressure.SP == null) ? string.Empty : obj.bloodPressure.SP.Reading.ToString().Equals("9999") ? string.Empty : guiradlblreportSPdisplay.Text;
                        //guiradtxtReportBloodPressure2.Text = (obj.bloodPressure.DP == null) ? string.Empty : obj.bloodPressure.DP.Reading.ToString().Equals("9999") ? string.Empty : guiradlblReportBloodPressure2.Text;
                        break;
                    case 1:
                        // SP & MP
                        guiradlblReportBloodPressure1.Text = "SP"; // used for internal checking while changing settings.
                        guiradlblBloodPressure2.Text = "MP"; // used for internal checking while changing settings.

                        if (obj.bloodPressure.SP == null || obj.bloodPressure.SP.Reading.ToString().Equals("9999"))
                        {
                            guiradtxtReportBloodPressure1.Text = string.Empty;
                        }
                        else
                        {
                            guiradtxtReportBloodPressure1.Text = obj.bloodPressure.SP.Reading.ToString();
                        }

                        if (obj.bloodPressure.MP == null || obj.bloodPressure.MP.Reading.ToString().Equals("9999"))
                        {
                            guiradtxtReportBloodPressure2.Text = string.Empty;
                        }
                        else
                        {
                            guiradtxtReportBloodPressure2.Text = obj.bloodPressure.MP.Reading.ToString();
                        }

                        //guiradtxtReportBloodPressure1.Text = obj.bloodPressure.SP == null ? string.Empty : obj.bloodPressure.SP.Reading.ToString().Equals("9999") ? string.Empty : guiradlblreportSPdisplay.Text;
                        //guiradtxtReportBloodPressure2.Text = obj.bloodPressure.MP == null ? string.Empty : obj.bloodPressure.MP.Reading.ToString().Equals("9999") ? string.Empty : guiradlblReportBloodPressure2.Text;
                        break;
                    case 2:
                        // MP & DP
                        guiradlblReportBloodPressure1.Text = "MP"; // used for internal checking while changing settings.
                        guiradlblBloodPressure2.Text = "DP"; // used for internal checking while changing settings.

                        if (obj.bloodPressure.MP == null || obj.bloodPressure.MP.Reading.ToString().Equals("9999"))
                        {
                            guiradtxtReportBloodPressure1.Text = string.Empty;
                        }
                        else
                        {
                            guiradtxtReportBloodPressure1.Text = obj.bloodPressure.MP.Reading.ToString();
                        }

                        if (obj.bloodPressure.DP == null || obj.bloodPressure.DP.Reading.ToString().Equals("9999"))
                        {
                            guiradtxtReportBloodPressure2.Text = string.Empty;
                        }
                        else
                        {
                            guiradtxtReportBloodPressure2.Text = obj.bloodPressure.DP.Reading.ToString();
                        }
                        
                        //guiradtxtReportBloodPressure1.Text = obj.bloodPressure.MP == null ? string.Empty : obj.bloodPressure.MP.Reading.ToString().Equals("9999") ? string.Empty : guiradlblreportSPdisplay.Text;
                        //guiradtxtReportBloodPressure2.Text = obj.bloodPressure.DP == null ? string.Empty : obj.bloodPressure.DP.Reading.ToString().Equals("9999") ? string.Empty : guiradlblReportBloodPressure2.Text;
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
            // cancels editing PWV details
            ReportPWVDisplayMode(true);
            guiradbtnreportcancel.Visible = false;
            guiradbtnreportedit.Visible = true;
            guiradbtnreportsave.Visible = false;
            
            guiradlblReportPwvDistanceMethodType.Visible = true;
            guiradlblReportPwvDistanceMethod.Visible = true;

            // reset PWV distance method type text
            guiradlblReportPwvDistance.Text = oMsgMgr.GetMessage("LABEL_PWV_DISTANCE");
            guiradlblReportPwvDistanceMethodType.Text = obj.myCarotidDistance.distance.ToString().Equals("9999") ? oMsgMgr.GetMessage("REPORT_LBL_DIRECT") : oMsgMgr.GetMessage("REPORT_LBL_SUBTRACTING");
            guiradlblReportPwvDitanceUnits.Text = crxMgrObject.PwvSettings.PWVDistanceUnits.Equals(0) ? oMsgMgr.GetMessage("MM") : oMsgMgr.GetMessage("CM");

            // sets blood pressure display text in labels
            SetBloodPressureDisplayText();
        }

        /** This method binds demographic details of patient on report screen
       */
        private void FillDemographicDetailsReport()
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

                // fill patient age from BizPwv
                obj = (BizPWV)BizSession.Instance().measurement;

                // fill other details from bizpatient object
                BizPatient patientObj = BizPatient.Instance();

                guilblReportGroupValue.Text = patientObj.groupStudyId;
                guilblReportPatientNameValue.Text = string.IsNullOrEmpty(patientObj.firstName) ? patientObj.lastName : patientObj.firstName + " " + patientObj.lastName;
                guilblReportPatientIdValue.Text = patientObj.patientId;
                guilblReportDobValue.Text = patientObj.dateOfBirth.ToString("dd/MM/yyyy"); // used for internal use.
                guilblReportAgeValue.Text = obj.patientAge.ToString();
                guilblReportGenderValue.Text = patientObj.gender;
            }
            catch (Exception ex)
            {
                RadMessageBox.Show(this, ex.Message, oMsgMgr.GetMessage("SYSTEM_ERROR"), MessageBoxButtons.OK, RadMessageIcon.Error);
                CrxLogger oLogObject = CrxLogger.Instance;
                oLogObject.Write(ex.Message);
            }
        }

        /** This method is used to initialise the assessment grid view.
        */
        private void InitializeReportAssessmentList()
        {
            try
            {
                guiradgridReportAssessment.TableElement.BeginUpdate();

                GridViewCheckBoxColumn checkBoxColumn = new GridViewCheckBoxColumn();
                checkBoxColumn.Name = "CheckBox"; // internal use only

                guiradgridReportAssessment.Columns.Add(checkBoxColumn);
                guiradgridReportAssessment.Columns[0].IsVisible = true;
                guiradgridReportAssessment.Columns[0].Width = 22;
                guiradgridReportAssessment.Columns[0].ReadOnly = false;

                guiradgridReportAssessment.Columns.Add("StudyDateTime", "Study DateTime", "StudyDateTime"); // used for internal use.Not displayed on the GUI
                guiradgridReportAssessment.Columns[1].Width = 290;
                guiradgridReportAssessment.Columns[1].IsVisible = true;

                guiradgridReportAssessment.TableElement.EndUpdate();
                guiradgridReportAssessment.AutoGenerateColumns = false;
            }
            catch (Exception ex)
            {
                RadMessageBox.Show(this, ex.Message, oMsgMgr.GetMessage("SYSTEM_ERROR"), MessageBoxButtons.OK, RadMessageIcon.Error);
                CrxLogger oLogObject = CrxLogger.Instance;
                oLogObject.Write(ex.Message);
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

                /*
                if (crxMgrObject.PwvSettings.PWVDistanceMethod == 0) // Subtracting 
                {
                    guiradtxtReportCuff.Visible = true;
                    guiradlblReportCuff.Visible = true;
                    guiradlblReportCuffUnits.Visible = true;

                    guiradlblCarotid.Text = oMsgMgr.GetMessage("REPORT_LBL_CAROTID");
                    guiradlblCarotid.Visible = true;
                    guiradtxtCarotid.Visible = true;
                    guiradlblCarotidUnits.Visible = true;

                    guiradlblReportPwvDistanceMethodType.Text = oMsgMgr.GetMessage("REPORT_LBL_SUBTRACTING");
                }
                else if (crxMgrObject.PwvSettings.PWVDistanceMethod == 1) // Direct 
                {
                    guiradtxtReportCuff.Visible = false;
                    guiradlblReportCuff.Visible = false;
                    guiradlblReportCuffUnits.Visible = false;

                    guiradlblCarotid.Text = oMsgMgr.GetMessage("REPORT_LBL_DIRECT");
                    guiradlblCarotid.Visible = true;
                    guiradtxtCarotid.Visible = true;
                    guiradlblCarotidUnits.Visible = true;

                    guiradlblReportPwvDistanceMethodType.Text = oMsgMgr.GetMessage("REPORT_LBL_DIRECT");
                }*/

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
                guiradlblReportHeightInches.SendToBack();
                guiradlblReportWeightdisplay.SendToBack();
                guiradlblReportBmiValue.SendToBack();
                guiradlblReportNotesDisplay.SendToBack();
                guiradlblreportpwvdistancedisplay.SendToBack();
                guiradtxtReportBloodPressure1.BringToFront();
                guiradtxtReportHeightInches.BringToFront();
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
            // create biz session instance & bind details to labels
            obj = (BizPWV)BizSession.Instance().measurement;

            guiradlblreportpwvdistancedisplay.Text = obj.calculatedDistance.ToString();
            guiradlblReportPwvDistanceMethodType.Text = obj.myCarotidDistance.distance.ToString().Equals("9999") ? oMsgMgr.GetMessage("REPORT_LBL_DIRECT") : oMsgMgr.GetMessage("REPORT_LBL_SUBTRACTING");
            guiradlblReportPwvDitanceUnits.Text = crxMgrObject.PwvSettings.PWVDistanceUnits.Equals(0) ? oMsgMgr.GetMessage("MM") : oMsgMgr.GetMessage("CM");

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
                    if (obj.heightAndWeight.weightInKilograms.ToString() == "9999")
                    {
                        guiradlblReportWeightdisplay.Text = Math.Round(double.Parse(obj.heightAndWeight.weightInPounds.ToString()) * 0.45359237, MidpointRounding.ToEven).ToString();
                    }
                    else
                    {
                        guiradlblReportWeightdisplay.Text = obj.heightAndWeight.weightInKilograms.ToString();
                    }

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
                    if (obj.heightAndWeight.weightInPounds.ToString() == "9999")
                    {
                        guiradlblReportWeightdisplay.Text = Math.Round(double.Parse(obj.heightAndWeight.weightInKilograms.ToString()) * 2.20462262, MidpointRounding.ToEven).ToString();
                    }
                    else
                    {
                        guiradlblReportWeightdisplay.Text = obj.heightAndWeight.weightInPounds.ToString();
                    }

                    guiradlblReportWeightUnits.Text = oMsgMgr.GetMessage("LBS");
                    guiradlblReportHeightUnits.Text = oMsgMgr.GetMessage("FEET");
                    break;
            }
        }
        
        /**This method fill assessment details for a particular patient
        * */
        void FillPatientAssessmentDetailsReport()
        {            
            // fetches assessment for a particular patient
            DataSet ds = new DataSet();
            GridViewRowInfo lastRow;
            BizPatient pObj = BizPatient.Instance();
            ds = dbMagr.GetPWVMeasurementDetails(int.Parse(pObj.patientNumber.ToString()), SettingsProperties.GroupID, bobj);

            if (ds.Tables[0].Rows.Count > 0)
            {
                // sets assessment count for a label
                guiradlblReportAssesmentCount.Text = "[" + ds.Tables[0].Rows.Count.ToString() + oMsgMgr.GetMessage("REPORT_ASSESMENT_RECORD_COUNT") + ds.Tables[0].Rows.Count.ToString() + "]";
                guiradgridReportAssessment.DataSource = ds.Tables[0];
                lastRow = guiradgridReportAssessment.Rows[guiradgridReportAssessment.Rows.Count - 1];
                lastRow.IsCurrent = true;
                lastRow.IsSelected = true;         
       
                // if (ds.Tables[0].Rows.Count == 1)
                // {
                //    // checkbox checked if there is only one record
                //    guiradgridReportAssessment.MasterGridViewTemplate.Rows[0].Cells[0].Value = true;
                // }
            }

            // guiradgridReportAssessment.MasterGridViewTemplate.Rows[0].Cells[0].Value = true;
            SuperImposedWaveForm();           
        }

        /**This method sets SP, DP & MP value based on bloodPressureEntryOption in labels
         * */
        void SetBloodPressureDisplayText()
        {
            switch (obj.bloodPressureEntryOption)
            {
                case 0:
                    // sp & dp
                    guiradlblReportBloodPressure1.Text = "SP"; // hardcoded for internal use while changing user settings.
                    guiradlblBloodPressure2.Text = "DP"; // hardcoded for internal use while changing user settings.
                    guiradlblreportSPdisplay.Text = obj.bloodPressure.SP.Reading.ToString();
                    guiradlblReportBloodPressure2.Text = obj.bloodPressure.DP.Reading.ToString();
                    break;
                case 1:
                    // sp & mp
                    guiradlblReportBloodPressure1.Text = "SP"; // hardcoded for internal use while changing user settings.
                    guiradlblBloodPressure2.Text = "MP"; // hardcoded for internal use while changing user settings.
                    guiradlblreportSPdisplay.Text = obj.bloodPressure.SP.Reading.ToString();
                    guiradlblReportBloodPressure2.Text = obj.bloodPressure.MP.Reading.ToString();
                    break;
                case 2:
                    // mp & dp
                    guiradlblReportBloodPressure1.Text = "MP"; // hardcoded for internal use while changing user settings.
                    guiradlblBloodPressure2.Text = "DP"; // hardcoded for internal use while changing user settings.
                    guiradlblreportSPdisplay.Text = obj.bloodPressure.MP.Reading.ToString();
                    guiradlblReportBloodPressure2.Text = obj.bloodPressure.DP.Reading.ToString();
                    break;
            }
        }

        /**This event fires on save button click, saves edited measurement data in database & session object
        * */
        private void guiradbtnreportsave_Click(object sender, EventArgs e)
        {
            try
            {
                // save PWV details in database and session object
                CrxStructPWVMeasurementData crxPWV = new CrxStructPWVMeasurementData();
                crxPWV.StudyDateTime = DateTime.Parse(SettingsProperties.PwvCurrentStudyDatetime);
                crxPWV.NormalRange = new float[0];
                crxPWV.ReferenceRange = new float[0];
                crxPWV.CarotidSignal = new short[0];
                crxPWV.FemoralSignal = new short[0];
                crxPWV.CarotidSignalFloatOnSets = new float[0];
                crxPWV.FemoralSignalFloatOnSets = new float[0];

                // calculates height in inches & centimeters
                if (guiradtxtReportHeightInches.Visible)
                {
                    int heightinches = (int.Parse(guiradtxtReportHeight.Text.Trim()) * 12) + int.Parse(guiradtxtReportHeightInches.Text.Trim());
                    crxPWV.HeightInInches = short.Parse(heightinches.ToString());
                    crxPWV.WeightInPounds = short.Parse(guiradtxtReportWeight.Text.Trim());

                    // 1 pound is 0.453592 kilograms

                    // 1 inch = 2.54 cm
                    crxPWV.WeightInKilograms = (short)Math.Round(double.Parse(crxPWV.WeightInPounds.ToString()) * 0.453592, MidpointRounding.ToEven);
                    crxPWV.HeightInCentimetres = (short)Math.Round(double.Parse(crxPWV.HeightInInches.ToString()) * 0.453592, MidpointRounding.ToEven);
                }
                else
                {
                    crxPWV.HeightInCentimetres = short.Parse(guiradtxtReportHeight.Text.Trim());
                    crxPWV.WeightInKilograms = short.Parse(guiradtxtReportWeight.Text.Trim());

                    // 1 kilogram = 2.20462262 pounds

                    // 0.3937007874 inches in 1 centimeter
                    crxPWV.WeightInPounds = (short)Math.Round(double.Parse(crxPWV.WeightInKilograms.ToString()) * 2.20462262, MidpointRounding.ToEven);
                    crxPWV.HeightInInches = (short)Math.Round(double.Parse(crxPWV.HeightInCentimetres.ToString()) * 0.3937007874, MidpointRounding.ToEven);
                }

                crxPWV.BodyMassIndex = float.Parse(guiradlblReportBmiValue.Text);
                crxPWV.Operator = guiradtxtReportOperator.Text.Trim();
                crxPWV.Notes = guiradtxtReportNotes.Text.Trim();
                crxPWV.BloodPressureEntryOption = crxMgrObject.GeneralSettings.BloodPressureEntryOptions.ToString();

                // sets SP, DP & MP value
                switch (crxPWV.BloodPressureEntryOption)
                {
                    case "0": // hardcoded for internal use.
                        // sp & dp
                        crxPWV.SP = int.Parse(guiradtxtReportBloodPressure1.Text.Trim());
                        crxPWV.DP = int.Parse(guiradtxtReportBloodPressure2.Text.Trim());
                        crxPWV.MP = 9999; 
                        break;
                    case "1": // hardcoded for internal use.
                        // sp & mp
                        crxPWV.SP = int.Parse(guiradtxtReportBloodPressure1.Text.Trim());
                        crxPWV.DP = 9999;
                        crxPWV.MP = int.Parse(guiradtxtReportBloodPressure2.Text.Trim());
                        break;
                    case "2":
                        // dp & mp
                        crxPWV.SP = 9999;
                        crxPWV.MP = int.Parse(guiradtxtReportBloodPressure1.Text.Trim());
                        crxPWV.DP = int.Parse(guiradtxtReportBloodPressure2.Text.Trim());
                        break;
                }

                // initially form session obj
                // crxPWV.PWVDistanceMethod = obj.myCarotidDistance.distance.ToString().Equals("9999") ? oMsgMgr.GetMessage("REPORT_LBL_DIRECT") : oMsgMgr.GetMessage("REPORT_LBL_SUBTRACTING");
                crxPWV.PWVDistanceMethod = (crxMgrObject.PwvSettings.PWVDistanceMethod == 0) ? oMsgMgr.GetMessage("REPORT_LBL_SUBTRACTING") : oMsgMgr.GetMessage("REPORT_LBL_DIRECT");
                crxPWV.PWVDistance = short.Parse(obj.calculatedDistance.ToString());
                crxPWV.Direct = short.Parse(obj.myPWVDirectDistance.distance.ToString());
                crxPWV.Carotid = short.Parse(obj.myCarotidDistance.distance.ToString());
                crxPWV.Cuff = short.Parse(obj.myCuffDistance.distance.ToString());
                crxPWV.FemoraltoCuff = short.Parse(obj.myFemoral2CuffDistance.distance.ToString());

                // calculate & intialise PWV distance only if there is change
                switch (crxPWV.PWVDistanceMethod)
                {
                    case "Subtracting":
                        if (!string.IsNullOrEmpty(guiradtxtCarotid.Text.Trim()) && !string.IsNullOrEmpty(guiradtxtReportCuff.Text.Trim()) && !string.IsNullOrEmpty(guiradtxtReportFemoToCuff.Text.Trim()))
                        {
                            crxPWV.Direct = 9999;
                            crxPWV.Carotid = short.Parse(guiradtxtCarotid.Text.Trim());
                            crxPWV.Cuff = short.Parse(guiradtxtReportCuff.Text.Trim());
                            crxPWV.FemoraltoCuff = short.Parse(guiradtxtReportFemoToCuff.Text.Trim());
                            crxPWV.PWVDistance = (short)(crxPWV.Cuff - crxPWV.Carotid - crxPWV.FemoraltoCuff);
                            crxPWV.PWVDistanceMethod = guiradlblReportPwvDistanceMethodType.Text;
                        }     
                   
                        break;

                    case "Direct":
                        if (!string.IsNullOrEmpty(guiradtxtCarotid.Text.Trim()) && !string.IsNullOrEmpty(guiradtxtReportFemoToCuff.Text.Trim()))
                        {
                            crxPWV.Direct = short.Parse(guiradtxtCarotid.Text.Trim());
                            crxPWV.Carotid = 9999;
                            crxPWV.Cuff = 9999;
                            crxPWV.FemoraltoCuff = short.Parse(guiradtxtReportFemoToCuff.Text.Trim());
                            crxPWV.PWVDistance = (short)(crxPWV.Direct - crxPWV.FemoraltoCuff);
                            crxPWV.PWVDistanceMethod = guiradlblReportPwvDistanceMethodType.Text;
                        }

                        break;
                }

                crxPWV.SystemIdentifier = bobj;
                crxPWV.GroupIdentifier = SettingsProperties.GroupID;
                crxPWV.PatientNumberInternal = SettingsProperties.PatientInternalNumber;

                // save data
                int iRow = dbMagr.UpdatePWVMeasurementDetails(crxPWV);

                if (iRow > 0)
                {
                    // record updated successfully
                    // populate session object
                    obj = (BizPWV)BizSession.Instance().measurement;

                    obj.bloodPressureEntryOption = ushort.Parse(crxPWV.BloodPressureEntryOption);

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
                    guiradlblReportPwvDistance.Text = oMsgMgr.GetMessage("LABEL_PWV_DISTANCE");

                    // re populate label fields again and display mode = true
                    FillPWVMeasurementDetailsReport();
                    ReportPWVDisplayMode(true);
                    guiradbtnreportcancel.Visible = false;
                    guiradbtnreportedit.Visible = true;
                    guiradbtnreportsave.Visible = false;
                }
            }
            catch (CrxException ex)
            {
                ExceptionHandling excep = new ExceptionHandling(ex, this);
            }
            catch (Exception ex)
            {
                // ExceptionHandling excep = new ExceptionHandling(ex, this);
                RadMessageBox.Show(this, ex.Message, oMsgMgr.GetMessage("SYSTEM_ERROR"), MessageBoxButtons.OK, RadMessageIcon.Error);
                CrxLogger oLogObject = CrxLogger.Instance;
                oLogObject.Write(ex.Message);
            } 
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

        private void SuperImposedWaveForm()
        {
            try
            {
                BizPWV obj1 = (BizPWV)BizSession.Instance().measurement;
                obj1.systemId = bobj.ToString();

                // obj1.patientNumber = 1;
                // crxMgrObject.PwvSettings.PWVDistanceMethod = 1;
                application = new Microsoft.Office.Interop.Excel.ApplicationClass();
                book = application.Workbooks.Open(ConfigurationManager.AppSettings["XcelPath"].ToString(),
                0, true, 5, string.Empty, string.Empty, false, Microsoft.Office.Interop.Excel.XlPlatform.xlWindows, string.Empty,
                true, false, 0, true, false, false);

                sheet = (Microsoft.Office.Interop.Excel.Worksheet)book.Worksheets[1];
                //obj1.myPWVDirectDistance.distance = Convert.ToUInt16(((Microsoft.Office.Interop.Excel.Range)sheet.Cells[2, 8]).Value2.ToString());
                string femoral = ((Microsoft.Office.Interop.Excel.Range)sheet.Cells[2, 12]).Value2.ToString();
                string carotid = ((Microsoft.Office.Interop.Excel.Range)sheet.Cells[2, 11]).Value2.ToString();
                ushort signalLength = Convert.ToUInt16(((Microsoft.Office.Interop.Excel.Range)sheet.Cells[2, 10]).Value2.ToString());                
                obj1.PrepareToCaptureSignal();
                string[] femoralValuesArray = new string[5120];
                femoralValuesArray = femoral.Split(',');
                ushort[] femoralSignal = Array.ConvertAll(femoralValuesArray, new Converter<string, ushort>(Convert.ToUInt16));
                obj1.femoralSignal.CaptureSignal(femoralSignal, signalLength);
                
                string[] carotidValuesArray = new string[5120];
                carotidValuesArray = carotid.Split(',');
                ushort[] carotidSignal = Array.ConvertAll(carotidValuesArray, new Converter<string, ushort>(Convert.ToUInt16));
                obj1.carotidSignal.CaptureSignal(carotidSignal, signalLength);
                bool status = obj1.Calculate();

                ushort[] femoralSignalToPlot = obj1.femoralSignal.signal;
                float[] femoralOnSetPoints = obj1.femoralSignal.floatOnsets;
                ushort femoralOnSetPointLength = obj1.femoralSignal.onsetsLength;
                ushort[] carotidSignalToPlot = obj1.carotidSignal.signal;
                float[] carotidOnSetPoints = obj1.carotidSignal.floatOnsets;
                ushort carotidOnSetPointLenth = obj1.carotidSignal.onsetsLength;

                PlotSuperImposedWaveform(femoralSignalToPlot, femoralOnSetPoints, carotidSignalToPlot, carotidOnSetPoints, signalLength);

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
            catch (Exception ex)
            {
                string message = ex.Message;
            }
        }

        private void PlotSuperImposedWaveform(ushort[] femoralSignalToPlot, float[] femoralOnSetPoints, ushort[] carotidSignalToPlot, float[] carotidOnSetPoints, ushort signalLength)
        {
            // plot on the waveform.
            const double chartHeight = 500;
            const double minXValue = 0;
            double maxXValue = signalLength;

            // set y axis
            guichartSuperImposedWaveform.ChartAreas[0].AxisY.Minimum = chartHeight * 0.96;
            guichartSuperImposedWaveform.ChartAreas[0].AxisY.Maximum = chartHeight * 1.04;

            // set x axis
            guichartSuperImposedWaveform.ChartAreas[0].AxisX.Minimum = minXValue;
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
                valueToPLotCuffOnset = int.Parse((Math.Round(double.Parse(femoralOnSetPoints[j].ToString()), MidpointRounding.ToEven)).ToString());

                valueToPLotCuffOnset1 = Math.Abs(valueToPLotCuffOnset);

                if (valueToPLotCuffOnset < 0)
                {
                    femoralOnsetSeries2.Points.AddXY(valueToPLotCuffOnset1, carotidTable[valueToPLotCuffOnset1]);                    
                    femoralOnsetSeries2.Points[femoralOnsetSeries2.Points.Count - 1].MarkerStyle = MarkerStyle.Circle;
                }
                else
                {
                    femoralOnsetSeries.Points.AddXY(valueToPLotCuffOnset1, carotidTable[valueToPLotCuffOnset1]);                    
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

        /**This event fires when checkbox is clicked
          * */
        private void guiradgridReportAssessment_ValueChanged(object sender, EventArgs e)
        {
            // int index;
            
            // if (this.guiradgridReportAssessment.ActiveEditor is RadCheckBoxEditor)
            // {
            //    index = this.guiradgridReportAssessment.CurrentCell.RowIndex;
            //    object value = this.guiradgridReportAssessment.ActiveEditor.Value;
            // }

            //// plots chart of checkbox is checked
            // if (bool.Parse(guiradgridReportAssessment.MasterGridViewTemplate.Rows[this.guiradgridReportAssessment.CurrentCell.RowIndex].Cells[0].Value.ToString()) == true)
            // {
            //    SuperImposedWaveForm();
            // }
        }

        /**This event fires when control leaves from report tab
         * Sets the screen to display mode
           * */
        private void Report_Leave(object sender, EventArgs e)
        {            
               ReportPWVDisplayMode(true);   
        }

        private void guiradgridReportAssessment_SelectionChanged(object sender, EventArgs e)
        {
            // if (firstTimeGridLoad)
            // {
            //    guiradgridReportAssessment.MasterGridViewTemplate.Rows[0].Cells[0].Value = true;
            // }
           // SuperImposedWaveForm();
        }
    }
}
