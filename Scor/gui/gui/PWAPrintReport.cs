/*
     Copyright (C) ATCOR MEDICAL PTY LTD, 2010
 
     Filename     :     PWAPrintReport.cs
        
     Author       :     Smarajit Mishra
 
     Description  :     Creates crystal report for Pwa report printing
*/
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.IO;
using gui;
using AtCor.Scor.CrossCutting.Configuration;
using AtCor.Scor.CrossCutting.Messaging;
using CrystalDecisions.Shared;
using AtCor.Scor.BusinessLogic;
using System.Configuration;

/**
 * @namespace AtCor.Scor.Gui.Presentation
 * @brief This namespace implements Presentation related classes.
 * 
 */
namespace AtCor.Scor.Gui.Presentation
{
    public partial class PWAPrintReport : Form
    {
        private readonly PWAClinicalPreview objPWAClinicalPreview;
        private readonly PWAPatientPreview objPWAPatientPreview;
        private readonly PWAAnalysisPreview objPWAAnalysisPreview;
        private readonly PWATestResult objPWATestResultPreview;
        readonly BizPatient patientObj = BizPatient.Instance();

        // Commeting default constructor
        // public PWAPrintReport()
        // {
        //    InitializeComponent();
        // }

         /**Parameterized Constructor, used to initialize the report object     
        */
        public PWAPrintReport(PWAClinicalPreview obj)
        {
            InitializeComponent();
            objPWAClinicalPreview = obj;
        }

        /**Parameterized Constructor, used to initialize the report object     
        */
        public PWAPrintReport(PWAPatientPreview obj)
        {
            InitializeComponent();
            objPWAPatientPreview = obj;
        }

        /**Parameterized Constructor, used to initialize the report object     
        */
        public PWAPrintReport(PWAAnalysisPreview obj)
        {
            InitializeComponent();
            objPWAAnalysisPreview = obj;
        }

        /**Parameterized Constructor, used to initialize the report object     
        */
        public PWAPrintReport(PWATestResult obj)
        {
            InitializeComponent();
            objPWATestResultPreview = obj;
        }

