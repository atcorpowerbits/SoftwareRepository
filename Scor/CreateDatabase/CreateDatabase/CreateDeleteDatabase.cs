using System;

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
    }

    public class ApplicationConstants
    {
        public const string BatchFileName           =   "\\CreateDropDatabase.bat";
        public const string CreateScriptFileName    =   "CreateDatabase.sql";
        public const string DeleteScriptFileName    =   "DeleteDatabase.sql";
        public const string ServerNameFormat        =   "{0}\\ATCORSERVER";
    }
}