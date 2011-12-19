/*
     Copyright (C) ATCOR MEDICAL PTY LTD, 2010
 
	 Filename     :      CustomInstaller.cs
        
     Author       :		 Smarajit Mishra
 
     Description  :      Creating Installer class to handle the installer
*/

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
    public partial class CustomInstaller : Installer
    {
        public CustomInstaller()
        {
            InitializeComponent();
        }

        [System.Security.Permissions.SecurityPermission(System.Security.Permissions.SecurityAction.Demand)]
        public override void Install(IDictionary stateSaver)
        {
            base.Install(stateSaver);
            stateSaver.Add("TargetDir", Context.Parameters["DP_TargetDir"].ToString());
            stateSaver.Add("SourceDir", Context.Parameters["InstallerPath"].ToString());
        }

        [System.Security.Permissions.SecurityPermission(System.Security.Permissions.SecurityAction.Demand)]
        public override void Commit(IDictionary savedState)
        {
            base.Commit(savedState);

            string stagingLocation = string.Empty;

            //get install directory and source directory
            string installDir = string.Empty;
            foreach (string k in savedState.Keys)
            {
                if (k.Equals("TargetDir"))
                {
                    installDir = savedState[k].ToString();
                }
                if (k.Equals("SourceDir"))
                {
                    stagingLocation = savedState[k].ToString();
                }
            }

            string DirName = System.IO.Directory.GetParent(stagingLocation).Name;
            int indexNm = stagingLocation.IndexOf(DirName);
            stagingLocation = stagingLocation.Substring(0, indexNm);
            // MessageBox.Show(stagingLocation);

            // This process do the copy process (scor.config) from source to application installed location
            // If not found in the specified location show message
            if (File.Exists(stagingLocation + "system\\config\\" + "scor.config"))
            {
                string flPath = string.Empty;
                string cyPath = string.Empty;
                flPath = stagingLocation + "system\\config\\" + "scor.config";
                cyPath = installDir + "system\\config\\" + "scor.config";
                File.Copy(flPath, cyPath, true);
            }
            else
            {
                MessageBox.Show("System Configuration file cannot be accessed. Please contact AtCor support  http://atcormedical.com/request_support.html");
            }

            string strVer8 = "C:\\Program Files\\AtCor\\SphygmoCor CvMS\\data\\";
            string strVer9 = "C:\\AtCor\\SphygmoCor CvMS V9\\data\\";
            string fileNameMdb = "scor.mdb";
            string fileNameXyz = "scor.xyz";

            // This will do the data file (scor.mdb/scor.xyz) copy process
            // If not found in the specified location show browse pathform 
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
