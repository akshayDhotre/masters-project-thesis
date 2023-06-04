import time
import pigpio
LED_PIN1 = 17
LED_PIN2 = 18
#connect to pigpiod daemon
pi = pigpio.pi()
# setup pin as an output
pi.set_mode(LED_PIN1, pigpio.OUTPUT)
pi.set_mode(LED_PIN2, pigpio.OUTPUT)
 
# pi set frequency
pi.set_PWM_frequency(LED_PIN1, 100)
print(pi.get_PWM_frequency(LED_PIN1))
pi.set_PWM_frequency(LED_PIN2, 200)
print(pi.get_PWM_frequency(LED_PIN2))
while True:
  while True:
    # increase duty cycle by 5, it will speed up the motor
    # or will increase LED brightness
    for i in range(5, 100, 5):
        pi.set_PWM_dutycycle(LED_PIN1,i);time.sleep(0.1)
	
    for j in range(5, 200, 5):
        pi.set_PWM_dutycycle(LED_PIN2,i);time.sleep(0.5)
 
    # decrease duty cycle by 5, it will slow down the motor
    # or will decrease LED brightness
    for i in range(100, 5, -5):
        pi.set_PWM_dutycycle(LED_PIN1,i);time.sleep(0.1)

    for j in range(200, 5, -5):
        pi.set_PWM_dutycycle(LED_PIN2,i);time.sleep(0.5)
#cleanup
pi.set_mode(LED_PIN, pigpio.INPUT)
#disconnect
pi.stop()