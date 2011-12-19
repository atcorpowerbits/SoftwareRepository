/*
     Copyright (C) ATCOR MEDICAL PTY LTD, 2010
 
     Filename     :     Report Window
        
     Author       :     Nitesh Chhedda
 
     Description  :     Functionality implemented for BPAssessment Dialog.
*/
using System;
using System.Data;
using System.Drawing;
using Telerik.WinControls;
using Telerik.WinControls.UI;
using AtCor.Scor.CrossCutting.Configuration;

/**
 * @namespace AtCor.Scor.Gui.Presentation
 * @brief This namespace implements Presentation related classes.
 * 
 */
namespace AtCor.Scor.Gui.Presentation
{
    /**
    * @class BPAssessment
    * @brief This class will handle displaying of the default window controls.It will also check for multiple instances of the application,exception handling and logging of events.
    */
    public partial class BPAssessments : RadForm
    {
        CrxConfigManager crxMgrObject;

        public BPAssessments()
        {
            InitializeComponent();
            crxMgrObject = CrxConfigManager.Instance;
        }

        /** This event load BP Assessment Form
        **/
        private void BPAssessments_Load(object sender, EventArgs e)
        {
            CreateDummyRecords();
        }

        /** This method is used to populate Dummy Records on the gridview. These values are hardcoded for representation
         * purpose only. Those shall be removed further.
         * */
        private void CreateDummyRecords()
        {
            guiradgrdAssessmentsDetails.Columns.Clear();
            guiradgrdAssessmentsDetails.TableElement.BeginUpdate();
            guiradgrdAssessmentsDetails.Columns.Add("BP Data", "BP Data", "BP Data");
            guiradgrdAssessmentsDetails.Columns[0].Width = 130;
            guiradgrdAssessmentsDetails.Columns[0].IsVisible = true;

            guiradgrdAssessmentsDetails.Columns.Add("SYS", "SYS", "SYS");
            guiradgrdAssessmentsDetails.Columns[1].Width = 40;
            guiradgrdAssessmentsDetails.Columns[1].IsVisible = true;

            guiradgrdAssessmentsDetails.Columns.Add("PP", "PP", "PP");
            guiradgrdAssessmentsDetails.Columns[2].Width = 40;
            guiradgrdAssessmentsDetails.Columns[2].IsVisible = true;

            guiradgrdAssessmentsDetails.Columns.Add("MAP", "MAP", "MAP");
            guiradgrdAssessmentsDetails.Columns[3].Width = 40;
            guiradgrdAssessmentsDetails.Columns[3].IsVisible = true;

            guiradgrdAssessmentsDetails.Columns.Add("DIA", "DIA", "DIA");
            guiradgrdAssessmentsDetails.Columns[4].Width = 40;
            guiradgrdAssessmentsDetails.Columns[4].IsVisible = true;

            guiradgrdAssessmentsDetails.TableElement.EndUpdate();
            guiradgrdAssessmentsDetails.AutoGenerateColumns = false;

            DataTable dummyTable = new DataTable("DummyTable");

            DataColumn bpDataOne = new DataColumn("BP Data");
            bpDataOne.DataType = Type.GetType("System.String");
            dummyTable.Columns.Add(bpDataOne);

            DataColumn bpDataTwo = new DataColumn("SYS");
            bpDataTwo.DataType = Type.GetType("System.String");
            dummyTable.Columns.Add(bpDataTwo);

            DataColumn bpDataThree = new DataColumn("PP");
            bpDataThree.DataType = Type.GetType("System.String");
            dummyTable.Columns.Add(bpDataThree);

            DataColumn bpDataFour = new DataColumn("MAP");
            bpDataFour.DataType = Type.GetType("System.String");
            dummyTable.Columns.Add(bpDataFour);

            DataColumn bpDataFive = new DataColumn("DIA");
            bpDataFive.DataType = Type.GetType("System.String");
            dummyTable.Columns.Add(bpDataFive);

            DataRow cellone;
            DataRow celltwo;
            DataRow cellthree;
            DataRow cellfour;
            DataRow cellfive;

            cellone = dummyTable.NewRow();
            cellone["BP Data"] = "Assessment 1";
            cellone["SYS"] = "140";
            cellone["PP"] = "60";
            cellone["MAP"] = "110";
            cellone["DIA"] = "80";
            dummyTable.Rows.Add(cellone);

            celltwo = dummyTable.NewRow();
            celltwo["BP Data"] = "Assessment 2";
            celltwo["SYS"] = "155";
            celltwo["PP"] = "50";
            celltwo["MAP"] = "150";
            celltwo["DIA"] = "90";
            dummyTable.Rows.Add(celltwo);

            cellthree = dummyTable.NewRow();
            cellthree["BP Data"] = "Assessment 3";
            cellthree["SYS"] = "140";
            cellthree["PP"] = "70";
            cellthree["MAP"] = "140";
            cellthree["DIA"] = "70";
            dummyTable.Rows.Add(cellthree);

            cellfour = dummyTable.NewRow();
            cellfour["BP Data"] = "Assessment 4";
            cellfour["SYS"] = "155";
            cellfour["PP"] = "70";
            cellfour["MAP"] = "120";
            cellfour["DIA"] = "90";
            dummyTable.Rows.Add(cellfour);

            cellfive = dummyTable.NewRow();
            cellfive["BP Data"] = "Assessment 5";
            cellfive["SYS"] = "160";
            cellfive["PP"] = "70";
            cellfive["MAP"] = "130";
            cellfive["DIA"] = "85";
            dummyTable.Rows.Add(cellfive);
            guiradgrdAssessmentsDetails.DataSource = dummyTable;

            // guiradgrdAssessmentsDetails.Columns[0].Width = 50;
            int counter = crxMgrObject.BpSettings.NumberofAssessments;

            if (counter == 1)
            {
                dummyTable.Rows.Remove(cellfive);
                dummyTable.Rows.Remove(cellfour);
                dummyTable.Rows.Remove(cellthree);
                dummyTable.Rows.Remove(celltwo);
                guiradgrdAssessmentsDetails.DataSource = dummyTable;
            }
            else if (counter == 2)
            {
                dummyTable.Rows.Remove(cellfive);
                dummyTable.Rows.Remove(cellfour);
                dummyTable.Rows.Remove(cellthree);
                guiradgrdAssessmentsDetails.DataSource = dummyTable;
            }
            else if (counter == 3)
            {
                dummyTable.Rows.Remove(cellfive);
                dummyTable.Rows.Remove(cellfour);
                guiradgrdAssessmentsDetails.DataSource = dummyTable;
            }
            else if (counter == 4)
            {
                dummyTable.Rows.Remove(cellfive);
                guiradgrdAssessmentsDetails.DataSource = dummyTable;
            }
            else if (counter == 5)
            {
                guiradgrdAssessmentsDetails.DataSource = dummyTable;
            }
        }
        
