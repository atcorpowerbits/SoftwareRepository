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
    public partial class MainMenu : Form
    {
        public MainMenu()
        {
            InitializeComponent();
        }

        private void aboutToolStripMenuItem_Click(object sender, EventArgs e)
        {
            AboutBox1 ab1 = new AboutBox1();
            ab1.Show();
        }

        private void startCaptureToolStripMenuItem_Click(object sender, EventArgs e)
        {
            bool rc = Biz.BizFacade.Instance().StartCapture();

            if (rc)
            {
                MessageBox.Show("Capture started successfully!!!");
            }
            else
            {
                MessageBox.Show("Capture start failed???");
            }
        }

        private void stopCaptureToolStripMenuItem_Click(object sender, EventArgs e)
        {
            bool rc = Biz.BizFacade.Instance().StopCapture();
            if (rc)
            {
                MessageBox.Show("Capture stopped successfully!!!");
            }
            else
            {
                MessageBox.Show("Capture stop failed???");
            }
        }

        private void calculateReportToolStripMenuItem_Click(object sender, EventArgs e)
        {
            bool rc = Biz.BizFacade.Instance().CalculateReport();
            if (rc)
            {
                MessageBox.Show("Report calculated successfully!!!");
            }
            else
            {
                MessageBox.Show("Report calculation failed???");
            }
        }

        private void simulateCaptureDataToolStripMenuItem_Click(object sender, EventArgs e)
        {
            Biz.BizFacade.Instance().SimulateCaptureData();
        }
    }
}
