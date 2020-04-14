#include "tasks.h"
#include "conditioner.h"
#include "temperature.h"
#include <Arduino.h>
#include "mykeypad.h"

float temperatureVal = 0.0;
char charKeypad = '-';

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

void TaskReadSerialChar() {
// TODO
}

void TaskReadKeypadChar() {
	char keypressed = kpd.getKey();
   	if (keypressed != NO_KEY)
   	{    charKeypad = keypressed;
   	}  
}