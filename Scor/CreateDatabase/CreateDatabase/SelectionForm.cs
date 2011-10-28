using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.Data.Sql;
using System.Diagnostics;
using System.IO;
using System.Globalization;
using System.Resources;
using System.Reflection;

namespace CreateDatabase
{
    public partial class SelectionForm : Form
    {
        //Constructor of the Class Form        
        public SelectionForm()
        {
            //Initialize the form componets
            InitializeComponent();
        }

        //Load the form and add/display required data on the form
        private void SelectionForm_Load(object sender, EventArgs e)
        {
            try
            {  
               
                // below code returns all the sql server instances available in a network 
                // with instance name for running instances, it gives values (server name, instance name, isclustered, version)
                SqlDataSourceEnumerator getCurInst = SqlDataSourceEnumerator.Instance;
                DataTable dt = getCurInst.GetDataSources();

                //Remove the Control box from the form
                this.ControlBox = false;

                //Append the server list in the form drop-down list
                guicmbxSqlServerList.DataSource = dt;                
         
                //TODO: Below mentioned control test message should come from resource string
                guicmbxSqlServerList.DisplayMember = ApplicationMessageManager.Instance.GetMessage("SERVER_NAME_TEXT");
                this.Text = ApplicationMessageManager.Instance.GetMessage("AVAILABLE_DATABASES_TEXT");
                labelMesg.Text = ApplicationMessageManager.Instance.GetMessage("SELECT_SERVER_TEXT");
                button_Ok.Text = ApplicationMessageManager.Instance.GetMessage("BTN_OK");
                button_Cancel.Text = ApplicationMessageManager.Instance.GetMessage("BTN_CANCEL");
              

            }
            catch (Exception exObj)
            {
                //TODO: Add proper exception handling and error mechanism
                MessageBox.Show(exObj.Message, "Scor", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }

        //Calls the method when the Ok button is Clicked
        private void button_Ok_Click(object sender, EventArgs e)
        {
            int outputErrCode = 0;                //Contains the process error output
            string serverName = string.Empty;     //Contains the Server Name
            string directoryLocation = string.Empty;     //Contains application directory location
            string scriptName = string.Empty;     //Contains the script file name
            string output = string.Empty;     //Contains the process output message
            string tempString = string.Empty;     //For manipulating temporary string
            string errorString = string.Empty;     //Contains the error message string for manipulation
            string[] outputMesgArr = null;             //Contains the split string array

            try
            {
                //Create Server Name
                serverName = string.Format(ApplicationConstants.ServerNameFormat, guicmbxSqlServerList.Text);

                //Get Directory location of the excutable application 
                directoryLocation = Directory.GetCurrentDirectory();

                //Hide the application form
                Hide();

                //Create the process object
                Process myProcess = new Process();

                //Process process arguments

                //Cm window will not be populated for the process 
                myProcess.StartInfo.CreateNoWindow = true;
                myProcess.StartInfo.WindowStyle = ProcessWindowStyle.Hidden;

                //Pass the working directory location
                myProcess.StartInfo.WorkingDirectory = directoryLocation;

                //Shell exceute process will not be executed
                myProcess.StartInfo.UseShellExecute = false;

                //TODO: Remove harcoding of filenames in this code
                //Pass the batch name with the file location
                myProcess.StartInfo.FileName = directoryLocation + ApplicationConstants.BatchFileName;

                //Validation of execute/run which script as per Database Key
                if (DatabaseCreation.DatabaseProcessKey == DatabaseKey.DbCreation)
                {
                    scriptName = ApplicationConstants.CreateScriptFileName;
                    //Passing arguments to the process
                    myProcess.StartInfo.Arguments = @" " + "\"" + serverName + "\" " + scriptName;
                }
                else
                {
                    scriptName = ApplicationConstants.DeleteScriptFileName;
                    //Passing arguments to the process
                    myProcess.StartInfo.Arguments = @" " + "\"" + serverName + "\" " + scriptName;
                }

                //Set to return output error message
                myProcess.StartInfo.RedirectStandardOutput = true;

                //Set to return error code
                myProcess.StartInfo.RedirectStandardError = true;

                // now execute the batch file
                myProcess.Start();
                myProcess.WaitForExit();

                //Get the Standard output message of the process
                output = myProcess.StandardOutput.ReadToEnd();

                //formatting the output message to be displayed

                //Split the Output error message in to string array as per new lines
                outputMesgArr = output.Split('\n');

                //Get the second last string value from the Output message string array
                tempString = outputMesgArr[outputMesgArr.Length - 2];

                //Get the formatted outout message string
                errorString = ErrorMessageString(tempString);

                //Convert from string to integer to get the Output Error Code
                outputErrCode = Convert.ToInt32(errorString);

                //Validation to display error message or not
                //If Output message string lenght is greater than zero 
                //and Output error code is 1, Display error message
                if (outputMesgArr.Length > 0 && outputErrCode == 1)
                {
                    ////Empty the strings
                    //tempString = string.Empty;
                    //errorString = string.Empty;
                    //output = string.Empty;

                    ////Get the third last string value from the Output message string array
                    //tempString = outputMesgArr[outputMesgArr.Length - 3];

                    ////Final error output to be displayed on the message box
                    //output = ErrorMessageString(tempString);

                    //Generic message to be displayed
                    output = ApplicationMessageManager.Instance.GetMessage("DATABASE_ERROR_MSG");

                    //Show message popup of the output message
                    MessageBox.Show(output, "Scor", MessageBoxButtons.OK, MessageBoxIcon.Information);
                }

                //Close the form
                Close();
            }
            catch (Exception exObj)
            {
                //TODO: Add proper exception handling and error mechanism
                MessageBox.Show(exObj.Message, "Scor", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }

        //Calls the method when the Cancel button is Clicked
        private void button_Cancel_Click(object sender, EventArgs e)
        {
            //Clicking the Cancel button
            //Close the form
            this.Close();
        }

        //Internal method to format the string
        private string ErrorMessageString(string errString)
        {
            string outputString = string.Empty;

            //Trim the string message
            errString.Trim();

            //Get the error string by removing carriage retun("\r") from the string
            outputString = errString.Replace("\r", string.Empty);

            //Get the error string by removing new line("\n") from the string
            errString = outputString.Replace("\n", string.Empty);

            //Remove the spaces from the error string
            outputString = errString.Trim();

            //Return the formatted string message
            return outputString;

        }  
    }
}
