#include "tasks.h"
#include "conditioner.h"
#include "temperature.h"
#include <Arduino.h>
#include "mykeypad.h"
#include "password.h"
#include "mystdio.h"

float temperatureVal = 0.0;
char charKeypad = '-';
int passwordIsCorrect = 0;
char charSerial;

// TP task code
void TaskReadTemperatureProvider() {
	Serial.println("Read temperature");
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
	if (Serial.available() > 0) {
    	charSerial = Serial.read();
    }
}


void TaskReadKeypadCharPwd() {
	char keypressed = kpd.getKey();
   	if (keypressed != NO_KEY)
   	{    
		charKeypad = keypressed;
		password[passwordIndex] = charKeypad;
		passwordIndex++; 
		
		if(passwordIndex>=10) {
			password = "";
			passwordIndex = 0;
		}
	}  
}

// TASK_CHK_PWD
void TaskChechPassword() {
	if(charKeypad=='#') {
		passwordIsCorrect = 0;
		if(PasswordIsCorrect(password)){
			passwordIsCorrect = 1;
		}
		password = "";
		passwordIndex = 0;
	} 
}
