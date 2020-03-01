/*
 * analoglibrary.h
 *
 *  Created on: Feb 22, 2020
 *      Author: mdiannna
 */

#ifndef ANALOGLIBRARY_H_
#define ANALOGLIBRARY_H_

float ADCtoVoltage(float value);
void SaltAndPepperFilter();
//Filtru medie ponderata
void WeightedAverageFilter();

float SaltAndPepperFilter(float * buff);

#endif /* ANALOGLIBRARY_H_ */
