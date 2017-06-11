
#include <stdio.h>
#include <pigpio.h>

#define SENSOR 7

int main(int argc, char *argv[])
{
	if (gpioInitialise() < 0)
   	{
      fprintf(stderr, "pigpio initialisation failed\n");
      return 1;
  	}
	
	gpioSetMode(SENSOR, PI_INPUT);

	printf("Keyence Sensor Test\n");
	
	int currentState = 0, prevState = 0;
	
	while (1)
	{
		//Read sensor state
		currentState = gpioRead(SENSOR);
		if (currentState && !prevState)
		{
			printf("Motion detected\n");
			prevState = 1;
		}
		else if (!currentState && prevState) 
		{
			printf("Ready\n");
			prevState = 0;
		}
		
		char c = getchar();
		if (c == "Q" || c == "q") break;
	}
	
	gpioTerminate();
	return 0;	
}



















