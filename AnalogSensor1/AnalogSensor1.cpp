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
int cnt = 0;
float median = 0;

void setup() {
	SerialInit();
	LightSensorInit();
	LED_Init();
	InitBMPSensor();

	buff = (float*) malloc(3*sizeof(float));

	printf("Initialization done\n");
}


void showLightResults(float lightLevel) {
	printf("-------\n");
	printf("\n");
	float Vout = ADCtoVoltage(lightLevel);
	float resistance = VoltageToResistance(R, Vin, Vout);

	//printf("LIGHT LEVEL: %d\n\r", lightLevel);
	printf("LIGHT LEVEL:\n\r");
	Serial.println(lightLevel);
	printf("Resistance: %d\n\r", resistance);
	Serial.println(resistance);

	printf("Voltage: %.2f\n\r", Vout);
	Serial.println(Vout);

	float lux = ResistanceToLumen(resistance);
	printf("Light intensity(lumen) - physical parameter: %f\n\r", lux);
	Serial.print(lux);
	printf("-------\n");
}


void loop() {
	double a, T, P, p0;

	float lightLevel = ReadLightLevel();

	printf("light level:\n\r");
	Serial.println(lightLevel);

	if(cnt==3){
		cnt = 0;
		showLightResults(median);
	}

	buff[cnt] = lightLevel;
	median = SaltAndPepperFilter(buff);
	cnt++;



	T = SensorGetTemperature();
	Serial.print("temperature: ");
	Serial.print(T,2);
	Serial.print(" deg C, ");
	P = SensorGetPressure(T);
	// Print out the measurement:
	Serial.print("absolute pressure: ");
	Serial.print(P,2);
	Serial.print(" mb, ");
	Serial.print(P*0.0295333727,2);
	Serial.println(" inHg");

	p0 = SensorGetRelativePressure(P);
	Serial.print("relative (sea-level) pressure: ");
	Serial.print(p0,2);
	Serial.print(" mb, ");
	Serial.print(p0*0.0295333727,2);
	Serial.println(" inHg");

	a = SensorGetAltitude(P, p0);
	Serial.print("computed altitude: ");
	Serial.print(a,0);
	Serial.print(" meters, ");
	Serial.print(a*3.28084,0);
	Serial.println(" feet");

	//TestSensorBMP();


	delay(500);
	LED_On();
	delay(500);
	LED_Off();
	delay(2500);
}
