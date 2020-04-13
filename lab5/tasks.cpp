#include "tasks.h"
#include "bmp_pressure_temp_altitude.h"
#include "conditioner.h"
#include "bmp_pressure_temp_altitude.h"
#include <Arduino.h>

double temperatureVal = 0.0;
double pressureVal = 0.0;
double relPressureVal = 0.0;


// BMPTP task code
void TaskReadBMPTemperatureProvider() {
  Serial.println("Task temperature");
  // Something wrong here
	temperatureVal = GetTemperature();
 Serial.print(temperatureVal);

}
// BMPPP task code
void TaskReadBMPPressureProvider() {
		pressureVal = GetPressure();
}

// BMPRP task code
void TaskReadBMPRelPressure() {
		relPressureVal = GetSeaLevelPressure(); 
}

// ConditOnOff code
void TaskConditionerOnOffConsumer() {
	if(TemperatureExceedsMaxTemp(temperatureVal) && IsConditionerTurnedOff())
    {
      TurnConditionerOn();
    }
    else if(TemperatureBelowMinTemp(temperatureVal)&&IsConditionerTurnedOn())
    {
      TurnConditionerOff();
    }
}
