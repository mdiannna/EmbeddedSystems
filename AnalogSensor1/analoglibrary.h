/*
 * analoglibrary.h
 *
 *  Created on: Feb 22, 2020
 *      Author: mdiannna
 */

#ifndef ANALOGLIBRARY_H_
#define ANALOGLIBRARY_H_

float ADCtoVoltage(int value);
void SaltAndPepperFilter();
//Filtru medie ponderata
void WeightedAverageFilter();


#endif /* ANALOGLIBRARY_H_ */
