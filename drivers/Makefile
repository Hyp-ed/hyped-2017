OBJS = mpu6050.o i2c.o
CC = g++
DEBUG = -g
CFLAGS = -std=c++11 -Wall -c -O3 $(DEBUG)
LFLAGS = -Wall $(DEBUG)

all : main integrator

main : $(OBJS) main.o
	$(CC) $(LFLAGS) $(OBJS) main.o -o main

integrator : $(OBJS) integrator.o
	$(CC) $(LFLAGS) $(OBJS) integrator.o -o integrator

main.o : main.cpp mpu6050.hpp i2c.hpp
	$(CC) $(CFLAGS) main.cpp

integrator.o : integrator.cpp mpu6050.hpp i2c.hpp vector3d.hpp
	$(CC) $(CFLAGS) integrator.cpp

mpu6050.o : mpu6050.hpp mpu6050.cpp i2c.hpp vector3d.hpp
	$(CC) $(CFLAGS) mpu6050.cpp

i2c.o : i2c.hpp i2c.cpp
	$(CC) $(CFLAGS) i2c.cpp
