OBJS = i2c.o mpu6050.o motion_tracker.o
CC = g++
DEBUG = -g
CFLAGS = -std=c++11 -Wall -c -O3 $(DEBUG)
LFLAGS = -Wall -latomic -lpthread $(DEBUG)

all : main integrator test_motion_tracker

main : $(OBJS) main.o
	$(CC) $(OBJS) $(LFLAGS) main.o -o main

integrator : $(OBJS) integrator.o
	$(CC) $(OBJS) $(LFLAGS) integrator.o -o integrator

test_motion_tracker : test_motion_tracker.o
	$(CC) $(OBJS) $(LFLAGS) -lncurses test_motion_tracker.o -o test_motion_tracker

main.o : main.cpp mpu6050.hpp i2c.hpp
	$(CC) $(CFLAGS) main.cpp

integrator.o : integrator.cpp mpu6050.hpp i2c.hpp vector3d.hpp
	$(CC) $(CFLAGS) integrator.cpp

test_motion_tracker.o : test_motion_tracker.cpp mpu6050.hpp i2c.hpp vector3d.hpp motion_tracker.hpp
	$(CC) $(CFLAGS) test_motion_tracker.cpp

motion_tracker.o : motion_tracker.hpp motion_tracker.cpp interfaces.hpp data_point.hpp vector3d.hpp
	$(CC) $(CFLAGS) motion_tracker.cpp

mpu6050.o : mpu6050.hpp mpu6050.cpp i2c.hpp vector3d.hpp
	$(CC) $(CFLAGS) mpu6050.cpp

i2c.o : i2c.hpp i2c.cpp
	$(CC) $(CFLAGS) i2c.cpp
