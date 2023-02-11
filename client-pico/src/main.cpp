#include <Arduino.h>

#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <MPU6050.h>
#include <Wire.h>
#include <LocationFinder.h>

#define GHOST_TYPE_LEN 32
#define GHOST_NAME_LEN 32

String location;
Adafruit_MPU6050 mpu;

struct Ghost {
    char type[GHOST_TYPE_LEN];
    char name[GHOST_NAME_LEN];
    uint8_t activeness;
};

// Function definitions
Ghost getGhostFromServer();
void waitForMovement();
String getLocation();
unsigned long timeSince(unsigned long);


void setup(){
  Serial.begin(115200);
  while (!Serial)
    delay(3); // will 
  // Try to initialize!
  while (!mpu.begin()) {
    Serial.println("Failed to find MPU6050 chip");
    delay(3);
  }
}

void setup1(){

}

void loop(){
/*  getGhostFromServer();
  waitForMovement();
  bool found;
  while (!found){
    location = getLocation();
  }
  */
  Serial.print("Current Location: ");
  Serial.println(getLocation());
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