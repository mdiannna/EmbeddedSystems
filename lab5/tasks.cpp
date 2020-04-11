#include "tasks.h"
#include "pressure_temp_altitude.h"
#include "conditioner.h"

#include <Arduino.h>

double temperatureVal = 0.0;
double pressureVal = 0.0;
double relPressureVal = 0.0;


// BMPTP task code
void TaskReadBMPTemperatureProvider() {
  Serial.println("Task temperature");
  // Something wrong here
	//temperatureVal = SensorGetTemperature();
 Serial.print(temperatureVal);

}
// BMPTP task code
void TaskReadBMPPressureProviderConsumer() {
	if(temperatureVal > 0.0) {
		pressureVal = SensorGetPressure(temperatureVal);
		
	}
}

// BMPRPC task code
void TaskReadBMPRelPressureConsumer() {
	if(pressureVal > 0.0) {
		relPressureVal = SensorGetRelativePressure(pressureVal); 
		// TODO: print Relative pressure in main loop	
	}
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
