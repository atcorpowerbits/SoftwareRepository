using System;
using System.Collections.Generic;
using System.Linq;
using AtCor.Scor.CrossCutting.Configuration;
using AtCor.Scor.CrossCutting.Messaging;
using AtCor.Scor.BusinessLogic;
using Telerik.WinControls;
using Telerik.WinControls.UI;
using System.Windows.Forms;

namespace AtCor.Scor.Gui.Presentation
{
    public class GuiFieldValidation
    {
       public List<RadTextBox> mandatoryTextboxes = new List<RadTextBox>();

       readonly CrxMessagingManager oMsgMgr = CrxMessagingManager.Instance;

       List<RadLabel> mandatoryLabels = new List<RadLabel>();

       bool isFieldEmpty = false;

        /** This method sets metric units & height & weight units for Biz data validations after reading from configuration file
        * at the launch of application and when any changes are made from settings window 
        * */
        public static void SetMeasForBizValidation()
        {
            CrxConfigManager crxConfig = CrxConfigManager.Instance;
            UnitsType setUnits;
            MetricDistanceUnits metricUnits;

            // check height weight units from config and accordingly set the units
            switch (crxConfig.GeneralSettings.HeightandWeightUnit)
            {
                case (int)CrxGenPwvValue.CrxGenHeightWeightMetric:
                    setUnits = UnitsType.UNITS_METRIC;
                    break;
                case (int)CrxGenPwvValue.CrxGenHeightWeightImperial:
                    setUnits = UnitsType.UNITS_IMPERIAL;
                    break;
                default:
                    setUnits = UnitsType.UNITS_INVALID;
                    break;
            }

            // check PWV distance units from config and accordingly set the units
            switch (crxConfig.PwvSettings.PWVDistanceUnits)
            {
                case (int)CrxGenPwvValue.CrxPwvDistDistUnitsMM:
                    metricUnits = MetricDistanceUnits.METRIC_DISTANCE_MM;
                    break;
                case (int)CrxGenPwvValue.CrxPwvDistDistUnitsCM:
                    metricUnits = MetricDistanceUnits.METRIC_DISTANCE_CM;
                    break;
                default:
                    metricUnits = MetricDistanceUnits.METRIC_DISTANCE_INVALID;
                    break;
            }

            // call the BizDataValidation object and set the values being read from config
            BizDataValidation.Instance().SetMeasSystem(setUnits, metricUnits);
        }

        public GuiFieldValidation(params Panel[] radCtrl)
        {
           // call the method to set mandatory fields for control
            SetMandatoryFields(radCtrl);
        }
        
        /** This method fetches mandatory fields information from Business logic
         * Sets astriek for labels on measurement details section
         * prepare ab array of textboxes to be validated for missing field
         * */
        public void SetMandatoryFields(params Panel[] radCtrl)
        {
            CrxConfigManager crxConfig = CrxConfigManager.Instance;
                        
            string[] mandatory = BizDataValidation.GetMandatoryFields(BizMode.PWV, crxConfig.PwvSettings.PWVDistanceMethod);
            
            // clear items in array list
            mandatoryLabels.Clear();
            mandatoryTextboxes.Clear();

            // this loop calls the panels which are passed as argument to constructor
            foreach (Panel t in radCtrl)
            {
                // following query fetches only the validation fields from the measurement panel based on the tag values
                // it will retirieve label & textboxes which has tag values
                var ctrlCollection = (from c in t.Controls.Cast<Control>()
                                      where c.Tag != null && c.Tag.ToString() != string.Empty
                                      select c);

                // loop through the controls in contols collection
                foreach (RadControl ctrl in ctrlCollection)
                {
                    SetControls(ctrl, mandatory);

                    // now get the array of labels used for field level validation
                    if (ctrl.GetType() == typeof(RadLabel))
                    {
                        mandatoryLabels.Add((RadLabel)ctrl);
                    }
                } // end ctrlCollection for each 
            }                  
        }

        /** This method takes parameter as textbox. It checks whether the value in textbox is within the limits and range defined for that textbox
         * If not within valid range, it will show error message
         * */
        public void CheckFieldLimits(RadTextBox radtxtCtrl)
        {
            try
            {
                if (radtxtCtrl.Text.Length > 0)
                {
                    int fieldValue = int.Parse(radtxtCtrl.Text.Trim());
                    GetValidationErrorMsg(fieldValue, radtxtCtrl);
                }              
            }
            catch (OverflowException)
            {
                GetValidationErrorMsg(-1, radtxtCtrl);
            }
            catch (Exception ex)
            {
                GUIExceptionHandler.HandleException(ex, radtxtCtrl.FindForm());
            }
        }

