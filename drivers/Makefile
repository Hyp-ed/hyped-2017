OBJS = main.o mpu6050.o i2c.o
CC = g++
DEBUG = -g
CFLAGS = -std=c++11 -Wall -c $(DEBUG)
LFLAGS = -Wall $(DEBUG)

all : main

main : $(OBJS)
	$(CC) $(LFLAGS) $(OBJS) -o main

main.o : main.cpp mpu6050.hpp i2c.hpp
	$(CC) $(CFLAGS) main.cpp

mpu6050.o : mpu6050.hpp mpu6050.cpp i2c.hpp
	$(CC) $(CFLAGS) mpu6050.cpp

i2c.o : i2c.hpp i2c.cpp
	$(CC) $(CFLAGS) i2c.cpp
