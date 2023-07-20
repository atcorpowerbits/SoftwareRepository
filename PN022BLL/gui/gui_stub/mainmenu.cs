using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using AtCor.Scor.BusinessLogic;

namespace AtCor
{
    namespace Scor
    {
        namespace Presentation
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
                    bool rc = BizFacade.Instance().StartCapture();

                    if (rc)
                    {
                        form_capture_stub frmCapture = new form_capture_stub();

                        frmCapture.Show();
                    }
                    else
                    {
                        MessageBox.Show("Capture start failed???");
                    }
                }

                private void calculateReportToolStripMenuItem_Click(object sender, EventArgs e)
                {
                    bool rc = BizFacade.Instance().CalculateReport();
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
                    BizFacade.Instance().SimulateCaptureOneShot();
                }

                private void simulateDispatchOneShotToolStripMenuItem_Click(object sender, EventArgs e)
                {
                    BizFacade.Instance().Dispatch();
                }

            }
        }
    }
}
