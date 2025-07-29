import binascii
import serial
import struct
import time

# --- Configuration ---
SERIAL_PORT = 'COM11'      # Change to your serial port (e.g., '/dev/ttyUSB0' or 'COM3')
BAUDRATE = 115200

# --- Message values ---
MSG_TYPE = 0x01          # Example: MCMD
NUMBER = 0x07
PULSE = 0x0100  # Example: 4000 in decimal

# --- Compose message ---
# struct.pack with '<BBH' means: little-endian, 1 byte (MSG_TYPE), 1 byte (NUMBER), 2 bytes (PULSE)
msg_bytes = struct.pack('<BBH', MSG_TYPE, NUMBER, PULSE)

# --- Send over serial ---
with serial.Serial(SERIAL_PORT, BAUDRATE, timeout=1) as ser:
    print(f"Sending: {[hex(b) for b in msg_bytes]}")
    ser.write(msg_bytes)
    time.sleep(0.1)  # Give ESP time to process

    # Optionally read response
    if ser.in_waiting:
        response = ser.read(ser.in_waiting)
        
        print("Received response:", [hex(b) for b in response])
        if len(response) > 0:
            print("Response length:", len(response))
            if len(response) >= 4:
                msg_type, number, pulse = struct.unpack('<BBH', response[:4])
                print(f"Parsed - Type: {msg_type}, Number: {number}, Pulse: {pulse}")
            else:
                print("Response too short to parse")
        
        print("Response from ESP:", response.hex())
        
        ascii_str = binascii.unhexlify(response.hex()).decode()
        print(ascii_str)

print("Test message sent!")