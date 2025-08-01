# ai-hackathon-2025

# Line Following

The Line Following object is define to read line sensor of 5 pins. These are methods in this class:

### Method definitions

- `LineFollowing(const uint8_t* sensorPins, uint8_t sensorCount = 5)`: Constructor that initializes the line following object with the specified sensor pins and count. You don't have to pass the sensor count, it defaults to 5.
- `void begin()`: Initializes the line following sensors.
- `void readSensors()`: Reads the values from the line sensors and stores them in the `sensorValues` array.
- `int getLinePosition()`: Return from -2 to 2, where -2 means the line is on the left side, 0 means the line is centered, and 2 means the line is on the right side.
- `uint8_t getSensorBits()`: Returns the sensor values as a bitmask, where each bit represents the state of a sensor (1 for line detected, 0 for no line). For example, 0b00001 means the first sensor detects a line, and 0b00010 means the second sensor detects a line.

### Usage Example

```cpp
#include <Arduino.h>
#include "LineFollowing.h"

const uint8_t lineSensorPins[5] = {0, 1, 4, 5, 8}; // define Line following sensor pins out here in-order
LineFollowing lineFollower(lineSensorPins);

void setup() {
    Serial.begin(115200);
    lineFollower.begin();
}

void loop() {
    lineFollower.readSensors();
    uint8_t lineBits = lineFollower.getSensorBits();
    Serial.print("Sensor bits: 0b");
    for (int i = 4; i >= 0; --i) {
        Serial.print((lineBits >> i) & 1);
    }
    Serial.println();
    // Send lineBits via UART
    Serial.write(lineBits);
    delay(100);
}
```

# Command Listener

The Command Listener is used to handle incoming commands over UART. It listens for messages and calls the appropriate handler based on the message type. 

### Message types

- `MSG_TYPE_MCMD`: Motor command message type. 0x01
- `MSG_TYPE_SCMD`: Servo command message type. 0x02
- `MSG_TYPE_LINE`: Line command message type. 0x03
- `MSG_TYPE_RFID`: Robot command message type. 0x04

### Usage Example

This example shows how to set up a command listener that processes motor and servo commands:

```cpp
#include <Arduino.h>

#include "robot_types.h"
#include "CommandListener.h"

void doSomething() {
  // Implementation of the function
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

        Serial.print("Received MCMD: ");
        Serial.print("Type = ");        Serial.print(type);
        Serial.print(", Motor Number = ");
        Serial.print(number);
        Serial.print(", Direction = ");
        Serial.print(dir);
        Serial.print(", Pulse = ");
        Serial.println(pulse);
        
        // Implement control DC here
    } else if (type == MSG_TYPE_SCMD) {
        uint8_t number = data[0];
        int16_t pulse = data[2] | (data[3] << 8);

        Serial.print("Received SCMD: ");
        Serial.print("Type = ");
        Serial.print(type);
        Serial.print(", Servo Number = ");
        Serial.print(number);
        Serial.print(", Pulse = ");
        Serial.println(pulse);

        // Implement control servo here
    } else {
        Serial.println("Unknown command type");
    } 
    Serial.flush();
}

CommandListener cmdListener(Serial1);

void setup() {
  cmdListener.begin();
  cmdListener.setHandler(onCommand);
}

void loop() {
  cmdListener.listen();
  delay(50);
}
```

### Message payload

- For `MSG_TYPE_MCMD`, the payload is:
  - `uint8_t number`: Motor number (1-4)
  - `uint8_t dir`: Direction (0 for forward, 1 for backward)
  - `int16_t pulse`: Pulse width for the motor control

- For `MSG_TYPE_SCMD`, the payload is:
  - `uint8_t number`: Servo number (1-4)
  - `int16_t pulse`: Pulse width for the servo control

```
MCMD:
MESSAGE_TYPE | NUMBER | DIR | PULSE (2 bytes)

SCMD:
MESSAGE_TYPE | NUMBER | ANGLE (2 bytes)
```

### Send to ESP sample

```python
import binascii
import serial
import struct
import time

# --- Configuration ---
SERIAL_PORT = 'COM11'      # Change to your serial port (e.g., '/dev/ttyUSB0' or 'COM3')
BAUDRATE = 115200

# --- Message values ---
MSG_TYPE = 0x01          # Example: MCMD Motor Command
NUMBER = 0x04 # Example: Motor number (0x04 for motor 4) 
DIR = 0x01           # Example: Direction (0 for forward, 1 for backward)
PULSE = 0x0FA0  # Example: 4000 in decimal

# Map message bytes MSG_TYPE, NUMBER, DIR, PULSE
msg_bytes = struct.pack('<BBBH', MSG_TYPE, NUMBER, DIR, PULSE)

# --- Send over serial ---
with serial.Serial(SERIAL_PORT, BAUDRATE, timeout=1) as ser:
    print(f"Sending: {[hex(b) for b in msg_bytes]}")
    ser.write(msg_bytes)
    time.sleep(0.1)  # Give ESP time to process

    # Optionally read response
    if ser.in_waiting:
        response = ser.read(ser.in_waiting)
        ascii_str = binascii.unhexlify(response.hex()).decode()
        print("Response from ESP:", ascii_str)

print("Test message sent!")
```