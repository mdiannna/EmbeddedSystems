#include <Wire.h>
//Library from https://github.com/Lithium366/BMP085
#include "BMP085NB.h"

BMP085NB bmp;

int temperature = 0;
long pressure = 0;
float alti = 130.0;
unsigned long timer = 0;

void setup () {
  Serial.begin(9600);
  bmp.initialize();
  bmp.setSeaLevelPressure(100600);
}
  
void loop () {
  timer = millis();  
  bmp.pollData(&temperature, &pressure, &alti);  
  if (bmp.newData) {
    Serial.print("Temp: ");
    Serial.print(temperature / 10);
    Serial.print("degC Pres: ");
    Serial.print(pressure, DEC);
    Serial.print("Pa Alt: ");
    Serial.print(alti);
    Serial.print("m Time: ");
    Serial.print(millis() - timer); 
    Serial.println("ms");
  }
}
