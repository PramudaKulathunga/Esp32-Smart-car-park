int servoMotorSpeed = 10;

void roomRotateForParkIn() {

  int size = 8;
  int degree;

  if (carRoomAvailability[currentRoom] == 1) {
    rotateRoom = currentRoom;
    degree = rotateRoom - currentRoom;
  } else {
    for (int offset = 0; offset < size; offset++) {  // finding nearest empty room
      int leftIndex = (currentRoom - offset + size) % size;
      int rightIndex = (currentRoom + offset) % size;

      if (carRoomAvailability[rightIndex] == 1) {
        rotateRoom = rightIndex;
        degree = -(rotateRoom - currentRoom);
        break;
      }
      if (carRoomAvailability[leftIndex] == 1) {
        rotateRoom = leftIndex;
        degree = (rotateRoom - currentRoom);
        break;
      }
    }
  }

  if (currentRoom == 0 && rotateRoom == 7) {
    degree = 1;
  }
  if (currentRoom == 7 && rotateRoom == 0) {
    degree = -1;
  }
  Serial.println(rotateRoom + 1);  //for testing porpose

  //rotate motor
  myStepper.step(stepsPerRevolution * degree);
  delay(1000);

  currentRoom = rotateRoom;
  Serial.println(currentRoom + 1);
  carRoomAvailability[rotateRoom] = false;
}

void roomRotateParkOut(char key) {

  int room = key - '0';
  int degree;
  int rotateRoom2;

  functionStop();

  //rotate motor
  if (room > 4) {
    rotateRoom2 = (room - 5);
  } else {
    rotateRoom2 = (room + 3);
  }
  Serial.println(rotateRoom2);

  if (carRoomAvailability[currentRoom] != rotateRoom2) {
    degree = currentRoom - rotateRoom2;
  }
  Serial.println(degree);

  myStepper.step(stepsPerRevolution * degree);
  delay(1000);

  while (!isBackAvailable) {
    checkUltraBack();
  }

  availableRoomCount++;
  if (room > 4) {
    currentRoom = (room - 5);
  } else {
    currentRoom = (room + 3);
  }

  Serial.println(currentRoom + 1);
  carRoomAvailability[(room - 1)] = true;  //release the car room

  //update room details to database
  postData = "type=0&room_number=" + String(room);
  updateDatabase();

  digitalWrite(greenLedBack, HIGH);  //light front green light
  digitalWrite(redLedBack, LOW);
  delay(5000);  //Restart after parking out vehicle
  functionStart();
}