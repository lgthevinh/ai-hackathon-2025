import spidev
import time

try:
    from rc522spi import RC522
except ImportError:
    print("Install the rc522spi library: pip install rc522spi")
    exit(1)

# Initialize RC522 SPI, RST pin is not required for basic reads if tied high
reader = RC522()

print("Place your RFID card near the RC522 reader...")

try:
    while True:
        id = reader.read_id()
        if id:
            print(f"Tag detected! UID: {id}")
        time.sleep(0.5)
except KeyboardInterrupt:
    print("Exiting RFID reader.")