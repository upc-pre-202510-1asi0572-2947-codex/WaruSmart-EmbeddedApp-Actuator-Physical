#include "WiFiManager.h"

WiFiManager::WiFiManager(const char* ssid, const char* password)
    : ssid(ssid), password(password) {}

void WiFiManager::connect() {
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.println("Esperando conexión...");
    }
    Serial.println("Conectado a Wi-Fi");
}

String WiFiManager::getLocalIP() {
    return WiFi.localIP().toString();
}
