#include "button.h"
#include <Arduino.h>

void ButtonInit() {
	pinMode(BUTTON_PIN, INPUT_PULLUP);
}

int IsButtonPressed() {
	int buttonState = digitalRead(BUTTON_PIN);
	if(buttonState==BUTTON_PRESSED) {
		return 1;
	}
//else
	return 0;
}

int IsButtonReleased() {
	int buttonState = digitalRead(BUTTON_PIN);
	if(buttonState==BUTTON_RELEASED) {
		return 1;
	}
//else
	return 0;
}
