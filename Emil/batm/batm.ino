
/*
(Big endian)

SLAVE1
7 ints. Big batt1 cell voltages mV (1 to 7)
1 int. Big batt1 Temperature Ã‚Â°C
1 int Big batt1 Current A
1 int Smallbatt total voltaage mV
1 int. Big batt1 Temperature Ã‚Â°C
1 int Hydraulic pump1 bar
1 int Hydraulic acc21 bar

SLAVE2
7 ints. Big batt2 cell voltages mV (1 to 7)
1 int. Big batt2 Temperature Ã‚Â°C
1 int Big batt2 Current A
1 int Smallbatt2 total voltaage mV
1 int. Big batt1 Temperature Ã‚Â°C
1 int Hydraulic pump2 bar
1 int Hydraulic acc2 bar
*/
#include <Wire.h>

#define SLAVE_ADDRESS 0x6A

#define INTER_ANAL 1
#define EXP_AVERAGING 1
#define SERIALDEBUG 1
#define SEND_BLANK 1

byte blank[28];


// select the input pins for the batteries



#define smallbattPinV A8
#define smallbattPinT A5

#define battPinT A6
#define currPin A7 
#define battPin6 A9
#define battPin5 A10
#define battPin4 A11 
#define battPin3 A12   
#define battPin2 A13
#define battPin1 A14
#define battPin0 A15

#define pumppin A4
#define accpin A3



#define CURRENTCOEF (1000.0/10.0)



float battWeighting = 0.5; // define a weighting to apply to our exponential moving average calculation for battery 

float abattValue0 = 0; // variable to store average value (exponential moving average) calculation
float abattValue1 = 0;
float abattValue2 = 0;
float abattValue3 = 0;
float abattValue4 = 0;
float abattValue5 = 0;
float abattValue6 = 0;
float acurrValue = 0;
float bigtempValue = 0;

float smallbattValue = 0;
float smalltempValue = 0;

float pumpvalue =0;
float accvalue = 0;





float CurrZeropoint = 0;


int Cell1 = 0; // variable to store actual cell voltages
int Cell2 = 0;
int Cell3 = 0;
int Cell4 = 0;
int Cell5 = 0;
int Cell6 = 0;
int Cell7 = 0;
int Current = 0;
int bigtemp = 0;

int smallbatt = 0;
int smalltemp = 0;

int pump = 0;
int acc = 0;

int i=0;

// one point on the ADC equals this many volts
#ifdef INTER_ANAL 
float adcVolt = (2.56/1024.0);
#else
float adcVolt = 0.0048680351906158 ; 
#endif


void writeString(String stringData) { // Used to serially push out a String with Serial.write()

  for (int i = 0; i < stringData.length(); i++)
  {
    Serial.write(stringData[i]);   // Push each char 1 by 1 on each loop pass
  }

}// end writeString 



void setup() {

//

  #ifdef INTER_ANAL 
  analogReference(INTERNAL2V56);
  #endif
  
  #ifdef SERIALDEBUG
  Serial.begin(115200);
  #endif
// initialize i2c as slave
  //Wire.begin(SLAVE_ADDRESS);

// define callbacks for i2c communication
 // Wire.onRequest(sendData);

  



//
  
  // Read the battery voltage values and set up the averaging
  // require 50 reads to initialise correct ewv.
//  for (int i=0; i<50; i++){
//    getBattStat();
//  }
//
//  CurrZeropoint = Current;


}

void loop() {
  // basic get and show voltages
  //getBattStat();

  #ifdef SERIALDEBUG
  showBattStat();
  #endif

  i=0;
while(i<5000){
  
  Serial.print(1);
  i++;
  }
  
i=0;
  while(1){
Serial.println (i);
i++;
  delay(50);  
  }

  
  delay(50);                  
}

