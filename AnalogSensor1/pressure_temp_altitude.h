/*
 * pressure_temp_altitude.h
 *
 *  Created on: Feb 26, 2020
 *      Author: mdiannna
 */

#ifndef PRESSURE_TEMP_ALTITUDE_H_
#define PRESSURE_TEMP_ALTITUDE_H_

void InitBMPSensor();
void TestSensorBMP();
double SensorGetTemperature();
double SensorGetPressure(double T);
double SensorGetRelativePressure(double P);
double SensorGetAltitude(double P, double p0);

#endif /* PRESSURE_TEMP_ALTITUDE_H_ */
