namespace AtCor.Scor.Gui.Presentation
{

    partial class SplashScreen
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
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(SplashScreen));
            this.lblimage = new System.Windows.Forms.Label();
            this.lblInitialMsg = new System.Windows.Forms.Label();
            this.lblversion = new System.Windows.Forms.Label();
            this.lblCopyright = new System.Windows.Forms.Label();
            this.radBottomLabel = new Telerik.WinControls.UI.RadLabel();
            this.radLabelCopyRight = new Telerik.WinControls.UI.RadLabel();
            this.radLabelScorName = new Telerik.WinControls.UI.RadLabel();
            this.radVersionNo = new Telerik.WinControls.UI.RadLabel();
            ((System.ComponentModel.ISupportInitialize)(this.radBottomLabel)).BeginInit();
            this.radBottomLabel.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.radLabelCopyRight)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.radLabelScorName)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.radVersionNo)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this)).BeginInit();
            this.SuspendLayout();
            // 
            // lblimage
            // 
            this.lblimage.Font = new System.Drawing.Font("Arial", 11.25F);
            this.lblimage.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(23)))), ((int)(((byte)(29)))), ((int)(((byte)(55)))));
            this.lblimage.Image = ((System.Drawing.Image)(resources.GetObject("lblimage.Image")));
            this.lblimage.Location = new System.Drawing.Point(15, 12);
            this.lblimage.Name = "lblimage";
            this.lblimage.Size = new System.Drawing.Size(567, 459);
            this.lblimage.TabIndex = 1;
            // 
            // lblInitialMsg
            // 
            this.lblInitialMsg.Font = new System.Drawing.Font("Arial", 11.25F, System.Drawing.FontStyle.Bold);
            this.lblInitialMsg.ForeColor = System.Drawing.Color.WhiteSmoke;
            this.lblInitialMsg.Location = new System.Drawing.Point(14, 479);
            this.lblInitialMsg.Name = "lblInitialMsg";
            this.lblInitialMsg.Size = new System.Drawing.Size(567, 17);
            this.lblInitialMsg.TabIndex = 2;
            this.lblInitialMsg.TextAlign = System.Drawing.ContentAlignment.TopCenter;
            // 
            // lblversion
            // 
            this.lblversion.BackColor = System.Drawing.Color.DarkBlue;
            this.lblversion.Font = new System.Drawing.Font("Arial", 11.25F);
            this.lblversion.ForeColor = System.Drawing.Color.WhiteSmoke;
            this.lblversion.Location = new System.Drawing.Point(68, 451);
            this.lblversion.Name = "lblversion";
            this.lblversion.Size = new System.Drawing.Size(20, 13);
            this.lblversion.TabIndex = 3;
            // 
            // lblCopyright
            // 
            this.lblCopyright.BackColor = System.Drawing.Color.DarkBlue;
            this.lblCopyright.Font = new System.Drawing.Font("Arial", 11.25F);
            this.lblCopyright.ForeColor = System.Drawing.Color.WhiteSmoke;
            this.lblCopyright.Location = new System.Drawing.Point(539, 451);
            this.lblCopyright.Margin = new System.Windows.Forms.Padding(0);
            this.lblCopyright.Name = "lblCopyright";
            this.lblCopyright.Size = new System.Drawing.Size(35, 13);
            this.lblCopyright.TabIndex = 4;
            // 
            // radBottomLabel
            // 
            this.radBottomLabel.AutoSize = false;
            this.radBottomLabel.BackgroundImage = ((System.Drawing.Image)(resources.GetObject("radBottomLabel.BackgroundImage")));
            this.radBottomLabel.Controls.Add(this.radLabelCopyRight);
            this.radBottomLabel.Controls.Add(this.radLabelScorName);
            this.radBottomLabel.Controls.Add(this.radVersionNo);
            this.radBottomLabel.Font = new System.Drawing.Font("Arial", 11.25F);
            this.radBottomLabel.ForeColor = System.Drawing.Color.WhiteSmoke;
            this.radBottomLabel.Location = new System.Drawing.Point(18, 448);
            this.radBottomLabel.Name = "radBottomLabel";
            // 
            // 
            // 
            this.radBottomLabel.RootElement.ForeColor = System.Drawing.Color.WhiteSmoke;
            this.radBottomLabel.Size = new System.Drawing.Size(560, 28);
            this.radBottomLabel.TabIndex = 6;
            // 
            // radLabelCopyRight
            // 
            this.radLabelCopyRight.BackColor = System.Drawing.Color.Navy;
            this.radLabelCopyRight.Font = new System.Drawing.Font("Arial", 11.25F);
            this.radLabelCopyRight.Location = new System.Drawing.Point(225, 4);
            this.radLabelCopyRight.Name = "radLabelCopyRight";
            this.radLabelCopyRight.Size = new System.Drawing.Size(2, 2);
            this.radLabelCopyRight.TabIndex = 7;
            // 
            // radLabelScorName
            // 
            this.radLabelScorName.BackColor = System.Drawing.Color.Navy;
            this.radLabelScorName.Font = new System.Drawing.Font("Arial", 11.25F, System.Drawing.FontStyle.Bold);
            this.radLabelScorName.Location = new System.Drawing.Point(98, 5);
            this.radLabelScorName.Name = "radLabelScorName";
            this.radLabelScorName.Size = new System.Drawing.Size(2, 2);
            this.radLabelScorName.TabIndex = 0;
            // 
            // radVersionNo
            // 
            this.radVersionNo.BackColor = System.Drawing.Color.Navy;
            this.radVersionNo.Font = new System.Drawing.Font("Arial", 11.25F, System.Drawing.FontStyle.Bold);
            this.radVersionNo.Location = new System.Drawing.Point(3, 5);
            this.radVersionNo.Name = "radVersionNo";
            this.radVersionNo.Size = new System.Drawing.Size(2, 2);
            this.radVersionNo.TabIndex = 7;
            // 
            // SplashScreen
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.AutoSizeMode = System.Windows.Forms.AutoSizeMode.GrowAndShrink;
            this.BackColor = System.Drawing.Color.Black;
            this.ClientSize = new System.Drawing.Size(608, 525);
            this.Controls.Add(this.radBottomLabel);
            this.Controls.Add(this.lblCopyright);
            this.Controls.Add(this.lblversion);
            this.Controls.Add(this.lblInitialMsg);
            this.Controls.Add(this.lblimage);
            this.Font = new System.Drawing.Font("Arial", 11.25F);
            this.ForeColor = System.Drawing.Color.White;
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.None;
            this.Name = "SplashScreen";
            // 
            // 
            // 
            this.RootElement.ApplyShapeToControl = true;
            this.RootElement.ForeColor = System.Drawing.Color.White;
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "Scor";
            this.ThemeName = "ControlDefault";
            this.TopMost = true;
            ((System.ComponentModel.ISupportInitialize)(this.radBottomLabel)).EndInit();
            this.radBottomLabel.ResumeLayout(false);
            this.radBottomLabel.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.radLabelCopyRight)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.radLabelScorName)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.radVersionNo)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this)).EndInit();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.Label lblimage;
        private System.Windows.Forms.Label lblInitialMsg;
        private System.Windows.Forms.Label lblversion;
        private System.Windows.Forms.Label lblCopyright;
        private Telerik.WinControls.UI.RadLabel radBottomLabel;
        private Telerik.WinControls.UI.RadLabel radVersionNo;
        private Telerik.WinControls.UI.RadLabel radLabelScorName;
        private Telerik.WinControls.UI.RadLabel radLabelCopyRight;
        

    }
}

