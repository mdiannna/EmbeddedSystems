/*
 * photoresistor.c
 *
 *  Created on: Feb 22, 2020
 *      Author: mdiannna
 */


#include <stdio.h>
#include <avr/io.h>
#include <Arduino.h>
#include "photoresistor.h"

void PhotoresistorInit() {
	printf("Photoresistor init");
}

int ReadLightLevel() {
	 int lightLevel = analogRead(PHOTORESISTOR_PIN);
	 return lightLevel;
}

int ResistanceToLumen(int resistance) {
	return 500/(resistance/1000); // Conversion resistance to lumen
}

int VoltageToResistance(int R, float Vin, float Vout) {
	int Rl = (R*Vin)/Vout - R;
//	Alternative formula:
	//int Rl = (R * (Vin - Vout))/Vout;
	return Rl;
}


