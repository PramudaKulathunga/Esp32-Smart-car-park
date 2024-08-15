void functionStop() {
  digitalWrite(redLedBack, HIGH);  //light back red light
  digitalWrite(greenLedBack, LOW);
  digitalWrite(redLedFront, HIGH);  //light front red light
  digitalWrite(greenLedFront, LOW);
}

void functionStart() {
  digitalWrite(greenLedBack, HIGH);  //light back green light
  digitalWrite(redLedBack, LOW);
  digitalWrite(greenLedFront, HIGH);  //light front green light
  digitalWrite(redLedFront, LOW);
}

void roomCountDisplay() {

  lcd.clear();                    // clear display
  lcd.setCursor(0, 0);            // move cursor to (0, 0)
  lcd.print("- CAR  PARKING -");  // print message at (0, 0)
  lcd.setCursor(0, 1);            // move cursor to (0, 1)
  lcd.print("Available room:");   // print message
  lcd.print(availableRoomCount);  // print the available room count
  delay(2000);
}

void reminderDisplay() {
  
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("  Remind your  ");
  lcd.setCursor(0, 1);
  lcd.print(" parking number ");
  delay(2000);
}