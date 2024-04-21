<?php
require_once "../utils/config.php";
global $connection;
if (isset($_GET['id']) && !empty(trim($_GET['id']))) {
    $id = trim($_GET['id']);
    $stmt = $connection->prepare("DELETE FROM user WHERE userID = ?");
$stmt->bind_param("i", $id);
if ($stmt->execute()) {
    if ($stmt->affected_rows > 0) {
        echo "Your user was deleted successfully!";
        header("Location: ../index.html");
        ob_end_flush();
    } else {
        echo "No user with that ID found.";
        exit();
    }
} else {
    echo "Oops! Something went wrong: " . $stmt->error;
    exit();
}
$stmt->close();
}
$connection->close();