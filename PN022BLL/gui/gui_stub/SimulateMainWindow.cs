using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using Telerik.WinControls;
using AtCor.Scor.BusinessLogic;

namespace AtCor.Scor.Presentation
{
    public partial class SimulateMainWindow : Telerik.WinControls.UI.RadForm
    {
        public SimulateMainWindow()
        {
            InitializeComponent();
        }

        private void radRibbonBarGroupCapture_Click(object sender, EventArgs e)
        {
            SimulatePWVCapture frmPWVSimulate = new SimulatePWVCapture();
            frmPWVSimulate.Show();
        }

        private void radRibbonBarGroup1Shot_Click(object sender, EventArgs e)
        {
            BizSession.Instance(); // to instantiate BizSession to setup event delegates
            BizFacade.Instance().SimulateCaptureOneShot();
        }

        private void radRibbonBarGroup1Dispatch_Click(object sender, EventArgs e)
        {
            BizSession.Instance().DispatchCaptureData();
        }
    }
}
