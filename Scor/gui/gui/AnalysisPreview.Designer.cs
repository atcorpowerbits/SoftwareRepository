namespace AtCor.Scor.Gui.Presentation
{
    partial class AnaylsisPreview
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
            System.Windows.Forms.DataVisualization.Charting.ChartArea chartArea1 = new System.Windows.Forms.DataVisualization.Charting.ChartArea();
            System.Windows.Forms.DataVisualization.Charting.Series series1 = new System.Windows.Forms.DataVisualization.Charting.Series();
            System.Windows.Forms.DataVisualization.Charting.ChartArea chartArea2 = new System.Windows.Forms.DataVisualization.Charting.ChartArea();
            System.Windows.Forms.DataVisualization.Charting.Series series2 = new System.Windows.Forms.DataVisualization.Charting.Series();
            System.Windows.Forms.DataVisualization.Charting.DataPoint dataPoint1 = new System.Windows.Forms.DataVisualization.Charting.DataPoint(1, 10);
            System.Windows.Forms.DataVisualization.Charting.DataPoint dataPoint2 = new System.Windows.Forms.DataVisualization.Charting.DataPoint(2, 20);
            System.Windows.Forms.DataVisualization.Charting.DataPoint dataPoint3 = new System.Windows.Forms.DataVisualization.Charting.DataPoint(3, 40);
            System.Windows.Forms.DataVisualization.Charting.DataPoint dataPoint4 = new System.Windows.Forms.DataVisualization.Charting.DataPoint(5, 50);
            System.Windows.Forms.DataVisualization.Charting.Title title1 = new System.Windows.Forms.DataVisualization.Charting.Title();
            this.guiradpnlAnalysis = new Telerik.WinControls.UI.RadPanel();
            this.guiradchartPulseWaveVelocity = new System.Windows.Forms.DataVisualization.Charting.Chart();
            this.guiradchartHeartRate = new System.Windows.Forms.DataVisualization.Charting.Chart();
            this.guiPicBoxReportLogo = new System.Windows.Forms.PictureBox();
            ((System.ComponentModel.ISupportInitialize)(this.guiradpnlAnalysis)).BeginInit();
            this.guiradpnlAnalysis.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.guiradchartPulseWaveVelocity)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.guiradchartHeartRate)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.guiPicBoxReportLogo)).BeginInit();
            this.SuspendLayout();
            // 
            // guiradpnlAnalysis
            // 
            this.guiradpnlAnalysis.Controls.Add(this.guiradchartPulseWaveVelocity);
            this.guiradpnlAnalysis.Controls.Add(this.guiradchartHeartRate);
            this.guiradpnlAnalysis.Location = new System.Drawing.Point(39, 130);
            this.guiradpnlAnalysis.Name = "guiradpnlAnalysis";
            this.guiradpnlAnalysis.Size = new System.Drawing.Size(655, 425);
            this.guiradpnlAnalysis.TabIndex = 103;
            // 
            // guiradchartPulseWaveVelocity
            // 
            this.guiradchartPulseWaveVelocity.BackColor = System.Drawing.Color.Transparent;
            chartArea1.AlignmentStyle = System.Windows.Forms.DataVisualization.Charting.AreaAlignmentStyles.PlotPosition;
            chartArea1.AxisX.IntervalOffset = 1;
            chartArea1.AxisX.IntervalType = System.Windows.Forms.DataVisualization.Charting.DateTimeIntervalType.Number;
            chartArea1.AxisX.IsStartedFromZero = false;
            chartArea1.AxisX.LabelAutoFitStyle = ((System.Windows.Forms.DataVisualization.Charting.LabelAutoFitStyles)((((System.Windows.Forms.DataVisualization.Charting.LabelAutoFitStyles.IncreaseFont | System.Windows.Forms.DataVisualization.Charting.LabelAutoFitStyles.DecreaseFont)
                        | System.Windows.Forms.DataVisualization.Charting.LabelAutoFitStyles.LabelsAngleStep90)
                        | System.Windows.Forms.DataVisualization.Charting.LabelAutoFitStyles.WordWrap)));
            chartArea1.AxisX.MajorGrid.Enabled = false;
            chartArea1.AxisX.ScaleBreakStyle.BreakLineStyle = System.Windows.Forms.DataVisualization.Charting.BreakLineStyle.None;
            chartArea1.AxisX.ScaleBreakStyle.StartFromZero = System.Windows.Forms.DataVisualization.Charting.StartFromZero.No;
            chartArea1.AxisY.IsLabelAutoFit = false;
            chartArea1.AxisY.LabelAutoFitStyle = ((System.Windows.Forms.DataVisualization.Charting.LabelAutoFitStyles)((((System.Windows.Forms.DataVisualization.Charting.LabelAutoFitStyles.IncreaseFont | System.Windows.Forms.DataVisualization.Charting.LabelAutoFitStyles.DecreaseFont)
                        | System.Windows.Forms.DataVisualization.Charting.LabelAutoFitStyles.LabelsAngleStep30)
                        | System.Windows.Forms.DataVisualization.Charting.LabelAutoFitStyles.WordWrap)));
            chartArea1.AxisY.LabelStyle.Font = new System.Drawing.Font("Verdana", 8F);
            chartArea1.AxisY.MajorGrid.Enabled = false;
            chartArea1.AxisY.Title = "PWV  (m/s)";
            chartArea1.BackColor = System.Drawing.Color.Transparent;
            chartArea1.BorderDashStyle = System.Windows.Forms.DataVisualization.Charting.ChartDashStyle.Solid;
            chartArea1.InnerPlotPosition.Auto = false;
            chartArea1.InnerPlotPosition.Height = 72.06963F;
            chartArea1.InnerPlotPosition.Width = 93.3223F;
            chartArea1.InnerPlotPosition.X = 5.56068F;
            chartArea1.InnerPlotPosition.Y = 2.46808F;
            chartArea1.Name = "ChartArea1";
            this.guiradchartPulseWaveVelocity.ChartAreas.Add(chartArea1);
            this.guiradchartPulseWaveVelocity.Location = new System.Drawing.Point(2, 3);
            this.guiradchartPulseWaveVelocity.Name = "guiradchartPulseWaveVelocity";
            series1.ChartArea = "ChartArea1";
            series1.ChartType = System.Windows.Forms.DataVisualization.Charting.SeriesChartType.Line;
            series1.Name = "Series1";
            this.guiradchartPulseWaveVelocity.Series.Add(series1);
            this.guiradchartPulseWaveVelocity.Size = new System.Drawing.Size(650, 197);
            this.guiradchartPulseWaveVelocity.TabIndex = 121;
            this.guiradchartPulseWaveVelocity.TabStop = false;
            this.guiradchartPulseWaveVelocity.Text = "chart1";
            this.guiradchartPulseWaveVelocity.Customize += new System.EventHandler(this.guiradchartPulseWaveVelocity_Customize);
            // 
            // guiradchartHeartRate
            // 
            this.guiradchartHeartRate.BackColor = System.Drawing.Color.Transparent;
            chartArea2.AlignmentStyle = System.Windows.Forms.DataVisualization.Charting.AreaAlignmentStyles.PlotPosition;
            chartArea2.AxisX.IntervalOffset = 1;
            chartArea2.AxisX.IntervalType = System.Windows.Forms.DataVisualization.Charting.DateTimeIntervalType.Number;
            chartArea2.AxisX.IsStartedFromZero = false;
            chartArea2.AxisX.LabelAutoFitStyle = ((System.Windows.Forms.DataVisualization.Charting.LabelAutoFitStyles)((((System.Windows.Forms.DataVisualization.Charting.LabelAutoFitStyles.IncreaseFont | System.Windows.Forms.DataVisualization.Charting.LabelAutoFitStyles.DecreaseFont)
                        | System.Windows.Forms.DataVisualization.Charting.LabelAutoFitStyles.LabelsAngleStep90)
                        | System.Windows.Forms.DataVisualization.Charting.LabelAutoFitStyles.WordWrap)));
            chartArea2.AxisX.LabelStyle.Font = new System.Drawing.Font("Microsoft Sans Serif", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            chartArea2.AxisX.LabelStyle.Interval = 0;
            chartArea2.AxisX.LabelStyle.IntervalOffsetType = System.Windows.Forms.DataVisualization.Charting.DateTimeIntervalType.Auto;
            chartArea2.AxisX.LabelStyle.IntervalType = System.Windows.Forms.DataVisualization.Charting.DateTimeIntervalType.Number;
            chartArea2.AxisX.MajorGrid.Enabled = false;
            chartArea2.AxisX.ScaleBreakStyle.BreakLineStyle = System.Windows.Forms.DataVisualization.Charting.BreakLineStyle.None;
            chartArea2.AxisX.ScaleBreakStyle.StartFromZero = System.Windows.Forms.DataVisualization.Charting.StartFromZero.No;
            chartArea2.AxisY.IsLabelAutoFit = false;
            chartArea2.AxisY.LabelStyle.Font = new System.Drawing.Font("Verdana", 8F);
            chartArea2.AxisY.MajorGrid.Enabled = false;
            chartArea2.AxisY.ScaleBreakStyle.BreakLineStyle = System.Windows.Forms.DataVisualization.Charting.BreakLineStyle.None;
            chartArea2.AxisY.ScaleBreakStyle.LineDashStyle = System.Windows.Forms.DataVisualization.Charting.ChartDashStyle.Dot;
            chartArea2.BackColor = System.Drawing.Color.Transparent;
            chartArea2.BorderDashStyle = System.Windows.Forms.DataVisualization.Charting.ChartDashStyle.Solid;
            chartArea2.InnerPlotPosition.Auto = false;
            chartArea2.InnerPlotPosition.Height = 72.06963F;
            chartArea2.InnerPlotPosition.Width = 93.3223F;
            chartArea2.InnerPlotPosition.X = 5.56068F;
            chartArea2.InnerPlotPosition.Y = 2.46808F;
            chartArea2.Name = "ChartArea1";
            this.guiradchartHeartRate.ChartAreas.Add(chartArea2);
            this.guiradchartHeartRate.Location = new System.Drawing.Point(3, 208);
            this.guiradchartHeartRate.Name = "guiradchartHeartRate";
            series2.ChartArea = "ChartArea1";
            series2.ChartType = System.Windows.Forms.DataVisualization.Charting.SeriesChartType.Line;
            series2.Name = "Series1";
            dataPoint4.Label = "50";
            series2.Points.Add(dataPoint1);
            series2.Points.Add(dataPoint2);
            series2.Points.Add(dataPoint3);
            series2.Points.Add(dataPoint4);
            this.guiradchartHeartRate.Series.Add(series2);
            this.guiradchartHeartRate.Size = new System.Drawing.Size(650, 197);
            this.guiradchartHeartRate.TabIndex = 120;
            this.guiradchartHeartRate.TabStop = false;
            title1.Name = "Title1";
            this.guiradchartHeartRate.Titles.Add(title1);
            // 
            // guiPicBoxReportLogo
            // 
            this.guiPicBoxReportLogo.Location = new System.Drawing.Point(644, 14);
            this.guiPicBoxReportLogo.Name = "guiPicBoxReportLogo";
            this.guiPicBoxReportLogo.Size = new System.Drawing.Size(50, 50);
            this.guiPicBoxReportLogo.SizeMode = System.Windows.Forms.PictureBoxSizeMode.StretchImage;
            this.guiPicBoxReportLogo.TabIndex = 104;
            this.guiPicBoxReportLogo.TabStop = false;
            // 
            // AnaylsisPreview
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.Color.White;
            this.ClientSize = new System.Drawing.Size(732, 742);
            this.Controls.Add(this.guiPicBoxReportLogo);
            this.Controls.Add(this.guiradpnlAnalysis);
            this.Name = "AnaylsisPreview";
            this.Text = "AnaylsisPreview";
            this.Load += new System.EventHandler(this.AnaylsisPreview_Load);
            ((System.ComponentModel.ISupportInitialize)(this.guiradpnlAnalysis)).EndInit();
            this.guiradpnlAnalysis.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.guiradchartPulseWaveVelocity)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.guiradchartHeartRate)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.guiPicBoxReportLogo)).EndInit();
            this.ResumeLayout(false);

        }

        #endregion

        private Telerik.WinControls.UI.RadPanel guiradpnlAnalysis;
        public System.Windows.Forms.PictureBox guiPicBoxReportLogo;
        public System.Windows.Forms.DataVisualization.Charting.Chart guiradchartPulseWaveVelocity;
        public System.Windows.Forms.DataVisualization.Charting.Chart guiradchartHeartRate;
    }
}