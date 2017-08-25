CC = g++
CFLAGS = -std=c++11 -Wall -c -O3
LFLAGS = -Wall -lpthread -lwiringPi

master : master.o NetworkMaster.o
	$(CC) NetworkMaster.o $(LFLAGS) master.o -o master

master.o : master.cpp NetworkMaster.hpp
	$(CC) $(CFLAGS) master.cpp

NetworkMaster.o : NetworkMaster.cpp NetworkMaster.hpp
	$(CC) $(CFLAGS) NetworkMaster.cpp



