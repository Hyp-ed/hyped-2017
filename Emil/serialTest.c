#include "../drivers/serialData.h"
#include <unistd.h>


#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <wiringPi.h>
#include <wiringSerial.h>

int main(int argc, char const *argv[])
{
	printf("%f", getData("accumulator_pressure"));
	return 0;
}
