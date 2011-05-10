namespace AtCor.Scor.Gui.Presentation
{
    partial class ReportPreview
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
            System.Windows.Forms.DataVisualization.Charting.ChartArea chartArea9 = new System.Windows.Forms.DataVisualization.Charting.ChartArea();
            System.Windows.Forms.DataVisualization.Charting.ChartArea chartArea10 = new System.Windows.Forms.DataVisualization.Charting.ChartArea();
            System.Windows.Forms.DataVisualization.Charting.ChartArea chartArea11 = new System.Windows.Forms.DataVisualization.Charting.ChartArea();
            System.Windows.Forms.DataVisualization.Charting.ChartArea chartArea12 = new System.Windows.Forms.DataVisualization.Charting.ChartArea();
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(ReportPreview));
            this.guiPicBoxReportLogo = new System.Windows.Forms.PictureBox();
            this.guichartNormalRange = new System.Windows.Forms.DataVisualization.Charting.Chart();
            this.guichartReferenceRange = new System.Windows.Forms.DataVisualization.Charting.Chart();
            this.guiradChartFemoral = new System.Windows.Forms.DataVisualization.Charting.Chart();
            this.guichartCarotid = new System.Windows.Forms.DataVisualization.Charting.Chart();
            this.guiimagelistTickCross = new System.Windows.Forms.ImageList(this.components);
            this.guilblStdDeviationImage = new System.Windows.Forms.Label();
            this.guilblFemoralImage = new System.Windows.Forms.Label();
            this.guilblCarotidImage = new System.Windows.Forms.Label();
            this.guilblBPmsg = new System.Windows.Forms.Label();
            this.guilblAgeRangeMsg = new System.Windows.Forms.Label();
            ((System.ComponentModel.ISupportInitialize)(this.guiPicBoxReportLogo)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.guichartNormalRange)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.guichartReferenceRange)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.guiradChartFemoral)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.guichartCarotid)).BeginInit();
            this.SuspendLayout();
            // 
            // guiPicBoxReportLogo
            // 
            this.guiPicBoxReportLogo.Location = new System.Drawing.Point(587, 5);
            this.guiPicBoxReportLogo.Name = "guiPicBoxReportLogo";
            this.guiPicBoxReportLogo.Size = new System.Drawing.Size(50, 50);
            this.guiPicBoxReportLogo.SizeMode = System.Windows.Forms.PictureBoxSizeMode.StretchImage;
            this.guiPicBoxReportLogo.TabIndex = 2;
            this.guiPicBoxReportLogo.TabStop = false;
            // 
            // guichartNormalRange
            // 
            this.guichartNormalRange.BackColor = System.Drawing.Color.Transparent;
            chartArea9.AxisX.Interval = 35;
            chartArea9.AxisX.IntervalOffsetType = System.Windows.Forms.DataVisualization.Charting.DateTimeIntervalType.Number;
            chartArea9.AxisX.IntervalType = System.Windows.Forms.DataVisualization.Charting.DateTimeIntervalType.Number;
            chartArea9.AxisX.IsLabelAutoFit = false;
            chartArea9.AxisX.IsStartedFromZero = false;
            chartArea9.AxisX.LabelStyle.Font = new System.Drawing.Font("Verdana", 8.25F);
            chartArea9.AxisX.MajorGrid.Enabled = false;
            chartArea9.AxisX.Maximum = 90;
            chartArea9.AxisX.Minimum = 20;
            chartArea9.AxisX.ScaleView.MinSizeType = System.Windows.Forms.DataVisualization.Charting.DateTimeIntervalType.Number;
            chartArea9.AxisX.ScaleView.SmallScrollMinSize = 0;
            chartArea9.AxisX.Title = "Age (years)";
            chartArea9.AxisY.Interval = 5;
            chartArea9.AxisY.IntervalOffsetType = System.Windows.Forms.DataVisualization.Charting.DateTimeIntervalType.Number;
            chartArea9.AxisY.IntervalType = System.Windows.Forms.DataVisualization.Charting.DateTimeIntervalType.Number;
            chartArea9.AxisY.IsLabelAutoFit = false;
            chartArea9.AxisY.IsStartedFromZero = false;
            chartArea9.AxisY.LabelStyle.Font = new System.Drawing.Font("Verdana", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            chartArea9.AxisY.MajorGrid.Enabled = false;
            chartArea9.AxisY.Maximum = 20;
            chartArea9.AxisY.Minimum = 5;
            chartArea9.AxisY.Title = "P W V m/s";
            chartArea9.BackColor = System.Drawing.Color.White;
            chartArea9.BorderDashStyle = System.Windows.Forms.DataVisualization.Charting.ChartDashStyle.Solid;
            chartArea9.InnerPlotPosition.Auto = false;
            chartArea9.InnerPlotPosition.Height = 66.13752F;
            chartArea9.InnerPlotPosition.Width = 83.42773F;
            chartArea9.InnerPlotPosition.X = 13.42227F;
            chartArea9.InnerPlotPosition.Y = 3.925F;
            chartArea9.Name = "ChartArea1";
            chartArea9.Position.Auto = false;
            chartArea9.Position.Height = 100F;
            chartArea9.Position.Width = 100F;
            this.guichartNormalRange.ChartAreas.Add(chartArea9);
            this.guichartNormalRange.Location = new System.Drawing.Point(59, 312);
            this.guichartNormalRange.Name = "guichartNormalRange";
            this.guichartNormalRange.Size = new System.Drawing.Size(306, 220);
            this.guichartNormalRange.TabIndex = 99;
            this.guichartNormalRange.TabStop = false;
            this.guichartNormalRange.Text = "chart2";
            // 
            // guichartReferenceRange
            // 
            this.guichartReferenceRange.BackColor = System.Drawing.Color.Transparent;
            chartArea10.AxisX.Interval = 35;
            chartArea10.AxisX.IntervalOffsetType = System.Windows.Forms.DataVisualization.Charting.DateTimeIntervalType.Number;
            chartArea10.AxisX.IntervalType = System.Windows.Forms.DataVisualization.Charting.DateTimeIntervalType.Number;
            chartArea10.AxisX.IsLabelAutoFit = false;
            chartArea10.AxisX.IsStartedFromZero = false;
            chartArea10.AxisX.LabelStyle.Font = new System.Drawing.Font("Verdana", 8.25F);
            chartArea10.AxisX.MajorGrid.Enabled = false;
            chartArea10.AxisX.Maximum = 90;
            chartArea10.AxisX.Minimum = 20;
            chartArea10.AxisX.ScaleView.MinSizeType = System.Windows.Forms.DataVisualization.Charting.DateTimeIntervalType.Number;
            chartArea10.AxisX.ScaleView.SmallScrollMinSize = 0;
            chartArea10.AxisX.Title = "Age (years)";
            chartArea10.AxisY.Interval = 5;
            chartArea10.AxisY.IntervalOffsetType = System.Windows.Forms.DataVisualization.Charting.DateTimeIntervalType.Number;
            chartArea10.AxisY.IntervalType = System.Windows.Forms.DataVisualization.Charting.DateTimeIntervalType.Number;
            chartArea10.AxisY.IsStartedFromZero = false;
            chartArea10.AxisY.LabelStyle.Enabled = false;
            chartArea10.AxisY.MajorGrid.Enabled = false;
            chartArea10.AxisY2.Interval = 5;
            chartArea10.AxisY2.IntervalOffsetType = System.Windows.Forms.DataVisualization.Charting.DateTimeIntervalType.Number;
            chartArea10.AxisY2.IntervalType = System.Windows.Forms.DataVisualization.Charting.DateTimeIntervalType.Number;
            chartArea10.AxisY2.IsLabelAutoFit = false;
            chartArea10.AxisY2.IsStartedFromZero = false;
            chartArea10.AxisY2.LabelStyle.Font = new System.Drawing.Font("Verdana", 8.25F);
            chartArea10.AxisY2.MajorGrid.Enabled = false;
            chartArea10.AxisY2.Maximum = 20;
            chartArea10.AxisY2.Minimum = 5;
            chartArea10.AxisY2.Title = "P W V m/s";
            chartArea10.BackColor = System.Drawing.Color.White;
            chartArea10.BorderDashStyle = System.Windows.Forms.DataVisualization.Charting.ChartDashStyle.Solid;
            chartArea10.InnerPlotPosition.Auto = false;
            chartArea10.InnerPlotPosition.Height = 66.13752F;
            chartArea10.InnerPlotPosition.Width = 83.42773F;
            chartArea10.InnerPlotPosition.X = 3.15F;
            chartArea10.InnerPlotPosition.Y = 4.725F;
            chartArea10.Name = "ChartArea1";
            chartArea10.Position.Auto = false;
            chartArea10.Position.Height = 100F;
            chartArea10.Position.Width = 100F;
            this.guichartReferenceRange.ChartAreas.Add(chartArea10);
            this.guichartReferenceRange.Enabled = false;
            this.guichartReferenceRange.Location = new System.Drawing.Point(371, 311);
            this.guichartReferenceRange.Name = "guichartReferenceRange";
            this.guichartReferenceRange.Size = new System.Drawing.Size(306, 220);
            this.guichartReferenceRange.TabIndex = 100;
            this.guichartReferenceRange.TabStop = false;
            this.guichartReferenceRange.Text = "chart1";
            // 
            // guiradChartFemoral
            // 
            this.guiradChartFemoral.BackColor = System.Drawing.Color.Transparent;
            chartArea11.AxisX.MajorGrid.Enabled = false;
            chartArea11.AxisX.MajorTickMark.Enabled = false;
            chartArea11.AxisX2.Enabled = System.Windows.Forms.DataVisualization.Charting.AxisEnabled.False;
            chartArea11.AxisY.MajorGrid.Enabled = false;
            chartArea11.AxisY.MajorTickMark.Enabled = false;
            chartArea11.AxisY2.Enabled = System.Windows.Forms.DataVisualization.Charting.AxisEnabled.False;
            chartArea11.BackColor = System.Drawing.Color.Transparent;
            chartArea11.BorderDashStyle = System.Windows.Forms.DataVisualization.Charting.ChartDashStyle.Solid;
            chartArea11.InnerPlotPosition.Auto = false;
            chartArea11.InnerPlotPosition.Height = 100F;
            chartArea11.InnerPlotPosition.Width = 100F;
            chartArea11.Name = "ChartArea1";
            chartArea11.Position.Auto = false;
            chartArea11.Position.Height = 100F;
            chartArea11.Position.Width = 100F;
            this.guiradChartFemoral.ChartAreas.Add(chartArea11);
            this.guiradChartFemoral.Location = new System.Drawing.Point(70, 744);
            this.guiradChartFemoral.Name = "guiradChartFemoral";
            this.guiradChartFemoral.Size = new System.Drawing.Size(542, 100);
            this.guiradChartFemoral.TabIndex = 107;
            this.guiradChartFemoral.TabStop = false;
            this.guiradChartFemoral.Text = "chart1";
            // 
            // guichartCarotid
            // 
            chartArea12.AxisX.MajorGrid.Enabled = false;
            chartArea12.AxisX.MajorTickMark.Enabled = false;
            chartArea12.AxisY.MajorGrid.Enabled = false;
            chartArea12.AxisY.MajorTickMark.Enabled = false;
            chartArea12.BackColor = System.Drawing.Color.White;
            chartArea12.BorderDashStyle = System.Windows.Forms.DataVisualization.Charting.ChartDashStyle.Solid;
            chartArea12.InnerPlotPosition.Auto = false;
            chartArea12.InnerPlotPosition.Height = 100F;
            chartArea12.InnerPlotPosition.Width = 100F;
            chartArea12.Name = "ChartArea1";
            chartArea12.Position.Auto = false;
            chartArea12.Position.Height = 100F;
            chartArea12.Position.Width = 100F;
            this.guichartCarotid.ChartAreas.Add(chartArea12);
            this.guichartCarotid.Location = new System.Drawing.Point(64, 604);
            this.guichartCarotid.Name = "guichartCarotid";
            this.guichartCarotid.Size = new System.Drawing.Size(542, 100);
            this.guichartCarotid.TabIndex = 108;
            this.guichartCarotid.TabStop = false;
            this.guichartCarotid.Text = "chart1";
            // 
            // guiimagelistTickCross
            // 
            this.guiimagelistTickCross.ImageStream = ((System.Windows.Forms.ImageListStreamer)(resources.GetObject("guiimagelistTickCross.ImageStream")));
            this.guiimagelistTickCross.TransparentColor = System.Drawing.Color.Transparent;
            this.guiimagelistTickCross.Images.SetKeyName(0, "cross-mark.gif");
            this.guiimagelistTickCross.Images.SetKeyName(1, "new green-tick-mark.jpg");
            // 
            // guilblStdDeviationImage
            // 
            this.guilblStdDeviationImage.Font = new System.Drawing.Font("Verdana", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.guilblStdDeviationImage.ImageList = this.guiimagelistTickCross;
            this.guilblStdDeviationImage.Location = new System.Drawing.Point(533, 228);
            this.guilblStdDeviationImage.Name = "guilblStdDeviationImage";
            this.guilblStdDeviationImage.Size = new System.Drawing.Size(21, 20);
            this.guilblStdDeviationImage.TabIndex = 112;
            // 
            // guilblFemoralImage
            // 
            this.guilblFemoralImage.Font = new System.Drawing.Font("Verdana", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.guilblFemoralImage.ImageList = this.guiimagelistTickCross;
            this.guilblFemoralImage.Location = new System.Drawing.Point(631, 769);
            this.guilblFemoralImage.Name = "guilblFemoralImage";
            this.guilblFemoralImage.Size = new System.Drawing.Size(50, 50);
            this.guilblFemoralImage.TabIndex = 113;
            // 
            // guilblCarotidImage
            // 
            this.guilblCarotidImage.Font = new System.Drawing.Font("Verdana", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.guilblCarotidImage.ImageList = this.guiimagelistTickCross;
            this.guilblCarotidImage.Location = new System.Drawing.Point(627, 629);
            this.guilblCarotidImage.Name = "guilblCarotidImage";
            this.guilblCarotidImage.Size = new System.Drawing.Size(50, 50);
            this.guilblCarotidImage.TabIndex = 114;
            // 
            // guilblBPmsg
            // 
            this.guilblBPmsg.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.guilblBPmsg.Location = new System.Drawing.Point(382, 322);
            this.guilblBPmsg.Name = "guilblBPmsg";
            this.guilblBPmsg.Size = new System.Drawing.Size(253, 147);
            this.guilblBPmsg.TabIndex = 116;
            this.guilblBPmsg.Text = "label2";
            this.guilblBPmsg.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // guilblAgeRangeMsg
            // 
            this.guilblAgeRangeMsg.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.guilblAgeRangeMsg.Location = new System.Drawing.Point(101, 322);
            this.guilblAgeRangeMsg.Name = "guilblAgeRangeMsg";
            this.guilblAgeRangeMsg.Size = new System.Drawing.Size(253, 147);
            this.guilblAgeRangeMsg.TabIndex = 117;
            this.guilblAgeRangeMsg.Text = "label2";
            this.guilblAgeRangeMsg.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // ReportPreview
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.AutoScroll = true;
            this.BackColor = System.Drawing.Color.White;
            this.ClientSize = new System.Drawing.Size(732, 742);
            this.Controls.Add(this.guilblAgeRangeMsg);
            this.Controls.Add(this.guilblBPmsg);
            this.Controls.Add(this.guilblCarotidImage);
            this.Controls.Add(this.guilblFemoralImage);
            this.Controls.Add(this.guilblStdDeviationImage);
            this.Controls.Add(this.guichartCarotid);
            this.Controls.Add(this.guiradChartFemoral);
            this.Controls.Add(this.guichartReferenceRange);
            this.Controls.Add(this.guichartNormalRange);
            this.Controls.Add(this.guiPicBoxReportLogo);
            this.Name = "ReportPreview";
            this.Text = "ReportPreview";
            this.Load += new System.EventHandler(this.ReportPreview_Load);
            ((System.ComponentModel.ISupportInitialize)(this.guiPicBoxReportLogo)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.guichartNormalRange)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.guichartReferenceRange)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.guiradChartFemoral)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.guichartCarotid)).EndInit();
            this.ResumeLayout(false);

        }

        #endregion

        public System.Windows.Forms.PictureBox guiPicBoxReportLogo;
        public System.Windows.Forms.DataVisualization.Charting.Chart guichartNormalRange;
        public System.Windows.Forms.Label guilblBPmsg;
        public System.Windows.Forms.DataVisualization.Charting.Chart guichartReferenceRange;
        public System.Windows.Forms.DataVisualization.Charting.Chart guiradChartFemoral;
        public System.Windows.Forms.DataVisualization.Charting.Chart guichartCarotid;
        public System.Windows.Forms.ImageList guiimagelistTickCross;
        public System.Windows.Forms.Label guilblStdDeviationImage;
        public System.Windows.Forms.Label guilblFemoralImage;
        public System.Windows.Forms.Label guilblCarotidImage;
        public System.Windows.Forms.Label guilblAgeRangeMsg;
    }
}