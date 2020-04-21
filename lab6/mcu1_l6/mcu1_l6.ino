// Master I2C

#include <Arduino.h>
#include "communication.h"
#include "myi2c.h"

const int pingPin = 7; // Trigger Pin of Ultrasonic Sensor
const int echoPin = 6; // Echo Pin of Ultrasonic Sensor


long microsecondsToCentimeters(long microseconds)
{
   return microseconds / 29 / 2;
}


// String a;
char a;

void setup() {
	CommunicationInit();
    InitI2C();
	Serial.println("Initialization done");
}

int GetSensorData() {
  long duration, inches, cm;
    pinMode(pingPin, OUTPUT);
    digitalWrite(pingPin, LOW);
    delayMicroseconds(2);
    digitalWrite(pingPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(pingPin, LOW);

    pinMode(echoPin, INPUT);
    duration = pulseIn(echoPin, HIGH);
    cm = microsecondsToCentimeters(duration);

    Serial.print("Real cm:");
    Serial.print(cm);
    Serial.println();
    
    cm += random(1, 10);
    Serial.print("Send cm:");
    Serial.print(cm);
    Serial.println();

    // Simulation without sensor:
    return cm;
}

void loop() {
	int command = ReceivePacket();
	if(command == COMMAND_SEND_SENSOR_DATA) {
		int cm = GetSensorData();
        SendI2C(cm);
  }
	delay(1000);
}
