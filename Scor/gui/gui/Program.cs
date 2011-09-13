/*
     Copyright (C) ATCOR MEDICAL PTY LTD, 2010
 
     Filename     :     Program.cs
        
     Author       :     Nitesh Chhedda
 
     Description  :     This class defines entry point for application.
*/
using System;
using System.Configuration;
using System.Windows.Forms;
using System.Globalization;
using Telerik.WinControls;

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
                ThemeResolutionService.LoadPackageResource("gui.Theme.Atcor.tssp");
                ThemeResolutionService.ApplicationThemeName = ConfigurationManager.AppSettings[GuiConstants.AppConfigParams.ApplicationThemeName.ToString()];                
                Application.EnableVisualStyles();
                Application.SetCompatibleTextRenderingDefault(false);
                defWindow = new DefaultWindow();
                DataAccess.DalModule dm = DataAccess.DalModule.Instance;   
            
            Application.Run(defWindow);
            }
            catch (Exception ex)
            {
                GUIExceptionHandler.HandleException(ex, defWindow);               
            }
        }
    }
}
