#include "led.h"

void ConditionerInit() {
  LEDs_Init();
}

void TurnConditionerOn() {
  Turn_LED_Off(GREEN_LED_PIN);
  Turn_LED_On(RED_LED_PIN);
}

void TurnConditionerOff() {
  Turn_LED_Off(RED_LED_PIN);
  Turn_LED_On(GREEN_LED_PIN);
}


int IsConditionerTurnedOn() {
  if(Is_RED_LED_On()==1 && Is_GREEN_LED_On()==0) {
    return 1;
  }
  return 0;
}

int IsConditionerTurnedOff() {
  if(Is_RED_LED_On()==0) {
    return 1;
  }
  return 0;
}
