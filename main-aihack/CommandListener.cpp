#include "CommandListener.h"

CommandListener::CommandListener(HardwareSerial& serial)
  : _serial(serial), _handler(nullptr) {}

void CommandListener::begin(uint32_t baudrate) {
  _serial.begin(baudrate);
}

void CommandListener::setHandler(CommandHandler handler) {
  _handler = handler;
}

void CommandListener::listen() {
  if (_serial.available()) {
    int typeByte = _serial.read();
    if (typeByte < 0) return;
    _buffer[0] = (uint8_t)typeByte;

    size_t dataLen = 0;
    while (_serial.available() && dataLen < MAX_DATA_SIZE) {
      _buffer[1 + dataLen] = _serial.read();
      dataLen++;
    }

    if (_handler) {
      _handler((message_type_t)_buffer[0], &_buffer[1], dataLen);
    }
  }
}