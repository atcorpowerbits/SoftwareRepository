namespace AtCor.Scor.Gui.Presentation
{
    partial class Migrate
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
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(Migrate));
            this.guiradlblHeader = new Telerik.WinControls.UI.RadLabel();
            this.guicmbGroupNameList = new System.Windows.Forms.ComboBox();
            this.radbtnMigrate = new Telerik.WinControls.UI.RadButton();
            this.radbtnCancel = new Telerik.WinControls.UI.RadButton();
            ((System.ComponentModel.ISupportInitialize)(this.guiradlblHeader)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.radbtnMigrate)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.radbtnCancel)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this)).BeginInit();
            this.SuspendLayout();
            // 
            // guiradlblHeader
            // 
            this.guiradlblHeader.AutoSize = false;
            this.guiradlblHeader.Font = new System.Drawing.Font("Verdana", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.guiradlblHeader.Location = new System.Drawing.Point(12, 12);
            this.guiradlblHeader.Name = "guiradlblHeader";
            this.guiradlblHeader.Size = new System.Drawing.Size(320, 50);
            this.guiradlblHeader.TabIndex = 1;
            // 
            // guicmbGroupNameList
            // 
            this.guicmbGroupNameList.DropDownHeight = 80;
            this.guicmbGroupNameList.Font = new System.Drawing.Font("Verdana", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.guicmbGroupNameList.FormattingEnabled = true;
            this.guicmbGroupNameList.IntegralHeight = false;
            this.guicmbGroupNameList.Location = new System.Drawing.Point(68, 77);
            this.guicmbGroupNameList.Name = "guicmbGroupNameList";
            this.guicmbGroupNameList.Size = new System.Drawing.Size(206, 24);
            this.guicmbGroupNameList.TabIndex = 2;
            // 
            // radbtnMigrate
            // 
            this.radbtnMigrate.Location = new System.Drawing.Point(68, 190);
            this.radbtnMigrate.Name = "radbtnMigrate";
            this.radbtnMigrate.Size = new System.Drawing.Size(100, 25);
            this.radbtnMigrate.TabIndex = 3;
            this.radbtnMigrate.Text = "radButton1";
            this.radbtnMigrate.Click += new System.EventHandler(this.radbtnMigrate_Click);
            // 
            // radbtnCancel
            // 
            this.radbtnCancel.Location = new System.Drawing.Point(174, 190);
            this.radbtnCancel.Name = "radbtnCancel";
            this.radbtnCancel.Size = new System.Drawing.Size(100, 25);
            this.radbtnCancel.TabIndex = 4;
            this.radbtnCancel.Text = "radButton2";
            this.radbtnCancel.Click += new System.EventHandler(this.radbtnCancel_Click);
            // 
            // Migrate
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(342, 256);
            this.Controls.Add(this.radbtnCancel);
            this.Controls.Add(this.radbtnMigrate);
            this.Controls.Add(this.guicmbGroupNameList);
            this.Controls.Add(this.guiradlblHeader);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle;
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.MaximizeBox = false;
            this.MinimizeBox = false;
            this.Name = "Migrate";
            // 
            // 
            // 
            this.RootElement.ApplyShapeToControl = true;
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "Migrate Database";
            this.ThemeName = "ControlDefault";
            this.Load += new System.EventHandler(this.Migrate_Load);
            ((System.ComponentModel.ISupportInitialize)(this.guiradlblHeader)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.radbtnMigrate)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.radbtnCancel)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this)).EndInit();
            this.ResumeLayout(false);

        }

        #endregion

        private Telerik.WinControls.UI.RadLabel guiradlblHeader;
        private System.Windows.Forms.ComboBox guicmbGroupNameList;
        private Telerik.WinControls.UI.RadButton radbtnMigrate;
        private Telerik.WinControls.UI.RadButton radbtnCancel;
    }
}

