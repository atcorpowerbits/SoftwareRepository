﻿//------------------------------------------------------------------------------
// <auto-generated>
//     This code was generated by a tool.
//     Runtime Version:2.0.50727.3623
//
//     Changes to this file may cause incorrect behavior and will be lost if
//     the code is regenerated.
// </auto-generated>
//------------------------------------------------------------------------------

namespace CreateDatabase {
    using System;
    
    
    /// <summary>
    ///   A strongly-typed resource class, for looking up localized strings, etc.
    /// </summary>
    // This class was auto-generated by the StronglyTypedResourceBuilder
    // class via a tool like ResGen or Visual Studio.
    // To add or remove a member, edit your .ResX file then rerun ResGen
    // with the /str option, or rebuild your VS project.
    [global::System.CodeDom.Compiler.GeneratedCodeAttribute("System.Resources.Tools.StronglyTypedResourceBuilder", "2.0.0.0")]
    [global::System.Diagnostics.DebuggerNonUserCodeAttribute()]
    [global::System.Runtime.CompilerServices.CompilerGeneratedAttribute()]
    internal class CustomMessage {
        
        private static global::System.Resources.ResourceManager resourceMan;
        
        private static global::System.Globalization.CultureInfo resourceCulture;
        
        [global::System.Diagnostics.CodeAnalysis.SuppressMessageAttribute("Microsoft.Performance", "CA1811:AvoidUncalledPrivateCode")]
        internal CustomMessage() {
        }
        
        /// <summary>
        ///   Returns the cached ResourceManager instance used by this class.
        /// </summary>
        [global::System.ComponentModel.EditorBrowsableAttribute(global::System.ComponentModel.EditorBrowsableState.Advanced)]
        internal static global::System.Resources.ResourceManager ResourceManager {
            get {
                if (object.ReferenceEquals(resourceMan, null)) {
                    global::System.Resources.ResourceManager temp = new global::System.Resources.ResourceManager("CreateDatabase.CustomMessage", typeof(CustomMessage).Assembly);
                    resourceMan = temp;
                }
                return resourceMan;
            }
        }
        
        /// <summary>
        ///   Overrides the current thread's CurrentUICulture property for all
        ///   resource lookups using this strongly typed resource class.
        /// </summary>
        [global::System.ComponentModel.EditorBrowsableAttribute(global::System.ComponentModel.EditorBrowsableState.Advanced)]
        internal static global::System.Globalization.CultureInfo Culture {
            get {
                return resourceCulture;
            }
            set {
                resourceCulture = value;
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to Available Databases.
        /// </summary>
        internal static string AVAILABLE_DATABASES_TEXT {
            get {
                return ResourceManager.GetString("AVAILABLE_DATABASES_TEXT", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to Cancel.
        /// </summary>
        internal static string BTN_CANCEL {
            get {
                return ResourceManager.GetString("BTN_CANCEL", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to Ok.
        /// </summary>
        internal static string BTN_OK {
            get {
                return ResourceManager.GetString("BTN_OK", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to Confirm Database Delete.
        /// </summary>
        internal static string CONFIRM_DELETE_MSG_TEXT {
            get {
                return ResourceManager.GetString("CONFIRM_DELETE_MSG_TEXT", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to Error occured while executing database scripts, please refer the Database.log file for details..
        /// </summary>
        internal static string DATABASE_ERROR_MSG {
            get {
                return ResourceManager.GetString("DATABASE_ERROR_MSG", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to Are you sure you want to delete database?.
        /// </summary>
        internal static string DELETE_DATABASE_MSG_TEXT {
            get {
                return ResourceManager.GetString("DELETE_DATABASE_MSG_TEXT", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to Incorrect parameters passed, Aborting....
        /// </summary>
        internal static string INCORRECT_PARAMETER_MSG_TEXT {
            get {
                return ResourceManager.GetString("INCORRECT_PARAMETER_MSG_TEXT", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to Select server to create/delete database:.
        /// </summary>
        internal static string SELECT_SERVER_TEXT {
            get {
                return ResourceManager.GetString("SELECT_SERVER_TEXT", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to ServerName.
        /// </summary>
        internal static string SERVER_NAME_TEXT {
            get {
                return ResourceManager.GetString("SERVER_NAME_TEXT", resourceCulture);
            }
        }
    }
}