        /** This method to load the PWA Print Crystal Report 
       * */
        private void PWAPrintReport_Load(object sender, EventArgs e)
        {
            try
            {
                CrxConfigManager configMgr = CrxConfigManager.Instance;
                configMgr.GetGeneralUserSettings();
                string tempPrinter = configMgr.GeneralSettings.PrinterName;
                CrxMessagingManager objMsg = CrxMessagingManager.Instance;
                string tempStr = string.Empty;

                if (PWACommonReportData.RptPrintType.Equals(CrxStructCommonResourceMsg.PwaClinicalReport))
                {
                    DsPwaPrintReport dsPwaClinical = new DsPwaPrintReport();
                    DsPwaPrintReport.ClinicalTableDataTable dtPwaClinical = new DsPwaPrintReport.ClinicalTableDataTable();

                    // Object of dataRow
                    DataRow dr = dtPwaClinical.NewRow();
                    Image imgLogo;
                    Image imgClincalParam;
                    Image imgClinicalPressureWaveform;
                    Image imgRawWaveformsChart;
                    Image imgRawMultiWaveformsChart;

                    GetPwaClinicalImages(out imgLogo, out imgClincalParam, out imgClinicalPressureWaveform, out imgRawWaveformsChart, out imgRawMultiWaveformsChart);

                    byte[] imgByteLogo = ImageToByteArray(imgLogo);
                    byte[] imgByteClinicalParam = ImageToByteArray(imgClincalParam);
                    byte[] imgByteClinicalPressureWaveform = ImageToByteArray(imgClinicalPressureWaveform);
                    byte[] imgByteRawWaveformsChart = ImageToByteArray(imgRawWaveformsChart);
                    byte[] imgByteMultiRawWaveformsChart = ImageToByteArray(imgRawMultiWaveformsChart);

                    dr[0] = imgByteLogo;
                    dr[1] = imgByteClinicalParam;
                    dr[2] = imgByteClinicalPressureWaveform;
                    dr[3] = imgByteRawWaveformsChart;
                    dr[4] = imgByteMultiRawWaveformsChart;
                    dtPwaClinical.Rows.Add(dr);

                    dsPwaClinical.Tables.Clear();
                    dsPwaClinical.Tables.Add(dtPwaClinical);

                    dsPwaClinical.AcceptChanges();

                    CrystalPwaClinical1.SetDataSource(dsPwaClinical);

                    CrystalPwaClinical1.SetParameterValue(GuiConstants.ReportHeader, PWACommonReportData.RptHeader);
                    CrystalPwaClinical1.SetParameterValue(GuiConstants.ReportTitle, objMsg.GetMessage(CrxStructCommonResourceMsg.GuiPrintPwaClinicalTitle));
                    CrystalPwaClinical1.SetParameterValue(GuiConstants.PatientData, PWACommonReportData.RptPatientDataHeader);
                    CrystalPwaClinical1.SetParameterValue(GuiConstants.StudyData, PWACommonReportData.RptStudyDataHeader);
                    CrystalPwaClinical1.SetParameterValue(GuiConstants.PatientNameTitle, PWACommonReportData.RptPatientName);
                    CrystalPwaClinical1.SetParameterValue(GuiConstants.PatientNameValue, PWACommonReportData.RptPatientNameValue);
                    CrystalPwaClinical1.SetParameterValue(GuiConstants.PatientIdTitle, PWACommonReportData.RptPatientId);
                    CrystalPwaClinical1.SetParameterValue(GuiConstants.PatientIdValue, PWACommonReportData.RptPatientIdValue);
                    CrystalPwaClinical1.SetParameterValue(GuiConstants.PatientDobTitle, PWACommonReportData.RptPatientDob);
                    CrystalPwaClinical1.SetParameterValue(GuiConstants.PatientDobValue, PWACommonReportData.RptPatientDobValue);
                    CrystalPwaClinical1.SetParameterValue(GuiConstants.PatientAgeTitle, PWACommonReportData.RptPatientAgeGender);
                    CrystalPwaClinical1.SetParameterValue(GuiConstants.PatientAgeValue, PWACommonReportData.RptPatientAgeGenderValue);

                    CrystalPwaClinical1.SetParameterValue(GuiConstants.PatientAssessmentTitle, PWACommonReportData.RptPatientAssessment);
                    CrystalPwaClinical1.SetParameterValue(GuiConstants.PatientAssessmentValue, PWACommonReportData.RptPatientAssessmentValue);
                    CrystalPwaClinical1.SetParameterValue(GuiConstants.PatientBPTitle, PWACommonReportData.RptPatientBP);
                    CrystalPwaClinical1.SetParameterValue(GuiConstants.PatientBPValue, PWACommonReportData.RptPatientBPValue);
                    CrystalPwaClinical1.SetParameterValue(GuiConstants.PatientHeightTitle, PWACommonReportData.RptPatientHeight);
                    CrystalPwaClinical1.SetParameterValue(GuiConstants.PatientHeightValue, PWACommonReportData.RptPatientHeightValue);

                    CrystalPwaClinical1.SetParameterValue(GuiConstants.GroupNameTitle, PWACommonReportData.RptGroupNameTitle);
                    CrystalPwaClinical1.SetParameterValue(GuiConstants.GroupNameValue, PWACommonReportData.RptGroupNameValue);
                    CrystalPwaClinical1.SetParameterValue(GuiConstants.WaveformPlotTitle, PWACommonReportData.RptWaveformPlotTitle);
                    CrystalPwaClinical1.SetParameterValue(GuiConstants.WaveformPlotValue, PWACommonReportData.RptWaveformPlotValue);
                    CrystalPwaClinical1.SetParameterValue(GuiConstants.NumberOfWaveformsTitle, PWACommonReportData.RptNumberOfWaveformsTitle);
                    CrystalPwaClinical1.SetParameterValue(GuiConstants.NumberOfWaveformsValue, PWACommonReportData.RptNumberOfWaveformsValue);
                    CrystalPwaClinical1.SetParameterValue(GuiConstants.QualityControlTitle, PWACommonReportData.RptQualityControlTitle);
                    CrystalPwaClinical1.SetParameterValue(GuiConstants.QualityControlValue, PWACommonReportData.RptQualityControlValue);
                    CrystalPwaClinical1.SetParameterValue(GuiConstants.SimulationModeTitle, PWACommonReportData.RptSimulationModeTitle);

                    CrystalPwaClinical1.SetParameterValue(GuiConstants.NoteTitle, PWACommonReportData.RptNoteTitle);
                    CrystalPwaClinical1.SetParameterValue(GuiConstants.NoteValue, PWACommonReportData.RptNoteValue);

                    CrystalPwaClinical1.SetParameterValue(GuiConstants.InterpretationTitle, PWAClinicalReportData.RptInterpretationTitle);
                    CrystalPwaClinical1.SetParameterValue(GuiConstants.InterpretationValue, PWAClinicalReportData.RptInterpretationValue);
                    CrystalPwaClinical1.SetParameterValue(GuiConstants.PhysicianTitle, PWACommonReportData.RptPhysicianTitle);
                    CrystalPwaClinical1.SetParameterValue(GuiConstants.SignatureTitle, PWACommonReportData.RptSignatureTitle);
                    CrystalPwaClinical1.SetParameterValue(GuiConstants.ClinicalParametersTitle, PWAClinicalReportData.RptClinicalParametersTitle);
                    CrystalPwaClinical1.SetParameterValue(GuiConstants.CentralPressureWaveformTitle, PWAClinicalReportData.RptCentralPressureWaveformTitle);
                    CrystalPwaClinical1.SetParameterValue(GuiConstants.BrachialTitle, PWAClinicalReportData.RptBrachialTitle);
                    CrystalPwaClinical1.SetParameterValue(GuiConstants.AorticTitle, PWAClinicalReportData.RptAroticTitle);

                    CrystalPwaClinical1.SetParameterValue(GuiConstants.SPTitle, PWAClinicalReportData.RptSPTitle);
                    CrystalPwaClinical1.SetParameterValue(GuiConstants.DPTitle, PWAClinicalReportData.RptDPTitle);
                    CrystalPwaClinical1.SetParameterValue(GuiConstants.MPTitle, PWAClinicalReportData.RptMPTitle);
                    CrystalPwaClinical1.SetParameterValue(GuiConstants.PPTitle, PWAClinicalReportData.RptPPTitle);
                    CrystalPwaClinical1.SetParameterValue(GuiConstants.HRTitle, PWAClinicalReportData.RptHRTitle);

                    CrystalPwaClinical1.SetParameterValue(GuiConstants.SPBrachialValue, PWAClinicalReportData.RptSPBrachialValue);
                    CrystalPwaClinical1.SetParameterValue(GuiConstants.DPBrachialValue, PWAClinicalReportData.RptDPBrachialValue);
                    CrystalPwaClinical1.SetParameterValue(GuiConstants.MPBrachialValue, PWAClinicalReportData.RptMPBrachialValue);
                    CrystalPwaClinical1.SetParameterValue(GuiConstants.PPBrachialValue, PWAClinicalReportData.RptPPBrachialValue);
                    CrystalPwaClinical1.SetParameterValue(GuiConstants.HRBrachialValue, PWAClinicalReportData.RptHRBrachialValue);

                    CrystalPwaClinical1.SetParameterValue(GuiConstants.SPAorticValue, PWAClinicalReportData.RptSPAroticValue);
                    CrystalPwaClinical1.SetParameterValue(GuiConstants.DPAorticValue, PWAClinicalReportData.RptDPAroticValue);
                    CrystalPwaClinical1.SetParameterValue(GuiConstants.MPAorticValue, PWAClinicalReportData.RptMPAroticValue);
                    CrystalPwaClinical1.SetParameterValue(GuiConstants.PPAorticValue, PWAClinicalReportData.RptPPAroticValue);
                    CrystalPwaClinical1.SetParameterValue(GuiConstants.HRAorticValue, PWAClinicalReportData.RptHRAroticValue);

                    crysRptVwrPwaPrintReport.ReportSource = CrystalPwaClinical1;
                    crysRptVwrPwaPrintReport.Refresh();
                    crysRptVwrPwaPrintReport.Hide();
                    CrystalPwaClinical1.PrintOptions.PrinterName = tempPrinter;
                    CrystalPwaClinical1.PrintOptions.PaperOrientation = GuiCommon.IsLandScape == false ? PaperOrientation.Portrait : PaperOrientation.Landscape;

                    CrystalPwaClinical1.PrintOptions.PaperSize = PaperSize.PaperA4;
                    CrystalPwaClinical1.PrintToPrinter(1, false, 0, 0);
                }
                else if (PWACommonReportData.RptPrintType.Equals(CrxStructCommonResourceMsg.PwaPatientReport))
                {
                    DsPwaPrintReport dsPwaPatient = new DsPwaPrintReport();
                    DsPwaPrintReport.PatientTableDataTable dtPwaPatient = new DsPwaPrintReport.PatientTableDataTable();

                    DataRow dr = dtPwaPatient.NewRow();
                    Image imgLogo;
                    Image imgHumanLogo;
                    Image imgSpSlider;
                    Image imgDpSlider;
                    Image imgHrSlider;
                    Image imgSpChart;
                    Image imgPpChart;
                    Image imgApChart;
                    Image imgAixChart;

                    GetPwaPatientImages(out imgLogo, out imgHumanLogo, out imgSpSlider, out imgDpSlider, out imgHrSlider, out imgSpChart, out imgApChart, out imgPpChart, out imgAixChart);

                    byte[] imgByteLogo = ImageToByteArray(imgLogo);
                    byte[] imgByteHumanLogo = ImageToByteArray(imgHumanLogo);
                    byte[] imgByteSpSlider = ImageToByteArray(imgSpSlider);
                    byte[] imgByteDpSlider = ImageToByteArray(imgDpSlider);
                    byte[] imgByteHrSlider = ImageToByteArray(imgHrSlider);
                    byte[] imgByteSpChart = ImageToByteArray(imgSpChart);
                    byte[] imgBytePpChart = ImageToByteArray(imgPpChart);
                    byte[] imgByteApChart = ImageToByteArray(imgApChart);
                    byte[] imgByteAixChart = ImageToByteArray(imgAixChart);
               
                    dr[0] = imgByteLogo;
                    dr[1] = imgByteHumanLogo;
                    dr[2] = imgByteSpSlider;
                    dr[3] = imgByteDpSlider;
                    dr[4] = imgByteHrSlider;
                    dr[5] = imgByteSpChart;
                    dr[6] = imgByteApChart;
                    dr[7] = imgBytePpChart;
                    dr[8] = imgByteAixChart;

                    dtPwaPatient.Rows.Add(dr);

                    dsPwaPatient.Tables.Clear();
                    dsPwaPatient.Tables.Add(dtPwaPatient);

                    dsPwaPatient.AcceptChanges();

                    CrystalPwaPatientReport1.SetDataSource(dsPwaPatient);

                    CrystalPwaPatientReport1.SetParameterValue(GuiConstants.ReportHeader, PWACommonReportData.RptHeader);
                    CrystalPwaPatientReport1.SetParameterValue(GuiConstants.ReportTitle, objMsg.GetMessage(CrxStructCommonResourceMsg.PrtPwvTextPatientReport));
                    CrystalPwaPatientReport1.SetParameterValue(GuiConstants.ProductName, objMsg.GetMessage(CrxStructCommonResourceMsg.PrtPwvTextScor));
                    CrystalPwaPatientReport1.SetParameterValue(GuiConstants.ReportDescription, objMsg.GetMessage(CrxStructCommonResourceMsg.PrtPwaTextRptDesc));
                    CrystalPwaPatientReport1.SetParameterValue(GuiConstants.LblPatientDetails, objMsg.GetMessage(CrxStructCommonResourceMsg.PrtPwvTextPatientDetails));
                    CrystalPwaPatientReport1.SetParameterValue(GuiConstants.LblFirstName, objMsg.GetMessage(CrxStructCommonResourceMsg.LblFirstName));
                    CrystalPwaPatientReport1.SetParameterValue(GuiConstants.TxtFirstNameValue, string.IsNullOrEmpty(patientObj.firstName) ? string.Empty : patientObj.firstName);
                    tempStr = string.Empty;
                    tempStr = objMsg.GetMessage(CrxStructCommonResourceMsg.LblLastName);
                    tempStr = tempStr.Replace(objMsg.GetMessage(CrxStructCommonResourceMsg.GuiDisplayAsteriskColon), objMsg.GetMessage(CrxStructCommonResourceMsg.GuiDisplayColon));
                    CrystalPwaPatientReport1.SetParameterValue(GuiConstants.LblLastName, tempStr);
                    CrystalPwaPatientReport1.SetParameterValue(GuiConstants.TxtLastNameValue, string.IsNullOrEmpty(patientObj.lastName) ? string.Empty : patientObj.lastName);
                    CrystalPwaPatientReport1.SetParameterValue(GuiConstants.LblPatientId, PWACommonReportData.RptPatientId);
                    CrystalPwaPatientReport1.SetParameterValue(GuiConstants.TxtPatientId, PWACommonReportData.RptPatientIdValue);
                    CrystalPwaPatientReport1.SetParameterValue(GuiConstants.LblAge, PWACommonReportData.RptPatientAge);
                    CrystalPwaPatientReport1.SetParameterValue(GuiConstants.TxtAge, PWACommonReportData.RptPatientAgeValue);
                    CrystalPwaPatientReport1.SetParameterValue(GuiConstants.LblGender, PWACommonReportData.RptPatientGender);
                    CrystalPwaPatientReport1.SetParameterValue(GuiConstants.TxtGender, PWACommonReportData.RptPatientGenderValue);

                    CrystalPwaPatientReport1.SetParameterValue(GuiConstants.LblDob, PWACommonReportData.RptPatientDob);
                    CrystalPwaPatientReport1.SetParameterValue(GuiConstants.TxtDobValue, PWACommonReportData.RptPatientDobValue);
                    CrystalPwaPatientReport1.SetParameterValue(GuiConstants.LblHeight, PWACommonReportData.RptPatientHeight);
                    CrystalPwaPatientReport1.SetParameterValue(GuiConstants.TxtHeightValue, PWACommonReportData.RptPatientHeightValue);
                    CrystalPwaPatientReport1.SetParameterValue(GuiConstants.LblDateofmeasurement, PWAPatientReportData.RptPatientAssessment);
                    CrystalPwaPatientReport1.SetParameterValue(GuiConstants.TxtDateofmeasurement, PWACommonReportData.RptPatientAssessmentValue);

                    CrystalPwaPatientReport1.SetParameterValue(GuiConstants.TxtPwaPatientRptHeader, objMsg.GetMessage(CrxStructCommonResourceMsg.RptPwaTxtPatientRptHeader));
                    CrystalPwaPatientReport1.SetParameterValue(GuiConstants.TxtPage, objMsg.GetMessage(CrxStructCommonResourceMsg.RptPwaTxtPage));
                    CrystalPwaPatientReport1.SetParameterValue(GuiConstants.PwaText1, objMsg.GetMessage(CrxStructCommonResourceMsg.RptPwaTxt1));
                    CrystalPwaPatientReport1.SetParameterValue(GuiConstants.PwaText2, objMsg.GetMessage(CrxStructCommonResourceMsg.RptPwaTxt2));
                    CrystalPwaPatientReport1.SetParameterValue(GuiConstants.PwaText3, objMsg.GetMessage(CrxStructCommonResourceMsg.RptPwaTxt3));
                    CrystalPwaPatientReport1.SetParameterValue(GuiConstants.PwaText4, objMsg.GetMessage(CrxStructCommonResourceMsg.RptPwaTxt4));
                    CrystalPwaPatientReport1.SetParameterValue(GuiConstants.PwaText5, objMsg.GetMessage(CrxStructCommonResourceMsg.RptPwaTxt5));
                    CrystalPwaPatientReport1.SetParameterValue(GuiConstants.PwaText6, objMsg.GetMessage(CrxStructCommonResourceMsg.RptPwaTxt6));

                    CrystalPwaPatientReport1.SetParameterValue(GuiConstants.PwaText7, objMsg.GetMessage(CrxStructCommonResourceMsg.RptPwaTxt7));
                    CrystalPwaPatientReport1.SetParameterValue(GuiConstants.PwaText8, objMsg.GetMessage(CrxStructCommonResourceMsg.RptPwaTxt8));
                    CrystalPwaPatientReport1.SetParameterValue(GuiConstants.PwaText9, objMsg.GetMessage(CrxStructCommonResourceMsg.RptPwaTxt9));
                    CrystalPwaPatientReport1.SetParameterValue(GuiConstants.PwaText10, objMsg.GetMessage(CrxStructCommonResourceMsg.RptPwaTxt10));
                    tempStr = string.Empty;
                    tempStr = string.Format("{0}{1}", GuiCommon.bizPwaobject.bloodPressure.SP.Reading.ToString() + objMsg.GetMessage(CrxStructCommonResourceMsg.GuiDisplaySlash), GuiCommon.bizPwaobject.bloodPressure.DP.Reading.ToString());
                    string pwaTempStr = GetPatientReportBpText();
                    CrystalPwaPatientReport1.SetParameterValue(GuiConstants.PwaText11, string.Format(objMsg.GetMessage(CrxStructCommonResourceMsg.RptPwaTxt11), tempStr, pwaTempStr));
                    CrystalPwaPatientReport1.SetParameterValue(GuiConstants.SystolicBpValue, string.Format(objMsg.GetMessage(CrxStructCommonResourceMsg.RptSystolicBpValue), GuiCommon.bizPwaobject.bloodPressure.SP.Reading.ToString()));
                    CrystalPwaPatientReport1.SetParameterValue(GuiConstants.DiastolicBpValue, string.Format(objMsg.GetMessage(CrxStructCommonResourceMsg.RptDiastolicBpValue), GuiCommon.bizPwaobject.bloodPressure.DP.Reading.ToString()));
                    CrystalPwaPatientReport1.SetParameterValue(GuiConstants.TxtPwaPatientRptFooter, objMsg.GetMessage(CrxStructCommonResourceMsg.RptPwaTxtPatientRptFooter));
                    CrystalPwaPatientReport1.SetParameterValue(GuiConstants.PwaText12, objMsg.GetMessage(CrxStructCommonResourceMsg.RptPwaTxt12));
                    CrystalPwaPatientReport1.SetParameterValue(GuiConstants.PwaText13, string.Format(objMsg.GetMessage(CrxStructCommonResourceMsg.RptPwaTxt13), PWAClinicalReportData.RptSPAroticValue));
                    CrystalPwaPatientReport1.SetParameterValue(GuiConstants.PwaText14, objMsg.GetMessage(CrxStructCommonResourceMsg.RptPwaTxt14));
                    CrystalPwaPatientReport1.SetParameterValue(GuiConstants.PwaText15, objMsg.GetMessage(CrxStructCommonResourceMsg.RptPwaTxt15));
                    CrystalPwaPatientReport1.SetParameterValue(GuiConstants.PwaText16, objMsg.GetMessage(CrxStructCommonResourceMsg.RptPwaTxt16));
                    CrystalPwaPatientReport1.SetParameterValue(GuiConstants.PwaText17, objMsg.GetMessage(CrxStructCommonResourceMsg.RptPwaTxt17));
                    CrystalPwaPatientReport1.SetParameterValue(GuiConstants.PwaText18, objMsg.GetMessage(CrxStructCommonResourceMsg.RptPwaTxt18));
                    CrystalPwaPatientReport1.SetParameterValue(GuiConstants.PwaText19, objMsg.GetMessage(CrxStructCommonResourceMsg.RptPwaTxt19));
                    CrystalPwaPatientReport1.SetParameterValue(GuiConstants.PwaText20, objMsg.GetMessage(CrxStructCommonResourceMsg.RptPwaTxt20));
                    CrystalPwaPatientReport1.SetParameterValue(GuiConstants.PwaText21, objMsg.GetMessage(CrxStructCommonResourceMsg.RptPwaTxt21));
                    CrystalPwaPatientReport1.SetParameterValue(GuiConstants.PwaText22, objMsg.GetMessage(CrxStructCommonResourceMsg.RptPwaTxt22));
                    CrystalPwaPatientReport1.SetParameterValue(GuiConstants.PwaText23, objMsg.GetMessage(CrxStructCommonResourceMsg.RptPwaTxt23));
                    CrystalPwaPatientReport1.SetParameterValue(GuiConstants.PwaText24, objMsg.GetMessage(CrxStructCommonResourceMsg.RptPwaTxt24));
                    CrystalPwaPatientReport1.SetParameterValue(GuiConstants.PwaText25, string.Format(objMsg.GetMessage(CrxStructCommonResourceMsg.RptPwaTxt25), PWAClinicalReportData.RptPPAroticValue));
                    CrystalPwaPatientReport1.SetParameterValue(GuiConstants.PwaText26, objMsg.GetMessage(CrxStructCommonResourceMsg.RptPwaTxt26));
                    CrystalPwaPatientReport1.SetParameterValue(GuiConstants.PwaText27, objMsg.GetMessage(CrxStructCommonResourceMsg.RptPwaTxt27));
                    CrystalPwaPatientReport1.SetParameterValue(GuiConstants.PwaText28, objMsg.GetMessage(CrxStructCommonResourceMsg.RptPwaTxt28));
                    CrystalPwaPatientReport1.SetParameterValue(GuiConstants.PwaText29, objMsg.GetMessage(CrxStructCommonResourceMsg.RptPwaTxt29));
                    CrystalPwaPatientReport1.SetParameterValue(GuiConstants.PwaText30, objMsg.GetMessage(CrxStructCommonResourceMsg.RptPwaTxt30));
                    CrystalPwaPatientReport1.SetParameterValue(GuiConstants.PwaText31, objMsg.GetMessage(CrxStructCommonResourceMsg.RptPwaTxt31));
                    CrystalPwaPatientReport1.SetParameterValue(GuiConstants.PwaText32, objMsg.GetMessage(CrxStructCommonResourceMsg.RptPwaTxt32));
                    CrystalPwaPatientReport1.SetParameterValue(GuiConstants.PwaText33, objMsg.GetMessage(CrxStructCommonResourceMsg.RptPwaTxt33));
                    CrystalPwaPatientReport1.SetParameterValue(GuiConstants.PwaText34, objMsg.GetMessage(CrxStructCommonResourceMsg.RptPwaTxt34));

                    CrystalPwaPatientReport1.SetParameterValue(GuiConstants.PwaText35, objMsg.GetMessage(CrxStructCommonResourceMsg.RptPwaTxt35));
                    tempStr = string.Empty;
                    tempStr = GuiCommon.crxPwaData.C_Ap.Equals(GuiConstants.DefaultValue) ? string.Empty : Math.Round(GuiCommon.crxPwaData.C_Ap).ToString();
                    CrystalPwaPatientReport1.SetParameterValue(GuiConstants.PwaText36, string.Format(objMsg.GetMessage(CrxStructCommonResourceMsg.RptPwaTxt36), tempStr));
                    CrystalPwaPatientReport1.SetParameterValue(GuiConstants.PwaText37, objMsg.GetMessage(CrxStructCommonResourceMsg.RptPwaTxt37));
                    CrystalPwaPatientReport1.SetParameterValue(GuiConstants.PwaText38, objMsg.GetMessage(CrxStructCommonResourceMsg.RptPwaTxt38));
                    
                    tempStr = string.Empty;
                    tempStr = GuiCommon.crxPwaData.C_Agph.Equals(GuiConstants.DefaultValue) ? string.Empty : Math.Round(GuiCommon.crxPwaData.C_Agph).ToString();
                    CrystalPwaPatientReport1.SetParameterValue(GuiConstants.PwaText39, string.Format(objMsg.GetMessage(CrxStructCommonResourceMsg.RptPwaTxt39), tempStr));

                    CrystalPwaPatientReport1.SetParameterValue(GuiConstants.PwaText40, objMsg.GetMessage(CrxStructCommonResourceMsg.RptPwaTxt40));
                    CrystalPwaPatientReport1.SetParameterValue(GuiConstants.PwaText41, objMsg.GetMessage(CrxStructCommonResourceMsg.RptPwaTxt41));
                    CrystalPwaPatientReport1.SetParameterValue(GuiConstants.PwaText42, string.Format(objMsg.GetMessage(CrxStructCommonResourceMsg.RptPwaTxt42), PWAClinicalReportData.RptHRAroticValue));
                    CrystalPwaPatientReport1.SetParameterValue(GuiConstants.PwaText43, objMsg.GetMessage(CrxStructCommonResourceMsg.RptPwaTxt43));

                    tempStr = string.Empty;
                    if (GuiCommon.bizPwaobject.ReferenceAge == GuiConstants.DefaultValue)
                    {
                        tempStr = objMsg.GetMessage(CrxStructCommonResourceMsg.RptPwaReferenceNorange);
                    }
                    else
                    {
                        tempStr = string.Format(objMsg.GetMessage(CrxStructCommonResourceMsg.RptPwaReferenceRange), Math.Round(GuiCommon.bizPwaobject.ReferenceAge).ToString());
                    }

                    CrystalPwaPatientReport1.SetParameterValue(GuiConstants.PwaText44, string.Format(objMsg.GetMessage(CrxStructCommonResourceMsg.RptPwaTxt44), tempStr));
                    CrystalPwaPatientReport1.SetParameterValue(GuiConstants.Dot, objMsg.GetMessage(CrxStructCommonResourceMsg.RptPwaDot));
                    crysRptVwrPwaPrintReport.ReportSource = CrystalPwaClinical1;
                    crysRptVwrPwaPrintReport.Refresh();
                    crysRptVwrPwaPrintReport.Hide();

                    CrystalPwaPatientReport1.PrintOptions.PrinterName = tempPrinter;
                    CrystalPwaPatientReport1.PrintOptions.PaperOrientation = GuiCommon.IsLandScape == false ? PaperOrientation.Portrait : PaperOrientation.Landscape;

                    CrystalPwaPatientReport1.PrintOptions.PaperSize = PaperSize.PaperA4;
                    CrystalPwaPatientReport1.PrintToPrinter(1, false, 0, 0);
                }
                else if (PWACommonReportData.RptPrintType.Equals(CrxStructCommonResourceMsg.PwaAnalysisReport))
                {                   
                    DsPwaPrintReport dsPwaAnalysis = new DsPwaPrintReport();
                    DsPwaPrintReport.ClinicalAnalysisTableDataTable dtPwaAnalysis = new DsPwaPrintReport.ClinicalAnalysisTableDataTable();

                    DataRow dr = dtPwaAnalysis.NewRow();
                    Image imgLogo;
                    Image imgSpChart;
                    Image imgPpChart;
                    Image imgApChart;
                    Image imgDpMapChart;
                    Image imgHrChart;
                    Image imgAixChart;

                    GetPwaAnalysisImages(out imgLogo, out imgSpChart, out imgPpChart, out imgApChart, out imgDpMapChart, out imgHrChart, out imgAixChart);

                    byte[] imgByteLogo = ImageToByteArray(imgLogo);
                    byte[] imgByteSpChart = ImageToByteArray(imgSpChart);
                    byte[] imgBytePpChart = ImageToByteArray(imgPpChart);
                    byte[] imgByteApChart = ImageToByteArray(imgApChart);
                    byte[] imgByteDpMapChart = ImageToByteArray(imgDpMapChart);
                    byte[] imgByteHrChart = ImageToByteArray(imgHrChart);
                    byte[] imgByteAixChart = ImageToByteArray(imgAixChart);

                    dr[0] = imgByteLogo;
                    dr[1] = imgByteSpChart;
                    dr[2] = imgBytePpChart;
                    dr[3] = imgByteDpMapChart;
                    dr[4] = imgByteHrChart;
                    dr[5] = imgByteApChart;
                    dr[6] = imgByteAixChart;

                    dtPwaAnalysis.Rows.Add(dr);

                    dsPwaAnalysis.Tables.Clear();
                    dsPwaAnalysis.Tables.Add(dtPwaAnalysis);

                    dsPwaAnalysis.AcceptChanges();

                    CrystalPwaTrendAnalysis1.SetDataSource(dsPwaAnalysis);

                    CrystalPwaTrendAnalysis1.SetParameterValue(GuiConstants.ReportHeader, PWACommonReportData.RptHeader);
                    CrystalPwaTrendAnalysis1.SetParameterValue(GuiConstants.ReportTitle, objMsg.GetMessage(CrxStructCommonResourceMsg.GuiPrintPwaTrendAnalysisTitle));
                    CrystalPwaTrendAnalysis1.SetParameterValue(GuiConstants.PatientData, PWACommonReportData.RptPatientDataHeader);
                    CrystalPwaTrendAnalysis1.SetParameterValue(GuiConstants.StudyData, PWACommonReportData.RptStudyDataHeader);
                    CrystalPwaTrendAnalysis1.SetParameterValue(GuiConstants.PatientNameTitle, PWACommonReportData.RptPatientName);
                    CrystalPwaTrendAnalysis1.SetParameterValue(GuiConstants.PatientNameValue, PWACommonReportData.RptPatientNameValue);
                    CrystalPwaTrendAnalysis1.SetParameterValue(GuiConstants.PatientIdTitle, PWACommonReportData.RptPatientId);
                    CrystalPwaTrendAnalysis1.SetParameterValue(GuiConstants.PatientIdValue, PWACommonReportData.RptPatientIdValue);
                    CrystalPwaTrendAnalysis1.SetParameterValue(GuiConstants.PatientDobTitle, PWACommonReportData.RptPatientDob);
                    CrystalPwaTrendAnalysis1.SetParameterValue(GuiConstants.PatientDobValue, PWACommonReportData.RptPatientDobValue);
                    CrystalPwaTrendAnalysis1.SetParameterValue(GuiConstants.PatientAgeTitle, PWACommonReportData.RptPatientAgeGender);
                    CrystalPwaTrendAnalysis1.SetParameterValue(GuiConstants.PatientAgeValue, PWACommonReportData.RptPatientAgeGenderValue);

                    CrystalPwaTrendAnalysis1.SetParameterValue(GuiConstants.PatientBPTitle, PWACommonReportData.RptPatientBP);
                    CrystalPwaTrendAnalysis1.SetParameterValue(GuiConstants.PatientBPValue, PWACommonReportData.RptPatientBPValue);
                    CrystalPwaTrendAnalysis1.SetParameterValue(GuiConstants.PatientHeightTitle, PWACommonReportData.RptPatientHeight);
                    CrystalPwaTrendAnalysis1.SetParameterValue(GuiConstants.PatientHeightValue, PWACommonReportData.RptPatientHeightValue);

                    CrystalPwaTrendAnalysis1.SetParameterValue(GuiConstants.GroupNameTitle, PWACommonReportData.RptGroupNameTitle);
                    CrystalPwaTrendAnalysis1.SetParameterValue(GuiConstants.GroupNameValue, PWACommonReportData.RptGroupNameValue);
                    CrystalPwaTrendAnalysis1.SetParameterValue(GuiConstants.PatientAssessmentTitle, PWACommonReportData.RptPatientAssessment);
                    CrystalPwaTrendAnalysis1.SetParameterValue(GuiConstants.PatientAssessmentValue, PWAAnalysisReportData.RptPatientAssessmentValue);
                    CrystalPwaTrendAnalysis1.SetParameterValue(GuiConstants.PhysicianTitle, PWACommonReportData.RptPhysicianTitle);
                    CrystalPwaTrendAnalysis1.SetParameterValue(GuiConstants.SignatureTitle, PWACommonReportData.RptSignatureTitle);

                    crysRptVwrPwaPrintReport.ReportSource = CrystalPwaTrendAnalysis1;
                    crysRptVwrPwaPrintReport.Refresh();
                    crysRptVwrPwaPrintReport.Hide();
                    CrystalPwaTrendAnalysis1.PrintOptions.PrinterName = tempPrinter;
                    CrystalPwaTrendAnalysis1.PrintOptions.PaperOrientation = GuiCommon.IsLandScape == false ? PaperOrientation.Portrait : PaperOrientation.Landscape;

                    CrystalPwaTrendAnalysis1.PrintOptions.PaperSize = PaperSize.PaperA4;
                    CrystalPwaTrendAnalysis1.PrintToPrinter(1, false, 0, 0);
                }
                else if (PWACommonReportData.RptPrintType.Equals(CrxStructCommonResourceMsg.QuickStart))
                {
                    DsPwaPrintReport dsPwaQuickStart = new DsPwaPrintReport();
                    DsPwaPrintReport.QuickStartTableDataTable dtPwaQuickStart = new DsPwaPrintReport.QuickStartTableDataTable();

                    DataRow dr = dtPwaQuickStart.NewRow();
                    Image imgLogo;
                    Image imgPanel;

                    GetPwaQuickStartImages(out imgLogo, out imgPanel);

                    byte[] imgByteLogo = ImageToByteArray(imgLogo);
                    byte[] imgBytePanel = ImageToByteArray(imgPanel);

                    dr[0] = imgByteLogo;
                    dr[1] = imgBytePanel;

                    dtPwaQuickStart.Rows.Add(dr);

                    dsPwaQuickStart.Tables.Clear();
                    dsPwaQuickStart.Tables.Add(dtPwaQuickStart);

                    dsPwaQuickStart.AcceptChanges();

                    CrystalPwaQuickStart1.SetDataSource(dsPwaQuickStart);

                    CrystalPwaQuickStart1.SetParameterValue(GuiConstants.ReportHeader, PWACommonReportData.RptHeader);
                    CrystalPwaQuickStart1.SetParameterValue(GuiConstants.ReportTitle, objMsg.GetMessage(CrxStructCommonResourceMsg.GuiPrintPwaQuickStartTitle));
                    CrystalPwaQuickStart1.SetParameterValue(GuiConstants.PatientData, PWACommonReportData.RptPatientDataHeader);
                    CrystalPwaQuickStart1.SetParameterValue(GuiConstants.StudyData, PWACommonReportData.RptStudyDataHeader);
                    CrystalPwaQuickStart1.SetParameterValue(GuiConstants.PatientNameTitle, PWACommonReportData.RptPatientName);
                    CrystalPwaQuickStart1.SetParameterValue(GuiConstants.PatientIdTitle, PWACommonReportData.RptPatientId);
                    CrystalPwaQuickStart1.SetParameterValue(GuiConstants.PatientDobTitle, PWACommonReportData.RptPatientDob);
                    CrystalPwaQuickStart1.SetParameterValue(GuiConstants.PatientAgeTitle, PWACommonReportData.RptPatientAgeGender);

                    CrystalPwaQuickStart1.SetParameterValue(GuiConstants.PatientBPTitle, PWACommonReportData.RptPatientBP);
                    CrystalPwaQuickStart1.SetParameterValue(GuiConstants.PatientHeightTitle, PWACommonReportData.RptPatientHeight);

                    CrystalPwaQuickStart1.SetParameterValue(GuiConstants.GroupNameTitle, PWACommonReportData.RptGroupNameTitle);
                    CrystalPwaQuickStart1.SetParameterValue(GuiConstants.PhysicianTitle, PWACommonReportData.RptPhysicianTitle);
                    CrystalPwaQuickStart1.SetParameterValue(GuiConstants.SignatureTitle, PWACommonReportData.RptSignatureTitle);
                    CrystalPwaQuickStart1.SetParameterValue(GuiConstants.PatientBPTitle, PWACommonReportData.RptPatientBP);
                    CrystalPwaQuickStart1.SetParameterValue(GuiConstants.PatientBPValue, string.Format("{0} {1}", GuiCommon.quickStartCrxPwaData.SP.ToString() + objMsg.GetMessage(CrxStructCommonResourceMsg.GuiDisplaySlash) + GuiCommon.quickStartCrxPwaData.DP.ToString(), objMsg.GetMessage(CrxStructCommonResourceMsg.UnitsPressureMmhg)));
                    
                    crysRptVwrPwaPrintReport.ReportSource = CrystalPwaQuickStart1;
                    crysRptVwrPwaPrintReport.Refresh();
                    crysRptVwrPwaPrintReport.Hide();
                    CrystalPwaQuickStart1.PrintOptions.PrinterName = tempPrinter;
                    CrystalPwaQuickStart1.PrintOptions.PaperOrientation = GuiCommon.IsLandScape == false ? PaperOrientation.Portrait : PaperOrientation.Landscape;

                    CrystalPwaQuickStart1.PrintOptions.PaperSize = PaperSize.PaperA4;
                    CrystalPwaQuickStart1.PrintToPrinter(1, false, 0, 0);
                }
                else
                {
                    DsPwaPrintReport dsPwaClinical = new DsPwaPrintReport();
                    DsPwaPrintReport.ClinicalTableDataTable dtPwaClinical = new DsPwaPrintReport.ClinicalTableDataTable();

                    // Object of dataRow
                    DataRow dr = dtPwaClinical.NewRow();
                    Image imgLogo;
                    Image imgClincalParam;
                    Image imgClinicalPressureWaveform;
                    Image imgRawWaveformsChart;
                    Image imgRawMultiWaveformsChart;

                    GetPwaClinicalImages(out imgLogo, out imgClincalParam, out imgClinicalPressureWaveform, out imgRawWaveformsChart, out imgRawMultiWaveformsChart);

                    byte[] imgByteLogo = ImageToByteArray(imgLogo);
                    byte[] imgByteClinicalParam = ImageToByteArray(imgClincalParam);
                    byte[] imgByteClinicalPressureWaveform = ImageToByteArray(imgClinicalPressureWaveform);

                    dr[0] = imgByteLogo;
                    dr[1] = imgByteClinicalParam;
                    dr[2] = imgByteClinicalPressureWaveform;
                    dtPwaClinical.Rows.Add(dr);

                    dsPwaClinical.Tables.Clear();
                    dsPwaClinical.Tables.Add(dtPwaClinical);

                    dsPwaClinical.AcceptChanges();

                    CrystalPwaEvalution1.SetDataSource(dsPwaClinical);

                    CrystalPwaEvalution1.SetParameterValue(GuiConstants.ReportHeader, PWACommonReportData.RptHeader);
                    CrystalPwaEvalution1.SetParameterValue(GuiConstants.ReportTitle, objMsg.GetMessage(CrxStructCommonResourceMsg.GuiPrintPwaEvaluationTitle));
                    CrystalPwaEvalution1.SetParameterValue(GuiConstants.PatientData, PWACommonReportData.RptPatientDataHeader);
                    CrystalPwaEvalution1.SetParameterValue(GuiConstants.StudyData, PWACommonReportData.RptStudyDataHeader);
                    CrystalPwaEvalution1.SetParameterValue(GuiConstants.PatientNameTitle, PWACommonReportData.RptPatientName);
                    CrystalPwaEvalution1.SetParameterValue(GuiConstants.PatientNameValue, PWACommonReportData.RptPatientNameValue);
                    CrystalPwaEvalution1.SetParameterValue(GuiConstants.PatientIdTitle, PWACommonReportData.RptPatientId);
                    CrystalPwaEvalution1.SetParameterValue(GuiConstants.PatientIdValue, PWACommonReportData.RptPatientIdValue);
                    CrystalPwaEvalution1.SetParameterValue(GuiConstants.PatientDobTitle, PWACommonReportData.RptPatientDob);
                    CrystalPwaEvalution1.SetParameterValue(GuiConstants.PatientDobValue, PWACommonReportData.RptPatientDobValue);
                    CrystalPwaEvalution1.SetParameterValue(GuiConstants.PatientAgeTitle, PWACommonReportData.RptPatientAge);
                    CrystalPwaEvalution1.SetParameterValue(GuiConstants.PatientAgeValue, PWACommonReportData.RptPatientAgeValue);

                    CrystalPwaEvalution1.SetParameterValue(GuiConstants.PatientAssessmentTitle, PWACommonReportData.RptPatientAssessment);
                    CrystalPwaEvalution1.SetParameterValue(GuiConstants.PatientAssessmentValue, PWACommonReportData.RptPatientAssessmentValue);
                    CrystalPwaEvalution1.SetParameterValue(GuiConstants.PatientBPTitle, PWACommonReportData.RptPatientBP);
                    CrystalPwaEvalution1.SetParameterValue(GuiConstants.PatientBPValue, PWACommonReportData.RptPatientBPValue);
                    CrystalPwaEvalution1.SetParameterValue(GuiConstants.PatientHeightTitle, PWACommonReportData.RptPatientHeight);
                    CrystalPwaEvalution1.SetParameterValue(GuiConstants.PatientHeightValue, PWACommonReportData.RptPatientHeightValue);

                    CrystalPwaEvalution1.SetParameterValue(GuiConstants.DatabaseVersionTitle, PWACommonReportData.RptDatabaseVersionTitle);
                    CrystalPwaEvalution1.SetParameterValue(GuiConstants.DatabaseVersionValue, PWACommonReportData.RptDatabaseVersionValue);
                    CrystalPwaEvalution1.SetParameterValue(GuiConstants.WaveformPlotTitle, PWACommonReportData.RptWaveformPlotTitle);
                    CrystalPwaEvalution1.SetParameterValue(GuiConstants.WaveformPlotValue, PWACommonReportData.RptWaveformPlotValue);
                    CrystalPwaEvalution1.SetParameterValue(GuiConstants.NumberOfWaveformsTitle, PWACommonReportData.RptNumberOfWaveformsTitle);
                    CrystalPwaEvalution1.SetParameterValue(GuiConstants.NumberOfWaveformsValue, PWACommonReportData.RptNumberOfWaveformsValue);
                    CrystalPwaEvalution1.SetParameterValue(GuiConstants.QualityControlTitle, PWACommonReportData.RptQualityControlTitle);
                    CrystalPwaEvalution1.SetParameterValue(GuiConstants.QualityControlValue, PWACommonReportData.RptQualityControlValue);
                    CrystalPwaEvalution1.SetParameterValue(GuiConstants.PhysicianTitle, PWACommonReportData.RptPhysicianTitle);
                    CrystalPwaEvalution1.SetParameterValue(GuiConstants.SignatureTitle, PWACommonReportData.RptSignatureTitle);
                    CrystalPwaEvalution1.SetParameterValue(GuiConstants.SimulationModeTitle, PWACommonReportData.RptSimulationModeTitle);

                    CrystalPwaEvalution1.SetParameterValue(GuiConstants.CentralPressureWaveformTitle, PWAEvaluationReportData.RptCentralPressureWaveformTitle);
                    CrystalPwaEvalution1.SetParameterValue(GuiConstants.HeartRatePeriodTitle, PWAEvaluationReportData.RptHeartRatePeriodTitle);
                    CrystalPwaEvalution1.SetParameterValue(GuiConstants.HeartRatePeriodValue, PWAEvaluationReportData.RptHeartRatePeriodValue);
                    CrystalPwaEvalution1.SetParameterValue(GuiConstants.CentralHaemodynamicParametersTitle, PWAEvaluationReportData.RptCentralHaemodynamicParametersTitle);
                    CrystalPwaEvalution1.SetParameterValue(GuiConstants.AroticT1T2Title, PWAEvaluationReportData.RptAroticT1T2Title);
                    CrystalPwaEvalution1.SetParameterValue(GuiConstants.AorticT1T2Value, PWAEvaluationReportData.RptAorticT1T2Value);
                    CrystalPwaEvalution1.SetParameterValue(GuiConstants.P1HeightValue, PWAEvaluationReportData.RptP1HeightValue);
                    CrystalPwaEvalution1.SetParameterValue(GuiConstants.P1HeightTitle, PWAEvaluationReportData.RptP1HeightTitle);

                    CrystalPwaEvalution1.SetParameterValue(GuiConstants.AorticAixTitle, PWAEvaluationReportData.RptAorticAixTitle);
                    CrystalPwaEvalution1.SetParameterValue(GuiConstants.AorticAixValue, PWAEvaluationReportData.RptAorticAixValue);
                    CrystalPwaEvalution1.SetParameterValue(GuiConstants.AorticAIxHR75Title, PWAEvaluationReportData.RptAorticAIxHR75Title);
                    CrystalPwaEvalution1.SetParameterValue(GuiConstants.AorticAIxHR75Value, PWAEvaluationReportData.RptAorticAIxHR75Value);

                    CrystalPwaEvalution1.SetParameterValue(GuiConstants.EndSystolicPressureTitle, PWAEvaluationReportData.RptEndSystolicPressureTitle);
                    CrystalPwaEvalution1.SetParameterValue(GuiConstants.EndSystolicPressureValue, PWAEvaluationReportData.RptEndSystolicPressureValue);

                    CrystalPwaEvalution1.SetParameterValue(GuiConstants.MPSystoleDiastoleTitle, PWAEvaluationReportData.RptMPSystoleDiastoleTitle);
                    CrystalPwaEvalution1.SetParameterValue(GuiConstants.MPSystoleDiastoleValue, PWAEvaluationReportData.RptMPSystoleDiastoleValue);
                    CrystalPwaEvalution1.SetParameterValue(GuiConstants.AorticAugmentationAP_PPTitle, PWAEvaluationReportData.RptAorticAugmentationAP_PPTitle);
                    CrystalPwaEvalution1.SetParameterValue(GuiConstants.AorticAugmentationAP_PPValue, PWAEvaluationReportData.RptAorticAugmentationAP_PPValue); 

                    crysRptVwrPwaPrintReport.ReportSource = CrystalPwaEvalution1;
                    crysRptVwrPwaPrintReport.Refresh();
                    crysRptVwrPwaPrintReport.Hide();
                    CrystalPwaEvalution1.PrintOptions.PrinterName = tempPrinter;
                    CrystalPwaEvalution1.PrintOptions.PaperOrientation = GuiCommon.IsLandScape == false ? PaperOrientation.Portrait : PaperOrientation.Landscape;

                    CrystalPwaEvalution1.PrintOptions.PaperSize = PaperSize.PaperA4;
                    CrystalPwaEvalution1.PrintToPrinter(1, false, 0, 0);
                }
            }
            catch (Exception ex)
            {
                GUIExceptionHandler.HandleException(ex, this);
            }

            Close();
            Dispose();
        }

