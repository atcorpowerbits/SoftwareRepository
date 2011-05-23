using System;
using System.Collections;
using System.Collections.Generic;
using System.ComponentModel;
using System.Configuration.Install;
using System.Linq;
using System.IO;
using System.Windows.Forms;


namespace PostInstallCopyDatabase
{
    [RunInstaller(true)]
    public partial class Installer1 : Installer
    {
        public Installer1()
        {
            InitializeComponent();
        }

        [System.Security.Permissions.SecurityPermission(System.Security.Permissions.SecurityAction.Demand)]
        public override void Install(IDictionary stateSaver)
        {
            base.Install(stateSaver);
            stateSaver.Add("TargetDir", Context.Parameters["DP_TargetDir"].ToString()); 

        }

        [System.Security.Permissions.SecurityPermission(System.Security.Permissions.SecurityAction.Demand)]
        public override void Commit(IDictionary savedState)
        {
            base.Commit(savedState);         

            //get install directory
            string installDir = "";
            foreach (string k in savedState.Keys)
            {
                if (k.Equals("TargetDir"))
                {
                    installDir = savedState[k].ToString();
                }
            }

            PathForm pf = new PathForm();
            pf.InstallPath = installDir;
            pf.ShowDialog();
            pf.ShowInTaskbar = true;

            //calling the 
            System.Diagnostics.Process.Start("http://get.adobe.com/reader/");

            #region Running Batch File
            ////get install directory
            //string installDir = "";
            //foreach (string k in savedState.Keys)
            //{
            //    if (k.Equals("TargetDir"))
            //    {
            //        installDir = savedState[k].ToString();
            //    }
            //}

            //StreamWriter sw = new StreamWriter("C:\\NTemp\\Commit.txt", false);



            //foreach (string k in savedState.Keys)
            //{
            //    sw.WriteLine("BATCH [" + k + "]= " + savedState[k].ToString());
            //}



            //sw.Flush();
            //sw.Close();


            
            //System.Diagnostics.Process.Start(@"C:\\Program Files\\Default Company Name\\DummySetup\\Runapp.bat");
            //System.Diagnostics.Process.Start(installDir + @"\Runapp.bat");
            

            #endregion

        }

        [System.Security.Permissions.SecurityPermission(System.Security.Permissions.SecurityAction.Demand)]
        public override void Rollback(IDictionary savedState)
        {
            base.Rollback(savedState);
        }

        [System.Security.Permissions.SecurityPermission(System.Security.Permissions.SecurityAction.Demand)]
        public override void Uninstall(IDictionary savedState)
        {
            base.Uninstall(savedState);
        }


    }
}
