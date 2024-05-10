<?php
require_once 'utils/config.php';

// Get role and name parameters from GET request
$role = isset($_GET["role"]) ? $_GET["role"] : "";
$name = isset($_GET["name"]) ? $_GET["name"] : "";

// Construct the WHERE clause based on whether role and name are empty or not
$where_clause = "";
if (!empty($role)) {
    $where_clause .= "role LIKE '%" . $role . "%'";
}
if (!empty($name)) {
    $where_clause .= ($where_clause != "") ? " AND " : "";
    $where_clause .= "name LIKE '%" . $name . "%'";
}

// Construct the SQL query
$sql_query = "SELECT * FROM user";
if (!empty($where_clause)) {
    $sql_query .= " WHERE " . $where_clause;
}

global $connection;
$result = mysqli_query($connection, $sql_query);

if ($result) {
    $requested_users = array();
    while ($row = mysqli_fetch_assoc($result)) {
        array_push($requested_users, array(
            'userID' => $row['userID'],
            'name' => $row['name'],
            'username' => $row['username'],
            'age' => $row['age'],
            'role' => $row['role'],
            'email' => $row['email'],
            'webpage' => $row['webpage']
        ));
    }
    mysqli_free_result($result);
    echo json_encode($requested_users);
} else {
    echo "Error executing query: " . mysqli_error($connection);
}

mysqli_close($connection);

