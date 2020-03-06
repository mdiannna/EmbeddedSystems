#include <Arduino.h>
#include <avr.h>
#include <avr/io.h>

#include <motor.h>


void InitMotorA() {
	pinMode(enA, OUTPUT);
  	pinMode(in1, OUTPUT);
  	pinMode(in2, OUTPUT); 
}

void InitMotorB() {
	pinMode(enB, OUTPUT);
  	pinMode(in3, OUTPUT);
  	pinMode(in4, OUTPUT);
}

// TODO:
void MotorForward(char motor, int speed) {
	if(motor=='A') {

	}
	if(motor=='B') {
		
	}

}


// TODO:
void MotorBackward(char motor, int speed) {
	if(motor=='A') {

	}
	if(motor=='B') {
		
	}

}

// TODO: check
void MotorStop(char motor) {
	if(motor=='A') {
		digitalWrite(in1, LOW);
	  	digitalWrite(in2, HIGH);
	  	analogWrite(enA,0);
	} 

	if(motor=='B') {
		digitalWrite(in3, LOW);
	  	digitalWrite(in4, HIGH);
	  	analogWrite(enA,0);
	}
	
}