void getBattStat() {




  #ifdef EXP_AVERAGING

  // read the value from the sensor:
  abattValue0 = (analogRead(battPin0) * battWeighting) + (abattValue0 * (1-battWeighting));
  abattValue1 = (analogRead(battPin1) * battWeighting) + (abattValue1 * (1-battWeighting));
  abattValue2 = (analogRead(battPin2) * battWeighting) + (abattValue2 * (1-battWeighting));
  abattValue3 = (analogRead(battPin3) * battWeighting) + (abattValue3 * (1-battWeighting));
  abattValue4 = (analogRead(battPin4) * battWeighting) + (abattValue4 * (1-battWeighting));
  abattValue5 = (analogRead(battPin5) * battWeighting) + (abattValue5 * (1-battWeighting));
  abattValue6 = (analogRead(battPin6) * battWeighting) + (abattValue6 * (1-battWeighting));
  
  acurrValue = (analogRead(currPin) * battWeighting) + (acurrValue * (1-battWeighting));
  bigtempValue = (analogRead(battPinT) * battWeighting) + (bigtempValue * (1-battWeighting));
  
  smallbattValue = (analogRead(smallbattPinV) * battWeighting) + (smallbattValue * (1-battWeighting));
  smalltempValue = (analogRead(smallbattPinT) * battWeighting) + (smalltempValue * (1-battWeighting));

  pumpvalue = (analogRead(pumppin) * battWeighting) + (pumpvalue * (1-battWeighting));
  accvalue = (analogRead(accpin) * battWeighting) + (accvalue * (1-battWeighting));
  // convert these values to cell voltages

  
  Cell1 = (adcVolt * abattValue0 * ((46.5+39.1)/39.1)) * 1000;
  Cell2 = (adcVolt * abattValue1 * ((120.0+39.0)/39.0))* 1000 - Cell1;
  Cell3 = (adcVolt * abattValue2 * ((180.0+39.0)/39.0))* 1000 - Cell2-Cell1;
  Cell4 = (adcVolt * abattValue3 * ((270.0+39.0)/39.0))* 1000 - Cell3-Cell2-Cell1;
  Cell5 = (adcVolt * abattValue4 * ((330.0+39.0)/39.0))* 1000 - Cell4-Cell3-Cell2-Cell1;
  Cell6 = (adcVolt * abattValue5 * ((390.0+39.0)/39.0))* 1000 - Cell5-Cell4-Cell3-Cell2-Cell1;
  Cell7 = (adcVolt * abattValue6 * ((470.0+39.0)/39.0))* 1000 - Cell6-Cell5-Cell4-Cell3-Cell2-Cell1;

  Current = (adcVolt * acurrValue * ((47.0+39.0)/39.0)  )*CURRENTCOEF- CurrZeropoint;

  bigtemp = ((adcVolt * bigtempValue * ((47.0+39.0)/39.0)) - 0.5) * 100.0;

  smallbatt = (adcVolt * smallbattValue * ((330.0+39.0)/39.0))*1000;

  smalltemp = ((adcVolt * smalltempValue * ((47.0+39.0)/39.0))-0.5)*100;

  pump = (adcVolt * pumpvalue * (249.0/1.6) - 61.25);
  acc = (adcVolt * accvalue * (249.0/1.6) - 61.25);




  #else

  Cell1 = adcVolt * analogRead(battPin0) * (46.5+39.1)/39.1 * 1000;
  Cell2 = adcVolt * (analogRead(battPin1) * ((120.0+39.0)/39.0)) * 1000 - Cell1;
  Cell3 = (adcVolt * (analogRead(battPin2) * ((180.0+39.0)/39.0))* 1000 - Cell2-Cell1);
  Cell4 = (adcVolt * (analogRead(battPin3) * ((270.0+39.0)/39.0))* 1000 - Cell3-Cell2-Cell1);
  Cell5 = (adcVolt * (analogRead(battPin4) * ((330.0+39.0)/39.0))* 1000 - Cell4-Cell3-Cell2-Cell1);
  Cell6 = (adcVolt * (analogRead(battPin5) * ((390.0+39.0)/39.0))* 1000 - Cell5-Cell4-Cell3-Cell2-Cell1);
  Cell7 = (adcVolt * (analogRead(battPin6) * ((470.0+39.0)/39.0))* 1000 - Cell6-Cell5-Cell4-Cell3-Cell2-Cell1);

  Current = (((adcVolt * (analogRead(currPin))) * ((47.0+39.0)/39.0) )*CURRENTCOEF)- CurrZeropoint;

  bigtemp = ((adcVolt * (analogRead(battPinT) * ((47.0+39.0)/39.0)))-0.5)*100;

  smallbatt = ((adcVolt * (analogRead(smallbattPinV) * ((330.0+39.0)/39.0))*1000));

  smalltemp = ((adcVolt * (analogRead(smallbattPinT) * ((47.0+39.0)/39.0) ) )-0.5)*100;

  pump = (adcVolt * (analogRead(pumppin)) * (249.0/1.6) - 61.25);
  acc = (adcVolt * (analogRead(accpin)) * (249.0/1.6) - 61.25);
  
  
  #endif
  

}

void showBattStat() {
  //Serial.println (Current);
//  Serial.print ("A. ");
//  Serial.print (Cell1);
//  Serial.print ("V. " );
//  Serial.print (Cell2);
//  Serial.print ("V. ");
//  Serial.print (Cell3);
//  Serial.print ("V. ");
//  Serial.print (Cell4);
//  Serial.print ("V. ");
//  Serial.print (Cell5);
//  Serial.print ("V. " );
//  Serial.print (Cell6);
//  Serial.print ("V. ");
//  Serial.print (Cell7);
//  Serial.print ("V. Total = " );
//  Serial.print (Cell1+Cell2+Cell3+Cell4);
//  
//  Serial.print ("   Bigtemp. ");
//  Serial.print (bigtemp);
//  
//  Serial.print ("  Small batt ");
//  Serial.print (smallbatt);
//
//  Serial.print ("  Smalltemp. ");
//  Serial.print (smalltemp);
//
//  Serial.print ("  Pump. ");
//  Serial.print (pump);
//
//  Serial.print ("  Acc. ");
 // Serial.println (acc);


  
}


// callback for sending data
void sendData(){
  
#ifdef SEND_BLANK
Wire.write(blank, 28);

#else

byte response[28];

response[0] = Cell1 >> 8;
response[1] = Cell1 & 0x00ff;
response[2] = Cell2 >> 8;
response[3] = Cell2 & 0x00ff;
response[4] = Cell3 >> 8;
response[5] = Cell3 & 0x00ff;
response[6] = Cell4 >> 8;
response[7] = Cell4 & 0x00ff;
response[8] = Cell5 >> 8;
response[9] = Cell5 & 0x00ff;
response[10] = Cell6 >> 8;
response[11] = Cell6 & 0x00ff;
response[12] = Cell7 >> 8;
response[13] = Cell7 & 0x00ff;

response[14] = bigtemp >> 8;
response[15] = bigtemp & 0x00ff;

response[16] = Current >> 8;
response[17] = Current & 0x00ff;

response[18] = smallbatt >> 8;
response[19] = smallbatt & 0x00ff;

response[20] = smalltemp >> 8;
response[21] = smalltemp & 0x00ff;

response[22] = pump >> 8;
response[23] = pump & 0x00ff;

response[24] = acc >> 8;
response[25] = acc & 0x00ff;

Wire.write(response,26);

#endif



}









