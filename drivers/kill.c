#include "hydraulics.h"




#define KILL 12
#define PUMP 7

int main(int argc, char const *argv[])
{
	wiringPiSetup();
	digitalWrite(KILL, HIGH);
	//chargeAccumulators("front", 50);
	shutDown("front");

	return 0;
}