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

namespace WindowsForms
{
    public partial class Form1 : Form
    {
        SqlConnection conn;
        SqlDataAdapter daMembers;
        SqlDataAdapter daTasks;
        DataSet dataSet;
        BindingSource bsMembers;
        BindingSource bsTasks;

        SqlCommandBuilder commandBuilder;

        string queryMembers;
        string queryTasks;
        public Form1()
        {
            InitializeComponent();
            FillData();
        }

        void FillData()
        {
            conn = new SqlConnection(getConnectionString());
            
            queryMembers = "SELECT * FROM StudentMember";
            queryTasks = "SELECT * FROM Task";

            daMembers = new SqlDataAdapter(queryMembers, conn);
            daTasks = new SqlDataAdapter(queryTasks, conn);
            dataSet = new DataSet();
            daMembers.Fill(dataSet, "StudentMember");
            daTasks.Fill(dataSet, "Task");

            commandBuilder = new SqlCommandBuilder(daMembers);
            commandBuilder = new SqlCommandBuilder(daTasks);

            dataSet.Relations.Add("Members_Tasks", dataSet.Tables["StudentMember"].Columns["studentid"], 
                                                 dataSet.Tables["Task"].Columns["assignedTO"]); 

            //METOD 1: fill data into DataGridViews using the properties DataSource and DataMember  
            this.dgvMembers.DataSource = dataSet.Tables["StudentMember"];
            this.dgvTasks.DataSource = this.dgvMembers.DataSource;
            this.dgvTasks.DataMember = "Members_Tasks";
            
            commandBuilder.GetUpdateCommand();
        }

        private string getConnectionString()
        {
            return "Data Source=RARES-DAN\\MSSQLSERVER01;" +
                "Initial Catalog=DBMSPractical;" 
                    + "Integrated Security=True;";
        }

        private void label1_Click(object sender, EventArgs e)
        {

        }

        private void button1_Click(object sender, EventArgs e)
        {
            try
            {
                daMembers.Update(dataSet, "StudentMember");
                daTasks.Update(dataSet, "Task");
            }
            catch (Exception ex)
            {
                MessageBox.Show("An error occurred while updating the database: " + ex.Message, "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }

        private void label2_Click(object sender, EventArgs e)
        {

        }
    }
}
