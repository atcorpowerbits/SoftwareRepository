using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.Configuration;
using AtCor.Scor.BusinessLogic;
using AtCor.Scor.CrossCutting;
using AtCor.Scor.CrossCutting.Messaging;
using AtCor.Scor.CrossCutting.Configuration;
using System.Windows.Forms.DataVisualization.Charting;
using AtCor.Scor.CrossCutting.DatabaseManager;
using System.Collections;

namespace AtCor.Scor.Gui.Presentation
{
    public partial class PWAAnalysisPreview : Form
    {
        const int LblVerticalAngle = -90; // angle of labels to display vertically on analysis screen when more records are are selected
        const int LblHorizontalAngle = 0; // angle of labels to display horizontally on analysis screen when few records are are selected

        readonly CrxMessagingManager oMsgMgr = CrxMessagingManager.Instance;
        BizPWA obj;

        CrxConfigManager crxMgrObject = CrxConfigManager.Instance;
        CrxDBManager dbMagr = CrxDBManager.Instance;

        CrxStructPWAMeasurementData crxPwaData = new CrxStructPWAMeasurementData();
        CrxStructCuffPWAMeasurementData crxPwaCuffData = new CrxStructCuffPWAMeasurementData();
        CrxStructTonoPWAMeasurementData crxPwaTonoData = new CrxStructTonoPWAMeasurementData();

        string dfBPVlaue = GuiConstants.SdefaultValue.ToString(); // Get and store the default BP vlaue
        string[] date; // date array to be used on analysis screen
        string[] apRate; // Ap rate array to be used on analysis screen
        string[] hrRate; // Hr rate array to be used on analysis screen
        string[] spRate; // Sp rate array to be used on analysis screen
        string[] dpRate; // Dp rate array to be used on analysis screen
        string[] mpRate; // Mp rate array to be used on analysis screen
        string[] ppRate; // Pp rate array to be used on analysis screen

        public PWAAnalysisPreview()
        {
            InitializeComponent();
        }

        private void PWAAnalysisPreview_Load(object sender, EventArgs e)
        {
            try
            {
                obj = (BizPWA)BizSession.Instance().measurement;
                SetTextForLabels();
                PlotAnalysisTrendCharts(GuiConstants.DateWithComma);

                PWAPrintReport objPwaPrintReport = new PWAPrintReport(this);

                objPwaPrintReport.Show();
                objPwaPrintReport.Hide();

                Close();
                Dispose();
            }
            catch (Exception ex)
            {
                GUIExceptionHandler.HandleException(ex, this);
            }
        }

        /** This method sets text for labels from resource file
       * */
        private void SetTextForLabels()
        {
            CrxConfigManager crxConfig = CrxConfigManager.Instance;
            string defaultImgPath = ConfigurationManager.AppSettings[GuiConstants.AppConfigParams.AtcorImageIcon.ToString()];
            guiPicBoxReportLogo.Image = string.IsNullOrEmpty(crxConfig.GeneralSettings.ReportLogoPath) ? Image.FromFile(defaultImgPath) : Image.FromFile(crxConfig.GeneralSettings.ReportLogoPath);
        }

