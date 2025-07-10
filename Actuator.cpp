#include "Actuator.h"

Actuator::Actuator(int pin, CommandHandler* commandHandler)
    : pin(pin), handler(commandHandler) {}

void Actuator::handle(Command command) {
    if (handler != nullptr) {
        handler->handle(command);
    }
}

void Actuator::setHandler(CommandHandler* commandHandler) {
    handler = commandHandler;
}

void Actuator::poll() {
    DynamicJsonDocument doc(1024);
    doc["device_id"] = "waru-smart-001";

    String jsonPayload;
    serializeJson(doc, jsonPayload);

    HTTPClient http;
    http.begin("http://10.146.252.109:5000/api/v1/actuators/status");
    http.addHeader("Content-Type", "application/json");

    int httpResponseCode = http.POST(jsonPayload);

    if (httpResponseCode > 0) {
        String payload = http.getString();
        Serial.println("Respuesta del servidor: ");
        Serial.println(payload);

        DynamicJsonDocument responseDoc(1024);
        deserializeJson(responseDoc, payload);

        String action = responseDoc["action"];

        if (action == "irrigate") {
            activate(); 
            Serial.println("Actuador activado (Riego)");
        } else if (action == "deactivate") {
            deactivate();
            Serial.println("Actuador desactivado");
        }
    } else {
        Serial.print("Error en la solicitud HTTP. Código de respuesta: ");
        Serial.println(httpResponseCode);
    }

    http.end();
}

void Actuator::activate() {
    digitalWrite(pin, HIGH);
}

void Actuator::deactivate() {
    digitalWrite(pin, LOW);
}
