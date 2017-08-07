#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "serialData.h"

int main(int argc, char const *argv[])
{
	printf("1");
	int fd = openData();
	
	printf("%f\n ", getData(fd, "current"));
	printf("%f\n ", getData(fd, "cell1V"));
	printf("%f\n ", getData(fd, "big_battery_voltage"));
	printf("%f\n ", getData(fd, "big_battery_temp"));
	printf("%f\n ", getData(fd, "small_battery_voltage"));
	printf("%f\n ", getData(fd, "small_battery_temp"));
	printf("%f\n ", getData(fd, "pump_pressure"));
	printf("%f\n ", getData(fd, "accumulator_pressure"));
closeData(fd);
	return 0;
}