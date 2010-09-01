namespace gui
{
    partial class form_capture_stub
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
            this.listBoxTonoData = new System.Windows.Forms.ListBox();
            this.backgroundWorker1 = new System.ComponentModel.BackgroundWorker();
            this.buttonCapture = new System.Windows.Forms.Button();
            this.buttonCancel = new System.Windows.Forms.Button();
            this.timer1 = new System.Windows.Forms.Timer(this.components);
            this.listBoxCuffPulse = new System.Windows.Forms.ListBox();
            this.label1 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.buttonCountDown = new System.Windows.Forms.Button();
            this.buttonStopCountDown = new System.Windows.Forms.Button();
            this.progressBarTimeCountDown = new System.Windows.Forms.ProgressBar();
            this.labelTimeTo = new System.Windows.Forms.Label();
            this.labelTimeCountDown = new System.Windows.Forms.Label();
            this.SuspendLayout();
            // 
            // listBoxTonoData
            // 
            this.listBoxTonoData.FormattingEnabled = true;
            this.listBoxTonoData.Location = new System.Drawing.Point(44, 35);
            this.listBoxTonoData.Name = "listBoxTonoData";
            this.listBoxTonoData.Size = new System.Drawing.Size(88, 199);
            this.listBoxTonoData.TabIndex = 0;
            // 
            // backgroundWorker1
            // 
            this.backgroundWorker1.WorkerReportsProgress = true;
            this.backgroundWorker1.WorkerSupportsCancellation = true;
            this.backgroundWorker1.DoWork += new System.ComponentModel.DoWorkEventHandler(this.backgroundWorker1_DoWork);
            // 
            // buttonCapture
            // 
            this.buttonCapture.Location = new System.Drawing.Point(43, 260);
            this.buttonCapture.Name = "buttonCapture";
            this.buttonCapture.Size = new System.Drawing.Size(97, 23);
            this.buttonCapture.TabIndex = 1;
            this.buttonCapture.Text = "Simulate Capture";
            this.buttonCapture.UseVisualStyleBackColor = true;
            this.buttonCapture.Click += new System.EventHandler(this.buttonCapture_Click);
            // 
            // buttonCancel
            // 
            this.buttonCancel.Location = new System.Drawing.Point(146, 260);
            this.buttonCancel.Name = "buttonCancel";
            this.buttonCancel.Size = new System.Drawing.Size(75, 23);
            this.buttonCancel.TabIndex = 2;
            this.buttonCancel.Text = "Stop";
            this.buttonCancel.UseVisualStyleBackColor = true;
            this.buttonCancel.Click += new System.EventHandler(this.buttonCancel_Click);
            // 
            // timer1
            // 
            this.timer1.Tick += new System.EventHandler(this.timer1_Tick);
            // 
            // listBoxCuffPulse
            // 
            this.listBoxCuffPulse.FormattingEnabled = true;
            this.listBoxCuffPulse.Location = new System.Drawing.Point(180, 35);
            this.listBoxCuffPulse.Name = "listBoxCuffPulse";
            this.listBoxCuffPulse.Size = new System.Drawing.Size(88, 199);
            this.listBoxCuffPulse.TabIndex = 3;
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(44, 13);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(84, 13);
            this.label1.TabIndex = 4;
            this.label1.Text = "Tonometer Data";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(180, 13);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(55, 13);
            this.label2.TabIndex = 5;
            this.label2.Text = "Cuff Pulse";
            // 
            // buttonCountDown
            // 
            this.buttonCountDown.Location = new System.Drawing.Point(321, 259);
            this.buttonCountDown.Name = "buttonCountDown";
            this.buttonCountDown.Size = new System.Drawing.Size(113, 23);
            this.buttonCountDown.TabIndex = 6;
            this.buttonCountDown.Text = "Simulate Countdown";
            this.buttonCountDown.UseVisualStyleBackColor = true;
            this.buttonCountDown.Click += new System.EventHandler(this.buttonCountDown_Click);
            // 
            // buttonStopCountDown
            // 
            this.buttonStopCountDown.Location = new System.Drawing.Point(440, 259);
            this.buttonStopCountDown.Name = "buttonStopCountDown";
            this.buttonStopCountDown.Size = new System.Drawing.Size(75, 23);
            this.buttonStopCountDown.TabIndex = 7;
            this.buttonStopCountDown.Text = "Stop";
            this.buttonStopCountDown.UseVisualStyleBackColor = true;
            this.buttonStopCountDown.Click += new System.EventHandler(this.buttonStopCountDown_Click);
            // 
            // progressBarTimeCountDown
            // 
            this.progressBarTimeCountDown.Location = new System.Drawing.Point(321, 210);
            this.progressBarTimeCountDown.Name = "progressBarTimeCountDown";
            this.progressBarTimeCountDown.Size = new System.Drawing.Size(194, 23);
            this.progressBarTimeCountDown.TabIndex = 8;
            // 
            // labelTimeTo
            // 
            this.labelTimeTo.AutoSize = true;
            this.labelTimeTo.Location = new System.Drawing.Point(321, 191);
            this.labelTimeTo.Name = "labelTimeTo";
            this.labelTimeTo.Size = new System.Drawing.Size(74, 13);
            this.labelTimeTo.TabIndex = 9;
            this.labelTimeTo.Text = "Time To xxxxx";
            // 
            // labelTimeCountDown
            // 
            this.labelTimeCountDown.AutoSize = true;
            this.labelTimeCountDown.Location = new System.Drawing.Point(402, 190);
            this.labelTimeCountDown.Name = "labelTimeCountDown";
            this.labelTimeCountDown.Size = new System.Drawing.Size(86, 13);
            this.labelTimeCountDown.TabIndex = 10;
            this.labelTimeCountDown.Text = "Count down time";
            // 
            // form_capture_stub
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(550, 428);
            this.Controls.Add(this.labelTimeCountDown);
            this.Controls.Add(this.labelTimeTo);
            this.Controls.Add(this.progressBarTimeCountDown);
            this.Controls.Add(this.buttonStopCountDown);
            this.Controls.Add(this.buttonCountDown);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.listBoxCuffPulse);
            this.Controls.Add(this.buttonCancel);
            this.Controls.Add(this.buttonCapture);
            this.Controls.Add(this.listBoxTonoData);
            this.Name = "form_capture_stub";
            this.Text = "form_capture_stub";
            this.Load += new System.EventHandler(this.form_capture_stub_Load);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.ListBox listBoxTonoData;
        private System.ComponentModel.BackgroundWorker backgroundWorker1;
        private System.Windows.Forms.Button buttonCapture;
        private System.Windows.Forms.Button buttonCancel;
        private System.Windows.Forms.Timer timer1;
        private System.Windows.Forms.ListBox listBoxCuffPulse;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Button buttonCountDown;
        private System.Windows.Forms.Button buttonStopCountDown;
        private System.Windows.Forms.ProgressBar progressBarTimeCountDown;
        private System.Windows.Forms.Label labelTimeTo;
        private System.Windows.Forms.Label labelTimeCountDown;
    }
}