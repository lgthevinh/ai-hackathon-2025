#include "LineFollowing.h"

LineFollowing::LineFollowing(const uint8_t* sensorPins, uint8_t sensorCount): _pins(sensorPins), _count(sensorCount) {
  
}

void LineFollowing::begin() {
  for (uint8_t i = 0; i < _count; i++) {
    pinMode(_pins[i], INPUT);
  }
}

void LineFollowing::readSensors() {
  for (uint8_t i = 0; i < _count; i++) {
    _values[i] = digitalRead(_pins[i]);
  }
}

const bool* LineFollowing::getSensorValues() const {
  return _values;
}

int LineFollowing::getLinePosition() const {
  int weights[5] = {-2, -1, 0, 1, 2};
  int sum = 0, count = 0;
  for (uint8_t i = 0; i < _count; i++) {
    if (_values[i]) {
      sum += weights[i];
      count++;
    }
  }
  if (count == 0) return 0;
  return sum / count;
}

uint8_t LineFollowing::getSensorBits() const {
  uint8_t bits = 0;
  for (uint8_t i = 0; i < _count; i++) {
    if (_values[i]) bits |= (1 << i);
  }
  return bits; // e.g., 0b00000 to 0b11111
}