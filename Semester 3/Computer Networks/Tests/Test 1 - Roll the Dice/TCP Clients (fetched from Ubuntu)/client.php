<?php

$serverHost = 'http://192.168.0.103:12345';  // Update with the server's IP and port
$httpClient = curl_init();

// Make an HTTP GET request to start the game
curl_setopt($httpClient, CURLOPT_URL, $serverHost);
curl_setopt($httpClient, CURLOPT_RETURNTRANSFER, true);

$response = curl_exec($httpClient);
echo $response;

if (strpos($response, "The game is starting") === false) {
    echo "Failed to connect to the server. Make sure the server is running.";
    exit(1);
}

while (true) {
    // Simulate player's input (you can replace these with user input)
    $prediction = "H"; // Replace with user input
    $playAgain = "Y";  // Replace with user input

    // Make an HTTP POST request to send the prediction
    curl_setopt($httpClient, CURLOPT_URL, $serverHost);
    curl_setopt($httpClient, CURLOPT_POST, true);
    curl_setopt($httpClient, CURLOPT_POSTFIELDS, http_build_query(['prediction' => $prediction]));

    $response = curl_exec($httpClient);
    echo $response;

    // Check for the "Game over" message
    if (strpos($response, "Game over") !== false) {
        break;
    }

    // Make an HTTP POST request to send the play again choice
    curl_setopt($httpClient, CURLOPT_URL, $serverHost);
    curl_setopt($httpClient, CURLOPT_POST, true);
    curl_setopt($httpClient, CURLOPT_POSTFIELDS, http_build_query(['play_again' => $playAgain]));

    $response = curl_exec($httpClient);
    echo $response;

    // Check for the "Game over" message
    if (strpos($response, "Game over") !== false) {
        break;
    }
}

curl_close($httpClient);

?>
