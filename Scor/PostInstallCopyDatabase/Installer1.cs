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

            string strVer8 = "C:\\Program Files\\AtCor\\SphygmoCor CvMS\\data\\";
            string strVer9 = "C:\\AtCor\\SphygmoCor CvMS V9\\data\\";
            string fileNameMdb = "scor.mdb";
            string fileNameXyz = "scor.xyz";

            if (File.Exists(strVer8 + fileNameXyz))
            {
                string filePath = strVer8 + fileNameXyz;
                string copyPath = installDir + "\\system\\data\\" + fileNameXyz;

                File.Copy(filePath, copyPath, true);
            }
            else if (File.Exists(strVer8 + fileNameMdb))
            {
                string filePath = strVer8 + fileNameMdb;
                string copyPath = installDir + "\\system\\data\\" + fileNameMdb;

                File.Copy(filePath, copyPath, true);
            }
            else if (File.Exists(strVer9 + fileNameXyz))
            {
                string filePath = strVer9 + fileNameXyz;
                string copyPath = installDir + "\\system\\data\\" + fileNameXyz;

                File.Copy(filePath, copyPath, true);
            }
            else if (File.Exists(strVer9 + fileNameMdb))
            {
                string filePath = strVer9 + fileNameMdb;
                string copyPath = installDir + "\\system\\data\\" + fileNameMdb;

                File.Copy(filePath, copyPath, true);
            }
            else
            {
                if (!(File.Exists(installDir + "\\system\\data\\" + fileNameMdb) || (File.Exists(installDir + "\\system\\data\\" + fileNameXyz))))
                {
                    PathForm pf = new PathForm();
                    pf.InstallPath = installDir;
                    pf.ShowDialog();
                    pf.ShowInTaskbar = true;
                }
            }         

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
