#include <Arduino.h>
#include <avr/io.h>
#include "car.h"
#include <stdio.h>
#include "mystdio.h"
#include "light.h"



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
	InitCar();
	InitLight();
	printf("Initialization done");
 s = (char *) malloc(10*sizeof(char));
}



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


	if(c=='f') {
		MoveForward();
		printf("Car Moves Forward\n\r");
	}

	if(c=='b') {
		MoveBackward();
		printf("Car Moves Backward\n\r");
	}

	if(c=='s') {
			StopCar();
			printf("Car Stops\n\r");
		}

	if(c=='l') {
		TurnLeft();
	}

	if(c=='r') {
		TurnRight();
	}
		
	if(c=='n') {
		LightOn();
	}

	if(c=='t') {
		LightOff();
	}
}


