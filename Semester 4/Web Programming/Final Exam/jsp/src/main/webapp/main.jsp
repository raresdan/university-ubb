<%@ page import="java.util.List" %>
<%@ page import="domain.Flights" %>
<%@ page import="domain.Hotels" %>

<%@ page contentType="text/html;charset=UTF-8" %>
<html>
<head>
    <meta charset="UTF-8">
    <title>Reservations | Main Page</title>
    <link rel="stylesheet" href="main.css">
    <script src="jquery-3.6.0.min.js"></script>
    <script src="main.js"></script>
</head>
<body>
<form method="post" action="main.jsp">
    <button type="submit" name="dataType" value="flights">Flights</button>
    <button type="submit" name="dataType" value="hotels">Hotels</button>
</form>

<%
    // Get the dataType parameter to determine which button was pressed
    String dataType = request.getParameter("dataType");

    // Initialize lists to hold flights and hotels data
    List<Flights> flights = (List<Flights>) request.getSession().getAttribute("flights");
    List<Hotels> hotels = (List<Hotels>) request.getSession().getAttribute("hotels");

    if ("hotels".equals(dataType)) {
%>
<ul>
    <%
        if (hotels != null) {
            for (Hotels hotel : hotels) {
    %>
    <li>
        <label><%= hotel.getHotelName() %></label>
        <label><%= hotel.getDate() %></label>
        <label><%= hotel.getCity() %></label>
        <label><%= hotel.getAvailableRooms() %></label>
        <input type="hidden" name="hotelId" value="<%= hotel.getHotelId() %>">
    </li>
    <%
            }
        }
    %>
</ul>
<%
} else if ("flights".equals(dataType)) {
%>
<ul>
    <%
        if (flights != null) {
            for (Flights flight : flights) {
    %>
    <li>
        <label><%= flight.getDate() %></label>
        <label><%= flight.getDestinationCity() %></label>
        <label><%= flight.getAvailableSeats() %></label>
        <input type="hidden" name="flightId" value="<%= flight.getFlightId() %>">
    </li>
    <%
            }
        }
    %>
</ul>
<%
    }
%>

<button type="submit">Make All Reservations</button>

</body>
</html>
