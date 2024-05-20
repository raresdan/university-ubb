package controllers;

import domain.DatabaseManager;
import domain.User;
import jakarta.servlet.ServletException;
import jakarta.servlet.http.Cookie;
import jakarta.servlet.http.HttpServlet;
import jakarta.servlet.http.HttpServletRequest;
import jakarta.servlet.http.HttpServletResponse;

import java.io.IOException;
import java.sql.SQLException;

public class LoginController extends HttpServlet {
    public LoginController() {
        super();
    }

    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        response.setContentType("text/html");

        String username = request.getParameter("username");
        String password = request.getParameter("password");

        if (username.equals("")) {
            request.getSession().setAttribute("error", "Username must not be null!");
            request.getRequestDispatcher("login.jsp").include(request, response);
        } else if (password.isEmpty()) {
            request.getSession().setAttribute("error", "Password must not be null!");
            request.getRequestDispatcher("login.jsp").include(request, response);
        } else {
            User user = null;
            try {
                user = DatabaseManager.authenticateUser(username, password);
            } catch (SQLException e) {
                e.printStackTrace();
            }
            if (user != null) {
                response.addCookie(new Cookie("user", user.getUsername()));
                response.sendRedirect("main");
            } else {
                request.getSession().setAttribute("error", "Username or password invalid!");
                request.getRequestDispatcher("login.jsp").include(request, response);
            }
        }
    }

    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        response.setContentType("text/html");
        request.getRequestDispatcher("login.jsp").include(request, response);
    }
}
