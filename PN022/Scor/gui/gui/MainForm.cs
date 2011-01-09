using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using Telerik.WinControls;

/**
 * @namespace AtCor.Scor.Gui
 * @brief This namespace is used to encapsulate GUI related functionality.
 * 
 */
namespace AtCor.Scor.Gui
{
    namespace AtCor.Scor.Gui.Presentation
    {
        public partial class MainForm : Telerik.WinControls.UI.RadForm
        {
            public MainForm()
            {
                InitializeComponent();
            }

            private void radPageViewPage1_Paint(object sender, PaintEventArgs e)
            {

            }

            private void MainForm_Load(object sender, EventArgs e)
            {
                //AxAcroPDFLib.AxAcroPDF pdf = new AxAcroPDFLib.AxAcroPDF();
                //pdf.Dock = System.Windows.Forms.DockStyle.None;
                //pdf.Enabled = true;
                //pdf.Location = new System.Drawing.Point(0, 0);
                //pdf.Size = new Size(1020,740);
                //pdf.Name = "pdfReader";
                //pdf.OcxState = ((System.Windows.Forms.AxHost.State)(new System.ComponentModel.ComponentResourceManager(typeof(GUI_POC)).GetObject("pdfReader.OcxState")));
                //// pdf.TabIndex = 1;  // Add pdf viewer to current form         
                //this.Controls.Add(pdf);
                //pdf.BringToFront();
                //pdf.LoadFile(@"d:\GUI_drop1_rev9.0.pdf");
                //pdf.setView("Fit");
                //pdf.Show();
            }
        }
    }
}