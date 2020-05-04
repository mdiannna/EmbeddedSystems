#include "led.h"


void LEDInit() {
	pinMode(LED_PIN, OUTPUT);
}


void LEDSetState(int state) {
	digitalWrite(LED_PIN, state);
}