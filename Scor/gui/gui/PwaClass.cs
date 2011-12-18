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
        
        public abstract void EnableRepeatAndCaptureTab(bool value);
        
        public abstract void SaveChangesOnMenuFocus();

        public abstract void SaveReportChangesOnEdit();
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
            try
            {
                (GuiCommon.SetupChildForm).FillPwaDetailsSession();
            }
            catch (Exception ex)
            {
                throw ex;
            }
        }
      
        public override void SetHeightWeightUnits()
        {
            try
            {
                (GuiCommon.SetupChildForm).SetPwaHeightWeightUnits();
            }
            catch (Exception ex)
            {
                throw ex;
            }
        }

        public override void SetDistanceMethodAndUnits()
        {
            // Do nothing in PWA mode. This method needs implementation in PWV mode only
        }

        public override void SetBloodPressure()
        {
            // Do nothing in PWA mode. This method needs implementation in PWV mode only
        }

        public override bool StartCapture()
        {
            try
            {
                return GuiCommon.bizPwaobject.StartCapture();
            }
            catch (Exception ex)
            {
                throw ex;
            }
        }

        public override bool StopCapture()
        {
            try
            {
                return GuiCommon.bizPwaobject.StopCapture();
            }
            catch (Exception ex)
            {
                throw ex;
            }
        }

        public override void ActionPerformedAfterClickingCancel()
        {
            try
            {
                (GuiCommon.CaptureChildForm).ActionPerformedAfterClickingCancelForPwaMode();
            }
            catch (Exception ex)
            {
                throw ex;
            }
        }

        public override void CalculateReportAfterSuccessfulCapture()
        {
            try
            {
                if (GuiCommon.StartupScreen.ToUpper().Equals(CrxStructCommonResourceMsg.QuickStart))
                {
                    (GuiCommon.CaptureChildForm).TickButtonActionForcPwaQuickStart();
                }
                else
                {
                    (GuiCommon.CaptureChildForm).TickButtonActionForPwaMode();
                }
            }
            catch (Exception ex)
            {
                throw ex;
            }
        }

        public override void SaveCapturedData()
        {
            try
            {
                GuiCommon.bizPwaobject.SaveCaptureData();
            }
            catch (Exception ex)
            {
                throw ex;
            }
        }

        public override void InitialiseCaptureScreen()
        {
            try
            {
              (GuiCommon.CaptureChildForm).InitialSettingsForPwaModeCapture();
            }
            catch (Exception ex)
            {
                throw ex;
            }
        }

        public override void HandleKeyDownEventOnCaptureScreen(System.Windows.Forms.KeyEventArgs e)
        {
            try
            {
               // (GuiCommon.CaptureChildForm).HandleKeyDownEventForPwaMode(e);
            }
            catch (Exception ex)
            {
                throw ex;
            }
        }

        public override void CreateTextFileForFailedCapture()
        {
            try
            {
                (GuiCommon.CaptureChildForm).CreateTextFileOnReportFailedForPwaMode();
            }
            catch (Exception ex)
            {
                throw ex;
            }
        }

        public override void LoadTemporaryReport()
        {
            try
            {
                (GuiCommon.PWATestResultChildForm).LoadTemporaryReport();
            }
            catch (Exception ex)
            {
                throw ex;
            }
        }

        public override void EnableDisableCaptureButton()
        {
            try
            {
                (GuiCommon.CaptureChildForm).RefreshOkButtonForPwaMode();
            }
            catch (Exception ex)
            {
                throw ex;
            }
        }
        
        public override void EnableRepeatAndCaptureTab(bool value)
        {
            try
            {
                (GuiCommon.PWAReportChildForm).EnableRepeatAndCaptureTab(value);
            }
            catch (Exception ex)
            {
                throw ex;
            }
        }
        
        public override void SaveChangesOnMenuFocus()
        {
            try
            {
                (GuiCommon.PWAReportChildForm).SaveChangesOnMenuFocus();
            }
            catch (Exception ex)
            {
                throw ex;
            }
        }

        public override void SaveReportChangesOnEdit()
        {
            try
            {
                (GuiCommon.PWAReportChildForm).SaveChangesOnEdit();
            }
            catch (Exception ex)
            {
                throw ex;
            }
        }
    }
}