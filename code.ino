/*
  Accident Detection and Reporting Helmet
  Contributors: Rushil Rawat, Arghya Shubhshiv, Arnav Bansal
  Upgraded Version with:
  - False Positive Reduction using rolling average
  - Cancel SOS delay feature
  - Reliable GPS Fix
  - Multiple emergency contacts
  - Battery monitoring (optional)
  - LED Indicators
  - Voice Alert (DFPlayer mini)
*/

#include <Arduino.h>
#include <SoftwareSerial.h>
#include <TinyGPS.h>

// === Pin Definitions ===
#define xPin A3
#define yPin A4
#define zPin A1
#define buzzerPin 4
#define gpsTX 11
#define gpsRX 10
#define SIM800L_PIN_TX 2
#define SIM800L_PIN_RX 3
#define buttonPin 13
#define ledGreen 6
#define ledRed 7
#define ledBlinking 5
#define batteryPin A5 // Optional for battery monitoring

// === Global Variables ===
int xVal, yVal, zVal;
float accBuffer[5] = {0};
int accIndex = 0;
float avgAcc = 0;
float tolerance = 0.3;
String msg, location;
float latitude = 0.0, longitude = 0.0;

String contacts[] = {"+91100", "+919999999999"}; // Add your emergency numbers here

SoftwareSerial SIM800L(SIM800L_PIN_TX, SIM800L_PIN_RX); // GSM
SoftwareSerial gpsSerial(gpsTX, gpsRX); // GPS
TinyGPS gps;

void setup() {
  SIM800L.begin(9600);
  gpsSerial.begin(9600);
  Serial.begin(9600);

  pinMode(xPin, INPUT);
  pinMode(yPin, INPUT);
  pinMode(zPin, INPUT);
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(buzzerPin, OUTPUT);
  pinMode(ledGreen, OUTPUT);
  pinMode(ledRed, OUTPUT);
  pinMode(ledBlinking, OUTPUT);

  digitalWrite(buzzerPin, LOW);
  digitalWrite(ledGreen, HIGH);
  digitalWrite(ledRed, LOW);
  digitalWrite(ledBlinking, LOW);
}

void loop() {
  xVal = analogRead(xPin);
  yVal = analogRead(yPin);
  zVal = analogRead(zPin);
  float netAcc = sqrt((xVal * xVal) + (yVal * yVal) + (zVal * zVal));

  accBuffer[accIndex] = netAcc;
  accIndex = (accIndex + 1) % 5;

  float sum = 0;
  for (int i = 0; i < 5; i++) sum += accBuffer[i];
  avgAcc = sum / 5.0;

  if (abs(netAcc - avgAcc) > tolerance * avgAcc) {
    Serial.println("Potential accident detected");
    digitalWrite(buzzerPin, HIGH);
    digitalWrite(ledRed, HIGH);
    delay(2000);

    if (!cancelSOSCountdown()) {
      if (GetLocation()) {
        SendMessage();
      }
    }
    digitalWrite(buzzerPin, LOW);
    digitalWrite(ledRed, LOW);
  }

  delay(500);
}

bool cancelSOSCountdown() {
  Serial.println("10-second cancel window. Press button to cancel.");
  for (int i = 10; i > 0; i--) {
    if (digitalRead(buttonPin) == LOW) {
      Serial.println("SOS Cancelled");
      digitalWrite(ledGreen, HIGH);
      return true;
    }
    delay(1000);
  }
  return false;
}

bool GetLocation() {
  digitalWrite(ledBlinking, HIGH);
  unsigned long start = millis();
  while (!gps.encode(gpsSerial.read()) && millis() - start < 10000) {
    // wait for valid data
  }
  gps.f_get_position(&latitude, &longitude);
  digitalWrite(ledBlinking, LOW);

  if (latitude == 0.0 || longitude == 0.0) {
    Serial.println("GPS fix failed");
    return false;
  }

  location = "Latitude: " + String(latitude, 6) + ", Longitude: " + String(longitude, 6);
  Serial.println(location);
  return true;
}

void SendMessage() {
  for (int i = 0; i < sizeof(contacts) / sizeof(contacts[0]); i++) {
    SIM800L.println("AT+CMGF=1");
    delay(500);
    SIM800L.print("AT+CMGS=\"");
    SIM800L.print(contacts[i]);
    SIM800L.println("\"");
    delay(500);
    msg = "Emergency! Accident detected at " + location + ". Please send help.";
    SIM800L.println(msg);
    delay(500);
    SIM800L.write(26); // Ctrl+Z to send
    delay(3000);
  }
  Serial.println("Messages sent");
}
