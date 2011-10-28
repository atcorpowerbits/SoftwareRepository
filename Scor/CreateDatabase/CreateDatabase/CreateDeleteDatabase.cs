using System;
using System.Globalization;
using System.Resources;
using System.IO;
using System.Windows;
using System.Windows.Forms;

namespace CreateDatabase
{
    //DatabaseKey Enum to differentate the process
    public enum DatabaseKey
    {
        NoDbProcess,
        DbCreation,
        DbDeletion,
        DbDelCancel
    }

    public static class DatabaseCreation
    {
        public static DatabaseKey DatabaseProcessKey { get; set; }
        public static CultureInfo gCI { get; set; }
    }

    public class ApplicationConstants
    {
        public const string BatchFileName           =   "\\CreateDropDatabase.bat";
        public const string CreateScriptFileName    =   "CreateDatabase.sql";
        public const string DeleteScriptFileName    =   "DeleteDatabase.sql";
        public const string ServerNameFormat        =   "{0}\\ATCORSERVER";
    }

    public class ApplicationMessageManager
    {
        private ResourceManager errRsrcMsg;

        private static ApplicationMessageManager _instance;

        private ApplicationMessageManager()
        {
            errRsrcMsg = new ResourceManager("CreateDatabase.CustomMessage", System.Reflection.Assembly.GetExecutingAssembly());
        }

        public static ApplicationMessageManager Instance
        {
            get
            {
                if (_instance == null)
                {
                    _instance = new ApplicationMessageManager();
                }
                return _instance;
            }

        }

        public string GetMessage(string strCode)
        {
            string strMessage = string.Empty;

            try
            {
                //Get the message string through resource manager object
                strMessage = errRsrcMsg.GetString(strCode, DatabaseCreation.gCI);
            }
            catch (Exception exObj)
            {
                MessageBox.Show(exObj.Message, "Scor", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }

            return strMessage;
        } 

    }


}