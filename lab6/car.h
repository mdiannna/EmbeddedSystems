
#ifndef CAR_H_
#define CAR_H_

#define TURN_POWER 40


void InitCar();


void MoveForward(int power);
void MoveBackward(int power);

void MoveForward();
void MoveBackward();

void TurnLeft();
void TurnRight();
void StopCar();

void SetCarSpeed(int);

#endif
