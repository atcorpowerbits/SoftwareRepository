using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using AtCor.Scor.CrossCutting.Configuration;
using AtCor.Scor.CrossCutting.Messaging;
using AtCor.Scor.CrossCutting.Logging;
using System.Windows.Forms;

namespace AtCor.Scor.Gui.Presentation
{
    // public delegate void SettingsChangedEventHandler(Object sender,EventArgs  args);   
   public static class SettingsProperties
   {
       ////#region struct
       ////public struct registyKeyInfo
       ////{
       ////   public static string environment = string.Empty;         
       ////};
       ////#endregion

       // public enum eEnvironment {Clinical, Research};

       // public event SettingsChangedEventHandler OnSettingsChangedEvent;
       #region Global variable declaration
       public static bool SetupToReport = false;
       public static bool CaptureToReport = false;
       public static bool CaptureToSetup = false;
       public static bool HasMeasurementDetails = false;
       public static string Environment = string.Empty;
       
       #endregion
        #region Child Form Handles
        public static Telerik.WinControls.UI.RadForm reportChildForm;
        public static Telerik.WinControls.UI.RadForm captureChildForm;
        public static Telerik.WinControls.UI.RadForm setupChildForm;

        public static Telerik.WinControls.UI.RadForm frmRptBlnk;
        #endregion

        #region Global variable declaration

        public static string GCI = string.Empty;
        #endregion

        #region General settings private variables

        private static bool patient_privacy = false;
        private static int height_weight_units = 0;
        private static int blood_pressure = 0;
        private static int systemidentifier = 0;
        private static int patientinternalnumber = 0;
        private static int groupid = 0;
        private static string groupname = string.Empty;
              
        #endregion

        #region PWV settings private variables
        private static int pwv_distance_units = 0;
        private static int pwv_distance_method = 0;
        private static int capture_time = 0;
        private static bool cuff_location = false;
        private static bool reference_range = false;
        private static string pwvcurrentstudydatetime = string.Empty; 
       
        #endregion

        #region General settings properties
        public static int SystemIdentifier
        {
            get
            {
                return systemidentifier;
            }

            set
            {
                systemidentifier = value;
            }
        }

        public static int PatientInternalNumber
        {
            get
            {
                return patientinternalnumber;
            }

            set
            {
                patientinternalnumber = value;
            }
        }

        public static int GroupID
        {
            get
            {
                return groupid;
            }

            set
            {
                groupid = value;
            }
        }

        public static string GroupName
        {
            get
            {
                return groupname;
            }

            set
            {
                groupname = value;
            }
        }

        public static int HeightWeightUnits
        {
            get
            {
                return height_weight_units;
            }

            set
            {
                height_weight_units = value;
            }
        }

        public static int BloodPressure
        {
            get
            {
                return blood_pressure;
            }

            set
            {
                blood_pressure = value;
            }
        }

        public static bool PatientPrivacy
        {
            get
            {
                return patient_privacy;
            }

            set
            {
                patient_privacy = value;
            }
        }

        #endregion

        #region PWV settings properties
        public static string PwvCurrentStudyDatetime
        {
            get
            {
                return pwvcurrentstudydatetime;
            }

            set
            {
                pwvcurrentstudydatetime = value;
            }
        }

        public static int PwvDistanceUnits
        {
            get
            {
                return pwv_distance_units;
            }

            set
            {
                pwv_distance_units = value;
            }
        }

        public static int PwvDistanceMethod
        {
            get
            {
                return pwv_distance_method;
            }

            set
            {
                pwv_distance_method = value;
            }
        }

        public static int CaptureTime
        {
            get
            {
                return capture_time;
            }

            set
            {
                capture_time = value;
            }
        }

        public static bool CuffLocation
        {
            get
            {
                return cuff_location;
            }

            set
            {
                cuff_location = value;
            }
        }

        public static bool ReferenceRange
        {
            get
            {
                return reference_range;
            }

            set
            {
                reference_range = value;
            }
        }
        #endregion

        #region methods..
        /** This method retrieves database servername
        * */
        public static string ServerNameString()
        {
            CrxConfigManager crxMgrObject = CrxConfigManager.Instance;
          
            if (crxMgrObject.GeneralSettings.ServerName == null)
            {
                return crxMgrObject.GeneralSettings.MachineName.Trim();
            }
            else
            {
                return crxMgrObject.GeneralSettings.MachineName.Trim() + @"\" + crxMgrObject.GeneralSettings.ServerName.Trim();
            }
        }

       /** This method retrieves error message during network connection failure
        * */
        public static string ConnectionErrorString()
        {
            string errorMsg = string.Empty;

            // initialize servername string with static method ServerNameString()
            string servername = ServerNameString();
            CrxMessagingManager oMsgMgr = CrxMessagingManager.Instance;            
          
            // Vibhuti: string for CONTACT_ATCOR_SUPPORT defined as per jira comments in SWREQ007
            if (!servername.Contains(SystemInformation.ComputerName))
            {
                // remote PC
                errorMsg += oMsgMgr.GetMessage("SQL_NETWORK_ERROR_STRG") + "\r\n\r\n";
            }
            else
            {
                errorMsg += oMsgMgr.GetMessage("SQL_LOCAL_ERROR_STRG") + "\r\n\r\n";
            }

            errorMsg += oMsgMgr.GetMessage("CONTACT_ATCOR_SUPPORT"); // +"\r\n" + oMsgMgr.GetMessage("CONTACT_ATCOR_SUPPORT1");

            // log the error
            CrxLogger oLogObject = CrxLogger.Instance;
            oLogObject.Write(errorMsg);

            return errorMsg;
        }

       /** This method gets environment information
        * */
        public static string GetEnvironment()
        {
            CrxMessagingManager oMsgMgr = CrxMessagingManager.Instance;

            // registyKeyInfo regKey = new registyKeyInfo(oMsgMgr.GetMessage("ENV_CLINICAL_TEXT"));
            Environment = oMsgMgr.GetMessage("ENV_CLINICAL_TEXT");
            return Environment;
        }

        #endregion
    }
}
