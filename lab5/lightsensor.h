/*
 * photoresistor.h
 *
 *  Created on: Feb 22, 2020
 *      Author: mdiannna
 */

#ifndef LIGHTSENSOR_H_
#define LIGHTSENSOR_H_

#include "analoglibrary.h"
#define PHOTORESISTOR_PIN 0 //A0

// #define R 10000 //ohm resistance value
#define R 15000 //ohm resistance value
// float R = 15000;

#define Vin 5.0 // input voltage

// extern float * buffLight;
// extern float * buffLight2;
// extern int cntLight;
// extern float median;

void LightSensorInit();
void LightSensorFiltersInit();
int ReadLightLevel();

float VoltageToResistance(float Vout);
float ResistanceToLumen(int resistance);

void showLightResults(float lightLevel);
float calcLux(float lightLevel);
float MyFilter(float lightLevel) ;
#endif /* LIGHTSENSOR_H_ */
