#ifndef _serialData_h
#define _serialData_h

#include <unistd.h>


#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <wiringPi.h>
#include <wiringSerial.h>

#ifdef __cplusplus
extern "C"{
#endif

float getData(char const data[]); //used to be (char *data)

#ifdef __cplusplus
}
#endif


#endif
