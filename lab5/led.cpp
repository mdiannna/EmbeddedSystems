#include "led.h"
#include <Arduino.h>
#include <Wire.h>


void LED_Init(int led_pin) {
  pinMode(led_pin, OUTPUT);//Change to output my pins
  digitalWrite(led_pin,LED_OFF);//Turn off LED
}

void LEDs_Init() {
  LED_Init(RED_LED_PIN);
  LED_Init(GREEN_LED_PIN);
  LED_Init(BLUE_LED_PIN);
}

int Is_RED_LED_On() {
  int LEDState = digitalRead(RED_LED_PIN);
  if(LEDState==LED_ON) {
    return 1;
  }
//else
  return 0;
}

int Is_GREEN_LED_On() {
  int LEDState = digitalRead(GREEN_LED_PIN);
  if(LEDState==LED_ON) {
    return 1;
  }
//else
  return 0;
}

int Is_BLUE_LED_On() {
  int LEDState = digitalRead(BLUE_LED_PIN);
  if(LEDState==LED_ON) {
    return 1;
  }
//else
  return 0;
}

void Turn_LED_On(int led_pin) {
  digitalWrite(led_pin,LED_ON);
}

void Turn_LED_Off(int led_pin) {
  digitalWrite(led_pin,LED_OFF);
}


/************************
 Functions for blue LED - default
 ************************/
int Is_LED_On() {
  return Is_BLUE_LED_On();
}

void LED_On() {
  Turn_LED_On(BLUE_LED_PIN);
}

void LED_Off() {
  Turn_LED_Off(BLUE_LED_PIN);
}
