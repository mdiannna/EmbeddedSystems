#include <keypad.h>
#include <Arduino.h>
#include <avr.h>
#include <avr/io.h>

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
	MotorForward('A', PowerToSpeed(power));
	MotorForward('B', PowerToSpeed(power));
}

void MoveBackward(int power) {
	MotorBackward('A', PowerToSpeed(power));
	MotorBackward('B', PowerToSpeed(power));
}

void StopCar() {
	MotorsStop();
}

// optional: degrees??
void TurnLeft() {
	int power = TURN_POWER;
	MotorBackward('A', PowerToSpeed(power));
	MotorForward('B', PowerToSpeed(power));
}

// optional: degrees??
void TurnRight() {
	int power = TURN_POWER;
	MotorForward('A', PowerToSpeed(power));
	MotorBackward('B', PowerToSpeed(power));
}