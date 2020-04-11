#include "encoder.h"
#include <Arduino.h>
#include "motor.h"
#include "mystdio.h"

int maxTimeOneRotation;

void EncoderInit() {
  printf("Encoder is initializing... please wait...");
  pinMode(ENCODER_PIN,INPUT);
  MotorForward(165);

  delay(1000);
  
  MotorForward(255);
  delay(3000);
  
  while(ReadEncoderValue()!=1);
  unsigned long startTime = millis();
  delay(50);
  while(ReadEncoderValue()!=1);
  unsigned long elapsedTime = millis()-startTime;
  Serial.println("max time 1 rotation:");
  Serial.println(elapsedTime);
  maxTimeOneRotation = elapsedTime;
  delay(3000);
}

double ReadEncoderValue() {
   int value = digitalRead(ENCODER_PIN);
   return value;
}
