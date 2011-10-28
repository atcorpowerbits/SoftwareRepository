using System;
using System.Collections.Generic;
using System.Linq;
using System.Windows.Forms;
using System.Globalization;
using System.Resources;
using System.Reflection;

namespace CreateDatabase
{
    static class Program
    {
        /// <summary>
        /// The main entry point for the application.
        /// </summary>
        [STAThread]
        static void Main(string[] args)
        {
            SetCommCultureInfo(args);
            SetDatabaseProcessKey(args);            

            if (DatabaseCreation.DatabaseProcessKey != DatabaseKey.NoDbProcess && 
                DatabaseCreation.DatabaseProcessKey != DatabaseKey.DbDelCancel)
            {
                Application.EnableVisualStyles();
                Application.SetCompatibleTextRenderingDefault(false);
                Application.Run(new SelectionForm());
            }
            else
            {
                if (DatabaseCreation.DatabaseProcessKey == DatabaseKey.NoDbProcess)
                {
                    //MessageBox.Show("Incorrect parameters passed, Aborting...", "Scor Message", MessageBoxButtons.OK, MessageBoxIcon.Error);
                    MessageBox.Show(ApplicationMessageManager.Instance.GetMessage("INCORRECT_PARAMETER_MSG_TEXT"), "Scor", MessageBoxButtons.OK, MessageBoxIcon.Error);
                }
                Application.ExitThread();
                Application.Exit();
            }
         
        }

        static void SetDatabaseProcessKey(string[] args)
        {
            string temp = string.Empty;        

            // Initialize to default database process 
            DatabaseCreation.DatabaseProcessKey = DatabaseKey.NoDbProcess;

            if (args.Length != 0)
            {
                temp = args[0];
            }

            // if no arguments are passed, create database is assumed
            if (args.Length == 0 || args[0] == null || args[0] == string.Empty)
            {
                DatabaseCreation.DatabaseProcessKey = DatabaseKey.DbCreation;
            }
            else if (string.Equals(temp, "-C") || string.Equals(temp, "-c"))
            {
                // explicitely create parameter passed. create database.
                DatabaseCreation.DatabaseProcessKey = DatabaseKey.DbCreation;
            }
            else if (string.Equals(temp, "-D") || string.Equals(temp, "-d"))
            {
                // explicitely delete parameter passed, delete / drop database
                DialogResult result;

                // following message needs to be localized based on the installer language
                // TODO: If required add a resource file for this project.
                //result = MessageBox.Show("Are you sure you want to delete database?", "Confirm Database Delete", MessageBoxButtons.YesNo, MessageBoxIcon.Question);
                result = MessageBox.Show(ApplicationMessageManager.Instance.GetMessage("DELETE_DATABASE_MSG_TEXT"), ApplicationMessageManager.Instance.GetMessage("CONFIRM_DELETE_MSG_TEXT"), MessageBoxButtons.YesNo, MessageBoxIcon.Question);
                if (result == DialogResult.Yes)
                {
                    DatabaseCreation.DatabaseProcessKey = DatabaseKey.DbDeletion;
                }
                else
                {
                    DatabaseCreation.DatabaseProcessKey = DatabaseKey.DbDelCancel;
                }
            }
            //else
            //{
            //    DatabaseCreation.DatabaseProcessKey = DatabaseKey.DbCreation;
            //}
        }
        static void SetCommCultureInfo(string[] args)
        {
            string temp = string.Empty;           

            try
            {
                if (args.Length != 0)
                {
                    temp = args[1];
                }
                // if no arguments are passed, create database is assumed
                if (args.Length == 0 || (args[1] == null && args[1] == string.Empty 
                    && args[1] == null && args[1] == string.Empty))
                {
                    DatabaseCreation.gCI = new CultureInfo("en-US");
                }
                else if (args[1].Length == 5)
                {
                    DatabaseCreation.gCI = new CultureInfo(args[1].ToString().Trim());
                }
                else if (args[0].Length == 5)
                {
                    DatabaseCreation.gCI = new CultureInfo(args[0].ToString().Trim());
                }
                else
                {
                    DatabaseCreation.gCI = new CultureInfo("en-US");
                }

            }
            catch (Exception)
            {
                DatabaseCreation.gCI = new CultureInfo("en-US");
            }
        }
    }
}
