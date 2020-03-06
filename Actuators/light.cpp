
#include "light.h"
#include "led.h"
#include <Arduino.h>

void InitLight() {
	LED_Init();
}

void LightOn() {
	LED_On();
}

void LightOff() {
	LED_Off();
}


int IsLightOn() {
	return Is_LED_On();
}