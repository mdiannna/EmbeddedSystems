#include <Arduino.h>
#include "photoresistor.h"
#include "mystdio.h"
#include "led.h"
#include "analoglibrary.h"
#include "airPressure.h"

#define R 10000 //ohm resistance value
#define Vin 5 // input voltage

void setup() {
	SerialInit();
	PhotoresistorInit();
	LED_Init();
	InitBMPSensor();

	printf("Initialization done\n");
}

void loop() {

	int lightLevel = ReadLightLevel();
	float Vout = ADCtoVoltage(lightLevel);
	int resistance = VoltageToResistance(R, Vin, Vout);

	printf("Light level: %d\n\r", lightLevel);
	printf("Voltage: %.2f\n\r", Vout);
	Serial.println(Vout);

	int lux = ResistanceToLumen(resistance);
	printf("Light intensity(lumen) - physical parameter: %d\n\r", lux);

	TestSensorBMP();

	delay(1000);
	LED_On();
	delay(1000);
	LED_Off();
	delay(1000);
}
