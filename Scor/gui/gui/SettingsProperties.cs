﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Gui.Atcor.Scor.Presentation
{
    //public delegate void SettingsChangedEventHandler(Object sender,EventArgs  args);
    
   public static class SettingsProperties
    {
       //public event SettingsChangedEventHandler OnSettingsChangedEvent;

        #region General settings private variables

        private static bool patient_privacy = false;
        private static int height_weight_units = 0;
        private static int blood_pressure = 0;

        #endregion

        #region PWV settings private variables
        private static int pwv_distance_units = 0;
        private static int pwv_distance_method = 0;
        private static int capture_time = 0;
        private static bool cuff_location = false;
        private static bool reference_range = false;
       
        #endregion

        #region General settings properties
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
    }
}
