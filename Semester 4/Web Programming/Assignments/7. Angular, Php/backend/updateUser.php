<?php
require_once "utils/config.php";

$userID = isset($_POST['id']) ? $_POST['id'] : '';
$name = isset($_POST['name']) ? $_POST['name'] : '';
$username = isset($_POST['username']) ? $_POST['username'] : '';
$password = isset($_POST['password']) ? $_POST['password'] : '';
$age = isset($_POST['age']) ? $_POST['age'] : '';
$role = isset($_POST['role']) ? $_POST['role'] : '';
$email = isset($_POST['email']) ? $_POST['email'] : '';
$webpage = isset($_POST['webpage']) ? $_POST['webpage'] : '';

global $connection;

$sql_query = "UPDATE user SET name=?, username=?, password=?, age=?, role=?, email=?, webpage=? WHERE userID=?";
$stmt = mysqli_prepare($connection, $sql_query);

if ($stmt === false) {
    echo json_encode(['error' => 'Failed to prepare statement: ' . mysqli_error($connection)]);
    exit;
}

$bind_result = mysqli_stmt_bind_param($stmt, "sssisssi", $name, $username, $password, $age, $role, $email, $webpage, $userID);

if ($bind_result === false) {
    echo json_encode(['error' => 'Failed to bind parameters: ' . mysqli_stmt_error($stmt)]);
    exit;
}

if (mysqli_stmt_execute($stmt)) {
    echo json_encode(['message' => 'User updated successfully']);
} else {
    echo json_encode(['error' => 'An error occurred while updating the user: ' . mysqli_stmt_error($stmt)]);
}

mysqli_stmt_close($stmt);
mysqli_close($connection);