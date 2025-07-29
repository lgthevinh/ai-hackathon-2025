import gpiod
import time

# Change to your correct GPIO chip - usually "gpiochip0" on Pi 5
CHIP = "gpiochip0"
SENSOR_LINES = [17, 18, 27, 22, 23]  # BCM numbering

# Open chip and request lines as inputs
chip = gpiod.Chip(CHIP)
lines = chip.get_lines(SENSOR_LINES)
lines.request(consumer="line_following", type=gpiod.LINE_REQ_DIR_IN)

try:
    while True:
        sensor_states = lines.get_values()
        print("Sensor states:", sensor_states)
        time.sleep(0.1)
except KeyboardInterrupt:
    print("Exiting.")
finally:
    lines.release()