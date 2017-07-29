/*
 * serialTest.c:
 *	Very simple program to test the serial port. Expects
 *	the port to be looped back to itself
 *
 * Copyright (c) 2012-2013 Gordon Henderson. <projects@drogon.net>
 ***********************************************************************
 * This file is part of wiringPi:
 *	https://projects.drogon.net/raspberry-pi/wiringpi/
 *
 *    wiringPi is free software: you can redistribute it and/or modify
 *    it under the terms of the GNU Lesser General Public License as published by
 *    the Free Software Foundation, either version 3 of the License, or
 *    (at your option) any later version.
 *
 *    wiringPi is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *    GNU Lesser General Public License for more details.
 *
 *    You should have received a copy of the GNU Lesser General Public License
 *    along with wiringPi.  If not, see <http://www.gnu.org/licenses/>.
 ***********************************************************************
 */

// #include <unistd.h>


// #include <stdio.h>
// #include <string.h>
// #include <errno.h>
// #include <stdlib.h>
// #include <wiringPi.h>
// #include <wiringSerial.h>

// int getData();

#include "serialData.h"

float getData (char *data)
{
 int fd;

char serial[20]; //Looking for a serial connection 
if( access( "/dev/ttyACM0", F_OK ) != -1 ) {
  strcpy(serial,"/dev/ttyACM0");
//tty = fopen("/dev/ttyACM0","r");
printf("\nACM0\n");
} 

else if( access( "/dev/ttyACM1", F_OK ) != -1 ) {
  strcpy(serial,"/dev/ttyACM1");
//tty = fopen("/dev/ttyACM1","r");
printf("\nACM1\n");
} 

else if( access( "/dev/ttyACM2", F_OK ) != -1 ) {
//tty = fopen("/dev/ttyACM2","r");
 strcpy(serial,"/dev/ttyACM2");
printf("\nACM2\n");
} 

else
  {
 printf("error no serial connection detected");
 return -1;
  }
  if ((fd = serialOpen (serial, 115200)) < 0)
  {
    fprintf (stderr, "Unable to open serial device: %s\n", strerror (errno)) ;
    return 1;
  }

  if (wiringPiSetup () == -1)
  {
    fprintf (stdout, "Unable to start wiringPi: %s\n", strerror (errno)) ;
    return 1 ;
  }



char a[100];
int j = 0;
int b = 1;
serialPutchar (fd, b);
a[j]=(serialGetchar(fd));
while (serialDataAvail(fd)!= 0)
{
  j++;
  a[j] = serialGetchar(fd);
  delay(1);
}
//printf(a);

float current,cell1V,cell2V,cell3V,cell4V,cell5V,cell6V,cell7V,big_battery_voltage, big_battery_temp,
small_battery_voltage, small_battery_temp, pump_pressure, accumulator_pressure;
sscanf(a, "%f %f %f %f %f %f %f %f %f %f %f %f %f %f",&current,&cell1V,&cell2V,&cell3V,&cell4V,&cell5V,&cell6V,&cell7V,&big_battery_voltage, &big_battery_temp,
&small_battery_voltage, &small_battery_temp, &pump_pressure, &accumulator_pressure);
//printf("%d %d %d %d %d %d %d %d %d %d %d %d %d %d", current,cell1V,cell2V,cell3V,cell4V,cell5V,cell6V,cell7V,big_battery_voltage, big_battery_temp,
//small_battery_voltage, small_battery_temp, pump_pressure, accumulator_pressure);
int value = -1;
if (strcmp(data, "current")== 0)
{
  value = current;
}
else if (strcmp(data, "cell1V")== 0)
{
  value = cell1V;
}
else if (strcmp(data, "cell2V")== 0)
{
  value = cell2V;
}
else if (strcmp(data, "cell3V")== 0)
{
  value = cell3V;
}
else if (strcmp(data, "cell4V")== 0)
{
  value = cell4V;
}
else if (strcmp(data, "cell5V")== 0)
{
  value = cell5V;
}
else if (strcmp(data, "cell6V")== 0)
{
  value = cell6V;
}
else if (strcmp(data, "cell7V")== 0)
{
  value = cell7V;
}
else if (strcmp(data, "big_battery_voltage")== 0)
{
  value = big_battery_voltage;
}
else if (strcmp(data, "big_battery_temp")== 0)
{
  value = big_battery_temp;
}
else if (strcmp(data, "small_battery_voltage")== 0)
{
  value = small_battery_voltage;
}
else if (strcmp(data, "small_battery_temp")== 0)
{
  value = small_battery_temp;
}
else if (strcmp(data, "pump_pressure")== 0)
{
  value = pump_pressure;
}
else if (strcmp(data, "accumulator_pressure")== 0)
{
  value = accumulator_pressure;
}









  return value ;
}