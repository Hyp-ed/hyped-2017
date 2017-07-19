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
#define SOL_3 29	//pin 21
#define SOL_4 3		//pin 22
#define SOL_5 4	//pin 23
#define SOL_6 5	//pin 24
#define SOL_7 6	//pin 25
#define PUMP 7	//pin 4

//global functions definitions
void hold_one();
void hold_two();
void retract_one();
void retract_two();
void extend_one();
void extend_two();
void standby();
void shutDown();
void chargeAccumulators();
void test();
//main accepts an argument from the command line

int main ( int argc, char *argv[] )
{

if (wiringPiSetup () == -1)
    {exit (1) ;
}
pinMode (SOL_1, OUTPUT);
pinMode (SOL_2, OUTPUT);
pinMode (SOL_3, OUTPUT);
pinMode (SOL_4, OUTPUT);
pinMode (SOL_5, OUTPUT);
pinMode (SOL_6, OUTPUT);
pinMode (SOL_7, OUTPUT);
pinMode (PUMP, OUTPUT);

    if ( argc != 2 ) /* argc should be 2 for correct execution */
    {
        /* We print argv[0] assuming it is the program name */
        printf( "missing argument");
     //   shutDown();
    }
    else
    {

	if(strcmp(argv[1],"hold") == 0)
	{
		printf("\nholding the cylinder...\n");
		hold_one();
	}
	else if(strcmp(argv[1],"extend") == 0)
	{
		printf("\nextending the cylinder\n");
		extend_one();
	}
	else if(strcmp(argv[1],"retract") == 0)
	{
        printf("\nretracting the cylinder\n");
		retract_one();
	}

  	else if(strcmp(argv[1],"charge") == 0)
        {
        printf("\nCharging Accumulators\n");
                chargeAccumulators();
        }
    else if(strcmp(argv[1],"kill") == 0)
        {
        printf("\nShutting Down\n");
                shutDown();
        }
    else if(strcmp(argv[1],"test") == 0)
    {
        printf("\n1\n");
        test();
        printf("\n1\n");
    }
	else
	{
		printf("\nnothing to do\n");
	}
    }


delay(500);
shutDown();
return 0 ;

}

void test()
{
    printf("\nTurning all solenoids off\n")
    digitalWrite(SOL_1, HIGH);
    digitalWrite(SOL_2, HIGH);
    digitalWrite(SOL_3, HIGH);
    digitalWrite(SOL_4, HIGH);
    digitalWrite(SOL_5, HIGH);
    digitalWrite(SOL_6, HIGH);
    digitalWrite(SOL_7, HIGH);
    digitalWrite(PUMP, HIGH);
printf("\nturns on all solenoids to test which work\n");
    printf("\n1 HIGH\n");
    digitalWrite(SOL_1, LOW);
    delay(5000);
    printf("\n1 LOW\n");
    digitalWrite(SOL_1, HIGH);
    delay(1000);

    printf("\n2 HIGH\n");
    digitalWrite(SOL_2, LOW);
    delay(5000);
    printf("\n2 LOW\n");
    digitalWrite(SOL_2, HIGH);
    delay(1000);

        printf("\n3 HIGH\n");
    digitalWrite(SOL_3, LOW);
    delay(5000);
    printf("\n3 LOW\n");
    digitalWrite(SOL_3, HIGH);
    delay(1000);

        printf("\n4 HIGH\n");
    digitalWrite(SOL_4, LOW);
    delay(5000);
    printf("\n4 LOW\n");
    digitalWrite(SOL_4, HIGH);
    delay(1000);

        printf("\n5 HIGH\n");
    digitalWrite(SOL_5, LOW);
    delay(5000);
    printf("\n5 LOW\n");
    digitalWrite(SOL_5, HIGH);
    delay(1000);

        printf("\n6 HIGH\n");
    digitalWrite(SOL_6, LOW);
    delay(5000);
    printf("\n6 LOW\n");
    digitalWrite(SOL_6, HIGH);
    delay(1000);

        printf("\n7 HIGH\n");
    digitalWrite(SOL_7, LOW);
    delay(5000);
    printf("\n7 LOW\n");
    digitalWrite(SOL_7, HIGH);
    delay(1000);

        printf("\nPUMP HIGH\n");
    digitalWrite(PUMP, LOW);
    delay(5000);
    printf("\nPUMP LOW\n");
    digitalWrite(PUMP, HIGH);
    delay(1000);





}

void hold_one()
{
    digitalWrite(SOL_2, LOW);
    digitalWrite(SOL_1, HIGH);
}

void hold_two()
{
    digitalWrite(SOL_6, LOW);
    digitalWrite(SOL_4, HIGH);
}


void retract_one()
{
    digitalWrite(SOL_1, LOW);
    digitalWrite(SOL_2, LOW);
    digitalWrite(SOL_3, HIGH);
    digitalWrite(SOL_4, HIGH);
    digitalWrite(SOL_5, LOW);
    digitalWrite(SOL_6, HIGH);
    digitalWrite(SOL_7, LOW);
    digitalWrite(PUMP, LOW);
}

void retract_two()
{
    digitalWrite(SOL_1, HIGH);
    digitalWrite(SOL_2, HIGH);
    digitalWrite(SOL_3, HIGH);
    digitalWrite(SOL_4, LOW);
    digitalWrite(SOL_5, LOW);
    digitalWrite(SOL_6, LOW);
    digitalWrite(SOL_7, LOW);
    digitalWrite(PUMP, LOW);
}
// Complete the function with corresponding
// solenoids

void extend_one()
{
    digitalWrite(SOL_2, HIGH);
    digitalWrite(SOL_1, HIGH);
	//Fill in GPIOs as in functions above
}
void extend_two()
{
    digitalWrite(SOL_6, HIGH);
    digitalWrite(SOL_4, HIGH);
    //Fill in GPIOs as in functions above
}

void shutDown()
{
    digitalWrite(SOL_1, HIGH);
    digitalWrite(SOL_2, HIGH);
    digitalWrite(SOL_3, HIGH);
    digitalWrite(SOL_4, HIGH);
    digitalWrite(SOL_5, HIGH);
    digitalWrite(SOL_6, HIGH);
    digitalWrite(SOL_7, HIGH);
    digitalWrite(PUMP, HIGH);
    delay(1000);
    printf("\nProgram Complete\nSAFE TO DISCHARGE ACCUMULATORS\n");



}

void standby()
{
    digitalWrite(SOL_1, HIGH);
    digitalWrite(SOL_2, LOW);
    digitalWrite(SOL_3, HIGH);
    digitalWrite(SOL_4, HIGH);
    digitalWrite(SOL_5, HIGH);
    digitalWrite(SOL_6, LOW);
    digitalWrite(SOL_7, HIGH);
    digitalWrite(PUMP, HIGH);

}

void chargeAccumulators()
{
    digitalWrite(SOL_1, HIGH);
    digitalWrite(SOL_2, HIGH);
    digitalWrite(SOL_3, LOW);
    digitalWrite(SOL_4, HIGH);
    digitalWrite(SOL_5, HIGH);
    digitalWrite(SOL_6, HIGH);
    digitalWrite(SOL_7, LOW);
    digitalWrite(PUMP, LOW);
delay(2000);
    digitalWrite(SOL_1, HIGH);
    digitalWrite(SOL_2, HIGH);
    digitalWrite(SOL_3, HIGH);
    digitalWrite(SOL_4, HIGH);
    digitalWrite(SOL_5, HIGH);
    digitalWrite(SOL_6, HIGH);
    digitalWrite(SOL_7, HIGH);
    digitalWrite(PUMP, HIGH);
}
