#pragma once
#include <Arduino.h>
#include "robot_types.h" // For message_type_t

typedef void (*CommandHandler)(message_type_t type, const uint8_t* data, size_t length);

class CommandListener {
public:
    CommandListener();

    void begin(uint32_t baudrate = 115200);
    void setHandler(CommandHandler handler);
    void listen();

    static const size_t BUFFER_SIZE = 1 + MAX_DATA_SIZE;

private:
    CommandHandler _handler;
    uint8_t _buffer[BUFFER_SIZE];
};