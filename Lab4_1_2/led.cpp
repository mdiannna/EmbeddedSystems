#include "led.h"
#include <Arduino.h>
#include <Wire.h>

void LEDs_Init() {
  pinMode(GREEN_LED_PIN, OUTPUT);//Change to output my pins
  pinMode(RED_LED_PIN, OUTPUT);
  digitalWrite(GREEN_LED_PIN,LED_OFF);//Turn off LED
  digitalWrite(RED_LED_PIN,LED_OFF);//Turn off LED
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

void Turn_LED_On(int led_pin) {
  digitalWrite(led_pin,LED_ON);
}

void Turn_LED_Off(int led_pin) {
  digitalWrite(led_pin,LED_OFF);
}
