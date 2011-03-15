/*
     Copyright (C) ATCOR MEDICAL PTY LTD, 2010
 
     Filename     :     Splash screen
        
     Author       :     Vibhuti Damania
 
     Description  :     Functionality implemented for showing splash screen on application launch
*/
using AtCor.Scor.CrossCutting.Messaging;

namespace AtCor.Scor.Gui.Presentation
{
    public partial class SplashScreen : Telerik.WinControls.UI.RadForm
    {
        private delegate void DisplayMessage(string msg);

        readonly CrxMessagingManager oMsgMgr = CrxMessagingManager.Instance;

        // private static Thread _splashLauncher;
        // private static SplashScreen _splashScreen;

        /** Constructor, subscribes event for defaultwindow & sqlinstancelist to update loading status on splash screen
         * */
        public SplashScreen()
        {
            InitializeComponent();
            lblversion.Text = "10"; // hardcoded: to be read from global registry variables
            lblCopyright.Text = "2011"; // hardcoded : to be read from global registry variables
            lblInitialMsg.Text = oMsgMgr.GetMessage("SPLASH_INI_MSG") + oMsgMgr.GetMessage("SPLASH_WAIT_MSG");
            DefaultWindow.OnInitializationProcess += new DefaultWindow.InitializationMessage(ShowInitializationMessage);
            SQLInstanceList.OnInitializationProcess += new SQLInstanceList.InitializationMessage(ShowInitializationMessage);
            radVersionNo.Text = oMsgMgr.GetMessage("SPLASH_LBL_VERSION_TXT");
            radLabelScorName.Text = oMsgMgr.GetMessage("SPLASH_LBL_SCOR_TXT");
            radLabelCopyRight.Text = oMsgMgr.GetMessage("SPALSH_COPYRT_TXT");
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

            if (message == oMsgMgr.GetMessage("BTN_EXIT"))
            {
               SendToBack();
            }
            else
            {
                lblInitialMsg.Text = message;
                Refresh();
            }            
        }

        // ############## code to start splash screen separate thread
        ////public static void ShowSplash()
        ////{
        ////    //Show the form in a new thread
        ////    _splashLauncher = new Thread(new ThreadStart(LaunchSplash));
        ////    _splashLauncher.IsBackground = true;
        ////    _splashLauncher.Start();

        ////}

        ////private static void LaunchSplash()
        ////{
        ////    _splashScreen = new SplashScreen();

        ////    //Create new message pump
        ////    Application.Run(_splashScreen);
        ////}

        ////private static void CloseSplashDown()
        ////{
        ////    Application.ExitThread();
        ////}

        ////public static void CloseSplash()
        ////{
        ////    //Need to get the thread that launched the form, so
        ////    //we need to use invoke.
        ////    MethodInvoker mi = new MethodInvoker(CloseSplashDown);
        ////    _splashScreen.Invoke(mi);
        ////}
    }
}