        /** This method to get the images from the Clinical intermediate form to draw it on the print report  
         * */
        private void GetPwaClinicalImages(out Image imgLogo, out Image imgClincalParam, out Image imgClinicalPressureWaveform, out Image imgRawWaveformsChart, out Image imgRawMultiWaveformsChart)
        {
            int width = objPWAClinicalPreview.guiPicBoxReportLogo.Width;
            int height = objPWAClinicalPreview.guiPicBoxReportLogo.Height;
            Point p = new Point(0, 0);
            Rectangle rect = new Rectangle(p, objPWAClinicalPreview.guiPicBoxReportLogo.Size);
            Bitmap imgPWActrl = new Bitmap(width, height);
            objPWAClinicalPreview.guiPicBoxReportLogo.DrawToBitmap(imgPWActrl, rect);
            imgLogo = imgPWActrl;

            width = objPWAClinicalPreview.guipnlSliderControls.Width;
            height = objPWAClinicalPreview.guipnlSliderControls.Height;
            p = new Point(0, 0);
            rect = new Rectangle(p, objPWAClinicalPreview.guipnlSliderControls.Size);
            imgPWActrl = new Bitmap(width, height);
            objPWAClinicalPreview.guipnlSliderControls.DrawToBitmap(imgPWActrl, rect);
            imgClincalParam = imgPWActrl;

            width = objPWAClinicalPreview.pnlCentralClinicalWaveform.Width;
            height = objPWAClinicalPreview.pnlCentralClinicalWaveform.Height;
            p = new Point(0, 0);
            rect = new Rectangle(p, objPWAClinicalPreview.pnlCentralClinicalWaveform.Size);
            imgPWActrl = new Bitmap(width, height);
            objPWAClinicalPreview.pnlCentralClinicalWaveform.DrawToBitmap(imgPWActrl, rect);
            imgClinicalPressureWaveform = imgPWActrl;

            width = objPWAClinicalPreview.pnlRawWaveformChart.Width;
            height = objPWAClinicalPreview.pnlRawWaveformChart.Height;
            p = new Point(0, 0);
            rect = new Rectangle(p, objPWAClinicalPreview.pnlRawWaveformChart.Size);
            imgPWActrl = new Bitmap(width, height);
            objPWAClinicalPreview.pnlRawWaveformChart.DrawToBitmap(imgPWActrl, rect);
            imgRawWaveformsChart = imgPWActrl;

            width = objPWAClinicalPreview.chartSinglePRawSignal.Width;
            height = objPWAClinicalPreview.chartSinglePRawSignal.Height;
            p = new Point(0, 0);
            rect = new Rectangle(p, objPWAClinicalPreview.chartSinglePRawSignal.Size);
            imgPWActrl = new Bitmap(width, height);
            objPWAClinicalPreview.chartSinglePRawSignal.DrawToBitmap(imgPWActrl, rect);
            imgRawMultiWaveformsChart = imgPWActrl;
        }

