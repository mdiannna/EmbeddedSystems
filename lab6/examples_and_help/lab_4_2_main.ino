#include “motor.h”
#include “encoder.h”
#include <PID_AutoTune_v0.h>
#include <PID_v1.h>

double Setpoint, Input, Output;

//Specify the links and initial tuning parameters
// Kp, Ki, Kd
PID myPID(&Input, &Output, &Setpoint,600,100,10, DIRECT);
PID_ATune aTune(&Input, &Output);

void PID_Init() {
  //turn the PID on
  myPID.SetMode(AUTOMATIC);
}

void SerialInit() {
   Serial.begin(9600);
}

unsigned long currentTime;
unsigned long prevTime;


void TimeInit() {
  currentTime = millis();
  prevTime = millis();
}

void setup()
{
  TimeInit();
  SerialInit();
  Setpoint = 230;

  //AutoTuneInit();
  // TunePID();
  EncoderInit();
  PID_Init();    
}


double CalculateMotorSpeed(unsigned long time_1_rotation) {
  //return 1000.0/time_1_rotation;
  return 10000/time_1_rotation;
}

unsigned long CalculateElapsedTime(unsigned long prevTime, unsigned long currentTime) {
  return currentTime - prevTime;
}

int AdjustKp(int kp, int ki, int kd) {
  Serial.println("Adjust kp");
  Serial.println(kp);
  myPID.Compute();
  //Wait for overshooting
  while(Output <Setpoint) {
     Serial.println("kp:");
     Serial.println(kp);
     Serial.println("Output:");
     Serial.println(Output);
     Serial.println("Input:");
     Serial.println(Input);
     Serial.println("Setpoint");
     Serial.println(Setpoint);
     kp+=100;
     myPID.SetTunings(kp,ki,kd);

     myPID.Compute();
  }
  
  Serial.println("kp overshooting");
  Serial.println(kp);
  kp = kp/2;
  Serial.println(kp);
  return kp;
}

int AdjustKi(int kp, int ki, int kd) {
  myPID.SetTunings(kp,ki,kd);
  myPID.Compute();
  while(Output <Setpoint) {
    ki=10; 
    myPID.SetTunings(kp,ki,kd);

 
    myPID.Compute();

    Serial.println("ki overshooting");
    Serial.println(ki);
    ki = ki/2;
    AdjustKp(kp,ki,kd);
    Serial.println(ki);
  }
  return ki;
}

int AdjustKd(int kp, int ki, int kd) {
    kd++;
    return kd;
}

void TunePID() {
  Serial.println("Tune PID");
  int kp = 1;
  int ki = 1;
  int kd = 1;
  Output = 0;
  Setpoint = 200;
  Input = maxTimeOneRotation/2;
  
  kp = 10;
    myPID.SetTunings(kp,ki,kd);

  kp = AdjustKp(kp, ki, kd);
  myPID.SetTunings(kp,ki,kd);
  
  ki = 10;
  myPID.SetTunings(kp,ki,kd);
  kp = AdjustKp(kp,ki,kd);
  myPID.SetTunings(kp,ki,kd);
  ki = AdjustKi(kp, ki, kd);
  myPID.SetTunings(kp,ki,kd);
  
  kd = 3;
  myPID.SetTunings(kp,ki,kd);
  kp = AdjustKp(kp,ki,kd);
  myPID.SetTunings(kp,ki,kd);
  ki = AdjustKi(kp, ki, kd);
  myPID.SetTunings(kp,ki,kd);
  kd = AdjustKd(kp, ki, kd);
  myPID.SetTunings(kp,ki,kd);

  Serial.println("--------");
  Serial.println("test after adjunsting:");
  myPID.Compute();
  Serial.println("Output:");
  Serial.println(Output);
  Serial.println("Setpoint:");
  Serial.println("Setpoint");
  
}

int motorSpeed; 
void loop()
{
  
  // O rotatie completa
  if(ReadEncoderValue()==1) {
    prevTime = currentTime;
    currentTime = millis();

    //  motorSpeed = 110;
    unsigned long elapsedTime = CalculateElapsedTime(prevTime, currentTime);
    Serial.println("Elapsed Time:");
    Serial.println(elapsedTime);
    motorSpeed = CalculateMotorSpeed(elapsedTime);
    Serial.println("---Motor speed:----");
    Serial.println(motorSpeed);
  }

  Input = motorSpeed;
  Serial.println("Input:");
  Serial.print(Input);
  Input = map(Input, 0, maxTimeOneRotation, 0, 255);  
  myPID.Compute();

  Serial.println("Input:");
  Serial.print(Input);
  Serial.println("Output:");
  Serial.print(Output);
  
  MotorForward(Output);
 
}
