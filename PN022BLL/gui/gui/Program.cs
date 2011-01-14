using System;
using System.Collections.Generic;
using System.Linq;
using System.Windows.Forms;
using System.Globalization;
using System.Xml;
using System.IO;
using AtCor.Scor.CrossCutting.Configuration;  

namespace AtCor.Scor.Gui.Presentation
{
    public static class Program
    {
        /// <summary>
        /// The main entry point for the application.
        /// </summary>
        [STAThread]
        static void Main()
        {
            try
            {                
                System.Diagnostics.EventLog.WriteEntry("Scor", "Entry Point");
                Application.EnableVisualStyles();
                Application.SetCompatibleTextRenderingDefault(false);
                Application.Run(new DefaultWindow());
            }
            catch (Exception ex)
            {
                System.Diagnostics.EventLog.WriteEntry("Scor error", ex.Message);
            }
        }
        
        public static string GetCurrentCulture()
        {
            CultureInfo currentCulture = CultureInfo.CurrentCulture;            
            string cultureSetting = currentCulture.Name.Substring(0, 2);
            return cultureSetting;
        }
    }
}
