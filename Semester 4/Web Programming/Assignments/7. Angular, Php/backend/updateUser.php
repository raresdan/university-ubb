<?php
require_once "utils/config.php";

if ($_SERVER["REQUEST_METHOD"] === "POST") {
    $userID = isset($_POST['id']) ? $_POST['id'] : '';
    $name = isset($_POST['name']) ? $_POST['name'] : '';
    $username = isset($_POST['username']) ? $_POST['username'] : '';
    $password = isset($_POST['password']) ? $_POST['password'] : '';
    $age = isset($_POST['age']) ? $_POST['age'] : '';
    $role = isset($_POST['role']) ? $_POST['role'] : '';
    $email = isset($_POST['email']) ? $_POST['email'] : '';
    $webpage = isset($_POST['webpage']) ? $_POST['webpage'] : '';

    $sql_query = "UPDATE user SET name=?, username=?, password=?, age=?, role=?, email=?, webpage=? WHERE userID=?";
    if ($stmt = mysqli_prepare($connection, $sql_query)) {

        mysqli_stmt_bind_param($stmt, "sssisssi", $name, $username, $password, $age, $role, $email, $webpage, $userID);
        if (mysqli_stmt_execute($stmt)) {
            echo json_encode(["message" => "User updated successfully"]);
        } else {
            echo "Failed to execute query: " . mysqli_error($connection);
        }
        mysqli_stmt_close($stmt);
    } else {
        echo "Failed to prepare query: " . mysqli_error($connection);
    }
    mysqli_close($connection);
} else {
    echo json_encode(["error" => "Invalid request method"]);
}

