//https://github.com/sadr0b0t/arduino-timer-api/tree/master/src/avr
//https://habr.com/en/post/337430/

#include "timer-api.h"
#include "tasks.h"
#include "led.h"
#include "myserial.h"
#include "light.h"
#include "car.h"
#include "motor.h"
#include "encoder.h"
#include "analoglibrary.h"
#include "light.h"

void timer_handle_interrupts(int timer) {
  if(--rec_cnt_A <=0) {
    TaskA();
    rec_cnt_A = REC_A;
  }
  
  if(--rec_cnt_B <=0) {
    TaskA();
    rec_cnt_B = REC_B;
  }
}

void setup() {
  SerialInit();
  LEDs_Init();
  InitLight();
  ConditionerInit();
  EncoderInit();
  InitCar();
  InitBMPSensor(); // for temperature, altitude and pressure
  LightSensorInit();
}

void loop() {
  // put your main code here, to run repeatedly:
}
