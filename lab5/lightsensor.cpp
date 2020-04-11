/*
 * photoresistor.c
 *
 *  Created on: Feb 22, 2020
 *      Author: mdiannna
 */


#include "lightsensor.h"

#include <stdio.h>
#include <avr/io.h>
#include <Arduino.h>

void LightSensorInit() {
	printf("Light sensor init");
}

int ReadLightLevel() {
	 int lightLevel = analogRead(PHOTORESISTOR_PIN);
	 return lightLevel;
}

float ResistanceToLumen(int resistance) {
	//return 500/(resistance/1000); // Conversion resistance to lumen
	float result = 500.00/resistance;
	return result;
}

float VoltageToResistance(float R, float Vin, float Vout) {
	//int Rl = (R*Vin)/Vout - R;
//	Alternative formula:
	printf("Vin:");
	Serial.println(Vin);
	printf("Vout:");
	Serial.println(Vout);

	float Rl = (R * (Vin - Vout))/Vout;
	return Rl;
}


