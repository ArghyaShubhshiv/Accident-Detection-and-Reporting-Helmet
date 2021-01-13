// Include Libraries
#include <Arduino.h>
#include <SoftwareSerial.h>
#include <TinyGPS.h>

// Pin Definitions
#define xPin	A3
#define yPin	A4
#define zPin	A1
#define buzzer	4
#define gpsTX	11
#define gpsRX	10
#define SIM800L_PIN_TX	2
#define SIM800L_PIN_RX	3
#define button 13
int xVal, yVal, zVal, total_acc1, total_acc2, total_acc3;
int tolerance = 0.5;
String msg, location;
float latitude, longtitude;

SoftwareSerial SIM800L(SIM800L_PIN_TX, SIM800L_PIN_RX); //SoftwareSerial for GSM Module
SoftwareSerial gpsSerial(gpsTX, gpsRX); //SoftwareSerial for GPS
TinyGPS gps;

void setup() {
  SIM800L.begin(9600);
  gpsSerial.begin(9600);
  Serial.begin(9600);
  pinMode(xPin, OUTPUT);
  pinMode(yPin, OUTPUT);
  pinMode(zPin, OUTPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(button, INPUT);
}

void loop() {
  if (digitalRead(button) == LOW){
    digitalWrite(buzzer, LOW);
  } else if (digitalRead(button) == HIGH){
    digitalWrite(buzzer, HIGH);
  }
  xVal = analogRead(xPin);
  yVal = analogRead(yPin);
  zVal = analogRead(zPin);
  total_acc1 = sqrt((xVal * xVal) + (yVal * yVal) + (zVal * zVal)); //calculating net "normal" acceleration
  
  delay(2000);
  
  xVal = analogRead(xPin);
  yVal = analogRead(yPin);
  zVal = analogRead(zPin);
  total_acc2 = sqrt((xVal * xVal) + (yVal * yVal) + (zVal * zVal)); //calculating net acceleration for the 1st check
  
  if ((abs(total_acc2) >= abs(13/10 * total_acc1)) || (abs(total_acc2) <= abs(7/10 * total_acc1))){
    delay(10000);
    
    xVal = analogRead(xPin);
    yVal = analogRead(yPin);
    zVal = analogRead(zPin);
    total_acc3 = sqrt((xVal * xVal) + (yVal * yVal) + (zVal * zVal)); //calculating net acceleration for the 2nd check
    
    if(((abs(total_acc3) >= abs(11.5/10 * total_acc2)) || (abs(total_acc3) <= abs(0.5/10 * total_acc2)))){    
      digitalWrite(button, HIGH);
      SendMessage();
    }
  }
}

void SendMessage(){
    GetLocation();
    
    SIM800L.println("AT+CMGF=1"); //setting SMS mode to TEXT
    delay(500);
    SIM800L.println("AT+CMGS=\"+91100\"\r"); //+91 100 (police) is the number where we'll message
    delay(500);
    msg = "Hello sir I'm injured in a traffic accident in the coordinates of " + location + " please save me!!!";
    SIM800L.println(msg); //finalizing the message
    delay(500);
    SIM800L.println((char)24); //sending the message
}

void GetLocation(){
  if(gpsSerial.available()){ // check for gps data 
    if(gps.encode(gpsSerial.read())){   //encoding GPS data
      gps.f_get_position(&latitude, &longtitude); //getting coordinates
    }
    location = "Latitude: " + String(latitude) + " Longtitude: " + String(longtitude); 
  }
}
