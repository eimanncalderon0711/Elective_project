<?php

header('Content-Type: application/json');
header('Access-Control-Allow-Origin: *');

$servername = "localhost";
$username = "root";
$password = "";
$dbname = "rfid_db";

// Create connection
$conn = new mysqli($servername, $username, $password, $dbname);

// Check connection
if ($conn->connect_error) {
    die("Connection failed: " . $conn->connect_error);
}

$rfid = isset($_GET['rfid']) ? $_GET['rfid'] : '';

if (!empty($rfid)) {
    // Prepare the SQL statement
    $sql = "SELECT * FROM rfid_data WHERE rfid = ?";
    $stmt = $conn->prepare($sql);
    
    if ($stmt) {
        // Bind the RFID parameter to the query
        $stmt->bind_param("s", $rfid);
        
        // Execute the query
        $stmt->execute();
        
        // Get the result
        $result = $stmt->get_result();
        $user = $result->fetch_assoc();
        
        // Close the statement
        $stmt->close();
        
        // Output the result as JSON
        echo json_encode($user);
    } else {
        echo json_encode(["error" => "Failed to prepare SQL statement."]);
    }
} else {
    echo json_encode(["error" => "No RFID provided."]);
}

// Close the connection
$conn->close();
?>
