using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using Telerik.WinControls;

namespace AtCor.Scor.Gui.Presentation
{
    public partial class QuickReport : Telerik.WinControls.UI.RadForm
    {
        private DefaultWindow objDefaultWindow;
        public QuickReport(DefaultWindow defWindow)
        {
            InitializeComponent();
            // set the default window
            objDefaultWindow = defWindow;

        }

      
    }
}
