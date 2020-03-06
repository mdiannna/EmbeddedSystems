
#ifndef MOTOR_H_
#define MOTOR_H_

void InitMotorA();
void InitMotorB();
void MotorForward(char motor, int speed);
void MotorBackward(char motor, int speed);
void MotorStop(char motor);

#endif