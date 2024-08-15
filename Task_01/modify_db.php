<?php
include 'db_connection.php';

$db = new Database();

$slot_number = "";
$type = "";

$errorMessage = "";
$successMessage = "";

if ($_SERVER['REQUEST_METHOD'] == 'POST') {

    $type = $_POST["type"] ?? '';
    $slot_number = $_POST["room_number"] ?? '';

    // Get current timestamp
    $current_time = date('Y-m-d H:i:s');

    if (empty($slot_number) || empty($type)) {
        $errorMessage = "All the required fields are not provided " . $type . $slot_number;
        http_response_code(400);
        echo json_encode(["error" => $errorMessage]);
        exit;
    }

    try {
        if ($type == 'in') {
            // Add new record to the database with in_time
            $stmt = $db->prepare("INSERT INTO price_table (slot_number, in_time, out_time) VALUES (?, ?, NULL)");
            $stmt->bind_param("ss", $slot_number, $current_time);
            $stmt->execute();

            if ($stmt->affected_rows > 0) {
                $successMessage = "Record added correctly";
                http_response_code(201);
                echo json_encode(["message" => $successMessage]);
            } else {
                throw new Exception("Failed to add record.");
            }

            $stmt->close();
        } elseif ($type == 'out') {
            // Update the out_time of the existing record
            $stmt = $db->prepare("UPDATE price_table SET out_time=? WHERE slot_number=? AND out_time IS NULL");
            $stmt->bind_param("ss", $current_time, $slot_number);
            $stmt->execute();

            if ($stmt->affected_rows > 0) {
                $successMessage = "Record updated correctly";
                http_response_code(200);
                echo json_encode(["message" => $successMessage]);
            } else {
                throw new Exception("Failed to update record or no matching record found.");
            }

            $stmt->close();
        } else {
            $errorMessage = "Invalid type provided";
            http_response_code(400);
            echo json_encode(["error" => $errorMessage]);
        }
    } catch (Exception $e) {
        $errorMessage = "Error: " . $e->getMessage();
        http_response_code(500);
        echo json_encode(["error" => $errorMessage]);
    }
}
?>
