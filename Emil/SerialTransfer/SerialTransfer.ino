
void setup() {
  // put your setup code here, to run once:
//#include <Wire.h>


Serial.begin(115200);

}

void loop() {
int i = 0;
for (;;){
if (i > 998)
{
  i = 0;
  }
char x = Serial.read();
if (x=='a')
{
Serial.print(i);
Serial.print(" ");
Serial.print(i);
Serial.print(" ");
Serial.print(i);
Serial.print(" ");
Serial.print(i);
Serial.print(" ");
Serial.print(i);
Serial.print(" ");
Serial.print(i);
Serial.print(" ");
Serial.print(i);
Serial.print(" ");
Serial.println(i);
}
delay(1000);
i++;
}
}
