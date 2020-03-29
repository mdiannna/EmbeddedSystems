// https://tutorial.cytron.io/2012/06/22/pid-for-embedded-design/
// Libraries:
// https://github.com/br3ttb/Arduino-PID-AutoTune-Library/blob/master/PID_AutoTune_v0
// https://github.com/br3ttb/Arduino-PID-Library/blob/master/

/********************************************************
 * PID Basic Example
 * Reading analog input 0 to control analog PWM output 3
 ********************************************************/

#include "PID_v1.h"
#include "PID_AutoTune_v0.h"
#include "motor.h"
#include "encoder.h"

double Setpoint, Input, Output;

//Specify the links and initial tuning parameters
// Kp, Ki, Kd
PID myPID(&Input, &Output, &Setpoint,2,5,1, DIRECT);
PID_ATune aTune(&Input, &Output);


void AutoTuneInit() {
    tuning=false;
    changeAutoTune();
    tuning=true;
}


void AutoTuneHelper(boolean start)
{
  if(start)
    ATuneModeRemember = myPID.GetMode();
  else
    myPID.SetMode(ATuneModeRemember);
}


void changeAutoTune()
{
 if(!tuning)
  {
    //Set the output to the desired starting frequency.
    output=aTuneStartValue;
    aTune.SetNoiseBand(aTuneNoise);
    aTune.SetOutputStep(aTuneStep);
    aTune.SetLookbackSec((int)aTuneLookBack);
    AutoTuneHelper(true);
    tuning = true;
  }
  else
  { //cancel autotune
    aTune.Cancel();
    tuning = false;
    AutoTuneHelper(false);
  }
}

void PID_Init() {
	//turn the PID on
	myPID.SetMode(AUTOMATIC);

	kp = aTune.GetKp();
	ki = aTune.GetKi();
	kd = aTune.GetKd();
	myPID.SetTunings(kp,ki,kd);
}

void SerialInit() {
   Serial.begin(9600);
}

void setup()
{
  SerialInit();
  //initialize the variables we're linked to
  Input = ReadEncoderValue();
  Setpoint = 100;

  AutoTuneInit();
  PID_Init();
}

void loop()
{
  Input = ReadEncoderValue();
  myPID.Compute();
  MotorForward(Output);
}
