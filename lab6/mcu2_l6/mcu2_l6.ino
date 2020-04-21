// Slave I2C

#include <Arduino.h>
#include "communication.h"
#include <Wire.h>
int sensorData;

void InitI2C() {
	Wire.begin(9); 
  	// Attach a function to trigger when something is received.
  	Wire.onReceive(ReceiveEvent);
}

void setup() {
	CommunicationInit();
	InitI2C();

	Serial.println("Init done MCU2");
	delay(1000);
	SendHello();
	
	int data = ReceiveData();
	if(data != -1) {
		Serial.print("Received data:");
		Serial.println(data);
	}
}


void ReceiveEvent(int bytes) {
  	sensorData = Wire.read();    // read one character from the I2C
  	Serial.println();
  	Serial.print("I2C receive sensor data: ");
 	Serial.print(sensorData);
 	Serial.println();
}

void loop() {
	// cerere prin serial de date de la MCU1
	QuerySensorData();
	delay(5000);
}
