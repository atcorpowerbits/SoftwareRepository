using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using Biz;

namespace gui
{
    public partial class form_capture_stub : Form
    {
        Biz.BizTonometerDataEvent tonometerData;
        Biz.BizCuffPulseEvent cuffPulse;
        Biz.BizCountdownTimerEvent countdownTimerData;
        Biz.BizCuffStateEvent cuffState;

        public form_capture_stub()
        {
            InitializeComponent();
            InitializeBackgoundWorker();
        }

        private void InitializeTimer()
        {
            //' Run this procedure in an appropriate event.
            // Set interval in milliseconds.
            timer1.Interval = 20;
        }

        // Set up the BackgroundWorker object by 
        // attaching event handlers. 
        private void InitializeBackgoundWorker()
        {
            backgroundWorker1.DoWork +=
                new DoWorkEventHandler(backgroundWorker1_DoWork);
            backgroundWorker1.RunWorkerCompleted +=
                new RunWorkerCompletedEventHandler(
                    backgroundWorker1_RunWorkerCompleted);
            backgroundWorker1.ProgressChanged +=
                new ProgressChangedEventHandler(
                    backgroundWorker1_ProgressChanged);
        }

        private void form_capture_stub_Load(object sender, EventArgs e)
        {
            tonometerData = Biz.BizFacade.Instance().FindTonometerDataEvent(); // to observe tonometer data from BLL
            cuffPulse = Biz.BizFacade.Instance().FindCuffPulseEvent(); // to observe cuff pulse data from BLL
            countdownTimerData = Biz.BizFacade.Instance().FindCountdownTimerEvent(); // to observe countdown data from BLL
            cuffState = Biz.BizFacade.Instance().FindCuffStateEvent(); // to observe countdown data from BLL

            // Attach the handler to observe tonometer data event from Biz
	    	tonometerData.TonometerDataEvent += new BizTonometerDataEvent.BizTonometerDataEventHandler( UpdateTonoData );
            // FxCop suggested to use EventHandler<T> but unit test doesn't like it, not compiling.
            // tonometerData.TonometerDataEvent += new EventHandler<BizTonometerDataEventArgs>(UpdateTonoData);

            // Attach the handler to observe cuff pulse event from Biz
            cuffPulse.CuffPulseEvent += new BizCuffPulseEvent.BizCuffPulseEventHandler(UpdateCuffPulse);

            // Attach the handler to observe cuff pulse event from Biz
            countdownTimerData.CountdownTimerEvent += new BizCountdownTimerEvent.BizCountdownTimerEventHandler(UpdateCountdown);

            // Attach the handler to observe cuff state event from Biz
            cuffState.CuffStateEvent += new BizCuffStateEvent.BizCuffStateEventHandler(UpdateCuffState);

            buttonCancel.Enabled = false;

            // Initialize the timer to dispatch captured data
            InitializeTimer();
        }

        private void UpdateTonoData( Object sender, BizTonometerDataEventArgs e )
        {
            int data = e.data;
//            listBoxTonoData.Items.Add(data.ToString());
            labelTonoData.Text = data.ToString();
        }

        private void UpdateCuffPulse(Object sender, BizCuffPulseEventArgs e)
        {
            int data = e.data;
//            listBoxCuffPulse.Items.Add(data.ToString());
            labelCuffPulse.Text = data.ToString();
        }

        private void UpdateCountdown(Object sender, BizCountdownTimerEventArgs e)
        {
            int data = e.data / 1000;
            labelCountdownTimer.Text = data.ToString();
        }

        private void UpdateCuffState(Object sender, BizCuffStateEventArgs e)
        {
            labelCuffState.Text = e.data;
        }

        private void backgroundWorker1_DoWork(object sender, DoWorkEventArgs e)
        {
            BackgroundWorker worker = sender as BackgroundWorker;
/*
            while (!worker.CancellationPending)
            {
                worker.ReportProgress(50);
            }
*/
        }

        private void backgroundWorker1_RunWorkerCompleted(object sender, RunWorkerCompletedEventArgs e)
        {
            MessageBox.Show("background worker completed", "caption", MessageBoxButtons.OK);
        }

        private void backgroundWorker1_ProgressChanged(object sender, ProgressChangedEventArgs e)
        {
            Biz.BizFacade.Instance().Dispatch();
        }

        private void buttonCapture_Click(object sender, EventArgs e)
        {
//            listBoxTonoData.Items.Clear();
//            listBoxCuffPulse.Items.Clear();

            Biz.BizFacade.Instance().SimulateCaptureData();

            // Start the dispatch timer.
            timer1.Enabled = true;

            // Enable the Cancel button.
            buttonCancel.Enabled = true;
            // Disable the Capture button.
            buttonCapture.Enabled = false;
        }

        private void buttonCancel_Click(object sender, EventArgs e)
        {
            // Cancel the asynchronous operation.
            this.backgroundWorker1.CancelAsync();

            Biz.BizFacade.Instance().StopCaptureSimulation();

            // Stop the dispatch timer.
            timer1.Enabled = false;

            // Disable the Cancel button.
            buttonCancel.Enabled = false;
            // Enable the Capture button.
            buttonCapture.Enabled = true;
        }

        private void timer1_Tick(object sender, EventArgs e)
        {
            Biz.BizFacade.Instance().Dispatch();
        }

//        private void buttonCountDown_Click(object sender, EventArgs e)
//        {
//            Biz.BizFacade.Instance().SimulateDeflationTimer();
//          // Disable the Stop button.
//            buttonStopCountDown.Enabled = true;
//            // Enable the Countdown button.
//            buttonCountDown.Enabled = false;
//        }

//        private void buttonStopCountDown_Click(object sender, EventArgs e)
//        {
//            Biz.BizFacade.Instance().StopDeflationTimerSimulation();
//            // Disable the Stop button.
//            buttonStopCountDown.Enabled = false;
//            // Enable the Countdown button.
//            buttonCountDown.Enabled = true;
//        }
    }
}
