int currentStateB = 0;
int previousStateB = 0;

int buttonState = 0;
unsigned long prevTime2 = 0;
unsigned long ifNotPressConfirmBtnInterval = 300000;  //waiting time if not pressed confirm botton

void checkUltraFront() {
  digitalWrite(trigPinUltraF, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPinUltraF, LOW);

  durationF = pulseIn(echoPinUltraF, HIGH);

  cmF = (durationF / 2) / 29.1;

  if (cmF < distanceBetweenVehicle) {

    Serial.println("front detected");  //for testing porpose
    reminderDisplay();
    functionStop();  //LED function
    roomRotateForParkIn();

    unsigned long currentTime2 = millis();
    prevTime2 = currentTime2;

    while (!buttonState) {
      unsigned long currentTime2 = millis();
      buttonState = digitalRead(confirmBtn);
      if (currentTime2 - prevTime2 > ifNotPressConfirmBtnInterval) {
        break;
      }
    }

    availableRoomCount--;
    buttonState = 0;

    //update room details to database
    postData = "type=1&room_number=" + String(currentRoom + 1);
    updateDatabase();

    functionStart();  //LED function
  }
}

void checkUltraBack() {
  digitalWrite(trigPinUltraB, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPinUltraB, LOW);

  durationB = pulseIn(echoPinUltraB, HIGH);

  cmB = (durationB / 2) / 29.1;

  if (cmB < distanceBetweenVehicle) {
    currentStateB = 1;
  } else {
    currentStateB = 0;
  }
  delay(200);

  if (currentStateB != previousStateB) {
    if (currentStateB == 1) {
      isBackAvailable = true;
    }
  }
  previousStateB = currentStateB;
}