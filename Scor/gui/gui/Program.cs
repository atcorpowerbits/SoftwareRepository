/*
     Copyright (C) ATCOR MEDICAL PTY LTD, 2010
 
     Filename     :     Program.cs
        
     Author       :     Nitesh Chhedda
 
     Description  :     This class defines entry point for application.
*/
using System;
using System.Collections.Generic;
using System.Linq;
using System.Windows.Forms;
using System.Globalization;
using System.Xml;
using System.IO;
using AtCor.Scor.CrossCutting.Configuration;
using AtCor.Scor.CrossCutting;
using Microsoft.VisualBasic.ApplicationServices; // imported to show splash screen

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
            DefaultWindow defWindow = null; 
            
            try
            { 
                Application.EnableVisualStyles();
                Application.SetCompatibleTextRenderingDefault(false);
                defWindow = new DefaultWindow();
                Application.Run(defWindow);
            }
            catch (Exception ex)
            {
                GUIExceptionHandler.HandleException(ex, defWindow);
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

        /** This class is used to display splash screen.
         * */
        public class MyApp : WindowsFormsApplicationBase
        {
            protected override void OnCreateSplashScreen()
            {
                this.SplashScreen = new SplashScreen();
                this.SplashScreen.ShowInTaskbar = false;
            }

            protected override void OnCreateMainForm()
            {
                // Do your initialization here
                // ...
                // System.Threading.Thread.Sleep(3000);  // Test

                // Then create the main form, the splash screen will automatically close
                this.MainForm = new DefaultWindow();
                this.HideSplashScreen();
                this.MainForm.Activate();
            }
        }
    }
}
