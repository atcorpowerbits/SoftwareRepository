/*
     Copyright (C) ATCOR MEDICAL PTY LTD, 2010
 
     Filename     :     GuiConstants
        
     Author       :     Nitesh Chhedda
 
     Description  :     Common class defining constants used over application
*/
using System.Configuration;

/**
 * @namespace AtCor.Scor.Gui.Presentation
 * @brief This namespace implements Presentation related classes.
 * 
 */
namespace AtCor.Scor.Gui.Presentation
{
    /**
   * @class GuiConstants
   * @brief This class contains global constant which will be used over application across different forms
   */
    public static class GuiConstants
    {
        /** SystemId => system identifier used for storing in backend
         *  DefaultValue => default value for height weight & BP & distance 
         *  separator => used to split strings
         *  SourceData => to be part of Crx struct in future
         * */
        
        public const int SystemId = 31256;
        public const ushort DefaultValue = 9999;
        public const short SdefaultValue = 9999;
        public const char Separator = ',';
        public const string SourceData = "SQLCLIENT";
        public const string DefaultAtcorImage = "AtcorLogo";
        public const string DefaultReportTitle = "AtCor Medical [THE PRODUCT] (R)";               

        // values used for disabling close button of form
        public const int WsMinimizebox = 0x20000;
        public const int CsDblclks = 0x8;
        public const int CpNocloseButton = 0x200;

        // value for conversion from mm to cm.
        public const int DivisionFactor = 10;

        // readonly values for setting chart max & min height to adjust series plotting away from edges of the chart
        public static readonly double ChartAreaMinimumY = 0.96;  
        public static readonly double ChartAreaMaximumY = 1.04;

        // double.Parse(ConfigurationManager.AppSettings[AppConfigParams.ChartAreaMinY.ToString()]);
        // double.Parse(ConfigurationManager.AppSettings[AppConfigParams.ChartAreaMaxY.ToString()]);
        
        // readonly string for setting font name used overall application
        public static readonly string FontName = ConfigurationManager.AppSettings[AppConfigParams.GuiFontName.ToString()]; 
       
        // following readonly values are defined for setting parameter values in Crystal report for the report generation functionality
        // Crystal reports binds values based on paramters defined in the report
        // PWV patient report
        public static readonly string ReportTitle = "ReportTitle";
        public static readonly string ProductName = "ProductName";
        public static readonly string ReportDescription = "ReportDescription";
        public static readonly string LblPatientDetails = "lblPatientDetails";
        public static readonly string LblName = "lblName";
        public static readonly string TxtNameValue = "txtNameValue";
        public static readonly string LblPatientId = "lblPatientId";
        public static readonly string TxtPatientId = "txtPatientId";
        public static readonly string LblAge = "lblAge";
        public static readonly string TxtAge = "txtAge";
        public static readonly string LblGender = "lblGender";
        public static readonly string TxtGender = "txtGender";
        public static readonly string PWVText1 = "PWVText1";
        public static readonly string PWVText2 = "PWVText2";
        public static readonly string PWVText3 = "PWVText3";
        public static readonly string PWVText4 = "PWVText4";
        public static readonly string PWVText5 = "PWVText5";
        public static readonly string PWVText6 = "PWVText6";
        public static readonly string PWVText7 = "PWVText7";
        public static readonly string PWVText8 = "PWVText8";
        public static readonly string PWVText9 = "PWVText9";
        public static readonly string PWVTextGreen = "PWVTextGreen";
        public static readonly string PWVText10 = "PWVText10";
        public static readonly string PWVText11 = "PWVText11";
        public static readonly string PWVText12 = "PWVText12";
        public static readonly string PWVTextRed = "PWVTextRed";
        public static readonly string PWVText13 = "PWVText13";
        public static readonly string PWVText14 = "PWVText14";
        public static readonly string PWVText15 = "PWVText15";
        public static readonly string PWVText16 = "PWVText16";
        public static readonly string PWVText17 = "PWVText17";
        public static readonly string PWVText18 = "PWVText18";
        public static readonly string PWVText19 = "PWVText19";
        public static readonly string PWVText20 = "PWVText20";
        public static readonly string PWVText21 = "PWVText21";
        public static readonly string PWVText22 = "PWVText22";
        public static readonly string P3BoxText1 = "P3BoxText1";
        public static readonly string P3BoxText2 = "P3BoxText2";
        public static readonly string P3BoxText3 = "P3BoxText3";
        public static readonly string P3BoxText4 = "P3BoxText4";
        public static readonly string P3BpValue = "P3BpValue";
        public static readonly string P3PwvValue = "P3PwvValue";
        public static readonly string PWVReportHeader = "PWVReportHeader";
        public static readonly string PWVPage = "PWVPage";
        public static readonly string PWVBPValue = "PWVBPValue";
        public static readonly string PWVGreenArea = "PWVGreenArea";
        public static readonly string PWVRedArea = "PWVRedArea";
        public static readonly string AgeUpperLimit = "AgeUpperLimit";
        public static readonly string AgeLowerLimit = "AgeLowerLimit";
        public static readonly string PWVPatientHeight = "PWVPatientHeight";
        public static readonly string HealthyPopulation = "HealthyPopulation";
        public static readonly string GeneralPopulation = "GeneralPopulation";
        
