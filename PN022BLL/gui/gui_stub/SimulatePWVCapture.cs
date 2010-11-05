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
    public partial class SimulatePWVCapture : Telerik.WinControls.UI.RadForm
    {
//        BizTonometerDataEvent tonometerData;
        BizCuffPulseEvent cuffPulse;
        BizCountdownTimerEvent countdownTimerData;
        BizCuffStateEvent cuffState;

        public SimulatePWVCapture()
        {
            InitializeComponent();
        }

        private void InitializeTimer()
        {
            //' Run this procedure in an appropriate event.
            // Set interval in milliseconds.
            timer1.Interval = 20;
        }

        private void radLabel2_Click(object sender, EventArgs e)
        {

        }

        private void radButtonPWVCapture_Click(object sender, EventArgs e)
        {
            BizFacade.Instance().SimulateCaptureData();

            // Start the dispatch timer.
            timer1.Enabled = true;

            // Enable the Cancel button.
            radButtonPWVStop.Enabled = true;

            // Disable the Capture button.
            radButtonPWVCapture.Enabled = false;
        }

        private void radButtonPWVStop_Click(object sender, EventArgs e)
        {
            BizFacade.Instance().StopCaptureSimulation();

            // Stop the dispatch timer.
            timer1.Enabled = false;

            // Disable the Cancel button.
            radButtonPWVStop.Enabled = false;

            // Enable the Capture button.
            radButtonPWVCapture.Enabled = true;
        }

        private void timer1_Tick(object sender, EventArgs e)
        {
                    BizSession.Instance().DispatchCaptureData();
        }

        private void SimulatePWVCapture_Load(object sender, EventArgs e)
        {
//            tonometerData = BizFacade.Instance().FindTonometerDataEvent(); // to observe tonometer data from BLL
            cuffPulse = BizFacade.Instance().FindCuffPulseEvent(); // to observe cuff pulse data from BLL
            countdownTimerData = BizFacade.Instance().FindCountdownTimerEvent(); // to observe countdown data from BLL
            cuffState = BizFacade.Instance().FindCuffStateEvent(); // to observe countdown data from BLL

            // Attach the handler to observe tonometer data event from Biz
//            tonometerData.TonometerDataEvent += new BizTonometerDataEvent.BizTonometerDataEventHandler(UpdateTonoData);
            // FxCop suggested to use EventHandler<T> but unit test doesn't like it, not compiling.
            // tonometerData.TonometerDataEvent += new EventHandler<BizTonometerDataEventArgs>(UpdateTonoData);
            BizEventContainer.Instance.OnBizTonometerDataEvent += new BizTonometerDataEventHandler(UpdateTonoData);

            // Attach the handler to observe carotid quality event from Biz
            BizEventContainer.Instance.OnBizCarotidQualityEvent += new BizCarotidQualityEventHandler(UpdateCarotidQuality);
            
            // Attach the handler to observe cuff pulse event from Biz
            cuffPulse.CuffPulseEvent += new BizCuffPulseEvent.BizCuffPulseEventHandler(UpdateCuffPulse);

            // Attach the handler to observe cuff pulse event from Biz
            countdownTimerData.CountdownTimerEvent += new BizCountdownTimerEvent.BizCountdownTimerEventHandler(UpdateCountdown);

            // Attach the handler to observe cuff state event from Biz
            cuffState.CuffStateEvent += new BizCuffStateEvent.BizCuffStateEventHandler(UpdateCuffState);

            radButtonPWVStop.Enabled = false;

            // Initialize the timer to dispatch captured data
            InitializeTimer();
        }
        private void UpdateTonoData(Object sender, BizTonometerDataEventArgs e)
        {
            int data = e.data;
            //            listBoxTonoData.Items.Add(data.ToString());
            radLabelTonoData.Text = data.ToString();
            //chartControl1.
        }

        private void UpdateCarotidQuality(Object sender, BizCarotidQualityEventArgs e)
        {
            radLabelCarotidMinimum.Text = e.signalMinimum.ToString();
            radLabelCarotidMaximum.Text = e.signalMaximum.ToString();
            radLabelCarotidColor.Text = e.signalStrengthColor.ToString();
            radLabelCarotidColor.ForeColor = e.signalStrengthColor;
            radLabelCarotidEnable.Text = e.enableOkayButton.ToString();
        }

        private void UpdateCuffPulse(Object sender, BizCuffPulseEventArgs e)
        {
            int data = e.data;
            //            listBoxCuffPulse.Items.Add(data.ToString());
            radLabelCuffPulse.Text = data.ToString();
        }

        private void UpdateCountdown(Object sender, BizCountdownTimerEventArgs e)
        {
            int data = e.data / 1000;
            radLabelCountdownTimer.Text = data.ToString();
        }

        private void UpdateCuffState(Object sender, BizCuffStateEventArgs e)
        {
            radLabelCuffState.Text = e.data;
        }

    }
}
