<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Smart Park</title>
    <link rel="stylesheet" href="https://cdn.jsdelivr.net/npm/bootstrap@5.3.3/dist/css/bootstrap.min.css">
</head>
<body>
    <div class='container my-5'>
        <h2>List of Clients</h2>
       
        <br>
        <table class="table">
            <thead>
                <tr>
                    <th>ID</th>
                    <th>Slot Number</th>
                    <th>In Time</th>
                    <th>Out Time</th>
                </tr>
            </thead>
            <tbody>
                <?php
                include 'db_connection.php';

                $db = new Database();

                // Read all rows from database table
                $sql = "SELECT * FROM price_table";
                $result = $db->query($sql);

                // Read data of each row
                while($row = $result->fetch_assoc()) {
                    echo "
                    <tr>
                        <td>{$row['id']}</td>
                        <td>{$row['slot_number']}</td>
                        <td>{$row['in_time']}</td>
                        <td>{$row['out_time']}</td>
                    </tr>
                    ";
                }
                ?>
            </tbody>
        </table>
    </div>
</body>
</html>
