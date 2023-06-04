import RPi.GPIO as GPIO
import time

#Select pin layout as on board
GPIO.setmode(GPIO.BOARD)

#Set GPIO pin 12 and 16 as output

GPIO.setup(16, GPIO.OUT)

#Set these pins as PWM
q = GPIO.PWM(16,20)

#Define Delay
delay = 0.02
q.start(0)

try:
	while True:

		for j in range(100):
			q.ChangeDutyCycle(j)
			time.sleep(delay)
		
		for j in range(100):
			q.ChangeDutyCycle(100-j)
			time.sleep(delay)
			
		q.ChangeDutyCycle(0)


except KeyboardInterrupt:
	pass
p.stop()
GPIO.cleanup()
