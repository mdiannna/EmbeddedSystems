#include <Arduino.h>
#include "communication.h"

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
	Serial.println("Initialization done");
}

void loop() {
	ReceivePacket();

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
  
  Serial.print(cm);
  Serial.print("cm");
  Serial.println();
  
  delay(100);
}