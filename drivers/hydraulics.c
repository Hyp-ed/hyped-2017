/*
To do: fill the placeholders for pressure readings and proximity sensor readings
take the exponential averaging from the arduino and check if that is enough to get a reliable function, otherwise, add uncertaintes to the readings
Check the processing power that this will use and if it is too high, add a delay to the position variable


//by convention: cylinder 1 on the wiringdiagram is left!

*/

#include "hydraulics.h"

#define pumpSpinup 400 //Spinup time for the pump when runing off load. This will occur before every operation that uses the pump, plan timing accordingly
#define inrushLimit 100 // sets the limit of current draw for which the motor will be run off load. 

#define lowBAttery 23
#define overcurrent 150
#define overpressureAccumulators 100
#define overpressurePump 200


void spinup(char const frontrear[])
{
digitalWrite(PUMP, LOW);
delay(pumpSpinup);
digitalWrite(SOL_5, LOW);
digitalWrite(SOL_7, LOW);  
}

void hold(char const frontrear[], char const leftright[])
{
//     int SOL_1, SOL_2, SOL_3, SOL_4, SOL_5, SOL_6, SOL_7, PUMP; //SOLVE THE CHOSING OF SIDES! CAN BE DONE POST SHIPPING
// if (strcmp(frontrear, "front") == 0 )
// {
//     int SOL_1 = SOL_1_F;
//     int SOL_2 = SOL_2_F;
//     int SOL_3 = SOL_3_F;
//     int SOL_4 = SOL_4_F;
//     int SOL_5 = SOL_5_F;
//     int SOL_6 = SOL_6_F;
//     int SOL_7 = SOL_7_F;
//     int PUMP = PUMP_F;
// }
// else if (strcmp(frontrear, "rear")== 0 )
// {
//     int SOL_1 = SOL_1_R;
//     int SOL_2 = SOL_2_R;
//     int SOL_3 = SOL_3_R;
//     int SOL_4 = SOL_4_R;
//     int SOL_5 = SOL_5_R;
//     int SOL_6 = SOL_6_R;
//     int SOL_7 = SOL_7_R;
//     int PUMP = PUMP_R;
// }
// else 
// {
//     printf("invalid input");
    
// }

if (strcmp(leftright, "right")== 0)
{


    digitalWrite(SOL_2, LOW);
    digitalWrite(SOL_1, HIGH);
}
else if (strcmp(leftright, "left")== 0)
{


    digitalWrite(SOL_6, LOW);
    digitalWrite(SOL_4, HIGH);
}
else
{
    printf("invalid input");
  
}
    //safetyCheck();
}









void retract(char const frontrear[], char const leftright[])
{
//     int SOL_1, SOL_2, SOL_3, SOL_4, SOL_5, SOL_6, SOL_7, PUMP;
//    if (strcmp(frontrear, "front") == 0 )
// {
//     int SOL_1 = SOL_1_F;
//     int SOL_2 = SOL_2_F;
//     int SOL_3 = SOL_3_F;
//     int SOL_4 = SOL_4_F;
//     int SOL_5 = SOL_5_F;
//     int SOL_6 = SOL_6_F;
//     int SOL_7 = SOL_7_F;
//     int PUMP = PUMP_F;
// }
// else if (strcmp(frontrear, "rear")== 0 )
// {
//     int SOL_1 = SOL_1_R;
//     int SOL_2 = SOL_2_R;
//     int SOL_3 = SOL_3_R;
//     int SOL_4 = SOL_4_R;
//     int SOL_5 = SOL_5_R;
//     int SOL_6 = SOL_6_R;
//     int SOL_7 = SOL_7_R;
//     int PUMP = PUMP_R;
// }
// else 
// {
//     printf("invalid input");
   
// }


if (strcmp(leftright, "right")== 0)
{
digitalWrite(SOL_1, LOW);
digitalWrite(SOL_2, LOW);
}
else if (strcmp(leftright, "left")== 0)
{
    digitalWrite(SOL_4, LOW);
    digitalWrite(SOL_6, LOW);
}
else
{
    printf("invalid input");
    digitalWrite(PUMP, HIGH);
    digitalWrite(SOL_7, HIGH);
}
}








