#include "tasks.h"
#include "conditioner.h"
#include "temperature.h"
#include <Arduino.h>

float temperatureVal = 0.0;


// TP task code
void TaskReadTemperatureProvider() {
  temperatureVal = ReadTemperature();
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
