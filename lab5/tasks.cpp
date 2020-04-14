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


void TaskReadKeypadCharPwd() {
	char keypressed = kpd.getKey();
   	if (keypressed != NO_KEY)
   	{    
	charKeypad = keypressed;
	if(charKeypad=='#' && PasswordIsCorrect(password)){
		passwordIsCorrect = 1;
		ResetPassword();
	} else
		if(passwordIndex>=10) {
			ResetPassword();
		} else {
			AddCharToPassword(charKeypad);    
		}
	}  
}
