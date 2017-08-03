#ifndef _hydraulic_control_h
#define _hydraulic_control_h

#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "serialData.h"


#define SOL_1_F 0    //physical pin 17
#define SOL_2_F 1 //physical pin 18
#define SOL_3_F 2 //pin 21
#define SOL_4_F 3         //pin 22
#define SOL_5_F 4 //pin 23
#define SOL_6_F 5 //pin 24
#define SOL_7_F 6 //pin 25
#define PUMP_F 7  //pin 4

#define SOL_1_R 0    //physical pin 17
#define SOL_2_R 1 //physical pin 18
#define SOL_3_R 2 //pin 21
#define SOL_4_R 3         //pin 22
#define SOL_5_R 24 //pin 19
#define SOL_6_R 25 //pin 26
#define SOL_7_R 6 //pin 25
#define PUMP_R 7  //pin 4


#define SOL_1 0    //physical pin 17 COMMENT OUT WHEN FUNCTION CALLING WORKS!
#define SOL_2 1 //physical pin 18
#define SOL_3 2 //pin 21
#define SOL_4 3         //pin 22
#define SOL_5 4 //pin 23
#define SOL_6 5 //pin 24
#define SOL_7 6 //pin 25
#define PUMP 7  //pin 4





void hold(char const frontrear[], char const leftright[]); //Holds brake 1 in place without affecting the operations of brake 2
void retract(char const frontrear[], char const leftright[]); //Retracts brake 1 without affecting the operations of brake 2
void extend(char const frontrear[], char const leftright[]); //Extends brake 1 without affecting the operations of brake 2 RELIES ON T$
void standby(char const frontrear[]); //Shuts down the pump and holds both cylinders in place
void shutDown(char const frontrear[]); //Shuts down the pump and releases both cylinders
void chargeAccumulators(char const frontrear[], int pressure_nominal_accumulator); //Charges the accumulators
void startUp(char const frontrear[]);// Retracts brakes and charges accumulators
void safetyCheck(char const frontrear[]); //Checks that all values are within the nominal range. Checks pump pressure, accumulator pressure, battery voltages and current draw, if any exceed nominal ranges, emergeny procedure will begin.



#endif
