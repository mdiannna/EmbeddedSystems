/*
 * analoglibrary.cpp
 *
 *  Created on: Feb 22, 2020
 *      Author: mdiannna
 */
#include "analoglibrary.h"
#include <Arduino.h>
#include <Wire.h>
#include <stdio.h>
#include "mystdio.h"


//TODO:
float ADCtoVoltage(float value) {
	// Convert the raw data value (0 - 1023) to voltage (0.0V - 5.0V):
	float voltage = value * (5.0 / 1024.0);
	return voltage;
}

void sort(float * arr, int n) {
	for(int i=1; i<n; i++) {
		int j = arr[i];
		int k;

		for(k=i-1; (k>=0) && (j<arr[k]); k--) {
			arr[k+1] = arr[k];
		}
	}
}

//TODO
float SaltAndPepperFilter(float * buff) {
	sort(buff, 3);
	float median = buff[1];
	printf("Median:");
	Serial.println(median);
	return median;
}

//TODO
//Filtru medie ponderata
void WeightedAverageFilter() {

}


