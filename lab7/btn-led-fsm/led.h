#ifndef _LED_H_
#define _LED_H_
	

#define LED_OFF_STATE 0
#define LED_ON_STATE 1

#define LED_PIN 2

#include <Arduino.h>

void LEDInit();
void LEDSetState(int);

#endif
