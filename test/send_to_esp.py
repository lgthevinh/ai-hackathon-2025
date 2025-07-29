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