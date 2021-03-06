#include <Arduino.h>
#include "mystdio.h"
#include "led.h"
#include "analoglibrary.h"
#include "lightsensor.h"
#include "pressure_temp_altitude.h"

//#define R 10000 //ohm resistance value
//#define R 15000 //ohm resistance value
float R = 15000;

#define Vin 5.0 // input voltage
float * buff;
float * buff2;
int cnt = 0;
float median = 0;

void setup() {
	SerialInit();
	LightSensorInit();
	LED_Init();
	InitBMPSensor();

	buff = (float *) malloc(3*sizeof(float));
	buff2 = (float *) malloc(3*sizeof(float));
	buff[0] = 0.0;
	buff[1] = 0.0;
	buff[2] = 0.0;

	buff2[0] = 0.0;
	buff2[1] = 0.0;
	buff2[2] = 0.0;

	printf("Initialization done\n");
}


void showLightResults(float lightLevel) {
	printf("\n-------\n");
	printf("\n");
	float Vout = ADCtoVoltage(lightLevel);
	float resistance = VoltageToResistance(R, Vin, Vout);

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


void loop() {
	double a, T, P, p0;

	float filteredValue = 0.0;

	float lightLevel = ReadLightLevel();

	printf("light level:\n\r");
	Serial.println(lightLevel);

	if(cnt==3){
		cnt = 0;
	}

	buff[cnt] = lightLevel;

	median = SaltAndPepperFilter(buff);
	printf("median:");
	Serial.println(median);
	PushQueue(buff2, median, 3);
	filteredValue = WeightedAverageFilter(buff2, 3);
	printf("Filtered value:");
	showLightResults(filteredValue);

	cnt++;


	T = SensorGetTemperature();
	printf("\nTemperature: ");
	Serial.print(T,2);
	printf(" deg C, ");

	P = SensorGetPressure(T);
	printf("\nAbsolute pressure: ");
	Serial.print(P,2);
	printf(" mb, ");
	Serial.print(P*0.0295333727,2);
	printf(" inHg");

	p0 = SensorGetRelativePressure(P);
	printf("\nRelative (sea-level) pressure: ");
	Serial.print(p0,2);
	printf(" mb, ");
	Serial.print(p0*0.0295333727,2);
	printf(" inHg");

	a = SensorGetAltitude(P, p0);
	printf("computed altitude: ");
	Serial.print(a,0);
	printf(" meters\n ");


	delay(3000);
}
