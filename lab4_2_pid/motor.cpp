#include <Arduino.h>
#include <avr/io.h>

#include "motor.h"


void InitMotor() {
	pinMode(enA, OUTPUT);
  	pinMode(in1, OUTPUT);
  	pinMode(in2, OUTPUT); 
}

void MotorForward(int speed) {
	digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
  	analogWrite(enA,speed);
}

void MotorBackward(int speed) {
	digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
  	// analogWrite(enA,PowerToSpeed(power));
  	analogWrite(enA,speed);
}

void MotorStop() {
	digitalWrite(in1, LOW);
  	digitalWrite(in2, LOW);
  	analogWrite(enA,0);	
}
