namespace AtCor
{
namespace Scor
{
namespace Presentation
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
            this.backgroundWorker1 = new System.ComponentModel.BackgroundWorker();
            this.buttonCapture = new System.Windows.Forms.Button();
            this.buttonCancel = new System.Windows.Forms.Button();
            this.timer1 = new System.Windows.Forms.Timer(this.components);
            this.label1 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.progressBarTimeCountDown = new System.Windows.Forms.ProgressBar();
            this.labelCuffState = new System.Windows.Forms.Label();
            this.labelCountdownTimer = new System.Windows.Forms.Label();
            this.labelTonoData = new System.Windows.Forms.Label();
            this.labelCuffPulse = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.label4 = new System.Windows.Forms.Label();
            this.label5 = new System.Windows.Forms.Label();
            this.SuspendLayout();
            // 
            // backgroundWorker1
            // 
            this.backgroundWorker1.WorkerReportsProgress = true;
            this.backgroundWorker1.WorkerSupportsCancellation = true;
            this.backgroundWorker1.DoWork += new System.ComponentModel.DoWorkEventHandler(this.backgroundWorker1_DoWork);
            // 
            // buttonCapture
            // 
            this.buttonCapture.Location = new System.Drawing.Point(252, 206);
            this.buttonCapture.Name = "buttonCapture";
            this.buttonCapture.Size = new System.Drawing.Size(97, 23);
            this.buttonCapture.TabIndex = 1;
            this.buttonCapture.Text = "Simulate Capture";
            this.buttonCapture.UseVisualStyleBackColor = true;
            this.buttonCapture.Click += new System.EventHandler(this.buttonCapture_Click);
            // 
            // buttonCancel
            // 
            this.buttonCancel.Location = new System.Drawing.Point(355, 206);
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
            this.label2.Location = new System.Drawing.Point(44, 45);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(55, 13);
            this.label2.TabIndex = 5;
            this.label2.Text = "Cuff Pulse";
            // 
            // progressBarTimeCountDown
            // 
            this.progressBarTimeCountDown.Location = new System.Drawing.Point(47, 136);
            this.progressBarTimeCountDown.Name = "progressBarTimeCountDown";
            this.progressBarTimeCountDown.Size = new System.Drawing.Size(194, 23);
            this.progressBarTimeCountDown.TabIndex = 8;
            // 
            // labelCuffState
            // 
            this.labelCuffState.AutoSize = true;
            this.labelCuffState.Location = new System.Drawing.Point(150, 77);
            this.labelCuffState.Name = "labelCuffState";
            this.labelCuffState.Size = new System.Drawing.Size(63, 13);
            this.labelCuffState.TabIndex = 9;
            this.labelCuffState.Text = "<cuff state>";
            // 
            // labelCountdownTimer
            // 
            this.labelCountdownTimer.AutoSize = true;
            this.labelCountdownTimer.Location = new System.Drawing.Point(150, 109);
            this.labelCountdownTimer.Name = "labelCountdownTimer";
            this.labelCountdownTimer.Size = new System.Drawing.Size(26, 13);
            this.labelCountdownTimer.TabIndex = 10;
            this.labelCountdownTimer.Text = "time";
            // 
            // labelTonoData
            // 
            this.labelTonoData.AutoSize = true;
            this.labelTonoData.Location = new System.Drawing.Point(150, 13);
            this.labelTonoData.Name = "labelTonoData";
            this.labelTonoData.Size = new System.Drawing.Size(51, 13);
            this.labelTonoData.TabIndex = 11;
            this.labelTonoData.Text = "tonoData";
            // 
            // labelCuffPulse
            // 
            this.labelCuffPulse.AutoSize = true;
            this.labelCuffPulse.Location = new System.Drawing.Point(150, 45);
            this.labelCuffPulse.Name = "labelCuffPulse";
            this.labelCuffPulse.Size = new System.Drawing.Size(51, 13);
            this.labelCuffPulse.TabIndex = 12;
            this.labelCuffPulse.Text = "cuffPulse";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(44, 109);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(64, 13);
            this.label3.TabIndex = 13;
            this.label3.Text = "Count down";
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(114, 110);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(30, 13);
            this.label4.TabIndex = 14;
            this.label4.Text = "(sec)";
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(44, 77);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(54, 13);
            this.label5.TabIndex = 15;
            this.label5.Text = "Cuff State";
            // 
            // form_capture_stub
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(442, 241);
            this.Controls.Add(this.label5);
            this.Controls.Add(this.label4);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.labelCuffPulse);
            this.Controls.Add(this.labelTonoData);
            this.Controls.Add(this.labelCountdownTimer);
            this.Controls.Add(this.labelCuffState);
            this.Controls.Add(this.progressBarTimeCountDown);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.buttonCancel);
            this.Controls.Add(this.buttonCapture);
            this.Name = "form_capture_stub";
            this.Text = "form_capture_stub";
            this.Load += new System.EventHandler(this.form_capture_stub_Load);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.ComponentModel.BackgroundWorker backgroundWorker1;
        private System.Windows.Forms.Button buttonCapture;
        private System.Windows.Forms.Button buttonCancel;
        private System.Windows.Forms.Timer timer1;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.ProgressBar progressBarTimeCountDown;
        private System.Windows.Forms.Label labelCuffState;
        private System.Windows.Forms.Label labelCountdownTimer;
        private System.Windows.Forms.Label labelTonoData;
        private System.Windows.Forms.Label labelCuffPulse;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Label label5;
    }
}
}
}

