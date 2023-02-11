#include <Arduino.h>

#define GHOST_TYPE_LEN 32
#define GHOST_NAME_LEN 32

String location;


struct Ghost {
    char type[GHOST_TYPE_LEN];
    char name[GHOST_NAME_LEN];
    uint8_t activeness;
};

// Function definitions
Ghost getGhostFromServer();
void waitForMovement();
String getLocation();


void setup(){
  
}

void setup1(){

}

void loop(){
  getGhostFromServer();
  waitForMovement();
  bool found;
  while (!found){
    location = getLocation();
  }
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
  
}

// get the current relative location from the wifi scanning stuff.
String getLocation() {
  return "";
}