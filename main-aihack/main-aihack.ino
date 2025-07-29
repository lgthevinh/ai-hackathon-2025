#include <Arduino.h>
#include "LineFollowing.h"

const uint8_t lineSensorPins[5] = {0, 1, 4, 5, 8}; // define Line following sensor pins out here in-order
LineFollowing lineFollower(lineSensorPins);

void setup() {
    Serial.begin(115200);
    lineFollower.begin();
}

void loop() {
    lineFollower.readSensors();
    uint8_t lineBits = lineFollower.getSensorBits();
    Serial.print("Sensor bits: 0b");
    for (int i = 4; i >= 0; --i) {
        Serial.print((lineBits >> i) & 1);
    }
    Serial.println();
    // Send lineBits via UART
    Serial.write(lineBits);
    delay(100);
}