        // PWV report
        public static readonly string ReportHeader = "ReportHeader";
        public static readonly string PatientData = "PatientData";
        public static readonly string StudyData = "StudyData";
        public static readonly string PatientNameTitle = "PatientNameTitle";
        public static readonly string PatientNameValue = "PatientNameValue";
        public static readonly string PatientIdTitle = "PatientIdTitle";
        public static readonly string PatientIdValue = "PatientIdValue";
        public static readonly string PatientDobTitle = "PatientDobTitle";
        public static readonly string PatientDobValue = "PatientDobValue";
        public static readonly string PatientAgeTitle = "PatientAgeTitle";
        public static readonly string PatientAgeValue = "PatientAgeValue";
        public static readonly string PatientGenderTitle = "PatientGenderTitle";
        public static readonly string PatientGenderValue = "PatientGenderValue";
        public static readonly string PatientAssessmentTitle = "PatientAssessmentTitle";
        public static readonly string PatientAssessmentValue = "PatientAssessmentValue";
        public static readonly string PatientBPTitle = "PatientBPTitle";
        public static readonly string PatientBPValue = "PatientBPValue";
        public static readonly string PatientHeightTitle = "PatientHeightTitle";
        public static readonly string PatientHeightValue = "PatientHeightValue";
        public static readonly string PatientOperatiorTitle = "PatientOperatiorTitle";
        public static readonly string PatientOperatiorValue = "PatientOperatiorValue";
        public static readonly string PatientNotesTitle = "PatientNotesTitle";
        public static readonly string PatientNotesValue = "PatientNotesValue";
        public static readonly string PatientDistanceTitle = "PatientDistanceTitle";
        public static readonly string PatientDistanceValue = "PatientDistanceValue";
        public static readonly string PatientPwvTitle = "PatientPwvTitle";
        public static readonly string PatientPwvValue = "PatientPwvValue";
        public static readonly string PatientHeartRateTitle = "PatientHeartRateTitle";
        public static readonly string PatientHeartRateValue = "PatientHeartRateValue";
        public static readonly string PatientSDTitle = "PatientSDTitle";
        public static readonly string PatientHealthyPopulation = "PatientHealthyPopulation";
        public static readonly string PatientGeneralPopulation = "PatientGeneralPopulation";
        public static readonly string PatientCarotid = "PatientCarotid";
        public static readonly string PatientFemoral = "PatientFemoral";

        // PWV Analysis
        public static readonly string PWVTitle = "PWVTitle";
        public static readonly string HeartRateTitle = "HeartRateTitle";
        public static readonly string BpChartTitle = "BpChartTitle";
        public static readonly string BPChartValidation = "BPChartValidation";
        public static readonly string BpChartTextValue = "BpChartTextValue";
        

        // PWA Clinical 
        public static readonly string DatabaseVersionTitle      = "DatabaseVersionTitle";
        public static readonly string DatabaseVersionValue      = "DatabaseVersionValue";
        public static readonly string WaveformPlotTitle         = "WaveformPlotTitle";
        public static readonly string WaveformPlotValue         = "WaveformPlotValue";
        public static readonly string NumberOfWaveformsTitle    = "NumberOfWaveformsTitle";
        public static readonly string NumberOfWaveformsValue    = "NumberOfWaveformsValue";
        public static readonly string QualityControlTitle       = "QualityControlTitle";
        public static readonly string QualityControlValue       = "QualityControlValue";
        public static readonly string SimulationModeTitle       = "SimulationModeTitle";

