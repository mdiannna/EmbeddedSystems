#include "button.h"


void ButtonInit() {
	pinMode(BUTTON_PIN, INPUT);
}


int ReadButton() {
 return digitalRead(BUTTON_PIN);
}