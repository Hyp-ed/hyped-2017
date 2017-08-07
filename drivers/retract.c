#include "hydraulics.h"
int main(int argc, char const *argv[])
{
	

	wiringPiSetup();
	pinMode(0, OUTPUT);
	pinMode(1, OUTPUT);
	pinMode(2, OUTPUT);
	pinMode(3, OUTPUT);
	pinMode(4, OUTPUT);
	pinMode(5, OUTPUT);
	pinMode(6, OUTPUT);
	pinMode(7, OUTPUT);
spinup("front");
	retract("front", "left");
//	retract("front", "right");
	delay(1000);
	hold("front", "left");
	delay(50);
	standby("front");
	//extend("front", "left");
	delay(5);
	standby("front");



	return 0;
}
