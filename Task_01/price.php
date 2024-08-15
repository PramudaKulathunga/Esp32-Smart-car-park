<?php
include 'db_connection.php';

$db = new Database();

// Get the slot number from the URL parameter
$slot_number = isset($_GET['slot_number']) ? (int)$_GET['slot_number'] : 0;

if ($slot_number > 0) {
    // Query the database for the given slot number, get the last row where in_time and out_time are not null
    $sql = "SELECT in_time, out_time FROM price_table WHERE slot_number = $slot_number AND in_time IS NOT NULL AND out_time IS NOT NULL ORDER BY out_time DESC LIMIT 1";
    $result = $db->query($sql);
    $price = 0;

    if ($result && $result->num_rows > 0) {
        // Fetch the in_time and out_time
        $row = $result->fetch_assoc();
        $in_time = new DateTime($row['in_time']);
        $out_time = new DateTime($row['out_time']);
        
        // Calculate the difference in minutes
        $interval = $in_time->diff($out_time);
        $minutes = $interval->days * 24 * 60 + $interval->h * 60 + $interval->i;
        
        // Calculate the price at 10 Rs per minute
        $price = $minutes * 10;
    }
} else {
    // Handle the case where slot_number is not provided or invalid
    $price = 0;
}
?>

<!doctype html>
<html lang="en">
  <head>
    <meta charset="utf-8">
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <title>Smart vehicle park</title>
    <link href="https://cdn.jsdelivr.net/npm/bootstrap@5.3.3/dist/css/bootstrap.min.css" rel="stylesheet" integrity="sha384-QWTKZyjpPEjISv5WaRU9OFeRpok6YctnYmDr5pNlyT2bRjXh0JMhjY6hW+ALEwIH" crossorigin="anonymous">
  </head>
  <body>
    <div class="container text-center d-flex vh-100 justify-content-between">
        <div class="d-flex flex-column w-100 my-auto">
            <h1 class="text-primary fw-bold" style="font-size: 60px">HELLO...</h1>
            <h3 class="mt-5 mb-4">Your Price is</h3>
            <h4 class="border border-black mx-auto px-4 py-2 mb-5"><?php echo $price; ?> Rs</h4>
            <h1 class="text-secondary fw-bold" style="font-size: 80px">Thank You...</h1> 
            <h1 class="text-black fw-bold" style="font-size: 80px">Come Again</h1>  
            <a href="./welcome.php" class="btn btn-primary mx-auto">Go Back</a>
        </div>
        <div class="d-flex">
          <img src="Policeman.jpg" width="200" height="auto" class="my-auto" />
        </div>
    </div>
    <script src="https://cdn.jsdelivr.net/npm/bootstrap@5.3.3/dist/js/bootstrap.bundle.min.js" integrity="sha384-YvpcrYf0tY3lHB60NNkmXc5s9fDVZLESaAA55NDzOxhy9GkcIdslK1eN7N6jIeHz" crossorigin="anonymous"></script>
  </body>
</html>
