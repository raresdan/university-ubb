<?php
require_once "../utils/config.php";
global $connection;
$id = "";
$name = "";
$username = "";
$password = "";
$age = "";
$role = "";
$email = "";
$webpage = "";
if (isset($_GET['id']) && !empty(trim($_GET['id']))) {
    $id = trim($_GET['id']);
    $sql_query = "SELECT * FROM user WHERE userID = ?";
    if ($stmt = mysqli_prepare($connection, $sql_query)) {
        mysqli_stmt_bind_param($stmt, "i", $param_id);
        $param_id = $id;
        if (mysqli_stmt_execute($stmt)) {
            $result = mysqli_stmt_get_result($stmt);
            if (mysqli_num_rows($result) == 1) {
            $row = mysqli_fetch_array($result);
            $name = $row['name'];
            $username = $row['username'];
            $password = $row['password'];
            $age = $row['age'];
            $role = $row['role'];
            $email = $row['email'];
            $webpage = $row['webpage'];
            $user = array(
                "name" => $name,
                "username" => $username,
                "password" => $password,
                "age" => $age,
                "role" => $role,
                "email" => $email,
                "webpage" => $webpage
            );
            echo json_encode($user);
        } else {
            echo json_encode(new stdClass());
            echo "Error: No user found with this ID.";
        }
    } else {
        echo "Error: Could not execute SQL statement.";
    }
} else {
    echo "Error: Could not prepare SQL statement.";
}
mysqli_stmt_close($stmt);
}
mysqli_close($connection);