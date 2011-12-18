/*
     Copyright (C) ATCOR MEDICAL PTY LTD, 2010
 
     Filename     :     System Key
        
     Author       :    Nitesh Chhedda
 
     Description  :     This class file is used to set the strategy for the application.
*/

/**
 * @namespace AtCor.Scor.Gui.Presentation
 * @brief This namespace implements Presentation related classes.
 * 
 */
using AtCor.Scor.BusinessLogic;
using AtCor.Scor.CrossCutting;
using System.Windows.Forms;
using System;

namespace AtCor.Scor.Gui.Presentation
{
    /**
    * @class ScorController
    * @brief ScorController is used to decide the strategy with the help of IScorStrategy.    
    */

    public class ScorController
    {
        private IScorStrategy scorStrategy;
        Form frmObject = new Form();

        // public string mode = string.Empty;
        public void SetScorStrategy(IScorStrategy newStrategy)
        {
            try
            {
                scorStrategy = newStrategy;
            }
            catch (Exception ex)
            {
                throw ex;
            }
        }

        public void DispatchCaptureData()
        {
            try
            {
                scorStrategy.DispatchCaptureData();
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
                scorStrategy.LoadReport();
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
                scorStrategy.FillSession();
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
                scorStrategy.SetHeightWeightUnits();
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
                scorStrategy.SetDistanceMethodAndUnits();
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
                scorStrategy.SetBloodPressure();
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
                scorStrategy.ActionPerformedAfterClickingCancel();
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
                return scorStrategy.StartCapture();
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
                return scorStrategy.StopCapture();
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
                scorStrategy.CalculateReportAfterSuccessfulCapture();
            }
            catch (Exception ex)
            {
                throw ex; 
            }
        }

        public void SaveCaptureData()
        {
            try
            {
                scorStrategy.SaveCapturedData();
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
                scorStrategy.InitialiseCaptureScreen();
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
                scorStrategy.HandleKeyDownEventOnCaptureScreen(e);
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
                scorStrategy.CreateTextFileForFailedCapture();
            }
            catch (Exception ex)
            {
                throw ex;
            }
        }

        public void LoadTemporaryReport()
        {
            try
            {
                scorStrategy.LoadTemporaryReport();
            }
            catch (Exception ex)
            {
                throw ex;
            }
        }

        public void EnableDisableCaptureButton()
        {
            try
            {
                scorStrategy.EnableDisableCaptureButton(); 
            }
            catch (Exception ex)
            {
                throw ex;
            }
        }
        
        public void EnableRepeatAndCaptureTab(bool value)
        {
            scorStrategy.EnableRepeatAndCaptureTab(value);
        }
        
        public void SaveChangesOnMenuFocus()
        {
            scorStrategy.SaveChangesOnMenuFocus();
        }

        public void SaveReportChangesOnEdit()
        {
            scorStrategy.SaveReportChangesOnEdit();
        }
    }
}
