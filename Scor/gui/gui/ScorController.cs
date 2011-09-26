﻿/*
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

namespace AtCor.Scor.Gui.Presentation
{
    /**
    * @class ScorController
    * @brief ScorController is used to decide the strategy with the help of IScorStrategy.    
    */

    public class ScorController
    {
        private IScorStrategy scorStrategy;
       
        // public string mode = string.Empty;
        public void SetScorStrategy(IScorStrategy newStrategy)
        {
            scorStrategy = newStrategy;            
        }

        public void DispatchCaptureData()
        {
            scorStrategy.DispatchCaptureData();              
        }

        public void LoadReport()
        {
            scorStrategy.LoadReport();              
        }

        public void FillSession()
        {
            scorStrategy.FillSession();  
        }     

        public void SetHeightWeightUnits()
        {
            scorStrategy.SetHeightWeightUnits();
        }

        public void SetDistanceMethodAndUnits()
        {
            scorStrategy.SetDistanceMethodAndUnits();
        }

        public void SetBloodPressure()
        {
            scorStrategy.SetBloodPressure();
        }

        public void ActionPerformedAfterClickingCancel()
        {
            scorStrategy.ActionPerformedAfterClickingCancel(); 
        }

        public bool StartCapture()
        {
           return scorStrategy.StartCapture();  
        }

        public bool StopCapture()
        {
           return scorStrategy.StopCapture(); 
        }

        public void CalculateReportAfterSuccessfulCapture()
        {
            scorStrategy.CalculateReportAfterSuccessfulCapture();  
        }

        public void SaveCaptureData()
        {
            scorStrategy.SaveCapturedData();
        }

        public void InitialiseCaptureScreen()
        {
            scorStrategy.InitialiseCaptureScreen(); 
        }

        public void HandleKeyDownEventOnCaptureScreen(System.Windows.Forms.KeyEventArgs e)
        {
            scorStrategy.HandleKeyDownEventOnCaptureScreen(e);
        }

        public void CreateTextFileForFailedCapture()
        {
            scorStrategy.CreateTextFileForFailedCapture(); 
        }
    }
}
