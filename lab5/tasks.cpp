#include "tasks.h"
#include "conditioner.h"
#include "temperature.h"
#include <Arduino.h>
#include "mykeypad.h"
#include "password.h"
#include "mystdio.h"
#include "car.h"
#include "light.h"
#include "button.h"
#include "led.h"
#include "lightsensor.h"
#include "lcd.h"

float temperatureVal = 0.0;
char charKeypad = '-';
int passwordIsCorrect = 0;
char charSerial;
char * password;
float lightValue = 0;
float luxValue = 0;

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
	if(charKeypad=='#' && IsLightOn() ){
		LightOff();
	} else 
		if(charKeypad=='*' && IsLightOn()==0 ){
		{
			LightOn();
		}
	}
}

// BTN_LED_1
void TaskButtonLedLab1() {
	if(IsButtonPressed()==1) {
		if(Is_LED_On()) {
			LED_Off();
		} else {
			LED_On();
		}
	}
}


// READ_LIGHT_SENSOR
void TaskReadValueLightSensorProvider() {
	float lightLevel = ReadLightLevel();
	float filteredValue = MyFilter(lightLevel);

	lightValue = filteredValue;
	luxValue = calcLux(filteredValue);
}

//SHOW_TEMP_LCD
void TaskShowTempLCDConsumer(){
	LCD_SetCursor(0,0);
	WriteLCD("Temp: ");
	WriteLCD(temperatureVal);
}

// ROTATE_MOTOR - lab 3 Actuators
void TaskRotateMotor() {
	if( charKeypad=='0') {
		StopCar();
	} else if(charKeypad=='1') {
		MoveForward();
		SetCarSpeed(20);
	} else if(charKeypad=='2') {
		MoveForward();
		SetCarSpeed(30);
	} else if(charKeypad=='3') {
		MoveForward();
		SetCarSpeed(40);
	} else if(charKeypad=='4') {
		MoveForward();
		SetCarSpeed(50);
	} else if(charKeypad=='5') {
		MoveForward();
		SetCarSpeed(60);
	} else if(charKeypad=='6') {
		MoveForward();
		SetCarSpeed(70);
	} else if(charKeypad=='7') {
		MoveForward();
		SetCarSpeed(80);
	} else if(charKeypad=='8') {
		MoveForward();
		SetCarSpeed(90);
	} else if(charKeypad=='9') {
		MoveForward();
		SetCarSpeed(100);
	}
}