<?php

$servername = "localhost";
$username = "root";
$password = "raresdan20";
$dbname = "EnterpriseWeb";

$connection = new mysqli($servername, $username, $password, $dbname);


if ($connection->connect_error) {
    die("Connection failed: " . $connection->connect_error);
}