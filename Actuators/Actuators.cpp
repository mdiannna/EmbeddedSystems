#include <Arduino.h>
#include <avr/io.h>
#include "car.h"
#include <stdio.h>
#include "mystdio.h"
#include "light.h"
#include "mykeypad.h"


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
char * s;

void setup() {
	InitSerial();
	//InitKeypad();
	InitCar();
	InitLight();
	printf("Initialization done");
 s = (char *) malloc(10*sizeof(char));
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
	char c;
	char speed;

	while(!Serial.available());
	c = Serial.read();
	Serial.write(c);

	if(c=='S') {
		while(!Serial.available());
		speed = Serial.read();
		Serial.write("Input speed:\n\r");
		 switch(speed) {
		 	     case '1':
		        	// 10% to 100%
		        	SetCarSpeed(10);
		        	break;
		        case '2':
		        	SetCarSpeed(20);
		        	break;
		        case '3':
		        	SetCarSpeed(30);
		        	break;
		        case '4':
		        	SetCarSpeed(40);
		        	break;
		        case '5':
		        	SetCarSpeed(50);
		        	break;
		        case '6':
		        	SetCarSpeed(60);
		        	break;
		        case '7':
		        	SetCarSpeed(70);
		        	break;
		        case '8':
		        	SetCarSpeed(80);
		        	break;
		        case '9':
		        	SetCarSpeed(90);
		        	break;
		        case 'C':
		        	SetCarSpeed(100);
		        	break;
		 }
		 printf("Car speed changed\n\r");
	}
	//
	//printf("You typed!!!: %c\n\r", c );

	//	String s ="";
//	if (Serial.available() > 0) {
//	char c = Serial.read();
//
////	char c = GetCharKeypad();
//	printf("You typed: %c\n\r", c );
//
//
//	delay(1000);
//	 s = Serial.readString();
//	printf("You typed: %s\n", s );
//	}
	//if(s=="forward") {
	if(c=='f') {
		MoveForward();
		printf("Car Moves Forward\n\r");
	}

//	if(s=="backward") {
	if(c=='b') {
		MoveBackward();
		printf("Car Moves Backward\n\r");
	}

	if(c=='s') {
			StopCar();
			printf("Car Stops\n\r");
		}

//	if(s=="left") {
	if(c=='l') {
		TurnLeft();
	}

//	if(s=="right") {
	if(c=='r') {
		TurnRight();
	}
		
	// * - Light on
	//if(s=="lighton" && !IsLightOn()) {
	if(c=='n') {
		LightOn();
	}

	// # - Light off
	//if(s=="lightof" && IsLightOn()) {
	if(c=='t') {
		LightOff();
	}
}


