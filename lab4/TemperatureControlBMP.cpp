// serial plotter:
// https://randomnerdtutorials.com/arduino-serial-plotter-new-tool/

#include "temperature.h"
#include "conditioner.h"
#include <Arduino.h>
#define TIME_INTERVAL_MS = 2000; //Read sensor each 2 seconds
#define MAX_TEMP 26
#define MIN_TEMP 24

long previousMillis = 0;

void setup() {
  InitTemperatureSensor();
  ConditionerInit();
}

unsigned long CompareTimeInterval(unsigned long currentMillis, unsigned long previousMillis) {
  return currentMillis - previousMillis;
}

int TimeIntervalElapsed(unsigned long currentMillis, unsigned long previousMillis) {
  if(CompareTimeInterval(currentMillis, previousMillis)> TIME_INTERVAL_MS) {
    return 1;
  }
  return 0;
}

int TemperatureExceedsMaxTemp(double t) {
  if(t>=MAX_TEMP) {
    return 1;
  }
  return 0;
}

int TemperatureBelowMinTemp(double t) {
  if(t<=MIN_TEMP) {
    return 1;
  }
  return 0;
}


void loop()
{
  double t = 0.0;

  unsigned long currentMillis = millis(); //time elapsed

  if(TimeIntervalElapsed(currentMillis, previousMillis))
  {
    previousMillis = currentMillis; //"Last time is now"
  
    t = ReadTemperature();

    // Open serial plotter
    Serial.println(t);

    if(TemperatureExceedsMaxTemp(t) && IsConditionerTurnedOff())//if temperature above of 25 degrees
    {
      TurnConditionerOn();     
    }
    else if(TemperatureBelowMinTemp(t)&&IsConditionerTurnedOn())//if temperature is under 23 degrees
    {
      TurnConditionerOff();
    }
    
  }
}