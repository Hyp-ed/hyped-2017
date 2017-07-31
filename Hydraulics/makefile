OBJS = i2c.o gpio.o  vl6180.o 
CC = g++
DEBUG = -g
CFLAGS = -std=c++11 -Wall -c -O3 $(DEBUG)
LFLAGS = -Wall -latomic -lpthread -lwiringPi $(DEBUG)

all : demo-vl6180

demo-vl6180 : $(OBJS) demo-vl6180.o
	$(CC) $(OBJS) $(LFLAGS) -lncurses demo-vl6180.o -o demo-vl6180

demo-vl6180.o : demo-vl6180.cpp ../drivers/vl6180.hpp ../drivers/gpio.hpp ../drivers/i2c.hpp
	$(CC) $(CFLAGS) demo-vl6180.cpp


vl6180.o : ../drivers/vl6180.hpp ../drivers/vl6180.cpp ../drivers/gpio.hpp ../drivers/i2c.hpp
	$(CC) $(CFLAGS) ../drivers/vl6180.cpp

gpio.o : ../drivers/gpio.hpp ../drivers/gpio.cpp
	$(CC) $(CFLAGS) ../drivers/gpio.cpp

i2c.o : ../drivers/i2c.hpp ../drivers/i2c.cpp
	$(CC) $(CFLAGS) ../drivers/i2c.cpp

##clean :
##	rm *.o main integrator test_motion_tracker demo-vl6180 demo-raspberry_pi demo-battery



