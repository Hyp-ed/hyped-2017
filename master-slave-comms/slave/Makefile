CC = g++
CFLAGS = -std=c++11 -Wall -c -O3
LFLAGS = -Wall -lpthread -lwiringPi

#all: 
#	g++ -Wall -o slave -I ../../ slave.cpp -std=c++11 -lpthread -fpermissive

slave : drivers slave.o NetworkSlave.o
	$(CC) $(LFLAGS) ../../drivers/i2c.o ../../drivers/gpio.o ../../drivers/vl6180.o NetworkSlave.o slave.o -o slave

slave1 : drivers slave1.o NetworkSlave.o
	$(CC) $(LFLAGS) ../../drivers/i2c.o ../../drivers/gpio.o ../../drivers/vl6180.o NetworkSlave.o slave1.o -o slave1

slave2 : drivers slave2.o NetworkSlave.o
	$(CC) $(LFLAGS) ../../drivers/i2c.o ../../drivers/gpio.o ../../drivers/vl6180.o NetworkSlave.o slave2.o -o slave2

slave3 : drivers slave3.o NetworkSlave.o
	$(CC) $(LFLAGS) ../../drivers/i2c.o ../../drivers/gpio.o ../../drivers/vl6180.o NetworkSlave.o slave3.o -o slave3

slave4 : drivers slave4.o NetworkSlave.o
	$(CC) $(LFLAGS) ../../drivers/i2c.o ../../drivers/gpio.o ../../drivers/vl6180.o NetworkSlave.o slave4.o -o slave4


.PHONY : drivers
drivers :
	cd ../../drivers && make i2c.o gpio.o vl6180.o


slave.o : slave.cpp NetworkSlave.hpp
	$(CC) $(CFLAGS) -I ../../ slave.cpp

slave1.o : slave1.cpp NetworkSlave.hpp
	$(CC) $(CFLAGS) -I ../../ slave1.cpp

slave2.o : slave2.cpp NetworkSlave.hpp
	$(CC) $(CFLAGS) -I ../../ slave2.cpp

slave3.o : slave3.cpp NetworkSlave.hpp
	$(CC) $(CFLAGS) -I ../../ slave3.cpp

slave4.o : slave4.cpp NetworkSlave.hpp
	$(CC) $(CFLAGS) -I ../../ slave4.cpp

serialData.o : serialData.c serialData.h
	gcc -Wall -c -O3 serialData.c

NetworkSlave.o : NetworkSlave.cpp NetworkSlave.hpp
	$(CC) $(CFLAGS) NetworkSlave.cpp

hydraulics.o : hydraulics.cpp hydraulics.hpp serialData.h
	$(CC) $(CFLAGS) -I ../../ hydraulics.cpp

.PHONY : clean
clean :
	rm *.o
	rm slave

