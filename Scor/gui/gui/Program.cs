/*
     Copyright (C) ATCOR MEDICAL PTY LTD, 2010
 
     Filename     :     Program.cs
        
     Author       :     Nitesh Chhedda
 
     Description  :     This class defines entry point for application.
*/
using System;
using System.Windows.Forms;
using System.Globalization;

namespace AtCor.Scor.Gui.Presentation
{
    public static class Program
    {
        /** This method fetches culture info string from current culture to show PDF files from respective folders
       * */
        public static string GetCurrentCulture()
        {
            CultureInfo currentCulture = CultureInfo.CurrentCulture;
            string cultureSetting = currentCulture.Name.Substring(0, 2);
            return cultureSetting;
        }

        /// <summary>
        /// The main entry point for the application.
        /// </summary>
        [STAThread]
        static void Main(string[] args)
        {
            DefaultWindow defWindow = null;             
            try
            { 
                Application.EnableVisualStyles();
                Application.SetCompatibleTextRenderingDefault(false);
                defWindow = new DefaultWindow();
                DataAccess.DalModule dm = DataAccess.DalModule.Instance;   
                Application.Run(defWindow);
            }
            catch (Exception ex)
            {
                GUIExceptionHandler.HandleException(ex, defWindow);
                System.Diagnostics.EventLog.WriteEntry("Scor error", ex.Message);
            }
        }
    }
}
