
int roomNumber = 1;

//Define libraries
#include <LiquidCrystal_I2C.h>  
#include <Keypad.h>             
#include <Stepper.h>            
#include <WiFi.h>               
#include <HTTPClient.h>         

LiquidCrystal_I2C lcd(0x27, 16, 2);
String URL = "http://192.168.43.143/Task_01/modify_db.php";  /

const char* ssid = "Rusiru";         //wifi id
const char* password = "111222333";  //wifi password

//Define pins
int redLedFront = 23;
int greenLedFront = 13;
int redLedBack = 0;
int greenLedBack = 26;

int confirmBtn = 34;  //front push button

int trigPinUltraF = 15;  //ultrasonic sensors
int echoPinUltraF = 2;
int trigPinUltraB = 4;
int echoPinUltraB = 16;

byte pin_rows[3] = { 12, 14, 27 };    //keypad row pins
byte pin_column[3] = { 25, 33, 32 };  //keypad column pins



long durationF, cmF, durationB, cmB;
long distanceBetweenVehicle = 10;
bool isBackAvailable = true;

int availableRoomCount = 0;
bool carRoomAvailability[] = { 1, 1, 1, 1, 1, 1, 1, 1 };
int currentRoom = roomNumber - 1;  //work with array index
int rotateRoom = 0;                //work with array index

const int stepsPerRevolution = 256;                    //for 45 degree
Stepper myStepper(stepsPerRevolution, 19, 5, 18, 17);  //in1 in3 in2 in4

char keys[3][3] = {
  { '1', '2', '3' },
  { '4', '5', '6' },
  { '7', '8', '9' }
};

Keypad keypad = Keypad(makeKeymap(keys), pin_rows, pin_column, 3, 3);

String postData;  //database request

unsigned long prevTime1 = 0;

void setup() {

  connectWiFi();  //connect to wifi

  myStepper.setSpeed(15);  //  motor speed

  Serial.begin(9600);

  pinMode(trigPinUltraF, OUTPUT);
  pinMode(echoPinUltraF, INPUT);
  pinMode(trigPinUltraB, OUTPUT);
  pinMode(echoPinUltraB, INPUT);
  pinMode(greenLedFront, OUTPUT);
  pinMode(redLedFront, OUTPUT);
  pinMode(greenLedBack, OUTPUT);
  pinMode(redLedBack, OUTPUT);
  pinMode(confirmBtn, INPUT);

  lcd.init();  // initialize the lcd
  lcd.backlight();

  digitalWrite(greenLedFront, HIGH);  //setup light both green lights at beginning
  digitalWrite(redLedFront, LOW);
  digitalWrite(greenLedBack, HIGH);
  digitalWrite(redLedBack, LOW);

  for (int x = 0; x < 8; x++) {  //count available rooms
    if (carRoomAvailability[x] == 1) {
      availableRoomCount++;
    }
  }
}

void loop() {
  unsigned long currentTime = millis();

  if (WiFi.status() != WL_CONNECTED) {  //wifi connection
    connectWiFi();
  }

  if (currentTime - prevTime1 > 2000) {
    roomCountDisplay();  //lcd display function

    for (int x = 0; x < 8; x++) {  //for testing porpose
      Serial.print(carRoomAvailability[x]);
    }
    Serial.println("");
  }

  if (availableRoomCount != 0) {  //ckecking front side
    checkUltraFront();
  } else {
    digitalWrite(greenLedFront, LOW);  //setup light both green lights at beginning
    digitalWrite(redLedFront, HIGH);
  }

  //ckecking back side
  char key = keypad.getKey();
  if (key && carRoomAvailability[key - '0' - 1] == 0) {
    isBackAvailable = false;
    Serial.println(key);
    roomRotateParkOut(key);
  }
}
