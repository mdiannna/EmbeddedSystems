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
#include "lightsensor.h"
#include "mystdio.h"
#include "conditioner.h"
#include "password.h"
//#include "temperature.h"

int rec_cnt_TP = OFFS_TP;
int rec_cnt_CONDIT_ON_OFF = OFFS_CONDIT_ON_OFF;

#define OFS_A 1000
#define REC_A 1000
int rec_cnt_A = OFS_A;


#define OFS_B 5000
#define REC_B 500
int rec_cnt_B = OFS_B;

void TaskA() {
 Serial.println("Task A");
}

void TaskB() {
 Serial.println("Task B"); 
}


#define NR_OF_TASKS 5
int rec_cnts[NR_OF_TASKS] = { OFS_A, OFS_B, OFFS_TP, OFFS_CONDIT_ON_OFF, OFFS_GET_KPD };
int rec_values[NR_OF_TASKS] = { REC_A, REC_B, REC_TP, REC_CONDIT_ON_OFF, REC_GET_KPD };
void (*fp[NR_OF_TASKS])() = { 
                    TaskA,
                    TaskB, 
                    TaskReadTemperatureProvider, 
                    TaskConditionerOnOffConsumer, 
                    TaskReadKeypadCharPwd 
                };

void timer_handle_interrupts(int timer) {
  for(int i=0; i<NR_OF_TASKS; i++) {
    if(--rec_cnts[i] <=0) {
     (*fp[i])();
      rec_cnts[i] = rec_values[i];
    } 
  }
 //  if(--rec_cnt_A <=0) {
 //    TaskA();
 //    rec_cnt_A = REC_A;
 //  }
 //  if(--rec_cnt_TP <=0) {
 //    TaskReadTemperatureProvider();
 //    rec_cnt_TP = REC_TP;
 //  }

 // if(--rec_cnt_CONDIT_ON_OFF <=0) {
 //   TaskConditionerOnOffConsumer();
 //   rec_cnt_CONDIT_ON_OFF = REC_CONDIT_ON_OFF;
 // }
}



void setup() {
  SerialInit();
  MystdioInit();
  LEDs_Init();
  InitLight();
  ConditionerInit();
  PasswordInit();
  //  EncoderInit();
  InitCar();
  LightSensorInit();
  PasswordInit();
  printf("Initializing timer");
  delay(1000);
  timer_init_ISR_1KHz(TIMER_DEFAULT);
}


void loop() {
  printf("\n\rTemperature:");
  Serial.print(temperatureVal);
  printf(" Char keypad: %c", charKeypad);
  printf(" Password: %s", password);
  printf(" Correct pwd?: %d", passwordIsCorrect);
}
