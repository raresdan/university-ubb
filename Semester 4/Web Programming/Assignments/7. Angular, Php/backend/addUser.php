<?php
require_once "utils/config.php";

if (!isset($_POST['name'], $_POST['username'], $_POST['password'], $_POST['age'], $_POST['role'], $_POST['email'], $_POST['webpage'])) {
    exit('Missing required parameter');
}

$name = $_POST['name'];
$username = $_POST['username'];
$password = $_POST['password'];
$age = $_POST['age'];
$role = $_POST['role'];
$email = $_POST['email'];
$webpage = $_POST['webpage'];

$stmt = $connection->prepare("INSERT INTO user (name, username, password, age, role, email, webpage) VALUES (?, ?, ?, ?, ?, ?, ?)");
$stmt->bind_param("sssisss", $name, $username, $password, $age, $role, $email, $webpage);

$result = $stmt->execute();

if ($result) {
    echo json_encode(['message' => 'User added successfully']);
} else {
    echo json_encode(['error' => 'Missing required parameter']);
}

$stmt->close();
$connection->close();