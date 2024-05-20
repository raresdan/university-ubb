<%@ page import="java.util.List" %>
<%@ page import="domain.Pair" %>
<%@ page contentType="text/html;charset=UTF-8" %>
<html>
<head>
    <meta charset="UTF-8">
    <title>MyURLs | Most Popular</title>
    <link rel="stylesheet" href="popular.css">
    <script src="jquery-3.6.0.min.js"></script>
    <script src="main.js"></script>
</head>
<body>
<div class="wrapper">
    <table>
        <tr>
            <th>URL</th>
            <th>COUNTS</th>
        </tr>
        <%
            List<Pair<String, Integer>> urls = (List<Pair<String, Integer>>) request.getSession().getAttribute("urls");
            for (Pair<String, Integer> pair : urls) {
        %>
        <tr>
            <td class="first_column">
                <p <%= pair.getFirst() %>><%= pair.getFirst() %></p>
            </td>
            <td class="second_column">
                <%= pair.getSecond() %>
            </td>
        </tr>
        <%
            }
        %>
    </table>
</div>
</body>
</html>
