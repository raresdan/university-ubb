package domain;

import java.sql.*;
import java.util.ArrayList;
import java.util.List;

public class DatabaseManager {
    // JDBC URL, username, and password of MySQL server
    private static final String JDBC_URL = "jdbc:mysql://localhost:3306/webexam";
    private static final String JDBC_USERNAME = "root";
    private static final String JDBC_PASSWORD = "raresdan20";

    // JDBC variables for opening and managing connection
    private static Connection connection;

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
    public static void closeConnection() throws SQLException {
        if (connection != null && !connection.isClosed()) {
            connection.close();
        }
    }

    // Method to close prepared statement
    public static void closeStatement(PreparedStatement preparedStatement) throws SQLException {
        if (preparedStatement != null && !preparedStatement.isClosed()) {
            preparedStatement.close();
        }
    }

    // Method to close result set
    public static void closeResultSet(ResultSet resultSet) throws SQLException {
        if (resultSet != null && !resultSet.isClosed()) {
            resultSet.close();
        }
    }

    public static List<Flights> getFlights(String date, String destinationCity) throws SQLException {
        if (connection == null || connection.isClosed()) {
            connect();
        }
        List<Flights> flights = new ArrayList<>();
        PreparedStatement preparedStatement = null;
        ResultSet resultSet = null;
        try {
            preparedStatement = connection.prepareStatement("SELECT * FROM Flights WHERE date=? AND destinationCity=?");
            preparedStatement.setString(1, date);
            preparedStatement.setString(2, destinationCity);
            resultSet = preparedStatement.executeQuery();
            while (resultSet.next()) {
                flights.add(new Flights(resultSet.getInt("flightId"), resultSet.getString("date"), resultSet.getString("destinationCity"), resultSet.getInt("availableSeats")));
            }
        } catch (SQLException e) {
            e.printStackTrace();
            throw e;
        }
        return flights;
    }

    public static List<Hotels> getHotels(String date, String destinationCity) throws SQLException {
        if (connection == null || connection.isClosed()) {
            connect();
        }
        List<Hotels> hotels = new ArrayList<>();
        PreparedStatement preparedStatement = null;
        ResultSet resultSet = null;
        try {
            preparedStatement = connection.prepareStatement("SELECT * FROM Hotels WHERE date=? AND city=?");
            preparedStatement.setString(1, date);
            preparedStatement.setString(2, destinationCity);
            resultSet = preparedStatement.executeQuery();
            while (resultSet.next()) {
                hotels.add(new Hotels(resultSet.getInt("hotelId"), resultSet.getString("hotelName"), resultSet.getString("date"), resultSet.getString("city"), resultSet.getInt("availableRooms")));
            }
        } catch (SQLException e) {
            e.printStackTrace();
            throw e;
        }
        return hotels;
    }

    public static void addReservation(String person, String date, String type, int idReservedResource) throws SQLException {
        if (connection == null || connection.isClosed()) {
            connect();
        }
        PreparedStatement preparedStatement = null;
        try {
            preparedStatement = connection.prepareStatement("INSERT INTO Reservations (person, date, type, idReservedResource) VALUES (?, ?, ?, ?)");
            preparedStatement.setString(1, person);
            preparedStatement.setString(2, date);
            preparedStatement.setString(3, type);
            preparedStatement.setInt(4, idReservedResource);
            preparedStatement.executeUpdate();
        } catch (SQLException e) {
            e.printStackTrace();
            throw e;
        } finally {
            closeStatement(preparedStatement);
        }
    }

    //Make reservation
    public static void makeReservation(String person, String type, int idReservedResource) throws SQLException {
        if (connection == null || connection.isClosed()) {
            connect();
        }
        PreparedStatement preparedStatement = null;
        try {
            preparedStatement = connection.prepareStatement("INSERT INTO Reservations (person, type, idReservedResource) VALUES (?, ?, ?)");
            preparedStatement.setString(1, person);
            preparedStatement.setString(2, type);
            preparedStatement.setInt(3, idReservedResource);
            preparedStatement.executeUpdate();
        } catch (SQLException e) {
            e.printStackTrace();
            throw e;
        } finally {
            closeStatement(preparedStatement);
        }
    }

    public static Flights getFlightById(int flightId) throws SQLException {
        if (connection == null || connection.isClosed()) {
            connect();
        }
        PreparedStatement preparedStatement = null;
        ResultSet resultSet = null;
        try {
            preparedStatement = connection.prepareStatement("SELECT * FROM Flights WHERE flightId=?");
            preparedStatement.setInt(1, flightId);
            resultSet = preparedStatement.executeQuery();
            if (resultSet.next()) {
                return new Flights(resultSet.getInt("flightId"), resultSet.getString("date"), resultSet.getString("destinationCity"), resultSet.getInt("availableSeats"));
            }
        } catch (SQLException e) {
            e.printStackTrace();
            throw e;
        } finally {
            closeResultSet(resultSet);
            closeStatement(preparedStatement);
        }
        return null;
    }

    public static Hotels getHotelById(int hotelId) throws SQLException {
        if (connection == null || connection.isClosed()) {
            connect();
        }
        PreparedStatement preparedStatement = null;
        ResultSet resultSet = null;
        try {
            preparedStatement = connection.prepareStatement("SELECT * FROM Hotels WHERE hotelId=?");
            preparedStatement.setInt(1, hotelId);
            resultSet = preparedStatement.executeQuery();
            if (resultSet.next()) {
                return new Hotels(resultSet.getInt("hotelId"), resultSet.getString("hotelName"), resultSet.getString("date"), resultSet.getString("city"), resultSet.getInt("availableRooms"));
            }
        } catch (SQLException e) {
            e.printStackTrace();
            throw e;
        } finally {
            closeResultSet(resultSet);
            closeStatement(preparedStatement);
        }
        return null;
    }
}
