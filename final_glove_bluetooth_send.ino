#include <SoftwareSerial.h>

// Declare variables
int sensorPins[] = {A3, A2, A1, A0}; // Sensor pins (Thumb, Index, Middle, Pinkie)
const int THRESHOLD = 415;
int sensorValues[4];                 // Array to store sensor readings
int buttonPin = 12;                  // Button pin
int buttonStatus = 0;                // Button status (pressed or not)
bool buttonPressed = false;          // Flag for button press
unsigned long pressTime = 0;         // Time when button was pressed

// Create a SoftwareSerial connection for HC-05
SoftwareSerial BTSerial(2, 3); // RX | TX

void setup() {
  // Initialize serial communication
  Serial.begin(9600);
  BTSerial.begin(9600); // Bluetooth module baud rate

  // Configure the button pin as input
  pinMode(buttonPin, INPUT);

  Serial.println("Starting Bluetooth communication...");
}

void loop() {
  // Read button status
  buttonStatus = digitalRead(buttonPin);

  // Check if the button is pressed
  if (buttonStatus == HIGH && !buttonPressed) {
    buttonPressed = true;             // Set flag
    pressTime = millis();             // Record the time
    Serial.println("Button Pressed!");
  }

  // Check if 1.5 seconds have passed since the button was pressed
  if (buttonPressed && (millis() - pressTime >= 1500)) {
    bool sensorStates[4] = {false, false, false, false}; // Store if sensors are bent

    // Read all sensor values
    for (int i = 0; i < 4; i++) {
      sensorValues[i] = analogRead(sensorPins[i]); // Read sensor value
      Serial.print("Sensor ");
      Serial.print(i);
      Serial.print(": ");
      Serial.println(sensorValues[i]);

      // Update sensor state
      sensorStates[i] = (sensorValues[i] <= THRESHOLD); 
    }

    // Assign sensor states to meaningful names
    bool thumbBent = sensorStates[0];   // Thumb = A3
    bool indexBent = sensorStates[1];   // Index Finger = A2
    bool middleBent = sensorStates[2];  // Middle Finger = A1
    bool pinkieBent = sensorStates[3];  // Pinkie = A0

    // Evaluate combinations
    if (thumbBent && indexBent && middleBent && pinkieBent) {
      BTSerial.println("S");
      Serial.println("Sent: stop over Bluetooth");
    } else if (!thumbBent && !indexBent && middleBent && pinkieBent) {
      BTSerial.println("R");
      Serial.println("Sent: right over Bluetooth");
    } else if (!thumbBent && !indexBent && !middleBent && pinkieBent) {
      BTSerial.println("L");
      Serial.println("Sent: left over Bluetooth");
    } else if (!thumbBent && indexBent && middleBent && pinkieBent) {
      BTSerial.println("t");
      Serial.println("Sent: thanks over Bluetooth");
    } else if (!thumbBent && !indexBent && middleBent && !pinkieBent) {
      BTSerial.println("l");
      Serial.println("Sent: love over Bluetooth");
    } else if (!thumbBent && !indexBent && !middleBent && !pinkieBent) {
      BTSerial.println('s');
      Serial.println("Sent: sorry over Bluetooth");
    } else if (thumbBent && !indexBent && !middleBent && pinkieBent) {
      BTSerial.println("d");
      Serial.println("Sent: danger over Bluetooth");
    } else {
      BTSerial.println("s");
      Serial.println("Sent: NO MATCH over Bluetooth");
    }

    buttonPressed = false; // Reset flag to wait for the next button press
  }
}
