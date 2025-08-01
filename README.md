# ai-hackathon-2025

# How to communicate from Raspberry Pi to Driver module (ESP32) through UART

The communication between the Raspberry Pi and the Driver module (ESP32) is done using UART. The ESP32 listens for incoming messages and processes them based on their type. Below are the details of how to set up and use this communication.

## Command Listener

The Command Listener is used to handle incoming commands over UART. It listens for messages and calls the appropriate handler based on the message type.

### Message types and payloads

- `MSG_TYPE_MCMD`: Motor command message type. 0x01
- `MSG_TYPE_SCMD`: Servo command message type. 0x02
- `MSG_TYPE_LINE`: Line command message type. 0x03 (currently not implemented)
- `MSG_TYPE_RFID`: Robot command message type. 0x04 (currently not implemented)

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

0x01 | 1-4 | 0-1 | 0-4000

SCMD:
MESSAGE_TYPE | NUMBER | PULSE (2 bytes)

0x02 | 1-4 | 0-4000
```


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

        Serial.printf("Received MCMD: Type = %d, Motor Number = %d, Direction = %d, Pulse = %d\n", type, number, dir, pulse);
        
        // Implement control DC here
    } else if (type == MSG_TYPE_SCMD) {
        uint8_t number = data[0];
        int16_t pulse = data[1] | (data[2] << 8);

        Serial.printf("Received SCMD: Type = %d, Servo Number = %d, Pulse = %d\n", type, number, pulse);
        
        // Implement control servo here
    } else {
        Serial.println("Unknown command type");
    }

    Serial.flush();
}
```

This code sets up a command listener that processes motor and servo commands. It checks the message type and extracts the relevant data, printing it to the serial console for debugging purposes. You can implement the actual control logic for motors and servos in the respective sections.

This example demonstrates how to handle incoming commands and provides a foundation for further development of the command processing logic. Make sure to adapt the `doSomething` function and the command handling logic according to your specific requirements.

### Control motors and servos from Raspberry Pi

To control motors and servos from the Raspberry Pi, you can send commands over UART using the defined message types. Below is an example of how to send a motor command from the Raspberry Pi:

```python
# File: sample/sample_motor.py

class Controller:
    def __init__(self, port='COM12', baudrate=115200):
        ...

    def control_motor(self, number, direction, pulse):
        ...
        
    def control_servo(self, number, pulse):
        ...
        
if __name__ == "__main__":
    controller = Controller(port='/dev/ttyACM0', baudrate=115200)
    
    # Example usage
    controller.control_motor(number=1, direction=1, pulse=1000)  # Motor 1, forward, 1000 pulse
    controller.control_servo(number=1, pulse=900) 
```

You can view the full implementation of the `Controller` class in the `sample/sample_motor.py` file. This class provides methods to control motors and servos by sending the appropriate commands over UART.

## Samples

You can find sample implementations in the `sample` directory. These samples demonstrate how to use the `Controller` class to send commands to the ESP32 Driver module.