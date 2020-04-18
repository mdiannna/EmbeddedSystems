
#include <Arduino.h>
#include "communication.h"

void SerialInit() {
	Serial.begin(9600);	
}

void setup() {
	SerialInit();
	// TODO:
	// I2CInit()
	delay(1000);
	SendHello();
	
	int data = ReceiveData();
	if(data != -1) {
		Serial.print("Received data:");
		Serial.println(data);
	}
}



// TODO: se poate de pus totul ca ReadSensorData();
void loop() {
	// cerere prin serial de date de la MCU1
	QuerySensorData();
	delay(100);

	int data = ReceiveData();
	if(data != -1) {
		Serial.print("Received data:");
		Serial.println(data);
	}
	
	delay(2000);
}