        /** This method takes parameter as textbox. It checks whether the value in textbox is within the limits and range defined for that textbox
        * If not within valid range, it will show error message
        * */
        public void CheckIntegerFieldLimits(RadTextBox radtxtCtrl)
        {
            try
            {
                if (radtxtCtrl.Text.Length > 0)
                {
                    int fieldValue = int.Parse(radtxtCtrl.Text.Trim());
                    GetIntegerValidationErrorMsg(fieldValue, radtxtCtrl);
                }
            }
            catch (OverflowException)
            {
                GetIntegerValidationErrorMsg(-1, radtxtCtrl);
            }
            catch (Exception ex)
            {
                GUIExceptionHandler.HandleException(ex, radtxtCtrl.FindForm());
            }
        }

        /** This method takes parameter as textbox. It checks whether the value in textbox is within the limits and range defined for that textbox
      * If not within valid range, it will show error message
      * */
        public void CheckIntegerFieldLimitsRemoveInvalidValue(RadTextBox radtxtCtrl)
        {
            try
            {
                if (radtxtCtrl.Text.Length > 0)
                {
                    int fieldValue = int.Parse(radtxtCtrl.Text.Trim());
                    GetIntegerValidationErrorMsgRemoveInvalidValue(fieldValue, radtxtCtrl);
                }
            }
            catch (OverflowException)
            {
                GetIntegerValidationErrorMsgRemoveInvalidValue(-1, radtxtCtrl);
            }
            catch (Exception ex)
            {
                GUIExceptionHandler.HandleException(ex, radtxtCtrl.FindForm());
            }
        }

        /** This method checks if mandatory fields are entered and accordingly displays missing field error message
         * */
        public bool CheckMandatoryFields()
        {
            string errMsg = string.Empty;
            GuiCommon.IsMandatoryFieldEmpty = false;
            int countFields = 0;
            GuiCommon.ExitApp = 0;
            GuiCommon.IsMenuItemShown = true;

            // for each textboxes in array, check if it empty or not and accordingly append error message in a string
            foreach (RadTextBox txt in mandatoryTextboxes.Where(txt => txt.Text.Length == 0))
            {
                countFields++;
                errMsg += GetLabelText(txt.Tag.ToString()) + oMsgMgr.GetMessage(CrxStructCommonResourceMsg.GuiDisplayComma);
            }

            if (errMsg.Length > 0)
            {
                isFieldEmpty = true;
                GuiCommon.IsMandatoryFieldEmpty = true;
                GuiCommon.ExitApp = 1;
                GuiCommon.IsMenuItemShown = false;

                // formulate error message string
                errMsg = errMsg.EndsWith(oMsgMgr.GetMessage(CrxStructCommonResourceMsg.GuiDisplayComma)) ? errMsg.Remove(errMsg.Length - 1) : errMsg;
                errMsg = string.Format(oMsgMgr.GetMessage(CrxStructCommonResourceMsg.GuiPleaseEnterFormat), errMsg);

                if (countFields > 1)
                {
                    errMsg = errMsg.Replace(errMsg.Substring(errMsg.LastIndexOf(oMsgMgr.GetMessage(CrxStructCommonResourceMsg.GuiDisplayComma)), 1), oMsgMgr.GetMessage(CrxStructCommonResourceMsg.GuiDisplayAmpersand));
                }

                // show the missing fields error to the user
                RadMessageBox.Show(errMsg, oMsgMgr.GetMessage(CrxStructCommonResourceMsg.SystemError), MessageBoxButtons.OK, RadMessageIcon.Error);
            }
            else
            {
                foreach (RadTextBox txt in mandatoryTextboxes.Where(txt => txt.Text.Length > 0))
                {
                    CheckFieldLimits(txt);
                    if (isFieldEmpty)
                    {
                        GuiCommon.IsMenuItemShown = false;
                        break;
                    }
                }
            }

            return isFieldEmpty;
        }

        /** This method fetched label text to display for error messages for missing fields & validation
       */
        public string GetLabelText(string txtTag)
        {
            string tag = txtTag;

            // fetch label whose tag matches txtTag
            RadLabel radLbl = (from RadLabel lbl in mandatoryLabels
                               where lbl.Tag.ToString() == txtTag
                               select lbl).FirstOrDefault();

            // if radLbl is not null use the label text to show error message
            if (radLbl != null)
            {
                // replace the "*:" & ":" in label text abd break the loop
                tag = radLbl.Text.Replace(oMsgMgr.GetMessage(CrxStructCommonResourceMsg.GuiDisplayAsteriskColon), string.Empty).Replace(oMsgMgr.GetMessage(CrxStructCommonResourceMsg.GuiDisplayColon), string.Empty);
            }

            return tag;
        }

