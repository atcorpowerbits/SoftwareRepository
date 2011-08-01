using System.Drawing;
namespace AtCor.Scor.Gui.Presentation
{
    partial class frmSettingsWindow
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
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(frmSettingsWindow));
            this.radDock1 = new Telerik.WinControls.UI.Docking.RadDock();
            this.docWndGeneralSettings = new Telerik.WinControls.UI.Docking.DocumentWindow();
            this.radgrpbxstartupMode = new Telerik.WinControls.UI.RadGroupBox();
            this.tableLayoutPanel12 = new System.Windows.Forms.TableLayoutPanel();
            this.radradiobtnPWVMode = new Telerik.WinControls.UI.RadRadioButton();
            this.radradiobtnPWAMode = new Telerik.WinControls.UI.RadRadioButton();
            this.radgrpbxStartupScreen = new Telerik.WinControls.UI.RadGroupBox();
            this.tableLayoutPanel7 = new System.Windows.Forms.TableLayoutPanel();
            this.radradiobtnQuickStart = new Telerik.WinControls.UI.RadRadioButton();
            this.radradiobtnSetup = new Telerik.WinControls.UI.RadRadioButton();
            this.radgrpbxReports = new Telerik.WinControls.UI.RadGroupBox();
            this.tableLayoutPanel5 = new System.Windows.Forms.TableLayoutPanel();
            this.radlblReportLogo = new Telerik.WinControls.UI.RadLabel();
            this.radtxtReportTitle = new Telerik.WinControls.UI.RadTextBox();
            this.radlblReportTitle = new Telerik.WinControls.UI.RadLabel();
            this.picbxReportLogo = new System.Windows.Forms.PictureBox();
            this.radbtnChange = new Telerik.WinControls.UI.RadButton();
            this.radgrpbxCommsPort = new Telerik.WinControls.UI.RadGroupBox();
            this.comboBoxCommsPort = new Telerik.WinControls.UI.RadDropDownList();
            this.radgrpbxHeightWeightUnits = new Telerik.WinControls.UI.RadGroupBox();
            this.tableLayoutPanel2 = new System.Windows.Forms.TableLayoutPanel();
            this.radradiobtnImperial = new Telerik.WinControls.UI.RadRadioButton();
            this.radradiobtnMetric = new Telerik.WinControls.UI.RadRadioButton();
            this.radgrpbxSetupScreen = new Telerik.WinControls.UI.RadGroupBox();
            this.radchkbxPatientPrivacy = new Telerik.WinControls.UI.RadCheckBox();
            this.documentContainer1 = new Telerik.WinControls.UI.Docking.DocumentContainer();
            this.documentTabStrip1 = new Telerik.WinControls.UI.Docking.DocumentTabStrip();
            this.docWndPWVSettings = new Telerik.WinControls.UI.Docking.DocumentWindow();
            this.radgrpbxCaptureGuide = new Telerik.WinControls.UI.RadGroupBox();
            this.tableLayoutPanel13 = new System.Windows.Forms.TableLayoutPanel();
            this.radchkAutoInflate = new Telerik.WinControls.UI.RadCheckBox();
            this.radchkAutoCapture = new Telerik.WinControls.UI.RadCheckBox();
            this.radgrpbxDefaultReport = new Telerik.WinControls.UI.RadGroupBox();
            this.comboDefaultReport = new Telerik.WinControls.UI.RadDropDownList();
            this.guiradgrpDefaultReport = new Telerik.WinControls.UI.RadGroupBox();
            this.radgrpbxSimulationTypes = new Telerik.WinControls.UI.RadGroupBox();
            this.comboSimulationFiles = new Telerik.WinControls.UI.RadDropDownList();
            this.radgrpSimulationFiles = new Telerik.WinControls.UI.RadGroupBox();
            this.radgrpCaptureTime = new Telerik.WinControls.UI.RadGroupBox();
            this.tableLayoutPanel4 = new System.Windows.Forms.TableLayoutPanel();
            this.rad5Seconds = new Telerik.WinControls.UI.RadRadioButton();
            this.rad10Seconds = new Telerik.WinControls.UI.RadRadioButton();
            this.rad20Seconds = new Telerik.WinControls.UI.RadRadioButton();
            this.radgrpReportScreen = new Telerik.WinControls.UI.RadGroupBox();
            this.radchkReferenceRange = new Telerik.WinControls.UI.RadCheckBox();
            this.radchkNormalRange = new Telerik.WinControls.UI.RadCheckBox();
            this.radgrpPwvDistanceUnits = new Telerik.WinControls.UI.RadGroupBox();
            this.tableLayoutPanel6 = new System.Windows.Forms.TableLayoutPanel();
            this.radmm = new Telerik.WinControls.UI.RadRadioButton();
            this.radcm = new Telerik.WinControls.UI.RadRadioButton();
            this.radgrpCuffLocation = new Telerik.WinControls.UI.RadGroupBox();
            this.radchkFemoralToCuff = new Telerik.WinControls.UI.RadCheckBox();
            this.radgrpbxPwvDistanceMethod = new Telerik.WinControls.UI.RadGroupBox();
            this.tblPWVDistanceMethod = new System.Windows.Forms.TableLayoutPanel();
            this.radDirect = new Telerik.WinControls.UI.RadRadioButton();
            this.radSubtracting = new Telerik.WinControls.UI.RadRadioButton();
            this.docWndPWASettings = new Telerik.WinControls.UI.Docking.DocumentWindow();
            this.guiradgrpbxPWASimulationFiles = new Telerik.WinControls.UI.RadGroupBox();
            this.radDropDownList3 = new Telerik.WinControls.UI.RadDropDownList();
            this.radgrpbxCaptureGuidePWA = new Telerik.WinControls.UI.RadGroupBox();
            this.radchkAutoCapturePWA = new Telerik.WinControls.UI.RadCheckBox();
            this.radchkGuidanceBars = new Telerik.WinControls.UI.RadCheckBox();
            this.radgrpbxClinicalReport = new Telerik.WinControls.UI.RadGroupBox();
            this.radchkBlindStudy = new Telerik.WinControls.UI.RadCheckBox();
            this.radchkAumentationIndexHR75 = new Telerik.WinControls.UI.RadCheckBox();
            this.radchkAumentationIndex = new Telerik.WinControls.UI.RadCheckBox();
            this.radgrpbxCaptureInput = new Telerik.WinControls.UI.RadGroupBox();
            this.tableLayoutPanel10 = new System.Windows.Forms.TableLayoutPanel();
            this.radradiobtnTonometer = new Telerik.WinControls.UI.RadRadioButton();
            this.radradiobtnPressureCuff = new Telerik.WinControls.UI.RadRadioButton();
            this.radgrpbxCaptureTime = new Telerik.WinControls.UI.RadGroupBox();
            this.tableLayoutPanel9 = new System.Windows.Forms.TableLayoutPanel();
            this.rad5SecondsPWA = new Telerik.WinControls.UI.RadRadioButton();
            this.rad10SecondsPWA = new Telerik.WinControls.UI.RadRadioButton();
            this.rad20SecondsPWA = new Telerik.WinControls.UI.RadRadioButton();
            this.documentWindow4 = new Telerik.WinControls.UI.Docking.DocumentWindow();
            this.docWndBPSettings = new Telerik.WinControls.UI.Docking.DocumentWindow();
            this.radgrpbxBloodPressures = new Telerik.WinControls.UI.RadGroupBox();
            this.tableLayoutPanel11 = new System.Windows.Forms.TableLayoutPanel();
            this.radradiobtnMPandDP = new Telerik.WinControls.UI.RadRadioButton();
            this.radradiobtnSPandDP = new Telerik.WinControls.UI.RadRadioButton();
            this.radradiobtnSPandMP = new Telerik.WinControls.UI.RadRadioButton();
            this.radgrpbxAutoPWA = new Telerik.WinControls.UI.RadGroupBox();
            this.guipnlBPAutoPWARangeDetails = new System.Windows.Forms.Panel();
            this.guiradtxtDPThreshold = new Telerik.WinControls.UI.RadTextBox();
            this.guiradtxtPPThreshold = new Telerik.WinControls.UI.RadTextBox();
            this.guiradtxtSPThreshold = new Telerik.WinControls.UI.RadTextBox();
            this.radradiochkDP = new Telerik.WinControls.UI.RadCheckBox();
            this.radradiochkPP = new Telerik.WinControls.UI.RadCheckBox();
            this.radradiochkSP = new Telerik.WinControls.UI.RadCheckBox();
            this.radgrpbxNumberOfAssessments = new Telerik.WinControls.UI.RadGroupBox();
            this.tableLayoutPanel14 = new System.Windows.Forms.TableLayoutPanel();
            this.radradiobtnAssessment5 = new Telerik.WinControls.UI.RadRadioButton();
            this.radradiobtnAssessment1 = new Telerik.WinControls.UI.RadRadioButton();
            this.radradiobtnAssessment2 = new Telerik.WinControls.UI.RadRadioButton();
            this.radradiobtnAssessment3 = new Telerik.WinControls.UI.RadRadioButton();
            this.radradiobtnAssessment4 = new Telerik.WinControls.UI.RadRadioButton();
            this.radgrpbxBPDevice = new Telerik.WinControls.UI.RadGroupBox();
            this.radradiobtnOther = new Telerik.WinControls.UI.RadRadioButton();
            this.radradiobtnSphygcomor = new Telerik.WinControls.UI.RadRadioButton();
            this.radGroupBox1 = new Telerik.WinControls.UI.RadGroupBox();
            this.tableLayoutPanel8 = new System.Windows.Forms.TableLayoutPanel();
            this.radRadioButton1 = new Telerik.WinControls.UI.RadRadioButton();
            this.radRadioButton4 = new Telerik.WinControls.UI.RadRadioButton();
            this.radRadioButton5 = new Telerik.WinControls.UI.RadRadioButton();
            this.radbtnDefaults = new Telerik.WinControls.UI.RadButton();
            this.radbtnCancel = new Telerik.WinControls.UI.RadButton();
            this.radbtnSave = new Telerik.WinControls.UI.RadButton();
            this.tableLayoutPanel3 = new System.Windows.Forms.TableLayoutPanel();
            this.radRadioButton2 = new Telerik.WinControls.UI.RadRadioButton();
            this.radRadioButton3 = new Telerik.WinControls.UI.RadRadioButton();
            this.object_2c8b2f0f_b093_4256_82f7_ffe6d52c17dc = new Telerik.WinControls.RootRadElement();
            this.documentWindow2 = new Telerik.WinControls.UI.Docking.DocumentWindow();
            this.documentWindow3 = new Telerik.WinControls.UI.Docking.DocumentWindow();
            this.radgrpbxBloodPressure = new Telerik.WinControls.UI.RadGroupBox();
            this.tableLayoutPanel1 = new System.Windows.Forms.TableLayoutPanel();
            ((System.ComponentModel.ISupportInitialize)(this.radDock1)).BeginInit();
            this.radDock1.SuspendLayout();
            this.docWndGeneralSettings.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.radgrpbxstartupMode)).BeginInit();
            this.radgrpbxstartupMode.SuspendLayout();
            this.tableLayoutPanel12.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.radradiobtnPWVMode)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.radradiobtnPWAMode)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.radgrpbxStartupScreen)).BeginInit();
            this.radgrpbxStartupScreen.SuspendLayout();
            this.tableLayoutPanel7.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.radradiobtnQuickStart)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.radradiobtnSetup)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.radgrpbxReports)).BeginInit();
            this.radgrpbxReports.SuspendLayout();
            this.tableLayoutPanel5.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.radlblReportLogo)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.radtxtReportTitle)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.radlblReportTitle)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.picbxReportLogo)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.radbtnChange)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.radgrpbxCommsPort)).BeginInit();
            this.radgrpbxCommsPort.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.comboBoxCommsPort)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.radgrpbxHeightWeightUnits)).BeginInit();
            this.radgrpbxHeightWeightUnits.SuspendLayout();
            this.tableLayoutPanel2.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.radradiobtnImperial)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.radradiobtnMetric)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.radgrpbxSetupScreen)).BeginInit();
            this.radgrpbxSetupScreen.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.radchkbxPatientPrivacy)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.documentContainer1)).BeginInit();
            this.documentContainer1.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.documentTabStrip1)).BeginInit();
            this.documentTabStrip1.SuspendLayout();
            this.docWndPWVSettings.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.radgrpbxCaptureGuide)).BeginInit();
            this.radgrpbxCaptureGuide.SuspendLayout();
            this.tableLayoutPanel13.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.radchkAutoInflate)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.radchkAutoCapture)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.radgrpbxDefaultReport)).BeginInit();
            this.radgrpbxDefaultReport.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.comboDefaultReport)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.guiradgrpDefaultReport)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.radgrpbxSimulationTypes)).BeginInit();
            this.radgrpbxSimulationTypes.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.comboSimulationFiles)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.radgrpSimulationFiles)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.radgrpCaptureTime)).BeginInit();
            this.radgrpCaptureTime.SuspendLayout();
            this.tableLayoutPanel4.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.rad5Seconds)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.rad10Seconds)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.rad20Seconds)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.radgrpReportScreen)).BeginInit();
            this.radgrpReportScreen.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.radchkReferenceRange)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.radchkNormalRange)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.radgrpPwvDistanceUnits)).BeginInit();
            this.radgrpPwvDistanceUnits.SuspendLayout();
            this.tableLayoutPanel6.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.radmm)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.radcm)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.radgrpCuffLocation)).BeginInit();
            this.radgrpCuffLocation.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.radchkFemoralToCuff)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.radgrpbxPwvDistanceMethod)).BeginInit();
            this.radgrpbxPwvDistanceMethod.SuspendLayout();
            this.tblPWVDistanceMethod.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.radDirect)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.radSubtracting)).BeginInit();
            this.docWndPWASettings.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.guiradgrpbxPWASimulationFiles)).BeginInit();
            this.guiradgrpbxPWASimulationFiles.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.radDropDownList3)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.radgrpbxCaptureGuidePWA)).BeginInit();
            this.radgrpbxCaptureGuidePWA.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.radchkAutoCapturePWA)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.radchkGuidanceBars)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.radgrpbxClinicalReport)).BeginInit();
            this.radgrpbxClinicalReport.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.radchkBlindStudy)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.radchkAumentationIndexHR75)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.radchkAumentationIndex)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.radgrpbxCaptureInput)).BeginInit();
            this.radgrpbxCaptureInput.SuspendLayout();
            this.tableLayoutPanel10.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.radradiobtnTonometer)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.radradiobtnPressureCuff)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.radgrpbxCaptureTime)).BeginInit();
            this.radgrpbxCaptureTime.SuspendLayout();
            this.tableLayoutPanel9.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.rad5SecondsPWA)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.rad10SecondsPWA)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.rad20SecondsPWA)).BeginInit();
            this.documentWindow4.SuspendLayout();
            this.docWndBPSettings.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.radgrpbxBloodPressures)).BeginInit();
            this.radgrpbxBloodPressures.SuspendLayout();
            this.tableLayoutPanel11.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.radradiobtnMPandDP)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.radradiobtnSPandDP)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.radradiobtnSPandMP)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.radgrpbxAutoPWA)).BeginInit();
            this.radgrpbxAutoPWA.SuspendLayout();
            this.guipnlBPAutoPWARangeDetails.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.guiradtxtDPThreshold)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.guiradtxtPPThreshold)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.guiradtxtSPThreshold)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.radradiochkDP)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.radradiochkPP)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.radradiochkSP)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.radgrpbxNumberOfAssessments)).BeginInit();
            this.radgrpbxNumberOfAssessments.SuspendLayout();
            this.tableLayoutPanel14.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.radradiobtnAssessment5)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.radradiobtnAssessment1)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.radradiobtnAssessment2)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.radradiobtnAssessment3)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.radradiobtnAssessment4)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.radgrpbxBPDevice)).BeginInit();
            this.radgrpbxBPDevice.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.radradiobtnOther)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.radradiobtnSphygcomor)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.radGroupBox1)).BeginInit();
            this.radGroupBox1.SuspendLayout();
            this.tableLayoutPanel8.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.radRadioButton1)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.radRadioButton4)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.radRadioButton5)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.radbtnDefaults)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.radbtnCancel)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.radbtnSave)).BeginInit();
            this.tableLayoutPanel3.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.radRadioButton2)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.radRadioButton3)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.radgrpbxBloodPressure)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this)).BeginInit();
            this.SuspendLayout();
            // 
            // radDock1
            // 
            this.radDock1.ActiveWindow = this.docWndPWVSettings;
            this.radDock1.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(142)))), ((int)(((byte)(150)))), ((int)(((byte)(186)))));
            this.radDock1.CausesValidation = false;
            this.radDock1.Controls.Add(this.documentContainer1);
            this.radDock1.DocumentManager.DocumentInsertOrder = Telerik.WinControls.UI.Docking.DockWindowInsertOrder.InFront;
            this.radDock1.Font = new System.Drawing.Font("Arial", 11.25F);
            this.radDock1.IsCleanUpTarget = true;
            this.radDock1.Location = new System.Drawing.Point(9, 9);
            this.radDock1.MainDocumentContainer = this.documentContainer1;
            this.radDock1.Name = "radDock1";
            // 
            // 
            // 
            this.radDock1.RootElement.MinSize = new System.Drawing.Size(25, 25);
            this.radDock1.RootElement.Padding = new System.Windows.Forms.Padding(0);
            this.radDock1.ShowToolCloseButton = true;
            this.radDock1.Size = new System.Drawing.Size(552, 411);
            this.radDock1.SplitterWidth = 4;
            this.radDock1.TabIndex = 0;
            this.radDock1.TabStop = false;
            this.radDock1.Text = "PWV Settings";
            // 
            // docWndGeneralSettings
            // 
            this.docWndGeneralSettings.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(142)))), ((int)(((byte)(150)))), ((int)(((byte)(186)))));
            this.docWndGeneralSettings.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D;
            this.docWndGeneralSettings.Controls.Add(this.radgrpbxstartupMode);
            this.docWndGeneralSettings.Controls.Add(this.radgrpbxStartupScreen);
            this.docWndGeneralSettings.Controls.Add(this.radgrpbxReports);
            this.docWndGeneralSettings.Controls.Add(this.radgrpbxCommsPort);
            this.docWndGeneralSettings.Controls.Add(this.radgrpbxHeightWeightUnits);
            this.docWndGeneralSettings.Controls.Add(this.radgrpbxSetupScreen);
            this.docWndGeneralSettings.DocumentButtons = Telerik.WinControls.UI.Docking.DocumentStripButtons.None;
            this.docWndGeneralSettings.Font = new System.Drawing.Font("Verdana", 8.25F);
            this.docWndGeneralSettings.Location = new System.Drawing.Point(6, 33);
            this.docWndGeneralSettings.Name = "docWndGeneralSettings";
            this.docWndGeneralSettings.Size = new System.Drawing.Size(540, 372);
            this.docWndGeneralSettings.Text = "General Settings";
            // 
            // radgrpbxstartupMode
            // 
            this.radgrpbxstartupMode.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(142)))), ((int)(((byte)(150)))), ((int)(((byte)(186)))));
            this.radgrpbxstartupMode.Controls.Add(this.tableLayoutPanel12);
            this.radgrpbxstartupMode.Font = new System.Drawing.Font("Arial", 11.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.radgrpbxstartupMode.FooterImageIndex = -1;
            this.radgrpbxstartupMode.FooterImageKey = "";
            this.radgrpbxstartupMode.HeaderImageIndex = -1;
            this.radgrpbxstartupMode.HeaderImageKey = "";
            this.radgrpbxstartupMode.HeaderMargin = new System.Windows.Forms.Padding(0);
            this.radgrpbxstartupMode.HeaderText = "Startup Mode";
            this.radgrpbxstartupMode.Location = new System.Drawing.Point(15, 273);
            this.radgrpbxstartupMode.Name = "radgrpbxstartupMode";
            this.radgrpbxstartupMode.Padding = new System.Windows.Forms.Padding(10, 20, 10, 10);
            // 
            // 
            // 
            this.radgrpbxstartupMode.RootElement.Padding = new System.Windows.Forms.Padding(10, 20, 10, 10);
            this.radgrpbxstartupMode.Size = new System.Drawing.Size(228, 82);
            this.radgrpbxstartupMode.TabIndex = 4;
            this.radgrpbxstartupMode.Text = "Startup Mode";
            ((Telerik.WinControls.Primitives.FillPrimitive)(this.radgrpbxstartupMode.GetChildAt(0).GetChildAt(0).GetChildAt(0))).BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(142)))), ((int)(((byte)(150)))), ((int)(((byte)(186)))));
            ((Telerik.WinControls.Primitives.BorderPrimitive)(this.radgrpbxstartupMode.GetChildAt(0).GetChildAt(0).GetChildAt(1))).ForeColor2 = System.Drawing.SystemColors.ControlLight;
            ((Telerik.WinControls.Primitives.BorderPrimitive)(this.radgrpbxstartupMode.GetChildAt(0).GetChildAt(0).GetChildAt(1))).ForeColor3 = System.Drawing.SystemColors.ControlLight;
            ((Telerik.WinControls.Primitives.BorderPrimitive)(this.radgrpbxstartupMode.GetChildAt(0).GetChildAt(0).GetChildAt(1))).ForeColor4 = System.Drawing.SystemColors.ControlLight;
            ((Telerik.WinControls.Primitives.BorderPrimitive)(this.radgrpbxstartupMode.GetChildAt(0).GetChildAt(0).GetChildAt(1))).ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(185)))), ((int)(((byte)(199)))), ((int)(((byte)(220)))));
            ((Telerik.WinControls.UI.GroupBoxHeader)(this.radgrpbxstartupMode.GetChildAt(0).GetChildAt(1))).ForeColor = System.Drawing.Color.WhiteSmoke;
            ((Telerik.WinControls.Primitives.FillPrimitive)(this.radgrpbxstartupMode.GetChildAt(0).GetChildAt(1).GetChildAt(0))).BackColor2 = System.Drawing.Color.FromArgb(((int)(((byte)(142)))), ((int)(((byte)(150)))), ((int)(((byte)(186)))));
            ((Telerik.WinControls.Primitives.FillPrimitive)(this.radgrpbxstartupMode.GetChildAt(0).GetChildAt(1).GetChildAt(0))).BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(142)))), ((int)(((byte)(150)))), ((int)(((byte)(186)))));
            ((Telerik.WinControls.Primitives.BorderPrimitive)(this.radgrpbxstartupMode.GetChildAt(0).GetChildAt(1).GetChildAt(1))).Width = 0F;
            // 
            // tableLayoutPanel12
            // 
            this.tableLayoutPanel12.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(142)))), ((int)(((byte)(150)))), ((int)(((byte)(186)))));
            this.tableLayoutPanel12.ColumnCount = 1;
            this.tableLayoutPanel12.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 50F));
            this.tableLayoutPanel12.Controls.Add(this.radradiobtnPWVMode, 0, 0);
            this.tableLayoutPanel12.Controls.Add(this.radradiobtnPWAMode, 0, 1);
            this.tableLayoutPanel12.Location = new System.Drawing.Point(17, 25);
            this.tableLayoutPanel12.Name = "tableLayoutPanel12";
            this.tableLayoutPanel12.RowCount = 2;
            this.tableLayoutPanel12.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 46.93877F));
            this.tableLayoutPanel12.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 53.06123F));
            this.tableLayoutPanel12.Size = new System.Drawing.Size(189, 45);
            this.tableLayoutPanel12.TabIndex = 3;
            // 
            // radradiobtnPWVMode
            // 
            this.radradiobtnPWVMode.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(142)))), ((int)(((byte)(150)))), ((int)(((byte)(186)))));
            this.radradiobtnPWVMode.Font = new System.Drawing.Font("Arial", 11.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.radradiobtnPWVMode.ForeColor = System.Drawing.Color.WhiteSmoke;
            this.radradiobtnPWVMode.Location = new System.Drawing.Point(3, 3);
            this.radradiobtnPWVMode.Name = "radradiobtnPWVMode";
            // 
            // 
            // 
            this.radradiobtnPWVMode.RootElement.ForeColor = System.Drawing.Color.WhiteSmoke;
            this.radradiobtnPWVMode.Size = new System.Drawing.Size(183, 14);
            this.radradiobtnPWVMode.TabIndex = 6;
            this.radradiobtnPWVMode.Text = "PWV";
            this.radradiobtnPWVMode.Click += new System.EventHandler(this.radradiobtnImperial_Click);
            // 
            // radradiobtnPWAMode
            // 
            this.radradiobtnPWAMode.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(142)))), ((int)(((byte)(150)))), ((int)(((byte)(186)))));
            this.radradiobtnPWAMode.Font = new System.Drawing.Font("Arial", 11.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.radradiobtnPWAMode.ForeColor = System.Drawing.Color.WhiteSmoke;
            this.radradiobtnPWAMode.Location = new System.Drawing.Point(3, 24);
            this.radradiobtnPWAMode.Name = "radradiobtnPWAMode";
            // 
            // 
            // 
            this.radradiobtnPWAMode.RootElement.ForeColor = System.Drawing.Color.WhiteSmoke;
            this.radradiobtnPWAMode.Size = new System.Drawing.Size(183, 17);
            this.radradiobtnPWAMode.TabIndex = 7;
            this.radradiobtnPWAMode.Text = "PWA";
            this.radradiobtnPWAMode.Click += new System.EventHandler(this.radradiobtnImperial_Click);
            // 
            // radgrpbxStartupScreen
            // 
            this.radgrpbxStartupScreen.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(142)))), ((int)(((byte)(150)))), ((int)(((byte)(186)))));
            this.radgrpbxStartupScreen.Controls.Add(this.tableLayoutPanel7);
            this.radgrpbxStartupScreen.Font = new System.Drawing.Font("Arial", 11.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.radgrpbxStartupScreen.FooterImageIndex = -1;
            this.radgrpbxStartupScreen.FooterImageKey = "";
            this.radgrpbxStartupScreen.HeaderImageIndex = -1;
            this.radgrpbxStartupScreen.HeaderImageKey = "";
            this.radgrpbxStartupScreen.HeaderMargin = new System.Windows.Forms.Padding(0);
            this.radgrpbxStartupScreen.HeaderText = "Startup Screen";
            this.radgrpbxStartupScreen.Location = new System.Drawing.Point(15, 184);
            this.radgrpbxStartupScreen.Name = "radgrpbxStartupScreen";
            this.radgrpbxStartupScreen.Padding = new System.Windows.Forms.Padding(10, 20, 10, 10);
            // 
            // 
            // 
            this.radgrpbxStartupScreen.RootElement.Padding = new System.Windows.Forms.Padding(10, 20, 10, 10);
            this.radgrpbxStartupScreen.Size = new System.Drawing.Size(228, 82);
            this.radgrpbxStartupScreen.TabIndex = 3;
            this.radgrpbxStartupScreen.Text = "Startup Screen";
            ((Telerik.WinControls.Primitives.FillPrimitive)(this.radgrpbxStartupScreen.GetChildAt(0).GetChildAt(0).GetChildAt(0))).BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(142)))), ((int)(((byte)(150)))), ((int)(((byte)(186)))));
            ((Telerik.WinControls.Primitives.BorderPrimitive)(this.radgrpbxStartupScreen.GetChildAt(0).GetChildAt(0).GetChildAt(1))).ForeColor2 = System.Drawing.SystemColors.ControlLight;
            ((Telerik.WinControls.Primitives.BorderPrimitive)(this.radgrpbxStartupScreen.GetChildAt(0).GetChildAt(0).GetChildAt(1))).ForeColor3 = System.Drawing.SystemColors.ControlLight;
            ((Telerik.WinControls.Primitives.BorderPrimitive)(this.radgrpbxStartupScreen.GetChildAt(0).GetChildAt(0).GetChildAt(1))).ForeColor4 = System.Drawing.SystemColors.ControlLight;
            ((Telerik.WinControls.Primitives.BorderPrimitive)(this.radgrpbxStartupScreen.GetChildAt(0).GetChildAt(0).GetChildAt(1))).ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(185)))), ((int)(((byte)(199)))), ((int)(((byte)(220)))));
            ((Telerik.WinControls.UI.GroupBoxHeader)(this.radgrpbxStartupScreen.GetChildAt(0).GetChildAt(1))).ForeColor = System.Drawing.Color.WhiteSmoke;
            ((Telerik.WinControls.Primitives.FillPrimitive)(this.radgrpbxStartupScreen.GetChildAt(0).GetChildAt(1).GetChildAt(0))).BackColor2 = System.Drawing.Color.FromArgb(((int)(((byte)(142)))), ((int)(((byte)(150)))), ((int)(((byte)(186)))));
            ((Telerik.WinControls.Primitives.FillPrimitive)(this.radgrpbxStartupScreen.GetChildAt(0).GetChildAt(1).GetChildAt(0))).BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(142)))), ((int)(((byte)(150)))), ((int)(((byte)(186)))));
            ((Telerik.WinControls.Primitives.BorderPrimitive)(this.radgrpbxStartupScreen.GetChildAt(0).GetChildAt(1).GetChildAt(1))).Width = 0F;
            // 
            // tableLayoutPanel7
            // 
            this.tableLayoutPanel7.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(142)))), ((int)(((byte)(150)))), ((int)(((byte)(186)))));
            this.tableLayoutPanel7.ColumnCount = 1;
            this.tableLayoutPanel7.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 50F));
            this.tableLayoutPanel7.Controls.Add(this.radradiobtnQuickStart, 0, 0);
            this.tableLayoutPanel7.Controls.Add(this.radradiobtnSetup, 0, 1);
            this.tableLayoutPanel7.Location = new System.Drawing.Point(17, 23);
            this.tableLayoutPanel7.Name = "tableLayoutPanel7";
            this.tableLayoutPanel7.RowCount = 2;
            this.tableLayoutPanel7.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 46.93877F));
            this.tableLayoutPanel7.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 53.06123F));
            this.tableLayoutPanel7.Size = new System.Drawing.Size(189, 49);
            this.tableLayoutPanel7.TabIndex = 3;
            // 
            // radradiobtnQuickStart
            // 
            this.radradiobtnQuickStart.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(142)))), ((int)(((byte)(150)))), ((int)(((byte)(186)))));
            this.radradiobtnQuickStart.Font = new System.Drawing.Font("Arial", 11.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.radradiobtnQuickStart.ForeColor = System.Drawing.Color.WhiteSmoke;
            this.radradiobtnQuickStart.Location = new System.Drawing.Point(3, 3);
            this.radradiobtnQuickStart.Name = "radradiobtnQuickStart";
            // 
            // 
            // 
            this.radradiobtnQuickStart.RootElement.ForeColor = System.Drawing.Color.WhiteSmoke;
            this.radradiobtnQuickStart.Size = new System.Drawing.Size(183, 16);
            this.radradiobtnQuickStart.TabIndex = 4;
            this.radradiobtnQuickStart.Text = "Quick Start";
            this.radradiobtnQuickStart.Click += new System.EventHandler(this.radradiobtnImperial_Click);
            // 
            // radradiobtnSetup
            // 
            this.radradiobtnSetup.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(142)))), ((int)(((byte)(150)))), ((int)(((byte)(186)))));
            this.radradiobtnSetup.Font = new System.Drawing.Font("Arial", 11.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.radradiobtnSetup.ForeColor = System.Drawing.Color.WhiteSmoke;
            this.radradiobtnSetup.Location = new System.Drawing.Point(3, 25);
            this.radradiobtnSetup.Name = "radradiobtnSetup";
            // 
            // 
            // 
            this.radradiobtnSetup.RootElement.ForeColor = System.Drawing.Color.WhiteSmoke;
            this.radradiobtnSetup.Size = new System.Drawing.Size(183, 21);
            this.radradiobtnSetup.TabIndex = 5;
            this.radradiobtnSetup.Text = "Setup";
            this.radradiobtnSetup.Click += new System.EventHandler(this.radradiobtnImperial_Click);
            // 
            // radgrpbxReports
            // 
            this.radgrpbxReports.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(142)))), ((int)(((byte)(150)))), ((int)(((byte)(186)))));
            this.radgrpbxReports.Controls.Add(this.tableLayoutPanel5);
            this.radgrpbxReports.Font = new System.Drawing.Font("Arial", 11.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.radgrpbxReports.FooterImageIndex = -1;
            this.radgrpbxReports.FooterImageKey = "";
            this.radgrpbxReports.HeaderImageIndex = -1;
            this.radgrpbxReports.HeaderImageKey = "";
            this.radgrpbxReports.HeaderMargin = new System.Windows.Forms.Padding(0);
            this.radgrpbxReports.HeaderText = "Reports";
            this.radgrpbxReports.Location = new System.Drawing.Point(282, 84);
            this.radgrpbxReports.Name = "radgrpbxReports";
            this.radgrpbxReports.Padding = new System.Windows.Forms.Padding(10, 20, 10, 10);
            // 
            // 
            // 
            this.radgrpbxReports.RootElement.Padding = new System.Windows.Forms.Padding(10, 20, 10, 10);
            this.radgrpbxReports.Size = new System.Drawing.Size(242, 271);
            this.radgrpbxReports.TabIndex = 6;
            this.radgrpbxReports.Text = "Reports";
            ((Telerik.WinControls.Primitives.FillPrimitive)(this.radgrpbxReports.GetChildAt(0).GetChildAt(0).GetChildAt(0))).BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(142)))), ((int)(((byte)(150)))), ((int)(((byte)(186)))));
            ((Telerik.WinControls.Primitives.BorderPrimitive)(this.radgrpbxReports.GetChildAt(0).GetChildAt(0).GetChildAt(1))).ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(185)))), ((int)(((byte)(199)))), ((int)(((byte)(220)))));
            ((Telerik.WinControls.UI.GroupBoxHeader)(this.radgrpbxReports.GetChildAt(0).GetChildAt(1))).ForeColor = System.Drawing.Color.WhiteSmoke;
            ((Telerik.WinControls.Primitives.FillPrimitive)(this.radgrpbxReports.GetChildAt(0).GetChildAt(1).GetChildAt(0))).BackColor2 = System.Drawing.Color.FromArgb(((int)(((byte)(142)))), ((int)(((byte)(150)))), ((int)(((byte)(186)))));
            ((Telerik.WinControls.Primitives.FillPrimitive)(this.radgrpbxReports.GetChildAt(0).GetChildAt(1).GetChildAt(0))).BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(142)))), ((int)(((byte)(150)))), ((int)(((byte)(186)))));
            ((Telerik.WinControls.Primitives.BorderPrimitive)(this.radgrpbxReports.GetChildAt(0).GetChildAt(1).GetChildAt(1))).Width = 0F;
            // 
            // tableLayoutPanel5
            // 
            this.tableLayoutPanel5.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(142)))), ((int)(((byte)(150)))), ((int)(((byte)(186)))));
            this.tableLayoutPanel5.ColumnCount = 1;
            this.tableLayoutPanel5.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 100F));
            this.tableLayoutPanel5.Controls.Add(this.radlblReportLogo, 0, 2);
            this.tableLayoutPanel5.Controls.Add(this.radtxtReportTitle, 0, 1);
            this.tableLayoutPanel5.Controls.Add(this.radlblReportTitle, 0, 0);
            this.tableLayoutPanel5.Controls.Add(this.picbxReportLogo, 0, 3);
            this.tableLayoutPanel5.Controls.Add(this.radbtnChange, 0, 4);
            this.tableLayoutPanel5.Location = new System.Drawing.Point(13, 30);
            this.tableLayoutPanel5.Name = "tableLayoutPanel5";
            this.tableLayoutPanel5.RowCount = 5;
            this.tableLayoutPanel5.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Absolute, 24F));
            this.tableLayoutPanel5.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Absolute, 30F));
            this.tableLayoutPanel5.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Absolute, 27F));
            this.tableLayoutPanel5.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Absolute, 95F));
            this.tableLayoutPanel5.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Absolute, 8F));
            this.tableLayoutPanel5.Size = new System.Drawing.Size(219, 217);
            this.tableLayoutPanel5.TabIndex = 6;
            // 
            // radlblReportLogo
            // 
            this.radlblReportLogo.Font = new System.Drawing.Font("Arial", 11.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.radlblReportLogo.ForeColor = System.Drawing.Color.White;
            this.radlblReportLogo.Location = new System.Drawing.Point(3, 57);
            this.radlblReportLogo.Name = "radlblReportLogo";
            // 
            // 
            // 
            this.radlblReportLogo.RootElement.ForeColor = System.Drawing.Color.White;
            this.radlblReportLogo.Size = new System.Drawing.Size(93, 21);
            this.radlblReportLogo.TabIndex = 1;
            this.radlblReportLogo.Text = "Report Logo";
            // 
            // radtxtReportTitle
            // 
            this.radtxtReportTitle.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(142)))), ((int)(((byte)(150)))), ((int)(((byte)(186)))));
            this.radtxtReportTitle.Font = new System.Drawing.Font("Arial", 11.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.radtxtReportTitle.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(23)))), ((int)(((byte)(29)))), ((int)(((byte)(55)))));
            this.radtxtReportTitle.Location = new System.Drawing.Point(3, 27);
            this.radtxtReportTitle.MaxLength = 100;
            this.radtxtReportTitle.Name = "radtxtReportTitle";
            // 
            // 
            // 
            this.radtxtReportTitle.RootElement.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(23)))), ((int)(((byte)(29)))), ((int)(((byte)(55)))));
            this.radtxtReportTitle.Size = new System.Drawing.Size(213, 23);
            this.radtxtReportTitle.TabIndex = 9;
            this.radtxtReportTitle.TabStop = false;
            this.radtxtReportTitle.TextChanged += new System.EventHandler(this.radtxtReportTitle_TextChanged);
            // 
            // radlblReportTitle
            // 
            this.radlblReportTitle.Font = new System.Drawing.Font("Arial", 11.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.radlblReportTitle.ForeColor = System.Drawing.Color.White;
            this.radlblReportTitle.Location = new System.Drawing.Point(3, 3);
            this.radlblReportTitle.Name = "radlblReportTitle";
            // 
            // 
            // 
            this.radlblReportTitle.RootElement.ForeColor = System.Drawing.Color.White;
            this.radlblReportTitle.Size = new System.Drawing.Size(87, 21);
            this.radlblReportTitle.TabIndex = 0;
            this.radlblReportTitle.Text = "Report Title";
            // 
            // picbxReportLogo
            // 
            this.picbxReportLogo.Anchor = System.Windows.Forms.AnchorStyles.None;
            this.picbxReportLogo.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D;
            this.picbxReportLogo.Location = new System.Drawing.Point(59, 86);
            this.picbxReportLogo.MaximumSize = new System.Drawing.Size(100, 84);
            this.picbxReportLogo.Name = "picbxReportLogo";
            this.picbxReportLogo.Size = new System.Drawing.Size(100, 84);
            this.picbxReportLogo.SizeMode = System.Windows.Forms.PictureBoxSizeMode.StretchImage;
            this.picbxReportLogo.TabIndex = 3;
            this.picbxReportLogo.TabStop = false;
            // 
            // radbtnChange
            // 
            this.radbtnChange.Anchor = System.Windows.Forms.AnchorStyles.Right;
            this.radbtnChange.Font = new System.Drawing.Font("Arial", 11.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.radbtnChange.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(23)))), ((int)(((byte)(29)))), ((int)(((byte)(55)))));
            this.radbtnChange.Location = new System.Drawing.Point(136, 184);
            this.radbtnChange.Name = "radbtnChange";
            // 
            // 
            // 
            this.radbtnChange.RootElement.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(23)))), ((int)(((byte)(29)))), ((int)(((byte)(55)))));
            this.radbtnChange.Size = new System.Drawing.Size(80, 25);
            this.radbtnChange.TabIndex = 10;
            this.radbtnChange.Text = " Change ";
            this.radbtnChange.Click += new System.EventHandler(this.radbtnChange_Click);
            ((Telerik.WinControls.UI.RadButtonElement)(this.radbtnChange.GetChildAt(0))).Text = " Change ";
            ((Telerik.WinControls.Primitives.FillPrimitive)(this.radbtnChange.GetChildAt(0).GetChildAt(0))).BackColor2 = System.Drawing.Color.FromArgb(((int)(((byte)(172)))), ((int)(((byte)(177)))), ((int)(((byte)(204)))));
            ((Telerik.WinControls.Primitives.FillPrimitive)(this.radbtnChange.GetChildAt(0).GetChildAt(0))).BackColor3 = System.Drawing.Color.FromArgb(((int)(((byte)(172)))), ((int)(((byte)(177)))), ((int)(((byte)(204)))));
            ((Telerik.WinControls.Primitives.FillPrimitive)(this.radbtnChange.GetChildAt(0).GetChildAt(0))).BackColor4 = System.Drawing.Color.FromArgb(((int)(((byte)(142)))), ((int)(((byte)(150)))), ((int)(((byte)(186)))));
            ((Telerik.WinControls.Primitives.FillPrimitive)(this.radbtnChange.GetChildAt(0).GetChildAt(0))).BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(225)))), ((int)(((byte)(228)))), ((int)(((byte)(243)))));
            ((Telerik.WinControls.Primitives.BorderPrimitive)(this.radbtnChange.GetChildAt(0).GetChildAt(2))).ForeColor = System.Drawing.Color.White;
            // 
            // radgrpbxCommsPort
            // 
            this.radgrpbxCommsPort.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(142)))), ((int)(((byte)(150)))), ((int)(((byte)(186)))));
            this.radgrpbxCommsPort.CausesValidation = false;
            this.radgrpbxCommsPort.Controls.Add(this.comboBoxCommsPort);
            this.radgrpbxCommsPort.Font = new System.Drawing.Font("Arial", 11.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.radgrpbxCommsPort.FooterImageIndex = -1;
            this.radgrpbxCommsPort.FooterImageKey = "";
            this.radgrpbxCommsPort.HeaderImageIndex = -1;
            this.radgrpbxCommsPort.HeaderImageKey = "";
            this.radgrpbxCommsPort.HeaderMargin = new System.Windows.Forms.Padding(0);
            this.radgrpbxCommsPort.HeaderText = "Comms Port";
            this.radgrpbxCommsPort.Location = new System.Drawing.Point(282, 16);
            this.radgrpbxCommsPort.Name = "radgrpbxCommsPort";
            this.radgrpbxCommsPort.Padding = new System.Windows.Forms.Padding(10, 20, 10, 10);
            // 
            // 
            // 
            this.radgrpbxCommsPort.RootElement.Padding = new System.Windows.Forms.Padding(10, 20, 10, 10);
            this.radgrpbxCommsPort.Size = new System.Drawing.Size(243, 62);
            this.radgrpbxCommsPort.TabIndex = 5;
            this.radgrpbxCommsPort.Text = "Comms Port";
            ((Telerik.WinControls.Primitives.FillPrimitive)(this.radgrpbxCommsPort.GetChildAt(0).GetChildAt(0).GetChildAt(0))).BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(142)))), ((int)(((byte)(150)))), ((int)(((byte)(186)))));
            ((Telerik.WinControls.Primitives.BorderPrimitive)(this.radgrpbxCommsPort.GetChildAt(0).GetChildAt(0).GetChildAt(1))).ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(185)))), ((int)(((byte)(199)))), ((int)(((byte)(220)))));
            ((Telerik.WinControls.UI.GroupBoxHeader)(this.radgrpbxCommsPort.GetChildAt(0).GetChildAt(1))).ForeColor = System.Drawing.Color.WhiteSmoke;
            ((Telerik.WinControls.Primitives.FillPrimitive)(this.radgrpbxCommsPort.GetChildAt(0).GetChildAt(1).GetChildAt(0))).BackColor2 = System.Drawing.Color.FromArgb(((int)(((byte)(142)))), ((int)(((byte)(150)))), ((int)(((byte)(186)))));
            ((Telerik.WinControls.Primitives.FillPrimitive)(this.radgrpbxCommsPort.GetChildAt(0).GetChildAt(1).GetChildAt(0))).BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(142)))), ((int)(((byte)(150)))), ((int)(((byte)(186)))));
            ((Telerik.WinControls.Primitives.BorderPrimitive)(this.radgrpbxCommsPort.GetChildAt(0).GetChildAt(1).GetChildAt(1))).Width = 0F;
            // 
            // comboBoxCommsPort
            // 
            this.comboBoxCommsPort.AutoCompleteMode = System.Windows.Forms.AutoCompleteMode.Append;
            this.comboBoxCommsPort.AutoSize = false;
            this.comboBoxCommsPort.CausesValidation = false;
            this.comboBoxCommsPort.DropDownHeight = 80;
            this.comboBoxCommsPort.DropDownStyle = Telerik.WinControls.RadDropDownStyle.DropDownList;
            this.comboBoxCommsPort.Font = new System.Drawing.Font("Arial", 11.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.comboBoxCommsPort.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(23)))), ((int)(((byte)(29)))), ((int)(((byte)(55)))));
            this.comboBoxCommsPort.Location = new System.Drawing.Point(16, 25);
            this.comboBoxCommsPort.Name = "comboBoxCommsPort";
            // 
            // 
            // 
            this.comboBoxCommsPort.RootElement.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(23)))), ((int)(((byte)(29)))), ((int)(((byte)(55)))));
            this.comboBoxCommsPort.Size = new System.Drawing.Size(163, 23);
            this.comboBoxCommsPort.TabIndex = 8;
            this.comboBoxCommsPort.SelectedIndexChanged += new Telerik.WinControls.UI.Data.PositionChangedEventHandler(this.comboBoxCommsPort_SelectionChangeCommitted);
            // 
            // radgrpbxHeightWeightUnits
            // 
            this.radgrpbxHeightWeightUnits.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(142)))), ((int)(((byte)(150)))), ((int)(((byte)(186)))));
            this.radgrpbxHeightWeightUnits.Controls.Add(this.tableLayoutPanel2);
            this.radgrpbxHeightWeightUnits.Font = new System.Drawing.Font("Arial", 11.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.radgrpbxHeightWeightUnits.FooterImageIndex = -1;
            this.radgrpbxHeightWeightUnits.FooterImageKey = "";
            this.radgrpbxHeightWeightUnits.HeaderImageIndex = -1;
            this.radgrpbxHeightWeightUnits.HeaderImageKey = "";
            this.radgrpbxHeightWeightUnits.HeaderMargin = new System.Windows.Forms.Padding(0);
            this.radgrpbxHeightWeightUnits.HeaderText = "Height and Weight Units";
            this.radgrpbxHeightWeightUnits.Location = new System.Drawing.Point(15, 85);
            this.radgrpbxHeightWeightUnits.Name = "radgrpbxHeightWeightUnits";
            this.radgrpbxHeightWeightUnits.Padding = new System.Windows.Forms.Padding(10, 20, 10, 10);
            // 
            // 
            // 
            this.radgrpbxHeightWeightUnits.RootElement.Padding = new System.Windows.Forms.Padding(10, 20, 10, 10);
            this.radgrpbxHeightWeightUnits.Size = new System.Drawing.Size(228, 82);
            this.radgrpbxHeightWeightUnits.TabIndex = 2;
            this.radgrpbxHeightWeightUnits.Text = "Height and Weight Units";
            ((Telerik.WinControls.Primitives.FillPrimitive)(this.radgrpbxHeightWeightUnits.GetChildAt(0).GetChildAt(0).GetChildAt(0))).BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(142)))), ((int)(((byte)(150)))), ((int)(((byte)(186)))));
            ((Telerik.WinControls.Primitives.BorderPrimitive)(this.radgrpbxHeightWeightUnits.GetChildAt(0).GetChildAt(0).GetChildAt(1))).ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(185)))), ((int)(((byte)(199)))), ((int)(((byte)(220)))));
            ((Telerik.WinControls.UI.GroupBoxHeader)(this.radgrpbxHeightWeightUnits.GetChildAt(0).GetChildAt(1))).ForeColor = System.Drawing.Color.WhiteSmoke;
            ((Telerik.WinControls.Primitives.FillPrimitive)(this.radgrpbxHeightWeightUnits.GetChildAt(0).GetChildAt(1).GetChildAt(0))).BackColor2 = System.Drawing.Color.FromArgb(((int)(((byte)(142)))), ((int)(((byte)(150)))), ((int)(((byte)(186)))));
            ((Telerik.WinControls.Primitives.FillPrimitive)(this.radgrpbxHeightWeightUnits.GetChildAt(0).GetChildAt(1).GetChildAt(0))).BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(142)))), ((int)(((byte)(150)))), ((int)(((byte)(186)))));
            ((Telerik.WinControls.Primitives.BorderPrimitive)(this.radgrpbxHeightWeightUnits.GetChildAt(0).GetChildAt(1).GetChildAt(1))).Width = 0F;
            // 
            // tableLayoutPanel2
            // 
            this.tableLayoutPanel2.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(142)))), ((int)(((byte)(150)))), ((int)(((byte)(186)))));
            this.tableLayoutPanel2.ColumnCount = 1;
            this.tableLayoutPanel2.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 50F));
            this.tableLayoutPanel2.Controls.Add(this.radradiobtnImperial, 0, 1);
            this.tableLayoutPanel2.Controls.Add(this.radradiobtnMetric, 0, 0);
            this.tableLayoutPanel2.Location = new System.Drawing.Point(17, 23);
            this.tableLayoutPanel2.Name = "tableLayoutPanel2";
            this.tableLayoutPanel2.RowCount = 2;
            this.tableLayoutPanel2.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 48.93617F));
            this.tableLayoutPanel2.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 51.06383F));
            this.tableLayoutPanel2.Size = new System.Drawing.Size(189, 47);
            this.tableLayoutPanel2.TabIndex = 2;
            // 
            // radradiobtnImperial
            // 
            this.radradiobtnImperial.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(142)))), ((int)(((byte)(150)))), ((int)(((byte)(186)))));
            this.radradiobtnImperial.Font = new System.Drawing.Font("Arial", 11.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.radradiobtnImperial.ForeColor = System.Drawing.Color.WhiteSmoke;
            this.radradiobtnImperial.Location = new System.Drawing.Point(3, 25);
            this.radradiobtnImperial.Name = "radradiobtnImperial";
            // 
            // 
            // 
            this.radradiobtnImperial.RootElement.ForeColor = System.Drawing.Color.WhiteSmoke;
            this.radradiobtnImperial.Size = new System.Drawing.Size(137, 19);
            this.radradiobtnImperial.TabIndex = 3;
            this.radradiobtnImperial.Text = "Imperial";
            this.radradiobtnImperial.MouseClick += new System.Windows.Forms.MouseEventHandler(this.radchkbxPatientPrivacy_MouseClick);
            this.radradiobtnImperial.Click += new System.EventHandler(this.radradiobtnImperial_Click);
            // 
            // radradiobtnMetric
            // 
            this.radradiobtnMetric.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(142)))), ((int)(((byte)(150)))), ((int)(((byte)(186)))));
            this.radradiobtnMetric.Font = new System.Drawing.Font("Arial", 11.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.radradiobtnMetric.ForeColor = System.Drawing.Color.WhiteSmoke;
            this.radradiobtnMetric.Location = new System.Drawing.Point(3, 3);
            this.radradiobtnMetric.Name = "radradiobtnMetric";
            // 
            // 
            // 
            this.radradiobtnMetric.RootElement.ForeColor = System.Drawing.Color.WhiteSmoke;
            this.radradiobtnMetric.Size = new System.Drawing.Size(137, 16);
            this.radradiobtnMetric.TabIndex = 2;
            this.radradiobtnMetric.Text = "Metric";
            this.radradiobtnMetric.Click += new System.EventHandler(this.radradiobtnImperial_Click);
            // 
            // radgrpbxSetupScreen
            // 
            this.radgrpbxSetupScreen.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(142)))), ((int)(((byte)(150)))), ((int)(((byte)(186)))));
            this.radgrpbxSetupScreen.Controls.Add(this.radchkbxPatientPrivacy);
            this.radgrpbxSetupScreen.Font = new System.Drawing.Font("Arial", 11.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.radgrpbxSetupScreen.FooterImageIndex = -1;
            this.radgrpbxSetupScreen.FooterImageKey = "";
            this.radgrpbxSetupScreen.HeaderImageIndex = -1;
            this.radgrpbxSetupScreen.HeaderImageKey = "";
            this.radgrpbxSetupScreen.HeaderMargin = new System.Windows.Forms.Padding(0);
            this.radgrpbxSetupScreen.HeaderText = "Setup Screen";
            this.radgrpbxSetupScreen.Location = new System.Drawing.Point(15, 16);
            this.radgrpbxSetupScreen.Name = "radgrpbxSetupScreen";
            this.radgrpbxSetupScreen.Padding = new System.Windows.Forms.Padding(10, 20, 10, 10);
            // 
            // 
            // 
            this.radgrpbxSetupScreen.RootElement.Padding = new System.Windows.Forms.Padding(10, 20, 10, 10);
            this.radgrpbxSetupScreen.Size = new System.Drawing.Size(228, 62);
            this.radgrpbxSetupScreen.TabIndex = 1;
            this.radgrpbxSetupScreen.Text = "Setup Screen";
            ((Telerik.WinControls.UI.RadGroupBoxElement)(this.radgrpbxSetupScreen.GetChildAt(0))).BorderBoxStyle = Telerik.WinControls.BorderBoxStyle.FourBorders;
            ((Telerik.WinControls.UI.RadGroupBoxElement)(this.radgrpbxSetupScreen.GetChildAt(0))).BorderBottomColor = System.Drawing.SystemColors.ControlDark;
            ((Telerik.WinControls.Primitives.FillPrimitive)(this.radgrpbxSetupScreen.GetChildAt(0).GetChildAt(0).GetChildAt(0))).BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(142)))), ((int)(((byte)(150)))), ((int)(((byte)(186)))));
            ((Telerik.WinControls.Primitives.BorderPrimitive)(this.radgrpbxSetupScreen.GetChildAt(0).GetChildAt(0).GetChildAt(1))).ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(185)))), ((int)(((byte)(199)))), ((int)(((byte)(220)))));
            ((Telerik.WinControls.Primitives.BorderPrimitive)(this.radgrpbxSetupScreen.GetChildAt(0).GetChildAt(0).GetChildAt(1))).BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(142)))), ((int)(((byte)(150)))), ((int)(((byte)(186)))));
            ((Telerik.WinControls.UI.GroupBoxHeader)(this.radgrpbxSetupScreen.GetChildAt(0).GetChildAt(1))).ForeColor = System.Drawing.Color.WhiteSmoke;
            ((Telerik.WinControls.Primitives.FillPrimitive)(this.radgrpbxSetupScreen.GetChildAt(0).GetChildAt(1).GetChildAt(0))).BackColor2 = System.Drawing.Color.FromArgb(((int)(((byte)(142)))), ((int)(((byte)(150)))), ((int)(((byte)(186)))));
            ((Telerik.WinControls.Primitives.FillPrimitive)(this.radgrpbxSetupScreen.GetChildAt(0).GetChildAt(1).GetChildAt(0))).ForeColor = System.Drawing.Color.WhiteSmoke;
            ((Telerik.WinControls.Primitives.FillPrimitive)(this.radgrpbxSetupScreen.GetChildAt(0).GetChildAt(1).GetChildAt(0))).BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(142)))), ((int)(((byte)(150)))), ((int)(((byte)(186)))));
            ((Telerik.WinControls.Primitives.BorderPrimitive)(this.radgrpbxSetupScreen.GetChildAt(0).GetChildAt(1).GetChildAt(1))).Width = 0F;
            ((Telerik.WinControls.Primitives.BorderPrimitive)(this.radgrpbxSetupScreen.GetChildAt(0).GetChildAt(1).GetChildAt(1))).BottomColor = System.Drawing.SystemColors.ControlDark;
            // 
            // radchkbxPatientPrivacy
            // 
            this.radchkbxPatientPrivacy.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(142)))), ((int)(((byte)(150)))), ((int)(((byte)(186)))));
            this.radchkbxPatientPrivacy.Font = new System.Drawing.Font("Arial", 11.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.radchkbxPatientPrivacy.ForeColor = System.Drawing.Color.WhiteSmoke;
            this.radchkbxPatientPrivacy.Location = new System.Drawing.Point(17, 28);
            this.radchkbxPatientPrivacy.Name = "radchkbxPatientPrivacy";
            // 
            // 
            // 
            this.radchkbxPatientPrivacy.RootElement.ForeColor = System.Drawing.Color.WhiteSmoke;
            this.radchkbxPatientPrivacy.Size = new System.Drawing.Size(125, 21);
            this.radchkbxPatientPrivacy.TabIndex = 1;
            this.radchkbxPatientPrivacy.Text = "Patient Privacy";
            this.radchkbxPatientPrivacy.MouseClick += new System.Windows.Forms.MouseEventHandler(this.radchkbxPatientPrivacy_MouseClick);
            // 
            // documentContainer1
            // 
            this.documentContainer1.CausesValidation = false;
            this.documentContainer1.Controls.Add(this.documentTabStrip1);
            this.documentContainer1.Location = new System.Drawing.Point(0, 0);
            this.documentContainer1.Name = "documentContainer1";
            // 
            // 
            // 
            this.documentContainer1.RootElement.MinSize = new System.Drawing.Size(25, 25);
            this.documentContainer1.Size = new System.Drawing.Size(552, 411);
            this.documentContainer1.SizeInfo.SizeMode = Telerik.WinControls.UI.Docking.SplitPanelSizeMode.Fill;
            this.documentContainer1.SplitterWidth = 4;
            this.documentContainer1.TabIndex = 0;
            this.documentContainer1.TabStop = false;
            // 
            // documentTabStrip1
            // 
            this.documentTabStrip1.CausesValidation = false;
            this.documentTabStrip1.Controls.Add(this.docWndGeneralSettings);
            this.documentTabStrip1.Controls.Add(this.docWndPWVSettings);
            this.documentTabStrip1.Controls.Add(this.docWndPWASettings);
            this.documentTabStrip1.Controls.Add(this.documentWindow4);
            this.documentTabStrip1.Font = new System.Drawing.Font("Arial", 11.25F);
            this.documentTabStrip1.Location = new System.Drawing.Point(0, 0);
            this.documentTabStrip1.Name = "documentTabStrip1";
            // 
            // 
            // 
            this.documentTabStrip1.RootElement.MinSize = new System.Drawing.Size(25, 25);
            this.documentTabStrip1.SelectedIndex = 1;
            this.documentTabStrip1.ShowItemToolTips = false;
            this.documentTabStrip1.Size = new System.Drawing.Size(552, 411);
            this.documentTabStrip1.TabIndex = 0;
            this.documentTabStrip1.TabStop = false;
            ((Telerik.WinControls.Primitives.FillPrimitive)(this.documentTabStrip1.GetChildAt(0).GetChildAt(0))).BackColor2 = System.Drawing.Color.FromArgb(((int)(((byte)(142)))), ((int)(((byte)(150)))), ((int)(((byte)(186)))));
            ((Telerik.WinControls.Primitives.FillPrimitive)(this.documentTabStrip1.GetChildAt(0).GetChildAt(0))).BackColor3 = System.Drawing.Color.FromArgb(((int)(((byte)(142)))), ((int)(((byte)(150)))), ((int)(((byte)(186)))));
            ((Telerik.WinControls.Primitives.FillPrimitive)(this.documentTabStrip1.GetChildAt(0).GetChildAt(0))).BackColor4 = System.Drawing.Color.FromArgb(((int)(((byte)(142)))), ((int)(((byte)(150)))), ((int)(((byte)(186)))));
            ((Telerik.WinControls.Primitives.FillPrimitive)(this.documentTabStrip1.GetChildAt(0).GetChildAt(0))).Font = new System.Drawing.Font("Arial", 11.25F, System.Drawing.FontStyle.Bold);
            ((Telerik.WinControls.UI.RadTabStripElement)(this.documentTabStrip1.GetChildAt(0).GetChildAt(2))).SeparatorColor = System.Drawing.Color.FromArgb(((int)(((byte)(142)))), ((int)(((byte)(150)))), ((int)(((byte)(186)))));
            ((Telerik.WinControls.UI.RadTabStripElement)(this.documentTabStrip1.GetChildAt(0).GetChildAt(2))).AllowDragDrop = false;
            ((Telerik.WinControls.UI.TabLayoutPanel)(this.documentTabStrip1.GetChildAt(0).GetChildAt(2).GetChildAt(0).GetChildAt(0))).AutoSize = true;
            ((Telerik.WinControls.Layouts.BoxLayout)(this.documentTabStrip1.GetChildAt(0).GetChildAt(2).GetChildAt(0).GetChildAt(0).GetChildAt(0))).StretchVertically = false;
            ((Telerik.WinControls.UI.TabStripItem)(this.documentTabStrip1.GetChildAt(0).GetChildAt(2).GetChildAt(0).GetChildAt(0).GetChildAt(0).GetChildAt(0))).Text = "General Settings";
            ((Telerik.WinControls.UI.TabStripItem)(this.documentTabStrip1.GetChildAt(0).GetChildAt(2).GetChildAt(0).GetChildAt(0).GetChildAt(0).GetChildAt(0))).ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(23)))), ((int)(((byte)(29)))), ((int)(((byte)(55)))));
            ((Telerik.WinControls.UI.TabStripItem)(this.documentTabStrip1.GetChildAt(0).GetChildAt(2).GetChildAt(0).GetChildAt(0).GetChildAt(0).GetChildAt(0))).Alignment = System.Drawing.ContentAlignment.BottomLeft;
            ((Telerik.WinControls.UI.TabStripItem)(this.documentTabStrip1.GetChildAt(0).GetChildAt(2).GetChildAt(0).GetChildAt(0).GetChildAt(0).GetChildAt(0))).StretchHorizontally = false;
            ((Telerik.WinControls.Primitives.FillPrimitive)(this.documentTabStrip1.GetChildAt(0).GetChildAt(2).GetChildAt(0).GetChildAt(0).GetChildAt(0).GetChildAt(0).GetChildAt(0))).BackColor2 = System.Drawing.Color.FromArgb(((int)(((byte)(233)))), ((int)(((byte)(240)))), ((int)(((byte)(249)))));
            ((Telerik.WinControls.Primitives.FillPrimitive)(this.documentTabStrip1.GetChildAt(0).GetChildAt(2).GetChildAt(0).GetChildAt(0).GetChildAt(0).GetChildAt(0).GetChildAt(0))).BackColor3 = System.Drawing.Color.FromArgb(((int)(((byte)(216)))), ((int)(((byte)(230)))), ((int)(((byte)(249)))));
            ((Telerik.WinControls.Primitives.FillPrimitive)(this.documentTabStrip1.GetChildAt(0).GetChildAt(2).GetChildAt(0).GetChildAt(0).GetChildAt(0).GetChildAt(0).GetChildAt(0))).BackColor4 = System.Drawing.Color.FromArgb(((int)(((byte)(142)))), ((int)(((byte)(150)))), ((int)(((byte)(186)))));
            ((Telerik.WinControls.Primitives.FillPrimitive)(this.documentTabStrip1.GetChildAt(0).GetChildAt(2).GetChildAt(0).GetChildAt(0).GetChildAt(0).GetChildAt(0).GetChildAt(0))).BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(142)))), ((int)(((byte)(150)))), ((int)(((byte)(186)))));
            ((Telerik.WinControls.Primitives.BorderPrimitive)(this.documentTabStrip1.GetChildAt(0).GetChildAt(2).GetChildAt(0).GetChildAt(0).GetChildAt(0).GetChildAt(0).GetChildAt(1))).InnerColor = System.Drawing.Color.FromArgb(((int)(((byte)(142)))), ((int)(((byte)(150)))), ((int)(((byte)(186)))));
            ((Telerik.WinControls.Primitives.BorderPrimitive)(this.documentTabStrip1.GetChildAt(0).GetChildAt(2).GetChildAt(0).GetChildAt(0).GetChildAt(0).GetChildAt(0).GetChildAt(1))).ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(142)))), ((int)(((byte)(150)))), ((int)(((byte)(186)))));
            ((Telerik.WinControls.UI.TabStripItem)(this.documentTabStrip1.GetChildAt(0).GetChildAt(2).GetChildAt(0).GetChildAt(0).GetChildAt(0).GetChildAt(1))).Text = "PWV Settings";
            ((Telerik.WinControls.UI.TabStripItem)(this.documentTabStrip1.GetChildAt(0).GetChildAt(2).GetChildAt(0).GetChildAt(0).GetChildAt(0).GetChildAt(1))).ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(29)))), ((int)(((byte)(30)))), ((int)(((byte)(55)))));
            ((Telerik.WinControls.UI.TabStripItem)(this.documentTabStrip1.GetChildAt(0).GetChildAt(2).GetChildAt(0).GetChildAt(0).GetChildAt(0).GetChildAt(1))).Font = new System.Drawing.Font("Arial", 11.25F, System.Drawing.FontStyle.Bold);
            ((Telerik.WinControls.UI.TabStripItem)(this.documentTabStrip1.GetChildAt(0).GetChildAt(2).GetChildAt(0).GetChildAt(0).GetChildAt(0).GetChildAt(1))).Alignment = System.Drawing.ContentAlignment.BottomLeft;
            ((Telerik.WinControls.UI.TabStripItem)(this.documentTabStrip1.GetChildAt(0).GetChildAt(2).GetChildAt(0).GetChildAt(0).GetChildAt(0).GetChildAt(1))).StretchHorizontally = false;
            ((Telerik.WinControls.Primitives.FillPrimitive)(this.documentTabStrip1.GetChildAt(0).GetChildAt(2).GetChildAt(0).GetChildAt(0).GetChildAt(0).GetChildAt(1).GetChildAt(0))).BackColor2 = System.Drawing.Color.FromArgb(((int)(((byte)(233)))), ((int)(((byte)(240)))), ((int)(((byte)(249)))));
            ((Telerik.WinControls.Primitives.FillPrimitive)(this.documentTabStrip1.GetChildAt(0).GetChildAt(2).GetChildAt(0).GetChildAt(0).GetChildAt(0).GetChildAt(1).GetChildAt(0))).BackColor3 = System.Drawing.Color.FromArgb(((int)(((byte)(216)))), ((int)(((byte)(230)))), ((int)(((byte)(249)))));
            ((Telerik.WinControls.Primitives.FillPrimitive)(this.documentTabStrip1.GetChildAt(0).GetChildAt(2).GetChildAt(0).GetChildAt(0).GetChildAt(0).GetChildAt(1).GetChildAt(0))).BackColor4 = System.Drawing.Color.FromArgb(((int)(((byte)(142)))), ((int)(((byte)(150)))), ((int)(((byte)(186)))));
            ((Telerik.WinControls.Primitives.FillPrimitive)(this.documentTabStrip1.GetChildAt(0).GetChildAt(2).GetChildAt(0).GetChildAt(0).GetChildAt(0).GetChildAt(1).GetChildAt(0))).ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(23)))), ((int)(((byte)(29)))), ((int)(((byte)(55)))));
            ((Telerik.WinControls.Primitives.FillPrimitive)(this.documentTabStrip1.GetChildAt(0).GetChildAt(2).GetChildAt(0).GetChildAt(0).GetChildAt(0).GetChildAt(1).GetChildAt(0))).BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(142)))), ((int)(((byte)(150)))), ((int)(((byte)(186)))));
            ((Telerik.WinControls.Primitives.BorderPrimitive)(this.documentTabStrip1.GetChildAt(0).GetChildAt(2).GetChildAt(0).GetChildAt(0).GetChildAt(0).GetChildAt(1).GetChildAt(1))).InnerColor = System.Drawing.Color.FromArgb(((int)(((byte)(142)))), ((int)(((byte)(150)))), ((int)(((byte)(186)))));
            ((Telerik.WinControls.Primitives.BorderPrimitive)(this.documentTabStrip1.GetChildAt(0).GetChildAt(2).GetChildAt(0).GetChildAt(0).GetChildAt(0).GetChildAt(1).GetChildAt(1))).ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(142)))), ((int)(((byte)(150)))), ((int)(((byte)(186)))));
            ((Telerik.WinControls.UI.TabStripItem)(this.documentTabStrip1.GetChildAt(0).GetChildAt(2).GetChildAt(0).GetChildAt(0).GetChildAt(0).GetChildAt(2))).Text = "PWA Settings";
            ((Telerik.WinControls.UI.TabStripItem)(this.documentTabStrip1.GetChildAt(0).GetChildAt(2).GetChildAt(0).GetChildAt(0).GetChildAt(0).GetChildAt(2))).ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(23)))), ((int)(((byte)(29)))), ((int)(((byte)(55)))));
            ((Telerik.WinControls.UI.TabStripItem)(this.documentTabStrip1.GetChildAt(0).GetChildAt(2).GetChildAt(0).GetChildAt(0).GetChildAt(0).GetChildAt(2))).Alignment = System.Drawing.ContentAlignment.BottomLeft;
            ((Telerik.WinControls.UI.TabStripItem)(this.documentTabStrip1.GetChildAt(0).GetChildAt(2).GetChildAt(0).GetChildAt(0).GetChildAt(0).GetChildAt(2))).StretchHorizontally = false;
            ((Telerik.WinControls.Primitives.FillPrimitive)(this.documentTabStrip1.GetChildAt(0).GetChildAt(2).GetChildAt(0).GetChildAt(0).GetChildAt(0).GetChildAt(2).GetChildAt(0))).BackColor2 = System.Drawing.Color.FromArgb(((int)(((byte)(233)))), ((int)(((byte)(240)))), ((int)(((byte)(249)))));
            ((Telerik.WinControls.Primitives.FillPrimitive)(this.documentTabStrip1.GetChildAt(0).GetChildAt(2).GetChildAt(0).GetChildAt(0).GetChildAt(0).GetChildAt(2).GetChildAt(0))).BackColor3 = System.Drawing.Color.FromArgb(((int)(((byte)(216)))), ((int)(((byte)(230)))), ((int)(((byte)(249)))));
            ((Telerik.WinControls.Primitives.FillPrimitive)(this.documentTabStrip1.GetChildAt(0).GetChildAt(2).GetChildAt(0).GetChildAt(0).GetChildAt(0).GetChildAt(2).GetChildAt(0))).BackColor4 = System.Drawing.Color.FromArgb(((int)(((byte)(142)))), ((int)(((byte)(150)))), ((int)(((byte)(186)))));
            ((Telerik.WinControls.Primitives.FillPrimitive)(this.documentTabStrip1.GetChildAt(0).GetChildAt(2).GetChildAt(0).GetChildAt(0).GetChildAt(0).GetChildAt(2).GetChildAt(0))).BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(142)))), ((int)(((byte)(150)))), ((int)(((byte)(186)))));
            ((Telerik.WinControls.Primitives.BorderPrimitive)(this.documentTabStrip1.GetChildAt(0).GetChildAt(2).GetChildAt(0).GetChildAt(0).GetChildAt(0).GetChildAt(2).GetChildAt(1))).InnerColor = System.Drawing.Color.FromArgb(((int)(((byte)(142)))), ((int)(((byte)(150)))), ((int)(((byte)(186)))));
            ((Telerik.WinControls.Primitives.BorderPrimitive)(this.documentTabStrip1.GetChildAt(0).GetChildAt(2).GetChildAt(0).GetChildAt(0).GetChildAt(0).GetChildAt(2).GetChildAt(1))).ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(142)))), ((int)(((byte)(150)))), ((int)(((byte)(186)))));
            ((Telerik.WinControls.Primitives.BorderPrimitive)(this.documentTabStrip1.GetChildAt(0).GetChildAt(2).GetChildAt(0).GetChildAt(0).GetChildAt(0).GetChildAt(2).GetChildAt(1))).Font = new System.Drawing.Font("Arial", 11.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            ((Telerik.WinControls.UI.TabStripItem)(this.documentTabStrip1.GetChildAt(0).GetChildAt(2).GetChildAt(0).GetChildAt(0).GetChildAt(0).GetChildAt(3))).Text = "BP Settings";
            ((Telerik.WinControls.UI.TabStripItem)(this.documentTabStrip1.GetChildAt(0).GetChildAt(2).GetChildAt(0).GetChildAt(0).GetChildAt(0).GetChildAt(3))).ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(23)))), ((int)(((byte)(29)))), ((int)(((byte)(55)))));
            ((Telerik.WinControls.UI.TabStripItem)(this.documentTabStrip1.GetChildAt(0).GetChildAt(2).GetChildAt(0).GetChildAt(0).GetChildAt(0).GetChildAt(3))).Font = new System.Drawing.Font("Arial", 11.25F, System.Drawing.FontStyle.Bold);
            ((Telerik.WinControls.UI.TabStripItem)(this.documentTabStrip1.GetChildAt(0).GetChildAt(2).GetChildAt(0).GetChildAt(0).GetChildAt(0).GetChildAt(3))).Alignment = System.Drawing.ContentAlignment.BottomLeft;
            ((Telerik.WinControls.UI.TabStripItem)(this.documentTabStrip1.GetChildAt(0).GetChildAt(2).GetChildAt(0).GetChildAt(0).GetChildAt(0).GetChildAt(3))).StretchHorizontally = false;
            ((Telerik.WinControls.Primitives.FillPrimitive)(this.documentTabStrip1.GetChildAt(0).GetChildAt(2).GetChildAt(0).GetChildAt(0).GetChildAt(0).GetChildAt(3).GetChildAt(0))).BackColor2 = System.Drawing.Color.FromArgb(((int)(((byte)(233)))), ((int)(((byte)(240)))), ((int)(((byte)(249)))));
            ((Telerik.WinControls.Primitives.FillPrimitive)(this.documentTabStrip1.GetChildAt(0).GetChildAt(2).GetChildAt(0).GetChildAt(0).GetChildAt(0).GetChildAt(3).GetChildAt(0))).BackColor3 = System.Drawing.Color.FromArgb(((int)(((byte)(216)))), ((int)(((byte)(230)))), ((int)(((byte)(249)))));
            ((Telerik.WinControls.Primitives.FillPrimitive)(this.documentTabStrip1.GetChildAt(0).GetChildAt(2).GetChildAt(0).GetChildAt(0).GetChildAt(0).GetChildAt(3).GetChildAt(0))).BackColor4 = System.Drawing.Color.FromArgb(((int)(((byte)(142)))), ((int)(((byte)(150)))), ((int)(((byte)(186)))));
            ((Telerik.WinControls.Primitives.FillPrimitive)(this.documentTabStrip1.GetChildAt(0).GetChildAt(2).GetChildAt(0).GetChildAt(0).GetChildAt(0).GetChildAt(3).GetChildAt(0))).BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(142)))), ((int)(((byte)(150)))), ((int)(((byte)(186)))));
            ((Telerik.WinControls.Primitives.FillPrimitive)(this.documentTabStrip1.GetChildAt(0).GetChildAt(2).GetChildAt(0).GetChildAt(0).GetChildAt(0).GetChildAt(3).GetChildAt(0))).Font = new System.Drawing.Font("Arial", 11.25F);
            ((Telerik.WinControls.Primitives.BorderPrimitive)(this.documentTabStrip1.GetChildAt(0).GetChildAt(2).GetChildAt(0).GetChildAt(0).GetChildAt(0).GetChildAt(3).GetChildAt(1))).InnerColor = System.Drawing.Color.FromArgb(((int)(((byte)(142)))), ((int)(((byte)(150)))), ((int)(((byte)(186)))));
            ((Telerik.WinControls.Primitives.BorderPrimitive)(this.documentTabStrip1.GetChildAt(0).GetChildAt(2).GetChildAt(0).GetChildAt(0).GetChildAt(0).GetChildAt(3).GetChildAt(1))).ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(142)))), ((int)(((byte)(150)))), ((int)(((byte)(186)))));
            ((Telerik.WinControls.Primitives.BorderPrimitive)(this.documentTabStrip1.GetChildAt(0).GetChildAt(2).GetChildAt(0).GetChildAt(0).GetChildAt(0).GetChildAt(3).GetChildAt(1))).Font = new System.Drawing.Font("Arial", 11.25F);
            ((Telerik.WinControls.Layouts.ImageAndTextLayoutPanel)(this.documentTabStrip1.GetChildAt(0).GetChildAt(2).GetChildAt(0).GetChildAt(0).GetChildAt(0).GetChildAt(3).GetChildAt(2))).StretchHorizontally = false;
            ((Telerik.WinControls.UI.RadImageButtonElement)(this.documentTabStrip1.GetChildAt(0).GetChildAt(2).GetChildAt(0).GetChildAt(0).GetChildAt(0).GetChildAt(3).GetChildAt(3))).Visibility = Telerik.WinControls.ElementVisibility.Collapsed;
            ((Telerik.WinControls.Primitives.FocusPrimitive)(this.documentTabStrip1.GetChildAt(0).GetChildAt(2).GetChildAt(0).GetChildAt(0).GetChildAt(0).GetChildAt(3).GetChildAt(3).GetChildAt(3))).Font = new System.Drawing.Font("Arial", 11.25F, System.Drawing.FontStyle.Bold);
            ((Telerik.WinControls.Primitives.FillPrimitive)(this.documentTabStrip1.GetChildAt(0).GetChildAt(2).GetChildAt(0).GetChildAt(1))).BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(169)))), ((int)(((byte)(177)))), ((int)(((byte)(211)))));
            ((Telerik.WinControls.Primitives.BorderPrimitive)(this.documentTabStrip1.GetChildAt(0).GetChildAt(2).GetChildAt(0).GetChildAt(1).GetChildAt(0))).ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(142)))), ((int)(((byte)(150)))), ((int)(((byte)(186)))));
            ((Telerik.WinControls.Primitives.BorderPrimitive)(this.documentTabStrip1.GetChildAt(0).GetChildAt(2).GetChildAt(0).GetChildAt(1).GetChildAt(0))).BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(142)))), ((int)(((byte)(150)))), ((int)(((byte)(186)))));
            ((Telerik.WinControls.UI.RadButtonElement)(this.documentTabStrip1.GetChildAt(0).GetChildAt(3).GetChildAt(0))).Enabled = false;
            ((Telerik.WinControls.UI.RadButtonElement)(this.documentTabStrip1.GetChildAt(0).GetChildAt(3).GetChildAt(0))).Visibility = Telerik.WinControls.ElementVisibility.Collapsed;
            ((Telerik.WinControls.UI.OverflowDropDownButtonElement)(this.documentTabStrip1.GetChildAt(0).GetChildAt(3).GetChildAt(1))).OverflowMode = false;
            ((Telerik.WinControls.UI.OverflowDropDownButtonElement)(this.documentTabStrip1.GetChildAt(0).GetChildAt(3).GetChildAt(1))).Enabled = false;
            ((Telerik.WinControls.UI.OverflowDropDownButtonElement)(this.documentTabStrip1.GetChildAt(0).GetChildAt(3).GetChildAt(1))).Visibility = Telerik.WinControls.ElementVisibility.Collapsed;
            ((Telerik.WinControls.UI.ActionButtonElement)(this.documentTabStrip1.GetChildAt(0).GetChildAt(3).GetChildAt(1).GetChildAt(1).GetChildAt(1))).Visibility = Telerik.WinControls.ElementVisibility.Hidden;
            // 
            // docWndPWVSettings
            // 
            this.docWndPWVSettings.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(142)))), ((int)(((byte)(150)))), ((int)(((byte)(186)))));
            this.docWndPWVSettings.Controls.Add(this.radgrpbxCaptureGuide);
            this.docWndPWVSettings.Controls.Add(this.radgrpbxDefaultReport);
            this.docWndPWVSettings.Controls.Add(this.guiradgrpDefaultReport);
            this.docWndPWVSettings.Controls.Add(this.radgrpbxSimulationTypes);
            this.docWndPWVSettings.Controls.Add(this.radgrpSimulationFiles);
            this.docWndPWVSettings.Controls.Add(this.radgrpCaptureTime);
            this.docWndPWVSettings.Controls.Add(this.radgrpReportScreen);
            this.docWndPWVSettings.Controls.Add(this.radgrpPwvDistanceUnits);
            this.docWndPWVSettings.Controls.Add(this.radgrpCuffLocation);
            this.docWndPWVSettings.Controls.Add(this.radgrpbxPwvDistanceMethod);
            this.docWndPWVSettings.DocumentButtons = Telerik.WinControls.UI.Docking.DocumentStripButtons.None;
            this.docWndPWVSettings.Font = new System.Drawing.Font("Verdana", 8.25F);
            this.docWndPWVSettings.Location = new System.Drawing.Point(6, 33);
            this.docWndPWVSettings.Name = "docWndPWVSettings";
            this.docWndPWVSettings.Size = new System.Drawing.Size(540, 372);
            this.docWndPWVSettings.Text = "PWV Settings";
            // 
            // radgrpbxCaptureGuide
            // 
            this.radgrpbxCaptureGuide.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(142)))), ((int)(((byte)(150)))), ((int)(((byte)(186)))));
            this.radgrpbxCaptureGuide.Controls.Add(this.tableLayoutPanel13);
            this.radgrpbxCaptureGuide.Font = new System.Drawing.Font("Arial", 11.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.radgrpbxCaptureGuide.FooterImageIndex = -1;
            this.radgrpbxCaptureGuide.FooterImageKey = "";
            this.radgrpbxCaptureGuide.HeaderImageIndex = -1;
            this.radgrpbxCaptureGuide.HeaderImageKey = "";
            this.radgrpbxCaptureGuide.HeaderMargin = new System.Windows.Forms.Padding(0);
            this.radgrpbxCaptureGuide.HeaderText = "Capture Guide";
            this.radgrpbxCaptureGuide.Location = new System.Drawing.Point(283, 84);
            this.radgrpbxCaptureGuide.Name = "radgrpbxCaptureGuide";
            this.radgrpbxCaptureGuide.Padding = new System.Windows.Forms.Padding(10, 20, 10, 10);
            // 
            // 
            // 
            this.radgrpbxCaptureGuide.RootElement.Padding = new System.Windows.Forms.Padding(10, 20, 10, 10);
            this.radgrpbxCaptureGuide.Size = new System.Drawing.Size(242, 90);
            this.radgrpbxCaptureGuide.TabIndex = 5;
            this.radgrpbxCaptureGuide.Text = "Capture Guide";
            ((Telerik.WinControls.Primitives.FillPrimitive)(this.radgrpbxCaptureGuide.GetChildAt(0).GetChildAt(0).GetChildAt(0))).BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(142)))), ((int)(((byte)(150)))), ((int)(((byte)(186)))));
            ((Telerik.WinControls.Primitives.BorderPrimitive)(this.radgrpbxCaptureGuide.GetChildAt(0).GetChildAt(0).GetChildAt(1))).ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(185)))), ((int)(((byte)(199)))), ((int)(((byte)(220)))));
            ((Telerik.WinControls.UI.GroupBoxHeader)(this.radgrpbxCaptureGuide.GetChildAt(0).GetChildAt(1))).ForeColor = System.Drawing.Color.WhiteSmoke;
            ((Telerik.WinControls.Primitives.FillPrimitive)(this.radgrpbxCaptureGuide.GetChildAt(0).GetChildAt(1).GetChildAt(0))).BackColor2 = System.Drawing.Color.FromArgb(((int)(((byte)(142)))), ((int)(((byte)(150)))), ((int)(((byte)(186)))));
            ((Telerik.WinControls.Primitives.FillPrimitive)(this.radgrpbxCaptureGuide.GetChildAt(0).GetChildAt(1).GetChildAt(0))).BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(142)))), ((int)(((byte)(150)))), ((int)(((byte)(186)))));
            ((Telerik.WinControls.Primitives.BorderPrimitive)(this.radgrpbxCaptureGuide.GetChildAt(0).GetChildAt(1).GetChildAt(1))).Width = 0F;
            // 
            // tableLayoutPanel13
            // 
            this.tableLayoutPanel13.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(142)))), ((int)(((byte)(150)))), ((int)(((byte)(186)))));
            this.tableLayoutPanel13.ColumnCount = 1;
            this.tableLayoutPanel13.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 50F));
            this.tableLayoutPanel13.Controls.Add(this.radchkAutoInflate, 0, 0);
            this.tableLayoutPanel13.Controls.Add(this.radchkAutoCapture, 0, 1);
            this.tableLayoutPanel13.Location = new System.Drawing.Point(18, 25);
            this.tableLayoutPanel13.Name = "tableLayoutPanel13";
            this.tableLayoutPanel13.RowCount = 2;
            this.tableLayoutPanel13.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 49.0566F));
            this.tableLayoutPanel13.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 50.9434F));
            this.tableLayoutPanel13.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Absolute, 20F));
            this.tableLayoutPanel13.Size = new System.Drawing.Size(189, 54);
            this.tableLayoutPanel13.TabIndex = 5;
            // 
            // radchkAutoInflate
            // 
            this.radchkAutoInflate.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(142)))), ((int)(((byte)(150)))), ((int)(((byte)(186)))));
            this.radchkAutoInflate.Font = new System.Drawing.Font("Arial", 11.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.radchkAutoInflate.ForeColor = System.Drawing.Color.WhiteSmoke;
            this.radchkAutoInflate.Location = new System.Drawing.Point(3, 3);
            this.radchkAutoInflate.Name = "radchkAutoInflate";
            // 
            // 
            // 
            this.radchkAutoInflate.RootElement.ForeColor = System.Drawing.Color.WhiteSmoke;
            this.radchkAutoInflate.Size = new System.Drawing.Size(100, 21);
            this.radchkAutoInflate.TabIndex = 0;
            this.radchkAutoInflate.Text = "Auto Inflate";
            this.radchkAutoInflate.MouseClick += new System.Windows.Forms.MouseEventHandler(this.radchkbxPatientPrivacy_MouseClick);
            // 
            // radchkAutoCapture
            // 
            this.radchkAutoCapture.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(142)))), ((int)(((byte)(150)))), ((int)(((byte)(186)))));
            this.radchkAutoCapture.Font = new System.Drawing.Font("Arial", 11.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.radchkAutoCapture.ForeColor = System.Drawing.Color.WhiteSmoke;
            this.radchkAutoCapture.Location = new System.Drawing.Point(3, 29);
            this.radchkAutoCapture.Name = "radchkAutoCapture";
            // 
            // 
            // 
            this.radchkAutoCapture.RootElement.ForeColor = System.Drawing.Color.WhiteSmoke;
            this.radchkAutoCapture.Size = new System.Drawing.Size(113, 21);
            this.radchkAutoCapture.TabIndex = 1;
            this.radchkAutoCapture.Text = "Auto Capture";
            this.radchkAutoCapture.MouseClick += new System.Windows.Forms.MouseEventHandler(this.radchkbxPatientPrivacy_MouseClick);
            // 
            // radgrpbxDefaultReport
            // 
            this.radgrpbxDefaultReport.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(142)))), ((int)(((byte)(150)))), ((int)(((byte)(186)))));
            this.radgrpbxDefaultReport.Controls.Add(this.comboDefaultReport);
            this.radgrpbxDefaultReport.Font = new System.Drawing.Font("Arial", 11.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.radgrpbxDefaultReport.FooterImageIndex = -1;
            this.radgrpbxDefaultReport.FooterImageKey = "";
            this.radgrpbxDefaultReport.HeaderImageIndex = -1;
            this.radgrpbxDefaultReport.HeaderImageKey = "";
            this.radgrpbxDefaultReport.HeaderMargin = new System.Windows.Forms.Padding(0);
            this.radgrpbxDefaultReport.HeaderText = "Default Report";
            this.radgrpbxDefaultReport.Location = new System.Drawing.Point(10, 303);
            this.radgrpbxDefaultReport.Name = "radgrpbxDefaultReport";
            this.radgrpbxDefaultReport.Padding = new System.Windows.Forms.Padding(10, 20, 10, 10);
            // 
            // 
            // 
            this.radgrpbxDefaultReport.RootElement.Padding = new System.Windows.Forms.Padding(10, 20, 10, 10);
            this.radgrpbxDefaultReport.Size = new System.Drawing.Size(254, 54);
            this.radgrpbxDefaultReport.TabIndex = 4;
            this.radgrpbxDefaultReport.Text = "Default Report";
            ((Telerik.WinControls.Primitives.FillPrimitive)(this.radgrpbxDefaultReport.GetChildAt(0).GetChildAt(0).GetChildAt(0))).BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(142)))), ((int)(((byte)(150)))), ((int)(((byte)(186)))));
            ((Telerik.WinControls.Primitives.BorderPrimitive)(this.radgrpbxDefaultReport.GetChildAt(0).GetChildAt(0).GetChildAt(1))).ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(185)))), ((int)(((byte)(199)))), ((int)(((byte)(220)))));
            ((Telerik.WinControls.UI.GroupBoxHeader)(this.radgrpbxDefaultReport.GetChildAt(0).GetChildAt(1))).ForeColor = System.Drawing.Color.WhiteSmoke;
            ((Telerik.WinControls.Primitives.FillPrimitive)(this.radgrpbxDefaultReport.GetChildAt(0).GetChildAt(1).GetChildAt(0))).BackColor2 = System.Drawing.Color.FromArgb(((int)(((byte)(142)))), ((int)(((byte)(150)))), ((int)(((byte)(186)))));
            ((Telerik.WinControls.Primitives.FillPrimitive)(this.radgrpbxDefaultReport.GetChildAt(0).GetChildAt(1).GetChildAt(0))).BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(142)))), ((int)(((byte)(150)))), ((int)(((byte)(186)))));
            ((Telerik.WinControls.Primitives.BorderPrimitive)(this.radgrpbxDefaultReport.GetChildAt(0).GetChildAt(1).GetChildAt(1))).Width = 0F;
            // 
            // comboDefaultReport
            // 
            this.comboDefaultReport.AutoCompleteMode = System.Windows.Forms.AutoCompleteMode.Append;
            this.comboDefaultReport.AutoSize = false;
            this.comboDefaultReport.DropDownHeight = 80;
            this.comboDefaultReport.DropDownStyle = Telerik.WinControls.RadDropDownStyle.DropDownList;
            this.comboDefaultReport.Font = new System.Drawing.Font("Arial", 11.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.comboDefaultReport.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(23)))), ((int)(((byte)(29)))), ((int)(((byte)(55)))));
            this.comboDefaultReport.Location = new System.Drawing.Point(14, 23);
            this.comboDefaultReport.Name = "comboDefaultReport";
            // 
            // 
            // 
            this.comboDefaultReport.RootElement.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(23)))), ((int)(((byte)(29)))), ((int)(((byte)(55)))));
            this.comboDefaultReport.Size = new System.Drawing.Size(185, 23);
            this.comboDefaultReport.TabIndex = 0;
            this.comboDefaultReport.SelectedIndexChanged += new Telerik.WinControls.UI.Data.PositionChangedEventHandler(this.comboDefaultReport_SelectedIndexChanged);
            // 
            // guiradgrpDefaultReport
            // 
            this.guiradgrpDefaultReport.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(142)))), ((int)(((byte)(150)))), ((int)(((byte)(186)))));
            this.guiradgrpDefaultReport.Font = new System.Drawing.Font("Arial", 11.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.guiradgrpDefaultReport.FooterImageIndex = -1;
            this.guiradgrpDefaultReport.FooterImageKey = "";
            this.guiradgrpDefaultReport.HeaderImageIndex = -1;
            this.guiradgrpDefaultReport.HeaderImageKey = "";
            this.guiradgrpDefaultReport.HeaderMargin = new System.Windows.Forms.Padding(0);
            this.guiradgrpDefaultReport.HeaderText = "Default Report";
            this.guiradgrpDefaultReport.Location = new System.Drawing.Point(15, 303);
            this.guiradgrpDefaultReport.Name = "guiradgrpDefaultReport";
            this.guiradgrpDefaultReport.Padding = new System.Windows.Forms.Padding(10, 20, 10, 10);
            // 
            // 
            // 
            this.guiradgrpDefaultReport.RootElement.Padding = new System.Windows.Forms.Padding(10, 20, 10, 10);
            this.guiradgrpDefaultReport.Size = new System.Drawing.Size(243, 54);
            this.guiradgrpDefaultReport.TabIndex = 6;
            this.guiradgrpDefaultReport.Text = "Default Report";
            ((Telerik.WinControls.Primitives.FillPrimitive)(this.guiradgrpDefaultReport.GetChildAt(0).GetChildAt(0).GetChildAt(0))).BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(142)))), ((int)(((byte)(150)))), ((int)(((byte)(186)))));
            ((Telerik.WinControls.Primitives.BorderPrimitive)(this.guiradgrpDefaultReport.GetChildAt(0).GetChildAt(0).GetChildAt(1))).ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(185)))), ((int)(((byte)(199)))), ((int)(((byte)(220)))));
            ((Telerik.WinControls.UI.GroupBoxHeader)(this.guiradgrpDefaultReport.GetChildAt(0).GetChildAt(1))).ForeColor = System.Drawing.Color.WhiteSmoke;
            ((Telerik.WinControls.Primitives.FillPrimitive)(this.guiradgrpDefaultReport.GetChildAt(0).GetChildAt(1).GetChildAt(0))).BackColor2 = System.Drawing.Color.FromArgb(((int)(((byte)(142)))), ((int)(((byte)(150)))), ((int)(((byte)(186)))));
            ((Telerik.WinControls.Primitives.FillPrimitive)(this.guiradgrpDefaultReport.GetChildAt(0).GetChildAt(1).GetChildAt(0))).BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(142)))), ((int)(((byte)(150)))), ((int)(((byte)(186)))));
            ((Telerik.WinControls.Primitives.BorderPrimitive)(this.guiradgrpDefaultReport.GetChildAt(0).GetChildAt(1).GetChildAt(1))).Width = 0F;
            // 
            // radgrpbxSimulationTypes
            // 
            this.radgrpbxSimulationTypes.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(142)))), ((int)(((byte)(150)))), ((int)(((byte)(186)))));
            this.radgrpbxSimulationTypes.Controls.Add(this.comboSimulationFiles);
            this.radgrpbxSimulationTypes.Font = new System.Drawing.Font("Arial", 11.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.radgrpbxSimulationTypes.FooterImageIndex = -1;
            this.radgrpbxSimulationTypes.FooterImageKey = "";
            this.radgrpbxSimulationTypes.HeaderImageIndex = -1;
            this.radgrpbxSimulationTypes.HeaderImageKey = "";
            this.radgrpbxSimulationTypes.HeaderMargin = new System.Windows.Forms.Padding(0);
            this.radgrpbxSimulationTypes.HeaderText = "Simulation Types";
            this.radgrpbxSimulationTypes.Location = new System.Drawing.Point(10, 146);
            this.radgrpbxSimulationTypes.Name = "radgrpbxSimulationTypes";
            this.radgrpbxSimulationTypes.Padding = new System.Windows.Forms.Padding(10, 20, 10, 10);
            // 
            // 
            // 
            this.radgrpbxSimulationTypes.RootElement.Padding = new System.Windows.Forms.Padding(10, 20, 10, 10);
            this.radgrpbxSimulationTypes.ShowItemToolTips = false;
            this.radgrpbxSimulationTypes.Size = new System.Drawing.Size(254, 50);
            this.radgrpbxSimulationTypes.TabIndex = 2;
            this.radgrpbxSimulationTypes.Text = "Simulation Types";
            ((Telerik.WinControls.UI.GroupBoxContent)(this.radgrpbxSimulationTypes.GetChildAt(0).GetChildAt(0))).BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(142)))), ((int)(((byte)(150)))), ((int)(((byte)(186)))));
            ((Telerik.WinControls.Primitives.FillPrimitive)(this.radgrpbxSimulationTypes.GetChildAt(0).GetChildAt(0).GetChildAt(0))).BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(142)))), ((int)(((byte)(150)))), ((int)(((byte)(186)))));
            ((Telerik.WinControls.Primitives.BorderPrimitive)(this.radgrpbxSimulationTypes.GetChildAt(0).GetChildAt(0).GetChildAt(1))).ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(185)))), ((int)(((byte)(199)))), ((int)(((byte)(220)))));
            ((Telerik.WinControls.UI.GroupBoxHeader)(this.radgrpbxSimulationTypes.GetChildAt(0).GetChildAt(1))).ForeColor = System.Drawing.Color.WhiteSmoke;
            ((Telerik.WinControls.Primitives.FillPrimitive)(this.radgrpbxSimulationTypes.GetChildAt(0).GetChildAt(1).GetChildAt(0))).BackColor2 = System.Drawing.Color.FromArgb(((int)(((byte)(142)))), ((int)(((byte)(150)))), ((int)(((byte)(186)))));
            ((Telerik.WinControls.Primitives.FillPrimitive)(this.radgrpbxSimulationTypes.GetChildAt(0).GetChildAt(1).GetChildAt(0))).BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(142)))), ((int)(((byte)(150)))), ((int)(((byte)(186)))));
            ((Telerik.WinControls.Primitives.BorderPrimitive)(this.radgrpbxSimulationTypes.GetChildAt(0).GetChildAt(1).GetChildAt(1))).Width = 0F;
            // 
            // comboSimulationFiles
            // 
            this.comboSimulationFiles.AutoCompleteMode = System.Windows.Forms.AutoCompleteMode.Append;
            this.comboSimulationFiles.AutoSize = false;
            this.comboSimulationFiles.DropDownHeight = 80;
            this.comboSimulationFiles.DropDownStyle = Telerik.WinControls.RadDropDownStyle.DropDownList;
            this.comboSimulationFiles.Font = new System.Drawing.Font("Arial", 11.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.comboSimulationFiles.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(23)))), ((int)(((byte)(29)))), ((int)(((byte)(55)))));
            this.comboSimulationFiles.Location = new System.Drawing.Point(14, 22);
            this.comboSimulationFiles.Name = "comboSimulationFiles";
            // 
            // 
            // 
            this.comboSimulationFiles.RootElement.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(23)))), ((int)(((byte)(29)))), ((int)(((byte)(55)))));
            this.comboSimulationFiles.Size = new System.Drawing.Size(185, 23);
            this.comboSimulationFiles.TabIndex = 8;
            this.comboSimulationFiles.SelectedIndexChanged += new Telerik.WinControls.UI.Data.PositionChangedEventHandler(this.comboSimulationFiles_SelectedIndexChanged);
            // 
            // radgrpSimulationFiles
            // 
            this.radgrpSimulationFiles.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(142)))), ((int)(((byte)(150)))), ((int)(((byte)(186)))));
            this.radgrpSimulationFiles.Font = new System.Drawing.Font("Arial", 11.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.radgrpSimulationFiles.FooterImageIndex = -1;
            this.radgrpSimulationFiles.FooterImageKey = "";
            this.radgrpSimulationFiles.HeaderImageIndex = -1;
            this.radgrpSimulationFiles.HeaderImageKey = "";
            this.radgrpSimulationFiles.HeaderMargin = new System.Windows.Forms.Padding(0);
            this.radgrpSimulationFiles.HeaderText = "Simulation Types";
            this.radgrpSimulationFiles.Location = new System.Drawing.Point(10, 146);
            this.radgrpSimulationFiles.Name = "radgrpSimulationFiles";
            this.radgrpSimulationFiles.Padding = new System.Windows.Forms.Padding(10, 20, 10, 10);
            // 
            // 
            // 
            this.radgrpSimulationFiles.RootElement.Padding = new System.Windows.Forms.Padding(10, 20, 10, 10);
            this.radgrpSimulationFiles.ShowItemToolTips = false;
            this.radgrpSimulationFiles.Size = new System.Drawing.Size(250, 50);
            this.radgrpSimulationFiles.TabIndex = 5;
            this.radgrpSimulationFiles.Text = "Simulation Types";
            ((Telerik.WinControls.UI.GroupBoxContent)(this.radgrpSimulationFiles.GetChildAt(0).GetChildAt(0))).BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(142)))), ((int)(((byte)(150)))), ((int)(((byte)(186)))));
            ((Telerik.WinControls.Primitives.FillPrimitive)(this.radgrpSimulationFiles.GetChildAt(0).GetChildAt(0).GetChildAt(0))).BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(142)))), ((int)(((byte)(150)))), ((int)(((byte)(186)))));
            ((Telerik.WinControls.Primitives.BorderPrimitive)(this.radgrpSimulationFiles.GetChildAt(0).GetChildAt(0).GetChildAt(1))).ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(185)))), ((int)(((byte)(199)))), ((int)(((byte)(220)))));
            ((Telerik.WinControls.UI.GroupBoxHeader)(this.radgrpSimulationFiles.GetChildAt(0).GetChildAt(1))).ForeColor = System.Drawing.Color.WhiteSmoke;
            ((Telerik.WinControls.Primitives.FillPrimitive)(this.radgrpSimulationFiles.GetChildAt(0).GetChildAt(1).GetChildAt(0))).BackColor2 = System.Drawing.Color.FromArgb(((int)(((byte)(142)))), ((int)(((byte)(150)))), ((int)(((byte)(186)))));
            ((Telerik.WinControls.Primitives.FillPrimitive)(this.radgrpSimulationFiles.GetChildAt(0).GetChildAt(1).GetChildAt(0))).BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(142)))), ((int)(((byte)(150)))), ((int)(((byte)(186)))));
            ((Telerik.WinControls.Primitives.BorderPrimitive)(this.radgrpSimulationFiles.GetChildAt(0).GetChildAt(1).GetChildAt(1))).Width = 0F;
            // 
            // radgrpCaptureTime
            // 
            this.radgrpCaptureTime.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(142)))), ((int)(((byte)(150)))), ((int)(((byte)(186)))));
            this.radgrpCaptureTime.Controls.Add(this.tableLayoutPanel4);
            this.radgrpCaptureTime.Font = new System.Drawing.Font("Arial", 11.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.radgrpCaptureTime.FooterImageIndex = -1;
            this.radgrpCaptureTime.FooterImageKey = "";
            this.radgrpCaptureTime.HeaderImageIndex = -1;
            this.radgrpCaptureTime.HeaderImageKey = "";
            this.radgrpCaptureTime.HeaderMargin = new System.Windows.Forms.Padding(0);
            this.radgrpCaptureTime.HeaderText = "Capture Time";
            this.radgrpCaptureTime.Location = new System.Drawing.Point(283, 262);
            this.radgrpCaptureTime.Name = "radgrpCaptureTime";
            this.radgrpCaptureTime.Padding = new System.Windows.Forms.Padding(10, 20, 10, 10);
            // 
            // 
            // 
            this.radgrpCaptureTime.RootElement.Padding = new System.Windows.Forms.Padding(10, 20, 10, 10);
            this.radgrpCaptureTime.Size = new System.Drawing.Size(242, 95);
            this.radgrpCaptureTime.TabIndex = 7;
            this.radgrpCaptureTime.Text = "Capture Time";
            ((Telerik.WinControls.Primitives.FillPrimitive)(this.radgrpCaptureTime.GetChildAt(0).GetChildAt(0).GetChildAt(0))).BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(142)))), ((int)(((byte)(150)))), ((int)(((byte)(186)))));
            ((Telerik.WinControls.Primitives.BorderPrimitive)(this.radgrpCaptureTime.GetChildAt(0).GetChildAt(0).GetChildAt(1))).ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(185)))), ((int)(((byte)(199)))), ((int)(((byte)(220)))));
            ((Telerik.WinControls.UI.GroupBoxHeader)(this.radgrpCaptureTime.GetChildAt(0).GetChildAt(1))).ForeColor = System.Drawing.Color.WhiteSmoke;
            ((Telerik.WinControls.Primitives.FillPrimitive)(this.radgrpCaptureTime.GetChildAt(0).GetChildAt(1).GetChildAt(0))).BackColor2 = System.Drawing.Color.FromArgb(((int)(((byte)(142)))), ((int)(((byte)(150)))), ((int)(((byte)(186)))));
            ((Telerik.WinControls.Primitives.FillPrimitive)(this.radgrpCaptureTime.GetChildAt(0).GetChildAt(1).GetChildAt(0))).BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(142)))), ((int)(((byte)(150)))), ((int)(((byte)(186)))));
            ((Telerik.WinControls.Primitives.BorderPrimitive)(this.radgrpCaptureTime.GetChildAt(0).GetChildAt(1).GetChildAt(1))).Width = 0F;
            // 
            // tableLayoutPanel4
            // 
            this.tableLayoutPanel4.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(142)))), ((int)(((byte)(150)))), ((int)(((byte)(186)))));
            this.tableLayoutPanel4.ColumnCount = 1;
            this.tableLayoutPanel4.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 50F));
            this.tableLayoutPanel4.Controls.Add(this.rad5Seconds, 0, 0);
            this.tableLayoutPanel4.Controls.Add(this.rad10Seconds, 0, 1);
            this.tableLayoutPanel4.Controls.Add(this.rad20Seconds, 0, 2);
            this.tableLayoutPanel4.Location = new System.Drawing.Point(18, 24);
            this.tableLayoutPanel4.Name = "tableLayoutPanel4";
            this.tableLayoutPanel4.RowCount = 3;
            this.tableLayoutPanel4.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 50F));
            this.tableLayoutPanel4.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 50F));
            this.tableLayoutPanel4.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Absolute, 20F));
            this.tableLayoutPanel4.Size = new System.Drawing.Size(189, 60);
            this.tableLayoutPanel4.TabIndex = 5;
            // 
            // rad5Seconds
            // 
            this.rad5Seconds.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(142)))), ((int)(((byte)(150)))), ((int)(((byte)(186)))));
            this.rad5Seconds.Font = new System.Drawing.Font("Arial", 11.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.rad5Seconds.ForeColor = System.Drawing.Color.WhiteSmoke;
            this.rad5Seconds.Location = new System.Drawing.Point(3, 3);
            this.rad5Seconds.Name = "rad5Seconds";
            // 
            // 
            // 
            this.rad5Seconds.RootElement.ForeColor = System.Drawing.Color.WhiteSmoke;
            this.rad5Seconds.Size = new System.Drawing.Size(110, 14);
            this.rad5Seconds.TabIndex = 0;
            this.rad5Seconds.Text = "5 seconds";
            this.rad5Seconds.MouseClick += new System.Windows.Forms.MouseEventHandler(this.radchkbxPatientPrivacy_MouseClick);
            this.rad5Seconds.Click += new System.EventHandler(this.radradiobtnImperial_Click);
            // 
            // rad10Seconds
            // 
            this.rad10Seconds.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(142)))), ((int)(((byte)(150)))), ((int)(((byte)(186)))));
            this.rad10Seconds.Font = new System.Drawing.Font("Arial", 11.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.rad10Seconds.ForeColor = System.Drawing.Color.WhiteSmoke;
            this.rad10Seconds.Location = new System.Drawing.Point(3, 23);
            this.rad10Seconds.Name = "rad10Seconds";
            // 
            // 
            // 
            this.rad10Seconds.RootElement.ForeColor = System.Drawing.Color.WhiteSmoke;
            this.rad10Seconds.Size = new System.Drawing.Size(110, 14);
            this.rad10Seconds.TabIndex = 1;
            this.rad10Seconds.Text = "10 seconds";
            this.rad10Seconds.MouseClick += new System.Windows.Forms.MouseEventHandler(this.radchkbxPatientPrivacy_MouseClick);
            this.rad10Seconds.Click += new System.EventHandler(this.radradiobtnImperial_Click);
            // 
            // rad20Seconds
            // 
            this.rad20Seconds.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(142)))), ((int)(((byte)(150)))), ((int)(((byte)(186)))));
            this.rad20Seconds.Font = new System.Drawing.Font("Arial", 11.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.rad20Seconds.ForeColor = System.Drawing.Color.WhiteSmoke;
            this.rad20Seconds.Location = new System.Drawing.Point(3, 43);
            this.rad20Seconds.Name = "rad20Seconds";
            // 
            // 
            // 
            this.rad20Seconds.RootElement.ForeColor = System.Drawing.Color.WhiteSmoke;
            this.rad20Seconds.Size = new System.Drawing.Size(110, 14);
            this.rad20Seconds.TabIndex = 2;
            this.rad20Seconds.Text = "20 seconds";
            this.rad20Seconds.MouseClick += new System.Windows.Forms.MouseEventHandler(this.radchkbxPatientPrivacy_MouseClick);
            this.rad20Seconds.Click += new System.EventHandler(this.radradiobtnImperial_Click);
            // 
            // radgrpReportScreen
            // 
            this.radgrpReportScreen.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(142)))), ((int)(((byte)(150)))), ((int)(((byte)(186)))));
            this.radgrpReportScreen.Controls.Add(this.radchkReferenceRange);
            this.radgrpReportScreen.Controls.Add(this.radchkNormalRange);
            this.radgrpReportScreen.Font = new System.Drawing.Font("Arial", 11.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.radgrpReportScreen.FooterImageIndex = -1;
            this.radgrpReportScreen.FooterImageKey = "";
            this.radgrpReportScreen.HeaderImageIndex = -1;
            this.radgrpReportScreen.HeaderImageKey = "";
            this.radgrpReportScreen.HeaderMargin = new System.Windows.Forms.Padding(0);
            this.radgrpReportScreen.HeaderText = "Report Screen";
            this.radgrpReportScreen.Location = new System.Drawing.Point(10, 199);
            this.radgrpReportScreen.Name = "radgrpReportScreen";
            this.radgrpReportScreen.Padding = new System.Windows.Forms.Padding(10, 20, 10, 10);
            // 
            // 
            // 
            this.radgrpReportScreen.RootElement.Padding = new System.Windows.Forms.Padding(10, 20, 10, 10);
            this.radgrpReportScreen.Size = new System.Drawing.Size(254, 95);
            this.radgrpReportScreen.TabIndex = 3;
            this.radgrpReportScreen.Text = "Report Screen";
            ((Telerik.WinControls.Primitives.FillPrimitive)(this.radgrpReportScreen.GetChildAt(0).GetChildAt(0).GetChildAt(0))).BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(142)))), ((int)(((byte)(150)))), ((int)(((byte)(186)))));
            ((Telerik.WinControls.Primitives.BorderPrimitive)(this.radgrpReportScreen.GetChildAt(0).GetChildAt(0).GetChildAt(1))).ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(185)))), ((int)(((byte)(199)))), ((int)(((byte)(220)))));
            ((Telerik.WinControls.UI.GroupBoxHeader)(this.radgrpReportScreen.GetChildAt(0).GetChildAt(1))).ForeColor = System.Drawing.Color.WhiteSmoke;
            ((Telerik.WinControls.Primitives.FillPrimitive)(this.radgrpReportScreen.GetChildAt(0).GetChildAt(1).GetChildAt(0))).BackColor2 = System.Drawing.Color.FromArgb(((int)(((byte)(142)))), ((int)(((byte)(150)))), ((int)(((byte)(186)))));
            ((Telerik.WinControls.Primitives.FillPrimitive)(this.radgrpReportScreen.GetChildAt(0).GetChildAt(1).GetChildAt(0))).BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(142)))), ((int)(((byte)(150)))), ((int)(((byte)(186)))));
            ((Telerik.WinControls.Primitives.BorderPrimitive)(this.radgrpReportScreen.GetChildAt(0).GetChildAt(1).GetChildAt(1))).Width = 0F;
            // 
            // radchkReferenceRange
            // 
            this.radchkReferenceRange.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(142)))), ((int)(((byte)(150)))), ((int)(((byte)(186)))));
            this.radchkReferenceRange.Font = new System.Drawing.Font("Arial", 11.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.radchkReferenceRange.ForeColor = System.Drawing.Color.WhiteSmoke;
            this.radchkReferenceRange.Location = new System.Drawing.Point(14, 58);
            this.radchkReferenceRange.Name = "radchkReferenceRange";
            // 
            // 
            // 
            this.radchkReferenceRange.RootElement.ForeColor = System.Drawing.Color.WhiteSmoke;
            this.radchkReferenceRange.Size = new System.Drawing.Size(225, 21);
            this.radchkReferenceRange.TabIndex = 1;
            this.radchkReferenceRange.Text = "European General Population";
            this.radchkReferenceRange.MouseClick += new System.Windows.Forms.MouseEventHandler(this.radchkbxPatientPrivacy_MouseClick);
            // 
            // radchkNormalRange
            // 
            this.radchkNormalRange.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(142)))), ((int)(((byte)(150)))), ((int)(((byte)(186)))));
            this.radchkNormalRange.Font = new System.Drawing.Font("Arial", 11.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.radchkNormalRange.ForeColor = System.Drawing.Color.WhiteSmoke;
            this.radchkNormalRange.Location = new System.Drawing.Point(14, 30);
            this.radchkNormalRange.Name = "radchkNormalRange";
            // 
            // 
            // 
            this.radchkNormalRange.RootElement.ForeColor = System.Drawing.Color.WhiteSmoke;
            this.radchkNormalRange.Size = new System.Drawing.Size(149, 21);
            this.radchkNormalRange.TabIndex = 0;
            this.radchkNormalRange.Text = "Healthy population";
            this.radchkNormalRange.MouseClick += new System.Windows.Forms.MouseEventHandler(this.radchkbxPatientPrivacy_MouseClick);
            // 
            // radgrpPwvDistanceUnits
            // 
            this.radgrpPwvDistanceUnits.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(142)))), ((int)(((byte)(150)))), ((int)(((byte)(186)))));
            this.radgrpPwvDistanceUnits.Controls.Add(this.tableLayoutPanel6);
            this.radgrpPwvDistanceUnits.Font = new System.Drawing.Font("Arial", 11.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.radgrpPwvDistanceUnits.FooterImageIndex = -1;
            this.radgrpPwvDistanceUnits.FooterImageKey = "";
            this.radgrpPwvDistanceUnits.HeaderImageIndex = -1;
            this.radgrpPwvDistanceUnits.HeaderImageKey = "";
            this.radgrpPwvDistanceUnits.HeaderMargin = new System.Windows.Forms.Padding(0);
            this.radgrpPwvDistanceUnits.HeaderText = "PWV Distance Units";
            this.radgrpPwvDistanceUnits.Location = new System.Drawing.Point(283, 178);
            this.radgrpPwvDistanceUnits.Name = "radgrpPwvDistanceUnits";
            this.radgrpPwvDistanceUnits.Padding = new System.Windows.Forms.Padding(10, 20, 10, 10);
            // 
            // 
            // 
            this.radgrpPwvDistanceUnits.RootElement.Padding = new System.Windows.Forms.Padding(10, 20, 10, 10);
            this.radgrpPwvDistanceUnits.Size = new System.Drawing.Size(242, 80);
            this.radgrpPwvDistanceUnits.TabIndex = 6;
            this.radgrpPwvDistanceUnits.Text = "PWV Distance Units";
            ((Telerik.WinControls.Primitives.FillPrimitive)(this.radgrpPwvDistanceUnits.GetChildAt(0).GetChildAt(0).GetChildAt(0))).BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(142)))), ((int)(((byte)(150)))), ((int)(((byte)(186)))));
            ((Telerik.WinControls.Primitives.BorderPrimitive)(this.radgrpPwvDistanceUnits.GetChildAt(0).GetChildAt(0).GetChildAt(1))).ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(185)))), ((int)(((byte)(199)))), ((int)(((byte)(220)))));
            ((Telerik.WinControls.UI.GroupBoxHeader)(this.radgrpPwvDistanceUnits.GetChildAt(0).GetChildAt(1))).ForeColor = System.Drawing.Color.WhiteSmoke;
            ((Telerik.WinControls.Primitives.FillPrimitive)(this.radgrpPwvDistanceUnits.GetChildAt(0).GetChildAt(1).GetChildAt(0))).BackColor2 = System.Drawing.Color.FromArgb(((int)(((byte)(142)))), ((int)(((byte)(150)))), ((int)(((byte)(186)))));
            ((Telerik.WinControls.Primitives.FillPrimitive)(this.radgrpPwvDistanceUnits.GetChildAt(0).GetChildAt(1).GetChildAt(0))).BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(142)))), ((int)(((byte)(150)))), ((int)(((byte)(186)))));
            ((Telerik.WinControls.Primitives.BorderPrimitive)(this.radgrpPwvDistanceUnits.GetChildAt(0).GetChildAt(1).GetChildAt(1))).Width = 0F;
            // 
            // tableLayoutPanel6
            // 
            this.tableLayoutPanel6.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(142)))), ((int)(((byte)(150)))), ((int)(((byte)(186)))));
            this.tableLayoutPanel6.ColumnCount = 1;
            this.tableLayoutPanel6.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 50F));
            this.tableLayoutPanel6.Controls.Add(this.radmm, 0, 0);
            this.tableLayoutPanel6.Controls.Add(this.radcm, 0, 1);
            this.tableLayoutPanel6.Location = new System.Drawing.Point(18, 23);
            this.tableLayoutPanel6.Name = "tableLayoutPanel6";
            this.tableLayoutPanel6.RowCount = 2;
            this.tableLayoutPanel6.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 48.93617F));
            this.tableLayoutPanel6.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 51.06383F));
            this.tableLayoutPanel6.Size = new System.Drawing.Size(189, 47);
            this.tableLayoutPanel6.TabIndex = 4;
            // 
            // radmm
            // 
            this.radmm.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(142)))), ((int)(((byte)(150)))), ((int)(((byte)(186)))));
            this.radmm.Font = new System.Drawing.Font("Arial", 11.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.radmm.ForeColor = System.Drawing.Color.WhiteSmoke;
            this.radmm.Location = new System.Drawing.Point(3, 3);
            this.radmm.Name = "radmm";
            // 
            // 
            // 
            this.radmm.RootElement.ForeColor = System.Drawing.Color.WhiteSmoke;
            this.radmm.Size = new System.Drawing.Size(110, 16);
            this.radmm.TabIndex = 0;
            this.radmm.Text = "mm";
            this.radmm.Click += new System.EventHandler(this.radradiobtnImperial_Click);
            // 
            // radcm
            // 
            this.radcm.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(142)))), ((int)(((byte)(150)))), ((int)(((byte)(186)))));
            this.radcm.Font = new System.Drawing.Font("Arial", 11.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.radcm.ForeColor = System.Drawing.Color.WhiteSmoke;
            this.radcm.Location = new System.Drawing.Point(3, 25);
            this.radcm.Name = "radcm";
            // 
            // 
            // 
            this.radcm.RootElement.ForeColor = System.Drawing.Color.WhiteSmoke;
            this.radcm.Size = new System.Drawing.Size(110, 14);
            this.radcm.TabIndex = 1;
            this.radcm.Text = "cm";
            this.radcm.MouseClick += new System.Windows.Forms.MouseEventHandler(this.radchkbxPatientPrivacy_MouseClick);
            this.radcm.Click += new System.EventHandler(this.radradiobtnImperial_Click);
            // 
            // radgrpCuffLocation
            // 
            this.radgrpCuffLocation.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(142)))), ((int)(((byte)(150)))), ((int)(((byte)(186)))));
            this.radgrpCuffLocation.Controls.Add(this.radchkFemoralToCuff);
            this.radgrpCuffLocation.Font = new System.Drawing.Font("Arial", 11.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.radgrpCuffLocation.FooterImageIndex = -1;
            this.radgrpCuffLocation.FooterImageKey = "";
            this.radgrpCuffLocation.HeaderImageIndex = -1;
            this.radgrpCuffLocation.HeaderImageKey = "";
            this.radgrpCuffLocation.HeaderMargin = new System.Windows.Forms.Padding(0);
            this.radgrpCuffLocation.HeaderText = "Cuff Location";
            this.radgrpCuffLocation.Location = new System.Drawing.Point(10, 89);
            this.radgrpCuffLocation.Name = "radgrpCuffLocation";
            this.radgrpCuffLocation.Padding = new System.Windows.Forms.Padding(10, 20, 10, 10);
            // 
            // 
            // 
            this.radgrpCuffLocation.RootElement.Padding = new System.Windows.Forms.Padding(10, 20, 10, 10);
            this.radgrpCuffLocation.Size = new System.Drawing.Size(254, 45);
            this.radgrpCuffLocation.TabIndex = 1;
            this.radgrpCuffLocation.Text = "Cuff Location";
            ((Telerik.WinControls.Primitives.FillPrimitive)(this.radgrpCuffLocation.GetChildAt(0).GetChildAt(0).GetChildAt(0))).BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(142)))), ((int)(((byte)(150)))), ((int)(((byte)(186)))));
            ((Telerik.WinControls.Primitives.BorderPrimitive)(this.radgrpCuffLocation.GetChildAt(0).GetChildAt(0).GetChildAt(1))).ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(185)))), ((int)(((byte)(199)))), ((int)(((byte)(220)))));
            ((Telerik.WinControls.UI.GroupBoxHeader)(this.radgrpCuffLocation.GetChildAt(0).GetChildAt(1))).ForeColor = System.Drawing.Color.WhiteSmoke;
            ((Telerik.WinControls.Primitives.FillPrimitive)(this.radgrpCuffLocation.GetChildAt(0).GetChildAt(1).GetChildAt(0))).BackColor2 = System.Drawing.Color.FromArgb(((int)(((byte)(142)))), ((int)(((byte)(150)))), ((int)(((byte)(186)))));
            ((Telerik.WinControls.Primitives.FillPrimitive)(this.radgrpCuffLocation.GetChildAt(0).GetChildAt(1).GetChildAt(0))).BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(142)))), ((int)(((byte)(150)))), ((int)(((byte)(186)))));
            ((Telerik.WinControls.Primitives.BorderPrimitive)(this.radgrpCuffLocation.GetChildAt(0).GetChildAt(1).GetChildAt(1))).Width = 0F;
            // 
            // radchkFemoralToCuff
            // 
            this.radchkFemoralToCuff.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(142)))), ((int)(((byte)(150)))), ((int)(((byte)(186)))));
            this.radchkFemoralToCuff.Font = new System.Drawing.Font("Arial", 11.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.radchkFemoralToCuff.ForeColor = System.Drawing.Color.WhiteSmoke;
            this.radchkFemoralToCuff.Location = new System.Drawing.Point(14, 16);
            this.radchkFemoralToCuff.Name = "radchkFemoralToCuff";
            // 
            // 
            // 
            this.radchkFemoralToCuff.RootElement.ForeColor = System.Drawing.Color.WhiteSmoke;
            this.radchkFemoralToCuff.Size = new System.Drawing.Size(125, 21);
            this.radchkFemoralToCuff.TabIndex = 0;
            this.radchkFemoralToCuff.Text = "Femoral to cuff";
            this.radchkFemoralToCuff.MouseClick += new System.Windows.Forms.MouseEventHandler(this.radchkbxPatientPrivacy_MouseClick);
            // 
            // radgrpbxPwvDistanceMethod
            // 
            this.radgrpbxPwvDistanceMethod.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(142)))), ((int)(((byte)(150)))), ((int)(((byte)(186)))));
            this.radgrpbxPwvDistanceMethod.Controls.Add(this.tblPWVDistanceMethod);
            this.radgrpbxPwvDistanceMethod.Font = new System.Drawing.Font("Arial", 11.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.radgrpbxPwvDistanceMethod.FooterImageIndex = -1;
            this.radgrpbxPwvDistanceMethod.FooterImageKey = "";
            this.radgrpbxPwvDistanceMethod.HeaderImageIndex = -1;
            this.radgrpbxPwvDistanceMethod.HeaderImageKey = "";
            this.radgrpbxPwvDistanceMethod.HeaderMargin = new System.Windows.Forms.Padding(0);
            this.radgrpbxPwvDistanceMethod.HeaderText = "PWV Distance Method";
            this.radgrpbxPwvDistanceMethod.Location = new System.Drawing.Point(10, 3);
            this.radgrpbxPwvDistanceMethod.Name = "radgrpbxPwvDistanceMethod";
            this.radgrpbxPwvDistanceMethod.Padding = new System.Windows.Forms.Padding(10, 20, 10, 10);
            // 
            // 
            // 
            this.radgrpbxPwvDistanceMethod.RootElement.Padding = new System.Windows.Forms.Padding(10, 20, 10, 10);
            this.radgrpbxPwvDistanceMethod.Size = new System.Drawing.Size(515, 76);
            this.radgrpbxPwvDistanceMethod.TabIndex = 0;
            this.radgrpbxPwvDistanceMethod.Text = "PWV Distance Method";
            ((Telerik.WinControls.Primitives.FillPrimitive)(this.radgrpbxPwvDistanceMethod.GetChildAt(0).GetChildAt(0).GetChildAt(0))).BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(142)))), ((int)(((byte)(150)))), ((int)(((byte)(186)))));
            ((Telerik.WinControls.Primitives.BorderPrimitive)(this.radgrpbxPwvDistanceMethod.GetChildAt(0).GetChildAt(0).GetChildAt(1))).ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(185)))), ((int)(((byte)(199)))), ((int)(((byte)(220)))));
            ((Telerik.WinControls.UI.GroupBoxHeader)(this.radgrpbxPwvDistanceMethod.GetChildAt(0).GetChildAt(1))).ForeColor = System.Drawing.Color.WhiteSmoke;
            ((Telerik.WinControls.Primitives.FillPrimitive)(this.radgrpbxPwvDistanceMethod.GetChildAt(0).GetChildAt(1).GetChildAt(0))).BackColor2 = System.Drawing.Color.FromArgb(((int)(((byte)(142)))), ((int)(((byte)(150)))), ((int)(((byte)(186)))));
            ((Telerik.WinControls.Primitives.FillPrimitive)(this.radgrpbxPwvDistanceMethod.GetChildAt(0).GetChildAt(1).GetChildAt(0))).BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(142)))), ((int)(((byte)(150)))), ((int)(((byte)(186)))));
            ((Telerik.WinControls.Primitives.BorderPrimitive)(this.radgrpbxPwvDistanceMethod.GetChildAt(0).GetChildAt(1).GetChildAt(1))).Width = 0F;
            // 
            // tblPWVDistanceMethod
            // 
            this.tblPWVDistanceMethod.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(142)))), ((int)(((byte)(150)))), ((int)(((byte)(186)))));
            this.tblPWVDistanceMethod.ColumnCount = 1;
            this.tblPWVDistanceMethod.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 50F));
            this.tblPWVDistanceMethod.Controls.Add(this.radDirect, 0, 1);
            this.tblPWVDistanceMethod.Controls.Add(this.radSubtracting, 0, 0);
            this.tblPWVDistanceMethod.Location = new System.Drawing.Point(14, 20);
            this.tblPWVDistanceMethod.Name = "tblPWVDistanceMethod";
            this.tblPWVDistanceMethod.RowCount = 2;
            this.tblPWVDistanceMethod.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 50F));
            this.tblPWVDistanceMethod.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 50F));
            this.tblPWVDistanceMethod.Size = new System.Drawing.Size(484, 47);
            this.tblPWVDistanceMethod.TabIndex = 3;
            // 
            // radDirect
            // 
            this.radDirect.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(142)))), ((int)(((byte)(150)))), ((int)(((byte)(186)))));
            this.radDirect.Font = new System.Drawing.Font("Arial", 11.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.radDirect.ForeColor = System.Drawing.Color.WhiteSmoke;
            this.radDirect.Location = new System.Drawing.Point(3, 26);
            this.radDirect.Name = "radDirect";
            // 
            // 
            // 
            this.radDirect.RootElement.ForeColor = System.Drawing.Color.WhiteSmoke;
            this.radDirect.Size = new System.Drawing.Size(478, 18);
            this.radDirect.TabIndex = 1;
            this.radDirect.Text = "Direct (carotid to cuff)";
            this.radDirect.MouseClick += new System.Windows.Forms.MouseEventHandler(this.radchkbxPatientPrivacy_MouseClick);
            // 
            // radSubtracting
            // 
            this.radSubtracting.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(142)))), ((int)(((byte)(150)))), ((int)(((byte)(186)))));
            this.radSubtracting.Font = new System.Drawing.Font("Arial", 11.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.radSubtracting.ForeColor = System.Drawing.Color.WhiteSmoke;
            this.radSubtracting.Location = new System.Drawing.Point(3, 3);
            this.radSubtracting.Name = "radSubtracting";
            // 
            // 
            // 
            this.radSubtracting.RootElement.ForeColor = System.Drawing.Color.WhiteSmoke;
            this.radSubtracting.Size = new System.Drawing.Size(478, 17);
            this.radSubtracting.TabIndex = 0;
            this.radSubtracting.Text = "Subtracting (sternal notch to cuff – sternal notch to carotid)";
            this.radSubtracting.MouseClick += new System.Windows.Forms.MouseEventHandler(this.radchkbxPatientPrivacy_MouseClick);
            // 
            // docWndPWASettings
            // 
            this.docWndPWASettings.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(142)))), ((int)(((byte)(150)))), ((int)(((byte)(186)))));
            this.docWndPWASettings.Controls.Add(this.guiradgrpbxPWASimulationFiles);
            this.docWndPWASettings.Controls.Add(this.radgrpbxCaptureGuidePWA);
            this.docWndPWASettings.Controls.Add(this.radgrpbxClinicalReport);
            this.docWndPWASettings.Controls.Add(this.radgrpbxCaptureInput);
            this.docWndPWASettings.Controls.Add(this.radgrpbxCaptureTime);
            this.docWndPWASettings.DocumentButtons = Telerik.WinControls.UI.Docking.DocumentStripButtons.None;
            this.docWndPWASettings.Location = new System.Drawing.Point(6, 33);
            this.docWndPWASettings.Name = "docWndPWASettings";
            this.docWndPWASettings.Size = new System.Drawing.Size(540, 372);
            this.docWndPWASettings.Text = "PWA Settings";
            // 
            // guiradgrpbxPWASimulationFiles
            // 
            this.guiradgrpbxPWASimulationFiles.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(142)))), ((int)(((byte)(150)))), ((int)(((byte)(186)))));
            this.guiradgrpbxPWASimulationFiles.Controls.Add(this.radDropDownList3);
            this.guiradgrpbxPWASimulationFiles.Font = new System.Drawing.Font("Arial", 11.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.guiradgrpbxPWASimulationFiles.FooterImageIndex = -1;
            this.guiradgrpbxPWASimulationFiles.FooterImageKey = "";
            this.guiradgrpbxPWASimulationFiles.HeaderImageIndex = -1;
            this.guiradgrpbxPWASimulationFiles.HeaderImageKey = "";
            this.guiradgrpbxPWASimulationFiles.HeaderMargin = new System.Windows.Forms.Padding(0);
            this.guiradgrpbxPWASimulationFiles.HeaderText = "Simulation Types";
            this.guiradgrpbxPWASimulationFiles.Location = new System.Drawing.Point(22, 257);
            this.guiradgrpbxPWASimulationFiles.Name = "guiradgrpbxPWASimulationFiles";
            this.guiradgrpbxPWASimulationFiles.Padding = new System.Windows.Forms.Padding(10, 20, 10, 10);
            // 
            // 
            // 
            this.guiradgrpbxPWASimulationFiles.RootElement.Padding = new System.Windows.Forms.Padding(10, 20, 10, 10);
            this.guiradgrpbxPWASimulationFiles.ShowItemToolTips = false;
            this.guiradgrpbxPWASimulationFiles.Size = new System.Drawing.Size(223, 50);
            this.guiradgrpbxPWASimulationFiles.TabIndex = 2;
            this.guiradgrpbxPWASimulationFiles.Text = "Simulation Types";
            ((Telerik.WinControls.UI.GroupBoxContent)(this.guiradgrpbxPWASimulationFiles.GetChildAt(0).GetChildAt(0))).BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(142)))), ((int)(((byte)(150)))), ((int)(((byte)(186)))));
            ((Telerik.WinControls.Primitives.FillPrimitive)(this.guiradgrpbxPWASimulationFiles.GetChildAt(0).GetChildAt(0).GetChildAt(0))).BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(142)))), ((int)(((byte)(150)))), ((int)(((byte)(186)))));
            ((Telerik.WinControls.Primitives.BorderPrimitive)(this.guiradgrpbxPWASimulationFiles.GetChildAt(0).GetChildAt(0).GetChildAt(1))).ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(185)))), ((int)(((byte)(199)))), ((int)(((byte)(220)))));
            ((Telerik.WinControls.UI.GroupBoxHeader)(this.guiradgrpbxPWASimulationFiles.GetChildAt(0).GetChildAt(1))).ForeColor = System.Drawing.Color.WhiteSmoke;
            ((Telerik.WinControls.Primitives.FillPrimitive)(this.guiradgrpbxPWASimulationFiles.GetChildAt(0).GetChildAt(1).GetChildAt(0))).BackColor2 = System.Drawing.Color.FromArgb(((int)(((byte)(142)))), ((int)(((byte)(150)))), ((int)(((byte)(186)))));
            ((Telerik.WinControls.Primitives.FillPrimitive)(this.guiradgrpbxPWASimulationFiles.GetChildAt(0).GetChildAt(1).GetChildAt(0))).BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(142)))), ((int)(((byte)(150)))), ((int)(((byte)(186)))));
            ((Telerik.WinControls.Primitives.BorderPrimitive)(this.guiradgrpbxPWASimulationFiles.GetChildAt(0).GetChildAt(1).GetChildAt(1))).Width = 0F;
            // 
            // radDropDownList3
            // 
            this.radDropDownList3.AutoCompleteMode = System.Windows.Forms.AutoCompleteMode.Append;
            this.radDropDownList3.AutoSize = false;
            this.radDropDownList3.DropDownHeight = 80;
            this.radDropDownList3.DropDownStyle = Telerik.WinControls.RadDropDownStyle.DropDownList;
            this.radDropDownList3.Font = new System.Drawing.Font("Arial", 11.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.radDropDownList3.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(23)))), ((int)(((byte)(29)))), ((int)(((byte)(55)))));
            this.radDropDownList3.Location = new System.Drawing.Point(13, 18);
            this.radDropDownList3.Name = "radDropDownList3";
            // 
            // 
            // 
            this.radDropDownList3.RootElement.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(23)))), ((int)(((byte)(29)))), ((int)(((byte)(55)))));
            this.radDropDownList3.Size = new System.Drawing.Size(163, 23);
            this.radDropDownList3.TabIndex = 8;
            this.radDropDownList3.SelectedIndexChanged += new Telerik.WinControls.UI.Data.PositionChangedEventHandler(this.comboSimulationFiles_SelectedIndexChanged);
            // 
            // radgrpbxCaptureGuidePWA
            // 
            this.radgrpbxCaptureGuidePWA.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(142)))), ((int)(((byte)(150)))), ((int)(((byte)(186)))));
            this.radgrpbxCaptureGuidePWA.Controls.Add(this.radchkAutoCapturePWA);
            this.radgrpbxCaptureGuidePWA.Controls.Add(this.radchkGuidanceBars);
            this.radgrpbxCaptureGuidePWA.Font = new System.Drawing.Font("Arial", 11.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.radgrpbxCaptureGuidePWA.FooterImageIndex = -1;
            this.radgrpbxCaptureGuidePWA.FooterImageKey = "";
            this.radgrpbxCaptureGuidePWA.HeaderImageIndex = -1;
            this.radgrpbxCaptureGuidePWA.HeaderImageKey = "";
            this.radgrpbxCaptureGuidePWA.HeaderMargin = new System.Windows.Forms.Padding(0);
            this.radgrpbxCaptureGuidePWA.HeaderText = "Capture Guide";
            this.radgrpbxCaptureGuidePWA.Location = new System.Drawing.Point(22, 163);
            this.radgrpbxCaptureGuidePWA.Name = "radgrpbxCaptureGuidePWA";
            this.radgrpbxCaptureGuidePWA.Padding = new System.Windows.Forms.Padding(10, 20, 10, 10);
            // 
            // 
            // 
            this.radgrpbxCaptureGuidePWA.RootElement.Padding = new System.Windows.Forms.Padding(10, 20, 10, 10);
            this.radgrpbxCaptureGuidePWA.Size = new System.Drawing.Size(223, 80);
            this.radgrpbxCaptureGuidePWA.TabIndex = 1;
            this.radgrpbxCaptureGuidePWA.Text = "Capture Guide";
            ((Telerik.WinControls.Primitives.FillPrimitive)(this.radgrpbxCaptureGuidePWA.GetChildAt(0).GetChildAt(0).GetChildAt(0))).BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(142)))), ((int)(((byte)(150)))), ((int)(((byte)(186)))));
            ((Telerik.WinControls.Primitives.BorderPrimitive)(this.radgrpbxCaptureGuidePWA.GetChildAt(0).GetChildAt(0).GetChildAt(1))).ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(185)))), ((int)(((byte)(199)))), ((int)(((byte)(220)))));
            ((Telerik.WinControls.UI.GroupBoxHeader)(this.radgrpbxCaptureGuidePWA.GetChildAt(0).GetChildAt(1))).ForeColor = System.Drawing.Color.WhiteSmoke;
            ((Telerik.WinControls.Primitives.FillPrimitive)(this.radgrpbxCaptureGuidePWA.GetChildAt(0).GetChildAt(1).GetChildAt(0))).BackColor2 = System.Drawing.Color.FromArgb(((int)(((byte)(142)))), ((int)(((byte)(150)))), ((int)(((byte)(186)))));
            ((Telerik.WinControls.Primitives.FillPrimitive)(this.radgrpbxCaptureGuidePWA.GetChildAt(0).GetChildAt(1).GetChildAt(0))).BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(142)))), ((int)(((byte)(150)))), ((int)(((byte)(186)))));
            ((Telerik.WinControls.Primitives.BorderPrimitive)(this.radgrpbxCaptureGuidePWA.GetChildAt(0).GetChildAt(1).GetChildAt(1))).Width = 0F;
            // 
            // radchkAutoCapturePWA
            // 
            this.radchkAutoCapturePWA.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(142)))), ((int)(((byte)(150)))), ((int)(((byte)(186)))));
            this.radchkAutoCapturePWA.Font = new System.Drawing.Font("Arial", 11.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.radchkAutoCapturePWA.ForeColor = System.Drawing.Color.WhiteSmoke;
            this.radchkAutoCapturePWA.Location = new System.Drawing.Point(20, 47);
            this.radchkAutoCapturePWA.Name = "radchkAutoCapturePWA";
            // 
            // 
            // 
            this.radchkAutoCapturePWA.RootElement.ForeColor = System.Drawing.Color.WhiteSmoke;
            this.radchkAutoCapturePWA.Size = new System.Drawing.Size(113, 21);
            this.radchkAutoCapturePWA.TabIndex = 1;
            this.radchkAutoCapturePWA.Text = "Auto Capture";
            this.radchkAutoCapturePWA.MouseClick += new System.Windows.Forms.MouseEventHandler(this.radchkbxPatientPrivacy_MouseClick);
            // 
            // radchkGuidanceBars
            // 
            this.radchkGuidanceBars.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(142)))), ((int)(((byte)(150)))), ((int)(((byte)(186)))));
            this.radchkGuidanceBars.Font = new System.Drawing.Font("Arial", 11.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.radchkGuidanceBars.ForeColor = System.Drawing.Color.WhiteSmoke;
            this.radchkGuidanceBars.Location = new System.Drawing.Point(20, 23);
            this.radchkGuidanceBars.Name = "radchkGuidanceBars";
            // 
            // 
            // 
            this.radchkGuidanceBars.RootElement.ForeColor = System.Drawing.Color.WhiteSmoke;
            this.radchkGuidanceBars.Size = new System.Drawing.Size(124, 21);
            this.radchkGuidanceBars.TabIndex = 0;
            this.radchkGuidanceBars.Text = "Guidance Bars";
            this.radchkGuidanceBars.MouseClick += new System.Windows.Forms.MouseEventHandler(this.radchkbxPatientPrivacy_MouseClick);
            // 
            // radgrpbxClinicalReport
            // 
            this.radgrpbxClinicalReport.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(142)))), ((int)(((byte)(150)))), ((int)(((byte)(186)))));
            this.radgrpbxClinicalReport.Controls.Add(this.radchkBlindStudy);
            this.radgrpbxClinicalReport.Controls.Add(this.radchkAumentationIndexHR75);
            this.radgrpbxClinicalReport.Controls.Add(this.radchkAumentationIndex);
            this.radgrpbxClinicalReport.Font = new System.Drawing.Font("Arial", 11.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.radgrpbxClinicalReport.FooterImageIndex = -1;
            this.radgrpbxClinicalReport.FooterImageKey = "";
            this.radgrpbxClinicalReport.HeaderImageIndex = -1;
            this.radgrpbxClinicalReport.HeaderImageKey = "";
            this.radgrpbxClinicalReport.HeaderMargin = new System.Windows.Forms.Padding(0);
            this.radgrpbxClinicalReport.HeaderText = "Clinical Report";
            this.radgrpbxClinicalReport.Location = new System.Drawing.Point(276, 47);
            this.radgrpbxClinicalReport.Name = "radgrpbxClinicalReport";
            this.radgrpbxClinicalReport.Padding = new System.Windows.Forms.Padding(10, 20, 10, 10);
            // 
            // 
            // 
            this.radgrpbxClinicalReport.RootElement.Padding = new System.Windows.Forms.Padding(10, 20, 10, 10);
            this.radgrpbxClinicalReport.Size = new System.Drawing.Size(235, 102);
            this.radgrpbxClinicalReport.TabIndex = 3;
            this.radgrpbxClinicalReport.Text = "Clinical Report";
            ((Telerik.WinControls.Primitives.FillPrimitive)(this.radgrpbxClinicalReport.GetChildAt(0).GetChildAt(0).GetChildAt(0))).BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(142)))), ((int)(((byte)(150)))), ((int)(((byte)(186)))));
            ((Telerik.WinControls.Primitives.BorderPrimitive)(this.radgrpbxClinicalReport.GetChildAt(0).GetChildAt(0).GetChildAt(1))).ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(185)))), ((int)(((byte)(199)))), ((int)(((byte)(220)))));
            ((Telerik.WinControls.UI.GroupBoxHeader)(this.radgrpbxClinicalReport.GetChildAt(0).GetChildAt(1))).ForeColor = System.Drawing.Color.WhiteSmoke;
            ((Telerik.WinControls.Primitives.FillPrimitive)(this.radgrpbxClinicalReport.GetChildAt(0).GetChildAt(1).GetChildAt(0))).BackColor2 = System.Drawing.Color.FromArgb(((int)(((byte)(142)))), ((int)(((byte)(150)))), ((int)(((byte)(186)))));
            ((Telerik.WinControls.Primitives.FillPrimitive)(this.radgrpbxClinicalReport.GetChildAt(0).GetChildAt(1).GetChildAt(0))).BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(142)))), ((int)(((byte)(150)))), ((int)(((byte)(186)))));
            ((Telerik.WinControls.Primitives.BorderPrimitive)(this.radgrpbxClinicalReport.GetChildAt(0).GetChildAt(1).GetChildAt(1))).Width = 0F;
            // 
            // radchkBlindStudy
            // 
            this.radchkBlindStudy.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(142)))), ((int)(((byte)(150)))), ((int)(((byte)(186)))));
            this.radchkBlindStudy.Font = new System.Drawing.Font("Arial", 11.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.radchkBlindStudy.ForeColor = System.Drawing.Color.WhiteSmoke;
            this.radchkBlindStudy.Location = new System.Drawing.Point(16, 70);
            this.radchkBlindStudy.Name = "radchkBlindStudy";
            // 
            // 
            // 
            this.radchkBlindStudy.RootElement.ForeColor = System.Drawing.Color.WhiteSmoke;
            this.radchkBlindStudy.Size = new System.Drawing.Size(104, 21);
            this.radchkBlindStudy.TabIndex = 2;
            this.radchkBlindStudy.Text = "Blind Study ";
            this.radchkBlindStudy.MouseClick += new System.Windows.Forms.MouseEventHandler(this.radchkbxPatientPrivacy_MouseClick);
            // 
            // radchkAumentationIndexHR75
            // 
            this.radchkAumentationIndexHR75.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(142)))), ((int)(((byte)(150)))), ((int)(((byte)(186)))));
            this.radchkAumentationIndexHR75.Font = new System.Drawing.Font("Arial", 11.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.radchkAumentationIndexHR75.ForeColor = System.Drawing.Color.WhiteSmoke;
            this.radchkAumentationIndexHR75.Location = new System.Drawing.Point(16, 49);
            this.radchkAumentationIndexHR75.Name = "radchkAumentationIndexHR75";
            // 
            // 
            // 
            this.radchkAumentationIndexHR75.RootElement.ForeColor = System.Drawing.Color.WhiteSmoke;
            this.radchkAumentationIndexHR75.Size = new System.Drawing.Size(218, 21);
            this.radchkAumentationIndexHR75.TabIndex = 1;
            this.radchkAumentationIndexHR75.Text = "Augmentation Index@HR75 ";
            this.radchkAumentationIndexHR75.MouseClick += new System.Windows.Forms.MouseEventHandler(this.radchkbxPatientPrivacy_MouseClick);
            // 
            // radchkAumentationIndex
            // 
            this.radchkAumentationIndex.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(142)))), ((int)(((byte)(150)))), ((int)(((byte)(186)))));
            this.radchkAumentationIndex.Font = new System.Drawing.Font("Arial", 11.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.radchkAumentationIndex.ForeColor = System.Drawing.Color.WhiteSmoke;
            this.radchkAumentationIndex.Location = new System.Drawing.Point(16, 28);
            this.radchkAumentationIndex.Name = "radchkAumentationIndex";
            // 
            // 
            // 
            this.radchkAumentationIndex.RootElement.ForeColor = System.Drawing.Color.WhiteSmoke;
            this.radchkAumentationIndex.Size = new System.Drawing.Size(163, 21);
            this.radchkAumentationIndex.TabIndex = 0;
            this.radchkAumentationIndex.Text = "Augmentation Index ";
            this.radchkAumentationIndex.MouseClick += new System.Windows.Forms.MouseEventHandler(this.radchkbxPatientPrivacy_MouseClick);
            // 
            // radgrpbxCaptureInput
            // 
            this.radgrpbxCaptureInput.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(142)))), ((int)(((byte)(150)))), ((int)(((byte)(186)))));
            this.radgrpbxCaptureInput.Controls.Add(this.tableLayoutPanel10);
            this.radgrpbxCaptureInput.Font = new System.Drawing.Font("Arial", 11.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.radgrpbxCaptureInput.FooterImageIndex = -1;
            this.radgrpbxCaptureInput.FooterImageKey = "";
            this.radgrpbxCaptureInput.HeaderImageIndex = -1;
            this.radgrpbxCaptureInput.HeaderImageKey = "";
            this.radgrpbxCaptureInput.HeaderMargin = new System.Windows.Forms.Padding(0);
            this.radgrpbxCaptureInput.HeaderText = "Capture Input";
            this.radgrpbxCaptureInput.Location = new System.Drawing.Point(276, 163);
            this.radgrpbxCaptureInput.Name = "radgrpbxCaptureInput";
            this.radgrpbxCaptureInput.Padding = new System.Windows.Forms.Padding(10, 20, 10, 10);
            // 
            // 
            // 
            this.radgrpbxCaptureInput.RootElement.Padding = new System.Windows.Forms.Padding(10, 20, 10, 10);
            this.radgrpbxCaptureInput.Size = new System.Drawing.Size(235, 80);
            this.radgrpbxCaptureInput.TabIndex = 4;
            this.radgrpbxCaptureInput.Text = "Capture Input";
            ((Telerik.WinControls.Primitives.FillPrimitive)(this.radgrpbxCaptureInput.GetChildAt(0).GetChildAt(0).GetChildAt(0))).BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(142)))), ((int)(((byte)(150)))), ((int)(((byte)(186)))));
            ((Telerik.WinControls.Primitives.BorderPrimitive)(this.radgrpbxCaptureInput.GetChildAt(0).GetChildAt(0).GetChildAt(1))).ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(185)))), ((int)(((byte)(199)))), ((int)(((byte)(220)))));
            ((Telerik.WinControls.UI.GroupBoxHeader)(this.radgrpbxCaptureInput.GetChildAt(0).GetChildAt(1))).ForeColor = System.Drawing.Color.WhiteSmoke;
            ((Telerik.WinControls.Primitives.FillPrimitive)(this.radgrpbxCaptureInput.GetChildAt(0).GetChildAt(1).GetChildAt(0))).BackColor2 = System.Drawing.Color.FromArgb(((int)(((byte)(142)))), ((int)(((byte)(150)))), ((int)(((byte)(186)))));
            ((Telerik.WinControls.Primitives.FillPrimitive)(this.radgrpbxCaptureInput.GetChildAt(0).GetChildAt(1).GetChildAt(0))).BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(142)))), ((int)(((byte)(150)))), ((int)(((byte)(186)))));
            ((Telerik.WinControls.Primitives.BorderPrimitive)(this.radgrpbxCaptureInput.GetChildAt(0).GetChildAt(1).GetChildAt(1))).Width = 0F;
            // 
            // tableLayoutPanel10
            // 
            this.tableLayoutPanel10.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(142)))), ((int)(((byte)(150)))), ((int)(((byte)(186)))));
            this.tableLayoutPanel10.ColumnCount = 1;
            this.tableLayoutPanel10.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 50F));
            this.tableLayoutPanel10.Controls.Add(this.radradiobtnTonometer, 0, 1);
            this.tableLayoutPanel10.Controls.Add(this.radradiobtnPressureCuff, 0, 0);
            this.tableLayoutPanel10.Location = new System.Drawing.Point(15, 23);
            this.tableLayoutPanel10.Name = "tableLayoutPanel10";
            this.tableLayoutPanel10.RowCount = 2;
            this.tableLayoutPanel10.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 50F));
            this.tableLayoutPanel10.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 50F));
            this.tableLayoutPanel10.Size = new System.Drawing.Size(176, 47);
            this.tableLayoutPanel10.TabIndex = 3;
            // 
            // radradiobtnTonometer
            // 
            this.radradiobtnTonometer.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(142)))), ((int)(((byte)(150)))), ((int)(((byte)(186)))));
            this.radradiobtnTonometer.Font = new System.Drawing.Font("Arial", 11.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.radradiobtnTonometer.ForeColor = System.Drawing.Color.WhiteSmoke;
            this.radradiobtnTonometer.Location = new System.Drawing.Point(3, 26);
            this.radradiobtnTonometer.Name = "radradiobtnTonometer";
            // 
            // 
            // 
            this.radradiobtnTonometer.RootElement.ForeColor = System.Drawing.Color.WhiteSmoke;
            this.radradiobtnTonometer.Size = new System.Drawing.Size(170, 18);
            this.radradiobtnTonometer.TabIndex = 1;
            this.radradiobtnTonometer.Text = "Tonometer";
            this.radradiobtnTonometer.Visible = false;
            this.radradiobtnTonometer.MouseClick += new System.Windows.Forms.MouseEventHandler(this.radchkbxPatientPrivacy_MouseClick);
            // 
            // radradiobtnPressureCuff
            // 
            this.radradiobtnPressureCuff.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(142)))), ((int)(((byte)(150)))), ((int)(((byte)(186)))));
            this.radradiobtnPressureCuff.Font = new System.Drawing.Font("Arial", 11.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.radradiobtnPressureCuff.ForeColor = System.Drawing.Color.WhiteSmoke;
            this.radradiobtnPressureCuff.Location = new System.Drawing.Point(3, 3);
            this.radradiobtnPressureCuff.Name = "radradiobtnPressureCuff";
            // 
            // 
            // 
            this.radradiobtnPressureCuff.RootElement.ForeColor = System.Drawing.Color.WhiteSmoke;
            this.radradiobtnPressureCuff.Size = new System.Drawing.Size(170, 17);
            this.radradiobtnPressureCuff.TabIndex = 0;
            this.radradiobtnPressureCuff.Text = "Pressure Cuff";
            this.radradiobtnPressureCuff.ToggleState = Telerik.WinControls.Enumerations.ToggleState.On;
            this.radradiobtnPressureCuff.MouseClick += new System.Windows.Forms.MouseEventHandler(this.radchkbxPatientPrivacy_MouseClick);
            // 
            // radgrpbxCaptureTime
            // 
            this.radgrpbxCaptureTime.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(142)))), ((int)(((byte)(150)))), ((int)(((byte)(186)))));
            this.radgrpbxCaptureTime.Controls.Add(this.tableLayoutPanel9);
            this.radgrpbxCaptureTime.Font = new System.Drawing.Font("Arial", 11.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.radgrpbxCaptureTime.FooterImageIndex = -1;
            this.radgrpbxCaptureTime.FooterImageKey = "";
            this.radgrpbxCaptureTime.HeaderImageIndex = -1;
            this.radgrpbxCaptureTime.HeaderImageKey = "";
            this.radgrpbxCaptureTime.HeaderMargin = new System.Windows.Forms.Padding(0);
            this.radgrpbxCaptureTime.HeaderText = "CaptureTime";
            this.radgrpbxCaptureTime.Location = new System.Drawing.Point(22, 47);
            this.radgrpbxCaptureTime.Name = "radgrpbxCaptureTime";
            this.radgrpbxCaptureTime.Padding = new System.Windows.Forms.Padding(10, 20, 10, 10);
            // 
            // 
            // 
            this.radgrpbxCaptureTime.RootElement.Padding = new System.Windows.Forms.Padding(10, 20, 10, 10);
            this.radgrpbxCaptureTime.Size = new System.Drawing.Size(223, 102);
            this.radgrpbxCaptureTime.TabIndex = 0;
            this.radgrpbxCaptureTime.Text = "CaptureTime";
            ((Telerik.WinControls.Primitives.FillPrimitive)(this.radgrpbxCaptureTime.GetChildAt(0).GetChildAt(0).GetChildAt(0))).BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(142)))), ((int)(((byte)(150)))), ((int)(((byte)(186)))));
            ((Telerik.WinControls.Primitives.BorderPrimitive)(this.radgrpbxCaptureTime.GetChildAt(0).GetChildAt(0).GetChildAt(1))).ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(185)))), ((int)(((byte)(199)))), ((int)(((byte)(220)))));
            ((Telerik.WinControls.UI.GroupBoxHeader)(this.radgrpbxCaptureTime.GetChildAt(0).GetChildAt(1))).ForeColor = System.Drawing.Color.WhiteSmoke;
            ((Telerik.WinControls.Primitives.FillPrimitive)(this.radgrpbxCaptureTime.GetChildAt(0).GetChildAt(1).GetChildAt(0))).BackColor2 = System.Drawing.Color.FromArgb(((int)(((byte)(142)))), ((int)(((byte)(150)))), ((int)(((byte)(186)))));
            ((Telerik.WinControls.Primitives.FillPrimitive)(this.radgrpbxCaptureTime.GetChildAt(0).GetChildAt(1).GetChildAt(0))).BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(142)))), ((int)(((byte)(150)))), ((int)(((byte)(186)))));
            ((Telerik.WinControls.Primitives.BorderPrimitive)(this.radgrpbxCaptureTime.GetChildAt(0).GetChildAt(1).GetChildAt(1))).Width = 0F;
            // 
            // tableLayoutPanel9
            // 
            this.tableLayoutPanel9.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(142)))), ((int)(((byte)(150)))), ((int)(((byte)(186)))));
            this.tableLayoutPanel9.ColumnCount = 1;
            this.tableLayoutPanel9.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 50F));
            this.tableLayoutPanel9.Controls.Add(this.rad5SecondsPWA, 0, 0);
            this.tableLayoutPanel9.Controls.Add(this.rad10SecondsPWA, 0, 1);
            this.tableLayoutPanel9.Controls.Add(this.rad20SecondsPWA, 0, 2);
            this.tableLayoutPanel9.Location = new System.Drawing.Point(17, 25);
            this.tableLayoutPanel9.Name = "tableLayoutPanel9";
            this.tableLayoutPanel9.RowCount = 3;
            this.tableLayoutPanel9.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 50F));
            this.tableLayoutPanel9.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 50F));
            this.tableLayoutPanel9.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Absolute, 20F));
            this.tableLayoutPanel9.Size = new System.Drawing.Size(189, 67);
            this.tableLayoutPanel9.TabIndex = 6;
            // 
            // rad5SecondsPWA
            // 
            this.rad5SecondsPWA.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(142)))), ((int)(((byte)(150)))), ((int)(((byte)(186)))));
            this.rad5SecondsPWA.Font = new System.Drawing.Font("Arial", 11.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.rad5SecondsPWA.ForeColor = System.Drawing.Color.WhiteSmoke;
            this.rad5SecondsPWA.Location = new System.Drawing.Point(3, 3);
            this.rad5SecondsPWA.Name = "rad5SecondsPWA";
            // 
            // 
            // 
            this.rad5SecondsPWA.RootElement.ForeColor = System.Drawing.Color.WhiteSmoke;
            this.rad5SecondsPWA.Size = new System.Drawing.Size(110, 14);
            this.rad5SecondsPWA.TabIndex = 0;
            this.rad5SecondsPWA.Text = "5 seconds";
            this.rad5SecondsPWA.Click += new System.EventHandler(this.radradiobtnImperial_Click);
            // 
            // rad10SecondsPWA
            // 
            this.rad10SecondsPWA.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(142)))), ((int)(((byte)(150)))), ((int)(((byte)(186)))));
            this.rad10SecondsPWA.Font = new System.Drawing.Font("Arial", 11.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.rad10SecondsPWA.ForeColor = System.Drawing.Color.WhiteSmoke;
            this.rad10SecondsPWA.Location = new System.Drawing.Point(3, 26);
            this.rad10SecondsPWA.Name = "rad10SecondsPWA";
            // 
            // 
            // 
            this.rad10SecondsPWA.RootElement.ForeColor = System.Drawing.Color.WhiteSmoke;
            this.rad10SecondsPWA.Size = new System.Drawing.Size(110, 14);
            this.rad10SecondsPWA.TabIndex = 1;
            this.rad10SecondsPWA.Text = "10 seconds";
            this.rad10SecondsPWA.Click += new System.EventHandler(this.radradiobtnImperial_Click);
            // 
            // rad20SecondsPWA
            // 
            this.rad20SecondsPWA.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(142)))), ((int)(((byte)(150)))), ((int)(((byte)(186)))));
            this.rad20SecondsPWA.Font = new System.Drawing.Font("Arial", 11.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.rad20SecondsPWA.ForeColor = System.Drawing.Color.WhiteSmoke;
            this.rad20SecondsPWA.Location = new System.Drawing.Point(3, 49);
            this.rad20SecondsPWA.Name = "rad20SecondsPWA";
            // 
            // 
            // 
            this.rad20SecondsPWA.RootElement.ForeColor = System.Drawing.Color.WhiteSmoke;
            this.rad20SecondsPWA.Size = new System.Drawing.Size(110, 14);
            this.rad20SecondsPWA.TabIndex = 2;
            this.rad20SecondsPWA.Text = "20 seconds";
            this.rad20SecondsPWA.Click += new System.EventHandler(this.radradiobtnImperial_Click);
            // 
            // documentWindow4
            // 
            this.documentWindow4.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(142)))), ((int)(((byte)(150)))), ((int)(((byte)(186)))));
            this.documentWindow4.Controls.Add(this.docWndBPSettings);
            this.documentWindow4.Controls.Add(this.radGroupBox1);
            this.documentWindow4.DocumentButtons = Telerik.WinControls.UI.Docking.DocumentStripButtons.None;
            this.documentWindow4.Location = new System.Drawing.Point(6, 33);
            this.documentWindow4.Name = "documentWindow4";
            this.documentWindow4.Size = new System.Drawing.Size(540, 372);
            this.documentWindow4.Text = "BP Settings";
            // 
            // docWndBPSettings
            // 
            this.docWndBPSettings.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(142)))), ((int)(((byte)(150)))), ((int)(((byte)(186)))));
            this.docWndBPSettings.Controls.Add(this.radgrpbxBloodPressures);
            this.docWndBPSettings.Controls.Add(this.radgrpbxAutoPWA);
            this.docWndBPSettings.Controls.Add(this.radgrpbxNumberOfAssessments);
            this.docWndBPSettings.Controls.Add(this.radgrpbxBPDevice);
            this.docWndBPSettings.DocumentButtons = Telerik.WinControls.UI.Docking.DocumentStripButtons.None;
            this.docWndBPSettings.Location = new System.Drawing.Point(-5, -5);
            this.docWndBPSettings.Name = "docWndBPSettings";
            this.docWndBPSettings.Size = new System.Drawing.Size(540, 372);
            this.docWndBPSettings.Text = "BP Settings";
            // 
            // radgrpbxBloodPressures
            // 
            this.radgrpbxBloodPressures.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(142)))), ((int)(((byte)(150)))), ((int)(((byte)(186)))));
            this.radgrpbxBloodPressures.Controls.Add(this.tableLayoutPanel11);
            this.radgrpbxBloodPressures.Font = new System.Drawing.Font("Arial", 11.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.radgrpbxBloodPressures.FooterImageIndex = -1;
            this.radgrpbxBloodPressures.FooterImageKey = "";
            this.radgrpbxBloodPressures.HeaderImageIndex = -1;
            this.radgrpbxBloodPressures.HeaderImageKey = "";
            this.radgrpbxBloodPressures.HeaderMargin = new System.Windows.Forms.Padding(0);
            this.radgrpbxBloodPressures.HeaderText = "Blood Pressures";
            this.radgrpbxBloodPressures.Location = new System.Drawing.Point(290, 186);
            this.radgrpbxBloodPressures.Name = "radgrpbxBloodPressures";
            this.radgrpbxBloodPressures.Padding = new System.Windows.Forms.Padding(10, 20, 10, 10);
            // 
            // 
            // 
            this.radgrpbxBloodPressures.RootElement.Padding = new System.Windows.Forms.Padding(10, 20, 10, 10);
            this.radgrpbxBloodPressures.Size = new System.Drawing.Size(235, 161);
            this.radgrpbxBloodPressures.TabIndex = 3;
            this.radgrpbxBloodPressures.Text = "Blood Pressures";
            this.radgrpbxBloodPressures.Visible = false;
            ((Telerik.WinControls.Primitives.FillPrimitive)(this.radgrpbxBloodPressures.GetChildAt(0).GetChildAt(0).GetChildAt(0))).BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(142)))), ((int)(((byte)(150)))), ((int)(((byte)(186)))));
            ((Telerik.WinControls.Primitives.BorderPrimitive)(this.radgrpbxBloodPressures.GetChildAt(0).GetChildAt(0).GetChildAt(1))).ForeColor2 = System.Drawing.SystemColors.ControlLight;
            ((Telerik.WinControls.Primitives.BorderPrimitive)(this.radgrpbxBloodPressures.GetChildAt(0).GetChildAt(0).GetChildAt(1))).ForeColor3 = System.Drawing.SystemColors.ControlLight;
            ((Telerik.WinControls.Primitives.BorderPrimitive)(this.radgrpbxBloodPressures.GetChildAt(0).GetChildAt(0).GetChildAt(1))).ForeColor4 = System.Drawing.SystemColors.ControlLight;
            ((Telerik.WinControls.Primitives.BorderPrimitive)(this.radgrpbxBloodPressures.GetChildAt(0).GetChildAt(0).GetChildAt(1))).ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(185)))), ((int)(((byte)(199)))), ((int)(((byte)(220)))));
            ((Telerik.WinControls.UI.GroupBoxHeader)(this.radgrpbxBloodPressures.GetChildAt(0).GetChildAt(1))).ForeColor = System.Drawing.Color.WhiteSmoke;
            ((Telerik.WinControls.Primitives.FillPrimitive)(this.radgrpbxBloodPressures.GetChildAt(0).GetChildAt(1).GetChildAt(0))).BackColor2 = System.Drawing.Color.FromArgb(((int)(((byte)(142)))), ((int)(((byte)(150)))), ((int)(((byte)(186)))));
            ((Telerik.WinControls.Primitives.FillPrimitive)(this.radgrpbxBloodPressures.GetChildAt(0).GetChildAt(1).GetChildAt(0))).BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(142)))), ((int)(((byte)(150)))), ((int)(((byte)(186)))));
            ((Telerik.WinControls.Primitives.BorderPrimitive)(this.radgrpbxBloodPressures.GetChildAt(0).GetChildAt(1).GetChildAt(1))).Width = 0F;
            // 
            // tableLayoutPanel11
            // 
            this.tableLayoutPanel11.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(142)))), ((int)(((byte)(150)))), ((int)(((byte)(186)))));
            this.tableLayoutPanel11.ColumnCount = 1;
            this.tableLayoutPanel11.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 50F));
            this.tableLayoutPanel11.Controls.Add(this.radradiobtnMPandDP, 0, 2);
            this.tableLayoutPanel11.Controls.Add(this.radradiobtnSPandDP, 0, 0);
            this.tableLayoutPanel11.Controls.Add(this.radradiobtnSPandMP, 0, 1);
            this.tableLayoutPanel11.Location = new System.Drawing.Point(13, 55);
            this.tableLayoutPanel11.Name = "tableLayoutPanel11";
            this.tableLayoutPanel11.RowCount = 3;
            this.tableLayoutPanel11.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 50F));
            this.tableLayoutPanel11.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 50F));
            this.tableLayoutPanel11.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Absolute, 21F));
            this.tableLayoutPanel11.Size = new System.Drawing.Size(189, 70);
            this.tableLayoutPanel11.TabIndex = 3;
            // 
            // radradiobtnMPandDP
            // 
            this.radradiobtnMPandDP.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(142)))), ((int)(((byte)(150)))), ((int)(((byte)(186)))));
            this.radradiobtnMPandDP.Font = new System.Drawing.Font("Arial", 11.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.radradiobtnMPandDP.ForeColor = System.Drawing.Color.WhiteSmoke;
            this.radradiobtnMPandDP.Location = new System.Drawing.Point(3, 51);
            this.radradiobtnMPandDP.Name = "radradiobtnMPandDP";
            // 
            // 
            // 
            this.radradiobtnMPandDP.RootElement.ForeColor = System.Drawing.Color.WhiteSmoke;
            this.radradiobtnMPandDP.Size = new System.Drawing.Size(145, 15);
            this.radradiobtnMPandDP.TabIndex = 2;
            this.radradiobtnMPandDP.Text = "MP and DP";
            this.radradiobtnMPandDP.MouseClick += new System.Windows.Forms.MouseEventHandler(this.radchkbxPatientPrivacy_MouseClick);
            this.radradiobtnMPandDP.Click += new System.EventHandler(this.radradiobtnImperial_Click);
            // 
            // radradiobtnSPandDP
            // 
            this.radradiobtnSPandDP.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(142)))), ((int)(((byte)(150)))), ((int)(((byte)(186)))));
            this.radradiobtnSPandDP.Font = new System.Drawing.Font("Arial", 11.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.radradiobtnSPandDP.ForeColor = System.Drawing.Color.WhiteSmoke;
            this.radradiobtnSPandDP.Location = new System.Drawing.Point(3, 3);
            this.radradiobtnSPandDP.Name = "radradiobtnSPandDP";
            // 
            // 
            // 
            this.radradiobtnSPandDP.RootElement.ForeColor = System.Drawing.Color.WhiteSmoke;
            this.radradiobtnSPandDP.Size = new System.Drawing.Size(145, 18);
            this.radradiobtnSPandDP.TabIndex = 0;
            this.radradiobtnSPandDP.Text = "SP and DP";
            this.radradiobtnSPandDP.MouseClick += new System.Windows.Forms.MouseEventHandler(this.radchkbxPatientPrivacy_MouseClick);
            this.radradiobtnSPandDP.Click += new System.EventHandler(this.radradiobtnImperial_Click);
            // 
            // radradiobtnSPandMP
            // 
            this.radradiobtnSPandMP.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(142)))), ((int)(((byte)(150)))), ((int)(((byte)(186)))));
            this.radradiobtnSPandMP.Font = new System.Drawing.Font("Arial", 11.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.radradiobtnSPandMP.ForeColor = System.Drawing.Color.WhiteSmoke;
            this.radradiobtnSPandMP.Location = new System.Drawing.Point(3, 27);
            this.radradiobtnSPandMP.Name = "radradiobtnSPandMP";
            // 
            // 
            // 
            this.radradiobtnSPandMP.RootElement.ForeColor = System.Drawing.Color.WhiteSmoke;
            this.radradiobtnSPandMP.Size = new System.Drawing.Size(145, 18);
            this.radradiobtnSPandMP.TabIndex = 1;
            this.radradiobtnSPandMP.Text = "SP and MP";
            this.radradiobtnSPandMP.MouseClick += new System.Windows.Forms.MouseEventHandler(this.radchkbxPatientPrivacy_MouseClick);
            this.radradiobtnSPandMP.Click += new System.EventHandler(this.radradiobtnImperial_Click);
            // 
            // radgrpbxAutoPWA
            // 
            this.radgrpbxAutoPWA.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(142)))), ((int)(((byte)(150)))), ((int)(((byte)(186)))));
            this.radgrpbxAutoPWA.Controls.Add(this.guipnlBPAutoPWARangeDetails);
            this.radgrpbxAutoPWA.Controls.Add(this.radradiochkDP);
            this.radgrpbxAutoPWA.Controls.Add(this.radradiochkPP);
            this.radgrpbxAutoPWA.Controls.Add(this.radradiochkSP);
            this.radgrpbxAutoPWA.Font = new System.Drawing.Font("Arial", 11.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.radgrpbxAutoPWA.FooterImageIndex = -1;
            this.radgrpbxAutoPWA.FooterImageKey = "";
            this.radgrpbxAutoPWA.HeaderImageIndex = -1;
            this.radgrpbxAutoPWA.HeaderImageKey = "";
            this.radgrpbxAutoPWA.HeaderMargin = new System.Windows.Forms.Padding(0);
            this.radgrpbxAutoPWA.HeaderText = "Auto PWA";
            this.radgrpbxAutoPWA.Location = new System.Drawing.Point(17, 44);
            this.radgrpbxAutoPWA.Name = "radgrpbxAutoPWA";
            this.radgrpbxAutoPWA.Padding = new System.Windows.Forms.Padding(10, 20, 10, 10);
            // 
            // 
            // 
            this.radgrpbxAutoPWA.RootElement.Padding = new System.Windows.Forms.Padding(10, 20, 10, 10);
            this.radgrpbxAutoPWA.Size = new System.Drawing.Size(255, 120);
            this.radgrpbxAutoPWA.TabIndex = 0;
            this.radgrpbxAutoPWA.Text = "Auto PWA";
            this.radgrpbxAutoPWA.Visible = false;
            ((Telerik.WinControls.Primitives.FillPrimitive)(this.radgrpbxAutoPWA.GetChildAt(0).GetChildAt(0).GetChildAt(0))).BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(142)))), ((int)(((byte)(150)))), ((int)(((byte)(186)))));
            ((Telerik.WinControls.Primitives.BorderPrimitive)(this.radgrpbxAutoPWA.GetChildAt(0).GetChildAt(0).GetChildAt(1))).ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(185)))), ((int)(((byte)(199)))), ((int)(((byte)(220)))));
            ((Telerik.WinControls.UI.GroupBoxHeader)(this.radgrpbxAutoPWA.GetChildAt(0).GetChildAt(1))).ForeColor = System.Drawing.Color.WhiteSmoke;
            ((Telerik.WinControls.Primitives.FillPrimitive)(this.radgrpbxAutoPWA.GetChildAt(0).GetChildAt(1).GetChildAt(0))).BackColor2 = System.Drawing.Color.FromArgb(((int)(((byte)(142)))), ((int)(((byte)(150)))), ((int)(((byte)(186)))));
            ((Telerik.WinControls.Primitives.FillPrimitive)(this.radgrpbxAutoPWA.GetChildAt(0).GetChildAt(1).GetChildAt(0))).BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(142)))), ((int)(((byte)(150)))), ((int)(((byte)(186)))));
            ((Telerik.WinControls.Primitives.BorderPrimitive)(this.radgrpbxAutoPWA.GetChildAt(0).GetChildAt(1).GetChildAt(1))).Width = 0F;
            // 
            // guipnlBPAutoPWARangeDetails
            // 
            this.guipnlBPAutoPWARangeDetails.Controls.Add(this.guiradtxtDPThreshold);
            this.guipnlBPAutoPWARangeDetails.Controls.Add(this.guiradtxtPPThreshold);
            this.guipnlBPAutoPWARangeDetails.Controls.Add(this.guiradtxtSPThreshold);
            this.guipnlBPAutoPWARangeDetails.Location = new System.Drawing.Point(126, 24);
            this.guipnlBPAutoPWARangeDetails.Name = "guipnlBPAutoPWARangeDetails";
            this.guipnlBPAutoPWARangeDetails.Size = new System.Drawing.Size(100, 83);
            this.guipnlBPAutoPWARangeDetails.TabIndex = 7;
            // 
            // guiradtxtDPThreshold
            // 
            this.guiradtxtDPThreshold.Font = new System.Drawing.Font("Arial", 11.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.guiradtxtDPThreshold.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(29)))), ((int)(((byte)(30)))), ((int)(((byte)(55)))));
            this.guiradtxtDPThreshold.Location = new System.Drawing.Point(4, 59);
            this.guiradtxtDPThreshold.Name = "guiradtxtDPThreshold";
            // 
            // 
            // 
            this.guiradtxtDPThreshold.RootElement.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(29)))), ((int)(((byte)(30)))), ((int)(((byte)(55)))));
            this.guiradtxtDPThreshold.Size = new System.Drawing.Size(50, 23);
            this.guiradtxtDPThreshold.TabIndex = 6;
            this.guiradtxtDPThreshold.TabStop = false;
            this.guiradtxtDPThreshold.Leave += new System.EventHandler(this.guiradtxtDPThreshold_Leave);
            this.guiradtxtDPThreshold.TextChanged += new System.EventHandler(this.guiradtxtSPThreshold_TextChanged);
            // 
            // guiradtxtPPThreshold
            // 
            this.guiradtxtPPThreshold.Font = new System.Drawing.Font("Arial", 11.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.guiradtxtPPThreshold.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(29)))), ((int)(((byte)(30)))), ((int)(((byte)(55)))));
            this.guiradtxtPPThreshold.Location = new System.Drawing.Point(4, 30);
            this.guiradtxtPPThreshold.Name = "guiradtxtPPThreshold";
            // 
            // 
            // 
            this.guiradtxtPPThreshold.RootElement.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(29)))), ((int)(((byte)(30)))), ((int)(((byte)(55)))));
            this.guiradtxtPPThreshold.Size = new System.Drawing.Size(50, 23);
            this.guiradtxtPPThreshold.TabIndex = 6;
            this.guiradtxtPPThreshold.TabStop = false;
            this.guiradtxtPPThreshold.Leave += new System.EventHandler(this.guiradtxtPPThreshold_Leave);
            this.guiradtxtPPThreshold.TextChanged += new System.EventHandler(this.guiradtxtSPThreshold_TextChanged);
            // 
            // guiradtxtSPThreshold
            // 
            this.guiradtxtSPThreshold.Font = new System.Drawing.Font("Arial", 11.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.guiradtxtSPThreshold.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(29)))), ((int)(((byte)(30)))), ((int)(((byte)(55)))));
            this.guiradtxtSPThreshold.Location = new System.Drawing.Point(4, 4);
            this.guiradtxtSPThreshold.Name = "guiradtxtSPThreshold";
            // 
            // 
            // 
            this.guiradtxtSPThreshold.RootElement.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(29)))), ((int)(((byte)(30)))), ((int)(((byte)(55)))));
            this.guiradtxtSPThreshold.Size = new System.Drawing.Size(50, 23);
            this.guiradtxtSPThreshold.TabIndex = 5;
            this.guiradtxtSPThreshold.TabStop = false;
            this.guiradtxtSPThreshold.Leave += new System.EventHandler(this.guiradtxtSPThreshold_Leave);
            this.guiradtxtSPThreshold.TextChanged += new System.EventHandler(this.guiradtxtSPThreshold_TextChanged);
            this.guiradtxtSPThreshold.Click += new System.EventHandler(this.guiradtxtSPThreshold_TextChanged);
            // 
            // radradiochkDP
            // 
            this.radradiochkDP.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(142)))), ((int)(((byte)(150)))), ((int)(((byte)(186)))));
            this.radradiochkDP.Font = new System.Drawing.Font("Arial", 11.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.radradiochkDP.ForeColor = System.Drawing.Color.WhiteSmoke;
            this.radradiochkDP.Location = new System.Drawing.Point(17, 83);
            this.radradiochkDP.Name = "radradiochkDP";
            // 
            // 
            // 
            this.radradiochkDP.RootElement.ForeColor = System.Drawing.Color.WhiteSmoke;
            this.radradiochkDP.RootElement.StretchHorizontally = true;
            this.radradiochkDP.RootElement.StretchVertically = true;
            this.radradiochkDP.Size = new System.Drawing.Size(95, 21);
            this.radradiochkDP.TabIndex = 4;
            this.radradiochkDP.Text = "    If DP >=";
            this.radradiochkDP.MouseClick += new System.Windows.Forms.MouseEventHandler(this.radchkbxPatientPrivacy_MouseClick);
            // 
            // radradiochkPP
            // 
            this.radradiochkPP.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(142)))), ((int)(((byte)(150)))), ((int)(((byte)(186)))));
            this.radradiochkPP.Font = new System.Drawing.Font("Arial", 11.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.radradiochkPP.ForeColor = System.Drawing.Color.WhiteSmoke;
            this.radradiochkPP.Location = new System.Drawing.Point(17, 56);
            this.radradiochkPP.Name = "radradiochkPP";
            // 
            // 
            // 
            this.radradiochkPP.RootElement.ForeColor = System.Drawing.Color.WhiteSmoke;
            this.radradiochkPP.RootElement.StretchHorizontally = true;
            this.radradiochkPP.RootElement.StretchVertically = true;
            this.radradiochkPP.Size = new System.Drawing.Size(94, 21);
            this.radradiochkPP.TabIndex = 2;
            this.radradiochkPP.Text = "    If PP >=";
            this.radradiochkPP.MouseClick += new System.Windows.Forms.MouseEventHandler(this.radchkbxPatientPrivacy_MouseClick);
            // 
            // radradiochkSP
            // 
            this.radradiochkSP.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(142)))), ((int)(((byte)(150)))), ((int)(((byte)(186)))));
            this.radradiochkSP.Font = new System.Drawing.Font("Arial", 11.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.radradiochkSP.ForeColor = System.Drawing.Color.WhiteSmoke;
            this.radradiochkSP.Location = new System.Drawing.Point(17, 29);
            this.radradiochkSP.Name = "radradiochkSP";
            // 
            // 
            // 
            this.radradiochkSP.RootElement.ForeColor = System.Drawing.Color.WhiteSmoke;
            this.radradiochkSP.RootElement.StretchHorizontally = true;
            this.radradiochkSP.RootElement.StretchVertically = true;
            this.radradiochkSP.Size = new System.Drawing.Size(94, 21);
            this.radradiochkSP.TabIndex = 0;
            this.radradiochkSP.Text = "    If SP >=";
            this.radradiochkSP.MouseClick += new System.Windows.Forms.MouseEventHandler(this.radchkbxPatientPrivacy_MouseClick);
            // 
            // radgrpbxNumberOfAssessments
            // 
            this.radgrpbxNumberOfAssessments.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(142)))), ((int)(((byte)(150)))), ((int)(((byte)(186)))));
            this.radgrpbxNumberOfAssessments.Controls.Add(this.tableLayoutPanel14);
            this.radgrpbxNumberOfAssessments.Font = new System.Drawing.Font("Arial", 11.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.radgrpbxNumberOfAssessments.FooterImageIndex = -1;
            this.radgrpbxNumberOfAssessments.FooterImageKey = "";
            this.radgrpbxNumberOfAssessments.HeaderImageIndex = -1;
            this.radgrpbxNumberOfAssessments.HeaderImageKey = "";
            this.radgrpbxNumberOfAssessments.HeaderMargin = new System.Windows.Forms.Padding(0);
            this.radgrpbxNumberOfAssessments.HeaderText = "Number of Assessments";
            this.radgrpbxNumberOfAssessments.Location = new System.Drawing.Point(17, 186);
            this.radgrpbxNumberOfAssessments.Name = "radgrpbxNumberOfAssessments";
            this.radgrpbxNumberOfAssessments.Padding = new System.Windows.Forms.Padding(10, 20, 10, 10);
            // 
            // 
            // 
            this.radgrpbxNumberOfAssessments.RootElement.Padding = new System.Windows.Forms.Padding(10, 20, 10, 10);
            this.radgrpbxNumberOfAssessments.Size = new System.Drawing.Size(255, 161);
            this.radgrpbxNumberOfAssessments.TabIndex = 1;
            this.radgrpbxNumberOfAssessments.Text = "Number of Assessments";
            this.radgrpbxNumberOfAssessments.Visible = false;
            ((Telerik.WinControls.Primitives.FillPrimitive)(this.radgrpbxNumberOfAssessments.GetChildAt(0).GetChildAt(0).GetChildAt(0))).BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(142)))), ((int)(((byte)(150)))), ((int)(((byte)(186)))));
            ((Telerik.WinControls.Primitives.BorderPrimitive)(this.radgrpbxNumberOfAssessments.GetChildAt(0).GetChildAt(0).GetChildAt(1))).ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(185)))), ((int)(((byte)(199)))), ((int)(((byte)(220)))));
            ((Telerik.WinControls.UI.GroupBoxHeader)(this.radgrpbxNumberOfAssessments.GetChildAt(0).GetChildAt(1))).ForeColor = System.Drawing.Color.WhiteSmoke;
            ((Telerik.WinControls.Primitives.FillPrimitive)(this.radgrpbxNumberOfAssessments.GetChildAt(0).GetChildAt(1).GetChildAt(0))).BackColor2 = System.Drawing.Color.FromArgb(((int)(((byte)(142)))), ((int)(((byte)(150)))), ((int)(((byte)(186)))));
            ((Telerik.WinControls.Primitives.FillPrimitive)(this.radgrpbxNumberOfAssessments.GetChildAt(0).GetChildAt(1).GetChildAt(0))).BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(142)))), ((int)(((byte)(150)))), ((int)(((byte)(186)))));
            ((Telerik.WinControls.Primitives.BorderPrimitive)(this.radgrpbxNumberOfAssessments.GetChildAt(0).GetChildAt(1).GetChildAt(1))).Width = 0F;
            // 
            // tableLayoutPanel14
            // 
            this.tableLayoutPanel14.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(142)))), ((int)(((byte)(150)))), ((int)(((byte)(186)))));
            this.tableLayoutPanel14.ColumnCount = 1;
            this.tableLayoutPanel14.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 100F));
            this.tableLayoutPanel14.Controls.Add(this.radradiobtnAssessment5, 0, 4);
            this.tableLayoutPanel14.Controls.Add(this.radradiobtnAssessment1, 0, 0);
            this.tableLayoutPanel14.Controls.Add(this.radradiobtnAssessment2, 0, 1);
            this.tableLayoutPanel14.Controls.Add(this.radradiobtnAssessment3, 0, 2);
            this.tableLayoutPanel14.Controls.Add(this.radradiobtnAssessment4, 0, 3);
            this.tableLayoutPanel14.Location = new System.Drawing.Point(17, 32);
            this.tableLayoutPanel14.Name = "tableLayoutPanel14";
            this.tableLayoutPanel14.RowCount = 5;
            this.tableLayoutPanel14.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 20F));
            this.tableLayoutPanel14.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 20F));
            this.tableLayoutPanel14.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 20F));
            this.tableLayoutPanel14.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 20F));
            this.tableLayoutPanel14.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 20F));
            this.tableLayoutPanel14.Size = new System.Drawing.Size(189, 117);
            this.tableLayoutPanel14.TabIndex = 6;
            // 
            // radradiobtnAssessment5
            // 
            this.radradiobtnAssessment5.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(142)))), ((int)(((byte)(150)))), ((int)(((byte)(186)))));
            this.radradiobtnAssessment5.Font = new System.Drawing.Font("Arial", 11.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.radradiobtnAssessment5.ForeColor = System.Drawing.Color.WhiteSmoke;
            this.radradiobtnAssessment5.Location = new System.Drawing.Point(3, 95);
            this.radradiobtnAssessment5.Name = "radradiobtnAssessment5";
            // 
            // 
            // 
            this.radradiobtnAssessment5.RootElement.ForeColor = System.Drawing.Color.WhiteSmoke;
            this.radradiobtnAssessment5.Size = new System.Drawing.Size(110, 17);
            this.radradiobtnAssessment5.TabIndex = 4;
            this.radradiobtnAssessment5.Text = "5";
            this.radradiobtnAssessment5.Click += new System.EventHandler(this.radradiobtnImperial_Click);
            // 
            // radradiobtnAssessment1
            // 
            this.radradiobtnAssessment1.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(142)))), ((int)(((byte)(150)))), ((int)(((byte)(186)))));
            this.radradiobtnAssessment1.Font = new System.Drawing.Font("Arial", 11.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.radradiobtnAssessment1.ForeColor = System.Drawing.Color.WhiteSmoke;
            this.radradiobtnAssessment1.Location = new System.Drawing.Point(3, 3);
            this.radradiobtnAssessment1.Name = "radradiobtnAssessment1";
            // 
            // 
            // 
            this.radradiobtnAssessment1.RootElement.ForeColor = System.Drawing.Color.WhiteSmoke;
            this.radradiobtnAssessment1.Size = new System.Drawing.Size(110, 17);
            this.radradiobtnAssessment1.TabIndex = 0;
            this.radradiobtnAssessment1.Text = "1";
            this.radradiobtnAssessment1.Click += new System.EventHandler(this.radradiobtnImperial_Click);
            // 
            // radradiobtnAssessment2
            // 
            this.radradiobtnAssessment2.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(142)))), ((int)(((byte)(150)))), ((int)(((byte)(186)))));
            this.radradiobtnAssessment2.Font = new System.Drawing.Font("Arial", 11.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.radradiobtnAssessment2.ForeColor = System.Drawing.Color.WhiteSmoke;
            this.radradiobtnAssessment2.Location = new System.Drawing.Point(3, 26);
            this.radradiobtnAssessment2.Name = "radradiobtnAssessment2";
            // 
            // 
            // 
            this.radradiobtnAssessment2.RootElement.ForeColor = System.Drawing.Color.WhiteSmoke;
            this.radradiobtnAssessment2.Size = new System.Drawing.Size(110, 17);
            this.radradiobtnAssessment2.TabIndex = 1;
            this.radradiobtnAssessment2.Text = "2";
            this.radradiobtnAssessment2.Click += new System.EventHandler(this.radradiobtnImperial_Click);
            // 
            // radradiobtnAssessment3
            // 
            this.radradiobtnAssessment3.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(142)))), ((int)(((byte)(150)))), ((int)(((byte)(186)))));
            this.radradiobtnAssessment3.Font = new System.Drawing.Font("Arial", 11.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.radradiobtnAssessment3.ForeColor = System.Drawing.Color.WhiteSmoke;
            this.radradiobtnAssessment3.Location = new System.Drawing.Point(3, 49);
            this.radradiobtnAssessment3.Name = "radradiobtnAssessment3";
            // 
            // 
            // 
            this.radradiobtnAssessment3.RootElement.ForeColor = System.Drawing.Color.WhiteSmoke;
            this.radradiobtnAssessment3.Size = new System.Drawing.Size(110, 14);
            this.radradiobtnAssessment3.TabIndex = 2;
            this.radradiobtnAssessment3.Text = "3";
            this.radradiobtnAssessment3.Click += new System.EventHandler(this.radradiobtnImperial_Click);
            // 
            // radradiobtnAssessment4
            // 
            this.radradiobtnAssessment4.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(142)))), ((int)(((byte)(150)))), ((int)(((byte)(186)))));
            this.radradiobtnAssessment4.Font = new System.Drawing.Font("Arial", 11.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.radradiobtnAssessment4.ForeColor = System.Drawing.Color.WhiteSmoke;
            this.radradiobtnAssessment4.Location = new System.Drawing.Point(3, 72);
            this.radradiobtnAssessment4.Name = "radradiobtnAssessment4";
            // 
            // 
            // 
            this.radradiobtnAssessment4.RootElement.ForeColor = System.Drawing.Color.WhiteSmoke;
            this.radradiobtnAssessment4.Size = new System.Drawing.Size(110, 17);
            this.radradiobtnAssessment4.TabIndex = 3;
            this.radradiobtnAssessment4.Text = "4";
            this.radradiobtnAssessment4.Click += new System.EventHandler(this.radradiobtnImperial_Click);
            // 
            // radgrpbxBPDevice
            // 
            this.radgrpbxBPDevice.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(142)))), ((int)(((byte)(150)))), ((int)(((byte)(186)))));
            this.radgrpbxBPDevice.Controls.Add(this.radradiobtnOther);
            this.radgrpbxBPDevice.Controls.Add(this.radradiobtnSphygcomor);
            this.radgrpbxBPDevice.Font = new System.Drawing.Font("Arial", 11.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.radgrpbxBPDevice.FooterImageIndex = -1;
            this.radgrpbxBPDevice.FooterImageKey = "";
            this.radgrpbxBPDevice.HeaderImageIndex = -1;
            this.radgrpbxBPDevice.HeaderImageKey = "";
            this.radgrpbxBPDevice.HeaderMargin = new System.Windows.Forms.Padding(0);
            this.radgrpbxBPDevice.HeaderText = "BP Device";
            this.radgrpbxBPDevice.Location = new System.Drawing.Point(290, 44);
            this.radgrpbxBPDevice.Name = "radgrpbxBPDevice";
            this.radgrpbxBPDevice.Padding = new System.Windows.Forms.Padding(10, 20, 10, 10);
            // 
            // 
            // 
            this.radgrpbxBPDevice.RootElement.Padding = new System.Windows.Forms.Padding(10, 20, 10, 10);
            this.radgrpbxBPDevice.Size = new System.Drawing.Size(235, 120);
            this.radgrpbxBPDevice.TabIndex = 2;
            this.radgrpbxBPDevice.Text = "BP Device";
            this.radgrpbxBPDevice.Visible = false;
            ((Telerik.WinControls.Primitives.FillPrimitive)(this.radgrpbxBPDevice.GetChildAt(0).GetChildAt(0).GetChildAt(0))).BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(142)))), ((int)(((byte)(150)))), ((int)(((byte)(186)))));
            ((Telerik.WinControls.Primitives.BorderPrimitive)(this.radgrpbxBPDevice.GetChildAt(0).GetChildAt(0).GetChildAt(1))).ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(185)))), ((int)(((byte)(199)))), ((int)(((byte)(220)))));
            ((Telerik.WinControls.UI.GroupBoxHeader)(this.radgrpbxBPDevice.GetChildAt(0).GetChildAt(1))).ForeColor = System.Drawing.Color.WhiteSmoke;
            ((Telerik.WinControls.Primitives.FillPrimitive)(this.radgrpbxBPDevice.GetChildAt(0).GetChildAt(1).GetChildAt(0))).BackColor2 = System.Drawing.Color.FromArgb(((int)(((byte)(142)))), ((int)(((byte)(150)))), ((int)(((byte)(186)))));
            ((Telerik.WinControls.Primitives.FillPrimitive)(this.radgrpbxBPDevice.GetChildAt(0).GetChildAt(1).GetChildAt(0))).BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(142)))), ((int)(((byte)(150)))), ((int)(((byte)(186)))));
            ((Telerik.WinControls.Primitives.BorderPrimitive)(this.radgrpbxBPDevice.GetChildAt(0).GetChildAt(1).GetChildAt(1))).Width = 0F;
            // 
            // radradiobtnOther
            // 
            this.radradiobtnOther.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(142)))), ((int)(((byte)(150)))), ((int)(((byte)(186)))));
            this.radradiobtnOther.Font = new System.Drawing.Font("Arial", 11.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.radradiobtnOther.ForeColor = System.Drawing.Color.WhiteSmoke;
            this.radradiobtnOther.Location = new System.Drawing.Point(20, 67);
            this.radradiobtnOther.Name = "radradiobtnOther";
            // 
            // 
            // 
            this.radradiobtnOther.RootElement.ForeColor = System.Drawing.Color.WhiteSmoke;
            this.radradiobtnOther.Size = new System.Drawing.Size(110, 17);
            this.radradiobtnOther.TabIndex = 3;
            this.radradiobtnOther.Text = "Other ";
            this.radradiobtnOther.Click += new System.EventHandler(this.radradiobtnImperial_Click);
            // 
            // radradiobtnSphygcomor
            // 
            this.radradiobtnSphygcomor.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(142)))), ((int)(((byte)(150)))), ((int)(((byte)(186)))));
            this.radradiobtnSphygcomor.Font = new System.Drawing.Font("Arial", 11.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.radradiobtnSphygcomor.ForeColor = System.Drawing.Color.WhiteSmoke;
            this.radradiobtnSphygcomor.Location = new System.Drawing.Point(20, 43);
            this.radradiobtnSphygcomor.Name = "radradiobtnSphygcomor";
            // 
            // 
            // 
            this.radradiobtnSphygcomor.RootElement.ForeColor = System.Drawing.Color.WhiteSmoke;
            this.radradiobtnSphygcomor.Size = new System.Drawing.Size(110, 17);
            this.radradiobtnSphygcomor.TabIndex = 2;
            this.radradiobtnSphygcomor.Text = "Sphygmocor";
            this.radradiobtnSphygcomor.Click += new System.EventHandler(this.radradiobtnImperial_Click);
            // 
            // radGroupBox1
            // 
            this.radGroupBox1.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(142)))), ((int)(((byte)(150)))), ((int)(((byte)(186)))));
            this.radGroupBox1.Controls.Add(this.tableLayoutPanel8);
            this.radGroupBox1.Font = new System.Drawing.Font("Arial", 11.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.radGroupBox1.FooterImageIndex = -1;
            this.radGroupBox1.FooterImageKey = "";
            this.radGroupBox1.HeaderImageIndex = -1;
            this.radGroupBox1.HeaderImageKey = "";
            this.radGroupBox1.HeaderMargin = new System.Windows.Forms.Padding(0);
            this.radGroupBox1.HeaderText = "Blood Pressures";
            this.radGroupBox1.Location = new System.Drawing.Point(298, 187);
            this.radGroupBox1.Name = "radGroupBox1";
            this.radGroupBox1.Padding = new System.Windows.Forms.Padding(10, 20, 10, 10);
            // 
            // 
            // 
            this.radGroupBox1.RootElement.Padding = new System.Windows.Forms.Padding(10, 20, 10, 10);
            this.radGroupBox1.Size = new System.Drawing.Size(228, 128);
            this.radGroupBox1.TabIndex = 2;
            this.radGroupBox1.Text = "Blood Pressures";
            ((Telerik.WinControls.Primitives.FillPrimitive)(this.radGroupBox1.GetChildAt(0).GetChildAt(0).GetChildAt(0))).BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(142)))), ((int)(((byte)(150)))), ((int)(((byte)(186)))));
            ((Telerik.WinControls.Primitives.BorderPrimitive)(this.radGroupBox1.GetChildAt(0).GetChildAt(0).GetChildAt(1))).ForeColor2 = System.Drawing.SystemColors.ControlLight;
            ((Telerik.WinControls.Primitives.BorderPrimitive)(this.radGroupBox1.GetChildAt(0).GetChildAt(0).GetChildAt(1))).ForeColor3 = System.Drawing.SystemColors.ControlLight;
            ((Telerik.WinControls.Primitives.BorderPrimitive)(this.radGroupBox1.GetChildAt(0).GetChildAt(0).GetChildAt(1))).ForeColor4 = System.Drawing.SystemColors.ControlLight;
            ((Telerik.WinControls.Primitives.BorderPrimitive)(this.radGroupBox1.GetChildAt(0).GetChildAt(0).GetChildAt(1))).ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(185)))), ((int)(((byte)(199)))), ((int)(((byte)(220)))));
            ((Telerik.WinControls.UI.GroupBoxHeader)(this.radGroupBox1.GetChildAt(0).GetChildAt(1))).ForeColor = System.Drawing.Color.WhiteSmoke;
            ((Telerik.WinControls.Primitives.FillPrimitive)(this.radGroupBox1.GetChildAt(0).GetChildAt(1).GetChildAt(0))).BackColor2 = System.Drawing.Color.FromArgb(((int)(((byte)(142)))), ((int)(((byte)(150)))), ((int)(((byte)(186)))));
            ((Telerik.WinControls.Primitives.FillPrimitive)(this.radGroupBox1.GetChildAt(0).GetChildAt(1).GetChildAt(0))).BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(142)))), ((int)(((byte)(150)))), ((int)(((byte)(186)))));
            ((Telerik.WinControls.Primitives.BorderPrimitive)(this.radGroupBox1.GetChildAt(0).GetChildAt(1).GetChildAt(1))).Width = 0F;
            // 
            // tableLayoutPanel8
            // 
            this.tableLayoutPanel8.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(142)))), ((int)(((byte)(150)))), ((int)(((byte)(186)))));
            this.tableLayoutPanel8.ColumnCount = 1;
            this.tableLayoutPanel8.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 50F));
            this.tableLayoutPanel8.Controls.Add(this.radRadioButton1, 0, 2);
            this.tableLayoutPanel8.Controls.Add(this.radRadioButton4, 0, 0);
            this.tableLayoutPanel8.Controls.Add(this.radRadioButton5, 0, 1);
            this.tableLayoutPanel8.Location = new System.Drawing.Point(11, 36);
            this.tableLayoutPanel8.Name = "tableLayoutPanel8";
            this.tableLayoutPanel8.RowCount = 3;
            this.tableLayoutPanel8.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 50F));
            this.tableLayoutPanel8.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 50F));
            this.tableLayoutPanel8.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Absolute, 21F));
            this.tableLayoutPanel8.Size = new System.Drawing.Size(189, 64);
            this.tableLayoutPanel8.TabIndex = 3;
            // 
            // radRadioButton1
            // 
            this.radRadioButton1.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(142)))), ((int)(((byte)(150)))), ((int)(((byte)(186)))));
            this.radRadioButton1.Font = new System.Drawing.Font("Arial", 11.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.radRadioButton1.ForeColor = System.Drawing.Color.WhiteSmoke;
            this.radRadioButton1.Location = new System.Drawing.Point(3, 45);
            this.radRadioButton1.Name = "radRadioButton1";
            // 
            // 
            // 
            this.radRadioButton1.RootElement.ForeColor = System.Drawing.Color.WhiteSmoke;
            this.radRadioButton1.Size = new System.Drawing.Size(110, 16);
            this.radRadioButton1.TabIndex = 2;
            this.radRadioButton1.Text = "MP and DP";
            // 
            // radRadioButton4
            // 
            this.radRadioButton4.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(142)))), ((int)(((byte)(150)))), ((int)(((byte)(186)))));
            this.radRadioButton4.Font = new System.Drawing.Font("Arial", 11.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.radRadioButton4.ForeColor = System.Drawing.Color.WhiteSmoke;
            this.radRadioButton4.Location = new System.Drawing.Point(3, 3);
            this.radRadioButton4.Name = "radRadioButton4";
            // 
            // 
            // 
            this.radRadioButton4.RootElement.ForeColor = System.Drawing.Color.WhiteSmoke;
            this.radRadioButton4.Size = new System.Drawing.Size(110, 15);
            this.radRadioButton4.TabIndex = 0;
            this.radRadioButton4.Text = "SP and DP";
            // 
            // radRadioButton5
            // 
            this.radRadioButton5.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(142)))), ((int)(((byte)(150)))), ((int)(((byte)(186)))));
            this.radRadioButton5.Font = new System.Drawing.Font("Arial", 11.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.radRadioButton5.ForeColor = System.Drawing.Color.WhiteSmoke;
            this.radRadioButton5.Location = new System.Drawing.Point(3, 24);
            this.radRadioButton5.Name = "radRadioButton5";
            // 
            // 
            // 
            this.radRadioButton5.RootElement.ForeColor = System.Drawing.Color.WhiteSmoke;
            this.radRadioButton5.Size = new System.Drawing.Size(110, 15);
            this.radRadioButton5.TabIndex = 1;
            this.radRadioButton5.Text = "SP and MP";
            // 
            // radbtnDefaults
            // 
            this.radbtnDefaults.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right)));
            this.radbtnDefaults.Font = new System.Drawing.Font("Arial", 11.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.radbtnDefaults.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(23)))), ((int)(((byte)(29)))), ((int)(((byte)(55)))));
            this.radbtnDefaults.Location = new System.Drawing.Point(466, 429);
            this.radbtnDefaults.Name = "radbtnDefaults";
            // 
            // 
            // 
            this.radbtnDefaults.RootElement.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(23)))), ((int)(((byte)(29)))), ((int)(((byte)(55)))));
            this.radbtnDefaults.Size = new System.Drawing.Size(80, 25);
            this.radbtnDefaults.TabIndex = 13;
            this.radbtnDefaults.Text = "Defaults";
            this.radbtnDefaults.Click += new System.EventHandler(this.radbtnDefaults_Click);
            ((Telerik.WinControls.UI.RadButtonElement)(this.radbtnDefaults.GetChildAt(0))).Text = "Defaults";
            ((Telerik.WinControls.Primitives.FillPrimitive)(this.radbtnDefaults.GetChildAt(0).GetChildAt(0))).BackColor2 = System.Drawing.Color.FromArgb(((int)(((byte)(172)))), ((int)(((byte)(177)))), ((int)(((byte)(204)))));
            ((Telerik.WinControls.Primitives.FillPrimitive)(this.radbtnDefaults.GetChildAt(0).GetChildAt(0))).BackColor3 = System.Drawing.Color.FromArgb(((int)(((byte)(172)))), ((int)(((byte)(177)))), ((int)(((byte)(204)))));
            ((Telerik.WinControls.Primitives.FillPrimitive)(this.radbtnDefaults.GetChildAt(0).GetChildAt(0))).BackColor4 = System.Drawing.Color.FromArgb(((int)(((byte)(142)))), ((int)(((byte)(150)))), ((int)(((byte)(186)))));
            ((Telerik.WinControls.Primitives.FillPrimitive)(this.radbtnDefaults.GetChildAt(0).GetChildAt(0))).BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(225)))), ((int)(((byte)(228)))), ((int)(((byte)(243)))));
            ((Telerik.WinControls.Primitives.BorderPrimitive)(this.radbtnDefaults.GetChildAt(0).GetChildAt(2))).ForeColor = System.Drawing.Color.White;
            // 
            // radbtnCancel
            // 
            this.radbtnCancel.Anchor = System.Windows.Forms.AnchorStyles.Bottom;
            this.radbtnCancel.Font = new System.Drawing.Font("Arial", 11.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.radbtnCancel.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(23)))), ((int)(((byte)(29)))), ((int)(((byte)(55)))));
            this.radbtnCancel.Location = new System.Drawing.Point(381, 429);
            this.radbtnCancel.Name = "radbtnCancel";
            // 
            // 
            // 
            this.radbtnCancel.RootElement.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(23)))), ((int)(((byte)(29)))), ((int)(((byte)(55)))));
            this.radbtnCancel.Size = new System.Drawing.Size(80, 25);
            this.radbtnCancel.TabIndex = 12;
            this.radbtnCancel.Text = "Cancel";
            this.radbtnCancel.Click += new System.EventHandler(this.radbtnCancel_Click);
            ((Telerik.WinControls.UI.RadButtonElement)(this.radbtnCancel.GetChildAt(0))).Text = "Cancel";
            ((Telerik.WinControls.Primitives.FillPrimitive)(this.radbtnCancel.GetChildAt(0).GetChildAt(0))).BackColor2 = System.Drawing.Color.FromArgb(((int)(((byte)(172)))), ((int)(((byte)(177)))), ((int)(((byte)(204)))));
            ((Telerik.WinControls.Primitives.FillPrimitive)(this.radbtnCancel.GetChildAt(0).GetChildAt(0))).BackColor3 = System.Drawing.Color.FromArgb(((int)(((byte)(172)))), ((int)(((byte)(177)))), ((int)(((byte)(204)))));
            ((Telerik.WinControls.Primitives.FillPrimitive)(this.radbtnCancel.GetChildAt(0).GetChildAt(0))).BackColor4 = System.Drawing.Color.FromArgb(((int)(((byte)(142)))), ((int)(((byte)(150)))), ((int)(((byte)(186)))));
            ((Telerik.WinControls.Primitives.FillPrimitive)(this.radbtnCancel.GetChildAt(0).GetChildAt(0))).BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(225)))), ((int)(((byte)(228)))), ((int)(((byte)(243)))));
            ((Telerik.WinControls.Primitives.BorderPrimitive)(this.radbtnCancel.GetChildAt(0).GetChildAt(2))).ForeColor = System.Drawing.Color.White;
            // 
            // radbtnSave
            // 
            this.radbtnSave.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
            this.radbtnSave.Font = new System.Drawing.Font("Arial", 11.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.radbtnSave.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(23)))), ((int)(((byte)(29)))), ((int)(((byte)(55)))));
            this.radbtnSave.Location = new System.Drawing.Point(296, 429);
            this.radbtnSave.Name = "radbtnSave";
            // 
            // 
            // 
            this.radbtnSave.RootElement.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(23)))), ((int)(((byte)(29)))), ((int)(((byte)(55)))));
            this.radbtnSave.Size = new System.Drawing.Size(80, 25);
            this.radbtnSave.TabIndex = 11;
            this.radbtnSave.Text = " Save ";
            this.radbtnSave.Click += new System.EventHandler(this.radbtnSave_Click);
            ((Telerik.WinControls.UI.RadButtonElement)(this.radbtnSave.GetChildAt(0))).Text = " Save ";
            ((Telerik.WinControls.Primitives.FillPrimitive)(this.radbtnSave.GetChildAt(0).GetChildAt(0))).BackColor2 = System.Drawing.Color.FromArgb(((int)(((byte)(172)))), ((int)(((byte)(177)))), ((int)(((byte)(204)))));
            ((Telerik.WinControls.Primitives.FillPrimitive)(this.radbtnSave.GetChildAt(0).GetChildAt(0))).BackColor3 = System.Drawing.Color.FromArgb(((int)(((byte)(172)))), ((int)(((byte)(177)))), ((int)(((byte)(204)))));
            ((Telerik.WinControls.Primitives.FillPrimitive)(this.radbtnSave.GetChildAt(0).GetChildAt(0))).BackColor4 = System.Drawing.Color.FromArgb(((int)(((byte)(142)))), ((int)(((byte)(150)))), ((int)(((byte)(186)))));
            ((Telerik.WinControls.Primitives.FillPrimitive)(this.radbtnSave.GetChildAt(0).GetChildAt(0))).BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(225)))), ((int)(((byte)(228)))), ((int)(((byte)(243)))));
            ((Telerik.WinControls.Primitives.BorderPrimitive)(this.radbtnSave.GetChildAt(0).GetChildAt(2))).ForeColor = System.Drawing.Color.White;
            // 
            // tableLayoutPanel3
            // 
            this.tableLayoutPanel3.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(233)))), ((int)(((byte)(240)))), ((int)(((byte)(249)))));
            this.tableLayoutPanel3.ColumnCount = 1;
            this.tableLayoutPanel3.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 50F));
            this.tableLayoutPanel3.Controls.Add(this.radRadioButton2, 0, 0);
            this.tableLayoutPanel3.Location = new System.Drawing.Point(0, 0);
            this.tableLayoutPanel3.Name = "tableLayoutPanel3";
            this.tableLayoutPanel3.RowCount = 2;
            this.tableLayoutPanel3.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Absolute, 20F));
            this.tableLayoutPanel3.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Absolute, 20F));
            this.tableLayoutPanel3.Size = new System.Drawing.Size(200, 100);
            this.tableLayoutPanel3.TabIndex = 0;
            // 
            // radRadioButton2
            // 
            this.radRadioButton2.Location = new System.Drawing.Point(3, 3);
            this.radRadioButton2.Name = "radRadioButton2";
            this.radRadioButton2.Size = new System.Drawing.Size(110, 14);
            this.radRadioButton2.TabIndex = 0;
            this.radRadioButton2.Text = "mm";
            // 
            // radRadioButton3
            // 
            this.radRadioButton3.Location = new System.Drawing.Point(3, 26);
            this.radRadioButton3.Name = "radRadioButton3";
            this.radRadioButton3.Size = new System.Drawing.Size(110, 18);
            this.radRadioButton3.TabIndex = 1;
            this.radRadioButton3.Text = "cm";
            // 
            // object_2c8b2f0f_b093_4256_82f7_ffe6d52c17dc
            // 
            this.object_2c8b2f0f_b093_4256_82f7_ffe6d52c17dc.Name = "object_2c8b2f0f_b093_4256_82f7_ffe6d52c17dc";
            this.object_2c8b2f0f_b093_4256_82f7_ffe6d52c17dc.Padding = new System.Windows.Forms.Padding(10, 20, 10, 10);
            this.object_2c8b2f0f_b093_4256_82f7_ffe6d52c17dc.StretchHorizontally = true;
            this.object_2c8b2f0f_b093_4256_82f7_ffe6d52c17dc.StretchVertically = true;
            // 
            // documentWindow2
            // 
            this.documentWindow2.Location = new System.Drawing.Point(0, 0);
            this.documentWindow2.Name = "documentWindow2";
            this.documentWindow2.Size = new System.Drawing.Size(200, 200);
            this.documentWindow2.Text = "documentWindow2";
            // 
            // documentWindow3
            // 
            this.documentWindow3.Location = new System.Drawing.Point(0, 0);
            this.documentWindow3.Name = "documentWindow3";
            this.documentWindow3.Size = new System.Drawing.Size(200, 200);
            this.documentWindow3.Text = "documentWindow3";
            // 
            // radgrpbxBloodPressure
            // 
            this.radgrpbxBloodPressure.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(142)))), ((int)(((byte)(150)))), ((int)(((byte)(186)))));
            this.radgrpbxBloodPressure.FooterImageIndex = -1;
            this.radgrpbxBloodPressure.FooterImageKey = "";
            this.radgrpbxBloodPressure.HeaderImageIndex = -1;
            this.radgrpbxBloodPressure.HeaderImageKey = "";
            this.radgrpbxBloodPressure.HeaderMargin = new System.Windows.Forms.Padding(0);
            this.radgrpbxBloodPressure.HeaderText = "";
            this.radgrpbxBloodPressure.Location = new System.Drawing.Point(0, 0);
            this.radgrpbxBloodPressure.Name = "radgrpbxBloodPressure";
            this.radgrpbxBloodPressure.Padding = new System.Windows.Forms.Padding(10, 20, 10, 10);
            // 
            // 
            // 
            this.radgrpbxBloodPressure.RootElement.Padding = new System.Windows.Forms.Padding(10, 20, 10, 10);
            this.radgrpbxBloodPressure.Size = new System.Drawing.Size(200, 100);
            this.radgrpbxBloodPressure.TabIndex = 0;
            ((Telerik.WinControls.Primitives.FillPrimitive)(this.radgrpbxBloodPressure.GetChildAt(0).GetChildAt(0).GetChildAt(0))).BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(142)))), ((int)(((byte)(150)))), ((int)(((byte)(186)))));
            ((Telerik.WinControls.Primitives.BorderPrimitive)(this.radgrpbxBloodPressure.GetChildAt(0).GetChildAt(0).GetChildAt(1))).ForeColor2 = System.Drawing.SystemColors.ControlLight;
            ((Telerik.WinControls.Primitives.BorderPrimitive)(this.radgrpbxBloodPressure.GetChildAt(0).GetChildAt(0).GetChildAt(1))).ForeColor3 = System.Drawing.SystemColors.ControlLight;
            ((Telerik.WinControls.Primitives.BorderPrimitive)(this.radgrpbxBloodPressure.GetChildAt(0).GetChildAt(0).GetChildAt(1))).ForeColor4 = System.Drawing.SystemColors.ControlLight;
            ((Telerik.WinControls.Primitives.BorderPrimitive)(this.radgrpbxBloodPressure.GetChildAt(0).GetChildAt(0).GetChildAt(1))).ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(185)))), ((int)(((byte)(199)))), ((int)(((byte)(220)))));
            ((Telerik.WinControls.UI.GroupBoxHeader)(this.radgrpbxBloodPressure.GetChildAt(0).GetChildAt(1))).ForeColor = System.Drawing.Color.WhiteSmoke;
            ((Telerik.WinControls.Primitives.FillPrimitive)(this.radgrpbxBloodPressure.GetChildAt(0).GetChildAt(1).GetChildAt(0))).BackColor2 = System.Drawing.Color.FromArgb(((int)(((byte)(142)))), ((int)(((byte)(150)))), ((int)(((byte)(186)))));
            ((Telerik.WinControls.Primitives.FillPrimitive)(this.radgrpbxBloodPressure.GetChildAt(0).GetChildAt(1).GetChildAt(0))).BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(142)))), ((int)(((byte)(150)))), ((int)(((byte)(186)))));
            ((Telerik.WinControls.Primitives.BorderPrimitive)(this.radgrpbxBloodPressure.GetChildAt(0).GetChildAt(1).GetChildAt(1))).Width = 0F;
            // 
            // tableLayoutPanel1
            // 
            this.tableLayoutPanel1.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(142)))), ((int)(((byte)(150)))), ((int)(((byte)(186)))));
            this.tableLayoutPanel1.ColumnCount = 1;
            this.tableLayoutPanel1.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 50F));
            this.tableLayoutPanel1.Location = new System.Drawing.Point(0, 0);
            this.tableLayoutPanel1.Name = "tableLayoutPanel1";
            this.tableLayoutPanel1.RowCount = 3;
            this.tableLayoutPanel1.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Absolute, 20F));
            this.tableLayoutPanel1.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Absolute, 20F));
            this.tableLayoutPanel1.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Absolute, 20F));
            this.tableLayoutPanel1.Size = new System.Drawing.Size(200, 100);
            this.tableLayoutPanel1.TabIndex = 0;
            // 
            // frmSettingsWindow
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(142)))), ((int)(((byte)(150)))), ((int)(((byte)(186)))));
            this.ClientSize = new System.Drawing.Size(570, 462);
            this.Controls.Add(this.radbtnDefaults);
            this.Controls.Add(this.radDock1);
            this.Controls.Add(this.radbtnCancel);
            this.Controls.Add(this.radbtnSave);
            this.Font = new System.Drawing.Font("Arial", 11.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(23)))), ((int)(((byte)(29)))), ((int)(((byte)(55)))));
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.MaximizeBox = false;
            this.MinimizeBox = false;
            this.Name = "frmSettingsWindow";
            // 
            // 
            // 
            this.RootElement.ApplyShapeToControl = true;
            this.RootElement.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(23)))), ((int)(((byte)(29)))), ((int)(((byte)(55)))));
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterParent;
            this.Text = "User Settings";
            this.Load += new System.EventHandler(this.SettingsWindow_Load);
            ((System.ComponentModel.ISupportInitialize)(this.radDock1)).EndInit();
            this.radDock1.ResumeLayout(false);
            this.docWndGeneralSettings.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.radgrpbxstartupMode)).EndInit();
            this.radgrpbxstartupMode.ResumeLayout(false);
            this.tableLayoutPanel12.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.radradiobtnPWVMode)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.radradiobtnPWAMode)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.radgrpbxStartupScreen)).EndInit();
            this.radgrpbxStartupScreen.ResumeLayout(false);
            this.tableLayoutPanel7.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.radradiobtnQuickStart)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.radradiobtnSetup)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.radgrpbxReports)).EndInit();
            this.radgrpbxReports.ResumeLayout(false);
            this.tableLayoutPanel5.ResumeLayout(false);
            this.tableLayoutPanel5.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.radlblReportLogo)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.radtxtReportTitle)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.radlblReportTitle)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.picbxReportLogo)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.radbtnChange)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.radgrpbxCommsPort)).EndInit();
            this.radgrpbxCommsPort.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.comboBoxCommsPort)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.radgrpbxHeightWeightUnits)).EndInit();
            this.radgrpbxHeightWeightUnits.ResumeLayout(false);
            this.tableLayoutPanel2.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.radradiobtnImperial)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.radradiobtnMetric)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.radgrpbxSetupScreen)).EndInit();
            this.radgrpbxSetupScreen.ResumeLayout(false);
            this.radgrpbxSetupScreen.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.radchkbxPatientPrivacy)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.documentContainer1)).EndInit();
            this.documentContainer1.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.documentTabStrip1)).EndInit();
            this.documentTabStrip1.ResumeLayout(false);
            this.docWndPWVSettings.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.radgrpbxCaptureGuide)).EndInit();
            this.radgrpbxCaptureGuide.ResumeLayout(false);
            this.tableLayoutPanel13.ResumeLayout(false);
            this.tableLayoutPanel13.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.radchkAutoInflate)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.radchkAutoCapture)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.radgrpbxDefaultReport)).EndInit();
            this.radgrpbxDefaultReport.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.comboDefaultReport)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.guiradgrpDefaultReport)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.radgrpbxSimulationTypes)).EndInit();
            this.radgrpbxSimulationTypes.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.comboSimulationFiles)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.radgrpSimulationFiles)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.radgrpCaptureTime)).EndInit();
            this.radgrpCaptureTime.ResumeLayout(false);
            this.tableLayoutPanel4.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.rad5Seconds)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.rad10Seconds)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.rad20Seconds)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.radgrpReportScreen)).EndInit();
            this.radgrpReportScreen.ResumeLayout(false);
            this.radgrpReportScreen.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.radchkReferenceRange)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.radchkNormalRange)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.radgrpPwvDistanceUnits)).EndInit();
            this.radgrpPwvDistanceUnits.ResumeLayout(false);
            this.tableLayoutPanel6.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.radmm)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.radcm)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.radgrpCuffLocation)).EndInit();
            this.radgrpCuffLocation.ResumeLayout(false);
            this.radgrpCuffLocation.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.radchkFemoralToCuff)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.radgrpbxPwvDistanceMethod)).EndInit();
            this.radgrpbxPwvDistanceMethod.ResumeLayout(false);
            this.tblPWVDistanceMethod.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.radDirect)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.radSubtracting)).EndInit();
            this.docWndPWASettings.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.guiradgrpbxPWASimulationFiles)).EndInit();
            this.guiradgrpbxPWASimulationFiles.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.radDropDownList3)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.radgrpbxCaptureGuidePWA)).EndInit();
            this.radgrpbxCaptureGuidePWA.ResumeLayout(false);
            this.radgrpbxCaptureGuidePWA.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.radchkAutoCapturePWA)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.radchkGuidanceBars)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.radgrpbxClinicalReport)).EndInit();
            this.radgrpbxClinicalReport.ResumeLayout(false);
            this.radgrpbxClinicalReport.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.radchkBlindStudy)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.radchkAumentationIndexHR75)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.radchkAumentationIndex)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.radgrpbxCaptureInput)).EndInit();
            this.radgrpbxCaptureInput.ResumeLayout(false);
            this.tableLayoutPanel10.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.radradiobtnTonometer)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.radradiobtnPressureCuff)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.radgrpbxCaptureTime)).EndInit();
            this.radgrpbxCaptureTime.ResumeLayout(false);
            this.tableLayoutPanel9.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.rad5SecondsPWA)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.rad10SecondsPWA)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.rad20SecondsPWA)).EndInit();
            this.documentWindow4.ResumeLayout(false);
            this.docWndBPSettings.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.radgrpbxBloodPressures)).EndInit();
            this.radgrpbxBloodPressures.ResumeLayout(false);
            this.tableLayoutPanel11.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.radradiobtnMPandDP)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.radradiobtnSPandDP)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.radradiobtnSPandMP)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.radgrpbxAutoPWA)).EndInit();
            this.radgrpbxAutoPWA.ResumeLayout(false);
            this.radgrpbxAutoPWA.PerformLayout();
            this.guipnlBPAutoPWARangeDetails.ResumeLayout(false);
            this.guipnlBPAutoPWARangeDetails.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.guiradtxtDPThreshold)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.guiradtxtPPThreshold)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.guiradtxtSPThreshold)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.radradiochkDP)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.radradiochkPP)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.radradiochkSP)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.radgrpbxNumberOfAssessments)).EndInit();
            this.radgrpbxNumberOfAssessments.ResumeLayout(false);
            this.tableLayoutPanel14.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.radradiobtnAssessment5)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.radradiobtnAssessment1)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.radradiobtnAssessment2)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.radradiobtnAssessment3)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.radradiobtnAssessment4)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.radgrpbxBPDevice)).EndInit();
            this.radgrpbxBPDevice.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.radradiobtnOther)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.radradiobtnSphygcomor)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.radGroupBox1)).EndInit();
            this.radGroupBox1.ResumeLayout(false);
            this.tableLayoutPanel8.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.radRadioButton1)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.radRadioButton4)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.radRadioButton5)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.radbtnDefaults)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.radbtnCancel)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.radbtnSave)).EndInit();
            this.tableLayoutPanel3.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.radRadioButton2)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.radRadioButton3)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.radgrpbxBloodPressure)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this)).EndInit();
            this.ResumeLayout(false);

        }

        #endregion

        private Telerik.WinControls.UI.Docking.RadDock radDock1;
        private Telerik.WinControls.UI.Docking.DocumentWindow docWndPWVSettings;
        private Telerik.WinControls.UI.Docking.DocumentContainer documentContainer1;
        private Telerik.WinControls.UI.Docking.DocumentTabStrip documentTabStrip1;
        private Telerik.WinControls.UI.Docking.DocumentWindow docWndGeneralSettings;
        private System.Windows.Forms.TableLayoutPanel tableLayoutPanel2;
        private Telerik.WinControls.UI.RadRadioButton radradiobtnMetric;
        private Telerik.WinControls.UI.RadRadioButton radradiobtnImperial;
        private Telerik.WinControls.UI.RadCheckBox radchkbxPatientPrivacy;
        private System.Windows.Forms.TableLayoutPanel tableLayoutPanel5;
        private Telerik.WinControls.UI.RadButton radbtnChange;
        private Telerik.WinControls.UI.RadLabel radlblReportTitle;
        private Telerik.WinControls.UI.RadLabel radlblReportLogo;
        private Telerik.WinControls.UI.RadTextBox radtxtReportTitle;
        private System.Windows.Forms.PictureBox picbxReportLogo;
        private Telerik.WinControls.UI.RadGroupBox radgrpbxSetupScreen;
        private Telerik.WinControls.UI.RadGroupBox radgrpbxHeightWeightUnits;
        private Telerik.WinControls.UI.RadGroupBox radgrpbxCommsPort;
        private Telerik.WinControls.UI.RadGroupBox radgrpbxReports;
        private Telerik.WinControls.UI.RadButton radbtnDefaults;
        private Telerik.WinControls.UI.RadButton radbtnCancel;
        private Telerik.WinControls.UI.RadGroupBox radgrpPwvDistanceUnits;
        private Telerik.WinControls.UI.RadGroupBox radgrpCuffLocation;
        private Telerik.WinControls.UI.RadGroupBox radgrpbxPwvDistanceMethod;
        private Telerik.WinControls.UI.RadGroupBox radgrpSimulationFiles;
        private Telerik.WinControls.UI.RadGroupBox radgrpCaptureTime;
        private Telerik.WinControls.UI.RadGroupBox radgrpReportScreen;
        private System.Windows.Forms.TableLayoutPanel tableLayoutPanel6;
        private System.Windows.Forms.TableLayoutPanel tblPWVDistanceMethod;
        private Telerik.WinControls.UI.RadRadioButton radSubtracting;
        private Telerik.WinControls.UI.RadRadioButton radDirect;
        private System.Windows.Forms.TableLayoutPanel tableLayoutPanel4;
        private Telerik.WinControls.UI.RadRadioButton rad5Seconds;
        private Telerik.WinControls.UI.RadRadioButton rad10Seconds;
        private Telerik.WinControls.UI.RadRadioButton rad20Seconds;
        private Telerik.WinControls.UI.RadRadioButton radmm;
        private Telerik.WinControls.UI.RadRadioButton radcm;
        private Telerik.WinControls.UI.RadRadioButton radRadioButton2;
        private System.Windows.Forms.TableLayoutPanel tableLayoutPanel3;
        private Telerik.WinControls.UI.RadRadioButton radRadioButton3;
        public Telerik.WinControls.UI.RadButton radbtnSave;
        private Telerik.WinControls.UI.RadGroupBox guiradgrpDefaultReport;
        private Telerik.WinControls.UI.RadCheckBox radchkNormalRange;
        private Telerik.WinControls.UI.RadCheckBox radchkReferenceRange;
        private Telerik.WinControls.UI.RadCheckBox radchkFemoralToCuff;
        private Telerik.WinControls.RootRadElement object_2c8b2f0f_b093_4256_82f7_ffe6d52c17dc;
        private Telerik.WinControls.UI.RadDropDownList comboBoxCommsPort;
        private Telerik.WinControls.UI.RadGroupBox radgrpbxStartupScreen;
        private System.Windows.Forms.TableLayoutPanel tableLayoutPanel7;
        private Telerik.WinControls.UI.RadRadioButton radradiobtnQuickStart;
        private Telerik.WinControls.UI.RadRadioButton radradiobtnSetup;
        private Telerik.WinControls.UI.Docking.DocumentWindow docWndPWASettings;
        private Telerik.WinControls.UI.Docking.DocumentWindow documentWindow2;
        private Telerik.WinControls.UI.Docking.DocumentWindow documentWindow3;
        private Telerik.WinControls.UI.RadGroupBox radgrpbxstartupMode;
        private System.Windows.Forms.TableLayoutPanel tableLayoutPanel12;
        private Telerik.WinControls.UI.RadRadioButton radradiobtnPWVMode;
        private Telerik.WinControls.UI.RadRadioButton radradiobtnPWAMode;
        private Telerik.WinControls.UI.Docking.DocumentWindow documentWindow4;
        private Telerik.WinControls.UI.RadGroupBox radGroupBox1;
        private System.Windows.Forms.TableLayoutPanel tableLayoutPanel8;
        private Telerik.WinControls.UI.RadRadioButton radRadioButton1;
        private Telerik.WinControls.UI.RadRadioButton radRadioButton4;
        private Telerik.WinControls.UI.RadRadioButton radRadioButton5;
        private Telerik.WinControls.UI.RadGroupBox radgrpbxBloodPressure;
        private System.Windows.Forms.TableLayoutPanel tableLayoutPanel1;
        private Telerik.WinControls.UI.RadGroupBox radgrpbxCaptureGuide;
        private System.Windows.Forms.TableLayoutPanel tableLayoutPanel13;
        private Telerik.WinControls.UI.RadCheckBox radchkAutoInflate;
        private Telerik.WinControls.UI.RadCheckBox radchkAutoCapture;
        private Telerik.WinControls.UI.RadGroupBox radgrpbxDefaultReport;
        private Telerik.WinControls.UI.RadDropDownList comboDefaultReport;
        private Telerik.WinControls.UI.RadGroupBox radgrpbxSimulationTypes;
        private Telerik.WinControls.UI.RadDropDownList comboSimulationFiles;
        private Telerik.WinControls.UI.RadGroupBox guiradgrpbxPWASimulationFiles;
        private Telerik.WinControls.UI.RadDropDownList radDropDownList3;
        private Telerik.WinControls.UI.RadGroupBox radgrpbxCaptureGuidePWA;
        private Telerik.WinControls.UI.RadCheckBox radchkAutoCapturePWA;
        private Telerik.WinControls.UI.RadCheckBox radchkGuidanceBars;
        private Telerik.WinControls.UI.RadGroupBox radgrpbxClinicalReport;
        private Telerik.WinControls.UI.RadCheckBox radchkBlindStudy;
        private Telerik.WinControls.UI.RadCheckBox radchkAumentationIndexHR75;
        private Telerik.WinControls.UI.RadCheckBox radchkAumentationIndex;
        private Telerik.WinControls.UI.RadGroupBox radgrpbxCaptureInput;
        private System.Windows.Forms.TableLayoutPanel tableLayoutPanel10;
        private Telerik.WinControls.UI.RadRadioButton radradiobtnTonometer;
        private Telerik.WinControls.UI.RadRadioButton radradiobtnPressureCuff;
        private Telerik.WinControls.UI.RadGroupBox radgrpbxCaptureTime;
        private System.Windows.Forms.TableLayoutPanel tableLayoutPanel9;
        private Telerik.WinControls.UI.RadRadioButton rad5SecondsPWA;
        private Telerik.WinControls.UI.RadRadioButton rad10SecondsPWA;
        private Telerik.WinControls.UI.RadRadioButton rad20SecondsPWA;
        private Telerik.WinControls.UI.Docking.DocumentWindow docWndBPSettings;
        private Telerik.WinControls.UI.RadGroupBox radgrpbxBloodPressures;
        private System.Windows.Forms.TableLayoutPanel tableLayoutPanel11;
        private Telerik.WinControls.UI.RadRadioButton radradiobtnMPandDP;
        private Telerik.WinControls.UI.RadRadioButton radradiobtnSPandDP;
        private Telerik.WinControls.UI.RadRadioButton radradiobtnSPandMP;
        private Telerik.WinControls.UI.RadGroupBox radgrpbxAutoPWA;
        private Telerik.WinControls.UI.RadCheckBox radradiochkDP;
        private Telerik.WinControls.UI.RadCheckBox radradiochkPP;
        private Telerik.WinControls.UI.RadCheckBox radradiochkSP;
        private Telerik.WinControls.UI.RadGroupBox radgrpbxNumberOfAssessments;
        private System.Windows.Forms.TableLayoutPanel tableLayoutPanel14;
        private Telerik.WinControls.UI.RadRadioButton radradiobtnAssessment5;
        private Telerik.WinControls.UI.RadRadioButton radradiobtnAssessment1;
        private Telerik.WinControls.UI.RadRadioButton radradiobtnAssessment2;
        private Telerik.WinControls.UI.RadRadioButton radradiobtnAssessment3;
        private Telerik.WinControls.UI.RadRadioButton radradiobtnAssessment4;
        private Telerik.WinControls.UI.RadGroupBox radgrpbxBPDevice;
        private Telerik.WinControls.UI.RadRadioButton radradiobtnOther;
        private Telerik.WinControls.UI.RadRadioButton radradiobtnSphygcomor;
        private Telerik.WinControls.UI.RadTextBox guiradtxtDPThreshold;
        private Telerik.WinControls.UI.RadTextBox guiradtxtPPThreshold;
        private Telerik.WinControls.UI.RadTextBox guiradtxtSPThreshold;
        private System.Windows.Forms.Panel guipnlBPAutoPWARangeDetails;
    }
}

