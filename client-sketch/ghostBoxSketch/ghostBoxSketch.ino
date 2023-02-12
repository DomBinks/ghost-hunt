#include <Arduino.h>
#include "LocationFinder.h"
#include <SoftwareSerial.h>
#include <Wire.h>
#include <Servo.h>
#include "LocationFinder.h"

#include "Ghost.h"
#include "WiFiJSONServer.h"



#define rxPin 0
#define txPin 15
#define sevseg 12
#define buzzer 13
#define servopin 8
#define buttonPin 19
#define statusLED 20

#define led1 16
#define led2 17
#define led3 18

Servo servo;
SoftwareSerial mySerial = SoftwareSerial(rxPin, txPin);

String location;


// Function definitions
Ghost getGhostFromServer();
void waitForMovement();
String getLocation();
unsigned long timeSince(unsigned long);
void ghostEffects(uint8_t);

void endGame(Ghost ghost){
  //setSevenSeg(ghost.foundCode);
  
  for (int i=0; i<20; i++){
    setSevenSeg(ghost.foundCode);
    delay(500);
  }
  ghostEffects(255);
}

void setup(){
  pinMode(txPin, OUTPUT);

  mySerial.begin(9600);
  pinMode(sevseg,OUTPUT);
  pinMode(buzzer,OUTPUT);

  pinMode(led1,OUTPUT);
  pinMode(led2,OUTPUT);
  pinMode(led3,OUTPUT);
  pinMode(buttonPin,INPUT);
  pinMode(statusLED,OUTPUT);

  digitalWrite(led1,LOW);
  digitalWrite(led2,LOW);
  digitalWrite(led3,LOW);
  digitalWrite(statusLED,LOW);

  digitalWrite(buzzer,LOW);
  digitalWrite(sevseg,LOW);
  setSevenSeg(12);

  servo.attach(servopin);
  Serial.begin(9600);
  
  // Try to initialize!
  //while (!mpu.begin()) {
  //  Serial.println("Failed to find MPU6050 chip");
  //  delay(3);
  //}
  
  

  
  
  setSevenSeg(10);
  setBuzzer(0);

  setupWiFi();
  startServer();
  digitalWrite(statusLED, HIGH);


}

void setup1(){

}

float intensity = 0;
float offset = 0;
Ghost ghost;
void loop(){
  digitalWrite(led1,LOW);
  digitalWrite(led2,LOW);
  digitalWrite(led3,LOW);

  digitalWrite(buzzer,LOW);
  digitalWrite(sevseg,LOW);
  // great succ
  ghost = getGhostFromServer();

  // stuff
  offset = ((float) ghost.activeness) / 128.0;
  randomSeed(analogRead(0));
  waitForMovement();
  bool found = false;
  while (!found){
    location = getLocation();
    if(true || location[0] == ghost.location)
    {
      //we're in the ghosts area do spooky things 
      //delay(500); //wait some time
      intensity += offset;
      ghostEffects(intensity);
      // button is pressed
      if (digitalRead(buttonPin) && intensity > 52){
        found = true;
        endGame(ghost);
      }
    }
    delay(10);


  
  //Serial.print("Current Location: ");
  //Serial.println(getLocation());
  delay(500);
  }

}
///sets the 7 segment display
///
void setSevenSeg(uint8_t i)
{
  digitalWrite(sevseg, HIGH);
      mySerial.write(i);
  delay(10);
  digitalWrite(sevseg, LOW);
}

void setBuzzer(uint8_t i)
{
  digitalWrite(buzzer, HIGH);
      mySerial.write(i);
  delay(10);
  digitalWrite(buzzer, LOW);
}

void ghostEffects(uint8_t intensity)
{
  Serial.println("Set ghosteffects");
  if(intensity > 10)
  { 
    setSevenSeg(20);  
    setBuzzer(3);
    digitalWrite(led1, HIGH);
  }
  if(intensity > 30)
  { 
    setSevenSeg(40);
    setBuzzer(6);  
    digitalWrite(led2, HIGH);
    
  }     
  if(intensity > 50)
  { 
    setSevenSeg(90);  
    setBuzzer(15);
    digitalWrite(led3, HIGH);
  }
  if(intensity > 60)
  {
    setSevenSeg(0);
    setBuzzer(0);    
    digitalWrite(led1, LOW);
    digitalWrite(led2, LOW);
    digitalWrite(led3, LOW);
  }
  return;
}

void loop1(){
  
}

// Blocking function that waits to recieve a "ghost" from the server.
// returns a struct containing the ghost type and any other location 
Ghost getGhostFromServer(){
    Ghost ghost = {"", "", 0, 0};
    // do some logic for actually getting a ghost
  
    while (ghost.name == "") {
      ghost = handleClient();
    }
    Serial.println(ghost.name);
    Serial.println("##############################################################################");
    Serial.println("################### S U C C E S S ############################################");
    Serial.println("##############################################################################");
    return ghost;
}

// use the MPU-6050 accelerometer breakout board to detect movement
void waitForMovement(){
  return;
  // gets time in ms since program started 
  unsigned long startTime = millis();
  bool not_moved = true;
  while (not_moved && timeSince(startTime) < 5000) {
    // check if moved
  }

}

// get the current relative location from the wifi scanning stuff.
WifiScanner s;
String getLocation() {
  return "a";
  return positioning.predictRoomName(s);
}

unsigned long timeSince(unsigned long start_time){
  return millis() - start_time;
}