        /** This method to get the images from the Patient intermediate form to draw it on the print report  
        * */
        private void GetPwaPatientImages(out Image imgLogo, out Image imgHumanLogo, out Image imgSpSlider, out Image imgDpSlider, out Image imgHrSlider, out Image imgSpChart, out Image imgApChart, out Image imgPpChart, out Image imgAixChart)
        {
            int width = objPWAPatientPreview.guiPicBoxReportLogo.Width;
            int height = objPWAPatientPreview.guiPicBoxReportLogo.Height;
            Point p = new Point(0, 0);
            Rectangle rect = new Rectangle(p, objPWAPatientPreview.guiPicBoxReportLogo.Size);
            Bitmap imgPWActrl = new Bitmap(width, height);
            objPWAPatientPreview.guiPicBoxReportLogo.DrawToBitmap(imgPWActrl, rect);
            imgLogo = imgPWActrl;

            width = objPWAPatientPreview.guiPicBoxHumanLogo.Width;
            height = objPWAPatientPreview.guiPicBoxHumanLogo.Height;
            p = new Point(0, 0);
            rect = new Rectangle(p, objPWAPatientPreview.guiPicBoxHumanLogo.Size);
            imgPWActrl = new Bitmap(width, height);
            objPWAPatientPreview.guiPicBoxHumanLogo.DrawToBitmap(imgPWActrl, rect);
            imgHumanLogo = imgPWActrl;

            width = objPWAPatientPreview.pnlSpSlider.Width;
            height = objPWAPatientPreview.pnlSpSlider.Height;
            p = new Point(0, 0);
            rect = new Rectangle(p, objPWAPatientPreview.pnlSpSlider.Size);
            imgPWActrl = new Bitmap(width, height);
            objPWAPatientPreview.pnlSpSlider.DrawToBitmap(imgPWActrl, rect);
            imgSpSlider = imgPWActrl;

            width = objPWAPatientPreview.pnlDpSlider.Width;
            height = objPWAPatientPreview.pnlDpSlider.Height;
            p = new Point(0, 0);
            rect = new Rectangle(p, objPWAPatientPreview.pnlDpSlider.Size);
            imgPWActrl = new Bitmap(width, height);
            objPWAPatientPreview.pnlDpSlider.DrawToBitmap(imgPWActrl, rect);
            imgDpSlider = imgPWActrl;

            width = objPWAPatientPreview.pnlHrSlider.Width;
            height = objPWAPatientPreview.pnlHrSlider.Height;
            p = new Point(0, 0);
            rect = new Rectangle(p, objPWAPatientPreview.pnlHrSlider.Size);
            imgPWActrl = new Bitmap(width, height);
            objPWAPatientPreview.pnlHrSlider.DrawToBitmap(imgPWActrl, rect);
            imgHrSlider = imgPWActrl;

            width = objPWAPatientPreview.guichartSp.Width;
            height = objPWAPatientPreview.guichartSp.Height;
            p = new Point(0, 0);
            rect = new Rectangle(p, objPWAPatientPreview.guichartSp.Size);
            imgPWActrl = new Bitmap(width, height);
            objPWAPatientPreview.guichartSp.DrawToBitmap(imgPWActrl, rect);
            imgSpChart = imgPWActrl;

            width = objPWAPatientPreview.guichartAp.Width;
            height = objPWAPatientPreview.guichartAp.Height;
            p = new Point(0, 0);
            rect = new Rectangle(p, objPWAPatientPreview.guichartAp.Size);
            imgPWActrl = new Bitmap(width, height);
            objPWAPatientPreview.guichartAp.DrawToBitmap(imgPWActrl, rect);
            imgApChart = imgPWActrl;

            width = objPWAPatientPreview.guichartPp.Width;
            height = objPWAPatientPreview.guichartPp.Height;
            p = new Point(0, 0);
            rect = new Rectangle(p, objPWAPatientPreview.guichartPp.Size);
            imgPWActrl = new Bitmap(width, height);
            objPWAPatientPreview.guichartPp.DrawToBitmap(imgPWActrl, rect);
            imgPpChart = imgPWActrl;

            width = objPWAPatientPreview.guichartAix.Width;
            height = objPWAPatientPreview.guichartAix.Height;
            p = new Point(0, 0);
            rect = new Rectangle(p, objPWAPatientPreview.guichartAix.Size);
            imgPWActrl = new Bitmap(width, height);
            objPWAPatientPreview.guichartAix.DrawToBitmap(imgPWActrl, rect);
            imgAixChart = imgPWActrl;
        }

