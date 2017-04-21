OBJS = mpu6050.o i2c.o
CC = g++
DEBUG = -g
CFLAGS = -std=c++11 -Wall -c $(DEBUG)
LFLAGS = -Wall $(DEBUG)

all : mpu6050

mpu6050 : $(OBJS)
	$(CC) $(LFLAGS) $(OBJS) -o mpu6050

mpu6050.o : mpu6050.hpp mpu6050.cpp i2c.hpp
	$(CC) $(CFLAGS) mpu6050.cpp

i2c.o : i2c.hpp i2c.cpp
	$(CC) $(CFLAGS) i2c.cpp
