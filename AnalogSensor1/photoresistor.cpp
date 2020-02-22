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



