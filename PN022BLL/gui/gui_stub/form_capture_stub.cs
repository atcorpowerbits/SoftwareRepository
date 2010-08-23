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

        public form_capture_stub()
        {
            InitializeComponent();
            InitializeBackgoundWorker();

            tonoData = Biz.BizFacade.Instance().FindTonoData(); // to observe Tonometer data from BLL
        }

        private void InitializeTimer()
        {
            //' Run this procedure in an appropriate event.
            // Set to 1 second.
            timer1.Interval = 20;
            // Enable timer.
            timer1.Enabled = true;
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
    		// Attach as an observer to Tonometer data event update
	    	tonoData.TonoDataEvent += new BizTonoDataEvent.BizTonoDataEventHandler( Update );
            buttonCancel.Enabled = false;
        }

        private void Update( Object sender, BizTonoDataArgs e )
        {
            int data = e.data;
            listBoxTonoData.Items.Add(data.ToString());
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
            Biz.BizFacade.Instance().DisplayCaptureData();
//?            MessageBox.Show("background worker progess", "caption", MessageBoxButtons.OK);
        }

        private void buttonCapture_Click(object sender, EventArgs e)
        {
            Biz.BizFacade.Instance().SimulateCaptureData();

/*
            // Start the asynchronous operation.
            backgroundWorker1.RunWorkerAsync();
*/

            listBoxTonoData.Items.Clear();

            InitializeTimer();

            // Enable the Cancel button.
            buttonCancel.Enabled = true;
        }

        private void buttonCancel_Click(object sender, EventArgs e)
        {
            // Cancel the asynchronous operation.
            this.backgroundWorker1.CancelAsync();

            Biz.BizFacade.Instance().StopCapture();
            
            // Disable the Cancel button.
            buttonCancel.Enabled = false;

            // Disable timer.
            timer1.Enabled = false;

        }

        private void timer1_Tick(object sender, EventArgs e)
        {
            Biz.BizFacade.Instance().DisplayCaptureData();
        }
    }
}
