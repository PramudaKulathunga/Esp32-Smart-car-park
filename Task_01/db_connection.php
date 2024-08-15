<?php
class Database {
    private $servername = "localhost";
    private $username = "root";
    private $password = "";
    private $database = "smart_park";
    public $connection;

    public function __construct() {
        // Create connection
        $this->connection = new mysqli($this->servername, $this->username, $this->password, $this->database);

        // Check connection
        if ($this->connection->connect_error) {
            throw new Exception("Connection failed: " . $this->connection->connect_error);
        }
    }

    public function query($sql) {
        $result = $this->connection->query($sql);
        if (!$result) {
            throw new Exception("Invalid query: " . $this->connection->error);
        }
        return $result;
    }

    public function prepare($sql) {
        $stmt = $this->connection->prepare($sql);
        if (!$stmt) {
            throw new Exception("Failed to prepare statement: " . $this->connection->error);
        }
        return $stmt;
    }

    public function __destruct() {
        $this->connection->close();
    }
}
