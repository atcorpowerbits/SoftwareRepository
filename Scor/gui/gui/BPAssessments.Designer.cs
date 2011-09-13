namespace AtCor.Scor.Gui.Presentation
{
    partial class BPAssessments
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
            this.guiradgrdAssessmentsDetails = new Telerik.WinControls.UI.RadGridView();
            ((System.ComponentModel.ISupportInitialize)(this.guiradgrdAssessmentsDetails)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.guiradgrdAssessmentsDetails.MasterTemplate)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this)).BeginInit();
            this.SuspendLayout();
            // 
            // guiradgrdAssessmentsDetails
            // 
            this.guiradgrdAssessmentsDetails.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(142)))), ((int)(((byte)(150)))), ((int)(((byte)(186)))));
            this.guiradgrdAssessmentsDetails.EnableHotTracking = false;
            this.guiradgrdAssessmentsDetails.Font = new System.Drawing.Font("Arial", 11.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.guiradgrdAssessmentsDetails.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(29)))), ((int)(((byte)(30)))), ((int)(((byte)(55)))));
            this.guiradgrdAssessmentsDetails.Location = new System.Drawing.Point(19, 16);
            // 
            // guiradgrdAssessmentsDetails
            // 
            this.guiradgrdAssessmentsDetails.MasterTemplate.AllowAddNewRow = false;
            this.guiradgrdAssessmentsDetails.MasterTemplate.AllowColumnHeaderContextMenu = false;
            this.guiradgrdAssessmentsDetails.MasterTemplate.AllowColumnReorder = false;
            this.guiradgrdAssessmentsDetails.MasterTemplate.AllowColumnResize = false;
            this.guiradgrdAssessmentsDetails.MasterTemplate.AllowDeleteRow = false;
            this.guiradgrdAssessmentsDetails.MasterTemplate.AllowEditRow = false;
            this.guiradgrdAssessmentsDetails.MasterTemplate.AllowRowResize = false;
            this.guiradgrdAssessmentsDetails.MasterTemplate.EnableAlternatingRowColor = true;
            this.guiradgrdAssessmentsDetails.MasterTemplate.ShowRowHeaderColumn = false;
            this.guiradgrdAssessmentsDetails.Name = "guiradgrdAssessmentsDetails";
            this.guiradgrdAssessmentsDetails.Padding = new System.Windows.Forms.Padding(0, 0, 0, 1);
            // 
            // 
            // 
            this.guiradgrdAssessmentsDetails.RootElement.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(29)))), ((int)(((byte)(30)))), ((int)(((byte)(55)))));
            this.guiradgrdAssessmentsDetails.RootElement.Padding = new System.Windows.Forms.Padding(0, 0, 0, 1);
            this.guiradgrdAssessmentsDetails.ShowGroupPanel = false;
            this.guiradgrdAssessmentsDetails.Size = new System.Drawing.Size(290, 140);
            this.guiradgrdAssessmentsDetails.TabIndex = 1;
            this.guiradgrdAssessmentsDetails.Text = "radGridView1";
            this.guiradgrdAssessmentsDetails.RowFormatting += new Telerik.WinControls.UI.RowFormattingEventHandler(this.guiradgrdAssessmentsDetails_RowFormatting);
            // 
            // BPAssessments
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(142)))), ((int)(((byte)(150)))), ((int)(((byte)(186)))));
            this.ClientSize = new System.Drawing.Size(328, 172);
            this.Controls.Add(this.guiradgrdAssessmentsDetails);
            this.MaximizeBox = false;
            this.MinimizeBox = false;
            this.Name = "BPAssessments";
            // 
            // 
            // 
            this.RootElement.ApplyShapeToControl = true;
            this.Text = "BP Assessments";
            this.ThemeName = "ControlDefault";
            this.Load += new System.EventHandler(this.BPAssessments_Load);
            ((System.ComponentModel.ISupportInitialize)(this.guiradgrdAssessmentsDetails.MasterTemplate)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.guiradgrdAssessmentsDetails)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this)).EndInit();
            this.ResumeLayout(false);

        }

        #endregion

        public Telerik.WinControls.UI.RadGridView guiradgrdAssessmentsDetails;
    }
}

