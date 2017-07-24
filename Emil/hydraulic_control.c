/*
To do: fill the placeholders for pressure readings and proximity sensor readings
take the exponential averaging from the arduino and check if that is enough to get a reliable function, otherwise, add uncertaintes to the readings
Check the processing power that this will use and if it is too high, add a delay to the position variable


*/




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


#define pressure_reading_accumulator 50 //PLACEHOLDER FOR PRESSURE SENSOR READING
#define distance_one 50 //PLACEHOLDER FOR PROXIMITY SENSOR READING ARRAY ONE
#define distance_two 50 //PLACEHOLDER FOR PROXIMITY SENSOR READING ARRAY TWO
#define pressure_nominal_accumulator 75 // nominal pressure for accumulator(s) UNIT: BAR



#define pumpSpinup 400 //Spinup time for the pump when runing off load. This will occur before every operation that uses the pump, plan timing accordingly

//global functions definitions
void hold_one(); //Holds brake 1 in place without affecting the operations of brake 2
void hold_two(); //Holds brake 2 in place without affecting the operations of brake 1
void retract_one(); //Retracts brake 1 without affecting the operations of brake 2
void retract_two(); //Retracts brake 2 without affecting the operations of brake 1
void extend_one(); //Extends brake 1 without affecting the operations of brake 2 RELIES ON THE PUMP RUNNING THROUGH THE OPERATION
void extend_two(); //Extends brake 2 without affecting the operations of brake 1 RELIES ON THE PUMP RUNNING THROUGHOUT THE OPERATION
void standby(); //Shuts down the pump and holds both cylinders in place
void shutDown(); //Shuts down the pump and releases both cylinders
void chargeAccumulators(); //Charges the accumulators 
void startUp();// Retracts brakes and charges accumulators
int pressure_reading_accumulator();
int pressure_reading_pump();
int proximity_reading_one();
int proximity_reading_two();
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

standby();

	if (strcmp(argv[1], "position") == 0)
{
  int position = atoi(argv[2]);

digitalWrite(PUMP, LOW);
delay(pumpSpinup);
int i = 0;

while(i != 2)
{
	proximity_reading_one();
	proximity_reading_two();
	if (proxmity_one < position)
	{
		extend_one();
		i = 0;
	}

	else if (proximity_one > position)
	{
		retract_one();
		i = 0;

	}
	else if (proximity_one = position)
	{
		hold_one();
		i++
	}
	if (proximity_two < position)
	{
		extend_two();
		i = 0;
	}

	else if (proximity_two > position)
	{
		retract_two();
		i = 0;

	}
	else if (proximity_two = position)
	{
		hold_two();
		i++
	}
}

standby();


}
	
  	else if(strcmp(argv[1],"startup") == 0)
        {
        printf("\nCharging Accumulators\n");
                chargeAccumulators();
        }
    else if(strcmp(argv[1],"kill") == 0)
        {
        printf("\nShutting Down\n");
                shutDown();
        }
	else
	{
		printf("\nInvalid input\n");
	}

return 0 ;

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
    
}

void extend_one()
{
    digitalWrite(SOL_2, HIGH);
    digitalWrite(SOL_1, HIGH);
}
void extend_two()
{
    digitalWrite(SOL_6, HIGH);
    digitalWrite(SOL_4, HIGH);
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
printf("\nCHARGING ACCUMULATORS\n");   
while(pressure_reading_accumulator < pressure_nominal_accumulator) {
    digitalWrite(PUMP, LOW);
    delay(pumpSpinup);
    digitalWrite(SOL_1, HIGH);
    digitalWrite(SOL_2, HIGH);
    digitalWrite(SOL_3, LOW);
    digitalWrite(SOL_4, HIGH);
    digitalWrite(SOL_5, HIGH);
    digitalWrite(SOL_6, HIGH);
    digitalWrite(SOL_7, LOW);
    pressure_reading_accumulator();
}

    digitalWrite(SOL_1, HIGH);
    digitalWrite(SOL_2, HIGH);
    digitalWrite(SOL_3, HIGH);
    digitalWrite(SOL_4, HIGH);
    digitalWrite(SOL_5, HIGH);
    digitalWrite(SOL_6, HIGH);
    digitalWrite(SOL_7, HIGH);
    digitalWrite(PUMP, HIGH);
    printf("\nACCUMULATORS CHARGED!\n");
}

int pressure_reading_accumulator()
{
//PLACEHOLDER FOR READING THE ACCUMULATOR PRESSURE FROM THE SERIAL INPUT

return pressure_reading_accumulator;
}
int pressure_reading_pump()
{
//PLACEHOLDER FOR READING THE PUMP PRESSURE FROM THE SERIAL INPUT

return pressure_reading_pump;
}
int proximity_reading_one()
{
//	PLACEHOLDER FOR READING THE PROXIMITY SENSOR ONE
	return proximity_one;
}
int proximity_reading_two()
{
//	PLACEHOLDER FOR READING THE PROXIMITY SENSOR ONE
	return proximity_two;
}


