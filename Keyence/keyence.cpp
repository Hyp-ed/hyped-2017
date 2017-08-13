#include "keyence.hpp"
using namespace std;

keyence :: keyence(int &stripes)
{
	setUp();
	countStripes(stripes);
}

void keyence :: setUp()
{
	if (wiringPiSetup () == -1)
	{
    	fprintf (stdout, "Unable to start wiringPi\n") ;
    	//return 1 ;
	}

	pinMode(29, OUTPUT);
	pinMode(28, INPUT);

	digitalWrite(CTL_SIG, LOW);
    delay(3500);
    digitalWrite(CTL_SIG, HIGH);
    printf("\nSetup complete");	
}

void keyence :: countStripes(int &numStripes)
{
	while (1) 
	{
		current_state = digitalRead(28);
		printf("\noutput = %d", current_state);
		if (current_state == 0 && prev_state == 0)
		{
			prev_state = 1;
			//numStripes += 0;
			printf("\n Stripe started");
		}	
		else if (current_state == 0 && prev_state == 1)
		{
			prev_state = 1;
			printf("\n Stripe still present");
		}
		else if (current_state == 1 && prev_state == 1)
		{
			prev_state = 0;
			numStripes += 1;
			printf("\n Stripe finished. Stripe Count = %d", numStripes);
		}
  		//Change delay to vary the reading frequency
  		delayMicroseconds(1000);
  		
	}
}