         /** This method shows analysis trend graph
         * */
        private void PlotAnalysisTrendCharts(string dateSelected)
        {
            try
            {
                // if date ends with comma, truncate it as it creates empty value in array for dates
                if (dateSelected.EndsWith(oMsgMgr.GetMessage(CrxStructCommonResourceMsg.GuiDisplayComma)))
                {
                    dateSelected = dateSelected.Remove(dateSelected.Length - 1);
                }

                /// date = dateSelected.Split(GuiConstants.Separator);
                string[] dateClac = dateSelected.Split(GuiConstants.Separator);
                 
                 string calcPwaIdWithComma = string.Empty;
                 string calcDateWithComma = string.Empty;

                 if (dateClac.Length > 10)
                 {
                     string[] tempPwaId = GuiConstants.PwaIdWithComma.Split(GuiConstants.Separator);

                     string[] calcDate = new string[10];
                     string[] calcPwaId = new string[10];
                     date = new string[10];

                     int clcStrt = dateClac.Length - 10;
                     for (int i = clcStrt, j = 0; i < dateClac.Length; i++, j++)
                     {
                         calcDate[j] = dateClac[i];
                         date[j] = dateClac[i];
                         calcPwaId[j] = tempPwaId[i];
                         string tempIdWithComma = string.Empty;
                         tempIdWithComma = tempPwaId[i].ToString();
                         calcPwaIdWithComma = calcPwaIdWithComma + tempIdWithComma + GuiConstants.Separator;
                         string tempDateWithComma = string.Empty;
                         tempDateWithComma = string.Format("{0:g}", Convert.ToDateTime(dateClac[i].ToString()));
                         if (j == 1 || j == 3 || j == 5 || j == 7)
                         {
                             calcDateWithComma = calcDateWithComma + tempDateWithComma + Environment.NewLine;
                         }
                         else
                         {
                             calcDateWithComma = calcDateWithComma + tempDateWithComma + "\t\t\t";
                         }
                     }
                 }
                 else
                 {
                     date = dateSelected.Split(GuiConstants.Separator);
                     for (int i = 0; i < date.Length; i++)
                     {
                         string tempDateWithComma = string.Empty;
                         tempDateWithComma = date[i].ToString();
                         if (i == 1 || i == 3 || i == 5 || i == 7)
                         {
                             calcDateWithComma = calcDateWithComma + tempDateWithComma + Environment.NewLine;
                         }
                         else
                         {
                             calcDateWithComma = calcDateWithComma + tempDateWithComma + "\t\t\t";
                         }
                     }

                     calcPwaIdWithComma = GuiConstants.PwaIdWithComma;         
                 }

                 PWAAnalysisReportData.RptPatientAssessmentValue = calcDateWithComma;

                // check for connection
                 if (dbMagr.CheckConnection(GuiCommon.ServerNameString(), crxMgrObject.GeneralSettings.SourceData) == 0)
                 {
                     CrxStructPWATrendData trendData = new CrxStructPWATrendData();

                     // fetch records for selected assessments
                     /// dbMagr.GetPWATrendData(GuiConstants.PwaIdWithComma, trendData);
                     dbMagr.GetPWATrendData(calcPwaIdWithComma, trendData);

                     if (!string.IsNullOrEmpty(trendData.ApValidArrStr) && !string.IsNullOrEmpty(trendData.HrValidArrStr) && !string.IsNullOrEmpty(trendData.SpValidArrStr) && !string.IsNullOrEmpty(trendData.DpValidArrStr) && !string.IsNullOrEmpty(trendData.MpValidArrStr))
                     {
                         PlotApTrendData(trendData);
                         PlotHrTrendData(trendData);
                         PlotSpTrendData(trendData);
                         PlotDpMpTrendData(trendData);
                         PlotPpTrendData(trendData);
                         PlotAixTrendData(calcPwaIdWithComma);
                     }
                 }                
            }
            catch (Exception ex)
            {
                GUIExceptionHandler.HandleException(ex, this);
            }
        }

        /** This method plots Sp trend graph
       * */
        private void PlotSpTrendData(CrxStructPWATrendData trendData)
        {
            guiradAnalysisChartSP.Titles[0].ForeColor = Color.Black;
            guiradAnalysisChartSP.Titles[0].Font = new Font("Arial", 8, FontStyle.Bold);

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
                    /// guiradAnalysisChartSP.Series[0].Points.AddXY(series, double.Parse(spRate[series], CrxCommon.nCI));
                    /// guiradAnalysisChartSP.Series[1].Points.AddXY(series, double.Parse(spRate[series], CrxCommon.nCI));
                  
                    // check if value is 9999
                    if (!spRate[series].Equals(dfBPVlaue))
                    {
                        guiradAnalysisChartSP.Series[0].Points.AddXY(series, double.Parse(spRate[series], CrxCommon.nCI));
                        guiradAnalysisChartSP.Series[1].Points.AddXY(series, double.Parse(spRate[series], CrxCommon.nCI));
                    }
                    else
                    {
                        guiradAnalysisChartSP.Series[1].Points.AddXY(series, double.Parse("-10"));
                    }
                }

