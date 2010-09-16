namespace gui
{
    partial class form_bizmix_stub
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
            this.buttonCreatePerson = new System.Windows.Forms.Button();
            this.dateTimePicker1 = new System.Windows.Forms.DateTimePicker();
            this.labelAge = new System.Windows.Forms.Label();
            this.buttonDirectAPI = new System.Windows.Forms.Button();
            this.labelDirectAPI = new System.Windows.Forms.Label();
            this.buttonIndirectInt = new System.Windows.Forms.Button();
            this.labelIndirectInt = new System.Windows.Forms.Label();
            this.buttonIndirectAPI = new System.Windows.Forms.Button();
            this.labelIndirectAPI = new System.Windows.Forms.Label();
            this.label1 = new System.Windows.Forms.Label();
            this.SuspendLayout();
            // 
            // buttonCreatePerson
            // 
            this.buttonCreatePerson.Location = new System.Drawing.Point(13, 72);
            this.buttonCreatePerson.Name = "buttonCreatePerson";
            this.buttonCreatePerson.Size = new System.Drawing.Size(153, 23);
            this.buttonCreatePerson.TabIndex = 0;
            this.buttonCreatePerson.Text = "Calculate Age - Native Obj";
            this.buttonCreatePerson.UseVisualStyleBackColor = true;
            this.buttonCreatePerson.Click += new System.EventHandler(this.buttonCreatePerson_Click);
            // 
            // dateTimePicker1
            // 
            this.dateTimePicker1.Location = new System.Drawing.Point(72, 32);
            this.dateTimePicker1.Name = "dateTimePicker1";
            this.dateTimePicker1.Size = new System.Drawing.Size(200, 20);
            this.dateTimePicker1.TabIndex = 1;
            // 
            // labelAge
            // 
            this.labelAge.AutoSize = true;
            this.labelAge.Location = new System.Drawing.Point(182, 77);
            this.labelAge.Name = "labelAge";
            this.labelAge.Size = new System.Drawing.Size(19, 13);
            this.labelAge.TabIndex = 3;
            this.labelAge.Text = "nn";
            // 
            // buttonDirectAPI
            // 
            this.buttonDirectAPI.Location = new System.Drawing.Point(13, 120);
            this.buttonDirectAPI.Name = "buttonDirectAPI";
            this.buttonDirectAPI.Size = new System.Drawing.Size(153, 23);
            this.buttonDirectAPI.TabIndex = 4;
            this.buttonDirectAPI.Text = "Call DLL API Directly";
            this.buttonDirectAPI.UseVisualStyleBackColor = true;
            this.buttonDirectAPI.Click += new System.EventHandler(this.button1_Click);
            // 
            // labelDirectAPI
            // 
            this.labelDirectAPI.AutoSize = true;
            this.labelDirectAPI.Location = new System.Drawing.Point(182, 125);
            this.labelDirectAPI.Name = "labelDirectAPI";
            this.labelDirectAPI.Size = new System.Drawing.Size(17, 13);
            this.labelDirectAPI.TabIndex = 5;
            this.labelDirectAPI.Text = "xx";
            // 
            // buttonIndirectInt
            // 
            this.buttonIndirectInt.Location = new System.Drawing.Point(13, 214);
            this.buttonIndirectInt.Name = "buttonIndirectInt";
            this.buttonIndirectInt.Size = new System.Drawing.Size(153, 23);
            this.buttonIndirectInt.TabIndex = 6;
            this.buttonIndirectInt.Text = "Get DLL Int Indirectly";
            this.buttonIndirectInt.UseVisualStyleBackColor = true;
            this.buttonIndirectInt.Click += new System.EventHandler(this.buttonCallIndirect_Click);
            // 
            // labelIndirectInt
            // 
            this.labelIndirectInt.AutoSize = true;
            this.labelIndirectInt.Location = new System.Drawing.Point(182, 219);
            this.labelIndirectInt.Name = "labelIndirectInt";
            this.labelIndirectInt.Size = new System.Drawing.Size(17, 13);
            this.labelIndirectInt.TabIndex = 7;
            this.labelIndirectInt.Text = "zz";
            // 
            // buttonIndirectAPI
            // 
            this.buttonIndirectAPI.Location = new System.Drawing.Point(13, 170);
            this.buttonIndirectAPI.Name = "buttonIndirectAPI";
            this.buttonIndirectAPI.Size = new System.Drawing.Size(153, 23);
            this.buttonIndirectAPI.TabIndex = 8;
            this.buttonIndirectAPI.Text = "Call DLL API Indirectly";
            this.buttonIndirectAPI.UseVisualStyleBackColor = true;
            this.buttonIndirectAPI.Click += new System.EventHandler(this.buttonIndirectAPI_Click);
            // 
            // labelIndirectAPI
            // 
            this.labelIndirectAPI.AutoSize = true;
            this.labelIndirectAPI.Location = new System.Drawing.Point(182, 175);
            this.labelIndirectAPI.Name = "labelIndirectAPI";
            this.labelIndirectAPI.Size = new System.Drawing.Size(17, 13);
            this.labelIndirectAPI.TabIndex = 9;
            this.labelIndirectAPI.Text = "yy";
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(10, 35);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(58, 13);
            this.label1.TabIndex = 10;
            this.label1.Text = "Enter Date";
            // 
            // form_bizmix_stub
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(284, 262);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.labelIndirectAPI);
            this.Controls.Add(this.buttonIndirectAPI);
            this.Controls.Add(this.labelIndirectInt);
            this.Controls.Add(this.buttonIndirectInt);
            this.Controls.Add(this.labelDirectAPI);
            this.Controls.Add(this.buttonDirectAPI);
            this.Controls.Add(this.labelAge);
            this.Controls.Add(this.dateTimePicker1);
            this.Controls.Add(this.buttonCreatePerson);
            this.Name = "form_bizmix_stub";
            this.Text = "form_bizmix_stub";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button buttonCreatePerson;
        private System.Windows.Forms.DateTimePicker dateTimePicker1;
        private System.Windows.Forms.Label labelAge;
        private System.Windows.Forms.Button buttonDirectAPI;
        private System.Windows.Forms.Label labelDirectAPI;
        private System.Windows.Forms.Button buttonIndirectInt;
        private System.Windows.Forms.Label labelIndirectInt;
        private System.Windows.Forms.Button buttonIndirectAPI;
        private System.Windows.Forms.Label labelIndirectAPI;
        private System.Windows.Forms.Label label1;
    }
}