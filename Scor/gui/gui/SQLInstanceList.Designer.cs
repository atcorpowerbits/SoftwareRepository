using System.Drawing;
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
            this.guiradbtnConnect = new Telerik.WinControls.UI.RadButton();
            this.guiradbtnCancel = new Telerik.WinControls.UI.RadButton();
            this.guicmbxSqlServerList = new Telerik.WinControls.UI.RadDropDownList();
            ((System.ComponentModel.ISupportInitialize)(this.guiradlblMessage)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.guiradbtnConnect)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.guiradbtnCancel)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.guicmbxSqlServerList)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this)).BeginInit();
            this.SuspendLayout();

            this.FormElement.TitleBar.TitleBarFill.NumberOfColors = 1;
            this.FormElement.TitleBar.TitleBarFill.BackColor = Color.FromArgb(88, 98, 146);
            this.BackColor = Color.FromArgb(142, 150, 186);
            this.FormElement.TitleBar.TitlePrimitive.ForeColor = Color.WhiteSmoke;

            // 
            // guiradlblMessage
            // 
            this.guiradlblMessage.AutoSize = false;
            this.guiradlblMessage.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(142)))), ((int)(((byte)(150)))), ((int)(((byte)(186)))));
            this.guiradlblMessage.Font = new System.Drawing.Font("Arial", 11.25F);
            this.guiradlblMessage.ForeColor = System.Drawing.Color.WhiteSmoke;
            this.guiradlblMessage.Location = new System.Drawing.Point(12, 12);
            this.guiradlblMessage.Name = "guiradlblMessage";
            // 
            // 
            // 
            this.guiradlblMessage.RootElement.ForeColor = System.Drawing.Color.WhiteSmoke;
            this.guiradlblMessage.Size = new System.Drawing.Size(320, 50);
            this.guiradlblMessage.TabIndex = 0;
            this.guiradlblMessage.Text = "Server name not valid,select another server from the below list.";
            // 
            // guiradbtnConnect
            // 
            this.guiradbtnConnect.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(142)))), ((int)(((byte)(150)))), ((int)(((byte)(186)))));
            this.guiradbtnConnect.Font = new System.Drawing.Font("Arial", 11.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.guiradbtnConnect.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(23)))), ((int)(((byte)(29)))), ((int)(((byte)(55)))));
            this.guiradbtnConnect.Location = new System.Drawing.Point(68, 190);
            this.guiradbtnConnect.Name = "guiradbtnConnect";
            // 
            // 
            // 
            this.guiradbtnConnect.RootElement.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(23)))), ((int)(((byte)(29)))), ((int)(((byte)(55)))));
            this.guiradbtnConnect.Size = new System.Drawing.Size(80, 25);
            this.guiradbtnConnect.TabIndex = 22;
            this.guiradbtnConnect.Text = "Connect";
            this.guiradbtnConnect.Click += new System.EventHandler(this.guiradbtnConnect_Click);
            ((Telerik.WinControls.UI.RadButtonElement)(this.guiradbtnConnect.GetChildAt(0))).Text = "Connect";
            ((Telerik.WinControls.Primitives.FillPrimitive)(this.guiradbtnConnect.GetChildAt(0).GetChildAt(0))).BackColor2 = System.Drawing.Color.FromArgb(((int)(((byte)(172)))), ((int)(((byte)(177)))), ((int)(((byte)(204)))));
            ((Telerik.WinControls.Primitives.FillPrimitive)(this.guiradbtnConnect.GetChildAt(0).GetChildAt(0))).BackColor3 = System.Drawing.Color.FromArgb(((int)(((byte)(172)))), ((int)(((byte)(177)))), ((int)(((byte)(204)))));
            ((Telerik.WinControls.Primitives.FillPrimitive)(this.guiradbtnConnect.GetChildAt(0).GetChildAt(0))).BackColor4 = System.Drawing.Color.FromArgb(((int)(((byte)(142)))), ((int)(((byte)(150)))), ((int)(((byte)(186)))));
            ((Telerik.WinControls.Primitives.FillPrimitive)(this.guiradbtnConnect.GetChildAt(0).GetChildAt(0))).BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(225)))), ((int)(((byte)(228)))), ((int)(((byte)(243)))));
            ((Telerik.WinControls.Primitives.BorderPrimitive)(this.guiradbtnConnect.GetChildAt(0).GetChildAt(2))).ForeColor = System.Drawing.Color.White;
            ((Telerik.WinControls.Primitives.FocusPrimitive)(this.guiradbtnConnect.GetChildAt(0).GetChildAt(3))).GradientStyle = Telerik.WinControls.GradientStyles.Linear;
            // 
            // guiradbtnCancel
            // 
            this.guiradbtnCancel.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(142)))), ((int)(((byte)(150)))), ((int)(((byte)(186)))));
            this.guiradbtnCancel.Font = new System.Drawing.Font("Arial", 11.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.guiradbtnCancel.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(23)))), ((int)(((byte)(29)))), ((int)(((byte)(55)))));
            this.guiradbtnCancel.Location = new System.Drawing.Point(174, 190);
            this.guiradbtnCancel.Name = "guiradbtnCancel";
            // 
            // 
            // 
            this.guiradbtnCancel.RootElement.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(23)))), ((int)(((byte)(29)))), ((int)(((byte)(55)))));
            this.guiradbtnCancel.Size = new System.Drawing.Size(80, 25);
            this.guiradbtnCancel.TabIndex = 23;
            this.guiradbtnCancel.Text = "Cancel";
            this.guiradbtnCancel.Click += new System.EventHandler(this.guiradbtnCancel_Click);
            ((Telerik.WinControls.UI.RadButtonElement)(this.guiradbtnCancel.GetChildAt(0))).Text = "Cancel";
            ((Telerik.WinControls.Primitives.FillPrimitive)(this.guiradbtnCancel.GetChildAt(0).GetChildAt(0))).BackColor2 = System.Drawing.Color.FromArgb(((int)(((byte)(172)))), ((int)(((byte)(177)))), ((int)(((byte)(204)))));
            ((Telerik.WinControls.Primitives.FillPrimitive)(this.guiradbtnCancel.GetChildAt(0).GetChildAt(0))).BackColor3 = System.Drawing.Color.FromArgb(((int)(((byte)(172)))), ((int)(((byte)(177)))), ((int)(((byte)(204)))));
            ((Telerik.WinControls.Primitives.FillPrimitive)(this.guiradbtnCancel.GetChildAt(0).GetChildAt(0))).BackColor4 = System.Drawing.Color.FromArgb(((int)(((byte)(142)))), ((int)(((byte)(150)))), ((int)(((byte)(186)))));
            ((Telerik.WinControls.Primitives.FillPrimitive)(this.guiradbtnCancel.GetChildAt(0).GetChildAt(0))).BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(225)))), ((int)(((byte)(228)))), ((int)(((byte)(243)))));
            ((Telerik.WinControls.Primitives.BorderPrimitive)(this.guiradbtnCancel.GetChildAt(0).GetChildAt(2))).ForeColor = System.Drawing.Color.White;
            // 
            // guicmbxSqlServerList
            // 
            this.guicmbxSqlServerList.AutoCompleteMode = System.Windows.Forms.AutoCompleteMode.Append;
            this.guicmbxSqlServerList.AutoSize = false;
            this.guicmbxSqlServerList.DropDownHeight = 80;
            this.guicmbxSqlServerList.Font = new System.Drawing.Font("Arial", 11.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.guicmbxSqlServerList.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(23)))), ((int)(((byte)(29)))), ((int)(((byte)(55)))));
            this.guicmbxSqlServerList.Location = new System.Drawing.Point(68, 77);
            this.guicmbxSqlServerList.Name = "guicmbxSqlServerList";
            // 
            // 
            // 
            this.guicmbxSqlServerList.RootElement.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(23)))), ((int)(((byte)(29)))), ((int)(((byte)(55)))));
            this.guicmbxSqlServerList.Size = new System.Drawing.Size(206, 25);
            this.guicmbxSqlServerList.TabIndex = 24;
            // 
            // SQLInstanceList
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(142)))), ((int)(((byte)(150)))), ((int)(((byte)(186)))));
            this.ClientSize = new System.Drawing.Size(342, 262);
            this.Controls.Add(this.guicmbxSqlServerList);
            this.Controls.Add(this.guiradbtnCancel);
            this.Controls.Add(this.guiradbtnConnect);
            this.Controls.Add(this.guiradlblMessage);
            this.Font = new System.Drawing.Font("Arial", 11.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.ForeColor = System.Drawing.Color.WhiteSmoke;
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.KeyPreview = true;
            this.MaximizeBox = false;
            this.MinimizeBox = false;
            this.Name = "SQLInstanceList";
            // 
            // 
            // 
            this.RootElement.ApplyShapeToControl = true;
            this.RootElement.ForeColor = System.Drawing.Color.WhiteSmoke;
            this.ShowItemToolTips = false;
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "Available Databases ";
            this.ThemeName = "ControlDefault";
            this.Load += new System.EventHandler(this.SQLInstanceList_Load);
            ((System.ComponentModel.ISupportInitialize)(this.guiradlblMessage)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.guiradbtnConnect)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.guiradbtnCancel)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.guicmbxSqlServerList)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this)).EndInit();
            this.ResumeLayout(false);

        }

        #endregion

        private Telerik.WinControls.UI.RadLabel guiradlblMessage;
        private Telerik.WinControls.UI.RadButton guiradbtnConnect;
        private Telerik.WinControls.UI.RadButton guiradbtnCancel;
        private Telerik.WinControls.UI.RadDropDownList guicmbxSqlServerList;
    }
}

