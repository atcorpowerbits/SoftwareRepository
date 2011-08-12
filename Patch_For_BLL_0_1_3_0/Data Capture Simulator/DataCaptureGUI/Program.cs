using System;
using System.Collections.Generic;
using System.Linq;
using System.Windows.Forms;
using AtCor.Scor.CrossCutting;

namespace DataCaptureGUI
{
    static class Program
    {
        /// <summary>
        /// The main entry point for the application.
        /// </summary>
        [STAThread]
        static void Main()
        {
            try
            {
                Application.EnableVisualStyles();
                Application.SetCompatibleTextRenderingDefault(false);
                Application.Run(new Form1());
            }
            catch (ScorException scExObj)
            {
                MessageBox.Show("SCOR Exception: " + scExObj.ErrorCode + " : " + scExObj.ErrorMessageKey);
            }
            catch (Exception exObj)
            {
                MessageBox.Show("Exception: " + exObj.Message);
            }
        }
    }
}
