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
        public SimulatePWVCapture()
        {
            InitializeComponent();
            BizSession.Instance(); // to instantiate BizSession to setup event delegates
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

            // Save the captured data as simulation file
            BizPWV pwvObj = (BizPWV)BizSession.Instance().measurement;
            if (!pwvObj.SaveCaptureData())
            {
                MessageBox.Show("Failed to save captured data as simulation file");
            }
        }

        private void timer1_Tick(object sender, EventArgs e)
        {
                    BizSession.Instance().DispatchCaptureData();
        }

        private void SimulatePWVCapture_Load(object sender, EventArgs e)
        {
            BizEventContainer.Instance.OnBizTonometerDataEvent += new BizTonometerDataEventHandler(UpdateTonoData);
            BizEventContainer.Instance.OnBizCuffPulseEvent += new BizCuffPulseEventHandler(UpdateCuffPulse);
            BizEventContainer.Instance.OnBizCuffStateEvent += new BizCuffStateEventHandler(UpdateCuffState);
            BizEventContainer.Instance.OnBizCountdownTimerEvent += new BizCountdownTimerEventHandler(UpdateCountdown);

            // Attach the handler to observe carotid quality event from Biz
            BizEventContainer.Instance.OnBizCarotidQualityEvent += new BizCarotidQualityEventHandler(UpdateCarotidQuality);

            // Attach the handler to observe femoral quality event from Biz
            BizEventContainer.Instance.OnBizFemoralQualityEvent += new BizFemoralQualityEventHandler(UpdateFemoralQuality);

            // Attach the handler to observe information, warning and error events from Biz
            BizEventContainer.Instance.OnBizInformationEvent += new BizInformationEventHandler(UpdateInformationMessage);
            BizEventContainer.Instance.OnBizWarningEvent += new BizWarningEventHandler(UpdateWarningMessage);
            BizEventContainer.Instance.OnBizErrorEvent += new BizErrorEventHandler(UpdateErrorMessage);

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
            int data = e.data / 1000; // round to sec
            radLabelCountdownTimer.Text = data.ToString();
        }

        private void UpdateCuffState(Object sender, BizCuffStateEventArgs e)
        {
            radLabelCuffState.Text = e.data;
        }

        private void UpdateInformationMessage(Object sender, BizInformationEventArgs e)
        {
            radLabelAlertMessage.Text = e.data;
        }

        private void UpdateWarningMessage(Object sender, BizWarningEventArgs e)
        {
            radLabelAlertMessage.Text = e.data;
        }

        private void UpdateErrorMessage(Object sender, BizErrorEventArgs e)
        {
            radLabelAlertMessage.Text = e.data;
        }

        private void UpdateFemoralQuality(Object sender, BizFemoralQualityEventArgs e)
        {
            radLabelFemoralMinimum.Text = e.signalMinimum.ToString();
            radLabelFemoralMaximum.Text = e.signalMaximum.ToString();
            if (e.signalStrengthIsGood)
            {
                radLabelFemoralQuality.Text = "√";
            }
            else
            {
                radLabelFemoralQuality.Text = "X";
            }
            radLabelFemoralEnable.Text = e.enableOkayButton.ToString();
        }
    }
}
