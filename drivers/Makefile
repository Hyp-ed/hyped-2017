OBJS = i2c.o gpio.o mpu6050.o vl6180.o battery.o raspberry_pi.o quaternion.o motion_tracker.o hydraulics.o serialData.o
CC = g++
DEBUG = -g
CFLAGS = -std=c++11 -Wall -c -O3 $(DEBUG)
LFLAGS = -Wall -latomic -lpthread -lwiringPi $(DEBUG)

all : main integrator demo-motion_tracker demo-vl6180 demo-raspberry_pi demo-battery proxi-hydro

main : $(OBJS) main.o
	$(CC) $(OBJS) $(LFLAGS) main.o -o main

integrator : $(OBJS) integrator.o
	$(CC) $(OBJS) $(LFLAGS) integrator.o -o integrator

demo-motion_tracker : $(OBJS) demo-motion_tracker.o
	$(CC) $(OBJS) $(LFLAGS) -lncurses demo-motion_tracker.o -o demo-motion_tracker

demo-vl6180 : $(OBJS) demo-vl6180.o
	$(CC) $(OBJS) $(LFLAGS) -lncurses demo-vl6180.o -o demo-vl6180

proxi-hydro : $(OBJS) proxi-hydro.o
	$(CC) $(OBJS) $(LFLAGS) -lncurses proxi-hydro.o -o proxi-hydro

demo-raspberry_pi : raspberry_pi.o demo-raspberry_pi.o
	$(CC) raspberry_pi.o $(LFLAGS)  -lncurses demo-raspberry_pi.o -o demo-raspberry_pi

demo-battery : demo-battery.o battery.o i2c.o
	$(CC) $(LFLAGS) i2c.o battery.o demo-battery.o -lncurses -o demo-battery


main.o : main.cpp mpu6050.hpp i2c.hpp
	$(CC) $(CFLAGS) main.cpp

integrator.o : integrator.cpp mpu6050.hpp i2c.hpp vector3d.hpp
	$(CC) $(CFLAGS) integrator.cpp

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


motion_tracker.o : motion_tracker.hpp motion_tracker.cpp interfaces.hpp data_point.hpp quaternion.hpp vector3d.hpp
	$(CC) $(CFLAGS) motion_tracker.cpp

quaternion.o : quaternion.hpp quaternion.cpp vector3d.hpp
	$(CC) $(CFLAGS) quaternion.cpp

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
	rm *.o main integrator demo-motion_tracker demo-vl6180 demo-raspberry_pi demo-battery proxi-hydro

