/*
     Copyright (C) ATCOR MEDICAL PTY LTD, 2010
 
     Filename     :     System Key
        
     Author       :    Nitesh Chhedda
 
     Description  :     This class file is used to implement the methodsfor PWV class.
*/

using AtCor.Scor.BusinessLogic;
using AtCor.Scor.DataAccess;
using AtCor.Scor.CrossCutting.Configuration;
/**
 * @namespace AtCor.Scor.Gui.Presentation
 * @brief This namespace implements Presentation related classes.
 * 
 */
namespace AtCor.Scor.Gui.Presentation
{
    /**
    * @class Pwv
    * @brief Pwv is used to implement the IScor Stratergy class.
    * This class is part of the strategy implementation for the different modes.
    */
    public class Pwv : IScorStrategy
    {        
        public Pwv()
        {
            BizSession.Instance().SwitchMeasurement(BizMode.PWV);
            GuiCommon.bizObject = (BizPWV)BizSession.Instance().measurement;
            DalModule.Instance.SetStreamingMode(DalStreamingMode.Pwv);     
        }

        public void DispatchCaptureData()
        {
            BizSession.Instance().DispatchCaptureData();
        }

        public void LoadReport()
        {
            ((Report)GuiCommon.ReportChildForm).LoadPWVReport();
            ((Report)GuiCommon.ReportChildForm).BringToFront();
        }       

        public void FillSession()
        {
            ((Setup)GuiCommon.SetupChildForm).FillPwvDetailsSession();   
        }
        
        public void SetHeightWeightUnits()
        {
            ((Setup)GuiCommon.SetupChildForm).SetPwvHeightWeightUnits();
        }

        public void SetDistanceMethodAndUnits()
        {
            ((Setup)GuiCommon.SetupChildForm).SetPwvDistanceMethodAndUnits();
        }

        public void SetBloodPressure()
        {
            ((Setup)GuiCommon.SetupChildForm).SetPwvBloodPressure();                
        }

        public bool StartCapture()
        {
           return GuiCommon.bizObject.StartCapture(); 
        }

        public bool StopCapture()
        {
            return GuiCommon.bizObject.StopCapture();
        }

        public void ActionPerformedAfterClickingCancel()
        {
            ((Capture)GuiCommon.CaptureChildForm).ActionPerformedAfterClickingCancelForPwvMode();   
        }

        public void CalculateReportAfterSuccessfulCapture()
        {
            ((Capture)GuiCommon.CaptureChildForm).TickButtonAction();  
        }

        public void SaveCapturedData()
        {
            GuiCommon.bizObject.SaveCaptureData();  
        }

        public void InitialiseCaptureScreen()
        {
            ((Capture)GuiCommon.CaptureChildForm).InitialSettingsForPwvModeCapture();  
        }

        public void HandleKeyDownEventOnCaptureScreen(System.Windows.Forms.KeyEventArgs e)
        {
            ((Capture)GuiCommon.CaptureChildForm).HandleKeyDownEventForPwvMode(e);   
        }

        public void CreateTextFileForFailedCapture()
        {
            ((Capture)GuiCommon.CaptureChildForm).CreateTextFileOnReportFailed();
        }
    }
}
