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
	float temp;
	for(int i=0; i<n; i++) {
		
		for(int k=i+1; k<n; k++) {
			if(arr[k] < arr[i]) {			
				temp = arr[k];
				arr[k] = arr[i];
				arr[i] = temp;
			}
		}
	}
	printArr(arr, 3);
}


// filter.cpp
float SaltAndPepperFilter(float * buff) {
	sort(buff, 3);
	float median = buff[1];
	printf("Median:");
	cout << median << "\n";
	// Serial.println(median);
	return median;
}


//Filtru medie ponderata
float WeightedAverageFilter(float * buff, int n) {
	float weights[3] = {0.25, 0.5, 0.75};
	float sum = 0;

	for(int i=0; i<n; i++) {
		sum += weights[i] * buff[i];
	}
	return sum/3.0;
}

void PushQueue(float * buff, float value, int size) {
	for(int i=size-1; i>0; i--) {
		buff[i] = buff[i-1];
	}
	buff[0] = value;
}




