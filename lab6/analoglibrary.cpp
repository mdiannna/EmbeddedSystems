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


/**
Convert the raw data value (0 - 1023) to voltage (0.0V - 5.0V):
**/
float ADCtoVoltage(float value) {
	float voltage = value * (5.0 / 1024.0);
	return voltage;
}

void sortBubble(float * arr, int n) {
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
}

void swap(float * arr, int ind1, int ind2) {
	float temp = 0.0;
	temp = arr[ind1];
	arr[ind1] = arr[ind2];
	arr[ind2] = temp;
}

void sort(float * arr) {
	float min = arr[0];
	float temp;
	char minInd = 0;
	char medInd = 1;

	if(arr[1] < min) {
		min = arr[1];
		swap(arr, 0, 1);
	}

	if(arr[2] < min) {
		min = arr[2];
		swap(arr, 0, 2);
	}


	float max = arr[2];
	char maxInd = 2;

	if(arr[1] > max) {
		max = arr[1];
		swap(arr, 2, 1);
	}
}


/**
Salt and pepper filter
**/
float SaltAndPepperFilter(float * buff) {
	Serial.println("Salt and pepper filter");
	sort(buff);
	float median = buff[1];
	printf("Median:");

	Serial.println(median);
	return median;
}


/**
Filtru medie ponderata
**/
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




