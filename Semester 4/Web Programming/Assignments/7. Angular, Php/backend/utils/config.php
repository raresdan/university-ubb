<?php
header("Access-Control-Allow-Origin: http://localhost:4200");
header("Access-Control-Allow-Methods: GET, POST, PUT, DELETE, OPTIONS");
header("Access-Control-Allow-Headers: Content-Type, Authorization");


$servername = "localhost";
$username = "root";
$password = "raresdan20";
$dbname = "EnterpriseWeb";

$connection = new mysqli($servername, $username, $password, $dbname);


if ($connection->connect_error) {
    die("Connection failed: " . $connection->connect_error);
}