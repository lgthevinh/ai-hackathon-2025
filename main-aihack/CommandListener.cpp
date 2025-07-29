#include "CommandListener.h"

CommandListener::CommandListener() : _handler(nullptr) {}

void CommandListener::begin(uint32_t baudrate) {
    Serial.begin(baudrate);
}

void CommandListener::setHandler(CommandHandler handler) {
    _handler = handler;
}

void CommandListener::listen() {
    if (Serial.available() > 0) {
        // Read the type byte
        int typeByte = Serial.read();
        if (typeByte < 0) return;
        _buffer[0] = (uint8_t)typeByte;

        // Read up to MAX_DATA_SIZE bytes as data
        size_t dataLen = 0;
        while (Serial.available() > 0 && dataLen < MAX_DATA_SIZE) {
            int dataByte = Serial.read();
            if (dataByte < 0) break;
            _buffer[1 + dataLen] = (uint8_t)dataByte;
            dataLen++;
        }

        if (_handler) {
            _handler((message_type_t)_buffer[0], &_buffer[1], dataLen);
        }
    }
}