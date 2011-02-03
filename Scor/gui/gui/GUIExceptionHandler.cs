using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using AtCor.Scor.CrossCutting;
using AtCor.Scor.CrossCutting.Logging;
using AtCor.Scor.CrossCutting.Messaging;
using Telerik.WinControls.UI;
using Telerik.WinControls;
using Telerik.WinControls.Primitives;
using AtCor.Scor.DataAccess;

namespace AtCor.Scor.Gui.Presentation
{
    public delegate void ExceptionHandler(Exception ex, object currentWindow);

    public class GUIExceptionHandler
    {
        /** Enum for defining exception type
          * */
        public enum Error_Type
        {
            Information,
            Warning,
            Exception
        }

        private static CrxMessagingManager oMsgMgr = CrxMessagingManager.Instance;
        private static CrxLogger oLogObject = CrxLogger.Instance;

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

                // Prepare a message for display.
                string eMsg = crEx.ErrorCode.ToString() + " : " + oMsgMgr.GetMessage(crEx.ErrorMessageKey);
               
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
                }
                else if (crEx.ErrorType == ErrorSeverity.Information)
                {
                    // TODO: Warning and Info messages displyed should be cleared from
                    //      status bar after 5/10 Seconds

                    // here display "eMsg" in status bar along with RadMessageIcon.Info icon at the
                    // begining of the message
                   
                    // log error message
                    oLogObject.Write("Info: " + eMsg);
                }
            }            
        } // End HandleCRXException

        /** This method handles general exception thrown by application which is not catched by DAL & CRX
         * */
        private static void HandleGeneralException(Exception ex, object currentWindow)
        {            
            // handle general GUI exception
            RadMessageBox.Show((IWin32Window)currentWindow, ex.Message, oMsgMgr.GetMessage("SYSTEM_ERROR"), MessageBoxButtons.OK, RadMessageIcon.Error);

            // log exception message alongwith stack trace
            oLogObject.Write(ex.Message + "\r\n\r\n" + ex.Source + "\r\n\r\n" + ex.StackTrace);
        } // End HandleGeneralException
    }
}
