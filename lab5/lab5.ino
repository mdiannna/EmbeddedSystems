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
//#include "pressure_temp_altitude.h"
//#include "bmp_pressure_temp_altitude.h"
#include "BMP085NB.h"


int rec_cnt_BMPTP = OFFS_BMPTP;
int rec_cnt_BMPPPC = OFFS_BMPPPC;
int rec_cnt_BMPRPC = OFFS_BMPRPC;
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

void TaskC() {
  
}

void TaskTemperatureNewBMP() {
  Serial.println("Get temperature with new BMP sensor");
 // temperatureVal = GetTemperature();
}

double SensorGetTemperature2(){
 double T = 0.02;
    return T;
    }




BMP085NB bmp;

int temperature = 0;
long pressure = 0;
float alti = 130.0;

void BMPInitNB() {
  bmp.initialize();
  bmp.setSeaLevelPressure(100600);
}

void BMPReadData() {
  Serial.println("Read data");
  bmp.pollData(&temperature, &pressure, &alti);  
  Serial.println("Read data");
  
  if (bmp.newData) {
      Serial.print("Temp: ");
    Serial.print(temperature / 10);
    Serial.print("degC Pres: ");
    Serial.print(pressure, DEC);
    Serial.print("Pa Alt: ");
    Serial.print(alti);

  }
}
    
void TaskBMPReadValues() {
Serial.println("BMP read data");
 
 LED_On();
 BMPReadData(); 
 LED_Off();
}

void timer_handle_interrupts(int timer) {
  if(--rec_cnt_A <=0) {
    TaskA();
    rec_cnt_A = REC_A;
  }
  
  if(--rec_cnt_B <=0) {
    TaskB();
    rec_cnt_B = REC_B;
  }
  if(--rec_cnt_BMPTP <=0) {
    TaskBMPReadValues();
    rec_cnt_BMPTP = REC_BMPTP;
  }
//  
//  if(--rec_cnt_BMPPPC <=0) {
//    TaskReadBMPPressureProviderConsumer();
//    rec_cnt_BMPPPC = REC_BMPPPC;
//  }
//
//  if(--rec_cnt_BMPRPC <=0) {
//    TaskReadBMPRelPressureConsumer();
//    rec_cnt_BMPRPC = REC_BMPRPC;
//  }
//
//  if(--rec_cnt_CONDIT_ON_OFF <=0) {
//    TaskConditionerOnOffConsumer();
//    rec_cnt_CONDIT_ON_OFF = REC_CONDIT_ON_OFF;
//  }
}



void setup() {
 
//
  SerialInit();
  MystdioInit();
  LEDs_Init();
  InitLight();
  ConditionerInit();
//  EncoderInit();
  InitCar();
  //InitBMPSensor(); // for temperature, altitude and pressure
//  InitBMPSensor() ;
BMPInitNB();
Serial.println("BMP Init");
  LightSensorInit();
  delay(1000);
  printf("Initializing timer");
 timer_init_ISR_1KHz(TIMER_DEFAULT);
}


void loop() {
  // TODO: test
//  printf("\n\rCurrent temperature:");
//  Serial.print(temperatureVal);
//  printf("\n");
//
//  printf("\nCurrent pressure:");
//  Serial.print(pressureVal);
//  printf("\n");
//
//  printf("\nCurrent relative pressure:");
//  Serial.print(relPressureVal);
//  printf("\n");  
}
