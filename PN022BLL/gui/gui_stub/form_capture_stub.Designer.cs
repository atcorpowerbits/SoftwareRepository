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
            this.buttonCapture.Location = new System.Drawing.Point(370, 262);
            this.buttonCapture.Name = "buttonCapture";
            this.buttonCapture.Size = new System.Drawing.Size(75, 23);
            this.buttonCapture.TabIndex = 1;
            this.buttonCapture.Text = "Simulate";
            this.buttonCapture.UseVisualStyleBackColor = true;
            this.buttonCapture.Click += new System.EventHandler(this.buttonCapture_Click);
            // 
            // buttonCancel
            // 
            this.buttonCancel.Location = new System.Drawing.Point(450, 262);
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
            // form_capture_stub
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(550, 428);
            this.Controls.Add(this.listBoxCuffPulse);
            this.Controls.Add(this.buttonCancel);
            this.Controls.Add(this.buttonCapture);
            this.Controls.Add(this.listBoxTonoData);
            this.Name = "form_capture_stub";
            this.Text = "form_capture_stub";
            this.Load += new System.EventHandler(this.form_capture_stub_Load);
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.ListBox listBoxTonoData;
        private System.ComponentModel.BackgroundWorker backgroundWorker1;
        private System.Windows.Forms.Button buttonCapture;
        private System.Windows.Forms.Button buttonCancel;
        private System.Windows.Forms.Timer timer1;
        private System.Windows.Forms.ListBox listBoxCuffPulse;
    }
}