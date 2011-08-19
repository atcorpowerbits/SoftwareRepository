/*
     Copyright (C) ATCOR MEDICAL PTY LTD, 2010
 
     Filename     :     System Key
        
     Author       :    Nitesh Chhedda
 
     Description  :     This class file is used to implement the methodsfor PWA class.
*/

using System;
using AtCor.Scor.DataAccess;

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

        // bool StartCapture();
        // void StopCapture();
        // void AppendCaptureData();
        // void SaveCapturedData();
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
          DalModule.Instance.SetStreamingMode(DalStreamingMode.cPwa);
        }

        override public void DispatchCaptureData()
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
    }
}