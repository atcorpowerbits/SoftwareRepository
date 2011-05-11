using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

using AtCor.Scor.DataAccess;
using AtCor.Scor.CrossCutting;

namespace DataCaptureGUI
{
    public partial class Form1 : Form
    {
        DalDataProvider dataProvider;
        public Form1()
        {
            try
            {
                dataProvider = new DalDataProvider();
                InitializeComponent();
            }
            catch (ScorException excep)
            {
                MessageBox.Show(excep.ErrorCode + " " + excep.ErrorMessageKey + " " + excep.ExceptionObject.Message);
            }
            catch (Exception excepObj)
            {
                MessageBox.Show(excepObj.Message);
            }
        }

        
       

        private void Start_Click(object sender, EventArgs e)
        {
            try
            {
                //dataProvider.StartSendingData();
                dataProvider.StartListeningToPCCommands();

                appstatus.Text = "In Listening mode";
            }
            catch (ScorException excep)
            {
                MessageBox.Show(excep.ErrorCode + " "+ excep.ErrorMessageKey + " "+ excep.ExceptionObject.Message );
            }
            catch (Exception excepObj)
            {
                MessageBox.Show(excepObj.Message);
            }

        }

        private void Stop_Click(object sender, EventArgs e)
        {
            try
            {
              //  dataProvider.StopSendingData();
                dataProvider.StopListeningToPCCommands();
                appstatus.Text = "Not listening for commands";
            }
            catch (ScorException excep)
            {
                MessageBox.Show(excep.ErrorCode + " " + excep.ErrorMessageKey + " " + excep.ExceptionObject.Message);
            }
            catch (Exception excepObj)
            {
                MessageBox.Show(excepObj.Message);
            }
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            appstatus.Text = "Not listening for commands";
        }

        
    }
}
