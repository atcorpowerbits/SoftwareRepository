namespace AtCor.Scor.Presentation
{
    partial class SimulateMainWindow
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
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(SimulateMainWindow));
            this.radRibbonBarSimulation = new Telerik.WinControls.UI.RadRibbonBar();
            this.radRibbonFormBehavior1 = new Telerik.WinControls.UI.RadRibbonFormBehavior();
            this.ribbonTabPWV = new Telerik.WinControls.UI.RibbonTab();
            this.radRibbonBarGroupCapture = new Telerik.WinControls.UI.RadRibbonBarGroup();
            this.radRibbonBarGroup1Shot = new Telerik.WinControls.UI.RadRibbonBarGroup();
            this.radRibbonBarGroup1Dispatch = new Telerik.WinControls.UI.RadRibbonBarGroup();
            this.ribbonTab1 = new Telerik.WinControls.UI.RibbonTab();
            this.radRibbonBarGroup1 = new Telerik.WinControls.UI.RadRibbonBarGroup();
            ((System.ComponentModel.ISupportInitialize)(this.radRibbonBarSimulation)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this)).BeginInit();
            this.SuspendLayout();
            // 
            // radRibbonBarSimulation
            // 
            this.radRibbonBarSimulation.AutoSize = true;
            this.radRibbonBarSimulation.CommandTabs.AddRange(new Telerik.WinControls.RadItem[] {
            this.ribbonTabPWV,
            this.ribbonTab1});
            this.radRibbonBarSimulation.Dock = System.Windows.Forms.DockStyle.Top;
            this.radRibbonBarSimulation.EnableKeyMap = true;
            // 
            // 
            // 
            this.radRibbonBarSimulation.ExitButton.Text = "Exit";
            this.radRibbonBarSimulation.Location = new System.Drawing.Point(0, 0);
            this.radRibbonBarSimulation.Name = "radRibbonBarSimulation";
            // 
            // 
            // 
            this.radRibbonBarSimulation.OptionsButton.Text = "Options";
            this.radRibbonBarSimulation.Size = new System.Drawing.Size(598, 150);
            this.radRibbonBarSimulation.StartButtonImage = ((System.Drawing.Image)(resources.GetObject("radRibbonBarSimulation.StartButtonImage")));
            this.radRibbonBarSimulation.TabIndex = 0;
            this.radRibbonBarSimulation.Text = "Simulation";
            // 
            // radRibbonFormBehavior1
            // 
            this.radRibbonFormBehavior1.Form = this;
            // 
            // ribbonTabPWV
            // 
            this.ribbonTabPWV.Alignment = System.Drawing.ContentAlignment.BottomLeft;
            // 
            // ribbonTabPWV.ContentPanel
            // 
            this.ribbonTab1.ContentPanel.BackColor = System.Drawing.SystemColors.ControlLightLight;
            this.ribbonTab1.ContentPanel.CausesValidation = true;
            this.ribbonTab1.ContentPanel.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.ribbonTab1.ContentPanel.ForeColor = System.Drawing.SystemColors.ControlText;
            this.ribbonTab1.ContentPanel.Location = new System.Drawing.Point(0, 0);
            this.ribbonTab1.ContentPanel.Size = new System.Drawing.Size(200, 100);
            this.ribbonTabPWV.IsSelected = true;
            this.ribbonTabPWV.Items.AddRange(new Telerik.WinControls.RadItem[] {
            this.radRibbonBarGroupCapture,
            this.radRibbonBarGroup1Shot,
            this.radRibbonBarGroup1Dispatch});
            this.ribbonTabPWV.Name = "ribbonTabPWV";
            this.ribbonTabPWV.StretchHorizontally = false;
            this.ribbonTabPWV.Text = "PWV";
            // 
            // radRibbonBarGroupCapture
            // 
            this.radRibbonBarGroupCapture.Name = "radRibbonBarGroupCapture";
            this.radRibbonBarGroupCapture.Text = "Capture";
            this.radRibbonBarGroupCapture.Click += new System.EventHandler(this.radRibbonBarGroupCapture_Click);
            // 
            // radRibbonBarGroup1Shot
            // 
            this.radRibbonBarGroup1Shot.Name = "radRibbonBarGroup1Shot";
            this.radRibbonBarGroup1Shot.Text = "One Shot";
            this.radRibbonBarGroup1Shot.Click += new System.EventHandler(this.radRibbonBarGroup1Shot_Click);
            // 
            // radRibbonBarGroup1Dispatch
            // 
            this.radRibbonBarGroup1Dispatch.Name = "radRibbonBarGroup1Dispatch";
            this.radRibbonBarGroup1Dispatch.Text = "Single Dispatch";
            this.radRibbonBarGroup1Dispatch.Click += new System.EventHandler(this.radRibbonBarGroup1Dispatch_Click);
            // 
            // ribbonTab1
            // 
            this.ribbonTab1.Alignment = System.Drawing.ContentAlignment.BottomLeft;
            // 
            // ribbonTab1.ContentPanel
            // 
            this.ribbonTab1.ContentPanel.BackColor = System.Drawing.SystemColors.ControlLightLight;
            this.ribbonTab1.ContentPanel.CausesValidation = true;
            this.ribbonTab1.ContentPanel.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.ribbonTab1.ContentPanel.ForeColor = System.Drawing.SystemColors.ControlText;
            this.ribbonTab1.ContentPanel.Location = new System.Drawing.Point(0, 0);
            this.ribbonTab1.ContentPanel.Size = new System.Drawing.Size(200, 100);
            this.ribbonTab1.Items.AddRange(new Telerik.WinControls.RadItem[] {
            this.radRibbonBarGroup1});
            this.ribbonTab1.Name = "ribbonTab1";
            this.ribbonTab1.StretchHorizontally = false;
            this.ribbonTab1.Text = "Help";
            // 
            // radRibbonBarGroup1
            // 
            this.radRibbonBarGroup1.Name = "radRibbonBarGroup1";
            this.radRibbonBarGroup1.Text = "About (TBD)";
            // 
            // SimulateMainWindow
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(598, 286);
            this.Controls.Add(this.radRibbonBarSimulation);
            this.FormBehavior = this.radRibbonFormBehavior1;
            this.Name = "SimulateMainWindow";
            // 
            // 
            // 
            this.RootElement.ApplyShapeToControl = true;
            this.Text = "Simulation";
            this.ThemeName = "ControlDefault";
            ((System.ComponentModel.ISupportInitialize)(this.radRibbonBarSimulation)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private Telerik.WinControls.UI.RadRibbonBar radRibbonBarSimulation;
        private Telerik.WinControls.UI.RadRibbonFormBehavior radRibbonFormBehavior1;
        private Telerik.WinControls.UI.RibbonTab ribbonTabPWV;
        private Telerik.WinControls.UI.RadRibbonBarGroup radRibbonBarGroupCapture;
        private Telerik.WinControls.UI.RadRibbonBarGroup radRibbonBarGroup1Shot;
        private Telerik.WinControls.UI.RadRibbonBarGroup radRibbonBarGroup1Dispatch;
        private Telerik.WinControls.UI.RibbonTab ribbonTab1;
        private Telerik.WinControls.UI.RadRibbonBarGroup radRibbonBarGroup1;
    }
}

