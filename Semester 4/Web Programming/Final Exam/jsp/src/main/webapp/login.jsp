<%@ page contentType="text/html;charset=UTF-8" %>
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>Reservations | Login</title>
    <link rel="stylesheet" href="login.css">
    <script src="jquery-3.6.0.min.js"></script>
    <script src="login.js"></script>
</head>
<body>
<div class="wrapper">
    <h1> Welcome to <em>Reservations</em>! </h1>
    <h5> Please input the following details before your browse! </h5>
    <%--suppress HtmlUnknownTarget --%>
    <form action="login" method="post">
        <label>
            <input type="text" name="name" placeholder="Name:" autocomplete="off">
        </label>
        <label>
            <input type="date" name="date" placeholder="Date: " autocomplete="off">
        </label>
        <label>
            <input type="text" name="city" placeholder="Destination City: " autocomplete="off">
        </label>
        <%
            String err = (String) session.getAttribute("error");
            if (err != null) {
        %>
        <p><%= err %></p>
        <%
            }
        %>
        <div id="buttons">
            <button type="submit">Begin Reservation</button>
        </div>
    </form>
</div>
</body>
</html>
