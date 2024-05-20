package controllers;

import domain.DatabaseManager;
import domain.Pair;
import jakarta.servlet.ServletException;
import jakarta.servlet.http.Cookie;
import jakarta.servlet.http.HttpServlet;
import jakarta.servlet.http.HttpServletRequest;
import jakarta.servlet.http.HttpServletResponse;

import java.io.IOException;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.ArrayList;
import java.util.List;

public class PopularController extends HttpServlet {
    public PopularController() {
        super();
    }

    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        response.setContentType("text/html");
        int howMany = 10;
        for (Cookie c : request.getCookies())
            if (c.getName().equals("howMany"))
                howMany = Integer.parseInt(c.getValue());
        List<Pair<String, Integer>> urls = new ArrayList<>();
        try {
            urls = DatabaseManager.getTopPopularURLs(howMany);
        } catch (SQLException e) {
            e.printStackTrace();
        }
        request.getSession().setAttribute("urls", urls);
        request.getRequestDispatcher("popular.jsp").include(request, response);
    }
}
