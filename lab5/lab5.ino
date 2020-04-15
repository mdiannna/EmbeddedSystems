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


#define NR_OF_TASKS 5
// int rec_cnts[NR_OF_TASKS] = { OFFS_TP, OFFS_CONDIT_ON_OFF, OFFS_GET_KPD, OFFS_READ_SCHAR, OFFS_CHK_PWD };
int rec_cnts[NR_OF_TASKS] = { OFFS_TP, OFFS_CONDIT_ON_OFF, OFFS_GET_KPD, OFFS_TURN_LIGHTS_ON, OFFS_BTN_LED_1};
// int rec_values[NR_OF_TASKS] = { REC_TP, REC_CONDIT_ON_OFF, REC_GET_KPD, REC_READ_SCHAR, REC_CHK_PWD };
// int rec_values[NR_OF_TASKS] = { REC_TP, REC_CONDIT_ON_OFF, REC_GET_KPD, REC_CHK_PWD, REC_TURN_LIGHTS_ON };
int rec_values[NR_OF_TASKS] = { REC_TP, REC_CONDIT_ON_OFF, REC_GET_KPD, REC_TURN_LIGHTS_ON, REC_BTN_LED_1 };
void (*fp[NR_OF_TASKS])() = { 
                    TaskReadTemperatureProvider, 
                    TaskConditionerOnOffConsumer, 
                    TaskReadKeypadCharPwd,
                    // TaskReadSerialChar,
                    // TaskChechPassword,
                    TaskTurnCarLightsOn,
                    TaskButtonLedLab1
                };

void timer_handle_interrupts(int timer) {
  for(int i=0; i<NR_OF_TASKS; i++) {
    if(--rec_cnts[i] <=0) {
     (*fp[i])();
      rec_cnts[i] = rec_values[i];
    } 
  }
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
  // PasswordInit();
  printf("Initializing timer");
  delay(1000);
  timer_init_ISR_1KHz(TIMER_DEFAULT);
}


void loop() {
  printf("\n\rTemperature:");
  Serial.print(temperatureVal);
  printf("\n\r Char keypad: %c", charKeypad);
  // printf(" Password:");
  // Serial.print(password);
  // printf(" Correct pwd?: %d", passwordIsCorrect);
  printf("\n\rChar serial:%c", charSerial);
  Serial.println("Is light on???");
  Serial.println(IsLightOn());
}
