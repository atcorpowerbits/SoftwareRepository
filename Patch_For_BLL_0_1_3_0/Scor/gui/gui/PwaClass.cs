using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using AtCor.Scor.BusinessLogic;

namespace AtCor.Scor.Gui.Presentation
{
    public abstract class PwaClass : IScorStrategy 
    {
        public abstract void DispatchCaptureData();

        public abstract void LoadReport();

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
    }
}
