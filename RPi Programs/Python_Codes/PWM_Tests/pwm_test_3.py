import RPi.GPIO as GPIO
import time

#Select pin layout as on board
GPIO.setmode(GPIO.BOARD)

#Set GPIO pin 12 and 16 as output
GPIO.setup(12, GPIO.OUT)
GPIO.setup(16, GPIO.OUT)

#Set these pins as PWM
p = GPIO.PWM(12,200)
q = GPIO.PWM(16,200)

#Define Delay
delay = 0.02
p.start(0)
q.start(0)

try:
	while True:
		for i in range(100):
			p.ChangeDutyCycle(i)
			time.sleep(delay)

		for j in range(100):
			q.ChangeDutyCycle(j)
			time.sleep(delay)
		
		for i in range(100):
			p.ChangeDutyCycle(100-i)
			time.sleep(delay)
		
		p.ChangeDutyCycle(0)

		for j in range(100):
			q.ChangeDutyCycle(100-j)
			time.sleep(delay)
			
		q.ChangeDutyCycle(0)


except KeyboardInterrupt:
	pass
p.stop()
GPIO.cleanup()
