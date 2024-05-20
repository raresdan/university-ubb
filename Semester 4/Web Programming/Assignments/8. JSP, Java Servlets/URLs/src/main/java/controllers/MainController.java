package controllers;

import domain.DatabaseManager;
import domain.URL;
import domain.User;
import jakarta.servlet.ServletException;
import jakarta.servlet.http.Cookie;
import jakarta.servlet.http.HttpServlet;
import jakarta.servlet.http.HttpServletRequest;
import jakarta.servlet.http.HttpServletResponse;

import java.io.IOException;
import java.util.List;

public class MainController extends HttpServlet {
    public MainController() {
        super();
    }

    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        response.setContentType("text/html");
        for (Cookie c : request.getCookies())
            if (c.getName().equals("user")) {
                try{
                    User user = (new DatabaseManager()).getUserFromName(c.getValue());
                    List<URL> urls = (new DatabaseManager()).urlsOfUser(c.getValue());
                    request.getSession().setAttribute("urls", urls);
                    request.getSession().setAttribute("user", user);
                    request.getRequestDispatcher("main.jsp").include(request, response);
                    return;
                } catch (Exception e) {
                    e.printStackTrace();
                }
                return;
            }
        response.getWriter().println("Invalid request");
    }
}
