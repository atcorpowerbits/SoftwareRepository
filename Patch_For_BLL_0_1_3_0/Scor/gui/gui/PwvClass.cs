using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using AtCor.Scor.BusinessLogic;
using AtCor.Scor.CrossCutting.Configuration;

namespace AtCor.Scor.Gui.Presentation
{
    public class Pwv : IScorStrategy
    {
        BizPWV bizObject;

        public Pwv()
        {
            BizSession.Instance().SwitchMeasurement(BizMode.PWV);
            bizObject = (BizPWV)BizSession.Instance().measurement; 
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
    }
}
