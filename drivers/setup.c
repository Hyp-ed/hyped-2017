#include "hydraulics.h"
#define PUMP 7
int main(int argc, char const *argv[])
{
	wiringPiSetup();
	chargeAccumulators("front", 50);
// int i = 0;
// while (i < 5)
// {
// 	digitalWrite(PUMP, LOW);
// 	delay(1000);
// 	digitalWrite(PUMP, HIGH);
// 	delay(2000);
// 	i++;
// }





	return 0;
}