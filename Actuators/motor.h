
#ifndef MOTOR_H_
#define MOTOR_H_

// Motor A
#define enA 10
#define in1 11
#define in2 12

// Motor B
#define enB 13
#define in3 22
#define in4 24

void InitMotorA();
void InitMotorB();
void MotorForward(char motor, int speed);
void MotorBackward(char motor, int speed);
void MotorStop(char motor);
void MotorsStop();

#endif