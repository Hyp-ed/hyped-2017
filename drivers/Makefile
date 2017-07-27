OBJS = i2c.o gpio.o mpu6050.o vl6180.o battery.o raspberry_pi.o motion_tracker.o
CC = g++
DEBUG = -g
CFLAGS = -std=c++11 -Wall -c -O3 $(DEBUG)
LFLAGS = -Wall -latomic -lpthread $(DEBUG)

all : main integrator test_motion_tracker demo-vl6180 demo-raspberry_pi demo-battery

main : $(OBJS) main.o
	$(CC) $(OBJS) $(LFLAGS) main.o -o main

integrator : $(OBJS) integrator.o
	$(CC) $(OBJS) $(LFLAGS) integrator.o -o integrator

test_motion_tracker : $(OBJS) test_motion_tracker.o
	$(CC) $(OBJS) $(LFLAGS) -lncurses test_motion_tracker.o -o test_motion_tracker

demo-vl6180 : $(OBJS) demo-vl6180.o
	$(CC) $(OBJS) $(LFLAGS) -lncurses demo-vl6180.o -o demo-vl6180

demo-raspberry_pi : raspberry_pi.o demo-raspberry_pi.o
	$(CC) raspberry_pi.o $(LFLAGS)  -lncurses demo-raspberry_pi.o -o demo-raspberry_pi

demo-battery : demo-battery.o battery.o i2c.o
	$(CC) $(LFLAGS) i2c.o battery.o demo-battery.o -lncurses -o demo-battery


main.o : main.cpp mpu6050.hpp i2c.hpp
	$(CC) $(CFLAGS) main.cpp

integrator.o : integrator.cpp mpu6050.hpp i2c.hpp vector3d.hpp
	$(CC) $(CFLAGS) integrator.cpp

test_motion_tracker.o : test_motion_tracker.cpp mpu6050.hpp i2c.hpp vector3d.hpp motion_tracker.hpp
	$(CC) $(CFLAGS) test_motion_tracker.cpp

demo-vl6180.o : demo-vl6180.cpp vl6180.hpp i2c.hpp
	$(CC) $(CFLAGS) demo-vl6180.cpp

demo-raspberry_pi.o : demo-raspberry_pi.cpp raspberry_pi.hpp
	$(CC) $(CFLAGS) demo-raspberry_pi.cpp

demo-battery.o : demo-battery.cpp battery.hpp i2c.hpp
	$(CC) $(CFLAGS) demo-battery.cpp


motion_tracker.o : motion_tracker.hpp motion_tracker.cpp interfaces.hpp data_point.hpp vector3d.hpp
	$(CC) $(CFLAGS) motion_tracker.cpp

raspberry_pi.o : raspberry_pi.hpp raspberry_pi.cpp
	$(CC) $(CFLAGS) raspberry_pi.cpp

battery.o : battery.hpp battery.cpp i2c.hpp
	$(CC) $(CFLAGS) battery.cpp

vl6180.o : vl6180.hpp vl6180.cpp i2c.hpp
	$(CC) $(CFLAGS) vl6180.cpp

mpu6050.o : mpu6050.hpp mpu6050.cpp i2c.hpp vector3d.hpp
	$(CC) $(CFLAGS) mpu6050.cpp

gpio.o : gpio.hpp gpio.cpp
	$(CC) $(CFLAGS) gpio.cpp

i2c.o : i2c.hpp i2c.cpp
	$(CC) $(CFLAGS) i2c.cpp

clean :
	rm *.o main integrator test_motion_tracker demo-vl6180 demo-raspberry_pi demo-battery

