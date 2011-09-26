using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using Telerik.WinControls;
using Telerik.WinControls.Primitives;
using Telerik.WinControls.UI;
using AtCor.Scor.CrossCutting.Messaging;
using AtCor.Scor.CrossCutting.Configuration;
using AtCor.Scor.CrossCutting.Logging;
using AtCor.Scor.CrossCutting.DatabaseManager;

namespace AtCor.Scor.Gui.Presentation
{
    public partial class PWATestResult : Telerik.WinControls.UI.RadForm
    {
        private DefaultWindow objDefaultWindow;

        CrxMessagingManager oMsgMgr;
       
        public PWATestResult(DefaultWindow defWindow)
        {
            InitializeComponent();

            // set the default window
            objDefaultWindow = defWindow;

            // initialize servername string
            // serverNameString = GuiCommon.ServerNameString();
            // obj = (BizPWV)BizSession.Instance().measurement;

            // subscribe report tab click event
            DefaultWindow.OnPWATestResultTabClick += PWATestResult_Load;

            Presentation.Capture.OnPWATestResultTabClick += PWATestResult_Load;
        }

        /**This method is used to round the text boxes and the label controls on the Report screen.
         */
        private void SetShape(params Control[] labelControl)
        {
            RoundRectShape shape = new RoundRectShape();
            shape.BottomLeftRounded = true;
            shape.BottomRightRounded = true;
            shape.TopLeftRounded = true;
            shape.TopRightRounded = true;
            shape.Radius = 5;

            foreach (Control control in labelControl)
            {
                RadLabel label = control as RadLabel;

                if (label != null)
                {
                    label.RootElement.BackColor = Color.Transparent;
                    ((FillPrimitive)label.LabelElement.Children[0]).NumberOfColors = 1;

                    label.LabelElement.Shape = shape;
                }

                RadTextBox textBox = control as RadTextBox;

                if (textBox != null)
                {
                    textBox.TextBoxElement.BackColor = Color.FromArgb(172, 177, 204);
                    textBox.TextBoxElement.Fill.BackColor = Color.FromArgb(172, 177, 204);

                    textBox.TextBoxElement.Border.Shape = shape;
                    textBox.TextBoxElement.Fill.Shape = shape;
                }
            }
        }

        private void PWATestResult_Load(object sender, EventArgs e)
        {   
            // Set Shapes of Labels 
            SetShape(guiradlblSPValueText, guiradlblPPValueText, guiradlblAPValueText, guiradlblAIxValueText, guiradlblHRValueText, guiradlblDPValueText, guiradlblTestSPDisplay, guiradlblPWADPDisplay, guiradlblTestResultMapDisplay, guiradlblQualityControlValue);

            // Display Calculated data on screen
        }

        private void radbtnUpdate_Click(object sender, EventArgs e)
        {
            objDefaultWindow.radpgTabCollection.SelectedPage = objDefaultWindow.guiradgrpbxPwvDistanceMethod;
            objDefaultWindow.guiradgrpbxPwvDistanceMethod.Enabled = true;

            GuiCommon.SetupChildForm.Controls["guipnlPWAMeasurementDetails"].Visible = true;
            GuiCommon.SetupChildForm.Controls["guipnlPWAMeasurementDetails"].Controls["guipnlPWABPOtherDevice"].Visible = false;
            
            GuiCommon.SetupChildForm.Controls["guipnlPWAMeasurementDetails"].Controls["guiradbtnGetBp"].Visible = false;
            GuiCommon.SetupChildForm.Controls["guipnlPWAMeasurementDetails"].Controls["guiradbtnAutoPWACancel"].Visible = false;
            GuiCommon.SetupChildForm.Controls["guipnlPWAMeasurementDetails"].Controls["guiradlblBPProgressBar"].Visible = false;
            GuiCommon.SetupChildForm.Controls["guipnlPWAMeasurementDetails"].Controls["guiradbtnDisplayReport"].Visible = true;            
        }
    }
}
