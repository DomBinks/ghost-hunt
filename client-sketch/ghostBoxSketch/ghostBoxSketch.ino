#include <Arduino.h>

#include <Wire.h>
#include "LocationFinder.h"
#include <MPU6050.h>

#define GHOST_TYPE_LEN 32
#define GHOST_NAME_LEN 32

#define PICO_I2C_SDA 20
#define PICO_I2C_SCL 21

MPU6050 accelgyro;
String location;
int16_t ax, ay, az;
int16_t gx, gy, gz;

typedef struct Ghost {
    char type[GHOST_TYPE_LEN];
    char name[GHOST_NAME_LEN];
    uint8_t activeness;
} Ghost;

// Function definitions
Ghost getGhostFromServer();
void waitForMovement();
String getLocation();
unsigned long timeSince(unsigned long);


void setup(){
  Serial.begin(9600);
  while (!Serial)
    delay(3); // will 
  Serial.println("test");
  

  Wire.begin();
  //Wire.setSCL(PICO_I2C_SCL);
  //Wire.setSDA(PICO_I2C_SDA);
  
  accelgyro.initialize();
  Serial.println(accelgyro.testConnection() ? "MPU6050 connection successful" : "MPU6050 connection failed");

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
  //Serial.print("Current Location: ");
  //Serial.println(getLocation());
  Serial.print("a/g:\t");
        Serial.print(ax); Serial.print("\t");
        Serial.print(ay); Serial.print("\t");
        Serial.print(az); Serial.print("\t");
        Serial.print(gx); Serial.print("\t");
        Serial.print(gy); Serial.print("\t");
        Serial.println(gz);
  delay(500);
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