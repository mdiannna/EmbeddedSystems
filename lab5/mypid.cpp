#include "mypid.h"
#include <PID_v1.h>
#include <Arduino.h>
#include "motor.h"

double Setpoint, Input, Output;

//Specify the links and initial tuning parameters
// Kp, Ki, Kd
PID myPID(&Input, &Output, &Setpoint,600,100,10, DIRECT);


void PID_Init() {
  //turn the PID on
  myPID.SetMode(AUTOMATIC);

  //kp = aTune.GetKp();
 // ki = aTune.GetKi();
 // kd = aTune.GetKd();
 // myPID.SetTunings(kp,ki,kd);
}

void PID_SetInput(double input) {
	Input = map(Input, 0, MAX_MOTOR_SPEED, 0, 255);  //Scales 0-1023 to 0-255 (or whatever you want)
	myPID.Compute();
}

double PID_GetOutput() {
	return Output;
}