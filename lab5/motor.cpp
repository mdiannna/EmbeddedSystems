#include <Arduino.h>
#include <avr/io.h>

#include "motor.h"

void InitMotor() {
    pinMode(enA, OUTPUT);
    pinMode(in1, OUTPUT);
    pinMode(in2, OUTPUT); 
}

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

void MotorsInit() {
    InitMotorA();
    InitMotorB();
}

// Motor A
void MotorForward(int speed) {
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
    analogWrite(enA,speed);
}

void MotorForward(char motor, int speed) {
    if(motor=='A') {
        digitalWrite(in1, LOW);
        digitalWrite(in2, HIGH);
        analogWrite(enA,speed);
    }
    if(motor=='B') {
        digitalWrite(in3, LOW);
        digitalWrite(in4, HIGH);    
        analogWrite(enB,speed);
    }

}


// Motor A
void MotorBackward(int speed) {
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    // analogWrite(enA,PowerToSpeed(power));
    analogWrite(enA,speed);
}


void MotorBackward(char motor, int speed) {
    if(motor=='A') {
        digitalWrite(in1, HIGH);
        digitalWrite(in2, LOW);
        // analogWrite(enA,PowerToSpeed(power));
        analogWrite(enA,speed);
    }
    if(motor=='B') {
        digitalWrite(in3, HIGH);
        digitalWrite(in4, LOW); 
        // analogWrite(enB,PowerToSpeed(power));
        analogWrite(enB,speed);
    }

}


// Motor A
void MotorStop() {
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);
    analogWrite(enA,0); 
}

void MotorStop(char motor) {
    if(motor=='A') {
        digitalWrite(in1, LOW);
        digitalWrite(in2, LOW);
        analogWrite(enA,0);
    } 

    if(motor=='B') {
        digitalWrite(in3, LOW);
        digitalWrite(in4, LOW);
        analogWrite(enA,0);
    }
    
}

void MotorsStop() {
    MotorStop('A');
    MotorStop('B');
}