        public static readonly string InterpretationTitle = "InterpretationTitle";
        public static readonly string InterpretationValue = "InterpretationValue";
        public static readonly string PhysicianTitle = "PhysicianTitle";
        public static readonly string SignatureTitle = "SignatureTitle";
        public static readonly string ClinicalParametersTitle = "ClinicalParametersTitle";
        public static readonly string CentralPressureWaveformTitle = "CentralPressureWaveformTitle";
        public static readonly string BrachialTitle = "BrachialTitle";
        public static readonly string AorticTitle = "AorticTitle";

        public static readonly string SPTitle = "SPTitle";
        public static readonly string DPTitle = "DPTitle";
        public static readonly string MPTitle = "MPTitle";
        public static readonly string PPTitle = "PPTitle";
        public static readonly string HRTitle = "HRTitle";

        public static readonly string SPBrachialValue = "SPBrachialValue";
        public static readonly string DPBrachialValue = "DPBrachialValue";
        public static readonly string MPBrachialValue = "MPBrachialValue";
        public static readonly string PPBrachialValue = "PPBrachialValue";
        public static readonly string HRBrachialValue = "HRBrachialValue";

        public static readonly string SPAorticValue = "SPAorticValue";
        public static readonly string DPAorticValue = "DPAorticValue";
        public static readonly string MPAorticValue = "MPAorticValue";
        public static readonly string PPAorticValue = "PPAorticValue";
        public static readonly string HRAorticValue = "HRAorticValue";

        // PWA Evaluation 
        public static readonly string HeartRatePeriodTitle = "HeartRatePeriodTitle";
        public static readonly string HeartRatePeriodValue = "HeartRatePeriodValue";
        public static readonly string CentralHaemodynamicParametersTitle = "CentralHaemodynamicParametersTitle";
        public static readonly string AroticT1T2Title = "AroticT1T2Title";
        public static readonly string AorticT1T2Value = "AorticT1T2Value";
        public static readonly string P1HeightValue = "P1HeightValue";
        public static readonly string P1HeightTitle = "P1HeightTitle";
        public static readonly string AorticAixTitle = "AorticAixTitle";
        public static readonly string AorticAixValue = "AorticAixValue";
        public static readonly string AorticAIxHR75Title = "AorticAIxHR75Title";
        public static readonly string AorticAIxHR75Value = "AorticAIxHR75Value";
        public static readonly string EndSystolicPressureTitle = "EndSystolicPressureTitle";
        public static readonly string EndSystolicPressureValue = "EndSystolicPressureValue";
        public static readonly string MPSystoleDiastoleTitle = "MPSystoleDiastoleTitle";
        public static readonly string MPSystoleDiastoleValue = "MPSystoleDiastoleValue";
        public static readonly string AorticAugmentationAP_PPTitle = "AorticAugmentationAP_PPTitle";
        public static readonly string AorticAugmentationAP_PPValue = "AorticAugmentationAP_PPValue";

        public static string DateWithComma = string.Empty;
        public static string PwaIdWithComma = string.Empty;

        public enum AppConfigParams
        {
            WaitInterval,
            WarningImage,
            InfoImage,
            DefaultInstanceName,
            CeMarkImage,
            Version,
            Copyright,
            AnalysisFontName,
            AnalysisFontMax,
            AnalysisFontMin,
            ChartAreaMinY,
            ChartAreaMaxY,
            GuiFontName,
            GuiBackColor,
            SetupScreenDirect,
            SetupScreenSubtracting,
            ApplicationThemeName,
            AtcorImageIcon,
            MinYearForDob,
            ServiceManualPath,
            OperatorGuidePath,
            SupportUrl,
            AtcorHomepage,
            DefaultCulture,
            DbDefaultFileName,
            DbVersionNumber,
            QualityIndicatorImage,
            QualityCrossImage
        }
    }
}
