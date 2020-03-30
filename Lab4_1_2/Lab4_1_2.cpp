// serial plotter:
// https://randomnerdtutorials.com/arduino-serial-plotter-new-tool/

#include "temperature.h"
#include "conditioner.h"
#include <Arduino.h>
#define TIME_INTERVAL_MS 2000 //Read sensor each 2 seconds
#define MAX_TEMP 26
#define MIN_TEMP 24

long previousMillis = 0;


void SerialInit() {
  Serial.begin(9600);
}

unsigned long CompareTimeInterval(unsigned long currentMillis, unsigned long previousMillis) {
  return currentMillis - previousMillis;
}

int TimeIntervalElapsed(unsigned long currentMillis, unsigned long previousMillis) {
  int interval = CompareTimeInterval(currentMillis, previousMillis);
  if(interval > TIME_INTERVAL_MS) {
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


void setup() {
  SerialInit();
  InitTemperatureSensor();
  ConditionerInit();
  Serial.println("Init complete");
}


void loop()
{

  double t = 0.0;

  unsigned long currentMillis = millis(); //time elapsed

  if(TimeIntervalElapsed(currentMillis, previousMillis))
  {
    previousMillis = currentMillis; //"Last time is now"

    t = GetTemperature();

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
