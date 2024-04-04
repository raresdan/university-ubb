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
        SqlDataAdapter daUsers;
        SqlDataAdapter daPosts;
        DataSet dataSet;
        BindingSource bsUsers;
        BindingSource bsPosts;

        SqlCommandBuilder commandBuilder;

        string queryUsers;
        string queryPosts;
        public Form1()
        {
            InitializeComponent();
            FillData();
        }

        void FillData()
        {
            conn = new SqlConnection(getConnectionString());
            
            queryUsers = "SELECT * FROM Users";
            queryPosts = "SELECT * FROM Posts";

            daUsers = new SqlDataAdapter(queryUsers, conn);
            daPosts = new SqlDataAdapter(queryPosts, conn);
            dataSet = new DataSet();
            daUsers.Fill(dataSet, "Users");
            daPosts.Fill(dataSet, "Posts");

            commandBuilder = new SqlCommandBuilder(daUsers);
            commandBuilder = new SqlCommandBuilder(daPosts);

            dataSet.Relations.Add("Users_Posts", dataSet.Tables["Users"].Columns["UserID"], 
                                                 dataSet.Tables["Posts"].Columns["UserID"]); 

            //METOD 1: fill data into DataGridViews using the properties DataSource and DataMember  
            this.dataGridView1.DataSource = dataSet.Tables["Users"];
            this.dataGridView2.DataSource = this.dataGridView1.DataSource;
            this.dataGridView2.DataMember = "Users_Posts";
            
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
                daUsers.Update(dataSet, "Users");
                daPosts.Update(dataSet, "Posts");
            }
            catch (Exception ex)
            {
                MessageBox.Show("An error occurred while updating the database: " + ex.Message, "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }
    }
}
