from time import sleep
from mfrc522 import SimpleMFRC522

reader = SimpleMFRC522()

## Set string value to buffer
try:
    while True:
        id, text = reader.read()
        
        print(f"ID: {id}, Text: {text}")
             
        sleep(1)
except KeyboardInterrupt:
    GPIO.cleanup()
    raise
