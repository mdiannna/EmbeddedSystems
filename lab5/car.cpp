#include "car.h"
#include "motor.h"
#include <Arduino.h>
#include <avr/io.h>

int motorPower = 50;

// s- stop
// f- forward
// b- backward
// l - left
// r - right
char direction = 's';

void InitMotors() {
	InitMotorA();
	InitMotorB();
}

void InitCar() {
	InitMotors();
	// InitEncoder();

	// Set initial rotation direction
	digitalWrite(in1, LOW);
	digitalWrite(in2, HIGH);
	analogWrite(enA,0);
}

int PowerToSpeed(int power) {
	// map 0-100% power to 0-255 speed
	return map(power, 0, 100, 0 , 255);
}

void MoveForward(int power) {
	direction = 'f';
	MotorForward('A', PowerToSpeed(power));
	MotorForward('B', PowerToSpeed(power));
}

void MoveBackward(int power) {
	direction = 'b';
	MotorBackward('A', PowerToSpeed(power));
	MotorBackward('B', PowerToSpeed(power));
}


void MoveForward() {
	direction = 'f';
	MotorForward('A', PowerToSpeed(motorPower));
	MotorForward('B', PowerToSpeed(motorPower));
}

void MoveBackward() {
	direction = 'b';
	MotorBackward('A', PowerToSpeed(motorPower));
	MotorBackward('B', PowerToSpeed(motorPower));
}

void StopCar() {
	MotorsStop();
	direction = 's';
}

void TurnLeft() {
	direction = 'l';
	int power = TURN_POWER;
	MotorBackward('A', PowerToSpeed(power));
	MotorForward('B', PowerToSpeed(power));
}

void TurnRight() {
	direction = 'r';
	int power = TURN_POWER;
	MotorForward('A', PowerToSpeed(power));
	MotorBackward('B', PowerToSpeed(power));
}

char GetCarDirection() {
	return direction;
}

void ResetCarDirectionSpeed() {
	switch(direction) {
		case 's':
		   	 StopCar();
	    	 break;
		case 'f':
			MoveForward(motorPower);
	    	 break;
		case 'b':
			MoveBackward(motorPower);
	    	 break;
		case 'l':
		   	 TurnLeft();
	    	 break;
		case 'r':
		   	 TurnRight();
	    	 break;
	// s- stop
	// f- forward
	// b- backward
	// l - left
	// r - right
	}
}

void SetCarSpeed(int powerSpeed) {
	motorPower = powerSpeed;
	ResetCarDirectionSpeed();
}
