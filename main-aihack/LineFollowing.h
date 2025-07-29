#pragma once
#include <Arduino.h>

class LineFollowing {
public:
    LineFollowing(const uint8_t* sensorPins, uint8_t sensorCount = 5);

    void begin();
    void readSensors();
    const bool* getSensorValues() const;
    int getLinePosition() const; // -2 to +2
    uint8_t getSensorBits() const; // 5-bit value

private:
    const uint8_t* _pins;
    uint8_t _count;
    bool _values[5];
};