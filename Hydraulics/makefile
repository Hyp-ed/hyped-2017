#!/bin/bash

sudo gcc -c -std=c11 hydraulics.h -lwiringPi
sudo gcc -c -std=c11 hydraulics.c -lwiringPi
sudo g++ -std=c11 -Wall -c -03 -gdemo-vl6180.cpp
sudo g++ i2c.o vl6180.o hydraulic_control.o  -Wall -latomic -lpthread -lwiringPi -g -lncurses demo-vl6180.o -o demo-vl6180