        /** To change the color of selected row.Also to implement color for alternating rows in the grid.
               */
        private void guiradgrdAssessmentsDetails_RowFormatting(object sender, RowFormattingEventArgs e)
        {
            GridRowElement row = e.RowElement as GridRowElement;
            if (row != null)
            {
                if (row.IsCurrent)
                {
                    // row fill
                    row.DrawFill = true;
                    row.GradientStyle = GradientStyles.Solid;

                    row.BackColor = Color.FromArgb(172, 177, 204);

                    // row border
                    row.DrawBorder = true;
                    row.BorderBoxStyle = BorderBoxStyle.SingleBorder;
                    row.BorderColor = Color.Red;
                }
                else if (row.IsOdd)
                {
                    row.DrawFill = true;
                    row.GradientStyle = GradientStyles.Solid;
                    row.BackColor = Color.LightGray;
                }
                else
                {
                    row.ResetValue(LightVisualElement.DrawFillProperty, ValueResetFlags.Local);
                    row.ResetValue(LightVisualElement.GradientStyleProperty, ValueResetFlags.Local);
                    row.ResetValue(LightVisualElement.BackColorProperty, ValueResetFlags.Local);
                    row.ResetValue(LightVisualElement.DrawBorderProperty, ValueResetFlags.Local);
                    row.ResetValue(LightVisualElement.BorderBoxStyleProperty, ValueResetFlags.Local);
                    row.ResetValue(LightVisualElement.BorderColorProperty, ValueResetFlags.Local);
                }
            }
        }
    }
}
