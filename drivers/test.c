#include <wiringPi.h>

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>


#define SOL_1 0    //physical pin 17 COMMENT OUT WHEN FUNCTION CALLING WORKS!
#define SOL_2 1 //physical pin 18
#define SOL_3 2 //pin 21
#define SOL_4 3         //pin 22
#define SOL_5 4 //pin 23
#define SOL_6 5 //pin 24
#define SOL_7 6 //pin 25
#define PUMP 7  //pin 4

#define LOW 0
#define HIGH 1



int main(int argc, char const *argv[])
{
	wiringPiSetup();


digitalWrite(SOL_1, LOW);
digitalWrite(SOL_2, LOW);
digitalWrite(SOL_3, LOW);
digitalWrite(SOL_4, LOW);
digitalWrite(SOL_5, LOW);
digitalWrite(SOL_6, LOW);
digitalWrite(SOL_7, LOW);
digitalWrite(PUMP, LOW);


delay(4000);
digitalWrite(SOL_1, HIGH);
digitalWrite(SOL_1, HIGH);
digitalWrite(SOL_2, HIGH);
digitalWrite(SOL_3, HIGH);
digitalWrite(SOL_4, HIGH);
digitalWrite(SOL_5, HIGH);
digitalWrite(SOL_6, HIGH);
digitalWrite(SOL_7, HIGH);
digitalWrite(PUMP, HIGH);
return 0;
}