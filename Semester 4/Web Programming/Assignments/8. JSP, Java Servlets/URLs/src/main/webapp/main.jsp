<%@ page import="domain.URL" %>
<%@ page import="java.util.List" %>
<%@ page import="domain.User" %>
<%@ page contentType="text/html;charset=UTF-8" %>
<html>
<head>
    <meta charset="UTF-8">
    <title>MyURLs | Main Page</title>
    <link rel="stylesheet" href="main.css">
    <script src="jquery-3.6.0.min.js"></script>
    <script src="main.js"></script>
</head>
<body>
<div class="wrapper">
    <div class="topWrapper">
        <% User user = (User) request.getSession().getAttribute("user"); %>
        <h3>Hi, <%= user.getUsername() %>!</h3>
        <button onclick="logout()">Logout</button>
    </div>
    <label>
        <input type="number" id="cntText" placeholder="Count:">
        <button onclick="nav()">URLs</button>
    </label>
    <label>
        <input type="text" id="urlText" placeholder="New url:">
        <button onclick="add(<%= user.getId() %>)">Add</button>
    </label>
    <%
        String err = (String) session.getAttribute("error");
        if (err != null) {
    %>
    <p><%= err %></p>
    <%
            session.removeAttribute("error");
        }
    %>
    <p id="errorMsg">
        Invalid url! Try another one
    </p>
    <ul>
        <%
            //noinspection unchecked
            List<URL> urls = (List<URL>) request.getSession().getAttribute("urls");
            for (URL url : urls) {
        %>
        <li>
            <a href="<%= url.getUrl() %>"><%= url.getUrl() %></a>
            <button onclick="del(<%= url.getId() %>)">Delete</button>
        </li>
        <%
            }
        %>
    </ul>
</div>
</body>
</html>
