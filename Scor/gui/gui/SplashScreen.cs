/*
     Copyright (C) ATCOR MEDICAL PTY LTD, 2010
 
     Filename     :     Splash screen
        
     Author       :     Vibhuti Damania
 
     Description  :     Functionality implemented for showing splash screen on application launch
*/
using AtCor.Scor.CrossCutting.Messaging;
using System.Configuration; 

namespace AtCor.Scor.Gui.Presentation
{
    public partial class SplashScreen : Telerik.WinControls.UI.RadForm
    {
        private delegate void DisplayMessage(string msg);

        readonly CrxMessagingManager oMsgMgr = CrxMessagingManager.Instance;
        
        /** Constructor, subscribes event for defaultwindow & sqlinstancelist to update loading status on splash screen
         * */
        public SplashScreen()
        {
            InitializeComponent();
            lblversion.Text = ConfigurationManager.AppSettings[GuiConstants.AppConfigParams.Version.ToString()]; // hardcoded: to be read from global registry variables
            lblCopyright.Text = ConfigurationManager.AppSettings[GuiConstants.AppConfigParams.Copyright.ToString()]; // hardcoded : to be read from global registry variables
            lblInitialMsg.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.SplashIniMsg) + oMsgMgr.GetMessage(CrxStructCommonResourceMsg.SplashWaitMsg);
            DefaultWindow.OnInitializationProcess += ShowInitializationMessage;
            SQLInstanceList.OnInitializationProcess += ShowInitializationMessage;
            radVersionNo.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.SplashLblVersionTxt);
            radLabelScorName.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.SplashLblScorTxt);
            radLabelCopyRight.Text = oMsgMgr.GetMessage(CrxStructCommonResourceMsg.SpalshCopyrtTxt);
        }

        /** This method shows status messages on splash screen as per the default window loading process.
         * */
        public void ShowInitializationMessage(string message)
        {
            if (InvokeRequired)
            {
                DisplayMessage displaymsg = ShowInitializationMessage;
                Invoke(displaymsg, message);
                return;
            }

            if (message == oMsgMgr.GetMessage(CrxStructCommonResourceMsg.BtnExit))
            {
               SendToBack();
            }
            else
            {
                lblInitialMsg.Text = message;
                Refresh();
            }            
        }
    }
}
