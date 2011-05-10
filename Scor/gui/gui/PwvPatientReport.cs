﻿/*
     Copyright (C) ATCOR MEDICAL PTY LTD, 2010
 
     Filename     :     PwvPatientReport
        
     Author       :     Smarajit Mishra
 
     Description  :     Creates crystal report for printing
*/
using System;
using System.Data;
using System.Drawing;
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
    /**
   * @class PwvPatientReport
   * @brief This class handles print functionality as per printing options selected by user on report screen
     * i.e It allows printing PWV Report and PWV Patient Report
   */
    public partial class PwvPatientReport : Form
    {
        private ReportPreview objReportPreview;

        /**Parameterized Constructor, used to initialize the report object     
      */
        public PwvPatientReport(ReportPreview obj)
        {
            InitializeComponent();
            objReportPreview = obj;
        }

        /** This method converts image object to byte array
        */
        public byte[] ImageToByteArray(Image imageIn)
        {
            MemoryStream ms = new MemoryStream();
            imageIn.Save(ms, System.Drawing.Imaging.ImageFormat.Bmp);
            return ms.ToArray();
        }

        /**This event fires when form is loaded.
     */
        private void PwvPatientReport_Load(object sender, EventArgs e)
        {
            CrxConfigManager configMgr = CrxConfigManager.Instance;
            configMgr.GetGeneralUserSettings();
            string tempPrinter = configMgr.GeneralSettings.PrinterName;

            if (PWVReportData.RptReportType.Equals(CrxMessagingManager.Instance.GetMessage(CrxStructCommonResourceMsg.GuiSettingsPwvPatientReport)))
            {
                // PWV patient report 
                try
                {
                    DsPwvPatientReport dsPwvPatRpt = new DsPwvPatientReport();

                    DsPwvPatientReport.DataTable1DataTable dtPwvPatRpt = new DsPwvPatientReport.DataTable1DataTable();

                    // object of data row 
                    DataRow dr1 = dtPwvPatRpt.NewRow();
                    Image imgLogo;
                    Image imgHealthyPopulation;
                    Image imgGeneralPopulation;
                    Image imgGeneralPopulationTxt;
                    Image imgCarotid;
                    Image imgFemoral;
                    Image imglblCarotid;
                    Image imglblFemoral;
                    Image imgStdDeviation;
                    
                    string bpvalue = PWVPatientReportData.RptPatientBPValue;

                    GetPwvReportImages(bpvalue, out imgLogo, out imgHealthyPopulation, out imgGeneralPopulation, out imgGeneralPopulationTxt, out imgCarotid, out imgFemoral, out imglblCarotid, out imglblFemoral, out imgStdDeviation);

                    byte[] imgbyteLogo = ImageToByteArray(imgLogo);
                    byte[] imgbyteHp = ImageToByteArray(imgHealthyPopulation);
                    byte[] imgbyteGp = ImageToByteArray(imgGeneralPopulation);
                    byte[] imgbyteGpTxt = ImageToByteArray(imgGeneralPopulationTxt);
                    
                    // add the column in table to store the image of Byte array type 
                    dr1[0] = imgbyteGpTxt;
                    dr1[6] = imgbyteGp;
                    dr1[7] = imgbyteHp;
                    dr1[8] = imgbyteLogo;

                    dtPwvPatRpt.Rows.Add(dr1);

                    dsPwvPatRpt.Tables.Clear();
                    dsPwvPatRpt.Tables.Add(dtPwvPatRpt);

                    dsPwvPatRpt.AcceptChanges();

                    CryPwvPatientReport1.SetDataSource(dsPwvPatRpt);
                }
                catch (Exception)
                {
                    crysRptVwrPwvPatientReport.Refresh();
                }

                CrxMessagingManager objMsg = CrxMessagingManager.Instance;

                CryPwvPatientReport1.SetParameterValue(GuiConstants.ReportTitle,  objMsg.GetMessage(CrxStructCommonResourceMsg.PrtPwvTextPatientReport));
                CryPwvPatientReport1.SetParameterValue(GuiConstants.ProductName, objMsg.GetMessage(CrxStructCommonResourceMsg.PrtPwvTextScor));
                CryPwvPatientReport1.SetParameterValue(GuiConstants.ReportDescription, objMsg.GetMessage(CrxStructCommonResourceMsg.PrtPwvTextRptDesc));
                CryPwvPatientReport1.SetParameterValue(GuiConstants.LblPatientDetails, objMsg.GetMessage(CrxStructCommonResourceMsg.PrtPwvTextPatientDetails));
                CryPwvPatientReport1.SetParameterValue(GuiConstants.LblName, objMsg.GetMessage(CrxStructCommonResourceMsg.PrtPwvTextNameLbl));
                CryPwvPatientReport1.SetParameterValue(GuiConstants.TxtNameValue, PWVPatientReportData.RptPatientNameValue);
                CryPwvPatientReport1.SetParameterValue(GuiConstants.LblPatientId, PWVPatientReportData.RptPatientId);
                CryPwvPatientReport1.SetParameterValue(GuiConstants.TxtPatientId, PWVPatientReportData.RptPatientIdValue);
                CryPwvPatientReport1.SetParameterValue(GuiConstants.LblAge, PWVPatientReportData.RptPatientAge);
                CryPwvPatientReport1.SetParameterValue(GuiConstants.TxtAge, PWVPatientReportData.RptPatientAgeValue);
                CryPwvPatientReport1.SetParameterValue(GuiConstants.LblGender, PWVPatientReportData.RptPatientGender);
                CryPwvPatientReport1.SetParameterValue(GuiConstants.TxtGender, PWVPatientReportData.RptPatientGenderValue);
                CryPwvPatientReport1.SetParameterValue(GuiConstants.PWVText1, objMsg.GetMessage(CrxStructCommonResourceMsg.PrtPwvText1));
                CryPwvPatientReport1.SetParameterValue(GuiConstants.PWVText2, objMsg.GetMessage(CrxStructCommonResourceMsg.PrtPwvText2));
                CryPwvPatientReport1.SetParameterValue(GuiConstants.PWVText3, objMsg.GetMessage(CrxStructCommonResourceMsg.PrtPwvText3));
                CryPwvPatientReport1.SetParameterValue(GuiConstants.PWVText4,  string.Format(objMsg.GetMessage(CrxStructCommonResourceMsg.PrtPwvText4), PWVPatientReportData.RptPatientPwvValue));
                CryPwvPatientReport1.SetParameterValue(GuiConstants.PWVText5, objMsg.GetMessage(CrxStructCommonResourceMsg.PrtPwvText5));
                CryPwvPatientReport1.SetParameterValue(GuiConstants.PWVText6, objMsg.GetMessage(CrxStructCommonResourceMsg.PrtPwvText6));
                CryPwvPatientReport1.SetParameterValue(GuiConstants.PWVText7, objMsg.GetMessage(CrxStructCommonResourceMsg.PrtPwvText7));
                CryPwvPatientReport1.SetParameterValue(GuiConstants.PWVText8, objMsg.GetMessage(CrxStructCommonResourceMsg.PrtPwvText8));
                CryPwvPatientReport1.SetParameterValue(GuiConstants.PWVText9, objMsg.GetMessage(CrxStructCommonResourceMsg.PrtPwvText9));
                CryPwvPatientReport1.SetParameterValue(GuiConstants.PWVTextGreen, objMsg.GetMessage(CrxStructCommonResourceMsg.PrtPwvTextGreen));
                CryPwvPatientReport1.SetParameterValue(GuiConstants.PWVText10, objMsg.GetMessage(CrxStructCommonResourceMsg.PrtPwvText10));
                CryPwvPatientReport1.SetParameterValue(GuiConstants.PWVText11, objMsg.GetMessage(CrxStructCommonResourceMsg.PrtPwvText11));
                CryPwvPatientReport1.SetParameterValue(GuiConstants.PWVText12, objMsg.GetMessage(CrxStructCommonResourceMsg.PrtPwvText12));
                CryPwvPatientReport1.SetParameterValue(GuiConstants.PWVTextRed, objMsg.GetMessage(CrxStructCommonResourceMsg.PrtPwvTextRed));
                CryPwvPatientReport1.SetParameterValue(GuiConstants.PWVText13, objMsg.GetMessage(CrxStructCommonResourceMsg.PrtPwvText13));
                CryPwvPatientReport1.SetParameterValue(GuiConstants.PWVText14, objMsg.GetMessage(CrxStructCommonResourceMsg.PrtPwvText14));
                CryPwvPatientReport1.SetParameterValue(GuiConstants.PWVText15, objMsg.GetMessage(CrxStructCommonResourceMsg.PrtPwvText15));
                CryPwvPatientReport1.SetParameterValue(GuiConstants.PWVText16, objMsg.GetMessage(CrxStructCommonResourceMsg.PrtPwvText16));
                CryPwvPatientReport1.SetParameterValue(GuiConstants.PWVText17, objMsg.GetMessage(CrxStructCommonResourceMsg.PrtPwvText17));
                CryPwvPatientReport1.SetParameterValue(GuiConstants.PWVText18, objMsg.GetMessage(CrxStructCommonResourceMsg.PrtPwvText18));
                CryPwvPatientReport1.SetParameterValue(GuiConstants.PWVText19, objMsg.GetMessage(CrxStructCommonResourceMsg.PrtPwvText19));
                CryPwvPatientReport1.SetParameterValue(GuiConstants.PWVText20, objMsg.GetMessage(CrxStructCommonResourceMsg.PrtPwvText20));
                CryPwvPatientReport1.SetParameterValue(GuiConstants.PWVText21, objMsg.GetMessage(CrxStructCommonResourceMsg.PrtPwvText21));
                CryPwvPatientReport1.SetParameterValue(GuiConstants.PWVText22, objMsg.GetMessage(CrxStructCommonResourceMsg.PrtPwvText22));
                CryPwvPatientReport1.SetParameterValue(GuiConstants.P3BoxText1, objMsg.GetMessage(CrxStructCommonResourceMsg.PrtPwvBoxText1));
                CryPwvPatientReport1.SetParameterValue(GuiConstants.P3BoxText2, objMsg.GetMessage(CrxStructCommonResourceMsg.PrtPwvBoxText2));
                CryPwvPatientReport1.SetParameterValue(GuiConstants.P3BoxText3, PWVPatientReportData.RptPatientBpRefRange);
                CryPwvPatientReport1.SetParameterValue(GuiConstants.P3BpValue, string.Format("{0} {1}", objMsg.GetMessage(CrxStructCommonResourceMsg.GuiReportBpColon), PWVPatientReportData.RptPatientBPValue));
                CryPwvPatientReport1.SetParameterValue(GuiConstants.P3PwvValue, string.Format("{0} {1}", objMsg.GetMessage(CrxStructCommonResourceMsg.GuiReportPwvColon), PWVPatientReportData.RptPatientPwvValue)); 
                CryPwvPatientReport1.SetParameterValue(GuiConstants.PWVReportHeader,  objMsg.GetMessage(CrxStructCommonResourceMsg.PrtPwvTextRptHeader));
                CryPwvPatientReport1.SetParameterValue(GuiConstants.PWVPage, objMsg.GetMessage(CrxStructCommonResourceMsg.PrtPwvTextPage));
                CryPwvPatientReport1.SetParameterValue(GuiConstants.PWVBPValue, PWVPatientReportData.RptPatientBPValue);
                CryPwvPatientReport1.SetParameterValue(GuiConstants.PWVGreenArea,  objMsg.GetMessage(CrxStructCommonResourceMsg.GuiReportGreenArea));
                CryPwvPatientReport1.SetParameterValue(GuiConstants.PWVRedArea, objMsg.GetMessage(CrxStructCommonResourceMsg.GuiReportRedArea));
                CryPwvPatientReport1.SetParameterValue(GuiConstants.AgeUpperLimit, BizConstants.MAXIMUM_REFERENCE_RANGE_AGE);
                CryPwvPatientReport1.SetParameterValue(GuiConstants.AgeLowerLimit, BizConstants.MINIMUM_REFERENCE_RANGE_AGE);
                CryPwvPatientReport1.SetParameterValue(GuiConstants.PWVPatientHeight, PWVPatientReportData.RptPatientHeight);
                
                crysRptVwrPwvPatientReport.ReportSource = CryPwvPatientReport1;
                crysRptVwrPwvPatientReport.Refresh();
                crysRptVwrPwvPatientReport.Hide();
                
                CryPwvPatientReport1.PrintOptions.PrinterName = tempPrinter;
                CryPwvPatientReport1.PrintOptions.PaperOrientation = GuiCommon.IsLandScape == false ? PaperOrientation.Portrait : PaperOrientation.Landscape;        

                CryPwvPatientReport1.PrintOptions.PaperSize = PaperSize.PaperA4;

                CryPwvPatientReport1.PrintToPrinter(1, false, 0, 0);   
            }
            else
            {
                // print PWV Report
                try
                {                    
                    DsPwvPatientReport dsPwvRpt = new DsPwvPatientReport();

                    DsPwvPatientReport.DataTable1DataTable dtPwvRpt = new DsPwvPatientReport.DataTable1DataTable();

                    // object of data row 
                    DataRow dr1 = dtPwvRpt.NewRow();
                    Image imgLogo;
                    Image imgHealthyPopulation;
                    Image imgGeneralPopulation;
                    Image imgGeneralPopulationTxt;
                    Image imgCarotid;
                    Image imgFemoral;
                    Image imglblCarotid;
                    Image imglblFemoral;
                    Image imgStdDeviation;

                    string bpvalue = PWVReportData.RptPatientBPValue;

                    GetPwvReportImages(bpvalue, out imgLogo, out imgHealthyPopulation, out imgGeneralPopulation, out imgGeneralPopulationTxt, out imgCarotid, out imgFemoral, out imglblCarotid, out imglblFemoral, out imgStdDeviation);

                    byte[] imgbyteLogo = ImageToByteArray(imgLogo);
                    byte[] imgbyteHp = ImageToByteArray(imgHealthyPopulation);
                    byte[] imgbyteGp = ImageToByteArray(imgGeneralPopulation);
                    byte[] imgbyteGpTxt = ImageToByteArray(imgGeneralPopulationTxt);

                    byte[] imgbyteCarotid = ImageToByteArray(imgCarotid);
                    byte[] imgbyteFemoral = ImageToByteArray(imgFemoral);
                    byte[] imgbytelblCarotid = ImageToByteArray(imglblCarotid);
                    byte[] imgbytelblFemoral = ImageToByteArray(imglblFemoral);
                    byte[] imgbyteStdDeviation = ImageToByteArray(imgStdDeviation);

                    // add the column in table to store the image of Byte array type 
                    dr1[0] = imgbyteGpTxt;
                    dr1[1] = imgbyteStdDeviation;
                    dr1[2] = imgbytelblFemoral;
                    dr1[3] = imgbytelblCarotid;
                    dr1[4] = imgbyteFemoral;
                    dr1[5] = imgbyteCarotid;
                    dr1[6] = imgbyteGp;
                    dr1[7] = imgbyteHp;
                    dr1[8] = imgbyteLogo;

                    dtPwvRpt.Rows.Add(dr1);

                    dsPwvRpt.Tables.Clear();
                    dsPwvRpt.Tables.Add(dtPwvRpt);

                    dsPwvRpt.AcceptChanges();

                    CryPwvReport1.SetDataSource(dsPwvRpt);
                }
                catch (Exception)
                {
                    crysRptVwrPwvPatientReport.Refresh();
                }

                CryPwvReport1.SetParameterValue(GuiConstants.ReportHeader, PWVReportData.RptHeader);
                CryPwvReport1.SetParameterValue(GuiConstants.ReportTitle, PWVReportData.RptTitle);
                CryPwvReport1.SetParameterValue(GuiConstants.PatientData, PWVReportData.RptPatientData);
                CryPwvReport1.SetParameterValue(GuiConstants.StudyData, PWVReportData.RptStudyData);
                CryPwvReport1.SetParameterValue(GuiConstants.PatientNameTitle, PWVReportData.RptPatientName);
                CryPwvReport1.SetParameterValue(GuiConstants.PatientNameValue, PWVReportData.RptPatientNameValue);
                CryPwvReport1.SetParameterValue(GuiConstants.PatientIdTitle, PWVReportData.RptPatientId);
                CryPwvReport1.SetParameterValue(GuiConstants.PatientIdValue, PWVReportData.RptPatientIdValue);
                CryPwvReport1.SetParameterValue(GuiConstants.PatientDobTitle, PWVReportData.RptPatientDob);
                CryPwvReport1.SetParameterValue(GuiConstants.PatientDobValue, PWVReportData.RptPatientDobValue);
                CryPwvReport1.SetParameterValue(GuiConstants.PatientAgeTitle, PWVReportData.RptPatientAge);
                CryPwvReport1.SetParameterValue(GuiConstants.PatientAgeValue, PWVReportData.RptPatientAgeValue);
                CryPwvReport1.SetParameterValue(GuiConstants.PatientGenderTitle, PWVReportData.RptPatientGender);
                CryPwvReport1.SetParameterValue(GuiConstants.PatientGenderValue, PWVReportData.RptPatientGenderValue);
                CryPwvReport1.SetParameterValue(GuiConstants.PatientAssessmentTitle, PWVReportData.RptPatientAssessment);
                CryPwvReport1.SetParameterValue(GuiConstants.PatientAssessmentValue, PWVReportData.RptPatientAssessmentValue);
                CryPwvReport1.SetParameterValue(GuiConstants.PatientBPTitle, PWVReportData.RptPatientBP);
                CryPwvReport1.SetParameterValue(GuiConstants.PatientBPValue, PWVReportData.RptPatientBPValue);
                CryPwvReport1.SetParameterValue(GuiConstants.PatientHeightTitle, PWVReportData.RptPatientHeight);
                CryPwvReport1.SetParameterValue(GuiConstants.PatientHeightValue, PWVReportData.RptPatientHeightValue);
                CryPwvReport1.SetParameterValue(GuiConstants.PatientOperatiorTitle, PWVReportData.RptPatientOperation);
                CryPwvReport1.SetParameterValue(GuiConstants.PatientOperatiorValue, PWVReportData.RptPatientOperationValue);
                CryPwvReport1.SetParameterValue(GuiConstants.PatientNotesTitle, PWVReportData.RptPatientNotes);
                CryPwvReport1.SetParameterValue(GuiConstants.PatientNotesValue, PWVReportData.RptPatientNotesValue);
                CryPwvReport1.SetParameterValue(GuiConstants.PatientDistanceTitle, PWVReportData.RptPatientDistance);
                CryPwvReport1.SetParameterValue(GuiConstants.PatientDistanceValue, PWVReportData.RptPatientDistanceValue);
                CryPwvReport1.SetParameterValue(GuiConstants.PatientPwvTitle, PWVReportData.RptPatientPwv);
                CryPwvReport1.SetParameterValue(GuiConstants.PatientPwvValue, PWVReportData.RptPatientPwvValue);
                CryPwvReport1.SetParameterValue(GuiConstants.PatientHeartRateTitle, PWVReportData.RptPatientHeartRate);
                CryPwvReport1.SetParameterValue(GuiConstants.PatientHeartRateValue, PWVReportData.RptPatientHeartRateValue);
                CryPwvReport1.SetParameterValue(GuiConstants.PatientSDTitle, PWVReportData.RptPatientStdDev);
                CryPwvReport1.SetParameterValue(GuiConstants.PatientHealthyPopulation, PWVReportData.RptPatientHealthyPop);
                CryPwvReport1.SetParameterValue(GuiConstants.PatientGeneralPopulation, PWVReportData.RptPatientGeneralPop);
                CryPwvReport1.SetParameterValue(GuiConstants.PatientCarotid, PWVReportData.RptPatientCarotid);
                CryPwvReport1.SetParameterValue(GuiConstants.PatientFemoral, PWVReportData.RptPatientFemoral);
                CryPwvReport1.SetParameterValue(GuiConstants.AgeUpperLimit, BizConstants.MAXIMUM_REFERENCE_RANGE_AGE);
                CryPwvReport1.SetParameterValue(GuiConstants.AgeLowerLimit, BizConstants.MINIMUM_REFERENCE_RANGE_AGE);
                
                crysRptVwrPwvPatientReport.ReportSource = CryPwvReport1;
                crysRptVwrPwvPatientReport.Refresh();
                crysRptVwrPwvPatientReport.Hide();
                CryPwvReport1.PrintOptions.PrinterName = tempPrinter;
                CryPwvReport1.PrintOptions.PaperOrientation = GuiCommon.IsLandScape == false ? PaperOrientation.Portrait : PaperOrientation.Landscape;        

                CryPwvReport1.PrintOptions.PaperSize = PaperSize.PaperA4;
                CryPwvReport1.PrintToPrinter(1, false, 0, 0);   
            }

            Close();
            Dispose();
        }

        /** This method creates images from the forms for charts and logo and returns the same
        */
        private void GetPwvReportImages(string bpvalue, out Image imgLogo, out Image imgHealthyPopulation, out Image imgGeneralPopulation, out Image imgGeneralPopulationTxt, out Image imgCarotid, out Image imgFemoral, out Image imglblCarotid, out Image imglblFemoral, out Image imgStdDeviation)
        {
            int width = objReportPreview.guiPicBoxReportLogo.Width;
            int height = objReportPreview.guiPicBoxReportLogo.Height;
            Point p = new Point(0, 0);
            Rectangle rect = new Rectangle(p, objReportPreview.guiPicBoxReportLogo.Size);
            Bitmap imgPWVctrl = new Bitmap(width, height);
            objReportPreview.guiPicBoxReportLogo.DrawToBitmap(imgPWVctrl, rect);
            imgLogo = imgPWVctrl;
                        
            width = objReportPreview.guichartNormalRange.Width;
            height = objReportPreview.guichartNormalRange.Height;
            p = new Point(0, 0);
            rect = new Rectangle(p, objReportPreview.guichartNormalRange.Size);
            imgPWVctrl = new Bitmap(width, height);
            objReportPreview.guichartNormalRange.DrawToBitmap(imgPWVctrl, rect);
            imgHealthyPopulation = imgPWVctrl;
       
            width = objReportPreview.guichartReferenceRange.Width;
            height = objReportPreview.guichartReferenceRange.Height;
            p = new Point(0, 0);
            rect = new Rectangle(p, objReportPreview.guichartReferenceRange.Size);
            imgPWVctrl = new Bitmap(width, height);
            objReportPreview.guichartReferenceRange.DrawToBitmap(imgPWVctrl, rect);
            imgGeneralPopulation = imgPWVctrl;
       
            width = objReportPreview.guilblBPmsg.Width;
            height = objReportPreview.guilblBPmsg.Height;
            p = new Point(0, 0);
            rect = new Rectangle(p, objReportPreview.guilblBPmsg.Size);
            imgPWVctrl = new Bitmap(width, height);
            objReportPreview.guilblBPmsg.DrawToBitmap(imgPWVctrl, rect);
            imgGeneralPopulationTxt = imgPWVctrl;
                    
            width = objReportPreview.guichartCarotid.Width;
            height = objReportPreview.guichartCarotid.Height;
            p = new Point(0, 0);
            rect = new Rectangle(p, objReportPreview.guichartCarotid.Size);
            imgPWVctrl = new Bitmap(width, height);
            objReportPreview.guichartCarotid.DrawToBitmap(imgPWVctrl, rect);
            imgCarotid = imgPWVctrl;

            width = objReportPreview.guiradChartFemoral.Width;
            height = objReportPreview.guiradChartFemoral.Height;
            p = new Point(0, 0);
            rect = new Rectangle(p, objReportPreview.guiradChartFemoral.Size);
            imgPWVctrl = new Bitmap(width, height);
            objReportPreview.guiradChartFemoral.DrawToBitmap(imgPWVctrl, rect);
            imgFemoral = imgPWVctrl;

            width = objReportPreview.guilblCarotidImage.Width;
            height = objReportPreview.guilblCarotidImage.Height;
            p = new Point(0, 0);
            rect = new Rectangle(p, objReportPreview.guilblCarotidImage.Size);
            imgPWVctrl = new Bitmap(width, height);
            objReportPreview.guilblCarotidImage.DrawToBitmap(imgPWVctrl, rect);
            imglblCarotid = imgPWVctrl;

            width = objReportPreview.guilblFemoralImage.Width;
            height = objReportPreview.guilblFemoralImage.Height;
            p = new Point(0, 0);
            rect = new Rectangle(p, objReportPreview.guilblFemoralImage.Size);
            imgPWVctrl = new Bitmap(width, height);
            objReportPreview.guilblFemoralImage.DrawToBitmap(imgPWVctrl, rect);
            imglblFemoral = imgPWVctrl;

            width = objReportPreview.guilblStdDeviationImage.Width;
            height = objReportPreview.guilblStdDeviationImage.Height;
            p = new Point(0, 0);
            rect = new Rectangle(p, objReportPreview.guilblStdDeviationImage.Size);
            imgPWVctrl = new Bitmap(width, height);
            objReportPreview.guilblStdDeviationImage.DrawToBitmap(imgPWVctrl, rect);
            imgStdDeviation = imgPWVctrl;
        }
    }
}
