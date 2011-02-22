namespace AtCor.Scor.Gui.Presentation
{
    partial class SQLInstanceList
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
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(SQLInstanceList));
            this.guiradlblMessage = new Telerik.WinControls.UI.RadLabel();
            this.guicmbxSqlServerList = new System.Windows.Forms.ComboBox();
            this.guiradbtnConnect = new Telerik.WinControls.UI.RadButton();
            this.guiradbtnCancel = new Telerik.WinControls.UI.RadButton();
            ((System.ComponentModel.ISupportInitialize)(this.guiradlblMessage)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.guiradbtnConnect)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.guiradbtnCancel)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this)).BeginInit();
            this.SuspendLayout();
            // 
            // guiradlblMessage
            // 
            this.guiradlblMessage.AutoSize = false;
            this.guiradlblMessage.Font = new System.Drawing.Font("Verdana", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.guiradlblMessage.Location = new System.Drawing.Point(12, 12);
            this.guiradlblMessage.Name = "guiradlblMessage";
            this.guiradlblMessage.Size = new System.Drawing.Size(320, 50);
            this.guiradlblMessage.TabIndex = 0;
            this.guiradlblMessage.Text = "Server name not valid,select another server from the below list.";
            // 
            // guicmbxSqlServerList
            // 
            this.guicmbxSqlServerList.DropDownHeight = 80;
            this.guicmbxSqlServerList.Font = new System.Drawing.Font("Verdana", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.guicmbxSqlServerList.FormattingEnabled = true;
            this.guicmbxSqlServerList.IntegralHeight = false;
            this.guicmbxSqlServerList.Location = new System.Drawing.Point(68, 77);
            this.guicmbxSqlServerList.Name = "guicmbxSqlServerList";
            this.guicmbxSqlServerList.Size = new System.Drawing.Size(206, 24);
            this.guicmbxSqlServerList.TabIndex = 1;
            
            // 
            // guiradbtnConnect
            // 
            this.guiradbtnConnect.Font = new System.Drawing.Font("Verdana", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.guiradbtnConnect.Location = new System.Drawing.Point(68, 190);
            this.guiradbtnConnect.Name = "guiradbtnConnect";
            this.guiradbtnConnect.Size = new System.Drawing.Size(100, 25);
            this.guiradbtnConnect.TabIndex = 22;
            this.guiradbtnConnect.Text = "Connect";
            this.guiradbtnConnect.Click += new System.EventHandler(this.guiradbtnConnect_Click);
            // 
            // guiradbtnCancel
            // 
            this.guiradbtnCancel.Font = new System.Drawing.Font("Verdana", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.guiradbtnCancel.Location = new System.Drawing.Point(174, 190);
            this.guiradbtnCancel.Name = "guiradbtnCancel";
            this.guiradbtnCancel.Size = new System.Drawing.Size(100, 25);
            this.guiradbtnCancel.TabIndex = 23;
            this.guiradbtnCancel.Text = "Cancel";
            this.guiradbtnCancel.Click += new System.EventHandler(this.guiradbtnCancel_Click);
            // 
            // SQLInstanceList
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(342, 262);
            this.Controls.Add(this.guiradbtnCancel);
            this.Controls.Add(this.guiradbtnConnect);
            this.Controls.Add(this.guicmbxSqlServerList);
            this.Controls.Add(this.guiradlblMessage);
            this.Font = new System.Drawing.Font("Verdana", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.MaximizeBox = false;
            this.MinimizeBox = false;
            this.Name = "SQLInstanceList";
            // 
            // 
            // 
            this.RootElement.ApplyShapeToControl = true;
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "Available Databases ";
            this.ThemeName = "ControlDefault";
            this.Load += new System.EventHandler(this.SQLInstanceList_Load);
            ((System.ComponentModel.ISupportInitialize)(this.guiradlblMessage)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.guiradbtnConnect)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.guiradbtnCancel)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this)).EndInit();
            this.ResumeLayout(false);

        }

        #endregion

        private Telerik.WinControls.UI.RadLabel guiradlblMessage;
        private System.Windows.Forms.ComboBox guicmbxSqlServerList;
        private Telerik.WinControls.UI.RadButton guiradbtnConnect;
        private Telerik.WinControls.UI.RadButton guiradbtnCancel;
    }
}

