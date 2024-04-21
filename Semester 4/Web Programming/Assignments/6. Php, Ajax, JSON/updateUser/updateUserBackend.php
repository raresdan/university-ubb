<?php
require_once "../utils/config.php";
$userID = $_POST['id'];
$name = $_POST['name'];
$username = $_POST['username'];
$password = $_POST['password'];
$age = $_POST['age'];
$role = $_POST['role'];
$email = $_POST['email'];
$webpage = $_POST['webpage'];

global $connection;

$sql_query = "UPDATE user SET name=?, username=?, password=?, age=?, role=?, email=?, webpage=? WHERE userID=?";
$stmt = mysqli_prepare($connection, $sql_query);

mysqli_stmt_bind_param($stmt, "sssisssi", $name, $username, $password, $age, $role, $email, $webpage, $userID);

if (mysqli_stmt_execute($stmt)) {
    echo "Your user was updated successfully!";
    header("Location: ../index.html");
} else {
    echo "Oops! Something went wrong and your document cannot be added! Please try again later.";
}

mysqli_stmt_close($stmt);
mysqli_close($connection);