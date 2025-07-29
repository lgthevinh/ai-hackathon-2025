# File: sample/sample_motor.py
import serial
import struct
import time
import binascii

class Controller:
    def __init__(self, port='COM12', baudrate=115200):
        self.port = port
        self.baudrate = baudrate
        self.ser = serial.Serial(port, baudrate, timeout=1)

    def control_motor(self, number, direction, pulse):
        # --- Message values ---
        MSG_TYPE = 0x01          # Example: MCMD Motor Command
        NUMBER = number           # Motor number
        DIR = direction           # Direction
        PULSE = pulse             # Pulse width

        # Map message bytes MSG_TYPE, NUMBER, DIR, PULSE
        msg_bytes = struct.pack('<BBBH', MSG_TYPE, NUMBER, DIR, PULSE)

        # --- Send over serial ---
        with self.ser as ser:
            print(f"Sending: {[hex(b) for b in msg_bytes]}")
            ser.write(msg_bytes)
            time.sleep(0.1)  # Give ESP time to process

            # Optionally read response
            if ser.in_waiting:
                response = ser.read(ser.in_waiting)
                ascii_str = binascii.unhexlify(response.hex()).decode()
                print("Response from ESP:", ascii_str)

        print("DC command sent!")
        
    def control_servo(self, number, angle):
        # Example for controlling a servo
        MSG_TYPE = 0x02          # Example: SCMD Servo Command
        NUMBER = number           # Servo number
        ANGLE = angle             # Angle in degrees

        # Map message bytes MSG_TYPE, NUMBER, ANGLE
        msg_bytes = struct.pack('<BBH', MSG_TYPE, NUMBER, ANGLE)

        with self.ser as ser:
            print(f"Sending: {[hex(b) for b in msg_bytes]}")
            ser.write(msg_bytes)
            time.sleep(0.1)
            
            if ser.in_waiting:
                response = ser.read(ser.in_waiting)
                ascii_str = binascii.unhexlify(response.hex()).decode()
                print("Response from ESP:", ascii_str)
                
        print("Servo command sent!")
        
if __name__ == "__main__":
    controller = Controller(port='/dev/ttyACM0', baudrate=115200)
    
    # Example usage
    controller.control_motor(number=1, direction=1, pulse=1000)  # Motor 1, forward, 1000ms pulse
    controller.control_servo(number=1, angle=90)  # Servo 1 to 90 degrees