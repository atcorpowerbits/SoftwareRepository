namespace AtCor.Scor.Gui.Presentation
{
    partial class Capture
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
            //if (disposing && (components != null))
            //{
            //    components.Dispose();
            //}
            //base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.components = new System.ComponentModel.Container();
            System.Windows.Forms.DataVisualization.Charting.ChartArea chartArea1 = new System.Windows.Forms.DataVisualization.Charting.ChartArea();
            System.Windows.Forms.DataVisualization.Charting.ChartArea chartArea2 = new System.Windows.Forms.DataVisualization.Charting.ChartArea();
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(Capture));
            this.chartTonometer = new System.Windows.Forms.DataVisualization.Charting.Chart();
            this.guiradlblCarotidTonometer = new Telerik.WinControls.UI.RadLabel();
            this.guichartFemoralCuff = new System.Windows.Forms.DataVisualization.Charting.Chart();
            this.radlblcuffQuality = new Telerik.WinControls.UI.RadLabel();
            this.guiradlblFemoralCuff = new Telerik.WinControls.UI.RadLabel();
            this.tableLayoutPanel1 = new System.Windows.Forms.TableLayoutPanel();
            this.radbtnTick = new Telerik.WinControls.UI.RadButton();
            this.radbtnCross = new Telerik.WinControls.UI.RadButton();
            this.guiradprgbarTimeToInflatioDeflation = new Telerik.WinControls.UI.RadProgressBar();
            this.radlblTimeStatus = new Telerik.WinControls.UI.RadLabel();
            this.timer1 = new System.Windows.Forms.Timer(this.components);
            this.tmrInflationTimer = new System.Windows.Forms.Timer(this.components);
            this.tmrDeflationTimer = new System.Windows.Forms.Timer(this.components);
            this.TenSecWaitTmr = new System.Windows.Forms.Timer(this.components);
            this.radProgressBarQualityIndicator = new Telerik.WinControls.UI.RadProgressBar();
            this.pictureBox1 = new System.Windows.Forms.PictureBox();
            ((System.ComponentModel.ISupportInitialize)(this.chartTonometer)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.guiradlblCarotidTonometer)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.guichartFemoralCuff)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.radlblcuffQuality)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.guiradlblFemoralCuff)).BeginInit();
            this.tableLayoutPanel1.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.radbtnTick)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.radbtnCross)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.guiradprgbarTimeToInflatioDeflation)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.radlblTimeStatus)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.radProgressBarQualityIndicator)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this)).BeginInit();
            this.SuspendLayout();
            // 
            // chartTonometer
            // 
            this.chartTonometer.BackColor = System.Drawing.Color.Black;
            chartArea1.AxisX.MajorGrid.Enabled = false;
            chartArea1.AxisY.MajorGrid.Enabled = false;
            chartArea1.AxisY.MajorGrid.LineColor = System.Drawing.Color.Yellow;
            chartArea1.AxisY.MinorGrid.LineColor = System.Drawing.Color.Cyan;
            chartArea1.BackColor = System.Drawing.Color.Black;
            chartArea1.InnerPlotPosition.Auto = false;
            chartArea1.InnerPlotPosition.Height = 100F;
            chartArea1.InnerPlotPosition.Width = 100F;
            chartArea1.Name = "ChartArea1";
            chartArea1.Position.Auto = false;
            chartArea1.Position.Height = 100F;
            chartArea1.Position.Width = 100F;
            this.chartTonometer.ChartAreas.Add(chartArea1);
            this.chartTonometer.Location = new System.Drawing.Point(4, 30);
            this.chartTonometer.Name = "chartTonometer";
            this.chartTonometer.Size = new System.Drawing.Size(939, 297);
            this.chartTonometer.TabIndex = 14;
            this.chartTonometer.Text = "Carotid Tonometer";
            // 
            // guiradlblCarotidTonometer
            // 
            this.guiradlblCarotidTonometer.Font = new System.Drawing.Font("Verdana", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.guiradlblCarotidTonometer.ForeColor = System.Drawing.Color.Black;
            this.guiradlblCarotidTonometer.Location = new System.Drawing.Point(440, 5);
            this.guiradlblCarotidTonometer.Name = "guiradlblCarotidTonometer";
            // 
            // 
            // 
            this.guiradlblCarotidTonometer.RootElement.ForeColor = System.Drawing.Color.Black;
            this.guiradlblCarotidTonometer.Size = new System.Drawing.Size(113, 17);
            this.guiradlblCarotidTonometer.TabIndex = 12;
            this.guiradlblCarotidTonometer.Text = "Carotid Tonometer";
            // 
            // guichartFemoralCuff
            // 
            this.guichartFemoralCuff.BackColor = System.Drawing.Color.Black;
            chartArea2.BackColor = System.Drawing.Color.Black;
            chartArea2.InnerPlotPosition.Auto = false;
            chartArea2.InnerPlotPosition.Height = 100F;
            chartArea2.InnerPlotPosition.Width = 100F;
            chartArea2.Name = "ChartArea1";
            chartArea2.Position.Auto = false;
            chartArea2.Position.Height = 100F;
            chartArea2.Position.Width = 100F;
            this.guichartFemoralCuff.ChartAreas.Add(chartArea2);
            this.guichartFemoralCuff.Location = new System.Drawing.Point(4, 356);
            this.guichartFemoralCuff.Name = "guichartFemoralCuff";
            this.guichartFemoralCuff.Size = new System.Drawing.Size(939, 186);
            this.guichartFemoralCuff.TabIndex = 17;
            this.guichartFemoralCuff.Text = "chart1";
            // 
            // radlblcuffQuality
            // 
            this.radlblcuffQuality.AutoSize = false;
            this.radlblcuffQuality.Image = ((System.Drawing.Image)(resources.GetObject("radlblcuffQuality.Image")));
            this.radlblcuffQuality.Location = new System.Drawing.Point(949, 356);
            this.radlblcuffQuality.Name = "radlblcuffQuality";
            this.radlblcuffQuality.Size = new System.Drawing.Size(50, 50);
            this.radlblcuffQuality.TabIndex = 16;
            this.radlblcuffQuality.Visible = false;
            // 
            // guiradlblFemoralCuff
            // 
            this.guiradlblFemoralCuff.Font = new System.Drawing.Font("Verdana", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.guiradlblFemoralCuff.Location = new System.Drawing.Point(463, 333);
            this.guiradlblFemoralCuff.Name = "guiradlblFemoralCuff";
            this.guiradlblFemoralCuff.Size = new System.Drawing.Size(79, 17);
            this.guiradlblFemoralCuff.TabIndex = 15;
            this.guiradlblFemoralCuff.Text = "Femoral Cuff";
            // 
            // tableLayoutPanel1
            // 
            this.tableLayoutPanel1.ColumnCount = 4;
            this.tableLayoutPanel1.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 50F));
            this.tableLayoutPanel1.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 50F));
            this.tableLayoutPanel1.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Absolute, 95F));
            this.tableLayoutPanel1.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Absolute, 92F));
            this.tableLayoutPanel1.Controls.Add(this.radbtnTick, 2, 0);
            this.tableLayoutPanel1.Controls.Add(this.radbtnCross, 3, 0);
            this.tableLayoutPanel1.Controls.Add(this.guiradprgbarTimeToInflatioDeflation, 0, 0);
            this.tableLayoutPanel1.Controls.Add(this.radlblTimeStatus, 1, 0);
            this.tableLayoutPanel1.Location = new System.Drawing.Point(-3, 546);
            this.tableLayoutPanel1.Name = "tableLayoutPanel1";
            this.tableLayoutPanel1.RowCount = 1;
            this.tableLayoutPanel1.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 50F));
            this.tableLayoutPanel1.Size = new System.Drawing.Size(950, 31);
            this.tableLayoutPanel1.TabIndex = 18;
            // 
            // radbtnTick
            // 
            this.radbtnTick.Anchor = System.Windows.Forms.AnchorStyles.Bottom;
            this.radbtnTick.Enabled = false;
            this.radbtnTick.Font = new System.Drawing.Font("Verdana", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.radbtnTick.ImageAlignment = System.Drawing.ContentAlignment.MiddleCenter;
            this.radbtnTick.Location = new System.Drawing.Point(769, 3);
            this.radbtnTick.Name = "radbtnTick";
            this.radbtnTick.Size = new System.Drawing.Size(80, 25);
            this.radbtnTick.TabIndex = 6;
            this.radbtnTick.Text = "Ok";
            this.radbtnTick.Click += new System.EventHandler(this.radbtnTick_Click);
            ((Telerik.WinControls.UI.RadButtonElement)(this.radbtnTick.GetChildAt(0))).Image = null;
            ((Telerik.WinControls.UI.RadButtonElement)(this.radbtnTick.GetChildAt(0))).ImageAlignment = System.Drawing.ContentAlignment.MiddleCenter;
            ((Telerik.WinControls.UI.RadButtonElement)(this.radbtnTick.GetChildAt(0))).Text = "Ok";
            ((Telerik.WinControls.Primitives.FillPrimitive)(this.radbtnTick.GetChildAt(0).GetChildAt(0))).BackColor3 = System.Drawing.Color.FromArgb(((int)(((byte)(121)))), ((int)(((byte)(171)))), ((int)(((byte)(231)))));
            ((Telerik.WinControls.Primitives.FillPrimitive)(this.radbtnTick.GetChildAt(0).GetChildAt(0))).BackColor4 = System.Drawing.Color.FromArgb(((int)(((byte)(233)))), ((int)(((byte)(241)))), ((int)(((byte)(252)))));
            // 
            // radbtnCross
            // 
            this.radbtnCross.Anchor = System.Windows.Forms.AnchorStyles.Bottom;
            this.radbtnCross.Font = new System.Drawing.Font("Verdana", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.radbtnCross.ImageAlignment = System.Drawing.ContentAlignment.MiddleCenter;
            this.radbtnCross.Location = new System.Drawing.Point(863, 3);
            this.radbtnCross.Name = "radbtnCross";
            this.radbtnCross.Size = new System.Drawing.Size(80, 25);
            this.radbtnCross.TabIndex = 7;
            this.radbtnCross.Text = "Cancel";
            this.radbtnCross.Click += new System.EventHandler(this.radbtnCross_Click);
            ((Telerik.WinControls.UI.RadButtonElement)(this.radbtnCross.GetChildAt(0))).Image = null;
            ((Telerik.WinControls.UI.RadButtonElement)(this.radbtnCross.GetChildAt(0))).ImageAlignment = System.Drawing.ContentAlignment.MiddleCenter;
            ((Telerik.WinControls.UI.RadButtonElement)(this.radbtnCross.GetChildAt(0))).Text = "Cancel";
            ((Telerik.WinControls.Primitives.FillPrimitive)(this.radbtnCross.GetChildAt(0).GetChildAt(0))).BackColor3 = System.Drawing.Color.FromArgb(((int)(((byte)(121)))), ((int)(((byte)(171)))), ((int)(((byte)(231)))));
            // 
            // guiradprgbarTimeToInflatioDeflation
            // 
            this.guiradprgbarTimeToInflatioDeflation.Dash = false;
            this.guiradprgbarTimeToInflatioDeflation.ForeColor = System.Drawing.Color.Black;
            this.guiradprgbarTimeToInflatioDeflation.Location = new System.Drawing.Point(3, 3);
            this.guiradprgbarTimeToInflatioDeflation.Name = "guiradprgbarTimeToInflatioDeflation";
            // 
            // 
            // 
            this.guiradprgbarTimeToInflatioDeflation.RootElement.ForeColor = System.Drawing.Color.Black;
            this.guiradprgbarTimeToInflatioDeflation.ShowProgressIndicators = true;
            this.guiradprgbarTimeToInflatioDeflation.Size = new System.Drawing.Size(370, 25);
            this.guiradprgbarTimeToInflatioDeflation.TabIndex = 8;
            this.guiradprgbarTimeToInflatioDeflation.Text = "0%";
            this.guiradprgbarTimeToInflatioDeflation.TextAlignment = System.Drawing.ContentAlignment.MiddleCenter;
            ((Telerik.WinControls.UI.RadProgressBarElement)(this.guiradprgbarTimeToInflatioDeflation.GetChildAt(0))).ShowProgressIndicator = true;
            ((Telerik.WinControls.UI.RadProgressBarElement)(this.guiradprgbarTimeToInflatioDeflation.GetChildAt(0))).Dash = false;
            ((Telerik.WinControls.UI.RadProgressBarElement)(this.guiradprgbarTimeToInflatioDeflation.GetChildAt(0))).Value1 = 0;
            ((Telerik.WinControls.UI.RadProgressBarElement)(this.guiradprgbarTimeToInflatioDeflation.GetChildAt(0))).SeparatorColor1 = System.Drawing.SystemColors.ControlLightLight;
            ((Telerik.WinControls.UI.RadProgressBarElement)(this.guiradprgbarTimeToInflatioDeflation.GetChildAt(0))).Text = "0%";
            ((Telerik.WinControls.Primitives.FillPrimitive)(this.guiradprgbarTimeToInflatioDeflation.GetChildAt(0).GetChildAt(0))).BackColor2 = System.Drawing.SystemColors.ControlLight;
            ((Telerik.WinControls.Primitives.FillPrimitive)(this.guiradprgbarTimeToInflatioDeflation.GetChildAt(0).GetChildAt(0))).BackColor3 = System.Drawing.Color.FromArgb(((int)(((byte)(233)))), ((int)(((byte)(241)))), ((int)(((byte)(252)))));
            ((Telerik.WinControls.Primitives.FillPrimitive)(this.guiradprgbarTimeToInflatioDeflation.GetChildAt(0).GetChildAt(0))).BackColor4 = System.Drawing.SystemColors.ControlLightLight;
            ((Telerik.WinControls.Primitives.FillPrimitive)(this.guiradprgbarTimeToInflatioDeflation.GetChildAt(0).GetChildAt(0))).NumberOfColors = 2;
            ((Telerik.WinControls.Primitives.FillPrimitive)(this.guiradprgbarTimeToInflatioDeflation.GetChildAt(0).GetChildAt(0))).GradientPercentage = 0.1F;
            ((Telerik.WinControls.Primitives.FillPrimitive)(this.guiradprgbarTimeToInflatioDeflation.GetChildAt(0).GetChildAt(0))).GradientPercentage2 = 0.1F;
            ((Telerik.WinControls.Primitives.FillPrimitive)(this.guiradprgbarTimeToInflatioDeflation.GetChildAt(0).GetChildAt(0))).BackColor = System.Drawing.SystemColors.ControlLightLight;
            ((Telerik.WinControls.Primitives.FillPrimitive)(this.guiradprgbarTimeToInflatioDeflation.GetChildAt(0).GetChildAt(0))).Font = new System.Drawing.Font("Verdana", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            ((Telerik.WinControls.Primitives.ProgressBarPrimitive)(this.guiradprgbarTimeToInflatioDeflation.GetChildAt(0).GetChildAt(1))).BackColor2 = System.Drawing.Color.FromArgb(((int)(((byte)(61)))), ((int)(((byte)(139)))), ((int)(((byte)(232)))));
            ((Telerik.WinControls.Primitives.ProgressBarPrimitive)(this.guiradprgbarTimeToInflatioDeflation.GetChildAt(0).GetChildAt(1))).BackColor3 = System.Drawing.Color.FromArgb(((int)(((byte)(61)))), ((int)(((byte)(139)))), ((int)(((byte)(232)))));
            ((Telerik.WinControls.Primitives.ProgressBarPrimitive)(this.guiradprgbarTimeToInflatioDeflation.GetChildAt(0).GetChildAt(1))).BackColor4 = System.Drawing.Color.FromArgb(((int)(((byte)(233)))), ((int)(((byte)(241)))), ((int)(((byte)(252)))));
            ((Telerik.WinControls.Primitives.ProgressBarPrimitive)(this.guiradprgbarTimeToInflatioDeflation.GetChildAt(0).GetChildAt(1))).GradientStyle = Telerik.WinControls.GradientStyles.Linear;
            ((Telerik.WinControls.Primitives.ProgressBarPrimitive)(this.guiradprgbarTimeToInflatioDeflation.GetChildAt(0).GetChildAt(1))).GradientPercentage = 0.5F;
            ((Telerik.WinControls.Primitives.ProgressBarPrimitive)(this.guiradprgbarTimeToInflatioDeflation.GetChildAt(0).GetChildAt(1))).GradientPercentage2 = 0.5F;
            ((Telerik.WinControls.Primitives.ProgressBarPrimitive)(this.guiradprgbarTimeToInflatioDeflation.GetChildAt(0).GetChildAt(1))).ForeColor = System.Drawing.SystemColors.ControlDark;
            ((Telerik.WinControls.Primitives.ProgressBarPrimitive)(this.guiradprgbarTimeToInflatioDeflation.GetChildAt(0).GetChildAt(1))).BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(233)))), ((int)(((byte)(241)))), ((int)(((byte)(252)))));
            ((Telerik.WinControls.Primitives.BorderPrimitive)(this.guiradprgbarTimeToInflatioDeflation.GetChildAt(0).GetChildAt(3))).LeftColor = System.Drawing.SystemColors.ControlLight;
            ((Telerik.WinControls.Primitives.BorderPrimitive)(this.guiradprgbarTimeToInflatioDeflation.GetChildAt(0).GetChildAt(3))).TopColor = System.Drawing.SystemColors.ControlLight;
            ((Telerik.WinControls.Primitives.BorderPrimitive)(this.guiradprgbarTimeToInflatioDeflation.GetChildAt(0).GetChildAt(3))).RightColor = System.Drawing.SystemColors.ControlLight;
            ((Telerik.WinControls.Primitives.BorderPrimitive)(this.guiradprgbarTimeToInflatioDeflation.GetChildAt(0).GetChildAt(3))).BottomColor = System.Drawing.SystemColors.ControlLight;
            ((Telerik.WinControls.Primitives.BorderPrimitive)(this.guiradprgbarTimeToInflatioDeflation.GetChildAt(0).GetChildAt(3))).ForeColor2 = System.Drawing.SystemColors.ControlLight;
            ((Telerik.WinControls.Primitives.BorderPrimitive)(this.guiradprgbarTimeToInflatioDeflation.GetChildAt(0).GetChildAt(3))).ForeColor3 = System.Drawing.SystemColors.ControlLight;
            ((Telerik.WinControls.Primitives.BorderPrimitive)(this.guiradprgbarTimeToInflatioDeflation.GetChildAt(0).GetChildAt(3))).ForeColor4 = System.Drawing.SystemColors.ControlLight;
            ((Telerik.WinControls.Primitives.BorderPrimitive)(this.guiradprgbarTimeToInflatioDeflation.GetChildAt(0).GetChildAt(3))).ForeColor = System.Drawing.SystemColors.ControlDark;
            // 
            // radlblTimeStatus
            // 
            this.radlblTimeStatus.Anchor = System.Windows.Forms.AnchorStyles.Left;
            this.radlblTimeStatus.Font = new System.Drawing.Font("Verdana", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.radlblTimeStatus.Location = new System.Drawing.Point(384, 7);
            this.radlblTimeStatus.Name = "radlblTimeStatus";
            this.radlblTimeStatus.Size = new System.Drawing.Size(135, 17);
            this.radlblTimeStatus.TabIndex = 5;
            this.radlblTimeStatus.Text = "Time to Deflation 1:30";
            this.radlblTimeStatus.TextAlignment = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // timer1
            // 
            this.timer1.Interval = 125;
            this.timer1.Tick += new System.EventHandler(this.timer1_Tick);
            // 
            // tmrInflationTimer
            // 
            this.tmrInflationTimer.Interval = 1000;
            this.tmrInflationTimer.Tick += new System.EventHandler(this.tmrInflationTimer_Tick);
            // 
            // tmrDeflationTimer
            // 
            this.tmrDeflationTimer.Interval = 1000;
            this.tmrDeflationTimer.Tick += new System.EventHandler(this.tmrDeflationTimer_Tick);
            // 
            // TenSecWaitTmr
            // 
            this.TenSecWaitTmr.Interval = 10000;
            this.TenSecWaitTmr.Tick += new System.EventHandler(this.TenSecWaitTmr_Tick);
            // 
            // radProgressBarQualityIndicator
            // 
            this.radProgressBarQualityIndicator.Dash = false;
            this.radProgressBarQualityIndicator.ForeColor = System.Drawing.Color.Black;
            this.radProgressBarQualityIndicator.Location = new System.Drawing.Point(951, 30);
            this.radProgressBarQualityIndicator.Name = "radProgressBarQualityIndicator";
            this.radProgressBarQualityIndicator.ProgressOrientation = Telerik.WinControls.ProgressOrientation.Bottom;
            // 
            // 
            // 
            this.radProgressBarQualityIndicator.RootElement.ForeColor = System.Drawing.Color.Black;
            this.radProgressBarQualityIndicator.ShowProgressIndicators = true;
            this.radProgressBarQualityIndicator.Size = new System.Drawing.Size(29, 297);
            this.radProgressBarQualityIndicator.SweepAngle = 90;
            this.radProgressBarQualityIndicator.TabIndex = 21;
            this.radProgressBarQualityIndicator.Text = "0%";
            this.radProgressBarQualityIndicator.TextAlignment = System.Drawing.ContentAlignment.MiddleCenter;
            ((Telerik.WinControls.UI.RadProgressBarElement)(this.radProgressBarQualityIndicator.GetChildAt(0))).Orientation = Telerik.WinControls.ProgressOrientation.Bottom;
            ((Telerik.WinControls.UI.RadProgressBarElement)(this.radProgressBarQualityIndicator.GetChildAt(0))).ShowProgressIndicator = true;
            ((Telerik.WinControls.UI.RadProgressBarElement)(this.radProgressBarQualityIndicator.GetChildAt(0))).SweepAngle = 90;
            ((Telerik.WinControls.UI.RadProgressBarElement)(this.radProgressBarQualityIndicator.GetChildAt(0))).Dash = false;
            ((Telerik.WinControls.UI.RadProgressBarElement)(this.radProgressBarQualityIndicator.GetChildAt(0))).Value1 = 0;
            ((Telerik.WinControls.UI.RadProgressBarElement)(this.radProgressBarQualityIndicator.GetChildAt(0))).SeparatorColor1 = System.Drawing.SystemColors.ControlLightLight;
            ((Telerik.WinControls.UI.RadProgressBarElement)(this.radProgressBarQualityIndicator.GetChildAt(0))).Text = "0%";
            ((Telerik.WinControls.Primitives.FillPrimitive)(this.radProgressBarQualityIndicator.GetChildAt(0).GetChildAt(0))).BackColor2 = System.Drawing.SystemColors.ControlLight;
            ((Telerik.WinControls.Primitives.FillPrimitive)(this.radProgressBarQualityIndicator.GetChildAt(0).GetChildAt(0))).BackColor3 = System.Drawing.Color.FromArgb(((int)(((byte)(233)))), ((int)(((byte)(241)))), ((int)(((byte)(252)))));
            ((Telerik.WinControls.Primitives.FillPrimitive)(this.radProgressBarQualityIndicator.GetChildAt(0).GetChildAt(0))).BackColor4 = System.Drawing.SystemColors.ControlLightLight;
            ((Telerik.WinControls.Primitives.FillPrimitive)(this.radProgressBarQualityIndicator.GetChildAt(0).GetChildAt(0))).NumberOfColors = 2;
            ((Telerik.WinControls.Primitives.FillPrimitive)(this.radProgressBarQualityIndicator.GetChildAt(0).GetChildAt(0))).GradientPercentage = 0.1F;
            ((Telerik.WinControls.Primitives.FillPrimitive)(this.radProgressBarQualityIndicator.GetChildAt(0).GetChildAt(0))).GradientPercentage2 = 0.1F;
            ((Telerik.WinControls.Primitives.FillPrimitive)(this.radProgressBarQualityIndicator.GetChildAt(0).GetChildAt(0))).BackColor = System.Drawing.SystemColors.ControlLightLight;
            ((Telerik.WinControls.Primitives.FillPrimitive)(this.radProgressBarQualityIndicator.GetChildAt(0).GetChildAt(0))).Font = new System.Drawing.Font("Verdana", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            ((Telerik.WinControls.Primitives.ProgressBarPrimitive)(this.radProgressBarQualityIndicator.GetChildAt(0).GetChildAt(1))).BackColor2 = System.Drawing.Color.FromArgb(((int)(((byte)(61)))), ((int)(((byte)(139)))), ((int)(((byte)(232)))));
            ((Telerik.WinControls.Primitives.ProgressBarPrimitive)(this.radProgressBarQualityIndicator.GetChildAt(0).GetChildAt(1))).BackColor3 = System.Drawing.Color.FromArgb(((int)(((byte)(61)))), ((int)(((byte)(139)))), ((int)(((byte)(232)))));
            ((Telerik.WinControls.Primitives.ProgressBarPrimitive)(this.radProgressBarQualityIndicator.GetChildAt(0).GetChildAt(1))).BackColor4 = System.Drawing.Color.FromArgb(((int)(((byte)(233)))), ((int)(((byte)(241)))), ((int)(((byte)(252)))));
            ((Telerik.WinControls.Primitives.ProgressBarPrimitive)(this.radProgressBarQualityIndicator.GetChildAt(0).GetChildAt(1))).GradientStyle = Telerik.WinControls.GradientStyles.Linear;
            ((Telerik.WinControls.Primitives.ProgressBarPrimitive)(this.radProgressBarQualityIndicator.GetChildAt(0).GetChildAt(1))).GradientPercentage = 0.5F;
            ((Telerik.WinControls.Primitives.ProgressBarPrimitive)(this.radProgressBarQualityIndicator.GetChildAt(0).GetChildAt(1))).GradientPercentage2 = 0.5F;
            ((Telerik.WinControls.Primitives.ProgressBarPrimitive)(this.radProgressBarQualityIndicator.GetChildAt(0).GetChildAt(1))).ForeColor = System.Drawing.SystemColors.ControlDark;
            ((Telerik.WinControls.Primitives.ProgressBarPrimitive)(this.radProgressBarQualityIndicator.GetChildAt(0).GetChildAt(1))).BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(233)))), ((int)(((byte)(241)))), ((int)(((byte)(252)))));
            ((Telerik.WinControls.Primitives.BorderPrimitive)(this.radProgressBarQualityIndicator.GetChildAt(0).GetChildAt(3))).LeftColor = System.Drawing.SystemColors.ControlLight;
            ((Telerik.WinControls.Primitives.BorderPrimitive)(this.radProgressBarQualityIndicator.GetChildAt(0).GetChildAt(3))).TopColor = System.Drawing.SystemColors.ControlLight;
            ((Telerik.WinControls.Primitives.BorderPrimitive)(this.radProgressBarQualityIndicator.GetChildAt(0).GetChildAt(3))).RightColor = System.Drawing.SystemColors.ControlLight;
            ((Telerik.WinControls.Primitives.BorderPrimitive)(this.radProgressBarQualityIndicator.GetChildAt(0).GetChildAt(3))).BottomColor = System.Drawing.SystemColors.ControlLight;
            ((Telerik.WinControls.Primitives.BorderPrimitive)(this.radProgressBarQualityIndicator.GetChildAt(0).GetChildAt(3))).ForeColor2 = System.Drawing.SystemColors.ControlLight;
            ((Telerik.WinControls.Primitives.BorderPrimitive)(this.radProgressBarQualityIndicator.GetChildAt(0).GetChildAt(3))).ForeColor3 = System.Drawing.SystemColors.ControlLight;
            ((Telerik.WinControls.Primitives.BorderPrimitive)(this.radProgressBarQualityIndicator.GetChildAt(0).GetChildAt(3))).ForeColor4 = System.Drawing.SystemColors.ControlLight;
            ((Telerik.WinControls.Primitives.BorderPrimitive)(this.radProgressBarQualityIndicator.GetChildAt(0).GetChildAt(3))).ForeColor = System.Drawing.SystemColors.ControlDark;
            // 
            // pictureBox1
            // 
            this.pictureBox1.Location = new System.Drawing.Point(945, 424);
            this.pictureBox1.Name = "pictureBox1";
            this.pictureBox1.Size = new System.Drawing.Size(50, 50);
            this.pictureBox1.SizeMode = System.Windows.Forms.PictureBoxSizeMode.StretchImage;
            this.pictureBox1.TabIndex = 22;
            this.pictureBox1.TabStop = false;
            // 
            // Capture
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(992, 599);
            this.Controls.Add(this.pictureBox1);
            this.Controls.Add(this.radProgressBarQualityIndicator);
            this.Controls.Add(this.tableLayoutPanel1);
            this.Controls.Add(this.guichartFemoralCuff);
            this.Controls.Add(this.radlblcuffQuality);
            this.Controls.Add(this.guiradlblFemoralCuff);
            this.Controls.Add(this.chartTonometer);
            this.Controls.Add(this.guiradlblCarotidTonometer);
            this.Font = new System.Drawing.Font("Verdana", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.KeyPreview = true;
            this.Name = "Capture";
            // 
            // 
            // 
            this.RootElement.ApplyShapeToControl = true;
            this.Text = "  ";
            this.ThemeName = "ControlDefault";
            this.Load += new System.EventHandler(this.Capture_Load);
            this.KeyDown += new System.Windows.Forms.KeyEventHandler(this.Capture_KeyDown);
            ((System.ComponentModel.ISupportInitialize)(this.chartTonometer)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.guiradlblCarotidTonometer)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.guichartFemoralCuff)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.radlblcuffQuality)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.guiradlblFemoralCuff)).EndInit();
            this.tableLayoutPanel1.ResumeLayout(false);
            this.tableLayoutPanel1.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.radbtnTick)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.radbtnCross)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.guiradprgbarTimeToInflatioDeflation)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.radlblTimeStatus)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.radProgressBarQualityIndicator)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.DataVisualization.Charting.Chart chartTonometer;
        private Telerik.WinControls.UI.RadLabel guiradlblCarotidTonometer;
        private System.Windows.Forms.DataVisualization.Charting.Chart guichartFemoralCuff;
        private Telerik.WinControls.UI.RadLabel radlblcuffQuality;
        private Telerik.WinControls.UI.RadLabel guiradlblFemoralCuff;
        private System.Windows.Forms.TableLayoutPanel tableLayoutPanel1;
        private Telerik.WinControls.UI.RadLabel radlblTimeStatus;
        private Telerik.WinControls.UI.RadButton radbtnTick;
        private Telerik.WinControls.UI.RadButton radbtnCross;
        private Telerik.WinControls.UI.RadProgressBar guiradprgbarTimeToInflatioDeflation;
        private System.Windows.Forms.Timer timer1;
        private System.Windows.Forms.Timer tmrInflationTimer;
        private System.Windows.Forms.Timer tmrDeflationTimer;
        private System.Windows.Forms.Timer TenSecWaitTmr;
        private Telerik.WinControls.UI.RadProgressBar radProgressBarQualityIndicator;
        private System.Windows.Forms.PictureBox pictureBox1;
    }
}

