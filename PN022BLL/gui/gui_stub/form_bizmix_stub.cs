using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using Biz;

namespace gui
{
    public partial class form_bizmix_stub : Form
    {
        public form_bizmix_stub()
        {
            InitializeComponent();
        }

        private void buttonCreatePerson_Click(object sender, EventArgs e)
        {
            Person someone = new Person("Test", this.dateTimePicker1.Value);

            this.labelAge.Text = someone.Age.ToString();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            this.labelDirectAPI.Text = Person.fnBizCorNativeDLL().ToString();
        }

        private void buttonCallIndirect_Click(object sender, EventArgs e)
        {
            this.labelIndirectInt.Text = Person.CallCVarImplicit().ToString();
        }

        private void buttonIndirectAPI_Click(object sender, EventArgs e)
        {
            this.labelIndirectAPI.Text = Person.CallCFunctionImplicit().ToString();
        }
    }
}
