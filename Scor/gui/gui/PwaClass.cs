/*
     Copyright (C) ATCOR MEDICAL PTY LTD, 2010
 
     Filename     :     System Key
        
     Author       :    Nitesh Chhedda
 
     Description  :     This class file is used to implement the methodsfor PWA class.
*/

using System;
using AtCor.Scor.BusinessLogic;
using AtCor.Scor.DataAccess;
using AtCor.Scor.CrossCutting.Configuration;
using AtCor.Scor.CrossCutting.Messaging;    

/**
 * @namespace AtCor.Scor.Gui.Presentation
 * @brief This namespace implements Presentation related classes.
 * 
 */
namespace AtCor.Scor.Gui.Presentation
{
    /**
    * @class PwaClass
    * @brief PwaClass is used to implement the IScor Stratergy class.
    * This class is part of the strategy implementation for the different modes.
    */
    public abstract class PwaClass : IScorStrategy 
    {
        public abstract void DispatchCaptureData();

        public abstract void LoadReport();
       
        public abstract void FillSession();

        public abstract void SetHeightWeightUnits();

        public abstract void SetDistanceMethodAndUnits();

        public abstract void SetBloodPressure();

        public abstract bool StartCapture();

        public abstract bool StopCapture();

        public abstract void ActionPerformedAfterClickingCancel();

        public abstract void CalculateReportAfterSuccessfulCapture();

        public abstract void SaveCapturedData();

        public abstract void InitialiseCaptureScreen();

        public abstract void HandleKeyDownEventOnCaptureScreen(System.Windows.Forms.KeyEventArgs e);

        public abstract void CreateTextFileForFailedCapture();

        public abstract void LoadTemporaryReport();

        public abstract void EnableDisableCaptureButton();

        // void AppendCaptureData();        
        // void CalculateReport();
        // void CalculateAge();
        // void Populate(crxPwv);
        // bool Validate();
        // void RecalculatePWVReport(crxPwv);
        // void GetBpRefRange();
        // bool Initialise();
        // void ValidateAgeLimit();
    }

    public class CuffPwa : PwaClass 
    {        
        public CuffPwa()
        {
          BizSession.Instance().SwitchMeasurement(BizMode.PWA);
          GuiCommon.bizPwaobject = (BizPWA)BizSession.Instance().measurement;         
        }

        public override void DispatchCaptureData()
        {           
        }

        public override void LoadReport()
        {
            try
            {
                ((PWAReport)GuiCommon.PWAReportChildForm).LoadPWAReport();
                ((PWAReport)GuiCommon.PWAReportChildForm).BringToFront();
            }
            catch (NotImplementedException notImplementedEx)
            {
                throw notImplementedEx;
            }
            catch (Exception ex)
            {
                throw ex;
            }
        }

        public override void FillSession()
        {
            ((Setup)GuiCommon.SetupChildForm).FillPwaDetailsSession();
        }
      
        public override void SetHeightWeightUnits()
        {
            ((Setup)GuiCommon.SetupChildForm).SetPwaHeightWeightUnits();
        }

        public override void SetDistanceMethodAndUnits()
        {            
        }

        public override void SetBloodPressure()
        {           
        }

        public override bool StartCapture()
        {
           return GuiCommon.bizPwaobject.StartCapture();
        }

        public override bool StopCapture()
        {
           return GuiCommon.bizPwaobject.StopCapture(); 
        }

        public override void ActionPerformedAfterClickingCancel()
        {
            ((Capture)GuiCommon.CaptureChildForm).ActionPerformedAfterClickingCancelForPwaMode();    
        }

        public override void CalculateReportAfterSuccessfulCapture()
        {
            if (GuiCommon.StartupScreen.ToUpper().Equals(CrxStructCommonResourceMsg.QuickStart))
            {
                ((Capture)GuiCommon.CaptureChildForm).TickButtonActionForcPwaQuickStart();
            }
            else
            {
                ((Capture)GuiCommon.CaptureChildForm).TickButtonActionForPwaMode();
            }
        }

        public override void SaveCapturedData()
        {
            GuiCommon.bizPwaobject.SaveCaptureData();  
        }

        public override void InitialiseCaptureScreen()
        {
            ((Capture)GuiCommon.CaptureChildForm).InitialSettingsForPwaModeCapture();   
        }

        public override void HandleKeyDownEventOnCaptureScreen(System.Windows.Forms.KeyEventArgs e)
        {
            ((Capture)GuiCommon.CaptureChildForm).HandleKeyDownEventForPwaMode(e);    
        }

        public override void CreateTextFileForFailedCapture()
        {
            ((Capture)GuiCommon.CaptureChildForm).CreateTextFileOnReportFailedForPwaMode();
        }

        public override void LoadTemporaryReport()
        {
            ((PWATestResult)GuiCommon.PWATestResultChildForm).LoadTemporaryReport(); 
        }

        public override void EnableDisableCaptureButton()
        {
            ((Capture)GuiCommon.CaptureChildForm).RefreshOkButtonForPwaMode(); 
        }
    }
}