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
}

void MoveForward(int speed) {

}

void MoveBackward(int speed) {

}

// optional: degrees??
void TurnLeft() {

}

// optional: degrees??
void TurnRight() {

}