        /** This method checks the field values within range from Biz logic 
        * and shows error message if it doesn't fall within the range
        * */
        private void GetIntegerValidationErrorMsg(int fieldValue, RadTextBox radtxtCtrl)
        {
            isFieldEmpty = false;

            // read limits
            int min = UInt16.MinValue;
            int max = UInt16.MaxValue;

            // check if value is within min & max limits
            if (fieldValue > max || fieldValue < min)
            {
                // field validation error
                isFieldEmpty = true;
                GuiCommon.IsValueOutsideIntegerLimits = true;
                string field = GetLabelText(radtxtCtrl.Tag.ToString());

               // radtxtCtrl.Text = string.Empty;
                string err = string.Format(oMsgMgr.GetMessage(CrxStructCommonResourceMsg.GuiLimitsFormat), field, min, string.Empty, max, string.Empty);
                RadMessageBox.Show(err, oMsgMgr.GetMessage(CrxStructCommonResourceMsg.SystemError), MessageBoxButtons.OK, RadMessageIcon.Error);
            }
            else
            {
                GuiCommon.IsValueOutsideIntegerLimits = false;
            }
        }
       
        /** This method checks the field values within range from Biz logic 
        * and shows error message if it doesn't fall within the range
        * */
        private void GetIntegerValidationErrorMsgRemoveInvalidValue(int fieldValue, RadTextBox radtxtCtrl)
        {
            isFieldEmpty = false;

            // read limits
            int min = UInt16.MinValue;
            int max = UInt16.MaxValue;

            // check if value is within min & max limits
            if (fieldValue > max || fieldValue < min)
            {
                // field validation error
                isFieldEmpty = true;
                GuiCommon.IsValueOutsideIntegerLimits = true;
                string field = GetLabelText(radtxtCtrl.Tag.ToString());

                radtxtCtrl.Text = string.Empty;
                string err = string.Format(oMsgMgr.GetMessage(CrxStructCommonResourceMsg.GuiLimitsFormat), field, min, string.Empty, max, string.Empty);
                RadMessageBox.Show(err, oMsgMgr.GetMessage(CrxStructCommonResourceMsg.SystemError), MessageBoxButtons.OK, RadMessageIcon.Error);
            }
            else
            {
                GuiCommon.IsValueOutsideIntegerLimits = false;
            }
        }          

        /** This method checks if the control is label or textbox and accordingly sets it mandatory
      */
        private void SetControls(RadControl ctrl, IList<string> mandatory)
        {
            // loop for the mandatory field array returned from biz dll
            for (int i = 0; i < mandatory.Count; i++)
            {
                if (ctrl.GetType() == typeof(RadLabel) && ctrl.Tag.ToString().Equals(mandatory[i]))
                {
                    // check if control is label and is mandatory
                    // put astriek against that label
                    ctrl.Text =
                        ctrl.Text.Contains(oMsgMgr.GetMessage(CrxStructCommonResourceMsg.GuiDisplayAsteriskColon))
                            ? ctrl.Text
                            : ctrl.Text.Replace(
                                                oMsgMgr.GetMessage(CrxStructCommonResourceMsg.GuiDisplayColon),
                                                oMsgMgr.GetMessage(CrxStructCommonResourceMsg.GuiDisplayAsteriskColon));

                    // found matching control, goto next control
                    break;
                }

                if (ctrl.GetType() == typeof(RadTextBox) && ctrl.Tag.ToString().Equals(mandatory[i]))
                {
                    // check if control is textbox and is mandatory
                    // move the textbox in array of mandatory textboxes
                    mandatoryTextboxes.Add((RadTextBox)ctrl);

                    // found matching control, goto next control
                    break;
                }
            }
        } // End mandatory array for loop        

        /** This method checks the field values within range from Biz logic 
         * and shows error message if it doesn't fall within the range
         * */
        private void GetValidationErrorMsg(int fieldValue, RadTextBox radtxtCtrl)
        {
            // instantiate BizDataLimits to retrieve limits for a particular field
            BizDataLimits lim = BizDataValidation.Instance().GetLimits(radtxtCtrl.Tag.ToString());
            isFieldEmpty = false;            

            // read limits and units 
            int min = lim.GetMin();
            int max = lim.GetMax();
            string units = lim.GetUnits();

            // check if value is within min & max limits
            if (fieldValue > max || fieldValue < min)
            {
                // field validation error
                isFieldEmpty = true;
                GuiCommon.IsValueOutsideLimits = true;
                string field = GetLabelText(radtxtCtrl.Tag.ToString());
                radtxtCtrl.Text = string.Empty;
                string err = string.Format(oMsgMgr.GetMessage(CrxStructCommonResourceMsg.GuiLimitsFormat), field, min, units, max, units);
                RadMessageBox.Show(err, oMsgMgr.GetMessage(CrxStructCommonResourceMsg.SystemError), MessageBoxButtons.OK, RadMessageIcon.Error);
            }
            else
            {
                GuiCommon.IsValueOutsideLimits = false;
            }
        }       
    }
}
