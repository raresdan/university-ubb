using backend.Models;
using MySql.Data.MySqlClient;
using System.Diagnostics;

namespace backend.Data_Abstraction_Layer
{
    public class DataAbstractionLayer
    {
        private MySqlConnection connection;
        private string mySQLConnectionString = "server=localhost;uid=root;pwd=raresdan20;database=enterpriseweb;";

        public List<User> GetUsers()
        {
            List<User> userList = new List<User>();

            try
            {
                connection = new MySqlConnection
                {
                    ConnectionString = this.mySQLConnectionString
                };
                connection.Open();

                MySqlCommand cmd = new MySqlCommand
                {
                    Connection = connection,
                    CommandText = "SELECT * FROM user"
                };
                MySqlDataReader myreader = cmd.ExecuteReader();

                while (myreader.Read())
                {
                    User user = new()
                    {
                        userID = myreader.GetInt32("userID"),
                        name = myreader.GetString("name"),
                        username = myreader.GetString("username"),
                        password = myreader.GetString("password"),
                        age = myreader.GetInt32("age"),
                        role = myreader.GetString("role"),
                        email = myreader.GetString("email"),
                        webpage = myreader.GetString("webpage")
                    };
                    userList.Add(user);
                }
                myreader.Close();
            }
            catch (MySqlException ex)
            {
                Console.Write(ex.Message);
            }
            return userList;
        }

        public void addUser(User user)
        {

            try
            {
                connection = new MySqlConnection
                {
                    ConnectionString = this.mySQLConnectionString
                };
                connection.Open();

                MySqlCommand cmd = new MySqlCommand
                {
                    Connection = connection,
                    CommandText = "INSERT INTO user(name, username, password, age, role, email, webpage) values ('" + user.name + "', '" + user.username + "', '" + user.password + "', " + user.age + ", '" + user.role + "', '" + user.email + "', '" + user.webpage + "')"
                };
                cmd.ExecuteNonQuery();
            }
            catch (MySqlException ex)
            {
                System.Diagnostics.Debug.WriteLine(ex.Message);
            }
        }

        public void deleteUser(int id)
        {

            try
            {
                connection = new MySqlConnection
                {
                    ConnectionString = this.mySQLConnectionString
                };
                connection.Open();

                MySqlCommand cmd = new MySqlCommand
                {
                    Connection = connection,
                    CommandText = "DELETE FROM user WHERE userID = " + id
                };
                cmd.ExecuteNonQuery();
            }
            catch (MySqlException ex)
            {
                System.Diagnostics.Debug.WriteLine(ex.Message);
            }
        }

        public void updateUser(User user)
        {

            try
            {
                connection = new MySqlConnection
                {
                    ConnectionString = this.mySQLConnectionString
                };
                connection.Open();

                MySqlCommand cmd = new()
                {
                    Connection = connection,
                    CommandText = "UPDATE user SET name='" + user.name + "', username = '" + user.username + "', password = '" + user.password + "', age = " + user.age + ", role = '" + user.role + "', email = '" + user.email + "', webpage = '" + user.webpage + "' WHERE userID = " + user.userID
                };
                Debug.WriteLine(cmd.CommandText);
                cmd.ExecuteNonQuery();
            }
            catch (MySqlException ex)
            {
                System.Diagnostics.Debug.WriteLine(ex.Message);
            }
        }

        public User getUserByUsername(string username)
        {
            if (username == null)
                return null;
            List<User> users = GetUsers();
            foreach (User user in users)
                if (user.username == username)
                    return user;
            return null;
        }

        public User getUserByRole(string role)
        {
            if (role == null)
                return null;
            List<User> users = GetUsers();
            foreach (User user in users)
                if (user.role == role)
                    return user;
            return null;
        }
    }
}
