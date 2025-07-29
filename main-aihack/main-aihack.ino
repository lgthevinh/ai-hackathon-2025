#include <Arduino.h>

#include "robot_types.h"
#include "CommandListener.h"

void onCommand(message_type_t type, const uint8_t* data, size_t length) {
    Serial.print("Type: ");
    Serial.println(type, HEX);

    Serial.print("Data: ");
    for (size_t i = 0; i < length; ++i) {
        Serial.print(data[i], HEX);
        Serial.print(" ");
    }
    Serial.println();
    
    if (type == MSG_TYPE_MCMD) {  
        Serial.println("TEST");
    } 
}

CommandListener cmdListener;

void setup() {
    cmdListener.begin();
    cmdListener.setHandler(onCommand);
}

void loop() {
    cmdListener.listen();
    delay(50);
}