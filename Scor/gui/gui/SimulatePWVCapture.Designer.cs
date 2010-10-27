namespace AtCor.Scor.Presentation
{
    partial class SimulatePWVCapture
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
            this.components = new System.ComponentModel.Container();
            this.radLabel1 = new Telerik.WinControls.UI.RadLabel();
            this.radLabelTonoData = new Telerik.WinControls.UI.RadLabel();
            this.radLabel2 = new Telerik.WinControls.UI.RadLabel();
            this.radLabelCuffPulse = new Telerik.WinControls.UI.RadLabel();
            this.radLabel3 = new Telerik.WinControls.UI.RadLabel();
            this.radLabelCuffState = new Telerik.WinControls.UI.RadLabel();
            this.radLabel4 = new Telerik.WinControls.UI.RadLabel();
            this.radLabelCountdownTimer = new Telerik.WinControls.UI.RadLabel();
            this.radButtonPWVCapture = new Telerik.WinControls.UI.RadButton();
            this.radButtonPWVStop = new Telerik.WinControls.UI.RadButton();
            this.timer1 = new System.Windows.Forms.Timer(this.components);
            ((System.ComponentModel.ISupportInitialize)(this.radLabel1)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.radLabelTonoData)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.radLabel2)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.radLabelCuffPulse)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.radLabel3)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.radLabelCuffState)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.radLabel4)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.radLabelCountdownTimer)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.radButtonPWVCapture)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.radButtonPWVStop)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this)).BeginInit();
            this.SuspendLayout();
            // 
            // radLabel1
            // 
            this.radLabel1.Location = new System.Drawing.Point(53, 37);
            this.radLabel1.Name = "radLabel1";
            this.radLabel1.Size = new System.Drawing.Size(88, 18);
            this.radLabel1.TabIndex = 0;
            this.radLabel1.Text = "Tonometer Data";
            // 
            // radLabelTonoData
            // 
            this.radLabelTonoData.Location = new System.Drawing.Point(147, 37);
            this.radLabelTonoData.Name = "radLabelTonoData";
            this.radLabelTonoData.Size = new System.Drawing.Size(53, 18);
            this.radLabelTonoData.TabIndex = 1;
            this.radLabelTonoData.Text = "tonoData";
            // 
            // radLabel2
            // 
            this.radLabel2.Location = new System.Drawing.Point(53, 88);
            this.radLabel2.Name = "radLabel2";
            this.radLabel2.Size = new System.Drawing.Size(56, 18);
            this.radLabel2.TabIndex = 2;
            this.radLabel2.Text = "Cuff Pulse";
            // 
            // radLabelCuffPulse
            // 
            this.radLabelCuffPulse.Location = new System.Drawing.Point(147, 88);
            this.radLabelCuffPulse.Name = "radLabelCuffPulse";
            this.radLabelCuffPulse.Size = new System.Drawing.Size(51, 18);
            this.radLabelCuffPulse.TabIndex = 3;
            this.radLabelCuffPulse.Text = "cuffPulse";
            // 
            // radLabel3
            // 
            this.radLabel3.Location = new System.Drawing.Point(53, 154);
            this.radLabel3.Name = "radLabel3";
            this.radLabel3.Size = new System.Drawing.Size(55, 18);
            this.radLabel3.TabIndex = 4;
            this.radLabel3.Text = "Cuff State";
            // 
            // radLabelCuffState
            // 
            this.radLabelCuffState.Location = new System.Drawing.Point(147, 148);
            this.radLabelCuffState.Name = "radLabelCuffState";
            this.radLabelCuffState.Size = new System.Drawing.Size(50, 18);
            this.radLabelCuffState.TabIndex = 5;
            this.radLabelCuffState.Text = "cuffState";
            // 
            // radLabel4
            // 
            this.radLabel4.Location = new System.Drawing.Point(53, 218);
            this.radLabel4.Name = "radLabel4";
            this.radLabel4.Size = new System.Drawing.Size(90, 18);
            this.radLabel4.TabIndex = 6;
            this.radLabel4.Text = "Countdown (sec)";
            // 
            // radLabelCountdownTimer
            // 
            this.radLabelCountdownTimer.Location = new System.Drawing.Point(147, 218);
            this.radLabelCountdownTimer.Name = "radLabelCountdownTimer";
            this.radLabelCountdownTimer.Size = new System.Drawing.Size(28, 18);
            this.radLabelCountdownTimer.TabIndex = 7;
            this.radLabelCountdownTimer.Text = "time";
            // 
            // radButtonPWVCapture
            // 
            this.radButtonPWVCapture.Location = new System.Drawing.Point(274, 302);
            this.radButtonPWVCapture.Name = "radButtonPWVCapture";
            this.radButtonPWVCapture.Size = new System.Drawing.Size(130, 24);
            this.radButtonPWVCapture.TabIndex = 8;
            this.radButtonPWVCapture.Text = "Simulate";
            this.radButtonPWVCapture.Click += new System.EventHandler(this.radButtonPWVCapture_Click);
            // 
            // radButtonPWVStop
            // 
            this.radButtonPWVStop.Location = new System.Drawing.Point(411, 301);
            this.radButtonPWVStop.Name = "radButtonPWVStop";
            this.radButtonPWVStop.Size = new System.Drawing.Size(130, 24);
            this.radButtonPWVStop.TabIndex = 9;
            this.radButtonPWVStop.Text = "Stop";
            this.radButtonPWVStop.Click += new System.EventHandler(this.radButtonPWVStop_Click);
            // 
            // timer1
            // 
            this.timer1.Tick += new System.EventHandler(this.timer1_Tick);
            // 
            // SimulatePWVCapture
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(612, 426);
            this.Controls.Add(this.radButtonPWVStop);
            this.Controls.Add(this.radButtonPWVCapture);
            this.Controls.Add(this.radLabelCountdownTimer);
            this.Controls.Add(this.radLabel4);
            this.Controls.Add(this.radLabelCuffState);
            this.Controls.Add(this.radLabel3);
            this.Controls.Add(this.radLabelCuffPulse);
            this.Controls.Add(this.radLabel2);
            this.Controls.Add(this.radLabelTonoData);
            this.Controls.Add(this.radLabel1);
            this.Name = "SimulatePWVCapture";
            // 
            // 
            // 
            this.RootElement.ApplyShapeToControl = true;
            this.Text = "Simulate PWV Capture";
            this.ThemeName = "ControlDefault";
            this.Load += new System.EventHandler(this.SimulatePWVCapture_Load);
            ((System.ComponentModel.ISupportInitialize)(this.radLabel1)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.radLabelTonoData)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.radLabel2)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.radLabelCuffPulse)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.radLabel3)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.radLabelCuffState)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.radLabel4)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.radLabelCountdownTimer)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.radButtonPWVCapture)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.radButtonPWVStop)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private Telerik.WinControls.UI.RadLabel radLabel1;
        private Telerik.WinControls.UI.RadLabel radLabelTonoData;
        private Telerik.WinControls.UI.RadLabel radLabel2;
        private Telerik.WinControls.UI.RadLabel radLabelCuffPulse;
        private Telerik.WinControls.UI.RadLabel radLabel3;
        private Telerik.WinControls.UI.RadLabel radLabelCuffState;
        private Telerik.WinControls.UI.RadLabel radLabel4;
        private Telerik.WinControls.UI.RadLabel radLabelCountdownTimer;
        private Telerik.WinControls.UI.RadButton radButtonPWVCapture;
        private Telerik.WinControls.UI.RadButton radButtonPWVStop;
        private System.Windows.Forms.Timer timer1;
    }
}

