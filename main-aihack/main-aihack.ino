#include <Arduino.h>

#include "robot_types.h"
#include "CommandListener.h"

void onCommand(message_type_t type, const uint8_t* data, size_t length) {
    if (type == MSG_TYPE_MCMD) {  
        
    } 
}

CommandListener cmdListener(Serial1);

void setup() {
    cmdListener.begin();
    cmdListener.setHandler(onCommand);
}

void loop() {
    cmdListener.listen();
    delay(50);
}