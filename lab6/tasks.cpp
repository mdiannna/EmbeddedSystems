#include "tasks.h"
#include "pressure_temp_altitude.h"
#include "conditioner.h"

int rec_cnt_BMPTP = OFFS_BMPTP;
int rec_cnt_BMPPPC = OFFS_BMPPPC;
int rec_cnt_BMPRPC = OFFS_BMPRPC;
int rec_cnt_CONDIT_ON_OFF = OFFS_CONDIT_ON_OFF;

// BMPTP task code
void TaskReadBMPTemperatureProvider() {
	temperatureVal = SensorGetTemperature();
	// TODO: print Temperature in main loop
}

// BMPTP task code
void TaskReadBMPPressureProviderConsumer() {
	if(temperatureVal > 0.0) {
		pressureVal = SensorGetPressure(temperatureVal);
		// TODO: print Pressure in main loop
	}
}

// BMPRPC task code
void TaskReadBMPRelPressureConsumer() {
	if(pressureVal > 0.0) {
		relativePressureVal = SensorGetRelativePressure(pressureVal); 
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