        /** This method to get the images from the Analysis intermediate form to draw it on the print report  
       * */
        private void GetPwaAnalysisImages(out Image imgLogo, out Image imgSpChart, out Image imgPpChart, out Image imgApChart, out Image imgDpMapChart, out Image imgHrChart, out Image imgAixChart)
        {
            int width = objPWAAnalysisPreview.guiPicBoxReportLogo.Width;
            int height = objPWAAnalysisPreview.guiPicBoxReportLogo.Height;
            Point p = new Point(0, 0);
            Rectangle rect = new Rectangle(p, objPWAAnalysisPreview.guiPicBoxReportLogo.Size);
            Bitmap imgPWActrl = new Bitmap(width, height);
            objPWAAnalysisPreview.guiPicBoxReportLogo.DrawToBitmap(imgPWActrl, rect);
            imgLogo = imgPWActrl;

            width = objPWAAnalysisPreview.guiradAnalysisChartSP.Width;
            height = objPWAAnalysisPreview.guiradAnalysisChartSP.Height;
            p = new Point(0, 0);
            rect = new Rectangle(p, objPWAAnalysisPreview.guiradAnalysisChartSP.Size);
            imgPWActrl = new Bitmap(width, height);
            objPWAAnalysisPreview.guiradAnalysisChartSP.DrawToBitmap(imgPWActrl, rect);
            imgSpChart = imgPWActrl;

            width = objPWAAnalysisPreview.guiradAnalysisChartPP.Width;
            height = objPWAAnalysisPreview.guiradAnalysisChartPP.Height;
            p = new Point(0, 0);
            rect = new Rectangle(p, objPWAAnalysisPreview.guiradAnalysisChartPP.Size);
            imgPWActrl = new Bitmap(width, height);
            objPWAAnalysisPreview.guiradAnalysisChartPP.DrawToBitmap(imgPWActrl, rect);
            imgPpChart = imgPWActrl;

            width = objPWAAnalysisPreview.guiradAnalysisChartAP.Width;
            height = objPWAAnalysisPreview.guiradAnalysisChartAP.Height;
            p = new Point(0, 0);
            rect = new Rectangle(p, objPWAAnalysisPreview.guiradAnalysisChartAP.Size);
            imgPWActrl = new Bitmap(width, height);
            objPWAAnalysisPreview.guiradAnalysisChartAP.DrawToBitmap(imgPWActrl, rect);
            imgApChart = imgPWActrl;

            width = objPWAAnalysisPreview.pnlDpMapChart.Width;
            height = objPWAAnalysisPreview.pnlDpMapChart.Height;
            p = new Point(0, 0);
            rect = new Rectangle(p, objPWAAnalysisPreview.pnlDpMapChart.Size);
            imgPWActrl = new Bitmap(width, height);
            objPWAAnalysisPreview.pnlDpMapChart.DrawToBitmap(imgPWActrl, rect);
            imgDpMapChart = imgPWActrl;

            width = objPWAAnalysisPreview.guiradAnalysisChartHR.Width;
            height = objPWAAnalysisPreview.guiradAnalysisChartHR.Height;
            p = new Point(0, 0);
            rect = new Rectangle(p, objPWAAnalysisPreview.guiradAnalysisChartHR.Size);
            imgPWActrl = new Bitmap(width, height);
            objPWAAnalysisPreview.guiradAnalysisChartHR.DrawToBitmap(imgPWActrl, rect);
            imgHrChart = imgPWActrl;

            width = objPWAAnalysisPreview.guiradAnalysisChartAix75.Width;
            height = objPWAAnalysisPreview.guiradAnalysisChartAix75.Height;
            p = new Point(0, 0);
            rect = new Rectangle(p, objPWAAnalysisPreview.guiradAnalysisChartAix75.Size);
            imgPWActrl = new Bitmap(width, height);
            objPWAAnalysisPreview.guiradAnalysisChartAix75.DrawToBitmap(imgPWActrl, rect);
            imgAixChart = imgPWActrl;
        }

