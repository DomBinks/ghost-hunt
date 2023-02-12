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

void handleClient() {
  WiFiClient client = server.available();
  if (!client) {
    return;
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
      return;
    }

    // Use the values in the JSON object
    int x = jsonBuffer["x"];
    int y = jsonBuffer["y"];

    // Do something with the values
    Serial.print("x: ");
    Serial.println(x);
    Serial.print("y: ");
    Serial.println(y);
  }

  client.stop();
}


