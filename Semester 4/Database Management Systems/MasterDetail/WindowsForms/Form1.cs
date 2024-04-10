using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Data.SqlClient;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Configuration;

namespace WindowsForms
{
    public partial class Form1 : Form
    {
        SqlConnection connectionString;
        SqlDataAdapter daMaster;
        SqlDataAdapter daDetail;
        DataSet dataSet;
        BindingSource bsUsers;
        BindingSource bsPosts;

        SqlCommandBuilder commandBuilder;

        string queryMaster;
        string queryDetail;

        string masterTableName;
        string detailTableName;
        string foreignKey;
        string scenarioName;

        public Form1()
        {
            InitializeComponent();
            FillData();
        }

        void FillData()
        {
            scenarioName = ConfigurationManager.AppSettings["SelectedScenario"];
            masterTableName = ConfigurationManager.AppSettings[$"{scenarioName}_MasterTable"];
            detailTableName = ConfigurationManager.AppSettings[$"{scenarioName}_DetailTable"];
            foreignKey = ConfigurationManager.AppSettings[$"{scenarioName}_ForeignKey"];


            connectionString = new SqlConnection(getConnectionString());
            
            queryMaster = $"SELECT * FROM {masterTableName}";
            queryDetail = $"SELECT * FROM {detailTableName}";

            daMaster = new SqlDataAdapter(queryMaster, connectionString);
            daDetail = new SqlDataAdapter(queryDetail, connectionString);
            dataSet = new DataSet();
            daMaster.Fill(dataSet, masterTableName);
            daDetail.Fill(dataSet, detailTableName);

            commandBuilder = new SqlCommandBuilder(daMaster);
            commandBuilder = new SqlCommandBuilder(daDetail);

            dataSet.Relations.Add($"{masterTableName}_{detailTableName}",
                                  dataSet.Tables[masterTableName].Columns[foreignKey],
                                  dataSet.Tables[detailTableName].Columns[foreignKey]);

            //METHOD 1: fill data into DataGridViews using the properties DataSource and DataMember  
            this.dataGridView1.DataSource = dataSet.Tables[masterTableName];
            this.dataGridView2.DataSource = this.dataGridView1.DataSource;
            this.dataGridView2.DataMember = $"{masterTableName}_{detailTableName}";


            commandBuilder.GetUpdateCommand();
        }

        private string getConnectionString()
        {
            return "Data Source=RARES-DAN\\MSSQLSERVER01;" +
                "Initial Catalog=SocialMediaApp;" 
                    + "Integrated Security=True;";
        }

        private void label1_Click(object sender, EventArgs e)
        {

        }

        private void button1_Click(object sender, EventArgs e)
        {
            try
            {
                daMaster.Update(dataSet, masterTableName);
                daDetail.Update(dataSet, detailTableName);
            }
            catch (Exception ex)
            {
                MessageBox.Show("An error occurred while updating the database: " + ex.Message, "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }
    }
}
