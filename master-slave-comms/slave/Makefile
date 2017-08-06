CC = g++
CFLAGS = -std=c++11 -Wall -c -O3
LFLAGS = -Wall -lpthread -lwiringPi

#all: 
#	g++ -Wall -o slave -I ../../ slave.cpp -std=c++11 -lpthread -fpermissive

slave : drivers slave.o NetworkSlave.o
	$(CC) $(LFLAGS) ../../drivers/i2c.o ../../drivers/gpio.o ../../drivers/vl6180.o NetworkSlave.o slave.o -o slave

.PHONY : drivers
drivers :
	cd ../../drivers && make i2c.o gpio.o vl6180.o

slave.o : slave.cpp NetworkSlave.hpp
	$(CC) $(CFLAGS) -I ../../ slave.cpp

NetworkSlave.o : NetworkSlave.cpp NetworkSlave.hpp
	$(CC) $(CFLAGS) NetworkSlave.cpp

.PHONY : clean
clean :
	rm *.o
	rm slave

