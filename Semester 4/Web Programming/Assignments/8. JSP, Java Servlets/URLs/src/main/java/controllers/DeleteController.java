package controllers;

import domain.DatabaseManager;
import jakarta.servlet.http.HttpServlet;
import jakarta.servlet.http.HttpServletRequest;
import jakarta.servlet.http.HttpServletResponse;

import java.sql.SQLException;

public class DeleteController extends HttpServlet {
    public DeleteController() {
        super();
    }

    @Override
    protected void doPost(HttpServletRequest req, HttpServletResponse resp) {
        try {
            DatabaseManager.deleteURL(Integer.parseInt(req.getParameter("url_id")));
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }
}
