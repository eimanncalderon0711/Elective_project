<?php
// Database connection settings
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

// Initialize response variables
$statusMessage = "No RFID data received";
$rfid = "";

// Get RFID data from GET request
if (isset($_GET['rfid'])) {
    $rfid = trim($_GET['rfid']); // Get the RFID value from query parameter

    // Check if RFID exists in the database
    $sql = "SELECT status FROM rfid_data WHERE rfid = ?";
    $stmt = $conn->prepare($sql);
    $stmt->bind_param("s", $rfid);
    $stmt->execute();
    $stmt->store_result();

    if ($stmt->num_rows > 0) {
        // RFID found, get the status
        $stmt->bind_result($status);
        $stmt->fetch();

        // Toggle status between 0 and 1
        $newStatus = ($status == 0) ? 1 : 0;

        // Update status in the database
        $updateSql = "UPDATE rfid_data SET status = ? WHERE rfid = ?";
        $updateStmt = $conn->prepare($updateSql);
        $updateStmt->bind_param("is", $newStatus, $rfid);
        $updateStmt->execute();
        $updateStmt->close();

        // Prepare status message for frontend
        $statusMessage = "RFID Found - Status updated to: $newStatus";
    } else {
        // RFID not found, do not insert
        $statusMessage = "RFID Not Found - No record updated";
    }
    $stmt->close();
}

// Close the database connection
$conn->close();
?>

<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>RFID Status</title>
    <script>

    </script>
    <style>

        /* Basic styling */
        .status-message {
            font-size: 18px;
            font-family: Arial, sans-serif;
            padding: 10px;
            margin-top: 20px;
            border: 1px solid #ccc;
        }
        .status-found {
            color: green;
        }
        .status-not-found {
            color: red;
        }
    </style>
</head>
<body>

    <div class="container">
        <h1>RFID Status Display</h1>
        <div class="status-message <?php echo ($statusMessage == 'RFID Not Found - No record updated') ? 'status-not-found' : 'status-found'; ?>">
            <?php echo "RFID Tag: $rfid - $statusMessage"; ?>   
        </div>
        <button class="btn-refresh" onclick="location.reload();">Refresh</button>
    </div>

</body>
</html>
