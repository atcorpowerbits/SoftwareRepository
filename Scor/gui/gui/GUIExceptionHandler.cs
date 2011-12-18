/*
     Copyright (C) ATCOR MEDICAL PTY LTD, 2010
 
     Filename     :     GUIExceptionHandler
        
     Author       :     Vibhuti Damania
 
     Description  :     Functionality implemented for common exception handling mechanism 
*/
using System;
using System.Collections.Generic;
using System.Text;
using System.Windows.Forms;
using AtCor.Scor.CrossCutting;
using AtCor.Scor.CrossCutting.Logging;
using AtCor.Scor.CrossCutting.Messaging;
using Telerik.WinControls;
using System.Configuration;
using System.IO;
using System.Drawing;
using AtCor.Scor.BusinessLogic;
using System.Diagnostics;
using System.Threading;

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

        private static readonly CrxMessagingManager OMsgMgr = CrxMessagingManager.Instance;
        private static readonly CrxLogger OLogObject = CrxLogger.Instance;
        private static StringBuilder eMesg = new StringBuilder();
        private static bool isScorSystemParameterCorrupted = false;

        public static void ShowStatusMessage(object sender, CrxShowStatusEventArgs args)
        {
            if (!isScorSystemParameterCorrupted)
            {
                Telerik.WinControls.UI.RadForm obj = new Telerik.WinControls.UI.RadForm();
                HandleException(args.ObjScorException, obj);
            }          
        }  

        public static void RegisterUnHandledExceptionHandler()
        {
            AppDomain currentDomain = AppDomain.CurrentDomain;
            currentDomain.UnhandledException += currentDomain_UnhandledException; 
        }

        /** This event gets called when alert message timer on default window ticks         
      * */
        public static void guialertmsgTimer_Tick(object sender, EventArgs e)
        {
            DisableTimerAndClearMessageFromStatusBar();
        }

        public static void DisableTimerAndClearMessageFromStatusBar()
        {
            GuiCommon.DefaultWindowForm.guipictureboxError.Image = null;
            GuiCommon.DefaultWindowForm.radlblMessage.Text = string.Empty;
        }

        /** This method handles all types of exception & throws appropriate messages
         * */
        public static void HandleException(Exception ex, object currentWindow)
        {
            System.Diagnostics.Debug.Write("Error Message:" + ex.Message);
            System.Diagnostics.Debug.Write("Stack Trace:" + ex.StackTrace); 
            Type typeOfObject = currentWindow.GetType();
            if (!(currentWindow.GetType() == typeof(Telerik.WinControls.UI.RadForm)))
            {
                Telerik.WinControls.UI.RadForm obj = new Telerik.WinControls.UI.RadForm();
                if (ex.GetType() == typeof(ScorException))
                {
                    HandleScorException((ScorException)ex, obj);
                }
                else
                {
                    HandleGeneralException(ex, obj);
                }
            }
            else
            {
                if (ex.GetType() == typeof(ScorException))
                {
                    HandleScorException((ScorException)ex, currentWindow);
                }
                else
                {
                    HandleGeneralException(ex, currentWindow);
                }
            }           
        }

        static void currentDomain_UnhandledException(object sender, UnhandledExceptionEventArgs e)
        {            
            Exception ex = (Exception)e.ExceptionObject;
            RadMessageBox.Show(ex.Message + Environment.NewLine + ex.StackTrace, OMsgMgr.GetMessage(CrxStructCommonResourceMsg.SystemError), MessageBoxButtons.OK, RadMessageIcon.Error);
        } 

        /** This method handles scor exception returned from both DAL & CRX with error codes & error types.
         * It displays exception message with error code for handled & unhandled exception 
         * It logs error code, error message & stack trace for unhandled exception
         * */
        private static void HandleScorException(ScorException crEx, object currentWindow)
        {
            string eMsg = string.Empty;
            if (crEx.ErrorCode == (int)CustomErrorCode.SystemErrorCode)
            {
                // Handle unknown exception

                // if exception is thrown, this will be unknown error, hence
                // show message box to user, with title Scor Application error
                // and Exception.Message as body text of mesg box.
                // also while logging an error of this type not only log the error message also
                // log the call stack and error source info in log file

                // crx unhandled exception
                RadMessageBox.Show((IWin32Window)currentWindow, crEx.ExceptionObject.Message, OMsgMgr.GetMessage(CrxStructCommonResourceMsg.SystemError), MessageBoxButtons.OK, RadMessageIcon.Error);
                // RadMessageBox.Show(crEx.ExceptionObject.Message, OMsgMgr.GetMessage(CrxStructCommonResourceMsg.SystemError), MessageBoxButtons.OK, RadMessageIcon.Error);

                // log exception message alongwith stack trace and error source
                OLogObject.Write(crEx.ExceptionObject.Message + Environment.NewLine + crEx.ExceptionObject.Source + Environment.NewLine + crEx.ExceptionObject.StackTrace);
            }
            else if (crEx.ErrorCode == (int)CustomErrorCode.SpecialExceptionCode)
            {
                eMesg = new StringBuilder(string.Empty);

                // Prepare a message for display. this will be for general exception
                string temp = string.Format("{0}{1}", crEx.ExceptionObject.Message, Environment.NewLine);
                eMesg.Append(temp);                

                // crEx.ErrorStringArr contains placeholder values for paramter strings
                // formulate the error messages based on array values
                eMsg = GetErrorString(crEx.ErrorStringArr);

                RadMessageBox.Show((IWin32Window)currentWindow, eMsg, OMsgMgr.GetMessage(CrxStructCommonResourceMsg.SystemError), MessageBoxButtons.OK, RadMessageIcon.Error);
                // RadMessageBox.Show(eMsg, OMsgMgr.GetMessage(CrxStructCommonResourceMsg.SystemError), MessageBoxButtons.OK, RadMessageIcon.Error);

                OLogObject.Write(OMsgMgr.GetMessage(CrxStructCommonResourceMsg.GuiErrorTxt) + eMsg);
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
                eMsg = ConstructErrorMessage(crEx);
               
                switch (crEx.ErrorType)
                {
                    case ErrorSeverity.Exception:

                        if (crEx.ErrorCode == CrxStructCommonResourceMsg.CrxErrXmlTagIncorrectErrCd)
                        {
                            isScorSystemParameterCorrupted = true;
                            if (GuiCommon.CaptureFormLoaded)
                            {
                                GuiCommon.CaptureChildForm.tmrPwvCaptureMode.Enabled = false; 
                                GuiCommon.CaptureChildForm.tmrPwaCaptureMode.Enabled = false;                                     
                            }
                        }

                        // RadMessageBox.Show(eMsg, OMsgMgr.GetMessage(CrxStructCommonResourceMsg.SystemError), MessageBoxButtons.OK, RadMessageIcon.Error);
                       
                        RadMessageBox.Show((IWin32Window)currentWindow, eMsg, OMsgMgr.GetMessage(CrxStructCommonResourceMsg.SystemError), MessageBoxButtons.OK, RadMessageIcon.Error);
                        OLogObject.Write(OMsgMgr.GetMessage(CrxStructCommonResourceMsg.GuiErrorTxt) + eMsg);

                        if (isScorSystemParameterCorrupted)
                        {
                            CrxLogger.Instance.Write(OMsgMgr.GetMessage(CrxStructCommonResourceMsg.Exitstr));
                            BizSession.Instance().OnExit();
                            Process.GetCurrentProcess().Kill();
                        }

                        break;
                    case ErrorSeverity.Warning:
                        
                        RadMessageBox.Show((IWin32Window)currentWindow, eMsg, OMsgMgr.GetMessage(CrxStructCommonResourceMsg.SystemError), MessageBoxButtons.OK, RadMessageIcon.Exclamation);
                        // RadMessageBox.Show(eMsg, OMsgMgr.GetMessage(CrxStructCommonResourceMsg.SystemError), MessageBoxButtons.OK, RadMessageIcon.Exclamation);

                        OLogObject.Write(OMsgMgr.GetMessage(CrxStructCommonResourceMsg.GuiErrorTxt) + eMsg);

                        // GuiCommon.DefaultWindowForm.radlblMessage.Text = string.Empty;
                        // OLogObject.Write(OMsgMgr.GetMessage(CrxStructCommonResourceMsg.GuiWarningTxt) + eMsg);
                        // GuiCommon.DefaultWindowForm.radlblMessage.Text = eMsg;
                        // GuiCommon.DefaultWindowForm.guipictureboxError.Image = new Bitmap(Path.GetFullPath(ConfigurationManager.AppSettings[GuiConstants.AppConfigParams.WarningImage.ToString()]));
                        // GuiCommon.DefaultWindowForm.guialertmsgTimer.Enabled = true;
                        // GuiCommon.DefaultWindowForm.guialertmsgTimer.Tick += guialertmsgTimer_Tick;
                        break;
                    case ErrorSeverity.Information:
                        GuiCommon.DefaultWindowForm.radlblMessage.Text = string.Empty;
                        OLogObject.Write(OMsgMgr.GetMessage(CrxStructCommonResourceMsg.GuiInfoTxt) + eMsg);
                        GuiCommon.DefaultWindowForm.radlblMessage.Text = eMsg;

                       // GuiCommon.DefaultWindowForm.guipictureboxError.Image = new Bitmap(Path.GetFullPath(ConfigurationManager.AppSettings[GuiConstants.AppConfigParams.InfoImage.ToString()]));
                        break;
                    default:
                        break;
                }
            }
        } // End HandleCRXException

        /** This method constructs error message depending upon the errormessagekey, general exception object
         * and array of errorstring which is used to replace placeholders in error message
         * */
        private static string ConstructErrorMessage(ScorException crEx)
        {
            string eMsg;
            eMesg = new StringBuilder(string.Empty);

            // check for error message key to construct exception message format
            if ((!string.IsNullOrEmpty(crEx.ErrorMessageKey)) && crEx.ErrorCode != 0)
            {
                // concatenate error code & get error message as per errormessagekey                   
                eMesg.AppendLine(string.Format("{0} {1} {2}", crEx.ErrorCode, OMsgMgr.GetMessage(CrxStructCommonResourceMsg.GuiDisplayColon), OMsgMgr.GetMessage(crEx.ErrorMessageKey)));

                // check if exception object is null this will have value when general exception is thrown
                // append it to the main message                
                string errKeyTemp = OMsgMgr.GetMessage(crEx.ErrorMessageKey);
                string temp = OMsgMgr.GetMessage(CrxStructCommonResourceMsg.GuiDisplayLeftCurlyBracket);
                int count = errKeyTemp.Length - errKeyTemp.Replace(temp, string.Empty).Length;
                int arrCount = crEx.ErrorStringArr.Length;
                string[] tempArr = new string[count];
                tempArr = GetStringArr(crEx.ErrorStringArr, count, arrCount);                

                if (crEx.ExceptionObject != null)
                {
                    eMesg.AppendLine(crEx.ExceptionObject.Message + OMsgMgr.GetMessage(CrxStructCommonResourceMsg.GuiDisplayComma));
                }

                // crEx.ErrorStringArr contains placeholder values for paramter strings
                // replace the placeholders in main message with the values in crEx.ErrorStringArr 
                eMsg = tempArr.Length > 0 ? string.Format(eMesg.ToString(), tempArr) : eMesg.ToString();
            }            
            else
            {                
                eMsg = OMsgMgr.GetMessage(CrxStructCommonResourceMsg.GuiDisplayErrorException);
            }

            return eMsg;
        }

        /** This method takes error string array as parameter and forumlates an error message from the array
         * */
        private static string GetErrorString(ICollection<string> errString)
        {
            if (errString.Count > 0)
            {
                foreach (string t in errString)
                {
                    eMesg.Append(OMsgMgr.GetMessage(t));
                }
            }

            return eMesg.ToString();
        }
        
        /** This method takes error string array as parameter and forumlates an string array
         * */
        private static string[] GetStringArr(IList<string> errArrString, int count, int arrCount)
        {
            string[] tempArr = new string[count];
            if (count > arrCount)
            {
                for (int i = 0; i < arrCount; i++) 
                {
                    tempArr[i] = errArrString[i];
                }

                for (int i = arrCount; i < count; i++)
                {
                    tempArr[i] = OMsgMgr.GetMessage(CrxStructCommonResourceMsg.GuiDisplayNoValueResourceString);     
                }
            }
            else
            {
                for (int i = 0; i < count; i++)
                {
                    tempArr[i] = errArrString[i];
                }
            }

            return tempArr;
        }        

        /** This method handles general exception thrown by application which is not catched by DAL & CRX
         * */
        private static void HandleGeneralException(Exception ex, object currentWindow)
        {
            // handle general GUI exception
            RadMessageBox.Show((IWin32Window)currentWindow, ex.Message, OMsgMgr.GetMessage(CrxStructCommonResourceMsg.SystemError), MessageBoxButtons.OK, RadMessageIcon.Error);
            // RadMessageBox.Show(ex.Message, OMsgMgr.GetMessage(CrxStructCommonResourceMsg.SystemError), MessageBoxButtons.OK, RadMessageIcon.Error);

            // log exception message alongwith stack trace
            OLogObject.Write(ex.Message + Environment.NewLine + ex.Source + Environment.NewLine + ex.StackTrace);        
        } // End HandleGeneralException     
    }
}
