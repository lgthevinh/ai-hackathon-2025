#pragma once
#include <Arduino.h>
#include "robot_types.h"

typedef void (*CommandHandler)(message_type_t type, const uint8_t* data, size_t length);

class CommandListener {
public:
    CommandListener(HardwareSerial& serial);

    void begin(uint32_t baudrate = BAUDRATE);
    void setHandler(CommandHandler handler);
    void listen();

    static const size_t BUFFER_SIZE = 1 + MAX_DATA_SIZE;

private:
    HardwareSerial& _serial;
    CommandHandler _handler;
    uint8_t _buffer[BUFFER_SIZE];
};