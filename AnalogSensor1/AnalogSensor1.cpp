#include <Arduino.h>
#include "photoresistor.h"
#include "mystdio.h"

void setup() {
	Serial.begin(9600);
	pinMode(13, OUTPUT);

	SerialInit();
	PhotoresistorInit();

}

void loop() {
	Serial.write("Hello!");
	delay(1000);
	  digitalWrite(13, 0);
	    delay(1000);
	    digitalWrite(13, 1);
	    delay(1000);
}
