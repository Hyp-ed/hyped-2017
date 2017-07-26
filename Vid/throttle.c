#include <stdio.h>
#include <errno.h>
#include <string.h>

#include <drogon/wiringpi/wiringPi/wiringPi.h>
#include <drogon/wiringpi/wiringPi/softServo.h>


// CALL THIS SETUP ONLY ONCE!
//also wiring pi setup is assumed
softServoSetup (0, 1, 2, 3, 4, 5, 6, 7) ;


//DONT LOOP THIS. It sets the pin into state
//Throttle -100% reverse
//0% idle or brake if moving
//100% forward
void motorstate(int servo, int throttle)
{
    
    float pulse=(throttle/100.0)*500.0+500
    softServoWrite(servo,(int)pulse);
    
}