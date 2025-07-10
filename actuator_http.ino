#include <Arduino.h>
#include "WiFiManager.h"
#include "Actuator.h"

const char* ssid = "Galaxy A12 313E";
const char* password = "jpvm6020";

WiFiManager wifiManager(ssid, password);
Actuator actuator(23); 

void setup() {
  Serial.begin(115200);

  wifiManager.connect();
  Serial.print("IP del ESP32: ");
  Serial.println(wifiManager.getLocalIP());

  actuator.setHandler(&commandHandler);
}

void loop() {
  actuator.poll();

  delay(5000);
}
