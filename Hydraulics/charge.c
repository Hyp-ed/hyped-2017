#include "../drivers/hydraulics.h"
#include <string.h>

int main(int argc, char const *argv[])
{
	wiringPiSetup();
	if (getData("current") == -1)
		printf("Current sensor not detected\n ");
		return -1;
	pinMode(0, OUTPUT);
	pinMode(1, OUTPUT);
	pinMode(2, OUTPUT);
	pinMode(3, OUTPUT);
	pinMode(4, OUTPUT);
	pinMode(5, OUTPUT);
	pinMode(6, OUTPUT);
	pinMode(7, OUTPUT);
	int p = atoi(argv[1]);

	pressure("front", p);



	return 0;
}
