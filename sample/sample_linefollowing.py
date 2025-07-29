import RPi.GPIO as GPIO
import time

# --- Pin Setup ---
SENSOR_PINS = [17, 18, 27, 22, 23]  # Adjust these GPIO numbers to your wiring: left to right

GPIO.setmode(GPIO.BCM)
for pin in SENSOR_PINS:
    GPIO.setup(pin, GPIO.IN)

try:
    while True:
        sensor_states = [GPIO.input(pin) for pin in SENSOR_PINS]
        print("Sensor states:", sensor_states)
        time.sleep(0.1)
except KeyboardInterrupt:
    GPIO.cleanup()