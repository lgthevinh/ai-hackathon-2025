from gpiozero import DigitalInputDevice
from time import sleep

# Define GPIO pins for your five sensors
sensor_pins = [5, 6, 13, 19, 26]  # Example pins, update as needed

# Create DigitalInputDevice objects for each sensor
sensors = [DigitalInputDevice(pin) for pin in sensor_pins]

print("Reading 5 line sensors. Press Ctrl+C to exit.")
try:
    while True:
        values = [sensor.value for sensor in sensors]
        print("Sensor values:", values)
        sleep(0.1)
except KeyboardInterrupt:
    print("Stopped.")