#include "keyence.h"
#include <errno.h>

int main(void)
{

// setup the library
if (wiringPiSetup () == -1)
  {
    fprintf (stdout, "Unable to start wiringPi: %s\n", strerror (errno)) ;
    return 1 ;
  }

        pinMode(29, OUTPUT); // pin 21 on the gpio expansion board
        pinMode(28, INPUT);  // pin 20 on the gpio expansion board

int curr_state = 0;
int prev_state = 0;
int numStr = 0;
int set_result = 0;
int i = 0;
int j =0;

// sets the setup pin HIGH
// Previously, was setting it to LOW
// Replace with LOW again if current version does not work
digitalWrite(29, HIGH);

// version with functions, not tested
/*
keyence_setup();
while(numStr <= 10)
{
    number_stripes = count_stripes(&curr_state, &prev_state, &numStr);
    delayMicroseconds(1000);
}
printf("\n %d stripes passed", number_stripes);
*/

// starting the setup
while(set_result != 1)
{
 digitalWrite(29, LOW);
 delay(3500);
 digitalWrite(29, HIGH);
 set_result = 1;
 printf("\nsetup complete");
}
printf("\nStarting count...");
delay(3000);

while(numStr < 20)
{
	curr_state = digitalRead(28);
	printf("\noutput = %d", curr_state);
	if (curr_state == 0 && prev_state == 0)
	{
		prev_state = 1;
		numStr += 0;
		printf("\n Stripe started");
	}
	else if (curr_state == 0 && prev_state == 1)
	{
		prev_state = 1;
		printf("\n Stripe still present");
	}
	else if (curr_state == 1 && prev_state == 1)
	{
		prev_state = 0;
		numStr += 1;
		printf("\n Stripe finished. Stripe Count = %d", numStr);
	}
  //Change delay to vary the reading frequency
  delayMicroseconds(1000);
  i++;

}
printf("\n Number of stripes is %d", numStr);
digitalWrite(29, HIGH);
return 0;
}


