package controllers;

import domain.DatabaseManager;
import domain.Flights;
import domain.Hotels;
import jakarta.servlet.ServletException;
import jakarta.servlet.http.Cookie;
import jakarta.servlet.http.HttpServlet;
import jakarta.servlet.http.HttpServletRequest;
import jakarta.servlet.http.HttpServletResponse;

import java.io.IOException;
import java.sql.ResultSet;
import java.util.List;
import java.util.Objects;

public class MainController extends HttpServlet {
    private static String name;
    private static String date;
    private static String city;

    public MainController() {
        super();
    }

    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        response.setContentType("text/html");
        for (Cookie c : request.getCookies())
        {
            if(Objects.equals(c.getName(), "name"))
               name = c.getValue();
            if(Objects.equals(c.getName(), "date"))
                date = c.getValue();
            if(Objects.equals(c.getName(), "city"))
                city = c.getValue();
        }
        try{
            List<Flights> flights = DatabaseManager.getFlights(date, city);
           List<Hotels> hotels = DatabaseManager.getHotels(date, city);

            for (Flights flight : flights){
                DatabaseManager.makeReservation(name, "Flight", flight.getFlightId());
            }

            for (Hotels hotel : hotels){
                DatabaseManager.makeReservation(name, "Hotel", hotel.getHotelId());
            }


            request.getSession().setAttribute("flights", flights);
            request.getSession().setAttribute("hotels", hotels);
            request.getRequestDispatcher("main.jsp").include(request, response);
                    return;
                } catch (Exception e) {
                    e.printStackTrace();
                }
                return;
            }

    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String flightId = request.getParameter("flightId");
        String hotelId = request.getParameter("hotelId");
        String name = (String) request.getSession().getAttribute("name");
    try {
        if (flightId != null) {
            DatabaseManager.makeReservation(name, "Flight", Integer.parseInt(flightId));
        } else if (hotelId != null) {
            DatabaseManager.makeReservation(name, "Hotel", Integer.parseInt(hotelId));
        }
    }
    catch (Exception e) {
        e.printStackTrace();
    }
        response.sendRedirect("main");
    }
    }

