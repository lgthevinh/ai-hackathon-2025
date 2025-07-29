#pragma once
#include <Arduino.h>

#define BAUDRATE 115200
#define MAX_DATA_SIZE 16

enum message_type_t {
  MSG_TYPE_MCMD = 0x01,
  MSG_TYPE_SCMD = 0x02,
  MSG_TYPE_LINE = 0x03,
  MSG_TYPE_RFID = 0x04,

  MSG_TYOE_CUSTOM = 0x10,
};
