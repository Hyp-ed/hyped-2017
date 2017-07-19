import RPi.GPIO as GPIO
import time

GPIO.setmode(GPIO.BCM)

SOLENOID_1 = 2
SOLENOID_2 = 3
SOLENOID_3 = 4
SOLENOID_4 = 7
SOLENOID_5 = 8
SOLENOID_6 = 9
SOLENOID_7 = 10
MOTOR = 11

GPIO.setup(SOLENOID_1, GPIO.OUT)
GPIO.setup(SOLENOID_2, GPIO.OUT)
GPIO.setup(SOLENOID_3, GPIO.OUT)
GPIO.setup(SOLENOID_4, GPIO.OUT)
GPIO.setup(SOLENOID_5, GPIO.OUT)
GPIO.setup(SOLENOID_6, GPIO.OUT)
GPIO.setup(SOLENOID_7, GPIO.OUT)

def extendOne():
    #abc

def extendTwo():
    #abc

def holdOne():
    GPIO.output(SOLENOID_1, GPIO.LOW)
    GPIO.output(SOLENOID_5, GPIO.LOW)
    GPIO.output(SOLENOID_7, GPIO.LOW)
    GPIO.output(MOTOR, GPIO.LOW)
    userInput = input("Re-extend? (Y/N)")
    if (userInput == 'Y'):
        GPIO.output(SOLENOID_2, GPIO.LOW)

def holdTwo():
    #abc

def retractOne():
    GPIO.output(MOTOR, GPIO.HIGH)
    GPIO.output(SOLENOID_5, GPIO.HIGH)
    GPIO.output(SOLENOID_1, GPIO.HIGH)
    GPIO.output(SOLENOID_2, GPIO.HIGH)
    GPIO.output(SOLENOID_7, GPIO.HIGH)

def retractTwo():
    #abc

def shutDown():
    #abc

response = -1

try:
    while (response != 0):
        print ("Please enter one of the following numbers, followed by the return key.\n")
        print ("1: Extend cylinder 1\n")
        print ("2: Extend cylinder 2\n")
        print ("3: Hold cylinder 1\n")
        print ("4: Hold cylinder 2\n")
        print ("5: Retract cylinder 1\n")
        print ("6: Retract cylinder 2\n")
        print ("0: ABORT\n")

        response = input()

        if (response == 1):
            extendOne()
        if (response == 2):
            extendTwo()
        if (response == 3):
            holdOne()
        if (response == 4):
            holdTwo()
        if (response == 5):
            retractOne()
        if (response == 6):
            retractTwo()
        if (response == 0):
            abort()
        
except KeyboardInterrupt:
    GPIO.output(RELAY_GREY, GPIO.LOW)
    GPIO.output(RELAY_BLUE, GPIO.LOW)
    GPIO.output(RELAY_PURPLE, GPIO.LOW)
    GPIO.output(RELAY_YELLOW, GPIO.LOW)
    GPIO.output(RELAY_ORANGE, GPIO.LOW)
    GPIO.output(RELAY_BROWN, GPIO.LOW)
    GPIO.output(RELAY_WHITE, GPIO.LOW)
    GPIO.cleanup()
    print ("SHUTDOWN")

