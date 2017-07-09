
import RPi.GPIO as GPIO
import time

GPIO.setmode(GPIO.BCM)

GPIO_PIR = 25
GPIO_EXTENABLE = 21


print ("Keyence Test")

GPIO.setup(GPIO_PIR, GPIO.IN)
GPIO.setup(GPIO_EXTENABLE, GPIO.OUT)


current_state = 0
previous_state = 0
numStripes = 0;

# THREE METHODS FOR SETTING SENSITIVITY OF THE KEYENCE SENSOR

# 2 point calibration (see manual) is listed as option "set1"
# Maximum sensitivty calibration (see manual) is listed as option "set2"
# Full auto calibration (see manual) is listed as option "set3"

string = raw_input('Define sensor calibration (set1, set2, set3)\n')

# 2 point calibration
if string in ['set1','Set1']:  
    GPIO.output(GPIO_EXTENABLE, GPIO.LOW)
    time.sleep(0.5)
    GPIO.output(GPIO_EXTENABLE, GPIO.HIGH)
    time.sleep(0.5)
    GPIO.output(GPIO_EXTENABLE, GPIO.LOW)
    time.sleep(0.5)
    GPIO.output(GPIO_EXTENABLE, GPIO.HIGH)
    
# Maximum sensitivity calibration. THIS IS THE PREFERRED CHOICE.
elif string in ['set2', 'Set2']:
    GPIO.output(GPIO_EXTENABLE, GPIO.LOW)
    time.sleep(3)
    GPIO.output(GPIO_EXTENABLE, GPIO.HIGH)

# Full auto calibration. Somewhat unreliable.
elif string in ['set3', 'Set3']:
    GPIO.output(GPIO_EXTENABLE, GPIO.LOW)
    time.sleep(4)
    GPIO.output(GPIO_EXTENABLE, GPIO.HIGH)


# Scan for the stripes. Should calibration option be included after this point?

try:
    while GPIO.input(GPIO_PIR) == 1:
        print ("Ready")
    while True:
            #string = raw_input() #('Define sensor calibration (set1, set2, set3)\n')
            #if string in ['set2', 'Set2']:
            #    GPIO.output(GPIO_EXTENABLE, GPIO.LOW)
             #   time.sleep(3)
              #  GPIO.output(GPIO_EXTENABLE, GPIO.HIGH)
                
            current_state = GPIO.input(GPIO_PIR)
            if current_state == 1 and previous_state == 0:
                print ("Stripe Detected")
                previous_state = 1
                numStripes = numStripes + 1
            elif current_state == 0 and previous_state == 1:
                print ("Ready")
                previous_state = 0
            time.sleep(0.001)
        
except KeyboardInterrupt:
    print ("Quit")
    print(numStripes)
    GPIO.cleanup()
