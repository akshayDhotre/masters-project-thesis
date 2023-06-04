# code for indicating status of axes of accelerometer on LEDs

import smbus
import time
import os
import RPi.GPIO as GPIO

# Define a class called Accel
class Accel():
	myBus=""
	if GPIO.RPI_INFO['P1_REVISION'] == 1:
		myBus=0
	else:
		myBus=1
	b = smbus.SMBus(myBus)
	def setUp(self):
		self.b.write_byte_data(0x1D,0x16,0x55) # Setup the Mode
		self.b.write_byte_data(0x1D,0x10,0) # Calibrate
		self.b.write_byte_data(0x1D,0x11,0) # Calibrate
		self.b.write_byte_data(0x1D,0x12,0) # Calibrate
		self.b.write_byte_data(0x1D,0x13,0) # Calibrate
		self.b.write_byte_data(0x1D,0x14,0) # Calibrate
		self.b.write_byte_data(0x1D,0x15,0) # Calibrate
	def getValueX(self):
		return self.b.read_byte_data(0x1D,0x06)
	def getValueY(self):
		return self.b.read_byte_data(0x1D,0x07)
	def getValueZ(self):
		return self.b.read_byte_data(0x1D,0x08)

MMA7455 = Accel()
MMA7455.setUp()

for a in range(10000):
	x = MMA7455.getValueX()
	y = MMA7455.getValueY()
	z = MMA7455.getValueZ()
	print("X=", x)
	print("Y=", y)
	print("Z=", z)
	time.sleep(0.5)
	os.system("clear")


GPIO.setmode(GPIO.BCM)  # choose BCM or BOARD numbering schemes. I use BCM  
  
GPIO.setup(25, GPIO.OUT)# set GPIO 25 as output for white led  
GPIO.setup(24, GPIO.OUT)# set GPIO 24 as output for red led  

white = GPIO.PWM(25, 100)    # create object white for PWM on port 25 at 100 Hertz  
red = GPIO.PWM(24, 100)      # create object red for PWM on port 24 at 100 Hertz  
  
white.start(0)              # start white led on 0 percent duty cycle (off)  
red.start(100)              # red fully on (100%)  

pause_time = 0.01           # you can change this to slow down/speed up

try:  
    while True:  
        if (x < 100):
            white.ChangeDutyCycle(x)  
            red.ChangeDutyCycle(100 - x)  
            sleep(pause_time)  
	sleep (1)
        if (y < 100):
            white.ChangeDutyCycle(y)  
            red.ChangeDutyCycle(100 - y)  
            sleep(pause_time)  
  	sleep (1)
except KeyboardInterrupt:  
    white.stop()            # stop the white PWM output  
    red.stop()              # stop the red PWM output  
    GPIO.cleanup()          # clean up GPIO on CTRL+C exit  