        /** This method to get the images from the Analysis intermediate form to draw it on the print report  
        * */
        private void GetPwaQuickStartImages(out Image imgLogo, out Image imgPanel)
        {
            int width = objPWATestResultPreview.guipnlPWAReport.Width;
            int height = objPWATestResultPreview.guipnlPWAReport.Height;
            Point p = new Point(0, 0);
            Rectangle rect = new Rectangle(p, objPWATestResultPreview.guipnlPWAReport.Size);
            Bitmap imgPWActrl = new Bitmap(width, height);
            objPWATestResultPreview.guipnlPWAReport.DrawToBitmap(imgPWActrl, rect);
            imgPanel = imgPWActrl;

            width = objPWATestResultPreview.guiPicBoxReportLogo.Width;
            height = objPWATestResultPreview.guiPicBoxReportLogo.Height;
            p = new Point(0, 0);
            rect = new Rectangle(p, objPWATestResultPreview.guiPicBoxReportLogo.Size);
            imgPWActrl = new Bitmap(width, height);
            objPWATestResultPreview.guiPicBoxReportLogo.DrawToBitmap(imgPWActrl, rect);
            imgLogo = imgPWActrl;
        }

        /** This method converts image object to byte array
        */
        private byte[] ImageToByteArray(Image imageIn)
        {
            MemoryStream ms = new MemoryStream();
            imageIn.Save(ms, System.Drawing.Imaging.ImageFormat.Bmp);
            return ms.ToArray();
        }

        // TODO - These strings need to come from BLL. Will be modified later
        /** This method get text PWA print report BP validation report
       */
        private string GetPatientReportBpText()
        {
            string temp = string.Empty;

            if (GuiCommon.bizPwaobject.bloodPressure.DP.Reading <= 80)
            {
                temp = "which is considered a high reading in the normal range";
            }
            else if (GuiCommon.bizPwaobject.bloodPressure.DP.Reading > 80 && GuiCommon.bizPwaobject.bloodPressure.DP.Reading <= 90)
            {
                temp = "which is considered a high reading in the high normal range";
            }
            else if (GuiCommon.bizPwaobject.bloodPressure.DP.Reading > 90 && GuiCommon.bizPwaobject.bloodPressure.DP.Reading <= 100)
            {
                temp = "which is considered a high reading in the mild hypertension range";
            }
            else if (GuiCommon.bizPwaobject.bloodPressure.DP.Reading > 100 && GuiCommon.bizPwaobject.bloodPressure.DP.Reading <= 110)
            {
                temp = "which is considered a high reading in the moderate hypertension range";
            }
            else
            {
                temp = "which is considered a high reading in the severe range";
            }

            return temp;
        }
    }
}
