package domain;

import java.sql.*;
import java.util.ArrayList;
import java.util.List;

public class DatabaseManager {
    // JDBC URL, username, and password of MySQL server
    private static final String JDBC_URL = "jdbc:mysql://localhost:3306/bookmarksweb";
    private static final String JDBC_USERNAME = "root";
    private static final String JDBC_PASSWORD = "raresdan20";

    // JDBC variables for opening and managing connection
    private static Connection connection;
    private static PreparedStatement preparedStatement;
    private static ResultSet resultSet;

    // Method to establish database connection
    public static void connect() throws SQLException {
        try {
            // Load and register MySQL JDBC driver
            Class.forName("com.mysql.cj.jdbc.Driver");

            // Establish connection to MySQL database
            connection = DriverManager.getConnection(JDBC_URL, JDBC_USERNAME, JDBC_PASSWORD);
            System.out.println("Database connection established successfully");
        } catch (ClassNotFoundException e) {
            e.printStackTrace();
        }
    }

    // Method to close database connection
    public static void close() throws SQLException {
        if (connection != null && !connection.isClosed()) {
            connection.close();
        }
        if (preparedStatement != null) {
            preparedStatement.close();
        }
        if (resultSet != null) {
            resultSet.close();
        }
    }

    // Method to authenticate user
    public static User authenticateUser(String username, String password) throws SQLException {
        connect();
        try {
            String query = "SELECT * FROM Users WHERE username=? AND password=?";
            preparedStatement = connection.prepareStatement(query);
            preparedStatement.setString(1, username);
            preparedStatement.setString(2, password);
            resultSet = preparedStatement.executeQuery();

            // return user if exists
            if (resultSet.next()) {
                return new User(resultSet.getInt("user_id"), resultSet.getString("username"), resultSet.getString("password"));
            }
            return null;
        } finally {
            close();
        }
    }

    // Method to add URL for a user
    public static void addURL(Integer user_id, String url) throws SQLException {
        connect();
        try {
            String insertUrlQuery = "INSERT INTO URLs (url, user_id) VALUES (?, ?)";
            preparedStatement = connection.prepareStatement(insertUrlQuery);
            preparedStatement.setString(1, url);
            preparedStatement.setInt(2, user_id);
            preparedStatement.executeUpdate();
        } finally {
            close();
        }
    }

    // Method to delete URL for a user
    public static void deleteURL(int urlId) throws SQLException {
        connect();
        try {
            String deleteUrlQuery = "DELETE FROM URLs WHERE url_id=?";
            preparedStatement = connection.prepareStatement(deleteUrlQuery);
            preparedStatement.setInt(1, urlId);
            preparedStatement.executeUpdate();

        } finally {
            close();
        }
    }

    // Method to retrieve top N most popular URLs
    public static List<Pair<String, Integer>> getTopPopularURLs(int n) throws SQLException {
        connect();
        List<Pair<String, Integer>> urls = new ArrayList<>();
        try {
            String query = "SELECT URLs.url, COUNT(DISTINCT URLs.user_id) AS popularity FROM URLs GROUP BY URLs.url ORDER BY popularity DESC LIMIT ?";
            preparedStatement = connection.prepareStatement(query);
            preparedStatement.setInt(1, n);
            resultSet = preparedStatement.executeQuery();
            while (resultSet.next()) {
                urls.add(new Pair<>(resultSet.getString("url"), resultSet.getInt("popularity")));
            }
            return urls;
        } finally {
            close();
        }
    }

    public List<URL> urlsOfUser(String username) throws SQLException {
        List<URL> urls = new ArrayList<>();
        connect();
        try{
            String getUserIdQuery = "SELECT urls.* FROM Users JOIN URLs ON Users.user_id = URLs.user_id WHERE Users.username=?";
            preparedStatement = connection.prepareStatement(getUserIdQuery);
            preparedStatement.setString(1, username);
            resultSet = preparedStatement.executeQuery();
            while(resultSet.next()){
                urls.add(new URL(resultSet.getInt("url_id"), resultSet.getInt("user_id"), resultSet.getString("url")));
            }
        } finally {
            close();
        }
        return urls;
    }

    public User getUserFromName(String username) throws SQLException {
        connect();
        try {
            String query = "SELECT * FROM Users WHERE username=?";
            preparedStatement = connection.prepareStatement(query);
            preparedStatement.setString(1, username);
            resultSet = preparedStatement.executeQuery();
            if (resultSet.next()) {
                return new User(resultSet.getInt("user_id"), resultSet.getString("username"), resultSet.getString("password"));
            }
            return null;
        } finally {
            close();
        }
    }
}
