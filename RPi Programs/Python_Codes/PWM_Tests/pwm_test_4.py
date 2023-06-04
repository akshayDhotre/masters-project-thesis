import RPi.GPIO as GPIO
import time

#Select pin layout as on board
GPIO.setmode(GPIO.BOARD)

#Set GPIO pin 12 and 16 as output
GPIO.setup(11, GPIO.OUT)


#Set these pins as PWM
p = GPIO.PWM(11,2000)


#Define Delay
delay = 0.01
p.start(0)


try:
	while True:
		for i in range(100):
			p.ChangeDutyCycle(i)
			time.sleep(delay)

		
		for i in range(100):
			p.ChangeDutyCycle(100-i)
			time.sleep(delay)
		
		p.ChangeDutyCycle(0)


except KeyboardInterrupt:
	pass
p.stop()
GPIO.cleanup()
