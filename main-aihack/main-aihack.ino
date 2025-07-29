#include <Adafruit_PWMServoDriver.h>

#include <Arduino.h>

#include "robot_types.h"
#include "CommandListener.h"

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

// MCMD:
// MESSAGE_TYPE | NUMBER | DIR | PULSE (2 bytes)

// SCMD:
// MESSAGE_TYPE | NUMBER | ANGLE (2 bytes)

void onCommand(message_type_t type, const uint8_t* data, size_t length) {
    if (length < 3) {
        Serial.println("Invalid command length");
        return;
    }

    if (type == MSG_TYPE_MCMD) {  
        uint8_t number = data[0];
        uint8_t dir = data[1];
        int16_t pulse = data[2] | (data[3] << 8);

        Serial.print("Received MCMD: ");
        Serial.print("Type = ");        Serial.print(type);
        Serial.print(", Motor Number = ");
        Serial.print(number);
        Serial.print(", Direction = ");
        Serial.print(dir);
        Serial.print(", Pulse = ");
        Serial.println(pulse);
        
        // Implement control DC here
    } else if (type == MSG_TYPE_SCMD) {
        uint8_t number = data[0];
        int16_t pulse = data[2] | (data[3] << 8);

        Serial.print("Received SCMD: ");
        Serial.print("Type = ");
        Serial.print(type);
        Serial.print(", Servo Number = ");
        Serial.print(number);
        Serial.print(", Pulse = ");
        Serial.println(pulse);

        // Implement control servo here
    } else {
        Serial.println("Unknown command type");
    } 
    Serial.flush();
}

CommandListener cmdListener;

void setup() {
    cmdListener.begin();
    cmdListener.setHandler(onCommand);

    pwm.begin();
    pwm.setOscillatorFrequency(27000000);
    pwm.setPWMFreq(50);
}

void loop() {
    cmdListener.listen();
    delay(50);
}