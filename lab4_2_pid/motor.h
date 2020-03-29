
#ifndef MOTOR_H_
#define MOTOR_H_

// Motor A
#define enA 10
#define in1 11
#define in2 12

void InitMotor();
void MotorForward(int speed);
void MotorBackward(int speed);
void MotorStop();

#endif