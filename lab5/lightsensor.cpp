/*
 * photoresistor.c
 *
 *  Created on: Feb 22, 2020
 *      Author: mdiannna
 */


#include "lightsensor.h"
#include "analoglibrary.h"
#include <stdio.h>
#include <avr/io.h>
#include <Arduino.h>


float * buffLight;
float * buffLight2;
int cntLight = 0;
float median = 0;


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

float VoltageToResistance( float Vout) {
	//	Alternative formula:
	//int Rl = (R*Vin)/Vout - R;
	float Rl = (R * (Vin - Vout))/Vout;
	return Rl;
}


void LightSensorFiltersInit() {
	buffLight = (float *) malloc(3*sizeof(float));
	buffLight2 = (float *) malloc(3*sizeof(float));
	buffLight[0] = 0.0;
	buffLight[1] = 0.0;
	buffLight[2] = 0.0;

	buffLight2[0] = 0.0;
	buffLight2[1] = 0.0;
	buffLight2[2] = 0.0;
}


void showLightResults(float lightLevel) {
	printf("\n-------\n");
	printf("\n");
	float Vout = ADCtoVoltage(lightLevel);
	float resistance = VoltageToResistance(Vout);

	//printf("LIGHT LEVEL: %d\n\r", lightLevel);
	printf("LIGHT LEVEL:\n\r");
	Serial.println(lightLevel);

	//printf("Voltage: %.2f\n\r", Vout);
	Serial.println(Vout);

	printf("Resistance: %d\n\r", resistance);
	Serial.println(resistance);



	float lux = ResistanceToLumen(resistance);
	printf("Light intensity(lumen) - physical parameter: %f\n\r");
	Serial.print(lux);
	printf("\n-------\n");
}

float calcLux(float lightLevel) {
	float Vout = ADCtoVoltage(lightLevel);
	float resistance = VoltageToResistance(Vout);
	float lux = ResistanceToLumen(resistance);

	return lightLevel;
}

float MyFilter(float lightLevel) {
	if(cntLight==3){
		cntLight = 0;
	}

	buffLight[cntLight] = lightLevel;

	median = SaltAndPepperFilter(buffLight);
	// printf("median:");
	// Serial.println(median);
	PushQueue(buffLight2, median, 3);
	cntLight++;

	return WeightedAverageFilter(buffLight2, 3);
}