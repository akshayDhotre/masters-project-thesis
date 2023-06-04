import time
import RPi.GPIO as GPIO
#Select Bcm Pin layout
GPIO.setmode(GPIO.BCM)

#Set GPIO direction as output
GPIO.setup(17,GPIO.OUT)
GPIO.setup(27,GPIO.OUT)
GPIO.setup(22,GPIO.OUT)


GPIO.output(27, 1)
GPIO.output(17, 0)

try:
	while 1:
		p = GPIO.PWM(22,50)
		p.start(0)
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
