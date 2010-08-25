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
        Biz.BizTonoDataEvent tonoData;
        Biz.BizCuffPulseEvent cuffPulse;

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
            tonoData = Biz.BizFacade.Instance().FindTonoData(); // to observe Tonometer data from BLL
            cuffPulse = Biz.BizFacade.Instance().FindCuffPulse(); // to observe cuff pulse data from BLL

            // Attach the handler to observe tonometer data event from Biz
	    	tonoData.TonoDataEvent += new BizTonoDataEvent.BizTonoDataEventHandler( UpdateTonoData );

            // Attach the handler to observe cuff pulse event from Biz
            cuffPulse.CuffPulseEvent += new BizCuffPulseEvent.BizCuffPulseEventHandler(UpdateCuffPulse);

            buttonCancel.Enabled = false;

            // Initialize the timer to dispatch captured data
            InitializeTimer();

            // Start the dispatch timer.
            timer1.Enabled = true;
        }

        private void UpdateTonoData( Object sender, BizTonoDataArgs e )
        {
            int data = e.data;
            listBoxTonoData.Items.Add(data.ToString());
        }

        private void UpdateCuffPulse(Object sender, BizCuffPulseArgs e)
        {
            int data = e.data;
            listBoxCuffPulse.Items.Add(data.ToString());
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
            Biz.BizFacade.Instance().DispatchCaptureData();
        }

        private void buttonCapture_Click(object sender, EventArgs e)
        {
            listBoxTonoData.Items.Clear();
            listBoxCuffPulse.Items.Clear();

            Biz.BizFacade.Instance().SimulateCaptureData();

            // Enable the Cancel button.
            buttonCancel.Enabled = true;
        }

        private void buttonCancel_Click(object sender, EventArgs e)
        {
            // Cancel the asynchronous operation.
            this.backgroundWorker1.CancelAsync();

            Biz.BizFacade.Instance().StopSimulation();
            
            // Disable the Cancel button.
            buttonCancel.Enabled = false;
        }

        private void timer1_Tick(object sender, EventArgs e)
        {
            Biz.BizFacade.Instance().DispatchCaptureData();
        }
    }
}
