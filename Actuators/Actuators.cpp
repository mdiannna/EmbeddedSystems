#include <Arduino.h>
#include <keypad.h>
#include <avr.h>
#include <avr/io.h>
#include <car.h>
#include <stdio.h>
#include <mystdio.h>
#include <light.h>


/*  Arduino DC Motor Control - PWM | H-Bridge | L298N  -  Example 01

    by Dejan Nedelkovski, www.HowToMechatronics.com
*/

#define enA 9
#define in1 6
#define in2 7
#define button 4

int rotDirection = 0;
int pressed = false;
int cnt = 0;

void setup() {
	InitSerial();
	InitKeypad();
	InitCar();
	InitLight();
}



// void loopTestMotor() {

// 	if(cnt<500) {

// 		int motorSpeedA = 100;
// 		 analogWrite(enA, motorSpeedA);
// 		 delay(20);
// 	} else if(cnt <1000) {
// 		  digitalWrite(in2, LOW);
// 		  digitalWrite(in1, HIGH);

// 		int motorSpeedA = 100;
// 				 analogWrite(enA, motorSpeedA);
// 				 delay(20);

// 	}
// 	else {
// 		 analogWrite(enA, 0);
// 	}
// 	cnt++;
// }


void loop() {
	char c = GetCharKeypad();
	printf("You typed: %c\n", c );
	
	if(c=='2') {
		MoveForward(50);
	}

	if(c=='8') {
		MoveBackward(50);
	}

	if(c=='4') {
		TurnLeft();
	}

	if(c=='6') {
		TurnRight();
	}
		
	// * - Light on
	if(c=='*' && !IsLightOn()) {
		LightOn();
	}

	// # - Light off
	if(c=='#' && IsLightOn()) {
		LightOff();
	}
}


