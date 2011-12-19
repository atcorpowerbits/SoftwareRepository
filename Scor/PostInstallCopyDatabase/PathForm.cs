/*
     Copyright (C) ATCOR MEDICAL PTY LTD, 2010
 
	 Filename     :      PathForm.cs
        
     Author       :		 Smarajit Mishra
 
     Description  :      Customize Pathform to do the after install process
*/
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.IO;

namespace PostInstallCopyDatabase
{
    public partial class PathForm : Form
    {
        private string _installPath;
        public string InstallPath
        {
            get { return _installPath; }
            set 
            {
                _installPath = value;
            }
        }

        public PathForm()
        {
            InitializeComponent();
            button1.Text = "Ok";
            button2.Text = "Browse...";
            button3.Text = "Cancel";
            this.Text = "Select backup file";
            lblNote.Text = " Press 'Ok' to copy or press 'Cancel' to cancel the database copy process";
            this.MaximizeBox = false;
            button1.Enabled = false;
            this.button2.Focus();
            this.BringToFront();
        }

        public PathForm(string InstallState)
        {
            InitializeComponent();
        }


        private void button1_Click(object sender, EventArgs e)
        {
            string[] splitArr = openFileDialog1.FileName.Split('\\');
            int numount = splitArr.Length;
            string copyPath = _installPath +"\\system\\data\\" + splitArr[numount - 1];
           
            File.Copy(textBox1.Text, copyPath,true);         
            Application.ExitThread();
        }


        private void button2_Click(object sender, EventArgs e)
        {            
            openFileDialog1.Title = string.Empty;
            openFileDialog1.DefaultExt = "xyz";
            openFileDialog1.Filter = "Database files (*.mdb)|*.mdb|Database files (*.xyz)|*.xyz";
            openFileDialog1.InitialDirectory = @"C:\";
            
            if (openFileDialog1.ShowDialog() == DialogResult.OK)
            {                
                textBox1.Text = openFileDialog1.FileName.ToString();

                if (textBox1.Text != String.Empty)
                {
                    button1.Enabled = true;
                }

            }           

        }

        private void button3_Click(object sender, EventArgs e)
        {       
            Close();
        }

        
                      
                
    }
}
