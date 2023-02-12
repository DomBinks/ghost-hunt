#include <Arduino.h>
#include "LocationFinder.h"
#include <SoftwareSerial.h>

#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <MPU6050.h>
#include <Wire.h>
#include "LocationFinder.h"

#define GHOST_TYPE_LEN 32
#define GHOST_NAME_LEN 32
#define rxPin 0
#define txPin 15
#define sevseg 12
#define buzzer 13
String location;

SoftwareSerial mySerial =  SoftwareSerial(rxPin, txPin);
Adafruit_MPU6050 mpu;

struct Ghost {
    char type[GHOST_TYPE_LEN];
    char name[GHOST_NAME_LEN];
    char location; //the room the ghost is in
    uint8_t activeness;
};

// Function definitions
Ghost getGhostFromServer();
void waitForMovement();
String getLocation();
unsigned long timeSince(unsigned long);


void setup(){
  pinMode(txPin, OUTPUT);
  mySerial.begin(9600);
  pinMode(sevseg,OUTPUT);
  pinMode(buzzer,OUTPUT);
  digitalWrite(buzzer,LOW);
  digitalWrite(sevseg,LOW);
  Serial.begin(115200);
  while (!Serial)
    delay(3); // will 
  // Try to initialize!
  //while (!mpu.begin()) {
  //  Serial.println("Failed to find MPU6050 chip");
  //  delay(3);
  //}
}

void setup1(){

}
float intensity = 0;
void loop(){
  Ghost ghost = getGhostFromServer();
  waitForMovement();
  bool found = false;
  while (!found){
    location = getLocation();
   
    if(location[0] == ghost.location)
    {
      //we're in the ghosts area do spooky things 
      //delay(500); //wait some time
      intensity += 0.5;
      ghostEffects(ghost);
    }
  }
}
///sets the 7 segment display
///
void setSevenSeg(uint8_t i)
{
  digitalWrite(sevseg, HIGH);
  delay(10);
      mySerial.write(i);
  delay(10);
  digitalWrite(sevseg, LOW);
}

void setBuzzer(uint8_t i)
{
  digitalWrite(buzzer, HIGH);
  delay(10);
      mySerial.write(i);
  delay(10);
  digitalWrite(buzzer, LOW);
}

void ghostEffects(Ghost ghost)
{
    
}

void loop1(){

}

// Blocking function that waits to recieve a "ghost" from the server.
// returns a struct containing the ghost type and any other location 
Ghost getGhostFromServer(){
    Ghost ghost = {"Poltegeist", "Daniel"};
    // do some logic for actually getting a ghost

    return ghost;
}

// use the MPU-6050 accelerometer breakout board to detect movement
void waitForMovement(){
  // gets time in ms since program started 
  unsigned long startTime = millis();
  bool not_moved = true;
  while (not_moved && timeSince(startTime) < 30000) {
    // check if moved
  }

}

// get the current relative location from the wifi scanning stuff.
WifiScanner s;
String getLocation() {
  return positioning.predictRoomName(s);
}

unsigned long timeSince(unsigned long start_time){
  return millis() - start_time;
}