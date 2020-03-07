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

void setup() {
	InitSerial();
	//InitKeypad();
	InitCar();
	InitLight();
	printf("Initialization done");
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

//	scanf("%c", &c);

	while(!Serial.available());
	c = Serial.read();
	//
	//printf("You typed!!!: %c\n\r", c );
	Serial.write(c);
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
		MoveForward(50);
	}

//	if(s=="backward") {
	if(c=='b') {
		MoveBackward(50);
	}

	if(c=='s') {
			StopCar();
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


