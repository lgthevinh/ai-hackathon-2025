#include <Adafruit_PWMServoDriver.h>

#include <Arduino.h>

#include "robot_types.h"
#include "CommandListener.h"

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

void onCommand(message_type_t type, const uint8_t* data, size_t length) {
    if (type == MSG_TYPE_MCMD) {  
        pwm.setPin(15, 4000);
        Serial.print(0x01);
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