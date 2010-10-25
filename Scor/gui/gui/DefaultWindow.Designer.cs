namespace AtCor
{
    namespace Scor
    {
        namespace Presentation
        {
            partial class DefaultWindow
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
                    System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(DefaultWindow));
                    this.radRibbonBar1 = new Telerik.WinControls.UI.RadRibbonBar();
                    this.rbnTabSystem = new Telerik.WinControls.UI.RibbonTab();
                    this.radRibbonBarGroupSettings = new Telerik.WinControls.UI.RadRibbonBarGroup();
                    this.radButtonElementSettings = new Telerik.WinControls.UI.RadButtonElement();
                    this.radButtonElementFindModule = new Telerik.WinControls.UI.RadButtonElement();
                    this.radButtonElementPrinterSetup = new Telerik.WinControls.UI.RadButtonElement();
                    this.radButtonElementExit = new Telerik.WinControls.UI.RadButtonElement();
                    this.rbnTabDatabase = new Telerik.WinControls.UI.RibbonTab();
                    this.rbnTabHelp = new Telerik.WinControls.UI.RibbonTab();
                    this.radStatusStrip1 = new Telerik.WinControls.UI.RadStatusStrip();
                    this.panel1 = new System.Windows.Forms.Panel();
                    ((System.ComponentModel.ISupportInitialize)(this.radRibbonBar1)).BeginInit();
                    ((System.ComponentModel.ISupportInitialize)(this.radStatusStrip1)).BeginInit();
                    ((System.ComponentModel.ISupportInitialize)(this)).BeginInit();
                    this.SuspendLayout();
                    // 
                    // radRibbonBar1
                    // 
                    this.radRibbonBar1.AutoSize = true;
                    this.radRibbonBar1.CommandTabs.AddRange(new Telerik.WinControls.RadItem[] {
            this.rbnTabSystem,
            this.rbnTabDatabase,
            this.rbnTabHelp});
                    this.radRibbonBar1.Dock = System.Windows.Forms.DockStyle.Top;
                    this.radRibbonBar1.EnableKeyMap = true;
                    // 
                    // 
                    // 
                    // 
                    // 
                    // 
                    this.radRibbonBar1.ExitButton.ButtonElement.Class = "RadMenuButtonElement";
                    this.radRibbonBar1.ExitButton.ButtonElement.TextImageRelation = System.Windows.Forms.TextImageRelation.ImageBeforeText;
                    this.radRibbonBar1.ExitButton.Text = "Exit";
                    this.radRibbonBar1.Location = new System.Drawing.Point(0, 0);
                    this.radRibbonBar1.Name = "radRibbonBar1";
                    // 
                    // 
                    // 
                    // 
                    // 
                    // 
                    this.radRibbonBar1.OptionsButton.ButtonElement.Class = "RadMenuButtonElement";
                    this.radRibbonBar1.OptionsButton.ButtonElement.TextImageRelation = System.Windows.Forms.TextImageRelation.ImageBeforeText;
                    this.radRibbonBar1.OptionsButton.Text = "Options";
                    // 
                    // 
                    // 
                    this.radRibbonBar1.RootElement.AutoSizeMode = Telerik.WinControls.RadAutoSizeMode.WrapAroundChildren;
                    this.radRibbonBar1.Size = new System.Drawing.Size(474, 150);
                    this.radRibbonBar1.StartButtonImage = ((System.Drawing.Image)(resources.GetObject("radRibbonBar1.StartButtonImage")));
                    this.radRibbonBar1.TabIndex = 0;
                    this.radRibbonBar1.Text = "Scor";
                    ((Telerik.WinControls.UI.RadRibbonBarElement)(this.radRibbonBar1.GetChildAt(0))).Text = "Scor";
                    ((Telerik.WinControls.UI.RadQuickAccessToolBar)(this.radRibbonBar1.GetChildAt(0).GetChildAt(0))).Visibility = Telerik.WinControls.ElementVisibility.Hidden;
                    ((Telerik.WinControls.UI.RadImageButtonElement)(this.radRibbonBar1.GetChildAt(0).GetChildAt(1).GetChildAt(0).GetChildAt(0).GetChildAt(1))).Enabled = false;
                    ((Telerik.WinControls.UI.RadImageButtonElement)(this.radRibbonBar1.GetChildAt(0).GetChildAt(1).GetChildAt(0).GetChildAt(0).GetChildAt(1))).Visibility = Telerik.WinControls.ElementVisibility.Visible;
                    // 
                    // rbnTabSystem
                    // 
                    this.rbnTabSystem.Alignment = System.Drawing.ContentAlignment.BottomLeft;
                    // 
                    // rbnTabSystem.ContentPanel
                    // 
                    this.rbnTabSystem.ContentPanel.BackColor = System.Drawing.SystemColors.ControlLightLight;
                    this.rbnTabSystem.ContentPanel.CausesValidation = true;
                    this.rbnTabSystem.ContentPanel.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
                    this.rbnTabSystem.ContentPanel.ForeColor = System.Drawing.SystemColors.ControlText;
                    this.rbnTabSystem.ContentPanel.Location = new System.Drawing.Point(0, 0);
                    this.rbnTabSystem.ContentPanel.Size = new System.Drawing.Size(200, 100);
                    this.rbnTabSystem.IsSelected = true;
                    this.rbnTabSystem.Items.AddRange(new Telerik.WinControls.RadItem[] {
            this.radRibbonBarGroupSettings});
                    this.rbnTabSystem.Name = "rbnTabSystem";
                    this.rbnTabSystem.StretchHorizontally = false;
                    this.rbnTabSystem.Text = "System";
                    // 
                    // radRibbonBarGroupSettings
                    // 
                    this.radRibbonBarGroupSettings.Items.AddRange(new Telerik.WinControls.RadItem[] {
            this.radButtonElementSettings,
            this.radButtonElementFindModule,
            this.radButtonElementPrinterSetup,
            this.radButtonElementExit});
                    this.radRibbonBarGroupSettings.Name = "radRibbonBarGroupSettings";
                    this.radRibbonBarGroupSettings.Text = "";
                    // 
                    // radButtonElementSettings
                    // 
                    this.radButtonElementSettings.Class = "RibbonBarButtonElement";
                    this.radButtonElementSettings.Image = ((System.Drawing.Image)(resources.GetObject("radButtonElementSettings.Image")));
                    this.radButtonElementSettings.ImageAlignment = System.Drawing.ContentAlignment.MiddleCenter;
                    this.radButtonElementSettings.Name = "radButtonElementSettings";
                    this.radButtonElementSettings.Text = "Settings";
                    this.radButtonElementSettings.TextImageRelation = System.Windows.Forms.TextImageRelation.ImageAboveText;
                    this.radButtonElementSettings.Click += new System.EventHandler(this.radButtonElementSettings_Click);
                    // 
                    // radButtonElementFindModule
                    // 
                    this.radButtonElementFindModule.Class = "RibbonBarButtonElement";
                    this.radButtonElementFindModule.Name = "radButtonElementFindModule";
                    this.radButtonElementFindModule.Text = "Find Module";
                    this.radButtonElementFindModule.TextImageRelation = System.Windows.Forms.TextImageRelation.ImageAboveText;
                    // 
                    // radButtonElementPrinterSetup
                    // 
                    this.radButtonElementPrinterSetup.Class = "RibbonBarButtonElement";
                    this.radButtonElementPrinterSetup.Name = "radButtonElementPrinterSetup";
                    this.radButtonElementPrinterSetup.Text = "Printer Setup";
                    this.radButtonElementPrinterSetup.TextImageRelation = System.Windows.Forms.TextImageRelation.ImageAboveText;
                    // 
                    // radButtonElementExit
                    // 
                    this.radButtonElementExit.Class = "RibbonBarButtonElement";
                    this.radButtonElementExit.Image = ((System.Drawing.Image)(resources.GetObject("radButtonElementExit.Image")));
                    this.radButtonElementExit.Name = "radButtonElementExit";
                    this.radButtonElementExit.Text = "Exit";
                    this.radButtonElementExit.TextImageRelation = System.Windows.Forms.TextImageRelation.ImageAboveText;
                    this.radButtonElementExit.Click += new System.EventHandler(this.radButtonElementExit_Click);
                    // 
                    // rbnTabDatabase
                    // 
                    this.rbnTabDatabase.Alignment = System.Drawing.ContentAlignment.BottomLeft;
                    // 
                    // rbnTabDatabase.ContentPanel
                    // 
                    this.rbnTabDatabase.ContentPanel.BackColor = System.Drawing.SystemColors.ControlLightLight;
                    this.rbnTabDatabase.ContentPanel.CausesValidation = true;
                    this.rbnTabDatabase.ContentPanel.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
                    this.rbnTabDatabase.ContentPanel.ForeColor = System.Drawing.SystemColors.ControlText;
                    this.rbnTabDatabase.ContentPanel.Location = new System.Drawing.Point(0, 0);
                    this.rbnTabDatabase.ContentPanel.Size = new System.Drawing.Size(200, 100);
                    this.rbnTabDatabase.Name = "rbnTabDatabase";
                    this.rbnTabDatabase.StretchHorizontally = false;
                    this.rbnTabDatabase.Text = "Database";
                    // 
                    // rbnTabHelp
                    // 
                    this.rbnTabHelp.Alignment = System.Drawing.ContentAlignment.BottomLeft;
                    // 
                    // rbnTabHelp.ContentPanel
                    // 
                    this.rbnTabHelp.ContentPanel.BackColor = System.Drawing.SystemColors.ControlLightLight;
                    this.rbnTabHelp.ContentPanel.CausesValidation = true;
                    this.rbnTabHelp.ContentPanel.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
                    this.rbnTabHelp.ContentPanel.ForeColor = System.Drawing.SystemColors.ControlText;
                    this.rbnTabHelp.ContentPanel.Location = new System.Drawing.Point(0, 0);
                    this.rbnTabHelp.ContentPanel.Size = new System.Drawing.Size(200, 100);
                    this.rbnTabHelp.Name = "rbnTabHelp";
                    this.rbnTabHelp.StretchHorizontally = false;
                    this.rbnTabHelp.Text = "Help";
                    // 
                    // radStatusStrip1
                    // 
                    this.radStatusStrip1.AutoSize = true;
                    this.radStatusStrip1.LayoutStyle = Telerik.WinControls.UI.RadStatusBarLayoutStyle.Stack;
                    this.radStatusStrip1.Location = new System.Drawing.Point(0, 397);
                    this.radStatusStrip1.Name = "radStatusStrip1";
                    this.radStatusStrip1.Size = new System.Drawing.Size(474, 28);
                    this.radStatusStrip1.SizingGrip = false;
                    this.radStatusStrip1.TabIndex = 1;
                    this.radStatusStrip1.Text = "radStatusStrip1";
                    // 
                    // panel1
                    // 
                    this.panel1.Dock = System.Windows.Forms.DockStyle.Fill;
                    this.panel1.Location = new System.Drawing.Point(0, 150);
                    this.panel1.Name = "panel1";
                    this.panel1.Size = new System.Drawing.Size(474, 247);
                    this.panel1.TabIndex = 2;
                    // 
                    // DefaultWindow
                    // 
                    this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
                    this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
                    this.ClientSize = new System.Drawing.Size(474, 425);
                    this.Controls.Add(this.panel1);
                    this.Controls.Add(this.radStatusStrip1);
                    this.Controls.Add(this.radRibbonBar1);
                    this.Name = "DefaultWindow";
                    // 
                    // 
                    // 
                    this.RootElement.ApplyShapeToControl = true;
                    this.Text = "Scor";
                    this.WindowState = System.Windows.Forms.FormWindowState.Maximized;
                    this.Load += new System.EventHandler(this.DefaultWindow_Load);
                    this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.DefaultWindow_FormClosing);
                    ((System.ComponentModel.ISupportInitialize)(this.radRibbonBar1)).EndInit();
                    ((System.ComponentModel.ISupportInitialize)(this.radStatusStrip1)).EndInit();
                    ((System.ComponentModel.ISupportInitialize)(this)).EndInit();
                    this.ResumeLayout(false);
                    this.PerformLayout();

                }

                #endregion

                private Telerik.WinControls.UI.RadRibbonBar radRibbonBar1;
                private Telerik.WinControls.UI.RadStatusStrip radStatusStrip1;
                private System.Windows.Forms.Panel panel1;
                private Telerik.WinControls.UI.RibbonTab rbnTabSystem;
                private Telerik.WinControls.UI.RibbonTab rbnTabDatabase;
                private Telerik.WinControls.UI.RibbonTab rbnTabHelp;
                private Telerik.WinControls.UI.RadRibbonBarGroup radRibbonBarGroupSettings;
                private Telerik.WinControls.UI.RadButtonElement radButtonElementSettings;
                private Telerik.WinControls.UI.RadButtonElement radButtonElementFindModule;
                private Telerik.WinControls.UI.RadButtonElement radButtonElementPrinterSetup;
                private Telerik.WinControls.UI.RadButtonElement radButtonElementExit;
            }
        }
    }
}