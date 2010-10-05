using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Linq;
using System.Reflection;
using System.Windows.Forms;
using System.Text;
//?using Biz;

namespace gui
{
    partial class AboutBox1 : Form
    {
        public AboutBox1()
        {
            int coInfoSize = 100;
            StringBuilder coInfo = new StringBuilder(coInfoSize);
            String coInfoStr = coInfo.ToString();

            InitializeComponent();
            this.Text = String.Format("About {0} {0}", AssemblyTitle);
            this.labelProductName.Text = AssemblyProduct;
//eg            this.labelVersion.Text = String.Format("Version {0} {0}", AssemblyVersion);
            Biz.BizFacade.Instance().FindBizInfo().GetVersion(ref coInfoStr, coInfoSize); ;
            this.labelVersion.Text = coInfoStr;
            this.labelCopyright.Text = AssemblyCopyright;
            Biz.BizFacade.Instance().FindBizInfo().GetCompanyName(ref coInfoStr, coInfoSize); ;
//eg            this.labelCompanyName.Text = AssemblyCompany;
            this.labelCompanyName.Text = coInfoStr;
            this.textBoxDescription.Text = AssemblyDescription;
            Biz.BizFacade.Instance().FindBizInfo().GetModuleType(ref coInfoStr, coInfoSize); ;
            this.labelModuleType.Text = coInfoStr;
            this.labelModuleCapability.Text = Biz.BizFacade.Instance().FindBizInfo().GetModuleCapability().ToString();
            Biz.BizFacade.Instance().FindBizInfo().GetModuleSN(ref coInfoStr, coInfoSize); ;
            this.labelModuleSN.Text = coInfoStr;
            Biz.BizFacade.Instance().FindBizInfo().GetModuleVersion(ref coInfoStr, coInfoSize); ;
            this.labelModuleFMVersion.Text = coInfoStr;
        }

        #region Assembly Attribute Accessors

        public string AssemblyTitle
        {
            get
            {
                object[] attributes = Assembly.GetExecutingAssembly().GetCustomAttributes(typeof(AssemblyTitleAttribute), false);
                if (attributes.Length > 0)
                {
                    AssemblyTitleAttribute titleAttribute = (AssemblyTitleAttribute)attributes[0];
                    if (titleAttribute.Title != "")
                    {
                        return titleAttribute.Title;
                    }
                }
                return System.IO.Path.GetFileNameWithoutExtension(Assembly.GetExecutingAssembly().CodeBase);
            }
        }

        public string AssemblyVersion
        {
            get
            {
                return Assembly.GetExecutingAssembly().GetName().Version.ToString();
            }
        }

        public string AssemblyDescription
        {
            get
            {
                object[] attributes = Assembly.GetExecutingAssembly().GetCustomAttributes(typeof(AssemblyDescriptionAttribute), false);
                if (attributes.Length == 0)
                {
                    return "";
                }
                return ((AssemblyDescriptionAttribute)attributes[0]).Description;
            }
        }

        public string AssemblyProduct
        {
            get
            {
                object[] attributes = Assembly.GetExecutingAssembly().GetCustomAttributes(typeof(AssemblyProductAttribute), false);
                if (attributes.Length == 0)
                {
                    return "";
                }
                return ((AssemblyProductAttribute)attributes[0]).Product;
            }
        }

        public string AssemblyCopyright
        {
            get
            {
                object[] attributes = Assembly.GetExecutingAssembly().GetCustomAttributes(typeof(AssemblyCopyrightAttribute), false);
                if (attributes.Length == 0)
                {
                    return "";
                }
                return ((AssemblyCopyrightAttribute)attributes[0]).Copyright;
            }
        }

        public string AssemblyCompany
        {
            get
            {
                object[] attributes = Assembly.GetExecutingAssembly().GetCustomAttributes(typeof(AssemblyCompanyAttribute), false);
                if (attributes.Length == 0)
                {
                    return "";
                }
                return ((AssemblyCompanyAttribute)attributes[0]).Company;
            }
        }
        #endregion

        private void okButton_Click(object sender, EventArgs e)
        {
            Close();
        }

    }
}