void extend(char const frontrear[], char const leftright[])
{
//     int SOL_1, SOL_2, SOL_3, SOL_4, SOL_5, SOL_6, SOL_7, PUMP;
//     if (strcmp(frontrear, "front") == 0 )
// {
//     int SOL_1 = SOL_1_F;
//     int SOL_2 = SOL_2_F;
//     int SOL_3 = SOL_3_F;
//     int SOL_4 = SOL_4_F;
//     int SOL_5 = SOL_5_F;
//     int SOL_6 = SOL_6_F;
//     int SOL_7 = SOL_7_F;
//     int PUMP = PUMP_F;
// }
// else if (strcmp(frontrear, "rear")== 0 )
// {
//     int SOL_1 = SOL_1_R;
//     int SOL_2 = SOL_2_R;
//     int SOL_3 = SOL_3_R;
//     int SOL_4 = SOL_4_R;
//     int SOL_5 = SOL_5_R;
//     int SOL_6 = SOL_6_R;
//     int SOL_7 = SOL_7_R;
//     int PUMP = PUMP_R;
// }
// else 
// {
//     printf("invalid input");
// }

if (strcmp(leftright, "right")== 0)
{

    digitalWrite(SOL_2, HIGH);
}
else if (strcmp(leftright, "left")== 0)
{


    digitalWrite(SOL_6, HIGH);
}
else
{
    printf("invalid input");
 }
}



void shutDown(char const frontrear[])
{
//     int SOL_1, SOL_2, SOL_3, SOL_4, SOL_5, SOL_6, SOL_7, PUMP;
//     if (strcmp(frontrear, "front") == 0 )

// {
//     int SOL_1 = SOL_1_F;
//     int SOL_2 = SOL_2_F;
//     int SOL_3 = SOL_3_F;
//     int SOL_4 = SOL_4_F;
//     int SOL_5 = SOL_5_F;
//     int SOL_6 = SOL_6_F;
//     int SOL_7 = SOL_7_F;
//     int PUMP = PUMP_F;
// }
// else if (strcmp(frontrear, "rear")== 0 )
// {
//     int SOL_1 = SOL_1_R;
//     int SOL_2 = SOL_2_R;
//     int SOL_3 = SOL_3_R;
//     int SOL_4 = SOL_4_R;
//     int SOL_5 = SOL_5_R;
//     int SOL_6 = SOL_6_R;
//     int SOL_7 = SOL_7_R;
//     int PUMP = PUMP_R;
// }
// else 
// {
//     printf("invalid input");
// }
    digitalWrite(SOL_1, HIGH);
    digitalWrite(SOL_2, HIGH);
    digitalWrite(SOL_3, HIGH);
    digitalWrite(SOL_4, HIGH);
    digitalWrite(SOL_5, HIGH);
    digitalWrite(SOL_6, HIGH);
    digitalWrite(SOL_7, HIGH);
    digitalWrite(PUMP, HIGH);
   

    printf("\nProgram Complete\n\n");
    // int fd = openData();
    // printf("Accumulator pressure is: %f\n", getData(fd, "accumulator_pressure"));
    // closeData(fd);
}

void standby(char const frontrear[])
{
//     int SOL_1, SOL_2, SOL_3, SOL_4, SOL_5, SOL_6, SOL_7, PUMP;
//     if (strcmp(frontrear, "front") == 0 )
// {
//     int SOL_1 = SOL_1_F;
//     int SOL_2 = SOL_2_F;
//     int SOL_3 = SOL_3_F;
//     int SOL_4 = SOL_4_F;
//     int SOL_5 = SOL_5_F;
//     int SOL_6 = SOL_6_F;
//     int SOL_7 = SOL_7_F;
//     int PUMP = PUMP_F;
// }
// else if (strcmp(frontrear, "rear")== 0 )
// {
//     int SOL_1 = SOL_1_R;
//     int SOL_2 = SOL_2_R;
//     int SOL_3 = SOL_3_R;
//     int SOL_4 = SOL_4_R;
//     int SOL_5 = SOL_5_R;
//     int SOL_6 = SOL_6_R;
//     int SOL_7 = SOL_7_R;
//     int PUMP = PUMP_R;
// }
// else 
// {
//     printf("invalid input");
// }
    hold(frontrear, "left");
    hold(frontrear, "right");
    delay(50);
    digitalWrite(SOL_1, LOW);
    digitalWrite(SOL_2, LOW);
    digitalWrite(SOL_3, HIGH);
    digitalWrite(SOL_4, LOW);
    digitalWrite(SOL_5, HIGH);
    digitalWrite(SOL_6, LOW);
    digitalWrite(SOL_7, HIGH);
    digitalWrite(PUMP, HIGH);
   // safetyCheck();
}

