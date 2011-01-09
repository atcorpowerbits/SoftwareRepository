using System;
using System.Collections.Generic;
using System.Linq;
using System.Windows.Forms;
using System.Globalization;

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
            Application.EnableVisualStyles();
            Application.SetCompatibleTextRenderingDefault(false);
            Application.Run(new DefaultWindow());
        }


        public static string GetCurrentCulture()
        {

            CultureInfo currentCulture = CultureInfo.CurrentCulture;

            string cultureSetting = currentCulture.Name.Substring(0, 2);

            return cultureSetting;

        }

    }

}
