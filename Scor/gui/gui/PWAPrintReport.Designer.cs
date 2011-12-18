namespace AtCor.Scor.Gui.Presentation
{
    partial class PWAPrintReport
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
            this.crysRptVwrPwaPrintReport = new CrystalDecisions.Windows.Forms.CrystalReportViewer();
            this.CrystalPwaTrendAnalysis1 = new gui.CrystalPwaTrendAnalysis();
            this.CrystalPwaPatientReport1 = new gui.CrystalPwaPatientReport();
            this.CrystalPwaEvalution1 = new gui.CrystalPwaEvalution();
            this.CrystalPwaClinical1 = new gui.CrystalPwaClinical();
            this.CrystalPwaQuickStart1 = new gui.CrystalPwaQuickStart();
            this.SuspendLayout();
            // 
            // crysRptVwrPwaPrintReport
            // 
            this.crysRptVwrPwaPrintReport.ActiveViewIndex = 0;
            this.crysRptVwrPwaPrintReport.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.crysRptVwrPwaPrintReport.DisplayGroupTree = false;
            this.crysRptVwrPwaPrintReport.DisplayStatusBar = false;
            this.crysRptVwrPwaPrintReport.Dock = System.Windows.Forms.DockStyle.Fill;
            this.crysRptVwrPwaPrintReport.Location = new System.Drawing.Point(0, 0);
            this.crysRptVwrPwaPrintReport.Name = "crysRptVwrPwaPrintReport";
            this.crysRptVwrPwaPrintReport.ReportSource = this.CrystalPwaQuickStart1;
            this.crysRptVwrPwaPrintReport.Size = new System.Drawing.Size(862, 490);
            this.crysRptVwrPwaPrintReport.TabIndex = 0;
            // 
            // PWAPrintReport
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(862, 490);
            this.Controls.Add(this.crysRptVwrPwaPrintReport);
            this.Name = "PWAPrintReport";
            this.Text = "PWAPrintReport";
            this.Load += new System.EventHandler(this.PWAPrintReport_Load);
            this.ResumeLayout(false);

        }

        #endregion

        private CrystalDecisions.Windows.Forms.CrystalReportViewer crysRptVwrPwaPrintReport;
        private gui.CrystalPwaClinical CrystalPwaClinical1;
        private gui.CrystalPwaEvalution CrystalPwaEvalution1;
        private gui.CrystalPwaPatientReport CrystalPwaPatientReport1;
        private gui.CrystalPwaTrendAnalysis CrystalPwaTrendAnalysis1;
        private gui.CrystalPwaQuickStart CrystalPwaQuickStart1;
        
    }
}