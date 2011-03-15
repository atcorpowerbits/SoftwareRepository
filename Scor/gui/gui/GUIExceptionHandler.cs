/*
     Copyright (C) ATCOR MEDICAL PTY LTD, 2010
 
     Filename     :     GUIExceptionHandler
        
     Author       :     Vibhuti Damania
 
     Description  :     Functionality implemented for common exception handling mechanism 
*/
using System;
using System.Text;
using System.Windows.Forms;
using AtCor.Scor.CrossCutting;
using AtCor.Scor.CrossCutting.Logging;
using AtCor.Scor.CrossCutting.Messaging;
using Telerik.WinControls;
using System.Configuration;
using System.IO;
using System.Drawing;

namespace AtCor.Scor.Gui.Presentation
{
    public delegate void ExceptionHandler(Exception ex, object currentWindow);

    public class GUIExceptionHandler
    {
        /** Enum for defining exception type
          * */
        public enum ErrorType
        {
            Information,
            Warning,
            Exception
        }

        private static readonly CrxMessagingManager oMsgMgr = CrxMessagingManager.Instance;
        private static readonly CrxLogger oLogObject = CrxLogger.Instance;
        private static StringBuilder eMesg = new StringBuilder();

        /** This method handles all types of exception & throws appropriate messages
         * */
        public static void HandleException(Exception ex, object currentWindow)
        {
            if (ex.GetType() == typeof(ScorException))
            {
                HandleScorException((ScorException)ex, currentWindow);
            }
            else
            {
                HandleGeneralException(ex, currentWindow);
            }
        } // End HandleException

        /** This method handles scor exception returned from both DAL & CRX with error codes & error types.
         * It displays exception message with error code for handled & unhandled exception 
         * It logs error code, error message & stack trace for unhandled exception
         * */
        private static void HandleScorException(ScorException crEx, object currentWindow)
        {
            if (crEx.ErrorCode == -1)
            {
                // Handle unknown exception

                // if exception is thrown, this will be unknown error, hence
                // show message box to user, with title Scor Application error
                // and Exception.Message as body text of mesg box.
                // also while logging an error of this type not only log the error message also
                // log the call stack and error source info in log file

                // crx unhandled exception
                RadMessageBox.Show((IWin32Window)currentWindow, crEx.ExceptionObject.Message, oMsgMgr.GetMessage("SYSTEM_ERROR"), MessageBoxButtons.OK, RadMessageIcon.Error);

                // log exception message alongwith stack trace and error source
                oLogObject.Write(crEx.ExceptionObject.Message + "\r\n\r\n" + crEx.ExceptionObject.Source + "\r\n\r\n" + crEx.ExceptionObject.StackTrace);
            }
            else
            {
                // since we are here, we are handling application generated exceptions

                // weather to show a message box or to show info and warning messages will depend 
                // om the error / exception type, if error type is Exception then show
                // msg box, other wise show message in status bar, with info or warninig 
                // icon in status bar, log all messages 
                // also error message has to be contacttenated with error code like "101: File Not Found",
                // cannot use crEx.ErrorString directly, used msg manager getmessage to get localized error
                // message

                // smarajit
                string eMsg = ConstructErrorMessage(crEx);

                if (crEx.ErrorType == ErrorSeverity.Exception)
                {
                    // crx handled exception
                    RadMessageBox.Show((IWin32Window)currentWindow, eMsg, oMsgMgr.GetMessage("SYSTEM_ERROR"), MessageBoxButtons.OK, RadMessageIcon.Error);

                    // log error message
                    oLogObject.Write("Error: " + eMsg);
                }
                else if (crEx.ErrorType == ErrorSeverity.Warning)
                {
                    // TODO: Warning and Info messages displyed should be cleared from
                    //      status bar after 5/10 Seconds

                    // here display "eMsg" in status bar along with RadMessageIcon.Exclamation icon at the
                    // begining of the message

                    // log error message
                    oLogObject.Write("Warning: " + eMsg);

                    // ###########################################
                    SettingsProperties.defaultWindowForm.radlblMessage.Text = eMsg;
                    SettingsProperties.defaultWindowForm.guipictureboxError.Image = new Bitmap(Path.GetFullPath(ConfigurationManager.AppSettings["WarningImage"].ToString()));

                    // ###########################################

                    // Using timer4 to disable image and text shown in status bar
                    SettingsProperties.defaultWindowForm.guialertmsgTimer.Enabled = true;
                    SettingsProperties.defaultWindowForm.guialertmsgTimer.Tick += new EventHandler(guialertmsgTimer_Tick);
                }
                else if (crEx.ErrorType == ErrorSeverity.Information)
                {
                    // TODO: Warning and Info messages displyed should be cleared from
                    //      status bar after 5/10 Seconds

                    // here display "eMsg" in status bar along with RadMessageIcon.Info icon at the
                    // begining of the message

                    // log error message
                    oLogObject.Write("Info: " + eMsg);

                    // ###########################################
                    SettingsProperties.defaultWindowForm.radlblMessage.Text = eMsg;
                    SettingsProperties.defaultWindowForm.guipictureboxError.Image = new Bitmap(Path.GetFullPath(ConfigurationManager.AppSettings["InfoImage"].ToString()));

                    // Using timer4 to disable image and text shown in status bar
                    SettingsProperties.defaultWindowForm.guialertmsgTimer.Enabled = true;
                    SettingsProperties.defaultWindowForm.guialertmsgTimer.Tick += new EventHandler(guialertmsgTimer_Tick);
                }
            }
        } // End HandleCRXException

