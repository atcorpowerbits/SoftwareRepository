/*
     Copyright (C) ATCOR MEDICAL PTY LTD, 2010
 
     Filename     :     System Key
        
     Author       :    Nitesh Chhedda
 
     Description  :     This class file is used to implement the methodsfor PWV class.
*/

using AtCor.Scor.BusinessLogic;
using AtCor.Scor.DataAccess;
using AtCor.Scor.CrossCutting.Configuration;
using System;
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
        }

        public void DispatchCaptureData()
        {
            try
            {
                BizSession.Instance().DispatchCaptureData();
            }
            catch (Exception ex)
            {
                throw ex;
            }
        }

        public void LoadReport()
        {
            try
            {
                GuiCommon.ReportChildForm.LoadPWVReport();
                GuiCommon.ReportChildForm.BringToFront();
            }
            catch (Exception ex)
            {
                throw ex;
            }
        }       

        public void FillSession()
        {
            try
            {
                GuiCommon.SetupChildForm.FillPwvDetailsSession();
            }
            catch (Exception ex)
            {
                throw ex;
            }
        }
        
        public void SetHeightWeightUnits()
        {
            try
            {
                GuiCommon.SetupChildForm.SetPwvHeightWeightUnits();
            }
            catch (Exception ex)
            {
                throw ex;
            }
        }

        public void SetDistanceMethodAndUnits()
        {
            try
            {
                GuiCommon.SetupChildForm.SetPwvDistanceMethodAndUnits();
            }
            catch (Exception ex)
            {
                throw ex;
            }
        }

        public void SetBloodPressure()
        {
            try
            {
                GuiCommon.SetupChildForm.SetPwvBloodPressure();                
            }
            catch (Exception ex)
            {
                throw ex;
            }
        }

        public bool StartCapture()
        {
            try
            {
                return GuiCommon.bizObject.StartCapture();
            }
            catch (Exception ex)
            {
                throw ex;
            }
        }

        public bool StopCapture()
        {
            try
            {
                return GuiCommon.bizObject.StopCapture();
            }
            catch (Exception ex)
            {
                throw ex;
            }
        }

        public void ActionPerformedAfterClickingCancel()
        {
            try
            {
                if (GuiCommon.CaptureChildForm != null)
                {
                    GuiCommon.CaptureChildForm.ActionPerformedAfterClickingCancelForPwvMode();
                }
            }
            catch (Exception ex)
            {
                throw ex;
            }
        }

        public void CalculateReportAfterSuccessfulCapture()
        {
            try
            {
                GuiCommon.CaptureChildForm.TickButtonAction();
            }
            catch (Exception ex)
            {
                throw ex;
            }
        }

        public void SaveCapturedData()
        {
            try
            {
                GuiCommon.bizObject.SaveCaptureData();
            }
            catch (Exception ex)
            {
                throw ex;
            }
        }

        public void InitialiseCaptureScreen()
        {
            try
            {
                GuiCommon.CaptureChildForm.InitialSettingsForPwvModeCapture();
            }
            catch (Exception ex)
            {
                throw ex;
            }
        }

        public void HandleKeyDownEventOnCaptureScreen(System.Windows.Forms.KeyEventArgs e)
        {
            try
            {
                if (GuiCommon.CaptureChildForm != null)
                {
                    GuiCommon.CaptureChildForm.HandleKeyDownEventForPwvMode(e);
                }
            }
            catch (Exception ex)
            {
                throw ex;
            }
        }

        public void CreateTextFileForFailedCapture()
        {
            try
            {
                GuiCommon.CaptureChildForm.CreateTextFileOnReportFailed();
            }
            catch (Exception ex)
            {
                throw ex;
            }
        }

        public void LoadTemporaryReport()
        {
            // Do nothing in PWV mode. This method needs implementation in PWA mode only
        }

        public void EnableDisableCaptureButton()
        {
            try
            {
                GuiCommon.CaptureChildForm.RefreshOkButtonForPwvMode(); 
            }
            catch (Exception ex)
            {
                throw ex;
            }
        }
        
        public void EnableRepeatAndCaptureTab(bool value)
        {
            try
            {
                GuiCommon.ReportChildForm.EnableRepeatAndCaptureTab(value);
            }
            catch (Exception ex)
            {
                throw ex;
            }
        }
        
        public void SaveChangesOnMenuFocus()
        {
            try
            {
                GuiCommon.ReportChildForm.SaveChangesOnMenuFocus();
            }
            catch (Exception ex)
            {
                throw ex;
            }
        }

        public void SaveReportChangesOnEdit()
        {
            try
            {
                GuiCommon.ReportChildForm.SaveChangesOnEdit();
            }
            catch (Exception ex)
            {
                throw ex;
            }
        }
    }
}
