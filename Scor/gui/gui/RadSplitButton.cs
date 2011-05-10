using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace gui
{
    class RadSplitButton : Telerik.WinControls.UI.RadSplitButton
    {
        protected override void OnEnter(EventArgs e)
        {
            base.OnEnter(e);
            base.DropDownButtonElement.ActionButton.Focus();
        }

        protected override void OnKeyDown(KeyEventArgs e)
        {
            base.OnKeyDown(e);

            if (e.KeyCode == Keys.Enter || e.KeyCode == Keys.Space)
            {
                base.ShowDropDown();
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
