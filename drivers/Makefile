OBJS = i2c.o gpio.o mpu6050.o vl6180.o battery.o raspberry_pi.o quaternion.o motion_tracker.o hydraulics.o serialData.o
CC = g++
DEBUG = -g
CFLAGS = -std=c++11 -Wall -c -O3 $(DEBUG)
LFLAGS = -Wall -latomic -lpthread -lwiringPi -lncurses $(DEBUG)

all : demo-mpu6050 demo-motion_tracker demo-vl6180 demo-raspberry_pi demo-battery proxi-hydro

demo-mpu6050 : demo-mpu6050.o mpu6050.o i2c.o
	$(CC) i2c.o mpu6050.o $(LFLAGS) demo-mpu6050.o -o demo-mpu6050

demo-motion_tracker : demo-motion_tracker.o motion_tracker.o quaternion.o mpu6050.o vl6180.o keyence.o gpio.o i2c.o
	$(CC) i2c.o gpio.o keyence.o vl6180.o mpu6050.o quaternion.o motion_tracker.o $(LFLAGS) demo-motion_tracker.o -o demo-motion_tracker

demo-vl6180 : demo-vl6180.o vl6180.o gpio.o i2c.o
	$(CC) i2c.o gpio.o vl6180.o $(LFLAGS) demo-vl6180.o -o demo-vl6180

proxi-hydro : $(OBJS) proxi-hydro.o 
	$(CC) $(OBJS) $(LFLAGS) -lncurses proxi-hydro.o -o proxi-hydro

demo-raspberry_pi : raspberry_pi.o demo-raspberry_pi.o
	$(CC) raspberry_pi.o $(LFLAGS) demo-raspberry_pi.o -o demo-raspberry_pi

demo-battery : demo-battery.o battery.o i2c.o
	$(CC) i2c.o battery.o $(LFLAGS) demo-battery.o -o demo-battery

demo-keyence : demo-keyence.o keyence.o gpio.o
	$(CC) gpio.o keyence.o $(LFLAGS) demo-keyence.o -o demo-keyence

demo-hydraulics : demo-hydraulics.o hydraulics.o gpio.o
	$(CC) gpio.o hydraulics.o $(LFLAGS) demo-hydraulics.o -o demo-hydraulics

demo-network_proxi : demo-network_proxi.o network_proxi.o master
	$(CC) ../master-slave-comms/master/NetworkMaster.o network_proxi.o $(LFLAGS) demo-network_proxi.o -o demo-network_proxi


.PHONY : master
master :
	cd ../master-slave-comms/master/ && make NetworkMaster.o


demo-mpu6050.o : demo-mpu6050.cpp mpu6050.hpp i2c.hpp
	$(CC) $(CFLAGS) demo-mpu6050.cpp

demo-motion_tracker.o : demo-motion_tracker.cpp mpu6050.hpp i2c.hpp vector3d.hpp motion_tracker.hpp quaternion.hpp
	$(CC) $(CFLAGS) demo-motion_tracker.cpp

demo-vl6180.o : demo-vl6180.cpp vl6180.hpp gpio.hpp i2c.hpp
	$(CC) $(CFLAGS) demo-vl6180.cpp

proxi-hydro.o : proxi-hydro.cpp vl6180.hpp gpio.hpp i2c.hpp hydraulics.c hydraulics.h serialData.c serialData.h
	$(CC) $(CFLAGS) proxi-hydro.cpp

demo-raspberry_pi.o : demo-raspberry_pi.cpp raspberry_pi.hpp
	$(CC) $(CFLAGS) demo-raspberry_pi.cpp

demo-battery.o : demo-battery.cpp battery.hpp i2c.hpp
	$(CC) $(CFLAGS) demo-battery.cpp

demo-keyence.o : demo-keyence.cpp keyence.hpp gpio.hpp
	$(CC) $(CFLAGS) demo-keyence.cpp

demo-hydraulics.o : demo-hydraulics.cpp hydraulics.hpp
	$(CC) $(CFLAGS) demo-hydraulics.cpp

demo-network_proxi.o : demo-network_proxi.cpp network_proxi.hpp
	$(CC) $(CFLAGS) -I ../ demo-network_proxi.cpp


hydraulics.o : hydraulics.cpp hydraulics.hpp gpio.hpp
	$(CC) $(CFLAGS) hydraulics.cpp

network_proxi.o : network_proxi.hpp network_proxi.cpp interfaces.hpp
	$(CC) $(CFLAGS) -I ../ network_proxi.cpp

motion_tracker.o : motion_tracker.hpp motion_tracker.cpp interfaces.hpp data_point.hpp quaternion.hpp vector3d.hpp
	$(CC) $(CFLAGS) -I /usr/local/include/eigen3/ motion_tracker.cpp

quaternion.o : quaternion.hpp quaternion.cpp vector3d.hpp
	$(CC) $(CFLAGS) quaternion.cpp

keyence.o : keyence.hpp keyence.cpp gpio.hpp
	$(CC) $(CFLAGS) keyence.cpp

raspberry_pi.o : raspberry_pi.hpp raspberry_pi.cpp
	$(CC) $(CFLAGS) raspberry_pi.cpp

battery.o : battery.hpp battery.cpp i2c.hpp
	$(CC) $(CFLAGS) battery.cpp

vl6180.o : vl6180.hpp vl6180.cpp gpio.hpp i2c.hpp interfaces.hpp
	$(CC) $(CFLAGS) vl6180.cpp

mpu6050.o : mpu6050.hpp mpu6050.cpp i2c.hpp vector3d.hpp interfaces.hpp
	$(CC) $(CFLAGS) mpu6050.cpp

gpio.o : gpio.hpp gpio.cpp
	$(CC) $(CFLAGS) gpio.cpp

i2c.o : i2c.hpp i2c.cpp
	$(CC) $(CFLAGS) i2c.cpp

hydraulic_control.o : hydraulics.h hydraulics.c
	g++ -std=c++11 -Wall -c hydraulics.c -lwiringPi

serialData.o : serialData.h serialData.c
	g++ -std=c++11 -Wall -c serialData.c -lwiringPi


clean :
	rm -f *.o demo-mpu6050 demo-motion_tracker demo-vl6180 demo-raspberry_pi demo-battery proxi-hydro