                guiradAnalysisChartSP.ChartAreas[0].AxisX.Maximum = spRate.Length;
                /// guiradAnalysisChartSP.Titles[0].Text = "SP";

                BindCustomLabelForTrendCharts(guiradAnalysisChartSP, date.Length);
                guiradChart_Customize(guiradAnalysisChartSP);
            }
        }

        /** This method plots DpMp trend graph
      * */
        private void PlotDpMpTrendData(CrxStructPWATrendData trendData)
        {
            // guiradAnalysisChartDPMP.Titles[0].Text = "SP MAP";
            guiradAnalysisChartDPMP.Titles[0].ForeColor = Color.Black;
            guiradAnalysisChartDPMP.Titles[0].Font = new Font("Arial", 8, FontStyle.Bold);
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
                    /// guiradAnalysisChartDPMP.Series[0].Points.AddXY(series, double.Parse(dpRate[series], CrxCommon.nCI));
                    /// guiradAnalysisChartDPMP.Series[1].Points.AddXY(series, double.Parse(dpRate[series], CrxCommon.nCI));
                    /// guiradAnalysisChartDPMP.Series[2].Points.AddXY(series, double.Parse(mpRate[series], CrxCommon.nCI));
                    /// guiradAnalysisChartDPMP.Series[3].Points.AddXY(series, double.Parse(mpRate[series], CrxCommon.nCI));
                     
                    // check if value is 9999
                    if (!dpRate[series].Equals(dfBPVlaue))
                    {
                        guiradAnalysisChartDPMP.Series[0].Points.AddXY(series, double.Parse(dpRate[series], CrxCommon.nCI));
                        guiradAnalysisChartDPMP.Series[1].Points.AddXY(series, double.Parse(dpRate[series], CrxCommon.nCI));
                    }
                    else
                    {
                        guiradAnalysisChartDPMP.Series[1].Points.AddXY(series, double.Parse("-10"));
                    }

                    if (!mpRate[series].Equals(GuiConstants.SdefaultValue.ToString()))
                    {
                        guiradAnalysisChartDPMP.Series[2].Points.AddXY(series, double.Parse(mpRate[series], CrxCommon.nCI));
                        guiradAnalysisChartDPMP.Series[3].Points.AddXY(series, double.Parse(mpRate[series], CrxCommon.nCI));
                    }
                    else
                    {
                        guiradAnalysisChartDPMP.Series[3].Points.AddXY(series, double.Parse("-10"));
                    }
                }

                guiradAnalysisChartDPMP.ChartAreas[0].AxisX.Maximum = mpRate.Length;
                BindCustomLabelForTrendCharts(guiradAnalysisChartDPMP, date.Length);
                guiradChart_Customize(guiradAnalysisChartDPMP);
            }
        }

        /** This method plots Pp trend graph
         * */
        private void PlotPpTrendData(CrxStructPWATrendData trendData)
        {
            guiradAnalysisChartPP.Titles[0].ForeColor = Color.Black;
            guiradAnalysisChartPP.Titles[0].Font = new Font("Arial", 8, FontStyle.Bold);

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
            setChartMinMaxForYAxis(guiradAnalysisChartPP, tempDouble, out minValue);

            // plot Pp rate series
            if (ppRate.Length > 0)
            {
                for (int series = 0; series < ppRate.Length; series++)
                {
                   /// guiradAnalysisChartPP.Series[0].Points.AddXY(series, double.Parse(ppRate[series], CrxCommon.nCI));
                   /// guiradAnalysisChartPP.Series[1].Points.AddXY(series, double.Parse(ppRate[series], CrxCommon.nCI));
                   
                    // check if value is 9999
                    if (!ppRate[series].Equals(dfBPVlaue))
                    {
                        guiradAnalysisChartPP.Series[0].Points.AddXY(series, double.Parse(ppRate[series], CrxCommon.nCI));
                        guiradAnalysisChartPP.Series[1].Points.AddXY(series, double.Parse(ppRate[series], CrxCommon.nCI));
                    }
                    else
                    {
                        guiradAnalysisChartPP.Series[1].Points.AddXY(series, double.Parse("-10"));
                    }
                }

                guiradAnalysisChartPP.ChartAreas[0].AxisX.Maximum = ppRate.Length;
               /// guiradAnalysisChartPP.Titles[0].Text = "PP";
                BindCustomLabelForTrendCharts(guiradAnalysisChartPP, date.Length);
                guiradChart_Customize(guiradAnalysisChartPP);
            }
        }

        /** This method plots Hr trend graph
        * */
        private void PlotHrTrendData(CrxStructPWATrendData trendData)
        {
            guiradAnalysisChartHR.Titles[0].ForeColor = Color.Black;
            guiradAnalysisChartHR.Titles[0].Font = new Font("Arial", 8, FontStyle.Bold);

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
                    if (!hrRate[series].Equals(dfBPVlaue))
                    {
                        guiradAnalysisChartHR.Series[0].Points.AddXY(series, double.Parse(hrRate[series], CrxCommon.nCI));
                        guiradAnalysisChartHR.Series[1].Points.AddXY(series, double.Parse(hrRate[series], CrxCommon.nCI));
                    }
                    else
                    {
                        guiradAnalysisChartHR.Series[1].Points.AddXY(series, double.Parse("-10"));
                    }
                }

                guiradAnalysisChartHR.ChartAreas[0].AxisX.Maximum = hrRate.Length;
               /// guiradAnalysisChartHR.Titles[0].Text = "HR";
                BindCustomLabelForTrendCharts(guiradAnalysisChartHR, date.Length);
                guiradChart_Customize(guiradAnalysisChartHR);
            }
        }

        /** This method plots Ap trend graph
        * */
        private void PlotApTrendData(CrxStructPWATrendData trendData)
        {          
            guiradAnalysisChartAP.Titles[0].ForeColor = Color.Black;
            guiradAnalysisChartAP.Titles[0].Font = new Font("Arial", 8, FontStyle.Bold);

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
                    /// guiradAnalysisChartAP.Series[0].Points.AddXY(series, double.Parse(apRate[series], CrxCommon.nCI));
                    /// guiradAnalysisChartAP.Series[1].Points.AddXY(series, double.Parse(apRate[series], CrxCommon.nCI));

                    // check if value is 9999
                    if (!apRate[series].Equals(dfBPVlaue))
                    {
                        guiradAnalysisChartAP.Series[0].Points.AddXY(series, double.Parse(apRate[series], CrxCommon.nCI));
                        guiradAnalysisChartAP.Series[1].Points.AddXY(series, double.Parse(apRate[series], CrxCommon.nCI));
                    }
                    else
                    {
                        guiradAnalysisChartAP.Series[1].Points.AddXY(series, double.Parse("-10"));
                    }
                }

                guiradAnalysisChartAP.ChartAreas[0].AxisX.Maximum = apRate.Length;
               /// guiradAnalysisChartAP.Titles[0].Text = "AP";

                BindCustomLabelForTrendCharts(guiradAnalysisChartAP, date.Length);
                guiradChart_Customize(guiradAnalysisChartAP);
            }
        }

        /** This method plots Aix trend graph
        * */
        private void PlotAixTrendData(string pwaIdWithComma)
        {           
            double[] aixDataArr = prepareAix75Data(pwaIdWithComma);
            string[] aixArr = CrxDBManager.Instance.CommonDoubleArrToStringArr(aixDataArr);

            guiradAnalysisChartAix75.Titles[0].ForeColor = Color.Black;
            guiradAnalysisChartAix75.Titles[0].Font = new Font("Arial", 8, FontStyle.Bold);

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
                        guiradAnalysisChartAix75.Series[1].Points.AddXY(series, double.Parse("-10"));
                    }
                }

                guiradAnalysisChartAix75.ChartAreas[0].AxisX.Maximum = aixDataArr.Length;
               /// guiradAnalysisChartAix75.Titles[0].Text = "Aix@75";
                BindCustomLabelForTrendCharts(guiradAnalysisChartAix75, date.Length);
                guiradChart_Customize(guiradAnalysisChartAix75);
            }
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
                               
                aixBizPWA.Populate(pdataAix, cdataAix);
                aixBizPWA.Validate();
                aixData[counter] = Math.Round(aixBizPWA.AGPH_HR75);
            }

            return aixData;
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

        /** This method is used to bind custom labels for X-Axis for Analysis trend charts
      * */
        private void BindCustomLabelForTrendCharts(Chart chartName, int seriesLength)
        {
            Font labelFontMax = new Font(ConfigurationManager.AppSettings[GuiConstants.AppConfigParams.AnalysisFontName.ToString()].ToString(), float.Parse(ConfigurationManager.AppSettings[GuiConstants.AppConfigParams.AnalysisFontMax.ToString()].ToString()));  // sets font max size for analysis chart x axis labels
            Font labelFontMin = new Font(ConfigurationManager.AppSettings[GuiConstants.AppConfigParams.AnalysisFontName.ToString()].ToString(), float.Parse(ConfigurationManager.AppSettings[GuiConstants.AppConfigParams.AnalysisFontMin.ToString()].ToString())); // sets font min size for analysis chart x axis labels
            chartName.ChartAreas[0].AxisX.CustomLabels.Clear();
            chartName.ChartAreas[0].AxisX.LabelStyle.Angle = LblHorizontalAngle;
            chartName.ChartAreas[0].AxisX.LabelStyle.Font = labelFontMax;
           
            for (int hrseries1 = 0; hrseries1 < seriesLength; hrseries1++)
            {
                // if (hrseries1 > (5 * labelInterval))
                if (hrseries1 == 0)
                {
                    chartName.ChartAreas[0].AxisX.LabelStyle.Font = new Font(ConfigurationManager.AppSettings[GuiConstants.AppConfigParams.AnalysisFontName.ToString()].ToString(), float.Parse(ConfigurationManager.AppSettings[GuiConstants.AppConfigParams.AnalysisFontMax.ToString()].ToString()) - 2);
                }
                else if (hrseries1 == 1)
                {
                    chartName.ChartAreas[0].AxisX.LabelStyle.Font = new Font(ConfigurationManager.AppSettings[GuiConstants.AppConfigParams.AnalysisFontName.ToString()].ToString(), float.Parse(ConfigurationManager.AppSettings[GuiConstants.AppConfigParams.AnalysisFontMin.ToString()].ToString()) + 1);
                }
                else if (hrseries1 >= 2)
                {
                    chartName.ChartAreas[0].AxisX.LabelStyle.Font = new Font(ConfigurationManager.AppSettings[GuiConstants.AppConfigParams.AnalysisFontName.ToString()].ToString(), float.Parse(ConfigurationManager.AppSettings[GuiConstants.AppConfigParams.AnalysisFontMin.ToString()].ToString()) + 1);
                    chartName.ChartAreas[0].AxisX.LabelStyle.Angle = LblVerticalAngle;
                }

                chartName.ChartAreas[0].AxisX.CustomLabels.Add(hrseries1 - 1, hrseries1 + 1, string.Format("{0:g}", Convert.ToDateTime(date[hrseries1].ToString())));                
            }
        }

        /** This event customizes label display on PWA trend Large chart
       * */
        private void guiradChart_Customize(Chart sampleChart)
        {
            try
            {
                const int SeriesPoints = 2;
                if (apRate != null)
                {
                    if (apRate.Length > SeriesPoints)
                    {
                        foreach (CustomLabel cl in sampleChart.ChartAreas[0].AxisX.CustomLabels)
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
