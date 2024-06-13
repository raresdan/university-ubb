package controllers;

import jakarta.servlet.ServletException;
import jakarta.servlet.http.Cookie;
import jakarta.servlet.http.HttpServlet;
import jakarta.servlet.http.HttpServletRequest;
import jakarta.servlet.http.HttpServletResponse;

import java.io.IOException;

public class LoginController extends HttpServlet {
    public LoginController(){ super(); }

    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        response.setContentType("text/html");

        String name = request.getParameter("name");
        String date = request.getParameter("date");
        String city = request.getParameter("city");

        if (name.isEmpty()) {
            request.getSession().setAttribute("error", "Name must not be null!");
            request.getRequestDispatcher("login.jsp").include(request, response);
        } else if (date.isEmpty()) {
            request.getSession().setAttribute("error", "Date must not be null!");
            request.getRequestDispatcher("login.jsp").include(request, response);
        } else if (city.isEmpty()) {
            request.getSession().setAttribute("error", "Destination city must not be null!");
            request.getRequestDispatcher("login.jsp").include(request, response);
        } else {
            response.addCookie(new Cookie("name", name));
            response.addCookie(new Cookie("date", date));
            response.addCookie(new Cookie("city", city));
            response.sendRedirect("main");
        }
    }

    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        response.setContentType("text/html");
        request.getRequestDispatcher("login.jsp").include(request, response);
    }

}
