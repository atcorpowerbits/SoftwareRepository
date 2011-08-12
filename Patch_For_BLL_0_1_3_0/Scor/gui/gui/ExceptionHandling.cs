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


namespace AtCor.Scor.Gui.Presentation
{
    public class ExceptionHandling
    {
        CrxMessagingManager oMsgMgr = CrxMessagingManager.Instance;
        CrxLogger oLogObject = CrxLogger.Instance;

        public ExceptionHandling(CrxException cx, object currentWindow)
        {
            RadMessageBox.Show((IWin32Window)currentWindow, cx.ErrorString, oMsgMgr.GetMessage("SYSTEM_ERROR"), MessageBoxButtons.OK, RadMessageIcon.Error);            
            oLogObject.Write(cx.ErrorString); 
        }

        public ExceptionHandling(Exception ex, object currentWindow)
        {
            RadMessageBox.Show((IWin32Window)currentWindow, ex.Message, oMsgMgr.GetMessage("SYSTEM_ERROR"), MessageBoxButtons.OK, RadMessageIcon.Error);           
            oLogObject.Write(ex.Message); 
        }
    
    
    }
}
