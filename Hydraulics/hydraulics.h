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
#define SOL_5_R 4 //pin 23
#define SOL_6_R 5 //pin 24
#define SOL_7_R 6 //pin 25
#define PUMP_R 7  //pin 4



char frontrear[5];
char leftright[5];

int hold(char frontrear[], char leftright[]); //Holds brake 1 in place without affecting the operations of brake 2
int retract(char frontrear[], char leftright[]); //Retracts brake 1 without affecting the operations of brake 2
int extend(char frontrear[], char leftright[]); //Extends brake 1 without affecting the operations of brake 2 RELIES ON T$
int standby(char frontrear[]); //Shuts down the pump and holds both cylinders in place
int shutDown(char frontrear[]); //Shuts down the pump and releases both cylinders
int chargeAccumulators(char frontrear[], int pressure_nominal_accumulator); //Charges the accumulators
int startUp(char frontrear[]);// Retracts brakes and charges accumulators
int safetyCheck(); //Checks that all values are within the nominal range. Checks pump pressure, accumulator pressure, battery voltages and current draw, if any exceed nominal ranges, emergeny procedure will begin.



#endif