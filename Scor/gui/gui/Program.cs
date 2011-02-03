using System;
using System.Collections.Generic;
using System.Linq;
using System.Windows.Forms;
using System.Globalization;
using System.Xml;
using System.IO;
using AtCor.Scor.CrossCutting.Configuration;
using AtCor.Scor.CrossCutting;

namespace AtCor.Scor.Gui.Presentation
{
    public static class Program
    {
        /// <summary>
        /// The main entry point for the application.
        /// </summary>
        [STAThread]
        static void Main(string[] args)
        {
            try
            { 
                Application.EnableVisualStyles();
                Application.SetCompatibleTextRenderingDefault(false);
                Application.Run(new DefaultWindow());
            }
            catch (Exception ex)
            {
                System.Diagnostics.EventLog.WriteEntry("Scor error", ex.Message);
            }
        }        

        /** This method fetches culture info string from current culture to show PDF files from respective folders
         * */
        public static string GetCurrentCulture()
        {
            CultureInfo currentCulture = CultureInfo.CurrentCulture;            
            string cultureSetting = currentCulture.Name.Substring(0, 2);
            return cultureSetting;
        }       
    }
}
