namespace gui
{
    partial class MainMenu
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
            this.menuStrip1 = new System.Windows.Forms.MenuStrip();
            this.pwvCommandToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.startCaptureToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.stopCaptureToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.simulateCaptureDataToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.calculateReportToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.helpToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.aboutToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.menuStrip1.SuspendLayout();
            this.SuspendLayout();
            // 
            // menuStrip1
            // 
            this.menuStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.pwvCommandToolStripMenuItem,
            this.helpToolStripMenuItem});
            this.menuStrip1.Location = new System.Drawing.Point(0, 0);
            this.menuStrip1.Name = "menuStrip1";
            this.menuStrip1.Size = new System.Drawing.Size(284, 24);
            this.menuStrip1.TabIndex = 0;
            this.menuStrip1.Text = "menuStrip1";
            // 
            // pwvCommandToolStripMenuItem
            // 
            this.pwvCommandToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.startCaptureToolStripMenuItem,
            this.stopCaptureToolStripMenuItem,
            this.simulateCaptureDataToolStripMenuItem,
            this.calculateReportToolStripMenuItem});
            this.pwvCommandToolStripMenuItem.Name = "pwvCommandToolStripMenuItem";
            this.pwvCommandToolStripMenuItem.Size = new System.Drawing.Size(44, 20);
            this.pwvCommandToolStripMenuItem.Text = "PWV";
            // 
            // startCaptureToolStripMenuItem
            // 
            this.startCaptureToolStripMenuItem.Name = "startCaptureToolStripMenuItem";
            this.startCaptureToolStripMenuItem.Size = new System.Drawing.Size(217, 22);
            this.startCaptureToolStripMenuItem.Text = "Start Capture";
            this.startCaptureToolStripMenuItem.Click += new System.EventHandler(this.startCaptureToolStripMenuItem_Click);
            // 
            // stopCaptureToolStripMenuItem
            // 
            this.stopCaptureToolStripMenuItem.Name = "stopCaptureToolStripMenuItem";
            this.stopCaptureToolStripMenuItem.Size = new System.Drawing.Size(217, 22);
            this.stopCaptureToolStripMenuItem.Text = "Stop Capture";
            this.stopCaptureToolStripMenuItem.Click += new System.EventHandler(this.stopCaptureToolStripMenuItem_Click);
            // 
            // simulateCaptureDataToolStripMenuItem
            // 
            this.simulateCaptureDataToolStripMenuItem.Name = "simulateCaptureDataToolStripMenuItem";
            this.simulateCaptureDataToolStripMenuItem.Size = new System.Drawing.Size(217, 22);
            this.simulateCaptureDataToolStripMenuItem.Text = "Simulate Capture One Shot";
            this.simulateCaptureDataToolStripMenuItem.Click += new System.EventHandler(this.simulateCaptureDataToolStripMenuItem_Click);
            // 
            // calculateReportToolStripMenuItem
            // 
            this.calculateReportToolStripMenuItem.Name = "calculateReportToolStripMenuItem";
            this.calculateReportToolStripMenuItem.Size = new System.Drawing.Size(217, 22);
            this.calculateReportToolStripMenuItem.Text = "Calculate Report";
            this.calculateReportToolStripMenuItem.Click += new System.EventHandler(this.calculateReportToolStripMenuItem_Click);
            // 
            // helpToolStripMenuItem
            // 
            this.helpToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.aboutToolStripMenuItem});
            this.helpToolStripMenuItem.Name = "helpToolStripMenuItem";
            this.helpToolStripMenuItem.Size = new System.Drawing.Size(44, 20);
            this.helpToolStripMenuItem.Text = "Help";
            // 
            // aboutToolStripMenuItem
            // 
            this.aboutToolStripMenuItem.Name = "aboutToolStripMenuItem";
            this.aboutToolStripMenuItem.Size = new System.Drawing.Size(107, 22);
            this.aboutToolStripMenuItem.Text = "About";
            this.aboutToolStripMenuItem.Click += new System.EventHandler(this.aboutToolStripMenuItem_Click);
            // 
            // MainMenu
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(284, 262);
            this.Controls.Add(this.menuStrip1);
            this.MainMenuStrip = this.menuStrip1;
            this.Name = "MainMenu";
            this.Text = "MainMenu";
            this.menuStrip1.ResumeLayout(false);
            this.menuStrip1.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.MenuStrip menuStrip1;
        private System.Windows.Forms.ToolStripMenuItem helpToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem aboutToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem pwvCommandToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem startCaptureToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem stopCaptureToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem calculateReportToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem simulateCaptureDataToolStripMenuItem;
    }
}

