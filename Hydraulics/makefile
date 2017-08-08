OBJS = i2c.o gpio.o  vl6180.o 
CC = g++
GCC = gcc
DEBUG = -g
CFLAGS = -std=c++11 -Wall -c -O3 $(DEBUG)
LFLAGS = -Wall -latomic -lpthread -lwiringPi $(DEBUG)
EFLAGS = -Wall -lwiringPi


all :  


vl6180.o : ../drivers/vl6180.hpp ../drivers/vl6180.cpp ../drivers/gpio.hpp ../drivers/i2c.hpp
	$(CC) $(CFLAGS) ../drivers/vl6180.cpp

gpio.o : ../drivers/gpio.hpp ../drivers/gpio.cpp
	$(CC) $(CFLAGS) ../drivers/gpio.cpp


charge : charge.c 
	$(GCC) $(EFLAGS) ../drivers/serialData.c ../drivers/hydraulics.c ../drivers/serialData.h ../drivers/hydraulics.h -o charge

##clean :
##	rm *.o main integrator test_motion_tracker demo-vl6180 demo-raspberry_pi demo-battery



