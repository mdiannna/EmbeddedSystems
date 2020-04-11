/*
 * photoresistor.h
 *
 *  Created on: Feb 22, 2020
 *      Author: mdiannna
 */

#ifndef LIGHTSENSOR_H_
#define LIGHTSENSOR_H_

#define PHOTORESISTOR_PIN 0 //A0

void LightSensorInit();
int ReadLightLevel();

float VoltageToResistance(float R, float Vin, float Vout);
float ResistanceToLumen(int resistance);

#endif /* LIGHTSENSOR_H_ */
