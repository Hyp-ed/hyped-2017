#ifndef _hydraulic_control_h
#define _hydraulic_control_h

#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "serialData.h"


#define SOL_1 0    //physical pin 17
#define SOL_2 1 //physical pin 18
#define SOL_3 2 //pin 21
#define SOL_4 3         //pin 22
#define SOL_5 4 //pin 23
#define SOL_6 5 //pin 24
#define SOL_7 6 //pin 25
#define PUMP 7  //pin 4

void hold_one(); //Holds brake 1 in place without affecting the operations of brake 2
void hold_two(); //Holds brake 2 in place without affecting the operations of brake 1
void retract_one(); //Retracts brake 1 without affecting the operations of brake 2
void retract_two(); //Retracts brake 2 without affecting the operations of brake 1
void extend_one(); //Extends brake 1 without affecting the operations of brake 2 RELIES ON T$
void extend_two(); //Extends brake 2 without affecting the operations of brake 1 RELIES ON T$
void standby(); //Shuts down the pump and holds both cylinders in place
void shutDown(); //Shuts down the pump and releases both cylinders
void chargeAccumulators(); //Charges the accumulators
void startUp();// Retracts brakes and charges accumulators
void safetyCheck(); //Checks that all values are within the nominal range. Checks pump pressure, accumulator pressure, battery voltages and current draw, if any exceed nominal ranges, emergeny procedure will begin.



#endif