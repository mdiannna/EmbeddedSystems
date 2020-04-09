//https://github.com/sadr0b0t/arduino-timer-api/tree/master/src/avr
//https://habr.com/en/post/337430/

#include "timer-api.h"
#include "tasks.h"

// components
#include "led.h"
#include "myserial.h"
#include "light.h"
#include "car.h"
#include "motor.h"
#include "encoder.h"
#include "analoglibrary.h"
#include "light.h"
#include "mystdio.h"


double temperatureVal = 0.0;
double pressureVal = 0.0;
double relativePressureVal = 0.0;



void timer_handle_interrupts(int timer) {
  if(--rec_cnt_BMPTP <=0) {
    TaskReadBMPTemperatureProvider();
    rec_cnt_BMPTP = REC_BMPTP;
  }
  
  if(--rec_cnt_BMPPPC <=0) {
    TaskReadBMPPressureProviderConsumer();
    rec_cnt_BMPPPC = REC_BMPPPC;
  }

  if(--rec_cnt_BMPRPC <=0) {
    TaskReadBMPRelPressureConsumer();
    rec_cnt_BMPRPC = REC_BMPRPC;
  }

  if(--rec_cnt_CONDIT_ON_OFF <=0) {
    TaskConditionerOnOffConsumer();
    rec_cnt_CONDIT_ON_OFF = REC_CONDIT_ON_OFF;
  }
}

void setup() {
  SerialInit();
  MystdioInit();
  LEDs_Init();
  InitLight();
  ConditionerInit();
  EncoderInit();
  InitCar();
  InitBMPSensor(); // for temperature, altitude and pressure
  LightSensorInit();
}


void loop() {
  // TODO: test
  printf("Current temperature:");
  Serial.print(temperatureVal);
  printf("\n");

  printf("Current pressure:");
  Serial.print(pressureVal);
  printf("\n");

  printf("Current relative pressure:");
  Serial.print(relPressureVal);
  printf("\n");  
}
