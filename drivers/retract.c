#include "hydraulics.h"
int main(int argc, char const *argv[])
{
	wiringPiSetup();
	retract("front", "left");
	retract("front", "right");
	standby("front");

	return 0;
}