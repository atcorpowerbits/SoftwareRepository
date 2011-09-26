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
      
        private void PWAPrintReport_Load(object sender, EventArgs e)
        {
            try
            {
                if (PWACommonReportData.RptPrintType.Equals(CrxStructCommonResourceMsg.PwaClinicalReport))
                {
                    CrxConfigManager configMgr = CrxConfigManager.Instance;
                    configMgr.GetGeneralUserSettings();
                    string tempPrinter = configMgr.GeneralSettings.PrinterName;
                    CrxMessagingManager objMsg = CrxMessagingManager.Instance;

                    DsPwaPrintReport dsPwaClinical = new DsPwaPrintReport();
                    DsPwaPrintReport.ClinicalTableDataTable dtPwaClinical = new DsPwaPrintReport.ClinicalTableDataTable();

                    // Object of dataRow
                    DataRow dr = dtPwaClinical.NewRow();
                    Image imgLogo;
                    Image imgClincalParam;
                    Image imgClinicalPressureWaveform;

                    GetPwaClinicalImages(out imgLogo, out imgClincalParam, out imgClinicalPressureWaveform);

                    byte[] imgByteLogo = ImageToByteArray(imgLogo);
                    byte[] imgByteClinicalParam = ImageToByteArray(imgClincalParam);
                    byte[] imgByteClinicalPressureWaveform = ImageToByteArray(imgClinicalPressureWaveform);

                    // dr["ImageLogo"] = imgByteLogo;
                    // dr["ClinicalParameter"] = imgByteClinicalParam;
                    dr[0] = imgByteLogo;
                    dr[1] = imgByteClinicalParam;
                    dr[2] = imgByteClinicalPressureWaveform;
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
                    CrystalPwaClinical1.SetParameterValue(GuiConstants.PatientAgeTitle, PWACommonReportData.RptPatientAge);
                    CrystalPwaClinical1.SetParameterValue(GuiConstants.PatientAgeValue, PWACommonReportData.RptPatientAgeValue);

                    // CrystalPwaClinical1.SetParameterValue(GuiConstants.PatientGenderTitle, PWACommonReportData.RptPatientGender);
                    // CrystalPwaClinical1.SetParameterValue(GuiConstants.PatientGenderValue, PWACommonReportData.RptPatientGenderValue);
                    CrystalPwaClinical1.SetParameterValue(GuiConstants.PatientAssessmentTitle, PWACommonReportData.RptPatientAssessment);
                    CrystalPwaClinical1.SetParameterValue(GuiConstants.PatientAssessmentValue, PWACommonReportData.RptPatientAssessmentValue);
                    CrystalPwaClinical1.SetParameterValue(GuiConstants.PatientBPTitle, PWACommonReportData.RptPatientBP);
                    CrystalPwaClinical1.SetParameterValue(GuiConstants.PatientBPValue, PWACommonReportData.RptPatientBPValue);
                    CrystalPwaClinical1.SetParameterValue(GuiConstants.PatientHeightTitle, PWACommonReportData.RptPatientHeight);
                    CrystalPwaClinical1.SetParameterValue(GuiConstants.PatientHeightValue, PWACommonReportData.RptPatientHeightValue);

                    // CrystalPwaClinical1.SetParameterValue(GuiConstants.PatientOperatiorTitle, PWVReportData.RptPatientOperation);
                    // CrystalPwaClinical1.SetParameterValue(GuiConstants.PatientOperatiorValue, PWVReportData.RptPatientOperationValue);
                    // CrystalPwaClinical1.SetParameterValue(GuiConstants.PatientDistanceTitle, PWVReportData.RptPatientDistance);
                    // CrystalPwaClinical1.SetParameterValue(GuiConstants.PatientDistanceValue, PWVReportData.RptPatientDistanceValue);
                    CrystalPwaClinical1.SetParameterValue(GuiConstants.DatabaseVersionTitle, PWACommonReportData.RptDatabaseVersionTitle);
                    CrystalPwaClinical1.SetParameterValue(GuiConstants.DatabaseVersionValue, PWACommonReportData.RptDatabaseVersionValue);
                    CrystalPwaClinical1.SetParameterValue(GuiConstants.WaveformPlotTitle, PWACommonReportData.RptWaveformPlotTitle);
                    CrystalPwaClinical1.SetParameterValue(GuiConstants.WaveformPlotValue, PWACommonReportData.RptWaveformPlotValue);
                    CrystalPwaClinical1.SetParameterValue(GuiConstants.NumberOfWaveformsTitle, PWACommonReportData.RptNumberOfWaveformsTitle);
                    CrystalPwaClinical1.SetParameterValue(GuiConstants.NumberOfWaveformsValue, PWACommonReportData.RptNumberOfWaveformsValue);
                    CrystalPwaClinical1.SetParameterValue(GuiConstants.QualityControlTitle, PWACommonReportData.RptQualityControlTitle);
                    CrystalPwaClinical1.SetParameterValue(GuiConstants.QualityControlValue, PWACommonReportData.RptQualityControlValue);
                    CrystalPwaClinical1.SetParameterValue(GuiConstants.SimulationModeTitle, PWACommonReportData.RptSimulationModeTitle);

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
                else
                {
                    CrxConfigManager configMgr = CrxConfigManager.Instance;
                    configMgr.GetGeneralUserSettings();
                    string tempPrinter = configMgr.GeneralSettings.PrinterName;
                    CrxMessagingManager objMsg = CrxMessagingManager.Instance;

                    DsPwaPrintReport dsPwaClinical = new DsPwaPrintReport();
                    DsPwaPrintReport.ClinicalTableDataTable dtPwaClinical = new DsPwaPrintReport.ClinicalTableDataTable();

                    // Object of dataRow
                    DataRow dr = dtPwaClinical.NewRow();
                    Image imgLogo;
                    Image imgClincalParam;
                    Image imgClinicalPressureWaveform;

                    GetPwaClinicalImages(out imgLogo, out imgClincalParam, out imgClinicalPressureWaveform);

                    byte[] imgByteLogo = ImageToByteArray(imgLogo);
                    byte[] imgByteClinicalParam = ImageToByteArray(imgClincalParam);
                    byte[] imgByteClinicalPressureWaveform = ImageToByteArray(imgClinicalPressureWaveform);

                    // dr["ImageLogo"] = imgByteLogo;
                    // dr["ClinicalParameter"] = imgByteClinicalParam;
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

                    // CrystalPwaEvalution1.SetParameterValue(GuiConstants.PatientGenderTitle, PWACommonReportData.RptPatientGender);
                    // CrystalPwaEvalution1.SetParameterValue(GuiConstants.PatientGenderValue, PWACommonReportData.RptPatientGenderValue);
                    CrystalPwaEvalution1.SetParameterValue(GuiConstants.PatientAssessmentTitle, PWACommonReportData.RptPatientAssessment);
                    CrystalPwaEvalution1.SetParameterValue(GuiConstants.PatientAssessmentValue, PWACommonReportData.RptPatientAssessmentValue);
                    CrystalPwaEvalution1.SetParameterValue(GuiConstants.PatientBPTitle, PWACommonReportData.RptPatientBP);
                    CrystalPwaEvalution1.SetParameterValue(GuiConstants.PatientBPValue, PWACommonReportData.RptPatientBPValue);
                    CrystalPwaEvalution1.SetParameterValue(GuiConstants.PatientHeightTitle, PWACommonReportData.RptPatientHeight);
                    CrystalPwaEvalution1.SetParameterValue(GuiConstants.PatientHeightValue, PWACommonReportData.RptPatientHeightValue);

                    // CrystalPwaClinical1.SetParameterValue(GuiConstants.PatientOperatiorTitle, PWVReportData.RptPatientOperation);
                    // CrystalPwaClinical1.SetParameterValue(GuiConstants.PatientOperatiorValue, PWVReportData.RptPatientOperationValue);
                    // CrystalPwaClinical1.SetParameterValue(GuiConstants.PatientDistanceTitle, PWVReportData.RptPatientDistance);
                    // CrystalPwaClinical1.SetParameterValue(GuiConstants.PatientDistanceValue, PWVReportData.RptPatientDistanceValue);
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
        }

        private void GetPwaClinicalImages(out Image imgLogo, out Image imgClincalParam, out Image imgClinicalPressureWaveform)
        {
            int width = objPWAClinicalPreview.guiPicBoxReportLogo.Width;
            int height = objPWAClinicalPreview.guiPicBoxReportLogo.Height;
            Point p = new Point(0, 0);
            Rectangle rect = new Rectangle(p, objPWAClinicalPreview.guiPicBoxReportLogo.Size);
            Bitmap imgPWActrl = new Bitmap(width, height);
            objPWAClinicalPreview.guiPicBoxReportLogo.DrawToBitmap(imgPWActrl, rect);
            imgLogo = imgPWActrl;

            width = objPWAClinicalPreview.pnlCentralClinicalParameters.Width;
            height = objPWAClinicalPreview.pnlCentralClinicalParameters.Height;
            p = new Point(0, 0);
            rect = new Rectangle(p, objPWAClinicalPreview.pnlCentralClinicalParameters.Size);
            imgPWActrl = new Bitmap(width, height);
            objPWAClinicalPreview.pnlCentralClinicalParameters.DrawToBitmap(imgPWActrl, rect);
            imgClincalParam = imgPWActrl;

            width = objPWAClinicalPreview.pnlCentralClinicalWaveform.Width;
            height = objPWAClinicalPreview.pnlCentralClinicalWaveform.Height;
            p = new Point(0, 0);
            rect = new Rectangle(p, objPWAClinicalPreview.pnlCentralClinicalWaveform.Size);
            imgPWActrl = new Bitmap(width, height);
            objPWAClinicalPreview.pnlCentralClinicalWaveform.DrawToBitmap(imgPWActrl, rect);
            imgClinicalPressureWaveform = imgPWActrl;
        }

        /** This method converts image object to byte array
        */
        public byte[] ImageToByteArray(Image imageIn)
        {
            MemoryStream ms = new MemoryStream();
            imageIn.Save(ms, System.Drawing.Imaging.ImageFormat.Bmp);
            return ms.ToArray();
        }           
    }
}
