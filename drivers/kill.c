#include "hydraulics.h"





#define PUMP 7

int main(int argc, char const *argv[])
{
	wiringPiSetup();
	//chargeAccumulators("front", 50);
	shutDown("front");

	return 0;
}