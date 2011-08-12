namespace AtCor.Scor.Gui.Presentation
{
    partial class PwvPatientReport
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.crysRptVwrPwvPatientReport = new CrystalDecisions.Windows.Forms.CrystalReportViewer();
            this.CryPwvPatientReport1 = new gui.CryPwvPatientReport();
            this.CryPwvReport1 = new gui.CryPwvReport();
            this.CryPwvAnalysis1 = new gui.CryPwvAnalysis();
            this.SuspendLayout();
            // 
            // crysRptVwrPwvPatientReport
            // 
            this.crysRptVwrPwvPatientReport.ActiveViewIndex = 0;
            this.crysRptVwrPwvPatientReport.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.crysRptVwrPwvPatientReport.DisplayGroupTree = false;
            this.crysRptVwrPwvPatientReport.DisplayStatusBar = false;
            this.crysRptVwrPwvPatientReport.Dock = System.Windows.Forms.DockStyle.Fill;
            this.crysRptVwrPwvPatientReport.Location = new System.Drawing.Point(0, 0);
            this.crysRptVwrPwvPatientReport.Name = "crysRptVwrPwvPatientReport";
            this.crysRptVwrPwvPatientReport.ReportSource = this.CryPwvAnalysis1;
            this.crysRptVwrPwvPatientReport.Size = new System.Drawing.Size(862, 490);
            this.crysRptVwrPwvPatientReport.TabIndex = 0;
            // 
            // PwvPatientReport
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(862, 490);
            this.Controls.Add(this.crysRptVwrPwvPatientReport);
            this.Name = "PwvPatientReport";
            this.Text = "PwvPatientReport";
            this.Load += new System.EventHandler(this.PwvPatientReport_Load);
            this.ResumeLayout(false);

        }

        #endregion

        private CrystalDecisions.Windows.Forms.CrystalReportViewer crysRptVwrPwvPatientReport;
        //private gui.CrystalReport1 CrystalReport11;
        private gui.CryPwvReport CryPwvReport1;
        private gui.CryPwvPatientReport CryPwvPatientReport1;
        private gui.CryPwvAnalysis CryPwvAnalysis1;

    }
}