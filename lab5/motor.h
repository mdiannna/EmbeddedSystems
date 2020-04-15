
#ifndef MOTOR_H_
#define MOTOR_H_

// Motor A
#define enA 10
#define in1 11
#define in2 12

// Motor B
// #define in3 22
// #define in4 24
// #define enB 13

#define in3 5
#define in4 4
#define enB 3


void InitMotor(); //motor A
void InitMotorA(); //motor A
void InitMotorB(); //motor B

void MotorForward(int speed); //motor A
void MotorForward(char motor, int speed);

void MotorBackward(int speed); //motor A
void MotorBackward(char motor, int speed);


void MotorStop(); //motor A
void MotorStop(char motor);
void MotorsStop(); // both motors
void MotorsInit(); // both motors



#endif