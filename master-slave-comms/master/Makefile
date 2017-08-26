CC = g++
CFLAGS = -std=c++11 -Wall -c -O3
LFLAGS = -Wall -latomic -lpthread -lwiringPi

base : base.o BaseCommunicator.o drivers
	$(CC) $(LFLAGS) ../../drivers/i2c.o ../../drivers/gpio.o ../../drivers/keyence.o ../../drivers/mpu6050.o ../../drivers/quaternion.o ../../drivers/motion_tracker.o ../../drivers/raspberry_pi.o BaseCommunicator.o base.o -o base

.PHONY : drivers
drivers :
	cd ../../drivers && make i2c.o gpio.o keyence.o mpu6050.o quaternion.o motion_tracker.o raspberry_pi.o
	

master : master.o NetworkMaster.o
	$(CC) NetworkMaster.o $(LFLAGS) master.o -o master

base.o : base.cpp BaseCommunicator.hpp
	$(CC) $(CFLAGS) -I ../../ base.cpp

master.o : master.cpp NetworkMaster.hpp
	$(CC) $(CFLAGS) master.cpp

BaseCommunicator.o : BaseCommunicator.cpp BaseCommunicator.hpp
	$(CC) $(CFLAGS) BaseCommunicator.cpp

NetworkMaster.o : NetworkMaster.cpp NetworkMaster.hpp
	$(CC) $(CFLAGS) NetworkMaster.cpp

