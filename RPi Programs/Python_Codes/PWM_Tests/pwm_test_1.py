import time
import RPi.GPIO as GPIO
GPIO.setmode(GPIO.BCM)
GPIO.setup(18, GPIO.OUT)
p = GPIO.PWM(18, 50)
p.start(0)
try:
	while 1:
		for a in range (0,101,10):
			p.ChangeDutyCycle(a)
			time.sleep(0.1)
		for a in range (100,-1,-10):
			p.ChangeDutyCycle(a)
			time.sleep(0.1)
except keyboardInterrupt:
	pass
p.stop()
GPIO.cleanup
