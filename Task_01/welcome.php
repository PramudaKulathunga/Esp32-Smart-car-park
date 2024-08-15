<!doctype html>
<html lang="en">
  <head>
    <meta charset="utf-8">
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <title>Smart Vehicle Park</title>
    <link href="https://cdn.jsdelivr.net/npm/bootstrap@5.3.3/dist/css/bootstrap.min.css" rel="stylesheet" integrity="sha384-QWTKZyjpPEjISv5WaRU9OFeRpok6YctnYmDr5pNlyT2bRjXh0JMhjY6hW+ALEwIH" crossorigin="anonymous">
  </head>
  <body>
    <div class="container text-center d-flex vh-100 justify-content-between">
      <div class="d-flex flex-column w-100 my-auto">
        <img class="mx-auto" src="welcome.jpg" alt="welcome" />
        <div class="d-flex mb-3 mx-auto">
          <label for="slot_number">Slot Number:</label>
          <input id="slot_number" type="number" min="1" max="9" class="ms-4 form-control" placeholder="Insert Slot Number" />
        </div>
        <button type="button" class="btn btn-primary mx-auto" onclick="submitSlot()">Submit</button>
      </div>
    </div>

    <script>
      function submitSlot() {
        const slotNumber = document.getElementById('slot_number').value;
        if (slotNumber) {
          const url = `http://localhost/Task_01/price.php?slot_number=${slotNumber}`;
          window.location.href = url;
        } else {
          alert('Please enter a slot number.');
        }
      }
    </script>

    <script src="https://cdn.jsdelivr.net/npm/bootstrap@5.3.3/dist/js/bootstrap.bundle.min.js" integrity="sha384-YvpcrYf0tY3lHB60NNkmXc5s9fDVZLESaAA55NDzOxhy9GkcIdslK1eN7N6jIeHz" crossorigin="anonymous"></script>
  </body>
</html>
