namespace CreateDatabase
{
    partial class SelectionForm
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
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(SelectionForm));
            this.guicmbxSqlServerList = new System.Windows.Forms.ComboBox();
            this.button_Ok = new System.Windows.Forms.Button();
            this.labelMesg = new System.Windows.Forms.Label();
            this.button_Cancel = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // guicmbxSqlServerList
            // 
            this.guicmbxSqlServerList.BackColor = System.Drawing.Color.WhiteSmoke;
            this.guicmbxSqlServerList.Font = new System.Drawing.Font("Arial", 11.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.guicmbxSqlServerList.ForeColor = System.Drawing.Color.Black;
            this.guicmbxSqlServerList.FormattingEnabled = true;
            this.guicmbxSqlServerList.Location = new System.Drawing.Point(264, 21);
            this.guicmbxSqlServerList.Name = "guicmbxSqlServerList";
            this.guicmbxSqlServerList.Size = new System.Drawing.Size(160, 25);
            this.guicmbxSqlServerList.TabIndex = 0;
            // 
            // button_Ok
            // 
            this.button_Ok.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(142)))), ((int)(((byte)(150)))), ((int)(((byte)(186)))));
            this.button_Ok.ForeColor = System.Drawing.Color.WhiteSmoke;
            this.button_Ok.Location = new System.Drawing.Point(264, 67);
            this.button_Ok.Name = "button_Ok";
            this.button_Ok.Size = new System.Drawing.Size(75, 23);
            this.button_Ok.TabIndex = 1;
            this.button_Ok.Text = "Ok";
            this.button_Ok.UseVisualStyleBackColor = false;
            this.button_Ok.Click += new System.EventHandler(this.button_Ok_Click);
            // 
            // labelMesg
            // 
            this.labelMesg.Font = new System.Drawing.Font("Arial", 11.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.labelMesg.ForeColor = System.Drawing.Color.WhiteSmoke;
            this.labelMesg.Location = new System.Drawing.Point(8, 18);
            this.labelMesg.Name = "labelMesg";
            this.labelMesg.Size = new System.Drawing.Size(250, 36);
            this.labelMesg.TabIndex = 2;
            this.labelMesg.Text = "Select Database";
            // 
            // button_Cancel
            // 
            this.button_Cancel.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(142)))), ((int)(((byte)(150)))), ((int)(((byte)(186)))));
            this.button_Cancel.ForeColor = System.Drawing.Color.WhiteSmoke;
            this.button_Cancel.Location = new System.Drawing.Point(349, 67);
            this.button_Cancel.Name = "button_Cancel";
            this.button_Cancel.Size = new System.Drawing.Size(75, 23);
            this.button_Cancel.TabIndex = 3;
            this.button_Cancel.Text = "Cancel";
            this.button_Cancel.UseVisualStyleBackColor = false;
            this.button_Cancel.Click += new System.EventHandler(this.button_Cancel_Click);
            // 
            // SelectionForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(142)))), ((int)(((byte)(150)))), ((int)(((byte)(186)))));
            this.ClientSize = new System.Drawing.Size(442, 100);
            this.ControlBox = false;
            this.Controls.Add(this.button_Cancel);
            this.Controls.Add(this.labelMesg);
            this.Controls.Add(this.button_Ok);
            this.Controls.Add(this.guicmbxSqlServerList);
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.MaximumSize = new System.Drawing.Size(450, 134);
            this.Name = "SelectionForm";
            this.ShowInTaskbar = false;
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "SelectionWindow";
            this.Load += new System.EventHandler(this.SelectionForm_Load);
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.ComboBox guicmbxSqlServerList;
        private System.Windows.Forms.Button button_Ok;
        private System.Windows.Forms.Label labelMesg;
        private System.Windows.Forms.Button button_Cancel;
    }
}

