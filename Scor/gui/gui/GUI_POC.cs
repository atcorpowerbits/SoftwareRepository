using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using Telerik.WinControls;
using Telerik.WinControls.UI;
using Telerik.WinControls.Primitives;
using Telerik.WinControls.Enumerations;
using Telerik.WinControls.UI.Docking;


namespace AtCor.Scor.Gui.Presentation
{
    public partial class GUI_POC : Telerik.WinControls.UI.RadForm
    {
        private string message = string.Empty;
        public GUI_POC()
        {
            InitializeComponent();
            //POC
            WindowState = FormWindowState.Maximized;

            radPageView1.SelectedPage = Capture;
           // this.Controls.Add(radPageView1 = new RadPageView());
          //  radPageView1.Size = new Size(this.ClientSize.Width, this.ClientSize.Height - 24);
           // radPageView1.Anchor = AnchorStyles.Bottom | AnchorStyles.Top | AnchorStyles.Left | AnchorStyles.Right;

            //var addFormButton = new RadButton();
            //addFormButton.Text = "Add Form";
            //addFormButton.Click += new EventHandler(radPageView1_Click);
            //addFormButton.Dock = DockStyle.Bottom;
            //this.Controls.Add(addFormButton);
        }

        private void Capture_Click(object sender, EventArgs e)
        {
            //==================added POC
            //var childForm = new frmSettingsWindow();
            //childForm.TopLevel = false;
            //childForm.Dock = DockStyle.Fill;
            //childForm.FormBorderStyle = System.Windows.Forms.FormBorderStyle.None;

            //var page = new RadPageViewPage();
            //childForm.Parent = page;
            //page.Text = "Page " + (radPageView1.Pages.Count + 1).ToString();
            //page.Controls.Add(childForm);

            //radPageView1.Pages.Add(page);
            //childForm.Show();


            //===========================================
        }

        private void radPageView1_Click(object sender, EventArgs e)
        {
            if (radPageView1.SelectedPage.Text.Equals("Capture"))
            {

                var childForm = new frmSettingsWindow(this);
                childForm.TopLevel = false;
                childForm.Dock = DockStyle.Fill;
                childForm.FormBorderStyle = System.Windows.Forms.FormBorderStyle.None;

                var page = radPageView1.Pages[1];
                childForm.Parent = page;
                //page.Text = "Page " + (radPageView1.Pages.Count + 1).ToString();
                page.Controls.Add(childForm);

                //radPageView1.Pages.Add(page);
                childForm.Show();
            }
            else
            {
                InitializeComponent1();
            }
           
            
        }

        public string Message
        {
            get
            { 
                return message;
            }

            set
            {
                message = value;
            }

        }
        public void UpdateMessage()
        {
            radLabel2.Text = Message;
        }

       

        private void radMenuItem2_Click(object sender, MouseEventArgs e)
        {
            System.Diagnostics.Process.Start(@"D:\Vibhuti\Scor\gui\gui\bin\Debug\system\Manuals\CurrentCulture\English\OperatorsManual.pdf");            
        }

        private void radMenuItem3_Click(object sender, EventArgs e)
        {
            System.Diagnostics.Process.Start(@"D:\Vibhuti\Scor\gui\gui\bin\Debug\system\Manuals\CurrentCulture\English\ServiceManual.pdf");            
        }


        
        

    }
}
