#include <Adafruit_PWMServoDriver.h>

#include <Arduino.h>

#include "robot_types.h"
#include "CommandListener.h"

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

// MCMD:
// MESSAGE_TYPE | NUMBER | DIR | PULSE (2 bytes)

// SCMD:
// MESSAGE_TYPE | NUMBER | ANGLE (2 bytes)

void motorControl(int number, int dir, int pulse) {
  if (dir == 1) {
    if (number == 1) {
      pwm.setPWM(M1_A, 0, 0);
      pwm.setPWM(M1_B, 0, pulse);
    }
    if (number == 2) {
      pwm.setPWM(M2_A, 0, 0);
      pwm.setPWM(M2_B, 0, pulse);
    }
    if (number == 3) {
      pwm.setPWM(M3_A, 0, 0);
      pwm.setPWM(M3_B, 0, pulse);
    }
    if (number == 4) {
      pwm.setPWM(M4_A, 0, 0);
      pwm.setPWM(M4_B, 0, pulse);
    }
  }
  else if (dir == 0) {
    if (number == 1) {
      pwm.setPWM(M1_A, 0, pulse);
      pwm.setPWM(M1_B, 0, 0);
    }
    if (number == 2) {
      pwm.setPWM(M2_A, 0, pulse);
      pwm.setPWM(M2_B, 0, 0);
    }
    if (number == 3) {
      pwm.setPWM(M3_A, 0, pulse);
      pwm.setPWM(M3_B, 0, 0);
    }
    if (number == 4) {
      pwm.setPWM(M4_A, 0, pulse);
      pwm.setPWM(M4_B, 0, 0);
    }
  }
}
void servoControl(int number, int pulse) {
    if (number == 1){
        pwm.setPWM(SERVO_1, 0, pulse);
    }
    if (number == 2){
        pwm.setPWM(SERVO_2, 0, pulse);
    }
    if (number == 3){
        pwm.setPWM(SERVO_3, 0, pulse);
    }
    if (number == 4){
        pwm.setPWM(SERVO_4, 0, pulse);
    }
}

void onCommand(message_type_t type, const uint8_t* data, size_t length) {
  if (length < 3) {
    Serial.println("Invalid command length");
    return;
  }

  if (type == MSG_TYPE_MCMD) {
    uint8_t number = data[0];
    uint8_t dir = data[1];
    int16_t pulse = data[2] | (data[3] << 8);

    Serial.printf("Received MCMD: Type = %d, Motor Number = %d, Direction = %d, Pulse = %d\n", type, number, dir, pulse);
    // Implement control DC here
    motorControl(number, dir, pulse);

  } else if (type == MSG_TYPE_SCMD) {
    uint8_t number = data[0];
    int16_t pulse = data[1] | (data[2] << 8);

    Serial.printf("Received SCMD: Type = %d, Servo Number = %d, Pulse = %d\n", type, number, pulse);
    // Implement control servo here
    servoControl(number, pulse);
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