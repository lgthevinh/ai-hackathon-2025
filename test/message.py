import struct

def parse_message(msg_bytes):
    """
    Parses bytes in the format: MSG_TYPE (1 byte), Number (1 byte), Pulse (2 bytes)
    Returns a tuple: (msg_type, number, pulse)
    """
    if len(msg_bytes) != 4:
        raise ValueError("Message must be exactly 4 bytes")
    msg_type, number, pulse_low, pulse_high = msg_bytes
    pulse = pulse_low | (pulse_high << 8)
    return msg_type, number, pulse

def test_parse_message():
    # Compose a test message
    msg_type = 0x01
    number = 0x01
    pulse = 0x1234  # 4660 in decimal

    # Pack into bytes: [MSG_TYPE][NUMBER][PULSE_L][PULSE_H]
    msg_bytes = struct.pack("BBH", msg_type, number, pulse)
    # struct.pack("BBH") is little-endian by default

    # Unpack for the test
    parsed = parse_message(msg_bytes)
    assert parsed[0] == msg_type, "Message type mismatch"
    assert parsed[1] == number, "Number mismatch"
    assert parsed[2] == pulse, "Pulse mismatch"

    print("Test passed!")

if __name__ == "__main__":
    test_parse_message()