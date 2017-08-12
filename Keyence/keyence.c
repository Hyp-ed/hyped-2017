#include "keyence.h"

// Sending the control signal
void keyenceSetup()
{
    int j = 0;
    while (j != 1)
    {
        digitalWrite(CTL_SIG, LOW);
        delay(3500);
        digitalWrite(CTL_SIG, HIGH);
        printf("\nSetup complete");
        j++;
    }
}

int count_stripe(int *curr_state, int *prev_state, int *numStr)
{
    *curr_state = digitalRead(28);
	printf("\noutput = %d", *curr_state);
	if (*curr_state == 0 && *prev_state == 0)
	{
		prev_state = 1;
		numStr += 0;
		printf("\n Stripe started");
	}
	else if (*curr_state == 0 && *prev_state == 1)
	{
		*prev_state = 1;
		printf("\n Stripe still present");
	}
	else if (*curr_state == 1 && *prev_state == 1)
	{
		*prev_state = 0;
		numStr += 1;
		printf("\n Stripe finished.");
	}
	return *numStr;
}
