using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Data;
using System.Data.SqlClient;

namespace ConsoleBased
{
    internal class Program
    {
        static void Main(string[] args)
        {
            string connectionString = "Data Source=RARES-DAN\\MSSQLSERVER01;" + 
                                      "Initial Catalog=SocialMediaApp;" + 
                                      "Integrated Security=True;";
            SqlConnection connection = new SqlConnection(connectionString);
            connection.Open();

            string query = "SELECT * FROM Users";
            SqlCommand command = new SqlCommand(query, connection);
            using (SqlDataReader reader = command.ExecuteReader())
            {
                while (reader.Read())
                {
                    Console.WriteLine("{0} {1}", reader[0], reader[1]);
                }
            }
            //connection.Close();

            //SqlDataAdapter, DataSet
            SqlDataAdapter adapter = new SqlDataAdapter(query, connection);
            DataSet dataSet = new DataSet();
            adapter.Fill(dataSet, "Users");
            foreach (DataRow row in dataSet.Tables["Users"].Rows)
            {
                Console.WriteLine("{0} {1}", row[0], row[1]);
            }
        }
    }
}