        /** This method constructs error message depending upon the errormessagekey, general exception object
         * and array of errorstring which is used to replace placeholders in error message
         * */
        private static string ConstructErrorMessage(ScorException crEx)
        {
            string eMsg = string.Empty;
            eMesg = new StringBuilder(string.Empty);
            
            // check for error message key to construct exception message format
            if (crEx.ErrorMessageKey != null)
            {
                // concatenate error code & get error message as per errormessagekey                   
                eMesg.AppendLine(string.Format("{0} : {1}", crEx.ErrorCode.ToString(), oMsgMgr.GetMessage(crEx.ErrorMessageKey)));

                // check if exception object is null this will have value when general exception is thrown
                // append it to the main message
                if (crEx.ExceptionObject != null)
                {
                    eMesg.AppendLine(crEx.ExceptionObject.Message + ", ");
                }

                // crEx.ErrorStringArr contains placeholder values for paramter strings
                // replace the placeholders in main message with the values in crEx.ErrorStringArr 
                if (crEx.ErrorStringArr.Length > 0)
                {
                    for (int i = 0; i < crEx.ErrorStringArr.Length; i++)
                    {
                        eMesg.Replace("{" + i + "}", crEx.ErrorStringArr[i].ToString());
                    }
                }

                eMsg = eMesg.ToString();
            }
            else if (crEx.ExceptionObject != null)
            {
                // Prepare a message for display. this will be for general exception
                string temp = crEx.ErrorCode.ToString() + " : " + crEx.ExceptionObject.Message;
                eMesg.Append(temp);

                // crEx.ErrorStringArr contains placeholder values for paramter strings
                // formulate the error messages based on array values
                eMsg = GetErrorString(crEx.ErrorStringArr);
            }
            else
            {
                //// Prepare a message for display if crEx.ErrorStringArr has value
                eMsg = GetErrorString(crEx.ErrorStringArr);
            }

            return eMsg;
        }

        /** This method takes error string array as parameter and forumlates an error message from the array
         * */
        private static string GetErrorString(string[] errString)
        {
            if (errString.Length > 0)
            {
                foreach (string t in errString)
                {
                    eMesg.Append(oMsgMgr.GetMessage(t));
                }
            }

            return eMesg.ToString();
        }

        /** This method handles general exception thrown by application which is not catched by DAL & CRX
         * */
        private static void HandleGeneralException(Exception ex, object currentWindow)
        {
            // handle general GUI exception
            RadMessageBox.Show((IWin32Window)currentWindow, ex.Message, oMsgMgr.GetMessage("SYSTEM_ERROR"), MessageBoxButtons.OK, RadMessageIcon.Error);

            // log exception message alongwith stack trace
            oLogObject.Write(ex.Message + "\r\n\r\n" + ex.Source + "\r\n\r\n" + ex.StackTrace);
        } // End HandleGeneralException

        /** This event gets called when alert message timer on default window ticks         
         * */
        private static void guialertmsgTimer_Tick(object sender, EventArgs e)
        {
            SettingsProperties.defaultWindowForm.guialertmsgTimer.Enabled = false;
            SettingsProperties.defaultWindowForm.guipictureboxError.Image = null;
            SettingsProperties.defaultWindowForm.radlblMessage.Text = string.Empty;
        }
    }
}
