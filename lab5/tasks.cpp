#include "tasks.h"
#include "conditioner.h"
#include "temperature.h"
#include <Arduino.h>
#include "mykeypad.h"
#include "password.h"
#include "mystdio.h"
#include "car.h"
#include "light.h"

float temperatureVal = 0.0;
char charKeypad = '-';
int passwordIsCorrect = 0;
char charSerial;
char * password;

int passwordIndex;

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
	Serial.println("Write char:");
	if (Serial.available() > 0) {
    	charSerial = Serial.read();
    }
}


void TaskReadKeypadCharPwd() {
	char keypressed = kpd.getKey();
   	if (keypressed != NO_KEY)
   	{    
		charKeypad = keypressed;
		// password[passwordIndex] = charKeypad;
		// passwordIndex++; 
		
		// if(passwordIndex>=3) {
		// 	password = "";
		// 	passwordIndex = 0;
		// }
	}  
}

// // TASK_CHK_PWD
// void TaskChechPassword() {
// 	if(charKeypad=='#') {
// 		passwordIsCorrect = 0;
// 		if(PasswordIsCorrect(password)==1	){
// 			passwordIsCorrect = 1;
// 		}
// 		password = "";
// 		// password[0] = '*';
// 		// password[1] = '*';
// 		// password[2] = '*';
// 		// password[3] = '*';

// 		passwordIndex = 0;
//     	charKeypad='-';
// 	} 
// }


// TURN_LIGHTS_ON
void TaskTurnCarLightsOn() {
	if(charKeypad=='*'){
		if(IsLightOn()) {
			LightOff();
		} else {
			LightOn();
		}
	}
}