void chargeAccumulators(char const frontrear[],int pressure_nominal_accumulator) //Takes input argument of the prechage pressure that the accumulators should have. Charges the accumulators until this value is reached.
{
//     int SOL_1, SOL_2, SOL_3, SOL_4, SOL_5, SOL_6, SOL_7, PUMP;
//     if (strcmp(frontrear, "front") == 0 )
// {
//     int SOL_1 = SOL_1_F;
//     int SOL_2 = SOL_2_F;
//     int SOL_3 = SOL_3_F;
//     int SOL_4 = SOL_4_F;
//     int SOL_5 = SOL_5_F;
//     int SOL_6 = SOL_6_F;
//     int SOL_7 = SOL_7_F;
//     int PUMP = PUMP_F;
// }
// else if (strcmp(frontrear, "rear")== 0 )
// {
//     int SOL_1 = SOL_1_R;
//     int SOL_2 = SOL_2_R;
//     int SOL_3 = SOL_3_R;
//     int SOL_4 = SOL_4_R;
//     int SOL_5 = SOL_5_R;
//     int SOL_6 = SOL_6_R;
//     int SOL_7 = SOL_7_R;
//     int PUMP = PUMP_R;
// }
// else 
// {
//     printf("invalid input");
// }
 
printf("\nCHARGING ACCUMULATORS\n");  



//  { //ADD WHEN CONFIDENT IN PRESSURE SENSOR
   // safetyCheck();
    digitalWrite(PUMP, LOW);
        // while (getData("current")> inrushLimit)  //ADD WHEN CURRENT SENSOR WORKS!
    // {
    //     delay(50);
    // }
    delay(pumpSpinup);
    digitalWrite(SOL_1, HIGH);//MOVE UP LATER
    digitalWrite(SOL_2, HIGH);
    digitalWrite(SOL_3, LOW);
    digitalWrite(SOL_4, HIGH);
    digitalWrite(SOL_5, HIGH);
    digitalWrite(SOL_6, HIGH);
    digitalWrite(SOL_7, LOW);
//}
delay(1500);

    digitalWrite(SOL_1, HIGH);
    digitalWrite(SOL_2, HIGH);
    digitalWrite(SOL_3, HIGH);
    digitalWrite(SOL_4, HIGH);
    digitalWrite(SOL_5, HIGH);
    digitalWrite(SOL_6, HIGH);
    digitalWrite(SOL_7, HIGH);
    digitalWrite(PUMP, HIGH);
    printf("\nACCUMULATORS CHARGED!\n");
    
 //  safetyCheck("frontrear");
}

void pressure(const char frontrear, int pressure)
{
    digitalWrite(PUMP, LOW);
    
    delay(pumpSpinup);
    digitalWrite(SOL_1, HIGH);//MOVE UP LATER
    digitalWrite(SOL_2, HIGH);
    digitalWrite(SOL_3, LOW);
    digitalWrite(SOL_4, HIGH);
    digitalWrite(SOL_5, HIGH);
    digitalWrite(SOL_6, HIGH);
    digitalWrite(SOL_7, LOW);
    float p = 0;
       while(p < pressure || p != -1)//ADD WHEN CURRENT SENSOR WORKS!
    {
        p = getData("accumulator_pressure");
        printf("%f", p);
        delay(50);
    }



    digitalWrite(SOL_1, HIGH);
    digitalWrite(SOL_2, HIGH);
    digitalWrite(SOL_3, HIGH);
    digitalWrite(SOL_4, HIGH);
    digitalWrite(SOL_5, HIGH);
    digitalWrite(SOL_6, HIGH);
    digitalWrite(SOL_7, HIGH);
    digitalWrite(PUMP, HIGH);
    printf("\nACCUMULATORS CHARGED!\n FINAL PRESSURE IS %f", getData("accumulator_pressure"));


}

void safetyCheck(char const frontrear[])
{

if (getData("big_battery_voltage") < lowBAttery) //consider whether to make this one so that it only prevents runnig of the pump. 
{
    shutDown(frontrear);
    printf("WARNING Battery voltage at:  %f, please recharge battery\n", getData("big_battery_voltage"));
}
else if (getData("pump_pressure") < overpressurePump)
{
    shutDown(frontrear);
     printf("WARNING pump pressure at:  %f, power disconnected\n", getData("pump_pressure"));
}
else if (getData("accumulator_pressure") < overpressureAccumulators)
{
     shutDown(frontrear);
    printf("WARNING accumulators pressure at:  %f, Power disconnected\n PLEASE DISCHARGE ACCUMULATORS", getData("pump_pressure"));
}
else if (getData("accumulator_pressure") < overpressureAccumulators)
{
     shutDown(frontrear);
    printf("WARNING accumulators pressure at:  %f, Power disconnected\n PLEASE DISCHARGE ACCUMULATORS", getData("pump_pressure"));
}
}

