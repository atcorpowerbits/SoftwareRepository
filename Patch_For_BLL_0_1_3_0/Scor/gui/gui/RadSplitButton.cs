/*
     Copyright (C) ATCOR MEDICAL PTY LTD, 2010
 
    Filename     :      RadSpilt Button
        
    Author       :      Nitesh Chhedda
 
    Description  :      This class is wriiten to customize the rad split button used on the Report screen.
*/
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows.Forms;

/**
 * @namespace AtCor.Scor.Gui.Presentation
 * @brief This namespace implements Presentation related classes.
 * 
 */
namespace AtCor.Scor.Gui.Presentation
{
    /**
    * @class RadSplitButton
    * @brief This class will handle customizing of the Rad split button used on the Report screen.
    * For instance,we have overidden the OnEnter property of the rad split button so that it gets focus when the control goes on it.
    */
    class RadSplitButton : Telerik.WinControls.UI.RadSplitButton
    {
        /**This method is overridden so that the radsplit buuton gets focus when control is selected through keyboard.
         */ 
        protected override void OnEnter(EventArgs e)
        {
            base.OnEnter(e);
            DropDownButtonElement.ActionButton.Focus();
        }

        /**This method is overidden so that when Enter of Space key is pressed, the drop down options for the Rad split button are shown.
        */ 
        protected override void OnKeyDown(KeyEventArgs e)
        {
            base.OnKeyDown(e);

            if (e.KeyCode == Keys.Enter || e.KeyCode == Keys.Space)
            {
                ShowDropDown();
            }
        }

        public override string ThemeClassName
        {
            get
            {
                return typeof(Telerik.WinControls.UI.RadSplitButton).FullName;
            }
        }
    }
}
