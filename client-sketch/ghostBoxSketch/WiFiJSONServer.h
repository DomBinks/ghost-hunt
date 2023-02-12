#include <WiFi.h>
#include <WiFiClient.h>
#include <WiFiServer.h>
#include <ArduinoJson.h>
#include "Ghost.h"

#define ssid "ghost"
#define password "12345678"

WiFiServer server(80);

void setupWiFi() {
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");
}

void startServer() {
  server.begin();
  Serial.println("Server started");
  Serial.println(WiFi.localIP());
}

Ghost handleClient() {
  WiFiClient client = server.available();
  if (!client) {
    return {"","",0,0};
  }

  while (!client.available()) {
    delay(1);
  }

  String request = client.readStringUntil('\r');
  client.flush();

  if (request.indexOf("POST /") != -1) {
    StaticJsonDocument<200> jsonBuffer;
    DeserializationError error = deserializeJson(jsonBuffer, request);
    if (error) {
      Serial.print(F("deserializeJson() failed with code "));
      Serial.println(error.c_str());
      return {"","",0,0};
    }

    
    // Use the values in the JSON object
    const char * name = jsonBuffer["Name"];
    const char * gType = jsonBuffer["Type"];
    uint8_t location = jsonBuffer["Location"];
    uint8_t activity = jsonBuffer["Activity"];

    Ghost ghost = {name, gType, location, activity};

    return ghost;
  }

  client.stop();
}


