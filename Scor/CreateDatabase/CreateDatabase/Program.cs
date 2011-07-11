using System;
using System.Collections.Generic;
using System.Linq;
using System.Windows.Forms;

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
            SetDatabaseProcessKey(args);

            if (DatabaseCreation.DatabaseProcessKey != DatabaseKey.NoDbProcess && 
                DatabaseCreation.DatabaseProcessKey != DatabaseKey.DbDelCancel)
            {
                Application.EnableVisualStyles();
                Application.SetCompatibleTextRenderingDefault(false);
                Application.Run(new Form1());
            }
            else
            {
                if (DatabaseCreation.DatabaseProcessKey == DatabaseKey.NoDbProcess)
                {
                    MessageBox.Show("Incorrect parameters passed, Aborting...", "Scor Message", MessageBoxButtons.OK, MessageBoxIcon.Error);
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
                result = MessageBox.Show("Are you sure you want to delete database?", "Confirm Database Delete", MessageBoxButtons.YesNo, MessageBoxIcon.Question);
                if (result == DialogResult.Yes)
                {
                    DatabaseCreation.DatabaseProcessKey = DatabaseKey.DbDeletion;
                }
                else
                {
                    DatabaseCreation.DatabaseProcessKey = DatabaseKey.DbDelCancel;
                }                
            }
        }
    }
}
