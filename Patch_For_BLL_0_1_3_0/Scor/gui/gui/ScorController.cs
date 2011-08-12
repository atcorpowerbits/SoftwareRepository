using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace AtCor.Scor.Gui.Presentation
{
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
    }
}
