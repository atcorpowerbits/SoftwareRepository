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
       /** This method handle handle all types of exception & throws appropriate messages
        * */
        public static void HandleException(Exception ex, object currentWindow)
        {
            CrxMessagingManager oMsgMgr = CrxMessagingManager.Instance;
            CrxLogger oLogObject = CrxLogger.Instance;

            if (ex.GetType() == typeof(CrxException))
            { 
                // handle crx exception
                CrxException crEx = (CrxException)ex;
                if (crEx.ErrorCode == -1)
                {
                    // crx unhandled exception
                    RadMessageBox.Show((IWin32Window)currentWindow, crEx.Message, oMsgMgr.GetMessage("SYSTEM_ERROR"), MessageBoxButtons.OK, RadMessageIcon.Error);

                    // log exception message alongwith stack trace
                    oLogObject.Write(crEx.Message + " \n\n " + crEx.StackTrace);
                }
                else
                {
                    // crx handled exception
                    RadMessageBox.Show((IWin32Window)currentWindow, crEx.ErrorString, oMsgMgr.GetMessage("SYSTEM_ERROR"), MessageBoxButtons.OK, RadMessageIcon.Error);

                    // log error message
                    oLogObject.Write(crEx.ErrorString);
                }
            }
            else if (ex.GetType() == typeof(DalException))
            {
                // handle dal exception
                DalException dalEx = (DalException)ex;
                if (dalEx.ErrorCode == -1)
                {
                    // dal unhandled exception
                    RadMessageBox.Show((IWin32Window)currentWindow, dalEx.Message, oMsgMgr.GetMessage("SYSTEM_ERROR"), MessageBoxButtons.OK, RadMessageIcon.Error);

                    // log exception message alongwith stack trace
                    oLogObject.Write(dalEx.Message + " \n\n " + dalEx.StackTrace);
                }
                else
                {
                    // dal unhandled exception
                    RadMessageBox.Show((IWin32Window)currentWindow, dalEx.ErrorString, oMsgMgr.GetMessage("SYSTEM_ERROR"), MessageBoxButtons.OK, RadMessageIcon.Error);

                    // log error message
                    oLogObject.Write(dalEx.ErrorString);
                }
            }
            else
            { 
                // handle general GUI exception
                RadMessageBox.Show((IWin32Window)currentWindow, ex.Message, oMsgMgr.GetMessage("SYSTEM_ERROR"), MessageBoxButtons.OK, RadMessageIcon.Error);

                // log exception message alongwith stack trace
                oLogObject.Write(ex.Message + " \n\n " + ex.StackTrace);
            }     
        }    
    }
}
