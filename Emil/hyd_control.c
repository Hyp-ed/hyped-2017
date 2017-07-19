#include <wiringPi.h>

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

// pin definitions based on wiringPi library
// to see the pin numbering enter gpio readall
// in the terminal
#define SOL_1 0    //physical pin 17
#define SOL_2 1 //physical pin 18
#define SOL_3 3 //pin 22
#define SOL_4 7         //pin 4
#define SOL_5 5 //pin 24
#define SOL_6 2 //pin 27
#define SOL_7 4 //pin 23
#define PUMP 6  //pin 25

//global functions definitions
void hold_one();
void retract_one();
void extend_one();
void shutDown();
void chargeAccumulators();
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
        printf("\nShutting Down\n SAFE TO DEPRESSURISE ACCUMULATORS\n");
                shutDown();
        }
        else
        {
                printf("\nnothing to do\n");
        }
    }
c



delay(500);
hold_one();
return 0 ;

}


void hold_one()
{
    digitalWrite(SOL_1, HIGH);
    digitalWrite(SOL_2, LOW);
    digitalWrite(SOL_3, HIGH);
    digitalWrite(SOL_4, HIGH);
    digitalWrite(SOL_5, HIGH);
    digitalWrite(SOL_6, LOW);
    digitalWrite(SOL_7, HIGH);
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

// Complete the function with corresponding
// solenoids

void extend_one()
{
    digitalWrite(SOL_1, HIGH);
    digitalWrite(SOL_2, HIGH);
    digitalWrite(SOL_3, HIGH);
    digitalWrite(SOL_4, HIGH);
    digitalWrite(SOL_5, HIGH);
    digitalWrite(SOL_6, HIGH);
    digitalWrite(SOL_7, HIGH);
    digitalWrite(PUMP, HIGH);
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
printf("ERROR, SAFETY MODE ENGAGED");
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

