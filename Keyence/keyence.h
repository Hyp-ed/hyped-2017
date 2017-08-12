

#ifndef _keyence_h
#define _keyence_h


#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define CTL_SIG 29
#define STR_IN 6

void keyenceSetup();
int count_stripe(int *curr_state, int *prev_state, int *numStr);

#endif
