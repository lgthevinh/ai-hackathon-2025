#pragma once
#include <Arduino.h>

#define BAUDRATE 115200
#define MAX_DATA_SIZE 16

#define M1_A 2
#define M1_B 3
#define M2_A 4
#define M2_B 5
#define M3_A 7
#define M3_B 6
#define M4_A 1
#define M4_B 0
#define SERVO_1 12
#define SERVO_2 11
#define SERVO_3 10
#define SERVO_4 9
#define SERVO_5 8

enum message_type_t {
  MSG_TYPE_MCMD = 0x01,
  MSG_TYPE_SCMD = 0x02,
  MSG_TYPE_LINE = 0x03,
  MSG_TYPE_RFID = 0x04,

  MSG_TYOE_CUSTOM = 0x10,
};
