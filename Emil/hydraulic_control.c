#include <wiringPi.h>

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

// pin definitions based on wiringPi library
// to see the pin numbering enter gpio readall
// in the terminal
#define SOL_1 0    //physical pin 17
#define SOL_2 1	//physical pin 18
#define SOL_3 2	//pin 21
#define SOL_4 3		//pin 22
#define SOL_5 4	//pin 23
#define SOL_6 5	//pin 24
#define SOL_7 6	//pin 25
#define PUMP 7	//pin 4


#define pumpSpinup 400 //Spinup time for the pump when runing off load. This will occur before every operation that uses the pump, plan timing accordingly
#define accumulatorChargingTime 2000 //Time that the accumulators will charge up SHOULD BE REPLACED BY A FUNCTION ONCE THE PRESSURE SENSOR IS WORKING






int main ( int argc, char *argv[] )
{
//printf("argc=\n");
//;
printf("\nargv\n");
printf("argv");
return 0;
}